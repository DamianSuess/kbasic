
#ifdef IDE

void updatePropertyWindow();

void updatePropertyWindow2(bool bb, QString sProperty = "" );

t_properties *p2;


t_properties p;
  


void controls_SETPROPERTY_Null(t_boolean n)
{
  _tableitem *c;
  

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_Null(n);
        #include "_table_property_switch.h"                 
        

      }
    } while (nextControl(&c));
  }

  bIsModified = true;

 

}


void controls_SETPROPERTY_Index(t_boolean n)
{
  _tableitem *c;
  

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_Index(n);
        #include "_table_property_switch.h"                 
        

      }
    } while (nextControl(&c));
  }

  bIsModified = true;

}



#endif