
#ifndef kb_forms_H
#define kb_forms_H


#include "../kbshared/_forms.h"

#include "../kbrun/interpreter.h"

#define CLASS _forms

extern interpreter *EXTERN_myInterpreter;

class kb_forms : public _forms
{

public:kb_forms() : _forms(){ 
         setInterpreter(EXTERN_myInterpreter); 
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
#include "../kbasic_binding/_forms/interpreter_kbasic_binding_protected.h"

interpreter *myInterpreter;

private: 


memory_variable2 *kbScope; int kbId; 

 };//------------------------------------------------------------------------------------------------------------------------------------


#endif