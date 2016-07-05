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

#ifndef interpreter_H
#define interpreter_H

#include <QString>
#include <QFile>


class _compile;

class interpreter
{
public:
  interpreter(_compile *_my_compile);
  ~interpreter();

  bool interpretContinue();  

  bool interpretStepIn();  

  bool interpretStepOver(QString sFilename, int nCurrentLine);

  bool interpretStepOut();

  bool interpretRunToCursor(QString sFilename, int nCurrentLine);

  bool interpretAddBreakpoint(QString sFilename, int nCurrentLine);
  bool interpretRemoveBreakpoint(QString sFilename, int nCurrentLine);
  bool interpretUpdateBreakpoint(QString sFilename, QString sLines);

  bool showDebug(QString _sFile, int _nLine);
private:
  _compile *my_compile;
  QFile f;
};

#endif