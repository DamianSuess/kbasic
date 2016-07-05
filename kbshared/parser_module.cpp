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
#include "../kbshared/pcode.h"


// scan sub header
bool parser::fREGISTER_MODULE_SUB()
{

	register int nTest = 0;
	register int nTestPrev = 0;
	bool bRet = true;
	bool bMethodDone = false;
	int nSubStartPos = getTokenPos();
	int nPrevTokenPos = 0;

	do {

		nTest = peekToken();

		if (nTestPrev == token__END && nTest == token__MODULE){
		  setTokenPos(nPrevTokenPos);
			return bMethodDone;
		}

		if (nTestPrev == token__END && nTest == token__FUNCTION){
			nextToken();
			return bMethodDone;
		}
/*
		if (nTestPrev == token__END && nTest == token__DECLARE){
			nextToken();
			return bMethodDone;
		}
*/
		if (nTestPrev == token__END && nTest == token__SUB){
			nextToken();
			return bMethodDone;
		}

		if (nTestPrev == token__MSC_EOL || nTestPrev == token__KB_FILENAME ){
			nSubStartPos = getTokenPos(); // last EOL before sub
		}

		if (bMethodDone == false){

			if ((nTestPrev != token__EXIT 
				&& nTestPrev != token__END 
				&& (nTest == token__FUNCTION || nTest == token__SUB || nTest == token__DECLARE))
			){
				 setTokenPos(nSubStartPos);
 				 bRet = fREGISTER_SUB();
				 bMethodDone = true;
         if (nTest == token__DECLARE) return bMethodDone;
         nTest = peekToken();
			}
		}

		nTestPrev = nTest;
		nPrevTokenPos = getTokenPos();

	} while(proceedParse() && bRet && (bRet = nextToken()));

	return false;
}

// ignore var, will be done later
bool parser::fMODULE_VAR()
{	
  _TBEGIN_

	static /**/ bool bTerm_PRIVATE;// = false;
	static /**/ bool bTerm_PUBLIC;// = false;
	static /**/ bool bTerm_DIM;// = false;

			 if ((bTerm_PRIVATE = parseTerm(token__PRIVATE))){ bTerm_PUBLIC = false; bTerm_DIM = false; } 
	else if ((bTerm_PUBLIC = parseTerm(token__PUBLIC))){ bTerm_PRIVATE = false; bTerm_DIM = false; }
	else if ((bTerm_DIM = parseTerm(token__DIM))){ bTerm_PRIVATE = false; bTerm_PUBLIC = false; }
	
  if (!bTerm_PRIVATE && !bTerm_PUBLIC && !bTerm_DIM){ _TEND_ }    

  switch(peekToken()){
    case token__SUB:
    case token__FUNCTION:
    case token__PROPERTY:
    case token__DECLARE:
    //case token__STRUCTURE:
    case token__TYPE:
    case token__ENUM:
      _TEND_
  }


	// ignore all until EOL or : is reached
  while(proceedParse() && peekToken() != token__MSC_EOL && peekToken() != token__SYM_COLON && nextToken());

	_DONE_

}

bool parser::fMODULE_CONST()
{
	_TBEGIN_

       if (/*bTerm_PRIVATE = */parseTerm(token__PRIVATE)){}
  else if (/*bTerm_PUBLIC = */parseTerm(token__PUBLIC)){}
	
  //bool bTerm_CONST = false;

  if (!(/*bTerm_CONST = */parseTerm(token__CONST))){ _TEND_ }

	// ignore all until EOL or : is reached
  while(proceedParse() && peekToken() != token__MSC_EOL && peekToken() != token__SYM_COLON && nextToken());

	_DONE_

}

/* *
[EXPLANATION]
NAME: MODULE TYPE
DESC:
SEEALSO:
*/
bool parser::fREGISTER_MODULE_TYPE()
{
  return registerAllTypes();
}

/* *
[EXPLANATION]
NAME: MODULE ENUMERATION
DESC:
SEEALSO:
*/
bool parser::fREGISTER_MODULE_ENUM()
{
  return registerAllEnums();
}

bool parser::fREGISTER_MODULE_VAR(pcode *p)
{
	_BEGIN_

	static /**/ bool bTerm_PRIVATE;// = false;
	static /**/ bool bTerm_PUBLIC;// = false;
	static /**/ bool bTerm_DIM;// = false;
	//bool bTerm_STATIC = false; 

			 if (bTerm_PRIVATE = parseTerm(token__PRIVATE)){ bTerm_PUBLIC = false; bTerm_DIM = false; } 
	else if (bTerm_PUBLIC = parseTerm(token__PUBLIC)){ bTerm_PRIVATE = false; bTerm_DIM = false; }
	else if (bTerm_DIM = parseTerm(token__DIM)){ bTerm_PUBLIC = false; bTerm_PRIVATE = false; }

  if (!bTerm_PRIVATE && !bTerm_PUBLIC && !bTerm_DIM){ _END_ }
  
  switch(peekToken()){
    case token__DECLARE:// maybe it's a method
    case token__SUB:// maybe it's a method
    case token__FUNCTION:// maybe it's a method
    case token__PROPERTY:
    //case token__STRUCTURE:
    case token__TYPE:
    case token__ENUM:
    case token__SIGNAL:
    case token__SLOT:
    case token__CONSTRUCTOR:
    case token__DESTRUCTOR:
      _END_
  }

	static /**/ bool bIDENTIFIER[parser__MAX_DIM];
	static /**/ bool bTerm_AS[parser__MAX_DIM];
	static /**/ bool bTerm_NEW[parser__MAX_DIM];
	static /**/ bool bTYPE[parser__MAX_DIM];
	bool bTerm_COMMA = false;
	bool bTerm__ = false;
	static /**/ const char *acIdentifier[parser__MAX_DIM];
	static /**/ const char *acType[parser__MAX_DIM];
	static /**/ int nSize[parser__MAX_DIM];
	const char *acCurrentType = "";

	static /**/ bool bARRAY[parser__MAX_DIM];
	static /**/ t_array a[parser__MAX_DIM];

	int nComma = 0;

	bTerm_AS[nComma] = false;
	bTYPE[nComma] = false;
	bARRAY[nComma] = false;
	bTerm_NEW[nComma] = false;


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

		if (bIDENTIFIER[nComma]){

 		  if (bARRAY[nComma] = fREGISTER_ARRAY_CONST(p, &a[nComma], 0, 0, global)){}

     	if (bTerm__ = parseTerm(token__OP_EQUAL)){
        { semanticError(token__DIM, "expression after DIM not allowed in global declaration scope"); _ERROR_ }
      }

			// check for AS, if %, &, !, # or $ is used, AS is not allowed, type already known
			if (bTerm_AS[nComma] == true && (parseTerm(token__AS))){ semanticError(token__DIM, "type already known, identifier may not stop with %, &, !, # or $"); _ERROR_ }
			if (bTerm_AS[nComma] == false){
				if (bTerm_AS[nComma] = parseTerm(token__AS)){

					if (bTerm_NEW[nComma] = parseTerm(token__NEW)){ semanticError(token__DIM, "NEW after DIM not allowed in global declaration scope"); _ERROR_ }

					if (bTYPE[nComma] = fTYPE(p, &acType[nComma], bTerm_NEW[nComma])){}
					if (bTerm_AS[nComma] && !bTYPE[nComma]){ syntaxError(token__DIM, "type name missing"); _ERROR_ }
				}

			}

     	if (bTerm__ = parseTerm(token__OP_EQUAL)){
        { semanticError(token__DIM, "expression after DIM not allowed in global declaration scope"); _ERROR_ }
      }

		  if (bTerm_COMMA = parseTerm(token__SYM_COMMA)){
				nComma++;
			} else {

				{

					for (int i = nComma; i >= 0; i--){

						if (bTYPE[i] == true){
							acCurrentType = (char *) acType[i];
						}

	  		  	int nTypes = findType(acCurrentType);
						if (nTypes == 0){ semanticError(token__DIM, utility::con(acCurrentType, " type not defined") ); _ERROR_ }

           // var und global var name müssen eindeutig sein
           if (bTerm_PUBLIC){
	            if (myModule->first()){
		            do {
                  int nModuleId = myModule->getId();
                  const char *acModuleName = myModule->getName(nModuleId);

                  if (findModulePublicVar(acModuleName, acIdentifier[i]) > 0){ semanticError(token__DIM, utility::con(utility::ident(acDefaultModuleName, acIdentifier[i]), " already declared AS PUBLIC at some place") ); _ERROR_ }

		            } while (myModule->next());
	            }
           /*
             } else {
               if (findModuleVar(acDefaultModuleName, acIdentifier[i]) > 0){ semanticError(token__DIM, utility::con(utility::ident(getModule(), acIdentifier[i]), " already declared AS PUBLIC") ); _ERROR_ }
             }
             */
           }
           int nTypeSize = 0;
           if (nTypes == pcode__LQSTRING || nTypes == pcode__LCSTRING) nTypeSize = nSize[i];

           int nVar = registerModuleVar(getModule(), acIdentifier[i], nTypes, &a[i], bTerm_PRIVATE ? token__PRIVATE : bTerm_PUBLIC ? token__PUBLIC : bTerm_DIM ? token__PUBLIC : token__PROTECTED, nTypeSize);
 					  if (nVar == 0){ semanticError(token__DIM, utility::con(utility::ident(getModule(), acIdentifier[i]), " already declared at some place") ); _ERROR_ }


						if (bProducePcode){     

             p->wr_DIM(pcode__DIM, nVar, getScopeCode(), nTypes, false, false, bARRAY[i], false, nTypeSize, 0, "", false); // write pcode
						}

           parseInfo(p,  utility::con("parsed MODULE DIM", acIdentifier[i], "") );

					}

					_DONE_


				}
				break;
			}
		} else break;
	}

	// no error, maybe it's a method
 // if (!bIDENTIFIER[0]){ syntaxError("identifier missing or identifier not declared"); _ERROR_ }


	_END_
}

bool parser::fREGISTER_MODULE_CONST(pcode *p)
{
	_BEGIN_

	static /**/ bool bTerm_PRIVATE;// = false;
	static /**/ bool bTerm_PUBLIC;// = false;

			 if (bTerm_PRIVATE = parseTerm(token__PRIVATE)){ bTerm_PUBLIC = false; } 
	else if (bTerm_PUBLIC = parseTerm(token__PUBLIC)){ bTerm_PRIVATE = false; }
	
  if (!bTerm_PRIVATE && !bTerm_PUBLIC){ bTerm_PUBLIC = true; }

	//bool bTerm_CONST = false;

  if (!(/*bTerm_CONST = */parseTerm(token__CONST))){ _END_ }

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
      if (bEXPRESSION[nComma] = fCONST_EXPRESSION(p, &nExpressionType)) if (bEXPRESSION[nComma] && !memory_type::scalar(nExpressionType)){ semanticError(token__CONST, "CONST must be of type BYTE, CURRENCY, DATE, INTEGER, LONG, BOOLEAN, SINGLE, DOUBLE or STRING"); _ERROR_ }
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

				 if (!bIDENTIFIER[nComma]){ syntaxError(token__CONST, "identifier missing or identifier not declared"); _ERROR_ }
		else if (!bTerm__){ syntaxError(token__CONST, "= missing"); _ERROR_ }
	  else if (!bEXPRESSION[nComma]){ syntaxError(token__CONST, "const expression missing"); _ERROR_ }

	  if (bTerm_COMMA = parseTerm(token__SYM_COMMA)){
			nComma++;
		} else {

			for (int i = nComma; i >= 0; i--){

    		int nVar = registerModuleConst(getModule(), acIdentifier[i], bTerm_PUBLIC);
    		if (nVar == 0){ semanticError(token__CONST, utility::con(utility::ident(getModule(), acIdentifier[i]), " already declared at some place") ); _ERROR_ }

     		if (bProducePcode){           
           p->wr_CONST(pcode__CONST, nVar, getScopeCode());
      		 p->wr_MOV_CONST(pcode__MOV_CONST, nVar, getScopeCode()); // write pcode
     		}

     		parseInfo(p, utility::con("parsed MODULE CONST", acIdentifier[i], "") );

			}

   		return true;

 		}
	}

	_END_
}


// scan module header
bool parser::fREGISTER_MODULE()
{
	_TBEGIN_

	//_SCANBEGIN_

  if (fEOLREM());
  if (fEOF2());
  if (fVERSION());
  if (fFILENAME());  

	static /**/ bool bTerm_PRIVATE;// = false;
	static /**/ bool bTerm_PUBLIC;// = false;

			 if (bTerm_PRIVATE = parseTerm(token__PRIVATE)){ bTerm_PUBLIC = false; } 
	else if (bTerm_PUBLIC = parseTerm(token__PUBLIC)){ bTerm_PRIVATE = false; }

	if (!(/*bTerm_MODULE = */parseTerm(token__MODULE))){ _TEND_ }

	bool bTerm_MODULE = false;

	bool bIDENTIFIER = false;
	bool bIDENTIFIER2 = false;
	//bool bTerm_EXTENDS = false;
	bool bTerm_THROWS = false;
	bool bREM = false;
	bool bEOL = false;
	const char *acModule;
	//pcode *p = 0;
	
	bool bTerm_COMMA = false;
	bool bTerm_END = false;
	int nClass = 0;

	if (bIDENTIFIER = fID_KEYWORD_OR_BUILTIN(&acModule)){
    static int nAgainstPointerLoss = 0;
    if (nAgainstPointerLoss >= 1024) _TEND_
    static XString sAgainstPointerLoss[1024];
    sAgainstPointerLoss[nAgainstPointerLoss] = acModule;
    acModule = sAgainstPointerLoss[nAgainstPointerLoss++].ascii();

  	if (myModule->registered(acModule)){ semanticError(token__KEYWORD, utility::con(acModule, " module already declared at some place")); _TERROR_ }

    parseInfo(0, utility::con("------ MODULE ", acModule, " ------ ") );

    if ((bEOL = fEOLREM())){

      if (classExists(acModule)){ semanticError(token__KEYWORD, utility::con(acModule, ": The name already exists as a class. Rename your module.") ); _TERROR_ }
			int nId = registerModule(acModule);//, p);
      if (nId == 0){ semanticError(token__KEYWORD, utility::con(acModule, " module already declared at some place") ); _TERROR_ }
			
      setScopeModule(acModule);

			do {
			
				if (proceedParse()){

					     if (fREGISTER_MODULE_CONST(myPcode)){ continue; } // attention! const before var
					else if (fREGISTER_MODULE_VAR(myPcode)){ continue; }

          else if (fREGISTER_MODULE_ENUM()){ continue; } // myPcode as pcode
					else if (fREGISTER_MODULE_TYPE()){ continue; } // myPcode as pcode
					//else if (fREGISTER_MODULE_STRUCTURE()){ continue; } // myPcode as pcode

          else if (fREM()){ continue; }
					else if (fEOL(false)){ continue; }
					else if (fCOL(false)){ continue; }
					else if (fOPTION(0)){ continue; }

					else if (fREGISTER_MODULE_SUB()){ continue; } // must be the last!! - myPcode as pcode (only library bindings use it)
					else {
						if (bTerm_END = parseTerm(token__END))
						if (bTerm_MODULE = parseTerm(token__MODULE)){}            
						break;
					}
					
				}

      } while (proceedParse());
	
      setScopeDefaultGlobal();

					 if (!bTerm_END){ syntaxError(token__MODULE, "missing END"); _TERROR_ }
			else if (!bTerm_MODULE){ syntaxError(token__MODULE, "missing MODULE"); _TERROR_ }



			
		}

  	if (!bIDENTIFIER){ syntaxError(token__MODULE, "module name missing"); _TERROR_ }
		if (!bEOL){ syntaxError(token__MODULE, "EOL missing"); _TERROR_ }

		parseInfo(0, utility::con("registered MODULE ", acModule) );

	//	_SCANEND_

		return true;
  }

	
	_TEND_
}

/* *
[EXPLANATION]
NAME: MODULE
DESC:
SEEALSO:
*/
// module body
bool parser::fMODULE_BODY()
{
  _TBEGIN_

	//bool bTerm_MODULE = false;

	if (/*bTerm_MODULE = */parseTerm(token__MODULE)){    

	  bool bIDENTIFIER = false;
    const char *acIdentifier = "";

		if (bIDENTIFIER = fID_KEYWORD_OR_BUILTIN(&acIdentifier)){

	    bool bEOL = false;
	    bool bSTATEMENTSEQUENCE = false;
	    bool bTerm_END = false;
	    bool bTerm_MODULE2 = false;

			if (!(bEOL = fEOLREM())){ syntaxError(token__MODULE, "EOL missing"); goto exit; }

      setScopeModule(acIdentifier);

      do {

  			      if (fREM()){}   
              
          else if (fOPTION(0)){} 

		      else if (fDEFINT());
		      else if (fDEFLNG());
		      else if (fDEFSNG());
		      else if (fDEFDBL());
		      else if (fDEFSTR());
		      else if (fDEFBOOL());
		      else if (fDEFBYTE());
		      else if (fDEFOBJ());
		      else if (fDEFVAR());
		      else if (fDEFCUR());
		      else if (fDEFDATE());

      // HINT eigentlich müsste jedes module diese def.... deklaration erlauben, da es aber obsolete ist, wird wohl keiner was merken, def... in einer einzelnen datei geht
      // HINT nur für parser relevant
        
        else if (fEOL(false)){} // parse stand-alone EOL's - ATTENTION must be the last PRODUCTION of all here!
				else if (fCOL(false)){} // parse stand-alone EOL's - ATTENTION must be the last PRODUCTION of all here!

				else {
					break;
				}

	    } while (proceedParse());


      do {

  			      if (fREM()){}                

        else if (fMODULE_VAR()){} // already parsed
  			else if (fMODULE_CONST()){} // already parsed

        else if (fSUB_BODY()); // parse body

        else if (fTYPE_BODY()); // already parsed
        else if (fENUM_BODY()); // already parsed
        //else if (fSTRUCTURE_BODY()); // already parsed

        else if (fEOL(false)){} // parse stand-alone EOL's - ATTENTION must be the last PRODUCTION of all here!
				else if (fCOL(false)){} // parse stand-alone EOL's - ATTENTION must be the last PRODUCTION of all here!

				else {
			    if (bTerm_END = parseTerm(token__END))
					if (bTerm_MODULE2 = parseTerm(token__MODULE)){}
					if (!bTerm_END || !bTerm_MODULE2){ syntaxError(token__MODULE, "END MODULE missing"); goto exit; }
           
					break;
				}

	    } while (proceedParse());

     setScopeDefaultGlobal();

			parseInfo(0, "parsed MODULE");
			_DONE_
		}

		if (!bIDENTIFIER){ syntaxError(token__MODULE, "module name missing"); goto exit; }

	}

exit:
  setScopeDefaultGlobal();
	_TEND_
}

bool parser::fMODULENAME(pcode *p, const char **acIdentifier)
{
	_BEGIN_

	if (fID_KEYWORD_OR_BUILTIN(acIdentifier, false)){

   if (myModule->exist(*acIdentifier) > 0) _DONE_

  }

  _END_
}


