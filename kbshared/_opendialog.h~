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

#ifndef _OPENDIALOG_H
#define _OPENDIALOG_H


#include "typedef.h"

#include "_strings.h"

#include <QMainWindow>
#include <QFileDialog>


extern QMainWindow *forms_mainwindow;

class _opendialog : public QFileDialog
{  


public:

#ifdef RUN
  

static QString METHOD_GetFile()
{
  return QFileDialog::getOpenFileName(qApp->focusWidget());
}

static QString METHOD_GetFile(QString Caption, QString Directory, QString Filter)
{
  return QFileDialog::getOpenFileName(qApp->focusWidget(), Caption, Directory, Filter);
}

static _strings *METHOD_GetFiles()
{
  QStringList l = QFileDialog::getOpenFileNames(qApp->focusWidget());

  _strings *ss = new _strings();

  foreach(QString s, l)
  {
    ss->METHOD_Append(s);
  }

  return ss;
}

static _strings *METHOD_GetFiles(QString Caption, QString Directory, QString Filter)
{
  QStringList l = QFileDialog::getOpenFileNames(qApp->focusWidget(), Caption, Directory, Filter);

  _strings *ss = new _strings();

  foreach(QString s, l)
  {
    ss->METHOD_Append(s);
  }

  return ss;
}

static QString METHOD_GetDirectory()
{
  return QFileDialog::getExistingDirectory(qApp->focusWidget());
}

static QString METHOD_GetDirectory(QString Caption, QString Directory)
{
  return QFileDialog::getExistingDirectory(qApp->focusWidget(), Caption, Directory);
}

/*
void METHOD_SetMode(QString Mode)
{
  int i = 0;
  if (n.contains("AnyFile")) i |= QFileDialog::AnyFile;
  if (n.contains("ExistingFile")) i |= QFileDialog::ExistingFile;
  if (n.contains("Directory")) i |= QFileDialog::Directory;
  if (n.contains("DirectoryOnly")) i |= QFileDialog::DirectoryOnly;
  if (n.contains("ExistingFiles")) i |= QFileDialog::ExistingFiles;

  setMode((QFileDialog::FileMode) i);
}

void METHOD_SetOption(QString Option)
{

  int i = 0;
  if (n.contains("ShowDirsOnly")) i |= QFileDialog::ShowDirsOnly;
  if (n.contains("DontResolveSymlinks")) i |= QFileDialog::DontResolveSymlinks;
  if (n.contains("DontConfirmOverwrite")) i |= QFileDialog::DontConfirmOverwrite;
  if (n.contains("DontUseSheet")) i |= QFileDialog::DontUseSheet;
  if (n.contains("DontUseNativeDialog")) i |= QFileDialog::DontUseNativeDialog;

  setOption((QFileDialog::Option) i);
}
*/

#endif
};

#endif

