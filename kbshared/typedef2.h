/*
***************************************************************************
Copyright (C) 2000-2008 KBasic Software: www.kbasic.com. All rights reserved.
Source codes are copyrighted by Bernd Noetscher 2000-2008.

You may use this source codes under the terms of the GNU Public License (Version 3)
as published by the Free Software Foundation. 

If you are interested in using the source codes for other licenses or 
commercial development, you must buy commercial licenses from KBasic Software.

This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
***************************************************************************
*/


#ifndef TYPEDEF2_H
#define TYPEDEF2_H


#include <math.h>

#include "../kbshared/define.h"
#include "const.h"



typedef char t_boolean; // must be char, because of Intel Macs (on Intel Macs bool has 4 byte size)
typedef char t_event; // must be char, because of Intel Macs (on Intel Macs bool has 4 byte size)


typedef const void *t_qstring; // UTF8, eigentlich vom Typ QString, ist aber in kbc nicht bekannt
typedef const char *t_cstring; // ASCII


typedef unsigned char t_byte;
typedef signed short int t_short;
typedef signed int t_integer;
typedef signed long long t_long;

typedef float t_single;
typedef double t_double;
/*
typedef signed short int t_int16;
typedef signed int t_int32;
typedef signed long long t_int64;
typedef unsigned short int t_uint16;
typedef unsigned int t_uint32;
typedef unsigned long long t_uint64;*/

typedef void* t_object;
typedef void* t_pointer;

//typedef *see below* t_variant;
//typedef *see below* t_currency;
//typedef *see below* t_date;
//typedef *see below* t_character;


typedef t_integer t_pcode;
typedef t_integer t_builtin;
typedef t_integer t_token;


const t_pcode pcode__ERROR  			 = 194;

const t_pcode pcode__DOUBLE  		= 224;
const t_pcode pcode__INTEGER     = 225;

const t_pcode pcode__QSTRING      = 226;
const t_pcode pcode__LQSTRING     = 227;

const t_pcode pcode__BOOLEAN     = 228;
const t_pcode pcode__LONG    		= 229;
const t_pcode pcode__SINGLE  		= 230;
const t_pcode pcode__ID  = 231;
const t_pcode pcode__CONST				= 232;
const t_pcode pcode__REALSTRING		  = 234; // needed for DATA
const t_pcode pcode__VOID		= 235;
const t_pcode pcode__REFERENCE		  = 236; 
const t_pcode pcode__BYTE		  = 237; 
const t_pcode pcode__VARIANT		  = 238; 
const t_pcode pcode__OBJECT = 239;
const t_pcode pcode__EMPTY = 240;
const t_pcode pcode__CURRENCY		  = 241; 
const t_pcode pcode__NULL = 242;
const t_pcode pcode__DATE      = 243;
const t_pcode pcode__PARAMARRAY      = 244;
const t_pcode pcode__CHARACTER = 245;
const t_pcode pcode__ANY = 246;

const t_pcode pcode__EQSTRING      = 247;
const t_pcode pcode__CSTRING = 248;
const t_pcode pcode__LCSTRING = 249;
const t_pcode pcode__ECSTRING      = 250;

const t_pcode pcode__WSTRING = 251;
const t_pcode pcode__LWSTRING = 252;
const t_pcode pcode__EWSTRING = 253;
const t_pcode pcode__CASTEXCEPTION = 254;
const t_pcode pcode__EXCEPTION = 255;
const t_pcode pcode__QTEXCEPTION = 256;

//const t_pcode pcode__QString = 247;
#define pcode__QString pcode__QSTRING

#define pcode__t_double pcode__DOUBLE
#define pcode__t_integer pcode__INTEGER
#define pcode__t_long pcode__LONG
#define pcode__t_boolean pcode__BOOLEAN
#define pcode__t_string pcode__QSTRING
#define pcode__t_variant pcode__VARIANT




/*
const t_pcode pcode__INT16 = 247;
const t_pcode pcode__INT32 = 248;
const t_pcode pcode__INT64 = 249;
const t_pcode pcode__UINT16 = 250;
const t_pcode pcode__UINT32 = 251;
const t_pcode pcode__UINT64 = 252;
*/
//const t_pcode pcode__RSTRING = 253;
//const t_pcode pcode__LCSTRING = 254;
//const t_pcode pcode__RCSTRING = 255;
const t_pcode pcode__COLLECTION = 272;
const t_pcode pcode__SHORT = 38;
const t_pcode pcode__BUFFER = 310;
const t_pcode pcode__POINTER = 314;

// next pcode number > ?? 273 in pcode.h!

enum t_scope {
  local = 0,
  global,
  me,
  param,  
  outofscope
};




/*
Variablen vom Datentyp Currency werden als 64-Bit-Zahlen (8 Bytes) 
in einem ganzzahligen Format gespeichert und durch 10.000 dividiert, 
was eine Festkommazahl mit 15 Vorkomma- und 4 Nachkommastellen ergibt. 
Diese Darstellung ergibt einen Wertebereich von -922.337.203.685.477,5808 bis 922.337.203.685.477,5807. 
Das Typkennzeichen fr Currency ist das Zeichen (@).

t_int64 * 10000 ---> currency
currency / 10000 ---> t_int64

currency als t_int64
*/
struct t_currency {
public:

  
	t_currency ()
  { 
    v = 0;
  }

	t_currency (t_long bc, t_long ad);
	t_currency (t_double d);

	void setValue (t_long bc, t_long ad);
  
  t_long getValue();

  t_long ad();
  t_long bc();
/*
  t_boolean toBoolean();

  t_qstring toQString();
  t_qstring toQString2();*/
  t_cstring toCString();/*
  t_cstring toCString2();
  
  //t_wstring toWString();
  //t_wstring toWString2();

  t_byte toByte();
  t_short toShort();

  t_integer toInteger();
  t_long toLong();

  t_single toSingle();
  t_double toDouble();
  */
/*
  t_int16 toInt16();
  t_int32 toInt32();
  t_int64 toInt64();
  t_uint16 toUInt16();
  t_uint32 toUInt32();
  t_uint64 toUInt64();*/
  
  t_long v;
};



struct t_date {
public:
  
	t_date();//{}
	//t_date(const char *s);//{}
	//t_date(int nValue);//{}
	t_date(int nYear, int nMonth, int nDay);//{}
	t_date(int nHour, int nMinute, int nSecond, bool bAm);//{}

  void setValue(t_long t);
/*
  //t_boolean toBoolean();//{ return 0; }
  
  t_qstring toQString();
  t_qstring toQString2();*/
  t_cstring toCString();  /*
  t_cstring toCString2();

  //t_wstring toWString();
  //t_wstring toWString2();

  //t_byte toByte();//{ return 0; }
  //t_short toShort();//{ return 0; }

  //t_integer toInteger();//{ return 0; }
  //t_long toLong();//{ return 0; }

  //t_single toSingle();//{ return 0; }
  //t_double toDouble();//{ return 0; }

  //t_int16 toInt16();//{ return 0; }
  //t_int32 toInt32();//{ return 0; }
  //t_int64 toInt64();//{ return 0; }
  //t_uint16 toUInt16();//{ return 0; }
  //t_uint32 toUInt32();//{ return 0; }
  //t_uint64 toUInt64();//{ return 0; }
*/
public:

  int nYear;
  int nMonth;
  int nDay;
  int nHour;
  int nMinute;
  int nSecond;

};


// QChar stored as 2bytes
/*
struct t_character {
public:
	t_character(){}
	t_character(char *s){}
};
*/

struct t_variant {
public:
#ifdef RUN
  
  t_pcode nType;

	t_variant (){  nType = pcode__EMPTY; }

	t_variant (t_boolean c){ nType = pcode__BOOLEAN; boolean_ = c == false ? 0 : 1; }

  t_variant (t_qstring ac){ nType = pcode__QSTRING; string_ = ac; qstring_ = &string_; }
	t_variant (t_cstring ac){ nType = pcode__CSTRING; string_ = ac; cstring_ = &string_; }
	//t_variant (t_wstring ac){ nType = pcode__WSTRING; wstring_ = ac; }
	//t_variant (char *ac){ nType = pcode__STRING; string_ = ac; }
	//t_variant (const char * ac){ nType = pcode__CSTRING; cstring_ = (char *) ac; }

  t_variant (t_byte c){ nType = pcode__BYTE; byte_ = c; }
	t_variant (t_short c){ nType = pcode__SHORT; short_ = c; }
	t_variant (t_integer n){ nType = pcode__INTEGER; integer_ = n; }
	t_variant (t_long l){ nType = pcode__LONG; long_ = l; }

  t_variant (t_single f){ nType = pcode__SINGLE; single_ = f; }
	t_variant (t_double d){ nType = pcode__DOUBLE; double_ = d; }

	t_variant (t_object p){ nType = pcode__OBJECT; object_ = p; }

	t_variant (t_pointer p, int _nType){ nType = _nType; pointer_ = p; }

	//t_variant (t_character c){ nType = pcode__CHARACTER; character_ = c; }
	
  t_variant (t_currency c){ nType = pcode__CURRENCY; currency_ = c; }

	t_variant (t_date d){ nType = pcode__DATE; date_ = d; }



	t_boolean toBoolean();

	t_qstring toQString();
  t_cstring toCString();
  //t_wstring toWString();

  t_byte toByte();
  t_short toShort();
	t_integer toInteger();
	t_long toLong();

	t_single toSingle();
	t_double toDouble();

	t_currency toCurrency();

	t_date toDate();

	t_object toObject();
	t_pointer toPointer();

  //t_character toCharacter();

	union
	{
		t_boolean		boolean_;

		t_qstring qstring_;
		t_cstring cstring_;
		//t_wstring wstring_;

		t_byte		byte_;
	  t_short   short_;
		t_integer			integer_;
		t_long			long_;
		
    t_single		single_;
		t_double 		double_;

		t_object object_;
		t_pointer pointer_;

	};

  QString string_;

	t_currency currency_;

	t_date date_;

//  t_character character_;
#endif

};


struct defaultvalue {
public:

	t_boolean boolean_;

 // t_qstring qstring_;
  t_cstring cstring_;
  //t_wstring wstring_;

  t_single single_; 
	t_double double_; 

  t_byte byte_;
	t_short short_;
	t_integer integer_; 
	t_long long_; 

	//t_variant variant_;

	t_currency currency_;

	t_date date_;


defaultvalue()
{
	boolean_ = 0; 
  
 // qstring_ = ""; 
  cstring_ = "";
 // wstring_ = "";

  byte_ = 0; 
  short_ = 0; 
	integer_ = 0; 
	long_ = 0; 

  single_ = 0; 
	double_ = 0; 

  
}

};


struct t_pcode_array {
	int count;
	int idx[MAX_ARRAY];
};

struct t_array {
public:
	int count;
	int idx[MAX_ARRAY];  // 0 To 100
	int idxTo[MAX_ARRAY];
	int type;

  bool bIsArray; // needed for Sub(ParamArray b() As Variant)

t_array()
{
	count = 0;
  bIsArray = false;
}

int typeSizeMulitplierOfArray()
{
  int n = 1;

  // +1 ist das extra: 0..10 = 11 einträge
  for (int i = 0; i < count; i++) n *= (idxTo[i] - idx[i] + 1);
  return n;
}

bool copyArray(t_array *a)
{
	a->count = count;
	for (int i = 0; i < count; i++){ a->idx[i] = idx[i]; a->idxTo[i] = idxTo[i]; }
  a->bIsArray = bIsArray;
  return true;
}

bool 		isArray()
{
 	if (count || bIsArray) return true;
 	return false;
}

bool 		setIsArray(bool b)
{
 	bIsArray = b;
 	return true;
}

bool 		setCount(int n)
{
 	count = n;
 	return true;
}

static bool 		isArray(t_array *a)
{
 	if (a->count || a->bIsArray) return true;
 	return false;
}

static bool 		dimensionsEqual(t_array *a, t_array *b)
{
 	if (a->count == b->count) return true;
 	return false;
}

static bool 		getOffset(int *nOffset, t_array *a, t_array *b, int nElementSize);


};

struct t_arrays {
public:
	t_array a[MAX_TYPE];
};



struct t_arrayAccess {
public:
	t_array def;
	t_array use;
};



struct t_arrayVariable {
public:
	t_arrayAccess var;
	t_arrayAccess class_;
	t_arrayAccess element;
};




#endif
