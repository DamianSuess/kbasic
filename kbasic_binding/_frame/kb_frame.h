
#ifndef kb_frame_H
#define kb_frame_H


#include "../kbshared/_frame.h"


#include "../kbrun/interpreter.h"

#define CLASS _frame

extern interpreter *EXTERN_myInterpreter;
extern interpreter **EXTERN_myInterpreter2;

class kb_frame : public _frame
{

public:kb_frame(_form *f, QWidget *parent = 0, QString _sName = "") : _frame(f, parent){

         a = sName.toAscii();
         acName = a.data();
         b = sGroup.toAscii();
         acGroup = b.data();

         setInterpreter(EXTERN_myInterpreter);
         initEvent();
         if (sName.isEmpty()){ my_form_addToCollection(f, this, sName, pcode___frame); SETPROPERTY_Name(sUniqueName); }

         EXTERN_myInterpreter2 = &myInterpreter;

         
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
#include "../kbasic_binding/_frame/interpreter_kbasic_binding_protected.h"

private:


memory_variable2 *kbScope; int kbId; interpreter *myInterpreter; 

};//------------------------------------------------------------------------------------------------------------------------------------



#endif