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


bool interpreter::binding_callMethod_kbasic_binding4(int m, bool bReturn)
{

	switch(m){
    
// KBBINDING
//------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------

#include "../kbasic_binding/_editor/interpreter_kbasic_binding_call_instance.h"
#include "../kbasic_binding/_browser/interpreter_kbasic_binding_call_instance.h"
#include "../kbasic_binding/_menubar/interpreter_kbasic_binding_call_instance.h"
#include "../kbasic_binding/_forms/interpreter_kbasic_binding_call_instance.h"
#include "../kbasic_binding/_toolbar/interpreter_kbasic_binding_call_instance.h"
#include "../kbasic_binding/_scrollbar/interpreter_kbasic_binding_call_instance.h"
#include "../kbasic_binding/_spinbox/interpreter_kbasic_binding_call_instance.h"
#include "../kbasic_binding/_slider/interpreter_kbasic_binding_call_instance.h"



default:
	return false ; //runtimeError( utility::con(pcode_qt_binding::name_(m), " method is not binded") );

	}

	return true;
}
