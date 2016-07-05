

#if defined(SWITCH_STATIC)
switch(static_controlType(c)){
#elif defined(SWITCH4)
switch(ct){
#else
switch(controlType(c)){
#endif

#define CONTROLTYPE t_menu
#define SUPERCLASS _menubaritem
#define CONTROLLIST menubaritems
#include "_menubar_property_switch2.h"
  
#define CONTROLTYPE t_submenu
#define SUPERCLASS _menubaritem
#define CONTROLLIST menubaritems
#include "_menubar_property_switch2.h"

#define CONTROLTYPE t_menubaritem
#define SUPERCLASS _menubaritem
#define CONTROLLIST menubaritems
#include "_menubar_property_switch2.h"


}

#undef SWITCH2

