
#ifndef kb_fontdialog_H
#define kb_fontdialog_H


#include "../kbshared/_fontdialog.h"


#include "../kbrun/interpreter.h"

#define CLASS _fontdialog

extern interpreter *EXTERN_myInterpreter;

class kb_fontdialog : public _fontdialog
{


public:kb_fontdialog() : _fontdialog(){ 

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
#include "../kbasic_binding/_fontdialog/interpreter_kbasic_binding_protected.h"

private: 

memory_variable2 *kbScope; int kbId; interpreter *myInterpreter; };//------------------------------------------------------------------------------------------------------------------------------------



#endif