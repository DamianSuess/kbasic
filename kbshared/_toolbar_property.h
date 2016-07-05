
#ifdef IDE

void updatePropertyWindow();

void updatePropertyWindow2(bool bb, QString sProperty = "" );

t_properties *p2;


t_properties p;
  

void controls_SETPROPERTY_Name(QString n)
{
  _toolbaritem *c;
  

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_Name(n);
        #include "_toolbar_property_switch.h"       
        
      }
    } while (nextControl(&c));
  }


}

void controls_SETPROPERTY_Caption(QString n)
{
  _toolbaritem *c;
  

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_Caption(n);
        #include "_toolbar_property_switch.h"       
        

      }
    } while (nextControl(&c));
  }

  

}

// TOOLBAR_CONTROL // CONTROL

void controls_SETPROPERTY_ParentIndex(t_integer n)
{
  _toolbaritem *c;
  

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_ParentIndex(n);
        #include "_toolbar_property_switch.h"                 
        

      }
    } while (nextControl(&c));
  }

  build();

}

void controls_SETPROPERTY_ArrowType(QString n)
{
  _toolbaritem *c;
  

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_ArrowType(n);
        #include "_toolbar_property_switch.h"                 
        

      }
    } while (nextControl(&c));
  }

  

}

void controls_SETPROPERTY_PopupMode(QString n)
{
  _toolbaritem *c;
  

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_PopupMode(n);
        #include "_toolbar_property_switch.h"                 
        

      }
    } while (nextControl(&c));
  }

  

}

void controls_SETPROPERTY_ToolBarRole(QString n)
{
  _toolbaritem *c;
  

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_ToolBarRole(n);
        #include "_toolbar_property_switch.h"                 
        

      }
    } while (nextControl(&c));
  }

  

}

void controls_SETPROPERTY_WhatsThis(QString n)
{
  _toolbaritem *c;
  

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_WhatsThis(n);
        #include "_toolbar_property_switch.h"                 
        

      }
    } while (nextControl(&c));
  }

  

}

void controls_SETPROPERTY_SoundOnEvent(QString n)
{
  _toolbaritem *c;
  

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_SoundOnEvent(n);
        #include "_toolbar_property_switch.h"                 
        

      }
    } while (nextControl(&c));
  }

  

}

void controls_SETPROPERTY_ActionId(QString n)
{
  _toolbaritem *c;
  

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_ActionId(n);
        #include "_toolbar_property_switch.h"                 
        

      }
    } while (nextControl(&c));
  }

  

}

void controls_SETPROPERTY_Enabled(t_boolean n)
{
  _toolbaritem *c;
  

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_Enabled(n);
        #include "_toolbar_property_switch.h"                 
        

      }
    } while (nextControl(&c));
  }

  

}

void controls_SETPROPERTY_Group(QString n)
{
  _toolbaritem *c;
  

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_Group(n);
        #include "_toolbar_property_switch.h"                 
        

      }
    } while (nextControl(&c));
  }

  

}

void controls_SETPROPERTY_Tag(QString n)
{
  _toolbaritem *c;
  

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_Tag(n);
        #include "_toolbar_property_switch.h"                 
        

      }
    } while (nextControl(&c));
  }

  

}

void controls_SETPROPERTY_StatusTip(QString n)
{
  _toolbaritem *c;
  

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_StatusTip(n);
        #include "_toolbar_property_switch.h"                 
        

      }
    } while (nextControl(&c));
  }

  

}

void controls_SETPROPERTY_ToolTip(QString n)
{
  _toolbaritem *c;
  

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_ToolTip(n);
        #include "_toolbar_property_switch.h"                 
        

      }
    } while (nextControl(&c));
  }

  

}
void controls_SETPROPERTY_ContextMenu(QString n)
{
  _toolbaritem *c;
  

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_ContextMenu(n);
        #include "_toolbar_property_switch.h"                 
        

      }
    } while (nextControl(&c));
  }

  

}

void controls_SETPROPERTY_Checkable(t_boolean n)
{
  _toolbaritem *c;
  

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_Checkable(n);
        #include "_toolbar_property_switch.h"                 
        

      }
    } while (nextControl(&c));
  }

  

}
void controls_SETPROPERTY_Checked(t_boolean n)
{
  _toolbaritem *c;
  

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_Checked(n);
        #include "_toolbar_property_switch.h"                 
        

      }
    } while (nextControl(&c));
  }

  

}
void controls_SETPROPERTY_Visible(t_boolean n)
{
  _toolbaritem *c;
  

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_Visible(n);
        #include "_toolbar_property_switch.h"                 
        

      }
    } while (nextControl(&c));
  }

  build();

}

void controls_SETPROPERTY_Separator(t_boolean n)
{
  _toolbaritem *c;
  

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_Separator(n);
        #include "_toolbar_property_switch.h"                 
        

      }
    } while (nextControl(&c));
  }

  build();

}

void controls_SETPROPERTY_Icon(QString n)
{
  _toolbaritem *c;
  

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_Icon(n);
        #include "_toolbar_property_switch.h"                 
        

      }
    } while (nextControl(&c));
  }

  if (n.contains(".")) build();

}


// TOOLBAR_EVENT

void controls_SETPROPERTY_OnEvent(t_boolean n)
{
  _toolbaritem *c;
  

  if (firstControl(&c)){
    do {

      if (c->acceptDrops()){ // missused as selected flag

        #define SWITCH SETPROPERTY_OnEvent(n);
        #include "_toolbar_property_switch.h"                 
        

      }
    } while (nextControl(&c));
  }

  

}


bool newEvent();


#endif