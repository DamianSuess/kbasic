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


#ifndef _INPUTDIALOG_H
#define _INPUTDIALOG_H


#include "typedef.h"

#include <QInputDialog>

extern bool _inputdialog_ok;

class _inputdialog
{
  
public:

/*
static t_double *METHOD_GetDouble()
{
  return 0;
} 
*/
static double METHOD_GetDouble(QString Caption, QString LabelCaption, t_double Value, t_double Minimum, t_double Maximum, t_integer Decimals)
{
  return QInputDialog::getDouble(qApp->focusWidget(), Caption, LabelCaption, Value, Minimum, Maximum, Decimals, &_inputdialog_ok);
} 

/*
static t_integer *METHOD_GetInteger()
{
  return 0;
} 
*/
static int METHOD_GetInteger(QString Caption, QString LabelCaption, t_double Value, t_double Minimum, t_double Maximum, t_integer Step)
{
  return QInputDialog::getInteger(qApp->focusWidget(), Caption, LabelCaption, Value, Minimum, Maximum, Step, &_inputdialog_ok);
} 
  /*
static t_integer *METHOD_GetString()
{
  return 0;
} 
*/
static QString METHOD_GetString(QString Caption, QString LabelCaption, QString Value, QString EchoMode)
{
  int i = 0;

  if (EchoMode.contains("Normal")) i |= QLineEdit::Normal;
  else if (EchoMode.contains("NoEcho")) i |= QLineEdit::NoEcho;
  else if (EchoMode.contains("PasswordEchoOnEdit")) i |= QLineEdit::PasswordEchoOnEdit;
  else if (EchoMode.contains("Password")) i |= QLineEdit::Password;

  return QInputDialog::getText(qApp->focusWidget(), Caption, LabelCaption, (QLineEdit::EchoMode) i, Value, &_inputdialog_ok);
} 

static bool METHOD_Ok()
{
  return _inputdialog_ok;
} 


}
;



#endif