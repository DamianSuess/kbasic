/*
***************************************************************************
Copyright (C) 2000-2008 KBasic Software: www.kbasic.com. All rights reserved.
Source codes are copyrighted by Bernd Noetscher 2000-2008.

You may use this source codes under the terms of the GNU Public License (Version 3)
as published by the Free Software Foundation. 

If you are interested in using the source codes for other licenses or 
commercial development, you must buy commercial licenses from KBasic Software.

This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
***************************************************************************
*/


#include "parser.h"
#include "../kbshared/cache.h"



extern XString sProjectName;
extern XString sLogin;
extern XString sProjectType;
extern XString sTranslation;
extern XString sSQL;
extern XString sMenu;

extern int nTest;
extern int nTest2;

extern int nGlobalVarId;

extern memory_module *EXTERN_myModule;
extern parser *EXTERN_myParser;

bool parser::parseVeryOldBasic(token *t, bool bSilent, bool bDebug, bool bUseCache)
{
  setVERYOLDBASIC();

  return parse2(t, bSilent, bDebug, bUseCache);
}

bool parser::parseOldBasic(token *t, bool bSilent, bool bDebug, bool bUseCache)
{
  setOLDBASIC();
  
  return parse2(t, bSilent, bDebug, bUseCache);
}

bool parser::parseKBasic(token *t, bool bSilent, bool bDebug, bool bUseCache)
{
  setKBASIC();
  bProducePcode = true;
  
  bool b =  parse2(t, bSilent, bDebug, bUseCache);
  

  return b;
}

bool parser::parse(token *t, bool bSilent, bool bDebug, bool bUseCache)
{
  return parseKBasic(t, bSilent, bDebug, bUseCache);
}

// ****************************
// * bool parse2()
// *
// * description:
// * entry point for this module
// *
// * parameter:
// * none
// *
// * return:
// * true, if no error
// * false, if error occured
// ****************************
bool parser::parse2(token *t, bool _bSilent, bool _bDebug, bool _bUseCache)
{
  bUseCache = _bUseCache;

  bSilent = _bSilent;
  bDebug = _bDebug;  

  nFORNEXT = 0;

  nProceedPercent = 30;
 	     
  if (!bSilent){
    CONSOLE print("\nKBasic Parser - highly optimized top-down, recursive descent, two-pass parser & compiler, LL(1)\n(C) Copyright KBasic Software 2000 - 2006\n");
	  CONSOLE header("\n-- parse --\n\n");
    CONSOLE print( utility::con("VERSION ", parser__KBASIC_VERSION, "\n\n") );
  }

  nPeekVar = 0; PeekScope = global; nPeekType = 0;

  nExpectedType = 0;

  bGLOBAL_EOL = false;
  bGLOBAL_SYM_UL = false;

  with_pos_list_POS = -1;

  nIfStatement = 0;

  sCurrentLib = "";

  // ***
  with.With = 0; // reset  
  with.WithToken = 0;
  // ** 

  bParserPhase1 = false;
  bParserPhase2 = false;

  bParseToken = true;
	bNoError = true; // syntax/parser/symantic error occured

	myToken = t;

  
  EXTERN_myModule = myModule; // needed for cache.cpp
  EXTERN_myParser = this; // needed for cache.cpp

  
	myPcodeDefault->resetPos();
	myPcodeDefault2->resetPos();
	myPcodeAll->resetPos();
	myPcodeData->resetPos();  
	myToken->resetPos(false);

  if (my_cache) my_cache->setMode(bSilent, bDebug); // important, setting right file name for caching

  {
  	bProducePcode = false;

	  setCurrentLine(0); // contains the current parsed source code line
	  setCurrentRow(0); // contains the current parsed source code row

   	bProducePcode = true;
  }

  setCurrentFile("");
  setCurrentEnum("");

  setScopeDefaultGlobal();
  if (bUseCache && my_cache) my_cache->wr_parserOpen(this, acDefaultModuleName);
  if (my_cache) my_cache->initParser(); // needed to create pcode map

  nDataCount = 0;
	nLastStatementPcode = 0;

  registerBuiltinTypes();
  registerBindingTypes();


  nProceedPercent += 5; if (bNoError){ CONSOLE printKBPROGRESS(nProceedPercent); }

  memory_variable::resetIdCounter(); // important


  myModule->addModule(acDefaultModuleName, new pcode(acDefaultModuleName), 0, acDefaultModuleName); // ist nur ein fake, pcode wird nicht wirklich gefllt, weil alles in myPcode, was dieses modul betrifft hineinflie�

  
  // write the initial pcode / header
	int nJMPpos = 0;
	int nSTARTpos = 0;

  myPcode = myPcodeAll;

	if (bProducePcode){
    int aa = myPcode->getPos();

   // CONSOLE printError("11111111111111111\n");

    myPcode->wr_KBASIC(pcode__KBASIC, pcode::pcode_(pcode__KBASIC), (char *) sProjectName.ascii(), (char *) sProjectType.ascii(), (char *) sLogin.ascii());



    aa = myPcode->getPos();

  	myPcode->wr_VER(pcode__VER, parser__KBASIC_VERSION);

    aa = myPcode->getPos();

    myPcode->wr_SEPARATOR(pcode__SEPARATOR, " START BLOCK"); // leading space used for cutting of the leading f...

    aa = myPcode->getPos();
        
    myPcode->wr_SILENTMODE(pcode__SILENTMODE, bSilent); // interpreter's debug output on/off  	
  	
    myPcode->wr_SEPARATOR(pcode__SEPARATOR, " OPTIONS / DEFAULTS"); // leading space used for cutting of the leading f...
  
    myPcode->wr_OPTION_RANGE(pcode__OPTION_RANGE, false); // set under/overflow range check off

  	nJMPpos = myPcode->getPos();
  	myPcode->wr_JMP(pcode__JMP, 0); // jump to registrations

    nSTARTpos = myPcode->getPos(); // position of first normal statement
	}


  registerBuiltinConsts();

  {
	  defaultvalue defval;
    int nString = registerStringLiteral(defval.cstring_);
    if (nString == 0){ internalError( utility::con(defval.cstring_, " string literal not declared") ); }
  }

	if (bProducePcode){
  	myPcode->wr_SILENTMODE(pcode__SILENTMODE, false); // interpreter's debug output on/off
  }

	bool bRet = true;

  nProceedPercent += 5; if (bNoError){ CONSOLE printKBPROGRESS(nProceedPercent); }

  parseInfo(0, " 1st PHASE --> sub/type... registrations\n");

  bParserPhase0 = true;
  if (bRet && (bRet = registerAll())){} // 0st phase --> all types are registered without really parsing them
  bParserPhase0 = false;

  nProceedPercent += 5; if (bNoError){ CONSOLE printKBPROGRESS(nProceedPercent); }

  bParserPhase1 = true;
  if (bRet && (bRet = registerAll2())){} // 1st phase --> sub/type... registrations

  if (bRet && myClass->first()){
    acCurrentFile = "";

    do {
      int nClassId = myClass->getId();
      int nParentId = myClass->getParentId(nClassId);

      if (nParentId <= 0){
        const char *ac = myClass->getParentName(nClassId);
        nParentId = myClass->getId(myClass->getParentName(nClassId)); // user defined parent class
        if (nParentId == 0){
          const char *acClassName = myClass->getName(nClassId);
          if (strcmp(myClass->getParentName(nClassId), "") == 0 || utility::my_stricmp(myClass->getParentName(nClassId), "Object") == 0){
             nParentId = 0; // object
          } else {
           { semanticError(token__CLASS, utility::con(myClass->getParentName(nClassId), " is used as parent class, but is not defined anywhere") ); _TERROR_ }
              
          }
        }
        myClass->setParentId(nClassId, nParentId);

      }

    } while (myClass->next());

  }

  nProceedPercent += 5; if (bNoError){ CONSOLE printKBPROGRESS(nProceedPercent); }

  if (bRet && myClass->first()){
    do {
      if (my_cache == 0 || !myClass->isCached(myClass->getId())){
        int nClassId = myClass->getId();
        
        setScopeClass(myClass->getParentName(nClassId), myClass->getName(nClassId));

		    fREGISTER_CLASS_DEFAULT_CONSTRUCTOR();
		    fREGISTER_CLASS_DEFAULT_DESTRUCTOR();     
      }

    } while (myClass->next());

    setScopeDefaultGlobal();
  }

  nProceedPercent += 5; if (bNoError){ CONSOLE printKBPROGRESS(nProceedPercent); }


  bParserPhase1 = false;

  setKBASIC(); // needed, because registerAll() could have changed it

  parseInfo(0, " 2nd PHASE --> main code generation\n");

  bParserPhase2 = true;
  

	if (bProducePcode){
    myPcode->wr_SEPARATOR(pcode__SEPARATOR, " START OF PROGRAM "); // leading space used for cutting of the leading f...
  }


  int kkk = myPcode->getPos();

  pcode *myPcodeDeclaration = new pcode("");


  // *** append different global pcode of different files - every file has one global pcode
  // *** must be placed before fKBASIC, because of global enums, types, vars, consts = DECLARATIONS
  // *** DECLARATIONS
  int nDeclarationCallCount = 0;
  if (bRet && my_cache){
  
    // * do cached parts
    if (my_cache->myDeclaration2) myPcodeDeclaration->pcodeWritePcode(my_cache->myDeclaration2);
    // *

    if (pcs.first(&key, &value)){
      do {
        pcode *m = (pcode *) value;

        // do non-cached parts
        if (my_cache->parserOpened(m->sCurrentFile.ascii())){

          int nLen =  m->getSize();
          m->nDeclarationSize = nLen;

          int nPos = myPcode->getPos();
          myPcodeDeclaration->pcodeWritePcode(m);       
          if (my_cache->parserOpened(m->sCurrentFile.ascii())) my_cache->wr_pcodeBlock(m->sCurrentFile.ascii(), pcodeBlock, m, m->getSize(), declaration2);
          
          if (bProducePcode) m->wr_CALL(pcode__CALL, 0, 0); // set global jump offset, later real address
          nDeclarationCallCount++;
        
        }
      } while (pcs.next(&key, &value));
    }
  }
  // ***

  nTest = myPcodeDeclaration->ba->getSize();
  nTest2 = nDeclarationCallCount * pcode::len(pcode__CALL);
  int kk = kkk + myPcodeDeclaration->ba->getSize();

 	if (bRet && (bRet = fKBASIC())){} // 2nd phase --> main code generation

  

  myPcode->pcodeWritePcode(myPcodeDefault); // prepend default.kbasic before any declarations
  myPcode->pcodeWritePcode(myPcodeDeclaration);
  myPcode->pcodeWritePcode(myPcodeDefault2); // prepend default.kbasic before any declarations
  delete myPcodeDeclaration;

  myPcode->pcodeWritePcode(myPcodeData); // prepend default.kbasic before any declarations



  int kk2 = myPcode->getPos();

  bParserPhase2 = false;  


  // ***  correct the offset
  if (bRet && my_cache){

    if (pcs.first(&key, &value)){
      do {
        pcode *m = (pcode *) value;

        // do non-cached parts
        if (my_cache->parserOpened(m->sCurrentFile.ascii())){
          

          int nLen =  m->getSize();
          int o = pcs.size();
          if (m->nAppendOffset2) m->nAppendOffset2 += kk2 - kk;
          if (bProducePcode){
            int n = m->getPos();
            m->setPos(m->nAppendOffset3);  

            // set global jump offset, all jmp pcodes will get new jump offset

            m->wr_CALL(pcode__CALL, o == 1 ? kkk + (kk2 - kk) : m->nAppendOffset2, 0); 
            m->setPos(n);
          }
        }

    
      } while (pcs.next(&key, &value));
    }   
  }
  // ***

  //int tt = myPcode->getPos();

	if (bProducePcode && bNoError){

     if (bRet = cleanUpLabels()){} // label position will be refilled after the complete program is parsed, last step, before using place holder

      // *** append different global pcode of different files - every file has one global pcode
      // *** global statements - CODE
      // *** STATEMENTS
      
      if (bRet && my_cache){

        if (pcs.first(&key, &value)){
          do {
            pcode *m = (pcode *) value;

            // do non-cached parts
            if (my_cache->parserOpened(m->sCurrentFile.ascii())){

              int aa = myPcode->getPos();

              myPcode->pcodeWritePcode(m, m->nAppendOffset3);
            }
          
            // * do cached parts
            if (my_cache->myStatements2){
              int aa = my_cache->myStatements2->getSize();
              myPcode->pcodeWritePcode(my_cache->myStatements2);
              my_cache->myStatements2->nAppendOffset2 -= my_cache->myDeclaration2->getSize();
            }    
            // *
        
          } while (pcs.next(&key, &value));
        }
      }
      // ***


      const char *aa = myPcode->ba->getMem();

    // markiere ende, damit nicht ausversehen subs ausgefhrt werden
	  if (bProducePcode){      
      int aa = myPcode->getPos();
      myPcode->wr_SEPARATOR(pcode__SEPARATOR, " END OF PROGRAM "); // leading space used for cutting of the leading f...    
      aa = myPcode->getPos();
		  myPcode->wr_PCode(pcode__END); // append END pcode
	  }


  



     if (bRet && (bRet = appendAllModules(myPcode))){} // append the pcode of all subs     

     if (bProducePcode){

      int n = myPcode->getPos();

			myPcode->setPos(nJMPpos);
			myPcode->wr_JMP(pcode__JMP, n);

			myPcode->setPos(n);
  		
		  appendAllStringLiterals(); // append all static Strings


      if (!sTranslation.isEmpty()) myPcode->wr_TRANSLATION(pcode__TRANSLATION, (char *) sTranslation.ascii());
      if (!sSQL.isEmpty()) myPcode->wr_SQL(pcode__SQL, (char *) sSQL.ascii());
      if (!sMenu.isEmpty()) myPcode->wr_MENU(pcode__MENU, (char *) sMenu.ascii());
  


     if (bRet && (bRet = appendAllClassesStatic())){} // static vars, treated like global vars
		 
     if (bRet && (bRet = appendAllClasses(myPcode))){} // append the pcode of all subs     

     if (bRet && (bRet = appendAllProjectFiles(myPcode))){} // append the pcode

     if (bRet && (bRet = appendAllBreakpoints(myPcode))){} // append the pcode

			myPcode->wr_JMP(pcode__JMP, nSTARTpos);

      // *** append different global pcode of different files - every file has one global pcode
      // *** global statements - CODE
      
      if (bRet && my_cache){
        if (pcs.first(&key, &value)){
          do {
            pcode *m = (pcode *) value;

            // do non-cached parts
            if (my_cache->parserOpened(m->sCurrentFile.ascii())){


              int nLen =  m->getSize();
              int nPos =  myPcode->getPos();

              if (m->nDeclarationSize){
                if (bRet && my_cache && my_cache->parserOpened(m->sCurrentFile.ascii())){ my_cache->wr_pcodeBlock(m->sCurrentFile.ascii(), pcodeBlock, m, m->getSize() - m->nAppendOffset4, statements2, m, m->nAppendOffset4); }
              } else {
                if (bRet && my_cache && my_cache->parserOpened(m->sCurrentFile.ascii())){ my_cache->wr_pcodeBlock(m->sCurrentFile.ascii(), pcodeBlock, m, m->getSize(), statements2); }
              }
            }


          } while (pcs.next(&key, &value));
        }
         
      }



      if (my_cache) my_cache->wr_parserCloseAll(bRet);
			
		}
    
    // ***

	}	else {
		myPcode->setPos(0);
	}

  // ***   

  if (pcs.first(&key, &value)){
    do {
      pcode *m = (pcode *) value;
      delete m;
    } while (pcs.next(&key, &value));
  }

  pcs.clear();

  nProceedPercent = 100; if (bNoError){ CONSOLE printKBPROGRESS(nProceedPercent); }


 
	if (!bSilent) CONSOLE print("\n");

	return bProducePcode & bRet & bNoError;
}

bool parser::registerBuiltinTypes()
{
	// register builtin types
	registerTypePublic(pcode::pcode_(pcode__ANY), pcode__ANY);

  registerTypePublic(pcode::pcode_(pcode__BOOLEAN), pcode__BOOLEAN);

	registerTypePublic(pcode::pcode_(pcode__QSTRING), pcode__QSTRING);
	registerTypePublic(pcode::pcode_(pcode__LQSTRING), pcode__LQSTRING);
	registerTypePublic(pcode::pcode_(pcode__CSTRING), pcode__CSTRING);
	registerTypePublic(pcode::pcode_(pcode__LCSTRING), pcode__LCSTRING);
  
  registerTypePublic(pcode::pcode_(pcode__BYTE), pcode__BYTE);
  registerTypePublic(pcode::pcode_(pcode__SHORT), pcode__SHORT);
	registerTypePublic(pcode::pcode_(pcode__INTEGER), pcode__INTEGER);
	registerTypePublic(pcode::pcode_(pcode__LONG), pcode__LONG);

	registerTypePublic(pcode::pcode_(pcode__SINGLE), pcode__SINGLE);
	registerTypePublic(pcode::pcode_(pcode__DOUBLE), pcode__DOUBLE);
  
  registerTypePublic(pcode::pcode_(pcode__CONST), pcode__CONST);
	registerTypePublic(pcode::pcode_(pcode__REFERENCE), pcode__REFERENCE);
	registerTypePublic(pcode::pcode_(pcode__VARIANT), pcode__VARIANT);

	registerTypePublic(pcode::pcode_(pcode__CURRENCY), pcode__CURRENCY);
	registerTypePublic(pcode::pcode_(pcode__DATE), pcode__DATE);

	registerTypePublic(pcode::pcode_(pcode__OBJECT), pcode__OBJECT);
	registerTypePublic(pcode::pcode_(pcode__VOID), pcode__VOID); // used for bindings

  registerTypePublic(pcode::pcode_(pcode__CASTEXCEPTION), pcode__CASTEXCEPTION); // used for bindings
  registerTypePublic(pcode::pcode_(pcode__QTEXCEPTION), pcode__QTEXCEPTION); // used for bindings
  registerTypePublic(pcode::pcode_(pcode__EXCEPTION), pcode__EXCEPTION); // used for bindings

  //registerTypePublic(pcode::pcode_(pcode__COLLECTION), pcode__COLLECTION);

  return true;
}

bool parser::registerBuiltinClasses()
{
	// register builtin classes

  return true;
}

bool parser::registerBuiltinConsts()
{

	if (bProducePcode){
    myPcode->wr_SEPARATOR(pcode__SEPARATOR, " BUILTIN CONSTS"); // leading space used for cutting of the leading f...
  }

  // builtin consts
  registerConstPublic("Exception", pcode__EXCEPTION);
  registerConstPublic("QtException", pcode__QTEXCEPTION);
  registerConstPublic("CastException", pcode__CASTEXCEPTION);
  registerConstPublic("Return", "\n");

  registerConstPublic("kbNormal", 0);
  registerConstPublic("kbHidden", 2);
  registerConstPublic("kbSystem", 4);
  registerConstPublic("kbVolume", 8);
  registerConstPublic("kbDirectory", 16);

  registerConstPublic("kbReadOnly", 1);
  registerConstPublic("kbArchive", 32);

  registerConstPublic("kbCrLf", "\r\n");
  registerConstPublic("kbCr", "\r");
  registerConstPublic("kbLf", "\n");
  registerConstPublic("kbNewLine", "\n");
  registerConstPublic("kbTab", 9);
  registerConstPublic("kbBack", 8);
  registerConstPublic("kbNullChar", "");
  registerConstPublic("kbNullString", "");

  registerConstPublic("kbOKOnly", 0);
  registerConstPublic("kbOKCancel", 1);
  registerConstPublic("kbAbortRetryIgnore", 2);
  registerConstPublic("kbYesNoCancel", 3);
  registerConstPublic("kbYesNo", 4);
  registerConstPublic("kbRetryCancel", 5);

  registerConstPublic("kbCritical", 16);
  registerConstPublic("kbQuestion", 32);
  registerConstPublic("kbExclamation", 48);
  registerConstPublic("kbInformation", 64);

  registerConstPublic("kbDefaultButton1", 0);
  registerConstPublic("kbDefaultButton2", 256);
  registerConstPublic("kbDefaultButton3", 512);

/*
registerConst(getScope(), getSub(), "kbDefaultButton4", 768);
registerConst(getScope(), getSub(), "kbApplicationModal", 0);
registerConst(getScope(), getSub(), "kbSystemModal", 4096);
*/

  registerConstPublic("kbOK", 1);
  registerConstPublic("kbCancel", 2);
  registerConstPublic("kbAbort", 3);
  registerConstPublic("kbRetry", 4);
  registerConstPublic("kbIgnore", 5);
  registerConstPublic("kbYes", 6);
  registerConstPublic("kbNo", 7);

  registerConstPublic("kbEmpty", 0);
  registerConstPublic("kbNull", 1);
  registerConstPublic("kbInteger", 2);
  registerConstPublic("kbLong", 3);
  registerConstPublic("kbSingle", 4);
  registerConstPublic("kbDouble", 5);
  registerConstPublic("kbCurrency", 6);
  registerConstPublic("kbDate", 7);
  registerConstPublic("kbString", 8);
  registerConstPublic("kbObject", 9);
  registerConstPublic("kbError", 10);
  registerConstPublic("kbBoolean", 11);
  registerConstPublic("kbVariant", 12);
  registerConstPublic("kbByte", 17);
  registerConstPublic("kbShort", 18);
  /*
  registerConstPublic("kbInt16", 19);
  registerConstPublic("kbInt32", 20);
  registerConstPublic("kbInt64", 21);
  registerConstPublic("kbUInt16", 22);
  registerConstPublic("kbUInt32", 23);
  registerConstPublic("kbUInt64", 24);*/
  registerConstPublic("kbArray", 8192);

  registerConstPublic("kbUseSystem", 0);
  registerConstPublic("kbSunday", 1);
  registerConstPublic("kbMonday", 2);
  registerConstPublic("kbTuesday", 3);
  registerConstPublic("kbWednesday", 4);
  registerConstPublic("kbThursday", 5);
  registerConstPublic("kbFriday", 6);
  registerConstPublic("kbSaturday", 7);

/**
[KBASIC]
NAME: BUILTIN_CONST
PRINTNAME: BUILTIN_CONST
TASK: 
DESC: 
DESCEND: 

CONST1: kbNormal CONSTDESC:' Normal file access
CONST2: kbHidden CONSTDESC:' Hidden file access
CONST3: kbSystem CONSTDESC:' System file access
CONST4: kbVolume CONSTDESC:' Volume file access
CONST5: kbDirectory CONSTDESC:' Directory file access
CONST6: kbReadOnly CONSTDESC:' ReadOnly file access
CONST7: kbArchive CONSTDESC:' Archive file access

CONST8: kbCrLf CONSTDESC:'
CONST9: kbCr CONSTDESC:'
CONST10: kbLf CONSTDESC:'
CONST11: kbNewLine CONSTDESC:'
CONST12: kbTab CONSTDESC:'
CONST13: kbBack CONSTDESC:'
CONST14: kbNullChar CONSTDESC:'
CONST15: kbNullString CONSTDESC:'

CONST16: kbOKOnly CONSTDESC:'
CONST17: kbOKCancel CONSTDESC:'
CONST18: kbAbortRetryIgnore CONSTDESC:'
CONST19: kbYesNoCancel CONSTDESC:'
CONST20: kbYesNo CONSTDESC:'
CONST21: kbRetryCancel CONSTDESC:'
CONST22: kbCritical CONSTDESC:'
CONST23: kbQuestion CONSTDESC:'
CONST24: kbExclamation CONSTDESC:'
CONST25: kbInformation CONSTDESC:'
CONST26: kbDefaultButton1 CONSTDESC:'
CONST27: kbDefaultButton2 CONSTDESC:'
CONST28: kbDefaultButton3 CONSTDESC:'

CONST29: kbOK CONSTDESC:'
CONST30: kbCancel CONSTDESC:'
CONST31: kbAbort CONSTDESC:'
CONST32: kbRetry CONSTDESC:'
CONST33: kbIgnore CONSTDESC:'
CONST34: kbYes CONSTDESC:'
CONST35: kbNo CONSTDESC:'

CONST36: kbBoolean CONSTDESC:'
CONST37: kbString CONSTDESC:'
CONST38: kbByte CONSTDESC:'
CONST39: kbShort CONSTDESC:'
CONST40: kbInteger CONSTDESC:'
CONST41: kbLong CONSTDESC:'
CONST42: kbSingle CONSTDESC:'
CONST43: kbDouble CONSTDESC:'
CONST44: kbCurrency CONSTDESC:'
CONST45: kbDate CONSTDESC:'
CONST46: kbObject CONSTDESC:'
CONST47: kbEmpty CONSTDESC:'
CONST48: kbNull CONSTDESC:'
CONST49: kbError CONSTDESC:'
CONST50: kbVariant CONSTDESC:'
CONST51: kbInt16 CONSTDESC:'
CONST52: kbInt32 CONSTDESC:'
CONST53: kbInt64 CONSTDESC:'
CONST54: kbUInt16 CONSTDESC:'
CONST55: kbUInt32 CONSTDESC:'
CONST56: kbUInt64 CONSTDESC:'
CONST57: kbArray CONSTDESC:'

CONST58: kbUseSystem CONSTDESC:'
CONST59: kbSunday CONSTDESC:'
CONST60: kbMonday CONSTDESC:'
CONST61: kbTuesday CONSTDESC:'
CONST62: kbWednesday CONSTDESC:'
CONST63: kbThursday CONSTDESC:'
CONST64: kbFriday CONSTDESC:'
CONST65: kbSaturday CONSTDESC:'




CATEGORY: BUILTIN_CONST
SEEALSO: FORM
LOG: 04-02-2004 implemented
TIP:
*/
  return true;
}

/* *
[KBASIC][VB][QBASIC]
NAME: NULL
PRINTNAME: Null
TASK: NULL literal
SYNTAX: NULL
DESC: 
CODE:
CATEGORY: DATATYPE
SEEALSO: 
LOG: 04-02-2004 implemented
TIP:
*/
// parse null
bool parser::fNULL()
{
	//_TBEGIN_

	if (peekToken() == token__NULL){
		myToken->rd_Token( getTokenPos() );
		//parseInfo(p, "NULL", true);
		return true;
	}

  return false;
  //_TEND_
}

/* *
[KBASIC][VB][QBASIC]
NAME: CURRENCY
PRINTNAME: Currency
TASK: CURRENCY
SYNTAX: CURRENCY
DESC: CURRENCY
CODE:
EXAMPLES: currency.kbasic
CATEGORY: TYPE
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
// parse currency literal
bool parser::fCURRENCY(t_currency *c)
{
	//_TBEGIN_

	if (peekToken() == token__LITERAL_CURRENCY){
		myToken->rd_Token( getTokenPos() );
		*c = myToken->rd_Currency( getTokenPos() );
		//parseInfo(p, "CURRENCY", true);
		return true;
	}
  return false;//_TEND_
}

/* *
[KBASIC][VB][QBASIC]
NAME: DATE
PRINTNAME: Date
TASK: DATE
SYNTAX: DATE
DESC: DATE
CODE:
EXAMPLES: date.kbasic
CATEGORY: TYPE
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
 // parse date literal
bool parser::fDATE(t_date *d)
{
	//_TBEGIN_

	if (peekToken() == token__LITERAL_DATE){
		myToken->rd_Token( getTokenPos() );
		*d = myToken->rd_Date( getTokenPos() );
		//parseInfo(p, "DATE", true);
		return true;
	}
  return false;//_TEND_
}

/* *
[KBASIC][VB][QBASIC]
NAME: TIME
PRINTNAME: Time
TASK: TIME
SYNTAX: TIME
DESC: TIME
CODE:
EXAMPLES: time.kbasic
CATEGORY: TYPE
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
 // parse time literal
bool parser::fTIME(t_date *d)
{
	//_TBEGIN_

	if (peekToken() == token__LITERAL_TIME){
		myToken->rd_Token( getTokenPos() );
		*d = myToken->rd_Date( getTokenPos() );
		//parseInfo(p, "TIME", true);
		return true;
	}
  return false;//_TEND_
}

/* *
[KBASIC][VB][QBASIC]
NAME: BYTE
PRINTNAME: Byte
TASK: BYTE
SYNTAX: BYTE
DESC: BYTE
CODE:
EXAMPLES: byte.kbasic
CATEGORY: TYPE
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
 // parse byte literal
bool parser::fBYTE(t_byte *c)
{
	//_TBEGIN_

	if (peekToken() == token__LITERAL_BYTE){
		myToken->rd_Token( getTokenPos() );
		*c = myToken->rd_Byte( getTokenPos() );
		//parseInfo(p, "BYTE", true);
		return true;
	}
  return false;//_TEND_
}

/* *
[KBASIC][VB][QBASIC]
NAME: BOOLEAN
PRINTNAME: Boolean
TASK: BOOLEAN
SYNTAX: BOOLEAN
DESC: BOOLEAN
CODE:
EXAMPLES: boolean.kbasic
CATEGORY: TYPE
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
// parse boolean literal
bool parser::fBOOLEAN(t_boolean *cBoolean)
{
	//_TBEGIN_

	if (peekToken() == token__LITERAL_BOOLEAN){
		myToken->rd_Token( getTokenPos() );
		*cBoolean = myToken->rd_Char( getTokenPos() ) != 0;
		//parseInfo(p, "BOOLEAN", true);
		return true;
	}
  return false;//_TEND_
}

/* *
[KBASIC][VB][QBASIC]
NAME: INTEGER
PRINTNAME: Integer
TASK: INTEGER
SYNTAX: INTEGER
DESC: INTEGER
CODE:
EXAMPLES: integer.kbasic
CATEGORY: TYPE
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
// parse integer literal
bool parser::fINTEGER(t_integer *nInteger)
{
	//_TBEGIN_

	if (peekToken() == token__LITERAL_INTEGER){
		myToken->rd_Token( getTokenPos() );
		*nInteger = myToken->rd_Integer( getTokenPos() );
		//parseInfo(p, "INTEGER", true);
		return true;
	} else { // maybe it's a byte literal
		register unsigned char uc;
		bool bRet = fBYTE(&uc);
		*nInteger = uc;
		return bRet;
	}

  return false;//_TEND_
}

/* *
[KBASIC][VB][QBASIC]
NAME: LONG
PRINTNAME: Long
TASK: LONG
SYNTAX: LONG
DESC: LONG
CODE:
EXAMPLES: long.kbasic
CATEGORY: TYPE
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
// parse long literal
bool parser::fLONG(t_long *lLongInteger)
{
	//_TBEGIN_

	if (peekToken() == token__LITERAL_LONG){
		myToken->rd_Token( getTokenPos() );
		*lLongInteger = myToken->rd_Long( getTokenPos() );
		//parseInfo(p, "LONG", true);
		return true;
	} else if (peekToken() == token__LITERAL_INTEGER){ // maybe it's a integer literal
		register int n;
		bool bRet = fINTEGER(&n);
		*lLongInteger = n;
		return bRet;
	} else if (peekToken() == token__LITERAL_BYTE){ // maybe it's a integer literal
		register t_byte b;
		bool bRet = fBYTE(&b);
		*lLongInteger = b;
		return bRet;
	}

  return false;//_TEND_
}

/* *
[KBASIC][VB][QBASIC]
NAME: DOUBLE
PRINTNAME: Double
TASK: DOUBLE
SYNTAX: DOUBLE
DESC: DOUBLE
CODE:
EXAMPLES: double.kbasic
CATEGORY: TYPE
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
// parse double literal
bool parser::fDOUBLE(t_double *dNumeric)
{
	//_TBEGIN_

	if (peekToken() == token__LITERAL_DOUBLE){
		myToken->rd_Token( getTokenPos() );
		*dNumeric = myToken->rd_Double( getTokenPos() );
		//parseInfo(p, "DOUBLE", true);
		return true;
	}

  return false;//_TEND_
}

/* *
[KBASIC][VB][QBASIC]
NAME: SINGLE
PRINTNAME: Single
TASK: SINGLE
SYNTAX: SINGLE
DESC: SINGLE
CODE:
EXAMPLES: single.kbasic
CATEGORY: TYPE
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
// parse single literal
bool parser::fSINGLE(t_single *fNumeric)
{
	//_TBEGIN_

	if (peekToken() == token__LITERAL_SINGLE){
		myToken->rd_Token( getTokenPos() );
		*fNumeric = myToken->rd_Single( getTokenPos() );
		//parseInfo(p, "SINGLE", true);
		return true;
	}

  return false;//_TEND_
}

/* *
[KBASIC][VB][QBASIC]
NAME: STRING
PRINTNAME: String
TASK: STRING
SYNTAX: STRING
DESC: STRING
CODE:
EXAMPLES: string.kbasic
CATEGORY: TYPE
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
// parse string literal
bool parser::fSTRING(t_cstring *acString, bool bAdd)
{
	//_TBEGIN_

	if (peekToken() == token__LITERAL_STRING){
		myToken->rd_Token( getTokenPos() );
		*acString = myToken->rd_CString( getTokenPos() );
    register int n = 0;
		if (bAdd) n = registerStringLiteral(*acString); // add string to the static string list
 		if (n == 0){ internalError( utility::con(*acString, " string literal not declared") ); _TERROR_ }
		//parseInfo(p, "STRING", true);
		return true;
	}

  return false;//_TEND_
}

/* *
[KBASIC][VB][QBASIC]
NAME: VARIABLE
PRINTNAME: Variable
TASK: VARIABLE
SYNTAX: VARIABLE
DESC: VARIABLE
CODE:
EXAMPLES: variable.kbasic
CATEGORY: VARIABLE
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fID_ALL(const char **acIdentifier)
{
  if (fID(acIdentifier, token__MSC_IDENTIFIER, false, true, false, true)) return true;

  return false;
}

/* *
[KBASIC][VB][QBASIC]
NAME: VARIABLE INTEGER
PRINTNAME: Variable Integer
TASK: VARIABLE INTEGER
SYNTAX: VARIABLE INTEGER
DESC: VARIABLE INTEGER
CODE:
EXAMPLES: variable_integer.kbasic
CATEGORY: VARIABLE, INTEGER
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
/* *
[KBASIC][VB][QBASIC]
NAME: VARIABLE DOUBLE
PRINTNAME: Variable Double
TASK: VARIABLE DOUBLE
SYNTAX: VARIABLE DOUBLE
DESC: VARIABLE DOUBLE
CODE:
EXAMPLES: variable_double.kbasic
CATEGORY: VARIABLE, DOUBLE
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
/* *
[KBASIC][VB][QBASIC]
NAME: VARIABLE SINGLE
PRINTNAME: Variable Single
TASK: VARIABLE SINGLE
SYNTAX: VARIABLE SINGLE
DESC: VARIABLE SINGLE
CODE:
EXAMPLES: variable_single.kbasic
CATEGORY: VARIABLE, SINGLE
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
/* *
[KBASIC][VB][QBASIC]
NAME: VARIABLE LONG
PRINTNAME: Variable Long
TASK: VARIABLE LONG
SYNTAX: VARIABLE LONG
DESC: VARIABLE LONG
CODE:
EXAMPLES: variable_long.kbasic
CATEGORY: VARIABLE, LONG
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
/* *
[KBASIC][VB][QBASIC]
NAME: VARIABLE CURRENCY
PRINTNAME: Variable Currency
TASK: VARIABLE CURRENCY
SYNTAX: VARIABLE CURRENCY
DESC: VARIABLE CURRENCY
CODE:
EXAMPLES: variable_currency.kbasic
CATEGORY: VARIABLE, CURRENCY
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/

bool parser::fID_STRING(const char **acIdentifier) { return fID(acIdentifier, token__MSC_ID_QSTRING, false); }
bool parser::fID_INTEGER(const char **acIdentifier){ return fID(acIdentifier, token__MSC_ID_INTEGER, false); }
bool parser::fID_LONG(const char **acIdentifier)   { return fID(acIdentifier, token__MSC_ID_LONG, false); }
bool parser::fID_SINGLE(const char **acIdentifier) { return fID(acIdentifier, token__MSC_ID_SINGLE, false); }
bool parser::fID_DOUBLE(const char **acIdentifier) { return fID(acIdentifier, token__MSC_ID_DOUBLE, false); }
bool parser::fID_CURRENCY(const char **acIdentifier)   { return fID(acIdentifier, token__MSC_ID_CURRENCY, false); }

bool parser::fID(const char **acIdentifier, bool bParseInfo)				 { return fID(acIdentifier, token__MSC_IDENTIFIER, false, bParseInfo); }

// id can be normal, keyword or builtin
bool parser::fID_KEYWORD_OR_BUILTIN(const char **acIdentifier, bool bLower)
{
  return fID(acIdentifier, token__MSC_IDENTIFIER, true, false, bLower, false);
}

bool parser::fID(const char **acIdentifier, int nID, bool bKeywordBuiltin, bool bParseInfo, bool bLower, bool bAll)
{
	_TBEGIN_

  register int i = peekToken();

  if (bAll){
		myToken->rd_Token( getTokenPos() );
		*acIdentifier = myToken->rd_CString( getTokenPos() );

    if (i == token__MSC_IDENTIFIER) return true;
    if (i == token__MSC_ID_QSTRING) return true;
    if (i == token__MSC_ID_INTEGER) return true;
    if (i == token__MSC_ID_LONG) return true;
    if (i == token__MSC_ID_SINGLE) return true;
    if (i == token__MSC_ID_DOUBLE) return true;
    if (i == token__MSC_ID_CURRENCY) return true;

    _TEND_
  }
  if (i == nID){
		myToken->rd_Token( getTokenPos() );
		*acIdentifier = myToken->rd_CString( getTokenPos() );

		switch (nID){
			case token__MSC_IDENTIFIER:
					//if (bParseInfo) parseInfo(p, "ID", true);
					return true;
			case token__MSC_ID_CURRENCY:
					//if (bParseInfo) parseInfo(p, "ID_CURRENCY", true);
					return true;
//			case token__MSC_ID_FILEHANDLE:
					//if (bParseInfo) parseInfo(p, "ID_FILEHANDLE", true);
			//		return true;
			case token__MSC_ID_INTEGER:
					//if (bParseInfo) parseInfo(p, "ID_INTEGER", true);
					return true;
			case token__MSC_ID_DOUBLE:
					//if (bParseInfo) parseInfo(p, "ID_DOUBLE", true);
					return true;
			case token__MSC_ID_SINGLE:
					//if (bParseInfo) parseInfo(p, "ID_SINGLE", true);
					return true;
			case token__MSC_ID_QSTRING:
					//if (bParseInfo) parseInfo(p, "ID_STRING", true);
					return true;
			case token__MSC_ID_LONG:
					//if (bParseInfo) parseInfo(p, "ID_LONG", true);
					return true;
		}
	} else if (bKeywordBuiltin){
		// What about name collision: keyword <-> varnames ? How to handle this?
	  // Use builtin_ to get the string to use for a varname? Seems to be the only solution.
		

    // damit ' und /* nicht als identifier zugelassen sind
    if (i > token__LITERAL) _TEND_
    switch(i){ 
      case token__REM:
      case token__REM_DOCUMENTATION:
      case token__REM_MULTILINE:
      case token__REM_MULTILINE_STOP:
      case token__REM_SHORT:
        _TEND_
        break;
      default:
        break;
    }

    *acIdentifier = token::builtin_(i);
    if (!strlen(*acIdentifier)){
      *acIdentifier = token::keyword_(i);
      if (!strlen(*acIdentifier)){
        *acIdentifier = token::type_(i);      
        if (!strlen(*acIdentifier)){
          *acIdentifier = token::operator_(i);
          if (!((*acIdentifier[0] >= 65 && *acIdentifier[0] <= 90) || (*acIdentifier[0] >= 97 && *acIdentifier[0] <= 122))){
            *acIdentifier = "";
          }
        }    
      }
      
    }

		if (strcmp(*acIdentifier, "") != 0){
			myToken->rd_Token( getTokenPos() );
 			////if (bParseInfo) parseInfo(p, "ID", true);
 			return true;
		}

	}

  _TEND_
}

// static array size, index is a fix integer; 
// for user defined type and class var declaration needed
// [ ] also supported, modern style
bool parser::fARRAY(const char *acIdentifier, t_array *a)
{
	_TBEGIN_

	register bool bTerm_SYM_BR_OP = false;
	register bool bTerm_SYM_BS_OP = false;

	a->count = 0;
  if (!(bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP))){}
  if (!bTerm_SYM_BR_OP && !(bTerm_SYM_BS_OP = parseTerm(token__SYM_BS_OP))) _TEND_

	bool bTerm_SYM_BR_CL = false;
	bool bTerm_SYM_BS_CL = false;
	bool bTerm_COMMA_ARRAY = false;
	bool bINTEGER[MAX_ARRAY];
	int nComma_Array = 0;

	bool bTO = false;

 	while (true){

 	 	if (nComma_Array >= MAX_ARRAY){ internalError("too many dimensions array indexes"); _TERROR_ }

		t_long n = 0;
 		if (bINTEGER[nComma_Array] = fLONG(&n)){


			if (bTO = parseTerm(token__TO)){

				a->idx[nComma_Array] = n;
				if (!(bINTEGER[nComma_Array] = fLONG(&n))){ syntaxError(token__DIM, "missing long number"); _TERROR_ } 
        a->idxTo[nComma_Array] = n;
        if (a->idxTo[nComma_Array] < a->idx[nComma_Array]){ semanticError(token__DIM, "start index must be smaller than end index"); _TERROR_ }

			} else {
				
				if (n <= nBaseOfArray){ // out of bounds
          if (nBaseOfArray == 0){ semanticError(token__DIM, "dimension must be > 0"); _TERROR_ }
          else if (nBaseOfArray == 1){ semanticError(token__DIM, "dimension must be > 1"); _TERROR_ }
        }
			
				a->idx[nComma_Array] = nBaseOfArray;
				a->idxTo[nComma_Array] = n;
			}

 		  if (bTerm_COMMA_ARRAY = parseTerm(token__SYM_COMMA)){
 				nComma_Array++;
  		} else {
 			  if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){
 					break;
 				}
 			  if (!bTerm_SYM_BR_CL && (bTerm_SYM_BS_CL = parseTerm(token__SYM_BS_CL))){
 					break;
 				}
 			}
 		} else break;
	}

 	if (!bINTEGER[nComma_Array]){ syntaxError(token__DIM, "dimension number missing"); _TERROR_	}
	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__DIM, ") missing"); _TERROR_ }
	if (bTerm_SYM_BS_OP && !bTerm_SYM_BS_CL){ syntaxError(token__DIM, "] missing"); _TERROR_ }
	a->count = ++nComma_Array;

	_DONE_

}


/* *
[KBASIC][VB][QBASIC]
NAME: ARRAY
PRINTNAME: Array
TASK: ARRAY
SYNTAX: ARRAY
DESC: ARRAY
CODE:
EXAMPLES: array.kbasic
CATEGORY: VARIABLE, ARRAY
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
// dynamic array used in expressions and local array definitions
// [ ] also supported, modern style
bool parser::fARRAY(pcode *p, t_array *a, int nType, int nIdentifier, int nElementId, bool bAssignment, bool bEmptyAllowed, bool bTestForError, t_scope scope)
{
	_BEGIN_

	register bool bTerm_SYM_BR_OP = false;
	register bool bTerm_SYM_BS_OP = false;

	a->count = 0;
  if ((bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP))){}
  if (!bTerm_SYM_BR_OP && !(bTerm_SYM_BS_OP = parseTerm(token__SYM_BS_OP))){ _END_ }

	bool bTerm_SYM_BR_CL = false;
	bool bTerm_SYM_BS_CL = false;

 	if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){ _END_ }
 	if (!bTerm_SYM_BR_CL && (bTerm_SYM_BS_CL= parseTerm(token__SYM_BS_CL))){ _END_ }

	bool bTerm_COMMA_ARRAY = false;
	bool bEXPRESSION[MAX_ARRAY];
	int nComma_Array = 0;

 	while (true){

 	 	if (nComma_Array >= MAX_ARRAY){ internalError("too many dimensions array indexes"); _ERROR_ }

		if (bEXPRESSION[nComma_Array] = fLONG_EXPRESSION(p)){

      if (bTerm_COMMA_ARRAY = parseTerm(token__SYM_COMMA)){
 				nComma_Array++;
  		} else {
 			  if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){
 					break;
 				}
 			  if (!bTerm_SYM_BR_CL && (bTerm_SYM_BS_CL= parseTerm(token__SYM_BS_CL))){
 					break;
 				}
 			}
 		} else break;
	}

  if (!bEXPRESSION[nComma_Array] && !bEmptyAllowed){
    if (bTestForError){
        _END_  // might be a function call return variable
    } else {
      _END_
    }
  } else {
  	a->count = ++nComma_Array;
  }

	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__DIM, ") missing"); _ERROR_ }
  if (bTerm_SYM_BS_OP && !bTerm_SYM_BS_CL){ syntaxError(token__DIM, "] missing"); _ERROR_ }

	if (bProducePcode){
    p->wr_ARRAY(pcode__ARRAY, a->count, nType, nIdentifier, scope, nElementId, bAssignment, false); // write pcode
	}

	_DONE_

}

// used for dim arrays
// [ ] also supported, modern style
bool parser::fREGISTER_ARRAY(pcode *p, t_array *a, int nType, int nIdentifier)
{
	_BEGIN_

	register bool bTerm_SYM_BR_OP = false;
	register bool bTerm_SYM_BS_OP = false;

	a->count = 0;
  if ((bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP))){}
  if (!bTerm_SYM_BR_OP && !(bTerm_SYM_BS_OP = parseTerm(token__SYM_BS_OP))) _END_

	bool bTerm_SYM_BR_CL = false;
	bool bTerm_SYM_BS_CL = false;
	bool bTerm_COMMA_ARRAY = false;
	bool bEXPRESSION[MAX_ARRAY];
	bool bEXPRESSION2[MAX_ARRAY];
	int nComma_Array = 0;

	bool bTO = false;

 	while (true){

 	 	if (nComma_Array >= MAX_ARRAY){ internalError("too many dimensions array indexes"); _ERROR_ }

		if (bEXPRESSION[nComma_Array] = fINTEGER_EXPRESSION(p)){
    } else {
      bEXPRESSION[nComma_Array] = true;
      if (bProducePcode){
        p->wr_PUSH_INTEGER(pcode__PUSH_INTEGER, 0);
	      p->wr_PUSH_BOOLEAN(pcode__PUSH_BOOLEAN, false); // write pcode
      }
      
      if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){
 					break;
 				}
 	  	 if (!bTerm_SYM_BR_CL && (bTerm_SYM_BS_CL = parseTerm(token__SYM_BS_CL))){
 					break;
 	  	}
      break;
    }

			if (bTO = parseTerm(token__TO)){
				if (!(bEXPRESSION2[nComma_Array] = fINTEGER_EXPRESSION(p))){ syntaxError(token__DIM, "dimension expression missing"); _ERROR_ }
	      if (bProducePcode){
 		      p->wr_PUSH_BOOLEAN(pcode__PUSH_BOOLEAN, true); // write pcode
	      }
      } else {
	      if (bProducePcode){
 		      p->wr_PUSH_BOOLEAN(pcode__PUSH_BOOLEAN, false); // write pcode
	      }
      }


     if (bTerm_COMMA_ARRAY = parseTerm(token__SYM_COMMA)){
 				nComma_Array++;
  		} else {
 			  if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){
 					break;
 				}
 			  if (!bTerm_SYM_BR_CL && (bTerm_SYM_BS_CL = parseTerm(token__SYM_BS_CL))){
 					break;
 				}
 			}
 		
	}

 	if (nComma_Array == 0 && !bEXPRESSION[nComma_Array] && !bTerm_SYM_BR_CL && !bTerm_SYM_BS_CL){
    //if (isScopeLocal()){
      if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
      else if (bTerm_SYM_BS_OP && (bTerm_SYM_BS_CL = parseTerm(token__SYM_BS_CL))){}
  //  } else {
	//		syntaxError(token__DIM, "dimension expression of non-local variable missing"); _ERROR_
    //}
  }
	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__DIM, ") missing"); _ERROR_ }
	if (bTerm_SYM_BS_OP && !bTerm_SYM_BS_CL){ syntaxError(token__DIM, "] missing"); _ERROR_ }
  a->count = bEXPRESSION[0] ? ++nComma_Array : 0;

	if (bProducePcode){
 		p->wr_REGISTER_ARRAY(pcode__REGISTER_ARRAY, a->count, nType, nIdentifier, getScopeCode(), false/*bTO*/, nBaseOfArray); // write pcode
	}

	_DONE_

}

// used for dim arrays - const expression
// [ ] also supported, modern style
bool parser::fREGISTER_ARRAY_CONST(pcode *p, t_array *a, int nType, int nIdentifier, t_scope scope)
{
	_BEGIN_

	register bool bTerm_SYM_BR_OP = false;
	register bool bTerm_SYM_BS_OP = false;

	a->count = 0;
  if ((bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP))){}
  if (!bTerm_SYM_BR_OP && !(bTerm_SYM_BS_OP = parseTerm(token__SYM_BS_OP))) _END_

	bool bTerm_SYM_BR_CL = false;
	bool bTerm_SYM_BS_CL = false;  

	bool bTerm_COMMA_ARRAY = false;
	bool bEXPRESSION[MAX_ARRAY];
	bool bEXPRESSION2[MAX_ARRAY];
	int nComma_Array = 0;

	bool bTO = false;

 	while (true){

 	 	if (nComma_Array >= MAX_ARRAY){ internalError("too many dimensions array indexes"); _ERROR_ }

		if (bEXPRESSION[nComma_Array] = fCONST_LONG_EXPRESSION(p)){

			if (bTO = parseTerm(token__TO)){
				if (!(bEXPRESSION2[nComma_Array] = fCONST_LONG_EXPRESSION(p))){ syntaxError(token__DIM, "const dimension expression missing"); _ERROR_ }
	      if (bProducePcode){
 		      p->wr_PUSH_BOOLEAN(pcode__PUSH_BOOLEAN, true); // write pcode
	      }
      } else {
	      if (bProducePcode){
 		      p->wr_PUSH_BOOLEAN(pcode__PUSH_BOOLEAN, false); // write pcode
	      }
      }

     if (bTerm_COMMA_ARRAY = parseTerm(token__SYM_COMMA)){
 				nComma_Array++;
  		} else {
 			  if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){
 					break;
        } else if (bTerm_SYM_BS_CL = parseTerm(token__SYM_BS_CL)){
 					break;
 				} else break;
 			}
 		} else break;
	}

 	if (!bEXPRESSION[nComma_Array]){
			syntaxError(token__DIM, "dimension expression missing"); _ERROR_
 	}
	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__DIM, ") missing"); _ERROR_ }
	if (bTerm_SYM_BS_OP && !bTerm_SYM_BS_CL){ syntaxError(token__DIM, "] missing"); _ERROR_ }
	a->count = ++nComma_Array;

	if (bProducePcode){
 		p->wr_REGISTER_ARRAY(pcode__REGISTER_ARRAY, a->count, nType, nIdentifier, scope, true/*bTO*/, nBaseOfArray); // write pcode
	}

	_DONE_

}

// used for dim arrays - const expression
// [ ] also supported, modern style
bool parser::fREGISTER_ARRAY_CONST(pcode *p, const char *acIdentifier, t_array *a, bool bTestDimension)
{
	_BEGIN_

	register bool bTerm_SYM_BR_OP = false;
	register bool bTerm_SYM_BS_OP = false;

	a->count = 0;
  if ((bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP))){}
  if (!bTerm_SYM_BR_OP && !(bTerm_SYM_BS_OP = parseTerm(token__SYM_BS_OP))) _END_

	bool bTerm_SYM_BR_CL = false;
	bool bTerm_SYM_BS_CL = false;

	bool bTerm_COMMA_ARRAY = false;
	bool bEXPRESSION[MAX_ARRAY];
	bool bEXPRESSION2[MAX_ARRAY];
	int nComma_Array = 0;

	bool bTO = false;

  if (bTestDimension == false) goto gg;

 	while (true){

 	 	if (nComma_Array >= MAX_ARRAY){ internalError("too many dimensions array indexes"); _ERROR_ }

		if (bEXPRESSION[nComma_Array] = fCONST_LONG_EXPRESSION(p)){

			if (bTO = parseTerm(token__TO)){
				if (!(bEXPRESSION2[nComma_Array] = fCONST_LONG_EXPRESSION(p))){ syntaxError(token__DIM, "const dimension expression missing"); _ERROR_ }
			}

      if (bProducePcode) p->wr_PUSH_BOOLEAN(pcode__PUSH_BOOLEAN, bTO);

     if (bTerm_COMMA_ARRAY = parseTerm(token__SYM_COMMA)){
 				nComma_Array++;
  		} else {
gg:
 			  if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){
 					break;
        } else if (bTerm_SYM_BS_CL = parseTerm(token__SYM_BS_CL)){
 					break;
 				} else break;
 			}
 		} else break;
	}

 	if (bTestDimension && !bEXPRESSION[nComma_Array]){
			syntaxError(token__DIM, "dimension expression missing"); _ERROR_
 	}
	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__DIM, ") missing"); _ERROR_ }
	if (bTerm_SYM_BS_OP && !bTerm_SYM_BS_CL){ syntaxError(token__DIM, "] missing"); _ERROR_ }
	a->count = ++nComma_Array;

	_DONE_

}


bool parser::fBOOLEAN_VARIABLE(pcode *p, int *nVar, t_scope *scope, int *nIdType, int *nType, t_arrayVariable *a3){ return fVARIABLE(p, nVar, scope, nIdType, nType, a3) && compatibleType(pcode__BOOLEAN, *nType); }

bool parser::fSTRING_VARIABLE(pcode *p, int *nVar, t_scope *scope, int *nIdType, int *nType, t_arrayVariable *a3){ return fVARIABLE(p, nVar, scope, nIdType, nType, a3) && (compatibleType(pcode__QSTRING, *nType) || compatibleType(pcode__CSTRING, *nType)); }

bool parser::fBYTE_VARIABLE(pcode *p, int *nVar, t_scope *scope, int *nIdType, int *nType, t_arrayVariable *a3){ return fVARIABLE(p, nVar, scope, nIdType, nType, a3) && compatibleType(pcode__BYTE, *nType); }

bool parser::fSHORT_VARIABLE(pcode *p, int *nVar, t_scope *scope, int *nIdType, int *nType, t_arrayVariable *a3){ return fVARIABLE(p, nVar, scope, nIdType, nType, a3) && compatibleType(pcode__BYTE, *nType); }

bool parser::fINTEGER_VARIABLE(pcode *p, int *nVar, t_scope *scope, int *nIdType, int *nType, t_arrayVariable *a3){ return fVARIABLE(p, nVar, scope, nIdType, nType, a3) && compatibleType(pcode__INTEGER, *nType); }
bool parser::fLONG_VARIABLE(pcode *p, int *nVar, t_scope *scope, int *nIdType, int *nType, t_arrayVariable *a3){ return fVARIABLE(p, nVar, scope, nIdType, nType, a3) && compatibleType(pcode__LONG, *nType); }

bool parser::fSINGLE_VARIABLE(pcode *p, int *nVar, t_scope *scope, int *nIdType, int *nType, t_arrayVariable *a3){ return fVARIABLE(p, nVar, scope, nIdType, nType, a3) && compatibleType(pcode__SINGLE, *nType); }
bool parser::fDOUBLE_VARIABLE(pcode *p, int *nVar, t_scope *scope, int *nIdType, int *nType, t_arrayVariable *a3){ return fVARIABLE(p, nVar, scope, nIdType, nType, a3) && compatibleType(pcode__DOUBLE, *nType); }

bool parser::fVARIANT_VARIABLE(pcode *p, int *nVar, t_scope *scope, int *nIdType, int *nType, t_arrayVariable *a3){ return fVARIABLE(p, nVar, scope, nIdType, nType, a3) && compatibleType(pcode__VARIANT, *nType); }
bool parser::fCURRENCY_VARIABLE(pcode *p, int *nVar, t_scope *scope, int *nIdType, int *nType, t_arrayVariable *a3){ return fVARIABLE(p, nVar, scope, nIdType, nType, a3) && compatibleType(pcode__CURRENCY, *nType); }
bool parser::fDATE_VARIABLE(pcode *p, int *nVar, t_scope *scope, int *nIdType, int *nType, t_arrayVariable *a3){ return fVARIABLE(p, nVar, scope, nIdType, nType, a3) && compatibleType(pcode__DATE, *nType); }



bool parser::fTYPE(const char **acType, int *nSize)
{
  *nSize = 0;
  return fTYPE(0, acType, false, nSize);
}

bool parser::fTYPE(pcode *p, const char **acType, bool bNew)
{
  register int nSize = 0;

  return fTYPE(p, acType, bNew, &nSize);
}

/* *
[EXPLANATION]
NAME: TYPE
DESC:
SEEALSO:
*/
bool parser::fTYPE(pcode *p, const char **acType, bool bNew, int *nSize)
{

	_TBEGIN_

/**
[KBASIC][VB][QBASIC]
NAME: TYPEDOUBLE
PRINTNAME: Double
TASK: DATATYPE storing floating point numbers
SYNTAX: DOUBLE
DESC: 
CODE:
DIM m AS DOUBLE
m = 23.234
EXAMPLES: double.kbasic
CATEGORY: TYPE, DOUBLE
SEEALSO: SINGLE, INTEGER, LONG
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/

  int nToken = peekToken();
	if (bNew == false && nToken == token__TYP_DOUBLE){
		myToken->rd_Token( getTokenPos() );
		*acType = pcode::pcode_(pcode__DOUBLE);
		//parseInfo(p, "TYPE", true);
		return true;
/**
[KBASIC][VB][QBASIC]
NAME: TYPESINGLE
PRINTNAME: Single
TASK: DATATYPE storing floating point numbers
SYNTAX: SINGLE
DESC: 
CODE:
DIM m AS SINGLE
m = 23.234
EXAMPLES: single.kbasic
CATEGORY: TYPE, SINGLE
SEEALSO: DOUBLE, INTEGER, LONG
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
	} else if (bNew == false && nToken == token__TYP_SINGLE){
		myToken->rd_Token( getTokenPos() );
		*acType = pcode::pcode_(pcode__SINGLE);
		//parseInfo(p, "TYPE", true);
		return true;
/**
[KBASIC][VB][QBASIC]
NAME: TYPEBOOLEAN
PRINTNAME: Boolean
TASK: DATATYPE storing boolean values
SYNTAX: BOOLEAN
DESC: 
CODE:
DIM m AS BOOLEAN
m = TRUE
EXAMPLES: boolean.kbasic
CATEGORY: TYPE, BOOLEAN
SEEALSO: DOUBLE, INTEGER, LONG
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
	} else if (bNew == false && nToken == token__TYP_BOOLEAN){
		myToken->rd_Token( getTokenPos() );
		*acType = pcode::pcode_(pcode__BOOLEAN);
		//parseInfo(p, "TYPE", true);
		return true;
/**
[KBASIC][VB][QBASIC]
NAME: TYPEOBJECT
PRINTNAME: Object
TASK: DATATYPE storing object referencies
SYNTAX: OBJECT
DESC: 
CODE:
DIM m AS OBJECT
m = objectVar
EXAMPLES: object.kbasic
CATEGORY: TYPE, OBJECT
SEEALSO: DOUBLE, INTEGER, LONG
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
	} else if (nToken == token__TYP_OBJECT){
		myToken->rd_Token( getTokenPos() );
		*acType = pcode::pcode_(pcode__OBJECT);
		//parseInfo(p, "TYPE", true);
		return true;

	} else if (nToken == token__TYP_CASTEXCEPTION){
		myToken->rd_Token( getTokenPos() );
		*acType = pcode::pcode_(pcode__CASTEXCEPTION);
		//parseInfo(p, "TYPE", true);
		return true;

	} else if (nToken == token__TYP_QTEXCEPTION){
		myToken->rd_Token( getTokenPos() );
		*acType = pcode::pcode_(pcode__QTEXCEPTION);
		//parseInfo(p, "TYPE", true);
		return true;

	} else if (nToken == token__TYP_EXCEPTION){
		myToken->rd_Token( getTokenPos() );
		*acType = pcode::pcode_(pcode__EXCEPTION);
		//parseInfo(p, "TYPE", true);
		return true;

/* *
[KBASIC][VB][QBASIC]
NAME: TYPECURRENCY
PRINTNAME: Currency
TASK: DATATYPE storing currency values
SYNTAX: CURRENCY
DESC: 
CODE:
DIM m AS CURRENCY
m = 12.234
EXAMPLES: currency.kbasic
CATEGORY: TYPE, CURRENCY
SEEALSO: DOUBLE, INTEGER, LONG
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
	} else if (bNew == false && nToken == token__TYP_CURRENCY){
		myToken->rd_Token( getTokenPos() );
		*acType = pcode::pcode_(pcode__CURRENCY);
		//parseInfo(p, "TYPE", true);
		return true;
/* *
[KBASIC][VB][QBASIC]
NAME: TYPEDATE
PRINTNAME: Date
TASK: DATATYPE storing date values
SYNTAX: DATE
DESC: 
CODE:
DIM m AS DATE
EXAMPLES: date.kbasic
CATEGORY: TYPE, DATE
SEEALSO: DOUBLE, INTEGER, LONG
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
	} else if (bNew == false && nToken == token__DATE){ // token__TYP_DATE
		myToken->rd_Token( getTokenPos() );
		*acType = pcode::pcode_(pcode__DATE);
		//parseInfo(p, "TYPE", true);
		return true;


/**
[KBASIC][VB][QBASIC]
NAME: TYPEBYTE
PRINTNAME: Byte
TASK: DATATYPE storing byte values
SYNTAX: BYTE
DESC: 
CODE:
DIM m AS BYTE
m = 9889
EXAMPLES: BYTE.kbasic
CATEGORY: TYPE, BYTE
SEEALSO: DOUBLE, INTEGER, LONG
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
	} else if (bNew == false && nToken == token__TYP_BYTE){
		myToken->rd_Token( getTokenPos() );
		*acType = pcode::pcode_(pcode__BYTE);
		//parseInfo(p, "TYPE", true);
		return true;
/**
[KBASIC][VB][QBASIC]
NAME: TYPESHORT
PRINTNAME: Short
TASK: DATATYPE storing integer values
SYNTAX: SHORT
DESC: 
CODE:
DIM m AS SHORT
m = 9889
EXAMPLES: SHORT.kbasic
CATEGORY: TYPE, SHORT
SEEALSO: DOUBLE, INTEGER, LONG
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
	} else if (bNew == false && nToken == token__TYP_SHORT){
		myToken->rd_Token( getTokenPos() );
		*acType = pcode::pcode_(pcode__SHORT);
		//parseInfo(p, "TYPE", true);
		return true;
/**
[KBASIC][VB][QBASIC]
NAME: TYPEVARIANT
PRINTNAME: Variant
TASK: DATATYPE storing different kind of values
SYNTAX: VARIANT
DESC: 
CODE:
DIM m AS VARIANT
m = 9889
EXAMPLES: variant.kbasic
CATEGORY: TYPE, VARIANT
SEEALSO: DOUBLE, INTEGER, LONG
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
	} else if (bNew == false && nToken == token__TYP_VARIANT){
		myToken->rd_Token( getTokenPos() );
		*acType = pcode::pcode_(pcode__VARIANT);
		//parseInfo(p, "TYPE", true);
		return true;
/**
[KBASIC][VB][QBASIC]
NAME: TYPEINTEGER
PRINTNAME: Integer
TASK: DATATYPE storing integer values
SYNTAX: INTEGER
DESC: 
CODE:
DIM m AS INTEGER
m = 9889
EXAMPLES: INTEGER.kbasic
CATEGORY: TYPE, INTEGER
SEEALSO: DOUBLE, INTEGER, LONG
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
	} else if (bNew == false && nToken == token__TYP_INTEGER){
		myToken->rd_Token( getTokenPos() );
		*acType = pcode::pcode_(pcode__INTEGER);
		//parseInfo(p, "TYPE", true);
		return true;
/**
[KBASIC][VB][QBASIC]
NAME: TYPELONG
PRINTNAME: Long
TASK: DATATYPE storing integer values
SYNTAX: LONG
DESC: 
CODE:
DIM m AS LONG
m = 9889
EXAMPLES: LONG.kbasic
CATEGORY: TYPE, LONG
SEEALSO: DOUBLE, LONG
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
	} else if (bNew == false && nToken == token__TYP_LONG){
		myToken->rd_Token( getTokenPos() );
		*acType = pcode::pcode_(pcode__LONG);
    { semanticError(token__KEYWORD, " Sorry! LONG (64bit) is not supported yet due to 64bit calculation limits of the C library.\nUse INTEGER (32bit) instead." ); _ERROR_ }
		//parseInfo(p, "TYPE", true);
		return true;

	} else if (bNew == false && nToken == token__TYP_ANY){
		myToken->rd_Token( getTokenPos() );
		*acType = pcode::pcode_(pcode__ANY);
		//parseInfo(p, "TYPE", true);
		return true;
/*
// special case collection
	} else if (peekToken() == token__TYP_COLLECTION){
		myToken->rd_Token( getTokenPos() );
		*acType = pcode::pcode_(pcode__COLLECTION);
		//parseInfo(p, "TYPE", true);
		return true;*/
/**
[KBASIC][VB][QBASIC]
NAME: TYPESTRING
PRINTNAME: String
TASK: DATATYPE storing strings and texts
SYNTAX: STRING
DESC: 
CODE:
DIM m AS STRING
m = "Hello !!"
EXAMPLES: STRING.kbasic
CATEGORY: TYPE, STRING
SEEALSO: DOUBLE, STRING, LONG
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
    
	} else if (bNew == false && (nToken == token__TYP_QSTRING || nToken == token__STRING)){
		myToken->rd_Token( getTokenPos() );

    if (parseTerm(token__OP_MUL)){
	 		if (fINTEGER(nSize)){ // byte, long, integer
				*acType = pcode::pcode_(pcode__LQSTRING); //  fixed length of String, e.g. s * 70 AS STRING
      } else {
			return syntaxError(token__STRING, "length (INTEGER) missing"); _ERROR_ }
		} else {
			*acType = pcode::pcode_(pcode__QSTRING);
		}

		//parseInfo(p, "TYPE", true);
		return true;
	} else if (bNew == false && (nToken == token__TYP_CSTRING)){
		myToken->rd_Token( getTokenPos() );

    if (/*bTerm_OP_MUL = */parseTerm(token__OP_MUL)){
	 		if (/*bINTEGER = */fINTEGER(nSize)){ // byte, long, integer
				*acType = pcode::pcode_(pcode__LCSTRING); //  fixed length of String, e.g. s * 70 AS STRING
      } else {
			/*if (!bINTEGER){ */return syntaxError(token__STRING, "length (INTEGER) missing"); _ERROR_ }
		} else {
			*acType = pcode::pcode_(pcode__CSTRING);
		}
		//parseInfo(p, "TYPE", true);
		return true;
	} else { 

		// binding Qt, KDE
		if (binding_fTYPE_Class(p, acType, bNew)){ /*parseInfo(p, "CLASS", true); */return true;}

    // user defined class
		if (fTYPE_Class(p, acType, bNew)){ /*parseInfo(p, "CLASS", true); */return true;}

    // user defined type
		if (fTYPE_Type(p, acType, bNew)){ /*parseInfo(p, "USER DEFINED TYPE", true); */return true;}

		// user defined enum
		if (fTYPE_Enum(p, acType, bNew)){ /*parseInfo(p, "ENUM", true); */return true;}

		// user defined structure
//		if (fTYPE_Structure(p, acType, bNew)){ /*parseInfo(p, "STRUCTURE", true); */return true;}

    if (fID_KEYWORD_OR_BUILTIN(acType, false)){ // find keywords and builtins as well
      if (utility::my_stricmp(*acType, "Timer") == 0/* || strcmp(*acType, "TIMER") == 0*/) return true;
      //if (utility::my_stricmp(*acType, "Tab") == 0/* || strcmp(*acType, "TAB") == 0*/) return true;
      if (utility::my_stricmp(*acType, "Color") == 0/* || strcmp(*acType, "COLOR") == 0*/) return true;
    //  if (utility::my_stricmp(*acType, "Array") == 0/* || strcmp(*acType, "COLOR") == 0*/) return binding_fCLASS_METHOD_CALL(p, &nReturnExpressionType, false, i, acIdentifier, true);;
      //if (utility::my_stricmp(*acType, "Collection") == 0/* || strcmp(*acType, "COLLECTION") == 0*/) return true;
    }


  }

	_TEND_
}

bool parser::fTYPE_Type(pcode *p, const char **acType, bool bNew)
{

	// user defined type
	if (bNew == false){ // user defined type is no class and cannot create an object

  	_TBEGIN_

 		//bool bIDENTIFIER = false;
		const char *acIdentifier = "";

		if (/*bIDENTIFIER = */fID_KEYWORD_OR_BUILTIN(&acIdentifier)){

  		const char *acScope = acIdentifier;

	    bool bTerm_SYM_DOT = false;

		  if (bTerm_SYM_DOT = parseTerm(token__SYM_DOT)){

		    if (!fID_KEYWORD_OR_BUILTIN(&acIdentifier)){ syntaxError(token__AS, "missing TYPE name after scope name"); _TERROR_ };

      } else {
        acScope = getScope();
      }

       // type of current scope
			if (myMemory_type->first()){
				do {

					if (utility::my_stricmp(acScope, myMemory_type->getModule()) == 0)
					if (utility::my_stricmp(acIdentifier, myMemory_type->getName()) == 0){

            // test for scope validity
            if (bTerm_SYM_DOT){
              if (myMemory_type->getScope() == token__PRIVATE){ semanticError(token__AS, "TYPE name cannot be used, because it is declared as PRIVATE"); _TERROR_ };              
            }

						*acType = acIdentifier;

            if (myClass->exist(acScope)){
              if (my_cache && p) addDependency(p->sCurrentFile.ascii(), myClass->getFile(myClass->getId(acScope)));
            } else {
              if (my_cache && p) addDependency(p->sCurrentFile.ascii(), myModule->getFile(myModule->getId(acScope)));
            }
						return true;
					}

				} while (myMemory_type->next());
     }
#ifdef KBDEBUG
      if (stopAtLine(149)){
        int i = 9;
        i++;
      }
#endif
      if (bTerm_SYM_DOT == false){

        // default
			  if (myMemory_type->first()){
				  do {

					  if (utility::my_stricmp(acIdentifier, myMemory_type->getName()) == 0){

             // test for scope validity
              if (myMemory_type->getScope() == token__PRIVATE){
                if (utility::my_stricmp(myMemory_type->getModule(), this->getScope()) != 0){ semanticError(token__AS, "TYPE name cannot be used, because it is declared as PRIVATE"); _TERROR_ };              
              }

						  *acType = acIdentifier;
						  return true;
					  }

				  } while (myMemory_type->next());
			  }
      }

		}
    _TEND_
	}

  return false;
	
}

bool parser::fTYPE_Enum(pcode *p, const char **acType, bool bNew)
{

	// user defined type
	if (bNew == false){ // user defined type is no class and can not create an object

   	_TBEGIN_

		const char *acIdentifier = "";

		if (fID_KEYWORD_OR_BUILTIN(&acIdentifier)){

  		const char *acScope = acIdentifier;

	    bool bTerm_SYM_DOT = false;

		  if (bTerm_SYM_DOT = parseTerm(token__SYM_DOT)){

		    if (!fID_KEYWORD_OR_BUILTIN(&acIdentifier)){ syntaxError(token__AS, "missing TYPE name after scope name"); _TERROR_ };

      } else {
        acScope = getScope();
      }

       // type of current scope
			if (myMemory_enum->first()){
				do {

					if (utility::my_stricmp(acScope, myMemory_enum->getModule()) == 0)
					if (utility::my_stricmp(acIdentifier, myMemory_enum->getName()) == 0){

            // test for scope validity
            if (bTerm_SYM_DOT){
              if (myMemory_enum->getScope() == token__PRIVATE){ semanticError(token__AS, "TYPE name cannot be used, because it is declared as PRIVATE"); _TERROR_ };              
            }

						*acType = acIdentifier;

            
            if (myClass->exist(acScope)){
              if (my_cache) addDependency(p->sCurrentFile.ascii(), myClass->getFile(myClass->getId(acScope)));
            } else {
              if (my_cache) addDependency(p->sCurrentFile.ascii(), myModule->getFile(myModule->getId(acScope)));
            }
						return true;
					}

				} while (myMemory_enum->next());
     }
       
      if (bTerm_SYM_DOT == false){

        // default
			  if (myMemory_enum->first()){
				  do {

					  if (utility::my_stricmp(acIdentifier, myMemory_enum->getName()) == 0){

             // test for scope validity
             if (myMemory_enum->getScope() == token__PRIVATE){ semanticError(token__AS, "TYPE name cannot be used, because it is declared as PRIVATE"); _TERROR_ };              

						  *acType = acIdentifier;
						  return true;
					  }

				  } while (myMemory_enum->next());
			  }
      }

		}

    _TEND_

	}

  return false;

}

// start production
bool parser::fKBASIC()
{
	register bool bSyntaxMatched = false;
	register bool bSyntaxMatched2 = false;
re:
	bParseToken = true;

  setScopeDefaultGlobal();
// setNamespace(acNamespace); // default namespacename

  bool bErrorRecovering = false;

	bSyntaxMatched = true;

	do {

		     if (!proceedParse()) bSyntaxMatched = false;

		else if (fEOL(false)) continue;
	  else if (fREM()) continue;    

    switch(peekToken()){
      case token__KB_VERSION:
        if (fVERSION()) continue;
        break;
      case token__KB_FILENAME:
        if (fFILENAME()) continue;
        break;
      case token__SYM_COLON:
        if (fCOL(false)) continue;
        break;
      case token__OPTION:
        if (fOPTION(myPcode)) continue; // myPcode
        break;
      case token__PUBLIC:
      case token__PRIVATE:
      case token__DECLARE:
        if (fDECLARE()) continue; // skip statement, because it has already been registered
        break;
      case token__DEFINT:
        if (fDEFINT()) continue;
        break;
      case token__DEFLNG:
        if (fDEFLNG()) continue;
        break;
      case token__DEFSNG:
        if (fDEFSNG()) continue;
        break;
      case token__DEFDBL:
        if (fDEFDBL()) continue;
        break;
      case token__DEFSTR:
        if (fDEFSTR()) continue;
        break;
      case token__DEFCUR:
        if (fDEFCUR()) continue;
        break;
      case token__DEFVAR:
        if (fDEFVAR()) continue;
        break;
      case token__DEFBOOL:
        if (fDEFBOOL()) continue;
        break;
      case token__DEFBYTE:
        if (fDEFBYTE()) continue;
        break;
      case token__DEFDATE:
        if (fDEFDATE()) continue;
        break;
      case token__DEFOBJ:
        if (fDEFOBJ()) continue;
        break;
    }

    bSyntaxMatched = false;

	} while (proceedParse() && bSyntaxMatched);


	bSyntaxMatched = true;

	do {

    if (bNoError){ nProceedPercent = 50 + ((myToken->getPos() * 100 / myToken->getSize2()) / 2); CONSOLE printKBPROGRESS(nProceedPercent); }

    int kk2 = myPcode->getPos();

		if (!proceedParse()) bSyntaxMatched = false;

    switch(peekToken()){
      case token__DECLARE:
      case token__PUBLIC:
      //case token__PROTECTED:
      case token__PRIVATE:

      case token__STATIC:
      //case token__ABSTRACT:
      case token__SUB:
      case token__FUNCTION:
      //case token__CONSTRUCTOR:
      //case token__DESTRUCTOR:
      //case token__SIGNAL:
      //case token__SLOT:
        if (fSUB_BODY()) continue; // sub body
      case token__TYPE:
        if (fTYPE_BODY()) continue; // already parsed
      case token__ENUM:
        if (fENUM_BODY()) continue; // already parsed
      case token__CLASS:           
        if (fCLASS_BODY()) continue; // class body        

        break;       
      case token__MODULE:
        if (fMODULE_BODY()) continue;
        break;                  
      case token__KB_EOF2:
        if (fEOF2()) goto re;   // // Attention! must before fSTATEMENTSEQUENCE
        break;
      case token__DATA:
        if (fDATA(myPcodeData)) continue; // myPcode
        break;
      case token__RESTORE:
        if (fRESTORE(myPcode)) continue; // myPcode
        break;
      case token__OPTION:
        if (fOPTION(myPcode)) continue; // myPcode //{ syntaxError(token__OPTION, "OPTION must be before all other statements"); _ERROR_ }
        break;
    }

    if (fSTATEMENT(myPcode, true, true, true, &bErrorRecovering)) continue; // Attention! must be the last

    else bSyntaxMatched = false;

		if (proceedParse() && bSyntaxMatched == false){

      const char *acIdentifier = "";
      if (fID_KEYWORD_OR_BUILTIN(&acIdentifier) && utility::my_stricmp(acIdentifier, "Main") == 0){

        // critical hint
        syntaxError(token__KEYWORD, ""              
        "Something with your project property 'Project's Main Form Name' is wrong.<br>"
        "You do not have entered a proper form name or the main function:<br>"
        "Try to create a function named 'Function Main()' in which you call "
        "the initial code of your program. Check the project property window for details.<br><br> If no project is opened, you cannot run a form."
        );

    } else {
 			syntaxError(token__KEYWORD, "no syntax matching");
    }

		}

    kk2 = myPcode->getPos();
    kk2 = kk2;

	} while (proceedParse() && bSyntaxMatched);

  if (myException.size() > 0){ // are all exceptions catched?

     t_exception *t;
     if (myException.first((int *) &t)){

        setCurrentLine(t->nLine);
        setCurrentRow(t->nRow);

        { semanticError(token__SUB, utility::con(t->acName, " must be catched inside TRY..CATCH..FINALLY")); return false; }

     }
  }

  myPcode = myPcodeAll;
  return bNoError;
}

/* *
[EXPLANATION]
NAME: fSTATEMENTSEQUENCE
DESC:
SEEALSO:
*/
bool parser::fSTATEMENTSEQUENCE(pcode *p, bool bDebugStatements, bool bNoStatementIsError, bool bTestEndIf)
{
  static int n = 0;

	_BLOCK_BEGIN_

  register bool bErrorRecovering = false;

	if (n != getTokenPos() && proceedParse() && fSTATEMENT(p, true, bDebugStatements, bNoStatementIsError, &bErrorRecovering)){
    
		do {      
    } while (proceedParse() && fSTATEMENT(p, true, bDebugStatements, bNoStatementIsError, &bErrorRecovering) && bErrorRecovering == false);

    n = getTokenPos();

  	_BLOCK_DONE_;
  }

  _BLOCK_END_
}

bool parser::fSTATEMENTSEQUENCEONELINE(pcode *p)
{
	_BEGIN_

	register bool bRet = false;

	if (proceedParse() && (bRet = fSTATEMENT(p, false))){

		do {} while (proceedParse() && peekToken() != token__MSC_EOL && peekToken() != token__KB_EOF /*&& !fREM(false)*/ && peekToken() != token__ELSE && peekToken() != token__ELSEIF  && peekToken() != token__ENDIF  && !peekTokens(token__END, token__IF) && proceedParse() && (bRet = fSTATEMENT(p, false)));
    
  	return bRet;
  }
  
	_END_
}

/* *
[EXPLANATION]
NAME: STATEMENT
DESC:
SEEALSO:
*/
bool parser::fSTATEMENT(pcode *p, bool bEOL, bool bDebugStatement, bool bNoStatementIsError, bool *bErrorRecovering)
{
	_BEGIN_

	if (!proceedParse()){ _END_ }

	const char *acIdentifier = "";
	int nExpressionType = 0;
	bool bReturn = false;
	bool bUnknownFunction = false;  

  if (bErrorRecovering != 0){    
    *bErrorRecovering = false;
  }

 

#ifdef KBDEBUG
  if (stopAtLine(66)){
    int i = 9;
    i++;
  }
#endif

			 if (bEOL && fEOL(false)) _DONE_ 
	else if (!bEOL && fCOL(false)) _DONE_ 


  else if (fREM()) _DONE_

    int n = p->getPos();
    const char *acFile = this->getCurrentFile();
    int nLine = this->getCurrentLine();// - 1;

    if (bProducePcode){    
			p->wr_STATEMENT(pcode__STATEMENT, n, 0, (char *) acFile, nLine); // wird auch für normal modus gebraucht, wegen on error goto
    }
    // to optimize
    switch(peekToken()){
      case token__PUBLIC:
      case token__PROTECTED:
      case token__PRIVATE:
        if (fCONST(p)) goto done;
        // FALLTRHOUGH
      case token__STATIC:
        if (fDIM(p)) goto done;
        break;
      case token__IF:
        if (fIF(p)) goto done;
        break;
      case token__DIM:
        if (fDIM(p)) goto done;
        break;
      case token__CONST:
        if (fCONST(p)) goto done;
        break;
      case token__NEW:
        if (fNEW(p)) goto done;
        break;
      case token__DO:
        if (fDOWHILELOOP(p)) goto done; // attention, the order how do loop while and do while loop occur must not be changed!
        if (fDOUNTILLOOP(p)) goto done; // attention, the order how do loop while and do while loop occur must not be changed!
        if (fWHILEWEND(p)) goto done; // attention, the order how do loop while and do while loop occur must not be changed!
        //if (fWHILEENDWHILE(p)) goto done; // attention, the order how do loop while and do while loop occur must not be changed!  
        if (fDOLOOPWHILE(p)) goto done; // attention, the order how do loop while and do while loop occur must not be changed!
        //if (fDOLOOPUNTIL(p)) goto done; // attention, the order how do loop while and do while loop occur must not be changed!
        break;
      case token__MID:
      case token__MID_:
        if (fMID2(p)) goto done;
        break;
      case token__SELECT:
        if (fSELECTCASE(p)) goto done; // must be called before fFOR
        break;
      case token__FOR:
        if (fFOREACH(p)) goto done; // must be called before fFOR
        if (fFOR(p)) goto done;
        break;
      case token__WHILE:
        if (fWHILEWEND(p)) goto done;
        if (fWHILEENDWHILE(p)) goto done;
        break;
      case token__TRY:
        if (fTRY(p)) goto done;
        break;
      case token__WITH:
        if (fWITH(p)) goto done; 
        break;
      case token__REDIM:
        if (fREDIM(p)) goto done;
        break;
      case token__THROW:
        if (fTHROW(p)) goto done;
        break;
      case token__ME:
        if (fME_METHOD_CALL(p, &nExpressionType, bReturn)) goto done;
        break;
      case token__PARENT:
        if (fPARENT_METHOD_CALL(p, &nExpressionType, bReturn)) goto done;
        break;      
      case token__RETURN:
        if (fRETURN(p)) goto done;
        break;
      case token__EXIT:
        if (fEXIT(p)) goto done;
        break;
      case token__ITERATE:
        if (fITERATE(p)) goto done;
        break;
      case token__STOP:
        if (fSTOP(p)) goto done;
        break;
      case token__END:
        if (fEND(p)) goto done;
        break;
      case token___END:
        if (f_END(p)) goto done;
        break;
      case token__GOTO:
        if (fGOTO(p)) goto done;
        break;
      case token__GOSUB:
        if (fGOSUB(p)) goto done;
        break;
      case token__RESUME:
        if (fRESUME(p)) goto done;
        break;
      case token__ON:
        if (fONTIMER(p)) goto done; // must be before fONERROR
        if (fONERROR(p)) goto done;
        if (fONGOSUB(p)) goto done;
        if (fONGOTO(p)) goto done;
        break;
        /*
      case token__CONNECT:
        if (binding_fCONNECT(myPcode)) goto done;
        break;
      case token__DISCONNECT:
        if (binding_fDISCONNECT(myPcode)) goto done;
        break;*/
      case token__SYSTEM:
        if (fSYSTEM(p)) goto done;
        break;
      case token__READ:
        if (fREAD(p)) goto done;
        break;
      case token__ERASE:
        if (fERASE(p)) goto done;
        break;
      case token__DATA:
        if (fDATA(myPcode)) goto done;
        break;
      case token__RESTORE:
        if (fRESTORE(myPcode)) goto done;
        break;
      case token__KB_FILENAME:
        if (fFILENAME()) goto done;
        break;
      case token__MSC_LABEL:
        if (fLABEL(p)) goto done;
        break;
      case token__MSC_LINE:
        if (fLINE(p)) goto done;
        break;
      case token___STATIC:
        if (f_STATIC(p)) goto done;
        break;
      case token___DYNAMIC:
        if (f_DYNAMIC(p)) goto done;
        break;
    }


/*
       if (fFILENAME()) goto done;
  else if (fLABEL(p)) goto done;
  else if (fLINE(p)) goto done;
  else if (fMID2(p)) goto done;

  else if (f_STATIC(p)) goto done;
  else if (f_DYNAMIC(p)) goto done;
*/



	// builtin sub/functions with higher priority
       if (fBUILTIN_SUB(p)) goto done;
  else if (fBUILTIN_FUNCTION(p, &nExpressionType, bReturn)) goto done;

  else if (fDIM(p)) goto done;
  else if (fCONST(p)) goto done;

  //else if (fME_METHOD_CALL(p, &nExpressionType, bReturn)) goto done;
  //else if (fPARENT_METHOD_CALL(p, &nExpressionType, bReturn)) goto done;


  if (fCLASS_METHOD_CALL(p, &nExpressionType, bReturn)) goto done;
  else if (fCLASS_STATICMETHOD_CALL(p, &nExpressionType, bReturn)) goto done;

	// binding
  else if (binding_fCLASS_METHOD_CALL(p, &nExpressionType, bReturn)) goto done;

 // mm = this->getTokenPos();      

  if (binding_fCLASS_STATICMETHOD_CALL(p, &nExpressionType, bReturn)) goto done;
 // else if (binding_fFUNCTION_CALL(p, &nExpressionType, bReturn)) goto done;
//  else if (binding_fFUNCTION_OPERATOR(p, &nExpressionType)) goto done;
 // else if (binding_fCLASS_ENUM(p, &nExpressionType, bReturn)) goto done;
  //else if (binding_fCONNECT(p)) goto done;
  //else if (binding_fDISCONNECT(p)) goto done;

  else if (fFUNCTION_RETURN(p)) goto done; // must be called before fASSIGNMENT and fFUNCTION/fMODULE

	// ***

  else {
    with = currentWith;
    if (fASSIGNMENT(p)) goto done;           
  }

  /*
  // attention, must be after all productions starting with keyword
*/
	
  if (fNEW_METHOD_CALL(p, &nExpressionType, false)) goto done; 

  else if (fFUNCTION_CALL(p, &acIdentifier, &nExpressionType, false, &bUnknownFunction)) goto done; // sub or function call without return

  // builtin classes
	else if (fKBASIC(p, &nExpressionType, true)) goto done; // attention, must be after ASSIGNMENT

  else if (bUnknownFunction){
  	{ semanticError(token__MSC_IDENTIFIER, utility::con(acIdentifier, " (sub/function/method) with given arguments is not declared. Check the arguments of function which you wish to call.") ); _ERROR_ }
  }

#ifdef KBDEBUG
    if (stopAtLine(22)){
      int i = 9;
      i++;
    }
#endif

	_END_
done:
 {

  if (bProducePcode){     // wird auch für normal modus gebraucht, wegen on error goto
    register int n2 = p->getPos();
    p->setPos(n);
	  p->wr_STATEMENT(pcode__STATEMENT, n, n2, acFile, nLine);
    p->setPos(n2);
  }
   
   _DONE_
 }
}
 
/*
unlike vb.net structure does not act like a class, in kbasic it is simliar to a type yet
*/

bool parser::fREGISTER_ENUM(pcode *p)
/*
[*]
[*]
[*]
[KBASIC]
*/
{
	_BEGIN_
    
  if (fEOLREM());
  if (fEOF2());
  if (fVERSION());
  if (fFILENAME());  
	
	bool bTerm_PRIVATE = false;
	bool bTerm_PROTECTED = false;
	bool bTerm_PUBLIC = false;
  int nEnumScope = token__PUBLIC;

  if (bTerm_PRIVATE = parseTerm(token__PRIVATE)){
    nEnumScope = token__PRIVATE;
		if (!bParserPhase0 && isScopeDefaultGlobal()){
			semanticError(token__ENUM, "PRIVATE not allowed outside class/module"); _ERROR_
		}
  } else if (bTerm_PROTECTED = parseTerm(token__PROTECTED)){
    nEnumScope = token__PROTECTED;
		if (!bParserPhase0 && !isScopeClass()){
			semanticError(token__ENUM, "PROTECTED not allowed outside class"); _ERROR_
		}
		semanticError(token__ENUM, "PROTECTED not supported yet"); _ERROR_
	} else if (bTerm_PUBLIC = parseTerm(token__PUBLIC)){
    nEnumScope = token__PUBLIC;
	}

  if (!(/*bTerm_ENUM = */parseTerm(token__ENUM))){ _END_ } // to optimize, the 'dim' is one of the first statements

  if (!isKBASIC()){ semanticError(token__ENUM, "ENUM not allowed outside OPTION KBASIC"); _ERROR_ }

  bool bTerm_ENUM = false;

	static /**/ bool bIDENTIFIER[MAX_TYPE];
	static /**/ const char *acIdentifier[MAX_TYPE];

	bool bENUMNAME = false;
	const char *acEnumName = "";
  int nEnumId = 0;
	static /**/ int nEnumElementID[MAX_ENUM];

	static /**/ bool bTYPE[MAX_ENUM];
	static /**/ int nSize[MAX_ENUM];
	static /**/ const char *acType[MAX_ENUM];
	static /**/ bool bTerm__[MAX_ENUM];
	static /**/ bool bEXPRESSION[MAX_ENUM];
  static /**/ int nExpressionType[MAX_ENUM];

	static /**/ bool bTerm_AS[MAX_ENUM];
	bool bTerm_END = false;

	bool bEOL = false;
	int nElement = 0;
	int nPos = 0;

	const char *acCurrentType = "INTEGER";
  
	if (bENUMNAME = fID_KEYWORD_OR_BUILTIN(&acEnumName)){

    setCurrentEnum(acEnumName);

    if (bParserPhase0){
 		  nEnumId = registerEnum(acEnumName, nEnumScope);
 		  if (nEnumId == 0){ semanticError(token__ENUM, utility::con(acEnumName, " enum name already declared at some place") ); goto exit; }
      registerType(acEnumName, nEnumScope, nEnumId); 
    } else {
      nEnumId = findEnum(getScope(), acEnumName);
    }
 		

    if (bParserPhase0){
      _DONE_
    }



		if (bProducePcode){
      nPos = p->getPos();
     	p->wr_ENUM(pcode__ENUM, nEnumId, 0);
    }


		if (bEOL = fEOLREM()){

      do {} while (bEOL = fEOLREM());

			if (bIDENTIFIER[nElement] = fID_KEYWORD_OR_BUILTIN(&acIdentifier[nElement])){

       int n = getTokenPos();

				do {

         // test for token__END           
        if (utility::my_stricmp(acIdentifier[nElement], token::keyword_(token__END)) == 0){
           bIDENTIFIER[nElement] = false;
           setTokenPos(n); // to be able to parse END later
           break;
        }

          if (bTerm_AS[nElement] = parseTerm(token__AS)){
            int nSize = 0;
					  if (!(bTYPE[nElement] = fTYPE(&acType[nElement], &nSize))){ syntaxError(token__ENUM, "type name missing"); goto exit; }
          } else {
            acType[nElement] = acCurrentType;
          }

          int nType = findType(acType[nElement]);
 					if (nType == 0){ semanticError(token__ENUM, utility::con(acType[nElement], " not defined") ); goto exit; }

          switch (nType){
            case pcode__BYTE:
            case pcode__SHORT:
            case pcode__INTEGER:
            case pcode__LONG:
              break;
            default:
              { semanticError(token__ENUM, "only integer type is allowed in enum definition" ); goto exit; }
              break;
          }

					if (bProducePcode){
       			p->wr_ENUM_ELEMENT(pcode__ENUM_ELEMENT, nEnumId, nElement + 1, nType);
					}

          if (bTerm__[nElement] = parseTerm(token__OP_EQUAL)){

            // const expression, wobei ein vorheriges enum feld auch in der constexpression vorkommen darf
            if (bEXPRESSION[nElement] = fENUM_EXPRESSION(p, &nExpressionType[nElement])){}
						if (bTerm__[nElement] && !bEXPRESSION[nElement]){ syntaxError(token__ENUM, "assignment expression missing"); goto exit; }

				  } else {
					  bEXPRESSION[nElement] = false;
				  }


          // test auf value = ddd, wenn nicht implicit popinteger (popvorheriges enum +1), oder wenn erster 0
         if (bEXPRESSION[nElement]){
					  if (bProducePcode){
        		   p->wr_MOV_ENUM(pcode__MOV_ENUM, nEnumId, nElement + 1); // write pcode
           }
         } else {
           if (nElement == 0){
					    if (bProducePcode){
               p->wr_PUSH_INTEGER(pcode__PUSH_INTEGER, 0);
               p->wr_PUSH_INTEGER(pcode__PUSH_INTEGER, 1);
               p->wr_ADD(pcode__ADD);
        		    p->wr_MOV_ENUM(pcode__MOV_ENUM, nEnumId, nElement + 1); // write pcode                        
             }
           } else {
					    if (bProducePcode){
               p->wr_PUSH_ENUM(pcode__PUSH_ENUM, nEnumId, nElement + 1 - 1);
               p->wr_PUSH_INTEGER(pcode__PUSH_INTEGER, 1);
               p->wr_ADD(pcode__ADD);
      		      p->wr_MOV_ENUM(pcode__MOV_ENUM, nEnumId, nElement + 1); // write pcode
             }
           }
         }

 					
         bool b = registerEnumElement(nEnumId, acIdentifier[nElement], acType[nElement]);
 					if (b == false){ semanticError(token__ENUM, utility::con(acIdentifier[nElement], " element already declared at some place") ); goto exit; }

 					if (!(bEOL = fEOLREM())){ syntaxError(token__ENUM, "EOL missing"); goto exit; }

  				acCurrentType = acType[nElement];

          nElement++;

					do {} while (bEOL = fEOLREM());

          n = getTokenPos();

				} while (bIDENTIFIER[nElement] = fID_KEYWORD_OR_BUILTIN(&acIdentifier[nElement]));

			} else {
				if (!bIDENTIFIER[nElement]){ syntaxError(token__ENUM, "element name missing"); goto exit; }
			}

		  if (bTerm_END = parseTerm(token__END))
		  if (bTerm_ENUM = parseTerm(token__ENUM))
			if (bEOL = fEOLREM()){

		    if (bProducePcode){
          int n = p->getPos();
          p->setPos(nPos);
     	    p->wr_ENUM(pcode__ENUM, nEnumId, nElement);
          p->setPos(n);
        }
 					
      }
	  }
  
				 if (!bEOL){ syntaxError(token__ENUM, "EOL missing"); goto exit; }
		else if (nElement == 0){ syntaxError(token__ENUM, "no enumeration elements declared"); goto exit; }
		else if (!bTerm_END){ syntaxError(token__ENUM, "missing END"); goto exit; }
		else if (!bTerm_ENUM){ syntaxError(token__ENUM, "missing ENUM"); goto exit; }
    
    setCurrentEnum("");

    if (isScopeDefaultGlobal()){
  		parseInfo(p, utility::con("parsed ENUM ", acEnumName) );
    } else if (isScopeModule()){
  		parseInfo(p, utility::con("parsed MODULE ENUM ", acEnumName) );
    } else if (isScopeClass()){
  		parseInfo(p, utility::con("parsed CLASS ENUM ", acEnumName) );
    }
		return true;

	}
  
	//if (!bENUMNAME){ syntaxError(token__ENUM, "enum name missing"); goto exit; }

exit:
  setCurrentEnum("");
  _END_

}

bool parser::fREGISTER_TYPE(pcode *p)
/*
[QBASIC]
[VB]
[*]
[*]
*/
{
	_TBEGIN_

  if (fEOLREM());
  if (fEOF2());
  if (fVERSION());
  if (fFILENAME());  

	bool bTerm_PRIVATE = false;
	bool bTerm_PUBLIC = false;
	bool bTerm_PROTECTED = false;

  if (bTerm_PRIVATE = parseTerm(token__PRIVATE)){
		if (!bParserPhase0 && isScopeDefaultGlobal()){
			semanticError(token__TYPE, "PRIVATE not allowed outside class/module"); _TERROR_
		}
	} else if (bTerm_PUBLIC = parseTerm(token__PUBLIC)){
	} else if (bTerm_PROTECTED = parseTerm(token__PROTECTED)){
	}

  if (!(/*bTerm_TYPE = */parseTerm(token__TYPE))){ _TEND_ } // to optimize, the 'dim' is one of the first statements

	bool bTerm_TYPE = false;

  if (bTerm_PROTECTED){        
		if (!bParserPhase0 && !isScopeClass()){
      semanticError(token__TYPE, " type must not be PROTECTED outside class definition"); _TERROR_                
		}
		semanticError(token__TYPE, "PROTECTED not supported yet"); _TERROR_
  }

	static /**/ bool bIDENTIFIER[MAX_TYPE];
	static /**/ const char *acIdentifier[MAX_TYPE];

	bool bTYPENAME = false;
	const char *acTypeName = "";

	static /**/ bool bTYPE[MAX_TYPE];
	static /**/ const char *acType[MAX_TYPE];
	static /**/ int nSize[MAX_TYPE];

	static /**/ bool bTerm_AS[MAX_TYPE];
	bool bTerm_END = false;

	bool bEOL = false;
	bool bREM = false;
	int nElement = 0;

	const char *acCurrentType = "";

	static /**/ bool bARRAY[MAX_TYPE];
	static /**/ t_array a[MAX_TYPE];

  const char *CodeInstight_acFile =  getCurrentFile();
  int CodeInstight_nLine = getCurrentLine();
  int CodeInstight_nRow = getCurrentRow();

	if (bTYPENAME = fID_KEYWORD_OR_BUILTIN(&acTypeName)){

		if (bEOL = fEOLREM()){

    int nId = 0;

    if (bParserPhase0){
       nId = registerType(acTypeName, bTerm_PRIVATE ? token__PRIVATE : bTerm_PUBLIC ? token__PUBLIC : token__PROTECTED);
 			  if (nId == 0){ semanticError(token__TYPE, utility::con(acTypeName, " (type) already declared at some place") ); _TERROR_ }
    } else {
      nId = findType(acTypeName);
    }

      if (bParserPhase0){
       _DONE_
      }

			do {} while (bEOL = fEOLREM());

			if (bIDENTIFIER[nElement] = fID_KEYWORD_OR_BUILTIN(&acIdentifier[nElement])){

				do {

         if (bARRAY[nElement] = fARRAY(acIdentifier[nElement], &a[nElement])){}

					if (bTerm_AS[nElement] = parseTerm(token__AS))
					if (bTYPE[nElement] = fTYPE(&acType[nElement], &nSize[nElement])){} // nSize[nElement] used for LSTRING len only

							 if (!bTerm_AS[nElement]){ syntaxError(token__TYPE, "AS missing"); _TERROR_ }
         else if (!bTYPE[nElement]){ syntaxError(token__TYPE, "type name missing"); _TERROR_ }

 					if (!(bEOL = fEOLREM())){ syntaxError(token__TYPE, "EOL missing"); _TERROR_ }

					nElement++;

					do {} while (bEOL = fEOLREM());

           // test for token__END 
          int n = getTokenPos();
          if (bIDENTIFIER[nElement] = fID_KEYWORD_OR_BUILTIN(&acIdentifier[nElement])){
             if (utility::my_stricmp(acIdentifier[nElement], token::keyword_(token__END)) == 0){
              bIDENTIFIER[nElement] = false;
              setTokenPos(n); // to be able to parse END later
            }
          }

				} while (bIDENTIFIER[nElement]);

			} else {
				if (!bIDENTIFIER[nElement]){ syntaxError(token__TYPE, "element name missing"); _TERROR_ }
			}

		  if (bTerm_END = parseTerm(token__END))
		  if (bTerm_TYPE = parseTerm(token__TYPE))
			if (bEOL = fEOLREM()){

				if (bProducePcode){
     			p->wr_TYPE(pcode__TYPE, nId, nElement);
				}

 				for (int i = 0; i < nElement; i++){

 					if (bTYPE[i] == true){
 						acCurrentType = acType[i];
 					}

   			  int nTypes = findType(acCurrentType);
 					if (nTypes == 0){ semanticError(token__TYPE, utility::con(acCurrentType, " type not defined") ); _TERROR_ }
					if (nTypes == pcode__VARIANT){ semanticError(token__TYPE, "variant type is not allowed in user defined type" ); _TERROR_ }

 					const char *acVars = acIdentifier[i];

         int n = nSize[i];
         if (n == 0) n = myMemory_type->getSize(nTypes); 

 					bool b = registerTypeElement(nId, acVars, acCurrentType, n, &a[i]);
 					if (b == false){ semanticError(token__TYPE, utility::con(acVars, " element already declared at some place") ); _TERROR_ }

					if (bProducePcode){
       			p->wr_TYPE_ELEMENT(pcode__TYPE_ELEMENT, i + 1, nTypes, &a[i], nSize[i]);
					}

 				}
      }
	  }

				 if (!bEOL){ syntaxError(token__TYPE, "EOL missing"); _TERROR_ }
		else if (!bTerm_END){ syntaxError(token__TYPE, "missing END"); _TERROR_ }
		else if (!bTerm_TYPE){ syntaxError(token__TYPE, "missing TYPE"); _TERROR_ }

    if (isScopeDefaultGlobal()){
  		parseInfo(p, utility::con("parsed TYPE ", acTypeName) );
    } else if (isScopeModule()){
  		parseInfo(p, utility::con("parsed MODULE TYPE ", acTypeName) );
    } else if (isScopeClass()){
  		parseInfo(p, utility::con("parsed CLASS TYPE ", acTypeName) );
    }

		return true;

	}
//	if (!bTYPENAME){ syntaxError(token__TYPE, "type name missing"); _TERROR_ }

	_TEND_
}

bool parser::fCOL(bool bPos)
{
	//_TBEGIN_

	//register bool bTerm_COL = false;

	if (/*bTerm_COL = */parseTerm(token__SYM_COLON)){
		//parseInfo(p, "EOL (:)", true, getCurrentLine());
		if (bPos == false) if (!bSilent) CONSOLE print("\n");
		//return bTerm_COL;
    return true;
	}

  return false;
	//_TEND_
}

bool parser::fEOL2(bool bPos)
{
	//_TBEGIN_

	//register bool bTerm_EOL = false;

	if (/*bTerm_EOL = */parseTerm(token__MSC_EOL)){
		//parseInfo(p, "EOL", true, getCurrentLine() - 1);
		//return bTerm_EOL;
    if (bGLOBAL_SYM_UL){
      bGLOBAL_SYM_UL = false;
      bGLOBAL_EOL = false;
    } else {
      bGLOBAL_EOL = true;
    }
    return true;
    /*
	} else if (bTerm_EOL = parseTerm(token__KB_EOF2)){
    return bTerm_EOL;
    */
	} else if (/*bTerm_EOL = */parseTerm(token__KB_EOF)){
		bParseToken = false; // is the last token symbol, so stop parse
		//parseInfo(p, "EOL (EOF)", true, getCurrentLine());
		//return bTerm_EOL;
    if (bGLOBAL_SYM_UL){
      bGLOBAL_SYM_UL = false;
      bGLOBAL_EOL = false;
    } else {
      bGLOBAL_EOL = true;
    }
    return true;
  } else if (isLastToken()){
    return true;
  }
  return false;
  

	//_TEND_
}

bool parser::fEOF2()
{
	//_TBEGIN_

	//register bool bTerm_EOF2 = false;

	if (/*bTerm_EOF2 = */parseTerm(token__KB_EOF2)){
    return true;
  }
  return false;
  

	//_TEND_
}

bool parser::peekEOLREM()
{
 // register int n = peekToken();

  switch(peekToken()){
    case token__SYM_COLON:
    case token__MSC_EOL:
    case token__KB_EOF:
    case token__KB_EOF2:
    case token__REM:
    case token__REM_SHORT:
    case token__REM_MULTILINE:
    case token__REM_DOCUMENTATION:
    return true;
  }
  
  return false;
}

bool parser::fEOLREM(bool bPos)
{
  return (fEOL() || fREM());
}

bool parser::fEOL(bool bPos)
{
	//_TBEGIN_

	if (fEOL2(bPos)) return true;
	else if (fCOL(bPos)) return true;

  return false;
  
	//_TEND_
}

bool parser::fREM(bool bParseEOL)
{
	//_TBEGIN_

	//register bool bTerm_REM = false;

  if ((/*bTerm_REM = */parseTerm(token__REM)) || (/*bTerm_REM = */parseTerm(token__REM_SHORT)) || (/*bTerm_REM = */parseTerm(token__REM_MULTILINE)) || (/*bTerm_REM = */parseTerm(token__REM_DOCUMENTATION))){
  	//register bool bEOL = false;
		if (bParseEOL && /*bEOL = */fEOL()){}
		//parseInfo(p, "parsed REM");
		return true;
	}

  return false;
  
	//_TEND_
}

bool parser::fFILENAME()
{
	//_TBEGIN_

	//register bool bTerm_FILENAME = false;

  if (/*bTerm_FILENAME = */parseTerm(token__KB_FILENAME)){
    
		return true;
	}

  return false;
  
	//_TEND_
}

bool parser::fVERSION()
{
	//_TBEGIN_

	//register bool bTerm_VERSION = false;

  if (/*bTerm_VERSION = */parseTerm(token__KB_VERSION)){
		return true;
	}

  return false;
  
	//_TEND_
}

/*
bool parser::fOPERATOR_OVERLOADING(pcode *p, int nVar, t_scope scope, int nType, int nOperatorType)
{
  register int nReturnExpressionType = 0;

  return fOPERATOR_OVERLOADING(p, nVar, scope, nType, nOperatorType, &nReturnExpressionType);
}

bool parser::fOPERATOR_OVERLOADING(pcode *p, int nType, int nOperatorType, int *nReturnExpressionType)
{
  register int nVar = 0;
  register t_scope scope = global;

  return fOPERATOR_OVERLOADING(p, nVar, scope, nType, nOperatorType, nReturnExpressionType);
}

bool parser::fOPERATOR_OVERLOADING(pcode *p, int nVar, t_scope scope, int nType, int nOperatorType, int *nReturnExpressionType)
{
	_BEGIN_

   if (nVar){
	   if (nType == token__ME){
       p->wr_PUSH_ME(pcode__PUSH_ME);
	   } else if (nType == token__PARENT){
		   p->wr_PUSH_PARENT(pcode__PUSH_PARENT);        
     } else {
		   p->wr_PUSH_ID(pcode__PUSH_ID, nVar, scope, true);
     }   
   }

   if (binding_fCLASS_OPERATOR(p, nReturnExpressionType, nType, nOperatorType)){

			if (bProducePcode){
 				 // the expression is already transformed to pcode
      }

      if (nVar == 0){
        parseInfo(p, "parsed OPERATOR OVERLOADING" );
      }
      _DONE_
/ *
   } else if (binding_fFUNCTION_OPERATOR(p, nReturnExpressionType, nType, nOperatorType)){

			if (bProducePcode){
 				 // the expression is already transformed to pcode
      }

      if (nVar == 0){
        parseInfo(p, "parsed FUNCTION OPERATOR OVERLOADING" );
      }
      _DONE_
* /
   }

  _END_
}*/

/*
bool parser::fADD_ASSIGNMENT(pcode *p)
{
	_BEGIN_

	int nVar;// = 0;
	t_scope scope;// = global;
	int nType;// = 0;

	if (fVARIABLE_DECLARED(p, &nVar, &scope, &nType)){

	  bool bTerm__ = false;

   	if (bTerm__ = parseTerm(token__OP_ADD_EQUAL)){

      int nPos = myPcode->getPos();

      if (fOPERATOR_OVERLOADING(p, nVar, scope, nType, token__OP_ADD_EQUAL)){
        parseInfo(p, "parsed ADD ASSIGNMENT OPERATOR OVERLOADING" );
        _DONE_       

      } else {
        // rollback
        myPcode->setPos(nPos);
      }
                 
       // TODO3
      semanticError(token__KEYWORD,  " Sorry! The += is not supported yet " ); _ERROR_ 

      if (!bSilent && bProducePcode){
       p->wr_SEPARATOR(pcode__SEPARATOR, utility::con("fADD_ASSIGNMENT", getCurrentLine() - 1));
      }

		  if (nType == token__ME){
        { semanticError(token__KEYWORD, "+= not allowed in combination with ME"); _ERROR_ }
		  } else if (nType == token__PARENT){
        { semanticError(token__KEYWORD, "+= not allowed in combination with PARENT"); _ERROR_ }
      } else {
      }

	    bool bEXPRESSION = false;

      if (!(bEXPRESSION = fNUMERIC_EXPRESSION(p))){ syntaxError(token__OP_ADD_EQUAL, "numeric expression missing"); _ERROR_ }

			if (bProducePcode){
 				// the expression is already transformed to pcode, so we only need the assignment pcode
        // TODO3
      }

      parseInfo(p, "parsed ADD ASSIGNMENT " );
      _DONE_

    }
  }

  _END_
}

bool parser::fSUB_ASSIGNMENT(pcode *p)
{
	_BEGIN_

	int nVar;// = 0;
	t_scope scope;// = global;
	int nType;// = 0;

	if (fVARIABLE_DECLARED(p, &nVar, &scope, &nType)){

	  bool bTerm__ = false;

   	if (bTerm__ = parseTerm(token__OP_SUB_EQUAL)){

      int nPos = myPcode->getPos();

      if (fOPERATOR_OVERLOADING(p, nVar, scope, nType, token__OP_SUB_EQUAL)){
        parseInfo(p, "parsed SUB ASSIGNMENT OPERATOR OVERLOADING" );
        _DONE_       

      } else {
        // rollback
        myPcode->setPos(nPos);
      }
                 
       // TODO3
      semanticError(token__KEYWORD,  " Sorry! The -= is not supported yet " ); _ERROR_ 


      if (!bSilent && bProducePcode){
        p->wr_SEPARATOR(pcode__SEPARATOR, utility::con("fSUB_ASSIGNMENT", getCurrentLine() - 1));
      }

		  if (nType == token__ME){
        { semanticError(token__KEYWORD, "-= not allowed in combination with ME"); _ERROR_ }
		  } else if (nType == token__PARENT){
        { semanticError(token__KEYWORD, "-= not allowed in combination with PARENT"); _ERROR_ }
      } else {
      }

	    bool bEXPRESSION = false;

      if (!(bEXPRESSION = fNUMERIC_EXPRESSION(p))){ syntaxError(token__OP_SUB_EQUAL, "numeric expression missing"); _ERROR_ }

			if (bProducePcode){
 				// the expression is already transformed to pcode, so we only need the assignment pcode
        // TODO3
      }

      parseInfo(p, "parsed SUB ASSIGNMENT " );
      _DONE_

    }
  }

  _END_
}

bool parser::fDIV_ASSIGNMENT(pcode *p)
{
	_BEGIN_

	int nVar;// = 0;
	t_scope scope;// = global;
	int nType;// = 0;

	if (fVARIABLE_DECLARED(p, &nVar, &scope, &nType)){

	  bool bTerm__ = false;

   	if (bTerm__ = parseTerm(token__OP_DIV_EQUAL)){

      int nPos = myPcode->getPos();

      if (fOPERATOR_OVERLOADING(p, nVar, scope, nType, token__OP_DIV_EQUAL)){
        parseInfo(p, "parsed DIV ASSIGNMENT OPERATOR OVERLOADING" );
        _DONE_       

      } else {
        // rollback
        myPcode->setPos(nPos);
      }

       // TODO3
       semanticError(token__KEYWORD,  " Sorry! The /= is not supported yet " ); _ERROR_ 

       if (!bSilent && bProducePcode){
        p->wr_SEPARATOR(pcode__SEPARATOR, utility::con("fDIV_ASSIGNMENT", getCurrentLine() - 1));
       }

		   if (nType == token__ME){
         { semanticError(token__KEYWORD, "/= not allowed in combination with ME"); _ERROR_ }
		   } else if (nType == token__PARENT){
         { semanticError(token__KEYWORD, "/= not allowed in combination with PARENT"); _ERROR_ }
      } else {
      }

	    bool bEXPRESSION = false;

      if (!(bEXPRESSION = fNUMERIC_EXPRESSION(p))){ syntaxError(token__OP_DIV_EQUAL, "numeric expression missing"); _ERROR_ }

			if (bProducePcode){
 				// the expression is already transformed to pcode, so we only need the assignment pcode
        // TODO3
      }

      parseInfo(p, "parsed DIV ASSIGNMENT " );
      _DONE_

    }
  }

  _END_
}

bool parser::fMUL_ASSIGNMENT(pcode *p)
{
	_BEGIN_

	int nVar;// = 0;
	t_scope scope;// = global;
	int nType;// = 0;

	if (fVARIABLE_DECLARED(p, &nVar, &scope, &nType)){

	  bool bTerm__ = false;

   	if (bTerm__ = parseTerm(token__OP_MUL_EQUAL)){

      int nPos = myPcode->getPos();

      if (fOPERATOR_OVERLOADING(p, nVar, scope, nType, token__OP_MUL_EQUAL)){
        parseInfo(p, "parsed MUL ASSIGNMENT OPERATOR OVERLOADING" );
        _DONE_       

      } else {
        // rollback
        myPcode->setPos(nPos);
      }

       // TODO3
       semanticError(token__KEYWORD,  " Sorry! The *= is not supported yet " ); _ERROR_ 


      if (!bSilent && bProducePcode){
       p->wr_SEPARATOR(pcode__SEPARATOR, "fMUL_ASSIGNMENT");
      }

		  if (nType == token__ME){
        { semanticError(token__KEYWORD, "*= not allowed in combination with ME"); _ERROR_ }
		  } else if (nType == token__PARENT){
        { semanticError(token__KEYWORD, "*= not allowed in combination with PARENT"); _ERROR_ }
      } else {
      }

	    bool bEXPRESSION = false;

      if (!(bEXPRESSION = fNUMERIC_EXPRESSION(p))){ syntaxError(token__OP_MUL_EQUAL, "numeric expression missing"); _ERROR_ }

			if (bProducePcode){
 				// the expression is already transformed to pcode, so we only need the assignment pcode
        // TODO3
      }

      parseInfo(p, "parsed MUL ASSIGNMENT " );
      _DONE_

    }
  }

  _END_
}

bool parser::fOR_ASSIGNMENT(pcode *p)
{
	_BEGIN_

	int nVar;// = 0;
	t_scope scope;// = global;
	int nType;// = 0;

	if (fVARIABLE_DECLARED(p, &nVar, &scope, &nType)){

	  bool bTerm__ = false;

   	if (bTerm__ = parseTerm(token__OP_OR_EQUAL)){

      int nPos = myPcode->getPos();

      if (fOPERATOR_OVERLOADING(p, nVar, scope, nType, token__OP_OR_EQUAL)){
        parseInfo(p, "parsed OR ASSIGNMENT OPERATOR OVERLOADING" );
        _DONE_       

      } else {
        // rollback
        myPcode->setPos(nPos);
      }

       // TODO3
       semanticError(token__KEYWORD,  " Sorry! The |= is not supported yet " ); _ERROR_ 


       if (!bSilent && bProducePcode){
        p->wr_SEPARATOR(pcode__SEPARATOR, utility::con("fOR_ASSIGNMENT", getCurrentLine() - 1));
       }

		   if (nType == token__ME){
          { semanticError(token__KEYWORD, "|= not allowed in combination with ME"); _ERROR_ }
		   } else if (nType == token__PARENT){
          { semanticError(token__KEYWORD, "|= not allowed in combination with PARENT"); _ERROR_ }
       } else {
       }

	    bool bEXPRESSION = false;

      if (!(bEXPRESSION = fNUMERIC_EXPRESSION(p))){ syntaxError(token__OP_OR_EQUAL, "numeric expression missing"); _ERROR_ }

			if (bProducePcode){
 				// the expression is already transformed to pcode, so we only need the assignment pcode
        // TODO3
      }

      parseInfo(p, "parsed OR ASSIGNMENT " );
      _DONE_

    }
  }

  _END_
}

bool parser::fXOR_ASSIGNMENT(pcode *p)
{
	_BEGIN_

	int nVar;// = 0;
	t_scope scope;// = global;
	int nType;// = 0;

	if (fVARIABLE_DECLARED(p, &nVar, &scope, &nType)){

	  bool bTerm__ = false;

   	if (bTerm__ = parseTerm(token__OP_XOR_EQUAL)){

      int nPos = myPcode->getPos();

      if (fOPERATOR_OVERLOADING(p, nVar, scope, nType, token__OP_XOR_EQUAL)){
        parseInfo(p, "parsed XOR ASSIGNMENT OPERATOR OVERLOADING" );
        _DONE_       

      } else {
        // rollback
        myPcode->setPos(nPos);
      }

       // TODO3
       semanticError(token__KEYWORD,  " Sorry! The ^= is not supported yet " ); _ERROR_ 

       if (!bSilent && bProducePcode){
        p->wr_SEPARATOR(pcode__SEPARATOR, utility::con("fXOR_ASSIGNMENT", getCurrentLine() - 1));
       }

		    if (nType == token__ME){
          { semanticError(token__KEYWORD, "^= not allowed in combination with ME"); _ERROR_ }
		    } else if (nType == token__PARENT){
          { semanticError(token__KEYWORD, "^= not allowed in combination with PARENT"); _ERROR_ }
       } else {
       }

	    bool bEXPRESSION = false;

      if (!(bEXPRESSION = fNUMERIC_EXPRESSION(p))){ syntaxError(token__OP_XOR_EQUAL, "numeric expression missing"); _ERROR_ }

			if (bProducePcode){
 				// the expression is already transformed to pcode, so we only need the assignment pcode
        // TODO3
      }

      parseInfo(p, "parsed XOR ASSIGNMENT " );
      _DONE_

    }
  }

  _END_
}

bool parser::fAND_ASSIGNMENT(pcode *p)
{
	_BEGIN_

	int nVar;// = 0;
	t_scope scope;// = global;
	int nType;// = 0;

	if (fVARIABLE_DECLARED(p, &nVar, &scope, &nType)){

    if (!bSilent && bProducePcode){
      p->wr_SEPARATOR(pcode__SEPARATOR, utility::con("fAND_ASSIGNMENT", getCurrentLine() - 1));
    }

		if (nType == token__ME){
     { semanticError(token__KEYWORD, "&= not allowed in combination with ME"); _ERROR_ }
		} else if (nType == token__PARENT){
     { semanticError(token__KEYWORD, "&= not allowed in combination with PARENT"); _ERROR_ }
   } else {
   }

	  bool bTerm__ = false;

   	if (bTerm__ = parseTerm(token__OP_AND_EQUAL)){

	    bool bEXPRESSION = false;

      if (!(bEXPRESSION = fNUMERIC_EXPRESSION(p))){ syntaxError(token__OP_AND_EQUAL, "numeric expression missing"); _ERROR_ }

			if (bProducePcode){
 				// the expression is already transformed to pcode, so we only need the assignment pcode
        // TODO3
      }

      parseInfo(p, "parsed AND ASSIGNMENT " );
      _DONE_

    }
  }

  _END_
}*/


bool parser::compatibleType(int n, int n2, bool bRetrySwapped)
{  
  if (memory_type::isClass(n2)){

    int nParentId = n2;

    // walk hierarchy
    do {
      if (memory_type::isBinding(nParentId)){ // binding
        parser_class2 *pc = (parser_class2 *) myParser_classMethod->myParser_class.get(nParentId);

        if (pc == 0) break;

        nParentId = pc->nParentClassId2;
        if (memory_type::compatibleType(n, nParentId)) return true;

        nParentId = pc->nParentClassId;
        if (memory_type::compatibleType(n, nParentId)) return true;

      } else {
        nParentId = myClass->getParentId(nParentId);
      }

      if (memory_type::compatibleType(n, nParentId)) return true;

    } while (nParentId > 0);

  } else if (memory_type::isEnum(n)){
    	switch(n2){
    		case pcode__BYTE:
    		case pcode__SHORT:
    		case pcode__INTEGER:
    		case pcode__LONG:

          return true;
          break;
      }
  }

  if (memory_type::isBinding(n2)){ // binding
    int nParentId = n2;
    // walk hierarchy
    do {
      parser_class2 *pc = (parser_class2 *) myParser_classMethod->myParser_class.get(nParentId);
      if (pc == 0) break;
      if (pc->nParentClassId == n) return true;
      nParentId = pc->nParentClassId;
    } while (nParentId > 0);
    
    int nParentId2 = n2;
    // walk hierarchy
    do {
      parser_class2 *pc = (parser_class2 *) myParser_classMethod->myParser_class.get(nParentId2);
      if (pc == 0) break;
      if (pc->nParentClassId2 == n) return true;
      nParentId2 = pc->nParentClassId2;
    } while (nParentId2 > 0);

  }

  if (memory_type::isBinding(n)){ // binding
    int nParentId = n;
    // walk hierarchy
    do {
      parser_class2 *pc = (parser_class2 *) myParser_classMethod->myParser_class.get(nParentId);
      if (pc == 0) break;
      if (pc->nParentClassId == n2) return true;
      nParentId = pc->nParentClassId;
    } while (nParentId > 0);
    
    int nParentId2 = n;
    // walk hierarchy
    do {
      parser_class2 *pc = (parser_class2 *) myParser_classMethod->myParser_class.get(nParentId2);
      if (pc == 0) break;
      if (pc->nParentClassId2 == n2) return true;
      nParentId2 = pc->nParentClassId2;
    } while (nParentId2 > 0);

  }
re:
  if (memory_type::compatibleType(n, n2)) return true;

  if (bRetrySwapped && !memory_type::scalar(n) && !memory_type::scalar(n2)){
    return compatibleType(n2, n, false);
  } else {
    return false;
  }
  
}

/* *
[EXPLANATION]
NAME: ASSIGNMENT
DESC:
SEEALSO:
*/
bool parser::fASSIGNMENT(pcode *p)
/*
[QBASIC]
- LET, RSET, LSET
[VB]
- LET, RSET, LSET
[*]
[*]
*/
{
	_BEGIN_

  if (with_pos_list_POS == -1){
    // *** look up if = is present in line
    bool bRet = true;
    int nTest = 0;

	  do {

		  nTest = peekToken();

		  if (nTest == token__MSC_EOL){
        _END_;      
      } else if (nTest == token__OP_EQUAL){ //  dangerous nur auf eol prfen? rem : 
			  break;
		  }

	  } while(proceedParse() && bRet && (bRet = nextToken()));

    _END2_
  } else {
    with_pos_list_POS = with_pos_list_POS;
  }
  // ***


	bool bVARIABLE = false;
	bool bTerm_SET = false;
	bool bTerm_LET = false;
	bool bTerm_LSET = false;
	bool bTerm_RSET = false;
	bool bTerm__ = false;
	bool bEXPRESSION = false;
	bool bIDENTIFIER = false;

	int nExpressionType = 0;

	if (!isVERYOLDBASIC() && (bTerm_SET = parseTerm(token__SET))){} // object zuweisung [VB]
	else if ((isVERYOLDBASIC() || isOLDBASIC()) && (bTerm_LET = parseTerm(token__LET))){} // optional [QBASIC] [VB]
  else if ((isVERYOLDBASIC() || isOLDBASIC()) && (bTerm_LSET = parseTerm(token__LSET))){} // optional [QBASIC] [VB]
  else if (isVERYOLDBASIC() && (bTerm_RSET = parseTerm(token__RSET))){} // optional [QBASIC] [VB]

  if (isKBASIC()){
	      if ((bTerm_LET = parseTerm(token__LET))){ semanticError(token__LET, "LET is not supported inside OPTION KBASIC. It is obsolete."); _ERROR_ }
    else if ((bTerm_LSET = parseTerm(token__LSET))){ semanticError(token__LSET, "LSET is not supported inside OPTION KBASIC. It is obsolete."); _ERROR_ }
    else if ((bTerm_RSET = parseTerm(token__RSET))){ semanticError(token__RSET, "RSET is not supported inside OPTION KBASIC. It is obsolete."); _ERROR_ }
  }

	int nVar = 0;
	t_scope scope = global;
	bool bReference = false;
	bool bProperty = false;
	bool bProperty2 = false;
	bool bProperty3 = false;
	bool bAllSize = false;
  int nLStringLen = 0;
	bool bImplicitDIM = false;
	bool bTestImplicitDim = true;
	int nIdType = 0;
	int nType = 0;
	bool bTestProperty = true;


  t_arrayVariable a_left;
  t_arrayVariable a_right;

  pcode *pp;

#ifdef KBDEBUG
  if (stopAtLine(11)){
    int i = 3;
    i++;
  }
#endif

  pp = new pcode(p->sCurrentFile.ascii());

  if (bIDENTIFIER = fPROPERTY_ASSIGNMENT(p, &nVar, &nType, &bProperty2)){
    bProperty = !bProperty2;
    nIdType = nType;
    if (bProperty2){
      nType = nVar;
    }    
  } else if (bIDENTIFIER = binding_fPROPERTY_ASSIGNMENT(pp, &nVar, &nType, &nIdType)){
    bProperty2 = true;
  } else if (bIDENTIFIER = binding_fSTATICPROPERTY_ASSIGNMENT(pp, &nVar, &nType, &nIdType)){
    bProperty3 = true;
  } else {
    bIDENTIFIER = fVARIABLE_ASSIGNMENT(pp, &nVar, &scope, &nIdType, &nType, &bImplicitDIM, bTestImplicitDim, &a_left, &bAllSize, &nLStringLen, &bReference, &bProperty, bTestProperty);
  }

	if (bIDENTIFIER){

    nExpectedType = nType;

#ifdef KBDEBUG
  if (stopAtLine(311)){
    int i = 9;
    i++;
  }
#endif

    if (memory_type::isEnum(nType)){
      nType = pcode__INTEGER; // TODO2
    }

		if (!bSilent && bProducePcode){
      p->wr_SEPARATOR(pcode__SEPARATOR, utility::con("fASSIGNMENT", getCurrentLine() - 1));
    }

		if (bImplicitDIM){
  		if (bProducePcode) p->wr_DIM(pcode__DIM, nVar, scope, nType, false, false, false, isSubVarStatic(), 0, 0, "", false); // write pcode
    }

    if ((bTerm_LSET || bTerm_RSET) && !memory_type::isString(nType)){ syntaxError(token__OP_EQUAL, "variable (LSET or RSET) must be type of STRING"); _ERROR_ }
    
   	if (bTerm__ = parseTerm(token__OP_EQUAL)){


      int nPos = myPcode->getPos();
      //int nPos2 = myToken->getPos();
/*
      if (fOPERATOR_OVERLOADING(p, nVar, scope, nType, token__OP_EQUAL)){
        parseInfo(p, "parsed ASSIGNMENT OPERATOR OVERLOADING" );
        _DONE_       

      } else {*/
        // rollback
        myPcode->setPos(nPos);
#ifdef KBDEBUG
  if (stopAtLine(1)){
    int i = 9;
    i++;
  }
#endif


			a_right.var.use.count = 9999; // hack see below, if expression is a non skalar id, then 9999 will be changed to the right dimension			

      bEXPRESSION = false;
     if (bProperty){

		    bool bEXPRESSION2;    
		    bool bISMISSING; 
        int nReferenceType;

   	    const char *acName = "";
   	    const char *acType = "";
   	    int nParameterCall = 0;
   	    bool bOptional = false;
   	    bool bDefault = false;    
       bool bParamArray = false;
   	    t_array *a = 0;
		    defaultvalue *defval = 0;
       int nParamId = 0;
       int nParamLStringLen = 0;
       int nParamArray = 0;
       bool bClassMethod = false;
       int nClassId = nVar;
       int nId = nType;
       bool bParent = false;

       if (myClass->firstParameterPropertySet	(nClassId, nId, &acName, &acType, &nParameterCall, &bOptional, &bDefault, &bParamArray, &a, &defval, &nParamId, &nParamLStringLen)){
         if (!pushParam(p, nId, acName, acType, nParameterCall, bOptional, bDefault, bParamArray, a, defval, bClassMethod, nClassId, nParamId, &bEXPRESSION2, &bISMISSING, &nReferenceType)){ syntaxError(token__PROPERTY, "missing matching expression for property set"); _ERROR_ }
       } else {
         { internalError("missing property set parameter"); _ERROR_ }
       }

       if (bProducePcode){
         p->wr_ENTER_PROPERTYSET(pcode__ENTER_PROPERTYSET, nClassId, nId); // write pcode

			    if (!popParam(p, nId, acName, acType, nParameterCall, bOptional, bDefault, bParamArray, a, bClassMethod, nClassId, nParamId, bEXPRESSION, bISMISSING, nReferenceType)){}

         p->wr_ClassPropertySet(pcode__CLASSPROPERTYSET, nClassId, nId, myClass->getNamePropertySet(nClassId, nId), false, false, bParent, true);
       }

       nType = findType(myClass->typePropertyGet(nClassId, nId));
       nExpressionType = findType(acType);

			 if (!compatibleType(nType, nExpressionType)){ 
         if (nExpressionType == pcode__QSTRING || nExpressionType == pcode__CSTRING){
           { semanticError(token__OP_EQUAL, "incompatible types in assignment. Left variable must be of type STRING or VARIANT"); _ERROR_ }
         } else {
           { semanticError(token__OP_EQUAL, "incompatible types in assignment"); _ERROR_ }
         }
       }

       bEXPRESSION = true;
     } else if (bProperty2){

#ifdef KBDEBUG
         if (stopAtLine(114)){
          int i = 9;
          i++;
         }
#endif


       bEXPRESSION = fEXPRESSION(pp, &nExpressionType, &a_right);
      if (!bEXPRESSION){ syntaxError(token__OP_EQUAL, "assignment expression missing"); _ERROR_ }

			 if (!compatibleType(nIdType, nExpressionType)){ 
        
           if (nExpressionType == pcode__QSTRING || nExpressionType == pcode__CSTRING){
             { semanticError(token__OP_EQUAL, "incompatible types in assignment. Left variable must be of type STRING or VARIANT"); _ERROR_ }
           } else {
             { semanticError(token__OP_EQUAL, "incompatible types in assignment"); _ERROR_ }
           }
       
       }

       if (bProducePcode){

         static int nParamCount = 1;
         static bool bReturn = false;

         pp->wr_PUSH_INTEGER(pcode__PUSH_INTEGER, nParamCount);
				 pp->wr_binding_ClassProperty(pcode__binding_CLASSPROPERTY, nType, bReturn);                
       }
       nExpressionType = nType = nIdType;

     } else if (bProperty3){

       bEXPRESSION = fEXPRESSION(pp, &nExpressionType, &a_right);
       if (!bEXPRESSION){ syntaxError(token__OP_EQUAL, "assignment expression missing"); _ERROR_ }

			 if (!compatibleType(nIdType, nExpressionType)){ 
         if (nExpressionType == pcode__QSTRING || nExpressionType == pcode__CSTRING){
           { semanticError(token__OP_EQUAL, "incompatible types in assignment. Left variable must be of type STRING or VARIANT"); _ERROR_ }
         } else {
           { semanticError(token__OP_EQUAL, "incompatible types in assignment"); _ERROR_ }
         }
       }

       if (bProducePcode){

         static int nParamCount = 1;
         static bool bReturn = false;

          pp->wr_PUSH_INTEGER(pcode__PUSH_INTEGER, nParamCount);
				  pp->wr_binding_ClassStaticProperty(pcode__binding_CLASSSTATICPROPERTY, nType, bReturn);                
       }
       nExpressionType = nType = nIdType;

     } else {


#ifdef KBDEBUG
  if (stopAtLine(237)){
    int i = 3;
    i++;
  }
#endif

       bEXPRESSION = fEXPRESSION(p, &nExpressionType, &a_right);
     }

     if (bEXPRESSION){

       if (bTerm_SET){
					if (nExpressionType != pcode__OBJECT){ semanticError(token__OP_EQUAL, "incompatible types in assignment, must be type OBJECT"); _ERROR_ }
				}

       if (isVERYOLDBASIC()){
         if (bTerm_LSET){
           if (nType != pcode__QSTRING && nType != pcode__CSTRING && nType != pcode__LQSTRING && nType != pcode__LCSTRING){
             { semanticError(token__OP_EQUAL, "wrong datatype for LSET"); _ERROR_ }
           }
         } else if (bTerm_RSET){
           if (nType != pcode__LCSTRING){ // RSET
             { semanticError(token__OP_EQUAL, "wrong datatype for RSET, must be LCSTRING"); _ERROR_ }
           }
         }
       }

				if (!compatibleType(nType, nExpressionType)){ 
          if (nExpressionType == pcode__QSTRING || nExpressionType == pcode__CSTRING){
            { semanticError(token__OP_EQUAL, "incompatible types in assignment. Left variable must be of type STRING or VARIANT"); _ERROR_ }
          } else {
            { semanticError(token__OP_EQUAL, "incompatible types in assignment"); _ERROR_ }
          }
       }
				
        // a_left.var.def: how the array defintion of the var looks like j[0].element[9]   --> j[0] main array of var
        // a_left.var.use: current access to array of var

        // a_right.var.def: how the current array defintion of the expression looks like j[0].element[9]   --> j[0] main array of var
        // a_right.var.use: current access to array of the expression

        // ...element.def --> j[0].element[9]   --> element[9] element array of var

        if (nType == pcode__VARIANT){
          // spezialfall variant = automatisch array, auch ohne explicite deklaration: 
          if (a_left.var.def.isArray() && (a_left.var.def.count == 1 && a_left.var.use.count == 0 && a_right.var.use.count == 9999)){
          } else {

         bool b1 = a_left.var.def.isArray() && a_left.var.def.count > 0;
         bool b2 = (a_left.element.def.isArray() && a_left.element.def.count > 0);

         if (nIdType == nType && !memory_type::scalar(nType) && !memory_type::isClass(nType) &&
             (
             // left no array, right scalar
                (b1 && !b2 && a_left.var.use.count == 0 && a_right.var.use.count == 9999) 
             || (b1 && !b2 && a_left.var.use.count > 0 && a_right.var.use.count == 0) 
             || (b1 && !b2 && a_left.var.use.count == 0 && a_right.var.use.count > 0)

             || (b2 && a_left.element.use.count > 0 && a_right.element.use.count == 0) 
             || (b2 && a_left.element.use.count == 0 && a_right.element.use.count > 0)

             )
            )
          { semanticError(token__OP_EQUAL, "left array, right non array assignment"); _ERROR_ }
          }
       } else {

#ifdef KBDEBUG
         if (stopAtLine(49)){
          int i = 9;
          i++;
         }
#endif

         bool b1 = a_left.var.def.isArray() && a_left.var.def.count > 0;
         bool b2 = a_left.element.def.isArray() && a_left.element.def.count > 0;         

         if (nIdType == nType && !memory_type::scalar(nType) && !memory_type::isClass(nType) &&
             (
             // left no array, right scalar
                (b1 && !b2 && a_left.var.use.count == 0 && a_right.var.use.count == 9999) 
             || (b1 && !b2 && a_left.var.use.count > 0 && a_right.var.use.count == 0) 
             || (b1 && !b2 && a_left.var.use.count == 0 && a_right.var.use.count > 0)

             || (b2 && a_left.element.use.count > 0 && a_right.element.use.count == 0) 
             || (b2 && a_left.element.use.count == 0 && a_right.element.use.count > 0)

             )
            )
          { semanticError(token__OP_EQUAL, "left array, right non array assignment"); _ERROR_ }
       }

			  if (bProducePcode){

         int nNewAdded = p->getPos(); // needed to change all pcode positions of calls of subs
         myModule->changeRegisterCallSub(pp, p, nNewAdded);
         if (my_cache && myPcode != myPcodeAll && my_cache->parserOpened(acCurrentFile)) my_cache->wr_memory_module_changeRegisterCallSub(getCurrentFile(), memory_module_changeRegisterCallSub, pp, p, nNewAdded);

         p->pcodeWritePcode(pp);
         delete pp;
         


		     if (nType == token__ME){
           { semanticError(token__OP_EQUAL, "ME alone cannot be used in assignment on the left"); _ERROR_ }
		     } else if (nType == token__PARENT){
           { semanticError(token__OP_EQUAL, "PARENT alone cannot be used in assignment on the left"); _ERROR_ }
         } else {
      
 				  // the expression is already transformed to pcode, so we only need the assignment pcode
          if (!bProperty && !bProperty2 && !bProperty3){
           if (!bReference){
            
						  if (!myMemory_type->scalar(nIdType)){

               switch (nType){
       					  case pcode__BOOLEAN: p->wr_MOV_BOOLEAN(pcode__MOV_BOOLEAN, nVar, scope); break;

         				  case pcode__QSTRING:
                    p->wr_MOV_QSTRING(pcode__MOV_QSTRING, nVar, scope); break;
         				  case pcode__CSTRING:
                    p->wr_MOV_CSTRING(pcode__MOV_CSTRING, nVar, scope); break;
                    
         				  case pcode__LQSTRING:
                    if (bTerm_RSET){
                      p->wr_MOV_RQSTRING(pcode__MOV_RQSTRING, nVar, scope); break;
                    } else {
                     p->wr_MOV_LQSTRING(pcode__MOV_LQSTRING, nVar, scope, nLStringLen); break;
                    }
         				  case pcode__LCSTRING:
                    if (bTerm_RSET){
                      p->wr_MOV_RCSTRING(pcode__MOV_RCSTRING, nVar, scope); break;
                    } else {
                       p->wr_MOV_LCSTRING(pcode__MOV_LCSTRING, nVar, scope, nLStringLen); break;
                    }

               case pcode__BYTE: p->wr_MOV_BYTE(pcode__MOV_BYTE, nVar, scope); break;
               case pcode__SHORT: p->wr_MOV_INTEGER(pcode__MOV_SHORT, nVar, scope); break;
               case pcode__INTEGER: p->wr_MOV_INTEGER(pcode__MOV_INTEGER, nVar, scope); break;
       					  case pcode__LONG: p->wr_MOV_LONG(pcode__MOV_LONG, nVar, scope); break;

         				  case pcode__SINGLE: p->wr_MOV_SINGLE(pcode__MOV_SINGLE, nVar, scope); break;
               case pcode__DOUBLE: p->wr_MOV_DOUBLE(pcode__MOV_DOUBLE, nVar, scope); break;


								  default: 
                  if (memory_type::isClass(nIdType) || nIdType == pcode__OBJECT){
                    p->wr_MOV(pcode__MOV, nVar, scope); // write pcode
                  } else {
                    // copy user defined type
            		  	  p->wr_MOV_TYPE(pcode__MOV_TYPE, nVar, scope, bAllSize, nLStringLen); break;
                  }
									  break;
     					  }

 						  } else {

                if (nIdType == pcode__LQSTRING){
                    if (bTerm_RSET){
                      p->wr_MOV_RQSTRING(pcode__MOV_RQSTRING, nVar, scope);
                    } else {
                     p->wr_MOV_LQSTRING(pcode__MOV_LQSTRING, nVar, scope, nLStringLen);
                    }
                } else if (nIdType == pcode__LCSTRING){
                    if (bTerm_RSET){
                      p->wr_MOV_RCSTRING(pcode__MOV_RCSTRING, nVar, scope);
                    } else {
                     p->wr_MOV_LCSTRING(pcode__MOV_LCSTRING, nVar, scope, nLStringLen);
                    }

                } else {
							    if (bTerm_LSET){
                     if (nIdType == pcode__QSTRING){
                        p->wr_MOV_QSTRING(pcode__MOV_QSTRING, nVar, scope); 
                     } else {
                        p->wr_MOV_CSTRING(pcode__MOV_CSTRING, nVar, scope); 
                     }
							    } else if (bTerm_RSET){
                    if (nIdType == pcode__QSTRING){
                      p->wr_MOV_RQSTRING(pcode__MOV_RQSTRING, nVar, scope); 
                    } else {
                      p->wr_MOV_RCSTRING(pcode__MOV_RCSTRING, nVar, scope); 
                    }
							    } else {
     				  	    p->wr_MOV(pcode__MOV, nVar, scope); // write pcode                  
							    }
                }
 						  }
              
					  } else {
						  if (bTerm_LSET){
               { semanticError(token__LSET, "LSET cannot be used in assignment with references"); _ERROR_ }
						  } else if (bTerm_RSET){
               { semanticError(token__RSET, "RSET cannot be used in assignment with references"); _ERROR_ }
						  } else {
               // referenzen auch mit offset auf type-elemente erlaubt   					
               p->wr_MOV_IDREFVAL(pcode__MOV_IDREFVAL, nVar, scope, nType, bAllSize, nLStringLen); // write pcode
             }

					  }
         }
        }
				}

				parseInfo(p, "parsed ASSIGNMENT " );

				return true;
			}
		}
	}

	if (bIDENTIFIER && bTerm__){
  	if (!bEXPRESSION){ syntaxError(token__OP_EQUAL, "assignment expression missing"); _ERROR_ }
	}

  const char *acIdentifier;// = "";

		   if (bIDENTIFIER = fID_KEYWORD_OR_BUILTIN(&acIdentifier)){}
	// because the identifier has a suffix $,%,&,#,!, AS <TYPE> is not allowed, already found out
	else if (bIDENTIFIER = fID_STRING(&acIdentifier)){}
  else if (bIDENTIFIER = fID_INTEGER(&acIdentifier)){}
	else if (bIDENTIFIER = fID_LONG(&acIdentifier)){}
	else if (bIDENTIFIER = fID_SINGLE(&acIdentifier)){}
	else if (bIDENTIFIER = fID_DOUBLE(&acIdentifier)){}
	else if (bIDENTIFIER = fID_CURRENCY(&acIdentifier)){}

	if(bIDENTIFIER){
   	if (bTerm__ = parseTerm(token__OP_EQUAL)){
  	  if (bExplicit || isKBASIC()){
        
        if (scope == outofscope){
    		  { semanticError(token__MSC_IDENTIFIER, utility::con(acIdentifier, " is declared, but its scope is PRIVATE or PROTECTED and not PUBLIC") ); _ERROR_ }
        } else {

         // if const then const can not be used in an assignment
         if (fCONST(p, &nVar, &scope)){
    		    { semanticError(token__MSC_IDENTIFIER, "const is not allowed to be used in an assignment on the left side of the =" ); _ERROR_ }
         }

         if (isScopeClass()){
      		  { semanticError(token__MSC_IDENTIFIER, utility::con(acIdentifier, " not declared. Maybe this variable was declared as INSTANCE CLASS variable and not as STATIC CLASS variable. See help for more details") ); _ERROR_ }
         } else {
      		  { semanticError(token__MSC_IDENTIFIER, utility::con(acIdentifier, " not declared. Remember that variable names are case sensitive and that you have to write OPTION OLDBASIC on top of your program for automatic declaration of variables = old style mode. See help for more details") ); _ERROR_ }
         }
        }
      }
    }
  }

	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: DIM
PRINTNAME: Dim
TASK: declares a variable in current scope
SYNTAX: Dim VarName[([Indizes])] [As [New] Typ] [, VarName[([Indizes])] [As [New] Typ]] . . .
DESC: 
CODE:
EXAMPLES: dim.kbasic
CATEGORY: KEYWORD, VARIABLE
SEEALSO: 
LOG: 04-02-2004 implemented
TIP:
*/
/* *
[KBASIC][VB][QBASIC]
NAME: STATIC
PRINTNAME: Static
TASK: STATIC
SYNTAX: STATIC
DESC: STATIC
CODE:
EXAMPLES: static.kbasic
CATEGORY: KEYWORD, VARIABLE
SEEALSO: 
LOG: 04-02-2004 implemented
TIP:
*/
/* *
[KBASIC][VB][QBASIC]
NAME: PUBLIC
PRINTNAME: Public
TASK: PUBLIC
SYNTAX: PUBLIC
DESC: PUBLIC
CODE:
EXAMPLES: public.kbasic
CATEGORY: KEYWORD, VARIABLE
SEEALSO: 
LOG: 04-02-2004 implemented
TIP:
*/
/* *
[KBASIC][VB][QBASIC]
NAME: PRIVATE
PRINTNAME: Private
TASK: PRIVATE
SYNTAX: PRIVATE
DESC: PRIVATE
CODE:
EXAMPLES: private.kbasic
CATEGORY: KEYWORD, VARIABLE
SEEALSO: 
LOG: 04-02-2004 implemented
TIP:
*/
// As Any keyword in vb6 ??
// auch [] ohne index als array deklaration erlauben
//  [VB] WithEvents
// common
// shared, static
bool parser::fDIM(pcode *p)
/*
[QBASIC]
- DIM [SHARED] give you access to variable outside of current function. Is implicitly supported, 
[VB]
[*]
[*]
*/
{
	_BEGIN_

	bool bTerm_PRIVATE = false;
	bool bTerm_PUBLIC = false;
	bool bTerm_GLOBAL = false;
	bool bTerm_STATIC = false;
	bool bTerm_COMMON = false;
	bool bTerm_SHARED = false;

	bool bTerm_DIM = false;
	bool bTerm_REDIM = false;

#ifdef KBDEBUG
  if (stopAtLine(13)){
    int i = 9;
    i++;
  }
#endif

  {
    if (!(bTerm_DIM = parseTerm(token__DIM))){
       if (isVERYOLDBASIC()){ if ((bTerm_COMMON = parseTerm(token__COMMON))); }
       if ((isVERYOLDBASIC() || isOLDBASIC()) && !isScopeLocal()){ if ((bTerm_GLOBAL = parseTerm(token__GLOBAL))); }
       if (isVERYOLDBASIC()){ if ((bTerm_SHARED = parseTerm(token__SHARED))); }
       if ((bTerm_STATIC = parseTerm(token__STATIC))){ 
			    if (isScopeLocal() == false && !isScopeClass()){
				    semanticError(token__STATIC, "STATIC not allowed outside sub/function/method"); _ERROR_
			    }        
       }
       if (bTerm_COMMON || bTerm_SHARED || bTerm_STATIC || bTerm_GLOBAL){ //  common, shared, global bedeutung berprfen
         bTerm_DIM = true;
       }
      } else {
        if (isVERYOLDBASIC()){ if ((bTerm_SHARED = parseTerm(token__SHARED))); }

        if (bTerm_PRIVATE = parseTerm(token__PRIVATE)){
				  if (isScopeLocal()){
					  semanticError(token__PRIVATE, "PRIVATE not allowed inside sub/function/method"); _ERROR_
				  }
				  goto w;
			  }

			  if (bTerm_PUBLIC = parseTerm(token__PUBLIC)){
				  if (isScopeLocal()){
					  semanticError(token__PUBLIC, "PUBLIC not allowed inside sub/function/method"); _ERROR_
				  }
				  goto w;
			  }

			  if (bTerm_GLOBAL = parseTerm(token__GLOBAL)){
				  if (isScopeLocal()){
					  semanticError(token__GLOBAL, "GLOBAL not allowed inside sub/function/method"); _ERROR_
				  }
				  goto w;
			  }
			  
		  }
	  
  }
w:

  if (!bTerm_DIM && !bTerm_GLOBAL && !bTerm_PRIVATE && !bTerm_PUBLIC && !bTerm_STATIC){ /* syntaxError(token__DIM, "DIM, PRIVATE, PUBLIC or STATIC missing"); */ _ERROR_ }

  if (!bSilent && bProducePcode){
    p->wr_SEPARATOR(pcode__SEPARATOR, utility::con("fDIM", getCurrentLine() - 1));
  }

#ifdef KBDEBUG
  if (stopAtLine(99)){
    int i = 9;
    i++;
  }
#endif

	static /**/ bool bIDENTIFIER[parser__MAX_DIM];
	static /**/ bool bTerm__[parser__MAX_DIM];
	static /**/ bool bEXPRESSION[parser__MAX_DIM];
	static /**/ bool bTerm_AS[parser__MAX_DIM];
	static /**/ bool bTYPE[parser__MAX_DIM];
	static /**/ pcode *myArrayPcode[parser__MAX_DIM];
	bool bTerm_COMMA = false;
	static /**/ const char *acIdentifier[parser__MAX_DIM];
	static /**/ const char *acType[parser__MAX_DIM];
  static /**/ int nLStringLen[parser__MAX_DIM];
	static /**/ int nSize[parser__MAX_DIM];
	const char *acCurrentType = 0;

	static /**/ bool bARRAY[parser__MAX_DIM];
	static /**/ t_array a[parser__MAX_DIM];
	static /**/ int nExpressionType[parser__MAX_DIM];
 	static /**/ bool bTerm_NEW[parser__MAX_DIM];


	int nComma = 0;


	bTerm_NEW[nComma] = false;
	bTerm__[nComma] = false;
	bEXPRESSION[nComma] = false;
	bTerm_AS[nComma] = false;
	bTYPE[nComma] = false;
	bARRAY[nComma] = false;

  bool bb = bTerm_STATIC || isScopeDefaultGlobal() && !isScopeLocal();


  pcode pp(p->sCurrentFile.ascii());

	while (true){
    
	 	if (nComma >= parser__MAX_DIM){ internalError("too many DIM in one line"); _ERROR_ }

		  	 if (bIDENTIFIER[nComma] = fID_KEYWORD_OR_BUILTIN(&acIdentifier[nComma])){ acType[nComma] = findType(findType(pcode::pcode_(defaultType(acIdentifier[nComma])))); bTerm_AS[nComma] = false; bTYPE[nComma] = true; }
		// because the identifier has a suffix $,%,&,#,!, AS <TYPE> is not allowed, already found out
		else if (bIDENTIFIER[nComma] = fID_STRING(&acIdentifier[nComma])){ acType[nComma] = findType(findType(pcode::pcode_(pcode__QSTRING))); bTerm_AS[nComma] = true; bTYPE[nComma] = true; }
		else if (bIDENTIFIER[nComma] = fID_INTEGER(&acIdentifier[nComma])){ acType[nComma] = findType(findType(pcode::pcode_(pcode__INTEGER))); bTerm_AS[nComma] = true; bTYPE[nComma] = true; }
		else if (bIDENTIFIER[nComma] = fID_LONG(&acIdentifier[nComma])){ acType[nComma] = findType(findType(pcode::pcode_(pcode__LONG))); bTerm_AS[nComma] = true; bTYPE[nComma] = true; }
		else if (bIDENTIFIER[nComma] = fID_SINGLE(&acIdentifier[nComma])){ acType[nComma] = findType(findType(pcode::pcode_(pcode__SINGLE))); bTerm_AS[nComma] = true; bTYPE[nComma] = true; }
		else if (bIDENTIFIER[nComma] = fID_DOUBLE(&acIdentifier[nComma])){ acType[nComma] = findType(findType(pcode::pcode_(pcode__DOUBLE))); bTerm_AS[nComma] = true; bTYPE[nComma] = true; }
		else if (bIDENTIFIER[nComma] = fID_CURRENCY(&acIdentifier[nComma])){ acType[nComma] = findType(findType(pcode::pcode_(pcode__CURRENCY))); bTerm_AS[nComma] = true; bTYPE[nComma] = true; }

    else if (bIDENTIFIER[nComma] = fID_KEYWORD_OR_BUILTIN(&acIdentifier[nComma])){ acType[nComma] = findType(findType(pcode::pcode_(defaultType(acIdentifier[nComma])))); bTerm_AS[nComma] = false; bTYPE[nComma] = true; }

		if (bIDENTIFIER[nComma]){

      myArrayPcode[nComma] = new pcode(p->sCurrentFile.ascii());
      if (isScopeGlobal()){
			  // globale variable darf nur const array haben
   		  if (bARRAY[nComma] = fREGISTER_ARRAY_CONST(myArrayPcode[nComma], &a[nComma], 0, 0, global)){}
      } else {
   		  if (bARRAY[nComma] = fREGISTER_ARRAY(myArrayPcode[nComma], &a[nComma], 0, 0)){}
      }      
      
      {
        bool b = false;

        bTerm_NEW[nComma] = false;
        nLStringLen[nComma] = 0;


        // assignment erst nach as type, nein beide varianten anbieten
tr:
        bTerm__[nComma] = false;

          if (!bTerm_NEW[nComma]){
          {
				    if (bTerm__[nComma] = parseTerm(token__OP_EQUAL)){
					    if (bARRAY[nComma]){ // array definition
						    {syntaxError(token__DIM, "assignment not allowed for array declaration"); _ERROR_ }
					    } else {
#ifdef KBDEBUG
               if (stopAtLine(67)){
                int i = 9;
                i++;
               }
#endif
               if (bTerm_AS[nComma]){
                 nExpectedType = findType(acType[nComma]);
               } else {
                 nExpectedType = 0;
               }
               if (bEXPRESSION[nComma] = fEXPRESSION(bb ? p : &pp, &nExpressionType[nComma])){}
						    if (bTerm__[nComma] && !bEXPRESSION[nComma]){ syntaxError(token__DIM, "assignment expression missing"); _ERROR_ }
					    }
				    } else {
					    bEXPRESSION[nComma] = false;
				    }
         } 
			  } else {
				  bEXPRESSION[nComma] = false;
			  }
               
#ifdef KBDEBUG
  if (stopAtLine(39)){
    int i = 9;
    i++;
  }
#endif
			  // check for AS, if %, &, !, # or $ is used, AS is not allowed, type already known
			  if (bTerm_AS[nComma] == true && (parseTerm(token__AS))){ syntaxError(token__DIM, "type already known, identifier may not stop with %, &, !, # or $"); _ERROR_ }
			  if (bTerm_AS[nComma] == false){
				  if (bTerm_AS[nComma] = parseTerm(token__AS)){
					  if (bTerm_NEW[nComma] = parseTerm(token__NEW)){}
            if (bARRAY[nComma] && bTerm_NEW[nComma]){
              { syntaxError(token__DIM, "NEW not allowed with array"); _ERROR_ }
            }

					  if (bTYPE[nComma] = fTYPE(&pp, &acType[nComma], bTerm_NEW[nComma], &nLStringLen[nComma])){}
            if (bTerm_AS[nComma] && !bTYPE[nComma]){ 

                if (fID_KEYWORD_OR_BUILTIN(&acIdentifier[0])){

                if (bTerm_NEW[nComma]){
                  semanticError(token__MSC_IDENTIFIER, utility::con("class constructor missing: new", acIdentifier[0], "() is no matching constructor of desired class") ); 
//                  errorRecovering();
                  _ERROR_
                } else {
                  semanticError(token__MSC_IDENTIFIER, utility::con("type name missing: ", acIdentifier[0], " not declared") ); 
                //  errorRecovering();
                  _ERROR_
                }
              } else {          
                syntaxError(token__DIM, "type name missing"); _ERROR_ 
              }
            }
          }                 
        }

        if (b == false && bEXPRESSION[nComma] == false){
          b = true;
          goto tr;
        }

        if (bTerm_NEW[nComma] && bEXPRESSION[nComma]){
          {syntaxError(token__DIM, "assignment not allowed if NEW is used"); _ERROR_ }
        }

        
      }

		  if (bTerm_COMMA = parseTerm(token__SYM_COMMA)){
				nComma++;
			} else {


        {
				  // check the last dimension, must end with  "... AS <TYPE>"
				  if (bIDENTIFIER[nComma] == true){
					  if (!bTYPE[nComma]){
  					  bTYPE[nComma] = true;
  					  bTerm_AS[nComma] = true;
  					  acType[nComma] = pcode::pcode_(nDefaultType); // qbasic: pcode__DOUBLE, vb6: pcode__VARIANT, kbasic: pcode__VARIANT
					  }
				  }
        }

				{

					char acVars[2048];
         sprintf(acVars, "");

					for (int i = nComma; i >= 0; i--){

            // [KBASIC] andere "Dim a, b, c As Double" deklariert 3 double und nicht 2 variant und ein double
            if (isKBASIC()){
						   if (bTYPE[i] == true){
							   acCurrentType = (char *) acType[i];
              } else {
							   acCurrentType = pcode::pcode_(nDefaultType); // qbasic: pcode__DOUBLE, vb6: pcode__VARIANT, kbasic: pcode__VARIANT
						   }
            } else {
						   if (bTYPE[i] == true){
							   acCurrentType = (char *) acType[i];
              } else {
							   acCurrentType = pcode::pcode_(nDefaultType); // qbasic: pcode__DOUBLE, vb6: pcode__VARIANT, kbasic: pcode__VARIANT
              }
            }            
/*
            if (strcmp(acCurrentType, "Form") == 0) {
              acCurrentType = acCurrentType;
            }*/

	  		  	int nTypes = findType(acCurrentType);
						if (nTypes == 0){ semanticError(token__DIM, utility::con(acCurrentType, " type not defined") ); _ERROR_ }
/*
            switch(nTypes){
              case pcode___strings:
                if (bARRAY[i]){
                  { semanticError(token__DIM, "type must not be declared with an array"); _ERROR_ }
                }
                break;
            }
            */
/*

            if (nTypes == 100001){
              nTypes = nTypes;
            }*/
						if (bEXPRESSION[i]) if (!compatibleType(nTypes, nExpressionType[i])){ semanticError(token__DIM, "incompatible types in assignment"); _ERROR_ }
#ifdef KBDEBUG
           if (stopAtLine(95)){
             int i = 9;
             i++;
           }
#endif

           bool bTerm_STATIC2 = false;
 
           
           // check if it is variant, but no array has been declared by the user, 
           // so that we must implicitly declare an array
            if (bARRAY[i] == false && nTypes == pcode__VARIANT){
              p->wr_PUSH_INTEGER(pcode__PUSH_INTEGER, 0);
              p->wr_PUSH_INTEGER(pcode__PUSH_INTEGER, 10);
              p->wr_PUSH_BOOLEAN(pcode__PUSH_BOOLEAN, true);

              bARRAY[i] = true;
              
	            if (bProducePcode){
 		            p->wr_REGISTER_ARRAY(pcode__REGISTER_ARRAY, 1, 0, 0, getScopeCode(), true, nBaseOfArray); // write pcode	      
              }
            }

           int nSpecialId = 0;

           if (utility::my_stricmp(acIdentifier[i], "kbForm") == 0){
              nSpecialId = pcode___form;
           } else if (utility::my_stricmp(acIdentifier[i], "kbMenuBar") == 0){
              nSpecialId = pcode___menubar;
           } else if (utility::my_stricmp(acIdentifier[i], "kbToolBar") == 0){
              nSpecialId = pcode___toolbar;
           } else if (utility::my_stricmp(acIdentifier[i], "kbEvent") == 0){
              nSpecialId = pcode___event;
           } 

           int nParentType = myClass->getParentId(nTypes);

           bool bGlobalForm = myClass->getParentId(nTypes) == pcode___form;
           bool bGlobal = bGlobalForm || nTypes == pcode___toolbaritem || nTypes == pcode___menubaritem || nTypes == pcode___err;

           if (bGlobal){ // make the id of the global variable in default.kbasic unique, needed due to caching

             nGlobalVarId = MAX_SKALAR_GLOBALVAR_ID;

             XString s = acIdentifier[i];
             s = s.upper();

             int y = 0;
             int l = strlen(s.ascii());
             for (; y < l; y++){
               nGlobalVarId += ((s.at(y)) * (128 *y + 1));
             }

             s = acCurrentType;
             s = s.upper();

             l = strlen(s.ascii());
             for (int y2 = 0; y2 < l; y2++){
               nGlobalVarId += (s.at(y2)) * (128 + y + y2 + 1);
             }

//             nGlobalVarId = nGlobalVarId;

           }

           int nVar = registerVar(acIdentifier[i], nTypes, &a[i], false, bTerm_STATIC/* | bTerm_STATIC2*/, bTerm_PRIVATE ? token__PRIVATE : token__PUBLIC, nLStringLen[i]);
           //nLastVarId = nVar; // needed for rollback

 					  if (nVar == 0){ semanticError(token__DIM, utility::con(utility::ident(getScope(), getSub(), acIdentifier[i]), " already declared at some place") ); _ERROR_ }
 					  //if (nVar == 0){ internalError(utility::con(utility::ident(getScope(), getSub(), acIdentifier[i]), " could not be declared") ); _ERROR_ }

           if (bGlobal){
             nGlobalVarId = 0;
           }

            // for debugging purpose
           // sprintf(acVars, "%s%s%s", acVars, acIdentifier[i], i > 0 ? ", " : "");

						  if (bProducePcode){

               p->pcodeWritePcode(myArrayPcode[i]);
               delete myArrayPcode[i];

               pp.wr_DIM(pcode__DIM, nVar, bTerm_STATIC ? global : getScopeCode(), nTypes, bTerm_NEW[i], false, bARRAY[i], (bTerm_STATIC && isScopeLocal()) || isSubVarStatic(), nLStringLen[i], 
                 nSpecialId, acIdentifier[i], bGlobalForm); // write pcode

               if (bTerm_NEW[i]){
 								  //pp.wr_MOV(pcode__MOV, nVar, getScopeCode()); // write pcode
               } else if (bTerm__[i] && bEXPRESSION[i]){
 								  pp.wr_MOV(pcode__MOV, nVar, getScopeCode()); // write pcode
 							  }


						  }
            

					}

					parseInfo(p,  utility::con("parsed DIM ", acVars) );

          myModule->changeRegisterCallSub(&pp, p, p->getPos());
          if (my_cache && myPcode != myPcodeAll && my_cache->parserOpened(getCurrentFile())) my_cache->wr_memory_module_changeRegisterCallSub(getCurrentFile(), memory_module_changeRegisterCallSub, &pp, p, p->getPos());

		      // add the pp to p
		      // 1. p
		      // 2.pp
		      p->pcodeWritePcode(&pp);

					return true;

				}
				break;
			}
		} else break;
	}

  if (!bIDENTIFIER[0]){ syntaxError(token__DIM, "identifier missing or identifier not declared"); _ERROR_ }

	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: REDIM
PRINTNAME: Redim
TASK: redeclares a variable in current scope
SYNTAX: Redim [PRESERVE] VarName[([Indizes])]
DESC: 
CODE:
EXAMPLES: redim.kbasic
CATEGORY: KEYWORD, VARIABLE
SEEALSO: DIM
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fREDIM(pcode *p)
/*
[QBASIC]
- DIM [SHARED] give you access to variable outside of current function. Is implicitly supported, 
[VB]
[*]
[*]
*/
{
	_BEGIN_

  if (!parseTerm(token__REDIM)){ _END_ }

	bool bTerm_SHARED = false;

  if (isVERYOLDBASIC()) if ((bTerm_SHARED = parseTerm(token__SHARED))){}
	if (!isScopeLocal()){ semanticError(token__REDIM, "REDIM can only be used inside sub/function/method"); _ERROR_ }

  if (!bSilent && bProducePcode){
    p->wr_SEPARATOR(pcode__SEPARATOR, utility::con("fREDIM", getCurrentLine() - 1));
  }

  bool bTerm_PRESERVE;	if (bTerm_PRESERVE = parseTerm(token__PRESERVE)){}

  int nVar;
  t_scope scope;

  const char *acModule = "";
  const char *acSub = "";
  const char *acName = "";

  if (!fVARIABLE_REDIM(p, &nVar, &scope)){ 
     
    findVar(nVar, &acModule, &acSub, &acName);
       
    semanticError(token__REDIM, utility::con(utility::ident(getScope(), getSub(), acName), " not declared") ); _ERROR_ 
  }
/*
  if (scope != local){ 

    findVar(nVar, &acModule, &acSub, &acName);
       
    semanticError(token__REDIM, utility::con(utility::ident(getScope(), getSub(), acName), " not local variable") ); _ERROR_ 
  }*/

  if (bProducePcode){         
    p->wr_REDIM(pcode__REDIM, nVar, scope, bTerm_PRESERVE); // write pcode
	}

  parseInfo(p,  "parsed REDIM" );

  return true;

	_END_
}


/* *
[KBASIC][VB][QBASIC]
NAME: ERASE
PRINTNAME: Erase
TASK: ERASE
SYNTAX: ERASE
DESC: ERASE
CODE:
EXAMPLES: erase.kbasic
CATEGORY: KEYWORD, VARIABLE
SEEALSO: CLEAR, DIM, REDIM
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fERASE(pcode *p)
/*
[*]
[VB]
[*]
[*]
*/
{	
  _BEGIN_
	//register bool bTerm_ERASE = false;
  if (!(/*bTerm_ERASE = */parseTerm(token__ERASE))){ _END_ }



	bool bIDENTIFIER;
	bool bTerm_COMMA = false;

	int nVar = 0;
	t_scope scope = global;
	int nType = 0;


	while (true){

	  if (bIDENTIFIER = fVARIABLE(p, &nVar, &scope, &nType)){
		 
      if (nType == token__ME){
        { semanticError(pcode__ERASE, "ERASE not allowed in combination with ME"); _ERROR_ }
		   } else if (nType == token__PARENT){
        { semanticError(pcode__ERASE, "ERASE not allowed in combination with PARENT"); _ERROR_ }
      } else {
      }

			if (bProducePcode){
 				p->wr_ERASE(pcode__ERASE, nVar, scope); // write pcode
			}

		  if (bTerm_COMMA = parseTerm(token__SYM_COMMA)){
				continue;
			} else {
				//parseInfo(p,  utility::con("parsed ERASE", "", "") );
				return true;
			}

		} else break;
	}

  {
	  if (!bIDENTIFIER){ syntaxError(token__ERASE, "identifier missing or identifier not declared"); _ERROR_ }
	}

	_END_
}


/* *
[KBASIC][VB][QBASIC]
NAME: CLEAR
PRINTNAME: Clear
TASK: CLEAR
SYNTAX: CLEAR
DESC: CLEAR
CODE:
EXAMPLES: clear.kbasic
CATEGORY: KEYWORD, VARIABLE
SEEALSO: ERASE
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fCLEAR(pcode *p)
/*
[*]
[VB]
[*]
[*]
*/
{
  _BEGIN_	
	//register bool bTerm_CLEAR = false;
  if (!(/*bTerm_CLEAR = */parseTerm(token__CLEAR))){ _END_ }



	bool bTerm_COMMA = false;
	bool bTerm_COMMA2 = false;
	bool bEXPRESSION = false;

	if (bTerm_COMMA = parseTerm(token__SYM_COMMA))
	if (bTerm_COMMA2 = parseTerm(token__SYM_COMMA))
  if (bEXPRESSION = fINTEGER_EXPRESSION(p)){}

	if ((bTerm_COMMA || bTerm_COMMA2) && !bEXPRESSION){
	  { syntaxError(token__CLEAR, "stack expression missing"); _ERROR_ }
	}

	if (bProducePcode){
 		p->wr_CLEAR(pcode__CLEAR, bEXPRESSION); // write pcode
	}

		//parseInfo(p,  utility::con("parsed CLEAR", "", "") );

	_DONE_

}

/**
[KBASIC][VB][QBASIC]
NAME: STOP
PRINTNAME: Stop
TASK: stops the running program
SYNTAX: STOP
DESC: 
CODE:
EXAMPLES: stop.kbasic
CATEGORY: KEYWORD, CONTROLFLOW, ERROR
SEEALSO: SYSTEM, END
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fSTOP(pcode *p)
/*
[QBASIC]
[VB]
[*]
[*]
*/
{
	_BEGIN_

	//register bool bTerm_STOP = false;

	if (/*bTerm_STOP = */parseTerm(token__STOP)){
		if (bProducePcode){
			p->wr_STOP(pcode__STOP); // write pcode
		}
		parseInfo(p, "parsed STOP");
		return true;
	}

  //return false;
	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: CLASS
PRINTNAME: Class
TASK: Classes are needed, when you would like use objects.
SYNTAX: 
DESC: 
CODE:
EXAMPLES: class.kbasic
CATEGORY: KEYWORD, STRUCTURE
SEEALSO: OBJECT
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
/**
[KBASIC][VB][QBASIC]
NAME: MODULE
PRINTNAME: Module
TASK: Modules are usefull when you would like to organize functions and subs.
SYNTAX: 
DESC: 
CODE:
EXAMPLES: module.kbasic
CATEGORY: KEYWORD, STRUCTURE
SEEALSO: CLASS
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
/**
[KBASIC]
NAME: ENUM
PRINTNAME: Enum
TASK: Is a list of integer constants relating to the same subject
SYNTAX: 
DESC: 
CODE:
EXAMPLES: enum.kbasic
CATEGORY: KEYWORD, STRUCTURE
SEEALSO: CLASS
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
/**
[KBASIC]
NAME: TYPE3
PRINTNAME: Type
TASK: Is a way of storing many variables inside one variable.
SYNTAX: 
DESC: 
CODE:
EXAMPLES: type.kbasic
CATEGORY: KEYWORD, STRUCTURE
SEEALSO: CLASS
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
/**
[KBASIC]
NAME: FUNCTION
PRINTNAME: Function
TASK: Is a part of a program, returning a value depending on calculation inside the function.
SYNTAX: 
DESC: 
CODE:
EXAMPLES: function.kbasic
CATEGORY: KEYWORD, STRUCTURE
SEEALSO: CLASS
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
/**
[KBASIC]
NAME: SUB
PRINTNAME: Sub
TASK: Is a part of your program containing commands.
SYNTAX: 
DESC: 
CODE:
EXAMPLES: sub.kbasic
CATEGORY: KEYWORD, STRUCTURE
SEEALSO: CLASS
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
/**
[KBASIC]
NAME: CONSTRUCTOR
PRINTNAME: Constructor
TASK: Constructs an object
SYNTAX: 
DESC: 
CODE:
EXAMPLES: constructor.kbasic
CATEGORY: KEYWORD, STRUCTURE
SEEALSO: CLASS
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
/**
[KBASIC]
NAME: DESTRUCTOR
PRINTNAME: Destructor
TASK: Destructs an object.
SYNTAX: 
DESC: 
CODE:
EXAMPLES: destructor.kbasic
CATEGORY: KEYWORD, STRUCTURE
SEEALSO: CLASS
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
/**
[KBASIC]
NAME: PROPERTY
PRINTNAME: Property
TASK: 
SYNTAX: 
DESC: 
CODE:
EXAMPLES: property.kbasic
CATEGORY: KEYWORD, STRUCTURE
SEEALSO: CLASS
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/

/* *
[KBASIC][VB][QBASIC]
NAME: END SELECT
PRINTNAME: End Select
TASK: END SELECT
SYNTAX: END SELECT
DESC: END SELECT
CODE:
EXAMPLES: endselect.kbasic
CATEGORY: KEYWORD, CONTROLFLOW
SEEALSO: SELECTCASE
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
/* *
[KBASIC][VB][QBASIC]
NAME: END IF
PRINTNAME: End If
TASK: END IF
SYNTAX: END IF
DESC: END IF
CODE:
EXAMPLES: endif.kbasic
CATEGORY: KEYWORD, CONTROLFLOW
SEEALSO: IF
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
/* *
[KBASIC][VB][QBASIC]
NAME: END FUNCTION
PRINTNAME: End Function
TASK: END FUNCTION
SYNTAX: END FUNCTION
DESC: END FUNCTION
CODE:
EXAMPLES: endfunction.kbasic
CATEGORY: KEYWORD, CONTROLFLOW
SEEALSO: FUNCTION
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
/* *
[KBASIC][VB][QBASIC]
NAME: END SUB
PRINTNAME: End Sub
TASK: END SUB
SYNTAX: END SUB
DESC: END SUB
CODE:
EXAMPLES: endsub.kbasic
CATEGORY: KEYWORD, CONTROLFLOW
SEEALSO: SUB
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
/* *
[KBASIC][VB][QBASIC]
NAME: END TYPE
PRINTNAME: End Type
TASK: END TYPE
SYNTAX: END TYPE
DESC: END TYPE
CODE:
EXAMPLES: endtype.kbasic
CATEGORY: KEYWORD, VARIABLE, STRUCTURE
SEEALSO: TYPE
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
/* *
[KBASIC][VB][QBASIC]
NAME: END CATCH
PRINTNAME: End Catch
TASK: END CATCH
SYNTAX: END CATCH
DESC: END CATCH
CODE:
EXAMPLES: endcatch.kbasic
CATEGORY: KEYWORD, CONTROLFLOW
SEEALSO: TRY
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
/* *
[KBASIC][VB][QBASIC]
NAME: END MODULE
PRINTNAME: End Module
TASK: END MODULE
SYNTAX: END MODULE
DESC: END MODULE
CODE:
EXAMPLES: endmodule.kbasic
CATEGORY: KEYWORD
SEEALSO: MODULE
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
/* *
[KBASIC][VB][QBASIC]
NAME: END CLASS
PRINTNAME: End Class
TASK: END CLASS
SYNTAX: END CLASS
DESC: END CLASS
CODE:
EXAMPLES: endclass.kbasic
CATEGORY: KEYWORD
SEEALSO: CLASS
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
/* *
[KBASIC][VB][QBASIC]
NAME: END DEF
PRINTNAME: End Def
TASK: END DEF
SYNTAX: END DEF
DESC: END DEF
CODE:
EXAMPLES: enddef.kbasic
CATEGORY: KEYWORD, VARIABLE, STRUCTURE
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
/* *
[KBASIC][VB][QBASIC]
NAME: END PROPERTY
PRINTNAME: End Property
TASK: END PROPERTY
SYNTAX: END PROPERTY
DESC: END PROPERTY
CODE:
EXAMPLES: endproperty.kbasic
CATEGORY: KEYWORD, VARIABLE, STRUCTURE
SEEALSO: PROPERTY
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
/* *
[KBASIC][VB][QBASIC]
NAME: END WITH
PRINTNAME: End With
TASK: END WITH
SYNTAX: END WITH
DESC: END WITH
CODE:
EXAMPLES: endwith.kbasic
CATEGORY: KEYWORD, VARIABLE, STRUCTURE
SEEALSO: WITH
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
/* *
[KBASIC][VB][QBASIC]
NAME: END ENUM
PRINTNAME: End Enum
TASK: END ENUM
SYNTAX: END ENUM
DESC: END ENUM
CODE:
EXAMPLES: endenum.kbasic
CATEGORY: KEYWORD, CONST, STRUCTURE
SEEALSO: ENUM
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
/* *
[KBASIC][VB][QBASIC]
NAME: END STRUCTURE
PRINTNAME: End Structure
TASK: END STRUCTURE
SYNTAX: END STRUCTURE
DESC: END STRUCTURE
CODE:
EXAMPLES: endstructure.kbasic
CATEGORY: KEYWORD, VARIABLE, STRUCTURE
SEEALSO: STRUCTURE
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
/* *
[KBASIC][VB][QBASIC]
NAME: END CONSTRUCTOR
PRINTNAME: End Constructor
TASK: END CONSTRUCTOR
SYNTAX: END CONSTRUCTOR
DESC: END CONSTRUCTOR
CODE:
EXAMPLES: endconstructure.kbasic
CATEGORY: KEYWORD, CLASS, STRUCTURE
SEEALSO: CONSTRUCTOR
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
/* *
[KBASIC][VB][QBASIC]
NAME: END DESTRUCTOR
PRINTNAME: End Destructor
TASK: END DESTRUCTOR
SYNTAX: END DESTRUCTOR
DESC: END DESTRUCTOR
CODE:
EXAMPLES: enddestructor.kbasic
CATEGORY: KEYWORD, CLASS, STRUCTURE
SEEALSO: DESTRUCTOR
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
/* *
[KBASIC][VB][QBASIC]
NAME: END SLOT
PRINTNAME: End Slot
TASK: END SLOT
SYNTAX: END SLOT
DESC: END SLOT
CODE:
EXAMPLES: endslot.kbasic
CATEGORY: KEYWORD, EVENT, STRUCTURE
SEEALSO: SLOT
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
/* *
[KBASIC][VB][QBASIC]
NAME: END SIGNAL
PRINTNAME: End Signal
TASK: END SIGNAL
SYNTAX: END SIGNAL
DESC: END SIGNAL
CODE:
EXAMPLES: endsignal.kbasic
CATEGORY: KEYWORD, EVENT, STRUCTURE
SEEALSO: SIGNAL
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fEND(pcode *p)
{
	_BEGIN_

	//register bool bTerm_END = false;
	//register bool b = false;

	if (/*bTerm_END = */parseTerm(token__END)){


  register int n = peekToken();

  if (
     n == token__IF
  || n == token__FUNCTION
  || n == token__SUB
  || n == token__SELECT
  || n == token__TYPE
  || n == token__CATCH
  || n == token__MODULE
  || n == token__CLASS
  || n == token__PROPERTY
  || n == token__WITH
  || n == token__ENUM
  || n == token__STRUCTURE
  || n == token__CONSTRUCTOR
  || n == token__DESTRUCTOR
  || n == token__SLOT
  || n == token__SIGNAL
  || n == token__GET
  || n == token__SET
  || n == token__STATIC
  || n == token__DEF
  || n == token__WHILE
  ) _END_; 

    if (bProducePcode){
     p->wr_END(pcode__END); // write pcode
		}
		parseInfo(p, "parsed END");
		return true;
	}

	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: END
PRINTNAME: End
TASK: ends the execution of a program immediately
SYNTAX: END
DESC:
CODE:
EXAMPLES: end.kbasic
CATEGORY: KEYWORD, CONTROLFLOW, ERROR
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::f_END(pcode *p)
{
	_BEGIN_

	//register bool bTerm__END = false;

	if (/*bTerm__END = */parseTerm(token___END)){

		if (bProducePcode){
			p->wr_END(pcode__END); // write pcode
		}
		bParseToken = false; // immediately stop the parser
		parseInfo(p, "parsed $END");
		return true;
	}

	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: SYSTEM
PRINTNAME: System
TASK: exit program and returns to system
SYNTAX: SYSTEM
DESC:
CODE:
EXAMPLES: system.kbasic
CATEGORY: KEYWORD, CONTROLFLOW
SEEALSO: END, STOP
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fSYSTEM(pcode *p)
/*
[QBASIC]
[*]
[*]
[*]
*/
{
	_BEGIN_

	//register bool bTerm_SYSTEM = false;

	if (/*bTerm_SYSTEM = */parseTerm(token__SYSTEM)){

		if (bProducePcode){
			p->wr_SYSTEM(pcode__SYSTEM); // write pcode
		}
		bParseToken = false; // immediately stop the parser
		parseInfo(p, "parsed SYSTEM");
		return true;
	}

  //return false;
	_END_
}

// for qbasic and dll support
bool parser::fDECLARE()
{
	_TBEGIN_

  if (parseTerm(token__PRIVATE)){}
  else if (parseTerm(token__PUBLIC)){}

  if (parseTerm(token__DECLARE)){

    // the declare statement has already been read, skip it for the second of compilation
  	while(proceedParse() && peekToken() != token__MSC_EOL && nextToken());
    _TDONE_

	}

	_TEND_
}


/**
[KBASIC][VB][QBASIC]
NAME: OPTION
PRINTNAME: Option
TASK: OPTION is used in many statements.
SYNTAX: 
DESC: 
CODE:
EXAMPLES: option.kbasic
CATEGORY: KEYWORD
SEEALSO: OPTION BASE, OPTION EXPLICIT, OPTION COMPARE, OPTION VERYOLDBASIC, OPTION OLDBASIC, OPTION KBASIC
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fOPTION(pcode *p)
{

	//register bool bTerm_OPTION = false;

  _TBEGIN_

  if (/*bTerm_OPTION = */parseTerm(token__OPTION)){

    bool bTerm_RANGE = false;
    bool bTerm_EXPLICIT = false;
    bool bTerm_BASE = false;
    bool bTerm_COMPARE = false;
    bool bTerm_VERYOLDBASIC = false;
    bool bTerm_KBASIC = false;
    bool bTerm_OLDBASIC = false;  
    bool bTerm_ON = false;
    bool bTerm_OFF = false;
    bool bTerm_BINARY = false;
    bool bTerm_TEXT = false;
    bool bTerm_PRIVATE = false;
    bool bTerm_MODULE = false;
    bool bTerm_DATABASE = false;

    bool bINTEGER = false;
    int nInteger = 0;
/* *
[VB]
NAME: OPTION RANGE
PRINTNAME: Option Range
TASK: overflow checking at runtime
SYNTAX: OPTION RANGE {ON | OFF}
DESC:
EXAMPLES: option.kbasic
CATEGORY: KEYWORD
SEEALSO:
VERSION: PERSONAL, PROFESSIONAL
LOG:
TIP:
*/
	  if ((bTerm_RANGE = parseTerm(token__RANGE))){ // overflow checking at runtime
      if (isKBASIC()){ syntaxError(token__RANGE, "OPTION RANGE not supported inside OPTION KBASIC"); _ERROR_ }
      if ((bTerm_ON = parseTerm(token__ON)) || (bTerm_OFF = parseTerm(token__OFF))){}
      if (!bTerm_ON && !bTerm_OFF){ syntaxError(token__RANGE, "ON or OFF missing"); _ERROR_ }

			if (p && bProducePcode){

				//p->wr_OPTION_RANGE(pcode__OPTION_RANGE, bTerm_ON ? 1 : 0); // set under/overflow range check off
			}

			parseInfo(p, "parsed OPTION RANGE");
			return true;

		} else  if ((bTerm_EXPLICIT = parseTerm(token__EXPLICIT))){ // [VB]
/**
[VB]
NAME: OPTIONEXPLICIT
PRINTNAME: Option Explicit
TASK: Forces to declare your variables inside the module.
SYNTAX: OPTION EXPLICIT {ON | OFF}
DESC:
EXAMPLES: option.kbasic
CATEGORY: KEYWORD
SEEALSO:
LOG:
TIP: You should always declare your variables, because error tracking will be easier.
*/
      if (isVERYOLDBASIC()){ syntaxError(token__OPTION, "OPTION EXPLICIT not supported inside OPTION VERYOLDBASIC"); _ERROR_ }
      if (isKBASIC()){ syntaxError(token__OPTION, "OPTION EXPLICIT not supported inside OPTION KBASIC (which is default)"); _ERROR_ }
      if ((bTerm_ON = parseTerm(token__ON)) || (bTerm_OFF = parseTerm(token__OFF))){}
      if (!bTerm_ON && !bTerm_OFF){ syntaxError(token__OPTION, "ON or OFF missing"); _ERROR_ }

			if (p && bProducePcode){

        setExplicit(bTerm_ON); // set declare explicit on/off
			}

			parseInfo(p, "parsed OPTION EXPLICIT");
			return true;

		} else if ((bTerm_OLDBASIC = parseTerm(token__OLDBASIC))){
/**
[QBASIC][VB][KBASIC]
NAME: OPTIONOLDBASIC
PRINTNAME: Option OldBasic
TASK: Switches into old basic compatibility mode.
SYNTAX: OPTION OLDBASIC
DESC:
EXAMPLES: option.kbasic
CATEGORY: KEYWORD
SEEALSO: OPTION VERYOLDBASIC, OPTION KBASIC
VERSION: PERSONAL, PROFESSIONAL
LOG:
TIP:
*/

			setOLDBASIC();
			if (p && bProducePcode){
			}

			parseInfo(p, "parsed OPTION OLDBASIC");
			return true;
		} else if ((bTerm_VERYOLDBASIC = parseTerm(token__VERYOLDBASIC))){
/**
[QBASIC][VB][KBASIC]
NAME: OPTIONVERYOLDBASIC
PRINTNAME: Option VeryOldBasic
TASK: Switches into very old basic compatibility mode.
SYNTAX: OPTION VERYOLDBASIC
DESC:
EXAMPLES: option.kbasic
CATEGORY: KEYWORD
SEEALSO: OPTION OLDBASIC, OPTION KBASIC
VERSION: PERSONAL, PROFESSIONAL
LOG:
TIP:
*/

			setVERYOLDBASIC();
			if (p && bProducePcode){
			}

			parseInfo(p, "parsed OPTION VERYOLDBASIC");
			return true;

		} else if ((bTerm_KBASIC = parseTerm(token__KBASIC))){
/**
[QBASIC][VB][KBASIC]
NAME: OPTIONKBASIC
PRINTNAME: Option KBasic
TASK: Switches into KBasic mode.
SYNTAX: OPTION KBASIC
DESC:
EXAMPLES: option.kbasic
CATEGORY: KEYWORD
SEEALSO: OPTION OLDBASIC, OPTION VERYOLDBASIC
VERSION: PERSONAL, PROFESSIONAL
LOG:
TIP: You should always use this mode, because in future versions older BASIC's like qbasic or vb may not be supported.
*/

			setKBASIC();
			if (p == myPcode && bProducePcode){
        p->wr_OPTION_KBASIC(pcode__OPTION_KBASIC);
			}

			parseInfo(p, "parsed OPTION KBASIC");
			return true;

		} else if ((bTerm_COMPARE = parseTerm(token__COMPARE))){ // [VB]
/**
[VB]
NAME: OPTIONCOMPARE
PRINTNAME: Option Compare
TASK: Set the default comparision mode.
SYNTAX: OPTION COMPARE BINARY
DESC:
EXAMPLES: option.kbasic
CATEGORY: KEYWORD
SEEALSO:
VERSION: PERSONAL, PROFESSIONAL
LOG:
TIP:
*/      
      if (isVERYOLDBASIC()){ syntaxError(token__OPTION, "OPTION COMPARE not supported inside OPTION VERYOLDBASIC"); _ERROR_ }
      if (isKBASIC()){ syntaxError(token__OPTION, "OPTION COMPARE not supported inside OPTION KBASIC"); _ERROR_ }
      if ((bTerm_BINARY = parseTerm(token__BINARY)) || (bTerm_TEXT = parseTerm(token__TEXT)) || (bTerm_DATABASE = parseTerm(token__DATABASE))){}
      if (bTerm_DATABASE){ syntaxError(token__OPTION, "OPTION COMPARE DATABASE is not supported"); _ERROR_ }
      if (!bTerm_BINARY && !bTerm_TEXT){ syntaxError(token__OPTION, "BINARY or TEXT missing"); _ERROR_ }

      bOptionCompareBinary = bTerm_BINARY;

			if (bProducePcode){

				//p->wr_OPTION_COMPARE(pcode__OPTION_COMPARE, bTerm_BINARY);

			}

			parseInfo(p, "parsed OPTION COMPARE");
			return true;

		} else if (bTerm_BASE = parseTerm(token__BASE)){ // [QBASIC] [VB]
/**
[QBASIC][VB]
NAME: OPTIONBASE
PRINTNAME: Option Base
TASK: Set default lower bound of arrays.
SYNTAX: OPTION BASE {0 | 1}
DESC: Set default lower bound of arrays. OPTION BASE has no effect on ARRAY or PARAMARRAY. OPTION RANGE takes effect only on the current module in which it is written.
EXAMPLES: option.kbasic
CATEGORY: KEYWORD
SEEALSO: DIM, REDIM, STATIC, PUBLIC, PRIVATE, LBOUND, UBOUND, ARRAY, PARAMARRY
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP: Better us TO when using DIM. For example: Dim i As Integer(10 To 100)
*/
      if (isKBASIC()){ syntaxError(token__OPTION, "OPTION BASE not supported inside OPTION KBASIC"); _ERROR_ }
      if (bINTEGER = fINTEGER(&nInteger)){

			  if (!(nInteger == 0 || nInteger == 1)){ semanticError(token__OPTION, "number 0 or 1 is only allowed for OPTION BASE"); _ERROR_ } // [QBASIC]

        nBaseOfArray = nInteger;

        if (bProducePcode){

				  //p->wr_OPTION_BASE(pcode__OPTION_BASE, nBaseOfArray);

			  }

			  parseInfo(p, "parsed OPTION BASE");
			  return true;
      }

      if (bTerm_BASE && !bINTEGER){ syntaxError(token__OPTION, "INTEGER missing"); _ERROR_ }

		} else if (bTerm_PRIVATE = parseTerm(token__PRIVATE)){ //  [VB] [VBNET]
		  if (bTerm_MODULE = parseTerm(token__MODULE)){
        { syntaxError(token__OPTION, "OPTION PRIVATE MODULE is not supported"); _ERROR_ }
      } else {
        { syntaxError(token__OPTION, "OPTION PRIVATE is not supported"); _ERROR_ }
      }
    }

    { syntaxError(token__OPTION, "EXPLICIT, COMPARE, BASE, VERYOLDBASIC, OLDBASIC or KBASIC missing"); _ERROR_ }

    _TEND_

	}

  _TEND_
	
}

bool parser::fDEFLNG(){	return fDEF(pcode__LONG); }
bool parser::fDEFSNG(){	return fDEF(pcode__SINGLE); }
bool parser::fDEFDBL(){	return fDEF(pcode__DOUBLE); }
bool parser::fDEFSTR(){	return fDEF(pcode__CSTRING); }
bool parser::fDEFINT(){	return fDEF(pcode__INTEGER); }

bool parser::fDEFCUR(){	return fDEF(pcode__CURRENCY); }
bool parser::fDEFVAR(){	return fDEF(pcode__VARIANT); }
bool parser::fDEFBOOL(){	return fDEF(pcode__BOOLEAN); }
bool parser::fDEFBYTE(){	return fDEF(pcode__BYTE); }
bool parser::fDEFDATE(){	return fDEF(pcode__DATE); }
bool parser::fDEFOBJ(){	return fDEF(pcode__OBJECT); }

/*
*/
/* *
[QBASIC][VB]
NAME: DEFINT, DEFLNG, DEFSNG, DEFDBL, DEFSTR, DEFCUR, DEFVAR, DEFBOOL, DEFBYTE, DEFDATE
PRINTNAME: DefInt, DefLng, DefSng, DefDbl, DefStr, DefCur, DefVar, DefBool, DefByte, DefDate
TASK: Set default type for variables depending on their first letter.
SYNTAX: 
DESC: 

examples:
DEFINT A-M
DEFLNG B, m, k
DEFSNG C
DEFDBL D
DEFSTR z

EXAMPLES: option.kbasic
CATEGORY: KEYWORD, VARIABLE
SEEALSO:
LOG: 05-02-2005 implemented
TIP:
*/
bool parser::fDEF(int nDefType)
/*
[QBASIC]
Ein Datentyp-Suffix (%, &, !, #, or $) hat immer Vorrang vor einer
DEFtype-Anweisung.
Der Standard-Datentyp ist Einfache Genauigkeit, falls  Sie keine andere
DEFtype-Anweisung angeben.
[*]
[!VBNET]
[!KBASIC]
*/
{
	_TBEGIN_

	register bool bTerm_DEF = false;

	switch(nDefType){
		case pcode__INTEGER:
			if (!(bTerm_DEF = parseTerm(token__DEFINT))){ _TEND_ } // [QBASIC][VB][!VBNET][!KBASIC]
 			break;
		case pcode__LONG:
			if (!(bTerm_DEF = parseTerm(token__DEFLNG))){ _TEND_ } // [QBASIC][VB][!VBNET][!KBASIC]
 			break;
		case pcode__SINGLE:
			if (!(bTerm_DEF = parseTerm(token__DEFSNG))){ _TEND_ } // [QBASIC][VB][!VBNET][!KBASIC]
 			break;
		case pcode__DOUBLE:
			if (!(bTerm_DEF = parseTerm(token__DEFDBL))){ _TEND_ } // [QBASIC][VB][!VBNET][!KBASIC]
 			break;
		case pcode__CSTRING:
			if (!(bTerm_DEF = parseTerm(token__DEFSTR))){ _TEND_ } // [QBASIC][VB][!VBNET][!KBASIC]
 			break;
		case pcode__CURRENCY:
			if (!(bTerm_DEF = parseTerm(token__DEFCUR))){ _TEND_ } // [!QBASIC][VB][!VBNET][!KBASIC]
 			break;
		case pcode__VARIANT:
			if (!(bTerm_DEF = parseTerm(token__DEFVAR))){ _TEND_ } // [!QBASIC][VB][!VBNET][!KBASIC]
 			break;
		case pcode__BOOLEAN:
			if (!(bTerm_DEF = parseTerm(token__DEFBOOL))){ _TEND_ } // [!QBASIC][VB][!VBNET][!KBASIC]
 			break;
		case pcode__BYTE:
			if (!(bTerm_DEF = parseTerm(token__DEFBYTE))){ _TEND_ } // [!QBASIC][VB][!VBNET][!KBASIC]
 			break;
		case pcode__DATE:
			if (!(bTerm_DEF = parseTerm(token__DEFDATE))){ _TEND_ } // [!QBASIC][*][!VBNET][!KBASIC]
 			break;
		case pcode__OBJECT:
			if (!(bTerm_DEF = parseTerm(token__DEFOBJ))){ _TEND_ } // [!QBASIC][VB][!VBNET][!KBASIC]
 			break;

	}

  if (!bTerm_DEF){ _TEND_  }

  if (isKBASIC()){ syntaxError(token__DEFINT, "not supported inside OPTION KBASIC"); _ERROR_ }

	bool bEOL = false;
	bool bREM = false;
	bool bTerm_COMMA = false;
	bool bTerm_OP_SUB = false;

	bool bIDENTIFIER[parser__MAX_DEF];
	const char *acIdentifier[parser__MAX_DEF];
	bool bIDENTIFIER2[parser__MAX_DEF];
	const char *acIdentifier2[parser__MAX_DEF];

	int nComma = 0;

	while (true){

	 	if (nComma >= parser__MAX_DEF){ internalError("too many DEF in one line"); _ERROR_ }

	 	if (!(bIDENTIFIER[nComma] = fID_KEYWORD_OR_BUILTIN(&acIdentifier[nComma]))){ syntaxError(token__DEF, "character missing"); _ERROR_ }

 		if (bTerm_OP_SUB = parseTerm(token__OP_SUB)){
		 	if (!(bIDENTIFIER2[nComma] = fID_KEYWORD_OR_BUILTIN(&acIdentifier2[nComma]))){ syntaxError(token__DEF, "character missing"); _ERROR_ }
		} else {
			bIDENTIFIER2[nComma] = false;
		}

	  if (bTerm_COMMA = parseTerm(token__SYM_COMMA)){
			nComma++;
		} else {

    	if (bEOL = fEOLREM()){

 				for (int i = 0; i <= nComma; i++){

          if (bIDENTIFIER[i]){
  					char c = toupper(acIdentifier[i][0]) - 'A';
					 	if (c >= 26){ semanticError(token__DEF, "invalid character, must be A - Z"); _ERROR_ }

  	        if (bIDENTIFIER2[i]){
  						char c2 = toupper(acIdentifier2[i][0]) - 'A';
						 	if (c2 >= 26){ semanticError(token__DEF, "invalid character, must be A - Z"); _ERROR_ }
            	for (int z = (c < c2 ? c : c2); z < (c < c2 ? c2 : c); z++){
            		nDEF[z] = nDefType;
            	}
  					} else {
          		nDEF[c] = nDefType;
  					}
   				}
				}

				switch(nDefType){
					case pcode__INTEGER:
						parseInfo(0, "parsed DEFINT");
		   			return true;
					case pcode__LONG:
						parseInfo(0, "parsed DEFLNG");
		   			return true;
					case pcode__SINGLE:
						parseInfo(0, "parsed DEFSNG");
		   			return true;
					case pcode__DOUBLE:
						parseInfo(0, "parsed DEFDBL");
		   			return true;
					case pcode__CSTRING:
						parseInfo(0, "parsed DEFSTR");
		   			return true;
					case pcode__CURRENCY:
						parseInfo(0, "parsed DEFCUR");
		   			return true;
					case pcode__VARIANT:
						parseInfo(0, "parsed DEFVAR");
		   			return true;
					case pcode__BOOLEAN:
						parseInfo(0, "parsed DEFBOOL");
		   			return true;
					case pcode__BYTE:
						parseInfo(0, "parsed DEFBYTE");
		   			return true;
					case pcode__DATE:
						parseInfo(0, "parsed DEFDATE");
		   			return true;
					case pcode__OBJECT:
						parseInfo(0, "parsed DEFOBJ");
		   			return true;

				}
    	}

  		if (!bEOL){ syntaxError(token__DEF, "EOL missing"); _ERROR_ }

		}

	}

	_TEND_
}

/**
[QBASIC]
NAME: DATA
PRINTNAME: Data
TASK: represents data inside your program, old style of static arrays
SYNTAX: 
DESC: 
EXAMPLES: data.kbasic
CATEGORY: KEYWORD, VARIABLE
SEEALSO: READ, RESTORE
VERSION: PERSONAL, PROFESSIONAL
LOG: 05-02-2005 implemented
TIP:
*/
bool parser::fDATA(pcode *p)
{

	//register bool bTerm_DATA = false;

 	_BEGIN_
  if (!(/*bTerm_DATA = */parseTerm(token__DATA))){ _END_ }


  if (!bSilent && bProducePcode){
    p->wr_SEPARATOR(pcode__SEPARATOR, utility::con("fDATA", getCurrentLine() - 1));
  }

	bool bTerm_COMMA = false;

	bool bINTEGER[parser__MAX_DATA]; int nInteger[parser__MAX_DATA];
	bool bLONG[parser__MAX_DATA]; t_long lLongInteger[parser__MAX_DATA];
	bool bDOUBLE[parser__MAX_DATA]; double dNumeric[parser__MAX_DATA];
	bool bSINGLE[parser__MAX_DATA]; float fNumeric[parser__MAX_DATA];
	bool bBOOLEAN[parser__MAX_DATA]; t_boolean bBoolean[parser__MAX_DATA];
	bool bSTRING[parser__MAX_DATA]; const char *acString[parser__MAX_DATA];
	int nType[parser__MAX_DATA];
	nType[0] = 0;

	int nComma = 0;


	while (true){

	 	if (nComma >= parser__MAX_DATA){ internalError("too many DATA in one line"); _ERROR_ }

   			 if (bINTEGER[nComma] = fINTEGER(&nInteger[nComma])) nType[nComma] = pcode__INTEGER;
  	else if (bLONG[nComma] = fLONG(&lLongInteger[nComma])) nType[nComma] = pcode__LONG;
  	else if (bDOUBLE[nComma] = fDOUBLE(&dNumeric[nComma])) nType[nComma] = pcode__DOUBLE;
  	else if (bSINGLE[nComma] = fSINGLE(&fNumeric[nComma])) nType[nComma] = pcode__SINGLE;
  	else if (bBOOLEAN[nComma] = fBOOLEAN(&bBoolean[nComma])) nType[nComma] = pcode__BOOLEAN;
  	else if (bSTRING[nComma] = fSTRING(&acString[nComma], true)) nType[nComma] = pcode__CSTRING;
		else { syntaxError(token__DATA, "const expression missing"); _ERROR_ }

	  if (bTerm_COMMA = parseTerm(token__SYM_COMMA)){
			nComma++;
		} else {

			if (nType[0] != 0){

   			if (bProducePcode){

					nDataCount = (nComma + 1);

 				  p->wr_DATA(pcode__DATA, nDataCount);

					for (int i = 0; i < nDataCount; i++){

						switch(nType[i]){

							case pcode__INTEGER: p->wr_INTEGER(nInteger[i]); break;
							case pcode__LONG: p->wr_LONG(lLongInteger[i]); break;
							case pcode__DOUBLE: p->wr_DOUBLE(dNumeric[i]); break;
							case pcode__SINGLE: p->wr_SINGLE(fNumeric[i]); break;
							case pcode__BOOLEAN: p->wr_BOOLEAN(bBoolean[i]); break;
							case pcode__CSTRING: p->wr_CSTRING(acString[i]); break;
						//	case pcode__QSTRING: p->wr_CSTRING(acString[i]); break;
              default:  { syntaxError(token__DATA, "wrong datatype"); _ERROR_ }
						}
					}
   			}

   			parseInfo(p, "parsed DATA");
   			return true;
    	}

  		if (!(nComma > 0)){ syntaxError(token__DATA, "DATA information missing"); _ERROR_ }

		}
	}

	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: RESTORE
PRINTNAME: Restore
TASK: reset position for reading data
SYNTAX: RESTORE
DESC:
CODE:
EXAMPLES: restore.kbasic
CATEGORY: KEYWORD, VARIABLE
SEEALSO: READ, DATA
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fRESTORE(pcode *p)
/*
[QBASIC]
SYNTAX: RESTORE [line]
[*]
[*]
[*]
*/
{
	_BEGIN_

  if (parseTerm(token__RESTORE)){

		if (bProducePcode){
		  p->wr_RESTORE(pcode__RESTORE);
      //    linenr/label:  
		}
		parseInfo(p, "parsed RESTORE");
		return true;

	}

  _END_;
	//_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: READ
PRINTNAME: Read
TASK: reads data
SYNTAX: READ [variable, variable ...]
DESC:
CODE:
EXAMPLES: read.kbasic
CATEGORY: KEYWORD, VARIABLE
SEEALSO: DATA, RESTORE
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fREAD(pcode *p)
/*
[QBASIC]
[*]
[*]
[*]
*/
{

//	register bool bTerm_READ = false;

  _BEGIN_

  if (!(/*bTerm_READ = */parseTerm(token__READ))){ _END_ }


  if (!bSilent && bProducePcode){
    p->wr_SEPARATOR(pcode__SEPARATOR, utility::con("fREAD", getCurrentLine() - 1));
  }

	bool bTerm_COMMA = false;

	bool bIDENTIFIER;

  static /**/ int nIdType[parser__MAX_DATA];
	static /**/ int nType[parser__MAX_DATA];
	nType[0] = 0;

	static /**/ int nVar[parser__MAX_DATA];
	static /**/ t_scope scope[parser__MAX_DATA];
  static /**/ bool bImplicitDIM[parser__MAX_DATA];
	bool bTestImplicitDim = true;
	t_arrayVariable a;
	static /**/ bool bAllSize[parser__MAX_DATA];
	static /**/ int nLStringLen[parser__MAX_DATA];
	static /**/ bool bReference[parser__MAX_DATA]; 
	static /**/ bool bProperty[parser__MAX_DATA]; 
	bool bTestProperty = false;


	int nComma = 0;


	while (true){

	 	if (nComma >= parser__MAX_DATA){ internalError("too many READ in one line"); _ERROR_ }

	 	if (!isScopeDefaultGlobal()){ semanticError(token__READ, "READ not allowed inside a sub/function/method"); _ERROR_ }

 	  if (bIDENTIFIER = fVARIABLE(p, &nVar[nComma], &scope[nComma], &nIdType[nComma], &nType[nComma], &bImplicitDIM[nComma], bTestImplicitDim, &a, &bAllSize[nComma], &nLStringLen[nComma], &bReference[nComma], &bProperty[nComma], bTestProperty)){
      
      int nReturnExpressionType = 0;
      if (fVARIABLE_DIM(p, p, nVar[nComma], scope[nComma], nIdType[nComma], nType[nComma], bImplicitDIM[nComma], false, &nReturnExpressionType, bReference[nComma], false)){

       if (nType[nComma] == token__ME){
         { semanticError(token__READ, "READ not allowed in combination with ME"); _ERROR_ }
		    } else if (nType[nComma] == token__PARENT){
         { semanticError(token__READ, "READ not allowed in combination with PARENT"); _ERROR_ }
       } else {
       }
      }

		}	else { syntaxError(token__READ, "identifier missing or identifier not declared"); _ERROR_ }

	  if (bTerm_COMMA = parseTerm(token__SYM_COMMA)){
			nComma++;
		} else {

			if (nType[0] != 0){

   			if (bProducePcode){
					nDataCount = (nComma + 1);


					for (int i = 0; i < nComma + 1; i++){

   				  p->wr_READ(pcode__READ, 1);
     				if (memory_type::scalar(nIdType[i])){
               switch (nType[i]){
           	    case pcode__BOOLEAN: p->wr_MOV_BOOLEAN(pcode__MOV_BOOLEAN, nVar[i], scope[i]); break;
           	    case pcode__INTEGER: p->wr_MOV_INTEGER(pcode__MOV_INTEGER, nVar[i], scope[i]); break;
           	    case pcode__LONG: p->wr_MOV_LONG(pcode__MOV_LONG, nVar[i], scope[i]); break;
             		case pcode__DOUBLE: p->wr_MOV_DOUBLE(pcode__MOV_DOUBLE, nVar[i], scope[i]); break;
             		case pcode__SINGLE: p->wr_MOV_SINGLE(pcode__MOV_SINGLE, nVar[i], scope[i]); break;
             		case pcode__CSTRING: p->wr_MOV_CSTRING(pcode__MOV_CSTRING, nVar[i], scope[i]); break;
             		case pcode__QSTRING: p->wr_MOV_QSTRING(pcode__MOV_QSTRING, nVar[i], scope[i]); break;
                default:  { syntaxError(token__READ, "wrong datatype"); _ERROR_ }
         			}

     				} else {
     					p->wr_MOV(pcode__MOV, nVar[i], scope[i]);
     				}

					}
   			}

   			parseInfo(p, "parsed READ");
   			return true;
    	}
			
			if (!(nComma > 0)){ syntaxError(token__READ, "READ information missing"); _ERROR_ }

		}

	}

	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: LBOUND
PRINTNAME: LBound
TASK: returns the lower bound of an array
SYNTAX: LBOUND(arrayvariable[, index])
DESC:
CODE:
EXAMPLES: lbound.kbasic
CATEGORY: KEYWORD, VARIABLE, ARRAY
SEEALSO: UBOUND, DIM, REDIM
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fLBOUND(pcode *p, int *nReturnExpressionType, bool bReturn)
/*
[QBASIC]
[VB]
[*]
[*]
*/
{

	//register bool bTerm_LBOUND = false;
 	_BEGIN_

  if (!(/*bTerm_LBOUND = */parseTerm(token__LBOUND))){ _END_ }


	bool bIDENTIFIER = false;

	bool bTerm_SYM_BR_OP = false;
	bool bTerm_SYM_BR_CL = false;
	bool bTerm_COMMA = false;

	bool bEXPRESSION = false;
	int nExpressionType;

	int nVar = 0;
	t_scope scope = global;
  bool bImplicitDIM = false;
	bool bTestImplicitDim = true;
	t_arrayVariable a;
  int nIdType = 0;
	int nType = 0;  
	bool bAllSize = false;
	int nLStringLen = 0;  
	bool bReference = false;  
	bool bProperty = false;  
  bool bTestProperty = false;

  if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

 	  if (bIDENTIFIER = fVARIABLE(p, &nVar, &scope, &nIdType, &nType, &bImplicitDIM, bTestImplicitDim, &a, &bAllSize, &nLStringLen, &bReference, &bProperty, bTestProperty)){

      if (nType == token__ME){
        { semanticError(token__LBOUND, "LBOUND not allowed in combination with ME"); _ERROR_ }
		   } else if (nType == token__PARENT){
        { semanticError(token__LBOUND, "LBOUND not allowed in combination with PARENT"); _ERROR_ }
      } else {
      }

		  if (bTerm_COMMA = parseTerm(token__SYM_COMMA)){

				if (bEXPRESSION = fEXPRESSION(p, &nExpressionType)){}

		  	if (!bEXPRESSION){ syntaxError(token__LBOUND, "expression missing"); _ERROR_ }

				if (!compatibleType(pcode__LONG, nExpressionType)){ semanticError(token__LBOUND, "incompatible types"); _ERROR_ }

			}

  		if (!(bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL)))){ syntaxError(token__LBOUND, ") missing"); _ERROR_ }
 
  		if (bProducePcode){
  			p->wr_LBOUND(pcode__LBOUND, nVar, scope, bEXPRESSION, bReturn);
  		}
			*nReturnExpressionType = pcode__LONG;

   		parseInfo(p, "parsed LBOUND");
  		return true;
		}
	}

	if (!bTerm_SYM_BR_OP){ syntaxError(token__LBOUND, "( missing"); _ERROR_ }
  if (!bIDENTIFIER){ syntaxError(token__LBOUND, "identifier missing or identifier not declared"); _ERROR_ }

	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: UBOUND
PRINTNAME: UBound
TASK: returns the upper bound of an array
SYNTAX: UBOUND(arrayvariable[, index])
DESC:
CODE:
EXAMPLES: ubound.kbasic
CATEGORY: KEYWORD, VARIABLE, ARRAY
SEEALSO: LBOUND
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fUBOUND(pcode *p, int *nReturnExpressionType, bool bReturn)
/*
[QBASIC]
[VB]
[*]
[*]
*/
{

	//register bool bTerm_UBOUND = false;
  _BEGIN_

    if (!(/*bTerm_UBOUND = */parseTerm(token__UBOUND))){ _END_ }

	

	bool bIDENTIFIER = false;

	bool bTerm_SYM_BR_OP = false;
	bool bTerm_SYM_BR_CL = false;
	bool bTerm_COMMA = false;

	bool bEXPRESSION = false;

	int nVar = 0;
	t_scope scope = global;
	int nType = 0;

  if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

 	  if (bIDENTIFIER = fVARIABLE(p, &nVar, &scope, &nType)){

      if (nType == token__ME){
        { semanticError(token__UBOUND, "UBOUND not allowed in combination with ME"); _ERROR_ }
		   } else if (nType == token__PARENT){
        { semanticError(token__UBOUND, "UBOUND not allowed in combination with PARENT"); _ERROR_ }
      } else {
      }

		  if (bTerm_COMMA = parseTerm(token__SYM_COMMA)){

				if (bEXPRESSION = fNUMERIC_EXPRESSION(p)){}

		  	if (!bEXPRESSION){ syntaxError(token__UBOUND, "expression missing"); _ERROR_ }

			}

  		if (!(bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL)))){ syntaxError(token__UBOUND, ") missing"); _ERROR_ }

  		if (bProducePcode){
  			p->wr_UBOUND(pcode__UBOUND, nVar, scope, bEXPRESSION, bReturn);
  		}
			*nReturnExpressionType = pcode__LONG;

   		parseInfo(p, "parsed UBOUND");
  		return true;
		}
	}

	if (!bTerm_SYM_BR_OP){ syntaxError(token__UBOUND, "( missing"); _ERROR_ }
  if (!bIDENTIFIER){ syntaxError(token__LBOUND, "identifier missing or identifier not declared"); _ERROR_ }

	_END_
}

/* *
[KBASIC][VB][QBASIC]
NAME: VARTYPE
PRINTNAME: VarType
TASK: returns the type of a variable
SYNTAX: VARTYPE(variable)
DESC:
kbEmpty	0
kbNull	1
kbInteger	2
kbLong	3
kbSingle	4
kbDouble	5
kbCurrency	6
kbDate	7
kbString	8
kbObject	9
kbError	10
kbBoolean	11
kbVariant	12
kbByte	17
kbShort	18
kbInt16	19
kbInt32	20
kbInt64	21
kbUInt16 22
kbUInt32 23
kbUInt64 24
kbArray	8192
CODE:
EXAMPLES: vartype.kbasic
CATEGORY: KEYWORD, VARIABLE
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fVARTYPE(pcode *p, int *nReturnExpressionType, bool bReturn)
/*
[*]
[VB]
[*]
[*]
*/
{

	//register bool bTerm_VARTYPE = false;

  _BEGIN_

  if (!(/*bTerm_VARTYPE = */parseTerm(token__VARTYPE))){ _END_ }
  
  

	bool bIDENTIFIER = false;

	bool bTerm_SYM_BR_OP = false;
	bool bTerm_SYM_BR_CL = false;

	int nVar = 0;
	t_scope scope = global;
  bool bImplicitDIM = false;
	bool bTestImplicitDim = true;
	t_arrayVariable a;
  int nIdType = 0;
	int nType = 0;  
  bool bAllSize = false;
	int nLStringLen = 0;  
	bool bReference = false;  
	bool bProperty = false;  
  bool bTestProperty = true;

  if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

 	  if (bIDENTIFIER = fVARIABLE(p, &nVar, &scope, &nIdType, &nType, &bImplicitDIM, bTestImplicitDim, &a, &bAllSize, &nLStringLen, &bReference, &bProperty, bTestProperty)){

      if (nType == token__ME){
        { semanticError(token__VARTYPE, "VARTYPE not allowed in combination with ME"); _ERROR_ }
		   } else if (nType == token__PARENT){
        { semanticError(token__VARTYPE, "VARTYPE not allowed in combination with PARENT"); _ERROR_ }
      } else {
      }

  		if (!(bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL)))){ syntaxError(token__VARTYPE, ") missing"); _ERROR_ }

  		if (bProducePcode){
  			p->wr_VARTYPE(pcode__VARTYPE, nVar, scope, bReturn);
  		}
			*nReturnExpressionType = pcode__INTEGER;

   		parseInfo(p, "parsed VARTYPE");
  		return true;
		}
	}

	if (!bTerm_SYM_BR_OP){ syntaxError(token__VARTYPE, "( missing"); _ERROR_ }

	_END_
}

/* *
[KBASIC][VB][QBASIC]
NAME: TYPEOF
PRINTNAME: TypeOf
TASK: TYPEOF
SYNTAX: TYPEOF
DESC: TYPEOF
CODE:
EXAMPLES: typeof.kbasic
CATEGORY: KEYWORD, VARIABLE
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fTYPEOF(pcode *p, int *nReturnExpressionType, bool bReturn)
{

	//register bool bTerm_TYPEOF = false;

  _BEGIN_

  if (!(/*bTerm_TYPEOF = */parseTerm(token__TYPEOF))){ _END_ }

  


	bool bIDENTIFIER = false;

	const char *acType = "";

	bool bTerm_IS = false;
	bool bTYPE = false;

	int nVar = 0;
	t_scope scope = global;
  bool bImplicitDIM = false;
	bool bTestImplicitDim = true;
	t_arrayVariable a;
  int nIdType = 0;
	int nType = 0;  
  bool bAllSize = false;
	int nLStringLen = 0;
	bool bReference = false;  
	bool bProperty = false; 
  bool bTestProperty = true;
  

  if (bIDENTIFIER = fVARIABLE(p, &nVar, &scope, &nIdType, &nType, &bImplicitDIM, bTestImplicitDim, &a, &bAllSize, &nLStringLen, &bReference, &bProperty, bTestProperty)){

     if (nType == token__ME){
       { semanticError(token__TYPEOF, "TYPEOF not allowed in combination with ME"); _ERROR_ }
		 } else if (nType == token__PARENT){
       { semanticError(token__TYPEOF, "TYPEOF not allowed in combination with PARENT"); _ERROR_ }
     } else {
     }

		if (!(bTerm_IS = parseTerm(token__IS))){ syntaxError(token__TYPEOF, "IS missing"); _ERROR_ }

		if (!(bTYPE = fTYPE(p, &acType, false))){ syntaxError(token__TYPEOF, "type name missing"); _ERROR_ }

	  int nType2 = findType(acType);
		if (nType2 == 0){ semanticError(token__TYPEOF, utility::con(acType, " not defined") ); _ERROR_ }

  	if (bProducePcode){
  		p->wr_TYPEOF(pcode__TYPEOF, nVar, scope, nType2, bReturn);
  	}
		*nReturnExpressionType = pcode__BOOLEAN;

   	parseInfo(p, "parsed TYPEOF");
  	return true;
	}


	_END_
}


//, PRIVATE CONST, PUBLIC CONST, Private Const, Public Const
/**
[QBASIC][VB][KBASIC]
NAME: CONST
PRINTNAME: Const
TASK: Declares a const
SYNTAX: CONST name [AS type] = expression
DESC: 
EXAMPLES: const.kbasic
CATEGORY: KEYWORD
SEEALSO: DIM
VERSION: PERSONAL, PROFESSIONAL
LOG: 05-02-2005 implemented
TIP:
*/
// module or global const
bool parser::fCONST(pcode *p) 
/*
[QBASIC] 
- const name can also contain . (which is not supported)
- can be inside a sub or a function
[VB]
[*]
[*]
*/
{
	_BEGIN_

	bool bTerm_PRIVATE = false;
	bool bTerm_PUBLIC = false;

			 if (bTerm_PRIVATE = parseTerm(token__PRIVATE)){} 
	else if (bTerm_PUBLIC = parseTerm(token__PUBLIC)){}
	
	//bool bTerm_CONST = false;

  if (!(/*bTerm_CONST = */parseTerm(token__CONST))){ _END_ }

  if (!bSilent && bProducePcode){
    p->wr_SEPARATOR(pcode__SEPARATOR, utility::con("fCONST", getCurrentLine() - 1));
  }

  // const local fehlermeldung, kann nicht public/private sein
  if (isScopeLocal() && (bTerm_PRIVATE || bTerm_PUBLIC)){ semanticError(token__CONST, " local const must not be PRIVATE or PUBLIC"); _ERROR_ }

  if (!bTerm_PRIVATE && !bTerm_PUBLIC){ bTerm_PUBLIC = true; }

	bool bTerm_COMMA = false;
	bool bTerm__ = false;
	static /**/ bool bIDENTIFIER[parser__MAX_CONST];
	static /**/ const char *acIdentifier[parser__MAX_CONST];
	static /**/ bool bEXPRESSION[parser__MAX_CONST];
	int nExpressionType;
	bool bTYPE = false;
	bool bTerm_AS = false;  
  static /**/ const char *acType[parser__MAX_CONST];

	int nComma = 0;

	bEXPRESSION[nComma] = false;


	while (true){

	 	if (nComma >= parser__MAX_CONST){ internalError("too many CONST in one line"); _ERROR_ }

		if (bIDENTIFIER[nComma] = fID_KEYWORD_OR_BUILTIN(&acIdentifier[nComma])){}

		if (bIDENTIFIER[nComma])
    if (bTerm__ = parseTerm(token__OP_EQUAL)){
		  if (bEXPRESSION[nComma] = fEXPRESSION(p, &nExpressionType)){}

	 	  if (!bEXPRESSION[nComma]){ semanticError(token__CONST, "const expression missing"); _ERROR_ }     
      
      if (!memory_type::scalar(nExpressionType)){ semanticError(token__CONST, "CONST must be of scalar type INTEGER, LONG, BOOLEAN, SINGLE, DOUBLE, STRING, CURRENCY, DATE, BYTE"); _ERROR_ }

    } else {
      if (bTerm_AS = parseTerm(token__AS)){
			  if (bTYPE = fTYPE(p, &acType[nComma], false)){}

        if (bTerm_AS && !bTYPE){ syntaxError(token__TRY, "type name missing"); _ERROR_ }

        if (bTerm__ = parseTerm(token__OP_EQUAL)){
		      if (bEXPRESSION[nComma] = fCONST_EXPRESSION(p)){}

          if (!bEXPRESSION[nComma]){ semanticError(token__CONST, "const expression missing"); _ERROR_ }     
        }
      }
    }

				 if (!bIDENTIFIER[nComma]){ syntaxError(token__CONST, "identifier missing or identifier not declared or not declared"); _ERROR_ }
		else if (!bTerm__){ syntaxError(token__CONST, "= missing"); _ERROR_ }
	  else if (!bEXPRESSION[nComma]){ syntaxError(token__CONST, "const expression missing"); _ERROR_ }

	  if (bTerm_COMMA = parseTerm(token__SYM_COMMA)){
			nComma++;
		} else {

			char acVars[2048];
			char ac[2048];
     sprintf(acVars, "");

			for (int i = nComma; i >= 0; i--){

        sprintf(ac, "%s%s", acIdentifier[i], i > 0 ? ", " : "");
        strcat(acVars, ac);

    		const char *acVar = acIdentifier[i];

        int nVar = 0;
        // es gibt auch lokale consts, diese werden von module.subconst erfasst
        if (isScopeLocal()){
          if (isScopeClassLocalInstance() || isScopeClassLocalStatic()){
            if (bScopeClassPropertyGet){
              nVar = registerClassLocalPropertyGetConst(getClass(), getMethod(), 0, acVar);
        	    if (nVar == 0){ semanticError(token__CONST, utility::con(utility::ident(getClass(), getMethod(), acVar), " already declared at some place") ); _ERROR_ }
            } else if (bScopeClassPropertySet){
              nVar = registerClassLocalPropertySetConst(getClass(), getMethod(), 0, acVar);
        	    if (nVar == 0){ semanticError(token__CONST, utility::con(utility::ident(getClass(), getMethod(), acVar), " already declared at some place") ); _ERROR_ }
            } else {
              nVar = registerClassLocalConst(getClass(), getMethod(), 0, acVar);
        	    if (nVar == 0){ semanticError(token__CONST, utility::con(utility::ident(getClass(), getMethod(), acVar), " already declared at some place") ); _ERROR_ }
            }
          } else {
             nVar = registerModuleLocalConst(getModule(), getSub(), 0, acVar);
        	    if (nVar == 0){ semanticError(token__CONST, utility::con(utility::ident(getModule(), getSub(), acVar), " already declared at some place") ); _ERROR_ }
          }
        } else {
          if (isScopeClass()){
             nVar = registerClassConst(getClass(), acVar, bTerm_PUBLIC);
        	    if (nVar == 0){ semanticError(token__CONST, utility::con(utility::ident(getClass(), acVar), " already declared at some place") ); _ERROR_ }
          } else {
             nVar = registerModuleConst(getModule(), acVar, bTerm_PUBLIC);
        	    if (nVar == 0){ semanticError(token__CONST, utility::con(utility::ident(getModule(), acVar), " already declared at some place") ); _ERROR_ }
          }
        }

     		if (bProducePcode){

     			 p->wr_CONST(pcode__CONST, nVar, getScopeCode());
      		 p->wr_MOV_CONST(pcode__MOV_CONST, nVar, getScopeCode()); // write pcode
     		}
			}

			parseInfo(p,  utility::con("parsed CONST ", acVars) );
   	
   		return true;

 		}
	}

	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: MID2
PRINTNAME: Mid
TASK: MID$ replaces part of a string with another string
SYNTAX: MID$(strvar AS STRING, start AS INTEGER [, length AS INTERGER]) = replacement-string
DESC: 
Usually you will use this statement to replace at least part of a string
 which is in "strvar" with the "replacement-string". The "strvar" variable
 must always be a string variable, but the string to replace it
 ("replacement-string") may be any string expression. Note that the "start"
 position for the replacement within "strvar" has to be given, but the
 "length" indication is optional. By giving "length" you may indicate how
 many characters of the "replacement-string" will be used to replace
 characters in the string variable "strvar".

NOTE:
The resulting string (in "strvar") will not become longer if "length" points
 to somewhere beyond its original length. In this case, the
 replacement-string will be cut to fit, and it will result in replacing just
 "the rest of strvar".

CODE:
Examples:

DIM text AS STRING, replacement AS STRING, originaltxt
AS STRING

text = "The dog bites the cat"
MID(text, 5)  = "cat"
MID(text, 20) = "dog"
PRINT text

MID(text, 5) = "text is too long for the string"
PRINT text

replacement = "The power of KBasic"
originaltxt = "*********************"
FOR i = 1 to LEN(replacement)
         MID(originaltxt, 2, i) = replacement
         PRINT originaltxt
NEXT i

Output:
The cat bites the dog
The text is too long
*T*******************
*Th******************
*The*****************
*The ****************
*The p***************
*The po**************
*The pow*************
*The powe************
*The power***********
*The power **********
*The power o*********
*The power of********
*The power of *******
*The power of K******
*The power of KB*****
*The power of KBa****
*The power of KBas***
*The power of KBasi**
*The power of KBasic*

EXAMPLES: mid.kbasic
CATEGORY: KEYWORD, STRING
SEEALSO: LEFT, RIGHT, LEN
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fMID2(pcode *p) // MID Statement
/*
[QBASIC]
[VB]
[*]
[*]
*/
{
	
	//register bool bTerm_MID = false;

  _BEGIN_

  if ((/*bTerm_MID = */parseTerm(token__MID)));
  else if (!(/*bTerm_MID = */parseTerm(token__MID_))){ _END_ }

  

 	bool bTerm_SYM_BR_OP = false;
 	bool bTerm_SYM_BR_CL = false;
	bool bTerm_COMMA = false;
	bool bTerm__ = false;

	bool bIDENTIFIER = false;
	bool bEXPRESSION = false;
	bool bEXPRESSION2 = false;

	int nVar = 0; t_scope scope = global; int nIdType = 0; int nType = 0; t_arrayVariable a;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){
 
		if (bIDENTIFIER = fSTRING_VARIABLE(p, &nVar, &scope, &nIdType, &nType, &a)){

  		if (bTerm_COMMA = parseTerm(token__SYM_COMMA))

  		if (!(bEXPRESSION = fLONG_EXPRESSION(p))){ syntaxError(token__MID, "long expression missing"); _ERROR_ }

  		if (bTerm_COMMA = parseTerm(token__SYM_COMMA)){
  			if (!(bEXPRESSION2 = fLONG_EXPRESSION(p))){ syntaxError(token__MID, "long expression missing"); _ERROR_ }
  		}
			if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
 			if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__MID, ") missing"); _ERROR_ }

 			if (bTerm__ = parseTerm(token__OP_EQUAL))
      if (bEXPRESSION = fEXPRESSION(p)){}

      if (!bEXPRESSION){ syntaxError(token__MID, "expression missing"); _ERROR_ }

 			if (bProducePcode){
   			 p->wr_MID2(pcode__MID2, nVar, scope, bEXPRESSION2); // write pcode
 			}

 			parseInfo(p, "parsed MID2 statement");
 			return true;
 		}
	}
  

	_END_
}

bool parser::catchFinally(pcode *p, bool bTry)
{
	_BEGIN_

	register bool bTerm_TRY = false;

  if (bTry){
    if (!(bTerm_TRY = parseTerm(token__TRY))){ _END_ }

    if (!bSilent && bProducePcode){
      p->wr_SEPARATOR(pcode__SEPARATOR, utility::con("fTRY", getCurrentLine() - 1));
    }
  }

	static /**/ const char *acIdentifier[parser__MAX_CATCH];

	int nComma = 0;

	bool bTerm_CATCH;
	bool bTerm_FINALLY;
	bool bTerm_END;

 	bool bTerm_SYM_BR_OP = false;
 	bool bTerm_SYM_BR_CL = false;

 	bool bTerm_AS = false;
 	bool bTYPE = false;
  int nTryPos = 0;
  
  static /**/ int nCatchPosBefore[parser__MAX_CATCH];
  static /**/ int nCatchPos[parser__MAX_CATCH];

	static /**/ const char *acType[parser__MAX_CATCH];

  if (bProducePcode){
    p->wr_TRY(pcode__TRY); // write pcode
  }

  if (bTry){
	  if (fSTATEMENTSEQUENCE(p)){}
  }

  nTryPos = p->getPos();

  if (bProducePcode){
    p->wr_JMP(pcode__JMP, 0);         
  }


  while (true){

		if (nComma >= parser__MAX_CATCH){ internalError("too many catches"); _ERROR_ }

		if (bTerm_CATCH = parseTerm(token__CATCH)){

			if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

				if (!fID_KEYWORD_OR_BUILTIN(&acIdentifier[nComma])){ syntaxError(token__TRY, "missing catch identifier"); _ERROR_ }

        if (bTerm_AS = parseTerm(token__AS))
			  if (bTYPE = fTYPE(p, &acType[nComma], false)){}

        if (
          strcmp(acIdentifier[nComma], "CASTEXCEPTION") != 0
          && strcmp(acIdentifier[nComma], "QTEXCEPTION") != 0
          && strcmp(acIdentifier[nComma], "EXCEPTION") != 0
          ){
           		   if (!bTerm_AS){ syntaxError(token__TRY, "AS missing"); _ERROR_ }
            else if (!bTYPE){ syntaxError(token__TRY, "catch object name missing"); _ERROR_ }
        } else {
          bTerm_AS = true;
          bTYPE = true;
          acType[nComma] = acIdentifier[nComma];
        }      

        t_exception *t;
        if (myException.first((int *) &t)){
          do {
               
            if (utility::my_stricmp(t->acName, acType[nComma]) == 0){
              myException.removeCurrent();
              break;
            }
          } while (myException.next((int *) &t));
          myException.first((int *) &t);
        }        


				if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}

			}
 					 if (!bTerm_SYM_BR_OP){ syntaxError(token__TRY, "( missing"); _ERROR_ }
 			else if (!bTerm_SYM_BR_CL){ syntaxError(token__TRY, ") missing"); _ERROR_ }

      t_array a;
      int nType = findType(acType[nComma]);

      bool bb = true;
      switch(nType){
        case pcode__CASTEXCEPTION:
        case pcode__QTEXCEPTION:
        case pcode__EXCEPTION:
          bb = false;
          break;
      }

      if (bb){
        int nVar = registerVar(acIdentifier[nComma], nType, &a, false, false, token__PUBLIC, 0);
 	      if (nVar == 0){ semanticError(token__DIM, utility::con(utility::ident(getScope(), getSub(), acIdentifier[nComma]), " already declared at some place") ); _ERROR_ }
 		    //if (nVar == 0){ internalError(utility::con(utility::ident(getScope(), getSub(), acIdentifier[nComma]), " could not be declared") ); _ERROR_ }

        nCatchPosBefore[nComma] = p->getPos();

		    if (bProducePcode){

          p->wr_DIM(pcode__DIM, nVar, getScopeCode(), nType, false, false, false, false, 0, 0, "", false); // write pcode
          p->wr_MOV(pcode__MOV, nVar, getScopeCode()); // write pcode

        }
      } else {
        nCatchPosBefore[nComma] = p->getPos();
      }

			if (fSTATEMENTSEQUENCE(p)){}			

      nCatchPos[nComma] = p->getPos();

		  if (bProducePcode){
        p->wr_JMP(pcode__JMP, 0);         
      }

			nComma++;

		} else {
			if (nComma == 0){
        if (bTry){
				   { syntaxError(token__TRY, "CATCH missing"); _ERROR_ }
        } else {
           _END_
        }
			}
			break;
		}
	
	}

  if (bTerm_FINALLY = parseTerm(token__FINALLY)){}

    memory_sub *s = 0;
    int nId = 0;
    int nSubId = 0;
    pcode *pp = 0;
    int nPcodeOffset = 0;
    int nCatchPcodePos = 0; 
    int nCatchType = 0;

      if (getCurrentLine() > 60){
        int i = 9;
        i++;
      }

    switch(isScopeClass()){
				case false:
           nId = myModule->getId(getScope());
   				  s = myModule->getSubs(nId);
           nSubId = s->getId(nId, getSub());
					  break;
			 case true:
           nId = myClass->getId(getScope());
   				  s = myClass->getMethods(nId);
           nSubId = s->getId(nId, getMethod());
					  break;
		}

   bool b = false;
   if (!isScopeLocal()){

      switch(isScopeClass()){
				  case false:
             b = myModule->firstPcodeCatch (nId, &pp, &nCatchType, &nPcodeOffset, &nCatchPcodePos);
					    break;
				  case true:
             b = myClass->firstPcodeCatch (nId, &pp, &nCatchType, &nPcodeOffset, &nCatchPcodePos);
					    break;
		  }
   }

    int z = 0;
    if (b || s->firstPcodeCatch (nSubId, &pp, &nCatchType, &nPcodeOffset, &nCatchPcodePos)){

			  do {

          for (int i = 0; i < nComma; i++){

             int nType = findType(acType[i]);

             if (nType == nCatchType){
                 nCatchPcodePos = nCatchPosBefore[i];

                  int n2 = pp->getPos();

                  pp->setPos(nPcodeOffset);

                  if (bProducePcode){
                    pp->wr_CATCH(pcode__CATCH, nCatchType, nCatchPcodePos - nPcodeOffset);         
                  }

                  pp->setPos(n2);
                  z++;
                  break;

             }

          }

          b = false;

         if (z < nComma){

           if (!isScopeLocal()){

              switch(isScopeClass()){
				          case false:
                   b = myModule->nextPcodeCatch (nId, &pp, &nCatchType, &nPcodeOffset, &nCatchPcodePos);
					          break;
				          case true:
                   b = myClass->nextPcodeCatch (nId, &pp, &nCatchType, &nPcodeOffset, &nCatchPcodePos);
					          break;
		          }
           } else {
              b = s->nextPcodeCatch	(nSubId, &pp, &nCatchType, &nPcodeOffset, &nCatchPcodePos);
           }

         }

			  } while (b);
    }
  


  // finally jumps korrigieren

  int n0 = p->getPos();

  for (int i = 0; i < nComma; i++){
    p->setPos(nCatchPos[i]);

	  if (bProducePcode){
       p->wr_JMP(pcode__JMP, n0);         
    }
  }


  p->setPos(nTryPos);

  if (bProducePcode){
    p->wr_JMP(pcode__JMP, n0);         
  }

  p->setPos(n0);

  if (bTerm_FINALLY) if (fSTATEMENTSEQUENCE(p)){}


  if (bProducePcode){
    p->wr_ENDCATCH(pcode__ENDCATCH); // write pcode
  }

  if (bTry && (bTerm_END = parseTerm(token__END))){
		if (bTerm_FINALLY && (bTerm_FINALLY = parseTerm(token__FINALLY))){
      parseInfo(p, "parsed TRY CATCH FINALLY statement");
    } else if (bTerm_CATCH = parseTerm(token__CATCH)){        
      parseInfo(p, "parsed TRY CATCH statement");
    } else if (bTerm_TRY = parseTerm(token__TRY)){        
      parseInfo(p, "parsed TRY CATCH statement");
		}
		return true;
  } else if (nComma > 0){
		if (bTerm_FINALLY){
      parseInfo(p, "parsed CATCH FINALLY statement");
    } else {
      parseInfo(p, "parsed CATCH statement");
		}
		return true;
  }

	 		 if (!bTerm_END){ syntaxError(token__TRY, "END missing"); _ERROR_ }
 	else if (!bTerm_CATCH && !bTerm_FINALLY){ syntaxError(token__TRY, "CATCH missing"); _ERROR_ }
 	else if (!bTerm_FINALLY){ syntaxError(token__TRY, "FINALLY missing"); _ERROR_ }
 	else if (!bTerm_TRY){ syntaxError(token__TRY, "TRY missing"); _ERROR_ }

	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: TRY
PRINTNAME: Try
TASK: TRY CATCH statement
SYNTAX: 
DESC: see 'The KBasic Book' for details
CODE:
EXAMPLES: try.kbasic
CATEGORY: KEYWORD, CONTROLFLOW, ERROR
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fTRY(pcode *p)
{
  return catchFinally(p, true);
}

/* *
[KBASIC][VB][QBASIC]
NAME: WITH
PRINTNAME: With
TASK: enables you to group statements
SYNTAX: 
DESC: see 'The KBasic Book' for details
CODE:
EXAMPLES: with.kbasic
CATEGORY: KEYWORD, VARIABLE, STRUCTURE
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
/*  
neue funktion in parser.h
die angibt ab welcher position in token gelesen werden soll, abh�gig ob with oder nicht
alle aufrufe von token::  mit dieser funktion als parameter als postionsangabe

withposition beendet mit eol : 
von, bis abspeichern bis= bis eol gehen

with o(88)
.test = 8 --> umgesetzt zu o(88).test
.test2 = 888 --> umgesetzt zu o(88).test2

*/
bool parser::fWITH(pcode *p)
/*
[*]
[VB]
[*]
[*]
*/
{	

	//register bool bTerm_WITH = false;

  _BEGIN_

  if (!(/*bTerm_WITH = */parseTerm(token__WITH))){ _END_ }

  register bool bTerm_WITH;// = false;

  

  if (!bSilent && bProducePcode){
    p->wr_SEPARATOR(pcode__SEPARATOR, utility::con("fWITH", getCurrentLine() - 1));
  }

	bool bTerm_END = false;
  bool bSTATEMENTSEQUENCE = false;

  int n1 = getTokenPos();
  int mm = 0;

  while(proceedParse()){ // setup with
    int n = peekToken();
    if (n == token__MSC_EOL){
      if (mm > 0){
        setTokenPos(mm);
      }
      break;
    }
    if (with_pos_list_POS == -1 && n == token__SYM_DOT){
      mm = getTokenPos();
    }
    if (!nextToken()) break;
  }
  
  int n2 = getTokenPos();      

  with_pos_list[++with_pos_list_POS] = new t_with(n1, n2);

  bSTATEMENTSEQUENCE = fSTATEMENTSEQUENCE(p);

  if (bTerm_END = parseTerm(token__END)){
		if (bTerm_WITH = parseTerm(token__WITH)){

      delete with_pos_list[with_pos_list_POS];
      --with_pos_list_POS;

			parseInfo(p, "parsed WITH statement");
			return true;
		}
	}

	 		 if (!bTerm_END){ syntaxError(token__WITH, ""/*END missing*/); _ERROR_ }
 	else if (!bTerm_WITH){ syntaxError(token__WITH, "WITH missing"); _ERROR_ }

	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: NEW
PRINTNAME: New
TASK: creates a object based on a class
SYNTAX: NEW classname(arguments)
DESC: 
CODE:
EXAMPLES: new.kbasic
CATEGORY: KEYWORD, VARIABLE, CLASS
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fNEW_METHOD_CALL(pcode *p, int *nReturnExpressionType, bool bReturn)
{

	//register bool bTerm_NEW = false;

  _BEGIN_

  if (!(/*bTerm_NEW = */parseTerm(token__NEW))){ _END_ }

  

	const char *acType = "";

	if (fTYPE(p, &acType, true)){

    int nType = findType(acType);
    if (nType == 0){ semanticError(token__KEYWORD, utility::con(acType, " not defined") ); _ERROR_ }
		*nReturnExpressionType = findType(acType);

   if (myClass->isAbstract(nType)){ semanticError(token__CLASS, utility::con(acType, " class is ABSTRACT and therefore can not be used to create an object") ); _TERROR_ };

   // nicht ben�igt: doppelt gemopelt
   //bool b = fCONSTRUCTOR_CALL(p, nType);

    //if (b){ _DONE_ }  
   _DONE_
	}

	_END_
}

bool parser::fNEW(pcode *p)
{
	register int nReturnExpressionType;// = 0; 

  return fNEW_METHOD_CALL(p, &nReturnExpressionType, false);
}

/* *
[EXPLANATION]
NAME: STRING LITERAL
PRINTNAME: String Literal
DESC:
SEEALSO:
VERSION: PERSONAL, PROFESSIONAL
*/
// ***
// write the pcodes for the static strings
// ***
bool parser::appendAllStringLiterals()
{
	if (bProducePcode){
    myPcode->wr_SEPARATOR(pcode__SEPARATOR, " STRING LITERALS"); // leading space used for cutting of the leading f...
  }

  if (bProducePcode){
	  if (myMemory_stringliteral->first()){
  		do {
  			myPcode->wr_STRING_LITERAL(pcode__DIM_STATIC, myMemory_stringliteral->getName(), myMemory_stringliteral->getId()); // TODO3 rename pcode__DIM_STATIC --> STRING_LITERAL
  		} while (myMemory_stringliteral->next());
		}
	}
  return true;
}


/* * 
[KBASIC][VB][QBASIC]
NAME: $STATIC
PRINTNAME: $STATIC
TASK: $STATIC
SYNTAX: $STATIC
DESC: $STATIC
CODE:
EXAMPLES: _static.kbasic
CATEGORY: KEYWORD, VARIABLE
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::f_STATIC(pcode *p)
/*
[QBASIC]

siehe fDYNAMIC, fERASE

[!VB]
[!VBNET]
[!KBASIC]
*/
{
	_BEGIN_

  if (isVERYOLDBASIC()){

    if (parseTerm(token___STATIC)){

      if (bProducePcode){
  			p->wr___STATIC(pcode___STATIC);
  		}

      parseInfo(p, "parsed $STATIC");
      _DONE_
    }
  }

  _END_
}


/* *
[KBASIC][VB][QBASIC]
NAME: $DYNAMIC
PRINTNAME: $DYNAMIC
TASK: $DYNAMIC
SYNTAX: $DYNAMIC
DESC: $DYNAMIC
CODE:
EXAMPLES: _dynamic.kbasic
CATEGORY: KEYWORD, VARIABLE
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::f_DYNAMIC(pcode *p)
/*
[QBASIC]
Fr statische Datenfelder setzt ERASE alle Elemente eines numerischen
Datenfelds auf Null und alle Elemente eines Zeichenfolgen-Datenfelds
auf eine Null-Zeichenfolge ("").
Fr dynamische Datenfelder gibt ERASE den vom Datenfeld benutzten
Speicher wieder frei. Vor der Verwendung von ERASE mssen Sie das
Datenfeld mit REDIM oder DIM neu dimensionieren.

siehe fERASE

[!VB]
[!VBNET]
[!KBASIC]
*/
{
	_BEGIN_

  if (isVERYOLDBASIC()){

    bool bTerm___DYNAMIC = false;
    if (bTerm___DYNAMIC = parseTerm(token___DYNAMIC)){

      if (bProducePcode){
  			p->wr___DYNAMIC(pcode___DYNAMIC);
  		}

      parseInfo(p, "parsed $DYNAMIC");
      _DONE_
    }
  }

  _END_
}

/* *
[KBASIC][VB][QBASIC]
NAME: NAMESPACE
PRINTNAME: Namespace
TASK: NAMESPACE
SYNTAX: NAMESPACE
DESC: NAMESPACE
CODE:
EXAMPLES: namespace.kbasic
CATEGORY: KEYWORD, CLASS, STRUCTURE
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
/*
bool parser::fNAMESPACE()
{
	_TBEGIN_
  if (!(parseTerm(token__NAMESPACE))){ _TEND_ } // to optimize, the 'if' is one of the first statements

  

	bool bIDENTIFIER = false;
	bool bTerm_END = false;
	const char *acNamespace;

	if (bIDENTIFIER = fID_KEYWORD_OR_BUILTIN(&acNamespace)){
/ *
    if (fKBASIC()){

	    if (bTerm_END = parseTerm(token__END))
	    if (bTerm_NAMESPACE = parseTerm(token__NAMESPACE)){}

				  if (!bTerm_END){ syntaxError("missing END"); _TERROR_ }
		  else if (!bTerm_NAMESPACE){ syntaxError("missing NAMESPACE"); _TERROR_ }
    }
    * /
  }
  
  if (!bIDENTIFIER){ syntaxError(token__NAMESPACE, "namespace name missing"); _TERROR_ }


	return true;
}*/

/* *
[KBASIC][VB][QBASIC]
NAME: IMPORTS
PRINTNAME: Imports
TASK: IMPORTS
SYNTAX: IMPORTS
DESC: IMPORTS
CODE:
EXAMPLES: imports.kbasic
CATEGORY: KEYWORD, CLASS, STRUCTURE
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
/*
bool parser::fIMPORTS()
{	

  _TBEGIN_

  if (!(parseTerm(token__IMPORTS))){ _TEND_ } // to optimize, the 'if' is one of the first statements

  

	bool bIDENTIFIER = false;
	bool bTerm_END = false;
	const char *ac;

  //  imports all = all neues keyword, packete werden nach bestimmter reihenfolge importiert kbasic.*, kbasic.io, qt.* ...

	if (bIDENTIFIER = fID_KEYWORD_OR_BUILTIN(&ac)){
/ *
    if (fKBASIC()){

	    if (bTerm_END = parseTerm(token__END))
	    if (bTerm_NAMESPACE = parseTerm(token__NAMESPACE)){}

				  if (!bTerm_END){ syntaxError("missing END"); _TERROR_ }
		  else if (!bTerm_NAMESPACE){ syntaxError("missing NAMESPACE"); _TERROR_ }
    }
    * /
  }
  
  if (!bIDENTIFIER){ syntaxError(token__IMPORTS, "name to import missing"); _TERROR_ }

  // setNamespace(acNamespace); 

	return true;
}*/

/*
// PRINT kbasic.math.ABS(value1 - value2)
bool parser::fNAMESPACECLASS(pcode *p, const char *acNamespaceClass)
{
	_BEGIN_

  / *
  const char *ac;

  XStringList s = XStringList::split(".", acNamespaceClass);
  
  for ( XStringList::Iterator it = s.begin(); it != s.end(); ++it ) {

    if (it != s.begin()){
      if (!parseTerm(token__SYM_DOT)){ _END_ }
    }

    if (!(fID(&ac))){ 
      if (it != s.begin()){
        semanticError(token__NAMESPACE, "namespace name missing");
      }
      _ERROR_ 
    }
    if (!(strcmp(*it, ac) == 0)){ _END_ }

  }
   * /

  if (!parseTerm(token__SYM_DOT)){ _END_ }

  _DONE_
}*/

/**
[KBASIC][VB][QBASIC]
NAME: __LINE__
PRINTNAME: __LINE__
TASK: Helpful for error messages. It contains the current source code line in your program
SYNTAX: __LINE__
DESC:
CODE:
Print "error in line " & __LINE__
EXAMPLES: __line__.kbasic
CATEGORY: FUNCTION, BUILTIN
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
/**
[KBASIC][VB][QBASIC]
NAME: __MODULE__
PRINTNAME: __MODULE__
TASK: Helpful for error messages. It contains the current module name
SYNTAX: __MODULE__
DESC:
CODE:
Print "error in module " & __MODULE__
EXAMPLES: __module__.kbasic
CATEGORY: FUNCTION, BUILTIN
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
/**
[KBASIC][VB][QBASIC]
NAME: __SCOPE__
PRINTNAME: __SCOPE__
TASK: Helpful for error messages. It contains the current scope name
SYNTAX: __SCOPE__
DESC:
CODE:
Print "error in scope " & __SCOPE__
EXAMPLES: __scope__.kbasic
CATEGORY: FUNCTION, BUILTIN
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
/**
[KBASIC][VB][QBASIC]
NAME: __CLASS__
PRINTNAME: __CLASS__
TASK: Helpful for error messages. It contains the current class name
SYNTAX: __CLASS__
DESC:
CODE:
Print "error in class " & __CLASS__
EXAMPLES: __class__.kbasic
CATEGORY: FUNCTION, BUILTIN
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
/**
[KBASIC][VB][QBASIC]
NAME: __SUB__
PRINTNAME: __SUB__
TASK: Helpful for error messages. It contains the current sub/function name
SYNTAX: __SUB__
DESC:
CODE:
Print "error in sub/function " & __SUB__
EXAMPLES: __sub__.kbasic
CATEGORY: FUNCTION, BUILTIN
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
/**
[KBASIC][VB][QBASIC]
NAME: __ISLINUX__
PRINTNAME: __ISLINUX__
TASK: returns true if KBasic is running on linux
SYNTAX: __ISLINUX__
DESC:
CODE:
EXAMPLES: __islinux__.kbasic
CATEGORY: FUNCTION, BUILTIN
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
/**
[KBASIC][VB][QBASIC]
NAME: __ISWINDOWS__
PRINTNAME: __ISWINDOWS__
TASK: returns true if KBasic is running on windows
SYNTAX: __ISWINDOWS__
DESC:
CODE:
EXAMPLES: __iswindows__.kbasic
CATEGORY: FUNCTION, BUILTIN
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
/**
[KBASIC][VB][QBASIC]
NAME: __ISMACOS__
PRINTNAME: __ISMACOS__
TASK: returns true if KBasic is running on mac os x
SYNTAX: __ISMACOS__
DESC:
CODE:
EXAMPLES: __ismacos__.kbasic
CATEGORY: FUNCTION, BUILTIN
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
/**
[KBASIC][VB][QBASIC]
NAME: __FILE__
PRINTNAME: __FILE__
TASK: returns the current file name
SYNTAX: __FILE__
DESC:
CODE:
EXAMPLES: __file__.kbasic
CATEGORY: FUNCTION, BUILTIN
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
/**
[KBASIC][VB][QBASIC]
NAME: __ISCLASS__
PRINTNAME: __ISCLASS__
TASK: returns true if current scope is class
SYNTAX: __ISCLASS__
DESC:
CODE:
EXAMPLES: __isclass__.kbasic
CATEGORY: FUNCTION, BUILTIN
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
/**
[KBASIC][VB][QBASIC]
NAME: __ISMODULE__
PRINTNAME: __ISMODULE__
TASK: returns true if current scope is module
SYNTAX: __ISMODULE__
DESC:
CODE:
EXAMPLES: __ismodule__.kbasic
CATEGORY: FUNCTION, BUILTIN
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
/**
[KBASIC][VB][QBASIC]
NAME: __ISSUB__
PRINTNAME: __ISSUB__
TASK: returns true if current scope is sub/function/method
SYNTAX: __ISSUB__
DESC:
CODE:
EXAMPLES: __issub__.kbasic
CATEGORY: FUNCTION, BUILTIN
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fMACRO(pcode *p, int *nReturnExpressionType, bool bReturn)
{
	_BEGIN_

	//register bool bTerm_ = false;
	register int token = 0;

  switch (peekToken()){
    case token____LINE__: parseTerm(token____LINE__); token = token____LINE__; break;
    case token____MODULE__: parseTerm(token____MODULE__); token = token____MODULE__; break;
    case token____SCOPE__: parseTerm(token____SCOPE__); token = token____SCOPE__; break;
    case token____CLASS__: parseTerm(token____CLASS__); token = token____CLASS__; break;
    case token____SUB__: parseTerm(token____SUB__); token = token____SUB__; break;
    case token____ISLINUX__: parseTerm(token____ISLINUX__); token = token____ISLINUX__; break;
    case token____ISWINDOWS__: parseTerm(token____ISWINDOWS__); token = token____ISWINDOWS__; break;
    case token____ISMACOS__: parseTerm(token____ISMACOS__); token = token____ISMACOS__; break;
    case token____FILE__: parseTerm(token____FILE__); token = token____FILE__; break;
    case token____ISCLASS__: parseTerm(token____ISCLASS__); token = token____ISCLASS__; break;
    case token____ISMODULE__: parseTerm(token____ISMODULE__); token = token____ISMODULE__; break;
    case token____ISSUB__: parseTerm(token____ISSUB__); token = token____ISSUB__; break;
    default:
      _END_
        break;
  }

  /*
  

__ISDEBUG__  wenn compilation mit debug informatino
__ISVMINFO__ wenn mit virtual machine info

__DATE__
The date of translation of the source file.
__TIME__
The time of translation of the source file.

__KBASICDIR__  the kbasic directory
__KBASICVER__  the kbasic version

__FILEDIR__the directory of current file
__PROJECTDIR__the directory of current file
  */

  //  callstack: comma-separated list of function callers  main;parse;statement[89];iteratioin;  []bei rekursive call     class/module.method/function
  //  __subvars__   __subconsts__   __classvars__ __classconsts__  __modulevars__ __moduleconsts__
  //  debug.subvars, debug.module, debug.islinux ...

	//if (bTerm_)
  {

//		if (bReturn){ syntaxError(token__KEYWORD, "macro can not be used as a function"); _ERROR_ }

		const char *ac = "";

 		if (bProducePcode){

			switch(token){
				case token____LINE__:
					p->wr_PUSH_INTEGER(pcode__PUSH_INTEGER, getCurrentLine()); // write pcode

					*nReturnExpressionType = pcode__INTEGER;
					break;
				case token____MODULE__:
					ac = getModule();
					goto r;
				case token____SCOPE__:
					ac = getScope();
          if (strcmp(ac, "") == 0) ac = "Default Global";
					goto r;
				case token____CLASS__:
					ac = getClass();
					goto r;
				case token____SUB__:
         if (isScopeClass()){
           ac = myClass->getRealNameMethod(myClass->getId(getClass()), myClass->getIdMethod(getClass(), getSub()));
         } else {
           ac = myModule->getRealNameSub(myModule->getId(getModule()), myModule->getIdSub(getModule(), getSub()));
         }
r:
					{
						int nStringLiteral = registerStringLiteral(ac);
 						if (nStringLiteral == 0){ internalError( utility::con(ac, " string literal not declared") ); _ERROR_ }
						p->wr_PUSH_QSTRING(pcode__PUSH_QSTRING, nStringLiteral);			
						
						*nReturnExpressionType = pcode__QSTRING;
					}
					break;
				case token____ISLINUX__: 
         #ifdef LINUX // HIDE
  					p->wr_PUSH_BOOLEAN(pcode__PUSH_BOOLEAN, true); // write pcode // HIDE
         #else // HIDE
  					p->wr_PUSH_BOOLEAN(pcode__PUSH_BOOLEAN, false); // write pcode // HIDE
         #endif // HIDE
 					// UNHIDE p->wr_PUSH_BOOLEAN(pcode__PUSH_BOOLEAN, true); // write pcode
					*nReturnExpressionType = pcode__BOOLEAN;
					break;
				case token____ISWINDOWS__:
         #ifdef WINDOWS // HIDE
  					p->wr_PUSH_BOOLEAN(pcode__PUSH_BOOLEAN, true); // write pcode // HIDE
         #else // HIDE
  					p->wr_PUSH_BOOLEAN(pcode__PUSH_BOOLEAN, false); // write pcode // HIDE
         #endif // HIDE
          // UNHIDE p->wr_PUSH_BOOLEAN(pcode__PUSH_BOOLEAN, false); // write pcode
					*nReturnExpressionType = pcode__BOOLEAN;
					break;
				case token____ISMACOS__:
         #ifdef MAC // HIDE
  					p->wr_PUSH_BOOLEAN(pcode__PUSH_BOOLEAN, true); // write pcode // HIDE
         #else // HIDE
  					p->wr_PUSH_BOOLEAN(pcode__PUSH_BOOLEAN, false); // write pcode // HIDE
         #endif // HIDE
          // UNHIDE p->wr_PUSH_BOOLEAN(pcode__PUSH_BOOLEAN, false); // write pcode
					*nReturnExpressionType = pcode__BOOLEAN;
					break;
				case token____FILE__:
					ac = getCurrentFile();
					{
						int nStringLiteral = registerStringLiteral(ac);
 						if (nStringLiteral == 0){ internalError( utility::con(ac, " string literal not declared") ); _ERROR_ }
						p->wr_PUSH_QSTRING(pcode__PUSH_QSTRING, nStringLiteral);			
						
						*nReturnExpressionType = pcode__QSTRING;
					}
					break;
				case token____ISCLASS__:
					p->wr_PUSH_BOOLEAN(pcode__PUSH_BOOLEAN, isScopeClass()); // write pcode
					*nReturnExpressionType = pcode__BOOLEAN;
					break;
				case token____ISMODULE__:
					p->wr_PUSH_BOOLEAN(pcode__PUSH_BOOLEAN, isScopeModule() && !isScopeDefaultGlobal()); // write pcode
					*nReturnExpressionType = pcode__BOOLEAN;
					break;
				case token____ISSUB__:
					p->wr_PUSH_BOOLEAN(pcode__PUSH_BOOLEAN, isScopeLocal()); // write pcode
					*nReturnExpressionType = pcode__BOOLEAN;
					break;
      }
    
    }

 		parseInfo(p, "parsed MACRO");
 		_DONE_
	}


	_END_
}


/**
[KBASIC][VB][QBASIC]
NAME: COLLECTION
PRINTNAME: Collection
TASK: 
SYNTAX: 
DESC: 
CODE:
EXAMPLES: collection.kbasic
CATEGORY: KEYWORD, CONTROLFLOW, ITERATION
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
/*
bool parser::fCOLLECTION(pcode *p, int nVar, t_scope scope, int *nReturnExpressionType, bool bReturn)
/ *
[*]
[VB]
[*]
[*]
* /
{

	_BEGIN_

  if (!bSilent && bProducePcode){
    p->wr_SEPARATOR(pcode__SEPARATOR, utility::con("fCOLLECTION", getCurrentLine() - 1));
  }


  int mid = 0;

	bool bTerm_SYM_BR_OP = false;
	bool bTerm_SYM_BS_OP = false;
  
  if ((bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP))){}
  if (!bTerm_SYM_BR_OP && !(bTerm_SYM_BS_OP = parseTerm(token__SYM_BS_OP))){ _END_ }

  int nParamCount = 1;

#ifdef KBDEBUG
      if (stopAtLine(12)){
       int i = 3;
       i++;
      }
#endif

  if (nVar && bProducePcode){
    p->wr_PUSH_ID(pcode__PUSH_ID, nVar, scope, false);
  }

  if (fNUMERIC_EXPRESSION(p)){

    switch(*nReturnExpressionType){
      case pcode___collection:
          //mid = pcode___collection__GET1;
          break;
        
      default:
        _END_
        break;
    }

   	if (bProducePcode){
			p->wr_PUSH_INTEGER(pcode__PUSH_INTEGER, nParamCount);
			p->wr_binding_ClassMethod(pcode__binding_CLASSMETHOD, mid, true);
   	}

  } else if (fSTRING_EXPRESSION(p)){

    switch(*nReturnExpressionType){
        case pcode___collection:
          //mid = pcode___collection__GET;
          break;
        
      default:
        _END_
        break;
    }

   	if (bProducePcode){
			p->wr_PUSH_INTEGER(pcode__PUSH_INTEGER, nParamCount);
			p->wr_binding_ClassMethod(pcode__binding_CLASSMETHOD, mid, true);
   	}

  } else _END_


	bool bTerm_SYM_BR_CL = false;
	bool bTerm_SYM_BS_CL = false;

 	if (!(bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL)))){ _END_ }

	parseInfo(p, "parsed COLLECTION");

  _DONE_


    
}*/



