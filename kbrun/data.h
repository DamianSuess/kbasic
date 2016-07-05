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


#ifndef DATA_H
#define DATA_H

#include "stack.h"


class data : public stack
{
public:
  data();


bool pushByte(t_byte c);
bool pushBoolean(t_boolean c);
bool pushInteger(t_integer _nValue);
bool pushShort(t_short short_);
bool pushReference(t_integer _nValue, t_integer nOffset, t_integer nType, t_scope scope, memory_variable2 *v);
bool pushObject(memory_variable2 *v);
bool pushBuffer(t_pointer t, t_integer nSize);
bool pushID(t_integer _nID, t_integer nType, memory_variable2 *v);
bool pushLong(t_long l);
bool pushQStringId(t_integer _nStaticID);
bool pushCStringId(t_integer _nStaticID);
bool pushCString(t_cstring s);
bool pushQString(t_qstring s);
//bool pushCString(int _nStaticID);
bool pushRealCString(t_cstring s);
bool pushEQString(t_integer _nDynamicID);
bool pushECString(t_integer _nDynamicID);
bool pushDouble(t_double _dValue);
bool pushSingle(t_single c);
bool pushPointer(t_integer classId, t_pointer p);
bool pushAddress(t_integer nType, t_pointer p);
bool pushCurrency(t_currency c);
bool pushDate(t_date d);
bool pushVariant(t_variant d);
//bool pushCharacter(t_character d);
/*
bool pushInt16(t_int16 d);
bool pushInt32(t_int32 d);
bool pushInt64(t_int64 d);
bool pushUInt16(t_uint16 d);
bool pushUInt32(t_uint32 d);
bool pushUInt64(t_uint64 d);*/
bool pushPCode(t_pcode c);
char *popRealCString();


};


#endif
