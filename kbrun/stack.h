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


#ifndef STACK_H
#define STACK_H

#include "../kbshared/bytearray.h"

class memory_variable2;

class stack {
public:
	stack(bool fifo = false);
	~stack();



void pushError(t_integer c)
{
  // push(); 


		ba->wr_Integer(c);
    ba->wr_PCode(pcode__ERROR);{
			return ;
		}
	
 	return ;
}

void pushByte(t_byte c)
{
  // push(); 


		ba->wr_Byte(c);
    ba->wr_PCode(pcode__BYTE);{
			return ;
		}
	
 	return ;
}

void pushBoolean(t_boolean c)
{
  // push();


		ba->wr_Boolean(c);
		ba->wr_PCode(pcode__BOOLEAN);{
			return ;
		}
	
 	return ;
}

void pushInteger(t_integer _nValue)
{
  // push();


		ba->wr_Integer(_nValue);
		ba->wr_PCode(pcode__INTEGER);{
			return ;
		}
	
 	return ;
}

void pushShort(t_short short_)
{
  // push();


		ba->wr_Short(short_);
		ba->wr_PCode(pcode__SHORT);{
			return ;
		}
	
 	return ;
}

void pushReference(t_integer _nValue, t_integer nOffset, t_integer nType, t_scope scope, t_array *a, memory_variable2 *v)
{
  // push();


		ba->wr_Integer(_nValue);
		ba->wr_Integer(nOffset);
		ba->wr_Integer(nType);
		ba->wr_Integer(scope);      
		ba->wr_Array(a);      
		ba->wr_Integer((t_integer) v);
		ba->wr_PCode(pcode__REFERENCE);{
			return ;
		}
	
 	return ;
}

/*
void pushObject(memory_variable2 *v)
{
  // push();

		ba->wr_Integer((t_integer) v);
		ba->wr_PCode(pcode__OBJECT);{
			return ;
		}
	
 	return ;
}*/

void pushBuffer(t_pointer t, t_integer nSize)
{
  // push();


		ba->wr_Integer(nSize);
		ba->wr_Integer((t_integer) t);
		ba->wr_PCode(pcode__BUFFER);{
			return ;
		}
	
 	return ;
}

void pushID(t_integer _nID, t_integer nType, memory_variable2 *v)
{
  // push();


		ba->wr_Integer((t_integer) v);
		ba->wr_Integer(nType);
		ba->wr_Integer(_nID);
		ba->wr_PCode(pcode__ID);{
			return ;
		}
	
 	return ;
}

void pushLong(t_long l)
{
  // push();


		ba->wr_Long(l);
		ba->wr_PCode(pcode__LONG);{
			return ;
		}
	
 	return ;
}

void pushQStringId(t_integer _nStaticID)
{
  // push();


		ba->wr_Integer(_nStaticID);
		ba->wr_PCode(pcode__QSTRING);{
			return ;
		}
	
 	return ;
}

void pushCStringId(t_integer _nStaticID)
{
  // push();


		ba->wr_Integer(_nStaticID);
		ba->wr_PCode(pcode__CSTRING);{
			return ;
		}
	
 	return ;
}

void pushCString(t_cstring s)
{
  // push();


		ba->wr_Integer((t_integer) s);
		ba->wr_PCode(pcode__CSTRING);{
			return ;
		}
	
 	return ;
}

void pushQString(t_qstring s)
{
  // push();


		ba->wr_Integer((t_integer) s);
		ba->wr_PCode(pcode__QSTRING);{
			return ;
		}
	
 	return ;
}

void pushRealCString(t_cstring s)
{
  // push();


		ba->wr_Char(0); // stop code for reading backward
		ba->wr_CString(s);
		ba->wr_PCode(pcode__REALCSTRING);{
			return ;
		}
	
 	return ;
}

void pushEQString(t_integer _nDynamicID)
{
  // push();


		ba->wr_Integer(_nDynamicID);
		ba->wr_PCode(pcode__EQSTRING);{
			return ;
		}
	
 	return ;
}

void pushECString(t_integer _nDynamicID)
{
  // push();


		ba->wr_Integer(_nDynamicID);
		ba->wr_PCode(pcode__ECSTRING);{
			return ;
		}
	
 	return ;
}

void pushEWString(t_integer _nDynamicID)
{
  // push();


		ba->wr_Integer(_nDynamicID);
		ba->wr_PCode(pcode__EWSTRING);{
			return ;
		}
	
 	return ;
}

void pushDouble(t_double _dValue)
{
  // push();


		ba->wr_Double(_dValue);
		ba->wr_PCode(pcode__DOUBLE);{
			return ;
		}
	
 	return ;
}

void pushSingle(t_single c)
{
  // push();


		ba->wr_Single(c);
		ba->wr_PCode(pcode__SINGLE);{
			return ;
		}
	
 	return ;
}

void pushParameter(t_integer classId, t_pointer p)
{
  return pushPointer(classId, p, true, false);
}

void pushPointer(t_integer classId, t_pointer p, t_boolean parameter, t_boolean memory_variable2)
{
  // push();


		ba->wr_PCode((t_integer)p);
		ba->wr_Boolean(memory_variable2);
		ba->wr_Boolean(parameter);
		ba->wr_Integer(classId);{
			return ;
		}
	
 	return ;
}

/*
void pushBinding(t_pointer p)
{
  // push();

		ba->wr_Integer((t_integer)p);{
			return ;
		}
	
 	return ;
}*/

void pushAddress(t_integer nType, t_pointer p)
{
  // push();


		ba->wr_Integer((t_integer) p);
		ba->wr_Integer(nType);{
			return ;
		}
	
 	return ;
}

void pushCurrency(t_currency c)
{
  // push();


		ba->wr_Currency(c);
		ba->wr_PCode(pcode__CURRENCY);{
			return ;
		}
	
 	return ;
}

void pushDate(t_date d)
{
  // push();


		ba->wr_Date(d);
		ba->wr_PCode(pcode__DATE);{
			return ;
		}
	
 	return ;
}

void pushVariant(t_variant d)
{
  // push();


		ba->wr_Variant(d);
		ba->wr_PCode(pcode__VARIANT);{
			return ;
		}
	
 	return ;
}
/*
void pushCharacter(t_character d)
{
  // push();


		ba->wr_Character(d);
		ba->wr_PCode(pcode__CHARACTER);{
			return ;
		}
	
 	return ;
}
*/
/*
void pushInt16(t_int16 d)
{
  // push();


		ba->wr_Int16(d);
		ba->wr_PCode(pcode__INT16);{
			return ;
		}
	
 	return ;
}

void pushInt32(t_int32 d)
{
  // push();


		ba->wr_Int32(d);
		ba->wr_PCode(pcode__INT32);{
			return ;
		}
	
 	return ;
}

void pushInt64(t_int64 d)
{
  // push();


		ba->wr_Int64(d);
		ba->wr_PCode(pcode__INT64);{
			return ;
		}
	
 	return ;
}

void pushUInt16(t_uint16 d)
{
  // push();


		ba->wr_UInt16(d);
		ba->wr_PCode(pcode__INT16);{
			return ;
		}
	
 	return ;
}

void pushUInt32(t_uint32 d)
{
  // push();


		ba->wr_UInt32(d);
		ba->wr_PCode(pcode__UINT32);{
			return ;
		}
	
 	return ;
}

void pushUInt64(t_uint64 d)
{
  // push();


		ba->wr_UInt64(d);
		ba->wr_PCode(pcode__UINT64);{
			return ;
		}
	
 	return ;
}
*/
void pushPCode(t_pcode c)
{


    ba->wr_PCode(c);{
			return ;
		}
	
 	return ;
}



t_pcode popPCode(){
	return ba->rd_PCode(bytearray__CURRENTPOS);
}

t_pcode peekPCode(){
	return ba->peekPCode(bytearray__CURRENTPOS);
}

t_byte popByte(){
  // pop();
	return ba->rd_Char(bytearray__CURRENTPOS);
}

t_integer popError(){
  // pop();
	return ba->rd_Integer(bytearray__CURRENTPOS);
}

t_boolean popBoolean(){
  // pop();
	return ba->rd_Boolean(bytearray__CURRENTPOS);
}

t_integer popInteger(){
  // pop();
	return ba->rd_Integer(bytearray__CURRENTPOS);
}

t_short popShort(){
  // pop();
	return ba->rd_Short(bytearray__CURRENTPOS);
}

t_integer popReference(t_integer*nOffset, t_integer *nType, t_scope *scope, t_array *a, memory_variable2 **v){
  // pop();
	*v = (memory_variable2 *) ba->rd_Integer(bytearray__CURRENTPOS);
	ba->rd_Array(a);
	*scope = (t_scope) ba->rd_Integer(bytearray__CURRENTPOS);
	*nType = ba->rd_Integer(bytearray__CURRENTPOS);
	*nOffset = ba->rd_Integer(bytearray__CURRENTPOS);
	t_integer n = ba->rd_Integer(bytearray__CURRENTPOS);
	return n;
}

/*
memory_variable2 * popObject(){
  // pop();
	return (memory_variable2 *) ba->rd_Integer(bytearray__CURRENTPOS);
}*/

t_long popLong(){
  // pop();
	return ba->rd_Long(bytearray__CURRENTPOS);
}

int popQStringId(){
  // pop();
	return ba->rd_Integer(bytearray__CURRENTPOS);
}

int popCStringId(){
  // pop();
	return ba->rd_Integer(bytearray__CURRENTPOS);
}

t_pointer popBuffer(t_integer *nSize)
{
  // pop();
	register t_pointer t = (t_pointer) ba->rd_Integer(bytearray__CURRENTPOS);
	*nSize = ba->rd_Integer(bytearray__CURRENTPOS);

	return t;
}

t_qstring popQString()
{
  // pop();
	return (t_qstring) ba->rd_Integer(bytearray__CURRENTPOS);
}

t_cstring popCString()
{
  // pop();
	return (t_cstring) ba->rd_Integer(bytearray__CURRENTPOS);
}


char *popRealCString(){
  // pop();

		return ba->rd_CString(bytearray__CURRENTPOS);
	
}

int popEQString(){
  // pop();
	return ba->rd_Integer(bytearray__CURRENTPOS);
}

int popECString(){
  // pop();
	return ba->rd_Integer(bytearray__CURRENTPOS);
}

int popID(t_integer *nType, memory_variable2 **v){
  // pop();
	register t_integer n = ba->rd_Integer(bytearray__CURRENTPOS);

	*nType = ba->rd_Integer(bytearray__CURRENTPOS);
	*v = (memory_variable2 *) ba->rd_Integer(bytearray__CURRENTPOS);
	return n;
}

t_single popSingle(){
  // pop();
	return ba->rd_Single(bytearray__CURRENTPOS);
}

t_double popDouble(){
  // pop();
	return ba->rd_Double(bytearray__CURRENTPOS);
}

t_pointer popPointer(){
  // pop();
	return (t_pointer) ba->rd_Integer(bytearray__CURRENTPOS);
}

/*
t_pointer popBinding(){
  // pop();
	return (t_pointer) ba->rd_Integer(bytearray__CURRENTPOS);
}
*/

t_pointer popAddress(){
  // pop();
	return (t_pointer) ba->rd_Integer(bytearray__CURRENTPOS);
}

t_currency popCurrency(){
  // pop();
	return ba->rd_Currency(bytearray__CURRENTPOS);
}

t_date popDate(){
  // pop();
	return ba->rd_Date(bytearray__CURRENTPOS);
}

t_variant popVariant(){
  // pop();
	return ba->rd_Variant(bytearray__CURRENTPOS);
}
/*
t_character popCharacter(){
  // pop();
	return ba->rd_Character(bytearray__CURRENTPOS);
}
*/
/*
t_int16 popInt16(){
  // pop();
	return ba->rd_Int16(bytearray__CURRENTPOS);
}

t_int32 popInt32(){
  // pop();
	return ba->rd_Int32(bytearray__CURRENTPOS);
}

t_int64 popInt64(){
  // pop();
	return ba->rd_Int64(bytearray__CURRENTPOS);
}

t_uint16 popUInt16(){
  // pop();
	return ba->rd_UInt16(bytearray__CURRENTPOS);
}

t_uint32 popUInt32(){
  // pop();
	return ba->rd_UInt32(bytearray__CURRENTPOS);
}

t_uint64 popUInt64(){
  // pop();
	return ba->rd_UInt64(bytearray__CURRENTPOS);
}
*/
bool resetStack()
{
  nCount = 0;
	return ba->resetPos();
}

void saveStack()
{
	ba->saveStack();
}

void restoreStack()
{
	ba->restoreStack();
}

void dumpStack()
{
/*
	CONSOLE print("-- dump stack --\n\n", console__RED);
	ba->dump();
  CONSOLE print("\n");*/
}

void printStack()
{
  /*
	CONSOLE print("\n");
	CONSOLE print("-- print stack --\n\n", console__RED);

	char ac[1024];
  t_boolean cValue = 0;
  t_string acValue = 0;
  t_integer nValue = 0;
  t_long lValue = 0;
  t_double dValue = 0;
  t_single fValue = 0;
  t_pcode type;

	int n = getPos();
	while (getPos() > 0){
		type = peekPCode();
		switch (type){
      
  		case pcode__BOOLEAN: cValue = popBoolean(); sprintf(ac, "BOOLEAN: %c", cValue); break;
  		case pcode__INTEGER: nValue = popInteger(); sprintf(ac, "INTEGER: %d", nValue); break;
  		case pcode__LONG: 	lValue = popLong(); sprintf(ac, "LONG: %I64d", lValue); break;
			case pcode__DOUBLE: dValue = popDouble(); sprintf(ac, "DOUBLE: %f", dValue); break;
			case pcode__SINGLE: fValue = popSingle(); sprintf(ac, "SINGLE: %f", fValue); break;
			//case pcode__STRING: nValue = popStringId(); sprintf(ac, "STRING: %d", nValue); break;
			case pcode__REALSTRING: acValue = popRealString(); sprintf(ac, "REALSTRING: %10.10s", acValue); break;
			case pcode__ESTRING: nValue = popEString(); sprintf(ac, "ESTRING: %d", nValue); break;
//			case pcode__ID: nValue = popID(); sprintf(ac, "IDENTIFIER: %d", nValue); break;
			default:
				sprintf(ac, "OTHER TYPE");
				break;
		}
  
		
		CONSOLE print(ac);
		CONSOLE print("\n");

	} 
	setPos(n);
	CONSOLE print("\n");
*/
}

int getPos()
{
	return ba->getPos();
}

void setPos(int nPos)
{
	ba->setPos(nPos);
}

int count()
{
  return nCount;
}

bytearray *ba;

private:

  ///* */ void pop();
  ///* */ void push();

bool bFifo;

int nCount;


};

#endif
