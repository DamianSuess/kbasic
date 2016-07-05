
#ifndef kb_image_H
#define kb_image_H


#include "../kbshared/_image.h"


#include "../kbrun/interpreter.h"

#define CLASS _image

//extern _mainwindow *EXTERN_my_mainwindow;
extern interpreter *EXTERN_myInterpreter;

class kb_image : public _image
{


public:kb_image(_form *f, QWidget *parent = 0, QString _sName = "") : _image(f, parent){ 
         sName = _sName; 

         a = sName.toAscii();
         acName = a.data();
         b = sGroup.toAscii();
         acGroup = b.data();

         setInterpreter(EXTERN_myInterpreter); 
         initEvent();
         if (sName.isEmpty()){ my_form_addToCollection(f, this, sName, pcode___image); SETPROPERTY_Name(sUniqueName); }

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
#include "../kbasic_binding/_image/interpreter_kbasic_binding_protected.h"

private: 
//QString sName;
memory_variable2 *kbScope; int kbId; interpreter *myInterpreter; };//------------------------------------------------------------------------------------------------------------------------------------



#endif