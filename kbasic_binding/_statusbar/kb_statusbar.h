
#ifndef kb_statusbar_H
#define kb_statusbar_H


#include "../kbshared/_statusbar.h"


#include "../kbrun/interpreter.h"

#define CLASS _statusbar

extern _statusbar *EXTERN_my_statusbar;
extern interpreter *EXTERN_myInterpreter;

class kb_statusbar : public _statusbar
{


public:kb_statusbar() : _statusbar(){ 
      
         EXTERN_my_statusbar = this;

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
#include "../kbasic_binding/_statusbar/interpreter_kbasic_binding_protected.h"

private: 

memory_variable2 *kbScope; int kbId; interpreter *myInterpreter; };//------------------------------------------------------------------------------------------------------------------------------------



#endif