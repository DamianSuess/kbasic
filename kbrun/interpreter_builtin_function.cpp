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

extern QString sProjectName;
extern QMap<t_integer, QDataStream *> qdatastream;
extern QMap<QDataStream *, QByteArray *>qdatastream_bytearray;

extern QLocale *qlocale;

void interpreter::fCHR()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif

  t_builtin chr; t_boolean bReturn;

  myPcode->rd_CHR(&chr, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__CHR);
#endif


    int n;
    n = popStackInteger();


    p = myFunction->fCHR(n); // call the associated function
    if (bReturn) pushStack(p); else delete p;
        
  } // } else return pcodeError(utility::con(pcode::builtin_(pcode__CHR), " missing"));

  return;
}

void interpreter::fLEN()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif

  t_builtin len; t_boolean bSTRING_EXPRESSION; t_boolean bReturn;

  myPcode->rd_LEN(&len, &bSTRING_EXPRESSION, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__LEN);
#endif

    if (bSTRING_EXPRESSION){

      int nestatics;
      t_pcode c;
      t_pointer q;

      q = popStackString(&nestatics, &c);
      if (c == pcode__QSTRING) p = myFunction->fLEN((t_qstring) q); // call the associated function
      else p = myFunction->fLEN((t_cstring) q); // call the associated function
      if (bReturn) pushStack(p); else delete p;
      estatics->undeclare(nestatics);
 
    } else {
      // len liegt bereits korrekt auf dem stack, bei typesize
      // muss nichts tun 
    }


  } // } else return pcodeError(utility::con(pcode::builtin_(pcode__LEN), " missing"));

  return;
}

void interpreter::fMID()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin mid; t_boolean bReturn; t_boolean bLen;

  myPcode->rd_MID(&mid, &bReturn, &bLen);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__MID);
#endif
    
    int n2 = 0; 
    if (bLen){ n2 = popStackInteger(); }

    p = 0;

    int n;
    n = popStackInteger();
    /*
    if (n <= 0){
      runtimeError("MID: INDEX < 0");
      return;
    }
     
    if (n2 < 0){
      runtimeError("MID: LEN < 0");
      return;
    }*/
    
      int nestatics;
      t_pcode c;
      t_pointer q;
      q = popStackString(&nestatics, &c);

      if (bLen){
        if (c == pcode__QSTRING) p = myFunction->fMID((t_qstring) q, n, n2); // call the associated function
        else  p = myFunction->fMID((t_cstring) q, n, n2); // call the associated function
      } else {
        if (c == pcode__QSTRING) p = myFunction->fMID((t_qstring) q, n); // call the associated function
        else p = myFunction->fMID((t_cstring) q, n); // call the associated function
      }
      estatics->undeclare(nestatics);
     

    if (bReturn) pushStack(p); else delete p;
    
  } // } else return pcodeError(utility::con(pcode::builtin_(pcode__MID), " missing"));

  return;
}

void interpreter::fUTF8()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin val; t_boolean bReturn;

  myPcode->rd_UTF8(&val, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__UTF8);
#endif

    int nestatics;
    t_pcode c;
    t_pointer q;
    q = popStackString(&nestatics, &c);

    if (c == pcode__QSTRING) p = myFunction->fUTF8((t_qstring) q); // call the associated function
    else p = myFunction->fUTF8((t_cstring) q); // call the associated function
    if (bReturn) pushStack(p); else delete p;
    estatics->undeclare(nestatics);

  } // } else return pcodeError(utility::con(pcode::builtin_(pcode__UTF8), " missing"));

  return;
}


void interpreter::fUTF16()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin val; t_boolean bReturn;

  myPcode->rd_UTF16(&val, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__UTF16);
#endif

    int wlen = popStackInteger();

    int nestatics;
    t_pcode c;
    t_pointer q;
    q = popStackString(&nestatics, &c);

    if (c == pcode__QSTRING){
      if (wlen > ((t_qstring) q)->length()) wlen = ((t_qstring) q)->length();
      int n = wlen * 2;
  
      int nId = estatics->declare(pcode__CSTRING, 0, false, false);
      estatics->setWString(nId, (t_cstring) ((t_qstring) q)->utf16(), 0, n);  
      estatics->setTypeSize(nId, n);

      if (bReturn) myStack->pushEWString(nId);
      estatics->undeclare(nestatics);
			return;

    } else {
      p = myFunction->fUTF16((t_cstring) q, wlen); // call the associated function
      if (bReturn) pushStack(p); else delete p;
    }
    estatics->undeclare(nestatics);

  } // } else return pcodeError(utility::con(pcode::builtin_(pcode__UTF8), " missing"));

  return;
}


void interpreter::fVAL()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin val; t_boolean bReturn;

  myPcode->rd_VAL(&val, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__VAL);
#endif

    int nestatics;
    t_pcode c;
    t_pointer q;
    q = popStackString(&nestatics, &c);

    if (c == pcode__QSTRING) p = myFunction->fVAL((t_qstring) q); // call the associated function
    else p = myFunction->fVAL((t_cstring) q); // call the associated function
    if (bReturn) pushStack(p); else delete p;
    estatics->undeclare(nestatics);

  } // } else return pcodeError(utility::con(pcode::builtin_(pcode__VAL), " missing"));

  return;
}

void interpreter::fINT()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin int_; t_boolean bReturn;

  myPcode->rd_INT(&int_, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__INT);
#endif

    p = myFunction->fINT(popStackDouble()); // call the associated function
    if (bReturn) pushStack(p); else delete p;    

  } // } else return pcodeError(utility::con(pcode::builtin_(pcode__INT), " missing"));

  return;
}

void interpreter::fRANDOMIZE()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin int_; t_boolean bExpression; t_boolean bAuto;

  myPcode->rd_RANDOMIZE(&int_, &bExpression, &bAuto);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__RANDOMIZE);
#endif

    int n;
    n = 0;
    if (bExpression){ n = popStackInteger(); }
    if (bAuto){
      p = myFunction->fTIMER(); // call the associated function
      pushStack(p);
      bExpression = true;
      n = popStackInteger();
    }

    myFunction->fRANDOMIZE(bExpression, n); // call the associated function

  } // } else return pcodeError(utility::con(pcode::builtin_(pcode__RANDOMIZE), " missing"));

  return;
}

void interpreter::fRND()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin rnd; t_boolean bReturn; t_boolean bExpression;

  myPcode->rd_RND(&rnd, &bReturn, &bExpression);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__RND);
#endif

    double d;
    d = 0;

    if (bExpression){ d = popStackDouble(); }

    p = myFunction->fRND(bExpression, d); // call the associated function
    if (bReturn) pushStack(p); else delete p;

  } // } else return pcodeError(utility::con(pcode::builtin_(pcode__RND), " missing"));

  return;
}

void interpreter::fCSRLIN()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin csrlin; t_boolean bReturn;

  myPcode->rd_CSRLIN(&csrlin, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__CSRLIN);
#endif

    p = myFunction->fCSRLIN(); // call the associated function
    if (bReturn) pushStack(p); else delete p;
    
  } // } else return pcodeError(utility::con(pcode::builtin_(pcode__CSRLIN), " missing"));

  return;
}

void interpreter::fPOS()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin pos; t_boolean bReturn;

  myPcode->rd_POS(&pos, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__POS);
#endif

    p = myFunction->fPOS(popStackInteger()); // call the associated function
    if (bReturn) pushStack(p); else delete p;
    
  } // } else return pcodeError(utility::con(pcode::builtin_(pcode__POS), " missing"));

  return;
}

void interpreter::fCOLOR()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin color; t_boolean bFORE; t_boolean bBACK;

  myPcode->rd_COLOR(&color, &bFORE, &bBACK);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__COLOR);
#endif

    if (bBACK) INTEGER_EXPRESSION[1] = popStackInteger();
    if (bFORE) INTEGER_EXPRESSION[0] = popStackInteger();

    if (bBACK){
      if (!(INTEGER_EXPRESSION[1] >= 0 && INTEGER_EXPRESSION[1] <= 15)){
        runtimeError("COLOR: background < 0 or background > 15");
        return;
      }
    }

    if (bFORE){
      if (!(INTEGER_EXPRESSION[0] >= 0 && INTEGER_EXPRESSION[0] <= 31)){
        runtimeError("COLOR: foreground < 0 or foreground > 31");
        return;
      }
    }

    myFunction->fCOLOR(bFORE, bBACK, INTEGER_EXPRESSION[0], INTEGER_EXPRESSION[1]); // call the associated function

  } // } else return pcodeError(utility::con(pcode::builtin_(pcode__COLOR), " missing"));

  return;
}


void interpreter::fABS()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin abs; t_boolean bReturn;

  myPcode->rd_ABS(&abs, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__ABS);   
#endif


    p = myFunction->fABS(popStackDouble()); // call the associated function
    if (bReturn) pushStack(p); else delete p;
    
  } // } else return pcodeError(utility::con(pcode::builtin_(pcode__ABS), " missing"));

  return;
}

void interpreter::fDATE()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin date; t_boolean bReturn;

  myPcode->rd_DATE(&date, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__DATE);
#endif

    p = myFunction->fDATE(); // call the associated function
    if (bReturn) pushStack(p); else delete p;
    
  } // } else return pcodeError(utility::con(pcode::builtin_(pcode__DATE), " missing"));

  return;
}

void interpreter::fDATE2()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin c; t_boolean bReturn;

  myPcode->rd_DATE2(&c, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__DATE2);
#endif

    //

  } // } else return pcodeError(utility::con(pcode::builtin_(pcode__DATE2), " missing"));

  return;
}

void interpreter::fTIME()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin time; t_boolean bReturn;

  myPcode->rd_TIME(&time, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__TIME);
#endif

    p = myFunction->fTIME(); // call the associated function
    if (bReturn) pushStack(p); else delete p;    

  } // } else return pcodeError(utility::con(pcode::builtin_(pcode__TIME), " missing"));

  return;
}

void interpreter::fSTRING2()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin string2; t_boolean bReturn; t_boolean bAscii; t_boolean bString;

  myPcode->rd_STRING2(&string2, &bReturn, &bAscii, &bString);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__STRING2);
#endif

    int nAscii;
    nAscii = 0;
    QChar cChar;
    cChar = ' ';

    int nestatics;    

    if (bAscii){
      nAscii = popStackInteger();
      /*
      if (nAscii <= 0 || nAscii >= 256){
        runtimeError("ascii-code < 0 or ascii-code > 255");
        return;
      }*/

    } else if (bString){
      const char *ac;
      t_pcode c;
      t_pointer q;
      q = popStackString(&nestatics, &c);

      if (c == pcode__QSTRING){
        cChar = ((t_qstring) q)->at(0);
      } else {
        cChar = ac[0];
      }
/*
      if (ac[0] == 0){
        runtimeError("string empty");
        return;
      } else {
        cChar = ac[0];
      }*/
    }

    int nLen;
    nLen = popStackInteger();
    if (nLen < 0){
      runtimeError("STRING: length < 0");
      return;
    }

    p = myFunction->fSTRING2(bAscii, bString, nLen, nAscii, cChar); // call the associated function
    if (bReturn) pushStack(p); else delete p;

    if (bString)  estatics->undeclare(nestatics);
    
  } // } else return pcodeError(utility::con(pcode::builtin_(pcode__STRING2), " missing"));

  return;
}

void interpreter::fKBASICDIR()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin c; t_boolean bReturn;

  myPcode->rd_KBASICDIR(&c, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__KBASICDIR);
#endif

    QString s = qApp->applicationDirPath();
#ifdef WINDOWS
    if (s.compare("c:/kbasic16/kbrun/Debug") == 0){ // HIDE
      s = "c:/kbasic16/kbide"; // HIDE
    } // HIDE
#endif

    p = new interpreter_parameter(s);
    if (bReturn) pushStack(p); else delete p;
    
  } // } else return pcodeError(utility::con(pcode::builtin_(pcode__STRING2), " missing"));

  return;
}

void interpreter::fSPACE()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin space; t_boolean bReturn;

  myPcode->rd_SPACE(&space, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__SPACE);
#endif    

    p = myFunction->fSPACE(popStackInteger()); // call the associated function
    if (bReturn) pushStack(p); else delete p;
    
  } // } else return pcodeError(utility::con(pcode::builtin_(pcode__SPACE), " missing"));

  return;
}


void interpreter::fLEFT()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin left; t_boolean bReturn;

  myPcode->rd_LEFT(&left, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__LEFT);
#endif

    INTEGER_EXPRESSION[0] = popStackInteger();
    int nestatics;   
    STRING_EXPRESSION[0] = popStackString(&nestatics, &C[0]);
/*
    if (INTEGER_EXPRESSION[0] <= 0){
      runtimeError("LEFT: string length <= 0");
      return;
    }*/

    if (C[0] == pcode__QSTRING) p = myFunction->fLEFT((t_qstring) STRING_EXPRESSION[0], INTEGER_EXPRESSION[0]); // call the associated function
    else p = myFunction->fLEFT((t_cstring) STRING_EXPRESSION[0], INTEGER_EXPRESSION[0]); // call the associated function

    if (bReturn) pushStack(p); else delete p;
    estatics->undeclare(nestatics);
    
  } // } else return pcodeError(utility::con(pcode::builtin_(pcode__LEFT), " missing"));

  return;
}

void interpreter::fRIGHT()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin right; t_boolean bReturn;

  myPcode->rd_RIGHT(&right, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__RIGHT);
#endif
    
    INTEGER_EXPRESSION[0] = popStackInteger();
    int nestatics;
    STRING_EXPRESSION[0] = popStackString(&nestatics, &C[0]);
/*
    if (INTEGER_EXPRESSION[0] <= 0){
      runtimeError("RIGHT: string length < 0");
      return;
    }
*/
    if (C[0] == pcode__QSTRING) p = myFunction->fRIGHT((t_qstring) STRING_EXPRESSION[0], INTEGER_EXPRESSION[0]); // call the associated function
    else p = myFunction->fRIGHT((t_cstring) STRING_EXPRESSION[0], INTEGER_EXPRESSION[0]); // call the associated function

    if (bReturn) pushStack(p); else delete p;    

    estatics->undeclare(nestatics);

  } // } else return pcodeError(utility::con(pcode::builtin_(pcode__RIGHT), " missing"));

  return;
}

void interpreter::fUCASE()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin ucase; t_boolean bReturn;

  myPcode->rd_UCASE(&ucase, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__UCASE);
#endif

    int nestatics;
    t_pcode c;
    t_pointer q;
    q = popStackString(&nestatics, &c);

    if (c == pcode__QSTRING) p = myFunction->fUCASE((t_qstring) q); // call the associated function
    else p = myFunction->fUCASE((t_cstring) q); // call the associated function

    if (bReturn) pushStack(p); else delete p;
    estatics->undeclare(nestatics);
    
  } // } else return pcodeError(utility::con(pcode::builtin_(pcode__UCASE), " missing"));

  return;
}

void interpreter::fLCASE()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin lcase; t_boolean bReturn;

  myPcode->rd_LCASE(&lcase, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__LCASE);
#endif

    int nestatics;
    t_pcode c;
    t_pointer q;
    q = popStackString(&nestatics, &c);

    if (c == pcode__QSTRING) p = myFunction->fLCASE((t_qstring) q); // call the associated function
    else p = myFunction->fLCASE((t_cstring) q); // call the associated function

    if (bReturn) pushStack(p); else delete p;
    estatics->undeclare(nestatics);
    
  } // } else return pcodeError(utility::con(pcode::builtin_(pcode__LCASE), " missing"));

  return;
}

void interpreter::fLTRIM()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin ltrim; t_boolean bReturn;

  myPcode->rd_LTRIM(&ltrim, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__LTRIM);
#endif

    int nestatics;
    t_pcode c;
    t_pointer q;
    q = popStackString(&nestatics, &c);

    if (c == pcode__QSTRING) p = myFunction->fLTRIM((t_qstring) q); // call the associated function
    else  p = myFunction->fLTRIM((t_cstring) q); // call the associated function

    if (bReturn) pushStack(p); else delete p;
    estatics->undeclare(nestatics);
    
  } // } else return pcodeError(utility::con(pcode::builtin_(pcode__LTRIM), " missing"));

  return;
}


void interpreter::fRTRIM()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin rtrim; t_boolean bReturn;

  myPcode->rd_RTRIM(&rtrim, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__RTRIM);
#endif

    int nestatics;
    t_pcode c;
    t_pointer q;
    q = popStackString(&nestatics, &c);

    if (c == pcode__QSTRING) p = myFunction->fRTRIM((t_qstring) q); // call the associated function
    else  p = myFunction->fRTRIM((t_cstring) q); // call the associated function

    if (bReturn) pushStack(p); else delete p;
    estatics->undeclare(nestatics);
    
  } // } else return pcodeError(utility::con(pcode::builtin_(pcode__RTRIM), " missing"));

  return;
}

void interpreter::fTRIM()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin trim; t_boolean bReturn;

  myPcode->rd_TRIM(&trim, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__TRIM);
#endif

    int nestatics;
    t_pcode c;
    t_pointer q;
    q = popStackString(&nestatics, &c);

    if (c == pcode__QSTRING) p = myFunction->fTRIM((t_qstring) q); // call the associated function
    else  p = myFunction->fTRIM((t_cstring) q); // call the associated function

    if (bReturn) pushStack(p); else delete p;
    estatics->undeclare(nestatics);
    
  } // } else return pcodeError(utility::con(pcode::builtin_(pcode__TRIM), " missing"));

  return;
}

void interpreter::fASC()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin asc; t_boolean bReturn;

  myPcode->rd_ASC(&asc, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__ASC);
#endif

    int nestatics;
    t_pcode c;
    t_pointer q;
    q = popStackString(&nestatics, &c);

    if (c == pcode__QSTRING) p = myFunction->fASC((t_qstring) q); // call the associated function
    else p = myFunction->fASC((t_cstring) q); // call the associated function

    if (bReturn) pushStack(p); else delete p;
    estatics->undeclare(nestatics);
    
  } // } else return pcodeError(utility::con(pcode::builtin_(pcode__ASC), " missing"));

  return;
}

void interpreter::fSTR()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin str; t_boolean bReturn;

  myPcode->rd_STR(&str, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__STR);
#endif

    p = myFunction->fSTR(popStackDouble()); // call the associated function
    if (bReturn) pushStack(p); else delete p;

  } // } else return pcodeError(utility::con(pcode::builtin_(pcode__STR), " missing"));

  return;
}

void interpreter::fHEX()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin hex; t_boolean bReturn;

  myPcode->rd_HEX(&hex, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__HEX);    
#endif

    p = myFunction->fHEX(popStackInteger()); // call the associated function
    if (bReturn) pushStack(p); else delete p;
    
  } // } else return pcodeError(utility::con(pcode::builtin_(pcode__HEX), " missing"));

  return;
}

void interpreter::fOCT()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin oct; t_boolean bReturn;

  myPcode->rd_OCT(&oct, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__OCT);
#endif

    p = myFunction->fOCT(popStackInteger()); // call the associated function
    if (bReturn) pushStack(p); else delete p;  

  } // } else return pcodeError(utility::con(pcode::builtin_(pcode__OCT), " missing"));

  return;
}

void interpreter::fBIN()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin bin; t_boolean bReturn;

  myPcode->rd_BIN(&bin, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__BIN);
#endif

    p = myFunction->fBIN(popStackInteger()); // call the associated function
    if (bReturn) pushStack(p); else delete p;    

  } // } else return pcodeError(utility::con(pcode::builtin_(pcode__BIN), " missing"));

  return;
}


void interpreter::fSLEEP()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin sleep; t_boolean bExpression;

  myPcode->rd_SLEEP(&sleep, &bExpression);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__SLEEP);
#endif
  
    int n;
    n = 0;

    if (bExpression){
      n = popStackInteger();
    }

    myFunction->fSLEEP(bExpression, n); // call the associated function    

  } // } else return pcodeError(utility::con(pcode::builtin_(pcode__SLEEP), " missing"));

  return;
}

void interpreter::fSHELL()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin shell; t_boolean bCommand; t_boolean bSynchron; t_boolean bReturn;

  myPcode->rd_SHELL(&shell, &bCommand, &bSynchron, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__SHELL);
#endif
    int nestatics;
    t_pcode c;
    t_pointer q;



    if (bSynchron){
      bSynchron = popStackBoolean();
    }

    if (bCommand){ 
      q = popStackString(&nestatics, &c);

    }

    if (c == pcode__QSTRING) p = myFunction->fSHELL(bCommand, bSynchron, (t_qstring) q); // call the associated function        
    else p = myFunction->fSHELL(bCommand, bSynchron, (t_cstring) q); // call the associated function        

    if (bReturn) pushStack(p); else delete p;
    if (bCommand) estatics->undeclare(nestatics);

    if (!bCommand){
      bRunPcode = false; // stop execution
      qApp->exit();
    }

  } // } else return pcodeError(utility::con(pcode::builtin_(pcode__SHELL), " missing"));

  return;
}

void interpreter::fCLNG()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin clng; t_boolean bReturn;

  myPcode->rd_CLNG(&clng, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__CLNG);
#endif

    
    p = myFunction->fCLNG(popStack()); // call the associated function
    if (bReturn) pushStack(p); else delete p;

  } // } else return pcodeError(utility::con(pcode::builtin_(pcode__CLNG), " missing"));

  return;
}

void interpreter::fCINT()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin cint; t_boolean bReturn;

  myPcode->rd_CINT(&cint, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__CINT);
#endif
    
    
    p = myFunction->fCINT(popStack()); // call the associated function
    if (bReturn) pushStack(p); else delete p;

  } // } else return pcodeError(utility::con(pcode::builtin_(pcode__CINT), " missing"));

  return;
}

void interpreter::fCSNG()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin c; t_boolean bReturn;

  myPcode->rd_CSNG(&c, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__CSNG);
#endif

    
    p = myFunction->fCSNG(popStack()); // call the associated function
    if (bReturn) pushStack(p); else delete p;
    
  } // } else return pcodeError(utility::con(pcode::builtin_(pcode__CSNG), " missing"));

  return;
}

void interpreter::fCDBL()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin c; t_boolean bReturn;

  myPcode->rd_CDBL(&c, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__CDBL);
#endif

    
    p = myFunction->fCDBL(popStack()); // call the associated function
    if (bReturn) pushStack(p); else delete p;
    
  } // } else return pcodeError(utility::con(pcode::builtin_(pcode__CDBL), " missing"));

  return;
}

void interpreter::fCCUR()
{
  register int nPos = myPcode->getPos();

  t_builtin c; t_boolean bReturn;

  myPcode->rd_CCUR(&c, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__CCUR);
#endif

    
    p = myFunction->fCCUR(popStack()); // call the associated function
    if (bReturn) pushStack(p); else delete p;
    
  } // } else return pcodeError(utility::con(pcode::builtin_(pcode__CCUR), " missing"));

  return;
}

void interpreter::fCVAR()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif

  t_builtin c; t_boolean bReturn;

  myPcode->rd_CVAR(&c, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__CVAR);
#endif

    
  } // } else return pcodeError(utility::con(pcode::builtin_(pcode__CVAR), " missing"));

  return;
}

void interpreter::fCBOOL()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif

  t_builtin c; t_boolean bReturn;

  myPcode->rd_CBOOL(&c, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__CBOOL);
#endif

    
    p = myFunction->fCBOOL(popStack()); // call the associated function
    if (bReturn) pushStack(p); else delete p;
    
  } // } else return pcodeError(utility::con(pcode::builtin_(pcode__CBOOL), " missing"));

  return;
}

void interpreter::fCBYTE()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif

  t_builtin c; t_boolean bReturn;

  myPcode->rd_CBYTE(&c, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__CBYTE);
#endif

    //int nestatics = 0;
    p = myFunction->fCBYTE(popStack()); // call the associated function
    if (bReturn) pushStack(p); else delete p;
    //if (nestatics)  estatics->undeclare(nestatics);
    
  } // } else return pcodeError(utility::con(pcode::builtin_(pcode__CBYTE), " missing"));

  return;
}

void interpreter::fCDATE()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif

  t_builtin c; t_boolean bReturn;

  myPcode->rd_CDATE(&c, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__CDATE);
#endif

    
    EXPRESSION[0] = popStack();

    if (bReturn) pushStack(new interpreter_parameter(EXPRESSION[0]->toDate(true)));
    delete EXPRESSION[0];

    
  } // } else return pcodeError(utility::con(pcode::builtin_(pcode__CDATE), " missing"));

  return;
}

void interpreter::fRAD()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif

  t_builtin rad; t_boolean bReturn;

  myPcode->rd_RAD(&rad, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__RAD);
#endif

    p = myFunction->fRAD(popStackDouble()); // call the associated function
    if (bReturn) pushStack(p); else delete p;
    
  } // } else return pcodeError(utility::con(pcode::builtin_(pcode__RAD), " missing"));

  return;
}

void interpreter::fDEG()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif

  t_builtin deg; t_boolean bReturn;

  myPcode->rd_DEG(&deg, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__DEG);
#endif

    p = myFunction->fDEG(popStackDouble()); // call the associated function
    if (bReturn) pushStack(p); else delete p;
    
  } // } else return pcodeError(utility::con(pcode::builtin_(pcode__DEG), " missing"));

  return;
}

void interpreter::fACS()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif

  t_builtin acs; t_boolean bReturn;

  myPcode->rd_ACS(&acs, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__ACS);
#endif

    p = myFunction->fACS(popStackDouble()); // call the associated function
    if (bReturn) pushStack(p); else delete p;
    
  } // } else return pcodeError(utility::con(pcode::builtin_(pcode__ACS), " missing"));

  return;
}

void interpreter::fASN()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif

  t_builtin asn; t_boolean bReturn;

  myPcode->rd_ASN(&asn, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__ASN);
#endif

    p = myFunction->fASN(popStackDouble()); // call the associated function
    if (bReturn) pushStack(p); else delete p;
    
  } // } else return pcodeError(utility::con(pcode::builtin_(pcode__ASN), " missing"));

  return;
}

void interpreter::fATN()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif

  t_builtin atn; t_boolean bReturn;

  myPcode->rd_ATN(&atn, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__ATN);
#endif

    p = myFunction->fATN(popStackDouble()); // call the associated function
    if (bReturn) pushStack(p); else delete p;
    
  } // } else return pcodeError(utility::con(pcode::builtin_(pcode__ATN), " missing"));

  return;
}

void interpreter::fCOS()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif

  t_builtin cos; t_boolean bReturn;

  myPcode->rd_COS(&cos, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__COS);
#endif

    p = myFunction->fCOS(popStackDouble()); // call the associated function
    if (bReturn) pushStack(p); else delete p;
    
  } // } else return pcodeError(utility::con(pcode::builtin_(pcode__COS), " missing"));

  return;
}

void interpreter::fEXP()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif

  t_builtin exp; t_boolean bReturn;

  myPcode->rd_EXP(&exp, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__EXP);
#endif

    p = myFunction->fEXP(popStackDouble()); // call the associated function
    if (bReturn) pushStack(p); else delete p;
    
  } // } else return pcodeError(utility::con(pcode::builtin_(pcode__EXP), " missing"));

  return;
}

void interpreter::fLOG()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif

  t_builtin log; t_boolean bReturn;

  myPcode->rd_LOG(&log, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__LOG);
#endif

    p = myFunction->fLOG(popStackDouble()); // call the associated function
    if (bReturn) pushStack(p); else delete p;
    
  } // } else return pcodeError(utility::con(pcode::builtin_(pcode__LOG), " missing"));

  return;
}

void interpreter::fLN()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif

  t_builtin ln; t_boolean bReturn;

  myPcode->rd_LN(&ln, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__LN);
#endif

    p = myFunction->fLN(popStackDouble()); // call the associated function
    if (bReturn) pushStack(p); else delete p;
    
  } // } else return pcodeError(utility::con(pcode::builtin_(pcode__LN), " missing"));

  return;
}

void interpreter::fSGN()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif

  t_builtin sgn; t_boolean bReturn;

  myPcode->rd_SGN(&sgn, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__SGN);
#endif

    p = myFunction->fSGN(popStackDouble()); // call the associated function
    if (bReturn) pushStack(p); else delete p;
    
  } // } else return pcodeError(utility::con(pcode::builtin_(pcode__SGN), " missing"));

  return;
}

void interpreter::fFIX()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif

  t_builtin fix; t_boolean bReturn;

  myPcode->rd_FIX(&fix, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__FIX);
#endif

    p = myFunction->fFIX(popStackDouble()); // call the associated function
    if (bReturn) pushStack(p); else delete p;
    
  } // } else return pcodeError(utility::con(pcode::builtin_(pcode__FIX), " missing"));

  return;
}

void interpreter::fSIN()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif

  t_builtin sin; t_boolean bReturn;

  myPcode->rd_SIN(&sin, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__SIN);
#endif

    p = myFunction->fSIN(popStackDouble()); // call the associated function
    if (bReturn) pushStack(p); else delete p;
    
  } // } else return pcodeError(utility::con(pcode::builtin_(pcode__SIN), " missing"));

  return;
}

void interpreter::fSQR()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif

  t_builtin sqr; t_boolean bReturn;

  myPcode->rd_SQR(&sqr, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__SQR);
#endif

    p = myFunction->fSQR(popStackDouble()); // call the associated function
    if (bReturn) pushStack(p); else delete p;
    
  } // } else return pcodeError(utility::con(pcode::builtin_(pcode__SQR), " missing"));

  return;
}

void interpreter::fTAN()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif

  t_builtin tan; t_boolean bReturn;

  myPcode->rd_TAN(&tan, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__TAN);
#endif

    p = myFunction->fTAN(popStackDouble()); // call the associated function
    if (bReturn) pushStack(p); else delete p;
    
  } // } else return pcodeError(utility::con(pcode::builtin_(pcode__TAN), " missing"));

  return;
}

void interpreter::fFACT()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif

  t_builtin fact; t_boolean bReturn;

  myPcode->rd_FACT(&fact, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__FACT);
#endif

    p = myFunction->fFACT(popStackDouble()); // call the associated function
    if (bReturn) pushStack(p); else delete p;
    
  } // } else return pcodeError(utility::con(pcode::builtin_(pcode__FACT), " missing"));

  return;
}

void interpreter::fFRAC()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif

  t_builtin frac; t_boolean bReturn;

  myPcode->rd_FRAC(&frac, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__FRAC);
#endif

    p = myFunction->fFRAC(popStackDouble()); // call the associated function
    if (bReturn) pushStack(p); else delete p;
    
  } // } else return pcodeError(utility::con(pcode::builtin_(pcode__FRAC), " missing"));

  return;
}

void interpreter::fSEC()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif

  t_builtin sec; t_boolean bReturn;

  myPcode->rd_SEC(&sec, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__SEC);
#endif

    p = myFunction->fSEC(popStackDouble()); // call the associated function
    if (bReturn) pushStack(p); else delete p;
    
  } // } else return pcodeError(utility::con(pcode::builtin_(pcode__SEC), " missing"));

  return;
}

void interpreter::fLOGB()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif

  t_builtin logb; t_boolean bReturn;

  myPcode->rd_LOGB(&logb, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__LOGB);
#endif
   
    DOUBLE_EXPRESSION[1] = popStackDouble();
    DOUBLE_EXPRESSION[0] = popStackDouble();

    p = myFunction->fLOGB(DOUBLE_EXPRESSION[0], DOUBLE_EXPRESSION[1]); // call the associated function
    if (bReturn) pushStack(p); else delete p;
    
  } // } else return pcodeError(utility::con(pcode::builtin_(pcode__LOGB), " missing"));

  return;
}

void interpreter::fHYPOT()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif

  t_builtin hypot; t_boolean bReturn;

  myPcode->rd_HYPOT(&hypot, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__HYPOT);    
#endif

    DOUBLE_EXPRESSION[1] = popStackDouble();
    DOUBLE_EXPRESSION[0] = popStackDouble();

    p = myFunction->fHYPOT(DOUBLE_EXPRESSION[0], DOUBLE_EXPRESSION[1]); // call the associated function
    if (bReturn) pushStack(p); else delete p;
    
  } // } else return pcodeError(utility::con(pcode::builtin_(pcode__HYPOT), " missing"));

  return;
}

void interpreter::fMAX()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif

  t_builtin max; t_boolean bReturn;

  myPcode->rd_MAX(&max, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__MAX);
#endif

    DOUBLE_EXPRESSION[1] = popStackDouble();
    DOUBLE_EXPRESSION[0] = popStackDouble();

    p = myFunction->fMAX(DOUBLE_EXPRESSION[0], DOUBLE_EXPRESSION[1]); // call the associated function
    if (bReturn) pushStack(p); else delete p;  

  } // } else return pcodeError(utility::con(pcode::builtin_(pcode__MAX), " missing"));

  return;
}

void interpreter::fMIN()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif

  t_builtin min; t_boolean bReturn;

  myPcode->rd_MIN(&min, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__MIN);
#endif

    DOUBLE_EXPRESSION[1] = popStackDouble();
    DOUBLE_EXPRESSION[0] = popStackDouble();

    p = myFunction->fMIN(DOUBLE_EXPRESSION[0], DOUBLE_EXPRESSION[1]); // call the associated function
    if (bReturn) pushStack(p); else delete p;    

  } // } else return pcodeError(utility::con(pcode::builtin_(pcode__MIN), " missing"));

  return;
}

void interpreter::fCHDIR()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif

  t_builtin chdir;

  myPcode->rd_CHDIR(&chdir);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__CHDIR);
#endif

    int nestatics;
    t_pcode c;
    t_pointer q;
    q = popStackString(&nestatics, &c);

    if (c == pcode__QSTRING) myFunction->fCHDIR((t_qstring) q); // call the associated function
    else  myFunction->fCHDIR((t_cstring) q); // call the associated function

    estatics->undeclare(nestatics);

  } // } else return pcodeError(utility::con(pcode::builtin_(pcode__CHDIR), " missing"));

  return;
}

void interpreter::fRMDIR()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif

  t_builtin rmdir;

  myPcode->rd_RMDIR(&rmdir);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__RMDIR);
#endif

    int nestatics;
    t_pcode c;
    t_pointer q;
    q = popStackString(&nestatics, &c);

    if (c == pcode__QSTRING) myFunction->fRMDIR((t_qstring) q); // call the associated function
    else  myFunction->fRMDIR((t_cstring) q); // call the associated function

    estatics->undeclare(nestatics);

  } // } else return pcodeError(utility::con(pcode::builtin_(pcode__RMDIR), " missing"));

  return;
}

void interpreter::fMKDIR()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif

  t_builtin mkdir;

  myPcode->rd_MKDIR(&mkdir);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__MKDIR);
#endif

    int nestatics;
    t_pcode c;
    t_pointer q;
    q = popStackString(&nestatics, &c);

    if (c == pcode__QSTRING) myFunction->fMKDIR((t_qstring) q); // call the associated function
    else  myFunction->fMKDIR((t_cstring) q); // call the associated function

    estatics->undeclare(nestatics);

  } // } else return pcodeError(utility::con(pcode::builtin_(pcode__MKDIR), " missing"));

  return;
}

void interpreter::fBEEP()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif

  t_builtin beep;

  myPcode->rd_BEEP(&beep);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__BEEP);
#endif

    {
      myFunction->fBEEP(); // call the associated function
    }

  } // } else return pcodeError(utility::con(pcode::builtin_(pcode__BEEP), " missing"));

  return;
}

void interpreter::fRESET()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif

  t_builtin reset;

  myPcode->rd_RESET(&reset);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__RESET);
#endif

    {
      myFunction->fRESET(); // call the associated function
    }

  } // } else return pcodeError(utility::con(pcode::builtin_(pcode__RESET), " missing"));

  return;
}

void interpreter::fFILES()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif

  t_builtin files; t_boolean bDirectory; t_boolean bReturn;

  myPcode->rd_FILES(&files, &bDirectory, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__FILES);
#endif

    t_boolean bFilesAll = false;
    int nestatics;
    C[0] = 0;
    if (bDirectory){
      STRING_EXPRESSION[0] = popStackString(&nestatics, &C[0]);
     
    }
    
    if (C[0] == pcode__QSTRING) myFunction->fFILES(bDirectory, (t_qstring) STRING_EXPRESSION[0]); // call the associated function
    else if (C[0] == pcode__CSTRING) myFunction->fFILES(bDirectory, (t_cstring) STRING_EXPRESSION[0]); // call the associated function
    else myFunction->fFILES(bDirectory, ""); // call the associated function

    if (bDirectory)  estatics->undeclare(nestatics);

  } // } else return pcodeError(utility::con(pcode::builtin_(pcode__FILES), " missing"));

  return;
}

void interpreter::fNAME()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif

  t_builtin name;

  myPcode->rd_NAME(&name);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__NAME);
#endif

    int nestatics[interpreter__MAX_PARAM];
    STRING_EXPRESSION[1] = popStackString(&nestatics[1], &C[1]);
    STRING_EXPRESSION[0] = popStackString(&nestatics[0], &C[0]);

    if (C[0] == pcode__QSTRING && C[1] == pcode__QSTRING) myFunction->fNAME((t_qstring) STRING_EXPRESSION[0], (t_qstring) STRING_EXPRESSION[1]); // call the associated function
    else if (C[0] == pcode__CSTRING && C[1] == pcode__CSTRING) myFunction->fNAME((t_cstring) STRING_EXPRESSION[0], (t_cstring) STRING_EXPRESSION[1]); // call the associated function
    else if (C[0] == pcode__QSTRING && C[1] == pcode__CSTRING){
      QString s = s.fromLocal8Bit((t_cstring) STRING_EXPRESSION[1]);
      myFunction->fNAME((t_qstring) STRING_EXPRESSION[0], &s); // call the associated function
    } else if (C[0] == pcode__CSTRING && C[1] == pcode__QSTRING){
      QString s = s.fromLocal8Bit((t_cstring) STRING_EXPRESSION[0]);
      myFunction->fNAME(&s, (t_qstring) STRING_EXPRESSION[1]); // call the associated function
    }

    estatics->undeclare(nestatics[1]);
    estatics->undeclare(nestatics[0]);

  } // } else return pcodeError(utility::con(pcode::builtin_(pcode__NAME), " missing"));

  return;
}

void interpreter::fKILL()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif

  t_builtin kill;

  myPcode->rd_KILL(&kill);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__KILL);
#endif

    int nestatics;
    t_pcode c;
    t_pointer q;
    q = popStackString(&nestatics, &c);
    
    if (c == pcode__QSTRING) myFunction->fKILL((t_qstring) q); // call the associated function
    else myFunction->fKILL((t_qstring) q); // call the associated function

    estatics->undeclare(nestatics);

  } // } else return pcodeError(utility::con(pcode::builtin_(pcode__KILL), " missing"));

  return;
}

void interpreter::fOPEN2()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif

  t_builtin open; t_boolean bLEN;

  myPcode->rd_OPEN2(&open, &bLEN);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__OPEN2);
#endif

    int nLen;
    nLen = 0;

    if (bLEN){
      nLen = popStackInteger();
    }
    int nestatics;
    STRING_EXPRESSION[2] = popStackString(&nestatics, &C[2]);

    int nFILEHANDLE;
    nFILEHANDLE = popStackInteger();

    const char *ac;
    int nestatics2;
    t_pcode c;
    t_pointer q;
    q = popStackString(&nestatics2, &c);
    
    int nMode;
    nMode = 0;

    if (C[2] == pcode__QSTRING && c == pcode__QSTRING){

      if (((t_qstring) q)->compare("I", Qt::CaseInsensitive) == 0){ 
        nMode = pcode__INPUT;
      } else if (((t_qstring) q)->compare("O", Qt::CaseInsensitive) == 0){ 
        nMode = pcode__OUTPUT;
      } else if (((t_qstring) q)->compare("A", Qt::CaseInsensitive) == 0){ 
        nMode = pcode__APPEND;
      } else if (((t_qstring) q)->compare("B", Qt::CaseInsensitive) == 0){ 
        nMode = pcode__BINARY;
      } else if (((t_qstring) q)->compare("R", Qt::CaseInsensitive) == 0){ 
        nMode = pcode__RANDOM;
      }

      myFunction->fOPEN((t_qstring) STRING_EXPRESSION[2], nMode, nFILEHANDLE, nLen); // call the associated function

    } else if (C[2] == pcode__CSTRING && c == pcode__CSTRING){

      if (utility::my_stricmp((t_cstring) q, "I") == 0){ 
        nMode = pcode__INPUT;
      } else if (utility::my_stricmp((t_cstring) q, "O") == 0){ 
        nMode = pcode__OUTPUT;
      } else if (utility::my_stricmp((t_cstring) q, "A") == 0){ 
        nMode = pcode__APPEND;
      } else if (utility::my_stricmp((t_cstring) q, "B") == 0){ 
        nMode = pcode__BINARY;
      } else if (utility::my_stricmp((t_cstring) q, "R") == 0){ 
        nMode = pcode__RANDOM;
      }

      myFunction->fOPEN((t_cstring) STRING_EXPRESSION[2], nMode, nFILEHANDLE, nLen); // call the associated function

    } else if (C[2] == pcode__QSTRING && c == pcode__CSTRING){

      if (utility::my_stricmp((t_cstring) q, "I") == 0){ 
        nMode = pcode__INPUT;
      } else if (utility::my_stricmp((t_cstring) q, "O") == 0){ 
        nMode = pcode__OUTPUT;
      } else if (utility::my_stricmp((t_cstring) q, "A") == 0){ 
        nMode = pcode__APPEND;
      } else if (utility::my_stricmp((t_cstring) q, "B") == 0){ 
        nMode = pcode__BINARY;
      } else if (utility::my_stricmp((t_cstring) q, "R") == 0){ 
        nMode = pcode__RANDOM;
      }

      myFunction->fOPEN((t_qstring) STRING_EXPRESSION[2], nMode, nFILEHANDLE, nLen); // call the associated function

    } else if (C[2] == pcode__CSTRING && c == pcode__QSTRING){

      if (((t_qstring) q)->compare("I", Qt::CaseInsensitive) == 0){ 
        nMode = pcode__INPUT;
      } else if (((t_qstring) q)->compare("O", Qt::CaseInsensitive) == 0){ 
        nMode = pcode__OUTPUT;
      } else if (((t_qstring) q)->compare("A", Qt::CaseInsensitive) == 0){ 
        nMode = pcode__APPEND;
      } else if (((t_qstring) q)->compare("B", Qt::CaseInsensitive) == 0){ 
        nMode = pcode__BINARY;
      } else if (((t_qstring) q)->compare("R", Qt::CaseInsensitive) == 0){ 
        nMode = pcode__RANDOM;
      }

      myFunction->fOPEN((t_cstring) STRING_EXPRESSION[2], nMode, nFILEHANDLE, nLen); // call the associated function

    }

     estatics->undeclare(nestatics);
     estatics->undeclare(nestatics2);

  } // } else return pcodeError(utility::con(pcode::builtin_(pcode__OPEN2), " missing"));

  return;
}

void interpreter::fOPEN()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif

  t_builtin open; t_integer nMode; t_integer nLock; t_integer nAccess; t_boolean bLEN;

  myPcode->rd_OPEN(&open, &nMode, &nLock, &nAccess, &bLEN);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__OPEN);
#endif    

    int nLen;
    nLen = 0;

    if (bLEN){
      nLen = popStackInteger();
    }

    int nFILEHANDLE;
    nFILEHANDLE = popStackInteger();

    int nestatics;
    t_pcode c;
    t_pointer q;
    q = popStackString(&nestatics, &c);
    if (c == pcode__QSTRING) myFunction->fOPEN((t_qstring) q, nMode, nFILEHANDLE, nLen); // call the associated function
    else myFunction->fOPEN((t_cstring) q, nMode, nFILEHANDLE, nLen); // call the associated function
    
    estatics->undeclare(nestatics);

  } // } else return pcodeError(utility::con(pcode::builtin_(pcode__OPEN), " missing"));

  return;
}

void interpreter::fSEEK()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif

  t_builtin c; t_boolean bReturn;

  myPcode->rd_SEEK(&c, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__SEEK);
#endif

    INTEGER_EXPRESSION[1] = popStackInteger();
    INTEGER_EXPRESSION[0] = popStackInteger(); //  manche parameter drehen, wegen performance in myfunctionaufruf  --> myFunction->fSEEK(EXPRESSION[1], EXPRESSION[0]  --> fSEEK(popStackInteger(), popStackInteger())

    myFunction->fSEEK(INTEGER_EXPRESSION[0], INTEGER_EXPRESSION[1]); // call the associated function
    
  } // } else return pcodeError(utility::con(pcode::builtin_(pcode__SEEK), " missing"));

  return;
}

void interpreter::fSEEK2()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif

  t_builtin c; t_boolean bReturn;

  myPcode->rd_SEEK2(&c, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__SEEK2);
#endif

    p = myFunction->fSEEK2(popStackInteger()); // call the associated function
    
    if (bReturn) pushStack(p); else delete p;    

  } // } else return pcodeError(utility::con(pcode::builtin_(pcode__SEEK2), " missing"));

  return;
}

void interpreter::fWRITE()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif

    
  t_builtin open; t_boolean bFILEHANDLE; t_integer expression_count;

  myPcode->rd_WRITE(&open, &bFILEHANDLE, &expression_count);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__WRITE);
#endif

  //  int nestatics[interpreter__MAX_PARAM];
    for (int i = 0; i < expression_count; i++){

      BOOLEAN_EXPRESSION[i] = popStackBoolean();
      EXPRESSION[i] = popStack();
      
    }

    int nFILEHANDLE;
    nFILEHANDLE = 0;

    if (bFILEHANDLE){
      nFILEHANDLE = popStackInteger();
    }

    for (int i = expression_count - 1; i >= 0; i--){

       myFunction->fPRINT(true, BOOLEAN_EXPRESSION[i],
       i == expression_count - 1, bFILEHANDLE, nFILEHANDLE, 
       "", true, 
       false, false, EXPRESSION[i], 0, 
       0, false, i == 0, false, false
      ); // call the associated function

    }

    for (int i = 0; i < expression_count; i++){

      delete EXPRESSION[i];
      
    }

  } // } else return pcodeError(utility::con(pcode::builtin_(pcode__WRITE), " missing"));

  return;
}

void interpreter::fEOF()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif

  t_builtin c; t_boolean bReturn;

  myPcode->rd_EOF(&c, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__EOF_);
#endif

    p = myFunction->fEOF(popStackInteger()); // call the associated function
    if (bReturn) pushStack(p); else delete p;

  } // } else return pcodeError(utility::con(pcode::builtin_(pcode__EOF_), " missing"));

  return;
}

void interpreter::fCLOSE()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif

  t_builtin close; t_integer nCount;

  myPcode->rd_CLOSE(&close, &nCount);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__CLOSE);
#endif

    int n;

    for (int i = 0; i < nCount; i++){

      myFunction->fCLOSE(popStackInteger()); // call the associated function
    }

  } // } else return pcodeError(utility::con(pcode::builtin_(pcode__CLOSE), " missing"));

  return;
}

void interpreter::fCLOSEALL()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif

  t_builtin closeall;

  myPcode->rd_CLOSEALL(&closeall);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__CLOSEALL);
#endif

    myFunction->fCLOSEALL(); // call the associated function

  } // } else return pcodeError(utility::con(pcode::builtin_(pcode__CLOSEALL), " missing"));

  return;
}



void interpreter::fSCREEN()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif

  t_builtin c; t_boolean bColor; t_boolean bOutputpage; t_boolean bVisiblepage;

  myPcode->rd_SCREEN(&c, &bColor, &bOutputpage, &bVisiblepage);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__SCREEN);
#endif

    /*
    if (bVisiblepage) INTEGER_EXPRESSION[3] = pop Stack();
    if (bOutputpage)  INTEGER_EXPRESSION[2] = pop Stack();
    if (bColor) INTEGER_EXPRESSION[1] = pop Stack();
    */

    int n;
    n = popStackInteger();

    if (n != 12){
      runtimeError("SCREEN: Sorry! Only 'SCREEN 12' is supported yet.");
      return;
    }

    myFunction->fSCREEN(n); // call the associated function    

 } // } else return pcodeError(utility::con(pcode::builtin_(pcode__SCREEN), " missing"));

  return;
}


void interpreter::fGET2()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin c; t_integer identifier; t_scope scope; t_boolean bStep1; t_boolean bStep2;

  myPcode->rd_GET2(&c, &identifier, &scope, &bStep1, &bStep2);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__GET2);
#endif

    //p = myFunction->fLOF(0); // call the associated function
    //if (bReturn) pushStack(p); else delete p;
    //

  } // } else return pcodeError(utility::con(pcode::builtin_(pcode__GET2), " missing"));

  return;
}

void interpreter::fPUT()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin c; t_integer identifier; t_scope scope; t_boolean bRecordNo;

  myPcode->rd_PUT(&c, &identifier, &scope, &bRecordNo);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__PUT);
#endif

    t_pcode cc;
    cc = myStack->peekPCode();
    t_pointer t;


      int nestatics = 0;
      t_pcode c = 0;
      t_pointer q;
 
    switch (cc){
         case pcode__ID:
              {
                myStack->popPCode();

               t_integer nVar2;// = 0;
               memory_variable2 *v2;// = 0;

                t_integer n;
                n = myStack->popID(&nVar2, &v2);

               t = v2->getStruct(n, movType_offset);

                break;
              }

         case pcode__QSTRING:
         case pcode__CSTRING:
         case pcode__EQSTRING:
         case pcode__ECSTRING:
              {
                q = popStackString(&nestatics, &c);
                break;
              }

         default:
           runtimeError("PUT: wrong datatype for PUT (file)");
           return;
           break;
    }    

    int nRecord;
    nRecord = 0;

    if (bRecordNo){ nRecord = popStackInteger(); }

    int nFILEHANDLE;
    nFILEHANDLE = popStackInteger();

    if (c == pcode__QSTRING){
      QByteArray a = ((t_qstring) q)->toUtf8();
      myFunction->fPUT(nFILEHANDLE, nRecord, bRecordNo, (const char *) a.data(), a.size()); // call the associated function
    }
    else if (c == pcode__CSTRING) myFunction->fPUT(nFILEHANDLE, nRecord, bRecordNo, (const char *) q, strlen((const char *) q)); // call the associated function
    else  myFunction->fPUT(nFILEHANDLE, nRecord, bRecordNo, (const char *) t); // call the associated function


    estatics->undeclare(nestatics);

  } // } else return pcodeError(utility::con(pcode::builtin_(pcode__PUT), " missing"));

  return;
}

void interpreter::fPUT2()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin c; t_integer identifier; t_scope scope; t_boolean bStep; t_integer nMode;

  myPcode->rd_PUT2(&c, &identifier, &scope, &bStep, &nMode);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__PUT2);
#endif


  } // } else return pcodeError(utility::con(pcode::builtin_(pcode__PUT2), " missing"));

  return;
}

void interpreter::fINSTREV()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin c; t_boolean bBegin; t_boolean bLastIndexOf; t_boolean bCase; t_boolean bReturn; t_boolean bObjectFake;

  myPcode->rd_INSTREV(&c, &bBegin, &bLastIndexOf, &bCase, &bReturn, &bObjectFake);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__INSTREV);
#endif
    
    int nestatics[interpreter__MAX_PARAM];

    t_boolean CaseSensitive = true;
    if (bCase){
      CaseSensitive = popStackBoolean();
    }

    int nBegin = -999;    

    if (bLastIndexOf){

      if (bBegin){
        nBegin = popStackInteger();
      }  

      STRING_EXPRESSION[1] = popStackString(&nestatics[1], &C[1]);
      STRING_EXPRESSION[0] = popStackString(&nestatics[0], &C[0]);

    } else {

      STRING_EXPRESSION[1] = popStackString(&nestatics[1], &C[1]);

      if (!bObjectFake){
        STRING_EXPRESSION[0] = popStackString(&nestatics[0], &C[0]);
      }

      if (bBegin){
        nBegin = popStackInteger();
      }

      if (bObjectFake){
        STRING_EXPRESSION[0] = popStackString(&nestatics[0], &C[0]);
      }

    } 

    register int n;
    if (C[0] == pcode__QSTRING) n = ((t_qstring) STRING_EXPRESSION[0])->length();
    else n = strlen((t_cstring) STRING_EXPRESSION[0]);
    
    if (nBegin == -999) nBegin = n;


    if (nBegin < 1){
      //runtimeError("INSTREV: begin < 1");
      pushStackInteger(0);
    estatics->undeclare(nestatics[1]);
    estatics->undeclare(nestatics[0]);
      return;
    }
    if (nBegin > (signed) n){
      pushStackInteger(0);
      //runtimeError("INSTREV: begin > length of string");
    estatics->undeclare(nestatics[1]);
    estatics->undeclare(nestatics[0]);

      return;
    }
    /*
    if (nBegin > (signed) strlen(acString) - (signed) strlen(acSearch)){
      return runtimeError("begin > length of string - search");
    }
    */

    if (C[0] == pcode__QSTRING && C[1] == pcode__QSTRING) p = myFunction->fINSTREV(bBegin, nBegin, (t_qstring) STRING_EXPRESSION[0], (t_qstring) STRING_EXPRESSION[1], CaseSensitive); // call the associated function
    else if (C[0] == pcode__CSTRING && C[1] == pcode__CSTRING) p = myFunction->fINSTREV(bBegin, nBegin, (t_cstring) STRING_EXPRESSION[0], (t_cstring) STRING_EXPRESSION[1], CaseSensitive); // call the associated function
    else if (C[0] == pcode__QSTRING && C[1] == pcode__CSTRING){
      QString s; s = s.fromLocal8Bit((t_cstring) STRING_EXPRESSION[1]);
      p = myFunction->fINSTREV(bBegin, nBegin, (t_qstring) STRING_EXPRESSION[0], &s, CaseSensitive); // call the associated function
    }
    else if (C[0] == pcode__CSTRING && C[1] == pcode__QSTRING){
      QString s; s = s.fromLocal8Bit((t_cstring) STRING_EXPRESSION[0]);
      p = myFunction->fINSTREV(bBegin, nBegin, &s, (t_qstring) STRING_EXPRESSION[1], CaseSensitive); // call the associated function
    }
    
    if (bReturn) pushStack(p); else delete p;   
    estatics->undeclare(nestatics[1]);
    estatics->undeclare(nestatics[0]);

  } // } else return pcodeError(utility::con(pcode::builtin_(pcode__INSTREV), " missing"));

  return;
}

void interpreter::fREPLACE()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin c; t_boolean bCase; t_boolean bReturn;

  myPcode->rd_REPLACE(&c, &bCase, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__REPLACE);
#endif

    t_boolean CaseSensitive = true;
    if (bCase){
      CaseSensitive = popStackBoolean();
    }

    //const char *acBy;
    int nestatics1;
    t_pcode c1;
    t_pointer q1;
    q1 = popStackString(&nestatics1, &c1);

    //const char *acPattern;
    int nestatics2;
    t_pcode c2;
    t_pointer q2;
    q2 = popStackString(&nestatics2, &c2);

    //const char *acString;
    int nestatics3;
    t_pcode c3;
    t_pointer q3;
    q3 = popStackString(&nestatics3, &c3);

    if (c1 == pcode__QSTRING && c2 == pcode__QSTRING && c3 == pcode__QSTRING) p = myFunction->fREPLACE((t_qstring) q3, (t_qstring) q2, (t_qstring) q1, CaseSensitive); // call the associated function
    else if (c1 == pcode__CSTRING && c2 == pcode__CSTRING && c3 == pcode__CSTRING){
      p = myFunction->fREPLACE((t_cstring) q3, (t_cstring) q2, (t_cstring) q1, CaseSensitive); // call the associated function
    }
    else if (c1 == pcode__QSTRING && c2 == pcode__QSTRING && c3 == pcode__CSTRING){
      QString s; s = s.fromLocal8Bit((t_cstring) q3);
      p = myFunction->fREPLACE(&s, (t_qstring) q2, (t_qstring) q1, CaseSensitive); // call the associated function
    } else if (c1 == pcode__QSTRING && c2 == pcode__CSTRING && c3 == pcode__QSTRING){
      QString s; s = s.fromLocal8Bit((t_cstring) q2);
      p = myFunction->fREPLACE((t_qstring) q3, &s, (t_qstring) q1, CaseSensitive); // call the associated function
    } else if (c1 == pcode__CSTRING && c2 == pcode__QSTRING && c3 == pcode__QSTRING){
      QString s; s = s.fromLocal8Bit((t_cstring) q1);
      p = myFunction->fREPLACE((t_qstring) q3, (t_qstring) q2, &s, CaseSensitive); // call the associated function
    } else if (c1 == pcode__CSTRING && c2 == pcode__CSTRING && c3 == pcode__QSTRING){
      QString s1; s1 = s1.fromLocal8Bit((t_cstring) q1);
      QString s2; s2 = s2.fromLocal8Bit((t_cstring) q2);
      p = myFunction->fREPLACE((t_qstring) q3, &s2, &s1, CaseSensitive); // call the associated function          
    } else if (c1 == pcode__QSTRING && c2 == pcode__CSTRING && c3 == pcode__CSTRING){
      QString s2; s2 = s2.fromLocal8Bit((t_cstring) q2);
      QString s3; s3 = s3.fromLocal8Bit((t_cstring) q3);
      p = myFunction->fREPLACE(&s3, &s2, (t_qstring) q1, CaseSensitive); // call the associated function
    } else if (c1 == pcode__CSTRING && c2 == pcode__QSTRING && c3 == pcode__CSTRING){
      QString s1; s1 = s1.fromLocal8Bit((t_cstring) q1);
      QString s3; s3 = s3.fromLocal8Bit((t_cstring) q3);
      p = myFunction->fREPLACE(&s3, (t_qstring) q2, &s1, CaseSensitive); // call the associated function      
    }

    if (bReturn) pushStack(p); else delete p;    
    estatics->undeclare(nestatics1);
    estatics->undeclare(nestatics2);
    estatics->undeclare(nestatics3);

  } // } else return pcodeError(utility::con(pcode::builtin_(pcode__REPLACE), " missing"));

  return;
}

void interpreter::fLOF()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin lof; t_boolean bReturn;

  myPcode->rd_LOF(&lof, &bReturn);
  
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__LOF);
#endif

    p = myFunction->fLOF(popStackInteger()); // call the associated function
    if (bReturn) pushStack(p); else delete p;
    
  } // } else return pcodeError(utility::con(pcode::builtin_(pcode__LOF), " missing"));

  return;
}

void interpreter::fISDATE()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin c; t_boolean bReturn;

  myPcode->rd_ISDATE(&c, &bReturn);
  
  {

#ifdef HAS_CONSOLE
    if (!bSilent){
      info2(nPos, pcode__ISDATE);
    }
#endif

    {
      t_pcode cType;

      cType = myStack->peekPCode();
      interpreter_parameter *pp;
    
      pp = popStack(); // stack muss ein element runternehmen, gilt auch fr isnumeric

      if (cType == pcode__DATE){ 
        if (bReturn) myStack->pushBoolean(true);
      } else {
        if (bReturn) myStack->pushBoolean(false);
      }
      delete pp;
      
    }

    return;
  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__ISDATE), " missing"));
}

void interpreter::fISEMPTY()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin c; t_integer identifier; t_scope scope; t_boolean bReturn;

  myPcode->rd_ISEMPTY(&c, &identifier, &scope, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent){
      const char *acModule, *acSub, *acVar;
      acModule = ""; acSub = ""; acVar = "";

      findVars(identifier, &acModule, &acSub, &acVar);

      info2(nPos, pcode__ISEMPTY);
      
    }
#endif

    
    {
      t_pcode cType;

      cType = myStack->peekPCode();
      interpreter_parameter *pp;

    
      pp = popStack(); // stack muss ein element runternehmen, gilt auch fr isnumeric

      if (cType == pcode__EMPTY){ 
        if (bReturn) myStack->pushBoolean(true);
      } else {        
        if (bReturn) myStack->pushBoolean(false);
      }
      delete pp;

      
    
    }

    return;
  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__ISARRAY), " missing"));
}

void interpreter::fISNULL()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin c; t_boolean bReturn;

  myPcode->rd_ISNULL(&c, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent)info2(nPos, pcode__ISNULL);
#endif

    {
      t_pcode cType;

      cType = myStack->popPCode();


		  t_pointer p;
      bool b44 = myStack->popBoolean();
      bool memory_variable2 = myStack->popBoolean();
      p = myStack->popPointer(); 

      if (memory_type::isClass(cType) || memory_type::isBinding(cType) || memory_type::isKBasic(cType)){

        if (p == 0){
          if (bReturn) myStack->pushBoolean(true);
        } else {
          if (bReturn) myStack->pushBoolean(false);
        }

      } else if (cType == pcode__OBJECT){

        if (p == 0){
          if (bReturn) myStack->pushBoolean(true);
        } else {
          if (bReturn) myStack->pushBoolean(false);
        }

      } else {
        if (bReturn) myStack->pushBoolean(false);
      }

    }

    return;
  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__ISNULL), " missing"));
}

void interpreter::fISNUMERIC()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin c; t_boolean bReturn;

  myPcode->rd_ISNUMERIC(&c, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent)info2(nPos, pcode__ISNUMERIC);
#endif    

    {
      t_pcode cType;

      cType = myStack->peekPCode();
      interpreter_parameter *pp;

     
      pp = popStack(); // stack muss ein element runternehmen, gilt auch fr isnumeric

      if (memory_type::isNumeric(cType)){ 
        if (bReturn) myStack->pushBoolean(true);
      } else {
        if (bReturn) myStack->pushBoolean(false);
      }

      delete pp;

    }

    return;
  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__ISNUMERIC), " missing"));
}

void interpreter::fISMISSING()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin c; t_integer identifier; t_scope scope; t_boolean bReturn;

  myPcode->rd_ISMISSING(&c, &identifier, &scope, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent){
      const char *acModule, *acSub, *acVar;
      acModule = ""; acSub = ""; acVar = "";

      findVars(identifier, &acModule, &acSub, &acVar);

      info2(nPos, pcode__ISMISSING);
      
    }
#endif

    bool b = getVar(scope)->isMissing(identifier);

    if (bReturn){
      myStack->pushBoolean(b);
    }

    return;
  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__ISMISSING), " missing"));
}

void interpreter::fISARRAY()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin c; t_integer identifier; t_scope scope; t_boolean bReturn;

  myPcode->rd_ISARRAY(&c, &identifier, &scope, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent){
      const char *acModule, *acSub, *acVar;
      acModule = ""; acSub = ""; acVar = "";

      findVars(identifier, &acModule, &acSub, &acVar);
      

      info2(nPos, pcode__ISARRAY);
      
    }
#endif

    bool b;
    b = getVar(scope)->isArray(identifier);

    if (bReturn){
      myStack->pushBoolean(b);
    }

    return;
  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__ISARRAY), " missing"));
}

void interpreter::fISBOOLEAN()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin c; t_integer identifier; t_scope scope; t_boolean bReturn;

  myPcode->rd_ISBOOLEAN(&c, &identifier, &scope, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent){
      const char *acModule, *acSub, *acVar;
      acModule = ""; acSub = ""; acVar = "";

      findVars(identifier, &acModule, &acSub, &acVar);

      info2(nPos, pcode__ISBOOLEAN);
      
    }
#endif

    {
      t_pcode cType;

      cType = myStack->peekPCode();
      interpreter_parameter *pp;
    
      pp = popStack(); // stack muss ein element runternehmen, gilt auch fr isnumeric

      if (cType == pcode__BOOLEAN){ 
        if (bReturn) myStack->pushBoolean(true);
      } else {
        if (bReturn) myStack->pushBoolean(false);
      }
      delete pp;

      
    }


    return;
  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__ISBOOLEAN), " missing"));
}

void interpreter::fISBYTE()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin c; t_integer identifier; t_scope scope; t_boolean bReturn;

  myPcode->rd_ISBYTE(&c, &identifier, &scope, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent){
      const char *acModule, *acSub, *acVar;
      acModule = ""; acSub; acVar = "";

      findVars(identifier, &acModule, &acSub, &acVar);

      info2(nPos, pcode__ISBYTE);
      
    }
#endif

    {
      t_pcode cType;

      cType = myStack->peekPCode();
      interpreter_parameter *pp;
     
      pp = popStack(); // stack muss ein element runternehmen, gilt auch fr isnumeric

      if (cType == pcode__BYTE){ 
        if (bReturn) myStack->pushBoolean(true);
      } else {
        if (bReturn) myStack->pushBoolean(false);
      }
      delete pp;

      
    }
    
    return;
  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__ISBYTE), " missing"));
}

void interpreter::fISSINGLE()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin c; t_integer identifier; t_scope scope; t_boolean bReturn;

  myPcode->rd_ISSINGLE(&c, &identifier, &scope, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent){
      const char *acModule, *acSub, *acVar;
      acModule = ""; acSub = ""; acVar = "";

      findVars(identifier, &acModule, &acSub, &acVar);

      info2(nPos, pcode__ISSINGLE);
      
    }
#endif

    {
      t_pcode cType;

      cType = myStack->peekPCode();
      interpreter_parameter *pp;
      
      pp = popStack(); // stack muss ein element runternehmen, gilt auch fr isnumeric

      if (cType == pcode__SINGLE){ 
        if (bReturn) myStack->pushBoolean(true);
      } else {
        if (bReturn) myStack->pushBoolean(false);
      }
      delete pp;


    }
    

    return;
  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__ISSINGLE), " missing"));
}

void interpreter::fISDOUBLE()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin c; t_integer identifier; t_scope scope; t_boolean bReturn;

  myPcode->rd_ISDOUBLE(&c, &identifier, &scope, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent){
      const char *acModule, *acSub, *acVar;
      acModule = ""; acSub = ""; acVar = "";

      findVars(identifier, &acModule, &acSub, &acVar);

      info2(nPos, pcode__ISDOUBLE);
      
    }
#endif


    {
      t_pcode cType;

      cType = myStack->peekPCode();
      interpreter_parameter *pp;
     
      pp = popStack(); // stack muss ein element runternehmen, gilt auch fr isnumeric

      if (cType == pcode__DOUBLE){ 
        if (bReturn) myStack->pushBoolean(true);
      } else {
        if (bReturn) myStack->pushBoolean(false);
      }
      delete pp;

      
     }
    
    return;
  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__ISDOUBLE), " missing"));
}

void interpreter::fISINTEGER()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin c; t_integer identifier; t_scope scope; t_boolean bReturn;

  myPcode->rd_ISINTEGER(&c, &identifier, &scope, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent){
      const char *acModule, *acSub, *acVar;
      acModule = ""; acSub = ""; acVar = "";

      findVars(identifier, &acModule, &acSub, &acVar);

      info2(nPos, pcode__ISINTEGER);
      
    }
#endif

    {
      t_pcode cType;

      cType = myStack->peekPCode();
      interpreter_parameter *pp;

     
      pp = popStack(); // stack muss ein element runternehmen, gilt auch fr isnumeric

      if (cType == pcode__INTEGER){ 
        if (bReturn) myStack->pushBoolean(true);
      } else {
        if (bReturn) myStack->pushBoolean(false);
      }
      delete pp;

      
    }
    

    return;
  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__ISINTEGER), " missing"));
}

/*
void interpreter::fISINT16()
{
  register int nPos = myPcode->getPos();

  t_builtin c; t_integer identifier; t_scope scope; t_boolean bReturn;

  myPcode->rd_ISINT16(&c, &identifier, &scope, &bReturn);
  {

    if (!bSilent){
      const char *acModule, *acSub, *acVar;
      acModule = ""; acSub = ""; acVar = "";

      findVars(identifier, &acModule, &acSub, &acVar);

      info2(nPos, pcode__ISINT16);
      
    }

    memory_variable *v;
    v = getVar(scope);

    bool b;
    b = v->type(identifier) == pcode__INT16;

    if (bReturn){
      myStack->pushBoolean(b);
    }

    return;
  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__ISINT16), " missing"));
}

void interpreter::fISINT32()
{
  register int nPos = myPcode->getPos();

  t_builtin c; t_integer identifier; t_scope scope; t_boolean bReturn;

  myPcode->rd_ISINT32(&c, &identifier, &scope, &bReturn);
  {

    if (!bSilent){
      const char *acModule, *acSub, *acVar;
      acModule = ""; acSub = ""; acVar = "";

      findVars(identifier, &acModule, &acSub, &acVar);

      info2(nPos, pcode__ISINT32);
      
    }

    memory_variable *v;
    v = getVar(scope);

    bool b;
    b = v->type(identifier) == pcode__INT32;

    if (bReturn){
      myStack->pushBoolean(b);
    }

    return;
  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__ISINT32), " missing"));
}

void interpreter::fISINT64()
{
  register int nPos = myPcode->getPos();

  t_builtin c; t_integer identifier; t_scope scope; t_boolean bReturn;

  myPcode->rd_ISINT64(&c, &identifier, &scope, &bReturn);
  {

    if (!bSilent){
      const char *acModule, *acSub, *acVar;
      acModule = ""; acSub = ""; acVar = "";

      findVars(identifier, &acModule, &acSub, &acVar);

      info2(nPos, pcode__ISINT64);
      
    }

    memory_variable *v;
    v = getVar(scope);

    bool b;
    b = v->type(identifier) == pcode__INT64;

    if (bReturn){
      myStack->pushBoolean(b);
    }

    return;
  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__ISINT64), " missing"));
}

void interpreter::fISUINT16()
{
  register int nPos = myPcode->getPos();

  t_builtin c; t_integer identifier; t_scope scope; t_boolean bReturn;

  myPcode->rd_ISUINT16(&c, &identifier, &scope, &bReturn);
  {

    if (!bSilent){
      const char *acModule, *acSub, *acVar;
      acModule = ""; acSub = ""; acVar = "";

      findVars(identifier, &acModule, &acSub, &acVar);

      info2(nPos, pcode__ISUINT16);
      
    }

    memory_variable *v;
    v = getVar(scope);

    bool b;
    b = v->type(identifier) == pcode__UINT16;

    if (bReturn){
      myStack->pushBoolean(b);
    }

    return;
  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__ISUINT16), " missing"));
}

void interpreter::fISUINT32()
{
  register int nPos = myPcode->getPos();

  t_builtin c; t_integer identifier; t_scope scope; t_boolean bReturn;

  myPcode->rd_ISUINT32(&c, &identifier, &scope, &bReturn);
  {

    if (!bSilent){
      const char *acModule = "", *acSub = "", *acVar = "";
      acModule = ""; acSub = ""; acVar = "";

      findVars(identifier, &acModule, &acSub, &acVar);

      info2(nPos, pcode__ISUINT32);
      
    }

    memory_variable *v;
    v = getVar(scope);

    bool b;
    b = v->type(identifier) == pcode__UINT32;

    if (bReturn){
      myStack->pushBoolean(b);
    }

    return;
  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__ISUINT32), " missing"));
}

void interpreter::fISUINT64()
{
  register int nPos = myPcode->getPos();

  t_builtin c; t_integer identifier; t_scope scope; t_boolean bReturn;

  myPcode->rd_ISUINT64(&c, &identifier, &scope, &bReturn);
  {

    if (!bSilent){
      const char *acModule, *acSub, *acVar;
      acModule = ""; acSub = ""; acVar = "";

      findVars(identifier, &acModule, &acSub, &acVar);

      info2(nPos, pcode__ISUINT64);
      
    }

    memory_variable *v;
    v = getVar(scope);

    bool b;
    b = v->type(identifier) == pcode__UINT64;

    if (bReturn){
      myStack->pushBoolean(b);
    }

    return;
  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__ISUINT64), " missing"));
}

*/
void interpreter::fISSHORT()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin c; t_integer identifier; t_scope scope; t_boolean bReturn;

  myPcode->rd_ISSHORT(&c, &identifier, &scope, &bReturn);
  {
#ifdef HAS_CONSOLE
    if (!bSilent){
      const char *acModule, *acSub, *acVar;
      acModule = ""; acSub = ""; acVar = "";

      findVars(identifier, &acModule, &acSub, &acVar);

      info2(nPos, pcode__ISSHORT);
      
    }
#endif
    {
      t_pcode cType;

      cType = myStack->peekPCode();
      interpreter_parameter *pp;

     // int nestatics = 0;
      pp = popStack(); // stack muss ein element runternehmen, gilt auch fr isnumeric

      if (cType == pcode__SHORT){ 
        if (bReturn) myStack->pushBoolean(true);
      } else {
        if (bReturn) myStack->pushBoolean(false);
      }
      delete pp;

      

    }
    

    return;
  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__ISSHORT), " missing"));
}
        
void interpreter::fISLONG()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin c; t_integer identifier; t_scope scope; t_boolean bReturn;

  myPcode->rd_ISLONG(&c, &identifier, &scope, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent){
      const char *acModule, *acSub, *acVar;
      acModule = ""; acSub = ""; acVar = "";

      findVars(identifier, &acModule, &acSub, &acVar);

      info2(nPos, pcode__ISLONG);
      
    }
#endif

    {
      t_pcode cType;

      cType = myStack->peekPCode();
      interpreter_parameter *pp;

   
      pp = popStack(); // stack muss ein element runternehmen, gilt auch fr isnumeric

      if (cType == pcode__LONG){ 
        if (bReturn) myStack->pushBoolean(true);
      } else {
        if (bReturn) myStack->pushBoolean(false);
      }
      delete pp;
    
      

    }
    

    return;
  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__ISLONG), " missing"));
}
     
void interpreter::fISSTRING()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin c; t_integer identifier; t_scope scope; t_boolean bReturn;

  myPcode->rd_ISSTRING(&c, &identifier, &scope, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent){
      const char *acModule, *acSub, *acVar;
      acModule = ""; acSub = ""; acVar = "";

      findVars(identifier, &acModule, &acSub, &acVar);

      info2(nPos, pcode__ISSTRING);
      
    }
#endif


    {
      t_pcode cType;

      cType = myStack->peekPCode();
      interpreter_parameter *pp;

    
      pp = popStack(); // stack muss ein element runternehmen, gilt auch fr isnumeric

      if (cType == pcode__QSTRING || cType == pcode__LQSTRING || cType == pcode__CSTRING || cType == pcode__LCSTRING){ 
        if (bReturn) myStack->pushBoolean(true);
      } else {
        if (bReturn) myStack->pushBoolean(false);
      }
      delete pp;

      
    
    }


    return;
  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__ISSTRING), " missing"));
}
  
void interpreter::fISVARIANT()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin c; t_integer identifier; t_scope scope; t_boolean bReturn;

  myPcode->rd_ISVARIANT(&c, &identifier, &scope, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent){
      const char *acModule, *acSub, *acVar;
      acModule = ""; acSub = ""; acVar = "";

      findVars(identifier, &acModule, &acSub, &acVar);

      info2(nPos, pcode__ISVARIANT);
      
    }
#endif

    memory_variable *v;
    v = getVar(scope);

    bool b;
    b = v->type(identifier) == pcode__VARIANT;

    if (bReturn){
      myStack->pushBoolean(b);
    }

    return;
  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__ISVARIANT), " missing"));
}

void interpreter::fTYPENAME()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin c; t_integer identifier; t_scope scope; t_boolean bReturn;

  myPcode->rd_TYPENAME(&c, &identifier, &scope, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent){
      const char *acModule, *acSub, *acVar;
      acModule = ""; acSub = ""; acVar = "";

      findVars(identifier, &acModule, &acSub, &acVar);

      info2(nPos, pcode__TYPENAME);
      
    }
#endif

    memory_variable *v;
    v = getVar(scope);

    int n;
    n = v->type(identifier);
    static QString s = "";

    t_array *a = 0;

    switch(n){
      case pcode__BOOLEAN: s = "Boolean"; break;

      case pcode__QSTRING: s = "String"; break;
      case pcode__CSTRING: s = "CString"; break;

      case pcode__BYTE: s = "Byte"; break;
      case pcode__SHORT:s = "Short"; break;
      case pcode__INTEGER: s = "Integer"; break;
      case pcode__LONG: s = "Long"; break;

      case pcode__DOUBLE: s = "Double"; break;
      case pcode__SINGLE: s = "Single"; break;

      case pcode__VARIANT: 
        switch (v->getVariantType(identifier)){
          case pcode__ERROR: s = "Error"; goto o;
          case pcode__EMPTY: s = "Empty"; goto o;
          default:
            if (v->getVariant_Object(identifier, 0) == 0){
              s = "Null"; 
              goto o;
            } else {
              s = "Variant"; 
            }
            break;
        }
        break;

      case pcode__OBJECT: s = "Object"; break;

      case pcode__CURRENCY: s = "Currency"; break;

      case pcode__DATE: s = "Date"; break;

      default:
        if (memory_type::isBinding(n)){
          s = pcode_kbasic_binding::classname_(n);
        } else if (memory_type::isClass(n)){
          s = myClass->getName(n);
        } else if (memory_type::isEnum(n)){
          s = myEnum->getName(n);
        } else if (memory_type::isType(n)){
          s = myType->getName(n);
        }        
        break;
    }

    a = v->getArray(identifier);
    if (a->count){
      s = s + "[]";
    }
o:
    if (bReturn){
      myStack->pushQString(&s);
    }

    return;
  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__TYPENAME), " missing"));
}

void interpreter::fISERROR()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin c; t_boolean bReturn;

  myPcode->rd_ISERROR(&c, &bReturn);
  
  {

    {
      t_pcode cType;

      cType = myStack->peekPCode();
      interpreter_parameter *pp;
    
      pp = popStack(); // stack muss ein element runternehme

      if (cType == pcode__ERROR){ 
        if (bReturn) myStack->pushBoolean(true);
      } else {
        if (bReturn) myStack->pushBoolean(false);
      }

      delete pp;
      

    }

    return;
  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__ISERROR), " missing"));
}


void interpreter::fISOBJECT()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin c; t_boolean bReturn;

  myPcode->rd_ISOBJECT(&c, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__ISOBJECT);
#endif

    {
      t_pcode cType;

      cType = myStack->peekPCode();
      interpreter_parameter *pp;
    
      pp = popStack(); // stack muss ein element runternehmen, gilt auch fr isnumeric

      if (memory_type::isObject(cType)){ 
        if (bReturn) myStack->pushBoolean(true);
      } else {
        if (bReturn) myStack->pushBoolean(false);
      }
      delete pp;
      
    }

    return;
  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__ISOBJECT), " missing"));
}

void interpreter::fISCURRENCY()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin c; t_boolean bReturn;

  myPcode->rd_ISCURRENCY(&c, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__ISCURRENCY);
#endif

    {
      t_pcode cType;

      cType = myStack->peekPCode();
      interpreter_parameter *pp;
    
      pp = popStack(); // stack muss ein element runternehmen, gilt auch fr isnumeric

      if (cType == pcode__CURRENCY){ 
        if (bReturn) myStack->pushBoolean(true);
      } else {
        if (bReturn) myStack->pushBoolean(false);
      }
      delete pp;
      
    }

    return;
  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__ISCURRENCY), " missing"));
}

void interpreter::fARRAY2() // array funktion    variant = Array(1, 2, 3)
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin c; t_boolean bReturn;

  myPcode->rd_ARRAY2(&c, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__ARRAY2);
#endif

    if (bReturn){
      myStack->pushPCode(pcode__ARRAY2);
    }

    return;
  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__ARRAY2), " missing"));
}

void interpreter::fCOMMAND()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin c; t_boolean bReturn;

  myPcode->rd_COMMAND(&c, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__COMMAND);
#endif

    p = myFunction->fCOMMAND(); // call the associated function

    if (bReturn) pushStack(p); else delete p;
    

    return;
  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__COMMAND), " missing"));
}

void interpreter::fCURDIR()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin c; t_boolean bEXPRESSION; t_boolean bReturn;
  myPcode->rd_CURDIR(&c, &bEXPRESSION, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__CURDIR);
#endif
    
    int nestatics;
    t_pcode c = 0;
    t_pointer q;

    if (bEXPRESSION){
      q = popStackString(&nestatics, &c);
    }

    // If no drive is specified or if drive is a zero-length string (""), 
    // CurDir returns the path for the current drive.

    if (c == pcode__QSTRING) p = myFunction->fCURDIR((t_qstring) q); // call the associated function
    else if (c == pcode__CSTRING) p = myFunction->fCURDIR((t_cstring) q); // call the associated function
    else p = myFunction->fCURDIR(""); // call the associated function
    
    if (bReturn) pushStack(p); else delete p;
    if (bEXPRESSION)  estatics->undeclare(nestatics);

    return;
  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__CURDIR), " missing"));
}

void interpreter::fCVERR()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin c; t_boolean bReturn;
  myPcode->rd_CVERR(&c, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__CVERR);
#endif

    INTEGER_EXPRESSION[0] = popStackInteger();

    myStack->pushError(INTEGER_EXPRESSION[0]);   

    return;
  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__CVERR), " missing"));
}

void interpreter::fDATEADD()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin c; t_boolean bReturn;
  myPcode->rd_DATEADD(&c, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__DATEADD);
#endif
        
    DATE_EXPRESSION[0] = popStack();
    INTEGER_EXPRESSION[0] = popStackInteger();
    int nestatics;
    STRING_EXPRESSION[0] = popStackString(&nestatics, &C[0]);

    if (C[0] == pcode__QSTRING) p = myFunction->fDATEADD((t_qstring) STRING_EXPRESSION[0], INTEGER_EXPRESSION[0], DATE_EXPRESSION[0]->toDate(true)); // call the associated function
    else p = myFunction->fDATEADD((t_cstring) STRING_EXPRESSION[0], INTEGER_EXPRESSION[0], DATE_EXPRESSION[0]->toDate(true)); // call the associated function
    
    if (bReturn) pushStack(p); else delete p;
    estatics->undeclare(nestatics);

    delete DATE_EXPRESSION[0];

    return;
  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__DATEADD), " missing"));
}

void interpreter::fDATEDIFF()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin c; t_boolean bFirstdayofweek; t_boolean bFirstweekofyear; t_boolean bReturn;
  myPcode->rd_DATEDIFF(&c, &bFirstdayofweek, &bFirstweekofyear, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__DATEDIFF);
#endif
        
    if (bFirstweekofyear) INTEGER_EXPRESSION[0] = popStackInteger(); else INTEGER_EXPRESSION[0] = -1;
    if (bFirstdayofweek) INTEGER_EXPRESSION[1] = popStackInteger(); else INTEGER_EXPRESSION[1] = -1;

    DATE_EXPRESSION[1] = popStack();
    DATE_EXPRESSION[0] = popStack();
    int nestatics;
    STRING_EXPRESSION[0] = popStackString(&nestatics, &C[0]);

    if (C[0] == pcode__QSTRING) p = myFunction->fDATEDIFF((t_qstring) STRING_EXPRESSION[0], DATE_EXPRESSION[0]->toDate(true), DATE_EXPRESSION[1]->toDate(true), INTEGER_EXPRESSION[0], INTEGER_EXPRESSION[1]); // call the associated function
    else p = myFunction->fDATEDIFF((t_cstring) STRING_EXPRESSION[0], DATE_EXPRESSION[0]->toDate(true), DATE_EXPRESSION[1]->toDate(true), INTEGER_EXPRESSION[0], INTEGER_EXPRESSION[1]); // call the associated function
    if (bReturn) pushStack(p); else delete p;
    estatics->undeclare(nestatics);

    delete DATE_EXPRESSION[1];
    delete DATE_EXPRESSION[0];

    return;
  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__DATEDIFF), " missing"));
}

void interpreter::fDATEPART()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin c; t_boolean bFirstdayofweek; t_boolean bFirstweekofyear; t_boolean bReturn;
  myPcode->rd_DATEPART(&c, &bFirstdayofweek, &bFirstweekofyear, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__DATEPART);
#endif    

    if (bFirstweekofyear) INTEGER_EXPRESSION[0] = popStackInteger(); else INTEGER_EXPRESSION[0] = -1;
    if (bFirstdayofweek) INTEGER_EXPRESSION[1] = popStackInteger(); else INTEGER_EXPRESSION[1] = -1;

    DATE_EXPRESSION[0] = popStack();
    int nestatics;
    STRING_EXPRESSION[0] = popStackString(&nestatics, &C[0]);

    t_integer n;
    
    if (C[0] == pcode__QSTRING) n = myFunction->fDATEPART((t_qstring) STRING_EXPRESSION[0], DATE_EXPRESSION[0]->toDate(), INTEGER_EXPRESSION[0], INTEGER_EXPRESSION[1]); // call the associated function
    else n = myFunction->fDATEPART((t_cstring) STRING_EXPRESSION[0], DATE_EXPRESSION[0]->toDate(), INTEGER_EXPRESSION[0], INTEGER_EXPRESSION[1]); // call the associated function

    if (bReturn) pushStackInteger(n);
    estatics->undeclare(nestatics);

    return;
  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__DATEPART), " missing"));
}

void interpreter::fDATESERIAL()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin c; t_boolean bReturn;

  myPcode->rd_DATESERIAL(&c, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__DATESERIAL);
#endif
        
    INTEGER_EXPRESSION[2] = popStackInteger();
    INTEGER_EXPRESSION[1] = popStackInteger();
    INTEGER_EXPRESSION[0] = popStackInteger();

    t_date n =  myFunction->fDATESERIAL(INTEGER_EXPRESSION[0], INTEGER_EXPRESSION[1], INTEGER_EXPRESSION[2]); // call the associated function
    if (bReturn) pushStack(new interpreter_parameter(n));
    
    return;
  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__DATESERIAL), " missing"));
}

void interpreter::fDATEVALUE()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin c; t_boolean bReturn;

  myPcode->rd_DATEVALUE(&c, &bReturn);
  {
#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__DATEVALUE);   
#endif

    EXPRESSION[0] = popStack();

    if (bReturn) pushStack(new interpreter_parameter(EXPRESSION[0]->toDate(true)));

    delete EXPRESSION[0];
    
    return;
  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__DATEVALUE), " missing"));
}

void interpreter::fDAY()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin c; t_boolean bReturn;

  myPcode->rd_DAY(&c, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__DAY);
#endif
    
    EXPRESSION[0] = popStack();

    t_long l = myFunction->fDAY(EXPRESSION[0]->toDate(true)); // call the associated function
    if (bReturn) pushStackLong(l);

    delete EXPRESSION[0];

    return;
  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__DAY), " missing"));
}

void interpreter::fDIR()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin c; t_boolean bEXPRESSION; t_boolean bEXPRESSION2; t_boolean bReturn;

  myPcode->rd_DIR(&c, &bEXPRESSION, &bEXPRESSION2, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__DIR);
#endif
    
    static int nType = 0;
    
    STRING_EXPRESSION[0] = (void *) "";

    if (bEXPRESSION2){
      nType = popStackInteger();
    }
    
    int nestatics;
    t_pcode c = 0;
    if (bEXPRESSION){
      STRING_EXPRESSION[0] = popStackString(&nestatics, &c);
      if (!bEXPRESSION2){
        nType = 0;
      }
    }
    
    if (c == pcode__QSTRING) p = myFunction->fDIR((t_qstring) STRING_EXPRESSION[0], nType); // call the associated function
    else if (c == pcode__CSTRING) p = myFunction->fDIR((t_cstring) STRING_EXPRESSION[0], nType); // call the associated function
    else p = myFunction->fDIR("", nType); // call the associated function

    if (bReturn) pushStack(p); else delete p;
    if (bEXPRESSION) estatics->undeclare(nestatics);

    return;
  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__DIR), " missing"));
}

void interpreter::fFILEATTR()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin c; t_boolean bReturn;

  myPcode->rd_FILEATTR(&c, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__FILEATTR);
#endif
    
    INTEGER_EXPRESSION[0] = popStackInteger();
    INTEGER_EXPRESSION[1] = popStackInteger();

    p = myFunction->fFILEATTR(INTEGER_EXPRESSION[1], INTEGER_EXPRESSION[0]); // call the associated function     

    if (bReturn) pushStack(p); else delete p;
    
    return;
  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__FILEATTR), " missing"));
}

void interpreter::fFILEDATETIME()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin c; t_boolean bReturn;

  myPcode->rd_FILEDATETIME(&c, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__FILEDATETIME);
#endif
    
    int nestatics;
    STRING_EXPRESSION[0] = popStackString(&nestatics, &C[0]);

    t_date d;
    if (C[0] == pcode__QSTRING) d = myFunction->fFILEDATETIME((t_qstring) STRING_EXPRESSION[0]); // call the associated function
    else d = myFunction->fFILEDATETIME((t_cstring) STRING_EXPRESSION[0]); // call the associated function

    if (bReturn) pushStack(new interpreter_parameter(d));
    estatics->undeclare(nestatics);
    
    return;
  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__FILEDATETIME), " missing"));
}

void interpreter::fFILELEN()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin c; t_boolean bReturn;

  myPcode->rd_FILELEN(&c, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__FILELEN);
#endif
    
    int nestatics;
    t_pcode c;
    t_pointer q;
    q = popStackString(&nestatics, &c);
    if (c == pcode__QSTRING) p = myFunction->fFILELEN((t_qstring) q); // call the associated function    
    else  p = myFunction->fFILELEN((t_cstring) q); // call the associated function    

    if (bReturn) pushStack(p); else delete p;
    estatics->undeclare(nestatics);
    
    return;
  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__FILELEN), " missing"));
}

void interpreter::fFORMAT()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif

  t_builtin c; t_boolean bFORMAT; t_boolean bFillChar; t_boolean bRightAligned; t_boolean bReturn;

  myPcode->rd_FORMAT(&c, &bFORMAT, &bFillChar, &bRightAligned, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__FORMAT);
#endif
    
    int nestatics0 = 0;
    int nestatics1 = 0;
    int nestatics2 = 0;

    QString s0;// = ""; 
    QString s1;// = ""; 

    if (bRightAligned) BOOLEAN_EXPRESSION[0] = popStackBoolean();
    if (bFillChar){
      STRING_EXPRESSION[0] = popStackString(&nestatics0, &C[0]);
    } else {
      s0 = " "; 
    }
    if (bFORMAT) STRING_EXPRESSION[1] = popStackString(&nestatics1, &C[1]);



    if (bFillChar){
      if (C[0] == pcode__CSTRING){
        s0 = s0.fromLocal8Bit((t_cstring) STRING_EXPRESSION[0]);
      } else {
        s0 = *((t_qstring) STRING_EXPRESSION[0]);
      }
    }

    if (C[1] == pcode__CSTRING){
      s1 = s1.fromLocal8Bit((t_cstring) STRING_EXPRESSION[1]);
    } else {
      s1 = *((t_qstring) STRING_EXPRESSION[1]);
    }
    
    p = myFunction->fFORMAT(popStack(), &s1, &s0, BOOLEAN_EXPRESSION[0]); // call the associated function

    if (bReturn) pushStack(p); else delete p;

    estatics->undeclare(nestatics0);
    estatics->undeclare(nestatics1);
    estatics->undeclare(nestatics2);


    return;
  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__FORMAT), " missing"));
}

void interpreter::fFORMATCURRENCY()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin c; t_boolean bFORMAT; t_boolean bFirstdayofweek; t_boolean bFirstweekofyear; t_boolean bReturn;

  myPcode->rd_FORMAT(&c, &bFORMAT, &bFirstdayofweek, &bFirstweekofyear, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__FORMAT);
#endif
    
    if (bFirstweekofyear) EXPRESSION[0] = popStack();
    if (bFirstdayofweek) EXPRESSION[1] = popStack();
    if (bFORMAT) EXPRESSION[2] = popStack();

    if (bFirstweekofyear) delete EXPRESSION[0];
    if (bFirstdayofweek) delete EXPRESSION[1];
    if (bFORMAT) delete EXPRESSION[2];


    return;
  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__FORMAT), " missing"));
}

void interpreter::fFORMATDATETIME()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin c; t_boolean bFORMAT; t_boolean bFirstdayofweek; t_boolean bFirstweekofyear; t_boolean bReturn;

  myPcode->rd_FORMAT(&c, &bFORMAT, &bFirstdayofweek, &bFirstweekofyear, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__FORMAT);
#endif
    
    if (bFirstweekofyear) EXPRESSION[0] = popStack();
    if (bFirstdayofweek) EXPRESSION[1] = popStack();
    if (bFORMAT) EXPRESSION[2] = popStack();

    if (bFirstweekofyear) delete EXPRESSION[0];
    if (bFirstdayofweek) delete EXPRESSION[1];
    if (bFORMAT) delete EXPRESSION[2];


    return;
  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__FORMAT), " missing"));
}

void interpreter::fFORMATNUMBER()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin c; t_boolean bFORMAT; t_boolean bFirstdayofweek; t_boolean bFirstweekofyear; t_boolean bReturn;

  myPcode->rd_FORMAT(&c, &bFORMAT, &bFirstdayofweek, &bFirstweekofyear, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__FORMAT);
#endif
    
    if (bFirstweekofyear) EXPRESSION[0] = popStack();
    if (bFirstdayofweek) EXPRESSION[1] = popStack();
    if (bFORMAT) EXPRESSION[2] = popStack();

    if (bFirstweekofyear) delete EXPRESSION[0];
    if (bFirstdayofweek) delete EXPRESSION[1];
    if (bFORMAT) delete EXPRESSION[2];
  

    return;
  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__FORMAT), " missing"));
}

void interpreter::fFORMATPERCENT()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin c; t_boolean bFORMAT; t_boolean bFirstdayofweek; t_boolean bFirstweekofyear; t_boolean bReturn;

  myPcode->rd_FORMAT(&c, &bFORMAT, &bFirstdayofweek, &bFirstweekofyear, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__FORMAT);
#endif
    
    if (bFirstweekofyear) EXPRESSION[0] = popStack();
    if (bFirstdayofweek) EXPRESSION[1] = popStack();
    if (bFORMAT) EXPRESSION[2] = popStack();

    if (bFirstweekofyear) delete EXPRESSION[0];
    if (bFirstdayofweek) delete EXPRESSION[1];
    if (bFORMAT) delete EXPRESSION[2];
 
    return;
  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__FORMAT), " missing"));
}

void interpreter::fWEEKDAYNAME()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin c; t_boolean bFORMAT; t_boolean bFirstdayofweek; t_boolean bFirstweekofyear; t_boolean bReturn;

  myPcode->rd_WEEKDAYNAME(&c, &bFORMAT, &bFirstdayofweek, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__FORMAT);
#endif
    
    if (bFirstdayofweek) INTEGER_EXPRESSION[0] = popStackInteger(); else INTEGER_EXPRESSION[0] = -1;
    if (bFORMAT) BOOLEAN_EXPRESSION[0] = popStackBoolean(); else BOOLEAN_EXPRESSION[0] = false;

    INTEGER_EXPRESSION[1] = popStackInteger();

     t_qstring s = myFunction->fWEEKDAYNAME(INTEGER_EXPRESSION[1], BOOLEAN_EXPRESSION[0], INTEGER_EXPRESSION[0]); // call the associated function
     if (bReturn) pushStackQString(s); 

    return;
  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__FORMAT), " missing"));
}

void interpreter::fFREEFILE()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin c; t_boolean bRange; t_boolean bReturn;

  myPcode->rd_FREEFILE(&c, &bRange, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__FREEFILE);
#endif
    
    int n;
    n = 0;

    if (bRange){
      n = popStackInteger();
    }

    p = myFunction->fFREEFILE(n); // call the associated function
    if (bReturn) pushStack(p); else delete p;    

    return;
  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__FREEFILE), " missing"));
}

void interpreter::fGETATTR()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin c; t_boolean bReturn;

  myPcode->rd_GETATTR(&c, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__GETATTR);
#endif
        
    int nestatics;
    STRING_EXPRESSION[0] = popStackString(&nestatics, &C[0]);

    if (C[0] == pcode__QSTRING) p = myFunction->fGETATTR((t_qstring) STRING_EXPRESSION[0]); // call the associated function     
    else p = myFunction->fGETATTR((t_cstring) STRING_EXPRESSION[0]); // call the associated function     

    if (bReturn) pushStack(p); else delete p;
    estatics->undeclare(nestatics);

    return;
  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__GETATTR), " missing"));
}

void interpreter::fHOUR()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin c; t_boolean bReturn;

  myPcode->rd_HOUR(&c, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__HOUR);
#endif
    
    EXPRESSION[0] = popStack();

    t_long l =  myFunction->fHOUR(EXPRESSION[0]->toDate(true)); // call the associated function
    if (bReturn) pushStackLong(l);

    delete EXPRESSION[0];

    return;
  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__HOUR), " missing"));
}

void interpreter::fINPUTBOX()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin c; t_boolean title; t_boolean default_; t_boolean bReturn;

  myPcode->rd_INPUTBOX(&c, &title, &default_, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__INPUTBOX);
#endif
        
    int nestatics[interpreter__MAX_PARAM];
    if (default_) STRING_EXPRESSION[2] = popStackString(&nestatics[2], &C[2]); else STRING_EXPRESSION[2] = 0;
    if (title) STRING_EXPRESSION[1] = popStackString(&nestatics[1], &C[1]);

    STRING_EXPRESSION[0] = popStackString(&nestatics[0], &C[0]);

    QString s2 = ""; 
    QString s1 = ""; 
    QString s0 = ""; 

    if (default_){
      if (C[2] == pcode__CSTRING){
        s2 = s2.fromLocal8Bit((t_cstring) STRING_EXPRESSION[2]);
      } else {
        s2 = *((t_qstring) STRING_EXPRESSION[2]);
      }
    }
    if (title){
      if (C[1] == pcode__CSTRING){
        s1 = s1.fromLocal8Bit((t_cstring) STRING_EXPRESSION[1]);
      } else {
        s1 = *((t_qstring) STRING_EXPRESSION[1]);
      }
    }
    if (C[0] == pcode__CSTRING){
      s0 = s0.fromLocal8Bit((t_cstring) STRING_EXPRESSION[0]);
    } else {
      s0 = *((t_qstring) STRING_EXPRESSION[0]);
    }



    bool ok;
  QString text;
  
  text = QInputDialog::getText(0, 
           title ? s1 : sProjectName.isEmpty() ? "KBasic" : sProjectName, 
            s0, QLineEdit::Normal,
            s2, &ok, 0 );


    // user entered something and pressed OK
    if ( ok && !text.isEmpty() ) {
      if (bReturn){
				 int nId = estatics->declare(pcode__QSTRING, 0, false, false);
    		 estatics->setQString(nId, &text, 0);
  				myStack->pushEQString(nId);
      }      
        
    // user entered nothing or pressed Cancel
    } else {
        if (bReturn) pushStackQString(&kbNullQString);        
    }

     if (default_) estatics->undeclare(nestatics[2]);
     if (title) estatics->undeclare(nestatics[1]);
     estatics->undeclare(nestatics[0]);

    return;
  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__INPUTBOX), " missing"));
}

void interpreter::fMSGBOX()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin c; t_boolean buttons; t_boolean title; t_boolean bReturn;

  myPcode->rd_MSGBOX(&c, &buttons, &title, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__MSGBOX);
#endif

    QString s0;
    QString s1;
    
    int nestatics = 0;
    if (title){
      STRING_EXPRESSION[1] = popStackString(&nestatics, &C[1]);
      if (C[1] == pcode__QSTRING) s1 = *((t_qstring) STRING_EXPRESSION[1]);
      else s1 = (t_cstring) STRING_EXPRESSION[1];
    }
    int n = 0;
    if (buttons) n = popStackInteger();

    //int nestatics2 = 0;
    EXPRESSION[0] = popStack();
    s0 = EXPRESSION[0]->toQString();

    delete EXPRESSION[0];


    //bool kbOKOnly = (n & 0) == 0;
    bool kbOKCancel = (n & 1) == 1;
    bool kbAbortRetryIgnore = (n & 2) == 2;
    bool kbYesNoCancel = (n & 3) == 3;
    bool kbYesNo = (n & 4) == 4;
    bool kbRetryCancel = (n & 5) == 5;

    bool kbOKOnly = !kbOKCancel && !kbAbortRetryIgnore && !kbYesNoCancel && !kbYesNo && !kbRetryCancel;

    bool kbInformation = (n & 64) == 64;
    bool kbExclamation = kbInformation ? false : (n & 48) == 48;
    bool kbQuestion = kbExclamation | kbInformation ? false : (n & 32) == 32;
    bool kbCritical = kbExclamation | kbInformation | kbQuestion ? false : (n & 16) == 16;

    bool kbDefaultButton1 = n & 0;
    bool kbDefaultButton2 = (n & 256) == 256;
    bool kbDefaultButton3 = (n & 512) == 512;

    int k0 = QMessageBox::NoIcon;
    int k1 = QMessageBox::Yes | QMessageBox::Default;
    int k2 = QMessageBox::NoButton;
    int k3 = QMessageBox::NoButton;

    if (kbCritical) k0 = QMessageBox::Critical;
    else if (kbQuestion) k0 = QMessageBox::Question;
    else if (kbExclamation) k0 = QMessageBox::Warning;
    else if (kbInformation) k0 = QMessageBox::Information;
    
    if (kbOKOnly){
      k1 = QMessageBox::Ok | QMessageBox::Escape;
    } else if (kbOKCancel){
      k1 = QMessageBox::Ok;
      k2 = QMessageBox::Cancel | QMessageBox::Escape;
    } else if (kbAbortRetryIgnore){
      k1 = QMessageBox::Abort;
      k2 = QMessageBox::Retry | QMessageBox::Escape;
      k3 = QMessageBox::Ignore;
    } else if (kbYesNoCancel){
      k1 = QMessageBox::Yes;
      k2 = QMessageBox::No;
      k3 = QMessageBox::Cancel | QMessageBox::Escape;
    } else if (kbYesNo){
      k1 = QMessageBox::Yes;
      k2 = QMessageBox::No | QMessageBox::Escape;
    } else if (kbRetryCancel){
      k1 = QMessageBox::Retry;
      k2 = QMessageBox::Cancel | QMessageBox::Escape;
    }

    if (kbDefaultButton1) k1 = k1 | QMessageBox::Default;
    else if (kbDefaultButton2) k2 = k2 | QMessageBox::Default;
    else if (kbDefaultButton3) k3 = k3 | QMessageBox::Default;

    QWidget *ww = qApp->activeWindow();
    
    QMessageBox mb((QMessageBox::Icon) k0, title ? s1 : sProjectName.isEmpty() ? "KBasic" : sProjectName, 
      s0,    
        (QMessageBox::StandardButton) (k1| k2 | k3), ww
        );


    if (kbOKOnly){
      mb.setButtonText( QMessageBox::Yes, QObject::tr("&OK") );
    } else if (kbOKCancel){
      mb.setButtonText( QMessageBox::Yes, QObject::tr("&OK") );
      mb.setButtonText( QMessageBox::No, QObject::tr("&Cancel") );
    } else if (kbAbortRetryIgnore){
      mb.setButtonText( QMessageBox::Yes, QObject::tr("&Abort") );
      mb.setButtonText( QMessageBox::No, QObject::tr("&Retry") );
      mb.setButtonText( QMessageBox::Cancel, QObject::tr("&Ignore") );
    } else if (kbYesNoCancel){
      mb.setButtonText( QMessageBox::Yes, QObject::tr("&Yes") );
      mb.setButtonText( QMessageBox::No, QObject::tr("&No") );
      mb.setButtonText( QMessageBox::Cancel, QObject::tr("&Cancel") );
    } else if (kbYesNo){
      mb.setButtonText( QMessageBox::Yes, QObject::tr("&Yes") );
      mb.setButtonText( QMessageBox::No, QObject::tr("&No") );
    } else if (kbRetryCancel){
      mb.setButtonText( QMessageBox::Yes, QObject::tr("&Retry") );
      mb.setButtonText( QMessageBox::No, QObject::tr("&Cancel") );
    }

    switch( mb.exec() ) {
    case QMessageBox::Ok:
        if (bReturn) pushStackInteger(1);
        return;
        break;
    case QMessageBox::Cancel:
        if (bReturn) pushStackInteger(2);
        return;
        break;
    case QMessageBox::Abort:
        if (bReturn) pushStackInteger(3);
        return;
        break;    
    case QMessageBox::Retry:
        if (bReturn) pushStackInteger(4);
        return;
        break;
    case QMessageBox::Ignore:
        if (bReturn) pushStackInteger(5);
        return;
        break;
    case QMessageBox::Yes:
        if (bReturn) pushStackInteger(6);
        return;
        break;
    case QMessageBox::No:
        if (bReturn) pushStackInteger(7);
        return;
        break;
    default:
      internalError("unknown return code for MsgBox");
      break;

    }

    estatics->undeclare(nestatics);

    return;
  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__MSGBOX), " missing"));
}

void interpreter::fLOC()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin c; t_boolean bReturn;

  myPcode->rd_LOC(&c, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__LOC);
#endif
    
    p = myFunction->fLOC(popStackInteger()); // call the associated function
    if (bReturn) pushStack(p); else delete p;    

    return;
  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__LOC), " missing"));
}

void interpreter::fMINUTE()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin c; t_boolean bReturn;

  myPcode->rd_MINUTE(&c, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__MINUTE);
#endif
    
    EXPRESSION[0] = popStack();

    t_long l =  myFunction->fMINUTE(EXPRESSION[0]->toDate(true)); // call the associated function
    if (bReturn) pushStackLong(l);

    delete EXPRESSION[0];

    return;
  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__MINUTE), " missing"));
}

void interpreter::fMONTH()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin c; t_boolean bReturn;

  myPcode->rd_MONTH(&c, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__MONTH);
#endif
    
    EXPRESSION[0] = popStack();

   t_long l =  myFunction->fMONTH(EXPRESSION[0]->toDate(true)); // call the associated function
   if (bReturn) pushStackLong(l);

   delete EXPRESSION[0];

    return;
  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__MONTH), " missing"));
}

void interpreter::fSECOND()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin c; t_boolean bReturn;

  myPcode->rd_SECOND(&c, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__SECOND);
#endif
    
    EXPRESSION[0] = popStack();

    t_long l =  myFunction->fSECOND(EXPRESSION[0]->toDate(true)); // call the associated function
   if (bReturn) pushStackLong(l);

   delete EXPRESSION[0];

    return;
  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__SECOND), " missing"));
}

void interpreter::fNOW()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin c; t_boolean bReturn;

  myPcode->rd_NOW(&c, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__NOW);
#endif

    p = myFunction->fNOW(); // call the associated function
    if (bReturn) pushStack(p); else delete p;

    return;
  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__NOW), " missing"));
}

void interpreter::fTIMER()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin c; t_boolean bReturn;

  myPcode->rd_TIMER(&c, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__TIMER);
#endif

    p = myFunction->fTIMER(); // call the associated function
    if (bReturn) pushStack(p); else delete p;
    


    return;
  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__TIMER), " missing"));
}

void interpreter::fRGB()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin c; t_boolean bReturn;

  myPcode->rd_RGB(&c, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__RGB);
#endif
    
    INTEGER_EXPRESSION[2] = popStackInteger();
    INTEGER_EXPRESSION[1] = popStackInteger();
    INTEGER_EXPRESSION[0] = popStackInteger();

    p = myFunction->fRGB(INTEGER_EXPRESSION[0], INTEGER_EXPRESSION[1], INTEGER_EXPRESSION[2]); // call the associated function
    if (bReturn) pushStack(p); else delete p;
    
    return;
  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__RGB), " missing"));
}

void interpreter::fTIMESERIAL()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin c; t_boolean bReturn;

  myPcode->rd_TIMESERIAL(&c, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__TIMESERIAL);
#endif
    
    INTEGER_EXPRESSION[2] = popStackInteger();
    INTEGER_EXPRESSION[1] = popStackInteger();
    INTEGER_EXPRESSION[0] = popStackInteger();

    t_date n =  myFunction->fTIMESERIAL(INTEGER_EXPRESSION[0], INTEGER_EXPRESSION[1], INTEGER_EXPRESSION[2]); // call the associated function
    if (bReturn) pushStack(new interpreter_parameter(n));

    return;
  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__TIMESERIAL), " missing"));
}

void interpreter::fTIMEVALUE()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin c; t_boolean bReturn;

  myPcode->rd_TIMEVALUE(&c, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__TIMEVALUE);
#endif
    
    EXPRESSION[0] = popStack();

    if (bReturn) pushStack(new interpreter_parameter(EXPRESSION[0]->toDate(true)));

    delete EXPRESSION[0];
    
    return;
  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__TIMEVALUE), " missing"));
}

void interpreter::fWEEKDAY()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin c; t_boolean firstdayofweek; t_boolean bReturn;

  myPcode->rd_WEEKDAY(&c, &firstdayofweek, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__WEEKDAY);
#endif

    if (firstdayofweek) runtimeError("WEEKDAY: Sorry! FirstDayOfWeek not supported yet. Try to change the data calculation.");
    
    EXPRESSION[0] = popStack();

    t_integer n = myFunction->fWEEKDAY(EXPRESSION[0]->toDate(true)); // call the associated function
    if (bReturn) pushStackInteger(n); 

    delete EXPRESSION[0];

    return;
  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__WEEKDAY), " missing"));
}     

void interpreter::fCIRCLE()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin c; t_boolean color; t_boolean start; t_boolean end; t_boolean aspect;

  myPcode->rd_CIRCLE(&c, &color, &start, &end, &aspect);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__CIRCLE);
#endif
    
    EXPRESSION[0] = popStack();
    delete EXPRESSION[0];

    // 

    //if (bReturn) pushStack(p); else delete p;
    //
    
    return;
  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__CIRCLE), " missing"));
}

void interpreter::fDRAW()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin c;

  myPcode->rd_DRAW(&c);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__DRAW);
#endif
    
    EXPRESSION[0] = popStack();
    delete EXPRESSION[0];

    return;
  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__DRAW), " missing"));
}

void interpreter::fPCOPY()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin c;

  myPcode->rd_PCOPY(&c);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__PCOPY);
#endif
    
    EXPRESSION[0] = popStack();
    delete EXPRESSION[0];

    return;
  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__PCOPY), " missing"));
}

void interpreter::fPMAP()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin c;

  myPcode->rd_PMAP(&c);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__PMAP);
#endif
    
    EXPRESSION[0] = popStack();
    delete EXPRESSION[0];

    return;
  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__PMAP), " missing"));
}

void interpreter::fWIDTH()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin c;

  myPcode->rd_WIDTH(&c);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__WIDTH);
#endif
    
    EXPRESSION[0] = popStack();
    delete EXPRESSION[0];

    return;
  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__WIDTH), " missing"));
}

void interpreter::fPRESET()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin c; t_boolean bStep; t_boolean bColor;

  myPcode->rd_PRESET(&c, &bStep, &bColor);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__PRESET);
#endif
    
    EXPRESSION[0] = popStack();
    delete EXPRESSION[0];

    return;
  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__PRESET), " missing"));
}

void interpreter::fPSET()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin c; t_boolean bStep; t_boolean bColor;

  myPcode->rd_PSET(&c, &bStep, &bColor);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__PSET);
#endif
    
    int n;

    if (bColor){
      n = popStackInteger();
    } else n = 0;

    INTEGER_EXPRESSION[1] = popStackInteger();
    INTEGER_EXPRESSION[0] = popStackInteger();

    // call the associated function
    myFunction->fPSET(bStep, INTEGER_EXPRESSION[0], INTEGER_EXPRESSION[1], bColor, n); 

    return;
  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__PSET), " missing"));
}

void interpreter::fPAINT()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin c; t_boolean color; t_boolean pattern; t_boolean bordercolor; t_boolean background;

  myPcode->rd_PAINT(&c, &color, &pattern, &bordercolor, &background);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__PAINT);
#endif
    
    EXPRESSION[0] = popStack();
    delete EXPRESSION[0];

    return;
  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__PAINT), " missing"));
}

void interpreter::fWINDOW()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin c; t_boolean bScreen; t_boolean bExpression;

  myPcode->rd_WINDOW(&c, &bScreen, &bExpression);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__WINDOW);
#endif
    
    EXPRESSION[0] = popStack();
    delete EXPRESSION[0];

    return;
  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__WINDOW), " missing"));
}

void interpreter::fVIEWPRINT()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin c;

  myPcode->rd_VIEWPRINT(&c);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__VIEWPRINT);
#endif   
    

    EXPRESSION[0] = popStack();
    delete EXPRESSION[0];

    return;
  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__VIEWPRINT), " missing"));
}

void interpreter::fVIEW()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin c; t_boolean bSCREEN; t_boolean color; t_boolean border;

  myPcode->rd_VIEW(&c, &bSCREEN, &color, &border);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__VIEW);
#endif
    
    

    EXPRESSION[0] = popStack();
    delete EXPRESSION[0];
    

    return;
  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__VIEW), " missing"));
}

void interpreter::fLINE()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin c; t_boolean bSTEP; t_boolean bEXPRESSION; t_boolean bSTEP2; t_boolean color; t_boolean b; t_boolean bf; t_boolean style;

  myPcode->rd_LINE(&c, &bSTEP, &bEXPRESSION, &bSTEP2, &color, &b, &bf, &style);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__LINE);
#endif
    
    if (bSTEP){ // 
    }

    if (bSTEP2){
    }

    int n5;
    int n4;
    int n3;
    int n2;

    if (style){
      n5 = popStackInteger();
    } else n5 = 0;

    if (color){
      n4 =popStackInteger();
    } else n4 = 0;

    if (bEXPRESSION){
      n3 = popStackInteger();
      n2 = popStackInteger();
    } else {
      n3 = 0;
      n2 = 0;
    }

    INTEGER_EXPRESSION[1] = popStackInteger();
    INTEGER_EXPRESSION[0] = popStackInteger();


    // call the associated function
     myFunction->fLINE(bSTEP, INTEGER_EXPRESSION[0], INTEGER_EXPRESSION[1], 
       bSTEP2, bEXPRESSION, n2, n3, 
       color, n4, b, bf, style, n5); 

    return;
  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__LINE), " missing"));
}

void interpreter::fSCREEN2()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin c; t_boolean bColor; t_boolean bReturn;

  myPcode->rd_SCREEN2(&c, &bColor, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__SCREEN2);
#endif
    
    

    EXPRESSION[0] = popStack();
    delete EXPRESSION[0];  

    return;
  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__SCREEN2), " missing"));
}

void interpreter::fPOINT()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin c; t_boolean bColor; t_boolean bReturn;

  myPcode->rd_POINT(&c, &bColor, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__POINT);
#endif
    
    

    EXPRESSION[0] = popStack();
    delete EXPRESSION[0];

    return;
  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__POINT), " missing"));
}

void interpreter::fYEAR()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin c; t_boolean bReturn;

  myPcode->rd_YEAR(&c, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__YEAR);
#endif
    
    

    EXPRESSION[0] = popStack();

    t_long l =  myFunction->fYEAR(EXPRESSION[0]->toDate(true)); // call the associated function
    if (bReturn) pushStackLong(l);

    delete EXPRESSION[0];

    return;
  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__YEAR), " missing"));
}

void interpreter::fSTRREVERSE()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin c; t_boolean bReturn;

  myPcode->rd_STRREVERSE(&c, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__STRREVERSE);
#endif
    
    int nestatics;
    t_pcode c;
    t_pointer q = popStackString(&nestatics, &c);
    if (c == pcode__QSTRING) p = myFunction->fSTRREVERSE((t_qstring) q); // call the associated function
    else p = myFunction->fSTRREVERSE((t_cstring) q); // call the associated function

    if (bReturn) pushStack(p); else delete p;

    estatics->undeclare(nestatics);
    
    return;
  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__STRREVERSE), " missing"));
}

void interpreter::fSPC()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin c; t_boolean bReturn;

  myPcode->rd_SPC(&c, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__SPC);
#endif
    
    p = myFunction->fSPACE(popStackInteger()); // call the associated function
    if (bReturn) pushStack(p); else delete p;

    return;
  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__SPC), " missing"));
}

void interpreter::fSETATTR()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin c;

  myPcode->rd_SETATTR(&c);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__SETATTR);
#endif
    
    int nestatics = 0;
    EXPRESSION[0] = popStack();
    EXPRESSION[1] = popStack();
    
    delete EXPRESSION[0];
    delete EXPRESSION[1];

    //not supported yet
    //myFunction->fSETATTR(&EXPRESSION[1]->toQString(), EXPRESSION[0]->toInteger()); // call the associated function     

   // estatics->undeclare(nestatics);

    return;
  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__SETATTR), " missing"));
}

void interpreter::fCHDRIVE()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin c;

  myPcode->rd_CHDRIVE(&c);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__CHDRIVE);
#endif
    
   
    EXPRESSION[0] = popStack();
        
    myFunction->fCHDRIVE(&EXPRESSION[0]->toQString()); // call the associated function            

    delete EXPRESSION[0];
    


    return;
  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__CHDRIVE), " missing"));
}

void interpreter::fPRINTSCREEN()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin c;

  myPcode->rd_PRINTSCREEN(&c);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__PRINTSCREEN);
#endif
    
    EXPRESSION[0] = popStack();
        
    myFunction->fPRINTSCREEN(EXPRESSION[0]->toBoolean()); // call the associated function            

    delete EXPRESSION[0];

    return;
  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__PRINTSCREEN), " missing"));
}

void interpreter::fFILECOPY()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin c; t_boolean bReturn;

  myPcode->rd_FILECOPY(&c, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__FILECOPY);
#endif
    
    //int nestatics[interpreter__MAX_PARAM];
    EXPRESSION[1] = popStack();
    EXPRESSION[0] = popStack();

    QString s0 = EXPRESSION[0]->toQString();
    QString s1 = EXPRESSION[1]->toQString();

    delete EXPRESSION[0];
    delete EXPRESSION[1];

    t_boolean b = myFunction->fFILECOPY(&s0, &s1); // call the associated function   

    if (bReturn) pushStack(new interpreter_parameter(b)); else delete p;

  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__FILECOPY), " missing"));
}

void interpreter::fSPLIT()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin c; t_boolean bKeepEmptyParts; t_boolean bCaseSensitive; t_boolean bReturn;

  myPcode->rd_SPLIT(&c, &bKeepEmptyParts, &bCaseSensitive, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__SPLIT);
#endif
    
    
    if (bCaseSensitive){
      bCaseSensitive = popStackBoolean();
    } else bCaseSensitive = true;
    
    if (bKeepEmptyParts){
      bKeepEmptyParts = popStackBoolean();
    } else bKeepEmptyParts = true;
    

    int nestatics2;
    t_pcode c2;
    t_pointer q2;

    q2 = popStackString(&nestatics2, &c2);

    QString s2;
    if (c2 == pcode__CSTRING){
      s2 = QString::fromLocal8Bit((t_cstring) q2);
      q2 = &s2;
    }

    int nestatics;
    t_pcode c;
    t_pointer q;

    q = popStackString(&nestatics, &c);

    QString s;
    if (c == pcode__CSTRING){
      s = QString::fromLocal8Bit((t_cstring) q);
      q = &s;
    }

    p = myFunction->fSPLIT((t_qstring) q, (t_qstring) q2, bKeepEmptyParts, bCaseSensitive); // call the associated function
            
    if (bReturn) pushStack(p); else delete p;

    estatics->undeclare(nestatics);
    estatics->undeclare(nestatics2);

    

    return;
  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__SPLIT), " missing"));
}

void interpreter::fROUND()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin c; t_boolean bDigit; t_boolean bReturn;

  myPcode->rd_ROUND(&c, &bDigit, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__ROUND);
#endif
    
    int nDigit = 0;
    if (bDigit){
      nDigit = popStackInteger();
    }
    p = myFunction->fROUND(popStack(), nDigit); // call the associated function
    if (bReturn) pushStack(p); else delete p;    

    return;
  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__ROUND), " missing"));
}

void interpreter::fFRE()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin fre; t_boolean bEXPRESSION; t_boolean bNUMERIC_EXPRESSION; t_boolean bReturn;

  myPcode->rd_FRE(&fre, &bEXPRESSION, &bNUMERIC_EXPRESSION, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info(nPos, pcode__FRE);
#endif
    
    int nestatics = 0;

    int n;
    n = 0;
    switch(bNUMERIC_EXPRESSION){
      case false:
        if (bEXPRESSION){
          t_pcode c;
          STRING_EXPRESSION[0] = popStackString(&nestatics, &c);
        }
        n = 0;
        break;
      case true:
        n = popStackInteger();
        break;
    }
    
    switch(n){
      case 0:
        n = 0xffff;
        break;
      case -1:
        n = 0xffff;
        break;
      case -2:
        n = 0xffff;
        break;
    }

    if (bReturn){
      myStack->pushLong(n);
    }

    if (nestatics)  estatics->undeclare(nestatics);
    
    return;

  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__FRE), " missing"));
}

void interpreter::fINPUT()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin input; t_boolean bEXPRESSION0; t_boolean bSEMICOL; t_boolean bSTRING_EXPRESSION; t_boolean bCOMMA; t_boolean bSEMICOL2; t_integer nID; t_scope scope; t_integer nType; t_boolean bReturn;

  myPcode->rd_INPUT(&input, &bEXPRESSION0, &bSEMICOL, &bSTRING_EXPRESSION, &bCOMMA, &bSEMICOL2, &nID, &scope, &nType, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__INPUT);
#endif

    //  1. semicolon prevent EOL after pressing return.
    //  If the 2. semicolon is replaced by a comma, no question mark will be displayed
    bool bQuestionMark;
    bQuestionMark = (bCOMMA == false);

    bool bNewLine;
    bNewLine = bSEMICOL;

    int nestatics = 0;
    t_pcode c;
    t_pointer q = 0;
    if (bSTRING_EXPRESSION){
      q = popStackString(&nestatics, &c);
    }

    if (c == pcode__QSTRING) p = myFunction->fINPUT((t_qstring) q, bQuestionMark, bNewLine, nType); // call the associated function
    else  p = myFunction->fINPUT((t_cstring) q, bQuestionMark, bNewLine, nType); // call the associated function
    pushStack(p);

    estatics->undeclare(nestatics);
//no:
    switch(nType){
        case pcode__BOOLEAN: fMOV_BOOLEAN(nID, scope); break;

        case pcode__SINGLE: fMOV_SINGLE(nID, scope); break;
        case pcode__DOUBLE: fMOV_DOUBLE(nID, scope); break;
/*
        case pcode__INT16: 
        case pcode__INT32: 
        case pcode__INT64: 
        case pcode__UINT16: 
        case pcode__UINT32: 
        case pcode__UINT64: */
        case pcode__BYTE: 
        case pcode__SHORT: 
        case pcode__INTEGER: 
          fMOV_INTEGER(nID, scope); break;
        case pcode__LONG: fMOV_LONG(nID, scope); break;

        case pcode__QSTRING: fMOV_QSTRING(nID, scope); break;
        case pcode__CSTRING: fMOV_CSTRING(nID, scope); break;

        case pcode__CURRENCY: fMOV_CURRENCY(nID, scope); break;

        default:
          pcodeError("wrong datatype");
          return;
          break;
    }
    
    

  } // } else return pcodeError(utility::con(pcode::builtin_(pcode__INPUT), " missing"));

  return;
}

void interpreter::fSTRCOMP()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin strcomp; t_boolean bReturn; t_boolean bMode; t_boolean bBinary;

  myPcode->rd_STRCOMP(&strcomp, &bMode, &bBinary, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__STRCOMP);
#endif

    int n;

    if (bMode){ n = popStackInteger(); } else n = bBinary ? 0 : 1; // compare binary, binary is default

    int nestatics[interpreter__MAX_PARAM];
  
    STRING_EXPRESSION[1] = popStackString(&nestatics[1], &C[1]);
    STRING_EXPRESSION[0] = popStackString(&nestatics[0], &C[0]);

    p = 0;
    
    if (n != 0 && n != 1){
      runtimeError("STRCOMP: mode is unexpected");
      return;
    }

    //if (bMode)  
    if (C[0] == pcode__QSTRING && C[1] == pcode__QSTRING) p = myFunction->fSTRCOMP((t_qstring) STRING_EXPRESSION[0], (t_qstring) STRING_EXPRESSION[1], n); // call the associated function
    else if (C[0] == pcode__CSTRING && C[1] == pcode__CSTRING) p = myFunction->fSTRCOMP((t_cstring) STRING_EXPRESSION[0], (t_cstring) STRING_EXPRESSION[1], n); // call the associated function
    else if (C[0] == pcode__QSTRING && C[1] == pcode__CSTRING){
      QString s1 = (t_cstring) STRING_EXPRESSION[1];
      p = myFunction->fSTRCOMP((t_qstring) STRING_EXPRESSION[0], &s1, n); // call the associated function
    } else if (C[0] == pcode__CSTRING && C[1] == pcode__QSTRING){
      QString s0 = (t_cstring) STRING_EXPRESSION[0];
      p = myFunction->fSTRCOMP(&s0, (t_qstring) STRING_EXPRESSION[1], n); // call the associated function
    }

    if (bReturn) pushStack(p); else delete p;  

     estatics->undeclare(nestatics[1]);
     estatics->undeclare(nestatics[0]);

  } // } else return pcodeError(utility::con(pcode::builtin_(pcode__STRCOMP), " missing"));

  return;
}

void interpreter::fMID2()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin mid2; t_integer identifier; t_scope scope; t_boolean bLen;

  myPcode->rd_MID2(&mid2, &identifier, &scope, &bLen);
  {

#ifdef HAS_CONSOLE
    if (!bSilent){
      const char *acModule, *acSub, *acVar;
      acModule = ""; acSub = ""; acVar = "";

      findVars(identifier, &acModule, &acSub, &acVar);

      CONSOLE pcodePrintSep("");
      CONSOLE pcodePrintPos(nPos);
      CONSOLE pcodePrintOpc(pcode::builtin_(pcode__MID));
      CONSOLE pcodePrintVar(acModule, acSub, acVar);
      CONSOLE pcodePrint("= ...");
      CONSOLE pcodePrintCR();
      
    }   
#endif

    int offset;
    offset = getOffset(identifier, scope);

    int nestatics;
    t_pcode c;
    t_pointer q;
    

    q = popStackString(&nestatics, &c);
    
    int n2;
    n2 = 0;

    if (bLen){ 
      n2 = popStackInteger();
    }

    int n;
    n = popStackInteger();

    if (n <= 0){      
      runtimeError("MID: 1st argument <= 0");
      return;
    }

    if (n2 < 0){
      runtimeError("MID: 2nd argument < 0");
      return;
    }

    if (c == pcode__QSTRING){

      int nType = getVar(scope)->type(identifier);

      if (nType == pcode__QSTRING || nType == pcode__LQSTRING){
        if (bLen) myFunction->fMID2(getVar(scope)->getQString(identifier, offset), (t_qstring) q, n, n2); // call the associated function
        else  myFunction->fMID2(getVar(scope)->getQString(identifier, offset), (t_qstring) q, n); // call the associated function
      } else {
        static QByteArray a = ((t_qstring) q)->toLocal8Bit();
        char *ac = a.data();
        if (bLen) myFunction->fMID2(getVar(scope)->getCString(identifier, offset), ac, n, n2); // call the associated function
        else  myFunction->fMID2(getVar(scope)->getCString(identifier, offset), ac, n); // call the associated function
      }

    } else {

      int nType = getVar(scope)->type(identifier);

      if (nType == pcode__QSTRING || nType == pcode__LQSTRING){
        QString s = s.fromLocal8Bit((t_cstring) q);
        if (bLen) myFunction->fMID2(getVar(scope)->getQString(identifier, offset), &s, n, n2); // call the associated function
        else  myFunction->fMID2(getVar(scope)->getQString(identifier, offset), &s, n); // call the associated function
      } else {
        if (bLen) myFunction->fMID2(getVar(scope)->getCString(identifier, offset), (t_cstring) q, n, n2); // call the associated function
        else  myFunction->fMID2(getVar(scope)->getCString(identifier, offset), (t_cstring) q, n); // call the associated function
      }

    }

    estatics->undeclare(nestatics);

  } // } else return pcodeError(utility::con(pcode::builtin_(pcode__MID2), " missing"));

  return;
}


void interpreter::fINPUT2()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin c; t_boolean bFIRST; 
  t_integer identifier[parser__MAX_INPUT]; t_scope scope[parser__MAX_INPUT]; 
  t_integer count; t_boolean bReturn;

  int nFILEHANDLE;
  nFILEHANDLE = 0;

  int i;
  i = 0;

  do {
    myPcode->rd_INPUT2(&c, &bFIRST, &identifier[i], &scope[i], &count, &bReturn);
    {

#ifdef HAS_CONSOLE
      if (!bSilent) info2(nPos, pcode__INPUT2);         
#endif

      if (bFIRST){
        nFILEHANDLE = popStackInteger();
      }

    }

    i++;

  } while (i < count);
  

  for (int i = 0; i < count; i++){
    p = myFunction->fINPUT2(nFILEHANDLE); // call the associated function
      

    memory_variable *v;
    v = getVar(scope[i]);

    int nType = v->type(identifier[i]);
    
    if (nType == pcode__QSTRING || nType == pcode__LQSTRING){

      QString ss; ss = ss.fromUtf8(p->toCString());

      myStack->pushQString(&ss);

      fMOV(pcode__MOV_QSTRING, identifier[i], scope[i]);

    } else {

      myStack->pushCString(p->toCString());

      fMOV(pcode__MOV_CSTRING, identifier[i], scope[i]);

    }

  }

  return;
}

void interpreter::fINSTR()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin instr; t_boolean bReturn; t_boolean bIndexOf; t_boolean bCase; t_boolean bBegin; t_boolean bObjectFake;

  myPcode->rd_INSTR(&instr, &bBegin, &bIndexOf, &bCase, &bReturn, &bObjectFake);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__INSTR);
#endif

    int nestatics[interpreter__MAX_PARAM];

    t_boolean CaseSensitive = true;
    if (bCase){
      CaseSensitive = popStackBoolean();
    }
    int nBegin = 1;

    nestatics[0] = 0;
    nestatics[1] = 0;

    if (bIndexOf){

      if (bBegin){
        nBegin = popStackInteger();
      }  

      STRING_EXPRESSION[1] = popStackString(&nestatics[1], &C[1]);
      STRING_EXPRESSION[0] = popStackString(&nestatics[0], &C[0]);

    } else {

      STRING_EXPRESSION[1] = popStackString(&nestatics[1], &C[1]);

      if (!bObjectFake){
        STRING_EXPRESSION[0] = popStackString(&nestatics[0], &C[0]);
      }

      if (bBegin){
        nBegin = popStackInteger();
      }  

      if (bObjectFake){
        STRING_EXPRESSION[0] = popStackString(&nestatics[0], &C[0]);
      }

    }

    if (nBegin < 1){
      //runtimeError("INSTR: begin < 1");
      pushStackInteger(0);
      
     estatics->undeclare(nestatics[1]);
     estatics->undeclare(nestatics[0]);

      return;
    }
    int n;
    if (C[0] == pcode__QSTRING) n = ((t_qstring) STRING_EXPRESSION[0])->length();
    else n = strlen((t_cstring) STRING_EXPRESSION[0]);

    if (n == 0)
    {
      if (bReturn){
        pushStack(new interpreter_parameter(0));
      }
      
     estatics->undeclare(nestatics[1]);
     estatics->undeclare(nestatics[0]);


      return;
    }


    if (nBegin > (signed) n){
      pushStackInteger(0);
      //runtimeError("INSTR: begin > length of string");

      estatics->undeclare(nestatics[1]);
      estatics->undeclare(nestatics[0]);

      return;
    }
    int n2;
    if (C[1] == pcode__QSTRING) n2 = ((t_qstring) STRING_EXPRESSION[1])->length();
    else n2 = strlen((t_cstring) STRING_EXPRESSION[1]);

    if (nBegin > (signed) n + (signed) n2){
      runtimeError("INSTR: begin > length of string + search");

     estatics->undeclare(nestatics[1]);
     estatics->undeclare(nestatics[0]);

      return;
    }

    if (C[0] == pcode__QSTRING && C[1] == pcode__QSTRING) p = myFunction->fINSTR(bBegin, nBegin, (t_qstring) STRING_EXPRESSION[0], (t_qstring) STRING_EXPRESSION[1], CaseSensitive); // call the associated function
    else if (C[0] == pcode__CSTRING && C[1] == pcode__CSTRING) p = myFunction->fINSTR(bBegin, nBegin, (t_cstring) STRING_EXPRESSION[0], (t_cstring) STRING_EXPRESSION[1], CaseSensitive); // call the associated function
    else if (C[0] == pcode__QSTRING && C[1] == pcode__CSTRING){
      QString s; s = s.fromLocal8Bit((t_cstring) STRING_EXPRESSION[1]);
      p = myFunction->fINSTR(bBegin, nBegin, (t_qstring) STRING_EXPRESSION[0], &s, CaseSensitive); // call the associated function
    } else if (C[0] == pcode__CSTRING && C[1] == pcode__QSTRING){
      QString s; s = s.fromLocal8Bit((t_cstring) STRING_EXPRESSION[0]);
      p = myFunction->fINSTR(bBegin, nBegin, &s, (t_qstring) STRING_EXPRESSION[1], CaseSensitive); // call the associated function
    }
    
    if (bReturn) pushStack(p); else delete p;

     estatics->undeclare(nestatics[1]);
     estatics->undeclare(nestatics[0]);

    
  } // } else return pcodeError(utility::con(pcode::builtin_(pcode__INSTR), " missing"));

  return;
}

void interpreter::fINKEY()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin inkey; t_boolean bReturn;

  myPcode->rd_INKEY(&inkey, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__INKEY);
#endif

    int nKeyPressed;
    nKeyPressed = 0;

    p = myFunction->fINKEY(&nKeyPressed); // call the associated function
   
    switch(nKeyPressed){
      case 1:
        if (bReturn) pushStack(new interpreter_parameter((t_cstring) ""));
     //   delete p;
        break;
      case 2:
        if (bReturn) pushStack(new interpreter_parameter((t_boolean) false)); // 
     //   delete p;
        break;
      case 3:
        if (bReturn) pushStack(p); else delete p;
        break;
      
    }
    

  } // } else return pcodeError(utility::con(pcode::builtin_(pcode__INKEY), " missing"));

  return;
}

void interpreter::fLINEINPUT()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif

  t_builtin c; t_integer identifier; t_scope scope;

  myPcode->rd_LINEINPUT(&c, &identifier, &scope);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__LINEINPUT);
#endif

    p = myFunction->fLINEINPUT(popStackInteger()); // call the associated function
    
    memory_variable *v;
    v = getVar(scope);

    int nType = v->type(identifier);
    
    if (nType == pcode__QSTRING || nType == pcode__LQSTRING){

      QString ss; ss = ss.fromUtf8(p->toCString());

      myStack->pushQString(&ss);

      fMOV(pcode__MOV_QSTRING, identifier, scope);

    } else {

      myStack->pushCString(p->toCString());

      fMOV(pcode__MOV_CSTRING, identifier, scope);

    }

    delete p;

  } // } else return pcodeError(utility::con(pcode::builtin_(pcode__LINEINPUT), " missing"));

  return;
}

void interpreter::fNZ()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif

  t_builtin c; t_boolean bReturn;

  myPcode->rd_NZ(&c, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__NZ);
#endif

    int nestatics = 0;
    const char *s;
    t_pcode c;
    t_pointer q;
    q = popStackString(&nestatics, &c);

    if (bReturn){

      if (q == 0){

        pushStack(new interpreter_parameter((t_cstring) ""));
      } else {
        if (c == pcode__QSTRING) pushStack(new interpreter_parameter((t_qstring) q));
        else if (c == pcode__CSTRING) pushStack(new interpreter_parameter((t_cstring) q));
      }

    }
    estatics->undeclare(nestatics);

  } // } else return pcodeError(utility::con(pcode::builtin_(pcode__NZ), " missing"));

  return;
}

void interpreter::fGET()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin c; t_integer identifier; t_scope scope; t_boolean bRecordNo; t_boolean bIDENTIFIER;

  myPcode->rd_GET(&c, &identifier, &scope, &bRecordNo, &bIDENTIFIER);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__GET);
#endif

    int nRecord;
    nRecord = 0;


    if (bRecordNo){ nRecord = popStackInteger(); }

    int nFILEHANDLE;
    nFILEHANDLE = popStackInteger();

    char *ac = myFunction->fGET(nFILEHANDLE, nRecord, bRecordNo); // call the associated function

    if (ac){
  
      myStack->pushBuffer((t_pointer) ac, myFunction->getRecordSizeFile(nFILEHANDLE));

        if (bIDENTIFIER){
          fMOV(pcode__MOV_TYPE, identifier, scope);
        
        }
    }

  } // } else return pcodeError(utility::con(pcode::builtin_(pcode__GET), " missing"));

  return;
}

void interpreter::fPOKE()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin c;// t_integer identifier; t_scope scope;

  myPcode->rd_POKE(&c/*, &identifier, &scope*/);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__POKE);
#endif


    int nSize = popStackInteger();

    t_pcode cc;
    cc = myStack->peekPCode();
    t_pointer t;

    switch (cc){
         case pcode__ID:
              {
                myStack->popPCode();

               t_integer nVar2;// = 0;
               memory_variable2 *v2;// = 0;

                t_integer n;
                n = myStack->popID(&nVar2, &v2);

               t = v2->getStruct(n, movType_offset);

                break;
              }


         default:
           runtimeError("POKE: wrong datatype for POKE");
           return;
           break;
    }    


    int nestatics;
    t_pcode c;
    t_pointer q;

    q = popStackString(&nestatics, &c);

    if (c == pcode__QSTRING){
      QByteArray a = ((t_qstring) q)->toUtf8();
      myFunction->fPOKE((const char *) a.data(), a.size(), (const char *) t, nSize); // call the associated function
    }
    else myFunction->fPOKE((const char *) q, strlen((const char *) q), (const char *) t, nSize); // call the associated function


    estatics->undeclare(nestatics);

  } // } else return pcodeError(utility::con(pcode::builtin_(pcode__PUT), " missing"));

  return;
}

void interpreter::fPEEK()
{
  
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin c; t_integer identifier; t_scope scope;

  myPcode->rd_PEEK(&c, &identifier, &scope);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__PEEK);
#endif


    int nSize = popStackInteger();

    t_pcode cc;
    cc = myStack->peekPCode();
    t_pointer t = 0;

    switch (cc){
         case pcode__ID:
              {
                myStack->popPCode();

               t_integer nVar2;// = 0;
               memory_variable2 *v2;// = 0;

                t_integer n;
                n = myStack->popID(&nVar2, &v2);

               t = v2->getStruct(n, movType_offset);

                break;
              }

         default:
           runtimeError("PEEK: wrong datatype for PEEK");
           return;
           break;
    }    

    if (t){
  
      myStack->pushBuffer(t, nSize);

        
        {
          fMOV(pcode__MOV_TYPE, identifier, scope);
       
        }
    }

  } // } else return pcodeError(utility::con(pcode::builtin_(pcode__GET), " missing"));

  return;
}

void interpreter::fCAST()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin c; t_integer nType; t_integer nType2; t_boolean bEXPRESSION; t_boolean bEXPRESSION2; t_boolean bEXPRESSION3; t_boolean bEXPRESSION4; t_boolean bEXPRESSION5; t_boolean bReturn;

  myPcode->rd_CAST(&c, &nType, &nType2, &bEXPRESSION, &bEXPRESSION2, &bEXPRESSION3, &bEXPRESSION4, &bEXPRESSION5, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__CAST);
#endif
    int nestatics[interpreter__MAX_PARAM];

    nExceptionCountParamToRemove = 1; bCatchBuiltinException = true; // EXCEPTION

    t_pcode c = nType2;
    bool ok = true;

    t_boolean boolean_;
    t_integer integer_;
    t_long long_;
    t_double double_;
    t_currency currency_;

    switch(nType){
      case pcode__BOOLEAN:

        switch(c){
          case pcode__CSTRING:
          case pcode__EQSTRING:
          case pcode__ECSTRING:
          case pcode__QSTRING:          
              STRING_EXPRESSION[0] = popStackString(&nestatics[0], &C[0]);

              if (C[0] == pcode__QSTRING){
                boolean_ = !((t_qstring) STRING_EXPRESSION[0])->isEmpty();
    
              } else if (C[0] == pcode__CSTRING){
                boolean_ = ((t_cstring) STRING_EXPRESSION[0]) && strlen(((t_cstring) STRING_EXPRESSION[0]));
              }

              p = new interpreter_parameter(boolean_);

              estatics->undeclare(nestatics[0]);            
              break;
          default:
            goto re;
            break;
        }

        break;

      case pcode__CSTRING:
      case pcode__EQSTRING:
      case pcode__ECSTRING:
      case pcode__QSTRING:

        switch(c){
          
          case pcode__BOOLEAN:
            p = new interpreter_parameter(popStackBoolean() ? "True" : "False");
            break;            

          case pcode__CSTRING:
          case pcode__EQSTRING:
          case pcode__ECSTRING:
          case pcode__QSTRING:
            goto re;
            break;

          case pcode__BYTE:
          case pcode__SHORT:
          case pcode__INTEGER:
            {
              QString s;
              
              if (bEXPRESSION == false){
                s = qlocale->toString(popStackInteger());

              } else if (bEXPRESSION == true && bEXPRESSION2 == false){
                nExceptionCountParamToRemove++;

                bool b = popStackBoolean();
                int n1 = popStackInteger();

                QLocale::NumberOptions options = qlocale->numberOptions();
                if (b == false) qlocale->setNumberOptions(QLocale::OmitGroupSeparator);
                s = qlocale->toString(n1); 
                if (b == false) qlocale->setNumberOptions(options);
    
              } else {
                if (bEXPRESSION2){ interpreter_parameter *pp = popStack(); delete pp; }
                if (bEXPRESSION3){ interpreter_parameter *pp = popStack(); delete pp; }
                if (bEXPRESSION4){ interpreter_parameter *pp = popStack(); delete pp; }
                if (bEXPRESSION5){ interpreter_parameter *pp = popStack(); delete pp; }
              }

              p = new interpreter_parameter(s);
            }
            break;
          case pcode__LONG:
            {
              QString s;
              
              if (bEXPRESSION == false){
                s = qlocale->toString(popStackLong());

              } else if (bEXPRESSION == true && bEXPRESSION2 == false){
                nExceptionCountParamToRemove++;

                bool b = popStackBoolean();
                t_long n1 = popStackLong();

                QLocale::NumberOptions options = qlocale->numberOptions();
                if (b == false) qlocale->setNumberOptions(QLocale::OmitGroupSeparator);
                s = qlocale->toString(n1); 
                if (b == false) qlocale->setNumberOptions(options);
    
              } else {
                if (bEXPRESSION2){ interpreter_parameter *pp = popStack(); delete pp; }
                if (bEXPRESSION3){ interpreter_parameter *pp = popStack(); delete pp; }
                if (bEXPRESSION4){ interpreter_parameter *pp = popStack(); delete pp; }
                if (bEXPRESSION5){ interpreter_parameter *pp = popStack(); delete pp; }
              }

              p = new interpreter_parameter(s);
            }
            break;

          case pcode__SINGLE:
          case pcode__DOUBLE:
            {
              QString s;
              
              if (bEXPRESSION == false){
                s = qlocale->toString(popStackDouble());

              } else if (bEXPRESSION == true && bEXPRESSION2 == false){
                nExceptionCountParamToRemove++;

                STRING_EXPRESSION[0] = popStackString(&nestatics[0], &C[0]);

                QString ss;              
                if (C[0] == pcode__QSTRING){
                  ss = *((t_qstring) STRING_EXPRESSION[0]);      
                } else if (C[0] == pcode__CSTRING){
                  ss = ss.fromLocal8Bit((t_cstring) STRING_EXPRESSION[0]);
                }
                QChar c = 'g';
                if (!ss.isEmpty()) c = ss.at(0);

                estatics->undeclare(nestatics[0]);      

                s = qlocale->toString(popStackDouble(), c.toAscii());

              } else if (bEXPRESSION == true && bEXPRESSION2 == true && bEXPRESSION3 == false){
                nExceptionCountParamToRemove += 2;

                int n = popStackInteger();
                STRING_EXPRESSION[0] = popStackString(&nestatics[0], &C[0]);

                QString ss;              
                if (C[0] == pcode__QSTRING){
                  ss = *((t_qstring) STRING_EXPRESSION[0]);
      
                } else if (C[0] == pcode__CSTRING){
                  ss = ss.fromLocal8Bit((t_cstring) STRING_EXPRESSION[0]);
                }
                QChar c = 'g';
                if (!ss.isEmpty()) c = ss.at(0);
   
                estatics->undeclare(nestatics[0]);      

                s = qlocale->toString(popStackDouble(), c.toAscii(), n);

              } else if (bEXPRESSION == true && bEXPRESSION2 == true && bEXPRESSION3 == true && bEXPRESSION4 == false){
                nExceptionCountParamToRemove += 3;

                bool b = popStackBoolean();
                int n = popStackInteger();
                STRING_EXPRESSION[0] = popStackString(&nestatics[0], &C[0]);

                QString ss;              
                if (C[0] == pcode__QSTRING){
                  ss = *((t_qstring) STRING_EXPRESSION[0]);
      
                } else if (C[0] == pcode__CSTRING){
                  ss = ss.fromLocal8Bit((t_cstring) STRING_EXPRESSION[0]);
                }
                QChar c = 'g';
                if (!ss.isEmpty()) c = ss.at(0);
   
                estatics->undeclare(nestatics[0]);      

                QLocale::NumberOptions options = qlocale->numberOptions();
                if (b == false) qlocale->setNumberOptions(QLocale::OmitGroupSeparator);
                s = qlocale->toString(popStackDouble(), c.toAscii(), n);
                if (b == false) qlocale->setNumberOptions(options);

              } else {
                if (bEXPRESSION4){ interpreter_parameter *pp = popStack(); delete pp; }
                if (bEXPRESSION5){ interpreter_parameter *pp = popStack(); delete pp; }
              }

              p = new interpreter_parameter(s);
            }
            break;

          case pcode__CURRENCY:
            {
              QString s;
              
              if (bEXPRESSION == false){
                s = qlocale->toString(popStackCurrency().toDouble(), 'f', 4);

              } else if (bEXPRESSION == true && bEXPRESSION2 == false){
                nExceptionCountParamToRemove++;

                bool b = popStackBoolean();

                QLocale::NumberOptions options = qlocale->numberOptions();
                if (b == false) qlocale->setNumberOptions(QLocale::OmitGroupSeparator);
                s = qlocale->toString(popStackCurrency().toDouble(), 'f', 4);
                if (b == false) qlocale->setNumberOptions(options);

              } else {
                if (bEXPRESSION2){ interpreter_parameter *pp = popStack(); delete pp; }
                if (bEXPRESSION3){ interpreter_parameter *pp = popStack(); delete pp; }
                if (bEXPRESSION4){ interpreter_parameter *pp = popStack(); delete pp; }
                if (bEXPRESSION5){ interpreter_parameter *pp = popStack(); delete pp; }
              }

              p = new interpreter_parameter(s);
            }
            break;
          case pcode__DATE:
            {
              QString s;
              
              if (bEXPRESSION == false){
             
                t_date d = popStackDate();
                QDateTime dt(QDate(d.nYear, d.nMonth, d.nDay), QTime(d.nHour, d.nMinute, d.nSecond));
   
                if (!dt.isValid()){
                  runtimeError("Cast exception", pcode__CASTEXCEPTION); return;
                }

                s = qlocale->toString(dt, QLocale::ShortFormat);

              } else if (bEXPRESSION == true && bEXPRESSION2 == false){
                nExceptionCountParamToRemove++;

                STRING_EXPRESSION[0] = popStackString(&nestatics[0], &C[0]);

                QString ss;              
                if (C[0] == pcode__QSTRING){
                  ss = *((t_qstring) STRING_EXPRESSION[0]);
      
                } else if (C[0] == pcode__CSTRING){
                  ss = ss.fromLocal8Bit((t_cstring) STRING_EXPRESSION[0]);
                }

                t_date d = popStackDate();
                QDateTime dt(QDate(d.nYear, d.nMonth, d.nDay), QTime(d.nHour, d.nMinute, d.nSecond));
   
                if (ss.contains("LongFormat", Qt::CaseInsensitive)){
                  s = qlocale->toString(dt, QLocale::LongFormat);
                } else if (ss.contains("ShortFormat", Qt::CaseInsensitive)){
                  s = qlocale->toString(dt, QLocale::ShortFormat);
                } else {
                  s = qlocale->toString(dt, ss);
                }

                estatics->undeclare(nestatics[0]);      

                if (!dt.isValid()){
                  runtimeError("Cast exception", pcode__CASTEXCEPTION); return;
                }

              } else {
                if (bEXPRESSION2){ interpreter_parameter *pp = popStack(); delete pp; }
                if (bEXPRESSION3){ interpreter_parameter *pp = popStack(); delete pp; }
                if (bEXPRESSION4){ interpreter_parameter *pp = popStack(); delete pp; }
                if (bEXPRESSION5){ interpreter_parameter *pp = popStack(); delete pp; }
              }

              p = new interpreter_parameter(s);
            }
            break;
        }             
        break;

      case pcode__BYTE:
      case pcode__SHORT:
      case pcode__INTEGER:
      case pcode__LONG:

        switch(c){

          case pcode__CSTRING:
          case pcode__EQSTRING:
          case pcode__ECSTRING:
          case pcode__QSTRING:
            if (nType == pcode__LONG){
              STRING_EXPRESSION[0] = popStackString(&nestatics[0], &C[0]);

              if (C[0] == pcode__QSTRING){
                QString s; s = *((t_qstring) STRING_EXPRESSION[0]);
                s = s.trimmed();
                if (s.startsWith("&H")){
                  long_ = qlocale->toLongLong("0x" + s.mid(2), &ok);
                } else {
                  long_ = qlocale->toLongLong(s, &ok);
                }              
              } else if (C[0] == pcode__CSTRING){
                QString s; s = s.fromLocal8Bit((t_cstring) STRING_EXPRESSION[0]);
                long_ = qlocale->toLongLong(s, &ok);
              }

              p = new interpreter_parameter(long_);

              estatics->undeclare(nestatics[0]);
            } else {
              STRING_EXPRESSION[0] = popStackString(&nestatics[0], &C[0]);

              if (C[0] == pcode__QSTRING){
                QString s; s = *((t_qstring) STRING_EXPRESSION[0]);
                s = s.trimmed();
                if (s.startsWith("&H")){
                  integer_ = qlocale->toInt("0x" + s.mid(2), &ok);
                } else {
                  integer_ = qlocale->toInt(s, &ok);
                }              
              } else if (C[0] == pcode__CSTRING){
                QString s; s = s.fromLocal8Bit((t_cstring) STRING_EXPRESSION[0]);
                integer_ = qlocale->toInt(s, &ok);
              }

              p = new interpreter_parameter(integer_);

              estatics->undeclare(nestatics[0]);
            }
            break;

          default:
            return;
            break;
        }                  
        break;

      case pcode__SINGLE:
      case pcode__DOUBLE:

        switch(c){
          case pcode__CSTRING:
          case pcode__EQSTRING:
          case pcode__ECSTRING:
          case pcode__QSTRING:          
              STRING_EXPRESSION[0] = popStackString(&nestatics[0], &C[0]);

              if (C[0] == pcode__QSTRING){
                QString s; s = *((t_qstring) STRING_EXPRESSION[0]);
                double_ = qlocale->toDouble(s, &ok);
              } else if (C[0] == pcode__CSTRING){
                QString s; s = s.fromLocal8Bit((t_cstring) STRING_EXPRESSION[0]);
                double_ = qlocale->toDouble(s, &ok);
              }

              p = new interpreter_parameter(double_);

              estatics->undeclare(nestatics[0]);
              break;
          default:
            goto re;
            break;
        }
        break;

      case pcode__CURRENCY:
        switch(c){
          case pcode__CSTRING:
          case pcode__EQSTRING:
          case pcode__ECSTRING:
          case pcode__QSTRING:      
              {
                STRING_EXPRESSION[0] = popStackString(&nestatics[0], &C[0]);

                QChar gs = qlocale->groupSeparator();
                QChar dp = qlocale->decimalPoint();

                QString s;
                QString bc = "";
                QString ad = "";

                if (C[0] == pcode__QSTRING){
                  s = *((t_qstring) STRING_EXPRESSION[0]);
                } else if (C[0] == pcode__CSTRING){
                  s = s.fromLocal8Bit((t_cstring) STRING_EXPRESSION[0]);
                }

                if (s.contains(qlocale->exponential())){
                  double_ = qlocale->toDouble(s, &ok);
                  p = new interpreter_parameter(t_currency(double_));
                  estatics->undeclare(nestatics[0]);
                  break;
                }

                int n = s.lastIndexOf(dp);
                if (n >= 0){
                  bc = s.left(n);
                  ad = s.mid(n + 1);
                } else bc = s;
                
                int nad = 0;
                int nbc = qlocale->toInt(bc, &ok);
                if (ok && !ad.isEmpty()) nad = qlocale->toInt(ad, &ok);

                p = new interpreter_parameter(t_currency(nbc, nad));

                estatics->undeclare(nestatics[0]);
              }
              break;
          default:
            goto re;
            break;
        }
        break;

      case pcode__DATE:
        switch(c){
          case pcode__CSTRING:
          case pcode__EQSTRING:
          case pcode__ECSTRING:
          case pcode__QSTRING:
              {
                QString sFormat = "";
                nestatics[1] = 0;

                if (bEXPRESSION){
                  nExceptionCountParamToRemove++;

                  STRING_EXPRESSION[1] = popStackString(&nestatics[1], &C[1]);
                  if (C[1] == pcode__QSTRING){
                    sFormat = *((t_qstring) STRING_EXPRESSION[1]);
                  } else if (C[1] == pcode__CSTRING){
                    sFormat = sFormat.fromLocal8Bit((t_cstring) STRING_EXPRESSION[1]);
                  }

                }
                STRING_EXPRESSION[0] = popStackString(&nestatics[0], &C[0]);

                QString s;

                if (C[0] == pcode__QSTRING){
                  s = *((t_qstring) STRING_EXPRESSION[0]);
                } else if (C[0] == pcode__CSTRING){
                  s = s.fromLocal8Bit((t_cstring) STRING_EXPRESSION[0]);
                }

                QTime t;
                //QDate d;
                QDateTime dt;
                /*
                QString sd = qlocale->dateFormat(QLocale::LongFormat);
                sd = qlocale->dateFormat(QLocale::ShortFormat);

                QString sdt = qlocale->dateTimeFormat(QLocale::LongFormat);
                sdt = qlocale->dateTimeFormat(QLocale::ShortFormat);

                QString st = qlocale->timeFormat(QLocale::LongFormat);
                st = qlocale->timeFormat(QLocale::ShortFormat);
*/
                if (sFormat.isEmpty()){
                  t = qlocale->toTime(s, "hh:mm:ss");
                  if (!t.isValid()){

                    t = qlocale->toTime(s, QLocale::LongFormat);
                    if (!t.isValid()){
                      t = qlocale->toTime(s, QLocale::ShortFormat);
                      if (!t.isValid()){

                     // d = qlocale->toDate(s, QLocale::LongFormat);
                    //  if (!d.isValid()) d = qlocale->toDate(s, QLocale::ShortFormat);

                        //if (d.isValid())
                        {                    
                          dt = qlocale->toDateTime(s, "yyyy-MM-dd hh:mm:ss");
                          if (!dt.isValid()){

                            dt = qlocale->toDateTime(s, "yyyy-MM-dd");
                            if (!dt.isValid()){

                              dt = qlocale->toDateTime(s, qlocale->dateTimeFormat(QLocale::LongFormat)); // do it with dateTimeFormat, cause of Qt bug
                              if (!dt.isValid()){
                                dt = qlocale->toDateTime(s, qlocale->dateTimeFormat(QLocale::ShortFormat)); // do it with dateTimeFormat, cause of Qt bug
                                if (!dt.isValid()){

                                }
                              }
                            }
                          }
                        }
                      }
                      //}
                    }
                  }
                } else {
                  dt = qlocale->toDateTime(s, sFormat);
                }

                bool bb = dt.date().isValid();
                bool bb2 = dt.time().isValid();

                if (t.isValid()){
                  p = new interpreter_parameter(t_date(true, t.hour(), t.minute(), t.second()));
            //    } else if (d.isValid()){
            //      p = new interpreter_parameter(t_date(d.year(), d.month(), d.day()));
                } else if (dt.isValid()){
                  p = new interpreter_parameter(t_date(dt.date().year(), dt.date().month(), dt.date().day(), dt.time().hour(), dt.time().minute(), dt.time().second()));
                } else {                  
                  runtimeError("Cast exception", pcode__CASTEXCEPTION); return;
                }

                if (bReturn) pushStack(p); else delete p;

                estatics->undeclare(nestatics[0]);
                estatics->undeclare(nestatics[1]);

                goto re;
              }
            break;

          case pcode__BOOLEAN:
          case pcode__BYTE:
          case pcode__SHORT:
          case pcode__INTEGER:
          case pcode__LONG:
          case pcode__SINGLE:
          case pcode__DOUBLE:
          case pcode__CURRENCY:
            runtimeError("Cast exception", pcode__CASTEXCEPTION); return;
            break;
          case pcode__DATE:
            goto re;
            break;
        }               
        break;
    }

    if (bReturn) pushStack(p); else delete p;
    
    if (ok == false){
      runtimeError("Cast exception", pcode__CASTEXCEPTION); return;
    }
re:
    bCatchBuiltinException = false; // EXCEPTION
  } // } else return pcodeError(utility::con(pcode::builtin_(pcode__CAST), " missing"));

  return;
}

void interpreter::fCOMPARE()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif

  t_builtin c; t_boolean bEXPRESSION; t_boolean bReturn;

  myPcode->rd_COMPARE(&c, &bEXPRESSION, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__COMPARE);
#endif
   
    int nestatics[interpreter__MAX_PARAM];

    bool CaseSensitive = true;
    if (bEXPRESSION){
      CaseSensitive = popStackBoolean();
    }    

    STRING_EXPRESSION[1] = popStackString(&nestatics[1], &C[1]);    
    STRING_EXPRESSION[0] = popStackString(&nestatics[0], &C[0]);

    if (C[0] == pcode__QSTRING && C[1] == pcode__QSTRING) p = myFunction->fCOMPARE((t_qstring) STRING_EXPRESSION[0], (t_qstring) STRING_EXPRESSION[1], CaseSensitive); // call the associated function
    else if (C[0] == pcode__CSTRING && C[1] == pcode__CSTRING){
      QString s; s = s.fromLocal8Bit((t_cstring) STRING_EXPRESSION[0]);
      QString s2; s2 = s2.fromLocal8Bit((t_cstring) STRING_EXPRESSION[1]);
      p = myFunction->fCOMPARE(&s, &s2, CaseSensitive); // call the associated function
    }
    else if (C[0] == pcode__QSTRING && C[1] == pcode__CSTRING){
      QString s; s = s.fromLocal8Bit((t_cstring) STRING_EXPRESSION[1]);
      p = myFunction->fCOMPARE((t_qstring) STRING_EXPRESSION[0], &s, CaseSensitive); // call the associated function
    }
    else if (C[0] == pcode__CSTRING && C[1] == pcode__QSTRING){
      QString s; s = s.fromLocal8Bit((t_cstring) STRING_EXPRESSION[0]);
      p = myFunction->fCOMPARE(&s, (t_qstring) STRING_EXPRESSION[1], CaseSensitive); // call the associated function
    }

    if (bReturn) pushStack(p); else delete p;

    estatics->undeclare(nestatics[1]);
    estatics->undeclare(nestatics[0]);

  }
  return;
}

void interpreter::fCONTAINS()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif

  t_builtin c; t_boolean bEXPRESSION; t_boolean bReturn;

  myPcode->rd_CONTAINS(&c, &bEXPRESSION, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__CONTAINS);
#endif
   
    int nestatics[interpreter__MAX_PARAM];

    bool CaseSensitive = true;
    if (bEXPRESSION){
      CaseSensitive = popStackBoolean();
    }    

    STRING_EXPRESSION[1] = popStackString(&nestatics[1], &C[1]);    
    STRING_EXPRESSION[0] = popStackString(&nestatics[0], &C[0]);

    if (C[0] == pcode__QSTRING && C[1] == pcode__QSTRING) p = myFunction->fCONTAINS((t_qstring) STRING_EXPRESSION[0], (t_qstring) STRING_EXPRESSION[1], CaseSensitive); // call the associated function
    else if (C[0] == pcode__CSTRING && C[1] == pcode__CSTRING){
      QString s; s = s.fromLocal8Bit((t_cstring) STRING_EXPRESSION[0]);
      QString s2; s2 = s2.fromLocal8Bit((t_cstring) STRING_EXPRESSION[1]);
      p = myFunction->fCONTAINS(&s, &s2, CaseSensitive); // call the associated function
    }
    else if (C[0] == pcode__QSTRING && C[1] == pcode__CSTRING){
      QString s; s = s.fromLocal8Bit((t_cstring) STRING_EXPRESSION[1]);
      p = myFunction->fCONTAINS((t_qstring) STRING_EXPRESSION[0], &s, CaseSensitive); // call the associated function
    }
    else if (C[0] == pcode__CSTRING && C[1] == pcode__QSTRING){
      QString s; s = s.fromLocal8Bit((t_cstring) STRING_EXPRESSION[0]);
      p = myFunction->fCONTAINS(&s, (t_qstring) STRING_EXPRESSION[1], CaseSensitive); // call the associated function
    }

    if (bReturn) pushStack(p); else delete p;

    estatics->undeclare(nestatics[1]);
    estatics->undeclare(nestatics[0]);

  }
  return;
}

void interpreter::fCOUNT()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif

  t_builtin c; t_boolean bEXPRESSION; t_boolean bReturn;

  myPcode->rd_COUNT(&c, &bEXPRESSION, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__COUNT);
#endif
   
    int nestatics[interpreter__MAX_PARAM];

    bool CaseSensitive = true;
    if (bEXPRESSION){
      CaseSensitive = popStackBoolean();
    }    

    STRING_EXPRESSION[1] = popStackString(&nestatics[1], &C[1]);    
    STRING_EXPRESSION[0] = popStackString(&nestatics[0], &C[0]);

    if (C[0] == pcode__QSTRING && C[1] == pcode__QSTRING) p = myFunction->fCOUNT((t_qstring) STRING_EXPRESSION[0], (t_qstring) STRING_EXPRESSION[1], CaseSensitive); // call the associated function
    else if (C[0] == pcode__CSTRING && C[1] == pcode__CSTRING){
      QString s; s = s.fromLocal8Bit((t_cstring) STRING_EXPRESSION[0]);
      QString s2; s2 = s2.fromLocal8Bit((t_cstring) STRING_EXPRESSION[1]);
      p = myFunction->fCOUNT(&s, &s2, CaseSensitive); // call the associated function
    }
    else if (C[0] == pcode__QSTRING && C[1] == pcode__CSTRING){
      QString s; s = s.fromLocal8Bit((t_cstring) STRING_EXPRESSION[1]);
      p = myFunction->fCOUNT((t_qstring) STRING_EXPRESSION[0], &s, CaseSensitive); // call the associated function
    }
    else if (C[0] == pcode__CSTRING && C[1] == pcode__QSTRING){
      QString s; s = s.fromLocal8Bit((t_cstring) STRING_EXPRESSION[0]);
      p = myFunction->fCOUNT(&s, (t_qstring) STRING_EXPRESSION[1], CaseSensitive); // call the associated function
    }

    if (bReturn) pushStack(p); else delete p;

    estatics->undeclare(nestatics[1]);
    estatics->undeclare(nestatics[0]);

  }
  return;
}

void interpreter::fENDSWITH()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif

  t_builtin c; t_boolean bEXPRESSION; t_boolean bReturn;

  myPcode->rd_ENDSWITH(&c, &bEXPRESSION, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__ENDSWITH);
#endif
   
    int nestatics[interpreter__MAX_PARAM];

    bool CaseSensitive = true;
    if (bEXPRESSION){
      CaseSensitive = popStackBoolean();
    }    

    STRING_EXPRESSION[1] = popStackString(&nestatics[1], &C[1]);    
    STRING_EXPRESSION[0] = popStackString(&nestatics[0], &C[0]);

    if (C[0] == pcode__QSTRING && C[1] == pcode__QSTRING) p = myFunction->fENDSWITH((t_qstring) STRING_EXPRESSION[0], (t_qstring) STRING_EXPRESSION[1], CaseSensitive); // call the associated function
    else if (C[0] == pcode__CSTRING && C[1] == pcode__CSTRING){
      QString s; s = s.fromLocal8Bit((t_cstring) STRING_EXPRESSION[0]);
      QString s2; s2 = s2.fromLocal8Bit((t_cstring) STRING_EXPRESSION[1]);
      p = myFunction->fENDSWITH(&s, &s2, CaseSensitive); // call the associated function
    }
    else if (C[0] == pcode__QSTRING && C[1] == pcode__CSTRING){
      QString s; s = s.fromLocal8Bit((t_cstring) STRING_EXPRESSION[1]);
      p = myFunction->fENDSWITH((t_qstring) STRING_EXPRESSION[0], &s, CaseSensitive); // call the associated function
    }
    else if (C[0] == pcode__CSTRING && C[1] == pcode__QSTRING){
      QString s; s = s.fromLocal8Bit((t_cstring) STRING_EXPRESSION[0]);
      p = myFunction->fENDSWITH(&s, (t_qstring) STRING_EXPRESSION[1], CaseSensitive); // call the associated function
    }

    if (bReturn) pushStack(p); else delete p;

    estatics->undeclare(nestatics[1]);
    estatics->undeclare(nestatics[0]);

  }
  return;
}

void interpreter::fSTARTSWITH()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif

  t_builtin c; t_boolean bEXPRESSION; t_boolean bReturn;

  myPcode->rd_STARTSWITH(&c, &bEXPRESSION, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__STARTSWITH);
#endif
   
    int nestatics[interpreter__MAX_PARAM];

    bool CaseSensitive = true;
    if (bEXPRESSION){
      CaseSensitive = popStackBoolean();
    }    

    STRING_EXPRESSION[1] = popStackString(&nestatics[1], &C[1]);    
    STRING_EXPRESSION[0] = popStackString(&nestatics[0], &C[0]);

    if (C[0] == pcode__QSTRING && C[1] == pcode__QSTRING) p = myFunction->fSTARTSWITH((t_qstring) STRING_EXPRESSION[0], (t_qstring) STRING_EXPRESSION[1], CaseSensitive); // call the associated function
    else if (C[0] == pcode__CSTRING && C[1] == pcode__CSTRING){
      QString s; s = s.fromLocal8Bit((t_cstring) STRING_EXPRESSION[0]);
      QString s2; s2 = s2.fromLocal8Bit((t_cstring) STRING_EXPRESSION[1]);
      p = myFunction->fSTARTSWITH(&s, &s2, CaseSensitive); // call the associated function
    }
    else if (C[0] == pcode__QSTRING && C[1] == pcode__CSTRING){
      QString s; s = s.fromLocal8Bit((t_cstring) STRING_EXPRESSION[1]);
      p = myFunction->fSTARTSWITH((t_qstring) STRING_EXPRESSION[0], &s, CaseSensitive); // call the associated function
    }
    else if (C[0] == pcode__CSTRING && C[1] == pcode__QSTRING){
      QString s; s = s.fromLocal8Bit((t_cstring) STRING_EXPRESSION[0]);
      p = myFunction->fSTARTSWITH(&s, (t_qstring) STRING_EXPRESSION[1], CaseSensitive); // call the associated function
    }

    if (bReturn) pushStack(p); else delete p;

    estatics->undeclare(nestatics[1]);
    estatics->undeclare(nestatics[0]);

  }
  return;
}

void interpreter::fLEFTJUSTIFIED()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif

  t_builtin c; t_boolean bEXPRESSION; t_boolean bEXPRESSION2; t_boolean bReturn;

  myPcode->rd_LEFTJUSTIFIED(&c, &bEXPRESSION, &bEXPRESSION2, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__LEFTJUSTIFIED);
#endif
   
    int nestatics[interpreter__MAX_PARAM];

    bool CaseSensitive = true;
    if (bEXPRESSION2){
      CaseSensitive = popStackBoolean();
    }    

    QString ss;
    if (bEXPRESSION){
      STRING_EXPRESSION[1] = popStackString(&nestatics[1], &C[1]);
      if (C[1] == pcode__QSTRING) ss = *((t_qstring) STRING_EXPRESSION[1]);
      else if (C[1] == pcode__QSTRING){
        ss = ss.fromLocal8Bit((t_cstring) STRING_EXPRESSION[1]);
      }
    } else {
      nestatics[1] = 0;
      ss = "";  
    }
    
    t_integer Width = popStackInteger();

    STRING_EXPRESSION[0] = popStackString(&nestatics[0], &C[0]);

    if (C[0] == pcode__QSTRING) p = myFunction->fLEFTJUSTIFIED((t_qstring) STRING_EXPRESSION[0], Width, &ss, CaseSensitive); // call the associated function
    else if (C[0] == pcode__QSTRING){
      QString s; s = s.fromLocal8Bit((t_cstring) STRING_EXPRESSION[0]);
      p = myFunction->fLEFTJUSTIFIED(&s, Width, &ss, CaseSensitive); // call the associated function
    }

    if (bReturn) pushStack(p); else delete p;

    estatics->undeclare(nestatics[0]);
    estatics->undeclare(nestatics[1]);

  }
  return;
}

void interpreter::fRIGHTJUSTIFIED()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif

  t_builtin c; t_boolean bEXPRESSION; t_boolean bEXPRESSION2; t_boolean bReturn;

  myPcode->rd_RIGHTJUSTIFIED(&c, &bEXPRESSION, &bEXPRESSION2, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__RIGHTJUSTIFIED);
#endif
   
    int nestatics[interpreter__MAX_PARAM];

    bool CaseSensitive = true;
    if (bEXPRESSION2){
      CaseSensitive = popStackBoolean();
    }    

    QString ss;
    if (bEXPRESSION){
      STRING_EXPRESSION[1] = popStackString(&nestatics[1], &C[1]);
      if (C[1] == pcode__QSTRING) ss = *((t_qstring) STRING_EXPRESSION[1]);
      else if (C[1] == pcode__QSTRING){
        ss = ss.fromLocal8Bit((t_cstring) STRING_EXPRESSION[1]);
      }
    } else {
      nestatics[1] = 0;
      ss = "";  
    }
    
    t_integer Width = popStackInteger();

    STRING_EXPRESSION[0] = popStackString(&nestatics[0], &C[0]);

    if (C[0] == pcode__QSTRING) p = myFunction->fRIGHTJUSTIFIED((t_qstring) STRING_EXPRESSION[0], Width, &ss, CaseSensitive); // call the associated function
    else if (C[0] == pcode__QSTRING){
      QString s; s = s.fromLocal8Bit((t_cstring) STRING_EXPRESSION[0]);
      p = myFunction->fRIGHTJUSTIFIED(&s, Width, &ss, CaseSensitive); // call the associated function
    }

    if (bReturn) pushStack(p); else delete p;

    estatics->undeclare(nestatics[0]);
    estatics->undeclare(nestatics[1]);

  }
  return;
}

void interpreter::fSECTION()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif

  t_builtin c; t_boolean bEXPRESSION; t_boolean bEXPRESSION2; t_boolean bReturn;

  myPcode->rd_SECTION(&c, &bEXPRESSION, &bEXPRESSION2, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__SECTION);
#endif
   
    int nestatics[interpreter__MAX_PARAM];

    QString SectionFlags;    
    if (bEXPRESSION2){
      STRING_EXPRESSION[2] = popStackString(&nestatics[2], &C[2]);
      if (C[2] == pcode__QSTRING) SectionFlags = *((t_qstring) STRING_EXPRESSION[2]);
      else if (C[2] == pcode__QSTRING){
        SectionFlags = SectionFlags.fromLocal8Bit((t_cstring) STRING_EXPRESSION[2]);
      }
    } else {
      nestatics[2] = 0;
      SectionFlags = "";  
    }

    t_integer End = -1;

    if (bEXPRESSION){
      End = popStackInteger() - 1;
    }

    t_integer Start = popStackInteger() - 1;

    STRING_EXPRESSION[1] = popStackString(&nestatics[1], &C[1]);

    STRING_EXPRESSION[0] = popStackString(&nestatics[0], &C[0]);


    if (C[0] == pcode__QSTRING && C[1] == pcode__QSTRING) p = myFunction->fSECTION((t_qstring) STRING_EXPRESSION[0], (t_qstring) STRING_EXPRESSION[1], Start, End, &SectionFlags); // call the associated function
    else if (C[0] == pcode__CSTRING && C[1] == pcode__CSTRING){
      QString s; s = s.fromLocal8Bit((t_cstring) STRING_EXPRESSION[0]);
      QString s2; s2 = s2.fromLocal8Bit((t_cstring) STRING_EXPRESSION[1]);
      p = myFunction->fSECTION(&s, &s2, Start, End, &SectionFlags); // call the associated function
    }
    else if (C[0] == pcode__QSTRING && C[1] == pcode__CSTRING){
      QString s; s = s.fromLocal8Bit((t_cstring) STRING_EXPRESSION[1]);
      p = myFunction->fSECTION((t_qstring) STRING_EXPRESSION[0], &s, Start, End, &SectionFlags); // call the associated function
    }
    else if (C[0] == pcode__CSTRING && C[1] == pcode__QSTRING){
      QString s; s = s.fromLocal8Bit((t_cstring) STRING_EXPRESSION[0]);
      p = myFunction->fSECTION(&s, (t_qstring) STRING_EXPRESSION[1], Start, End, &SectionFlags); // call the associated function
    }

    if (bReturn) pushStack(p); else delete p;

    estatics->undeclare(nestatics[0]);
    estatics->undeclare(nestatics[1]);
    estatics->undeclare(nestatics[2]);

  }
  return;
}

void interpreter::fSIMPLIFIED()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif

  t_builtin c; t_boolean bReturn;

  myPcode->rd_SIMPLIFIED(&c, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__SIMPLIFIED);
#endif
   
    int nestatics[interpreter__MAX_PARAM];

    STRING_EXPRESSION[0] = popStackString(&nestatics[0], &C[0]);

    if (C[0] == pcode__QSTRING) p = myFunction->fSIMPLIFIED((t_qstring) STRING_EXPRESSION[0]); // call the associated function
    else if (C[0] == pcode__QSTRING){
      QString s; s = s.fromLocal8Bit((t_cstring) STRING_EXPRESSION[0]);
      p = myFunction->fSIMPLIFIED(&s); // call the associated function
    }

    if (bReturn) pushStack(p); else delete p;

    estatics->undeclare(nestatics[0]);

  }
  return;
}

void interpreter::fTRIMMED()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif

  t_builtin c; t_boolean bReturn;

  myPcode->rd_TRIMMED(&c, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__TRIMMED);
#endif
   
    int nestatics[interpreter__MAX_PARAM];

    STRING_EXPRESSION[0] = popStackString(&nestatics[0], &C[0]);

    if (C[0] == pcode__QSTRING) p = myFunction->fTRIMMED((t_qstring) STRING_EXPRESSION[0]); // call the associated function
    else if (C[0] == pcode__QSTRING){
      QString s; s = s.fromLocal8Bit((t_cstring) STRING_EXPRESSION[0]);
      p = myFunction->fTRIMMED(&s); // call the associated function
    }

    if (bReturn) pushStack(p); else delete p;

    estatics->undeclare(nestatics[0]);

  }
  return;
}

void interpreter::fREVERSED()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif

  t_builtin c; t_boolean bReturn;

  myPcode->rd_REVERSED(&c, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__REVERSED);
#endif
   
    int nestatics[interpreter__MAX_PARAM];

    STRING_EXPRESSION[0] = popStackString(&nestatics[0], &C[0]);

    if (C[0] == pcode__QSTRING) p = myFunction->fSTRREVERSE((t_qstring) STRING_EXPRESSION[0]); // call the associated function
    else if (C[0] == pcode__QSTRING){
      QString s; s = s.fromLocal8Bit((t_cstring) STRING_EXPRESSION[0]);
      p = myFunction->fSTRREVERSE(&s); // call the associated function
    }

    if (bReturn) pushStack(p); else delete p;

    estatics->undeclare(nestatics[0]);

  }
  return;
}

void interpreter::fUNICODE()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif

  t_builtin c; t_boolean bEXPRESSION; t_boolean bEXPRESSION2; t_boolean bReturn;

  myPcode->rd_UNICODE(&c, &bEXPRESSION, &bEXPRESSION2, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__UNICODE);
#endif
   
    int nestatics[interpreter__MAX_PARAM];

    t_integer Unicode = 0;
    t_integer Position = -1;
    if (bEXPRESSION2){
      Unicode = popStackInteger();
    } else {
      Position = popStackInteger() - 1;      
    }

    STRING_EXPRESSION[0] = popStackString(&nestatics[0], &C[0]);

    if (C[0] == pcode__QSTRING) p = myFunction->fUNICODE((t_qstring) STRING_EXPRESSION[0], Position, bEXPRESSION2, Unicode); // call the associated function
    else if (C[0] == pcode__QSTRING){
      QString s; s = s.fromLocal8Bit((t_cstring) STRING_EXPRESSION[0]);
      p = myFunction->fUNICODE(&s, Position, bEXPRESSION2, Unicode); // call the associated function
    }

    if (bReturn) pushStack(p); else delete p;

    estatics->undeclare(nestatics[0]);

  }
  return;
}

void interpreter::fREADBINARY()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin c; t_integer identifier; t_scope scope; t_integer nType; t_boolean bEXPRESSION; t_boolean bReturn;

  myPcode->rd_READBINARY(&c, &identifier, &scope, &nType, &bEXPRESSION, &bReturn);

  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__READBINARY);
#endif
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

    int nestatics[interpreter__MAX_PARAM];

    t_integer nLen = -1;
    if (bEXPRESSION){
      nLen = popStackInteger();
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
    }

    int n = as->device()->pos();

    delete as;

    ba = new QByteArray(s.toLatin1());
    as = new QDataStream(ba, QIODevice::ReadWrite);
    qdatastream[identifier] = as;
    qdatastream_bytearray[as] = ba;


    as->device()->seek(n);

    switch(nType){
      case pcode__BOOLEAN:
        *as >> byte_;
        p = new interpreter_parameter((t_boolean) byte_);
        break;
      case pcode__EQSTRING:
      case pcode__QSTRING:
        {
          *as >> s;
          p = new interpreter_parameter(s);

        }
        break;
      case pcode__BYTE:
        *as >> byte_;
        p = new interpreter_parameter(byte_);
        break;
      case pcode__SHORT:
        *as >> short_;
        p = new interpreter_parameter(short_);
        break;
      case pcode__INTEGER:
        *as >> integer_;
        p = new interpreter_parameter(integer_);
        break;
      case pcode__LONG:
        *as >> long_;
        p = new interpreter_parameter(long_);
        break;
      case pcode__SINGLE:
        *as >> single_;
        p = new interpreter_parameter(single_);
        break;
      case pcode__DOUBLE:
        *as >> double_;
        p = new interpreter_parameter(double_);
        break;
      case pcode__CURRENCY:
        *as >> long_;
        *as >> long2_;
        p = new interpreter_parameter(t_currency(long_, long2_));
        break;
      case pcode__DATE:
        *as >> integer_;
        *as >> integer2_;
        *as >> integer3_;
        *as >> integer4_;
        *as >> integer5_;
        *as >> integer6_;
        p = new interpreter_parameter(t_date(integer_, integer2_, integer3_, integer4_, integer5_, integer6_));
        break;
    }

    if (bReturn) pushStack(p); else delete p;

    estatics->undeclare(nestatics[0]);
   
  }
  return;
}

void interpreter::fSEEKBINARY()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif

  t_builtin c; t_integer identifier; t_scope scope; t_boolean bEXPRESSION; t_boolean bReturn;

  myPcode->rd_SEEKBINARY(&c, &identifier, &scope, &bEXPRESSION, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__SEEKBINARY);
#endif
   
    int nestatics[interpreter__MAX_PARAM];

    t_integer nPos = -1;
    if (bEXPRESSION) nPos = popStackInteger() - 1;
      
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
    if (bNew){
      QByteArray *ba = new QByteArray();//s.toLatin1());
      as = new QDataStream(ba, QIODevice::ReadWrite);
      qdatastream[identifier] = as;
      qdatastream_bytearray[as] = ba;
    } else {
      as = qdatastream[identifier];
    }

    if (nPos != -1) as->device()->seek(nPos);

    int n = as->device()->pos();

    if (bReturn) pushStack(new interpreter_parameter(n));

    estatics->undeclare(nestatics[0]);
  }
  return;
}

/*
void interpreter::fADDDATE()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif

  t_builtin c; t_boolean bReturn;

  myPcode->rd_ADDDATE(&c, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__ADDDATE);
#endif
   
    DATE_EXPRESSION[1] = popStackDate();
    t_date d1 = popStackDate();

    p = myFunction->fADDDATE(DATE_EXPRESSION[0], DATE_EXPRESSION[1]); // call the associated function

    if (bReturn) pushStack(p); else delete p;

  }
  return;
}
*/
void interpreter::fADDDAYS()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif

  t_builtin c; t_boolean bReturn;

  myPcode->rd_ADDDAYS(&c, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__ADDDAYS);
#endif
   
    int n = popStackInteger();
    t_date d1 = popStackDate();

    p = myFunction->fADDDAYS(d1, n); // call the associated function

    if (bReturn) pushStack(p); else delete p;

  }
  return;
}

void interpreter::fADDMONTHS()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif

  t_builtin c; t_boolean bReturn;

  myPcode->rd_ADDMONTHS(&c, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__ADDMONTHS);
#endif
   
    int n = popStackInteger();
    t_date d1 = popStackDate();

    p = myFunction->fADDMONTHS(d1, n); // call the associated function

    if (bReturn) pushStack(p); else delete p;

  }
  return;
}

void interpreter::fADDYEARS()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif

  t_builtin c; t_boolean bReturn;

  myPcode->rd_ADDYEARS(&c, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__ADDYEARS);
#endif
   
    int n = popStackInteger();
    t_date d1 = popStackDate();

    p = myFunction->fADDYEARS(d1, n); // call the associated function

    if (bReturn) pushStack(p); else delete p;

  }
  return;
}
/*
void interpreter::fSUBDATE()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif

  t_builtin c; t_boolean bReturn;

  myPcode->rd_SUBDATE(&c, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__SUBDATE);
#endif
   
    DATE_EXPRESSION[1] = popStackDate();
    t_date d1 = popStackDate();

    p = myFunction->fSUBDATE(DATE_EXPRESSION[0], DATE_EXPRESSION[1]); // call the associated function

    if (bReturn) pushStack(p); else delete p;

  }
  return;
}
*/
void interpreter::fSUBDAYS()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif

  t_builtin c; t_boolean bReturn;

  myPcode->rd_SUBDAYS(&c, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__SUBDAYS);
#endif
   
    int n = popStackInteger();
    t_date d1 = popStackDate();

    p = myFunction->fSUBDAYS(d1, n); // call the associated function

    if (bReturn) pushStack(p); else delete p;

  }
  return;
}

void interpreter::fSUBMONTHS()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif

  t_builtin c; t_boolean bReturn;

  myPcode->rd_SUBMONTHS(&c, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__SUBMONTHS);
#endif
   
    int n = popStackInteger();
    t_date d1 = popStackDate();

    p = myFunction->fSUBMONTHS(d1, n); // call the associated function

    if (bReturn) pushStack(p); else delete p;

  }
  return;
}

void interpreter::fSUBYEARS()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif

  t_builtin c; t_boolean bReturn;

  myPcode->rd_SUBYEARS(&c, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__SUBYEARS);
#endif
   
    int n = popStackInteger();
    t_date d1 = popStackDate();

    p = myFunction->fSUBYEARS(d1, n); // call the associated function

    if (bReturn) pushStack(p); else delete p;

  }
  return;
}
/*
void interpreter::fADDTIME()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif

  t_builtin c; t_boolean bReturn;

  myPcode->rd_ADDTIME(&c, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__ADDTIME);
#endif
   
    DATE_EXPRESSION[1] = popStackDate();
    t_date d1 = popStackDate();

    p = myFunction->fADDTIME(DATE_EXPRESSION[0], DATE_EXPRESSION[1]); // call the associated function

    if (bReturn) pushStack(p); else delete p;

  }
  return;
}
*/
void interpreter::fADDHOURS()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif

  t_builtin c; t_boolean bReturn;

  myPcode->rd_ADDHOURS(&c, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__ADDHOURS);
#endif
   
    int n = popStackInteger();
    t_date d1 = popStackDate();

    p = myFunction->fADDHOURS(d1, n); // call the associated function

    if (bReturn) pushStack(p); else delete p;

  }
  return;
}

void interpreter::fADDMINUTES()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif

  t_builtin c; t_boolean bReturn;

  myPcode->rd_ADDMINUTES(&c, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__ADDMINUTES);
#endif
   
    int n = popStackInteger();
    t_date d1 = popStackDate();

    p = myFunction->fADDMINUTES(d1, n); // call the associated function

    if (bReturn) pushStack(p); else delete p;

  }
  return;
}

void interpreter::fADDSECONDS()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif

  t_builtin c; t_boolean bReturn;

  myPcode->rd_ADDSECONDS(&c, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__ADDSECONDS);
#endif
   
    int n = popStackInteger();
    t_date d1 = popStackDate();

    p = myFunction->fADDSECONDS(d1, n); // call the associated function

    if (bReturn) pushStack(p); else delete p;

  }
  return;
}
/*
void interpreter::fSUBTIME()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif

  t_builtin c; t_boolean bReturn;

  myPcode->rd_SUBTIME(&c, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__SUBTIME);
#endif
   
    DATE_EXPRESSION[1] = popStackDate();
    t_date d1 = popStackDate();

    p = myFunction->fSUBTIME(DATE_EXPRESSION[0], DATE_EXPRESSION[1]); // call the associated function

    if (bReturn) pushStack(p); else delete p;

  }
  return;
}
*/
void interpreter::fSUBHOURS()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif

  t_builtin c; t_boolean bReturn;

  myPcode->rd_SUBHOURS(&c, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__SUBHOURS);
#endif
   
    int n = popStackInteger();
    t_date d1 = popStackDate();

    p = myFunction->fSUBHOURS(d1, n); // call the associated function

    if (bReturn) pushStack(p); else delete p;

  }
  return;
}

void interpreter::fSUBMINUTES()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif

  t_builtin c; t_boolean bReturn;

  myPcode->rd_SUBMINUTES(&c, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__SUBMINUTES);
#endif
   
    int n = popStackInteger();
    t_date d1 = popStackDate();

    p = myFunction->fSUBMINUTES(d1, n); // call the associated function

    if (bReturn) pushStack(p); else delete p;

  }
  return;
}

void interpreter::fSUBSECONDS()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif

  t_builtin c; t_boolean bReturn;

  myPcode->rd_SUBSECONDS(&c, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__SUBSECONDS);
#endif
   
    int n = popStackInteger();
    t_date d1 = popStackDate();

    p = myFunction->fSUBSECONDS(d1, n); // call the associated function

    if (bReturn) pushStack(p); else delete p;

  }
  return;
}

void interpreter::fDAYOFWEEK()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif

  t_builtin c; t_boolean bEXPRESSION; t_boolean bReturn;

  myPcode->rd_DAYOFWEEK(&c, &bEXPRESSION, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__DAYOFWEEK);
#endif
   
    t_date d1 = popStackDate();

    int nestatics[interpreter__MAX_PARAM];
    nestatics[0] = 0;

    if (bEXPRESSION){
      STRING_EXPRESSION[0] = popStackString(&nestatics[0], &C[0]);
    }

    QString s = "";
    if (C[0] == pcode__QSTRING){
      s = *((t_qstring) STRING_EXPRESSION[0]);
    } else if (C[0] == pcode__CSTRING){
      s = s.fromLocal8Bit((t_cstring) STRING_EXPRESSION[0]);
    }

    p = myFunction->fDAYOFWEEK(d1, &s); // call the associated function

    if (bReturn) pushStack(p); else delete p;

    estatics->undeclare(nestatics[0]);

  }
  return;
}

void interpreter::fDAYOFYEAR()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif

  t_builtin c; t_boolean bReturn;

  myPcode->rd_DAYOFYEAR(&c, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__DAYOFWEEK);
#endif
   
    t_date d1 = popStackDate();

    p = myFunction->fDAYOFYEAR(d1); // call the associated function

    if (bReturn) pushStack(p); else delete p;

  }
  return;
}

void interpreter::fDAYSINMONTH()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif

  t_builtin c; t_boolean bReturn;

  myPcode->rd_DAYSINMONTH(&c, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__DAYSINMONTH);
#endif
   
    t_date d1 = popStackDate();

    p = myFunction->fDAYSINMONTH(d1); // call the associated function

    if (bReturn) pushStack(p); else delete p;

  }
  return;
}

void interpreter::fDAYSINYEAR()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif

  t_builtin c; t_boolean bReturn;

  myPcode->rd_DAYSINYEAR(&c, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__DAYSINYEAR);
#endif
   
    t_date d1 = popStackDate();

    p = myFunction->fDAYSINYEAR(d1); // call the associated function

    if (bReturn) pushStack(p); else delete p;

  }
  return;
}

void interpreter::fWEEKNUMBER()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif

  t_builtin c; t_boolean bReturn;

  myPcode->rd_WEEKNUMBER(&c, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__WEEKNUMBER);
#endif
   
    t_date d1 = popStackDate();

    p = myFunction->fWEEKNUMBER(d1); // call the associated function

    if (bReturn) pushStack(p); else delete p;

  }
  return;
}

void interpreter::fISLEAPYEAR()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif

  t_builtin c; t_boolean bReturn;

  myPcode->rd_ISLEAPYEAR(&c, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__ISLEAPYEAR);
#endif
   
    t_date d1 = popStackDate();

    p = myFunction->fISLEAPYEAR(d1); // call the associated function

    if (bReturn) pushStack(p); else delete p;

  }
  return;
}

void interpreter::fDIFFDAY()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif

  t_builtin c; t_boolean bReturn;

  myPcode->rd_DIFFDAY(&c, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__DIFFDAY);
#endif
   
    t_date d1 = popStackDate();
    t_date d2 = popStackDate();

    p = myFunction->fDIFFDAY(d1, d2); // call the associated function

    if (bReturn) pushStack(p); else delete p;

  }
  return;
}

void interpreter::fDIFFSECONDS()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif

  t_builtin c; t_boolean bReturn;

  myPcode->rd_DIFFSECONDS(&c, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__DIFFSECONDS);
#endif
   
    t_date d1 = popStackDate();
    t_date d2 = popStackDate();

    p = myFunction->fDIFFSECONDS(d1, d2); // call the associated function

    if (bReturn) pushStack(p); else delete p;

  }
  return;
}

void interpreter::fISDATEVALID()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif

  t_builtin c; t_boolean bReturn;

  myPcode->rd_ISDATEVALID(&c, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__ISDATEVALID);
#endif
   
    t_date d1 = popStackDate();

    p = myFunction->fISDATEVALID(d1); // call the associated function

    if (bReturn) pushStack(p); else delete p;

  }
  return;
}

void interpreter::fISTIMEVALID()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif

  t_builtin c; t_boolean bReturn;

  myPcode->rd_ISTIMEVALID(&c, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__ISTIMEVALID);
#endif
   
    t_date d1 = popStackDate();

    p = myFunction->fISTIMEVALID(d1); // call the associated function

    if (bReturn) pushStack(p); else delete p;

  }
  return;
}

void interpreter::fISDATETIMEVALID()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif

  t_builtin c; t_boolean bReturn;

  myPcode->rd_ISDATETIMEVALID(&c, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__ISDATETIMEVALID);
#endif
   
    t_date d1 = popStackDate();

    p = myFunction->fISDATETIMEVALID(d1); // call the associated function

    if (bReturn) pushStack(p); else delete p;

  }
  return;
}

void interpreter::fMONTHNAME()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin c; t_boolean bFORMAT; t_boolean bFirstdayofweek; t_boolean bFirstweekofyear; t_boolean bReturn;

  myPcode->rd_MONTHNAME(&c, &bFORMAT, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__FORMAT);
#endif
    
    bool bBoolean = false;
    
    QString s = "";

    int nestatics[interpreter__MAX_PARAM];
    nestatics[0] = 0;

    if (bFORMAT){
      bBoolean = myStack->peekPCode() == pcode__BOOLEAN;

      if (bBoolean){
        if (popStackBoolean()){
          s = "ShortFormat";
        } else {
          s = "LongFormat";
        }
      } else {
        STRING_EXPRESSION[0] = popStackString(&nestatics[0], &C[0]);

        if (C[0] == pcode__QSTRING){
          s = *((t_qstring) STRING_EXPRESSION[0]);
        } else if (C[0] == pcode__CSTRING){
          s = s.fromLocal8Bit((t_cstring) STRING_EXPRESSION[0]);
        }

      }
    }

    INTEGER_EXPRESSION[0] = popStackInteger();

    p = myFunction->fMONTHNAME(INTEGER_EXPRESSION[0], &s); // call the associated function
    if (bReturn) p; else delete p;

    estatics->undeclare(nestatics[0]);

    return;
  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__FORMAT), " missing"));
}

void interpreter::fDAYNAME()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  t_builtin c; t_boolean bFORMAT; t_boolean bFirstdayofweek; t_boolean bFirstweekofyear; t_boolean bReturn;

  myPcode->rd_DAYNAME(&c, &bFORMAT, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__FORMAT);
#endif
    
    bool bBoolean = false;
    
    QString s = "";

    int nestatics[interpreter__MAX_PARAM];
    nestatics[0] = 0;

    if (bFORMAT){
      bBoolean = myStack->peekPCode() == pcode__BOOLEAN;

      if (bBoolean){
        if (popStackBoolean()){
          s = "ShortFormat";
        } else {
          s = "LongFormat";
        }
      } else {
        STRING_EXPRESSION[0] = popStackString(&nestatics[0], &C[0]);

        if (C[0] == pcode__QSTRING){
          s = *((t_qstring) STRING_EXPRESSION[0]);
        } else if (C[0] == pcode__CSTRING){
          s = s.fromLocal8Bit((t_cstring) STRING_EXPRESSION[0]);
        }

      }
    }

    INTEGER_EXPRESSION[0] = popStackInteger();

    p =  myFunction->fDAYNAME(INTEGER_EXPRESSION[0], &s); // call the associated function
    if (bReturn) p; else delete p;

    estatics->undeclare(nestatics[0]);

    return;
  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__FORMAT), " missing"));
}

void interpreter::fENCODE()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif

  t_builtin c; t_boolean bReturn;

  myPcode->rd_ENCODE(&c, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__ENCODE);
#endif

    int nestatics;   
    STRING_EXPRESSION[0] = popStackString(&nestatics, &C[0]);

    if (C[0] == pcode__QSTRING) p = myFunction->fENCODE((t_qstring) STRING_EXPRESSION[0]); // call the associated function
    else p = myFunction->fENCODE((t_cstring) STRING_EXPRESSION[0]); // call the associated function

    if (bReturn) pushStack(p); else delete p;
    estatics->undeclare(nestatics);
    
  } // } else return pcodeError(utility::con(pcode::builtin_(pcode__ENCODE), " missing"));

  return;
}

void interpreter::fDECODE()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif

  t_builtin c; t_boolean bReturn;

  myPcode->rd_DECODE(&c, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__DECODE);
#endif

    int nestatics;   
    STRING_EXPRESSION[0] = popStackString(&nestatics, &C[0]);

    if (C[0] == pcode__QSTRING) p = myFunction->fDECODE((t_qstring) STRING_EXPRESSION[0]); // call the associated function
    else p = myFunction->fDECODE((t_cstring) STRING_EXPRESSION[0]); // call the associated function

    if (bReturn) pushStack(p); else delete p;
    estatics->undeclare(nestatics);
    
  } // } else return pcodeError(utility::con(pcode::builtin_(pcode__DECODE), " missing"));

  return;
}