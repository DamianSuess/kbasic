

#ifdef SWITCH4
switch(ct){
#else
switch(controlType(c)){
#endif

#define CONTROLTYPE t_tableitem
#define SUPERCLASS _tableitem
#define CONTROLLIST tableitems
#include "_table_property_switch2.h"  


}

#undef SWITCH2

