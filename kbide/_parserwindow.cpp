/*
***************************************************************************
Copyright (C) 2000-2008 KBasic Software: www.kbasic.com. All rights reserved.
Source codes are copyrighted by Bernd Noetscher 2000-2008.

You may use this source codes under the terms of the GNU Public License (Version 3) as published 
by the Free Software Foundation. 

If you are interested in using the source codes for other licenses or 
commercial development, you must buy commercial licenses from KBasic Software.
***************************************************************************
*/


#include <QtGui>

#include "_parserwindow.h"
#include "../kbshared/_report.h"
#include "../kbshared/_form.h"


#include "_mainwindow.h"
#include "_sourcecodeeditor_editor.h"
#include "_sourcecodeeditor_syntaxhighlighter.h"

#include "_inputtip_parser.h"


extern _mainwindow *EXTERN_my_mainwindow;
extern _form *EXTERN_my_form;
extern _report *EXTERN_my_report;


extern QMap<QString, _inputtip_parser>ci;

extern QString kbasicPath(QString sPath);
extern const QIcon &kbasicIcon(QString s);
extern QString kbasicControlPath(QString s);

extern QMap<QString, QString> list;
extern QMap<QString, QString> list_desc;

extern QList<_class>framework_classes;
extern QList<_variable>framework_variables;
extern QList<_method>framework_methods;


extern _parserwindow *EXTERN_my_parserwindow;

_parserwindow::_parserwindow(QWidget *parent) : QWidget(parent)
{
  setAttribute(Qt::WA_DeleteOnClose);

  EXTERN_my_parserwindow = this;
  /*
  QPalette p = palette();
  QColor c = Qt::lightGray; c = c.light();
  p.setColor(QPalette::Window, c);  
  p.setColor(QPalette::Base, c);  
  setPalette(p);
*/
  QVBoxLayout *l = new QVBoxLayout();
  l->setMargin(0);
  l->setSpacing(0);
  setLayout(l);
  

  QAction *a = 0;
  QAction *aAll = 0;
  
  ag = new QActionGroup(this);
  ag->setExclusive(true);
  
  QToolBar *tb = new QToolBar(this); l->addWidget(tb);
   
  a = tb->addAction(tr("Form"), this, SLOT(actionSelected())); a->setActionGroup(ag); a->setCheckable(true);
  a = tb->addAction(tr("Report"), this, SLOT(actionSelected())); a->setActionGroup(ag); a->setCheckable(true);
  aAll = a = tb->addAction(tr("Opened Files"), this, SLOT(actionSelected())); a->setActionGroup(ag); a->setCheckable(true);
  a = tb->addAction(MYAPP, this, SLOT(actionSelected())); a->setActionGroup(ag); a->setCheckable(true);
  a = tb->addAction(tr("Builtin"), this, SLOT(actionSelected())); a->setActionGroup(ag); a->setCheckable(true);
  
  { // add extra space
    QWidget *ww = new QWidget();
    QSizePolicy sp;
    sp.setHorizontalPolicy(QSizePolicy::Expanding);
    ww->setSizePolicy(sp);
    tb->addWidget(ww);
  }
  /*
  QTabBar *tb = new QTabBar(this); l->addWidget(tb);
  
  tb->addTab(tr("Form"));
  tb->addTab(tr("Report"));
  tb->addTab(tr("Opened Files"));
  //tb->addTab(tr("@"));
  tb->addTab(tr(MYAPP));
  tb->addTab(tr("Builtin"));

  connect(tb, SIGNAL(currentChanged(int)), this, SLOT(currentChanged(int)));
*/

  QSplitter *sl = new QSplitter(Qt::Vertical, this);
  l->addWidget(sl);

  te = new QTextEdit(this);
  te->setMaximumHeight(60);
  te->setReadOnly(true);
  _sourcecodeeditor_syntaxhighlighter *highlighter = new _sourcecodeeditor_syntaxhighlighter(te->document());


  tree = new QTreeWidget(this);
  tree->header()->hide();
  connect(tree, SIGNAL(itemDoubleClicked(QTreeWidgetItem *, int)), this, SLOT(itemDoubleClicked(QTreeWidgetItem *, int)));
  connect(tree, SIGNAL(itemSelectionChanged()), this, SLOT(itemSelectionChanged()));

  //l->addWidget(tree);
  tree->setHeaderLabel("");
  //tree->setSortingEnabled(true);

  sl->addWidget(tree);
  sl->addWidget(te);

#ifdef MAC
  QFont f = tree->font(); f.setPixelSize(10); tree->setFont(f); 
#endif

  createTree();
  
  {
    _sourcecodeeditor_editor::createList();

    QMapIterator<QString, QString> i(list);
    while (i.hasNext()) {
        i.next();

        QTreeWidgetItem *e = new QTreeWidgetItem(_builtin, QStringList(""));
        QString s = i.value();
        QString ss = i.key();
        e->setIcon(0, ss == "Constant" ? kbasicIcon(kbasicPath("ide/Constant.png")) : s.contains(") As ") ? kbasicIcon(kbasicPath("ide/Function.png")) : kbasicIcon(kbasicPath("ide/Sub.png")));          

        e->setText(0, s);
        e->setText(1, " ' " + list_desc[ss]);
        e->setToolTip(0, e->text(0));
        e->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    }
  }

  {
    _inputtip_parser::framework_parse();
    
    QListIterator<_class> i(framework_classes);
    while (i.hasNext()){

        _class my_class = i.next();

        QTreeWidgetItem *e = new QTreeWidgetItem(_framework, QStringList(""));
        QString s = kbasicControlPath(my_class.name.toLower() + ".png");

        if (QFile::exists(s)){
          e->setIcon(0, kbasicIcon(s));          
        } else {
          e->setIcon(0, kbasicIcon(kbasicPath("ide/Class.png")));          
        }


        e->setText(0, my_class.name);
        e->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        e->setExpanded(false);
        

        {

          QTreeWidgetItem *property = new QTreeWidgetItem(e, QStringList(""));
          property->setText(0, tr("Property"));
          property->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
          property->setExpanded(true);

          QListIterator<_variable> i(framework_variables);
          while (i.hasNext()){
            _variable my_variable = i.next();
            if (my_variable.scope != my_class.name) continue;

            QTreeWidgetItem *e = new QTreeWidgetItem(property, QStringList(""));
            e->setIcon(0, kbasicIcon(kbasicPath("ide/Property.png")));          
            e->setText(0, my_variable.name + " As " + my_variable.type);
            e->setText(1, "Property " + my_variable.name + " As " + my_variable.type);
            e->setToolTip(0, e->text(1));
            e->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

          }
        }

        {
          bool b_event = true;
          bool b_method = true;

          QTreeWidgetItem *event;
          QTreeWidgetItem *method;

          QListIterator<_method> i(framework_methods);
          while (i.hasNext()){
            _method my_method = i.next();
            if (my_method.scope != my_class.name) continue;

            if (my_method.methodtype == _event){
              
              if (b_event){
                b_event = false;

                event = new QTreeWidgetItem(e, QStringList(""));
                event->setText(0, tr("Event"));
                event->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
                event->setExpanded(true);
              }

              QTreeWidgetItem *e = new QTreeWidgetItem(event, QStringList(""));            
              e->setIcon(0, !my_method.type.isEmpty() ? kbasicIcon(kbasicPath("ide/Function.png")) : kbasicIcon(kbasicPath("ide/Sub.png")));          
              e->setText(0, my_method.name + "(" + my_method.def + ")");
              e->setText(1, "Sub " + my_method.name + "(" + my_method.def + ")");
              e->setToolTip(0, e->text(1));
              
              e->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

            } else {
              if (b_method){
                b_method = false;

                method = new QTreeWidgetItem(e, QStringList(""));
                method->setText(0, tr("Method"));
                method->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
                method->setExpanded(true);
              }

              QTreeWidgetItem *e = new QTreeWidgetItem(method, QStringList(""));            
              e->setIcon(0, my_method.methodtype == _function ? kbasicIcon(kbasicPath("ide/Function.png")) : kbasicIcon(kbasicPath("ide/Sub.png")));          
              if (my_method.methodtype == _function){
                e->setText(0, my_method.name + "(" + my_method.def + ")" + " As " + my_method.type);
                e->setText(1, "Function " + my_method.name + "(" + my_method.def + ")" + " As " + my_method.type);
              } else {
                e->setText(0, my_method.name + "(" + my_method.def + ")");
                e->setText(1, "Sub " + my_method.name + "(" + my_method.def + ")");
              }
              e->setToolTip(0, e->text(1));
              e->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

            }

          }
        }

    }
  }

  refreshProject();

  aAll->setChecked(true);


}

void _parserwindow::refreshProject(QString sIgnoreFile)
{
  QTreeWidgetItem *t;

  _custom->takeChildren();

 QMapIterator<QString, _inputtip_parser> i(ci);
 while (i.hasNext()) {

    i.next();

    QString sFilename = i.key();

    if (sFilename == sIgnoreFile) continue;

    _inputtip_parser pp = i.value();
                
    QString ss = EXTERN_my_mainwindow->getFilenameWithoutPath(sFilename);

    t = new QTreeWidgetItem(_custom, QStringList(ss));

    QString s = "";

    if (ss.endsWith(".kbasic_form", Qt::CaseInsensitive)){
      s = "ide/PROJECT_NEW_FORM.png";
    } else if (ss.endsWith(".kbasic_module", Qt::CaseInsensitive)){
      s = "ide/PROJECT_NEW_MODULE.png";
    } else if (ss.endsWith(".kbasic_class", Qt::CaseInsensitive)){
      s = "ide/PROJECT_NEW_CLASS.png";
    } else if (ss.endsWith(".kbasic_report", Qt::CaseInsensitive)){
      s = "ide/PROJECT_NEW_REPORT.png";
    } else if (ss.endsWith(".kbasic_menubar", Qt::CaseInsensitive)){
      s = "ide/PROJECT_NEW_MENUBAR.png";
    } else if (ss.endsWith(".kbasic_toolbar", Qt::CaseInsensitive)){
      s = "ide/PROJECT_NEW_TOOLBAR.png";
    } else if (ss.endsWith(".kbasic", Qt::CaseInsensitive)){
      s = "ide/PROJECT_NEW_MODULE.png";
    }

    if (!s.isEmpty()) t->setIcon(0, kbasicIcon(kbasicPath(s)));
    t->setExpanded(false);

    _constants = new QTreeWidgetItem(t, QStringList(tr("Constants")));
    _constants->setExpanded(true);

    _variables = new QTreeWidgetItem(t, QStringList(tr("Variables")));
    _variables->setExpanded(true);

    _methods = new QTreeWidgetItem(t, QStringList(tr("Methods")));
    _methods->setExpanded(true);

    _properties = new QTreeWidgetItem(t, QStringList(tr("Properties")));
    _properties->setExpanded(true);

    _enums = new QTreeWidgetItem(t, QStringList(tr("Enums")));
    _enums->setExpanded(true);

    _types = new QTreeWidgetItem(t, QStringList(tr("Types")));
    _types->setExpanded(true);

    QList<_inputtip_info> l = EXTERN_my_mainwindow->ci_getAllForFile(sFilename);

    foreach (_inputtip_info v, l)
    {         

        QString ss = "";
        switch(v.type){
          case __sub: 
            if (v.name.contains("_On")){
              ss = "ide/Event.png"; t = _methods;
            } else {
              ss = "ide/Sub.png"; t = _methods; 
            }
            break;
          case __function: ss = "ide/Function.png"; t = _methods; break;
          case __constructor: ss = "ide/Constructor.png"; t = _methods; break;
          case __enum: ss = "ide/Enum.png"; t = _enums; break;
          case __type: ss = "ide/Type.png"; t = _types; break;
          case __constant: ss = "ide/Constant.png"; t = _constants; break;
          case __property2: ss = "ide/Property.png"; t = _properties; break;
          case __variable:             
            {
              ss = "ide/Variable.png";
              if (!v.type_name.isEmpty()){
                #ifdef MAC
                  ss = "ide/controls/mac/" + v.type_name.toLower() + ".png";    // HIDE
                #else
                #ifdef WINDOWS
                  ss = "ide/controls/windows/" + v.type_name.toLower() + ".png";    // HIDE
                #else
                  ss = "ide/controls/linux/" + v.type_name.toLower() + ".png";   
                #endif
                #endif
              }

              t = _variables; 
              break;
             }                                   
            
            t = _variables; break;
          case __event2: ss = "ide/Event.png"; t = _methods; break;
          default: continue; break;
        }

        QTreeWidgetItem *m = new QTreeWidgetItem(t, QStringList(""));
        m->setIcon(0, kbasicIcon(kbasicPath(ss)));          
        m->setText(0, v.name);
        m->setText(2, v.file);
        m->setText(3, QString("%1").arg(v.line));
        m->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        m->setExpanded(false);
    }

  }            


}

void _parserwindow::itemDoubleClicked2(QTreeWidgetItem *item, int column)
{   
  QString file = item->text(2);
  QString line = item->text(3);

  if (!line.isEmpty()) EXTERN_my_mainwindow->showError(file, line.toInt(), "");
}

void _parserwindow::createTree()
{

  _framework = 0;


  tree->clear();
  tree->setHidden(false);

  QTreeWidgetItem *t;

  t = _all = new QTreeWidgetItem(tree, QStringList(tr("All"))); 
  t->setIcon(0, kbasicIcon(kbasicPath("ide/PROJECT_FOLDER.png")));  
  t->setExpanded(true);



  _form = new QTreeWidgetItem(_all, QStringList(tr("Form")));
  _form->setExpanded(true);
  _form->setIcon(0, kbasicIcon(kbasicPath("ide/VIEW_FORM.png")));

  _report = new QTreeWidgetItem(_all, QStringList(tr("Report")));
  _report->setExpanded(true);
  _report->setIcon(0, kbasicIcon(kbasicPath("ide/VIEW_REPORT.png")));


  _custom = new QTreeWidgetItem(_all, QStringList(tr("Opened Files")));
  _custom->setExpanded(true);
  _custom->setIcon(0, kbasicIcon(kbasicPath("ide/PROJECT_DATABASE.png")));
  /*
  _file = new QTreeWidgetItem(_all, QStringList(tr("@")));
  //_file->setExpanded(true);
*/
  _framework = new QTreeWidgetItem(_all, QStringList(tr(MYAPP)));
  _framework->setExpanded(true);
  _framework->setIcon(0, kbasicIcon(kbasicPath("ide/kbasic_icon.png")));

  _builtin = new QTreeWidgetItem(_all, QStringList(tr("Builtin")));
  _builtin->setExpanded(true);
  _builtin->setIcon(0, kbasicIcon(kbasicPath("ide/PROJECT_NEW_MODULE.png")));
}

void _parserwindow::refresh(QString sFile)
{
  return;
}

void _parserwindow::refreshControl()
{
  _form->takeChildren();
  _report->takeChildren();

  if (EXTERN_my_form){

    QWidget *c;

    if (EXTERN_my_form->firstControl(&c)){
      do {

        if (c->isHidden()) continue;

        QString sControlName = c->objectName();
        //QVariant v = c->property("ControlType");
        QString sControlType = c->property("ControlType").toString();
        QString sSQLName = "";

        #define SWITCH6 EXTERN_my_form->controlType(c)

        #define SWITCH GETPROPERTY_SQLName();
        #define SWITCH3 sSQLName
        #include "../kbshared/_form_property_switch.h" 
        #undef SWITCH3

        #undef SWITCH6

        QTreeWidgetItem *e = new QTreeWidgetItem(_form, QStringList(""));

        e->setIcon(0, kbasicIcon(kbasicControlPath("" + sControlType.toLower() + ".png")));          

        e->setText(0, sControlName + (sSQLName.isEmpty() ? "" : " (" + sSQLName + ")"));
        e->setText(1, "Select KBFormControl");
        e->setText(2, QString("%1").arg((int) c));
        e->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);


      } while (EXTERN_my_form->nextControl(&c));
    }

  }

  if (EXTERN_my_report){

    QWidget *c;

    if (EXTERN_my_report->firstControl(&c)){
      do {

        if (c->isHidden()) continue;

        QString sControlName = c->objectName();
        QString sControlType = c->property("ControlType").toString();
        QString sSQLName = "";

        #define SWITCH6 EXTERN_my_report->controlType(c)

        #define SWITCH GETPROPERTY_SQLName();
        #define SWITCH3 sSQLName
        #include "../kbshared/_form_property_switch.h" 
        #undef SWITCH3

        #undef SWITCH6

        QTreeWidgetItem *e = new QTreeWidgetItem(_report, QStringList(""));

        e->setIcon(0, kbasicIcon(kbasicControlPath("" + sControlType.toLower() + ".png")));          

        e->setText(0, sControlName + (sSQLName.isEmpty() ? "" : " (" + sSQLName + ")"));
        e->setText(1, "Select KBReportControl");
        e->setText(2, QString("%1").arg((int) c));
        e->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);


      } while (EXTERN_my_report->nextControl(&c));
    }

  }

}


void _parserwindow::itemDoubleClicked(QTreeWidgetItem *item, int column)
{   
  QString file = item->text(2);
  QString line = item->text(3);

  int n = line.toInt();

  if (n < 0){
    QMessageBox::information(this, MYAPP, tr("The selected variable is a control added during compilation automatically by KBasic.\n"));
  } 
  if (!line.isEmpty()) EXTERN_my_mainwindow->showError(file, n, "");

}

void _parserwindow::itemSelectionChanged()
{  
  QList<QTreeWidgetItem *>l = tree->selectedItems();
  for (int i = 0; i < l.size(); ++i) {
     QTreeWidgetItem *it = l.at(i);

     if (it->text(1) == "Select KBFormControl"){
       if (EXTERN_my_form){
         EXTERN_my_form->unselectAllControls();
         QString s = it->text(2);
         EXTERN_my_form->selectControl((QWidget *) ((int) s.toInt()));
         EXTERN_my_form->updatePropertyWindow(true);
         EXTERN_my_form->activateWindow();
         EXTERN_my_form->setFocus();
       }

     } else if (it->text(1) == "Select KBReportControl"){
       if (EXTERN_my_report){
         EXTERN_my_report->unselectAllControls();
         QString s = it->text(2);
         EXTERN_my_report->selectControl((QWidget *) ((int) s.toInt()));
         EXTERN_my_report->updatePropertyWindow(true);
         EXTERN_my_report->activateWindow();
         EXTERN_my_report->setFocus();
       }
     } else {
       te->setText(it->text(1));
       if (!te->toPlainText().isEmpty()) te->show();
     }
     break;
  }
    
}

void _parserwindow::actionSelected()
{
  if (_framework == 0) return;

  QAction *a = ag->checkedAction();

  if (a->text().compare(tr("Form"), Qt::CaseInsensitive) == 0){
      _framework->setExpanded(false);
      _builtin->setExpanded(false);
      _custom->setExpanded(false);
      //_file->setExpanded(false);
      _form->setExpanded(true);
      _report->setExpanded(false);
   } else if (a->text().compare(tr("Report"), Qt::CaseInsensitive) == 0){
      _framework->setExpanded(false);
      _builtin->setExpanded(false);
      _custom->setExpanded(false);
      //_file->setExpanded(false);
      _form->setExpanded(false);
      _report->setExpanded(true);
      te->hide();
      te->setText("");
   } else if (a->text().compare(tr("Opened Files"), Qt::CaseInsensitive) == 0){
      _framework->setExpanded(false);
      _builtin->setExpanded(false);
      _custom->setExpanded(true);
      //_file->setExpanded(false);
      _form->setExpanded(false);
      _report->setExpanded(false);
      if (!te->toPlainText().isEmpty()) te->show();
   } else if (a->text().compare(tr(MYAPP), Qt::CaseInsensitive) == 0){
      _framework->setExpanded(true);
      _builtin->setExpanded(false);
      _custom->setExpanded(false);
      //_file->setExpanded(false);
      _form->setExpanded(false);
      _report->setExpanded(false);
      if (!te->toPlainText().isEmpty()) te->show();
   } else if (a->text().compare(tr("Builtin"), Qt::CaseInsensitive) == 0){
      _framework->setExpanded(false);
      _builtin->setExpanded(true);
      _custom->setExpanded(false);
      //_file->setExpanded(false);
      _form->setExpanded(false);
      _report->setExpanded(false);
      if (!te->toPlainText().isEmpty()) te->show();

   }
}

