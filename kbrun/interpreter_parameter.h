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



#ifndef INTERPRETER_PARAMETER_H
#define INTERPRETER_PARAMETER_H


#include "../kbshared/typedef.h"
#include "../kbshared/pcode.h"


#include "../kbshared/pcode_kbasic_binding.h"

#include "memory_type.h"

class scanner;
class parser;
class interpreter;

class _form;


#define toDecimal toCurrency 
#define totDateTime toDate 
#define tot_currency toCurrency 
#define tot_date toDate
#define tot_double toDouble
#define tot_boolean toBoolean
#define tot_integer toInteger
#define tot_variant toVariant
#define tot_long toLong
#define tot_string toQString

extern void *NIL;


#define INIT bCopyPointer = false; bDelete = false; pointer_ = 0;
#define INIT2 bCopyPointer = true;  bDelete = false; pointer_ = 0; register int n = qt_binding_sizeof(pcodeType); pointer_ = (void *) malloc(n); /*  if (pointer_ == 0){ memory_variableError("memory allocation failed"); return; }*/ memcpy(pointer_, (void *) &c, n);



struct interpreter_parameter {
public:
  t_pcode pcodeType;




	interpreter_parameter (){ pcodeType = 0; cstring_ = 0; INIT }
	
  interpreter_parameter (t_boolean c){ pcodeType = pcode__BOOLEAN; boolean_ = c; INIT }

  interpreter_parameter (QString c)
  { 
  pcodeType = pcode__QString; 
  string_ = c;
  qstring_ = &string_; 
 // b = qstring_.toAscii();
  //cstring_ = b.data();
  INIT 
  }

  interpreter_parameter (t_qstring c)
  { 
  pcodeType = pcode__QString; 
  if (c == 0){
    qstring_ = 0; 
  } else {
    string_ = *c;
    qstring_ = &string_; 
  }  
 // b = qstring_.toAscii();
  //cstring_ = b.data();
  INIT 
  }

//	interpreter_parameter (const char * ac){ pcodeType = pcode__STRING; string_ = (char *) ac; INIT }
	//interpreter_parameter (t_qstring ac){ pcodeType = pcode__QSTRING; qstring_ = ac; INIT }
	interpreter_parameter (t_cstring ac)
  { 
    pcodeType = pcode__CSTRING; 
    if (ac == 0){
      cstring_ = 0;
    } else {
      int n = strlen(ac) + 1;
      cstring_ = (char *) malloc(n);
      memcpy(cstring_, ac, n);
    }
    INIT 
  }
//	interpreter_parameter (cstring ac){ pcodeType = pcode__CSTRING; cstring_ = ac; INIT }

	interpreter_parameter (t_byte d){ pcodeType = pcode__BYTE; byte_ = d; INIT }
	interpreter_parameter (t_short d){ pcodeType = pcode__SHORT; short_ = d; INIT }
  interpreter_parameter (t_integer n){ pcodeType = pcode__INTEGER; integer_ = n; INIT }
	interpreter_parameter (t_long l){ pcodeType = pcode__LONG; long_ = l; INIT }

	interpreter_parameter (t_single f){ pcodeType = pcode__SINGLE; single_ = f; INIT }
	interpreter_parameter (t_double d){ pcodeType = pcode__DOUBLE; double_ = d; INIT }
/*
	interpreter_parameter (t_int16 d){ pcodeType = pcode__INT16; int16_ = d; INIT }
//	interpreter_parameter (t_int32 d){ pcodeType = pcode__INT32; int32_ = d; INIT }
	//interpreter_parameter (t_int64 d){ pcodeType = pcode__INT64; int64_ = d; INIT }
	interpreter_parameter (t_uint16 d){ pcodeType = pcode__UINT16; uint16_ = d; INIT }
	interpreter_parameter (t_uint32 d){ pcodeType = pcode__UINT32; uint32_ = d; INIT }
	interpreter_parameter (t_uint64 d){ pcodeType = pcode__UINT64; uint64_ = d; INIT }
*/

	interpreter_parameter (t_currency c){ pcodeType = pcode__CURRENCY; currency_ = c; INIT }

  interpreter_parameter (t_date c){ pcodeType = pcode__DATE; 

  date_.setValue(c.nYear,c.nMonth, c.nDay, c.nHour, c.nMinute, c.nSecond); 
  
  INIT }

	interpreter_parameter (t_pointer p){ pcodeType = pcode__POINTER; INIT  ; pointer_ = p; }

  interpreter_parameter (t_variant c);//{ pcodeType = pcode__VARIANT; variant_.copyVariant(&c); INIT }

  ~interpreter_parameter();


  

	//interpreter_parameter (t_character d){ pcodeType = pcode__CHARACTER; character_ = d; INIT }


	t_boolean toBoolean();
	t_boolean toConstBoolean();
	t_boolean *toPointerBoolean();



	t_cstring toCString();
	t_cstring toConstCString();
	t_cstring *toPointerCString();

	QString toQString();
	QString toConstQString();
	QString *toPointerQString();


	t_byte toByte();
	t_byte toConstByte();
	t_byte *toPointerByte();

	t_short toShort();
	t_short toConstShort();
	t_short *toPointerShort();

t_integer toInteger()
{
	t_pcode c;
  c = pcodeType;

	pcodeType = pcode__INTEGER;
  switch (c){
    case pcode__BOOLEAN: return (t_integer) boolean_;

    case pcode__BYTE: return (t_integer) byte_;
    case pcode__SHORT: return (t_integer) short_;
    case pcode__INTEGER: return integer_;
    case pcode__LONG: 	 return (t_integer) long_;

    case pcode__SINGLE:  return (t_integer) single_;
  	case pcode__DOUBLE:  return (t_integer) double_;

    case pcode__CURRENCY: return currency_.toInteger();

    case pcode__DATE: return (t_integer) 0;//date_.toInteger();

    // ***
//  	case pcode__STRING:
//  	case pcode__CSTRING:
//  	case pcode__CHARACTER:
    //default: 
//      return runtimeError("internal error: interpreter_parameter::toInteger()");
//  	case pcode__STRING:  return runtimeError("STRING not allowed");
//    default: 						 return runtimeError("internal error");
      //break;
	}
	return 0;
}

  t_integer toConstInteger();
	t_integer *toPointerInteger();

	t_long toLong();
	t_long toConstLong();
	t_long *toPointerLong();


	t_single toSingle();
	t_single toConstSingle();
	t_single *toPointerSingle();

	t_double toDouble();
	t_double toConstDouble();
	t_double *toPointerDouble();

/*
	t_int16 toInt16();
	t_int16 toConstInt16();
	t_int16 *toPointerInt16();

	t_int32 toInt32();
	t_int32 toConstInt32();
	t_int32 *toPointerInt32();

	t_int64 toInt64();
	t_int64 toConstInt64();
	t_int64 *toPointerInt64();

	t_uint16 toUInt16();
	t_uint16 toConstUInt16();
	t_uint16 *toPointerUInt16();

	t_uint32 toUInt32();
	t_uint32 toConstUInt32();
	t_uint32 *toPointerUInt32();

	t_uint64 toUInt64();
	t_uint64 toConstUInt64();
	t_uint64 *toPointerUInt64();
*/
	t_currency toCurrency();
	t_currency toConstCurrency();
	t_currency *toPointerCurrency();

  t_date toDate(bool bReturnOnly = false);
	t_date toConstDate();
	t_date *toPointerDate();

  t_variant toVariant();
	t_variant toConstVariant();
	t_variant *toPointerVariant();

	t_pointer toPointer();
	t_pointer toVoid();


	t_integer toId();


  t_qstring qstring_;
  QString string_;
  //QByteArray b;

	t_boolean		boolean_;

	//t_string  string_;
	t_cstring cstring_;

  t_byte		byte_;
  t_short short_;
	t_integer			integer_;
	t_long		long_;

	t_single		single_;
	t_double 	double_;
/*
  t_int16 int16_;
  t_int32 int32_;
  t_int64 int64_;
  t_uint16 uint16_;
  t_uint32 uint32_;
  t_uint64 uint64_;*/

	t_integer 		id_;
	t_pointer pointer_; 
	t_currency currency_;
	t_variant variant_;
	t_date date_;
//  t_character character_;


	interpreter_parameter *next;


  bool bCopyPointer;
  bool bDelete;
  


	// qt_binding
//  #include "interpreter_parameter_qt_binding.h"
  #include "interpreter_parameter_kbasic_binding.h"

};
#endif
