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

#include "_menubar.h"

_menubar *EXTERN_my_menubar;




#ifdef RUN
#include "../kbasic_binding/_menubaritem/kb_menubaritem.h"

QMap<QString, QActionGroup*>actiongroups;


QString sLastUsedMenu;
#endif

#ifdef IDE


extern QDockWidget *EXTERN_ToolboxForm;
extern QDockWidget *EXTERN_ToolboxReport;
extern QDockWidget *EXTERN_ToolboxMenuBar;
extern QDockWidget *EXTERN_ToolboxToolBar;
extern QDockWidget *EXTERN_Helpwindow_shortcut;

#include "../kbide/_mainwindow.h"
#include "../kbide/_propertywindow.h"
#include "../kbide/_helpwindow_shortcut.h"
#include "../kbide/_sourcecodeeditor.h"
#include "../kbide/_help.h"

extern int nPropertyWindowForWhat;
//extern _helpwindow *EXTERN_my_helpwindow;
#endif



_menubaritem *_menubar::getMenuBarItemByAction(QAction *a, bool b)
{
  
  _menubaritem *c;
  _menubaritem *m;

  if (firstControl(&c)){
   
    do {

      m = (_menubaritem *) c;

      if (m->my_qaction == a){
        if (b && m->parent != 0){
          return m->parent;
        } else {
          return m;
        }
      }

    } while (nextControl(&c)); 
  }

  return 0;
}


#ifdef RUN

#include "../kbrun/interpreter.h"

_menubaritem *currentMenu;
_menubaritem *currentMenuItem;


_menubar::_menubar(_form *f)
{
  my_form = f;


  connect(this, SIGNAL(triggered(QAction *)), this, SLOT(triggered(QAction *)));
  connect(this, SIGNAL(hovered(QAction *)), this, SLOT(hovered(QAction *)));
/*
        QWidget *w = this;//->parentWidget();
        w->setAutoFillBackground(true);
        QPalette p = w->palette();
        QColor c = QColor(0, 0, 0, 55 * 2.55);
        p.setColor(QPalette::Window, c);  
        w->setPalette(p);*/
}

QString _menubar::loadProjectFile (QString sFile) 
{
  return  QString::fromUtf8(myInterpreter->loadProjectFile(sFile));
}

t_pointer _menubar::loadProjectFile(QString sFile, t_integer *nSize)
{
    return myInterpreter->loadProjectFile(sFile, nSize);
}

QPixmap _menubar::loadProjectImage(QString sFile)
{
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

typedef QVector<_menubaritem*>items;
QMap<_qmenu*, items*>sorted_actions;

kb_menubaritem *_menubar::METHOD_MenuBarItem(const QString & Name)
{
  if (EXTERN_my_menubar == 0){ EXTERN_myInterpreter->runtimeError("no menubar object created"); return 0; }

  _menubaritem *c;

  if (EXTERN_my_menubar->firstControl(&c)){
   
    do {

      if (c->GETPROPERTY_Name().compare(Name, Qt::CaseInsensitive) == 0){
        return (kb_menubaritem *) c;
      }

    } while (EXTERN_my_menubar->nextControl(&c)); 
  }

  return 0;
}

void _menubar::METHOD_SetVisible(t_boolean b)
{
  if (EXTERN_my_menubar == 0){ EXTERN_myInterpreter->runtimeError("no menubar object created"); return; }

  EXTERN_my_menubar->setHidden(!b);
}

t_boolean _menubar::METHOD_IsVisible()
{
  if (EXTERN_my_menubar == 0){ EXTERN_myInterpreter->runtimeError("no menubar object created"); return 0; }

  return !EXTERN_my_menubar->isHidden();
}

void _menubar::METHOD_Show()
{
  if (EXTERN_my_menubar == 0){ EXTERN_myInterpreter->runtimeError("no menubar object created"); return; }

  EXTERN_my_menubar->show();
}

void _menubar::METHOD_Hide()
{
  if (EXTERN_my_menubar == 0){ EXTERN_myInterpreter->runtimeError("no menubar object created"); return; }

  EXTERN_my_menubar->hide();
}

void _menubar::METHOD_ToggleVisible()
{
  if (EXTERN_my_menubar == 0){ EXTERN_myInterpreter->runtimeError("no menubar object created"); return; }

  EXTERN_my_menubar->setHidden(!EXTERN_my_menubar->isHidden());
}

// used for context menu only
void _menubar::METHOD_Remove(QString MenuBarItemName)
{
  if (EXTERN_my_menubar == 0){ EXTERN_myInterpreter->runtimeError("no menubar object created"); return; }
  
  QAction *my_qaction = 0;
  bool b = false;

  _menubaritem *c;

  if (EXTERN_my_menubar->firstControl(&c)){
   
    do {

      if (c->GETPROPERTY_Name().compare(MenuBarItemName, Qt::CaseInsensitive) == 0){
        b = true;
        break;
      }

    } while (EXTERN_my_menubar->nextControl(&c)); 
  }

  if (!b) return;

  METHOD_RemoveAllChilds(MenuBarItemName);
  EXTERN_my_menubar->menubaritems.del(MenuBarItemName);
 
}

void _menubar::METHOD_RemoveAll()
{
  if (EXTERN_my_menubar == 0){ EXTERN_myInterpreter->runtimeError("no menubar object created"); return; }

  EXTERN_my_menubar->menubaritems.clear();
  EXTERN_my_menubar->clear();
}

QList<_menubaritem *>DeleteList;




void _menubar::removeAllChilds(_menubaritem *Parent)
{
  static int IT = -1;

  IT++;

  _menubaritem *c;

  if (EXTERN_my_menubar->firstControl(&c, IT)){
   
    do {

      if (c->parent == Parent){        
        DeleteList.append(c);
        removeAllChilds(c);
      }

    } while (EXTERN_my_menubar->nextControl(&c, IT)); 
  }
  IT--;
}

void _menubar::METHOD_RemoveAllChilds(QString MenuBarItemName)
{
  if (EXTERN_my_menubar == 0){ EXTERN_myInterpreter->runtimeError("no menubar object created"); return; }

  QAction *my_qaction = 0;

  _menubaritem *c;

  bool b = false;

  if (EXTERN_my_menubar->firstControl(&c)){
   
    do {

      if (c->GETPROPERTY_Name().compare(MenuBarItemName, Qt::CaseInsensitive) == 0){
        b = true;
        break;
      }

    } while (EXTERN_my_menubar->nextControl(&c)); 
  }

  if (b == false) return;

    DeleteList.clear();
 
  removeAllChilds(c);
  sLastUsedMenu = c->GETPROPERTY_Name();

  int nCount = DeleteList.size();

  _qmenu *my_qmenu = (_qmenu *) c->my_qmenu;
  if (my_qmenu) my_qmenu->clear(); 

  foreach(_menubaritem *it, DeleteList){
    QString s = it->GETPROPERTY_Name();
    it->my_qaction = 0; // qaction has been altered by qt: set to zero, otherwise it crashes
    EXTERN_my_menubar->menubaritems.del(s);
  }
    
}


void _menubar::METHOD_AppendMenuBarItem(_menubaritem *MenuBarItem)
{
  if (EXTERN_my_menubar == 0){ EXTERN_myInterpreter->runtimeError("no menubar object created"); return; }

  METHOD_AppendMenuBarItem(sLastUsedMenu, MenuBarItem);
}

void _menubar::METHOD_AppendMenuBarItem(QString ParentMenuBarItemName, _menubaritem *MenuBarItem)
{
  if (EXTERN_my_menubar == 0){ EXTERN_myInterpreter->runtimeError("no menubar object created"); return; }

  _menubaritem *ParentMenuBarItem = EXTERN_my_menubar->getParent(ParentMenuBarItemName);
  if (ParentMenuBarItem){
    if (EXTERN_my_menubar->getParent(MenuBarItem->GETPROPERTY_Name())) return;
    sLastUsedMenu = ParentMenuBarItemName;
    EXTERN_my_menubar->menubaritems.add(EXTERN_my_menubar->menubaritems.count(), MenuBarItem->GETPROPERTY_Name(), (_menubaritem *) MenuBarItem);

    _qmenu *my_qmenu = ParentMenuBarItem->my_qmenu;
    if (my_qmenu == 0) my_qmenu = ParentMenuBarItem->parent->my_qmenu;

    MenuBarItem->my_qaction = my_qmenu->addAction(MenuBarItem->GETPROPERTY_Caption());
    if (MenuBarItem->GETPROPERTY_Separator()) my_qmenu->addSeparator();

    QString k;

    k = MenuBarItem->GETPROPERTY_Icon(); 
    MenuBarItem->SETPROPERTY_Icon(k); // do it this way to call SETPROPERTY_Icon with const QString &

    k = MenuBarItem->GETPROPERTY_Key(); 
    MenuBarItem->SETPROPERTY_Key(k); // do it this way to call SETPROPERTY_Key with const QString &

    t_boolean b;
    b = MenuBarItem->GETPROPERTY_Enabled();
    MenuBarItem->SETPROPERTY_Enabled(b); // do it this way to call

    b = MenuBarItem->GETPROPERTY_Visible();
    MenuBarItem->SETPROPERTY_Visible(b); // do it this way to call

    b = MenuBarItem->GETPROPERTY_Checkable();
    MenuBarItem->SETPROPERTY_Checkable(b); // do it this way to call

    if (MenuBarItem->GETPROPERTY_Checkable() && !MenuBarItem->GETPROPERTY_Group().isEmpty()){
     // MenuBarItem->my_qaction->setCheckable(true);
      if (!actiongroups.contains(MenuBarItem->GETPROPERTY_Group().toLower())){
        actiongroups[MenuBarItem->GETPROPERTY_Group().toLower()] = new QActionGroup(EXTERN_my_menubar);
        MenuBarItem->SETPROPERTY_Checked(true);
      }
      actiongroups[MenuBarItem->GETPROPERTY_Group().toLower()]->addAction(MenuBarItem->my_qaction);      
    }

    b = MenuBarItem->GETPROPERTY_Checked2();
    if (b) MenuBarItem->SETPROPERTY_Checked(b); // do it this way to call   

    if (my_qmenu == 0 || ParentMenuBarItem->my_qmenu == 0) MenuBarItem->parent = ParentMenuBarItem->parent; else MenuBarItem->parent = ParentMenuBarItem;
    MenuBarItem->bDynamicMenuItem = true;
  }
}

void _menubar::METHOD_AppendContextMenu(_menubaritem *MenuBarItem)
{
  if (EXTERN_my_menubar == 0){ EXTERN_myInterpreter->runtimeError("no menubar object created"); return; }

  _menubaritem *ParentMenuBarItem = EXTERN_my_menubar->getParent(MenuBarItem->GETPROPERTY_Name());
  sLastUsedMenu = MenuBarItem->GETPROPERTY_Name();
  bool bNew = true;
  if (ParentMenuBarItem){

    METHOD_Remove(MenuBarItem->GETPROPERTY_Name());
    bNew = false;
  }
  int count = EXTERN_my_menubar->menubaritems.count();
  EXTERN_my_menubar->menubaritems.add(EXTERN_my_menubar->menubaritems.count(), MenuBarItem->GETPROPERTY_Name(), (_menubaritem *) MenuBarItem);
  count = EXTERN_my_menubar->menubaritems.count();

  if (bNew){
    MenuBarItem->my_qmenu = new _qmenu(EXTERN_my_menubar, EXTERN_my_menubar);
    
    connect(MenuBarItem->my_qmenu, SIGNAL(aboutToShow()), EXTERN_my_menubar, SLOT(aboutToShow()));
    connect(MenuBarItem->my_qmenu, SIGNAL(aboutToHide()), EXTERN_my_menubar, SLOT(aboutToHide()));
    connect(MenuBarItem->my_qmenu, SIGNAL(triggered(QAction *)), EXTERN_my_menubar, SLOT(triggered(QAction *)));
    connect(MenuBarItem->my_qmenu, SIGNAL(hovered(QAction *)), EXTERN_my_menubar, SLOT(hovered(QAction *)));   
  } else {
    MenuBarItem->my_qmenu = ParentMenuBarItem->my_qmenu;
  }
  

  MenuBarItem->bDynamicMenuItem = true;
}

void _menubar::METHOD_ShowContextMenu(int X, int Y)
{
  if (EXTERN_my_menubar == 0){ EXTERN_myInterpreter->runtimeError("no menubar object created"); return; }

  METHOD_ShowContextMenu(sLastUsedMenu, X, Y);
}

void _menubar::METHOD_ShowContextMenu(QString MenuBarItemName, int X, int Y)
{
  if (EXTERN_my_menubar == 0){ EXTERN_myInterpreter->runtimeError("no menubar object created"); return; }

  _qmenu *my_qmenu = 0;

  _menubaritem *c;

  if (EXTERN_my_menubar->firstControl(&c)){
   
    do {

      if (c->GETPROPERTY_Name().compare(MenuBarItemName, Qt::CaseInsensitive) == 0){
        my_qmenu = c->my_qmenu;
        break;
      }

    } while (EXTERN_my_menubar->nextControl(&c)); 
  }

  if (my_qmenu == 0) return;

  my_qmenu->exec(QPoint(X, Y));
  
  int count = EXTERN_my_menubar->menubaritems.count();

  METHOD_Remove(c->GETPROPERTY_Name()); // remove list containing real menubaritems and temporary menubaritems
    
  count = EXTERN_my_menubar->menubaritems.count();

  count = count;

  int i = 4;
  i++;

}

void _menubar::METHOD_AppendMenu(_menubaritem *MenuBarItem)
{
  METHOD_AppendMenu1("", MenuBarItem);
}

void _menubar::METHOD_AppendMenu1(QString ParentMenuBarItemName, _menubaritem *MenuBarItem)
{
  if (EXTERN_my_menubar == 0){ EXTERN_myInterpreter->runtimeError("no menubar object created"); return; }

  sLastUsedMenu = MenuBarItem->GETPROPERTY_Name();
  if (EXTERN_my_menubar->getParent(MenuBarItem->GETPROPERTY_Name())) return;
  EXTERN_my_menubar->menubaritems.add(EXTERN_my_menubar->menubaritems.count(), MenuBarItem->GETPROPERTY_Name(), (_menubaritem *) MenuBarItem);

  MenuBarItem->my_qmenu = new _qmenu(EXTERN_my_menubar, EXTERN_my_menubar);
  MenuBarItem->my_qmenu->setTitle(MenuBarItem->GETPROPERTY_Caption());          
  connect(MenuBarItem->my_qmenu, SIGNAL(aboutToShow()), EXTERN_my_menubar, SLOT(aboutToShow()));
  connect(MenuBarItem->my_qmenu, SIGNAL(aboutToHide()), EXTERN_my_menubar, SLOT(aboutToHide()));

  if (!ParentMenuBarItemName.isEmpty()){
    _menubaritem *it = METHOD_MenuBarItem(ParentMenuBarItemName);
    if (it){
      MenuBarItem->my_qaction = EXTERN_my_menubar->insertMenu(it->my_qaction, MenuBarItem->my_qmenu);
    } else {
      MenuBarItem->my_qaction = EXTERN_my_menubar->addMenu(MenuBarItem->my_qmenu);
    }
    
  } else {
    MenuBarItem->my_qaction = EXTERN_my_menubar->addMenu(MenuBarItem->my_qmenu);
  }
  
  t_boolean b;
  b = MenuBarItem->GETPROPERTY_Enabled();
  MenuBarItem->SETPROPERTY_Enabled(b); // do it this way to call

  b = MenuBarItem->GETPROPERTY_Visible();
  MenuBarItem->SETPROPERTY_Visible(b); // do it this way to call

  MenuBarItem->bDynamicMenuItem = true;
}

void _menubar::METHOD_AppendChildMenu(_menubaritem *MenuBarItem)
{
  if (EXTERN_my_menubar == 0){ EXTERN_myInterpreter->runtimeError("no menubar object created"); return; }

  METHOD_AppendChildMenu(sLastUsedMenu, MenuBarItem);
}

void _menubar::METHOD_AppendChildMenu(QString ParentMenuBarItemName, _menubaritem *MenuBarItem)
{
  if (EXTERN_my_menubar == 0){ EXTERN_myInterpreter->runtimeError("no menubar object created"); return; }

  _menubaritem *ParentMenuBarItem = EXTERN_my_menubar->getParent(ParentMenuBarItemName);
  if (ParentMenuBarItem){
    sLastUsedMenu = MenuBarItem->GETPROPERTY_Name();
    if (EXTERN_my_menubar->getParent(MenuBarItem->GETPROPERTY_Name())) return;
    EXTERN_my_menubar->menubaritems.add(EXTERN_my_menubar->menubaritems.count(), MenuBarItem->GETPROPERTY_Name(), (_menubaritem *) MenuBarItem);

    MenuBarItem->my_qmenu = new _qmenu(EXTERN_my_menubar, EXTERN_my_menubar);
    MenuBarItem->my_qmenu->setTitle(MenuBarItem->GETPROPERTY_Caption());          

    _qmenu *my_qmenu = ParentMenuBarItem->my_qmenu;
    if (my_qmenu == 0) my_qmenu = ParentMenuBarItem->parent->my_qmenu;

    MenuBarItem->my_qaction = my_qmenu->addMenu(MenuBarItem->my_qmenu);
    if (MenuBarItem->GETPROPERTY_Separator()) my_qmenu->addSeparator();

    t_boolean b;
    b = MenuBarItem->GETPROPERTY_Enabled();
    MenuBarItem->SETPROPERTY_Enabled(b); // do it this way to call

    b = MenuBarItem->GETPROPERTY_Visible();
    MenuBarItem->SETPROPERTY_Visible(b); // do it this way to call

    if (my_qmenu == 0 || ParentMenuBarItem->my_qmenu == 0) MenuBarItem->parent = ParentMenuBarItem->parent; else MenuBarItem->parent = ParentMenuBarItem;

    MenuBarItem->bDynamicMenuItem = true;

  }
}


void _menubar::EVENT_OnEvent()
{ 
  if (currentMenuItem->GETPROPERTY_Enabled() == false){
    acName = "";
    acGroup = "";
    return;
  }

  static QString sName; sName = currentMenuItem->GETPROPERTY_Name();
  static QByteArray a; a = sName.toAscii();
  acName = a.data();    
  acGroup = "";

}

void _menubar::hovered(QAction *action)
{
  currentMenu = getMenuBarItemByAction(action);
  currentMenuItem = getMenuBarItemByAction(action, false);  

#ifdef RUN
  if (currentMenuItem){
    _application::EVENT_MenuBar_OnHovered(currentMenuItem->GETPROPERTY_Name());
  }
#endif
}

void _menubar::triggered(QAction *action)
{
  currentMenu = getMenuBarItemByAction(action);
  currentMenuItem = getMenuBarItemByAction(action, false);  

#ifdef RUN
  if (currentMenuItem){
    if (currentMenuItem->bDynamicMenuItem){      
      currentMenuItem->SoundOnEvent();
      currentMenuItem->EVENT_OnEvent();
    } else {
      currentMenuItem->SoundOnEvent();
      EVENT_OnEvent();
    }
    _application::EVENT_MenuBar_OnEvent(currentMenuItem->GETPROPERTY_Name());
    _application::EVENT_Actions_OnAction(currentMenuItem->GETPROPERTY_ActionId());
  }
#endif

}

void _menubar::aboutToShow()
{

  QMenu *my_qmenu = (QMenu *) sender();
  aboutToShow(my_qmenu->menuAction());
}

void _menubar::aboutToHide()
{
  QMenu *my_qmenu = (QMenu *) sender();
  aboutToHide(my_qmenu->menuAction());
}

void _menubar::aboutToShow(QAction *action)
{
  currentMenu = getMenuBarItemByAction(action);
  currentMenuItem = getMenuBarItemByAction(action, false);  

#ifdef RUN
  if (currentMenuItem){
    _application::EVENT_MenuBar_OnAboutToShow(currentMenuItem->GETPROPERTY_Name());
  }
#endif

}

void _menubar::aboutToHide(QAction *action)
{
  currentMenu = getMenuBarItemByAction(action);
  currentMenuItem = getMenuBarItemByAction(action, false);  

#ifdef RUN
  if (currentMenuItem){
    _application::EVENT_MenuBar_OnAboutToHide(currentMenuItem->GETPROPERTY_Name());
  }
#endif

}



QAction *_menubar::insertItem( _qmenu *qp, _menubaritem *m, int nIndex)
{  

  _qmenu *G = qp;
  if (G == 0) G = (_qmenu *) 1;

  items *i = sorted_actions[G];
  if (i == 0){
    i = new items();
    sorted_actions[G] = i;
  }

  _menubaritem *l = i->isEmpty() ? 0 : i->last();
  if (l){
    if (l->nIndex > nIndex){

      for (int y = 0; y < i->size(); y++){
        _menubaritem *ll = i->at(y);

        if (ll->nIndex > nIndex){
          i->insert(y, m);
          return 0;
        }
        
      }
      i->append(m);
 
      
    } else {
      i->append(m);
    }
  } else {
    i->append(m);
  }

  
  return 0;
}


_menubaritem *_menubar::getParent(QString s)
{
  _menubaritem *c;
  _menubaritem *m;

  
  if (firstControl(&c, 40)){
   
    do {

      m = (_menubaritem *) c;

      if (m->GETPROPERTY_Name().compare(s, Qt::CaseInsensitive) == 0){
        return m;
      }

    } while (nextControl(&c, 40)); 
  }
  

  return 0;
}


void _menubar::buildMenu(_qmenu *pm, 
                       _menubaritem* p, int nItIndex)
{  
  _menubaritem *c;
  _menubaritem *m;

  if (pm == 0 && p == 0){
    this->clear();
    sorted_actions.clear();
  }
  

  if (firstControl(&c, nItIndex)){

    do {

      m = (_menubaritem *) c;

      _qmenu *my_qmenu = m->my_qmenu;

      int nIndex = m->nIndex;
      _menubaritem *parent = m->parent;
      bool bMenu = m->bMenu;
      bool bSubMenu = m->bSubMenu;
      QString kk;


      if (parent == p){

        QString s = m->GETPROPERTY_Caption();


        if (bMenu){

          m->SETPROPERTY_ParentIndex(m->nIndex);

          m->my_qmenu = new _qmenu(this, this);
          m->my_qmenu->setTitle(s);          
  
          m->sTitle = s;

          m->bChecked = false;

          m->bCheckable = false;
      
          m->bVisible = true;
          if (!m->GETPROPERTY_Visible()) m->bVisible = false;

          m->bEnabled = true;
          if (!m->GETPROPERTY_Enabled()){
            m->bEnabled = false;
          }

          m->sIcon = "";
          m->sKey = "";
          m->my_qmenu_childs = 0;
            
          insertItem(0, m, nIndex);

          buildMenu(m->my_qmenu, m, nItIndex + 1);

        } else {

          m->SETPROPERTY_ParentIndex(m->nIndex);

          if (bSubMenu){

            m->my_qmenu = pm;
            m->my_qmenu_childs = new _qmenu(pm, this);
            m->my_qmenu_childs->setTitle(s);          


            m->sTitle = s;

            m->SETPROPERTY_ParentControl(p->GETPROPERTY_Name());

            m->bChecked = false;

            m->bCheckable = false;
        
            m->bVisible = true;
            if (!m->GETPROPERTY_Visible()) m->bVisible = false;

            m->bEnabled = true;
            if (!m->GETPROPERTY_Enabled()){
              m->bEnabled = false;
            }

            m->bSeparator = false;
            if (m->GETPROPERTY_Separator()){
              m->bSeparator = true;
            }            
            m->sIcon = "";
            m->sKey = "";

            insertItem(pm, m, nIndex);

            buildMenu(m->my_qmenu_childs, m, nItIndex + 1);

          } else {

            m->my_qmenu = pm;
            m->my_qmenu_childs = 0;
            m->sTitle = s;

            m->SETPROPERTY_ParentControl(p->GETPROPERTY_Name());

            m->bCheckable = false;
            if (m->GETPROPERTY_Checkable()) m->bCheckable = true;
        
            m->bVisible = true;
            if (!m->GETPROPERTY_Visible()) m->bVisible = false;

            m->bChecked = false;
            if (m->GETPROPERTY_Checked()){
              m->bChecked = true;
            }

            m->bEnabled = true;
            if (!m->GETPROPERTY_Enabled()){
              m->bEnabled = false;
            }
            
            m->bSeparator = false;
            if (m->GETPROPERTY_Separator()){
              m->bSeparator = true;
            }          
 
            m->sKey = m->GETPROPERTY_Key();


            m->sIcon = m->GETPROPERTY_Icon().simplified();

            insertItem(pm, m, nIndex);
            

          }

          

        }

      }

    } while (nextControl(&c, nItIndex)); 
  }

  // actually build it
  if (pm == 0 && p == 0){

    QMap<_qmenu*, items*>::const_iterator i = sorted_actions.constBegin();
    while(i != sorted_actions.constEnd()){
      items *t = i.value();
 
      for (int y = 0; y < t->size(); y++){
        _menubaritem* tt = t->at(y);

        if (tt->bMenu){
          tt->my_qaction = this->addMenu(tt->my_qmenu);
          connect(tt->my_qmenu, SIGNAL(aboutToShow()), EXTERN_my_menubar, SLOT(aboutToShow()));
          connect(tt->my_qmenu, SIGNAL(aboutToHide()), EXTERN_my_menubar, SLOT(aboutToHide()));
          tt->my_qaction->setVisible(tt->bVisible);

        } else if (tt->bSubMenu){
          tt->my_qaction = tt->my_qmenu->addMenu(tt->my_qmenu_childs);

          connect(tt->my_qmenu, SIGNAL(aboutToShow()), EXTERN_my_menubar, SLOT(aboutToShow()));
          connect(tt->my_qmenu, SIGNAL(aboutToHide()), EXTERN_my_menubar, SLOT(aboutToHide()));

          if (tt->bSeparator) tt->my_qmenu->addSeparator();
          tt->my_qaction->setVisible(tt->bVisible);
        } else {
          tt->my_qaction = tt->my_qmenu->addAction(tt->sTitle);
          if (tt->bSeparator) tt->my_qmenu->addSeparator();
          //if (tt->bChecked) tt->my_qaction->setChecked(true);

          
          if (!tt->GETPROPERTY_Group().isEmpty()){
            tt->my_qaction->setVisible(tt->bVisible);
            tt->my_qaction->setCheckable(tt->bCheckable);
            if (tt->bCheckable){
              if (!actiongroups.contains(tt->GETPROPERTY_Group().toLower())){
                actiongroups[tt->GETPROPERTY_Group().toLower()] = new QActionGroup(EXTERN_my_menubar);
                tt->SETPROPERTY_Checked(true);
              }
              actiongroups[tt->GETPROPERTY_Group().toLower()]->addAction(tt->my_qaction);
            }

            bool b = tt->bChecked;
            if (b) tt->SETPROPERTY_Checked(b); // do it this way to call   

          } else {
            tt->my_qaction->setVisible(tt->bVisible);
            tt->my_qaction->setCheckable(tt->bCheckable);
            tt->my_qaction->setChecked(tt->bChecked);
          }

          tt->my_qaction->setEnabled(tt->bEnabled);

          tt->my_qaction->setShortcut(QKeySequence(tt->sKey));
          if (!tt->sIcon.isEmpty()) tt->my_qaction->setIcon(QIcon(loadProjectImage(tt->sIcon)));
         
        }
        tt->my_qaction->setStatusTip(tt->GETPROPERTY_StatusTip());

      }
      ++i;
      
    }

  }
  
}

#else

bool _menubar::isModified()
{  
  _menubaritem *c;

  if (bModified) return true;

  if (firstControl(&c)){

    do {

      if (c->bModified) return true;

    } while (nextControl(&c)); 
  }

  return bModified;
}

void _menubar::setNonModified()
{  
  _menubaritem *c;

  if (firstControl(&c)){

    do {

      c->bModified = false;

    } while (nextControl(&c)); 
  }
  
  bModified = false;
}

QAction *my_qaction;
_menubaritem *currentMenu;
_menubaritem *currentMenuItem;

typedef QVector<_menubaritem*>items;
QMap<_qmenu*, items*>sorted_actions;


int nTo;
int nTo2;

extern _helpwindow_shortcut *EXTERN_my_helpwindow_shortcut;
extern _propertywindow *EXTERN_my_propertywindow;

_menubar::_menubar(_mainwindow *_my_mainwindow)
{
  bModified = false;

  setAttribute(Qt::WA_DeleteOnClose);

  setWindowFlags(windowFlags() | Qt::Tool);

  EXTERN_my_menubar = this;

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
        f.close();
      }

      setStyleSheet(s);
    }
  }
#endif

  //updateCaption("");
  setFocusPolicy(Qt::StrongFocus);
  setFocus();

  resize(500, 60);
  QWidget::move(5, 5);
  setWindowIcon(kbasicIcon(kbasicPath("ide/PROJECT_NEW_MENUBAR.png")));

  bSelected = false;


  my_qmenubar = new _qmenubar(this, this);
  
  QBoxLayout *l = new QBoxLayout(QBoxLayout::TopToBottom);
  l->addWidget(my_qmenubar);
  l->setMargin(0);
  l->setSpacing(0);

  setLayout(l);

  
  nTo = 0;
  nTo2 = 0;

  currentMenu = 0;
  currentMenuItem = 0;

  insertType = t_notype;

  setMenubarSelf();
}


void _qmenubar::hovered(QAction *action)
{
  my_qaction = action;

  _menubaritem *currentMenu2 = currentMenu;
  _menubaritem *currentMenuItem2 = currentMenuItem;

  currentMenu = EXTERN_my_menubar->getMenuBarItemByAction(my_qaction);
  currentMenuItem = EXTERN_my_menubar->getMenuBarItemByAction(my_qaction, false);  

  if (currentMenu == 0 || currentMenuItem == 0){

    if (currentMenu == 0) currentMenu = currentMenu2;
    if (currentMenuItem == 0) currentMenuItem = currentMenuItem2;
/*
    int i = 0;
    i++; 
    return;*/
  }

  nTo = currentMenuItem->nIndex;
 

  _menubaritem *p = currentMenuItem->parent;
  nTo2 = nTo;

  _menubaritem *c = 0;
  _menubaritem *m = 0;

  if (EXTERN_my_menubar->firstControl(&c)){

    do {

      m = (_menubaritem *) c;

      if (m->parent == p && m->GETPROPERTY_Separator() && m->nIndex < nTo2){ // selected
        nTo++;
      }

    } while (EXTERN_my_menubar->nextControl(&c)); 
  }


}


void _qmenubar::mouseReleaseEvent ( QMouseEvent * e )
{    
    if (e->button() == Qt::RightButton){
      if (bMousePressed2){
       bMouseReleased2 = true;

      } else {
       bMouseReleased2 = false;
      }

      bMousePressed2 = false;
    }

    if (bMousePressed){
       bMouseReleased = true;
    } else {
       bMouseReleased = false;
    }

    bMousePressed = false;

    QMenuBar::mouseReleaseEvent(e);

    if (e->button() == Qt::LeftButton){
      if (my_menubar->insertType == t_menu){
        my_menubar->addNewToMenu();
        my_menubar->updatePropertyWindow();
      } else if (my_menubar->insertType == t_notype){        
        my_menubar->select();   
        my_menubar->updatePropertyWindow();
      }
    }    
    
}
#endif

void _qmenu::mouseReleaseEvent ( QMouseEvent * e )
{

#ifdef RUN
  QMenu::mouseReleaseEvent(e);
  
#endif
#ifdef IDE
  if (bMousePressed){
    bMouseReleased = true;
  } else {
    bMouseReleased = false;
  }

  bMousePressed = false;

  bool b = false;
  
  QRect r = contentsRect();

  int x = e->x() - 7;
  int y = e->y() + 15;
  int left = r.left() - 7;
  int top = r.top() - 15;
  int right = r.right() + 40;
  int bottom = r.bottom() + 40;

  // check if clicked inside menuarea
  if (x >= left && y >= top && x <= right && y <= bottom){
    b = true;
  }


  if (b && my_menubar->insertType != t_menu){   
    if (e->button() == Qt::LeftButton && (my_menubar->insertType == t_menubaritem || my_menubar->insertType == t_submenu)){
      my_menubar->addNewToMenu2();
      my_menubar->updatePropertyWindow();
      
    } else if (e->button() == Qt::LeftButton && my_menubar->insertType == t_move){
      my_menubar->move();
      my_menubar->updatePropertyWindow();

    } else if ((e->button() == Qt::LeftButton && my_menubar->insertType == t_notype) || e->button() == Qt::RightButton){
      _controlType save_insertType = my_menubar->insertType;
      my_menubar->insertType = t_notype;
      my_menubar->select();
      my_menubar->updatePropertyWindow();
      my_menubar->insertType = save_insertType;
    } else if (e->button() == Qt::LeftButton && my_menubar->insertType == t_delete){
      my_menubar->del();
      my_menubar->updatePropertyWindow();
    } else {      
      QMenu::mouseReleaseEvent(e);
    }
  } else {
    QMenu::mouseReleaseEvent(e);
  } 
#endif
}

#ifdef IDE
void _menubar::addNewToMenu()
{

    _menubaritem *c;

    int nn = nTo;

    switch(insertType){
      case t_menu:
       c = new _menubaritem(0, 0, nn);
       break;
      default:
       return;
       break;
    }  

    ////bModified = true;

    c->my_qmenu = 0;
    c->my_qaction = 0;
    c->nIndex = nn;
    c->parent = 0;
    c->bMenu = true;
    c->bSubMenu = false;
    
    //setUpdatesEnabled(false);


    METHOD_insertControl(c, insertType);

    unselectAllControls();
    selectControlAlways(c);
    currentMenu = c;
    currentMenuItem = 0;

    incIndexFor(c, c->nIndex);
    c->nIndex = nn; // reset


    buildMenu();

}

void _menubar::addNewToMenu2()
{


    _menubaritem *c;
    int nToKK = 0;

//    if (hasChilds(currentMenu->my_qmenu)){
    if (currentMenuItem && currentMenuItem->bSubMenu){
      currentMenu = currentMenuItem;
      nToKK = 0;
    } else {
      if (currentMenuItem && (hasChilds(currentMenu->my_qmenu) && currentMenu->bSubMenu == false || currentMenu->my_qmenu_childs)){
        nToKK = nTo2;
      } else {
        nToKK = 0;
      }
    }

    switch(insertType){
      case t_submenu:
      case t_menubaritem:
       c = new _menubaritem(0, 0, nToKK);
       break;
      default:
       return;
       break;
    }  

    bModified = true;

    if (currentMenuItem && currentMenuItem->bSubMenu){
      c->my_qmenu = currentMenuItem->my_qmenu_childs;
      c->parent = currentMenuItem;
    } else {
      if (currentMenu && currentMenu->bSubMenu){
        c->my_qmenu = currentMenu->my_qmenu_childs;
        c->parent = currentMenu;
      } else {
        c->my_qmenu = currentMenu->my_qmenu;
        c->parent = getRootParent(currentMenu);
      }

    }


    if (insertType == t_submenu){
      c->my_qmenu_childs = new _qmenu(c->my_qmenu, this);
    } else {
      c->my_qmenu_childs = 0;
    }


    c->nIndex = nToKK;

    
    c->bMenu = false;
    c->bSubMenu = insertType == t_submenu;
    

    METHOD_insertControl(c, insertType);

    unselectAllControls();
    selectControlAlways(c);


    incIndexFor(c, c->nIndex);
    c->nIndex = nToKK; // reset

    buildMenu();

    my_qmenubar->show();
}

void _menubar::select()
{

  bSelected = true;


  _menubaritem *c;
  _menubaritem *m;

  unselectAllControls();

  if (firstControl(&c)){

    do {

      m = (_menubaritem *) c;

      if (m->my_qaction == my_qaction){ // selected
        c->setAcceptDrops(true);

        currentMenu = m;
        currentMenuItem = m;
      }

    } while (nextControl(&c)); 
  }


  buildMenu();
  
  updateMenuBar();


}

void _menubar::buildMenu2(bool bActivate)
{/*
  //setUpdatesEnabled(false);

*/
  
  if (bSelected){ 
    bSelected = false;
    //return;
  }

  buildMenu(0, 0, 0, bActivate);

}

void _menubar::move()
{

  _menubaritem *c = 0;
  _menubaritem *m = 0;
  _menubaritem *m2 = 0;
  _menubaritem *currentMenu2 = 0;
 
  int nOldIndex = 0;


  if (firstControl(&c)){

    do {

      m = (_menubaritem *) c;

      if (c->acceptDrops()){ // selected
        nOldIndex = m->nIndex;
        m->nIndex = nTo2;
        m2 = m;
        break;
      }

    } while (nextControl(&c)); 
  }

  if (firstControl(&c)){

    do {

      m = (_menubaritem *) c;

      if (c->acceptDrops() == false && m->my_qaction == my_qaction){ // selected

        currentMenu2 = m;

        if ((m->my_qmenu != m2->my_qmenu && m->parent != 0 && m2->parent != 0) || (((m->parent == 0 || m2->parent == 0) && m->parent != m2->parent)) || (m->parent == m2->parent && m->parent && m->parent->bSubMenu)){
          if ((m->parent == 0 || m2->parent == 0) && m->parent != m2->parent){
            m2->nIndex = nOldIndex;
            break;
          }
          
          decIndexFor(m2, nOldIndex);

          int n = m->nIndex;
          m2->nIndex = n;
          m2->my_qmenu = m->my_qmenu;
          m2->parent = m->parent;

          incIndexFor(m2, m2->nIndex);
          

          m2->nIndex = n;

          if (!(m->parent == m2->parent && m->parent->bSubMenu)) break;
        }
        m->nIndex = nOldIndex;
        
        break;
      }

    } while (nextControl(&c)); 
  }


  bModified = true;
  buildMenu();

  my_qmenubar->show();

}

void _menubar::del()
{

  _menubaritem *c;
  _menubaritem *m;

  unselectAllControls();


  int nIndex = 0;

  if (firstControl(&c)){

    do {

      m = (_menubaritem *) c;

      if (c->my_qaction == my_qaction){ // selected

        nIndex = c->nIndex;


        decIndexFor(c, nIndex);

        
        deleteControl(c);        
        break;
      }

    } while (nextControl(&c)); 
  }
  

   bModified = true;
  buildMenu();




  currentMenu = 0;
  currentMenuItem = 0;
}

QAction *_menubar::insertItem( _qmenu *qp, _menubaritem *m, int nIndex)
{  

  _qmenu *G = qp;
  if (G == 0) G = (_qmenu *) 1;

  items *i = sorted_actions[G];
  if (i == 0){
    i = new items();
    sorted_actions[G] = i;
  }

  _menubaritem *l = i->isEmpty() ? 0 : i->last();
  if (l){
    if (l->nIndex > nIndex){

      for (int y = 0; y < i->size(); y++){
        _menubaritem *ll = i->at(y);

        if (ll->nIndex > nIndex){
          i->insert(y, m);
          return 0;
        }
        
      }
      i->append(m);
 
      
    } else {
      i->append(m);
    }
  } else {
    i->append(m);
  }

  return 0;
}

void _menubar::buildMenu(_qmenu *pm, 
                       _menubaritem* p, int nItIndex, bool bActivate)
{  
  _menubaritem *c;
  _menubaritem *m;
  bool bIsModified = false;

  if (pm == 0 && p == 0){
    my_qmenubar->clear();
    sorted_actions.clear();
    bIsModified = this->isModified();
  }
 

  if (firstControl(&c, nItIndex)){

    do {

      m = (_menubaritem *) c;

      _qmenu *my_qmenu = m->my_qmenu;

      int nIndex = m->nIndex;
      _menubaritem *parent = m->parent;
      bool bMenu = m->bMenu;
      bool bSubMenu = m->bSubMenu;
      QString kk;


      if (parent == p){

        QString s = m->GETPROPERTY_Caption();
   
        if (m->acceptDrops()){ // selected
          s = "-> " + s + " <-";
        } else {
          if (parent != 0){
             s = "     " + s + "     ";
          }
        }       


        if (bMenu){

          m->SETPROPERTY_ParentIndex(m->nIndex);

          m->my_qmenu = new _qmenu(my_qmenubar, this);
          m->my_qmenu->setTitle(s);          

          m->sTitle = s;

          m->bChecked = false;

          m->bEnabled = true;
          if (!m->GETPROPERTY_Enabled()){
            m->bEnabled = false;
          }

          m->sIcon = "";
          m->sKey = "";
          m->my_qmenu_childs = 0;
            
          insertItem(0, m, nIndex);

          buildMenu(m->my_qmenu, m, nItIndex + 1);

        } else {

          if (!existsParent(m->parent, nItIndex + 1)){
             continue;  // gelöschte kinder ignorieren
          }

          m->SETPROPERTY_ParentIndex(m->nIndex);

          if (bSubMenu){

            m->my_qmenu = pm;
            m->my_qmenu_childs = new _qmenu(pm, this);
            m->my_qmenu_childs->setTitle(s);          


            m->sTitle = s;

            m->SETPROPERTY_ParentControl(p->GETPROPERTY_Name());

            m->bChecked = false;

            m->bEnabled = true;
            if (!m->GETPROPERTY_Enabled()){
              m->bEnabled = false;
            }

            m->bSeparator = false;
            if (m->GETPROPERTY_Separator()){
              m->bSeparator = true;
            }            
            m->sIcon = "";
            m->sKey = "";

            insertItem(pm, m, nIndex);

            buildMenu(m->my_qmenu_childs, m, nItIndex + 1);

          } else {

            m->my_qmenu = pm;
            m->my_qmenu_childs = 0;
            m->sTitle = s;

            m->SETPROPERTY_ParentControl(p->GETPROPERTY_Name());

            m->bChecked = false;
            if (m->GETPROPERTY_Checked()){
              m->bChecked = true;
            }        

            m->bEnabled = true;
            if (!m->GETPROPERTY_Enabled()){
              m->bEnabled = false;
            }
            
            m->bSeparator = false;
            if (m->GETPROPERTY_Separator()){
              m->bSeparator = true;
            }          

            m->sKey = m->GETPROPERTY_Key();

            m->sIcon = m->GETPROPERTY_Icon().simplified();
            insertItem(pm, m, nIndex);
            

          }

          

        }

      }

    } while (nextControl(&c, nItIndex)); 
  }

  // actually build it
  if (pm == 0 && p == 0){

    QMap<_qmenu*, items*>::const_iterator i = sorted_actions.constBegin();
    while(i != sorted_actions.constEnd()){
      items *t = i.value();
 
      for (int y = 0; y < t->size(); y++){
        _menubaritem* tt = t->at(y);

        if (tt->bMenu){
          tt->my_qaction = my_qmenubar->addMenu(tt->my_qmenu);
          if (tt->bSeparator) my_qmenubar->addSeparator();
        } else if (tt->bSubMenu){
          tt->my_qaction = tt->my_qmenu->addMenu(tt->my_qmenu_childs);
          if (tt->bSeparator) tt->my_qmenu->addSeparator();
        } else {
          tt->my_qaction = tt->my_qmenu->addAction(tt->sTitle);
          if (tt->bSeparator) tt->my_qmenu->addSeparator();
        }

        tt->my_qaction->setCheckable(tt->bCheckable);
        tt->my_qaction->setChecked(tt->bChecked);
        tt->my_qaction->setEnabled(tt->bEnabled);

        tt->my_qaction->setShortcut(QKeySequence(tt->sKey));
        if (!tt->sIcon.isEmpty()) tt->my_qaction->setIcon(QIcon(loadPixmap(tt->sIcon)));
         

      }
      ++i;
      
    }
    updateMenuBar(bActivate);
  }
  
  if (pm == 0 && p == 0 && bIsModified == false){
    this->setNonModified();
  }

}

void _menubar::updateMenuBar(bool bActivate)
{
   if (currentMenu){
     if (currentMenu->my_qmenu_childs){
      _menubaritem *m = getRootParent(currentMenu);
      if (m == 0) m = currentMenu;
      if (bActivate) my_qmenubar->setActiveAction(m->my_qaction);

     } else {
        _menubaritem *m = getRootParent(currentMenu);
        if (m == 0) m = currentMenu;
        if (bActivate) my_qmenubar->setActiveAction(m->my_qaction);
     
    }
    
  }
}

bool _menubar::hasChilds(_qmenu *pm)
{  
  _menubaritem *c;
  _menubaritem *m;


  if (firstControl(&c, 0)){

    do {

      m = (_menubaritem *) c;

      if (m->parent && m->parent->my_qmenu == pm) return true;

    } while (nextControl(&c, 0)); 
  }  

  return false;
}

_menubaritem * _menubar::getRootParent(_menubaritem *p)
{
  _menubaritem *pp = p;
  do {
    p = pp;
    pp = pp->parent;
  } while (pp);

  return p;
}

void _menubar::incIndexFor(_menubaritem *p, int nIndex)
{  
  _menubaritem *c;
  _menubaritem *m;
  int nSeparator = 0;


  if (firstControl(&c)){

    int nIndex2 = nIndex;

    do {

      m = (_menubaritem *) c;

      _menubaritem *parent = m->parent;

      if (parent == p->parent && m->nIndex >= nIndex){

        m->nIndex = ++nIndex2;// + nSeparator;

      }

    } while (nextControl(&c)); 
  }

}

void _menubar::incIndexFor2(_menubaritem *p, int nIndex)
{  
  _menubaritem *c;
  _menubaritem *m;

  int nSeparator = 0;


  if (firstControl(&c)){

    int nIndex2 = nIndex;

    do {

      m = (_menubaritem *) c;

      _menubaritem *parent = m->parent;

      if (parent == p->parent && m->nIndex > nIndex){
        m->nIndex = ++nIndex2;// + nSeparator;

      }

    } while (nextControl(&c)); 
  }

}

void _menubar::decIndexFor(_menubaritem *p, int nIndex)
{  
  _menubaritem *c;
  _menubaritem *m;

  int nSeparator = 0;

  if (firstControl(&c)){
   
    int nIndex2 = nIndex;

    do {

      m = (_menubaritem *) c;

      _menubaritem *parent = m->parent;

      if (parent == p->parent && m->nIndex > nIndex){

        m->nIndex = nIndex2++;

      }

    } while (nextControl(&c)); 
  }

}

_menubaritem *_menubar::getParent(QString s)
{
  _menubaritem *c;
  _menubaritem *m;

  
  if (firstControl(&c, 40)){
   
    do {

      m = (_menubaritem *) c;

      if (m->GETPROPERTY_Name().compare(s, Qt::CaseInsensitive) == 0){
        return m;
      }

    } while (nextControl(&c, 40)); 
  }
  

  return 0;
}

bool _menubar::existsParent(_menubaritem *cc, int nItIndex)
{
  _menubaritem *c;  

  
  if (firstControl(&c, nItIndex)){
   
    do {

      if (cc == c) return true;

    } while (nextControl(&c, nItIndex)); 
  }

  return false;
}


void _menubar::setInsertControlType(_controlType t)
{
   insertType = t;
}




void _menubar::focusInEvent ( QFocusEvent * e)
{  
  EXTERN_ToolboxForm->hide();
  EXTERN_ToolboxReport->hide();
  EXTERN_ToolboxMenuBar->show();
  EXTERN_ToolboxToolBar->hide();
  EXTERN_Helpwindow_shortcut->hide();

  EXTERN_my_mainwindow->workspace->setActiveSubWindow((QMdiSubWindow *) parentWidget());

  EXTERN_my_mainwindow->updateGeneralActions(
   false,  false,  false,  false, 
   false,  false,  false,  true,  false, 
  
   false,  false,  false, 
   false,  false,  false,  false, 
   false, "");

  nPropertyWindowForWhat = 1;
  EXTERN_my_menubar = this;
  bool b = isModified();
  updatePropertyWindow();
  if (!b) setNonModified();


  //EXTERN_my_helpwindow->setText("Edit your your MenuBar here.");

  
  QWidget::focusInEvent(e);
  
}

void _menubar::updatePropertyWindow()
{

  _menubaritem *c;
  
  p.clear();

  //if (!bObjectEditor) _property::addProperties(&p, &EXTERN_my_mainwindow->allProperties);

  bool bb = true;

  EXTERN_my_propertywindow->setform->setHidden(true);
  EXTERN_my_propertywindow->showControlName("");

  if (firstControl(&c)){

    do {

      if (c->acceptDrops()){ // missused as selected flag        

      #define SWITCH getProperties();
      #define SWITCH3 p2
      #include "_menubar_property_switch.h" 
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


void _menubar::updatePropertyWindow2(bool bb, QString sProperty)
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
      } else if (ss == "Icon"){ EXTERN_my_propertywindow->SETPROPERTY_Icon(d->display, d->set, d->v_qstring);
    } else if (ss == "Caption"){ EXTERN_my_propertywindow->SETPROPERTY_Caption(d->display, d->set, d->v_qstring);

    } else if (ss == "Key"){ EXTERN_my_propertywindow->SETPROPERTY_Key(d->display, d->set, d->v_qstring);

    } else if (ss == "Enabled"){
     EXTERN_my_propertywindow->SETPROPERTY_Enabled(d->display, d->set, d->v_boolean);
    } else if (ss == "Checked"){
     EXTERN_my_propertywindow->SETPROPERTY_Checked(d->display, d->set, d->v_boolean);
    } else if (ss == "Checkable"){
     EXTERN_my_propertywindow->SETPROPERTY_Checkable(d->display, d->set, d->v_boolean);
    } else if (ss == "Visible"){
     EXTERN_my_propertywindow->SETPROPERTY_Visible(d->display, d->set, d->v_boolean);

    } else if (ss == "ActionId"){
     EXTERN_my_propertywindow->SETPROPERTY_ActionId(d->display, d->set, d->v_qstring);
    } else if (ss == "Tag"){
     EXTERN_my_propertywindow->SETPROPERTY_Tag(d->display, d->set, d->v_qstring);
    } else if (ss == "Group"){
     EXTERN_my_propertywindow->SETPROPERTY_Group(d->display, d->set, d->v_qstring);
    } else if (ss == "MenuBarRole"){
     EXTERN_my_propertywindow->SETPROPERTY_MenuBarRole(d->display, d->set, d->v_qstring);
    } else if (ss == "Data"){
     EXTERN_my_propertywindow->SETPROPERTY_Data(d->display, d->set, d->v_qstring);
    } else if (ss == "SoundOnEvent"){
     EXTERN_my_propertywindow->SETPROPERTY_SoundOnEvent(d->display, d->set, d->v_qstring);


     
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
    EXTERN_my_propertywindow->setEnabled(p.count() > 0); nPropertyWindowForWhat = 1;
    
  }


}

const QPixmap &_menubar::loadPixmap(QString fn)
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

void _menubar::closeEvent( QCloseEvent *e )
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

  }
  

a:
  e->accept();
  EXTERN_my_menubar = 0;

  if (parentWidget()){
    QMdiSubWindow *mdis = qobject_cast<QMdiSubWindow *>(parentWidget());
    EXTERN_my_mainwindow->workspace->removeSubWindow(mdis);
  }

  QWidget::closeEvent(e);

}

bool _menubar::newEvent()
{  
    QString sControlName = "";
    QString sControlType = "";
    QString sParameter = "";
    QString sEvent = "OnEvent";
    if (sControlName.isEmpty()){


      _menubaritem *c;

      if (firstControl(&c)){

        do {

          if (c->acceptDrops()){

            #define SWITCH GETPROPERTY_Name();      
            #define SWITCH3 sControlName
            #include "_menubar_property_switch.h"   
            #undef SWITCH3

            #define SWITCH GETPROPERTY_ControlType();      
            #define SWITCH3 sControlType
            #include "_menubar_property_switch.h"   
            #undef SWITCH3
          
            break;
          }

        } while (nextControl(&c)); 
      }
      
    }


  EXTERN_my_mainwindow->openMenuBarClassSourceCode(getFilename());
  _sourcecodeeditor *o = qobject_cast<_sourcecodeeditor *>(EXTERN_my_mainwindow->workspace->activeSubWindow() ? EXTERN_my_mainwindow->workspace->activeSubWindow()->widget() : 0);
  if (o){
    return o->newEvent (sControlName, sEvent, sParameter);
  }

  return false;

}


#endif

bool _menubar::loadControl(QString *s, _controlType ct, QString sName)
{ 
  _menubaritem *c = 0;

#ifdef IDE
  #define SWITCH4 (0, 0, 0);
  #define SWITCH3 c
  #include "_menubar_property_switch.h" 
  #undef SWITCH3
  #undef SWITCH4
#else
   c = new kb_menubaritem(0, 0, 0);
#endif


  METHOD_insertControl(c, ct);

  if (ct == t_menu){    
    c->bMenu = true;
    c->bSubMenu = false;    

  } else if (ct == t_submenu){
    c->bMenu = false;
    c->bSubMenu = true;

  } else if (ct == t_menubaritem){
    c->bMenu = false;
    c->bSubMenu = false;

  }

  c->parent = 0;

  #define SWITCH SETPROPERTY_Name(sName);
  #include "_menubar_property_switch.h"       


  do {

    const char *sss = (*s).toAscii();

    *s = (*s).trimmed();

    QString sKey;

    bool bb;
    QString ss;
    int nn;

    #define SWITCH loadProperty(s, &sKey, &bb, &ss, &nn);
    #include "_menubar_property_switch.h"       


    // MENUBAR_CONTROL // CONTROL 

    if (sKey == "Caption"){      
      #define SWITCH SETPROPERTY_Caption(ss);
      #include "_menubar_property_switch.h"         

    } else if (sKey == "ParentIndex"){      
      #define SWITCH SETPROPERTY_ParentIndex(nn);
      #include "_menubar_property_switch.h"   

      c->nIndex = nn;//ss.toInt();

    } else if (sKey == "Enabled"){      
      #define SWITCH SETPROPERTY_Enabled(bb);
      #include "_menubar_property_switch.h"   

      c->bEnabled = bb;

    } else if (sKey == "Checked"){      
      #define SWITCH SETPROPERTY_Checked(bb);
      #include "_menubar_property_switch.h"   

      c->bChecked = bb;

    } else if (sKey == "Checkable"){      
      #define SWITCH SETPROPERTY_Checkable(bb);
      #include "_menubar_property_switch.h"   

    } else if (sKey == "Visible"){      
      #define SWITCH SETPROPERTY_Visible(bb);
      #include "_menubar_property_switch.h"   

    } else if (sKey == "MenuBarRole"){      
      #define SWITCH SETPROPERTY_MenuBarRole(ss);
      #include "_menubar_property_switch.h"   

    } else if (sKey == "ActionId"){      
      #define SWITCH SETPROPERTY_ActionId(ss);
      #include "_menubar_property_switch.h"   

    } else if (sKey == "Data"){      
      #define SWITCH SETPROPERTY_Data(ss);
      #include "_menubar_property_switch.h"   

    } else if (sKey == "SoundOnEvent"){      
      #define SWITCH SETPROPERTY_SoundOnEvent(ss);
      #include "_menubar_property_switch.h"   

      

    } else if (sKey == "Separator"){      
      #define SWITCH SETPROPERTY_Separator(bb);
      #include "_menubar_property_switch.h"  

      c->bSeparator = bb;
/*
    } else if (sKey == "Checked"){      
      #define SWITCH SETPROPERTY_Checked(bb);
      #include "_menubar_property_switch.h"  
*/

    } else if (sKey == "BooleanValue"){      
      #define SWITCH SETPROPERTY_BooleanValue(bb);
      #include "_menubar_property_switch.h"  

    } else if (sKey == "Key"){      
      #define SWITCH SETPROPERTY_Key(ss);
      #include "_menubar_property_switch.h"   

      c->sKey = ss;

    } else if (sKey == "ParentControl"){      
      #define SWITCH SETPROPERTY_ParentControl(ss);
      #include "_menubar_property_switch.h"   

    } else if (sKey == "Icon"){   
      #define SWITCH SETPROPERTY_Icon(ss);
      #include "_menubar_property_switch.h"   

      c->sIcon = ss;

    } else if (sKey == "StatusTip"){      
      #define SWITCH SETPROPERTY_StatusTip(ss);
      #include "_menubar_property_switch.h"   

    } else if (sKey == "Tag"){      
      #define SWITCH SETPROPERTY_Tag(ss);
      #include "_menubar_property_switch.h"   

    } else if (sKey == "Group"){      
      #define SWITCH SETPROPERTY_Group(ss);
      #include "_menubar_property_switch.h"   

    // MENUBAR_EVENT

    } else if (sKey == "OnEvent"){      
      #define SWITCH SETPROPERTY_OnEvent(bb);
      #include "_menubar_property_switch.h"  

    }

    // ***

  } while ( !((*s).length() <= 0 || (*s).startsWith("End")/* || (*s).startsWith("End ") || (*s).startsWith("End'") || (*s).startsWith("End\n") || (*s).startsWith("End ")*/) );

  *s = (*s).mid(3); // eat 'End'

  return true;
}


#ifdef IDE
QString _menubar::getMenuBarItems(QString sFile)
{
  QString s = "";
  QString re = "";
  int n = getMenuBarClassSourceCodeFilePos(sFile, &s);
  s = s.left(n);

  n = 0;

  while ((n = s.indexOf("Begin MenuItem ", n)) >= 0){
    n += 15;
    int n2 = s.indexOf("\n", n);
  
    QString sItem = s.mid(n, n2 - n).simplified();  
    re += "Dim " + sItem + " As MenuBarItem\n";

    n = n2;
  }

  n = 0;
  while ((n = s.indexOf("Begin ChildMenu ", n)) >= 0){
    n += 16;
    int n2 = s.indexOf("\n", n);
  
    QString sItem = s.mid(n, n2 - n).simplified();  
    re += "Dim " + sItem + " As MenuBarItem\n";

    n = n2;
  }

  n = 0;
  while ((n = s.indexOf("Begin Menu ", n)) >= 0){
    n += 11;
    int n2 = s.indexOf("\n", n);
  
    QString sItem = s.mid(n, n2 - n).simplified();  
    re += "Dim " + sItem + " As MenuBarItem\n";

    n = n2;
  }

  return re;
}
#endif



#ifdef RUN
void _menubar::METHOD_SetWithTag(QString Tag, QString PropertyName, t_boolean bb)
{
  if (EXTERN_my_menubar == 0){ EXTERN_myInterpreter->runtimeError("no menubar object created"); return; }

  EXTERN_my_menubar->METHOD_2SetWithTag(Tag, PropertyName, bb);
}

void _menubar::METHOD_2SetWithTag(QString Tag, QString PropertyName, t_boolean bb)
{
  if (EXTERN_my_menubar == 0){ EXTERN_myInterpreter->runtimeError("no menubar object created"); return; }

  _menubaritem *c;

  _controlType ct = t_menubaritem;

  if (firstControl(&c)){
   
    do {

      if (c->GETPROPERTY_Tag().compare(Tag, Qt::CaseInsensitive) == 0){

        if (PropertyName.compare("Separator", Qt::CaseInsensitive) == 0){
          #define SWITCH SETPROPERTY_Separator(bb);
          #include "_menubar_property_switch.h"  
        } else if (PropertyName.compare("Enabled", Qt::CaseInsensitive) == 0){
          #define SWITCH SETPROPERTY_Enabled(bb);
          #include "_menubar_property_switch.h"  
        } else if (PropertyName.compare("Checked", Qt::CaseInsensitive) == 0){
          #define SWITCH SETPROPERTY_Checked(bb);
          #include "_menubar_property_switch.h"  
        } else if (PropertyName.compare("Checkable", Qt::CaseInsensitive) == 0){
          #define SWITCH SETPROPERTY_Checkable(bb);
          #include "_menubar_property_switch.h"  
        } else if (PropertyName.compare("Visible", Qt::CaseInsensitive) == 0){
          #define SWITCH SETPROPERTY_Visible(bb);
          #include "_menubar_property_switch.h"  
        }  
        
      }

    } while (nextControl(&c)); 
  }

}

void _menubar::METHOD_SetWithTag(QString Tag, QString PropertyName, t_integer nn)
{
  if (EXTERN_my_menubar == 0){ EXTERN_myInterpreter->runtimeError("no menubar object created"); return; }

  EXTERN_my_menubar->METHOD_2SetWithTag(Tag, PropertyName, nn);
}

void _menubar::METHOD_2SetWithTag(QString Tag, QString PropertyName, t_integer nn)
{
}

void _menubar::METHOD_SetWithTag(QString Tag, QString PropertyName, QString ss)
{
  if (EXTERN_my_menubar == 0){ EXTERN_myInterpreter->runtimeError("no menubar object created"); return; }

  EXTERN_my_menubar->METHOD_2SetWithTag(Tag, PropertyName, ss);
}

void _menubar::METHOD_2SetWithTag(QString Tag, QString PropertyName, QString ss)
{
  if (EXTERN_my_menubar == 0){ EXTERN_myInterpreter->runtimeError("no menubar object created"); return; }

  _menubaritem *c;

  if (firstControl(&c)){
   
    do {

      if (c->GETPROPERTY_Tag().compare(Tag, Qt::CaseInsensitive) == 0){

        if (PropertyName.compare("Name", Qt::CaseInsensitive) == 0){
          #define SWITCH SETPROPERTY_Name(ss);
          #include "_menubar_property_switch.h"  
        } else if (PropertyName.compare("Caption", Qt::CaseInsensitive) == 0){
          #define SWITCH SETPROPERTY_Caption(ss);
          #include "_menubar_property_switch.h"  
        } else if (PropertyName.compare("ActionId", Qt::CaseInsensitive) == 0){
          #define SWITCH SETPROPERTY_ActionId(ss);
          #include "_menubar_property_switch.h"  
        } else if (PropertyName.compare("Text", Qt::CaseInsensitive) == 0){
          #define SWITCH SETPROPERTY_Caption(ss);
          #include "_menubar_property_switch.h"  
        } else if (PropertyName.compare("Value", Qt::CaseInsensitive) == 0){
          #define SWITCH SETPROPERTY_Caption(ss);
          #include "_menubar_property_switch.h"  
        } else if (PropertyName.compare("Tag", Qt::CaseInsensitive) == 0){
          #define SWITCH SETPROPERTY_Tag(ss);
          #include "_menubar_property_switch.h"  
        } else if (PropertyName.compare("Icon", Qt::CaseInsensitive) == 0){
          #define SWITCH SETPROPERTY_Icon(ss);
          #include "_menubar_property_switch.h"  
        } else if (PropertyName.compare("StatusTip", Qt::CaseInsensitive) == 0){
          #define SWITCH SETPROPERTY_StatusTip(ss);
          #include "_menubar_property_switch.h"  
        } else if (PropertyName.compare("MenuBarRole", Qt::CaseInsensitive) == 0){
          #define SWITCH SETPROPERTY_MenuBarRole(ss);
          #include "_menubar_property_switch.h"  
        } else if (PropertyName.compare("Group", Qt::CaseInsensitive) == 0){
          #define SWITCH SETPROPERTY_Group(ss);
          #include "_menubar_property_switch.h"  
        } else if (PropertyName.compare("Data", Qt::CaseInsensitive) == 0){
          #define SWITCH SETPROPERTY_Data(ss);
          #include "_menubar_property_switch.h"  
        } else if (PropertyName.compare("SoundOnEvent", Qt::CaseInsensitive) == 0){
          #define SWITCH SETPROPERTY_SoundOnEvent(ss);
          #include "_menubar_property_switch.h"  
        }  

        
        
      }

    } while (nextControl(&c)); 
  }
}

void _menubar::METHOD_SetWithGroup(QString Group, QString PropertyName, t_boolean bb)
{
  if (EXTERN_my_menubar == 0){ EXTERN_myInterpreter->runtimeError("no menubar object created"); return; }

  EXTERN_my_menubar->METHOD_2SetWithGroup(Group, PropertyName, bb);
}

void _menubar::METHOD_2SetWithGroup(QString Group, QString PropertyName, t_boolean bb)
{
  if (EXTERN_my_menubar == 0){ EXTERN_myInterpreter->runtimeError("no menubar object created"); return; }

  _menubaritem *c;

  if (firstControl(&c)){
   
    do {

      if (c->GETPROPERTY_Group().compare(Group, Qt::CaseInsensitive) == 0){

        if (PropertyName.compare("Separator", Qt::CaseInsensitive) == 0){
          #define SWITCH SETPROPERTY_Separator(bb);
          #include "_menubar_property_switch.h"  
        } else if (PropertyName.compare("Enabled", Qt::CaseInsensitive) == 0){
          #define SWITCH SETPROPERTY_Enabled(bb);
          #include "_menubar_property_switch.h"  
        } else if (PropertyName.compare("Checked", Qt::CaseInsensitive) == 0){
          #define SWITCH SETPROPERTY_Checked(bb);
          #include "_menubar_property_switch.h"  
        } else if (PropertyName.compare("Checkable", Qt::CaseInsensitive) == 0){
          #define SWITCH SETPROPERTY_Checkable(bb);
          #include "_menubar_property_switch.h"  
        } else if (PropertyName.compare("Visible", Qt::CaseInsensitive) == 0){
          #define SWITCH SETPROPERTY_Visible(bb);
          #include "_menubar_property_switch.h"  
        }  
        
      }

    } while (nextControl(&c)); 
  }
}

void _menubar::METHOD_SetWithGroup(QString Group, QString PropertyName, t_integer nn)
{
  if (EXTERN_my_menubar == 0){ EXTERN_myInterpreter->runtimeError("no menubar object created"); return; }

  EXTERN_my_menubar->METHOD_2SetWithGroup(Group, PropertyName, nn);
}

void _menubar::METHOD_2SetWithGroup(QString Group, QString PropertyName, t_integer nn)
{
  if (EXTERN_my_menubar == 0){ EXTERN_myInterpreter->runtimeError("no menubar object created"); return; }
}

void _menubar::METHOD_SetWithGroup(QString Group, QString PropertyName, QString ss)
{
  if (EXTERN_my_menubar == 0){ EXTERN_myInterpreter->runtimeError("no menubar object created"); return; }

  EXTERN_my_menubar->METHOD_2SetWithGroup(Group, PropertyName, ss);
}

void _menubar::METHOD_2SetWithGroup(QString Group, QString PropertyName, QString ss)
{
  if (EXTERN_my_menubar == 0){ EXTERN_myInterpreter->runtimeError("no menubar object created"); return; }

  _menubaritem *c;

  if (firstControl(&c)){
   
    do {

      if (c->GETPROPERTY_Group().compare(Group, Qt::CaseInsensitive) == 0){

        if (PropertyName.compare("Name", Qt::CaseInsensitive) == 0){
          #define SWITCH SETPROPERTY_Name(ss);
          #include "_menubar_property_switch.h"  
        } else if (PropertyName.compare("ActionId", Qt::CaseInsensitive) == 0){
          #define SWITCH SETPROPERTY_ActionId(ss);
          #include "_menubar_property_switch.h"  
        } else if (PropertyName.compare("Caption", Qt::CaseInsensitive) == 0){
          #define SWITCH SETPROPERTY_Caption(ss);
          #include "_menubar_property_switch.h"  
        } else if (PropertyName.compare("Text", Qt::CaseInsensitive) == 0){
          #define SWITCH SETPROPERTY_Caption(ss);
          #include "_menubar_property_switch.h"  
        } else if (PropertyName.compare("Value", Qt::CaseInsensitive) == 0){
          #define SWITCH SETPROPERTY_Caption(ss);
          #include "_menubar_property_switch.h"  
        } else if (PropertyName.compare("Tag", Qt::CaseInsensitive) == 0){
          #define SWITCH SETPROPERTY_Tag(ss);
          #include "_menubar_property_switch.h"  
        } else if (PropertyName.compare("Icon", Qt::CaseInsensitive) == 0){
          #define SWITCH SETPROPERTY_Icon(ss);
          #include "_menubar_property_switch.h"  
        } else if (PropertyName.compare("StatusTip", Qt::CaseInsensitive) == 0){
          #define SWITCH SETPROPERTY_StatusTip(ss);
          #include "_menubar_property_switch.h"  
        } else if (PropertyName.compare("MenuBarRole", Qt::CaseInsensitive) == 0){
          #define SWITCH SETPROPERTY_MenuBarRole(ss);
          #include "_menubar_property_switch.h"  
        } else if (PropertyName.compare("Group", Qt::CaseInsensitive) == 0){
          #define SWITCH SETPROPERTY_Group(ss);
          #include "_menubar_property_switch.h"  
        } else if (PropertyName.compare("Data", Qt::CaseInsensitive) == 0){
          #define SWITCH SETPROPERTY_Data(ss);
          #include "_menubar_property_switch.h"  
        } else if (PropertyName.compare("SoundOnEvent", Qt::CaseInsensitive) == 0){
          #define SWITCH SETPROPERTY_SoundOnEvent(ss);
          #include "_menubar_property_switch.h"  
        }  
        
        
      }

    } while (nextControl(&c)); 
  }
}

#endif