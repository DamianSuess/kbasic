
#ifndef kb_menubaritem_H
#define kb_menubaritem_H


#include "../kbshared/_menubaritem.h"


#include "../kbrun/interpreter.h"

#define CLASS _menubaritem

extern interpreter *EXTERN_myInterpreter;

class kb_menubaritem : public _menubaritem
{


public:
  
  kb_menubaritem(_qmenu *_my_qmenu, _menubaritem *_parent, 
          int _nIndex, QString _sName = "") : _menubaritem(_my_qmenu, _parent, 
          _nIndex){ 
         sName = _sName; 

         a = sName.toAscii();
         acName = a.data();

         acGroup = "";

         setInterpreter(EXTERN_myInterpreter); 
         initEvent();
       }

kb_menubaritem(_form *f) : _menubaritem(f){ 
 
         acName = "";
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
#include "../kbasic_binding/_menubaritem/interpreter_kbasic_binding_protected.h"

private: 

memory_variable2 *kbScope; int kbId; interpreter *myInterpreter; };//------------------------------------------------------------------------------------------------------------------------------------



#endif