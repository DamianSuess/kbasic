
#ifndef kb_color_H
#define kb_color_H


#include "../kbshared/_color.h"


#include "../kbrun/interpreter.h"

#define CLASS _color

//extern _mainwindow *EXTERN_my_mainwindow;
extern interpreter *EXTERN_myInterpreter;

class kb_color : public _color
{


public:kb_color() : _color(){ 

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
#include "../kbasic_binding/_color/interpreter_kbasic_binding_protected.h"

private: 

memory_variable2 *kbScope; int kbId; interpreter *myInterpreter; };//------------------------------------------------------------------------------------------------------------------------------------



#endif