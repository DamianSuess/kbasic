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



#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "../kbshared/console.h"
#include "data.h"
#include "../kbshared/pcode.h"

data::data() : stack(true)
{
}

bool data::pushByte(t_byte c)
{
  // push(); 

	
		ba->wr_PCode(pcode__BYTE);
		ba->wr_Byte(c);{
			return true;
		}

 	return false;
}

bool data::pushBoolean(t_boolean c)
{
  // push();

	
		ba->wr_PCode(pcode__BOOLEAN);
		ba->wr_Boolean(c);{
			return true;
		}

 	return false;
}

bool data::pushInteger(t_integer _nValue)
{
  // push();

		ba->wr_PCode(pcode__INTEGER);
		ba->wr_Integer(_nValue);{
			return true;
		}

 	return false;
}

bool data::pushShort(t_short short_)
{
  // push();

		ba->wr_PCode(pcode__SHORT);
		ba->wr_Short(short_);{
			return true;
		}

 	return false;
}

bool data::pushReference(t_integer _nValue, t_integer nOffset, t_integer nType, t_scope scope, memory_variable2 *v)
{
  // push();

		ba->wr_PCode(pcode__REFERENCE);
		ba->wr_Integer(_nValue);
		ba->wr_Integer(nOffset);
		ba->wr_Integer(nType);
		ba->wr_Integer(scope);      
		ba->wr_Integer((t_integer) v);{
			return true;
		}

 	return false;
}

bool data::pushObject(memory_variable2 *v)
{
  // push();

		ba->wr_PCode(pcode__OBJECT);
		ba->wr_Integer((t_integer) v);{
			return true;
		}

 	return false;
}

bool data::pushBuffer(t_pointer t, t_integer nSize)
{
  // push();

    ba->wr_PCode(pcode__BUFFER);
			ba->wr_Integer((t_integer) t);
			ba->wr_Integer(nSize);{
			return true;
		}

 	return false;
}

bool data::pushID(t_integer _nID, t_integer nType, memory_variable2 *v)
{
  // push();

		ba->wr_PCode(pcode__ID);
			ba->wr_Integer(_nID);
			ba->wr_Integer(nType);
			ba->wr_Integer((t_integer) v);{
			return true;
		}

 	return false;
}

bool data::pushLong(t_long l)
{
  // push();

		ba->wr_PCode(pcode__LONG);
		ba->wr_Long(l);{
			return true;
		}

 	return false;
}

bool data::pushQStringId(t_integer _nStaticID)
{
  // push();

		ba->wr_PCode(pcode__QSTRING);
		ba->wr_Integer(_nStaticID);{
			return true;
		}

 	return false;
}

bool data::pushCStringId(t_integer _nStaticID)
{
  // push();

		ba->wr_PCode(pcode__CSTRING);
		ba->wr_Integer(_nStaticID);{
			return true;
		}

 	return false;
}

bool data::pushQString(t_qstring s)
{
  // push();

		ba->wr_PCode(pcode__QSTRING);
		ba->wr_Integer((t_integer) s);{
			return true;
		}

 	return false;
}

bool data::pushCString(t_cstring s)
{
  // push();

		ba->wr_PCode(pcode__CSTRING);
		ba->wr_Integer((t_integer) s);{
			return true;
		}

 	return false;
}

/*
bool data::pushCString(int _nStaticID)
{
  // push();

		ba->wr_PCode(pcode__CSTRING);
		ba->wr_Integer(_nStaticID);{
			return true;
		}

 	return false;
}
*/
bool data::pushRealCString(t_cstring s)
{
  // push();

		ba->wr_PCode(pcode__REALCSTRING);
		ba->wr_CString(s);{
			return true;
		}

 	return false;
}

bool data::pushEQString(t_integer _nDynamicID)
{
  // push();

		ba->wr_PCode(pcode__EQSTRING);
		ba->wr_Integer(_nDynamicID);{
			return true;
		}

 	return false;
}

bool data::pushECString(t_integer _nDynamicID)
{
  // push();

		ba->wr_PCode(pcode__ECSTRING);
		ba->wr_Integer(_nDynamicID);{
			return true;
		}

 	return false;
}

bool data::pushDouble(t_double _dValue)
{
  // push();

		ba->wr_PCode(pcode__DOUBLE);
		ba->wr_Double(_dValue);{
			return true;
		}

 	return false;
}

bool data::pushSingle(t_single c)
{
  // push();

		ba->wr_PCode(pcode__SINGLE);
		ba->wr_Single(c);{
			return true;
		}

 	return false;
}

bool data::pushPointer(t_integer classId, t_pointer p)
{
  // push();

		ba->wr_PCode(classId);
		ba->wr_Integer((t_integer)p);{
			return true;
		}

 	return false;
}

bool data::pushAddress(t_integer nType, t_pointer p)
{
  // push();

		ba->wr_Integer(nType);
		ba->wr_Integer((t_integer) p);{
			return true;
		}

 	return false;
}

bool data::pushCurrency(t_currency c)
{
  // push();

		ba->wr_PCode(pcode__CURRENCY);
		ba->wr_Currency(c);{
			return true;
		}

 	return false;
}

bool data::pushDate(t_date d)
{
  // push();

		ba->wr_PCode(pcode__DATE);
		ba->wr_Date(d);{
			return true;
		}

 	return false;
}

bool data::pushVariant(t_variant d)
{
  // push();

		ba->wr_PCode(pcode__VARIANT);
		ba->wr_Variant(d);{
			return true;
		}

 	return false;
}
/*
bool data::pushCharacter(t_character d)
{
  // push();

		ba->wr_PCode(pcode__CHARACTER);
		ba->wr_Character(d);{
			return true;
		}

 	return false;
}
*/
/*
bool data::pushInt16(t_int16 d)
{
  // push();

		ba->wr_PCode(pcode__INT16);
		ba->wr_Int16(d);{
			return true;
		}

 	return false;
}

bool data::pushInt32(t_int32 d)
{
  // push();

		ba->wr_PCode(pcode__INT32);
		ba->wr_Int32(d);{
			return true;
		}

 	return false;
}

bool data::pushInt64(t_int64 d)
{
  // push();

		ba->wr_PCode(pcode__INT64);
		ba->wr_Int64(d);{
			return true;
		}

 	return false;
}

bool data::pushUInt16(t_uint16 d)
{
  // push();

		ba->wr_PCode(pcode__UINT16);
		ba->wr_UInt16(d);{
			return true;
		}

 	return false;
}

bool data::pushUInt32(t_uint32 d)
{
  // push();

		ba->wr_PCode(pcode__UINT32);
		ba->wr_UInt32(d);{
			return true;
		}

 	return false;
}

bool data::pushUInt64(t_uint64 d)
{
  // push();

		ba->wr_PCode(pcode__UINT64);
		ba->wr_UInt64(d);{
			return true;
		}

 	return false;
}
*/

bool data::pushPCode(t_pcode c)
{

    ba->wr_PCode(c);{
			return true;
		}

 	return false;
}

char *data::popRealCString(){
  // pop();
		return ba->rd_CString(bytearray__CURRENTPOS);
}
