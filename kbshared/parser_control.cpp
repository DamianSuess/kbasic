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



/**
[KBASIC][VB][QBASIC]
NAME: IF
PRINTNAME: If
TASK: single decision possibility
SYNTAX: 
IF <condition> THEN <statementSequence> ELSE: <statementSequence>

IF <condition> THEN
<statementSequence>
ELSEIF <condition> THEN
<statementSequence>
ELSE
<statementSequence>
END IF

if EXPR then STATEMENT { : STATEMENT } { : else STATEMENT }
if EXPR then LINENUM
if EXPR

DESC: 
The IF statement. If the condition is true then the statements after the THEN are
executed and the statements after the ELSE are skipped. If the condition is false then
the statements after the "else" are executed instead. If the item after "then" is a line
number then a goto is executed. If the condition is true and there is no THEN
statement on the same line, statements are executed until a line with an END IF is
found.
Single-line conditional.
IF <expression> THEN
...
ELSE
...
ELSEIF
...
END IF
Multi-line conditional.
Command: ELSE
ELSE introduces a default condition in a multi-line IF statement.
Command: ELSEIF
ELSEIF introduces a secondary condition in a multi-line IF statement.
Command: END IF
END IF ends a multi-line IF statement.

Command: IF expression THEN [statement [ELSE statement]]

IF evaluates 'expression' and performs the THEN statement if it is true or (optionally)
the ELSE statement if it is FALSE. KBasic allows multi-line IF statements with ELSE and
ELSEIF cases, ending with END IF.
This works as zero is interpreted to be FALSE and any non-zero is interpreted to be
TRUE

CODE:
DIM i AS INTEGER
DIM n AS INTEGER
IF i <> 1 THEN
n = 11111
ELSEIF i = 2 * 10 THEN
n = 22222
ELSE
n = 33333
END IF

EXAMPLES: if.kbasic
CATEGORY: KEYWORD, CONTROLFLOW, DECISION
SEEALSO: ONGOSUB, ONGOTO, SELECTCASE
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
/**
[KEYWORD]
NAME: THEN
PRINTNAME: Then
SEEALSO: IF
VERSION: PERSONAL, PROFESSIONAL
*/
/**
[KBASIC][VB][QBASIC]
NAME: ELSE
PRINTNAME: Else
SEEALSO: IF
VERSION: PERSONAL, PROFESSIONAL
*/
/**
[KBASIC][VB][QBASIC]
NAME: ELSEIF
PRINTNAME: ElseIf
SEEALSO: IF
VERSION: PERSONAL, PROFESSIONAL
*/
bool parser::fIF(pcode *p)
/*
[QBASIC]
[VB]
[VBNET]
[KBASIC]
*/
{

	//register bool bTerm_IF = false;

  _BEGIN_

  if (!(/*bTerm_IF = */parseTerm(token__IF))){ _END_ } // to optimize, the 'if' is one of the first statements

  bGLOBAL_EOL = false;
	

  if (!bSilent && bProducePcode){
     p->wr_SEPARATOR(pcode__SEPARATOR, utility::con("fIF", getCurrentLine() - 1));
  }

	bool bCONDITION_THEN = false;

	bool bTerm_THEN = false;
	bool bSTATEMENTSEQUENCE_THEN = false;
	bool bEOL_THEN = false;
	bool bREM = false;
	int nPcodeOffset_THEN = 0;
	int nPcodeOffset_THEN_AFTER = 0;

	bool bTerm_ELSEIF[parser__MAX_ELSEIF];
	bool bCONDITION_ELSEIF[parser__MAX_ELSEIF];
	bool bTerm_ELSEIF_THEN[parser__MAX_ELSEIF];
	bool bSTATEMENTSEQUENCE_ELSEIF[parser__MAX_ELSEIF];
	bool bEOL_ELSEIF[parser__MAX_ELSEIF];
	int nPcodeOffset_ELSEIF_BEFORE[parser__MAX_ELSEIF];
	int nPcodeOffset_ELSEIF[parser__MAX_ELSEIF];
	int nPcodeOffset_ELSEIF_AFTER[parser__MAX_ELSEIF];
	int nElseIf = 0;

	bool bTerm_ELSE = false;
	bool bSTATEMENTSEQUENCE_ELSE = false;
	bool bEOL_ELSE = false;
	int nPcodeOffset_ELSE = 0;

	bool bTerm_ENDIF = false;
	bool bTerm_END = false;
	int nPcodeOffset_ENDIF = 0;
	int nExpressionType;
   
  bool bParseAdditionalEOL = false;
	bool bEOL_THEN2 = false;

  bool bSAVE = bGLOBAL_EOL;
  bool bSAVE2 = bGLOBAL_EOL;

  bGLOBAL_EOL = false;

#ifdef KBDEBUG
  if (stopAtLine(133)){
    int i = 9;
    i++;
  }
#endif

  nIfStatement++;

	if (bCONDITION_THEN = fCONDITION(p, &nExpressionType)){
		if (bProducePcode){

			nPcodeOffset_THEN = p->getPos(); // save the position of the CJMP pcode, later the destination will be overwritten
			p->wr_CJMP(pcode__CJMP, 0, true); // write pcode

		}
		if (bTerm_THEN = parseTerm(token__THEN))
			if (((bEOL_THEN = fEOL()) || (bEOL_THEN = bREM = fREM()))){} // EOL is optional

    bSAVE = bGLOBAL_EOL;
		bool bOk = false;
		 // statement in one line, many statements in following lines, no statements in the following lines
		if (bEOL_THEN == false && (bParseAdditionalEOL = bSTATEMENTSEQUENCE_THEN = fSTATEMENTSEQUENCEONELINE(p))) bOk = true;
		else if (bSTATEMENTSEQUENCE_THEN = fSTATEMENTSEQUENCE(p, false, false, true)) bOk = true;
		else if (bEOL_THEN) bOk = true;

    if (bParseAdditionalEOL){
      bEOL_THEN2 = true;
      bGLOBAL_EOL = bSAVE;

      _BEGIN2_        
      if (fEOL()){
        while(fREM()){ // eat appended REM
        }
        if (parseTerm(token__ELSEIF)){
          _END2_
          fEOL();
        } else {
          _END2_
        }
      }
      bGLOBAL_EOL = bSAVE;
    }

		if (!bEOL_THEN && !bSTATEMENTSEQUENCE_THEN){

			if (fGOTO(p, false)){ // special THEN line or THEN label
				bOk = true;
        bEOL_THEN2 = true;
			} else {
				syntaxError(token__IF, "THEN statement(s) missing"); _ERROR_
			}
		}

		if (bOk){

			if (bProducePcode){

				nPcodeOffset_THEN_AFTER = p->getPos(); // save the position of the CJMP pcode, later the destination will be overwritten
				p->wr_JMP(pcode__JMP, 0); // write pcode

			}

			do {

			 	if (nElseIf >= parser__MAX_ELSEIF){ internalError("too many ELSEIF"); _ERROR_ }

				if (bTerm_ELSEIF[nElseIf] = parseTerm(token__ELSEIF)){
				 	if (!bEOL_THEN && !bEOL_THEN2){ syntaxError(token__IF, "EOL missing after THEN"); _ERROR_ }

					if (bProducePcode){

						nPcodeOffset_ELSEIF_BEFORE[nElseIf] = p->getPos(); // save the position of the CJMP pcode, later the destination will be overwritten

					}
					if (bCONDITION_ELSEIF[nElseIf] = fCONDITION(p, &nExpressionType))
					if (bTerm_ELSEIF_THEN[nElseIf] = parseTerm(token__THEN)){
						if (bProducePcode){

							nPcodeOffset_ELSEIF[nElseIf] = p->getPos(); // save the position of the CJMP pcode, later the destination will be overwritten
							p->wr_CJMP(pcode__CJMP, 0, false); // write pcode

						} 

            bSAVE = bGLOBAL_EOL;
            bEOL_ELSEIF[nElseIf] = false;
						if ((fREM()) || (bEOL_ELSEIF[nElseIf] = fEOL()) || true) // EOL is optional
						if ((bEOL_ELSEIF[nElseIf] == false && (bParseAdditionalEOL = bSTATEMENTSEQUENCE_ELSEIF[nElseIf] = fSTATEMENTSEQUENCEONELINE(p))) || (bSTATEMENTSEQUENCE_ELSEIF[nElseIf] = fSTATEMENTSEQUENCE(p)) || bEOL_ELSEIF[nElseIf]){ // statement in one line, many statements in following lines, no statements in the following lines
              if (bParseAdditionalEOL){
                fEOL(); // needed for   elseif true then print "full=face"
              }
              bGLOBAL_EOL = bSAVE;

							if (!bEOL_ELSEIF[nElseIf] && !bSTATEMENTSEQUENCE_ELSEIF[nElseIf]){ syntaxError(token__IF, "ELSEIF statement(s) missing"); _ERROR_ }

							if (bProducePcode){

								nPcodeOffset_ELSEIF_AFTER[nElseIf] = p->getPos(); // save the position of the CJMP pcode, later the destination will be overwritten
								p->wr_JMP(pcode__JMP, 0); // write pcode

							}
						}

						if (bTerm_ELSEIF[nElseIf]){
									 if (!bCONDITION_ELSEIF[nElseIf]){ syntaxError(token__IF, "ELSEIF condition missing"); _ERROR_ }
							else if (!bTerm_ELSEIF_THEN[nElseIf]){ syntaxError(token__IF, "ELSEIF THEN missing"); _ERROR_ }
						}
					}
					nElseIf++;
				} else {
					bTerm_ELSEIF[nElseIf] = false;
					break;
				}

			} while (bTerm_ELSEIF[nElseIf - 1]);

			if (bTerm_ELSE = parseTerm(token__ELSE)){

        fREM(false);

#ifdef KBDEBUG
  if (stopAtLine(106)){
    int i = 9;
    i++;
  }
#endif
				if (bProducePcode){
					nPcodeOffset_ELSE = p->getPos(); // save the position of the CJMP pcode, later the destination will be overwritten
				}

        bSAVE = bGLOBAL_EOL;
				if ((bEOL_ELSE = fEOL()) || true) // EOL is optional
			  if ((bEOL_ELSE == false && (bParseAdditionalEOL = bSTATEMENTSEQUENCE_ELSE = fSTATEMENTSEQUENCEONELINE(p))) || (bSTATEMENTSEQUENCE_ELSE = fSTATEMENTSEQUENCE(p)) || bEOL_ELSE){} // statement in one line, many statements in following lines, no statements in the following lines
          
        if (bParseAdditionalEOL){
          fEOL(); // needed for   else print "full=face"
        }
        bGLOBAL_EOL = bSAVE;

				if (bTerm_ELSE){
					if (!bEOL_ELSE && !bSTATEMENTSEQUENCE_ELSE){ syntaxError(token__IF, "ELSE statement(s) missing"); _ERROR_ }
				}
			}

      while(fREM()){ // eat appended REM
      }


      bool bb = false;
			if (
        (bEOL_THEN == false && bEOL_ELSE == false && (bEOL_THEN2/* == false */&& (bGLOBAL_EOL == false))))
      {
        bb = true;

      }

      if ((bb && !(bEOL_THEN2 && bGLOBAL_EOL == false)) || ( ((nIfStatement == 1 || bGLOBAL_EOL) && (bTerm_ENDIF = parseTerm(token__ENDIF)))
				|| ( ((nIfStatement == 1 || bGLOBAL_EOL) && (bTerm_END = bTerm_ENDIF = parseTerms(token__END, token__IF))) ) ) || bb || (bGLOBAL_EOL && nElseIf))
			{
			 	if (!bEOL_THEN && !bEOL_THEN2 && bTerm_ENDIF){ syntaxError(token__IF, "ENDIF (END IF) not allowed in only one line if statement without THEN"); _ERROR_ }
				if (bProducePcode){
					nPcodeOffset_ENDIF = p->getPos();

					if (bTerm_ELSEIF[0]){
						for(int i = 0; nElseIf > 0 && i < nElseIf; i++){

							if (bTerm_ELSEIF[i]){
								if (i == 0){
									p->setPos(nPcodeOffset_THEN);	p->wr_CJMP(pcode__CJMP, nPcodeOffset_ELSEIF_BEFORE[i], true); // write pcode, new jump destination
								}
								p->setPos(nPcodeOffset_THEN_AFTER);	p->wr_JMP(pcode__JMP, nPcodeOffset_ENDIF); // write pcode, new jump destination

								if (i + 1 < nElseIf){
									p->setPos(nPcodeOffset_ELSEIF[i]); p->wr_CJMP(pcode__CJMP, nPcodeOffset_ELSEIF_BEFORE[i + 1], true); // write pcode, new jump destination
								} else {
									if (bTerm_ELSE){
										p->setPos(nPcodeOffset_ELSEIF[i]);	p->wr_CJMP(pcode__CJMP, nPcodeOffset_ELSE, true); // write pcode, new jump destination
									} else {
										p->setPos(nPcodeOffset_ELSEIF[i]); p->wr_CJMP(pcode__CJMP, nPcodeOffset_ENDIF, true); // write pcode, new jump destination
									}
								}

								p->setPos(nPcodeOffset_ELSEIF_AFTER[i]);	p->wr_JMP(pcode__JMP, nPcodeOffset_ENDIF); // write pcode, new jump destination

							}

							p->setPos(nPcodeOffset_ENDIF);
						}
					} else {
						if (bTerm_ELSE){
							p->setPos(nPcodeOffset_THEN);	p->wr_CJMP(pcode__CJMP, nPcodeOffset_ELSE, true); // write pcode, new jump destination
							p->setPos(nPcodeOffset_THEN_AFTER);	p->wr_JMP(pcode__JMP, nPcodeOffset_ENDIF); // write pcode, new jump destination
						} else {
							p->setPos(nPcodeOffset_THEN);	p->wr_CJMP(pcode__CJMP, nPcodeOffset_ENDIF, true); // write pcode, new jump destination
							p->setPos(nPcodeOffset_THEN_AFTER);	p->wr_JMP(pcode__JMP, nPcodeOffset_ENDIF); // write pcode, new jump destination
						}
						p->setPos(nPcodeOffset_ENDIF);
					}

				}
						 if (bTerm_ELSEIF[0] && bTerm_ELSE && bTerm_ENDIF) parseInfo(p, "parsed IF..THEN..ELSEIF..ELSE..ENDIF");
				else if (bTerm_ELSEIF[0] && bTerm_ELSE) parseInfo(p, "parsed IF..THEN..ELSEIF..ELSE..");
				else if (bTerm_ELSEIF[0] && bTerm_ENDIF) parseInfo(p, "parsed IF..THEN..ELSEIF..ENDIF");
				else if (bTerm_ELSEIF[0]) parseInfo(p, "parsed IF..THEN..ELSEIF");
				else if (bTerm_ELSE && bTerm_ENDIF) parseInfo(p, "parsed IF..THEN..ELSE..ENDIF");
				else if (bTerm_ELSE) parseInfo(p, "parsed IF..THEN..ELSE..");
				else if (bTerm_ENDIF) parseInfo(p, "parsed IF..THEN..ENDIF");
				else parseInfo(p, "parsed IF..THEN..");


        nIfStatement--;

        bGLOBAL_EOL = bSAVE2;

				_DONE_
			}
		}
	}

	
  {
				 if (!bCONDITION_THEN){ syntaxError(token__IF, "condition expression missing"); _ERROR_ }
		else if (!bTerm_THEN){ syntaxError(token__IF, "THEN missing"); _ERROR_ }
		else if (!bSTATEMENTSEQUENCE_THEN){ syntaxError(token__IF, "" /*THEN statement(s) missing*/); _ERROR_ }
		else if (!bTerm_ENDIF){ syntaxError(token__IF, ""/*ENDIF missing*/); _ERROR_ }
	}

  nIfStatement--;

  bGLOBAL_EOL = bSAVE2;
	_END_
}

/*
SELECT CASE i
nPcodeOffset_CASE_BEFORE: <-- jumped from the previous CASE
	CASE 0
nPcodeOffset_CASE --> jump to the next case (nPcodeOffset_CASE_BEFORE), if condition false
		n = 0
nPcodeOffset_CASE_AFTER: --> jump to END SELECT
	CASE 1, 2
		n = 1122
	CASE IS > 10
		n = 9999
nPcodeOffset_CASEELSE: <-- jumped from the last CASE
	CASE ELSE
		n = 999999
nPcodeOffset_ENDSELECT: <-- jumped from if a case condition has been true
END SELECT

/**
[QBASIC][VB][KBASIC]
NAME: SELECTCASE
PRINTNAME: Select Case
TASK: Multi-line conditional selection statement.
SYNTAX: 
SELECT CASE <expression>
CASE <expression>
<statementSequence>
CASE ELSE
<statementSequence>
END SELECT

DESC: 
The SELECT CASE statement is much more complicated than the IF statement:

In many occasions, you may want to compare the same variable (or
expression) with many different values, and execute a different piece of code
depending on which value it equals to. This is exactly what the SELECT CASE statement
is for.

SELECT CASE introduces a multi-line conditional selection statement. The expression
given as the argument to SELECT CASE will be evaluated by CASE statements following.
The SELECT CASE statement concludes with an END SELECT statement. As currently
implemented, CASE statements may be followed by string values, in this case complex
expression can be performed.

Multi-way branch. Executes the statements after the CASE statement which matches
the SELECT CASE expression, then skips to the END SELECT statement. If there is no
match, and a CASE ELSE statement is present, then execution defaults to the
statements following the CASE ELSE.

CASE introduces an element of a SELECT CASE statement (see SELECT CASE). CASE
introduces a conditional SELECT CASE element, and CASE ELSE introduces a default
SELECT CASE element.
Begin a multi-way decision block and establish the test expression that subsequent
CASE statements test against. The test expression can be TRUE, FALSE, or a numeric or
string expression.
Each expression in the subsequent CASE statements is tested against the test
expression. If any expression matches the test expression, the statements following the
CASE statement are executed and then jumps to after the END SELECT statement.
To match TRUE requires a non-zero number or a non-empty string. To match FALSE
requires a zero number or an empty string. To match expression requires an equal
numeric value or string.
SELECT CASE blocks are called one-of-many decision blocks because at most one CASE
statement block is executed. This occurs because an invisible jump past the matching
END SELECT is inserted before every CASE statement except the first.
END SELECT marks the end of every SELECT CASE block.

DIM i AS DOUBLE
DIM n AS INTEGER
i = 4
SELECT CASE i
CASE 0
n = 0
CASE 1, 2
n = 1122
CASE 4 TO 10
n = 441000
CASE IS = 9
n = 9999
CASE ELSE
n = 999999
END SELECT

EXAMPLES: selectcase.kbasic
CATEGORY: KEYWORD, CONTROLFLOW, DECISION
SEEALSO: IF
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
/**
[QBASIC][VB][KBASIC]
NAME: CASE
PRINTNAME: Case
SEEALSO: SELECTCASE
VERSION: PERSONAL, PROFESSIONAL
*/
bool parser::fSELECTCASE(pcode *p)
/*
[QBASIC]
[VB]
[*]
[KBASIC]
*/
{

	//register bool bTerm_SELECT = false;

  _BEGIN_

  if (!(/*bTerm_SELECT = */parseTerm(token__SELECT))){ _END_ } 

	

  if (!bSilent && bProducePcode){
    p->wr_SEPARATOR(pcode__SEPARATOR, utility::con("fSELECTCASE", getCurrentLine() - 1));
  }

	bool bEXPRESSION_COMPARE = false;
	bool bEOL_COMPARE = false;
	bool bREM = false;

	bool bTerm_CASE[parser__MAX_CASE];
	bool bTerm_CASECOMMA[parser__MAX_CASE];
	bool bEXPRESSION_CASE[parser__MAX_CASE];
	bool bEOL_CASE[parser__MAX_CASE];
	bool bSTATEMENTSEQUENCE_CASE[parser__MAX_CASE];
	int nPcodeOffset_CASE_BEFORE[parser__MAX_CASE];
	int nPcodeOffset_CASE[parser__MAX_CASE];
	int nPcodeOffset_CASE_AFTER[parser__MAX_CASE];
	int nCase = 0;

	bool bTerm_CASEELSE = false;
	bool bTerm_IS = false;
	bool bSYM_COMMA = false;
	bool bTerm__ = false;
	bool bSTATEMENTSEQUENCE_CASEELSE = false;
	bool bEOL_CASEELSE = false;
	bool bTO = false;
	int nPcodeOffset_CASEELSE = 0;
	int nPcodeOffset_TO_LEFT = 0;
	int nPcodeOffset_TO_RIGHT = 0;
	int nPcodeOffset_TO_AFTER = 0;
	int nPcodeOffset_TO_AFTER2 = 0;
	int nPcodeOffset_CASEELSE_AFTER = 0;  

	int nPcodeOffset_COMMA[parser__MAX_CASECOMMA]; //  e.g. case 15, 24, 34, 45
	int nCaseComma = 0;

	bool bTerm_END = false;
	bool bTerm_ENDSELECT = false;
	int nPcodeOffset_ENDSELECT = 0;
	int nOP = 0;
	int n;
	int nExpressionTypeCompare;
	int nExpressionType;


  if (parseTerm(token__CASE));

	if (bEXPRESSION_COMPARE = fEXPRESSION(p, &nExpressionTypeCompare))
    if (!(bEOL_COMPARE = fEOL()) || (bEOL_COMPARE = bREM = fREM())){
		     { syntaxError(token__SELECT, "carriage return (EOL) missing"); _ERROR_ }
    }
    do {} while ((bEOL_COMPARE = fEOL()) || (bEOL_COMPARE = bREM = fREM()));
  
   {

		do {

		 	if (nCase >= parser__MAX_CASE){ internalError("too many CASE"); _ERROR_ }

      if ((bEOL_COMPARE = fEOL()) || (bEOL_COMPARE = bREM = fREM())){}

			if (bTerm_CASE[nCase] = parseTerm(token__CASE)){ // CASE XYZ...

        bTerm_CASECOMMA[nCase] = false;

				if (bTerm_CASEELSE = parseTerm(token__ELSE)){ // CASE ELSE
					if (nCase == 0){ syntaxError(token__SELECT, "at least one normal CASE missing"); _ERROR_ } // at least one normal case is needed
					break; // this means CASE ELSE
				}

				if (bProducePcode){

					nPcodeOffset_CASE_BEFORE[nCase] = p->getPos(); // entry point for the previous jump, save the position of the CJMP pcode, later the destination will be overwritten

				}

				if (bTerm_IS = parseTerm(token__IS)){ // CASE IS

							 if (bTerm__ = parseTerm(token__OP_EQUAL)) nOP = token__OP_EQUAL;
					else if (bTerm__ = parseTerm(token__OP_UNEQUAL)) nOP = token__OP_UNEQUAL;
					else if (bTerm__ = parseTerm(token__OP_GREATER)) nOP = token__OP_GREATER;
					else if (bTerm__ = parseTerm(token__OP_GREATER_EQUAL)) nOP = token__OP_GREATER_EQUAL;
					else if (bTerm__ = parseTerm(token__OP_LESSER_EQUAL)) nOP = token__OP_LESSER_EQUAL;
					else if (bTerm__ = parseTerm(token__OP_LESSER)) nOP = token__OP_LESSER;

					if (bTerm__){

						if (bEXPRESSION_CASE[nCase] = fEXPRESSION(p, &nExpressionType)){ // first store the expression, then the operator!

							if (!compatibleType(nExpressionTypeCompare, nExpressionType)){ semanticError(token__SELECT, "incompatible types"); _ERROR_ }

							if (bProducePcode){
										 if (nOP == token__OP_EQUAL) p->wr_EQUAL(pcode__EQUAL, false); // write pcode
								else if (nOP == token__OP_UNEQUAL) p->wr_UNEQUAL(pcode__UNEQUAL, false); // write pcode
								else if (nOP == token__OP_GREATER) p->wr_GREATER(pcode__GREATER, false); // write pcode
								else if (nOP == token__OP_GREATER_EQUAL) p->wr_GREATER_EQUAL(pcode__GREATER_EQUAL, false); // write pcode
								else if (nOP == token__OP_LESSER_EQUAL) p->wr_LESSER_EQUAL(pcode__LESSER_EQUAL, false); // write pcode
								else if (nOP == token__OP_LESSER) p->wr_LESSER(pcode__LESSER, false); // write pcode

								nPcodeOffset_CASE[nCase] = p->getPos(); // save the position of the CJMP pcode, later the destination will be overwritten
								p->wr_CJMP(pcode__CJMP, 0, true); // write pcode

							}
						} else {
							 syntaxError(token__SELECT, "expression missing after IS"); _ERROR_
						}

          } else {
						syntaxError(token__SELECT, "=, <>, <, >, <= or >= missing"); _ERROR_
					}

				} else {
					if (bEXPRESSION_CASE[nCase] = fEXPRESSION(p, &nExpressionType)){}

					if (!compatibleType(nExpressionTypeCompare, nExpressionType)){ semanticError(token__SELECT, "incompatible types"); _ERROR_ }

					if (bEXPRESSION_CASE[nCase] && (bTO = parseTerm(token__TO))){}

					if (bTO){ // e.g. CASE 10 TO 33

						if (bProducePcode){

							p->wr_GREATER_EQUAL(pcode__GREATER_EQUAL, false); // write pcode
							nPcodeOffset_TO_LEFT = p->getPos(); // save the position of the CJMP pcode, later the destination will be overwritten
							p->wr_CJMP(pcode__CJMP, 0, true); // write pcode
						}

						if (bEXPRESSION_CASE[nCase] = fEXPRESSION(p, &nExpressionType)){}
					  if (!bEXPRESSION_CASE[nCase]){ syntaxError(token__SELECT, "CASE expression missing"); _ERROR_ }

						if (!compatibleType(nExpressionTypeCompare, nExpressionType)){ semanticError(token__SELECT, "incompatible types"); _ERROR_ }

						if (bProducePcode){
							p->wr_LESSER_EQUAL(pcode__LESSER_EQUAL, false); // write pcode
							nPcodeOffset_TO_RIGHT = p->getPos(); // save the position of the CJMP pcode, later the destination will be overwritten
							p->wr_CJMP(pcode__CJMP, 0, true); // write pcode

							nPcodeOffset_TO_AFTER = p->getPos(); // save the position of the CJMP pcode, later the destination will be overwritten
							p->wr_JMP(pcode__JMP, 0); // write pcode

							nPcodeOffset_TO_AFTER2 = p->getPos();
			    		p->wr_PUSH_BOOLEAN(pcode__PUSH_BOOLEAN, 0); // little tricky, because all nPcodeOffset_CASE[nCase] are CJMP and we need false on the stack
							nPcodeOffset_CASE[nCase] = p->getPos(); // save the position of the CJMP pcode, later the destination will be overwritten
							p->wr_CJMP(pcode__CJMP, 0, true); // must be a CJMP, because all nPcodeOffset_CASE[nCase] are CJMP, write pcode

							n = p->getPos();
							p->setPos(nPcodeOffset_TO_LEFT); p->wr_CJMP(pcode__CJMP, nPcodeOffset_TO_AFTER2, true); // write pcode, new jump destination
							p->setPos(nPcodeOffset_TO_RIGHT); p->wr_CJMP(pcode__CJMP, nPcodeOffset_TO_AFTER2, true); // write pcode, new jump destination
							p->setPos(nPcodeOffset_TO_AFTER); p->wr_JMP(pcode__JMP, n); // write pcode, new jump destination
							p->setPos(n);

						}
					} else {

						if (bSYM_COMMA = parseTerm(token__SYM_COMMA)){  //  e.g. CASE 15, 24, 34, 45

                bTerm_CASECOMMA[nCase] = true;

								do {

									if (bProducePcode){
										p->wr_EQUAL(pcode__EQUAL, false); // write pcode
										nPcodeOffset_COMMA[nCaseComma] = p->getPos(); // save the position of the CJMP pcode, later the destination will be overwritten
										p->wr_CJMP(pcode__CJMP, 0, false); // write pcode
									}

									if (bEXPRESSION_CASE[nCase] = fEXPRESSION(p, &nExpressionType)) nCaseComma++;
									else { syntaxError(token__SELECT, "CASE expression missing"); _ERROR_ }

									if (!compatibleType(nExpressionTypeCompare, nExpressionType)){ semanticError(token__SELECT, "incompatible types"); _ERROR_ }

								} while (bSYM_COMMA = parseTerm(token__SYM_COMMA));

								if (bProducePcode){
  								// * for the last expression
  								p->wr_EQUAL(pcode__EQUAL, false); // write pcode
  								nPcodeOffset_COMMA[nCaseComma] = p->getPos(); // save the position of the CJMP pcode, later the destination will be overwritten
  								p->wr_CJMP(pcode__CJMP, 0, false); // write pcode
  								nCaseComma++;
  								// *

  					    	p->wr_PUSH_BOOLEAN(pcode__PUSH_BOOLEAN, 0); // little tricky, because all nPcodeOffset_CASE[nCase] are CJMP and we need this point false on the stack
  								nPcodeOffset_CASE[nCase] = p->getPos(); // save the position of the CJMP pcode, later the destination will be overwritten
  								p->wr_CJMP(pcode__CJMP, 0, true); // must be a CJMP, because all nPcodeOffset_CASE[nCase] are CJMP, write pcode

  								n = p->getPos();
  								for(int i = 0; nCaseComma > 0 && i < nCaseComma; i++){
  									p->setPos(nPcodeOffset_COMMA[i]); p->wr_CJMP(pcode__CJMP, n, false); // write pcode, new jump destination
  								}
  								p->setPos(n);

                  nCaseComma = 0;
								}    
                fREM(false);          

            } else {
              fREM(false);          
            }

							if (bProducePcode){
  							if (nCaseComma == 0){ // normal case
  								p->wr_EQUAL(pcode__EQUAL, false); // write pcode
  								nPcodeOffset_CASE[nCase] = p->getPos(); // save the position of the CJMP pcode, later the destination will be overwritten
  								p->wr_CJMP(pcode__CJMP, 0, true); // write pcode
  							}
							}
			          
					  }

					}

				}

 			  if (bProducePcode){ // remove select case expression from stack
 				   p->wr_STACKPOP(pcode__STACKPOP); // write pcode
 				}
        
				if ((bEOL_CASE[nCase] = fEOL())){}

				if ((bEOL_CASE[nCase] == false && (bSTATEMENTSEQUENCE_CASE[nCase] = fSTATEMENT(p))) || (bSTATEMENTSEQUENCE_CASE[nCase] = fSTATEMENTSEQUENCE(p)) || bEOL_CASE[nCase]){ // statement in one line, many statements in following lines, no statements in the following lines

					if (!bEOL_CASE[nCase] && !bSTATEMENTSEQUENCE_CASE[nCase]){ syntaxError(token__SELECT, "CASE statement(s) missing"); _ERROR_ }

 					if (bProducePcode){
 						nPcodeOffset_CASE_AFTER[nCase] = p->getPos(); // save the position of the CJMP pcode, later the destination will be overwritten
 						p->wr_JMP(pcode__JMP, 0); // write pcode
 					}

					if (bTerm_CASE[nCase]){
								 if (!bEXPRESSION_CASE[nCase]){ syntaxError(token__SELECT, "CASE expression missing"); _ERROR_ }
						else if (!bSTATEMENTSEQUENCE_CASE[nCase]){ syntaxError(token__SELECT, "CASE statement(s) missing"); _ERROR_ }
					}

					nCase++;
			} else {
				bTerm_CASE[nCase] = false;
				break;
			}

		} while (bTerm_CASE[nCase - 1]);

		if (bTerm_CASEELSE){

			if (bProducePcode){
				nPcodeOffset_CASEELSE = p->getPos(); // save the position of the CJMP pcode, later the destination will be overwritten
			}

 			if (bProducePcode){ // remove select case expression from stack
 				  p->wr_STACKPOP(pcode__STACKPOP); // write pcode
 			}

			if ((bEOL_CASEELSE = fEOL())){} // EOL is optional
			if ((bEOL_CASEELSE == false && (bSTATEMENTSEQUENCE_CASEELSE = fSTATEMENT(p))) || (bSTATEMENTSEQUENCE_CASEELSE = fSTATEMENTSEQUENCE(p)) || bEOL_CASEELSE){} // statement in one line, many statements in following lines, no statements in the following lines
			if (!bEOL_CASEELSE && !bSTATEMENTSEQUENCE_CASEELSE){ syntaxError(token__SELECT, "CASE ELSE statement(s) missing"); _ERROR_ }

 			if (bProducePcode){
 				nPcodeOffset_CASEELSE_AFTER = p->getPos(); // save the position of the CJMP pcode, later the destination will be overwritten
 				p->wr_JMP(pcode__JMP, 0); // write pcode
 			}

		}

    do { // eat whitespaces
    } while (fEOL() || fREM());

		if (bTerm_END = parseTerm(token__END))
		if ((bTerm_ENDSELECT = parseTerm(token__SELECT)) || (bEOL_CASEELSE == false)){

 			if (bProducePcode){ // remove select case expression from stack
       
        int nPcodeOffset_ENDSELECT2 = p->getPos();

 			  p->wr_STACKPOP(pcode__STACKPOP); // write pcode
 
				nPcodeOffset_ENDSELECT = p->getPos();

				if (bTerm_CASE[0]){
					for(int i = 0; nCase > 0 && i < nCase; i++){

						if (bTerm_CASE[i] && bTerm_CASECOMMA[i] == false){
							if (i + 1 < nCase){
								p->setPos(nPcodeOffset_CASE[i]); p->wr_CJMP(pcode__CJMP, nPcodeOffset_CASE_BEFORE[i + 1], true); // write pcode, new jump destination
							} else {  // last case
								if (bTerm_CASEELSE){
									p->setPos(nPcodeOffset_CASE[i]);	p->wr_CJMP(pcode__CJMP, nPcodeOffset_CASEELSE, true); // if a CASE ELSE exit, it must be the destination, write pcode, new jump destination
								} else {
									p->setPos(nPcodeOffset_CASE[i]); p->wr_CJMP(pcode__CJMP, nPcodeOffset_ENDSELECT2, true); // write pcode, new jump destination
								}
							}

							p->setPos(nPcodeOffset_CASE_AFTER[i]);	p->wr_JMP(pcode__JMP, nPcodeOffset_ENDSELECT); // write pcode, new jump destination

            } else {
							p->setPos(nPcodeOffset_CASE_AFTER[i]);	p->wr_JMP(pcode__JMP, nPcodeOffset_ENDSELECT); // write pcode, new jump destination
            }

            if (bTerm_CASEELSE){
  					  p->setPos(nPcodeOffset_CASEELSE_AFTER);	p->wr_JMP(pcode__JMP, nPcodeOffset_ENDSELECT); // write pcode, new jump destination
            }

						p->setPos(nPcodeOffset_ENDSELECT);
					}
				} else {
					p->setPos(nPcodeOffset_ENDSELECT);
				}

			}
			if (bTerm_CASE[0] && bTerm_CASEELSE && bTerm_ENDSELECT) parseInfo(p, "parsed SELECT CASE..CASE..CASE ELSE..END CASE");
			else parseInfo(p, "parsed SELECT CASE..CASE..END CASE");
			_DONE_
		}
	}

  {
		     if (!bEXPRESSION_COMPARE){ syntaxError(token__SELECT, "comparision expression missing"); _ERROR_ }
		else if (!bTerm_END){ syntaxError(token__SELECT, "" /*END missing*/); _ERROR_ }
		else if (!bTerm_ENDSELECT){ syntaxError(token__SELECT, "SELECT missing"); _ERROR_ }
	}

	_END_
}



/**
[KBASIC][VB][QBASIC]
NAME: FORNEXT
PRINTNAME: For Next
TASK: Defines a loop that runs for a specified number of times.
SYNTAX: 
FOR counter = start TO stop [STEP incrementation]
[lines with statements]
[EXIT FOR]
[lines with statements]
NEXT [counter]

DESC: 
"counter" is a numerical variable which is used to store the current counter
 number while the loop is running. "start" is a numerical expression that
 determines the starting value of the loop countings. "stop" is a numerical
 expression that determines the ending value at which the loop will stop. If
 you wish to count in different steps than the default value of 1, use "step"
 to determine a specific value for incrementing the counter.

If you use EXIT FOR, this will exit the FOR/NEXT loop at once and continue
 with the line following to the NEXT statement. Usually this is used in
 connection with an IF clause (IF something THEN EXIT FOR) to exit the loop
 before its specified end.

The NEXT statement is the lower end of the loop and increments "counter" by
 the value given by "STEP" or by 1 if no "STEP" incrementation is defined.
 The loop will be repeated as long as the value of "counter" is
 smaller/greater than or equals the value of "stop". The indication of
 "counter" may be left out for the "NEXT" statement, however this is
 depreciated as it can lead to confusion when nesting several FOR/NEXT loops.

Notes:
- The speed of FOR/NEXT loops depends on the kind of variables you use.
 FOR/NEXT loops will run fastest when "counter" is an integer variable and
 "start", "stop" and "step" are integer constants.

- You can count backward by using STEP with a negative incrementation value.

 - Take extra care when nesting FOR/NEXT loops; remember to end the loop
   last initiated.(see example).Or else an infinite loop will occur.

CODE:
' Example 1:
DIM ctr AS INTEGER

FOR ctr = 1 TO 5
PRINT "Z";
NEXT ctr

' Output:
' ZZZZZ

' Example 2:
' Here we use STEP
' The resulting string is the same
' as in example 1

DIM ctr AS INTEGER

FOR ctr = 1 TO 50 STEP 10
  PRINT "Z";
NEXT ctr

' Output:
' ZZZZZ

' Example 3:
' You may use expressions for "start"
' and "stop":

DIM ctr AS integer
DIM y, z AS integer

y = 25
z = 5

FOR ctr = 4-3 to y/z
  PRINT "Z";
NEXT ctr

' Output:
' ZZZZZ

' Example 4:
' These are nested loops.
' The "y" loop is the INNER one
' and thus will end first:

DIM x, y AS INTEGER

FOR x = 1 to 5
  PRINT "Line" + STR$(x)
  FOR y = 1 to 5
    PRINT "Z";
  NEXT y
  PRINT "-"
NEXT x

' Output:
' Line 1
' ZZZZZ-
' Line 2
' ZZZZZ-
' Line 3
' ZZZZZ-
' Line 4
' ZZZZZ-
' Line 5
' ZZZZZ-

EXAMPLES: fornext.kbasic
CATEGORY: KEYWORD, CONTROLFLOW, ITERATION, DECISION
SEEALSO: DOLOOPEXIT, WHILEWEND
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
/**
[KBASIC][VB][QBASIC]
NAME: NEXT
PRINTNAME: Next
SEEALSO: FORNEXT
VERSION: PERSONAL, PROFESSIONAL
*/
bool parser::fFOR(pcode *p)
/*
[QBASIC]
[*]
[*]
[*]
*/
{

	_BEGIN_

  //register bool bTerm_FOR = false;

  if (!(/*bTerm_FOR = */parseTerm(token__FOR))){ _END_ } // to optimize, the 'for' is one of the first statements

  if (!bSilent && bProducePcode){
    p->wr_SEPARATOR(pcode__SEPARATOR, utility::con("fFOR", getCurrentLine() - 1));
  }

	bool bIDENTIFIER = false;
	bool bIDENTIFIER2 = false;
	bool bTerm_ = false;
	bool bEXPRESSION = false;
	bool bTerm_TO = false;
	bool bEXPRESSION2 = false;
	bool bEXPRESSION3 = false;
	bool bSTATEMENTSEQUENCE = false;
	bool bTerm_NEXT = false;
	bool bTerm_STEP = false;
	bool bEOL = false;
	bool bREM = false;

	int nPcodeOffset_CJMP = 0;
	int nPcodeOffset_TO = 0;
	int nCurrentline = getCurrentLine();
	int nExpressionType = 0;

  int nVar = 0;
	t_scope scope = global;
	bool bReference = false;
	bool bProperty = false;
	bool bProperty2 = false;
	bool bAllSize = false;
  int nLStringLen = 0;
	bool bImplicitDIM = false;
	bool bTestImplicitDim = true;
	int nIdType = 0;
	int nType = 0;
	bool bTestProperty = false;
  t_arrayVariable a_left;

	int nVar2 = 0;

	bool bTYPE = false;
	bool bTerm_AS = false;  
	bool bTerm_NEW = false;  
	const char *acIdentifier = "";
	const char *acType = "";


  _BEGIN2_

  nFORNEXT++;


  // schauen ob "FOR i AS INTEGER = ..." steht
	if (bIDENTIFIER = fID_KEYWORD_OR_BUILTIN(&acIdentifier)){}

  if (bIDENTIFIER){
		if (bTerm_AS = parseTerm(token__AS)){

			if (bTYPE = fTYPE(p, &acType, bTerm_NEW)){}
			if (bTerm_AS && !bTYPE){ syntaxError(token__DIM, "type name missing"); goto end; }
    } else {
      bIDENTIFIER = false; _END2_    
		}

    if (bIDENTIFIER){

      t_array a;
      a.count = 0;
      scope = getScopeCode();

	    nIdType = nType = findType(acType);
		  if (nType == 0){ semanticError(token__DIM, utility::con(acType, " not defined") ); goto end; }

		  nVar = registerVar(acIdentifier, nType, &a, false, false, token__PRIVATE, 0);
 		  if (nVar == 0){ semanticError(token__DIM, utility::con(utility::ident(getScope(), getSub(), acIdentifier), " already declared at some place") ); goto end; }

		  if (bProducePcode){
			  p->wr_DIM(pcode__DIM, nVar, getScopeCode(), nType, bTerm_NEW, false, false, isSubVarStatic(), 0, 0, "", false); // write pcode
		  }
      bReference = false;
    }
  }

  if (!bIDENTIFIER){
   
	  if (bIDENTIFIER = fVARIABLE_ASSIGNMENT(p, &nVar, &scope, &nIdType, &nType, &bImplicitDIM, bTestImplicitDim, &a_left, &bAllSize, &nLStringLen, &bReference, &bProperty, bTestProperty)){
      int nReturnExpressionType = 0;
      bool bAssignment = false;
      bIDENTIFIER = fVARIABLE_DIM(p, p, nVar, scope, nIdType, nType, bImplicitDIM, false, &nReturnExpressionType, bReference, bAssignment);
    }

		 if (nType == token__ME){
        { semanticError(token__FOR, "FOR not allowed in combination with ME"); goto end; }
		 } else if (nType == token__PARENT){
        { semanticError(token__FOR, "FOR not allowed in combination with PARENT"); goto end; }
     } else {
     }
  }

  if (bIDENTIFIER)
	if (bTerm_ = parseTerm(token__OP_EQUAL))
	if (bEXPRESSION = fEXPRESSION(p, &nExpressionType)){

		if (!compatibleType(nType, nExpressionType)){ semanticError(token__FOR, "incompatible types"); goto end; }

 		switch(nType){ // type checking of counter

     case pcode__BYTE:
 			case pcode__SHORT:
 			case pcode__INTEGER: 
 			case pcode__LONG: 

     case pcode__SINGLE: 
 			case pcode__DOUBLE: 

      case pcode__VARIANT:
       if (!bReference){
 				 if (bProducePcode){
 					 p->wr_MOV(pcode__MOV, nVar, scope); // write pcode
 				 }
       } else {

         // referenzen auch mit offset auf type-elemente erlaubt   					
  			 if (bProducePcode){
           p->wr_MOV_IDREFVAL(pcode__MOV_IDREFVAL, nVar, scope, nType, false, 0); // write pcode    
         }
       }
 				break;
 			default:
 	 		 semanticError(token__FOR, " counter variable must be type of BYTE, INTEGER, SINGLE, DOUBLE, LONG or VARIANT..." ); goto end;
 				break;
 		}

		if (bTerm_TO = parseTerm(token__TO)){
			if (!bSilent && bProducePcode){
       p->wr_SEPARATOR(pcode__SEPARATOR, "fFOR.TO");				
			}
      nPcodeOffset_TO = p->getPos();
			if (bEXPRESSION2 = fEXPRESSION(p, &nExpressionType)){

				if (!compatibleType(nType, nExpressionType)){ semanticError(token__FOR, "incompatible types"); goto end; }

				if (bTerm_STEP = parseTerm(token__STEP)){

  				if (!bSilent && bProducePcode){
           p->wr_SEPARATOR(pcode__SEPARATOR, "fFOR.STEP");
         }

					if (!(bEXPRESSION3 = fEXPRESSION(p, &nExpressionType))){ syntaxError(token__FOR, "expression missing"); goto end; }
					if (!compatibleType(nType, nExpressionType)){ semanticError(token__FOR, "incompatible types"); goto end; }

        } else { 
          p->wr_PUSH_INTEGER(pcode__PUSH_INTEGER, 1); // set on default increment
        }



				if (bProducePcode){
         if (!bSilent) p->wr_SEPARATOR(pcode__SEPARATOR, "fFOR.GREATER_EQUAL");
      	
         if (!bReference){
  	 	 	  	 p->wr_PUSH_ID(pcode__PUSH_ID, nVar, scope, false);//, true);
         } else {
  	 	 	 	  p->wr_PUSH_IDREFVAL(pcode__PUSH_IDREFVAL, nVar, scope, nType);
         }

					p->wr_FOR_GREATER_EQUAL(pcode__FOR_GREATER_EQUAL, true); // write pcode
					nPcodeOffset_CJMP = p->getPos();
					p->wr_CJMP(pcode__CJMP, 0, true); // write pcode
				}

				if (!bSilent){
         p->wr_SEPARATOR(pcode__SEPARATOR);
       }

				if (bEOL = fEOLREM()){}

				myExitFor->addLabel(getScope(), getSub(), utility::toString(getCurrentLine())); // add one exit for handler
  			myIterateFor->addLabel(getScope(), getSub(), utility::toString(getCurrentLine()));

				if ((bEOL == false && (bSTATEMENTSEQUENCE = fSTATEMENT(p))) || (bSTATEMENTSEQUENCE = fSTATEMENTSEQUENCE(p)) || bEOL){} // statement in one line, many statements in following lines, no statements in the following lines

				if (!bEOL && !bSTATEMENTSEQUENCE){ syntaxError(token__FOR, "statement(s) missing"); goto end; }

				if (bTerm_NEXT = parseTerm(token__NEXT)){

					// is there a counter var name after NEXT
          t_arrayVariable a2;
          t_scope scope2;
					if ((bIDENTIFIER2 = fVARIABLE(p, &nVar2, &scope2, &nIdType, &nType, &a2, &bReference, &bProperty, bTestProperty))){

		       if (nType == token__ME){
              { semanticError(token__FOR, "FOR not allowed in combination with ME"); goto end; }
		       } else if (nType == token__PARENT){
              { semanticError(token__FOR, "FOR not allowed in combination with PARENT"); goto end; }
           } else {
           }

						if (nVar != nVar2 || scope != scope2){ semanticError(token__FOR, "next identifier differs from initalizer identifier"); goto end;  }}

						if (bProducePcode){

             if (!bSilent) p->wr_SEPARATOR(pcode__SEPARATOR, "fFOR.INCREMENT"); 
					  
             int nSavePcodeOffset2 = p->getPos();

             if (!bReference){
  	 	 					 p->wr_PUSH_ID(pcode__PUSH_ID, nVar, scope, false);//, true);
             } else {
  	 	 					 p->wr_PUSH_IDREFVAL(pcode__PUSH_IDREFVAL, nVar, scope, nType);
             }

							p->wr_ADD(pcode__ADD);

             if (!bReference){
 					      p->wr_MOV(pcode__MOV, nVar, scope); // write pcode
             } else {
               // referenzen auch mit offset auf type-elemente erlaubt   					
               p->wr_MOV_IDREFVAL(pcode__MOV_IDREFVAL, nVar, scope, nType, false, 0); // write pcode    
             }
             
             if (!bSilent) p->wr_SEPARATOR(pcode__SEPARATOR);

							p->wr_JMP(pcode__JMP, nPcodeOffset_TO); // write pcode

							// cjmp, update jump destination
							int nSavePcodeOffset = p->getPos();
							p->setPos(nPcodeOffset_CJMP);
							p->wr_CJMP(pcode__CJMP, nSavePcodeOffset, true); // write pcode


          		{ // EXIT FOR
          			int nPcodeOffset;
          			int nNewPcodeOffset = nSavePcodeOffset;
          			pcode *p = 0;
								int nCurrentline;
								bool bGoto;
								t_pcode nPcodeId;

          			if (myExitFor->last()){

          					if (myExitFor->firstCall (myExitFor->getId(), &p, &nPcodeOffset, &nCurrentline, &bGoto, &nPcodeId)){
          						do {

          								int n = p->getPos();
          								p->setPos(nPcodeOffset);
													p->wr_JMP(pcode__JMP, nNewPcodeOffset); // write pcode
          								p->setPos(n);

          						} while (myExitFor->nextCall	(myExitFor->getId(), &p, &nPcodeOffset, &nCurrentline, &bGoto, &nPcodeId));

          					}
										myExitFor->removeLast();

								}

          		}

             { // ITERATE FOR
          			int nPcodeOffset;
          			int nNewPcodeOffset = nSavePcodeOffset2;
          			pcode *p = 0;
								int nCurrentline;
								bool bGoto;
								t_pcode nPcodeId;
							
          		  if (myIterateFor->last()){

          				  if (myIterateFor->firstCall (myIterateFor->getId(), &p, &nPcodeOffset, &nCurrentline, &bGoto, &nPcodeId)){
          					  do {

          							  int n = p->getPos();
          							  p->setPos(nPcodeOffset);
												  p->wr_JMP(pcode__JMP, nNewPcodeOffset); // write pcode
          							  p->setPos(n);

          					  } while (myIterateFor->nextCall	(myIterateFor->getId(), &p, &nPcodeOffset, &nCurrentline, &bGoto, &nPcodeId));

          				  }
									  myIterateFor->removeLast();

							  }
             }

             p->setPos(nSavePcodeOffset);
             p->wr_STACKPOP(pcode__STACKPOP); // needed to get rid of the increment counter value on stack

						}

            nFORNEXT--;

						parseInfo(p, "parsed FOR..NEXT");
						_DONE_
				}
			}
		}
	}

  {
				 if (!bIDENTIFIER){ 			 
           
		        if (fID_KEYWORD_OR_BUILTIN(&acIdentifier)){
  	         if (bExplicit || isKBASIC()){

                 if (scope == outofscope){
    		            { semanticError(token__MSC_IDENTIFIER, utility::con(acIdentifier, " is declared, but its scope is PRIVATE or PROTECTED and not PUBLIC") ); goto end; }
                 } else {
                   if (isScopeClass()){
      		           { semanticError(token__MSC_IDENTIFIER, utility::con(acIdentifier, " not declared. Maybe this variable was declared as INSTANCE CLASS variable and not as STATIC CLASS variable. See help for more details") ); goto end; }
                   } else {
      		           { semanticError(token__MSC_IDENTIFIER, utility::con(acIdentifier, " not declared. Remember that variable names are case sensitive and that you have to write OPTION OLDBASIC on top of your program for automatic declaration of variables = old style mode. See help for more details") ); goto end; }
                   }
                 }

             }
          }

          syntaxError(token__FOR, "identifier missing or identifier not declared"); goto end; }

		else if (!bTerm_){ 						 syntaxError(token__FOR, "= missing"); goto end; }
		else if (!bEXPRESSION){ 			 syntaxError(token__FOR, "expression missing"); goto end; }
		else if (!bTerm_TO){ 					 syntaxError(token__FOR, "TO missing"); goto end; }
		else if (!bEXPRESSION2){		 	 syntaxError(token__FOR, "expression missing"); goto end; }
		else if (!bSTATEMENTSEQUENCE){ syntaxError(token__FOR, ""/*statement missing*/); goto end; }
		else if (!bTerm_NEXT){ 				 syntaxError(token__FOR, ""/*NEXT missing"*/); goto end; }
	}
end:
  nFORNEXT--;

	_END_
}


/* *
[KBASIC][VB][QBASIC]
NAME: FOREACH
PRINTNAME: For Each
TASK: iterates through a collection
SYNTAX: FOR EACH object IN collection
DESC: 
CODE:
EXAMPLES: foreach.kbasic
CATEGORY: KEYWORD, CONTROLFLOW, ITERATION
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fFOREACH(pcode *p)
/*
[*]
[VB]
[*]
[*]
*/
{

	_BEGIN_

  nFORNEXT++;

  if (!(parseTerm(token__FOR))){ _END_ } // to optimize, the 'for' is one of the first statements
  if (!(parseTerm(token__EACH))){ _END_ } // to optimize, the 'for' is one of the first statements

  if (!bSilent && bProducePcode){
    p->wr_SEPARATOR(pcode__SEPARATOR, utility::con("fFOREACH", getCurrentLine() - 1));
  }

	bool bIDENTIFIER = false;
	bool bIDENTIFIER2 = false;
	bool bTerm_IN = false;
	bool bSTATEMENTSEQUENCE = false;
	bool bTerm_NEXT = false;
	bool bEOL = false;
	bool bREM = false;

	int nPcodeOffset_CJMP = 0;
	int nPcodeOffset_TO = 0;
	int nCurrentline = getCurrentLine();
	
  bool bTYPE = false;
	bool bTerm_AS = false;  	
	bool bTerm_NEW = false;  
	const char *acIdentifier = "";
	const char *acType = "";

  int nVar = 0;
	t_scope scope = global;
	bool bReference = false;
	bool bProperty = false;
	bool bProperty2 = false;
	bool bAllSize = false;
  int nLStringLen = 0;
	bool bImplicitDIM = false;
	bool bTestImplicitDim = false;
	int nIdType = 0;
	int nType = 0;
	bool bTestProperty = false;
  t_arrayVariable a_left;

	int nVar2 = 0; t_scope scope2 = global; int nIdType2 = 0; int nType2 = 0; t_arrayVariable a2;
  


  _BEGIN2_

  int mid = 0;
  int nId = 0;  
  int nParamCount = 0;

  // schauen ob "FOR i AS INTEGER = ..." steht
	if (bIDENTIFIER = fID_KEYWORD_OR_BUILTIN(&acIdentifier)){}

  if (bIDENTIFIER){
		if (bTerm_AS = parseTerm(token__AS)){

			if (bTYPE = fTYPE(p, &acType, bTerm_NEW)){}
			if (bTerm_AS && !bTYPE){ syntaxError(token__DIM, "type name missing"); goto end; }
    } else {
      bIDENTIFIER = false; _END2_    
		}

    if (bIDENTIFIER){
      
      t_array b;

      b.count = 0;
      scope = getScopeCode();

	    nIdType = nType = findType(acType);
		  if (nType == 0){ semanticError(token__DIM, utility::con(acType, " not defined") ); goto end; }

		  nVar = registerVar(acIdentifier, nType, &b, false, false, token__PRIVATE, 0);
 		  if (nVar == 0){ semanticError(token__DIM, utility::con(utility::ident(getScope(), getSub(), acIdentifier), " already declared at some place") ); goto end; }

		  if (bProducePcode){
			  p->wr_DIM(pcode__DIM, nVar, getScopeCode(), nType, bTerm_NEW, false, false, isSubVarStatic(), 0, 0, "", false); // write pcode
		  }
      
      goto w;
    }
  }  


  if (!bIDENTIFIER && (bIDENTIFIER = fVARIABLE_ASSIGNMENT(p, &nVar, &scope, &nIdType, &nType, &bImplicitDIM, bTestImplicitDim, &a_left, &bAllSize, &nLStringLen, &bReference, &bProperty, bTestProperty))){

		if (nType == token__ME){
      { semanticError(token__FOR, "FOR not allowed in combination with ME"); goto end; }
		} else if (nType == token__PARENT){
      { semanticError(token__FOR, "FOR not allowed in combination with PARENT"); goto end; }
    } else {
    }
w:
        
    t_arrayVariable a;

    if (bTerm_IN = parseTerm(token__IN)){
      if (bIDENTIFIER = fVARIABLE(p, &nVar2, &scope2, &nIdType2, &nType2, &a2)){}
      else { syntaxError(token__FOR, "missing identifier after IN"); goto end; }

      if (!((nType2 == pcode___strings || nType2 == pcode___stringsstrings || nType2 == pcode___array) && (nType == pcode__QSTRING || nType == pcode__LQSTRING || nType == pcode__CSTRING || nType == pcode__LCSTRING))){ semanticError(token__FOR, "incompatible types"); goto end; }

		  if (nType2 == token__ME){
        { semanticError(token__FOR, "FOR not allowed in combination with ME"); goto end; }
		  } else if (nType2 == token__PARENT){
        { semanticError(token__FOR, "FOR not allowed in combination with PARENT"); goto end; }
      } else {
      }

      switch(nType2){
        case pcode___strings:
          mid = pcode___strings__FOR;
          break;     
        case pcode___stringsstrings:
          mid = pcode___stringsstrings__FOR;
          break;     
        case pcode___array:
          mid = pcode___array__FOR;
          break;     
 
        default:
          { semanticError(token__FOR, "data type does not support FOR EACH"); goto end; }
          break;
      }
      

   		if (bProducePcode){
        //if (mid != pcode___strings__FOR){
          if (nVar2){
            p->wr_PUSH_ID(pcode__PUSH_ID, nVar2, scope2, false);
          }
        //}
				p->wr_PUSH_INTEGER(pcode__PUSH_INTEGER, nParamCount);
				p->wr_binding_ClassMethod(pcode__binding_CLASSMETHOD, mid, true);
 			  p->wr_MOV(pcode__MOV, nVar, scope); // write pcode
 		  }

			if (!bSilent && bProducePcode){
       p->wr_SEPARATOR(pcode__SEPARATOR, "fFOR.IN");				
			}

      nPcodeOffset_TO = p->getPos();

      if (bProducePcode){
        if (mid == pcode___strings__FOR){
				  nPcodeOffset_CJMP = p->getPos();
				  p->wr_CJMP(pcode__CJMP, 0, true); // write pcode
          p->wr_PUSH_ID(pcode__PUSH_ID, nVar, scope, false);
        } else {
          p->wr_PUSH_ID(pcode__PUSH_ID, nVar, scope, false);
				  nPcodeOffset_CJMP = p->getPos();
				  p->wr_CJMP(pcode__CJMP, 0, true); // write pcode
        }
      }


    } else { syntaxError(token__FOR, "missing object name after IN"); goto end; }

		if (bEOL = fEOLREM()){}

		myExitFor->addLabel(getScope(), getSub(), utility::toString(getCurrentLine())); // add one exit for handler
		myIterateFor->addLabel(getScope(), getSub(), utility::toString(getCurrentLine()));

		if ((bEOL == false && (bSTATEMENTSEQUENCE = fSTATEMENT(p))) || (bSTATEMENTSEQUENCE = fSTATEMENTSEQUENCE(p)) || bEOL){} // statement in one line, many statements in following lines, no statements in the following lines

		if (!bEOL && !bSTATEMENTSEQUENCE){ syntaxError(token__FOR, "statement(s) missing"); goto end; }

		if (bTerm_NEXT = parseTerm(token__NEXT)){

        switch(nType2){        
          case pcode___strings:
            mid = pcode___strings__EACH;
            break; 
          case pcode___stringsstrings:
            mid = pcode___stringsstrings__EACH;
            break; 
          case pcode___array:
            mid = pcode___array__EACH;
            break; 
    
          default:
            { semanticError(token__FOR, "data type does not support FOR EACH"); goto end; }
            break;
        }

   		  if (bProducePcode){
          if (nVar2){
            //if ( mid != pcode___strings__EACH){
              p->wr_PUSH_ID(pcode__PUSH_ID, nVar2, scope2, false);
           // }

          }

				  p->wr_PUSH_INTEGER(pcode__PUSH_INTEGER, nParamCount);
				  p->wr_binding_ClassMethod(pcode__binding_CLASSMETHOD, mid, true);
   		   		  
 			    p->wr_MOV(pcode__MOV, nVar, scope); // write pcode
          p->wr_JMP(pcode__JMP, nPcodeOffset_TO); // write pcode
 		    }

			  // cjmp, update jump destination
			  int nSavePcodeOffset = p->getPos();

        if (bProducePcode){
			    p->setPos(nPcodeOffset_CJMP);
			    p->wr_CJMP(pcode__CJMP, nSavePcodeOffset, true); // write pcode
        }


				if (bProducePcode){

          { // EXIT FOR
          	int nPcodeOffset;
          	int nNewPcodeOffset = nSavePcodeOffset;
          	pcode *p = 0;
						int nCurrentline;
						bool bGoto;
						t_pcode nPcodeId;

          	if (myExitFor->last()){

          			if (myExitFor->firstCall (myExitFor->getId(), &p, &nPcodeOffset, &nCurrentline, &bGoto, &nPcodeId)){
          				do {

          						int n = p->getPos();
          						p->setPos(nPcodeOffset);
											p->wr_JMP(pcode__JMP, nNewPcodeOffset); // write pcode
          						p->setPos(n);

          				} while (myExitFor->nextCall	(myExitFor->getId(), &p, &nPcodeOffset, &nCurrentline, &bGoto, &nPcodeId));

          			}
								myExitFor->removeLast();

						}

          }

         { // ITERATE FOR
           int nPcodeOffset;
           int nNewPcodeOffset = nSavePcodeOffset;
           pcode *p = 0;
					  int nCurrentline;
					  bool bGoto;
					  t_pcode nPcodeId;
				
          	if (myIterateFor->last()){

          			if (myIterateFor->firstCall (myIterateFor->getId(), &p, &nPcodeOffset, &nCurrentline, &bGoto, &nPcodeId)){
          				do {

          						int n = p->getPos();
          						p->setPos(nPcodeOffset);
											p->wr_JMP(pcode__JMP, nPcodeOffset_CJMP); // write pcode
          						p->setPos(n);

          				} while (myIterateFor->nextCall	(myIterateFor->getId(), &p, &nPcodeOffset, &nCurrentline, &bGoto, &nPcodeId));

          			}
								myIterateFor->removeLast();

						}
         }

         p->setPos(nSavePcodeOffset);

				}

        nFORNEXT--;

				parseInfo(p, "parsed FOR EACH..NEXT");
				_DONE_
		
    
		}

   }
	
  {
				 if (!bIDENTIFIER){ 			 syntaxError(token__FOR, "identifier missing or identifier not declared"); goto end; }
		else if (!bTerm_IN){ 					 syntaxError(token__FOR, "IN missing"); goto end; }
		else if (!bIDENTIFIER){ 			 syntaxError(token__FOR, "identifier missing or identifier not declared"); goto end; }
		else if (!bSTATEMENTSEQUENCE){ syntaxError(token__FOR, ""/*statement missing*/); goto end; }
		else if (!bTerm_NEXT){ 				 syntaxError(token__FOR, "NEXT missing"); goto end; }
	}

end:
  nFORNEXT--;

	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: DOWHILELOOP
PRINTNAME: Do While...Loop
TASK: A group of statements enabling you to define a loop which will be repeated until a certain condition remains true.
SYNTAX: 
DO [WHILE condition]
.
.
statements
.
[EXIT (LOOP | DO)]
[ITERATE (LOOP | DO)]
.
statements
.
.
LOOP [WHILE condition]
DESC: 

- DO
launches the loop and must be the first statement

- LOOP
ends the loop and must be the last statement

- WHILE
lets the loop repeat while the condition is true

- condition
a numeric or string expression with a result of true or false

- EXIT LOOP (EXIT DO)
exits the loop at this very line and lets the program continue behind the
 LOOP statement

- ITERATE LOOP (ITERATE DO)
jumps directly to the LOOP statement

Examples:

In the first example, the loop will be repeated as long as xyz remains 5:
DO WHILE xyz = 5
(lines of code)
LOOP

Please note that the lines of code will never be executed if xyz is not 5
 when entering the loop.

To overcome the problem of "never executed code", you may move the condition
 to the end of the loop:

DO
(lines of code)
LOOP WHILE xyz = 5

Now the lines of code will be executed at least one time before the loop
 checks for the value of xyz and decides whether to exit or repeat execution.

If there is a second condition which may arise somewhere within the loop
 making it necessary to exit the loop before the lines of code within it end,
 the EXIT statement may be helpful:

DO
(lines of code)
IF abc = 0 then EXIT LOOP
(lines of code)
LOOP WHILE xyz <> 5

This means, if abc becomes zero at the IF statement within the loop within
 the loop, it will exit the loop. The rest of the code lines will be skipped.

Sometimes it is necessary to skip the rest of the code lines but nevertheless
 stay in the loop to be repeated. Now you may use ITERATE instead:

DO
(lines of code)
IF abc = 0 then ITERATE LOOP
(lines of code)
LOOP WHILE xyz <> 5

This means, if abc becomes zero at anyone moment within the loop, it will
 skip the rest of the code lines within the loop and jump directly to its
 "LOOP WHILE xyz = 5". Now the loop can check for the value of xyz and decide
 what to do.

You may use the "condition" with a number of expressions like AND and OR:

DO WHILE x < 10 AND y < 10
(lines of code)
LOOP

will repeat while x AND y are smaller than 10.

NOTE: Please be careful when nesting several loops within each other.
 Sometimes it is overseen that a variable checked for the outer loop is
 changed within the inner loop and thus the outer loop will never end:

DO WHILE counter < 10
(lines of code)
counter = 0
DO
counter = counter + 1
LOOP WHILE counter <> 5
LOOP

It would be a good idea to use a separate variable for each loop. The same
 might happen with a FOR...NEXT loop within:

DO WHILE counter < 10
(lines of code)
FOR counter = 1 TO 5
(lines of code)
NEXT counter
LOOP

Moreover, be careful not to interchange the different loops:

DO WHILE counter < 10
(lines of code)
FOR i = 1 TO 5
(lines of code)
LOOP
NEXT i

This will result in an error because "LOOP" has to appear after the "NEXT i".


CODE:
x = 5
DO WHILE x = 5
  PRINT x
LOOP
EXAMPLES: dowhileloop.kbasic
CATEGORY: KEYWORD, CONTROLFLOW, ITERATION, LOOP
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
/**
[KEYWORD]
NAME: DO
PRINTNAME: Do
SEEALSO: DOWHILELOOP, DOUNTILLOOP, DOLOOPWHILE
VERSION: PERSONAL, PROFESSIONAL
*/
bool parser::fDOWHILELOOP(pcode *p)
/*
[QBASIC]
[VB]
[*]
[*]
*/
{
	_BEGIN_

	//register bool bTerm_DO = false;
  if (!(/*bTerm_DO = */parseTerm(token__DO))){ _END_ } // optimized, the 'do' is one of the first statements

  if (!bSilent && bProducePcode){
    p->wr_SEPARATOR(pcode__SEPARATOR, utility::con("fDOWHILELOOP", getCurrentLine() - 1));
  }

	bool bTerm_WHILE = false;
	bool bCONDITION = false;
	bool bEOL = false;
	bool bREM = false;

	bool bSTATEMENTSEQUENCE = false;
	bool bTerm_LOOP = false;
	int nPcodeOffset_CJMP = 0;
	int nPcodeOffset_WHILE = 0;
	int nCurrentline = getCurrentLine();
	int nExpressionType;


  if (bTerm_WHILE = parseTerm(token__WHILE)){
		if (bProducePcode){
			nPcodeOffset_WHILE = p->getPos();
		}
		if (bCONDITION = fCONDITION(p, &nExpressionType)){

			if (bProducePcode){
				nPcodeOffset_CJMP = p->getPos();
				p->wr_CJMP(pcode__CJMP, 0, true); // write pcode
			}

			if (bEOL = fEOLREM()){}

			myExitDo->addLabel(getScope(), getSub(), utility::toString(getCurrentLine())); // add one exit for handler
			myIterateDo->addLabel(getScope(), getSub(), utility::toString(getCurrentLine())); // add one exit for handler

			if ((bEOL == false && (bSTATEMENTSEQUENCE = fSTATEMENT(p))) || (bSTATEMENTSEQUENCE = fSTATEMENTSEQUENCE(p)) || bEOL){ // statement in one line, many statements in following lines, no statements in the following lines

				if (!bEOL && !bSTATEMENTSEQUENCE){ syntaxError(token__DO, "statement(s) missing"); _ERROR_ }

				if (bTerm_LOOP = parseTerm(token__LOOP)){
					if (bProducePcode){

						p->wr_JMP(pcode__JMP, nPcodeOffset_WHILE); // write pcode

						// cjmp, update jump destination
						int nSavePcodeOffset = p->getPos();
						p->setPos(nPcodeOffset_CJMP);
						p->wr_CJMP(pcode__CJMP, nSavePcodeOffset, true); // write pcode
						p->setPos(nSavePcodeOffset);

          	{
          		int nPcodeOffset;
          		int nNewPcodeOffset = nSavePcodeOffset;
          		pcode *p = 0;
							int nCurrentline;
							bool bGoto;
							t_pcode nPcodeId;

							// EXIT DO/LOOP
          		if (myExitDo->last()){

          				if (myExitDo->firstCall (myExitDo->getId(), &p, &nPcodeOffset, &nCurrentline, &bGoto, &nPcodeId)){
          					do {

          							int n = p->getPos();
          							p->setPos(nPcodeOffset);
												p->wr_JMP(pcode__JMP, nNewPcodeOffset); // write pcode
          							p->setPos(n);

          					} while (myExitDo->nextCall	(myExitDo->getId(), &p, &nPcodeOffset, &nCurrentline, &bGoto, &nPcodeId));

          				}
									myExitDo->removeLast();

							}

							// ITERATE DO/LOOP
          		if (myIterateDo->last()){

          				if (myIterateDo->firstCall (myIterateDo->getId(), &p, &nPcodeOffset, &nCurrentline, &bGoto, &nPcodeId)){
          					do {

          							int n = p->getPos();
          							p->setPos(nPcodeOffset);
												p->wr_JMP(pcode__JMP, nPcodeOffset_WHILE); // write pcode
          							p->setPos(n);

          					} while (myIterateDo->nextCall	(myIterateDo->getId(), &p, &nPcodeOffset, &nCurrentline, &bGoto, &nPcodeId));

          				}
									myIterateDo->removeLast();

							}

          	}

						p->setPos(nSavePcodeOffset);

					}
					parseInfo(p, "parsed DO WHILE..LOOP");
					_DONE_
				}
			}
		}
	}

  {
		if (bTerm_WHILE){ // maybe it's UNTIL, so do not throw an error if WHILE is missing
  				 if (!bCONDITION){ 			   syntaxError(token__DO, "condition missing"); _ERROR_ }
  		else if (!bSTATEMENTSEQUENCE){ syntaxError(token__DO, "" /*statement missing*/); _ERROR_ }
  		else if (!bTerm_LOOP){ 				 syntaxError(token__DO, "" /*LOOP missing*/); _ERROR_ }
		}
	}

	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: DOUNTILLOOP
PRINTNAME: Do Until...Loop
TASK: A group of statements enabling you to define a loop which will be repeated until a certain condition remains true.
SYNTAX:
DO UNTIL condition
.
.
statements
.
.
LOOP
DESC:
CODE:
EXAMPLES: dountilloop.kbasic
CATEGORY: KEYWORD, CONTROLFLOW, ITERATION, LOOP
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fDOUNTILLOOP(pcode *p)
{

  _BEGIN_

	//register bool bTerm_DO = false;
  if (!(/*bTerm_DO = */parseTerm(token__DO))){ _END_ } // optimized, the 'do' is one of the first statements
	

  if (!bSilent && bProducePcode){
    p->wr_SEPARATOR(pcode__SEPARATOR, utility::con("fDOUNTILLOOP", getCurrentLine() - 1));
  }

	bool bTerm_UNTIL = false;
	bool bCONDITION = false;
	bool bEOL = false;
	bool bREM = false;

	bool bSTATEMENTSEQUENCE = false;
	bool bTerm_LOOP = false;
	int nPcodeOffset_CJMP = 0;
	int nPcodeOffset_UNTIL = 0;
	int nCurrentline = getCurrentLine();
	int nExpressionType;


  if (bTerm_UNTIL = parseTerm(token__UNTIL)){
		if (bProducePcode){
			nPcodeOffset_UNTIL = p->getPos();
		}
		if (bCONDITION = fCONDITION(p, &nExpressionType)){

			if (bProducePcode){
				nPcodeOffset_CJMP = p->getPos();
				p->wr_CJMP(pcode__CJMP, 0, false); // write pcode
			}

			if (bEOL = fEOLREM()){}

			myExitDo->addLabel(getScope(), getSub(), utility::toString(getCurrentLine())); // add one exit for handler
			myIterateDo->addLabel(getScope(), getSub(), utility::toString(getCurrentLine())); // add one exit for handler

			if ((bEOL == false && (bSTATEMENTSEQUENCE = fSTATEMENT(p))) || (bSTATEMENTSEQUENCE = fSTATEMENTSEQUENCE(p)) || bEOL){ // statement in one line, many statements in following lines, no statements in the following lines

				if (!bEOL && !bSTATEMENTSEQUENCE){ syntaxError(token__DO, "statement(s) missing"); _ERROR_ }

				if (bTerm_LOOP = parseTerm(token__LOOP)){
					if (bProducePcode){

						p->wr_JMP(pcode__JMP, nPcodeOffset_UNTIL); // write pcode

						// cjmp, update jump destination
						int nSavePcodeOffset = p->getPos();
						p->setPos(nPcodeOffset_CJMP);
						p->wr_CJMP(pcode__CJMP, nSavePcodeOffset, false); // write pcode
						p->setPos(nSavePcodeOffset);

          	{
          		int nPcodeOffset;
          		int nNewPcodeOffset = nSavePcodeOffset;
          		pcode *p = 0;
							int nCurrentline;
							bool bGoto;
							t_pcode nPcodeId;

							// EXIT DO/LOOP
          		if (myExitDo->last()){

          				if (myExitDo->firstCall (myExitDo->getId(), &p, &nPcodeOffset, &nCurrentline, &bGoto, &nPcodeId)){
          					do {

          							int n = p->getPos();
          							p->setPos(nPcodeOffset);
												p->wr_JMP(pcode__JMP, nNewPcodeOffset); // write pcode
          							p->setPos(n);

          					} while (myExitDo->nextCall	(myExitDo->getId(), &p, &nPcodeOffset, &nCurrentline, &bGoto, &nPcodeId));

          				}
									myExitDo->removeLast();

							}

							// ITERATE DO/LOOP
          		if (myIterateDo->last()){

          				if (myIterateDo->firstCall (myIterateDo->getId(), &p, &nPcodeOffset, &nCurrentline, &bGoto, &nPcodeId)){
          					do {

          							int n = p->getPos();
          							p->setPos(nPcodeOffset);
												p->wr_JMP(pcode__JMP, nPcodeOffset_UNTIL); // write pcode
          							p->setPos(n);

          					} while (myIterateDo->nextCall	(myIterateDo->getId(), &p, &nPcodeOffset, &nCurrentline, &bGoto, &nPcodeId));

          				}
									myIterateDo->removeLast();

							}

          	}

						p->setPos(nSavePcodeOffset);

					}
					parseInfo(p, "parsed DO UNTIL..LOOP");
					_DONE_
				}
			}
		}
	}

	//if (bTerm_DO)
  {
		if (bTerm_UNTIL){ // maybe it's a another DO ... LOOP
					 if (!bCONDITION){ 			   syntaxError(token__DO, "condition missing"); _ERROR_ }
			else if (!bSTATEMENTSEQUENCE){ syntaxError(token__DO, ""/*statement missing*/); _ERROR_ }
			else if (!bTerm_LOOP){ 				 syntaxError(token__DO, ""/*LOOP missing*/); _ERROR_ }
		}
	}

	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: WHILEWEND
PRINTNAME: While...WEnd
TASK: WHILE initiates a WHILE-WEND loop.
SYNTAX: 
WHILE <expression>
...
WEND
DESC: 
WHILE initiates a WHILE-WEND loop. The loop ends with WEND, and execution
reiterates through the loop as long as the 'expression' is TRUE (-1).

CODE:
EXAMPLES: whilewend.kbasic
CATEGORY: KEYWORD, CONTROLFLOW, ITERATION, LOOP
SEEALSO: DOLOOP, FORNEXT
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fWHILEWEND(pcode *p)
/*
[QBASIC]
[VB]
[*]
[*]
*/
{

	//register bool bTerm_WHILE = false;
  _BEGIN_

  if (!(/*bTerm_WHILE = */parseTerm(token__WHILE))){ _END_ }	

  if (!bSilent && bProducePcode){
    p->wr_SEPARATOR(pcode__SEPARATOR, utility::con("fWHILEWEND", getCurrentLine() - 1));
  }

	bool bCONDITION = false;
	bool bTerm_WHILE2 = false;
  
	bool bEOL = false;
	bool bREM = false;

	bool bSTATEMENTSEQUENCE = false;
	bool bTerm_WEND = false;
	int nPcodeOffset_CJMP = 0;
	int nPcodeOffset_WHILE = 0;
	int nExpressionType;

	{
		if (bProducePcode){
			nPcodeOffset_WHILE = p->getPos();
		}
		if (bCONDITION = fCONDITION(p, &nExpressionType)){

			if (bProducePcode){
				nPcodeOffset_CJMP = p->getPos();
				p->wr_CJMP(pcode__CJMP, 0, true); // write pcode
			}

			if (bEOL = fEOLREM()){}

			if ((bEOL == false && (bSTATEMENTSEQUENCE = fSTATEMENT(p))) || (bSTATEMENTSEQUENCE = fSTATEMENTSEQUENCE(p)) || bEOL){ // statement in one line, many statements in following lines, no statements in the following lines

				if (!bEOL && !bSTATEMENTSEQUENCE){ syntaxError(token__WHILE, "statement(s) missing"); _ERROR_ }

				if (bTerm_WHILE2 = parseTerm(token__WHILE)){
					if (bProducePcode){

						p->wr_JMP(pcode__JMP, nPcodeOffset_WHILE); // write pcode

						// cjmp, update jump destination
						int nSavePcodeOffset = p->getPos();
						p->setPos(nPcodeOffset_CJMP);
						p->wr_CJMP(pcode__CJMP, nSavePcodeOffset, true); // write pcode
						p->setPos(nSavePcodeOffset);

						p->setPos(nSavePcodeOffset);

					}
					parseInfo(p, "parsed WHILE..END WHILE");
					_DONE_
				}

				if (bTerm_WEND = parseTerm(token__WEND)){
					if (bProducePcode){

						p->wr_JMP(pcode__JMP, nPcodeOffset_WHILE); // write pcode

						// cjmp, update jump destination
						int nSavePcodeOffset = p->getPos();
						p->setPos(nPcodeOffset_CJMP);
						p->wr_CJMP(pcode__CJMP, nSavePcodeOffset, true); // write pcode
						p->setPos(nSavePcodeOffset);

						p->setPos(nSavePcodeOffset);

					}
					parseInfo(p, "parsed WHILE..WEND");
					_DONE_
				}
			}
		}
	}

	//if (bTerm_WHILE)
  {
				 if (!bCONDITION){ 			   syntaxError(token__WHILE, "condition missing"); _ERROR_ }
		else if (!bSTATEMENTSEQUENCE){ syntaxError(token__WHILE, ""/*statement missing*/); _ERROR_ }
//		else if (!bTerm_WEND){ 				 syntaxError(token__WHILE, "WEND missing"); _ERROR_ }
	}

	_END_
}



/**
[KBASIC][VB][QBASIC]
NAME: WHILEENDWHILE
PRINTNAME: While...End While
TASK: WHILE initiates a WHILE END WHILE loop.
SYNTAX: 
WHILE <expression>
...
WEND
DESC: 
WHILE initiates a WHILE...END WHILE loop. The loop ends with END WHILE, and execution
reiterates through the loop as long as the 'expression' is TRUE (-1).

CODE:
EXAMPLES: whileendwhile.kbasic
CATEGORY: KEYWORD, CONTROLFLOW, ITERATION, LOOP
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fWHILEENDWHILE(pcode *p)
/*
[!QBASIC]
[!VB]
[*]
[KBASIC]
*/
{
  // WHILE END WHILE is handled in WHILE WEND
  _BEGIN_

	//register bool bTerm_WHILE = false;
  if (!(/*bTerm_WHILE = */parseTerm(token__WHILE))){ _END_ }	

  if (!bSilent && bProducePcode){
    p->wr_SEPARATOR(pcode__SEPARATOR, utility::con("fWHILEENDWHILE", getCurrentLine() - 1));
  }

	bool bCONDITION = false;
	bool bEOL = false;
	bool bREM = false;

	bool bSTATEMENTSEQUENCE = false;
	bool bTerm_END = false;
	bool bTerm_WHILE2 = false;
	int nPcodeOffset_CJMP = 0;
	int nPcodeOffset_WHILE = 0;
	int nExpressionType;

	{
		if (bProducePcode){
			nPcodeOffset_WHILE = p->getPos();
		}
		if (bCONDITION = fCONDITION(p, &nExpressionType)){

			if (bProducePcode){
				nPcodeOffset_CJMP = p->getPos();
				p->wr_CJMP(pcode__CJMP, 0, true); // write pcode
			}

			if (bEOL = fEOLREM()){}

			if ((bEOL == false && (bSTATEMENTSEQUENCE = fSTATEMENT(p))) || (bSTATEMENTSEQUENCE = fSTATEMENTSEQUENCE(p)) || bEOL){ // statement in one line, many statements in following lines, no statements in the following lines

				if (!bEOL && !bSTATEMENTSEQUENCE){ syntaxError(token__WHILE, "statement(s) missing"); _ERROR_ }

				if (bTerm_END = parseTerm(token__END))
				if (bTerm_WHILE2 = parseTerm(token__WHILE)){
					if (bProducePcode){

						p->wr_JMP(pcode__JMP, nPcodeOffset_WHILE); // write pcode

						// cjmp, update jump destination
						int nSavePcodeOffset = p->getPos();
						p->setPos(nPcodeOffset_CJMP);
						p->wr_CJMP(pcode__CJMP, nSavePcodeOffset, true); // write pcode
						p->setPos(nSavePcodeOffset);

						p->setPos(nSavePcodeOffset);

					}
					parseInfo(p, "parsed WHILE..END WHILE");
					_DONE_
				}
			}
		}
	}

  {
				 if (!bCONDITION){ 			   syntaxError(token__WHILE, "condition missing"); _ERROR_ }
		else if (!bSTATEMENTSEQUENCE){ syntaxError(token__WHILE, ""/*statement missing*/); _ERROR_ }
		else if (!bTerm_END){ 				 syntaxError(token__WHILE, ""/*END missing*/); _ERROR_ }
		else if (!bTerm_WHILE2){ 				 syntaxError(token__WHILE, "WHILE missing"); _ERROR_ }
	}

	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: DOLOOPWHILE
PRINTNAME: Do...Loop While
TASK: repeats statements while condition is set
SYNTAX: 
DO
.
.
statements
.
.
LOOP WHILE condition
DESC: DOLOOPWHILE
CODE:
EXAMPLES: doloopwhile.kbasic
CATEGORY: KEYWORD, CONTROLFLOW, ITERATION, LOOP
SEEALSO: EXIT, FORNEXT, WHILEWEND
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fDOLOOPWHILE(pcode *p)
/*
[QBASIC]
[VB]
[*]
[*]
*/
{

  _BEGIN_

	//register bool bTerm_DO = false;
  if (!(/*bTerm_DO = */parseTerm(token__DO))){ _END_ } // to optimize, the 'do' is one of the first statements
	

  if (!bSilent && bProducePcode){
    p->wr_SEPARATOR(pcode__SEPARATOR, utility::con("fDOLOOPWHILE", getCurrentLine() - 1));
  }

	bool bTerm_WHILE = false;
	bool bTerm_UNTIL = false;
  
	bool bCONDITION = false;
	bool bEOL = false;
	bool bREM = false;

	bool bSTATEMENTSEQUENCE = false;
	bool bTerm_LOOP = false;
	int nPcodeOffset_CJMP = 0;
	int nPcodeOffset_DO = 0;
	int nCurrentline = getCurrentLine();
	int nExpressionType;


	{
		if (bProducePcode){

			nPcodeOffset_DO = p->getPos();
		}
		if (bEOL = fEOLREM()){}

		myExitDo->addLabel(getScope(), getSub(), utility::toString(getCurrentLine())); // add one exit for handler
		myIterateDo->addLabel(getScope(), getSub(), utility::toString(getCurrentLine())); // add one exit for handler

    prepareRollbackVariable();

		if ((bEOL == false && (bSTATEMENTSEQUENCE = fSTATEMENT(p))) || (bSTATEMENTSEQUENCE = fSTATEMENTSEQUENCE(p)) || bEOL){ // statement in one line, many statements in following lines, no statements in the following lines

      int nPcodeOffset_CONDITION = p->getPos();
			
      if (!bEOL && !bSTATEMENTSEQUENCE){ goto exit; }

			if (!(bTerm_LOOP = parseTerm(token__LOOP))){ goto exit; }
		  if (bTerm_UNTIL = parseTerm(token__UNTIL))
			if (bCONDITION = fCONDITION(p, &nExpressionType)){
				if (bProducePcode){

					nPcodeOffset_CJMP = p->getPos();
					p->wr_CJMP(pcode__CJMP, 0, true); // write pcode

					// cjmp, update jump destination
					int nSavePcodeOffset = p->getPos();
					p->setPos(nPcodeOffset_CJMP);
					p->wr_CJMP(pcode__CJMP, nPcodeOffset_DO, true); // write pcode
					p->setPos(nSavePcodeOffset);

         	{
         		int nPcodeOffset;
         		int nNewPcodeOffset = nSavePcodeOffset;
         		pcode *p = 0;
 						int nCurrentline;
  					bool bGoto;
						t_pcode nPcodeId;

 						// EXIT DO/LOOP
         		if (myExitDo->last()){

         				if (myExitDo->firstCall (myExitDo->getId(), &p, &nPcodeOffset, &nCurrentline, &bGoto, &nPcodeId)){
         					do {

         							int n = p->getPos();
         							p->setPos(nPcodeOffset);
 											p->wr_JMP(pcode__JMP, nNewPcodeOffset); // write pcode
         							p->setPos(n);

         					} while (myExitDo->nextCall	(myExitDo->getId(), &p, &nPcodeOffset, &nCurrentline, &bGoto, &nPcodeId));

         				}
 								myExitDo->removeLast();

 						}

 						// ITERATE DO/LOOP
         		if (myIterateDo->last()){

         				if (myIterateDo->firstCall (myIterateDo->getId(), &p, &nPcodeOffset, &nCurrentline, &bGoto, &nPcodeId)){
         					do {

         							int n = p->getPos();
         							p->setPos(nPcodeOffset);
 											p->wr_JMP(pcode__JMP, nPcodeOffset_CONDITION); // write pcode
         							p->setPos(n);

         					} while (myIterateDo->nextCall	(myIterateDo->getId(), &p, &nPcodeOffset, &nCurrentline, &bGoto, &nPcodeId));

         				}
 								myIterateDo->removeLast();

 						}

         	}

 					p->setPos(nSavePcodeOffset);

				}
				parseInfo(p, "parsed DO..UNTIL WHILE");
				_DONE_
			}


      if (!(bTerm_WHILE = parseTerm(token__WHILE))){ goto exit; }

			if (bCONDITION = fCONDITION(p, &nExpressionType)){
				if (bProducePcode){

					nPcodeOffset_CJMP = p->getPos();
					p->wr_CJMP(pcode__CJMP, 0, true); // write pcode

					// cjmp, update jump destination
					int nSavePcodeOffset = p->getPos();
					p->setPos(nPcodeOffset_CJMP);
					p->wr_CJMP(pcode__CJMP, nPcodeOffset_DO, false); // write pcode
					p->setPos(nSavePcodeOffset);

         	{
         		int nPcodeOffset;
         		int nNewPcodeOffset = nSavePcodeOffset;
         		pcode *p = 0;
 						int nCurrentline;
						bool bGoto;
						t_pcode nPcodeId;

 						// EXIT DO/LOOP
         		if (myExitDo->last()){

         				if (myExitDo->firstCall (myExitDo->getId(), &p, &nPcodeOffset, &nCurrentline, &bGoto, &nPcodeId)){
         					do {

         							int n = p->getPos();
         							p->setPos(nPcodeOffset);
 											p->wr_JMP(pcode__JMP, nNewPcodeOffset); // write pcode
         							p->setPos(n);

         					} while (myExitDo->nextCall	(myExitDo->getId(), &p, &nPcodeOffset, &nCurrentline, &bGoto, &nPcodeId));

         				}
 								myExitDo->removeLast();

 						}

 						// ITERATE DO/LOOP
         		if (myIterateDo->last()){

         				if (myIterateDo->firstCall (myIterateDo->getId(), &p, &nPcodeOffset, &nCurrentline, &bGoto, &nPcodeId)){
         					do {

         							int n = p->getPos();
         							p->setPos(nPcodeOffset);
 											p->wr_JMP(pcode__JMP, nPcodeOffset_CONDITION); // write pcode
         							p->setPos(n);

         					} while (myIterateDo->nextCall	(myIterateDo->getId(), &p, &nPcodeOffset, &nCurrentline, &bGoto, &nPcodeId));

         				}
 								myIterateDo->removeLast();

 						}
         	}

 					p->setPos(nSavePcodeOffset);

				}
				parseInfo(p, "parsed DO..LOOP WHILE");
				_DONE_
			} else {
exit:
       rollbackVariable();
        // rollback
    	  myExitDo->removeLast();
       myIterateDo->removeLast();

      }
		}
	}

	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: DOLOOPUNTIL
PRINTNAME: Do...Loop Until
TASK: repeats until a condition is set
SYNTAX:
DO
.
.
statements
.
LOOP UNTIL condition

DESC:
CODE:
EXAMPLES: doloopuntil.kbasic
CATEGORY: KEYWORD, CONTROLFLOW, ITERATION, LOOP
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fDOLOOPUNTIL(pcode *p)
/*
[QBASIC]
[VB]
[*]
[*]
*/
{

  _BEGIN_

  // DO LOOP UNTIL is handled in DO LOOP WHILE

	//register bool bTerm_DO = false;
  if (!(/*bTerm_DO = */parseTerm(token__DO))){ _END_ } // to optimize, the 'do' is one of the first statements

	

  if (!bSilent && bProducePcode){
    p->wr_SEPARATOR(pcode__SEPARATOR, utility::con("fDOLOOPUNTIL", getCurrentLine() - 1));
  }

	bool bTerm_UNTIL = false;
	bool bCONDITION = false;
	bool bEOL = false;
	bool bREM = false;

	bool bSTATEMENTSEQUENCE = false;
	bool bTerm_LOOP = false;
	int nPcodeOffset_CJMP = 0;
	int nPcodeOffset_DO = 0;
	int nCurrentline = getCurrentLine();
	int nExpressionType;

	{
		if (bProducePcode){
			nPcodeOffset_DO = p->getPos();
		}

    if (bEOL = fEOLREM()){}

		myExitDo->addLabel(getScope(), getSub(), utility::toString(getCurrentLine())); // add one exit for handler
		myIterateDo->addLabel(getScope(), getSub(), utility::toString(getCurrentLine())); // add one exit for handler

		if ((bEOL == false && (bSTATEMENTSEQUENCE = fSTATEMENT(p))) || (bSTATEMENTSEQUENCE = fSTATEMENTSEQUENCE(p)) || bEOL){ // statement in one line, many statements in following lines, no statements in the following lines

			if (!bEOL && !bSTATEMENTSEQUENCE){ _END_ }

			int nPcodeOffset_CONDITION = p->getPos();

			if (bTerm_LOOP = parseTerm(token__LOOP))
		  if (bTerm_UNTIL = parseTerm(token__UNTIL))
			if (bCONDITION = fCONDITION(p, &nExpressionType)){
				if (bProducePcode){

					nPcodeOffset_CJMP = p->getPos();
					p->wr_CJMP(pcode__CJMP, 0, true); // write pcode

					// cjmp, update jump destination
					int nSavePcodeOffset = p->getPos();
					p->setPos(nPcodeOffset_CJMP);
					p->wr_CJMP(pcode__CJMP, nPcodeOffset_DO, true); // write pcode
					p->setPos(nSavePcodeOffset);

         	{
         		int nPcodeOffset;
         		int nNewPcodeOffset = nSavePcodeOffset;
         		pcode *p = 0;
 						int nCurrentline;
  					bool bGoto;
						t_pcode nPcodeId;

 						// EXIT DO/LOOP
         		if (myExitDo->last()){

         				if (myExitDo->firstCall (myExitDo->getId(), &p, &nPcodeOffset, &nCurrentline, &bGoto, &nPcodeId)){
         					do {

         							int n = p->getPos();
         							p->setPos(nPcodeOffset);
 											p->wr_JMP(pcode__JMP, nNewPcodeOffset); // write pcode
         							p->setPos(n);

         					} while (myExitDo->nextCall	(myExitDo->getId(), &p, &nPcodeOffset, &nCurrentline, &bGoto, &nPcodeId));

         				}
 								myExitDo->removeLast();

 						}

 						// ITERATE DO/LOOP
         		if (myIterateDo->last()){

         				if (myIterateDo->firstCall (myIterateDo->getId(), &p, &nPcodeOffset, &nCurrentline, &bGoto, &nPcodeId)){
         					do {

         							int n = p->getPos();
         							p->setPos(nPcodeOffset);
 											p->wr_JMP(pcode__JMP, nPcodeOffset_CONDITION); // write pcode
         							p->setPos(n);

         					} while (myIterateDo->nextCall	(myIterateDo->getId(), &p, &nPcodeOffset, &nCurrentline, &bGoto, &nPcodeId));

         				}
 								myIterateDo->removeLast();

 						}

         	}

 					p->setPos(nSavePcodeOffset);

				}
				parseInfo(p, "parsed DO..UNTIL WHILE");
				_DONE_
			}
		}
	}

  {
	 	if (!bSTATEMENTSEQUENCE){
      syntaxError(token__DO, "statement missing"); _END_
	  }
		else if (!bTerm_LOOP){ 				 syntaxError(token__DO, "LOOP missing"); _ERROR_ }
		else if (!bTerm_UNTIL){	 			 syntaxError(token__DO, ""/*UNTIL missing*/); _ERROR_ }
		else if (!bCONDITION){ 			   syntaxError(token__DO, ""/*condition missing*/); _ERROR_ }
	}

	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: EXITDO
PRINTNAME: Exit Do
TASK: breaks out of a loop
SYNTAX: EXIT DO
DESC:
CODE:
CATEGORY: KEYWORD, CONTROLFLOW, ITERATION, LOOP
SEEALSO: DOLOOP
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
/**
[KBASIC][VB][QBASIC]
NAME: EXITFOR
PRINTNAME: Exit For
TASK: breaks out of a for loop
SYNTAX: EXIT FOR
DESC:
CODE:
CATEGORY: KEYWORD, CONTROLFLOW, ITERATION, LOOP
SEEALSO: FORNEXT, FOREACH
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
/**
[KBASIC][VB][QBASIC]
NAME: EXITSUB
PRINTNAME: Exit Sub
TASK: exits a sub
SYNTAX: EXIT SUB
DESC: 
CODE:
CATEGORY: KEYWORD, CONTROLFLOW, ITERATION, LOOP
SEEALSO: SUB
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
/**
[KBASIC][VB][QBASIC]
NAME: EXITFUNCTION
PRINTNAME: Exit Function
TASK: exits a function
SYNTAX: EXIT FUNCTION
DESC:
CODE:
CATEGORY: KEYWORD, CONTROLFLOW, ITERATION, LOOP
SEEALSO: FUNCTION
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
/* *
[KBASIC][VB][QBASIC]
NAME: EXITSELECT
PRINTNAME: Exit Select
TASK: breaks out of a select case
SYNTAX: EXIT SELECT
DESC: 
CODE:
CATEGORY: KEYWORD, CONTROLFLOW, ITERATION, LOOP
SEEALSO: SELECTCASE
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
/* *
[KBASIC][VB][QBASIC]
NAME: EXITTRY
PRINTNAME: Exit Try
TASK: breaks out of a try catch
SYNTAX: EXIT TRY
DESC:
CODE:
CATEGORY: KEYWORD, CONTROLFLOW, ITERATION, LOOP
SEEALSO: TRY
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
/* *
[KBASIC][VB][QBASIC]
NAME: EXITPROPERTY
PRINTNAME: Exit Property
TASK: exits a property
SYNTAX: EXIT PROPERTY
DESC: 
CODE:
CATEGORY: KEYWORD, CONTROLFLOW, ITERATION, LOOP
SEEALSO: PROPERTY
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fEXIT(pcode *p)
{

	//register bool bTerm_EXIT = false;

  _BEGIN_

  if (!(/*bTerm_EXIT = */parseTerm(token__EXIT))){ _END_ }	

  if (!bSilent && bProducePcode){
    p->wr_SEPARATOR(pcode__SEPARATOR, utility::con("fEXIT", getCurrentLine() - 1));
  }

	bool bEOL = false;

	bool bTerm_DO = false;
	bool bTerm_FOR = false;
	bool bTerm_SUB = false;
	bool bTerm_FUNCTION = false;
	bool bTerm_DEF = false;
	bool bTerm_SELECT = false;
	bool bTerm_TRY = false;
	bool bTerm_PROPERTY = false;
  
  if ((bTerm_DO = parseTerm(token__DO)) || (bTerm_DO = parseTerm(token__LOOP))){

		if (bProducePcode){

			if (myExitDo->last()){
				myExitDo->registerCall(myExitDo->getId(), p, p->getPos(), getCurrentLine(), true, pcode__JMP);
			} else {
				{  syntaxError(token__EXIT, "EXIT DO/LOOP outside DO/LOOP statement"); _ERROR_ }
			}

			p->wr_JMP(pcode__JMP, 0); // write pcode
		}

		parseInfo(p, "parsed EXIT DO/LOOP");
		_DONE_

	} else if (bTerm_FOR = parseTerm(token__FOR)){

		if (bProducePcode){

			if (myExitFor->last()){
				myExitFor->registerCall(myExitFor->getId(), p, p->getPos(), getCurrentLine(), true, pcode__JMP);
			} else {
				{  syntaxError(token__EXIT, "EXIT FOR outside FOR..NEXT statement"); _ERROR_ }
			}

			p->wr_JMP(pcode__JMP, 0); // write pcode
		}

 		parseInfo(p, "parsed EXIT FOR");
 		_DONE_

	} else if (bTerm_SUB = parseTerm(token__SUB)){
    // test ob innerhalb einer sub oder function nicht notwendig, da vorher abgefangen

		if (bProducePcode){
			p->wr_CALL_RETURN(pcode__CALL_RETURN, isScopeClass()); // return to caller pcode
		}

 		parseInfo(p, "parsed EXIT SUB");
 		_DONE_

	} else if (bTerm_FUNCTION = parseTerm(token__FUNCTION)){

		if (bProducePcode){
      
      {

       memory_sub *s = 0;
       int nType = 0;
       int nId = 0;

       switch(isScopeClass()){
				  case false:
           nId = myModule->getId(getScope());
   				  s = myModule->getSubs(nId);
           nType = findType(s->type(s->getId(nId, getSub())));
					  break;
				  case true:
           nId = myClass->getId(getScope());
   				  s = myClass->getMethods(nId);
           nType = findType(s->type(s->getId(nId, getMethod())));
					  break;
			  }
        
       if (nType == 0){ semanticError(token__KEYWORD, utility::con(nType, " not defined") ); _ERROR_ ; }          

       // default function return expression
       defaultFunctionReturnExpression(p, nType);    	    
      
      }

			p->wr_CALL_RETURN(pcode__CALL_RETURN, isScopeClass()); // return to caller pcode
		}

 		parseInfo(p, "parsed EXIT FUNCTION");
 		_DONE_
	} else if (isVERYOLDBASIC() && (bTerm_DEF = parseTerm(token__DEF))){ // [QBASIC][!VB][!VBNET][!KBASIC]

		if (bProducePcode){
			p->wr_CALL_RETURN(pcode__CALL_RETURN, isScopeClass()); // return to caller pcode
		}

 		parseInfo(p, "parsed EXIT DEF");
 		_DONE_
	}

	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: ITERATEDO
PRINTNAME: Iterate Do
TASK: continues to iterate a loop if condition is set
SYNTAX: ITERATE DO
DESC:
CODE:
CATEGORY: KEYWORD, CONTROLFLOW, ITERATION, LOOP
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
/**
[KBASIC][VB][QBASIC]
NAME: ITERATEFOR
PRINTNAME: Iterate For
TASK: continues to iterate a for loop if condition is set
SYNTAX: ITERATE FOR
DESC:
CODE:
CATEGORY: KEYWORD, CONTROLFLOW, ITERATION
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fITERATE(pcode *p)
{

	//register bool bTerm_ITERATE = false;

  _BEGIN_    

  if (!(/*bTerm_ITERATE = */parseTerm(token__ITERATE))){ _END_ }	

  if (!bSilent && bProducePcode){
    p->wr_SEPARATOR(pcode__SEPARATOR, utility::con("fITERATE", getCurrentLine() - 1));
  }

	bool bTerm_DO = false;

  if ((bTerm_DO = parseTerm(token__DO))){

		if (bProducePcode){

			if (myIterateDo->last()){
				myIterateDo->registerCall(myIterateDo->getId(), p, p->getPos(), getCurrentLine(), true, pcode__JMP);
			} else {
				{  syntaxError(token__ITERATE, "ITERATE DO outside DO/LOOP statement"); _ERROR_ }
			}

			p->wr_JMP(pcode__JMP, 0); // write pcode

		}

 		parseInfo(p, "parsed ITERATE DO");
 		_DONE_

	}

  bool bTerm_FOR = false;

  if ((bTerm_FOR = parseTerm(token__FOR))){

		if (bProducePcode){

			if (myIterateFor->last()){
				myIterateFor->registerCall(myIterateFor->getId(), p, p->getPos(), getCurrentLine(), true, pcode__JMP);
			} else {
				{  syntaxError(token__ITERATE, "ITERATE FOR outside FOR/LOOP statement"); _ERROR_ }
			}

			p->wr_JMP(pcode__JMP, 0); // write pcode

		}

 		parseInfo(p, "parsed ITERATE FOR");
 		_DONE_

	}

	{ semanticError(token__ITERATE, "missing DO or FOR after ITERATE"); _ERROR_ }
}

/**
[KBASIC][VB][QBASIC]
NAME: ONERROR
PRINTNAME: On Error
TASK: jumps to desired label or line if an error occured
SYNTAX: ON ERROR
DESC:
CODE:
EXAMPLES: onerror.kbasic
CATEGORY: KEYWORD, CONTROLFLOW, ERROR, DECISION
SEEALSO: ERR, ERL, ERROR, GOTO, RESUME, TRY
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fONERROR(pcode *p)
/*
[QBASIC]
[VB]
[*]
[*]
*/
{

  _BEGIN_

	//register bool bTerm_ON = false;

  if (!(/*bTerm_ON = */parseTerm(token__ON))){ _END_ }	

  if (parseTerm(token__TIMER)) _END_

  if (!bSilent && bProducePcode){
    p->wr_SEPARATOR(pcode__SEPARATOR, utility::con("fONERROR", getCurrentLine() - 1));
  }

	//bool bTerm_ERROR = false;

  if (!(/*bTerm_ERROR = */parseTerm(token__ERROR))){ _END_ }//syntaxError(token__ON, "ERROR missing"); _ERROR_ }

	bool bTerm_GOTO = false;

	bool bTerm_RESUME = false;
	bool bTerm_NEXT = false;

	bool bIDENTIFIER = false;

	const char *acIdentifier = "";
	bool bINTEGER = false;
	int nInteger = 0;

  if (bTerm_GOTO = parseTerm(token__GOTO)){
  	if ((bIDENTIFIER = fID_KEYWORD_OR_BUILTIN(&acIdentifier)) || (bINTEGER = fINTEGER(&nInteger))){

   		if (bINTEGER) acIdentifier = utility::toString(nInteger);

   		// label position will be refilled after the complete program has been parsed, last step, before using place holder

   		int nId = myMemory_label->getId(getScope(), getSub(), acIdentifier);

   		// label still not declared
   		if (nId == 0){
   			nId = myMemory_label->addLabel(getScope(), getSub(), acIdentifier);
   		}

   		myMemory_label->registerCall(nId, p, p->getPos(), nCurrentLine, true, pcode__ONERRORGOTO);

  		if (bProducePcode){
  			p->wr_ONERRORGOTO(pcode__ONERRORGOTO, 0); // write pcode
  		}

  		parseInfo(p, "parsed ON ERROR GOTO");
  		_DONE_
  	}

   			 if (!bTerm_GOTO){ syntaxError(token__ON, "GOTO missing"); _ERROR_ }
   	else if (!bIDENTIFIER){ syntaxError(token__ON, "label name or line number missing"); _ERROR_ }
  	else if(!bINTEGER){ syntaxError(token__ON, "label name or line number missing"); _ERROR_ }

	} else {
	  if (bTerm_RESUME = parseTerm(token__RESUME))
	  if (bTerm_NEXT = parseTerm(token__NEXT)){

  		if (bProducePcode){
  			p->wr_ONERRORGOTORESUMENEXT(pcode__ONERRORGOTORESUMENEXT); // write pcode
  		}

  		parseInfo(p, "parsed ON ERROR GOTO RESUME NEXT");
  		_DONE_

		}

   			 if (!bTerm_RESUME){ syntaxError(token__ON, "RESUME missing"); _ERROR_ }
   	else if (!bTerm_NEXT){ syntaxError(token__ON, "NEXT missing"); _ERROR_ }

	}

	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: ONGOSUB
PRINTNAME: On...Gosub
TASK: jumps to the desired sub
SYNTAX: ON expression% GOSUB lines | labels
DESC:
CODE:
FOR i% = 1 TO 2
    ON i% GOSUB Eins, Zwei
NEXT i%
END

Eins: PRINT "Eins"
RETURN
Zwei: PRINT "Zwei"
RETURN
EXAMPLES: ongosub.kbasic
CATEGORY: KEYWORD, CONTROLFLOW, DECISION
SEEALSO: SELECTCASE
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fONGOSUB(pcode *p)
/*
[QBASIC]
[VB]
[*]
[*]
*/
{
  _BEGIN_

	//register bool bTerm_ON = false;

  if (!(/*bTerm_ON = */parseTerm(token__ON))){ _END_ }

	
  if (!bSilent && bProducePcode){
    p->wr_SEPARATOR(pcode__SEPARATOR, utility::con("fONGOSUB", getCurrentLine() - 1));
  }

	bool bTerm_GOSUB = false;
	bool bEXPRESSION = false;

	bool bTerm_COMMA = false;

	static /**/ bool bIDENTIFIER[parser__MAX_ONGOSUB];
	static /**/ const char *acIdentifier[parser__MAX_ONGOSUB];
	static /**/ bool bINTEGER[parser__MAX_ONGOSUB];
	static /**/ int nInteger[parser__MAX_ONGOSUB];
	static /**/ int nReturn[parser__MAX_ONGOSUB];

	int nComma = 0;

	if (!(bEXPRESSION = fINTEGER_EXPRESSION(p))){ _END_ }

  if (!(bTerm_GOSUB = parseTerm(token__GOSUB))){ _END_ }

	while (true){

	 	if (nComma >= parser__MAX_ONGOSUB){ internalError("too many label or line definitions in one line"); _ERROR_ }


		bINTEGER[nComma] = false;
		if ((bIDENTIFIER[nComma] = fID_KEYWORD_OR_BUILTIN(&acIdentifier[nComma])) || (bINTEGER[nComma] = fINTEGER(&nInteger[nComma]))){
		} else {
			{ syntaxError(token__ON, "label name or line number missing"); _ERROR_ }
		}

	  if (bTerm_COMMA = parseTerm(token__SYM_COMMA)){
			nComma++;
		} else {

			if (bIDENTIFIER[0] || bINTEGER[0]){

				for (int i = nComma; i >= 0; i--){

       		if (bINTEGER[i]) acIdentifier[i] = utility::toString(nInteger[i]);

       		// label position will be refilled after the complete program has been parsed, last step, before using place holder

       		int nId = myMemory_label->getId(getScope(), getSub(), acIdentifier[i]);

       		// label still not declared
       		if (nId == 0){
       			nId = myMemory_label->addLabel(getScope(), getSub(), acIdentifier[i]);
       		}


      		if (bProducePcode){
						p->wr_PUSH_INTEGER(pcode__PUSH_INTEGER, i + 1); // write pcode
						p->wr_EQUAL(pcode__UNEQUAL, false); // write pcode
						p->wr_CJMP(pcode__CJMP, p->getPos() + pcode::len(pcode__CJMP)	+ pcode::len(pcode__PUSH_INTEGER) + pcode::len(pcode__JMP), false); // write pcode, new jump destination
						nReturn[i] = p->getPos();
						p->wr_PUSH_INTEGER(pcode__PUSH_INTEGER, 0); // push current pcode pos on stack
	       		myMemory_label->registerCall(nId, p, p->getPos(), nCurrentLine, true, pcode__JMP);
      			p->wr_JMP(pcode__JMP, 0); // write pcode
					}

				}

				int n = p->getPos();
				for (int z = nComma; z >= 0; z--){
      		if (bProducePcode){
						p->setPos(nReturn[z]);
						p->wr_PUSH_INTEGER(pcode__PUSH_INTEGER, n); // push current pcode pos on stack
					}
				}
				p->setPos(n);

			} else {
 				{ syntaxError(token__ON, "label name or line number missing"); _ERROR_ }
			}

  		parseInfo(p, "parsed ON .. GOSUB");
  		_DONE_

		}

	}

	_END_
}

/* *
[KBASIC][VB][QBASIC]
NAME: ONTIMER
PRINTNAME: On Timer
TASK: jumps to the desired place after a defined period of time
SYNTAX: ON TIMER(n%) GOSUB line | label 
DESC:
CODE:
EXAMPLES: ontimer.kbasic
CATEGORY: KEYWORD, CONTROLFLOW, DECISION
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fONTIMER(pcode *p)
/*
[QBASIC]
[VB]
[*]
[*]
*/
{

  _BEGIN_

	//register bool bTerm_ON = false;

  if (!(/*bTerm_ON = */parseTerm(token__ON))){ _END_ }

	

	register bool bTerm_TIMER = false;
	
  if (!(bTerm_TIMER = parseTerm(token__TIMER))){ _END_ } // no error, because it could be ON ERROR... //syntaxError(token__ON, "TIMER missing"); _ERROR_ }

  if (!bSilent && bProducePcode){
    p->wr_SEPARATOR(pcode__SEPARATOR, utility::con("fONTIMER", getCurrentLine() - 1));
  }

	bool bTerm_GOSUB = false;
	bool bEXPRESSION = false;

	bool bTerm_COMMA = false;
	bool bTerm_SYM_BR_OP = false;
	bool bTerm_SYM_BR_CL = false;

	bool bIDENTIFIER = false;
	const char *acIdentifier = false;
	bool bINTEGER = false;
	int nInteger = 0;
	int nReturn = 0;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){}

	if (!(bEXPRESSION = fINTEGER_EXPRESSION(p))){ _END_ }

	if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
 	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__TIMER, ") missing"); _ERROR_ }

  if (!(bTerm_GOSUB = parseTerm(token__GOSUB))){ _END_ }

	bINTEGER = false;
	if ((bIDENTIFIER = fID_KEYWORD_OR_BUILTIN(&acIdentifier)) || (bINTEGER = fINTEGER(&nInteger))){
	} else {
		{ syntaxError(token__ON, "label name or line number missing"); _ERROR_ }
	}

  if (bINTEGER) acIdentifier = utility::toString(nInteger);

  // label position will be refilled after the complete program has been parsed, last step, before using place holder

  int nId = myMemory_label->getId(getScope(), getSub(), acIdentifier);

  // label still not declared
  if (nId == 0){
    nId = myMemory_label->addLabel(getScope(), getSub(), acIdentifier);
  }

  if (bProducePcode){

	  myMemory_label->registerCall(nId, p, p->getPos(), nCurrentLine, true, pcode__ONTIMERGOSUB);
    p->wr_ONTIMERGOSUB(pcode__ONTIMERGOSUB, 0); // write pcode
    
	}

  parseInfo(p, "parsed ON TIMER .. GOSUB");
  _DONE_

	//}

//	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: ONGOTO
PRINTNAME: On...Goto
TASK: jumps to another line or label depending on an expression
SYNTAX: ON expression% GOTO labels | lines
DESC: 
CODE:

FOR i% = 1 TO 2
    ON i% GOTO Eins, Zwei
NEXT i%
END

Eins: PRINT "Eins"
END
Zwei: PRINT "Zwei"
END

EXAMPLES: ongoto.kbasic
CATEGORY: KEYWORD, CONTROLFLOW, DECISION
SEEALSO: SELECTCASE
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fONGOTO(pcode *p)
/*
[QBASIC]
[VB]
[*]
[*]
*/
{

  _BEGIN_

	//register bool bTerm_ON = false;

  if (!(/*bTerm_ON = */parseTerm(token__ON))){ _END_ }

	


  if (!bSilent && bProducePcode){
    p->wr_SEPARATOR(pcode__SEPARATOR, utility::con("fONGOTO", getCurrentLine() - 1));
  }

	bool bTerm_GOTO = false;
	bool bEXPRESSION = false;

	bool bTerm_COMMA = false;

	static /**/ bool bIDENTIFIER[parser__MAX_ONGOTO];
	static /**/ const char *acIdentifier[parser__MAX_ONGOTO];
	static /**/ bool bINTEGER[parser__MAX_ONGOTO];
	static /**/ int nInteger[parser__MAX_ONGOTO];

	int nComma = 0;

	if (!(bEXPRESSION = fINTEGER_EXPRESSION(p))){ _END_ }

  if (!(bTerm_GOTO = parseTerm(token__GOTO))){ _END_ }

	while (true){

	 	if (nComma >= parser__MAX_ONGOTO){ internalError("too many label or line refered in one line"); _ERROR_ }

		bINTEGER[nComma] = false;
		if ((bIDENTIFIER[nComma] = fID_KEYWORD_OR_BUILTIN(&acIdentifier[nComma])) || (bINTEGER[nComma] = fINTEGER(&nInteger[nComma]))){
		} else {
			{ syntaxError(token__ON, "label name or line number missing"); _ERROR_ }
		}

	  if (bTerm_COMMA = parseTerm(token__SYM_COMMA)){
			nComma++;
		} else {

			if (bIDENTIFIER[0] || bINTEGER[0]){

				for (int i = nComma; i >= 0; i--){

       		if (bINTEGER[i]) acIdentifier[i] = utility::toString(nInteger[i]);

       		// label position will be refilled after the complete program has been parsed, last step, before using place holder

       		int nId = myMemory_label->getId(getScope(), getSub(), acIdentifier[i]);

       		// label still not declared
       		if (nId == 0){
       			nId = myMemory_label->addLabel(getScope(), getSub(), acIdentifier[i]);
       		}

      		if (bProducePcode){
						p->wr_PUSH_INTEGER(pcode__PUSH_INTEGER, i + 1); // write pcode
						p->wr_EQUAL(pcode__UNEQUAL, false); // write pcode
						p->wr_CJMP(pcode__CJMP, p->getPos() + pcode::len(pcode__CJMP) + pcode::len(pcode__JMP), false); // write pcode, new jump destination
	       		myMemory_label->registerCall(nId, p, p->getPos(), nCurrentLine, true, pcode__JMP);
      			p->wr_JMP(pcode__JMP, 0); // write pcode
					}

				}

			} else {
 				{ syntaxError(token__ON, "label name or line number missing"); _ERROR_ }
			}

  		parseInfo(p, "parsed ON .. GOSUB");
  		_DONE_

		}

	}

	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: RESUME
PRINTNAME: Resume
TASK: continues execution after an error occured
SYNTAX: RESUME [{label | line | NEXT}]
DESC:
CODE:
EXAMPLES: resume.kbasic
CATEGORY: KEYWORD, CONTROLFLOW, ERROR
SEEALSO: ERROR, ONERROR
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fRESUME(pcode *p)
/*
[QBASIC]
[VB]
[*]
[*]
*/
{

	//register bool bTerm_RESUME = false;
  _BEGIN_

  if (!(/*bTerm_RESUME = */parseTerm(token__RESUME))){ _END_ }
	

  if (!bSilent && bProducePcode){
    p->wr_SEPARATOR(pcode__SEPARATOR, utility::con("fRESUME", getCurrentLine() - 1));
  }

	bool bTerm_NEXT = false;
	bool bIDENTIFIER = false;
	bool bEOL = false;
	bool bREM = false;
	const char *acIdentifier;
	bool bINTEGER = false;
	int nInteger;

  if (bTerm_NEXT = parseTerm(token__NEXT)){

		if (bProducePcode){
			p->wr_RESUME(pcode__RESUME, -1); // write pcode
		}

		parseInfo(p, "parsed RESUME NEXT");
		_DONE_

	} else if ((bIDENTIFIER = fID_KEYWORD_OR_BUILTIN(&acIdentifier)) || (bINTEGER = fINTEGER(&nInteger))){

 		if (bINTEGER) acIdentifier = utility::toString(nInteger);

 		// label position will be refilled after the complete program has been parsed, last step, before using place holder

 		int nId = myMemory_label->getId(getScope(), getSub(), acIdentifier);

 		// label still not declared
 		if (nId == 0){
 			nId = myMemory_label->addLabel(getScope(), getSub(), acIdentifier);
 		}

 		myMemory_label->registerCall(nId, p, p->getPos(), nCurrentLine, true, pcode__RESUME);

		if (bProducePcode){
			p->wr_RESUME(pcode__RESUME, 0); // write pcode
		}

		parseInfo(p, "parsed RESUME label");
		_DONE_
  } else {

		if (bProducePcode){
			p->wr_RESUME(pcode__RESUME, 0); // write pcode
		}

		parseInfo(p, "parsed RESUME");
		_DONE_

	}

	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: GOTO
PRINTNAME: GoTo
TASK: jumps to the desired label or line
SYNTAX: GOTO line | label
DESC:
CODE:
DIM b AS INTEGER
DIM n AS INTEGER

b = 45
GOTO bernd
b = 99999
bernd:

n = 0
ok:
n = n + 1
IF n < 5 THEN GOTO ok
EXAMPLES: goto.kbasic
CATEGORY: KEYWORD, CONTROLFLOW
SEEALSO: DOLOOP, FUNCTION, SUB, IF, ONERROR, SELECTCASE
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fGOTO(pcode *p, bool bParseGotoKeyword)
/*
[QBASIC]
goto 0 schaltet fehlerbehandlung aus
[VB]
[!VBNET]
[!KBASIC]
*/
{
	_BEGIN_

	register bool bTerm_GOTO = false;

  if (bParseGotoKeyword == false || (bTerm_GOTO = parseTerm(token__GOTO))){

	  bool bIDENTIFIER = false;
	  const char *acIdentifier;
	  bool bINTEGER = false;
	  int nInteger;
	  bool bEOL = false;

	  if ((bIDENTIFIER = fID_KEYWORD_OR_BUILTIN(&acIdentifier)) || (bINTEGER = fINTEGER(&nInteger))){

      if (!bSilent && bProducePcode){
       p->wr_SEPARATOR(pcode__SEPARATOR, utility::con("fGOTO", getCurrentLine() - 1));
      }

 		  if (bINTEGER) acIdentifier = utility::toString(nInteger);

 		  // label position will be refilled after the complete program has been parsed, last step, before using place holder

 		  int nId = myMemory_label->getId(getScope(), getSub(), acIdentifier);

 		  // label still not declared
 		  if (nId == 0){
 			  nId = myMemory_label->addLabel(getScope(), getSub(), acIdentifier);
       // goto darf nicht sub verlassen, muss local bleiben; wird woanders gechecked
 		  }

 		  myMemory_label->registerCall(nId, p, p->getPos(), nCurrentLine, true, pcode__JMP);

		  if (bProducePcode){
			  p->wr_JMP(pcode__JMP, 0); // write pcode
		  }

		  parseInfo(p, "parsed GOTO");

		  _DONE_
    }

	  if (bTerm_GOTO){
 	 			  if (!bIDENTIFIER){ syntaxError(token__GOTO, "label name or line number missing"); _ERROR_ }
 		  else if(!bINTEGER){ syntaxError(token__GOTO, "label name or line number missing"); _ERROR_ }
	  }

  }

	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: GOSUB
PRINTNAME: GoSub
TASK: jumps to the desired sub
SYNTAX: GOSUB label | line
DESC:
CODE:
FOR i% = 1 TO 20
    GOSUB square
NEXT i%
END

square:
PRINT i%, i% * i%
RETURN
EXAMPLES: gosub.kbasic
CATEGORY: KEYWORD, CONTROLFLOW
SEEALSO: SUB
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fGOSUB(pcode *p)
/*
[QBASIC]
[VB]
[!VBNET]
[!KBASIC]
*/
{

	//bool bTerm_GOSUB = false;

  _BEGIN_

  if (/*bTerm_GOSUB = */parseTerm(token__GOSUB)){

	

	  bool bIDENTIFIER = false;

	  const char *acIdentifier;
	  bool bINTEGER = false;
	  int nInteger;

	  if ((bIDENTIFIER = fID_KEYWORD_OR_BUILTIN(&acIdentifier)) || (bINTEGER = fINTEGER(&nInteger))){

      if (!bSilent && bProducePcode){
       p->wr_SEPARATOR(pcode__SEPARATOR, utility::con("fGOSUB", getCurrentLine() - 1));
      }

 		  if (bINTEGER) acIdentifier = utility::toString(nInteger);

 		  // label position will be refilled after the complete program has been parsed, last step, before using place holder

 		  int nId = myMemory_label->getId(getScope(), getSub(), acIdentifier);

 		  // label still not declared
 		  if (nId == 0){
 			  nId = myMemory_label->addLabel(getScope(), getSub(), acIdentifier);
 		  }

 		  myMemory_label->registerCall(nId, p, p->getPos(), nCurrentLine, false, pcode__JMP);

		  if (bProducePcode){
			  p->wr_PUSH_INTEGER(pcode__PUSH_INTEGER, p->getPos() + pcode::len(pcode__PUSH_INTEGER) + pcode::len(pcode__JMP)); // push current pcode pos on stack
			  p->wr_JMP(pcode__JMP, 0); // write pcode
		  }

		  parseInfo(p, "parsed GOSUB");
		  _DONE_
	  }
	  
    {
 	 			  if (!bIDENTIFIER){ syntaxError(token__GOSUB, "label name or line number missing"); _ERROR_ }
 		  else if(!bINTEGER){ syntaxError(token__GOSUB, "label name or line number missing"); _ERROR_ }
	  }
    _END_

  }


	_END_;
}

/**
[KBASIC][VB][QBASIC]
NAME: LABEL2
PRINTNAME: Label
TASK: defines a label which can be used for jumping
SYNTAX: <name>:
DESC: 
CODE:
EXAMPLES: label.kbasic
CATEGORY: KEYWORD, CONTROLFLOW
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fLABEL(pcode *p)
{

	if (peekToken() == token__MSC_LABEL){
	

		myToken->rd_Token(getTokenPos());
		const char *acLabel = myToken->rd_CString( getTokenPos() );

 		int nLabels = myMemory_label->addLabel(getScope(), getSub(), acLabel);
 	  if (nLabels == 0){
 		  if (myMemory_label->getPcodeOffset(myMemory_label->getId(getScope(), getSub(), acLabel))){
 				semanticError(token__KEYWORD, utility::con(acLabel, " already declared (label) at some place") ); _ERROR_
 			}
 		}

 		myMemory_label->setPcodeOffset(myMemory_label->getId(getScope(), getSub(), acLabel), p->getPos());

 		parseInfo(p, "parsed LABEL");
 		_DONE_

	}

  return false;	
}

/**
[KBASIC][VB][QBASIC]
NAME: LINENO
PRINTNAME: LineNo
TASK: defines a line which can be used for jumping
SYNTAX: <lineno>:
DESC: 
CODE:
CATEGORY: KEYWORD, CONTROLFLOW
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fLINE(pcode *p)
{
	//_BEGIN_

	if (peekToken() == token__MSC_LINE){

    if (!isVERYOLDBASIC()){
      semanticError(token__MSC_LINE, "line numbers are supported only within VERYOLDBASIC. Use OPTION VERYOLDBASIC on top of your program to be allowed to use line numbers");
      _ERROR_
    }
		myToken->rd_Token( getTokenPos() );
		const char *acLabel = myToken->rd_CString( getTokenPos() );
/*
    if (strcmp(acLabel, "333") == 0){
      int i = 0;
      i++;
    }
    */
		int nLabels = myMemory_label->addLabel(getScope(), getSub(), acLabel);
	  if (nLabels == 0){
      // could be already declard, because of roll back of a production like doloopwhile
 		  if (myMemory_label->getPcodeOffset(myMemory_label->getId(getScope(), getSub(), acLabel))){
 				semanticError(token__KEYWORD, utility::con(acLabel, " already declared (line) at some place") ); _ERROR_
 			}
    }
    {
       myMemory_label->setPcodeOffset(myMemory_label->getId(getScope(), getSub(), acLabel), p->getPos());
    }

		parseInfo(p, "parsed LINE");
		_DONE_

	}

  return false;
	//_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: RETURN
PRINTNAME: Return
TASK: returns either from a gosub call or leaves the function or sub
SYNTAX: RETURN [expression]
DESC:
CODE:
CATEGORY: KEYWORD, CONTROLFLOW
SEEALSO: ONGOSUB, SUB
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
// [QBASIC] return ohne gosub
// befehl berladen, alte bedeutung + funktionsrckgabewert neu
bool parser::fRETURN(pcode *p)
/*
[QBASIC]
[*]
[*]
[*]
*/
{

	//register bool bTerm_RETURN = false;
  _BEGIN_

  if (/*bTerm_RETURN = */parseTerm(token__RETURN)){

    	


    if (!bSilent && bProducePcode){
      p->wr_SEPARATOR(pcode__SEPARATOR, utility::con("fRETURN", getCurrentLine() - 1));
    }

	  bool bIDENTIFIER = false;
	  const char *acIdentifier;
	  bool bINTEGER = false;
	  int nInteger = 0;
  	bool bEXPRESSION = false;
  	int nExpressionType = 0;

#ifdef KBDEBUG
    if (stopAtLine(118)){
      int i = 9;
      i++;
    }
#endif

  	if ((isOLDBASIC() || isVERYOLDBASIC()) && ((bIDENTIFIER = fID_KEYWORD_OR_BUILTIN(&acIdentifier)) || (bINTEGER = fINTEGER(&nInteger)))){

   		if (bINTEGER) acIdentifier = utility::toString(nInteger);

   		// label position will be refilled after the complete program has been parsed, last step, before using of a place holder

   		int nId = myMemory_label->getId(getScope(), getSub(), acIdentifier);

   		// label still not declared
   		if (nId == 0){
   			nId = myMemory_label->addLabel(getScope(), getSub(), acIdentifier);
   		}

   		myMemory_label->registerCall(nId, p, p->getPos(), nCurrentLine, true, pcode__JMP);

			if (bProducePcode){
 				p->wr_JMP(pcode__JMP, 0); // return to caller pcode
			}

		  parseInfo(p, "parsed RETURN");
		  _DONE_

  	} else if (isOLDBASIC() || isVERYOLDBASIC()){

  		if (bProducePcode){
   			p->wr_RETURN(pcode__RETURN); // return to caller pcode
  		}

      parseInfo(p, "parsed RETURN");
   		_DONE_
        
    } else if ((bEXPRESSION = fEXPRESSION(p, &nExpressionType))){

       if (!(
            isScopeClassLocalStatic() 
         || isScopeClassLocalInstance() 
         || isScopeModuleLocal()
         || isScopeModuleLocalStatic()
         )){
          semanticError(token__RETURN, "return used outside of sub/function/method"); _ERROR_ 
         }

      const char *ac = "";
      int nType = 0;

      if (isScopeClass()){
        ac = myClass->typeMethod(getClass(), getMethod());
      } else if (isScopeModule()){
        ac = myModule->typeSub(getModule(), getSub());
      } if (isScopeClassPropertySet()){
        ac = myClass->typePropertySet(getClass(), getMethod());
      } if (isScopeClassPropertyGet()){
        ac = myClass->typePropertyGet(getClass(), getMethod());
      }

	    nType = findType(ac);
		  if (nType == 0){ internalError(utility::con(ac, " not defined") ); _ERROR_ }

      if (!compatibleType(nExpressionType, nType)){ semanticError(token__RETURN, "incompatible types: return type differs from sub/funtion/method definition"); _ERROR_ }

      {
  		  if (bProducePcode){
         p->wr_CALL_RETURN(pcode__CALL_RETURN, isScopeClass()); // return to caller pcode
  		  }
      }

		  parseInfo(p, "parsed RETURN");
		  _DONE_

    } else {

       if (!(
            isScopeClassLocalStatic() 
         || isScopeClassLocalInstance() 
         || isScopeModuleLocal()
         || isScopeModuleLocalStatic()
         )){
          semanticError(token__RETURN, "return used outside of sub/function/method"); _ERROR_ 
         }

      {
  		  if (bProducePcode){
         p->wr_CALL_RETURN(pcode__CALL_RETURN, isScopeClass()); // return to caller pcode
  		  }
      }

		  parseInfo(p, "parsed RETURN");
		  _DONE_

    }
    _END_

	}

  _END_

}

bool parser::cleanUpLabels()
{

	int nPcodeOffset = 0;
	int nNewPcodeOffset = 0;
	pcode *p = 0;
	int nCurrentLine = 0;
	bool bGoto = false;
	t_pcode nPcodeId = 0;


	if (myMemory_label->first()){
		do {

			nNewPcodeOffset = myMemory_label->getPcodeOffset(myMemory_label->getId());
			// label-nNewPcodeOffset must be delcared > 0

			if (nNewPcodeOffset == 0){
  			semanticError(token__KEYWORD, utility::con(myMemory_label->getName(), " not declared in SUB/FUNCTION or GLOBAL") );
        _ERROR_				
			}

			if (myMemory_label->firstCall (myMemory_label->getId(), &p, &nPcodeOffset, &nCurrentLine, &bGoto, &nPcodeId)){
				do {

 		 			if (bProducePcode){

 						int n = p->getPos();
 						p->setPos(nPcodeOffset);

 						switch(nPcodeId){
              case pcode__ONTIMERGOSUB:
 								p->wr_ONTIMERGOSUB(pcode__ONTIMERGOSUB, nNewPcodeOffset); // call address of sub, later it will be the real address
                break;
							case pcode__JMP:
								if (bGoto){
 									p->wr_JMP(pcode__JMP, nNewPcodeOffset); // call address of sub, later it will be the real address
								} else {
									p->wr_PUSH_INTEGER(pcode__PUSH_INTEGER, p->getPos() + pcode::len(pcode__PUSH_INTEGER) + pcode::len(pcode__JMP)); // push current pcode pos on stack
									p->wr_JMP(pcode__JMP, nNewPcodeOffset); // write pcode
								}
								break;
							case pcode__ONERRORGOTO:
								p->wr_ONERRORGOTO(pcode__ONERRORGOTO, nNewPcodeOffset); // write pcode
								break;
							case pcode__RESUME:
								p->wr_RESUME(pcode__RESUME, nNewPcodeOffset); // write pcode
								break;
								
							default:
                internalError("in cleanUpLabels: invalid nPcodeId");
                _ERROR_
								break;
						}

 						p->setPos(n);
 					}

				} while (myMemory_label->nextCall (myMemory_label->getId(),&p, &nPcodeOffset, &nCurrentLine, &bGoto, &nPcodeId));
			}

		} while (myMemory_label->next());
	}

	return true;

}

