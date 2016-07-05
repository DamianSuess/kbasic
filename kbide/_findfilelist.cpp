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

#include "_findfilelist.h"
#include "_mainwindow.h"
#include "_sourcecodeeditor.h"

extern _mainwindow *EXTERN_my_mainwindow;

_findfilelist::_findfilelist(QWidget *parent) : QListWidget(parent)
{


  connect(this, SIGNAL(itemActivated(QListWidgetItem *)), this, SLOT(itemActivated(QListWidgetItem *)));
}

void _findfilelist::itemActivated(QListWidgetItem *item)
{

  QString s = "";

  s = item->text();

  if (s.contains("(") > 0){
    int k = s.indexOf("(");
    
    QString sFile = s.left(k);

    int k2 = s.indexOf(")");
    QVariant v(s.mid(k + 1, k2 - k - 1));
    int nLine = v.toInt();


    if (sFile.endsWith(".kbasic_class", Qt::CaseInsensitive)){
      EXTERN_my_mainwindow->openClass(sFile);
    } else if (sFile.endsWith(".kbasic_module", Qt::CaseInsensitive)){
      EXTERN_my_mainwindow->openModule(sFile);
    } else if (sFile.endsWith(".kbasic_form", Qt::CaseInsensitive)){
      EXTERN_my_mainwindow->openFormClassSourceCode(sFile);
    } else if (sFile.endsWith(".kbasic_report", Qt::CaseInsensitive)){
      EXTERN_my_mainwindow->openReportClassSourceCode(sFile);
    } else if (sFile.endsWith(".kbasic_menubar", Qt::CaseInsensitive)){
      EXTERN_my_mainwindow->openMenuBarClassSourceCode(sFile);
    } else if (sFile.endsWith(".kbasic_toolbar", Qt::CaseInsensitive)){
      EXTERN_my_mainwindow->openToolBarClassSourceCode(sFile);
    } else if (sFile.endsWith(".kbasic", Qt::CaseInsensitive)){
      EXTERN_my_mainwindow->openModule(sFile);
    } else {
      EXTERN_my_mainwindow->openOther(sFile);
    }

    _sourcecodeeditor *o = qobject_cast<_sourcecodeeditor *>(EXTERN_my_mainwindow->workspace->activeSubWindow() ? EXTERN_my_mainwindow->workspace->activeSubWindow()->widget() : 0);
    if (o){

      o->setCurrentLineAndSelectLine(nLine);
    }


  }
}
