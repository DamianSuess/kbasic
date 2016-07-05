
#ifndef kb_savedialog_H
#define kb_savedialog_H


#include "../kbshared/_savedialog.h"


#include "../kbrun/interpreter.h"

#define CLASS _savedialog

extern interpreter *EXTERN_myInterpreter;

class kb_savedialog : public _savedialog
{


public:kb_savedialog() : _savedialog(){ 

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
#include "../kbasic_binding/_savedialog/interpreter_kbasic_binding_protected.h"

private: 

memory_variable2 *kbScope; int kbId; interpreter *myInterpreter; };//------------------------------------------------------------------------------------------------------------------------------------



#endif