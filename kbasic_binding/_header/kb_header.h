
#ifndef kb_header_H
#define kb_header_H

#include "../kbshared/_header.h"



#include "../kbrun/interpreter.h"

#define CLASS _header

extern interpreter *EXTERN_myInterpreter;

class kb_header : public _header
{



public:kb_header(_form *f, QWidget *parent = 0, QString _sName = "") : _header(f, parent){ sName = _sName; setInterpreter(EXTERN_myInterpreter); }


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
#include "../kbasic_binding/_header/interpreter_kbasic_binding_protected.h"

private: 
memory_variable2 *kbScope; int kbId; interpreter *myInterpreter; };//------------------------------------------------------------------------------------------------------------------------------------



#endif