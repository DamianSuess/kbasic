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
#include "utility.h"


#include "interpreter_kbasic_binding.h"

void interpreter::fMOV()
{
  fMOV(pcode__MOV);
}

void interpreter::fMOV(t_pcode cMov, int nID, t_scope scope2, QByteArray *ba, int nBinaryPos)
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
  /*
  if (nPos == 145425){
    nPos = nPos;
  }*/
#endif
  int nestatics = 0;

  t_pcode mov;
  t_integer identifier;
  t_scope scope;
  t_integer lstringlen = 0; 
  t_boolean bAllSize;
  t_integer size;
  t_integer nVarType;

	int offset = 0;
	nVarType = 0;
  

	if (nID != -1){
		mov = cMov;
		identifier = nID;
		scope = scope2;

		//bRet = true;
	} else {

    switch(cMov){
      //pcode__MOVLS
      //pcode__MOVRS
      //pcode__MOV_RSTRING
      case pcode__MOV:
		    myPcode->rd_MOV(&mov, &identifier, &scope);
        break;
      case pcode__MOV_CONST:
		    myPcode->rd_MOV_CONST(&mov, &identifier, &scope);
        break;
      case pcode__MOV_IDREF:
		    myPcode->rd_MOV_IDREF(&mov, &identifier, &scope);
        break;
      case pcode__MOV_IDREFVAL:
		    myPcode->rd_MOV_IDREFVAL(&mov, &identifier, &scope, &nVarType, &bAllSize, &size);
        break;
      case pcode__MOV_BOOLEAN:
		    myPcode->rd_MOV_BOOLEAN(&mov, &identifier, &scope);
        break;

      case pcode__MOV_QSTRING:
		    myPcode->rd_MOV_QSTRING(&mov, &identifier, &scope);
        break;
      case pcode__MOV_RQSTRING:
		    myPcode->rd_MOV_RQSTRING(&mov, &identifier, &scope);
        break;
      case pcode__MOV_CSTRING:
		    myPcode->rd_MOV_CSTRING(&mov, &identifier, &scope);
        break;
      case pcode__MOV_RCSTRING:
		    myPcode->rd_MOV_RCSTRING(&mov, &identifier, &scope);
        break;
      case pcode__MOV_LQSTRING:
		    myPcode->rd_MOV_LQSTRING(&mov, &identifier, &scope, &lstringlen);
        break;
      case pcode__MOV_LCSTRING:
		    myPcode->rd_MOV_LCSTRING(&mov, &identifier, &scope, &lstringlen);
        break;

      case pcode__MOV_SINGLE:
		    myPcode->rd_MOV_SINGLE(&mov, &identifier, &scope);
        break;
      case pcode__MOV_DOUBLE:
		    myPcode->rd_MOV_DOUBLE(&mov, &identifier, &scope);
        break;
      case pcode__MOV_BYTE:
		    myPcode->rd_MOV_BYTE(&mov, &identifier, &scope);
        break;
      case pcode__MOV_SHORT:
		    myPcode->rd_MOV_SHORT(&mov, &identifier, &scope);
        break;
      case pcode__MOV_INTEGER:
		    myPcode->rd_MOV_INTEGER(&mov, &identifier, &scope);
        break;
      case pcode__MOV_LONG:
		    myPcode->rd_MOV_LONG(&mov, &identifier, &scope);
        break;
        /*
      case pcode__MOV_INT16:
		    myPcode->rd_MOV_INT16(&mov, &identifier, &scope);
        break;
      case pcode__MOV_INT32:
		    myPcode->rd_MOV_INT32(&mov, &identifier, &scope);
        break;
      case pcode__MOV_INT64:
		    myPcode->rd_MOV_INT64(&mov, &identifier, &scope);
        break;
      case pcode__MOV_UINT16:
		    myPcode->rd_MOV_UINT16(&mov, &identifier, &scope);
        break;
      case pcode__MOV_UINT32:
		    myPcode->rd_MOV_UINT32(&mov, &identifier, &scope);
        break;
      case pcode__MOV_UINT64:
		    myPcode->rd_MOV_UINT64(&mov, &identifier, &scope);
        break;*/

      case pcode__MOV_TYPE:
		    myPcode->rd_MOV_TYPE(&mov, &identifier, &scope, &bAllSize, &size);
        break;
      default:
        internalError("unkown type for MOV");
        return;
        break;
    }

	}

	
    {
#ifdef HAS_CONSOLE
		if (nID != -1){
      
      if (!bSilent){
        CONSOLE pcodePrintSep("");
	 		  CONSOLE pcodePrintPos("");
      }
		} else {
      if (!bSilent){
        CONSOLE pcodePrintSep("");
	 		  CONSOLE pcodePrintPos(nPos);
      }
		}
    if (!bSilent){
		  CONSOLE pcodePrintOpc(pcode::pcode_(cMov));
//	  CONSOLE pcodePrintVar(acModule, acSub, acVar));
    }
#endif

    

		const char *acModule;
		const char *acSub;
		const char *acVar;
    acModule = "";
    acSub = "";
    acVar = "";

		// search for 1. const, 2. var

		memory_variable *v;
		memory_variable2 *v2;

		if (cMov == pcode__MOV_CONST){
#ifdef HAS_CONSOLE      
      if (!bSilent){
			   findConsts(identifier, &acModule, &acSub, &acVar);
      }
#endif
			v = consts;
		} else {
#ifdef HAS_CONSOLE
      if (!bSilent){
			   findVars(identifier, &acModule, &acSub, &acVar);
      }
#endif
			v = getVar(scope);

			switch(cMov){
      
				case pcode__MOV_IDREFVAL:
           if (v->isReference(identifier)){ // nur wenn Reference byref gepassed wurde und nicht eine pseudo-Reference ist mit byval
						 array_offset += v->getReferenceOffset(identifier);
             nVarType = v->type(identifier);
						 v = v->getReferenceVariablePool(identifier);             
						 identifier = getVar(scope)->getReferenceId(identifier);             
           }
					break;
			}
			
		}

    if (v == 0){
      runtimeError("Nullpointer exception");
      return;
    }

		if (nVarType == 0){

      switch(cMov){
       //pcode__MOVLS
       //pcode__MOVRS
       //pcode__MOV_RSTRING
       case pcode__MOV:
         nVarType = v->type(identifier);
         break;
       case pcode__MOV_CONST:
         nVarType = v->type(identifier);
         break;
       case pcode__MOV_IDREF:
         nVarType = v->type(identifier);
         break;
       case pcode__MOV_IDREFVAL:
         break;
       case pcode__MOV_BOOLEAN:
         nVarType = pcode__BOOLEAN;
         break;

       case pcode__MOV_QSTRING:
         nVarType = pcode__QSTRING;
         break;
       case pcode__MOV_RQSTRING: // RSET
         nVarType = pcode__LQSTRING;
         break;
       case pcode__MOV_CSTRING:
         nVarType = pcode__CSTRING;
         break;
       case pcode__MOV_RCSTRING: // RSET
         nVarType = pcode__LCSTRING;
         break;
       case pcode__MOV_LQSTRING:
         nVarType = pcode__LQSTRING;
         break;
       case pcode__MOV_LCSTRING:
         nVarType = pcode__LCSTRING;
         break;

       case pcode__MOV_SINGLE:
         nVarType = pcode__SINGLE;
         break;
       case pcode__MOV_DOUBLE:
         nVarType = pcode__DOUBLE;
         break;
       case pcode__MOV_BYTE:
         nVarType = pcode__BYTE;
         break;
       case pcode__MOV_SHORT:
         nVarType = pcode__SHORT;
         break;
       case pcode__MOV_INTEGER:
         nVarType = pcode__INTEGER;
         break;
       case pcode__MOV_LONG:
         nVarType = pcode__LONG;
         break;
         /*
       case pcode__MOV_INT16:
         nVarType = pcode__INT16;
         break;
       case pcode__MOV_INT32:
         nVarType = pcode__INT32;
         break;
       case pcode__MOV_INT64:
         nVarType = pcode__INT64;
         break;
       case pcode__MOV_UINT16:
         nVarType = pcode__UINT16;
         break;
       case pcode__MOV_UINT32:
         nVarType = pcode__UINT32;
         break;
       case pcode__MOV_UINT64:
         nVarType = pcode__UINT64;
         break;*/

       case pcode__MOV_TYPE:
         nVarType = v->type(identifier);
/*
	       CONSOLE pcodePrint("\npcode__MOV_TYPE " );
	       CONSOLE pcodePrint(nVarType);
		     CONSOLE pcodePrintCR();*/

         break;
       default:
         internalError("unkown type for MOV");
         break;
      }
    }
    int wlen = 0;

    static char ac[1024];

		if (cMov == pcode__MOV_CONST){
      offset = 0;
#ifdef HAS_CONSOLE
      if (!bSilent){
        sprintf(ac, "");
      }
#endif
    } else {

			offset = array_offset;
			array_offset = 0;
#ifdef HAS_CONSOLE
			if (!bSilent && !memory_type::scalar(identifier) && offset > 0){
   			  sprintf(ac, "(%d )", offset);
      } else if (!bSilent){
        sprintf(ac, "");
      }
#endif
		}
		{

      t_boolean boolean_;// = 0;

      t_qstring qstring_ ;//= 0;
      t_cstring cstring_ ;//= 0;
     
      t_byte byte_;// = 0;
      t_short short_;// = 0;
      t_integer integer_;// = 0;
      t_long long_ ;//= 0;

      t_single single_;// = 0;
      t_double double_;// = 0;
/*
      t_int16 int16_;// = 0;
      t_int32 int32_;// = 0;
      t_long int64_;// = 0;
      t_uint16 uint16_;// = 0;
      t_uint32 uint32_;// = 0;
      t_uint64 uint64_;// = 0;*/

      t_object object_;// = 0;

      static t_currency currency_;
      static t_date date_;			


      int nVar;// = 0;

      t_pcode cType;// = 0;

			int nReferenceOffset;// = 0;
			int nReferenceType;// = 0;
     t_scope ReferenceScope;
     static t_array ReferenceArray;
			
//			myStack->dumpStack();

      // UDF copy or binding or object 
			if (cMov != pcode__MOV_IDREF && (!memory_type::scalar(nVarType) || (cMov == pcode__MOV_TYPE && (nVarType == pcode__QSTRING || nVarType == pcode__CSTRING)))){ 

        {

    		  cType = myStack->popPCode();
				  switch (cType){
           // object
    			  case pcode__OBJECT:
						  {

                // achtung! weiter unten ist variant mit setObject genauso, bei änderung beachten
                bool b44 = myStack->popBoolean();
                bool memory_variable2_ = myStack->popBoolean();                
							  object_ = myStack->popPointer();

               memory_variable2 *oldObject_ = (memory_variable2 *) v->getObject(identifier, offset);             
               v->setObject(identifier, object_, offset);


               if (object_ && ((memory_variable2 *) object_)->getBindingParentClassPointer()){
                  //memory_variable2 *vvv = getVar(scope);
                  kbasic_binding_setKbId(((memory_variable2 *) object_)->getBindingParentClassPointer(), (memory_variable2 *) object_/*getVar(scope)*/, identifier, ((memory_variable2 *) object_)->getBindingParentClassType());
               }
#ifdef HAS_CONSOLE
               if (!bSilent){
                 sprintf(acStringOutputBuffer, "%s = &H%X (Object)", ac, object_);

                 CONSOLE pcodePrintVar(acModule, acSub, acVar);
	               CONSOLE pcodePrint(acStringOutputBuffer);
		             CONSOLE pcodePrintCR();
               }
#endif
               myGc->inc((memory_variable2 *) object_); // gc
               myGc->dec(oldObject_); // gc
               myGc->dec2((t_pointer) oldObject_); // gc  wenn control = Null
               
               return;

							  break;
						  }
         // UDF copy bei GET (file)
         case pcode__BUFFER:
						  {

               int nSize;

							  t_pointer t = myStack->popBuffer(&nSize);
                


                int nnn = v->type(identifier);
                switch(nnn){
                   case pcode__QSTRING:
                     {
                       QString k = QString::fromUtf8((const char *) t, nSize);
                       v->setQString(identifier, &k, offset);
                     }
                     break;
                   case pcode__CSTRING:
                     {
                       QString k = QString::fromLocal8Bit((const char *) t, nSize);
                       v->setCString(identifier, k.toLocal8Bit().data(), offset, 0);
                     }
                     break;
                   default:
                     v->setStruct(identifier, t, offset, nSize);
                     break;
                }

                free(t);
               
#ifdef HAS_CONSOLE
        			  if (!bSilent) sprintf(acStringOutputBuffer, "%s = ...", ac);
#endif
							  break;
						  }
         case pcode__ID:
						  {

               t_integer nVarType2;// = 0;
               memory_variable2 *v2;// = 0;

							  t_integer n;
               n = myStack->popID(&nVarType2, &v2);

               int m1;
               m1 = v->getStructSize(identifier);

               int m2;
               m2 = v2->getStructSize(n);

               if (bAllSize && m1 != m2){
                 internalError("different size in UDF-copy");
                 return;
               }

               v->setStruct(identifier, v2->getStruct(n, movType_offset), offset, bAllSize ? m1 : size);
               movType_offset = 0;
#ifdef HAS_CONSOLE
        			  if (!bSilent) sprintf(acStringOutputBuffer, "%s = ...", ac);
#endif
							  break;
						  }
						  // qt binding
					  default:
						  {
                if (nVarType == -1){
                  internalError("Unknown variable on stack.");
                  return;
                }

           void *p3;
          bool b44 = myStack->popBoolean();
          bool memory_variable2_ = myStack->popBoolean();          
          if (b44){
            p3 = myStack->popPointer(); 

            if (p3 == 0){
               myGc->dec2(getVar(scope)->getPointer(identifier, offset)); // gc

               getVar(scope)->setPointer(identifier, p3, offset);
            } else {

              if (/*memory_type::isClass(nVarType) || memory_type::isKBasic(nVarType) || */memory_type::isBinding(nVarType)){
                kbasic_binding_setKbId(p3, getVar(scope), identifier, nVarType);
              }

              switch(nVarType){
                case pcode___strings:
                case pcode___stringsstrings:
                case pcode___array:
                case pcode___bits:
                  myGc->dec2(getVar(scope)->getPointer(identifier, offset)); // gc
                  myGc->add2(p3, nVarType); // gc
                  myGc->inc2(p3); // gc
                  break;
              }
             
              getVar(scope)->setPointer(identifier, p3, offset);
            
            }

            } else {

    			 t_pointer p;          
          p = myStack->popPointer(); 

          if (p == 0){
             myGc->dec2(getVar(scope)->getPointer(identifier, offset)); // gc

             getVar(scope)->setPointer(identifier, p, offset);
          } else {

            if (memory_variable2_){
              p = ((memory_variable2 *) p)->getBindingParentClassPointer();
            }
            

            // qt binding
            if (/*memory_type::isClass(nVarType) || memory_type::isKBasic(nVarType) || */memory_type::isBinding(nVarType)){

              kbasic_binding_setKbId(p, getVar(scope), identifier, nVarType);
            }

              switch(nVarType){
                case pcode___strings:
                case pcode___stringsstrings:
                case pcode___array:
                case pcode___bits:
                  myGc->dec2(getVar(scope)->getPointer(identifier, offset)); // gc
                  myGc->add2(p, nVarType); // gc
                  myGc->inc2(p); // gc
                  break;
              }

            getVar(scope)->setPointer(identifier, p, offset);

            }

#ifdef HAS_CONSOLE
          if (!bSilent) sprintf(acStringOutputBuffer, "%s = &H%X", ac, p3);
#endif
							  break;
						  }
				  }

          }
       }

			} else {

//			myStack->printStack();
re:
      
      if (ba == 0){
    	cType = myStack->popPCode();
      switch (cType){

        case pcode__VARIANT: 
          {
            t_variant v = myStack->popVariant();
               
            switch (v.nType){
              case pcode__BOOLEAN: boolean_ = v.boolean_; break;

    		      case pcode__QSTRING: 
                qstring_ = v.qstring_; break;
    		      case pcode__CSTRING: 
                cstring_ = v.cstring_; break;

  	          case pcode__BYTE: byte_ = v.byte_; break;
  	          case pcode__SHORT: short_ = v.short_; break;
  	          case pcode__INTEGER: integer_ = v.integer_; break;
              case pcode__LONG: 	long_ = v.long_; break;
      
    		      case pcode__SINGLE: single_ = v.single_; break;
    		      case pcode__DOUBLE: double_ = v.double_; break;

  	          case pcode__CURRENCY: currency_ = v.currency_; break;
  	          case pcode__DATE: date_ =v.date_; break;

              case pcode__OBJECT:
                   object_ = v.object_;               
						       break;

  	          case pcode__ARRAY2:  // e.g. array2 = Array(1, 2, 3)
						       nVarType = pcode__ARRAY2;
						       break;

  	          case pcode__EMPTY:  // Dim v As Variant : v = Empty 
						       break;

  	          case pcode__ERROR: 
                break;
            }

          }
          break;

        case pcode__BOOLEAN: boolean_ = myStack->popBoolean(); break;

    		case pcode__QSTRING: 
          qstring_ = myStack->popQString(); break;
    		case pcode__EQSTRING:
          {
             nestatics = myStack->popQStringId();
						 qstring_ = estatics->getQString(nestatics, 0);
						 cType = pcode__QSTRING;
           //  int n = qstring_->length();
           //  n = n;
          }
				  break;
    		case pcode__CSTRING: 
          cstring_ = myStack->popCString(); break;
    		case pcode__ECSTRING:
          {
             nestatics = myStack->popCStringId();
						 cstring_ = estatics->getCString(nestatics, 0);
						 cType = pcode__CSTRING;
          }
				  break;
    		case pcode__EWSTRING: // 16bit unicode cstring
          {
             nestatics = myStack->popCStringId();
						 cstring_ = estatics->getCString(nestatics, 0);
						 cType = pcode__CSTRING;

             wlen = estatics->getTypeSize(nestatics);
          }
				  break;
    		case pcode__REALCSTRING: cstring_ = myStack->popRealCString(); break;

  	    case pcode__BYTE: byte_ = myStack->popByte(); break;
  	    case pcode__SHORT: short_ = myStack->popShort(); break;
  	    case pcode__INTEGER: integer_ = myStack->popInteger(); break;
        case pcode__LONG: 	long_ = myStack->popLong(); break;
/*
        case pcode__INT16: int16_ = myStack->popInt16(); break;
  	    case pcode__INT32: int32_ = myStack->popInt32(); break;
  	    case pcode__INT64: int64_ = myStack->popInt64(); break;
  	    case pcode__UINT16: uint16_ = myStack->popUInt16(); break;
  	    case pcode__UINT32: uint32_ = myStack->popUInt32(); break;
  	    case pcode__UINT64: uint64_ = myStack->popUInt64(); break;
*/
    		case pcode__SINGLE: single_ = myStack->popSingle(); break;
    		case pcode__DOUBLE: double_ = myStack->popDouble(); break;

  	    case pcode__CURRENCY: currency_ = myStack->popCurrency(); break;
  	    case pcode__DATE: date_ = myStack->popDate(); break;

  	    case pcode__REFERENCE: 
						 nVar = myStack->popReference(&nReferenceOffset, &nReferenceType, &ReferenceScope, &ReferenceArray, (memory_variable2 **) &v2); 
						 nVarType = pcode__REFERENCE;
						 break;

        case pcode__OBJECT: // wenn variable = variant und stack = object, dann kommt man hier an
          {
             bool b44 = myStack->popBoolean();
             bool memory_variable2 = myStack->popBoolean();             
             object_ = myStack->popPointer(); 
          }
						 break;

  	    case pcode__ARRAY2:  // e.g. array2 = Array(1, 2, 3)
						 nVarType = pcode__ARRAY2;
						 break;

  	    case pcode__EMPTY:  // Dim v As Variant : v = Empty 
						 break;

    		case pcode__ID: 
					{

           t_integer nVarType2;// = 0;
           memory_variable2 *v2;// = 0;

						t_integer n;
           n = myStack->popID(&nVarType2, &v2);
           myStack->popPCode();

           cType = nVarType2;
           v = v2;

					  break;
					}

  	    case pcode__ERROR: 
          integer_ = myStack->popInteger(); 
          if (nVarType != pcode__VARIANT){
            cType = pcode__INTEGER;
          }
          break;

    		case pcode__BOOLEAN_POINTER: 
    		case pcode__BYTE_POINTER: 
    		case pcode__SHORT_POINTER: 
    		case pcode__INTEGER_POINTER: 
    		case pcode__LONG_POINTER: 
    		case pcode__SINGLE_POINTER: 
    		case pcode__DOUBLE_POINTER: 
    		case pcode__CSTRING_POINTER: 
          /*
    		case pcode__INT16_POINTER: 
    		case pcode__INT32_POINTER: 
    		case pcode__INT64_POINTER: 
    		case pcode__UINT16_POINTER: 
    		case pcode__UINT32_POINTER: 
    		case pcode__UINT64_POINTER: */
          integer_ = (t_integer) myStack->popAddress();
          cType = pcode__INTEGER;
          break;

        default:
          // qt binding
          if (nVarType == pcode__VARIANT){
          
    			    t_pointer p;
              bool b44 = myStack->popBoolean();
              bool memory_variable2 = myStack->popBoolean();
              p = myStack->popPointer(); 

              if (memory_variable2){
              

             // qt binding
             if (/*memory_type::isClass(cType) || memory_type::isBinding(cType) || */memory_type::isKBasic(cType)){
               kbasic_binding_setKbId(p, getVar(scope), identifier, cType);
             }
             getVar(scope)->setVariant_Pointer(identifier, p, cType, offset);


             }
#ifdef HAS_CONSOLE
             if (!bSilent) sprintf(acStringOutputBuffer, "%s = &H%X", ac, p);
#endif
							break;
						  
          } else {
            internalError("unknown PCODE on stack for MOV");
          }          
          break;
      }
      }

		//	myStack->printStack();


			switch(nVarType){
				case pcode__REFERENCE:
					{
            if (v2->isReference(nVar)){ // falls eine reference auf eine reference, muss die reference auf die eigentliche quellvariable gemacht werden
              memory_variable2 *v3;
              v3 = (memory_variable2 *) v2->getReferenceVariablePool(nVar);
              int nReferenceOffset3;
              nReferenceOffset3 = v2->getReferenceOffset(nVar);
              t_array *ReferenceArray3;
              ReferenceArray3 = v2->getReferenceArray(nVar);
              int nVar3;
              nVar3 = v2->getReferenceId(nVar);

              nVar = nVar3;
              nReferenceOffset = nReferenceOffset3;
              v->setArray(identifier, ReferenceArray3);    
              v2 = v3;
            } else { 
              v->setArray(identifier, &ReferenceArray);            
            }
  		  		v->setReferenceId(identifier, nVar);
  		  		v->setReferenceOffset(identifier, nReferenceOffset);
  		  		v->setReferenceVariablePool(identifier, v2);
  		  		v->setReferenceScope(identifier, ReferenceScope);      
            //int nn = v->type(identifier);
  		  		
#ifdef HAS_CONSOLE
           if (!bSilent) {
						  const char *acModule2, *acSub2, *acVar2;
						  findVars(nVar, &acModule2, &acSub2, &acVar2);

             sprintf(acStringOutputBuffer, "%s at &H%X REFERS TO &H%X::%s", ac, v, v2, acVar2);
           }
#endif
					}
					break;

        case pcode__OBJECT:
					break;

				case pcode__ARRAY2: // e.g. array2 = Array(1, 2, 3)
					{
           if (v->type(identifier) != pcode__VARIANT){
              internalError("variable is not VARIANT type");
              return;
           }

           
           int m = array_offset;
           bool b = bSilent;
           bSilent = true;

           for (int i = popStackInteger() - 1; i >= 0; i--){             
             array_offset = sizeof(t_variant) * i;
             fMOV(cMov, identifier, scope);
           }

           bSilent = b;
           array_offset = m;
#ifdef HAS_CONSOLE
  					if (!bSilent) sprintf(acStringOutputBuffer, "%s = Array(...)", acVar, ac);
#endif
					}
					break;

				case pcode__BOOLEAN: // BOOLEAN

          if (cType == pcode__BOOLEAN){
    				v->setBoolean(identifier, boolean_, offset);
#ifdef HAS_CONSOLE
  					if (!bSilent) sprintf(acStringOutputBuffer, "%s = %d", ac, (t_integer) boolean_);
#endif

          } else if (cType == pcode__BYTE){
    				v->setBoolean(identifier, (t_boolean) byte_, offset);
#ifdef HAS_CONSOLE
  					if (!bSilent) sprintf(acStringOutputBuffer, "%s = %d", ac, (t_integer) byte_);
#endif
          } else if (cType == pcode__SHORT){
    				v->setBoolean(identifier, (t_boolean) short_, offset);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%s = %d", ac, (t_integer) short_);
#endif
          } else if (cType == pcode__INTEGER){
  		  		v->setBoolean(identifier, (t_boolean) integer_, offset);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%s = %d (warning lost precision: auto-cast to BOOLEAN)", ac, (t_integer) integer_);
#endif
          } else if (cType == pcode__LONG){
  		  		v->setBoolean(identifier, (t_boolean) long_, offset);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%s = %I64d (warning lost precision: auto-cast to BOOLEAN)", ac, long_);
#endif
   	   	  } else if (cType == pcode__SINGLE){
    				v->setBoolean(identifier, (t_boolean) single_, offset);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%s = %d (warning lost precision: auto-cast to BOOLEAN)", ac, (t_integer) single_);
#endif
          } else if (cType == pcode__DOUBLE){
    				v->setBoolean(identifier, (t_boolean) double_, offset);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%s = %d (warning lost precision: auto-cast to BOOLEAN)", ac, (t_integer) double_);
#endif
          } else if (cType == pcode__CURRENCY){
    				v->setBoolean(identifier, (t_boolean) currency_.toBoolean(), offset);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%s = %d (warning lost precision: auto-cast to BOOLEAN)", ac, (t_integer) currency_.toBoolean());
#endif
          } else {
            runtimeError("Cast exception");
            goto er;
		      }
					break;

				case pcode__QSTRING: // QSTRING

          if (ba){ // binary copy
      		
            v->setQString(identifier, &QString::fromLatin1(ba->data(), ba->length()), offset, nBinaryPos);     
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%s = Unicode", ac);
#endif
					} else if (cType == pcode__BOOLEAN){
    				v->setQString_Boolean(identifier, &kbNullQString, boolean_, offset);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%s = Unicode", ac);
#endif
          } else if (cType == pcode__QSTRING){
      		
            v->setQString(identifier, qstring_, offset);     
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%s = Unicode", ac);
#endif

          } else if (cType == pcode__CSTRING || cType == pcode__REALCSTRING){
            v->setQString_CString(identifier, &kbNullQString, cstring_, offset);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%s = Unicode", ac);
#endif

          } else if (cType == pcode__BYTE){
    				v->setQString_Byte(identifier, &kbNullQString, byte_, offset);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%s = Unicode", ac);
#endif
          } else if (cType == pcode__SHORT){
    				v->setQString_Short(identifier, &kbNullQString, short_, offset);
#ifdef HAS_CONSOLE
  					if (!bSilent) sprintf(acStringOutputBuffer, "%s = Unicode", ac);
#endif
		      } else if (cType == pcode__INTEGER){
    				v->setQString_Integer(identifier, &kbNullQString, integer_, offset);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%s = Unicode", ac);
#endif
		      } else if (cType ==  pcode__LONG){
    				v->setQString_Long(identifier, &kbNullQString, long_, offset);
#ifdef HAS_CONSOLE
  					if (!bSilent) sprintf(acStringOutputBuffer, "%s = Unicode", ac);
#endif
   	   	  } else if (cType == pcode__SINGLE){
            v->setQString_Single(identifier, &kbNullQString, single_, offset);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%s = \"%-30.30s\"", ac, acStringConvertBuffer);
#endif
          } else if (cType == pcode__DOUBLE){
            v->setQString_Double(identifier, &kbNullQString, double_, offset);
#ifdef HAS_CONSOLE
  					if (!bSilent) sprintf(acStringOutputBuffer, "%s = Unicode", ac);

#endif
          } else if (cType == pcode__CURRENCY){
            v->setQString_Currency(identifier, &kbNullQString, currency_, offset);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%s = Unicode", ac);
#endif          
          } else if (cType == pcode__DATE){
            v->setQString_Date(identifier, &kbNullQString, date_, offset);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%s = Unicode", ac);
#endif
          } else {
            runtimeError("Cast exception");
            goto er;
					}
					break;
        
        case pcode__LQSTRING: // LQSTRING

					if (cType == pcode__BOOLEAN){
    				v->setLQString_Boolean(identifier, &kbNullQString, boolean_, offset, lstringlen);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%s = Unicode", ac);
#endif
          } else if (cType == pcode__QSTRING){
            if (cMov == pcode__MOV_RQSTRING){ // RSET

              int n = v->getTypeSize(identifier);
              QString s; 
              s.fill(' ', n);
              s += *qstring_;

    			    v->setLQString(identifier, &s, offset, lstringlen);
            } else {
              v->setLQString(identifier, qstring_, offset, lstringlen);
            }

          } else if (cType == pcode__CSTRING || cType == pcode__REALCSTRING){

            if (cMov == pcode__MOV_RCSTRING){ // RSET
              int n = v->getTypeSize(identifier);

               char *ac;

               textbuffer *myTextbuffer = new textbuffer();
              ac = myTextbuffer->get(n + 1);              
              memset((void *) ac, ' ', n);
              memset((void *) (ac + n), 0, n);

              int n2;
              n2 = strlen(cstring_);
              memcpy((void *) (ac + n - n2 - 1), (void *) cstring_, n2);

        			 v->setRQString_CString(identifier, &kbNullQString, ac, offset, n);
               delete myTextbuffer;

            } else {

    			    	v->setLQString_CString(identifier, &kbNullQString, cstring_, offset, lstringlen);
            }

            if (!bSilent) sprintf(acStringOutputBuffer, "%s = Unicode", ac);

          } else if (cType == pcode__BYTE){
    				v->setLQString_Byte(identifier, &kbNullQString, byte_, offset, lstringlen);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%s = Unicode", ac);
#endif
          } else if (cType == pcode__SHORT){
    				v->setLQString_Short(identifier, &kbNullQString, short_, offset, lstringlen);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%s = Unicode", ac);
#endif
		      } else if (cType == pcode__INTEGER){
    				v->setLQString_Integer(identifier, &kbNullQString, integer_, offset, lstringlen);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%s = Unicode", ac);
#endif
		      } else if (cType ==  pcode__LONG){
    				v->setLQString_Long(identifier, &kbNullQString, long_, offset, lstringlen);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%s = Unicode", ac);
#endif
  	   	  } else if (cType == pcode__SINGLE){
    				v->setLQString_Single(identifier, &kbNullQString, single_, offset, lstringlen);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%s = Unicode", ac);
#endif
          } else if (cType == pcode__DOUBLE){
    				v->setLQString_Double(identifier, &kbNullQString, double_, offset, lstringlen);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%s = Unicode", ac);
#endif
          } else if (cType == pcode__CURRENCY){
    				v->setLQString_QString(identifier, &kbNullQString, currency_.toQString(), offset, lstringlen);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%s = Unicode", ac);
#endif
          } else if (cType == pcode__DATE){
    				v->setLQString_QString(identifier, &kbNullQString, date_.toQString(), offset, lstringlen);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%s = Unicode", ac);
#endif
          } else {
            runtimeError("Cast exception");
            goto er;
					}
					break;

				case pcode__CSTRING: // CSTRING

					if (cType == pcode__BOOLEAN){
            sprintf(acStringConvertBuffer, "%d", (t_integer) boolean_ ? -1 : 0);
    				v->setCString(identifier, acStringConvertBuffer, offset, 0);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%s = \"%-30.30s\"", ac, acStringConvertBuffer);
#endif
          } else if (cType == pcode__QSTRING){
      		
            v->setCString_QString(identifier, "", qstring_, offset);     
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%s = Unicode", ac);
#endif
          } else if (cType == pcode__CSTRING || cType == pcode__REALCSTRING){
            if (wlen){
              v->setWString(identifier, cstring_, offset, wlen);     
            } else {
              v->setCString(identifier, cstring_, offset, 0);     
            }
#ifdef HAS_CONSOLE
            if (!bSilent && strlen(cstring_) > 30){ sprintf(acStringOutputBuffer, "%s = \"%-30.30s...\"", ac, cstring_); }
  					 else if (!bSilent) sprintf(acStringOutputBuffer, "%s = \"%-30.30s\"", ac, cstring_);
#endif
          } else if (cType == pcode__BYTE){
	 					sprintf(acStringConvertBuffer, "%d", (t_integer) byte_);
    				v->setCString(identifier, acStringConvertBuffer, offset, 0);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%s = \"%-30.30s\"", ac, acStringConvertBuffer);
#endif
          } else if (cType == pcode__SHORT){
	 					sprintf(acStringConvertBuffer, "%d", (t_integer) short_);
    				v->setCString(identifier, acStringConvertBuffer, offset, 0);
#ifdef HAS_CONSOLE
  					if (!bSilent) sprintf(acStringOutputBuffer, "%s = \"%-30.30s\"", ac, acStringConvertBuffer);
#endif
		      } else if (cType == pcode__INTEGER){
	 					sprintf(acStringConvertBuffer, "%d", integer_);
    				v->setCString(identifier, acStringConvertBuffer, offset, 0);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%s = \"%-30.30s\"", ac, acStringConvertBuffer);
#endif
		      } else if (cType ==  pcode__LONG){
#ifdef WINDOWS
	 					sprintf(acStringConvertBuffer, "%I64d", long_); // HIDE
#else
	 					sprintf(acStringConvertBuffer, "%lld", long_);
#endif
    				v->setCString(identifier, acStringConvertBuffer, offset, 0);
#ifdef HAS_CONSOLE
  					if (!bSilent) sprintf(acStringOutputBuffer, "%s = \"%-30.30s\"", ac, acStringConvertBuffer);
#endif
   	   	  } else if (cType == pcode__SINGLE){
  					sprintf(acStringConvertBuffer, "%f", single_);
    				v->setCString(identifier, acStringConvertBuffer, offset, 0);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%s = \"%-30.30s\"", ac, acStringConvertBuffer);
#endif
          } else if (cType == pcode__DOUBLE){
  					sprintf(acStringConvertBuffer, "%f", double_);
    				v->setCString(identifier, acStringConvertBuffer, offset, 0);
#ifdef HAS_CONSOLE
  					if (!bSilent) sprintf(acStringOutputBuffer, "%s = \"%-30.30s\"", ac, acStringConvertBuffer);

#endif
          } else if (cType == pcode__CURRENCY){
  					sprintf(acStringConvertBuffer, "%s", currency_.toCString());
    				v->setCString(identifier, acStringConvertBuffer, offset, 0);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%s = \"%-30.30s\"", ac, acStringConvertBuffer);
#endif          
          } else if (cType == pcode__DATE){
  					sprintf(acStringConvertBuffer, "%s", date_.toCString());
    				v->setCString(identifier, acStringConvertBuffer, offset, 0);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%s = \"%-30.30s\"", ac, acStringConvertBuffer);
#endif
          } else {
            runtimeError("Cast exception");
            goto er;
					}
					break;       


        case pcode__LCSTRING: // LCSTRING

					if (cType == pcode__BOOLEAN){
            sprintf(acStringConvertBuffer, "%d", (t_integer) boolean_ ? -1 : 0);
    				v->setLCString(identifier, acStringConvertBuffer, offset, lstringlen);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%s = \"%-30.30s\"", ac, acStringConvertBuffer);
#endif
          } else if (cType == pcode__QSTRING){
            if (cMov == pcode__MOV_RQSTRING){ // RSET

              int n = v->getTypeSize(identifier);
              QString s; 
              s.fill(' ', n);
              s += *qstring_;

    			    v->setLCString_QString(identifier, "", &s, offset, lstringlen);
            } else {
              v->setLCString_QString(identifier, "", qstring_, offset, lstringlen);
            }

          } else if (cType == pcode__CSTRING || cType == pcode__REALCSTRING){

            if (cMov == pcode__MOV_RCSTRING){ // RSET
              int n = v->getTypeSize(identifier);

               char *ac;

               textbuffer *myTextbuffer = new textbuffer();
              ac = myTextbuffer->get(n + 1);              
              memset((void *) ac, ' ', n);
              memset((void *) (ac + n), 0, n);

              int n2;
              n2 = strlen(cstring_);
              memcpy((void *) (ac + n - n2 - 1), (void *) cstring_, n2);

        			 v->setRCString(identifier, ac, offset, n);
               delete myTextbuffer;

            } else {

    			    	v->setLCString(identifier, cstring_, offset, lstringlen);
            }

#ifdef HAS_CONSOLE
            if (!bSilent && strlen(cstring_) > 30){ sprintf(acStringOutputBuffer, "%s = \"%-30.30s...\"", ac, cstring_); }
						else if (!bSilent) sprintf(acStringOutputBuffer, "%s = \"%-30.30s\"", ac, cstring_);
#endif
          } else if (cType == pcode__BYTE){
	 					sprintf(acStringConvertBuffer, "%d", (t_integer) byte_);
    				v->setLCString(identifier, acStringConvertBuffer, offset, lstringlen);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%s = \"%-30.30s\"", ac, acStringConvertBuffer);
#endif
          } else if (cType == pcode__SHORT){
	 					sprintf(acStringConvertBuffer, "%d", (t_integer) short_);
    				v->setLCString(identifier, acStringConvertBuffer, offset, lstringlen);
#ifdef HAS_CONSOLE
  					if (!bSilent) sprintf(acStringOutputBuffer, "%s = \"%-30.30s\"", ac, acStringConvertBuffer);
#endif
		      } else if (cType == pcode__INTEGER){
	 					sprintf(acStringConvertBuffer, "%d", integer_);
    				v->setLCString(identifier, acStringConvertBuffer, offset, lstringlen);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%s = \"%-30.30s\"", ac, acStringConvertBuffer);
#endif
		      } else if (cType ==  pcode__LONG){
#ifdef WINDOWS
	 					sprintf(acStringConvertBuffer, "%I64d", long_); // HIDE
#else
	 					sprintf(acStringConvertBuffer, "%lld", long_);
#endif
    				v->setLCString(identifier, acStringConvertBuffer, offset, lstringlen);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%s = \"%-30.30s\"", ac, acStringConvertBuffer);
#endif
   	   	  } else if (cType == pcode__SINGLE){
  					sprintf(acStringConvertBuffer, "%f", single_);
    				v->setLCString(identifier, acStringConvertBuffer, offset, lstringlen);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%s = \"%-30.30s\"", ac, acStringConvertBuffer);
#endif
          } else if (cType == pcode__DOUBLE){
  					sprintf(acStringConvertBuffer, "%f", double_);
    				v->setLCString(identifier, acStringConvertBuffer, offset, lstringlen);
#ifdef HAS_CONSOLE  					
            if (!bSilent) sprintf(acStringOutputBuffer, "%s = \"%-30.30s\"", ac, acStringConvertBuffer);
#endif

          } else if (cType == pcode__CURRENCY){
  					sprintf(acStringConvertBuffer, "%s", currency_.toCString());
    				v->setLCString(identifier, acStringConvertBuffer, offset, lstringlen);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%s = \"%-30.30s\"", ac, acStringConvertBuffer);
#endif
          } else if (cType == pcode__DATE){
  					sprintf(acStringConvertBuffer, "%s", date_.toCString());
    				v->setLCString(identifier, acStringConvertBuffer, offset, lstringlen);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%s = \"%-30.30s\"", ac, acStringConvertBuffer);
#endif

          } else {
            runtimeError("Cast exception");
            goto er;
					}
					break;

        case pcode__BYTE:
					 
          if (cType == pcode__BOOLEAN){
            v->setByte(identifier, (t_byte) boolean_ ? -1 : 0, offset);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%s = %d (auto-cast to BYTE)", ac, (t_integer) boolean_ ? -1 : 0);
#endif
          } else if (cType == pcode__BYTE){
    				v->setByte(identifier, byte_, offset);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%s = %d", ac, (t_integer) byte_);
#endif
          } else if (cType == pcode__SHORT){
  		  		v->setByte(identifier, (t_byte) short_, offset);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%s = %d (warning lost precision: auto-cast to BYTE)", ac, (t_integer) short_);
#endif
          } else if (cType == pcode__INTEGER){
  		  		v->setByte(identifier, (t_byte) integer_, offset);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%s = %d (warning lost precision: auto-cast to BYTE)", ac, (t_integer) integer_);
#endif
          } else if (cType == pcode__LONG){
  		  		v->setByte(identifier, (t_byte) long_, offset);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%s = %d (warning lost precision: auto-cast to BYTE)", ac, (t_integer) long_);
#endif  	   	  
  	   	  } else if (cType == pcode__SINGLE){
    				v->setByte(identifier, (t_byte) floor(single_), offset);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%s = %d (warning lost precision: auto-cast to BYTE)", ac, (t_integer) single_);
#endif
          } else if (cType == pcode__DOUBLE){
    				v->setByte(identifier, (t_byte) floor(double_), offset); 
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%s = %d (warning lost precision: auto-cast to BYTE)", ac, (t_integer) double_);
#endif
            /*
          } else if (cType == pcode__INT16){
  		  		v->setByte(identifier, (t_byte) int16_, offset);
	  				if (!bSilent) sprintf(acStringOutputBuffer, "%s = %d (warning lost precision: auto-cast to BYTE)", ac, (t_integer) int16_);
          } else if (cType == pcode__INT32){
  		  		v->setByte(identifier, (t_byte) int32_, offset);
	  				if (!bSilent) sprintf(acStringOutputBuffer, "%s = %d (warning lost precision: auto-cast to BYTE)", ac, (t_integer) int32_);
          } else if (cType == pcode__INT64){
  		  		v->setByte(identifier, (t_byte) int64_, offset);
	  				if (!bSilent) sprintf(acStringOutputBuffer, "%s = %d (warning lost precision: auto-cast to BYTE)", ac, (t_integer) int64_);
          } else if (cType == pcode__UINT16){
  		  		v->setByte(identifier, (t_byte) uint16_, offset);
	  				if (!bSilent) sprintf(acStringOutputBuffer, "%s = %d (warning lost precision: auto-cast to BYTE)", ac, (t_integer) uint16_);
          } else if (cType == pcode__UINT32){
  		  		v->setByte(identifier, (t_byte) uint32_, offset);
	  				if (!bSilent) sprintf(acStringOutputBuffer, "%s = %d (warning lost precision: auto-cast to BYTE)", ac, (t_integer) uint32_);
          } else if (cType == pcode__UINT64){
  		  		v->setByte(identifier, (t_byte) uint64_, offset);
	  				if (!bSilent) sprintf(acStringOutputBuffer, "%s = %d (warning lost precision: auto-cast to BYTE)", ac, (t_integer) uint64_);
*/
          } else if (cType == pcode__CURRENCY){
    				v->setByte(identifier, currency_.toByte(), offset); 
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%s = %d (warning lost precision: auto-cast to BYTE)", ac, (t_integer) currency_.toByte());
#endif
          } else {
            runtimeError("Cast exception");
            goto er;
		      }
					break;
        case pcode__SHORT:
					 
          if (cType == pcode__BOOLEAN){
    				v->setShort(identifier, (t_short) boolean_ ? -1 : 0, offset);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%s = %d (auto-cast to SHORT)", ac, (t_integer) boolean_ ? -1 : 0);		      
#endif
          } else if (cType == pcode__BYTE){
    				v->setShort(identifier, (t_short) byte_, offset);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%s = %d (auto-cast to SHORT)", ac, (t_integer) short_);
#endif
          } else if (cType == pcode__SHORT){
  		  		v->setShort(identifier, short_, offset);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%s = %d", ac, (t_integer) short_);
#endif
          } else if (cType == pcode__INTEGER){
            v->setShort(identifier, (t_short) integer_, offset);
#ifdef HAS_CONSOLE
	  				if (!bSilent) sprintf(acStringOutputBuffer, "%s = %d (warning lost precision: auto-cast to SHORT)", ac, (t_integer) integer_);
#endif
          } else if (cType == pcode__LONG){
  		  		v->setShort(identifier, (t_short) long_, offset);
#ifdef HAS_CONSOLE
	  				if (!bSilent) sprintf(acStringOutputBuffer, "%s = %d (warning lost precision: auto-cast to SHORT)", ac, (t_integer) long_);  	   	  
#endif
          } else if (cType == pcode__SINGLE){
    				v->setShort(identifier, (t_short) floor(single_), offset);
#ifdef HAS_CONSOLE
  					if (!bSilent) sprintf(acStringOutputBuffer, "%s = %d (warning lost precision: auto-cast to SHORT)", ac, (t_integer) single_);
#endif
          } else if (cType == pcode__DOUBLE){
    				v->setShort(identifier, (t_short) floor(double_), offset); 
#ifdef HAS_CONSOLE
  					if (!bSilent) sprintf(acStringOutputBuffer, "%s = %d (warning lost precision: auto-cast to SHORT)", ac, (t_integer) double_);
#endif
            /*
          } else if (cType == pcode__INT16){
  		  		v->setShort(identifier, (t_short) int16_, offset);
	  				if (!bSilent) sprintf(acStringOutputBuffer, "%s = %d (warning lost precision: auto-cast to SHORT)", ac, (t_integer) int16_);
          } else if (cType == pcode__INT32){
  		  		v->setShort(identifier, (t_short) int32_, offset);
	  				if (!bSilent) sprintf(acStringOutputBuffer, "%s = %d (warning lost precision: auto-cast to SHORT)", ac, (t_integer) int32_);
          } else if (cType == pcode__INT64){
  		  		v->setShort(identifier, (t_short) int64_, offset);
	  				if (!bSilent) sprintf(acStringOutputBuffer, "%s = %d (warning lost precision: auto-cast to SHORT)", ac, (t_integer) int64_);
          } else if (cType == pcode__UINT16){
  		  		v->setShort(identifier, (t_short) uint16_, offset);
	  				if (!bSilent) sprintf(acStringOutputBuffer, "%s = %d (warning lost precision: auto-cast to SHORT)", ac, (t_integer) uint16_);
          } else if (cType == pcode__UINT32){
  		  		v->setShort(identifier, (t_short) uint32_, offset);
	  				if (!bSilent) sprintf(acStringOutputBuffer, "%s = %d (warning lost precision: auto-cast to SHORT)", ac, (t_integer) uint32_);
          } else if (cType == pcode__UINT64){
  		  		v->setShort(identifier, (t_short) uint64_, offset);
	  				if (!bSilent) sprintf(acStringOutputBuffer, "%s = %d (warning lost precision: auto-cast to SHORT)", ac, (t_integer) uint64_);
*/
          } else if (cType == pcode__CURRENCY){
    				v->setShort(identifier, currency_.toShort(), offset); 
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%s = %d (warning lost precision: auto-cast to SHORT)", ac, (t_integer) currency_.toShort());
#endif
          } else {
            runtimeError("Cast exception");
            goto er;
		      }
					break;
        case pcode__INTEGER: // INTEGER

          if (cType == pcode__BOOLEAN){
    				v->setInteger(identifier, (t_integer) boolean_ ? -1 : 0, offset);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%s = %d (auto-cast to INTEGER)", ac, (t_integer) boolean_ ? -1 : 0);
#endif
          } else if (cType == pcode__BYTE){
    				v->setInteger(identifier, (t_integer) byte_, offset);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%s = %d (auto-cast to INTEGER)", ac, (t_integer) byte_);
#endif
          } else if (cType == pcode__SHORT){
    				v->setInteger(identifier, (t_integer) short_, offset);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%s = %d (auto-cast to INTEGER)", ac, (t_integer) short_);
#endif
          } else if (cType == pcode__INTEGER){
  		  		v->setInteger(identifier, integer_, offset);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%s = %d", ac, integer_);
#endif
          } else if (cType == pcode__LONG){
  		  		v->setInteger(identifier, (t_integer) long_, offset);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%s = %d (warning lost precision: auto-cast to INTEGER)", ac, (t_integer) long_);
#endif
  	   	  } else if (cType == pcode__SINGLE){
    				v->setInteger(identifier, (t_integer) floor(single_), offset);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%s = %d (warning lost precision: auto-cast to INTEGER)", ac, (t_integer) single_);
#endif
          } else if (cType == pcode__DOUBLE){
    				v->setInteger(identifier, (t_integer) floor(double_), offset);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%s = %d (warning lost precision: auto-cast to INTEGER)", ac, (t_integer) double_);
#endif
            /*
		      } else if (cType == pcode__INT16){
  		  		v->setInteger(identifier, (t_integer) int16_, offset);
	  				if (!bSilent) sprintf(acStringOutputBuffer, "%s = %d (warning lost precision: auto-cast to INTEGER)", ac, (t_integer) int16_);
		      } else if (cType == pcode__INT32){
  		  		v->setInteger(identifier, (t_integer) int32_, offset);
	  				if (!bSilent) sprintf(acStringOutputBuffer, "%s = %d (warning lost precision: auto-cast to INTEGER)", ac, (t_integer) int32_);
		      } else if (cType == pcode__INT64){
  		  		v->setInteger(identifier, (t_integer) int64_, offset);
	  				if (!bSilent) sprintf(acStringOutputBuffer, "%s = %d (warning lost precision: auto-cast to INTEGER)", ac, (t_integer) int64_);
		      } else if (cType == pcode__UINT16){
  		  		v->setInteger(identifier, (t_integer) uint16_, offset);
	  				if (!bSilent) sprintf(acStringOutputBuffer, "%s = %d (warning lost precision: auto-cast to INTEGER)", ac, (t_integer) uint16_);
		      } else if (cType == pcode__UINT32){
  		  		v->setInteger(identifier, (t_integer) uint32_, offset);
	  				if (!bSilent) sprintf(acStringOutputBuffer, "%s = %d (warning lost precision: auto-cast to INTEGER)", ac, (t_integer) uint32_);
		      } else if (cType == pcode__UINT64){
  		  		v->setInteger(identifier, (t_integer) uint64_, offset);
	  				if (!bSilent) sprintf(acStringOutputBuffer, "%s = %d (warning lost precision: auto-cast to INTEGER)", ac, (t_integer) uint64_);
*/
          } else if (cType == pcode__CURRENCY){
    				v->setInteger(identifier, currency_.toInteger(), offset); 
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%s = %d (warning lost precision: auto-cast to INTEGER)", ac, (t_integer) currency_.toInteger());
#endif
            /*
          } else if (cType == pcode__DATE){
    				v->setInteger(identifier, date_.toInteger(), offset); 
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%s = %d (warning lost precision: auto-cast to INTEGER)", ac, (t_integer) currency_.toInteger());
#endif*/
          } else {
            runtimeError("Cast exception");
            goto er;
          }
					break;
				case pcode__LONG: // LONG
					 if (cType == pcode__BOOLEAN){
    				v->setLong(identifier, (t_long) boolean_ ? -1 : 0, offset);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%s = %I64d (auto-cast to LONG)", ac, (t_long) boolean_ ? -1 : 0);
#endif
          } else if (cType == pcode__BYTE){
    				v->setLong(identifier, (t_long) byte_, offset);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%s = %I64d (auto-cast to LONG)", ac, (t_long) byte_);
#endif
          } else if (cType == pcode__SHORT){
    				v->setLong(identifier, (t_long) short_, offset);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%s = %I64d (auto-cast to LONG)", ac, (t_long) short_);
#endif
          } else if (cType == pcode__INTEGER){
  		  		v->setLong(identifier, (t_long) integer_, offset);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%s = %d (auto-cast to LONG)", ac, integer_);
#endif
          } else if (cType ==  pcode__LONG){ 
  		  		v->setLong(identifier, long_, offset);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%s = %I64d", ac, long_);
#endif
  	   	  } else if (cType == pcode__SINGLE){
    				v->setLong(identifier, (t_long) floor(single_), offset);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%s = %I64d (warning lost precision: auto-cast to LONG)", ac, (t_long) single_);
#endif
          } else if (cType == pcode__DOUBLE){
    				v->setLong(identifier, (t_long) floor(double_), offset);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%s = %I64d (warning lost precision: auto-cast to LONG)", ac, (t_long) double_);
#endif
            /*
		      } else if (cType == pcode__INT16){
  		  		v->setLong(identifier, (t_long) int16_, offset);
	  				if (!bSilent) sprintf(acStringOutputBuffer, "%s = %d (auto-cast to LONG)", ac, int16_);
		      } else if (cType == pcode__INT32){
  		  		v->setLong(identifier, (t_long) int32_, offset);
	  				if (!bSilent) sprintf(acStringOutputBuffer, "%s = %I32d (auto-cast to LONG)", ac, int32_);
		      } else if (cType == pcode__INT64){
  		  		v->setLong(identifier, (t_long) int64_, offset);
	  				if (!bSilent) sprintf(acStringOutputBuffer, "%s = %I64d (auto-cast to LONG)", ac, int64_);
         } else if (cType == pcode__UINT16){
    				v->setLong(identifier, (t_long) uint16_, offset);
  					if (!bSilent) sprintf(acStringOutputBuffer, "%s = %I64d (warning lost precision: auto-cast to LONG)", ac, (t_long) uint16_);
         } else if (cType == pcode__UINT32){
    				v->setLong(identifier, (t_long) uint32_, offset);
  					if (!bSilent) sprintf(acStringOutputBuffer, "%s = %I64d (warning lost precision: auto-cast to LONG)", ac, (t_long) uint32_);
         } else if (cType == pcode__UINT64){
    				v->setLong(identifier, (t_long) uint64_, offset);
  					if (!bSilent) sprintf(acStringOutputBuffer, "%s = %I64d (warning lost precision: auto-cast to LONG)", ac, (t_long) uint64_);
*/
          } else if (cType == pcode__CURRENCY){
    				v->setLong(identifier, currency_.toLong(), offset); 
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%s = %I64d (warning lost precision: auto-cast to LONG)", ac, (t_long) currency_.toLong());
#endif
          } else {
            runtimeError("Cast exception");
            goto er;
		      }
					break;
				case pcode__SINGLE: // SINGLE
					if (cType == pcode__BOOLEAN){
    				v->setSingle(identifier, (t_single) boolean_ ? -1 : 0, offset);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%s = %.6f (auto-cast to SINGLE)", ac, (t_single) boolean_ ? -1 : 0);
#endif
          } else if (cType == pcode__BYTE){
    				v->setSingle(identifier, (t_single) byte_, offset);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%s = %.6f (auto-cast to SINGLE)", ac, (t_single) byte_);
#endif
          } else if (cType == pcode__SHORT){
    				v->setSingle(identifier, (t_single) short_, offset);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%s = %.6f (auto-cast to SINGLE)", ac, (t_single) short_);
#endif
          } else if (cType == pcode__INTEGER){
  		  		v->setSingle(identifier, (t_single) integer_, offset);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%s = %.6f (auto-cast to SINGLE)", ac, (t_single) integer_);
#endif
          } else if (cType ==  pcode__LONG){
  		  		v->setSingle(identifier, (t_single) long_, offset);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%s = %.6f (warning lost precision: auto-cast to SINGLE)", ac, (t_single) long_);
#endif
	  	   	} else if (cType == pcode__SINGLE){
    				v->setSingle(identifier, single_, offset);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%s = %.6f", ac, single_);
#endif
          } else if (cType == pcode__DOUBLE){
    				v->setSingle(identifier, (t_single) double_, offset);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%s = %.6f (warning lost precision: auto-cast to SINGLE)", ac, (t_single) double_);
#endif
            /*
         } else if (cType == pcode__INT16){
  		  		v->setSingle(identifier, (t_single) int16_, offset);
  					if (!bSilent) sprintf(acStringOutputBuffer, "%s = %.6f (auto-cast to SINGLE)", ac, (t_single) int16_);
         } else if (cType == pcode__INT32){
  		  		v->setSingle(identifier, (t_single) int32_, offset);
  					if (!bSilent) sprintf(acStringOutputBuffer, "%s = %.6f (auto-cast to SINGLE)", ac, (t_single) int32_);
		      } else if (cType ==  pcode__INT64){
  		  		v->setSingle(identifier, (t_single) int64_, offset);
  					if (!bSilent) sprintf(acStringOutputBuffer, "%s = %.6f (warning lost precision: auto-cast to SINGLE)", ac, (t_single) int64_);
         } else if (cType == pcode__UINT16){
  		  		v->setSingle(identifier, (t_single) uint16_, offset);
  					if (!bSilent) sprintf(acStringOutputBuffer, "%s = %.6f (auto-cast to SINGLE)", ac, (t_single) uint16_);
         } else if (cType == pcode__UINT32){
  		  		v->setSingle(identifier, (t_single) uint32_, offset);
  					if (!bSilent) sprintf(acStringOutputBuffer, "%s = %.6f (auto-cast to SINGLE)", ac, (t_single) uint32_);
		      } else if (cType ==  pcode__UINT64){
  		  		v->setSingle(identifier, (t_single) uint64_, offset);
  					if (!bSilent) sprintf(acStringOutputBuffer, "%s = %.6f (warning lost precision: auto-cast to SINGLE)", ac, (t_single) uint64_);
*/
          } else if (cType == pcode__CURRENCY){
    				v->setSingle(identifier, currency_.toSingle(), offset); 
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%s = %.6f (warning lost precision: auto-cast to SINGLE)", ac, (t_single) currency_.toSingle());
#endif
          } else {
            runtimeError("Cast exception");
            goto er;
		      }
					break;
				case pcode__DOUBLE: // DOUBLE
					 if (cType == pcode__BOOLEAN){
    				v->setDouble(identifier, (t_double) boolean_ ? -1 : 0, offset);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%s = %.6f (auto-cast to DOUBLE)", ac, (t_double) boolean_ ? -1 : 0);
#endif
          } else if (cType == pcode__BYTE){
    				v->setDouble(identifier, (t_double) byte_, offset);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%s = %.6f (auto-cast to DOUBLE)", ac, (t_double) byte_);
#endif
          } else if (cType == pcode__SHORT){
    				v->setDouble(identifier, (t_double) short_, offset);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%s = %.6f (auto-cast to DOUBLE)", ac, (t_double) short_);
#endif
          } else if (cType == pcode__INTEGER){
  		  		v->setDouble(identifier, (t_double) integer_, offset);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%s = %.6f (auto-cast to DOUBLE)", ac, (t_double) integer_);
#endif
          } else if (cType ==  pcode__LONG){
  		  		v->setDouble(identifier, (t_double) long_, offset);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%s = %.6f (warning lost precision: auto-cast to DOUBLE)", ac, (t_double) long_);
#endif
	  	   	} else if (cType == pcode__SINGLE){
    				v->setDouble(identifier, single_, offset);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%s = %.6f (auto-cast to DOUBLE)", ac, single_);
#endif
          } else if (cType == pcode__DOUBLE){
    				v->setDouble(identifier, double_, offset);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%s = %.6f", ac, double_);
#endif
            /*
		      } else if (cType == pcode__INT16){
  		  		v->setDouble(identifier, (t_double) int16_, offset);
  					if (!bSilent) sprintf(acStringOutputBuffer, "%s = %.6f (auto-cast to DOUBLE)", ac, (t_double) int16_);
		      } else if (cType == pcode__INT32){
  		  		v->setDouble(identifier, (t_double) int32_, offset);
  					if (!bSilent) sprintf(acStringOutputBuffer, "%s = %.6f (auto-cast to DOUBLE)", ac, (t_double) int32_);
		      } else if (cType ==  pcode__INT64){
  		  		v->setDouble(identifier, (t_double) int64_, offset);
  					if (!bSilent) sprintf(acStringOutputBuffer, "%s = %.6f (warning lost precision: auto-cast to DOUBLE)", ac, (t_double) int64_);
		      } else if (cType == pcode__UINT16){
  		  		v->setDouble(identifier, (t_double) uint16_, offset);
  					if (!bSilent) sprintf(acStringOutputBuffer, "%s = %.6f (auto-cast to DOUBLE)", ac, (t_double) uint16_);
		      } else if (cType == pcode__UINT32){
  		  		v->setDouble(identifier, (t_double) uint32_, offset);
  					if (!bSilent) sprintf(acStringOutputBuffer, "%s = %.6f (auto-cast to DOUBLE)", ac, (t_double) uint32_);
		      } else if (cType ==  pcode__UINT64){
  		  		v->setDouble(identifier, (t_double) uint64_, offset);
  					if (!bSilent) sprintf(acStringOutputBuffer, "%s = %.6f (warning lost precision: auto-cast to DOUBLE)", ac, (t_double) uint64_);
*/
          } else if (cType == pcode__CURRENCY){
    				v->setDouble(identifier, currency_.toDouble(), offset); 
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%s = %.6f (warning lost precision: auto-cast to DOUBLE)", ac, (t_double) currency_.toDouble());
#endif
          } else {
            runtimeError("Cast exception");
            goto er;
		      }
					break;
          /*
        case pcode__INT16: 

          if (cType == pcode__BOOLEAN){
    				v->setInt16(identifier, (t_int16) boolean_, offset);
  					if (!bSilent) sprintf(acStringOutputBuffer, "%s = %d (auto-cast to INT16)", ac, (t_int16) boolean_);

          } else if (cType == pcode__BYTE){
    				v->setInt16(identifier, (t_int16) byte_, offset);
  					if (!bSilent) sprintf(acStringOutputBuffer, "%s = %d (auto-cast to INT16)", ac, (t_int16) byte_);
          } else if (cType == pcode__SHORT){
    				v->setInt16(identifier, (t_int16) short_, offset);
  					if (!bSilent) sprintf(acStringOutputBuffer, "%s = %d (auto-cast to INT16)", ac, (t_int16) short_);
          } else if (cType == pcode__INTEGER){
    				v->setInt16(identifier, (t_int16) integer_, offset);
  					if (!bSilent) sprintf(acStringOutputBuffer, "%s = %d (warning lost precision: auto-cast to INT16)", ac, (t_int16) integer_);
		      } else if (cType == pcode__LONG){
  		  		v->setInt16(identifier, (t_int16) long_, offset);
	  				if (!bSilent) sprintf(acStringOutputBuffer, "%s = %d (warning lost precision: auto-cast to INT16)", ac, (t_int16) long_);

  	   	  } else if (cType == pcode__SINGLE){
    				v->setInt16(identifier, (t_int16) floor(single_), offset);
  					if (!bSilent) sprintf(acStringOutputBuffer, "%s = %d (warning lost precision: auto-cast to INT16)", ac, (t_int16) single_);
          } else if (cType == pcode__DOUBLE){
    				v->setInt16(identifier, (t_int16) floor(double_), offset);
  					if (!bSilent) sprintf(acStringOutputBuffer, "%s = %d (warning lost precision: auto-cast to INT16)", ac, (t_int16) double_);
  	   	  
		      } else if (cType == pcode__INT16){
  		  		v->setInt16(identifier, (t_int16) int16_, offset);
	  				if (!bSilent) sprintf(acStringOutputBuffer, "%s = %d", ac, (t_int16) int16_);
		      } else if (cType == pcode__INT32){
  		  		v->setInt16(identifier, (t_int16) int32_, offset);
	  				if (!bSilent) sprintf(acStringOutputBuffer, "%s = %d (warning lost precision: auto-cast to INT16)", ac, (t_int16) int32_);
		      } else if (cType == pcode__INT64){
  		  		v->setInt16(identifier, (t_int16) int64_, offset);
	  				if (!bSilent) sprintf(acStringOutputBuffer, "%s = %d (warning lost precision: auto-cast to INT16)", ac, (t_int16) int64_);
		      } else if (cType == pcode__UINT16){
  		  		v->setInt16(identifier, (t_int16) uint16_, offset);
	  				if (!bSilent) sprintf(acStringOutputBuffer, "%s = %d (warning lost precision: auto-cast to INT16)", ac, (t_int16) uint16_);
		      } else if (cType == pcode__UINT32){
  		  		v->setInt16(identifier, (t_int16) uint32_, offset);
	  				if (!bSilent) sprintf(acStringOutputBuffer, "%s = %d (warning lost precision: auto-cast to INT16)", ac, (t_int16) uint32_);
		      } else if (cType == pcode__UINT64){
  		  		v->setInt16(identifier, (t_int16) uint64_, offset);
	  				if (!bSilent) sprintf(acStringOutputBuffer, "%s = %d (warning lost precision: auto-cast to INT16)", ac, (t_int16) uint64_);

          } else if (cType == pcode__CURRENCY){
    				v->setInt16(identifier, currency_.toInt16(), offset); 
  					if (!bSilent) sprintf(acStringOutputBuffer, "%s = %d (warning lost precision: auto-cast to INT16)", ac, (t_int16) currency_.toInt16());

          } else {
            runtimeError("Cast exception");
            goto er;
          }
					break;
        case pcode__INT32: 

          if (cType == pcode__BOOLEAN){
    				v->setInt32(identifier, (t_int32) boolean_, offset);
  					if (!bSilent) sprintf(acStringOutputBuffer, "%s = %d (auto-cast to INT32)", ac, (t_int32) boolean_);

          } else if (cType == pcode__BYTE){
    				v->setInt32(identifier, (t_int32) byte_, offset);
  					if (!bSilent) sprintf(acStringOutputBuffer, "%s = %d (auto-cast to INT32)", ac, (t_int32) byte_);
          } else if (cType == pcode__SHORT){
    				v->setInt32(identifier, (t_int32) short_, offset);
  					if (!bSilent) sprintf(acStringOutputBuffer, "%s = %d (auto-cast to INT32)", ac, (t_int32) short_);
          } else if (cType == pcode__INTEGER){
    				v->setInt32(identifier, (t_int32) integer_, offset);
  					if (!bSilent) sprintf(acStringOutputBuffer, "%s = %d (auto-cast to INT32)", ac, (t_int32) integer_);
		      } else if (cType == pcode__LONG){
  		  		v->setInt32(identifier, (t_int32) long_, offset);
	  				if (!bSilent) sprintf(acStringOutputBuffer, "%s = %d (warning lost precision: auto-cast to INT32)", ac, (t_int32) long_);

  	   	  } else if (cType == pcode__SINGLE){
    				v->setInt32(identifier, (t_int32) floor(single_), offset);
  					if (!bSilent) sprintf(acStringOutputBuffer, "%s = %d (warning lost precision: auto-cast to INT32)", ac, (t_int32) single_);
          } else if (cType == pcode__DOUBLE){
    				v->setInt32(identifier, (t_int32) floor(double_), offset);
  					if (!bSilent) sprintf(acStringOutputBuffer, "%s = %d (warning lost precision: auto-cast to INT32)", ac, (t_int32) double_);
  	   	  
		      } else if (cType == pcode__INT16){
  		  		v->setInt32(identifier, (t_int32) int16_, offset);
	  				if (!bSilent) sprintf(acStringOutputBuffer, "%s = %d (auto-cast to INT32)", ac, (t_int32) int16_);
		      } else if (cType == pcode__INT32){
  		  		v->setInt32(identifier, (t_int32) int32_, offset);
	  				if (!bSilent) sprintf(acStringOutputBuffer, "%s = %d", ac, (t_int32) int32_);
		      } else if (cType == pcode__INT64){
  		  		v->setInt32(identifier, (t_int32) int64_, offset);
	  				if (!bSilent) sprintf(acStringOutputBuffer, "%s = %d (warning lost precision: auto-cast to INT32)", ac, (t_int32) int64_);
		      } else if (cType == pcode__UINT16){
  		  		v->setInt32(identifier, (t_int32) uint16_, offset);
	  				if (!bSilent) sprintf(acStringOutputBuffer, "%s = %d (warning lost precision: auto-cast to INT32)", ac, (t_int32) uint16_);
		      } else if (cType == pcode__UINT32){
  		  		v->setInt32(identifier, (t_int32) uint32_, offset);
	  				if (!bSilent) sprintf(acStringOutputBuffer, "%s = %d (warning lost precision: auto-cast to INT32)", ac, (t_int32) uint32_);
		      } else if (cType == pcode__UINT64){
  		  		v->setInt32(identifier, (t_int32) uint64_, offset);
	  				if (!bSilent) sprintf(acStringOutputBuffer, "%s = %d (warning lost precision: auto-cast to INT32)", ac, (t_int32) uint64_);

          } else if (cType == pcode__CURRENCY){
    				v->setInt32(identifier, currency_.toInt32(), offset); 
  					if (!bSilent) sprintf(acStringOutputBuffer, "%s = %d (warning lost precision: auto-cast to INT32)", ac, (t_int32) currency_.toInt32());

          } else {
            runtimeError("Cast exception");
            goto er;
          }
					break;
        case pcode__INT64: 

          if (cType == pcode__BOOLEAN){
    				v->setInt64(identifier, (t_long) boolean_, offset);
  					if (!bSilent) sprintf(acStringOutputBuffer, "%s = %I64d (auto-cast to INT64)", ac, (t_long) boolean_);

          } else if (cType == pcode__BYTE){
    				v->setInt64(identifier, (t_long) byte_, offset);
  					if (!bSilent) sprintf(acStringOutputBuffer, "%s = %I64d (auto-cast to INT64)", ac, (t_long) byte_);
          } else if (cType == pcode__SHORT){
    				v->setInt64(identifier, (t_long) short_, offset);
  					if (!bSilent) sprintf(acStringOutputBuffer, "%s = %I64d (auto-cast to INT64)", ac, (t_long) short_);
          } else if (cType == pcode__INTEGER){
    				v->setInt64(identifier, (t_long) integer_, offset);
  					if (!bSilent) sprintf(acStringOutputBuffer, "%s = %I64d (auto-cast to INT64)", ac, (t_long) integer_);
		      } else if (cType == pcode__LONG){
  		  		v->setInt64(identifier, (t_long) long_, offset);
	  				if (!bSilent) sprintf(acStringOutputBuffer, "%s = %I64d  (auto-cast to INT64)", ac, (t_long) long_);

  	   	  } else if (cType == pcode__SINGLE){
    				v->setInt64(identifier, (t_long) floor(single_), offset);
  					if (!bSilent) sprintf(acStringOutputBuffer, "%s = %I64d (warning lost precision: auto-cast to INT64)", ac, (t_long) single_);
          } else if (cType == pcode__DOUBLE){
    				v->setInt64(identifier, (t_long) floor(double_), offset);
  					if (!bSilent) sprintf(acStringOutputBuffer, "%s = %I64d (warning lost precision: auto-cast to INT64)", ac, (t_long) double_);
  	   	  
		      } else if (cType == pcode__INT16){
  		  		v->setInt64(identifier, (t_long) int16_, offset);
	  				if (!bSilent) sprintf(acStringOutputBuffer, "%s = %I64d (auto-cast to INT64)", ac, (t_long) int16_);
		      } else if (cType == pcode__INT32){
  		  		v->setInt64(identifier, (t_long) int32_, offset);
	  				if (!bSilent) sprintf(acStringOutputBuffer, "%s = %I64d (auto-cast to INT64)", ac, (t_long) int32_);
		      } else if (cType == pcode__INT64){
  		  		v->setInt64(identifier, (t_long) int64_, offset);
	  				if (!bSilent) sprintf(acStringOutputBuffer, "%s = %I64d", ac, (t_long) int64_);
		      } else if (cType == pcode__UINT16){
  		  		v->setInt64(identifier, (t_long) uint16_, offset);
	  				if (!bSilent) sprintf(acStringOutputBuffer, "%s = %I64d (warning lost precision: auto-cast to INT64)", ac, (t_long) uint16_);
		      } else if (cType == pcode__UINT32){
  		  		v->setInt64(identifier, (t_long) uint32_, offset);
	  				if (!bSilent) sprintf(acStringOutputBuffer, "%s = %I64d (warning lost precision: auto-cast to INT64)", ac, (t_long) uint32_);
		      } else if (cType == pcode__UINT64){
  		  		v->setInt64(identifier, (t_long) uint64_, offset);
	  				if (!bSilent) sprintf(acStringOutputBuffer, "%s = %I64d (warning lost precision: auto-cast to INT64)", ac, (t_long) uint64_);

          } else if (cType == pcode__CURRENCY){
    				v->setInt64(identifier, currency_.toInt64(), offset); 
  					if (!bSilent) sprintf(acStringOutputBuffer, "%s = %I64d (warning lost precision: auto-cast to INT64)", ac, (t_long) currency_.toInt64());

          } else {
            runtimeError("Cast exception");
            goto er;
          }
					break;
        case pcode__UINT16: 

          if (cType == pcode__BOOLEAN){
    				v->setUInt16(identifier, (t_uint16) boolean_, offset);
  					if (!bSilent) sprintf(acStringOutputBuffer, "%s = %d (auto-cast to UINT16)", ac, (t_uint16) boolean_);

          } else if (cType == pcode__BYTE){
    				v->setUInt16(identifier, (t_uint16) byte_, offset);
  					if (!bSilent) sprintf(acStringOutputBuffer, "%s = %d (auto-cast to UINT16)", ac, (t_uint16) byte_);
          } else if (cType == pcode__SHORT){
    				v->setUInt16(identifier, (t_uint16) short_, offset);
  					if (!bSilent) sprintf(acStringOutputBuffer, "%s = %d (warning lost precision: auto-cast to UINT16)", ac, (t_uint16) short_);
          } else if (cType == pcode__INTEGER){
    				v->setUInt16(identifier, (t_uint16) integer_, offset);
  					if (!bSilent) sprintf(acStringOutputBuffer, "%s = %d (warning lost precision: auto-cast to UINT16)", ac, (t_uint16) integer_);
		      } else if (cType == pcode__LONG){
  		  		v->setUInt16(identifier, (t_uint16) long_, offset);
	  				if (!bSilent) sprintf(acStringOutputBuffer, "%s = %d (warning lost precision: auto-cast to UINT16)", ac, (t_uint16) long_);

  	   	  } else if (cType == pcode__SINGLE){
    				v->setUInt16(identifier, (t_uint16) floor(single_), offset);
  					if (!bSilent) sprintf(acStringOutputBuffer, "%s = %d (warning lost precision: auto-cast to UINT16)", ac, (t_uint16) single_);
          } else if (cType == pcode__DOUBLE){
    				v->setUInt16(identifier, (t_uint16) floor(double_), offset);
  					if (!bSilent) sprintf(acStringOutputBuffer, "%s = %d (warning lost precision: auto-cast to UINT16)", ac, (t_uint16) double_);
  	   	  
		      } else if (cType == pcode__INT16){
  		  		v->setUInt16(identifier, (t_uint16) int16_, offset);
	  				if (!bSilent) sprintf(acStringOutputBuffer, "%s = %d (warning lost precision: auto-cast to UINT16)", ac, (t_uint16) int16_);
		      } else if (cType == pcode__INT32){
  		  		v->setUInt16(identifier, (t_uint16) int32_, offset);
	  				if (!bSilent) sprintf(acStringOutputBuffer, "%s = %d (warning lost precision: auto-cast to UINT16)", ac, (t_uint16) int32_);
		      } else if (cType == pcode__INT64){
  		  		v->setUInt16(identifier, (t_uint16) int64_, offset);
	  				if (!bSilent) sprintf(acStringOutputBuffer, "%s = %d (warning lost precision: auto-cast to UINT16)", ac, (t_uint16) int64_);
		      } else if (cType == pcode__UINT16){
  		  		v->setUInt16(identifier, (t_uint16) uint16_, offset);
	  				if (!bSilent) sprintf(acStringOutputBuffer, "%s = %d", ac, (t_uint16) uint16_);
		      } else if (cType == pcode__UINT32){
  		  		v->setUInt16(identifier, (t_uint16) uint32_, offset);
	  				if (!bSilent) sprintf(acStringOutputBuffer, "%s = %d (warning lost precision: auto-cast to UINT16)", ac, (t_uint16) uint32_);
		      } else if (cType == pcode__UINT64){
  		  		v->setUInt16(identifier, (t_uint16) uint64_, offset);
	  				if (!bSilent) sprintf(acStringOutputBuffer, "%s = %d (warning lost precision: auto-cast to UINT16)", ac, (t_uint16) uint64_);

          } else if (cType == pcode__CURRENCY){
    				v->setUInt16(identifier, currency_.toUInt16(), offset); 
  					if (!bSilent) sprintf(acStringOutputBuffer, "%s = %d (warning lost precision: auto-cast to UINT16)", ac, (t_uint16) currency_.toUInt16());

          } else {
            runtimeError("Cast exception");
            goto er;
          }
					break;
        case pcode__UINT32: 

          if (cType == pcode__BOOLEAN){
    				v->setUInt32(identifier, (t_uint32) boolean_, offset);
  					if (!bSilent) sprintf(acStringOutputBuffer, "%s = %I32u (auto-cast to UINT32)", ac, (t_uint32) boolean_);

          } else if (cType == pcode__BYTE){
    				v->setUInt32(identifier, (t_uint32) byte_, offset);
  					if (!bSilent) sprintf(acStringOutputBuffer, "%s = %I32u (auto-cast to UINT32)", ac, (t_uint32) byte_);
          } else if (cType == pcode__SHORT){
    				v->setUInt32(identifier, (t_uint32) short_, offset);
  					if (!bSilent) sprintf(acStringOutputBuffer, "%s = %I32u (auto-cast to UINT32)", ac, (t_uint32) short_);
          } else if (cType == pcode__INTEGER){
    				v->setUInt32(identifier, (t_uint32) integer_, offset);
  					if (!bSilent) sprintf(acStringOutputBuffer, "%s = %I32u (warning lost precision: auto-cast to UINT32)", ac, (t_uint32) integer_);
		      } else if (cType == pcode__LONG){
  		  		v->setUInt32(identifier, (t_uint32) long_, offset);
	  				if (!bSilent) sprintf(acStringOutputBuffer, "%s = %I32u (warning lost precision: auto-cast to UINT32)", ac, (t_uint32) long_);

  	   	  } else if (cType == pcode__SINGLE){
    				v->setUInt32(identifier, (t_uint32) floor(single_), offset);
  					if (!bSilent) sprintf(acStringOutputBuffer, "%s = %I32u (warning lost precision: auto-cast to UINT32)", ac, (t_uint32) single_);
          } else if (cType == pcode__DOUBLE){
    				v->setUInt32(identifier, (t_uint32) floor(double_), offset);
  					if (!bSilent) sprintf(acStringOutputBuffer, "%s = %I32u (warning lost precision: auto-cast to UINT32)", ac, (t_uint32) double_);
  	   	  
		      } else if (cType == pcode__INT16){
  		  		v->setUInt32(identifier, (t_uint32) int16_, offset);
	  				if (!bSilent) sprintf(acStringOutputBuffer, "%s = %I32u (auto-cast to UINT32)", ac, (t_uint32) int16_);
		      } else if (cType == pcode__INT32){
  		  		v->setUInt32(identifier, (t_uint32) int32_, offset);
	  				if (!bSilent) sprintf(acStringOutputBuffer, "%s = %I32u (warning lost precision: auto-cast to UINT32)", ac, (t_uint32) int32_);
		      } else if (cType == pcode__INT64){
  		  		v->setUInt32(identifier, (t_uint32) int64_, offset);
	  				if (!bSilent) sprintf(acStringOutputBuffer, "%s = %I32u (warning lost precision: auto-cast to UINT32)", ac, (t_uint32) int64_);
		      } else if (cType == pcode__UINT16){
  		  		v->setUInt32(identifier, (t_uint32) uint16_, offset);
	  				if (!bSilent) sprintf(acStringOutputBuffer, "%s = %I32u (auto-cast to UINT32)", ac, (t_uint32) uint16_);
		      } else if (cType == pcode__UINT32){
  		  		v->setUInt32(identifier, (t_uint32) uint32_, offset);
	  				if (!bSilent) sprintf(acStringOutputBuffer, "%s = %I32u", ac, (t_uint32) uint32_);
		      } else if (cType == pcode__UINT64){
  		  		v->setUInt32(identifier, (t_uint32) uint64_, offset);
	  				if (!bSilent) sprintf(acStringOutputBuffer, "%s = %I32u (warning lost precision: auto-cast to UINT32)", ac, (t_uint32) uint64_);
          
          } else if (cType == pcode__CURRENCY){
    				v->setUInt32(identifier, currency_.toUInt32(), offset); 
  					if (!bSilent) sprintf(acStringOutputBuffer, "%s = %I32u (warning lost precision: auto-cast to UINT32)", ac, (t_uint32) currency_.toUInt32());

          } else {
            runtimeError("Cast exception");
            goto er;
          }
					break;
        case pcode__UINT64: 

          if (cType == pcode__BOOLEAN){
    				v->setUInt64(identifier, (t_uint64) boolean_, offset);
  					if (!bSilent) sprintf(acStringOutputBuffer, "%s = %I64u (auto-cast to UINT64)", ac, (t_uint64) boolean_);

          } else if (cType == pcode__BYTE){
    				v->setUInt64(identifier, (t_uint64) byte_, offset);
  					if (!bSilent) sprintf(acStringOutputBuffer, "%s = %I64u (auto-cast to UINT64)", ac, (t_uint64) byte_);
          } else if (cType == pcode__SHORT){
    				v->setUInt64(identifier, (t_uint64) short_, offset);
  					if (!bSilent) sprintf(acStringOutputBuffer, "%s = %I64u (auto-cast to UINT64)", ac, (t_uint64) short_);
          } else if (cType == pcode__INTEGER){
    				v->setUInt64(identifier, (t_uint64) integer_, offset);
  					if (!bSilent) sprintf(acStringOutputBuffer, "%s = %I64u (auto-cast to UINT64)", ac, (t_uint64) integer_);
		      } else if (cType == pcode__LONG){
  		  		v->setUInt64(identifier, (t_uint64) long_, offset);
	  				if (!bSilent) sprintf(acStringOutputBuffer, "%s = %I64u (warning lost precision: auto-cast to UINT64)", ac, (t_uint64) long_);

  	   	  } else if (cType == pcode__SINGLE){
    				v->setUInt64(identifier, (t_uint64) floor(single_), offset);
  					if (!bSilent) sprintf(acStringOutputBuffer, "%s = %I64u (warning lost precision: auto-cast to UINT64)", ac, (t_uint64) single_);
          } else if (cType == pcode__DOUBLE){
    				v->setUInt64(identifier, (t_uint64) floor(double_), offset);
  					if (!bSilent) sprintf(acStringOutputBuffer, "%s = %I64u (warning lost precision: auto-cast to UINT64)", ac, (t_uint64) double_);
  	   	  
		      } else if (cType == pcode__INT16){
  		  		v->setUInt64(identifier, (t_uint64) int16_, offset);
	  				if (!bSilent) sprintf(acStringOutputBuffer, "%s = %I64u (auto-cast to UINT64)", ac, (t_uint64) int16_);
		      } else if (cType == pcode__INT32){
  		  		v->setUInt64(identifier, (t_uint64) int32_, offset);
	  				if (!bSilent) sprintf(acStringOutputBuffer, "%s = %I64u (warning lost precision: auto-cast to UINT64)", ac, (t_uint64) int32_);
		      } else if (cType == pcode__INT64){
  		  		v->setUInt64(identifier, (t_uint64) int64_, offset);
	  				if (!bSilent) sprintf(acStringOutputBuffer, "%s = %I64u (warning lost precision: auto-cast to UINT64)", ac, (t_uint64) int64_);
		      } else if (cType == pcode__UINT16){
  		  		v->setUInt64(identifier, (t_uint64) uint16_, offset);
	  				if (!bSilent) sprintf(acStringOutputBuffer, "%s = %I64u (auto-cast to UINT64)", ac, (t_uint64) uint16_);
		      } else if (cType == pcode__UINT32){
  		  		v->setUInt64(identifier, (t_uint64) uint32_, offset);
	  				if (!bSilent) sprintf(acStringOutputBuffer, "%s = %I64u (auto-cast to UINT64)", ac, (t_uint32) uint32_);
		      } else if (cType == pcode__UINT64){
  		  		v->setUInt64(identifier, (t_uint64) uint64_, offset);
	  				if (!bSilent) sprintf(acStringOutputBuffer, "%s = %I64u (warning lost precision: auto-cast to UINT64)", ac, (t_uint64) uint64_);

          } else if (cType == pcode__CURRENCY){
    				v->setUInt64(identifier, currency_.toUInt64(), offset); 
  					if (!bSilent) sprintf(acStringOutputBuffer, "%s = %I64u (warning lost precision: auto-cast to UINT64)", ac, (t_uint64) currency_.toUInt64());

          } else {
            runtimeError("Cast exception");
            goto er;
          }
					break;*/

				case pcode__ANY: // ANY
          if (cType == pcode__INTEGER){
  		  		v->setInteger(identifier, integer_, offset);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%s = &H%X (Address)", ac, integer_);
#endif

          } else {
            runtimeError("Cast exception");
            goto er;
		      }
					break;

        case pcode__VARIANT: 

          if (cType == pcode__BOOLEAN){
    				v->setVariant_Boolean(identifier, boolean_, offset);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%s = %d", ac, (t_integer) boolean_);
#endif
          } else if (cType == pcode__QSTRING){
    				v->setVariant_QString(identifier, qstring_, offset);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%s = Unicode", ac);
#endif          
          } else if (cType == pcode__CSTRING || cType == pcode__LCSTRING){
    				v->setVariant_CString(identifier, cstring_, offset);
#ifdef HAS_CONSOLE
            if (!bSilent && strlen(cstring_) > 30){ sprintf(acStringOutputBuffer, "%s = \"%-30.30s...\"", ac, cstring_); }
						else if (!bSilent) sprintf(acStringOutputBuffer, "%s = \"%-30.30s\"", ac, cstring_);
#endif
          } else if (cType == pcode__BYTE){
    				v->setVariant_Byte(identifier, byte_, offset);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%s = %d", ac, (t_integer) byte_);
#endif
          } else if (cType == pcode__SHORT){
    				v->setVariant_Short(identifier, short_, offset);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%s = %d", ac, (t_integer) short_);
#endif
          } else if (cType == pcode__INTEGER){
    				v->setVariant_Integer(identifier, integer_, offset);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%s = %d", ac, (t_integer) integer_);
#endif
          } else if (cType == pcode__LONG){
  		  		v->setVariant_Long(identifier, long_, offset);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%s = %I64d", ac, long_);
#endif
  	   	  } else if (cType == pcode__SINGLE){
    				v->setVariant_Single(identifier, single_, offset);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%s = %.6f", ac, single_);
#endif
          } else if (cType == pcode__DOUBLE){
    				v->setVariant_Double(identifier, double_, offset);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%s = %.6f", ac, double_);
#endif

          } else if (cType == pcode__CURRENCY){
    				v->setVariant_Currency(identifier, currency_, offset); 
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%s = %s", ac, currency_.toCString());
#endif
          } else if (cType == pcode__DATE){
    				v->setVariant_Date(identifier, date_, offset); 
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%s = %s", ac, date_.toCString());
#endif
          } else if (cType == pcode__OBJECT){

            memory_variable2 *oldObject_;
            oldObject_ = (memory_variable2 *) v->getVariant_Object(identifier, offset);             
      		   v->setVariant_Object(identifier, object_, offset);
#ifdef HAS_CONSOLE
            if (!bSilent){
               if (!bSilent) sprintf(acStringOutputBuffer, "%s = &H%X (Object)", ac, object_);

               CONSOLE pcodePrintVar(acModule, acSub, acVar);
	             CONSOLE pcodePrint(acStringOutputBuffer);
		           CONSOLE pcodePrintCR();
            }
#endif
            myGc->inc((memory_variable2 *) object_); // gc
            myGc->dec(oldObject_); // gc

		      } else if (cType == pcode__EMPTY){ // Dim v As Variant : v = Empty 
  		  		v->setVariant_Empty(identifier, pcode__EMPTY, offset);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%s = Empty", acVar);
#endif
          } else if (cType == pcode__ERROR){
    				v->setVariant_Error(identifier, integer_, offset);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%s = %d", ac, (t_integer) integer_);
#endif
          } else {
            runtimeError("Cast exception");
            goto er;
          }
					break;

				case pcode__CURRENCY:

          if (cType == pcode__BOOLEAN){
    				v->setCurrency(identifier, (t_long) boolean_ ? -1 : 0, offset);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%s = %I64d (auto-cast to Currency)", ac, (t_long) boolean_ ? -1 : 0);
#endif
          } else if (cType == pcode__BYTE){
    				v->setCurrency(identifier, (t_long) byte_, offset);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%s = %I64d (auto-cast to Currency)", ac, (t_long) byte_);
#endif
          } else if (cType == pcode__SHORT){
    				v->setCurrency(identifier, (t_long) short_, offset);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%s = %I64d (auto-cast to Currency)", ac, (t_long) short_);
#endif
          } else if (cType == pcode__INTEGER){
    				v->setCurrency(identifier, (t_long) integer_, offset);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%s = %I64d (auto-cast to Currency)", ac, (t_long) integer_);
#endif
          } else if (cType == pcode__LONG){
  		  		v->setCurrency(identifier, (t_long) long_, offset);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%s = %I64d  (auto-cast to Currency)", ac, (t_long) long_);
#endif
  	   	  } else if (cType == pcode__SINGLE){
    				v->setCurrencyDouble(identifier, (t_double) single_, offset);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%s = %s (warning lost precision: auto-cast to Currency)", ac, (v->getCurrency(identifier, offset)).toCString());
#endif
          } else if (cType == pcode__DOUBLE){
    				v->setCurrencyDouble(identifier, (t_double) double_, offset);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%s = %s (warning lost precision: auto-cast to Currency)", ac, (v->getCurrency(identifier, offset)).toCString());
#endif
            /*
		      } else if (cType == pcode__INT16){
  		  		v->setCurrency(identifier, (t_long) int16_, offset);
	  				if (!bSilent) sprintf(acStringOutputBuffer, "%s = %I64d (auto-cast to Currency)", ac, (t_long) int16_);
		      } else if (cType == pcode__INT32){
  		  		v->setCurrency(identifier, (t_long) int32_, offset);
	  				if (!bSilent) sprintf(acStringOutputBuffer, "%s = %I64d (auto-cast to Currency)", ac, (t_long) int32_);
		      } else if (cType == pcode__INT64){
  		  		v->setCurrency(identifier, (t_long) int64_, offset);
	  				if (!bSilent) sprintf(acStringOutputBuffer, "%s = %I64d", ac, (t_long) int64_);
		      } else if (cType == pcode__UINT16){
  		  		v->setCurrency(identifier, (t_long) uint16_, offset);
	  				if (!bSilent) sprintf(acStringOutputBuffer, "%s = %I64d (warning lost precision: auto-cast to Currency)", ac, (t_long) uint16_);
		      } else if (cType == pcode__UINT32){
  		  		v->setCurrency(identifier, (t_long) uint32_, offset);
	  				if (!bSilent) sprintf(acStringOutputBuffer, "%s = %I64d (warning lost precision: auto-cast to Currency)", ac, (t_long) uint32_);
		      } else if (cType == pcode__UINT64){
  		  		v->setCurrency(identifier, (t_long) uint64_, offset);
	  				if (!bSilent) sprintf(acStringOutputBuffer, "%s = %I64d (warning lost precision: auto-cast to Currency)", ac, (t_long) uint64_);
*/
          } else if (cType == pcode__CURRENCY){
    				v->setCurrency(identifier, currency_, offset); 
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%s = %s", ac, currency_.toCString());
#endif
          } else {
            runtimeError("Cast exception");
            goto er;
          }										
					break;
				case pcode__DATE:

          if (cType == pcode__QSTRING){
            t_date d(qstring_);
    				v->setDate(identifier, d, offset); 
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%s = Unicode", ac);
#endif
          } else if (cType == pcode__CSTRING || cType == pcode__LCSTRING){
            t_date d(cstring_);
    				v->setDate(identifier, d, offset); 
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%s = %s (auto-cast to Date)", ac, cstring_);
#endif
          } else if (cType == pcode__DATE){
    				v->setDate(identifier, date_, offset); 
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "%s = %s", ac, date_.toCString());
#endif
          } else {
            runtimeError("Cast exception");
            goto er;
          }										
					break;
        
        default: // error
er: // error
					// 
					break;
			}
			}

		}

    if (nestatics) estatics->undeclare(nestatics);

#ifdef HAS_CONSOLE
    if (!bSilent){
      if (interpretPcode()){
        CONSOLE pcodePrintVar(acModule, acSub, acVar);
	      CONSOLE pcodePrint(acStringOutputBuffer);
		    CONSOLE pcodePrintCR();
      }
    }
#endif
	} // } else return pcodeError(utility::con(pcode::pcode_(cMov), " missing"));
	
}

void interpreter::fMOV_ISMISSING()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif

	t_builtin c; t_integer identifier; t_scope scope;

	myPcode->rd_MOV_ISMISSING(&c, &identifier, &scope);
  {

#ifdef HAS_CONSOLE
    if (!bSilent){
   		const char *acModule, *acSub, *acVar;
   		acModule = ""; acSub = ""; acVar = "";

      findVars(identifier, &acModule, &acSub, &acVar);

      CONSOLE pcodePrintSep("");
      CONSOLE pcodePrintPos(nPos);
      CONSOLE pcodePrintOpc(pcode::pcode_(pcode__MOV_ISMISSING));
        
      static char ac[1024];
      sprintf(ac, "%X::", getVar(scope));
      CONSOLE pcodePrint(ac);
	    CONSOLE pcodePrintVar(acModule, acSub, acVar);
      CONSOLE pcodePrintCR();
    }
#endif
    

    {
  		getVar(scope)->setIsMissing(identifier, true);
    }

		
	} // } else return pcodeError(utility::con(pcode::pcode_(pcode__MOV_ISMISSING), " missing"));
}