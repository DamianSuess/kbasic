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


#ifndef _FORM_H
#define _FORM_H


#include <QFrame>
#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QScrollBar>


#include "typedef.h"


class _record;
class _query;


#ifdef IDE

#define XSCROLLBAR (XScrollBar?XScrollBar->value():0)
#define YSCROLLBAR (YScrollBar?YScrollBar->value():0)

extern bool bApply;
extern QString sInsertTypeOption;

#include "../kbide/_propertywindow.h"
#include "../kbide/_toolboxwindow_form.h"
#include "../kbide/_toolboxwindow_vista.h"

// CONTROL


  #include "_udpsocket.h"
  #include "_scrollbar.h"
  #include "_spinbox.h"
  #include "_slider.h"
  #include "_formsview.h"
  #include "_toolbarview.h"
  #include "_svg.h"
  #include "_commandlinkbutton.h"
  #include "_resizebox.h"
  #include "_toolbutton.h"
  #include "_line.h"
  #include "_serialport.h"
  #include "_movie.h"
  #include "_sound.h"
  #include "_web.h"
  #include "_header.h"
  #include "_footer.h"
 // #include "_vsplit.h"
 // #include "_hsplit.h"
//  #include "_vhbox.h"
 // #include "_hbox.h"
 // #include "_vbox.h"
  #include "_label.h"
  #include "_checkbox.h"
  #include "_frame.h"
  #include "_listbox.h"
  #include "_radiobutton.h"
  #include "_textbox.h"
  #include "_progressbar.h"
  #include "_image.h"
  #include "_combobox.h"
  #include "_commandbutton.h"

  #include "_box.h"
 // #include "_hidden.h"

  #include "_treeview.h"
  #include "_timer.h"
  #include "_tab.h"
  #include "_imagebutton.h"

  #include "_childcontrol.h"
  #include "_browser.h"
  #include "_editor.h"
  #include "_datebox.h"
  #include "_timebox.h"
  #include "_datetimebox.h"

#elif defined(RUN)

#include <QSqlDatabase>

extern QString getPrimary(QString sTable);
extern QString getPrimary(QSqlDatabase &db, QString sTable);

#define XSCROLLBAR 0
#define YSCROLLBAR 0

#define SUPERCLASS QScrollArea

  #include <QtGui>
  #include <QtSql>

  extern QMdiArea *forms_workspace;

  extern QObject *EventSource;

  extern QSqlDatabase CurrentDatabase;

  extern QString sCurrentLanguage;
  extern QString sCurrentCountry;

  extern QString sChildControlParentOverwrite;

  // CONTROL
  
  #include "../kbasic_binding/_udpsocket/kb_udpsocket.h"
  #include "../kbasic_binding/_scrollbar/kb_scrollbar.h"
  #include "../kbasic_binding/_spinbox/kb_spinbox.h"
  #include "../kbasic_binding/_slider/kb_slider.h"
  #include "../kbasic_binding/_formsview/kb_formsview.h"
  #include "../kbasic_binding/_toolbarview/kb_toolbarview.h"
  #include "../kbasic_binding/_svg/kb_svg.h"
  #include "../kbasic_binding/_commandlinkbutton/kb_commandlinkbutton.h"
  #include "../kbasic_binding/_resizebox/kb_resizebox.h"
  #include "../kbasic_binding/_toolbutton/kb_toolbutton.h"
  #include "../kbasic_binding/_line/kb_line.h"
  #include "../kbasic_binding/_checkbox/kb_checkbox.h"

  #include "../kbasic_binding/_movie/kb_movie.h"
  #include "../kbasic_binding/_sound/kb_sound.h"
  #include "../kbasic_binding/_web/kb_web.h"

/*
  #include "../kbasic_binding/_vsplit/kb_vsplit.h"

  #include "../kbasic_binding/_hsplit/kb_hsplit.h"
  #include "../kbasic_binding/_vhbox/kb_vhbox.h"
  #include "../kbasic_binding/_hbox/kb_hbox.h"
  #include "../kbasic_binding/_vbox/kb_vbox.h"
  */

  #include "../kbasic_binding/_header/kb_header.h"
  #include "../kbasic_binding/_footer/kb_footer.h"
  #include "../kbasic_binding/_serialport/kb_serialport.h"

  #include "../kbasic_binding/_label/kb_label.h"
  #include "../kbasic_binding/_frame/kb_frame.h"
  #include "../kbasic_binding/_listbox/kb_listbox.h"
  #include "../kbasic_binding/_radiobutton/kb_radiobutton.h"
  #include "../kbasic_binding/_textbox/kb_textbox.h"
  #include "../kbasic_binding/_progressbar/kb_progressbar.h"
  #include "../kbasic_binding/_image/kb_image.h"
  #include "../kbasic_binding/_combobox/kb_combobox.h"
  #include "../kbasic_binding/_commandbutton/kb_commandbutton.h"

  #include "../kbasic_binding/_box/kb_box.h"
//  #include "../kbasic_binding/_hidden/kb_hidden.h"

  #include "../kbasic_binding/_treeview/kb_treeview.h"
  #include "../kbasic_binding/_timer/kb_timer.h"
  #include "../kbasic_binding/_tab/kb_tab.h"
  #include "../kbasic_binding/_imagebutton/kb_imagebutton.h"

  #include "../kbasic_binding/_childcontrol/kb_childcontrol.h"
  #include "../kbasic_binding/_browser/kb_browser.h"
  #include "../kbasic_binding/_editor/kb_editor.h"
  #include "../kbasic_binding/_datebox/kb_datebox.h"
  #include "../kbasic_binding/_timebox/kb_timebox.h"
  #include "../kbasic_binding/_datetimebox/kb_datetimebox.h"

#endif

#include "_property.h"

class _mainwindow;
extern _mainwindow *EXTERN_my_mainwindow;

#define _FORM true
#define SWITCH6 controlType(c)

class _form;

#ifdef RUN
class _main : public QWidget
{
public:
  _main(_form *parent = 0) : QWidget(( QWidget *) parent)
  {
    f = parent;
  }

  void paintEvent(QPaintEvent *e);
  /*
  void actionEvent(QActionEvent *e);
  void changeEvent(QEvent *e);  
  void contextMenuEvent(QContextMenuEvent *e);
  void dragEnterEvent(QDragEnterEvent *e);
  void dragLeaveEvent(QDragLeaveEvent *e);
  void dragMoveEvent(QDragMoveEvent *e);
  void dropEvent(QDropEvent *e);
  void enterEvent(QEvent *e);
  void focusInEvent(QFocusEvent *e);
  void focusOutEvent(QFocusEvent *e);
  void hideEvent(QHideEvent *e);
  void inputMethodEvent(QInputMethodEvent *e);
  void keyPressEvent(QKeyEvent *e);
  void keyReleaseEvent(QKeyEvent *e);
  void leaveEvent(QEvent *e);
  void mouseDoubleClickEvent(QMouseEvent *e);
  void mouseMoveEvent(QMouseEvent *e);
  void mousePressEvent(QMouseEvent *e);
  void mouseReleaseEvent(QMouseEvent *e);
  void resizeEvent(QResizeEvent *e);
  //void showEvent(QShowEvent *e);
  void tabletEvent(QTabletEvent *e);
  void wheelEvent(QWheelEvent *e);
*/
private:
  _form *f;
};
#endif

#ifdef IDE

extern _toolboxwindow_form *EXTERN_my_toolboxwindow_form;
extern _toolboxwindow_vista *EXTERN_my_toolboxwindow_vista;

#endif


#ifdef IDE
class _form : public QWidget, public _property
#else
class _form : public QScrollArea, public _property
#endif
{
  Q_OBJECT
public:

_form(){}
~_form();
_form(_mainwindow *_my_mainwindow);
_form(_mainwindow *_my_mainwindow, QString sObjectName);

#ifdef RUN
QString sName;
QString sGroup;
const char *acName;
const char *acGroup;
QByteArray a;
QByteArray b;
#endif

void constructor(_mainwindow *_my_mainwindow, QString _sObjectName = "");


#include "_form_property.h"


#include "_form_loadsave.h"

#ifdef RUN
  #include "_control1_binding.h"
  #include "_form_binding.h"
#else
  #include "__property_background.h"
#endif


bool isReport()
{
  return sFilename.endsWith(".kbasic_report", Qt::CaseInsensitive);
}

bool isForm()
{
  return sFilename.endsWith(".kbasic_form", Qt::CaseInsensitive);
}

#ifdef RUN
bool isOpened()
{
  return bOpened;
}
#endif


virtual void SETPROPERTY_X(int n, bool b = true);
#ifdef RUN

void timerEvent(QTimerEvent* e);

virtual int GETPROPERTY_X();
virtual int GETPROPERTY_Width();
virtual int GETPROPERTY_GlobalX();
#endif
virtual void SETPROPERTY_Y(int n, bool b = true);
#ifdef RUN
virtual int GETPROPERTY_Y();
virtual int GETPROPERTY_Height();
virtual int GETPROPERTY_GlobalY();
#endif
virtual void SETPROPERTY_Width(int n, bool b = true);
virtual void SETPROPERTY_Height(int n, bool b = true);

// ***

#ifdef IDE
void setFormSelf()
{
    unselectAllControls();
    focusInEvent(0);
    updatePropertyWindow();

    bApply = false;
  
}
#endif



void  paintEvent( QPaintEvent *e );


bool eventFilter( QObject *o, QEvent *e );


#ifdef RUN
void moveEvent ( QMoveEvent *e);
void moveEvent ( QMoveEvent *e, bool b);


void showEvent ( QShowEvent * e)
{
 
  QScrollArea::showEvent(e);
  
  EVENT_OnShow(); 
  
}

void hideEvent ( QHideEvent * e)
{

  QScrollArea::hideEvent(e);
  
  EVENT_OnHide(); 
  bDialogRunning = false;
  
}



void contextMenuEvent(QContextMenuEvent *e)
{    
    QScrollArea::contextMenuEvent(e);
    { 
      EVENT_OnContextMenu(e->x() + this->horizontalScrollBar()->value(), e->y() + this->verticalScrollBar()->value(), e->globalX(), e->globalY()); 
    }

  
}

#endif

#ifdef IDE
void showEvent ( QShowEvent *e);
void showScrollBars();
#endif
void resizeEvent ( QResizeEvent *e);
void resizeEvent ( QResizeEvent *e, bool b);
void tabPageSelected(_tab *t, int index);





#ifdef IDE

void updateActions()
{
  focusInEvent(0);
}

void updateControls(_selectPanelStyle style, int x, int y, int w, int h);


void updatePropertyWindowGeo();




_controlType insertType;
virtual void setInsertControlType(_controlType t)
{
  insertType = t;
  if (insertType == t_notype){
    bApply = false;
    sInsertTypeOption = "";
  }
}
#endif

_controlType iterationType[MAX_ITERATOR];

virtual bool 		firstControl(QWidget **c, int nIndex = 0)
{
  bool b = false;

  iterationType[nIndex] = t_notype;

  lines.reset(nIndex);
  movies.reset(nIndex);
  sounds.reset(nIndex);
  webs.reset(nIndex);
  serialports.reset(nIndex);
  headers.reset(nIndex);
  footers.reset(nIndex);
  labels.reset(nIndex);

  // CONTROL
  
  udpsockets.reset(nIndex);
  scrollbars.reset(nIndex);
  spinboxes.reset(nIndex);
  sliders.reset(nIndex);
  formsviews.reset(nIndex);
  toolbarviews.reset(nIndex);
  svgs.reset(nIndex);
  commandlinkbuttons.reset(nIndex);
  resizeboxes.reset(nIndex);
  toolbuttons.reset(nIndex);
  commandbuttons.reset(nIndex);
  checkboxes.reset(nIndex);
  frames.reset(nIndex);
  listboxes.reset(nIndex);
  //listviews.reset(nIndex);
  //optionbuttons.reset(nIndex);
  radiobuttons.reset(nIndex);  
  textboxes.reset(nIndex);
  progressbars.reset(nIndex);
  //scrollbars.reset(nIndex);
  images.reset(nIndex);
  //subforms.reset(nIndex);
  //textareas.reset(nIndex);
  timers.reset(nIndex);
  treeviews.reset(nIndex);
  comboboxes.reset(nIndex);

  //dots.reset(nIndex);
  //lines.reset(nIndex);
  //rectangles.reset(nIndex);
  //circles.reset(nIndex);
//  hiddens.reset(nIndex);
  //qwidgets.reset(nIndex);

  imagebuttons.reset(nIndex);
 // canvases.reset(nIndex);
  //activexes.reset(nIndex);

  boxes.reset(nIndex);
  childcontrols.reset(nIndex);
  editors.reset(nIndex);
  browsers.reset(nIndex);
  dateboxes.reset(nIndex);
  timeboxes.reset(nIndex);
  datetimeboxes.reset(nIndex);
/*
  vboxes.reset(nIndex); // must be last
  hboxes.reset(nIndex); // must be last
  vhboxes.reset(nIndex); // must be last
  vsplits.reset(nIndex); // must be last
  hsplits.reset(nIndex); // must be last*/
  tabs.reset(nIndex); // must be last

  b = lines.first((_line**) c, nIndex);
  if (b){ CurrentControl = *c; return true; }
    
  b = movies.first((_movie**) c, nIndex);
  if (b){ CurrentControl = *c; return true; }
    
  b = sounds.first((_sound**) c, nIndex);
  if (b){ CurrentControl = *c; return true; }
    
  b = webs.first((_web**) c, nIndex);
  if (b){ CurrentControl = *c; return true; }
    
  b = serialports.first((_serialport**) c, nIndex);
  if (b){ CurrentControl = *c; return true; }
    
  b = headers.first((_header**) c, nIndex);
  if (b){ CurrentControl = *c; return true; }
  
  b = footers.first((_footer**) c, nIndex);
  if (b){ CurrentControl = *c; return true; }

  b = labels.first((_label**) c, nIndex);
  if (b){ CurrentControl = *c; return true; }

  // CONTROL
  
  b = udpsockets.first((_udpsocket**) c, nIndex);
  if (b){ CurrentControl = *c; return true; }

  b = scrollbars.first((_scrollbar**) c, nIndex);
  if (b){ CurrentControl = *c; return true; }

  b = spinboxes.first((_spinbox**) c, nIndex);
  if (b){ CurrentControl = *c; return true; }

  b = sliders.first((_slider**) c, nIndex);
  if (b){ CurrentControl = *c; return true; }

  b = formsviews.first((_formsview**) c, nIndex);
  if (b){ CurrentControl = *c; return true; }

  b = toolbarviews.first((_toolbarview**) c, nIndex);
  if (b){ CurrentControl = *c; return true; }

  b = svgs.first((_svg**) c, nIndex);
  if (b){ CurrentControl = *c; return true; }

  b = commandlinkbuttons.first((_commandlinkbutton**) c, nIndex);
  if (b){ CurrentControl = *c; return true; }

  b = resizeboxes.first((_resizebox**) c, nIndex);
  if (b){ CurrentControl = *c; return true; }

  b = toolbuttons.first((_toolbutton**) c, nIndex);
  if (b){ CurrentControl = *c; return true; }

  b = commandbuttons.first((_commandbutton**) c, nIndex);
  if (b){ CurrentControl = *c; return true; }

  b = checkboxes.first((_checkbox**) c, nIndex);
  if (b){ CurrentControl = *c; return true; }

  b = frames.first((_frame**) c, nIndex);
  if (b){ CurrentControl = *c; return true; }

  b = listboxes.first((_listbox**) c, nIndex);
  if (b){ CurrentControl = *c; return true; }

  b = radiobuttons.first((_radiobutton**) c, nIndex);
  if (b){ CurrentControl = *c; return true; }

  b = textboxes.first((_textbox**) c, nIndex);
  if (b){ CurrentControl = *c; return true; }

  b = progressbars.first((_progressbar**) c, nIndex);
  if (b){ CurrentControl = *c; return true; }

  b = images.first((_image**) c, nIndex);
  if (b){ CurrentControl = *c; return true; }

  b = timers.first((_timer**) c, nIndex);
  if (b){ CurrentControl = *c; return true; }

  b = treeviews.first((_treeview**) c, nIndex);
  if (b){ CurrentControl = *c; return true; }

  b = comboboxes.first((_combobox**) c, nIndex);
  if (b){ CurrentControl = *c; return true; }

  //b = lines.first((_line**) c, nIndex);
  //if (b){ CurrentControl = *c; return true; }

  //b = rectangles.first((_rectangle**) c, nIndex);
  //if (b){ CurrentControl = *c; return true; }

  //b = circles.first((_circle**) c, nIndex);
  //if (b){ CurrentControl = *c; return true; }

//  b = hiddens.first((_hidden**) c, nIndex);
 // if (b){ CurrentControl = *c; return true; }

  b = imagebuttons.first((_imagebutton**) c, nIndex);
  if (b){ CurrentControl = *c; return true; }

  b = boxes.first((_box**) c, nIndex);
  if (b){ CurrentControl = *c; return true; }

  b = childcontrols.first((_childcontrol**) c, nIndex);
  if (b){ CurrentControl = *c; return true; }
  
  b = browsers.first((_browser**) c, nIndex);
  if (b){ CurrentControl = *c; return true; }

  b = editors.first((_editor**) c, nIndex);
  if (b){ CurrentControl = *c; return true; }

  b = dateboxes.first((_datebox**) c, nIndex);
  if (b){ CurrentControl = *c; return true; }

  b = timeboxes.first((_timebox**) c, nIndex);
  if (b){ CurrentControl = *c; return true; }

  b = datetimeboxes.first((_datetimebox**) c, nIndex);
  if (b){ CurrentControl = *c; return true; }

  //b = activexes.first((_activex**) c, nIndex);
  //if (b){ CurrentControl = *c; return true; }
/*
  b = vboxes.first((_vbox**) c, nIndex); // must be last
  if (b){ CurrentControl = *c; return true; }

  b = hboxes.first((_hbox**) c, nIndex); // must be last
  if (b){ CurrentControl = *c; return true; }

  b = vhboxes.first((_vhbox**) c, nIndex); // must be last
  if (b){ CurrentControl = *c; return true; }

  b = vsplits.first((_vsplit**) c, nIndex); // must be last
  if (b){ CurrentControl = *c; return true; }

  b = hsplits.first((_hsplit**) c, nIndex); // must be last
  if (b){ CurrentControl = *c; return true; }
*/
  b = tabs.first((_tab**) c, nIndex); // must be last
  if (b){ CurrentControl = *c; return true; }

  CurrentControl = 0;


  return false;
}

virtual bool 		nextControl(QWidget **c, int nIndex = 0)
{ 
  bool b = false;
    
  // CONTROL

  if (iterationType[nIndex] == t_notype){
    b = lines.next((_line**) c, nIndex);
    if (b){ CurrentControl = *c; return true; }
    iterationType[nIndex] = t_udpsocket;
  }

  if (iterationType[nIndex] == t_udpsocket){
    b = udpsockets.next((_udpsocket**) c, nIndex);
    if (b){ CurrentControl = *c; return true; }
    iterationType[nIndex] = t_line;
  }

  if (iterationType[nIndex] == t_line){
    b = movies.next((_movie**) c, nIndex);
    if (b){ CurrentControl = *c; return true; }
    iterationType[nIndex] = t_movie;
  }

  if (iterationType[nIndex] == t_movie){
    b = sounds.next((_sound**) c, nIndex);
    if (b){ CurrentControl = *c; return true; }
    iterationType[nIndex] = t_sound;
  }

  if (iterationType[nIndex] == t_sound){
    b = webs.next((_web**) c, nIndex);
    if (b){ CurrentControl = *c; return true; }
    iterationType[nIndex] = t_web;
  }

  if (iterationType[nIndex] == t_web){
    b = serialports.next((_serialport**) c, nIndex);
    if (b){ CurrentControl = *c; return true; }
    iterationType[nIndex] = t_serialport;
  }

  if (iterationType[nIndex] == t_serialport){
    b = headers.next((_header**) c, nIndex);
    if (b){ CurrentControl = *c; return true; }
    iterationType[nIndex] = t_header;
  }
  if (iterationType[nIndex] == t_header){

    b = footers.next((_footer**) c, nIndex);
    if (b){ CurrentControl = *c; return true; }
    iterationType[nIndex] = t_footer;
  }

  if (iterationType[nIndex] == t_footer){
    b = labels.next((_label**) c, nIndex);
    if (b){ CurrentControl = *c; return true; }
    iterationType[nIndex] = t_label;

  }

  if (iterationType[nIndex] == t_label){
    b = scrollbars.next((_scrollbar**) c, nIndex);
    if (b){ CurrentControl = *c; return true; }
    iterationType[nIndex] = t_scrollbar;
  }

  if (iterationType[nIndex] == t_scrollbar){
    b = spinboxes.next((_spinbox**) c, nIndex);
    if (b){ CurrentControl = *c; return true; }
    iterationType[nIndex] = t_spinbox;
  }

  if (iterationType[nIndex] == t_spinbox){
    b = sliders.next((_slider**) c, nIndex);
    if (b){ CurrentControl = *c; return true; }
    iterationType[nIndex] = t_slider;
  }

  if (iterationType[nIndex] == t_slider){
    b = formsviews.next((_formsview**) c, nIndex);
    if (b){ CurrentControl = *c; return true; }
    iterationType[nIndex] = t_formsview;
  }

  if (iterationType[nIndex] == t_formsview){
    b = toolbarviews.next((_toolbarview**) c, nIndex);
    if (b){ CurrentControl = *c; return true; }
    iterationType[nIndex] = t_toolbarview;
  }

  if (iterationType[nIndex] == t_toolbarview){
    b = svgs.next((_svg**) c, nIndex);
    if (b){ CurrentControl = *c; return true; }
    iterationType[nIndex] = t_svg;
  }

  if (iterationType[nIndex] == t_svg){
    b = commandlinkbuttons.next((_commandlinkbutton**) c, nIndex);
    if (b){ CurrentControl = *c; return true; }
    iterationType[nIndex] = t_commandlinkbutton;
  }

  if (iterationType[nIndex] == t_commandlinkbutton){
    b = resizeboxes.next((_resizebox**) c, nIndex);
    if (b){ CurrentControl = *c; return true; }
    iterationType[nIndex] = t_resizebox;
  }

  if (iterationType[nIndex] == t_resizebox){
    b = toolbuttons.next((_toolbutton**) c, nIndex);
    if (b){ CurrentControl = *c; return true; }
    iterationType[nIndex] = t_toolbutton;
  }

  if (iterationType[nIndex] == t_toolbutton){
    b = commandbuttons.next((_commandbutton**) c, nIndex);
    if (b){ CurrentControl = *c; return true; }
    iterationType[nIndex] = t_commandbutton;
  }

  if (iterationType[nIndex] == t_commandbutton){
    b = checkboxes.next((_checkbox**) c, nIndex);
    if (b){ CurrentControl = *c; return true; }
    iterationType[nIndex] = t_checkbox;
  }

  if (iterationType[nIndex] == t_checkbox){
    b = frames.next((_frame**) c, nIndex);
    if (b){ CurrentControl = *c; return true; }
    iterationType[nIndex] = t_frame;
  }

  if (iterationType[nIndex] == t_frame){
    b = listboxes.next((_listbox**) c, nIndex);
    if (b){ CurrentControl = *c; return true; }
    iterationType[nIndex] = t_listbox;
  }

  if (iterationType[nIndex] == t_listbox){
    b = radiobuttons.next((_radiobutton**) c, nIndex);
    if (b){ CurrentControl = *c; return true; }
    iterationType[nIndex] = t_radiobutton;
  }

  if (iterationType[nIndex] == t_radiobutton){
    b = textboxes.next((_textbox**) c, nIndex);
    if (b){ CurrentControl = *c; return true; }
    iterationType[nIndex] = t_textbox;
  }

  if (iterationType[nIndex] == t_textbox){
    b = progressbars.next((_progressbar**) c, nIndex);
    if (b){ CurrentControl = *c; return true; }
    iterationType[nIndex] = t_progressbar;
  }

  if (iterationType[nIndex] == t_progressbar){
    b = images.next((_image**) c, nIndex);
    if (b){ CurrentControl = *c; return true; }
    iterationType[nIndex] = t_image;
  }

  if (iterationType[nIndex] == t_image){
    b = timers.next((_timer**) c, nIndex);
    if (b){ CurrentControl = *c; return true; }
    iterationType[nIndex] = t_timer;
  }

  if (iterationType[nIndex] == t_timer){
    b = treeviews.next((_treeview**) c, nIndex);
    if (b){ CurrentControl = *c; return true; }
    iterationType[nIndex] = t_treeview;
  }

  if (iterationType[nIndex] == t_treeview){
    b = comboboxes.next((_combobox**) c, nIndex);
    if (b){ CurrentControl = *c; return true; }
    iterationType[nIndex] = t_combobox;
  }
/*
  if (iterationType[nIndex] == t_combobox){
    b = hiddens.next((_hidden**) c, nIndex);
    if (b){ CurrentControl = *c; return true; }
    iterationType[nIndex] = t_hidden;
  }
*/
  if (iterationType[nIndex] == t_combobox){
    b = imagebuttons.next((_imagebutton**) c, nIndex);
    if (b){ CurrentControl = *c; return true; }
    iterationType[nIndex] = t_imagebutton;
  }

  if (iterationType[nIndex] == t_imagebutton){
    b = boxes.next((_box**) c, nIndex);
    if (b){ CurrentControl = *c; return true; }
    iterationType[nIndex] = t_childcontrol;
  }

  if (iterationType[nIndex] == t_childcontrol){
    b = childcontrols.next((_childcontrol**) c, nIndex);
    if (b){ CurrentControl = *c; return true; }
    iterationType[nIndex] = t_browser;
  }

  if (iterationType[nIndex] == t_browser){
    b = browsers.next((_browser**) c, nIndex);
    if (b){ CurrentControl = *c; return true; }
    iterationType[nIndex] = t_editor;
  }

  if (iterationType[nIndex] == t_editor){
    b = editors.next((_editor**) c, nIndex);
    if (b){ CurrentControl = *c; return true; }
    iterationType[nIndex] = t_datebox;
  }

  if (iterationType[nIndex] == t_datebox){
    b = dateboxes.next((_datebox**) c, nIndex);
    if (b){ CurrentControl = *c; return true; }
    iterationType[nIndex] = t_timebox;
  }

  if (iterationType[nIndex] == t_timebox){
    b = timeboxes.next((_timebox**) c, nIndex);
    if (b){ CurrentControl = *c; return true; }
    iterationType[nIndex] = t_datetimebox;
  }

  if (iterationType[nIndex] == t_datetimebox){
    b = datetimeboxes.next((_datetimebox**) c, nIndex);
    if (b){ CurrentControl = *c; return true; }
    iterationType[nIndex] = t_tab;
  }
/*
  if (iterationType[nIndex] == t_datetimebox){ // must be last
    b = vboxes.next((_vbox**) c, nIndex);
    if (b){ CurrentControl = *c; return true; }
    iterationType[nIndex] = t_vbox;
  }

  if (iterationType[nIndex] == t_vbox){ // must be last
    b = hboxes.next((_hbox**) c, nIndex);
    if (b){ CurrentControl = *c; return true; }
    iterationType[nIndex] = t_hbox;
  }

  if (iterationType[nIndex] == t_hbox){ // must be last
    b = vhboxes.next((_vhbox**) c, nIndex);
    if (b){ CurrentControl = *c; return true; }
    iterationType[nIndex] = t_vhbox;
  }

  if (iterationType[nIndex] == t_vhbox){ // must be last
    b = vsplits.next((_vsplit**) c, nIndex);
    if (b){ CurrentControl = *c; return true; }
    iterationType[nIndex] = t_vsplit;
  }

  if (iterationType[nIndex] == t_vsplit){ // must be last
    b = hsplits.next((_hsplit**) c, nIndex);
    if (b){ CurrentControl = *c; return true; }
    iterationType[nIndex] = t_hsplit;
  }
*/
  if (iterationType[nIndex] == t_tab){ // must be last
    b = tabs.next((_tab**) c, nIndex);
    if (b){ CurrentControl = *c; return true; }
    iterationType[nIndex] = t_atend;
  }


  CurrentControl = 0;

  return false;
}


#ifdef IDE
void formatValues(int *nMaxX, int *nMaxY, int *nMinX, int *nMinY, int *nMaxWidth, int *nMaxHeight)
{
  QWidget *c;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        int X;

        #define SWITCH GETPROPERTY_X();      
        #define SWITCH3 X
        #include "_form_property_switch.h"   
        #undef SWITCH3

        int Y;

        #define SWITCH GETPROPERTY_Y();      
        #define SWITCH3 Y
        #include "_form_property_switch.h"   
        #undef SWITCH3

        if (X + c->width() > *nMaxX) *nMaxX = X + c->width();
        if (Y + c->height() > *nMaxY) *nMaxY = Y + c->height();

        if (X < *nMinX) *nMinX = X;
        if (Y < *nMinY) *nMinY = Y;

        if (c->width() > *nMaxWidth) *nMaxWidth = c->width();
        if (c->height() > *nMaxHeight) *nMaxHeight = c->height();
      }

    } while (nextControl(&c));
  }
  
}

public slots:


void performSelectAll()
{
  QWidget *c;

  if (firstControl(&c)){

    do {
      c->setAcceptDrops(true); // missused as selected flag
      c->update();
    } while (nextControl(&c)); 

    focusInEvent(0);

  }
}
// *** events called by _mainwindow_events
void event_INSERT_SELECT2(){ setInsertControlType(t_notype); }
void event_INSERT_LABEL(){ setInsertControlType(t_label); }
void event_INSERT_COMMANDBUTTON(){ setInsertControlType(t_commandbutton); }
void event_INSERT_TOOLBUTTON(){ setInsertControlType(t_toolbutton); }
void event_INSERT_COMMANDLINKBUTTON(){ setInsertControlType(t_commandlinkbutton); }
void event_INSERT_SVG(){ setInsertControlType(t_svg); }
void event_INSERT_RESIZEBOX(){ setInsertControlType(t_resizebox); }
// CONTROL
void event_INSERT_UDPSOCKET(){ setInsertControlType(t_udpsocket); }
void event_INSERT_SCROLLBAR(){ setInsertControlType(t_scrollbar); }
void event_INSERT_SPINBOX(){ setInsertControlType(t_spinbox); }
void event_INSERT_SLIDER(){ setInsertControlType(t_slider); }
void event_INSERT_FORMSVIEW(){ setInsertControlType(t_formsview); }
void event_INSERT_TOOLBARVIEW(){ setInsertControlType(t_toolbarview); }
void event_INSERT_CHECKBOX(){ setInsertControlType(t_checkbox); }
void event_INSERT_RADIOBUTTON(){ setInsertControlType(t_radiobutton); }
void event_INSERT_TEXTBOX(){ setInsertControlType(t_textbox); }
void event_INSERT_FRAME(){ setInsertControlType(t_frame); }
void event_INSERT_LISTBOX(){ setInsertControlType(t_listbox); }
void event_INSERT_LISTBOX_ICONMODE(){ setInsertControlType(t_listbox); sInsertTypeOption = "IconMode"; }
void event_INSERT_COMBOBOX(){ setInsertControlType(t_combobox); }
void event_INSERT_PROGRESSBAR(){ setInsertControlType(t_progressbar); }
void event_INSERT_PROGRESSBAR_SPINNING(){ setInsertControlType(t_progressbar); sInsertTypeOption = "Spinning"; }
void event_INSERT_TREEVIEW_LISTVIEW(){ setInsertControlType(t_treeview); sInsertTypeOption = "ListView"; }
void event_INSERT_COMBOBOX_EDITABLE(){ setInsertControlType(t_combobox); sInsertTypeOption = "Editable"; }
void event_INSERT_IMAGE(){ setInsertControlType(t_image); }

void event_INSERT_HEADER(){ setInsertControlType(t_header); }
void event_INSERT_FOOTER(){ setInsertControlType(t_footer); }

void event_INSERT_CHILDCONTROL(){ setInsertControlType(t_childcontrol); }
void event_INSERT_SERIALPORT(){ setInsertControlType(t_serialport); }
void event_INSERT_BROWSER(){ setInsertControlType(t_browser); }
void event_INSERT_EDITOR(){ setInsertControlType(t_editor); }
void event_INSERT_DATEBOX(){ setInsertControlType(t_datebox); }
void event_INSERT_TIMEBOX(){ setInsertControlType(t_timebox); }
void event_INSERT_DATETIMEBOX(){ setInsertControlType(t_datetimebox); }


void event_INSERT_TEXTBOX_PASSWORD(){ setInsertControlType(t_textbox); sInsertTypeOption = "Password"; }
void event_INSERT_LABEL_LINK(){ setInsertControlType(t_label); sInsertTypeOption = "Link"; }
void event_INSERT_LINE_VERTICAL(){ setInsertControlType(t_line); sInsertTypeOption = "Vertical"; }
void event_INSERT_LINE_HORIZONTAL(){ setInsertControlType(t_line); sInsertTypeOption = "Horizontal"; }


void event_INSERT_VSPLIT(){ setInsertControlType(t_vsplit); }
void event_INSERT_HSPLIT(){ setInsertControlType(t_hsplit); }
void event_INSERT_VBOX(){ setInsertControlType(t_vbox); }
void event_INSERT_HBOX(){ setInsertControlType(t_hbox); }
void event_INSERT_VHBOX(){ setInsertControlType(t_vhbox); }
void event_INSERT_BOX(){ setInsertControlType(t_box); }
void event_INSERT_HIDDEN(){ setInsertControlType(t_hidden); }
void event_INSERT_TREEVIEW(){ setInsertControlType(t_treeview); }
void event_INSERT_TAB(){ setInsertControlType(t_tab); }
void event_INSERT_MOVIE(){ setInsertControlType(t_movie); }
void event_INSERT_SOUND(){ setInsertControlType(t_sound); }
void event_INSERT_WEB(){ setInsertControlType(t_web); }
void event_INSERT_TIMER(){ setInsertControlType(t_timer); }
void event_INSERT_IMAGEBUTTON(){ setInsertControlType(t_imagebutton); }
/*
void event_INSERT_MENU(){ setInsertControlType(t_menu); }
void event_INSERT_CHILDMENU(){ setInsertControlType(t_submenu); }
void event_INSERT_MENUBARITEM(){ setInsertControlType(t_menubaritem); }
void event_INSERT_MOVE(){ setInsertControlType(t_move); }
void event_INSERT_DELETE(){ setInsertControlType(t_delete); }
void event_INSERT_TOOLBARITEM(){ setInsertControlType(t_toolbaritem); }
*/

public:

void event_EDIT_BACKGROUND();
void event_EDIT_FONTNAME();
void event_EDIT_FONTCOLOR();
void event_EDIT_BOLD();
void event_EDIT_ITALIC();
void event_EDIT_UNDERLINE();
void event_EDIT_FONTSIZE();

void event_FORMAT_ALIGN_MOVELEFT()
{
  QWidget *c;
  int b = 0;
  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        bool bb = c->x() - 1 < 50;

        int X;

        #define SWITCH GETPROPERTY_X();      
        #define SWITCH3 X
        #include "_form_property_switch.h"   
        #undef SWITCH3

        int Y;

        #define SWITCH GETPROPERTY_Y();      
        #define SWITCH3 Y
        #include "_form_property_switch.h"   
        #undef SWITCH3

        if ((!XScrollBar && c->x() - 1 < 0) || (XScrollBar && X - 1 < 0)){
          my_move(c, 0, c->y());
        } else {
          decX(c, 1);
        }
  
        if (XScrollBar && bb){
          XScrollBar->setValue(XScrollBar->value() - 50);             
        }

        b++;
      }

    } while (nextControl(&c));
  }
  if (b < 1){
      QMessageBox::information( this, MYAPP,
        tr(
            "You have to select one controls at least,\n"       
            "before this command does any usefully function."
            )
            );
  }
  
  updatePropertyWindowGeo();
}

void event_FORMAT_ALIGN_MOVERIGHT()
{
  QWidget *c;
  int b = 0;
  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        bool bb = c->x() + c->width() + 50 > frameW();

        int X;

        #define SWITCH GETPROPERTY_X();      
        #define SWITCH3 X
        #include "_form_property_switch.h"   
        #undef SWITCH3

        int Y;

        #define SWITCH GETPROPERTY_Y();      
        #define SWITCH3 Y
        #include "_form_property_switch.h"   
        #undef SWITCH3

        if ((!XScrollBar && c->x() + c->width() + 1 > frameW()) || (XScrollBar && X + c->width() + 1 > XScrollBar->value() + frameW())){
          my_move(c, frameW() - c->width(), c->y());
        } else {
          incX(c, 1);
        }

        if (XScrollBar && bb){
          XScrollBar->setValue(XScrollBar->value() + 50);
        }

        b++;
      }

    } while (nextControl(&c));
  }
  if (b < 1){
      QMessageBox::information( this, MYAPP,
        tr(
            "You have to select one controls at least,\n"       
            "before this does any usefully function."
            )
            );
  }
  
  updatePropertyWindowGeo();
}

void event_FORMAT_ALIGN_MOVEUP()
{
  QWidget *c;
  int b = 0;
  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        bool bb = c->y() - 1 < 50;

        int X;

        #define SWITCH GETPROPERTY_X();      
        #define SWITCH3 X
        #include "_form_property_switch.h"   
        #undef SWITCH3

        int Y;

        #define SWITCH GETPROPERTY_Y();      
        #define SWITCH3 Y
        #include "_form_property_switch.h"   
        #undef SWITCH3

        if ((!YScrollBar && c->y() - 1 < 0) || (YScrollBar && Y - 1 < 0)){
          my_move(c, c->x(), 0);
        } else {
          decY(c, 1);
        }

        if (YScrollBar && bb){
          YScrollBar->setValue(YScrollBar->value() - 50);
        }

        b++;
      }

    } while (nextControl(&c));
  }
  if (b < 1){
      QMessageBox::information( this, MYAPP,
        tr(
            "You have to select one controls at least,\n"       
            "before this does any usefully function."
            )
            );
  }
  
  updatePropertyWindowGeo();
}

void event_FORMAT_ALIGN_MOVEDOWN()
{
  QWidget *c;
  int b = 0;
  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag
       
        bool bb = c->y() + c->height() + 50 > frameH();
        
        int X;

        #define SWITCH GETPROPERTY_X();      
        #define SWITCH3 X
        #include "_form_property_switch.h"   
        #undef SWITCH3

        int Y;

        #define SWITCH GETPROPERTY_Y();      
        #define SWITCH3 Y
        #include "_form_property_switch.h"   
        #undef SWITCH3

        if ((!YScrollBar && c->y() + c->height() + 1 > frameH()) || (YScrollBar && Y + c->height() + 1 > YScrollBar->value() + frameH())){
          my_move(c, c->x(), frameH() - c->height());
        } else {
          incY(c, 1);
        }

        if (YScrollBar && bb){
          YScrollBar->setValue(YScrollBar->value() + 50);
        }


        b++;
      }

    } while (nextControl(&c));
  }
  if (b < 1){
      QMessageBox::information( this, MYAPP,
        tr(
            "You have to select one controls at least,\n"       
            "before this does any usefully function."
            )
            );
  }
  
  updatePropertyWindowGeo();
}

void event_FORMAT_ALIGN_TOP()
{
  int nMaxX = 0;
  int nMaxY = 0;
  int nMinX = 999999;
  int nMinY = 999999;
  int nMaxWidth = 0;
  int nMaxHeight = 0;

  formatValues(&nMaxX, &nMaxY, &nMinX, &nMinY, &nMaxWidth, &nMaxHeight);

  QWidget *c;
  int b = 0;
  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_Y(nMinY);
        #include "_form_property_switch.h"      

        b++;
      }

    } while (nextControl(&c));
  }
  if (b <= 1){
      QMessageBox::information( this, MYAPP,
        tr(
            "You have to select two controls at least,\n"       
            "before this does any usefully function."
            )
            );
  }
  
  updatePropertyWindowGeo();

}

void event_FORMAT_ALIGN_BOTTOM()
{
  int nMaxX = 0;
  int nMaxY = 0;
  int nMinX = 999999;
  int nMinY = 999999;
  int nMaxWidth = 0;
  int nMaxHeight = 0;

  formatValues(&nMaxX, &nMaxY, &nMinX, &nMinY, &nMaxWidth, &nMaxHeight);

  QWidget *c;
  int b = 0;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_Y(nMaxY - c->height());
        #include "_form_property_switch.h"      

        b++;
      }

    } while (nextControl(&c));
  }
  if (b <= 1){
      QMessageBox::information( this, MYAPP,
        tr(
            "You have to select two controls at least,\n"       
            "before this does any usefully function."
            )
            );
  }

  updatePropertyWindowGeo();

}

void event_FORMAT_ALIGN_LEFT()
{
  int nMaxX = 0;
  int nMaxY = 0;
  int nMinX = 999999;
  int nMinY = 999999;
  int nMaxWidth = 0;
  int nMaxHeight = 0;

  formatValues(&nMaxX, &nMaxY, &nMinX, &nMinY, &nMaxWidth, &nMaxHeight);

  QWidget *c;
  int b = 0;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_X(nMinX);
        #include "_form_property_switch.h"      

        b++;
      }

    } while (nextControl(&c));
  }
  if (b <= 1){
      QMessageBox::information( this, MYAPP,
        tr(
            "You have to select two controls at least,\n"       
            "before this does any usefully function."
            )
            );
  }

  updatePropertyWindowGeo();

}

void event_FORMAT_ALIGN_RIGHT()
{
  int nMaxX = 0;
  int nMaxY = 0;
  int nMinX = 999999;
  int nMinY = 999999;
  int nMaxWidth = 0;
  int nMaxHeight = 0;

  formatValues(&nMaxX, &nMaxY, &nMinX, &nMinY, &nMaxWidth, &nMaxHeight);

  QWidget *c;
  int b = 0;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_X(nMaxX - c->width());
        #include "_form_property_switch.h"      

        b++;
      }

    } while (nextControl(&c));
  }
  if (b <= 1){
      QMessageBox::information( this, MYAPP,
        tr(
            "You have to select two controls at least,\n"       
            "before this does any usefully function."
            )
            );
  }

  updatePropertyWindowGeo();

}

void event_FORMAT_SET_SAME_WIDTH()
{
  int nMaxX = 0;
  int nMaxY = 0;
  int nMinX = 999999;
  int nMinY = 999999;
  int nMaxWidth = 0;
  int nMaxHeight = 0;

  formatValues(&nMaxX, &nMaxY, &nMinX, &nMinY, &nMaxWidth, &nMaxHeight);


  QWidget *c;
  int b = 0;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_Width(nMaxWidth);
        #include "_form_property_switch.h"    

        b++;

      }

    } while (nextControl(&c));
  }
  if (b <= 1){
      QMessageBox::information( this, MYAPP,
        tr(
            "You have to select two controls at least,\n"       
            "before this does any usefully function."
            )
            );
  }

  updatePropertyWindowGeo();

}

void event_FORMAT_SET_SAME_HEIGHT()
{
  int nMaxX = 0;
  int nMaxY = 0;
  int nMinX = 999999;
  int nMinY = 999999;
  int nMaxWidth = 0;
  int nMaxHeight = 0;

  formatValues(&nMaxX, &nMaxY, &nMinX, &nMinY, &nMaxWidth, &nMaxHeight);

  QWidget *c;
  int b = 0;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_Height(nMaxHeight);
        #include "_form_property_switch.h"    

        b++;

      }

    } while (nextControl(&c));
  }
  if (b <= 1){
      QMessageBox::information( this, MYAPP,
        tr(
            "You have to select two controls at least,\n"       
            "before this does any usefully function."
            )
            );
  }

  updatePropertyWindowGeo();

}       

void event_FORMAT_SET_SAME_SIZE()
{
  int nMaxX = 0;
  int nMaxY = 0;
  int nMinX = 999999;
  int nMinY = 999999;
  int nMaxWidth = 0;
  int nMaxHeight = 0;

  formatValues(&nMaxX, &nMaxY, &nMinX, &nMinY, &nMaxWidth, &nMaxHeight);

  QWidget *c;
  int b = 0;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_Width(nMaxWidth);
        #define SWITCH2 SETPROPERTY_Height(nMaxHeight);
        #include "_form_property_switch.h"            

        b++;

      }

    } while (nextControl(&c));
  }
  if (b <= 1){
      QMessageBox::information( this, MYAPP,
        tr(
            "You have to select two controls at least,\n"       
            "before this does any usefully function."
            )
            );
  }

  updatePropertyWindowGeo();

}       

void event_FORMAT_LAYOUT_HORIZONTALLY()
{ 

  vec.clear();

  QWidget *c;
  int b = 0;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        b++;

        if (vec.size() > 0){

          int X;

          #define SWITCH GETPROPERTY_X();      
          #define SWITCH3 X
          #include "_form_property_switch.h"   
          #undef SWITCH3

          int b = 0;
          QVector<QWidget *>::iterator it;

          for( it = vec.begin(); it != vec.end(); ++it ){
            if ((*it)->x() < X){
              vec.insert(it, c);
              b++;
              break;
            }
          }
          if (b == false){
            vec.append(c);
          }
        } else {
          vec.append(c);
        }
      }

    } while (nextControl(&c));
  }
  int n = vec.size();
  
  if (n > 0){

    c = vec[n - 1];

    int x;

    #define SWITCH GETPROPERTY_X();      
    #define SWITCH3 x
    #include "_form_property_switch.h"   
    #undef SWITCH3

    for (int i = n - 1; i >= 0; i--){

      c = vec[i];

      #define SWITCH SETPROPERTY_X(x);
      #include "_form_property_switch.h"    

      c->move(x - XSCROLLBAR, vec[i]->y());

      x += vec[i]->width() + 5;
    }

  }
  if (b <= 1){
      QMessageBox::information( this, MYAPP,
        tr(
            "You have to select two controls at least,\n"       
            "before this does any usefully function."
            )
            );
  }


  updatePropertyWindowGeo();

}       

void event_FORMAT_LAYOUT_VERTICALLY()
{

  vec.clear();

  QWidget *c;
  int b = 0;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        b++;

        if (vec.size() > 0){

          int Y;

          #define SWITCH GETPROPERTY_Y();      
          #define SWITCH3 Y
          #include "_form_property_switch.h"   
          #undef SWITCH3

          int b = 0;
          QVector<QWidget *>::iterator it;

          for( it = vec.begin(); it != vec.end(); ++it ){
            if ((*it)->y() < Y){
              vec.insert(it, c);
              b++;
              break;
            }
          }
          if (b == false){
            vec.append(c);
          }
        } else {
          vec.append(c);
        }
      }

    } while (nextControl(&c));
  }
  int n = vec.size();
  
  if (n > 0){

    c = vec[n - 1];

    int y;

    #define SWITCH GETPROPERTY_Y();      
    #define SWITCH3 y
    #include "_form_property_switch.h"   
    #undef SWITCH3

    for (int i = n - 1; i >= 0; i--){

      c = vec[i];

      #define SWITCH SETPROPERTY_Y(y);
      #include "_form_property_switch.h"    

      c->move(vec[i]->x(), y - YSCROLLBAR);

      y += vec[i]->height() + 5;
    }

  }
  if (b <= 1){
      QMessageBox::information( this, MYAPP,
        tr(
            "You have to select two controls at least,\n"       
            "before this does any usefully function."
            )
            );
  }

  updatePropertyWindowGeo();

}       

void event_FORMAT_MOVE_TO_FRONT();
void event_FORMAT_MOVE_TO_BACK();
// *** 
#endif

void focusInEvent ( QFocusEvent * e);
void focusOutEvent( QFocusEvent * e);

#ifdef RUN
void enterEvent  ( QEvent * e )
{
    QWidget::enterEvent(e);
    EVENT_OnEnter();
  
}
#endif

#ifdef RUN
void leaveEvent  ( QEvent * e )
{
    QWidget::leaveEvent(e);
    EVENT_OnExit();
}
#endif

void show ();
void hide ();

#ifdef IDE
bool newEvent (QString sControlName, QString sEvent, QString sParameter);
void addTable (QString s);
#endif

void mouseDoubleClickEvent ( QMouseEvent * e );


#ifdef IDE
int mouseX( QMouseEvent * e)
{
  return e->x() + XSCROLLBAR;
}

int mouseY( QMouseEvent * e)
{
  return e->y() + YSCROLLBAR;
}

void setParentControl(QWidget *c, int x, int y, bool bInsert = false);
#endif

void mousePressEvent ( QMouseEvent * e );

bool insertControl(int x, int y, bool bUpdatePropertyWindow = true, int width = -1, int height = -1);


void mouseReleaseEvent ( QMouseEvent * e );

#ifdef IDE
bool hasSelectedControls () 
{  
  QWidget *c;

  if (firstControl(&c)){

    do {

      if (c->acceptDrops()){
        return true;
      }

    } while (nextControl(&c)); 
  }

  return false;
}

#endif



#ifdef IDE

int frameW()
{
  return width();
  
}

int frameH()
{
  return height();
}

bool moveControls ( QMouseEvent * e );

QWidget *insideHeader(int x, int y, int w, int h);
QWidget *insideFooter(int x, int y, int w, int h);

QWidget *insideTab(int x, int y, int w, int h);
QWidget *insideVBox(int x, int y, int w, int h);
QWidget *insideHBox(int x, int y, int w, int h);
QWidget *insideVHBox(int x, int y, int w, int h);
QWidget *insideVSplit(int x, int y, int w, int h);
QWidget *insideHSplit(int x, int y, int w, int h);
#endif

void mouseMoveEvent ( QMouseEvent * e );



#ifdef IDE
QSize checkFrameMinSize ();

#endif

void keyPressEvent ( QKeyEvent * e );

#ifdef IDE
void showFocusOrder(bool bChange = true);
void showSQLSettings(bool bChange = true);
void showSQLTables(bool bChange = true);


#endif

_controlType controlType(QWidget *c)
{
  
#ifdef IDE
  if (serialports.isType((_serialport *) c)) return t_serialport;
  if (headers.isType((_header *) c)) return t_header;
  if (footers.isType((_footer *) c)) return t_footer;
  if (labels.isType((_label *) c)) return t_label;
  if (movies.isType((_movie *) c)) return t_movie;
  if (sounds.isType((_sound *) c)) return t_sound;
  if (webs.isType((_web *) c)) return t_web;
  if (lines.isType((_line *) c)) return t_line;
  if (toolbuttons.isType((_toolbutton *) c)) return t_toolbutton;
  if (resizeboxes.isType((_resizebox *) c)) return t_resizebox;
  if (commandlinkbuttons.isType((_commandlinkbutton *) c)) return t_commandlinkbutton;
  if (svgs.isType((_svg *) c)) return t_svg;
  if (toolbarviews.isType((_toolbarview *) c)) return t_toolbarview;
  if (formsviews.isType((_formsview *) c)) return t_formsview;
  if (sliders.isType((_slider *) c)) return t_slider;
  if (spinboxes.isType((_spinbox *) c)) return t_spinbox;
  if (scrollbars.isType((_scrollbar *) c)) return t_scrollbar;
  if (udpsockets.isType((_udpsocket *) c)) return t_udpsocket;
  // CONTROL
  /*
  if (vsplits.isType((_vsplit *) c)) return t_vsplit;
  if (hsplits.isType((_hsplit *) c)) return t_hsplit;
  if (vhboxes.isType((_vhbox *) c)) return t_vhbox;
  if (hboxes.isType((_hbox *) c)) return t_hbox;
  if (vboxes.isType((_vbox *) c)) return t_vbox;*/
  if (boxes.isType((_box *) c)) return t_box;
  if (commandbuttons.isType((_commandbutton *) c)) return t_commandbutton;
  if (checkboxes.isType((_checkbox *) c)) return t_checkbox;
  if (frames.isType((_frame *) c)) return t_frame;
  if (listboxes.isType((_listbox *) c)) return t_listbox;
  if (radiobuttons.isType((_radiobutton *) c)) return t_radiobutton;
  if (tabs.isType((_tab *) c)) return t_tab;
  if (textboxes.isType((_textbox *) c)) return t_textbox;
  if (progressbars.isType((_progressbar *) c)) return t_progressbar;
  //if (scrollbars.isType((_scrollbar *) c)) return t_scrollbar;
  if (images.isType((_image *) c)) return t_image;
  if (timers.isType((_timer *) c)) return t_timer;
  if (treeviews.isType((_treeview *) c)) return t_treeview;
  if (comboboxes.isType((_combobox *) c)) return t_combobox;

  //if (lines.isType((_line *) c)) return t_line;
  //if (rectangles.isType((_rectangle *) c)) return t_rectangle;
  //if (circles.isType((_circle *) c)) return t_circle;
//  if (hiddens.isType((_hidden *) c)) return t_hidden;
  
  //if (activexes.isType((_activex *) c)) return t_activex;

  if (imagebuttons.isType((_imagebutton *) c)) return t_imagebutton;
  if (childcontrols.isType((_childcontrol *) c)) return t_childcontrol;
  if (browsers.isType((_browser *) c)) return t_browser;
  if (editors.isType((_editor *) c)) return t_editor;
  if (dateboxes.isType((_datebox *) c)) return t_datebox;
  if (timeboxes.isType((_timebox *) c)) return t_timebox;
  if (datetimeboxes.isType((_datetimebox *) c)) return t_datetimebox;

#elif defined(RUN)
  if (serialports.isType((kb_serialport *) c)) return t_serialport;
  if (headers.isType((kb_header *) c)) return t_header;
  if (footers.isType((kb_footer *) c)) return t_footer;
  if (labels.isType((kb_label *) c)) return t_label;
  if (movies.isType((kb_movie *) c)) return t_movie;
  if (sounds.isType((kb_sound *) c)) return t_sound;
  if (webs.isType((kb_web *) c)) return t_web;
  if (lines.isType((kb_line *) c)) return t_line;
  if (toolbuttons.isType((kb_toolbutton *) c)) return t_toolbutton;
  if (resizeboxes.isType((kb_resizebox *) c)) return t_resizebox;
  if (commandlinkbuttons.isType((kb_commandlinkbutton *) c)) return t_commandlinkbutton;
  if (svgs.isType((kb_svg *) c)) return t_svg;
  if (toolbarviews.isType((kb_toolbarview *) c)) return t_toolbarview;
  if (formsviews.isType((kb_formsview *) c)) return t_formsview;
  if (sliders.isType((kb_slider *) c)) return t_slider;
  if (spinboxes.isType((kb_spinbox *) c)) return t_spinbox;
  if (scrollbars.isType((kb_scrollbar *) c)) return t_scrollbar;
  if (udpsockets.isType((kb_udpsocket *) c)) return t_udpsocket;

  // CONTROL
  /*
  if (vsplits.isType((kb_vsplit *) c)) return t_vsplit;
  if (hsplits.isType((kb_hsplit *) c)) return t_hsplit;
  if (vhboxes.isType((kb_vhbox *) c)) return t_vhbox;
  if (hboxes.isType((kb_hbox *) c)) return t_hbox;
  if (vboxes.isType((kb_vbox *) c)) return t_vbox;*/
  if (boxes.isType((kb_box *) c)) return t_box;
  if (commandbuttons.isType((kb_commandbutton *) c)) return t_commandbutton;
  if (checkboxes.isType((kb_checkbox *) c)) return t_checkbox;
  if (frames.isType((kb_frame *) c)) return t_frame;
  if (listboxes.isType((kb_listbox *) c)) return t_listbox;
  if (radiobuttons.isType((kb_radiobutton *) c)) return t_radiobutton;
  if (tabs.isType((kb_tab *) c)) return t_tab;
  if (textboxes.isType((kb_textbox *) c)) return t_textbox;
  if (progressbars.isType((kb_progressbar *) c)) return t_progressbar;
  //if (scrollbars.isType((kb_scrollbar *) c)) return t_scrollbar;
  if (images.isType((kb_image *) c)) return t_image;
  if (timers.isType((kb_timer *) c)) return t_timer;
  if (treeviews.isType((kb_treeview *) c)) return t_treeview;
  if (comboboxes.isType((kb_combobox *) c)) return t_combobox;

  //if (lines.isType((kb_line *) c)) return t_line;
  //if (rectangles.isType((kb_rectangle *) c)) return t_rectangle;
  //if (circles.isType((kb_circle *) c)) return t_circle;
//  if (hiddens.isType((kb_hidden *) c)) return t_hidden;
  
  //if (activexes.isType((kb_activex *) c)) return t_activex;

  if (imagebuttons.isType((kb_imagebutton *) c)) return t_imagebutton;
  if (childcontrols.isType((kb_childcontrol *) c)) return t_childcontrol;
  if (browsers.isType((kb_browser *) c)) return t_browser;
  if (editors.isType((kb_editor *) c)) return t_editor;
  if (dateboxes.isType((kb_datebox *) c)) return t_datebox;
  if (timeboxes.isType((kb_timebox *) c)) return t_timebox;
  if (datetimeboxes.isType((kb_datetimebox *) c)) return t_datetimebox;
#endif

  return t_notype;


}

void keyReleaseEvent ( QKeyEvent * e );


#ifdef IDE
void moveTabRelated(QWidget *c, int x, int y);
#endif



void my_move(QWidget *c, int x, int y, int mx2 = 0, int my2 = 0);
void setGeo(QWidget *c, int x, int y, int w, int h);

void incX(QWidget *c, int n)
{
#ifdef IDE
  moveTabRelated(c, c->x() + n, c->y());
#endif
  #define SWITCH incX(n);
  #include "_form_property_switch.h"            
}

void incY(QWidget *c, int n)
{
#ifdef IDE
  moveTabRelated(c, c->x(), c->y() + n);
#endif
  #define SWITCH incY(n);
  #include "_form_property_switch.h"            
}

void decX(QWidget *c, int n)
{
#ifdef IDE
  moveTabRelated(c, c->x() - n, c->y());
#endif
  #define SWITCH decX(n);
  #include "_form_property_switch.h"            
}

void decY(QWidget *c, int n)
{
#ifdef IDE
  moveTabRelated(c, c->x(), c->y() - n);
#endif
  #define SWITCH decY(n);
  #include "_form_property_switch.h"            
}

void incWidth(QWidget *c, int n)
{
  #define SWITCH incWidth(n);
  #include "_form_property_switch.h"            
}

void incHeight(QWidget *c, int n)
{
  #define SWITCH incHeight(n);
  #include "_form_property_switch.h"            
}

void decWidth(QWidget *c, int n)
{
  #define SWITCH decWidth(n);
  #include "_form_property_switch.h"            
}

void decHeight(QWidget *c, int n)
{
  #define SWITCH decHeight(n);
  #include "_form_property_switch.h"            
}

t_boolean METHOD_insertControl(QWidget *c, _controlType controlType)
{
  return METHOD_insertControl(c, controlType, 0, 0, false);
}

t_boolean METHOD_insertControl(QWidget *c, _controlType controlType, int x, int y, bool bMove = true, QString s2 = "", bool bShow = true);

t_boolean METHOD_deleteControl(bool bFirst = true);

void previewReport();
void printDialog();


void deleteControl(QWidget *c);

#ifdef IDE



void selectControl(QWidget *c)
{
  bool b = c->acceptDrops();
  c->setAcceptDrops(!b); // missused as selected flag
  c->update();
}

void unselectControl(QWidget *c)
{
  c->setAcceptDrops(false); // missused as selected flag
  c->update();
}

void selectControlAlways(QWidget *c)
{
  c->setAcceptDrops(true); // missused as selected flag
  c->update();
}

typedef QList<t_properties2> undoRedoControls;
QVector<undoRedoControls> undoRedoStacks;
int nUndoRedo;
bool bUndoRedoLastNewFormMove;
bool bUndoRedoLastNewFormResize;
bool bUndoRedoSaveLast;
bool bPerformUndoRedo;
bool bLastWasUndo;

void newUndoRedo(bool bIgnoreBlocking = false, bool bFormMoveOnly = false, bool bFormResizeOnly = false, bool bLastAppend = false);

bool hasUndo()
{
  return nUndoRedo > -1;
}

bool hasRedo()
{
  return nUndoRedo + 1 < undoRedoStacks.size();
}

void performUndoRedo(bool bRedo);
void performUndo();
void performRedo();


void unselectAllControls()
{
  QWidget *c;

  if (firstControl(&c)){

    do {
      c->setAcceptDrops(false); // missused as selected flag
      c->update();
    } while (nextControl(&c)); 

  }

}      

bool controlSelected()
{
  QWidget *c;

  if (firstControl(&c)){

    do {
      if (c->acceptDrops()) return true; // missused as selected flag
    } while (nextControl(&c)); 

  }
  return false;

}           
#endif

QString getFilename(){ return sFilename; }

QString getPath();

QString getFilenameWithoutPath(QString ss = "")
{ 
  QString s;

  if (ss == ""){
    s = sFilename;
  } else {
    s = ss;
  }

  int i = s.lastIndexOf('/');
  s = s.right(s.length() - i - 1);
  return s; 
}

QString getFilenameWithoutPathAndExtension()
{ 
  QString s;

  s = sFilename;

  int i = s.lastIndexOf('/');
  s = s.right(s.length() - i - 1);

  i = s.lastIndexOf('.');
  s = s.left(i);
  return s; 
}

static QString getFilenameWithoutPathAndExtension(QString ss)
{ 
  QString s;
  s = ss;

  int i = s.lastIndexOf('/');
  s = s.right(s.length() - i - 1);

  i = s.lastIndexOf('.');
  s = s.left(i);
  return s; 
}





void load( const QString& fn)
{
  sFilename  = fn;

#ifdef IDE
   if (sFilename.endsWith(".kbasic_report", Qt::CaseInsensitive)) setWindowIcon(kbasicIcon(kbasicPath("ide/PROJECT_NEW_REPORT.png")));
   bLoading = true;
   QString q = EXTERN_my_mainwindow->trFilename(sFilename);
   if (QFile::exists(q)){
     loadForm(q);
   } else {
     loadForm(sFilename);
   }
#else
   loadForm(sFilename);
#endif
  
#ifdef IDE
  setNonModified();
  updateCaption(getFilenameWithoutPath());
  focusInEvent(0);
  bLoading = false;
  

#endif
  bLoaded = true;

}

#ifdef IDE
virtual void save()
{
  if (saveForm(EXTERN_my_mainwindow->trFilename(getFilename()))){
    setNonModified();
  }
}

void saveAs()
{
    QString fn = QFileDialog::getSaveFileName(this, tr("SaveAs"), sFilename, QString::null);
    if (!fn.isEmpty()){
      QFile f(fn);

      if (f.exists()){
	      switch( QMessageBox::warning( this, tr("Save As"), 
	          tr("File %1 already exists. Do want to overwrite?").arg( fn ),
	          tr("Yes"), tr("No"), tr("Cancel") ) ) {
	        case 0:
            bool b = sFilename != fn;
            sFilename = fn;
            if (saveForm(fn)){
              setNonModified();
            }

	          break;
	      }
      } else {
        bool b = sFilename != fn;
        sFilename = fn;
        if (saveForm(fn)){
          setNonModified();
        }
      }

    }

  updateCaption(getFilenameWithoutPath());

}

#endif

void updateCaption(QString s);

bool isModified();
void setNonModified();


void closeEvent( QCloseEvent *e );



#ifdef IDE

static QString getFormClassSourceCodeForSaving(QString sFilename)
{
  QString ss = "";
  int n = getFormClassSourceCodeFilePos(sFilename, &ss);
  ss = ss.mid(n);

  return ss;

}

static QString getFormClassSourceCode(QString sFileName, QString & sAllText, bool bAddHeader)
{
  QString ss = "";
  int n = getFormClassSourceCodeFilePos(sFileName, &ss);  
  sAllText = ss;
  ss = ss.mid(n);


  QString g = "";

  if (bAddHeader){
    g = "\nClass ";
    g += _form::getFilenameWithoutPathAndExtension(sFileName);
    g += " Inherits Form\n' ------------------------------------------------------------------------\n";
    g += "  \n";
    g += ss;
    g += "  \n";
    g += "' ------------------------------------------------------------------------\nEnd Class\n";
  } else {
    g = ss;
  }

  return g;

}

static bool saveFormClassSourceCodeOnly(QString m, QString k);


#endif

static QString getObjectNameFromFilename(QString s)
{
  QString sType = s;
  int i = sType.lastIndexOf('.');
  sType = sType.mid(i + 1);

  // OBJECT
  if (sType == "kbasic_file") sType = "File";
  else sType = "";

  return sType;
}

void readdToCollection(QWidget *c, QString old, QString s, const char *acType);
void addToCollection(QWidget *c, QString s, int nType);

_controlType getControlType(QString sTypeName)
{
  _controlType ct = t_notype; 

// CONTROL

  if (sTypeName.compare("Label", Qt::CaseInsensitive) == 0){
    ct = t_label;    
    
  } else if (sTypeName.compare("UdpSocket", Qt::CaseInsensitive) == 0){
    ct = t_udpsocket;  
  } else if (sTypeName.compare("ScrollBar", Qt::CaseInsensitive) == 0){
    ct = t_scrollbar;  
  } else if (sTypeName.compare("SpinBox", Qt::CaseInsensitive) == 0){
    ct = t_spinbox;  
  } else if (sTypeName.compare("Slider", Qt::CaseInsensitive) == 0){
    ct = t_slider;  
  } else if (sTypeName.compare("FormsView", Qt::CaseInsensitive) == 0){
    ct = t_formsview;  
  } else if (sTypeName.compare("ToolBarView", Qt::CaseInsensitive) == 0){
    ct = t_toolbarview;  
  } else if (sTypeName.compare("SvgBox", Qt::CaseInsensitive) == 0){
    ct = t_svg;  
  } else if (sTypeName.compare("CommandLinkButton", Qt::CaseInsensitive) == 0){
    ct = t_commandlinkbutton;  
  } else if (sTypeName.compare("ResizeBox", Qt::CaseInsensitive) == 0){
    ct = t_resizebox;  
  } else if (sTypeName.compare("ToolButton", Qt::CaseInsensitive) == 0){
    ct = t_toolbutton;  
  } else if (sTypeName.compare("Line", Qt::CaseInsensitive) == 0){
    ct = t_line;
  } else if (sTypeName.compare("MovieBox", Qt::CaseInsensitive) == 0){
    ct = t_movie;
  } else if (sTypeName.compare("Sound", Qt::CaseInsensitive) == 0){
    ct = t_sound;
  } else if (sTypeName.compare("WebView", Qt::CaseInsensitive) == 0){
    ct = t_web;
  } else if (sTypeName.compare("CommandButton", Qt::CaseInsensitive) == 0){
    ct = t_commandbutton;
  } else if (sTypeName.compare("CheckBox", Qt::CaseInsensitive) == 0){
    ct = t_checkbox;
  } else if (sTypeName.compare("Frame", Qt::CaseInsensitive) == 0){
    ct = t_frame;
  } else if (sTypeName.compare("ListBox", Qt::CaseInsensitive) == 0){
    ct = t_listbox;
  } else if (sTypeName.compare("RadioButton", Qt::CaseInsensitive) == 0){
    ct = t_radiobutton;
  } else if (sTypeName.compare("TabView", Qt::CaseInsensitive) == 0){
    ct = t_tab;
  } else if (sTypeName.compare("TextBox", Qt::CaseInsensitive) == 0){
    ct = t_textbox;
  } else if (sTypeName.compare("ProgressBar", Qt::CaseInsensitive) == 0){
    ct = t_progressbar;
  } else if (sTypeName.compare("ImageBox", Qt::CaseInsensitive) == 0){
    ct = t_image;
  } else if (sTypeName.compare("Timer", Qt::CaseInsensitive) == 0){
    ct = t_timer;
  } else if (sTypeName.compare("SerialPort", Qt::CaseInsensitive) == 0){
    ct = t_serialport;
  } else if (sTypeName.compare("TreeView", Qt::CaseInsensitive) == 0){
    ct = t_treeview;
  } else if (sTypeName.compare("ComboBox", Qt::CaseInsensitive) == 0){
    ct = t_combobox;
  //} else if (sTypeName.compare("Line", Qt::CaseInsensitive) == 0){
    //ct = t_line;
  //} else if (sTypeName.compare("Rectangle", Qt::CaseInsensitive) == 0){
    //ct = t_rectangle;
  //} else if (sTypeName.compare("Circle", Qt::CaseInsensitive) == 0){
    //ct = t_circle;
  } else if (sTypeName.compare("Hidden", Qt::CaseInsensitive) == 0){
    ct = t_hidden;
  //} else if (sTypeName.compare("ActiveX", Qt::CaseInsensitive) == 0){
    //ct = t_activex;

  } else if (sTypeName.compare("ImageButton", Qt::CaseInsensitive) == 0){
    ct = t_imagebutton;

  } else if (sTypeName.compare("Box", Qt::CaseInsensitive) == 0){
    ct = t_box;

  } else if (sTypeName.compare("FormView", Qt::CaseInsensitive) == 0){
    ct = t_childcontrol;

  } else if (sTypeName.compare("HtmlView", Qt::CaseInsensitive) == 0){
    ct = t_browser;

  } else if (sTypeName.compare("RichTextBox", Qt::CaseInsensitive) == 0){
    ct = t_editor;

  } else if (sTypeName.compare("DateBox", Qt::CaseInsensitive) == 0){
    ct = t_datebox;

  } else if (sTypeName.compare("TimeBox", Qt::CaseInsensitive) == 0){
    ct = t_timebox;

  } else if (sTypeName.compare("DateTimeBox", Qt::CaseInsensitive) == 0){
    ct = t_datetimebox;

  } else if (sTypeName.compare("Header", Qt::CaseInsensitive) == 0){
    ct = t_header;
  } else if (sTypeName.compare("Footer", Qt::CaseInsensitive) == 0){
    ct = t_footer;
  } else if (sTypeName.compare("VSplit", Qt::CaseInsensitive) == 0){
    ct = t_vsplit;
  } else if (sTypeName.compare("HSplit", Qt::CaseInsensitive) == 0){
    ct = t_hsplit;
  } else if (sTypeName.compare("HBox", Qt::CaseInsensitive) == 0){
    ct = t_hbox;
  } else if (sTypeName.compare("VBox", Qt::CaseInsensitive) == 0){
    ct = t_vbox;
  } else if (sTypeName.compare("VHBox", Qt::CaseInsensitive) == 0){
    ct = t_vhbox;
  }

  return ct;
}


int getControlType2(QString sTypeName)
{
  int n = 0; 
#ifdef RUN
// CONTROL

  if (sTypeName.compare("Label") == 0){
    n = pcode___label;    
    
  } else if (sTypeName.compare("UdpSocket") == 0){
    n = pcode___udpsocket;  
  } else if (sTypeName.compare("ScrollBar") == 0){
    n = pcode___scrollbar;  
  } else if (sTypeName.compare("SpinBox") == 0){
    n = pcode___spinbox;  
  } else if (sTypeName.compare("Slider") == 0){
    n = pcode___slider;  
  } else if (sTypeName.compare("FormsView") == 0){
    n = pcode___formsview;  
  } else if (sTypeName.compare("ToolBarView") == 0){
    n = pcode___toolbarview;  
  } else if (sTypeName.compare("SvgBox") == 0){
    n = pcode___svg;  
  } else if (sTypeName.compare("CommandLinkButton") == 0){
    n = pcode___commandlinkbutton;  
  } else if (sTypeName.compare("ResizeBox") == 0){
    n = pcode___resizebox;  
  } else if (sTypeName.compare("ToolButton") == 0){
    n = pcode___toolbutton;  
  } else if (sTypeName.compare("Line") == 0){
    n = pcode___line;
  } else if (sTypeName.compare("MovieBox") == 0){
    pcode___movie;
  } else if (sTypeName.compare("Sound") == 0){
    pcode___sound;
  } else if (sTypeName.compare("WebView") == 0){
    pcode___web;
  } else if (sTypeName.compare("CommandButton") == 0){
    pcode___commandbutton;
  } else if (sTypeName.compare("CheckBox") == 0){
    pcode___checkbox;
  } else if (sTypeName.compare("Frame") == 0){
    pcode___frame;
  } else if (sTypeName.compare("ListBox") == 0){
    pcode___listbox;
  } else if (sTypeName.compare("RadioButton") == 0){
    pcode___radiobutton;
  } else if (sTypeName.compare("TabView") == 0){
    pcode___tab;
  } else if (sTypeName.compare("TextBox") == 0){
    pcode___textbox;
  } else if (sTypeName.compare("ProgressBar") == 0){
    pcode___progressbar;
//   } else if (sTypeName.compare("ScrollBar") == 0){
//        pcode___scrollbar;
  } else if (sTypeName.compare("ImageBox") == 0){
    pcode___image;
  } else if (sTypeName.compare("Timer") == 0){
    pcode___timer;
  } else if (sTypeName.compare("SerialPort") == 0){
    pcode___serialport;
  } else if (sTypeName.compare("TreeView") == 0){
    pcode___treeview;
  } else if (sTypeName.compare("ComboBox") == 0){
    pcode___combobox;
  //} else if (sTypeName.compare("Line") == 0){
    //ct = t_line;
  //} else if (sTypeName.compare("Rectangle") == 0){
    //ct = t_rectangle;
  //} else if (sTypeName.compare("Circle") == 0){
    //ct = t_circle;
 // } else if (sTypeName.compare("Hidden") == 0){
 //   pcode___hidden;
  //} else if (sTypeName.compare("ActiveX") == 0){
    //pcode___activex;

  } else if (sTypeName.compare("ImageButton") == 0){
    pcode___imagebutton;

  } else if (sTypeName.compare("Box") == 0){
    pcode___box;

  } else if (sTypeName.compare("FormView") == 0){
    pcode___childcontrol;

  } else if (sTypeName.compare("HtmlView") == 0){
    pcode___browser;

  } else if (sTypeName.compare("RichTextBox") == 0){
    pcode___editor;

  } else if (sTypeName.compare("DateBox") == 0){
    pcode___datebox;

  } else if (sTypeName.compare("TimeBox") == 0){
    pcode___timebox;

  } else if (sTypeName.compare("DateTimeBox") == 0){
    pcode___datetimebox;

  } else if (sTypeName.compare("Header") == 0){
    pcode___header;
  } else if (sTypeName.compare("Footer") == 0){
    pcode___footer;
  } else if (sTypeName.compare("VSplit") == 0){
 //   pcode___vsplit;
 // } else if (sTypeName.compare("HSplit") == 0){
    /*
    pcode___hsplit;
  } else if (sTypeName.compare("HBox") == 0){
    pcode___hbox;
  } else if (sTypeName.compare("VBox") == 0){
    pcode___vbox;
  } else if (sTypeName.compare("VHBox") == 0){
    pcode___vhbox;*/
  }
#endif
  return n;
}

int getControlType(_controlType ct);


#ifdef IDE
void openFormDesign()
{
  if (!EXTERN_my_mainwindow->isFormFileOpened(getFilename(), true)){
    EXTERN_my_mainwindow->openForm(getFilename());
  }
}


void openFormClassSourceCode()
{
  QString s = getFilename();
  if (!EXTERN_my_mainwindow->isFormClassFileOpened(s, true)){
    EXTERN_my_mainwindow->openFormClassSourceCode(s);
  }
}


bool pasteAvailable () 
{  
  int n = 0;

  return n > 0;
}

bool undoAvailable () 
{  
  return false;
}

bool redoAvailable () 
{  
  return false;
}

void undo()
{
}

void redo()
{
}

void cut()
{
  copy();
  del();
}

void copy()
{
}

t_properties *prop;

void paste()
{
}

void del()
{
  METHOD_deleteControl();
}
#endif

#ifdef RUN
QString loadProjectFile (QString sFile);
t_pointer loadProjectFile(QString s, t_integer *nSize);
QPixmap loadProjectImage(QString sFile);
#endif

QWidget *getControl(QString s);


const QPixmap &loadPixmap(QString fn)
{
  static QPixmap p;

  p = QPixmap();
  if (!(fn.contains("/") || fn.contains("\\"))){

#ifdef RUN
      p = my_form_loadProjectImage(this, fn);
#elif defined (IDE)

      #ifdef _FORM
        fn = getPath() + "/" + fn;
      #else
        fn = getProjectPath() + "/" + fn;
      #endif

      if (QFile::exists(fn)){
        p = QPixmap(fn);
      }

#endif
    
  } else {

    if (QFile::exists(fn)){
      p = QPixmap(fn);
    }
    
  }

  return p;
  
}


public slots:

#ifdef RUN

void dockLocationChanged(Qt::DockWidgetArea area)
{
  EVENT_OnDockMove();
}

void topLevelChanged(bool topLevel)
{
  if (topLevel){
    EVENT_OnDockFloating();
  } else {
    EVENT_OnDockNotFloating();
  }
}

void visibilityChanged(bool visible)
{
  if (visible){
    EVENT_OnDockShow();
  } else {
    EVENT_OnDockHide();
  }
  
}

void frameChanged(int)
{  
  setWindowIcon(movie->currentPixmap());
}

void cursoranimation_frameChanged(int)
{
  setCursor(QCursor(cursoranimation_movie->currentPixmap()));
}


#endif


void XScrollBar_valueChanged(int value);
void YScrollBar_valueChanged(int value);


#ifdef RUN
void form_topLevelChanged(bool);
#endif

#ifdef IDE

void performApply(QWidget *c, int nIndex);

// used by the controls for their contextmenu
bool applyApply();

void _event_EDIT_APPLY();
void _event_EDIT_CUT();
void _event_EDIT_COPY();
void _event_EDIT_PASTE(bool bFirst = true);
void _event_EDIT_DELETE();

void _event_FORMAT_MOVE_TO_FRONT();
void _event_FORMAT_MOVE_TO_BACK();

void _event_ADDPAGE();
void _event_REMOVEPAGE();
void _event_RENAMEPAGE();
#endif

public:

bool bObjectEditor;
QString sObjectName;

#ifdef RUN
QSqlRelationalTableModel sqlm;
QTableView *sqlv;
#endif

protected:

#ifdef RUN
_main *main;
#else
QWidget *main;
#endif


QWidget *CurrentControl;

bool bSHIFT;
bool bCTRL;
bool bSelector;
bool bSelected;
bool bControlMove;
bool bRightButton;
bool bDoubleClick;



int nMouseOriginX;
int nMouseOriginY;

int nMouseX;
int nMouseY;

int nOldMouseX;
int nOldMouseY;

bool bMousePressed;
bool bMouseMove;
bool bFirstMouseMove;

public:
/*_vsplits vsplits;
_hsplits hsplits;
_vboxes vboxes;
_vhboxes vhboxes;
_hboxes hboxes;*/
_labels labels;
_headers headers;
_footers footers;
_serialports serialports;
_movies movies;
_sounds sounds;
_webs webs;
_lines lines;

// CONTROL

_udpsockets udpsockets;
_scrollbars scrollbars;
_spinboxes spinboxes;
_sliders sliders;
_formsviews formsviews;
_toolbarviews toolbarviews;
_svgs svgs;
_commandlinkbuttons commandlinkbuttons;
_resizeboxes resizeboxes;
_toolbuttons toolbuttons;
_commandbuttons commandbuttons;
_checkboxes checkboxes;
_frames frames;
_listboxes listboxes;
_radiobuttons radiobuttons;
_tabs tabs;
_textboxes textboxes;
_progressbars progressbars;

_images images;
_timers timers;
_treeviews treeviews;
_comboboxes comboboxes;

//_lines lines;
//_rectangles rectangles;
//_circles circles;
//_hiddens hiddens;

_imagebuttons imagebuttons;
//_activexes activexes;

_boxes boxes;
_childcontrols childcontrols;
_browsers browsers;
_editors editors;
_dateboxes dateboxes;
_timeboxes timeboxes;
_datetimeboxes datetimeboxes;


protected:


#ifdef IDE

QString sCoordinate;
t_properties pp;




QVector<QWidget *> vec;



QFrame *selector1;
QFrame *selector2;
QFrame *selector3;
QFrame *selector4;


_sourcecodeeditor *my_sourcecodeeditor;

#endif

#ifdef RUN

kb_form *ParentForm;
bool bOpened;
bool bMETHOD_Open_Opened;
bool bTableView;
bool bDialogRunning;
QSqlQuery q;
QMap<QString, t_variant>recordbuffer;

int nMoveOnMouseDragX;
int nMoveOnMouseDragY;

interpreter *myInterpreter;

bool bOnGoTo3First;
bool bOnGoTo3Children;

bool bQuerySize;
int nQuerySize;

void setQuerySize();


#endif

bool bEventClick;
bool bEventKeyPress;

bool bShowFocusOrder;
bool bShowSQLSettings;

QMovie *movie; QByteArray *moviea; QBuffer *movieb;
QMovie *cursoranimation_movie; QByteArray *cursoranimation_moviea; QBuffer *cursoranimation_movieb;


QWidget *form_parent;
QMap<_form*,_childcontrol*>layout_childcontrols;

QString sFilename;



int nTimerId;
int nTimerIdMove;
int nTimerIdResize;

int nMoveEventX;
int nMoveEventY;
int nMoveEventOldX;
int nMoveEventOldY;

int nResizeEventWidth;
int nResizeEventHeight;
int nResizeEventOldWidth;
int nResizeEventOldHeight;
QSize resizeSize;
QSize resizeOldSize;

QSize oldSize;

public:
#ifdef IDE
bool bLoading;
QScrollBar *XScrollBar;
QScrollBar *YScrollBar;
#endif

bool bLoaded;



bool bBlockOnceOpenModal;

bool bShowSQLTables;
int REPORT_pageCount();
QSizeF REPORT_pageSize();
QSizeF REPORT_docSize();
int REPORT_drawSection(QPainter* p, int nPage, int nSection);
int REPORT_draw(QPainter *p, int nPage);
void REPORT_drawControl(QPainter* p, QWidget *c, int nSection);
void REPORT_setMargin(int);
void REPORT_setPageSize(QSizeF);
void REPORT_print(QPrinter*);

//QString sInsertTypeOption;

#ifdef RUN

void actionEvent(QActionEvent *e){ QScrollArea::actionEvent(e); }
void changeEvent(QEvent *e){ QScrollArea::changeEvent(e); }
//void contextMenuEvent(QContextMenuEvent *e){ QScrollArea::contextMenuEvent(e); }
void dragEnterEvent(QDragEnterEvent *e){ QScrollArea::dragEnterEvent(e); }
void dragLeaveEvent(QDragLeaveEvent *e){ QScrollArea::dragLeaveEvent(e); }
void dragMoveEvent(QDragMoveEvent *e){ QScrollArea::dragMoveEvent(e); }
void dropEvent(QDropEvent *e){ QScrollArea::dropEvent(e); }
//void enterEvent(QEvent *e){ QScrollArea::enterEvent(e); }
//void focusInEvent(QFocusEvent *e){ QScrollArea::focusInEvent(e); }
//void focusOutEvent(QFocusEvent *e){ QScrollArea::focusOutEvent(e); }
//void hideEvent(QHideEvent *e){ QScrollArea::hideEvent(e); }
void inputMethodEvent(QInputMethodEvent *e){ QScrollArea::inputMethodEvent(e); }
//void keyPressEvent(QKeyEvent *e){ QScrollArea::keyPressEvent(e); }
//void keyReleaseEvent(QKeyEvent *e){ QScrollArea::keyReleaseEvent(e); }
//void leaveEvent(QEvent *e){ QScrollArea::leaveEvent(e); }
//void mouseDoubleClickEvent(QMouseEvent *e){ QScrollArea::mouseDoubleClickEvent(e); }
//void mouseMoveEvent(QMouseEvent *e){ QScrollArea::mouseMoveEvent(e); }
//void mousePressEvent(QMouseEvent *e){ QScrollArea::mousePressEvent(e); }
//void mouseReleaseEvent(QMouseEvent *e){ QScrollArea::mouseReleaseEvent(e); }
//void resizeEvent(QResizeEvent *e){ QScrollArea::resizeEvent(e); }
//void showEvent(QShowEvent *e){ QScrollArea::showEvent(e); }
void tabletEvent(QTabletEvent *e){ QScrollArea::tabletEvent(e); }
void wheelEvent(QWheelEvent *e){ QScrollArea::wheelEvent(e); }

int nFormId;


QDockWidget *dock;
int nTableViewCurrentX;
int nTableViewCurrentY;
QString sTableFilter;
QString sMNIDFilter;
bool bFirstResize;
bool bFirstDockResize;
QMap<QWidget*, QString> menusForButtons;
_form *my_form;

bool bFullscreen;  
QWidget *noFullScreenParent;
Qt::WindowFlags noFullScreenWindowFlags;
QPoint noFullScreenPos;
QSize noFullScreenSize;

bool bResizeEventFlag;

#endif

};


#ifdef RUN
class TableViewDelegate : public QItemDelegate
 {
     Q_OBJECT
 public:
     TableViewDelegate(_form *f, QObject *parent = 0);
     QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &,
         const QModelIndex &index) const;
     void setEditorData(QWidget *editor, const QModelIndex &index) const;
     void setModelData(QWidget *editor, QAbstractItemModel *model,
         const QModelIndex &index) const;
 private slots:
     void commitAndCloseEditor();
 private:
      QWidget *QModelIndexToWidget(const QModelIndex &index) const;

     _form *my_form; 
 };

class TableView : public QTableView
 {
     Q_OBJECT
 public:
     TableView(_form *f);
 private:
      void currentChanged ( const QModelIndex & current, const QModelIndex & previous );

     _form *my_form; 
 };
#endif

#ifdef RUN
  #undef SUPERCLASS
#endif

#undef _FORM



#endif