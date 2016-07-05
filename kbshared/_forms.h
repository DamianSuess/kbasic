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

#ifndef _FORMS_H
#define _FORMS_H

#include <QString>
#include <QWidget>
#include <QMdiSubWindow>
#include <QMovie>
#include <QBuffer>
#include <QMainWindow>
#include <QIcon>
#include <QSystemTrayIcon>


#include "typedef.h"

class kb_form;

extern QMainWindow *forms_mainwindow;

class _forms : public QObject
{
#ifdef RUN
  Q_OBJECT

public:
_forms()
{
  movie = 0; moviea = 0; movieb = 0;
}

~_forms()
{
  if (movie) delete movie; if (moviea) delete moviea; if (movieb) delete movieb;
}

public slots:

void activated(QSystemTrayIcon::ActivationReason);
void messageClicked();


void trayIcon_frameChanged(int);

void frameChanged(int)
{
  forms_mainwindow->setWindowIcon(movie->currentPixmap());
}

  void setActiveSubWindow(QWidget *window);

  void CONTENTS();
  void ABOUT();

void SLOT_AddFilter();
void SLOT_AddNotFilter();
void SLOT_SetFilter();
void SLOT_SetNotFilter();
void SLOT_ClearFilter();
void SLOT_SortAscending();
void SLOT_SortDescending();
void SLOT_Seek();
void SLOT_Requery();
void SLOT_AddNew();
void SLOT_Update();
void SLOT_Delete();

void SLOT_Cut();
void SLOT_Copy();
void SLOT_Paste();


  void updateWindowMenu();
  void subWindowActivated(QMdiSubWindow *w);
  void lastWindowClosed();

public:

static void init();
static void deinit();

static void METHOD_OpenForm(QString k);
static void METHOD_CloseForm(QString k);
/*
static void METHOD_SetMenuBar(QString k);
static void METHOD_AppendToolBar(QString k);
static void METHOD_InsertToolBarBreak();
static void METHOD_RemoveToolBar(QString k);
static QString METHOD_ActiveControl();*/
static QString METHOD_FocusForm();
static QString METHOD_FirstForm();
static QString METHOD_NextForm();
static void METHOD_SetFocusForm(QString k);
static t_boolean METHOD_IsOpen(QString k);




static kb_form *METHOD_Form(QString s);


static void METHOD_FormShowFullScreen(QString k);
static void METHOD_FormShowMaximized(QString k);
static void METHOD_FormShowMinimized(QString k);
static void METHOD_FormShowNormal(QString k);
static void METHOD_FormShow(QString k);
static void METHOD_FormHide(QString k);




public:
  
QMovie *movie; QByteArray *moviea; QBuffer *movieb;


#endif

}
;



#endif