
#ifndef kb_inputdialog_H
#define kb_inputdialog_H


#include "../kbshared/_inputdialog.h"


#include "../kbrun/interpreter.h"

#define CLASS _inputdialog

extern interpreter *EXTERN_myInterpreter;

class kb_inputdialog : public _inputdialog
{


public:kb_inputdialog() : _inputdialog(){ 

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
#include "../kbasic_binding/_inputdialog/interpreter_kbasic_binding_protected.h"

private: 

memory_variable2 *kbScope; int kbId; interpreter *myInterpreter; };//------------------------------------------------------------------------------------------------------------------------------------



#endif