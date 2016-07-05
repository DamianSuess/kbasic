
#ifndef kb_query_H
#define kb_query_H


#include "../kbshared/_query.h"


#include "../kbrun/interpreter.h"

#define CLASS _query

extern interpreter *EXTERN_myInterpreter;

class kb_query : public _query
{


public:kb_query() : _query(){ 

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
#include "../kbasic_binding/_query/interpreter_kbasic_binding_protected.h"

private: 

memory_variable2 *kbScope; int kbId; interpreter *myInterpreter; };//------------------------------------------------------------------------------------------------------------------------------------



#endif