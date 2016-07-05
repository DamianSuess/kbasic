
#ifndef kb_label_H
#define kb_label_H



#include "../kbshared/_label.h"


#include "../kbrun/interpreter.h"

#define CLASS _label

//extern _mainwindow *EXTERN_my_mainwindow;
extern interpreter *EXTERN_myInterpreter;

class kb_label : public _label
{

public:
kb_label(_form *f, QWidget *parent = 0, QString _sName = "") : _label(f, parent){ 

         sName = _sName; 

         a = sName.toAscii();
         acName = a.data();
         b = sGroup.toAscii();
         acGroup = b.data();     
           
  setInterpreter(EXTERN_myInterpreter); 
  initEvent();
  if (sName.isEmpty()){ my_form_addToCollection(f, this, sName, pcode___label); SETPROPERTY_Name(sUniqueName); }

  
}

public:
#include "../kbasic_binding/_label/interpreter_kbasic_binding_protected.h"


public: 
// set event handling related information, in which object to search for event methods for this object
void setKbId(memory_variable2 *sc, int n) 
{ 
  if (sc == 0 || kbScope == 0){ 
    kbScope = sc; kbId = n; 
  }
} 

void setInterpreter(interpreter *i){ setKbId(0, 0); myInterpreter = i;}



private: 
  /*
QString sName;
QString sGroup;
const char *acName;
const char *acGroup;
QByteArray a;
QByteArray b;
*/
memory_variable2 *kbScope; int kbId; interpreter *myInterpreter;

};//------------------------------------------------------------------------------------------------------------------------------------


#endif