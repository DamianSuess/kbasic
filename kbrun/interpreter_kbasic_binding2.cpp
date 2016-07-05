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
extern interpreter_parameter *identifier;

extern t_boolean b;
extern t_integer i;
extern t_long l;

extern void *pp;


bool interpreter::binding_callMethod_kbasic_binding(int m, bool bReturn)
{
  foreach(interpreter_parameter *i, v){
    delete i;
  }
  v.clear();

  interpreter_parameter *save_identifier = identifier;
  identifier = 0;


	n = pcode__kbasic_binding_method;

	
	switch(m){    
// KBBINDING
// CONTROL
//------------------------------------------------------------------------------------------------------------------------------------
#include "../kbasic_binding/_udpsocket/interpreter_kbasic_binding_call_instance.h"
#include "../kbasic_binding/_formsview/interpreter_kbasic_binding_call_instance.h"
#include "../kbasic_binding/_toolbarview/interpreter_kbasic_binding_call_instance.h"
#include "../kbasic_binding/_svg/interpreter_kbasic_binding_call_instance.h"
#include "../kbasic_binding/_commandlinkbutton/interpreter_kbasic_binding_call_instance.h"
#include "../kbasic_binding/_resizebox/interpreter_kbasic_binding_call_instance.h"
#include "../kbasic_binding/_toolbutton/interpreter_kbasic_binding_call_instance.h"
#include "../kbasic_binding/_systemtray/interpreter_kbasic_binding_call_instance.h"
#include "../kbasic_binding/_movie/interpreter_kbasic_binding_call_instance.h"
#include "../kbasic_binding/_sound/interpreter_kbasic_binding_call_instance.h"
#include "../kbasic_binding/_web/interpreter_kbasic_binding_call_instance.h"
#include "../kbasic_binding/_checkbox/interpreter_kbasic_binding_call_instance.h"
#include "../kbasic_binding/_form/interpreter_kbasic_binding_call_instance.h"
#include "../kbasic_binding/_combobox/interpreter_kbasic_binding_call_instance.h"
#include "../kbasic_binding/_commandbutton/interpreter_kbasic_binding_call_instance.h"
#include "../kbasic_binding/_frame/interpreter_kbasic_binding_call_instance.h"
//#include "../kbasic_binding/_control/interpreter_kbasic_binding_call_instance.h"
#include "../kbasic_binding/_label/interpreter_kbasic_binding_call_instance.h"
#include "../kbasic_binding/_listbox/interpreter_kbasic_binding_call_instance.h"
#include "../kbasic_binding/_radiobutton/interpreter_kbasic_binding_call_instance.h"
#include "../kbasic_binding/_textbox/interpreter_kbasic_binding_call_instance.h"
#include "../kbasic_binding/_datebox/interpreter_kbasic_binding_call_instance.h"
#include "../kbasic_binding/_timebox/interpreter_kbasic_binding_call_instance.h"




//------------------------------------------------------------------------------------------------------------------------------------
default:
  bool b = binding_callMethod_kbasic_binding2(m, bReturn);
  if (b == false){
    identifier = save_identifier;
    return false;
  }

	}


  if (identifier){
    if (identifier->pcodeType != pcode__INTEGER){ // test needed for special form handling
    }
	  delete identifier;
  }


  identifier = save_identifier;
	return true;
}

