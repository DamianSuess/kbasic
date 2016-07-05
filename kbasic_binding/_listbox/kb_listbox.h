
#ifndef kb_listbox_H
#define kb_listbox_H



#include "../kbshared/_listbox.h"



#include "../kbrun/interpreter.h"

#define CLASS _listbox

extern interpreter *EXTERN_myInterpreter;

class kb_listbox : public _listbox
{


public:kb_listbox(_form *f, QWidget *parent = 0, QString _sName = "") : _listbox(f, parent){ 
         sName = _sName; 

         a = sName.toAscii();
         acName = a.data();
         b = sGroup.toAscii();
         acGroup = b.data();

         setInterpreter(EXTERN_myInterpreter); 
         initEvent();
         if (sName.isEmpty()){ my_form_addToCollection(f, this, sName, pcode___listbox); SETPROPERTY_Name(sUniqueName); }

         
}


public: 
// set event handling related information, in which object to search for event methods for this object
void setKbId(memory_variable2 *sc, int n) 
{ 
  if (sc == 0 || kbScope == 0){ 
    kbScope = sc; kbId = n; 
  }
} 

void setInterpreter(interpreter *i){ setKbId(0, 0); myInterpreter = i;}



public:
#include "../kbasic_binding/_listbox/interpreter_kbasic_binding_protected.h"

private: 
memory_variable2 *kbScope; int kbId; interpreter *myInterpreter; 

};//------------------------------------------------------------------------------------------------------------------------------------



#endif