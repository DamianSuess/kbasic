
#ifndef kb_record_H
#define kb_record_H


#include "../kbshared/_record.h"


#include "../kbrun/interpreter.h"

#define CLASS _record

extern interpreter *EXTERN_myInterpreter;

class kb_record : public _record
{


public:kb_record() : _record(){ 

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
#include "../kbasic_binding/_record/interpreter_kbasic_binding_protected.h"

private: 

memory_variable2 *kbScope; int kbId; interpreter *myInterpreter; };//------------------------------------------------------------------------------------------------------------------------------------



#endif