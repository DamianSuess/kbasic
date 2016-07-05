
#ifndef kb_imagebutton_H
#define kb_imagebutton_H


#include "../kbshared/_imagebutton.h"



#include "../kbrun/interpreter.h"

#define CLASS _imagebutton

extern interpreter *EXTERN_myInterpreter;

class kb_imagebutton : public _imagebutton
{

public:kb_imagebutton(_form *f, QWidget *parent = 0, QString _sName = "") : _imagebutton(f, parent){ 
         sName = _sName; 

         a = sName.toAscii();
         acName = a.data();
         b = sGroup.toAscii();
         acGroup = b.data();         
         
         setInterpreter(EXTERN_myInterpreter); 
         initEvent();
         if (sName.isEmpty()){ my_form_addToCollection(f, this, sName, pcode___imagebutton); SETPROPERTY_Name(sUniqueName); }
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
#include "../kbasic_binding/_imagebutton/interpreter_kbasic_binding_protected.h"

private: 


memory_variable2 *kbScope; int kbId; interpreter *myInterpreter; 

};//------------------------------------------------------------------------------------------------------------------------------------



#endif