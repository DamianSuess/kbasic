
#ifndef kb_mainwindow_H
#define kb_mainwindow_H

#include "../kbshared/_mainwindow.h"

#include "../kbrun/interpreter.h"

#define CLASS _mainwindow2

extern interpreter *EXTERN_myInterpreter;
extern memory_variable2 *kbEventScope;
extern int kbEventId;


class kb_mainwindow : public _mainwindow2
{ 


public:kb_mainwindow() : _mainwindow2(){
                
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
#include "../kbasic_binding/_mainwindow/interpreter_kbasic_binding_protected.h"


private: memory_variable2 *kbScope; int kbId; interpreter *myInterpreter; 


};//------------------------------------------------------------------------------------------------------------------------------------


#endif