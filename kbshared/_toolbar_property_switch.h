

#if defined(SWITCH_STATIC)
switch(static_controlType(c)){
#elif defined(SWITCH4)
switch(ct){
#else
switch(controlType(c)){
#endif

#define CONTROLTYPE t_toolbaritem
#define SUPERCLASS _toolbaritem
#define CONTROLLIST toolbaritems
#include "_toolbar_property_switch2.h"  


}

#undef SWITCH2

