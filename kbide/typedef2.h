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


#ifndef TYPEDEF2_H
#define TYPEDEF2_H



typedef bool t_boolean;
typedef bool t_event;

typedef signed int t_integer;
typedef signed long long t_long;
typedef double t_double;



// CONTROL
enum _controlType {
  t_notype = 0,

  // form related
  t_udpsocket,
  t_scrollbar,
  t_spinbox,
  t_slider,
  t_formsview,
  t_toolbarview,
  t_svg,
  t_commandlinkbutton,
  t_resizebox,
  t_toolbutton,
  t_line,
  t_movie,
  t_sound,
  t_web,
  t_serialport,
  t_header,
  t_footer,
  t_vsplit,
  t_hsplit,
  t_vhbox,
  t_vbox,
  t_hbox,
  t_label,
  t_commandbutton,
  t_checkbox,
  t_frame,
  t_listbox,
  t_radiobutton,
  t_tab,
  t_textbox,
  t_progressbar,
  t_image,
  t_timer,
  t_treeview,
  t_combobox,
  t_imagebutton,

  t_box,
  t_childcontrol,
  t_editor,
  t_browser,
  t_datebox,
  t_timebox,
  t_datetimebox,

  t_hidden,

  // OBJECT
  //t_file,

  // menubar related
  t_menu,
  t_submenu,
  t_menubaritem,

  // toolbar related
  t_toolbaritem,

  // table related
  t_tableitem,

  // sql related
  t_SQLInsert,
  t_SQLNext,
  t_SQLPrevious,
  t_SQLUpdate,
  t_SQLDelete,
  t_SQLFirst,
  t_SQLLast,
  t_SQLGoTo,  
  t_SQLInfo,  
  t_SQLAll,  
  t_SQLRequery,  

  // misc related
  t_move,
  t_delete,

  t_atend

};


#endif
