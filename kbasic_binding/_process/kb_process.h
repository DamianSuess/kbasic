
#ifndef kb_process_H
#define kb_process_H


#include "../kbshared/_process.h"


#include "../kbrun/interpreter.h"

#define CLASS _process


extern interpreter *EXTERN_myInterpreter;

class kb_process : public _process
{


public:kb_process() : _process(){ 
      
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
#include "../kbasic_binding/_log/interpreter_kbasic_binding_protected.h"

private: 

memory_variable2 *kbScope; int kbId; interpreter *myInterpreter; };//------------------------------------------------------------------------------------------------------------------------------------



#endif