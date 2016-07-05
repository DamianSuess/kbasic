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

#include "../kbshared/_control.h"

#ifdef RUN

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
  #include "../kbasic_binding/_movie/kb_movie.h"
  #include "../kbasic_binding/_sound/kb_sound.h"
  #include "../kbasic_binding/_web/kb_web.h"

#include "../kbasic_binding/_checkbox/kb_checkbox.h"

  #include "../kbasic_binding/_header/kb_header.h"
  #include "../kbasic_binding/_footer/kb_footer.h"

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
  #include "../kbasic_binding/_serialport/kb_serialport.h"


#define SWITCH6 controlType()

_controlType _control::controlType()
{
  const char *ac =this->metaObject()->className();

  if (strcmp(ac, "_serialport") == 0) return t_serialport;
  if (strcmp(ac, "_header") == 0) return t_header;
  if (strcmp(ac, "_footer") == 0) return t_footer;
  if (strcmp(ac, "_label") == 0) return t_label;

  if (strcmp(ac, "_movie") == 0) return t_movie;
  if (strcmp(ac, "_sound") == 0) return t_sound;
  if (strcmp(ac, "_web") == 0) return t_web;
  if (strcmp(ac, "_line") == 0) return t_line;
  if (strcmp(ac, "_toolbutton") == 0) return t_toolbutton;
  if (strcmp(ac, "_resizebox") == 0) return t_resizebox;
  if (strcmp(ac, "_commandlinkbutton") == 0) return t_commandlinkbutton;
  if (strcmp(ac, "_svg") == 0) return t_svg;
  if (strcmp(ac, "_toolbarview") == 0) return t_toolbarview;
  if (strcmp(ac, "_formsview") == 0) return t_formsview;
  if (strcmp(ac, "_slider") == 0) return t_slider;
  if (strcmp(ac, "_spinbox") == 0) return t_spinbox;
  if (strcmp(ac, "_scrollbar") == 0) return t_scrollbar;
  
  // CONTROL
    
  if (strcmp(ac, "_udpsocket") == 0) return t_udpsocket;
  if (strcmp(ac, "_box") == 0) return t_box;
  if (strcmp(ac, "_commandbutton") == 0) return t_commandbutton;
  if (strcmp(ac, "_checkbox") == 0) return t_checkbox;
  if (strcmp(ac, "_frame") == 0) return t_frame;
  if (strcmp(ac, "_listbox") == 0) return t_listbox;
  if (strcmp(ac, "_radiobutton") == 0) return t_radiobutton;
  if (strcmp(ac, "_tab") == 0) return t_tab;
  if (strcmp(ac, "_textbox") == 0) return t_textbox;
  if (strcmp(ac, "_progressbar") == 0) return t_progressbar;
  if (strcmp(ac, "_image") == 0) return t_image;
  if (strcmp(ac, "_timer") == 0) return t_timer;
  if (strcmp(ac, "_treeview") == 0) return t_treeview;
  if (strcmp(ac, "_combobox") == 0) return t_combobox;
  if (strcmp(ac, "_browser") == 0) return t_browser;
  if (strcmp(ac, "_editor") == 0) return t_editor;
  if (strcmp(ac, "_datebox") == 0) return t_datebox;
  if (strcmp(ac, "_timebox") == 0) return t_timebox;
  if (strcmp(ac, "_datetimebox") == 0) return t_datetimebox;
  if (strcmp(ac, "_childcontrol") == 0) return t_childcontrol;
  if (strcmp(ac, "_serialport") == 0) return t_serialport;

  return t_notype;


}

void _control::METHOD_Move(t_integer X, t_integer Y)
{
  move(X, Y);
}

void _control::METHOD_Resize(t_integer Width, t_integer Height)
{
  resize(Width, Height);
}

void _control::METHOD_Show()
{
  show();
}

void _control::METHOD_Hide()
{
  hide();
}

void _control::METHOD_RepaintAlways()
{
  repaint();
}

void _control::METHOD_Repaint()
{
  update();
}

void _control::METHOD_Raise()
{
  raise();
}

void _control::METHOD_Lower()
{
  lower();
}

void _control::METHOD_Close()
{
}

void _control::METHOD_Open()
{
}

void _control::METHOD_SetFocus()
{
  setFocus();
}

void _control::SETPROPERTY_X(t_integer n)
{     
  QWidget *c = this;
  #define SWITCH SETPROPERTY_X(n);
  #include "_form_property_switch.h"    


  #define SWITCH SETPROPERTY_GlobalX(c->mapToGlobal(QPoint(n, 0)).x());
  #include "_form_property_switch.h"    

}

t_integer _control::GETPROPERTY_X()
{   
  QWidget *c = this;
  t_integer n = 0;
  #define SWITCH GETPROPERTY_X();
  #define SWITCH3 n
  #include "_form_property_switch.h"   
  #undef SWITCH3
  return n;
}

void _control::SETPROPERTY_Y(t_integer n)
{     
  QWidget *c = this;
  #define SWITCH SETPROPERTY_Y(n);
  #include "_form_property_switch.h"    

  #define SWITCH SETPROPERTY_GlobalY(c->mapToGlobal(QPoint(0, n)).y());
  #include "_form_property_switch.h"    

}

t_integer _control::GETPROPERTY_Y()
{   
  QWidget *c = this;
  t_integer n = 0;
  #define SWITCH GETPROPERTY_Y();
  #define SWITCH3 n
  #include "_form_property_switch.h"   
  #undef SWITCH3
  return n;
}

void _control::SETPROPERTY_Width(t_integer n)
{     
  QWidget *c = this;
  #define SWITCH SETPROPERTY_Width(n);
  #include "_form_property_switch.h"    
}

t_integer _control::GETPROPERTY_Width()
{   
  QWidget *c = this;
  t_integer n = 0;
  #define SWITCH GETPROPERTY_Width();
  #define SWITCH3 n
  #include "_form_property_switch.h"   
  #undef SWITCH3
  return n;
}

void _control::SETPROPERTY_Height(t_integer n)
{     
  QWidget *c = this;
  #define SWITCH SETPROPERTY_Height(n);
  #include "_form_property_switch.h"    
}

t_integer _control::GETPROPERTY_Height()
{   
  QWidget *c = this;
  t_integer n = 0;
  #define SWITCH GETPROPERTY_Height();
  #define SWITCH3 n
  #include "_form_property_switch.h"   
  #undef SWITCH3
  return n;
}

const QString & _control::GETPROPERTY_Name()
{
  QWidget *c = this;
  static QString n; n = "";
  #define SWITCH GETPROPERTY_Name();
  #define SWITCH3 n
  #include "_form_property_switch.h"   
  #undef SWITCH3
  return n;
}

const QString & _control::GETPROPERTY_Group()
{
  QWidget *c = this;
  static QString n; n = "";
  #define SWITCH GETPROPERTY_Group();
  #define SWITCH3 n
  #include "_form_property_switch.h"   
  #undef SWITCH3
  return n;
}

void _control::SETPROPERTY_Background(const QString & n)
{
  QWidget *c = this;
  #define SWITCH SETPROPERTY_Background(n);
  #include "_form_property_switch.h"   
}

const QString & _control::GETPROPERTY_Background()
{
  QWidget *c = this;
  static QString n; n = "";
  #define SWITCH GETPROPERTY_Background();
  #define SWITCH3 n
  #include "_form_property_switch.h"   
  #undef SWITCH3
  return n;
}

void _control::SETPROPERTY_BackgroundStyle(const QString & n)
{
  QWidget *c = this;
  #define SWITCH SETPROPERTY_BackgroundStyle(n);
  #include "_form_property_switch.h"   
}

const QString & _control::GETPROPERTY_BackgroundStyle()
{
  QWidget *c = this;
  static QString n; n = "";
  #define SWITCH GETPROPERTY_BackgroundStyle();
  #define SWITCH3 n
  #include "_form_property_switch.h"   
  #undef SWITCH3
  return n;
}

void _control::SETPROPERTY_Palette(const QString & n)
{
  QWidget *c = this;
  #define SWITCH SETPROPERTY_Palette(n);
  #include "_form_property_switch.h"   
}

const QString & _control::GETPROPERTY_Palette()
{
  QWidget *c = this;
  static QString n; n = "";
  #define SWITCH GETPROPERTY_Palette();
  #define SWITCH3 n
  #include "_form_property_switch.h"   
  #undef SWITCH3
  return n;
}

t_integer _control::GETPROPERTY_GlobalX()
{   
  QWidget *c = this;
  t_integer n = 0;
  #define SWITCH GETPROPERTY_GlobalX();
  #define SWITCH3 n
  #include "_form_property_switch.h"   
  #undef SWITCH3
  return n;
}

t_integer _control::GETPROPERTY_GlobalY()
{   
  QWidget *c = this;
  t_integer n = 0;
  #define SWITCH GETPROPERTY_GlobalY();
  #define SWITCH3 n
  #include "_form_property_switch.h"   
  #undef SWITCH3
  return n;
}

t_integer _control::GETPROPERTY_OldX()
{   
  QWidget *c = this;
  t_integer n = 0;
  #define SWITCH GETPROPERTY_OldX();
  #define SWITCH3 n
  #include "_form_property_switch.h"   
  #undef SWITCH3
  return n;
}

t_integer _control::GETPROPERTY_OldY()
{   
  QWidget *c = this;
  t_integer n = 0;
  #define SWITCH GETPROPERTY_OldY();
  #define SWITCH3 n
  #include "_form_property_switch.h"   
  #undef SWITCH3
  return n;
}

t_integer _control::GETPROPERTY_OldWidth()
{   
  QWidget *c = this;
  t_integer n = 0;
  #define SWITCH GETPROPERTY_OldWidth();
  #define SWITCH3 n
  #include "_form_property_switch.h"   
  #undef SWITCH3
  return n;
}

t_integer _control::GETPROPERTY_OldHeight()
{   
  QWidget *c = this;
  t_integer n = 0;
  #define SWITCH GETPROPERTY_OldHeight();
  #define SWITCH3 n
  #include "_form_property_switch.h"   
  #undef SWITCH3
  return n;
}

void _control::SETPROPERTY_MinimumWidth(t_integer n)
{     
  QWidget *c = this;
  #define SWITCH SETPROPERTY_MinimumWidth(n);
  #include "_form_property_switch.h"    
}

t_integer _control::GETPROPERTY_MinimumWidth()
{   
  QWidget *c = this;
  t_integer n = 0;
  #define SWITCH GETPROPERTY_MinimumWidth();
  #define SWITCH3 n
  #include "_form_property_switch.h"   
  #undef SWITCH3
  return n;
}

void _control::SETPROPERTY_MinimumHeight(t_integer n)
{     
  QWidget *c = this;
  #define SWITCH SETPROPERTY_MinimumHeight(n);
  #include "_form_property_switch.h"    
}

t_integer _control::GETPROPERTY_MinimumHeight()
{   
  QWidget *c = this;
  t_integer n = 0;
  #define SWITCH GETPROPERTY_MinimumHeight();
  #define SWITCH3 n
  #include "_form_property_switch.h"   
  #undef SWITCH3
  return n;
}

void _control::SETPROPERTY_MaximumWidth(t_integer n)
{     
  QWidget *c = this;
  #define SWITCH SETPROPERTY_MaximumWidth(n);
  #include "_form_property_switch.h"    
}

t_integer _control::GETPROPERTY_MaximumWidth()
{   
  QWidget *c = this;
  t_integer n = 0;
  #define SWITCH GETPROPERTY_MaximumWidth();
  #define SWITCH3 n
  #include "_form_property_switch.h"   
  #undef SWITCH3
  return n;
}

void _control::SETPROPERTY_MaximumHeight(t_integer n)
{     
  QWidget *c = this;
  #define SWITCH SETPROPERTY_MaximumHeight(n);
  #include "_form_property_switch.h"    
}

t_integer _control::GETPROPERTY_MaximumHeight()
{   
  QWidget *c = this;
  t_integer n = 0;
  #define SWITCH GETPROPERTY_MaximumHeight();
  #define SWITCH3 n
  #include "_form_property_switch.h"   
  #undef SWITCH3
  return n;
}

void _control::SETPROPERTY_Tag(const QString & n)
{
  QWidget *c = this;
  #define SWITCH SETPROPERTY_Tag(n);
  #include "_form_property_switch.h"   
}

const QString & _control::GETPROPERTY_Tag()
{
  QWidget *c = this;
  static QString n; n = "";
  #define SWITCH GETPROPERTY_Tag();
  #define SWITCH3 n
  #include "_form_property_switch.h"   
  #undef SWITCH3
  return n;
}

void _control::SETPROPERTY_CSV(const QString & n)
{
  QWidget *c = this;
  #define SWITCH SETPROPERTY_CSV(n);
  #include "_form_property_switch.h"   
}

const QString & _control::GETPROPERTY_CSV()
{
  QWidget *c = this;
  static QString n; n = "";
  #define SWITCH GETPROPERTY_CSV();
  #define SWITCH3 n
  #include "_form_property_switch.h"   
  #undef SWITCH3
  return n;
}

const QString & _control::GETPROPERTY_ParentControl()
{
  QWidget *c = this;
  static QString n; n = "";
  #define SWITCH GETPROPERTY_ParentControl();
  #define SWITCH3 n
  #include "_form_property_switch.h"   
  #undef SWITCH3
  return n;
}

const QString & _control::GETPROPERTY_ParentForm()
{
  QWidget *c = this;
  static QString n; n = "";
  #define SWITCH GETPROPERTY_ParentForm();
  #define SWITCH3 n
  #include "_form_property_switch.h"   
  #undef SWITCH3
  return n;
}

void _control::SETPROPERTY_DragDrop(t_boolean n)
{
  QWidget *c = this;
  #define SWITCH SETPROPERTY_DragDrop(n);
  #include "_form_property_switch.h"   
}

t_boolean _control::GETPROPERTY_DragDrop()
{
  QWidget *c = this;
  t_boolean n = 0;
  #define SWITCH GETPROPERTY_DragDrop();
  #define SWITCH3 n
  #include "_form_property_switch.h"   
  #undef SWITCH3
  return n;
}

const QString & _control::GETPROPERTY_ControlType()
{
  QWidget *c = this;
  static QString n; n = "";
  #define SWITCH GETPROPERTY_ControlType();
  #define SWITCH3 n
  #include "_form_property_switch.h"   
  #undef SWITCH3
  return n;
}

t_boolean _control::GETPROPERTY_Focus()
{
  QWidget *c = this;
  t_boolean n = 0;
  #define SWITCH GETPROPERTY_Focus();
  #define SWITCH3 n
  #include "_form_property_switch.h"   
  #undef SWITCH3
  return n;
}

void _control::SETPROPERTY_FocusPolicy(const QString & n)
{
  QWidget *c = this;
  #define SWITCH SETPROPERTY_FocusPolicy(n);
  #include "_form_property_switch.h"   
}

const QString & _control::GETPROPERTY_FocusPolicy()
{
  QWidget *c = this;
  static QString n; n = "";
  #define SWITCH GETPROPERTY_FocusPolicy();
  #define SWITCH3 n
  #include "_form_property_switch.h"   
  #undef SWITCH3
  return n;
}

void _control::SETPROPERTY_FocusProxy(const QString & n)
{
  QWidget *c = this;
  #define SWITCH SETPROPERTY_FocusProxy(n);
  #include "_form_property_switch.h"   
}

const QString & _control::GETPROPERTY_FocusProxy()
{
  QWidget *c = this;
  static QString n; n = "";
  #define SWITCH GETPROPERTY_FocusProxy();
  #define SWITCH3 n
  #include "_form_property_switch.h"   
  #undef SWITCH3
  return n;
}

t_integer _control::GETPROPERTY_FocusOrder()
{   
  QWidget *c = this;
  t_integer n = 0;
  #define SWITCH GETPROPERTY_FocusOrder();
  #define SWITCH3 n
  #include "_form_property_switch.h"   
  #undef SWITCH3
  return n;
}

void _control::SETPROPERTY_Cursor(const QString & n)
{
  QWidget *c = this;
  #define SWITCH SETPROPERTY_Cursor(n);
  #include "_form_property_switch.h"   
}

const QString & _control::GETPROPERTY_Cursor()
{
  QWidget *c = this;
  static QString n; n = "";
  #define SWITCH GETPROPERTY_Cursor();
  #define SWITCH3 n
  #include "_form_property_switch.h"   
  #undef SWITCH3
  return n;
}

void _control::SETPROPERTY_FontName(const QString & n)
{
  QWidget *c = this;
  #define SWITCH SETPROPERTY_FontName(n);
  #include "_form_property_switch.h"   
}

const QString & _control::GETPROPERTY_FontName()
{
  QWidget *c = this;
  static QString n; n = "";
  #define SWITCH GETPROPERTY_FontName();
  #define SWITCH3 n
  #include "_form_property_switch.h"   
  #undef SWITCH3
  return n;
}

void _control::SETPROPERTY_FontSize(t_integer n)
{     
  QWidget *c = this;
  #define SWITCH SETPROPERTY_FontSize(n);
  #include "_form_property_switch.h"    
}

t_integer _control::GETPROPERTY_FontSize()
{   
  QWidget *c = this;
  t_integer n = 0;
  #define SWITCH GETPROPERTY_FontSize();
  #define SWITCH3 n
  #include "_form_property_switch.h"   
  #undef SWITCH3
  return n;
}

void _control::SETPROPERTY_FontItalic(t_boolean n)
{
  QWidget *c = this;
  #define SWITCH SETPROPERTY_FontItalic(n);
  #include "_form_property_switch.h"   
}

t_boolean _control::GETPROPERTY_FontItalic()
{
  QWidget *c = this;
  t_boolean n = 0;
  #define SWITCH GETPROPERTY_FontItalic();
  #define SWITCH3 n
  #include "_form_property_switch.h"   
  #undef SWITCH3
  return n;
}

void _control::SETPROPERTY_FontBold(t_boolean n)
{
  QWidget *c = this;
  #define SWITCH SETPROPERTY_FontBold(n);
  #include "_form_property_switch.h"   
}

t_boolean _control::GETPROPERTY_FontBold()
{
  QWidget *c = this;
  t_boolean n = 0;
  #define SWITCH GETPROPERTY_FontBold();
  #define SWITCH3 n
  #include "_form_property_switch.h"   
  #undef SWITCH3
  return n;
}

void _control::SETPROPERTY_FontUnderline(t_boolean n)
{
  QWidget *c = this;
  #define SWITCH SETPROPERTY_FontUnderline(n);
  #include "_form_property_switch.h"   
}

t_boolean _control::GETPROPERTY_FontUnderline()
{
  QWidget *c = this;
  t_boolean n = 0;
  #define SWITCH GETPROPERTY_FontUnderline();
  #define SWITCH3 n
  #include "_form_property_switch.h"   
  #undef SWITCH3
  return n;
}

void _control::SETPROPERTY_FontColor(const QString & n)
{
  QWidget *c = this;
  #define SWITCH SETPROPERTY_FontColor(n);
  #include "_form_property_switch.h"   
}

const QString & _control::GETPROPERTY_FontColor()
{
  QWidget *c = this;
  static QString n; n = "";
  #define SWITCH GETPROPERTY_FontColor();
  #define SWITCH3 n
  #include "_form_property_switch.h"   
  #undef SWITCH3
  return n;
}

void _control::SETPROPERTY_Enabled(t_boolean n)
{
  QWidget *c = this;
  #define SWITCH SETPROPERTY_Enabled(n);
  #include "_form_property_switch.h"   
}

t_boolean _control::GETPROPERTY_Enabled()
{
  QWidget *c = this;
  t_boolean n = 0;
  #define SWITCH GETPROPERTY_Enabled();
  #define SWITCH3 n
  #include "_form_property_switch.h"   
  #undef SWITCH3
  return n;
}

void _control::SETPROPERTY_Visible(t_boolean n)
{
  QWidget *c = this;
  #define SWITCH SETPROPERTY_Visible(n);
  #include "_form_property_switch.h"   
}

t_boolean _control::GETPROPERTY_Visible()
{
  QWidget *c = this;
  t_boolean n = 0;
  #define SWITCH GETPROPERTY_Visible();
  #define SWITCH3 n
  #include "_form_property_switch.h"   
  #undef SWITCH3
  return n;
}

void _control::SETPROPERTY_StatusTip(const QString & n)
{
  QWidget *c = this;
  #define SWITCH SETPROPERTY_StatusTip(n);
  #include "_form_property_switch.h"   
}

const QString & _control::GETPROPERTY_StatusTip()
{
  QWidget *c = this;
  static QString n; n = "";
  #define SWITCH GETPROPERTY_StatusTip();
  #define SWITCH3 n
  #include "_form_property_switch.h"   
  #undef SWITCH3
  return n;
}

void _control::SETPROPERTY_ToolTip(const QString & n)
{
  QWidget *c = this;
  #define SWITCH SETPROPERTY_ToolTip(n);
  #include "_form_property_switch.h"   
}

const QString & _control::GETPROPERTY_ToolTip()
{
  QWidget *c = this;
  static QString n; n = "";
  #define SWITCH GETPROPERTY_ToolTip();
  #define SWITCH3 n
  #include "_form_property_switch.h"   
  #undef SWITCH3
  return n;
}

void _control::SETPROPERTY_StyleSheet(const QString & n)
{
  QWidget *c = this;
  #define SWITCH SETPROPERTY_StyleSheet(n);
  #include "_form_property_switch.h"   
}

const QString & _control::GETPROPERTY_StyleSheet()
{
  QWidget *c = this;
  static QString n; n = "";
  #define SWITCH GETPROPERTY_StyleSheet();
  #define SWITCH3 n
  #include "_form_property_switch.h"   
  #undef SWITCH3
  return n;
}

void _control::SETPROPERTY_WhatsThis(const QString & n)
{
  QWidget *c = this;
  #define SWITCH SETPROPERTY_WhatsThis(n);
  #include "_form_property_switch.h"   
}

const QString & _control::GETPROPERTY_WhatsThis()
{
  QWidget *c = this;
  static QString n; n = "";
  #define SWITCH GETPROPERTY_WhatsThis();
  #define SWITCH3 n
  #include "_form_property_switch.h"   
  #undef SWITCH3
  return n;
}

void _control::SETPROPERTY_TimerInterval(t_integer n)
{     
  QWidget *c = this;
  #define SWITCH SETPROPERTY_TimerInterval(n);
  #include "_form_property_switch.h"    
}

t_integer _control::GETPROPERTY_TimerInterval()
{   
  QWidget *c = this;
  t_integer n = 0;
  #define SWITCH GETPROPERTY_TimerInterval();
  #define SWITCH3 n
  #include "_form_property_switch.h"   
  #undef SWITCH3
  return n;
}

void _control::SETPROPERTY_Opacity(t_integer n)
{     
  QWidget *c = this;
  #define SWITCH SETPROPERTY_Opacity(n);
  #include "_form_property_switch.h"    
}

t_integer _control::GETPROPERTY_Opacity()
{   
  QWidget *c = this;
  t_integer n = 0;
  #define SWITCH GETPROPERTY_Opacity();
  #define SWITCH3 n
  #include "_form_property_switch.h"   
  #undef SWITCH3
  return n;
}

void _control::SETPROPERTY_SQLName(const QString & n)
{
  QWidget *c = this;
  #define SWITCH SETPROPERTY_SQLName(n);
  #include "_form_property_switch.h"   
}

const QString & _control::GETPROPERTY_SQLName()
{
  QWidget *c = this;
  static QString n; n = "";
  #define SWITCH GETPROPERTY_SQLName();
  #define SWITCH3 n
  #include "_form_property_switch.h"   
  #undef SWITCH3
  return n;
}

void _control::SETPROPERTY_SQL(const QString & n)
{
  QWidget *c = this;
  QVariant v = c->property("__kb1979.ControlType.kb__");
  if (v.isValid() && (v.toString() == "ComboBox" || v.toString() == "ListBox" || v.toString() == "TextBox" || v.toString() == "RichTextBox")){
    #define SWITCH SETPROPERTY_SQL(n);
    #include "_form_property_switch.h"   
  }
}

const QString & _control::GETPROPERTY_SQL()
{
  QWidget *c = this;
  static QString n; n = "";
  QVariant v = c->property("__kb1979.ControlType.kb__");
  if (v.isValid() && (v.toString() == "ComboBox" || v.toString() == "ListBox" || v.toString() == "TextBox" || v.toString() == "RichTextBox")){
    #define SWITCH GETPROPERTY_SQL();
    #define SWITCH3 n
    #include "_form_property_switch.h"   
    #undef SWITCH3
  }
  return n;
}


void _control::SETPROPERTY_CursorAnimation(const QString & n)
{
  QWidget *c = this;

  #define SWITCH SETPROPERTY_SQL(n);
  #include "_form_property_switch.h"     
}

QString _control::GETPROPERTY_CursorAnimation()
{
  QWidget *c = this;
  static QString n; n = "";

  #define SWITCH GETPROPERTY_CursorAnimation();
  #define SWITCH3 n
  #include "_form_property_switch.h"   
  #undef SWITCH3
  
  return n;
}



void _control::SETPROPERTY_SQLRelation(const QString & n)
{
  QWidget *c = this;
  #define SWITCH SETPROPERTY_SQLRelation(n);
  #include "_form_property_switch.h"   
}

const QString & _control::GETPROPERTY_SQLRelation()
{
  QWidget *c = this;
  static QString n; n = "";
  #define SWITCH GETPROPERTY_SQLRelation();
  #define SWITCH3 n
  #include "_form_property_switch.h"   
  #undef SWITCH3
  return n;
}


void _control::SETPROPERTY_Mask(const QString & n)
{
  QWidget *c = this;
  #define SWITCH SETPROPERTY_Mask(n);
  #include "_form_property_switch.h"   
}

const QString & _control::GETPROPERTY_Mask()
{
  QWidget *c = this;
  static QString n; n = "";
  #define SWITCH GETPROPERTY_Mask();
  #define SWITCH3 n
  #include "_form_property_switch.h"   
  #undef SWITCH3
  return n;
}

void _control::SETPROPERTY_TableViewCaption(const QString & n)
{
  QWidget *c = this;
  #define SWITCH SETPROPERTY_TableViewCaption(n);
  #include "_form_property_switch.h"   
}

const QString & _control::GETPROPERTY_TableViewCaption()
{
  QWidget *c = this;
  static QString n; n = "";
  #define SWITCH GETPROPERTY_TableViewCaption();
  #define SWITCH3 n
  #include "_form_property_switch.h"   
  #undef SWITCH3
  return n;
}

void _control::SETPROPERTY_TableViewSort(const QString & n)
{
  QWidget *c = this;
  #define SWITCH SETPROPERTY_TableViewSort(n);
  #include "_form_property_switch.h"   
}

const QString & _control::GETPROPERTY_TableViewSort()
{
  QWidget *c = this;
  static QString n; n = "";
  #define SWITCH GETPROPERTY_TableViewSort();
  #define SWITCH3 n
  #include "_form_property_switch.h"   
  #undef SWITCH3
  return n;
}

void _control::SETPROPERTY_TableViewFilter(const QString & n)
{
  QWidget *c = this;
  #define SWITCH SETPROPERTY_TableViewFilter(n);
  #include "_form_property_switch.h"   
}

const QString & _control::GETPROPERTY_TableViewFilter()
{
  QWidget *c = this;
  static QString n; n = "";
  #define SWITCH GETPROPERTY_TableViewFilter();
  #define SWITCH3 n
  #include "_form_property_switch.h"   
  #undef SWITCH3
  return n;
}

void _control::SETPROPERTY_TableViewWidth(t_integer n)
{
  QWidget *c = this;
  #define SWITCH SETPROPERTY_TableViewWidth(n);
  #include "_form_property_switch.h"   
}

t_integer _control::GETPROPERTY_TableViewWidth()
{
  QWidget *c = this;
  static t_integer n; n = 0;
  #define SWITCH GETPROPERTY_TableViewWidth();
  #define SWITCH3 n
  #include "_form_property_switch.h"   
  #undef SWITCH3
  return n;
}


void _control::SETPROPERTY_MouseTracking(t_boolean n)
{
  QWidget *c = this;
  #define SWITCH SETPROPERTY_MouseTracking(n);
  #include "_form_property_switch.h"   
}

t_boolean _control::GETPROPERTY_MouseTracking()
{
  QWidget *c = this;
  static t_boolean n; n = false;
  #define SWITCH GETPROPERTY_MouseTracking();
  #define SWITCH3 n
  #include "_form_property_switch.h"   
  #undef SWITCH3
  return n;
}

void _control::SETPROPERTY_TableViewVisible(t_boolean n)
{
  QWidget *c = this;
  #define SWITCH SETPROPERTY_TableViewVisible(n);
  #include "_form_property_switch.h"   
}

t_boolean _control::GETPROPERTY_TableViewVisible()
{
  QWidget *c = this;
  static t_boolean n; n = false;
  #define SWITCH GETPROPERTY_TableViewWidth();
  #define SWITCH3 n
  #include "_form_property_switch.h"   
  #undef SWITCH3
  return n;
}

// PROPERTY
void _control::SETPROPERTY_TableViewOrder(t_integer n)
{
  QWidget *c = this;
  #define SWITCH SETPROPERTY_TableViewOrder(n);
  #include "_form_property_switch.h"   
}

t_integer _control::GETPROPERTY_TableViewOrder()
{
  QWidget *c = this;
  static t_integer n; n = 0;
  #define SWITCH GETPROPERTY_TableViewOrder();
  #define SWITCH3 n
  #include "_form_property_switch.h"   
  #undef SWITCH3
  return n;
}

void _control::SETPROPERTY_DrawOnPaint(t_boolean n)
{
  QWidget *c = this;
  #define SWITCH SETPROPERTY_DrawOnPaint(n);
  #include "_form_property_switch.h"   
}

t_boolean _control::GETPROPERTY_DrawOnPaint()
{
  QWidget *c = this;
  static t_boolean n; n = 0;
  #define SWITCH GETPROPERTY_DrawOnPaint();
  #define SWITCH3 n
  #include "_form_property_switch.h"   
  #undef SWITCH3
  return n;
}



void _control::SETPROPERTY_SoundOnEvent(const QString & n)
{
  QWidget *c = this;
  #define SWITCH SETPROPERTY_SoundOnEvent(n);
  #include "_form_property_switch.h"   
}

QString _control::GETPROPERTY_SoundOnEvent()
{
  QWidget *c = this;
  static QString n; n = "";
  #define SWITCH GETPROPERTY_SoundOnEvent();
  #define SWITCH3 n
  #include "_form_property_switch.h"   
  #undef SWITCH3
  return n;
}

void _control::SETPROPERTY_LoadedX(t_integer n)
{
  QWidget *c = this;
  #define SWITCH SETPROPERTY_LoadedX(n);
  #include "_form_property_switch.h"   
}

t_integer _control::GETPROPERTY_LoadedX()
{
  QWidget *c = this;
  static t_integer n; n = 0;
  #define SWITCH GETPROPERTY_LoadedX();
  #define SWITCH3 n
  #include "_form_property_switch.h"   
  #undef SWITCH3
  return n;
}

void _control::SETPROPERTY_LoadedY(t_integer n)
{
  QWidget *c = this;
  #define SWITCH SETPROPERTY_LoadedY(n);
  #include "_form_property_switch.h"   
}

t_integer _control::GETPROPERTY_LoadedY()
{
  QWidget *c = this;
  static t_integer n; n = 0;
  #define SWITCH GETPROPERTY_LoadedY();
  #define SWITCH3 n
  #include "_form_property_switch.h"   
  #undef SWITCH3
  return n;
}

void _control::SETPROPERTY_LoadedWidth(t_integer n)
{
  QWidget *c = this;
  #define SWITCH SETPROPERTY_LoadedWidth(n);
  #include "_form_property_switch.h"   
}

t_integer _control::GETPROPERTY_LoadedWidth()
{
  QWidget *c = this;
  static t_integer n; n = 0;
  #define SWITCH GETPROPERTY_LoadedWidth();
  #define SWITCH3 n
  #include "_form_property_switch.h"   
  #undef SWITCH3
  return n;
}


void _control::SETPROPERTY_LoadedHeight(t_integer n)
{
  QWidget *c = this;
  #define SWITCH SETPROPERTY_LoadedHeight(n);
  #include "_form_property_switch.h"   
}

t_integer _control::GETPROPERTY_LoadedHeight()
{
  QWidget *c = this;
  static t_integer n; n = 0;
  #define SWITCH GETPROPERTY_LoadedHeight();
  #define SWITCH3 n
  #include "_form_property_switch.h"   
  #undef SWITCH3
  return n;
}



void _control::METHOD_DataRemove(QString Id)
{
  QWidget *c = this;
  #define SWITCH METHOD_DataRemove(Id);
  #include "_form_property_switch.h"   
}

void _control::METHOD_DataRemoveAll()
{
  QWidget *c = this;
  #define SWITCH METHOD_DataRemoveAll();
  #include "_form_property_switch.h"   
}

void _control::METHOD_DataSetBoolean(QString Id, t_boolean Value)
{
  QWidget *c = this;
  #define SWITCH METHOD_DataSetBoolean(Id, Value);
  #include "_form_property_switch.h"   
}

void _control::METHOD_DataSetInteger(QString Id, t_integer Value)
{
  QWidget *c = this;
  #define SWITCH METHOD_DataSetInteger(Id, Value);
  #include "_form_property_switch.h"   
}

void _control::METHOD_DataSetString(QString Id, QString Value)
{
  QWidget *c = this;
  #define SWITCH METHOD_DataSetString(Id, Value);
  #include "_form_property_switch.h"   
}

void _control::METHOD_DataSetDouble(QString Id, t_double Value)
{
  QWidget *c = this;
  #define SWITCH METHOD_DataSetDouble(Id, Value);
  #include "_form_property_switch.h"   
}

void _control::METHOD_DataSetLong(QString Id, t_long Value)
{
  QWidget *c = this;
  #define SWITCH METHOD_DataSetLong(Id, Value);
  #include "_form_property_switch.h"   
}

void _control::METHOD_DataSetDecimal(QString Id, t_currency Value)
{
  QWidget *c = this;
  #define SWITCH METHOD_DataSetDecimal(Id, Value);
  #include "_form_property_switch.h"   
}

void _control::METHOD_DataSetDateTime(QString Id, t_date Value)
{
  QWidget *c = this;
  #define SWITCH METHOD_DataSetDateTime(Id, Value);
  #include "_form_property_switch.h"   
}



t_long _control::METHOD_DataLong(QString Id)
{  
  QWidget *c = this;
  static t_long n; n = 0;
  #define SWITCH METHOD_DataLong(Id);
  #define SWITCH3 n
  #include "_form_property_switch.h"   
  #undef SWITCH3
  return n;
}

t_currency _control::METHOD_DataDecimal(QString Id)
{  
  QWidget *c = this;
  static t_currency n;
  #define SWITCH METHOD_DataDecimal(Id);
  #define SWITCH3 n
  #include "_form_property_switch.h"   
  #undef SWITCH3
  return n;
}

t_date _control::METHOD_DataDateTime(QString Id)
{  
  QWidget *c = this;
  static t_date n;
  #define SWITCH METHOD_DataDateTime(Id);
  #define SWITCH3 n
  #include "_form_property_switch.h"   
  #undef SWITCH3
  return n;
}

t_boolean _control::METHOD_DataBoolean(QString Id)
{  
  QWidget *c = this;
  static t_boolean n; n = 0;
  #define SWITCH METHOD_DataBoolean(Id);
  #define SWITCH3 n
  #include "_form_property_switch.h"   
  #undef SWITCH3
  return n;
}

t_integer _control::METHOD_DataInteger(QString Id)
{
  QWidget *c = this;
  static t_integer n; n = 0;
  #define SWITCH METHOD_DataInteger(Id);
  #define SWITCH3 n
  #include "_form_property_switch.h"   
  #undef SWITCH3
  return n;
}

QString _control::METHOD_DataString(QString Id)
{
  QWidget *c = this;
  static QString n; n = "";
  #define SWITCH METHOD_DataString(Id);
  #define SWITCH3 n
  #include "_form_property_switch.h"   
  #undef SWITCH3
  return n;
}

t_double _control::METHOD_DataDouble(QString Id)
{
  QWidget *c = this;
  static t_double n; n = 0;
  #define SWITCH METHOD_DataDouble(Id);
  #define SWITCH3 n
  #include "_form_property_switch.h"   
  #undef SWITCH3
  return n;
}

void _control::METHOD_ClearFocus()
{
  QWidget *c = this;
  #define SWITCH METHOD_ClearFocus();
  #include "_form_property_switch.h"   
}


void _control::METHOD_ToggleVisible()
{
  QWidget *c = this;
  #define SWITCH METHOD_ToggleVisible();
  #include "_form_property_switch.h"   
}

void _control::METHOD_SingleShot(t_integer Milliseconds)
{
  QWidget *c = this;
  #define SWITCH METHOD_SingleShot(Milliseconds);
  #include "_form_property_switch.h"   
}


void _control::METHOD_StartTimer()
{
  QWidget *c = this;
  #define SWITCH METHOD_StartTimer();
  #include "_form_property_switch.h"   
}


void _control::METHOD_StopTimer()
{
  QWidget *c = this;
  #define SWITCH METHOD_StopTimer();
  #include "_form_property_switch.h"   
}


t_integer _control::METHOD_LocalX(t_integer GlobalX)
{
  QWidget *c = this;
  static t_integer n; n = 0;
  #define SWITCH METHOD_LocalX(GlobalX);
  #define SWITCH3 n
  #include "_form_property_switch.h"   
  #undef SWITCH3
  return n;
}

t_integer _control::METHOD_LocalY(t_integer GlobalY)
{
  QWidget *c = this;
  static t_integer n; n = 0;
  #define SWITCH METHOD_LocalY(GlobalY);
  #define SWITCH3 n
  #include "_form_property_switch.h"   
  #undef SWITCH3
  return n;
}

t_integer _control::METHOD_GlobalX(t_integer LocalX)
{
  QWidget *c = this;
  static t_integer n; n = 0;
  #define SWITCH METHOD_GlobalX(LocalX);
  #define SWITCH3 n
  #include "_form_property_switch.h"   
  #undef SWITCH3
  return n;
}

t_integer _control::METHOD_GlobalY(t_integer LocalY)
{
  QWidget *c = this;
  static t_integer n; n = 0;
  #define SWITCH METHOD_GlobalY(LocalY);
  #define SWITCH3 n
  #include "_form_property_switch.h"   
  #undef SWITCH3
  return n;
}

t_boolean _control::METHOD_UnderMouse()
{
  QWidget *c = this;
  static t_boolean n; n = 0;
  #define SWITCH METHOD_UnderMouse();
  #define SWITCH3 n
  #include "_form_property_switch.h"   
  #undef SWITCH3
  return n;
}

#undef SWITCH6

#endif
