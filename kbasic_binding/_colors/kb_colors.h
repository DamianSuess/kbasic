
#ifndef kb_colors_H
#define kb_colors_H


#include "../kbshared/_colors.h"


#include "../kbrun/interpreter.h"

#define CLASS _colors

extern interpreter *EXTERN_myInterpreter;

class kb_colors : public _colors
{


public:kb_colors() : _colors(){ 

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
#include "../kbasic_binding/_colors/interpreter_kbasic_binding_protected.h"

private: 

memory_variable2 *kbScope; int kbId; interpreter *myInterpreter; };//------------------------------------------------------------------------------------------------------------------------------------



#endif