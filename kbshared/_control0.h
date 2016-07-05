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

#ifndef _CONTROL0_H
#define _CONTROL0_H

#include "typedef.h"

#ifdef RUN
#include <QtGui>

extern void MYLOG(QString s);

extern QObject *EventSource;
#endif

#include <QPixmap>
#include <QIcon>
#include <QFile>
#include <QString>
#include <QWidget>
#include <QBuffer>

extern QWidget *ControlFocusPrevious;

class _form;
class _toolbar;

extern void my_form_addToCollection(_form *f, QWidget *c, QString s, int nType);
extern void my_form_readdToCollection(_form *f, QWidget *c, QString old, QString s, const char *acType);



extern void my_form_EVENT_OnGotFocus(_form *f);
extern void my_form_EVENT_OnLostFocus(_form *f);

extern QString sUniqueName;

extern void my_form_setImageButtonBooleanValue(_form *f, QString sGroup, QWidget *control, t_boolean b);
extern void my_form_setCommandButtonBooleanValue(_form *f, QString sGroup, QWidget *control, t_boolean b);
extern void my_form_setCommandLinkButtonBooleanValue(_form *f, QString sGroup, QWidget *control, t_boolean b);
extern void my_form_setToolButtonBooleanValue(_form *f, QString sGroup, QWidget *control, t_boolean b);
extern void my_form_setRadioButtonBooleanValue(_form *f, QString sGroup, QWidget *control, t_boolean b);
extern QWidget *my_form_getControl(_form *f, QString s);
extern QPixmap my_form_loadProjectImage(_form *f, QString s);
extern QString my_form_getProjectPath(_form *f);
extern QPixmap &my_form_createPixmap(_form *f, QString fn);
extern bool my_form_isForm(_form *f);
extern bool my_form_isOpened(_form *f);
extern void my_form_setMenuForButton(_form *f, QString sMenuName, QWidget *control);
extern void my_toolbar_setMenuForButton(_toolbar *t, QString sMenuName, QString control);

extern void my_form_newUndoRedo(_form *f);


extern _toolbar *EXTERN_my_toolbar;

extern void setVisibleToolBar(bool visible, QWidget *child, QWidget *parent);

extern bool setMyMovie(QWidget *control, QMovie **movie, QByteArray **moviea, QBuffer **movieb, QString n);



extern void _SETPROPERTY_X(_form *my_form, QWidget *w, int n);
extern void _SETPROPERTY_Y(_form *my_form, QWidget *w, int n);


extern int my_form_XScrollBar_value(_form *my_form);

#ifdef IDE

#include "../kbide/_typedef.h"

extern void my_form_newEvent(_form *f, QString sControlName, QString sEvent, QString sParameter);
extern const QIcon &kbasicIcon(QString s);

class _selectPanel : public QWidget
{
public:

int width;
_selectPanelStyle style;
bool bMousePressed;
bool bResize;


_selectPanel (_selectPanelStyle s, QWidget *c = 0, bool _bResize = true, int nWidth = 0) : QWidget(c)
{
  if (nWidth != 0) width = nWidth; else width = 7;
  bResize = _bResize;

  parent = c;
  bMousePressed = false;
  style = s;

  resize(width, width); 
  back = QPixmap(width, width);
  QPainter paint;
  paint.begin(&back);
  QBrush brush( Qt::black ); 
  paint.fillRect(rect(), brush);
  paint.setPen(Qt::white);
  paint.drawRect(rect());
  paint.end();

  setCursor2();
  reorder();
  show();
}

void setCursor2()
{
  if (bResize){
    switch(style){
      case LeftTop:
        setCursor(Qt::SizeFDiagCursor);
      break;
      case MidTop:
      setCursor(Qt::SizeVerCursor);
      break;
      case RightTop:
      setCursor(Qt::SizeBDiagCursor);
      break;
      case LeftMid:
      setCursor(Qt::SizeHorCursor);
      break;
      case RightMid:
      setCursor(Qt::SizeHorCursor);
      break;
      case LeftBottom:
      setCursor(Qt::SizeBDiagCursor);
      break;
      case MidBottom:
      setCursor(Qt::SizeVerCursor);
      break;
      case RightBottom:
      setCursor(Qt::SizeFDiagCursor);
      break;
      default:
      break;
    }
  }
  
}

void reorder()
{
  switch(style){
    case LeftTop:
      nX = 0;
      nY = 0;
      break;
    case MidTop:
      nX = (parent->width() - width) / 2;
      nY = 0;
      break;
    case RightTop:
      nX = parent->width() - width;
      nY = 0;
      break;
    case LeftMid:
      nX = 0;
      nY = (parent->height() - width) / 2;
      break;
    case RightMid:
      nX = parent->width() - width;
      nY = (parent->height() - width) / 2;
      break;
    case LeftBottom:
      nX = 0;
      nY = parent->height() - width;
      break;
    case MidBottom:
      nX = (parent->width() - width) / 2;
      nY = parent->height() - width;
      break;
    case RightBottom:
      nX = parent->width() - width;
      nY = parent->height() - width;
      break;
    default:
      break;
  }

  if (nX != x() || nY != y()){
    move(nX, nY);
  }

}

void  paintEvent( QPaintEvent *event )
{
  QPainter paint( this );
  paint.drawPixmap(0, 0, back);
}

void mousePressEvent ( QMouseEvent * e )
{
  bMousePressed = true;

  nMouseX = e->globalX();
  nMouseY = e->globalY();
}

void mouseMoveEvent ( QMouseEvent * e );

void mouseReleaseEvent ( QMouseEvent * e );

int positive(int n)
{
  if (n < 0) return n = 0;
  return n;
}

int nX;
int nY;
QWidget *parent;

QPixmap back;

int nMouseX;
int nMouseY;

};




#endif
#endif