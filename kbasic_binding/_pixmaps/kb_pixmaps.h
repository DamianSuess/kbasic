
#ifndef kb_pixmaps_H
#define kb_pixmaps_H


#include "../kbshared/_pixmaps.h"


#include "../kbrun/interpreter.h"

#define CLASS _pixmaps

extern interpreter *EXTERN_myInterpreter;

class kb_pixmaps : public _pixmaps
{


public:kb_pixmaps() : _pixmaps(){ 

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
#include "../kbasic_binding/_pixmaps/interpreter_kbasic_binding_protected.h"

private: 

memory_variable2 *kbScope; int kbId; interpreter *myInterpreter; };//------------------------------------------------------------------------------------------------------------------------------------



#endif