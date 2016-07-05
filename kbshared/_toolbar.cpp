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

#include "_toolbar.h"

_toolbar *EXTERN_my_toolbar;

#ifdef IDE
#include "../kbide/_mainwindow.h"
#include "../kbide/_propertywindow.h"
#include "../kbide/_helpwindow_shortcut.h"
#include "../kbide/_sourcecodeeditor.h"
#include "../kbide/_help.h"

extern int nPropertyWindowForWhat;
//extern _helpwindow *EXTERN_my_helpwindow;
#endif

#ifdef RUN
QMap<QString, QActionGroup*>toolbar_actiongroups;

#include "../kbasic_binding/_toolbaritem/kb_toolbaritem.h"

#include "../kbrun/interpreter.h"

_toolbaritem *currentToolBarItem = 0;
#include "_menubar.h"

extern _menubar *EXTERN_my_menubar;


QString _toolbar::loadProjectFile (QString sFile) 
{
  return  QString::fromUtf8(myInterpreter->loadProjectFile(sFile));
}

t_pointer _toolbar::loadProjectFile(QString sFile, t_integer *nSize)
{
    return myInterpreter->loadProjectFile(sFile, nSize);
}

QPixmap _toolbar::loadProjectImage(QString sFile)
{
    t_integer n = 0;
    t_pointer pp = loadProjectFile(sFile, &n);
    QPixmap p;
//    QByteArray b(n);
  //  b.assign((const char *) pp, n);
    bool b = p.loadFromData((const uchar *) pp, n);
    if (b == false){
      static QPixmap pp = QPixmap();
      p = pp;
    }
    return p;
}


_toolbar::_toolbar(_form *f, QWidget *parent) : QToolBar(parent ? parent : (QWidget *) f)
{
  my_form = f;
#ifdef MAC
  setToolButtonStyle(Qt::ToolButtonTextUnderIcon); // HIDE
#endif
/*

        QWidget *w = this;//->parentWidget();
        w->setAutoFillBackground(true);
        QPalette p = w->palette();
        QColor c = QColor(0, 0, 0, 55 * 2.55);
        p.setColor(QPalette::Window, c);  
        w->setPalette(p);
*/
  //connect(this, SIGNAL(hovered(QAction *)), this, SLOT(hovered(QAction *)));
}


kb_toolbaritem *_toolbar::METHOD_ToolBarItem(const QString & Name, _toolbar *my_toolbar)
{
  _toolbaritem *c;

  if (my_toolbar->firstControl(&c)){
   
    do {

      if (c->GETPROPERTY_Name().compare(Name, Qt::CaseInsensitive) == 0){
        return (kb_toolbaritem *) c;
      }

    } while (my_toolbar->nextControl(&c)); 
  }

  return 0;
}


void _toolbar::METHOD_2SetEnabled(QString ToolBarItemName, t_boolean Enabled, _toolbar *my_toolbar)
{
  _toolbaritem *c;

  if (my_toolbar->firstControl(&c)){
   
    do {

      if (c->GETPROPERTY_Name().compare(ToolBarItemName, Qt::CaseInsensitive) == 0){

        c->SETPROPERTY_Enabled(Enabled);
        return;
      }

    } while (my_toolbar->nextControl(&c)); 
  }
}

t_boolean _toolbar::METHOD_2IsEnabled(QString ToolBarItemName, _toolbar *my_toolbar)
{
  _toolbaritem *c;

  if (my_toolbar->firstControl(&c)){
   
    do {

      if (c->GETPROPERTY_Name().compare(ToolBarItemName, Qt::CaseInsensitive) == 0){
        return c->GETPROPERTY_Enabled();        
      }

    } while (my_toolbar->nextControl(&c)); 
  }
  return false;
}

void _toolbar::METHOD_2SetVisible(QString ToolBarItemName, t_boolean Visible, _toolbar *my_toolbar)
{
  _toolbaritem *c;

  if (my_toolbar->firstControl(&c)){
   
    do {

      if (c->GETPROPERTY_Name().compare(ToolBarItemName, Qt::CaseInsensitive) == 0){

        c->SETPROPERTY_Visible(Visible);
        //repaint();

        return;
      }

    } while (my_toolbar->nextControl(&c)); 
  }
}

t_boolean _toolbar::METHOD_2IsVisible(QString ToolBarItemName, _toolbar *my_toolbar)
{
  _toolbaritem *c;

  if (my_toolbar->firstControl(&c)){
   
    do {

      if (c->GETPROPERTY_Name().compare(ToolBarItemName, Qt::CaseInsensitive) == 0){
        return c->GETPROPERTY_Visible();        
      }

    } while (my_toolbar->nextControl(&c)); 
  }
  return false;
}


void _toolbar::METHOD_InsertControl(int Index, _control *cc, _toolbar *my_toolbar)
{
  _toolbaritem *c;
  QAction *a = 0;

  if (my_toolbar->firstControl(&c)){
   
    do {

      if (c->GETPROPERTY_ParentIndex() == Index){
        a = ((kb_toolbaritem *) c)->my_qaction;
      }

    } while (my_toolbar->nextControl(&c)); 
  }

  if (a){
    my_toolbar->insertWidget(a, (QWidget *) cc);
    
  }

}

void _toolbar::METHOD_SetVisible(t_boolean b, _toolbar *my_toolbar)
{
  my_toolbar->setHidden(!b);
}

t_boolean _toolbar::METHOD_IsVisible(_toolbar *my_toolbar)
{
  return !my_toolbar->isHidden();
}

void _toolbar::EVENT_OnEvent()
{ 
  if (currentToolBarItem->GETPROPERTY_Enabled() == false){
    acName = "";
    acGroup = "";
    return;
  }

  static QString sName; sName = currentToolBarItem->GETPROPERTY_Name();
  static QByteArray a; a = sName.toAscii();
  acName = a.data();    
  acGroup = "";

}


void _toolbar::EVENT_OnEvent(QString ToolBarItemName)
{ 
}

void _toolbar::build()
{  
  
  _toolbaritem *c;
  _toolbaritem *m;  


  bool b = true;


  int i = 0; 
  int n = 0;

  while (true){
    n++; if (n > 10000) break; 

    if (firstControl(&c)){
      b = false;

      do {

       m = (_toolbaritem *) c;

       int nIndex = m->nIndex;

       QString kk;

       if (i == nIndex){



          m->SETPROPERTY_ParentIndex(m->nIndex);

          QToolButton *x = new QToolButton(this);
          m->my_qaction = this->addWidget(x);
          m->my_qtoolbutton = x;
          x->setDefaultAction(m->my_qaction);

          
          m->my_qaction->setStatusTip(m->GETPROPERTY_StatusTip());
          m->my_qaction->setToolTip(m->GETPROPERTY_ToolTip());
          m->my_qaction->setWhatsThis(m->GETPROPERTY_WhatsThis());

          if (!m->GETPROPERTY_Enabled()){
            
            x->setEnabled(false);
            m->my_qaction->setEnabled(false);
          }
          QString u = m->GETPROPERTY_Icon();
          if (!u.isEmpty()){
            QIcon i = QIcon(loadProjectImage(u));
            x->setIcon(i);
            m->my_qaction->setIcon(i);
            
          }

          bool b = m->GETPROPERTY_Visible();
          if (b == false){
            m->my_qaction->setVisible(b);
          }

          b = m->GETPROPERTY_Checkable();
          if (b){
            m->my_qaction->setCheckable(b);
            if (!toolbar_actiongroups.contains(m->GETPROPERTY_Group())){
              toolbar_actiongroups[m->GETPROPERTY_Group().toLower()] = new QActionGroup(EXTERN_my_toolbar);
              m->SETPROPERTY_Checked(true);
            }
            toolbar_actiongroups[m->GETPROPERTY_Group().toLower()]->addAction(m->my_qaction);      
            toolbar_actiongroups[m->GETPROPERTY_Group().toLower()]->setExclusive(true);

          }
          
          b = m->GETPROPERTY_Checked();
          if (b){
            m->my_qaction->setChecked(b);
          }
          //else 
          
          QString ss = m->GETPROPERTY_ArrowType();
          if (!ss.isEmpty()) m->SETPROPERTY_ArrowType(ss);

          ss = m->GETPROPERTY_PopupMode();
          if (!ss.isEmpty()) m->SETPROPERTY_PopupMode(ss);

          x->setToolTip(m->GETPROPERTY_ToolTip());
          m->my_qaction->setToolTip(m->GETPROPERTY_ToolTip());

          x->setStatusTip(m->GETPROPERTY_StatusTip());
          m->my_qaction->setStatusTip(m->GETPROPERTY_StatusTip());

          x->setWhatsThis(m->GETPROPERTY_WhatsThis());
          m->my_qaction->setWhatsThis(m->GETPROPERTY_WhatsThis());
          connect(x, SIGNAL(triggered(QAction *)), this, SLOT(triggered(QAction *))); 
        
          if (m->GETPROPERTY_Separator()){
            this->addSeparator();
          }   
          
          i++;       

         }

      } while (nextControl(&c)); 
    }
  }

  // do the context menus of buttons etc.
  QMapIterator<QString, QString> ii(menusForButtons);
  while (ii.hasNext()){
    ii.next();

    QMenu *my_qmenu = 0;
    bool b = false;

    _toolbaritem *c;

    if (firstControl(&c)){
     
      do {

        if (c->GETPROPERTY_Name().compare(ii.key(), Qt::CaseInsensitive) == 0){
          b = true;
          break;
        }

      } while (nextControl(&c)); 
    }

    if (b == false) return;

    _menubaritem *mbi;
    if (!(mbi = EXTERN_my_menubar->getParent(ii.value()))) mbi = new _menubaritem(0, 0, 0);

    mbi->SETPROPERTY_Name(ii.value());
    EXTERN_my_menubar->METHOD_AppendContextMenu(mbi);
    c->my_qaction->setMenu(mbi->my_qmenu);

  }

}

void _toolbar::triggered(QAction *a)
{
  _toolbaritem *c;
  if (firstControl(&c)){

    do {
      if (a == c->my_qaction){
        currentToolBarItem = c;
        currentToolBarItem->SoundOnEvent();
        if (c->GETPROPERTY_ToolBarRole().contains("WhatsThis", Qt::CaseInsensitive)){
          QWhatsThis::enterWhatsThisMode();
        } else {
          EVENT_OnEvent();
          EVENT_OnEvent(c->GETPROPERTY_Name());
          _application::EVENT_ToolBar_OnEvent(currentToolBarItem->GETPROPERTY_Name());
          _application::EVENT_Actions_OnAction(currentToolBarItem->GETPROPERTY_ActionId());
        }
        break;
      }

    } while (nextControl(&c)); 
  }
  
}


#else


extern QDockWidget *EXTERN_ToolboxForm;
extern QDockWidget *EXTERN_ToolboxReport;
extern QDockWidget *EXTERN_ToolboxMenuBar;
extern QDockWidget *EXTERN_ToolboxToolBar;
extern QDockWidget *EXTERN_Helpwindow_shortcut;

extern QString kbasicPath(QString s);

_toolbaritem *current;


QMap<_toolbaritem*, QToolButton*> toolbutton_list;

extern _helpwindow_shortcut *EXTERN_my_helpwindow_shortcut;
extern _propertywindow *EXTERN_my_propertywindow;

_toolbar::_toolbar(_mainwindow *_my_mainwindow)
{
  bModified = false;

  setAttribute(Qt::WA_DeleteOnClose);

  EXTERN_my_toolbar = this;

#ifdef IDE
  {
    QString k = EXTERN_my_mainwindow->getProjectPath() + "/application.qss";
    if (QFile::exists(k)){
      QString s = "";

      QFile f(k);
      if (!f.open(QIODevice::ReadOnly)){
        QMessageBox::information(this, MYAPP, QString("Could not read from %1").arg(k));
      } else {
        QTextStream t(&f);
        
        t.setCodec("UTF-8");
        t.setAutoDetectUnicode(true);
        t.setGenerateByteOrderMark(true);

        s = t.readAll();
        s = s.replace("\r", "");
        f.close();
      }

      setStyleSheet(s);
    }
  }
#endif
  setFocusPolicy(Qt::StrongFocus);
  setFocus();


  resize(500, 70);
  move(40, 150);
  setWindowIcon(kbasicIcon(kbasicPath("ide/PROJECT_NEW_TOOLBAR.png")));



  my_qtoolbar = new _qtoolbar(this, this);
  QBoxLayout *l = new QBoxLayout(QBoxLayout::TopToBottom);
  l->addWidget(my_qtoolbar);
  l->setMargin(0);
  l->setSpacing(0);

  setLayout(l);

  

  current = 0;

  insertType = t_notype;

  setToolbarSelf();
}

void _toolbar::build()
{  
  
  _toolbaritem *c;
  _toolbaritem *m;  


  my_qtoolbar->clear();  

  bool b = true;

  toolbutton_list.clear();

  int i = 0; 
  int n = 0;

  bool bIsModified = this->isModified();

  while (true){
    n++; if (n > 10000) break; // 

    if (firstControl(&c)){
      b = false;

      do {

       m = (_toolbaritem *) c;

       int nIndex = m->nIndex;

       QString kk;

       if (i == nIndex){

         QString s = m->GETPROPERTY_ToolTip();
      
         if (m->acceptDrops()){ // selected
           s = "-> " + s + " <-";
         }       

         if (!m->GETPROPERTY_Enabled()){
           s = s + " (Enabled = False)";
         }

          m->SETPROPERTY_ParentIndex(m->nIndex);

          QToolButton *x = new QToolButton(my_qtoolbar);
          x->setToolTip(m->GETPROPERTY_Name());
          
          QString u = m->GETPROPERTY_Icon();
          if (!u.isEmpty()){
            x->setIcon(QIcon(loadPixmap(u)));
          }
          else x->setIcon(QIcon(loadPixmap(kbasicPath("ide/FILE_NEW_FILE.png"))));

          
          connect(x, SIGNAL(clicked(bool)), this, SLOT(clicked())); 
          connect(x, SIGNAL(pressed ()), this, SLOT(pressed()));

          toolbutton_list[m] = x;
          



          if (m->acceptDrops()){ // selected
            x->setCheckable ( true );
            x->setDown(true);
          }

          QAction *a = my_qtoolbar->addWidget(x);

          if (m->GETPROPERTY_Separator()){
            my_qtoolbar->addSeparator();
          }   

          
          i++;       

         }

         

       
       

      } while (nextControl(&c)); 
    }
  }

  if (bIsModified == false){
    this->setNonModified();
  }


}


void _toolbar::pressed()
{    

  current = 0;  

  QMap<_toolbaritem*, QToolButton*>::Iterator it;
  for ( it = toolbutton_list.begin(); it != toolbutton_list.end(); ++it ){

    QToolButton *uu = *it;

    if (uu->isDown() && !uu->isCheckable()){
      current = it.key();
      return;
    }
  }     

  for ( it = toolbutton_list.begin(); it != toolbutton_list.end(); ++it ){

    QToolButton *uu = *it;

    if (uu->isDown()){ // 2nd try, propably togglebutton
      current = it.key();
      return;
    }
  }       

}

void _toolbar::clicked()
{  

  {

    // ***
    if (insertType == t_notype){

      _toolbaritem *c;
      _toolbaritem *m;

      unselectAllControls();

      if (firstControl(&c)){

       do {

        m = (_toolbaritem *) c;

        if (m == current){ // selected
          c->setAcceptDrops(true);

          current = m;
          break;
        }

       } while (nextControl(&c)); 
      }

      build();

    // ***
    } else if (insertType == t_delete){

      _toolbaritem *c;
      _toolbaritem *m;

      unselectAllControls();

      int nIndex = 0;

      if (firstControl(&c)){

       do {

        m = (_toolbaritem *) c;

        if (m == current){ // selected

          nIndex = c->nIndex;

          _toolbaritem *k;

          if (firstControl(&k)){   
            do {
              if (k->nIndex > nIndex){
                k->nIndex--;
              }
            } while (nextControl(&k)); 
          }

          deleteControl(c);        
          break;
        }

       } while (nextControl(&c)); 
      }
      
      bModified = true;
      build();

    // ***
    } else if (insertType == t_move){
      

      _toolbaritem *c = 0;
      _toolbaritem *m = 0;
      _toolbaritem *m2 = 0;
     
      int nOldIndex = 0;

      if (firstControl(&c)){

       do {

        m = (_toolbaritem *) c;

        if (c->acceptDrops()){ // selected
          nOldIndex = m->nIndex;
          m->nIndex = current->nIndex;
          m2 = m;
          break;
        }

       } while (nextControl(&c)); 
      }

      if (m2 == 0) return;

      if (firstControl(&c)){

       do {

        m = (_toolbaritem *) c;

        if (c->acceptDrops() == false && m == current){ // selected

          if (m->nIndex > nOldIndex){

            _toolbaritem *k;

            if (firstControl(&k)){   
              do {
                if (k->nIndex > nOldIndex && k->nIndex <= m->nIndex){
                  k->nIndex--;
                }
              } while (nextControl(&k)); 
            }
            m2->nIndex = m->nIndex + 1;

          } else if (m->nIndex < nOldIndex){

            _toolbaritem *k;

            if (firstControl(&k)){   
              do {
                if (k->nIndex < nOldIndex && k->nIndex >= m->nIndex){
                  k->nIndex++;
                }
              } while (nextControl(&k)); 
            }
            m2->nIndex = m->nIndex - 1;

          }


            break;
        }

       } while (nextControl(&c)); 
      }

      bModified = true;

      build();

    // ***
    } else if (insertType == t_toolbaritem){

      _toolbaritem *c;

      switch(insertType){
       case t_toolbaritem:
        c = new _toolbaritem(0);
        break;
       default:
        return;
        break;
      }  

      bModified = true;

      int nToKK = toolbutton_list.count();

      if (current) nToKK = current->nIndex;

      c->nIndex = nToKK;

      METHOD_insertControl(c, insertType);

      unselectAllControls();
      selectControlAlways(c);

      incIndexFor2(c, c->nIndex);
      c->nIndex = nToKK; // reset

      build();
    }
  }

  updatePropertyWindow();

}


void _toolbar::incIndexFor2(_toolbaritem *p, int nIndex)
{  
  
  _toolbaritem *c;
  _toolbaritem *m;
  int nSeparator = 0;


  if (firstControl(&c)){

    int nIndex2 = nIndex + 1;

    do {

      m = (_toolbaritem *) c;

      if (m != p && m->nIndex >= nIndex){

        m->nIndex = nIndex2++;

      }

    } while (nextControl(&c)); 
  }

}


void _toolbar::incIndexFor(_toolbaritem *p, int nIndex)
{  
  
  _toolbaritem *c;
  _toolbaritem *m;
  int nSeparator = 0;


  if (firstControl(&c)){

    int nIndex2 = nIndex;

    do {

      m = (_toolbaritem *) c;

      if (m != p && m->nIndex > nIndex){

        m->nIndex -= nIndex2++;

      }

    } while (nextControl(&c)); 
  }

}

void _toolbar::decIndexFor(_toolbaritem *p, int nIndex)
{  
  
  _toolbaritem *c;
  _toolbaritem *m;

  int nSeparator = 0;

  if (firstControl(&c)){
   
    int nIndex2 = nIndex;

    do {

      m = (_toolbaritem *) c;

      if (p != m && m->nIndex > nIndex){

        m->nIndex = ++nIndex2;


      }

    } while (nextControl(&c)); 
  }

}


void _toolbar::setInsertControlType(_controlType t)
{
  insertType = t;
}

void _toolbar::focusInEvent ( QFocusEvent * e)
{  
  EXTERN_ToolboxForm->hide();
  EXTERN_ToolboxReport->hide();
  EXTERN_ToolboxMenuBar->hide();
  EXTERN_ToolboxToolBar->show();
  EXTERN_Helpwindow_shortcut->hide();

  EXTERN_my_mainwindow->workspace->setActiveSubWindow((QMdiSubWindow *) parentWidget());

    EXTERN_my_mainwindow->updateGeneralActions(
   false,  false,  false,  false, 
   false,  false,  false,  false,  true, 
  
   false,  false,  false, 
   false,  false,  false,  false, 
   false, "");

  nPropertyWindowForWhat = 2;
  EXTERN_my_toolbar = this;
  bool b = isModified();
  updatePropertyWindow();
  if (!b) setNonModified();

//  EXTERN_my_helpwindow->setText("Edit your your ToolBar here.");

  QWidget::focusInEvent(e);
  
}

void _toolbar::updatePropertyWindow()
{
  EXTERN_my_propertywindow->setform->setHidden(true);
  EXTERN_my_propertywindow->showControlName("");

  _toolbaritem *c;
  
  p.clear();

  bool bb = true;

  if (firstControl(&c)){

    do {

      if (c->acceptDrops()){ // missused as selected flag        

      #define SWITCH getProperties();
      #define SWITCH3 p2
      #include "_toolbar_property_switch.h" 
      #undef SWITCH3

        if (bb){
          bb = false;

          _property::addProperties(&p, p2);

        } else {

          _property::mergeProperties(&p, p2);
        }

      }

    } while (nextControl(&c));
    
  }

  updatePropertyWindow2(true);  

}


void _toolbar::updatePropertyWindow2(bool bb, QString sProperty)
{

  t_properties::Iterator it;
  t_properties *a;
  t_property *d =  0;
  bool b = false;
  QString ss = "";

  if (bb){
    EXTERN_my_propertywindow->setEnabled(false);
    EXTERN_my_propertywindow->showProperties(false);

  }

  EXTERN_my_propertywindow->setUpdatesEnabled(false);
  for ( it = p.begin(); it != p.end(); ++it){

    ss = it.key();
    d = *it;

    if (ss == "Name"){
     EXTERN_my_propertywindow->SETPROPERTY_Name(d->display, d->set, d->v_qstring);


    } else if (ss == "ControlType"){
     EXTERN_my_propertywindow->SETPROPERTY_ControlType(d->display, d->set, d->v_qstring);
    } else if (ss == "Caption"){
     EXTERN_my_propertywindow->SETPROPERTY_Caption(d->display, d->set, d->v_qstring);

    } else if (ss == "StatusTip"){ EXTERN_my_propertywindow->SETPROPERTY_StatusTip(d->display, d->set, d->v_qstring);
    } else if (ss == "ToolTip"){ EXTERN_my_propertywindow->SETPROPERTY_ToolTip(d->display, d->set, d->v_qstring);
    //} else if (ss == "StyleSheet"){ EXTERN_my_propertywindow->SETPROPERTY_StyleSheet(d->display, d->set, d->v_qstring);
    } else if (ss == "WhatsThis"){ EXTERN_my_propertywindow->SETPROPERTY_WhatsThis(d->display, d->set, d->v_qstring);
    } else if (ss == "ContextMenu"){ EXTERN_my_propertywindow->SETPROPERTY_ContextMenu(d->display, d->set, d->v_qstring);

    //} else if (ss == "Flag"){ EXTERN_my_propertywindow->SETPROPERTY_Flag(d->display, d->set, d->v_qstring);
    } else if (ss == "Icon"){ EXTERN_my_propertywindow->SETPROPERTY_Icon(d->display, d->set, d->v_qstring);
    } else if (ss == "Group"){ EXTERN_my_propertywindow->SETPROPERTY_Group(d->display, d->set, d->v_qstring);

    //} else if (ss == "Flag"){ EXTERN_my_propertywindow->SETPROPERTY_Flag(d->display, d->set, d->v_qstring);
    } else if (ss == "Icon"){ EXTERN_my_propertywindow->SETPROPERTY_Icon(d->display, d->set, d->v_qstring);
    } else if (ss == "ArrowType"){ EXTERN_my_propertywindow->SETPROPERTY_ArrowType(d->display, d->set, d->v_qstring);
    } else if (ss == "PopupMode"){ EXTERN_my_propertywindow->SETPROPERTY_PopupMode(d->display, d->set, d->v_qstring);
    } else if (ss == "ToolBarRole"){ EXTERN_my_propertywindow->SETPROPERTY_ToolBarRole(d->display, d->set, d->v_qstring);
    } else if (ss == "Checkable"){ EXTERN_my_propertywindow->SETPROPERTY_Checkable(d->display, d->set, d->v_boolean);
    } else if (ss == "SoundOnEvent"){ EXTERN_my_propertywindow->SETPROPERTY_SoundOnEvent(d->display, d->set, d->v_qstring);    
    } else if (ss == "Checked"){ EXTERN_my_propertywindow->SETPROPERTY_Checked(d->display, d->set, d->v_boolean);
    } else if (ss == "Visible"){ EXTERN_my_propertywindow->SETPROPERTY_Visible(d->display, d->set, d->v_boolean);

    } else if (ss == "Enabled"){
     EXTERN_my_propertywindow->SETPROPERTY_Enabled(d->display, d->set, d->v_boolean);

    } else if (ss == "ActionId"){
     EXTERN_my_propertywindow->SETPROPERTY_ActionId(d->display, d->set, d->v_qstring);

    } else if (ss == "Tag"){
     EXTERN_my_propertywindow->SETPROPERTY_Tag(d->display, d->set, d->v_qstring);

    } else if (ss == "Separator"){
     EXTERN_my_propertywindow->SETPROPERTY_Separator(d->display, d->set, d->v_boolean);

    // EVENT
    } 
    
    if (ss == "OnEvent"){ EXTERN_my_propertywindow->SETPROPERTY_OnEvent(d->display, d->set, d->v_event);
    

    }

    // ***

  }

  EXTERN_my_propertywindow->setUpdatesEnabled(true);
  if (bb){
    EXTERN_my_propertywindow->setEnabled(p.count()); nPropertyWindowForWhat = 2;
    //EXTERN_my_propertywindow->showProperties(true);
  }


}

const QPixmap &_toolbar::loadPixmap(QString fn)
{
  static QPixmap p;

  p = QPixmap();
  if (!(fn.contains("/") || fn.contains("\\"))){

    fn = EXTERN_my_mainwindow->getProjectPath() + "/" + fn;      

    if (QFile::exists(fn)){
      p = QPixmap(fn);
    }
    
  } else {

    if (QFile::exists(fn)){
      p = QPixmap(fn);
    }
    
  }

  return p;
  
}

void _toolbar::closeEvent( QCloseEvent *e )
{

  if (isModified()){
      
	  show();
    setFocus();

	  switch( QMessageBox::question( this, tr("Save Changes"), 
	      tr("Save changes to %1?").arg( sFilename ),
	      QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel )){
	    case QMessageBox::Yes:
	        {
		        save();            
		        if (!sFilename.isEmpty())
		          goto a;
		        else
		          e->ignore();
	        }
	        break;
	    case QMessageBox::No:
	        goto a;
	        break;
	    default:
	        e->ignore();
          return;
	        break;
	  }

//  } else {
	 // goto a;
  }
  //return;

a:

  if (parentWidget()){
    QMdiSubWindow *mdis = qobject_cast<QMdiSubWindow *>(parentWidget());
    EXTERN_my_mainwindow->workspace->removeSubWindow(mdis);
  }
  
  e->accept();
  EXTERN_my_toolbar = 0;

  QWidget::closeEvent(e);


}

bool _toolbar::newEvent()
{  
    QString sControlName = "";
    QString sControlType = "";
    QString sParameter = "";
    QString sEvent = "OnEvent";
    if (sControlName.isEmpty()){

//      sControlName = GETPROPERTY_Name();
   //   sControlType = GETPROPERTY_ControlType();

      _toolbaritem *c;

      if (firstControl(&c)){

        do {

          if (c->acceptDrops()){

            #define SWITCH GETPROPERTY_Name();      
            #define SWITCH3 sControlName
            #include "_toolbar_property_switch.h"   
            #undef SWITCH3

            #define SWITCH GETPROPERTY_ControlType();      
            #define SWITCH3 sControlType
            #include "_toolbar_property_switch.h"   
            #undef SWITCH3
          
            break;
          }

        } while (nextControl(&c)); 
      }
      
    }


  EXTERN_my_mainwindow->openToolBarClassSourceCode(getFilename());
  _sourcecodeeditor *o = qobject_cast<_sourcecodeeditor *>(EXTERN_my_mainwindow->workspace->activeSubWindow() ? EXTERN_my_mainwindow->workspace->activeSubWindow()->widget() : 0);
  if (o){
    return o->newEvent (sControlName, sEvent, sParameter);
  }

  return false;

}

void _qtoolbar::paintEvent( QPaintEvent *event )
{
  QToolBar::paintEvent(event);

  QPainter paint( this );


  QRect r = event->rect();

  paint.setPen(Qt::gray);

  for (int y = 0; y < r.bottom() + 11; y += 10){
    for (int x = 0; x < r.right() + 11; x += 10){
        paint.drawPoint(x, y);
    }
  }

  if (toolbutton_list.count() == 0){
    paint.setPen(Qt::black);
    paint.drawText (5, 16, "ToolBar");
  }

}

void _qtoolbar::mouseReleaseEvent ( QMouseEvent * e )
{    
    QToolBar::mouseReleaseEvent(e);

    if (e->button() == Qt::LeftButton){
      if (my_toolbar->insertType == t_toolbaritem){
        current = 0;
        my_toolbar->clicked();
      }
    }    

}

bool _toolbar::isModified()
{  
  _toolbaritem *c;

  if (bModified) return true;

  if (firstControl(&c)){

    do {

      if (c->bModified) return true;

    } while (nextControl(&c)); 
  }

  return bModified;
}

void _toolbar::setNonModified()
{  
  _toolbaritem *c;

  if (firstControl(&c)){

    do {

      c->bModified = false;

    } while (nextControl(&c)); 
  }
  
  bModified = false;
}


#endif

bool _toolbar::loadControl(QString *s, _controlType ct, QString sName)
{ 
  _toolbaritem *c = 0;

#ifdef IDE
  #define SWITCH4 (0);
  #define SWITCH3 c
  #include "_toolbar_property_switch.h" 
  #undef SWITCH3
  #undef SWITCH4
#else
   c = new kb_toolbaritem(0);
#endif

  METHOD_insertControl(c, ct);

  

  #define SWITCH SETPROPERTY_Name(sName);
  #include "_toolbar_property_switch.h"       

  c->my_toolbar = this;

  do {

    const char *sss = (*s).toAscii();

    *s = (*s).trimmed();

    QString sKey;

    bool bb;
    QString ss;
    int nn;

    #define SWITCH loadProperty(s, &sKey, &bb, &ss, &nn);
    #include "_toolbar_property_switch.h"       


    // TOOLBAR_CONTROL // CONTROL 

    if (sKey == "ParentIndex"){      
      #define SWITCH SETPROPERTY_ParentIndex(nn);
      #include "_toolbar_property_switch.h"   

      c->nIndex = nn;//ss.toInt();

    } else if (sKey == "Enabled"){      
      #define SWITCH SETPROPERTY_Enabled(bb);
      #include "_toolbar_property_switch.h"   

      c->bEnabled = bb;
/*
    } else if (sKey == "Visible"){      
      #define SWITCH SETPROPERTY_Visible(bb);
      #include "_toolbar_property_switch.h"        
*/
    } else if (sKey == "Separator"){      
      #define SWITCH SETPROPERTY_Separator(bb);
      #include "_toolbar_property_switch.h"  

      c->bSeparator = bb;
/*
    } else if (sKey == "Checked"){      
      #define SWITCH SETPROPERTY_Checked(bb);
      #include "_toolbar_property_switch.h"  
*/

    } else if (sKey == "Icon"){   
      #define SWITCH SETPROPERTY_Icon(ss);
      #include "_toolbar_property_switch.h"   

      c->sIcon = ss;

    } else if (sKey == "ArrowType"){      
      #define SWITCH SETPROPERTY_ArrowType(ss);
      #include "_toolbar_property_switch.h"   

    } else if (sKey == "PopupMode"){      
      #define SWITCH SETPROPERTY_PopupMode(ss);
      #include "_toolbar_property_switch.h"   

    } else if (sKey == "ToolBarRole"){      
      #define SWITCH SETPROPERTY_ToolBarRole(ss);
      #include "_toolbar_property_switch.h"   

    } else if (sKey == "StatusTip"){      
      #define SWITCH SETPROPERTY_StatusTip(ss);
      #include "_toolbar_property_switch.h"   

    } else if (sKey == "ToolTip"){      
      #define SWITCH SETPROPERTY_ToolTip(ss);
      #include "_toolbar_property_switch.h"   

    } else if (sKey == "WhatsThis"){      
      #define SWITCH SETPROPERTY_WhatsThis(ss);
      #include "_toolbar_property_switch.h"   

    } else if (sKey == "Group"){      
      #define SWITCH SETPROPERTY_Group(ss);
      #include "_toolbar_property_switch.h"   

    } else if (sKey == "Visible"){      
      #define SWITCH SETPROPERTY_Visible(bb);
      #include "_toolbar_property_switch.h"   

    } else if (sKey == "Checkable"){      
      #define SWITCH SETPROPERTY_Checkable(bb);
      #include "_toolbar_property_switch.h"   

    } else if (sKey == "SoundOnEvent"){      
      #define SWITCH SETPROPERTY_SoundOnEvent(ss);
      #include "_toolbar_property_switch.h"        

    } else if (sKey == "Checked"){      
      #define SWITCH SETPROPERTY_Checked(bb);
      #include "_toolbar_property_switch.h"   

    } else if (sKey == "Caption"){      
      #define SWITCH SETPROPERTY_Caption(ss);
      #include "_toolbar_property_switch.h"   

    } else if (sKey == "ActionId"){      
      #define SWITCH SETPROPERTY_ActionId(ss);
      #include "_toolbar_property_switch.h"   

    } else if (sKey == "Tag"){      
      #define SWITCH SETPROPERTY_Tag(ss);
      #include "_toolbar_property_switch.h"   

    } else if (sKey == "ContextMenu"){      
      #define SWITCH SETPROPERTY_ContextMenu(ss);
      #include "_toolbar_property_switch.h"   

    } else if (sKey == "SoundOnEvent"){      
      #define SWITCH SETPROPERTY_SoundOnEvent(ss);
      #include "_toolbar_property_switch.h"   

    // TOOLBAR_EVENT

    } else if (sKey == "OnEvent"){      
      #define SWITCH SETPROPERTY_OnEvent(bb);
      #include "_toolbar_property_switch.h"  

    }

    // ***

  } while ( !((*s).length() <= 0 || (*s).startsWith("End")/* || (*s).startsWith("End ") || (*s).startsWith("End'") || (*s).startsWith("End\n") || (*s).startsWith("End ")*/) );

  *s = (*s).mid(3); // eat 'End'

  return true;
}

#ifdef IDE
QString _toolbar::getToolBarItems(QString sFile)
{
  QString s = "";
  QString re = "";
  int n = getToolBarClassSourceCodeFilePos(sFile, &s);
  s = s.left(n);

  n = 0;
  while ((n = s.indexOf("Begin ToolBarItem ", n)) >= 0){
    n += 18;
    int n2 = s.indexOf("\n", n);
  
    QString sItem = s.mid(n, n2 - n).simplified();  
    re += "Dim " + sItem + " As ToolBarItem\n";// = ToolBar.ToolBarItem(\"" + sItem + "\")\n";

    n = n2;
  }


  return re;
}
#endif



#ifdef RUN
void _toolbar::METHOD_SetWithTag(QString Tag, QString PropertyName, t_boolean bb, _toolbar *my_toolbar)
{
  my_toolbar->METHOD_2SetWithTag(Tag, PropertyName, bb);
}

void _toolbar::METHOD_2SetWithTag(QString Tag, QString PropertyName, t_boolean bb)
{
  _toolbaritem *c;

  _controlType ct = t_toolbaritem;

  if (firstControl(&c)){
   
    do {

      if (c->GETPROPERTY_Tag().compare(Tag, Qt::CaseInsensitive) == 0){

        if (PropertyName.compare("Separator", Qt::CaseInsensitive) == 0){
          #define SWITCH SETPROPERTY_Separator(bb);
          #include "_toolbar_property_switch.h"  
        } else if (PropertyName.compare("Enabled", Qt::CaseInsensitive) == 0){
          #define SWITCH SETPROPERTY_Enabled(bb);
          #include "_toolbar_property_switch.h"  
        } else if (PropertyName.compare("Checked", Qt::CaseInsensitive) == 0){
          #define SWITCH SETPROPERTY_Checked(bb);
          #include "_toolbar_property_switch.h"  
        } else if (PropertyName.compare("Checkable", Qt::CaseInsensitive) == 0){
          #define SWITCH SETPROPERTY_Checkable(bb);
          #include "_toolbar_property_switch.h"  
          
        } else if (PropertyName.compare("Visible", Qt::CaseInsensitive) == 0){
          #define SWITCH SETPROPERTY_Visible(bb);
          #include "_toolbar_property_switch.h"  
        }  
        
      }

    } while (nextControl(&c)); 
  }

}

void _toolbar::METHOD_SetWithTag(QString Tag, QString PropertyName, t_integer nn, _toolbar *my_toolbar)
{
  my_toolbar->METHOD_2SetWithTag(Tag, PropertyName, nn);
}

void _toolbar::METHOD_2SetWithTag(QString Tag, QString PropertyName, t_integer nn)
{
}

void _toolbar::METHOD_SetWithTag(QString Tag, QString PropertyName, QString ss, _toolbar *my_toolbar)
{
  my_toolbar->METHOD_2SetWithTag(Tag, PropertyName, ss);
}

void _toolbar::METHOD_2SetWithTag(QString Tag, QString PropertyName, QString ss)
{
  _toolbaritem *c;

  if (firstControl(&c)){
   
    do {

      if (c->GETPROPERTY_Tag().compare(Tag, Qt::CaseInsensitive) == 0){

        if (PropertyName.compare("Name", Qt::CaseInsensitive) == 0){
          #define SWITCH SETPROPERTY_Name(ss);
          #include "_toolbar_property_switch.h"  
        } else if (PropertyName.compare("ActionId", Qt::CaseInsensitive) == 0){
          #define SWITCH SETPROPERTY_ActionId(ss);
          #include "_toolbar_property_switch.h"  
        } else if (PropertyName.compare("Caption", Qt::CaseInsensitive) == 0){
          #define SWITCH SETPROPERTY_Caption(ss);
          #include "_toolbar_property_switch.h"  
        } else if (PropertyName.compare("Text", Qt::CaseInsensitive) == 0){
          #define SWITCH SETPROPERTY_Caption(ss);
          #include "_toolbar_property_switch.h"  
        } else if (PropertyName.compare("Value", Qt::CaseInsensitive) == 0){
          #define SWITCH SETPROPERTY_Caption(ss);
          #include "_toolbar_property_switch.h"  
        } else if (PropertyName.compare("Tag", Qt::CaseInsensitive) == 0){
          #define SWITCH SETPROPERTY_Tag(ss);
          #include "_toolbar_property_switch.h"  
        } else if (PropertyName.compare("Icon", Qt::CaseInsensitive) == 0){
          #define SWITCH SETPROPERTY_Icon(ss);
          #include "_toolbar_property_switch.h"  
        } else if (PropertyName.compare("StatusTip", Qt::CaseInsensitive) == 0){
          #define SWITCH SETPROPERTY_StatusTip(ss);
          #include "_toolbar_property_switch.h"  
       } else if (PropertyName.compare("ToolTip", Qt::CaseInsensitive) == 0){
          #define SWITCH SETPROPERTY_ToolTip(ss);
          #include "_toolbar_property_switch.h"  
       } else if (PropertyName.compare("WhatsThis", Qt::CaseInsensitive) == 0){
          #define SWITCH SETPROPERTY_WhatsThis(ss);
          #include "_toolbar_property_switch.h"  
        } else if (PropertyName.compare("ToolBarRole", Qt::CaseInsensitive) == 0){
          #define SWITCH SETPROPERTY_ToolBarRole(ss);
          #include "_toolbar_property_switch.h"  
        } else if (PropertyName.compare("Group", Qt::CaseInsensitive) == 0){
          #define SWITCH SETPROPERTY_Group(ss);
          #include "_toolbar_property_switch.h"  
        } else if (PropertyName.compare("ArrowType", Qt::CaseInsensitive) == 0){
          #define SWITCH SETPROPERTY_ArrowType(ss);
          #include "_toolbar_property_switch.h"  
        } else if (PropertyName.compare("PopupMode", Qt::CaseInsensitive) == 0){
          #define SWITCH SETPROPERTY_PopupMode(ss);
          #include "_toolbar_property_switch.h"  
        } else if (PropertyName.compare("SoundOnEvent", Qt::CaseInsensitive) == 0){
          #define SWITCH SETPROPERTY_SoundOnEvent(ss);
          #include "_toolbar_property_switch.h"  
        }  
        
      }

    } while (nextControl(&c)); 
  }
}

void _toolbar::METHOD_SetWithGroup(QString Tag, QString PropertyName, t_boolean bb, _toolbar *my_toolbar)
{
  EXTERN_my_toolbar->METHOD_2SetWithGroup(Tag, PropertyName, bb);
}

void _toolbar::METHOD_2SetWithGroup(QString Group, QString PropertyName, t_boolean bb)
{
  _toolbaritem *c;

  if (firstControl(&c)){
   
    do {

      if (c->GETPROPERTY_Group().compare(Group, Qt::CaseInsensitive) == 0){

        if (PropertyName.compare("Separator", Qt::CaseInsensitive) == 0){
          #define SWITCH SETPROPERTY_Separator(bb);
          #include "_toolbar_property_switch.h"  
        } else if (PropertyName.compare("Enabled", Qt::CaseInsensitive) == 0){
          #define SWITCH SETPROPERTY_Enabled(bb);
          #include "_toolbar_property_switch.h"  
        } else if (PropertyName.compare("Checked", Qt::CaseInsensitive) == 0){
          #define SWITCH SETPROPERTY_Checked(bb);
          #include "_toolbar_property_switch.h"  
        } else if (PropertyName.compare("Checkable", Qt::CaseInsensitive) == 0){
          #define SWITCH SETPROPERTY_Checkable(bb);
          #include "_toolbar_property_switch.h"  
        } else if (PropertyName.compare("Visible", Qt::CaseInsensitive) == 0){
          #define SWITCH SETPROPERTY_Visible(bb);
          #include "_toolbar_property_switch.h"  
        }  
        
      }

    } while (nextControl(&c)); 
  }
}

void _toolbar::METHOD_SetWithGroup(QString Tag, QString PropertyName, t_integer nn, _toolbar *my_toolbar)
{
  my_toolbar->METHOD_2SetWithGroup(Tag, PropertyName, nn);
}

void _toolbar::METHOD_2SetWithGroup(QString Group, QString PropertyName, t_integer nn)
{
}

void _toolbar::METHOD_SetWithGroup(QString Tag, QString PropertyName, QString ss, _toolbar *my_toolbar)
{
  my_toolbar->METHOD_2SetWithGroup(Tag, PropertyName, ss);
}

void _toolbar::METHOD_2SetWithGroup(QString Group, QString PropertyName, QString ss)
{
  _toolbaritem *c;

  if (firstControl(&c)){
   
    do {

      if (c->GETPROPERTY_Group().compare(Group, Qt::CaseInsensitive) == 0){
      
        if (PropertyName.compare("Name", Qt::CaseInsensitive) == 0){
          #define SWITCH SETPROPERTY_Name(ss);
          #include "_toolbar_property_switch.h"           
        } else if (PropertyName.compare("ActionId", Qt::CaseInsensitive) == 0){
          #define SWITCH SETPROPERTY_ActionId(ss);
          #include "_toolbar_property_switch.h"  
        } else if (PropertyName.compare("Caption", Qt::CaseInsensitive) == 0){
          #define SWITCH SETPROPERTY_Caption(ss);
          #include "_toolbar_property_switch.h"  
        } else if (PropertyName.compare("Text", Qt::CaseInsensitive) == 0){
          #define SWITCH SETPROPERTY_Caption(ss);
          #include "_toolbar_property_switch.h"  
        } else if (PropertyName.compare("Value", Qt::CaseInsensitive) == 0){
          #define SWITCH SETPROPERTY_Caption(ss);
          #include "_toolbar_property_switch.h"  
        } else if (PropertyName.compare("Tag", Qt::CaseInsensitive) == 0){
          #define SWITCH SETPROPERTY_Tag(ss);
          #include "_toolbar_property_switch.h"  
        } else if (PropertyName.compare("ActionId", Qt::CaseInsensitive) == 0){
          #define SWITCH SETPROPERTY_ActionId(ss);
          #include "_toolbar_property_switch.h"  
        } else if (PropertyName.compare("Icon", Qt::CaseInsensitive) == 0){
          #define SWITCH SETPROPERTY_Icon(ss);
          #include "_toolbar_property_switch.h"  
        } else if (PropertyName.compare("StatusTip", Qt::CaseInsensitive) == 0){
          #define SWITCH SETPROPERTY_StatusTip(ss);
          #include "_toolbar_property_switch.h"  
       } else if (PropertyName.compare("ToolTip", Qt::CaseInsensitive) == 0){
          #define SWITCH SETPROPERTY_ToolTip(ss);
          #include "_toolbar_property_switch.h"  
       } else if (PropertyName.compare("WhatsThis", Qt::CaseInsensitive) == 0){
          #define SWITCH SETPROPERTY_WhatsThis(ss);
          #include "_toolbar_property_switch.h"  
        } else if (PropertyName.compare("ToolBarRole", Qt::CaseInsensitive) == 0){
          #define SWITCH SETPROPERTY_ToolBarRole(ss);
          #include "_toolbar_property_switch.h"  
        } else if (PropertyName.compare("Group", Qt::CaseInsensitive) == 0){
          #define SWITCH SETPROPERTY_Group(ss);
          #include "_toolbar_property_switch.h"  
        } else if (PropertyName.compare("ArrowType", Qt::CaseInsensitive) == 0){
          #define SWITCH SETPROPERTY_ArrowType(ss);
          #include "_toolbar_property_switch.h"  
        } else if (PropertyName.compare("PopupMode", Qt::CaseInsensitive) == 0){
          #define SWITCH SETPROPERTY_PopupMode(ss);
          #include "_toolbar_property_switch.h"  
        } else if (PropertyName.compare("SoundOnEvent", Qt::CaseInsensitive) == 0){
          #define SWITCH SETPROPERTY_SoundOnEvent(ss);
          #include "_toolbar_property_switch.h"  
          
        }  
        
      }

    } while (nextControl(&c)); 
  }
}

#endif

