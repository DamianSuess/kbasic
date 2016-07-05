/*
***************************************************************************
Copyright (C) 2000-2008 KBasic Software (Bernd Noetscher, Boseweg 9, 60529 Frankfurt / Germany).  All rights reserved.

pcode_kbasic_binding.h
---------------------------------------------------------------------------
19.02.2004 - new header for this file (BN)
***************************************************************************
*/




#ifndef PCODE_KBASIC_BINDING_H
#define PCODE_KBASIC_BINDING_H


#include "../kbshared/typedef.h"

#ifdef RUN

#include <QtGui>

// KBBINDING
// CONTROL
#include "../kbshared/_udpsocket.h"
#include "../kbshared/_scrollbar.h"
#include "../kbshared/_spinbox.h"
#include "../kbshared/_slider.h"
#include "../kbshared/_formsview.h"
#include "../kbshared/_toolbarview.h"
#include "../kbshared/_svg.h"
#include "../kbshared/_commandlinkbutton.h"
#include "../kbshared/_resizebox.h"
#include "../kbshared/_toolbutton.h"
#include "../kbshared/_line.h"
#include "../kbshared/_movie.h"
#include "../kbshared/_sound.h"
#include "../kbshared/_web.h"
#include "../kbshared/_checkbox.h"
#include "../kbshared/_commandbutton.h"
#include "../kbshared/_label.h"
#include "../kbshared/_textbox.h"
#include "../kbshared/_radiobutton.h"
#include "../kbshared/_frame.h"
#include "../kbshared/_combobox.h"
#include "../kbshared/_listbox.h"
#include "../kbshared/_datebox.h"
#include "../kbshared/_timebox.h"
#include "../kbshared/_datetimebox.h"
#include "../kbshared/_timer.h"
#include "../kbshared/_tab.h"
#include "../kbshared/_treeview.h"
#include "../kbshared/_box.h"
#include "../kbshared/_progressbar.h"
#include "../kbshared/_editor.h"
#include "../kbshared/_browser.h"
#include "../kbshared/_menubaritem.h"
#include "../kbshared/_toolbaritem.h"
#include "../kbshared/_menubar.h"
#include "../kbshared/_forms.h"
#include "../kbshared/_toolbar.h"
#include "../kbshared/_strings.h"
#include "../kbshared/_stringsstrings.h"
#include "../kbshared/_bits.h"
#include "../kbshared/_array.h"
#include "../kbshared/_application.h"
#include "../kbshared/_mainwindow.h"
#include "../kbshared/_systemtray.h"
#include "../kbshared/_err.h"
#include "../kbshared/_image.h"
#include "../kbshared/_tab.h"
#include "../kbshared/_log.h"
#include "../kbshared/_actions.h"
#include "../kbshared/_process.h"
#include "../kbshared/_file.h"
#include "../kbshared/_dir.h"
#include "../kbshared/_preferences.h"
#include "../kbshared/_sounds.h"
#include "../kbshared/_pixmaps.h"
//#include "../kbshared/_pixmap.h"
#include "../kbshared/_color.h"
#include "../kbshared/_colors.h"
//#include "../kbshared/_font.h"
#include "../kbshared/_fonts.h"
#include "../kbshared/_paint.h"
#include "../kbshared/_control.h"
#include "../kbshared/_event.h"
#include "../kbshared/_childcontrol.h"
#include "../kbshared/_serialport.h"
#include "../kbshared/_statusbar.h"
#include "../kbshared/_savedialog.h"
#include "../kbshared/_fontdialog.h"
#include "../kbshared/_colordialog.h"
#include "../kbshared/_progressdialog.h"
#include "../kbshared/_inputdialog.h"
#include "../kbshared/_messagebox.h"
#include "../kbshared/_opendialog.h"
#include "../kbshared/_cmath.h"
#include "../kbshared/_imagebutton.h"
#include "../kbshared/_database.h"
#include "../kbshared/_table2.h"
#include "../kbshared/_query.h"
#include "../kbshared/_record.h"
#include "../kbshared/_databasedialog.h"




//#include "../kbshared/_hidden.h"



//#include "../kbshared/_conversion.h"
//#include "../kbshared/_desktop.h"

//#include "../kbshared/_bytearray.h"
//#include "../kbshared/_collection.h"

#include "../kbshared/_header.h"
#include "../kbshared/_footer.h"


#endif






static const int pcode__kbasic_binding_class		= 10000;
// KBBINDING
static const int pcode___checkbox = pcode__kbasic_binding_class + 1;
static const int pcode___form = pcode___checkbox + 1;
static const int pcode___control = pcode___form + 1;
static const int pcode___commandbutton = pcode___control + 1;
static const int pcode___label = pcode___commandbutton + 1;
static const int pcode___textbox = pcode___label + 1;
static const int pcode___radiobutton = pcode___textbox + 1;
static const int pcode___frame = pcode___radiobutton + 1;
static const int pcode___combobox = pcode___frame + 1;
static const int pcode___listbox = pcode___combobox + 1;
static const int pcode___datebox = pcode___listbox + 1;
static const int pcode___timebox = pcode___datebox + 1;
static const int pcode___datetimebox = pcode___timebox + 1;
static const int pcode___timer = pcode___datetimebox + 1;
static const int pcode___tab = pcode___timer + 1;
static const int pcode___image = pcode___tab + 1;
static const int pcode___treeview = pcode___image + 1;
static const int pcode___box = pcode___treeview + 1;
static const int pcode___progressbar = pcode___box + 1;
static const int pcode___editor = pcode___progressbar + 1;
static const int pcode___browser = pcode___editor + 1;
static const int pcode___menubaritem = pcode___browser + 1;
static const int pcode___toolbaritem = pcode___menubaritem + 1;
static const int pcode___menubar = pcode___toolbaritem + 1;
static const int pcode___forms = pcode___menubar + 1;
static const int pcode___toolbar = pcode___forms + 1;
static const int pcode___strings = pcode___toolbar + 1;
static const int pcode___application = pcode___strings + 1;
static const int pcode___err = pcode___application + 1;
static const int pcode___log = pcode___err + 1;
static const int pcode___sounds = pcode___log + 1;
static const int pcode___pixmaps = pcode___sounds + 1;
static const int pcode___pixmap = pcode___pixmaps + 1;
static const int pcode___color = pcode___pixmap + 1;
static const int pcode___colors = pcode___color + 1;
static const int pcode___font = pcode___colors + 1;
static const int pcode___fonts = pcode___font + 1;
static const int pcode___paint = pcode___fonts + 1;
static const int pcode___event = pcode___paint + 1;
static const int pcode___childcontrol = pcode___event + 1;
//static const int pcode___report = pcode___childcontrol + 1;


static const int pcode___header = pcode___childcontrol + 1;
static const int pcode___footer = pcode___header + 1;
static const int pcode___serialport = pcode___footer + 1;
static const int pcode___statusbar = pcode___serialport + 1;
static const int pcode___savedialog = pcode___statusbar + 1;
static const int pcode___opendialog = pcode___savedialog + 1;
static const int pcode___cmath = pcode___opendialog + 1;
static const int pcode___movie = pcode___cmath + 1;
static const int pcode___sound = pcode___movie + 1;
static const int pcode___web = pcode___sound + 1;
static const int pcode___line = pcode___web + 1;
static const int pcode___systemtray = pcode___line + 1;
static const int pcode___mainwindow = pcode___systemtray + 1;
static const int pcode___actions = pcode___mainwindow + 1;
static const int pcode___preferences = pcode___actions + 1;
static const int pcode___dir = pcode___preferences + 1;
static const int pcode___file = pcode___dir + 1;
static const int pcode___process = pcode___file + 1;
static const int pcode___colordialog = pcode___process + 1;
static const int pcode___fontdialog = pcode___colordialog + 1;
static const int pcode___progressdialog = pcode___fontdialog + 1;
static const int pcode___inputdialog = pcode___progressdialog + 1;
static const int pcode___messagebox = pcode___inputdialog + 1;
static const int pcode___imagebutton = pcode___messagebox + 1;
static const int pcode___stringsstrings = pcode___imagebutton + 1;
static const int pcode___array = pcode___stringsstrings + 1;
static const int pcode___bits = pcode___array + 1;
static const int pcode___database = pcode___bits + 1;
static const int pcode___table = pcode___database + 1;
static const int pcode___record = pcode___table + 1;
static const int pcode___query = pcode___record + 1;
static const int pcode___databasedialog = pcode___query + 1;
static const int pcode___toolbutton = pcode___databasedialog + 1;
static const int pcode___resizebox = pcode___toolbutton + 1;
static const int pcode___commandlinkbutton = pcode___resizebox + 1;
static const int pcode___svg = pcode___commandlinkbutton + 1;
static const int pcode___toolbarview = pcode___svg + 1;
static const int pcode___formsview = pcode___toolbarview + 1;
static const int pcode___slider = pcode___formsview + 1;
static const int pcode___spinbox = pcode___slider + 1;
static const int pcode___scrollbar = pcode___spinbox + 1;
static const int pcode___udpsocket = pcode___scrollbar + 1;

// CONTROL

//static const int pcode___collection = pcode___serialport + 1;

//static const int pcode___optionbutton = pcode___listbox + 1;





//static const int pcode___line = pcode___box + 1;
//static const int pcode___circle = pcode___line + 1;
//static const int pcode___rectangle = pcode___circle + 1;
//static const int pcode___hidden = pcode___rectangle + 1;
//static const int pcode___qwidget = pcode___hidden + 1;
//static const int pcode___imagebutton = pcode___qwidget + 1;
//static const int pcode___canvas = pcode___imagebutton + 1;
//static const int pcode___listview = pcode___box + 1;

//static const int pcode___subform = pcode___listview + 1;

//static const int pcode___kbasic = pcode___treeview + 1;
//static const int pcode___conversion = pcode___kbasic + 1;
//static const int pcode___desktop = pcode___conversion + 1;

//static const int pcode___bytearray = pcode___desktop + 1;


//static const int pcode___activex = pcode___tab + 1;




//static const int pcode___kb = pcode___collection + 1;



//static const int pcode___datetime = pcode___footer + 1;


static const int SPACE = 1000; // the space between differents ids



static const int pcode__kbasic_binding_method		= pcode__kbasic_binding_class + 1000;

// KBBINDING
// CONTROL
//------------------------------------------------------------------------------------------------------------------------------------
#include "../kbasic_binding/_udpsocket/pcode_kbasic_binding_method_id.h"
#include "../kbasic_binding/_scrollbar/pcode_kbasic_binding_method_id.h"
#include "../kbasic_binding/_spinbox/pcode_kbasic_binding_method_id.h"
#include "../kbasic_binding/_slider/pcode_kbasic_binding_method_id.h"
#include "../kbasic_binding/_formsview/pcode_kbasic_binding_method_id.h"
#include "../kbasic_binding/_toolbarview/pcode_kbasic_binding_method_id.h"
#include "../kbasic_binding/_svg/pcode_kbasic_binding_method_id.h"
#include "../kbasic_binding/_commandlinkbutton/pcode_kbasic_binding_method_id.h"
#include "../kbasic_binding/_resizebox/pcode_kbasic_binding_method_id.h"
#include "../kbasic_binding/_line/pcode_kbasic_binding_method_id.h"
#include "../kbasic_binding/_checkbox/pcode_kbasic_binding_method_id.h"
#include "../kbasic_binding/_form/pcode_kbasic_binding_method_id.h"
//#include "../kbasic_binding/_control/pcode_kbasic_binding_method_id.h"
#include "../kbasic_binding/_commandbutton/pcode_kbasic_binding_method_id.h"
#include "../kbasic_binding/_label/pcode_kbasic_binding_method_id.h"
#include "../kbasic_binding/_textbox/pcode_kbasic_binding_method_id.h"
#include "../kbasic_binding/_radiobutton/pcode_kbasic_binding_method_id.h"
#include "../kbasic_binding/_frame/pcode_kbasic_binding_method_id.h"
#include "../kbasic_binding/_combobox/pcode_kbasic_binding_method_id.h"
#include "../kbasic_binding/_listbox/pcode_kbasic_binding_method_id.h"
#include "../kbasic_binding/_datebox/pcode_kbasic_binding_method_id.h"
#include "../kbasic_binding/_timebox/pcode_kbasic_binding_method_id.h"
#include "../kbasic_binding/_datetimebox/pcode_kbasic_binding_method_id.h"
#include "../kbasic_binding/_timer/pcode_kbasic_binding_method_id.h"
#include "../kbasic_binding/_tab/pcode_kbasic_binding_method_id.h"
#include "../kbasic_binding/_image/pcode_kbasic_binding_method_id.h"
#include "../kbasic_binding/_treeview/pcode_kbasic_binding_method_id.h"
#include "../kbasic_binding/_box/pcode_kbasic_binding_method_id.h"
#include "../kbasic_binding/_progressbar/pcode_kbasic_binding_method_id.h"
#include "../kbasic_binding/_editor/pcode_kbasic_binding_method_id.h"
#include "../kbasic_binding/_browser/pcode_kbasic_binding_method_id.h"
#include "../kbasic_binding/_menubaritem/pcode_kbasic_binding_method_id.h"
#include "../kbasic_binding/_toolbaritem/pcode_kbasic_binding_method_id.h"
#include "../kbasic_binding/_menubar/pcode_kbasic_binding_method_id.h"
#include "../kbasic_binding/_forms/pcode_kbasic_binding_method_id.h"
#include "../kbasic_binding/_toolbar/pcode_kbasic_binding_method_id.h"
#include "../kbasic_binding/_strings/pcode_kbasic_binding_method_id.h"
#include "../kbasic_binding/_stringsstrings/pcode_kbasic_binding_method_id.h"
#include "../kbasic_binding/_bits/pcode_kbasic_binding_method_id.h"
#include "../kbasic_binding/_array/pcode_kbasic_binding_method_id.h"
#include "../kbasic_binding/_application/pcode_kbasic_binding_method_id.h"
#include "../kbasic_binding/_mainwindow/pcode_kbasic_binding_method_id.h"
#include "../kbasic_binding/_systemtray/pcode_kbasic_binding_method_id.h"
#include "../kbasic_binding/_err/pcode_kbasic_binding_method_id.h"
#include "../kbasic_binding/_log/pcode_kbasic_binding_method_id.h"
#include "../kbasic_binding/_actions/pcode_kbasic_binding_method_id.h"
#include "../kbasic_binding/_process/pcode_kbasic_binding_method_id.h"
#include "../kbasic_binding/_file/pcode_kbasic_binding_method_id.h"
#include "../kbasic_binding/_dir/pcode_kbasic_binding_method_id.h"
#include "../kbasic_binding/_preferences/pcode_kbasic_binding_method_id.h"
#include "../kbasic_binding/_sounds/pcode_kbasic_binding_method_id.h"
#include "../kbasic_binding/_pixmaps/pcode_kbasic_binding_method_id.h"
//#include "../kbasic_binding/_pixmap/pcode_kbasic_binding_method_id.h"
#include "../kbasic_binding/_color/pcode_kbasic_binding_method_id.h"
#include "../kbasic_binding/_colors/pcode_kbasic_binding_method_id.h"
//#include "../kbasic_binding/_font/pcode_kbasic_binding_method_id.h"
#include "../kbasic_binding/_fonts/pcode_kbasic_binding_method_id.h"
#include "../kbasic_binding/_paint/pcode_kbasic_binding_method_id.h"
#include "../kbasic_binding/_control/pcode_kbasic_binding_method_id.h"
#include "../kbasic_binding/_event/pcode_kbasic_binding_method_id.h"
#include "../kbasic_binding/_childcontrol/pcode_kbasic_binding_method_id.h"
//#include "../kbasic_binding/_report/pcode_kbasic_binding_method_id.h"
#include "../kbasic_binding/_header/pcode_kbasic_binding_method_id.h" 
#include "../kbasic_binding/_footer/pcode_kbasic_binding_method_id.h"
#include "../kbasic_binding/_serialport/pcode_kbasic_binding_method_id.h"
#include "../kbasic_binding/_statusbar/pcode_kbasic_binding_method_id.h"
#include "../kbasic_binding/_savedialog/pcode_kbasic_binding_method_id.h"
#include "../kbasic_binding/_colordialog/pcode_kbasic_binding_method_id.h"
#include "../kbasic_binding/_progressdialog/pcode_kbasic_binding_method_id.h"
#include "../kbasic_binding/_inputdialog/pcode_kbasic_binding_method_id.h"
#include "../kbasic_binding/_messagebox/pcode_kbasic_binding_method_id.h"
#include "../kbasic_binding/_fontdialog/pcode_kbasic_binding_method_id.h"
#include "../kbasic_binding/_opendialog/pcode_kbasic_binding_method_id.h"
#include "../kbasic_binding/_cmath/pcode_kbasic_binding_method_id.h"
#include "../kbasic_binding/_movie/pcode_kbasic_binding_method_id.h"
#include "../kbasic_binding/_sound/pcode_kbasic_binding_method_id.h"
#include "../kbasic_binding/_web/pcode_kbasic_binding_method_id.h"
#include "../kbasic_binding/_imagebutton/pcode_kbasic_binding_method_id.h"
#include "../kbasic_binding/_database/pcode_kbasic_binding_method_id.h"
#include "../kbasic_binding/_table/pcode_kbasic_binding_method_id.h"
#include "../kbasic_binding/_query/pcode_kbasic_binding_method_id.h"
#include "../kbasic_binding/_record/pcode_kbasic_binding_method_id.h"
#include "../kbasic_binding/_databasedialog/pcode_kbasic_binding_method_id.h"
#include "../kbasic_binding/_toolbutton/pcode_kbasic_binding_method_id.h"

//#include "../kbasic_binding/_hidden/pcode_kbasic_binding_method_id.h"


//#include "../kbasic_binding/_conversion/pcode_kbasic_binding_method_id.h"

//#include "../kbasic_binding/_bytearray/pcode_kbasic_binding_method_id.h"
//#include "../kbasic_binding/_collection/pcode_kbasic_binding_method_id.h" 




/*
#include "../kbasic_binding/_dot/pcode_kbasic_binding_method_id.h"

#include "../kbasic_binding/_line/pcode_kbasic_binding_method_id.h"
#include "../kbasic_binding/_rectangle/pcode_kbasic_binding_method_id.h"
#include "../kbasic_binding/_circle/pcode_kbasic_binding_method_id.h"
#include "../kbasic_binding/_qwidget/pcode_kbasic_binding_method_id.h"
#include "../kbasic_binding/_subform/pcode_kbasic_binding_method_id.h"
#include "../kbasic_binding/_treeview/pcode_kbasic_binding_method_id.h"
*/

//------------------------------------------------------------------------------------------------------------------------------------


class pcode_kbasic_binding {
public:
//	pcode_kbasic_binding();
	//~pcode_kbasic_binding();


static const char *methodname_(int n)
{
	switch(n)
	{
// KBBINDING
    // CONTROL
//------------------------------------------------------------------------------------------------------------------------------------
#include "../kbasic_binding/_udpsocket/pcode_kbasic_binding_method_name.h"
#include "../kbasic_binding/_scrollbar/pcode_kbasic_binding_method_name.h"
#include "../kbasic_binding/_spinbox/pcode_kbasic_binding_method_name.h"
#include "../kbasic_binding/_slider/pcode_kbasic_binding_method_name.h"
#include "../kbasic_binding/_formsview/pcode_kbasic_binding_method_name.h"
#include "../kbasic_binding/_toolbarview/pcode_kbasic_binding_method_name.h"
#include "../kbasic_binding/_svg/pcode_kbasic_binding_method_name.h"
#include "../kbasic_binding/_commandlinkbutton/pcode_kbasic_binding_method_name.h"
#include "../kbasic_binding/_resizebox/pcode_kbasic_binding_method_name.h"
#include "../kbasic_binding/_line/pcode_kbasic_binding_method_name.h"
#include "../kbasic_binding/_checkbox/pcode_kbasic_binding_method_name.h"
//#include "../kbasic_binding/_control/pcode_kbasic_binding_method_name.h" 
#include "../kbasic_binding/_form/pcode_kbasic_binding_method_name.h"
#include "../kbasic_binding/_commandbutton/pcode_kbasic_binding_method_name.h"
#include "../kbasic_binding/_label/pcode_kbasic_binding_method_name.h"
#include "../kbasic_binding/_textbox/pcode_kbasic_binding_method_name.h"
#include "../kbasic_binding/_radiobutton/pcode_kbasic_binding_method_name.h"
#include "../kbasic_binding/_frame/pcode_kbasic_binding_method_name.h"
#include "../kbasic_binding/_combobox/pcode_kbasic_binding_method_name.h"
#include "../kbasic_binding/_listbox/pcode_kbasic_binding_method_name.h"
#include "../kbasic_binding/_datebox/pcode_kbasic_binding_method_name.h"
#include "../kbasic_binding/_timebox/pcode_kbasic_binding_method_name.h"
#include "../kbasic_binding/_datetimebox/pcode_kbasic_binding_method_name.h"
#include "../kbasic_binding/_timer/pcode_kbasic_binding_method_name.h"
#include "../kbasic_binding/_tab/pcode_kbasic_binding_method_name.h"
#include "../kbasic_binding/_image/pcode_kbasic_binding_method_name.h"
#include "../kbasic_binding/_treeview/pcode_kbasic_binding_method_name.h"
#include "../kbasic_binding/_box/pcode_kbasic_binding_method_name.h"

	default: return pcode_kbasic_binding::methodname2_(n);
	}
}


static const char *methodname2_(int n)
{
	switch(n)
	{
// KBBINDING

#include "../kbasic_binding/_progressbar/pcode_kbasic_binding_method_name.h"
#include "../kbasic_binding/_editor/pcode_kbasic_binding_method_name.h"
#include "../kbasic_binding/_browser/pcode_kbasic_binding_method_name.h"
#include "../kbasic_binding/_menubaritem/pcode_kbasic_binding_method_name.h"
#include "../kbasic_binding/_toolbaritem/pcode_kbasic_binding_method_name.h"
#include "../kbasic_binding/_menubar/pcode_kbasic_binding_method_name.h"
#include "../kbasic_binding/_forms/pcode_kbasic_binding_method_name.h"
#include "../kbasic_binding/_toolbar/pcode_kbasic_binding_method_name.h"
#include "../kbasic_binding/_strings/pcode_kbasic_binding_method_name.h"
#include "../kbasic_binding/_stringsstrings/pcode_kbasic_binding_method_name.h"
#include "../kbasic_binding/_bits/pcode_kbasic_binding_method_name.h"
#include "../kbasic_binding/_array/pcode_kbasic_binding_method_name.h"
#include "../kbasic_binding/_application/pcode_kbasic_binding_method_name.h"
#include "../kbasic_binding/_mainwindow/pcode_kbasic_binding_method_name.h"
#include "../kbasic_binding/_systemtray/pcode_kbasic_binding_method_name.h"
#include "../kbasic_binding/_err/pcode_kbasic_binding_method_name.h"
#include "../kbasic_binding/_log/pcode_kbasic_binding_method_name.h"
#include "../kbasic_binding/_actions/pcode_kbasic_binding_method_name.h"
#include "../kbasic_binding/_process/pcode_kbasic_binding_method_name.h"
#include "../kbasic_binding/_file/pcode_kbasic_binding_method_name.h"
#include "../kbasic_binding/_dir/pcode_kbasic_binding_method_name.h"
#include "../kbasic_binding/_preferences/pcode_kbasic_binding_method_name.h"
#include "../kbasic_binding/_sounds/pcode_kbasic_binding_method_name.h"
#include "../kbasic_binding/_pixmaps/pcode_kbasic_binding_method_name.h"
//#include "../kbasic_binding/_pixmap/pcode_kbasic_binding_method_name.h"
#include "../kbasic_binding/_color/pcode_kbasic_binding_method_name.h"
#include "../kbasic_binding/_colors/pcode_kbasic_binding_method_name.h"
//#include "../kbasic_binding/_font/pcode_kbasic_binding_method_name.h"
#include "../kbasic_binding/_fonts/pcode_kbasic_binding_method_name.h"
#include "../kbasic_binding/_paint/pcode_kbasic_binding_method_name.h"
#include "../kbasic_binding/_control/pcode_kbasic_binding_method_name.h"
#include "../kbasic_binding/_event/pcode_kbasic_binding_method_name.h"
#include "../kbasic_binding/_childcontrol/pcode_kbasic_binding_method_name.h"
//#include "../kbasic_binding/_report/pcode_kbasic_binding_method_name.h"
#include "../kbasic_binding/_header/pcode_kbasic_binding_method_name.h"
#include "../kbasic_binding/_footer/pcode_kbasic_binding_method_name.h"
#include "../kbasic_binding/_serialport/pcode_kbasic_binding_method_name.h"
#include "../kbasic_binding/_statusbar/pcode_kbasic_binding_method_name.h"
#include "../kbasic_binding/_savedialog/pcode_kbasic_binding_method_name.h"
#include "../kbasic_binding/_fontdialog/pcode_kbasic_binding_method_name.h"
#include "../kbasic_binding/_colordialog/pcode_kbasic_binding_method_name.h"
#include "../kbasic_binding/_progressdialog/pcode_kbasic_binding_method_name.h"
#include "../kbasic_binding/_inputdialog/pcode_kbasic_binding_method_name.h"
#include "../kbasic_binding/_messagebox/pcode_kbasic_binding_method_name.h"
#include "../kbasic_binding/_opendialog/pcode_kbasic_binding_method_name.h"
#include "../kbasic_binding/_cmath/pcode_kbasic_binding_method_name.h"
#include "../kbasic_binding/_movie/pcode_kbasic_binding_method_name.h"
#include "../kbasic_binding/_sound/pcode_kbasic_binding_method_name.h"
#include "../kbasic_binding/_web/pcode_kbasic_binding_method_name.h"
#include "../kbasic_binding/_imagebutton/pcode_kbasic_binding_method_name.h"
#include "../kbasic_binding/_database/pcode_kbasic_binding_method_name.h"
#include "../kbasic_binding/_table/pcode_kbasic_binding_method_name.h"
#include "../kbasic_binding/_query/pcode_kbasic_binding_method_name.h"
#include "../kbasic_binding/_record/pcode_kbasic_binding_method_name.h"
#include "../kbasic_binding/_databasedialog/pcode_kbasic_binding_method_name.h"
#include "../kbasic_binding/_toolbutton/pcode_kbasic_binding_method_name.h"




//#include "../kbasic_binding/_textarea/pcode_kbasic_binding_method_name.h"





//#include "../kbasic_binding/_hidden/pcode_kbasic_binding_method_name.h"



//#include "../kbasic_binding/_conversion/pcode_kbasic_binding_method_name.h"

//#include "../kbasic_binding/_bytearray/pcode_kbasic_binding_method_name.h" 



//#include "../kbasic_binding/_collection/pcode_kbasic_binding_method_name.h"

    

/*
#include "../kbasic_binding/_dot/pcode_kbasic_binding_method_name.h"
#include "../kbasic_binding/_line/pcode_kbasic_binding_method_name.h"
#include "../kbasic_binding/_rectangle/pcode_kbasic_binding_method_name.h"
#include "../kbasic_binding/_circle/pcode_kbasic_binding_method_name.h"
#include "../kbasic_binding/_qwidget/pcode_kbasic_binding_method_name.h"
#include "../kbasic_binding/_subform/pcode_kbasic_binding_method_name.h"
#include "../kbasic_binding/_treeview/pcode_kbasic_binding_method_name.h"

*/
//------------------------------------------------------------------------------------------------------------------------------------
	default: return ""; //pcode_kbasic_binding::methodname_(n);
	}
}


static const char *classname_(int n)
{
	switch(n)
	{
//------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------
// 
// KBBINDING
// BINDING
// CONTROL
    
case pcode___udpsocket: return "UdpSocket";
case pcode___scrollbar: return "ScrollBar";
case pcode___spinbox: return "SpinBox";
case pcode___slider: return "Slider";
case pcode___formsview: return "FormsView";
case pcode___toolbarview: return "ToolBarView";
case pcode___svg: return "SvgBox";
case pcode___commandlinkbutton: return "CommandLinkButton";
case pcode___resizebox: return "ResizeBox";
case pcode___toolbutton: return "ToolButton";
case pcode___line: return "LINE";
case pcode___form: return "Form";
case pcode___control: return "Control";
case pcode___checkbox: return "CheckBox";
case pcode___commandbutton: return "CommandButton";
case pcode___label: return "Label";
case pcode___textbox: return "TextBox";
case pcode___radiobutton: return "RadioButton";
case pcode___frame: return "Frame";
case pcode___combobox: return "ComboBox";
case pcode___listbox: return "ListBox";
case pcode___datebox: return "DateBox";
case pcode___timebox: return "TimeBox";
case pcode___datetimebox: return "DateTimeBox";
case pcode___timer: return "TIMER";
case pcode___tab: return "TabView";
case pcode___image: return "ImageBox";
case pcode___treeview: return "TreeView";
case pcode___box: return "Box";
case pcode___progressbar: return "ProgressBar";
case pcode___editor: return "RichTextBox";
case pcode___browser: return "HtmlView";
case pcode___menubaritem: return "MenuBarItem";
case pcode___toolbaritem: return "ToolBarItem";
case pcode___menubar: return "MenuBar";
case pcode___forms: return "Forms";
case pcode___toolbar: return "ToolBar";
case pcode___strings: return "Strings";
case pcode___stringsstrings: return "Dictionary";
case pcode___bits: return "Bits";
case pcode___array: return "ARRAY";
case pcode___application: return "Application";
case pcode___mainwindow: return "MainWindow";
case pcode___systemtray: return "SystemTray";
case pcode___err: return "Err2";
case pcode___log: return "Log";
case pcode___actions: return "Actions";
case pcode___process: return "Process";
case pcode___file: return "File";
case pcode___dir: return "Dir";
case pcode___preferences: return "Preferences";  
case pcode___sounds: return "Sounds";
case pcode___pixmaps: return "Pixmaps";
case pcode___pixmap: return "Pixmap";
case pcode___color: return "Color";
case pcode___colors: return "Colors";
case pcode___font: return "Font";
case pcode___fonts: return "Fonts";
case pcode___paint: return "Painter";
case pcode___event: return "Event";
case pcode___childcontrol: return "FormView";
//case pcode___report: return "Report";
case pcode___header: return "Header";
case pcode___footer: return "Footer";
case pcode___serialport: return "SerialPort";
case pcode___statusbar: return "StatusBar";
case pcode___savedialog: return "SaveDialog";
case pcode___colordialog: return "ColorDialog";
case pcode___progressdialog: return "ProgressDialog";
case pcode___inputdialog: return "InputDialog";
case pcode___messagebox: return "MessageBox";
case pcode___fontdialog: return "FontDialog";
case pcode___opendialog: return "OpenDialog";
case pcode___cmath: return "CMath";
case pcode___movie: return "MovieBox";
case pcode___sound: return "SOUND";
case pcode___web: return "WebView";
case pcode___imagebutton: return "ImageButton";
case pcode___database: return "DATABASE";
case pcode___table: return "Table";
case pcode___query: return "Query";
case pcode___record: return "Records";
case pcode___databasedialog: return "DatabaseDialog";

  //case pcode___optionbutton: return "OptionButton";

//case pcode___textarea: return "TextArea";




//case pcode___canvas: return "Canvas";
//case pcode___listview: return "ListView";



//case pcode___line: return "Line";
//case pcode___rectangle: return "Rectangle";
//case pcode___circle: return "Circle";
//case pcode___hidden: return "Hidden";
//case pcode___qwidget: return "QWidget";

//case pcode___subform: return "SubForm";

//case pcode___kbasic: return "KBasic";
//case pcode___conversion: return "Conversion";
//case pcode___desktop: return "Desktop";

//case pcode___bytearray: return "Bytearray";

//case pcode___kb: return "kb";

//case pcode___activex: return "ActiveX";
//case pcode___collection: return "Collection";



  



//------------------------------------------------------------------------------------------------------------------------------------
	default: return ""; // pcode_kbasic_binding::classname_(n);
	}
}

};


#endif