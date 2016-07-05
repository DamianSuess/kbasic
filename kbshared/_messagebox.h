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


#ifndef _MESSAGEBOX_H
#define _MESSAGEBOX_H


#include "typedef.h"

#include <QMessageBox>

extern const QPixmap &interpreter_loadPixmap(QString fn);

extern QMessageBox *qmessagebox;

class _messagebox
{
#ifdef RUN

public:


static QString METHOD_Show(QString Caption, QString Text, QString Buttons, QString DefaultButton, QString DetailedText, QString Icon)
{
  if (qmessagebox) delete qmessagebox;
  qmessagebox = 0;

  int i = 0;

  if (Buttons.isEmpty()){
    i = QMessageBox::Ok;
  } else {

    if (Buttons.contains("Ok", Qt::CaseInsensitive)) i |= QMessageBox::Ok;
    if (Buttons.contains("Open", Qt::CaseInsensitive)) i |= QMessageBox::Open;
    if (Buttons.contains("Cancel", Qt::CaseInsensitive)) i |= QMessageBox::Cancel;
    if (Buttons.contains("Close", Qt::CaseInsensitive)) i |= QMessageBox::Close;
    if (Buttons.contains("Discard", Qt::CaseInsensitive)) i |= QMessageBox::Discard;
    if (Buttons.contains("Apply", Qt::CaseInsensitive)) i |= QMessageBox::Apply;
    if (Buttons.contains("Reset", Qt::CaseInsensitive)) i |= QMessageBox::Reset;
    if (Buttons.contains("RestoreDefaults", Qt::CaseInsensitive)) i |= QMessageBox::RestoreDefaults;
    if (Buttons.contains("Help", Qt::CaseInsensitive)) i |= QMessageBox::Help;
    if (Buttons.contains("Abort", Qt::CaseInsensitive)) i |= QMessageBox::Abort;
    if (Buttons.contains("Retry", Qt::CaseInsensitive)) i |= QMessageBox::Retry;
    if (Buttons.contains("Ignore", Qt::CaseInsensitive)) i |= QMessageBox::Ignore;
    if (Buttons.contains("SaveAll", Qt::CaseInsensitive)) i |= QMessageBox::SaveAll;
    if (Buttons.count("Save", Qt::CaseInsensitive) > 1 && Buttons.contains("SaveAll", Qt::CaseInsensitive)) i |= QMessageBox::Save;
    if ((Buttons.count("Save", Qt::CaseInsensitive) > 1 && Buttons.contains("SaveAll", Qt::CaseInsensitive)) || Buttons.count("Save", Qt::CaseInsensitive) == 1) i |= QMessageBox::Save;
    if (Buttons.contains("YesToAll", Qt::CaseInsensitive)) i |= QMessageBox::YesToAll;
    if (Buttons.count("Yes", Qt::CaseInsensitive) > 1 && Buttons.contains("YesToAll", Qt::CaseInsensitive) || Buttons.count("Yes", Qt::CaseInsensitive) == 1) i |= QMessageBox::Save;
    if (Buttons.contains("NoToAll", Qt::CaseInsensitive)) i |= QMessageBox::NoToAll;
    if (Buttons.count("No", Qt::CaseInsensitive) > 1 && Buttons.contains("NoToAll", Qt::CaseInsensitive) || Buttons.count("No", Qt::CaseInsensitive) == 1) i |= QMessageBox::Save;

  }

  qmessagebox = new QMessageBox(QMessageBox::NoIcon, Caption, Text, (QMessageBox::StandardButtons) i, qApp->focusWidget());

  int i2 = 0;

  if (DefaultButton.isEmpty()){
    i2 = QMessageBox::NoButton;
  } else {

    if (DefaultButton.contains("Ok", Qt::CaseInsensitive)) i2 |= QMessageBox::Ok;
    if (DefaultButton.contains("Open", Qt::CaseInsensitive)) i2 |= QMessageBox::Open;
    if (DefaultButton.contains("Cancel", Qt::CaseInsensitive)) i2 |= QMessageBox::Cancel;
    if (DefaultButton.contains("Close", Qt::CaseInsensitive)) i2 |= QMessageBox::Close;
    if (DefaultButton.contains("Discard", Qt::CaseInsensitive)) i2 |= QMessageBox::Discard;
    if (DefaultButton.contains("Apply", Qt::CaseInsensitive)) i2 |= QMessageBox::Apply;
    if (DefaultButton.contains("Reset", Qt::CaseInsensitive)) i2 |= QMessageBox::Reset;
    if (DefaultButton.contains("RestoreDefaults", Qt::CaseInsensitive)) i2 |= QMessageBox::RestoreDefaults;
    if (DefaultButton.contains("Help", Qt::CaseInsensitive)) i2 |= QMessageBox::Help;
    if (DefaultButton.contains("Abort", Qt::CaseInsensitive)) i2 |= QMessageBox::Abort;
    if (DefaultButton.contains("Retry", Qt::CaseInsensitive)) i2 |= QMessageBox::Retry;
    if (DefaultButton.contains("Ignore", Qt::CaseInsensitive)) i2 |= QMessageBox::Ignore;
    if (DefaultButton.contains("SaveAll", Qt::CaseInsensitive)) i2 |= QMessageBox::SaveAll;
    if ((DefaultButton.count("Save", Qt::CaseInsensitive) > 1 && DefaultButton.contains("SaveAll", Qt::CaseInsensitive)) || DefaultButton.count("Save", Qt::CaseInsensitive) == 1) i2 |= QMessageBox::Save;
    if (DefaultButton.contains("YesToAll", Qt::CaseInsensitive)) i2 |= QMessageBox::YesToAll;
    if (DefaultButton.count("Yes", Qt::CaseInsensitive) > 1 && DefaultButton.contains("YesToAll", Qt::CaseInsensitive) || DefaultButton.count("Yes", Qt::CaseInsensitive) == 1) i2 |= QMessageBox::Save;
    if (DefaultButton.contains("NoToAll", Qt::CaseInsensitive)) i2 |= QMessageBox::NoToAll;
    if (DefaultButton.count("No", Qt::CaseInsensitive) > 1 && DefaultButton.contains("NoToAll", Qt::CaseInsensitive) || DefaultButton.count("No", Qt::CaseInsensitive) == 1) i2 |= QMessageBox::Save;

  }
  qmessagebox->setDefaultButton((QPushButton *) qmessagebox->button((QMessageBox::StandardButton) i2));

#ifdef MAC
  qmessagebox->setInformativeText(DetailedText); // HIDE
#else
  qmessagebox->setDetailedText(DetailedText);
#endif

  if (!Icon.isEmpty()){
     if (Icon.length() > 200){ // QString contains binary data
       
       QPixmap pi; pi.loadFromData(Icon.toLatin1());
       qmessagebox->setIconPixmap(pi);
     } else {
       qmessagebox->setIconPixmap(interpreter_loadPixmap(Icon.contains(".") ? Icon : Icon + ".png"));
     }
  }

  QMessageBox::StandardButton b = (QMessageBox::StandardButton) qmessagebox->exec();

  if (b == QMessageBox::Ok) return "Ok";
  if (b == QMessageBox::Open) return "Open";
  if (b == QMessageBox::Cancel) return "Cancel";
  if (b == QMessageBox::Close) return "Close";
  if (b == QMessageBox::Discard) return "Discard";
  if (b == QMessageBox::Apply) return "Apply";
  if (b == QMessageBox::Reset) return "Reset";
  if (b == QMessageBox::RestoreDefaults) return "RestoreDefaults";
  if (b == QMessageBox::Help) return "Help";
  if (b == QMessageBox::Abort) return "Abort";
  if (b == QMessageBox::Retry) return "Retry";
  if (b == QMessageBox::Ignore) return "Ignore";
  if (b == QMessageBox::SaveAll) return "SaveAll";
  if (b == QMessageBox::Save) return "Save";
  if (b == QMessageBox::YesToAll) return "YesToAll";
  if (b == QMessageBox::Yes) return "Yes";
  if (b == QMessageBox::NoToAll) return "NoToAll";
  if (b == QMessageBox::No) return "No";

  return "";
} 

static QString METHOD_Critical(QString Caption, QString Text, QString Buttons, QString DefaultButton)
{
  int i = 0;

  if (Buttons.isEmpty()){
    i = QMessageBox::Ok;
  } else {

    if (Buttons.contains("Ok", Qt::CaseInsensitive)) i |= QMessageBox::Ok;
    if (Buttons.contains("Open", Qt::CaseInsensitive)) i |= QMessageBox::Open;
    if (Buttons.contains("Cancel", Qt::CaseInsensitive)) i |= QMessageBox::Cancel;
    if (Buttons.contains("Close", Qt::CaseInsensitive)) i |= QMessageBox::Close;
    if (Buttons.contains("Discard", Qt::CaseInsensitive)) i |= QMessageBox::Discard;
    if (Buttons.contains("Apply", Qt::CaseInsensitive)) i |= QMessageBox::Apply;
    if (Buttons.contains("Reset", Qt::CaseInsensitive)) i |= QMessageBox::Reset;
    if (Buttons.contains("RestoreDefaults", Qt::CaseInsensitive)) i |= QMessageBox::RestoreDefaults;
    if (Buttons.contains("Help", Qt::CaseInsensitive)) i |= QMessageBox::Help;
    if (Buttons.contains("Abort", Qt::CaseInsensitive)) i |= QMessageBox::Abort;
    if (Buttons.contains("Retry", Qt::CaseInsensitive)) i |= QMessageBox::Retry;
    if (Buttons.contains("Ignore", Qt::CaseInsensitive)) i |= QMessageBox::Ignore;
    if (Buttons.contains("SaveAll", Qt::CaseInsensitive)) i |= QMessageBox::SaveAll;
    if (Buttons.count("Save", Qt::CaseInsensitive) > 1 && Buttons.contains("SaveAll", Qt::CaseInsensitive)) i |= QMessageBox::Save;
    if ((Buttons.count("Save", Qt::CaseInsensitive) > 1 && Buttons.contains("SaveAll", Qt::CaseInsensitive)) || Buttons.count("Save", Qt::CaseInsensitive) == 1) i |= QMessageBox::Save;
    if (Buttons.contains("YesToAll", Qt::CaseInsensitive)) i |= QMessageBox::YesToAll;
    if (Buttons.count("Yes", Qt::CaseInsensitive) > 1 && Buttons.contains("YesToAll", Qt::CaseInsensitive) || Buttons.count("Yes", Qt::CaseInsensitive) == 1) i |= QMessageBox::Save;
    if (Buttons.contains("NoToAll", Qt::CaseInsensitive)) i |= QMessageBox::NoToAll;
    if (Buttons.count("No", Qt::CaseInsensitive) > 1 && Buttons.contains("NoToAll", Qt::CaseInsensitive) || Buttons.count("No", Qt::CaseInsensitive) == 1) i |= QMessageBox::Save;

  }

  int i2 = 0;

  if (DefaultButton.isEmpty()){
    i2 = QMessageBox::NoButton;
  } else {

    if (DefaultButton.contains("Ok", Qt::CaseInsensitive)) i2 |= QMessageBox::Ok;
    if (DefaultButton.contains("Open", Qt::CaseInsensitive)) i2 |= QMessageBox::Open;
    if (DefaultButton.contains("Cancel", Qt::CaseInsensitive)) i2 |= QMessageBox::Cancel;
    if (DefaultButton.contains("Close", Qt::CaseInsensitive)) i2 |= QMessageBox::Close;
    if (DefaultButton.contains("Discard", Qt::CaseInsensitive)) i2 |= QMessageBox::Discard;
    if (DefaultButton.contains("Apply", Qt::CaseInsensitive)) i2 |= QMessageBox::Apply;
    if (DefaultButton.contains("Reset", Qt::CaseInsensitive)) i2 |= QMessageBox::Reset;
    if (DefaultButton.contains("RestoreDefaults", Qt::CaseInsensitive)) i2 |= QMessageBox::RestoreDefaults;
    if (DefaultButton.contains("Help", Qt::CaseInsensitive)) i2 |= QMessageBox::Help;
    if (DefaultButton.contains("Abort", Qt::CaseInsensitive)) i2 |= QMessageBox::Abort;
    if (DefaultButton.contains("Retry", Qt::CaseInsensitive)) i2 |= QMessageBox::Retry;
    if (DefaultButton.contains("Ignore", Qt::CaseInsensitive)) i2 |= QMessageBox::Ignore;
    if (DefaultButton.contains("SaveAll", Qt::CaseInsensitive)) i2 |= QMessageBox::SaveAll;
    if ((DefaultButton.count("Save", Qt::CaseInsensitive) > 1 && DefaultButton.contains("SaveAll", Qt::CaseInsensitive)) || DefaultButton.count("Save", Qt::CaseInsensitive) == 1) i2 |= QMessageBox::Save;
    if (DefaultButton.contains("YesToAll", Qt::CaseInsensitive)) i2 |= QMessageBox::YesToAll;
    if (DefaultButton.count("Yes", Qt::CaseInsensitive) > 1 && DefaultButton.contains("YesToAll", Qt::CaseInsensitive) || DefaultButton.count("Yes", Qt::CaseInsensitive) == 1) i2 |= QMessageBox::Save;
    if (DefaultButton.contains("NoToAll", Qt::CaseInsensitive)) i2 |= QMessageBox::NoToAll;
    if (DefaultButton.count("No", Qt::CaseInsensitive) > 1 && DefaultButton.contains("NoToAll", Qt::CaseInsensitive) || DefaultButton.count("No", Qt::CaseInsensitive) == 1) i2 |= QMessageBox::Save;

  }
  QMessageBox::StandardButton b = QMessageBox::critical(qApp->focusWidget(), Caption, Text, (QMessageBox::StandardButtons) i, (QMessageBox::StandardButton) i2);

  if (b == QMessageBox::Ok) return "Ok";
  if (b == QMessageBox::Open) return "Open";
  if (b == QMessageBox::Cancel) return "Cancel";
  if (b == QMessageBox::Close) return "Close";
  if (b == QMessageBox::Discard) return "Discard";
  if (b == QMessageBox::Apply) return "Apply";
  if (b == QMessageBox::Reset) return "Reset";
  if (b == QMessageBox::RestoreDefaults) return "RestoreDefaults";
  if (b == QMessageBox::Help) return "Help";
  if (b == QMessageBox::Abort) return "Abort";
  if (b == QMessageBox::Retry) return "Retry";
  if (b == QMessageBox::Ignore) return "Ignore";
  if (b == QMessageBox::SaveAll) return "SaveAll";
  if (b == QMessageBox::Save) return "Save";
  if (b == QMessageBox::YesToAll) return "YesToAll";
  if (b == QMessageBox::Yes) return "Yes";
  if (b == QMessageBox::NoToAll) return "NoToAll";
  if (b == QMessageBox::No) return "No";

  return "";
} 

static QString METHOD_Information(QString Caption, QString Text, QString Buttons, QString DefaultButton)
{
  int i = 0;

  if (Buttons.isEmpty()){
    i = QMessageBox::Ok;
  } else {

    if (Buttons.contains("Ok", Qt::CaseInsensitive)) i |= QMessageBox::Ok;
    if (Buttons.contains("Open", Qt::CaseInsensitive)) i |= QMessageBox::Open;
    if (Buttons.contains("Cancel", Qt::CaseInsensitive)) i |= QMessageBox::Cancel;
    if (Buttons.contains("Close", Qt::CaseInsensitive)) i |= QMessageBox::Close;
    if (Buttons.contains("Discard", Qt::CaseInsensitive)) i |= QMessageBox::Discard;
    if (Buttons.contains("Apply", Qt::CaseInsensitive)) i |= QMessageBox::Apply;
    if (Buttons.contains("Reset", Qt::CaseInsensitive)) i |= QMessageBox::Reset;
    if (Buttons.contains("RestoreDefaults", Qt::CaseInsensitive)) i |= QMessageBox::RestoreDefaults;
    if (Buttons.contains("Help", Qt::CaseInsensitive)) i |= QMessageBox::Help;
    if (Buttons.contains("Abort", Qt::CaseInsensitive)) i |= QMessageBox::Abort;
    if (Buttons.contains("Retry", Qt::CaseInsensitive)) i |= QMessageBox::Retry;
    if (Buttons.contains("Ignore", Qt::CaseInsensitive)) i |= QMessageBox::Ignore;
    if (Buttons.contains("SaveAll", Qt::CaseInsensitive)) i |= QMessageBox::SaveAll;
    if ((Buttons.count("Save", Qt::CaseInsensitive) > 1 && Buttons.contains("SaveAll", Qt::CaseInsensitive)) || Buttons.count("Save", Qt::CaseInsensitive) == 1) i |= QMessageBox::Save;
    if (Buttons.contains("YesToAll", Qt::CaseInsensitive)) i |= QMessageBox::YesToAll;
    if (Buttons.count("Yes", Qt::CaseInsensitive) > 1 && Buttons.contains("YesToAll", Qt::CaseInsensitive) || Buttons.count("Yes", Qt::CaseInsensitive) == 1) i |= QMessageBox::Save;
    if (Buttons.contains("NoToAll", Qt::CaseInsensitive)) i |= QMessageBox::NoToAll;
    if (Buttons.count("No", Qt::CaseInsensitive) > 1 && Buttons.contains("NoToAll", Qt::CaseInsensitive) || Buttons.count("No", Qt::CaseInsensitive) == 1) i |= QMessageBox::Save;

  }

  int i2 = 0;

  if (DefaultButton.isEmpty()){
    i2 = QMessageBox::NoButton;
  } else {

    if (DefaultButton.contains("Ok", Qt::CaseInsensitive)) i2 |= QMessageBox::Ok;
    if (DefaultButton.contains("Open", Qt::CaseInsensitive)) i2 |= QMessageBox::Open;
    if (DefaultButton.contains("Cancel", Qt::CaseInsensitive)) i2 |= QMessageBox::Cancel;
    if (DefaultButton.contains("Close", Qt::CaseInsensitive)) i2 |= QMessageBox::Close;
    if (DefaultButton.contains("Discard", Qt::CaseInsensitive)) i2 |= QMessageBox::Discard;
    if (DefaultButton.contains("Apply", Qt::CaseInsensitive)) i2 |= QMessageBox::Apply;
    if (DefaultButton.contains("Reset", Qt::CaseInsensitive)) i2 |= QMessageBox::Reset;
    if (DefaultButton.contains("RestoreDefaults", Qt::CaseInsensitive)) i2 |= QMessageBox::RestoreDefaults;
    if (DefaultButton.contains("Help", Qt::CaseInsensitive)) i2 |= QMessageBox::Help;
    if (DefaultButton.contains("Abort", Qt::CaseInsensitive)) i2 |= QMessageBox::Abort;
    if (DefaultButton.contains("Retry", Qt::CaseInsensitive)) i2 |= QMessageBox::Retry;
    if (DefaultButton.contains("Ignore", Qt::CaseInsensitive)) i2 |= QMessageBox::Ignore;
    if (DefaultButton.contains("SaveAll", Qt::CaseInsensitive)) i2 |= QMessageBox::SaveAll;
    if ((DefaultButton.count("Save", Qt::CaseInsensitive) > 1 && DefaultButton.contains("SaveAll", Qt::CaseInsensitive)) || DefaultButton.count("Save", Qt::CaseInsensitive) == 1) i2 |= QMessageBox::Save;
    if (DefaultButton.contains("YesToAll", Qt::CaseInsensitive)) i2 |= QMessageBox::YesToAll;
    if (DefaultButton.count("Yes", Qt::CaseInsensitive) > 1 && DefaultButton.contains("YesToAll", Qt::CaseInsensitive) || DefaultButton.count("Yes", Qt::CaseInsensitive) == 1) i2 |= QMessageBox::Save;
    if (DefaultButton.contains("NoToAll", Qt::CaseInsensitive)) i2 |= QMessageBox::NoToAll;
    if (DefaultButton.count("No", Qt::CaseInsensitive) > 1 && DefaultButton.contains("NoToAll", Qt::CaseInsensitive) || DefaultButton.count("No", Qt::CaseInsensitive) == 1) i2 |= QMessageBox::Save;

  }
  QMessageBox::StandardButton b = QMessageBox::information(qApp->focusWidget(), Caption, Text, (QMessageBox::StandardButtons) i, (QMessageBox::StandardButton) i2);

  if (b == QMessageBox::Ok) return "Ok";
  if (b == QMessageBox::Open) return "Open";
  if (b == QMessageBox::Cancel) return "Cancel";
  if (b == QMessageBox::Close) return "Close";
  if (b == QMessageBox::Discard) return "Discard";
  if (b == QMessageBox::Apply) return "Apply";
  if (b == QMessageBox::Reset) return "Reset";
  if (b == QMessageBox::RestoreDefaults) return "RestoreDefaults";
  if (b == QMessageBox::Help) return "Help";
  if (b == QMessageBox::Abort) return "Abort";
  if (b == QMessageBox::Retry) return "Retry";
  if (b == QMessageBox::Ignore) return "Ignore";
  if (b == QMessageBox::SaveAll) return "SaveAll";
  if (b == QMessageBox::Save) return "Save";
  if (b == QMessageBox::YesToAll) return "YesToAll";
  if (b == QMessageBox::Yes) return "Yes";
  if (b == QMessageBox::NoToAll) return "NoToAll";
  if (b == QMessageBox::No) return "No";

  return "";
} 

static QString METHOD_Question(QString Caption, QString Text, QString Buttons, QString DefaultButton)
{
  int i = 0;

  if (Buttons.isEmpty()){
    i = QMessageBox::Ok;
  } else {

    if (Buttons.contains("Ok", Qt::CaseInsensitive)) i |= QMessageBox::Ok;
    if (Buttons.contains("Open", Qt::CaseInsensitive)) i |= QMessageBox::Open;
    if (Buttons.contains("Cancel", Qt::CaseInsensitive)) i |= QMessageBox::Cancel;
    if (Buttons.contains("Close", Qt::CaseInsensitive)) i |= QMessageBox::Close;
    if (Buttons.contains("Discard", Qt::CaseInsensitive)) i |= QMessageBox::Discard;
    if (Buttons.contains("Apply", Qt::CaseInsensitive)) i |= QMessageBox::Apply;
    if (Buttons.contains("Reset", Qt::CaseInsensitive)) i |= QMessageBox::Reset;
    if (Buttons.contains("RestoreDefaults", Qt::CaseInsensitive)) i |= QMessageBox::RestoreDefaults;
    if (Buttons.contains("Help", Qt::CaseInsensitive)) i |= QMessageBox::Help;
    if (Buttons.contains("Abort", Qt::CaseInsensitive)) i |= QMessageBox::Abort;
    if (Buttons.contains("Retry", Qt::CaseInsensitive)) i |= QMessageBox::Retry;
    if (Buttons.contains("Ignore", Qt::CaseInsensitive)) i |= QMessageBox::Ignore;
    if (Buttons.contains("SaveAll", Qt::CaseInsensitive)) i |= QMessageBox::SaveAll;
    if ((Buttons.count("Save", Qt::CaseInsensitive) > 1 && Buttons.contains("SaveAll", Qt::CaseInsensitive)) || Buttons.count("Save", Qt::CaseInsensitive) == 1) i |= QMessageBox::Save;
    if (Buttons.contains("YesToAll", Qt::CaseInsensitive)) i |= QMessageBox::YesToAll;
    if (Buttons.count("Yes", Qt::CaseInsensitive) > 1 && Buttons.contains("YesToAll", Qt::CaseInsensitive) || Buttons.count("Yes", Qt::CaseInsensitive) == 1) i |= QMessageBox::Save;
    if (Buttons.contains("NoToAll", Qt::CaseInsensitive)) i |= QMessageBox::NoToAll;
    if (Buttons.count("No", Qt::CaseInsensitive) > 1 && Buttons.contains("NoToAll", Qt::CaseInsensitive) || Buttons.count("No", Qt::CaseInsensitive) == 1) i |= QMessageBox::Save;

  }

  int i2 = 0;

  if (DefaultButton.isEmpty()){
    i2 = QMessageBox::NoButton;
  } else {

    if (DefaultButton.contains("Ok", Qt::CaseInsensitive)) i2 |= QMessageBox::Ok;
    if (DefaultButton.contains("Open", Qt::CaseInsensitive)) i2 |= QMessageBox::Open;
    if (DefaultButton.contains("Cancel", Qt::CaseInsensitive)) i2 |= QMessageBox::Cancel;
    if (DefaultButton.contains("Close", Qt::CaseInsensitive)) i2 |= QMessageBox::Close;
    if (DefaultButton.contains("Discard", Qt::CaseInsensitive)) i2 |= QMessageBox::Discard;
    if (DefaultButton.contains("Apply", Qt::CaseInsensitive)) i2 |= QMessageBox::Apply;
    if (DefaultButton.contains("Reset", Qt::CaseInsensitive)) i2 |= QMessageBox::Reset;
    if (DefaultButton.contains("RestoreDefaults", Qt::CaseInsensitive)) i2 |= QMessageBox::RestoreDefaults;
    if (DefaultButton.contains("Help", Qt::CaseInsensitive)) i2 |= QMessageBox::Help;
    if (DefaultButton.contains("Abort", Qt::CaseInsensitive)) i2 |= QMessageBox::Abort;
    if (DefaultButton.contains("Retry", Qt::CaseInsensitive)) i2 |= QMessageBox::Retry;
    if (DefaultButton.contains("Ignore", Qt::CaseInsensitive)) i2 |= QMessageBox::Ignore;
    if (DefaultButton.contains("SaveAll", Qt::CaseInsensitive)) i2 |= QMessageBox::SaveAll;
    if ((DefaultButton.count("Save", Qt::CaseInsensitive) > 1 && DefaultButton.contains("SaveAll", Qt::CaseInsensitive)) || DefaultButton.count("Save", Qt::CaseInsensitive) == 1) i2 |= QMessageBox::Save;
    if (DefaultButton.contains("YesToAll", Qt::CaseInsensitive)) i2 |= QMessageBox::YesToAll;
    if (DefaultButton.count("Yes", Qt::CaseInsensitive) > 1 && DefaultButton.contains("YesToAll", Qt::CaseInsensitive) || DefaultButton.count("Yes", Qt::CaseInsensitive) == 1) i2 |= QMessageBox::Save;
    if (DefaultButton.contains("NoToAll", Qt::CaseInsensitive)) i2 |= QMessageBox::NoToAll;
    if (DefaultButton.count("No", Qt::CaseInsensitive) > 1 && DefaultButton.contains("NoToAll", Qt::CaseInsensitive) || DefaultButton.count("No", Qt::CaseInsensitive) == 1) i2 |= QMessageBox::Save;

  }
  QMessageBox::StandardButton b = QMessageBox::question(qApp->focusWidget(), Caption, Text, (QMessageBox::StandardButtons) i, (QMessageBox::StandardButton) i2);

  if (b == QMessageBox::Ok) return "Ok";
  if (b == QMessageBox::Open) return "Open";
  if (b == QMessageBox::Cancel) return "Cancel";
  if (b == QMessageBox::Close) return "Close";
  if (b == QMessageBox::Discard) return "Discard";
  if (b == QMessageBox::Apply) return "Apply";
  if (b == QMessageBox::Reset) return "Reset";
  if (b == QMessageBox::RestoreDefaults) return "RestoreDefaults";
  if (b == QMessageBox::Help) return "Help";
  if (b == QMessageBox::Abort) return "Abort";
  if (b == QMessageBox::Retry) return "Retry";
  if (b == QMessageBox::Ignore) return "Ignore";
  if (b == QMessageBox::SaveAll) return "SaveAll";
  if (b == QMessageBox::Save) return "Save";
  if (b == QMessageBox::YesToAll) return "YesToAll";
  if (b == QMessageBox::Yes) return "Yes";
  if (b == QMessageBox::NoToAll) return "NoToAll";
  if (b == QMessageBox::No) return "No";

  return "";
} 

static QString METHOD_Warning(QString Caption, QString Text, QString Buttons, QString DefaultButton)
{
  int i = 0;

  if (Buttons.isEmpty()){
    i = QMessageBox::Ok;
  } else {

    if (Buttons.contains("Ok", Qt::CaseInsensitive)) i |= QMessageBox::Ok;
    if (Buttons.contains("Open", Qt::CaseInsensitive)) i |= QMessageBox::Open;
    if (Buttons.contains("Cancel", Qt::CaseInsensitive)) i |= QMessageBox::Cancel;
    if (Buttons.contains("Close", Qt::CaseInsensitive)) i |= QMessageBox::Close;
    if (Buttons.contains("Discard", Qt::CaseInsensitive)) i |= QMessageBox::Discard;
    if (Buttons.contains("Apply", Qt::CaseInsensitive)) i |= QMessageBox::Apply;
    if (Buttons.contains("Reset", Qt::CaseInsensitive)) i |= QMessageBox::Reset;
    if (Buttons.contains("RestoreDefaults", Qt::CaseInsensitive)) i |= QMessageBox::RestoreDefaults;
    if (Buttons.contains("Help", Qt::CaseInsensitive)) i |= QMessageBox::Help;
    if (Buttons.contains("Abort", Qt::CaseInsensitive)) i |= QMessageBox::Abort;
    if (Buttons.contains("Retry", Qt::CaseInsensitive)) i |= QMessageBox::Retry;
    if (Buttons.contains("Ignore", Qt::CaseInsensitive)) i |= QMessageBox::Ignore;
    if (Buttons.contains("SaveAll", Qt::CaseInsensitive)) i |= QMessageBox::SaveAll;
    if ((Buttons.count("Save", Qt::CaseInsensitive) > 1 && Buttons.contains("SaveAll", Qt::CaseInsensitive)) || Buttons.count("Save", Qt::CaseInsensitive) == 1) i |= QMessageBox::Save;
    if (Buttons.contains("YesToAll", Qt::CaseInsensitive)) i |= QMessageBox::YesToAll;
    if (Buttons.count("Yes", Qt::CaseInsensitive) > 1 && Buttons.contains("YesToAll", Qt::CaseInsensitive) || Buttons.count("Yes", Qt::CaseInsensitive) == 1) i |= QMessageBox::Save;
    if (Buttons.contains("NoToAll", Qt::CaseInsensitive)) i |= QMessageBox::NoToAll;
    if (Buttons.count("No", Qt::CaseInsensitive) > 1 && Buttons.contains("NoToAll", Qt::CaseInsensitive) || Buttons.count("No", Qt::CaseInsensitive) == 1) i |= QMessageBox::Save;

  }

  int i2 = 0;

  if (DefaultButton.isEmpty()){
    i2 = QMessageBox::NoButton;
  } else {

    if (DefaultButton.contains("Ok", Qt::CaseInsensitive)) i2 |= QMessageBox::Ok;
    if (DefaultButton.contains("Open", Qt::CaseInsensitive)) i2 |= QMessageBox::Open;
    if (DefaultButton.contains("Cancel", Qt::CaseInsensitive)) i2 |= QMessageBox::Cancel;
    if (DefaultButton.contains("Close", Qt::CaseInsensitive)) i2 |= QMessageBox::Close;
    if (DefaultButton.contains("Discard", Qt::CaseInsensitive)) i2 |= QMessageBox::Discard;
    if (DefaultButton.contains("Apply", Qt::CaseInsensitive)) i2 |= QMessageBox::Apply;
    if (DefaultButton.contains("Reset", Qt::CaseInsensitive)) i2 |= QMessageBox::Reset;
    if (DefaultButton.contains("RestoreDefaults", Qt::CaseInsensitive)) i2 |= QMessageBox::RestoreDefaults;
    if (DefaultButton.contains("Help", Qt::CaseInsensitive)) i2 |= QMessageBox::Help;
    if (DefaultButton.contains("Abort", Qt::CaseInsensitive)) i2 |= QMessageBox::Abort;
    if (DefaultButton.contains("Retry", Qt::CaseInsensitive)) i2 |= QMessageBox::Retry;
    if (DefaultButton.contains("Ignore", Qt::CaseInsensitive)) i2 |= QMessageBox::Ignore;
    if (DefaultButton.contains("SaveAll", Qt::CaseInsensitive)) i2 |= QMessageBox::SaveAll;
    if ((DefaultButton.count("Save", Qt::CaseInsensitive) > 1 && DefaultButton.contains("SaveAll", Qt::CaseInsensitive)) || DefaultButton.count("Save", Qt::CaseInsensitive) == 1) i2 |= QMessageBox::Save;
    if (DefaultButton.contains("YesToAll", Qt::CaseInsensitive)) i2 |= QMessageBox::YesToAll;
    if (DefaultButton.count("Yes", Qt::CaseInsensitive) > 1 && DefaultButton.contains("YesToAll", Qt::CaseInsensitive) || DefaultButton.count("Yes", Qt::CaseInsensitive) == 1) i2 |= QMessageBox::Save;
    if (DefaultButton.contains("NoToAll", Qt::CaseInsensitive)) i2 |= QMessageBox::NoToAll;
    if (DefaultButton.count("No", Qt::CaseInsensitive) > 1 && DefaultButton.contains("NoToAll", Qt::CaseInsensitive) || DefaultButton.count("No", Qt::CaseInsensitive) == 1) i2 |= QMessageBox::Save;

  }
  QMessageBox::StandardButton b = QMessageBox::warning(qApp->focusWidget(), Caption, Text, (QMessageBox::StandardButtons) i, (QMessageBox::StandardButton) i2);

  if (b == QMessageBox::Ok) return "Ok";
  if (b == QMessageBox::Open) return "Open";
  if (b == QMessageBox::Cancel) return "Cancel";
  if (b == QMessageBox::Close) return "Close";
  if (b == QMessageBox::Discard) return "Discard";
  if (b == QMessageBox::Apply) return "Apply";
  if (b == QMessageBox::Reset) return "Reset";
  if (b == QMessageBox::RestoreDefaults) return "RestoreDefaults";
  if (b == QMessageBox::Help) return "Help";
  if (b == QMessageBox::Abort) return "Abort";
  if (b == QMessageBox::Retry) return "Retry";
  if (b == QMessageBox::Ignore) return "Ignore";
  if (b == QMessageBox::SaveAll) return "SaveAll";
  if (b == QMessageBox::Save) return "Save";
  if (b == QMessageBox::YesToAll) return "YesToAll";
  if (b == QMessageBox::Yes) return "Yes";
  if (b == QMessageBox::NoToAll) return "NoToAll";
  if (b == QMessageBox::No) return "No";

  return "";
}

  /*
static void METHOD_About(QString Title, QString Caption)
{
} 

} 
*/
#endif
};



#endif