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

#ifndef _BROWSER_H
#define _BROWSER_H

#include <QTextBrowser>

#include "typedef.h"




#include "_property.h"
#include "_control0.h"

#define TEST _browser    
#define TEST2 _browsers  
#define TEST3 "HtmlView"
#define SUPERCLASS QTextBrowser   

#define _BROWSER true

class _form;

class _browser : public QTextBrowser, public _property
{
  Q_OBJECT
public:



_browser(_form *f = 0, QWidget *parent = 0) : QTextBrowser (parent ? parent : (QWidget *) f)
{
  constructor(f, parent);

  // properties
  addProperty("StringValue", pt_qstring); addProperty("OldStringValue", pt_qstring); addProperty("OldStringValue", pt_qstring);
  addProperty("Flat", pt_boolean);
  addProperty("HomeURL", pt_qstring);
  addProperty("OpenLinks", pt_boolean);

  // events
  addProperty("OnEvent", pt_event);

  // default values
  SETPROPERTY_ControlType("HtmlView");
  SETPROPERTY_Visible(true);
  SETPROPERTY_Enabled(true);
  
  // slots
  connect(this, SIGNAL(backwardAvailable(bool)), this, SLOT(backwardAvailable(bool)));
  connect(this, SIGNAL(forwardAvailable(bool)), this, SLOT(forwardAvailable(bool)));
  connect(this, SIGNAL(sourceChanged(const QUrl &)), this, SLOT(sourceChanged(const QUrl &)));

}

#include "__property_x.h"
#include "__property_y.h"
#include "__property_flat.h"
#include "__property_stringvalue.h"
#include "__property_homeurl.h"
#include "__property_openlinks.h"


#ifdef RUN
void EVENT_OnSQLEvent();
#endif


public slots:

void backwardAvailable(bool b) // must be bool instead of t_boolean, cause of Qt
{
  EVENT_OnEvent(b, isForwardAvailable(), "");
}

void forwardAvailable(bool b) // must be bool instead of t_boolean, cause of Qt
{
  EVENT_OnEvent(isBackwardAvailable(), b, "");
}

void sourceChanged(const QUrl & u)
{
  EVENT_OnEvent(isBackwardAvailable(), isForwardAvailable(), u.toString());
}

// KBBINDINGEVENTS
virtual void EVENT_OnEvent(t_boolean BackwardAvailable, t_boolean ForwardAvailable, QString NewURL)
{
}

// KBBINDINGMETHODS

public:

QString GETPROPERTY_HomeURL()
{
  return source().toString();
}

#ifdef RUN  // ifdef needed, otherwise HomeURL will not function in IDE
QString GETPROPERTY_StringValue()
{
  return toPlainText();
}
#endif

t_boolean METHOD_BackwardAvailable()
{
  return isBackwardAvailable();
}

t_boolean METHOD_ForwardAvailable()
{
  return isForwardAvailable();
}

void METHOD_Backward()
{
  backward();
}

void METHOD_Forward()
{
  forward();
}

void METHOD_Reload()
{
  reload();
}

// ***
#include "_control1_binding.h"


// ***
#include "_control1.h"


};

#include "_control2.h"

#undef _BROWSER

#undef TEST
#undef TEST2
#undef TEST3
#undef SUPERCLASS


#endif