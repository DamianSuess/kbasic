/*
***************************************************************************
Copyright (C) 2000-2008 KBasic Software: www.kbasic.com. All rights reserved.
Source codes are copyrighted by Bernd Noetscher 2000-2008.

You may use this source codes under the terms of the GNU Public License (Version 3) as published 
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
//#define SUPERCLASS ?   
#undef SUPERCLASS

#define _TABLEITEM true



class _tableitem : public _property
{
  
public:


_tableitem()
{


  addProperty("Tag", pt_qstring);
  addProperty("Index", pt_boolean);
  addProperty("LoadedIndex", pt_boolean);
  addProperty("Null", pt_boolean);
  addProperty("LoadedNull", pt_boolean);

  addProperty("Type", pt_qstring);
  addProperty("LoadedType", pt_qstring);

  addProperty("LoadedName", pt_qstring);

  // events


  // default values
  

  addProperty("Name", pt_qstring);
  addProperty("ControlType", pt_qstring);
  SETPROPERTY_ControlType("TableItem");

  SETPROPERTY_Null(true);
 


}




#include "../kbshared/__property_name.h"
#include "../kbshared/__property_controltype.h"

//#include "../kbshared/__property_tag.h"


// events

void setAcceptDrops(bool b)
{
  bAcceptDrops = b;
}

bool acceptDrops()
{
  return bAcceptDrops;
}


public:

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







