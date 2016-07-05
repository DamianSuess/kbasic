
#ifndef kb_line_H
#define kb_line_H


#include "../kbshared/_line.h"


#include "../kbrun/interpreter.h"

#define CLASS _line

extern interpreter *EXTERN_myInterpreter;
extern interpreter **EXTERN_myInterpreter2;

class kb_line : public _line
{

public:kb_line(_form *f, QWidget *parent = 0, QString _sName = "") : _line(f, parent){

         a = sName.toAscii();
         acName = a.data();
         b = sGroup.toAscii();
         acGroup = b.data();

         setInterpreter(EXTERN_myInterpreter); 
         initEvent();
         if (sName.isEmpty()){ my_form_addToCollection(f, this, sName, pcode___line); SETPROPERTY_Name(sUniqueName); }

         EXTERN_myInterpreter2 = &myInterpreter;

         
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
#include "../kbasic_binding/_line/interpreter_kbasic_binding_protected.h"

private:


memory_variable2 *kbScope; int kbId; interpreter *myInterpreter; 

};//------------------------------------------------------------------------------------------------------------------------------------



#endif