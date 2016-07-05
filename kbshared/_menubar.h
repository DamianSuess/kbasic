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


#ifndef _menubar_H
#define _menubar_H

#include <QtGui>

#include "../kbshared/typedef.h"
#include "../kbshared/_property.h"

#include "../kbshared/_menubaritem.h"

extern _menubaritem *currentMenu;
extern _menubaritem *currentMenuItem;

class _menubar;
extern _menubar *EXTERN_my_menubar;

#ifdef IDE

extern QAction *my_qaction;


class _mainwindow;
extern _mainwindow *EXTERN_my_mainwindow;
extern _menubar *EXTERN_my_menubar;

#endif


class _menubar;
class interpreter;

#ifdef IDE
class _qmenubar : public QMenuBar
{
  Q_OBJECT
public:
  _qmenubar (QWidget * p, _menubar *_my_menubar2 ) : QMenuBar(p)
  {
    my_menubar = _my_menubar2;

    bMousePressed = false;
    bMouseReleased = false;

    bMousePressed2 = false;
    bMouseReleased2 = false;

    bMousePressed3 = false;
    connect(this, SIGNAL(hovered(QAction *)), this, SLOT(hovered(QAction *)));

  }

public slots:

void hovered(QAction *action);


public:
  void mousePressEvent ( QMouseEvent * e )
  {
    if (e->button() == Qt::RightButton){
      bMousePressed2 = true;
    }

    
    if (bMousePressed == false){
      bMousePressed3 = true; 
      //printf("BBB ");
    } else {
      bMousePressed3 = false; 
    }
    

    bMousePressed = true;

    QMenuBar::mousePressEvent(e);
  }

  void mouseMoveEvent ( QMouseEvent * e )
  {

    if (bMousePressed == false){
    }

    QMenuBar::mouseMoveEvent(e);
  }

  void mouseReleaseEvent ( QMouseEvent * e );

  bool mousePressEvent()
  {
    return bMousePressed;
  }

  bool mousePressEvent2()
  {
    return bMousePressed3;
  }

  bool mouseReleaseEvent()
  {
    return bMouseReleased;
  }


void  paintEvent( QPaintEvent *event )
{
  QMenuBar::paintEvent(event);

  QPainter paint( this );



  QRect r = event->rect();

  paint.setPen(Qt::gray);

  for (int y = 0; y < r.bottom() + 11; y += 10){
    for (int x = 0; x < r.right() + 11; x += 10){
        paint.drawPoint(x, y);
    }
  }
  if (actions().count() == 0){
    paint.setPen(Qt::black);
    paint.drawText (5, 16, "MenuBar");
  }

}
private:
  bool bMousePressed;
  bool bMouseReleased;

  bool bMousePressed2;
  bool bMouseReleased2;

  bool bMousePressed3;

  _menubar *my_menubar;

};


#endif
class _qmenu : public QMenu
{

public:
  _qmenu ( QWidget *p, _menubar *mb) : QMenu(p)
  {
    my_menubar = mb;

    bMousePressed = false;
    bMouseReleased = false;
  }

  void mousePressEvent ( QMouseEvent * e )
  {
    bMousePressed = true;    

    if (e->button() == Qt::LeftButton){
      QMenu::mousePressEvent(e);
    }
  }

  void mouseReleaseEvent ( QMouseEvent * e );

  bool mousePressEvent()
  {
    return bMousePressed;
  }

  bool mouseReleaseEvent()
  {
    return bMouseReleased;
  }

#ifdef IDE
  void  paintEvent( QPaintEvent *event )
  {
    QMenu::paintEvent(event);

    QPainter paint( this );

    QRect r = event->rect();
    paint.setPen(Qt::gray);

    for (int y = 0; y < r.bottom() + 11; y += 10){
      for (int x = 0; x < r.right() + 11; x += 10){
      
       paint.drawPoint(x, y);
      }
    }
  }
#endif

private:
  bool bMousePressed;
  bool bMouseReleased;

  _menubar *my_menubar;
  
};

class kb_menubaritem;



#ifdef IDE
class _menubar : public QWidget
#endif
#ifdef RUN
extern QString sCurrentLanguage;

class _menubar : public QMenuBar
#endif
{
  Q_OBJECT
public:

#ifdef IDE
_menubar(_mainwindow *_my_mainwindow);
#endif
#ifdef RUN
_menubar(_form *f = 0);
#endif


#ifdef RUN

bool isEmpty()
{
  _menubaritem *c;

  if (firstControl(&c)){
    return false;
  }
  return true;
}

QString loadProjectFile (QString sFile);
t_pointer loadProjectFile(QString s, t_integer *nSize);
QPixmap loadProjectImage(QString sFile);

void buildMenu(_qmenu *pm = 0, _menubaritem* _parent = 0, int _nItIndex = 0);
QAction *insertItem(_qmenu *qp, _menubaritem *m, int nIndex);

void METHOD_2SetWithTag(QString Tag, QString PropertyName, t_boolean b);
void METHOD_2SetWithTag(QString Tag, QString PropertyName, t_integer n);
void METHOD_2SetWithTag(QString Tag, QString PropertyName, QString s);

void METHOD_2SetWithGroup(QString Group, QString PropertyName, t_boolean b);
void METHOD_2SetWithGroup(QString Group, QString PropertyName, t_integer n);
void METHOD_2SetWithGroup(QString Group, QString PropertyName, QString s);


static void METHOD_SetWithTag(QString Tag, QString PropertyName, t_boolean b);
static void METHOD_SetWithTag(QString Tag, QString PropertyName, t_integer n);
static void METHOD_SetWithTag(QString Tag, QString PropertyName, QString s);

static void METHOD_SetWithGroup(QString Group, QString PropertyName, t_boolean b);
static void METHOD_SetWithGroup(QString Group, QString PropertyName, t_integer n);
static void METHOD_SetWithGroup(QString Group, QString PropertyName, QString s);



static void METHOD_SetEnabled(QString ActionId, t_boolean Value)
{
  _menubaritem *c;

  if (EXTERN_my_menubar && EXTERN_my_menubar->firstControl(&c)){

    do {

      if (c->GETPROPERTY_ActionId().compare(ActionId, Qt::CaseInsensitive) == 0){

        #define SWITCH_STATIC static
        #define SWITCH SETPROPERTY_Enabled(Value);
        #include "_menubar_property_switch.h"  
        #undef SWITCH_STATIC

        return;

      }

    } while (EXTERN_my_menubar->nextControl(&c)); 
  }

}

static t_boolean METHOD_IsEnabled(QString ActionId)
{

  _menubaritem *c;

  if (EXTERN_my_menubar && EXTERN_my_menubar->firstControl(&c)){    
   
    do {

      if (c->GETPROPERTY_ActionId().compare(ActionId, Qt::CaseInsensitive) == 0){

        bool bb = false;
        
        #define SWITCH_STATIC ?
        #define SWITCH3 bb
        #define SWITCH GETPROPERTY_Enabled();
        #include "_menubar_property_switch.h" 
        #undef SWITCH3
        #undef SWITCH_STATIC

        return bb;

      }

    } while (EXTERN_my_menubar->nextControl(&c)); 
  }

  return false;
}

static void METHOD_SetVisible(QString ActionId, t_boolean Value)
{
  _menubaritem *c;

  if (EXTERN_my_menubar && EXTERN_my_menubar->firstControl(&c)){

    do {

      if (c->GETPROPERTY_ActionId().compare(ActionId, Qt::CaseInsensitive) == 0){

        #define SWITCH_STATIC static
        #define SWITCH SETPROPERTY_Visible(Value);
        #include "_menubar_property_switch.h"  
        #undef SWITCH_STATIC

        return;

      }

    } while (EXTERN_my_menubar->nextControl(&c)); 
  }
}

static t_boolean METHOD_IsVisible(QString ActionId)
{
  _menubaritem *c;

  if (EXTERN_my_menubar && EXTERN_my_menubar->firstControl(&c)){    
   
    do {

      if (c->GETPROPERTY_ActionId().compare(ActionId, Qt::CaseInsensitive) == 0){

        bool bb = false;
        
        #define SWITCH_STATIC ?
        #define SWITCH3 bb
        #define SWITCH GETPROPERTY_Visible();
        #include "_menubar_property_switch.h" 
        #undef SWITCH3
        #undef SWITCH_STATIC

        return bb;

      }

    } while (EXTERN_my_menubar->nextControl(&c)); 
  }

  return false;
}

static void METHOD_SetChecked(QString ActionId, t_boolean Value)
{
  _menubaritem *c;

  if (EXTERN_my_menubar && EXTERN_my_menubar->firstControl(&c)){

    do {

      if (c->GETPROPERTY_ActionId().compare(ActionId, Qt::CaseInsensitive) == 0){

        #define SWITCH_STATIC static
        #define SWITCH SETPROPERTY_Checked(Value);
        #include "_menubar_property_switch.h"  
        #undef SWITCH_STATIC

        return;

      }

    } while (EXTERN_my_menubar->nextControl(&c)); 
  }
}

static t_boolean METHOD_IsChecked(QString ActionId)
{
  _menubaritem *c;

  if (EXTERN_my_menubar && EXTERN_my_menubar->firstControl(&c)){    
   
    do {

      if (c->GETPROPERTY_ActionId().compare(ActionId, Qt::CaseInsensitive) == 0){

        bool bb = false;
        
        #define SWITCH_STATIC ?
        #define SWITCH3 bb
        #define SWITCH GETPROPERTY_Checked();
        #include "_menubar_property_switch.h" 
        #undef SWITCH3
        #undef SWITCH_STATIC

        return bb;

      }

    } while (EXTERN_my_menubar->nextControl(&c)); 
  }

  return false;
}

static void METHOD_SetStatusTip(QString ActionId, QString Value)
{
  _menubaritem *c;

  if (EXTERN_my_menubar && EXTERN_my_menubar->firstControl(&c)){

    do {

      if (c->GETPROPERTY_ActionId().compare(ActionId, Qt::CaseInsensitive) == 0){

        #define SWITCH_STATIC static
        #define SWITCH SETPROPERTY_StatusTip(Value);
        #include "_menubar_property_switch.h"  
        #undef SWITCH_STATIC

        return;

      }

    } while (EXTERN_my_menubar->nextControl(&c)); 
  }
}

static QString METHOD_StatusTip(QString ActionId)
{
  _menubaritem *c;

  if (EXTERN_my_menubar && EXTERN_my_menubar->firstControl(&c)){    
   
    do {

      if (c->GETPROPERTY_ActionId().compare(ActionId, Qt::CaseInsensitive) == 0){

        QString bb = "";
        
        #define SWITCH_STATIC ?
        #define SWITCH3 bb
        #define SWITCH GETPROPERTY_StatusTip();
        #include "_menubar_property_switch.h" 
        #undef SWITCH3
        #undef SWITCH_STATIC

        return bb;

      }

    } while (EXTERN_my_menubar->nextControl(&c)); 
  }

  return "";
}

static void METHOD_SetToolTip(QString ActionId, QString Value)
{
  _menubaritem *c;

  if (EXTERN_my_menubar && EXTERN_my_menubar->firstControl(&c)){

    do {

      if (c->GETPROPERTY_ActionId().compare(ActionId, Qt::CaseInsensitive) == 0){

        #define SWITCH_STATIC static
        #define SWITCH SETPROPERTY_ToolTip(Value);
        #include "_menubar_property_switch.h"  
        #undef SWITCH_STATIC

        return;

      }

    } while (EXTERN_my_menubar->nextControl(&c)); 
  }
}

static QString METHOD_ToolTip(QString ActionId)
{
  _menubaritem *c;

  if (EXTERN_my_menubar && EXTERN_my_menubar->firstControl(&c)){    
   
    do {

      if (c->GETPROPERTY_ActionId().compare(ActionId, Qt::CaseInsensitive) == 0){

        QString bb = "";
        
        #define SWITCH_STATIC ?
        #define SWITCH3 bb
        #define SWITCH GETPROPERTY_ToolTip();
        #include "_menubar_property_switch.h" 
        #undef SWITCH3
        #undef SWITCH_STATIC

        return bb;

      }

    } while (EXTERN_my_menubar->nextControl(&c)); 
  }

  return "";
}

static void METHOD_SetWhatsThis(QString ActionId, QString Value)
{
  _menubaritem *c;

  if (EXTERN_my_menubar && EXTERN_my_menubar->firstControl(&c)){

    do {

      if (c->GETPROPERTY_ActionId().compare(ActionId, Qt::CaseInsensitive) == 0){

        #define SWITCH_STATIC static
        #define SWITCH SETPROPERTY_WhatsThis(Value);
        #include "_menubar_property_switch.h"  
        #undef SWITCH_STATIC

        return;

      }

    } while (EXTERN_my_menubar->nextControl(&c)); 
  }
}

static QString METHOD_WhatsThis(QString ActionId)
{
  _menubaritem *c;

  if (EXTERN_my_menubar && EXTERN_my_menubar->firstControl(&c)){    
   
    do {

      if (c->GETPROPERTY_ActionId().compare(ActionId, Qt::CaseInsensitive) == 0){

        QString bb = "";
        
        #define SWITCH_STATIC ?
        #define SWITCH3 bb
        #define SWITCH GETPROPERTY_WhatsThis();
        #include "_menubar_property_switch.h" 
        #undef SWITCH3
        #undef SWITCH_STATIC

        return bb;

      }

    } while (EXTERN_my_menubar->nextControl(&c)); 
  }

  return "";
}

static void METHOD_SetIcon(QString ActionId, QString Value)
{
  _menubaritem *c;

  if (EXTERN_my_menubar && EXTERN_my_menubar->firstControl(&c)){

    do {

      if (c->GETPROPERTY_ActionId().compare(ActionId, Qt::CaseInsensitive) == 0){

        #define SWITCH_STATIC static
        #define SWITCH SETPROPERTY_Icon(Value);
        #include "_menubar_property_switch.h"  
        #undef SWITCH_STATIC

        return;

      }

    } while (EXTERN_my_menubar->nextControl(&c)); 
  }
}

static QString METHOD_Icon(QString ActionId)
{
  _menubaritem *c;

  if (EXTERN_my_menubar && EXTERN_my_menubar->firstControl(&c)){    
   
    do {

      if (c->GETPROPERTY_ActionId().compare(ActionId, Qt::CaseInsensitive) == 0){

        QString bb = "";
        
        #define SWITCH_STATIC ?
        #define SWITCH3 bb
        #define SWITCH GETPROPERTY_Icon();
        #include "_menubar_property_switch.h" 
        #undef SWITCH3
        #undef SWITCH_STATIC

        return bb;

      }

    } while (EXTERN_my_menubar->nextControl(&c)); 
  }

  return "";
}

static void METHOD_SetTag(QString ActionId, QString Value)
{
  _menubaritem *c;

  if (EXTERN_my_menubar && EXTERN_my_menubar->firstControl(&c)){

    do {

      if (c->GETPROPERTY_ActionId().compare(ActionId, Qt::CaseInsensitive) == 0){

        #define SWITCH_STATIC static
        #define SWITCH SETPROPERTY_Tag(Value);
        #include "_menubar_property_switch.h"  
        #undef SWITCH_STATIC

        return;

      }

    } while (EXTERN_my_menubar->nextControl(&c)); 
  }
}

static QString METHOD_Tag(QString ActionId)
{
  _menubaritem *c;

  if (EXTERN_my_menubar && EXTERN_my_menubar->firstControl(&c)){    
   
    do {

      if (c->GETPROPERTY_ActionId().compare(ActionId, Qt::CaseInsensitive) == 0){

        QString bb = "";
        
        #define SWITCH_STATIC ?
        #define SWITCH3 bb
        #define SWITCH GETPROPERTY_Tag();
        #include "_menubar_property_switch.h" 
        #undef SWITCH3
        #undef SWITCH_STATIC

        return bb;

      }

    } while (EXTERN_my_menubar->nextControl(&c)); 
  }

  return "";
}


static void METHOD_SetCaption(QString ActionId, QString Value)
{
  _menubaritem *c;

  if (EXTERN_my_menubar && EXTERN_my_menubar->firstControl(&c)){

    do {

      if (c->GETPROPERTY_ActionId().compare(ActionId, Qt::CaseInsensitive) == 0){

        #define SWITCH_STATIC static
        #define SWITCH SETPROPERTY_Caption(Value);
        #include "_menubar_property_switch.h"  
        #undef SWITCH_STATIC

        return;

      }

    } while (EXTERN_my_menubar->nextControl(&c)); 
  }
}

static QString METHOD_Caption(QString ActionId)
{
  _menubaritem *c;

  if (EXTERN_my_menubar && EXTERN_my_menubar->firstControl(&c)){    
   
    do {

      if (c->GETPROPERTY_ActionId().compare(ActionId, Qt::CaseInsensitive) == 0){

        QString bb = "";
        
        #define SWITCH_STATIC ?
        #define SWITCH3 bb
        #define SWITCH GETPROPERTY_Caption();
        #include "_menubar_property_switch.h" 
        #undef SWITCH3
        #undef SWITCH_STATIC

        return bb;

      }

    } while (EXTERN_my_menubar->nextControl(&c)); 
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
  _menubaritem *c;

  if (EXTERN_my_menubar && EXTERN_my_menubar->firstControl(&c)){

    do {

      if (c->GETPROPERTY_ActionId().compare(ActionId, Qt::CaseInsensitive) == 0){

        #define SWITCH_STATIC static
        #define SWITCH SETPROPERTY_SoundOnEvent(Value);
        #include "_menubar_property_switch.h"  
        #undef SWITCH_STATIC

        return;

      }

    } while (EXTERN_my_menubar->nextControl(&c)); 
  }
}

static QString METHOD_SoundOnEvent(QString ActionId)
{
  _menubaritem *c;

  if (EXTERN_my_menubar && EXTERN_my_menubar->firstControl(&c)){    
   
    do {

      if (c->GETPROPERTY_ActionId().compare(ActionId, Qt::CaseInsensitive) == 0){

        QString bb = "";
        
        #define SWITCH_STATIC ?
        #define SWITCH3 bb
        #define SWITCH GETPROPERTY_SoundOnEvent();
        #include "_menubar_property_switch.h" 
        #undef SWITCH3
        #undef SWITCH_STATIC

        return bb;

      }

    } while (EXTERN_my_menubar->nextControl(&c)); 
  }

  return "";
}

static void METHOD_SetGroup(QString ActionId, QString Value)
{
  _menubaritem *c;

  if (EXTERN_my_menubar && EXTERN_my_menubar->firstControl(&c)){

    do {

      if (c->GETPROPERTY_ActionId().compare(ActionId, Qt::CaseInsensitive) == 0){

        #define SWITCH_STATIC static
        #define SWITCH SETPROPERTY_Group(Value);
        #include "_menubar_property_switch.h"  
        #undef SWITCH_STATIC

        return;

      }

    } while (EXTERN_my_menubar->nextControl(&c)); 
  }
}

static QString METHOD_Group(QString ActionId)
{
  _menubaritem *c;

  if (EXTERN_my_menubar && EXTERN_my_menubar->firstControl(&c)){    
   
    do {

      if (c->GETPROPERTY_ActionId().compare(ActionId, Qt::CaseInsensitive) == 0){

        QString bb = "";
        
        #define SWITCH_STATIC ?
        #define SWITCH3 bb
        #define SWITCH GETPROPERTY_Group();
        #include "_menubar_property_switch.h" 
        #undef SWITCH3
        #undef SWITCH_STATIC

        return bb;

      }

    } while (EXTERN_my_menubar->nextControl(&c)); 
  }

  return "";
}


static void METHOD_SetKey(QString ActionId, QString Value)
{
  _menubaritem *c;

  if (EXTERN_my_menubar && EXTERN_my_menubar->firstControl(&c)){

    do {

      if (c->GETPROPERTY_ActionId().compare(ActionId, Qt::CaseInsensitive) == 0){

        #define SWITCH_STATIC static
        #define SWITCH SETPROPERTY_Key(Value);
        #include "_menubar_property_switch.h"  
        #undef SWITCH_STATIC

        return;

      }

    } while (EXTERN_my_menubar->nextControl(&c)); 
  }
}

static QString METHOD_Key(QString ActionId)
{
  _menubaritem *c;

  if (EXTERN_my_menubar && EXTERN_my_menubar->firstControl(&c)){    
   
    do {

      if (c->GETPROPERTY_ActionId().compare(ActionId, Qt::CaseInsensitive) == 0){

        QString bb = "";
        
        #define SWITCH_STATIC ?
        #define SWITCH3 bb
        #define SWITCH GETPROPERTY_Key();
        #include "_menubar_property_switch.h" 
        #undef SWITCH3
        #undef SWITCH_STATIC

        return bb;

      }

    } while (EXTERN_my_menubar->nextControl(&c)); 
  }

  return "";
}


static kb_menubaritem *METHOD_MenuBarItem(const QString & Name);
static void METHOD_SetVisible(t_boolean b);
static t_boolean METHOD_IsVisible();

static void METHOD_Show();
static void METHOD_Hide();
static void METHOD_ToggleVisible();

static void METHOD_Remove(QString MenuBarItemName);
static void METHOD_RemoveAll();

static void removeAllChilds(_menubaritem *Parent);

static void METHOD_RemoveAllChilds(QString MenuBarItemName);

static void METHOD_AppendMenuBarItem(QString ParentMenuBarItemName, _menubaritem *MenuBarItem);

static void METHOD_AppendMenuBarItem(_menubaritem *MenuBarItem);

//static void METHOD_AppendSeparator(QString ParentMenuBarItemName);

static void METHOD_AppendMenu(_menubaritem *MenuBarItem);

static void METHOD_AppendMenu1(QString ParentMenuBarItemName, _menubaritem *MenuBarItem);

static void METHOD_AppendChildMenu(QString ParentMenuBarItemName, _menubaritem *MenuBarItem);

static void METHOD_AppendChildMenu(_menubaritem *MenuBarItem);


static void METHOD_AppendContextMenu(_menubaritem *MenuBarItem);
static void METHOD_ShowContextMenu(QString MenuBarItemName, int X, int Y);
static void METHOD_ShowContextMenu(int X, int Y);




#endif

#include "_menubar_property.h"
#include "_menubar_loadsave.h"

#ifdef RUN

void aboutToHide(QAction *action);
void aboutToShow(QAction *action);

public slots:
void hovered(QAction *action);
void triggered(QAction *action);
void aboutToHide();
void aboutToShow();
#endif

//void triggered(QAction *action);

public:

#ifdef RUN
const char *acName;  
const char *acGroup;
virtual void EVENT_OnEvent();
#endif

_menubaritem *getParent(QString s);
t_boolean METHOD_insertControl(_menubaritem *c, _controlType controlType, QString s2 = "")
{
  QString s = s2; 

  switch(controlType){
    case t_menu:
    case t_menubaritem:
    case t_submenu:
      if (!s2.length()) menubaritems.uniqueName(&s);
      menubaritems.add(menubaritems.count(), s, (_menubaritem *) c);

      ((_menubaritem *) c)->SETPROPERTY_Name(s);
      ((_menubaritem *) c)->SETPROPERTY_Caption(s);
      break;

  }

  return true;
}
_controlType controlType(_menubaritem *c)
{
  return t_menubaritem;
}

static _controlType static_controlType(_menubaritem *c)
{
  return t_menubaritem;
}

_menubaritem *getMenuBarItemByAction(QAction *a, bool bParent = true);

#ifdef IDE


bool existsParent(_menubaritem *cc, int nItIndex = 0);

void addNewToMenu();
void addNewToMenu2();

void buildMenu(_qmenu *pm = 0, _menubaritem* _parent = 0, int _nItIndex = 0, bool bActivate = true);
void buildMenu2(bool bActivate);

bool hasChilds(_qmenu *pm);

QAction *insertItem(/*_qmenubar *qm, */_qmenu *qp, _menubaritem *m/*QString s, _qmenu *child*/, int nIndex);


QString getMenuBarClassSourceCode(/*bool b = true*/)
{
  
    QString sAllText;
    QString s = _menubar::getMenuBarClassSourceCode(sFilename, sAllText, true);
 

    return s;


}


static QString getMenuBarClassSourceCodeForSaving(QString sFileName)
{
  QString ss = "";
  int n = getMenuBarClassSourceCodeFilePos(sFileName, &ss);
  ss = ss.mid(n);

  return ss;

}

static QString getMenuBarClassSourceCode(QString sFileName, QString & sAllText, bool bAddHeader)
{
  QString ss = "";
  int n = getMenuBarClassSourceCodeFilePos(sFileName, &ss);
  sAllText = ss;
  ss = ss.mid(n);

  QString g = "";

  if (bAddHeader){

    g = "\nClass ";
    g += _menubar::getFilenameWithoutPathAndExtension(sFileName);
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


void openMenuBarClassSourceCode()
{
  if (!EXTERN_my_mainwindow->isMenuBarClassFileOpened(getFilename(), true)){
    EXTERN_my_mainwindow->openMenuBarClassSourceCode(getFilename());
  }
}

bool saveMenuBarControlsOnly(QString m)
{
  return saveMenubar(m);
}

static QString getMenuBarItems(QString sFile);

static int getMenuBarClassSourceCodeFilePos(QString m, QString *ss)
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
    n = f2.size();
	  f2.close();
  }

  QString g = "End MenuBar";

  int n2 = (*ss).lastIndexOf(g, -1, Qt::CaseInsensitive);

  return n2 != -1 ? n2 + QString("End MenuBar").length() + 1 : n;
}

static bool saveMenuBarClassSourceCodeOnly(QString m, QString k)
{
  //QString s = "";
  QString ss = "";

  int n = getMenuBarClassSourceCodeFilePos(m, &ss);
 // s = ss;
  ss = ss.left(n);

  //ss = ss.mid(n);

  QFile f(m);
  if (!f.open(QIODevice::WriteOnly )){
    QMessageBox::information(EXTERN_my_mainwindow, MYAPP, QString("Could not read from %1").arg(m));
  } else {
    //f.seek(n);
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

_menubaritem *getRootParent(_menubaritem *p);


void updateMenuBar(bool bActivate = true);
void closeEvent( QCloseEvent *e );

const QPixmap &loadPixmap(QString fn);

void incIndexFor(_menubaritem *p, int nIndex);
void incIndexFor2(_menubaritem *p, int nIndex);
void decIndexFor(_menubaritem *p, int nIndex);

void select();
void move();
void del();

void setMenubarSelf()
{
  unselectAllControls();

  buildMenu();

  if (currentMenu){
    my_qmenubar->setActiveAction(currentMenu->my_qaction);

  }


  updatePropertyWindow();
}

_controlType insertType;
void setInsertControlType(_controlType t);



bool 		deleteControl(_menubaritem *c)
{
  bool b = false;
  
  b = menubaritems.del2((_menubaritem *) c);
  if (b) return true;

  return false;
}

void event_INSERT_SELECT2(){ setInsertControlType(t_notype); }
void event_INSERT_MENU(){ setInsertControlType(t_menu); }
void event_INSERT_CHILDMENU(){ setInsertControlType(t_submenu); }
void event_INSERT_MENUBARITEM(){ setInsertControlType(t_menubaritem); }
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
     loadMenubar(q);
   } else {
     loadMenubar(sFilename);
   }
  
  updateCaption(getFilenameWithoutPath());
  setNonModified();
}

void save()
{
  if (saveMenubar(EXTERN_my_mainwindow->trFilename(getFilename()))){    
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
            if (saveMenubar(fn)){
              setNonModified();
            }

	          break;
	      }
      } else {
        bool b = sFilename != fn;
        sFilename = fn;
        if (saveMenubar(fn)){
          setNonModified();
         }
      }
  
    }
 
  updateCaption(getFilenameWithoutPath());

}

void selectControl(_menubaritem *c)
{
  bool b = c->acceptDrops();
  c->setAcceptDrops(!b); // missused as selected flag
}

void unselectControl(_menubaritem *c)
{
  c->setAcceptDrops(false); // missused as selected flag
}

void selectControlAlways(_menubaritem *c)
{
  c->setAcceptDrops(true); // missused as selected flag
}

void unselectAllControls()
{
  _menubaritem *c;

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
bool firstControl(_menubaritem **c, int nIndex = 0)
{
  bool b = false;  

  menubaritems.reset();
  
  b = menubaritems.first((_menubaritem**) c, nIndex);
  if (b){ return true; }

  return false;
}

bool nextControl(_menubaritem **c, int nIndex = 0)
{ 
  bool b = false;
    
  // MENUBAR_CONTROL // CONTROL
  
  b = menubaritems.next((_menubaritem**) c, nIndex);
  if (b){ return true; }

  return false;
}

private:
QString sFilename;

_menubaritems menubaritems;

_qmenubar *my_qmenubar;

bool bSelected;

#ifdef IDE
bool isModified();
void setNonModified();
bool bModified;
#endif

#ifdef RUN
interpreter *myInterpreter;
_form *my_form;
#endif



};


#endif