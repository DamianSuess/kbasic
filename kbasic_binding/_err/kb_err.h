
#ifndef kberr_H
#define kberr_H

#include "../kbshared/_err.h"

#include "../kbrun/interpreter.h"




#define CLASS _err


extern interpreter *EXTERN_myInterpreter;

class kb_err : public _err
{ 


public:
  kb_err() : _err(){  setInterpreter(EXTERN_myInterpreter);  }


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
#include "../kbasic_binding/_err/interpreter_kbasic_binding_protected.h"

private: 
memory_variable2 *kbScope; int kbId;  interpreter *myInterpreter;  };//------------------------------------------------------------------------------------------------------------------------------------



#endif