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


#ifndef _SYSTEMTRAY_H
#define _SYSTEMTRAY_H


#include "typedef.h"

#include <QSystemTrayIcon>
#include <QString>
#include <QBuffer>
#include <QMovie>

extern QString sProjectName;

extern QString sSystemTrayIcon;
extern QString sSystemTrayContextMenu;

class _forms;
extern _forms *my_forms;



extern QSystemTrayIcon *trayIcon;
extern QMovie *trayIcon_movie; extern QByteArray *trayIcon_moviea; extern QBuffer *trayIcon_movieb;

extern const QPixmap &interpreter_loadPixmap(QString fn);

class _systemtray
{
#ifdef RUN

public:


static t_boolean METHOD_IsSystemTrayAvailable()
{
  return QSystemTrayIcon::isSystemTrayAvailable();
} 

static t_boolean METHOD_IsPrintSupported()
{
  return QSystemTrayIcon::supportsMessages();
} 

static void METHOD_Print(QString Text)
{
  trayIcon->showMessage(sProjectName.isNull() ? "KBasic" : sProjectName, Text);
} 

static void METHOD_Print1(QString Text, QString Title)
{
  trayIcon->showMessage(Title, Text);
} 

static void METHOD_Print2(QString Text, QString Title, QString PrintIcon)
{
  int i = 0;

  if (PrintIcon.contains("NoIcon")) i |= QSystemTrayIcon::NoIcon;
  else if (PrintIcon.contains("Information")) i |= QSystemTrayIcon::Information;
  else if (PrintIcon.contains("Warning")) i |= QSystemTrayIcon::Warning;
  else if (PrintIcon.contains("Critical")) i |= QSystemTrayIcon::Critical;

  trayIcon->showMessage(Title, Text, (QSystemTrayIcon::MessageIcon) i);
} 

static void METHOD_Print3(QString Text, QString Title, QString PrintIcon, t_integer TimeOut)
{
  int i = 0;

  if (PrintIcon.contains("NoIcon")) i |= QSystemTrayIcon::NoIcon;
  else if (PrintIcon.contains("Information")) i |= QSystemTrayIcon::Information;
  else if (PrintIcon.contains("Warning")) i |= QSystemTrayIcon::Warning;
  else if (PrintIcon.contains("Critical")) i |= QSystemTrayIcon::Critical;

  trayIcon->showMessage(Title, Text, (QSystemTrayIcon::MessageIcon) i, TimeOut);

} 

static void METHOD_Show()
{
  trayIcon->show();
} 

static void METHOD_Hide()
{
  trayIcon->hide();
} 

static void METHOD_ToggleVisible()
{
  trayIcon->setVisible(!trayIcon->isVisible());
} 

static void PROPERTYSET_ContextMenu(QString k);

static QString PROPERTYGET_ContextMenu()
{
  return sSystemTrayContextMenu;
}

static void PROPERTYSET_Icon(QString n)
{
  sSystemTrayIcon = n;

   bool bMovie = false;
   QList<QByteArray> l = QMovie::supportedFormats();
   for (int i = 0; i < l.size(); ++i) {
      QString ss(l.at(i));
      if (n.endsWith("." + ss, Qt::CaseInsensitive)){
        bMovie = true;
        break;
      }
   }      
   if (bMovie){
     if (setMyMovie(0, &trayIcon_movie, &trayIcon_moviea, &trayIcon_movieb, n)){
       QObject::connect(trayIcon_movie, SIGNAL(frameChanged(int)), my_forms, SLOT(trayIcon_frameChanged(int)));
       trayIcon_movie->start();
     } else {
       trayIcon->setIcon(QIcon(interpreter_loadPixmap(n.contains(".") ? n : n + ".png")));
     }
     
   } else {
     trayIcon->setIcon(QIcon(interpreter_loadPixmap(n.contains(".") ? n : n + ".png")));
   }
}

static QString PROPERTYGET_Icon()
{
  return sSystemTrayIcon;
}

static void PROPERTYSET_ToolTip(QString k)
{
  trayIcon->setToolTip(k);
}

static QString PROPERTYGET_ToolTip()
{
  return trayIcon->toolTip();
}

static void PROPERTYSET_Visible(t_boolean k)
{
  trayIcon->setVisible(k);
}

static t_boolean PROPERTYGET_Visible()
{
  return trayIcon->isVisible();
}

static t_integer PROPERTYGET_GlobalX()
{
  return trayIcon->geometry().x();
}

static t_integer PROPERTYGET_GlobalY()
{
  return trayIcon->geometry().y();
}

static t_integer PROPERTYGET_Width()
{
  return trayIcon->geometry().width();
}

static t_integer PROPERTYGET_Height()
{
  return trayIcon->geometry().height();
}

#endif
};



#endif