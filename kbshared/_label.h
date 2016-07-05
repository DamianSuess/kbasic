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



#ifndef _LABEL_H
#define _LABEL_H

#include <QLabel>
#include <QMovie>

#include "typedef.h"

#include <QSvgWidget>
#include <QSvgRenderer>


#ifdef RUN
extern t_pointer loadProjectFile(QString sFile, t_integer *nSize);
#endif

#include "_property.h"
#include "_control0.h"

#define TEST _label    
#define TEST2 _labels   
#define TEST3 "Label"
#define SUPERCLASS QLabel   

#define _LABEL true

class _form;

#ifdef IDE
extern QString sInsertTypeOption;
extern void copy_controlimage(QString s);
extern int nInsert_Width;  
extern int nInsert_Height;
#endif

class _label : public QLabel, public _property
{
  Q_OBJECT
public:


_label(_form *f = 0, QWidget *parent = 0) : QLabel (parent ? parent : (QWidget *) f)
{
  constructor(f, parent);

  bool bForm = my_form_isForm(my_form);

  // properties  

  if (bForm){
    addProperty("Shape", pt_boolean);

    addProperty("OpenLinks", pt_boolean);
    addProperty("Icon", pt_qstring);
    addProperty("InputControl", pt_qstring);
    addProperty("Alignment", pt_qstring);
    addProperty("Feature", pt_qstring);
    addProperty("WordWrap", pt_boolean);
  }

#ifdef RUN
  addProperty("StringValue", pt_qstring); addProperty("OldStringValue", pt_qstring);
#endif
  addProperty("Caption", pt_qstring);
  //addProperty("Space", pt_integer);

  // events

  // default values
  SETPROPERTY_Caption("Label");
  SETPROPERTY_ControlType("Label");
  SETPROPERTY_Visible(true);
  SETPROPERTY_WordWrap(true);
  if (bForm) SETPROPERTY_Enabled(true);

#ifdef IDE
  if (sInsertTypeOption.contains("Link", Qt::CaseInsensitive)){
    SETPROPERTY_Feature("LinksAccessibleByMouse");
    SETPROPERTY_Caption("www.kbasic.com");    
    SETPROPERTY_OpenLinks(true);
  } else if (sInsertTypeOption.contains("vista_bar", Qt::CaseInsensitive)){
    SETPROPERTY_Caption("");    
    SETPROPERTY_Scale(true);
    SETPROPERTY_Icon("vista_bar.png");  
    copy_controlimage("vista_bar.png");

    nInsert_Width = 150;  
    nInsert_Height = 30;

  } else if (sInsertTypeOption.contains("vista_box_black", Qt::CaseInsensitive)){    
    SETPROPERTY_Caption("");
    SETPROPERTY_Scale(true);

    copy_controlimage("vista_box_black.png");
    SETPROPERTY_Background("vista_box_black.png");  

    nInsert_Width = 200;  
    nInsert_Height = 200;

  } else if (sInsertTypeOption.contains("vista_box_white", Qt::CaseInsensitive)){    
    SETPROPERTY_Caption("");
    SETPROPERTY_Scale(true);

    copy_controlimage("vista_box_white.png");
    SETPROPERTY_Background("vista_box_white.png");  

    nInsert_Width = 200;  
    nInsert_Height = 200;
    
  } else if (sInsertTypeOption.contains("vista_window_light", Qt::CaseInsensitive)){    
    SETPROPERTY_Caption("");
    SETPROPERTY_Scale(true);

    copy_controlimage("vista_window_light.png");
    SETPROPERTY_Background("vista_window_light.png");  

    nInsert_Width = 200;  
    nInsert_Height = 200;
    
  } else if (sInsertTypeOption.contains("vista_navigation_bar", Qt::CaseInsensitive)){    
    SETPROPERTY_Caption("");
    SETPROPERTY_Scale(true);

    copy_controlimage("vista_navigation_bar.png");
    SETPROPERTY_Background("vista_navigation_bar.png");  

    nInsert_Width = 200;  
    nInsert_Height = 200;
    
  } else if (sInsertTypeOption.contains("vista_icon_search", Qt::CaseInsensitive)){    
    SETPROPERTY_Caption("");
    SETPROPERTY_Scale(true);

    copy_controlimage("vista_icon_search.png");
    SETPROPERTY_Background("vista_icon_search.png");  

    nInsert_Width = 20;  
    nInsert_Height = 20;
    
  } else if (sInsertTypeOption.contains("vista_imagebox_whiteblack", Qt::CaseInsensitive)){    
    SETPROPERTY_Caption("");
    SETPROPERTY_Scale(true);

    copy_controlimage("vista_imagebox_whiteblack.png");
    SETPROPERTY_Background("vista_imagebox_whiteblack.png");  

    nInsert_Width = 20;  
    nInsert_Height = 20;
    
  } else if (sInsertTypeOption.contains("vista_separator_black", Qt::CaseInsensitive)){    
    SETPROPERTY_Caption("");
    SETPROPERTY_Scale(true);

    copy_controlimage("vista_separator_black.png");
    SETPROPERTY_Background("vista_separator_black.png");  

    nInsert_Width = 100;  
    nInsert_Height = 2;
        
  } else if (sInsertTypeOption.contains("vista_separator_white", Qt::CaseInsensitive)){    
    SETPROPERTY_Caption("");
    SETPROPERTY_Scale(true);

    copy_controlimage("vista_separator_white.png");
    SETPROPERTY_Background("vista_separator_white.png");  

    nInsert_Width = 100;  
    nInsert_Height = 2;
        
  } else if (sInsertTypeOption.contains("vista_textbox_whiteblack", Qt::CaseInsensitive)){    
    SETPROPERTY_Caption("");
    SETPROPERTY_Scale(true);

    copy_controlimage("vista_textbox_whiteblack.png");
    SETPROPERTY_Background("vista_textbox_whiteblack.png");  

    nInsert_Width = 100;  
    nInsert_Height = 24;
  } else {    
    SETPROPERTY_OpenLinks(false);
              
  }
#endif

}


~_label()
{
  destructor();
}



#include "__property_x.h"
#include "__property_y.h"
#include "__property_stringvalue.h"
#include "__property_caption.h"
#include "__property_alignment.h"
#include "__property_feature.h"
#include "__property_shape.h"
#include "__property_openlinks.h"
#include "__property_icon.h"
#include "__property_inputcontrol.h"
//#include "__property_key.h"
//#include "__property_space.h"
#include "__property_wordwrap.h"


// events


// *** bindings
// *** 
#include "_control1_binding.h"


// *** 
#include "_control1.h"

private:
  QString sEnabledText;

};

#include "_control2.h"

#undef _LABEL

#undef TEST
#undef TEST2
#undef TEST3
#undef SUPERCLASS


#endif
