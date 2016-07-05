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


#include <qmap.h>

#include "../kbshared/pcode_kbasic_binding.h"
#include "interpreter_kbasic_binding.h"
#include "interpreter.h"

class _mainwindow;
_mainwindow *EXTERN_my_mainwindow;

QMap<int, interpreter_parameter*> v;
int n;
interpreter_parameter *identifier;// = new interpreter_parameter();
t_boolean b;
t_integer i;
t_long l;
void *pp;

bool interpreter::binding_callStaticMethod_kbasic_binding(int m, bool bReturn)
{
  foreach(interpreter_parameter *i, v){
    delete i;
  }
  v.clear();

  n = pcode__kbasic_binding_method;

  getParam(v, m, n); 

	switch(m){

// KBBINDING
// CONTROL
//------------------------------------------------------------------------------------------------------------------------------------
#include "../kbasic_binding/_udpsocket/interpreter_kbasic_binding_call_static.h"
#include "../kbasic_binding/_scrollbar/interpreter_kbasic_binding_call_static.h"
#include "../kbasic_binding/_spinbox/interpreter_kbasic_binding_call_static.h"
#include "../kbasic_binding/_slider/interpreter_kbasic_binding_call_static.h"
#include "../kbasic_binding/_formsview/interpreter_kbasic_binding_call_static.h"
#include "../kbasic_binding/_toolbarview/interpreter_kbasic_binding_call_static.h"
#include "../kbasic_binding/_svg/interpreter_kbasic_binding_call_static.h"
#include "../kbasic_binding/_commandlinkbutton/interpreter_kbasic_binding_call_static.h"
#include "../kbasic_binding/_resizebox/interpreter_kbasic_binding_call_static.h"
#include "../kbasic_binding/_toolbutton/interpreter_kbasic_binding_call_static.h"
#include "../kbasic_binding/_systemtray/interpreter_kbasic_binding_call_static.h"
#include "../kbasic_binding/_movie/interpreter_kbasic_binding_call_static.h"
#include "../kbasic_binding/_sound/interpreter_kbasic_binding_call_static.h"
#include "../kbasic_binding/_web/interpreter_kbasic_binding_call_static.h"
#include "../kbasic_binding/_checkbox/interpreter_kbasic_binding_call_static.h"
#include "../kbasic_binding/_combobox/interpreter_kbasic_binding_call_static.h"
#include "../kbasic_binding/_commandbutton/interpreter_kbasic_binding_call_static.h"
#include "../kbasic_binding/_form/interpreter_kbasic_binding_call_static.h"
#include "../kbasic_binding/_frame/interpreter_kbasic_binding_call_static.h"
#include "../kbasic_binding/_label/interpreter_kbasic_binding_call_static.h"
#include "../kbasic_binding/_listbox/interpreter_kbasic_binding_call_static.h"
#include "../kbasic_binding/_radiobutton/interpreter_kbasic_binding_call_static.h"
#include "../kbasic_binding/_textbox/interpreter_kbasic_binding_call_static.h"
#include "../kbasic_binding/_datebox/interpreter_kbasic_binding_call_static.h"
#include "../kbasic_binding/_timebox/interpreter_kbasic_binding_call_static.h"
#include "../kbasic_binding/_timer/interpreter_kbasic_binding_call_static.h"
#include "../kbasic_binding/_event/interpreter_kbasic_binding_call_static.h"
#include "../kbasic_binding/_childcontrol/interpreter_kbasic_binding_call_static.h"
#include "../kbasic_binding/_serialport/interpreter_kbasic_binding_call_static.h"
#include "../kbasic_binding/_statusbar/interpreter_kbasic_binding_call_static.h"
#include "../kbasic_binding/_savedialog/interpreter_kbasic_binding_call_static.h"
#include "../kbasic_binding/_fontdialog/interpreter_kbasic_binding_call_static.h"
#include "../kbasic_binding/_colordialog/interpreter_kbasic_binding_call_static.h"
#include "../kbasic_binding/_progressdialog/interpreter_kbasic_binding_call_static.h"
#include "../kbasic_binding/_inputdialog/interpreter_kbasic_binding_call_static.h"
#include "../kbasic_binding/_messagebox/interpreter_kbasic_binding_call_static.h"
#include "../kbasic_binding/_opendialog/interpreter_kbasic_binding_call_static.h"
#include "../kbasic_binding/_cmath/interpreter_kbasic_binding_call_static.h"
#include "../kbasic_binding/_line/interpreter_kbasic_binding_call_static.h"
//#include "../kbasic_binding/_report/interpreter_kbasic_binding_call_static.h"

#include "../kbasic_binding/_databasedialog/interpreter_kbasic_binding_call_static.h"
#include "../kbasic_binding/_database/interpreter_kbasic_binding_call_static.h"
#include "../kbasic_binding/_table/interpreter_kbasic_binding_call_static.h"
#include "../kbasic_binding/_record/interpreter_kbasic_binding_call_static.h"
#include "../kbasic_binding/_query/interpreter_kbasic_binding_call_static.h"



//------------------------------------------------------------------------------------------------------------------------------------


		default:
      return binding_callStaticMethod_kbasic_binding2(m, bReturn,  v);
			break;
	}
 

	return true;
}

bool interpreter::binding_callStaticMethod_kbasic_binding2(int m, bool bReturn, QMap<int, interpreter_parameter*> &v)
{
	
	switch(m){

// KBBINDING
//------------------------------------------------------------------------------------------------------------------------------------
#include "../kbasic_binding/_tab/interpreter_kbasic_binding_call_static.h"
#include "../kbasic_binding/_image/interpreter_kbasic_binding_call_static.h"
#include "../kbasic_binding/_treeview/interpreter_kbasic_binding_call_static.h"
#include "../kbasic_binding/_box/interpreter_kbasic_binding_call_static.h"
#include "../kbasic_binding/_datetimebox/interpreter_kbasic_binding_call_static.h"
#include "../kbasic_binding/_progressbar/interpreter_kbasic_binding_call_static.h"
#include "../kbasic_binding/_editor/interpreter_kbasic_binding_call_static.h"
#include "../kbasic_binding/_browser/interpreter_kbasic_binding_call_static.h"
#include "../kbasic_binding/_menubaritem/interpreter_kbasic_binding_call_static.h"
#include "../kbasic_binding/_toolbaritem/interpreter_kbasic_binding_call_static.h"
#include "../kbasic_binding/_menubar/interpreter_kbasic_binding_call_static.h"
#include "../kbasic_binding/_forms/interpreter_kbasic_binding_call_static.h"
#include "../kbasic_binding/_toolbar/interpreter_kbasic_binding_call_static.h"
#include "../kbasic_binding/_strings/interpreter_kbasic_binding_call_static.h"
#include "../kbasic_binding/_stringsstrings/interpreter_kbasic_binding_call_static.h"
#include "../kbasic_binding/_bits/interpreter_kbasic_binding_call_static.h"
#include "../kbasic_binding/_array/interpreter_kbasic_binding_call_static.h"
#include "../kbasic_binding/_application/interpreter_kbasic_binding_call_static.h"
#include "../kbasic_binding/_mainwindow/interpreter_kbasic_binding_call_static.h"    
#include "../kbasic_binding/_err/interpreter_kbasic_binding_call_static.h"
#include "../kbasic_binding/_log/interpreter_kbasic_binding_call_static.h"
#include "../kbasic_binding/_process/interpreter_kbasic_binding_call_static.h"    
#include "../kbasic_binding/_actions/interpreter_kbasic_binding_call_static.h"    
#include "../kbasic_binding/_file/interpreter_kbasic_binding_call_static.h"        
#include "../kbasic_binding/_dir/interpreter_kbasic_binding_call_static.h"        
#include "../kbasic_binding/_preferences/interpreter_kbasic_binding_call_static.h"        
#include "../kbasic_binding/_sounds/interpreter_kbasic_binding_call_static.h"
#include "../kbasic_binding/_pixmaps/interpreter_kbasic_binding_call_static.h"
//#include "../kbasic_binding/_pixmap/interpreter_kbasic_binding_call_static.h"
#include "../kbasic_binding/_color/interpreter_kbasic_binding_call_static.h"
#include "../kbasic_binding/_colors/interpreter_kbasic_binding_call_static.h"
//#include "../kbasic_binding/_font/interpreter_kbasic_binding_call_static.h"
#include "../kbasic_binding/_fonts/interpreter_kbasic_binding_call_static.h"
#include "../kbasic_binding/_paint/interpreter_kbasic_binding_call_static.h"
#include "../kbasic_binding/_control/interpreter_kbasic_binding_call_static.h"
#include "../kbasic_binding/_imagebutton/interpreter_kbasic_binding_call_static.h"





//#include "../kbasic_binding/_hidden/interpreter_kbasic_binding_call_static.h"




//#include "../kbasic_binding/_conversion/interpreter_kbasic_binding_call_static.h"
//#include "../kbasic_binding/_bytearray/interpreter_kbasic_binding_call_static.h"
//#include "../kbasic_binding/_collection/interpreter_kbasic_binding_call_static.h"
//------------------------------------------------------------------------------------------------------------------------------------
		default:
      return binding_callStaticMethod_kbasic_binding3(m, bReturn, v);
			break;
	}
 

	return true;
}

bool interpreter::binding_callStaticMethod_kbasic_binding3(int m, bool bReturn, QMap<int, interpreter_parameter*> &v)
{
	
	switch(m){    
// KBBINDING
//------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------

		default:
			return false;//runtimeError( utility::con(pcode_qt_binding::name_(m), " method is not binded") );
			break;
	}
  
	return true;
}

bool interpreter::binding_callOperator_kbasic_binding(int m)
{
  return binding_callMethod_kbasic_binding(m, true);
}

bool interpreter::binding_callFunctionOperator_kbasic_binding(int m)
{
  return binding_callStaticMethod_kbasic_binding(m, true);
}

bool interpreter::binding_callFunction_kbasic_binding(int m, bool bReturn)
{
  return binding_callStaticMethod_kbasic_binding(m, bReturn);
}

