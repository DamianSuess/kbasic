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

#ifndef _compile_H
#define _compile_H

#include <QProcess>
#include <QFile>

class _compile : public QProcess
{
  Q_OBJECT

public:
  _compile(QObject *parent);
  ~_compile();




private slots:

void error(QProcess::ProcessError error);
void finished(int exitCode, QProcess::ExitStatus exitStatus);
void readyReadStandardError();
void readyReadStandardOutput();
void started();

private:
  void timerEvent(QTimerEvent *event);

  QFile f;
  QString s;
  int nTimerId;


};

#endif
