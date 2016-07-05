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



#ifndef _IMAGEBUTTON_H
#define _IMAGEBUTTON_H


#include <QWidget>

#include "typedef.h"

#include <QSvgWidget>
#include <QSvgRenderer>

#ifdef RUN
#include "_sounds.h"
extern _sounds2 *EXTERN_my_sounds;
#endif


#ifdef IDE
extern QString sInsertTypeOption;
extern void copy_controlimage(QString s);
extern int nInsert_Width;  
extern int nInsert_Height;
#endif

#include <qpixmap.h>
#include <qstring.h>

#include "_property.h"
#include "_control0.h"

#define TEST _imagebutton  
#define TEST2 _imagebuttons   
#define TEST3 "ImageButton"
#define SUPERCLASS QWidget   

#define _IMAGEBUTTON true

class _form;


class _imagebutton : public QWidget, public _property
{
  Q_OBJECT
public:


_imagebutton(_form *f = 0, QWidget *parent = 0) : QWidget (parent ? parent : (QWidget *) f)
{
  constructor(f, parent);

  setAutoFillBackground(true);
  QPalette p = palette();
  p.setColor(QPalette::Window, Qt::white);  
  setPalette(p);

  // properties
#ifdef RUN
  addProperty("StringValue", pt_qstring); addProperty("OldStringValue", pt_qstring);
#endif
  addProperty("Caption", pt_qstring);
  addProperty("Icon", pt_qstring);
  addProperty("Key", pt_qstring);
  addProperty("ContextMenu", pt_qstring);

  //addProperty("AutoDefault", pt_boolean);
  addProperty("Checkable", pt_boolean);
  addProperty("CheckableExclusive", pt_boolean);
  addProperty("Checked", pt_boolean);
  //addProperty("Default", pt_boolean);

  addProperty("CheckEnterImage", pt_qstring);
  addProperty("CheckExitImage", pt_qstring);
  addProperty("CheckMouseDownImage", pt_qstring);
  addProperty("CheckMouseUpImage", pt_qstring);
  addProperty("CheckEnabledImage", pt_qstring);
  addProperty("CheckDisabledImage", pt_qstring);

  addProperty("EnterImage", pt_qstring);
  addProperty("ExitImage", pt_qstring);
  addProperty("MouseDownImage", pt_qstring);
  addProperty("MouseUpImage", pt_qstring);
  addProperty("EnabledImage", pt_qstring);
  addProperty("DisabledImage", pt_qstring);

  addProperty("EnterSound", pt_qstring);
  addProperty("ExitSound", pt_qstring);
  addProperty("MouseDownSound", pt_qstring);
  addProperty("MouseUpSound", pt_qstring);

  addProperty("Scale", pt_boolean);

  // events
  addProperty("OnEvent", pt_event);

  // default values  
  SETPROPERTY_Caption("ImageButton");
  SETPROPERTY_ControlType("ImageButton");
  SETPROPERTY_Visible(true);
  SETPROPERTY_Enabled(true);

#ifdef IDE
  SETPROPERTY_EnabledImage(kbasicPath("ide/tux.png"));
#else
  setFocusPolicy(Qt::TabFocus);
#endif

#ifdef IDE
  if (sInsertTypeOption.contains("vista_bar_commandbutton", Qt::CaseInsensitive)){
    SETPROPERTY_Caption("CommandButton (Bar)");    

    copy_controlimage("vista_bar_commandbutton_enabled.png");
    copy_controlimage("vista_bar_commandbutton_checkedenabled.png");
    copy_controlimage("vista_bar_commandbutton_enter.png");
    copy_controlimage("vista_bar_commandbutton_checkedenter.png");

    SETPROPERTY_EnabledImage("vista_bar_commandbutton_enabled.png");  
    SETPROPERTY_CheckEnabledImage("vista_bar_commandbutton_checkedenabled.png");  
    SETPROPERTY_EnterImage("vista_bar_commandbutton_enter.png");  
    SETPROPERTY_CheckEnterImage("vista_bar_commandbutton_checkedenter.png");  
    SETPROPERTY_MouseDownImage("vista_bar_commandbutton_checkedenabled.png");  

    nInsert_Width = 158;  
    nInsert_Height = 27;
    SETPROPERTY_FontColor("&HFFFFFF");  
    SETPROPERTY_Scale(true);

  } else if (sInsertTypeOption.contains("vista_window_close", Qt::CaseInsensitive)){
    SETPROPERTY_Caption("");    

    copy_controlimage("vista_window_close_enabled.png");
    copy_controlimage("vista_window_close_enter.png");
    copy_controlimage("vista_window_close_mousedown.png");

    SETPROPERTY_EnabledImage("vista_window_close_enabled.png");  
    SETPROPERTY_EnterImage("vista_window_close_enter.png");  
    SETPROPERTY_MouseDownImage("vista_window_close_mousedown.png");  

    nInsert_Width = 28;  
    nInsert_Height = 15;
    SETPROPERTY_FontColor("&HFFFFFF");  
    SETPROPERTY_Scale(true);

  } else if (sInsertTypeOption.contains("vista_window_minimize", Qt::CaseInsensitive)){
    SETPROPERTY_Caption("");    

    copy_controlimage("vista_window_minimize_enabled.png");
    copy_controlimage("vista_window_minimize_enter.png");
    copy_controlimage("vista_window_minimize_mousedown.png");

    SETPROPERTY_EnabledImage("vista_window_minimize_enabled.png");  
    SETPROPERTY_EnterImage("vista_window_minimize_enter.png");  
    SETPROPERTY_MouseDownImage("vista_window_minimize_mousedown.png");  

    nInsert_Width = 28;  
    nInsert_Height = 15;
    SETPROPERTY_FontColor("&HFFFFFF");  
    SETPROPERTY_Scale(true);

  } else if (sInsertTypeOption.contains("vista_window_maximize", Qt::CaseInsensitive)){
    SETPROPERTY_Caption("");    

    copy_controlimage("vista_window_maximize_enabled.png");
    copy_controlimage("vista_window_maximize_enter.png");
    copy_controlimage("vista_window_maximize_mousedown.png");

    SETPROPERTY_EnabledImage("vista_window_maximize_enabled.png");  
    SETPROPERTY_EnterImage("vista_window_maximize_enter.png");  
    SETPROPERTY_MouseDownImage("vista_window_maximize_mousedown.png");  

    nInsert_Width = 28;  
    nInsert_Height = 15;
    SETPROPERTY_FontColor("&HFFFFFF");  
    SETPROPERTY_Scale(true);

  } else if (sInsertTypeOption.contains("vista_button_arrowleft", Qt::CaseInsensitive)){
    SETPROPERTY_Caption("");    

    copy_controlimage("vista_button_arrowleft.png");
    copy_controlimage("vista_button_arrowleft_enter.png");

    SETPROPERTY_EnabledImage("vista_button_arrowleft.png");  
    SETPROPERTY_EnterImage("vista_button_arrowleft_enter.png");  

    nInsert_Width = 24;  
    nInsert_Height = 24;
    SETPROPERTY_Scale(true);

  } else if (sInsertTypeOption.contains("vista_button_arrowright", Qt::CaseInsensitive)){
    SETPROPERTY_Caption("");    

    copy_controlimage("vista_button_arrowright.png");
    copy_controlimage("vista_button_arrowright_enter.png");

    SETPROPERTY_EnabledImage("vista_button_arrowright.png");  
    SETPROPERTY_EnterImage("vista_button_arrowright_enter.png");  

    nInsert_Width = 24;  
    nInsert_Height = 24;
    SETPROPERTY_Scale(true);

  } else if (sInsertTypeOption.contains("vista_buttonblack_middle", Qt::CaseInsensitive)){
    SETPROPERTY_Caption("Button Black (Middle)");    

    copy_controlimage("vista_buttonblack_middle.png");
    copy_controlimage("vista_buttonblack_middle_enter.png");
    copy_controlimage("vista_buttonblack_middle_mousedown.png");

    SETPROPERTY_EnabledImage("vista_buttonblack_middle.png");  
    SETPROPERTY_EnterImage("vista_buttonblack_middle_enter.png");  
    SETPROPERTY_MouseDownImage("vista_buttonblack_middle_mousedown.png");  

    nInsert_Width = 53;  
    nInsert_Height = 24;
    SETPROPERTY_FontColor("&HFFFFFF");  
    SETPROPERTY_Scale(true);

  } else if (sInsertTypeOption.contains("vista_button_middle", Qt::CaseInsensitive)){
    SETPROPERTY_Caption("Button (Middle)");    

    copy_controlimage("vista_button_middle.png");
    copy_controlimage("vista_button_middle_enter.png");
    copy_controlimage("vista_button_middle_mousedown.png");

    SETPROPERTY_EnabledImage("vista_button_middle.png");  
    SETPROPERTY_EnterImage("vista_button_middle_enter.png");  
    SETPROPERTY_MouseDownImage("vista_button_middle_mousedown.png");  

    nInsert_Width = 53;  
    nInsert_Height = 24;
    SETPROPERTY_FontColor("&HFFFFFF");  
    SETPROPERTY_Scale(true);

  } else if (sInsertTypeOption.contains("vista_button_left", Qt::CaseInsensitive)){
    SETPROPERTY_Caption("Button (Left)");    

    copy_controlimage("vista_button_left.png");
    copy_controlimage("vista_button_left_enter.png");
    copy_controlimage("vista_button_left_mousedown.png");

    SETPROPERTY_EnabledImage("vista_button_left.png");  
    SETPROPERTY_EnterImage("vista_button_left_enter.png");  
    SETPROPERTY_MouseDownImage("vista_button_left_mousedown.png");  

    nInsert_Width = 53;  
    nInsert_Height = 24;
    SETPROPERTY_FontColor("&HFFFFFF");  
    SETPROPERTY_Scale(true);

  } else if (sInsertTypeOption.contains("vista_button_right", Qt::CaseInsensitive)){
    SETPROPERTY_Caption("Button (Right)");    

    copy_controlimage("vista_button_right.png");
    copy_controlimage("vista_button_right_enter.png");
    copy_controlimage("vista_button_right_mousedown.png");

    SETPROPERTY_EnabledImage("vista_button_right.png");  
    SETPROPERTY_EnterImage("vista_button_right_enter.png");  
    SETPROPERTY_MouseDownImage("vista_button_right_mousedown.png");  

    nInsert_Width = 53;  
    nInsert_Height = 24;
    SETPROPERTY_FontColor("&HFFFFFF");  
    SETPROPERTY_Scale(true);

  } else if (sInsertTypeOption.contains("vista_selection_black", Qt::CaseInsensitive)){
    SETPROPERTY_Caption("Selection (Black)");    

    copy_controlimage("vista_selection_black.png");

    SETPROPERTY_EnabledImage("");  
    SETPROPERTY_EnterImage("vista_selection_black.png");  
    SETPROPERTY_ExitImage(" ");  

    nInsert_Width = 132;  
    nInsert_Height = 33;
    SETPROPERTY_FontColor("&HFFFFFF");  
    SETPROPERTY_Scale(true);
    
  } else if (sInsertTypeOption.contains("vista_selection_white", Qt::CaseInsensitive)){
    SETPROPERTY_Caption("Selection (White)");    

    copy_controlimage("vista_selection_white_enter.png");
    copy_controlimage("vista_selection_white_checkedenabled.png");
    copy_controlimage("vista_selection_white_checkedenter.png");

    SETPROPERTY_EnabledImage("");  
    SETPROPERTY_EnterImage("vista_selection_white_enter.png");  
    SETPROPERTY_ExitImage(" ");  
    SETPROPERTY_CheckEnabledImage("vista_selection_white_checkedenabled.png");  
    SETPROPERTY_CheckEnterImage("vista_selection_white_checkedenter");  

    nInsert_Width = 246;  
    nInsert_Height = 36;
    SETPROPERTY_Scale(true);

  } else if (sInsertTypeOption.contains("vista_navigation_right", Qt::CaseInsensitive)){
    SETPROPERTY_Caption("");    

    copy_controlimage("vista_navigation_right_mousedown.png");
    copy_controlimage("vista_navigation_right_disabled.png");
    copy_controlimage("vista_navigation_right_enabled.png");
    copy_controlimage("vista_navigation_right_enter.png");

    SETPROPERTY_EnabledImage("vista_navigation_right_enabled.png");  
    SETPROPERTY_DisabledImage("vista_navigation_right_disabled.png");  
    SETPROPERTY_EnterImage("vista_navigation_right_enter.png");  
    SETPROPERTY_MouseDownImage("vista_navigation_right_mousedown.png");  

    nInsert_Width = 30;  
    nInsert_Height = 30;
    SETPROPERTY_Scale(true);

  } else if (sInsertTypeOption.contains("vista_navigation_left", Qt::CaseInsensitive)){
    SETPROPERTY_Caption("");    

    copy_controlimage("vista_navigation_left_mousedown.png");
    copy_controlimage("vista_navigation_left_disabled.png");
    copy_controlimage("vista_navigation_left_enabled.png");
    copy_controlimage("vista_navigation_left_enter.png");

    SETPROPERTY_EnabledImage("vista_navigation_left_enabled.png");  
    SETPROPERTY_DisabledImage("vista_navigation_left_disabled.png");  
    SETPROPERTY_EnterImage("vista_navigation_left_enter.png");  
    SETPROPERTY_MouseDownImage("vista_navigation_left_mousedown.png");  

    nInsert_Width = 30;  
    nInsert_Height = 30;
    SETPROPERTY_Scale(true);
  }


  
  
#endif

  qfocusframe = 0;
  //oldImage = 0;

  //resize(60, 30);

}
#include "__property_x.h"
#include "__property_y.h"

//#include "__property_stringvalue.h"
#include "__property_stringvalue.h"
#include "__property_caption.h"
#include "__property_icon.h"
//#include "__property_checkable.h"
//#include "__property_checkableexclusive.h"
#include "__property_checked.h"
//#include "__property_autodefault.h"
//#include "__property_default.h"
//#include "__property_key.h"
#include "__property_contextmenu.h"

#include "__property_checkenterimage.h"
#include "__property_checkexitimage.h"
#include "__property_checkmousedownimage.h"
#include "__property_checkmouseupimage.h"
#include "__property_checkenabledimage.h"
#include "__property_checkdisabledimage.h"

#include "__property_enterimage.h"
#include "__property_exitimage.h"
#include "__property_mousedownimage.h"
#include "__property_mouseupimage.h"
#include "__property_enabledimage.h"
#include "__property_disabledimage.h"

#include "__property_entersound.h"
#include "__property_exitsound.h"
#include "__property_mousedownsound.h"
#include "__property_mouseupsound.h"


~_imagebutton()
{
  destructor();
}


// KBBINDINGEVENTS
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

void EVENT_OnEvent2(bool b) // needed for updating radio buttons in the same group
{
  QString s = GETPROPERTY_Group();
  if (!s.isEmpty()){
    my_form_setImageButtonBooleanValue(my_form, GETPROPERTY_Group(), this, b);
  }
}

public:

// *** bindings
// *** 
#include "_control1_binding.h"


// *** 
#include "_control1.h"



private:

QPixmap qpixmap;
QFocusFrame *qfocusframe;
/*
QString sClickImage;
QString sEnterImage;
QString sExitImage;

QPixmap clickImage;
QPixmap enterImage;
QPixmap exitImage;

const QPixmap *oldImage;
QPixmap oldImage2;
*/

};

#include "_control2.h"


#undef _IMAGEBUTTON

#undef TEST
#undef TEST2
#undef TEST3
#undef SUPERCLASS

#endif