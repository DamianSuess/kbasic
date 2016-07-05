
#ifndef kb_browser_H
#define kb_browser_H


#include "../kbshared/_browser.h"


#include "../kbrun/interpreter.h"

#define CLASS _browser


extern interpreter *EXTERN_myInterpreter;

class kb_browser : public _browser
{


public:kb_browser(_form *f, QWidget *parent = 0, QString _sName = "") : _browser(f, parent){ 
         sName = _sName; 

         a = sName.toAscii();
         acName = a.data();
         b = sGroup.toAscii();
         acGroup = b.data();

         setInterpreter(EXTERN_myInterpreter); 
         initEvent();
         if (sName.isEmpty()){ my_form_addToCollection(f, this, sName, pcode___browser); SETPROPERTY_Name(sUniqueName); }

         
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
#include "../kbasic_binding/_browser/interpreter_kbasic_binding_protected.h"

private: 
//QString sName;
memory_variable2 *kbScope; int kbId; interpreter *myInterpreter; };//------------------------------------------------------------------------------------------------------------------------------------



#endif