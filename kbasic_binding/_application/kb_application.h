
#ifndef kb_application_H
#define kb_application_H

#include "../kbshared/_application.h"

#include "../kbrun/interpreter.h"

#define CLASS _application

extern interpreter *EXTERN_myInterpreter;
extern memory_variable2 *kbEventScope;
extern int kbEventId;

extern int nEVENT_Actions_OnAction;
extern int nEVENT_Forms_OnFormGotFocus;

extern int nEVENT_MenuBar_OnEvent;
extern int nEVENT_MenuBar_OnHovered;
extern int nEVENT_MenuBar_OnAboutToShow;
extern int nEVENT_MenuBar_OnAboutToHide;
extern int nEVENT_ToolBar_OnEvent;
extern int nEVENT_SystemTray_OnEvent;



class kb_application : public _application
{ 


public:kb_application() : _application(){
                
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
#include "../kbasic_binding/_application/interpreter_kbasic_binding_protected.h"


private: memory_variable2 *kbScope; int kbId; interpreter *myInterpreter; 


};//------------------------------------------------------------------------------------------------------------------------------------


#endif