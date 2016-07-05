
#ifndef kb_sound_H
#define kb_sound_H


#include "../kbshared/_sound.h"


#include "../kbrun/interpreter.h"

#define CLASS _sound


extern interpreter *EXTERN_myInterpreter;

class kb_sound : public _sound
{
#ifdef MAC // HIDE
  Q_OBJECT // HIDE
#endif // HIDE

public:kb_sound(_form *f, QWidget *parent = 0, QString _sName = "") : _sound(f, parent){ 
         sName = _sName; 

         a = sName.toAscii();
         acName = a.data();
         b = sGroup.toAscii();
         acGroup = b.data();

         setInterpreter(EXTERN_myInterpreter); 
         initEvent();
         if (sName.isEmpty()){ my_form_addToCollection(f, this, sName, pcode___sound); SETPROPERTY_Name(sUniqueName); }

         
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
#include "../kbasic_binding/_sound/interpreter_kbasic_binding_protected.h"

private: 

memory_variable2 *kbScope; int kbId; interpreter *myInterpreter; };//------------------------------------------------------------------------------------------------------------------------------------



#endif