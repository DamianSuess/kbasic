/*
***************************************************************************
Copyright (C) 2000-2008 KBasic Software.  All rights reserved.

_toolbarview.h
---------------------------------------------------------------------------
19.02.2004 - new header for this file (BN)
***************************************************************************
*/


#ifndef _TOOLBARVIEW_H
#define _TOOLBARVIEW_H

#include <QLabel>

#include "typedef.h"



#include "_property.h"
#include "_control0.h"

#include "_toolbar.h"

#define TEST _toolbarview    
#define TEST2 _toolbarviews   
#define TEST3 "ToolBarView"

#ifdef RUN
  #define SUPERCLASS _toolbar
#else
  #define SUPERCLASS QLabel
#endif

#define _TOOLBARVIEW true

class _form;
class kb_form;


#ifdef RUN
  class _toolbarview : public _toolbar, public _property
#else
  class _toolbarview : public QLabel, public _property
#endif

{
  Q_OBJECT
public:


#ifdef RUN
  _toolbarview(_form *f = 0, QWidget *parent = 0) : _toolbar (f, parent)
#else
  _toolbarview(_form *f = 0, QLabel *parent = 0) : QLabel (parent ? parent : (QLabel *) f)
#endif

{

#ifdef IDE
  constructor(f, parent);

  setAutoFillBackground(true);
  QPalette p = palette();
  p.setColor(QPalette::Window, Qt::white);  
  setPalette(p);
#else
  constructor(f, 0);  

#endif



  // properties
  addProperty("StringValue", pt_qstring); addProperty("OldStringValue", pt_qstring);
  
  // events
  if (bForm) addProperty("OnEvent", pt_event);


  // default values
  SETPROPERTY_ControlType("ToolBarView");
  SETPROPERTY_MouseTracking(true);

#ifdef IDE
  setText("Control 'ToolBarView'");
  SETPROPERTY_Layout("RelativeWidth;");
#endif

}

#include "__property_x.h"
#include "__property_y.h"
#include "__property_stringvalue.h"


#ifdef RUN

// KBBINDINGEVENTS
public slots:

virtual void EVENT_OnEvent(QString ToolBarItemName)
{
}

public:

void METHOD_SetWithTag(QString Tag, QString PropertyName, t_boolean Value)
{
  _toolbar::METHOD_SetWithTag(Tag, PropertyName, Value, this);
}

void METHOD_SetWithTag1(QString Tag, QString PropertyName, t_integer Value)
{
  _toolbar::METHOD_SetWithTag(Tag, PropertyName, Value, this);
}

void METHOD_SetWithTag2(QString Tag, QString PropertyName, QString Value)
{
  _toolbar::METHOD_SetWithTag(Tag, PropertyName, Value, this);
}

void METHOD_SetWithGroup(QString Group, QString PropertyName, t_boolean Value)
{
  _toolbar::METHOD_SetWithGroup(Group, PropertyName, Value, this);
}

void METHOD_SetWithGroup1(QString Group, QString PropertyName, t_integer Value)
{
  _toolbar::METHOD_SetWithGroup(Group, PropertyName, Value, this);
}

void METHOD_SetWithGroup2(QString Group, QString PropertyName, QString Value)
{
  _toolbar::METHOD_SetWithGroup(Group, PropertyName, Value, this);
}

kb_toolbaritem *METHOD_ToolBarItem(QString ToolBarItemName)
{
  return _toolbar::METHOD_ToolBarItem(ToolBarItemName, this);
}

void METHOD_InsertControl(t_integer Index, _control *Control)
{
  _toolbar::METHOD_InsertControl(Index, Control, this);
}

void METHOD_SetEnabled(QString ToolBarItemName, t_boolean Enabled)
{
  _toolbar::METHOD_2SetEnabled(ToolBarItemName, Enabled, this);
}

t_boolean METHOD_IsEnabled(QString ToolBarItemName)
{
  return _toolbar::METHOD_2IsEnabled(ToolBarItemName, this);
}

void METHOD_SetVisible(QString ToolBarItemName, t_boolean Visible)
{
  _toolbar::METHOD_2SetVisible(ToolBarItemName, Visible, this);
}

t_boolean METHOD_IsVisible(QString ToolBarItemName)
{
  return _toolbar::METHOD_2IsVisible(ToolBarItemName, this);
}


#endif

// ***
#include "_control1_binding.h"


// ***
#include "_control1.h"


};

#include "_control2.h"

#undef _TOOLBARVIEW

#undef TEST
#undef TEST2
#undef TEST3
#undef SUPERCLASS

#endif