
#ifndef kb_fonts_H
#define kb_fonts_H


#include "../kbshared/_fonts.h"


#include "../kbrun/interpreter.h"

#define CLASS _fonts

extern interpreter *EXTERN_myInterpreter;

class kb_fonts : public _fonts
{


public:kb_fonts() : _fonts(){ 

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
#include "../kbasic_binding/_fonts/interpreter_kbasic_binding_protected.h"

private: 

memory_variable2 *kbScope; int kbId; interpreter *myInterpreter; };//------------------------------------------------------------------------------------------------------------------------------------



#endif