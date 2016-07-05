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




#ifndef _MENUBARITEM_H
#define _MENUBARITEM_H


#include "typedef.h"


#ifdef RUN
#include "_sounds.h"
extern _sounds2 *EXTERN_my_sounds;

#include <QSvgWidget>
#include <QSvgRenderer>

#endif

#include "_property.h"
#include "_control0.h"

#define TEST _menubaritem    
#define TEST2 _menubaritems   
#define TEST3 "MenuBarItem"
//#define SUPERCLASS ?   
#undef SUPERCLASS

#define _MENUBARITEM true


class QAction;
class _qmenubar;
class _qmenu;

#ifdef RUN
extern const QPixmap &interpreter_loadPixmap(QString fn);
#endif

class _menubaritem : public QObject, public _property
{
#ifdef LINUX // HIDE
    Q_OBJECT
#endif // HIDE
#ifdef MAC // HIDE
    Q_OBJECT // HIDE
#endif // HIDE
#ifdef WINDOWS // HIDE
#ifdef RUN // HIDE
    Q_OBJECT // HIDE
#endif // HIDE
#endif // HIDE
public:


_menubaritem(_form *f)
{
  my_form = f;

  init(0, 0, 0);
}

_menubaritem(_qmenu *_my_qmenu, _menubaritem *_parent, 
          int _nIndex)
{
  my_form = 0;
  init(_my_qmenu, _parent, _nIndex);
}

#ifdef RUN
~_menubaritem()
{  
  if (my_qaction) delete my_qaction; my_qaction = 0;
  if (movie) delete movie; if (moviea) delete moviea; if (movieb) delete movieb;
}
#endif

void init(_qmenu *_my_qmenu, _menubaritem *_parent, 
          int _nIndex)
{
#ifdef RUN
  movie = 0; moviea = 0; movieb = 0;
#endif

//  constructor2(0, 0);
  my_qaction = 0;
  
  my_qmenu = _my_qmenu;
  nIndex = _nIndex;
  parent = _parent;

  bDynamicMenuItem = false;


  // properties

  addProperty("ActionId", pt_qstring);
  addProperty("Tag", pt_qstring);

  addProperty("ParentControl", pt_qstring);
  addProperty("ParentIndex", pt_integer);
  addProperty("Key", pt_qstring);

  addProperty("Separator", pt_boolean);
  addProperty("BooleanValue", pt_boolean);

  addProperty("Enabled", pt_boolean);
  addProperty("Checked", pt_boolean);

  addProperty("Icon", pt_qstring);

  addProperty("Caption", pt_qstring);
  addProperty("StatusTip", pt_qstring);
  addProperty("WhatsThis", pt_qstring);

  addProperty("Checkable", pt_boolean);
  addProperty("Visible", pt_boolean);

  addProperty("MenuBarRole", pt_qstring);
  addProperty("Data", pt_qstring);


  // events
  addProperty("OnEvent", pt_event);


  // default values
  SETPROPERTY_Caption("MenuBarItem");

  addProperty("Name", pt_qstring);
  addProperty("Group", pt_qstring);
  addProperty("ControlType", pt_qstring);
  SETPROPERTY_ControlType("MenuBarItem");

  SETPROPERTY_Visible(true);
  SETPROPERTY_Enabled(true);

}


#include "../kbshared/__property_visible.h"
#include "../kbshared/__property_menubarrole.h"

#include "../kbshared/__property_name.h"
#include "../kbshared/__property_group.h"
#include "../kbshared/__property_controltype.h"
#include "../kbshared/__property_parentcontrol.h"
#include "../kbshared/__property_caption.h"
#include "../kbshared/__property_separator.h"
//#include "../kbshared/__property_tag.h"

#include "../kbshared/__property_booleanvalue.h"
#include "../kbshared/__property_enabled.h"
#include "../kbshared/__property_checked.h"
#include "../kbshared/__property_checkable.h"
#include "../kbshared/__property_icon.h"

//#include "../kbshared/__property_parentindex.h"
#include "../kbshared/__property_key.h"
#include "../kbshared/__property_statustip.h"
#include "../kbshared/__property_whatsthis.h"

//#include "../kbshared/__property_event.h"


void SoundOnEvent()
{
#ifdef RUN
  QString s = GETPROPERTY_SoundOnEvent();
  if (!s.isEmpty()){
    EXTERN_my_sounds->playOnce(s);
  }
#endif
}

virtual void EVENT_OnEvent()
{ 
}

// events

void setAcceptDrops(bool b)
{
  bAcceptDrops = b;
}

bool acceptDrops()
{
  return bAcceptDrops;
}


public:
  QAction *my_qaction;
  _qmenu *my_qmenu;
  _qmenu *my_qmenu_childs;
 
  int nIndex;
  //int nId;
  _menubaritem *parent;
  bool bVisible;
  bool bCheckable;
  bool bEnabled;
  bool bChecked;
  bool bSeparator;
  bool bMenu;
  bool bSubMenu;
  QString sKey;
  QString sIcon;
  QString sTitle;
  //QIcon is;
  bool bDynamicMenuItem;

  QString sName;
  QString sGroup;
  const char *acName;
  const char *acGroup;
  QByteArray a;
  QByteArray b;

private:
  bool bAcceptDrops;
  

  _form *my_form;

#ifdef RUN
  QMovie *movie; QByteArray *moviea; QBuffer *movieb; QIcon ic;   
#endif


public slots:
#ifdef RUN
void frameChanged(int);
#endif

};

#include "_control2.h"

#undef TEST
#undef TEST2
#undef TEST3

#undef _MENUBARITEM

#endif






