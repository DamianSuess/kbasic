
#ifndef kb_toolbar_H
#define kb_toolbar_H


#include "../kbshared/_toolbar.h"


#include "../kbrun/interpreter.h"

#define CLASS _toolbar

extern _toolbar *EXTERN_my_toolbar;
extern interpreter *EXTERN_myInterpreter;

class kb_toolbar : public _toolbar
{


public:kb_toolbar() : _toolbar(){ 
      
         EXTERN_my_toolbar = this;

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
#include "../kbasic_binding/_toolbar/interpreter_kbasic_binding_protected.h"

private: 

memory_variable2 *kbScope; int kbId; interpreter *myInterpreter; };//------------------------------------------------------------------------------------------------------------------------------------



#endif