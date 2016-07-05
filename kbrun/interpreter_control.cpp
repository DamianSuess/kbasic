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


extern QString sQtException;   
extern QString sQtException2;   

void interpreter::fCJMP()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


	t_pcode cjmp; t_integer new_pc; t_boolean conditional;

	myPcode->rd_CJMP(&cjmp, &new_pc, &conditional);
  {

		new_pc += myLocalFrame.last()->subPcodeOffset;

#ifdef HAS_CONSOLE
    if (!bSilent){
      CONSOLE pcodePrintSep("");
	 	  CONSOLE pcodePrintPos(nPos);
		  CONSOLE pcodePrintOpc(pcode::pcode_(pcode__CJMP));
    }
#endif


		{
		  t_boolean boolean_;// = 0;

		  t_byte byte_;// = 0;
		  t_short short_;// = 0;
      t_integer integer_;// = 0;
		  t_long long_ ;//= 0;

		  t_single single_;// = 0;
		  t_double double_;// = 0;
/*
      t_int16 int16_;// = 0;
      t_int32 int32_;// = 0;
      t_int64 int64_;// = 0;
      t_uint16 uint16_;// = 0;
      t_uint32 uint32_;// = 0;
      t_uint64 uint64_;// = 0;*/


			t_pcode cType ;//= 0;

#ifdef HAS_CONSOLE
      if (!bSilent) sprintf(acStringOutputBuffer, "%s", "not jumped");
#endif

			cType = myStack->popPCode();
		  switch (cType){ 
				case pcode__BOOLEAN: 
          boolean_ = myStack->popBoolean(); 
				  if (boolean_ == false && conditional || boolean_ == true && !conditional){
					  myPcode->setPos(new_pc);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "jump to %d", (int) new_pc);
#endif
          } else {
            break;
          }
          break;

       case pcode__BYTE: 
         byte_ = myStack->popByte(); 
				  if (byte_ == 0 && conditional || byte_ != 0 && !conditional){
					  myPcode->setPos(new_pc);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "jump to %d", (int) new_pc);
#endif
				  }
         break;
       case pcode__SHORT: 
         short_ = myStack->popShort(); 
				  if (short_ == 0 && conditional || short_ != 0 && !conditional){
					  myPcode->setPos(new_pc);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "jump to %d", (int) new_pc);
#endif
				  }
         break;
       case pcode__INTEGER: 
         integer_ = myStack->popInteger(); 
				  if (integer_ == 0 && conditional || integer_ != 0 && !conditional){
					  myPcode->setPos(new_pc);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "jump to %d", (int) new_pc);
#endif
				  }
         break;
				case pcode__LONG: 
          long_ = myStack->popLong(); 
				  if (long_ == 0 && conditional || long_ != 0 && !conditional){
					  myPcode->setPos(new_pc);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "jump to %d", (int) new_pc);
#endif
				  }
          break;

				case pcode__SINGLE: 
          single_ = myStack->popSingle();   
				  if (single_ == 0 && conditional || single_ != 0 && !conditional){
					  myPcode->setPos(new_pc);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "jump to %d", (int) new_pc);
#endif
          } else {
            break;
          }
          break;
       case pcode__DOUBLE: 
         double_ = myStack->popDouble(); 
				  if (double_ == 0 && conditional || double_ != 0 && !conditional){
					  myPcode->setPos(new_pc);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "jump to %d", (int) new_pc);
#endif
          } else {
            break;
          }
         break;
/*
       case pcode__INT16: 
         int16_ = myStack->popInt16(); 
				  if (int16_ == 0 && conditional || int16_ != 0 && !conditional){
					  myPcode->setPos(new_pc);
					  if (!bSilent) sprintf(acStringOutputBuffer, "jump to %d", (int) new_pc);
				  }
         break;
       case pcode__INT32: 
         int32_ = myStack->popInt32(); 
				  if (int32_ == 0 && conditional || int32_ != 0 && !conditional){
					  myPcode->setPos(new_pc);
					  if (!bSilent) sprintf(acStringOutputBuffer, "jump to %d", (int) new_pc);
				  }
         break;
       case pcode__INT64: 
         int64_ = myStack->popInt64(); 
				  if (int64_ == 0 && conditional || int64_ != 0 && !conditional){
					  myPcode->setPos(new_pc);
					  if (!bSilent) sprintf(acStringOutputBuffer, "jump to %d", (int) new_pc);
				  }
         break;
       case pcode__UINT16: 
         uint16_ = myStack->popUInt16(); 
				  if (uint16_ == 0 && conditional || uint16_ != 0 && !conditional){
					  myPcode->setPos(new_pc);
					  if (!bSilent) sprintf(acStringOutputBuffer, "jump to %d", (int) new_pc);
				  }
         break;
       case pcode__UINT32: 
         uint32_ = myStack->popUInt32();
				  if (uint32_ == 0 && conditional || uint32_ != 0 && !conditional){
					  myPcode->setPos(new_pc);
					  if (!bSilent) sprintf(acStringOutputBuffer, "jump to %d", (int) new_pc);
				  }
         break;
       case pcode__UINT64: 
         uint64_ = myStack->popUInt64(); 
				  if (uint64_ == 0 && conditional || uint64_ != 0 && !conditional){
					  myPcode->setPos(new_pc);
					  if (!bSilent) sprintf(acStringOutputBuffer, "jump to %d", (int) new_pc);
				  }
         break;
         */
     case pcode__OBJECT:
       {
         bool b44 = myStack->popBoolean();
         bool memory_variable2 = myStack->popBoolean();
         t_object object_ = myStack->popPointer();
				 //t_object object_ = myStack->popObject();
				  if (object_ == 0 && conditional || object_ != 0 && !conditional){
					  myPcode->setPos(new_pc);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "jump to %d", (int) new_pc);
#endif
				  }
       }
         break;

   case pcode__ECSTRING:
       {
        int id = myStack->popCStringId();
        t_cstring s = estatics->getCString(id, 0);

          if (s == 0 && conditional || s != 0 && !conditional){
					  myPcode->setPos(new_pc);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "jump to %d", (int) new_pc);
#endif
				  }
       }
         break;

   case pcode__EQSTRING:
       {
        int id = myStack->popQStringId();
        t_qstring s = estatics->getQString(id, 0);

          if (s == 0 && conditional || s != 0 && !conditional){
					  myPcode->setPos(new_pc);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "jump to %d", (int) new_pc);
#endif
				  }
       }
         break;

   case pcode__QSTRING:
       {
        t_qstring s = myStack->popQString();

          if (s == 0 && conditional || s != 0 && !conditional){
					  myPcode->setPos(new_pc);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "jump to %d", (int) new_pc);
#endif
				  }
       }
         break;

   case pcode__CSTRING:
       {
        t_cstring s = myStack->popCString();

          if (s == 0 && conditional || s != 0 && !conditional){
					  myPcode->setPos(new_pc);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "jump to %d", (int) new_pc);
#endif
				  }
       }
         break;

       default:

        {

#ifdef HAS_CONSOLE
          if (!bSilent){
            sprintf(acStringOutputBuffer, "pcode__CJMP %s", "error wrong datatype");
            pcodeError(acStringOutputBuffer);
          }
#else
           pcodeError("pcode__CJMP error wrong datatype");
#endif
           return;
        }
        break;

      }


	  }

#ifdef HAS_CONSOLE
    if (!bSilent){
	    CONSOLE pcodePrint(acStringOutputBuffer);
		  CONSOLE pcodePrintCR();
    }
#endif

	} // } else return pcodeError(utility::con(pcode::pcode_(pcode__CJMP), " missing"));
	return;
}

void interpreter::fCJMP2()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


	t_pcode cjmp2; t_integer new_pc; t_boolean conditional;

	myPcode->rd_CJMP2(&cjmp2, &new_pc, &conditional);
  {

		new_pc += myLocalFrame.last()->subPcodeOffset;

#ifdef HAS_CONSOLE
    if (!bSilent){
      CONSOLE pcodePrintSep("");
	 	  CONSOLE pcodePrintPos(nPos);
		  CONSOLE pcodePrintOpc(pcode::pcode_(pcode__CJMP2));
    }
#endif


		{
		  t_boolean boolean_;// = 0;

		  t_byte byte_;// = 0;
		  t_short short_;// = 0;
      t_integer integer_;// = 0;
		  t_long long_ ;//= 0;

		  t_single single_;// = 0;
		  t_double double_;// = 0;
/*
      t_int16 int16_;// = 0;
      t_int32 int32_;// = 0;
      t_int64 int64_;// = 0;
      t_uint16 uint16_;// = 0;
      t_uint32 uint32_;// = 0;
      t_uint64 uint64_;// = 0;
*/

			t_pcode cType ;//= 0;

      myStack->saveStack();

#ifdef HAS_CONSOLE
      if (!bSilent) sprintf(acStringOutputBuffer, "%s", "not jumped");
#endif

			cType = myStack->popPCode();
		  switch (cType){
				case pcode__BOOLEAN: 
          boolean_ = myStack->popBoolean(); 
				  if (boolean_ == false && conditional || boolean_ == true && !conditional){
					  myPcode->setPos(new_pc);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "jump to %d", (int) new_pc);
#endif
				  }
          break;

       case pcode__BYTE: 
         byte_ = myStack->popByte(); 
				  if (byte_ == 0 && conditional || byte_ != 0 && !conditional){
					  myPcode->setPos(new_pc);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "jump to %d", (int) new_pc);
#endif
				  }
         break;
       case pcode__SHORT: 
         short_ = myStack->popShort(); 
				  if (short_ == 0 && conditional || short_ != 0 && !conditional){
					  myPcode->setPos(new_pc);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "jump to %d", (int) new_pc);
#endif
				  }
         break;
       case pcode__INTEGER: 
         integer_ = myStack->popInteger(); 
				  if (integer_ == 0 && conditional || integer_ != 0 && !conditional){
					  myPcode->setPos(new_pc);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "jump to %d", (int) new_pc);
#endif
				  }
         break;
				case pcode__LONG: 
          long_ = myStack->popLong(); 
				  if (long_ == 0 && conditional || long_ != 0 && !conditional){
					  myPcode->setPos(new_pc);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "jump to %d", (int) new_pc);
#endif
				  }
          break;

				case pcode__SINGLE: 
          single_ = myStack->popSingle();   
				  if (single_ == 0 && conditional || single_ != 0 && !conditional){
					  myPcode->setPos(new_pc);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "jump to %d", (int) new_pc);
#endif
				  }
          break;
       case pcode__DOUBLE: 
         double_ = myStack->popDouble(); 
				  if (double_ == 0 && conditional || double_ != 0 && !conditional){
					  myPcode->setPos(new_pc);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "jump to %d", (int) new_pc);
#endif
				  }
         break;
/*
       case pcode__INT16: 
         int16_ = myStack->popInt16(); 
				  if (int16_ == 0 && conditional || int16_ != 0 && !conditional){
					  myPcode->setPos(new_pc);
					  if (!bSilent) sprintf(acStringOutputBuffer, "jump to %d", (int) new_pc);
				  }
         break;
       case pcode__INT32: 
         int32_ = myStack->popInt32(); 
				  if (int32_ == 0 && conditional || int32_ != 0 && !conditional){
					  myPcode->setPos(new_pc);
					  if (!bSilent) sprintf(acStringOutputBuffer, "jump to %d", (int) new_pc);
				  }
         break;
       case pcode__INT64: 
         int64_ = myStack->popInt64(); 
				  if (int64_ == 0 && conditional || int64_ != 0 && !conditional){
					  myPcode->setPos(new_pc);
					  if (!bSilent) sprintf(acStringOutputBuffer, "jump to %d", (int) new_pc);
				  }
         break;
       case pcode__UINT16: 
         uint16_ = myStack->popUInt16(); 
				  if (uint16_ == 0 && conditional || uint16_ != 0 && !conditional){
					  myPcode->setPos(new_pc);
					  if (!bSilent) sprintf(acStringOutputBuffer, "jump to %d", (int) new_pc);
				  }
         break;
       case pcode__UINT32: 
         uint32_ = myStack->popUInt32();
				  if (uint32_ == 0 && conditional || uint32_ != 0 && !conditional){
					  myPcode->setPos(new_pc);
					  if (!bSilent) sprintf(acStringOutputBuffer, "jump to %d", (int) new_pc);
				  }
         break;
       case pcode__UINT64: 
         uint64_ = myStack->popUInt64(); 
				  if (uint64_ == 0 && conditional || uint64_ != 0 && !conditional){
					  myPcode->setPos(new_pc);
					  if (!bSilent) sprintf(acStringOutputBuffer, "jump to %d", (int) new_pc);
				  }
         break;
*/
        default:
          internalError("fCJMP2: wrong datatype on stack");           
          return;
          break;
		  }

		  myStack->restoreStack();

	  }
#ifdef HAS_CONSOLE
    if (!bSilent){
	    CONSOLE pcodePrint(acStringOutputBuffer);
		  CONSOLE pcodePrintCR();
    }
#endif

	} // } else return pcodeError(utility::con(pcode::pcode_(pcode__CJMP2), " missing"));
	return;
}

void interpreter::fCJMP3()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


	t_pcode cjmp; t_integer new_pc; t_boolean andalso;

	myPcode->rd_CJMP3(&cjmp, &new_pc, &andalso);
  {

		new_pc += myLocalFrame.last()->subPcodeOffset;

#ifdef HAS_CONSOLE
    if (!bSilent){
      CONSOLE pcodePrintSep("");
	 	  CONSOLE pcodePrintPos(nPos);
		  CONSOLE pcodePrintOpc(pcode::pcode_(pcode__CJMP3));
    }
#endif


		{
		  t_boolean boolean_;// = 0;

		  t_byte byte_;// = 0;
		  t_short short_;// = 0;
      t_integer integer_;// = 0;
		  t_long long_ ;//= 0;

		  t_single single_;// = 0;
		  t_double double_;// = 0;



			t_pcode cType ;//= 0;

#ifdef HAS_CONSOLE
      if (!bSilent) sprintf(acStringOutputBuffer, "%s", "not jumped");
#endif

			cType = myStack->popPCode();
		  switch (cType){ 
				case pcode__BOOLEAN: 
          boolean_ = myStack->popBoolean(); 
				  if (boolean_ == false && andalso || boolean_ == true && !andalso){
					  myPcode->setPos(new_pc);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "jump to %d", (int) new_pc);
#endif
            myStack->pushBoolean(boolean_);
          } else if (boolean_ == false){
            break;
          }
          break;

       case pcode__BYTE: 
         byte_ = myStack->popByte(); 
				  if (byte_ == 0 && andalso || byte_ != 0 && !andalso){
					  myPcode->setPos(new_pc);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "jump to %d", (int) new_pc);
#endif
            myStack->pushByte(byte_);
          } else if (byte_ == 0){
            break;
				  }
         break;
       case pcode__SHORT: 
         short_ = myStack->popShort(); 
				  if (short_ == 0 && andalso || short_ != 0 && !andalso){
					  myPcode->setPos(new_pc);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "jump to %d", (int) new_pc);
#endif
            myStack->pushShort(short_);
          } else if (short_ == 0){
            break;
				  }
         break;
       case pcode__INTEGER: 
         integer_ = myStack->popInteger(); 
				  if (integer_ == 0 && andalso || integer_ != 0 && !andalso){
					  myPcode->setPos(new_pc);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "jump to %d", (int) new_pc);
#endif
            myStack->pushInteger(integer_);
          } else if (integer_ == 0){
            break;
				  }
         break;
				case pcode__LONG: 
          long_ = myStack->popLong(); 
				  if (long_ == 0 && andalso || long_ != 0 && !andalso){
					  myPcode->setPos(new_pc);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "jump to %d", (int) new_pc);
#endif
            myStack->pushLong(long_);
          } else if (long_ == 0){
            break;
          }
          break;

				case pcode__SINGLE: 
          single_ = myStack->popSingle();   
				  if (single_ == 0 && andalso || single_ != 0 && !andalso){
					  myPcode->setPos(new_pc);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "jump to %d", (int) new_pc);
#endif
            myStack->pushSingle(single_);
          } else if (single_ == 0){
            break;
          }
          break;
       case pcode__DOUBLE: 
         double_ = myStack->popDouble(); 
				  if (double_ == 0 && andalso || double_ != 0 && !andalso){
					  myPcode->setPos(new_pc);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "jump to %d", (int) new_pc);
#endif
            myStack->pushDouble(double_);
          } else if (double_ == 0){
            break;
          }
         break;

   case pcode__EQSTRING:
       {
        int id = myStack->popQStringId();
        t_qstring s = estatics->getQString(id, 0);

          if (s == 0 && andalso || s != 0 && !andalso){
					  myPcode->setPos(new_pc);
#ifdef HAS_CONSOLE
            if (!bSilent) sprintf(acStringOutputBuffer, "jump to %d", (int) new_pc);
#endif
            myStack->pushQStringId(id);
          } else if (s == 0){
            break;
				  }
       }
         break;

       default:

        break;

      }


	  }

#ifdef HAS_CONSOLE
    if (!bSilent){
	    CONSOLE pcodePrint(acStringOutputBuffer);
		  CONSOLE pcodePrintCR();
    }
#endif

	} // } else return pcodeError(utility::con(pcode::pcode_(pcode__CJMP), " missing"));
	return;
}


void interpreter::fJMP()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


	t_pcode jmp; t_integer new_pc;

	myPcode->rd_JMP(&jmp, &new_pc);
  {
  /*  if (new_pc == 4803){
      new_pc = new_pc;
    }*/

		new_pc += myLocalFrame.last()->subPcodeOffset;

#ifdef HAS_CONSOLE
    if (!bSilent) info(nPos, pcode__JMP, new_pc);
#endif
   /*
    if (new_pc == 180215){
      new_pc = new_pc;
    }
*/
		{
			myPcode->setPos(new_pc);
		}
		return;

	} // } else return pcodeError(utility::con(pcode::pcode_(pcode__JMP), " missing"));
}

void interpreter::fONERRORGOTO()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


	t_pcode onerrorgoto; t_integer new_pc;

	myPcode->rd_ONERRORGOTO(&onerrorgoto, &new_pc);
  {


#ifdef HAS_CONSOLE
    if (!bSilent) info(nPos, pcode__ONERRORGOTO, new_pc);
#endif
    

		// subs a,b,c fehler tritt in c auf handler ist aber in a definiert, ist onerrorgoto nicht definiert muss eine msgbox mit fehlerausgabe kommen
		
		{
			myLocalFrame.last()->onErrorGotoPos = new_pc;
		}
		return;

	} // } else return pcodeError(utility::con(pcode::pcode_(pcode__ONERRORGOTO), " missing"));
}

void interpreter::fRESUME()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


	t_pcode resume; t_integer new_pc;

	myPcode->rd_RESUME(&resume, &new_pc);
  {



#ifdef HAS_CONSOLE
    if (!bSilent) info(nPos, pcode__RESUME, new_pc);
#endif
    

    nRuntimeErrorLine2 = -1;
    sRuntimeErrorFile2 = "";
    nRuntimeErrorNo = -1;

		{
			if (new_pc == -1){ // resume next
				myPcode->setPos(nRuntimeErrorPos2 + myLocalFrame.last()->subPcodeOffset);
			} else if (new_pc == 0){ // resume [0]
				if (nRuntimeErrorPos != -1){
					myPcode->setPos(nRuntimeErrorPos1 + myLocalFrame.last()->subPcodeOffset);
					nRuntimeErrorPos1 = -1;
				} else {
					 runtimeError("no error occured, resume not possible");
           return;
				}
			} else { // resume label
				myPcode->setPos(new_pc + myLocalFrame.last()->subPcodeOffset);
			}
		}
		return;

	} // } else return pcodeError(utility::con(pcode::pcode_(pcode__RESUME), " missing"));
}

void interpreter::interruptDebugAtBreakpoint(QString file, t_integer line)
{  
  fflush(stdout);
  interrupt_interpret();

  QByteArray a = file.toLocal8Bit();

  fprintf(stdout, "interruptDebugAtBreakpoint|");
  fprintf(stdout, a.data());
  fprintf(stdout, "|");
  fprintf(stdout, "%d", line);
  fprintf(stdout, "|");
  fflush(stdout);

  
  QFile::remove(debuginfo.fileName());
  debuginfo.open(QFile::WriteOnly);
  if (!debuginfo.isOpen()) return;

  
  QString sName;
  QString s;
  QString sType; 
  int nType;
  QString sValue;

  // globals
  {
    
    memory_variable2 *v = getGlobalVar();

    if (v->first()){
        do {
          int nId = v->getId();

          sName = v->getName(nId);
          sValue = v->toQString(nId);
          nType = v->type(nId);
          if (nType == pcode__LQSTRING){
            sType = "String";
          } else if (nType == pcode__LCSTRING){
            sType = "CString";
          } else {
            sType = findTypes(nType);
          }
          if (memory_type::scalar(nType)){
            sType = sType.left(1) + sType.mid(1).toLower();
          }

          QString s;

          s = QString("%1").arg((t_integer) 1, 5);
          debuginfo.write(s.toUtf8());

          s = QString("%1").arg((t_integer) sName.length(), 5);
          debuginfo.write(s.toUtf8());

          s = QString("%1").arg((t_integer) sValue.length(), 5);
          debuginfo.write(s.toUtf8());

          s = QString("%1").arg((t_integer) sType.length(), 5);
          debuginfo.write(s.toUtf8());

          debuginfo.write(sName.toUtf8());
          debuginfo.write(sValue.toUtf8());
          debuginfo.write(sType.toUtf8());          

        } while (v->next());
    }
  }

  // me
  {
    
    memory_variable2 *v = getMeVar();

    if (v && v->first()){
        do {
          int nId = v->getId();

          sName = v->getName(nId);
          sValue = v->toQString(nId);
          nType = v->type(nId);
          if (nType == pcode__LQSTRING){
            sType = "String";
          } else if (nType == pcode__LCSTRING){
            sType = "CString";
          } else {
            sType = findTypes(nType);
          }
          if (memory_type::scalar(nType)){
            sType = sType.left(1) + sType.mid(1).toLower();
          }

          QString s;

          s = QString("%1").arg((t_integer) 4, 5);
          debuginfo.write(s.toUtf8());

          s = QString("%1").arg((t_integer) sName.length(), 5);
          debuginfo.write(s.toUtf8());

          s = QString("%1").arg((t_integer) sValue.length(), 5);
          debuginfo.write(s.toUtf8());

          s = QString("%1").arg((t_integer) sType.length(), 5);
          debuginfo.write(s.toUtf8());

          debuginfo.write(sName.toUtf8());
          debuginfo.write(sValue.toUtf8());
          debuginfo.write(sType.toUtf8());          

        } while (v->next());
    }
  }

  // locals
  {
    
    if (myLocalFrame.count()){

      local_frame_ *lf = myLocalFrame.last();
      if (lf){
        memory_variable2 *v = lf->localVars;

        if (v && v->first()){
          do {
            int nId = v->getId();

            sName = v->getName(nId);

       //     QMessageBox::information(0, sName, "");

            sValue = v->toQString(nId);
            nType = v->type(nId);
            if (nType == pcode__QSTRING || nType == pcode__LQSTRING){
              sType = "String";
            } else if (nType == pcode__CSTRING || nType == pcode__LCSTRING || nType == pcode__WSTRING){
              sType = "CString";
            } else {
              sType = findTypes(nType);
            
              if (memory_type::scalar(nType)){
                sType = sType.left(1) + sType.mid(1).toLower();
              }
            }


            QString s;

            s = QString("%1").arg((t_integer) 2, 5);
            debuginfo.write(s.toUtf8());

            s = QString("%1").arg((t_integer) sName.length(), 5);
            debuginfo.write(s.toUtf8());

            s = QString("%1").arg((t_integer) sValue.length(), 5);
            debuginfo.write(s.toUtf8());

            s = QString("%1").arg((t_integer) sType.length(), 5);
            debuginfo.write(s.toUtf8());

            debuginfo.write(sName.toUtf8());
            debuginfo.write(sValue.toUtf8());
            debuginfo.write(sType.toUtf8());          

          } while (v->next());
        }
      }
    }
  }

  // stacks
  { 
    
    if (myLocalFrame.count()){
      static char ac[1024];

      local_frame::const_iterator ii;
      for (ii = myLocalFrame.constBegin(); ii != myLocalFrame.constEnd(); ++ii){
        int i = 0;

        local_frame_ *lf = *ii;

        if (lf && lf->bGlobal == false){
          sName = lf->acName;

          i++;
          s = s.sprintf("%2d : ", i);
          s += sName;

          sValue = "";
          sType = "";


          QString s;

          s = QString("%1").arg((t_integer) 3, 5);
          debuginfo.write(s.toUtf8());

          s = QString("%1").arg((t_integer) sName.length(), 5);
          debuginfo.write(s.toUtf8());

          s = QString("%1").arg((t_integer) sValue.length(), 5);
          debuginfo.write(s.toUtf8());

          s = QString("%1").arg((t_integer) sType.length(), 5);
          debuginfo.write(s.toUtf8());

          debuginfo.write(sName.toUtf8());
          debuginfo.write(sValue.toUtf8());
          debuginfo.write(sType.toUtf8());          
          
        }      
      }
    }
    
    myLocalFrame.last();

  }

  debuginfo.close(); 

  return;

}

void interpreter::fSTATEMENT()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif

	t_pcode statement; t_integer next_pc;  t_integer next_pc2; t_cstring file; t_integer line;


	myPcode->rd_STATEMENT(&statement, &next_pc, &next_pc2, &file, &line);

  {
    static char ac[1024];
#ifdef HAS_CONSOLE
    if (!bSilent){
      
      nCurrentLine = line;
      sprintf(ac, "line %d", line);
      info(nPos, file, ac);

	    CONSOLE pcodePrintSep("");
      if (strcmp(acCurrentFile, file) != 0){
        acCurrentFile = file;
 	      CONSOLE pcodePrint(file);
        CONSOLE pcodePrint(" in ");
      }
 	    CONSOLE pcodePrint(ac);
 	    CONSOLE pcodePrintCR();
/*
      if (next_pc == 181){
        next_pc = next_pc;
      }*/

      info(nPos, pcode__STATEMENT, next_pc);
    }
		
#endif

    
		{
      if (nRuntimeErrorNo == -1){
			  nRuntimeErrorPos = next_pc;
        nRuntimeErrorPos2 = next_pc2;
        nRuntimeErrorLine = line;
        sRuntimeErrorFile = file;
      }

      if (bStepOut && myLocalFrame.count() == nStepToCursorLine){
        nStepToCursorLine = 0;
        bStepOut = false;
        bStepIn = true;
      }

      if (bStepOver && nStepToCursorLine > 0 && myLocalFrame.count() <= nStepToCursorLine){
        nStepToCursorLine = 0;
        bStepOver = false;
        bStepIn = true;
      }

//      fprintf(stdout, "====%d %d\n", (int) nStepToCursorLine, (int) strcmp(acStepToCursorFile, file) == 0);

      if (bDebug && (bStepIn || hasBreakpoint(file, line) || (bStepToCursor && nStepToCursorLine == line && sStepToCursorFile == file))){
        interruptDebugAtBreakpoint(file, line);
      }

		}
		return;

	} // } else return pcodeError(utility::con(pcode::pcode_(pcode__STATEMENT), " missing"));
}	

void interpreter::fSTATEMENT_OUT()
{
  
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


	t_pcode statement_out; t_cstring file; t_integer line;

	myPcode->rd_STATEMENT_OUT(&statement_out, &file, &line);
  {
    
#ifdef HAS_CONSOLE
    if (!bSilent) info(nPos, pcode__STATEMENT_OUT, line);
#endif

    {

		}
		return;

	} // } else return pcodeError(utility::con(pcode::pcode_(pcode__STATEMENT_OUT), " missing"));
}	

void interpreter::fSTATEMENT_OVER()
{
  
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


	t_pcode statement_over; t_cstring file; t_integer line;

	myPcode->rd_STATEMENT_OVER(&statement_over, &file, &line);
  {
    {
#ifdef HAS_CONSOLE
      if (!bSilent) info(nPos, pcode__STATEMENT_OVER, line);
#endif
      
      if (bDebug && bStepOver && nStepToCursorLine + 1 == line && sStepToCursorFile == file){        
        interruptDebugAtBreakpoint(file, line);       
      }
      
		}
		return;

	} // } else return pcodeError(utility::con(pcode::pcode_(pcode__STATEMENT_OVER), " missing"));
}	

void interpreter::fSTATEMENT_CURSOR()
{

#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


	t_pcode statement_cursor; t_cstring file; t_integer line;

	myPcode->rd_STATEMENT_CURSOR(&statement_cursor, &file, &line);
  {
#ifdef HAS_CONSOLE
    if (!bSilent) info(nPos, pcode__STATEMENT_CURSOR, line);
#endif

    {
      
      if (bDebug && bStepToCursor && nStepToCursorLine == line && sStepToCursorFile == file){          
        interruptDebugAtBreakpoint(file, line);       
      }
      
		}
		return;

	} // } else return pcodeError(utility::con(pcode::pcode_(pcode__STATEMENT_CURSOR), " missing"));
}	

void interpreter::fONERRORGOTORESUMENEXT()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


	t_pcode c;

	myPcode->rd_ONERRORGOTORESUMENEXT(&c);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info(nPos, pcode__ONERRORGOTORESUMENEXT);
#endif
    

		{
			myLocalFrame.last()->onErrorGotoPos = -1;
		}
		return;

	} // } else return pcodeError(utility::con(pcode::pcode_(pcode__ONERRORGOTORESUMENEXT), " missing"));
}

void interpreter::fCALL()
{

	register int nPos = myPcode->getPos();



	t_pcode call; t_integer new_pc; t_integer return_pc;

	myPcode->rd_CALL(&call, &new_pc, &return_pc);
  {

    return_pc += nPos;

#ifdef HAS_CONSOLE
    if (!bSilent && return_pc != nPos) infoCall(nPos, pcode__CALL, new_pc, return_pc);
#endif
    
	  // 
    if (new_pc) myLocalFrame.last()->subPcodeOffset = new_pc;
    else if (return_pc == nPos) myLocalFrame.last()->subPcodeOffset = return_pc;
    else { 
      pcodeError("new position for CALL is zero");
      return;

    }
    myLocalFrame.last()->onErrorGotoPos = 0;
    myLocalFrame.last()->return_pos = return_pc;

		{
			if (return_pc != nPos) myPcode->setPos(new_pc); // if return_pc == nPos then it is the global jump offset for global code
		}


		return;

	} // } else return pcodeError(utility::con(pcode::pcode_(pcode__CALL), " missing"));
}

void interpreter::fLIBCALL()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


	t_pcode c; t_cstring lib; t_cstring function; 
  t_integer return_type; t_integer count; t_cstring signature;


	myPcode->rd_LIBCALL(&c, &lib, &function, &return_type, &count, &signature);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info(nPos, pcode__LIBCALL);
#endif
    
    
    callLib(getVar(local), lib, function, return_type, count, signature);

		//return;

	} // } else return pcodeError(utility::con(pcode::pcode_(pcode__LIBCALL), " missing"));
}

void interpreter::fCATCH()
{

	register int nPos = myPcode->getPos();



	t_pcode c; t_integer class_id; t_integer catch_pc;

	myPcode->rd_CATCH(&c, &class_id, &catch_pc);
  {

    t_integer n;
    n = catch_pc + nPos;

#ifdef HAS_CONSOLE
    if (catch_pc > 0){
      if (!bSilent) infoCatch(nPos, pcode__CATCH, class_id, n);
    } else {
      if (!bSilent) infoCatch2(nPos, pcode__CATCH, class_id);
	  }
#endif
    
    
    bool bb = true;
    switch(class_id){
      case pcode__EXCEPTION:
      case pcode__CASTEXCEPTION:
        {
          if (bCatchBuiltinException == false){
            nExceptionCountParamToRemove = 0;
            return;
          }
          for (int i = 0; i < nExceptionCountParamToRemove; i++){

            interpreter_parameter *pp = popStack(); delete pp; // stack muss ein element runternehmen, gilt auch fr isnumeric
          }
          nExceptionCountParamToRemove = 0;

          bb = false; 
        }
        break;
    }

    if (bb){
      t_pcode c;
      c = myStack->peekPCode();

      if (c != 309 && memory_type::isObject(c)){ // WORKAROUND c != 309
       
       myStack->popPCode();

       memory_variable2 *v;
       bool b44 = myStack->popBoolean();
       bool memory_variable2_ = myStack->popBoolean();
       v = (memory_variable2 *) myStack->popPointer();

       if (class_id == myLocalFrame.last()->tryCatch){
         myLocalFrame.last()->tryCatch = 0;
       }

       if (v && v->getClassId() == class_id){

         if (catch_pc > 0){
 			      myPcode->setPos(n);
         } else {
           int nValue = myLocalFrame.last()->return_pos;
		        exitLocal();
  	        myPcode->setPos(nValue);		     
		     }
       }

       myStack->pushPointer(pcode__OBJECT, v, false, true);

      }
    } else {
        myPcode->setPos(n);

    }

		return;

	} // } else return pcodeError(utility::con(pcode::pcode_(pcode__CATCH), " missing"));
}

void interpreter::fCALLMETHOD()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


	t_pcode c; t_integer new_pc;

	myPcode->rd_CALLMETHOD(&c, &new_pc);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info(nPos, pcode__CALLMETHOD, new_pc);
#endif

		// fCALL & callSub 
    enterLocal("");

		{
			myPcode->setPos(new_pc);
		}

		return;

	} // } else return pcodeError(utility::con(pcode::pcode_(pcode__CALLMETHOD), " missing"));
}

void interpreter::fRETURN()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


	t_pcode return_;

	myPcode->rd_RETURN(&return_);
  {



    t_integer nValue;
    t_pcode cType;

   	cType = myStack->popPCode();
    switch (cType){
 	    case pcode__INTEGER: 
        nValue = myStack->popInteger();
        nValue += myLocalFrame.last()->subPcodeOffset;
        break;
			default:
				pcodeError("wrong datatype of RETURN address on stack");
        return;
			  break;
    }

#ifdef HAS_CONSOLE
		if (!bSilent) info(nPos, pcode__RETURN, nValue);
#endif
		{
			myPcode->setPos(nValue);
		}
		return;

	} // } else return pcodeError(utility::con(pcode::pcode_(pcode__RETURN), " missing"));
}


void interpreter::fCHOOSE()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


	t_pcode choose; t_integer count; t_boolean bReturn;

	myPcode->rd_CHOOSE(&choose, &count, &bReturn);
  {

#ifdef HAS_CONSOLE
		if (!bSilent) info(nPos, pcode__CHOOSE);
#endif

		QMap<int, interpreter_parameter*> v;

		for (int i = 0; i < count; i++){
				v[i] = popStack();
		}

		int n = popStackInteger();

/*

Choose evaluates every choice in the list, even though it returns only one. 
For this reason, you should watch for undesirable side effects. 
For example, if you use the MsgBox function as part of an expression in all the choices, 
a message box will be displayed for each choice as it is evaluated, 
even though Choose returns the value of only one of them.

The Choose function returns a Null if index is less than 1 or greater than the number of choices listed.
If index is not a whole number, it is rounded to the nearest whole number before being evaluated.

*/
		if (n - 1 < 0 || n > count){
			
			runtimeError("CHOOSE index out of bounds");
      return;
		}

		if (bReturn){
			pushStack(v[count - n]);
		} 

    // delete restlicher v
		for (int i = 0; i < count; i++){
				if (i != count - n) delete v[i];
		}
    
		return;

	} // } else return pcodeError(utility::con(pcode::pcode_(pcode__CHOOSE), " missing"));
}


void interpreter::fFIELD()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


	t_pcode c; t_boolean bEXPRESSION2; t_integer count;

	myPcode->rd_FIELD(&c, &bEXPRESSION2, &count);
  {

#ifdef HAS_CONSOLE
		if (!bSilent) info(nPos, pcode__FIELD);
#endif
    

		QMap<int, interpreter_parameter*> v;

		for (int i = 0; i < count; i++){
				v[i] = popStack();
		}

		int n = popStackInteger();

		return;

	} // } else return pcodeError(utility::con(pcode::pcode_(pcode__FIELD), " missing"));
}

void interpreter::fSWITCH()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


	t_pcode switch_; t_integer count; t_boolean bReturn;

	myPcode->rd_SWITCH(&switch_, &count, &bReturn);
  {

#ifdef HAS_CONSOLE
		if (!bSilent) info(nPos, pcode__SWITCH);
#endif

		QMap<int, interpreter_parameter*> v;

		for (int i = 0; i < count * 2; i++){
				v[i] = popStack();
		}

		for (int z = 0; z < count; z++){
			if (v[z * 2 + 1]->toBoolean()){
				if (bReturn){
					pushStack(v[z * 2 + 0]);

          // delete restlicher v
		      for (int i = 0; i < count; i++){
				      if (i != z * 2 + 0) delete v[i];
		      }

					return;
				}
			}
		}

		runtimeError("SWITCH no matching");

	} // } else return pcodeError(utility::con(pcode::pcode_(pcode__SWITCH), " missing"));
}

void interpreter::fIIF()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


	t_pcode iif; t_boolean bReturn;

	myPcode->rd_IIF(&iif, &bReturn);
  {

#ifdef HAS_CONSOLE
		if (!bSilent) info(nPos, pcode__IIF);
#endif

    EXPRESSION[2] = popStack();
    EXPRESSION[1] = popStack();
    BOOLEAN_EXPRESSION[0] = popStackBoolean();

		if (bReturn){
			if (BOOLEAN_EXPRESSION[0]){
				pushStack(EXPRESSION[1]);
        delete EXPRESSION[0];
			} else {
				pushStack(EXPRESSION[2]);
        delete EXPRESSION[1];
			}
		}

		return;

	} // } else return pcodeError(utility::con(pcode::pcode_(pcode__IIF), " missing"));
}

void interpreter::fTRY()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif

  t_builtin c;

  myPcode->rd_TRY(&c);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__TRY);
#endif

    myLocalFrame.last()->tryCatch = 999999;
    
  } // } else return pcodeError(utility::con(pcode::builtin_(pcode__TRY), " missing"));

  return;
}

void interpreter::fENDCATCH()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif

  t_builtin c;

  myPcode->rd_ENDCATCH(&c);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info2(nPos, pcode__TRY);
#endif

    if (myLocalFrame.last()->tryCatch != 999999 && myLocalFrame.last()->tryCatch != 0){
      QByteArray ba = sRuntimeErrorTxt.toLocal8Bit();
      runtimeError(ba.data(), myLocalFrame.last()->tryCatch);
      //myLocalFrame.last()->tryCatch = 0;
    }
    
    
  } // } else return pcodeError(utility::con(pcode::builtin_(pcode__TRY), " missing"));

  return;
}
