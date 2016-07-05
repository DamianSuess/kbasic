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

#include "interpreter.h"


void interpreter::operate(t_pcode cOperator)
{
	operate(cOperator, true);
}

void interpreter::operate(t_pcode cOperator, bool remove)
{


	t_boolean L_boolean_ ;//= 0;
  t_boolean R_boolean_ ;//= 0;
  t_boolean boolean_ ;//= 0;


	t_qstring L_qstring_;// = 0;
	t_qstring R_qstring_;// = 0;

	t_cstring L_cstring_;// = 0;
	t_cstring R_cstring_;// = 0;


	t_byte L_byte_;// = 0;
	t_byte R_byte_;// = 0;
  t_byte byte_;// = 0;

	t_short L_short_ ;//= 0;
	t_short R_short_;// = 0;
  t_short short_ ;//= 0;

	t_integer L_integer_;// = 0;
	t_integer R_integer_;// = 0;
  t_integer integer_;// = 0;

	t_long L_long_ ;//= 0;
	t_long R_long_;// = 0;
  t_long long_;// = 0;


	t_single L_single_ ;//= 0;
	t_single R_single_;// = 0;
  t_single single_;// = 0;

	t_double L_double_;// = 0;
	t_double R_double_;// = 0;
  t_double double_ ;//= 0;

	static t_currency L_currency_;// = 0;
	static t_currency R_currency_ ;//= 0;
  static t_currency currency_ ;//= 0;

	static t_date L_date_;// = 0;
	static t_date R_date_ ;//= 0;
  static t_date date_ ;//= 0;

	t_object L_object_;// = 0;
	t_object R_object_ ;//= 0;
  t_object object_ ;//= 0;


  t_pcode LType;
  LType = 0; // muss initalisiert werden

	t_pcode RType;
  RType = 0; // muss initalisiert werden

  t_pcode cc;// = 0;

 	int nRID = 0;
 	int nLID = 0;

  bool b;

  t_pcode cOperator2;
  cOperator2 = cOperator;



  RType = myStack->popPCode();

  switch (RType){
		case pcode__REFERENCE:
				{
					int nReferenceOffset ;//= 0;
					int nReferenceType;// = 0;
         t_scope scope;
         t_array a;
				  memory_variable2 *v;// = 0;

		    	int identifier;
         identifier = myStack->popReference(&nReferenceOffset, &nReferenceType, &scope, &a, &v); 
					
					int n1;
         n1 = getVar(scope)->getReferenceId(identifier);

					int n2;
         n2 = getVar(scope)->getReferenceOffset(identifier);

					pushId(scope, n1, n2, 0);
				  RType = myStack->popPCode();
				}
				break;
  }	

  switch (RType){

		case pcode__BOOLEAN: R_boolean_ = myStack->popBoolean(); break;

    case pcode__QSTRING:
				 R_qstring_ = myStack->popQString();
				 break;
		case pcode__EQSTRING:
				 nRID = myStack->popQStringId();
				 R_qstring_ = estatics->getQString(nRID, 0);
				 RType = pcode__QSTRING;
				 break;
    case pcode__CSTRING:
				 R_cstring_ = myStack->popCString();
				 break;
		case pcode__ECSTRING:
				 nRID = myStack->popCStringId();
				 R_cstring_ = estatics->getCString(nRID, 0);
				 RType = pcode__CSTRING;
				 break;

		case pcode__BYTE:		 R_byte_ = myStack->popByte(); break;
		case pcode__SHORT:	 R_short_ = myStack->popShort(); break;
		case pcode__INTEGER: R_integer_ = myStack->popInteger(); break;
		case pcode__LONG: 	 R_long_ = myStack->popLong();    break;

		case pcode__SINGLE:  R_single_ = myStack->popSingle();  break;
		case pcode__DOUBLE:  R_double_ = myStack->popDouble();  break;
    


		case pcode__CURRENCY:  R_currency_ = myStack->popCurrency();    break;

    case pcode__DATE:  R_date_ = myStack->popDate();    break;

    case pcode__ERROR: 
        R_integer_ = myStack->popInteger(); break;
        RType = pcode__INTEGER;
        break;

    case pcode__OBJECT:  

      {
        bool b44 = myStack->popBoolean();
        bool memory_variable2 = myStack->popBoolean();
        R_object_ = myStack->popPointer();
      }

      break;

		default:

      {
        bool b44 = myStack->popBoolean();
        bool memory_variable2 = myStack->popBoolean();
        R_object_ = myStack->popPointer();
        R_object_ = R_object_;
      }

				 break;
  }

	myStack->saveStack();

  if (cOperator != pcode__NOT){

    // spezialhandling  for next step in einer for next schleife
   if (cOperator2 == pcode__FOR_GREATER_EQUAL){
     
     cc = myStack->popPCode();

     // hole step und entscheide ob >= 0 oder < 0
     switch (cc){

		   case pcode__BYTE:		 byte_ = myStack->popByte(); b = byte_ >= 0; break;
		   case pcode__SHORT:	 short_ = myStack->popShort(); b = short_ >= 0; break;
		   case pcode__INTEGER: integer_ = myStack->popInteger(); b = integer_ >= 0; break;
		   case pcode__LONG: 	 long_ = myStack->popLong(); b = long_ >= 0; break;

		   case pcode__SINGLE:  single_ = myStack->popSingle(); b = single_ >= 0; break;
		   case pcode__DOUBLE:  double_ = myStack->popDouble(); b = double_ >= 0; break;
       


		   default:

      {
        bool b44 = myStack->popBoolean();
        bool memory_variable2 = myStack->popBoolean();
        R_object_ = myStack->popPointer();
      }

				   break;
     }      

     if (b){
       cOperator = pcode__GREATER_EQUAL;
     } else {
       cOperator = pcode__LESSER_EQUAL;
     }
   }


    LType = myStack->popPCode();
    switch (LType){
		  case pcode__REFERENCE:
				  {
					  int nReferenceOffset ;//= 0;
					  int nReferenceType;// = 0;
           t_scope scope;
           t_array a;
           memory_variable2 *v ;//= 0;
  					
		    	  int identifier;
           identifier = myStack->popReference(&nReferenceOffset, &nReferenceType, &scope, &a, &v); 

					  int n1;
           n1 = getVar(scope)->getReferenceId(identifier);

					  int n2;
           n2 = getVar(scope)->getReferenceOffset(identifier);

					  pushId(scope, n1, n2, 0);
				    LType = myStack->popPCode();
				  }
				  break;
	  }

 	  switch (LType){
   	  case pcode__BOOLEAN: L_boolean_ = myStack->popBoolean(); break;

      case pcode__QSTRING:
				  L_qstring_ = myStack->popQString();
				  break;
		  case pcode__EQSTRING:
				  nLID = myStack->popQStringId();
				  L_qstring_ = estatics->getQString(nLID, 0);
				  LType = pcode__QSTRING;
				  break;
      case pcode__CSTRING:
				  L_cstring_ = myStack->popCString();
				  break;
		  case pcode__ECSTRING:
				  nLID = myStack->popCStringId();
				  L_cstring_ = estatics->getCString(nLID, 0);
				  LType = pcode__CSTRING;
				  break;

      case pcode__BYTE:		 L_byte_ = myStack->popByte(); break;
 		  case pcode__SHORT:		L_short_ = myStack->popShort(); break;
 		  case pcode__INTEGER: L_integer_ = myStack->popInteger(); break;
 		  case pcode__LONG: 	 L_long_ = myStack->popLong(); 	  break;

 		  case pcode__SINGLE:  L_single_ = myStack->popSingle();  break;
 		  case pcode__DOUBLE:  L_double_ = myStack->popDouble();  break;



      case pcode__CURRENCY: L_currency_ = myStack->popCurrency(); 	  break;

      case pcode__DATE: L_date_ = myStack->popDate(); 	  break;

	  case pcode__ERL: L_integer_ = myStack->popInteger(); break;

    case pcode__ERROR: 
        L_integer_ = myStack->popInteger(); 
        LType = pcode__INTEGER;
        break;

    case pcode__OBJECT:  
      
      {
        bool b44 = myStack->popBoolean();
        bool memory_variable2 = myStack->popBoolean();
        L_object_ = myStack->popPointer();
      }

      break;

		  default:


          {
            bool b44 = myStack->popBoolean();
            bool memory_variable2 = myStack->popBoolean();
            L_object_ = myStack->popPointer();
          }
				  break;
 	  }

  
   if (cOperator2 == pcode__FOR_GREATER_EQUAL){

     switch (cc){

		   case pcode__BYTE:		  myStack->pushByte(byte_); break;
		   case pcode__SHORT:	  myStack->pushShort(short_); break;
		   case pcode__INTEGER:  myStack->pushInteger(integer_); break;
		   case pcode__LONG: 	  myStack->pushLong(long_);    break;

		   case pcode__SINGLE:   myStack->pushSingle(single_);  break;
		   case pcode__DOUBLE:   myStack->pushDouble(double_);  break;
       


		   default:
			     {  internalError("error occured while operation"); return;}
				   break;
     }  
   }
   

  }



// HINT: linker typ bestimmt die größe, wenn beide typen gleich groß sind, --> lost precision gefahr  e.g. long<->uint64, vorzeichen setzt sich durch
  static char c[1024];
#ifdef HAS_CONSOLE
  if (!bSilent) sprintf(c, "%s", pcode::pcode_(cOperator));
#endif


  if (cOperator == pcode__DIV){

    switch(LType){
      case pcode__BOOLEAN:
        switch(RType){
          case pcode__BOOLEAN: { if (R_boolean_ == 0){ runtimeError("division by zero", 11); return;} double_ = (t_double) L_boolean_ / R_boolean_; } break;
          case pcode__BYTE: { if (R_byte_ == 0){ runtimeError("division by zero", 11); return; } double_ = (t_double) L_boolean_ / R_byte_; } break;
          case pcode__SHORT: { if (R_short_ == 0){ runtimeError("division by zero", 11); return; } double_ = (t_double) L_boolean_ / R_short_; } break;
          case pcode__INTEGER: { if (R_integer_ == 0){ runtimeError("division by zero", 11); return; } double_ = (t_double) L_boolean_ / R_integer_; } break;
          case pcode__LONG: { if (R_long_ == 0){ runtimeError("division by zero", 11); return; } double_ = (t_double) L_boolean_ / R_long_; } break;
          case pcode__SINGLE: { if (R_single_ == 0){ runtimeError("division by zero", 11); return; } double_ = (t_double) L_boolean_ / R_single_; } break;
          case pcode__DOUBLE: { if (R_double_ == 0){ runtimeError("division by zero", 11); return; } double_ = (t_double) L_boolean_ / R_double_; } break;
          //case pcode__CURRENCY: { if (R_currency_.getValue() == 0){ runtimeError("division by zero", 11); return; } t_currency t(L_boolean_, 0); double_ = (t.bc() / R_currency_.bc(), t.ad() / R_currency_.ad()); } break;
        }
        break;
      case pcode__BYTE:
        switch(RType){
          case pcode__BOOLEAN: { if (R_boolean_ == 0){ runtimeError("division by zero", 11); return;} double_ = (t_double) L_byte_ / R_boolean_; } break;
          case pcode__BYTE: { if (R_byte_ == 0){ runtimeError("division by zero", 11); return; } double_ = (t_double) L_byte_ / R_byte_; } break;
          case pcode__SHORT: { if (R_short_ == 0){ runtimeError("division by zero", 11); return; } double_ = (t_double) L_byte_ / R_short_; } break;
          case pcode__INTEGER: { if (R_integer_ == 0){ runtimeError("division by zero", 11); return; } double_ = (t_double) L_byte_ / R_integer_; } break;
          case pcode__LONG: { if (R_long_ == 0){ runtimeError("division by zero", 11); return; } double_ = (t_double) L_byte_ / R_long_; } break;
          case pcode__SINGLE: { if (R_single_ == 0){ runtimeError("division by zero", 11); return; } double_ = (t_double) L_byte_ / R_single_; } break;
          case pcode__DOUBLE: { if (R_double_ == 0){ runtimeError("division by zero", 11); return; } double_ = (t_double) L_byte_ / R_double_; } break;
          //case pcode__CURRENCY: { if (R_currency_.getValue() == 0){ runtimeError("division by zero", 11); return; } t_currency t(L_byte_, 0); double_ = (t.bc() / R_currency_.bc(), t.ad() / R_currency_.ad()); } break;
        }
        break;
      case pcode__SHORT:
        switch(RType){
          case pcode__BOOLEAN: { if (R_boolean_ == 0){ runtimeError("division by zero", 11); return;} double_ = (t_double) L_short_ / R_boolean_; } break;
          case pcode__BYTE: { if (R_byte_ == 0){ runtimeError("division by zero", 11); return; } double_ = (t_double) L_short_ / R_byte_; } break;
          case pcode__SHORT: { if (R_short_ == 0){ runtimeError("division by zero", 11); return; } double_ = (t_double) L_short_ / R_short_; } break;
          case pcode__INTEGER: { if (R_integer_ == 0){ runtimeError("division by zero", 11); return; } double_ = (t_double) L_short_ / R_integer_; } break;
          case pcode__LONG: { if (R_long_ == 0){ runtimeError("division by zero", 11); return; } double_ = (t_double) L_short_ / R_long_; } break;
          case pcode__SINGLE: { if (R_single_ == 0){ runtimeError("division by zero", 11); return; } double_ = (t_double) L_short_ / R_single_; } break;
          case pcode__DOUBLE: { if (R_double_ == 0){ runtimeError("division by zero", 11); return; } double_ = (t_double) L_short_ / R_double_; } break;
          //case pcode__CURRENCY: { if (R_currency_.getValue() == 0){ runtimeError("division by zero", 11); return; } t_currency t(L_short_, 0); double_ = (t.bc() / R_currency_.bc(), t.ad() / R_currency_.ad()); } break;
        }
        break;
      case pcode__INTEGER:
        switch(RType){
          case pcode__BOOLEAN: { if (R_boolean_ == 0){ runtimeError("division by zero", 11); return;} double_ = (t_double) L_integer_ / R_boolean_; } break;
          case pcode__BYTE: { if (R_byte_ == 0){ runtimeError("division by zero", 11); return; } double_ = (t_double) L_integer_ / R_byte_; } break;
          case pcode__SHORT: { if (R_short_ == 0){ runtimeError("division by zero", 11); return; } double_ = (t_double) L_integer_ / R_short_; } break;
          case pcode__INTEGER: { if (R_integer_ == 0){ runtimeError("division by zero", 11); return; } double_ = (t_double) L_integer_ / R_integer_; } break;
          case pcode__LONG: { if (R_long_ == 0){ runtimeError("division by zero", 11); return; } double_ = (t_double) L_integer_ / R_long_; } break;
          case pcode__SINGLE: { if (R_single_ == 0){ runtimeError("division by zero", 11); return; } double_ = (t_double) L_integer_ / R_single_; } break;
          case pcode__DOUBLE: { if (R_double_ == 0){ runtimeError("division by zero", 11); return; } double_ = (t_double) L_integer_ / R_double_; } break;
          //case pcode__CURRENCY: { if (R_currency_.getValue() == 0){ runtimeError("division by zero", 11); return; } t_currency t(L_integer_, 0); double_ = (t.bc() / R_currency_.bc(), t.ad() / R_currency_.ad()); } break;
        }
        break;
      case pcode__LONG:
        switch(RType){
          case pcode__BOOLEAN: { if (R_boolean_ == 0){ runtimeError("division by zero", 11); return;} double_ = (t_double) L_long_ / R_boolean_; } break;
          case pcode__BYTE: { if (R_byte_ == 0){ runtimeError("division by zero", 11); return; } double_ = (t_double) L_long_ / R_byte_; } break;
          case pcode__SHORT: { if (R_short_ == 0){ runtimeError("division by zero", 11); return; } double_ = (t_double) L_long_ / R_short_; } break;
          case pcode__INTEGER: { if (R_integer_ == 0){ runtimeError("division by zero", 11); return; } double_ = (t_double) L_long_ / R_integer_; } break;
          case pcode__LONG: { if (R_long_ == 0){ runtimeError("division by zero", 11); return; } double_ = (t_double) L_long_ / R_long_; } break;
          case pcode__SINGLE: { if (R_single_ == 0){ runtimeError("division by zero", 11); return; } double_ = (t_double) L_long_ / R_single_; } break;
          case pcode__DOUBLE: { if (R_double_ == 0){ runtimeError("division by zero", 11); return; } double_ = (t_double) L_long_ / R_double_; } break;
          //case pcode__CURRENCY: { if (R_currency_.getValue() == 0){ runtimeError("division by zero", 11); return; } t_currency t(L_long_, 0); double_ = (t.bc() / R_currency_.bc(), t.ad() / R_currency_.ad()); } break;
        }
        break;
      case pcode__SINGLE:
        switch(RType){
          case pcode__BOOLEAN: { if (R_boolean_ == 0){ runtimeError("division by zero", 11); return;} double_ = (t_double) L_single_ / R_boolean_; } break;
          case pcode__BYTE: { if (R_byte_ == 0){ runtimeError("division by zero", 11); return; } double_ = (t_double) L_single_ / R_byte_; } break;
          case pcode__SHORT: { if (R_short_ == 0){ runtimeError("division by zero", 11); return; } double_ = (t_double) L_single_ / R_short_; } break;
          case pcode__INTEGER: { if (R_integer_ == 0){ runtimeError("division by zero", 11); return; } double_ = (t_double) L_single_ / R_integer_; } break;
          case pcode__LONG: { if (R_long_ == 0){ runtimeError("division by zero", 11); return; } double_ = (t_double) L_single_ / R_long_; } break;
          case pcode__SINGLE: { if (R_single_ == 0){ runtimeError("division by zero", 11); return; } double_ = (t_double) L_single_ / R_single_; } break;
          case pcode__DOUBLE: { if (R_double_ == 0){ runtimeError("division by zero", 11); return; } double_ = (t_double) L_single_ / R_double_; } break;
          //case pcode__CURRENCY: { if (R_currency_.getValue() == 0){ runtimeError("division by zero", 11); return; } t_currency t(L_single_, 0); double_ = (t.bc() / R_currency_.bc(), t.ad() / R_currency_.ad()); } break;
        }
        break;
      case pcode__DOUBLE:
        switch(RType){
          case pcode__BOOLEAN: { if (R_boolean_ == 0){ runtimeError("division by zero", 11); return;} double_ = (t_double) L_double_ / R_boolean_; } break;
          case pcode__BYTE: { if (R_byte_ == 0){ runtimeError("division by zero", 11); return; } double_ = (t_double) L_double_ / R_byte_; } break;
          case pcode__SHORT: { if (R_short_ == 0){ runtimeError("division by zero", 11); return; } double_ = (t_double) L_double_ / R_short_; } break;
          case pcode__INTEGER: { if (R_integer_ == 0){ runtimeError("division by zero", 11); return; } double_ = (t_double) L_double_ / R_integer_; } break;
          case pcode__LONG: { if (R_long_ == 0){ runtimeError("division by zero", 11); return; } double_ = (t_double) L_double_ / R_long_; } break;
          case pcode__SINGLE: { if (R_single_ == 0){ runtimeError("division by zero", 11); return; } double_ = (t_double) L_double_ / R_single_; } break;
          case pcode__DOUBLE: { if (R_double_ == 0){ runtimeError("division by zero", 11); return; } double_ = (t_double) L_double_ / R_double_; } break;
          //case pcode__CURRENCY: { if (R_currency_.getValue() == 0){ runtimeError("division by zero", 11); return; } t_currency t(L_double_, 0); double_ = (t.bc() / R_currency_.bc(), t.ad() / R_currency_.ad()); } break;
        }
        break;
        /*
      case pcode__CURRENCY:
        switch(RType){
          case pcode__BOOLEAN: { if (R_boolean_ == 0){ runtimeError("division by zero", 11); return;} double_ = L_dou ble_ / R_boolean_; } break;
          case pcode__BYTE: { if (R_byte_ == 0){ runtimeError("division by zero", 11); return; } double_ = L_doub le_ / R_byte_; } break;
          case pcode__SHORT: { if (R_short_ == 0){ runtimeError("division by zero", 11); return; } double_ = L_double_ / R_short_; } break;
          case pcode__INTEGER: { if (R_integer_ == 0){ runtimeError("division by zero", 11); return; } double_ = L_double_ / R_integer_; } break;
          case pcode__LONG: { if (R_long_ == 0){ runtimeError("division by zero", 11); return; } double_ = L_double_ / R_long_; } break;
          case pcode__SINGLE: { if (R_single_ == 0){ runtimeError("division by zero", 11); return; } double_ = L_ double_ / R_single_; } break;
          case pcode__DOUBLE: { if (R_double_ == 0){ runtimeError("division by zero", 11); return; } double_ = L_double_ / R_double_; } break;
          //case pcode__CURRENCY: { if (R_currency_.getValue() == 0){ runtimeError("division by zero", 11); return; } double_ = (L_currency_.bc() / R_currency_.bc(), L_currency_.ad() / R_currency_.ad()); } break;
        }
        break;*/
    }

		if (remove == false) myStack->restoreStack();
 	  myStack->pushDouble(double_); 
#ifdef HAS_CONSOLE
    if (!bSilent) sprintf(acStringOutputBuffer, "/ --> %.6f", double_);
#endif

  } else {

  // pcode__BOOLEAN ***
  if (LType == pcode__BOOLEAN){

  if (RType == pcode__BOOLEAN){
         if (cOperator == pcode__MUL) boolean_ = L_boolean_ * R_boolean_;
    else if (cOperator == pcode__AND) boolean_ = L_boolean_ & R_boolean_;
    else if (cOperator == pcode__OR)  boolean_ = L_boolean_ | R_boolean_;
    else if (cOperator == pcode__XOR) boolean_ = L_boolean_ ^ R_boolean_;
    else if (cOperator == pcode__IMP) boolean_ = !(L_boolean_ != 0 && R_boolean_ == 0);
    else if (cOperator == pcode__POWER) boolean_ = (t_boolean) pow((t_double) L_boolean_, (t_double) R_boolean_);
    else if (cOperator == pcode__ADD) boolean_ = L_boolean_ + R_boolean_;
    else if (cOperator == pcode__SUB) boolean_ = L_boolean_ - R_boolean_;
    //else if (cOperator == pcode__DIV){ if (R_boolean_ == 0){ runtimeError("division by zero", 11); return;} boolean_ = L_boolean_ / R_boolean_; }
    else if (cOperator == pcode__MOD){ if (R_boolean_ == 0){ runtimeError("MOD by zero", 11); return;} boolean_ = L_boolean_ % R_boolean_; }
    else if (cOperator == pcode__IDIV){ if (R_boolean_ == 0){ runtimeError("integer division by zero", 11); return;} boolean_ = L_boolean_ / R_boolean_; }
    else if (cOperator == pcode__EQUAL) 				boolean_ = L_boolean_ == R_boolean_;
    else if (cOperator == pcode__EQV) 				boolean_ = L_boolean_ == R_boolean_;
    else if (cOperator == pcode__UNEQUAL) 			boolean_ = L_boolean_ != R_boolean_;
    else if (cOperator == pcode__GREATER) 			boolean_ = L_boolean_ > R_boolean_;
    else if (cOperator == pcode__LESSER) 				boolean_ = L_boolean_ < R_boolean_;
    else if (cOperator == pcode__GREATER_EQUAL) boolean_ = L_boolean_ >= R_boolean_;
    else if (cOperator == pcode__LESSER_EQUAL) 	boolean_ = L_boolean_ <= R_boolean_;
    else { runtimeError("unknown operator"); return; }

		if (remove == false) myStack->restoreStack();
 	  myStack->pushBoolean(boolean_); 
#ifdef HAS_CONSOLE
    if (!bSilent) sprintf(acStringOutputBuffer, "%d %s %d --> %d", (t_integer) L_boolean_, c, (t_integer) R_boolean_, (t_integer) boolean_);
#endif

  } else if (RType == pcode__QSTRING){

    if (cOperator == pcode__EQUAL || cOperator == pcode__UNEQUAL){

      boolean_ = !(L_boolean_ == false && R_qstring_->isEmpty()); // special handling for INKEY used
		  if (remove == false) myStack->restoreStack();
		  myStack->pushBoolean(boolean_); 
#ifdef HAS_CONSOLE
      if (!bSilent) sprintf(acStringOutputBuffer, "Unicode");
#endif

    } else if (cOperator == pcode__ADD){
			 int nId = estatics->declare(pcode__QSTRING, 0, false, false);
    	 estatics->setQString_Boolean(nId, L_boolean_, R_qstring_ , 0);
			 myStack->pushEQString(nId);
#ifdef HAS_CONSOLE
      if (!bSilent) sprintf(acStringOutputBuffer, "Unicode");
#endif
     } else { runtimeError("unknown operator"); return; }

  } else if (RType == pcode__CSTRING){

    if (cOperator == pcode__EQUAL || cOperator == pcode__UNEQUAL){

      boolean_ = !(L_boolean_ == false && strcmp("", R_cstring_) == 0); // special handling for INKEY used
		  if (remove == false) myStack->restoreStack();
		  myStack->pushBoolean(boolean_); 
#ifdef HAS_CONSOLE
      if (!bSilent) sprintf(acStringOutputBuffer, "%d %s %-30.30s --> %d", (t_integer) L_boolean_, c, R_cstring_, (t_integer) boolean_);
#endif

    } else if (cOperator == pcode__ADD){
			 int nId = estatics->declare(pcode__CSTRING, 0, false, false);
    	 estatics->setCString_Boolean(nId, L_boolean_, R_cstring_ , 0);
			 myStack->pushECString(nId);
#ifdef HAS_CONSOLE
			 if (!bSilent) sprintf(acStringOutputBuffer, "%d %s \"%-30.30s\" --> \"%-30.30s\"", (t_integer) L_boolean_, c, R_cstring_, estatics->getCString(nId));
#endif
     } else { runtimeError("unknown operator"); return; }

  } else if (RType == pcode__BYTE){
         if (cOperator == pcode__MUL) byte_ = L_boolean_ * R_byte_;
    else if (cOperator == pcode__AND) byte_ = L_boolean_ & R_byte_;
    else if (cOperator == pcode__OR)  byte_ = L_boolean_ | R_byte_;
    else if (cOperator == pcode__XOR) byte_ = L_boolean_ ^ R_byte_;
    else if (cOperator == pcode__IMP) byte_ = !(L_boolean_ != 0 && R_byte_ == 0);
    else if (cOperator == pcode__POWER) byte_ = (t_integer) pow((t_double) L_boolean_, (t_double) R_byte_);
    else if (cOperator == pcode__ADD) byte_ = L_boolean_ + R_byte_;
    else if (cOperator == pcode__SUB) byte_ = L_boolean_ - R_byte_;
    //else if (cOperator == pcode__DIV){ if (R_byte_ == 0){ runtimeError("division by zero", 11); return; } byte_ = L_boolean_ / R_byte_; }
    else if (cOperator == pcode__MOD){ if (R_byte_ == 0){ runtimeError("MOD by zero", 11); return; } byte_ = L_boolean_ % R_byte_; }
    else if (cOperator == pcode__IDIV){ if (R_byte_ == 0){ runtimeError("integer division by zero", 11); return; } byte_ = L_boolean_ / R_byte_; }
    else if (cOperator == pcode__EQUAL) 				byte_ = L_boolean_ == R_byte_;
    else if (cOperator == pcode__EQV) 				byte_ = L_boolean_ == R_byte_;
    else if (cOperator == pcode__UNEQUAL) 			byte_ = L_boolean_ != R_byte_;
    else if (cOperator == pcode__GREATER) 			byte_ = L_boolean_ > R_byte_;
    else if (cOperator == pcode__LESSER) 				byte_ = L_boolean_ < R_byte_;
    else if (cOperator == pcode__GREATER_EQUAL) byte_ = L_boolean_ >= R_byte_;
    else if (cOperator == pcode__LESSER_EQUAL) 	byte_ = L_boolean_ <= R_byte_;
    else { runtimeError("unknown operator"); return; }

		if (remove == false) myStack->restoreStack();
 	  myStack->pushByte(byte_); 
#ifdef HAS_CONSOLE
    if (!bSilent) sprintf(acStringOutputBuffer, "%d %s %d --> %d", (t_integer) L_boolean_, c, (t_integer) R_byte_, (t_integer) byte_);
#endif

  } else if (RType == pcode__SHORT){
         if (cOperator == pcode__MUL) short_ = L_boolean_ * R_short_;
    else if (cOperator == pcode__AND) short_ = L_boolean_ & R_short_;
    else if (cOperator == pcode__OR)  short_ = L_boolean_ | R_short_;
    else if (cOperator == pcode__XOR) short_ = L_boolean_ ^ R_short_;
    else if (cOperator == pcode__IMP) short_ = !(L_boolean_ != 0 && R_short_ == 0);
    else if (cOperator == pcode__POWER) short_ = (t_integer) pow((t_double) L_boolean_, (t_double) R_short_);
    else if (cOperator == pcode__ADD) short_ = L_boolean_ + R_short_;
    else if (cOperator == pcode__SUB) short_ = L_boolean_ - R_short_;
    //else if (cOperator == pcode__DIV){ if (R_short_ == 0){ runtimeError("division by zero", 11); return; } short_ = L_boolean_ / R_short_; }
    else if (cOperator == pcode__MOD){ if (R_short_ == 0){ runtimeError("MOD by zero", 11); return; } short_ = L_boolean_ % R_short_; }
    else if (cOperator == pcode__IDIV){ if (R_short_ == 0){ runtimeError("integer division by zero", 11); return; } short_ = L_boolean_ / R_short_; }
    else if (cOperator == pcode__EQUAL) 				short_ = L_boolean_ == R_short_;
    else if (cOperator == pcode__EQV) 				short_ = L_boolean_ == R_short_;
    else if (cOperator == pcode__UNEQUAL) 			short_ = L_boolean_ != R_short_;
    else if (cOperator == pcode__GREATER) 			short_ = L_boolean_ > R_short_;
    else if (cOperator == pcode__LESSER) 				short_ = L_boolean_ < R_short_;
    else if (cOperator == pcode__GREATER_EQUAL) short_ = L_boolean_ >= R_short_;
    else if (cOperator == pcode__LESSER_EQUAL) 	short_ = L_boolean_ <= R_short_;
    else { runtimeError("unknown operator"); return; }

		if (remove == false) myStack->restoreStack();
    myStack->pushShort(short_); 
#ifdef HAS_CONSOLE
    if (!bSilent) sprintf(acStringOutputBuffer, "%d %s %d --> %d", (t_integer) L_boolean_, c, (t_integer) R_short_, (t_integer) short_);
#endif

  } else if (RType == pcode__INTEGER){
         if (cOperator == pcode__MUL) integer_ = L_boolean_ * R_integer_;
    else if (cOperator == pcode__AND) integer_ = L_boolean_ & R_integer_;
    else if (cOperator == pcode__OR)  integer_ = L_boolean_ | R_integer_;
    else if (cOperator == pcode__XOR) integer_ = L_boolean_ ^ R_integer_;
    else if (cOperator == pcode__IMP) integer_ = !(L_boolean_ != 0 && R_integer_ == 0);
    else if (cOperator == pcode__POWER) integer_ = (t_integer) pow((t_double) L_boolean_, (t_double) R_integer_);
    else if (cOperator == pcode__ADD) integer_ = L_boolean_ + R_integer_;
    else if (cOperator == pcode__SUB) integer_ = L_boolean_ - R_integer_;
    //else if (cOperator == pcode__DIV){ if (R_integer_ == 0){ runtimeError("division by zero", 11); return; } integer_ = L_boolean_ / R_integer_; }
    else if (cOperator == pcode__MOD){ if (R_integer_ == 0){ runtimeError("MOD by zero", 11); return; } integer_ = L_boolean_ % R_integer_; }
    else if (cOperator == pcode__IDIV){ if (R_integer_ == 0){ runtimeError("integer division by zero", 11); return; } integer_ = L_boolean_ / R_integer_; }
    else if (cOperator == pcode__EQUAL) 				integer_ = L_boolean_ == R_integer_;
    else if (cOperator == pcode__EQV) 				integer_ = L_boolean_ == R_integer_;
    else if (cOperator == pcode__UNEQUAL) 			integer_ = L_boolean_ != R_integer_;
    else if (cOperator == pcode__GREATER) 			integer_ = L_boolean_ > R_integer_;
    else if (cOperator == pcode__LESSER) 				integer_ = L_boolean_ < R_integer_;
    else if (cOperator == pcode__GREATER_EQUAL) integer_ = L_boolean_ >= R_integer_;
    else if (cOperator == pcode__LESSER_EQUAL) 	integer_ = L_boolean_ <= R_integer_;
    else { runtimeError("unknown operator"); return; }

		if (remove == false) myStack->restoreStack();
 	  myStack->pushInteger(integer_); 
#ifdef HAS_CONSOLE
    if (!bSilent) sprintf(acStringOutputBuffer, "%d %s %d --> %d", (t_integer) L_boolean_, c, R_integer_, integer_);
#endif

  } else if (RType ==  pcode__LONG){
         if (cOperator == pcode__MUL) long_ = L_boolean_ * R_long_;
    else if (cOperator == pcode__AND) long_ = L_boolean_ & R_long_;
    else if (cOperator == pcode__OR)  long_ = L_boolean_ | R_long_;
    else if (cOperator == pcode__XOR) long_ = L_boolean_ ^ R_long_;
    else if (cOperator == pcode__IMP) long_ = !(L_boolean_ != 0 && R_long_ == 0);
    else if (cOperator == pcode__POWER) long_ = (t_long) pow((t_double) L_boolean_, (t_double) R_long_);
    else if (cOperator == pcode__ADD) long_ = L_boolean_ + R_long_;
    else if (cOperator == pcode__SUB) long_ = L_boolean_ - R_long_;
    //else if (cOperator == pcode__DIV){ if (R_long_ == 0){ runtimeError("division by zero", 11); return; } long_ = L_boolean_ / R_long_; }
    else if (cOperator == pcode__MOD){ if (R_long_ == 0){ runtimeError("MOD by zero", 11); return; } long_ = L_boolean_ % R_long_; }
    else if (cOperator == pcode__IDIV){ if (R_long_ == 0){ runtimeError("integer division by zero", 11); return; } long_ = L_boolean_ / R_long_; }
    else if (cOperator == pcode__EQUAL) 				long_ = L_boolean_ == R_long_;
    else if (cOperator == pcode__EQV) 				long_ = L_boolean_ == R_long_;
    else if (cOperator == pcode__UNEQUAL) 			long_ = L_boolean_ != R_long_;
    else if (cOperator == pcode__GREATER) 			long_ = L_boolean_ > R_long_;
    else if (cOperator == pcode__LESSER) 				long_ = L_boolean_ < R_long_;
    else if (cOperator == pcode__GREATER_EQUAL) long_ = L_boolean_ >= R_long_;
    else if (cOperator == pcode__LESSER_EQUAL) 	long_ = L_boolean_ <= R_long_;
    else { runtimeError("unknown operator"); return; }

		if (remove == false) myStack->restoreStack();
 	  myStack->pushLong(long_); 
#ifdef HAS_CONSOLE
    if (!bSilent) sprintf(acStringOutputBuffer, "%d %s %I64d --> %I64d", (t_integer) L_boolean_, c, R_long_, long_);
#endif

  } else if (RType == pcode__SINGLE){
         if (cOperator == pcode__MUL) single_ = L_boolean_ * R_single_;
    else if (cOperator == pcode__AND) single_ = L_boolean_ & (t_long) R_single_;
    else if (cOperator == pcode__OR)  single_ = L_boolean_ | (t_long) R_single_;
    else if (cOperator == pcode__XOR) single_ = L_boolean_ ^ (t_long) R_single_;
    else if (cOperator == pcode__IMP) single_ = !(L_boolean_ != 0 && R_single_ == 0);
    else if (cOperator == pcode__POWER) single_ = pow((t_double) L_boolean_, (t_double) R_single_);
    else if (cOperator == pcode__ADD) single_ = L_boolean_ + R_single_;
    else if (cOperator == pcode__SUB) single_ = L_boolean_ - R_single_;
    //else if (cOperator == pcode__DIV){ if (R_single_ == 0){ runtimeError("division by zero", 11); return; } single_ = L_boolean_ / R_single_; }
    else if (cOperator == pcode__MOD){ if (R_double_ == 0){ runtimeError("MOD by zero", 11); return; } single_ = L_boolean_ % (t_long) R_single_; }
    else if (cOperator == pcode__IDIV){ if (R_single_ == 0){ runtimeError("integer division by zero", 11); return; } single_ = (t_long) (L_boolean_ / R_single_); }
    else if (cOperator == pcode__EQUAL) 				single_ = L_boolean_ == R_single_;
    else if (cOperator == pcode__EQV) 				single_ = L_boolean_ == R_single_;
    else if (cOperator == pcode__UNEQUAL) 			single_ = L_boolean_ != R_single_;
    else if (cOperator == pcode__GREATER) 			single_ = L_boolean_ > R_single_;
    else if (cOperator == pcode__LESSER) 				single_ = L_boolean_ < R_single_;
    else if (cOperator == pcode__GREATER_EQUAL) single_ = L_boolean_ >= R_single_;
    else if (cOperator == pcode__LESSER_EQUAL) 	single_ = L_boolean_ <= R_single_;
    else { runtimeError("unknown operator"); return; }

		if (remove == false) myStack->restoreStack();
    myStack->pushSingle(single_); 
#ifdef HAS_CONSOLE
    if (!bSilent) sprintf(acStringOutputBuffer, "%d %s %.6f --> %.6f", (t_integer) L_boolean_, c, R_single_, single_);
#endif

  } else if (RType == pcode__DOUBLE){
         if (cOperator == pcode__MUL) double_ = L_boolean_ * R_double_;
    else if (cOperator == pcode__AND) double_ = L_boolean_ & (t_long) R_double_;
    else if (cOperator == pcode__OR)  double_ = L_boolean_ | (t_long) R_double_;
    else if (cOperator == pcode__XOR) double_ = L_boolean_ ^ (t_long) R_double_;
    else if (cOperator == pcode__IMP) double_ = !(L_boolean_ != 0 && R_double_ == 0);
    else if (cOperator == pcode__POWER) double_ = pow((t_double) L_boolean_, R_double_);
    else if (cOperator == pcode__ADD) double_ = L_boolean_ + R_double_;
    else if (cOperator == pcode__SUB) double_ = L_boolean_ - R_double_;
    //else if (cOperator == pcode__DIV){ if (R_double_ == 0){ runtimeError("division by zero", 11); return; } double_ = L_boolean_ / R_double_; }
    else if (cOperator == pcode__MOD){ if (R_double_ == 0){ runtimeError("MOD by zero", 11); return; } double_ = L_boolean_ % (t_long) R_double_; }
    else if (cOperator == pcode__IDIV){ if (R_double_ == 0){ runtimeError("integer division by zero", 11); return; } double_ = (t_long) (L_boolean_ / R_double_); }
    else if (cOperator == pcode__EQUAL) 				double_ = L_boolean_ == R_double_;
    else if (cOperator == pcode__EQV) 				double_ = L_boolean_ == R_double_;
    else if (cOperator == pcode__UNEQUAL) 			double_ = L_boolean_ != R_double_;
    else if (cOperator == pcode__GREATER) 			double_ = L_boolean_ > R_double_;
    else if (cOperator == pcode__LESSER) 				double_ = L_boolean_ < R_double_;
    else if (cOperator == pcode__GREATER_EQUAL) double_ = L_boolean_ >= R_double_;
    else if (cOperator == pcode__LESSER_EQUAL) 	double_ = L_boolean_ <= R_double_;
    else { runtimeError("unknown operator"); return; }

		if (remove == false) myStack->restoreStack();
    myStack->pushDouble(double_); 
#ifdef HAS_CONSOLE
    if (!bSilent) sprintf(acStringOutputBuffer, "%d %s %.6f --> %.6f", (t_integer) L_boolean_, c, R_double_, double_);
#endif

  } else if (RType == pcode__CURRENCY){

    t_currency t(L_boolean_, 0);

         if (cOperator == pcode__MUL) currency_.setValue(t.bc() * R_currency_.bc(), t.bc() * R_currency_.ad());
    else if (cOperator == pcode__AND) currency_.setValue(t.bc() & R_currency_.bc(), t.ad() & R_currency_.ad());
    else if (cOperator == pcode__OR)  currency_.setValue(t.bc() | R_currency_.bc(), t.ad() | R_currency_.ad());
    else if (cOperator == pcode__XOR) currency_.setValue(t.bc() ^ R_currency_.bc(), t.ad() ^ R_currency_.ad());
    else if (cOperator == pcode__IMP) currency_.setValue(!(t.getValue() != 0 && R_currency_.getValue() == 0), 0);
    else if (cOperator == pcode__POWER) currency_.setValue((t_long) pow((t_double) t.bc(), (t_double) R_currency_.toDouble()), 0);
    else if (cOperator == pcode__ADD) currency_.setValue(t.bc() + R_currency_.bc(), t.ad() + R_currency_.ad());
    else if (cOperator == pcode__SUB) currency_.setValue(t.bc() - R_currency_.bc(), t.ad() - R_currency_.ad());
    //else if (cOperator == pcode__DIV){ if (R_currency_.getValue() == 0){ runtimeError("division by zero", 11); return; } currency_.setValue(t.bc() / R_currency_.bc(), t.ad() / R_currency_.ad()); }
    else if (cOperator == pcode__MOD){ if (R_currency_.getValue() == 0){ runtimeError("MOD by zero", 11); return; } currency_.setValue(t.bc() % R_currency_.bc(), t.ad() % R_currency_.ad()); }
    else if (cOperator == pcode__IDIV){ if (R_currency_.getValue() == 0){ runtimeError("integer division by zero", 11); return; } currency_.setValue(t.bc() / R_currency_.bc(), t.ad() / R_currency_.ad()); }
    else if (cOperator == pcode__EQUAL) 				currency_.setValue(t.getValue() == R_currency_.getValue(), 0);
    else if (cOperator == pcode__EQV) 				currency_.setValue(t.getValue() == R_currency_.getValue(), 0);
    else if (cOperator == pcode__UNEQUAL) 			currency_.setValue(t.getValue() != R_currency_.getValue(), 0);
    else if (cOperator == pcode__GREATER) 			currency_.setValue(t.getValue() > R_currency_.getValue(), 0);
    else if (cOperator == pcode__LESSER) 				currency_.setValue(t.getValue() < R_currency_.getValue(), 0);
    else if (cOperator == pcode__GREATER_EQUAL) currency_.setValue(t.getValue() >= R_currency_.getValue(), 0);
    else if (cOperator == pcode__LESSER_EQUAL) currency_.setValue(t.getValue() <= R_currency_.getValue(), 0);
    else { runtimeError("unknown operator"); return; }

		if (remove == false) myStack->restoreStack();
 	  myStack->pushCurrency(currency_); 
#ifdef HAS_CONSOLE
    if (!bSilent) sprintf(acStringOutputBuffer, "%d %s %s --> %s", (t_integer) t.bc(), c, R_currency_.toCString(), currency_.toCString2());
#endif
  }
  
		// pcode__QSTRING ***
  } else if (LType == pcode__QSTRING){
  if (RType == pcode__QSTRING){
    		 if (cOperator == pcode__ADD){

					 int nId = estatics->declare(pcode__QSTRING, 0, false, false);
    			 estatics->setQString_QString(nId, L_qstring_, R_qstring_, 0);
					 myStack->pushEQString(nId);
#ifdef HAS_CONSOLE
				   if (!bSilent) sprintf(acStringOutputBuffer, "Unicode");
#endif

				 } else if (cOperator == pcode__EQV || cOperator == pcode__EQUAL){
						boolean_ = L_qstring_->compare(*R_qstring_) == 0;
						if (remove == false) myStack->restoreStack();
						myStack->pushBoolean(boolean_);
#ifdef HAS_CONSOLE
				   if (!bSilent) sprintf(acStringOutputBuffer, "Unicode");
#endif
				 } else if (cOperator == pcode__UNEQUAL){
						boolean_ = L_qstring_->compare(*R_qstring_) != 0;
						if (remove == false) myStack->restoreStack();
						myStack->pushBoolean(boolean_); 
#ifdef HAS_CONSOLE
				   if (!bSilent) sprintf(acStringOutputBuffer, "Unicode");
#endif

				 } else if (cOperator == pcode__GREATER){
    				boolean_ = L_qstring_->compare(*R_qstring_) > 0;
    				if (remove == false) myStack->restoreStack();
  	    	  myStack->pushBoolean(boolean_); 
#ifdef HAS_CONSOLE
				   if (!bSilent) sprintf(acStringOutputBuffer, "Unicode");
#endif

				 } else if (cOperator == pcode__LESSER){
    				boolean_ = L_qstring_->compare(*R_qstring_) < 0;
    				if (remove == false) myStack->restoreStack();
  	    	  myStack->pushBoolean(boolean_); 
#ifdef HAS_CONSOLE
				   if (!bSilent) sprintf(acStringOutputBuffer, "Unicode");
#endif

				 } else if (cOperator == pcode__GREATER_EQUAL){
    				boolean_ = L_qstring_->compare(*R_qstring_) >= 0;
    				if (remove == false) myStack->restoreStack();
  	    	  myStack->pushBoolean(boolean_); 
#ifdef HAS_CONSOLE
				   if (!bSilent) sprintf(acStringOutputBuffer, "Unicode");
#endif

				 } else if (cOperator == pcode__LESSER_EQUAL){
    				boolean_ = L_qstring_->compare(*R_qstring_) <= 0;
    				if (remove == false) myStack->restoreStack();
  	    	  myStack->pushBoolean(boolean_); 
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "Unicode");
#endif
				 } else if (cOperator == pcode__LIKE){
    				boolean_ = myFunction->fLIKE(L_qstring_, R_qstring_, bOptionComparyBinary ? 0 : 1);
    				if (remove == false) myStack->restoreStack();
  	    	  myStack->pushBoolean(boolean_); 
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "Unicode");
#endif
 				 } else { runtimeError("unknown operator"); return; } // 
//
  } else if (RType == pcode__CSTRING){
    		 if (cOperator == pcode__ADD){
					 int nId = estatics->declare(pcode__QSTRING, 0, false, false);
    			 estatics->setQString_CString(nId, L_qstring_, R_cstring_, 0);
					 myStack->pushEQString(nId);
#ifdef HAS_CONSOLE
           if (!bSilent) sprintf(acStringOutputBuffer, "Unicode");
#endif

				 } else if (cOperator == pcode__EQV || cOperator == pcode__EQUAL){
						boolean_ = L_qstring_->compare(R_cstring_) == 0;
						if (remove == false) myStack->restoreStack();
						myStack->pushBoolean(boolean_);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "Unicode");
#endif
				 } else if (cOperator == pcode__UNEQUAL){
						boolean_ = L_qstring_->compare(R_cstring_) != 0;
						if (remove == false) myStack->restoreStack();
						myStack->pushBoolean(boolean_); 
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "Unicode");
#endif

				 } else if (cOperator == pcode__GREATER){
    				boolean_ = L_qstring_->compare(R_cstring_) > 0;
    				if (remove == false) myStack->restoreStack();
  	    	  myStack->pushBoolean(boolean_); 
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "Unicode");
#endif

				 } else if (cOperator == pcode__LESSER){
    				boolean_ = L_qstring_->compare(R_cstring_) < 0;
    				if (remove == false) myStack->restoreStack();
  	    	  myStack->pushBoolean(boolean_); 
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "Unicode");
#endif

				 } else if (cOperator == pcode__GREATER_EQUAL){
    				boolean_ = L_qstring_->compare(R_cstring_) >= 0;
    				if (remove == false) myStack->restoreStack();
  	    	  myStack->pushBoolean(boolean_); 
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "Unicode");
#endif

				 } else if (cOperator == pcode__LESSER_EQUAL){
    				boolean_ = L_qstring_->compare(R_cstring_) <= 0;
    				if (remove == false) myStack->restoreStack();
  	    	  myStack->pushBoolean(boolean_); 
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "Unicode");
#endif
				 } else if (cOperator == pcode__LIKE){
    				boolean_ = myFunction->fLIKE(L_qstring_, &QString(R_cstring_), bOptionComparyBinary ? 0 : 1);
    				if (remove == false) myStack->restoreStack();
  	    	  myStack->pushBoolean(boolean_); 
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "Unicode");
#endif
 				 } else { runtimeError("unknown operator"); return; } // 

  } else if (RType == pcode__BOOLEAN){
    		 if (cOperator == pcode__ADD){

					 int nId = estatics->declare(pcode__QSTRING, 0, false, false);
    			 estatics->setQString_Boolean(nId, L_qstring_, R_boolean_, 0);
					 myStack->pushEQString(nId);
#ifdef HAS_CONSOLE
           if (!bSilent) sprintf(acStringOutputBuffer, "Unicode");
#endif
 				 } else { runtimeError("unknown operator"); return; }
  } else if (RType == pcode__BYTE){
    		 if (cOperator == pcode__ADD){
					 int nId = estatics->declare(pcode__QSTRING, 0, false, false);
    			 estatics->setQString_Byte(nId, L_qstring_, R_byte_, 0);
					 myStack->pushEQString(nId);
#ifdef HAS_CONSOLE
           if (!bSilent) sprintf(acStringOutputBuffer, "Unicode");
#endif
 				 } else { runtimeError("unknown operator"); return; }
  } else if (RType == pcode__SHORT){
    		 if (cOperator == pcode__ADD){
					 int nId = estatics->declare(pcode__QSTRING, 0, false, false);
    			 estatics->setQString_Short(nId, L_qstring_, R_short_, 0);
					 myStack->pushEQString(nId);
#ifdef HAS_CONSOLE
           if (!bSilent) sprintf(acStringOutputBuffer, "Unicode");
#endif
 				 } else { runtimeError("unknown operator"); return; }
  } else if (RType == pcode__INTEGER){
    		 if (cOperator == pcode__ADD){
					 int nId = estatics->declare(pcode__QSTRING, 0, false, false);
    			 estatics->setQString_Integer(nId, L_qstring_, R_integer_, 0);
					 myStack->pushEQString(nId);
#ifdef HAS_CONSOLE
           if (!bSilent) sprintf(acStringOutputBuffer, "Unicode");
#endif
 				 } else { runtimeError("unknown operator"); return; }
  } else if (RType ==  pcode__LONG){
    		 if (cOperator == pcode__ADD){

					 int nId = estatics->declare(pcode__QSTRING, 0, false, false);
    			 estatics->setQString_Long(nId, L_qstring_, (t_long) R_long_, 0);
					 myStack->pushEQString(nId);
#ifdef HAS_CONSOLE
           if (!bSilent) sprintf(acStringOutputBuffer, "Unicode");
#endif
 				 } else { runtimeError("unknown operator"); return; }
  } else if (RType == pcode__SINGLE){
    		 if (cOperator == pcode__ADD){

					 int nId = estatics->declare(pcode__QSTRING, 0, false, false);
    			 estatics->setQString_Single(nId, L_qstring_, R_single_, 0);
					 myStack->pushEQString(nId);
#ifdef HAS_CONSOLE
           if (!bSilent) sprintf(acStringOutputBuffer, "Unicode");
#endif
 				 } else { runtimeError("unknown operator"); return; }
  } else if (RType == pcode__DOUBLE){
    		 if (cOperator == pcode__ADD){

					 int nId = estatics->declare(pcode__QSTRING, 0, false, false);
    			 estatics->setQString_Double(nId, L_qstring_, R_double_, 0);
					 myStack->pushEQString(nId);
#ifdef HAS_CONSOLE
           if (!bSilent) sprintf(acStringOutputBuffer, "Unicode");
#endif
 				 } else { runtimeError("unknown operator"); return; }

  } else if (RType ==  pcode__CURRENCY){
    		 if (cOperator == pcode__ADD){

					 int nId = estatics->declare(pcode__QSTRING, 0, false, false);
    			 estatics->setQString_Currency(nId, L_qstring_, R_currency_, 0);
					 myStack->pushEQString(nId);
#ifdef HAS_CONSOLE
           if (!bSilent) sprintf(acStringOutputBuffer, "Unicode");
#endif
 				 } else { runtimeError("unknown operator"); return; }

  } else if (RType ==  pcode__DATE){
    		 if (cOperator == pcode__ADD){

					 int nId = estatics->declare(pcode__QSTRING, 0, false, false);
    			 estatics->setQString_Date(nId, L_qstring_, R_date_, 0);
					 myStack->pushEQString(nId);
#ifdef HAS_CONSOLE
           if (!bSilent) sprintf(acStringOutputBuffer, "Unicode");
#endif
 				 } else { runtimeError("unknown operator"); return; }

  }
 
		// pcode__CSTRING ***
  } else if (LType == pcode__CSTRING){
  if (RType == pcode__CSTRING){
    		 if (cOperator == pcode__ADD){

					 int nId = estatics->declare(pcode__CSTRING, 0, false, false);
    			 estatics->setCString_CString(nId, L_cstring_, R_cstring_, 0);
					 myStack->pushECString(nId);
#ifdef HAS_CONSOLE
				   if (!bSilent) sprintf(acStringOutputBuffer, "\"%-30.30s\" %s \"%-30.30s\" --> \"%-30.30s\"", L_cstring_, c, R_cstring_, estatics->getCString(nId));
#endif

				 } else if (cOperator == pcode__EQV || cOperator == pcode__EQUAL){
						boolean_ = strcmp(L_cstring_, R_cstring_) == 0;
						if (remove == false) myStack->restoreStack();
						myStack->pushBoolean(boolean_);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%-30.30s %s %-30.30s --> %d", L_cstring_, c, R_cstring_, (t_integer) boolean_);
#endif
				 } else if (cOperator == pcode__UNEQUAL){
						boolean_ = strcmp(L_cstring_, R_cstring_) != 0;
						if (remove == false) myStack->restoreStack();
						myStack->pushBoolean(boolean_); 
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%-30.30s %s %-30.30s --> %d", L_cstring_, c, R_cstring_, (t_integer) boolean_);
#endif

				 } else if (cOperator == pcode__GREATER){
    				boolean_ = strcmp(L_cstring_, R_cstring_) > 0;
    				if (remove == false) myStack->restoreStack();
  	    	  myStack->pushBoolean(boolean_); 
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%-30.30s %s %-30.30s --> %d", L_cstring_, c, R_cstring_, (t_integer) boolean_);
#endif

				 } else if (cOperator == pcode__LESSER){
    				boolean_ = strcmp(L_cstring_, R_cstring_) < 0;
    				if (remove == false) myStack->restoreStack();
  	    	  myStack->pushBoolean(boolean_); 
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%-30.30s %s %-30.30s --> %d", L_cstring_, c, R_cstring_, (t_integer) boolean_);
#endif

				 } else if (cOperator == pcode__GREATER_EQUAL){
    				boolean_ = strcmp(L_cstring_, R_cstring_) >= 0;
    				if (remove == false) myStack->restoreStack();
  	    	  myStack->pushBoolean(boolean_); 
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%-30.30s %s %-30.30s --> %d", L_cstring_, c, R_cstring_, (t_integer) boolean_);
#endif

				 } else if (cOperator == pcode__LESSER_EQUAL){
    				boolean_ = strcmp(L_cstring_, R_cstring_) <= 0;
    				if (remove == false) myStack->restoreStack();
  	    	  myStack->pushBoolean(boolean_); 
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%-30.30s %s %-30.30s --> %d", L_cstring_, c, R_cstring_, (t_integer) boolean_);
#endif
				 } else if (cOperator == pcode__LIKE){
    				boolean_ = myFunction->fLIKE(L_cstring_, R_cstring_, bOptionComparyBinary ? 0 : 1);
    				if (remove == false) myStack->restoreStack();
  	    	  myStack->pushBoolean(boolean_); 
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%-30.30s %s %-30.30s --> %d", L_cstring_, c, R_cstring_, (t_integer) boolean_);
#endif
 				 } else { runtimeError("unknown operator"); return; } // 
//
  } else if (RType == pcode__QSTRING){
    QByteArray a = R_qstring_->toLocal8Bit();
    char *ac = a.data();
    		 if (cOperator == pcode__ADD){
					 int nId = estatics->declare(pcode__CSTRING, 0, false, false);
    			 estatics->setCString_CString(nId, L_cstring_, ac, 0);
					 myStack->pushECString(nId);
#ifdef HAS_CONSOLE
				   if (!bSilent) sprintf(acStringOutputBuffer, "\"%-30.30s\" %s \"%-30.30s\" --> \"%-30.30s\"", L_cstring_, c, R_cstring_, estatics->getCString(nId));
#endif

				 } else if (cOperator == pcode__EQV || cOperator == pcode__EQUAL){
						boolean_ = strcmp(L_cstring_, ac) == 0;
						if (remove == false) myStack->restoreStack();
						myStack->pushBoolean(boolean_);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%-30.30s %s %-30.30s --> %d", L_cstring_, c, R_cstring_, (t_integer) boolean_);
#endif
				 } else if (cOperator == pcode__UNEQUAL){
						boolean_ = strcmp(L_cstring_, ac) != 0;
						if (remove == false) myStack->restoreStack();
						myStack->pushBoolean(boolean_); 
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%-30.30s %s %-30.30s --> %d", L_cstring_, c, R_cstring_, (t_integer) boolean_);
#endif

				 } else if (cOperator == pcode__GREATER){
    				boolean_ = strcmp(L_cstring_, ac) > 0;
    				if (remove == false) myStack->restoreStack();
  	    	  myStack->pushBoolean(boolean_); 
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%-30.30s %s %-30.30s --> %d", L_cstring_, c, R_cstring_, (t_integer) boolean_);
#endif

				 } else if (cOperator == pcode__LESSER){
    				boolean_ = strcmp(L_cstring_, ac) < 0;
    				if (remove == false) myStack->restoreStack();
  	    	  myStack->pushBoolean(boolean_); 
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%-30.30s %s %-30.30s --> %d", L_cstring_, c, R_cstring_, (t_integer) boolean_);
#endif

				 } else if (cOperator == pcode__GREATER_EQUAL){
    				boolean_ = strcmp(L_cstring_, ac) >= 0;
    				if (remove == false) myStack->restoreStack();
  	    	  myStack->pushBoolean(boolean_); 
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%-30.30s %s %-30.30s --> %d", L_cstring_, c, R_cstring_, (t_integer) boolean_);
#endif

				 } else if (cOperator == pcode__LESSER_EQUAL){
    				boolean_ = strcmp(L_cstring_, ac) <= 0;
    				if (remove == false) myStack->restoreStack();
  	    	  myStack->pushBoolean(boolean_); 
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%-30.30s %s %-30.30s --> %d", L_cstring_, c, R_cstring_, (t_integer) boolean_);
#endif
				 } else if (cOperator == pcode__LIKE){
    				boolean_ = myFunction->fLIKE(L_cstring_, ac, bOptionComparyBinary ? 0 : 1);
    				if (remove == false) myStack->restoreStack();
  	    	  myStack->pushBoolean(boolean_); 
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%-30.30s %s %-30.30s --> %d", L_cstring_, c, R_cstring_, (t_integer) boolean_);
#endif
 				 } else { runtimeError("unknown operator"); return; } // 

  } else if (RType == pcode__BOOLEAN){
    		 if (cOperator == pcode__ADD){

					 int nId = estatics->declare(pcode__CSTRING, 0, false, false);
    			 estatics->setCString_Boolean(nId, L_cstring_, R_boolean_, 0);
					 myStack->pushECString(nId);
#ifdef HAS_CONSOLE
           if (!bSilent) sprintf(acStringOutputBuffer, "\"%-30.30s\" %s %s --> \"%-30.30s\"", L_cstring_, c, R_boolean_ ? "TRUE" : "FALSE", estatics->getCString(nId));
#endif
 				 } else { runtimeError("unknown operator"); return; }
  } else if (RType == pcode__BYTE){
    		 if (cOperator == pcode__ADD){
					 int nId = estatics->declare(pcode__CSTRING, 0, false, false);
    			 estatics->setCString_Byte(nId, L_cstring_, R_byte_, 0);
					 myStack->pushECString(nId);
#ifdef HAS_CONSOLE
				   if (!bSilent) sprintf(acStringOutputBuffer, "\"%-30.30s\" %s %d --> \"%-30.30s\"", L_cstring_, c, (t_integer) R_byte_, estatics->getCString(nId));
#endif
 				 } else { runtimeError("unknown operator"); return; }
  } else if (RType == pcode__SHORT){
    		 if (cOperator == pcode__ADD){
					 int nId = estatics->declare(pcode__CSTRING, 0, false, false);
    			 estatics->setCString_Short(nId, L_cstring_, R_short_, 0);
					 myStack->pushECString(nId);
#ifdef HAS_CONSOLE
				   if (!bSilent) sprintf(acStringOutputBuffer, "\"%-30.30s\" %s %d --> \"%-30.30s\"", L_cstring_, c, R_short_, estatics->getCString(nId));
#endif
 				 } else { runtimeError("unknown operator"); return; }
  } else if (RType == pcode__INTEGER){
    		 if (cOperator == pcode__ADD){
					 int nId = estatics->declare(pcode__CSTRING, 0, false, false);
    			 estatics->setCString_Integer(nId, L_cstring_, R_integer_, 0);
					 myStack->pushECString(nId);
#ifdef HAS_CONSOLE
				   if (!bSilent) sprintf(acStringOutputBuffer, "\"%-30.30s\" %s %d --> \"%-30.30s\"", L_cstring_, c, R_integer_, estatics->getCString(nId));
#endif
 				 } else { runtimeError("unknown operator"); return; }
  } else if (RType ==  pcode__LONG){
    		 if (cOperator == pcode__ADD){

					 int nId = estatics->declare(pcode__CSTRING, 0, false, false);
    			 estatics->setCString_Long(nId, L_cstring_, (t_long) R_long_, 0);
					 myStack->pushECString(nId);
#ifdef HAS_CONSOLE
				   if (!bSilent) sprintf(acStringOutputBuffer, "\"%-30.30s\" %s %I64d --> \"%-30.30s\"", L_cstring_, c, R_long_, estatics->getCString(nId));
#endif
 				 } else { runtimeError("unknown operator"); return; }
  } else if (RType == pcode__SINGLE){
    		 if (cOperator == pcode__ADD){

					 int nId = estatics->declare(pcode__CSTRING, 0, false, false);
    			 estatics->setCString_Single(nId, L_cstring_, R_single_, 0);
					 myStack->pushECString(nId);
#ifdef HAS_CONSOLE
				   if (!bSilent) sprintf(acStringOutputBuffer, "\"%-30.30s\" %s %.6f --> \"%-30.30s\"", L_cstring_, c, R_single_, estatics->getCString(nId));
#endif
 				 } else { runtimeError("unknown operator"); return; }
  } else if (RType == pcode__DOUBLE){
    		 if (cOperator == pcode__ADD){

					 int nId = estatics->declare(pcode__CSTRING, 0, false, false);
    			 estatics->setCString_Double(nId, L_cstring_, R_double_, 0);
					 myStack->pushECString(nId);
#ifdef HAS_CONSOLE
				   if (!bSilent) sprintf(acStringOutputBuffer, "\"%-30.30s\" %s %.6f --> \"%-30.30s\"", L_cstring_, c, R_double_, estatics->getCString(nId));
#endif
 				 } else { runtimeError("unknown operator"); return; }

  } else if (RType ==  pcode__CURRENCY){
    		 if (cOperator == pcode__ADD){

					 int nId = estatics->declare(pcode__CSTRING, 0, false, false);
    			 estatics->setCString_Currency(nId, L_cstring_, R_currency_, 0);
					 myStack->pushECString(nId);
#ifdef HAS_CONSOLE
          if (!bSilent) sprintf(acStringOutputBuffer, "\"%-30.30s\" %s %s --> \"%-30.30s\"", L_cstring_, c, R_currency_.toCString(), estatics->getCString(nId));
#endif
 				 } else { runtimeError("unknown operator"); return; }

  } else if (RType ==  pcode__DATE){
    		 if (cOperator == pcode__ADD){

					 int nId = estatics->declare(pcode__CSTRING, 0, false, false);
    			 estatics->setCString_Date(nId, L_cstring_, R_date_, 0);
					 myStack->pushECString(nId);
#ifdef HAS_CONSOLE
          if (!bSilent) sprintf(acStringOutputBuffer, "\"%-30.30s\" %s %s --> \"%-30.30s\"", L_cstring_, c, R_date_.toCString(), estatics->getCString(nId));
#endif
 				 } else { runtimeError("unknown operator"); return; }

  }

	// pcode__BYTE ***
  } else if (LType == pcode__BYTE){
  if (RType == pcode__BOOLEAN){
         if (cOperator == pcode__MUL) integer_ = L_byte_ * R_boolean_;
    else if (cOperator == pcode__AND) integer_ = L_byte_ & R_boolean_;
    else if (cOperator == pcode__OR)  integer_ = L_byte_ | R_boolean_;
    else if (cOperator == pcode__XOR) integer_ = L_byte_ ^ R_boolean_;
    else if (cOperator == pcode__IMP) integer_ = !(L_byte_ != 0 && R_boolean_ == 0);
    else if (cOperator == pcode__POWER) integer_ = (t_integer) pow((t_double) L_byte_, (t_double) R_boolean_);
    else if (cOperator == pcode__ADD) integer_ = L_byte_ + R_boolean_;
    else if (cOperator == pcode__SUB) integer_ = L_byte_ - R_boolean_;
    //else if (cOperator == pcode__DIV){ if (R_boolean_ == 0){ runtimeError("division by zero", 11); return; } integer_ = L_byte_ / R_boolean_; }
    else if (cOperator == pcode__MOD){ if (R_boolean_ == 0){ runtimeError("MOD by zero", 11); return; } integer_ = L_byte_ % R_boolean_; }
    else if (cOperator == pcode__IDIV){ if (R_boolean_ == 0){ runtimeError("integer division by zero", 11); return; } integer_ = L_byte_ / R_boolean_; }
    else if (cOperator == pcode__EQUAL) 				integer_ = L_byte_ == R_boolean_;
    else if (cOperator == pcode__EQV) 				integer_ = L_byte_ == R_boolean_;
    else if (cOperator == pcode__UNEQUAL) 			integer_ = L_byte_ != R_boolean_;
    else if (cOperator == pcode__GREATER) 			integer_ = L_byte_ > R_boolean_;
    else if (cOperator == pcode__LESSER) 				integer_ = L_byte_ < R_boolean_;
    else if (cOperator == pcode__GREATER_EQUAL) integer_ = L_byte_ >= R_boolean_;
    else if (cOperator == pcode__LESSER_EQUAL) 	integer_ = L_byte_ <= R_boolean_;
    else { runtimeError("unknown operator"); return; }

		if (remove == false) myStack->restoreStack();
 	  myStack->pushInteger(integer_); 
#ifdef HAS_CONSOLE
    if (!bSilent) sprintf(acStringOutputBuffer, "%d %s %d --> %d", (t_integer) L_byte_, c, (t_integer) R_boolean_, integer_);
#endif

  } else if (RType == pcode__QSTRING){

     if (cOperator == pcode__ADD){
			 int nId = estatics->declare(pcode__QSTRING, 0, false, false);
    	 estatics->setQString_Byte(nId, L_byte_, R_qstring_ , 0);
			 myStack->pushEQString(nId);
#ifdef HAS_CONSOLE
			 if (!bSilent) sprintf(acStringOutputBuffer, "Unicode");
#endif
     } else { runtimeError("unknown operator"); return; }

  } else if (RType == pcode__CSTRING){

     if (cOperator == pcode__ADD){
			 int nId = estatics->declare(pcode__CSTRING, 0, false, false);
    	 estatics->setCString_Byte(nId, L_byte_, R_cstring_ , 0);
			 myStack->pushECString(nId);
#ifdef HAS_CONSOLE
			 if (!bSilent) sprintf(acStringOutputBuffer, "%d %s \"%-30.30s\" --> \"%-30.30s\"", (t_integer) L_byte_, c, R_cstring_, estatics->getCString(nId));
#endif
     } else { runtimeError("unknown operator"); return; }

  } else if (RType == pcode__BYTE){
         if (cOperator == pcode__MUL) integer_ = L_byte_ * R_byte_;
    else if (cOperator == pcode__AND) integer_ = L_byte_ & R_byte_;
    else if (cOperator == pcode__OR)  integer_ = L_byte_ | R_byte_;
    else if (cOperator == pcode__XOR) integer_ = L_byte_ ^ R_byte_;
    else if (cOperator == pcode__IMP) integer_ = !(L_byte_ != 0 && R_byte_ == 0);
    else if (cOperator == pcode__POWER) integer_ = (t_integer) pow((t_double) L_byte_, (t_double) R_byte_);
    else if (cOperator == pcode__ADD) integer_ = L_byte_ + R_byte_;
    else if (cOperator == pcode__SUB) integer_ = L_byte_ - R_byte_;
    //else if (cOperator == pcode__DIV){ if (R_byte_ == 0){ runtimeError("division by zero", 11); return; } integer_ = L_byte_ / R_byte_; }
    else if (cOperator == pcode__MOD){ if (R_byte_ == 0){ runtimeError("MOD by zero", 11); return; } integer_ = L_byte_ % R_byte_; }
    else if (cOperator == pcode__IDIV){ if (R_byte_ == 0){ runtimeError("integer division by zero", 11); return; } integer_ = L_byte_ / R_byte_; }
    else if (cOperator == pcode__EQUAL) 				integer_ = L_byte_ == R_byte_;
    else if (cOperator == pcode__EQV) 				integer_ = L_byte_ == R_byte_;
    else if (cOperator == pcode__UNEQUAL) 			integer_ = L_byte_ != R_byte_;
    else if (cOperator == pcode__GREATER) 			integer_ = L_byte_ > R_byte_;
    else if (cOperator == pcode__LESSER) 				integer_ = L_byte_ < R_byte_;
    else if (cOperator == pcode__GREATER_EQUAL) integer_ = L_byte_ >= R_byte_;
    else if (cOperator == pcode__LESSER_EQUAL) 	integer_ = L_byte_ <= R_byte_;
    else { runtimeError("unknown operator"); return; }

		if (remove == false) myStack->restoreStack();
 	  myStack->pushInteger(integer_); 
#ifdef HAS_CONSOLE
    if (!bSilent) sprintf(acStringOutputBuffer, "%d %s %d --> %d", (t_integer) L_byte_, c, (t_integer) R_byte_, integer_);
#endif

  } else if (RType == pcode__SHORT){
         if (cOperator == pcode__MUL) integer_ = L_byte_ * R_short_;
    else if (cOperator == pcode__AND) integer_ = L_byte_ & R_short_;
    else if (cOperator == pcode__OR)  integer_ = L_byte_ | R_short_;
    else if (cOperator == pcode__XOR) integer_ = L_byte_ ^ R_short_;
    else if (cOperator == pcode__IMP) integer_ = !(L_byte_ != 0 && R_short_ == 0);
    else if (cOperator == pcode__POWER) integer_ = (t_integer) pow((t_double) L_byte_, (t_double) R_short_);
    else if (cOperator == pcode__ADD) integer_ = L_byte_ + R_short_;
    else if (cOperator == pcode__SUB) integer_ = L_byte_ - R_short_;
    //else if (cOperator == pcode__DIV){ if (R_byte_ == 0){ runtimeError("division by zero", 11); return; } integer_ = L_byte_ / R_short_; }
    else if (cOperator == pcode__MOD){ if (R_byte_ == 0){ runtimeError("MOD by zero", 11); return; } integer_ = L_byte_ % R_short_; }
    else if (cOperator == pcode__IDIV){ if (R_byte_ == 0){ runtimeError("integer division by zero", 11); return; } integer_ = L_byte_ / R_short_; }
    else if (cOperator == pcode__EQUAL) 				integer_ = L_byte_ == R_short_;
    else if (cOperator == pcode__EQV) 				integer_ = L_byte_ == R_short_;
    else if (cOperator == pcode__UNEQUAL) 			integer_ = L_byte_ != R_short_;
    else if (cOperator == pcode__GREATER) 			integer_ = L_byte_ > R_short_;
    else if (cOperator == pcode__LESSER) 				integer_ = L_byte_ < R_short_;
    else if (cOperator == pcode__GREATER_EQUAL) integer_ = L_byte_ >= R_short_;
    else if (cOperator == pcode__LESSER_EQUAL) 	integer_ = L_byte_ <= R_short_;
    else { runtimeError("unknown operator"); return; }

		if (remove == false) myStack->restoreStack();
 	  myStack->pushInteger(integer_); 
#ifdef HAS_CONSOLE
    if (!bSilent) sprintf(acStringOutputBuffer, "%d %s %d --> %d", (t_integer) L_byte_, c, (t_integer) R_short_, integer_);
#endif

  } else if (RType == pcode__INTEGER){
         if (cOperator == pcode__MUL) integer_ = L_byte_ * R_integer_;
    else if (cOperator == pcode__AND) integer_ = L_byte_ & R_integer_;
    else if (cOperator == pcode__OR)  integer_ = L_byte_ | R_integer_;
    else if (cOperator == pcode__XOR) integer_ = L_byte_ ^ R_integer_;
    else if (cOperator == pcode__IMP) integer_ = !(L_byte_ != 0 && R_integer_ == 0);
    else if (cOperator == pcode__POWER) integer_ = (t_integer) pow((t_double) L_byte_, (t_double) R_integer_);
    else if (cOperator == pcode__ADD) integer_ = L_byte_ + R_integer_;
    else if (cOperator == pcode__SUB) integer_ = L_byte_ - R_integer_;
    //else if (cOperator == pcode__DIV){ if (R_integer_ == 0){ runtimeError("division by zero", 11); return; } integer_ = L_byte_ / R_integer_; }
    else if (cOperator == pcode__MOD){ if (R_integer_ == 0){ runtimeError("MOD by zero", 11); return; } integer_ = L_byte_ % R_integer_; }
    else if (cOperator == pcode__IDIV){ if (R_integer_ == 0){ runtimeError("integer division by zero", 11); return; } integer_ = L_byte_ / R_integer_; }
    else if (cOperator == pcode__EQUAL) 				integer_ = L_byte_ == R_integer_;
    else if (cOperator == pcode__EQV) 				integer_ = L_byte_ == R_integer_;
    else if (cOperator == pcode__UNEQUAL) 			integer_ = L_byte_ != R_integer_;
    else if (cOperator == pcode__GREATER) 			integer_ = L_byte_ > R_integer_;
    else if (cOperator == pcode__LESSER) 				integer_ = L_byte_ < R_integer_;
    else if (cOperator == pcode__GREATER_EQUAL) integer_ = L_byte_ >= R_integer_;
    else if (cOperator == pcode__LESSER_EQUAL) 	integer_ = L_byte_ <= R_integer_;
    else { runtimeError("unknown operator"); return; }

		if (remove == false) myStack->restoreStack();
 	  myStack->pushInteger(integer_); 
#ifdef HAS_CONSOLE
    if (!bSilent) sprintf(acStringOutputBuffer, "%d %s %d --> %d", (t_integer) L_byte_, c, R_integer_, integer_);
#endif
  } else if (RType ==  pcode__LONG){
         if (cOperator == pcode__MUL) long_ = L_byte_ * R_long_;
    else if (cOperator == pcode__AND) long_ = L_byte_ & R_long_;
    else if (cOperator == pcode__OR)  long_ = L_byte_ | R_long_;
    else if (cOperator == pcode__XOR) long_ = L_byte_ ^ R_long_;
    else if (cOperator == pcode__IMP) long_ = !(L_byte_ != 0 && R_long_ == 0);
    else if (cOperator == pcode__POWER) long_ = (t_long) pow((t_double) L_byte_, (t_double) R_long_);
    else if (cOperator == pcode__ADD) long_ = L_byte_ + R_long_;
    else if (cOperator == pcode__SUB) long_ = L_byte_ - R_long_;
    //else if (cOperator == pcode__DIV){ if (R_long_ == 0){ runtimeError("division by zero", 11); return; } long_ = L_byte_ / R_long_; }
    else if (cOperator == pcode__MOD){ if (R_long_ == 0){ runtimeError("MOD by zero", 11); return; } long_ = L_byte_ % R_long_; }
    else if (cOperator == pcode__IDIV){ if (R_long_ == 0){ runtimeError("integer division by zero", 11); return; } long_ = L_byte_ / R_long_; }
    else if (cOperator == pcode__EQUAL) 				long_ = L_byte_ == R_long_;
    else if (cOperator == pcode__EQV) 				long_ = L_byte_ == R_long_;
    else if (cOperator == pcode__UNEQUAL) 			long_ = L_byte_ != R_long_;
    else if (cOperator == pcode__GREATER) 			long_ = L_byte_ > R_long_;
    else if (cOperator == pcode__LESSER) 				long_ = L_byte_ < R_long_;
    else if (cOperator == pcode__GREATER_EQUAL) long_ = L_byte_ >= R_long_;
    else if (cOperator == pcode__LESSER_EQUAL) 	long_ = L_byte_ <= R_long_;
    else { runtimeError("unknown operator"); return; }

		if (remove == false) myStack->restoreStack();
 	  myStack->pushLong(long_); 
#ifdef HAS_CONSOLE
    if (!bSilent) sprintf(acStringOutputBuffer, "%d %s %I64d --> %I64d", (t_integer) L_byte_, c, R_long_, long_);
#endif

  } else if (RType == pcode__SINGLE){
         if (cOperator == pcode__MUL) double_ = L_byte_ * R_single_;
    else if (cOperator == pcode__AND) double_ = L_byte_ & (t_long) R_single_;
    else if (cOperator == pcode__OR)  double_ = L_byte_ | (t_long) R_single_;
    else if (cOperator == pcode__XOR) double_ = L_byte_ ^ (t_long) R_single_;
    else if (cOperator == pcode__IMP) double_ = !(L_byte_ != 0 && R_single_ == 0);
    else if (cOperator == pcode__POWER) double_ = pow((t_double) L_byte_, (t_double) R_single_);
    else if (cOperator == pcode__ADD) double_ = L_byte_ + R_single_;
    else if (cOperator == pcode__SUB) double_ = L_byte_ - R_single_;
    //else if (cOperator == pcode__DIV){ if (R_single_ == 0){ runtimeError("division by zero", 11); return; } double_ = L_byte_ / R_single_; }
    else if (cOperator == pcode__MOD){ if (R_single_ == 0){ runtimeError("MOD by zero", 11); return; } double_ = L_byte_ % (t_long) R_single_; }
    else if (cOperator == pcode__IDIV){ if (R_single_ == 0){ runtimeError("integer division by zero", 11); return; } double_ = (t_long) (L_byte_ / R_single_); }
    else if (cOperator == pcode__EQUAL) 				double_ = L_byte_ == R_single_;
    else if (cOperator == pcode__EQV) 				double_ = L_byte_ == R_single_;
    else if (cOperator == pcode__UNEQUAL) 			double_ = L_byte_ != R_single_;
    else if (cOperator == pcode__GREATER) 			double_ = L_byte_ > R_single_;
    else if (cOperator == pcode__LESSER) 				double_ = L_byte_ < R_single_;
    else if (cOperator == pcode__GREATER_EQUAL) double_ = L_byte_ >= R_single_;
    else if (cOperator == pcode__LESSER_EQUAL) 	double_ = L_byte_ <= R_single_;
    else { runtimeError("unknown operator"); return; }

		if (remove == false) myStack->restoreStack();
    myStack->pushDouble(double_); 
#ifdef HAS_CONSOLE
    if (!bSilent) sprintf(acStringOutputBuffer, "%d %s %.6f --> %.6f", (t_integer) L_byte_, c, R_single_, double_);
#endif

  } else if (RType == pcode__DOUBLE){
         if (cOperator == pcode__MUL) double_ = L_byte_ * R_double_;
    else if (cOperator == pcode__AND) double_ = L_byte_ & (t_long) R_double_;
    else if (cOperator == pcode__OR)  double_ = L_byte_ | (t_long) R_double_;
    else if (cOperator == pcode__XOR) double_ = L_byte_ ^ (t_long) R_double_;
    else if (cOperator == pcode__IMP) double_ = !(L_byte_ != 0 && R_double_ == 0);
    else if (cOperator == pcode__POWER) double_ = (t_integer) pow((t_double) L_byte_, R_double_);
    else if (cOperator == pcode__ADD) double_ = L_byte_ + R_double_;
    else if (cOperator == pcode__SUB) double_ = L_byte_ - R_double_;
    //else if (cOperator == pcode__DIV){ if (R_double_ == 0){ runtimeError("division by zero", 11); return; } double_ = L_byte_ / R_double_; }
    else if (cOperator == pcode__MOD){ if (R_double_ == 0){ runtimeError("MOD by zero", 11); return; } double_ = L_byte_ % (t_long) R_double_; }
    else if (cOperator == pcode__IDIV){ if (R_double_ == 0){ runtimeError("integer division by zero", 11); return; } double_ = (t_long) (L_byte_ / R_double_); }
    else if (cOperator == pcode__EQUAL) 				double_ = L_byte_ == R_double_;
    else if (cOperator == pcode__EQV) 				double_ = L_byte_ == R_double_;
    else if (cOperator == pcode__UNEQUAL) 			double_ = L_byte_ != R_double_;
    else if (cOperator == pcode__GREATER) 			double_ = L_byte_ > R_double_;
    else if (cOperator == pcode__LESSER) 				double_ = L_byte_ < R_double_;
    else if (cOperator == pcode__GREATER_EQUAL) double_ = L_byte_ >= R_double_;
    else if (cOperator == pcode__LESSER_EQUAL) 	double_ = L_byte_ <= R_double_;
    else { runtimeError("unknown operator"); return; }

		if (remove == false) myStack->restoreStack();
    myStack->pushDouble(double_); 
#ifdef HAS_CONSOLE
    if (!bSilent) sprintf(acStringOutputBuffer, "%d %s %.6f --> %.6f", (t_integer) L_byte_, c, R_double_, double_);
#endif

  } else if (RType == pcode__CURRENCY){

    t_currency t(L_byte_, 0);

         if (cOperator == pcode__MUL) currency_.setValue(t.bc() * R_currency_.bc(), t.bc() * R_currency_.ad());
    else if (cOperator == pcode__AND) currency_.setValue(t.bc() & R_currency_.bc(), t.ad() & R_currency_.ad());
    else if (cOperator == pcode__OR)  currency_.setValue(t.bc() | R_currency_.bc(), t.ad() | R_currency_.ad());
    else if (cOperator == pcode__XOR) currency_.setValue(t.bc() ^ R_currency_.bc(), t.ad() ^ R_currency_.ad());
    else if (cOperator == pcode__IMP) currency_.setValue(!(t.getValue() != 0 && R_currency_.getValue() == 0), 0);
    else if (cOperator == pcode__POWER) currency_.setValue((t_long) pow((t_double) t.bc(), (t_double) R_currency_.toDouble()), 0);
    else if (cOperator == pcode__ADD) currency_.setValue(t.bc() + R_currency_.bc(), t.ad() + R_currency_.ad());
    else if (cOperator == pcode__SUB) currency_.setValue(t.bc() - R_currency_.bc(), t.ad() - R_currency_.ad());
    //else if (cOperator == pcode__DIV){ if (R_currency_.getValue() == 0){ runtimeError("division by zero", 11); return; } currency_.setValue(t.bc() / R_currency_.bc(), t.ad() / R_currency_.ad()); }
    else if (cOperator == pcode__MOD){ if (R_currency_.getValue() == 0){ runtimeError("MOD by zero", 11); return; } currency_.setValue(t.bc() % R_currency_.bc(), t.ad() % R_currency_.ad()); }
    else if (cOperator == pcode__IDIV){ if (R_currency_.getValue() == 0){ runtimeError("integer division by zero", 11); return; } currency_.setValue(t.bc() / R_currency_.bc(), t.ad() / R_currency_.ad()); }
    else if (cOperator == pcode__EQUAL) 				currency_.setValue(t.getValue() == R_currency_.getValue(), 0);
    else if (cOperator == pcode__EQV) 				currency_.setValue(t.getValue() == R_currency_.getValue(), 0);
    else if (cOperator == pcode__UNEQUAL) 			currency_.setValue(t.getValue() != R_currency_.getValue(), 0);
    else if (cOperator == pcode__GREATER) 			currency_.setValue(t.getValue() > R_currency_.getValue(), 0);
    else if (cOperator == pcode__LESSER) 				currency_.setValue(t.getValue() < R_currency_.getValue(), 0);
    else if (cOperator == pcode__GREATER_EQUAL) currency_.setValue(t.getValue() >= R_currency_.getValue(), 0);
    else if (cOperator == pcode__LESSER_EQUAL) currency_.setValue(t.getValue() <= R_currency_.getValue(), 0);
    else { runtimeError("unknown operator"); return; }

		if (remove == false) myStack->restoreStack();
 	  myStack->pushCurrency(currency_); 
#ifdef HAS_CONSOLE
    if (!bSilent) sprintf(acStringOutputBuffer, "%d %s %s --> %s", (t_integer) t.bc(), c, R_currency_.toCString(), currency_.toCString2());
#endif
  }
	// pcode__SHORT ***
  } else if (LType == pcode__SHORT){
  if (RType == pcode__BOOLEAN){
         if (cOperator == pcode__MUL) integer_ = L_short_ * R_boolean_;
    else if (cOperator == pcode__AND) integer_ = L_short_ & R_boolean_;
    else if (cOperator == pcode__OR)  integer_ = L_short_ | R_boolean_;
    else if (cOperator == pcode__XOR) integer_ = L_short_ ^ R_boolean_;
    else if (cOperator == pcode__IMP) integer_ = !(L_short_ != 0 && R_boolean_ == 0);
    else if (cOperator == pcode__POWER) integer_ = (t_integer) pow((t_double) L_short_, (t_double) R_boolean_);
    else if (cOperator == pcode__ADD) integer_ = L_short_ + R_boolean_;
    else if (cOperator == pcode__SUB) integer_ = L_short_ - R_boolean_;
    //else if (cOperator == pcode__DIV){ if (R_boolean_ == 0){ runtimeError("division by zero", 11); return; } integer_ = L_short_ / R_boolean_; }
    else if (cOperator == pcode__MOD){ if (R_boolean_ == 0){ runtimeError("MOD by zero", 11); return; } integer_ = L_short_ % R_boolean_; }
    else if (cOperator == pcode__IDIV){ if (R_boolean_ == 0){ runtimeError("integer division by zero", 11); return; } integer_ = L_short_ / R_boolean_; }
    else if (cOperator == pcode__EQUAL) 				integer_ = L_short_ == R_boolean_;
    else if (cOperator == pcode__EQV) 				integer_ = L_short_ == R_boolean_;
    else if (cOperator == pcode__UNEQUAL) 			integer_ = L_short_ != R_boolean_;
    else if (cOperator == pcode__GREATER) 			integer_ = L_short_ > R_boolean_;
    else if (cOperator == pcode__LESSER) 				integer_ = L_short_ < R_boolean_;
    else if (cOperator == pcode__GREATER_EQUAL) integer_ = L_short_ >= R_boolean_;
    else if (cOperator == pcode__LESSER_EQUAL) 	integer_ = L_short_ <= R_boolean_;
    else { runtimeError("unknown operator"); return; }

		if (remove == false) myStack->restoreStack();
 	  myStack->pushInteger(integer_); 
#ifdef HAS_CONSOLE
    if (!bSilent) sprintf(acStringOutputBuffer, "%d %s %d --> %d", (t_integer) L_short_, c, (t_integer) R_boolean_, integer_);
#endif

  } else if (RType == pcode__QSTRING){

     if (cOperator == pcode__ADD){
			 int nId = estatics->declare(pcode__QSTRING, 0, false, false);
    	 estatics->setQString_Short(nId, L_short_, R_qstring_, 0);
			 myStack->pushEQString(nId);
#ifdef HAS_CONSOLE
			 if (!bSilent) sprintf(acStringOutputBuffer, "Unicode");
//			 if (!bSilent) sprintf(acStringOutputBuffer, "%d %s \"%-30.30s\" --> \"%-30.30s\"", (t_integer) L_short_, c, R_string_, estatics->getString(nId));
#endif
     } else { runtimeError("unknown operator"); return; }

  } else if (RType == pcode__CSTRING){

     if (cOperator == pcode__ADD){
			 int nId = estatics->declare(pcode__CSTRING, 0, false, false);
    	 estatics->setCString_Short(nId, L_short_, R_cstring_, 0);
			 myStack->pushECString(nId);
#ifdef HAS_CONSOLE
			 if (!bSilent) sprintf(acStringOutputBuffer, "%d %s \"%-30.30s\" --> \"%-30.30s\"", (t_integer) L_short_, c, R_cstring_, estatics->getCString(nId));
#endif
     } else { runtimeError("unknown operator"); return; }

  } else if (RType == pcode__BYTE){
         if (cOperator == pcode__MUL) integer_ = L_short_ * R_byte_;
    else if (cOperator == pcode__AND) integer_ = L_short_ & R_byte_;
    else if (cOperator == pcode__OR)  integer_ = L_short_ | R_byte_;
    else if (cOperator == pcode__XOR) integer_ = L_short_ ^ R_byte_;
    else if (cOperator == pcode__IMP) integer_ = !(L_short_ != 0 && R_byte_ == 0);
    else if (cOperator == pcode__POWER) integer_ = (t_integer) pow((t_double) L_short_, (t_double) R_byte_);
    else if (cOperator == pcode__ADD) integer_ = L_short_ + R_byte_;
    else if (cOperator == pcode__SUB) integer_ = L_short_ - R_byte_;
    //else if (cOperator == pcode__DIV){ if (R_byte_ == 0){ runtimeError("division by zero", 11); return; } integer_ = L_short_ / R_byte_; }
    else if (cOperator == pcode__MOD){ if (R_byte_ == 0){ runtimeError("MOD by zero", 11); return; } integer_ = L_short_ % R_byte_; }
    else if (cOperator == pcode__IDIV){ if (R_byte_ == 0){ runtimeError("integer division by zero", 11); return; } integer_ = L_short_ / R_byte_; }
    else if (cOperator == pcode__EQUAL) 				integer_ = L_short_ == R_byte_;
    else if (cOperator == pcode__EQV) 				integer_ = L_short_ == R_byte_;
    else if (cOperator == pcode__UNEQUAL) 			integer_ = L_short_ != R_byte_;
    else if (cOperator == pcode__GREATER) 			integer_ = L_short_ > R_byte_;
    else if (cOperator == pcode__LESSER) 				integer_ = L_short_ < R_byte_;
    else if (cOperator == pcode__GREATER_EQUAL) integer_ = L_short_ >= R_byte_;
    else if (cOperator == pcode__LESSER_EQUAL) 	integer_ = L_short_ <= R_byte_;
    else { runtimeError("unknown operator"); return; }

		if (remove == false) myStack->restoreStack();
 	  myStack->pushInteger(integer_); 
#ifdef HAS_CONSOLE
    if (!bSilent) sprintf(acStringOutputBuffer, "%d %s %d --> %d", (t_integer) L_short_, c, (t_integer) R_byte_, integer_);
#endif

  } else if (RType == pcode__SHORT){
         if (cOperator == pcode__MUL) integer_ = L_short_ * R_short_;
    else if (cOperator == pcode__AND) integer_ = L_short_ & R_short_;
    else if (cOperator == pcode__OR)  integer_ = L_short_ | R_short_;
    else if (cOperator == pcode__XOR) integer_ = L_short_ ^ R_short_;
    else if (cOperator == pcode__IMP) integer_ = !(L_short_ != 0 && R_short_ == 0);
    else if (cOperator == pcode__POWER) integer_ = (t_integer) pow((t_double) L_short_, (t_double) R_short_);
    else if (cOperator == pcode__ADD) integer_ = L_short_ + R_short_;
    else if (cOperator == pcode__SUB) integer_ = L_short_ - R_short_;
    //else if (cOperator == pcode__DIV){ if (R_byte_ == 0){ runtimeError("division by zero", 11); return; } integer_ = L_short_ / R_short_; }
    else if (cOperator == pcode__MOD){ if (R_byte_ == 0){ runtimeError("MOD by zero", 11); return; } integer_ = L_short_ % R_short_; }
    else if (cOperator == pcode__IDIV){ if (R_byte_ == 0){ runtimeError("integer division by zero", 11); return; } integer_ = L_short_ / R_short_; }
    else if (cOperator == pcode__EQUAL) 				integer_ = L_short_ == R_short_;
    else if (cOperator == pcode__EQV) 				integer_ = L_short_ == R_short_;
    else if (cOperator == pcode__UNEQUAL) 			integer_ = L_short_ != R_short_;
    else if (cOperator == pcode__GREATER) 			integer_ = L_short_ > R_short_;
    else if (cOperator == pcode__LESSER) 				integer_ = L_short_ < R_short_;
    else if (cOperator == pcode__GREATER_EQUAL) integer_ = L_short_ >= R_short_;
    else if (cOperator == pcode__LESSER_EQUAL) 	integer_ = L_short_ <= R_short_;
    else { runtimeError("unknown operator"); return; }

		if (remove == false) myStack->restoreStack();
 	  myStack->pushInteger(integer_); 
#ifdef HAS_CONSOLE
    if (!bSilent) sprintf(acStringOutputBuffer, "%d %s %d --> %d", (t_integer) L_short_, c, (t_integer) R_short_, integer_);
#endif

  } else if (RType == pcode__INTEGER){
         if (cOperator == pcode__MUL) integer_ = L_short_ * R_integer_;
    else if (cOperator == pcode__AND) integer_ = L_short_ & R_integer_;
    else if (cOperator == pcode__OR)  integer_ = L_short_ | R_integer_;
    else if (cOperator == pcode__XOR) integer_ = L_short_ ^ R_integer_;
    else if (cOperator == pcode__IMP) integer_ = !(L_short_ != 0 && R_integer_ == 0);
    else if (cOperator == pcode__POWER) integer_ = (t_integer) pow((t_double) L_short_, (t_double) R_integer_);
    else if (cOperator == pcode__ADD) integer_ = L_short_ + R_integer_;
    else if (cOperator == pcode__SUB) integer_ = L_short_ - R_integer_;
    //else if (cOperator == pcode__DIV){ if (R_integer_ == 0){ runtimeError("division by zero", 11); return; } integer_ = L_short_ / R_integer_; }
    else if (cOperator == pcode__MOD){ if (R_integer_ == 0){ runtimeError("MOD by zero", 11); return; } integer_ = L_short_ % R_integer_; }
    else if (cOperator == pcode__IDIV){ if (R_integer_ == 0){ runtimeError("integer division by zero", 11); return; } integer_ = L_short_ / R_integer_; }
    else if (cOperator == pcode__EQUAL) 				integer_ = L_short_ == R_integer_;
    else if (cOperator == pcode__EQV) 				integer_ = L_short_ == R_integer_;
    else if (cOperator == pcode__UNEQUAL) 			integer_ = L_short_ != R_integer_;
    else if (cOperator == pcode__GREATER) 			integer_ = L_short_ > R_integer_;
    else if (cOperator == pcode__LESSER) 				integer_ = L_short_ < R_integer_;
    else if (cOperator == pcode__GREATER_EQUAL) integer_ = L_short_ >= R_integer_;
    else if (cOperator == pcode__LESSER_EQUAL) 	integer_ = L_short_ <= R_integer_;
    else { runtimeError("unknown operator"); return; }

		if (remove == false) myStack->restoreStack();
 	  myStack->pushInteger(integer_); 
#ifdef HAS_CONSOLE    
    if (!bSilent) sprintf(acStringOutputBuffer, "%d %s %d --> %d", (t_integer) L_short_, c, R_integer_, integer_);
#endif

  } else if (RType ==  pcode__LONG){
         if (cOperator == pcode__MUL) long_ = L_short_ * R_long_;
    else if (cOperator == pcode__AND) long_ = L_short_ & R_long_;
    else if (cOperator == pcode__OR)  long_ = L_short_ | R_long_;
    else if (cOperator == pcode__XOR) long_ = L_short_ ^ R_long_;
    else if (cOperator == pcode__IMP) long_ = !(L_short_ != 0 && R_long_ == 0);
    else if (cOperator == pcode__POWER) long_ = (t_long) pow((t_double) L_short_, (t_double) R_long_);
    else if (cOperator == pcode__ADD) long_ = L_short_ + R_long_;
    else if (cOperator == pcode__SUB) long_ = L_short_ - R_long_;
    //else if (cOperator == pcode__DIV){ if (R_long_ == 0){ runtimeError("division by zero", 11); return; } long_ = L_short_ / R_long_; }
    else if (cOperator == pcode__MOD){ if (R_long_ == 0){ runtimeError("MOD by zero", 11); return; } long_ = L_short_ % R_long_; }
    else if (cOperator == pcode__IDIV){ if (R_long_ == 0){ runtimeError("integer division by zero", 11); return; } long_ = L_short_ / R_long_; }
    else if (cOperator == pcode__EQUAL) 				long_ = L_short_ == R_long_;
    else if (cOperator == pcode__EQV) 				long_ = L_short_ == R_long_;
    else if (cOperator == pcode__UNEQUAL) 			long_ = L_short_ != R_long_;
    else if (cOperator == pcode__GREATER) 			long_ = L_short_ > R_long_;
    else if (cOperator == pcode__LESSER) 				long_ = L_short_ < R_long_;
    else if (cOperator == pcode__GREATER_EQUAL) long_ = L_short_ >= R_long_;
    else if (cOperator == pcode__LESSER_EQUAL) 	long_ = L_short_ <= R_long_;
    else { runtimeError("unknown operator"); return; }

		if (remove == false) myStack->restoreStack();
 	  myStack->pushLong(long_); 
#ifdef HAS_CONSOLE
    if (!bSilent) sprintf(acStringOutputBuffer, "%d %s %I64d --> %I64d", (t_integer) L_short_, c, R_long_, long_);
#endif

  } else if (RType == pcode__SINGLE){
         if (cOperator == pcode__MUL) double_ = L_short_ * R_single_;
    else if (cOperator == pcode__AND) double_ = L_short_ & (t_long) R_single_;
    else if (cOperator == pcode__OR)  double_ = L_short_ | (t_long) R_single_;
    else if (cOperator == pcode__XOR) double_ = L_short_ ^ (t_long) R_single_;
    else if (cOperator == pcode__IMP) double_ = !(L_short_ != 0 && R_single_ == 0);
    else if (cOperator == pcode__POWER) double_ = pow((t_double) L_short_, (t_double) R_single_);
    else if (cOperator == pcode__ADD) double_ = L_short_ + R_single_;
    else if (cOperator == pcode__SUB) double_ = L_short_ - R_single_;
    //else if (cOperator == pcode__DIV){ if (R_single_ == 0){ runtimeError("division by zero", 11); return; } double_ = L_short_ / R_single_; }
    else if (cOperator == pcode__MOD){ if (R_single_ == 0){ runtimeError("MOD by zero", 11); return; } double_ = L_short_ % (t_long) R_single_; }
    else if (cOperator == pcode__IDIV){ if (R_single_ == 0){ runtimeError("integer division by zero", 11); return; } double_ = (t_long) (L_short_ / R_single_); }
    else if (cOperator == pcode__EQUAL) 				double_ = L_short_ == R_single_;
    else if (cOperator == pcode__EQV) 				double_ = L_short_ == R_single_;
    else if (cOperator == pcode__UNEQUAL) 			double_ = L_short_ != R_single_;
    else if (cOperator == pcode__GREATER) 			double_ = L_short_ > R_single_;
    else if (cOperator == pcode__LESSER) 				double_ = L_short_ < R_single_;
    else if (cOperator == pcode__GREATER_EQUAL) double_ = L_short_ >= R_single_;
    else if (cOperator == pcode__LESSER_EQUAL) 	double_ = L_short_ <= R_single_;
    else { runtimeError("unknown operator"); return; }

		if (remove == false) myStack->restoreStack();
    myStack->pushDouble(double_); 
#ifdef HAS_CONSOLE
    if (!bSilent) sprintf(acStringOutputBuffer, "%d %s %.6f --> %.6f", (t_integer) L_short_, c, R_single_, double_);
#endif

  } else if (RType == pcode__DOUBLE){
         if (cOperator == pcode__MUL) double_ = L_short_ * R_double_;
    else if (cOperator == pcode__AND) double_ = L_short_ & (t_long) R_double_;
    else if (cOperator == pcode__OR)  double_ = L_short_ | (t_long) R_double_;
    else if (cOperator == pcode__XOR) double_ = L_short_ ^ (t_long) R_double_;
    else if (cOperator == pcode__IMP) double_ = !(L_short_ != 0 && R_double_ == 0);
    else if (cOperator == pcode__POWER) double_ = (t_integer) pow((t_double) L_short_, R_double_);
    else if (cOperator == pcode__ADD) double_ = L_short_ + R_double_;
    else if (cOperator == pcode__SUB) double_ = L_short_ - R_double_;
    //else if (cOperator == pcode__DIV){ if (R_double_ == 0){ runtimeError("division by zero", 11); return; } double_ = L_short_ / R_double_; }
    else if (cOperator == pcode__MOD){ if (R_double_ == 0){ runtimeError("MOD by zero", 11); return; } double_ = L_short_ % (t_long) R_double_; }
    else if (cOperator == pcode__IDIV){ if (R_double_ == 0){ runtimeError("integer division by zero", 11); return; } double_ = (t_long) (L_short_ / R_double_); }
    else if (cOperator == pcode__EQUAL) 				double_ = L_short_ == R_double_;
    else if (cOperator == pcode__EQV) 				double_ = L_short_ == R_double_;
    else if (cOperator == pcode__UNEQUAL) 			double_ = L_short_ != R_double_;
    else if (cOperator == pcode__GREATER) 			double_ = L_short_ > R_double_;
    else if (cOperator == pcode__LESSER) 				double_ = L_short_ < R_double_;
    else if (cOperator == pcode__GREATER_EQUAL) double_ = L_short_ >= R_double_;
    else if (cOperator == pcode__LESSER_EQUAL) 	double_ = L_short_ <= R_double_;
    else { runtimeError("unknown operator"); return; }

		if (remove == false) myStack->restoreStack();
    myStack->pushDouble(double_); 
#ifdef HAS_CONSOLE
    if (!bSilent) sprintf(acStringOutputBuffer, "%d %s %.6f --> %.6f", (t_integer) L_short_, c, R_double_, double_);
#endif

  } else if (RType == pcode__CURRENCY){

    t_currency t(L_short_, 0);

         if (cOperator == pcode__MUL) currency_.setValue(t.bc() * R_currency_.bc(), t.bc() * R_currency_.ad());
    else if (cOperator == pcode__AND) currency_.setValue(t.bc() & R_currency_.bc(), t.ad() & R_currency_.ad());
    else if (cOperator == pcode__OR)  currency_.setValue(t.bc() | R_currency_.bc(), t.ad() | R_currency_.ad());
    else if (cOperator == pcode__XOR) currency_.setValue(t.bc() ^ R_currency_.bc(), t.ad() ^ R_currency_.ad());
    else if (cOperator == pcode__IMP) currency_.setValue(!(t.getValue() != 0 && R_currency_.getValue() == 0), 0);
    else if (cOperator == pcode__POWER) currency_.setValue((t_long) pow((t_double) t.bc(), (t_double) R_currency_.toDouble()), 0);
    else if (cOperator == pcode__ADD) currency_.setValue(t.bc() + R_currency_.bc(), t.ad() + R_currency_.ad());
    else if (cOperator == pcode__SUB) currency_.setValue(t.bc() - R_currency_.bc(), t.ad() - R_currency_.ad());
    //else if (cOperator == pcode__DIV){ if (R_currency_.getValue() == 0){ runtimeError("division by zero", 11); return; } currency_.setValue(t.bc() / R_currency_.bc(), t.ad() / R_currency_.ad()); }
    else if (cOperator == pcode__MOD){ if (R_currency_.getValue() == 0){ runtimeError("MOD by zero", 11); return; } currency_.setValue(t.bc() % R_currency_.bc(), t.ad() % R_currency_.ad()); }
    else if (cOperator == pcode__IDIV){ if (R_currency_.getValue() == 0){ runtimeError("integer division by zero", 11); return; } currency_.setValue(t.bc() / R_currency_.bc(), t.ad() / R_currency_.ad()); }
    else if (cOperator == pcode__EQUAL) 				currency_.setValue(t.getValue() == R_currency_.getValue(), 0);
    else if (cOperator == pcode__EQV) 				currency_.setValue(t.getValue() == R_currency_.getValue(), 0);
    else if (cOperator == pcode__UNEQUAL) 			currency_.setValue(t.getValue() != R_currency_.getValue(), 0);
    else if (cOperator == pcode__GREATER) 			currency_.setValue(t.getValue() > R_currency_.getValue(), 0);
    else if (cOperator == pcode__LESSER) 				currency_.setValue(t.getValue() < R_currency_.getValue(), 0);
    else if (cOperator == pcode__GREATER_EQUAL) currency_.setValue(t.getValue() >= R_currency_.getValue(), 0);
    else if (cOperator == pcode__LESSER_EQUAL) currency_.setValue(t.getValue() <= R_currency_.getValue(), 0);
    else { runtimeError("unknown operator"); return; }

		if (remove == false) myStack->restoreStack();
 	  myStack->pushCurrency(currency_); 
#ifdef HAS_CONSOLE
    if (!bSilent) sprintf(acStringOutputBuffer, "%d %s %s --> %s", (t_integer) t.bc(), c, R_currency_.toCString(), currency_.toCString2());
#endif
  }
  // pcode__INTEGER ***
  } else if (LType == pcode__INTEGER){
  if (RType == pcode__BOOLEAN){
         if (cOperator == pcode__MUL) integer_ = L_integer_ * R_boolean_;
    else if (cOperator == pcode__AND) integer_ = L_integer_ & R_boolean_;
    else if (cOperator == pcode__OR)  integer_ = L_integer_ | R_boolean_;
    else if (cOperator == pcode__XOR) integer_ = L_integer_ ^ R_boolean_;
    else if (cOperator == pcode__IMP) integer_ = !(L_integer_ != 0 && R_boolean_ == 0);
    else if (cOperator == pcode__POWER) integer_ = (t_integer) pow((t_double) L_integer_, (t_double) R_boolean_);
    else if (cOperator == pcode__ADD) integer_ = L_integer_ + R_boolean_;
    else if (cOperator == pcode__SUB) integer_ = L_integer_ - R_boolean_;
    //else if (cOperator == pcode__DIV){ if (R_boolean_ == 0){ runtimeError("division by zero", 11); return; } integer_ = L_integer_ / R_boolean_; }
    else if (cOperator == pcode__MOD){ if (R_boolean_ == 0){ runtimeError("MOD by zero", 11); return; } integer_ = L_integer_ % R_boolean_; }
    else if (cOperator == pcode__IDIV){ if (R_boolean_ == 0){ runtimeError("integer division by zero", 11); return; } integer_ = L_integer_ / R_boolean_; }
    else if (cOperator == pcode__EQUAL) 				integer_ = L_integer_ == R_boolean_;
    else if (cOperator == pcode__EQV) 				integer_ = L_integer_ == R_boolean_;
    else if (cOperator == pcode__UNEQUAL) 			integer_ = L_integer_ != R_boolean_;
    else if (cOperator == pcode__GREATER) 			integer_ = L_integer_ > R_boolean_;
    else if (cOperator == pcode__LESSER) 				integer_ = L_integer_ < R_boolean_;
    else if (cOperator == pcode__GREATER_EQUAL) integer_ = L_integer_ >= R_boolean_;
    else if (cOperator == pcode__LESSER_EQUAL) 	integer_ = L_integer_ <= R_boolean_;
    else { runtimeError("unknown operator"); return; }

		if (remove == false) myStack->restoreStack();
 	  myStack->pushInteger(integer_); 
#ifdef HAS_CONSOLE
    if (!bSilent) sprintf(acStringOutputBuffer, "%d %s %d --> %d", L_integer_, c, (t_integer) R_boolean_, integer_);
#endif

  } else if (RType == pcode__QSTRING){

     if (cOperator == pcode__ADD){
			 int nId = estatics->declare(pcode__QSTRING, 0, false, false);
    	 estatics->setQString_Integer(nId,L_integer_, R_qstring_ , 0);
			 myStack->pushEQString(nId);
#ifdef HAS_CONSOLE
			 if (!bSilent) sprintf(acStringOutputBuffer, "Unicode");
//			 if (!bSilent) sprintf(acStringOutputBuffer, "%d %s \"%-30.30s\" --> \"%-30.30s\"", L_integer_, c, R_string_, estatics->getString(nId));
#endif
     } else { runtimeError("unknown operator"); return; }

  } else if (RType == pcode__CSTRING){

     if (cOperator == pcode__ADD){
			 int nId = estatics->declare(pcode__CSTRING, 0, false, false);
    	 estatics->setCString_Integer(nId,L_integer_, R_cstring_ , 0);
			 myStack->pushECString(nId);
#ifdef HAS_CONSOLE
			 if (!bSilent) sprintf(acStringOutputBuffer, "%d %s \"%-30.30s\" --> \"%-30.30s\"", L_integer_, c, R_cstring_, estatics->getCString(nId));
#endif
     } else { runtimeError("unknown operator"); return; }


  } else if (RType == pcode__BYTE){
         if (cOperator == pcode__MUL) long_ = (t_long) L_integer_ * R_byte_;
    else if (cOperator == pcode__AND) long_ = L_integer_ & R_byte_;
    else if (cOperator == pcode__OR)  long_ = L_integer_ | R_byte_;
    else if (cOperator == pcode__XOR) long_ = L_integer_ ^ R_byte_;
    else if (cOperator == pcode__IMP) long_ = !(L_integer_ != 0 && R_byte_ == 0);
    else if (cOperator == pcode__POWER) long_ = (t_integer) pow((t_double) L_integer_, (t_double) R_byte_);
    else if (cOperator == pcode__ADD) long_ = L_integer_ + R_byte_;
    else if (cOperator == pcode__SUB) long_ = L_integer_ - R_byte_;
    //else if (cOperator == pcode__DIV){ if (R_byte_ == 0){ runtimeError("division by zero", 11); return; } long_ = L_integer_ / R_byte_; }
    else if (cOperator == pcode__MOD){ if (R_byte_ == 0){ runtimeError("MOD by zero", 11); return; } long_ = L_integer_ % R_byte_; }
    else if (cOperator == pcode__IDIV){ if (R_byte_ == 0){ runtimeError("integer division by zero", 11); return; } long_ = L_integer_ / R_byte_; }
    else if (cOperator == pcode__EQUAL) 				long_ = L_integer_ == R_byte_;
    else if (cOperator == pcode__EQV) 				long_ = L_integer_ == R_byte_;
    else if (cOperator == pcode__UNEQUAL) 			long_ = L_integer_ != R_byte_;
    else if (cOperator == pcode__GREATER) 			long_ = L_integer_ > R_byte_;
    else if (cOperator == pcode__LESSER) 				long_ = L_integer_ < R_byte_;
    else if (cOperator == pcode__GREATER_EQUAL) long_ = L_integer_ >= R_byte_;
    else if (cOperator == pcode__LESSER_EQUAL) 	long_ = L_integer_ <= R_byte_;
    else { runtimeError("unknown operator"); return; }

		if (remove == false) myStack->restoreStack();
 	  myStack->pushLong(long_); 
#ifdef HAS_CONSOLE
    if (!bSilent) sprintf(acStringOutputBuffer, "%d %s %d --> %d", L_integer_, c, (t_integer) R_byte_, long_);
#endif

  } else if (RType == pcode__SHORT){
         if (cOperator == pcode__MUL) long_ = L_integer_ * R_short_;
    else if (cOperator == pcode__AND) long_ = L_integer_ & R_short_;
    else if (cOperator == pcode__OR)  long_ = L_integer_ | R_short_;
    else if (cOperator == pcode__XOR) long_ = L_integer_ ^ R_short_;
    else if (cOperator == pcode__IMP) long_ = !(L_integer_ != 0 && R_short_ == 0);
    else if (cOperator == pcode__POWER) long_ = (t_integer) pow((t_double) L_integer_, (t_double) R_short_);
    else if (cOperator == pcode__ADD) long_ = L_integer_ + R_short_;
    else if (cOperator == pcode__SUB) long_ = L_integer_ - R_short_;
    //else if (cOperator == pcode__DIV){ if (R_byte_ == 0){ runtimeError("division by zero", 11); return; } long_ = L_integer_ / R_short_; }
    else if (cOperator == pcode__MOD){ if (R_byte_ == 0){ runtimeError("MOD by zero", 11); return; } long_ = L_integer_ % R_short_; }
    else if (cOperator == pcode__IDIV){ if (R_byte_ == 0){ runtimeError("integer division by zero", 11); return; } long_ = L_integer_ / R_short_; }
    else if (cOperator == pcode__EQUAL) 				long_ = L_integer_ == R_short_;
    else if (cOperator == pcode__EQV) 				long_ = L_integer_ == R_short_;
    else if (cOperator == pcode__UNEQUAL) 			long_ = L_integer_ != R_short_;
    else if (cOperator == pcode__GREATER) 			long_ = L_integer_ > R_short_;
    else if (cOperator == pcode__LESSER) 				long_ = L_integer_ < R_short_;
    else if (cOperator == pcode__GREATER_EQUAL) long_ = L_integer_ >= R_short_;
    else if (cOperator == pcode__LESSER_EQUAL) 	long_ = L_integer_ <= R_short_;
    else { runtimeError("unknown operator"); return; }

		if (remove == false) myStack->restoreStack();
 	  myStack->pushLong(long_); 
#ifdef HAS_CONSOLE
    if (!bSilent) sprintf(acStringOutputBuffer, "%d %s %d --> %I64d", L_integer_, c, (t_integer) R_short_, long_);
#endif

  } else if (RType == pcode__INTEGER){
         if (cOperator == pcode__MUL) long_ = L_integer_ * R_integer_;
    else if (cOperator == pcode__AND) long_ = L_integer_ & R_integer_;
    else if (cOperator == pcode__OR)  long_ = L_integer_ | R_integer_;
    else if (cOperator == pcode__XOR) long_ = L_integer_ ^ R_integer_;
    else if (cOperator == pcode__IMP) long_ = !(L_integer_ != 0 && R_integer_ == 0);
    else if (cOperator == pcode__POWER) long_ = (t_integer) pow((t_double) L_integer_, (t_double) R_integer_);
    else if (cOperator == pcode__ADD) long_ = L_integer_ + R_integer_;
    else if (cOperator == pcode__SUB) long_ = L_integer_ - R_integer_;
    //else if (cOperator == pcode__DIV){ if (R_integer_ == 0){ runtimeError("division by zero", 11); return; } long_ = L_integer_ / R_integer_; }
    else if (cOperator == pcode__MOD){ if (R_integer_ == 0){ runtimeError("MOD by zero", 11); return; } long_ = L_integer_ % R_integer_; }
    else if (cOperator == pcode__IDIV){ if (R_integer_ == 0){ runtimeError("integer division by zero", 11); return; } long_ = L_integer_ / R_integer_; }
    else if (cOperator == pcode__EQUAL) 				long_ = L_integer_ == R_integer_;
    else if (cOperator == pcode__EQV) 				long_ = L_integer_ == R_integer_;
    else if (cOperator == pcode__UNEQUAL) 			long_ = L_integer_ != R_integer_;
    else if (cOperator == pcode__GREATER) 			long_ = L_integer_ > R_integer_;
    else if (cOperator == pcode__LESSER) 				long_ = L_integer_ < R_integer_;
    else if (cOperator == pcode__GREATER_EQUAL) long_ = L_integer_ >= R_integer_;
    else if (cOperator == pcode__LESSER_EQUAL) 	long_ = L_integer_ <= R_integer_;
    else { runtimeError("unknown operator"); return; }

		if (remove == false) myStack->restoreStack();
 	  myStack->pushLong(long_); 
#ifdef HAS_CONSOLE
    if (!bSilent) sprintf(acStringOutputBuffer, "%d %s %d --> %I64d", L_integer_, c, R_integer_, long_);
#endif

  } else if (RType ==  pcode__LONG){
         if (cOperator == pcode__MUL) long_ = L_integer_ * R_long_;
    else if (cOperator == pcode__AND) long_ = L_integer_ & R_long_;
    else if (cOperator == pcode__OR)  long_ = L_integer_ | R_long_;
    else if (cOperator == pcode__XOR) long_ = L_integer_ ^ R_long_;
    else if (cOperator == pcode__IMP) long_ = !(L_integer_ != 0 && R_long_ == 0);
    else if (cOperator == pcode__POWER) long_ = (t_long) pow((t_double) L_integer_, (t_double) R_long_);
    else if (cOperator == pcode__ADD) long_ = L_integer_ + R_long_;
    else if (cOperator == pcode__SUB) long_ = L_integer_ - R_long_;
    //else if (cOperator == pcode__DIV){ if (R_long_ == 0){ runtimeError("division by zero", 11); return; } long_ = L_integer_ / R_long_; }
    else if (cOperator == pcode__MOD){ if (R_long_ == 0){ runtimeError("MOD by zero", 11); return; } long_ = L_integer_ % R_long_; }
    else if (cOperator == pcode__IDIV){ if (R_long_ == 0){ runtimeError("integer division by zero", 11); return; } long_ = L_integer_ / R_long_; }
    else if (cOperator == pcode__EQUAL) 				long_ = L_integer_ == R_long_;
    else if (cOperator == pcode__EQV) 				long_ = L_integer_ == R_long_;
    else if (cOperator == pcode__UNEQUAL) 			long_ = L_integer_ != R_long_;
    else if (cOperator == pcode__GREATER) 			long_ = L_integer_ > R_long_;
    else if (cOperator == pcode__LESSER) 				long_ = L_integer_ < R_long_;
    else if (cOperator == pcode__GREATER_EQUAL) long_ = L_integer_ >= R_long_;
    else if (cOperator == pcode__LESSER_EQUAL) 	long_ = L_integer_ <= R_long_;
    else { runtimeError("unknown operator"); return; }

		if (remove == false) myStack->restoreStack();
 	  myStack->pushLong(long_); 
#ifdef HAS_CONSOLE
    if (!bSilent) sprintf(acStringOutputBuffer, "%d %s %I64d --> %I64d", L_integer_, c, R_long_, long_);
#endif

  } else if (RType == pcode__SINGLE){
         if (cOperator == pcode__MUL) double_ = L_integer_ * R_single_;
    else if (cOperator == pcode__AND) double_ = L_integer_ & (t_long) R_single_;
    else if (cOperator == pcode__OR)  double_ = L_integer_ | (t_long) R_single_;
    else if (cOperator == pcode__XOR) double_ = L_integer_ ^ (t_long) R_single_;
    else if (cOperator == pcode__IMP) double_ = !(L_integer_ != 0 && R_single_ == 0);
    else if (cOperator == pcode__POWER) double_ = pow((t_double) L_integer_, (t_double) R_single_);
    else if (cOperator == pcode__ADD) double_ = L_integer_ + R_single_;
    else if (cOperator == pcode__SUB) double_ = L_integer_ - R_single_;
    //else if (cOperator == pcode__DIV){ if (R_single_ == 0){ runtimeError("division by zero", 11); return; } double_ = L_integer_ / R_single_; }
    else if (cOperator == pcode__MOD){ if (R_single_ == 0){ runtimeError("MOD by zero", 11); return; } double_ = L_integer_ % (t_long) R_single_; }
    else if (cOperator == pcode__IDIV){ if (R_single_ == 0){ runtimeError("integer division by zero", 11); return; } double_ = (t_long) (L_integer_ / R_single_); }
    else if (cOperator == pcode__EQUAL) 				double_ = L_integer_ == R_single_;
    else if (cOperator == pcode__EQV) 				double_ = L_integer_ == R_single_;
    else if (cOperator == pcode__UNEQUAL) 			double_ = L_integer_ != R_single_;
    else if (cOperator == pcode__GREATER) 			double_ = L_integer_ > R_single_;
    else if (cOperator == pcode__LESSER) 				double_ = L_integer_ < R_single_;
    else if (cOperator == pcode__GREATER_EQUAL) double_ = L_integer_ >= R_single_;
    else if (cOperator == pcode__LESSER_EQUAL) 	double_ = L_integer_ <= R_single_;
    else { runtimeError("unknown operator"); return; }

		if (remove == false) myStack->restoreStack();
    myStack->pushDouble(double_); 
#ifdef HAS_CONSOLE
    if (!bSilent) sprintf(acStringOutputBuffer, "%d %s %.6f --> %.6f", L_integer_, c, R_single_, double_);
#endif

  } else if (RType == pcode__DOUBLE){
         if (cOperator == pcode__MUL) double_ = L_integer_ * R_double_;
    else if (cOperator == pcode__AND) double_ = L_integer_ & (t_long) R_double_;
    else if (cOperator == pcode__OR)  double_ = L_integer_ | (t_long) R_double_;
    else if (cOperator == pcode__XOR) double_ = L_integer_ ^ (t_long) R_double_;
    else if (cOperator == pcode__IMP) double_ = !(L_integer_ != 0 && R_double_ == 0);
    else if (cOperator == pcode__POWER) double_ = (t_integer) pow((t_double) L_integer_, R_double_);
    else if (cOperator == pcode__ADD) double_ = L_integer_ + R_double_;
    else if (cOperator == pcode__SUB) double_ = L_integer_ - R_double_;
    //else if (cOperator == pcode__DIV){ if (R_double_ == 0){ runtimeError("division by zero", 11); return; } double_ = L_integer_ / R_double_; }
    else if (cOperator == pcode__MOD){ if (R_double_ == 0){ runtimeError("MOD by zero", 11); return; } double_ = L_integer_ % (t_long) R_double_; }
    else if (cOperator == pcode__IDIV){ if (R_double_ == 0){ runtimeError("integer division by zero", 11); return; } double_ = (t_long) (L_integer_ / R_double_); }
    else if (cOperator == pcode__EQUAL) 				double_ = L_integer_ == R_double_;
    else if (cOperator == pcode__EQV) 				double_ = L_integer_ == R_double_;
    else if (cOperator == pcode__UNEQUAL) 			double_ = L_integer_ != R_double_;
    else if (cOperator == pcode__GREATER) 			double_ = L_integer_ > R_double_;
    else if (cOperator == pcode__LESSER) 				double_ = L_integer_ < R_double_;
    else if (cOperator == pcode__GREATER_EQUAL) double_ = L_integer_ >= R_double_;
    else if (cOperator == pcode__LESSER_EQUAL) 	double_ = L_integer_ <= R_double_;
    else { runtimeError("unknown operator"); return; }

		if (remove == false) myStack->restoreStack();
    myStack->pushDouble(double_); 
#ifdef HAS_CONSOLE
    if (!bSilent) sprintf(acStringOutputBuffer, "%d %s %.6f --> %.6f", L_integer_, c, R_double_, double_);
#endif

  } else if (RType == pcode__CURRENCY){

    t_currency t(L_integer_, 0);

         if (cOperator == pcode__MUL) currency_.setValue(t.bc() * R_currency_.bc(), t.bc() * R_currency_.ad());
    else if (cOperator == pcode__AND) currency_.setValue(t.bc() & R_currency_.bc(), t.ad() & R_currency_.ad());
    else if (cOperator == pcode__OR)  currency_.setValue(t.bc() | R_currency_.bc(), t.ad() | R_currency_.ad());
    else if (cOperator == pcode__XOR) currency_.setValue(t.bc() ^ R_currency_.bc(), t.ad() ^ R_currency_.ad());
    else if (cOperator == pcode__IMP) currency_.setValue(!(t.getValue() != 0 && R_currency_.getValue() == 0), 0);
    else if (cOperator == pcode__POWER) currency_.setValue((t_long) pow((t_double) t.bc(), (t_double) R_currency_.toDouble()), 0);
    else if (cOperator == pcode__ADD) currency_.setValue(t.bc() + R_currency_.bc(), t.ad() + R_currency_.ad());
    else if (cOperator == pcode__SUB) currency_.setValue(t.bc() - R_currency_.bc(), t.ad() - R_currency_.ad());
    //else if (cOperator == pcode__DIV){ if (R_currency_.getValue() == 0){ runtimeError("division by zero", 11); return; } currency_.setValue(t.bc() / R_currency_.bc(), t.ad() / R_currency_.ad()); }
    else if (cOperator == pcode__MOD){ if (R_currency_.getValue() == 0){ runtimeError("MOD by zero", 11); return; } currency_.setValue(t.bc() % R_currency_.bc(), t.ad() % R_currency_.ad()); }
    else if (cOperator == pcode__IDIV){ if (R_currency_.getValue() == 0){ runtimeError("integer division by zero", 11); return; } currency_.setValue(t.bc() / R_currency_.bc(), t.ad() / R_currency_.ad()); }
    else if (cOperator == pcode__EQUAL) 				currency_.setValue(t.getValue() == R_currency_.getValue(), 0);
    else if (cOperator == pcode__EQV) 				currency_.setValue(t.getValue() == R_currency_.getValue(), 0);
    else if (cOperator == pcode__UNEQUAL) 			currency_.setValue(t.getValue() != R_currency_.getValue(), 0);
    else if (cOperator == pcode__GREATER) 			currency_.setValue(t.getValue() > R_currency_.getValue(), 0);
    else if (cOperator == pcode__LESSER) 				currency_.setValue(t.getValue() < R_currency_.getValue(), 0);
    else if (cOperator == pcode__GREATER_EQUAL) currency_.setValue(t.getValue() >= R_currency_.getValue(), 0);
    else if (cOperator == pcode__LESSER_EQUAL) currency_.setValue(t.getValue() <= R_currency_.getValue(), 0);
    else { runtimeError("unknown operator"); return; }

		if (remove == false) myStack->restoreStack();
 	  myStack->pushCurrency(currency_); 
#ifdef HAS_CONSOLE
    if (!bSilent) sprintf(acStringOutputBuffer, "%d %s %s --> %s", (t_integer) t.bc(), c, R_currency_.toCString(), currency_.toCString2());
#endif

  }


	
  // pcode__LONG ***
  } else if (LType == pcode__LONG){
  if (RType == pcode__BOOLEAN){
         if (cOperator == pcode__MUL) long_ = L_long_ * R_boolean_;
    else if (cOperator == pcode__AND) long_ = L_long_ & R_boolean_;
    else if (cOperator == pcode__OR)  long_ = L_long_ | R_boolean_;
    else if (cOperator == pcode__XOR) long_ = L_long_ ^ R_boolean_;
    else if (cOperator == pcode__IMP) long_ = !(L_long_ != 0 && R_boolean_ == 0);
    else if (cOperator == pcode__POWER) long_ = (t_long) pow((t_double) L_long_, (t_double) R_boolean_);
    else if (cOperator == pcode__ADD) long_ = L_long_ + R_boolean_;
    else if (cOperator == pcode__SUB) long_ = L_long_ - R_boolean_;
    //else if (cOperator == pcode__DIV){ if (R_boolean_ == 0){ runtimeError("division by zero", 11); return; } long_ = L_long_ / R_boolean_; }
    else if (cOperator == pcode__MOD){ if (R_boolean_ == 0){ runtimeError("MOD by zero", 11); return; } long_ = L_long_ % R_boolean_; }
    else if (cOperator == pcode__IDIV){ if (R_boolean_ == 0){ runtimeError("integer division by zero", 11); return; } long_ = L_long_ / R_boolean_; }
    else if (cOperator == pcode__EQUAL) 				long_ = L_long_ == R_boolean_;
    else if (cOperator == pcode__EQV) 				long_ = L_long_ == R_boolean_;
    else if (cOperator == pcode__UNEQUAL) 			long_ = L_long_ != R_boolean_;
    else if (cOperator == pcode__GREATER) 			long_ = L_long_ > R_boolean_;
    else if (cOperator == pcode__LESSER) 				long_ = L_long_ < R_boolean_;
    else if (cOperator == pcode__GREATER_EQUAL) long_ = L_long_ >= R_boolean_;
    else if (cOperator == pcode__LESSER_EQUAL) 	long_ = L_long_ <= R_boolean_;
    else { runtimeError("unknown operator"); return; }

		if (remove == false) myStack->restoreStack();
 	  myStack->pushLong(long_); 
#ifdef HAS_CONSOLE
    if (!bSilent) sprintf(acStringOutputBuffer, "%I64d %s %d --> %I64d", L_long_, c, (t_integer) R_boolean_, long_);
#endif

  } else if (RType == pcode__QSTRING){

     if (cOperator == pcode__ADD){
			 int nId = estatics->declare(pcode__QSTRING, 0, false, false);
    	 estatics->setQString_Long(nId, L_long_, R_qstring_, 0);
			 myStack->pushEQString(nId);
#ifdef HAS_CONSOLE
			 if (!bSilent) sprintf(acStringOutputBuffer, "Unicode");
//			 if (!bSilent) sprintf(acStringOutputBuffer, "%I64d %s \"%-30.30s\" --> \"%-30.30s\"", L_long_, c, R_string_, estatics->getString(nId));
#endif
     } else { runtimeError("unknown operator"); return; }

  } else if (RType == pcode__CSTRING){

     if (cOperator == pcode__ADD){
			 int nId = estatics->declare(pcode__CSTRING, 0, false, false);
    	 estatics->setCString_Long(nId, L_long_, R_cstring_, 0);
			 myStack->pushECString(nId);
#ifdef HAS_CONSOLE
			 if (!bSilent) sprintf(acStringOutputBuffer, "%I64d %s \"%-30.30s\" --> \"%-30.30s\"", L_long_, c, R_cstring_, estatics->getCString(nId));
#endif

    } else if (cOperator == pcode__EQUAL || cOperator == pcode__UNEQUAL){ // special handling for INKEY used
		  boolean_ = L_long_ == 0 && strcmp("", R_cstring_) == 0;
		  if (remove == false) myStack->restoreStack();
		  myStack->pushBoolean(boolean_); 
#ifdef HAS_CONSOLE
      if (!bSilent) sprintf(acStringOutputBuffer, "%d %s %s --> %d", (t_integer) L_long_, c, R_cstring_, (t_integer) boolean_);
#endif
    } else { runtimeError("unknown operator"); return; } 

  } else if (RType == pcode__BYTE){
         if (cOperator == pcode__MUL) long_ = L_long_ * R_byte_;
    else if (cOperator == pcode__AND) long_ = L_long_ & R_byte_;
    else if (cOperator == pcode__OR)  long_ = L_long_ | R_byte_;
    else if (cOperator == pcode__XOR) long_ = L_long_ ^ R_byte_;
    else if (cOperator == pcode__IMP) long_ = !(L_long_ != 0 && R_byte_ == 0);
    else if (cOperator == pcode__POWER) long_ = (t_long) pow((t_double) L_long_, (t_double) R_byte_);
    else if (cOperator == pcode__ADD) long_ = L_long_ + R_byte_;
    else if (cOperator == pcode__SUB) long_ = L_long_ - R_byte_;
    //else if (cOperator == pcode__DIV){ if (R_byte_ == 0){ runtimeError("division by zero", 11); return; } long_ = L_long_ / R_byte_; }
    else if (cOperator == pcode__MOD){ if (R_byte_ == 0){ runtimeError("MOD by zero", 11); return; } long_ = L_long_ % R_byte_; }
    else if (cOperator == pcode__IDIV){ if (R_byte_ == 0){ runtimeError("integer division by zero", 11); return; } long_ = L_long_ / R_byte_; }
    else if (cOperator == pcode__EQUAL) 				long_ = L_long_ == R_byte_;
    else if (cOperator == pcode__EQV) 				long_ = L_long_ == R_byte_;
    else if (cOperator == pcode__UNEQUAL) 			long_ = L_long_ != R_byte_;
    else if (cOperator == pcode__GREATER) 			long_ = L_long_ > R_byte_;
    else if (cOperator == pcode__LESSER) 				long_ = L_long_ < R_byte_;
    else if (cOperator == pcode__GREATER_EQUAL) long_ = L_long_ >= R_byte_;
    else if (cOperator == pcode__LESSER_EQUAL) 	long_ = L_long_ <= R_byte_;
    else { runtimeError("unknown operator"); return; }

		if (remove == false) myStack->restoreStack();
 	  myStack->pushLong(long_); 
#ifdef HAS_CONSOLE
    if (!bSilent) sprintf(acStringOutputBuffer, "%I64d %s %d --> %I64d", L_long_, c, (t_integer) R_byte_, long_);
#endif

  } else if (RType == pcode__SHORT){
         if (cOperator == pcode__MUL) long_ = L_long_ * R_short_;
    else if (cOperator == pcode__AND) long_ = L_long_ & R_short_;
    else if (cOperator == pcode__OR)  long_ = L_long_ | R_short_;
    else if (cOperator == pcode__XOR) long_ = L_long_ ^ R_short_;
    else if (cOperator == pcode__IMP) long_ = !(L_long_ != 0 && R_short_ == 0);
    else if (cOperator == pcode__POWER) long_ = (t_long) pow((t_double) L_long_, (t_double) R_short_);
    else if (cOperator == pcode__ADD) long_ = L_long_ + R_short_;
    else if (cOperator == pcode__SUB) long_ = L_long_ - R_short_;
    //else if (cOperator == pcode__DIV){ if (R_short_ == 0){ runtimeError("division by zero", 11); return; } long_ = L_long_ / R_short_; }
    else if (cOperator == pcode__MOD){ if (R_short_ == 0){ runtimeError("MOD by zero", 11); return; } long_ = L_long_ % R_short_; }
    else if (cOperator == pcode__IDIV){ if (R_short_ == 0){ runtimeError("integer division by zero", 11); return; } long_ = L_long_ / R_short_; }
    else if (cOperator == pcode__EQUAL) 				long_ = L_long_ == R_short_;
    else if (cOperator == pcode__EQV) 				long_ = L_long_ == R_short_;
    else if (cOperator == pcode__UNEQUAL) 			long_ = L_long_ != R_short_;
    else if (cOperator == pcode__GREATER) 			long_ = L_long_ > R_short_;
    else if (cOperator == pcode__LESSER) 				long_ = L_long_ < R_short_;
    else if (cOperator == pcode__GREATER_EQUAL) long_ = L_long_ >= R_short_;
    else if (cOperator == pcode__LESSER_EQUAL) 	long_ = L_long_ <= R_short_;
    else { runtimeError("unknown operator"); return; }

		if (remove == false) myStack->restoreStack();
 	  myStack->pushLong(long_); 
#ifdef HAS_CONSOLE
    if (!bSilent) sprintf(acStringOutputBuffer, "%I64d %s %d --> %I64d", L_long_, c, (t_integer) R_short_, long_);
#endif

  } else if (RType == pcode__INTEGER){
         if (cOperator == pcode__MUL) long_ = L_long_ * R_integer_;
    else if (cOperator == pcode__AND) long_ = L_long_ & R_integer_;
    else if (cOperator == pcode__OR)  long_ = L_long_ | R_integer_;
    else if (cOperator == pcode__XOR) long_ = L_long_ ^ R_integer_;
    else if (cOperator == pcode__IMP) long_ = !(L_long_ != 0 && R_integer_ == 0);
    else if (cOperator == pcode__POWER) long_ = (t_long) pow((t_double) L_long_, (t_double) R_integer_);
    else if (cOperator == pcode__ADD) long_ = L_long_ + R_integer_;
    else if (cOperator == pcode__SUB) long_ = L_long_ - R_integer_;
    //else if (cOperator == pcode__DIV){ if (R_integer_ == 0){ runtimeError("division by zero", 11); return; } long_ = L_long_ / R_integer_; }
    else if (cOperator == pcode__MOD){ if (R_integer_ == 0){ runtimeError("MOD by zero", 11); return; } long_ = L_long_ % R_integer_; }
    else if (cOperator == pcode__IDIV){ if (R_integer_ == 0){ runtimeError("integer division by zero", 11); return; } long_ = L_long_ / R_integer_; }
    else if (cOperator == pcode__EQUAL) 				long_ = L_long_ == R_integer_;
    else if (cOperator == pcode__EQV) 				long_ = L_long_ == R_integer_;
    else if (cOperator == pcode__UNEQUAL) 			long_ = L_long_ != R_integer_;
    else if (cOperator == pcode__GREATER) 			long_ = L_long_ > R_integer_;
    else if (cOperator == pcode__LESSER) 				long_ = L_long_ < R_integer_;
    else if (cOperator == pcode__GREATER_EQUAL) long_ = L_long_ >= R_integer_;
    else if (cOperator == pcode__LESSER_EQUAL) 	long_ = L_long_ <= R_integer_;
    else { runtimeError("unknown operator"); return; }

		if (remove == false) myStack->restoreStack();
 	  myStack->pushLong(long_); 
#ifdef HAS_CONSOLE
    if (!bSilent) sprintf(acStringOutputBuffer, "%I64d %s %d --> %I64d", L_long_, c, R_integer_, long_);
#endif

  } else if (RType ==  pcode__LONG){
         if (cOperator == pcode__MUL) long_ = L_long_ * R_long_;
    else if (cOperator == pcode__AND) long_ = L_long_ & R_long_;
    else if (cOperator == pcode__OR)  long_ = L_long_ | R_long_;
    else if (cOperator == pcode__XOR) long_ = L_long_ ^ R_long_;
    else if (cOperator == pcode__IMP) long_ = !(L_long_ != 0 && R_long_ == 0);
    else if (cOperator == pcode__POWER) long_ = (t_long) pow((t_double) L_long_, (t_double) R_long_);
    else if (cOperator == pcode__ADD) long_ = L_long_ + R_long_;
    else if (cOperator == pcode__SUB) long_ = L_long_ - R_long_;
    //else if (cOperator == pcode__DIV){ if (R_long_ == 0){ runtimeError("division by zero", 11); return; } long_ = L_long_ / R_long_; }
    else if (cOperator == pcode__MOD){ if (R_long_ == 0){ runtimeError("MOD by zero", 11); return; } long_ = L_long_ % R_long_; }
    else if (cOperator == pcode__IDIV){ if (R_long_ == 0){ runtimeError("integer division by zero", 11); return; } long_ = L_long_ / R_long_; }
    else if (cOperator == pcode__EQUAL) 				long_ = L_long_ == R_long_;
    else if (cOperator == pcode__EQV) 				long_ = L_long_ == R_long_;
    else if (cOperator == pcode__UNEQUAL) 			long_ = L_long_ != R_long_;
    else if (cOperator == pcode__GREATER) 			long_ = L_long_ > R_long_;
    else if (cOperator == pcode__LESSER) 				long_ = L_long_ < R_long_;
    else if (cOperator == pcode__GREATER_EQUAL) long_ = L_long_ >= R_long_;
    else if (cOperator == pcode__LESSER_EQUAL) 	long_ = L_long_ <= R_long_;
    else { runtimeError("unknown operator"); return; }

		if (remove == false) myStack->restoreStack();
 	  myStack->pushLong(long_); 
#ifdef HAS_CONSOLE
    if (!bSilent) sprintf(acStringOutputBuffer, "%I64d %s %I64d --> %I64d", L_long_, c, R_long_, long_);
#endif

  } else if (RType == pcode__SINGLE){
         if (cOperator == pcode__MUL) single_ = L_long_ * R_single_;
    else if (cOperator == pcode__AND) single_ = L_long_ & (t_long) R_single_;
    else if (cOperator == pcode__OR)  single_ = L_long_ | (t_long) R_single_;
    else if (cOperator == pcode__XOR) single_ = L_long_ ^ (t_long) R_single_;
    else if (cOperator == pcode__IMP) single_ = !(L_long_ != 0 && R_single_ == 0);
    else if (cOperator == pcode__POWER) single_ = pow((t_double) L_long_, (t_double) R_single_);
    else if (cOperator == pcode__ADD) single_ = L_long_ + R_single_;
    else if (cOperator == pcode__SUB) single_ = L_long_ - R_single_;
    //else if (cOperator == pcode__DIV){ if (R_single_ == 0){ runtimeError("division by zero", 11); return; } single_ = L_long_ / R_single_; }
    else if (cOperator == pcode__MOD){ if (R_single_ == 0){ runtimeError("MOD by zero", 11); return; } single_ = L_long_ % (t_long) R_single_; }
    else if (cOperator == pcode__IDIV){ if (R_single_ == 0){ runtimeError("integer division by zero", 11); return; } single_ = (t_long) (L_long_ / R_single_); }
    else if (cOperator == pcode__EQUAL) 				single_ = L_long_ == R_single_;
    else if (cOperator == pcode__EQV) 				single_ = L_long_ == R_single_;
    else if (cOperator == pcode__UNEQUAL) 			single_ = L_long_ != R_single_;
    else if (cOperator == pcode__GREATER) 			single_ = L_long_ > R_single_;
    else if (cOperator == pcode__LESSER) 				single_ = L_long_ < R_single_;
    else if (cOperator == pcode__GREATER_EQUAL) single_ = L_long_ >= R_single_;
    else if (cOperator == pcode__LESSER_EQUAL) 	single_ = L_long_ <= R_single_;
    else { runtimeError("unknown operator"); return; }

		if (remove == false) myStack->restoreStack();
    myStack->pushSingle(single_); 
#ifdef HAS_CONSOLE
    if (!bSilent) sprintf(acStringOutputBuffer, "%I64d %s %.6f --> %.6f", L_long_, c, R_single_, single_);
#endif

  } else if (RType == pcode__DOUBLE){
         if (cOperator == pcode__MUL) double_ = L_long_ * R_double_;
    else if (cOperator == pcode__AND) double_ = L_long_ & (t_long) R_double_;
    else if (cOperator == pcode__OR)  double_ = L_long_ | (t_long) R_double_;
    else if (cOperator == pcode__XOR) double_ = L_long_ ^ (t_long) R_double_;
    else if (cOperator == pcode__IMP) double_ = !(L_long_ != 0 && R_double_ == 0);
    else if (cOperator == pcode__POWER) double_ = (t_long) pow((t_double) L_long_, R_double_);
    else if (cOperator == pcode__ADD) double_ = L_long_ + R_double_;
    else if (cOperator == pcode__SUB) double_ = L_long_ - R_double_;
    //else if (cOperator == pcode__DIV){ if (R_double_ == 0){ runtimeError("division by zero", 11); return; } double_ = L_long_ / R_double_; }
    else if (cOperator == pcode__MOD){ if (R_double_ == 0){ runtimeError("MOD by zero", 11); return; } double_ = L_long_ % (t_long) R_double_; }
    else if (cOperator == pcode__IDIV){ if (R_double_ == 0){ runtimeError("integer division by zero", 11); return; } double_ = (t_long) (L_long_ / R_double_); }
    else if (cOperator == pcode__EQUAL) 				double_ = L_long_ == R_double_;
    else if (cOperator == pcode__EQV) 				double_ = L_long_ == R_double_;
    else if (cOperator == pcode__UNEQUAL) 			double_ = L_long_ != R_double_;
    else if (cOperator == pcode__GREATER) 			double_ = L_long_ > R_double_;
    else if (cOperator == pcode__LESSER) 				double_ = L_long_ < R_double_;
    else if (cOperator == pcode__GREATER_EQUAL) double_ = L_long_ >= R_double_;
    else if (cOperator == pcode__LESSER_EQUAL) 	double_ = L_long_ <= R_double_;
    else { runtimeError("unknown operator"); return; }

		if (remove == false) myStack->restoreStack();
    myStack->pushDouble(double_); 
#ifdef HAS_CONSOLE
    if (!bSilent) sprintf(acStringOutputBuffer, "%I64d %s %.6f --> %.6f", L_long_, c, R_double_, double_);
#endif

  } else if (RType == pcode__CURRENCY){

    t_currency t(L_long_, 0);

         if (cOperator == pcode__MUL) currency_.setValue(t.bc() * R_currency_.bc(), t.bc() * R_currency_.ad());
    else if (cOperator == pcode__AND) currency_.setValue(t.bc() & R_currency_.bc(), t.ad() & R_currency_.ad());
    else if (cOperator == pcode__OR)  currency_.setValue(t.bc() | R_currency_.bc(), t.ad() | R_currency_.ad());
    else if (cOperator == pcode__XOR) currency_.setValue(t.bc() ^ R_currency_.bc(), t.ad() ^ R_currency_.ad());
    else if (cOperator == pcode__IMP) currency_.setValue(!(t.getValue() != 0 && R_currency_.getValue() == 0), 0);
    else if (cOperator == pcode__POWER) currency_.setValue((t_long) pow((t_double) t.bc(), (t_double) R_currency_.toDouble()), 0);
    else if (cOperator == pcode__ADD) currency_.setValue(t.bc() + R_currency_.bc(), t.ad() + R_currency_.ad());
    else if (cOperator == pcode__SUB) currency_.setValue(t.bc() - R_currency_.bc(), t.ad() - R_currency_.ad());
    //else if (cOperator == pcode__DIV){ if (R_currency_.getValue() == 0){ runtimeError("division by zero", 11); return; } currency_.setValue(t.bc() / R_currency_.bc(), t.ad() / R_currency_.ad()); }
    else if (cOperator == pcode__MOD){ if (R_currency_.getValue() == 0){ runtimeError("MOD by zero", 11); return; } currency_.setValue(t.bc() % R_currency_.bc(), t.ad() % R_currency_.ad()); }
    else if (cOperator == pcode__IDIV){ if (R_currency_.getValue() == 0){ runtimeError("integer division by zero", 11); return; } currency_.setValue(t.bc() / R_currency_.bc(), t.ad() / R_currency_.ad()); }
    else if (cOperator == pcode__EQUAL) 				currency_.setValue(t.getValue() == R_currency_.getValue(), 0);
    else if (cOperator == pcode__EQV) 				currency_.setValue(t.getValue() == R_currency_.getValue(), 0);
    else if (cOperator == pcode__UNEQUAL) 			currency_.setValue(t.getValue() != R_currency_.getValue(), 0);
    else if (cOperator == pcode__GREATER) 			currency_.setValue(t.getValue() > R_currency_.getValue(), 0);
    else if (cOperator == pcode__LESSER) 				currency_.setValue(t.getValue() < R_currency_.getValue(), 0);
    else if (cOperator == pcode__GREATER_EQUAL) currency_.setValue(t.getValue() >= R_currency_.getValue(), 0);
    else if (cOperator == pcode__LESSER_EQUAL) currency_.setValue(t.getValue() <= R_currency_.getValue(), 0);
    else { runtimeError("unknown operator"); return; }

		if (remove == false) myStack->restoreStack();
 	  myStack->pushCurrency(currency_); 
#ifdef HAS_CONSOLE
    if (!bSilent) sprintf(acStringOutputBuffer, "%d %s %s --> %s", (t_integer) t.bc(), c, R_currency_.toCString(), currency_.toCString2());
#endif
  }
  // pcode__SINGLE ***
  } else if (LType == pcode__SINGLE){
  if (RType == pcode__BOOLEAN){
         if (cOperator == pcode__MUL) double_ = L_single_ * R_boolean_;
    else if (cOperator == pcode__AND) double_ = (t_long) L_single_ & R_boolean_;
    else if (cOperator == pcode__OR)  double_ = (t_long) L_single_ | R_boolean_;
    else if (cOperator == pcode__XOR) double_ = (t_long) L_single_ ^ R_boolean_;
    else if (cOperator == pcode__IMP) double_ = !(L_single_ != 0 && R_boolean_ == 0);
    else if (cOperator == pcode__POWER) double_ = pow((t_double) L_single_, (t_double) R_boolean_);
    else if (cOperator == pcode__ADD) double_ = L_single_ + R_boolean_;
    else if (cOperator == pcode__SUB) double_ = L_single_ - R_boolean_;
    //else if (cOperator == pcode__DIV){ if (R_boolean_ == 0){ runtimeError("division by zero", 11); return; } double_ = L_single_ / R_boolean_; }
    else if (cOperator == pcode__MOD){ if (R_boolean_ == 0){ runtimeError("MOD by zero", 11); return; } double_ = (t_long) L_single_ % R_boolean_; }
    else if (cOperator == pcode__IDIV){ if (R_boolean_ == 0){ runtimeError("integer division by zero", 11); return; } double_ = (t_long) (L_single_ / R_boolean_); }
    else if (cOperator == pcode__EQUAL) 				double_ = L_single_ == R_boolean_;
    else if (cOperator == pcode__EQV) 				double_ = L_single_ == R_boolean_;
    else if (cOperator == pcode__UNEQUAL) 			double_ = L_single_ != R_boolean_;
    else if (cOperator == pcode__GREATER) 			double_ = L_single_ > R_boolean_;
    else if (cOperator == pcode__LESSER) 				double_ = L_single_ < R_boolean_;
    else if (cOperator == pcode__GREATER_EQUAL) double_ = L_single_ >= R_boolean_;
    else if (cOperator == pcode__LESSER_EQUAL) 	double_ = L_single_ <= R_boolean_;
    else { runtimeError("unknown operator"); return; }

		if (remove == false) myStack->restoreStack();
    myStack->pushDouble(double_); 
#ifdef HAS_CONSOLE
    if (!bSilent) sprintf(acStringOutputBuffer, "%.6f %s %d --> %.6f", L_single_, c, (t_integer) R_boolean_, double_);
#endif

  } else if (RType == pcode__QSTRING){

     if (cOperator == pcode__ADD){
			 int nId = estatics->declare(pcode__QSTRING, 0, false, false);
    	 estatics->setQString_Single(nId, L_single_, R_qstring_, 0);
			 myStack->pushEQString(nId);
#ifdef HAS_CONSOLE
			 if (!bSilent) sprintf(acStringOutputBuffer, "Unicode");
//			 if (!bSilent) sprintf(acStringOutputBuffer, "%.6f %s \"%-30.30s\" --> \"%-30.30s\"", L_single_, c, R_string_, estatics->getString(nId));
#endif
     } else { runtimeError("unknown operator"); return; }

  } else if (RType == pcode__CSTRING){

     if (cOperator == pcode__ADD){
			 int nId = estatics->declare(pcode__CSTRING, 0, false, false);
    	 estatics->setCString_Single(nId, L_single_, R_cstring_, 0);
			 myStack->pushECString(nId);
#ifdef HAS_CONSOLE
			 if (!bSilent) sprintf(acStringOutputBuffer, "%.6f %s \"%-30.30s\" --> \"%-30.30s\"", L_single_, c, R_cstring_, estatics->getCString(nId));
#endif
     } else { runtimeError("unknown operator"); return; }

  } else if (RType == pcode__BYTE){
         if (cOperator == pcode__MUL) double_ = L_single_ * R_byte_;
    else if (cOperator == pcode__AND) double_ = (t_long) L_single_ & R_byte_;
    else if (cOperator == pcode__OR)  double_ = (t_long) L_single_ | R_byte_;
    else if (cOperator == pcode__XOR) double_ = (t_long) L_single_ ^ R_byte_;
    else if (cOperator == pcode__IMP) double_ = !(L_single_ != 0 && R_byte_ == 0);
    else if (cOperator == pcode__POWER) double_ = pow((t_double) L_single_, (t_double) R_byte_);
    else if (cOperator == pcode__ADD) double_ = L_single_ + R_byte_;
    else if (cOperator == pcode__SUB) double_ = L_single_ - R_byte_;
    //else if (cOperator == pcode__DIV){ if (R_byte_ == 0){ runtimeError("division by zero", 11); return; } double_ = L_single_ / R_byte_; }
    else if (cOperator == pcode__MOD){ if (R_byte_ == 0){ runtimeError("MOD by zero", 11); return; } double_ = (t_long) L_single_ % R_byte_; }
    else if (cOperator == pcode__IDIV){ if (R_byte_ == 0){ runtimeError("integer division by zero", 11); return; } double_ = (t_long) (L_single_ / R_byte_); }
    else if (cOperator == pcode__EQUAL) 				double_ = L_single_ == R_byte_;
    else if (cOperator == pcode__EQV) 				double_ = L_single_ == R_byte_;
    else if (cOperator == pcode__UNEQUAL) 			double_ = L_single_ != R_byte_;
    else if (cOperator == pcode__GREATER) 			double_ = L_single_ > R_byte_;
    else if (cOperator == pcode__LESSER) 				double_ = L_single_ < R_byte_;
    else if (cOperator == pcode__GREATER_EQUAL) double_ = L_single_ >= R_byte_;
    else if (cOperator == pcode__LESSER_EQUAL) 	double_ = L_single_ <= R_byte_;
    else { runtimeError("unknown operator"); return; }

		if (remove == false) myStack->restoreStack();
    myStack->pushDouble(double_); 
#ifdef HAS_CONSOLE
    if (!bSilent) sprintf(acStringOutputBuffer, "%.6f %s %d --> %.6f", L_single_, c, (t_integer) R_byte_, double_);
#endif

  } else if (RType == pcode__SHORT){
         if (cOperator == pcode__MUL) double_ = L_single_ * R_short_;
    else if (cOperator == pcode__AND) double_ = (t_long) L_single_ & R_short_;
    else if (cOperator == pcode__OR)  double_ = (t_long) L_single_ | R_short_;
    else if (cOperator == pcode__XOR) double_ = (t_long) L_single_ ^ R_short_;
    else if (cOperator == pcode__IMP) double_ = !(L_single_ != 0 && R_short_ == 0);
    else if (cOperator == pcode__POWER) double_ = pow((t_double) L_single_, (t_double) R_short_);
    else if (cOperator == pcode__ADD) double_ = L_single_ + R_short_;
    else if (cOperator == pcode__SUB) double_ = L_single_ - R_short_;
    //else if (cOperator == pcode__DIV){ if (R_short_ == 0){ runtimeError("division by zero", 11); return; } double_ = L_single_ / R_short_; }
    else if (cOperator == pcode__MOD){ if (R_short_ == 0){ runtimeError("MOD by zero", 11); return; } double_ = (t_long) L_single_ % R_short_; }
    else if (cOperator == pcode__IDIV){ if (R_short_ == 0){ runtimeError("integer division by zero", 11); return; } double_ = (t_long) (L_single_ / R_short_); }
    else if (cOperator == pcode__EQUAL) 				double_ = L_single_ == R_short_;
    else if (cOperator == pcode__EQV) 				double_ = L_single_ == R_short_;
    else if (cOperator == pcode__UNEQUAL) 			double_ = L_single_ != R_short_;
    else if (cOperator == pcode__GREATER) 			double_ = L_single_ > R_short_;
    else if (cOperator == pcode__LESSER) 				double_ = L_single_ < R_short_;
    else if (cOperator == pcode__GREATER_EQUAL) double_ = L_single_ >= R_short_;
    else if (cOperator == pcode__LESSER_EQUAL) 	double_ = L_single_ <= R_short_;
    else { runtimeError("unknown operator"); return; }

		if (remove == false) myStack->restoreStack();
    myStack->pushDouble(double_); 
#ifdef HAS_CONSOLE
    if (!bSilent) sprintf(acStringOutputBuffer, "%.6f %s %d --> %.6f", L_single_, c, (t_integer) R_short_, double_);
#endif

  } else if (RType == pcode__INTEGER){
         if (cOperator == pcode__MUL) double_ = L_single_ * R_integer_;
    else if (cOperator == pcode__AND) double_ = (t_long) L_single_ & R_integer_;
    else if (cOperator == pcode__OR)  double_ = (t_long) L_single_ | R_integer_;
    else if (cOperator == pcode__XOR) double_ = (t_long) L_single_ ^ R_integer_;
    else if (cOperator == pcode__IMP) double_ = !(L_single_ != 0 && R_integer_ == 0);
    else if (cOperator == pcode__POWER) double_ = pow((t_double) L_single_, (t_double) R_integer_);
    else if (cOperator == pcode__ADD) double_ = L_single_ + R_integer_;
    else if (cOperator == pcode__SUB) double_ = L_single_ - R_integer_;
    //else if (cOperator == pcode__DIV){ if (R_integer_ == 0){ runtimeError("division by zero", 11); return; } double_ = L_single_ / R_integer_; }
    else if (cOperator == pcode__MOD){ if (R_integer_ == 0){ runtimeError("MOD by zero", 11); return; } double_ = (t_long) L_single_ % R_integer_; }
    else if (cOperator == pcode__IDIV){ if (R_integer_ == 0){ runtimeError("integer division by zero", 11); return; } double_ = (t_long) (L_single_ / R_integer_); }
    else if (cOperator == pcode__EQUAL) 				double_ = L_single_ == R_integer_;
    else if (cOperator == pcode__EQV) 				double_ = L_single_ == R_integer_;
    else if (cOperator == pcode__UNEQUAL) 			double_ = L_single_ != R_integer_;
    else if (cOperator == pcode__GREATER) 			double_ = L_single_ > R_integer_;
    else if (cOperator == pcode__LESSER) 				double_ = L_single_ < R_integer_;
    else if (cOperator == pcode__GREATER_EQUAL) double_ = L_single_ >= R_integer_;
    else if (cOperator == pcode__LESSER_EQUAL) 	double_ = L_single_ <= R_integer_;
    else { runtimeError("unknown operator"); return; }

		if (remove == false) myStack->restoreStack();
    myStack->pushDouble(double_); 
#ifdef HAS_CONSOLE
    if (!bSilent) sprintf(acStringOutputBuffer, "%.6f %s %d --> %.6f", L_single_, c, R_integer_, double_);
#endif

  } else if (RType ==  pcode__LONG){
         if (cOperator == pcode__MUL) double_ = L_single_ * R_long_;
    else if (cOperator == pcode__AND) double_ = (t_long) L_single_ & R_long_;
    else if (cOperator == pcode__OR)  double_ = (t_long) L_single_ | R_long_;
    else if (cOperator == pcode__XOR) double_ = (t_long) L_single_ ^ R_long_;
    else if (cOperator == pcode__IMP) double_ = !(L_single_ != 0 && R_long_ == 0);
    else if (cOperator == pcode__POWER) double_ = pow((t_double) L_single_, (t_double) R_long_);
    else if (cOperator == pcode__ADD) double_ = L_single_ + R_long_;
    else if (cOperator == pcode__SUB) double_ = L_single_ - R_long_;
    //else if (cOperator == pcode__DIV){ if (R_long_ == 0){ runtimeError("division by zero", 11); return; } double_ = L_single_ / R_long_; }
    else if (cOperator == pcode__MOD){ if (R_long_ == 0){ runtimeError("MOD by zero", 11); return; } double_ = (t_long) L_single_ % R_long_; }
    else if (cOperator == pcode__IDIV){ if (R_long_ == 0){ runtimeError("integer division by zero", 11); return; } double_ = (t_long) (L_single_ / R_long_); }
    else if (cOperator == pcode__EQUAL) 				double_ = L_single_ == R_long_;
    else if (cOperator == pcode__EQV) 				double_ = L_single_ == R_long_;
    else if (cOperator == pcode__UNEQUAL) 			double_ = L_single_ != R_long_;
    else if (cOperator == pcode__GREATER) 			double_ = L_single_ > R_long_;
    else if (cOperator == pcode__LESSER) 				double_ = L_single_ < R_long_;
    else if (cOperator == pcode__GREATER_EQUAL) double_ = L_single_ >= R_long_;
    else if (cOperator == pcode__LESSER_EQUAL) 	double_ = L_single_ <= R_long_;
    else { runtimeError("unknown operator"); return; }

		if (remove == false) myStack->restoreStack();
    myStack->pushDouble(double_); 
#ifdef HAS_CONSOLE
    if (!bSilent) sprintf(acStringOutputBuffer, "%.6f %s %I64d --> %.6f", L_single_, c, R_long_, double_);
#endif

  } else if (RType == pcode__SINGLE){
         if (cOperator == pcode__MUL) double_ = L_single_ * R_single_;
    else if (cOperator == pcode__AND) double_ = (t_long) L_single_ & (t_long) R_single_;
    else if (cOperator == pcode__OR)  double_ = (t_long) L_single_ | (t_long) R_single_;
    else if (cOperator == pcode__XOR) double_ = (t_long) L_single_ ^ (t_long) R_single_;
    else if (cOperator == pcode__IMP) double_ = !(L_single_ != 0 && R_single_ == 0);
    else if (cOperator == pcode__POWER) double_ = pow((t_double) L_single_, (t_double) R_single_);
    else if (cOperator == pcode__ADD) double_ = L_single_ + R_single_;
    else if (cOperator == pcode__SUB) double_ = L_single_ - R_single_;
    //else if (cOperator == pcode__DIV){ if (R_single_ == 0){ runtimeError("division by zero", 11); return; } double_ = L_single_ / R_single_; }
    else if (cOperator == pcode__MOD){ if (R_double_ == 0){ runtimeError("MOD by zero", 11); return; } double_ = (t_long) L_single_ % (t_long) R_single_; }
    else if (cOperator == pcode__IDIV){ if (R_single_ == 0){ runtimeError("integer division by zero", 11); return; } double_ = (t_long) (L_single_ / R_single_); }
    else if (cOperator == pcode__EQUAL) 				double_ = L_single_ == R_single_;
    else if (cOperator == pcode__EQV) 				double_ = L_single_ == R_single_;
    else if (cOperator == pcode__UNEQUAL) 			double_ = L_single_ != R_single_;
    else if (cOperator == pcode__GREATER) 			double_ = L_single_ > R_single_;
    else if (cOperator == pcode__LESSER) 				double_ = L_single_ < R_single_;
    else if (cOperator == pcode__GREATER_EQUAL) double_ = L_single_ >= R_single_;
    else if (cOperator == pcode__LESSER_EQUAL) 	double_ = L_single_ <= R_single_;
    else { runtimeError("unknown operator"); return; }

		if (remove == false) myStack->restoreStack();
    myStack->pushDouble(double_); 
#ifdef HAS_CONSOLE
    if (!bSilent) sprintf(acStringOutputBuffer, "%.6f %s %.6f --> %.6f", L_single_, c, R_single_, double_);
#endif

  } else if (RType == pcode__DOUBLE){
         if (cOperator == pcode__MUL) double_ = L_single_ * R_double_;
    else if (cOperator == pcode__AND) double_ = (t_long) L_single_ & (t_long) R_double_;
    else if (cOperator == pcode__OR)  double_ = (t_long) L_single_ | (t_long) R_double_;
    else if (cOperator == pcode__XOR) double_ = (t_long) L_single_ ^ (t_long) R_double_;
    else if (cOperator == pcode__IMP) double_ = !(L_single_ != 0 && R_double_ == 0);
    else if (cOperator == pcode__POWER) double_ = pow((t_double) L_single_, R_double_);
    else if (cOperator == pcode__ADD) double_ = L_single_ + R_double_;
    else if (cOperator == pcode__SUB) double_ = L_single_ - R_double_;
    //else if (cOperator == pcode__DIV){ if (R_single_ == 0){ runtimeError("division by zero", 11); return; } double_ = L_single_ / R_double_; }
    else if (cOperator == pcode__MOD){ if (R_double_ == 0){ runtimeError("MOD by zero", 11); return; } double_ = (t_long) L_single_ % (t_long) R_double_; }
    else if (cOperator == pcode__IDIV){ if (R_single_ == 0){ runtimeError("integer division by zero", 11); return; } double_ = (t_long) (L_single_ / R_double_); }
    else if (cOperator == pcode__EQUAL) 				double_ = L_single_ == R_double_;
    else if (cOperator == pcode__EQV) 				double_ = L_single_ == R_double_;
    else if (cOperator == pcode__UNEQUAL) 			double_ = L_single_ != R_double_;
    else if (cOperator == pcode__GREATER) 			double_ = L_single_ > R_double_;
    else if (cOperator == pcode__LESSER) 				double_ = L_single_ < R_double_;
    else if (cOperator == pcode__GREATER_EQUAL) double_ = L_single_ >= R_double_;
    else if (cOperator == pcode__LESSER_EQUAL) 	double_ = L_single_ <= R_double_;
    else { runtimeError("unknown operator"); return; }

		if (remove == false) myStack->restoreStack();
    myStack->pushDouble(double_); 
#ifdef HAS_CONSOLE
    if (!bSilent) sprintf(acStringOutputBuffer, "%.6f %s %.6f --> %.6f", L_single_, c, R_double_, double_);
#endif
  
  } else if (RType == pcode__CURRENCY){

    t_currency t(L_single_);

         if (cOperator == pcode__MUL) currency_.setValue(t.bc() * R_currency_.bc(), t.bc() * R_currency_.ad());
    else if (cOperator == pcode__AND) currency_.setValue(t.bc() & R_currency_.bc(), t.ad() & R_currency_.ad());
    else if (cOperator == pcode__OR)  currency_.setValue(t.bc() | R_currency_.bc(), t.ad() | R_currency_.ad());
    else if (cOperator == pcode__XOR) currency_.setValue(t.bc() ^ R_currency_.bc(), t.ad() ^ R_currency_.ad());
    else if (cOperator == pcode__IMP) currency_.setValue(!(t.getValue() != 0 && R_currency_.getValue() == 0), 0);
    else if (cOperator == pcode__POWER) currency_.setValue((t_long) pow((t_double) t.bc(), (t_double) R_currency_.toDouble()), 0);
    else if (cOperator == pcode__ADD) currency_.setValue(t.bc() + R_currency_.bc(), t.ad() + R_currency_.ad());
    else if (cOperator == pcode__SUB) currency_.setValue(t.bc() - R_currency_.bc(), t.ad() - R_currency_.ad());
    //else if (cOperator == pcode__DIV){ if (R_currency_.getValue() == 0){ runtimeError("division by zero", 11); return; } currency_.setValue(t.bc() / R_currency_.bc(), t.ad() / R_currency_.ad()); }
    else if (cOperator == pcode__MOD){ if (R_currency_.getValue() == 0){ runtimeError("MOD by zero", 11); return; } currency_.setValue(t.bc() % R_currency_.bc(), t.ad() % R_currency_.ad()); }
    else if (cOperator == pcode__IDIV){ if (R_currency_.getValue() == 0){ runtimeError("integer division by zero", 11); return; } currency_.setValue(t.bc() / R_currency_.bc(), t.ad() / R_currency_.ad()); }
    else if (cOperator == pcode__EQUAL) 				currency_.setValue(t.getValue() == R_currency_.getValue(), 0);
    else if (cOperator == pcode__EQV) 				currency_.setValue(t.getValue() == R_currency_.getValue(), 0);
    else if (cOperator == pcode__UNEQUAL) 			currency_.setValue(t.getValue() != R_currency_.getValue(), 0);
    else if (cOperator == pcode__GREATER) 			currency_.setValue(t.getValue() > R_currency_.getValue(), 0);
    else if (cOperator == pcode__LESSER) 				currency_.setValue(t.getValue() < R_currency_.getValue(), 0);
    else if (cOperator == pcode__GREATER_EQUAL) currency_.setValue(t.getValue() >= R_currency_.getValue(), 0);
    else if (cOperator == pcode__LESSER_EQUAL) currency_.setValue(t.getValue() <= R_currency_.getValue(), 0);
    else { runtimeError("unknown operator"); return; }

		if (remove == false) myStack->restoreStack();
 	  myStack->pushCurrency(currency_); 
#ifdef HAS_CONSOLE
    if (!bSilent) sprintf(acStringOutputBuffer, "%.6f %s %s --> %s", L_single_, c, R_currency_.toCString(), currency_.toCString2());
#endif

  }
  // pcode__DOUBLE ***
  } else if (LType == pcode__DOUBLE){
  if (RType == pcode__BOOLEAN){
         if (cOperator == pcode__MUL) double_ = L_double_ * R_boolean_;
    else if (cOperator == pcode__AND) double_ = (t_long) L_double_ & R_boolean_;
    else if (cOperator == pcode__OR)  double_ = (t_long) L_double_ | R_boolean_;
    else if (cOperator == pcode__XOR) double_ = (t_long) L_double_ ^ R_boolean_;
    else if (cOperator == pcode__IMP) double_ = !(L_double_ != 0 && R_boolean_ == 0);
    else if (cOperator == pcode__POWER) double_ = pow(L_double_, (t_double) R_boolean_);
    else if (cOperator == pcode__ADD) double_ = L_double_ + R_boolean_;
    else if (cOperator == pcode__SUB) double_ = L_double_ - R_boolean_;
    //else if (cOperator == pcode__DIV){ if (R_boolean_ == 0){ runtimeError("division by zero", 11); return; } double_ = L_double_ / R_boolean_; }
    else if (cOperator == pcode__MOD){ if (R_boolean_ == 0){ runtimeError("MOD by zero", 11); return; } double_ = (t_long) L_double_ % R_boolean_; }
    else if (cOperator == pcode__IDIV){ if (R_boolean_ == 0){ runtimeError("integer division by zero", 11); return; } double_ = (t_long) (L_double_ / R_boolean_); }
    else if (cOperator == pcode__EQUAL) 				double_ = L_double_ == R_boolean_;
    else if (cOperator == pcode__EQV) 				double_ = L_double_ == R_boolean_;
    else if (cOperator == pcode__UNEQUAL) 			double_ = L_double_ != R_boolean_;
    else if (cOperator == pcode__GREATER) 			double_ = L_double_ > R_boolean_;
    else if (cOperator == pcode__LESSER) 				double_ = L_double_ < R_boolean_;
    else if (cOperator == pcode__GREATER_EQUAL) double_ = L_double_ >= R_boolean_;
    else if (cOperator == pcode__LESSER_EQUAL) 	double_ = L_double_ <= R_boolean_;
    else { runtimeError("unknown operator"); return; }

		if (remove == false) myStack->restoreStack();
    myStack->pushDouble(double_); 
#ifdef HAS_CONSOLE
    if (!bSilent) sprintf(acStringOutputBuffer, "%.6f %s %d --> %.6f", L_double_, c, (t_integer) R_boolean_, double_);
#endif

  } else if (RType == pcode__QSTRING){

     if (cOperator == pcode__ADD){
			 int nId = estatics->declare(pcode__QSTRING, 0, false, false);
    	 estatics->setQString_Double(nId, L_double_, R_qstring_, 0);
			 myStack->pushEQString(nId);
#ifdef HAS_CONSOLE
			 if (!bSilent) sprintf(acStringOutputBuffer, "Unicode");
//			 if (!bSilent) sprintf(acStringOutputBuffer, "%.6f %s \"%-30.30s\" --> \"%-30.30s\"", L_double_, c, R_string_, estatics->getString(nId));
#endif
     } else { runtimeError("unknown operator"); return; }

  } else if (RType == pcode__CSTRING){

     if (cOperator == pcode__ADD){
			 int nId = estatics->declare(pcode__CSTRING, 0, false, false);
    	 estatics->setCString_Double(nId, L_double_, R_cstring_, 0);
			 myStack->pushECString(nId);
#ifdef HAS_CONSOLE
			 if (!bSilent) sprintf(acStringOutputBuffer, "%.6f %s \"%-30.30s\" --> \"%-30.30s\"", L_double_, c, R_cstring_, estatics->getCString(nId));
#endif
     } else { runtimeError("unknown operator"); return; }

  } else if (RType == pcode__BYTE){
         if (cOperator == pcode__MUL) double_ = L_double_ * R_byte_;
    else if (cOperator == pcode__AND) double_ = (t_long) L_double_ & R_byte_;
    else if (cOperator == pcode__OR)  double_ = (t_long) L_double_ | R_byte_;
    else if (cOperator == pcode__XOR) double_ = (t_long) L_double_ ^ R_byte_;
    else if (cOperator == pcode__IMP) double_ = !(L_double_ != 0 && R_byte_ == 0);
    else if (cOperator == pcode__POWER) double_ = pow(L_double_, (t_double) R_byte_);
    else if (cOperator == pcode__ADD) double_ = L_double_ + R_byte_;
    else if (cOperator == pcode__SUB) double_ = L_double_ - R_byte_;
    //else if (cOperator == pcode__DIV){ if (R_byte_ == 0){ runtimeError("division by zero", 11); return; } double_ = L_double_ / R_byte_; }
    else if (cOperator == pcode__MOD){ if (R_byte_ == 0){ runtimeError("MOD by zero", 11); return; } double_ = (t_long) L_double_ % R_byte_; }
    else if (cOperator == pcode__IDIV){ if (R_byte_ == 0){ runtimeError("integer division by zero", 11); return; } double_ = (t_long) (L_double_ / R_byte_); }
    else if (cOperator == pcode__EQUAL) 				double_ = L_double_ == R_byte_;
    else if (cOperator == pcode__EQV) 				double_ = L_double_ == R_byte_;
    else if (cOperator == pcode__UNEQUAL) 			double_ = L_double_ != R_byte_;
    else if (cOperator == pcode__GREATER) 			double_ = L_double_ > R_byte_;
    else if (cOperator == pcode__LESSER) 				double_ = L_double_ < R_byte_;
    else if (cOperator == pcode__GREATER_EQUAL) double_ = L_double_ >= R_byte_;
    else if (cOperator == pcode__LESSER_EQUAL) 	double_ = L_double_ <= R_byte_;
    else { runtimeError("unknown operator"); return; }

		if (remove == false) myStack->restoreStack();
    myStack->pushDouble(double_); 
#ifdef HAS_CONSOLE
    if (!bSilent) sprintf(acStringOutputBuffer, "%.6f %s %d --> %.6f", L_double_, c, (t_integer) R_byte_, double_);
#endif

  } else if (RType == pcode__SHORT){
         if (cOperator == pcode__MUL) double_ = L_double_ * R_short_;
    else if (cOperator == pcode__AND) double_ = (t_long) L_double_ & R_short_;
    else if (cOperator == pcode__OR)  double_ = (t_long) L_double_ | R_short_;
    else if (cOperator == pcode__XOR) double_ = (t_long) L_double_ ^ R_short_;
    else if (cOperator == pcode__IMP) double_ = !(L_double_ != 0 && R_short_ == 0);
    else if (cOperator == pcode__POWER) double_ = pow(L_double_, (t_double) R_short_);
    else if (cOperator == pcode__ADD) double_ = L_double_ + R_short_;
    else if (cOperator == pcode__SUB) double_ = L_double_ - R_short_;
    //else if (cOperator == pcode__DIV){ if (R_short_ == 0){ runtimeError("division by zero", 11); return; } double_ = L_double_ / R_short_; }
    else if (cOperator == pcode__MOD){ if (R_short_ == 0){ runtimeError("MOD by zero", 11); return; } double_ = (t_long) L_double_ % R_short_; }
    else if (cOperator == pcode__IDIV){ if (R_short_ == 0){ runtimeError("integer division by zero", 11); return; } double_ = (t_long) (L_double_ / R_short_); }
    else if (cOperator == pcode__EQUAL) 				double_ = L_double_ == R_short_;
    else if (cOperator == pcode__EQV) 				double_ = L_double_ == R_short_;
    else if (cOperator == pcode__UNEQUAL) 			double_ = L_double_ != R_short_;
    else if (cOperator == pcode__GREATER) 			double_ = L_double_ > R_short_;
    else if (cOperator == pcode__LESSER) 				double_ = L_double_ < R_short_;
    else if (cOperator == pcode__GREATER_EQUAL) double_ = L_double_ >= R_short_;
    else if (cOperator == pcode__LESSER_EQUAL) 	double_ = L_double_ <= R_short_;
    else { runtimeError("unknown operator"); return; }

		if (remove == false) myStack->restoreStack();
    myStack->pushDouble(double_); 
#ifdef HAS_CONSOLE
    if (!bSilent) sprintf(acStringOutputBuffer, "%.6f %s %d --> %.6f", L_double_, c, (t_integer) R_short_, double_);
#endif

  } else if (RType == pcode__INTEGER){
         if (cOperator == pcode__MUL) double_ = L_double_ * R_integer_;
    else if (cOperator == pcode__AND) double_ = (t_long) L_double_ & R_integer_;
    else if (cOperator == pcode__OR)  double_ = (t_long) L_double_ | R_integer_;
    else if (cOperator == pcode__XOR) double_ = (t_long) L_double_ ^ R_integer_;
    else if (cOperator == pcode__IMP) double_ = !(L_double_ != 0 && R_integer_ == 0);
    else if (cOperator == pcode__POWER) double_ = pow(L_double_, (t_double) R_integer_);
    else if (cOperator == pcode__ADD) double_ = L_double_ + R_integer_;
    else if (cOperator == pcode__SUB) double_ = L_double_ - R_integer_;
    //else if (cOperator == pcode__DIV){ if (R_integer_ == 0){ runtimeError("division by zero", 11); return; } double_ = L_double_ / R_integer_; }
    else if (cOperator == pcode__MOD){ if (R_integer_ == 0){ runtimeError("MOD by zero", 11); return; } double_ = (t_long) L_double_ % R_integer_; }
    else if (cOperator == pcode__IDIV){ if (R_integer_ == 0){ runtimeError("integer division by zero", 11); return; } double_ = (t_long) (L_double_ / R_integer_); }
    else if (cOperator == pcode__EQUAL) 				double_ = L_double_ == R_integer_;
    else if (cOperator == pcode__EQV) 				double_ = L_double_ == R_integer_;
    else if (cOperator == pcode__UNEQUAL) 			double_ = L_double_ != R_integer_;
    else if (cOperator == pcode__GREATER) 			double_ = L_double_ > R_integer_;
    else if (cOperator == pcode__LESSER) 				double_ = L_double_ < R_integer_;
    else if (cOperator == pcode__GREATER_EQUAL) double_ = L_double_ >= R_integer_;
    else if (cOperator == pcode__LESSER_EQUAL) 	double_ = L_double_ <= R_integer_;
    else { runtimeError("unknown operator"); return; }

		if (remove == false) myStack->restoreStack();
    myStack->pushDouble(double_); 
#ifdef HAS_CONSOLE
    if (!bSilent) sprintf(acStringOutputBuffer, "%.6f %s %d --> %.6f", L_double_, c, R_integer_, double_);
#endif

  } else if (RType ==  pcode__LONG){
         if (cOperator == pcode__MUL) double_ = L_double_ * R_long_;
    else if (cOperator == pcode__AND) double_ = (t_long) L_double_ & R_long_;
    else if (cOperator == pcode__OR)  double_ = (t_long) L_double_ | R_long_;
    else if (cOperator == pcode__XOR) double_ = (t_long) L_double_ ^ R_long_;
    else if (cOperator == pcode__IMP) double_ = !(L_double_ != 0 && R_long_ == 0);
    else if (cOperator == pcode__POWER) double_ = pow(L_double_, (t_double) R_long_);
    else if (cOperator == pcode__ADD) double_ = L_double_ + R_long_;
    else if (cOperator == pcode__SUB) double_ = L_double_ - R_long_;
    //else if (cOperator == pcode__DIV){ if (R_long_ == 0){ runtimeError("division by zero", 11); return; } double_ = L_double_ / R_long_; }
    else if (cOperator == pcode__MOD){ if (R_long_ == 0){ runtimeError("MOD by zero", 11); return; } double_ = (t_long) L_double_ % R_long_; }
    else if (cOperator == pcode__IDIV){ if (R_long_ == 0){ runtimeError("integer division by zero", 11); return; } double_ = (t_long) (L_double_ / R_long_); }
    else if (cOperator == pcode__EQUAL) 				double_ = L_double_ == R_long_;
    else if (cOperator == pcode__EQV) 				double_ = L_double_ == R_long_;
    else if (cOperator == pcode__UNEQUAL) 			double_ = L_double_ != R_long_;
    else if (cOperator == pcode__GREATER) 			double_ = L_double_ > R_long_;
    else if (cOperator == pcode__LESSER) 				double_ = L_double_ < R_long_;
    else if (cOperator == pcode__GREATER_EQUAL) double_ = L_double_ >= R_long_;
    else if (cOperator == pcode__LESSER_EQUAL) 	double_ = L_double_ <= R_long_;
    else { runtimeError("unknown operator"); return; }

		if (remove == false) myStack->restoreStack();
    myStack->pushDouble(double_); 
#ifdef HAS_CONSOLE
    if (!bSilent) sprintf(acStringOutputBuffer, "%.6f %s %I64d --> %.6f", L_double_, c, R_long_, double_);
#endif

  } else if (RType == pcode__SINGLE){
         if (cOperator == pcode__MUL) double_ = L_double_ * R_single_;
    else if (cOperator == pcode__AND) double_ = (t_long) L_double_ & (t_long) R_single_;
    else if (cOperator == pcode__OR)  double_ = (t_long) L_double_ | (t_long) R_single_;
    else if (cOperator == pcode__XOR) double_ = (t_long) L_double_ ^ (t_long) R_single_;
    else if (cOperator == pcode__IMP) double_ = !(L_double_ != 0 && R_single_ == 0);
    else if (cOperator == pcode__POWER) double_ = pow(L_double_, (t_double) R_single_);
    else if (cOperator == pcode__ADD) double_ = L_double_ + R_single_;
    else if (cOperator == pcode__SUB) double_ = L_double_ - R_single_;
    //else if (cOperator == pcode__DIV){ if (R_single_ == 0){ runtimeError("division by zero", 11); return; } double_ = L_double_ / R_single_; }
    else if (cOperator == pcode__MOD){ if (R_double_ == 0){ runtimeError("MOD by zero", 11); return; } double_ = (t_long) L_double_ % (t_long) R_single_; }
    else if (cOperator == pcode__IDIV){ if (R_single_ == 0){ runtimeError("integer division by zero", 11); return; } double_ = (t_long) (L_double_ / R_single_); }
    else if (cOperator == pcode__EQUAL) 				double_ = L_double_ == R_single_;
    else if (cOperator == pcode__EQV) 				double_ = L_double_ == R_single_;
    else if (cOperator == pcode__UNEQUAL) 			double_ = L_double_ != R_single_;
    else if (cOperator == pcode__GREATER) 			double_ = L_double_ > R_single_;
    else if (cOperator == pcode__LESSER) 				double_ = L_double_ < R_single_;
    else if (cOperator == pcode__GREATER_EQUAL) double_ = L_double_ >= R_single_;
    else if (cOperator == pcode__LESSER_EQUAL) 	double_ = L_double_ <= R_single_;
    else { runtimeError("unknown operator"); return; }

		if (remove == false) myStack->restoreStack();
    myStack->pushDouble(double_); 
#ifdef HAS_CONSOLE
    if (!bSilent) sprintf(acStringOutputBuffer, "%.6f %s %.6f --> %.6f", L_double_, c, R_single_, double_);
#endif

  } else if (RType == pcode__DOUBLE){
         if (cOperator == pcode__MUL) double_ = L_double_ * R_double_;
    else if (cOperator == pcode__AND) double_ = (t_long) L_double_ & (t_long) R_double_;
    else if (cOperator == pcode__OR)  double_ = (t_long) L_double_ | (t_long) R_double_;
    else if (cOperator == pcode__XOR) double_ = (t_long) L_double_ ^ (t_long) R_double_;
    else if (cOperator == pcode__IMP) double_ = !(L_double_ != 0 && R_double_ == 0);
    else if (cOperator == pcode__POWER) double_ = pow(L_double_, R_double_);
    else if (cOperator == pcode__ADD) double_ = L_double_ + R_double_;
    else if (cOperator == pcode__SUB) double_ = L_double_ - R_double_;
    //else if (cOperator == pcode__DIV){ if (R_double_ == 0){ runtimeError("division by zero", 11); return; } double_ = L_double_ / R_double_; }
    else if (cOperator == pcode__MOD){ if (R_double_ == 0){ runtimeError("MOD by zero", 11); return; } double_ = (t_long) L_double_ % (t_long) R_double_; }
    else if (cOperator == pcode__IDIV){ if (R_double_ == 0){ runtimeError("integer division by zero", 11); return; } double_ = (t_long) (L_double_ / R_double_); }
    else if (cOperator == pcode__EQUAL) 				double_ = L_double_ == R_double_;
    else if (cOperator == pcode__EQV) 				double_ = L_double_ == R_double_;
    else if (cOperator == pcode__UNEQUAL) 			double_ = L_double_ != R_double_;
    else if (cOperator == pcode__GREATER) 			double_ = L_double_ > R_double_;
    else if (cOperator == pcode__LESSER) 				double_ = L_double_ < R_double_;
    else if (cOperator == pcode__GREATER_EQUAL) double_ = L_double_ >= R_double_;
    else if (cOperator == pcode__LESSER_EQUAL) 	double_ = L_double_ <= R_double_;
    else { runtimeError("unknown operator"); return; }

		if (remove == false) myStack->restoreStack();
    myStack->pushDouble(double_); 
#ifdef HAS_CONSOLE
    if (!bSilent) sprintf(acStringOutputBuffer, "%.6f %s %.6f --> %.6f", L_double_, c, R_double_, double_);
#endif

  } else if (RType == pcode__CURRENCY){

    t_currency t(L_double_);

         if (cOperator == pcode__MUL) currency_.setValue(t.bc() * R_currency_.bc(), t.bc() * R_currency_.ad());
    else if (cOperator == pcode__AND) currency_.setValue(t.bc() & R_currency_.bc(), t.ad() & R_currency_.ad());
    else if (cOperator == pcode__OR)  currency_.setValue(t.bc() | R_currency_.bc(), t.ad() | R_currency_.ad());
    else if (cOperator == pcode__XOR) currency_.setValue(t.bc() ^ R_currency_.bc(), t.ad() ^ R_currency_.ad());
    else if (cOperator == pcode__IMP) currency_.setValue(!(t.getValue() != 0 && R_currency_.getValue() == 0), 0);
    else if (cOperator == pcode__POWER) currency_.setValue((t_long) pow((t_double) t.bc(), (t_double) R_currency_.toDouble()), 0);
    else if (cOperator == pcode__ADD) currency_.setValue(t.bc() + R_currency_.bc(), t.ad() + R_currency_.ad());
    else if (cOperator == pcode__SUB) currency_.setValue(t.bc() - R_currency_.bc(), t.ad() - R_currency_.ad());
    //else if (cOperator == pcode__DIV){ if (R_currency_.getValue() == 0){ runtimeError("division by zero", 11); return; } currency_.setValue(t.bc() / R_currency_.bc(), t.ad() / R_currency_.ad()); }
    else if (cOperator == pcode__MOD){ if (R_currency_.getValue() == 0){ runtimeError("MOD by zero", 11); return; } currency_.setValue(t.bc() % R_currency_.bc(), t.ad() % R_currency_.ad()); }
    else if (cOperator == pcode__IDIV){ if (R_currency_.getValue() == 0){ runtimeError("integer division by zero", 11); return; } currency_.setValue(t.bc() / R_currency_.bc(), t.ad() / R_currency_.ad()); }
    else if (cOperator == pcode__EQUAL) 				currency_.setValue(t.getValue() == R_currency_.getValue(), 0);
    else if (cOperator == pcode__EQV) 				currency_.setValue(t.getValue() == R_currency_.getValue(), 0);
    else if (cOperator == pcode__UNEQUAL) 			currency_.setValue(t.getValue() != R_currency_.getValue(), 0);
    else if (cOperator == pcode__GREATER) 			currency_.setValue(t.getValue() > R_currency_.getValue(), 0);
    else if (cOperator == pcode__LESSER) 				currency_.setValue(t.getValue() < R_currency_.getValue(), 0);
    else if (cOperator == pcode__GREATER_EQUAL) currency_.setValue(t.getValue() >= R_currency_.getValue(), 0);
    else if (cOperator == pcode__LESSER_EQUAL) currency_.setValue(t.getValue() <= R_currency_.getValue(), 0);
    else { runtimeError("unknown operator"); return; }

		if (remove == false) myStack->restoreStack();
 	  myStack->pushCurrency(currency_); 
#ifdef HAS_CONSOLE
    if (!bSilent) sprintf(acStringOutputBuffer, "%.6f %s %s --> %s", L_double_, c, R_currency_.toCString(), currency_.toCString2());
#endif

  }

  } else if ((LType == pcode__OBJECT || memory_type::isBinding(LType) || memory_type::isClass(LType)) 
    && (RType == pcode__OBJECT || memory_type::isBinding(RType) || memory_type::isClass(RType))){

      {

             if (cOperator == pcode__EQUAL) 				boolean_ = L_object_ == R_object_;
        else if (cOperator == pcode__UNEQUAL) 			boolean_ = L_object_ != R_object_;
        else { runtimeError("unknown operator"); return; }
      }

		if (remove == false) myStack->restoreStack();
    myStack->pushBoolean(boolean_); 
#ifdef HAS_CONSOLE
    if (!bSilent) sprintf(acStringOutputBuffer, "&H%X %s &H%X --> %s", L_object_, c, R_object_, boolean_ ? "TRUE" : "FALSE");  
#endif  

	// pcode__CURRENCY ***
  } else if (LType == pcode__CURRENCY){
  if (RType == pcode__BOOLEAN){
    R_currency_ = t_currency(R_boolean_, 0);
    goto cur;

  } else if (RType == pcode__QSTRING){

     if (cOperator == pcode__ADD){
			 int nId = estatics->declare(pcode__QSTRING, 0, false, false);
    	 estatics->setQString_Currency(nId, L_currency_, R_qstring_, 0);
			 myStack->pushEQString(nId);
#ifdef HAS_CONSOLE
			 if (!bSilent) sprintf(acStringOutputBuffer, "Unicode");
//			 if (!bSilent) sprintf(acStringOutputBuffer, "%s %s \"%-30.30s\" --> \"%-30.30s\"", L_currency_.toString(), c, R_string_, estatics->getString(nId));
#endif

     } else { runtimeError("unknown operator"); return; }

  } else if (RType == pcode__CSTRING){

     if (cOperator == pcode__ADD){
			 int nId = estatics->declare(pcode__CSTRING, 0, false, false);
    	 estatics->setCString_Currency(nId, L_currency_, R_cstring_, 0);
			 myStack->pushECString(nId);
#ifdef HAS_CONSOLE
			 if (!bSilent) sprintf(acStringOutputBuffer, "%s %s \"%-30.30s\" --> \"%-30.30s\"", L_currency_.toCString(), c, R_cstring_, estatics->getCString(nId));
#endif

     } else { runtimeError("unknown operator"); return; }

  } else if (RType == pcode__BYTE){
    R_currency_ = t_currency(R_byte_, 0);
    goto cur;

  } else if (RType == pcode__SHORT){
    R_currency_ = t_currency(R_short_, 0);
    goto cur;

  } else if (RType == pcode__INTEGER){
    R_currency_ = t_currency(R_integer_, 0);
    goto cur;

  } else if (RType ==  pcode__LONG){
    R_currency_ = t_currency(R_long_, 0);
    goto cur;

  } else if (RType == pcode__SINGLE){
    R_currency_ = t_currency(R_single_);
    goto cur;

  } else if (RType == pcode__DOUBLE){
    R_currency_ = t_currency(R_double_);
    goto cur;

  } else if (RType == pcode__CURRENCY){
cur:
    t_currency t = L_currency_;

         if (cOperator == pcode__MUL) currency_.setValue(t.bc() * R_currency_.bc(), t.bc() * R_currency_.ad());
    else if (cOperator == pcode__AND) currency_.setValue(t.bc() & R_currency_.bc(), t.ad() & R_currency_.ad());
    else if (cOperator == pcode__OR)  currency_.setValue(t.bc() | R_currency_.bc(), t.ad() | R_currency_.ad());
    else if (cOperator == pcode__XOR) currency_.setValue(t.bc() ^ R_currency_.bc(), t.ad() ^ R_currency_.ad());
    else if (cOperator == pcode__IMP) currency_.setValue(!(t.getValue() != 0 && R_currency_.getValue() == 0), 0);
    else if (cOperator == pcode__POWER) currency_.setValue((t_long) pow((t_double) t.bc(), (t_double) R_currency_.toDouble()), 0);
    else if (cOperator == pcode__ADD) currency_.setValue(t.bc() + R_currency_.bc(), t.ad() + R_currency_.ad());
    else if (cOperator == pcode__SUB) currency_.setValue(t.bc() - R_currency_.bc(), t.ad() - R_currency_.ad());
    //else if (cOperator == pcode__DIV){ if (R_currency_.getValue() == 0){ runtimeError("division by zero", 11); return; } currency_.setValue(t.bc() / R_currency_.bc(), t.ad() / R_currency_.ad()); }
    else if (cOperator == pcode__MOD){ if (R_currency_.getValue() == 0){ runtimeError("MOD by zero", 11); return; } currency_.setValue(t.bc() % R_currency_.bc(), t.ad() % R_currency_.ad()); }
    else if (cOperator == pcode__IDIV){ if (R_currency_.getValue() == 0){ runtimeError("integer division by zero", 11); return; } currency_.setValue(t.bc() / R_currency_.bc(), t.ad() / R_currency_.ad()); }
    else if (cOperator == pcode__EQUAL) 				currency_.setValue(t.getValue() == R_currency_.getValue(), 0);
    else if (cOperator == pcode__EQV) 				currency_.setValue(t.getValue() == R_currency_.getValue(), 0);
    else if (cOperator == pcode__UNEQUAL) 			currency_.setValue(t.getValue() != R_currency_.getValue(), 0);
    else if (cOperator == pcode__GREATER) 			currency_.setValue(t.getValue() > R_currency_.getValue(), 0);
    else if (cOperator == pcode__LESSER) 				currency_.setValue(t.getValue() < R_currency_.getValue(), 0);
    else if (cOperator == pcode__GREATER_EQUAL) currency_.setValue(t.getValue() >= R_currency_.getValue(), 0);
    else if (cOperator == pcode__LESSER_EQUAL) currency_.setValue(t.getValue() <= R_currency_.getValue(), 0);
    else { runtimeError("unknown operator"); return; }

		if (remove == false) myStack->restoreStack();
 	  myStack->pushCurrency(currency_); 
#ifdef HAS_CONSOLE
    if (!bSilent) sprintf(acStringOutputBuffer, "%d %s %s --> %s", (t_integer) t.bc(), c, R_currency_.toCString(), currency_.toCString2());
#endif
  }

  // pcode__DATE ***
  } else if (LType == pcode__DATE){
      { runtimeError("DATE with ordinary operator not allowed"); return; }  



	// *
	// * process unary operators
	// *
  } else if (LType == 0){
    if (RType == pcode__BOOLEAN){
      if (cOperator == pcode__NOT) boolean_ = (R_boolean_ == 0);
      else { runtimeError("unknown operator"); return; }

		  if (remove == false) myStack->restoreStack();
 	    myStack->pushBoolean(boolean_); 
#ifdef HAS_CONSOLE
      if (!bSilent) sprintf(acStringOutputBuffer, "%s %d --> %d", c, (t_integer) R_boolean_, (t_integer) boolean_);
#endif

    } else if (RType == pcode__BYTE){
      if (cOperator == pcode__NOT) integer_ = (R_byte_ == 0);
      else { runtimeError("unknown operator"); return; }

		  if (remove == false) myStack->restoreStack();
 	    myStack->pushInteger(integer_); 
#ifdef HAS_CONSOLE
      if (!bSilent) sprintf(acStringOutputBuffer, "%s %d --> %d", c, (t_integer) R_byte_, integer_);
#endif

    } else if (RType == pcode__SHORT){
      if (cOperator == pcode__NOT) integer_ = (R_short_ == 0);
      else { runtimeError("unknown operator"); return; }

		  if (remove == false) myStack->restoreStack();
 	    myStack->pushInteger(integer_); 
#ifdef HAS_CONSOLE
      if (!bSilent) sprintf(acStringOutputBuffer, "%s %d --> %d", c, (t_integer) R_byte_, integer_);
#endif

    } else if (RType == pcode__INTEGER){
      if (cOperator == pcode__NOT) integer_ = (R_integer_ == 0);
      else { runtimeError("unknown operator"); return; }

		  if (remove == false) myStack->restoreStack();
 	    myStack->pushInteger(integer_); 
#ifdef HAS_CONSOLE
      if (!bSilent) sprintf(acStringOutputBuffer, "%s %d --> %d", c, R_integer_, integer_);
#endif

    } else if (RType ==  pcode__LONG){
      if (cOperator == pcode__NOT) long_ = (R_long_ == 0);
      else { runtimeError("unknown operator"); return; }

		  if (remove == false) myStack->restoreStack();
 	    myStack->pushLong(long_); 
#ifdef HAS_CONSOLE
      if (!bSilent) sprintf(acStringOutputBuffer, "%s %I64d --> %I64d", c, R_long_, long_);
#endif


    } else if (RType == pcode__SINGLE){
      if (cOperator == pcode__NOT) single_ = (R_single_ == 0);
      else { runtimeError("unknown operator"); return; }

		  if (remove == false) myStack->restoreStack();
 	    myStack->pushSingle(single_); 
#ifdef HAS_CONSOLE
      if (!bSilent) sprintf(acStringOutputBuffer, "%s %.6f --> %.6f", c, R_single_, single_);
#endif

    } else if (RType == pcode__DOUBLE){
      if (cOperator == pcode__NOT) double_ = (R_double_ == 0);
      else { runtimeError("unknown operator"); return; }

		  if (remove == false) myStack->restoreStack();
 	    myStack->pushDouble(double_); 
#ifdef HAS_CONSOLE
      if (!bSilent) sprintf(acStringOutputBuffer, "%s %.6f --> %.6f", c, R_double_, double_);
#endif

    } else {
      { internalError("error occured while OPERATION");  return;}
	  }

  } else {

    
    {

      if (memory_type::isString(RType) && memory_type::isNumeric(LType)){
        { runtimeError("you cannot assing a STRING value, if it is a NUMERIC variable"); return; }
      }

      {  internalError("error occured while OPERATION"); return; }
    }
	}

  }

raus:
  if (nRID)  estatics->undeclare(nRID);
  if (remove && nLID){
    estatics->undeclare(nLID);
  }
#ifdef HAS_CONSOLE
  if (!bSilent){
    CONSOLE pcodePrint(acStringOutputBuffer);
    CONSOLE pcodePrintCR();
  }
#endif
	return;
}
