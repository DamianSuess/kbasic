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


#ifndef _CONTROL_H
#define _CONTROL_H

#include <QWidget>

#include "typedef.h"

#ifdef RUN


#include "_property.h"


#define TEST _control    
#define TEST2 _controls   
#define TEST3 "Control"
#define SUPERCLASS QWidget   



#define _CONTROL true

class _form;

// actually this is a fake class and only be used for kbasic_binding, to get access to control in code, if an control has been cast to superclass control

class _control : public QWidget, public _property
{
  Q_OBJECT
public:


  _control(_form *f = 0, QWidget *parent = 0) : QWidget (parent ? parent : (QWidget *) f)
{
  

}

// events

// *** bindings
// *** 


_controlType controlType();


void METHOD_Move(t_integer X, t_integer Y);

void METHOD_Resize(t_integer Width, t_integer Height);

void METHOD_Show();

void METHOD_Hide();

void METHOD_RepaintAlways();

void METHOD_Repaint();

void METHOD_Raise();

void METHOD_Lower();

void METHOD_Close();

void METHOD_Open();

void METHOD_SetFocus();



void SETPROPERTY_X(t_integer n);
t_integer GETPROPERTY_X();

void SETPROPERTY_Y(t_integer n);
t_integer GETPROPERTY_Y();

void SETPROPERTY_Width(t_integer n);
t_integer GETPROPERTY_Width();

void SETPROPERTY_Height(t_integer n);
t_integer GETPROPERTY_Height();

const QString & GETPROPERTY_Name();

const QString & GETPROPERTY_Group();

void SETPROPERTY_Background(const QString & n);
const QString & GETPROPERTY_Background();

void SETPROPERTY_BackgroundStyle(const QString & n);
const QString & GETPROPERTY_BackgroundStyle();

void SETPROPERTY_Palette(const QString & n);
const QString & GETPROPERTY_Palette();

t_integer GETPROPERTY_GlobalX();

t_integer GETPROPERTY_GlobalY();

t_integer GETPROPERTY_OldX();

t_integer GETPROPERTY_OldY();

t_integer GETPROPERTY_OldWidth();

t_integer GETPROPERTY_OldHeight();

void SETPROPERTY_MinimumWidth(t_integer n);
t_integer GETPROPERTY_MinimumWidth();

void SETPROPERTY_MinimumHeight(t_integer n);
t_integer GETPROPERTY_MinimumHeight();

void SETPROPERTY_MaximumWidth(t_integer n);
t_integer GETPROPERTY_MaximumWidth();

void SETPROPERTY_MaximumHeight(t_integer n);
t_integer GETPROPERTY_MaximumHeight();

void SETPROPERTY_Tag(const QString & n);
const QString & GETPROPERTY_Tag();

void SETPROPERTY_CSV(const QString & n);
const QString & GETPROPERTY_CSV();

const QString & GETPROPERTY_ParentForm();

const QString & GETPROPERTY_ParentControl();

void SETPROPERTY_DragDrop(t_boolean n);
t_boolean GETPROPERTY_DragDrop();

const QString & GETPROPERTY_ControlType();

t_boolean GETPROPERTY_Focus();

void SETPROPERTY_FocusPolicy(const QString & n);
const QString & GETPROPERTY_FocusPolicy();

void SETPROPERTY_FocusProxy(const QString & n);
const QString & GETPROPERTY_FocusProxy();

t_integer GETPROPERTY_FocusOrder();

void SETPROPERTY_Cursor(const QString & n);
const QString & GETPROPERTY_Cursor();

void SETPROPERTY_FontName(const QString & n);
const QString & GETPROPERTY_FontName();

void SETPROPERTY_FontSize(t_integer n);
t_integer GETPROPERTY_FontSize();

void SETPROPERTY_FontItalic(t_boolean n);
t_boolean GETPROPERTY_FontItalic();

void SETPROPERTY_FontBold(t_boolean n);
t_boolean GETPROPERTY_FontBold();

void SETPROPERTY_FontUnderline(t_boolean n);
t_boolean GETPROPERTY_FontUnderline();

void SETPROPERTY_FontColor(const QString & n);
const QString & GETPROPERTY_FontColor();

void SETPROPERTY_Enabled(t_boolean n);
t_boolean GETPROPERTY_Enabled();

void SETPROPERTY_Visible(t_boolean n);
t_boolean GETPROPERTY_Visible();

void SETPROPERTY_StatusTip(const QString & n);
const QString & GETPROPERTY_StatusTip();

void SETPROPERTY_ToolTip(const QString & n);
const QString & GETPROPERTY_ToolTip();

void SETPROPERTY_StyleSheet(const QString & n);
const QString & GETPROPERTY_StyleSheet();

void SETPROPERTY_WhatsThis(const QString & n);
const QString & GETPROPERTY_WhatsThis();

void SETPROPERTY_TimerInterval(t_integer n);
t_integer GETPROPERTY_TimerInterval();

void SETPROPERTY_Opacity(t_integer n);
t_integer GETPROPERTY_Opacity();

void SETPROPERTY_SQL(const QString & n);
const QString & GETPROPERTY_SQL();

void SETPROPERTY_SQLName(const QString & n);
const QString & GETPROPERTY_SQLName();

void SETPROPERTY_SQLRelation(const QString & n);
const QString & GETPROPERTY_SQLRelation();

void SETPROPERTY_TableViewCaption(const QString & n);
const QString & GETPROPERTY_TableViewCaption();

void SETPROPERTY_TableViewSort(const QString & n);
const QString & GETPROPERTY_TableViewSort();

void SETPROPERTY_TableViewFilter(const QString & n);
const QString & GETPROPERTY_TableViewFilter();

void SETPROPERTY_Mask(const QString & n);
const QString & GETPROPERTY_Mask();

void SETPROPERTY_TableViewWidth(t_integer n);
t_integer GETPROPERTY_TableViewWidth();

void SETPROPERTY_TableViewVisible(t_boolean n);
t_boolean GETPROPERTY_TableViewVisible();

void SETPROPERTY_TableViewOrder(t_integer n);
t_integer GETPROPERTY_TableViewOrder();


void SETPROPERTY_LoadedX(t_integer n);
t_integer GETPROPERTY_LoadedX();

void SETPROPERTY_LoadedY(t_integer n);
t_integer GETPROPERTY_LoadedY();

void SETPROPERTY_LoadedWidth(t_integer n);
t_integer GETPROPERTY_LoadedWidth();

void SETPROPERTY_LoadedHeight(t_integer n);
t_integer GETPROPERTY_LoadedHeight();

void SETPROPERTY_DrawOnPaint(t_boolean n);
t_boolean GETPROPERTY_DrawOnPaint();

void SETPROPERTY_SoundOnEvent(const QString & n);
QString GETPROPERTY_SoundOnEvent();

void SETPROPERTY_CursorAnimation(const QString & n);
QString GETPROPERTY_CursorAnimation();

void SETPROPERTY_MouseTracking(t_boolean n);
t_boolean GETPROPERTY_MouseTracking();


void METHOD_DataRemove(QString Id);
void METHOD_DataRemoveAll();
void METHOD_DataSetBoolean(QString Id, t_boolean Value);
void METHOD_DataSetInteger(QString Id, t_integer Value);
void METHOD_DataSetString(QString Id, QString Value);
void METHOD_DataSetDouble(QString Id, t_double Value);
void METHOD_DataSetLong(QString Id, t_long Value);
void METHOD_DataSetDecimal(QString Id, t_currency Value);
void METHOD_DataSetDateTime(QString Id, t_date Value);

t_long METHOD_DataLong(QString Id);
t_currency METHOD_DataDecimal(QString Id);
t_date METHOD_DataDateTime(QString Id);

t_boolean METHOD_DataBoolean(QString Id);
t_integer METHOD_DataInteger(QString Id);
QString METHOD_DataString(QString Id);
t_double METHOD_DataDouble(QString Id);

void METHOD_ClearFocus();
void METHOD_ToggleVisible();
void METHOD_SingleShot(t_integer Milliseconds);

void METHOD_StartTimer();
void METHOD_StopTimer();

t_integer METHOD_LocalX(t_integer GlobalX);
t_integer METHOD_LocalY(t_integer GlobalY);

t_integer METHOD_GlobalX(t_integer LocalX);
t_integer METHOD_GlobalY(t_integer LocalY);
t_boolean METHOD_UnderMouse();


private:
_form *my_form;
// PROPERTY

};



#undef _CONTROL






#undef TEST
#undef TEST2
#undef TEST3
#undef SUPERCLASS

#endif

#endif