
#ifndef kb_table_H
#define kb_table_H


#include "../kbshared/_table2.h"


#include "../kbrun/interpreter.h"

#define CLASS _table2

extern interpreter *EXTERN_myInterpreter;

class kb_table2 : public _table2
{


public:kb_table2() : _table2(){ 

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
#include "../kbasic_binding/_table/interpreter_kbasic_binding_protected.h"

private: 

memory_variable2 *kbScope; int kbId; interpreter *myInterpreter; };//------------------------------------------------------------------------------------------------------------------------------------



#endif