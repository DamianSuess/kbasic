
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


#ifndef _toolbar_H
#define _toolbar_H

#include <QtGui>

#include "../kbshared/typedef.h"
#include "../kbshared/_property.h"

#include "../kbshared/_toolbaritem.h"



#ifdef IDE

extern QAction *my_qaction;

extern _toolbaritem *current;

class _mainwindow;
extern _mainwindow *EXTERN_my_mainwindow;
extern _toolbar *EXTERN_my_toolbar;
#else
#include "../kbshared/_control.h"
#endif

class _toolbar;
class interpreter;


#ifdef IDE
class _qtoolbar : public QToolBar
{
  Q_OBJECT
public:
  _qtoolbar (QWidget * p, _toolbar *_my_toolbar) : QToolBar(p)
  {
    my_toolbar = _my_toolbar;

  }

public:

  void mouseReleaseEvent ( QMouseEvent * e );


void  paintEvent( QPaintEvent *event );

private:

  _toolbar *my_toolbar;

};


#endif

class kb_toolbaritem;

#ifdef IDE
class _toolbar : public QWidget
#endif
#ifdef RUN
extern QString sCurrentLanguage;
extern QString sCurrentCountry;

class _toolbar;
class _form;


extern _toolbar *EXTERN_my_toolbar;

class _toolbar : public QToolBar
#endif

{
  Q_OBJECT
public:

#ifdef RUN



QString loadProjectFile (QString sFile);
t_pointer loadProjectFile(QString s, t_integer *nSize);
QPixmap loadProjectImage(QString sFile);

const char *acName;  
const char *acGroup;
virtual void EVENT_OnEvent();
virtual void EVENT_OnEvent(QString ToolBarItemName);


#endif

  
#ifdef IDE
_toolbar(_mainwindow *_my_mainwindow);
#endif
#ifdef RUN
_toolbar(_form *f = 0, QWidget *parent = 0);
#endif



_form *my_form;


#ifdef RUN

bool isEmpty()
{
  _toolbaritem *c;

  if (firstControl(&c)){
    return false;
  }
  return true;
}


void METHOD_2SetEnabled(QString ToolBarItemName, t_boolean Enabled, _toolbar *my_toolbar);
t_boolean METHOD_2IsEnabled(QString ToolBarItemName, _toolbar *my_toolbar);

void METHOD_2SetVisible(QString ToolBarItemName, t_boolean Visible, _toolbar *my_toolbar);
t_boolean METHOD_2IsVisible(QString ToolBarItemName, _toolbar *my_toolbar);



void METHOD_2SetWithTag(QString Tag, QString PropertyName, t_boolean b);
void METHOD_2SetWithTag(QString Tag, QString PropertyName, t_integer n);
void METHOD_2SetWithTag(QString Tag, QString PropertyName, QString s);

void METHOD_2SetWithGroup(QString Group, QString PropertyName, t_boolean b);
void METHOD_2SetWithGroup(QString Group, QString PropertyName, t_integer n);
void METHOD_2SetWithGroup(QString Group, QString PropertyName, QString s);

static void METHOD_SetWithTag(QString Tag, QString PropertyName, t_boolean b, _toolbar *my_toolbar);
static void METHOD_SetWithTag(QString Tag, QString PropertyName, t_integer n, _toolbar *my_toolbar);
static void METHOD_SetWithTag(QString Tag, QString PropertyName, QString s, _toolbar *my_toolbar);

static void METHOD_SetWithGroup(QString Group, QString PropertyName, t_boolean b, _toolbar *my_toolbar);
static void METHOD_SetWithGroup(QString Group, QString PropertyName, t_integer n, _toolbar *my_toolbar);
static void METHOD_SetWithGroup(QString Group, QString PropertyName, QString s, _toolbar *my_toolbar);



static void METHOD_SetEnabled(QString ActionId, t_boolean Value)
{
  _toolbaritem *c;

  if (EXTERN_my_toolbar && EXTERN_my_toolbar->firstControl(&c)){

    do {

      if (c->GETPROPERTY_ActionId().compare(ActionId, Qt::CaseInsensitive) == 0){

        #define SWITCH_STATIC static
        #define SWITCH SETPROPERTY_Enabled(Value);
        #include "_toolbar_property_switch.h"  
        #undef SWITCH_STATIC

        return;

      }

    } while (EXTERN_my_toolbar->nextControl(&c)); 
  }

}

static t_boolean METHOD_IsEnabled(QString ActionId)
{

  _toolbaritem *c;

  if (EXTERN_my_toolbar && EXTERN_my_toolbar->firstControl(&c)){    
   
    do {

      if (c->GETPROPERTY_ActionId().compare(ActionId, Qt::CaseInsensitive) == 0){

        bool bb = false;
        
        #define SWITCH_STATIC ?
        #define SWITCH3 bb
        #define SWITCH GETPROPERTY_Enabled();
        #include "_toolbar_property_switch.h" 
        #undef SWITCH3
        #undef SWITCH_STATIC

        return bb;

      }

    } while (EXTERN_my_toolbar->nextControl(&c)); 
  }

  return false;
}

static void METHOD_SetVisible(QString ActionId, t_boolean Value)
{
  _toolbaritem *c;

  if (EXTERN_my_toolbar && EXTERN_my_toolbar->firstControl(&c)){

    do {

      if (c->GETPROPERTY_ActionId().compare(ActionId, Qt::CaseInsensitive) == 0){

        #define SWITCH_STATIC static
        #define SWITCH SETPROPERTY_Visible(Value);
        #include "_toolbar_property_switch.h"  
        #undef SWITCH_STATIC

        return;

      }

    } while (EXTERN_my_toolbar->nextControl(&c)); 
  }
}

static t_boolean METHOD_IsVisible(QString ActionId)
{
  _toolbaritem *c;

  if (EXTERN_my_toolbar && EXTERN_my_toolbar->firstControl(&c)){    
   
    do {

      if (c->GETPROPERTY_ActionId().compare(ActionId, Qt::CaseInsensitive) == 0){

        bool bb = false;
        
        #define SWITCH_STATIC ?
        #define SWITCH3 bb
        #define SWITCH GETPROPERTY_Visible();
        #include "_toolbar_property_switch.h" 
        #undef SWITCH3
        #undef SWITCH_STATIC

        return bb;

      }

    } while (EXTERN_my_toolbar->nextControl(&c)); 
  }

  return false;
}

static void METHOD_SetChecked(QString ActionId, t_boolean Value)
{
  _toolbaritem *c;

  if (EXTERN_my_toolbar && EXTERN_my_toolbar->firstControl(&c)){

    do {

      if (c->GETPROPERTY_ActionId().compare(ActionId, Qt::CaseInsensitive) == 0){

        #define SWITCH_STATIC static
        #define SWITCH SETPROPERTY_Checked(Value);
        #include "_toolbar_property_switch.h"  
        #undef SWITCH_STATIC

        return;

      }

    } while (EXTERN_my_toolbar->nextControl(&c)); 
  }
}

static t_boolean METHOD_IsChecked(QString ActionId)
{
  _toolbaritem *c;

  if (EXTERN_my_toolbar && EXTERN_my_toolbar->firstControl(&c)){    
   
    do {

      if (c->GETPROPERTY_ActionId().compare(ActionId, Qt::CaseInsensitive) == 0){

        bool bb = false;
        
        #define SWITCH_STATIC ?
        #define SWITCH3 bb
        #define SWITCH GETPROPERTY_Checked();
        #include "_toolbar_property_switch.h" 
        #undef SWITCH3
        #undef SWITCH_STATIC

        return bb;

      }

    } while (EXTERN_my_toolbar->nextControl(&c)); 
  }

  return false;
}

static void METHOD_SetStatusTip(QString ActionId, QString Value)
{
  _toolbaritem *c;

  if (EXTERN_my_toolbar && EXTERN_my_toolbar->firstControl(&c)){

    do {

      if (c->GETPROPERTY_ActionId().compare(ActionId, Qt::CaseInsensitive) == 0){

        #define SWITCH_STATIC static
        #define SWITCH SETPROPERTY_StatusTip(Value);
        #include "_toolbar_property_switch.h"  
        #undef SWITCH_STATIC

        return;

      }

    } while (EXTERN_my_toolbar->nextControl(&c)); 
  }
}

static QString METHOD_StatusTip(QString ActionId)
{
  _toolbaritem *c;

  if (EXTERN_my_toolbar && EXTERN_my_toolbar->firstControl(&c)){    
   
    do {

      if (c->GETPROPERTY_ActionId().compare(ActionId, Qt::CaseInsensitive) == 0){

        QString bb = "";
        
        #define SWITCH_STATIC ?
        #define SWITCH3 bb
        #define SWITCH GETPROPERTY_StatusTip();
        #include "_toolbar_property_switch.h" 
        #undef SWITCH3
        #undef SWITCH_STATIC

        return bb;

      }

    } while (EXTERN_my_toolbar->nextControl(&c)); 
  }

  return "";
}

static void METHOD_SetToolTip(QString ActionId, QString Value)
{
  _toolbaritem *c;

  if (EXTERN_my_toolbar && EXTERN_my_toolbar->firstControl(&c)){

    do {

      if (c->GETPROPERTY_ActionId().compare(ActionId, Qt::CaseInsensitive) == 0){

        #define SWITCH_STATIC static
        #define SWITCH SETPROPERTY_ToolTip(Value);
        #include "_toolbar_property_switch.h"  
        #undef SWITCH_STATIC

        return;

      }

    } while (EXTERN_my_toolbar->nextControl(&c)); 
  }
}

static QString METHOD_ToolTip(QString ActionId)
{
  _toolbaritem *c;

  if (EXTERN_my_toolbar && EXTERN_my_toolbar->firstControl(&c)){    
   
    do {

      if (c->GETPROPERTY_ActionId().compare(ActionId, Qt::CaseInsensitive) == 0){

        QString bb = "";
        
        #define SWITCH_STATIC ?
        #define SWITCH3 bb
        #define SWITCH GETPROPERTY_ToolTip();
        #include "_toolbar_property_switch.h" 
        #undef SWITCH3
        #undef SWITCH_STATIC

        return bb;

      }

    } while (EXTERN_my_toolbar->nextControl(&c)); 
  }

  return "";
}

static void METHOD_SetWhatsThis(QString ActionId, QString Value)
{
  _toolbaritem *c;

  if (EXTERN_my_toolbar && EXTERN_my_toolbar->firstControl(&c)){

    do {

      if (c->GETPROPERTY_ActionId().compare(ActionId, Qt::CaseInsensitive) == 0){

        #define SWITCH_STATIC static
        #define SWITCH SETPROPERTY_WhatsThis(Value);
        #include "_toolbar_property_switch.h"  
        #undef SWITCH_STATIC

        return;

      }

    } while (EXTERN_my_toolbar->nextControl(&c)); 
  }
}

static QString METHOD_WhatsThis(QString ActionId)
{
  _toolbaritem *c;

  if (EXTERN_my_toolbar && EXTERN_my_toolbar->firstControl(&c)){    
   
    do {

      if (c->GETPROPERTY_ActionId().compare(ActionId, Qt::CaseInsensitive) == 0){

        QString bb = "";
        
        #define SWITCH_STATIC ?
        #define SWITCH3 bb
        #define SWITCH GETPROPERTY_WhatsThis();
        #include "_toolbar_property_switch.h" 
        #undef SWITCH3
        #undef SWITCH_STATIC

        return bb;

      }

    } while (EXTERN_my_toolbar->nextControl(&c)); 
  }

  return "";
}

static void METHOD_SetIcon(QString ActionId, QString Value)
{
  _toolbaritem *c;

  if (EXTERN_my_toolbar && EXTERN_my_toolbar->firstControl(&c)){

    do {

      if (c->GETPROPERTY_ActionId().compare(ActionId, Qt::CaseInsensitive) == 0){

        #define SWITCH_STATIC static
        #define SWITCH SETPROPERTY_Icon(Value);
        #include "_toolbar_property_switch.h"  
        #undef SWITCH_STATIC

        return;

      }

    } while (EXTERN_my_toolbar->nextControl(&c)); 
  }
}

static QString METHOD_Icon(QString ActionId)
{
  _toolbaritem *c;

  if (EXTERN_my_toolbar && EXTERN_my_toolbar->firstControl(&c)){    
   
    do {

      if (c->GETPROPERTY_ActionId().compare(ActionId, Qt::CaseInsensitive) == 0){

        QString bb = "";
        
        #define SWITCH_STATIC ?
        #define SWITCH3 bb
        #define SWITCH GETPROPERTY_Icon();
        #include "_toolbar_property_switch.h" 
        #undef SWITCH3
        #undef SWITCH_STATIC

        return bb;

      }

    } while (EXTERN_my_toolbar->nextControl(&c)); 
  }

  return "";
}

static void METHOD_SetTag(QString ActionId, QString Value)
{
  _toolbaritem *c;

  if (EXTERN_my_toolbar && EXTERN_my_toolbar->firstControl(&c)){

    do {

      if (c->GETPROPERTY_ActionId().compare(ActionId, Qt::CaseInsensitive) == 0){

        #define SWITCH_STATIC static
        #define SWITCH SETPROPERTY_Tag(Value);
        #include "_toolbar_property_switch.h"  
        #undef SWITCH_STATIC

        return;

      }

    } while (EXTERN_my_toolbar->nextControl(&c)); 
  }
}

static QString METHOD_Tag(QString ActionId)
{
  _toolbaritem *c;

  if (EXTERN_my_toolbar && EXTERN_my_toolbar->firstControl(&c)){    
   
    do {

      if (c->GETPROPERTY_ActionId().compare(ActionId, Qt::CaseInsensitive) == 0){

        QString bb = "";
        
        #define SWITCH_STATIC ?
        #define SWITCH3 bb
        #define SWITCH GETPROPERTY_Tag();
        #include "_toolbar_property_switch.h" 
        #undef SWITCH3
        #undef SWITCH_STATIC

        return bb;

      }

    } while (EXTERN_my_toolbar->nextControl(&c)); 
  }

  return "";
}


static void METHOD_SetCaption(QString ActionId, QString Value)
{
  _toolbaritem *c;

  if (EXTERN_my_toolbar && EXTERN_my_toolbar->firstControl(&c)){

    do {

      if (c->GETPROPERTY_ActionId().compare(ActionId, Qt::CaseInsensitive) == 0){

        #define SWITCH_STATIC static
        #define SWITCH SETPROPERTY_Caption(Value);
        #include "_toolbar_property_switch.h"  
        #undef SWITCH_STATIC

        return;

      }

    } while (EXTERN_my_toolbar->nextControl(&c)); 
  }
}

static QString METHOD_Caption(QString ActionId)
{
  _toolbaritem *c;

  if (EXTERN_my_toolbar && EXTERN_my_toolbar->firstControl(&c)){    
   
    do {

      if (c->GETPROPERTY_ActionId().compare(ActionId, Qt::CaseInsensitive) == 0){

        QString bb = "";
        
        #define SWITCH_STATIC ?
        #define SWITCH3 bb
        #define SWITCH GETPROPERTY_Caption();
        #include "_toolbar_property_switch.h" 
        #undef SWITCH3
        #undef SWITCH_STATIC

        return bb;

      }

    } while (EXTERN_my_toolbar->nextControl(&c)); 
  }

  return "";
}

static void METHOD_SetText(QString ActionId, QString Value)
{
  METHOD_SetCaption(ActionId, Value);
}

static QString METHOD_Text(QString ActionId)
{
  return METHOD_Caption(ActionId);
}

static void METHOD_SetSoundOnEvent(QString ActionId, QString Value)
{
  _toolbaritem *c;

  if (EXTERN_my_toolbar && EXTERN_my_toolbar->firstControl(&c)){

    do {

      if (c->GETPROPERTY_ActionId().compare(ActionId, Qt::CaseInsensitive) == 0){

        #define SWITCH_STATIC static
        #define SWITCH SETPROPERTY_SoundOnEvent(Value);
        #include "_toolbar_property_switch.h"  
        #undef SWITCH_STATIC

        return;

      }

    } while (EXTERN_my_toolbar->nextControl(&c)); 
  }
}

static QString METHOD_SoundOnEvent(QString ActionId)
{
  _toolbaritem *c;

  if (EXTERN_my_toolbar && EXTERN_my_toolbar->firstControl(&c)){    
   
    do {

      if (c->GETPROPERTY_ActionId().compare(ActionId, Qt::CaseInsensitive) == 0){

        QString bb = "";
        
        #define SWITCH_STATIC ?
        #define SWITCH3 bb
        #define SWITCH GETPROPERTY_SoundOnEvent();
        #include "_toolbar_property_switch.h" 
        #undef SWITCH3
        #undef SWITCH_STATIC

        return bb;

      }

    } while (EXTERN_my_toolbar->nextControl(&c)); 
  }

  return "";
}

static void METHOD_SetGroup(QString ActionId, QString Value)
{
  _toolbaritem *c;

  if (EXTERN_my_toolbar && EXTERN_my_toolbar->firstControl(&c)){

    do {

      if (c->GETPROPERTY_ActionId().compare(ActionId, Qt::CaseInsensitive) == 0){

        #define SWITCH_STATIC static
        #define SWITCH SETPROPERTY_Group(Value);
        #include "_toolbar_property_switch.h"  
        #undef SWITCH_STATIC

        return;

      }

    } while (EXTERN_my_toolbar->nextControl(&c)); 
  }
}

static QString METHOD_Group(QString ActionId)
{
  _toolbaritem *c;

  if (EXTERN_my_toolbar && EXTERN_my_toolbar->firstControl(&c)){    
   
    do {

      if (c->GETPROPERTY_ActionId().compare(ActionId, Qt::CaseInsensitive) == 0){

        QString bb = "";
        
        #define SWITCH_STATIC ?
        #define SWITCH3 bb
        #define SWITCH GETPROPERTY_Group();
        #include "_toolbar_property_switch.h" 
        #undef SWITCH3
        #undef SWITCH_STATIC

        return bb;

      }

    } while (EXTERN_my_toolbar->nextControl(&c)); 
  }

  return "";
}


static void METHOD_SetKey(QString ActionId, QString Value)
{
  _toolbaritem *c;

  if (EXTERN_my_toolbar && EXTERN_my_toolbar->firstControl(&c)){

    do {

      if (c->GETPROPERTY_ActionId().compare(ActionId, Qt::CaseInsensitive) == 0){

        #define SWITCH_STATIC static
        #define SWITCH SETPROPERTY_Key(Value);
        #include "_toolbar_property_switch.h"  
        #undef SWITCH_STATIC

        return;

      }

    } while (EXTERN_my_toolbar->nextControl(&c)); 
  }
}

static QString METHOD_Key(QString ActionId)
{
  _toolbaritem *c;

  if (EXTERN_my_toolbar && EXTERN_my_toolbar->firstControl(&c)){    
   
    do {

      if (c->GETPROPERTY_ActionId().compare(ActionId, Qt::CaseInsensitive) == 0){

        QString bb = "";
        
        #define SWITCH_STATIC ?
        #define SWITCH3 bb
        #define SWITCH GETPROPERTY_Key();
        #include "_toolbar_property_switch.h" 
        #undef SWITCH3
        #undef SWITCH_STATIC

        return bb;

      }

    } while (EXTERN_my_toolbar->nextControl(&c)); 
  }

  return "";
}


static kb_toolbaritem *METHOD_ToolBarItem(const QString & Name, _toolbar *my_toolbar);
static void METHOD_InsertControl(int Index, _control *c, _toolbar *my_toolbar);
static void METHOD_SetVisible(t_boolean b, _toolbar *my_toolbar);
static t_boolean METHOD_IsVisible(_toolbar *my_toolbar);


public slots:
void triggered(QAction *);

public:
#endif

#include "_toolbar_property.h"
#include "_toolbar_loadsave.h"




#ifdef IDE
public slots:
void clicked();
void pressed();
#endif

public:
  
_toolbaritem *getToolBarItemByAction(QAction *a);




void build();



t_boolean METHOD_insertControl(_toolbaritem *c, _controlType controlType, QString s2 = "")
{
  QString s = s2; 

  switch(controlType){
    case t_toolbaritem:
      if (!s2.length()) toolbaritems.uniqueName(&s);
      toolbaritems.add(toolbaritems.count(), s, (_toolbaritem *) c);

      ((_toolbaritem *) c)->SETPROPERTY_Name(s);
      
      break;

  }

  return true;
}
_controlType controlType(_toolbaritem *c)
{
  return t_toolbaritem;
}

static _controlType static_controlType(_toolbaritem *c)
{
  return t_toolbaritem;
}



#ifdef IDE
QString getToolBarClassSourceCode(/*bool b = true*/)
{
  
  QString sAllText;
    QString s = _toolbar::getToolBarClassSourceCode(sFilename, sAllText, true);
   

    return s;
 

}

static QString getToolBarClassSourceCodeForSaving(QString sFileName)
{
  QString ss = "";
  int n = getToolBarClassSourceCodeFilePos(sFileName, &ss);
  ss = ss.mid(n);

  return ss;

}

static QString getToolBarClassSourceCode(QString sFileName, QString & sAllText, bool bAddHeader)
{
  QString ss = "";
  int n = getToolBarClassSourceCodeFilePos(sFileName, &ss);
  sAllText = ss;
  ss = ss.mid(n);

  QString g = "";
  if (bAddHeader){
    g = "\nClass ";
    g += _toolbar::getFilenameWithoutPathAndExtension(sFileName);
    g += " \n' ------------------------------------------------------------------------\n";
    g += "  \n";
    g += ss;
    g += "  \n";
    g += "' ------------------------------------------------------------------------\nEnd Class\n";
  } else {
    g = ss;
  }

  return g;


}


void openToolBarClassSourceCode()
{
  if (!EXTERN_my_mainwindow->isToolBarClassFileOpened(getFilename(), true)){
    EXTERN_my_mainwindow->openToolBarClassSourceCode(getFilename());
  }
}

bool saveToolBarControlsOnly(QString m)
{
  return saveToolbar(m);
}

static QString getToolBarItems(QString sFile);

static int getToolBarClassSourceCodeFilePos(QString m, QString *ss)
{
  QString s = "";
  int n = 0;

  QFile f2(m);
  if (!f2.open(QIODevice::ReadOnly )){
    return 0;
  } else {
	  QTextStream t(&f2);
    
    t.setCodec("UTF-8");
    t.setAutoDetectUnicode(true);
    t.setGenerateByteOrderMark(true);

	  *ss = t.readAll();
    *ss = (*ss).replace("\r", "");
    n = f2.size();
	  f2.close();
  }

  QString g = "End ToolBar";
  

  int n2 = (*ss).lastIndexOf(g, -1, Qt::CaseInsensitive);

  return n2 != -1 ? n2 + QString("End ToolBar").length() + 1 : n;
}

static bool saveToolBarClassSourceCodeOnly(QString m, QString k)
{
  //QString s = "";
  QString ss = "";

  int n = getToolBarClassSourceCodeFilePos(m, &ss);
 
  ss = ss.left(n);

  

  QFile f(m);
  if (!f.open(QIODevice::WriteOnly )){
    QMessageBox::information(EXTERN_my_mainwindow, MYAPP, QString("Could not read from %1").arg(m));
  } else {
    
    QTextStream t(&f);
    
    t.setCodec("UTF-8");
    t.setAutoDetectUnicode(true);
    t.setGenerateByteOrderMark(true);

    t << ss;
    t << k;
    f.resize(f.pos());
    f.close();
  }

  return true;
}



void closeEvent( QCloseEvent *e );

const QPixmap &loadPixmap(QString fn);

void incIndexFor(_toolbaritem *p, int nIndex);
void incIndexFor2(_toolbaritem *p, int nIndex);

void decIndexFor(_toolbaritem *p, int nIndex);


void setToolbarSelf()
{
  unselectAllControls();

  build();

  updatePropertyWindow();
}

_controlType insertType;
void setInsertControlType(_controlType t);


bool 		deleteControl(_toolbaritem *c)
{
  bool b = false;
  
  b = toolbaritems.del2((_toolbaritem *) c);
  if (b) return true;

  return false;
}

void event_INSERT_SELECT2(){ setInsertControlType(t_notype); }
void event_INSERT_TOOLBARITEM(){ setInsertControlType(t_toolbaritem); }
void event_INSERT_MOVE(){ setInsertControlType(t_move); }
void event_INSERT_DELETE(){ setInsertControlType(t_delete); }



void updateCaption(QString s)
{
  if (s.isEmpty()){
    s = tr("unnamed document");
  } else {
    s = getFilenameWithoutPath();
  }
  setWindowTitle(s);      

}

void load( const QString& fn)
{
  sFilename  = fn;

   QString q = EXTERN_my_mainwindow->trFilename(sFilename);
   if (QFile::exists(q)){
     loadToolbar(q);
   } else {
     loadToolbar(sFilename);
   }

  updateCaption(getFilenameWithoutPath());
  setNonModified();
}

void save()
{
  if (saveToolbar(EXTERN_my_mainwindow->trFilename(getFilename()))){  
    setNonModified();
  }
}

void saveAs()
{
    QString fn = QFileDialog::getSaveFileName(this, tr("SaveAs"), sFilename, QString::null);
    if (!fn.isEmpty()){
      QFile f(fn);

      if (f.exists()){
	      switch( QMessageBox::warning( this, tr("Save As"), 
	          tr("File %1 already exists. Do want to overwrite?").arg( fn ),
	          tr("Yes"), tr("No"), tr("Cancel") ) ) {
	        case 0:
            bool b = sFilename != fn;
            sFilename = fn;
            if (saveToolbar(fn)){
              setNonModified();
            }

	          break;
	      }
      } else {
        bool b = sFilename != fn;
        sFilename = fn;
        if (saveToolbar(fn)){
          setNonModified();
        }
      }

    }

  updateCaption(getFilenameWithoutPath());

}

void selectControl(_toolbaritem *c)
{
  bool b = c->acceptDrops();
  c->setAcceptDrops(!b); // missused as selected flag
}

void unselectControl(_toolbaritem *c)
{
  c->setAcceptDrops(false); // missused as selected flag
}

void selectControlAlways(_toolbaritem *c)
{
  c->setAcceptDrops(true); // missused as selected flag
}

void unselectAllControls()
{
  _toolbaritem *c;


  if (firstControl(&c)){

    do {
      c->setAcceptDrops(false); // missused as selected flag
    } while (nextControl(&c)); 

  }

}           


QString getFilename(){ return sFilename; }

QString getPath()
{ 
  QString s = sFilename;
  int i = s.lastIndexOf('/');
  if (i == -1) i = s.lastIndexOf('\\');
  s = s.left(i);
  return s; 
}

QString getFilenameWithoutPath(QString ss = "")
{ 
  QString s;

  if (ss == ""){
    s = sFilename;
  } else {
    s = ss;
  }

  int i = s.lastIndexOf('/');
  s = s.right(s.length() - i - 1);
  return s; 
}

QString getFilenameWithoutPathAndExtension()
{ 
  QString s;

  s = sFilename;

  int i = s.lastIndexOf('/');
  s = s.right(s.length() - i - 1);

  i = s.lastIndexOf('.');
  s = s.left(i);
  return s; 
}

static QString getFilenameWithoutPathAndExtension(QString ss)
{ 
  QString s;
  s = ss;

  int i = s.lastIndexOf('/');
  s = s.right(s.length() - i - 1);

  i = s.lastIndexOf('.');
  s = s.left(i);
  return s; 
}

void focusInEvent(QFocusEvent *e);

#endif

public:
bool firstControl(_toolbaritem **c)
{
  bool b = false;  

  toolbaritems.reset();
  
  b = toolbaritems.first((_toolbaritem**) c);
  if (b){ return true; }

  return false;
}

bool nextControl(_toolbaritem **c)
{ 
  bool b = false;
    
  // TOOLBAR_CONTROL // CONTROL
  
  b = toolbaritems.next((_toolbaritem**) c);
  if (b){ return true; }

  return false;
}
private:
QString sFilename;

_toolbaritems toolbaritems;

#ifdef IDE
bool isModified();
void setNonModified();
bool bModified;

_qtoolbar *my_qtoolbar;
#endif

#ifdef RUN
interpreter *myInterpreter;

public:
QMap<QString, QString> menusForButtons;

#endif


};


#endif