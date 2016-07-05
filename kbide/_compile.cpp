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

#include <QtGui>

#include "_compile.h"
#include "_mainwindow.h"
#include "_infoconsole.h"

#include "_locallist.h"
#include "_globallist.h"
#include "_stacklist.h"

extern _melist *EXTERN_melist;
extern _locallist *EXTERN_locallist;
extern _globallist *EXTERN_globallist;
extern _stacklist *EXTERN_stacklist;

extern _mainwindow *EXTERN_my_mainwindow;

extern QString runPath(QString s);
extern QString cachePath(QString s);

_compile::_compile(QObject *parent) : QProcess(parent)
{

  connect(this, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(finished(int, QProcess::ExitStatus)));
  connect(this, SIGNAL(readyReadStandardError()), this, SLOT(readyReadStandardError()));
  connect(this, SIGNAL(readyReadStandardOutput()), this, SLOT(readyReadStandardOutput()));

  f.setFileName(cachePath("compiler.output"));
  nTimerId = startTimer(100);

  
}

_compile::~_compile(void)
{
  f.close();
}




void _compile::error ( QProcess::ProcessError error )
{

}

void _compile::finished ( int exitCode, QProcess::ExitStatus exitStatus )
{  
  close();
}
void _compile::readyReadStandardError ()
{
  
  QString s = readAllStandardError();    
  s = s.simplified();
/*
  if (s.startsWith("##kbprogress##")){
    int n = s.mid(10).toInt();
    if (n > 0)EXTERN_my_mainwindow->oPercentInfo->setValue(n);
  } else if (s.startsWith("##kbfile##")){    
    s = s.mid(10);
    sCurrentFile = s;
    EXTERN_my_mainwindow->my_infoconsole->print(s.toAscii(), 0);
    EXTERN_my_mainwindow->statusBar()->showMessage(s.toAscii());
  } else*/ 
  {
    int n = s.indexOf("in line ") + 8;  
    QString sCurrentFile = "";
    if (n >= 0 && s.lastIndexOf("in file") >= 0) sCurrentFile = s.mid(s.lastIndexOf("in file") + 8);

    int nLine = 0;
    if (s.contains("near pos")){
      nLine = s.mid(n, s.lastIndexOf("near pos") - n).toInt();
    } else if (s.contains("in file")){
      nLine = s.mid(n, s.indexOf("in file", n) - n).toInt();
    } else {
      nLine = 0;
    }
    n = s.lastIndexOf("in file");
    if (n >= 0){
      s = s.left(n);
    }
    killTimer(nTimerId);
    EXTERN_my_mainwindow->showError(sCurrentFile, nLine, s);
  }

  
}

void _compile::readyReadStandardOutput ()
{
  static bool bLock = false;


  if (bLock) return;

  bLock = true;
 

  QByteArray ba = readAllStandardOutput();

  if (ba.size() == 0) return;

  QString s = QString::fromUtf8(ba.data(), ba.size());



  if(!s.isEmpty()){
  
  //  QMessageBox::information(EXTERN_my_mainwindow, "KBasic", s);

    int n0 = 0;
    int n = n0 = s.indexOf("interruptDebugAtBreakpoint|");
    
    if (n >= 0){ 
      //s = s.mid(n);
      n += QString("interruptDebugAtBreakpoint|").length();
      int n2 = s.indexOf("|", n);
      QString sCurrentFile = s.mid(n, n2 - n);
      n = s.indexOf("|", n2 + 1);
      n2++;
      QString sLine = s.mid(n2, n - n2);
      n++;

      EXTERN_my_mainwindow->showDebug(sCurrentFile, sLine.toInt());    

      QString s2 = s.left(n0);
      s2 = s2 + s.mid(n);
      s = s2;

      EXTERN_melist->clear();
      EXTERN_locallist->clear();
      EXTERN_globallist->clear();
      EXTERN_stacklist->clear();

      QFile ff;
      ff.setFileName(cachePath("ide.debuginfo"));  
      ff.open(QFile::ReadOnly);
      if (ff.isOpen()){
        QString s = QString::fromUtf8(ff.readAll());
        int n = 0;

        QString sStack = "";
        int l = s.length();
        while (n < l){
          QString sT = s.mid(n, 5); n += 5; int t = sT.toInt();
          QString sLn = s.mid(n, 5); n += 5; int ln = sLn.toInt();
          QString sLv = s.mid(n, 5); n += 5; int lv = sLv.toInt();
          QString sLt = s.mid(n, 5); n += 5; int lt = sLt.toInt();

          QString sName = s.mid(n, ln); n += ln;
          QString sValue = s.mid(n, lv); n += lv;
          QString sType = s.mid(n, lt); n += lt;

          if (t == 1) EXTERN_globallist->add(sName, sValue, sType);
          else if (t == 2) EXTERN_locallist->add(sName, sValue, sType);
          else if (t == 4) EXTERN_melist->add(sName, sValue, sType);
          else if (t == 3){
            sStack = sStack.prepend("|");        
            sStack = sStack.prepend(sName);  
          }
        }
        QStringList ll = sStack.split("|");
        for (int i = 0; i < ll.size(); ++i){          
          EXTERN_stacklist->add(ll.at(i), "", "");
        }

        ff.close();
      }

    }
      
    EXTERN_my_mainwindow->my_infoconsole->print(ba.data(), 0);
  }

  bLock = false;
  
}

void _compile::started ()
{  
}

void _compile::timerEvent(QTimerEvent *event)
{  
  
  bool b = f.open(QIODevice::ReadOnly);

  if (b){
    QByteArray a = f.readAll();
    f.close();
    QString s2 = a.data();
    if (s2 != s && !s2.simplified().isEmpty()){
      if (s2.startsWith("#")){
        EXTERN_my_mainwindow->oPercentInfo->setValue(s2.mid(1).toInt());
      } else {
        EXTERN_my_mainwindow->statusBar()->showMessage(s2);
      }
      s = s2;
    }    
  }
}
