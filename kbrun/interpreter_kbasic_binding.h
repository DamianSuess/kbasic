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



#ifndef INTERPRETER_KBASIC_BINDING_H
#define INTERPRETER_KBASIC_BINDING_H

#include "interpreter.h"

//------------------------------------------------------------------------------------------------------------------------------------
// KBBINDING
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
#include "../kbasic_binding/_systemtray/kb_systemtray.h"
#include "../kbasic_binding/_movie/kb_movie.h"
#include "../kbasic_binding/_sound/kb_sound.h"
#include "../kbasic_binding/_web/kb_web.h"
#include "../kbasic_binding/_combobox/kb_combobox.h"
#include "../kbasic_binding/_checkbox/kb_checkbox.h"
#include "../kbasic_binding/_commandbutton/kb_commandbutton.h"
#include "../kbasic_binding/_form/kb_form.h"
#include "../kbasic_binding/_frame/kb_frame.h"
#include "../kbasic_binding/_label/kb_label.h"
#include "../kbasic_binding/_radiobutton/kb_radiobutton.h"
#include "../kbasic_binding/_textbox/kb_textbox.h"
#include "../kbasic_binding/_listbox/kb_listbox.h"
#include "../kbasic_binding/_tab/kb_tab.h"
#include "../kbasic_binding/_progressbar/kb_progressbar.h"
#include "../kbasic_binding/_box/kb_box.h"
#include "../kbasic_binding/_image/kb_image.h"
#include "../kbasic_binding/_timer/kb_timer.h"
#include "../kbasic_binding/_treeview/kb_treeview.h"
#include "../kbasic_binding/_menubaritem/kb_menubaritem.h"
#include "../kbasic_binding/_toolbaritem/kb_toolbaritem.h"
#include "../kbasic_binding/_menubar/kb_menubar.h"
#include "../kbasic_binding/_forms/kb_forms.h"
#include "../kbasic_binding/_toolbar/kb_toolbar.h"
#include "../kbasic_binding/_application/kb_application.h"
#include "../kbasic_binding/_mainwindow/kb_mainwindow.h"
#include "../kbasic_binding/_err/kb_err.h"
#include "../kbasic_binding/_strings/kb_strings.h"
#include "../kbasic_binding/_stringsstrings/kb_stringsstrings.h"
#include "../kbasic_binding/_bits/kb_bits.h"
#include "../kbasic_binding/_array/kb_array.h"
#include "../kbasic_binding/_log/kb_log.h"
#include "../kbasic_binding/_process/kb_process.h"
#include "../kbasic_binding/_actions/kb_actions.h"
#include "../kbasic_binding/_file/kb_file.h"
#include "../kbasic_binding/_dir/kb_dir.h"
#include "../kbasic_binding/_preferences/kb_preferences.h"
#include "../kbasic_binding/_sounds/kb_sounds.h"
#include "../kbasic_binding/_pixmaps/kb_pixmaps.h"
//#include "../kbasic_binding/_pixmap/kb_pixmap.h"
#include "../kbasic_binding/_color/kb_color.h"
#include "../kbasic_binding/_colors/kb_colors.h"
//#include "../kbasic_binding/_font/kb_font.h"
#include "../kbasic_binding/_fonts/kb_fonts.h"
#include "../kbasic_binding/_paint/kb_paint.h"
#include "../kbasic_binding/_control/kb_control.h"
#include "../kbasic_binding/_event/kb_event.h"
#include "../kbasic_binding/_childcontrol/kb_childcontrol.h"
#include "../kbasic_binding/_serialport/kb_serialport.h"
#include "../kbasic_binding/_statusbar/kb_statusbar.h"
#include "../kbasic_binding/_savedialog/kb_savedialog.h"
#include "../kbasic_binding/_colordialog/kb_colordialog.h"
#include "../kbasic_binding/_progressdialog/kb_progressdialog.h"
#include "../kbasic_binding/_inputdialog/kb_inputdialog.h"
#include "../kbasic_binding/_messagebox/kb_messagebox.h"
#include "../kbasic_binding/_fontdialog/kb_fontdialog.h"
#include "../kbasic_binding/_opendialog/kb_opendialog.h"
#include "../kbasic_binding/_cmath/kb_cmath.h"
#include "../kbasic_binding/_imagebutton/kb_imagebutton.h"

#include "../kbasic_binding/_databasedialog/kb_databasedialog.h"
#include "../kbasic_binding/_database/kb_database.h"
#include "../kbasic_binding/_table/kb_table.h"
#include "../kbasic_binding/_record/kb_record.h"
#include "../kbasic_binding/_query/kb_query.h"



//#include "../kbasic_binding/_report/kb_report.h"





//#include "../kbasic_binding/_hidden/kb_hidden.h"



//#include "../kbasic_binding/_conversion/kb_conversion.h"

//#include "../kbasic_binding/_bytearray/kb_bytearray.h"
//#include "../kbasic_binding/_collection/kb_collection.h"



//------------------------------------------------------------------------------------------------------------------------------------
#endif

