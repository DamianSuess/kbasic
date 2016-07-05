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
extern _mainwindow *EXTERN_my_mainwindow;

extern QMap<int, interpreter_parameter*> v;
extern int n;
extern interpreter_parameter *identifier;// = new interpreter_parameter();

extern t_boolean b;
extern t_integer i;
extern t_long l;

extern void *pp;


bool interpreter::binding_callMethod_kbasic_binding2(int m, bool bReturn)
{

	switch(m){   
// KBBINDING
//------------------------------------------------------------------------------------------------------------------------------------
#include "../kbasic_binding/_stringsstrings/interpreter_kbasic_binding_call_instance.h"
#include "../kbasic_binding/_bits/interpreter_kbasic_binding_call_instance.h"
#include "../kbasic_binding/_array/interpreter_kbasic_binding_call_instance.h"
#include "../kbasic_binding/_application/interpreter_kbasic_binding_call_instance.h"
#include "../kbasic_binding/_mainwindow/interpreter_kbasic_binding_call_instance.h"    
#include "../kbasic_binding/_err/interpreter_kbasic_binding_call_instance.h"
#include "../kbasic_binding/_log/interpreter_kbasic_binding_call_instance.h"
#include "../kbasic_binding/_actions/interpreter_kbasic_binding_call_instance.h"    
#include "../kbasic_binding/_process/interpreter_kbasic_binding_call_instance.h"    
#include "../kbasic_binding/_file/interpreter_kbasic_binding_call_instance.h"        
#include "../kbasic_binding/_dir/interpreter_kbasic_binding_call_instance.h"        
#include "../kbasic_binding/_preferences/interpreter_kbasic_binding_call_instance.h"        
#include "../kbasic_binding/_sounds/interpreter_kbasic_binding_call_instance.h"
#include "../kbasic_binding/_pixmaps/interpreter_kbasic_binding_call_instance.h"
//#include "../kbasic_binding/_pixmap/interpreter_kbasic_binding_call_instance.h"
#include "../kbasic_binding/_color/interpreter_kbasic_binding_call_instance.h"
#include "../kbasic_binding/_colors/interpreter_kbasic_binding_call_instance.h"
//#include "../kbasic_binding/_font/interpreter_kbasic_binding_call_instance.h"
#include "../kbasic_binding/_fonts/interpreter_kbasic_binding_call_instance.h"

    //#include "../kbasic_binding/_report/interpreter_kbasic_binding_call_instance.h"






//#include "../kbasic_binding/_hidden/interpreter_kbasic_binding_call_instance.h"




//#include "../kbasic_binding/_conversion/interpreter_kbasic_binding_call_instance.h"
//#include "../kbasic_binding/_bytearray/interpreter_kbasic_binding_call_instance.h"
//#include "../kbasic_binding/_control/interpreter_kbasic_binding_call_instance.h"
//#include "../kbasic_binding/_collection/interpreter_kbasic_binding_call_instance.h"


//------------------------------------------------------------------------------------------------------------------------------------

default:
  return binding_callMethod_kbasic_binding3(m, bReturn);
	}


	return true;
}
