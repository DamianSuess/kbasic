
#ifdef IDE

void updatePropertyWindow();

void updatePropertyWindow2(bool bb, QString sProperty = "" );

t_properties *p2;


t_properties p;
  

void controls_SETPROPERTY_Name(QString n)
{
  _menubaritem *c;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_Name(n);
        #include "_menubar_property_switch.h"       
      }
    } while (nextControl(&c));
  }


}

void controls_SETPROPERTY_Caption(QString n)
{
  _menubaritem *c;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_Caption(n);
        #include "_menubar_property_switch.h"       

      }
    } while (nextControl(&c));
  }

  buildMenu2(false);

}

// MENUBAR_CONTROL // CONTROL

void controls_SETPROPERTY_ParentIndex(t_integer n)
{
  _menubaritem *c;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_ParentIndex(n);
        #include "_menubar_property_switch.h"                 

      }
    } while (nextControl(&c));
  }

  buildMenu2(false);

}

void controls_SETPROPERTY_Key(QString n)
{
  _menubaritem *c;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_Key(n);
        #include "_menubar_property_switch.h"                 

      }
    } while (nextControl(&c));
  }

  buildMenu2(false);

}

void controls_SETPROPERTY_ParentControl(QString n)
{
  _menubaritem *c;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_ParentControl(n);
        #include "_menubar_property_switch.h"                 

      }
    } while (nextControl(&c));
  }

  buildMenu2(false);

}

void controls_SETPROPERTY_Enabled(t_boolean n)
{
  _menubaritem *c;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_Enabled(n);
        #include "_menubar_property_switch.h"                 

      }
    } while (nextControl(&c));
  }

  buildMenu2(true);

}

void controls_SETPROPERTY_Checked(t_boolean n)
{
  _menubaritem *c;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_Checked(n);
        #include "_menubar_property_switch.h"                 

      }
    } while (nextControl(&c));
  }

  buildMenu2(true);

}

void controls_SETPROPERTY_Checkable(t_boolean n)
{
  _menubaritem *c;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_Checkable(n);
        #include "_menubar_property_switch.h"                 

      }
    } while (nextControl(&c));
  }

  buildMenu2(true);

}

void controls_SETPROPERTY_Tag(QString n)
{
  _menubaritem *c;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_Tag(n);
        #include "_menubar_property_switch.h"                 

      }
    } while (nextControl(&c));
  }

  buildMenu2(false);

}

void controls_SETPROPERTY_Group(QString n)
{
  _menubaritem *c;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_Group(n);
        #include "_menubar_property_switch.h"                 

      }
    } while (nextControl(&c));
  }

  buildMenu2(false);

}

void controls_SETPROPERTY_StatusTip(QString n)
{
  _menubaritem *c;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_StatusTip(n);
        #include "_menubar_property_switch.h"                 

      }
    } while (nextControl(&c));
  }

  buildMenu2(false);

}

void controls_SETPROPERTY_Visible(t_boolean &n)

{
  _menubaritem *c;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_Visible(n);
        #include "_menubar_property_switch.h"                 

      }
    } while (nextControl(&c));
  }


  buildMenu2(true);

}

void controls_SETPROPERTY_BooleanValue(t_boolean n)
{
  _menubaritem *c;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_BooleanValue(n);
        #include "_menubar_property_switch.h"                 

      }
    } while (nextControl(&c));
  }

  buildMenu2(true);

}

void controls_SETPROPERTY_Separator(t_boolean n)
{
  _menubaritem *c;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_Separator(n);
        #include "_menubar_property_switch.h"                 

      }
    } while (nextControl(&c));
  }

  buildMenu2(true);

}

void controls_SETPROPERTY_Icon(QString n)
{
  _menubaritem *c;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_Icon(n);
        #include "_menubar_property_switch.h"                 

      }
    } while (nextControl(&c));
  }

  buildMenu2(false);


}

void controls_SETPROPERTY_MenuBarRole(QString n)
{
  _menubaritem *c;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_MenuBarRole(n);
        #include "_menubar_property_switch.h"                 

      }
    } while (nextControl(&c));
  }

  buildMenu2(false);


}

void controls_SETPROPERTY_Data(QString n)
{
  _menubaritem *c;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_Data(n);
        #include "_menubar_property_switch.h"                 

      }
    } while (nextControl(&c));
  }

  buildMenu2(false);


}

void controls_SETPROPERTY_SoundOnEvent(QString n)
{
  _menubaritem *c;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_SoundOnEvent(n);
        #include "_menubar_property_switch.h"                 

      }
    } while (nextControl(&c));
  }

  buildMenu2(false);


}


void controls_SETPROPERTY_ActionId(QString n)
{
  _menubaritem *c;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_ActionId(n);
        #include "_menubar_property_switch.h"                 

      }
    } while (nextControl(&c));
  }

  buildMenu2(false);


}


// MENUBAR_EVENT

void controls_SETPROPERTY_OnEvent(t_boolean n)
{
  _menubaritem *c;
  // bool b = true;

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_OnEvent(n);
        #include "_menubar_property_switch.h"                 
        //b = false;

      }
    } while (nextControl(&c));
  }

  buildMenu2(true);

}


bool newEvent();


#endif