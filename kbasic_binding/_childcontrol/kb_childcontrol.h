
#ifndef kb_childcontrol_H
#define kb_childcontrol_H


#include "../kbshared/_childcontrol.h"


#include "../kbrun/interpreter.h"

#define CLASS _childcontrol

extern interpreter *EXTERN_myInterpreter;

class kb_childcontrol : public _childcontrol
{


public:kb_childcontrol(_form *f, QWidget *parent = 0, QString _sName = "") : _childcontrol(f, parent){ 
         sName = _sName; 

         a = sName.toAscii();
         acName = a.data();
         b = sGroup.toAscii();
         acGroup = b.data();

         setInterpreter(EXTERN_myInterpreter); 
         initEvent();
         if (sName.isEmpty()){ my_form_addToCollection(f, this, sName, pcode___checkbox); SETPROPERTY_Name(sUniqueName); }

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
#include "../kbasic_binding/_childcontrol/interpreter_kbasic_binding_protected.h"

private: 
memory_variable2 *kbScope; int kbId; interpreter *myInterpreter; };//------------------------------------------------------------------------------------------------------------------------------------



#endif