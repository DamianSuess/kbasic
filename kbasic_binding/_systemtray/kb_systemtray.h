
#ifndef kb_systemtray_H
#define kb_systemtray_H


#include "../kbshared/_systemtray.h"


#include "../kbrun/interpreter.h"

#define CLASS _systemtray

extern interpreter *EXTERN_myInterpreter;

class kb_systemtray : public _systemtray
{


public:kb_systemtray() : _systemtray(){ 
      

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
#include "../kbasic_binding/_systemtray/interpreter_kbasic_binding_protected.h"

private: 

memory_variable2 *kbScope; int kbId; interpreter *myInterpreter; };//------------------------------------------------------------------------------------------------------------------------------------



#endif