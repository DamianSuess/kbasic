
#ifdef IDE

void updatePropertyWindow();

void updatePropertyWindow2(bool bb, QString sProperty = "" );

t_properties *p2;
//void showUpdatePropertyWindow(bool b = true);


t_properties p;
  
//void updatePropertyWindow2(bool b = true, QString sProperty = "");
//void updatePropertyWindow(bool b = true);



void controls_SETPROPERTY_Null(t_boolean n)
{
  _tableitem *c;
  // bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_Null(n);
        #include "_table_property_switch.h"                 
        //b = false;

      }
    } while (nextControl(&c));
  }

  bIsModified = true;

 //  build();

}


void controls_SETPROPERTY_Index(t_boolean n)
{
  _tableitem *c;
  // bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_Index(n);
        #include "_table_property_switch.h"                 
        //b = false;

      }
    } while (nextControl(&c));
  }

  bIsModified = true;

 //  build();

}



#endif