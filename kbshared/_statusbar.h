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


#ifndef _STATUSBAR_H
#define _STATUSBAR_H


#include "typedef.h"


extern QMainWindow *forms_mainwindow;

class _statusbar
{
#ifdef RUN
public:

/*
static void METHOD_Print(QString k)
{
} 

static void METHOD_Print(QString k, t_integer TimeOut)
{
} 
*/


static void METHOD_Clear()
{
  if (forms_mainwindow){
    forms_mainwindow->statusBar()->clearMessage();
  }
} 

static void METHOD_Remove(_control *Control)
{
  if (forms_mainwindow){
    forms_mainwindow->statusBar()->removeWidget((QWidget *) Control);
  }
} 

static void METHOD_InsertControl(int Index, _control *Control)
{
  if (forms_mainwindow){
    forms_mainwindow->statusBar()->insertPermanentWidget(Index, (QWidget *) Control);
  }
} 

static void METHOD_InsertControl(int Index, _control *Control, int Stretch)
{
  if (forms_mainwindow){
    forms_mainwindow->statusBar()->insertPermanentWidget(Index - 1, (QWidget *) Control, Stretch);
  }
} 

static void METHOD_Print(QString Text)
{
  if (forms_mainwindow){
    forms_mainwindow->statusBar()->show();
    forms_mainwindow->statusBar()->showMessage(Text);
  }
} 

static void METHOD_Print(QString Text, int TimeOutInMilliSeconds)
{
  if (forms_mainwindow){
    forms_mainwindow->statusBar()->show();
    forms_mainwindow->statusBar()->showMessage(Text, TimeOutInMilliSeconds);
  }
} 

static void METHOD_Open()
{
  if (forms_mainwindow){
    forms_mainwindow->statusBar()->show();
  }
} 

static void METHOD_Close()
{
  if (forms_mainwindow){
    forms_mainwindow->statusBar()->hide();
  }
} 
static void METHOD_Toggle()
{
  if (forms_mainwindow){
    bool b = forms_mainwindow->statusBar()->isHidden();
    if (b) forms_mainwindow->statusBar()->show(); else forms_mainwindow->statusBar()->hide(); 
  }
} 


#endif
};



#endif