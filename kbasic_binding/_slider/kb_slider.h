
#ifndef kb_slider_H
#define kb_slider_H


#include "../kbshared/_slider.h"


#include "../kbrun/interpreter.h"

#define CLASS _slider

extern interpreter *EXTERN_myInterpreter;

class kb_slider : public _slider
{

public:kb_slider(_form *f, QWidget *parent = 0, QString _sName = "") : _slider(f, parent){ 
         sName = _sName; 

         a = sName.toAscii();
         acName = a.data();
         b = sGroup.toAscii();
         acGroup = b.data();

         setInterpreter(EXTERN_myInterpreter); 
         initEvent();

         if (sName.isEmpty()){ my_form_addToCollection(f, this, sName, pcode___slider); SETPROPERTY_Name(sUniqueName); }

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
#include "../kbasic_binding/_slider/interpreter_kbasic_binding_protected.h"

private: 


memory_variable2 *kbScope; int kbId; interpreter *myInterpreter;

};//------------------------------------------------------------------------------------------------------------------------------------



#endif