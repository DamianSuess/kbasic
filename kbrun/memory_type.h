/*
***************************************************************************
Copyright (C) 2000-2008 KBasic Software: www.kbasic.com. All rights reserved.
Source codes are copyrighted by Bernd Noetscher 2000-2008.

You may use this source codes under the terms of the GNU Public License (Version 3) 
as published by the Free Software Foundation. 

If you are interested in using the source codes for other licenses or 
commercial development, you must buy commercial licenses from KBasic Software.
***************************************************************************
*/


#ifndef MEMORY_TYPE_H
#define MEMORY_TYPE_H

#include <stdio.h>
#include <qmap.h>


#include <QLinkedList>

#include "../kbshared/pcode.h"

#include "const.h"


#include "../kbshared/pcode_kbasic_binding.h"


struct type_element {
	int    nElementId;
	char   acElementName[MAX_IDENTIFIER];
	char   acElementType[MAX_IDENTIFIER];
	int    nElementSize; // used for length of LSTRING
	t_array  a;

  int nType; // used for enum integer types

  // for enum values *
	t_byte		byte_;
  t_short short_;
	t_integer			integer_;
	t_long		long_;


  t_integer 		id_;
  // *

};

struct type {

	char acModule[MAX_IDENTIFIER];
	char acName[MAX_IDENTIFIER];
	int nId;
  int nScope;

  QLinkedList<type_element*> *list_type_element;
  QLinkedList<type_element*>::iterator IT;


};


class memory_type
{
public:
	memory_type				();
	~memory_type			();

	bool memory_typeError(char *acMemory_typeError);

	int 		addType			(const char *acModule, const char *acName, int nScope, int nId = -1);

	int 		addType2 	(const char *acModule, const char *acName, int nScope, int nId/* = -1*/);
  
	bool 		exist				(int nId);
	bool 		exist				(const char *acModule, const char *acName);

  char   *getModule			(int nId);
	char   *getModule			();

  char   *getName			(int nId);
	char   *getName			();

  int    getScope	  (int nId);
	int    getScope		();

  int			getId				(const char *acModule, const char *acName);
	int			getId				();

	bool 		first();
	bool 		next();

	bool		addElement	(int nId, const char *acElementName, const char *acElementType, int nElementSize, t_array *a, int nElementId);

	bool		firstElement	(int nId, char **acElementName, char **acElementType, int *nElementSize, t_array **a, int *nElementId);
	bool		nextElement	(int nId, char **acElementName, char **acElementType, int *nElementSize, t_array **a, int *nElementId);
	bool		findElement	(int nId, char *acElementNa, char **acElementName, char **acElementType, int *nElementSize, t_array **a, int *nElementId);
	const char *findElement	(int nId, int nFieldId);
	int findElement	(int nId, const char *acElementName);


static bool 		isObject(int nId)
{
  return compatibleType(pcode__OBJECT, nId);
}

static bool 		isClass(int nId)
{
  return nId > pcode__user_defined_class && nId < pcode__user_defined_module;
}

static bool 		isBinding(int nId)
{  
  return nId > pcode__kbasic_binding_class && nId < pcode__user_defined_class;
}

static bool 		isKBasic(int nId)
{  
  return nId > pcode__kbasic_binding_class && nId < pcode__user_defined_class;
}

static bool 		isModule(int nId)
{
  return nId > pcode__user_defined_module;
}

static bool 		isEnum(int nId)
{
  return nId > MAX_SKALAR_ENUM_ID;
}

static bool 		isType(int nId)
{
  return nId > MAX_SKALAR_TYPE_ID && nId < MAX_SKALAR_ENUM_ID;
}
/*
static bool 		isStructure(int nId)
{
  return nId > MAX_SKALAR_TYPE_ID && nId < MAX_SKALAR_ENUM_ID;
}
*/
static bool 		isString(int nId)
{
	switch(nId){
		case pcode__QSTRING:
		case pcode__CSTRING:
		case pcode__LQSTRING:   
		case pcode__LCSTRING:   

    case pcode__VARIANT:      
			return true;
	}

	return false;
}

static bool 		isNumeric(int nId)
{
	switch(nId){
		case pcode__BYTE:
		case pcode__SHORT:
		case pcode__INTEGER:
		case pcode__LONG:

		case pcode__SINGLE:
		case pcode__DOUBLE:


		case pcode__CURRENCY:
		case pcode__VARIANT:
			return true;
	}

	return false;
}

static bool 		scalar(int nId)
{
	switch(nId){
		case pcode__BOOLEAN:

		case pcode__QSTRING:
		case pcode__LQSTRING:
		case pcode__CSTRING:
		case pcode__LCSTRING:
		//case pcode__CSTRING:

		case pcode__SINGLE:
		case pcode__DOUBLE:

		case pcode__BYTE:
		case pcode__SHORT:
		case pcode__INTEGER:
		case pcode__LONG:


   	case pcode__VARIANT:

		//case pcode__CHARACTER:
		case pcode__CURRENCY:
		case pcode__DATE:

		case pcode__BOOLEAN_POINTER:

    case pcode__CSTRING_POINTER:

    case pcode__SINGLE_POINTER:
		case pcode__DOUBLE_POINTER:

		case pcode__SHORT_POINTER:
		case pcode__INTEGER_POINTER:
    case pcode__LONG_POINTER:


			return true;
	}

	return false;
}


static bool 		scalar(char *s)
{

  if (strcmp(s, pcode::pcode_(pcode__BOOLEAN)) == 0) return true;

  if (strcmp(s, pcode::pcode_(pcode__QSTRING)) == 0) return true;
	if (strcmp(s, pcode::pcode_(pcode__CSTRING)) == 0) return true;
	if (strcmp(s, pcode::pcode_(pcode__LQSTRING)) == 0) return true;
	if (strcmp(s, pcode::pcode_(pcode__LCSTRING)) == 0) return true;

	if (strcmp(s, pcode::pcode_(pcode__BYTE)) == 0) return true;
  if (strcmp(s, pcode::pcode_(pcode__SHORT)) == 0) return true;
	if (strcmp(s, pcode::pcode_(pcode__INTEGER)) == 0) return true;
  if (strcmp(s, pcode::pcode_(pcode__LONG)) == 0) return true;
	
	if (strcmp(s, pcode::pcode_(pcode__SINGLE)) == 0) return true;
	if (strcmp(s, pcode::pcode_(pcode__DOUBLE)) == 0) return true;
/*
	if (strcmp(s, pcode::pcode_(pcode__INT16)) == 0) return true;
	if (strcmp(s, pcode::pcode_(pcode__INT32)) == 0) return true;
	if (strcmp(s, pcode::pcode_(pcode__INT64)) == 0) return true;
	if (strcmp(s, pcode::pcode_(pcode__UINT16)) == 0) return true;
	if (strcmp(s, pcode::pcode_(pcode__UINT32)) == 0) return true;
	if (strcmp(s, pcode::pcode_(pcode__UINT64)) == 0) return true;
*/
	if (strcmp(s, pcode::pcode_(pcode__CURRENCY)) == 0) return true;

  if (strcmp(s, pcode::pcode_(pcode__DATE)) == 0) return true;

//	if (strcmp(s, pcode::pcode_(pcode__CHARACTER)) == 0) return true;

	return false;
}


static int 		getElementSize(int nType)
{
	switch(nType){
		case pcode__BOOLEAN: return sizeof(t_boolean);

    case pcode__QSTRING: return sizeof(t_qstring);
    case pcode__CSTRING: return sizeof(t_cstring);
		//case pcode__CSTRING: return sizeof(t_cstring);
		case pcode__LQSTRING: return 0;
		case pcode__LCSTRING: return 0;

		case pcode__SINGLE: return sizeof(t_single);
		case pcode__DOUBLE: return sizeof(t_double);

		case pcode__BYTE: return sizeof(t_byte);
		case pcode__SHORT: return sizeof(t_short);
		case pcode__INTEGER: return sizeof(t_integer);
    case pcode__LONG: return sizeof(t_long);
/*
    case pcode__INT16: return sizeof(t_int16);
    case pcode__INT32: return sizeof(t_int32);
    case pcode__INT64: return sizeof(t_int64);
    case pcode__UINT16: return sizeof(t_uint16);
    case pcode__UINT32: return sizeof(t_uint32);
    case pcode__UINT64: return sizeof(t_uint64);
*/
    case pcode__VARIANT: return sizeof(t_variant);

    case pcode__CURRENCY: return sizeof(t_currency);

    case pcode__DATE: return sizeof(t_date);
//    case pcode__CHARACTER: return sizeof(t_character);

  }

	return 0;
}

static int 		getElementSize(char *s)
{
	if (strcmp(s, pcode::pcode_(pcode__BOOLEAN)) == 0) return sizeof(t_boolean);

  if (strcmp(s, pcode::pcode_(pcode__QSTRING)) == 0) return sizeof(t_qstring);
	if (strcmp(s, pcode::pcode_(pcode__CSTRING)) == 0) return sizeof(t_cstring);
	if (strcmp(s, pcode::pcode_(pcode__LQSTRING)) == 0) return 0;
	if (strcmp(s, pcode::pcode_(pcode__LCSTRING)) == 0) return 0;

	if (strcmp(s, pcode::pcode_(pcode__SINGLE)) == 0) return sizeof(t_single);
  if (strcmp(s, pcode::pcode_(pcode__DOUBLE)) == 0) return sizeof(t_double);

  if (strcmp(s, pcode::pcode_(pcode__BYTE)) == 0) return sizeof(t_byte);
	if (strcmp(s, pcode::pcode_(pcode__SHORT)) == 0) return sizeof(t_short);
	if (strcmp(s, pcode::pcode_(pcode__INTEGER)) == 0) return sizeof(t_integer);
	if (strcmp(s, pcode::pcode_(pcode__LONG)) == 0) return sizeof(t_long);
	/*
  if (strcmp(s, pcode::pcode_(pcode__INT16)) == 0) return sizeof(t_int16);
  if (strcmp(s, pcode::pcode_(pcode__INT32)) == 0) return sizeof(t_int32);
  if (strcmp(s, pcode::pcode_(pcode__INT64)) == 0) return sizeof(t_int64);
  if (strcmp(s, pcode::pcode_(pcode__UINT16)) == 0) return sizeof(t_uint16);
  if (strcmp(s, pcode::pcode_(pcode__UINT32)) == 0) return sizeof(t_uint32);
  if (strcmp(s, pcode::pcode_(pcode__UINT64)) == 0) return sizeof(t_uint64);
*/
	if (strcmp(s, pcode::pcode_(pcode__CURRENCY)) == 0) return sizeof(t_currency);

  if (strcmp(s, pcode::pcode_(pcode__DATE)) == 0) return sizeof(t_date);

//  if (strcmp(s, pcode::pcode_(pcode__CHARACTER)) == 0) return sizeof(t_character);

	return 0;
}

static int 		getType(char *s)
{
	if (strcmp(s, pcode::pcode_(pcode__BOOLEAN)) == 0) return pcode__BOOLEAN;

  if (strcmp(s, pcode::pcode_(pcode__QSTRING)) == 0) return pcode__QSTRING;
	if (strcmp(s, pcode::pcode_(pcode__CSTRING)) == 0) return pcode__CSTRING;
	if (strcmp(s, pcode::pcode_(pcode__LQSTRING)) == 0) return pcode__LQSTRING;
	if (strcmp(s, pcode::pcode_(pcode__LCSTRING)) == 0) return pcode__LCSTRING;

	if (strcmp(s, pcode::pcode_(pcode__BYTE)) == 0) return pcode__BYTE;
	if (strcmp(s, pcode::pcode_(pcode__SHORT)) == 0) return pcode__SHORT;
  if (strcmp(s, pcode::pcode_(pcode__INTEGER)) == 0) return pcode__INTEGER;
  if (strcmp(s, pcode::pcode_(pcode__LONG)) == 0) return pcode__LONG;

	if (strcmp(s, pcode::pcode_(pcode__SINGLE)) == 0) return pcode__SINGLE;
	if (strcmp(s, pcode::pcode_(pcode__DOUBLE)) == 0) return pcode__DOUBLE;
/*
  if (strcmp(s, pcode::pcode_(pcode__INT16)) == 0) return pcode__INT16;
  if (strcmp(s, pcode::pcode_(pcode__INT32)) == 0) return pcode__INT32;
  if (strcmp(s, pcode::pcode_(pcode__INT64)) == 0) return pcode__INT64;
  if (strcmp(s, pcode::pcode_(pcode__UINT16)) == 0) return pcode__UINT16;
  if (strcmp(s, pcode::pcode_(pcode__UINT32)) == 0) return pcode__UINT32;
  if (strcmp(s, pcode::pcode_(pcode__UINT64)) == 0) return pcode__UINT64;
*/
	if (strcmp(s, pcode::pcode_(pcode__CURRENCY)) == 0) return pcode__CURRENCY;

  if (strcmp(s, pcode::pcode_(pcode__DATE)) == 0) return pcode__DATE;

//  if (strcmp(s, pcode::pcode_(pcode__CHARACTER)) == 0) return pcode__CHARACTER;

	return 0;
}

//static bool compatibleType_qt_binding(int nType, int nType2, bool b = false);

static bool 		compatibleType(int nType, int nType2)
{
	switch(nType){
// 		case pcode__QString:
		case pcode__QSTRING:
		case pcode__CSTRING:
		case pcode__LQSTRING:
		case pcode__LCSTRING:
    	switch(nType2){
    		case pcode__BOOLEAN:

//        case pcode__QString:
    		case pcode__QSTRING:
    		case pcode__CSTRING:
    		case pcode__LQSTRING:
    		case pcode__LCSTRING:

    		case pcode__BYTE:
    		case pcode__SHORT:
    		case pcode__INTEGER:
    		case pcode__LONG:

    		case pcode__SINGLE:
    		case pcode__DOUBLE:

       case pcode__CURRENCY:
//		    case pcode__CHARACTER:
		    case pcode__DATE:

        case pcode__VARIANT: // variant always compatible, will checked at runtime, impossible to know type at compilation time
    		case pcode__CONST: // const always compatible, will checked at runtime, impossible to know type at compilation time
    			return true;
    	}
			return false;
		case pcode__BOOLEAN:
    	switch(nType2){
    		case pcode__BOOLEAN:
    		case pcode__VARIANT: // variant always compatible, will checked at runtime, impossible to know type at compilation time
    		case pcode__CONST: // const always compatible, will checked at runtime, impossible to know type at compilation time
    			return true;
    	}
			return false;
      
		case pcode__CURRENCY:
    	switch(nType2){
		    case pcode__CURRENCY:
		    case pcode__DOUBLE:
		    case pcode__SINGLE:
		    case pcode__LONG:
		    case pcode__SHORT:
		    case pcode__INTEGER:
		    case pcode__BYTE:
          /*
		    case pcode__INT16:
		    case pcode__INT32:
		    case pcode__INT64:
        */
    		case pcode__VARIANT: // variant always compatible, will checked at runtime, impossible to know type at compilation time
    		case pcode__CONST: // const always compatible, will checked at runtime, impossible to know type at compilation time
    			return true;
    	}
			return false;      
		case pcode__DATE:
    	switch(nType2){
    		case pcode__DATE:
    		case pcode__QSTRING:
    		case pcode__CSTRING:
    		case pcode__LQSTRING:
    		case pcode__LCSTRING:
    		case pcode__VARIANT: // variant always compatible, will checked at runtime, impossible to know type at compilation time
    		case pcode__CONST: // const always compatible, will checked at runtime, impossible to know type at compilation time
    			return true;
    	}
			return false;
      /*
		case pcode__CHARACTER:
    	switch(nType2){
    		case pcode__CHARACTER:
    		case pcode__VARIANT: // variant always compatible, will checked at runtime, impossible to know type at compilation time
    		case pcode__CONST: // const always compatible, will checked at runtime, impossible to know type at compilation time
    			return true;
    	}
			return false;
      */
		case pcode__VARIANT:
      return true;
		case pcode__OBJECT:
     if (nType2 == pcode__OBJECT) return true;
     if (nType2 == pcode__VARIANT) return true;
 			return isClass(nType2);

		case pcode__SINGLE:
		case pcode__DOUBLE:

		case pcode__BYTE:
		case pcode__SHORT:
		case pcode__INTEGER:
		case pcode__LONG:

      switch(nType2){
    		case pcode__BOOLEAN:

    		case pcode__SINGLE:
    		case pcode__DOUBLE:

    		case pcode__BYTE:
    		case pcode__SHORT:
    		case pcode__INTEGER:
    		case pcode__LONG:

    		case pcode__CURRENCY:

       case pcode__VARIANT: // variant always compatible, will checked at runtime, impossible to know type at compilation time
    		case pcode__CONST: // const always compatible, will checked at runtime, impossible to know type at compilation time
    			return true;
    	}
			return false;
	}

  if (nType2 == pcode__VARIANT) return true; // variant always compatible, will checked at runtime, impossible to know type at compilation time
  if (nType2 == pcode__OBJECT) return true; // object always compatible, will checked at runtime, impossible to know type at compilation time

  if (nType2 == pcode__CONST) return true; // const always compatible, will checked at runtime, impossible to know type at compilation time

//  if (nType2 == pcode___collection) return true; // always compatible, will checked at runtime

//  if (nType == pcode___form && nType2 == pcode___report) return true;

  if (nType == pcode___control){ // CONTROL
    switch(nType2){              
    		case pcode___udpsocket:
    		case pcode___scrollbar:
    		case pcode___spinbox:
    		case pcode___slider:
    		case pcode___formsview:
    		case pcode___toolbarview:
    		case pcode___svg:
    		case pcode___commandlinkbutton:
    		case pcode___resizebox:
    		case pcode___toolbutton:
    		case pcode___movie:
    		case pcode___sound:
    		case pcode___web:
    		case pcode___label:
    		case pcode___checkbox:
    		case pcode___combobox:
    		case pcode___frame:
    		case pcode___image:
    		case pcode___listbox:
//    		case pcode___optionbutton:
    		case pcode___progressbar:
    		case pcode___radiobutton:
//    		case pcode___textarea:
    		case pcode___textbox:
    		case pcode___commandbutton:
    		case pcode___box:
    		case pcode___childcontrol:
    		case pcode___serialport:
        //case pcode___report:
          
//    		case pcode___line:
//    		case pcode___circle:
//    		case pcode___rectangle:
//    		case pcode___hidden:
//    		case pcode___qwidget:
    		case pcode___imagebutton:
//    		case pcode___canvas:
//    		case pcode___listview:
//    		case pcode___subform:
    		case pcode___timer:
    		case pcode___treeview:
    		case pcode___tab:
//    		case pcode___activex:
          return true;
        default:
          break;
    }
  }

	// binding; represents the inheritance tree, if user defined class look up if it is a subclass of a qt class
 // if (compatibleType_qt_binding(nType, nType2)) return true;  

	return nType == nType2; // user defined types or same type?
}



	//int 		getSizeElement(int nId, int nElementId);
	int 		getSize(int nId, int *nSize);
	int 		getSize(int nId);
	int 		getElementSize(int nId, int nFieldId);

	int 		getOffset(int nId, const char *acName, int *nOffset, bool *bDone, int *nIdx, t_arrays *as);
	int 		getOffset(int nId, const char *acName, t_arrays *as);

	int 		getOffset(int nId, int nElementId);
	int 		getOffset(int nId, int nElementId, int *nOffset, bool *bDone);

	int 		getType(int nId, const char *acName);
	int 		getType2(int nId, const char *acName, int *type, int *type_element, int *nAllSize, int *nElementSize, bool bOnlyFirstLevel);

	char *getKey(const char *acModule, const char *acName);

  type_element	*getElement	(int nId, int _nElementId);

  t_array   *getArray		(int nId, int nFieldId);

  // enum parts *
	int   getType		(int nId, int nFieldId);

  int getInteger(int nId, int nElementId);
  bool setInteger(int nId, int nElementId, int n);
  // *

private:
	bool type_memoryError(char *acTypeError);

	type *newMemory_type(const char *acModule, const char *acName, int nScope, int nId);
	type	*findMemory_type	(int nId);

	typedef QMap<int, type*> map9;
	map9 list_type;
	QMap<QString, type*> list_type2;
  map9::Iterator it;

  type_element* it2;
  
protected:
	int nIdCounter;

};

#endif
