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

#ifndef _PREFERENCES_H
#define _PREFERENCES_H




#include "typedef.h"

#ifdef RUN

#include <QSettings>
extern QSettings *settings;

#endif

class _preferences
{
#ifdef RUN
public:


static t_boolean METHOD_Has(QString PreferenceId)
{
  QStringList l = settings->allKeys();
  return l.indexOf(PreferenceId) >= 0;
}

static void METHOD_Remove(QString PreferenceId)
{
  settings->remove(PreferenceId);
}
/*
static t_boolean METHOD_Load()
{
  return false;
}
   
static t_boolean METHOD_Save()
{
  return false;
}
*/

static _strings *METHOD_Ids()
{
  _strings *ss = new _strings();

  foreach(QString s, settings->allKeys())
  {
    ss->METHOD_Append(s);
  }

  return ss;
}  

static void METHOD_SetBoolean(QString PreferenceId, t_boolean Value)
{
  settings->setValue(PreferenceId, Value);
}

static void METHOD_SetInteger(QString PreferenceId, t_integer Value)
{
  settings->setValue(PreferenceId, Value);
}

static void METHOD_SetString(QString PreferenceId, QString Value)
{
  settings->setValue(PreferenceId, Value);
}

static void METHOD_SetDouble(QString PreferenceId, t_double Value)
{
  settings->setValue(PreferenceId, Value);
}

static t_boolean METHOD_Boolean(QString PreferenceId)
{
  return settings->value(PreferenceId).toBool();
}

static t_integer METHOD_Integer(QString PreferenceId)
{
  return settings->value(PreferenceId).toInt();
}

static QString METHOD_String(QString PreferenceId);

static t_double METHOD_Double(QString PreferenceId)
{
  return settings->value(PreferenceId).toDouble();
}

private:


#endif
};


#endif