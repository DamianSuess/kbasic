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

#ifndef _PROPERTY_H
#define _PROPERTY_H



#include "typedef.h"



#include <QString>
#include <QMap>
#include <QFont>
#include <QColor>
#include <QWidget>


enum _propertyType {
  pt_notype = 0,
  pt_event,
  pt_integer,
  pt_boolean,
  pt_qstring
};


class t_property {
public:

t_property(t_property *p)
{
  propertyType = p->propertyType;

  used = p->used;
  display = p->display;
  set = p->set;

  v_integer = p->v_integer;
  v_boolean = p->v_boolean;
  v_qstring = p->v_qstring;
  v_event = p->v_event;
}

t_property()
{
  used = false;
  display = true;
  set = true;
//  defaultValue = false;

  v_integer = 0;
  v_boolean = false;
  v_qstring = "";
  v_event = false;
}


  bool used;

  bool display; // if the value can be displayed
  bool set; // if the value can be used
  bool readOnly;

  _propertyType propertyType;
  
  t_integer v_integer;
  t_boolean v_boolean;
  QString v_qstring;
  t_double v_double;
  t_boolean v_event;
  
};

typedef QMap<QString, t_property*> t_properties;
typedef QMap<QString, t_property> t_properties2;


class _property
{
public:

// if (bInitControl)bModified = true; bModified2 = true;  

void SETPROPERTY_Name(const QString & n){ properties["Name"]->v_qstring = n; properties["Name"]->used = true; bModified = true; }
QString GETPROPERTY_Name(){ return properties["Name"]->v_qstring; }

void SETPROPERTY_LoadedName(const QString & n){ properties["LoadedName"]->v_qstring = n; properties["LoadedName"]->used = true; bModified = true; }
QString GETPROPERTY_LoadedName(){ return properties["LoadedName"]->v_qstring; }

void SETPROPERTY_LoadedType(const QString & n){ properties["LoadedType"]->v_qstring = n; properties["LoadedType"]->used = true; bModified = true; }
QString GETPROPERTY_LoadedType(){ return properties["LoadedType"]->v_qstring; }

void SETPROPERTY_Type(const QString & n){ properties["Type"]->v_qstring = n; properties["Type"]->used = true; bModified = true; }
QString GETPROPERTY_Type(){ return properties["Type"]->v_qstring; }

void SETPROPERTY_ControlType(const QString & n){ properties["ControlType"]->v_qstring = n; properties["ControlType"]->used = true; bModified = true; }
QString GETPROPERTY_ControlType(){ return properties["ControlType"]->v_qstring; }

void SETPROPERTY_GlobalX(t_integer n){ 
  properties["GlobalX"]->v_integer = n; 
  properties["GlobalX"]->used = true; 
  bModified = true;
}

void SETPROPERTY_X(t_integer n){ 
  properties["OldX"]->v_integer = properties["X"]->v_integer; 
  properties["X"]->v_integer = n; 

  
  properties["GlobalX"]->used = true; 

  properties["OldX"]->used = true; 
  properties["X"]->used = true; 
  bModified = true;
}
t_integer GETPROPERTY_X(){ return properties["X"]->v_integer; }
t_integer GETPROPERTY_OldX(){ return properties["OldX"]->v_integer; }
t_integer GETPROPERTY_GlobalX(){ return properties["GlobalX"]->v_integer; }


void SETPROPERTY_GlobalY(t_integer n){ 
  properties["GlobalY"]->v_integer = n; 
  properties["GlobalY"]->used = true; 
  bModified = true;
}

void SETPROPERTY_Y(t_integer n){ 
  properties["OldY"]->v_integer = properties["Y"]->v_integer; 
  properties["Y"]->v_integer = n; 

  
  properties["GlobalY"]->used = true; 

  properties["OldY"]->used = true; 
  properties["Y"]->used = true; 
  bModified = true;
}
t_integer GETPROPERTY_Y(){ return properties["Y"]->v_integer; }
t_integer GETPROPERTY_OldY(){ return properties["OldY"]->v_integer; }
t_integer GETPROPERTY_GlobalY(){ return properties["GlobalY"]->v_integer; }


void SETPROPERTY_Width(t_integer n){ 
  properties["OldWidth"]->v_integer = properties["Width"]->v_integer; 
  properties["Width"]->v_integer = n; 
  properties["OldWidth"]->used = true; 
  properties["Width"]->used = true; 
  bModified = true;
}
t_integer GETPROPERTY_Width(){ return properties["Width"]->v_integer; }
t_integer GETPROPERTY_OldWidth(){ return properties["OldWidth"]->v_integer; }


void SETPROPERTY_Height(t_integer n){ 
  properties["OldHeight"]->v_integer = properties["Height"]->v_integer; 
  properties["Height"]->v_integer = n; 
  properties["OldHeight"]->used = true; 
  properties["Height"]->used = true; 
  bModified = true;
}
t_integer GETPROPERTY_Height(){ return properties["Height"]->v_integer; }
t_integer GETPROPERTY_OldHeight(){ return properties["OldHeight"]->v_integer; }


void SETPROPERTY_Caption(const QString & n){ if (!properties.contains("Caption")) return; properties["Caption"]->v_qstring = n; properties["Caption"]->used = true; bModified = true; }
QString GETPROPERTY_Caption(){ if (!properties.contains("Caption")) return ""; return properties["Caption"]->v_qstring; }

void SETPROPERTY_Text(const QString & n){ if (!properties.contains("Text")) return; properties["Text"]->v_qstring = n; properties["Text"]->used = true; bModified = true; }
QString GETPROPERTY_Text(){ if (!properties.contains("Text")) return ""; return properties["Text"]->v_qstring; }

void SETPROPERTY_IntegerValue(t_integer n)
{ 
  if (!properties.contains("OldIntegerValue")) return; 
  if (!properties.contains("IntegerValue")) return; 

  properties["OldIntegerValue"]->v_integer = properties["IntegerValue"]->v_integer; 

  properties["IntegerValue"]->v_integer = n; 
  properties["IntegerValue"]->used = true; 
 bModified = true; 
}
t_integer GETPROPERTY_IntegerValue(){ if (!properties.contains("IntegerValue")) return 0; return properties["IntegerValue"]->v_integer; }

void SETPROPERTY_Enabled(t_boolean n){ if (!properties.contains("Enabled")) return; properties["Enabled"]->v_boolean = n; properties["Enabled"]->used = true; bModified = true; }
t_boolean GETPROPERTY_Enabled(){ if (!properties.contains("Enabled")) return false; return properties["Enabled"]->v_boolean; }

void SETPROPERTY_Flip(t_boolean n){ if (!properties.contains("Flip")) return; properties["Flip"]->v_boolean = n; properties["Flip"]->used = true; bModified = true; }
t_boolean GETPROPERTY_Flip(){ if (!properties.contains("Flip")) return false; return properties["Flip"]->v_boolean; }

void SETPROPERTY_Checked(t_boolean n){ if (!properties.contains("Checked")) return; properties["Checked"]->v_boolean = n; properties["Checked"]->used = true; bModified = true; }
t_boolean GETPROPERTY_Checked(){ if (!properties.contains("Checked")) return false; return properties["Checked"]->v_boolean; }

void SETPROPERTY_CheckableExclusive(t_boolean n){ if (!properties.contains("CheckableExclusive")) return; properties["CheckableExclusive"]->v_boolean = n; properties["CheckableExclusive"]->used = true; bModified = true; }
t_boolean GETPROPERTY_CheckableExclusive(){ if (!properties.contains("CheckableExclusive")) return false; return properties["CheckableExclusive"]->v_boolean; }

void SETPROPERTY_Visible(t_boolean n){ if (!properties.contains("Visible")) return; properties["Visible"]->v_boolean = n; properties["Visible"]->used = true; bModified = true; }
t_boolean GETPROPERTY_Visible(){ if (!properties.contains("Visible")) return false; return properties["Visible"]->v_boolean; }

void SETPROPERTY_Resizable(t_boolean n){ if (!properties.contains("Resizable")) return; properties["Resizable"]->v_boolean = n; properties["Resizable"]->used = true; bModified = true; }
t_boolean GETPROPERTY_Resizable(){ if (!properties.contains("Resizable")) return false; return properties["Resizable"]->v_boolean; }

void SETPROPERTY_ResizableSmaller(t_boolean n){ if (!properties.contains("ResizableSmaller")) return; properties["ResizableSmaller"]->v_boolean = n; properties["ResizableSmaller"]->used = true; bModified = true; }
t_boolean GETPROPERTY_ResizableSmaller(){ if (!properties.contains("ResizableSmaller")) return false; return properties["ResizableSmaller"]->v_boolean; }

void SETPROPERTY_ResizableBigger(t_boolean n){ if (!properties.contains("ResizableBigger")) return; properties["ResizableBigger"]->v_boolean = n; properties["ResizableBigger"]->used = true; bModified = true; }
t_boolean GETPROPERTY_ResizableBigger(){ if (!properties.contains("ResizableBigger")) return false; return properties["ResizableBigger"]->v_boolean; }


void SETPROPERTY_Separator(t_boolean n){ if (!properties.contains("Separator")) return; properties["Separator"]->v_boolean = n; properties["Separator"]->used = true; bModified = true; }
t_boolean GETPROPERTY_Separator(){ if (!properties.contains("Separator")) return false; return properties["Separator"]->v_boolean; }

void SETPROPERTY_WordWrap(t_boolean n){ if (!properties.contains("WordWrap")) return; properties["WordWrap"]->v_boolean = n; properties["WordWrap"]->used = true; bModified = true; }
t_boolean GETPROPERTY_WordWrap(){ if (!properties.contains("WordWrap")) return false; return properties["WordWrap"]->v_boolean; }

void SETPROPERTY_ReadOnly(t_boolean n){ if (!properties.contains("ReadOnly")) return; properties["ReadOnly"]->v_boolean = n; properties["ReadOnly"]->used = true; bModified = true; }
t_boolean GETPROPERTY_ReadOnly(){ if (!properties.contains("ReadOnly")) return false; return properties["ReadOnly"]->v_boolean; }

void SETPROPERTY_LoadedNull(t_boolean n){ if (!properties.contains("LoadedNull")) return; properties["LoadedNull"]->v_boolean = n; properties["LoadedNull"]->used = true; bModified = true; }
t_boolean GETPROPERTY_LoadedNull(){ if (!properties.contains("LoadedNull")) return false; return properties["LoadedNull"]->v_boolean; }

void SETPROPERTY_Null(t_boolean n){ if (!properties.contains("Null")) return; properties["Null"]->v_boolean = n; properties["Null"]->used = true; bModified = true; }
t_boolean GETPROPERTY_Null(){ if (!properties.contains("Null")) return false; return properties["Null"]->v_boolean; }

void SETPROPERTY_LoadedIndex(t_boolean n){ if (!properties.contains("LoadedIndex")) return; properties["LoadedIndex"]->v_boolean = n; properties["LoadedIndex"]->used = true; bModified = true; }
t_boolean GETPROPERTY_LoadedIndex(){ if (!properties.contains("LoadedIndex")) return false; return properties["LoadedIndex"]->v_boolean; }

void SETPROPERTY_Index(t_boolean n){ if (!properties.contains("Index")) return; properties["Index"]->v_boolean = n; properties["Index"]->used = true; bModified = true; }
t_boolean GETPROPERTY_Index(){ if (!properties.contains("Index")) return false; return properties["Index"]->v_boolean; }

void SETPROPERTY_Cursor(const QString & n){ if (!properties.contains("Cursor")) return; properties["Cursor"]->v_qstring = n; properties["Cursor"]->used = true; bModified = true; }
QString GETPROPERTY_Cursor(){ if (!properties.contains("Cursor")) return ""; return properties["Cursor"]->v_qstring; }

void SETPROPERTY_Tag(const QString & n){ if (!properties.contains("Tag")) return; properties["Tag"]->v_qstring = n; properties["Tag"]->used = true; bModified = true; }
QString GETPROPERTY_Tag(){ if (!properties.contains("Tag")) return ""; return properties["Tag"]->v_qstring; }

void SETPROPERTY_MenuBarRole(const QString & n){ if (!properties.contains("MenuBarRole")) return; properties["MenuBarRole"]->v_qstring = n; properties["MenuBarRole"]->used = true; bModified = true; }
QString GETPROPERTY_MenuBarRole(){ if (!properties.contains("MenuBarRole")) return ""; return properties["MenuBarRole"]->v_qstring; }

void SETPROPERTY_Data(const QString & n){ if (!properties.contains("Data")) return; properties["Data"]->v_qstring = n; properties["Data"]->used = true; bModified = true; }
QString GETPROPERTY_Data(){ if (!properties.contains("Data")) return ""; return properties["Data"]->v_qstring; }

void SETPROPERTY_Alignment(const QString & n){ if (!properties.contains("Alignment")) return; properties["Alignment"]->v_qstring = n; properties["Alignment"]->used = true; bModified = true; }
QString GETPROPERTY_Alignment(){ if (!properties.contains("Alignment")) return ""; return properties["Alignment"]->v_qstring; }

void SETPROPERTY_EchoMode(const QString & n){ if (!properties.contains("EchoMode")) return; properties["EchoMode"]->v_qstring = n; properties["EchoMode"]->used = true; bModified = true; }
QString GETPROPERTY_EchoMode(){ if (!properties.contains("EchoMode")) return ""; return properties["EchoMode"]->v_qstring; }



void SETPROPERTY_Orientation(const QString & n){ if (!properties.contains("Orientation")) return; properties["Orientation"]->v_qstring = n; properties["Orientation"]->used = true; bModified = true; }
QString GETPROPERTY_Orientation(){ if (!properties.contains("Orientation")) return ""; return properties["Orientation"]->v_qstring; }

void SETPROPERTY_Feature(const QString & n){ if (!properties.contains("Feature")) return; properties["Feature"]->v_qstring = n; properties["Feature"]->used = true; bModified = true; }
QString GETPROPERTY_Feature(){ if (!properties.contains("Feature")) return ""; return properties["Feature"]->v_qstring; }

void SETPROPERTY_ContextMenu(const QString & n){ if (!properties.contains("ContextMenu")) return; properties["ContextMenu"]->v_qstring = n; properties["ContextMenu"]->used = true; bModified = true; }
QString GETPROPERTY_ContextMenu(){ if (!properties.contains("ContextMenu")) return ""; return properties["ContextMenu"]->v_qstring; }


void SETPROPERTY_ArrowType(const QString & n){ if (!properties.contains("ArrowType")) return; properties["ArrowType"]->v_qstring = n; properties["ArrowType"]->used = true; bModified = true; }
QString GETPROPERTY_ArrowType(){ if (!properties.contains("ArrowType")) return ""; return properties["ArrowType"]->v_qstring; }

void SETPROPERTY_PopupMode(const QString & n){ if (!properties.contains("PopupMode")) return; properties["PopupMode"]->v_qstring = n; properties["PopupMode"]->used = true; bModified = true; }
QString GETPROPERTY_PopupMode(){ if (!properties.contains("PopupMode")) return ""; return properties["PopupMode"]->v_qstring; }

void SETPROPERTY_ToolBarRole(const QString & n){ if (!properties.contains("ToolBarRole")) return; properties["ToolBarRole"]->v_qstring = n; properties["ToolBarRole"]->used = true; bModified = true; }
QString GETPROPERTY_ToolBarRole(){ if (!properties.contains("ToolBarRole")) return ""; return properties["ToolBarRole"]->v_qstring; }

// PROPERTY

void SETPROPERTY_ViewMode(const QString & n){ if (!properties.contains("ViewMode")) return; properties["ViewMode"]->v_qstring = n; properties["ViewMode"]->used = true; bModified = true; }
QString GETPROPERTY_ViewMode(){ if (!properties.contains("ViewMode")) return 0; return properties["ViewMode"]->v_qstring; }

void SETPROPERTY_Prefix(const QString & n){ if (!properties.contains("Prefix")) return; properties["Prefix"]->v_qstring = n; properties["Prefix"]->used = true; bModified = true; }
QString GETPROPERTY_Prefix(){ if (!properties.contains("Prefix")) return 0; return properties["Prefix"]->v_qstring; }

void SETPROPERTY_Suffix(const QString & n){ if (!properties.contains("Suffix")) return; properties["Suffix"]->v_qstring = n; properties["Suffix"]->used = true; bModified = true; }
QString GETPROPERTY_Suffix(){ if (!properties.contains("Suffix")) return 0; return properties["Suffix"]->v_qstring; }

void SETPROPERTY_TickPosition(const QString & n){ if (!properties.contains("TickPosition")) return; properties["TickPosition"]->v_qstring = n; properties["TickPosition"]->used = true; bModified = true; }
QString GETPROPERTY_TickPosition(){ if (!properties.contains("TickPosition")) return 0; return properties["TickPosition"]->v_qstring; }

void SETPROPERTY_InvertedAppearance(t_boolean n){ if (!properties.contains("InvertedAppearance")) return; properties["InvertedAppearance"]->v_boolean = n; properties["InvertedAppearance"]->used = true; bModified = true; }
t_boolean GETPROPERTY_InvertedAppearance(){ if (!properties.contains("InvertedAppearance")) return 0; return properties["InvertedAppearance"]->v_boolean; }

void SETPROPERTY_InvertedControls(t_boolean n){ if (!properties.contains("InvertedControls")) return; properties["InvertedControls"]->v_boolean = n; properties["InvertedControls"]->used = true; bModified = true; }
t_boolean GETPROPERTY_InvertedControls(){ if (!properties.contains("InvertedControls")) return 0; return properties["InvertedControls"]->v_boolean; }

void SETPROPERTY_Tracking(t_boolean n){ if (!properties.contains("Tracking")) return; properties["Tracking"]->v_boolean = n; properties["Tracking"]->used = true; bModified = true; }
t_boolean GETPROPERTY_Tracking(){ if (!properties.contains("Tracking")) return 0; return properties["Tracking"]->v_boolean; }

void SETPROPERTY_TickInterval(t_integer n){ if (!properties.contains("TickInterval")) return; properties["TickInterval"]->v_integer = n; properties["TickInterval"]->used = true; bModified = true; }
t_integer GETPROPERTY_TickInterval(){ if (!properties.contains("TickInterval")) return 0; return properties["TickInterval"]->v_integer; }

void SETPROPERTY_PageStep(t_integer n){ if (!properties.contains("PageStep")) return; properties["PageStep"]->v_integer = n; properties["PageStep"]->used = true; bModified = true; }
t_integer GETPROPERTY_PageStep(){ if (!properties.contains("PageStep")) return 0; return properties["PageStep"]->v_integer; }

void SETPROPERTY_SingleStep(t_integer n){ if (!properties.contains("SingleStep")) return; properties["SingleStep"]->v_integer = n; properties["SingleStep"]->used = true; bModified = true; }
t_integer GETPROPERTY_SingleStep(){ if (!properties.contains("SingleStep")) return 0; return properties["SingleStep"]->v_integer; }


void SETPROPERTY_Description(const QString & n){ if (!properties.contains("Description")) return; properties["Description"]->v_qstring = n; properties["Description"]->used = true; bModified = true; }
QString GETPROPERTY_Description(){ if (!properties.contains("Description")) return 0; return properties["Description"]->v_qstring; }


void SETPROPERTY_MoveOnMouseDrag(t_boolean n){ if (!properties.contains("MoveOnMouseDrag")) return; properties["MoveOnMouseDrag"]->v_boolean = n; properties["MoveOnMouseDrag"]->used = true; bModified = true; }
t_boolean GETPROPERTY_MoveOnMouseDrag(){ if (!properties.contains("MoveOnMouseDrag")) return 0; return properties["MoveOnMouseDrag"]->v_boolean; }

void SETPROPERTY_MouseTracking(t_boolean n){ if (!properties.contains("MouseTracking")) return; properties["MouseTracking"]->v_boolean = n; properties["MouseTracking"]->used = true; bModified = true; }
t_boolean GETPROPERTY_MouseTracking(){ if (!properties.contains("MouseTracking")) return 0; return properties["MouseTracking"]->v_boolean; }

void SETPROPERTY_DrawOnPaint(t_boolean n){ if (!properties.contains("DrawOnPaint")) return; properties["DrawOnPaint"]->v_boolean = n; properties["DrawOnPaint"]->used = true; bModified = true; }
t_boolean GETPROPERTY_DrawOnPaint(){ if (!properties.contains("DrawOnPaint")) return 0; return properties["DrawOnPaint"]->v_boolean; }

void SETPROPERTY_ActionId(const QString & n){ if (!properties.contains("ActionId")) return; properties["ActionId"]->v_qstring = n; properties["ActionId"]->used = true; bModified = true; }
QString GETPROPERTY_ActionId(){ if (!properties.contains("ActionId")) return 0; return properties["ActionId"]->v_qstring; }

void SETPROPERTY_SoundOnEvent(const QString & n){ if (!properties.contains("SoundOnEvent")) return; properties["SoundOnEvent"]->v_qstring = n; properties["SoundOnEvent"]->used = true; bModified = true; }
QString GETPROPERTY_SoundOnEvent(){ if (!properties.contains("SoundOnEvent")) return 0; return properties["SoundOnEvent"]->v_qstring; }

void SETPROPERTY_CursorAnimation(const QString & n){ if (!properties.contains("CursorAnimation")) return; properties["CursorAnimation"]->v_qstring = n; properties["CursorAnimation"]->used = true; bModified = true; }
QString GETPROPERTY_CursorAnimation(){ if (!properties.contains("CursorAnimation")) return 0; return properties["CursorAnimation"]->v_qstring; }




void SETPROPERTY_Brightness(t_integer n){ if (!properties.contains("Brightness")) return; properties["Brightness"]->v_integer = n; properties["Brightness"]->used = true; bModified = true; }
t_integer GETPROPERTY_Brightness(){ if (!properties.contains("Brightness")) return 0; return properties["Brightness"]->v_integer; }

void SETPROPERTY_Contrast(t_integer n){ if (!properties.contains("Contrast")) return; properties["Contrast"]->v_integer = n; properties["Contrast"]->used = true; bModified = true; }
t_integer GETPROPERTY_Contrast(){ if (!properties.contains("Contrast")) return 0; return properties["Contrast"]->v_integer; }

void SETPROPERTY_Hue(t_integer n){ if (!properties.contains("Hue")) return; properties["Hue"]->v_integer = n; properties["Hue"]->used = true; bModified = true; }
t_integer GETPROPERTY_Hue(){ if (!properties.contains("Hue")) return 0; return properties["Hue"]->v_integer; }

void SETPROPERTY_Saturation(t_integer n){ if (!properties.contains("Saturation")) return; properties["Saturation"]->v_integer = n; properties["Saturation"]->used = true; bModified = true; }
t_integer GETPROPERTY_Saturation(){ if (!properties.contains("Saturation")) return 0; return properties["Saturation"]->v_integer; }

void SETPROPERTY_ScaleMode(const QString & n){ if (!properties.contains("ScaleMode")) return; properties["ScaleMode"]->v_qstring = n; properties["ScaleMode"]->used = true; bModified = true; }
QString GETPROPERTY_ScaleMode(){ if (!properties.contains("ScaleMode")) return ""; return properties["ScaleMode"]->v_qstring; }

void SETPROPERTY_AspectRatio(const QString & n){ if (!properties.contains("AspectRatio")) return; properties["AspectRatio"]->v_qstring = n; properties["AspectRatio"]->used = true; bModified = true; }
QString GETPROPERTY_AspectRatio(){ if (!properties.contains("AspectRatio")) return ""; return properties["AspectRatio"]->v_qstring; }

void SETPROPERTY_TransitionTime(t_integer n){ if (!properties.contains("TransitionTime")) return; properties["TransitionTime"]->v_integer = n; properties["TransitionTime"]->used = true; bModified = true; }
t_integer GETPROPERTY_TransitionTime(){ if (!properties.contains("TransitionTime")) return 0; return properties["TransitionTime"]->v_integer; }



void SETPROPERTY_RootIsDecorated(t_boolean n){ if (!properties.contains("RootIsDecorated")) return; properties["RootIsDecorated"]->v_boolean = n; properties["RootIsDecorated"]->used = true; bModified = true; }
t_boolean GETPROPERTY_RootIsDecorated(){ if (!properties.contains("RootIsDecorated")) return false; return properties["RootIsDecorated"]->v_boolean; }


void SETPROPERTY_Muted(t_boolean n){ if (!properties.contains("Muted")) return; properties["Muted"]->v_boolean = n; properties["Muted"]->used = true; bModified = true; }
t_boolean GETPROPERTY_Muted(){ if (!properties.contains("Muted")) return false; return properties["Muted"]->v_boolean; }

void SETPROPERTY_Volume(t_integer n){ if (!properties.contains("Volume")) return; properties["Volume"]->v_integer = n; properties["Volume"]->used = true; bModified = true; }
t_integer GETPROPERTY_Volume(){ if (!properties.contains("Volume")) return 0; return properties["Volume"]->v_integer; }

void SETPROPERTY_PrefinishMark(t_integer n){ if (!properties.contains("PrefinishMark")) return; properties["PrefinishMark"]->v_integer = n; properties["PrefinishMark"]->used = true; bModified = true; }
t_integer GETPROPERTY_PrefinishMark(){ if (!properties.contains("PrefinishMark")) return 0; return properties["PrefinishMark"]->v_integer; }

void SETPROPERTY_Tick(t_integer n){ if (!properties.contains("Tick")) return; properties["Tick"]->v_integer = n; properties["Tick"]->used = true; bModified = true; }
t_integer GETPROPERTY_Tick(){ if (!properties.contains("Tick")) return 0; return properties["Tick"]->v_integer; }


void SETPROPERTY_OnTick(t_boolean n){ if (!properties.contains("OnTick")) return; properties["OnTick"]->v_event = n; properties["OnTick"]->used = true; bModified = true; }
t_boolean GETPROPERTY_OnTick(){ if (!properties.contains("OnTick")) return false; return properties["OnTick"]->v_event; }

void SETPROPERTY_OnStateChanged(t_boolean n){ if (!properties.contains("OnStateChanged")) return; properties["OnStateChanged"]->v_event = n; properties["OnStateChanged"]->used = true; bModified = true; }
t_boolean GETPROPERTY_OnStateChanged(){ if (!properties.contains("OnStateChanged")) return false; return properties["OnStateChanged"]->v_event; }

void SETPROPERTY_OnAboutToFinish(t_boolean n){ if (!properties.contains("OnAboutToFinish")) return; properties["OnAboutToFinish"]->v_event = n; properties["OnAboutToFinish"]->used = true; bModified = true; }
t_boolean GETPROPERTY_OnAboutToFinish(){ if (!properties.contains("OnAboutToFinish")) return false; return properties["OnAboutToFinish"]->v_event; }

void SETPROPERTY_OnFinished(t_boolean n){ if (!properties.contains("OnFinished")) return; properties["OnFinished"]->v_event = n; properties["OnFinished"]->used = true; bModified = true; }
t_boolean GETPROPERTY_OnFinished(){ if (!properties.contains("OnFinished")) return false; return properties["OnFinished"]->v_event; }

void SETPROPERTY_OnMutedChanged(t_boolean n){ if (!properties.contains("OnMutedChanged")) return; properties["OnMutedChanged"]->v_event = n; properties["OnMutedChanged"]->used = true; bModified = true; }
t_boolean GETPROPERTY_OnMutedChanged(){ if (!properties.contains("OnMutedChanged")) return false; return properties["OnMutedChanged"]->v_event; }

void SETPROPERTY_OnVolumeChanged(t_boolean n){ if (!properties.contains("OnVolumeChanged")) return; properties["OnVolumeChanged"]->v_event = n; properties["OnVolumeChanged"]->used = true; bModified = true; }
t_boolean GETPROPERTY_OnVolumeChanged(){ if (!properties.contains("OnVolumeChanged")) return false; return properties["OnVolumeChanged"]->v_event; }

void SETPROPERTY_OnPlayingTitleChanged(t_boolean n){ if (!properties.contains("OnPlayedTitleChanged")) return; properties["OnPlayedTitleChanged"]->v_event = n; properties["OnPlayedTitleChanged"]->used = true; bModified = true; }
t_boolean GETPROPERTY_OnPlayingTitleChanged(){ if (!properties.contains("OnPlayedTitleChanged")) return false; return properties["OnPlayedTitleChanged"]->v_event; }

void SETPROPERTY_OnBufferStatus(t_boolean n){ if (!properties.contains("OnBufferStatus")) return; properties["OnBufferStatus"]->v_event = n; properties["OnBufferStatus"]->used = true; bModified = true; }
t_boolean GETPROPERTY_OnBufferStatus(){ if (!properties.contains("OnBufferStatus")) return false; return properties["OnBufferStatus"]->v_event; }

void SETPROPERTY_OnTotalTimeChanged(t_boolean n){ if (!properties.contains("OnTotalTimeChanged")) return; properties["OnTotalTimeChanged"]->v_event = n; properties["OnTotalTimeChanged"]->used = true; bModified = true; }
t_boolean GETPROPERTY_OnTotalTimeChanged(){ if (!properties.contains("OnTotalTimeChanged")) return false; return properties["OnTotalTimeChanged"]->v_event; }


void SETPROPERTY_PortName(const QString & n){ if (!properties.contains("PortName")) return; properties["PortName"]->v_qstring = n; properties["PortName"]->used = true; bModified = true; }
QString GETPROPERTY_PortName(){ if (!properties.contains("PortName")) return ""; return properties["PortName"]->v_qstring; }

void SETPROPERTY_BaudRate(const QString & n){ if (!properties.contains("BaudRate")) return; properties["BaudRate"]->v_qstring = n; properties["BaudRate"]->used = true; bModified = true; }
QString GETPROPERTY_BaudRate(){ if (!properties.contains("BaudRate")) return ""; return properties["BaudRate"]->v_qstring; }

void SETPROPERTY_DataBits(const QString & n){ if (!properties.contains("DataBits")) return; properties["DataBits"]->v_qstring = n; properties["DataBits"]->used = true; bModified = true; }
QString GETPROPERTY_DataBits(){ if (!properties.contains("DataBits")) return ""; return properties["DataBits"]->v_qstring; }

void SETPROPERTY_FlowControl(const QString & n){ if (!properties.contains("FlowControl")) return; properties["FlowControl"]->v_qstring = n; properties["FlowControl"]->used = true; bModified = true; }
QString GETPROPERTY_FlowControl(){ if (!properties.contains("FlowControl")) return ""; return properties["FlowControl"]->v_qstring; }

void SETPROPERTY_Parity(const QString & n){ if (!properties.contains("Parity")) return; properties["Parity"]->v_qstring = n; properties["Parity"]->used = true; bModified = true; }
QString GETPROPERTY_Parity(){ if (!properties.contains("Parity")) return ""; return properties["Parity"]->v_qstring; }

void SETPROPERTY_StopBits(const QString & n){ if (!properties.contains("StopBits")) return; properties["StopBits"]->v_qstring = n; properties["StopBits"]->used = true; bModified = true; }
QString GETPROPERTY_StopBits(){ if (!properties.contains("StopBits")) return ""; return properties["StopBits"]->v_qstring; }

void SETPROPERTY_TimeOutMillisec(t_integer n){ if (!properties.contains("TimeOutMillisec")) return; properties["TimeOutMillisec"]->v_integer = n; properties["TimeOutMillisec"]->used = true; bModified = true; }
t_integer GETPROPERTY_TimeOutMillisec(){ if (!properties.contains("TimeOutMillisec")) return 0; return properties["TimeOutMillisec"]->v_integer; }

void SETPROPERTY_PollingInterval(t_integer n){ if (!properties.contains("PollingInterval")) return; properties["PollingInterval"]->v_integer = n; properties["PollingInterval"]->used = true; bModified = true; }
t_integer GETPROPERTY_PollingInterval(){ if (!properties.contains("PollingInterval")) return 0; return properties["PollingInterval"]->v_integer; }


void SETPROPERTY_Layout(const QString & n){ if (!properties.contains("Layout")) return; properties["Layout"]->v_qstring = n; properties["Layout"]->used = true; bModified = true; }
QString GETPROPERTY_Layout(){ if (!properties.contains("Layout")) return ""; return properties["Layout"]->v_qstring; }

void SETPROPERTY_CommandColor(const QString & n){ if (!properties.contains("CommandColor")) return; properties["CommandColor"]->v_qstring = n; properties["CommandColor"]->used = true; bModified = true; }
QString GETPROPERTY_CommandColor(){ if (!properties.contains("CommandColor")) return ""; return properties["CommandColor"]->v_qstring; }

void SETPROPERTY_KeywordColor(const QString & n){ if (!properties.contains("KeywordColor")) return; properties["KeywordColor"]->v_qstring = n; properties["KeywordColor"]->used = true; bModified = true; }
QString GETPROPERTY_KeywordColor(){ if (!properties.contains("KeywordColor")) return ""; return properties["KeywordColor"]->v_qstring; }

void SETPROPERTY_CommentColor(const QString & n){ if (!properties.contains("CommentColor")) return; properties["CommentColor"]->v_qstring = n; properties["CommentColor"]->used = true; bModified = true; }
QString GETPROPERTY_CommentColor(){ if (!properties.contains("CommentColor")) return ""; return properties["CommentColor"]->v_qstring; }

void SETPROPERTY_Commands(const QString & n){ if (!properties.contains("Commands")) return; properties["Commands"]->v_qstring = n; properties["Commands"]->used = true; bModified = true; }
QString GETPROPERTY_Commands(){ if (!properties.contains("Commands")) return ""; return properties["Commands"]->v_qstring; }

void SETPROPERTY_Keywords(const QString & n){ if (!properties.contains("Keywords")) return; properties["Keywords"]->v_qstring = n; properties["Keywords"]->used = true; bModified = true; }
QString GETPROPERTY_Keywords(){ if (!properties.contains("Keywords")) return ""; return properties["Keywords"]->v_qstring; }

void SETPROPERTY_Comment1Begin(const QString & n){ if (!properties.contains("Comment1Begin")) return; properties["Comment1Begin"]->v_qstring = n; properties["Comment1Begin"]->used = true; bModified = true; }
QString GETPROPERTY_Comment1Begin(){ if (!properties.contains("Comment1Begin")) return ""; return properties["Comment1Begin"]->v_qstring; }

void SETPROPERTY_Comment1End(const QString & n){ if (!properties.contains("Comment1End")) return; properties["Comment1End"]->v_qstring = n; properties["Comment1End"]->used = true; bModified = true; }
QString GETPROPERTY_Comment1End(){ if (!properties.contains("Comment1End")) return ""; return properties["Comment1End"]->v_qstring; }

void SETPROPERTY_Comment2Begin(const QString & n){ if (!properties.contains("Comment2Begin")) return; properties["Comment2Begin"]->v_qstring = n; properties["Comment2Begin"]->used = true; bModified = true; }
QString GETPROPERTY_Comment2Begin(){ if (!properties.contains("Comment2Begin")) return ""; return properties["Comment2Begin"]->v_qstring; }

/*
void SETPROPERTY_Comment2End(const QString & n){ if (!properties.contains("Comment2End")) return; properties["Comment2End"]->v_qstring = n; properties["Comment2End"]->used = true; }
QString GETPROPERTY_Comment2End(){ if (!properties.contains("Comment2End")) return ""; return properties["Comment2End"]->v_qstring; }
*/


void SETPROPERTY_Dock(const QString & n){ if (!properties.contains("Dock")) return; properties["Dock"]->v_qstring = n; properties["Dock"]->used = true; bModified = true; }
QString GETPROPERTY_Dock(){ if (!properties.contains("Dock")) return ""; return properties["Dock"]->v_qstring; }

void SETPROPERTY_SelectionMode(const QString & n){ if (!properties.contains("SelectionMode")) return; properties["SelectionMode"]->v_qstring = n; properties["SelectionMode"]->used = true; bModified = true; }
QString GETPROPERTY_SelectionMode(){ if (!properties.contains("SelectionMode")) return ""; return properties["SelectionMode"]->v_qstring; }


void SETPROPERTY_AlternatingRowColors(t_boolean n){ if (!properties.contains("AlternatingRowColors")) return; properties["AlternatingRowColors"]->v_boolean = n; properties["AlternatingRowColors"]->used = true; bModified = true; }
t_boolean GETPROPERTY_AlternatingRowColors(){ if (!properties.contains("AlternatingRowColors")) return false; return properties["AlternatingRowColors"]->v_boolean; }

void SETPROPERTY_SQL(const QString & n){ if (!properties.contains("SQL")) return; properties["SQL"]->v_qstring = n; properties["SQL"]->used = true; bModified = true; }
QString GETPROPERTY_SQL(){ if (!properties.contains("SQL")) return ""; return properties["SQL"]->v_qstring; }

void SETPROPERTY_SQLName(const QString & n){ if (!properties.contains("SQLName")) return; properties["SQLName"]->v_qstring = n; properties["SQLName"]->used = true; bModified = true; }
QString GETPROPERTY_SQLName(){ if (!properties.contains("SQLName")) return ""; return properties["SQLName"]->v_qstring; }

void SETPROPERTY_SQLRelation(const QString & n){ if (!properties.contains("SQLRelation")) return; properties["SQLRelation"]->v_qstring = n; properties["SQLRelation"]->used = true; bModified = true; }
QString GETPROPERTY_SQLRelation(){ if (!properties.contains("SQLRelation")) return ""; return properties["SQLRelation"]->v_qstring; }

void SETPROPERTY_SQLInsert(t_boolean n){ if (!properties.contains("SQLInsert")) return; properties["SQLInsert"]->v_boolean = n; properties["SQLInsert"]->used = true; bModified = true; }
t_boolean GETPROPERTY_SQLInsert(){ if (!properties.contains("SQLInsert")) return false; return properties["SQLInsert"]->v_boolean; }

void SETPROPERTY_SQLUpdate(t_boolean n){ if (!properties.contains("SQLUpdate")) return; properties["SQLUpdate"]->v_boolean = n; properties["SQLUpdate"]->used = true; bModified = true; }
t_boolean GETPROPERTY_SQLUpdate(){ if (!properties.contains("SQLUpdate")) return false; return properties["SQLUpdate"]->v_boolean; }

void SETPROPERTY_SQLDelete(t_boolean n){ if (!properties.contains("SQLDelete")) return; properties["SQLDelete"]->v_boolean = n; properties["SQLDelete"]->used = true; bModified = true; }
t_boolean GETPROPERTY_SQLDelete(){ if (!properties.contains("SQLDelete")) return false; return properties["SQLDelete"]->v_boolean; }


void SETPROPERTY_TableViewCaption(const QString & n){ if (!properties.contains("TableViewCaption")) return; properties["TableViewCaption"]->v_qstring = n; properties["TableViewCaption"]->used = true; bModified = true; }
QString GETPROPERTY_TableViewCaption(){ if (!properties.contains("TableViewCaption")) return ""; return properties["TableViewCaption"]->v_qstring; }

void SETPROPERTY_TableViewSort(const QString & n){ if (!properties.contains("TableViewSort")) return; properties["TableViewSort"]->v_qstring = n; properties["TableViewSort"]->used = true; bModified = true; }
QString GETPROPERTY_TableViewSort(){ if (!properties.contains("TableViewSort")) return ""; return properties["TableViewSort"]->v_qstring; }

void SETPROPERTY_TableViewFilter(const QString & n){ if (!properties.contains("TableViewFilter")) return; properties["TableViewFilter"]->v_qstring = n; properties["TableViewFilter"]->used = true; bModified = true; }
QString GETPROPERTY_TableViewFilter(){ if (!properties.contains("TableViewFilter")) return ""; return properties["TableViewFilter"]->v_qstring; }

void SETPROPERTY_TableViewWidth(t_integer n){ if (!properties.contains("TableViewWidth")) return; properties["TableViewWidth"]->v_integer = n; properties["TableViewWidth"]->used = true; bModified = true; }
t_integer GETPROPERTY_TableViewWidth(){ if (!properties.contains("TableViewWidth")) return 0; return properties["TableViewWidth"]->v_integer; }

void SETPROPERTY_TableViewVisible(t_boolean n){ if (!properties.contains("TableViewVisible")) return; properties["TableViewVisible"]->v_boolean = n; properties["TableViewVisible"]->used = true; bModified = true; }
t_boolean GETPROPERTY_TableViewVisible(){ if (!properties.contains("TableViewVisible")) return false; return properties["TableViewVisible"]->v_boolean; }

void SETPROPERTY_TableViewOrder(t_integer n){ if (!properties.contains("TableViewOrder")) return; properties["TableViewOrder"]->v_integer = n; properties["TableViewOrder"]->used = true; bModified = true; }
t_integer GETPROPERTY_TableViewOrder(){ if (!properties.contains("TableViewOrder")) return 0; return properties["TableViewOrder"]->v_integer; }


void SETPROPERTY_LoadedX(t_integer n){ if (!properties.contains("LoadedX")) return; properties["LoadedX"]->v_integer = n; properties["LoadedX"]->used = true; bModified = true; }
t_integer GETPROPERTY_LoadedX(){ if (!properties.contains("LoadedX")) return 0; return properties["LoadedX"]->v_integer; }

void SETPROPERTY_LoadedY(t_integer n){ if (!properties.contains("LoadedY")) return; properties["LoadedY"]->v_integer = n; properties["LoadedY"]->used = true; bModified = true; }
t_integer GETPROPERTY_LoadedY(){ if (!properties.contains("LoadedY")) return 0; return properties["LoadedY"]->v_integer; }

void SETPROPERTY_LoadedWidth(t_integer n){ if (!properties.contains("LoadedWidth")) return; properties["LoadedWidth"]->v_integer = n; properties["LoadedWidth"]->used = true; bModified = true; }
t_integer GETPROPERTY_LoadedWidth(){ if (!properties.contains("LoadedWidth")) return 0; return properties["LoadedWidth"]->v_integer; }

void SETPROPERTY_LoadedHeight(t_integer n){ if (!properties.contains("LoadedHeight")) return; properties["LoadedHeight"]->v_integer = n; properties["LoadedHeight"]->used = true; bModified = true; }
t_integer GETPROPERTY_LoadedHeight(){ if (!properties.contains("LoadedHeight")) return 0; return properties["LoadedHeight"]->v_integer; }

void SETPROPERTY_MultiPage(t_integer n){ if (!properties.contains("MultiPage")) return; properties["MultiPage"]->v_integer = n; properties["MultiPage"]->used = true; bModified = true; }
t_integer GETPROPERTY_MultiPage(){ if (!properties.contains("MultiPage")) return 0; return properties["MultiPage"]->v_integer; }


void SETPROPERTY_DockTitleVisible(t_boolean n){ if (!properties.contains("DockTitleVisible")) return; properties["DockTitleVisible"]->v_boolean = n; properties["DockTitleVisible"]->used = true; bModified = true; }
t_boolean GETPROPERTY_DockTitleVisible(){ if (!properties.contains("DockTitleVisible")) return false; return properties["DockTitleVisible"]->v_boolean; }

void SETPROPERTY_DockOrder(const QString & n){ if (!properties.contains("DockParent")) return; properties["DockParent"]->v_qstring = n; properties["DockParent"]->used = true; bModified = true; }
QString GETPROPERTY_DockOrder(){ if (!properties.contains("DockParent")) return ""; return properties["DockParent"]->v_qstring; }

void SETPROPERTY_DockSplit(const QString & n){ if (!properties.contains("DockSplit")) return; properties["DockSplit"]->v_qstring = n; properties["DockSplit"]->used = true; bModified = true; }
QString GETPROPERTY_DockSplit(){ if (!properties.contains("DockSplit")) return ""; return properties["DockSplit"]->v_qstring; }

void SETPROPERTY_ShowMode(const QString & n){ if (!properties.contains("ShowMode")) return; properties["ShowMode"]->v_qstring = n; properties["ShowMode"]->used = true; bModified = true; }
QString GETPROPERTY_ShowMode(){ if (!properties.contains("ShowMode")) return ""; return properties["ShowMode"]->v_qstring; }

void SETPROPERTY_FormFileName(const QString & n){ if (!properties.contains("FormFileName")) return; properties["FormFileName"]->v_qstring = n; properties["FormFileName"]->used = true; bModified = true; }
QString GETPROPERTY_FormFileName(){ if (!properties.contains("FormFileName")) return ""; return properties["FormFileName"]->v_qstring; }

void SETPROPERTY_FormModified(t_boolean n){ if (!properties.contains("FormModified")) return; properties["FormModified"]->v_boolean = n; properties["FormModified"]->used = true; bModified = true; }
t_boolean GETPROPERTY_FormModified(){ if (!properties.contains("FormModified")) return false; return properties["FormModified"]->v_boolean; }


void SETPROPERTY_FormX(t_integer n){ if (!properties.contains("FormX")) return; properties["FormX"]->v_integer = n; properties["FormX"]->used = true; bModified = true; }
t_integer GETPROPERTY_FormX(){ if (!properties.contains("FormX")) return 0; return properties["FormX"]->v_integer; }

void SETPROPERTY_FormY(t_integer n){ if (!properties.contains("FormY")) return; properties["FormY"]->v_integer = n; properties["FormY"]->used = true; bModified = true; }
t_integer GETPROPERTY_FormY(){ if (!properties.contains("FormY")) return 0; return properties["FormY"]->v_integer; }

void SETPROPERTY_FormWidth(t_integer n){ if (!properties.contains("FormWidth")) return; properties["FormWidth"]->v_integer = n; properties["FormWidth"]->used = true; bModified = true; }
t_integer GETPROPERTY_FormWidth(){ if (!properties.contains("FormWidth")) return 0; return properties["FormWidth"]->v_integer; }

void SETPROPERTY_FormHeight(t_integer n){ if (!properties.contains("FormHeight")) return; properties["FormHeight"]->v_integer = n; properties["FormHeight"]->used = true; bModified = true; }
t_integer GETPROPERTY_FormHeight(){ if (!properties.contains("FormHeight")) return 0; return properties["FormHeight"]->v_integer; }


void SETPROPERTY_DockWidth(t_integer n){ if (!properties.contains("DockWidth")) return; properties["DockWidth"]->v_integer = n; properties["DockWidth"]->used = true; bModified = true; }
t_integer GETPROPERTY_DockWidth(){ if (!properties.contains("DockWidth")) return 0; return properties["DockWidth"]->v_integer; }

void SETPROPERTY_DockHeight(t_integer n){ if (!properties.contains("DockHeight")) return; properties["DockHeight"]->v_integer = n; properties["DockHeight"]->used = true; bModified = true; }
t_integer GETPROPERTY_DockHeight(){ if (!properties.contains("DockHeight")) return 0; return properties["DockHeight"]->v_integer; }


void SETPROPERTY_ScrollX(t_integer n){ if (!properties.contains("ScrollX")) return; properties["ScrollX"]->v_integer = n; properties["ScrollX"]->used = true; bModified = true; }
t_integer GETPROPERTY_ScrollX(){ if (!properties.contains("ScrollX")) return 0; return properties["ScrollX"]->v_integer; }

void SETPROPERTY_ScrollY(t_integer n){ if (!properties.contains("ScrollY")) return; properties["ScrollY"]->v_integer = n; properties["ScrollY"]->used = true; bModified = true; }
t_integer GETPROPERTY_ScrollY(){ if (!properties.contains("ScrollY")) return 0; return properties["ScrollY"]->v_integer; }

void SETPROPERTY_ScrollWidth(t_integer n){ if (!properties.contains("ScrollWidth")) return; properties["ScrollWidth"]->v_integer = n; properties["ScrollWidth"]->used = true; bModified = true; }
t_integer GETPROPERTY_ScrollWidth(){ if (!properties.contains("ScrollWidth")) return 0; return properties["ScrollWidth"]->v_integer; }

void SETPROPERTY_ScrollHeight(t_integer n){ if (!properties.contains("ScrollHeight")) return; properties["ScrollHeight"]->v_integer = n; properties["ScrollHeight"]->used = true; bModified = true; }
t_integer GETPROPERTY_ScrollHeight(){ if (!properties.contains("ScrollHeight")) return 0; return properties["ScrollHeight"]->v_integer; }


void SETPROPERTY_MultiPageHeight(t_integer n){ if (!properties.contains("MultiPageHeight")) return; properties["MultiPageHeight"]->v_integer = n; properties["MultiPageHeight"]->used = true; bModified = true; }
t_integer GETPROPERTY_MultiPageHeight(){ if (!properties.contains("MultiPageHeight")) return 0; return properties["MultiPageHeight"]->v_integer; }

void SETPROPERTY_MultiPageBorderTop(t_integer n){ if (!properties.contains("MultiPageBorderTop")) return; properties["MultiPageBorderTop"]->v_integer = n; properties["MultiPageBorderTop"]->used = true; bModified = true; }
t_integer GETPROPERTY_MultiPageBorderTop(){ if (!properties.contains("MultiPageBorderTop")) return 0; return properties["MultiPageBorderTop"]->v_integer; }

void SETPROPERTY_MultiPageBorderBottom(t_integer n){ if (!properties.contains("MultiPageBorderBottom")) return; properties["MultiPageBorderBottom"]->v_integer = n; properties["MultiPageBorderBottom"]->used = true; bModified = true; }
t_integer GETPROPERTY_MultiPageBorderBottom(){ if (!properties.contains("MultiPageBorderBottom")) return 0; return properties["MultiPageBorderBottom"]->v_integer; }

void SETPROPERTY_MultiPageBorderLeft(t_integer n){ if (!properties.contains("MultiPageBorderLeft")) return; properties["MultiPageBorderLeft"]->v_integer = n; properties["MultiPageBorderLeft"]->used = true; bModified = true; }
t_integer GETPROPERTY_MultiPageBorderLeft(){ if (!properties.contains("MultiPageBorderLeft")) return 0; return properties["MultiPageBorderLeft"]->v_integer; }

void SETPROPERTY_MultiPageBorderRight(t_integer n){ if (!properties.contains("MultiPageBorderRight")) return; properties["MultiPageBorderRight"]->v_integer = n; properties["MultiPageBorderRight"]->used = true; bModified = true; }
t_integer GETPROPERTY_MultiPageBorderRight(){ if (!properties.contains("MultiPageBorderRight")) return 0; return properties["MultiPageBorderRight"]->v_integer; }

void SETPROPERTY_BorderTop(t_integer n){ if (!properties.contains("BorderTop")) return; properties["BorderTop"]->v_integer = n; properties["BorderTop"]->used = true; bModified = true; }
t_integer GETPROPERTY_BorderTop(){ if (!properties.contains("BorderTop")) return 0; return properties["BorderTop"]->v_integer; }

void SETPROPERTY_BorderBottom(t_integer n){ if (!properties.contains("BorderBottom")) return; properties["BorderBottom"]->v_integer = n; properties["BorderBottom"]->used = true; bModified = true; }
t_integer GETPROPERTY_BorderBottom(){ if (!properties.contains("BorderBottom")) return 0; return properties["BorderBottom"]->v_integer; }

void SETPROPERTY_BorderLeft(t_integer n){ if (!properties.contains("BorderLeft")) return; properties["BorderLeft"]->v_integer = n; properties["BorderLeft"]->used = true; bModified = true; }
t_integer GETPROPERTY_BorderLeft(){ if (!properties.contains("BorderLeft")) return 0; return properties["BorderLeft"]->v_integer; }

void SETPROPERTY_BorderRight(t_integer n){ if (!properties.contains("BorderRight")) return; properties["BorderRight"]->v_integer = n; properties["BorderRight"]->used = true; bModified = true; }
t_integer GETPROPERTY_BorderRight(){ if (!properties.contains("BorderRight")) return 0; return properties["BorderRight"]->v_integer; }


void SETPROPERTY_Pages(const QString & n){ if (!properties.contains("Pages")) return; properties["Pages"]->v_qstring = n; properties["Pages"]->used = true; bModified = true; }
QString GETPROPERTY_Pages(){ if (!properties.contains("Pages")) return ""; return properties["Pages"]->v_qstring; }

void SETPROPERTY_ParentForm(const QString & n){ if (!properties.contains("ParentForm")) return; properties["ParentForm"]->v_qstring = n; properties["ParentForm"]->used = true; bModified = true; }
QString GETPROPERTY_ParentForm(){ if (!properties.contains("ParentForm")) return ""; return properties["ParentForm"]->v_qstring; }

void SETPROPERTY_ParentControl(const QString & n){ if (!properties.contains("ParentControl")) return; properties["ParentControl"]->v_qstring = n; properties["ParentControl"]->used = true; bModified = true; }
QString GETPROPERTY_ParentControl(){ if (!properties.contains("ParentControl")) return ""; return properties["ParentControl"]->v_qstring; }

void SETPROPERTY_TabIndex(t_integer n){ if (!properties.contains("TabIndex")) return; properties["TabIndex"]->v_integer = n; properties["TabIndex"]->used = true; bModified = true; }
t_integer GETPROPERTY_TabIndex(){ if (!properties.contains("TabIndex")) return 0; return properties["TabIndex"]->v_integer; }

void SETPROPERTY_ParentIndex(t_integer n){ if (!properties.contains("ParentIndex")) return; properties["ParentIndex"]->v_integer = n; properties["ParentIndex"]->used = true; bModified = true; }
t_integer GETPROPERTY_ParentIndex(){ if (!properties.contains("ParentIndex")) return 0; return properties["ParentIndex"]->v_integer; }


void SETPROPERTY_CheckEnterImage(const QString & n){ if (!properties.contains("CheckEnterImage")) return; properties["CheckEnterImage"]->v_qstring = n; properties["CheckEnterImage"]->used = true; bModified = true; }
QString GETPROPERTY_CheckEnterImage(){ if (!properties.contains("CheckEnterImage")) return ""; return properties["CheckEnterImage"]->v_qstring; }

void SETPROPERTY_CheckExitImage(const QString & n){ if (!properties.contains("CheckExitImage")) return; properties["CheckExitImage"]->v_qstring = n; properties["CheckExitImage"]->used = true; bModified = true; }
QString GETPROPERTY_CheckExitImage(){ if (!properties.contains("CheckExitImage")) return ""; return properties["CheckExitImage"]->v_qstring; }

void SETPROPERTY_CheckDisabledImage(const QString & n){ if (!properties.contains("CheckDisabledImage")) return; properties["CheckDisabledImage"]->v_qstring = n; properties["CheckDisabledImage"]->used = true; bModified = true; }
QString GETPROPERTY_CheckDisabledImage(){ if (!properties.contains("CheckDisabledImage")) return ""; return properties["CheckDisabledImage"]->v_qstring; }


void SETPROPERTY_EnterImage(const QString & n){ if (!properties.contains("EnterImage")) return; properties["EnterImage"]->v_qstring = n; properties["EnterImage"]->used = true; bModified = true; }
QString GETPROPERTY_EnterImage(){ if (!properties.contains("EnterImage")) return ""; return properties["EnterImage"]->v_qstring; }

void SETPROPERTY_ExitImage(const QString & n){ if (!properties.contains("ExitImage")) return; properties["ExitImage"]->v_qstring = n; properties["ExitImage"]->used = true; bModified = true; }
QString GETPROPERTY_ExitImage(){ if (!properties.contains("ExitImage")) return ""; return properties["ExitImage"]->v_qstring; }

void SETPROPERTY_DisabledImage(const QString & n){ if (!properties.contains("DisabledImage")) return; properties["DisabledImage"]->v_qstring = n; properties["DisabledImage"]->used = true; bModified = true; }
QString GETPROPERTY_DisabledImage(){ if (!properties.contains("DisabledImage")) return ""; return properties["DisabledImage"]->v_qstring; }

void SETPROPERTY_EnterSound(const QString & n){ if (!properties.contains("EnterSound")) return; properties["EnterSound"]->v_qstring = n; properties["EnterSound"]->used = true; bModified = true; }
QString GETPROPERTY_EnterSound(){ if (!properties.contains("EnterSound")) return ""; return properties["EnterSound"]->v_qstring; }

void SETPROPERTY_ExitSound(const QString & n){ if (!properties.contains("ExitSound")) return; properties["ExitSound"]->v_qstring = n; properties["ExitSound"]->used = true; bModified = true; }
QString GETPROPERTY_ExitSound(){ if (!properties.contains("ExitSound")) return ""; return properties["ExitSound"]->v_qstring; }

void SETPROPERTY_Menu(t_boolean n){ if (!properties.contains("Menu")) return; properties["Menu"]->v_boolean = n; properties["Menu"]->used = true; bModified = true; }
t_boolean GETPROPERTY_Menu(){ if (!properties.contains("Menu")) return false; return properties["Menu"]->v_boolean; }

void SETPROPERTY_Interval(t_integer n){ if (!properties.contains("Interval")) return; properties["Interval"]->v_integer = n; properties["Interval"]->used = true; bModified = true; }
t_integer GETPROPERTY_Interval(){ if (!properties.contains("Interval")) return 0; return properties["Interval"]->v_integer; }


void SETPROPERTY_OpenAtStartup(t_boolean n){ if (!properties.contains("OpenOnRun")) return; properties["OpenOnRun"]->v_boolean = n; properties["OpenOnRun"]->used = true; bModified = true; }
t_boolean GETPROPERTY_OpenAtStartup(){ if (!properties.contains("OpenOnRun")) return false; return properties["OpenOnRun"]->v_boolean; }

void SETPROPERTY_AcceptRichText(t_boolean n){ if (!properties.contains("AcceptRichText")) return; properties["AcceptRichText"]->v_boolean = n; properties["AcceptRichText"]->used = true; bModified = true; }
t_boolean GETPROPERTY_AcceptRichText(){ if (!properties.contains("AcceptRichText")) return false; return properties["AcceptRichText"]->v_boolean; }

void SETPROPERTY_AutoDefault(t_boolean n){ if (!properties.contains("AutoDefault")) return; properties["AutoDefault"]->v_boolean = n; properties["AutoDefault"]->used = true; bModified = true; }
t_boolean GETPROPERTY_AutoDefault(){ if (!properties.contains("AutoDefault")) return false; return properties["AutoDefault"]->v_boolean; }

void SETPROPERTY_EventOnOpen(t_boolean n){ if (!properties.contains("EventOnOpen")) return; properties["EventOnOpen"]->v_boolean = n; properties["EventOnOpen"]->used = true; bModified = true; }
t_boolean GETPROPERTY_EventOnOpen(){ if (!properties.contains("EventOnOpen")) return false; return properties["EventOnOpen"]->v_boolean; }


void SETPROPERTY_Default(t_boolean n){ if (!properties.contains("Default")) return; properties["Default"]->v_boolean = n; properties["Default"]->used = true; bModified = true; }
t_boolean GETPROPERTY_Default(){ if (!properties.contains("Default")) return false; return properties["Default"]->v_boolean; }

void SETPROPERTY_Checkable(t_boolean n){ if (!properties.contains("Checkable")) return; properties["Checkable"]->v_boolean = n; properties["Checkable"]->used = true; bModified = true; }
t_boolean GETPROPERTY_Checkable(){ if (!properties.contains("Checkable")) return false; return properties["Checkable"]->v_boolean; }



void SETPROPERTY_StringValue(const QString & n)
{ 
  if (!properties.contains("OldStringValue")) return; 
  if (!properties.contains("StringValue")) return; 

  properties["OldStringValue"]->v_qstring = properties["StringValue"]->v_qstring; 

  properties["StringValue"]->v_qstring = n; 
  properties["StringValue"]->used = true; 
 bModified = true; 
}

QString GETPROPERTY_StringValue(){ if (!properties.contains("StringValue")) return ""; return properties["StringValue"]->v_qstring; }

QString GETPROPERTY_OldStringValue(){ if (!properties.contains("OldStringValue")) return ""; return properties["OldStringValue"]->v_qstring; }
t_integer GETPROPERTY_OldIntegerValue(){ if (!properties.contains("OldIntegerValue")) return 0; return properties["OldIntegerValue"]->v_integer; }

void SETPROPERTY_InputMask(const QString & n){ if (!properties.contains("InputMask")) return; properties["InputMask"]->v_qstring = n; properties["InputMask"]->used = true; bModified = true; }
QString GETPROPERTY_InputMask(){ if (!properties.contains("InputMask")) return ""; return properties["InputMask"]->v_qstring; }

void SETPROPERTY_Mask(const QString & n){ if (!properties.contains("Mask")) return; properties["Mask"]->v_qstring = n; properties["Mask"]->used = true; bModified = true; }
QString GETPROPERTY_Mask(){ if (!properties.contains("Mask")) return ""; return properties["Mask"]->v_qstring; }

void SETPROPERTY_BooleanValue(t_boolean n)
{ 
  if (!properties.contains("OldBooleanValue")) return; 
  if (!properties.contains("BooleanValue")) return; 

  properties["OldBooleanValue"]->v_boolean = properties["BooleanValue"]->v_boolean; 

  properties["BooleanValue"]->v_boolean = n; 
  properties["BooleanValue"]->used = true; 
 bModified = true; 
}
t_boolean GETPROPERTY_BooleanValue(){ if (!properties.contains("BooleanValue")) return false; return properties["BooleanValue"]->v_boolean; }

t_boolean GETPROPERTY_OldBooleanValue(){ if (!properties.contains("OldBooleanValue")) return false; return properties["OldBooleanValue"]->v_boolean; }


void SETPROPERTY_Group(const QString & n){ if (!properties.contains("Group")) return; properties["Group"]->v_qstring = n; properties["Group"]->used = true; bModified = true; }
QString GETPROPERTY_Group(){ if (!properties.contains("Group")) return ""; return properties["Group"]->v_qstring; }

void SETPROPERTY_Background(const QString & n){ if (!properties.contains("Background")) return; properties["Background"]->v_qstring = n; properties["Background"]->used = true; bModified = true; }
QString GETPROPERTY_Background(){ if (!properties.contains("Background")) return ""; return properties["Background"]->v_qstring; }

void SETPROPERTY_BackgroundStyle(const QString & n){ if (!properties.contains("BackgroundStyle")) return; properties["BackgroundStyle"]->v_qstring = n; properties["BackgroundStyle"]->used = true; bModified = true; }
QString GETPROPERTY_BackgroundStyle(){ if (!properties.contains("BackgroundStyle")) return ""; return properties["BackgroundStyle"]->v_qstring; }

void SETPROPERTY_Palette(const QString & n){ if (!properties.contains("Palette")) return; properties["Palette"]->v_qstring = n; properties["Palette"]->used = true; bModified = true; }
QString GETPROPERTY_Palette(){ if (!properties.contains("Palette")) return ""; return properties["Palette"]->v_qstring; }

void SETPROPERTY_MinimumWidth(t_integer n){ if (!properties.contains("MinimumWidth")) return; properties["MinimumWidth"]->v_integer = n; properties["MinimumWidth"]->used = true; bModified = true; }
t_integer GETPROPERTY_MinimumWidth(){ if (!properties.contains("MinimumWidth")) return 0; return properties["MinimumWidth"]->v_integer; }

void SETPROPERTY_MinimumHeight(t_integer n){ if (!properties.contains("MinimumHeight")) return; properties["MinimumHeight"]->v_integer = n; properties["MinimumHeight"]->used = true; bModified = true; }
t_integer GETPROPERTY_MinimumHeight(){ if (!properties.contains("MinimumHeight")) return 0; return properties["MinimumHeight"]->v_integer; }

void SETPROPERTY_MaximumWidth(t_integer n){ if (!properties.contains("MaximumWidth")) return; properties["MaximumWidth"]->v_integer = n; properties["MaximumWidth"]->used = true; bModified = true; }
t_integer GETPROPERTY_MaximumWidth(){ if (!properties.contains("MaximumWidth")) return 0; return properties["MaximumWidth"]->v_integer; }

void SETPROPERTY_MaximumHeight(t_integer n){ if (!properties.contains("MaximumHeight")) return; properties["MaximumHeight"]->v_integer = n; properties["MaximumHeight"]->used = true; bModified = true; }
t_integer GETPROPERTY_MaximumHeight(){ if (!properties.contains("MaximumHeight")) return 0; return properties["MaximumHeight"]->v_integer; }

void SETPROPERTY_CSV(const QString & n){ if (!properties.contains("CSV")) return; properties["CSV"]->v_qstring = n; properties["CSV"]->used = true; bModified = true; }
QString GETPROPERTY_CSV(){ if (!properties.contains("CSV")) return ""; return properties["CSV"]->v_qstring; }

void SETPROPERTY_TableView(t_boolean n){ if (!properties.contains("TableView")) return; properties["TableView"]->v_boolean = n; properties["TableView"]->used = true; bModified = true; }
t_boolean GETPROPERTY_TableView(){ if (!properties.contains("TableView")) return false; return properties["TableView"]->v_boolean; }

void SETPROPERTY_BoxIndex(t_integer n){ if (!properties.contains("BoxIndex")) return; properties["BoxIndex"]->v_integer = n; properties["BoxIndex"]->used = true; bModified = true; }
t_integer GETPROPERTY_BoxIndex(){ if (!properties.contains("BoxIndex")) return 0; return properties["BoxIndex"]->v_integer; }

void SETPROPERTY_BoxX(t_integer n){ if (!properties.contains("BoxX")) return; properties["BoxX"]->v_integer = n; properties["BoxX"]->used = true; bModified = true; }
t_integer GETPROPERTY_BoxX(){ if (!properties.contains("BoxX")) return 0; return properties["BoxX"]->v_integer; }

void SETPROPERTY_BoxY(t_integer n){ if (!properties.contains("BoxY")) return; properties["BoxY"]->v_integer = n; properties["BoxY"]->used = true; bModified = true; }
t_integer GETPROPERTY_BoxY(){ if (!properties.contains("BoxY")) return 0; return properties["BoxY"]->v_integer; }

void SETPROPERTY_SplitIndex(t_integer n){ if (!properties.contains("SplitIndex")) return; properties["SplitIndex"]->v_integer = n; properties["SplitIndex"]->used = true; bModified = true; }
t_integer GETPROPERTY_SplitIndex(){ if (!properties.contains("SplitIndex")) return 0; return properties["SplitIndex"]->v_integer; }

void SETPROPERTY_StopOnClose(t_boolean n){ if (!properties.contains("StopOnClose")) return; properties["StopOnClose"]->v_boolean = n; properties["StopOnClose"]->used = true; bModified = true; }
t_boolean GETPROPERTY_StopOnClose(){ if (!properties.contains("StopOnClose")) return false; return properties["StopOnClose"]->v_boolean; }

void SETPROPERTY_Scale(t_boolean n){ if (!properties.contains("Scale")) return; properties["Scale"]->v_boolean = n; properties["Scale"]->used = true; bModified = true; }
t_boolean GETPROPERTY_Scale(){ if (!properties.contains("Scale")) return false; return properties["Scale"]->v_boolean; }
/*
void SETPROPERTY_FormCentered(t_boolean n){ if (!properties.contains("FormCentered")) return; properties["FormCentered"]->v_boolean = n; properties["FormCentered"]->used = true; }
t_boolean GETPROPERTY_FormCentered(){ if (!properties.contains("FormCentered")) return false; return properties["FormCentered"]->v_boolean; }

void SETPROPERTY_FormScaled(t_boolean n){ if (!properties.contains("FormScaled")) return; properties["FormScaled"]->v_boolean = n; properties["FormScaled"]->used = true; }
t_boolean GETPROPERTY_FormScaled(){ if (!properties.contains("FormScaled")) return false; return properties["FormScaled"]->v_boolean; }
*/
void SETPROPERTY_DragDrop(t_boolean n){ if (!properties.contains("DragDrop")) return; properties["DragDrop"]->v_boolean = n; properties["DragDrop"]->used = true; bModified = true; }
t_boolean GETPROPERTY_DragDrop(){ if (!properties.contains("DragDrop")) return false; return properties["DragDrop"]->v_boolean; }

void SETPROPERTY_Focus(t_boolean n){ if (!properties.contains("Focus")) return; properties["Focus"]->v_boolean = n; properties["Focus"]->used = true; bModified = true; }
t_boolean GETPROPERTY_Focus(){ if (!properties.contains("Focus")) return false; return properties["Focus"]->v_boolean; }

void SETPROPERTY_FocusPolicy(const QString & n){ if (!properties.contains("FocusPolicy")) return; properties["FocusPolicy"]->v_qstring = n; properties["FocusPolicy"]->used = true; bModified = true; }
QString GETPROPERTY_FocusPolicy(){ if (!properties.contains("FocusPolicy")) return ""; return properties["FocusPolicy"]->v_qstring; }

void SETPROPERTY_FocusProxy(const QString & n){ if (!properties.contains("FocusProxy")) return; properties["FocusProxy"]->v_qstring = n; properties["FocusProxy"]->used = true; bModified = true; }
QString GETPROPERTY_FocusProxy(){ if (!properties.contains("FocusProxy")) return ""; return properties["FocusProxy"]->v_qstring; }

void SETPROPERTY_FocusOrder(t_integer n){ if (!properties.contains("FocusOrder")) return; properties["FocusOrder"]->v_integer = n; properties["FocusOrder"]->used = true; bModified = true; }
t_integer GETPROPERTY_FocusOrder(){ if (!properties.contains("FocusOrder")) return 0; return properties["FocusOrder"]->v_integer; }

void SETPROPERTY_FontName(const QString & n){ if (!properties.contains("FontName")) return; properties["FontName"]->v_qstring = n; properties["FontName"]->used = true; bModified = true; }
QString GETPROPERTY_FontName(){ if (!properties.contains("FontName")) return ""; return properties["FontName"]->v_qstring; }

void SETPROPERTY_FontSize(t_integer n){ if (!properties.contains("FontSize")) return; properties["FontSize"]->v_integer = n; properties["FontSize"]->used = true; bModified = true; }
t_integer GETPROPERTY_FontSize(){ if (!properties.contains("FontSize")) return 0; return properties["FontSize"]->v_integer; }

void SETPROPERTY_FontBold(t_boolean n){ if (!properties.contains("FontBold")) return; properties["FontBold"]->v_boolean = n; properties["FontBold"]->used = true; bModified = true; }
t_boolean GETPROPERTY_FontBold(){ if (!properties.contains("FontBold")) return false; return properties["FontBold"]->v_boolean; }

void SETPROPERTY_FontItalic(t_boolean n){ if (!properties.contains("FontItalic")) return; properties["FontItalic"]->v_boolean = n; properties["FontItalic"]->used = true; bModified = true; }
t_boolean GETPROPERTY_FontItalic(){ if (!properties.contains("FontItalic")) return false; return properties["FontItalic"]->v_boolean; }

void SETPROPERTY_FontUnderline(t_boolean n){ if (!properties.contains("FontUnderline")) return; properties["FontUnderline"]->v_boolean = n; properties["FontUnderline"]->used = true; bModified = true; }
t_boolean GETPROPERTY_FontUnderline(){ if (!properties.contains("FontUnderline")) return false; return properties["FontUnderline"]->v_boolean; }

void SETPROPERTY_FontColor(const QString & n){ if (!properties.contains("FontColor")) return; properties["FontColor"]->v_qstring = n; properties["FontColor"]->used = true; bModified = true; }
QString GETPROPERTY_FontColor(){ if (!properties.contains("FontColor")) return ""; return properties["FontColor"]->v_qstring; }

void SETPROPERTY_StatusTip(const QString & n){ if (!properties.contains("StatusTip")) return; properties["StatusTip"]->v_qstring = n; properties["StatusTip"]->used = true; bModified = true; }
QString GETPROPERTY_StatusTip(){ if (!properties.contains("StatusTip")) return ""; return properties["StatusTip"]->v_qstring; }

void SETPROPERTY_ToolTip(const QString & n){ if (!properties.contains("ToolTip")) return; properties["ToolTip"]->v_qstring = n; properties["ToolTip"]->used = true; bModified = true; }
QString GETPROPERTY_ToolTip(){ if (!properties.contains("ToolTip")) return ""; return properties["ToolTip"]->v_qstring; }

void SETPROPERTY_StyleSheet(const QString & n){ if (!properties.contains("StyleSheet")) return; properties["StyleSheet"]->v_qstring = n; properties["StyleSheet"]->used = true; bModified = true; }
QString GETPROPERTY_StyleSheet(){ if (!properties.contains("StyleSheet")) return ""; return properties["StyleSheet"]->v_qstring; }

void SETPROPERTY_WhatsThis(const QString & n){ if (!properties.contains("WhatsThis")) return; properties["WhatsThis"]->v_qstring = n; properties["WhatsThis"]->used = true; bModified = true; }
QString GETPROPERTY_WhatsThis(){ if (!properties.contains("WhatsThis")) return ""; return properties["WhatsThis"]->v_qstring; }

void SETPROPERTY_SQLControls(const QString & n){ if (!properties.contains("SQLControls")) return; properties["SQLControls"]->v_qstring = n; properties["SQLControls"]->used = true; bModified = true; }
QString GETPROPERTY_SQLControls(){ if (!properties.contains("SQLControls")) return ""; return properties["SQLControls"]->v_qstring; }

void SETPROPERTY_Flag(const QString & n){ if (!properties.contains("Flag")) return; properties["Flag"]->v_qstring = n; properties["Flag"]->used = true; bModified = true; }
QString GETPROPERTY_Flag(){ if (!properties.contains("Flag")) return ""; return properties["Flag"]->v_qstring; }

//void SETPROPERTY_IconCaption(const QString & n){ if (!properties.contains("IconCaption")) return; properties["IconCaption"]->v_qstring = n; properties["IconCaption"]->used = true; bModified = true; }
//QString GETPROPERTY_IconCaption(){ if (!properties.contains("IconCaption")) return ""; return properties["IconCaption"]->v_qstring; }

void SETPROPERTY_Modal(t_boolean n){ if (!properties.contains("Modal")) return; properties["Modal"]->v_boolean = n; properties["Modal"]->used = true; bModified = true; }
t_boolean GETPROPERTY_Modal(){ if (!properties.contains("Modal")) return false; return properties["Modal"]->v_boolean; }

void SETPROPERTY_Opacity(t_integer n){ if (!properties.contains("Opacity")) return; properties["Opacity"]->v_integer = n; properties["Opacity"]->used = true; bModified = true; }
t_integer GETPROPERTY_Opacity(){ if (!properties.contains("Opacity")) return 0; return properties["Opacity"]->v_integer; }

void SETPROPERTY_TimerInterval(t_integer n){ if (!properties.contains("TimerInterval")) return; properties["TimerInterval"]->v_integer = n; properties["TimerInterval"]->used = true; bModified = true; }
t_integer GETPROPERTY_TimerInterval(){ if (!properties.contains("TimerInterval")) return 0; return properties["TimerInterval"]->v_integer; }

void SETPROPERTY_Shadow(t_boolean n){ if (!properties.contains("Shadow")) return; properties["Shadow"]->v_boolean = n; properties["Shadow"]->used = true; bModified = true; }
t_boolean GETPROPERTY_Shadow(){ if (!properties.contains("Shadow")) return false; return properties["Shadow"]->v_boolean; }

void SETPROPERTY_Shape(t_boolean n){ if (!properties.contains("Shape")) return; properties["Shape"]->v_boolean = n; properties["Shape"]->used = true; bModified = true; }
t_boolean GETPROPERTY_Shape(){ if (!properties.contains("Shape")) return false; return properties["Shape"]->v_boolean; }

void SETPROPERTY_OpenLinks(t_boolean n){ if (!properties.contains("OpenLinks")) return; properties["OpenLinks"]->v_boolean = n; properties["OpenLinks"]->used = true; bModified = true; }
t_boolean GETPROPERTY_OpenLinks(){ if (!properties.contains("OpenLinks")) return false; return properties["OpenLinks"]->v_boolean; }

void SETPROPERTY_Icon(const QString & n){ if (!properties.contains("Icon")) return; properties["Icon"]->v_qstring = n; properties["Icon"]->used = true; bModified = true; }
QString GETPROPERTY_Icon(){ if (!properties.contains("Icon")) return ""; return properties["Icon"]->v_qstring; }

void SETPROPERTY_InputControl(const QString & n){ if (!properties.contains("InputControl")) return; properties["InputControl"]->v_qstring = n; properties["InputControl"]->used = true; bModified = true; }
QString GETPROPERTY_InputControl(){ if (!properties.contains("InputControl")) return ""; return properties["InputControl"]->v_qstring; }

void SETPROPERTY_Space(t_integer n){ if (!properties.contains("Space")) return; properties["Space"]->v_integer = n; properties["Space"]->used = true; bModified = true; }
t_integer GETPROPERTY_Space(){ if (!properties.contains("Space")) return 0; return properties["Space"]->v_integer; }

void SETPROPERTY_Border(t_integer n){ if (!properties.contains("Border")) return; properties["Border"]->v_integer = n; properties["Border"]->used = true; bModified = true; }
t_integer GETPROPERTY_Border(){ if (!properties.contains("Border")) return 0; return properties["Border"]->v_integer; }

void SETPROPERTY_Flat(t_boolean n){ if (!properties.contains("Flat")) return; properties["Flat"]->v_boolean = n; properties["Flat"]->used = true; bModified = true; }
t_boolean GETPROPERTY_Flat(){ if (!properties.contains("Flat")) return false; return properties["Flat"]->v_boolean; }

void SETPROPERTY_Key(const QString & n){ if (!properties.contains("Key")) return; properties["Key"]->v_qstring = n; properties["Key"]->used = true; bModified = true; }
QString GETPROPERTY_Key(){ if (!properties.contains("Key")) return ""; return properties["Key"]->v_qstring; }

void SETPROPERTY_IntegerMaximum(t_integer n){ if (!properties.contains("IntegerMaximum")) return; properties["IntegerMaximum"]->v_integer = n; properties["IntegerMaximum"]->used = true; bModified = true; }
t_integer GETPROPERTY_IntegerMaximum(){ if (!properties.contains("IntegerMaximum")) return 0; return properties["IntegerMaximum"]->v_integer; }

void SETPROPERTY_IntegerMinimum(t_integer n){ if (!properties.contains("IntegerMinimum")) return; properties["IntegerMinimum"]->v_integer = n; properties["IntegerMinimum"]->used = true; bModified = true; }
t_integer GETPROPERTY_IntegerMinimum(){ if (!properties.contains("IntegerMinimum")) return 0; return properties["IntegerMinimum"]->v_integer; }

void SETPROPERTY_Completer(const QString & n){ if (!properties.contains("Completer")) return; properties["Completer"]->v_qstring = n; properties["Completer"]->used = true; bModified = true; }
QString GETPROPERTY_Completer(){ if (!properties.contains("Completer")) return ""; return properties["Completer"]->v_qstring; }

void SETPROPERTY_ValidatorDouble(t_boolean n){ if (!properties.contains("ValidatorDouble")) return; properties["ValidatorDouble"]->v_boolean = n; properties["ValidatorDouble"]->used = true; bModified = true; }
t_boolean GETPROPERTY_ValidatorDouble(){ if (!properties.contains("ValidatorDouble")) return false; return properties["ValidatorDouble"]->v_boolean; }

void SETPROPERTY_ValidatorInteger(t_boolean n){ if (!properties.contains("ValidatorInteger")) return; properties["ValidatorInteger"]->v_boolean = n; properties["ValidatorInteger"]->used = true; bModified = true; }
t_boolean GETPROPERTY_ValidatorInteger(){ if (!properties.contains("ValidatorInteger")) return false; return properties["ValidatorInteger"]->v_boolean; }

void SETPROPERTY_ValidatorRegEx(const QString & n){ if (!properties.contains("ValidatorRegEx")) return; properties["ValidatorRegEx"]->v_qstring = n; properties["ValidatorRegEx"]->used = true; bModified = true; }
QString GETPROPERTY_ValidatorRegEx(){ if (!properties.contains("ValidatorRegEx")) return ""; return properties["ValidatorRegEx"]->v_qstring; }

void SETPROPERTY_ValidatorRegEx2(const QString & n){ if (!properties.contains("ValidatorRegEx2")) return; properties["ValidatorRegEx2"]->v_qstring = n; properties["ValidatorRegEx2"]->used = true; bModified = true; }
QString GETPROPERTY_ValidatorRegEx2(){ if (!properties.contains("ValidatorRegEx2")) return ""; return properties["ValidatorRegEx2"]->v_qstring; }

void SETPROPERTY_DoubleEntry(t_boolean n){ if (!properties.contains("DoubleEntry")) return; properties["DoubleEntry"]->v_boolean = n; properties["DoubleEntry"]->used = true; bModified = true; }
t_boolean GETPROPERTY_DoubleEntry(){ if (!properties.contains("DoubleEntry")) return false; return properties["DoubleEntry"]->v_boolean; }

void SETPROPERTY_InsertPolicy(const QString & n){ if (!properties.contains("InsertPolicy")) return; properties["InsertPolicy"]->v_qstring = n; properties["InsertPolicy"]->used = true; bModified = true; }
QString GETPROPERTY_InsertPolicy(){ if (!properties.contains("InsertPolicy")) return ""; return properties["InsertPolicy"]->v_qstring; }

void SETPROPERTY_Editable(t_boolean n){ if (!properties.contains("Editable")) return; properties["Editable"]->v_boolean = n; properties["Editable"]->used = true; bModified = true; }
t_boolean GETPROPERTY_Editable(){ if (!properties.contains("Editable")) return false; return properties["Editable"]->v_boolean; }

void SETPROPERTY_MaximumVisible(t_integer n){ if (!properties.contains("MaximumVisible")) return; properties["MaximumVisible"]->v_integer = n; properties["MaximumVisible"]->used = true; bModified = true; }
t_integer GETPROPERTY_MaximumVisible(){ if (!properties.contains("MaximumVisible")) return 0; return properties["MaximumVisible"]->v_integer; }

void SETPROPERTY_Sorted(t_boolean n){ if (!properties.contains("Sorted")) return; properties["Sorted"]->v_boolean = n; properties["Sorted"]->used = true; bModified = true; }
t_boolean GETPROPERTY_Sorted(){ if (!properties.contains("Sorted")) return false; return properties["Sorted"]->v_boolean; }

void SETPROPERTY_StringMaximum(const QString & n){ if (!properties.contains("StringMaximum")) return; properties["StringMaximum"]->v_qstring = n; properties["StringMaximum"]->used = true; bModified = true; }
QString GETPROPERTY_StringMaximum(){ if (!properties.contains("StringMaximum")) return ""; return properties["StringMaximum"]->v_qstring; }

void SETPROPERTY_StringMinimum(const QString & n){ if (!properties.contains("StringMinimum")) return; properties["StringMinimum"]->v_qstring = n; properties["StringMinimum"]->used = true; bModified = true; }
QString GETPROPERTY_StringMinimum(){ if (!properties.contains("StringMinimum")) return ""; return properties["StringMinimum"]->v_qstring; }

void SETPROPERTY_Format(const QString & n){ if (!properties.contains("Format")) return; properties["Format"]->v_qstring = n; properties["Format"]->used = true; bModified = true; }
QString GETPROPERTY_Format(){ if (!properties.contains("Format")) return ""; return properties["Format"]->v_qstring; }

void SETPROPERTY_PopUp(t_boolean n){ if (!properties.contains("PopUp")) return; properties["PopUp"]->v_boolean = n; properties["PopUp"]->used = true; bModified = true; }
t_boolean GETPROPERTY_PopUp(){ if (!properties.contains("PopUp")) return false; return properties["PopUp"]->v_boolean; }

void SETPROPERTY_ScrollBar(const QString & n){ if (!properties.contains("ScrollBar")) return; properties["ScrollBar"]->v_qstring = n; properties["ScrollBar"]->used = true; bModified = true; }
QString GETPROPERTY_ScrollBar(){ if (!properties.contains("ScrollBar")) return ""; return properties["ScrollBar"]->v_qstring; }

void SETPROPERTY_CheckMouseDownImage(const QString & n){ if (!properties.contains("CheckMouseDownImage")) return; properties["CheckMouseDownImage"]->v_qstring = n; properties["CheckMouseDownImage"]->used = true; bModified = true; }
QString GETPROPERTY_CheckMouseDownImage(){ if (!properties.contains("CheckMouseDownImage")) return ""; return properties["CheckMouseDownImage"]->v_qstring; }

void SETPROPERTY_CheckMouseUpImage(const QString & n){ if (!properties.contains("CheckMouseUpImage")) return; properties["CheckMouseUpImage"]->v_qstring = n; properties["CheckMouseUpImage"]->used = true; bModified = true; }
QString GETPROPERTY_CheckMouseUpImage(){ if (!properties.contains("CheckMouseUpImage")) return ""; return properties["CheckMouseUpImage"]->v_qstring; }

void SETPROPERTY_CheckEnabledImage(const QString & n){ if (!properties.contains("CheckEnabledImage")) return; properties["CheckEnabledImage"]->v_qstring = n; properties["CheckEnabledImage"]->used = true; bModified = true; }
QString GETPROPERTY_CheckEnabledImage(){ if (!properties.contains("CheckEnabledImage")) return ""; return properties["CheckEnabledImage"]->v_qstring; }

void SETPROPERTY_MouseDownImage(const QString & n){ if (!properties.contains("MouseDownImage")) return; properties["MouseDownImage"]->v_qstring = n; properties["MouseDownImage"]->used = true; bModified = true; }
QString GETPROPERTY_MouseDownImage(){ if (!properties.contains("MouseDownImage")) return ""; return properties["MouseDownImage"]->v_qstring; }

void SETPROPERTY_MouseUpImage(const QString & n){ if (!properties.contains("MouseUpImage")) return; properties["MouseUpImage"]->v_qstring = n; properties["MouseUpImage"]->used = true; bModified = true; }
QString GETPROPERTY_MouseUpImage(){ if (!properties.contains("MouseUpImage")) return ""; return properties["MouseUpImage"]->v_qstring; }

void SETPROPERTY_EnabledImage(const QString & n){ if (!properties.contains("EnabledImage")) return; properties["EnabledImage"]->v_qstring = n; properties["EnabledImage"]->used = true; bModified = true; }
QString GETPROPERTY_EnabledImage(){ if (!properties.contains("EnabledImage")) return ""; return properties["EnabledImage"]->v_qstring; }

void SETPROPERTY_MouseDownSound(const QString & n){ if (!properties.contains("MouseDownSound")) return; properties["MouseDownSound"]->v_qstring = n; properties["MouseDownSound"]->used = true; bModified = true; }
QString GETPROPERTY_MouseDownSound(){ if (!properties.contains("MouseDownSound")) return ""; return properties["MouseDownSound"]->v_qstring; }

void SETPROPERTY_MouseUpSound(const QString & n){ if (!properties.contains("MouseUpSound")) return; properties["MouseUpSound"]->v_qstring = n; properties["MouseUpSound"]->used = true; bModified = true; }
QString GETPROPERTY_MouseUpSound(){ if (!properties.contains("MouseUpSound")) return ""; return properties["MouseUpSound"]->v_qstring; }

void SETPROPERTY_HomeURL(const QString & n){ if (!properties.contains("HomeURL")) return; properties["HomeURL"]->v_qstring = n; properties["HomeURL"]->used = true; bModified = true; }
QString GETPROPERTY_HomeURL(){ if (!properties.contains("HomeURL")) return ""; return properties["HomeURL"]->v_qstring; }


// EVENT
   

//void SETPROPERTY_OnCursorPositionChanged(t_boolean n){ if (!properties.contains("OnCursorPositionChanged")) return; properties["OnCursorPositionChanged"]->v_event = n; properties["OnCursorPositionChanged"]->used = true; bModified = true; }
//t_boolean GETPROPERTY_OnCursorPositionChanged(){ if (!properties.contains("OnCursorPositionChanged")) return false; return properties["OnCursorPositionChanged"]->v_event; }

void SETPROPERTY_OnEditingFinished(t_boolean n){ if (!properties.contains("OnEditingFinished")) return; properties["OnEditingFinished"]->v_event = n; properties["OnEditingFinished"]->used = true; bModified = true; }
t_boolean GETPROPERTY_OnEditingFinished(){ if (!properties.contains("OnEditingFinished")) return false; return properties["OnEditingFinished"]->v_event; }

void SETPROPERTY_OnReturnPressed(t_boolean n){ if (!properties.contains("OnReturnPressed")) return; properties["OnReturnPressed"]->v_event = n; properties["OnReturnPressed"]->used = true; bModified = true; }
t_boolean GETPROPERTY_OnReturnPressed(){ if (!properties.contains("OnReturnPressed")) return false; return properties["OnReturnPressed"]->v_event; }

void SETPROPERTY_OnSelectionChanged(t_boolean n){ if (!properties.contains("OnSelectionChanged")) return; properties["OnSelectionChanged"]->v_event = n; properties["OnSelectionChanged"]->used = true; bModified = true; }
t_boolean GETPROPERTY_OnSelectionChanged(){ if (!properties.contains("OnSelectionChanged")) return false; return properties["OnSelectionChanged"]->v_event; }

void SETPROPERTY_OnTextChanged(t_boolean n){ if (!properties.contains("OnTextChanged")) return; properties["OnTextChanged"]->v_event = n; properties["OnTextChanged"]->used = true; bModified = true; }
t_boolean GETPROPERTY_OnTextChanged(){ if (!properties.contains("OnTextChanged")) return false; return properties["OnTextChanged"]->v_event; }

void SETPROPERTY_OnTextEdited(t_boolean n){ if (!properties.contains("OnTextEdited")) return; properties["OnTextEdited"]->v_event = n; properties["OnTextEdited"]->used = true; bModified = true; }
t_boolean GETPROPERTY_OnTextEdited(){ if (!properties.contains("OnTextEdited")) return false; return properties["OnTextEdited"]->v_event; }


void SETPROPERTY_OnPage(t_boolean n){ if (!properties.contains("OnPage")) return; properties["OnPage"]->v_event = n; properties["OnPage"]->used = true; bModified = true; }
t_boolean GETPROPERTY_OnPage(){ if (!properties.contains("OnPage")) return false; return properties["OnPage"]->v_event; }

void SETPROPERTY_OnLinkHovered(t_boolean n){ if (!properties.contains("OnLinkHovered")) return; properties["OnLinkHovered"]->v_event = n; properties["OnLinkHovered"]->used = true; bModified = true; }
t_boolean GETPROPERTY_OnLinkHovered(){ if (!properties.contains("OnLinkHovered")) return false; return properties["OnLinkHovered"]->v_event; }

void SETPROPERTY_OnLoadFinished(t_boolean n){ if (!properties.contains("OnLoadFinished")) return; properties["OnLoadFinished"]->v_event = n; properties["OnLoadFinished"]->used = true; bModified = true; }
t_boolean GETPROPERTY_OnLoadFinished(){ if (!properties.contains("OnLoadFinished")) return false; return properties["OnLoadFinished"]->v_event; }

void SETPROPERTY_OnLoadProgress(t_boolean n){ if (!properties.contains("OnLoadProgress")) return; properties["OnLoadProgress"]->v_event = n; properties["OnLoadProgress"]->used = true; bModified = true; }
t_boolean GETPROPERTY_OnLoadProgress(){ if (!properties.contains("OnLoadProgress")) return false; return properties["OnLoadProgress"]->v_event; }

void SETPROPERTY_OnLoadStarted(t_boolean n){ if (!properties.contains("OnLoadStarted")) return; properties["OnLoadStarted"]->v_event = n; properties["OnLoadStarted"]->used = true; bModified = true; }
t_boolean GETPROPERTY_OnLoadStarted(){ if (!properties.contains("OnLoadStarted")) return false; return properties["OnLoadStarted"]->v_event; }

void SETPROPERTY_OnWindowCloseRequested(t_boolean n){ if (!properties.contains("OnWindowCloseRequested")) return; properties["OnWindowCloseRequested"]->v_event = n; properties["OnWindowCloseRequested"]->used = true; bModified = true; }
t_boolean GETPROPERTY_OnWindowCloseRequested(){ if (!properties.contains("OnWindowCloseRequested")) return false; return properties["OnWindowCloseRequested"]->v_event; }


void SETPROPERTY_OnEvent(t_boolean n){ if (!properties.contains("OnEvent")) return; properties["OnEvent"]->v_event = n; properties["OnEvent"]->used = true; bModified = true; }
t_boolean GETPROPERTY_OnEvent(){ if (!properties.contains("OnEvent")) return false; return properties["OnEvent"]->v_event; }

void SETPROPERTY_OnSingleShot(t_boolean n){ if (!properties.contains("OnSingleShot")) return; properties["OnSingleShot"]->v_event = n; properties["OnSingleShot"]->used = true; bModified = true; }
t_boolean GETPROPERTY_OnSingleShot(){ if (!properties.contains("OnSingleShot")) return false; return properties["OnSingleShot"]->v_event; }

void SETPROPERTY_OnAction(t_boolean n){ if (!properties.contains("OnAction")) return; properties["OnAction"]->v_event = n; properties["OnAction"]->used = true; bModified = true; }
t_boolean GETPROPERTY_OnAction(){ if (!properties.contains("OnAction")) return false; return properties["OnAction"]->v_event; }

void SETPROPERTY_OnCursorPositionChanged(t_boolean n){ if (!properties.contains("OnCursorPositionChanged")) return; properties["OnCursorPositionChanged"]->v_event = n; properties["OnActionOnCursorPositionChanged"]->used = true; bModified = true; }
t_boolean GETPROPERTY_OnCursorPositionChanged(){ if (!properties.contains("OnCursorPositionChanged")) return false; return properties["OnCursorPositionChanged"]->v_event; }

void SETPROPERTY_OnOpen(t_boolean n){ if (!properties.contains("OnOpen")) return; properties["OnOpen"]->v_event = n; properties["OnOpen"]->used = true; bModified = true; }
t_boolean GETPROPERTY_OnOpen(){ if (!properties.contains("OnOpen")) return false; return properties["OnOpen"]->v_event; }

void SETPROPERTY_OnClose(t_boolean n){ if (!properties.contains("OnClose")) return; properties["OnClose"]->v_event = n; properties["OnClose"]->used = true; bModified = true; }
t_boolean GETPROPERTY_OnClose(){ if (!properties.contains("OnClose")) return false; return properties["OnClose"]->v_event; }

void SETPROPERTY_OnGoTo(t_boolean n){ if (!properties.contains("OnGoTo")) return; properties["OnGoTo"]->v_event = n; properties["OnGoTo"]->used = true; bModified = true; }
t_boolean GETPROPERTY_OnGoTo(){ if (!properties.contains("OnGoTo")) return false; return properties["OnGoTo"]->v_event; }

void SETPROPERTY_OnBeforeInsert(t_boolean n){ if (!properties.contains("OnBeforeInsert")) return; properties["OnBeforeInsert"]->v_event = n; properties["OnBeforeInsert"]->used = true; bModified = true; }
t_boolean GETPROPERTY_OnBeforeInsert(){ if (!properties.contains("OnBeforeInsert")) return false; return properties["OnBeforeInsert"]->v_event; }

void SETPROPERTY_OnBeforeDelete(t_boolean n){ if (!properties.contains("OnBeforeDelete")) return; properties["OnBeforeDelete"]->v_event = n; properties["OnBeforeDelete"]->used = true; bModified = true; }
t_boolean GETPROPERTY_OnBeforeDelete(){ if (!properties.contains("OnBeforeDelete")) return false; return properties["OnBeforeDelete"]->v_event; }

void SETPROPERTY_OnDragExit(t_boolean n){ if (!properties.contains("OnDragExit")) return; properties["OnDragExit"]->v_event = n; properties["OnDragExit"]->used = true; bModified = true; }
t_boolean GETPROPERTY_OnDragExit(){ if (!properties.contains("OnDragExit")) return false; return properties["OnDragExit"]->v_event; }

void SETPROPERTY_OnPaint(t_boolean n){ if (!properties.contains("OnPaint")) return; properties["OnPaint"]->v_event = n; properties["OnPaint"]->used = true; bModified = true; }
t_boolean GETPROPERTY_OnPaint(){ if (!properties.contains("OnPaint")) return false; return properties["OnPaint"]->v_event; }

void SETPROPERTY_OnDirty(t_boolean n){ if (!properties.contains("OnDirty")) return; properties["OnDirty"]->v_event = n; properties["OnDirty"]->used = true; bModified = true; }
t_boolean GETPROPERTY_OnDirty(){ if (!properties.contains("OnDirty")) return false; return properties["OnDirty"]->v_event; }

void SETPROPERTY_OnAddNew(t_boolean n){ if (!properties.contains("OnAddNew")) return; properties["OnAddNew"]->v_event = n; properties["OnAddNew"]->used = true; bModified = true; }
t_boolean GETPROPERTY_OnAddNew(){ if (!properties.contains("OnAddNew")) return false; return properties["OnAddNew"]->v_event; }

void SETPROPERTY_OnQuery(t_boolean n){ if (!properties.contains("OnQuery")) return; properties["OnQuery"]->v_event = n; properties["OnQuery"]->used = true; bModified = true; }
t_boolean GETPROPERTY_OnQuery(){ if (!properties.contains("OnQuery")) return false; return properties["OnQuery"]->v_event; }


void SETPROPERTY_OnTimer(t_boolean n){ if (!properties.contains("OnTimer")) return; properties["OnTimer"]->v_event = n; properties["OnTimer"]->used = true; bModified = true; }
t_boolean GETPROPERTY_OnTimer(){ if (!properties.contains("OnTimer")) return false; return properties["OnTimer"]->v_event; }

void SETPROPERTY_OnMove(t_boolean n){ if (!properties.contains("OnMove")) return; properties["OnMove"]->v_event = n; properties["OnMove"]->used = true; bModified = true; }
t_boolean GETPROPERTY_OnMove(){ if (!properties.contains("OnMove")) return false; return properties["OnMove"]->v_event; }

void SETPROPERTY_OnHide(t_boolean n){ if (!properties.contains("OnHide")) return; properties["OnHide"]->v_event = n; properties["OnHide"]->used = true; bModified = true; }
t_boolean GETPROPERTY_OnHide(){ if (!properties.contains("OnHide")) return false; return properties["OnHide"]->v_event; }

void SETPROPERTY_OnShow(t_boolean n){ if (!properties.contains("OnShow")) return; properties["OnShow"]->v_event = n; properties["OnShow"]->used = true; bModified = true; }
t_boolean GETPROPERTY_OnShow(){ if (!properties.contains("OnShow")) return false; return properties["OnShow"]->v_event; }

void SETPROPERTY_OnEnabled(t_boolean n){ if (!properties.contains("OnEnabled")) return; properties["OnEnabled"]->v_event = n; properties["OnEnabled"]->used = true; bModified = true; }
t_boolean GETPROPERTY_OnEnabled(){ if (!properties.contains("OnEnabled")) return false; return properties["OnEnabled"]->v_event; }

void SETPROPERTY_OnDisabled(t_boolean n){ if (!properties.contains("OnDisabled")) return; properties["OnDisabled"]->v_event = n; properties["OnDisabled"]->used = true; bModified = true; }
t_boolean GETPROPERTY_OnDisabled(){ if (!properties.contains("OnDisabled")) return false; return properties["OnDisabled"]->v_event; }

void SETPROPERTY_OnMouseWheel(t_boolean n){ if (!properties.contains("OnMouseWheel")) return; properties["OnMouseWheel"]->v_event = n; properties["OnMouseWheel"]->used = true; bModified = true; }
t_boolean GETPROPERTY_OnMouseWheel(){ if (!properties.contains("OnMouseWheel")) return false; return properties["OnMouseWheel"]->v_event; }

void SETPROPERTY_OnScroll(t_boolean n){ if (!properties.contains("OnScroll")) return; properties["OnScroll"]->v_event = n; properties["OnScroll"]->used = true; bModified = true; }
t_boolean GETPROPERTY_OnScroll(){ if (!properties.contains("OnScroll")) return false; return properties["OnScroll"]->v_event; }

void SETPROPERTY_OnMultiPageShow(t_boolean n){ if (!properties.contains("OnMultiPageShow")) return; properties["OnMultiPageShow"]->v_event = n; properties["OnMultiPageShow"]->used = true; bModified = true; }
t_boolean GETPROPERTY_OnMultiPageShow(){ if (!properties.contains("OnMultiPageShow")) return false; return properties["OnMultiPageShow"]->v_event; }

void SETPROPERTY_OnContextMenu(t_boolean n){ if (!properties.contains("OnContextMenu")) return; properties["OnContextMenu"]->v_event = n; properties["OnContextMenu"]->used = true; bModified = true; }
t_boolean GETPROPERTY_OnContextMenu(){ if (!properties.contains("OnContextMenu")) return false; return properties["OnContextMenu"]->v_event; }

void SETPROPERTY_OnDrop(t_boolean n){ if (!properties.contains("OnDrop")) return; properties["OnDrop"]->v_event = n; properties["OnDrop"]->used = true; bModified = true; }
t_boolean GETPROPERTY_OnDrop(){ if (!properties.contains("OnDrop")) return false; return properties["OnDrop"]->v_event; }

void SETPROPERTY_OnDragMove(t_boolean n){ if (!properties.contains("OnDragMove")) return; properties["OnDragMove"]->v_event = n; properties["OnDragMove"]->used = true; bModified = true; }
t_boolean GETPROPERTY_OnDragMove(){ if (!properties.contains("OnDragMove")) return false; return properties["OnDragMove"]->v_event; }

void SETPROPERTY_OnDragEnter(t_boolean n){ if (!properties.contains("OnDragEnter")) return; properties["OnDragEnter"]->v_event = n; properties["OnDragEnter"]->used = true; bModified = true; }
t_boolean GETPROPERTY_OnDragEnter(){ if (!properties.contains("OnDragEnter")) return false; return properties["OnDragEnter"]->v_event; }

void SETPROPERTY_OnClick(t_boolean n){ if (!properties.contains("OnClick")) return; properties["OnClick"]->v_event = n; properties["OnClick"]->used = true; bModified = true; }
t_boolean GETPROPERTY_OnClick(){ if (!properties.contains("OnClick")) return false; return properties["OnClick"]->v_event; }

void SETPROPERTY_OnDblClick(t_boolean n){ if (!properties.contains("OnDblClick")) return; properties["OnDblClick"]->v_event = n; properties["OnDblClick"]->used = true; bModified = true; }
t_boolean GETPROPERTY_OnDblClick(){ if (!properties.contains("OnDblClick")) return false; return properties["OnDblClick"]->v_event; }

void SETPROPERTY_OnMouseDown(t_boolean n){ if (!properties.contains("OnMouseDown")) return; properties["OnMouseDown"]->v_event = n; properties["OnMouseDown"]->used = true; bModified = true; }
t_boolean GETPROPERTY_OnMouseDown(){ if (!properties.contains("OnMouseDown")) return false; return properties["OnMouseDown"]->v_event; }

void SETPROPERTY_OnMouseUp(t_boolean n){ if (!properties.contains("OnMouseUp")) return; properties["OnMouseUp"]->v_event = n; properties["OnMouseUp"]->used = true; bModified = true; }
t_boolean GETPROPERTY_OnMouseUp(){ if (!properties.contains("OnMouseUp")) return false; return properties["OnMouseUp"]->v_event; }

void SETPROPERTY_OnMouseMove(t_boolean n){ if (!properties.contains("OnMouseMove")) return; properties["OnMouseMove"]->v_event = n; properties["OnMouseMove"]->used = true; bModified = true; }
t_boolean GETPROPERTY_OnMouseMove(){ if (!properties.contains("OnMouseMove")) return false; return properties["OnMouseMove"]->v_event; }

void SETPROPERTY_OnGotFocus(t_boolean n){ if (!properties.contains("OnGotFocus")) return; properties["OnGotFocus"]->v_event = n; properties["OnGotFocus"]->used = true; bModified = true; }
t_boolean GETPROPERTY_OnGotFocus(){ if (!properties.contains("OnGotFocus")) return false; return properties["OnGotFocus"]->v_event; }

void SETPROPERTY_OnLostFocus(t_boolean n){ if (!properties.contains("OnLostFocus")) return; properties["OnLostFocus"]->v_event = n; properties["OnLostFocus"]->used = true; bModified = true; }
t_boolean GETPROPERTY_OnLostFocus(){ if (!properties.contains("OnLostFocus")) return false; return properties["OnLostFocus"]->v_event; }

void SETPROPERTY_OnEnter(t_boolean n){ if (!properties.contains("OnEnter")) return; properties["OnEnter"]->v_event = n; properties["OnEnter"]->used = true; bModified = true; }
t_boolean GETPROPERTY_OnEnter(){ if (!properties.contains("OnEnter")) return false; return properties["OnEnter"]->v_event; }

void SETPROPERTY_OnExit(t_boolean n){ if (!properties.contains("OnExit")) return; properties["OnExit"]->v_event = n; properties["OnExit"]->used = true; bModified = true; }
t_boolean GETPROPERTY_OnExit(){ if (!properties.contains("OnExit")) return false; return properties["OnExit"]->v_event; }

void SETPROPERTY_OnKeyDown(t_boolean n){ if (!properties.contains("OnKeyDown")) return; properties["OnKeyDown"]->v_event = n; properties["OnKeyDown"]->used = true; bModified = true; }
t_boolean GETPROPERTY_OnKeyDown(){ if (!properties.contains("OnKeyDown")) return false; return properties["OnKeyDown"]->v_event; }

void SETPROPERTY_OnKeyUp(t_boolean n){ if (!properties.contains("OnKeyUp")) return; properties["OnKeyUp"]->v_event = n; properties["OnKeyUp"]->used = true; bModified = true; }
t_boolean GETPROPERTY_OnKeyUp(){ if (!properties.contains("OnKeyUp")) return false; return properties["OnKeyUp"]->v_event; }

void SETPROPERTY_OnKeyPress(t_boolean n){ if (!properties.contains("OnKeyPress")) return; properties["OnKeyPress"]->v_event = n; properties["OnKeyPress"]->used = true; bModified = true; }
t_boolean GETPROPERTY_OnKeyPress(){ if (!properties.contains("OnKeyPress")) return false; return properties["OnKeyPress"]->v_event; }

void SETPROPERTY_OnBeforeUpdate(t_boolean n){ if (!properties.contains("OnBeforeUpdate")) return; properties["OnBeforeUpdate"]->v_event = n; properties["OnBeforeUpdate"]->used = true; bModified = true; }
t_boolean GETPROPERTY_OnBeforeUpdate(){ if (!properties.contains("OnBeforeUpdate")) return false; return properties["OnBeforeUpdate"]->v_event; }

void SETPROPERTY_OnResize(t_boolean n){ if (!properties.contains("OnResize")) return; properties["OnResize"]->v_event = n; properties["OnResize"]->used = true; bModified = true; }
t_boolean GETPROPERTY_OnResize(){ if (!properties.contains("OnResize")) return false; return properties["OnResize"]->v_event; }


void SETPROPERTY_OnPrint(t_boolean n){ if (!properties.contains("OnPrint")) return; properties["OnPrint"]->v_qstring = n; properties["OnPrint"]->used = true; bModified = true; }
t_boolean GETPROPERTY_OnPrint(){ if (!properties.contains("OnPrint")) return false; return properties["OnPrint"]->v_boolean; }

void SETPROPERTY_OnCurrentItemChanged(t_boolean n){ if (!properties.contains("OnCurrentItemChanged")) return; properties["OnCurrentItemChanged"]->v_qstring = n; properties["OnCurrentItemChanged"]->used = true; bModified = true; }
t_boolean GETPROPERTY_OnCurrentItemChanged(){ if (!properties.contains("OnCurrentItemChanged")) return false; return properties["OnCurrentItemChanged"]->v_boolean; }

void SETPROPERTY_OnItemActivated(t_boolean n){ if (!properties.contains("OnItemActivated")) return; properties["OnItemActivated"]->v_qstring = n; properties["OnItemActivated"]->used = true; bModified = true; }
t_boolean GETPROPERTY_OnItemActivated(){ if (!properties.contains("OnItemActivated")) return false; return properties["OnItemActivated"]->v_boolean; }

void SETPROPERTY_OnItemChanged(t_boolean n){ if (!properties.contains("OnItemChanged")) return; properties["OnItemChanged"]->v_qstring = n; properties["OnItemChanged"]->used = true; bModified = true; }
t_boolean GETPROPERTY_OnItemChanged(){ if (!properties.contains("OnItemChanged")) return false; return properties["OnItemChanged"]->v_boolean; }

void SETPROPERTY_OnItemClicked(t_boolean n){ if (!properties.contains("OnItemClicked")) return; properties["OnItemClicked"]->v_qstring = n; properties["OnItemClicked"]->used = true; bModified = true; }
t_boolean GETPROPERTY_OnItemClicked(){ if (!properties.contains("OnItemClicked")) return false; return properties["OnItemClicked"]->v_boolean; }

void SETPROPERTY_OnItemCollapsed(t_boolean n){ if (!properties.contains("OnItemCollapsed")) return; properties["OnItemCollapsed"]->v_qstring = n; properties["OnItemCollapsed"]->used = true; bModified = true; }
t_boolean GETPROPERTY_OnItemCollapsed(){ if (!properties.contains("OnItemCollapsed")) return false; return properties["OnItemCollapsed"]->v_boolean; }

void SETPROPERTY_OnItemDoubleClicked(t_boolean n){ if (!properties.contains("OnItemDoubleClicked")) return; properties["OnItemDoubleClicked"]->v_qstring = n; properties["OnItemDoubleClicked"]->used = true; bModified = true; }
t_boolean GETPROPERTY_OnItemDoubleClicked(){ if (!properties.contains("OnItemDoubleClicked")) return false; return properties["OnItemDoubleClicked"]->v_boolean; }

void SETPROPERTY_OnItemEntered(t_boolean n){ if (!properties.contains("OnItemEntered")) return; properties["OnItemEntered"]->v_qstring = n; properties["OnItemEntered"]->used = true; bModified = true; }
t_boolean GETPROPERTY_OnItemEntered(){ if (!properties.contains("OnItemEntered")) return false; return properties["OnItemEntered"]->v_boolean; }

void SETPROPERTY_OnItemExpanded(t_boolean n){ if (!properties.contains("OnItemExpanded")) return; properties["OnItemExpanded"]->v_qstring = n; properties["OnItemExpanded"]->used = true; bModified = true; }
t_boolean GETPROPERTY_OnItemExpanded(){ if (!properties.contains("OnItemExpanded")) return false; return properties["OnItemExpanded"]->v_boolean; }

void SETPROPERTY_OnItemPressed(t_boolean n){ if (!properties.contains("OnItemPressed")) return; properties["OnItemPressed"]->v_qstring = n; properties["OnItemPressed"]->used = true; bModified = true; }
t_boolean GETPROPERTY_OnItemPressed(){ if (!properties.contains("OnItemPressed")) return false; return properties["OnItemPressed"]->v_boolean; }

void SETPROPERTY_OnItemSelectionChanged(t_boolean n){ if (!properties.contains("OnItemSelectionChanged")) return; properties["OnItemSelectionChanged"]->v_qstring = n; properties["OnItemSelectionChanged"]->used = true; bModified = true; }
t_boolean GETPROPERTY_OnItemSelectionChanged(){ if (!properties.contains("OnItemSelectionChanged")) return false; return properties["OnItemSelectionChanged"]->v_boolean; }

void SETPROPERTY_OnDockMove(t_boolean n){ if (!properties.contains("OnDockMove")) return; properties["OnDockMove"]->v_qstring = n; properties["OnDockMove"]->used = true; bModified = true; }
t_boolean GETPROPERTY_OnDockMove(){ if (!properties.contains("OnDockMove")) return false; return properties["OnDockMove"]->v_boolean; }

void SETPROPERTY_OnDockShow(t_boolean n){ if (!properties.contains("OnDockShow")) return; properties["OnDockShow"]->v_qstring = n; properties["OnDockShow"]->used = true; bModified = true; }
t_boolean GETPROPERTY_OnDockShow(){ if (!properties.contains("OnDockShow")) return false; return properties["OnDockShow"]->v_boolean; }

void SETPROPERTY_OnDockHide(t_boolean n){ if (!properties.contains("OnDockHide")) return; properties["OnDockHide"]->v_qstring = n; properties["OnDockHide"]->used = true; bModified = true; }
t_boolean GETPROPERTY_OnDockHide(){ if (!properties.contains("OnDockHide")) return false; return properties["OnDockHide"]->v_boolean; }

void SETPROPERTY_OnDockFloating(t_boolean n){ if (!properties.contains("OnDockFloating")) return; properties["OnDockFloating"]->v_qstring = n; properties["OnDockFloating"]->used = true; bModified = true; }
t_boolean GETPROPERTY_OnDockFloating(){ if (!properties.contains("OnDockFloating")) return false; return properties["OnDockFloating"]->v_boolean; }

void SETPROPERTY_OnDockNotFloating(t_boolean n){ if (!properties.contains("OnDockNotFloating")) return; properties["OnDockNotFloating"]->v_qstring = n; properties["OnDockNotFloating"]->used = true; bModified = true; }
t_boolean GETPROPERTY_OnDockNotFloating(){ if (!properties.contains("OnDockNotFloating")) return false; return properties["OnDockNotFloating"]->v_boolean; }






// ***

void addProperty(QString s, _propertyType t)
{
  properties[s] = new t_property;
  properties[s]->propertyType = t;
  properties[s]->readOnly = false;
  if (s == "OnEvent"){
    addProperty("SoundOnEvent", pt_qstring);
  }
}

bool loadProperty(QString *s, QString *sKey, /*t_properties *p, */bool *bb, QString *ss, int *nn)
{ 
  int n = 0;
  int n2 = 0;
  int n3 = 0;
  QString k = "";

  const char *sss = (*s).toAscii();
  sss = sss;

  n2 = (*s).indexOf("\n"); // get line
  k = (*s).left(n2);

  n3 = k.indexOf("'"); // ignore comments
  k = k.left(n3);

  k = k.trimmed();

  n = k.indexOf("="); // =

  if (n < 0){
    if (k.length() == 0){
      *s = (*s).mid(n2); // eat read property
    } else {
      //  fehlerhandling
    }
    return false;
  }

  (*sKey) = k.left(n);
  (*sKey) = (*sKey).trimmed();

  sss = (*sKey).toAscii();

  QString sValue = k.mid(n + 1);
  sValue = sValue.trimmed();

  sss = sValue.toAscii();

  *s = (*s).mid(n2); // eat read property
  if (n2 == -1) *s = "";

  sss = (*s).toAscii();

  // test for values
  if (sValue.compare("True") == 0 || sValue.compare("Yes") == 0 ){

    *bb = true;

  } else if (sValue.compare("False") == 0 || sValue.compare("No") == 0){

    *bb = false;

  } else if (sValue.startsWith("\"")){

    *ss = sValue.mid(1, sValue.length() - 2);
    (*ss).replace("_kbasicQM_", "\"");
    (*ss).replace("_kbasicQM2_", "'");
    (*ss).replace("_kbasicBR_", "\n");
    (*ss).replace("_kbasicMCB_", "/*");
    (*ss).replace("_kbasicMCE_", "*/");

  } else {

    *nn = sValue.toInt();

  }

  return true;
}

bool saveProperty(QString *s)
{
  t_properties::Iterator it;
  t_property *p;
  QString k;

  for ( it = properties.begin(); it != properties.end(); ++it ){

    p = *it;    
    k = it.key();

    if (!p->used) continue;

    if (k.compare("Name") == 0) continue;
    if (k.compare("ControlType") == 0) continue;

    if (k.compare("LoadedName") == 0) continue;
    if (k.compare("LoadedIndex") == 0) continue;
    if (k.compare("LoadedNull") == 0) continue;
    if (k.compare("LoadedType") == 0) continue;

    if (k.compare("OldHeight") == 0) continue;
    if (k.compare("OldWidth") == 0) continue;
    if (k.compare("OldX") == 0) continue;
    if (k.compare("OldY") == 0) continue;
    if (k.compare("OldBooleanValue") == 0) continue;
    if (k.compare("OldStringValue") == 0) continue;
    if (k.compare("OldIntegerValue") == 0) continue;

    if (k.compare("DockTitleVisible") == 0 && properties.contains("Dock") == false) continue;

    *s += "    " + k + " = ";

    switch(p->propertyType){
      case pt_integer:
        {
          QString t;

          t.sprintf("%d", p->v_integer);

          *s += t; 
        }
        break;
      case pt_event:
        {
          QString t;

          t.sprintf("%s", p->v_event ? "Yes" : "No");

          *s += t; 
        }
        break;
      case pt_boolean:
        {
          QString t;

          t.sprintf("%s", p->v_boolean ? "True" : "False");

          *s += t; 
        }
        break;
      case pt_qstring:
        {
          QString t = p->v_qstring;

          if (!t.isNull()){
            *s += "\"";
            t.replace("\"", "_kbasicQM_");
            t.replace("'", "_kbasicQM2_");
            t.replace("\r\n", "_kbasicBR_");
            t.replace("\n", "_kbasicBR_");
            t.replace("/*", "_kbasicMCB_");
            t.replace("*/", "_kbasicMCE_");

            *s += t;
            *s += "\"";
          }
        }
        break;
      default:
        break;
    }
    *s += "\n";

  }

  return true;
}

void applyProperties()
{
  t_properties::Iterator it;
  //QString k;
  t_property *d;
  QString ss;

  for ( it = properties.begin(); it != properties.end(); ++it ){
    //k = it.key();
    d = *it;

    ss = it.key();

    if (ss == "Name"){
      //SETPROPERTY_Name(d->v_qstring);
    } else if (ss == "ControlType"){
      //SETPROPERTY_ControlType(d->v_qstring);
    } else if (ss == "X"){
       SETPROPERTY_X(d->v_integer);
    } else if (ss == "Y"){
      SETPROPERTY_Y(d->v_integer);
    } else if (ss == "Width"){
      SETPROPERTY_Width(d->v_integer);
    } else if (ss == "Height"){
      SETPROPERTY_Height(d->v_integer);
    } else if (ss == "Caption"){
      SETPROPERTY_Caption(d->v_qstring);
    } else if (ss == "IntegerValue"){
      SETPROPERTY_IntegerValue(d->v_integer);
    } else if (ss == "Enabled"){
      SETPROPERTY_Enabled(d->v_boolean);
    } else if (ss == "Flip"){
      SETPROPERTY_Flip(d->v_boolean);
    } else if (ss == "Cursor"){
      SETPROPERTY_Cursor(d->v_qstring);
    } else if (ss == "TabIndex"){
      SETPROPERTY_TabIndex(d->v_integer);
    } else if (ss == "ParentIndex"){
      SETPROPERTY_ParentIndex(d->v_integer);
    } else if (ss == "Visible"){
      SETPROPERTY_Visible(d->v_boolean);
    } else if (ss == "WordWrap"){
      SETPROPERTY_WordWrap(d->v_boolean);
    } else if (ss == "ReadOnly"){
      SETPROPERTY_ReadOnly(d->v_boolean);
    } else if (ss == "Alignment"){
      SETPROPERTY_Alignment(d->v_qstring);
    } else if (ss == "EchoMode"){
      SETPROPERTY_EchoMode(d->v_qstring);
    } else if (ss == "Feature"){
      SETPROPERTY_Feature(d->v_qstring);
    } else if (ss == "Orientation"){
      SETPROPERTY_Orientation(d->v_qstring);



    }// else 

    if (ss == "EnterImage"){
      SETPROPERTY_EnterImage(d->v_qstring);

    } else if (ss == "Group"){
      SETPROPERTY_Group(d->v_qstring);

    } else if (ss == "Background"){
      SETPROPERTY_Background(d->v_qstring);

    } else if (ss == "BackgroundStyle"){
      SETPROPERTY_BackgroundStyle(d->v_qstring);

    } else if (ss == "Palette"){
      SETPROPERTY_Palette(d->v_qstring);

      
    } else if (ss == "MinimumWidth"){ SETPROPERTY_MinimumWidth(d->v_integer);
    } else if (ss == "MinimumHeight"){ SETPROPERTY_MinimumHeight(d->v_integer);
    } else if (ss == "MaximumWidth"){ SETPROPERTY_MaximumWidth(d->v_integer);
    } else if (ss == "MaximumHeight"){ SETPROPERTY_MaximumHeight(d->v_integer);

    } else if (ss == "StopOnClose"){ SETPROPERTY_StopOnClose(d->v_boolean);

    } else if (ss == "DockTitleVisible"){ SETPROPERTY_DockTitleVisible(d->v_boolean);
    } else if (ss == "DockParent"){ SETPROPERTY_DockOrder(d->v_qstring);

    } else if (ss == "DockSplit"){ SETPROPERTY_DockSplit(d->v_qstring);
    } else if (ss == "ShowMode"){ SETPROPERTY_ShowMode(d->v_qstring);
    } else if (ss == "FormFileName"){ SETPROPERTY_FormFileName(d->v_qstring);    
    } else if (ss == "FormModified"){ SETPROPERTY_FormModified(d->v_boolean);    

    } else if (ss == "FormX"){ SETPROPERTY_FormX(d->v_integer);    
    } else if (ss == "FormY"){ SETPROPERTY_FormY(d->v_integer);    
    } else if (ss == "FormWidth"){ SETPROPERTY_FormWidth(d->v_integer);    
    } else if (ss == "FormHeight"){ SETPROPERTY_FormHeight(d->v_integer);    


    } else if (ss == "DockWidth"){ SETPROPERTY_DockWidth(d->v_integer);
    } else if (ss == "DockHeight"){ SETPROPERTY_DockHeight(d->v_integer);

    } else if (ss == "ScrollX"){ SETPROPERTY_ScrollX(d->v_integer);
    } else if (ss == "ScrollY"){ SETPROPERTY_ScrollY(d->v_integer);
    } else if (ss == "ScrollWidth"){ SETPROPERTY_ScrollWidth(d->v_integer);
    } else if (ss == "ScrollHeight"){ SETPROPERTY_ScrollHeight(d->v_integer);

    } else if (ss == "MultiPageHeight"){ SETPROPERTY_MultiPageHeight(d->v_integer);
    } else if (ss == "MultiPageBorderTop"){ SETPROPERTY_MultiPageBorderTop(d->v_integer);
    } else if (ss == "MultiPageBorderBottom"){ SETPROPERTY_MultiPageBorderBottom(d->v_integer);
    } else if (ss == "MultiPageBorderLeft"){ SETPROPERTY_MultiPageBorderLeft(d->v_integer);
    } else if (ss == "MultiPageBorderRight"){ SETPROPERTY_MultiPageBorderRight(d->v_integer);

    } else if (ss == "BorderTop"){ SETPROPERTY_BorderTop(d->v_integer);
    } else if (ss == "BorderBottom"){ SETPROPERTY_BorderBottom(d->v_integer);
    } else if (ss == "BorderLeft"){ SETPROPERTY_BorderLeft(d->v_integer);
    } else if (ss == "BorderRight"){ SETPROPERTY_BorderRight(d->v_integer);

    } else if (ss == "CSV"){ SETPROPERTY_CSV(d->v_qstring);
        
    } else if (ss == "ArrowType"){ SETPROPERTY_ArrowType(d->v_qstring);
    } else if (ss == "PopupMode"){ SETPROPERTY_PopupMode(d->v_qstring);
    } else if (ss == "ToolBarRole"){ SETPROPERTY_ToolBarRole(d->v_qstring);

    } else if (ss == "Tag"){ SETPROPERTY_Tag(d->v_qstring);
    } else if (ss == "MenuBarRole"){ SETPROPERTY_MenuBarRole(d->v_qstring);
    } else if (ss == "Data"){ SETPROPERTY_Data(d->v_qstring);
    } else if (ss == "TableView"){ SETPROPERTY_TableView(d->v_boolean);
    } else if (ss == "Resizable"){ SETPROPERTY_Resizable(d->v_boolean);
    } else if (ss == "ResizableSmaller"){ SETPROPERTY_ResizableSmaller(d->v_boolean);
    } else if (ss == "ResizableBigger"){ SETPROPERTY_ResizableBigger(d->v_boolean);

    

    } else if (ss == "BoxIndex"){ SETPROPERTY_BoxIndex(d->v_integer);
    } else if (ss == "BoxX"){ SETPROPERTY_BoxX(d->v_integer);
    } else if (ss == "BoxY"){ SETPROPERTY_BoxY(d->v_integer);
    } else if (ss == "SplitIndex"){ SETPROPERTY_SplitIndex(d->v_integer);

    } else if (ss == "Scale"){ SETPROPERTY_Scale(d->v_boolean);
	/*
    } else if (ss == "FormCentered"){ SETPROPERTY_FormCentered(d->v_boolean);
    } else if (ss == "FormScaled"){ SETPROPERTY_FormScaled(d->v_boolean);
	*/
    } else if (ss == "DragDrop"){ SETPROPERTY_DragDrop(d->v_boolean);

    } else if (ss == "FocusPolicy"){ SETPROPERTY_FocusPolicy(d->v_qstring);
    } else if (ss == "FocusProxy"){ SETPROPERTY_FocusProxy(d->v_qstring);
    } else if (ss == "FocusOrder"){ SETPROPERTY_FocusOrder(d->v_integer);

    } else if (ss == "FontName"){ SETPROPERTY_FontName(d->v_qstring);
    } else if (ss == "FontSize"){ SETPROPERTY_FontSize(d->v_integer);
    } else if (ss == "FontBold"){ SETPROPERTY_FontBold(d->v_boolean);
    } else if (ss == "FontItalic"){ SETPROPERTY_FontItalic(d->v_boolean);
    } else if (ss == "FontUnderline"){ SETPROPERTY_FontUnderline(d->v_boolean);
    } else if (ss == "FontColor"){ SETPROPERTY_FontColor(d->v_qstring);

    } else if (ss == "StatusTip"){ SETPROPERTY_StatusTip(d->v_qstring);
    } else if (ss == "ToolTip"){ SETPROPERTY_ToolTip(d->v_qstring);
    } else if (ss == "StyleSheet"){ SETPROPERTY_StyleSheet(d->v_qstring);

    } else if (ss == "SQLControls"){ SETPROPERTY_SQLControls(d->v_qstring);
    } else if (ss == "Flag"){ SETPROPERTY_Flag(d->v_qstring);
    //} else if (ss == "IconCaption"){ SETPROPERTY_IconCaption(d->v_qstring);

    } else if (ss == "Modal"){ SETPROPERTY_Modal(d->v_boolean);
    } else if (ss == "Opacity"){ SETPROPERTY_Opacity(d->v_integer);
    } else if (ss == "TimerInterval"){ SETPROPERTY_TimerInterval(d->v_integer);

    } else if (ss == "Shadow"){ SETPROPERTY_Shadow(d->v_boolean);
    } else if (ss == "Shape"){ SETPROPERTY_Shape(d->v_boolean);
    } else if (ss == "OpenLinks"){ SETPROPERTY_OpenLinks(d->v_boolean);
    
    } else if (ss == "Icon"){ SETPROPERTY_Icon(d->v_qstring);
    } else if (ss == "InputControl"){ SETPROPERTY_InputControl(d->v_qstring);

    } else if (ss == "Space"){ SETPROPERTY_Space(d->v_integer);
    } else if (ss == "Border"){ SETPROPERTY_Border(d->v_integer);

    } else if (ss == "Flat"){ SETPROPERTY_Flat(d->v_boolean);
    } else if (ss == "Key"){ SETPROPERTY_Key(d->v_qstring);

    } else if (ss == "IntegerMaximum"){ SETPROPERTY_IntegerMaximum(d->v_integer);
    } else if (ss == "IntegerMinimum"){ SETPROPERTY_IntegerMinimum(d->v_integer);
    } else if (ss == "Completer"){ SETPROPERTY_Completer(d->v_qstring);

    } else if (ss == "ValidatorDouble"){ SETPROPERTY_ValidatorDouble(d->v_boolean);
    } else if (ss == "ValidatorInteger"){ SETPROPERTY_ValidatorInteger(d->v_boolean);

    } else if (ss == "ValidatorRegEx"){ SETPROPERTY_ValidatorRegEx(d->v_qstring);
    } else if (ss == "ValidatorRegEx2"){ SETPROPERTY_ValidatorRegEx2(d->v_qstring);

    } else if (ss == "DoubleEntry"){ SETPROPERTY_DoubleEntry(d->v_boolean);
    } else if (ss == "InsertPolicy"){ SETPROPERTY_InsertPolicy(d->v_qstring);
    } else if (ss == "Editable"){ SETPROPERTY_Editable(d->v_boolean);
    } else if (ss == "MaximumVisible"){ SETPROPERTY_MaximumVisible(d->v_integer);
    } else if (ss == "Sorted"){ SETPROPERTY_Sorted(d->v_boolean);

    } else if (ss == "StringMaximum"){ SETPROPERTY_StringMaximum(d->v_qstring);
    } else if (ss == "StringMinimum"){ SETPROPERTY_StringMinimum(d->v_qstring);
    } else if (ss == "Format"){ SETPROPERTY_Format(d->v_qstring);

    } else if (ss == "PopUp"){ SETPROPERTY_PopUp(d->v_boolean);
    
    } else if (ss == "ScrollBar"){ SETPROPERTY_ScrollBar(d->v_qstring);

    } else if (ss == "MouseDownImage"){ SETPROPERTY_MouseDownImage(d->v_qstring);
    } else if (ss == "MouseUpImage"){ SETPROPERTY_MouseUpImage(d->v_qstring);
    } else if (ss == "EnabledImage"){ SETPROPERTY_EnabledImage(d->v_qstring);
    } else if (ss == "MouseDownSound"){ SETPROPERTY_MouseDownSound(d->v_qstring);
    } else if (ss == "MouseUpSound"){ SETPROPERTY_MouseUpSound(d->v_qstring);
    } else if (ss == "HomeURL"){ SETPROPERTY_HomeURL(d->v_qstring);

    } else if (ss == "ExitImage"){
      SETPROPERTY_ExitImage(d->v_qstring);

    } else if (ss == "DisabledImage"){
      SETPROPERTY_DisabledImage(d->v_qstring);

    } else if (ss == "EnterSound"){
      SETPROPERTY_EnterSound(d->v_qstring);

    } else if (ss == "ExitSound"){
      SETPROPERTY_ExitSound(d->v_qstring);

    } else if (ss == "Menu"){
      SETPROPERTY_Menu(d->v_boolean);    

    } else if (ss == "RootIsDecorated"){
      SETPROPERTY_RootIsDecorated(d->v_boolean);    

    } else if (ss == "Interval"){
      SETPROPERTY_Interval(d->v_integer);

    }

    // PROPERTY
      
    if (ss == "DrawOnPaint"){  SETPROPERTY_DrawOnPaint(d->v_boolean);

    } else if (ss == "Prefix"){  SETPROPERTY_Prefix(d->v_qstring);
    } else if (ss == "Suffix"){  SETPROPERTY_Suffix(d->v_qstring);

    } else if (ss == "ViewMode"){  SETPROPERTY_ViewMode(d->v_qstring);

    } else if (ss == "TickPosition"){  SETPROPERTY_TickPosition(d->v_qstring);
    } else if (ss == "InvertedAppearance"){  SETPROPERTY_InvertedAppearance(d->v_boolean);
    } else if (ss == "InvertedControls"){  SETPROPERTY_InvertedControls(d->v_boolean);
    } else if (ss == "Tracking"){  SETPROPERTY_Tracking(d->v_boolean);
    } else if (ss == "TickInterval"){  SETPROPERTY_TickInterval(d->v_integer);
    } else if (ss == "PageStep"){  SETPROPERTY_PageStep(d->v_integer);
    } else if (ss == "SingleStep"){  SETPROPERTY_SingleStep(d->v_integer);

    } else if (ss == "Description"){  SETPROPERTY_Description(d->v_qstring);
    
    } else if (ss == "MoveOnMouseDrag"){  SETPROPERTY_MoveOnMouseDrag(d->v_boolean);
    } else if (ss == "MouseTracking"){  SETPROPERTY_MouseTracking(d->v_boolean);

    } else if (ss == "SoundOnEvent"){  SETPROPERTY_SoundOnEvent(d->v_qstring);
    } else if (ss == "ActionId"){  SETPROPERTY_ActionId(d->v_qstring);
    
    } else if (ss == "CursorAnimation"){  SETPROPERTY_CursorAnimation(d->v_qstring);
    

    } else if (ss == "Brightness"){  SETPROPERTY_Brightness(d->v_integer);
    } else if (ss == "Contrast"){  SETPROPERTY_Contrast(d->v_integer);
    } else if (ss == "Hue"){  SETPROPERTY_Hue(d->v_integer);
    } else if (ss == "Saturation"){  SETPROPERTY_Saturation(d->v_integer);
    } else if (ss == "ScaleMode"){  SETPROPERTY_ScaleMode(d->v_qstring);
    } else if (ss == "AspectRatio"){  SETPROPERTY_AspectRatio(d->v_qstring);

	} else if (ss == "TransitionTime"){  SETPROPERTY_TransitionTime(d->v_integer);
	} else if (ss == "Muted"){  SETPROPERTY_Muted(d->v_boolean);
	} else if (ss == "Volume"){  SETPROPERTY_Volume(d->v_integer);
	} else if (ss == "PrefinishMark"){  SETPROPERTY_PrefinishMark(d->v_integer);
	} else if (ss == "Tick"){  SETPROPERTY_Tick(d->v_integer);

	} else if (ss == "OnTick"){  SETPROPERTY_OnTick(d->v_event);
	} else if (ss == "OnStateChanged"){  SETPROPERTY_OnStateChanged(d->v_event);
	} else if (ss == "OnAboutToFinish"){  SETPROPERTY_OnAboutToFinish(d->v_event);
	} else if (ss == "OnFinished"){  SETPROPERTY_OnFinished(d->v_event);
	} else if (ss == "OnMutedChanged"){  SETPROPERTY_OnMutedChanged(d->v_event);
	} else if (ss == "OnVolumeChanged"){  SETPROPERTY_OnVolumeChanged(d->v_event);
	} else if (ss == "OnPlayedTitleChanged"){  SETPROPERTY_OnPlayingTitleChanged(d->v_event);
	} else if (ss == "OnBufferStatus"){  SETPROPERTY_OnBufferStatus(d->v_event);
  }

  if (ss == "OnTotalTimeChanged"){  SETPROPERTY_OnTotalTimeChanged(d->v_event);


    //} else if (ss == "Null"){  SETPROPERTY_Null(d->v_boolean);
    } else if (ss == "Index"){  SETPROPERTY_Index(d->v_boolean);
    } else if (ss == "OpenOnRun"){  SETPROPERTY_OpenAtStartup(d->v_boolean);
    } else if (ss == "Dock"){  SETPROPERTY_Dock(d->v_qstring);
    } else if (ss == "Layout"){  SETPROPERTY_Layout(d->v_qstring);
    } else if (ss == "SelectionMode"){  SETPROPERTY_SelectionMode(d->v_qstring);
    } else if (ss == "AlternatingRowColors"){  SETPROPERTY_AlternatingRowColors(d->v_boolean);
    } else if (ss == "Checked"){  SETPROPERTY_Checked(d->v_boolean);
    } else if (ss == "CheckableExclusive"){  SETPROPERTY_CheckableExclusive(d->v_boolean);    
    }

    if (ss == "PortName"){  SETPROPERTY_PortName(d->v_qstring);
    } else if (ss == "BaudRate"){  SETPROPERTY_BaudRate(d->v_qstring);
    } else if (ss == "DataBits"){  SETPROPERTY_DataBits(d->v_qstring);
    } else if (ss == "Parity"){  SETPROPERTY_Parity(d->v_qstring);
    } else if (ss == "FlowControl"){  SETPROPERTY_FlowControl(d->v_qstring);    
    } else if (ss == "StopBits"){  SETPROPERTY_StopBits(d->v_qstring);
    } else if (ss == "TimeOutMillisec"){  SETPROPERTY_TimeOutMillisec(d->v_integer);
    } else if (ss == "PollingInterval"){  SETPROPERTY_PollingInterval(d->v_integer);
    } else if (ss == "ContextMenu"){  SETPROPERTY_ContextMenu(d->v_qstring);

    } else if (ss == "Comment1Begin"){  SETPROPERTY_Comment1Begin(d->v_qstring);
    } else if (ss == "Comment1End"){  SETPROPERTY_Comment1End(d->v_qstring);
    } else if (ss == "Comment2Begin"){  SETPROPERTY_Comment2Begin(d->v_qstring);
    //} else if (ss == "Comment2End"){  SETPROPERTY_Comment2End(d->v_qstring);
    } else if (ss == "Keywords"){  SETPROPERTY_Keywords(d->v_qstring);
    } else if (ss == "Commands"){  SETPROPERTY_Commands(d->v_qstring);
    } else if (ss == "CommentColor"){  SETPROPERTY_CommentColor(d->v_qstring);
    } else if (ss == "KeywordColor"){  SETPROPERTY_KeywordColor(d->v_qstring);
    } else if (ss == "CommandColor"){  SETPROPERTY_CommandColor(d->v_qstring);

    } else if (ss == "SQL"){  SETPROPERTY_SQL(d->v_qstring);

    } else if (ss == "SQLName"){  SETPROPERTY_SQLName(d->v_qstring);
    } else if (ss == "SQLRelation"){  SETPROPERTY_SQLRelation(d->v_qstring);
    } else if (ss == "SQLInsert"){  SETPROPERTY_SQLInsert(d->v_boolean);
    } else if (ss == "SQLUpdate"){  SETPROPERTY_SQLUpdate(d->v_boolean);
    } else if (ss == "SQLDelete"){  SETPROPERTY_SQLDelete(d->v_boolean);

    } else if (ss == "TableViewCaption"){  SETPROPERTY_TableViewCaption(d->v_qstring);
    } else if (ss == "TableViewSort"){  SETPROPERTY_TableViewSort(d->v_qstring);
    } else if (ss == "TableViewFilter"){  SETPROPERTY_TableViewFilter(d->v_qstring);
    } else if (ss == "TableViewWidth"){  SETPROPERTY_TableViewWidth(d->v_integer);
    } else if (ss == "TableViewVisible"){  SETPROPERTY_TableViewVisible(d->v_boolean);
    } else if (ss == "TableViewOrder"){  SETPROPERTY_TableViewOrder(d->v_integer);
    }

    if (ss == "Pages"){  SETPROPERTY_Pages(d->v_qstring);
    } else if (ss == "ParentForm"){  SETPROPERTY_ParentForm(d->v_qstring);
    } else if (ss == "ParentControl"){  SETPROPERTY_ParentControl(d->v_qstring);
    } else if (ss == "TabIndex"){  SETPROPERTY_TabIndex(d->v_integer);
    } else if (ss == "ParentIndex"){  SETPROPERTY_ParentIndex(d->v_integer);

    } else if (ss == "StringValue"){
      SETPROPERTY_StringValue(d->v_qstring);

    } else if (ss == "InputMask"){
      SETPROPERTY_InputMask(d->v_qstring);
           
    } else if (ss == "Mask"){
      SETPROPERTY_Mask(d->v_qstring);
           
    } else if (ss == "EventOnOpen"){
      SETPROPERTY_EventOnOpen(d->v_boolean);
      
    } else if (ss == "AcceptRichText"){
      SETPROPERTY_AcceptRichText(d->v_boolean);

    } else if (ss == "AutoDefault"){
      SETPROPERTY_AutoDefault(d->v_boolean);

    } else if (ss == "Default"){
      SETPROPERTY_Default(d->v_boolean);

    } else if (ss == "Checkable"){
      SETPROPERTY_Checkable(d->v_boolean);
     
    } else if (ss == "Separator"){
      SETPROPERTY_Separator(d->v_boolean);

    } else if (ss == "BooleanValue"){
      SETPROPERTY_BooleanValue(d->v_boolean);
	}

    // EVENT

    if (ss == "OnEvent"){
      SETPROPERTY_OnEvent(d->v_event);

    //} else if (ss == "OnCursorPositionChanged"){  SETPROPERTY_OnCursorPositionChanged(d->v_event);
    } else if (ss == "OnEditingFinished"){  SETPROPERTY_OnEditingFinished(d->v_event);
    } else if (ss == "OnReturnPressed"){  SETPROPERTY_OnReturnPressed(d->v_event);
    } else if (ss == "OnSelectionChanged"){  SETPROPERTY_OnSelectionChanged(d->v_event);
    } else if (ss == "OnTextChanged"){  SETPROPERTY_OnTextChanged(d->v_event);
    } else if (ss == "OnTextEdited"){  SETPROPERTY_OnTextEdited(d->v_event);

    } else if (ss == "OnPage"){
      SETPROPERTY_OnPage(d->v_event);

    } else if (ss == "OnLinkHovered"){
      SETPROPERTY_OnLinkHovered(d->v_event);

    } else if (ss == "OnLoadFinished"){
      SETPROPERTY_OnLoadFinished(d->v_event);

    } else if (ss == "OnLoadProgress"){
      SETPROPERTY_OnLoadProgress(d->v_event);

    } else if (ss == "OnLoadStarted"){
      SETPROPERTY_OnLoadStarted(d->v_event);

    } else if (ss == "OnWindowCloseRequested"){
      SETPROPERTY_OnWindowCloseRequested(d->v_event);


    } else if (ss == "OnAction"){
      SETPROPERTY_OnAction(d->v_event);

    } else if (ss == "OnCursorPositionChanged"){
      SETPROPERTY_OnCursorPositionChanged(d->v_event);

    } else if (ss == "OnOpen"){
      SETPROPERTY_OnOpen(d->v_event);

    } else if (ss == "OnGoTo"){
      SETPROPERTY_OnGoTo(d->v_event);

    } else if (ss == "OnBeforeInsert"){
      SETPROPERTY_OnBeforeInsert(d->v_event);

    } else if (ss == "OnBeforeDelete"){
      SETPROPERTY_OnBeforeDelete(d->v_event);

    } else if (ss == "OnDragExit"){
      SETPROPERTY_OnDragExit(d->v_event);

    } else if (ss == "OnPaint"){
      SETPROPERTY_OnPaint(d->v_event);

    } else if (ss == "OnDirty"){  SETPROPERTY_OnDirty(d->v_event);
    } else if (ss == "OnAddNew"){  SETPROPERTY_OnAddNew(d->v_event);
    } else if (ss == "OnQuery"){  SETPROPERTY_OnQuery(d->v_event);

    } else if (ss == "OnTimer"){
      SETPROPERTY_OnTimer(d->v_event);

    } else if (ss == "OnClick"){
      SETPROPERTY_OnClick(d->v_event);

    } else if (ss == "OnDblClick"){
      SETPROPERTY_OnDblClick(d->v_event);

    } else if (ss == "OnMouseDown"){
      SETPROPERTY_OnMouseDown(d->v_event);

    } else if (ss == "OnMouseUp"){
      SETPROPERTY_OnMouseUp(d->v_event);

    } else if (ss == "OnMouseMove"){
      SETPROPERTY_OnMouseMove(d->v_event);

    } else if (ss == "OnGotFocus"){
      SETPROPERTY_OnGotFocus(d->v_event);

    } else if (ss == "OnLostFocus"){
      SETPROPERTY_OnLostFocus(d->v_event);

    } else if (ss == "OnEnter"){
      SETPROPERTY_OnEnter(d->v_event);

    } else if (ss == "OnExit"){
      SETPROPERTY_OnExit(d->v_event);

    } else if (ss == "OnKeyDown"){
      SETPROPERTY_OnKeyDown(d->v_event);

    } else if (ss == "OnKeyUp"){
      SETPROPERTY_OnKeyUp(d->v_event);

    } else if (ss == "OnKeyPress"){
      SETPROPERTY_OnKeyPress(d->v_event);

    } else if (ss == "OnBeforeUpdate"){
      SETPROPERTY_OnBeforeUpdate(d->v_event);

    } else if (ss == "OnOpen"){
      SETPROPERTY_OnOpen(d->v_event);

    } else if (ss == "OnResize"){
      SETPROPERTY_OnResize(d->v_event);

    } else if (ss == "OnClose"){
      SETPROPERTY_OnClose(d->v_event);

    } else if (ss == "OnPrint"){ SETPROPERTY_OnPrint(d->v_event);

    } else if (ss == "OnCurrentItemChanged"){ SETPROPERTY_OnCurrentItemChanged(d->v_event);
    } else if (ss == "OnItemActivated"){ SETPROPERTY_OnItemActivated(d->v_event);
    } else if (ss == "OnItemChanged"){ SETPROPERTY_OnItemChanged(d->v_event);
    } else if (ss == "OnItemClicked"){ SETPROPERTY_OnItemClicked(d->v_event);
    } else if (ss == "OnItemCollapsed"){ SETPROPERTY_OnItemCollapsed(d->v_event);
    } else if (ss == "OnItemDoubleClicked"){ SETPROPERTY_OnItemDoubleClicked(d->v_event);
    } else if (ss == "OnItemEntered"){ SETPROPERTY_OnItemEntered(d->v_event);
    } else if (ss == "OnItemExpanded"){ SETPROPERTY_OnItemExpanded(d->v_event);
    } else if (ss == "OnItemPressed"){ SETPROPERTY_OnItemPressed(d->v_event);
    } else if (ss == "OnItemSelectionChanged"){ SETPROPERTY_OnItemSelectionChanged(d->v_event);

    } else if (ss == "OnDockMove"){ SETPROPERTY_OnDockMove(d->v_event);
    } else if (ss == "OnDockShow"){ SETPROPERTY_OnDockShow(d->v_event);
    } else if (ss == "OnDockHide"){ SETPROPERTY_OnDockHide(d->v_event);
    } else if (ss == "OnDockFloating"){ SETPROPERTY_OnDockFloating(d->v_event);
    } else if (ss == "OnDockNotFloating"){ SETPROPERTY_OnDockNotFloating(d->v_event);

    } else if (ss == "OnDragEnter"){ SETPROPERTY_OnDragEnter(d->v_event);
    } else if (ss == "OnDragMove"){ SETPROPERTY_OnDragMove(d->v_event);
    } else if (ss == "OnDrop"){ SETPROPERTY_OnDrop(d->v_event);
    } else if (ss == "OnContextMenu"){ SETPROPERTY_OnContextMenu(d->v_event);
    } else if (ss == "OnMouseWheel"){ SETPROPERTY_OnMouseWheel(d->v_event);
    } else if (ss == "OnShow"){ SETPROPERTY_OnShow(d->v_event);
    } else if (ss == "OnHide"){ SETPROPERTY_OnHide(d->v_event);
    } else if (ss == "OnMove"){ SETPROPERTY_OnMove(d->v_event);

    } else if (ss == "OnEnabled"){ SETPROPERTY_OnEnabled(d->v_event);
    } else if (ss == "OnDisabled"){ SETPROPERTY_OnDisabled(d->v_event);
    } else if (ss == "OnSingleShot"){ SETPROPERTY_OnSingleShot(d->v_event);

    }
  }
}

static void addProperties(t_properties *p, t_properties *p2);

static void mergeProperties(t_properties *p, t_properties *p2, bool bApplyMode = false);

static void undisplayNameProperty(t_properties *p)
{
  t_properties::Iterator it;

  it = p->find("Name");
  (*it)->display = false;
}

static QColor getColor(const QString & n)
{
  QString s = n;
  bool ok = false;
  int v = 0;

  const char *ss = s.toAscii();

  if (s.startsWith("&h") || s.startsWith("&H")){    
    s = s.mid(2);
    v = s.toInt( &ok, 16 );
  } else {
    v = s.toInt( &ok, 10 );     
  }

  int r = 0xff & (v >> 16);
  int g = 0xff & (v >> 8);
  int b = 0xff & v;
  return QColor(r, g, b);  
}

static QFont getFont(const QString & n)
{ 
  QFont f;


  f.setFamily(n);

  return f;  
}  

t_properties *getProperties()
{
  return &properties;
}

public:

bool bModified;

protected:


t_properties properties;

};

#endif



