
#ifndef kb_sounds_H
#define kb_sounds_H


#include "../kbshared/_sounds.h"


#include "../kbrun/interpreter.h"

#define CLASS _sounds

extern interpreter *EXTERN_myInterpreter;

class kb_sounds : public _sounds
{


public:kb_sounds() : _sounds(){ 

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
#include "../kbasic_binding/_sounds/interpreter_kbasic_binding_protected.h"

private: 

memory_variable2 *kbScope; int kbId; interpreter *myInterpreter; };//------------------------------------------------------------------------------------------------------------------------------------



#endif