
#ifndef kb_udpsocket_H
#define kb_udpsocket_H


#include "../kbshared/_udpsocket.h"


#include "../kbrun/interpreter.h"

#define CLASS _udpsocket


extern interpreter *EXTERN_myInterpreter;

class kb_udpsocket : public _udpsocket
{


public:kb_udpsocket(_form *f, QWidget *parent = 0, QString _sName = "") : _udpsocket(f, parent){ 

         sName = _sName; 

         a = sName.toAscii();
         acName = a.data();
         b = sGroup.toAscii();
         acGroup = b.data();

         setInterpreter(EXTERN_myInterpreter); 
         initEvent();
         if (sName.isEmpty()){ my_form_addToCollection(f, this, sName, pcode___udpsocket); SETPROPERTY_Name(sUniqueName); }

         
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
#include "../kbasic_binding/_udpsocket/interpreter_kbasic_binding_protected.h"

private: 
QString sName;
QString sGroup;

const char *acName;
const char *acGroup;
QByteArray a;
QByteArray b;

memory_variable2 *kbScope; int kbId; interpreter *myInterpreter; };//------------------------------------------------------------------------------------------------------------------------------------



#endif