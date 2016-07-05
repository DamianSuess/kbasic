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

#include "interpreter.h"
#include "_mainwindow.h"
#include "_compile.h"

extern _mainwindow *EXTERN_my_mainwindow;

extern QString cachePath(QString s);

interpreter::interpreter(_compile *_my_compile)
{
  my_compile = _my_compile;
  f.setFileName(cachePath("runtime.interpreter"));  
}

interpreter::~interpreter(void)
{
  if (f.isOpen()) f.close();
}

bool interpreter::interpretContinue()
{
  f.open(QFile::WriteOnly);
  if (!f.isOpen()) return false;

  int n = f.write("interpretContinue");
  f.close();
  
  return true;
}

bool interpreter::interpretStepIn()
{
  f.open(QFile::WriteOnly);
  if (!f.isOpen()) return false;

  int n = f.write("interpretStepIn");
  f.close();
  

  return true;
}

bool interpreter::interpretStepOver(QString sFilename, int nCurrentLine)
{
  f.open(QFile::WriteOnly);
  if (!f.isOpen()) return false;

  
  

  QString s = "interpretStepOver|";
  s = s + sFilename;
  s = s + "|";
  s = s + QString("%1").arg(nCurrentLine);
  s = s + "|";

  int n = f.write(s.toAscii());
  f.close();

  return true;
}

bool interpreter::interpretStepOut()
{
  f.open(QFile::WriteOnly);
  if (!f.isOpen()) return false;

  int n = f.write("interpretStepOut");
  f.close();

  return true;
}

bool interpreter::interpretRunToCursor(QString sFilename, int nCurrentLine)
{
  f.open(QFile::WriteOnly);
  if (!f.isOpen()) return false;

  QString s = "interpretRunToCursor|";
  s = s + sFilename;
  s = s + "|";
  s = s + QString("%1").arg(nCurrentLine);
  s = s + "|";

  int n = f.write(s.toAscii());
  f.close();

  return true;
}

bool interpreter::interpretAddBreakpoint(QString sFilename, int nCurrentLine)
{
  f.open(QFile::WriteOnly);
  if (!f.isOpen()) return false;

  QString s = "interpretAddBreakpoint|";
  s = s + sFilename;
  s = s + "|";
  s = s + QString("%1").arg(nCurrentLine);
  s = s + "|";

  int n = f.write(s.toAscii());
  f.close();

  return true;
}

bool interpreter::interpretRemoveBreakpoint(QString sFilename, int nCurrentLine)
{
  f.open(QFile::WriteOnly);
  if (!f.isOpen()) return false;

  QString s = "interpretRemoveBreakpoint|";
  s = s + sFilename;
  s = s + "|";
  s = s + QString("%1").arg(nCurrentLine);
  s = s + "|";

  int n = f.write(s.toAscii());
  f.close();

  return true;
}

bool interpreter::interpretUpdateBreakpoint(QString sFilename, QString sLines)
{
  f.open(QFile::WriteOnly);
  if (!f.isOpen()) return false;

  QString s = "interpretUpdateBreakpoint|";
  s = s + sFilename;
  s = s + "|";
  s = s + sLines;
  s = s + "|";

  int n = f.write(s.toAscii());
  f.close();

  return true;
}

bool interpreter::showDebug(QString _sFile, int _nLine)
{
  return EXTERN_my_mainwindow->showDebug(_sFile, _nLine);
}

