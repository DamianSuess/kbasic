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

#ifndef _MAINWINDOW_H
#define _MAINWINDOW_H




class _strings;
class _form;
class _control;

#include "typedef.h"

#ifdef RUN

#include <QMotifStyle>
#include <QCDEStyle>
#include <QCleanlooksStyle>
#ifdef MAC
#include <QMacStyle> // HIDE
#endif
#include <QPlastiqueStyle>
#include <QWindowsStyle>
#include <QWindowsXPStyle>
#include <QWindowsVistaStyle>

#include <QApplication>
#include <QMainWindow>
#include <QString>
#include <QMessageBox>
#include <QString>
#include <QTranslator>
#include <QMap>
#include <QClipboard>
#include <QDesktopWidget>
#include <QSound>
#include <QDesktopServices>
#include <QUrl>
#include <QIcon>
#include <QMdiArea>


extern QMainWindow *forms_mainwindow;

extern QMdiArea *forms_workspace;

#endif



class _mainwindow2
{
#ifdef RUN
public:

/*
static void EVENT_Application_OnOpen();


static void EVENT_Application_OnClose2(bool *Cancel); 
static void EVENT_Application_OnClose(bool *Cancel); 
*/


static void SETPROPERTY_X(int X)
{
  forms_mainwindow->move(X, forms_mainwindow->y());
}

static int GETPROPERTY_X()
{
  return forms_mainwindow->x();
}

static void SETPROPERTY_Y(int Y)
{
  forms_mainwindow->move(forms_mainwindow->x(), Y);
}

static int GETPROPERTY_Y()
{
  return forms_mainwindow->y();
}

static void SETPROPERTY_Width(int Width)
{
  forms_mainwindow->resize(Width, forms_mainwindow->height());
}

static int GETPROPERTY_Width()
{
  return forms_mainwindow->width();
}

static void SETPROPERTY_Height(int Height)
{
  forms_mainwindow->resize(forms_mainwindow->width(), Height);
}

static int GETPROPERTY_Height()
{
  return forms_mainwindow->height();
}

static void METHOD_SetVisible(t_boolean b)
{
  forms_mainwindow->setHidden(!b);
}

static t_boolean METHOD_IsVisible()
{
  return forms_mainwindow->isHidden();
}

static void METHOD_ShowFullScreen()
{
  forms_mainwindow->showFullScreen();
}

static void METHOD_ShowMaximized()
{
  forms_mainwindow->showMaximized();
}

static void METHOD_ShowMinimized()
{
  forms_mainwindow->showMinimized();
}

static void METHOD_ShowNormal()
{
  forms_mainwindow->showNormal();
}

static void METHOD_SetViewMode(QString n)
{
  if (forms_workspace == 0) return;

  int i = 0;

  if (n.contains("SubWindowView")) i |= QMdiArea::SubWindowView;
  else if (n.contains("TabbedView")) i |= QMdiArea::TabbedView;

  forms_workspace->setViewMode((QMdiArea::ViewMode) i);
}

static QString METHOD_ViewMode()
{
  if (forms_workspace == 0) return "";

  QMdiArea::ViewMode i = forms_workspace->viewMode();
  if (i == QMdiArea::SubWindowView) return "SubWindowView";
  else if (i == QMdiArea::TabbedView) return "TabbedView";

  return "";
}

static void METHOD_SetCaption(QString Text)
{
  if (forms_mainwindow) forms_mainwindow->setWindowTitle(Text);
}

static void METHOD_SetIcon(QString Text);



static t_boolean METHOD_IsScrollBarsEnabled();


static void METHOD_SetScrollBarsEnabled(t_boolean k);
static void METHOD_SetFocusNextForm();
static void METHOD_SetFocusPreviousForm();
static void METHOD_Cascade();
static void METHOD_CloseActiveForm();
static void METHOD_CloseAll();
static void METHOD_Tile();


static void METHOD_Move(int X, int Y)
{
  forms_mainwindow->move(X, Y);
}

static void METHOD_Resize(int Width, int Height)
{
  forms_mainwindow->resize(Width, Height);
}

static void METHOD_Close()
{
  forms_mainwindow->close();
}

static void METHOD_CloseAllWindows()
{
  qApp->closeAllWindows();
}

private:


#endif
};


#endif