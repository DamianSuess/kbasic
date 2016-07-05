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


bool interpreter::binding_callMethod_kbasic_binding3(int m, bool bReturn)
{

	switch(m){
    
// KBBINDING
//------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------

#include "../kbasic_binding/_menubaritem/interpreter_kbasic_binding_call_instance.h"
#include "../kbasic_binding/_toolbaritem/interpreter_kbasic_binding_call_instance.h"
#include "../kbasic_binding/_strings/interpreter_kbasic_binding_call_instance.h"
#include "../kbasic_binding/_box/interpreter_kbasic_binding_call_instance.h"
#include "../kbasic_binding/_datetimebox/interpreter_kbasic_binding_call_instance.h"
#include "../kbasic_binding/_progressbar/interpreter_kbasic_binding_call_instance.h"
#include "../kbasic_binding/_tab/interpreter_kbasic_binding_call_instance.h"
#include "../kbasic_binding/_image/interpreter_kbasic_binding_call_instance.h"
#include "../kbasic_binding/_treeview/interpreter_kbasic_binding_call_instance.h"
#include "../kbasic_binding/_progressdialog/interpreter_kbasic_binding_call_instance.h"
#include "../kbasic_binding/_inputdialog/interpreter_kbasic_binding_call_instance.h"
#include "../kbasic_binding/_messagebox/interpreter_kbasic_binding_call_instance.h"
#include "../kbasic_binding/_opendialog/interpreter_kbasic_binding_call_instance.h"
#include "../kbasic_binding/_cmath/interpreter_kbasic_binding_call_instance.h"
#include "../kbasic_binding/_line/interpreter_kbasic_binding_call_instance.h"
#include "../kbasic_binding/_databasedialog/interpreter_kbasic_binding_call_instance.h"
#include "../kbasic_binding/_database/interpreter_kbasic_binding_call_instance.h"
#include "../kbasic_binding/_table/interpreter_kbasic_binding_call_instance.h"
#include "../kbasic_binding/_record/interpreter_kbasic_binding_call_instance.h"
#include "../kbasic_binding/_query/interpreter_kbasic_binding_call_instance.h"
#include "../kbasic_binding/_paint/interpreter_kbasic_binding_call_instance.h"
#include "../kbasic_binding/_control/interpreter_kbasic_binding_call_instance.h"
#include "../kbasic_binding/_childcontrol/interpreter_kbasic_binding_call_instance.h"
#include "../kbasic_binding/_imagebutton/interpreter_kbasic_binding_call_instance.h"
#include "../kbasic_binding/_timer/interpreter_kbasic_binding_call_instance.h"
#include "../kbasic_binding/_event/interpreter_kbasic_binding_call_instance.h"
#include "../kbasic_binding/_serialport/interpreter_kbasic_binding_call_instance.h"
#include "../kbasic_binding/_statusbar/interpreter_kbasic_binding_call_instance.h"
#include "../kbasic_binding/_savedialog/interpreter_kbasic_binding_call_instance.h"
#include "../kbasic_binding/_fontdialog/interpreter_kbasic_binding_call_instance.h"
#include "../kbasic_binding/_colordialog/interpreter_kbasic_binding_call_instance.h"



default:
   return binding_callMethod_kbasic_binding4(m, bReturn);

	}


	return true;
}
