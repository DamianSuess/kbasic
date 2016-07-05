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



#ifndef _COMBOBOX_H
#define _COMBOBOX_H

#include <QComboBox>

#include "typedef.h"


#include <QSvgWidget>
#include <QSvgRenderer>

#include "_property.h"
#include "_control0.h"


#ifdef IDE
extern QString sInsertTypeOption;
#endif

#ifdef RUN
#include <QtSql>
#endif

#define TEST _combobox    
#define TEST2 _comboboxes  
#define TEST3 "ComboBox"
#define SUPERCLASS QComboBox   

#define _COMBOBOX true

class _form;

class _combobox : public QComboBox, public _property
{
  Q_OBJECT
public:



_combobox(_form *f = 0, QWidget *parent = 0) : QComboBox (parent ? parent : (QWidget *) f)
{
  constructor(f, parent);

  // properties

  addProperty("StringValue", pt_qstring); addProperty("OldStringValue", pt_qstring);
  addProperty("Flat", pt_boolean);
  addProperty("SQL", pt_qstring);

  addProperty("DoubleEntry", pt_boolean);
  addProperty("Editable", pt_boolean);
  addProperty("InsertPolicy", pt_qstring);
  addProperty("IntegerMaximum", pt_integer);
  addProperty("MaximumVisible", pt_integer);

  // events
  addProperty("OnEvent", pt_event);

  // default values
  SETPROPERTY_ControlType("ComboBox");
  SETPROPERTY_Visible(true);
  SETPROPERTY_Enabled(true);

  SETPROPERTY_CSV("ComboBox;1st Entry;2nd Entry;3rd Entry");

#ifdef IDE
  if (sInsertTypeOption.contains("Editable", Qt::CaseInsensitive)){
    SETPROPERTY_Editable(true);
  } else {
    SETPROPERTY_Editable(false);
  }
#endif

  // misc.
  

  connect(this, SIGNAL(activated(int)), this, SLOT(EVENT_2Event(int)));
  connect(this, SIGNAL(currentIndexChanged(int)), this, SLOT(EVENT_OnSQLEvent()));
  
}

#include "__property_x.h"
#include "__property_y.h"
#include "__property_flat.h"
#include "__property_stringvalue.h"

#include "__property_completer.h"
#include "__property_doubleentry.h"
#include "__property_insertpolicy.h"
#include "__property_editable.h"
#include "__property_integermaximum.h"
#include "__property_maximumvisible.h"


// KBBINDINGEVENTS
public slots:

virtual void EVENT_2Event(int Index)
{
  EVENT_OnEvent(Index + 1, METHOD_Caption(Index + 1));
}

virtual void EVENT_OnEvent(int Index, const QString & Caption)
{
}

void EVENT_OnSQLEvent();

// KBBINDINGMETHODS

public:

  

t_integer METHOD_Len()
{
  return count();
}

t_integer METHOD_Find(const QString & s)
{
  return findText(s) + 1;
}

void METHOD_HidePopUp()
{
  hidePopup();
}

void METHOD_ShowPopUp()
{
  showPopup();
}

void METHOD_InsertSeparator(t_integer Index)
{
  if (Index - 1 < 0 || Index - 1 >= count()) return;
  insertSeparator(Index - 1);
}

void METHOD_Insert(t_integer Index, const QString & Caption)
{
  if (Index - 1 < 0 || Index - 1 >= count()) return;
  insertItem(Index - 1, Caption);
}

void METHOD_Insert(t_integer Index, const QString & Icon, const QString & Caption)
{
  if (Index - 1 < 0 || Index - 1 >= count()) return;

  QPixmap pi; 
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
        pi = p;
      }
    } else {
       pi.loadFromData(Icon.toLatin1());
    }
    
  } else {
    pi = loadPixmap(Icon);
  }

  insertItem(Index - 1, pi, Caption);
}

void METHOD_AppendSeparator()
{
  insertSeparator(count());
}

void METHOD_Append(const QString & Caption)
{
  addItem(Caption);
}

void METHOD_Append(QString Icon, const QString & Caption)
{
  QPixmap pi; 
  if (Icon.length() > 200){ // QString contains binary data

    if (Icon.left(200).contains("<svg ", Qt::CaseInsensitive)){
      Icon = Icon.trimmed();
      QSvgWidget w(0);
      w.resize(width(), height());
      QSvgRenderer *r = w.renderer();
      if (r->load(Icon.toLatin1())){
        QPixmap p(width(), height());
        QPainter painter(&p);
        r->render(&painter);
        pi = p;
      }
    } else {
       pi.loadFromData(Icon.toLatin1());
    }
    
  } else {
    pi = loadPixmap(Icon);
  }

  addItem(pi, Caption);
}

void METHOD_Remove(t_integer Index)
{
  if (Index - 1 < 0 || Index - 1 >= count()) return;
  removeItem(Index - 1);
}

void METHOD_RemoveAll()
{
  clear();
}

void METHOD_Select(t_integer Index)
{
  if (Index - 1 < 0 || Index - 1 >= count()) return;
  setCurrentIndex(Index - 1);
}

void METHOD_Select(const QString & s)
{
  int n = findText(s);
  if (n >= 0) setCurrentIndex(n); else setCurrentIndex(0);
}

t_integer METHOD_Selected()
{
  return currentIndex() + 1;
}

t_integer METHOD_Index()
{
  return currentIndex() + 1;
}

QString METHOD_Caption()
{
  int n = currentIndex();
  if (n >= 0) return itemText(n);
  return "";
}

t_integer METHOD_Data()
{
  int n = currentIndex();
  if (n >= 0) return itemData(n).toLongLong();
  return 0;
}

QString METHOD_Caption(t_integer Index)
{
  if (Index - 1 < 0 || Index - 1 >= count()) return "";
  return itemText(Index - 1);
}

void METHOD_SetCaption(t_integer Index, const QString & Caption)
{
  if (Index - 1 < 0 || Index - 1 >= count()) return;
  setItemText(Index - 1, Caption);
}

void METHOD_SetIcon(t_integer Index, const QString & Icon)
{
  if (Index - 1 < 0 || Index - 1 >= count()) return;

  QPixmap pi; 
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
        pi = p;
      }
    } else {
       pi.loadFromData(Icon.toLatin1());
    }
    
  } else {
    pi = loadPixmap(Icon);
  }

  setItemIcon(Index - 1, pi);
}

QString METHOD_Tag(t_integer Index)
{
  if (Index - 1 < 0 || Index - 1 >= count()) return "";
  return itemData(Index - 1).toString();
}

void METHOD_SetTag(t_integer Index, const QString & Tag)
{
  if (Index - 1 < 0 || Index - 1 >= count()) return;
  setItemData(Index - 1, QVariant(Tag));
}


// ***
#include "_control1_binding.h"


// ***
#include "_control1.h"


};

#include "_control2.h"


#undef _COMBOBOX

#undef TEST
#undef TEST2
#undef TEST3
#undef SUPERCLASS



#endif