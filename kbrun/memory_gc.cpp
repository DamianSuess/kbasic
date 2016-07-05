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


#include "memory_gc.h"
#include "interpreter.h"

#include "interpreter_kbasic_binding.h"
/*
liste pointer referenzcounter
add - bei erzeugung und zuweisung  + inc 
inc
dec - bei löschen der variable (verlassen der methode)

deleteold - periodisch aufgerufen p=0, dann löschen

alle freigeben, bei programmbeendigung


 rückgabe von objekten aus funktion, objekt darf nicht gelöscht werden, gc muss sich darum kümmern

*/

extern t_pointer myGcLock2;

memory_gc::memory_gc			(interpreter *_myInterpreter)
{
  myInterpreter = _myInterpreter;
}

memory_gc::~memory_gc		()
{
  deleteAll();
  deleteAll2();
}

// ****************************
// * bool gcError(char *acGcError)
// *
// * description:
// * prints a gc error message
// *
// * interpreter_parameter:
// * char *acGcError = the error message to print
// *
// * return:
// * dummy
// ****************************
bool memory_gc::gcError(char *acGcError)
{
	static char acText[1024];

	sprintf(acText, "\ngc error: %s\n", acGcError);
	CONSOLE printError(acText);
	return false;
}

bool 		memory_gc::add	(memory_variable2 *object)
{
  if (!list_gc.contains(object)){
	  gc_ *t = new gc_();

	  t->object = object;
	  t->count = 0;

	  list_gc.insert(object, t);

  }

  return true;

}

bool		memory_gc::first	()
{
  it = list_gc.begin();
	return it != list_gc.end();
}

bool		memory_gc::next	()
{
	++it;
	return it != list_gc.end();
}

void 		memory_gc::inc	(memory_variable2 *object)
{
  if (object != 0 && list_gc.contains(object)){

    gc_ *t = list_gc[object];
    t->count++;

  }
}

void 		memory_gc::dec	(memory_variable2 *object)
{
  if (object != 0 && list_gc.contains(object)){
   
    gc_ *t = list_gc[object];

    if (t){

      t->count--;

      if (t->count == 0){
        if (object->getBindingParentClassType() != pcode___form) deleteOld(object); // forms are not freed implicitly by gc
      }
    }
  }

}

void 		memory_gc::deleteOld	(memory_variable2 *object, bool bRemove)
{
  if (object != 0 && list_gc.contains(object)){
    int nClassId = object->getClassId();
    int nId = myInterpreter->myClass->getDestructorId(nClassId);

    
    if (nId > 0){
      bool b = myInterpreter->bRunPcode; // always execute destructors even if program already stopped
      myInterpreter->bRunPcode = true;
      myInterpreter->callDestructor(nClassId, nId, true);                 
      myInterpreter->bRunPcode = b;
    }

    if (bRemove){
      gc_ *t = list_gc[object];
      delete t;
      list_gc.remove(object); 
    } else {
      list_gc[object] = 0;
    }
  }

}

void 		memory_gc::deleteOld	()
{
  if (first()){
    do {
      gc_ *t = *it;

      if (t && t->count == 0){
        deleteOld(t->object);
        if (!first()) break;
      }      

    } while (next());
  }  
}

void 		memory_gc::deleteAll	()
{
  if (first()){
    do {
      gc_ *t = *it;
      int n = list_gc.count();


      if (t){
        deleteOld(t->object);
        if (!first()) break;
      }

    } while (next()); // iterator ungultig und da alle abgearbeitet werden müssen  first
  }  

  list_gc.clear();
}

// ***************

bool 		memory_gc::add2	(t_pointer pointer, int nType)
{
  if (!list_gc2.contains(pointer)){
	  gc2_ *t2 = new gc2_();

	  t2->pointer = pointer;
	  t2->count = 0;
	  t2->type = nType;  

	  list_gc2.insert(pointer, t2);

  }

  return true;

}

bool		memory_gc::first2	()
{
  it2 = list_gc2.begin();
	return it2 != list_gc2.end();
}

bool		memory_gc::next2	()
{
	++it2;
	return it2 != list_gc2.end();
}

void 		memory_gc::inc2	(t_pointer pointer)
{
  if (pointer != 0 && list_gc2.contains(pointer)){

    gc2_ *t2 = list_gc2[pointer];
    t2->count++;

  }
}

void 		memory_gc::dec2	(t_pointer pointer)
{
  int n = list_gc2.count();
  if (pointer != 0 && list_gc2.contains(pointer)){
   
    gc2_ *t2 = list_gc2[pointer];

    if (t2){

      t2->count--;
      if (t2->count == 0 && pointer != myGcLock2){
        deleteOld2(pointer);
      }
    }
  }

}

void 		memory_gc::deleteOld2	(t_pointer pointer, bool bRemove)
{
  if (pointer != 0 && list_gc2.contains(pointer)){

   
 
      gc2_ *t2 = list_gc2[pointer];

      if (t2){
        switch(t2->type){
          // CONTROL
          
          case pcode___udpsocket: delete (kb_udpsocket *) pointer; break;
          case pcode___scrollbar: delete (kb_scrollbar *) pointer; break;
          case pcode___spinbox: delete (kb_spinbox *) pointer; break;
          case pcode___slider: delete (kb_slider *) pointer; break;
          case pcode___formsview: delete (kb_formsview *) pointer; break;
          case pcode___toolbarview: delete (kb_toolbarview *) pointer; break;
          case pcode___svg: delete (kb_svg *) pointer; break;
          case pcode___commandlinkbutton: delete (kb_commandlinkbutton *) pointer; break;
          case pcode___resizebox: delete (kb_resizebox *) pointer; break;
          case pcode___toolbutton: delete (kb_toolbutton *) pointer; break;
          case pcode___movie: delete (kb_movie *) pointer; break;
          case pcode___sound: delete (kb_sound *) pointer; break;
          case pcode___web: delete (kb_web *) pointer; break;
          case pcode___datetimebox: delete (kb_datetimebox *) pointer; break;
          case pcode___datebox: delete (kb_datebox *) pointer; break;
          case pcode___timebox: delete (kb_timebox *) pointer; break;
          case pcode___checkbox: delete (kb_checkbox *) pointer; break;
          case pcode___combobox: delete (kb_combobox *) pointer; break;
          case pcode___label: delete (kb_label *) pointer; break;
          case pcode___radiobutton: delete (kb_radiobutton *) pointer; break;
          case pcode___commandbutton: delete (kb_commandbutton *) pointer; break;
          case pcode___listbox: delete (kb_listbox *) pointer; break;
          case pcode___textbox: delete (kb_textbox *) pointer; break;
          case pcode___frame: delete (kb_frame *) pointer; break;
          case pcode___form: delete (kb_form *) pointer; break;
          case pcode___timer: delete (kb_timer *) pointer; break;
          case pcode___tab: delete (kb_tab *) pointer; break;
          case pcode___image: delete (kb_image *) pointer; break;
          case pcode___treeview: delete (kb_treeview *) pointer; break;
          case pcode___box: delete (kb_box *) pointer; break;
          case pcode___progressbar: delete (kb_progressbar *) pointer; break;
          case pcode___editor: delete (kb_editor *) pointer; break;
          case pcode___browser: delete (kb_browser *) pointer; break;
          case pcode___menubaritem: delete (kb_menubaritem *) pointer; break;
          case pcode___toolbaritem: delete (kb_toolbaritem *) pointer; break;
          case pcode___menubar: delete (kb_menubar *) pointer; break;
          case pcode___forms: delete (kb_forms *) pointer; break;
          case pcode___toolbar: delete (kb_toolbar *) pointer; break;
          case pcode___strings: delete (kb_strings *) pointer; break;
          case pcode___stringsstrings: delete (kb_stringsstrings *) pointer; break;
          case pcode___bits: delete (kb_bits *) pointer; break;
          case pcode___array: delete (kb_array *) pointer; break;
          case pcode___application: delete (kb_application *) pointer; break;
          case pcode___err: delete (kb_err *) pointer; break;
          case pcode___log: delete (kb_log *) pointer; break;
          case pcode___pixmaps: delete (kb_pixmaps *) pointer; break;
//          case pcode___pixmap: delete (kb_pixmap *) pointer; break;
          case pcode___color: delete (kb_color *) pointer; break;
          case pcode___colors: delete (kb_colors *) pointer; break;
         // case pcode___font: delete (kb_font *) pointer; break;
          case pcode___fonts: delete (kb_fonts *) pointer; break;
          case pcode___paint: delete (kb_paint *) pointer; break;
          case pcode___control: delete (kb_control *) pointer; break;
          case pcode___event: delete (kb_event *) pointer; break;
          case pcode___childcontrol: delete (kb_childcontrol *) pointer; break;
          case pcode___serialport: delete (kb_serialport *) pointer; break;
          case pcode___statusbar: delete (kb_statusbar *) pointer; break;
          case pcode___savedialog: delete (kb_savedialog *) pointer; break;
          case pcode___opendialog: delete (kb_opendialog *) pointer; break;
          case pcode___cmath: delete (kb_cmath *) pointer; break;
          case pcode___imagebutton: delete (kb_imagebutton *) pointer; break;

        }
        delete t2;
        list_gc2.remove(pointer); 
      
      }
      
  }

}

void 		memory_gc::deleteOld2	()
{
  if (first2()){
    do {
      gc2_ *t2 = *it2;

      if (t2 && t2->count == 0){
        deleteOld2(t2->pointer);
        if (!first2()) break;
      }

    } while (next2());
  }  
}

void 		memory_gc::deleteAll2	()
{
  if (first2()){
    do {
      gc2_ *t2 = *it2;
      int n = list_gc2.count();


      if (t2){
        deleteOld2(t2->pointer);
        if (!first2()) break;
      }

    } while (next2()); // iterator ungultig und da alle abgearbeitet werden müssen  first
  }  

  list_gc2.clear();
}

