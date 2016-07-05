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

#ifndef INTERPRETER_PARAMETER_KBASIC_BINDING_H
#define INTERPRETER_PARAMETER_KBASIC_BINDING_H


// wurde wegen abhängigkeiten ausgelagert
static int kbasic_binding_sizeof(t_integer type);


//------------------------------------------------------------------------------------------------------------------------------------
// KBBINDING
// CONTROL
//interpreter_parameter (_systemtray *c){ pcodeType = pcode___systemtray; pointer_ = (void *) c;  }
interpreter_parameter (_udpsocket *c){ pcodeType = pcode___udpsocket; INIT; pointer_ = (void *) c;  }
interpreter_parameter (_scrollbar *c){ pcodeType = pcode___scrollbar; INIT; pointer_ = (void *) c;  }
interpreter_parameter (_spinbox *c){ pcodeType = pcode___spinbox; INIT; pointer_ = (void *) c; }
interpreter_parameter (_slider *c){ pcodeType = pcode___slider; INIT; pointer_ = (void *) c;  }
interpreter_parameter (_formsview *c){ pcodeType = INIT; pointer_ = (void *) c; }
interpreter_parameter (_toolbarview *c){ pcodeType = pcode___toolbarview; INIT; pointer_ = (void *) c;  }
interpreter_parameter (_svg *c){ pcodeType = pcode___svg; INIT; pointer_ = (void *) c;  }
interpreter_parameter (_commandlinkbutton *c){ pcodeType = pcode___commandlinkbutton; INIT; pointer_ = (void *) c;  }
interpreter_parameter (_resizebox *c){ pcodeType = pcode___resizebox; INIT; pointer_ = (void *) c;  }
interpreter_parameter (_toolbutton *c){ pcodeType = pcode___toolbutton; INIT; pointer_ = (void *) c;  }
interpreter_parameter (_movie *c){ pcodeType = pcode___movie; INIT; pointer_ = (void *) c;  }
interpreter_parameter (_sound *c){ pcodeType = pcode___sound; INIT; pointer_ = (void *) c;  }
interpreter_parameter (_web *c){ pcodeType = pcode___web; INIT; pointer_ = (void *) c;  }
interpreter_parameter (_checkbox *c){ pcodeType = pcode___checkbox; INIT; pointer_ = (void *) c;  }
interpreter_parameter (_form *c){ pcodeType = pcode___form; INIT; pointer_ = (void *) c;  }
interpreter_parameter (_label *c){ pcodeType = pcode___label; INIT; pointer_ = (void *) c;  }
interpreter_parameter (_commandbutton *c){ pcodeType = pcode___commandbutton; INIT; pointer_ = (void *) c;  }
interpreter_parameter (_combobox *c){ pcodeType = pcode___combobox; INIT; pointer_ = (void *) c;  }
interpreter_parameter (_listbox *c){ pcodeType = pcode___listbox; INIT; pointer_ = (void *) c;  }
interpreter_parameter (_datebox *c){ pcodeType = pcode___datebox; INIT; pointer_ = (void *) c;  }
interpreter_parameter (_timebox *c){ pcodeType = pcode___timebox; INIT; pointer_ = (void *) c;  }
interpreter_parameter (_datetimebox *c){ pcodeType = pcode___datebox; INIT; pointer_ = (void *) c;  }
interpreter_parameter (_timer *c){ pcodeType = pcode___timer; INIT; pointer_ = (void *) c;  }
interpreter_parameter (_tab *c){ pcodeType = pcode___tab; INIT; pointer_ = (void *) c;  }
interpreter_parameter (_image *c){ pcodeType = pcode___image; INIT; pointer_ = (void *) c;  }
interpreter_parameter (_box *c){ pcodeType = pcode___box; INIT; pointer_ = (void *) c;  }
interpreter_parameter (_progressbar *c){ pcodeType = pcode___progressbar; INIT; pointer_ = (void *) c;  }
interpreter_parameter (_radiobutton *c){ pcodeType = pcode___radiobutton; INIT; pointer_ = (void *) c;  }
interpreter_parameter (_textbox *c){ pcodeType = pcode___textbox; INIT; pointer_ = (void *) c;  }
interpreter_parameter (_frame *c){ pcodeType = pcode___frame; INIT; pointer_ = (void *) c;  }
interpreter_parameter (_treeview *c){ pcodeType = pcode___treeview; INIT; pointer_ = (void *) c;  }
interpreter_parameter (_editor *c){ pcodeType = pcode___editor; INIT; pointer_ = (void *) c;  }
interpreter_parameter (_browser *c){ pcodeType = pcode___browser; INIT; pointer_ = (void *) c;  }
interpreter_parameter (_menubaritem *c){ pcodeType = pcode___menubaritem; INIT; pointer_ = (void *) c;  }
interpreter_parameter (_toolbaritem *c){ pcodeType = pcode___toolbaritem; INIT; pointer_ = (void *) c;  }
interpreter_parameter (_menubar *c){ pcodeType = pcode___menubar; INIT; pointer_ = (void *) c;  }
interpreter_parameter (_forms *c){ pcodeType = pcode___forms; INIT; pointer_ = (void *) c;  }
interpreter_parameter (_toolbar *c){ pcodeType = pcode___toolbar; INIT; pointer_ = (void *) c;  }
interpreter_parameter (_strings *c){ pcodeType = pcode___strings; INIT; pointer_ = (void *) c;  }
interpreter_parameter (_stringsstrings *c){ pcodeType = pcode___stringsstrings; INIT; pointer_ = (void *) c;  }
interpreter_parameter (_bits *c){ pcodeType = pcode___bits; INIT; pointer_ = (void *) c;  }
interpreter_parameter (_array *c){ pcodeType = pcode___array; INIT; pointer_ = (void *) c;  }
//interpreter_parameter (_application *c){ pcodeType = pcode___application; INIT; pointer_ = (void *) c;  }
interpreter_parameter (_err *c){ pcodeType = pcode___err; INIT; pointer_ = (void *) c;  }
interpreter_parameter (_log *c){ pcodeType = pcode___log; INIT; pointer_ = (void *) c;  }
interpreter_parameter (_pixmaps *c){ pcodeType = pcode___pixmaps; INIT; pointer_ = (void *) c;  }
//interpreter_parameter (_pixmap *c);//{ pcodeType = pcode___pixmap; INIT; pointer_ = (void *) c;  }
interpreter_parameter (_color *c){ pcodeType = pcode___color; INIT; pointer_ = (void *) c;  }
interpreter_parameter (_colors *c){ pcodeType = pcode___colors; INIT; pointer_ = (void *) c;  }
//interpreter_parameter (_font *c){ pcodeType = pcode___font; INIT; pointer_ = (void *) c;  }
interpreter_parameter (_fonts *c){ pcodeType = pcode___fonts; INIT; pointer_ = (void *) c;  }
interpreter_parameter (_paint *c){ pcodeType = pcode___paint; INIT; pointer_ = (void *) c;  }
interpreter_parameter (_control *c){ pcodeType = pcode___control; INIT; pointer_ = (void *) c;  }
interpreter_parameter (_event *c){ pcodeType = pcode___event; INIT; pointer_ = (void *) c;  }
interpreter_parameter (_childcontrol *c){ pcodeType = pcode___childcontrol; INIT; pointer_ = (void *) c;  }
interpreter_parameter (_serialport *c){ pcodeType = pcode___serialport; INIT; pointer_ = (void *) c;  }
interpreter_parameter (_statusbar *c){ pcodeType = pcode___statusbar; INIT; pointer_ = (void *) c;  }
interpreter_parameter (_savedialog *c){ pcodeType = pcode___savedialog; INIT; pointer_ = (void *) c;  }
interpreter_parameter (_opendialog *c){ pcodeType = pcode___opendialog; INIT; pointer_ = (void *) c;  }
interpreter_parameter (_cmath *c){ pcodeType = pcode___cmath; INIT; pointer_ = (void *) c;  }
interpreter_parameter (_imagebutton *c){ pcodeType = pcode___imagebutton; INIT; pointer_ = (void *) c;  }
//interpreter_parameter (_report *c){ pcodeType = pcode___report; INIT; pointer_ = (void *) c;  }


//interpreter_parameter (_hidden *c){ pcodeType = pcode___hidden; INIT; pointer_ = (void *) c;  }





//interpreter_parameter (_datetime *c){ pcodeType = pcode___datetime; INIT; pointer_ = (void *) c;  }

//interpreter_parameter (_conversion *c){ pcodeType = pcode___conversion; INIT; pointer_ = (void *) c;  }
//interpreter_parameter (_bytearray *c){ pcodeType = pcode___bytearray; INIT; pointer_ = (void *) c;  }

//interpreter_parameter (_collection *c){ pcodeType = pcode___collection; INIT; pointer_ = (void *) c;  }





//------------------------------------------------------------------------------------------------------------------------------------



//------------------------------------------------------------------------------------------------------------------------------------
// KBBINDING
// CONTROL

//_report *to_report();
//_systemtray *to_systemtray();


_udpsocket *to_udpsocket();
_scrollbar *to_scrollbar();
_spinbox *to_spinbox();
_slider *to_slider();
_formsview *to_formsview();
_toolbarview *to_toolbarview();
_svg *to_svg();
_commandlinkbutton *to_commandlinkbutton();
_resizebox *to_resizebox();
_toolbutton *to_toolbutton();
_movie *to_movie();
_sound *to_sound();
_web *to_web();

_childcontrol *to_childcontrol();
_event *to_event();
_checkbox *to_checkbox();
_form *to_form(int nId = 0);
//_control *to_control();
_label *to_label();
_commandbutton *to_commandbutton();
_line *to_line();
_combobox *to_combobox();
_listbox *to_listbox();
_datebox *to_datebox();
_timebox *to_timebox();
_datetimebox *to_datetimebox();
_timer *to_timer();
_tab *to_tab();
_image *to_image();
_treeview *to_treeview();
_box *to_box();
_frame *to_frame();
_progressbar *to_progressbar();
_radiobutton *to_radiobutton();
_textbox *to_textbox();
_editor *to_editor();
_browser *to_browser();
_menubaritem *to_menubaritem();
_toolbaritem *to_toolbaritem();
_menubar *to_menubar();
_forms *to_forms();
_toolbar *to_toolbar();
_strings *to_strings();
_stringsstrings *to_stringsstrings();
_bits *to_bits();
_array *to_array();
_application *to_application();
_err *to_err();
_log *to_log();
_pixmaps *to_pixmaps();
//_pixmap *to_pixmap();
_color *to_color();
_colors *to_colors();
//_font *to_font();
_fonts *to_fonts();
_paint *to_paint();
_control *to_control();
_serialport *to_serialport();
_statusbar *to_statusbar();
_savedialog *to_savedialog();
_opendialog *to_opendialog();
_cmath *to_cmath();




//_datetime *to_datetime();





//_hidden *to_hidden();

_imagebutton *to_imagebutton();



//_conversion *to_conversion();
_property *to_property();
//_collection *to_collection();




#endif