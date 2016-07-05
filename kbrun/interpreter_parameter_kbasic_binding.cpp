/*
***************************************************************************
Copyright (C) 2000-2008 KBasic Software: www.kbasic.com. All rights reserved.
Source codes are copyrighted by Bernd Noetscher 2000-2008.

You may use this source codes under the terms of the GNU Public License (Version 3) 
as published by the Free Software Foundation. 

If you are interested in using the source codes for other licenses or 
commercial development, you must buy commercial licenses from KBasic Software.
***************************************************************************
*/


#include "interpreter_parameter.h"
#include "interpreter.h"

extern interpreter *EXTERN_myInterpreter;
extern QMap<int,QString>forms;

extern memory_variable2 *SoftOpen_returnvar;
extern QMap<int, interpreter_parameter*> v;

int nCurrentFormId = 0;
//------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------

// KBBINDING



// CONTROL




_udpsocket *interpreter_parameter::to_udpsocket(){ 
  if (memory_type::compatibleType(pcode___udpsocket, pcodeType) && pointer_){
    return (_udpsocket *) pointer_; 
  }
  EXTERN_myInterpreter->runtimeError("Nullpointer exception"); return 0; 
}

_scrollbar *interpreter_parameter::to_scrollbar(){ 
  if (memory_type::compatibleType(pcode___scrollbar, pcodeType) && pointer_){
    return (_scrollbar *) pointer_; 
  }
  EXTERN_myInterpreter->runtimeError("Nullpointer exception"); return 0; 
}

_spinbox *interpreter_parameter::to_spinbox(){ 
  if (memory_type::compatibleType(pcode___spinbox, pcodeType) && pointer_){
    return (_spinbox *) pointer_; 
  }
  EXTERN_myInterpreter->runtimeError("Nullpointer exception"); return 0; 
}

_slider *interpreter_parameter::to_slider(){ 
  if (memory_type::compatibleType(pcode___slider, pcodeType) && pointer_){
    return (_slider *) pointer_; 
  }
  EXTERN_myInterpreter->runtimeError("Nullpointer exception"); return 0; 
}

_formsview *interpreter_parameter::to_formsview(){ 
  if (memory_type::compatibleType(pcode___formsview, pcodeType) && pointer_){
    return (_formsview *) pointer_; 
  }
  EXTERN_myInterpreter->runtimeError("Nullpointer exception"); return 0; 
}

_toolbarview *interpreter_parameter::to_toolbarview(){ 
  if (memory_type::compatibleType(pcode___toolbarview, pcodeType) && pointer_){
    return (_toolbarview *) pointer_; 
  }
  EXTERN_myInterpreter->runtimeError("Nullpointer exception"); return 0; 
}

_svg *interpreter_parameter::to_svg(){ 
  if (memory_type::compatibleType(pcode___svg, pcodeType) && pointer_){
    return (_svg *) pointer_; 
  }
  EXTERN_myInterpreter->runtimeError("Nullpointer exception"); return 0; 
}

_commandlinkbutton *interpreter_parameter::to_commandlinkbutton(){ 
  if (memory_type::compatibleType(pcode___commandlinkbutton, pcodeType) && pointer_){
    return (_commandlinkbutton *) pointer_; 
  }
  EXTERN_myInterpreter->runtimeError("Nullpointer exception"); return 0; 
}

_resizebox *interpreter_parameter::to_resizebox(){ 
  if (memory_type::compatibleType(pcode___resizebox, pcodeType) && pointer_){
    return (_resizebox *) pointer_; 
  }
  EXTERN_myInterpreter->runtimeError("Nullpointer exception"); return 0; 
}

_toolbutton *interpreter_parameter::to_toolbutton(){ 
  if (memory_type::compatibleType(pcode___toolbutton, pcodeType) && pointer_){
    return (_toolbutton *) pointer_; 
  }
  EXTERN_myInterpreter->runtimeError("Nullpointer exception"); return 0; 
}

_movie *interpreter_parameter::to_movie(){ 
  if (memory_type::compatibleType(pcode___movie, pcodeType) && pointer_){
    return (_movie *) pointer_; 
  }
  EXTERN_myInterpreter->runtimeError("Nullpointer exception"); return 0; 
}

_sound *interpreter_parameter::to_sound(){ 
  if (memory_type::compatibleType(pcode___sound, pcodeType) && pointer_){
    return (_sound *) pointer_; 
  }
  EXTERN_myInterpreter->runtimeError("Nullpointer exception"); return 0; 
}

_web *interpreter_parameter::to_web(){ 
  if (memory_type::compatibleType(pcode___web, pcodeType) && pointer_){
    return (_web *) pointer_; 
  }
  EXTERN_myInterpreter->runtimeError("Nullpointer exception"); return 0; 
}

_childcontrol *interpreter_parameter::to_childcontrol(){ 
  if (memory_type::compatibleType(pcode___childcontrol, pcodeType) && pointer_){
    return (_childcontrol *) pointer_; 
  }
  EXTERN_myInterpreter->runtimeError("Nullpointer exception"); return 0; 
}

_serialport *interpreter_parameter::to_serialport(){ 
  if (memory_type::compatibleType(pcode___serialport, pcodeType) && pointer_){
    return (_serialport *) pointer_; 
  }
  EXTERN_myInterpreter->runtimeError("Nullpointer exception"); return 0; 
}

_event *interpreter_parameter::to_event(){ 
  if (memory_type::compatibleType(pcode___event, pcodeType) && pointer_){
    return (_event *) pointer_; 
  }
  EXTERN_myInterpreter->runtimeError("Nullpointer exception"); return 0; 
}

_label *interpreter_parameter::to_label(){ 
  if (memory_type::compatibleType(pcode___label, pcodeType) && pointer_){
    return (_label *) pointer_; 
  }
  EXTERN_myInterpreter->runtimeError("Nullpointer exception"); return 0; 
}
_application *interpreter_parameter::to_application(){ 
  if (memory_type::compatibleType(pcode___application, pcodeType) && pointer_){
    return (_application *) pointer_; 
  }
  EXTERN_myInterpreter->runtimeError("Nullpointer exception"); return 0; 
}
_checkbox *interpreter_parameter::to_checkbox(){ 
  if (memory_type::compatibleType(pcode___checkbox, pcodeType) && pointer_){
    return (_checkbox *) pointer_; 
  }
  EXTERN_myInterpreter->runtimeError("Nullpointer exception"); return 0; 
}

_combobox *interpreter_parameter::to_combobox(){ 
  if (memory_type::compatibleType(pcode___combobox, pcodeType) && pointer_){
    return (_combobox *) pointer_; 
  }
  EXTERN_myInterpreter->runtimeError("Nullpointer exception"); EXTERN_myInterpreter->runtimeError("Nullpointer exception"); EXTERN_myInterpreter->runtimeError("Nullpointer exception"); return 0;
}

_form *interpreter_parameter::to_form(int nId){ 
  if (pcodeType != pcode__INTEGER && pointer_){

    
    if (memory_type::compatibleType(pcode___form, pcodeType)){
        return (_form *) pointer_; 

    }
    if (EXTERN_myInterpreter->myClass->getParentId(pcodeType) == pcode___form){
      return (_form *) ((memory_variable *) pointer_)->getBindingParentClassPointer();

    }
  } else {
    if (nId > 0){
      int n = toInteger();
      nCurrentFormId = n;
      if (forms.contains(n)){
        QString s = forms[n];

        kb_form *f;
        if (nId == pcode___form__METHOD_Open) f = interpreter::openForm(s);
        else if (nId == pcode___form__METHOD_OpenHidden) f = interpreter::openForm(s, 0, 0, 0, 0, 0, true);
        else if (nId == pcode___form__METHOD_Open1) f = interpreter::openForm(s, 0, v[0]->tot_integer(), v[1]->tot_integer(), 0, 0, false);
        else if (nId == pcode___form__METHOD_Open2) f = interpreter::openForm(s, 0, v[0]->tot_integer(), v[1]->tot_integer(), v[2]->tot_integer(), v[3]->tot_integer(), false);
        else if (nId == pcode___form__METHOD_OpenFullScreen) f = interpreter::openForm(s, 0, 0, 0, 0, 0, false, true);
        else if (nId == pcode___form__METHOD_OpenCentered) f = interpreter::openForm(s, 0, 0, 0, 0, 0, false, false, true);

        else if (nId == pcode___form__METHOD_OpenMaximized) f = interpreter::openForm(s, 0, 0, 0, 0, 0, false, false, false, true);
        else if (nId == pcode___form__METHOD_OpenMinimized) f = interpreter::openForm(s, 0, 0, 0, 0, 0, false, false, false, false, true);
        else if (nId == pcode___form__METHOD_OpenCenteredOnlyOnce) f = interpreter::openForm(s, 0, 0, 0, 0, 0, false, false, false, false, false, true);
        else if (nId == pcode___form__METHOD_OpenOnlyOnce) f = interpreter::openForm(s, 0, 0, 0, 0, 0, false, false, false, false, false, false, true);
        else if (nId == pcode___form__METHOD_OpenHiddenOnlyOnce) f = interpreter::openForm(s, 0, 0, 0, 0, 0, false, false, false, false, false, false, false, true);


        return (_form *) f;
      }
    }
  }
  // -1 used for IsOpen()
  if (nId != -1) EXTERN_myInterpreter->runtimeError("Nullpointer exception"); return 0; 
}

_frame *interpreter_parameter::to_frame(){ 
  if (memory_type::compatibleType(pcode___frame, pcodeType) && pointer_){
    return (_frame *) pointer_; 
  }
  EXTERN_myInterpreter->runtimeError("Nullpointer exception"); return 0; 
}
_image *interpreter_parameter::to_image(){ 
  if (memory_type::compatibleType(pcode___image, pcodeType) && pointer_){
    return (_image *) pointer_; 
  }
  EXTERN_myInterpreter->runtimeError("Nullpointer exception"); return 0; 
}
_listbox *interpreter_parameter::to_listbox(){ 
  if (memory_type::compatibleType(pcode___listbox, pcodeType) && pointer_){
    return (_listbox *) pointer_; 
  }
  EXTERN_myInterpreter->runtimeError("Nullpointer exception"); return 0; 
}

_datebox *interpreter_parameter::to_datebox(){ 
  if (memory_type::compatibleType(pcode___datebox, pcodeType) && pointer_){
    return (_datebox *) pointer_; 
  }
  EXTERN_myInterpreter->runtimeError("Nullpointer exception"); return 0; 
}

_timebox *interpreter_parameter::to_timebox(){ 
  if (memory_type::compatibleType(pcode___timebox, pcodeType) && pointer_){
    return (_timebox *) pointer_; 
  }
  EXTERN_myInterpreter->runtimeError("Nullpointer exception"); return 0; 
}

_editor *interpreter_parameter::to_editor(){ 
  if (memory_type::compatibleType(pcode___editor, pcodeType) && pointer_){
    return (_editor *) pointer_; 
  }
  EXTERN_myInterpreter->runtimeError("Nullpointer exception"); return 0; 
}

_browser *interpreter_parameter::to_browser(){ 
  if (memory_type::compatibleType(pcode___browser, pcodeType) && pointer_){
    return (_browser *) pointer_; 
  }
  EXTERN_myInterpreter->runtimeError("Nullpointer exception"); return 0; 
}

_menubaritem *interpreter_parameter::to_menubaritem(){ 
  if (memory_type::compatibleType(pcode___menubaritem, pcodeType) && pointer_){
    return (_menubaritem *) pointer_; 
  }
  EXTERN_myInterpreter->runtimeError("Nullpointer exception"); return 0; 
}

_menubar *interpreter_parameter::to_menubar(){ 
  if (memory_type::compatibleType(pcode___menubar, pcodeType) && pointer_){
    return (_menubar *) pointer_; 
  }
  EXTERN_myInterpreter->runtimeError("Nullpointer exception"); return 0; 
}
_toolbaritem *interpreter_parameter::to_toolbaritem(){ 
  if (memory_type::compatibleType(pcode___toolbaritem, pcodeType) && pointer_){
    return (_toolbaritem *) pointer_; 
  }
  EXTERN_myInterpreter->runtimeError("Nullpointer exception"); return 0; 
}

_datetimebox *interpreter_parameter::to_datetimebox(){ 
  if (memory_type::compatibleType(pcode___datetimebox, pcodeType) && pointer_){
    return (_datetimebox *) pointer_; 
  }
  EXTERN_myInterpreter->runtimeError("Nullpointer exception"); return 0; 
}

_control *interpreter_parameter::to_control(){ 
  if (memory_type::compatibleType(pcode___control, pcodeType) && pointer_){
    return (_control *) pointer_; 
  }
  EXTERN_myInterpreter->runtimeError("Nullpointer exception"); return 0; 
}

_strings *interpreter_parameter::to_strings(){ 
  if (memory_type::compatibleType(pcode___strings, pcodeType) && pointer_){
    return (_strings *) pointer_; 
  }
  EXTERN_myInterpreter->runtimeError("Nullpointer exception"); return 0; 
}

_stringsstrings *interpreter_parameter::to_stringsstrings(){ 
  if (memory_type::compatibleType(pcode___stringsstrings, pcodeType) && pointer_){
    return (_stringsstrings *) ( pointer_);  
  }
  EXTERN_myInterpreter->runtimeError("Nullpointer exception"); return 0; 
}

_bits *interpreter_parameter::to_bits(){ 
  if (memory_type::compatibleType(pcode___bits, pcodeType) && pointer_){
    return (_bits *) pointer_; 
  }
  EXTERN_myInterpreter->runtimeError("Nullpointer exception"); return 0; 
}

_array *interpreter_parameter::to_array(){ 
  if (memory_type::compatibleType(pcode___array, pcodeType) && pointer_){
    return (_array *) pointer_; 
  }
  EXTERN_myInterpreter->runtimeError("Nullpointer exception"); return 0; 
}

_log *interpreter_parameter::to_log(){ 
  if (memory_type::compatibleType(pcode___log, pcodeType) && pointer_){
    return (_log *) pointer_; 
  }
  EXTERN_myInterpreter->runtimeError("Nullpointer exception"); return 0; 
}

_pixmaps *interpreter_parameter::to_pixmaps(){ 
  if (memory_type::compatibleType(pcode___pixmaps, pcodeType) && pointer_){
    return (_pixmaps *) pointer_; 
  }
  EXTERN_myInterpreter->runtimeError("Nullpointer exception"); return 0; 
}

/*
_pixmap *interpreter_parameter::to_pixmap(){ 
  if (memory_type::compatibleType(pcode___pixmap, pcodeType) && pointer_){
    return (_pixmap *) pointer_; 
  }
  EXTERN_myInterpreter->runtimeError("Nullpointer exception"); return 0; 
}
*/
_color *interpreter_parameter::to_color(){ 
  if (memory_type::compatibleType(pcode___color, pcodeType) && pointer_){
    return (_color *) pointer_; 
  }
  EXTERN_myInterpreter->runtimeError("Nullpointer exception"); return 0; 
}

_paint *interpreter_parameter::to_paint(){ 
  if (memory_type::compatibleType(pcode___paint, pcodeType) && pointer_){
    return (_paint *) pointer_; 
  }
  EXTERN_myInterpreter->runtimeError("Nullpointer exception"); return 0; 
}

_colors *interpreter_parameter::to_colors(){ 
  if (memory_type::compatibleType(pcode___colors, pcodeType) && pointer_){
    return (_colors *) pointer_; 
  }
  EXTERN_myInterpreter->runtimeError("Nullpointer exception"); return 0; 
}
/*
_font *interpreter_parameter::to_font(){ 
  if (memory_type::compatibleType(pcode___font, pcodeType) && pointer_){
    return (_font *) pointer_; 
  }
  EXTERN_myInterpreter->runtimeError("Nullpointer exception"); return 0; 
}
*/
_fonts *interpreter_parameter::to_fonts(){ 
  if (memory_type::compatibleType(pcode___fonts, pcodeType) && pointer_){
    return (_fonts *) pointer_; 
  }
  EXTERN_myInterpreter->runtimeError("Nullpointer exception"); return 0; 
}

_forms *interpreter_parameter::to_forms(){ 
  if (memory_type::compatibleType(pcode___forms, pcodeType) && pointer_){
    return (_forms*) pointer_; 
  }
  EXTERN_myInterpreter->runtimeError("Nullpointer exception"); return 0; 
}
/*
_datetime *interpreter_parameter::to_datetime(){ 
  if (memory_type::compatibleType(pcode___datetime, pcodeType) && pointer_){
    return (_datetime *) pointer_; 
  }
  EXTERN_myInterpreter->runtimeError("Nullpointer exception"); return 0; 
}
*/
_progressbar *interpreter_parameter::to_progressbar(){ 
  if (memory_type::compatibleType(pcode___progressbar, pcodeType) && pointer_){
    return (_progressbar *) pointer_; 
  }
  EXTERN_myInterpreter->runtimeError("Nullpointer exception"); return 0; 
}
_radiobutton *interpreter_parameter::to_radiobutton(){ 
  if (memory_type::compatibleType(pcode___radiobutton, pcodeType) && pointer_){
    return (_radiobutton *) pointer_; 
  }
  EXTERN_myInterpreter->runtimeError("Nullpointer exception"); return 0; 
}

_textbox *interpreter_parameter::to_textbox(){ 
  if (memory_type::compatibleType(pcode___textbox, pcodeType) && pointer_){
    return (_textbox *) pointer_; 
  }
  int n = this->toInteger();
  n = n;

  EXTERN_myInterpreter->runtimeError("Nullpointer exception"); return 0; 
}

_commandbutton *interpreter_parameter::to_commandbutton(){ 
  if (memory_type::compatibleType(pcode___commandbutton, pcodeType) && pointer_){
    return (_commandbutton *) pointer_; 
  }
  EXTERN_myInterpreter->runtimeError("Nullpointer exception"); return 0; 
}

_line *interpreter_parameter::to_line(){ 
  if (memory_type::compatibleType(pcode___line, pcodeType) && pointer_){
    return (_line *) pointer_; 
  }
  EXTERN_myInterpreter->runtimeError("Nullpointer exception"); return 0; 
}

_box *interpreter_parameter::to_box(){ 
  if (memory_type::compatibleType(pcode___box, pcodeType) && pointer_){
    return (_box *) pointer_; 
  }
  EXTERN_myInterpreter->runtimeError("Nullpointer exception"); return 0; 
}

/*
_hidden *interpreter_parameter::to_hidden(){ 
  if (memory_type::compatibleType(pcode___hidden, pcodeType) && pointer_){
    return (_hidden *) pointer_; 
  }
  EXTERN_myInterpreter->runtimeError("Nullpointer exception"); return 0; 
}
*/

_imagebutton *interpreter_parameter::to_imagebutton(){ 
  if (memory_type::compatibleType(pcode___imagebutton, pcodeType) && pointer_){
    return (_imagebutton *) pointer_; 
  }
  EXTERN_myInterpreter->runtimeError("Nullpointer exception"); return 0; 
}


_timer *interpreter_parameter::to_timer(){ 
  if (memory_type::compatibleType(pcode___timer, pcodeType) && pointer_){
    return (_timer *) pointer_; 
  }
  EXTERN_myInterpreter->runtimeError("Nullpointer exception"); return 0; 
}

_treeview *interpreter_parameter::to_treeview(){ 
  if (memory_type::compatibleType(pcode___treeview, pcodeType) && pointer_){
    return (_treeview *) pointer_; 
  }
  EXTERN_myInterpreter->runtimeError("Nullpointer exception"); return 0; 
}

_tab *interpreter_parameter::to_tab(){ 
  if (memory_type::compatibleType(pcode___tab, pcodeType) && pointer_){
    return (_tab *) pointer_; 
  }
  EXTERN_myInterpreter->runtimeError("Nullpointer exception"); return 0; 
}
/*
_conversion *interpreter_parameter::to_conversion(){ 
  if (memory_type::compatibleType(pcode___conversion, pcodeType) && pointer_){
    return (_conversion *) pointer_; 
  }
  EXTERN_myInterpreter->runtimeError("Nullpointer exception"); return 0; 
}*/




_err *interpreter_parameter::to_err(){ 
  if (memory_type::compatibleType(pcode___err, pcodeType) && pointer_){
    return (_err *) pointer_; 
  }
  EXTERN_myInterpreter->runtimeError("Nullpointer exception"); return 0; 
}
/*
_bytearray *interpreter_parameter::to_bytearray(){ 
  if (memory_type::compatibleType(pcode___bytearray, pcodeType) && pointer_){
    return (_bytearray *) pointer_; 
  }
  EXTERN_myInterpreter->runtimeError("Nullpointer exception"); return 0; 
}*/
/*
_collection *interpreter_parameter::to_collection(){ 
  if (memory_type::compatibleType(pcode___collection, pcodeType) && pointer_){
    return (_collection *) pointer_; 
  }
  EXTERN_myInterpreter->runtimeError("Nullpointer exception"); return 0; 
}*/


_property *interpreter_parameter::to_property(){ 
  if (memory_type::compatibleType(pcode___control, pcodeType) && pointer_){

    QObject *o = (QObject *) ((interpreter_parameter *) pointer_)->pointer_;

  }
  EXTERN_myInterpreter->runtimeError("Nullpointer exception"); return 0; 
}

//------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------


