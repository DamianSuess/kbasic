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




#include "../kbshared/_form.h"
#include "../kbshared/_tab.h"
#include "../kbshared/_editor.h"
#include "../kbshared/_browser.h"

#include "../kbshared/_strings.h"
#include "../kbshared/_web.h"






#ifdef IDE
#include "../kbide/_mainwindow.h"

extern _mainwindow *EXTERN_my_mainwindow;
#endif


#ifdef RUN
extern interpreter* EXTERN_myInterpreter;

extern const QString interpreter_loadFileAsString(QString fn);

extern QMap<QString, QSqlDatabase> databases;
extern QMap<QString, QSqlQuery *> records;
extern QMap<QString, QString> records_database;
extern QMap<QString, QString> records_table;

extern QSqlDatabase CurrentDatabase;


QString sLastSQLError = "";

QMap<QString, QString> sLastSQLCommands;
QMap<QString, QString> sLastSQLCommandFailed;

#include <QNetworkReply>

#include "moc__databasedialog.cpp"

bool bOk_dbcondialog;
QString p_dbuser;
QString p_dbname;
QString p_dbdriver;
QString p_dbhost;
QString p_dbport;
QString p_dbuserpassword;
QString p_dbconnectoptions;

#include "../kbshared/_dir.h"
#include "../kbshared/_file.h"
#include "../kbrun/interpreter.h"
#include "../kbshared/_menubar.h"
#include "../kbshared/_toolbar.h"

#include "../kbasic_binding/_form/kb_form.h"

extern QMap<int, interpreter_parameter*> v;




#endif

QString sUniqueName;

void rehighlight(_syntaxhighlighter *h)
{
  h->update();
  h->rehighlight();  
}

void my_form_EVENT_OnGotFocus(_form *f)
{
#ifdef RUN
  if (f && EXTERN_myInterpreter->bRunPcode) f->EVENT_OnGotFocus();

#endif
}

void my_form_EVENT_OnLostFocus(_form *f)
{
#ifdef RUN
  if (f && EXTERN_myInterpreter->bRunPcode) f->EVENT_OnLostFocus();
#endif
}

_syntaxhighlighter *new_highlighter(_editor *e, QTextDocument *d)
{
  return new _syntaxhighlighter(e, d);
}

void my_form_readdToCollection(_form *f, QWidget *c, QString old, QString s, const char *acType)
{
#ifdef RUN
  if (f && f->bLoading == false){
    f->readdToCollection(c, old, s, acType);
  }
#endif

}

void my_form_addToCollection(_form *f, QWidget *c, QString s, int nType)
{
#ifdef RUN
  if (f && f->bLoading == false){
    f->addToCollection(c, s, nType);
  }
#endif
}

#ifdef RUN
bool my_form_isOpened(_form *f)
{
  return f && f->isOpened();
}
#endif

bool my_form_isForm(_form *f)
{
  return f == 0 || f->isForm();
}

void my_form_newEvent (_form *f, QString sControlName, QString sEvent, QString sParameter )
{
#ifdef IDE
  if (sControlName == "FormView"){
    EXTERN_my_mainwindow->openForm(EXTERN_my_mainwindow->getProjectPath()+ "/" + sEvent + ".kbasic_form");
  } else {
    f->newEvent (sControlName, sEvent, sParameter);
  }
#endif
}

#ifdef RUN
QPixmap my_form_loadProjectImage(_form *f, QString sFile)
{
  if (f){
    return f->loadProjectImage(sFile);
  }

  t_integer n = 0;
  t_pointer pp = loadProjectFile(sFile, &n);
  QPixmap p;
  bool b = p.loadFromData((const uchar *) pp, n);
  if (b == false){
    static QPixmap pp = QPixmap();
    p = pp;
  }
  return p;
}

QWidget *my_form_getControl(_form *f, QString s)
{
  if (f) return f->getControl(s);
  return 0;
}
#endif

void my_form_setRadioButtonBooleanValue(_form *f, QString sGroup, QWidget *control, t_boolean b)
{
  QWidget *c;

  if (f && f->firstControl(&c, 1)){
    
    do {    
      if (f->controlType(c) == t_radiobutton && c != control){

        QString ss;
  
        #define SWITCH6 f->controlType(c) // must adapt it to this class

        #define SWITCH GETPROPERTY_Group();      
        #define SWITCH3 ss
        #include "_form_property_switch.h"   
        #undef SWITCH3     

        #undef SWITCH6 
#ifdef IDE
        if (ss == sGroup){
          ((_radiobutton *) c)->SETPROPERTY_BooleanValue2(false);
          ((_radiobutton *) c)->setChecked(false);
        }
#endif
#ifdef RUN
        if (ss == sGroup){
          ((kb_radiobutton *) c)->SETPROPERTY_BooleanValue2(false);
          ((kb_radiobutton *) c)->setChecked(false);
        }
#endif
      }      

    } while (f->nextControl(&c, 1)); 
  }
#ifdef IDE
  ((_radiobutton *) control)->SETPROPERTY_BooleanValue2(b);
  ((_radiobutton *) control)->setChecked(b);
#endif
#ifdef RUN
  ((kb_radiobutton *) control)->SETPROPERTY_BooleanValue2(b);
  ((kb_radiobutton *) control)->setChecked(b);
#endif

}


t_boolean _radiobutton::GETPROPERTY_BooleanValue()
{

   bool b = isChecked();
    return b;

  
}



void my_toolbar_setMenuForButton(_toolbar *t, QString sMenuName, QString control)
{
#ifdef RUN
  t->menusForButtons[control] = sMenuName;
#endif
}

void my_form_setMenuForButton(_form *f, QString sMenuName, QWidget *control)
{
#ifdef RUN
  if (f) f->menusForButtons[control] = sMenuName;

#endif
}

void my_form_setCommandButtonBooleanValue(_form *f, QString sGroup, QWidget *control, t_boolean b)
{
  if (!b) b = true;

  QWidget *c;

  if (f && f->firstControl(&c, 1)){
    
    do {    
      if (f->controlType(c) == t_commandbutton && c != control){

        QString ss;
  
        #define SWITCH6 f->controlType(c) // must adapt it to this class

        #define SWITCH GETPROPERTY_Group();      
        #define SWITCH3 ss
        #include "_form_property_switch.h"   
        #undef SWITCH3     

        #undef SWITCH6 
#ifdef IDE
        if (ss == sGroup){
          ((_commandbutton *) c)->SETPROPERTY_Checked2(false);
          ((_commandbutton *) c)->setChecked(false);
        }
#endif
#ifdef RUN
        if (ss == sGroup){
          ((kb_commandbutton *) c)->SETPROPERTY_Checked2(false);
          ((kb_commandbutton *) c)->setChecked(false);
        }
#endif
      }      

    } while (f->nextControl(&c, 1)); 
  }
#ifdef IDE
  ((_commandbutton *) control)->SETPROPERTY_Checked2(b);
  ((_commandbutton *) control)->setChecked(b);
#endif
#ifdef RUN
  ((kb_commandbutton *) control)->SETPROPERTY_Checked2(b);
  ((kb_commandbutton *) control)->setChecked(b);
#endif

}

void my_form_setCommandLinkButtonBooleanValue(_form *f, QString sGroup, QWidget *control, t_boolean b)
{
  if (!b) b = true;

  QWidget *c;

  if (f && f->firstControl(&c, 1)){
    
    do {    
      if (f->controlType(c) == t_commandlinkbutton && c != control){

        QString ss;
  
        #define SWITCH6 f->controlType(c) // must adapt it to this class

        #define SWITCH GETPROPERTY_Group();      
        #define SWITCH3 ss
        #include "_form_property_switch.h"   
        #undef SWITCH3     

        #undef SWITCH6 
#ifdef IDE
        if (ss == sGroup){
          ((_commandlinkbutton *) c)->SETPROPERTY_Checked2(false);
          ((_commandlinkbutton *) c)->setChecked(false);
        }
#endif
#ifdef RUN
        if (ss == sGroup){
          ((kb_commandlinkbutton *) c)->SETPROPERTY_Checked2(false);
          ((kb_commandlinkbutton *) c)->setChecked(false);
        }
#endif
      }      

    } while (f->nextControl(&c, 1)); 
  }
#ifdef IDE
  ((_commandlinkbutton *) control)->SETPROPERTY_Checked2(b);
  ((_commandlinkbutton *) control)->setChecked(b);
#endif
#ifdef RUN
  ((kb_commandlinkbutton *) control)->SETPROPERTY_Checked2(b);
  ((kb_commandlinkbutton *) control)->setChecked(b);
#endif

}

void my_form_setToolButtonBooleanValue(_form *f, QString sGroup, QWidget *control, t_boolean b)
{
  if (!b) b = true;

  QWidget *c;

  if (f && f->firstControl(&c, 1)){
    
    do {    
      if (f->controlType(c) == t_toolbutton && c != control){

        QString ss;
  
        #define SWITCH6 f->controlType(c) // must adapt it to this class

        #define SWITCH GETPROPERTY_Group();      
        #define SWITCH3 ss
        #include "_form_property_switch.h"   
        #undef SWITCH3     

        #undef SWITCH6 
#ifdef IDE
        if (ss == sGroup){
          ((_toolbutton *) c)->SETPROPERTY_Checked2(false);
          ((_toolbutton *) c)->setChecked(false);
        }
#endif
#ifdef RUN
        if (ss == sGroup){
          ((kb_toolbutton *) c)->SETPROPERTY_Checked2(false);
          ((kb_toolbutton *) c)->setChecked(false);
        }
#endif
      }      

    } while (f->nextControl(&c, 1)); 
  }
#ifdef IDE
  ((_toolbutton *) control)->SETPROPERTY_Checked2(b);
  ((_toolbutton *) control)->setChecked(b);
#endif
#ifdef RUN
  ((kb_toolbutton *) control)->SETPROPERTY_Checked2(b);
  ((kb_toolbutton *) control)->setChecked(b);
#endif

}

void my_form_setImageButtonBooleanValue(_form *f, QString sGroup, QWidget *control, t_boolean b)
{
  if (!b) b = true;

  QWidget *c;

  if (f && f->firstControl(&c, 1)){
    
    do {    
      if (f->controlType(c) == t_imagebutton && c != control){

        bool bb = ((_imagebutton *) c)->GETPROPERTY_CheckableExclusive();      

        QString ss = ((_imagebutton *) c)->GETPROPERTY_Group();      
/*
        QString ss;

        #define SWITCH6 f->controlType(c) // must adapt it to this class

        #define SWITCH GETPROPERTY_Group();      
        #define SWITCH3 ss
        #include "_form_property_switch.h"   
        #undef SWITCH3     

        #undef SWITCH6 */
#ifdef IDE
        if (bb == false && ss == sGroup){
          ((_imagebutton *) c)->SETPROPERTY_Checked2(false);
        }
#endif
#ifdef RUN
        if (bb == false && ss == sGroup){
          ((kb_imagebutton *) c)->SETPROPERTY_Checked2(false);

          if (((kb_imagebutton *) c)->GETPROPERTY_Enabled()){
            ((kb_imagebutton *) c)->SETPROPERTY_EnabledImage(((kb_imagebutton *) c)->GETPROPERTY_EnabledImage()); 
          } else {
            ((kb_imagebutton *) c)->SETPROPERTY_DisabledImage(((kb_imagebutton *) c)->GETPROPERTY_DisabledImage());            
          }

          
        }
#endif
      }      

    } while (f->nextControl(&c, 1)); 
  }
#ifdef IDE
  ((_imagebutton *) control)->SETPROPERTY_Checked2(b);
#endif
#ifdef RUN
  ((kb_imagebutton *) control)->SETPROPERTY_Checked2(b);
#endif

}



void _tab::EVENT_OnEvent(int index)
{
#ifdef IDE
  if (my_form) my_form->tabPageSelected(this, index);
#endif
}


void _tab::EVENT_OnEvent2(int index)
{
  #ifdef RUN
  if (my_form) my_form->tabPageSelected(this, index);
  #endif
}


QString my_form_getProjectPath(_form *f)
{
#ifdef IDE
  if (f == 0) return EXTERN_my_mainwindow->getProjectPath();
#endif
  if (f) return f->getPath();
  return qApp->applicationDirPath();
}

QPixmap &my_form_createPixmap(_form *f, QString fn)
{
  static QPixmap p;

  if (!(fn.contains("/") || fn.contains("\\"))){
    if (f){
      fn = my_form_getProjectPath(f) + "/" + fn;
    } else {
      fn = qApp->applicationDirPath() + "/" + fn;
    }    
  }

  if (QFile::exists( fn )){
    QImage img( fn );

  }

  return p;
}

void _syntaxhighlighter::highlightBlock(const QString &text)
{
    bool bHTML = my_editor->GETPROPERTY_Keywords().contains("<");
    

     int nLen = text.length();

     setFormat(0, nLen, normalFormat);

     if (set.count() == 0) return;

     int index = 0;
     int index2 = 0;
     int nString = 0;
     bool b = false;
     bool bbb = false;
     bool bString = false;
      QChar c = 0;
      QChar c2 = 0;
      int nn = 0;


n:
     while (index < nLen){
       int i;
       for (i = index; i < nLen; i++){
         c2 = c;
         c = text.at(i);

         if (c == '\"'){
           if (bString){
              setFormat(nString, i - nString + 1, quotationFormat);              
           } else {
             nString = i;
           }
           bString = !bString;
         }
         if (!bString && c == commentStart2){
           QString r = text.mid(index, i - index);

          if (set2.contains(r)){
            setFormat(index, i - index, commandFormat);
          } else if (set.contains(r)){
            setFormat(index, i - index, keywordFormat);
          }

           setFormat(i, nLen - i, commentFormat);
           goto r;
         }

         if (!bString && ((!c.isLetter() && i == index && c != '_' && (bHTML && c != '<')) || c.isSpace() || c.isMark() || c == '(') || (bHTML && (c == '>' || (nn % 2 == 1 && c == '<')))){
           if (bHTML && c == '>'){
             bbb = true;
             nn++;
             i++;
             break;
           } else if (bHTML && nn % 2 == 1 && c == '<'){
             bbb = true;
             nn--;
             break;
           } else {
             bbb = false;
             break;
           }
           
         }

       }

       QString q = text.mid(index, i - index);
       if (set2.contains(q)){
         setFormat(index, i - index, commandFormat);
         index2 = index + (i - index);
       } else if (set.contains(q)){
         setFormat(index, i - index, keywordFormat);
         index2 = index + (i - index);
       }
       index = i + (bbb ? 0 : 1);
       bbb = false;
       
     }
t:
     index = index2;

     if (b == false && index == -1 && index2 && index2 + 1 < nLen){
       b = true;
       index = index2;
       goto n;
     }
r:

     setCurrentBlockState(0);
     if (!commentStartExpression.pattern().isEmpty()){

        int startIndex = 0;
        if (bHTML){
          if (previousBlockState() != 1) startIndex = text.indexOf("<!--");
        } else {
          if (previousBlockState() != 1) startIndex = text.indexOf(commentStartExpression);
        }

        while (startIndex >= 0) {
          int endIndex;
          if (bHTML){
            endIndex = text.indexOf("-->", startIndex);
          } else {
            endIndex = text.indexOf(commentEndExpression, startIndex);
          }           
          int commentLength;
          if (endIndex == -1){
            setCurrentBlockState(1);
            commentLength = nLen - startIndex;
          } else {
            commentLength = endIndex - startIndex + (bHTML ? 3 : commentEndExpression.matchedLength());
          }
          setFormat(startIndex, commentLength, commentFormat);

          if (bHTML){
            startIndex = text.indexOf("<!--", startIndex + commentLength);
          } else {
            startIndex = text.indexOf(commentStartExpression, startIndex + commentLength);
          }


        }
     }
}


t_integer _treeview::METHOD_AppendChild(const QString & Caption)
{
  QTreeWidgetItem *l = new QTreeWidgetItem(this);
  l->setText(0, Caption);

  return (t_integer) l;
}

void _browser::SETPROPERTY_HomeURL(const QString & n)
{ 
  QString kk = GETPROPERTY_StringValue().simplified();
  if (!kk.isEmpty()) return;

  {

  static QUrl u; 
  QString k = n;

  if (!(k.contains("/") ||k.contains("\\"))){
    k = getProjectPath() + "/" + n;
  
    k = "file:///" + k;
    u = QUrl(k);
    setSource(u);
  } else {
    u = QUrl(k);
    setSource(u);    
  }
    

#ifdef RUN
    _property::SETPROPERTY_HomeURL(k);
#else
    _property::SETPROPERTY_HomeURL(n);
#endif
  }
}

void _web::SETPROPERTY_HomeURL(const QString & n)
{ 
  QString kk = GETPROPERTY_StringValue().simplified();
  if (kk.isEmpty() && n.simplified().isEmpty()) return;

 {  

  QString k = n;
  if (k.startsWith("www.", Qt::CaseInsensitive)){
    k = "http://" + k;
  }

  static QUrl u; 
  if (!(k.contains("/") || k.contains("\\") || k.contains("http://"))){
    k = getProjectPath() + "/" + n;
      
    k = "file:///" + k;

    u = QUrl(k);
    setUrl(u);
  } else {
    u = QUrl(k);
    setUrl(u);
  }
    
      
#ifdef RUN
    _property::SETPROPERTY_HomeURL(k);
#else
    _property::SETPROPERTY_HomeURL(n);
#endif
  }
}

#ifdef RUN
void _spinbox::EVENT_OnSQLEvent()
{
  if (!GETPROPERTY_SQLName().isEmpty() && my_form) my_form->setDirty(true);
}

void _sound::EVENT_OnSQLEvent()
{
  if (!GETPROPERTY_SQLName().isEmpty() && my_form) my_form->setDirty(true);
}

void _movie::EVENT_OnSQLEvent()
{
  if (!GETPROPERTY_SQLName().isEmpty() && my_form) my_form->setDirty(true);
}

void _web::EVENT_OnSQLEvent()
{
  if (!GETPROPERTY_SQLName().isEmpty() && my_form) my_form->setDirty(true);
}

void _browser::EVENT_OnSQLEvent()
{
  if (!GETPROPERTY_SQLName().isEmpty() && my_form) my_form->setDirty(true);
}

void _image::EVENT_OnSQLEvent()
{
  if (!GETPROPERTY_SQLName().isEmpty() && my_form) my_form->setDirty(true);
}

#endif

void _textbox::EVENT_OnSQLEvent()
{
#ifdef RUN
  if (!GETPROPERTY_SQLName().isEmpty() && my_form) my_form->setDirty(true);
#endif
}

void _editor::EVENT_OnSQLEvent()
{
#ifdef RUN
  if (!GETPROPERTY_SQLName().isEmpty() && my_form) my_form->setDirty(true);
  #endif
}

void _checkbox::EVENT_OnSQLEvent()
{
#ifdef RUN
  if (!GETPROPERTY_SQLName().isEmpty() && my_form) my_form->setDirty(true);
  #endif
}

void _combobox::EVENT_OnSQLEvent()
{
#ifdef RUN
  if (!GETPROPERTY_SQLName().isEmpty() && my_form) my_form->setDirty(true);
  #endif
}

void _datebox::EVENT_OnSQLEvent()
{
#ifdef RUN
  if (!GETPROPERTY_SQLName().isEmpty() && my_form) my_form->setDirty(true);
  #endif

}

void _timebox::EVENT_OnSQLEvent()
{
#ifdef RUN
  if (!GETPROPERTY_SQLName().isEmpty() && my_form) my_form->setDirty(true);
  #endif
}

void _listbox::EVENT_OnSQLEvent()
{
  #ifdef RUN
  if (!GETPROPERTY_SQLName().isEmpty() && my_form) my_form->setDirty(true);
  #endif
}

#ifdef RUN
void fillWithSQLForTreeView(QTreeWidget *tree, QTreeWidgetItem *parent, QString & sTable, QString & sSQL, QStringList & groups, QStringList & values, int nCurrent)
{  
  int nCount = groups.count();

  if (nCurrent > nCount){
    nCurrent = -1;
    return;
  }

  QSqlQuery rr(CurrentDatabase);

  QString sWhere = "";
  for(int i = 0; i < nCurrent; i++){
    if (!sWhere.isEmpty()) sWhere += " AND ";
    QString m = values.at(i);
    sWhere += groups.at(i) + " = " + m;
  }
    

  if (nCurrent == nCount){

    QString ss = sSQL;
    bool b = ss.contains(" WHERE ", Qt::CaseInsensitive);
    if (!b){
      if (!sWhere.isEmpty()) sWhere = " WHERE ";
    } else sWhere += " AND ";

    if (!sWhere.isEmpty()){ 
      int n = ss.indexOf(" FROM ", Qt::CaseInsensitive);
      n += b ? 13 : 6;
      int nn = ss.indexOf(" ", n, Qt::CaseInsensitive);
      if (nn >= 0) n = nn;

      sWhere = " " + sWhere;
      ss.insert(n, sWhere);
    }

      if (rr.exec(ss)){

        if (rr.first()){

          QSqlRecord r = rr.record();
/*
          for (int i = 0; i < r.count() - 1; i++){
            tree->headerItem()->setText(nCount + i, r.fieldName(i + 1));
          }*/

          do {          
        
            QStringList l;
            
            for (int i = 0; i < r.count() - 1; i++){
              QString sss = rr.value(i + 1).toString();
              l.append(sss);     
            }
            qulonglong recordid = rr.value(0).toLongLong();
            
            QTreeWidgetItem *it;
            if (parent){
              it = new QTreeWidgetItem(parent, l);
            } else {
              it = new QTreeWidgetItem(tree, l);
            }
            it->setData(0, Qt::UserRole, QVariant(recordid)); 
            it->setHidden(false);

          } while (rr.next());
        }
      }

  } else {

    if (!sWhere.isEmpty()) sWhere = " WHERE " + sWhere;

    QString ss = groups.at(nCurrent);

    QString k = "SELECT " + ss + " FROM " + sTable + sWhere + " GROUP BY " + ss;

   // tree->headerItem()->setText(nCurrent, ss);    

    if (rr.exec(k)){
      if (rr.first()){
        QSqlRecord r = rr.record();

        do {                    
          
          QString value = rr.value(0).toString();

          QTreeWidgetItem *it;
          if (parent){
            it = new QTreeWidgetItem(parent, QStringList(value));
          } else {
            it = new QTreeWidgetItem(tree, QStringList(value));
          }          
          it->setHidden(false);

          switch(r.field(0).type()){
            case QVariant::Bool:
              break;
            case QVariant::Date: 
              value = value.isEmpty() ? "NULL" : "'" + value + "'";
              break;
            case QVariant::Time: 
              value = value.isEmpty() ? "NULL" : "'" + value + "'";
              break;
            case QVariant::Double:
              value = value.isEmpty() ? "0" : value;
              break;
            case QVariant::UInt:
            case QVariant::ULongLong:
            case QVariant::LongLong:
            case QVariant::Int:
              value = value.isEmpty() ? "0" : value;
              break;
            case QVariant::String: 
              value = "'" + value + "'";
              break;
            default:
              value = value.isEmpty() ? "0" : value;
              break;
          }

          values[nCurrent] = value;

          fillWithSQLForTreeView(tree, it, sTable, sSQL, groups, values, nCurrent + 1);

        } while (rr.next());
      }
    }
  }
  
}

#endif

void _tab::resizeEvent ( QResizeEvent *e)
{  

//  if (autoMask()) updateMask();
    
  QSize k = e->size();
#ifdef IDE
  tb->setGeometry(tb->x(), tb->y(), k.width(), 25);
#else
  tb->setGeometry(tb->x(), tb->y(), k.width(), k.height());
#endif

  QSize size = e->size();
  int w = size.width();
  int h = size.height();

  QString sName = GETPROPERTY_Name();
  int w2 = GETPROPERTY_Width();
  int h2 = GETPROPERTY_Height();

#ifdef RUN
  _form *f = qobject_cast<_form *>(parent());
#else
  _form *f = qobject_cast<_form *>(parent());
#endif

  #define SWITCH6 f->controlType(c)

  QWidget *c = 0;
  if (f && f->firstControl(&c)){
    do {

      QString sParentControl = "";

      #define SWITCH GETPROPERTY_ParentControl();      
      #define SWITCH3 sParentControl
      #include "_form_property_switch.h"   
      #undef SWITCH3

      if (sParentControl == sName){
        
        QString sLayout = "";

        #define SWITCH GETPROPERTY_Layout();      
        #define SWITCH3 sLayout
        #include "_form_property_switch.h"   
        #undef SWITCH3

        if (sLayout.contains("RelativeX", Qt::CaseInsensitive)){          

          #define SWITCH SETPROPERTY_X(c->x() + w - w2);
          #include "_form_property_switch.h"      

        } else if (sLayout.contains("RelativeWidth", Qt::CaseInsensitive)){          

          int n = c->width() + w - w2;
          int n2 = c->minimumWidth();
          if (n < n2 && n2 > 0) n = n2;

          #define SWITCH SETPROPERTY_Width(n);         
          #include "_form_property_switch.h"      

        }

        if (sLayout.contains("RelativeY", Qt::CaseInsensitive)){          

          #define SWITCH SETPROPERTY_Y(c->height() + h - h2);
          #include "_form_property_switch.h"      

        } else if (sLayout.contains("RelativeHeight", Qt::CaseInsensitive)){          

          int n = c->height() + h - h2;
          int n2 = c->minimumHeight();
          if (n < n2 && n2 > 0) n = n2;

          #define SWITCH SETPROPERTY_Height(n);
          #include "_form_property_switch.h"      


        }

      }
        
    } while (f->nextControl(&c));
  }

  #undef SWITCH6

#ifdef IDE

    for (int i = 0; i < 8; i++){
      _selectPanels[i]->reorder();
    }

  #ifdef _FRAME
    QString s = title();
    setTitle(s + " "); // WORK AROUND
    setTitle(s);
  #endif

QWidget::resizeEvent(e);

#elif defined(RUN)
#ifdef SUPERCLASS
    QTabWidget::resizeEvent(e);
    { 
      EVENT_OnResize(e->size().width(), e->size().height(), e->oldSize().width(), e->oldSize().height()); 
    }    
#endif
 #endif

}

int _tab::METHOD_AppendTab(const QString & Icon, const QString & Caption)
{
#ifdef IDE

  int n = 0;
  if (!Icon.isEmpty()){

    if (Icon.length() > 200){ // QString contains binary data
      if (Icon.left(200).contains("<svg ", Qt::CaseInsensitive)){
        QString m = Icon;
        m = m.trimmed();
        QSvgWidget w(0);
        w.resize(width(), height());
        QSvgRenderer *r = w.renderer();
        if (r->load(m.toLatin1())){
          QPixmap p(width(), height());
          QPainter painter(&p);
          r->render(&painter);
          n = tb->addTab(QIcon(p), Caption);
        }
      } else {
         QPixmap p; p.loadFromData(Icon.toLatin1());
         n = tb->addTab(QIcon(p), Caption);
      }
    } else {  
      n = tb->addTab(QIcon(loadPixmap(Icon)), Caption);
    }
  } else {
    n = tb->addTab(Caption);
  }
  tb->repaint();

  return n;
#else
  tb->setUsesScrollButtons(true);

  QWidget *w = new QWidget();
 
  int ww = GETPROPERTY_Width();
  int hh = GETPROPERTY_Height();

  tb->setFixedSize(ww, hh);

  int n = 0;
  if (!Icon.isEmpty()){

    if (Icon.length() > 200){ // QString contains binary data
      if (Icon.left(200).contains("<svg ", Qt::CaseInsensitive)){
        QString m = Icon;
        m = m.trimmed();
        QSvgWidget ww(0);
        ww.resize(width(), height());
        QSvgRenderer *r = ww.renderer();
        if (r->load(m.toLatin1())){
          QPixmap p(width(), height());
          QPainter painter(&p);
          r->render(&painter);
          n = tb->addTab(w, QIcon(p), Caption);
        }
      } else {
         QPixmap p; p.loadFromData(Icon.toLatin1());
         n = tb->addTab(w, QIcon(p), Caption);
      }
    } else {  
      n = tb->addTab(w, QIcon(loadPixmap(Icon)), Caption);
    }
  } else {
    n = tb->addTab(w, Caption);
  }
  tb->repaint();  
 
  return n;

#endif
}

int _tab::METHOD_InsertTab(int Index, const QString & Icon, const QString & Caption)
{
#ifdef IDE

  int n = tb->insertTab(Index, Caption);
  tb->repaint();
  return n;
#else
  // is not called on runtime

  int n = tb->insertTab(Index - 1, new QWidget(), Caption);

  if (!Icon.isEmpty()){

    if (Icon.length() > 200){ // QString contains binary data
      if (Icon.left(200).contains("<svg ", Qt::CaseInsensitive)){
        QString m = Icon;
        m = m.trimmed();
        QSvgWidget w(0);
        w.resize(width(), height());
        QSvgRenderer *r = w.renderer();
        if (r->load(m.toLatin1())){
          QPixmap p(width(), height());
          QPainter painter(&p);
          r->render(&painter);
          tb->setTabIcon(Index - 1, p);
        }
      } else {
         QPixmap p; p.loadFromData(Icon.toLatin1());
         tb->setTabIcon(Index - 1, p);
      }
    } else {  
      tb->setTabIcon(Index - 1, loadPixmap(Icon));
    }    
  }
  tb->repaint();
  return n;
#endif
}

#ifdef RUN
void _serialport::METHOD_ReadLine()
{  

  t_pointer p = 0;
  static char ac[4096];
  nBytesRead = sp.readLine(&ac[0], 4096);
  if (nBytesRead > 0) EXTERN_myInterpreter->pushStackCString(ac); else EXTERN_myInterpreter->pushStackCString(""); 
  
}

void _serialport::METHOD_WriteLine(const QString & s)
{  
  QByteArray a = s.toAscii();  
  nBytesWritten = sp.write(a.data(), a.length());  
}

void _serialport::METHOD_ReadData()
{

  t_boolean boolean_;// = 0;

	t_byte byte_;// = 0;
	t_short short_;// = 0;
  t_integer integer_;// = 0;
	t_integer long_ ;//= 0;

	t_single single_;// = 0;
	t_double double_;// = 0;

  {
    int nType = v[0]->tot_integer();

	  switch (nType){ 
		  case pcode__BOOLEAN: 
        nBytesRead = sp.read((char *) &boolean_, sizeof(boolean_));
        if (nBytesRead > 0) EXTERN_myInterpreter->myStack->pushBoolean(boolean_);
        else EXTERN_myInterpreter->myStack->pushBoolean(false);
        break;

      case pcode__BYTE: 
        nBytesRead = sp.read((char *) &byte_, sizeof(byte_));
        if (nBytesRead > 0) EXTERN_myInterpreter->myStack->pushByte(byte_);
        else EXTERN_myInterpreter->myStack->pushByte(0);
        break;
      case pcode__SHORT: 
        nBytesRead = sp.read((char *) &short_, sizeof(short_));
        if (nBytesRead > 0) EXTERN_myInterpreter->myStack->pushShort(short_);
        else EXTERN_myInterpreter->myStack->pushShort(0);
        break;
      case pcode__INTEGER: 
        nBytesRead = sp.read((char *) &integer_, sizeof(integer_));
        if (nBytesRead > 0) EXTERN_myInterpreter->myStack->pushInteger(integer_);
        else EXTERN_myInterpreter->myStack->pushInteger(0);
        break;
		  case pcode__LONG: 
        nBytesRead = sp.read((char *) &long_, sizeof(long_));
        if (nBytesRead > 0) EXTERN_myInterpreter->myStack->pushLong(long_);
        else EXTERN_myInterpreter->myStack->pushLong(0);
        break;

		  case pcode__SINGLE: 
        nBytesRead = sp.read((char *) &single_, sizeof(single_));
        if (nBytesRead > 0) EXTERN_myInterpreter->myStack->pushSingle(single_);
        else EXTERN_myInterpreter->myStack->pushSingle(0);
        break;
      case pcode__DOUBLE: 
        nBytesRead = sp.read((char *) &double_, sizeof(double_));
        if (nBytesRead > 0) EXTERN_myInterpreter->myStack->pushDouble(double_);
        else EXTERN_myInterpreter->myStack->pushDouble(0);
        break;

      default:
        EXTERN_myInterpreter->pcodeError("wrong datatype on stack");
        break;
    }  

  }

}

void _serialport::METHOD_WriteData()
{
  t_boolean boolean_;// = 0;

  t_byte byte_;// = 0;
	t_short short_;// = 0;
  t_integer integer_;// = 0;
	t_integer long_ ;//= 0;

	t_single single_;// = 0;
	t_double double_;// = 0;

  switch (v[0]->pcodeType){ 
		case pcode__BOOLEAN: 
      boolean_ = v[0]->tot_boolean();//EXTERN_myInterpreter->myStack->popBoolean(); 
      nBytesWritten = sp.write((char *) &boolean_, sizeof(boolean_));
      break;

      /*
    case pcode__STRING:
			string_ = v[0]->tot_string();//EXTERN_myInterpreter->myStack->popBoolean(); 
      nBytesWritten = sp.write((char *) string_, strlen(string_));
      if (EXTERN_myInterpreter->gnestatics[0]) EXTERN_myInterpreter->estatics->undeclare(EXTERN_myInterpreter->gnestatics[0]);
			break;*/
      /*
		case pcode__ESTRING:
			nestatics = EXTERN_myInterpreter->myStack->popStringId();
			string_ = EXTERN_myInterpreter->estatics->getString(nestatics, 0);				 
      nBytesWritten = sp.write((char *) string_, strlen(string_));
			break;
*/
    case pcode__BYTE: 
      byte_ = v[0]->tot_integer();//EXTERN_myInterpreter->myStack->popByte(); 
      nBytesWritten = sp.write((char *) &byte_, sizeof(byte_));
      break;
    case pcode__SHORT: 
      short_ = v[0]->tot_integer();//EXTERN_myInterpreter->myStack->popShort(); 
      nBytesWritten = sp.write((char *) &short_, sizeof(short_));
      break;
    case pcode__INTEGER: 
      integer_ = v[0]->tot_integer();//EXTERN_myInterpreter->myStack->popInteger(); 
      nBytesWritten = sp.write((char *) &integer_, sizeof(integer_));
      break;
		case pcode__LONG: 
      long_ = v[0]->tot_integer();//EXTERN_myInterpreter->myStack->popLong(); 
      nBytesWritten = sp.write((char *) &long_, sizeof(long_));
      break;

		case pcode__SINGLE: 
      single_ = v[0]->tot_double();//EXTERN_myInterpreter->myStack->popSingle();   
      nBytesWritten = sp.write((char *) &single_, sizeof(single_));
      break;
    case pcode__DOUBLE: 
      double_ = v[0]->tot_double();//EXTERN_myInterpreter->myStack->popDouble(); 
      nBytesWritten = sp.write((char *) &double_, sizeof(double_));
      break;

    default:
      EXTERN_myInterpreter->pcodeError("wrong datatype on stack");
      break;
  }  

}

#endif


void _SETPROPERTY_X(_form *my_form, QWidget *w, int n)
{   
  int m = 0;
#ifdef IDE
  if (my_form && my_form->XScrollBar) m = my_form->XScrollBar->value();
#endif
  w->move(n - m, w->y());
}

void _SETPROPERTY_Y(_form *my_form, QWidget *w, int n)
{ 
  int m = 0;
#ifdef IDE
  if (my_form && my_form->YScrollBar) m = my_form->YScrollBar->value();
#endif
  w->move(w->x(), n - m);
}

int my_form_XScrollBar_value(_form *my_form)
{
#ifdef IDE
  if (my_form && my_form->XScrollBar) return my_form->XScrollBar->value();
#else
  return my_form->horizontalScrollBar()->value();
#endif
  return 0;
}



void setVisibleToolBar(bool visible, QWidget *child, QWidget *parent)
{
  QObjectList it = parent->children(); // iterate over the children
  QObject *o;
  for (int q = 0; q < it.size(); q++){
    o = it.at(q);
    if (o == child){
      QList<QAction *>a = parent->actions(); 

      QAction *my_qaction = 0;

      foreach(QAction *dd, a){
        if (((QToolBar *) parent)->widgetForAction(dd) == child){
          my_qaction = dd;
          break;
        }
      }

      if (my_qaction){
        my_qaction->setVisible(visible);
        my_qaction->setEnabled(true);
      }
    }
    }
}

bool setMyMovie(QWidget *control, QMovie **movie, QByteArray **moviea, QBuffer **movieb, QString n)
{

   if (!(n.contains("/") || n.contains("\\"))){    
     t_integer nn = 0;
#ifdef RUN
     t_pointer pp = loadProjectFile(n, &nn);
#endif
#ifdef IDE
  if (!(n.contains("/") || n.contains("\\"))){
    n = my_form_getProjectPath(0) + "/" + n;    
  }
  QFile file(n);
  void *pp = 0;
  if (file.open(QIODevice::ReadOnly)){
    QByteArray aa = file.readAll();
    nn = aa.size();
    pp = aa.data();
    file.close();
  }
#endif
     if (pp != 0){
       int nCurrentFrameNumber = 0;
       if (*movie){
         nCurrentFrameNumber  = (*movie)->currentFrameNumber();
         delete *movie; 
       }
       if (*moviea) delete *moviea; if (*movieb) delete *movieb;
       *moviea = new QByteArray((const char *) pp, nn);
       *movieb = new QBuffer(*moviea); (*movieb)->open(QIODevice::ReadOnly);
       *movie = new QMovie(*movieb);
       if (control && qobject_cast<QLabel *>(control)){
         (*movie)->setScaledSize(control->size());
       } else if (control && qobject_cast<QPushButton *>(control)){
         (*movie)->jumpToFrame(0);
         QPixmap p = (*movie)->currentPixmap();
         (*movie)->jumpToFrame(-1);
         if (!p.isNull()){
           ((QPushButton *)control)->setIconSize(p.size());         
         }
       } else {
         (*movie)->setScaledSize(QSize(32, 32));
       }
       (*movie)->jumpToFrame(nCurrentFrameNumber);     

     }
   } else {
     if (*movie) delete *movie;
     *movie = new QMovie(n);
     if (control && qobject_cast<QLabel *>(control)){
       (*movie)->setScaledSize(control->size());
     } else if (control && qobject_cast<QPushButton *>(control)){
         (*movie)->jumpToFrame(0);
         QPixmap p = (*movie)->currentPixmap();
         (*movie)->jumpToFrame(-1);
         if (!p.isNull()){
           ((QPushButton *)control)->setIconSize(p.size());         
         }
     } else {
       (*movie)->setScaledSize(QSize(32, 32));
     }
   }

   if ((*movie)->isValid()){
      return true;
     
   }
   return false;
}

#ifdef RUN
void _menubaritem::frameChanged(int)
{
 
    for (int i = 0; i < 1000; i++){
      if (i % 2 == 0){
        if (my_qaction) my_qaction->setIcon(QIcon("c:\\fish3.gif"));
      } else {
        if (my_qaction) my_qaction->setIcon(QIcon("c:\\3.gif"));
      }
    }
  
}
#endif


void my_form_newUndoRedo(_form *f)
{
#ifdef IDE
  f->newUndoRedo();
#endif
}


#ifdef RUN
_strings *_dir::FindFile(QString Path, QString NameFilter, QStringList NameFilter2, QString Filter, QString Sorting, bool bRecursive, bool bRecursiveCall, bool bbb)
{
  int i = 0;

  bool b = bbb;
  if (bRecursive && !Filter.contains("AllDirs", Qt::CaseInsensitive)){
    b = true;
    Filter += ";AllDirs;Files";
  }

  if (b == false && Filter.contains("NoFilter", Qt::CaseInsensitive)){
    i = QDir::NoFilter;
  } else {

    if (Filter.contains("AllDirs", Qt::CaseInsensitive)) i |= QDir::AllDirs;
    else if (Filter.contains("Dirs", Qt::CaseInsensitive)) i |= QDir::Dirs;

    if (Filter.contains("Files", Qt::CaseInsensitive)) i |= QDir::Files;
    if (Filter.contains("Drives", Qt::CaseInsensitive)) i |= QDir::Drives;
    if (Filter.contains("NoSymLinks", Qt::CaseInsensitive)) i |= QDir::NoSymLinks;
    if (Filter.contains("NoDotAndDotDot", Qt::CaseInsensitive)) i |= QDir::NoDotAndDotDot;
    if (Filter.contains("AllEntries", Qt::CaseInsensitive)) i |= QDir::AllEntries;
    if (Filter.contains("Readable", Qt::CaseInsensitive)) i |= QDir::Readable;
    if (Filter.contains("Writable", Qt::CaseInsensitive)) i |= QDir::Writable;
    if (Filter.contains("Executable", Qt::CaseInsensitive)) i |= QDir::Executable;
    if (Filter.contains("Modified", Qt::CaseInsensitive)) i |= QDir::Modified;
    if (Filter.contains("Hidden", Qt::CaseInsensitive)){
      i |= QDir::Hidden;
    }
    if (Filter.contains("System", Qt::CaseInsensitive)) i |= QDir::System;
    if (Filter.contains("CaseSensitive", Qt::CaseInsensitive)) i |= QDir::CaseSensitive;
  }

  
  int i2 = 0;

  if (Sorting.contains("NoSort", Qt::CaseInsensitive)){
    i2 = QDir::NoSort;
  } else {

    if (Sorting.contains("Name", Qt::CaseInsensitive)) i |= QDir::Name;
    if (Sorting.contains("Time", Qt::CaseInsensitive)) i |= QDir::Time;
    if (Sorting.contains("Size", Qt::CaseInsensitive)) i |= QDir::Size;
    if (Sorting.contains("Type", Qt::CaseInsensitive)) i |= QDir::Type;
    if (Sorting.contains("Unsorted", Qt::CaseInsensitive)) i |= QDir::Unsorted;
    if (Sorting.contains("DirsFirst", Qt::CaseInsensitive)) i |= QDir::DirsFirst;
    if (Sorting.contains("DirsLast", Qt::CaseInsensitive)) i |= QDir::DirsLast;
    if (Sorting.contains("Reversed", Qt::CaseInsensitive)) i |= QDir::Reversed;
    if (Sorting.contains("IgnoreCase", Qt::CaseInsensitive)) i |= QDir::IgnoreCase;
    if (Sorting.contains("LocaleAware", Qt::CaseInsensitive)) i |= QDir::LocaleAware;
  }

  
  QFileInfoList l;

  if (bRecursiveCall){
    QDir dir;

    dir.setPath(Path);
    
    if (NameFilter.isEmpty()){
      l = dir.entryInfoList(NameFilter2, (QDir::Filters) i, (QDir::SortFlags) i2);
    } else {
      l = dir.entryInfoList(QStringList(NameFilter), (QDir::Filters) i, (QDir::SortFlags) i2);
    }

  } else {

    dir.setPath(Path);
    
    if (NameFilter.isEmpty()){
      l = dir.entryInfoList(NameFilter2, (QDir::Filters) i, (QDir::SortFlags) i2);
    } else {
      l = dir.entryInfoList(QStringList(NameFilter), (QDir::Filters) i, (QDir::SortFlags) i2);
    }

  }

  _strings *ss = new _strings();

  int size = l.size();

  foreach(QFileInfo f, l){

    bool bb = bRecursive && f.isDir();

    if (!bb || (bb && b == false)){
      ss->METHOD_Append(f.absoluteFilePath());
    }

    if (bb){

		  if (f.fileName() == "." || f.fileName() == ".."){
		      ; // nothing
		  } else {

        _strings *ss2 = FindFile(f.absoluteFilePath(), NameFilter, NameFilter2, Filter, Sorting, bRecursive, true, b);
        int n = ss2->qstringlist.size();
        ss->qstringlist << ss2->qstringlist;
        delete ss2;
      }
    }

  }
  return ss;
}

t_boolean _file::METHOD_SetWriteable(QString FileName, t_boolean Writable, QString Who)
{  
  qfile.setFileName(FileName);

  QFile::Permissions p = qfile.permissions();

  if (Who.isEmpty() || Who.contains("User", Qt::CaseInsensitive)){
    if (Writable){
      return qfile.setPermissions(p | QFile::WriteUser);
    } else {
      return qfile.setPermissions(QFile::WriteUser);
      int n = p;
      int n2 = ((t_integer) QFile::WriteUser) ^ 0xffffff;
      n = n & n2;
      return qfile.setPermissions((QFile::Permissions) n);
    }
  } else if (Who.contains("Owner", Qt::CaseInsensitive)){
  } else if (Who.contains("Group", Qt::CaseInsensitive)){
  } else if (Who.contains("Other", Qt::CaseInsensitive)){
  }
}

void _array::METHOD_Set(QString Key, QString Key2, QString Key3, QString Key4, QString Key5, QString Key6, QString Key7, QString Key8, t_variant Value)
{
  
  QString sKey = Key + Key2 + Key3 + Key4 + Key5 + Key6 + Key7 + Key8;

  qmap[sKey] = Value;
  t_variant vv = qmap[sKey];
  return;
/*
// t{"a", "Person", "Name"} = "Julie Hepp"
 
  keys[0][Key] = Key2;
  if (Key2.isEmpty()){
    keys[1][Key + Key2] = sKey; 
  } else {
    keys[1][Key + Key2] = Key3;
    if (Key3.isEmpty()){
      keys[2][Key + Key2 + Key3] = sKey; 
    } else {
      keys[2][Key + Key2 + Key3] = Key4;
      if (Key4.isEmpty()){
        keys[3][Key + Key2 + Key3 + Key4] = sKey; 
      } else {
        keys[3][Key + Key2 + Key3 + Key4] = Key5;
        if (Key5.isEmpty()){
          keys[4][Key + Key2 + Key3 + Key4 + Key5] = sKey; 
        } else {
          keys[4][Key + Key2 + Key3 + Key4 + Key5] = Key6;
          if (Key6.isEmpty()){
            keys[5][Key + Key2 + Key3 + Key4 + Key5 + Key6] = sKey; 
          } else {
            keys[5][Key + Key2 + Key3 + Key4 + Key5 + Key6] = Key7;
            if (Key7.isEmpty()){
              keys[6][Key + Key2 + Key3 + Key4 + Key5 + Key6 + Key7] = sKey; 
            } else {
              keys[6][Key + Key2 + Key3 + Key4 + Key5 + Key6 + Key7] = Key8;
              keys[7][Key + Key2 + Key3 + Key4 + Key5 + Key6 + Key7 + Key8] = sKey;
            }
          }
        }
      }
    }
  }

  */
}

void _bits::METHOD_SetByte(t_byte Value)
{  
  a.clear();
  a.resize(8);

  a[0] = Value & 1;
  a[1] = Value & 2;
  a[2] = Value & 4;
  a[3] = Value & 8;
  a[4] = Value & 16;
  a[5] = Value & 32;
  a[6] = Value & 64;
  a[7] = Value & 128;  
}

t_byte _bits::METHOD_Byte()
{
  t_byte c = 0;

  c |= a[0] << 0;
  c |= a[1] << 1;
  c |= a[2] << 2;
  c |= a[3] << 3;
  c |= a[4] << 4;
  c |= a[5] << 5;
  c |= a[6] << 6;
  c |= a[7] << 7;

  return c;
}



_dbcondialog::_dbcondialog(QWidget* _parent) : QDialog(_parent)
{
  bOk_dbcondialog = false;

  setAttribute(Qt::WA_DeleteOnClose);
  setWindowFlags(windowFlags() | Qt::Tool);

  setWindowTitle(tr("Database Connection"));
  setModal(true);     

  QVBoxLayout *j = new QVBoxLayout();
  setLayout(j);

  bool t = false;

  QLabel *l;
  l = new QLabel(tr("Properties:")); j->addWidget(l);
  {
    QFont f = l->font();
    f.setBold(true);
    l->setFont(f);
  }


  QGridLayout *g = new QGridLayout();
  g->setColumnStretch(1, 10);

  j->addLayout(g);
  int y = 0;


  QComboBox *d;

  l = new QLabel(tr("db driver:")); g->addWidget(l, y, 0);
  dbdriver = d = new QComboBox(); g->addWidget(d, y++, 1);
  
  d->addItem("");

  QStringList drivers = QSqlDatabase::drivers();
  for (int i = 0; i < drivers.size(); ++i){
    QString k = drivers.at(i);
    if (!k.right(1).at(0).isDigit()){ // filter out old-versions marked with digits at the end
      d->addItem(k);
    }
  }
  QString s = p_dbdriver;

  int n = d->findText(s);
  if (n >= 0){
    d->setCurrentIndex(n);
  }

  l = new QLabel(tr("db host:")); g->addWidget(l, y, 0);
  dbhost = d = new QComboBox(); g->addWidget(d, y++, 1);
  d->setEditable(true);
  d->addItem(tr("localhost"));


  l = new QLabel(tr("db port:")); g->addWidget(l, y, 0);
  dbport = d = new QComboBox(); g->addWidget(d, y++, 1);
  d->setEditable(true);

  l = new QLabel(tr("db name:")); g->addWidget(l, y, 0);
  dbname = d = new QComboBox(); g->addWidget(d, y++, 1);
  d->setEditable(true);


  l = new QLabel(tr("db user:")); g->addWidget(l, y, 0);
  dbuser = d = new QComboBox(); g->addWidget(d, y++, 1);
  d->setEditable(true);


  l = new QLabel(tr("user password:")); g->addWidget(l, y, 0);
  dbuserpassword = d = new QComboBox(); g->addWidget(d, y++, 1);
  d->setEditable(true);

  l = new QLabel(tr("connect options:")); g->addWidget(l, y, 0);
  dbconnectoptions = d = new QComboBox(); g->addWidget(d, y++, 1);
  d->setEditable(true);
  


  QFrame *ff = new QFrame(); ff->setFrameShape(QFrame::HLine); ff->setFrameShadow(QFrame::Sunken); j->addWidget(ff);

  
    
  QWidget *f = new QWidget(); j->addWidget(f);
  QHBoxLayout *fj = new QHBoxLayout();
  f->setLayout(fj);

  
  QPushButton *p;

  f = new QWidget(); j->addWidget(f);
  fj = new QHBoxLayout();
  f->setLayout(fj);

  p = new QPushButton(tr("&OK"), f); fj->addWidget(p);
  connect(p, SIGNAL( clicked(bool) ), this, SLOT(ok()) );

  p = new QPushButton(tr("&Cancel"), f); fj->addWidget(p);
  connect(p, SIGNAL( clicked(bool) ), this, SLOT(cancel()) );



  if (p_dbuser.length()){
    dbuser->setEditText (p_dbuser);
  }

  if (p_dbname.length()){
    dbname->setEditText (p_dbname);
  }

  if (p_dbdriver.length()){
    dbdriver->setEditText (p_dbdriver);
  }

  if (p_dbhost.length()){
    dbhost->setEditText (p_dbhost);
  }

  if (p_dbport.length()){
    dbport->setEditText (p_dbport);
  }

  if (p_dbuserpassword.length()){
    dbuserpassword->setEditText (p_dbuserpassword);
  }

  if (p_dbconnectoptions.length()){
    dbconnectoptions->setEditText (p_dbconnectoptions);
  }
  move(QApplication::desktop()->width() / 2 - 400 / 2, QApplication::desktop()->height() / 2 - sizeHint().height() / 2);
  resize(400, sizeHint().height());

  show();
  qApp->setActiveWindow(this);
  this-exec();
}

void _dbcondialog::ok()
{  
  p_dbdriver = dbdriver->currentText();
  p_dbhost = dbhost->currentText();
  p_dbname = dbname->currentText();
  p_dbuser = dbuser->currentText();
  p_dbuserpassword = dbuserpassword->currentText();
  p_dbport = dbport->currentText();
  p_dbconnectoptions = dbconnectoptions->currentText();

  bOk_dbcondialog = true;

  accept();
}

void _dbcondialog::cancel()
{
  close();
}

t_boolean _database::METHOD_Exists(QString Driver, QString Name, QString User, QString Password, QString Host, QString Options, QString Port)
{
  if (!Driver.isEmpty()){
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase(Driver, "kbasic_internal");
    db.setHostName(Host);
    db.setDatabaseName(Name);
    db.setUserName(User);
    db.setPassword(Password);
    if (!Port.isEmpty()) db.setPort(Port.toInt());
    db.setConnectOptions(Options);
    if (db.open()){    
              
      // ODBC  GetDataSources oder geht nicht
      /*
  SQLite 	geht nicht, weil db automatisch angelegt wird   PRAGMA database_list; 
        */

      QString sSQL = "";
      if (Driver.contains("MYSQL", Qt::CaseInsensitive)){
        sSQL = "SHOW DATABASES;";
      } else if (Driver.contains("PSQL", Qt::CaseInsensitive)){
        sSQL = "SELECT * FROM pg_database;";
      } else if (Driver.contains("SQLITE", Qt::CaseInsensitive)){
        QSqlDatabase::removeDatabase("kbasic_internal");
        return false;
      } else {
        QSqlDatabase::removeDatabase("kbasic_internal");
        return false;
      }

      QSqlQuery rr(db);
      if (rr.exec(sSQL)){ sLastSQLError = ""; sLastSQLCommands[Name] += sSQL + "\n";
        if (rr.first()){
          do {
            QSqlRecord r = rr.record();
            QString k = rr.value(0).toString();
            if (Name.compare(k, Qt::CaseInsensitive) == 0){
              QSqlDatabase::removeDatabase("kbasic_internal");
              return true;
            }
          } while (rr.next());
        }
      } else {
        sLastSQLError = rr.lastError().text();
        sLastSQLCommandFailed[Name] = sSQL;
      }

      QSqlDatabase::removeDatabase("kbasic_internal");
      return false;
    }
    QSqlDatabase::removeDatabase("kbasic_internal");
  }
  return false;
}
  
t_boolean _database::METHOD_SetCurrentDatabase(QString Name)
{
  if (databases.contains(Name)){
    CurrentDatabase = databases[Name];
    return true;
  }
  return false;
}

QString _database::METHOD_CurrentDatabase()
{
  return CurrentDatabase.databaseName();
}

t_boolean _database::METHOD_OpenSQLite(QString Name)
{
  if (!databases.contains(Name)){
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE", Name);
    db.setDatabaseName(Name);
    if (db.open()){    
      databases[Name] = db;
      CurrentDatabase = db;
      return true;
    } else {
      QSqlDatabase::removeDatabase(Name);
    }
  }

  return false;
}

t_boolean _database::METHOD_Open(QString Driver, QString Name, QString User, QString Password)
{
  if (!Driver.isEmpty() && !databases.contains(Name)){
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase(Driver, Name);
    db.setHostName("localhost");
    db.setDatabaseName(Name);
    db.setUserName(User);
    db.setPassword(Password);
    if (db.open()){    
      databases[Name] = db;
      CurrentDatabase = db;
      return true;
    } else {
      QSqlDatabase::removeDatabase(Name);
    }
  }

  return false;
}

t_boolean _database::METHOD_Open(QString Driver, QString Name, QString User, QString Password, QString Host, QString Options, QString Port)
{
  if (!Driver.isEmpty() && !databases.contains(Name)){
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase(Driver, Name);
    db.setHostName(Host);
    db.setDatabaseName(Name);
    db.setUserName(User);
    db.setPassword(Password);
    if (!Port.isEmpty()) db.setPort(Port.toInt());
    db.setConnectOptions(Options);
    if (db.open()){    
      databases[Name] = db;
      CurrentDatabase = db;
      return true;
    } else {       
      QSqlDatabase::removeDatabase(Name);
    }
  }

  return false;
}

t_boolean _database::METHOD_Close(QString Name)
{
  if (Name.isEmpty()){
    CurrentDatabase.close();    
    QSqlDatabase::removeDatabase(CurrentDatabase.databaseName());
    sLastSQLCommands[Name] = "";
    sLastSQLCommandFailed[Name] = "";
    return true;
  }
  if (databases.contains(Name)){
    if (CurrentDatabase.databaseName() == databases[Name].databaseName()){
    }
    databases[Name].close();    
    QSqlDatabase::removeDatabase(Name);
    databases.remove(Name);
    sLastSQLCommands[Name] = "";
    sLastSQLCommandFailed[Name] = "";
    return true;
  }
  return false;
}

t_boolean _database::METHOD_IsOpen(QString Name)
{
  if (Name.isEmpty()){
    return CurrentDatabase.isOpen();
  }
  if (databases.contains(Name)){    
    return databases[Name].isOpen();
  }
  return false;
}

t_boolean _database::METHOD_Create(QString Driver, QString Name, QString User, QString Password, QString Host, QString Options, QString Port)
{
  /*
  odbc: geht nicht
  sqlite: geht nicht (automatisch erstellt)
  */
  if (!Driver.isEmpty()){
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase(Driver, "kbasic_internal");
    db.setHostName(Host);

    db.setUserName(User);
    db.setPassword(Password);
    if (!Port.isEmpty()) db.setPort(Port.toInt());
    db.setConnectOptions(Options);
    if (db.open()){  
      QString sSQL = "";
      if (Driver.contains("MYSQL", Qt::CaseInsensitive)){
        sSQL = "CREATE DATABASE " + Name + ";";
      } else if (Driver.contains("PSQL", Qt::CaseInsensitive)){
        sSQL = "CREATE DATABASE " + Name + "ENCODING='utf-8';";
      } else {
        QSqlDatabase::removeDatabase("kbasic_internal");
        return false;
      }
      QSqlQuery rr(db);
      if (rr.exec(sSQL)){ sLastSQLError = ""; sLastSQLCommands[Name] += sSQL + "\n";
        QSqlDatabase::removeDatabase("kbasic_internal");
        return true;
      } else {
        sLastSQLError = rr.lastError().text();
        sLastSQLCommandFailed[Name] = sSQL;
      }
    }
    QSqlDatabase::removeDatabase("kbasic_internal");
  }
  return false;
}

QString _database::METHOD_TestConnection(QString Driver, QString User, QString Password, QString Host, QString Options, QString Port)
{
  if (!Driver.isEmpty()){
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase(Driver, "kbasic_internal");
    db.setHostName(Host);
    db.setUserName(User);
    db.setPassword(Password);
    if (!Port.isEmpty()) db.setPort(Port.toInt());
    db.setConnectOptions(Options);
    if (!db.open()){ 
      QSqlDatabase::removeDatabase("kbasic_internal");
      return db.lastError().text();
    }
    QSqlDatabase::removeDatabase("kbasic_internal");
    return "";
  }
  return "Driver not selected";
}

t_boolean _database::METHOD_Clear(QString Driver, QString Name, QString User, QString Password, QString Host, QString Options, QString Port)
{
  if (!Driver.isEmpty()){
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase(Driver, "kbasic_internal");
    db.setHostName(Host);
    db.setDatabaseName(Name);
    db.setUserName(User);
    db.setPassword(Password);
    if (!Port.isEmpty()) db.setPort(Port.toInt());
    db.setConnectOptions(Options);
    if (db.open()){  
      foreach(QString s, db.tables(QSql::Tables)){
        QString sSQL = "DROP TABLE " + s + ";";
        QSqlQuery rr(db);
        sLastSQLError = "";
        if (!rr.exec(sSQL)){
          sLastSQLError = rr.lastError().text();
          sLastSQLCommandFailed[Name] = sSQL;
          return false;
        } else {
          sLastSQLCommands[Name] += sSQL + "\n";
        }
      }
      QSqlDatabase::removeDatabase("kbasic_internal");
      return true;
    }
    QSqlDatabase::removeDatabase("kbasic_internal");
  }
  return false;
}

t_boolean _database::METHOD_Drop(QString Driver, QString Name, QString User, QString Password, QString Host, QString Options, QString Port)
{
  /*
  odbc: geht nicht
  sqlite: geht nicht
  */

  if (!Driver.isEmpty()){
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase(Driver, "kbasic_internal");
    db.setHostName(Host);
    db.setDatabaseName(Name);
    db.setUserName(User);
    db.setPassword(Password);
    if (!Port.isEmpty()) db.setPort(Port.toInt());
    db.setConnectOptions(Options);
    if (db.open()){  

      QString sSQL = "";
      if (Driver.contains("MYSQL", Qt::CaseInsensitive)){
        sSQL = "DROP DATABASE " + Name + ";";
      } else if (Driver.contains("PSQL", Qt::CaseInsensitive)){
        sSQL = "DROP DATABASE " + Name + ";";
      } else {
        QSqlDatabase::removeDatabase("kbasic_internal");
        return false;
      }

      QSqlQuery rr(db);
      if (rr.exec(sSQL)){ sLastSQLError = ""; sLastSQLCommands[Name] += sSQL + "\n";
        QSqlDatabase::removeDatabase("kbasic_internal");
        return true;
      } else {
        sLastSQLError = rr.lastError().text();
        sLastSQLCommandFailed[Name] = sSQL;
      }
    }
    QSqlDatabase::removeDatabase("kbasic_internal");    
  }

  return false;
}

t_boolean _database::METHOD_Copy(QString Source, QString Destination)
{
  // wird nicht unterstützt
  return false;
}

QString _database::METHOD_LastSQLError(QString Name)
{
  if (Name.isEmpty()){
    QString k = CurrentDatabase.lastError().text().trimmed();    
    if (!k.isEmpty()) return k;
    k = sLastSQLError;
    return k;
  }
  if (databases.contains(Name)){  
    QString k = databases[Name].lastError().text().trimmed();    
    if (!k.isEmpty()) return k;
    k = sLastSQLError;
    return k;
  }
  return "";
}

QString _database::METHOD_LastSQLCommands(QString Name)
{
  if (Name.isEmpty()){
    QString k = sLastSQLCommands[CurrentDatabase.databaseName()];
    sLastSQLCommands[CurrentDatabase.databaseName()] = "";
    return k;
  }
  if (databases.contains(Name)){  
    QString k = sLastSQLCommands[Name];
    sLastSQLCommands[Name] = "";
    return k;
  }
  return "";
}

QString _database::METHOD_LastSQLCommandFailed(QString Name)
{
  if (Name.isEmpty()){
    QString k = sLastSQLCommandFailed[CurrentDatabase.databaseName()];
    sLastSQLCommandFailed[CurrentDatabase.databaseName()] = "";
    return k;
  }
  if (databases.contains(Name)){  
    QString k = sLastSQLCommandFailed[Name];
    sLastSQLCommandFailed[Name] = "";
    return k;
  }
  return "";
}

t_boolean _database::METHOD_IsTransactionSupported(QString Name)
{
  if (Name.isEmpty()){
    return CurrentDatabase.driver()->hasFeature(QSqlDriver::Transactions);
  }
  if (databases.contains(Name)){    
    return databases[Name].driver()->hasFeature(QSqlDriver::Transactions);
  }
  return false;
}

t_boolean _database::METHOD_Transaction(QString Name)
{
  if (Name.isEmpty()){
    return CurrentDatabase.transaction();
  }
  if (databases.contains(Name)){    
    return databases[Name].transaction();
  }
  return false;
}

t_boolean _database::METHOD_Commit(QString Name)
{
  if (Name.isEmpty()){
    return CurrentDatabase.commit();
  }
  if (databases.contains(Name)){    
    return databases[Name].commit();
  }
  return false;
}

t_boolean _database::METHOD_Rollback(QString Name)
{
  if (Name.isEmpty()){
    return CurrentDatabase.rollback();
  }
  if (databases.contains(Name)){    
    return databases[Name].rollback();
  }
  return false;
}

_strings *_database::METHOD_Tables(QString Name)
{
  _strings *ss = new _strings();

  if (databases.contains(Name)){    
    foreach(QString s, Name.isEmpty() ? CurrentDatabase.tables(QSql::Tables) : databases[Name].tables(QSql::Tables))
    {
      ss->METHOD_Append(s);
    } 
  }

  return ss;
}

_strings *_database::METHOD_Drivers()
{
  _strings *ss = new _strings();
      
  QStringList drivers = QSqlDatabase::drivers();
  for (int i = 0; i < drivers.size(); i++){
    QString k = drivers.at(i);
    if (!k.right(1).at(0).isDigit()){ // filter out old-versions marked with digits at the end
      ss->METHOD_Append(k);
    }
  }
  
  return ss;
}


t_boolean _table2::METHOD_Exists1(QString Table)
{
  return METHOD_Exists(CurrentDatabase.databaseName(), Table);
}

t_boolean _table2::METHOD_Exists(QString Database, QString Table)
{
  if (databases.contains(Database)){
    foreach(QString s, databases[Database].tables(QSql::Tables))
    {
      if (s.compare(Table, Qt::CaseInsensitive) == 0) return true;
    } 
  }

  return false;
}

t_boolean _table2::METHOD_Create3(QString Table)
{
  return METHOD_Create2(CurrentDatabase.databaseName(), Table);
}

t_boolean _table2::METHOD_Create2(QString Database, QString Table)
{  
  _array *Fields = new _array();

  QString sFields = interpreter_loadFileAsString(Table.endsWith(".kbasic_table") ? Table : (Table + ".kbasic_table"));
  QStringList l = sFields.split(",");
  foreach(QString s, l)
  {
    QString sName = "";
    QString sType = "";
    int n = s.indexOf(" As ");
    sName = s.left(n);
    sType = s.mid(n + 4);

    Fields->METHOD_Set(sName, "", "", "", "", "", "", "", t_variant(&sType));
    t_variant v = Fields->qmap[sName];
    v = v;
  }

  if (METHOD_Create(Database, Table, Fields)){
    return true;
  }
  delete Fields;
  return false;
}

t_boolean _table2::METHOD_Create1(QString Table, _array *Fields)
{
  return METHOD_Create(CurrentDatabase.databaseName(), Table, Fields);
}

t_boolean _table2::METHOD_Create(QString Database, QString Table, _array *Fields)
{
  if (databases.contains(Database)){

    QString sSQL = "";
    QString driver = databases[Database].driver()->handle().typeName();
    QSqlQuery rr(databases[Database]);

    databases[Database].transaction();

    QString sCREATEINDEX = "";
    
    if (driver.contains("MYSQL", Qt::CaseInsensitive)){      
      sCREATEINDEX = "CREATE INDEX " + Table + "_idx_kbrecordid USING btree ON " + Table + " (kbrecordid);";
    } else if (driver.contains("PSQL", Qt::CaseInsensitive)){
      sCREATEINDEX = "CREATE INDEX " + Table + "_idx_kbrecordid ON " + Table + " USING btree (kbrecordid);";
    } else if (driver.contains("SQLITE", Qt::CaseInsensitive)){
      sCREATEINDEX = "CREATE INDEX " + Table + "_idx_kbrecordid ON " + Table + " (kbrecordid);";
    } else if (driver.contains("ODBC", Qt::CaseInsensitive)){
      sCREATEINDEX = "CREATE INDEX " + Table + "_idx_kbrecordid ON " + Table + " USING btree (kbrecordid);";
    } else {
      return false;
    }

    sSQL = "CREATE TABLE " + Table + " (\n";
    sSQL += "\nkbrecordid int NOT NULL,\nCONSTRAINT " + Table + "_kbrecordid PRIMARY KEY (kbrecordid)\n);";

    sLastSQLError = "";
    
    if (!rr.exec(sSQL)){ 
      sLastSQLError = rr.lastError().text();
      sLastSQLCommandFailed[Database] = sSQL;
      databases[Database].rollback();
      return false;
    } else {
      sLastSQLCommands[Database] += sSQL + "\n";
    }

    sSQL = sCREATEINDEX;

    sLastSQLError = "";
    if (!rr.exec(sSQL)){
      sLastSQLError = rr.lastError().text();
      sLastSQLCommandFailed[Database] = sSQL;
      databases[Database].rollback();
      return false;
    } else {
      sLastSQLCommands[Database] += sSQL + "\n";
    }
  

    QMapIterator<QString, t_variant> i(Fields->qmap);

    int n = Fields->qmap.count();

    while (i.hasNext()){
      i.next();

      QString sName = i.key();
      t_variant v = i.value();
      QString sType = *v.toQString();

      if (driver.contains("MYSQL", Qt::CaseInsensitive)){      
        if (sType.contains("Boolean", Qt::CaseInsensitive)){ sType = "BOOLEAN";
        } else if (sType.contains("String", Qt::CaseInsensitive)){ sType = "LONGTEXT";
        } else if (sType.contains("Byte", Qt::CaseInsensitive)){ sType = "SMALLINT";
        } else if (sType.contains("Short", Qt::CaseInsensitive)){ sType = "SMALLINT";
        } else if (sType.contains("Integer", Qt::CaseInsensitive)){ sType = "INT";
        } else if (sType.contains("Long", Qt::CaseInsensitive)){ sType = "BIGINT";
        } else if (sType.contains("Single", Qt::CaseInsensitive)){ sType = "FLOAT";
        } else if (sType.contains("Double", Qt::CaseInsensitive)){ sType = "DOUBLE";
        } else if (sType.contains("Decimal", Qt::CaseInsensitive)){ sType = "DECIMAL(10,4)";
        } else if (sType.contains("Currrency", Qt::CaseInsensitive)){ sType = "DECIMAL(10,4)";
        } else if (sType.contains("Date", Qt::CaseInsensitive)){ sType = "DATETIME";
        } else if (sType.contains("DateTime", Qt::CaseInsensitive)){ sType = "DATETIME";
        } else return false;

      } else if (driver.contains("PSQL", Qt::CaseInsensitive)){
        if (sType.contains("Boolean", Qt::CaseInsensitive)){ sType = "BOOLEAN";
        } else if (sType.contains("String", Qt::CaseInsensitive)){ sType = "TEXT";
        } else if (sType.contains("Byte", Qt::CaseInsensitive)){ sType = "SMALLINT";
        } else if (sType.contains("Short", Qt::CaseInsensitive)){ sType = "SMALLINT";
        } else if (sType.contains("Integer", Qt::CaseInsensitive)){ sType = "INTEGER";
        } else if (sType.contains("Long", Qt::CaseInsensitive)){ sType = "BIGINT";
        } else if (sType.contains("Single", Qt::CaseInsensitive)){ sType = "REAL";
        } else if (sType.contains("Double", Qt::CaseInsensitive)){ sType = "DOUBLE";
        } else if (sType.contains("Decimal", Qt::CaseInsensitive)){ sType = "DECIMAL";
        } else if (sType.contains("Currrency", Qt::CaseInsensitive)){ sType = "DECIMAL";
        } else if (sType.contains("Date", Qt::CaseInsensitive)){ sType = "TIMESTAMP";
        } else if (sType.contains("DateTime", Qt::CaseInsensitive)){ sType = "TIMESTAMP";
        } else return false;

      } else if (driver.contains("SQLITE", Qt::CaseInsensitive)){
        if (sType.contains("Boolean", Qt::CaseInsensitive)){ sType = "INTEGER";
        } else if (sType.contains("String", Qt::CaseInsensitive)){ sType = "TEXT";
        } else if (sType.contains("Byte", Qt::CaseInsensitive)){ sType = "INTEGER";
        } else if (sType.contains("Short", Qt::CaseInsensitive)){ sType = "INTEGER";
        } else if (sType.contains("Integer", Qt::CaseInsensitive)){ sType = "INTEGER";
        } else if (sType.contains("Long", Qt::CaseInsensitive)){ sType = "INTEGER";
        } else if (sType.contains("Single", Qt::CaseInsensitive)){ sType = "REAL";
        } else if (sType.contains("Double", Qt::CaseInsensitive)){ sType = "REAL";
        } else if (sType.contains("Decimal", Qt::CaseInsensitive)){ sType = "TEXT";
        } else if (sType.contains("Currrency", Qt::CaseInsensitive)){ sType = "TEXT";
        } else if (sType.contains("Date", Qt::CaseInsensitive)){ sType = "TEXT";
        } else if (sType.contains("DateTime", Qt::CaseInsensitive)){ sType = "TEXT";
        } else return false;

      } else if (driver.contains("ODBC", Qt::CaseInsensitive)){
        if (sType.contains("Boolean", Qt::CaseInsensitive)){ sType = "SMALLINT";
        } else if (sType.contains("String", Qt::CaseInsensitive)){ sType = "LONGTEXT";
        } else if (sType.contains("Byte", Qt::CaseInsensitive)){ sType = "SMALLINT";
        } else if (sType.contains("Short", Qt::CaseInsensitive)){ sType = "SMALLINT";
        } else if (sType.contains("Integer", Qt::CaseInsensitive)){ sType = "INTEGER";
        } else if (sType.contains("Long", Qt::CaseInsensitive)){ sType = "BIGINT";
        } else if (sType.contains("Single", Qt::CaseInsensitive)){ sType = "REAL";
        } else if (sType.contains("Double", Qt::CaseInsensitive)){ sType = "DOUBLE";
        } else if (sType.contains("Decimal", Qt::CaseInsensitive)){ sType = "DECIMAL";
        } else if (sType.contains("Currrency", Qt::CaseInsensitive)){ sType = "DECIMAL";
        } else if (sType.contains("Date", Qt::CaseInsensitive)){ sType = "TIMESTAMP";
        } else if (sType.contains("DateTime", Qt::CaseInsensitive)){ sType = "TIMESTAMP";
        } else return false;

      } else {
        return false;
      }

      sSQL = "ALTER TABLE " + Table + " ADD " + sName + " " + sType + ";";

      sLastSQLError = "";
      if (!rr.exec(sSQL)){
        sLastSQLError = rr.lastError().text();
        sLastSQLCommandFailed[Database] = sSQL;
        databases[Database].rollback();
        return false;
      } else {
        sLastSQLCommands[Database] += sSQL + "\n";
      }
    }

    databases[Database].commit();

    return true;    

  }

  return false;
}

_strings *_table2::METHOD_FieldNames1(QString Table)
{
  return METHOD_FieldNames(CurrentDatabase.databaseName(), Table);
}

_strings *_table2::METHOD_FieldNames(QString Database, QString Table)
{
  _strings *ss = new _strings();

  if (databases.contains(Database)){

    QString sSQL = "";
    QSqlQuery rr(databases[Database]);

    sSQL = "SELECT * FROM " + Table + ";";

    sLastSQLError = "";    
    if (!rr.exec(sSQL)){
      sLastSQLError = rr.lastError().text();
      sLastSQLCommandFailed[Database] = sSQL;
      return ss;
    } else {
      sLastSQLCommands[Database] += sSQL + "\n";

      QSqlRecord ri = rr.record();
      for (int i = 0; i < ri.count(); i++){
        ss->METHOD_Append(ri.fieldName(i));
      }
    }
    
  }

  return ss;
}

QString _table2::METHOD_PrimaryKeyName1(QString Table)
{
  return METHOD_PrimaryKeyName(CurrentDatabase.databaseName(), Table);
}

QString _table2::METHOD_PrimaryKeyName(QString Database, QString Table)
{
  if (databases.contains(Database)){
    return getPrimary(databases[Database], Table);
  }

  return "kbrecordid";
}

t_boolean _table2::METHOD_Clear1(QString Table)
{
  return METHOD_Clear(CurrentDatabase.databaseName(), Table);
}

t_boolean _table2::METHOD_Clear(QString Database, QString Table)
{
  if (databases.contains(Database)){

    QString sSQL = "";
    QSqlQuery rr(databases[Database]);

    sSQL = "DELETE FROM " + Table + ";";

    sLastSQLError = "";    
    if (!rr.exec(sSQL)){
      sLastSQLError = rr.lastError().text();
      sLastSQLCommandFailed[Database] = sSQL;
      return false;
    } else {
      sLastSQLCommands[Database] += sSQL + "\n";
    }

    return true;
  }

  return false;
}

t_boolean _table2::METHOD_Drop1(QString Table)
{
  return METHOD_Drop(CurrentDatabase.databaseName(), Table);
}

t_boolean _table2::METHOD_Drop(QString Database, QString Table)
{
  if (databases.contains(Database)){

    QString sSQL = "";
    QSqlQuery rr(databases[Database]);

    sSQL = "DROP TABLE " + Table + ";";

    sLastSQLError = "";    
    if (!rr.exec(sSQL)){
      sLastSQLError = rr.lastError().text();
      sLastSQLCommandFailed[Database] = sSQL;
      return false;
    } else {
      sLastSQLCommands[Database] += sSQL + "\n";
    }

    return true;
  }

  return false;
}
/*
t_boolean _table2::METHOD_Copy(QString Database, QString Source, QString Destination)
{
  // not implemented yet
  return false;
}*/


t_boolean _table2::METHOD_Delete1(QString Table, _array *Where)
{
  return METHOD_Delete(CurrentDatabase.databaseName(), Table, Where);
}

t_boolean _table2::METHOD_Delete(QString Database, QString Table, _array *Where)
{
 if (databases.contains(Database)){

    QString sWhere = "";

    QSqlDriver *driver = databases[Database].driver();

    QMapIterator<QString, t_variant> i(Where->qmap);
    int x = 0;
    while (i.hasNext()){
      i.next();
      if (x > 0) sWhere += " AND ";
      x++;

      QString sName = i.key();
      t_variant v = i.value();
      QString sValue = "";

      QSqlField f;

      switch (v.nType){
        case pcode__BOOLEAN:
          f.setValue(QVariant((bool) v.boolean_));
          sValue = driver->formatValue(f);
          break;
        case pcode__SHORT:
        case pcode__BYTE:
        case pcode__INTEGER:
        case pcode__LONG:
          f.setValue(QVariant(v.toLong()));
          sValue = driver->formatValue(f);
          break;
        case pcode__SINGLE:
          f.setValue(QVariant(v.single_));
          sValue = driver->formatValue(f);
          break;
        case pcode__DOUBLE:
          f.setValue(QVariant(v.double_));
          sValue = driver->formatValue(f);
          break;
        case pcode__CURRENCY:
          sValue = *v.toQString();
          break;
        case pcode__DATE:                    
          f.setValue(QVariant(QDateTime(QDate(v.date_.nYear, v.date_.nMonth, v.date_.nDay), QTime(v.date_.nHour, v.date_.nMinute, v.date_.nSecond))));
          sValue = driver->formatValue(f);          
          break;
        default:
          {
            QString k = *v.toQString();
            f.setValue(QVariant(k));
            sValue = driver->formatValue(f);
          }
          break;
      }

      sWhere += sName;
      sWhere += " ";
      sWhere += sValue;

    }

    QString sSQL = "";
    QSqlQuery rr(databases[Database]);

    sSQL = "DELETE FROM " + Table + " WHERE " + sWhere + ";";

    sLastSQLError = "";    
    if (!rr.exec(sSQL)){
      sLastSQLError = rr.lastError().text();
      sLastSQLCommandFailed[Database] = sSQL;
      return false;
    } else {
      sLastSQLCommands[Database] += sSQL + "\n";
    }

    return true;
  }

  return false;
}

t_boolean _table2::METHOD_Update1(QString Table, _array *Update, _array *Where)
{
  return METHOD_Update(CurrentDatabase.databaseName(), Table, Update, Where);
}

t_boolean _table2::METHOD_Update(QString Database, QString Table, _array *Update, _array *Where)
{
 if (databases.contains(Database)){

    QString sUpdate = "";
    QString sWhere = "";

    QSqlDriver *driver = databases[Database].driver();

    QMapIterator<QString, t_variant> i(Where->qmap);
    int x = 0;
    while (i.hasNext()){
      i.next();
      if (x > 0) sWhere += " AND ";
      x++;

      QString sName = i.key();
      t_variant v = i.value();
      QString sValue = "";

      QSqlField f;

      switch (v.nType){
        case pcode__BOOLEAN:
          f.setValue(QVariant((bool) v.boolean_));
          sValue = driver->formatValue(f);
          break;
        case pcode__SHORT:
        case pcode__BYTE:
        case pcode__INTEGER:
        case pcode__LONG:
          f.setValue(QVariant(v.toLong()));
          sValue = driver->formatValue(f);
          break;
        case pcode__SINGLE:
          f.setValue(QVariant(v.single_));
          sValue = driver->formatValue(f);
          break;
        case pcode__DOUBLE:
          f.setValue(QVariant(v.double_));
          sValue = driver->formatValue(f);
          break;
        case pcode__CURRENCY:
          sValue = *v.toQString();
          break;
        case pcode__DATE:                    
          f.setValue(QVariant(QDateTime(QDate(v.date_.nYear, v.date_.nMonth, v.date_.nDay), QTime(v.date_.nHour, v.date_.nMinute, v.date_.nSecond))));
          sValue = driver->formatValue(f);          
          break;
        default:
          {
            QString k = *v.toQString();
            f.setValue(QVariant(k));
            sValue = driver->formatValue(f);
          }
          break;
      }

      sWhere += sName;
      sWhere += " ";
      sWhere += sValue;

    }

    QMapIterator<QString, t_variant> y(Update->qmap);
    x = 0;
    while (y.hasNext()){
      y.next();
      if (x > 0) sUpdate += ", ";
      x++;

      QString sName = y.key();
      t_variant v = y.value();
      QString sValue = "";

      QSqlField f;

      switch (v.nType){
        case pcode__BOOLEAN:
          f.setValue(QVariant((bool) v.boolean_));
          sValue = driver->formatValue(f);
          break;
        case pcode__SHORT:
        case pcode__BYTE:
        case pcode__INTEGER:
        case pcode__LONG:
          f.setValue(QVariant(v.toLong()));
          sValue = driver->formatValue(f);
          break;
        case pcode__SINGLE:
          f.setValue(QVariant(v.single_));
          sValue = driver->formatValue(f);
          break;
        case pcode__DOUBLE:
          f.setValue(QVariant(v.double_));
          sValue = driver->formatValue(f);
          break;
        case pcode__CURRENCY:
          sValue = *v.toQString();
          break;
        case pcode__DATE:                    
          f.setValue(QVariant(QDateTime(QDate(v.date_.nYear, v.date_.nMonth, v.date_.nDay), QTime(v.date_.nHour, v.date_.nMinute, v.date_.nSecond))));
          sValue = driver->formatValue(f);          
          break;
        default:
          {
            QString k = *v.toQString();
            f.setValue(QVariant(k));
            sValue = driver->formatValue(f);
          }
          break;
      }

      sUpdate += sName;
      sUpdate += " = ";
      sUpdate += sValue;

    }

    QString sSQL = "";
    QSqlQuery rr(databases[Database]);

    sSQL = "UPDATE " + Table + " SET " + sUpdate + " WHERE " + sWhere + ";";

    sLastSQLError = "";    
    if (!rr.exec(sSQL)){
      sLastSQLError = rr.lastError().text();
      sLastSQLCommandFailed[Database] = sSQL;
      return false;
    } else {
      sLastSQLCommands[Database] += sSQL + "\n";
    }

    return true;
  }

  return false;
}

t_boolean _table2::METHOD_Insert1(QString Table, _array *Insert)
{
  return METHOD_Insert(CurrentDatabase.databaseName(), Table, Insert);
}

t_boolean _table2::METHOD_Insert(QString Database, QString Table, _array *Insert)
{

 if (databases.contains(Database)){

    QString sFields = "";
    QString sValues = "";

    QSqlDriver *driver = databases[Database].driver();

    QMapIterator<QString, t_variant> y(Insert->qmap);
    int x = 0;
    while (y.hasNext()){
      y.next();
      if (x > 0) sFields += ", ";
      if (x > 0) sValues += ", ";
      x++;

      QString sName = y.key();
      t_variant v = y.value();
      QString sValue = "";

      QSqlField f;

      switch (v.nType){
        case pcode__BOOLEAN:
          f.setValue(QVariant((bool) v.boolean_));
          sValue = driver->formatValue(f);
          break;
        case pcode__SHORT:
        case pcode__BYTE:
        case pcode__INTEGER:
        case pcode__LONG:
          f.setValue(QVariant(v.toLong()));
          sValue = driver->formatValue(f);
          break;
        case pcode__SINGLE:
          f.setValue(QVariant(v.single_));
          sValue = driver->formatValue(f);
          break;
        case pcode__DOUBLE:
          f.setValue(QVariant(v.double_));
          sValue = driver->formatValue(f);
          break;
        case pcode__CURRENCY:
          sValue = *v.toQString();
          break;
        case pcode__DATE:                    
          f.setValue(QVariant(QDateTime(QDate(v.date_.nYear, v.date_.nMonth, v.date_.nDay), QTime(v.date_.nHour, v.date_.nMinute, v.date_.nSecond))));
          sValue = driver->formatValue(f);          
          break;
        default:
          {
            QString k = *v.toQString();
            f.setValue(QVariant(k));
            sValue = driver->formatValue(f);
          }
          break;
      }

      sFields += sName;
      sValues += sValue;

    }

    QSqlQuery rr(databases[Database]);
    qulonglong kbrecordid = 0;
    
    sLastSQLError = "";
    QString sKBRecordId = getPrimary(databases[Database], Table);

    QString sSQL = "SELECT " + sKBRecordId + " FROM " + Table + " ORDER BY " +sKBRecordId + " DESC;";
    if (rr.exec(sSQL)){
      sLastSQLCommands[Database] += sSQL + "\n";

      QSqlRecord ri = rr.record();
      if (rr.first()){
        int n = ri.indexOf(sKBRecordId);
        kbrecordid = rr.value(n).toLongLong();                 
      }
    } else {
      sLastSQLError = rr.lastError().text();
      sLastSQLCommandFailed[Database] = sSQL;
      return false;
    }

    if (x > 0) sFields += ", ";
    if (x > 0) sValues += ", ";
    sFields += sKBRecordId;
    {
      QSqlField f;
      f.setValue(QVariant(kbrecordid + 1));
      sValues += driver->formatValue(f);
    }    

    sSQL = "INSERT INTO " + Table + " (" + sFields + ") VALUES (" + sValues + ");";

    sLastSQLError = "";    
    if (!rr.exec(sSQL)){
      sLastSQLError = rr.lastError().text();
      sLastSQLCommandFailed[Database] = sSQL;
      return false;
    } else {
      sLastSQLCommands[Database] += sSQL + "\n";
    }

    return true;
  }

  return false;
}



QString _record::METHOD_Open(QString Database, QString TableOrSql)
{
  return METHOD_Open(Database, TableOrSql, 0, 0);
} 

QString _record::METHOD_Open(QString Database, QString TableOrSql, _array *Where, _array *OrderBy)
{
  if (!databases.contains(Database)) return "";

  QString sOrderBy = "";

  if (OrderBy){
    QMapIterator<QString, t_variant> i(OrderBy->qmap);
    int x = 0;
    while (i.hasNext()){
      i.next();
      if (x > 0) sOrderBy += " AND ";
      x++;

      QString sName = i.key();
      t_variant v = i.value();
      QString sValue = *v.toQString();

      sOrderBy += sName;
      sOrderBy += " ";
      sOrderBy += sValue;

    }
  }

  QString sWhere = "";

  QSqlDriver *driver = databases[Database].driver();

  if (Where){
    QMapIterator<QString, t_variant> i(Where->qmap);
    int x = 0;
    while (i.hasNext()){
      i.next();
      if (x > 0) sWhere += " AND ";
      x++;

      QString sName = i.key();
      t_variant v = i.value();
      QString sValue = "";

      QSqlField f;

      switch (v.nType){
        case pcode__BOOLEAN:
          f.setValue(QVariant((bool) v.boolean_));
          sValue = driver->formatValue(f);
          break;
        case pcode__SHORT:
        case pcode__BYTE:
        case pcode__INTEGER:
        case pcode__LONG:
          f.setValue(QVariant(v.toLong()));
          sValue = driver->formatValue(f);
          break;
        case pcode__SINGLE:
          f.setValue(QVariant(v.single_));
          sValue = driver->formatValue(f);
          break;
        case pcode__DOUBLE:
          f.setValue(QVariant(v.double_));
          sValue = driver->formatValue(f);
          break;
        case pcode__CURRENCY:
          sValue = *v.toQString();
          break;
        case pcode__DATE:                    
          f.setValue(QVariant(QDateTime(QDate(v.date_.nYear, v.date_.nMonth, v.date_.nDay), QTime(v.date_.nHour, v.date_.nMinute, v.date_.nSecond))));
          sValue = driver->formatValue(f);          
          break;
        default:
          {
            QString k = *v.toQString();
            f.setValue(QVariant(k));
            sValue = driver->formatValue(f);
          }
          break;
      }

      sWhere += sName;
      sWhere += " ";
      sWhere += sValue;

    }
  }

  QSqlQuery *rr = new QSqlQuery(databases[Database]);
  QString sSQL = TableOrSql;
  if (!TableOrSql.contains(" ")){
    QString sKBRecordId = getPrimary(databases[Database], sSQL);

    if (sWhere.isEmpty()){
      sSQL = "SELECT * FROM " + TableOrSql + " ORDER BY " + sKBRecordId + " ASC;";
    } else {
      sSQL = "SELECT * FROM " + TableOrSql + " WHERE " + sWhere + " ORDER BY " + sKBRecordId + " ASC;";
    }
  }

  QString QueryId = QString("%1").arg((int) rr);
  records[QueryId] = rr;
  records_database[QueryId] = Database;

  if (records[QueryId]->exec(sSQL)){
    sLastSQLCommands[records_database[QueryId]] += sSQL + "\n";    
  } else {
    sLastSQLError = records[QueryId]->lastError().text();
    sLastSQLCommandFailed[records_database[QueryId]] = sSQL;
    return "";
  }

  int n = records[QueryId]->size();

  return QueryId;
} 

QString _record::METHOD_Open(QString Database, _strings *Tables, _array *Where)
{
  // not implemented
  return false;
} 

QString _record::METHOD_Open3(QString TableOrSql)
{
  return METHOD_Open(CurrentDatabase.databaseName(), TableOrSql);
} 

QString _record::METHOD_Open4(QString Table, _array *Where, _array *OrderBy)
{
  return METHOD_Open(CurrentDatabase.databaseName(), Table, Where, OrderBy);
} 

QString _record::METHOD_Open5(_strings *Tables, _array *Where)
{
  return METHOD_Open(CurrentDatabase.databaseName(), Tables, Where);
} 

t_boolean _record::METHOD_Close(QString QueryId)
{
  if (!records.contains(QueryId)) return false;

  delete records[QueryId];
  records.remove(QueryId);

  records_database.remove(QueryId);
  records_table.remove(QueryId);


  return true;
} 

t_boolean _record::METHOD_Requery(QString QueryId)
{
  if (!records.contains(QueryId)) return false;

  QString sSQL = records[QueryId]->executedQuery();
  if (records[QueryId]->exec(sSQL)){
    sLastSQLCommands[records_database[QueryId]] += sSQL + "\n";
    return true;
  }
  sLastSQLError = records[QueryId]->lastError().text();
  sLastSQLCommandFailed[records_database[QueryId]] = sSQL;
  return false;
} 

t_boolean _record::METHOD_First(QString QueryId)
{
  if (!records.contains(QueryId)) return false;

  return records[QueryId]->first();
} 

t_boolean _record::METHOD_Next(QString QueryId)
{
  if (!records.contains(QueryId)) return false;

  return records[QueryId]->next();
} 

t_boolean _record::METHOD_Previous(QString QueryId)
{
  if (!records.contains(QueryId)) return false;

  return records[QueryId]->previous();
} 

t_boolean _record::METHOD_Last(QString QueryId)
{
  if (!records.contains(QueryId)) return false;

  return records[QueryId]->last();
} 

t_boolean _record::METHOD_GoTo(QString QueryId, t_integer Position)
{
  if (!records.contains(QueryId)) return false;

  return records[QueryId]->seek(Position + 1);
} 

t_integer _record::METHOD_Length(QString QueryId)
{
  if (!records.contains(QueryId)) return false;

  return records[QueryId]->size();
} 

t_integer _record::METHOD_Position(QString QueryId)
{
  if (!records.contains(QueryId)) return false;

  return records[QueryId]->at() + 1;
} 

t_boolean _record::METHOD_AddNew(QString QueryId)
{  
  // not implemented 
  return false;
} 

t_boolean _record::METHOD_Insert(QString QueryId)
{
  if (!records.contains(QueryId)) return false;

  QString sFields = "";
  QString sValues = "";

  QSqlDriver *driver = databases[records_database[QueryId]].driver();

  QSqlRecord ri = records[QueryId]->record();
  int y = 0;
  for ( ; y < ri.count(); y++);{
    if (y > 0) sFields += ", ";
    if (y > 0) sValues += ", ";

    QString sName = ri.fieldName(y);
    QString sValue = "";

    QSqlField f;
    f.setValue(ri.value(y));
    sValue = driver->formatValue(f);

    sFields += sName;
    sValues += sValue;

  }

  qulonglong kbrecordid = 0;
  
  sLastSQLError = "";
  QString sKBRecordId = getPrimary(databases[records_database[QueryId]], records_table[QueryId]);

  QString sSQL = "SELECT " + sKBRecordId + " FROM " + records_table[QueryId] + " ORDER BY " + sKBRecordId + " DESC;";
  QSqlQuery rr(databases[records_database[QueryId]]);
  if (rr.exec(sSQL)){
    sLastSQLCommands[records_database[QueryId]] += sSQL + "\n";

    QSqlRecord ri = rr.record();
    if (rr.first()){
      int n = ri.indexOf(sKBRecordId);
      kbrecordid = rr.value(n).toLongLong();                 
    }
  } else {
    sLastSQLError = rr.lastError().text();
    sLastSQLCommandFailed[records_database[QueryId]] = sSQL;
    return false;
  }

  if (y > 0) sFields += ", ";
  if (y > 0) sValues += ", ";
  sFields += sKBRecordId;
  {
    QSqlField f;
    f.setValue(QVariant(kbrecordid + 1));
    sValues += driver->formatValue(f);
  }    

  sSQL = "INSERT INTO " + records_table[QueryId] + " (" + sFields + ") VALUES (" + sValues + ");";

  sLastSQLError = "";    
  if (!rr.exec(sSQL)){
    sLastSQLError = rr.lastError().text();
    sLastSQLCommandFailed[records_database[QueryId]] = sSQL;
    return false;
  } else {
    sLastSQLCommands[records_database[QueryId]] += sSQL + "\n";
  }

  return false;
} 

t_boolean _record::METHOD_Update(QString QueryId)
{
  return false;
} 

t_boolean _record::METHOD_Delete(QString QueryId)
{
  return false;
} 

t_boolean _record::METHOD_Clear(QString QueryId)
{
  return false;
} 

void _record::METHOD_Set(QString QueryId, QString Field, t_variant Value)
{  
} 

t_variant _record::METHOD_Get(QString QueryId, QString Field)
{
  if (!records.contains(QueryId)) return false;

  QSqlRecord ri = records[QueryId]->record();
  int n = ri.indexOf(Field);
  if (records[QueryId]->isValid() && n >= 0){

    switch(ri.value(n).type()){
      case QVariant::Bool:
        return t_variant((t_boolean) ri.value(n).toBool());
        break;
      case QVariant::Date: 
      case QVariant::Time: 
      case QVariant::DateTime:  
        return t_variant(ri.value(n).toDateTime());         
        break;
      case QVariant::Double:
        return t_variant(ri.value(n).toDouble());
        break;
      case QVariant::Int:
        return t_variant(ri.value(n).toInt());
        break;
      case QVariant::LongLong:
        return t_variant(ri.value(n).toLongLong());
        break;
      case QVariant::String: 
      default:
        return t_variant(&ri.value(n).toString());
        break;
    }
    
  }

  return t_variant("");
} 

_strings *_record::METHOD_Fields(QString QueryId)
{
  _strings *ss = new _strings();

  if (!records.contains(QueryId)) return ss;
  QSqlRecord ri = records[QueryId]->record();
  
  if (!records[QueryId]->isActive()) return ss;

  for (int i = 0; i < ri.count(); i++){
    ss->METHOD_Append(ri.fieldName(i));
  }
  
  return ss;
}

QString _record::METHOD_PrimaryKeyName(QString QueryId)
{
  return "kbrecordid";
}

t_integer _record::METHOD_PrimaryKey(QString QueryId)
{
  return METHOD_Get(QueryId, "kbrecordid").toInteger();
}


t_boolean _query::METHOD_Run1(QString QueryNameOrSql)
{
  return METHOD_Run(CurrentDatabase.databaseName(), QueryNameOrSql);
}

t_boolean _query::METHOD_Run(QString Database, QString QueryNameOrSql)
{
  QString sSQL = "";
  if (QueryNameOrSql.contains(" ")){
    sSQL = interpreter_loadFileAsString(QueryNameOrSql.endsWith(".kbasic_query") ? QueryNameOrSql : (QueryNameOrSql + ".kbasic_query"));
  } else {
    sSQL = QueryNameOrSql;
  }

  sLastSQLError = "";
  QSqlQuery rr(databases[Database]);
  if (rr.exec(sSQL)){
    sLastSQLCommands[Database] += sSQL + "\n";
    return true;
  } else {
    sLastSQLError = rr.lastError().text();
    sLastSQLCommandFailed[Database] = sSQL;
    return false;
  }

  return false;
}

void _listbox::METHOD_SetForm(t_integer Index, _form *Form)
{
  if (Index - 1 < 0 || Index - 1 >= count()) return;
  QListWidgetItem *l = item(Index - 1);

  if (l){
    setItemWidget(l, (QWidget *) Form);
    /*
	QComboBox *com = new QComboBox();
	com->addItem("1");
	com->addItem("2");
	com->addItem("3");
	
	QPushButton *but = new QPushButton();
	but->setText("+");

	QHBoxLayout *layout = new QHBoxLayout();
	layout->addWidget(but);
	//layout->addWidget(com);
	QWidget *widget = new QWidget();
	widget->setLayout(layout);
  widget->resize(100, 100);

	setItemWidget(l, but);*/


  }
  

}



void _formsview::init()
{

  qvboxlayout = new QVBoxLayout();
  qvboxlayout->setSpacing(0);
  qvboxlayout->setMargin(0);

  QWidget *w = new QWidget();
  w->setLayout(qvboxlayout);

  QScrollArea *a = new QScrollArea();  
  a->setFrameShadow(QFrame::Plain);
  a->setWidget(w);
  a->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
  a->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded); 
  a->setWidgetResizable(true);

  QVBoxLayout *l = new QVBoxLayout();
  setLayout(l);
  l->addWidget(a);

}

void _formsview::METHOD_SelectAll(t_boolean YesNo)
{
}

void _formsview::METHOD_Select(t_integer Index, t_boolean YesNo)
{
}

t_boolean _formsview::METHOD_IsSelected(t_integer Index)
{
  return false;
}

t_integer _formsview::METHOD_Length()
{
  return 0;
}

void _formsview::METHOD_RemoveAll()
{
}

void _formsview::METHOD_Remove(t_integer Index)
{
}

void _formsview::METHOD_Insert(t_integer Index, _form *Form)
{
}

void _formsview::METHOD_Append(_form *Form)
{
  Form->SETPROPERTY_MinimumWidth(Form->GETPROPERTY_Width());
  Form->SETPROPERTY_MinimumHeight(Form->GETPROPERTY_Height());

  qvboxlayout->addWidget(Form);
}

void _formsview::METHOD_SetForm(t_integer Index, _form *Form)
{
}

_form *_formsview::METHOD_Form(t_integer Index)
{
  return 0;
}

void _formsview::METHOD_ScrollTo(t_integer Index)
{
}

void _web::linkClicked(const QUrl & u)
{
  EVENT_OnEvent(METHOD_BackwardAvailable(), METHOD_ForwardAvailable(), u.toString());
}


void _web::unsupportedContent ( QNetworkReply * reply )
{
  QUrl u = reply->url();
  QString k = u.toString();
  if (k.startsWith("file:///WEBVIEW/", Qt::CaseInsensitive)){
    k = k.mid(QString("file:///WEBVIEW/").length());
    int n = k.indexOf("?");
    QString m = "";
    if (n >= 0){
      m = k.mid(n + 1);
      Keys.clear();
      Values.clear();
      QStringList l = m.split("&");
      for (int i = 0; i < l.count(); i++){
        QString z = l.at(i);
        int y = z.indexOf("=");
        QString sKey = "";
        QString sValue = "";

        if (y >= 0){
          sKey = z.left(y);
          sValue = z.mid(y + 1);
        }

        //?name=gut&part=333

        Keys.append(sKey);
        Values.append(sValue);
      }

      k = k.left(n);
    }

    // CONTROL
    my_form->udpsockets.delRelatedWebView(GETPROPERTY_Name());
    my_form->labels.delRelatedWebView(GETPROPERTY_Name());
    my_form->headers.delRelatedWebView(GETPROPERTY_Name());
    my_form->footers.delRelatedWebView(GETPROPERTY_Name());
    my_form->serialports.delRelatedWebView(GETPROPERTY_Name());
    my_form->movies.delRelatedWebView(GETPROPERTY_Name());
    my_form->sounds.delRelatedWebView(GETPROPERTY_Name());
    my_form->webs.delRelatedWebView(GETPROPERTY_Name());
    my_form->lines.delRelatedWebView(GETPROPERTY_Name());
    my_form->spinboxes.delRelatedWebView(GETPROPERTY_Name());
    my_form->sliders.delRelatedWebView(GETPROPERTY_Name());
    my_form->formsviews.delRelatedWebView(GETPROPERTY_Name());
    my_form->toolbarviews.delRelatedWebView(GETPROPERTY_Name());
    my_form->svgs.delRelatedWebView(GETPROPERTY_Name());
    my_form->commandlinkbuttons.delRelatedWebView(GETPROPERTY_Name());
    my_form->resizeboxes.delRelatedWebView(GETPROPERTY_Name());
    my_form->toolbuttons.delRelatedWebView(GETPROPERTY_Name());
    my_form->commandbuttons.delRelatedWebView(GETPROPERTY_Name());
    my_form->checkboxes.delRelatedWebView(GETPROPERTY_Name());
    my_form->frames.delRelatedWebView(GETPROPERTY_Name());
    my_form->listboxes.delRelatedWebView(GETPROPERTY_Name());
    my_form->radiobuttons.delRelatedWebView(GETPROPERTY_Name());
    my_form->tabs.delRelatedWebView(GETPROPERTY_Name());
    my_form->textboxes.delRelatedWebView(GETPROPERTY_Name());
    my_form->progressbars.delRelatedWebView(GETPROPERTY_Name());
    my_form->images.delRelatedWebView(GETPROPERTY_Name());
    my_form->timers.delRelatedWebView(GETPROPERTY_Name());
    my_form->treeviews.delRelatedWebView(GETPROPERTY_Name());
    my_form->comboboxes.delRelatedWebView(GETPROPERTY_Name());
    my_form->imagebuttons.delRelatedWebView(GETPROPERTY_Name());
    my_form->boxes.delRelatedWebView(GETPROPERTY_Name());
    my_form->childcontrols.delRelatedWebView(GETPROPERTY_Name());
    my_form->browsers.delRelatedWebView(GETPROPERTY_Name());
    my_form->editors.delRelatedWebView(GETPROPERTY_Name());
    my_form->dateboxes.delRelatedWebView(GETPROPERTY_Name());
    my_form->timeboxes.delRelatedWebView(GETPROPERTY_Name());
    my_form->datetimeboxes.delRelatedWebView(GETPROPERTY_Name());
    my_form->scrollbars.delRelatedWebView(GETPROPERTY_Name());

    EVENT_OnPage(k);
  }
}

bool qwebpage::acceptNavigationRequest(QWebFrame *frame, const QNetworkRequest &request, NavigationType type)
{  
  return QWebPage::acceptNavigationRequest(frame, request, type);
}

QObject *qwebpage::createPlugin(const QString & classid, const QUrl & url, const QStringList & paramNames, const QStringList & paramValues )
{
  if (qobject_cast<_web *>(parent())){
    _web *my_web = qobject_cast<_web *>(parent());


    QString sName = "";
    
    int nWidth = 0;
    int nHeight = 0;

    QString s = "";
    QString j = "";
    int i = 0;
    foreach(QString k, paramNames)
    {
      if (k.compare("classid", Qt::CaseInsensitive) == 0){ i++; continue; }
      if (k.compare("type", Qt::CaseInsensitive) == 0){ i++; continue; }
      if (k.compare("name", Qt::CaseInsensitive) == 0){ sName = paramValues.at(i); i++; continue; }
      if (k.compare("width", Qt::CaseInsensitive) == 0){ j = paramValues.at(i); nWidth = paramValues.at(i).toInt(); i++; continue; }
      if (k.compare("height", Qt::CaseInsensitive) == 0){ nHeight = paramValues.at(i).toInt(); i++; continue; }
      s += k;
      s += "=";
      s += paramValues.at(i);
      s += "\n";
      i++;
    }
    
      
    // CONTROL
    if (classid.compare("CommandButton", Qt::CaseInsensitive) == 0){
      kb_commandbutton *c = new kb_commandbutton(my_web->my_form);

      EXTERN_myInterpreter->kbasic_binding_setKbId(c, ((kb_form *) (my_web->my_form))->kbScope, 0, pcode___commandbutton);

      c->SETPROPERTY_Name(sName);
      c->SETPROPERTY_Width(nWidth);
      c->SETPROPERTY_Height(nHeight);
      c->setParent(my_web);      
      my_web->my_form->commandbuttons.add(my_web->my_form->commandbuttons.count(), sName, c, my_web->GETPROPERTY_Name());
            
      my_web->my_form->loadControl(&s, my_web->my_form->getControlType(sName), sName, c);

      return c;
    } else if (classid.compare("UdpSocket", Qt::CaseInsensitive) == 0){
      kb_udpsocket *c = new kb_udpsocket(my_web->my_form);

      EXTERN_myInterpreter->kbasic_binding_setKbId(c, ((kb_form *) (my_web->my_form))->kbScope, 0, pcode___udpsocket);

      c->SETPROPERTY_Name(sName);
      c->SETPROPERTY_Width(nWidth);
      c->SETPROPERTY_Height(nHeight);
      c->setParent(my_web);      
      my_web->my_form->udpsockets.add(my_web->my_form->udpsockets.count(), sName, c, my_web->GETPROPERTY_Name());
            
      my_web->my_form->loadControl(&s, my_web->my_form->getControlType(sName), sName, c);

      return c;
 
    } else if (classid.compare("MovieBox", Qt::CaseInsensitive) == 0){
      kb_movie *c = new kb_movie(my_web->my_form);

      EXTERN_myInterpreter->kbasic_binding_setKbId(c, ((kb_form *) (my_web->my_form))->kbScope, 0, pcode___movie);

      c->SETPROPERTY_Name(sName);
      c->SETPROPERTY_Width(nWidth);
      c->SETPROPERTY_Height(nHeight);
      c->setParent(my_web);      
      my_web->my_form->movies.add(my_web->my_form->movies.count(), sName, c, my_web->GETPROPERTY_Name());
            
      my_web->my_form->loadControl(&s, my_web->my_form->getControlType(sName), sName, c);

      return c;
 
    } else if (classid.compare("Label", Qt::CaseInsensitive) == 0){
      kb_label *c = new kb_label(my_web->my_form);

      EXTERN_myInterpreter->kbasic_binding_setKbId(c, ((kb_form *) (my_web->my_form))->kbScope, 0, pcode___label);

      c->SETPROPERTY_Name(sName);
      c->SETPROPERTY_Width(nWidth);
      c->SETPROPERTY_Height(nHeight);
      c->setParent(my_web);      
      my_web->my_form->labels.add(my_web->my_form->labels.count(), sName, c, my_web->GETPROPERTY_Name());
            
      my_web->my_form->loadControl(&s, my_web->my_form->getControlType(sName), sName, c);

      return c;
    } else if (classid.compare("Header", Qt::CaseInsensitive) == 0){
      kb_header *c = new kb_header(my_web->my_form);

      EXTERN_myInterpreter->kbasic_binding_setKbId(c, ((kb_form *) (my_web->my_form))->kbScope, 0, pcode___header);

      c->SETPROPERTY_Name(sName);
      c->SETPROPERTY_Width(nWidth);
      c->SETPROPERTY_Height(nHeight);
      c->setParent(my_web);      
      my_web->my_form->headers.add(my_web->my_form->headers.count(), sName, c, my_web->GETPROPERTY_Name());
            
      my_web->my_form->loadControl(&s, my_web->my_form->getControlType(sName), sName, c);

      return c;

    } else if (classid.compare("Footer", Qt::CaseInsensitive) == 0){
      kb_footer *c = new kb_footer(my_web->my_form);

      EXTERN_myInterpreter->kbasic_binding_setKbId(c, ((kb_form *) (my_web->my_form))->kbScope, 0, pcode___footer);

      c->SETPROPERTY_Name(sName);
      c->SETPROPERTY_Width(nWidth);
      c->SETPROPERTY_Height(nHeight);
      c->setParent(my_web);      
      my_web->my_form->footers.add(my_web->my_form->footers.count(), sName, c, my_web->GETPROPERTY_Name());
            
      my_web->my_form->loadControl(&s, my_web->my_form->getControlType(sName), sName, c);

      return c;

    } else if (classid.compare("SerialPort", Qt::CaseInsensitive) == 0){
      kb_serialport *c = new kb_serialport(my_web->my_form);

      EXTERN_myInterpreter->kbasic_binding_setKbId(c, ((kb_form *) (my_web->my_form))->kbScope, 0, pcode___serialport);

      c->SETPROPERTY_Name(sName);
      c->SETPROPERTY_Width(nWidth);
      c->SETPROPERTY_Height(nHeight);
      c->setParent(my_web);      
      my_web->my_form->serialports.add(my_web->my_form->serialports.count(), sName, c, my_web->GETPROPERTY_Name());
            
      my_web->my_form->loadControl(&s, my_web->my_form->getControlType(sName), sName, c);

      return c;

    } else if (classid.compare("Sound", Qt::CaseInsensitive) == 0){
      kb_sound *c = new kb_sound(my_web->my_form);

      EXTERN_myInterpreter->kbasic_binding_setKbId(c, ((kb_form *) (my_web->my_form))->kbScope, 0, pcode___sound);

      c->SETPROPERTY_Name(sName);
      c->SETPROPERTY_Width(nWidth);
      c->SETPROPERTY_Height(nHeight);
      c->setParent(my_web);      
      my_web->my_form->sounds.add(my_web->my_form->sounds.count(), sName, c, my_web->GETPROPERTY_Name());
            
      my_web->my_form->loadControl(&s, my_web->my_form->getControlType(sName), sName, c);

      return c;

    } else if (classid.compare("WebView", Qt::CaseInsensitive) == 0){
      kb_web *c = new kb_web(my_web->my_form);

      EXTERN_myInterpreter->kbasic_binding_setKbId(c, ((kb_form *) (my_web->my_form))->kbScope, 0, pcode___web);

      c->SETPROPERTY_Name(sName);
      c->SETPROPERTY_Width(nWidth);
      c->SETPROPERTY_Height(nHeight);
      c->setParent(my_web);      
      my_web->my_form->webs.add(my_web->my_form->webs.count(), sName, c, my_web->GETPROPERTY_Name());
            
      my_web->my_form->loadControl(&s, my_web->my_form->getControlType(sName), sName, c);

      return c;

    } else if (classid.compare("Line", Qt::CaseInsensitive) == 0){
      kb_line *c = new kb_line(my_web->my_form);

      EXTERN_myInterpreter->kbasic_binding_setKbId(c, ((kb_form *) (my_web->my_form))->kbScope, 0, pcode___line);

      c->SETPROPERTY_Name(sName);
      c->SETPROPERTY_Width(nWidth);
      c->SETPROPERTY_Height(nHeight);
      c->setParent(my_web);      
      my_web->my_form->lines.add(my_web->my_form->lines.count(), sName, c, my_web->GETPROPERTY_Name());
            
      my_web->my_form->loadControl(&s, my_web->my_form->getControlType(sName), sName, c);

      return c;

    } else if (classid.compare("SpinBox", Qt::CaseInsensitive) == 0){
      kb_spinbox *c = new kb_spinbox(my_web->my_form);

      EXTERN_myInterpreter->kbasic_binding_setKbId(c, ((kb_form *) (my_web->my_form))->kbScope, 0, pcode___spinbox);

      c->SETPROPERTY_Name(sName);
      c->SETPROPERTY_Width(nWidth);
      c->SETPROPERTY_Height(nHeight);
      c->setParent(my_web);      
      my_web->my_form->spinboxes.add(my_web->my_form->spinboxes.count(), sName, c, my_web->GETPROPERTY_Name());
            
      my_web->my_form->loadControl(&s, my_web->my_form->getControlType(sName), sName, c);

      return c;

    } else if (classid.compare("Slider", Qt::CaseInsensitive) == 0){
      kb_slider *c = new kb_slider(my_web->my_form);

      EXTERN_myInterpreter->kbasic_binding_setKbId(c, ((kb_form *) (my_web->my_form))->kbScope, 0, pcode___slider);

      c->SETPROPERTY_Name(sName);
      c->SETPROPERTY_Width(nWidth);
      c->SETPROPERTY_Height(nHeight);
      c->setParent(my_web);      
      my_web->my_form->sliders.add(my_web->my_form->sliders.count(), sName, c, my_web->GETPROPERTY_Name());
            
      my_web->my_form->loadControl(&s, my_web->my_form->getControlType(sName), sName, c);

      return c;

    } else if (classid.compare("FormsView", Qt::CaseInsensitive) == 0){
      kb_formsview *c = new kb_formsview(my_web->my_form);

      EXTERN_myInterpreter->kbasic_binding_setKbId(c, ((kb_form *) (my_web->my_form))->kbScope, 0, pcode___formsview);

      c->SETPROPERTY_Name(sName);
      c->SETPROPERTY_Width(nWidth);
      c->SETPROPERTY_Height(nHeight);
      c->setParent(my_web);      
      my_web->my_form->formsviews.add(my_web->my_form->formsviews.count(), sName, c, my_web->GETPROPERTY_Name());
            
      my_web->my_form->loadControl(&s, my_web->my_form->getControlType(sName), sName, c);

      return c;

    } else if (classid.compare("ToolBarView", Qt::CaseInsensitive) == 0){
      kb_toolbarview *c = new kb_toolbarview(my_web->my_form);

      EXTERN_myInterpreter->kbasic_binding_setKbId(c, ((kb_form *) (my_web->my_form))->kbScope, 0, pcode___toolbarview);

      c->SETPROPERTY_Name(sName);
      c->SETPROPERTY_Width(nWidth);
      c->SETPROPERTY_Height(nHeight);
      c->setParent(my_web);      
      my_web->my_form->toolbarviews.add(my_web->my_form->toolbarviews.count(), sName, c, my_web->GETPROPERTY_Name());
            
      my_web->my_form->loadControl(&s, my_web->my_form->getControlType(sName), sName, c);

      return c;

    } else if (classid.compare("SvgBox", Qt::CaseInsensitive) == 0){
      kb_svg *c = new kb_svg(my_web->my_form);

      EXTERN_myInterpreter->kbasic_binding_setKbId(c, ((kb_form *) (my_web->my_form))->kbScope, 0, pcode___svg);

      c->SETPROPERTY_Name(sName);
      c->SETPROPERTY_Width(nWidth);
      c->SETPROPERTY_Height(nHeight);
      c->setParent(my_web);      
      my_web->my_form->svgs.add(my_web->my_form->svgs.count(), sName, c, my_web->GETPROPERTY_Name());
            
      my_web->my_form->loadControl(&s, my_web->my_form->getControlType(sName), sName, c);

      return c;

    } else if (classid.compare("CommandLinkButton", Qt::CaseInsensitive) == 0){
      kb_commandlinkbutton *c = new kb_commandlinkbutton(my_web->my_form);

      EXTERN_myInterpreter->kbasic_binding_setKbId(c, ((kb_form *) (my_web->my_form))->kbScope, 0, pcode___commandlinkbutton);

      c->SETPROPERTY_Name(sName);
      c->SETPROPERTY_Width(nWidth);
      c->SETPROPERTY_Height(nHeight);
      c->setParent(my_web);      
      my_web->my_form->commandlinkbuttons.add(my_web->my_form->commandlinkbuttons.count(), sName, c, my_web->GETPROPERTY_Name());
            
      my_web->my_form->loadControl(&s, my_web->my_form->getControlType(sName), sName, c);

      return c;

    } else if (classid.compare("ResizeBox", Qt::CaseInsensitive) == 0){
      kb_resizebox *c = new kb_resizebox(my_web->my_form);

      EXTERN_myInterpreter->kbasic_binding_setKbId(c, ((kb_form *) (my_web->my_form))->kbScope, 0, pcode___resizebox);

      c->SETPROPERTY_Name(sName);
      c->SETPROPERTY_Width(nWidth);
      c->SETPROPERTY_Height(nHeight);
      c->setParent(my_web);      
      my_web->my_form->resizeboxes.add(my_web->my_form->resizeboxes.count(), sName, c, my_web->GETPROPERTY_Name());
            
      my_web->my_form->loadControl(&s, my_web->my_form->getControlType(sName), sName, c);

      return c;

    } else if (classid.compare("ToolButton", Qt::CaseInsensitive) == 0){
      kb_toolbutton *c = new kb_toolbutton(my_web->my_form);

      EXTERN_myInterpreter->kbasic_binding_setKbId(c, ((kb_form *) (my_web->my_form))->kbScope, 0, pcode___toolbutton);

      c->SETPROPERTY_Name(sName);
      c->SETPROPERTY_Width(nWidth);
      c->SETPROPERTY_Height(nHeight);
      c->setParent(my_web);      
      my_web->my_form->toolbuttons.add(my_web->my_form->toolbuttons.count(), sName, c, my_web->GETPROPERTY_Name());
            
      my_web->my_form->loadControl(&s, my_web->my_form->getControlType(sName), sName, c);

      return c;

    } else if (classid.compare("CheckBox", Qt::CaseInsensitive) == 0){
      kb_checkbox *c = new kb_checkbox(my_web->my_form);

      EXTERN_myInterpreter->kbasic_binding_setKbId(c, ((kb_form *) (my_web->my_form))->kbScope, 0, pcode___checkbox);

      c->SETPROPERTY_Name(sName);
      c->SETPROPERTY_Width(nWidth);
      c->SETPROPERTY_Height(nHeight);
      c->setParent(my_web);      
      my_web->my_form->checkboxes.add(my_web->my_form->checkboxes.count(), sName, c, my_web->GETPROPERTY_Name());
            
      my_web->my_form->loadControl(&s, my_web->my_form->getControlType(sName), sName, c);

      return c;
 
    } else if (classid.compare("Frames", Qt::CaseInsensitive) == 0){
      kb_frame *c = new kb_frame(my_web->my_form);

      EXTERN_myInterpreter->kbasic_binding_setKbId(c, ((kb_form *) (my_web->my_form))->kbScope, 0, pcode___frame);

      c->SETPROPERTY_Name(sName);
      c->SETPROPERTY_Width(nWidth);
      c->SETPROPERTY_Height(nHeight);
      c->setParent(my_web);      
      my_web->my_form->frames.add(my_web->my_form->frames.count(), sName, c, my_web->GETPROPERTY_Name());
            
      my_web->my_form->loadControl(&s, my_web->my_form->getControlType(sName), sName, c);

      return c;

    } else if (classid.compare("ListBox", Qt::CaseInsensitive) == 0){
      kb_listbox *c = new kb_listbox(my_web->my_form);

      EXTERN_myInterpreter->kbasic_binding_setKbId(c, ((kb_form *) (my_web->my_form))->kbScope, 0, pcode___listbox);

      c->SETPROPERTY_Name(sName);
      c->SETPROPERTY_Width(nWidth);
      c->SETPROPERTY_Height(nHeight);
      c->setParent(my_web);      
      my_web->my_form->listboxes.add(my_web->my_form->listboxes.count(), sName, c, my_web->GETPROPERTY_Name());
            
      my_web->my_form->loadControl(&s, my_web->my_form->getControlType(sName), sName, c);

      return c;

    } else if (classid.compare("RadioButton", Qt::CaseInsensitive) == 0){
      kb_radiobutton *c = new kb_radiobutton(my_web->my_form);

      EXTERN_myInterpreter->kbasic_binding_setKbId(c, ((kb_form *) (my_web->my_form))->kbScope, 0, pcode___radiobutton);

      c->SETPROPERTY_Name(sName);
      c->SETPROPERTY_Width(nWidth);
      c->SETPROPERTY_Height(nHeight);
      c->setParent(my_web);      
      my_web->my_form->radiobuttons.add(my_web->my_form->radiobuttons.count(), sName, c, my_web->GETPROPERTY_Name());
            
      my_web->my_form->loadControl(&s, my_web->my_form->getControlType(sName), sName, c);

      return c;

    } else if (classid.compare("TabView", Qt::CaseInsensitive) == 0){
      kb_tab *c = new kb_tab(my_web->my_form);

      EXTERN_myInterpreter->kbasic_binding_setKbId(c, ((kb_form *) (my_web->my_form))->kbScope, 0, pcode___tab);

      c->SETPROPERTY_Name(sName);
      c->SETPROPERTY_Width(nWidth);
      c->SETPROPERTY_Height(nHeight);
      c->setParent(my_web);      
      my_web->my_form->tabs.add(my_web->my_form->tabs.count(), sName, c, my_web->GETPROPERTY_Name());
            
      my_web->my_form->loadControl(&s, my_web->my_form->getControlType(sName), sName, c);

      return c;

    } else if (classid.compare("TextBox", Qt::CaseInsensitive) == 0){
      kb_textbox *c = new kb_textbox(my_web->my_form);

      EXTERN_myInterpreter->kbasic_binding_setKbId(c, ((kb_form *) (my_web->my_form))->kbScope, 0, pcode___textbox);

      c->SETPROPERTY_Name(sName);
      c->SETPROPERTY_Width(nWidth);
      c->SETPROPERTY_Height(nHeight);
      c->setParent(my_web);      
      my_web->my_form->textboxes.add(my_web->my_form->textboxes.count(), sName, c, my_web->GETPROPERTY_Name());
            
      my_web->my_form->loadControl(&s, my_web->my_form->getControlType(sName), sName, c);

      return c;

    } else if (classid.compare("ProgressBar", Qt::CaseInsensitive) == 0){
      kb_progressbar *c = new kb_progressbar(my_web->my_form);

      EXTERN_myInterpreter->kbasic_binding_setKbId(c, ((kb_form *) (my_web->my_form))->kbScope, 0, pcode___progressbar);

      c->SETPROPERTY_Name(sName);
      c->SETPROPERTY_Width(nWidth);
      c->SETPROPERTY_Height(nHeight);
      c->setParent(my_web);      
      my_web->my_form->progressbars.add(my_web->my_form->progressbars.count(), sName, c, my_web->GETPROPERTY_Name());
            
      my_web->my_form->loadControl(&s, my_web->my_form->getControlType(sName), sName, c);

      return c;

    } else if (classid.compare("ImageBox", Qt::CaseInsensitive) == 0){
      kb_image *c = new kb_image(my_web->my_form);

      EXTERN_myInterpreter->kbasic_binding_setKbId(c, ((kb_form *) (my_web->my_form))->kbScope, 0, pcode___image);

      c->SETPROPERTY_Name(sName);
      c->SETPROPERTY_Width(nWidth);
      c->SETPROPERTY_Height(nHeight);
      c->setParent(my_web);      
      my_web->my_form->images.add(my_web->my_form->images.count(), sName, c, my_web->GETPROPERTY_Name());
            
      my_web->my_form->loadControl(&s, my_web->my_form->getControlType(sName), sName, c);

      return c;

    } else if (classid.compare("Timer", Qt::CaseInsensitive) == 0){
      kb_timer *c = new kb_timer(my_web->my_form);

      EXTERN_myInterpreter->kbasic_binding_setKbId(c, ((kb_form *) (my_web->my_form))->kbScope, 0, pcode___timer);

      c->SETPROPERTY_Name(sName);
      c->SETPROPERTY_Width(nWidth);
      c->SETPROPERTY_Height(nHeight);
      c->setParent(my_web);      
      my_web->my_form->timers.add(my_web->my_form->timers.count(), sName, c, my_web->GETPROPERTY_Name());
            
      my_web->my_form->loadControl(&s, my_web->my_form->getControlType(sName), sName, c);

      return c;

    } else if (classid.compare("TreeView", Qt::CaseInsensitive) == 0){
      kb_treeview *c = new kb_treeview(my_web->my_form);

      EXTERN_myInterpreter->kbasic_binding_setKbId(c, ((kb_form *) (my_web->my_form))->kbScope, 0, pcode___treeview);

      c->SETPROPERTY_Name(sName);
      c->SETPROPERTY_Width(nWidth);
      c->SETPROPERTY_Height(nHeight);
      c->setParent(my_web);      
      my_web->my_form->treeviews.add(my_web->my_form->treeviews.count(), sName, c, my_web->GETPROPERTY_Name());
            
      my_web->my_form->loadControl(&s, my_web->my_form->getControlType(sName), sName, c);

      return c;

    } else if (classid.compare("ComboBox", Qt::CaseInsensitive) == 0){
      kb_combobox *c = new kb_combobox(my_web->my_form);

      EXTERN_myInterpreter->kbasic_binding_setKbId(c, ((kb_form *) (my_web->my_form))->kbScope, 0, pcode___combobox);

      c->SETPROPERTY_Name(sName);
      c->SETPROPERTY_Width(nWidth);
      c->SETPROPERTY_Height(nHeight);
      c->setParent(my_web);      
      my_web->my_form->comboboxes.add(my_web->my_form->comboboxes.count(), sName, c, my_web->GETPROPERTY_Name());
            
      my_web->my_form->loadControl(&s, my_web->my_form->getControlType(sName), sName, c);

      return c;

    } else if (classid.compare("ImageButton", Qt::CaseInsensitive) == 0){
      kb_imagebutton *c = new kb_imagebutton(my_web->my_form);

      EXTERN_myInterpreter->kbasic_binding_setKbId(c, ((kb_form *) (my_web->my_form))->kbScope, 0, pcode___imagebutton);

      c->SETPROPERTY_Name(sName);
      c->SETPROPERTY_Width(nWidth);
      c->SETPROPERTY_Height(nHeight);
      c->setParent(my_web);      
      my_web->my_form->imagebuttons.add(my_web->my_form->imagebuttons.count(), sName, c, my_web->GETPROPERTY_Name());
            
      my_web->my_form->loadControl(&s, my_web->my_form->getControlType(sName), sName, c);

      return c;

    } else if (classid.compare("Box", Qt::CaseInsensitive) == 0){
      kb_box *c = new kb_box(my_web->my_form);

      EXTERN_myInterpreter->kbasic_binding_setKbId(c, ((kb_form *) (my_web->my_form))->kbScope, 0, pcode___box);

      c->SETPROPERTY_Name(sName);
      c->SETPROPERTY_Width(nWidth);
      c->SETPROPERTY_Height(nHeight);
      c->setParent(my_web);      
      my_web->my_form->boxes.add(my_web->my_form->boxes.count(), sName, c, my_web->GETPROPERTY_Name());
            
      my_web->my_form->loadControl(&s, my_web->my_form->getControlType(sName), sName, c);

      return c;

    } else if (classid.compare("FormView", Qt::CaseInsensitive) == 0){
      kb_childcontrol *c = new kb_childcontrol(my_web->my_form);

      EXTERN_myInterpreter->kbasic_binding_setKbId(c, ((kb_form *) (my_web->my_form))->kbScope, 0, pcode___childcontrol);

      c->SETPROPERTY_Name(sName);
      c->SETPROPERTY_Width(nWidth);
      c->SETPROPERTY_Height(nHeight);
      c->setParent(my_web);      
      my_web->my_form->childcontrols.add(my_web->my_form->childcontrols.count(), sName, c, my_web->GETPROPERTY_Name());
            
      my_web->my_form->loadControl(&s, my_web->my_form->getControlType(sName), sName, c);

      return c;

    } else if (classid.compare("HtmlView", Qt::CaseInsensitive) == 0){
      kb_browser *c = new kb_browser(my_web->my_form);

      EXTERN_myInterpreter->kbasic_binding_setKbId(c, ((kb_form *) (my_web->my_form))->kbScope, 0, pcode___browser);

      c->SETPROPERTY_Name(sName);
      c->SETPROPERTY_Width(nWidth);
      c->SETPROPERTY_Height(nHeight);
      c->setParent(my_web);      
      my_web->my_form->browsers.add(my_web->my_form->browsers.count(), sName, c, my_web->GETPROPERTY_Name());
            
      my_web->my_form->loadControl(&s, my_web->my_form->getControlType(sName), sName, c);

      return c;

    } else if (classid.compare("RichTextBox", Qt::CaseInsensitive) == 0){
      kb_editor *c = new kb_editor(my_web->my_form);

      EXTERN_myInterpreter->kbasic_binding_setKbId(c, ((kb_form *) (my_web->my_form))->kbScope, 0, pcode___editor);

      c->SETPROPERTY_Name(sName);
      c->SETPROPERTY_Width(nWidth);
      c->SETPROPERTY_Height(nHeight);
      c->setParent(my_web);      
      my_web->my_form->editors.add(my_web->my_form->editors.count(), sName, c, my_web->GETPROPERTY_Name());
            
      my_web->my_form->loadControl(&s, my_web->my_form->getControlType(sName), sName, c);

      return c;

    } else if (classid.compare("DateBox", Qt::CaseInsensitive) == 0){
      kb_datebox *c = new kb_datebox(my_web->my_form);

      EXTERN_myInterpreter->kbasic_binding_setKbId(c, ((kb_form *) (my_web->my_form))->kbScope, 0, pcode___datebox);

      c->SETPROPERTY_Name(sName);
      c->SETPROPERTY_Width(nWidth);
      c->SETPROPERTY_Height(nHeight);
      c->setParent(my_web);      
      my_web->my_form->dateboxes.add(my_web->my_form->dateboxes.count(), sName, c, my_web->GETPROPERTY_Name());
            
      my_web->my_form->loadControl(&s, my_web->my_form->getControlType(sName), sName, c);

      return c;

    } else if (classid.compare("TimeBox", Qt::CaseInsensitive) == 0){
      kb_timebox *c = new kb_timebox(my_web->my_form);

      EXTERN_myInterpreter->kbasic_binding_setKbId(c, ((kb_form *) (my_web->my_form))->kbScope, 0, pcode___timebox);

      c->SETPROPERTY_Name(sName);
      c->SETPROPERTY_Width(nWidth);
      c->SETPROPERTY_Height(nHeight);
      c->setParent(my_web);      
      my_web->my_form->timeboxes.add(my_web->my_form->timeboxes.count(), sName, c, my_web->GETPROPERTY_Name());
            
      my_web->my_form->loadControl(&s, my_web->my_form->getControlType(sName), sName, c);

      return c;

    } else if (classid.compare("DateTimeBox", Qt::CaseInsensitive) == 0){
      kb_datetimebox *c = new kb_datetimebox(my_web->my_form);

      EXTERN_myInterpreter->kbasic_binding_setKbId(c, ((kb_form *) (my_web->my_form))->kbScope, 0, pcode___datetimebox);

      c->SETPROPERTY_Name(sName);
      c->SETPROPERTY_Width(nWidth);
      c->SETPROPERTY_Height(nHeight);
      c->setParent(my_web);      
      my_web->my_form->datetimeboxes.add(my_web->my_form->datetimeboxes.count(), sName, c, my_web->GETPROPERTY_Name());
            
      my_web->my_form->loadControl(&s, my_web->my_form->getControlType(sName), sName, c);

      return c;

    } else if (classid.compare("ScrollBar", Qt::CaseInsensitive) == 0){
      kb_scrollbar *c = new kb_scrollbar(my_web->my_form);

      EXTERN_myInterpreter->kbasic_binding_setKbId(c, ((kb_form *) (my_web->my_form))->kbScope, 0, pcode___scrollbar);

      c->SETPROPERTY_Name(sName);
      c->SETPROPERTY_Width(nWidth);
      c->SETPROPERTY_Height(nHeight);
      c->setParent(my_web);      
      my_web->my_form->scrollbars.add(my_web->my_form->scrollbars.count(), sName, c, my_web->GETPROPERTY_Name());
            
      my_web->my_form->loadControl(&s, my_web->my_form->getControlType(sName), sName, c);

      return c;
    }

  }
  return QWebPage::createPlugin(classid, url, paramNames, paramValues);
}

QString _web::METHOD_Argument(QString Name)
{
  int n = Keys.indexOf(Name);
  if (n >= 0){
    return Values.at(n);
  }
  return "";
}

_strings *METHOD_Keys2(_web *my_web) // used to avoid compilation problem
{  
  _strings *ss = new _strings();

  foreach(QString s, my_web->Keys)
  {
    ss->METHOD_Append(s);
  }

  return ss;
}

_strings *_web::METHOD_Keys()
{  
  return METHOD_Keys2(this);
}

_strings *METHOD_Values2(_web *my_web) // used to avoid compilation problem
{  
  _strings *ss = new _strings();

  foreach(QString s, my_web->Values)
  {
    ss->METHOD_Append(s);
  }

  return ss;
}

_strings *_web::METHOD_Values()
{  
  return METHOD_Values2(this);
}

  interpreter_parameter::~interpreter_parameter()
  {

    if (pcodeType == pcode__CSTRING && cstring_){
      free(cstring_);
    }
    
  }

  void _sounds2::METHOD_Play(const QString & Id)
{

  if (sounds_map.contains(Id)){
    t_sound2 ts = sounds_map[Id];
    Phonon::MediaObject *mediaObject = new Phonon::MediaObject();
    Phonon::AudioOutput *audioOutput = new Phonon::AudioOutput();

    sounds_playing[mediaObject] = audioOutput;
    sounds_playing2[mediaObject] = new Phonon::MediaSource(ts.buffer);
    mediaObject->setCurrentSource(*sounds_playing2[mediaObject]);
    sounds_playing3[mediaObject] = Phonon::createPath(mediaObject, audioOutput);
    

/*
    //ts.path = 
  ///   Phonon::Path path = Phonon::createPath(mediaObject, audioOutput);
   // Phonon::MediaSource *ms = new Phonon::MediaSource(ts.buffer);
  //  mediaObject->setCurrentSource(*ms);

    mediaObject->setCurrentSource(Phonon::MediaSource(ts.buffer));
//   mediaObject->setCurrentSource(Phonon::MediaSource("c:\\aliciabessette_callersplace.mp3"));
    mediaObject->setCurrentSource(Phonon::MediaSource(Phonon::NoDisc));
 //   mediaObject->setCurrentSource(sounds_playing2[mediaObject]);
    mediaObject->stop();
    delete audioOutput;
    delete mediaObject;*/

   // sounds_playing.remove(mediaObject);
   // sounds_playing2.remove(mediaObject);
 //   delete ms;

  //return;
    
    QObject::connect(mediaObject, SIGNAL(finished()), EXTERN_my_sounds, SLOT(finished()));
    mediaObject->play();
    
  }
  
}

_sounds2::~_sounds2()
{
  if (mediaObject) delete mediaObject;
  if (audioOutput) delete audioOutput;
   
  QMapIterator<Phonon::MediaObject*, Phonon::AudioOutput*> i(sounds_playing);
  while (i.hasNext()) {
      i.next();
      delete i.key();
      delete i.value();
   }

  foreach(t_sound2 ts, sounds_map){
    delete ts.buffer;
    delete ts.bytearray;
  }
}

void _sounds2::timerEvent(QTimerEvent *e)
{
  killTimer(nTimer);

  int n = sounds_to_be_deleted.count();

  Phonon::MediaObject *mediaObject = sounds_to_be_deleted.takeFirst();

  bool b = sounds_playing3[mediaObject].disconnect();
  sounds_playing3.remove(mediaObject);

  delete mediaObject;
  delete sounds_playing[mediaObject];
//  sounds_playing[mediaObject]->deleteLater();
  //mediaObject->deleteLater();;
  sounds_playing.remove(mediaObject);

  delete sounds_playing2[mediaObject];
  sounds_playing2.remove(mediaObject);

  
  if (n > 1) EXTERN_my_sounds->nTimer = EXTERN_my_sounds->startTimer(10000);
}

void _sounds2::finished()
{
  //ts.path.disconnect();
  Phonon::MediaObject *mediaObject = qobject_cast<Phonon::MediaObject *>(sender());
  if (mediaObject){
    sounds_to_be_deleted.append(mediaObject);

    if (EXTERN_my_sounds->nTimer == 0) EXTERN_my_sounds->nTimer = EXTERN_my_sounds->startTimer(10000);
    /*
    sounds_playing.remove(mediaObject);
    delete sounds_playing[mediaObject];
    sounds_playing.remove2(mediaObject);
    delete sounds_playing2[mediaObject];*/
    /*
    if (mediaObject->state() != Phonon::StoppedState)
    {
      mediaObject->stop();
      while (mediaObject->state() != Phonon::StoppedState){
        qApp->processEvents();
      }
      delete mediaObject;
      sounds_playing.remove(mediaObject);

    }*/
    //sounds_to_be_deleted.append(mediaObject);
    //if (EXTERN_my_sounds->nTimer == 0) EXTERN_my_sounds->nTimer = EXTERN_my_sounds->startTimer(1000);
    
    //EXTERN_my_sounds->myDeleteLater();
    /*
    QThread *t = mediaObject->thread();
    QThread *tt = this->thread();

    sounds_playing[mediaObject]->deleteLater();
    mediaObject->deleteLater();;
    sounds_playing.remove(mediaObject);
    */
    
  }
}

QString _preferences::METHOD_String(QString PreferenceId)
{

  QVariant v = settings->value(PreferenceId);
  int n = v.type();
  QString s = v.toString();
  return s;
}


#endif

