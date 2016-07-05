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


void *NIL = 0;


#include "../kbshared/_form.h"

#include "memory_type.h"
#include "interpreter_parameter.h"




//t_short *interpreter_parameter::toPointerShort(){	return (t_short *) pointer_; }
t_boolean *interpreter_parameter::toPointerBoolean(){	return (t_boolean *) pointer_; }

QString *interpreter_parameter::toPointerQString(){	return (QString *) pointer_; }
t_cstring *interpreter_parameter::toPointerCString(){	return (t_cstring *) pointer_; }

t_byte *interpreter_parameter::toPointerByte(){	return (t_byte *) pointer_; }
t_integer *interpreter_parameter::toPointerInteger(){	return (t_integer *) pointer_; }
t_long *interpreter_parameter::toPointerLong(){	return (t_long *) pointer_; }
t_single *interpreter_parameter::toPointerSingle(){	return (t_single *) pointer_; }
t_double *interpreter_parameter::toPointerDouble(){	return (t_double *) pointer_; }

//QString *interpreter_parameter::toPointerQString(){	return (QString *) pointer_; }

t_currency *interpreter_parameter::toPointerCurrency(){	return (t_currency *) pointer_; }
t_date *interpreter_parameter::toPointerDate(){	return (t_date *) pointer_; }
t_variant *interpreter_parameter::toPointerVariant(){	return (t_variant *) pointer_; }




t_boolean interpreter_parameter::toConstBoolean(){ return toBoolean(); }
t_boolean interpreter_parameter::toBoolean()
{
	t_pcode c;
  c = pcodeType;

	pcodeType = pcode__BOOLEAN;
  switch (c){
    case pcode__BOOLEAN: return boolean_;

  	//case pcode__STRING:  return (t_boolean) string_[0];      
  	//case pcode__CSTRING:  return (t_boolean) cstring_[0];

    case pcode__BYTE: return (t_boolean) byte_;
    case pcode__SHORT: return (t_boolean) short_;
    case pcode__INTEGER: return (t_boolean) integer_;
    case pcode__LONG: 	 return (t_boolean) long_;

  	case pcode__SINGLE:  return (t_boolean) single_;
  	case pcode__DOUBLE:  return (t_boolean) double_;
    
    case pcode__CURRENCY: return currency_.toBoolean();

    case pcode__DATE: return (t_boolean) 0;//date_.toBoolean();

    // ***
  	//case pcode__CHARACTER:
  	
    //default: 
//      return runtimeError("internal error: interpreter_parameter::toBoolean()");
      //break;
	}
	return 0;
}

t_cstring interpreter_parameter::toConstCString(){ return toCString(); }
t_cstring interpreter_parameter::toCString()
{
  static char acStringOutputBuffer[1024]; 

	//sprintf(acStringOutputBuffer, "%s", "");

	int c;
  c = pcodeType;

	pcodeType = pcode__CSTRING;

  if (c == pcode__BOOLEAN){
		sprintf(acStringOutputBuffer, "%s", boolean_ ? "TRUE" : "FALSE");

   } else if (c == pcode__QSTRING){
     if (qstring_ == 0) return 0;
     static QByteArray a; a = qstring_->toLocal8Bit();
 		 return a.data();

   } else if (c == pcode__CSTRING){
     return cstring_;

   } else if (c == pcode__BYTE){
 		sprintf(acStringOutputBuffer, "%d", (t_integer) byte_);
   } else if (c == pcode__SHORT){
 		sprintf(acStringOutputBuffer, "%d", (t_integer) short_);
  } else if (c == pcode__INTEGER){
 		sprintf(acStringOutputBuffer, "%d", integer_);
  } else if (c ==  pcode__LONG){
#ifdef WINDOWS
 		sprintf(acStringOutputBuffer, "%I64d", long_); // HIDE
#else
 		sprintf(acStringOutputBuffer, "%lld", long_);
#endif

   } else if (c == pcode__SINGLE){
		sprintf(acStringOutputBuffer, "%.6f", single_);
   } else if (c == pcode__DOUBLE){
		sprintf(acStringOutputBuffer, "%.6f", double_);

  } else if (c == pcode__CURRENCY){
    QString s;
 		s = *currency_.toQString();
    static QByteArray a; a = s.toLocal8Bit();
 		return a.data();

  } else if (c == pcode__DATE){
    QString s;
 		s = *date_.toQString();
    static QByteArray a; a = s.toLocal8Bit();
 		return a.data();

  } else if (c == pcode__ERROR){
 		sprintf(acStringOutputBuffer, "%d", integer_);

   } else {
  //    return runtimeError("internal error: interpreter_parameter::toString()");
   }
//  return runtimeError("internal error");
	return acStringOutputBuffer;
}


QString interpreter_parameter::toConstQString(){ return toQString(); }
QString interpreter_parameter::toQString()
{

	//sprintf(acStringOutputBuffer, "%s", "");

	int c;
  c = pcodeType;

	pcodeType = pcode__QSTRING;
  static QString s; 

  if (c == pcode__BOOLEAN){
		s = s.sprintf("%s", boolean_ ? "TRUE" : "FALSE");

   } else if (c == pcode__QSTRING){
     return *qstring_;

   } else if (c == pcode__CSTRING){
     s = cstring_;
     
     if (cstring_){
       free(cstring_);
       cstring_ = 0;
     }
     return s;

   } else if (c == pcode__BYTE){
 		s = s.sprintf("%d", (t_integer) byte_);
   } else if (c == pcode__SHORT){
 		s = s.sprintf("%d", (t_integer) short_);
  } else if (c == pcode__INTEGER){
 		s = s.sprintf("%d", integer_);
  } else if (c ==  pcode__LONG){
    s = QString("%1").arg(long_);
   } else if (c == pcode__SINGLE){
		s = s.sprintf("%.6f", single_);
   } else if (c == pcode__DOUBLE){
		s = s.sprintf("%.6f", double_);


  } else if (c == pcode__CURRENCY){
 		s = *currency_.toQString();
 		return s;

  } else if (c == pcode__DATE){
 		s = *date_.toQString();
 		return s;
  
  } else if (c == pcode__ERROR){
 		s = s.sprintf("%d", integer_);

   //} else if (c == pcode__CSTRING){
		//return (char *) cstring_;
   } else {
  //    return runtimeError("internal error: interpreter_parameter::toString()");
   }
//  return runtimeError("internal error");
	return s;
}



t_byte interpreter_parameter::toConstByte(){ return toByte(); }
t_byte interpreter_parameter::toByte()
{
	t_pcode c;
  c = pcodeType;

	pcodeType = pcode__BYTE;
  switch (c){
    case pcode__BOOLEAN: return (t_byte) byte_;

    //case pcode__STRING:  return (t_byte) string_[0];      
  	//case pcode__CSTRING:  return (t_byte) cstring_[0];

    case pcode__BYTE: return byte_;
    case pcode__SHORT: return (t_byte) short_;
    case pcode__INTEGER: return (t_byte) integer_;
    case pcode__LONG: 	 return (t_byte) long_;

    case pcode__SINGLE:  return (t_byte) single_;
  	case pcode__DOUBLE:  return (t_byte) double_;

    case pcode__CURRENCY: return currency_.toByte();

    case pcode__DATE: return (t_byte) 0;//date_.toByte();

    // ***
  	//case pcode__CHARACTER:
    //default: 
//      return runtimeError("internal error: interpreter_parameter::toBoolean()");
      //break;
	}
	return 0;
}
/* wird nicht gebraucht, entspricht toINT16

t_short interpreter_parameter::toShort()
{
	t_pcode c = pcodeType;
	pcodeType = pcode__SHORT;
  switch (c){
    case pcode__BOOLEAN: return (t_short) boolean_;

  	case pcode__STRING:  return (t_short) string_[0];
  	case pcode__CSTRING:  return (t_short) cstring_[0];

    case pcode__BYTE: return (t_short) byte_;
    case pcode__SHORT: return short_;
    case pcode__INTEGER: return (t_short) integer_;
    case pcode__LONG: 	 return (t_short) long_;

    case pcode__SINGLE:  return (t_short) single_;
  	case pcode__DOUBLE:  return (t_short) double_;

    // ***      
  	case pcode__CHARACTER:
  	case pcode__DATE:
  	case pcode__CURRENCY:
      
    default: 
//      return runtimeError("internal error: interpreter_parameter::toBoolean()");
      break;
	}
	return 0;
}
*/

t_integer interpreter_parameter::toConstInteger(){ return toInteger(); }


t_long interpreter_parameter::toConstLong(){ return toLong(); }
t_long interpreter_parameter::toLong()
{
	int c;
  c = pcodeType;

	pcodeType = pcode__LONG;
  switch (c){
    case pcode__BOOLEAN: return (t_long) boolean_;

    case pcode__BYTE: return (t_long) byte_;
    case pcode__SHORT: return (t_long) short_;
    case pcode__INTEGER: return (t_long) integer_;
    case pcode__LONG: 	 return long_;

    case pcode__SINGLE:  return (t_long) single_;
  	case pcode__DOUBLE:  return (t_long) double_;
        
    case pcode__CURRENCY: return currency_.toLong();
    
    case pcode__DATE: return (t_long) 0;//date_.toLong();

    // ***
  	//case pcode__STRING:
  	//case pcode__CSTRING:
  	//case pcode__CHARACTER:
    //default: 
//      return runtimeError("internal error: interpreter_parameter::toLong()");
//  	case pcode__STRING:  return runtimeError("STRING not allowed");
//    default: 						 return runtimeError("internal error");
      //break;
	}
	return 0;
}

t_single interpreter_parameter::toConstSingle(){ return toSingle(); }
t_single interpreter_parameter::toSingle()
{
	int c;
  c = pcodeType;

	pcodeType = pcode__SINGLE;
  switch (c){
    case pcode__BOOLEAN: return (t_single) boolean_;

    case pcode__BYTE: return (t_single) byte_;
    case pcode__SHORT: return (t_single) short_;
    case pcode__INTEGER: return (t_single) integer_;
    case pcode__LONG: 	 return (t_single) long_;

    case pcode__SINGLE:  return single_;
  	case pcode__DOUBLE:  return (t_single) double_;

    case pcode__CURRENCY: return currency_.toSingle();

    case pcode__DATE: return (t_single) 0;//date_.toSingle();

    // ***
  	//case pcode__STRING:
  	//case pcode__CSTRING:
  	//case pcode__CHARACTER:
    //default: 
//      return runtimeError("internal error: interpreter_parameter::toSingle()");
//  	case pcode__STRING:  return runtimeError("STRING not allowed");
//    default: 						 return runtimeError("internal error");
      //break;
	}
	return 0;
}

t_double interpreter_parameter::toConstDouble(){ return toDouble(); }
t_double interpreter_parameter::toDouble()
{
	int c;
  c = pcodeType;

	pcodeType = pcode__DOUBLE;
  switch (c){
    case pcode__BOOLEAN: return (t_double) boolean_;

    case pcode__BYTE: return (t_double) byte_;
    case pcode__SHORT: return (t_double) short_;
    case pcode__INTEGER: return (t_double) integer_;
    case pcode__LONG: 	 return (t_double) long_;
  	
    case pcode__SINGLE:  return (t_double) single_;
  	case pcode__DOUBLE:  return double_;
    
    case pcode__CURRENCY: return currency_.toDouble();

    case pcode__DATE: return (t_double) 0;//date_.toDouble();


  	//case pcode__STRING:
  	//case pcode__CSTRING:
  	//case pcode__CHARACTER:
    //default: 
//      return runtimeError("internal error: interpreter_parameter::toDouble()");
//  	case pcode__STRING:  return runtimeError("STRING not allowed");
//    default: 						 return runtimeError("internal error");
      //break;
	}
	return 0;
}

t_currency interpreter_parameter::toConstCurrency(){ return toCurrency(); }
t_currency interpreter_parameter::toCurrency()
{
	t_pcode c;
  c = pcodeType;

	pcodeType = pcode__CURRENCY;
  t_currency f;
  switch (c){
    case pcode__BOOLEAN: f.setValue(boolean_, 0); return f;

    case pcode__BYTE: f.setValue(byte_, 0); return f;
    case pcode__SHORT: f.setValue(short_, 0); return f;
    case pcode__INTEGER: f.setValue(integer_, 0); return f;
    case pcode__LONG: 	 f.setValue(long_, 0); return f;

    case pcode__SINGLE:  { t_currency f2(single_); return f2; }
  	case pcode__DOUBLE:  { t_currency f2(double_); return f2; }
    
    case pcode__CURRENCY: return currency_;

    //case pcode__DATE: f.setValue(date_, 0); return f;

    // ***
  	//case pcode__STRING:
  	//case pcode__CSTRING:
  	//case pcode__CHARACTER:
    //default: 
//      return runtimeError("internal error: interpreter_parameter::toInteger()");
//  	case pcode__STRING:  return runtimeError("STRING not allowed");
//    default: 						 return runtimeError("internal error");
      //break;
	}
	return t_currency();
}

t_date interpreter_parameter::toConstDate(){ return toDate(); }
t_date interpreter_parameter::toDate(bool bReturnOnly)
{
	t_pcode c;
  c = pcodeType;

	if (!bReturnOnly) pcodeType = pcode__DATE;
  
  t_date f;
  switch (c){
     
    case pcode__BOOLEAN: f.setValue(boolean_); return f;

    case pcode__QSTRING: 
      {
        t_date d(qstring_);
        return d;
      }

    case pcode__CSTRING: 
      {
        t_date d(cstring_);
        return d;
      }

    case pcode__BYTE: f.setValue(byte_); return f;
    case pcode__SHORT: f.setValue(short_); return f;
    case pcode__INTEGER: f.setValue(integer_); return f;
    case pcode__LONG: 	 f.setValue(long_); return f;

    case pcode__SINGLE:  f.setValue(single_); return f;
  	case pcode__DOUBLE:  f.setValue(double_); return f;
    
    case pcode__CURRENCY:  f.setValue(long_); return f;

    case pcode__DATE: return date_;

    // ***
  	//case pcode__CSTRING:
  	//case pcode__CHARACTER:
    //default: 
//      return runtimeError("internal error: interpreter_parameter::toInteger()");
//  	case pcode__STRING:  return runtimeError("STRING not allowed");
//    default: 						 return runtimeError("internal error");
      //break;
	}
	return 0;
}

t_integer interpreter_parameter::toId()
{
	t_pcode c;
  c = pcodeType;

	pcodeType = pcode__ID;
  switch (c){
    case pcode__ID: return id_;
//  	case pcode__STRING:  return runtimeError("STRING not allowed");
//    default: 						 return runtimeError("internal error");
	}
	return 0;
}

t_pointer interpreter_parameter::toPointer()
{
	t_pcode c;
  c = pcodeType;

	pcodeType = pcode__POINTER;
  switch (c){
    case pcode__POINTER: return pointer_;
//  	case pcode__STRING:  return runtimeError("STRING not allowed");
//    default: 						 return runtimeError("internal error");
	}
	return 0;
}
t_pointer interpreter_parameter::toVoid()
{
	t_pcode c;
  c = pcodeType;

  
  switch (c){
    case pcode___form: return (t_pointer) to_form();
//  	case pcode__STRING:  return runtimeError("STRING not allowed");
//    default: 						 return runtimeError("internal error");
	}
	return 0;
  
}

t_variant interpreter_parameter::toConstVariant(){ return toVariant(); }
t_variant interpreter_parameter::toVariant()
{
	t_pcode c;
  c = pcodeType;

	pcodeType = pcode__VARIANT;
  switch (c){
    case pcode__BOOLEAN: return t_variant(boolean_);

  	case pcode__QSTRING:  return t_variant(qstring_);      
  	case pcode__CSTRING:  return t_variant(cstring_);        	

    case pcode__BYTE: return t_variant(byte_);
    case pcode__SHORT: return t_variant(short_);
    case pcode__INTEGER: return t_variant(integer_);
    case pcode__LONG: 	 return t_variant(long_);

  	case pcode__SINGLE:  return t_variant(single_);
  	case pcode__DOUBLE:  return t_variant(double_);
    
    case pcode__CURRENCY: return t_variant(currency_);

    case pcode__DATE: return t_variant(date_);

    case pcode__VARIANT: return variant_;

    // ***
  	//case pcode__CHARACTER:
  	
    //default: 
//      return runtimeError("internal error: interpreter_parameter::toBoolean()");
      //break;
	}
	return 0;
}

int interpreter_parameter::kbasic_binding_sizeof(t_integer type)
{

switch(type){		
// KBBINDING
// CONTROL
//------------------------------------------------------------------------------------------------------------------------------------


case pcode___udpsocket: return sizeof(_udpsocket); break;
case pcode___scrollbar: return sizeof(_scrollbar); break;
case pcode___spinbox: return sizeof(_spinbox); break;
case pcode___slider: return sizeof(_slider); break;
case pcode___formsview: return sizeof(_formsview); break;
case pcode___toolbarview: return sizeof(_toolbarview); break;
case pcode___svg: return sizeof(_svg); break;
case pcode___commandlinkbutton: return sizeof(_commandlinkbutton); break;
case pcode___resizebox: return sizeof(_resizebox); break;
case pcode___toolbutton: return sizeof(_toolbutton); break;
case pcode___movie: return sizeof(_movie); break;
case pcode___sound: return sizeof(_sound); break;
case pcode___web: return sizeof(_web); break;
case pcode___checkbox: return sizeof(_checkbox); break;
case pcode___form: return sizeof(_form); break;
//case pcode___control: return sizeof(_control); break;

case pcode___label: return sizeof(_label); break;
case pcode___application: return sizeof(_application); break;
case pcode___mainwindow: return sizeof(_mainwindow2); break;
  
case pcode___combobox: return sizeof(_combobox); break;
case pcode___frame: return sizeof(_frame); break;
case pcode___image: return sizeof(_image); break;
case pcode___listbox: return sizeof(_listbox); break;
case pcode___progressbar: return sizeof(_progressbar); break;
case pcode___radiobutton: return sizeof(_radiobutton); break;
case pcode___textbox: return sizeof(_textbox); break;
case pcode___commandbutton: return sizeof(_commandbutton); break;  

case pcode___err: return sizeof(_err); break;  

case pcode___box: return sizeof(_box); break;  
//case pcode___hidden: return sizeof(_hidden); break;  

case pcode___imagebutton: return sizeof(_imagebutton); break;  
case pcode___timer: return sizeof(_timer); break;  
case pcode___treeview: return sizeof(_treeview); break;  
case pcode___tab: return sizeof(_tab); break;  
case pcode___event: return sizeof(_event); break;  
case pcode___childcontrol: return sizeof(_childcontrol); break;  
case pcode___serialport: return sizeof(_serialport); break;  
case pcode___statusbar: return sizeof(_statusbar); break;  
case pcode___savedialog: return sizeof(_savedialog); break;
case pcode___opendialog: return sizeof(_opendialog); break;
case pcode___cmath: return sizeof(_cmath); break;

//case pcode___report: return sizeof(_report); break;  

  

//case pcode___conversion: return sizeof(_conversion); break;  

//case pcode___bytearray: return sizeof(_bytearray); break;  
//case pcode___collection: return sizeof(_collection); break;  





//------------------------------------------------------------------------------------------------------------------------------------
default:
   
    return 0;
    break;
}
}



interpreter_parameter::interpreter_parameter (t_variant c){ 
  pcodeType = pcode__VARIANT; variant_ = c;/**variant_.copyVariant(&c);*/  INIT 
}
