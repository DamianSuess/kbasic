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

#ifndef _process_H
#define _process_H


#include "../kbshared/typedef.h"

#include <QProcess>



class _process : public QProcess

{ 
public:


    static t_boolean METHOD_Run(QString FileName, t_boolean WaitForFinished)
    {
      QProcess p;
      p.start(FileName);

      bool b = p.waitForStarted();
      if (b && WaitForFinished) return p.waitForFinished(-1);
      if (b){
        do {
          qApp->processEvents();
        } while (p.state() != QProcess::NotRunning);
      }
      if (b) b = p.waitForFinished(-1);
      return b;
    }

    static t_boolean METHOD_Run1(QString FileName, _strings *Arguments, t_boolean WaitForFinished)
    {
      QProcess p;
      p.start(FileName, Arguments->qstringlist);

      bool b = p.waitForStarted();
      if (b && WaitForFinished) return p.waitForFinished(-1);
      if (b){
        do {
          qApp->processEvents();
        } while (p.state() != QProcess::NotRunning);
      }
      if (b) b = p.waitForFinished(-1);
      return b;
    }

    static t_boolean METHOD_Run2(QString s, _strings *Arguments, _strings *Environment, t_boolean WaitForFinished)
    {
      return false;
    }


private:


};




#endif