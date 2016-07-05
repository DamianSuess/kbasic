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


#ifndef _ERR_H
#define _ERR_H


#include "typedef.h"

/**
[KBASIC][VB][QBASIC]
NAME: ERR
PRINTNAME: Err
TASK: provided for backward compatibility. Use Try Catch Exception instead, if you start a new application.
DESC: 
DESCEND: 
PROPERTY1: Source As String PROPERTYDESC:' 
PROPERTY2: Description As String PROPERTYDESC:' 
PROPERTY3: Number As Integer PROPERTYDESC:' 
METHOD1: Sub Clear() METHODDESC:' clear the error properties
METHOD2: Sub Raise(Number As Integer, Source As String, Description As String) METHODDESC:' clear the error properties
EXAMPLES: err.kbasic
CATEGORY: CLASS
SEEALSO: 
LOG: 04-02-2004 implemented
TIP:
*/

#ifdef RUN
  class interpreter;
#endif

#include <qobject.h>
#include <qstring.h>

class _err : public QObject
{ 
  Q_OBJECT 
public:

  _err()
  { 
#ifdef RUN
    myInterpreter = 0; 
#endif
  }


#ifdef RUN
  void METHOD_Clear()
  {
    nNumber = 0;
    sSource = "";
    sDescription = "";
  }

  void METHOD_Raise(int _Number, QString _Source, QString _Description = "", bool bRaiseRuntimeError = true);
  
  void METHOD_Raise(int _Number, bool bRaiseRuntimeError = true){ METHOD_Raise(_Number, "", "", bRaiseRuntimeError); }
  void METHOD_Raise1(int _Number, QString _Source, bool bRaiseRuntimeError = true){ METHOD_Raise(_Number, _Source, "", bRaiseRuntimeError); }
  void METHOD_Raise2(int _Number, QString _Source, QString _Description, bool bRaiseRuntimeError = true){ METHOD_Raise(_Number, _Source, _Description, bRaiseRuntimeError); }

  int GETPROPERTY_Number()
  {
    return nNumber;
  }

  QString GETPROPERTY_Source()
  {

    return sSource;
  }

  QString GETPROPERTY_Description()
  {
    return sDescription;
  }


public:
  interpreter *myInterpreter;
  int nNumber;
  int nLine;

private:
  QString sSource;
  QString sDescription;
#endif
};

#endif