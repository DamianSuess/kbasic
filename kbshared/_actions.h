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

#ifndef _ACTIONS_H
#define _ACTIONS_H




#include "typedef.h"

#ifdef RUN

#include <QAction>

#endif



class _actions
{
#ifdef RUN
public:


static void METHOD_SetEnabled(QString ActionId, t_boolean Value)
{
  _menubar::METHOD_SetEnabled(ActionId, Value);
  _toolbar::METHOD_SetEnabled(ActionId, Value);
}

static t_boolean METHOD_IsEnabled(QString ActionId)
{
  return _menubar::METHOD_IsEnabled(ActionId);
}

static void METHOD_SetVisible(QString ActionId, t_boolean Value)
{
  _menubar::METHOD_SetVisible(ActionId, Value);
  _toolbar::METHOD_SetVisible(ActionId, Value);
}

static t_boolean METHOD_IsVisible(QString ActionId)
{
  return _menubar::METHOD_IsVisible(ActionId);
}

static void METHOD_SetChecked(QString ActionId, t_boolean Value)
{
  _menubar::METHOD_SetChecked(ActionId, Value);
  _toolbar::METHOD_SetChecked(ActionId, Value);
}

static t_boolean METHOD_IsChecked(QString ActionId)
{
  return _menubar::METHOD_IsChecked(ActionId);
}

static void METHOD_SetStatusTip(QString ActionId, QString Value)
{
  _menubar::METHOD_SetStatusTip(ActionId, Value);
  _toolbar::METHOD_SetStatusTip(ActionId, Value);
}

static QString METHOD_StatusTip(QString ActionId)
{
  return _menubar::METHOD_StatusTip(ActionId);
}

static void METHOD_SetToolTip(QString ActionId, QString Value)
{
  _menubar::METHOD_SetToolTip(ActionId, Value);
  _toolbar::METHOD_SetToolTip(ActionId, Value);
}

static QString METHOD_ToolTip(QString ActionId)
{
  return _toolbar::METHOD_ToolTip(ActionId);
}

static void METHOD_SetWhatsThis(QString ActionId, QString Value)
{
  _menubar::METHOD_SetWhatsThis(ActionId, Value);
  _toolbar::METHOD_SetWhatsThis(ActionId, Value);
}

static QString METHOD_WhatsThis(QString ActionId)
{
  return _toolbar::METHOD_ToolTip(ActionId);
}

static void METHOD_SetIcon(QString ActionId, QString Value)
{
  _menubar::METHOD_SetIcon(ActionId, Value);
  _toolbar::METHOD_SetIcon(ActionId, Value);
}

static QString METHOD_Icon(QString ActionId)
{
  return _menubar::METHOD_ToolTip(ActionId);
}

static void METHOD_SetTag(QString ActionId, QString Value)
{
  _menubar::METHOD_SetTag(ActionId, Value);
  _toolbar::METHOD_SetTag(ActionId, Value);
}

static QString METHOD_Tag(QString ActionId)
{
  return _menubar::METHOD_Tag(ActionId);
}

static void METHOD_SetCaption(QString ActionId, QString Value)
{
  _menubar::METHOD_SetCaption(ActionId, Value);
  _toolbar::METHOD_SetCaption(ActionId, Value);
}

static QString METHOD_Caption(QString ActionId)
{
  return _menubar::METHOD_Caption(ActionId);
}

static void METHOD_SetText(QString ActionId, QString Value)
{
  _menubar::METHOD_SetText(ActionId, Value);
  _toolbar::METHOD_SetText(ActionId, Value);
}

static QString METHOD_Text(QString ActionId)
{
  return _menubar::METHOD_Text(ActionId);
}

static void METHOD_SetSoundOnEvent(QString ActionId, QString Value)
{
  _menubar::METHOD_SetSoundOnEvent(ActionId, Value);
  _toolbar::METHOD_SetSoundOnEvent(ActionId, Value);
}

static QString METHOD_SoundOnEvent(QString ActionId)
{
  return _menubar::METHOD_SoundOnEvent(ActionId);
}

static void METHOD_SetGroup(QString ActionId, QString Value)
{
  _menubar::METHOD_SetGroup(ActionId, Value);
  _toolbar::METHOD_SetGroup(ActionId, Value);
}

static QString METHOD_Group(QString ActionId)
{
  return _menubar::METHOD_Group(ActionId);
}

static void METHOD_SetKey(QString ActionId, QString Value)
{
  _menubar::METHOD_SetKey(ActionId, Value);
  _toolbar::METHOD_SetKey(ActionId, Value);
}

static QString METHOD_Key(QString ActionId)
{
  return _menubar::METHOD_Key(ActionId);
}


private:


#endif
};


#endif