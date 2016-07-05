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

extern QMap<QString,QString>trs;

void interpreter::fEQUAL()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


	t_pcode equal; t_boolean remove;

	myPcode->rd_EQUAL(&equal, &remove);
  {

#ifdef HAS_CONSOLE
		if (!bSilent) info3(nPos, pcode__EQUAL);
#endif
		{
      operate(pcode__EQUAL, remove); // 
		}

	} // } else return pcodeError(utility::con(pcode::pcode_(pcode__EQUAL), " missing"));

	return;
}

void interpreter::fLIKE()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


	t_pcode like; t_boolean remove; t_boolean bOptionComparyBinary;

	myPcode->rd_LIKE(&like, &remove, &bOptionComparyBinary);
  {

#ifdef HAS_CONSOLE
		if (!bSilent) info3(nPos, pcode__LIKE);
#endif
		{
      operate(pcode__LIKE, remove);
		}

	} // } else return pcodeError(utility::con(pcode::pcode_(pcode__LIKE), " missing"));

	return;
}

void interpreter::fIS()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


	t_pcode is; t_boolean remove;

	myPcode->rd_IS(&is, &remove);
  {

#ifdef HAS_CONSOLE
		if (!bSilent) info3(nPos, pcode__IS);
#endif
		{
      operate(pcode__IS, remove); // 
		}

	} // } else return pcodeError(utility::con(pcode::pcode_(pcode__IS), " missing"));

	return;
}

void interpreter::fUNEQUAL()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


	t_pcode unequal; t_boolean remove;

	myPcode->rd_UNEQUAL(&unequal, &remove);
  {

#ifdef HAS_CONSOLE
		if (!bSilent) info3(nPos, pcode__UNEQUAL);
#endif
		{
      operate(pcode__UNEQUAL, remove);
		}

	} // } else return pcodeError(utility::con(pcode::pcode_(pcode__UNEQUAL), " missing"));

	return;
}

void interpreter::fGREATER()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


	t_pcode greater; t_boolean remove;

	myPcode->rd_GREATER(&greater, &remove);
  {

#ifdef HAS_CONSOLE
		if (!bSilent) info3(nPos, pcode__GREATER);
#endif
		{
      operate(pcode__GREATER, remove);
		}

	} // } else return pcodeError(utility::con(pcode::pcode_(pcode__GREATER), " missing"));

	return;
}

void interpreter::fLESSER()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


	t_pcode lesser; t_boolean remove;

	myPcode->rd_LESSER(&lesser, &remove);
  {

#ifdef HAS_CONSOLE
		if (!bSilent) info3(nPos, pcode__LESSER);
#endif
		{
      operate(pcode__LESSER, remove);
		}

	} // } else return pcodeError(utility::con(pcode::pcode_(pcode__LESSER), " missing"));

	return;
}

void interpreter::fGREATER_EQUAL()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


	t_pcode greater_equal; t_boolean remove;

	myPcode->rd_GREATER_EQUAL(&greater_equal, &remove);
  {

#ifdef HAS_CONSOLE
		if (!bSilent) info3(nPos, pcode__GREATER_EQUAL);
#endif
		{
      operate(pcode__GREATER_EQUAL, remove);
		}

	} // } else return pcodeError(utility::con(pcode::pcode_(pcode__GREATER_EQUAL), " missing"));

	return;
}

void interpreter::fFOR_GREATER_EQUAL()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


	t_pcode c; t_boolean remove;

	myPcode->rd_FOR_GREATER_EQUAL(&c, &remove);
  {

#ifdef HAS_CONSOLE
		if (!bSilent) info3(nPos, pcode__FOR_GREATER_EQUAL);
#endif
		{
      operate(pcode__FOR_GREATER_EQUAL, remove);    
		}

	} // } else return pcodeError(utility::con(pcode::pcode_(pcode__FOR_GREATER_EQUAL), " missing"));

	return;
}

void interpreter::fLESSER_EQUAL()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


	t_pcode lesser_equal; t_boolean remove;

	myPcode->rd_LESSER_EQUAL(&lesser_equal, &remove);
  {

#ifdef HAS_CONSOLE
		if (!bSilent) info3(nPos, pcode__LESSER_EQUAL);
#endif
		{
      operate(pcode__LESSER_EQUAL, remove);
		}

	} // } else return pcodeError(utility::con(pcode::pcode_(pcode__LESSER_EQUAL), " missing"));

	return;
}

void interpreter::fXOR()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


	t_pcode xor_;

	myPcode->rd_XOR(&xor_);
  {

#ifdef HAS_CONSOLE
		if (!bSilent) info3(nPos, pcode__XOR);
#endif
		{
      operate(pcode__XOR);
		}

	} // } else return pcodeError(utility::con(pcode::pcode_(pcode__XOR), " missing"));

	return;
}

void interpreter::fIMP()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_pcode imp_;

	myPcode->rd_IMP(&imp_);
  {

#ifdef HAS_CONSOLE
		if (!bSilent) info3(nPos, pcode__IMP);
#endif
		{
      operate(pcode__IMP);
		}

	} // } else return pcodeError(utility::con(pcode::pcode_(pcode__IMP), " missing"));

	return;
}

void interpreter::fEQV()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_pcode c;

	myPcode->rd_EQV(&c);
  {

#ifdef HAS_CONSOLE
		if (!bSilent) info3(nPos, pcode__EQV);
#endif
		{
      operate(pcode__EQV);
		}

	} // } else return pcodeError(utility::con(pcode::pcode_(pcode__EQV), " missing"));

	return;
}

void interpreter::fAND()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


	t_pcode and_;

	myPcode->rd_AND(&and_);
  {

#ifdef HAS_CONSOLE
		if (!bSilent) info3(nPos, pcode__AND);
#endif
		{
      operate(pcode__AND);
		}

	} // } else return pcodeError(utility::con(pcode::pcode_(pcode__AND), " missing"));

	return;
}

void interpreter::fOR()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


	t_pcode or_;

	myPcode->rd_OR(&or_);
  {

#ifdef HAS_CONSOLE
		if (!bSilent) info3(nPos, pcode__OR);
#endif
		{
      operate(pcode__OR);
		}

	} // } else return pcodeError(utility::con(pcode::pcode_(pcode__OR), " missing"));

	return;
}

void interpreter::fNOT()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


	t_pcode not_;

	myPcode->rd_NOT(&not_);
  {

#ifdef HAS_CONSOLE
		if (!bSilent) info3(nPos, pcode__NOT);
#endif
		{
      operate(pcode__NOT);
		}

	} // } else return pcodeError(utility::con(pcode::pcode_(pcode__NOT), " missing"));

	return;
}

void interpreter::fPOWER()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


	t_pcode exponent;

	myPcode->rd_POWER(&exponent);
  {

#ifdef HAS_CONSOLE
		if (!bSilent) info3(nPos, pcode__POWER);
#endif
		{
      operate(pcode__POWER);
		}

	} // } else return pcodeError(utility::con(pcode::pcode_(pcode__POWER), " missing"));

	return;
}

void interpreter::fMUL()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif



	t_pcode mul;

	myPcode->rd_MUL(&mul);
  {

#ifdef HAS_CONSOLE
		if (!bSilent) info3(nPos, pcode__MUL);
#endif
		{
      operate(pcode__MUL);
		}

	} // } else return pcodeError(utility::con(pcode::pcode_(pcode__MUL), " missing"));

	return;
}

void interpreter::fDIV()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif



	t_pcode div;

	myPcode->rd_DIV(&div);
  {

#ifdef HAS_CONSOLE
		if (!bSilent) info3(nPos, pcode__DIV);
#endif
		{
      operate(pcode__DIV);
		}

	} // } else return pcodeError(utility::con(pcode::pcode_(pcode__DIV), " missing"));

	return;
}

void interpreter::fIDIV()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif



	t_pcode idiv;

	myPcode->rd_IDIV(&idiv);
  {

#ifdef HAS_CONSOLE
		if (!bSilent) info3(nPos, pcode__IDIV);
#endif
		{
      operate(pcode__IDIV);
		}

	} // } else return pcodeError(utility::con(pcode::pcode_(pcode__IDIV), " missing"));

	return;
}

void interpreter::fMOD()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


	t_pcode mod;

	myPcode->rd_MOD(&mod);
  {

#ifdef HAS_CONSOLE
		if (!bSilent) info3(nPos, pcode__MOD);
#endif
		{
      operate(pcode__MOD);
		}

	} // } else return pcodeError(utility::con(pcode::pcode_(pcode__MOD), " missing"));

	return;
}

void interpreter::fADD()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif



	t_pcode add;

	myPcode->rd_ADD(&add);
  {

#ifdef HAS_CONSOLE
		if (!bSilent) info3(nPos, pcode__ADD);
#endif
		{
      operate(pcode__ADD);
		}

	} // } else return pcodeError(utility::con(pcode::pcode_(pcode__ADD), " missing"));

	return;
}

void interpreter::fSUB()
{
	#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif



	t_pcode sub;

	myPcode->rd_SUB(&sub);
  {

#ifdef HAS_CONSOLE
		if (!bSilent) info3(nPos, pcode__SUB);
#endif
		{
      operate(pcode__SUB);
		}

	} // } else return pcodeError(utility::con(pcode::pcode_(pcode__SUB), " missing"));

	return;
}

void interpreter::fPUSH_BYTE()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif



	t_pcode c; unsigned char byte;

	myPcode->rd_PUSH_BYTE(&c, &byte);
  {

#ifdef HAS_CONSOLE
		if (!bSilent) info(nPos, pcode__PUSH_BYTE, byte);
#endif
    

		{
      myStack->pushByte(byte);
    }

	} // } else return pcodeError(utility::con(pcode::pcode_(pcode__PUSH_BYTE), " missing"));

	return;
}

void interpreter::fPUSH_SHORT()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif



	t_pcode c; t_short m;

	myPcode->rd_PUSH_SHORT(&c, &m);
  {

#ifdef HAS_CONSOLE
		if (!bSilent) info(nPos, pcode__PUSH_SHORT, m);
#endif
    

		{
      myStack->pushShort(m);
    }

	} // } else return pcodeError(utility::con(pcode::pcode_(pcode__PUSH_SHORT), " missing"));

	return;
}

void interpreter::fPUSH_CURRENCY()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif



	t_pcode d; t_currency c;
	myPcode->rd_PUSH_CURRENCY(&d, &c);
  {

#ifdef HAS_CONSOLE
		if (!bSilent) info(nPos, pcode__PUSH_CURRENCY);
#endif
    

		{
       myStack->pushCurrency(c);
    }

	} // } else return pcodeError(utility::con(pcode::pcode_(pcode__PUSH_CURRENCY), " missing"));

	return;
}

void interpreter::fPUSH_DATE()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif



	t_pcode pushdate; t_date d;
	myPcode->rd_PUSH_DATE(&pushdate, &d);
  {

#ifdef HAS_CONSOLE
		if (!bSilent) info(nPos, pcode__PUSH_DATE);
#endif
    

		{
			 myStack->pushDate(d);
    }

	} // } else return pcodeError(utility::con(pcode::pcode_(pcode__PUSH_DATE), " missing"));

	return;
}

void interpreter::fPUSH_INTEGER()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif



	t_pcode pushi; t_integer integer;

	myPcode->rd_PUSH_INTEGER(&pushi, &integer);
  {

#ifdef HAS_CONSOLE
		if (!bSilent) info(nPos, pcode__PUSH_INTEGER, integer);
#endif
    
/*
    if (integer == 555){
      integer = integer;
    }*/
		{
      myStack->pushInteger(integer);
    }

	} // } else return pcodeError(utility::con(pcode::pcode_(pcode__PUSH_INTEGER), " missing"));

	return;
}

void interpreter::fPUSH_LONG()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif

	t_pcode pushl; t_long long_;

	myPcode->rd_PUSH_LONG(&pushl, &long_);
  {

#ifdef HAS_CONSOLE
		if (!bSilent) info(nPos, pcode__PUSH_LONG, long_);
#endif
    

		{
      myStack->pushLong(long_);
    }

	} // } else return pcodeError(utility::con(pcode::pcode_(pcode__PUSH_LONG), " missing"));

	return;
}

void interpreter::fPUSH_NULL()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif



	t_pcode c;

	myPcode->rd_PUSH_NULL(&c);
  {

#ifdef HAS_CONSOLE
		if (!bSilent) info(nPos, pcode__PUSH_NULL);
#endif
    

		{
      myStack->pushPointer(pcode__OBJECT, 0, true, false);
    }

	} // } else return pcodeError(utility::con(pcode::pcode_(pcode__PUSH_NULL), " missing"));

	return;
}

void interpreter::fPUSH_EMPTY()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif



	t_pcode c;

	myPcode->rd_PUSH_EMPTY(&c);
  {

#ifdef HAS_CONSOLE
		if (!bSilent) info(nPos, pcode__PUSH_EMPTY);
#endif
    

		{
      myStack->pushPCode(pcode__EMPTY);
    }

	} // } else return pcodeError(utility::con(pcode::pcode_(pcode__PUSH_EMPTY), " missing"));

	return;
}

void interpreter::fPUSH_ERROR()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif



	t_pcode c;

	myPcode->rd_PUSH_ERROR(&c);
  {

#ifdef HAS_CONSOLE
		if (!bSilent) info(nPos, pcode__PUSH_ERROR);
#endif
    

	{    
      myStack->pushError(nRuntimeErrorNo);
    }

	} // } else return pcodeError(utility::con(pcode::pcode_(pcode__PUSH_ERROR), " missing"));

	return;
}

void interpreter::fPUSH_BOOLEAN()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif



	t_pcode pushc; t_boolean boolean;

	myPcode->rd_PUSH_BOOLEAN(&pushc, &boolean);
  {

#ifdef HAS_CONSOLE
		if (!bSilent) info(nPos, pcode__PUSH_BOOLEAN, boolean);
#endif
    

		{
      myStack->pushBoolean(boolean);
    }

	} // } else return pcodeError(utility::con(pcode::pcode_(pcode__PUSH_BOOLEAN), " missing"));

	return;
}

void interpreter::fPUSH_QSTRING()
{
  static char ac[1024];
  t_cstring ac2;
  ac2 = "";

#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif



	t_pcode pushs; t_integer cstring;

	myPcode->rd_PUSH_QSTRING(&pushs, &cstring);
  {

#ifdef HAS_CONSOLE
    if (!bSilent){
      CONSOLE pcodePrintSep("");
	 	  CONSOLE pcodePrintPos(nPos);
		  CONSOLE pcodePrintOpc(pcode::pcode_(pcode__PUSH_QSTRING));
	    //CONSOLE pcodePrint(string);
		  //CONSOLE pcodePrint(",");

		  CONSOLE pcodePrint("\"");
    }
#endif


    
    ac2 = stringliterals->getName(cstring);
   

#ifdef HAS_CONSOLE
    if (!bSilent){
      if (strlen(ac2) > 20){
         sprintf(ac, "%-16.16s", ac2);
  	     CONSOLE pcodePrint(ac);
      } else {
 	      CONSOLE pcodePrint(ac2);
      }
		  CONSOLE pcodePrint("\"");
    }
#endif
		{
    
      QString s; s = s.fromUtf8(ac2);

      if (trs.contains(s)){
        QString ss = trs[s];
        if (!ss.isEmpty()) s = ss;

      }

      int nId = estatics->declare(pcode__QSTRING, 0, false, false);
      estatics->setQString(nId, &s, 0); 
      myStack->pushEQString(nId);
    

    }

#ifdef HAS_CONSOLE
    if (!bSilent){
		  CONSOLE pcodePrintCR();
    }
#endif

	} // } else return pcodeError(utility::con(pcode::pcode_(pcode__PUSH_STRING), " missing"));

	return;
}


void interpreter::fPUSH_CSTRING()
{
  static char ac[1024];
  t_cstring ac2;
  ac2 = "";

#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif



	t_pcode pushs; t_integer cstring;

	myPcode->rd_PUSH_CSTRING(&pushs, &cstring);
  {

#ifdef HAS_CONSOLE
    if (!bSilent){
      CONSOLE pcodePrintSep("");
	 	  CONSOLE pcodePrintPos(nPos);
		  CONSOLE pcodePrintOpc(pcode::pcode_(pcode__PUSH_CSTRING));
	    //CONSOLE pcodePrint(string);
		  //CONSOLE pcodePrint(",");

		  CONSOLE pcodePrint("\"");
    }
#endif


    
    ac2 = stringliterals->getName(cstring);




#ifdef HAS_CONSOLE
    if (!bSilent){
      if (strlen(ac2) > 20){
         sprintf(ac, "%-16.16s", ac2);
  	     CONSOLE pcodePrint(ac);
      } else {
 	      CONSOLE pcodePrint(ac2);
      }
		  CONSOLE pcodePrint("\"");
    }
#endif
		{
    
      myStack->pushCString(ac2);
    }

#ifdef HAS_CONSOLE
    if (!bSilent){
		  CONSOLE pcodePrintCR();
    }
#endif

	} // } else return pcodeError(utility::con(pcode::pcode_(pcode__PUSH_STRING), " missing"));

	return;
}

void interpreter::fPUSH_POINTERPOINTER()
{
  static char ac[1024];
  const char *ac2;
  ac2 = "";

#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif



	t_pcode c; 

	myPcode->rd_PUSH_POINTERPOINTER(&c);
  {

#ifdef HAS_CONSOLE
    if (!bSilent){
      CONSOLE pcodePrintSep("");
	 	  CONSOLE pcodePrintPos(nPos);
		  CONSOLE pcodePrintOpc(pcode::pcode_(pcode__PUSH_POINTERPOINTER));
	    //CONSOLE pcodePrint(string);
		  //CONSOLE pcodePrint(",");

		  CONSOLE pcodePrint("\"");
    }
#endif


#ifdef HAS_CONSOLE
    if (!bSilent){
		  CONSOLE pcodePrintCR();
    }
#endif

    bPushPointerPointer = true;

	} // } else return pcodeError(utility::con(pcode::pcode_(pcode__PUSH_POINTERPOINTER), " missing"));

	return;
}

void interpreter::fPUSH_CONST()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif



	t_pcode pushconst; t_integer identifier;

	myPcode->rd_PUSH_CONST(&pushconst, &identifier);
/*
  if (identifier == 0){
    identifier = identifier;
  }*/
  {

		int nVarType;
    nVarType = consts->type(identifier);

#ifdef HAS_CONSOLE
    if (!bSilent){

		  const char *acModule, *acSub, *acVar;
		  acModule = ""; acSub = ""; acVar = "";

		  findConsts(identifier, &acModule, &acSub, &acVar);

      CONSOLE pcodePrintSep("");
	 	  CONSOLE pcodePrintPos(nPos);
		  CONSOLE pcodePrintOpc(pcode::pcode_(pcode__PUSH_CONST));
	    CONSOLE pcodePrintVar(acModule, acSub, acVar);
		  CONSOLE pcodePrintCR();
    }
#endif
    

    t_boolean boolean_;// = 0;

    t_qstring qstring_;// = 0;
    t_cstring cstring_;// = 0;

    t_byte byte_;// = 0;
    t_short short_;// = 0;
    t_integer integer_;// = 0;
    t_long long_;// = 0;

    t_single single_;// = 0;
    t_double double_;// = 0;
/*
    t_int16 int16_;// = 0;
    t_int32 int32_;// = 0;
    t_int64 int64_;// = 0;
    t_uint16 uint16_;// = 0;
    t_uint32 uint32_;// = 0;
    t_uint64 uint64_;// = 0;*/

		int offset;
    offset = 0;
		//int nID;

		{

			switch(nVarType){
				case pcode__BOOLEAN: // BOOLEAN
					boolean_ = consts->getBoolean(identifier, offset);
		      myStack->pushBoolean(boolean_);
					break;

				case pcode__QSTRING: // STRING
					qstring_ = consts->getQString(identifier, offset);
		      myStack->pushQString(qstring_);
					break;

				case pcode__CSTRING: // STRING
					cstring_ = consts->getCString(identifier, offset);
		      myStack->pushCString(cstring_);
					break;

        case pcode__BYTE:
					byte_ = consts->getByte(identifier, offset);
		      myStack->pushByte(byte_);
					break;
        case pcode__SHORT: 
					short_ = consts->getShort(identifier, offset);
		      myStack->pushShort(short_);
					break;
        case pcode__INTEGER: // INTEGER
					integer_ = consts->getInteger(identifier, offset);
		      myStack->pushInteger(integer_);
					break;
        case pcode__LONG: // LONG
					long_ = consts->getLong(identifier, offset);
		      myStack->pushLong(long_);
					break;

        case pcode__SINGLE: // SINGLE
					single_ = consts->getSingle(identifier, offset);
		      myStack->pushSingle(single_);
					break;
				case pcode__DOUBLE: // DOUBLE
					double_ = consts->getDouble(identifier, offset);
		      myStack->pushDouble(double_);
					break;
/*
        case pcode__INT16: 
					int16_ = consts->getInt16(identifier, offset);
		      myStack->pushInt16(int16_);
					break;
        case pcode__INT32: 
					int32_ = consts->getInt32(identifier, offset);
		      myStack->pushInt32(int32_);
					break;
        case pcode__INT64: 
					int64_ = consts->getInt64(identifier, offset);
		      myStack->pushInt64(int64_);
					break;
        case pcode__UINT16: 
					uint16_ = consts->getUInt16(identifier, offset);
		      myStack->pushUInt16(uint16_);
					break;
        case pcode__UINT32: 
					uint32_ = consts->getUInt32(identifier, offset);
		      myStack->pushUInt32(uint32_);
					break;
        case pcode__UINT64: 
					uint64_ = consts->getUInt64(identifier, offset);
		      myStack->pushUInt64(uint64_);
					break;
*/
				default:
					pcodeError("wrong datatype of const");
          return;
					break;
			}
	  }

	} // } else return pcodeError(utility::con(pcode::pcode_(pcode__PUSH_CONST), " missing"));

	return;
}

void interpreter::fPUSH_ENUM()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif



	t_pcode c; t_integer identifier; t_integer element_id;
   
	myPcode->rd_PUSH_ENUM(&c, &identifier, &element_id);
  {


		int nVarType;
    nVarType = pcode__INTEGER;//myEnum->type(identifier);

#ifdef HAS_CONSOLE
    if (!bSilent){
      CONSOLE pcodePrintSep("");
	 	  CONSOLE pcodePrintPos(nPos);
		  CONSOLE pcodePrintOpc(pcode::pcode_(pcode__PUSH_ENUM));
		  CONSOLE pcodePrint(identifier);
  	  CONSOLE pcodePrint(findTypes(identifier));
		  CONSOLE pcodePrint(". ");
		  CONSOLE pcodePrint(element_id);
		  CONSOLE pcodePrint(findFieldInEnum(identifier, element_id));
		  CONSOLE pcodePrintCR();		
    }
#endif

		t_integer n;

		{

			switch(nVarType){
				case pcode__INTEGER: // INTEGER
					n = myEnum->getInteger(identifier, element_id);
		      myStack->pushInteger(n);
					break;
				default:
					pcodeError("wrong datatype of enum");
          return;
					break;
			}
	  }

	} // } else return pcodeError(utility::con(pcode::pcode_(pcode__PUSH_ENUM), " missing"));

	return;
}



void interpreter::fPUSH_DOUBLE()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif



	t_pcode pushd; t_double double_;

	myPcode->rd_PUSH_DOUBLE(&pushd, &double_);
  {

#ifdef HAS_CONSOLE
		if (!bSilent) info(nPos, pcode__PUSH_DOUBLE, double_);
#endif

		{
      myStack->pushDouble(double_);
    }

	} // } else return pcodeError(utility::con(pcode::pcode_(pcode__PUSH_DOUBLE), " missing"));

	return;
}

void interpreter::fPUSH_SINGLE()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif



	t_pcode pushf; t_single single_;

	myPcode->rd_PUSH_SINGLE(&pushf, &single_);
  {

#ifdef HAS_CONSOLE
		if (!bSilent) info(nPos, pcode__PUSH_SINGLE, single_);
#endif

		{
      myStack->pushSingle(single_);
    }

	} // } else return pcodeError(utility::con(pcode::pcode_(pcode__PUSH_SINGLE), " missing"));

	return;
}

void interpreter::fSTACKPOP()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif



	t_pcode c;
	myPcode->rd_STACKPOP(&c);
  {

		//if (!bSilent) info(nPos, pcode__STACKPOP);
    

   //t_boolean boolean_;// = 0;

   //t_string string_;// = 0;
 
   //t_byte byte_;// = 0;
   //t_short short_ ;//= 0;
   //t_integer integer_ ;//= 0;
   //t_long long_ ;//= 0;

   //t_single single_ ;//= 0;
   //t_double double_;// = 0;

   //t_int16 int16_;// = 0;
   //t_int32 int32_;// = 0;
   //t_int64 int64_;// = 0;
   //t_uint16 uint16_ ;//= 0;
   //t_uint32 uint32_;// = 0;
   //t_uint64 uint64_;// = 0;

   //t_currency currency_;
   //t_date date_;	
   

    interpreter_parameter *p = popStack();
    if (memory_type::isBinding(p->pcodeType)){
      myGc->dec2(p->pointer_);
    }
    delete p;

#ifdef auskommentierenjetzt

    t_pcode cType;
    cType = myStack->popPCode();
    switch (cType){

        case pcode__BOOLEAN: /*boolean_ = */myStack->popBoolean(); break;

    		case pcode__QSTRING:  myStack->popQString(); break;
    		case pcode__CSTRING:  myStack->popCString(); break;

    		case pcode__EQSTRING:   myStack->popEQString(); break;
    		case pcode__ECSTRING:   myStack->popECString(); break;

  	    case pcode__BYTE: /*byte_ = */myStack->popByte(); break;
  	    case pcode__SHORT: /*short_ = */myStack->popShort(); break;
  	    case pcode__INTEGER: /*integer_ = */myStack->popInteger(); break;
        case pcode__LONG: 	/*long_ = */myStack->popLong(); break;

    		case pcode__SINGLE: /*single_ = */myStack->popSingle(); break;
    		case pcode__DOUBLE: /*double_ = */myStack->popDouble(); break;

  	    case pcode__CURRENCY: /*currency_ = */myStack->popCurrency(); break;
  	    case pcode__DATE: /*date_ = */myStack->popDate(); break;

        case pcode__ERROR: /*date_ = */myStack->popError(); break;
			default:
				//myStack->dumpStack();
				pcodeError("unknown datatype on stack");
        return;
			  break;
    }
#endif

	} // } else return pcodeError(utility::con(pcode::pcode_(pcode__STACKPOP), " missing"));

	return;
}


