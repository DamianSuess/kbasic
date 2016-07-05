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


#ifndef _TOOLBARITEM_H
#define _TOOLBARITEM_H


#include "typedef.h"


#ifdef RUN
#include "_sounds.h"
extern _sounds2 *EXTERN_my_sounds;

#include <QSvgWidget>
#include <QSvgRenderer>


#endif

#include "_property.h"
#include "_control0.h"

#define TEST _toolbaritem    
#define TEST2 _toolbaritems   
#define TEST3 "ToolBarItem"
//#define SUPERCLASS ?   
#undef SUPERCLASS

#define _TOOLBARITEM true

class _toolbar;



#ifdef RUN
extern const QPixmap &interpreter_loadPixmap(QString fn);
#endif

class _toolbaritem : public QObject, public _property
{

#ifdef LINUX // HIDE
    Q_OBJECT // HIDE
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


_toolbaritem(int _nIndex)
{
#ifdef RUN
   movie = 0; moviea = 0; movieb = 0;
#endif

   my_qaction = 0;
   my_qtoolbutton = 0;
   my_toolbar = 0;

  nIndex = _nIndex;
  

  addProperty("ActionId", pt_qstring);
  addProperty("Tag", pt_qstring);

  addProperty("ParentIndex", pt_integer);

  addProperty("Separator", pt_boolean);

  addProperty("Enabled", pt_boolean);

  addProperty("Visible", pt_boolean);
  addProperty("Checked", pt_boolean);
  addProperty("Checkable", pt_boolean);
  addProperty("Group", pt_qstring);

  addProperty("Icon", pt_qstring);

  addProperty("ContextMenu", pt_qstring);
  addProperty("StatusTip", pt_qstring);
  addProperty("ToolTip", pt_qstring);
  addProperty("WhatsThis", pt_qstring);
  addProperty("ToolBarRole", pt_qstring);
  addProperty("ArrowType", pt_qstring);
  addProperty("PopupMode", pt_qstring);

  // events
  addProperty("OnEvent", pt_event);

  addProperty("StringValue", pt_qstring); addProperty("OldStringValue", pt_qstring);
  addProperty("Caption", pt_qstring);


  // default values
  SETPROPERTY_Caption("ToolBarItem");

  addProperty("Name", pt_qstring);
  addProperty("Group", pt_qstring);
  addProperty("ControlType", pt_qstring);
  SETPROPERTY_ControlType("ToolBarItem");

  SETPROPERTY_Visible(true);
  SETPROPERTY_Enabled(true);

}

#ifdef RUN
~_toolbaritem()
{
  if (movie) delete movie; if (moviea) delete moviea; if (movieb) delete movieb;
}
#endif

#include "__property_contextmenu.h"

#include "__property_stringvalue.h"
#include "__property_caption.h"

#include "../kbshared/__property_checked.h"
#include "../kbshared/__property_checkable.h"
#include "../kbshared/__property_toolbarrole.h"

#include "../kbshared/__property_visible.h"
#include "../kbshared/__property_name.h"
#include "../kbshared/__property_group.h"
#include "../kbshared/__property_controltype.h"
#include "../kbshared/__property_parentcontrol.h"
#include "../kbshared/__property_separator.h"
//#include "../kbshared/__property_tag.h"

#include "../kbshared/__property_enabled.h"
#include "../kbshared/__property_icon.h"


#include "../kbshared/__property_tooltip.h"
#include "../kbshared/__property_statustip.h"
#include "../kbshared/__property_whatsthis.h"

#include "../kbshared/__property_arrowtype.h"

#include "../kbshared/__property_popupmode.h"


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
  QToolButton *my_qtoolbutton;
  _toolbar *my_toolbar;

  int nIndex;
  bool bEnabled;
  bool bSeparator;
  QString sIcon;

  QString sName;
  QString sGroup;
  const char *acName;
  const char *acGroup;
  QByteArray a;
  QByteArray b;

private:
  bool bAcceptDrops;

#ifdef RUN
  QMovie *movie; QByteArray *moviea; QBuffer *movieb;
#endif



public slots:
void frameChanged(int)
{

  #ifdef RUN
    if (my_qaction) my_qaction->setIcon(movie->currentPixmap());
  #endif

}
};

#include "_control2.h"

#undef TEST
#undef TEST2
#undef TEST3

#undef _TOOLBARITEM

#endif





