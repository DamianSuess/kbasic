
#ifndef kb_formsview_H
#define kb_formsview_H


#include "../kbshared/_formsview.h"


#include "../kbrun/interpreter.h"

#define CLASS _formsview

extern interpreter *EXTERN_myInterpreter;

class kb_formsview : public _formsview
{
#ifndef WINDOWS
  Q_OBJECT
#endif

public:kb_formsview(_form *f, QWidget *parent = 0, QString _sName = "") : _formsview(f, parent){ 
         sName = _sName; 

         a = sName.toAscii();
         acName = a.data();
         b = sGroup.toAscii();
         acGroup = b.data();

         setInterpreter(EXTERN_myInterpreter); 
         initEvent();
         if (sName.isEmpty()){ my_form_addToCollection(f, this, sName, pcode___checkbox); SETPROPERTY_Name(sUniqueName); }

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
#include "../kbasic_binding/_formsview/interpreter_kbasic_binding_protected.h"

private: 
memory_variable2 *kbScope; int kbId; interpreter *myInterpreter; };//------------------------------------------------------------------------------------------------------------------------------------



#endif