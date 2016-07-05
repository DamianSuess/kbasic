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


#ifndef _WEB_H
#define _WEB_H

#include <QWebView>
#include <QWebHistory>
#include <QWebFrame>


class QNetworkReply;



#include "typedef.h"

#ifdef RUN
#include <QNetworkRequest>
#endif


#include "_property.h"


#include "_control0.h"

#include "_strings.h"



#define TEST _web    
#define TEST2 _webs  
#define TEST3 "WebView"
#define SUPERCLASS QWebView   

#define _WEB true

class _form;

#ifdef RUN
class qwebpage : public QWebPage
{
  Q_OBJECT
public:

qwebpage ( QObject * parent = 0 ) : QWebPage(parent){}

bool acceptNavigationRequest(QWebFrame *frame, const QNetworkRequest &request, NavigationType type);

QObject *createPlugin(const QString & classid, const QUrl & url, const QStringList & paramNames, const QStringList & paramValues );

};
#endif


class _web : public QWebView, public _property
{
  Q_OBJECT
public:



_web(_form *f = 0, QWidget *parent = 0) : QWebView (parent ? parent : (QWidget *) f)
{
  constructor(f, parent);

  // properties
  addProperty("StringValue", pt_qstring); addProperty("OldStringValue", pt_qstring); addProperty("OldStringValue", pt_qstring);
  //addProperty("Flat", pt_boolean);
  addProperty("HomeURL", pt_qstring);
  //addProperty("OpenLinks", pt_boolean);

  // events
  addProperty("OnEvent", pt_event);
  addProperty("OnPage", pt_event);
  addProperty("OnLinkHovered", pt_event);
  addProperty("OnLoadFinished", pt_event);
  addProperty("OnLoadProgress", pt_event);
  addProperty("OnLoadStarted", pt_event);
  addProperty("OnWindowCloseRequested", pt_event);


  // default values
  SETPROPERTY_ControlType("WebView");
  SETPROPERTY_Visible(true);
  SETPROPERTY_Enabled(true);

#ifdef IDE
  SETPROPERTY_HomeURL(" "); // WORKAROUND for display problems in IDE
  SETPROPERTY_HomeURL("");
#endif
  
  // slots
  /*
  connect(this, SIGNAL(backwardAvailable(bool)), this, SLOT(backwardAvailable(bool)));
  connect(this, SIGNAL(forwardAvailable(bool)), this, SLOT(forwardAvailable(bool)));
  connect(this, SIGNAL(sourceChanged(const QUrl &)), this, SLOT(sourceChanged(const QUrl &)));
  */
#ifdef RUN
  setPage(new qwebpage(this));
  page()->settings()->setAttribute(QWebSettings::PluginsEnabled, true);
  page()->settings()->setAttribute(QWebSettings::JavascriptEnabled, true);

  connect(this, SIGNAL(urlChanged(const QUrl &)), this, SLOT(urlChanged(const QUrl &)));
  connect(this, SIGNAL(linkClicked(const QUrl &)), this, SLOT(linkClicked(const QUrl &)));

  connect(page(), SIGNAL(unsupportedContent(QNetworkReply *)), this, SLOT(unsupportedContent(QNetworkReply *)));
   
  page()->setForwardUnsupportedContent(true);
  //page()->setLinkDelegationPolicy(QWebPage::DelegateExternalLinks);

  connect(page(), SIGNAL(linkHovered(const QString &, const QString &, const QString &)), this, SLOT(EVENT_OnLinkHovered(const QString &, const QString &, const QString &)));
  connect(this, SIGNAL(loadFinished(bool)), this, SLOT(EVENT_OnLoadFinished2(bool)));
  connect(this, SIGNAL(loadProgress(int)), this, SLOT(EVENT_OnLoadProgress2(int)));
  connect(this, SIGNAL(loadStarted()), this, SLOT(EVENT_OnLoadStarted())); 
  connect(page(), SIGNAL(windowCloseRequested ()), this, SLOT(EVENT_OnWindowCloseRequested()));

#endif

}



#include "__property_x.h"
#include "__property_y.h"
#include "__property_flat.h"
#include "__property_stringvalue.h"
#include "__property_homeurl.h"


#ifdef RUN
void EVENT_OnSQLEvent();
#endif

public slots:

/*
void backwardAvailable(bool b) // must be bool instead of t_boolean, cause of Qt
{
  EVENT_OnEvent(b, isForwardAvailable(), "");
}

void forwardAvailable(bool b) // must be bool instead of t_boolean, cause of Qt
{
  EVENT_OnEvent(isBackwardAvailable(), b, "");
}
*/

#ifdef RUN

void urlChanged(const QUrl & u)
{
  EVENT_OnEvent(METHOD_BackwardAvailable(), METHOD_ForwardAvailable(), u.toString());
}


void linkClicked(const QUrl & u);

void unsupportedContent( QNetworkReply * reply);
#endif

// KBBINDINGEVENTS
virtual void EVENT_OnEvent(t_boolean BackwardAvailable, t_boolean ForwardAvailable, QString NewURL)
{
}

virtual void EVENT_OnPage(QString NewPage)
{
}
virtual void EVENT_OnLinkHovered(const QString & Link, const QString & Title, const QString & TextContent)
{
}

virtual void EVENT_OnLoadFinished2(bool Ok)
{
  EVENT_OnLoadFinished(Ok);
}

virtual void EVENT_OnLoadFinished(t_boolean Ok)
{
}

virtual void EVENT_OnLoadProgress2(int Progress)
{
  EVENT_OnLoadProgress(Progress);
}

virtual void EVENT_OnLoadProgress(t_integer Progress)
{
}

virtual void EVENT_OnLoadStarted()
{
}

virtual void EVENT_OnWindowCloseRequested()
{
}


// KBBINDINGMETHODS

public:

/*
QString GETPROPERTY_HomeURL()
{
  return url().toString();
}*/

#ifdef RUN  // ifdef needed, otherwise HomeURL will not function in IDE
QString GETPROPERTY_StringValue()
{
  return page()->currentFrame()->toPlainText();
}

QString METHOD_Argument(QString Name);

_strings *METHOD_Keys();
_strings *METHOD_Values();


t_boolean METHOD_BackwardAvailable()
{
  return history()->canGoBack();
}

t_boolean METHOD_ForwardAvailable()
{
  return history()->canGoForward();
}

void METHOD_Backward()
{
  back();
}

void METHOD_Forward()
{
  forward();
}

void METHOD_Reload()
{
  reload();
}
#endif

// ***
#include "_control1_binding.h"


// ***
#include "_control1.h"

public:
  QStringList Keys;
  QStringList Values;
};

#include "_control2.h"

#undef _WEB

#undef TEST
#undef TEST2
#undef TEST3
#undef SUPERCLASS


#endif
