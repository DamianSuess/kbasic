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

extern QMap<int,QString>forms;

int kbFormId;
int kbMenuBarId;
int kbToolBarId;

void interpreter::pushId(t_scope scope, int identifier, int offset, int _nVarType, bool bAssignment, memory_variable2 *v2, bool bBindingParent, bool bReturnVar)
{
  /*
  if (identifier == 103){
    identifier = identifier;
  }*/

  t_boolean boolean_;

  t_qstring qstring_;
  t_cstring cstring_;

  t_byte byte_;
	t_short short_;
 	t_integer integer_;
	t_long long_;

	t_double double_;
	t_single single_;
/*
  t_int16 int16_;
  t_int32 int32_;
  t_int64 int64_;
  t_uint16 uint16_;
  t_uint32 uint32_;
  t_uint64 uint64_;
*/
  t_variant variant_;

	t_pointer pointer_;
	t_object object_;

  memory_variable2 *mv;

	t_currency currency_;
	t_date date_;
	//t_date date_;

	int nVarType;
  nVarType = _nVarType; 

  bool bType;
  bType = false;

  //bool bStructure;
  //bStructure = false;

  bool bClass;
  bClass = false;

  bool bBinding;
  bBinding = false;

  if (memory_type::isBinding(nVarType)){
    bBinding = true;
  } else if (myType->exist(nVarType)){
    bType = true;
  } else if (myClass->exist(nVarType)){
    bClass = true;
  }

  int n;
  n = movType_offset;

  movType_offset = 0;

  memory_variable2 *v;
  v = v2;

  if (v == 0){
    v = getVar(scope);
  }

  static char ac[2048];


	switch(nVarType){

		case pcode__BOOLEAN: 
			boolean_ = v->getBoolean(identifier, offset);
		  myStack->pushBoolean(boolean_);
			break;

		case pcode__QSTRING:
      if (bPushPointerPointer){
        bPushPointerPointer = false;
        qstring_ = (t_qstring)(v->getPointerPointer(identifier, offset));
        myStack->pushInteger((t_integer) qstring_);
      } else {
        qstring_ = v->getQString(identifier, offset);
        if (bReturnVar || scope == param || scope == local){
				  int nId = estatics->declare(pcode__QSTRING, 0, false, false);
    		  estatics->setQString(nId, qstring_, 0);
		  	  myStack->pushEQString(nId);

        } else {
          myStack->pushQString(qstring_);
        }
      }      
			break;

		case pcode__CSTRING:
      if (bPushPointerPointer){
        bPushPointerPointer = false;
        cstring_ = (t_cstring)(v->getPointerPointer(identifier, offset));
        myStack->pushInteger((t_integer) cstring_);
      } else {
        cstring_ = v->getCString(identifier, offset);
        if (bReturnVar || scope == param || scope == local){
				  int nId = estatics->declare(pcode__CSTRING, 0, false, false);
    		  estatics->setCString(nId, cstring_, 0, 0);
		  		myStack->pushECString(nId);
        } else {
          myStack->pushCString(cstring_);
        }
      }      
			break;

    case pcode__LQSTRING:
      if (bPushPointerPointer){
        bPushPointerPointer = false;
        qstring_ = (t_qstring)(v->getPointerPointer(identifier, offset));
        myStack->pushInteger((t_integer) qstring_);
      } else {
        qstring_ = v->getLQString(identifier, offset);

        if (scope == param || scope == local){
				  int nId = estatics->declare(pcode__QSTRING, 0, false, false);
    		  estatics->setQString(nId, qstring_, 0);
		  		myStack->pushEQString(nId);
        } else {
          myStack->pushQString(qstring_);
        }
        
      }			
			break;

    case pcode__LCSTRING:
      if (bPushPointerPointer){
        bPushPointerPointer = false;
        cstring_ = (t_cstring)(v->getPointerPointer(identifier, offset));
        myStack->pushInteger((t_integer) cstring_);
      } else {
        cstring_ = v->getLCString(identifier, offset);

        if (scope == param || scope == local){
				  int nId = estatics->declare(pcode__CSTRING, 0, false, false);
    		  estatics->setCString(nId, cstring_, 0, 0);
		  		myStack->pushECString(nId);
        } else {
          myStack->pushCString(cstring_);
        }
        
      }			
			break;
		case pcode__BYTE:
			byte_ = v->getByte(identifier, offset);
		  myStack->pushByte(byte_);
			break;
		case pcode__SHORT:
			short_ = v->getShort(identifier, offset);
		  myStack->pushShort(short_);
			break;
		case pcode__INTEGER:
			integer_ = v->getInteger(identifier, offset);
		  myStack->pushInteger(integer_);
			break;
		case pcode__LONG: 
			long_ = v->getLong(identifier, offset);
		  myStack->pushLong(long_);
			break;

		case pcode__SINGLE: 
			single_ = v->getSingle(identifier, offset);
		  myStack->pushSingle(single_);
			break;
		case pcode__DOUBLE: 
			double_ = v->getDouble(identifier, offset);
		  myStack->pushDouble(double_);
			break;
/*
		case pcode__INT16: 
			int16_ = v->getInt16(identifier, offset);
		  myStack->pushInt16(int16_);
			break;
		case pcode__INT32: 
			int32_ = v->getInt32(identifier, offset);
		  myStack->pushInt32(int32_);
			break;
		case pcode__INT64: 
			int64_ = v->getInt64(identifier, offset);
		  myStack->pushInt64(int64_);
			break;
		case pcode__UINT16: 
			uint16_ = v->getUInt16(identifier, offset);
		  myStack->pushUInt16(uint16_);
			break;
		case pcode__UINT32: 
			uint32_ = v->getUInt32(identifier, offset);
		  myStack->pushUInt32(uint32_);
			break;
		case pcode__UINT64: 
			uint64_ = v->getUInt64(identifier, offset);
		  myStack->pushUInt64(uint64_);
			break;
*/

		case pcode__OBJECT: 
		  mv = (memory_variable2 *) v->getObject(identifier, offset);
      myStack->pushPointer(pcode__OBJECT, mv, false, true);
		  //myStack->pushObject(mv);
			break;

		case pcode__VARIANT: 
			nVarType = v->getVariantType(identifier);

	    switch(nVarType){

		    case pcode__BOOLEAN: 
			    boolean_ = v->getVariant_Boolean(identifier, offset);
		      myStack->pushBoolean(boolean_);
			    break;

		    case pcode__QSTRING:
          if (bPushPointerPointer){
            bPushPointerPointer = false;
            qstring_ = (t_qstring) v->getPointerPointer(identifier, offset);
            myStack->pushInteger((t_integer) qstring_);
          } else {
            qstring_ = v->getVariant_QString(identifier, offset);
            if (bReturnVar){
				      int nId = estatics->declare(pcode__QSTRING, 0, false, false);
    		      estatics->setQString(nId, qstring_, 0);
		  		    myStack->pushEQString(nId);
            } else {              
              myStack->pushQString(qstring_);
            }
          }
			    break;
		    case pcode__CSTRING:
          if (bPushPointerPointer){
            bPushPointerPointer = false;
            cstring_ = (t_cstring) v->getPointerPointer(identifier, offset);
            myStack->pushInteger((t_integer) cstring_);
          } else {
            cstring_ = v->getVariant_CString(identifier, offset);
            if (bReturnVar){
				      int nId = estatics->declare(pcode__CSTRING, 0, false, false);
    		      estatics->setCString(nId, cstring_, 0, 0);
		  		    myStack->pushECString(nId);
            } else {              
              myStack->pushCString(cstring_);
            }
          }
			    break;

		    case pcode__BYTE:
			    byte_ = v->getVariant_Byte(identifier, offset);
		      myStack->pushByte(byte_);
			    break;
		    case pcode__SHORT:
			    short_ = v->getVariant_Short(identifier, offset);
		      myStack->pushShort(short_);
			    break;
		    case pcode__INTEGER:
			    integer_ = v->getVariant_Integer(identifier, offset);
		      myStack->pushInteger(integer_);
			    break;
		    case pcode__LONG: 
			    long_ = v->getVariant_Long(identifier, offset);
		      myStack->pushLong(long_);
			    break;

		    case pcode__SINGLE: 
			    single_ = v->getVariant_Single(identifier, offset);
		      myStack->pushSingle(single_);
			    break;
		    case pcode__DOUBLE: 
			    double_ = v->getVariant_Double(identifier, offset);
		      myStack->pushDouble(double_);
			    break;
/*
		    case pcode__INT16: 
			    int16_ = v->getVariant_Int16(identifier, offset);
		      myStack->pushInt16(int16_);
			    break;
		    case pcode__INT32: 
			    int32_ = v->getVariant_Int32(identifier, offset);
		      myStack->pushInt32(int32_);
			    break;
		    case pcode__INT64: 
			    int64_ = v->getVariant_Int64(identifier, offset);
		      myStack->pushInt64(int64_);
			    break;
		    case pcode__UINT16: 
			    uint16_ = v->getVariant_UInt16(identifier, offset);
		      myStack->pushUInt16(uint16_);
			    break;
		    case pcode__UINT32: 
			    uint32_ = v->getVariant_UInt32(identifier, offset);
		      myStack->pushUInt32(uint32_);
			    break;
		    case pcode__UINT64: 
			    uint64_ = v->getVariant_UInt64(identifier, offset);
		      myStack->pushUInt64(uint64_);
			    break;
*/
		    case pcode__OBJECT: 
			    mv = (memory_variable2 *) v->getVariant_Object(identifier, offset);
          myStack->pushPointer(pcode__OBJECT, mv, false, true);
		      //myStack->pushObject(mv);
			    break;
          
		    case pcode__ARRAY:  // Variant variable mit array of variant   e.g. array2 = Array(1, 2, 3)
		      myStack->pushInteger(0);
			    break;

		    case pcode__EMPTY: 
		      myStack->pushInteger(0);
			    break;
        
		    case pcode__CURRENCY:
    			currency_ = v->getVariant_Currency(identifier, offset);
	    	  myStack->pushCurrency(currency_);
			    break;
          
		    case pcode__DATE:
    			date_ = v->getVariant_Date(identifier, offset);
	    	  myStack->pushDate(date_);
			    break;
          
        case pcode__ERROR:
			    integer_ = v->getVariant_Integer(identifier, offset);
		      myStack->pushError(integer_);
			    break;
          
		    default:

          if (memory_type::isBinding(nVarType)){
            bBinding = true;
            bType = false;
//            bStructure = false;
            bClass = false;
          } else if (myType->exist(nVarType)){      
            bBinding = false;
            bType = true;
            //bStructure = false;
            bClass = false;          

          } else if (myClass->exist(nVarType)){
            bBinding = false;
            bType = false;
            //bStructure = false;
            bClass = true;  
          }

          if (bType){

			       myStack->pushID(identifier, nVarType, v);
/*
          } else if (bStructure){

			       myStack->pushID(identifier, nVarType, v);
*/
          } else if (bClass){

			      object_ = v->getVariant_Object(identifier, offset); 

            if (bAssignment){

#ifdef HAS_CONSOLE
              if (!bSilent){
                sprintf(ac, "ME = &H%X (Object)", object_);
             }
#endif
              meVars = (memory_variable2 *) object_;
            } else {
#ifdef HAS_CONSOLE
              if (!bSilent){
                sprintf(ac, "--> &H%X (Object)", object_);
             }
#endif

             if (bBindingParent){ // desired object is the qt binding object, which is parent of this class       
               

               
               memory_variable2 *mv3 = (memory_variable2 *) object_;

               myStack->pushParameter(mv3->getBindingParentClassType(), mv3->getBindingParentClassPointer());


             } else {
               myStack->pushPointer(pcode__OBJECT, (memory_variable2 *) object_, false, true);
    			      //myStack->pushObject((memory_variable2 *) object_);
             }
            }

#ifdef HAS_CONSOLE
            if (!bSilent){
              CONSOLE pcodePrint(ac);
           }
#endif

          } else if (bBinding){

			      pointer_ = v->getVariant_Pointer(identifier, offset);   

            myStack->pushParameter(nVarType, pointer_);

          }
          movType_offset = n;
			    break;

			    }

			break;

		case pcode__ID:
      myStack->pushID(identifier, nVarType, v);
      movType_offset = n;
			break;

      
		case pcode__CURRENCY:
			currency_ = v->getCurrency(identifier, offset);
		  myStack->pushCurrency(currency_);
			break;

      
		case pcode__DATE:
			date_ = v->getDate(identifier, offset);
		  myStack->pushDate(date_);
			break;
      
		default:
     if (bType){

       myStack->pushID(identifier, nVarType, v);

     } else if (bClass){

			  object_ = v->getObject(identifier, offset); 

        if (bAssignment){

#ifdef HAS_CONSOLE
          if (!bSilent){
            sprintf(ac, "ME = &H%X (Object)", object_);
          }
#endif
          meVars = (memory_variable2 *) object_;
        } else {
#ifdef HAS_CONSOLE
          if (!bSilent){
            sprintf(ac, "--> &H%X (Object)", object_);
          }
#endif
          if (bBindingParent){ // desired object is the qt binding object, which is parent of this class       
           
            if (object_ == 0){ 
              if (scope == global && forms.contains(identifier)){
                
                pushStackInteger(identifier);
     
              } else {
                runtimeError("Nullpointer exception"); 
                return;
              }
            } else {
              memory_variable2 *mv3 = (memory_variable2 *) object_;
              myStack->pushParameter(mv3->getBindingParentClassType(), mv3->getBindingParentClassPointer());

            }


          } else {
            if (bBinding){
              myStack->pushPointer(pcode__OBJECT, (memory_variable2 *) object_, false, true);
            } else {
      			  myStack->pushPointer(nVarType, object_, false, false);
            }
          }
  		  	 
        }

#ifdef HAS_CONSOLE
        if (!bSilent){
          CONSOLE pcodePrint(ac);
        }
#endif

     } else if (bBinding){

			 pointer_ = v->getPointer(identifier, offset); 

       myStack->pushPointer(nVarType, pointer_, true, false);


     }
     movType_offset = n;

			break;

			}

  if (v->isMissing(identifier)){

		const char *acModule = "", *acSub = "", *acVar = "";
		findVars(identifier, &acModule, &acSub, &acVar);

    sprintf(ac, "IsMissing() has happened! Variable %s.%s.%s has not been passed.", acModule, acSub, acVar);
    runtimeError(ac);
  
  } 


}

void interpreter::fPUSH_RETURNVAR()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif



	t_pcode c; t_integer identifier; t_scope scope;	

	myPcode->rd_PUSH_RETURNVAR(&c, &identifier, &scope);
  {
    
		int nVarType;
    nVarType = getVar(scope)->type(identifier);

#ifdef HAS_CONSOLE
    if (!bSilent){

		  const char *acModule, *acSub, *acVar;
		  acModule = ""; acSub = ""; acVar = "";

		  findVars(identifier, &acModule, &acSub, &acVar);

      CONSOLE pcodePrintSep("");
	 	  CONSOLE pcodePrintPos(nPos);
		  CONSOLE pcodePrintOpc(pcode::pcode_(c));
	    CONSOLE pcodePrintVar(acModule, acSub, acVar);
    }
#endif


		int offset = getOffset(identifier, scope);

#ifdef HAS_CONSOLE
    if (!bSilent){
		  CONSOLE pcodePrintCR();
    }
#endif

		pushId(scope, identifier, offset, nVarType, false, 0, false, true);

	} // } else return pcodeError(utility::con(pcode::pcode_(pcode__PUSH_RETURNVAR), " missing"));

	return;
}

void interpreter::fMOV_ME()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif



	t_pcode c;

  myPcode->rd_MOV_ME(&c);
  {
	
#ifdef HAS_CONSOLE
    if (!bSilent){
      CONSOLE pcodePrintSep("");
	 	  CONSOLE pcodePrintPos(nPos);
		  CONSOLE pcodePrintOpc(pcode::pcode_(pcode__MOV_ME));
    }
#endif

#ifdef HAS_CONSOLE
    if (!bSilent){

		  CONSOLE pcodePrintCR();
    }
#endif

	} // } else return pcodeError(utility::con(pcode::pcode_(pcode__MOV_ME), " missing"));

	return;
}

void interpreter::fMOV_PARENT()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif



	t_pcode c;

  myPcode->rd_MOV_PARENT(&c);
  {
	
#ifdef HAS_CONSOLE
    if (!bSilent){
      CONSOLE pcodePrintSep("");
	 	  CONSOLE pcodePrintPos(nPos);
		  CONSOLE pcodePrintOpc(pcode::pcode_(pcode__MOV_PARENT));
    }
#endif

#ifdef HAS_CONSOLE
    if (!bSilent){

		  CONSOLE pcodePrintCR();
    }
#endif

	} // } else return pcodeError(utility::con(pcode::pcode_(pcode__MOV_PARENT), " missing"));

	return;
}

void interpreter::fSET_ME()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif



	t_pcode c; t_integer identifier; t_scope scope; t_boolean bAssignment = false;

  myPcode->rd_SET_ME(&c, &identifier, &scope, &bAssignment);
  {
	
		int nVarType;
    nVarType = getVar(scope)->type(identifier);

#ifdef HAS_CONSOLE
    if (!bSilent){

		  const char *acModule, *acSub, *acVar;
		  acModule = ""; acSub = ""; acVar = "";

		  findVars(identifier, &acModule, &acSub, &acVar);

      CONSOLE pcodePrintSep("");
	 	  CONSOLE pcodePrintPos(nPos);
		  CONSOLE pcodePrintOpc(pcode::pcode_(pcode__SET_ME));
	    CONSOLE pcodePrintVar(acModule, acSub, acVar);
    }
#endif



		int offset;
    offset = 0;

    if (bAssignment){
			offset = array_offset;
			array_offset = 0;

#ifdef HAS_CONSOLE
      if (!bSilent){
		    //if (!memory_type::scalar(identifier))
        {
			    CONSOLE pcodePrint("(");
			    CONSOLE pcodePrint(offset);
			    CONSOLE pcodePrint(")");
		    }
      }
#endif

    } else {
      offset = getOffset(identifier, scope);
    }    

    t_object object_;
    object_ = getVar(scope)->getObject(identifier, offset); 

    if (object_ == 0){ 
      runtimeError("Nullpointer exception");
      return;
    }

    OldmeVars = meVars;
    bSetMe = true;

    meVars = (memory_variable2 *) object_;

#ifdef HAS_CONSOLE
    if (!bSilent){

      static char ac[1024];

      sprintf(ac, "--> &H%X (Object)", object_);
      CONSOLE pcodePrint(ac);

		  CONSOLE pcodePrintCR();
    }
#endif

	} // } else return pcodeError(utility::con(pcode::pcode_(pcode__SET_ME), " missing"));

	return;
}

void interpreter::fbinding_SET_ME()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif



	t_pcode c; 
  t_integer type;

  myPcode->rd_binding_SET_ME(&c);
  myPcode->rd_PUSH_INTEGER(&c, &type);
  {
	
#ifdef HAS_CONSOLE
    if (!bSilent){
      CONSOLE pcodePrintSep("");
	 	  CONSOLE pcodePrintPos(nPos);
		  CONSOLE pcodePrintOpc(pcode::pcode_(pcode__binding_SET_ME));


    }
#endif

   	t_pcode pcodeType = myStack->popPCode();
    bool b44 = myStack->popBoolean();
    bool memory_variable2 = myStack->popBoolean();
    t_pointer p = myStack->popPointer();


    // qt binding
   
    if (meVars){

      meVars->setBindingParentClassPointer(p);
      meVars->setBindingParentClassType(type);
    }
    
#ifdef HAS_CONSOLE
    if (!bSilent){

		  CONSOLE pcodePrintCR();
    }
#endif

	} // } else return pcodeError(utility::con(pcode::pcode_(pcode__binding_SET_ME), " missing"));

	return;
}

void interpreter::fPUSH_ID()
{
  fPUSH_ID(pcode__PUSH_ID);
}

void interpreter::fbinding_PUSH_ID()
{
  fPUSH_ID(pcode__binding_PUSH_ID);
}

void interpreter::fPUSH_ID(t_pcode cPushId)
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif
  if (nPos == 105314){
    nPos=nPos;
  }


	t_pcode pushid; t_integer identifier; t_scope scope; 
  t_boolean bAssignment = false;

	bool bRet;
  bRet = false;

  int nVarType;
  nVarType = 0;


  switch(cPushId){

    case pcode__PUSH_ID:
      myPcode->rd_PUSH_ID(&pushid, &identifier, &scope, &bAssignment);
      /*
      if (identifier == 4){
        identifier = identifier;
      }*/
      nVarType = getVar(scope)->type(identifier);
      break;

    case pcode__binding_PUSH_ID:
      myPcode->rd_binding_PUSH_ID(&pushid, &identifier, &scope);
      
      nVarType = getVar(scope)->type(identifier);
/*
      if (!memory_type::isBinding(nVarType)){
        cPushId = pcode__PUSH_ID;
      }*/
      break;

    case pcode__PUSH_BOOLEAN_ID:
      myPcode->rd_PUSH_BOOLEAN_ID(&pushid, &identifier, &scope);
      
      nVarType = pcode__BOOLEAN;
      break;   

    case pcode__PUSH_QSTRING_ID:
      myPcode->rd_PUSH_QSTRING_ID(&pushid, &identifier, &scope);
      
      nVarType = pcode__QSTRING;
      break;

    case pcode__PUSH_CSTRING_ID:
      myPcode->rd_PUSH_CSTRING_ID(&pushid, &identifier, &scope);
      
      nVarType = pcode__CSTRING;
      break;

    case pcode__PUSH_LQSTRING_ID:
      myPcode->rd_PUSH_LQSTRING_ID(&pushid, &identifier, &scope);
      
      nVarType = pcode__LQSTRING;
      break;

    case pcode__PUSH_LCSTRING_ID:
      myPcode->rd_PUSH_LCSTRING_ID(&pushid, &identifier, &scope);
      
      nVarType = pcode__LCSTRING;
      break;

    case pcode__PUSH_BYTE_ID:
      myPcode->rd_PUSH_BYTE_ID(&pushid, &identifier, &scope);
      
      nVarType = pcode__BYTE;
      break;
// 
    case pcode__PUSH_SHORT_ID:
      myPcode->rd_PUSH_SHORT_ID(&pushid, &identifier, &scope);
      
      nVarType = pcode__SHORT;
      break;

    case pcode__PUSH_INTEGER_ID:
      myPcode->rd_PUSH_INTEGER_ID(&pushid, &identifier, &scope);
      
      nVarType = pcode__INTEGER;
      break;

    case pcode__PUSH_LONG_ID:
      myPcode->rd_PUSH_LONG_ID(&pushid, &identifier, &scope);
      
      nVarType = pcode__LONG;
      break;

    case pcode__PUSH_SINGLE_ID:
      myPcode->rd_PUSH_SINGLE_ID(&pushid, &identifier, &scope);
      
      nVarType = pcode__SINGLE;
      break;

    case pcode__PUSH_DOUBLE_ID:
      myPcode->rd_PUSH_DOUBLE_ID(&pushid, &identifier, &scope);
      
      nVarType = pcode__DOUBLE;
      break;

    case pcode__PUSH_VARIANT_ID:
      myPcode->rd_PUSH_VARIANT_ID(&pushid, &identifier, &scope);
      
      nVarType = pcode__VARIANT;
      break;

    case pcode__PUSH_CURRENCY_ID:
      myPcode->rd_PUSH_CURRENCY_ID(&pushid, &identifier, &scope);
      
      nVarType = pcode__CURRENCY;
      break;

    case pcode__PUSH_DATE_ID:
      myPcode->rd_PUSH_DATE_ID(&pushid, &identifier, &scope);
      
      nVarType = pcode__DATE;
      break;

    default:
      
      false;
      break;

  }

  bool bb = !bSilent && identifier != kbFormId && identifier != kbMenuBarId && identifier != kbToolBarId;


  {
#ifdef HAS_CONSOLE
    const char *acModule, *acSub, *acVar;
    
    if (bb){		 
      acModule = ""; acSub = ""; acVar = "";
		  findVars(identifier, &acModule, &acSub, &acVar);
    }
#endif
/*
    if (identifier == 33){
      identifier = identifier;
    }*/
/*
			   if (cPushId == pcode__PUSH_BOOLEAN_ID) nVarType = pcode__BOOLEAN;

  	else if (cPushId == pcode__PUSH_STRING_ID) nVarType = pcode__STRING;
  	else if (cPushId == pcode__PUSH_LSTRING_ID) nVarType = pcode__LSTRING;

  	else if (cPushId == pcode__PUSH_SINGLE_ID) nVarType = pcode__SINGLE;
  	else if (cPushId == pcode__PUSH_DOUBLE_ID) nVarType = pcode__DOUBLE;

  	else if (cPushId == pcode__PUSH_BYTE_ID) nVarType = pcode__BYTE;
  	else if (cPushId == pcode__PUSH_SHORT_ID) nVarType = pcode__SHORT;
  	else if (cPushId == pcode__PUSH_INTEGER_ID) nVarType = pcode__INTEGER;
  	else if (cPushId == pcode__PUSH_LONG_ID) nVarType = pcode__LONG;

  	else if (cPushId == pcode__PUSH_INT16_ID) nVarType = pcode__INT16;
  	else if (cPushId == pcode__PUSH_INT32_ID) nVarType = pcode__INT32;
  	else if (cPushId == pcode__PUSH_INT64_ID) nVarType = pcode__INT64;
  	else if (cPushId == pcode__PUSH_UINT16_ID) nVarType = pcode__UINT16;
  	else if (cPushId == pcode__PUSH_UINT32_ID) nVarType = pcode__UINT32;
  	else if (cPushId == pcode__PUSH_UINT64_ID) nVarType = pcode__UINT64;

  	else if (cPushId == pcode__PUSH_VARIANT_ID) nVarType = pcode__VARIANT;
  	//else if (cPushId == pcode__PUSH_CURRENCY_ID) nVarType = pcode__CURRENCY;
  	//else if (cPushId == pcode__PUSH_DATE_ID) nVarType = pcode__DATE;

  	else if (cPushId == pcode__PUSH_ID) nVarType = getVar(scope)->type(identifier);
  	else if (cPushId == pcode__binding_PUSH_ID) nVarType = getVar(scope)->type(identifier);
*/
#ifdef HAS_CONSOLE
    if (bb){
      CONSOLE pcodePrintSep("");
	 	  CONSOLE pcodePrintPos(nPos);
		  CONSOLE pcodePrintOpc(pcode::pcode_(cPushId));
	    CONSOLE pcodePrintVar(acModule, acSub, acVar);
    }
#endif

		int offset;
    offset = 0;

    if (bAssignment){
			offset = array_offset;
			array_offset = 0;

#ifdef HAS_CONSOLE
      if (bb){
		    
        {
			    CONSOLE pcodePrint("(");
			    CONSOLE pcodePrint(offset);
			    CONSOLE pcodePrint(")");
		    }
      }
#endif

    } else {
      offset = getOffset(identifier, scope);
    }    

    pushId(scope, identifier, offset, nVarType, bAssignment, 0, cPushId == pcode__binding_PUSH_ID);

    if (bSetMe){
      bSetMe = false;
      meVars = OldmeVars;
    }

#ifdef HAS_CONSOLE
    if (bb){
		  CONSOLE pcodePrintCR();
    }
#endif

	} // } else return pcodeError(utility::con(pcode::pcode_(cPushId), " missing"));

	return;
tt:
  {
#ifdef HAS_CONSOLE
    if (bb){
      CONSOLE pcodePrintSep("");
	 	  CONSOLE pcodePrintPos(nPos);
		  CONSOLE pcodePrintOpc(pcode::pcode_(cPushId));	    
      CONSOLE pcodePrintCR();
    }
#endif
    return;
  }
}

void interpreter::fPUSH__binding_ME()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif



	t_pcode c;

	myPcode->rd_PUSH__binding_ME(&c);
  {

#ifdef HAS_CONSOLE
    if (!bSilent){
      CONSOLE pcodePrintSep("");
	 	  CONSOLE pcodePrintPos(nPos);
		  CONSOLE pcodePrintOpc(pcode::pcode_(pcode__PUSH__binding_ME));

		  CONSOLE pcodePrintCR();
    }
#endif


    
    myStack->pushParameter(meVars->getBindingParentClassType(), meVars->getBindingParentClassPointer());


	} // } else return pcodeError(utility::con(pcode::pcode_(pcode__PUSH__binding_ME), " missing"));

	return;
}

void interpreter::fPUSH__binding_PARENT()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif



	t_pcode c;

	myPcode->rd_PUSH__binding_PARENT(&c);
  {

#ifdef HAS_CONSOLE
    if (!bSilent){
      CONSOLE pcodePrintSep("");
	 	  CONSOLE pcodePrintPos(nPos);
		  CONSOLE pcodePrintOpc(pcode::pcode_(pcode__PUSH__binding_PARENT));

		  CONSOLE pcodePrintCR();
    }
#endif


    myStack->pushParameter(meVars->getBindingParentClassType(), meVars->getBindingParentClassPointer());

	} // } else return pcodeError(utility::con(pcode::pcode_(pcode__PUSH__binding_PARENT), " missing"));

	return;
}

void interpreter::fPUSH_ME()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif



	t_pcode c;

	myPcode->rd_PUSH_ME(&c);
  {

#ifdef HAS_CONSOLE
    if (!bSilent){
      CONSOLE pcodePrintSep("");
	 	  CONSOLE pcodePrintPos(nPos);
		  CONSOLE pcodePrintOpc(pcode::pcode_(pcode__PUSH_ME));

		  CONSOLE pcodePrintCR();
    }
#endif

    myStack->pushPointer(pcode__OBJECT, meVars, false, true);
    //myStack->pushObject(meVars);

	} // } else return pcodeError(utility::con(pcode::pcode_(pcode__PUSH_ME), " missing"));

	return;
}

void interpreter::fPUSH_PARENT()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif



	t_pcode c;

	myPcode->rd_PUSH_PARENT(&c);
  {

#ifdef HAS_CONSOLE
    if (!bSilent){
      CONSOLE pcodePrintSep("");
	 	  CONSOLE pcodePrintPos(nPos);
		  CONSOLE pcodePrintOpc(pcode::pcode_(pcode__PUSH_PARENT));

		  CONSOLE pcodePrintCR();
    }
#endif

    myStack->pushPointer(pcode__OBJECT, meVars, false, true);

	} // } else return pcodeError(utility::con(pcode::pcode_(pcode__PUSH_PARENT), " missing"));

	return;
}



void interpreter::fPUSH_BOOLEAN_ID(){	fPUSH_ID(pcode__PUSH_BOOLEAN_ID); }

void interpreter::fPUSH_QSTRING_ID(){	fPUSH_ID(pcode__PUSH_QSTRING_ID); }
void interpreter::fPUSH_LQSTRING_ID(){	fPUSH_ID(pcode__PUSH_LQSTRING_ID); }

void interpreter::fPUSH_CSTRING_ID(){	fPUSH_ID(pcode__PUSH_CSTRING_ID); }
void interpreter::fPUSH_LCSTRING_ID(){	fPUSH_ID(pcode__PUSH_LCSTRING_ID); }

void interpreter::fPUSH_BYTE_ID(){	fPUSH_ID(pcode__PUSH_BYTE_ID); }
void interpreter::fPUSH_SHORT_ID(){	fPUSH_ID(pcode__PUSH_SHORT_ID); }
void interpreter::fPUSH_INTEGER_ID(){	fPUSH_ID(pcode__PUSH_INTEGER_ID); }
void interpreter::fPUSH_LONG_ID(){	fPUSH_ID(pcode__PUSH_LONG_ID); }

void interpreter::fPUSH_SINGLE_ID(){	fPUSH_ID(pcode__PUSH_SINGLE_ID); }
void interpreter::fPUSH_DOUBLE_ID(){	fPUSH_ID(pcode__PUSH_DOUBLE_ID); }



void interpreter::fPUSH_VARIANT_ID(){	fPUSH_ID(pcode__PUSH_VARIANT_ID); }
void interpreter::fPUSH_CURRENCY_ID(){	fPUSH_ID(pcode__PUSH_CURRENCY_ID); }
void interpreter::fPUSH_DATE_ID(){	fPUSH_ID(pcode__PUSH_DATE_ID); }

void interpreter::fPUSH_IDREF(t_pcode cPushIdRef)
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif



	t_pcode pushidref; t_integer identifier; t_scope scope;
  
	myPcode->rd_PUSH_IDREF(&pushidref, &identifier, &scope);
  {

    memory_variable2 *v;

    v = getVar(scope);
		int nVarType;
    nVarType = v->type(identifier);
	
    int offset;
    offset = getOffset(identifier, scope);

    t_array *a;
    a = v->getArray(identifier);

#ifdef HAS_CONSOLE
    if (!bSilent){
    
		  const char *acModule, *acSub, *acVar;
		  acModule = ""; acSub = ""; acVar = "";

		  findVars(identifier, &acModule, &acSub, &acVar);

      CONSOLE pcodePrintSep("");
	 	  CONSOLE pcodePrintPos(nPos);
		  CONSOLE pcodePrintOpc(pcode::pcode_(cPushIdRef));
	    CONSOLE pcodePrintVar(acModule, acSub, acVar);

		  CONSOLE pcodePrintCR();
    }
#endif

		{
		  
			myStack->pushReference(identifier, offset, nVarType, scope, a, getVar(scope));

	  }

	} // } else return pcodeError(utility::con(pcode::pcode_(cPushIdRef), " missing"));

	return;
}

void interpreter::fPUSH_IDREFVAL()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif



	t_pcode c; t_integer identifier; t_scope scope; t_integer nVarType;

	myPcode->rd_PUSH_IDREFVAL(&c, &identifier, &scope, &nVarType);
  {	

    int offset2;
    offset2 = 0;

		int id;
    id = identifier;

    memory_variable2 *v;
    v = 0;

    memory_variable2 *v2;
    v2 = getVar(scope);

    if (v2->isReference(identifier)){ // nur wenn Reference byref gepassed wurde und nicht eine pseudo-Reference ist mit byval
      id = v2->getReferenceId(identifier);
      offset2 = v2->getReferenceOffset(identifier);
      //int nn = v2->type(identifier);
  		  		
      v = (memory_variable2 *) getVar(scope)->getReferenceVariablePool(identifier);

      if (array_offset2.count() && (v2->isArray(identifier) || 
        (memory_type::isType(v2->type(identifier)) || memory_type::isEnum(v2->type(identifier)) )) ){
        offset2 += (array_offset2.last());
        array_offset2.removeLast();
      }

      scope = outofscope;

    } else {
  	  nVarType = v2->type(id);
      offset2 = getOffset(id, scope);
    }

#ifdef HAS_CONSOLE
    if (!bSilent){
      
		  const char *acModule, *acSub, *acVar;
		  acModule = ""; acSub = ""; acVar = "";

		  findVars(identifier, &acModule, &acSub, &acVar);

      CONSOLE pcodePrintSep("");
	 	  CONSOLE pcodePrintPos(nPos);
		  CONSOLE pcodePrintOpc(pcode::pcode_(c));
	    CONSOLE pcodePrintVar(acModule, acSub, acVar);

		  CONSOLE pcodePrintCR();
    }
#endif

		{

  		pushId(scope, id, offset2, nVarType, false, v);
		  
	  }

	} // } else return pcodeError(utility::con(pcode::pcode_(pcode__PUSH_IDREFVAL), " missing"));

	return;
}

void interpreter::fPUSH_IDPOINTER(t_pcode cPushIDPOINTER)
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif



	t_pcode c; t_integer identifier; t_scope scope;

	bool bRet = false;
    switch(myPcode->peekPCode()){
        case pcode__PUSH_IDPOINTER:
            myPcode->rd_PUSH_IDPOINTER(&c, &identifier, &scope);
            break;
            /*
        case pcode__PUSH_BOOLEAN_IDPOINTER:
            myPcode->rd_PUSH_BOOLEAN_IDPOINTER(&c, &identifier, &scope);
            break;
        case pcode__PUSH_CSTRING_IDPOINTER:
            myPcode->rd_PUSH_CSTRING_IDPOINTER(&c, &identifier, &scope);
            break;
        case pcode__PUSH_INTEGER_IDPOINTER:
            myPcode->rd_PUSH_CSTRING_IDPOINTER(&c, &identifier, &scope);
            break;
        case pcode__PUSH_LONG_IDPOINTER:
            myPcode->rd_PUSH_LONG_IDPOINTER(&c, &identifier, &scope);
            break;
        case pcode__PUSH_SINGLE_IDPOINTER:
            myPcode->rd_PUSH_SINGLE_IDPOINTER(&c, &identifier, &scope);
            break;
        case pcode__PUSH_DOUBLE_IDPOINTER:
            myPcode->rd_PUSH_DOUBLE_IDPOINTER(&c, &identifier, &scope);
            break;*/
        default:
            internalError("wrong pcode for PUSH_IDPOINTER");
            return;
            break;
    }
/*
	if (bRet == false && cPushIDPOINTER == pcode__PUSH_BOOLEAN_IDPOINTER && (bRet = myPcode->rd_PUSH_BOOLEAN_IDPOINTER(&c, &identifier, &scope))){}
	
  if (bRet == false && cPushIDPOINTER == pcode__PUSH_CSTRING_IDPOINTER && (bRet = myPcode->rd_PUSH_CSTRING_IDPOINTER(&c, &identifier, &scope))){}
	
  if (bRet == false && cPushIDPOINTER == pcode__PUSH_INTEGER_IDPOINTER && (bRet = myPcode->rd_PUSH_INTEGER_IDPOINTER(&c, &identifier, &scope))){}
	if (bRet == false && cPushIDPOINTER == pcode__PUSH_LONG_IDPOINTER && (bRet = myPcode->rd_PUSH_LONG_IDPOINTER(&c, &identifier, &scope))){}
	
  if (bRet == false && cPushIDPOINTER == pcode__PUSH_SINGLE_IDPOINTER && (bRet = myPcode->rd_PUSH_SINGLE_IDPOINTER(&c, &identifier, &scope))){}
	if (bRet == false && cPushIDPOINTER == pcode__PUSH_DOUBLE_IDPOINTER && (bRet = myPcode->rd_PUSH_DOUBLE_IDPOINTER(&c, &identifier, &scope))){}
  
  if (bRet == false && cPushIDPOINTER == pcode__PUSH_IDPOINTER && (bRet = myPcode->rd_PUSH_IDPOINTER(&c, &identifier, &scope))){}
  */
	//if (bRet)
    {

		const char *acModule, *acSub, *acVar;

#ifdef HAS_CONSOLE
    if (!bSilent){
      
		  acModule = ""; acSub = ""; acVar = "";
		  findVars(identifier, &acModule, &acSub, &acVar);

      CONSOLE pcodePrintSep("");
	 	  CONSOLE pcodePrintPos(nPos);
		  CONSOLE pcodePrintOpc(pcode::pcode_(c));
    }
#endif

		int offset;
    offset = getOffset(identifier, scope);


		{
		  void *p;
      p = 0;

			switch(cPushIDPOINTER){

				case pcode__PUSH_BOOLEAN_IDPOINTER:
					p = getVar(scope)->getAddress(identifier, offset, pcode__BOOLEAN);
					myStack->pushAddress(pcode__BOOLEAN_POINTER, p);
					break;

				case pcode__PUSH_QSTRING_IDPOINTER:
					p = getVar(scope)->getAddress(identifier, offset, pcode__QSTRING);
					myStack->pushAddress(pcode__QSTRING_POINTER, p);
					break;

				case pcode__PUSH_CSTRING_IDPOINTER:
					p = getVar(scope)->getAddress(identifier, offset, pcode__CSTRING);
					myStack->pushAddress(pcode__CSTRING_POINTER, p);
					break;

				case pcode__PUSH_INTEGER_IDPOINTER:
					p = getVar(scope)->getAddress(identifier, offset, pcode__INTEGER);
					myStack->pushAddress(pcode__INTEGER_POINTER, p);
					break;
				case pcode__PUSH_LONG_IDPOINTER:
					p = getVar(scope)->getAddress(identifier, offset, pcode__LONG);
					myStack->pushAddress(pcode__LONG_POINTER, p);
					break;

				case pcode__PUSH_SINGLE_IDPOINTER:
					p = getVar(scope)->getAddress(identifier, offset, pcode__SINGLE);
					myStack->pushAddress(pcode__SINGLE_POINTER, p);
					break;
				case pcode__PUSH_DOUBLE_IDPOINTER:
					p = getVar(scope)->getAddress(identifier, offset, pcode__DOUBLE);
					myStack->pushAddress(pcode__DOUBLE_POINTER, p);
					break;

				case pcode__PUSH_IDPOINTER:
					p = getVar(scope)->getAddress(identifier, offset, 0);
					myStack->pushAddress(pcode__INTEGER_POINTER, p);

					break;
				default:
					// 
					break;
			}
#ifdef HAS_CONSOLE
      if (!bSilent){
		    CONSOLE pcodePrint(acVar, p);
      }
#endif

	  }

#ifdef HAS_CONSOLE
    if (!bSilent){
		  CONSOLE pcodePrintCR();
    }
#endif

	} // } else return pcodeError(utility::con(pcode::pcode_(cPushIDPOINTER), " missing"));

	return;
}
