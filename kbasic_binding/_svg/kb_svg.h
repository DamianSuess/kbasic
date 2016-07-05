
#ifndef kb_svg_H
#define kb_svg_H


#include "../kbshared/_svg.h"


#include "../kbrun/interpreter.h"

#define CLASS _svg


extern interpreter *EXTERN_myInterpreter;
extern QPainter *EXTERN_myQPainter;

class kb_svg : public _svg
{


public:kb_svg(_form *f, QWidget *parent = 0, QString _sName = "") : _svg(f, parent){ 


         sName = _sName; 

         a = sName.toAscii();
         acName = a.data();
         b = sGroup.toAscii();
         acGroup = b.data();

         setInterpreter(EXTERN_myInterpreter); 
         initEvent();

         if (sName.isEmpty()){ my_form_addToCollection(f, this, sName, pcode___svg); SETPROPERTY_Name(sUniqueName); }


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
#include "../kbasic_binding/_svg/interpreter_kbasic_binding_protected.h"

private: 

memory_variable2 *kbScope; int kbId; interpreter *myInterpreter; };//------------------------------------------------------------------------------------------------------------------------------------



#endif