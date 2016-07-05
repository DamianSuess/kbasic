
#ifndef kb_dir_H
#define kb_dir_H


#include "../kbshared/_dir.h"


#include "../kbrun/interpreter.h"

#define CLASS _dir


extern interpreter *EXTERN_myInterpreter;

class kb_dir : public _dir
{


public:kb_dir() : _dir(){ 

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
#include "../kbasic_binding/_dir/interpreter_kbasic_binding_protected.h"

private: 

memory_variable2 *kbScope; int kbId; interpreter *myInterpreter; };//------------------------------------------------------------------------------------------------------------------------------------



#endif