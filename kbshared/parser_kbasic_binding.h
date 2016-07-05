/*
***************************************************************************
Copyright (C) 2000-2008 KBasic Software: www.kbasic.com. All rights reserved.
Source codes are copyrighted by Bernd Noetscher 2000-2008.

You may use this source codes under the terms of the GNU Public License (Version 3)
as published by the Free Software Foundation. 

If you are interested in using the source codes for other licenses or 
commercial development, you must buy commercial licenses from KBasic Software.

This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
***************************************************************************
*/

#ifndef PARSER_KBASIC_BINDING_H
#define PARSER_KBASIC_BINDING_H



setNamespace(pcode__kbasic_binding_class);

//------------------------------------------------------------------------------------------------------------------------------------
// KBBINDING
// CONTROL
//#include "../kbasic_binding/_control/parser_kbasic_binding.h"
#include "../kbasic_binding/_udpsocket/parser_kbasic_binding.h"
#include "../kbasic_binding/_scrollbar/parser_kbasic_binding.h"
#include "../kbasic_binding/_spinbox/parser_kbasic_binding.h"
#include "../kbasic_binding/_slider/parser_kbasic_binding.h"
#include "../kbasic_binding/_formsview/parser_kbasic_binding.h"
#include "../kbasic_binding/_toolbarview/parser_kbasic_binding.h"
#include "../kbasic_binding/_svg/parser_kbasic_binding.h"
#include "../kbasic_binding/_commandlinkbutton/parser_kbasic_binding.h"
#include "../kbasic_binding/_resizebox/parser_kbasic_binding.h"
#include "../kbasic_binding/_toolbutton/parser_kbasic_binding.h"
#include "../kbasic_binding/_line/parser_kbasic_binding.h"
#include "../kbasic_binding/_movie/parser_kbasic_binding.h"
#include "../kbasic_binding/_sound/parser_kbasic_binding.h"
#include "../kbasic_binding/_web/parser_kbasic_binding.h"
#include "../kbasic_binding/_checkbox/parser_kbasic_binding.h"
#include "../kbasic_binding/_form/parser_kbasic_binding.h"
#include "../kbasic_binding/_commandbutton/parser_kbasic_binding.h"
#include "../kbasic_binding/_label/parser_kbasic_binding.h"
#include "../kbasic_binding/_textbox/parser_kbasic_binding.h"
#include "../kbasic_binding/_radiobutton/parser_kbasic_binding.h"
#include "../kbasic_binding/_frame/parser_kbasic_binding.h"
#include "../kbasic_binding/_combobox/parser_kbasic_binding.h"
#include "../kbasic_binding/_listbox/parser_kbasic_binding.h"
#include "../kbasic_binding/_datebox/parser_kbasic_binding.h"
#include "../kbasic_binding/_timebox/parser_kbasic_binding.h"
#include "../kbasic_binding/_datetimebox/parser_kbasic_binding.h"
#include "../kbasic_binding/_timer/parser_kbasic_binding.h"
#include "../kbasic_binding/_tab/parser_kbasic_binding.h"
#include "../kbasic_binding/_image/parser_kbasic_binding.h"
#include "../kbasic_binding/_treeview/parser_kbasic_binding.h"
#include "../kbasic_binding/_box/parser_kbasic_binding.h"
#include "../kbasic_binding/_progressbar/parser_kbasic_binding.h"
#include "../kbasic_binding/_editor/parser_kbasic_binding.h"
#include "../kbasic_binding/_browser/parser_kbasic_binding.h"
#include "../kbasic_binding/_menubaritem/parser_kbasic_binding.h"
#include "../kbasic_binding/_toolbaritem/parser_kbasic_binding.h"
#include "../kbasic_binding/_menubar/parser_kbasic_binding.h"
#include "../kbasic_binding/_forms/parser_kbasic_binding.h"
#include "../kbasic_binding/_toolbar/parser_kbasic_binding.h"
#include "../kbasic_binding/_strings/parser_kbasic_binding.h"
#include "../kbasic_binding/_stringsstrings/parser_kbasic_binding.h"
#include "../kbasic_binding/_bits/parser_kbasic_binding.h"
#include "../kbasic_binding/_array/parser_kbasic_binding.h"
#include "../kbasic_binding/_application/parser_kbasic_binding.h"
#include "../kbasic_binding/_mainwindow/parser_kbasic_binding.h"
#include "../kbasic_binding/_systemtray/parser_kbasic_binding.h"
#include "../kbasic_binding/_err/parser_kbasic_binding.h"
#include "../kbasic_binding/_log/parser_kbasic_binding.h"
#include "../kbasic_binding/_actions/parser_kbasic_binding.h"
#include "../kbasic_binding/_process/parser_kbasic_binding.h"
#include "../kbasic_binding/_file/parser_kbasic_binding.h"
#include "../kbasic_binding/_dir/parser_kbasic_binding.h"
#include "../kbasic_binding/_preferences/parser_kbasic_binding.h"
#include "../kbasic_binding/_sounds/parser_kbasic_binding.h"
#include "../kbasic_binding/_pixmaps/parser_kbasic_binding.h"
//#include "../kbasic_binding/_pixmap/parser_kbasic_binding.h"
#include "../kbasic_binding/_color/parser_kbasic_binding.h"
#include "../kbasic_binding/_colors/parser_kbasic_binding.h"
//#include "../kbasic_binding/_font/parser_kbasic_binding.h"
#include "../kbasic_binding/_fonts/parser_kbasic_binding.h"
#include "../kbasic_binding/_paint/parser_kbasic_binding.h"
#include "../kbasic_binding/_control/parser_kbasic_binding.h"
#include "../kbasic_binding/_event/parser_kbasic_binding.h"
#include "../kbasic_binding/_childcontrol/parser_kbasic_binding.h"
//#include "../kbasic_binding/_report/parser_kbasic_binding.h"
#include "../kbasic_binding/_footer/parser_kbasic_binding.h"
#include "../kbasic_binding/_header/parser_kbasic_binding.h"
#include "../kbasic_binding/_serialport/parser_kbasic_binding.h"
#include "../kbasic_binding/_statusbar/parser_kbasic_binding.h"
#include "../kbasic_binding/_savedialog/parser_kbasic_binding.h"
#include "../kbasic_binding/_colordialog/parser_kbasic_binding.h"
#include "../kbasic_binding/_progressdialog/parser_kbasic_binding.h"
#include "../kbasic_binding/_inputdialog/parser_kbasic_binding.h"
#include "../kbasic_binding/_messagebox/parser_kbasic_binding.h"
#include "../kbasic_binding/_fontdialog/parser_kbasic_binding.h"
#include "../kbasic_binding/_opendialog/parser_kbasic_binding.h"
#include "../kbasic_binding/_cmath/parser_kbasic_binding.h"
#include "../kbasic_binding/_imagebutton/parser_kbasic_binding.h"
#include "../kbasic_binding/_database/parser_kbasic_binding.h"
#include "../kbasic_binding/_table/parser_kbasic_binding.h"
#include "../kbasic_binding/_query/parser_kbasic_binding.h"
#include "../kbasic_binding/_record/parser_kbasic_binding.h"
#include "../kbasic_binding/_databasedialog/parser_kbasic_binding.h"

/*BN
#include "../kbasic_binding/_optionbutton/parser_kbasic_binding.h"

#include "../kbasic_binding/_textarea/parser_kbasic_binding.h"



#include "../kbasic_binding/_dot/parser_kbasic_binding.h"
#include "../kbasic_binding/_line/parser_kbasic_binding.h"
#include "../kbasic_binding/_rectangle/parser_kbasic_binding.h"
#include "../kbasic_binding/_circle/parser_kbasic_binding.h"
#include "../kbasic_binding/_hidden/parser_kbasic_binding.h"
#include "../kbasic_binding/_qwidget/parser_kbasic_binding.h"

#include "../kbasic_binding/_canvas/parser_kbasic_binding.h"
#include "../kbasic_binding/_listview/parser_kbasic_binding.h"
#include "../kbasic_binding/_subform/parser_kbasic_binding.h"
#include "../kbasic_binding/_tab/parser_kbasic_binding.h"

#include "../kbasic_binding/_kbasic/parser_kbasic_binding.h"
#include "../kbasic_binding/_conversion/parser_kbasic_binding.h"
#include "../kbasic_binding/_desktop/parser_kbasic_binding.h"

#include "../kbasic_binding/_bytearray/parser_kbasic_binding.h"

#include "../kbasic_binding/_activex/parser_kbasic_binding.h"
#include "../kbasic_binding/_collection/parser_kbasic_binding.h"

*/



//------------------------------------------------------------------------------------------------------------------------------------

#endif

/*
setNamespace(pcode__kbasic_binding_class);

new_class(pcode__scanner, pcode__NULL, pcode__NULL);
	new_param("t", pcode__token, false);
new_method(true, pcode__scanner, pcode__scanner__scanner, pcode__scanner);
new_method(true, pcode__scanner, pcode__scanner__scanner1, pcode__scanner);
	new_param("text", pcode__STRING, false);
new_method(true, pcode__scanner, pcode__scanner__scan, pcode__BOOLEAN);




new_class(pcode__parser, pcode__NULL, pcode__NULL);
	new_param("p", pcode__pcode, false);
new_method(true, pcode__parser, pcode__parser__parser, pcode__parser);
	new_param("t", pcode__token, false);
new_method(true, pcode__parser, pcode__parser__parse, pcode__BOOLEAN);




new_class(pcode__interpreter, pcode__NULL, pcode__NULL);
new_method(true, pcode__interpreter, pcode__interpreter__interpreter, pcode__interpreter);
	new_param("p", pcode__pcode, false);
	new_param("pa", pcode__parser, false);
new_method(true, pcode__interpreter, pcode__interpreter__interpret, pcode__BOOLEAN);




new_class(pcode__pcode, pcode__NULL, pcode__NULL);
new_method(true, pcode__pcode, pcode__pcode__pcode, pcode__pcode);




new_class(pcode__token, pcode__NULL, pcode__NULL);
new_method(true, pcode__token, pcode__token__token, pcode__token);
*/
