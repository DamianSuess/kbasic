
#ifndef kb_menubar_H
#define kb_menubar_H


#include "../kbshared/_menubar.h"


#include "../kbrun/interpreter.h"

#define CLASS _menubar

extern _menubar *EXTERN_my_menubar;
extern interpreter *EXTERN_myInterpreter;

class kb_menubar : public _menubar
{


public:
  
  kb_menubar() : _menubar(){ 
      
         EXTERN_my_menubar = this;

         acName = "";
         acGroup = "";

         setInterpreter(EXTERN_myInterpreter); 
       }

  kb_menubar(_form *f) : _menubar(f){ 
      
         EXTERN_my_menubar = this;

         acName = "";
         acGroup = "";

         setInterpreter(EXTERN_myInterpreter); 
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

       
void callCustomEvent(const char *acName)
{  

	QList<int> *param = new QList<int>;
	if (myInterpreter && myInterpreter->hasEvent(kbScope, kbId, "OnEvent", acGroup, acName, param)){
		myInterpreter->callEvent(kbScope, kbId, "OnEvent", acGroup, acName, param);
		delete param; return;
	}
	delete param;
}

public:
#include "../kbasic_binding/_menubar/interpreter_kbasic_binding_protected.h"

private: 

memory_variable2 *kbScope; int kbId; interpreter *myInterpreter; };//------------------------------------------------------------------------------------------------------------------------------------



#endif