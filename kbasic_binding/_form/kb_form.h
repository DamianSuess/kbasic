
#ifndef kb_form_H
#define kb_form_H


#include "../kbshared/_form.h"

#include "../kbrun/interpreter.h"

#define CLASS _form

extern interpreter *EXTERN_myInterpreter;
class kb_form;
extern kb_form *FORMPARENT;


class kb_form : public _form
{
#ifndef WINDOWS
  Q_OBJECT
#endif
public:kb_form() : _form(EXTERN_my_mainwindow /*EXTERN_my_mainwindow->ws*/){ 

         ParentForm = FORMPARENT;

         setInterpreter(EXTERN_myInterpreter); 
         
         initEvent();

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
#include "../kbasic_binding/_form/interpreter_kbasic_binding_protected.h"

public: 


memory_variable2 *kbScope; int kbId; 

 };//------------------------------------------------------------------------------------------------------------------------------------


#endif