
/*
***************************************************************************
Copyright (C) 2000-2007 KBasic Software.  All rights reserved.

parser_main.cpp
---------------------------------------------------------------------------
READY
19.02.2004 - new header for this file (BN)
***************************************************************************
*/

// TODO1b rollback in builtin/binary.kbasic geht nicht      dim on the fly

// TODO1b screen mit mausx und mausy; und ein textarray?, Sie möchten eine Dateiauswahl in Ihrem Programm haben. Anbei finden Sie ein kleines Programm mit einer Dateiauswahl, aber noch ohne klicken. Dazu müsste ich erst einen neuen Befehl für die Konsole erstellen. Das muss leider bis zur übernächsten Version warten.

/* TODO2

string literal über mehrere zielen mit
"kjlklj"_
""_
"g"_
"gd" 

im scanner zu realiseren


TODO2
Collection
IntegerCollection
long stringcollection

[]
first next
for eách

push fifo, lifo
pop

sort

intern qmap  qptrlist


TODO2
bitarray, bytearray, stringarray, mmplayer(mp3, wav,ogg,mpg,avi), stringlist, paint(drawlines, copybitmaps, sprite,font)
applicationwindow(mainwindow), menubar, toolbar,statusbar,dockwindow

TODO2 QLibrary , QProcess

TODO activex mit QAxBase *

TODO2
mini-datenbank sql-- mit dateien mit qmap primary-key
fieldname, type...

id, 
delete, select, update

TODO2
syntaxhighlighter in strings sql-keywords hervorheben

*/


// TODO2 neues macro  __kbasicversion__,  __builddate__

// TODO3 zeitmessungfunktion bei scanner, parser ausgeben in dosfenster
// TODO3 objects: clone, equals

// TODO3 neues menu bookmark aufgelistet mit dateinamen und zeilennummer
/*
TODO2

dim f as form = downcast(object, form)

dim f as myform = upcast(object, myform), 

cast(o, Integer)
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
// TODO2 namenskollision mit klassenname/-modul und variablenname verhindern, klassenname gewinnt
// auch [] ohne index als array deklaration erlauben
// TODO3 [VB] WithEvents
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

  // TODO3 blockscope, dim muss aktuelle rekursiontiefe mit ablegen, auf interpreterseite wird dann wie sub ein blockscope gehandelt
  // aber nur wenn option kbasic

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
       if (bTerm_COMMON || bTerm_SHARED || bTerm_STATIC || bTerm_GLOBAL){ // TODO2 common, shared, global bedeutung berprfen
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

	 /**/ bool bIDENTIFIER[parser__MAX_DIM];
	 /**/ bool bTerm__[parser__MAX_DIM];
	 /**/ bool bEXPRESSION[parser__MAX_DIM];
	 /**/ bool bTerm_AS[parser__MAX_DIM];
	 /**/ bool bTYPE[parser__MAX_DIM];
	 /**/ pcode *myArrayPcode[parser__MAX_DIM];
	bool bTerm_COMMA = false;
	 /**/ const char *acIdentifier[parser__MAX_DIM];
	 /**/ const char *acType[parser__MAX_DIM];
   /**/ int nLStringLen[parser__MAX_DIM];
	 /**/ int nSize[parser__MAX_DIM];
	const char *acCurrentType = 0;

	 /**/ bool bARRAY[parser__MAX_DIM];
	 /**/ t_array a[parser__MAX_DIM];
	 /**/ int nExpressionType[parser__MAX_DIM];
 	 /**/ bool bTerm_NEW[parser__MAX_DIM];


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
		
		/*
int n1 = defaultType(acIdentifier[nComma]);




const char *ac2 = pcode::pcode_(n1);
const char *ac3 = ac2;
int n2 =findType(ac3);
const char *ac4 =findType(n2);
//acType[nComma] = ac4;
 		  	 //if (bIDENTIFIER[nComma]){ fID_KEYWORD_OR_BUILTIN(&acIdentifier[nComma]);  }
*/

    //#ifdef jkl
		  	 if (bIDENTIFIER[nComma] = fID_KEYWORD_OR_BUILTIN(&acIdentifier[nComma])){ acType[nComma] = findType(findType(pcode::pcode_(defaultType(acIdentifier[nComma])))); bTerm_AS[nComma] = false; bTYPE[nComma] = true; }
		// because the identifier has a suffix $,%,&,#,!, AS <TYPE> is not allowed, already found out

		else if (bIDENTIFIER[nComma] = fID_STRING(&acIdentifier[nComma])){ acType[nComma] = findType(findType(pcode::pcode_(pcode__QSTRING))); bTerm_AS[nComma] = true; bTYPE[nComma] = true; }
		else if (bIDENTIFIER[nComma] = fID_INTEGER(&acIdentifier[nComma])){ acType[nComma] = findType(findType(pcode::pcode_(pcode__INTEGER))); bTerm_AS[nComma] = true; bTYPE[nComma] = true; } // TODO2 create a new method for findTypes(findTypes())
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
/*
			  // globale variable darf hier nicht initalisiert werden
        if (!isScopeDefaultGlobal() && isScopeGlobal() && !isScopeLocal()){
			    bEXPRESSION[nComma] = false;

  		    if (bTerm__[nComma] = parseTerm(token__OP_EQUAL)){
				    {syntaxError(token__DIM, "assignment not allowed for global var"); _ERROR_ }
          }

        } else 
          */
          if (!bTerm_NEW[nComma]){
			    //if (bTerm_STATIC)
          {
				    if (bTerm__[nComma] = parseTerm(token__OP_EQUAL)){
					    if (bARRAY[nComma]){ // array definition
						    {syntaxError(token__DIM, "assignment not allowed for array declaration"); _ERROR_ }
					    } else {

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

		       //   if (fID_ALL(&acIdentifier[0])){
           //     goto r;
           //   } else 
                if (fID_KEYWORD_OR_BUILTIN(&acIdentifier[0])){
//r:
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


	  		  	int nTypes = findType(acCurrentType);
						if (nTypes == 0){ semanticError(token__DIM, utility::con(acCurrentType, " type not defined") ); _ERROR_ }

						if (bEXPRESSION[i]) if (!compatibleType(nTypes, nExpressionType[i])){ semanticError(token__DIM, "incompatible types in assignment"); _ERROR_ }


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
//#endif
	}



  if (!bIDENTIFIER[0]){ syntaxError(token__DIM, "identifier missing or identifier not declared"); _ERROR_ }

	_END_
}
