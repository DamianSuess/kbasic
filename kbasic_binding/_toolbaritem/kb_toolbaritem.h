
#ifndef kb_toolbaritem_H
#define kb_toolbaritem_H


#include "../kbshared/_toolbaritem.h"


#include "../kbrun/interpreter.h"

#define CLASS _toolbaritem


extern interpreter *EXTERN_myInterpreter;

class kb_toolbaritem : public _toolbaritem
{


public:kb_toolbaritem(int _nIndex, QString _sName = "") : _toolbaritem(_nIndex){ 
         sName = _sName; 

         a = sName.toAscii();
         acName = a.data();

         acGroup = "";


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
#include "../kbasic_binding/_toolbaritem/interpreter_kbasic_binding_protected.h"

private: 

memory_variable2 *kbScope; int kbId; interpreter *myInterpreter; };//------------------------------------------------------------------------------------------------------------------------------------



#endif