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


#ifndef _LISTBOX_H
#define _LISTBOX_H

#include <QCompleter>
#include <QListWidget>

#include "typedef.h"


#include <QSvgWidget>
#include <QSvgRenderer>

#ifdef IDE
extern QString sInsertTypeOption;
#endif

#include "_property.h"
#include "_control0.h"

#ifdef RUN
#include <QtSql>
#endif

#define TEST _listbox    
#define TEST2 _listboxes  
#define TEST3 "ListBox"
#define SUPERCLASS QListWidget   

#define _LISTBOX true

class _form;


#ifdef RUN

extern QMap<QString, QColor>colors_map;
#endif

class _listbox : public QListWidget, public _property
{
  Q_OBJECT
public:



_listbox(_form *f = 0, QWidget *parent = 0) : QListWidget (parent ? parent : (QWidget *) f)
{
  constructor(f, parent);

  // properties
  addProperty("StringValue", pt_qstring); addProperty("OldStringValue", pt_qstring);
  addProperty("Flat", pt_boolean);
  addProperty("SQL", pt_qstring);
  addProperty("Sorted", pt_boolean);
  addProperty("SelectionMode", pt_qstring);
  addProperty("AlternatingRowColors", pt_boolean);

  addProperty("ViewMode", pt_qstring);

  // events
  addProperty("OnEvent", pt_event);

  // default values
  SETPROPERTY_ControlType("ListBox");
  SETPROPERTY_Visible(true);
  SETPROPERTY_Enabled(true);
  SETPROPERTY_CSV("ListBox;1st Entry;2nd Entry;3rd Entry");
  
#ifdef IDE
  if (sInsertTypeOption.contains("IconMode", Qt::CaseInsensitive)){
    SETPROPERTY_ViewMode("IconMode");
  }
#endif

  // slots
  /*
  connect(this, SIGNAL( selected(int) ), this, SLOT( EVENT_Selected(int) ));
  connect(this, SIGNAL( selected(const QString &) ), this, SLOT( EVENT_2Selected(const QString &) ));
  connect(this, SIGNAL( highlighted(int) ), this, SLOT( EVENT_Highlighted(int) ));  
  connect(this, SIGNAL( highlighted(const QString &) ), this, SLOT( EVENT_2Highlighted(const QString &) ));
  connect(this, SIGNAL( selectionChanged() ), this, SLOT( EVENT_SelectionChanged() ));  
  connect(this, SIGNAL( selectionChanged(QListWidgetItem *) ), this, SLOT( EVENT_2SelectionChanged(QListWidgetItem *) ));  
  connect(this, SIGNAL( currentChanged(QListWidgetItem *) ), this, SLOT( EVENT_2CurrentChanged(QListWidgetItem *) ));  
  connect(this, SIGNAL( clicked(QListWidgetItem *) ), this, SLOT( EVENT_2Clicked(QListWidgetItem *) ));  
  connect(this, SIGNAL( pressed(QListWidgetItem *) ), this, SLOT( EVENT_2Pressed(QListWidgetItem *) ));  
  connect(this, SIGNAL( doubleClicked(QListWidgetItem *) ), this, SLOT( EVENT_2DoubleClicked(QListWidgetItem *) ));  
  connect(this, SIGNAL( returnPressed(QListWidgetItem *) ), this, SLOT( EVENT_2ReturnPressed(QListWidgetItem *) ));    
  connect(this, SIGNAL( contextMenuRequested(QListWidgetItem *, const QPoint & ) ), this, SLOT( EVENT_2ContextMenuRequested(QListWidgetItem *, const QPoint & ) ));  
  connect(this, SIGNAL( onItem(QListWidgetItem *) ), this, SLOT( EVENT_2OnItem(QListWidgetItem *) ));  
  connect(this, SIGNAL( onViewport() ), this, SLOT( EVENT_OnViewport() ));  
  */

  connect(this, SIGNAL(currentRowChanged(int)), this, SLOT(EVENT_2Event(int)));
  connect(this, SIGNAL(currentRowChanged(int)), this, SLOT(EVENT_OnSQLEvent()));

   

}


#include "__property_x.h"
#include "__property_y.h"
#include "__property_flat.h"
#include "__property_stringvalue.h"
//#include "__property_sql.h"
#include "__property_sorted.h"
#include "__property_selectionmode.h"
#include "__property_alternatingrowcolors.h"
#include "__property_viewmode.h"






// KBBINDINGEVENTS
public slots:

virtual void EVENT_2Event(int Index)
{
  QListWidgetItem *it = item(Index);
  if (it) EVENT_OnEvent(Index + 1, it->text());
}

virtual void EVENT_OnEvent(int Index, const QString & Caption)
{
}

void EVENT_OnSQLEvent();

// KBBINDINGMETHODS

public:


void METHOD_SetForm(t_integer Index, _form *Form);

int METHOD_Len()
{
  return count();
}

void METHOD_Insert(t_integer Index, const QString & Caption)
{
  if (Index - 1 < 0 || Index - 1 >= count()) return;
  insertItem(Index - 1, new QListWidgetItem(Caption));
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

  insertItem(Index - 1, new QListWidgetItem(pi, Caption));
}

void METHOD_Append(const QString & Caption)
{
  addItem(new QListWidgetItem(Caption));
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

  addItem(new QListWidgetItem(pi, Caption));
}

void METHOD_Remove(t_integer Index)
{
  if (Index - 1 < 0 || Index - 1 >= count()) return;
  QListWidgetItem *l = takeItem(Index - 1);
  if (l) delete l;  
}

void METHOD_RemoveAll()
{
  clear();
}

void METHOD_Select(t_integer Index)
{
  if (Index - 1 < 0 || Index - 1 >= count()) return;
  setCurrentRow(Index - 1);
}

void METHOD_Select(const QString & s)
{  
  QList<QListWidgetItem *>l = findItems (s, Qt::MatchExactly);

  if (l.count()) setCurrentItem (l.at(0)); else setCurrentRow(0);
}

t_integer METHOD_Selected()
{
  return currentRow() + 1;
}

t_integer METHOD_Index()
{
  return currentRow() + 1;
}

QString METHOD_Caption()
{
  QListWidgetItem *it = currentItem();
  if (it) return it->text();
  return "";
}

t_integer METHOD_Data()
{
  QListWidgetItem *it = currentItem();
  if (it) return it->data(Qt::UserRole).toLongLong();
  return 0;
}

QString METHOD_Caption(t_integer Index)
{
  if (Index - 1 < 0 || Index - 1 >= count()) return "";
  QListWidgetItem *l = item(Index - 1);
  return l ? l->text() : "";
}

void METHOD_SetCaption(t_integer Index, const QString & Caption)
{
  if (Index - 1 < 0 || Index - 1 >= count()) return;
  QListWidgetItem *l = item(Index - 1);
  if (l) l->setText(Caption);
}

void METHOD_SetIcon(t_integer Index, const QString & Icon)
{
  if (Index - 1 < 0 || Index - 1 >= count()) return;
  QListWidgetItem *l = item(Index - 1);

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

  if (l) l->setIcon(pi);
}

QString METHOD_Tag(t_integer Index)
{
  if (Index - 1 < 0 || Index - 1 >= count()) return  ""; 
  QListWidgetItem *l = item(Index - 1);
  return l ? l->data(Qt::UserRole).toString() : "";
}

void METHOD_SetTag(t_integer Index, const QString & Tag)
{
  if (Index - 1 < 0 || Index - 1 >= count()) return;
  QListWidgetItem *l = item(Index - 1);
  if (l) l->setData(Qt::UserRole, QVariant(Tag));
}

void METHOD_Sort(t_boolean Descending)
{
  sortItems(Descending ? Qt::DescendingOrder : Qt::AscendingOrder);
}


QString METHOD_CheckState(t_integer Index)
{
  if (Index - 1 < 0 || Index - 1 >= count()) return  "";
  QListWidgetItem *l = item(Index - 1);
  Qt::CheckState t = l->checkState();

  QString i = "";

  if (t & Qt::Unchecked) i = "Unchecked";
  else if (t & Qt::PartiallyChecked) i = "PartiallyChecked";
  else if (t & Qt::Checked) i = "Checked";

  return i;
}

void METHOD_SetCheckState(t_integer Index, const QString & CheckState)
{
  if (Index - 1 < 0 || Index - 1 >= count()) return;
  QListWidgetItem *l = item(Index - 1);
  int i = 0;

  if (CheckState.contains("Unchecked")) i |= Qt::Unchecked;
  else if (CheckState.contains("PartiallyChecked")) i |= Qt::PartiallyChecked;
  else if (CheckState.contains("Checked")) i |= Qt::Checked;

  l->setCheckState((Qt::CheckState) i);
}

QString METHOD_Flag(t_integer Index)
{
  if (Index - 1 < 0 || Index - 1 >= count()) return "";
  QListWidgetItem *l = item(Index - 1);
  Qt::ItemFlags t = l->flags();

  QString i = "";

  if (t & Qt::ItemIsSelectable){ if (!i.isEmpty()) i += ";"; i += "ItemIsSelectable"; } 
  if (t & Qt::ItemIsEditable){ if (!i.isEmpty()) i += ";"; i += "ItemIsEditable"; }
  if (t & Qt::ItemIsDragEnabled){ if (!i.isEmpty()) i += ";"; i += "ItemIsDragEnabled"; }
  if (t & Qt::ItemIsDropEnabled){ if (!i.isEmpty()) i += ";"; i += "ItemIsDropEnabled"; }
  if (t & Qt::ItemIsUserCheckable){ if (!i.isEmpty()) i += ";"; i += "ItemIsUserCheckable"; }
  if (t & Qt::ItemIsEnabled){ if (!i.isEmpty()) i += ";"; i += "ItemIsEnabled"; }
  if (t & Qt::ItemIsTristate){ if (!i.isEmpty()) i += ";"; i += "ItemIsTristate"; }

  return i;
}

void METHOD_SetFlag(t_integer Index, const QString & Flag)
{
  if (Index - 1 < 0 || Index - 1 >= count()) return;
  QListWidgetItem *l = item(Index - 1);
  int i = 0;

  if (Flag.contains("ItemIsSelectable")) i |= Qt::ItemIsSelectable;
  if (Flag.contains("ItemIsEditable")) i |= Qt::ItemIsEditable;
  if (Flag.contains("ItemIsDragEnabled")) i |= Qt::ItemIsDragEnabled;
  if (Flag.contains("ItemIsDropEnabled")) i |= Qt::ItemIsDropEnabled;
  if (Flag.contains("ItemIsUserCheckable")) i |= Qt::ItemIsUserCheckable;
  if (Flag.contains("ItemIsEnabled")) i |= Qt::ItemIsEnabled;
  if (Flag.contains("ItemIsTristate")) i |= Qt::ItemIsTristate;

  l->setFlags((Qt::ItemFlags) i);
}

void METHOD_SetBackground(t_integer Index, const QString & ColorId)
{
  if (Index - 1 < 0 || Index - 1 >= count()) return;
  QListWidgetItem *l = item(Index - 1);
#ifdef RUN
  l->setBackground(QBrush(colors_map[ColorId]));
#endif
}

void METHOD_SetBackground(t_integer Index, const QString & ColorId, const QString & BrushStyle)
{
  if (Index - 1 < 0 || Index - 1 >= count()) return;
  QListWidgetItem *l = item(Index - 1);

  int i = 0;

  if (BrushStyle.contains("NoBrush")) i |= Qt::NoBrush;
  else if (BrushStyle.contains("SolidPattern")) i |= Qt::SolidPattern;
  else if (BrushStyle.contains("Dense1Pattern")) i |= Qt::Dense1Pattern;
  else if (BrushStyle.contains("Dense2Pattern")) i |= Qt::Dense2Pattern;
  else if (BrushStyle.contains("Dense3Pattern")) i |= Qt::Dense3Pattern;
  else if (BrushStyle.contains("Dense4Pattern")) i |= Qt::Dense4Pattern;
  else if (BrushStyle.contains("Dense5Pattern")) i |= Qt::Dense5Pattern;
  else if (BrushStyle.contains("Dense6Pattern")) i |= Qt::Dense6Pattern;
  else if (BrushStyle.contains("Dense7Pattern")) i |= Qt::Dense7Pattern;
  else if (BrushStyle.contains("HorPattern")) i |= Qt::HorPattern;
  else if (BrushStyle.contains("VerPattern")) i |= Qt::VerPattern;
  else if (BrushStyle.contains("CrossPattern")) i |= Qt::CrossPattern;
  else if (BrushStyle.contains("BDiagPattern")) i |= Qt::BDiagPattern;
  else if (BrushStyle.contains("FDiagPattern")) i |= Qt::FDiagPattern;
  else if (BrushStyle.contains("DiagCrossPattern")) i |= Qt::DiagCrossPattern;
  else if (BrushStyle.contains("LinearGradientPattern")) i |= Qt::LinearGradientPattern;
  else if (BrushStyle.contains("ConicalGradientPattern")) i |= Qt::ConicalGradientPattern;
  else if (BrushStyle.contains("RadialGradientPattern")) i |= Qt::RadialGradientPattern;
  else if (BrushStyle.contains("TexturePattern")) i |= Qt::TexturePattern;

#ifdef RUN
  l->setBackground(QBrush(colors_map[ColorId], (Qt::BrushStyle) i));
#endif
}


t_boolean METHOD_IsHidden(t_integer Index)
{
  if (Index - 1 < 0 || Index - 1 >= count()) return false;
  QListWidgetItem *l = item(Index - 1);
  return l->isHidden();
}

void METHOD_SetHidden(t_integer Index, t_boolean IsHidden)
{
  if (Index - 1 < 0 || Index - 1 >= count()) return;
  QListWidgetItem *l = item(Index - 1);
  l->setHidden(IsHidden);
}

t_boolean METHOD_IsSelected(t_integer Index)
{
  if (Index - 1 < 0 || Index - 1 >= count()) return false;
  QListWidgetItem *l = item(Index - 1);
  return l->isSelected();
}

void METHOD_SetSelected(t_integer Index, t_boolean IsSelected)
{
  if (Index - 1 < 0 || Index - 1 >= count()) return;
  QListWidgetItem *l = item(Index - 1);
  l->setSelected(IsSelected);
}

QString METHOD_StatusTip(t_integer Index)
{
  if (Index - 1 < 0 || Index - 1 >= count()) return "";
  QListWidgetItem *l = item(Index - 1);
  return l->statusTip();
}

void METHOD_SetStatusTip(t_integer Index, const QString & StatusTip)
{
  if (Index - 1 < 0 || Index - 1 >= count()) return;
  QListWidgetItem *l = item(Index - 1);
  l->setStatusTip(StatusTip);
}

QString METHOD_ToolTip(t_integer Index)
{
  if (Index - 1 < 0 || Index - 1 >= count()) return "";
  QListWidgetItem *l = item(Index - 1);
  return l->toolTip();
}

void METHOD_SetToolTip(t_integer Index, const QString & ToolTip)
{
  if (Index - 1 < 0 || Index - 1 >= count()) return;
  QListWidgetItem *l = item(Index - 1);
  l->setToolTip(ToolTip);
}

QString METHOD_TextAlignment(t_integer Index)
{
  if (Index - 1 < 0 || Index - 1 >= count()) return "";
  QListWidgetItem *l = item(Index - 1);
  Qt::AlignmentFlag t = (Qt::AlignmentFlag) l->textAlignment();

  QString i = "";

  if (t & Qt::AlignLeft){ if (!i.isEmpty()) i += ";"; i += "AlignLeft"; } 
  if (t & Qt::AlignRight){ if (!i.isEmpty()) i += ";"; i += "AlignLeft"; } 
  if (t & Qt::AlignHCenter){ if (!i.isEmpty()) i += ";"; i += "AlignLeft"; } 
  if (t & Qt::AlignJustify){ if (!i.isEmpty()) i += ";"; i += "AlignLeft"; } 
  if (t & Qt::AlignTop){ if (!i.isEmpty()) i += ";"; i += "AlignLeft"; } 
  if (t & Qt::AlignBottom){ if (!i.isEmpty()) i += ";"; i += "AlignLeft"; } 
  if (t & Qt::AlignVCenter){ if (!i.isEmpty()) i += ";"; i += "AlignLeft"; } 
  if (t & Qt::AlignCenter){ if (!i.isEmpty()) i += ";"; i += "AlignLeft"; } 
  if (t & Qt::AlignAbsolute){ if (!i.isEmpty()) i += ";"; i += "AlignLeft"; } 
  if (t & Qt::AlignLeading){ if (!i.isEmpty()) i += ";"; i += "AlignLeft"; } 
  if (t & Qt::AlignTrailing){ if (!i.isEmpty()) i += ";"; i += "AlignLeft"; } 
  if (t & Qt::AlignHorizontal_Mask){ if (!i.isEmpty()) i += ";"; i += "AlignLeft"; } 
  if (t & Qt::AlignVertical_Mask){ if (!i.isEmpty()) i += ";"; i += "AlignLeft"; } 

  return i;
}

void METHOD_SetTextAlignment(t_integer Index, const QString & TextAlignment)
{
  if (Index - 1 < 0 || Index - 1 >= count()) return;
  QListWidgetItem *l = item(Index - 1);
  int i = 0;

  if (TextAlignment == "AlignLeft") i |= Qt::AlignLeft;
  if (TextAlignment == "AlignRight") i |= Qt::AlignRight;
  if (TextAlignment == "AlignHCenter") i |= Qt::AlignHCenter;
  if (TextAlignment == "AlignJustify") i |= Qt::AlignJustify;
  if (TextAlignment == "AlignTop") i |= Qt::AlignTop;
  if (TextAlignment == "AlignBottom") i |= Qt::AlignBottom;
  if (TextAlignment == "AlignVCenter") i |= Qt::AlignVCenter;
  if (TextAlignment == "AlignCenter") i |= Qt::AlignCenter;
  if (TextAlignment == "AlignAbsolute") i |= Qt::AlignAbsolute;
  if (TextAlignment == "AlignLeading") i |= Qt::AlignLeading;
  if (TextAlignment == "AlignTrailing") i |= Qt::AlignTrailing;
  if (TextAlignment == "AlignHorizontal_Mask") i |= Qt::AlignHorizontal_Mask;
  if (TextAlignment == "AlignVertical_Mask") i |= Qt::AlignVertical_Mask;

  l->setTextAlignment((Qt::AlignmentFlag) i);
}


// ***
  /*
virtual void EVENT_Selected(int index)
{
}

virtual void EVENT_2Selected(const QString &s)
{
  EVENT_Selected(s);
}

virtual void EVENT_Selected(const char *s)
{
}

virtual void EVENT_Highlighted(int index)
{
}

virtual void EVENT_2Highlighted(const QString &s)
{
  EVENT_Highlighted(s);
}

virtual void EVENT_Highlighted(const char *s)
{
}

virtual void EVENT_SelectionChanged()
{
}

virtual void EVENT_2SelectionChanged(QListWidgetItem *l)
{
  EVENT_SelectionChanged(index(l));
}

virtual void EVENT_SelectionChanged(int index)
{
}

virtual void EVENT_2CurrentChanged(QListWidgetItem *l)
{
  EVENT_CurrentChanged(index(l));
}

virtual void EVENT_CurrentChanged(int index)
{
}

virtual void EVENT_2Clicked(QListWidgetItem *l)
{
  EVENT_Clicked(index(l));
}

virtual void EVENT_Clicked(int index)
{
}

virtual void EVENT_2Pressed(QListWidgetItem *l)
{
  EVENT_Pressed(index(l));
}

virtual void EVENT_Pressed(int index)
{
}

virtual void EVENT_2DoubleClicked(QListWidgetItem *l)
{
  EVENT_DoubleClicked(index(l));
}

virtual void EVENT_DoubleClicked(int index)
{
}

virtual void EVENT_2ReturnPressed(QListWidgetItem *l)
{
  EVENT_ReturnPressed(index(l));
}

virtual void EVENT_ReturnPressed(int index)
{
}

virtual void EVENT_2ContextMenuRequested(QListWidgetItem *l, const QPoint & pos )
{
  EVENT_ContextMenuRequested(index(l), pos.x(), pos.y());
}

virtual void EVENT_ContextMenuRequested(int index, int x, int y)
{
}

virtual void EVENT_2OnItem(QListWidgetItem *l)
{
  EVENT_OnItem(index(l));
}

virtual void EVENT_OnItem(int index)
{
}

virtual void EVENT_OnViewport()
{
}

*/
// ***



public:
/*
// METHOD ***
int METHOD_Count()
{
  return count();
}

void METHOD_InsertItem(const char *t, int index = -1 )
{
  insertItem(t, index);
}

void METHOD_InsertItem(const char *image, const char *t, int index = -1 )
{
  insertItem(createPixmap(image), t, index);    
}

void METHOD_RemoveItem(int index)
{
  removeItem(index);
}

const char *METHOD_Text(int index)
{
  const char *s = text(index).latin1();
  if (s == 0) return "";
  return s;
}

void METHOD_ChangeText(const char *s, int index)
{
  const QPixmap *p = pixmap(index);
  if (p) changeItem((const QPixmap &) p, s, index);
  else changeItem(s, index);
}

void METHOD_ChangeImage(const char *image, int index)
{
  changeItem(createPixmap(image), text(index), index);
}

int METHOD_CurrentItem()
{
  return currentItem();
}

int METHOD_Current(int index)
{
  QListWidgetItem *li = item (index);
  if (li) return li->isCurrent();
  return -1;
}

void METHOD_SetCurrentItem(int index)
{
  setCurrentItem(index);
}

int METHOD_SelectedItem()
{
  return currentItem();
}

int METHOD_Selected(int index)
{
  QListWidgetItem *li = item (index);
  if (li) return li->isSelected();
  return -1;
}

void METHOD_SetSelectedItem(int index, bool b)
{
  setSelected(index, b);
}

int METHOD_FindItem(const char *text, bool b)
{
  QListWidgetItem *li = findItem (text, b ? Qt::CaseSensitive | Qt::Contains : Qt::Contains);
  for (int i = 0; i < count(); i++){
    if (item(i) == li) return i;
  }

  return -1;
}

bool METHOD_ItemVisible(int index)
{
  return itemVisible (index);
}

void METHOD_Clear()
{
  clear();
}

void METHOD_Sort(bool b)
{
  sort(b);
}

void METHOD_EnsureCurrentVisible()
{
  ensureCurrentVisible();
}

void METHOD_ClearSelection ()
{
  clearSelection();
}

void METHOD_SelectAll(bool b)
{
  selectAll(b);
}

void METHOD_InvertSelection()
{
  invertSelection();
}
*/
// ***


// ***
#include "_control1_binding.h"


// ***
#include "_control1.h"


};

#include "_control2.h"

#undef _LISTBOX

#undef TEST
#undef TEST2
#undef TEST3
#undef SUPERCLASS


#endif