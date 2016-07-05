/*
***************************************************************************
Copyright (C) 2000-2007 KBasic Software: www.kbasic.com. All rights reserved.
Source codes are copyrighted by Bernd Noetscher 2000 - 2007.

You may use this source codes under the terms of the GNU Public License (Version 2) as published 
by the Free Software Foundation. 

If you are interested in using the source codes for other licenses or 
commercial development, you must buy commercial licenses from KBasic Software.
***************************************************************************
*/


#ifndef _TABLEITEM_H
#define _TABLEITEM_H


#include "typedef.h"
#include "_property.h"
#include "_control0.h"

#define TEST _tableitem    
#define TEST2 _tableitems   
#define TEST3 "tableItem"
//#define SUPERCLASS Object   
#undef SUPERCLASS

#define _TABLEITEM true



class _tableitem : public _property
{
  
public:


_tableitem()
{

 // nIndex = _nIndex;


  addProperty("Tag", pt_qstring);
  addProperty("Index", pt_boolean);
  addProperty("LoadedIndex", pt_boolean);
  addProperty("Null", pt_boolean);
  addProperty("LoadedNull", pt_boolean);

  addProperty("Type", pt_qstring);
  addProperty("LoadedType", pt_qstring);

  addProperty("LoadedName", pt_qstring);

/*  addProperty("ParentIndex", pt_integer);

  addProperty("Separator", pt_boolean);

  addProperty("Enabled", pt_boolean);
 // addProperty("Visible", pt_boolean);

  addProperty("Icon", pt_qstring);

  addProperty("StatusTip", pt_qstring);
  addProperty("ToolTip", pt_qstring);
  addProperty("WhatsThis", pt_qstring);*/

  // events


  // default values
  //SETPROPERTY_Caption("tableItem");

  addProperty("Name", pt_qstring);
  addProperty("ControlType", pt_qstring);
  SETPROPERTY_ControlType("TableItem");

  SETPROPERTY_Null(true);
 // SETPROPERTY_Enabled(true);


}




#include "../kbshared/__property_name.h"
#include "../kbshared/__property_controltype.h"
//#include "../kbshared/__property_parentcontrol.h"
#include "../kbshared/__property_tag.h"
/*
#include "../kbshared/__property_enabled.h"
#include "../kbshared/__property_icon.h"

#include "../kbshared/__property_parentindex.h"
#include "../kbshared/__property_tooltip.h"
#include "../kbshared/__property_statustip.h"
#include "../kbshared/__property_whatsthis.h"*/

//#include "../kbshared/__property_event.h"
//#include "_property_MENUBARITEMkeycode.h"



// events
//#include "_property_click.h"

void setAcceptDrops(bool b)
{
  bAcceptDrops = b;
}

bool acceptDrops()
{
  return bAcceptDrops;
}

//#include "_control1_binding.h"
//#include "_control1.h"

public:
  //_qpopupmenu *my_qpopupmenu;
  //_qpopupmenu *my_qpopupmenu_childs;
  //QAction *my_qaction;

 // 
  /*
  bool bEnabled;
  bool bSeparator;
  QString sIcon;*/

  //int nId;
  //_tableitem *parent;
  //bool bMenu;
  //bool bSubMenu;
  //QIconSet is;
  int nRow;
private:
  bool bAcceptDrops;



};

#include "_control2.h"

#undef TEST
#undef TEST2
#undef TEST3

#undef _TABLEITEM

#endif







