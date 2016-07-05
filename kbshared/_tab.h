
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

#ifndef _TAB_H
#define _TAB_H


/*
qt 4.5
documentMode : bool     auch für mdi anbieten

void tabCloseRequested ( int index )

movable : bool

tabsClosable : bool



*/


#include <qtabbar.h>

#include <QSvgWidget>
#include <QSvgRenderer>

#include "typedef.h"

#include "_property.h"
#include "_control0.h"

#define TEST _tab    
#define TEST2 _tabs   
#define TEST3 "TabView"

#ifdef IDE
#define SUPERCLASS QWidget
#else
#define SUPERCLASS QTabWidget   
#endif

#define _TAB true

class _form;
class _tab;




#ifdef IDE
class _tab : public QWidget, public _property
#else
class _tab : public QTabWidget, public _property
#endif
{
  Q_OBJECT
public:


#ifdef IDE
_tab(_form *f = 0, QWidget *parent = 0) : QWidget (parent ? parent : (QWidget *) f)
{
  tb = new QTabBar(this);
#else
_tab(_form *f = 0, QWidget *parent = 0) : QTabWidget (parent ? parent : (QWidget *) f)
{
  tb = this;

#endif

  

#ifdef IDE
  setAutoFillBackground(true);
  QPalette p = palette();
  p.setColor(QPalette::Window, Qt::gray);  
  setPalette(p);
#endif

  constructor(f, parent);

  // properties
  addProperty("Pages", pt_qstring);

  // events
  addProperty("OnEvent", pt_event);

  // default values
  SETPROPERTY_ControlType("TabView");
  SETPROPERTY_Visible(true);

  // slots
  connect(tb, SIGNAL(currentChanged(int)), this, SLOT(EVENT_OnEvent2(int)));
  connect(tb, SIGNAL(currentChanged(int)), this, SLOT(EVENT_OnEvent3(int)));

}

// properties
#include "__property_x.h"
#include "__property_y.h"
#include "__property_pages.h"


// KBBINDINGEVENTS

// *** bindings
// *** 


public slots:

void EVENT_OnEvent2(int Index);

void EVENT_OnEvent3(int Index)
{
  EVENT_OnEvent(Index + 1);
}

virtual void EVENT_OnEvent(int Index);

public:



int METHOD_AppendTab(const QString & Icon, const QString & Caption);



int METHOD_InsertTab(int Index, const QString & Icon, const QString & Caption);


void METHOD_RemoveTab(int Index)
{  

  if (Index - 1 < 0 || Index - 1 > tb->count()) return;
  tb->removeTab(Index - 1);
  tb->repaint();
}

int METHOD_Len()
{
  return tb->count();
}

///

void METHOD_SetTabEnabled(int Index, bool Enabled = true)
{
  if (Index - 1 < 0 || Index - 1 > tb->count()) return;
  tb->setTabEnabled(Index - 1, Enabled);
}

bool METHOD_IsTabEnabled(int Index)
{
  if (Index - 1 < 0 || Index - 1 > tb->count()) return false;
  return tb->isTabEnabled(Index - 1);
}

void METHOD_Select (int Index)
{
  if (Index - 1 < 0 || Index - 1 > tb->count()) return;
  tb->setCurrentIndex(Index - 1);
}

int METHOD_Selected()
{
  return tb->currentIndex() + 1;
}

void METHOD_SetToolTip(int Index, const QString & s)
{
  if (Index - 1 < 0 || Index - 1 > tb->count()) return;
  tb->setTabToolTip(Index - 1, s);
}

QString METHOD_ToolTip(int Index)
{
  if (Index - 1 < 0 || Index - 1 > tb->count()) return "";
  return tb->tabToolTip(Index - 1);
}

void METHOD_SetWhatsThis(int Index, const QString & s)
{
  if (Index - 1 < 0 || Index - 1 > tb->count()) return;
  tb->setTabWhatsThis(Index - 1, s);
}

QString METHOD_WhatsThis(int Index)
{
  if (Index - 1 < 0 || Index - 1 > tb->count()) return "";
  return tb->tabWhatsThis(Index - 1);
}

void METHOD_SetCaption(int Index, const QString & Caption)
{
  if (Index - 1 < 0 || Index - 1 > tb->count()) return;
  tb->setTabText(Index - 1, Caption);
}

QString METHOD_Caption(int Index)
{  
  if (Index - 1 < 0 || Index - 1 > tb->count()) return "";
  return tb->tabText(Index - 1);
}

void METHOD_SetIcon(int Index, const QString & Icon)
{  
  if (Index - 1 < 0 || Index - 1 > tb->count()) return;

  if (Icon.length() > 200){ // QString contains binary data
    if (Icon.left(200).contains("<svg ", Qt::CaseInsensitive)){
      QString m = Icon;
      m = m.trimmed();
      QSvgWidget w(0);
      w.resize(width(), height());
      QSvgRenderer *r = w.renderer();
      if (r->load(m.toLatin1())){
        QPixmap p(width(), height());
        QPainter painter(&p);
        r->render(&painter);
        tb->setTabIcon(Index - 1, p);
      }
    } else {
       QPixmap p; p.loadFromData(Icon.toLatin1());
       tb->setTabIcon(Index - 1, p);
    }
  } else {  
    tb->setTabIcon(Index - 1, loadPixmap(Icon));
  }
}



// ***
#include "_control1_binding.h"


// ***
#include "_control1.h"

public:
#ifdef IDE
  QTabBar *tb;
#else
  QTabWidget *tb;
#endif

private:


};

#include "_control2.h"

#undef _TAB

#undef TEST
#undef TEST2
#undef TEST3
#undef SUPERCLASS

#endif




