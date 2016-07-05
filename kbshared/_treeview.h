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

#ifndef _TREEVIEW_H
#define _TREEVIEW_H


#include <QMap>
#include <QTreeWidget>


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


#include "_sounds.h"
extern _sounds2 *EXTERN_my_sounds;
#endif

#define TEST _treeview    
#define TEST2 _treeviews 
#define TEST3 "TreeView"
#define SUPERCLASS QTreeWidget   

#define _TREEVIEW true

class _form;

#ifdef RUN

extern QMap<QString, QColor>colors_map;
extern QMap<QString, QFont>fonts_map;

extern void fillWithSQLForTreeView(QTreeWidget *tree, QTreeWidgetItem *parent, QString & sTable, QString & sSQL, QStringList & groups, QStringList & values, int nCurrent);

#endif


class _treeview : public QTreeWidget, public _property
{
  Q_OBJECT
public:



_treeview(_form *f = 0, QWidget *parent = 0) : QTreeWidget (parent ? parent : (QWidget *) f)
{
  constructor(f, parent);

#ifdef IDE
  setHeaderLabel("HeaderItem");
#else
  headerItem()->setHidden(true);
#endif

  // properties
  addProperty("SelectionMode", pt_qstring);
  addProperty("AlternatingRowColors", pt_boolean);
  addProperty("RootIsDecorated", pt_boolean);
  addProperty("Flat", pt_boolean);
  addProperty("SQL", pt_qstring);

  // events
  addProperty("OnEvent", pt_event);

  addProperty("CurrentItemChanged", pt_event);
  addProperty("ItemActivated", pt_event);
  addProperty("ItemChanged", pt_event);
  addProperty("ItemClicked", pt_event);
  addProperty("ItemCollapsed", pt_event);
  addProperty("ItemDoubleClicked", pt_event);
  addProperty("ItemEntered", pt_event);
  addProperty("ItemExpanded", pt_event);
  addProperty("ItemPressed", pt_event);
  addProperty("ItemSelectionChanged", pt_event);

  // default values
  SETPROPERTY_ControlType("TreeView");
  SETPROPERTY_Visible(true);
  SETPROPERTY_Enabled(true);
  
#ifdef IDE
  if (sInsertTypeOption.contains("ListView", Qt::CaseInsensitive)){
    SETPROPERTY_RootIsDecorated(false);
  } else {
    SETPROPERTY_RootIsDecorated(true);
  }
#else
  SETPROPERTY_RootIsDecorated(true);
#endif



  connect(this, SIGNAL(currentItemChanged(QTreeWidgetItem *, QTreeWidgetItem *)), this, SLOT(currentItemChanged(QTreeWidgetItem *, QTreeWidgetItem *)));
  connect(this, SIGNAL(itemActivated(QTreeWidgetItem *, int)), this, SLOT(itemActivated(QTreeWidgetItem *, int)));
  connect(this, SIGNAL(itemChanged(QTreeWidgetItem *, int)), this, SLOT(itemChanged(QTreeWidgetItem *, int)));
  connect(this, SIGNAL(itemClicked(QTreeWidgetItem *, int)), this, SLOT(itemClicked(QTreeWidgetItem *, int)));
  connect(this, SIGNAL(itemCollapsed(QTreeWidgetItem *)), this, SLOT(itemCollapsed(QTreeWidgetItem *)));
  connect(this, SIGNAL(itemDoubleClicked(QTreeWidgetItem *, int)), this, SLOT(itemDoubleClicked(QTreeWidgetItem *, int)));
  connect(this, SIGNAL(itemEntered(QTreeWidgetItem *, int)), this, SLOT(itemEntered(QTreeWidgetItem *, int)));
  connect(this, SIGNAL(itemExpanded(QTreeWidgetItem *)), this, SLOT(itemExpanded(QTreeWidgetItem *)));
  connect(this, SIGNAL(itemPressed(QTreeWidgetItem *, int)), this, SLOT(itemPressed(QTreeWidgetItem *, int)));
  connect(this, SIGNAL(itemSelectionChanged()), this, SLOT(itemSelectionChanged()));  
  connect(this, SIGNAL(currentItemChanged(QTreeWidgetItem *, QTreeWidgetItem *)), this, SLOT(SoundOnEvent()));
  connect(this, SIGNAL(currentItemChanged(QTreeWidgetItem *, QTreeWidgetItem *)), this, SLOT(EVENT_OnEvent()));
}

public slots:

  
void SoundOnEvent()
{
#ifdef RUN
  QString s = GETPROPERTY_SoundOnEvent();
  if (!s.isEmpty()){
    EXTERN_my_sounds->playOnce(s);
  }
#endif
}

virtual void EVENT_OnEvent()
{
}

void currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
  EVENT_CurrentItemChanged((t_integer) current, (t_integer) previous);
}

void itemActivated(QTreeWidgetItem *item, int Column) // must be int snd not t_integer cause Qt signal/slot code
{
  EVENT_ItemActivated((t_integer) item, Column);
}

void itemChanged(QTreeWidgetItem *item, int Column) // must be int snd not t_integer cause Qt signal/slot code
{
  EVENT_ItemChanged((t_integer) item, Column);
}

void itemClicked(QTreeWidgetItem *item, int Column) // must be int snd not t_integer cause Qt signal/slot code
{
  EVENT_ItemClicked((t_integer) item, Column);
}

void itemCollapsed(QTreeWidgetItem *item)
{
  EVENT_ItemCollapsed((t_integer) item);
}

void itemDoubleClicked(QTreeWidgetItem *item, int Column) // must be int snd not t_integer cause Qt signal/slot code
{
  EVENT_ItemDoubleClicked((t_integer) item, Column);
}
  
void itemEntered(QTreeWidgetItem *item, int Column) // must be int snd not t_integer cause Qt signal/slot code
{
  EVENT_ItemEntered((t_integer) item, Column);
}
  
void itemExpanded(QTreeWidgetItem *item)
{
  EVENT_ItemExpanded((t_integer) item);
}

void itemPressed(QTreeWidgetItem *item, int Column) // must be int snd not t_integer cause Qt signal/slot code
{
  EVENT_ItemPressed((t_integer) item, Column);
}

void itemSelectionChanged()
{
  EVENT_ItemSelectionChanged();
}

public:
#include "__property_x.h"
#include "__property_y.h"
#include "__property_flat.h"
#include "__property_selectionmode.h"
#include "__property_alternatingrowcolors.h"
#include "__property_rootisdecorated.h"




t_integer METHOD_AppendChild(const QString & Caption);

t_integer METHOD_AppendChild(const QString & Icon, const QString & Caption)
{
  QTreeWidgetItem *l = new QTreeWidgetItem(this);
  l->setText(0, Caption);

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

  l->setIcon(0, pi);
  return (t_integer) l;
}

t_integer METHOD_AppendChild(t_integer Id, const QString & Caption)
{
  QTreeWidgetItem *ll = ((QTreeWidgetItem *) Id);
  if (ll){
    QTreeWidgetItem *l = new QTreeWidgetItem(ll);
    l->setText(0, Caption);
    return (t_integer) l;
  }
  return 0;
}

t_integer METHOD_AppendChild(t_integer Id, const QString & Icon, const QString & Caption)
{
  QTreeWidgetItem *ll = ((QTreeWidgetItem *) Id);
  if (ll){
    QTreeWidgetItem *l = new QTreeWidgetItem(ll);
    l->setText(0, Caption);

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

    l->setIcon(0, pi);
    return (t_integer) l;
  }
  return 0;
}

t_integer METHOD_ChildCount(t_integer Id)
{
  QTreeWidgetItem *l = (QTreeWidgetItem *) Id;
  if (l) return l->childCount();
  return -1;
}

t_integer METHOD_Child(t_integer Id, t_integer Index)
{
  QTreeWidgetItem *l = (QTreeWidgetItem *) Id;
  if (l) if (Index - 1 >= 0 && Index - 1 <= l->childCount()) return (t_integer) l->child(Index - 1);
  return -1;
}

QString METHOD_Tag(t_integer Id, t_integer Column)
{
  QTreeWidgetItem *l = (QTreeWidgetItem *) Id;
  if (l) return l->data(Column, Qt::UserRole).toString();
  return "";
}

void METHOD_SetTag(t_integer Id, t_integer Column, const QString & Tag)
{
  QTreeWidgetItem *l = (QTreeWidgetItem *) Id;
  if (l) l->setData(Column, Qt::UserRole, QVariant(Tag));
}

QString METHOD_CheckState(t_integer Id, t_integer Column)
{
  QTreeWidgetItem *l = (QTreeWidgetItem *) Id;
  if (l){
    Qt::CheckState t = l->checkState(Column);

    QString i = "";

    if (t & Qt::Unchecked) i = "Unchecked";
    else if (t & Qt::PartiallyChecked) i = "PartiallyChecked";
    else if (t & Qt::Checked) i = "Checked";

    return i;
  }
  return "";
}

void METHOD_SetCheckState(t_integer Id, t_integer Column, const QString & CheckState)
{
  QTreeWidgetItem *l = (QTreeWidgetItem *) Id;
  if (l){
    int i = 0;

    if (CheckState.contains("Unchecked")) i |= Qt::Unchecked;
    else if (CheckState.contains("PartiallyChecked")) i |= Qt::PartiallyChecked;
    else if (CheckState.contains("Checked")) i |= Qt::Checked;

    l->setCheckState(Column, (Qt::CheckState) i);
  }
}

QString METHOD_Data(t_integer Id)
{
  QTreeWidgetItem *l = (QTreeWidgetItem *) Id;
  if (l){
    QVariant v= l->data(0, Qt::UserRole);

    return v.toString();
  }
  return "";
}

QString METHOD_Flag(t_integer Id)
{
  QTreeWidgetItem *l = (QTreeWidgetItem *) Id;
  if (l){
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
  return "";
}

void METHOD_SetFlag(t_integer Id, const QString & Flag)
{
  QTreeWidgetItem *l = (QTreeWidgetItem *) Id;
  if (l){
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
}

void METHOD_SetBackground(t_integer Id, int Column, const QString & ColorId)
{
  QTreeWidgetItem *l = (QTreeWidgetItem *) Id;
  if (l){
#ifdef RUN
    l->setBackground(Column, QBrush(colors_map[ColorId]));
#endif
  }
}

void METHOD_SetBackground(t_integer Id, int Column, const QString & ColorId, const QString & BrushStyle)
{
  QTreeWidgetItem *l = (QTreeWidgetItem *) Id;
  if (l){

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
    l->setBackground(Column, QBrush(colors_map[ColorId], (Qt::BrushStyle) i));
#endif
  }
}

void METHOD_SetFontColor(t_integer Id, int Column, const QString & ColorId)
{
  QTreeWidgetItem *l = (QTreeWidgetItem *) Id;
  if (l){
#ifdef RUN
    l->setForeground(Column, QBrush(colors_map[ColorId]));
#endif
  }
}

void METHOD_SetFontColor(t_integer Id, int Column, const QString & ColorId, const QString & BrushStyle)
{
  QTreeWidgetItem *l = (QTreeWidgetItem *) Id;
  if (l){

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
    l->setForeground(Column, QBrush(colors_map[ColorId], (Qt::BrushStyle) i));
#endif
  }
}

void METHOD_SetFont(t_integer Id, t_integer Column, const QString & FontId)
{
  QTreeWidgetItem *l = (QTreeWidgetItem *) Id;
  if (l){
#ifdef RUN
    l->setFont(Column, fonts_map[FontId]);
#endif
  }
}

QString METHOD_Caption(t_integer Id, t_integer Column)
{
  QTreeWidgetItem *l = (QTreeWidgetItem *) Id;
  if (l) return l->text(Column);
  return "";
}

void METHOD_SetCaption(t_integer Id, t_integer Column, const QString & Caption)
{
  QTreeWidgetItem *l = (QTreeWidgetItem *) Id;
  if (l) l->setText(Column, Caption);
}

void METHOD_SetIcon(t_integer Id, t_integer Column, const QString & Icon)
{
  QTreeWidgetItem *l = (QTreeWidgetItem *) Id;

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

  if (l) l->setIcon(Column, pi);
}

t_integer METHOD_IndexOfChild(t_integer Id, t_integer ChildId)
{
  QTreeWidgetItem *l = (QTreeWidgetItem *) Id;
  if (l) return l->indexOfChild((QTreeWidgetItem *) ChildId) + 1;
  return -1;
}

t_integer METHOD_InsertChild(t_integer Id, t_integer Index, const QString & Caption)
{  
  QTreeWidgetItem *ll = ((QTreeWidgetItem *) Id);
  if (ll){
    if (Index - 1 >= 0 && Index - 1 <= ll->childCount()){
      QTreeWidgetItem *l = new QTreeWidgetItem(ll);
      if (l){
        l->setText(0, Caption);
        ll->insertChild(Index - 1, l);
        return (t_integer) l;
      }
    }
  }
  return 0;
}

t_integer METHOD_InsertChild(t_integer Id, t_integer Index, const QString & Icon, const QString & Caption)
{
  QTreeWidgetItem *ll = ((QTreeWidgetItem *) Id);
  if (ll){
    if (Index - 1 >= 0 && Index - 1 <= ll->childCount()){
      QTreeWidgetItem *l = new QTreeWidgetItem(ll);
      if (l){
        l->setText(0, Caption);

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
        l->setIcon(0, pi);
        ll->insertChild(Index - 1, l);
        return (t_integer) l;
      }
    }
  }
  return 0;
}

t_boolean METHOD_IsExpanded(t_integer Id)
{
  QTreeWidgetItem *l = (QTreeWidgetItem *) Id;
  return l->isExpanded();
}

void METHOD_SetExpanded(t_integer Id, t_boolean IsExpanded)
{
  QTreeWidgetItem *l = (QTreeWidgetItem *) Id;
  if (l) l->setExpanded(IsExpanded);
}

t_boolean METHOD_IsHidden(t_integer Id)
{
  QTreeWidgetItem *l = (QTreeWidgetItem *) Id;
  if (l) return l->isHidden();
  return false;
}

void METHOD_SetHidden(t_integer Id, t_boolean IsHidden)
{
  QTreeWidgetItem *l = (QTreeWidgetItem *) Id;
  if (l) l->setHidden(IsHidden);
}

t_boolean METHOD_IsSelected(t_integer Id)
{
  QTreeWidgetItem *l = (QTreeWidgetItem *) Id;
  if (l) return l->isSelected();
  return false;
}

void METHOD_SetSelected(t_integer Id, t_boolean IsSelected)
{
  QTreeWidgetItem *l = (QTreeWidgetItem *) Id;
  if (l) l->setSelected(IsSelected);
}

QString METHOD_StatusTip(t_integer Id, t_integer Column)
{
  QTreeWidgetItem *l = (QTreeWidgetItem *) Id;
  if (l) return l->statusTip(Column);
  return "";
}

void METHOD_SetStatusTip(t_integer Id, t_integer Column, const QString & StatusTip)
{
  QTreeWidgetItem *l = (QTreeWidgetItem *) Id;
  l->setStatusTip(Column, StatusTip);
}

QString METHOD_ToolTip(t_integer Id, t_integer Column)
{
  QTreeWidgetItem *l = (QTreeWidgetItem *) Id;
  if (l) return l->toolTip(Column);
  return "";
}

void METHOD_SetToolTip(t_integer Id, t_integer Column, const QString & ToolTip)
{
  QTreeWidgetItem *l = (QTreeWidgetItem *) Id;
  if (l) l->setToolTip(Column, ToolTip);
}

void METHOD_RemoveChild(t_integer Id, t_integer Index)
{
  QTreeWidgetItem *l = (QTreeWidgetItem *) Id;
  if (l) if (Index - 1 >= 0 && Index - 1 <= l->childCount()) l->takeChild(Index - 1);
}

QString METHOD_TextAlignment(t_integer Id, t_integer Column)
{
  QTreeWidgetItem *l = (QTreeWidgetItem *) Id;
  if (l){
    Qt::AlignmentFlag t = (Qt::AlignmentFlag) l->textAlignment(Column);

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
  return "";
}

void METHOD_SetTextAlignment(t_integer Id, t_integer Column, const QString & TextAlignment)
{
  QTreeWidgetItem *l = (QTreeWidgetItem *) Id;
  if (l){
    int i = 0;

    if (TextAlignment.contains("AlignLeft")) i |= Qt::AlignLeft;
    if (TextAlignment.contains("AlignRight")) i |= Qt::AlignRight;
    if (TextAlignment.contains("AlignHCenter")) i |= Qt::AlignHCenter;
    if (TextAlignment.contains("AlignJustify")) i |= Qt::AlignJustify;
    if (TextAlignment.contains("AlignTop")) i |= Qt::AlignTop;
    if (TextAlignment.contains("AlignBottom")) i |= Qt::AlignBottom;
    if (TextAlignment.contains("AlignVCenter")) i |= Qt::AlignVCenter;
    if (TextAlignment.contains("AlignCenter")) i |= Qt::AlignCenter;
    if (TextAlignment.contains("AlignAbsolute")) i |= Qt::AlignAbsolute;
    if (TextAlignment.contains("AlignLeading")) i |= Qt::AlignLeading;
    if (TextAlignment.contains("AlignTrailing")) i |= Qt::AlignTrailing;
    if (TextAlignment.contains("AlignHorizontal_Mask")) i |= Qt::AlignHorizontal_Mask;
    if (TextAlignment.contains("AlignVertical_Mask")) i |= Qt::AlignVertical_Mask;

    l->setTextAlignment(Column, (Qt::AlignmentFlag) i);
  }
}

t_integer METHOD_ColumnCount(t_integer Id)
{
  QTreeWidgetItem *l = (QTreeWidgetItem *) Id;
  if (l) return l->columnCount();
  return 0;
}



t_integer METHOD_Append(const QString & Caption)
{
  QTreeWidgetItem *l = new QTreeWidgetItem();
  if (l){
    l->setText(0, Caption);
    addTopLevelItem(l);
    return (t_integer) l;
  }
  return 0;
}

t_integer METHOD_Append(const QString & Icon, const QString & Caption)
{
  QTreeWidgetItem *l = new QTreeWidgetItem();
  if (l){
    l->setText(0, Caption);
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
    l->setIcon(0, pi);
    addTopLevelItem(l);
    return (t_integer) l;
  }
  return 0;
}

void METHOD_ClosePersistentEditor(t_integer Id, t_integer Column)
{
  QTreeWidgetItem *l = (QTreeWidgetItem *) Id;
  if (l) closePersistentEditor(l, Column);
}

t_integer METHOD_ColumnCount()
{
  return columnCount();
}
  
t_integer METHOD_CurrentColumn()
{
  return currentColumn();
}

t_integer METHOD_CurrentItem()
{
  return (t_integer) currentItem();
}

void METHOD_EditItem(t_integer Id, t_integer Column)
{
  QTreeWidgetItem *l = (QTreeWidgetItem *) Id;
  if (l) editItem(l, Column);
}

t_integer METHOD_FindItem(const QString & Caption, const QString & Flag, t_integer Column)
{
  int i = 0;

  if (Flag.contains("MatchExactly")) i |= Qt::MatchExactly;
  else if (Flag.contains("MatchFixedString")) i |= Qt::MatchFixedString;
  else if (Flag.contains("MatchContains")) i |= Qt::MatchContains;
  else if (Flag.contains("MatchStartsWith")) i |= Qt::MatchStartsWith;
  else if (Flag.contains("MatchEndsWith")) i |= Qt::MatchEndsWith;
  else if (Flag.contains("MatchCaseSensitive")) i |= Qt::MatchCaseSensitive;
  else if (Flag.contains("MatchRegExp")) i |= Qt::MatchRegExp;
  else if (Flag.contains("MatchWildcard")) i |= Qt::MatchWildcard;
  else if (Flag.contains("MatchWrap")) i |= Qt::MatchWrap;
  else if (Flag.contains("MatchRecursive")) i |= Qt::MatchRecursive;

  QList<QTreeWidgetItem *>l = findItems(Caption, (Qt::MatchFlag) i, Column);
  return l.count() ? (t_integer) l.at(0) : 0;
}

t_integer METHOD_HeaderItem()
{
  return (t_integer) headerItem();
}

t_integer METHOD_IndexOfTopLevelItem(t_integer Id)
{
  QTreeWidgetItem *l = (QTreeWidgetItem *) Id;
  if(l) return indexOfTopLevelItem(l) + 1;
  return -1;
}

t_integer METHOD_Insert(t_integer Index, const QString & Caption)
{
  if (Index - 1 >= 0 && Index - 1 <= topLevelItemCount()){
    QTreeWidgetItem *l = new QTreeWidgetItem();
    if (l){
      l->setText(0, Caption);
      insertTopLevelItem(Index - 1, l);
      return (t_integer) l;
    }
  }
  return 0;
}

t_integer METHOD_Insert(t_integer Index, const QString & Icon, const QString & Caption)
{
  if (Index - 1 >= 0 && Index - 1 <= topLevelItemCount()){
    QTreeWidgetItem *l = new QTreeWidgetItem();
    if (l){
      l->setText(0, Caption);
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
      l->setIcon(0, pi);
      insertTopLevelItem(Index, l);
      return (t_integer) l;
    }
  }
  return 0;
}

t_integer METHOD_InvisibleRootItem()
{
  return (t_integer) invisibleRootItem();
}

t_integer METHOD_ItemAt(t_integer X, t_integer Y)
{
  return (t_integer) itemAt(X, Y);
}

void METHOD_OpenPersistentEditor(t_integer Id, t_integer Column)
{
  QTreeWidgetItem *l = (QTreeWidgetItem *) Id;
  if (l) openPersistentEditor(l, Column);
}

QList<QTreeWidgetItem *> selected;
int nSelected;

t_integer METHOD_FirstSelectedItem()
{
  selected = selectedItems();
  nSelected = 0;
  return selected.count() ? (t_integer) selected.at(0) : 0;
}

t_integer METHOD_NextSelectedItem()
{
  return ++nSelected < selected.count() ? (t_integer) selected.at(nSelected) : 0;
}

void METHOD_SetColumnCount(t_integer Count)
{
  setColumnCount(Count);
}

void METHOD_SetCurrentItem(t_integer Id)
{
  QTreeWidgetItem *l = (QTreeWidgetItem *) Id;
  if (l) setCurrentItem(l);
}

void METHOD_SetCurrentItem(t_integer Id, t_integer Column)
{
  QTreeWidgetItem *l = (QTreeWidgetItem *) Id;
  if (l) setCurrentItem(l, Column);
}

void METHOD_SetHeaderLabel(const QString & Caption)
{
  setHeaderLabel(Caption);
  headerItem()->setHidden(false);
}

void METHOD_SetHeaderLabel(const QString & Caption, t_integer Column)
{
  QTreeWidgetItem *l = headerItem();
  if (l){ 
    l->setText(Column, Caption);
    l->setHidden(false);
  }
}

t_integer METHOD_SortColumn()
{
  return sortColumn();
}

void METHOD_SortItems(t_integer Column, t_boolean Descending)
{
  return sortItems(Column, Descending  ? Qt::DescendingOrder : Qt::AscendingOrder);
}

void METHOD_RemoveTopLevelItem(t_integer Index)
{
  if (Index - 1 >= 0 && Index - 1 <= topLevelItemCount()) takeTopLevelItem(Index - 1);
}

t_integer METHOD_TopLevelItem(t_integer Index)
{
  if (Index - 1 >= 0 && Index - 1 <= topLevelItemCount()) return (t_integer) topLevelItem(Index - 1);
  return 0;
}

t_integer METHOD_TopLevelItemCount()
{
  return topLevelItemCount();
}

t_boolean METHOD_IsColumnHidden(t_integer Column)
{
  return isColumnHidden(Column);
}

void METHOD_SetColumnHidden(t_integer Column, t_boolean IsColumnHidden)
{
  setColumnHidden(Column, IsColumnHidden);
}

t_boolean METHOD_IsSortingEnabled()
{
  return isSortingEnabled();
}

void METHOD_SetSortingEnabled(t_boolean IsSortingEnabled)
{
  setSortingEnabled(IsSortingEnabled);
}

t_boolean METHOD_IsItemsExpandable()
{
  return itemsExpandable();
}

void METHOD_SetItemsExpandable(t_boolean IsItemsExpandable)
{
  setItemsExpandable(IsItemsExpandable);
}

t_boolean METHOD_IsAllColumnsShowFocus()
{
  return allColumnsShowFocus();
}

void METHOD_SetAllColumnsShowFocus(t_boolean IsAllColumnsShowFocus)
{
  setAllColumnsShowFocus(IsAllColumnsShowFocus);
}

t_integer METHOD_ColumnWidth(t_integer Column)
{
  return columnWidth(Column);
}

void METHOD_SetColumnWidth(t_integer Column, t_integer Width)
{
  setColumnWidth(Column, Width);
}

void METHOD_CollapseAll()
{
  collapseAll();
}

void METHOD_ExpandAll()
{
  expandAll();
}

void METHOD_SelectAll()
{
  selectAll();
}

void METHOD_ShowColumn(t_integer Column)
{
  showColumn(Column);
}

void METHOD_CollapseItem(t_integer Id)
{
  QTreeWidgetItem *l = (QTreeWidgetItem *) Id;
  if (l) collapseItem(l);
}

void METHOD_ExpandItem(t_integer Id)
{
  QTreeWidgetItem *l = (QTreeWidgetItem *) Id;
  if (l) expandItem(l);
}

void METHOD_ScrollToItem(t_integer Id)
{
  QTreeWidgetItem *l = (QTreeWidgetItem *) Id;
  if (l) scrollToItem(l);
}

t_boolean METHOD_IsAlternatingRowColors()
{
  return alternatingRowColors();
}

void METHOD_SetAlternatingRowColors(t_boolean IsAlternatingRowColors)
{
  setAlternatingRowColors(IsAlternatingRowColors);
}

void METHOD_ScrollToBottom()
{
  scrollToBottom();
}

void METHOD_ScrollToTop()
{
  scrollToTop();
}

virtual void EVENT_CurrentItemChanged(t_integer Current, t_integer Previous)
{
}

virtual void EVENT_ItemActivated(t_integer Id, t_integer Column)
{
}

virtual void EVENT_ItemChanged(t_integer Id, t_integer Column)
{
}

virtual void EVENT_ItemClicked(t_integer Id, t_integer Column)
{
}

virtual void EVENT_ItemCollapsed(t_integer Id)
{
}

virtual void EVENT_ItemDoubleClicked(t_integer Id, t_integer Column)
{
}

virtual void EVENT_ItemEntered(t_integer Id, t_integer Column)
{
}

virtual void EVENT_ItemExpanded(t_integer Id)
{
}

virtual void EVENT_ItemPressed(t_integer Id, t_integer Column)
{
}

virtual void EVENT_ItemSelectionChanged()
{
}
/*
public slots:
void CurrentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
  EVENT_CurrentItemChanged((t_integer) current, (t_integer) previous);
}

void ItemActivated(QTreeWidgetItem *item, t_integer Column)
{
  EVENT_ItemActivated((t_integer) item, Column);
}

void ItemChanged(QTreeWidgetItem *item, t_integer Column)
{
  EVENT_ItemChanged((t_integer) item, Column);
}

void ItemClicked(QTreeWidgetItem *item, t_integer Column)
{
  EVENT_ItemClicked((t_integer) item, Column);
}

void ItemCollapsed(QTreeWidgetItem *item, t_integer Column)
{
  EVENT_ItemCollapsed((t_integer) item, Column);
}

void ItemDoubleClicked(QTreeWidgetItem *item, t_integer Column)
{
  EVENT_ItemDoubleClicked((t_integer) item, Column);
}
  
void ItemEntered(QTreeWidgetItem *item, t_integer Column)
{
  EVENT_ItemEntered((t_integer) item, Column);
}
  
void ItemExpanded(QTreeWidgetItem *item)
{
  EVENT_ItemExpanded((t_integer) item);
}

void ItemPressed(QTreeWidgetItem *item, t_integer Column)
{
  EVENT_ItemPressed((t_integer) item, Column);
}

void ItemSelectionChanged(QTreeWidgetItem *item, t_integer Column)
{
  EVENT_ItemSelectionChanged();
}
*/

public:

// events
// *** bindings

// ***
#include "_control1_binding.h"


// ***
#include "_control1.h"


};

#include "_control2.h"

#undef _TREEVIEW

#undef TEST
#undef TEST2
#undef TEST3
#undef SUPERCLASS

#endif