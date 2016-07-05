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



#include "interpreter_kbasic_binding.h"
#include "interpreter.h"


void interpreter::kbasic_binding_setKbId(void *p, memory_variable2 *v, t_integer identifier, t_integer type)
{
  if (v == getVar(local)){
    int n = identifier;
    v = getVar(me);
    identifier = 0;
    if (v == 0){
      v = getVar(local);
      identifier = n;
    }
  }

switch(type){		
//------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------


// CONTROL

case pcode___udpsocket: ((kb_udpsocket *) p)->setKbId(v, identifier); break;
case pcode___header: ((kb_header *) p)->setKbId(v, identifier); break;
case pcode___footer: ((kb_footer *) p)->setKbId(v, identifier); break;
case pcode___scrollbar: ((kb_scrollbar *) p)->setKbId(v, identifier); break;
case pcode___spinbox: ((kb_spinbox *) p)->setKbId(v, identifier); break;
case pcode___slider: ((kb_slider *) p)->setKbId(v, identifier); break;
case pcode___formsview: ((kb_formsview *) p)->setKbId(v, identifier); break;
case pcode___toolbarview: ((kb_toolbarview *) p)->setKbId(v, identifier); break;
case pcode___svg: ((kb_svg *) p)->setKbId(v, identifier); break;
case pcode___commandlinkbutton: ((kb_commandlinkbutton *) p)->setKbId(v, identifier); break;
case pcode___resizebox: ((kb_resizebox *) p)->setKbId(v, identifier); break;
case pcode___toolbutton: ((kb_toolbutton *) p)->setKbId(v, identifier); break;
case pcode___movie: ((kb_movie *) p)->setKbId(v, identifier); break;
case pcode___sound: ((kb_sound *) p)->setKbId(v, identifier); break;
case pcode___web: ((kb_web *) p)->setKbId(v, identifier); break;
case pcode___datetimebox: ((kb_datetimebox *) p)->setKbId(v, identifier); break;
case pcode___datebox: ((kb_datebox *) p)->setKbId(v, identifier); break;
case pcode___timebox: ((kb_timebox *) p)->setKbId(v, identifier); break;
case pcode___checkbox: ((kb_checkbox *) p)->setKbId(v, identifier); break;
case pcode___combobox: ((kb_combobox *) p)->setKbId(v, identifier); break;
case pcode___label: ((kb_label *) p)->setKbId(v, identifier); break;
case pcode___radiobutton: ((kb_radiobutton *) p)->setKbId(v, identifier); break;
case pcode___commandbutton: ((kb_commandbutton *) p)->setKbId(v, identifier); break;
case pcode___listbox: ((kb_listbox *) p)->setKbId(v, identifier); break;
case pcode___textbox: ((kb_textbox *) p)->setKbId(v, identifier); break;
case pcode___frame: ((kb_frame *) p)->setKbId(v, identifier); break;
case pcode___form: ((kb_form *) p)->setKbId(v, identifier); break;
case pcode___timer: ((kb_timer *) p)->setKbId(v, identifier); break;
case pcode___tab: ((kb_tab *) p)->setKbId(v, identifier); break;
case pcode___image: ((kb_image *) p)->setKbId(v, identifier); break;
case pcode___treeview: ((kb_treeview *) p)->setKbId(v, identifier); break;
case pcode___box: ((kb_box *) p)->setKbId(v, identifier); break;
case pcode___progressbar: ((kb_progressbar *) p)->setKbId(v, identifier); break;
case pcode___editor: ((kb_editor *) p)->setKbId(v, identifier); break;
case pcode___browser: ((kb_browser *) p)->setKbId(v, identifier); break;
case pcode___menubaritem: ((kb_menubaritem *) p)->setKbId(v, identifier); break;
case pcode___toolbaritem: ((kb_toolbaritem *) p)->setKbId(v, identifier); break;
case pcode___menubar: ((kb_menubar *) p)->setKbId(v, identifier); break;
case pcode___forms: ((kb_forms *) p)->setKbId(v, identifier); break;
case pcode___toolbar: ((kb_toolbar *) p)->setKbId(v, identifier); break;
case pcode___strings: ((kb_strings *) p)->setKbId(v, identifier); break;
case pcode___stringsstrings: ((kb_stringsstrings *) p)->setKbId(v, identifier); break;
case pcode___bits: ((kb_bits *) p)->setKbId(v, identifier); break;
case pcode___array: ((kb_array *) p)->setKbId(v, identifier); break;
case pcode___application: ((kb_application *) p)->setKbId(v, identifier); break;
case pcode___err: ((kb_err *) p)->setKbId(v, identifier); break;
case pcode___line: ((kb_line *) p)->setKbId(v, identifier); break;
case pcode___log: ((kb_log *) p)->setKbId(v, identifier); break;
case pcode___pixmaps: ((kb_pixmaps *) p)->setKbId(v, identifier); break;
//case pcode___pixmap: ((kb_pixmap *) p)->setKbId(v, identifier); break;
case pcode___color: ((kb_color *) p)->setKbId(v, identifier); break;
case pcode___colors: ((kb_colors *) p)->setKbId(v, identifier); break;
//case pcode___font: ((kb_font *) p)->setKbId(v, identifier); break;
case pcode___fonts: ((kb_fonts *) p)->setKbId(v, identifier); break;
case pcode___paint: ((kb_paint *) p)->setKbId(v, identifier); break;
case pcode___control: ((kb_control *) p)->setKbId(v, identifier); break;
case pcode___event: ((kb_event *) p)->setKbId(v, identifier); break;
case pcode___childcontrol: ((kb_childcontrol *) p)->setKbId(v, identifier); break;
case pcode___serialport: ((kb_serialport *) p)->setKbId(v, identifier); break;
case pcode___statusbar: ((kb_statusbar *) p)->setKbId(v, identifier); break;
case pcode___savedialog: ((kb_savedialog *) p)->setKbId(v, identifier); break;
case pcode___opendialog: ((kb_opendialog *) p)->setKbId(v, identifier); break;
case pcode___cmath: ((kb_cmath *) p)->setKbId(v, identifier); break;
case pcode___imagebutton: ((kb_imagebutton *) p)->setKbId(v, identifier); break;
//case pcode___report: ((kb_report *) p)->setKbId(v, identifier); break;


//case pcode___hidden: ((kb_hidden *) p)->setKbId(v, identifier); break;



//case pcode___bytearray: ((kb_bytearray *) p)->setKbId(v, identifier); break;
//case pcode___collection: ((kb_collection *) p)->setKbId(v, identifier); break;






default:
    internalError("setKbId not set");
    break;
}



}


