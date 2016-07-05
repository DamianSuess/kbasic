
#ifndef kb_control_H
#define kb_control_H


#include "../kbshared/_control.h"


#include "../kbrun/interpreter.h"

#define CLASS _control


extern interpreter *EXTERN_myInterpreter;


class kb_control : public _control
{


public:kb_control(_form *f, QWidget *parent = 0, QString _sName = "") : _control(f, parent){ 

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
#include "../kbasic_binding/_control/interpreter_kbasic_binding_protected.h"

private: 

memory_variable2 *kbScope; int kbId; interpreter *myInterpreter; };//------------------------------------------------------------------------------------------------------------------------------------



#endif