
#ifndef kb_event_H
#define kb_event_H


#include "../kbshared/_event.h"


#include "../kbrun/interpreter.h"

#define CLASS _event


extern interpreter *EXTERN_myInterpreter;
extern QPainter *EXTERN_myQPainter;

class kb_event : public _event
{


public:kb_event(QString _sName = "") : _event(){ 

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
#include "../kbasic_binding/_event/interpreter_kbasic_binding_protected.h"

private: 

memory_variable2 *kbScope; int kbId; interpreter *myInterpreter; };//------------------------------------------------------------------------------------------------------------------------------------



#endif