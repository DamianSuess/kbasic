
#ifndef kb_commandlinkbutton_H
#define kb_commandlinkbutton_H


#include "../kbshared/_commandlinkbutton.h"



#include "../kbrun/interpreter.h"

#define CLASS _commandlinkbutton

extern interpreter *EXTERN_myInterpreter;

class kb_commandlinkbutton : public _commandlinkbutton
{

public:kb_commandlinkbutton(_form *f, QWidget *parent = 0, QString _sName = "") : _commandlinkbutton(f, parent){ 
         sName = _sName; 

         a = sName.toAscii();
         acName = a.data();
         b = sGroup.toAscii();
         acGroup = b.data();         
         
         setInterpreter(EXTERN_myInterpreter); 
         initEvent();
         if (sName.isEmpty()){ my_form_addToCollection(f, this, sName, pcode___commandlinkbutton); SETPROPERTY_Name(sUniqueName); }
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
#include "../kbasic_binding/_commandlinkbutton/interpreter_kbasic_binding_protected.h"

private: 


memory_variable2 *kbScope; int kbId; interpreter *myInterpreter; 

};//------------------------------------------------------------------------------------------------------------------------------------



#endif