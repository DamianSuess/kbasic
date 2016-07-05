
#ifndef kb_preferences_H
#define kb_preferences_H

#include "../kbshared/_preferences.h"

#include "../kbrun/interpreter.h"

#define CLASS _preferences

extern interpreter *EXTERN_myInterpreter;




class kb_preferences : public _preferences
{ 


public:kb_preferences() : _preferences(){
                
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
#include "../kbasic_binding/_preferences/interpreter_kbasic_binding_protected.h"


private: memory_variable2 *kbScope; int kbId; interpreter *myInterpreter; 


};//------------------------------------------------------------------------------------------------------------------------------------


#endif