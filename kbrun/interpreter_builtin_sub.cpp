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

extern QMap<t_integer, QDataStream *> qdatastream;
extern QMap<QDataStream *, QByteArray *>qdatastream_bytearray;



void interpreter::fCLS()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin cls; t_boolean bEXPRESSION;

	myPcode->rd_CLS(&cls, &bEXPRESSION);
  {

    
#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__CLS);
#endif

		{
			myFunction->fCLS(); // call the associated function
		}
    return;

	} // } else return pcodeError(utility::con(pcode::builtin_(pcode__CLS), " missing"));

	return;
}

void interpreter::fLOCATE()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin locate; t_boolean bY; t_boolean bX; t_boolean bCursor;

	myPcode->rd_LOCATE(&locate, &bY, &bX, &bCursor);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__LOCATE);
#endif

		int x;
    x = 0;

		if (bX){
  		x = popStackInteger();
  		if (!(x >= 1 && x <= 80)){
  			runtimeError("x < 1 or x > 80");
        return;
  		}
		}

		int y;
    y = 0;

		if (bY){
  		y = popStackInteger();
  		if (!(y >= 1 && y <= 35)){
  			runtimeError("y < 1 or y > 35");
        return;
  		}
		}

	 	myFunction->fLOCATE(bY, bX, y, x); // call the associated function

    return;

	} // } else return pcodeError(utility::con(pcode::builtin_(pcode__LOCATE), " missing"));

	return;
}

void interpreter::fPRINT()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin print; t_boolean bFIRST; t_boolean bFILEHANDLE; t_boolean bUSING; t_boolean bEXPRESSION; t_boolean bSPC; t_boolean bTAB; t_boolean bCOMMA; t_boolean bSEMICOL; t_boolean bEcho; t_boolean bLog;

	myPcode->rd_PRINT(&print, &bFIRST, &bFILEHANDLE, &bUSING, &bEXPRESSION, &bSPC, &bTAB, &bCOMMA, &bSEMICOL, &bEcho, &bLog);
  //return;
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__PRINT);
#endif

    if (bLog){
      bSPC = bTAB = bCOMMA = bSEMICOL = false;
    }
    
    EXPRESSION[1] = 0;
    EXPRESSION[2] = 0;

    //int nestatics = 0;
	  if (bEXPRESSION) EXPRESSION[0] = popStack(); else EXPRESSION[0] = new interpreter_parameter("");

		    if (bSPC) EXPRESSION[1] = popStack(); 
		else if (bTAB) EXPRESSION[2] = popStack(); 

		bool bTabbedOutput;
    bTabbedOutput = bCOMMA;

		bool bNewLine;
    bNewLine = !(bCOMMA || bSEMICOL);

		//bool bFirst3 = false;
    int nFILEHANDLE;
    //nFILEHANDLE = 0;

    if (bFIRST && bFILEHANDLE){
      //bFirst3 = true;
      nFILEHANDLE = EXPRESSION[0]->toInteger();//popStackInteger();

      delete EXPRESSION[0];
      
      EXPRESSION[0] = new interpreter_parameter("");
    }

    int nestatics = 0;
    t_pcode c = 0;
    t_pointer q = 0;

    if (bFIRST && bUSING){
      q = popStackString(&nestatics, &c);
    }
    
    {      

      if (c == pcode__QSTRING){

		   myFunction->fPRINT(false, false,
          bFIRST, bFILEHANDLE, nFILEHANDLE, 
          ((t_qstring ) q), bEXPRESSION, 
          bSPC, bTAB, EXPRESSION[0], EXPRESSION[1] ? EXPRESSION[1]->toInteger() : 0, 
          EXPRESSION[2] ? EXPRESSION[2]->toInteger() : 0, bTabbedOutput, bNewLine, bEcho, bLog
        ); // call the associated function

      } else {

		   myFunction->fPRINT(false, false,
          bFIRST, bFILEHANDLE, nFILEHANDLE, 
          (t_cstring ) q, bEXPRESSION, 
          bSPC, bTAB, EXPRESSION[0], EXPRESSION[1] ? EXPRESSION[1]->toInteger() : 0, 
          EXPRESSION[2] ? EXPRESSION[2]->toInteger() : 0, bTabbedOutput, bNewLine, bEcho, bLog
        ); // call the associated function

      }

    }

    
      delete EXPRESSION[0];
    if (bSPC) delete EXPRESSION[1];
    if (bTAB) delete EXPRESSION[2];


    
    estatics->undeclare(nestatics);

    return;

	} // } else return pcodeError(utility::con(pcode::builtin_(pcode__PRINT), " missing"));

	return;
}

void interpreter::fPREPEND()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif

  t_builtin c; t_boolean bReturn;

  myPcode->rd_PREPEND(&c);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__PREPEND);
#endif
   
    int nestatics[interpreter__MAX_PARAM];

    STRING_EXPRESSION[1] = popStackString(&nestatics[1], &C[1]);    
    STRING_EXPRESSION[0] = popStackString(&nestatics[0], &C[0]);

    
    if (C[0] == pcode__QSTRING && C[1] == pcode__QSTRING) myFunction->fPREPEND((t_qstring) STRING_EXPRESSION[0], (t_qstring) STRING_EXPRESSION[1]); // call the associated function
    else if (C[0] == pcode__CSTRING && C[1] == pcode__CSTRING){
      estatics->undeclare(nestatics[0]);
      estatics->undeclare(nestatics[1]);
      this->runtimeError("CString not supported by PREPEND. Use String instead."); return;
      
    }
    else if (C[0] == pcode__QSTRING && C[1] == pcode__CSTRING){
      QString s; s = s.fromLocal8Bit((t_cstring) STRING_EXPRESSION[1]);
      myFunction->fPREPEND((t_qstring) STRING_EXPRESSION[0], &s); // call the associated function
    }
    else if (C[0] == pcode__CSTRING && C[1] == pcode__QSTRING){
      estatics->undeclare(nestatics[0]);
      estatics->undeclare(nestatics[1]);
      this->runtimeError("CString not supported by PREPEND. Use String instead."); return;
      
    }



    estatics->undeclare(nestatics[0]);
    estatics->undeclare(nestatics[1]);

  }
  return;
}

void interpreter::fAPPEND()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif

  t_builtin c; t_boolean bReturn;

  myPcode->rd_APPEND2(&c);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__APPEND2);
#endif
   
    int nestatics[interpreter__MAX_PARAM];

    STRING_EXPRESSION[1] = popStackString(&nestatics[1], &C[1]);    
    STRING_EXPRESSION[0] = popStackString(&nestatics[0], &C[0]);

    if (C[0] == pcode__QSTRING && C[1] == pcode__QSTRING) myFunction->fAPPEND((t_qstring) STRING_EXPRESSION[0], (t_qstring) STRING_EXPRESSION[1]); // call the associated function
    else if (C[0] == pcode__CSTRING && C[1] == pcode__CSTRING){
      estatics->undeclare(nestatics[0]);
      estatics->undeclare(nestatics[1]);
      this->runtimeError("CString not supported by APPEND. Use String instead."); return;
      
    }
    else if (C[0] == pcode__QSTRING && C[1] == pcode__CSTRING){
      QString s; s = s.fromLocal8Bit((t_cstring) STRING_EXPRESSION[1]);
      myFunction->fAPPEND((t_qstring) STRING_EXPRESSION[0], &s); // call the associated function
    }
    else if (C[0] == pcode__CSTRING && C[1] == pcode__QSTRING){
      estatics->undeclare(nestatics[0]);
      estatics->undeclare(nestatics[1]);
      this->runtimeError("CString not supported by APPEND. Use String instead."); return;
      
    }


    estatics->undeclare(nestatics[0]);
    estatics->undeclare(nestatics[1]);

  }
  return;
}

void interpreter::fREMOVE()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif

  t_builtin c; t_boolean bReturn;

  myPcode->rd_REMOVE(&c);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__REMOVE);
#endif
   
    int nestatics[interpreter__MAX_PARAM];

    t_integer Length = popStackInteger();

    t_integer Position = popStackInteger() - 1;

    STRING_EXPRESSION[0] = popStackString(&nestatics[0], &C[0]);


    if (C[0] == pcode__QSTRING) myFunction->fREMOVE((t_qstring) STRING_EXPRESSION[0], Position, Length); // call the associated function
    else if (C[0] == pcode__QSTRING){
      estatics->undeclare(nestatics[0]);
      this->runtimeError("CString not supported by REMOVE. Use String instead."); return;
      
    }

    estatics->undeclare(nestatics[0]);

  }
  return;
}

void interpreter::fTRUNCATE()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif

  t_builtin c; t_boolean bReturn;

  myPcode->rd_TRUNCATE(&c);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__TRUNCATE);
#endif
   
    int nestatics[interpreter__MAX_PARAM];

    t_integer Position = popStackInteger() - 1;

    STRING_EXPRESSION[0] = popStackString(&nestatics[0], &C[0]);


    if (C[0] == pcode__QSTRING) myFunction->fTRUNCATE((t_qstring) STRING_EXPRESSION[0], Position); // call the associated function
    else if (C[0] == pcode__QSTRING){
      estatics->undeclare(nestatics[0]);
      this->runtimeError("CString not supported by TRUNCATE. Use String instead."); return;
      
    }

    estatics->undeclare(nestatics[0]);

  }
  return;
}

void interpreter::fINSERT()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif

  t_builtin c; t_boolean bReturn;

  myPcode->rd_INSERT(&c);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__INSERT);
#endif
   
    int nestatics[interpreter__MAX_PARAM];

    t_integer Position = popStackInteger() - 1;

    STRING_EXPRESSION[1] = popStackString(&nestatics[1], &C[1]);    
    STRING_EXPRESSION[0] = popStackString(&nestatics[0], &C[0]);

    if (C[0] == pcode__QSTRING && C[1] == pcode__QSTRING) myFunction->fINSERT((t_qstring) STRING_EXPRESSION[0], (t_qstring) STRING_EXPRESSION[1], Position); // call the associated function
    else if (C[0] == pcode__CSTRING && C[1] == pcode__CSTRING){
      estatics->undeclare(nestatics[0]);
      estatics->undeclare(nestatics[1]);
      this->runtimeError("CString not supported by INSERT. Use String instead."); return;
      
    }
    else if (C[0] == pcode__QSTRING && C[1] == pcode__CSTRING){
      QString s; s = s.fromLocal8Bit((t_cstring) STRING_EXPRESSION[1]);
      myFunction->fINSERT((t_qstring) STRING_EXPRESSION[0], &s, Position); // call the associated function
    }
    else if (C[0] == pcode__CSTRING && C[1] == pcode__QSTRING){
      estatics->undeclare(nestatics[0]);
      estatics->undeclare(nestatics[1]);
      this->runtimeError("CString not supported by INSERT. Use String instead."); return;
      
    }

    estatics->undeclare(nestatics[0]);
    estatics->undeclare(nestatics[1]);

  }
  return;
}

void interpreter::fFILL()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif

  t_builtin c; t_boolean bEXPRESSION; t_boolean bReturn;

  myPcode->rd_FILL(&c, &bEXPRESSION);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__FILL);
#endif
   
    int nestatics[interpreter__MAX_PARAM];

    t_integer Position = -1;
    if (bEXPRESSION){
      Position = popStackInteger();
    }

    STRING_EXPRESSION[1] = popStackString(&nestatics[1], &C[1]);    
    STRING_EXPRESSION[0] = popStackString(&nestatics[0], &C[0]);

    if (C[0] == pcode__QSTRING && C[1] == pcode__QSTRING) myFunction->fFILL((t_qstring) STRING_EXPRESSION[0], (t_qstring) STRING_EXPRESSION[1], Position); // call the associated function
    else if (C[0] == pcode__CSTRING && C[1] == pcode__CSTRING){
      estatics->undeclare(nestatics[0]);
      estatics->undeclare(nestatics[1]);
      this->runtimeError("CString not supported by FILL. Use String instead."); return;
      
    }
    else if (C[0] == pcode__QSTRING && C[1] == pcode__CSTRING){
      QString s; s = s.fromLocal8Bit((t_cstring) STRING_EXPRESSION[1]);
      myFunction->fFILL((t_qstring) STRING_EXPRESSION[0], &s, Position); // call the associated function
    }
    else if (C[0] == pcode__CSTRING && C[1] == pcode__QSTRING){
      estatics->undeclare(nestatics[0]);
      estatics->undeclare(nestatics[1]);
      this->runtimeError("CString not supported by FILL. Use String instead."); return;
      
    }

    estatics->undeclare(nestatics[0]);
    estatics->undeclare(nestatics[1]);

  }
  return;
}
 

void interpreter::fWRITEBINARY()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif

  t_builtin c; t_integer identifier; t_scope scope; t_boolean bEXPRESSION;

  myPcode->rd_WRITEBINARY(&c, &identifier, &scope, &bEXPRESSION);

  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__WRITEBINARY);
#endif
   
    int nestatics[interpreter__MAX_PARAM];

    t_boolean boolean_;
    t_byte byte_;
    t_short short_;
    t_integer integer_;
    t_integer integer2_;
    t_integer integer3_;
    t_integer integer4_;
    t_integer integer5_;
    t_integer integer6_;
    t_long long_;
    t_long long2_;
    t_single single_;
    t_double double_;
    t_currency currency_;
    t_date date_;

    nestatics[1] = 0;

    t_boolean WriteLength = true;

    if (bEXPRESSION){
      WriteLength = popStackBoolean();
    }

    t_pcode cc = myStack->peekPCode();
    switch(cc){
      case pcode__BOOLEAN:
        boolean_ = popStackBoolean();
        break;
      case pcode__EQSTRING:
      case pcode__QSTRING:
        STRING_EXPRESSION[1] = popStackString(&nestatics[1], &C[1]);
        break;
      case pcode__BYTE:
        byte_ = popStackInteger();
        break;
      case pcode__SHORT:
        short_ = popStackInteger();
        break;
      case pcode__INTEGER:
        integer_ = popStackInteger();
        break;
      case pcode__LONG:
        long_ = popStackLong();
        break;
      case pcode__SINGLE:
        single_ = popStackDouble();
        break;
      case pcode__DOUBLE:
        double_ = popStackDouble();
        break;
      case pcode__CURRENCY:
        currency_ = popStackCurrency();
        break;
      case pcode__DATE:
        date_ = popStackDate();
        break;
    }


    STRING_EXPRESSION[0] = popStackString(&nestatics[0], &C[0]);

    bool bNew = true;

    QString s;
    if (C[0] == pcode__QSTRING){
      s = *((t_qstring) STRING_EXPRESSION[0]);

      bNew = !qdatastream.contains(identifier);
    } else {
      runtimeError("CString not allowed");
    }
    
    QDataStream *as;
    QByteArray *ba;
    if (bNew){
      ba = new QByteArray();//s.toLatin1());
      as = new QDataStream(ba, QIODevice::ReadWrite);
      qdatastream[identifier] = as;
      qdatastream_bytearray[as] = ba;
    } else {
      as = qdatastream[identifier];
      ba = qdatastream_bytearray[as];
    }

    int nBinaryPos = as->device()->pos();

    switch(cc){
      case pcode__BOOLEAN:
        byte_ = boolean_;
        *as << byte_;
        break;
      case pcode__EQSTRING:
      case pcode__QSTRING:
        {
          QString s = *((t_qstring) STRING_EXPRESSION[1]);
          int n = s.length();

          int m = ba->length();

          *as << s;

          m = ba->length();
        }
        break;
      case pcode__BYTE:
        *as << byte_;
        break;
      case pcode__SHORT:
        *as << short_;
        break;
      case pcode__INTEGER:
        *as << integer_;
        break;
      case pcode__LONG:
        *as << long_;
        break;
      case pcode__SINGLE:
        *as << single_;
        break;
      case pcode__DOUBLE:
        *as << double_;
        break;
      case pcode__CURRENCY:
        long_ = currency_.bc();
        *as << long_;
        long_ = currency_.ad();
        *as << long_;
        break;
      case pcode__DATE:
        integer_ = date_.nYear;
        *as << integer_;
        integer_ = date_.nMonth;
        *as << integer_;
        integer_ = date_.nDay;
        *as << integer_;
        integer_ = date_.nHour;
        *as << integer_;
        integer_ = date_.nMinute;
        *as << integer_;
        integer_ = date_.nSecond;
        *as << integer_;
        break;
    }

    fMOV_QSTRING(identifier, scope, ba, nBinaryPos);

    estatics->undeclare(nestatics[0]);
    estatics->undeclare(nestatics[1]);
  }
  return;
}

