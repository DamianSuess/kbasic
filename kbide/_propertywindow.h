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

#ifndef _PROPERTYWINDOW_H
#define _PROPERTYWINDOW_H

#include <QtGui>


class _form;
class _propertywindow;

#include "../kbshared/typedef.h"


#include "_propertywidget.h"




class _qwidget : public QWidget
{
  Q_OBJECT
public:
  _qwidget(_propertywindow *_parent) : QWidget((QWidget *)_parent)
  {
    parent = _parent;
  }

void paintEvent(QPaintEvent *e);

private:
_propertywindow *parent;
};


class _qgridlayout : public QGridLayout
{
  Q_OBJECT
public:
  _qgridlayout(_propertywindow *_parent)
  {
    parent = _parent;
  }

void paintEvent(QPaintEvent *e);

private:
_propertywindow *parent;
};


class _propertywindow : public QWidget
{
  Q_OBJECT

public:
  _propertywindow(QWidget *parent);
  ~_propertywindow(void);

  void showProperties(bool bBuild, QString sForFile = "");
  void showControlName(const QString &s)
  {
    currentcontrolname->setText(s);
  }

  void setEnabled(bool b);
  bool newEvent(QString s);

  void lock();
  void unlock();

  QPushButton *setform;

public slots:

  void actionMain();
  void actionSpecial();
  void actionFormat();
  void actionData();
  void actionControl();
  void actionEvent();
  void actionType();



private:
  void paintEvent(QPaintEvent *e);

  void createList();

  //bool bHIDDEN;
  bool bTREE;
  _qwidget *fr;
  _qgridlayout *grid;
  QToolBar *tb;

  QAction *aMain;
  QAction *aSpecial;
  QAction *aFormat;
  QAction *aData;
  QAction *aControl;
  QAction *aEvent;
  QAction *aType;


_property_header *header_main;
_property_header *header_other;
_property_header *header_other2;
_property_header *header_other3;
_property_header *header_other4;
_property_header *header_event;


void addRow(_property_pixeledit *le, int &y, bool visible, bool bNewHeader = false);
void addRow(_property_listcombobox *le, int &y, bool visible, bool bNewHeader = false);
void addRow(_property_event *le, int &y, bool visible, bool bNewHeader = false);
void addRow(_property_fontedit *le, int &y, bool visible, bool bNewHeader = false);
void addRow(_property_imageedit *le, int &y, bool visible, bool bNewHeader = false);
void addRow(_property_coloredit *le, int &y, bool visible, bool bNewHeader = false);
void addRow(_property_lineedit *le, int &y, bool visible, bool bNewHeader = false);
void addRow(_property_booleancombobox *le, int &y, bool visible, bool bNewHeader = false);
void addRow(_property_choicebox *le, int &y, bool visible, bool bNewHeader = false);
void addRow(_property_colorimageedit *le, int &y, bool visible, bool bNewHeader = false);
void addRow(_property_soundedit *le, int &y, bool visible, bool bNewHeader = false);
void addRow(_property_fileedit *le, int &y, bool visible, bool bNewHeader = false);

void addRowHeader(_property_header *l, int &y, bool visible);



void SETPROPERTY_QString(bool d, bool b, QString n, _property_soundedit *le, bool bBold = false)
{
  if (d){
    le->display(bBold);
    if (b){
      le->setText(n); 
    } else {
      le->setText(""); 
    }
 //   le->nei
  } else {
    le->undisplay();
  }
}

void SETPROPERTY_QString(bool d, bool b, QString n, _property_fileedit *le, bool bBold = false)
{
  if (d){
    le->display(bBold);
    if (b){
      le->setText(n); 
    } else {
      le->setText(""); 
    }
  } else {
    le->undisplay();
  }
}

void SETPROPERTY_QString(bool d, bool b, QString n, _property_linelabel *le, bool bBold = false)
{
  if (d){
    le->display(bBold);
    if (b){
      le->setText(n); 
    } else {
      le->setText(""); 
    }
  } else {
    le->undisplay();
  }
}

void SETPROPERTY_QString(bool d, bool b, QString n, _property_fontedit *le, bool bBold = false)
{
  if (d){
    le->display(bBold);
    if (b){
      le->setText(n); 
    } else {
      le->setText(""); 
    }
  } else {
    le->undisplay();
  }
}

void SETPROPERTY_QString(bool d, bool b, QString n, _property_imageedit *le, bool bBold = false)
{
  if (d){
    le->display(bBold);
    if (b){
      le->setText(n); 
    } else {
      le->setText(""); 
    }
  } else {
    le->undisplay();
  }
}

void SETPROPERTY_QString(bool d, bool b, QString n, _property_colorimageedit *le, bool bBold = false)
{
  if (d){
    le->display(bBold);
    if (b){
      le->setText(n); 
    } else {
      le->setText(""); 
    }
  } else {
    le->undisplay();
  }
}

void SETPROPERTY_QString(bool d, bool b, QString n, _property_coloredit *le, bool bBold = false)
{
  if (d){
    le->display(bBold);
    if (b){
      le->setText(n); 
    } else {
      le->setText(""); 
    }
  } else {
    le->undisplay();
  }
}

void SETPROPERTY_QString(bool d, bool b, QString n, _property_choicebox *le, bool bBold = false)
{
  if (d){
    le->display(bBold);
    if (b){
      le->setText(n); 
    } else {
      le->setText(""); 
    }
  } else {
    le->undisplay();
  }
}

void SETPROPERTY_QString(bool d, bool b, QString n, _property_lineedit *le, bool bBold = false)
{
  if (d){
    le->display(bBold);
    if (b){
      le->setText(n); 
    } else {
      le->setText(""); 
    }
  } else {
    le->undisplay();
  }
}

void SETPROPERTY_Integer(bool d, bool b, int n, _property_pixeledit *le, bool bBold = false)
{
  QString ac;

  if (d){
    le->display(bBold);

    {
      if (b){
        ac.sprintf("%d", n);
        le->setText(ac); 
      } else {
        le->setText(""); 
      }
    }    
  } else {
    le->undisplay();
  }
}

void SETPROPERTY_Integer(bool d, bool b, int n, _property_lineedit *le, bool bBold = false)
{
  QString ac;

  if (d){
    le->display(bBold);

    if (le == PROPERTY_MinimumWidth 
      || le == PROPERTY_MinimumHeight 
      || le == PROPERTY_MaximumWidth 
      || le == PROPERTY_MaximumHeight 
      )
    {
      if (n && b){
        ac.sprintf("%d", n);
        le->setText(ac); 
      } else {
        le->setText(""); 
      }
    } else {        
      if (b){
        ac.sprintf("%d", n);
        le->setText(ac); 
      } else {
        le->setText(""); 
      }
    }    
  } else {
    le->undisplay();
  }
}

void SETPROPERTY_Boolean(bool d, bool b, bool n, _property_booleancombobox *le, bool bBold = false)
{
  QString ac;

  if (d){
    le->display(bBold);
    if (b){
      if (n){
        le->setCurrentIndex(le->findText("True"));
      } else {
        le->setCurrentIndex(le->findText("False"));
      }
    } else {
      le->setCurrentIndex(le->findText("False"));
      le->setEditText("");
    }
  } else {
    le->undisplay();
  }
}

void SETPROPERTY_Boolean(bool d, bool b, bool n, _property_event *le, bool bBold = false)
{
  QString ac;

  if (d){
    le->display(bBold);
    if (b){
      if (n){
        le->setText("Yes");
      } else {
        le->setText("");
      }
    } else {
      le->setText("");
    }
  } else {
    le->undisplay();
  }
}

void SETPROPERTY_QString(bool d, bool b, QString n, _property_listcombobox *le, bool bBold = false)
{
  QString ac;

  if (d){
    le->display(bBold);
    if (n.length()){
      le->setEditText(n);
    } else {
      le->setEditText(n);
    }
  } else {
    le->undisplay();
  }
}


// *********************************
public:

void SETPROPERTY_Group(bool d, bool b, QString n){ SETPROPERTY_QString(d, b, n, PROPERTY_Group, !n.isEmpty()); }
void SETPROPERTY_Background(bool d, bool b, QString n){ SETPROPERTY_QString(d, b, n, PROPERTY_Background, !n.isEmpty()); }
void SETPROPERTY_BackgroundStyle(bool d, bool b, QString n){ SETPROPERTY_QString(d, b, n, PROPERTY_BackgroundStyle, !n.isEmpty()); }
void SETPROPERTY_Palette(bool d, bool b, QString n){ SETPROPERTY_QString(d, b, n, PROPERTY_Palette, !n.isEmpty()); }
void SETPROPERTY_MinimumWidth(bool d, bool b, t_integer n){ SETPROPERTY_Integer(d, b, n, PROPERTY_MinimumWidth, n != 0); }
void SETPROPERTY_MinimumHeight(bool d, bool b, t_integer n){ SETPROPERTY_Integer(d, b, n, PROPERTY_MinimumHeight, n != 0); }
void SETPROPERTY_MaximumWidth(bool d, bool b, t_integer n){ SETPROPERTY_Integer(d, b, n, PROPERTY_MaximumWidth, n != 0); }
void SETPROPERTY_MaximumHeight(bool d, bool b, t_integer n){ SETPROPERTY_Integer(d, b, n, PROPERTY_MaximumHeight, n != 0); }

void SETPROPERTY_DockTitleVisible(bool d, bool b, t_boolean n){ SETPROPERTY_Boolean(d, b, n, PROPERTY_DockTitleVisible, n == false); }
void SETPROPERTY_DockOrder(bool d, bool b, QString n){ SETPROPERTY_QString(d, b, n, PROPERTY_DockOrder, !n.isEmpty()); }

void SETPROPERTY_DockSplit(bool d, bool b, QString n){ SETPROPERTY_QString(d, b, n, PROPERTY_DockSplit, !n.isEmpty()); }
void SETPROPERTY_ShowMode(bool d, bool b, QString n){ SETPROPERTY_QString(d, b, n, PROPERTY_ShowMode, !n.isEmpty()); }

void SETPROPERTY_DockWidth(bool d, bool b, t_integer n){ SETPROPERTY_Integer(d, b, n, PROPERTY_DockWidth, n != 0); }
void SETPROPERTY_DockHeight(bool d, bool b, t_integer n){ SETPROPERTY_Integer(d, b, n, PROPERTY_DockHeight, n != 0); }

void SETPROPERTY_ScrollX(bool d, bool b, t_integer n){ SETPROPERTY_Integer(d, b, n, PROPERTY_ScrollX, n != 0); }
void SETPROPERTY_ScrollY(bool d, bool b, t_integer n){ SETPROPERTY_Integer(d, b, n, PROPERTY_ScrollY, n != 0); }
void SETPROPERTY_ScrollWidth(bool d, bool b, t_integer n){ SETPROPERTY_Integer(d, b, n, PROPERTY_ScrollWidth, n != 0); }
void SETPROPERTY_ScrollHeight(bool d, bool b, t_integer n){ SETPROPERTY_Integer(d, b, n, PROPERTY_ScrollHeight, n != 0); }

void SETPROPERTY_MultiPageHeight(bool d, bool b, t_integer n){ SETPROPERTY_Integer(d, b, n, PROPERTY_MultiPageHeight, n != 0); }
void SETPROPERTY_MultiPageBorderTop(bool d, bool b, t_integer n){ SETPROPERTY_Integer(d, b, n, PROPERTY_MultiPageBorderTop, n != 0); }
void SETPROPERTY_MultiPageBorderBottom(bool d, bool b, t_integer n){ SETPROPERTY_Integer(d, b, n, PROPERTY_MultiPageBorderBottom, n != 0); }
void SETPROPERTY_MultiPageBorderLeft(bool d, bool b, t_integer n){ SETPROPERTY_Integer(d, b, n, PROPERTY_MultiPageBorderLeft, n != 0); }
void SETPROPERTY_MultiPageBorderRight(bool d, bool b, t_integer n){ SETPROPERTY_Integer(d, b, n, PROPERTY_MultiPageBorderRight, n != 0); }



void SETPROPERTY_BorderTop(bool d, bool b, t_integer n){ SETPROPERTY_Integer(d, b, n, PROPERTY_BorderTop, n != 0); }
void SETPROPERTY_BorderBottom(bool d, bool b, t_integer n){ SETPROPERTY_Integer(d, b, n, PROPERTY_BorderBottom, n != 0); }
void SETPROPERTY_BorderLeft(bool d, bool b, t_integer n){ SETPROPERTY_Integer(d, b, n, PROPERTY_BorderLeft, n != 0); }
void SETPROPERTY_BorderRight(bool d, bool b, t_integer n){ SETPROPERTY_Integer(d, b, n, PROPERTY_BorderRight, n != 0); }


void SETPROPERTY_EchoMode(bool d, bool b, QString n){ SETPROPERTY_QString(d, b, n, PROPERTY_EchoMode, !n.isEmpty()); }
void SETPROPERTY_CSV(bool d, bool b, QString n){ SETPROPERTY_QString(d, b, n, PROPERTY_CSV, !n.isEmpty()); }
void SETPROPERTY_Tag(bool d, bool b, QString n){ SETPROPERTY_QString(d, b, n, PROPERTY_Tag, !n.isEmpty()); }

void SETPROPERTY_ArrowType(bool d, bool b, QString n){ SETPROPERTY_QString(d, b, n, PROPERTY_ArrowType, !n.isEmpty()); }
void SETPROPERTY_PopupMode(bool d, bool b, QString n){ SETPROPERTY_QString(d, b, n, PROPERTY_PopupMode, !n.isEmpty()); }
void SETPROPERTY_ToolBarRole(bool d, bool b, QString n){ SETPROPERTY_QString(d, b, n, PROPERTY_ToolBarRole, !n.isEmpty());}

void SETPROPERTY_MenuBarRole(bool d, bool b, QString n){ SETPROPERTY_QString(d, b, n, PROPERTY_MenuBarRole, !n.isEmpty()); }
void SETPROPERTY_Data(bool d, bool b, QString n){ SETPROPERTY_QString(d, b, n, PROPERTY_Data, !n.isEmpty()); }
void SETPROPERTY_TableView(bool d, bool b, t_boolean n){ SETPROPERTY_Boolean(d, b, n, PROPERTY_TableView, n != false); }

void SETPROPERTY_BoxIndex(bool d, bool b, t_integer n){ SETPROPERTY_Integer(d, b, n, PROPERTY_BoxIndex); }
void SETPROPERTY_BoxX(bool d, bool b, t_integer n){ SETPROPERTY_Integer(d, b, n, PROPERTY_BoxX); }
void SETPROPERTY_BoxY(bool d, bool b, t_integer n){ SETPROPERTY_Integer(d, b, n, PROPERTY_BoxY); }
void SETPROPERTY_SplitIndex(bool d, bool b, t_integer n){ SETPROPERTY_Integer(d, b, n, PROPERTY_SplitIndex); }

void SETPROPERTY_Scale(bool d, bool b, t_boolean n){ SETPROPERTY_Boolean(d, b, n, PROPERTY_Scale, n != false); }
void SETPROPERTY_StopOnClose(bool d, bool b, t_boolean n){ SETPROPERTY_Boolean(d, b, n, PROPERTY_StopOnClose, n != false); }
/*
void SETPROPERTY_FormCentered(bool d, bool b, t_boolean n){ SETPROPERTY_Boolean(d, b, n, PROPERTY_FormCentered); }
void SETPROPERTY_FormScaled(bool d, bool b, t_boolean n){ SETPROPERTY_Boolean(d, b, n, PROPERTY_FormScaled); }
*/
void SETPROPERTY_DragDrop(bool d, bool b, t_boolean n){ SETPROPERTY_Boolean(d, b, n, PROPERTY_DragDrop, n != false); }
void SETPROPERTY_FocusPolicy(bool d, bool b, QString n){ SETPROPERTY_QString(d, b, n, PROPERTY_FocusPolicy, !n.isEmpty()); }
void SETPROPERTY_FocusProxy(bool d, bool b, QString n){ SETPROPERTY_QString(d, b, n, PROPERTY_FocusProxy, !n.isEmpty()); }
void SETPROPERTY_FocusOrder(bool d, bool b, t_integer n){ SETPROPERTY_Integer(d, b, n, PROPERTY_FocusOrder, n != 0); }

void SETPROPERTY_FontName(bool d, bool b, QString n){ SETPROPERTY_QString(d, b, n, PROPERTY_FontName, !n.isEmpty()); }
void SETPROPERTY_FontSize(bool d, bool b, t_integer n){ SETPROPERTY_QString(d, b, QString("%1").arg(n), PROPERTY_FontSize, n != 0); }
void SETPROPERTY_FontBold(bool d, bool b, t_boolean n){ SETPROPERTY_Boolean(d, b, n, PROPERTY_FontBold, n != false); }
void SETPROPERTY_FontItalic(bool d, bool b, t_boolean n){ SETPROPERTY_Boolean(d, b, n, PROPERTY_FontItalic, n != false); }
void SETPROPERTY_FontUnderline(bool d, bool b, t_boolean n){ SETPROPERTY_Boolean(d, b, n, PROPERTY_FontUnderline, n != false); }
void SETPROPERTY_FontColor(bool d, bool b, QString n){ SETPROPERTY_QString(d, b, n, PROPERTY_FontColor, !n.isEmpty()); }

void SETPROPERTY_StatusTip(bool d, bool b, QString n){ SETPROPERTY_QString(d, b, n, PROPERTY_StatusTip, !n.isEmpty()); }
void SETPROPERTY_ToolTip(bool d, bool b, QString n){ SETPROPERTY_QString(d, b, n, PROPERTY_ToolTip, !n.isEmpty()); }
void SETPROPERTY_StyleSheet(bool d, bool b, QString n){ SETPROPERTY_QString(d, b, n, PROPERTY_StyleSheet, !n.isEmpty()); }
void SETPROPERTY_WhatsThis(bool d, bool b, QString n){ SETPROPERTY_QString(d, b, n, PROPERTY_WhatsThis, !n.isEmpty()); }

void SETPROPERTY_Flag(bool d, bool b, QString n){ SETPROPERTY_QString(d, b, n, PROPERTY_Flag, !n.isEmpty()); }
void SETPROPERTY_Layout(bool d, bool b, QString n){ SETPROPERTY_QString(d, b, n, PROPERTY_Layout, !n.isEmpty()); }
void SETPROPERTY_SQLControls(bool d, bool b, QString n){ SETPROPERTY_QString(d, b, n, PROPERTY_SQLControls, !n.isEmpty()); }
//void SETPROPERTY_IconCaption(bool d, bool b, QString n){ SETPROPERTY_QString(d, b, n, PROPERTY_IconCaption); }

void SETPROPERTY_Modal(bool d, bool b, t_boolean n){ SETPROPERTY_Boolean(d, b, n, PROPERTY_Modal, n != false); }
void SETPROPERTY_Opacity(bool d, bool b, t_integer n){ SETPROPERTY_QString(d, b, QString("%1").arg(n), PROPERTY_Opacity, n != 0); }
void SETPROPERTY_TimerInterval(bool d, bool b, t_integer n){ SETPROPERTY_Integer(d, b, n, PROPERTY_TimerInterval, n != 0); }

void SETPROPERTY_Shadow(bool d, bool b, t_boolean n){ SETPROPERTY_Boolean(d, b, n, PROPERTY_Shadow, n != false); }
void SETPROPERTY_Shape(bool d, bool b, t_boolean n){ SETPROPERTY_Boolean(d, b, n, PROPERTY_Shape, n != false); }
void SETPROPERTY_OpenLinks(bool d, bool b, t_boolean n){ SETPROPERTY_Boolean(d, b, n, PROPERTY_OpenLinks, n != false); }

void SETPROPERTY_Icon(bool d, bool b, QString n){ SETPROPERTY_QString(d, b, n, PROPERTY_Icon, !n.isEmpty()); }
void SETPROPERTY_InputControl(bool d, bool b, QString n){ SETPROPERTY_QString(d, b, n, PROPERTY_InputControl, !n.isEmpty()); }
void SETPROPERTY_Space(bool d, bool b, t_integer n){ SETPROPERTY_Integer(d, b, n, PROPERTY_Space, n != 0); }
void SETPROPERTY_Border(bool d, bool b, t_integer n){ SETPROPERTY_Integer(d, b, n, PROPERTY_Border, n != 0); }

void SETPROPERTY_Flat(bool d, bool b, t_boolean n){ SETPROPERTY_Boolean(d, b, n, PROPERTY_Flat, n != false); }
void SETPROPERTY_Flip(bool d, bool b, t_boolean n){ SETPROPERTY_Boolean(d, b, n, PROPERTY_Flip, n != false); }
void SETPROPERTY_Key(bool d, bool b, QString n){ SETPROPERTY_QString(d, b, n, PROPERTY_Key, !n.isEmpty()); }

void SETPROPERTY_IntegerMaximum(bool d, bool b, t_integer n){ SETPROPERTY_Integer(d, b, n, PROPERTY_IntegerMaximum, n != 0); }
void SETPROPERTY_IntegerMinimum(bool d, bool b, t_integer n){ SETPROPERTY_Integer(d, b, n, PROPERTY_IntegerMinimum, n != 0); }
void SETPROPERTY_Completer(bool d, bool b, QString n){ SETPROPERTY_QString(d, b, n, PROPERTY_Completer, !n.isEmpty()); }
void SETPROPERTY_ValidatorDouble(bool d, bool b, t_boolean n){ SETPROPERTY_Boolean(d, b, n, PROPERTY_ValidatorDouble, n != false); }
void SETPROPERTY_ValidatorInteger(bool d, bool b, t_boolean n){ SETPROPERTY_Boolean(d, b, n, PROPERTY_ValidatorInteger, n != false); }
void SETPROPERTY_ValidatorRegEx(bool d, bool b, QString n){ SETPROPERTY_QString(d, b, n, PROPERTY_ValidatorRegEx, n != false); }
void SETPROPERTY_ValidatorRegEx2(bool d, bool b, QString n){ SETPROPERTY_QString(d, b, n, PROPERTY_ValidatorRegEx2, n != false); }

void SETPROPERTY_DoubleEntry(bool d, bool b, t_boolean n){ SETPROPERTY_Boolean(d, b, n, PROPERTY_DoubleEntry, n != false); }
void SETPROPERTY_InsertPolicy(bool d, bool b, QString n){ SETPROPERTY_QString(d, b, n, PROPERTY_InsertPolicy, !n.isEmpty()); }
void SETPROPERTY_Editable(bool d, bool b, t_boolean n){ SETPROPERTY_Boolean(d, b, n, PROPERTY_Editable, n == false); }
void SETPROPERTY_MaximumVisible(bool d, bool b, t_integer n){ SETPROPERTY_Integer(d, b, n, PROPERTY_MaximumVisible, n != 0); }

void SETPROPERTY_Sorted(bool d, bool b, t_boolean n){ SETPROPERTY_Boolean(d, b, n, PROPERTY_Sorted, n != false); }

void SETPROPERTY_StringMaximum(bool d, bool b, QString n){ SETPROPERTY_QString(d, b, n, PROPERTY_StringMaximum, !n.isEmpty()); }
void SETPROPERTY_StringMinimum(bool d, bool b, QString n){ SETPROPERTY_QString(d, b, n, PROPERTY_StringMinimum, !n.isEmpty()); }
void SETPROPERTY_Format(bool d, bool b, QString n){ SETPROPERTY_QString(d, b, n, PROPERTY_Format, !n.isEmpty()); }

void SETPROPERTY_PopUp(bool d, bool b, t_boolean n){ SETPROPERTY_Boolean(d, b, n, PROPERTY_PopUp, n != false); }

void SETPROPERTY_ScrollBar(bool d, bool b, QString n){ SETPROPERTY_QString(d, b, n, PROPERTY_ScrollBar, n != false); }


void SETPROPERTY_MouseDownImage(bool d, bool b, QString n){ SETPROPERTY_QString(d, b, n, PROPERTY_MouseDownImage, !n.isEmpty()); }
void SETPROPERTY_MouseUpImage(bool d, bool b, QString n){ SETPROPERTY_QString(d, b, n, PROPERTY_MouseUpImage, !n.isEmpty()); }
void SETPROPERTY_EnabledImage(bool d, bool b, QString n){ SETPROPERTY_QString(d, b, n, PROPERTY_EnabledImage, !n.isEmpty()); }

void SETPROPERTY_CheckMouseDownImage(bool d, bool b, QString n){ SETPROPERTY_QString(d, b, n, PROPERTY_CheckMouseDownImage, !n.isEmpty()); }
void SETPROPERTY_CheckMouseUpImage(bool d, bool b, QString n){ SETPROPERTY_QString(d, b, n, PROPERTY_CheckMouseUpImage, !n.isEmpty()); }
void SETPROPERTY_CheckEnabledImage(bool d, bool b, QString n){ SETPROPERTY_QString(d, b, n, PROPERTY_CheckEnabledImage, !n.isEmpty()); }

void SETPROPERTY_MouseDownSound(bool d, bool b, QString n){ SETPROPERTY_QString(d, b, n, PROPERTY_MouseDownSound, !n.isEmpty()); }
void SETPROPERTY_MouseUpSound(bool d, bool b, QString n){ SETPROPERTY_QString(d, b, n, PROPERTY_MouseUpSound, !n.isEmpty()); }

void SETPROPERTY_HomeURL(bool d, bool b, QString n){ SETPROPERTY_QString(d, b, n, PROPERTY_HomeURL, !n.isEmpty()); }





void SETPROPERTY_Name(bool d, bool b, QString n)
{
  SETPROPERTY_QString(d, b, n, PROPERTY_Name, !n.isEmpty());
}

void SETPROPERTY_ControlType(bool d, bool b, QString n)
{
  SETPROPERTY_QString(d, b, n, PROPERTY_ControlType);
}

void SETPROPERTY_X(bool d, bool b, int n)
{
  SETPROPERTY_Integer(d, b, n, PROPERTY_X, true);
}

void SETPROPERTY_Y(bool d, bool b, int n)
{
  SETPROPERTY_Integer(d, b, n, PROPERTY_Y, true);
}

void SETPROPERTY_Width(bool d, bool b, int n)
{
  SETPROPERTY_Integer(d, b, n, PROPERTY_Width, true);
}

void SETPROPERTY_Height(bool d, bool b, int n)
{
  SETPROPERTY_Integer(d, b, n, PROPERTY_Height, true);
}

void SETPROPERTY_Caption(bool d, bool b, QString n)
{
  SETPROPERTY_QString(d, b, n, PROPERTY_Caption, !n.isEmpty());
}

void SETPROPERTY_IntegerValue(bool d, bool b, int n)
{
  SETPROPERTY_Integer(d, b, n, PROPERTY_IntegerValue);
}

void SETPROPERTY_Enabled(bool d, bool b, bool n)
{
  SETPROPERTY_Boolean(d, b, n, PROPERTY_Enabled, n == false);
}

void SETPROPERTY_Cursor(bool d, bool b, QString n)
{
  SETPROPERTY_QString(d, b, n, PROPERTY_Cursor, !n.isEmpty());
}

void SETPROPERTY_TabIndex(bool d, bool b, int n)
{
  SETPROPERTY_Integer(d, b, n, PROPERTY_TabIndex);
}

void SETPROPERTY_ParentIndex(bool d, bool b, int n)
{
  SETPROPERTY_Integer(d, b, n, PROPERTY_ParentIndex);
}

void SETPROPERTY_Resizable(bool d, bool b, bool n)
{
  SETPROPERTY_Boolean(d, b, n, PROPERTY_Resizable, n == false);
}


void SETPROPERTY_ResizableSmaller(bool d, bool b, bool n)
{
  SETPROPERTY_Boolean(d, b, n, PROPERTY_ResizableSmaller, n != false);
}
void SETPROPERTY_ResizableBigger(bool d, bool b, bool n)
{
  SETPROPERTY_Boolean(d, b, n, PROPERTY_ResizableBigger, n != false);
}



void SETPROPERTY_Visible(bool d, bool b, bool n)
{
  SETPROPERTY_Boolean(d, b, n, PROPERTY_Visible, n == false);
}

void SETPROPERTY_Separator(bool d, bool b, bool n)
{
  SETPROPERTY_Boolean(d, b, n, PROPERTY_Separator, n != false);
}

void SETPROPERTY_WordWrap(bool d, bool b, bool n)
{
  SETPROPERTY_Boolean(d, b, n, PROPERTY_WordWrap, n != false);
}

void SETPROPERTY_ReadOnly(bool d, bool b, bool n)
{
  SETPROPERTY_Boolean(d, b, n, PROPERTY_ReadOnly, n != false);
}

void SETPROPERTY_Alignment(bool d, bool b, QString n)
{
  SETPROPERTY_QString(d, b, n, PROPERTY_Alignment, !n.isEmpty());
}

void SETPROPERTY_Orientation(bool d, bool b, QString n)
{
  SETPROPERTY_QString(d, b, n, PROPERTY_Orientation, !n.isEmpty());
}

void SETPROPERTY_Feature(bool d, bool b, QString n)
{
  SETPROPERTY_QString(d, b, n, PROPERTY_Feature, !n.isEmpty());
}


void SETPROPERTY_OnCurrentItemChanged(bool d, bool b, bool n){ SETPROPERTY_Boolean(d, b, n, PROPERTY_OnCurrentItemChanged); }
void SETPROPERTY_OnItemActivated(bool d, bool b, bool n){ SETPROPERTY_Boolean(d, b, n, PROPERTY_OnItemActivated); }
void SETPROPERTY_OnItemChanged(bool d, bool b, bool n){ SETPROPERTY_Boolean(d, b, n, PROPERTY_OnItemChanged); }
void SETPROPERTY_OnItemClicked(bool d, bool b, bool n){ SETPROPERTY_Boolean(d, b, n, PROPERTY_OnItemClicked); }
void SETPROPERTY_OnItemCollapsed(bool d, bool b, bool n){ SETPROPERTY_Boolean(d, b, n, PROPERTY_OnItemCollapsed); }
void SETPROPERTY_OnItemDoubleClicked(bool d, bool b, bool n){ SETPROPERTY_Boolean(d, b, n, PROPERTY_OnItemDoubleClicked); }
void SETPROPERTY_OnItemEntered(bool d, bool b, bool n){ SETPROPERTY_Boolean(d, b, n, PROPERTY_OnItemEntered); }
void SETPROPERTY_OnItemExpanded(bool d, bool b, bool n){ SETPROPERTY_Boolean(d, b, n, PROPERTY_OnItemExpanded); }
void SETPROPERTY_OnItemPressed(bool d, bool b, bool n){ SETPROPERTY_Boolean(d, b, n, PROPERTY_OnItemPressed); }
void SETPROPERTY_OnItemSelectionChanged(bool d, bool b, bool n){ SETPROPERTY_Boolean(d, b, n, PROPERTY_OnItemSelectionChanged); }

void SETPROPERTY_OnDockMove(bool d, bool b, bool n){ SETPROPERTY_Boolean(d, b, n, PROPERTY_OnDockMove); }
void SETPROPERTY_OnDockShow(bool d, bool b, bool n){ SETPROPERTY_Boolean(d, b, n, PROPERTY_OnDockShow); }
void SETPROPERTY_OnDockHide(bool d, bool b, bool n){ SETPROPERTY_Boolean(d, b, n, PROPERTY_OnDockHide); }
void SETPROPERTY_OnDockFloating(bool d, bool b, bool n){ SETPROPERTY_Boolean(d, b, n, PROPERTY_OnDockFloating); }
void SETPROPERTY_OnDockNotFloating(bool d, bool b, bool n){ SETPROPERTY_Boolean(d, b, n, PROPERTY_OnDockNotFloating); }


// PROPERTY
void SETPROPERTY_ViewMode(bool d, bool b, QString n){ SETPROPERTY_QString(d, b, n, PROPERTY_ViewMode, !n.isEmpty()); }
void SETPROPERTY_Prefix(bool d, bool b, QString n){ SETPROPERTY_QString(d, b, n, PROPERTY_Prefix, !n.isEmpty()); }
void SETPROPERTY_Suffix(bool d, bool b, QString n){ SETPROPERTY_QString(d, b, n, PROPERTY_Suffix, !n.isEmpty()); }

void SETPROPERTY_TickPosition(bool d, bool b, QString n){ SETPROPERTY_QString(d, b, n, PROPERTY_TickPosition, !n.isEmpty()); }
void SETPROPERTY_InvertedAppearance(bool d, bool b, bool n){ SETPROPERTY_Boolean(d, b, n, PROPERTY_InvertedAppearance, n == true); }
void SETPROPERTY_InvertedControls(bool d, bool b, bool n){ SETPROPERTY_Boolean(d, b, n, PROPERTY_InvertedControls, n == true); }
void SETPROPERTY_Tracking(bool d, bool b, bool n){ SETPROPERTY_Boolean(d, b, n, PROPERTY_Tracking, n != true); }
void SETPROPERTY_TickInterval(bool d, bool b, t_integer n){  SETPROPERTY_Integer(d, b, n, PROPERTY_TickInterval, n != 0); }
void SETPROPERTY_PageStep(bool d, bool b, t_integer n){  SETPROPERTY_Integer(d, b, n, PROPERTY_PageStep, n != 0); }
void SETPROPERTY_SingleStep(bool d, bool b, t_integer n){  SETPROPERTY_Integer(d, b, n, PROPERTY_SingleStep, n != 0); }


void SETPROPERTY_ActionId(bool d, bool b, QString n){ SETPROPERTY_QString(d, b, n, PROPERTY_ActionId, !n.isEmpty()); }
void SETPROPERTY_Description(bool d, bool b, QString n){ SETPROPERTY_QString(d, b, n, PROPERTY_Description, !n.isEmpty()); }

void SETPROPERTY_MoveOnMouseDrag(bool d, bool b, bool n){ SETPROPERTY_Boolean(d, b, n, PROPERTY_MoveOnMouseDrag, n == true); }
void SETPROPERTY_MouseTracking(bool d, bool b, bool n){ SETPROPERTY_Boolean(d, b, n, PROPERTY_MouseTracking, n == true); }

void SETPROPERTY_DrawOnPaint(bool d, bool b, bool n){ SETPROPERTY_Boolean(d, b, n, PROPERTY_DrawOnPaint, n != true); }
void SETPROPERTY_SoundOnEvent(bool d, bool b, QString n){ SETPROPERTY_QString(d, b, n, PROPERTY_SoundOnEvent, !n.isEmpty()); }
void SETPROPERTY_CursorAnimation(bool d, bool b, QString n){ SETPROPERTY_QString(d, b, n, PROPERTY_CursorAnimation, !n.isEmpty()); }

void SETPROPERTY_Brightness(bool d, bool b, t_integer n){  SETPROPERTY_Integer(d, b, n, PROPERTY_Brightness, n != 0); }
void SETPROPERTY_Contrast(bool d, bool b, t_integer n){  SETPROPERTY_Integer(d, b, n, PROPERTY_Contrast, n != 0); }
void SETPROPERTY_Hue(bool d, bool b, t_integer n){  SETPROPERTY_Integer(d, b, n, PROPERTY_Hue, n != 0); }
void SETPROPERTY_Saturation(bool d, bool b, t_integer n){  SETPROPERTY_Integer(d, b, n, PROPERTY_Saturation, n != 0); }
void SETPROPERTY_ScaleMode(bool d, bool b, QString n){  SETPROPERTY_QString(d, b, n, PROPERTY_ScaleMode, !n.isEmpty()); }
void SETPROPERTY_AspectRatio(bool d, bool b, QString n){  SETPROPERTY_QString(d, b, n, PROPERTY_AspectRatio, !n.isEmpty()); }

void SETPROPERTY_TransitionTime(bool d, bool b, t_integer n){  SETPROPERTY_Integer(d, b, n, PROPERTY_TransitionTime, n != 0); }
void SETPROPERTY_Muted(bool d, bool b, bool n){ SETPROPERTY_Boolean(d, b, n, PROPERTY_Muted); }
void SETPROPERTY_Volume(bool d, bool b, t_integer n){  SETPROPERTY_Integer(d, b, n, PROPERTY_Volume, n != 0); }
void SETPROPERTY_PrefinishMark(bool d, bool b, t_integer n){  SETPROPERTY_Integer(d, b, n, PROPERTY_PrefinishMark, n != 0); }
void SETPROPERTY_Tick(bool d, bool b, t_integer n){  SETPROPERTY_Integer(d, b, n, PROPERTY_Tick, n != 0); }

void SETPROPERTY_OnTick(bool d, bool b, bool n){ SETPROPERTY_Boolean(d, b, n, PROPERTY_OnTick); }
void SETPROPERTY_OnStateChanged(bool d, bool b, bool n){ SETPROPERTY_Boolean(d, b, n, PROPERTY_OnStateChanged); }
void SETPROPERTY_OnAboutToFinish(bool d, bool b, bool n){ SETPROPERTY_Boolean(d, b, n, PROPERTY_OnAboutToFinish); }
void SETPROPERTY_OnFinished(bool d, bool b, bool n){ SETPROPERTY_Boolean(d, b, n, PROPERTY_OnFinished); }
void SETPROPERTY_OnMutedChanged(bool d, bool b, bool n){ SETPROPERTY_Boolean(d, b, n, PROPERTY_OnMutedChanged); }
void SETPROPERTY_OnVolumeChanged(bool d, bool b, bool n){ SETPROPERTY_Boolean(d, b, n, PROPERTY_OnVolumeChanged); }
void SETPROPERTY_OnPlayingTitleChanged(bool d, bool b, bool n){ SETPROPERTY_Boolean(d, b, n, PROPERTY_OnPlayingTitleChanged); }
void SETPROPERTY_OnBufferStatus(bool d, bool b, bool n){ SETPROPERTY_Boolean(d, b, n, PROPERTY_OnBufferStatus); }
void SETPROPERTY_OnTotalTimeChanged(bool d, bool b, bool n){ SETPROPERTY_Boolean(d, b, n, PROPERTY_OnTotalTimeChanged); }


void SETPROPERTY_ContextMenu(bool d, bool b, QString n){  SETPROPERTY_QString(d, b, n, PROPERTY_ContextMenu, !n.isEmpty()); }
void SETPROPERTY_PortName(bool d, bool b, QString n){  SETPROPERTY_QString(d, b, n, PROPERTY_PortName, !n.isEmpty()); }
void SETPROPERTY_BaudRate(bool d, bool b, QString n){  SETPROPERTY_QString(d, b, n, PROPERTY_BaudRate, !n.isEmpty()); }
void SETPROPERTY_DataBits(bool d, bool b, QString n){  SETPROPERTY_QString(d, b, n, PROPERTY_DataBits, !n.isEmpty()); }
void SETPROPERTY_Parity(bool d, bool b, QString n){  SETPROPERTY_QString(d, b, n, PROPERTY_Parity, !n.isEmpty()); }
void SETPROPERTY_FlowControl(bool d, bool b, QString n){  SETPROPERTY_QString(d, b, n, PROPERTY_FlowControl, !n.isEmpty()); }
void SETPROPERTY_StopBits(bool d, bool b, QString n){  SETPROPERTY_QString(d, b, n, PROPERTY_StopBits, !n.isEmpty()); }
void SETPROPERTY_TimeOutMillisec(bool d, bool b, int n){ SETPROPERTY_Integer(d, b, n, PROPERTY_TimeoutMillisec, n != 0); }
void SETPROPERTY_PollingInterval(bool d, bool b, int n){ SETPROPERTY_Integer(d, b, n, PROPERTY_PollingInterval, n != 0); }


void SETPROPERTY_Dock(bool d, bool b, QString n){  SETPROPERTY_QString(d, b, n, PROPERTY_Dock, !n.isEmpty()); }
void SETPROPERTY_SelectionMode(bool d, bool b, QString n){  SETPROPERTY_QString(d, b, n, PROPERTY_SelectionMode, !n.isEmpty()); }
void SETPROPERTY_Null(bool d, bool b, bool n){ SETPROPERTY_Boolean(d, b, n, PROPERTY_Null); }
void SETPROPERTY_Index(bool d, bool b, bool n){ SETPROPERTY_Boolean(d, b, n, PROPERTY_Index); }
void SETPROPERTY_AlternatingRowColors(bool d, bool b, bool n){ SETPROPERTY_Boolean(d, b, n, PROPERTY_AlternatingRowColors, n != false); }
void SETPROPERTY_Checked(bool d, bool b, bool n){ SETPROPERTY_Boolean(d, b, n, PROPERTY_Checked, n != false); }
void SETPROPERTY_CheckableExclusive(bool d, bool b, bool n){ SETPROPERTY_Boolean(d, b, n, PROPERTY_CheckableExclusive, n != false); }

void SETPROPERTY_RootIsDecorated(bool d, bool b, bool n){ SETPROPERTY_Boolean(d, b, n, PROPERTY_RootIsDecorated, n != false); }

void SETPROPERTY_OnPrint(bool d, bool b, bool n){ SETPROPERTY_Boolean(d, b, n, PROPERTY_OnPrint); }

void SETPROPERTY_Comment1Begin(bool d, bool b, QString n){  SETPROPERTY_QString(d, b, n, PROPERTY_Comment1Begin, !n.isEmpty()); }
void SETPROPERTY_Comment1End(bool d, bool b, QString n){  SETPROPERTY_QString(d, b, n, PROPERTY_Comment1End, !n.isEmpty()); }
void SETPROPERTY_Comment2Begin(bool d, bool b, QString n){  SETPROPERTY_QString(d, b, n, PROPERTY_Comment2Begin, !n.isEmpty()); }
//void SETPROPERTY_Comment2End(bool d, bool b, QString n){  SETPROPERTY_QString(d, b, n, PROPERTY_Comment2End, !n.isEmpty()); }
void SETPROPERTY_Keywords(bool d, bool b, QString n){  SETPROPERTY_QString(d, b, n, PROPERTY_Keywords, !n.isEmpty()); }
void SETPROPERTY_Commands(bool d, bool b, QString n){  SETPROPERTY_QString(d, b, n, PROPERTY_Commands, !n.isEmpty()); }
void SETPROPERTY_CommentColor(bool d, bool b, QString n){  SETPROPERTY_QString(d, b, n, PROPERTY_CommentColor, !n.isEmpty()); }
void SETPROPERTY_KeywordColor(bool d, bool b, QString n){  SETPROPERTY_QString(d, b, n, PROPERTY_KeywordColor, !n.isEmpty()); }
void SETPROPERTY_CommandColor(bool d, bool b, QString n){  SETPROPERTY_QString(d, b, n, PROPERTY_CommandColor, !n.isEmpty()); }

void SETPROPERTY_SQL(bool d, bool b, QString n){  SETPROPERTY_QString(d, b, n, PROPERTY_SQL, !n.isEmpty()); }

void SETPROPERTY_SQLName(bool d, bool b, QString n){  SETPROPERTY_QString(d, b, n, PROPERTY_SQLName, !n.isEmpty()); }
void SETPROPERTY_SQLRelation(bool d, bool b, QString n){  SETPROPERTY_QString(d, b, n, PROPERTY_SQLRelation, !n.isEmpty()); }
void SETPROPERTY_SQLInsert(bool d, bool b, bool n){ SETPROPERTY_Boolean(d, b, n, PROPERTY_SQLInsert, n == false); }
void SETPROPERTY_SQLUpdate(bool d, bool b, bool n){ SETPROPERTY_Boolean(d, b, n, PROPERTY_SQLUpdate, n == false); }
void SETPROPERTY_SQLDelete(bool d, bool b, bool n){ SETPROPERTY_Boolean(d, b, n, PROPERTY_SQLDelete, n == false); }

void SETPROPERTY_TableViewCaption(bool d, bool b, QString n){  SETPROPERTY_QString(d, b, n, PROPERTY_TableViewCaption, !n.isEmpty()); }
void SETPROPERTY_TableViewSort(bool d, bool b, QString n){  SETPROPERTY_QString(d, b, n, PROPERTY_TableViewSort, !n.isEmpty()); }
void SETPROPERTY_TableViewFilter(bool d, bool b, QString n){  SETPROPERTY_QString(d, b, n, PROPERTY_TableViewFilter, !n.isEmpty()); }
void SETPROPERTY_TableViewWidth(bool d, bool b, t_integer n){  SETPROPERTY_Integer(d, b, n, PROPERTY_TableViewWidth, n != 0); }
void SETPROPERTY_TableViewVisible(bool d, bool b, t_boolean n){  SETPROPERTY_Boolean(d, b, n, PROPERTY_TableViewVisible, n == false); }
void SETPROPERTY_TableViewOrder(bool d, bool b, t_integer n){  SETPROPERTY_Integer(d, b, n, PROPERTY_TableViewOrder, n != 0); }


void SETPROPERTY_Pages(bool d, bool b, QString n){  SETPROPERTY_QString(d, b, n, PROPERTY_Pages, !n.isEmpty()); }

void SETPROPERTY_ParentForm(bool d, bool b, QString n){  SETPROPERTY_QString(d, b, n, PROPERTY_ParentForm); }
void SETPROPERTY_ParentControl(bool d, bool b, QString n){  SETPROPERTY_QString(d, b, n, PROPERTY_ParentControl); }


void SETPROPERTY_EnterImage(bool d, bool b, QString n)
{
  SETPROPERTY_QString(d, b, n, PROPERTY_EnterImage, !n.isEmpty());
}

void SETPROPERTY_ExitImage(bool d, bool b, QString n)
{
  SETPROPERTY_QString(d, b, n, PROPERTY_ExitImage, !n.isEmpty());
}

void SETPROPERTY_DisabledImage(bool d, bool b, QString n)
{
  SETPROPERTY_QString(d, b, n, PROPERTY_DisabledImage, !n.isEmpty());
}

void SETPROPERTY_CheckEnterImage(bool d, bool b, QString n)
{
  SETPROPERTY_QString(d, b, n, PROPERTY_CheckEnterImage, !n.isEmpty());
}

void SETPROPERTY_CheckExitImage(bool d, bool b, QString n)
{
  SETPROPERTY_QString(d, b, n, PROPERTY_CheckExitImage, !n.isEmpty());
}

void SETPROPERTY_CheckDisabledImage(bool d, bool b, QString n)
{
  SETPROPERTY_QString(d, b, n, PROPERTY_CheckDisabledImage, !n.isEmpty());
}

void SETPROPERTY_EnterSound(bool d, bool b, QString n)
{
  SETPROPERTY_QString(d, b, n, PROPERTY_EnterSound, !n.isEmpty());
}

void SETPROPERTY_ExitSound(bool d, bool b, QString n)
{
  SETPROPERTY_QString(d, b, n, PROPERTY_ExitSound, !n.isEmpty());
}

void SETPROPERTY_Menu(bool d, bool b, bool n)
{
  SETPROPERTY_Boolean(d, b, n, PROPERTY_Menu);
}

void SETPROPERTY_Interval(bool d, bool b, int n)
{
  SETPROPERTY_Integer(d, b, n, PROPERTY_Interval, n != 0);
}

void SETPROPERTY_StringValue(bool d, bool b, QString n)
{
  SETPROPERTY_QString(d, b, n, PROPERTY_StringValue, !n.isEmpty());
}

void SETPROPERTY_InputMask(bool d, bool b, QString n)
{
  SETPROPERTY_QString(d, b, n, PROPERTY_InputMask, !n.isEmpty());
}

void SETPROPERTY_Mask(bool d, bool b, QString n)
{
  SETPROPERTY_QString(d, b, n, PROPERTY_Mask, !n.isEmpty());
}
void SETPROPERTY_OpenAtStartup(bool d, bool b, bool n)
{
  SETPROPERTY_Boolean(d, b, n, PROPERTY_OpenAtStartup, n != false);
}

void SETPROPERTY_EventOnOpen(bool d, bool b, bool n)
{
  SETPROPERTY_Boolean(d, b, n, PROPERTY_EventOnOpen, n != false);
}

void SETPROPERTY_Default(bool d, bool b, bool n)
{
  SETPROPERTY_Boolean(d, b, n, PROPERTY_Default, n != false);
}

void SETPROPERTY_Checkable(bool d, bool b, bool n)
{
  SETPROPERTY_Boolean(d, b, n, PROPERTY_Checkable, n != false);
}

void SETPROPERTY_AcceptRichText(bool d, bool b, bool n)
{
  SETPROPERTY_Boolean(d, b, n, PROPERTY_AcceptRichText, n == false);
}

void SETPROPERTY_AutoDefault(bool d, bool b, bool n)
{
  SETPROPERTY_Boolean(d, b, n, PROPERTY_AutoDefault, n != false);
}

void SETPROPERTY_BooleanValue(bool d, bool b, bool n)
{
  SETPROPERTY_Boolean(d, b, n, PROPERTY_BooleanValue, n != false);
}

// EVENT

//void SETPROPERTY_OnCursorPositionChanged(bool d, bool b, bool n){ SETPROPERTY_Boolean(d, b, n, PROPERTY_OnCursorPositionChanged); }
void SETPROPERTY_OnEditingFinished(bool d, bool b, bool n){ SETPROPERTY_Boolean(d, b, n, PROPERTY_OnEditingFinished); }
void SETPROPERTY_OnReturnPressed(bool d, bool b, bool n){ SETPROPERTY_Boolean(d, b, n, PROPERTY_OnReturnPressed); }
void SETPROPERTY_OnSelectionChanged(bool d, bool b, bool n){ SETPROPERTY_Boolean(d, b, n, PROPERTY_OnSelectionChanged); }
void SETPROPERTY_OnTextChanged(bool d, bool b, bool n){ SETPROPERTY_Boolean(d, b, n, PROPERTY_OnTextChanged); }
void SETPROPERTY_OnTextEdited(bool d, bool b, bool n){ SETPROPERTY_Boolean(d, b, n, PROPERTY_OnTextEdited); }

void SETPROPERTY_OnPage(bool d, bool b, bool n){ SETPROPERTY_Boolean(d, b, n, PROPERTY_OnPage); }
void SETPROPERTY_OnLinkHovered(bool d, bool b, bool n){ SETPROPERTY_Boolean(d, b, n, PROPERTY_OnLinkHovered); }
void SETPROPERTY_OnLoadFinished(bool d, bool b, bool n){ SETPROPERTY_Boolean(d, b, n, PROPERTY_OnLoadFinished); }
void SETPROPERTY_OnLoadProgress(bool d, bool b, bool n){ SETPROPERTY_Boolean(d, b, n, PROPERTY_OnLoadProgress); }
void SETPROPERTY_OnLoadStarted(bool d, bool b, bool n){ SETPROPERTY_Boolean(d, b, n, PROPERTY_OnLoadStarted); }
void SETPROPERTY_OnWindowCloseRequested(bool d, bool b, bool n){ SETPROPERTY_Boolean(d, b, n, PROPERTY_OnWindowCloseRequested); }

void SETPROPERTY_OnSingleShot(bool d, bool b, bool n){ SETPROPERTY_Boolean(d, b, n, PROPERTY_OnSingleShot); }
void SETPROPERTY_OnEvent(bool d, bool b, bool n){ SETPROPERTY_Boolean(d, b, n, PROPERTY_OnEvent); }
void SETPROPERTY_OnAction(bool d, bool b, bool n){ SETPROPERTY_Boolean(d, b, n, PROPERTY_OnAction); }
void SETPROPERTY_OnCursorPositionChanged(bool d, bool b, bool n){ SETPROPERTY_Boolean(d, b, n, PROPERTY_OnCursorPositionChanged); }


void SETPROPERTY_OnDirty(bool d, bool b, bool n){ SETPROPERTY_Boolean(d, b, n, PROPERTY_OnDirty); }
void SETPROPERTY_OnAddNew(bool d, bool b, bool n){ SETPROPERTY_Boolean(d, b, n, PROPERTY_OnAddNew); }
void SETPROPERTY_OnQuery(bool d, bool b, bool n){ SETPROPERTY_Boolean(d, b, n, PROPERTY_OnQuery); }

void SETPROPERTY_OnOpen(bool d, bool b, bool n){ SETPROPERTY_Boolean(d, b, n, PROPERTY_OnOpen); }
void SETPROPERTY_OnClose(bool d, bool b, bool n){ SETPROPERTY_Boolean(d, b, n, PROPERTY_OnClose); }
void SETPROPERTY_OnGoTo(bool d, bool b, bool n){ SETPROPERTY_Boolean(d, b, n, PROPERTY_OnGoTo); }
void SETPROPERTY_OnBeforeInsert(bool d, bool b, bool n){ SETPROPERTY_Boolean(d, b, n, PROPERTY_OnBeforeInsert); }
void SETPROPERTY_OnBeforeDelete(bool d, bool b, bool n){ SETPROPERTY_Boolean(d, b, n, PROPERTY_OnBeforeDelete); }
void SETPROPERTY_OnDragExit(bool d, bool b, bool n){ SETPROPERTY_Boolean(d, b, n, PROPERTY_OnDragExit); }
void SETPROPERTY_OnPaint(bool d, bool b, bool n){ SETPROPERTY_Boolean(d, b, n, PROPERTY_OnPaint); }

void SETPROPERTY_OnTimer(bool d, bool b, bool n){ SETPROPERTY_Boolean(d, b, n, PROPERTY_OnTimer); }

void SETPROPERTY_OnMove(bool d, bool b, bool n){ SETPROPERTY_Boolean(d, b, n, PROPERTY_OnMove); }
void SETPROPERTY_OnHide(bool d, bool b, bool n){ SETPROPERTY_Boolean(d, b, n, PROPERTY_OnHide); }
void SETPROPERTY_OnShow(bool d, bool b, bool n){ SETPROPERTY_Boolean(d, b, n, PROPERTY_OnShow); }
void SETPROPERTY_OnEnabled(bool d, bool b, bool n){ SETPROPERTY_Boolean(d, b, n, PROPERTY_OnEnabled); }
void SETPROPERTY_OnDisabled(bool d, bool b, bool n){ SETPROPERTY_Boolean(d, b, n, PROPERTY_OnDisabled); }
void SETPROPERTY_OnMouseWheel(bool d, bool b, bool n){ SETPROPERTY_Boolean(d, b, n, PROPERTY_OnMouseWheel); }
void SETPROPERTY_OnMultiPageShow(bool d, bool b, bool n){ SETPROPERTY_Boolean(d, b, n, PROPERTY_OnMultiPageShow); }
void SETPROPERTY_OnScroll(bool d, bool b, bool n){ SETPROPERTY_Boolean(d, b, n, PROPERTY_OnScroll); }


void SETPROPERTY_OnContextMenu(bool d, bool b, bool n){ SETPROPERTY_Boolean(d, b, n, PROPERTY_OnContextMenu); }
void SETPROPERTY_OnDrop(bool d, bool b, bool n){ SETPROPERTY_Boolean(d, b, n, PROPERTY_OnDrop); }
void SETPROPERTY_OnDragMove(bool d, bool b, bool n){ SETPROPERTY_Boolean(d, b, n, PROPERTY_OnDragMove); }
void SETPROPERTY_OnDragEnter(bool d, bool b, bool n){ SETPROPERTY_Boolean(d, b, n, PROPERTY_OnDragEnter); }



void SETPROPERTY_OnClick(bool d, bool b, bool n)
{
  SETPROPERTY_Boolean(d, b, n, PROPERTY_OnClick);
}

void SETPROPERTY_OnDblClick(bool d, bool b, bool n)
{
  SETPROPERTY_Boolean(d, b, n, PROPERTY_OnDblClick);
}

void SETPROPERTY_OnMouseDown(bool d, bool b, bool n)
{
  SETPROPERTY_Boolean(d, b, n, PROPERTY_OnMouseDown);
}

void SETPROPERTY_OnMouseUp(bool d, bool b, bool n)
{
  SETPROPERTY_Boolean(d, b, n, PROPERTY_OnMouseUp);
}

void SETPROPERTY_OnMouseMove(bool d, bool b, bool n)
{
  SETPROPERTY_Boolean(d, b, n, PROPERTY_OnMouseMove);
}

void SETPROPERTY_OnGotFocus(bool d, bool b, bool n)
{
  SETPROPERTY_Boolean(d, b, n, PROPERTY_OnGotFocus);
}

void SETPROPERTY_OnLostFocus(bool d, bool b, bool n)
{
  SETPROPERTY_Boolean(d, b, n, PROPERTY_OnLostFocus);
}

void SETPROPERTY_OnEnter(bool d, bool b, bool n)
{
  SETPROPERTY_Boolean(d, b, n, PROPERTY_OnEnter);
}

void SETPROPERTY_OnExit(bool d, bool b, bool n)
{
  SETPROPERTY_Boolean(d, b, n, PROPERTY_OnExit);
}

void SETPROPERTY_OnKeyDown(bool d, bool b, bool n)
{
  SETPROPERTY_Boolean(d, b, n, PROPERTY_OnKeyDown);
}

void SETPROPERTY_OnKeyUp(bool d, bool b, bool n)
{
  SETPROPERTY_Boolean(d, b, n, PROPERTY_OnKeyUp);
}

void SETPROPERTY_OnKeyPress(bool d, bool b, bool n)
{
  SETPROPERTY_Boolean(d, b, n, PROPERTY_OnKeyPress);
}

void SETPROPERTY_OnBeforeUpdate(bool d, bool b, bool n)
{
  SETPROPERTY_Boolean(d, b, n, PROPERTY_OnBeforeUpdate);
}


void SETPROPERTY_OnResize(bool d, bool b, bool n)
{
  SETPROPERTY_Boolean(d, b, n, PROPERTY_OnResize);
}





public slots:

void settingform();

void SLOTPROPERTY_Group();
void SLOTPROPERTY_Background();
void SLOTPROPERTY_BackgroundStyle();
void SLOTPROPERTY_Palette();
void SLOTPROPERTY_MinimumWidth();
void SLOTPROPERTY_MinimumHeight();
void SLOTPROPERTY_MaximumWidth();
void SLOTPROPERTY_MaximumHeight();
void SLOTPROPERTY_StopOnClose();
void SLOTPROPERTY_DockTitleVisible();
void SLOTPROPERTY_DockOrder();

void SLOTPROPERTY_DockSplit();
void SLOTPROPERTY_ShowMode();



void SLOTPROPERTY_DockWidth();
void SLOTPROPERTY_DockHeight();

void SLOTPROPERTY_ScrollX();
void SLOTPROPERTY_ScrollY();
void SLOTPROPERTY_ScrollWidth();
void SLOTPROPERTY_ScrollHeight();


void SLOTPROPERTY_MultiPageHeight();
void SLOTPROPERTY_MultiPageBorderTop();
void SLOTPROPERTY_MultiPageBorderBottom();
void SLOTPROPERTY_MultiPageBorderLeft();
void SLOTPROPERTY_MultiPageBorderRight();

void SLOTPROPERTY_BorderTop();
void SLOTPROPERTY_BorderBottom();
void SLOTPROPERTY_BorderLeft();
void SLOTPROPERTY_BorderRight();
void SLOTPROPERTY_CSV();
void SLOTPROPERTY_Tag();
void SLOTPROPERTY_ArrowType();
void SLOTPROPERTY_PopupMode();
void SLOTPROPERTY_ToolBarRole();
void SLOTPROPERTY_MenuBarRole();
void SLOTPROPERTY_Data();
void SLOTPROPERTY_TableView();
void SLOTPROPERTY_BoxIndex();
void SLOTPROPERTY_BoxX();
void SLOTPROPERTY_BoxY();
void SLOTPROPERTY_SplitIndex();

void SLOTPROPERTY_Scale();
void SLOTPROPERTY_DragDrop();
void SLOTPROPERTY_FocusPolicy();
void SLOTPROPERTY_FocusProxy();
void SLOTPROPERTY_FocusOrder();

void SLOTPROPERTY_FontName();
void SLOTPROPERTY_FontSize();
void SLOTPROPERTY_FontBold();
void SLOTPROPERTY_FontItalic();
void SLOTPROPERTY_FontUnderline();
void SLOTPROPERTY_FontColor();

void SLOTPROPERTY_StatusTip();
void SLOTPROPERTY_ToolTip();
void SLOTPROPERTY_StyleSheet();
void SLOTPROPERTY_WhatsThis();

void SLOTPROPERTY_Flag();
void SLOTPROPERTY_Layout();

void SLOTPROPERTY_Dock();
void SLOTPROPERTY_SQLControls();
//void SLOTPROPERTY_IconCaption();

void SLOTPROPERTY_Modal();
void SLOTPROPERTY_Opacity();
void SLOTPROPERTY_TimerInterval();

void SLOTPROPERTY_Shadow();
void SLOTPROPERTY_Shape();
void SLOTPROPERTY_OpenLinks();

void SLOTPROPERTY_Icon();
void SLOTPROPERTY_InputControl();
void SLOTPROPERTY_Space();
void SLOTPROPERTY_Border();

void SLOTPROPERTY_Flat();
void SLOTPROPERTY_Flip();
void SLOTPROPERTY_Key();

void SLOTPROPERTY_IntegerMaximum();
void SLOTPROPERTY_IntegerMinimum();
void SLOTPROPERTY_Completer();
void SLOTPROPERTY_ValidatorDouble();
void SLOTPROPERTY_ValidatorInteger();
void SLOTPROPERTY_ValidatorRegEx();
void SLOTPROPERTY_ValidatorRegEx2();

void SLOTPROPERTY_DoubleEntry();
void SLOTPROPERTY_InsertPolicy();
void SLOTPROPERTY_Editable();
void SLOTPROPERTY_MaximumVisible();

void SLOTPROPERTY_Sorted();

void SLOTPROPERTY_StringMaximum();
void SLOTPROPERTY_StringMinimum();
void SLOTPROPERTY_Format();

void SLOTPROPERTY_PopUp();

void SLOTPROPERTY_ScrollBar();


void SLOTPROPERTY_MouseDownImage();
void SLOTPROPERTY_MouseUpImage();
void SLOTPROPERTY_EnabledImage();

void SLOTPROPERTY_CheckMouseDownImage();
void SLOTPROPERTY_CheckMouseUpImage();
void SLOTPROPERTY_CheckEnabledImage();

void SLOTPROPERTY_MouseDownSound();
void SLOTPROPERTY_MouseUpSound();

void SLOTPROPERTY_HomeURL();




void SLOTPROPERTY_Name();

void SLOTPROPERTY_X();
void SLOTPROPERTY_Y();
void SLOTPROPERTY_Width();
void SLOTPROPERTY_Height();

void SLOTPROPERTY_IntegerValue();
void SLOTPROPERTY_Enabled();
void SLOTPROPERTY_Visible();
void SLOTPROPERTY_Resizable();
void SLOTPROPERTY_ResizableSmaller();
void SLOTPROPERTY_ResizableBigger();


void SLOTPROPERTY_Separator();
void SLOTPROPERTY_WordWrap();
void SLOTPROPERTY_ReadOnly();
void SLOTPROPERTY_Cursor();

void SLOTPROPERTY_Caption();
void SLOTPROPERTY_Alignment();
void SLOTPROPERTY_EchoMode();
void SLOTPROPERTY_Feature();
void SLOTPROPERTY_Orientation();

void SLOTPROPERTY_OnCurrentItemChanged();
void SLOTPROPERTY_OnItemActivated();
void SLOTPROPERTY_OnItemChanged();
void SLOTPROPERTY_OnItemClicked();
void SLOTPROPERTY_OnItemCollapsed();
void SLOTPROPERTY_OnItemDoubleClicked();
void SLOTPROPERTY_OnItemEntered();
void SLOTPROPERTY_OnItemExpanded();
void SLOTPROPERTY_OnItemPressed();
void SLOTPROPERTY_OnItemSelectionChanged();

void SLOTPROPERTY_OnDockMove();
void SLOTPROPERTY_OnDockShow();
void SLOTPROPERTY_OnDockHide();
void SLOTPROPERTY_OnDockFloating();
void SLOTPROPERTY_OnDockNotFloating();




// PROPERTY
void SLOTPROPERTY_Prefix();
void SLOTPROPERTY_Suffix();

void SLOTPROPERTY_TickPosition();
void SLOTPROPERTY_InvertedAppearance();
void SLOTPROPERTY_InvertedControls();
void SLOTPROPERTY_Tracking();
void SLOTPROPERTY_TickInterval();
void SLOTPROPERTY_PageStep();
void SLOTPROPERTY_SingleStep();



void SLOTPROPERTY_ViewMode();
void SLOTPROPERTY_Description();
void SLOTPROPERTY_ActionId();
void SLOTPROPERTY_MoveOnMouseDrag();
void SLOTPROPERTY_MouseTracking();

void SLOTPROPERTY_DrawOnPaint();
void SLOTPROPERTY_SoundOnEvent();
void SLOTPROPERTY_CursorAnimation();


void SLOTPROPERTY_RootIsDecorated();
void SLOTPROPERTY_Brightness();
void SLOTPROPERTY_Contrast();
void SLOTPROPERTY_Hue();
void SLOTPROPERTY_Saturation();
void SLOTPROPERTY_ScaleMode();
void SLOTPROPERTY_AspectRatio();
void SLOTPROPERTY_TransitionTime();
void SLOTPROPERTY_Muted();
void SLOTPROPERTY_Volume();
void SLOTPROPERTY_PrefinishMark();
void SLOTPROPERTY_Tick();

void SLOTPROPERTY_OnTick();
void SLOTPROPERTY_OnStateChanged();
void SLOTPROPERTY_OnAboutToFinish();
void SLOTPROPERTY_OnFinished();
void SLOTPROPERTY_OnMutedChanged();
void SLOTPROPERTY_OnVolumeChanged();
void SLOTPROPERTY_OnPlayingTitleChanged();
void SLOTPROPERTY_OnBufferStatus();
void SLOTPROPERTY_OnTotalTimeChanged();

void SLOTPROPERTY_ContextMenu();
void SLOTPROPERTY_PortName();
void SLOTPROPERTY_BaudRate();
void SLOTPROPERTY_DataBits();
void SLOTPROPERTY_Parity();
void SLOTPROPERTY_FlowControl();
void SLOTPROPERTY_StopBits();
void SLOTPROPERTY_TimeoutMillisec();
void SLOTPROPERTY_PollingInterval();

void SLOTPROPERTY_SelectionMode();
void SLOTPROPERTY_Null();
void SLOTPROPERTY_Index();
void SLOTPROPERTY_AlternatingRowColors();
void SLOTPROPERTY_Checked();
void SLOTPROPERTY_CheckableExclusive();
void SLOTPROPERTY_OnPrint();

void SLOTPROPERTY_Comment1Begin();
void SLOTPROPERTY_Comment1End();
void SLOTPROPERTY_Comment2Begin();
//void SLOTPROPERTY_Comment2End();
void SLOTPROPERTY_Keywords();
void SLOTPROPERTY_Commands();
void SLOTPROPERTY_CommentColor();
void SLOTPROPERTY_KeywordColor();
void SLOTPROPERTY_CommandColor();


void SLOTPROPERTY_SQL();

void SLOTPROPERTY_SQLName();
void SLOTPROPERTY_SQLRelation();
void SLOTPROPERTY_TableViewCaption();
void SLOTPROPERTY_TableViewSort();
void SLOTPROPERTY_TableViewFilter();
void SLOTPROPERTY_TableViewWidth();
void SLOTPROPERTY_TableViewVisible();
void SLOTPROPERTY_TableViewOrder();

void SLOTPROPERTY_SQLInsert();
void SLOTPROPERTY_SQLUpdate();
void SLOTPROPERTY_SQLDelete();





void SLOTPROPERTY_Pages();

void SLOTPROPERTY_ParentForm();
void SLOTPROPERTY_ParentControl();
void SLOTPROPERTY_TabIndex();
void SLOTPROPERTY_ParentIndex();


void SLOTPROPERTY_OpenAtStartup();


void SLOTPROPERTY_EventOnOpen();
void SLOTPROPERTY_Default();
void SLOTPROPERTY_Checkable();
void SLOTPROPERTY_AcceptRichText();
void SLOTPROPERTY_AutoDefault();
void SLOTPROPERTY_BooleanValue();
void SLOTPROPERTY_StringValue();
void SLOTPROPERTY_InputMask();
void SLOTPROPERTY_Mask();



void SLOTPROPERTY_EnterImage();//bool b = false); void SLOTPROPERTY_EnterImage2();
void SLOTPROPERTY_ExitImage();//bool b = false); void SLOTPROPERTY_ExitImage2();
void SLOTPROPERTY_DisabledImage();//bool b = false); void SLOTPROPERTY_DisabledImage2();

void SLOTPROPERTY_CheckEnterImage();//bool b = false); void SLOTPROPERTY_CheckEnterImage2();
void SLOTPROPERTY_CheckExitImage();//bool b = false); void SLOTPROPERTY_CheckExitImage2();
void SLOTPROPERTY_CheckDisabledImage();//bool b = false); void SLOTPROPERTY_CheckDisabledImage2();

void SLOTPROPERTY_EnterSound();
void SLOTPROPERTY_ExitSound();

void SLOTPROPERTY_Menu();

void SLOTPROPERTY_Interval();

// EVENT




//void SLOTPROPERTY_OnCursorPositionChanged();
void SLOTPROPERTY_OnEditingFinished();
void SLOTPROPERTY_OnReturnPressed();
void SLOTPROPERTY_OnSelectionChanged();
void SLOTPROPERTY_OnTextChanged();
void SLOTPROPERTY_OnTextEdited();


void SLOTPROPERTY_OnPage();
void SLOTPROPERTY_OnLinkHovered();
void SLOTPROPERTY_OnLoadFinished();
void SLOTPROPERTY_OnLoadProgress();
void SLOTPROPERTY_OnLoadStarted();
void SLOTPROPERTY_OnWindowCloseRequested();

void SLOTPROPERTY_OnSingleShot();
void SLOTPROPERTY_OnEvent();
void SLOTPROPERTY_OnAction();
void SLOTPROPERTY_OnCursorPositionChanged();


void SLOTPROPERTY_OnDirty();
void SLOTPROPERTY_OnAddNew();
void SLOTPROPERTY_OnQuery();

void SLOTPROPERTY_OnOpen();
void SLOTPROPERTY_OnClose();
void SLOTPROPERTY_OnGoTo();
void SLOTPROPERTY_OnBeforeInsert();
void SLOTPROPERTY_OnBeforeDelete();
void SLOTPROPERTY_OnDragExit();
void SLOTPROPERTY_OnPaint();


void SLOTPROPERTY_OnTimer();
void SLOTPROPERTY_OnMove();
void SLOTPROPERTY_OnHide();
void SLOTPROPERTY_OnShow();
void SLOTPROPERTY_OnEnabled();
void SLOTPROPERTY_OnDisabled();
void SLOTPROPERTY_OnContextMenu();
void SLOTPROPERTY_OnMouseWheel();
void SLOTPROPERTY_OnMultiPageShow();
void SLOTPROPERTY_OnScroll();

void SLOTPROPERTY_OnDrop();
void SLOTPROPERTY_OnDragMove();
void SLOTPROPERTY_OnDragEnter();

void SLOTPROPERTY_OnClick();
void SLOTPROPERTY_OnDblClick();
void SLOTPROPERTY_OnMouseDown();
void SLOTPROPERTY_OnMouseUp();
void SLOTPROPERTY_OnMouseMove();
void SLOTPROPERTY_OnGotFocus();
void SLOTPROPERTY_OnLostFocus();
void SLOTPROPERTY_OnEnter();
void SLOTPROPERTY_OnExit();
void SLOTPROPERTY_OnKeyDown();
void SLOTPROPERTY_OnKeyUp();
void SLOTPROPERTY_OnKeyPress();
void SLOTPROPERTY_OnBeforeUpdate();

void SLOTPROPERTY_OnResize();

private slots:
  void itemSelectionChanged();
  void itemDoubleClicked(QTreeWidgetItem *item, int column);

private:

_property_lineedit *PROPERTY_Group;
_property_colorimageedit *PROPERTY_Background;
_property_choicebox *PROPERTY_BackgroundStyle;
_property_lineedit *PROPERTY_Palette;
_property_lineedit *PROPERTY_MinimumWidth;
_property_lineedit *PROPERTY_MinimumHeight;
_property_lineedit *PROPERTY_MaximumWidth;
_property_lineedit *PROPERTY_MaximumHeight;
_property_lineedit *PROPERTY_CSV;
_property_lineedit *PROPERTY_Tag;

_property_choicebox *PROPERTY_ArrowType;
_property_choicebox *PROPERTY_PopupMode;
_property_choicebox *PROPERTY_ToolBarRole;

_property_choicebox *PROPERTY_MenuBarRole;
_property_lineedit *PROPERTY_Data;
_property_booleancombobox *PROPERTY_TableView;


_property_lineedit *PROPERTY_BoxIndex;
_property_lineedit *PROPERTY_BoxX;
_property_lineedit *PROPERTY_BoxY;
_property_lineedit *PROPERTY_SplitIndex;

_property_booleancombobox *PROPERTY_Scale;
//_property_booleancombobox *PROPERTY_FormCentered;
//_property_booleancombobox *PROPERTY_FormScaled;
_property_booleancombobox *PROPERTY_DragDrop;

_property_choicebox *PROPERTY_FocusPolicy;
_property_lineedit *PROPERTY_FocusProxy;
_property_lineedit *PROPERTY_FocusOrder;

_property_fontedit *PROPERTY_FontName;
_property_listcombobox *PROPERTY_FontSize;

_property_booleancombobox *PROPERTY_FontBold;
_property_booleancombobox *PROPERTY_FontItalic;
_property_booleancombobox *PROPERTY_FontUnderline;

_property_coloredit *PROPERTY_FontColor;

_property_lineedit *PROPERTY_StatusTip;
_property_lineedit *PROPERTY_ToolTip;
_property_lineedit *PROPERTY_StyleSheet;
_property_lineedit *PROPERTY_WhatsThis;

_property_choicebox *PROPERTY_Flag;
_property_choicebox *PROPERTY_Layout;
_property_choicebox *PROPERTY_SQLControls;
//_property_lineedit *PROPERTY_IconCaption;

_property_booleancombobox *PROPERTY_Modal;
_property_listcombobox *PROPERTY_Opacity;
_property_lineedit *PROPERTY_TimerInterval;

_property_booleancombobox *PROPERTY_Shadow;
_property_booleancombobox *PROPERTY_Shape;
_property_booleancombobox *PROPERTY_OpenLinks;

_property_imageedit *PROPERTY_Icon;
_property_lineedit *PROPERTY_InputControl;
_property_lineedit *PROPERTY_Space;
_property_lineedit *PROPERTY_Border;

_property_booleancombobox *PROPERTY_Flat;
_property_booleancombobox *PROPERTY_Flip;
_property_lineedit *PROPERTY_Key;
_property_lineedit *PROPERTY_IntegerMaximum;
_property_lineedit *PROPERTY_IntegerMinimum;
_property_lineedit *PROPERTY_Completer;

_property_booleancombobox *PROPERTY_ValidatorDouble;
_property_booleancombobox *PROPERTY_ValidatorInteger;
_property_lineedit *PROPERTY_ValidatorRegEx;
_property_lineedit *PROPERTY_ValidatorRegEx2;

_property_booleancombobox *PROPERTY_DoubleEntry;
_property_choicebox *PROPERTY_InsertPolicy;
_property_booleancombobox *PROPERTY_Editable;
_property_lineedit *PROPERTY_MaximumVisible;
_property_booleancombobox *PROPERTY_Sorted;

_property_lineedit *PROPERTY_StringMaximum;
_property_lineedit *PROPERTY_StringMinimum;
_property_lineedit *PROPERTY_Format;

_property_booleancombobox *PROPERTY_PopUp;
_property_choicebox *PROPERTY_ScrollBar;

_property_imageedit *PROPERTY_MouseDownImage;
_property_imageedit *PROPERTY_MouseUpImage;
_property_imageedit *PROPERTY_EnabledImage;

_property_imageedit *PROPERTY_CheckMouseDownImage;
_property_imageedit *PROPERTY_CheckMouseUpImage;
_property_imageedit *PROPERTY_CheckEnabledImage;

_property_soundedit *PROPERTY_MouseDownSound;
_property_soundedit *PROPERTY_MouseUpSound;

_property_fileedit *PROPERTY_HomeURL;

_property_lineedit *PROPERTY_Name;
_property_lineedit *PROPERTY_ControlType;
_property_pixeledit *PROPERTY_X;
_property_pixeledit *PROPERTY_Y;
_property_pixeledit *PROPERTY_Width;
_property_pixeledit *PROPERTY_Height;

_property_booleancombobox *PROPERTY_StopOnClose;

_property_booleancombobox *PROPERTY_DockTitleVisible;
_property_lineedit *PROPERTY_DockOrder;

_property_lineedit *PROPERTY_DockSplit;
_property_choicebox *PROPERTY_ShowMode;




_property_pixeledit *PROPERTY_DockWidth;
_property_pixeledit *PROPERTY_DockHeight;

_property_pixeledit *PROPERTY_ScrollX;
_property_pixeledit *PROPERTY_ScrollY;
_property_pixeledit *PROPERTY_ScrollWidth;
_property_pixeledit *PROPERTY_ScrollHeight;

_property_pixeledit *PROPERTY_MultiPageHeight;
_property_pixeledit *PROPERTY_MultiPageBorderTop;
_property_pixeledit *PROPERTY_MultiPageBorderBottom;
_property_pixeledit *PROPERTY_MultiPageBorderLeft;
_property_pixeledit *PROPERTY_MultiPageBorderRight;


_property_pixeledit *PROPERTY_BorderTop;
_property_pixeledit *PROPERTY_BorderBottom;
_property_pixeledit *PROPERTY_BorderLeft;
_property_pixeledit *PROPERTY_BorderRight;

_property_lineedit *PROPERTY_IntegerValue;
_property_booleancombobox *PROPERTY_Enabled;
_property_listcombobox *PROPERTY_Cursor;

_property_listcombobox *PROPERTY_PortName;
_property_listcombobox *PROPERTY_BaudRate;
_property_listcombobox *PROPERTY_DataBits;
_property_listcombobox *PROPERTY_FlowControl;
_property_listcombobox *PROPERTY_Parity;
_property_listcombobox *PROPERTY_StopBits;
_property_lineedit *PROPERTY_TimeoutMillisec;
_property_lineedit *PROPERTY_PollingInterval;



_property_lineedit *PROPERTY_TabIndex;
_property_lineedit *PROPERTY_ParentIndex;
_property_booleancombobox *PROPERTY_Visible;
_property_booleancombobox *PROPERTY_Resizable;
_property_booleancombobox *PROPERTY_ResizableSmaller;
_property_booleancombobox *PROPERTY_ResizableBigger;


_property_booleancombobox *PROPERTY_Separator;
_property_booleancombobox *PROPERTY_WordWrap;
_property_booleancombobox *PROPERTY_ReadOnly;

_property_lineedit *PROPERTY_Caption;
_property_choicebox *PROPERTY_Alignment;
_property_choicebox *PROPERTY_EchoMode;
_property_choicebox *PROPERTY_Feature;
_property_choicebox *PROPERTY_Orientation;

_property_lineedit *PROPERTY_Comment1Begin;
_property_lineedit *PROPERTY_Comment1End;
_property_lineedit *PROPERTY_Comment2Begin;
//_property_lineedit *PROPERTY_Comment2End;
_property_lineedit *PROPERTY_Keywords;
_property_lineedit *PROPERTY_Commands;

_property_coloredit *PROPERTY_CommentColor;
_property_coloredit *PROPERTY_KeywordColor;
_property_coloredit *PROPERTY_CommandColor;


_property_lineedit *PROPERTY_SQLName;
_property_lineedit *PROPERTY_SQLRelation;
_property_lineedit *PROPERTY_TableViewCaption;
_property_lineedit *PROPERTY_TableViewSort;
_property_lineedit *PROPERTY_TableViewFilter;
_property_lineedit *PROPERTY_TableViewWidth;
_property_booleancombobox *PROPERTY_TableViewVisible;
_property_lineedit *PROPERTY_TableViewOrder;


_property_booleancombobox *PROPERTY_SQLInsert;
_property_booleancombobox *PROPERTY_SQLUpdate;
_property_booleancombobox *PROPERTY_SQLDelete;

_property_choicebox *PROPERTY_Dock;
_property_choicebox *PROPERTY_SelectionMode;
_property_booleancombobox *PROPERTY_AlternatingRowColors;

_property_event *PROPERTY_OnCurrentItemChanged;
_property_event *PROPERTY_OnItemActivated;
_property_event *PROPERTY_OnItemChanged;
_property_event *PROPERTY_OnItemClicked;
_property_event *PROPERTY_OnItemCollapsed;
_property_event *PROPERTY_OnItemDoubleClicked;
_property_event *PROPERTY_OnItemEntered;
_property_event *PROPERTY_OnItemExpanded;
_property_event *PROPERTY_OnItemPressed;
_property_event *PROPERTY_OnItemSelectionChanged;

_property_event *PROPERTY_OnDockMove;
_property_event *PROPERTY_OnDockShow;
_property_event *PROPERTY_OnDockHide;
_property_event *PROPERTY_OnDockFloating;
_property_event *PROPERTY_OnDockNotFloating;


_property_event *PROPERTY_OnPrint;


_property_lineedit *PROPERTY_Brightness;
_property_lineedit *PROPERTY_Contrast;
_property_lineedit *PROPERTY_Hue;
_property_lineedit *PROPERTY_Saturation;
_property_choicebox *PROPERTY_ScaleMode;
_property_choicebox *PROPERTY_AspectRatio;

_property_lineedit *PROPERTY_TransitionTime;
_property_booleancombobox *PROPERTY_Muted;
_property_lineedit *PROPERTY_Volume;
_property_lineedit *PROPERTY_PrefinishMark;
_property_lineedit *PROPERTY_Tick;

_property_event *PROPERTY_OnTick;
_property_event *PROPERTY_OnStateChanged;
_property_event *PROPERTY_OnAboutToFinish;
_property_event *PROPERTY_OnFinished;
_property_event *PROPERTY_OnMutedChanged;
_property_event *PROPERTY_OnVolumeChanged;
_property_event *PROPERTY_OnPlayingTitleChanged;
_property_event *PROPERTY_OnBufferStatus;
_property_event *PROPERTY_OnTotalTimeChanged;



// PROPERTY
_property_lineedit *PROPERTY_Prefix;
_property_lineedit *PROPERTY_Suffix;

_property_lineedit *PROPERTY_Description;
_property_choicebox *PROPERTY_ViewMode;

_property_choicebox *PROPERTY_TickPosition;
_property_booleancombobox *PROPERTY_InvertedAppearance;
_property_booleancombobox *PROPERTY_InvertedControls;
_property_booleancombobox *PROPERTY_Tracking;
_property_lineedit *PROPERTY_TickInterval;
_property_lineedit *PROPERTY_PageStep;
_property_lineedit *PROPERTY_SingleStep;

_property_booleancombobox *PROPERTY_MoveOnMouseDrag;
_property_booleancombobox *PROPERTY_MouseTracking;

_property_booleancombobox *PROPERTY_DrawOnPaint;

_property_lineedit *PROPERTY_ActionId;
_property_lineedit *PROPERTY_SoundOnEvent;
_property_listcombobox *PROPERTY_CursorAnimation;


_property_lineedit *PROPERTY_ContextMenu;
_property_imageedit *PROPERTY_StringValue;
_property_lineedit *PROPERTY_InputMask;
_property_lineedit *PROPERTY_Mask;
_property_lineedit *PROPERTY_Pages;

_property_lineedit *PROPERTY_SQL;


_property_lineedit *PROPERTY_ParentForm;
_property_lineedit *PROPERTY_ParentControl;

_property_imageedit *PROPERTY_EnterImage;
_property_imageedit *PROPERTY_ExitImage;
_property_imageedit *PROPERTY_DisabledImage;

_property_imageedit *PROPERTY_CheckEnterImage;
_property_imageedit *PROPERTY_CheckExitImage;
_property_imageedit *PROPERTY_CheckDisabledImage;

_property_soundedit *PROPERTY_EnterSound;
_property_soundedit *PROPERTY_ExitSound;

_property_booleancombobox *PROPERTY_Menu;
_property_booleancombobox *PROPERTY_Checked;
_property_booleancombobox *PROPERTY_CheckableExclusive;

_property_lineedit *PROPERTY_Interval;



_property_booleancombobox *PROPERTY_RootIsDecorated;
_property_booleancombobox *PROPERTY_Null;
_property_booleancombobox *PROPERTY_Index;
_property_booleancombobox *PROPERTY_OpenAtStartup;

_property_booleancombobox *PROPERTY_AcceptRichText;
_property_booleancombobox *PROPERTY_AutoDefault;
_property_booleancombobox *PROPERTY_EventOnOpen;
_property_booleancombobox *PROPERTY_Default;
_property_booleancombobox *PROPERTY_Checkable;
_property_booleancombobox *PROPERTY_BooleanValue;

_property_lineedit *PROPERTY_Dummy1;
_property_lineedit *PROPERTY_Dummy2;
_property_lineedit *PROPERTY_Dummy3;
_property_lineedit *PROPERTY_Dummy4;
_property_lineedit *PROPERTY_Dummy5;
_property_lineedit *PROPERTY_Dummy6;
_property_lineedit *PROPERTY_Dummy7;


// EVENT


//_property_event *PROPERTY_OnCursorPositionChanged;
_property_event *PROPERTY_OnEditingFinished;
_property_event *PROPERTY_OnReturnPressed;
_property_event *PROPERTY_OnSelectionChanged;
_property_event *PROPERTY_OnTextChanged;
_property_event *PROPERTY_OnTextEdited;


_property_event *PROPERTY_OnPage;
_property_event *PROPERTY_OnLinkHovered;
_property_event *PROPERTY_OnLoadFinished;
_property_event *PROPERTY_OnLoadProgress;
_property_event *PROPERTY_OnLoadStarted;
_property_event *PROPERTY_OnWindowCloseRequested;

_property_event *PROPERTY_OnSingleShot;
_property_event *PROPERTY_OnDirty;
_property_event *PROPERTY_OnAddNew;
_property_event *PROPERTY_OnQuery;

_property_event *PROPERTY_OnEvent;
_property_event *PROPERTY_OnAction;
_property_event *PROPERTY_OnCursorPositionChanged;

_property_event *PROPERTY_OnOpen;
_property_event *PROPERTY_OnClose;
_property_event *PROPERTY_OnGoTo;
_property_event *PROPERTY_OnBeforeInsert;
_property_event *PROPERTY_OnBeforeDelete;
_property_event *PROPERTY_OnDragExit;
_property_event *PROPERTY_OnPaint;

_property_event *PROPERTY_OnTimer;
_property_event *PROPERTY_OnMove;
_property_event *PROPERTY_OnRefresh;
_property_event *PROPERTY_OnHide;
_property_event *PROPERTY_OnShow;
_property_event *PROPERTY_OnEnabled;
_property_event *PROPERTY_OnDisabled;
_property_event *PROPERTY_OnContextMenu;
_property_event *PROPERTY_OnMouseWheel;
_property_event *PROPERTY_OnMultiPageShow;
_property_event *PROPERTY_OnScroll;


_property_event *PROPERTY_OnDrop;
_property_event *PROPERTY_OnDragMove;
_property_event *PROPERTY_OnDragEnter;


_property_event *PROPERTY_OnClick;
_property_event *PROPERTY_OnDblClick;
_property_event *PROPERTY_OnMouseDown;
_property_event *PROPERTY_OnMouseUp;
_property_event *PROPERTY_OnMouseMove;
_property_event *PROPERTY_OnGotFocus;
_property_event *PROPERTY_OnLostFocus;
_property_event *PROPERTY_OnEnter;
_property_event *PROPERTY_OnExit;
_property_event *PROPERTY_OnKeyDown;
_property_event *PROPERTY_OnKeyUp;
_property_event *PROPERTY_OnKeyPress;
_property_event *PROPERTY_OnBeforeUpdate;

_property_event *PROPERTY_OnResize;


QList<_property_lineedit*>controls_lineedit;
QList<_property_coloredit*>controls_coloredit;
QList<_property_imageedit*>controls_imageedit;
QList<_property_colorimageedit*>controls_colorimageedit;
QList<_property_listcombobox*>controls_listcombobox;
QList<_property_booleancombobox*>controls_booleancombobox;
QList<_property_fontedit*>controls_fontedit;
QList<_property_event*>controls_event;
QList<_property_choicebox*>controls_choicebox;
QList<_property_soundedit*>controls_soundedit;
QList<_property_fileedit*>controls_fileedit;
QList<_property_pixeledit*>controls_pixeledit;




QScrollArea *a;

QTreeWidgetItem *_all;
QTreeWidgetItem *_constants;
QTreeWidgetItem *_variables;
QTreeWidgetItem *_methods;
QTreeWidgetItem *_properties;
QTreeWidgetItem *_enums;
QTreeWidgetItem *_types;


QLabel *currentcontrolname;
QTreeWidget *tree;

void focusInEvent(QFocusEvent * e);

};


#endif