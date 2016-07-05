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

#include <stdio.h>

#include <QtGui>

#include "../kbshared/typedef.h"
#include "memory_type.h"


bool bPcodePrint_SilentMode; // für console.h hier ausgelagert


// *** t_variant

t_variant::t_variant(t_variant const& other)
{
  copy((t_variant &)other, *this);
}

t_variant& t_variant::operator=(t_variant const& other)
{
   if (this == &other)      // Same object?
    return *this;        // Yes, so skip assignment, and just return *this.

   
   copy((t_variant &)other, *this);
   return *this;
}


t_variant::t_variant(t_variant *v)
{
  copy((t_variant &)v, *this);
}

t_variant &t_variant::copy(t_variant & v, t_variant & me)
{         
    me.nType = v.nType; 
    switch(me.nType){
      case pcode__BOOLEAN:
        /*string_ = 0; */
        me.boolean_ = v.toBoolean();
        break;
      case pcode__QSTRING:
        //string_ = new QString();
        me.string_ = *v.toQString();
        me.qstring_ = &string_;
        break;
      case pcode__CSTRING:
        {
		      int nLen = strlen(v.cstring_);
		      char *ac = (char *) malloc(nLen + 1);		  
          memcpy(ac, v.cstring_, nLen);
			    memset(ac + nLen, 0, 1);
          me.cstring_ = ac;
        }
        break;
      case pcode__BYTE:
        /*string_ = 0; */
        me.byte_ = v.toByte();
        break;
      case pcode__SHORT:
        /*string_ = 0; */
        me.short_ = v.toShort();
        break;
      case pcode__INTEGER:
        /*string_ = 0; */
        me.integer_ = v.toInteger();
        break;
      case pcode__LONG:
        /*string_ = 0; */
        me.long_ = v.toLong();
        break;
      case pcode__SINGLE:
        /*string_ = 0; */
        me.single_ = v.toSingle();
        break;
      case pcode__DOUBLE:
        /*string_ = 0; */
        me.double_ = v.toDouble();
        break;
      case pcode__CURRENCY:
        /*string_ = 0; */
        me.currency_ = v.toCurrency();
        break;
      case pcode__DATE:
        /*string_ = 0; */
        me.date_ = v.toDate();
        break;
      default:
        /*string_ = 0; */
        me.object_ = v.toObject();
        me.pointer_ = v.toPointer();
        break;

    }
    return me;
  }



t_boolean t_variant::toBoolean()
{
  switch (nType){
    case pcode__BOOLEAN: return boolean_;

    case pcode__QSTRING:  return (t_boolean) qstring_->length() != 0;
  	case pcode__CSTRING:  return (t_boolean) cstring_[0];

    case pcode__BYTE: return (t_boolean) byte_;
    case pcode__SHORT: return (t_boolean) short_;
    case pcode__INTEGER: return (t_boolean) integer_;
    case pcode__LONG: 	 return (t_boolean) long_;

  	case pcode__SINGLE:  return (t_boolean) single_;
  	case pcode__DOUBLE:  return (t_boolean) double_;



    case pcode__CURRENCY: return (t_boolean) currency_.toBoolean();

    case pcode__DATE: return (t_boolean) 0;//date_.toBoolean();

    // ***
  	//case pcode__CHARACTER:
    //default: 
//      return runtimeError("internal error: t_variant::toBoolean()");
      //break;
	}
	return 0;
}

t_qstring t_variant::toQString()
{
  static QString sStringOutputBuffer;

  if (nType == pcode__BOOLEAN){
		sStringOutputBuffer = QString("%1").arg(boolean_ ? "TRUE" : "FALSE");

   } else if (nType == pcode__QSTRING){
 		return qstring_;

   } else if (nType == pcode__CSTRING){
    static QString s; s = cstring_;
 		return &s;

   } else if (nType == pcode__BYTE){
 		sStringOutputBuffer = QString("%1").arg((t_integer) byte_);
   } else if (nType == pcode__SHORT){
 		sStringOutputBuffer = QString("%1").arg((t_integer) short_);
  } else if (nType == pcode__INTEGER){
 		sStringOutputBuffer = QString("%1").arg(integer_);
  } else if (nType ==  pcode__LONG){
 		sStringOutputBuffer = QString("%1").arg(long_);
   } else if (nType == pcode__SINGLE){
		sStringOutputBuffer = QString("%1").arg(single_);
   } else if (nType == pcode__DOUBLE){
		sStringOutputBuffer = QString("%1").arg(double_);


  } else if (nType == pcode__CURRENCY){
 		sStringOutputBuffer = QString("%1").arg(*currency_.toQString());

  } else if (nType == pcode__DATE){
 		sStringOutputBuffer = QString("%1").arg(*date_.toQString());

   }

  return &sStringOutputBuffer;
}


t_cstring t_variant::toCString()
{
  static char acStringOutputBuffer[1024]; 

	sprintf(acStringOutputBuffer, "%s", "");

  if (nType == pcode__BOOLEAN){
		sprintf(acStringOutputBuffer, "%s", boolean_ ? "TRUE" : "FALSE");

   } else if (nType == pcode__QSTRING){
     static QString s; s = cstring_;
     static QByteArray a; a = s.toLocal8Bit();
     static t_cstring ac; ac = a.data();
 		return ac;

   } else if (nType == pcode__CSTRING){
 		return cstring_;

   } else if (nType == pcode__BYTE){
 		sprintf(acStringOutputBuffer, "%d", (t_integer) byte_);
   } else if (nType == pcode__SHORT){
 		sprintf(acStringOutputBuffer, "%d", (t_integer) short_);
  } else if (nType == pcode__INTEGER){
 		sprintf(acStringOutputBuffer, "%d", integer_);
  } else if (nType ==  pcode__LONG){
#ifdef WINDOWS
 		sprintf(acStringOutputBuffer, "%I64d", long_); // HIDE
#else
 		sprintf(acStringOutputBuffer, "%lld", long_);
#endif

   } else if (nType == pcode__SINGLE){
		sprintf(acStringOutputBuffer, "%.6f", single_);
   } else if (nType == pcode__DOUBLE){
		sprintf(acStringOutputBuffer, "%.6f", double_);


  } else if (nType == pcode__CURRENCY){
 		sprintf(acStringOutputBuffer, "%s",  currency_.toCString());

  } else if (nType == pcode__DATE){
 		sprintf(acStringOutputBuffer, "%s",  date_.toCString());

   //} else if (nType == pcode__CSTRING){
		//return (char *) cstring_;
   } else {
  //    return runtimeError("internal error: t_variant::toString()");
   }
//  return runtimeError("internal error");
	return acStringOutputBuffer;
}


t_byte t_variant::toByte()
{
  switch (nType){
    case pcode__BOOLEAN: return (t_byte) byte_;

    case pcode__QSTRING:  
      return (t_byte) qstring_->toInt();

    case pcode__CSTRING:  
      {
        QString s = cstring_;
        return (t_byte) s.toInt();
      }
    case pcode__BYTE: return byte_;
    case pcode__SHORT: return (t_byte) short_;
    case pcode__INTEGER: return (t_byte) integer_;
    case pcode__LONG: 	 return (t_byte) long_;

    case pcode__SINGLE:  return (t_byte) single_;
  	case pcode__DOUBLE:  return (t_byte) double_;



    case pcode__CURRENCY: return (t_byte) currency_.toByte();

    case pcode__DATE: return (t_byte) 0;//date_.toByte();

    // ***
  	//case pcode__CHARACTER:
    //default: 
//      return runtimeError("internal error: t_variant::toBoolean()");
      //break;
	}
	return 0;
}

t_short t_variant::toShort()
{
  switch (nType){
    case pcode__BOOLEAN: return (t_short) boolean_;

    case pcode__QSTRING:  
      return (t_short) qstring_->toInt();

    case pcode__CSTRING:  
      {
      QString s = cstring_;
      return  (t_short) s.toInt();
      }
    case pcode__BYTE: return (t_short) byte_;
    case pcode__SHORT: return short_;
    case pcode__INTEGER: return (t_short) integer_;
    case pcode__LONG: 	 return (t_short) long_;

    case pcode__SINGLE:  return (t_short) single_;
  	case pcode__DOUBLE:  return (t_short) double_;


   
    case pcode__CURRENCY: return (t_short) currency_.toShort();

    case pcode__DATE: return (t_short) 0;//date_.toShort();

    // ***
  	//case pcode__CHARACTER:
    //default: 
//      return runtimeError("internal error: t_variant::toBoolean()");
      //break;
	}
	return 0;
}

t_integer t_variant::toInteger()
{
  switch (nType){
    case pcode__BOOLEAN: return (t_integer) boolean_;

    case pcode__QSTRING:  
      return (t_integer) qstring_->toInt();

    case pcode__CSTRING:  
      {
      QString s = cstring_;
      return  (t_integer) s.toInt();
      }
    case pcode__BYTE: return (t_integer) byte_;
    case pcode__SHORT: return (t_integer) short_;
    case pcode__INTEGER: return integer_;
    case pcode__LONG: 	 return (t_integer) long_;

    case pcode__SINGLE:  return (t_integer) single_;
  	case pcode__DOUBLE:  return (t_integer) double_;

    
    case pcode__CURRENCY: return (t_integer) currency_.toInteger();

    case pcode__DATE: return (t_integer) 0;//date_.toInteger();

    // ***
//  	case pcode__STRING:
//  	case pcode__CSTRING:
//  	case pcode__CHARACTER:
    //default: 
//      return runtimeError("internal error: t_variant::toInteger()");
//  	case pcode__STRING:  return runtimeError("STRING not allowed");
//    default: 						 return runtimeError("internal error");
      //break;
	}
	return 0;
}

t_long t_variant::toLong()
{
  switch (nType){
    case pcode__BOOLEAN: return (t_long) boolean_;

    case pcode__QSTRING:  
      return (t_long) qstring_->toInt();

    case pcode__CSTRING:  
      {
      QString s = cstring_;
      return  (t_long) s.toInt();
      }
    case pcode__BYTE: return (t_long) byte_;
    case pcode__SHORT: return (t_long) short_;
    case pcode__INTEGER: return (t_long) integer_;
    case pcode__LONG: 	 return long_;

    case pcode__SINGLE:  return (t_long) single_;
  	case pcode__DOUBLE:  return (t_long) double_;
    

    
    case pcode__CURRENCY: return (t_long) currency_.toLong();

    case pcode__DATE: return (t_long) 0;//date_.toLong();

    // ***
  	//case pcode__STRING:
  	//case pcode__CSTRING:
  	//case pcode__CHARACTER:
    //default: 
//      return runtimeError("internal error: t_variant::toLong()");
//  	case pcode__STRING:  return runtimeError("STRING not allowed");
//    default: 						 return runtimeError("internal error");
      //break;
	}
	return 0;
}

t_single t_variant::toSingle()
{
  switch (nType){
    case pcode__BOOLEAN: return (t_single) boolean_;

    case pcode__QSTRING:  
      return (t_long) qstring_->toDouble();

    case pcode__CSTRING:  
      {
      QString s = cstring_;
      return  (t_long) s.toDouble();
      }
    case pcode__BYTE: return (t_single) byte_;
    case pcode__SHORT: return (t_single) short_;
    case pcode__INTEGER: return (t_single) integer_;
    case pcode__LONG: 	 return (t_single) long_;

    case pcode__SINGLE:  return single_;
  	case pcode__DOUBLE:  return (t_single) double_;


    case pcode__CURRENCY: return (t_single) currency_.toSingle();

    case pcode__DATE: return (t_single) 0;//date_.toSingle();

    // ***
  	//case pcode__STRING:
  	//case pcode__CSTRING:
  	//case pcode__CHARACTER:
    //default: 
//      return runtimeError("internal error: t_variant::toSingle()");
//  	case pcode__STRING:  return runtimeError("STRING not allowed");
//    default: 						 return runtimeError("internal error");
      //break;
	}
	return 0;
}

t_double t_variant::toDouble()
{
  switch (nType){
    case pcode__BOOLEAN: return (t_double) boolean_;

    case pcode__QSTRING:  
      return (t_long) qstring_->toDouble();

    case pcode__CSTRING:  
      {
      QString s = cstring_;
      return  (t_long) s.toDouble();
      }
    case pcode__BYTE: return (t_double) byte_;
    case pcode__SHORT: return (t_double) short_;
    case pcode__INTEGER: return (t_double) integer_;
    case pcode__LONG: 	 return (t_double) long_;
  	
    case pcode__SINGLE:  return (t_double) single_;
  	case pcode__DOUBLE:  return double_;
    

    case pcode__CURRENCY: return (t_double) currency_.toDouble();

    case pcode__DATE: return (t_double) 0;//date_.toDouble();

  	//case pcode__STRING:
  	//case pcode__CSTRING:
  	//case pcode__CHARACTER:
    //default: 
//      return runtimeError("internal error: t_variant::toDouble()");
//  	case pcode__STRING:  return runtimeError("STRING not allowed");
//    default: 						 return runtimeError("internal error");
      //break;
	}
	return 0;
}

t_currency t_variant::toCurrency()
{
  t_currency t;

  switch (nType){
    case pcode__BOOLEAN: t.setValue(boolean_, 0); break;

    case pcode__QSTRING:  
      {
        t_currency t2(qstring_->toDouble());
        t = t2;
        break;
      }

    case pcode__CSTRING:  
      {
      QString s = cstring_;
      t_currency t2(s.toDouble());
      t = t2;
      }
    case pcode__BYTE: t.setValue(byte_, 0); break;
    case pcode__SHORT: t.setValue(short_, 0); break;
    case pcode__INTEGER: t.setValue(integer_, 0); break;
    case pcode__LONG: 	 t.setValue(long_, 0); break;

    case pcode__SINGLE:  
      {
        t_currency t2(single_);
        t = t2;
        break; 
      }
  	case pcode__DOUBLE:  
      {
        t_currency t2(double_);
        t = t2;
        break; 
      }      


    case pcode__CURRENCY: t = currency_; break;

    case pcode__DATE: t.setValue(integer_, 0); break;

    // ***
  	//case pcode__STRING:
  	//case pcode__CSTRING:
  	//case pcode__CHARACTER:
  	//case pcode__DATE:
    //default: 
//      return runtimeError("internal error: t_variant::toInteger()");
//  	case pcode__STRING:  return runtimeError("STRING not allowed");
//    default: 						 return runtimeError("internal error");
      //break;
	}
	return t;
}

t_date t_variant::toDate()
{
  t_date t;
  switch (nType){
    
    case pcode__DATE: t = date_; break;
    // ***
  	//case pcode__STRING:
  	//case pcode__CSTRING:
  	//case pcode__CHARACTER:
  	//case pcode__DATE:
  	//case pcode__CURRENCY:
    //default: 
//      return runtimeError("internal error: t_variant::toInteger()");
//  	case pcode__STRING:  return runtimeError("STRING not allowed");
//    default: 						 return runtimeError("internal error");
      //break;
	}
	return t;
}

t_object t_variant::toObject()
{
  switch (nType){
    case pcode__OBJECT: return object_;
    default: 
      return (t_object) 0; 
      break;
	}
	return 0;
}

t_pointer t_variant::toPointer()
{
  if  (memory_type::isBinding(nType)){
    return pointer_;
  }
	return 0;
}


// *** t_currency

t_currency::t_currency (t_long bc, t_long ad)
{ 
  v = bc * 10000;
  if (bc < 0) v -= ad; else v += ad;
}

void t_currency::setValue (t_long bc, t_long ad)
{ 
  v = bc * 10000;
  if (bc < 0) v -= ad; else v += ad;
}

t_currency::t_currency (t_double d)
{ 
  t_long bc = (t_long) d;
  t_double e;
 
  if (bc < 0){
    e = (d - bc);
  } else {
    e = (d + bc);
  }
  t_long ad = e * 10000;

  v = bc * 10000 + ad;
}


t_currency::t_currency(t_qstring sv)
{
  v = 0;

  QByteArray a = sv->toLocal8Bit();
  fromCString(a.data());  
}

t_currency::t_currency(t_cstring sv)
{
  v = 0;

  fromCString(sv);
}
  
void t_currency::fromCString(t_cstring sv)
{
  static char *s, *b;
	static bool t, p;
	
  b = s = (char *) sv;
  
	static int nLen; nLen = 0;
	static int nLen2; nLen2 = 0;
	static bool qb; qb = false;
	//static bool bSuffix; bSuffix = false;
	static char cSign; cSign = 0;

  t = false;
	if (*s == '+' || *s == '-'){
		cSign = *s;
		s++;
		nLen++;
  }
  while (*s >= '0' && *s <= '9') {
    s++;
		nLen++;
    t = true;
  }
  if (p = (*s == '.')) {
    s++;
		nLen++;
    while (*s >= '0' && *s <= '9') {
      s++;
			nLen++;
  		nLen2++;
      t = true;
    }
  }
  if (!t) return;

	if (p == true) goto ok;
	else return;

  t = false;
  while (*s >= '0' && *s <= '9') {
    s++;
		nLen++;
    t = true;
  }
  if (!t) return;

ok:

  if (nLen2 > 4) {return; }

  errno = 0;
 
  static char acBc[256];
  static char acAd[64];

  memcpy(acBc, b, nLen - 1 - nLen2);
  acBc[nLen - 1 - nLen2] = 0;

  static t_long bc; bc = atol(acBc);

  static t_long ad; 


  if (nLen2){
    memcpy(acAd, b + nLen - nLen2, nLen);
    acAd[nLen] = 0;

    ad = atol(acAd);
    for (int i = 0; i < 4 - nLen2; i++){
      ad = ad * 10;
    }
  } else {
    ad = 0;
  }

  setValue(bc, ad);

}

t_long t_currency::ad()
{
  t_long m = v % 10000;
  if (m < 0) m = -m;
  return m;
}

t_long t_currency::bc()
{
  return v / 10000;
}

t_long t_currency::getValue()
{
  return v;
}

t_boolean t_currency::toBoolean()
{
  return v != 0;
}

t_qstring t_currency::toQString()
{
  static QString s;
  
  t_long r = v;

  s = QString("%1").arg((t_integer) r / 10000);
  if (r < 0) r = -r;
  s = s + QString(".%1").arg((t_integer) r % 10000, -4, 10, QChar('0')); // have to be done with these two lines, else v % 10000 does not work

  return &s;
}

t_qstring t_currency::toQString2()
{
  static QString s;
  
  t_long r = v;

  s = QString("%1").arg((t_integer) r / 10000);
  if (r < 0) r = -r;
  s = s + QString(".%1").arg((t_integer) r % 10000, -4, 10, QChar('0')); // have to be done with these two lines, else v % 10000 does not work

  return &s;
}

t_cstring t_currency::toCString()
{
  static char acText[1024];
  static char ac[1024];
  
  t_long r = v;

  sprintf(acText, "%d.", (t_integer) r / 10000);
  if (r < 0) r = -r;
  sprintf(ac, "%4d", (t_integer) r % 10000); // have to be done with these two lines, else v % 10000 does not work
  strcat(acText, ac);

  return acText;
}

t_cstring t_currency::toCString2()
{
  static char acText[1024];
  static char ac[1024];
  
  t_long r = v;

  sprintf(acText, "%d.", (t_integer) r / 10000);
  if (r < 0) r = -r;
  sprintf(ac, "%4d", (t_integer) r % 10000); // have to be done with these two lines, else v % 10000 does not work
  strcat(acText, ac);

  return acText;
}

t_byte t_currency::toByte()
{
  return toLong();
}

t_short t_currency::toShort()
{
  return toLong();
}

t_integer t_currency::toInteger()
{
  return toLong();
}

t_long t_currency::toLong()
{
  return v / 10000;
}

t_single t_currency::toSingle()
{
  return (t_single) toDouble();
}

t_double t_currency::toDouble()
{
  t_long ad = v % 10000;
  if (ad < 0) ad = -ad;

  t_long bc = v / 10000;

  t_double f = ad;
  f /= 10000;
  f += bc;
  return f;
}




t_date::t_date()
{
  nYear = 0;
  nMonth = 0;
  nDay = 0;
  nHour = 0;
  nMinute = 0;
  nSecond = 0;
}

t_date::t_date(t_qstring sv)
{
  nYear = 0;
  nMonth = 0;
  nDay = 0;

  nHour = 0;
  nMinute = 0;
  nSecond = 0;

  QByteArray a = sv->toLocal8Bit();
  fromCString(a.data());  
}

t_date::t_date(t_cstring sv)
{
  nYear = 0;
  nMonth = 0;
  nDay = 0;

  nHour = 0;
  nMinute = 0;
  nSecond = 0;

  fromCString(sv);
}
  
void t_date::fromCString(t_cstring sv)
{
  static char *s, *str, *b;
	
  b = s = str = (char *) sv;

	static bool bOK;
  bOK = false;

	static int nLen;
  nLen = 0;

  // format is #yyyy-mm-dd#

  nYear = 0;
  nMonth = 0;
  nDay = 0;

  nHour = 0;
  nMinute = 0;
  nSecond = 0;

  static char acYear[64];
  static char acMonth[64];
  static char acDay[64];

  static int i;
	if (*s != 0){

      i = 0;
      while ((*s >= '0' && *s <= '9') && i < 4) {

          if (*s >= '0' && *s <= '9') acYear[i] = *s;
          s++;
					
          i++;
          if (*s == 0){ goto r; } // no error, maybe it's a filehandle
          else if (*s == '-'){ s++; break; }

      }
      if (i == 0) goto r; // maybe it is  just the symbol #
      acYear[i] = '\0';

      i = 0;
      while ((*s >= '0' && *s <= '9') && i < 2) {

          if (*s >= '0' && *s <= '9') acMonth[i] = *s;
          s++;
					
          i++;
          if (*s == 0){ goto r; } // scannerError("Wrong date format. It must be #yyyy-mm-dd#."); }
          else if (*s == '-'){ s++; break; }

      }
      if (i == 0) goto r; // maybe it is just the symbol #
      acMonth[i] = '\0';

      i = 0;
      while ((*s >= '0' && *s <= '9') && i < 2) {

          if (*s >= '0' && *s <= '9') acDay[i] = *s;
          s++;
					
          i++;
          if (*s == 0){ break; } // scannerError("Wrong date format. It must be #yyyy-mm-dd#."); }

      }
      acDay[i] = '\0';

      if (s > str) {    // make sure at least one number character
        bOK = true;
      }	else goto r;
  }



  static int _nYear; _nYear = atoi(acYear);
  static int _nMonth; _nMonth = atoi(acMonth);
  static int _nDay; _nDay = atoi(acDay);

  if (_nMonth <= 0 || _nMonth >= 13){ goto r; } // scannerError("Wrong date. Month must be > 0 and < 13."); }
  if (_nDay <= 0 || _nDay >= 32){ goto r; } // scannerError("Wrong date. Day must be > 0 and < 32."); }

  nYear = _nYear;
  nMonth = _nMonth;
  nDay = _nDay;

  nHour = 0;
  nMinute = 0;
  nSecond = 0;

  return;
r:
  nYear = 0;
  nMonth = 0;
  nDay = 0;


  b = s = str = (char *) sv;
	
  bOK = false;

	
  // format is #hh:mm:ss PM#
  // format is #hh:mm:ss AM#
  // format is #0-12:m:s#

  static char acHour[64];
  static char acMinute[64];
  static char acSecond[64];
  static bool am; am = false;

//  static int i;
  if (*s != 0){

      i = 0;
      while ((*s >= '0' && *s <= '9') && i < 2) {

          if (*s >= '0' && *s <= '9') acHour[i] = *s;
          s++;
					
          i++;
          if (*s == 0){ return; } // no error, maybe it's a filehandle
          else if (*s == ':'){ s++; break; }

      }
      if (i == 0) return; // maybe it is  just the symbol #

      acHour[i] = '\0';

      i = 0;
      while ((*s >= '0' && *s <= '9') && i < 2) {

          if (*s >= '0' && *s <= '9') acMinute[i] = *s;
          s++;
					
          i++;
          if (*s == 0){ return; } // scannerError("Wrong time format. It must be #hh:mm:ss AM/PM#."); }
          else if (*s == ':'){ s++; break; }

      }
      if (i == 0) return;  // false; // maybe it is  just the symbol #

      acMinute[i] = '\0';

      i = 0;
      while ((*s >= '0' && *s <= '9') && i < 2) {

          if (*s >= '0' && *s <= '9') acSecond[i] = *s;
          s++;
					
          i++;
          if (*s == 0){ break; } // scannerError("Wrong time format. It must be #hh:mm:ss AM/PM#."); }
          else if (*s == ' ') break;

      }
      acSecond[i] = '\0';

      char c[3];
      c[1] = 0;
      i = 0;

      if (*s == ' '){
       while (i < 3) {

         c[i] = *s;
           s++;
					  
           i++;
           if (*s == 0){ break; } // scannerError("Wrong time format. It must be #hh:mm:ss AM/PM#."); }

       }
      }
      if ((c[1] == 'A' || c[1] == 'a') && (c[2] == 'M' || c[2] == 'm')){
        am = true;
      } else if ((c[1] == 'P' || c[1] == 'p') && (c[2] == 'M' || c[2] == 'm')){
        am = false;
      } else if (i == 0){
      } else {
        return; // scannerError("Wrong time format. It must be #hh:mm:ss AM/PM#."); 
      }


      if (s > str) {    // make sure at least one number character
        bOK = true;
      }	else return;
  }


  static int _nHour; _nHour = atoi(acHour);
  static int _nMinute; _nMinute = atoi(acMinute);
  static int _nSecond; _nSecond = atoi(acSecond);

  if (!am) _nHour += 12;

  if (_nHour <= 0 || _nHour >= 24){ return; } // scannerError("Wrong time. Hour must be >= 0 and <= 12."); }
  if (_nMinute <= 0 || _nMinute >= 59){ return; } // scannerError("Wrong time. Month must be >= 0 and <= 59."); }
  if (_nSecond <= 0 || _nSecond >= 32){ return; } // scannerError("Wrong time. Second must be >= 0 and <= 59."); }


  nYear = 0;
  nMonth = 0;
  nDay = 0;

  nHour = _nHour;
  nMinute = _nMinute;
  nSecond = _nSecond;

}

t_date::t_date(int Value)
{
  nYear = 0;
  nMonth = 0;
  nDay = 0;
  nHour = 0;
  nMinute = 0;
  nSecond = 0;
}

t_date::t_date(int _nYear, int _nMonth, int _nDay)
{
  nYear = _nYear;
  nMonth = _nMonth;
  nDay = _nDay;

  nHour = 0;
  nMinute = 0;
  nSecond = 0;
  //t.setDate(QDate(nYear, nMonth, nDay));
}

/*
t_date::t_date(t_date *dt)
{
  nYear = dt->nYear;
  nMonth = dt->nMonth;
  nDay = dt->nDay;

  nHour = dt->nHour;
  nMinute = dt->nMinute;
  nSecond = dt->nSecond;
}
*/

t_date::t_date(QDateTime dt)
{
  nYear = dt.date().year();
  nMonth = dt.date().month();
  nDay = dt.date().day();

  nHour = dt.time().hour();
  nMinute = dt.time().minute();
  nSecond = dt.time().second();
}

t_date::t_date(const t_date &dt)
{
  nYear = dt.nYear;
  nMonth = dt.nMonth;
  nDay = dt.nDay;

  nHour = dt.nHour;
  nMinute = dt.nMinute;
  nSecond = dt.nSecond;
}



void t_date::setValue(int _nYear, int _nMonth, int _nDay, int _nHour, int _nMinute, int _nSecond)
{
  nYear = _nYear;
  nMonth = _nMonth;
  nDay = _nDay;

  nHour = _nHour;
  nMinute = _nMinute;
  nSecond = _nSecond;

  //t.setDate(QDate(nYear, nMonth, nDay));
}


t_date::t_date(int _nYear, int _nMonth, int _nDay, int _nHour, int _nMinute, int _nSecond)
{
  nYear = _nYear;
  nMonth = _nMonth;
  nDay = _nDay;

  nHour = _nHour;
  nMinute = _nMinute;
  nSecond = _nSecond;

  //t.setDate(QDate(nYear, nMonth, nDay));
}

t_date::t_date(int _nHour, int _nMinute, int _nSecond, bool bAm)
{
  nYear = 0;
  nMonth = 0;
  nDay = 0;

  nHour = _nHour + (bAm ? 0 : 12);

  nMinute = _nMinute;
  nSecond = _nSecond;

  //t.setTime(QTime(nHour, nMinute, nSecond));
}

t_date::t_date(bool Time, int _nHour, int _nMinute, int _nSecond)
{
  nYear = 0;
  nMonth = 0;
  nDay = 0;

  nHour = _nHour;// + (bAm ? 0 : 12);

  nMinute = _nMinute;
  nSecond = _nSecond;

  //t.setTime(QTime(nHour, nMinute, nSecond));
}

void t_date::setValue(t_long t)
{
  
}

/*
t_boolean t_date::toBoolean()
{
  return 0;
}
*/
//12.344.545.454.545
t_qstring t_date::toQString()
{
  static QString s;
  static QString s2;

  if (nYear || nMonth || nDay){
    s = s.sprintf("%04d-%02d-%02d", nYear, nMonth, nDay);
    if (nHour || nMinute || nSecond){
      s2 = s2.sprintf(" %02d:%02d:%02d", nHour, nMinute, nSecond);
      s += s2;
    }
  } else {
    if (nHour || nMinute || nSecond){
      s = s.sprintf("%02d:%02d:%02d", nHour, nMinute, nSecond);
    }
  }

  return &s;
}

t_cstring t_date::toCString()
{
  static char acText[1024];
  static char ac[1024];

  if (nYear || nMonth || nDay){
    sprintf(acText, "%04d-%02d-%02d", nYear, nMonth, nDay);
    if (nHour || nMinute || nSecond){
      sprintf(ac, " %02d:%02d:%02d", nHour, nMinute, nSecond);
      strcat(acText, ac);  
    }
  } else {
    if (nHour || nMinute || nSecond){
      sprintf(acText, "%02d:%02d:%02d", nHour, nMinute, nSecond);
    }
  }

  return acText;
}

/*
t_byte t_date::toByte()
{
  return toLong();
}

t_short t_date::toShort()
{
  return toLong();
}

t_integer t_date::toInteger()
{
  return toLong();
}

t_long t_date::toLong()
{
  return toLong();
}

t_single t_date::toSingle()
{
  return toLong();
}

t_double t_date::toDouble()
{
  return toLong();
}

t_int16 t_date::toInt16()
{
  return toLong();
}

t_int32 t_date::toInt32()
{
  return toLong();
}

t_long t_date::toLong()
{
  return 0;// v / 10000;
}

t_uint16 t_date::toUInt16()
{
  return toLong();
}

t_uint32 t_date::toUInt32()
{
  return toLong();
}

t_uint64 t_date::toUInt64()
{
  return toLong();
}
*/

/*
// datetime class von qt
t_date::t_date()
{
}

t_date::t_date(char *s)
{
}

t_date::t_date(int nYear, int nMonth, int nDay)
{
}

t_string t_date::toString()
{
  return '\0';
}



// character class von qt
t_character::t_character()
{
}

t_character::t_character(char *s)
{
}

*/


// *** t_array

bool 		t_array::getOffset(int *nOffset, t_array *a, t_array *b, int nElementSize)
{
	*nOffset = 0;
	int n = 0;
	int y = 0;
  int nSize = nElementSize;

  if (a->count != b->count) return false;

 	for (int i = b->count - 1; i >= 0; i--){
    // possibilities 0..100, -10..100, -10..-5
    int m = (0 - b->idx[i]); // 0..10 = 11 einträge sind standard
    
		if (a->idx[i] >= b->idx[i] && a->idx[i] <= b->idxTo[i]){ // check the bounds, e.g. >= 1 && <= max     
			 
        if (i + 1 < b->count){
          nSize += (b->idxTo[i + 1] - b->idx[i + 1]) * nSize; // calculate size for the inner dimensions
        }
			  n += ( (a->idx[i] + m) * nSize); // transform many dimensions into one, e.g. y * 320 + x
     
		} else return false;
 	}
	*nOffset += n; // add offset

 	return true;
}

