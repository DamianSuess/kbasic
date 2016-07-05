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
NAME: CLS
PRINTNAME: CLS
TASK: Clears the terminal screen. Returns the cursor to the upper left corner.
SYNTAX: CLS[numeric expression]
DESC: 
In the terminal screen, CLS will clear the screen and returns the cursor to
the upper left corner (line 1, column 1).
CODE:
' CLS clearing the terminal screen
' with a new background color

PRINT "This is to show the CLS command"
INPUT "To clear the screen, press [Return]", keypressed$

' changes the background color:
COLOR (2, 4)
CLS
PRINT "This is green text on a blue screen!"

EXAMPLES: cls.kbasic
CATEGORY: SUB, BUILTIN, SCREEN
SEEALSO: VIEW, VIEW PRINT, WINDOW
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fCLS(pcode *p)
/*
[QBASIC]
[*]
[*]
[*]
*/
{

	//bool bTerm_CLS = false;
	_BEGIN_

  if (!(/*bTerm_CLS = */parseTerm(token__CLS))){ _END_ }



 	static /**/ bool bTerm_SYM_BR_OP;
 	static /**/ bool bTerm_SYM_BR_CL;

  static /**/ bool bEXPRESSION = false;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){}

  if (bEXPRESSION = fNUMERIC_EXPRESSION(p)){}

  if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
 	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__CLS, ") missing"); _ERROR_ }

	{

 		if (bProducePcode){
  		p->wr_CLS(pcode__CLS, bEXPRESSION);
 		}

 		parseInfo(p, "parsed CLS");
 		_DONE_
	}

	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: LOCATE
PRINTNAME: Locate
TASK: set the cursor position
SYNTAX: LOCATE [y] [,x] [,cursor]
DESC: 
CODE:
CLS
LOCATE 5, 5
row% = CSRLIN
column% = POS(0)
PRINT "position 1 (press any key)"
DO
LOOP WHILE INKEY$ = ""
LOCATE (row% + 2), (column% + 2)
PRINT "position 2"
EXAMPLES: locate.kbasic
CATEGORY: SUB, BUILTIN, SCREEN
SEEALSO: CSRLIN, POS, PRINT
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fLOCATE(pcode *p)
/*
[QBASIC]
[*]
[*]
[*]
*/
{

	//bool bTerm_LOCATE = false;
	_BEGIN_
  if (!(/*bTerm_LOCATE = */parseTerm(token__LOCATE))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	bool bTerm_COMMA = false;

	bool bEXPRESSION = false;
	bool bEXPRESSION2 = false;
	bool bEXPRESSION3 = false;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){}

	if (bEXPRESSION = fINTEGER_EXPRESSION(p)){}

  if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL)))){ bTerm_SYM_BR_OP = false; }
 	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__CLS, ") missing"); _ERROR_ }

  if (bTerm_COMMA = parseTerm(token__SYM_COMMA)){
		if (bEXPRESSION2 = fINTEGER_EXPRESSION(p)){}
  	if (!bEXPRESSION2){ syntaxError(token__LOCATE, "expression missing"); _ERROR_ }

    if (bTerm_COMMA = parseTerm(token__SYM_COMMA)){
		  if (bEXPRESSION3 = fINTEGER_EXPRESSION(p)){}
  	  if (!bEXPRESSION3){ syntaxError(token__LOCATE, "expression missing"); _ERROR_ }
	  }
  }

 	if (!bEXPRESSION && !bEXPRESSION2 && !bEXPRESSION3){ syntaxError(token__LOCATE, "expression missing"); _ERROR_ }

  if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL)))){}
 	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__CLS, ") missing"); _ERROR_ }

	{

 		if (bProducePcode){
			p->wr_LOCATE(pcode__LOCATE, bEXPRESSION, bEXPRESSION2, bEXPRESSION3);
 		}

 		parseInfo(p, "parsed LOCATE");
 		_DONE_
	}

	_END_
}


/**
[KBASIC][VB][QBASIC]
NAME: COLOR
PRINTNAME: Color
TASK: COLOR alters the background and foreground color of the terminal screen.
SYNTAX: COLOR(Fore AS INTEGER [, Back AS INTEGER])
DESC: 
Calling COLOR will set the color of either the
foreground and optionally the background. Passing
only one integer will change the fore color. Passing
2 will change both the fore and background color.

CODE:
COLOR(5)
PRINT "Hi"
COLOR(15,1)
PRINT "Nadja"
EXAMPLES: color.kbasic
CATEGORY: SUB, BUILTIN, SCREEN
SEEALSO: DRAW, PAINT, SCREEN
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fCOLOR(pcode *p)
/*
[QBASIC]
[*]
[*]
[*]
*/
{

	//bool bTerm_COLOR = false;
	_BEGIN_
  if (!(/*bTerm_COLOR = */parseTerm(token__COLOR))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;
	bool bTerm_COMMA = false;

	bool bEXPRESSION = false;
	bool bEXPRESSION2 = false;

	int nExpressionType = 0;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){}

 	if ((bEXPRESSION = fEXPRESSION(p, &nExpressionType))){
	 	if (!memory_type::isNumeric(nExpressionType)){ syntaxError(token__COLOR, "wrong type, must be a number type"); _ERROR_ }
	}

  if (bTerm_COMMA = parseTerm(token__SYM_COMMA)){

   	if ((bEXPRESSION2 = fEXPRESSION(p, &nExpressionType))){
  	 	if (!memory_type::isNumeric(nExpressionType)){ syntaxError(token__COLOR, "wrong type, must be a number type"); _ERROR_ }
  	}
	}
 	if (!bEXPRESSION && !bEXPRESSION2){ syntaxError(token__COLOR, "expression missing"); _ERROR_ }

  if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
 	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__COLOR, ") missing"); _ERROR_ }

	{

 		if (bProducePcode){
			 p->wr_COLOR(pcode__COLOR, bEXPRESSION, bEXPRESSION2);
 		}

 		parseInfo(p, "parsed COLOR");
 		_DONE_
	}

	_END_
}
/**
[KBASIC][VB][QBASIC]
NAME: ECHO
PRINTNAME: Echo
TASK: output information for browser 
SYNTAX: ECHO {(expression | SPC(expression) | TAB(expression) [;|,]) }
DESC:
It is used to generate HTML files on the fly, like PHP do. It is useful when you create dynamic web pages for Apache & Co.


CODE:

ECHO ""_
"<HTML>"_
"<HEAD>"_
"<TITLE>Web pages on the fly</TITLE>"_
"</HEAD>"_
"<BODY>"_
"<TABLE WIDTH=100% BORDER=0>"_
"<TR>"_
"<TD>"_
"Hello World! Dynamically created HTML files..."_
"</TD>"_
"</TR>"_
"</TABLE>"_
"</BODY>"_
"</HTML>"


EXAMPLES: 
CATEGORY: SUB, BUILTIN, BROWSER, VARIABLE
SEEALSO: USING
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
/**
[KBASIC][VB][QBASIC]
NAME: PRINT
PRINTNAME: Print
TASK: output information on screen
SYNTAX: PRINT {[#filehandle ,] | (expression | SPC(expression) | TAB(expression) [;|,]) }
DESC:

, = TAB
; = nothing
EOL = \n


CODE:
PRINT 12.12345
EXAMPLES: 
CATEGORY: SUB, BUILTIN, SCREEN, VARIABLE
SEEALSO: WIDTH, WRITE, USING
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/

/** 
[KBASIC][VB][QBASIC]
NAME: PRINT2
PRINTNAME: Print
TASK: output information on screen
SYNTAX: PRINT {[#filehandle ,] [USING string_expression ;] | (expression | SPC(expression) | TAB(expression) [;|,]) }
DESC:

, = TAB
; = nothing
EOL = \n

NUMBER

# number
. decimal
, print thousand separator
+
^^^^^
-
$$
**
**$

--> sprintf

##. number to large then print in exponent format
###,.##
###+.
###.+#
$$###
**$####

STRING

&complete string
! first character
\ \     print count spaces between \ + 2

&
!
\\

ESCAPE
_


CODE:
PRINT #1, USING "##.###  "; 12.12345
EXAMPLES: 
CATEGORY: SUB, BUILTIN, SCREEN, VARIABLE
SEEALSO: WIDTH, WRITE, USING
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/

/** 
[KBASIC][VB][QBASIC]
NAME: USING
PRINTNAME: Using
TASK: Prints strings or numbers using a specified format
SYNTAX: PRINT USING <i>formatstring; expressionlist</i> [{,|;}
DESC:

---------
Formatted strings:

formatstring may contain \\ or ! or &

you can use "\\" to print a certain number of characters (n-2), so

"\\" will print 2
"\  \" will print 4 characters

A "!" will print only the first character of the string

A "&" will print the whole string

----------
Formatted numbers:
you can choose the width of the printing, the number of decimals and the place of the decimal point. Also the place of $, kommas and + or minus

- every # is a decimal digit (max 18)
- additional spaces right of the decimal point will be filled with 0
- additional spaces left of the decimal point will be filled with spaces
- exception: 1 > n > -1 when a 0 is before the decimal point
- all numbers rounded to number of digits
- negative numbers with a leading -
- this leading - takes one # in the formatstring

 0.468  ##.##    0.47   one leading space
 0.468  #.####  0.4680  no leading space
12.5    ##.##   12.50   no leading space
12.5    ####.#    12.5  two leading spaces

Well, this is a bit confusing:

- a plus at the beginning produces a leading + or - before the number
- a minus at the beginning produces always a - (for positive and negative)
- a plus at the end produces a trailing + or -
- a minus at the end produces a space for positive and a - for negative numbers

Now the $ and stuff:
- a $ at the beginning: $ before the number
- for a negative value, the - is between $ and first digit
- several $ reserve additional spaces, but only one $ is printed
- two * fill the spaces with ***
- you can combine ** and $
- a comma left of decimal point marks thousands (1,000,000 - English style)

Exponentials:
- scientific notation by including 3 - 6 "^" signs
- one for "E", one for +/- and two to four for the exponents

Literals:
literals must be preceeded by a "_":

print using "_##"; 1  'prints #1
print using "#_#"; 1  'prints 1#

- if the number doesn't fit, the formatstring is ignored and the whole number with a leading "%" is printed

- variables may be used as formatstrings

- formatstrings may be emedded into normal text:

a = 12.56
x$= "sum"
PRINT USING "The & is $##.##";x$,a


&nbsp;&nbsp;The <i>formatstring</i> is a string literal (or variable) containing literal
characters to print (such as labels) and special formatting characters. &nbsp;These
&nbsp; formatting characters determine the field and the format of the printed
string or numbers. &nbsp;Spaces, commas, and semicolons in the <i>expressionlist</i>
 have the same meaning as they do in a PRINT statement.<br>
  <br>
The <i>expressionlist</i> contains the string expressions or numeric expressions
to be printed, separated by semicolons.<br>
  <br>
When PRINT USING is used to print strings, you may use one of three formatting
characters to format the string field, as described in the following list:<br>
  <br>
  <table cellpadding="2" cellspacing="2" border="1" width="80%" align="Center">
    <tbody>
      <tr>
        <td valign="Top">Character<br>
        </td>
        <td valign="Top">Description<br>
        </td>
      </tr>
      <tr>
        <td valign="Top">!<br>
        </td>
        <td valign="Top">Only the first character in the given string is
to be printed<br>
        </td>
      </tr>
      <tr>
        <td valign="Top">\ &nbsp; &nbsp;\<br>
        </td>
        <td valign="Top">Prints 2+n characters from a string where n is the
number of spaces between the two backslashes. &nbsp;If the backslashes are typed
with no spaces, two characters are printed, and so on. &nbsp;If the field is longer
than the string, the string is left-justified in the field and padded with
spaces to the right.<br>
        </td>
      </tr>
      <tr>
        <td valign="Top">&amp;<br>
        </td>
        <td valign="Top">Indicates a variable length string field. &nbsp;When
the field is specified with the ampersand (&amp;), the string is output without
modification.<br>
        </td>
      </tr>
    </tbody>
  </table>
&nbsp;<br>
When PRINT USING is used to print numbers, the following special characters
can be used to format the numeric field:<br>
  <br>
  <table cellpadding="2" cellspacing="2" border="1" width="80%" align="Center">
    <tbody>
      <tr>
        <td valign="Top">Character<br>
        </td>
        <td valign="Top">Description<br>
        </td>
      </tr>
      <tr>
        <td valign="Top">#<br>
        </td>
        <td valign="Top">Represents each digit position. &nbsp;Digit positions
are always filled. &nbsp;If the number to be printed has fewer digits than positions
specified, the number is right justified (preceded by spaces) in the field.<br>
        </td>
      </tr>
      <tr>
        <td valign="Top">.<br>
        </td>
        <td valign="Top">Prints a decimal point. &nbsp;A decimal point may be
inserted at any position in the field. If the format string specifies that
a digit is to precede the decimal point, the digit is always printed (as
0, if necessary). &nbsp;If necessary, numbers are rounded.<br>
        </td>
      </tr>
      <tr>
        <td valign="Top">+<br>
        </td>
        <td valign="Top">Causes the sign of the number (plus or minus) to
be printed before the number (if it appears at the beginningat
string) or after (if it appears at the endat string).<br>
        </td>
      </tr>
      <tr>
        <td valign="Top">-<br>
        </td>
        <td valign="Top">Causes a negative number to be printed with a trailing
minus sign if it appears at the endat string.<br>
        </td>
      </tr>
      <tr>
        <td valign="Top">**<br>
        </td>
        <td valign="Top">Causes leading spaces in the numeric field to be
filled with asterisks. &nbsp;The double asterisk also specifies positions for
two more digits.<br>
        </td>
      </tr>
      <tr>
        <td valign="Top">$$<br>
        </td>
        <td valign="Top">Causes a dollar sign to be printed to the immediate
leftatted number. &nbsp;The $$ specifies two more digit positions,
one of which is the dollar sign.<br>
        </td>
      </tr>
      <tr>
        <td valign="Top">**$<br>
        </td>
        <td valign="Top">Combines the effects of the double-asterisk and
double-dollar sign signals. &nbsp;Leading spaces are asterisk filled, and a dollar
sign is printed before the number. &nbsp;The **$ symbols specify three more digit
positions, one of which is the dollar sign. When negative numbers are printed,
the minus sign appears to the immediate left of the dollar sign.<br>
        </td>
      </tr>
      <tr>
        <td valign="Top">,<br>
        </td>
        <td valign="Top">If the comma appears to the left of the decimal
point, in a format string, it causes a comma to be printed to the left of
every third digit left of the decimal point. &nbsp;If it appears at the end of
the format string, it is printed as part of the string. &nbsp;A comma specifies
another digit position. The comma has no effect if used with exponential
(^^^^ or ^^^^^) format.<br>
        </td>
      </tr>
      <tr>
        <td valign="Top">^^^^<br>
        </td>
        <td valign="Top">Specifies exponential format. &nbsp;You can also use
five carets (^^^^^) to allow E+xxx to be printed for larger numbers. &nbsp;Any
decimal point position may be specified. &nbsp;The significant digits are left
justified and the exponent is adjusted. &nbsp;Unless a leading +, trailing +,
or - is specified, one digit position is used to the left of the decimal
point to print a space or a minus sign. <br>
        </td>
      </tr>
      <tr>
        <td valign="Top">_<br>
        </td>
        <td valign="Top">An underscore in the format string prints the next
character as a literal character. &nbsp;A literal underscore is printed as the
result of two underscores in the format string.<br>
        </td>
      </tr>
    </tbody>
  </table>
  <br>
If he number to be printed is larger than the specified numeric field, a
percent sign (%) is printed in front of the number. &nbsp;If rounding causes a
number to exceed the field, a percent sign is printed in front of the rounded
number. If the number of digits specified exceeds 24, an error message results
that reads <tt>Illegal function call.</tt><br>
  <br>
[examples omitted - too tedious to count all those spaces and type in correctly.]
&nbsp;&nbsp; &nbsp;&nbsp; &nbsp;<br>
  <br>


CODE:
PRINT #1, USING "##.###  "; 12.12345
EXAMPLES: 
CATEGORY: SUB, BUILTIN, SCREEN, VARIABLE
SEEALSO: PRINT
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fPRINT(pcode *p)
/*
[QBASIC]
[VB] 
[*]
[*]
*/
{

	//bool bTerm_PRINT = false;

	bool bTerm_ECHO = false;
	bool bTerm_LOG = false;
	_BEGIN_
  if (/*bTerm_PRINT = */parseTerm(token__PRINT));
  else if (/*bTerm_PRINT = */parseTerm(token__SYM_QM));
  else if ((bTerm_ECHO = parseTerm(token__ECHO)));
  else if (!(bTerm_LOG = parseTerm(token__LOG))){ _END_ }

	
  if (bTerm_LOG && peekToken() == token__SYM_DOT) _END_ // might be the call of class Log

	bool bTerm_COMMA = false;
	bool bTerm_SEMICOL = false;

	bool bEXPRESSION0 = false;
	bool bEXPRESSION00 = false;
	bool bEXPRESSION = false;
	int nExpressionType = 0;
  t_arrayVariable a;

	bool bTerm_USING = false;

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

 	bool bTerm_SPC = false;
	bool bTerm_TAB = false;
	bool bTerm__HASH = false;

 	bool bEOL = false;
	bool bREM = false;

	const char *acUSING = "";

  bool bFirst3 = false;

  if (bTerm__HASH = parseTerm(token__SYM_HASH)){
    if ((bEXPRESSION00 = bEXPRESSION0 = fINTEGER_EXPRESSION(p))){
      bFirst3 = true;
    }
  }

	bool bFirst = true;
	bool bFirst2 = true;
	
#ifdef KBDEBUG
   if (stopAtLine(340)){
     int i = 9;
     i++;
   }
#endif

 	while (true){

    if (!bFirst && !bTerm_COMMA && !bTerm_SEMICOL && !bTerm_TAB && !bTerm_SPC){ 

      if (!bEXPRESSION){
        { syntaxError(token__PRINT, "missing expression"); _ERROR_ }
      } else { 
        {syntaxError(token__PRINT, "expression missing or expression type not compatible [or probably , or ; forgotten for PRINT]"); _ERROR_ }
      }
   }

		bEXPRESSION = bTerm_SPC = bTerm_TAB = bTerm_COMMA = bTerm_SEMICOL = false;

    if (bTerm_USING == false && (bTerm_USING = parseTerm(token__USING))){

 			if (!(fSTRING_EXPRESSION(p))){ syntaxError(token__PRINT, "expression missing"); _ERROR_ }

   	  if (!(bTerm_SEMICOL = parseTerm(token__SYM_SEMICOL))){ syntaxError(token__PRINT, "; missing"); _ERROR_ }

  	} else {

			bEXPRESSION = false;
			bTerm_SPC = false;
			bTerm_TAB = false;

			if (bTerm_TAB = parseTerm(token__TAB)){

        {
          if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){}

    			if (!(fINTEGER_EXPRESSION(p))){ syntaxError(token__PRINT, "expression missing"); _ERROR_ }

     		  if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
    		}

//    	 			 if (!bTerm_SYM_BR_OP){ syntaxError(token__PRINT, "( missing"); _ERROR_ }
 //   	 	else if (!bTerm_SYM_BR_CL){ syntaxError(token__PRINT, ") missing"); _ERROR_ }

  		} else if (bTerm_SPC = parseTerm(token__SPC)){

        {
          if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){}

    			if (!(fINTEGER_EXPRESSION(p))){ syntaxError(token__PRINT, "expression missing"); _END_ }

     		  if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
    		}

    	 		//	 if (!bTerm_SYM_BR_OP){ syntaxError(token__PRINT, "( missing"); _ERROR_ }
    	// 	else if (!bTerm_SYM_BR_CL){ syntaxError(token__PRINT, ") missing"); _ERROR_ }

    	} else {

#ifdef KBDEBUG
  if (stopAtLine(118)){
    int i = 9;
    i++;
  }
#endif

   			if (bEXPRESSION = fEXPRESSION(p, &nExpressionType, &a)){
          
          if (!memory_type::scalar(nExpressionType) && nExpressionType != pcode__CONST || 
            (bExplicit && (a.var.def.count > 0 && a.var.use.count == 0) 
            || (a.class_.def.count > 0 && a.class_.use.count == 0) 
            || (a.element.def.count > 0 && a.element.use.count == 0) )){
           semanticError(token__PRINT, "expression to print is not a scalar (e.g. STRING, INTEGER...) or array of var is not used in expression"); _ERROR_ 
         }
       }
  		}

  	  if (bTerm_COMMA = parseTerm(token__SYM_COMMA)){}
   	  else if (bTerm_SEMICOL = parseTerm(token__SYM_SEMICOL)){}

	    if (bFirst && !bEXPRESSION && bTerm_COMMA && !bTerm_SEMICOL){ 
        if (bEXPRESSION0){
          bEXPRESSION0 = false;
          bEXPRESSION = true;
        } else {
//          syntaxError(token__PRINT, "expression missing"); _ERROR_ 
        }
      }

			if (bFirst || bEXPRESSION || bTerm_SPC || bTerm_TAB){

       if ((bEXPRESSION0 && bFirst == false || bEXPRESSION0 == false && bFirst) || bFirst2 == false/* || bFirst3 == false*/){
      	  if (bProducePcode){
      		  p->wr_PRINT(pcode__PRINT, bFirst2/* || bFirst3*/, bEXPRESSION00, bTerm_USING, bEXPRESSION, bTerm_SPC, bTerm_TAB, bTerm_COMMA, bTerm_SEMICOL, bTerm_ECHO, bTerm_LOG);
      	  }

         bFirst2 = false;
       }

				bFirst = false;

			}

      int mm = peekToken();
    /*  if (mm == token__END){
        mm = mm;
      }*/
 		  if (peekfEOL() || peekfREM() || peekTerm(token__SYM_BR_CL) || peekTerm(token__KB_EOF2) || mm == token__ELSE || mm == token__ELSEIF || mm == token__ENDIF || (mm == token__END && peekToken(1) == token__IF) /*|| nextTokenIsKeyword()*/){ // needed to find out when ; or , is missing

      	parseInfo(p, "parsed PRINT");
      	_DONE_

			}
      
		}
	}

	_END_

}

/* *
[KBASIC][VB][QBASIC]
NAME: RANDOMIZE
PRINTNAME: Randomize
TASK: initalizie the random generator
SYNTAX: RANDOMIZE [startvalue%]
DESC: 
CODE:
RANDOMIZE TIMER
x% = INT(RND * 6) + 1
y% = INT(RND * 6) + 1
PRINT "2 throws with one dice: 1st throw ="; x%; "and 2nd throw ="; y%
EXAMPLES: randomize.kbasic
CATEGORY: SUB, BUILTIN, MATH
SEEALSO: RND
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fRANDOMIZE(pcode *p)
/*
[QBASIC]
[VB]
[*]
[*]
*/
{

	//bool bTerm_RANDOMIZE = false;
	_BEGIN_
  if (!(/*bTerm_RANDOMIZE = */parseTerm(token__RANDOMIZE))){ _END_ }

	

	bool bEXPRESSION = false;
	bool bAUTO = false;
  int nReturnExpressionType = 0;


  if (peekTerm(token__SYM_BR_OP)){
    bool bTerm_SYM_BR_OP = false;
    bool bTerm_SYM_BR_CL = false;
    if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){}
    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
    if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__BEEP, ") missing"); _ERROR_ }

    bAUTO = true;
  } else {
    if (!(peekfEOL() || peekfREM() || peekTerm(token__KB_EOF2))){
      if ((bEXPRESSION = fNUMERIC_EXPRESSION(p))){}
      else if ((bEXPRESSION = fTIMER(p, &nReturnExpressionType, true))){}
    } else {
      bAUTO = true;
    }
  }

	{

 		if (bProducePcode){
			p->wr_RANDOMIZE(pcode__RANDOMIZE, bEXPRESSION, bAUTO);
 		}

 		parseInfo(p, "parsed RANDOMIZE");
 		_DONE_
	}
	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: BEEP
PRINTNAME: Beep
TASK: Produces a sound. Depends on the system if it works.
SYNTAX: BEEP
DESC: 
CODE:
BEEP
EXAMPLES: beep.kbasic
CATEGORY: SUB, BUILTIN, SCREEN
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fBEEP(pcode *p)
/*
[QBASIC]
[VB]
[*]
[*]
*/
{

	//bool bTerm_BEEP = false;
	_BEGIN_
  if (!(/*bTerm_BEEP = */parseTerm(token__BEEP))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

  if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
    if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__BEEP, ") missing"); _ERROR_ }
  }

	{
    if (bProducePcode){
			 p->wr_BEEP(pcode__BEEP);
 		}

 		parseInfo(p, "parsed BEEP");
 		_DONE_
	}

	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: RESET
PRINTNAME: Reset
TASK: closes all files
SYNTAX: RESET
DESC: 
CODE:
RESET
EXAMPLES: reset.kbasic
CATEGORY: SUB, BUILTIN, FILE
SEEALSO: CLOSE, OPEN, END, STOP
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fRESET(pcode *p)
/*
[QBASIC]
[VB]
[*]
[*]
*/
{

	//bool bTerm_RESET = false;
	_BEGIN_
  if (!(/*bTerm_RESET = */parseTerm(token__RESET))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

  if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
    if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__RESET, ") missing"); _ERROR_ }
  }

	{
    if (bProducePcode){
			 p->wr_RESET(pcode__RESET);
 		}

 		parseInfo(p, "parsed RESET");
 		_DONE_
	}

	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: SLEEP
PRINTNAME: Sleep
TASK: waits for key pressed
SYNTAX: SLEEP [seconds%]
DESC: 
CODE:
PRINT "Pausing 10 seconds..."
SLEEP 10
PRINT "Continue..."
EXAMPLES: sleep.kbasic
CATEGORY: SUB, BUILTIN
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fSLEEP(pcode *p)
/*
[QBASIC]
[*]
[*]
[*]
*/
{

	//bool bTerm_SLEEP = false;
	_BEGIN_
  if (!(/*bTerm_SLEEP = */parseTerm(token__SLEEP))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){}

	bool bEXPRESSION = false;

  if ((bEXPRESSION = fNUMERIC_EXPRESSION(p))){}

  if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
 	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__SLEEP, ") missing"); _ERROR_ }

	{

 		if (bProducePcode){
			 p->wr_SLEEP(pcode__SLEEP, bEXPRESSION);
 		}

 		parseInfo(p, "parsed SLEEP");
 		_DONE_
	}

	_END_
}

/**
[KBASIC][VB][QBASIC]

NAME: DOEVENTS
PRINTNAME: DoEvents
TASK: enables the application to process events
SYNTAX: DOEVENTS
DESC:
CODE:
EXAMPLES: doevents.kbasic
CATEGORY: SUB, BUILTIN
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fDOEVENTS(pcode *p)
/*
[*]
[VB]
[*]
[*]
*/
{

	//bool bTerm_DOEVENTS = false;
	_BEGIN_
  if (!(/*bTerm_DOEVENTS = */parseTerm(token__DOEVENTS))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){}
  if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
 	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__DOEVENTS, ") missing"); _ERROR_ }

	{

 		if (bProducePcode){
			p->wr_DOEVENTS(pcode__DOEVENTS);
 		}

 		parseInfo(p, "parsed DOEVENTS");
 		_DONE_
	}

	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: NAME
PRINTNAME: Name
TASK: NAME renames a file or a directory
SYNTAX: NAME old AS new
DESC: 
CODE:
NAME old.txt AS new.txt
EXAMPLES: name.kbasic
CATEGORY: SUB, BUILTIN, FILE
SEEALSO: FILES, OPEN
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fNAME(pcode *p)
/*
[QBASIC]
[VB]
[*]
[*]
*/
{

	//bool bTerm_NAME = false;
	_BEGIN_
  if (!(/*bTerm_NAME = */parseTerm(token__NAME))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

  bool bTerm_AS;

	bool bEXPRESSION = false;
	bool bEXPRESSION2 = false;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){}

  if (!(bEXPRESSION = fSTRING_EXPRESSION(p))){ _END_ }// might be used as variable name    syntaxError(token__NAME, "expression missing"); _ERROR_ }

	if (!(bTerm_AS = parseTerm(token__AS))){ syntaxError(token__NAME, "AS missing"); _ERROR_ }

	if (!(bEXPRESSION2 = fSTRING_EXPRESSION(p))){ syntaxError(token__NAME, "expression missing"); _ERROR_ }

  if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL)))){}
 	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__NAME, ") missing"); _ERROR_ }

	{

 		if (bProducePcode){

   		p->wr_NAME(pcode__NAME);
 		}

 		parseInfo(p, "parsed NAME");
 		_DONE_
	}

	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: CHDRIVE
PRINTNAME: ChDrive
TASK: changes to another current drive
SYNTAX: CHDRIVE drive$ 
DESC:
CODE:
CHDRIVE "C"	' change to D:
EXAMPLES: chdrive.kbasic
CATEGORY: SUB, BUILTIN, FILE
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fCHDRIVE(pcode *p)
/*
[*]
[VB]
[*]
[*]
*/
{

	//bool bTerm_CHDRIVE = false;
	_BEGIN_
  if (!(/*bTerm_CHDRIVE = */parseTerm(token__CHDRIVE))){ _END_ }

	

	bool bEXPRESSION = false;

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){}

  if (!(bEXPRESSION = fSTRING_EXPRESSION(p))){ syntaxError(token__CHDRIVE, "expression missing"); _ERROR_ }

  if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL)))){}
 	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__CHDRIVE, ") missing"); _ERROR_ }

	{

 		if (bProducePcode){
    		p->wr_CHDRIVE(pcode__CHDRIVE);
 		}

 		parseInfo(p, "parsed CHDRIVE");
 		_DONE_
	}

	_END_
}

/**
[KBASIC]
NAME: PRINTSCREEN
*/
bool parser::fPRINTSCREEN(pcode *p)
/*
[*]
[VB]
[*]
[*]
*/
{
	_BEGIN_
  if (!(parseTerm(token__PRINTSCREEN))){ _END_ }

	

	bool bEXPRESSION = false;

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){}

  if (!(bEXPRESSION = fBOOLEAN_EXPRESSION(p))){ syntaxError(token__PRINTSCREEN, "expression missing"); _ERROR_ }

  if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL)))){}
 	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__PRINTSCREEN, ") missing"); _ERROR_ }

	{

 		if (bProducePcode){
    		p->wr_PRINTSCREEN(pcode__PRINTSCREEN);
 		}

 		parseInfo(p, "parsed PRINTSCREEN");
 		_DONE_
	}

	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: SETATTR
PRINTNAME: SetAttr
TASK: sets attributes for files
SYNTAX: SETATTR pathname AS STRING, attributes AS INTEGER
DESC:
attributes possible values:
kbNormal	0	(default).
kbReadOnly	1
kbHidden	2
kbSystem	4
kbArchive	32
CODE:
SETATTR "TSTFILE", vbHidden	
SETATTR "TSTFILE", vbHidden + vbReadOnly			
EXAMPLES: setattr.kbasic
CATEGORY: SUB, BUILTIN, FILE
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fSETATTR(pcode *p)
/*
[*]
[VB]
[*]
[*]
*/
{

	//bool bTerm_SETATTR = false;
	_BEGIN_
  if (!(/*bTerm_SETATTR = */parseTerm(token__SETATTR))){ _END_ }

	

	bool bEXPRESSION = false;
	bool bEXPRESSION2 = false;

	bool bTerm_COMMA = false;

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){}

  if (!(bEXPRESSION = fSTRING_EXPRESSION(p))){ syntaxError(token__SETATTR, "string expression missing"); _ERROR_ }

 	if (!(parseTerm(token__SYM_COMMA))){
		{ syntaxError(token__SETATTR, ", missing"); _ERROR_ }
	}

  if (!(bEXPRESSION2 = fINTEGER_EXPRESSION(p))){ syntaxError(token__SETATTR, "integer expression missing"); _ERROR_ }

  if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL)))){}
 	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__SETATTR, ") missing"); _ERROR_ }

	{

 		if (bProducePcode){
   		p->wr_SETATTR(pcode__SETATTR); 
 		}

 		parseInfo(p, "parsed SETATTR");
 		_DONE_
	}

	_END_
}


/**
[KBASIC][VB][QBASIC]
NAME: CHDIR
PRINTNAME: ChDir
TASK: changes the current directory to new one
SYNTAX: CHDIR (dir As String)
DESC: 
CODE:
MKDIR "C:\TEMP\TEST"
CHDIR "C:\TEMP"
FILES
RMDIR "TEST"
EXAMPLES: chdir.kbasic
CATEGORY: FUNCTION, BUILTIN, FILE
SEEALSO: CURDIR, MKDIR, RMDIR, CHDRIVE, FILES
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fCHDIR(pcode *p)
/*
[QBASIC]
[VB]
[*]
[*]
*/
{

	//bool bTerm_CHDIR = false;
	_BEGIN_
  if (!(/*bTerm_CHDIR = */parseTerm(token__CHDIR))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	bool bEXPRESSION = false;

  if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){}

  if (!(bEXPRESSION = fSTRING_EXPRESSION(p))){ syntaxError(token__CHDIR, "expression missing"); _ERROR_ }

  if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
  if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__CHDIR, ") missing"); _ERROR_ }

  {
   
   	  if (bProducePcode){
 		    p->wr_CHDIR(pcode__CHDIR);
   	  }

   	  parseInfo(p, "parsed CHDIR");
   	  _DONE_
  }
  
 	//if (!bTerm_SYM_BR_OP){ syntaxError(token__CHDIR, "( missing"); _ERROR_ }

	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: CLOSE
PRINTNAME: Close
TASK: close opened file
SYNTAX: CLOSE [[#]fileno] [, [#]fileno] 
DESC: 
CLOSE without fileno arguments close all opened files.
CODE:
Dim I, filename
For I = 1 To 3	' repeat loop 3 times
	filename = "TEST" & I	' create filename
	Open filename For Output As #I	' open file
	Print #I, "Ein Test."	' write string into file
Next I
Close	' close all 3 opened files
EXAMPLES: close.kbasic
CATEGORY: FUNCTION, BUILTIN, FILE
SEEALSO: END, OPEN, RESET, STOP
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fCLOSE(pcode *p)
/*
[QBASIC]
[VB]
[*]
[*]
*/
{

	//bool bTerm_CLOSE = false;
	_BEGIN_
  if (!(/*bTerm_CLOSE = */parseTerm(token__CLOSE))){ _END_ }

	

	static /**/ bool bEXPRESSION[parser__MAX_CLOSE];
  bool bEXPRESSION2;

	int nComma = 0;

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

 	bool bTerm__HASH = false;
 	bool bTerm_COMMA = false;

	int nExpressionType[parser__MAX_CLOSE];

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){}


	while (true){

	 	if (nComma >= parser__MAX_CLOSE){ internalError("too many expressions for CLOSE"); _ERROR_ }

    if (bTerm__HASH = parseTerm(token__SYM_HASH)){}
		if (bEXPRESSION[nComma] = fINTEGER_EXPRESSION(p)){}

	  if (bTerm_COMMA = parseTerm(token__SYM_COMMA)){
			nComma++;
		} else {

			if (!bEXPRESSION[nComma] && nComma > 0){ syntaxError(token__CLOSE, "expression missing"); _ERROR_ }

		  if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
		 	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__CLOSE, ") missing"); _ERROR_ }

			{

       if (!bEXPRESSION[nComma] && nComma == 0){
        if (bProducePcode){
   				  p->wr_CLOSEALL(pcode__CLOSEALL);
   			  }
       } else {
        if (bProducePcode){
   				  p->wr_CLOSE(pcode__CLOSE, nComma + 1);
   			  }
       }
   		
   			parseInfo(p, "parsed CLOSE");
   			_DONE_
			}

 		}
	}

	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: ERROR
PRINTNAME: Error
TASK: simulates an error
SYNTAX: ERROR (number)
DESC: 
CODE:
Dim errorno
For errorno = 61 To 64	
	Print Error(errorno)	
Next
EXAMPLES: error.kbasic
CATEGORY: FUNCTION, BUILTIN, ERROR
SEEALSO: ERL, RESUME, ERR, ONERROR
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fERROR(pcode *p)
/*
[QBASIC]
[VB]
[!VBNET]
[!KBASIC]
*/
{

	//bool bTerm_ERROR = false;
	_BEGIN_
  if (!(/*bTerm_ERROR = */parseTerm(token__ERROR)) && !(/*bTerm_ERROR = */parseTerm(token__ERROR_))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	bool bEXPRESSION = false;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP));

  {

		if (bEXPRESSION = fINTEGER_EXPRESSION(p)){}
	
		if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
 		if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__ERROR, ") missing"); _ERROR_ }


 		if (bProducePcode){

   			 p->wr_ERROR(pcode__ERROR, bEXPRESSION);
 		}

 		parseInfo(p, "parsed ERROR");
 		_DONE_
	}

			 //if (!bTerm_SYM_BR_OP){ syntaxError(token__ERROR, "( missing"); _ERROR_ }
 	//if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__ERROR, ") missing"); _ERROR_ }

	_END_
}

/* *
[KBASIC][VB][QBASIC]
NAME: FIELD
PRINTNAME: Field
TASK: defines variables for accessing the buffer of GET/PUT
SYNTAX: 
FIELD [#]fileno%, recordlen% AS stringvariable$ [,recordlen% AS stringvariable$] ...
DESC: 
CODE:
OPEN "ADDRESS.DAT" FOR RANDOM AS #1 LEN = 80
FIELD #1, 30 AS name$, 50 AS address$
GET #1
PRINT name$, address$
EXAMPLES: field.kbasic
CATEGORY: FUNCTION, BUILTIN, FILE
SEEALSO: GET, PUT, TYPE
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
/*
bool parser::fFIELD(pcode *p)
/ *
[QBASIC]
[VB]
[*]
[*]
* /
{

	//bool bTerm_FIELD = false;
	_BEGIN_
  if (!(parseTerm(token__FIELD))){ _END_ }

	

	bool bTerm_COMMA = false;
	bool bTerm__HASH = false;
	bool bTerm__AS = false;

	bool bEXPRESSION[parser__MAX_FIELD];
  bool bEXPRESSION2;

	int nComma = 0;

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

  bool bIDENTIFIER = false;

  int nVar[parser__MAX_FIELD];
	t_scope scope[parser__MAX_FIELD];
	int nType[parser__MAX_FIELD];

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){}

  if (bTerm__HASH = parseTerm(token__SYM_HASH)){}
  if ((bEXPRESSION2 = fINTEGER_EXPRESSION(p))){
    if (!(bTerm_COMMA = parseTerm(token__SYM_COMMA))){ syntaxError(token__FIELD, ", missing"); _ERROR_ }
  }

	while (true){

	 	if (nComma >= parser__MAX_FIELD){ internalError("too many expressions for FIELD"); _ERROR_ }

		if (bEXPRESSION[nComma] = fINTEGER_EXPRESSION(p))
    if (bTerm__AS = parseTerm(token__AS))
    if (bIDENTIFIER = fVARIABLE(p, &nVar[nComma], &scope[nComma], &nType[nComma])){}


		 if (nType[nComma] == token__ME){
       { semanticError(token__FIELD, "FIELD not allowed in combination with ME"); _ERROR_ }
		 } else if (nType[nComma] == token__PARENT){
       { semanticError(token__FIELD, "FIELD not allowed in combination with PARENT"); _ERROR_ }
    } else {
    }


  	if (!bEXPRESSION[nComma]){ syntaxError(token__FIELD, "integer expression missing"); _ERROR_ }
  	if (!bTerm__AS){ syntaxError(token__FIELD, "AS missing"); _ERROR_ }
  	if (!bIDENTIFIER){ syntaxError(token__FIELD, "string variable missing"); _ERROR_ }

	  if (bTerm_COMMA = parseTerm(token__SYM_COMMA)){
			nComma++;
		} else {

		  if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
		 	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__WRITE, ") missing"); _ERROR_ }

			{

   			if (bProducePcode){

   				 p->wr_FIELD(pcode__FIELD, bEXPRESSION2, nComma);
   			}

   			parseInfo(p, "parsed FIELD");
   			_DONE_
			}

 		}
	}

	_END_
}
*/
/**
[KBASIC][VB][QBASIC]
NAME: GET
PRINTNAME: Get
TASK: reads a record from file
SYNTAX: Get [#]fileno, [recordno], variable 
DESC:
CODE:
TYPE TestRecord
    Student AS STRING * 20
    Result AS SINGLE
END TYPE
DIM MyClass AS TestRecord
OPEN "ENDRESULTS.DAT" FOR RANDOM AS #1 LEN = LEN(MyClass)
MyClass.Student = "Bernd Noetscher"
MyClass.Result = 99
PUT #1, 1, MyClass
CLOSE #1
OPEN "ENDRESULTS.DAT" FOR RANDOM AS #1 LEN = LEN(MyClass)
GET #1, 1, MyClass
PRINT "STUDENT:", MyClass.Student
PRINT "SCORE:", MyClass.Result
CLOSE #1
KILL "ENDRESULTS.DAT"
EXAMPLES: get.kbasic
CATEGORY: FUNCTION, BUILTIN, FILE
SEEALSO: TYPE, FIELD
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
/* *
[KBASIC][VB][QBASIC]
NAME: GET2
PRINTNAME: Get
TASK: stores part of the screen into an array
SYNTAX: GET [STEP] (x1!,y1!)-[STEP](x2!,y2!), arrayvar[(index%)]
DESC:
CODE:
SCREEN 13
DIM Box%(1 TO 200)
x1% = 0: x2% = 10: y1% = 0: y2% = 10
LINE (x1%, y1%)-(x2%, y2%), 2, BF
GET (x1%, y1%)-(x2%, y2%), Box%
DO
    PUT (x1%, y1%), Box%, XOR
    x1% = RND * 300
    y1% = RND * 180
    PUT (x1%, y1%), Box%
LOOP WHILE INKEY$ = ""
EXAMPLES: get2.kbasic
CATEGORY: FUNCTION, BUILTIN, SCREEN
SEEALSO: SCREEN
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fGET(pcode *p)
/*
[QBASIC]

[VB]
[*]
[*]
*/
{

	//bool bTerm_GET = false;
	_BEGIN_
  if (!(/*bTerm_GET = */parseTerm(token__GET))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	bool bEXPRESSION = false;
	bool bTerm_COMMA = false;
	bool bTerm__HASH = false;
	bool bIDENTIFIER = false;

  bool bTerm__ = false;
  bool bTerm__STEP1 = false;
  bool bTerm__STEP2 = false;
	
	int nVar = 0; t_scope scope = global; int nType = 0;

  // variante 1
 	if (bTerm__STEP1 = parseTerm(token__STEP)){}

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){
  	if (bEXPRESSION = fINTEGER_EXPRESSION(p))
    if (bTerm_COMMA = parseTerm(token__SYM_COMMA))
  	if (bEXPRESSION = fINTEGER_EXPRESSION(p))
    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL)))
    if (bTerm__ = parseTerm(token__OP_SUB)){

      if (bTerm__STEP2 = parseTerm(token__STEP)){}

	    if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP))
  	  if (bEXPRESSION = fINTEGER_EXPRESSION(p))
      if (bTerm_COMMA = parseTerm(token__SYM_COMMA))
  	  if (bEXPRESSION = fINTEGER_EXPRESSION(p))
	    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL)))
      if (bTerm_COMMA = parseTerm(token__SYM_COMMA))
      if (bIDENTIFIER = fVARIABLE(p, &nVar, &scope, &nType)){


		    if (nType == token__ME){
           { semanticError(token__GET, "GET not allowed in combination with ME"); _ERROR_ }
		    } else if (nType == token__PARENT){
           { semanticError(token__GET, "GET not allowed in combination with PARENT"); _ERROR_ }
        }

        if (bProducePcode){
   			  p->wr_GET2(pcode__GET2, nVar, scope, bTerm__STEP1, bTerm__STEP2);
        }

 		    parseInfo(p, "parsed GET2");
 		    _DONE_
      }
    }   
  }
  
  // variante 2
 if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){}

 if (bTerm__HASH = parseTerm(token__SYM_HASH)){}
 if (!(bEXPRESSION = fINTEGER_EXPRESSION(p))){ syntaxError(token__GET, "integer expression missing"); _ERROR_ }

   bEXPRESSION = false;
   if ((bTerm_COMMA = parseTerm(token__SYM_COMMA))){
     if (bEXPRESSION = fINTEGER_EXPRESSION(p)){}
   }

   if ((bTerm_COMMA = parseTerm(token__SYM_COMMA))){
     if (!(bIDENTIFIER = fVARIABLE(p, &nVar, &scope, &nType))){ syntaxError(token__GET, "variable missing"); _ERROR_ }

		 if (nType == token__ME){
      { semanticError(token__GET, "GET not allowed in combination with ME"); _ERROR_ }
		 } else if (nType == token__PARENT){
      { semanticError(token__GET, "GET not allowed in combination with PARENT"); _ERROR_ }
     }

   } else {
    // syntaxError(token__GET, ", missing"); _ERROR_ 
   }

	if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
 	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__GET, ") missing"); _ERROR_ }

 	if (bProducePcode){
 		p->wr_GET(pcode__GET, nVar, scope, bEXPRESSION, bIDENTIFIER);
 	}

 	parseInfo(p, "parsed GET");
 	_DONE_
}

/**
[KBASIC][VB][QBASIC]
NAME: PUT
PRINTNAME: Put
TASK: writes a record from file
SYNTAX: Put [#]fileno, [recordno], variable 
DESC:
CODE:
TYPE TestRecord
    Student AS STRING * 20
    Result AS SINGLE
END TYPE
DIM MyClass AS TestRecord
OPEN "ENDRESULTS.DAT" FOR RANDOM AS #1 LEN = LEN(MyClass)
MyClass.Student = "Bernd Noetscher"
MyClass.Result = 99
PUT #1, 1, MyClass
CLOSE #1
OPEN "ENDRESULTS.DAT" FOR RANDOM AS #1 LEN = LEN(MyClass)
GET #1, 1, MyClass
PRINT "STUDENT:", MyClass.Student
PRINT "SCORE:", MyClass.Result
CLOSE #1
KILL "ENDRESULTS.DAT"
EXAMPLES: put.kbasic
CATEGORY: FUNCTION, BUILTIN, FILE
SEEALSO: TYPE, FIELD
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
/* *
[KBASIC][VB][QBASIC]
NAME: PUT2
PRINTNAME: Put
TASK: put an array on screen
SYNTAX: PUT [STEP] (x1!,y1!), arrayvar[(index%)] [,bitmode]
DESC:
bitmode possible values:
AND, OR, PSET (normal), PRESET (normal inverted), XOR
CODE:
SCREEN 13
DIM Box%(1 TO 200)
x1% = 0: x2% = 10: y1% = 0: y2% = 10
LINE (x1%, y1%)-(x2%, y2%), 2, BF
GET (x1%, y1%)-(x2%, y2%), Box%
DO
    PUT (x1%, y1%), Box%, XOR
    x1% = RND * 300
    y1% = RND * 180
    PUT (x1%, y1%), Box%
LOOP WHILE INKEY$ = ""
EXAMPLES: put2.kbasic
CATEGORY: FUNCTION, BUILTIN, SCREEN
SEEALSO: SCREEN
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fPUT(pcode *p)
/*
[QBASIC]
[VB]
[*]
[*]
*/
{

	//bool bTerm_PUT = false;
	_BEGIN_
  if (!(/*bTerm_PUT = */parseTerm(token__PUT))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	bool bEXPRESSION = false;
	bool bTerm_COMMA = false;
	bool bTerm__HASH = false;

	bool bIDENTIFIER = false;
	
	int nVar = 0; t_scope scope = global; int nType = 0;

  bool bTerm__ = false;
  bool bTerm__STEP1 = false;
  int nMode = 2;
  

  // variante 1
 	if (bTerm__STEP1 = parseTerm(token__STEP)){}

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){   
    {
  	  if (bEXPRESSION = fINTEGER_EXPRESSION(p))
      if (bTerm_COMMA = parseTerm(token__SYM_COMMA))
  	  if (bEXPRESSION = fINTEGER_EXPRESSION(p))
      if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL)))
      if (bTerm_COMMA = parseTerm(token__SYM_COMMA))
      if (bIDENTIFIER = fVARIABLE(p, &nVar, &scope, &nType)){
     
		     if (nType == token__ME){
             { semanticError(token__PUT, "PUT not allowed in combination with ME"); _ERROR_ }
		     } else if (nType == token__PARENT){
             { semanticError(token__PUT, "PUT not allowed in combination with PARENT"); _ERROR_ }
         } else {
           if (bProducePcode){
		          p->wr_PUSH_ID(pcode__PUSH_ID, nVar, scope, false);
           }
         }

        if (bTerm_COMMA = parseTerm(token__SYM_COMMA)){
          if (bTerm__ = parseTerm(token__OP_AND)){ nMode = 0; }
          else if (bTerm__ = parseTerm(token__OP_OR)){ nMode = 1; }
          else if (bTerm__ = parseTerm(token__PSET)){ nMode = 2; }
          else if (bTerm__ = parseTerm(token__PRESET)){ nMode = 3; }
          else if (bTerm__ = parseTerm(token__OP_XOR)){ nMode = 4; }          
        }


        if (bTerm__ || !bTerm_COMMA){
          if (bProducePcode){
   			    p->wr_PUT2(pcode__PUT2, nVar, scope, bTerm__STEP1, nMode);
          }

 		      parseInfo(p, "parsed PUT2");
 		      _DONE_
        }
      }
    }    
  }

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){}

	if (bTerm__HASH = parseTerm(token__SYM_HASH)){}
	if (!(bEXPRESSION = fINTEGER_EXPRESSION(p))){ syntaxError(token__PUT, "integer expression missing"); _ERROR_ }

	if ((bTerm_COMMA = parseTerm(token__SYM_COMMA))){
	  if (bEXPRESSION = fINTEGER_EXPRESSION(p)){}
	}

	if ((bTerm_COMMA = parseTerm(token__SYM_COMMA))){
	if (!(bIDENTIFIER = fVARIABLE(p, &nVar, &scope, &nType))){ 
    if (!fEXPRESSION(p)){    // naybe it is only an expression of data 
        syntaxError(token__PUT, "variable missing"); _ERROR_ 
    }
    nVar = 0;
  }

	if (nType == token__ME){
		{ semanticError(token__PUT, "PUT not allowed in combination with ME"); _ERROR_ }
	} else if (nType == token__PARENT){
		{ semanticError(token__PUT, "PUT not allowed in combination with PARENT"); _ERROR_ }
	} else {
    if (bProducePcode){
		    if (nVar) p->wr_PUSH_ID(pcode__PUSH_ID, nVar, scope, false);
    }
	}

	} else {
	  syntaxError(token__PUT, ", missing"); _ERROR_ 
	}

	if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
 	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__PUT, ") missing"); _ERROR_ }


 	if (bProducePcode){
    p->wr_PUT(pcode__PUT, nVar, scope, bEXPRESSION);
 	}

 	parseInfo(p, "parsed PUT");
 	_DONE_

}

bool parser::fPOKE(pcode *p, bool bObjectFake)
{

	_BEGIN_
  if (!(parseTerm(token__POKE))){ _END_ }	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	bool bTerm_COMMA = false;
  
	
	int nVar = 0; t_scope scope = global; int nType = 0;
 

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

  	if (!bObjectFake && !(fSTRING_EXPRESSION(p))){ syntaxError(token__POKE, "string expression missing"); _ERROR_ }

    if (!bObjectFake && !(bTerm_COMMA = parseTerm(token__SYM_COMMA))){ syntaxError(token__POKE, ", missing"); _ERROR_ }
  	
      if (fVARIABLE(p, &nVar, &scope, &nType)){
     
		     if (nType == token__ME){
             { semanticError(token__POKE, "POKE not allowed in combination with ME"); _ERROR_ }
		     } else if (nType == token__PARENT){
             { semanticError(token__POKE, "POKE not allowed in combination with PARENT"); _ERROR_ }
         } else {
           if (bProducePcode){
		          p->wr_PUSH_ID(pcode__PUSH_ID, nVar, scope, false);
           }
         }
         if (bTerm_COMMA = parseTerm(token__SYM_COMMA))
         if (!fINTEGER_EXPRESSION(p)){ syntaxError(token__PUT, "missing INTEGER expression"); _ERROR_ }

        if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
        if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__POKE, ") missing"); _ERROR_ }

          if (bProducePcode){
   			    p->wr_POKE(pcode__POKE);
          }

 		      parseInfo(p, "parsed POKE");
 		      _DONE_        

      }
    
    
  }

  _END_
}


bool parser::fPEEK(pcode *p, bool bObjectFake)
{

	_BEGIN_
  if (!(parseTerm(token__PEEK))){ _END_ }	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	bool bTerm_COMMA = false;
  
	
 	int nVar2 = 0; t_scope scope2 = global; int nType2 = 0;
 

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

    if (!bObjectFake){
      if (!fVARIABLE(p, &nPeekVar, &PeekScope, &nPeekType)){ syntaxError(token__PEEK, "string variable missing"); _ERROR_ }

	     if (nPeekType == token__ME){
           { semanticError(token__PEEK, "PEEK not allowed in combination with ME"); _ERROR_ }
	     } else if (nPeekType == token__PARENT){
           { semanticError(token__PEEK, "PEEK not allowed in combination with PARENT"); _ERROR_ }
	     } else if (!memory_type::isString(nPeekType)){
           { semanticError(token__PEEK, "PEEK not allowed in combination with non-String variable"); _ERROR_ }
     
       }
    }

    if (!bObjectFake && !(bTerm_COMMA = parseTerm(token__SYM_COMMA))){ syntaxError(token__PEEK, ", missing"); _ERROR_ }
  	
      if (fVARIABLE(p, &nVar2, &scope2, &nType2)){
     
		     if (nType2 == token__ME){
             { semanticError(token__PEEK, "PEEK not allowed in combination with ME"); _ERROR_ }
		     } else if (nType2 == token__PARENT){
             { semanticError(token__PEEK, "PEEK not allowed in combination with PARENT"); _ERROR_ }
         } else {
           
           if (bProducePcode){
		          p->wr_PUSH_ID(pcode__PUSH_ID, nVar2, scope2, false);
           }
         }
         if (bTerm_COMMA = parseTerm(token__SYM_COMMA))
         if (!fINTEGER_EXPRESSION(p)){ syntaxError(token__PUT, "missing INTEGER expression"); _ERROR_ }

        if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
        if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__PEEK, ") missing"); _ERROR_ }

          if (bProducePcode){
   			    p->wr_PEEK(pcode__PEEK, nPeekVar, PeekScope/*, bObjectFake*/);
          }

 		      parseInfo(p, "parsed PEEK");
 		      _DONE_        

      }
   
    
  }

  _END_
}

/**
[QBASIC][VB]
NAME: KILL
PRINTNAME: Kill
TASK: Deletes a file specified by a filename.
SYNTAX: KILL filename

DESC:
filename is a string expression stating which file to be deleted.
Like for DOS-based Basics, KILL deletes only files.

CODE:
' This deletes the file "test.xml":
KILL "test.xml"

and using a string variable, this would look like:
filename$ = "test.xml"
KILL filename$
EXAMPLES: kill.kbasic
CATEGORY: SUB, BUILTIN, FILE
SEEALSO: OPEN, FILES
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fKILL(pcode *p)
/*
[QBASIC]
[VB]
[*]
[*]
*/
{

	//bool bTerm_KILL = false;
	_BEGIN_
  if (!(/*bTerm_KILL = */parseTerm(token__KILL))){ _END_ }

	

	bool bEXPRESSION = false;

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

  if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){}

	if (!(bEXPRESSION = fSTRING_EXPRESSION(p))){ syntaxError(token__KILL, "expression missing"); _ERROR_ }

  if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
  if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__KILL, ") missing"); _ERROR_ } 

	{
 		if (bProducePcode){
			 p->wr_KILL(pcode__KILL);
 		}

 		parseInfo(p, "parsed KILL");

 		_DONE_
	}

	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: LINEINPUT
PRINTNAME: Line Input
TASK: reads line of text from file into variable
SYNTAX: LINE INPUT [#]fileno%, variable$
DESC: 
CODE:
CLS
OPEN "LIST" FOR OUTPUT AS #1
DO
    INPUT "   NAME:       ", Name$  'input from keyboard
    INPUT "   Age:      ", Age$
    WRITE #1, Name$, Age$
    INPUT "Type a new entry"; R$
LOOP WHILE UCASE$(R$) = "Y"
CLOSE #1
'print content of file
OPEN "LIST" FOR INPUT AS #1
CLS
PRINT "entries of file:": PRINT
DO WHILE NOT EOF(1)
    LINE INPUT #1, REC$  
    PRINT REC$           
LOOP
CLOSE #1
EXAMPLES: lineinput.kbasic
CATEGORY: FUNCTION, BUILTIN, FILE
SEEALSO: PRINT, OPEN, WRITE, INPUT, INKEY
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
/**
[KBASIC][VB][QBASIC]
NAME: LINE
PRINTNAME: Line
TASK: draws a line on the screen
SYNTAX: LINE (x1!,y1!)]-(x2!,y2!) [,[color%] ]
DESC: 
CODE:
SCREEN 13
LINE (0, 0)-(320, 200), 3
EXAMPLES: line.kbasic
CATEGORY: FUNCTION, BUILTIN, SCREEN
SEEALSO: CIRCLE, INPUT, LINEINPUT, PRESET, PSET, SCREEN
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
/* *
[KBASIC][VB][QBASIC]
NAME: LINE
PRINTNAME: Line
TASK: draws a line on the screen
SYNTAX: LINE [[STEP](x1!,y1!)]-[STEP](x2!,y2!) [,[color%] [,[B | BF] [,style%]]]
DESC: 
CODE:
SCREEN 13
LINE (110, 70)-(190, 120), , B
LINE (0, 0)-(320, 200), 3, , &HFF00
EXAMPLES: line.kbasic
CATEGORY: FUNCTION, BUILTIN, SCREEN
SEEALSO: CIRCLE, INPUT, LINEINPUT, PRESET, PSET, SCREEN
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fLINEINPUT(pcode *p)
/*
[QBASIC]
[VB]
[*]
[*]
*/
{

	//bool bTerm_LINE = false;
	_BEGIN_
  if (!(/*bTerm_LINE = */parseTerm(token__LINE))){ _END_ }

	

	bool bTerm_INPUT = false;

  if ((bTerm_INPUT = parseTerm(token__INPUT))){

    _BEGIN2_
	  bool bTerm_COMMA = false;

      bool bImplicitDIM = false;
      bool bTestImplicitDim = true;
      bool bSizeAll = false;
      int nLStringLen = 0;
      bool bReference = false;  
      bool bAssignment = false;  
      bool bProperty = false;  
      bool bTestProperty = false;  

	  int nVar = 0; t_scope scope = global; int nIdType = 0; int nType = 0; t_arrayVariable a;

	  bool bIDENTIFIER = false;

	  bool bEXPRESSION = false;

 	  bool bTerm_SYM_BR_OP;
 	  bool bTerm_SYM_BR_CL;
   	
    bool bTerm__HASH = false;
    

	  if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){}

    if (bTerm__HASH = parseTerm(token__SYM_HASH)){}
	  if (!(bEXPRESSION = fINTEGER_EXPRESSION(p))){ 
      if (bTerm__HASH){
        { syntaxError(token__EOF_, "integer expression missing"); _ERROR_ }
      } else {
        _END2_
        return fINPUT(p, 0, false);
      }
    }

	  if (!(bTerm_COMMA = parseTerm(token__SYM_COMMA))){ syntaxError(token__LINE, ", missing"); _ERROR_ }

	if ((bIDENTIFIER = fVARIABLE_ASSIGNMENT(p, &nVar, &scope, &nIdType, &nType, &bImplicitDIM, 
                                  bTestImplicitDim, &a, 
                                  &bSizeAll, &nLStringLen, &bReference, &bProperty, bTestProperty                 
                                  ))){  	

      if (!memory_type::isString(nType)){ semanticError(token__INPUT, "INPUT variable must be of type BOOLEAN, STRING, INTEGER, LONG, SINGLE or DOUBLE"); _ERROR_ }

      if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
   	  if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__LINE, ") missing"); _ERROR_ }

		  {

   		  if (bProducePcode){

  				  p->wr_LINEINPUT(pcode__LINEINPUT, nVar, scope);
   		  }

   		  parseInfo(p, "parsed LINE INPUT");
   		  _DONE_
  	  }

 	  } else { syntaxError(token__LINE, "identifier missing or identifier not declared"); _ERROR_ }


	  _END_
  } else {

	  bool bTerm_STEP = false;
	  bool bTerm_STEP2 = false;
	  bool bTerm_COMMA = false;
	  bool bEXPRESSION = false;
	  bool bEXPRESSION2 = false;

	  bool color = false;
	  bool b = false;
	  bool bf = false;
	  bool style = false;  

    bool bTerm_ = false;      

	  bool bTerm_SYM_BR_OP;
	  bool bTerm_SYM_BR_CL;

    if (bTerm_STEP = parseTerm(token__STEP)){}

	  if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

      if (!(bEXPRESSION = fINTEGER_EXPRESSION(p))){ syntaxError(token__LINE, "integer expression missing"); _ERROR_ }

      if (!(bTerm_COMMA = parseTerm(token__SYM_COMMA))){ syntaxError(token__LINE, ", missing"); _ERROR_ }

      if (!(bEXPRESSION = fINTEGER_EXPRESSION(p))){ syntaxError(token__LINE, "integer expression missing"); _ERROR_ }

	    if (!(bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL)))){ syntaxError(token__LINE, ") missing"); _ERROR_ }

    } else if (bTerm_STEP){
      { syntaxError(token__LINE, "x1, y1 missing"); _ERROR_ }
    }


    if (!(bTerm_ = parseTerm(token__OP_SUB))){ syntaxError(token__LINE, "- missing"); _ERROR_ }


    if (bTerm_STEP2 = parseTerm(token__STEP)){}

	  if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

      if (!(bEXPRESSION2 = fINTEGER_EXPRESSION(p))){ syntaxError(token__LINE, "integer expression missing"); _ERROR_ }

      if (!(bTerm_COMMA = parseTerm(token__SYM_COMMA))){ syntaxError(token__LINE, ", missing"); _ERROR_ }

      if (!(bEXPRESSION2 = fINTEGER_EXPRESSION(p))){ syntaxError(token__LINE, "integer expression missing"); _ERROR_ }

	    if (!(bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL)))){ syntaxError(token__LINE, ") missing"); _ERROR_ }

    }


    if (bTerm_COMMA = parseTerm(token__SYM_COMMA)){
      if (color = fINTEGER_EXPRESSION(p)){}
    }

    if (bTerm_COMMA = parseTerm(token__SYM_COMMA)){
      const char *s = "";

      if (fID_KEYWORD_OR_BUILTIN(&s)){
        if (utility::my_stricmp("B", s)){
          b = true;
        } else if (utility::my_stricmp("BF", s)){
          bf = true;
        } else {
          { syntaxError(token__LINE, "B or BF missing"); _ERROR_ }
        }
      }
    }

    if (bTerm_COMMA = parseTerm(token__SYM_COMMA)){
      if (style = fINTEGER_EXPRESSION(p)){}
    }

    if (bTerm_STEP || bTerm_STEP2) { semanticError(token__LINE, "STEP is not supported yet"); _ERROR_ }
    if (style) { semanticError(token__LINE, "STYLE is not supported yet"); _ERROR_ }

    if (bProducePcode){
  	  p->wr_LINE(pcode__LINE, bTerm_STEP, bEXPRESSION2, bTerm_STEP2, color, b, bf, style);
    }

    parseInfo(p, "parsed LINE");
    _DONE_
  }
}

/**
[KBASIC][VB][QBASIC]
NAME: MKDIR
PRINTNAME: MkDir
TASK: create a new directory
SYNTAX: MKDIR (dir As String)
DESC: 
CODE:
MKDIR "C:\TEMP\TEST"
CHDIR "C:\TEMP"
FILES
RMDIR "TEST"
EXAMPLES: mkdir.kbasic
CATEGORY: FUNCTION, BUILTIN, FILE
SEEALSO: CURDIR, MKDIR, RMDIR, CHDRIVE
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fMKDIR(pcode *p)
/*
[QBASIC]
[VB]
[*]
[*]
*/
{

	//bool bTerm_MKDIR = false;
	_BEGIN_
  if (!(/*bTerm_MKDIR = */parseTerm(token__MKDIR))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	bool bEXPRESSION = false;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){}

  if (!(bEXPRESSION = fSTRING_EXPRESSION(p))){ syntaxError(token__MKDIR, "expression missing"); _ERROR_ }

  if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
  if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__MKDIR, ") missing"); _ERROR_ }

  {

   	  if (bProducePcode){

     				  p->wr_MKDIR(pcode__MKDIR);
   	  }

   	  parseInfo(p, "parsed MKDIR");
   	  _DONE_
  }
  
	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: OPEN2
PRINTNAME: Open
TASK: needed to open files (alternate syntax)
SYNTAX: OPEN mode$,[#]fileno%,file$[,recordlen%]
DESC: 
 mode$        "O" or "o" for output, "I" or "i" for input, "A" or "a" for append
 fileno%       An integer between 1 and 255, which names a file, which is opened.
 file$         The name of the file. It can contain path information.
 recordlen%    For direct access files: It is the length of the record (default is 128 byte).
               For sequentiel files: The amount of buffer characters (default is 512 Byte).
CODE:
INPUT "What input file to use  (e.g. C:\file.inp)? ", file$
OPEN "I", #1, file$                 ' Open the input file
INPUT "What output file to use  (e.g. C:\file.out)? ", file$
OPEN "O", #2, file$                 ' Open the output file

EXAMPLES: open2.kbasic
CATEGORY: FUNCTION, BUILTIN, FILE
SEEALSO: OPEN
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
/**
[KBASIC][VB][QBASIC]
NAME: OPEN
PRINTNAME: Open
TASK: needed to open files
SYNTAX: OPEN file$ FOR mode [ACCESS access] [lock] AS [#]fileno% [LEN=recordlen%]
DESC: 
 file$         The name of the file. It can contain path information.
 mode          One of the following modi: APPEND, BINARY, INPUT,
                OUTPUT or RANDOM.
 access         Gibt in einer Netzwerk-Umgebung an, ob das Zugriffsrech
                auf eine Datei READ, WRITE oder READ WRITE ist.
                 
                READ          Opens a file only for reading from file
                WRITE         Opens a file only for writing to file
                READ WRITE    Opens a file for writing and reading. READ WRITE
               is only possible for direct access and sequentiel files,
               and for files, which are opened for APPEND (sequentiel access)
 lock(not supported) Access permission inside network filesystem: 
               SHARED, LOCK READ, LOCK WRITE oder LOCK READ WRITE.
 fileno%       An integer between 1 and 255, which names a file, which is opened.
 recordlen%    For direct access files: It is the length of the record (default is 128 byte).
               For sequentiel files: The amount of buffer characters (default is 512 Byte).
CODE:
INPUT "Input filename: "; n$
OPEN n$ FOR OUTPUT AS #1
PRINT #1, "This is stored in a file."
CLOSE
OPEN n$ FOR INPUT AS #1
INPUT #1, a$
PRINT "Readed from file: "; a$
CLOSE

EXAMPLES: open.kbasic
CATEGORY: FUNCTION, BUILTIN, FILE
SEEALSO: OPEN2, CLOSE, FREEFILE, TYPE
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fOPEN(pcode *p)
/*
[QBASIC]

[VB]
[*]
[*]
*/
{

	//bool bTerm_OPEN = false;
	_BEGIN_
  if (!(/*bTerm_OPEN = */parseTerm(token__OPEN))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;
	bool bTerm_FOR = false;
	bool bTerm__ = false;
	bool bTerm2__ = false;
	bool bTerm_AS = false;
	bool bTerm__HASH = false;
	bool bFILEHANDLE = false;
	int nFILEHANDLE = -1;
	bool bTerm_LEN = false;

	bool bEXPRESSION = false;
	bool bEXPRESSION2 = false;
	bool bEXPRESSION3 = false;

	bool bTerm_COMMA = false;

	int nMode = 0;
	int nLock = 0;  
	int nAccess = 0;   


	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){}

	if (!(bEXPRESSION = fSTRING_EXPRESSION(p))){ syntaxError(token__OPEN, "string expression missing"); _ERROR_ }

	// 1. variante OPEN mode$,[#]fileno%,file$[,recordlen%]
  if (bTerm_COMMA = parseTerm(token__SYM_COMMA)){

  	if (bTerm__HASH = parseTerm(token__SYM_HASH)){}
  	if (!(bEXPRESSION = fINTEGER_EXPRESSION(p))){ syntaxError(token__OPEN, "integer expression missing"); _ERROR_ }

	  if (!(bTerm_COMMA = parseTerm(token__SYM_COMMA))){ syntaxError(token__OPEN, ", missing"); _ERROR_ }
		if (!(bEXPRESSION2 = fSTRING_EXPRESSION(p))){ syntaxError(token__OPEN, "string expression missing"); _ERROR_ }

    if (bEXPRESSION3 = fINTEGER_EXPRESSION(p)){}

    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
 	  if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__OPEN, ") missing"); _ERROR_ }

	  {

 		  if (bProducePcode){
  			  p->wr_OPEN2(pcode__OPEN2, bEXPRESSION3);
 		  }

 		  parseInfo(p, "parsed OPEN2");
 		  _DONE_
	  }


 	// 2. variante OPEN file$ FOR mode [ACCESS access] [lock] AS [#]fileno% [LEN=recordlen%]
	} else {

    if (!(bTerm_FOR = parseTerm(token__FOR))){ syntaxError(token__OPEN, "FOR missing"); _ERROR_ }

		if (bTerm__ = parseTerm(token__OUTPUT)){ nMode = pcode__OUTPUT; }
  	else if (bTerm__ = parseTerm(token__INPUT)){ nMode = pcode__INPUT; }
  	else if (bTerm__ = parseTerm(token__APPEND)){ nMode = pcode__APPEND; }
  	else if (bTerm__ = parseTerm(token__BINARY)){ nMode = pcode__BINARY; }
  	else if (bTerm__ = parseTerm(token__RANDOM)){ nMode = pcode__RANDOM; }
   	if (!bTerm__){ syntaxError(token__OPEN, "OUTPUT, INPUT, APPEND, BINARY or RANDOM missing"); _ERROR_ }

    // access wird nicht unterstützt, aber die syntax wird akzeptiert
  	if (bTerm__ = parseTerm(token__ACCESS)){ 
      if (bTerm__ = parseTerm(token__READ)){
        nAccess = token__READ; 
        if (bTerm__ = parseTerm(token__WRITE)){ nAccess = token__READ + token__WRITE; } // READWRITE eigentlich
      } else if (bTerm__ = parseTerm(token__WRITE)){ 
        nAccess = token__WRITE; 
      }
    }

    // lock wird nicht unterstützt, aber die syntax wird akzeptiert
  	if (bTerm__ = parseTerm(token__SHARED)){ nLock = token__SHARED; }
  	else if (bTerm__ = parseTerm(token__LOCK)){ 
      if (bTerm__ = parseTerm(token__READ)){
        nLock = token__READ; 
        if (bTerm__ = parseTerm(token__WRITE)){ nLock = token__WRITE; } // READWRITE eigentlich
      } else if (bTerm__ = parseTerm(token__WRITE)){ 
        nLock = token__WRITE; 
        if (bTerm__ = parseTerm(token__READ)){ nLock = token__READ; } // READWRITE eigentlich
      }
    }

    if (!(bTerm_AS = parseTerm(token__AS))){ syntaxError(token__OPEN, "AS missing"); _ERROR_ }

  	if (bTerm__HASH = parseTerm(token__SYM_HASH)){}
  	if (!(bEXPRESSION = fINTEGER_EXPRESSION(p))){ syntaxError(token__OPEN, "integer expression missing"); _ERROR_ }

		if (bTerm_LEN = parseTerm(token__LEN)){

	    if (!(bTerm2__ = parseTerm(token__OP_EQUAL))){ syntaxError(token__OPEN, "= missing"); _ERROR_ }

			if (!(bEXPRESSION3 = fINTEGER_EXPRESSION(p))){ syntaxError(token__OPEN, "expression missing"); _ERROR_ }

		}

    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
 	  if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__OPEN, ") missing"); _ERROR_ }

	  {

 		  if (bProducePcode){
   			  p->wr_OPEN(pcode__OPEN, nMode, nLock, nAccess, bTerm_LEN);
 		  }

 		  parseInfo(p, "parsed OPEN");
 		  _DONE_
	  }

	}
	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: RMDIR
PRINTNAME: RmDir
TASK: deletes a complete directory
SYNTAX: RMDIR (dir As String)
DESC:
CODE:
MKDIR "C:\TEMP\TEST"
CHDIR "C:\TEMP"
FILES
RMDIR "TEST"
EXAMPLES: rmdir.kbasic
CATEGORY: FUNCTION, BUILTIN, FILE
SEEALSO: CURDIR, MKDIR, RMDIR, CHDRIVE
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fRMDIR(pcode *p)
/*
[QBASIC]
[VB]
[*]
[*]
*/
{

	//bool bTerm_RMDIR = false;
	_BEGIN_
  if (!(/*bTerm_RMDIR = */parseTerm(token__RMDIR))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	bool bEXPRESSION = false;

  if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){}

  if (!(bEXPRESSION = fSTRING_EXPRESSION(p))){ syntaxError(token__RMDIR, "expression missing"); _ERROR_ }

  if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
  if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__RMDIR, ") missing"); _ERROR_ }

  {

   	  if (bProducePcode){

     				  p->wr_RMDIR(pcode__RMDIR);
   	  }

   	  parseInfo(p, "parsed RMDIR");
   	  _DONE_
  }  	

	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: WRITE
PRINTNAME: Write
TASK: Writes data to screen or file
SYNTAX: WRITE [[#]fileno%,] list of expression
DESC: 
 fileno%      The number of an opened sequentiel file. If no fileno is given, the output is done to the screen.
 list of expression     Expressions, comma separated, which should be written to file or screen

 While writing between the elements commas and quotations are inserted.

CODE:
 CLS
 OPEN "LIST" FOR OUTPUT AS #1
 DO
     INPUT "   NAME:       ", Name$
     INPUT "   AGE:      ", Age$
     WRITE #1, Name$, Age$
     INPUT "More entries?"; R$
 LOOP WHILE UCASE$(R$) = "Y"
 CLOSE #1
 'print file on screen
 OPEN "LIST" FOR INPUT AS #1
 CLS
 PRINT "Entries of file:": PRINT
DO WHILE NOT EOF(1)
    INPUT #1, Rec1$, Rec2$   
    PRINT Rec1$, Rec2$       
LOOP
CLOSE #1
KILL "LIST"
 
EXAMPLES: write.kbasic
CATEGORY: FUNCTION, BUILTIN, FILE
SEEALSO: INPUT, LINEINPUT, OPEN, PRINT
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fWRITE(pcode *p)
/*
[QBASIC]
[VB]
[*]
[*]
*/
{

	//bool bTerm_WRITE = false;
	_BEGIN_
  if (!(/*bTerm_WRITE = */parseTerm(token__WRITE))){ _END_ }

	

	bool bTerm_COMMA = false;
	bool bTerm__HASH = false;

	bool bEXPRESSION[parser__MAX_WRITE];
  bool bEXPRESSION2 = false;

	int nComma = 0;

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	int nExpressionType[parser__MAX_WRITE];
  t_arrayVariable a;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){}

  if (bTerm__HASH = parseTerm(token__SYM_HASH)){}
  if ((bEXPRESSION2 = fINTEGER_EXPRESSION(p))){}

	while (true){

	 	if (nComma >= parser__MAX_WRITE){ internalError("too many expressions for WRITE"); _ERROR_ }

		if (bEXPRESSION[nComma] = fEXPRESSION(p, &nExpressionType[nComma], &a)){

      if (!memory_type::scalar(nExpressionType[nComma]) || 
             ((a.var.def.count > 0 && a.var.use.count == 0) 
             || (a.class_.def.count > 0 && a.class_.use.count == 0) 
             || (a.element.def.count > 0 && a.element.use.count == 0) )){
             semanticError(token__WRITE, "expression to write is not a scalar (e.g. STRING, INTEGER...) or array of var is not used in expression"); _ERROR_ 
      }       

         switch(nExpressionType[nComma]){
           case pcode__QSTRING:
           case pcode__CSTRING:
           case pcode__LQSTRING:
           case pcode__LCSTRING:
             if (bProducePcode) p->wr_PUSH_BOOLEAN(pcode__PUSH_BOOLEAN, true); // write pcode
             break;
           default:
             if (bProducePcode) p->wr_PUSH_BOOLEAN(pcode__PUSH_BOOLEAN, false); // write pcode
             break;
         }
       
    }

	  if (bTerm_COMMA = parseTerm(token__SYM_COMMA)){
			nComma++;
		} else {

			if (!bEXPRESSION[nComma]){ syntaxError(token__WRITE, "expression missing"); _ERROR_ }

		  if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
		 	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__WRITE, ") missing"); _ERROR_ }

			{

       if (bProducePcode){
   			  p->wr_WRITE(pcode__WRITE, bEXPRESSION2, nComma);
   		  }       

   			parseInfo(p, "parsed WRITE");
   			_DONE_
			}

 		}
	}

	_END_
}

/* *
[KBASIC][VB][QBASIC]
NAME: CIRCLE
PRINTNAME: Circle
TASK: draws a circle on screen
SYNTAX: CIRCLE [STEP] (x!,y!),radius![,[color%] [,[start!] [,[end!] [,aspect!]]]]
DESC: 
CODE:
SCREEN 13
LINE (110, 70)-(190, 120), , B
LINE (0, 0)-(32, 200), 3, , &HFF00
EXAMPLES: circle.kbasic
CATEGORY: FUNCTION, BUILTIN, SCREEN
SEEALSO: COLOR, DRAW, LINE, SCREEN, VIEW, WINDOW
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
/*
bool parser::fCIRCLE(pcode *p)
/ *
[QBASIC]
[VB]
[*]
[*]
* /
{

	_BEGIN_
  if (!(parseTerm(token__CIRCLE))){ _END_ }

	

	bool bTerm_STEP = false;
	bool bTerm_COMMA = false;
	bool bEXPRESSION = false;

	bool color = false;
	bool start = false;
	bool end = false;
	bool aspect = false;

	bool bTerm_SYM_BR_OP;
	bool bTerm_SYM_BR_CL;

  if (bTerm_STEP = parseTerm(token__STEP)){}

	if (!(bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP))){ syntaxError(token__CIRCLE, "( missing"); _ERROR_ }

  if (!(bEXPRESSION = fINTEGER_EXPRESSION(p))){ syntaxError(token__CIRCLE, "integer expression missing"); _ERROR_ }

  if (!(bTerm_COMMA = parseTerm(token__SYM_COMMA))){ syntaxError(token__CIRCLE, ", missing"); _ERROR_ }

  if (!(bEXPRESSION = fINTEGER_EXPRESSION(p))){ syntaxError(token__CIRCLE, "integer expression missing"); _ERROR_ }

	if (!(bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL)))){ syntaxError(token__CIRCLE, ") missing"); _ERROR_ }

  if (!(bTerm_COMMA = parseTerm(token__SYM_COMMA))){ syntaxError(token__CIRCLE, ", missing"); _ERROR_ }

  if (!(bEXPRESSION = fINTEGER_EXPRESSION(p))){ syntaxError(token__CIRCLE, "integer expression missing"); _ERROR_ }

  if (bTerm_COMMA = parseTerm(token__SYM_COMMA)){
    if (color = fINTEGER_EXPRESSION(p)){}
  }

  if (bTerm_COMMA = parseTerm(token__SYM_COMMA)){
    if (start = fINTEGER_EXPRESSION(p)){}
  }

  if (bTerm_COMMA = parseTerm(token__SYM_COMMA)){
    if (end = fINTEGER_EXPRESSION(p)){}
  }

  if (bTerm_COMMA = parseTerm(token__SYM_COMMA)){
    if (aspect = fINTEGER_EXPRESSION(p)){}
  }

  if (bProducePcode){
  	p->wr_CIRCLE(pcode__CIRCLE, color, start, end, aspect);
  }

  parseInfo(p, "parsed CIRCLE");
  _DONE_

}*/

/* *
[KBASIC][VB][QBASIC]
NAME: DRAW
PRINTNAME: Draw
TASK: draws commands
SYNTAX: DRAW stringexpression$
DESC: 
CODE:
SCREEN 13
triangle$ = "F60 L120 E60"
DRAW "BD30 P1,2 C3 M-30,-30"
EXAMPLES: draw.kbasic
CATEGORY: FUNCTION, BUILTIN, FILE
SEEALSO: SCREEN, PSET
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
/*
bool parser::fDRAW(pcode *p)
/ *
[QBASIC]
[VB]
[*]
[*]
* /
{

	//bool bTerm_DRAW = false;
	_BEGIN_
  if (!(parseTerm(token__DRAW))){ _END_ }

	

  bool bEXPRESSION = false;

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){}

  if (!(bEXPRESSION = fSTRING_EXPRESSION(p))){ syntaxError(token__DRAW, "string expression missing"); _ERROR_ }

  if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
 	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__DRAW, ") missing"); _ERROR_ }


  if (bProducePcode){

   		p->wr_DRAW(pcode__DRAW);
  }

  parseInfo(p, "parsed DRAW");

  _DONE_
}
*/
/* *
[KBASIC][VB][QBASIC]
NAME: PCOPY
PRINTNAME: PCopy
TASK: copy one screen to another
SYNTAX: PCOPY sourcepage%,destinationpage%
DESC: 
CODE:
PCOPY 1,3
EXAMPLES: pcopy.kbasic
CATEGORY: FUNCTION, BUILTIN, SCREEN
SEEALSO: SCREEN
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
/*
bool parser::fPCOPY(pcode *p)
/ *
[QBASIC]
[VB]
[*]
[*]
* /
{

	//bool bTerm_PCOPY = false;
	_BEGIN_
  if (!(parseTerm(token__PCOPY))){ _END_ }

	

  bool bEXPRESSION = false;
  bool bTerm_COMMA = false;

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){}

  if (!(bEXPRESSION = fINTEGER_EXPRESSION(p))){ syntaxError(token__PCOPY, "integer expression missing"); _ERROR_ }

  if (!(bTerm_COMMA = parseTerm(token__SYM_COMMA))){ syntaxError(token__PCOPY, ", missing"); _ERROR_ }

  if (!(bEXPRESSION = fINTEGER_EXPRESSION(p))){ syntaxError(token__PCOPY, "integer expression missing"); _ERROR_ }

  if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
 	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__PCOPY, ") missing"); _ERROR_ }

  if (bProducePcode){
  	p->wr_PCOPY(pcode__PCOPY);
  }

  parseInfo(p, "parsed PCOPY");

  _DONE_
}*/

/* *
[KBASIC][VB][QBASIC]
NAME: PMAP
PRINTNAME: PMap
TASK: translates coordinates (logical <-> physical)
SYNTAX: PMAP (startcoordinate%, n%)
DESC: 

CODE:
SCREEN 13
WINDOW SCREEN (0, 0)-(100, 100)
PRINT "logical x=50, physical x="; PMAP(50, 0)
PRINT "logical y=50, physical y="; PMAP(50, 1)
EXAMPLES: pmap.kbasic
CATEGORY: FUNCTION, BUILTIN, SCREEN
SEEALSO: POINT, VIEW, WINDOW
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
/*
bool parser::fPMAP(pcode *p)
/ *
[QBASIC]
[VB]
[*]
[*]
* /
{

	//bool bTerm_PMAP = false;
	_BEGIN_
  if (!(parseTerm(token__PMAP))){ _END_ }

	

  bool bEXPRESSION = false;
  bool bTerm_COMMA = false;

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){}

  if (!(bEXPRESSION = fINTEGER_EXPRESSION(p))){ syntaxError(token__PMAP, "integer expression missing"); _ERROR_ }

  if (!(bTerm_COMMA = parseTerm(token__SYM_COMMA))){ syntaxError(token__PMAP, ", missing"); _ERROR_ }

  if (!(bEXPRESSION = fINTEGER_EXPRESSION(p))){ syntaxError(token__PMAP, "integer expression missing"); _ERROR_ }

  if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
 	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__PMAP, ") missing"); _ERROR_ }

  if (bProducePcode){
  	p->wr_PMAP(pcode__PMAP);
  }

  parseInfo(p, "parsed PMAP");

  _DONE_
}*/

/* *
[KBASIC][VB][QBASIC]
NAME: WIDTH
PRINTNAME: Width
TASK: defines max column and max row for screen
SYNTAX: WIDTH maxcolumn%, maxrow%
DESC: 
CODE:
WIDTH 80,25
EXAMPLES: width.kbasic
CATEGORY: FUNCTION, BUILTIN, SCREEN
SEEALSO: SCREEN, PRINT
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
/*
bool parser::fWIDTH(pcode *p)
/ *
[QBASIC]
[VB]
[*]
[*]
* /
{

	//bool bTerm_WIDTH = false;
	_BEGIN_
  if (!(parseTerm(token__WIDTH))){ _END_ }

	

  bool bEXPRESSION = false;
  bool bTerm_COMMA = false;

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){}

  if (!(bEXPRESSION = fINTEGER_EXPRESSION(p))){ syntaxError(token__WIDTH, "integer expression missing"); _ERROR_ }

  if (!(bTerm_COMMA = parseTerm(token__SYM_COMMA))){ syntaxError(token__WIDTH, ", missing"); _ERROR_ }

  if (!(bEXPRESSION = fINTEGER_EXPRESSION(p))){ syntaxError(token__WIDTH, "integer expression missing"); _ERROR_ }

  if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
 	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__WIDTH, ") missing"); _ERROR_ }

  if (bProducePcode){
  	p->wr_WIDTH(pcode__WIDTH);
  }

  parseInfo(p, "parsed WIDTH");

  _DONE_
}
*/
/* *
[KBASIC][VB][QBASIC]
NAME: PRESET
PRINTNAME: PReset
TASK: draws a point on screen
SYNTAX: PRESET [STEP] (x!,y!) [,Farbe%]

DESC: 
CODE:
SCREEN 13
FOR i% = 0 TO 32
    PSET (i%, 100)
    FOR waiting% = 1 TO 100: NEXT
    PRESET (i%, 100)
NEXT i%
EXAMPLES: preset.kbasic
CATEGORY: FUNCTION, BUILTIN, SCREEN
SEEALSO: SCREEN, VIEW, WINDOW
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
/*
bool parser::fPRESET(pcode *p)
/ *
[QBASIC]
[VB]
[*]
[*]
* /
{

	//bool bTerm_PRESET = false;
	_BEGIN_
  if (!(parseTerm(token__PRESET))){ _END_ }

	

  bool bTerm_STEP = false;

  if (bTerm_STEP = parseTerm(token__STEP)){}


  bool bEXPRESSION = false;
  bool bTerm_COMMA = false;

  bool color = false;

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	if (!(bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP))){ syntaxError(token__PRESET, "( missing"); _ERROR_ }

  if (!(bEXPRESSION = fINTEGER_EXPRESSION(p))){ syntaxError(token__PRESET, "integer expression missing"); _ERROR_ }

  if (!(bTerm_COMMA = parseTerm(token__SYM_COMMA))){ syntaxError(token__PRESET, ", missing"); _ERROR_ }

  if (!(bEXPRESSION = fINTEGER_EXPRESSION(p))){ syntaxError(token__PRESET, "integer expression missing"); _ERROR_ }

	if (!(bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL)))){ syntaxError(token__PRESET, ") missing"); _ERROR_ }
 	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__PRESET, ") missing"); _ERROR_ }

  if (bTerm_COMMA = parseTerm(token__SYM_COMMA)){
    if (!(color = fINTEGER_EXPRESSION(p))){ syntaxError(token__PRESET, "color% missing"); _ERROR_ }
  }

  if (bProducePcode){
  	p->wr_PRESET(pcode__PRESET, bTerm_STEP, color);
  }

  parseInfo(p, "parsed PRESET");

  _DONE_
}
*/
/* *
[KBASIC][VB][QBASIC]
NAME: PSET
PRINTNAME: PSet
TASK: draws a point on screen
SYNTAX: PSET [STEP] (x!,y!) [,Farbe%]
DESC: 
CODE:
SCREEN 13
FOR i% = 0 TO 32
    PSET (i%, 100)
    FOR waiting% = 1 TO 100: NEXT
    PRESET (i%, 100)
NEXT i%
EXAMPLES: pset.kbasic
CATEGORY: FUNCTION, BUILTIN, SCREEN
SEEALSO: SCREEN, VIEW, WINDOW
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
/*
bool parser::fPSET(pcode *p)
/ *
[QBASIC]
[VB]
[*]
[*]
* /
{

	//bool bTerm_PSET = false;
	_BEGIN_
  if (!(parseTerm(token__PSET))){ _END_ }

	

  bool bTerm_STEP = false;

  if (bTerm_STEP = parseTerm(token__STEP)){}

  bool bEXPRESSION = false;
  bool bTerm_COMMA = false;

  bool color = false;

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	if (!(bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP))){ syntaxError(token__PSET, "( missing"); _ERROR_ }

  if (!(bEXPRESSION = fINTEGER_EXPRESSION(p))){ syntaxError(token__PSET, "integer expression missing"); _ERROR_ }

  if (!(bTerm_COMMA = parseTerm(token__SYM_COMMA))){ syntaxError(token__PSET, ", missing"); _ERROR_ }

  if (!(bEXPRESSION = fINTEGER_EXPRESSION(p))){ syntaxError(token__PSET, "integer expression missing"); _ERROR_ }

	if (!(bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL)))){ syntaxError(token__PSET, ") missing"); _ERROR_ }
 	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__PSET, ") missing"); _ERROR_ }

  if (bTerm_COMMA = parseTerm(token__SYM_COMMA)){
    if (!(color = fINTEGER_EXPRESSION(p))){ syntaxError(token__PSET, "color% missing"); _ERROR_ }
  }

  if (bTerm_STEP) { semanticError(token__PSET, "STEP is not supported yet"); _ERROR_ }

  if (bProducePcode){
  	p->wr_PSET(pcode__PSET, bTerm_STEP, color);
  }

  parseInfo(p, "parsed PSET");

  _DONE_
}*/

/* *
[KBASIC][VB][QBASIC]
NAME: PAINT
PRINTNAME: Paint
TASK: fills part of the screen
SYNTAX: PAINT [STEP](x!,y!)[,[{color%|pattern$}] [,[bordercolor%] [,background$]]]
DESC: 
CODE:
SCREEN 13
CIRCLE (106, 100), 75, 1
LINE (138, 35)-(288, 165), 1, B
PAINT (160, 100), 2, 1
EXAMPLES: paint.kbasic
CATEGORY: FUNCTION, BUILTIN, SCREEN
SEEALSO: ASC, CHR, CIRCLE, DRAW, LINE, SCREEN
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
/*
bool parser::fPAINT(pcode *p)
/ *
[QBASIC]
[VB]
[*]
[*]
* /
{

	//bool bTerm_PAINT = false;
	_BEGIN_
  if (!(parseTerm(token__PAINT))){ _END_ }

  if (peekToken() == token__SYM_DOT){ _END_ } // it might be class Paint for drawing

	

	bool bTerm_STEP = false;
	bool bTerm_COMMA = false;
	bool bEXPRESSION = false;

	bool color = false;

	bool pattern = false;
	bool bordercolor = false;
	bool background = false;  

	bool bTerm_SYM_BR_OP;
	bool bTerm_SYM_BR_CL;

  if (bTerm_STEP = parseTerm(token__STEP)){}

	if (!(bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP))){ syntaxError(token__PAINT, "( missing"); _ERROR_ }

  if (!(bEXPRESSION = fINTEGER_EXPRESSION(p))){ syntaxError(token__PAINT, "integer expression missing"); _ERROR_ }

  if (!(bTerm_COMMA = parseTerm(token__SYM_COMMA))){ syntaxError(token__PAINT, ", missing"); _ERROR_ }

  if (!(bEXPRESSION = fINTEGER_EXPRESSION(p))){ syntaxError(token__PAINT, "integer expression missing"); _ERROR_ }

	if (!(bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL)))){ syntaxError(token__PAINT, ") missing"); _ERROR_ }

  if (bTerm_COMMA = parseTerm(token__SYM_COMMA)){
    if (color = fINTEGER_EXPRESSION(p)){}
    else if (!(pattern = fSTRING_EXPRESSION(p))){ syntaxError(token__PAINT, "string expression missing"); _ERROR_ }
  }

  if (bTerm_COMMA = parseTerm(token__SYM_COMMA)){
    if (!(bordercolor = fINTEGER_EXPRESSION(p))){ syntaxError(token__PAINT, "integer expression missing"); _ERROR_ }
  }

  if (bTerm_COMMA = parseTerm(token__SYM_COMMA)){
    if (!(background = fSTRING_EXPRESSION(p))){ syntaxError(token__PAINT, "string expression missing"); _ERROR_ }
  }

  if (bProducePcode){
  	p->wr_PAINT(pcode__PAINT, color, pattern, bordercolor, background);
  }

  parseInfo(p, "parsed PAINT");
  _DONE_

}
*/

/* *
[KBASIC][VB][QBASIC]
NAME: WINDOW
PRINTNAME: Window
TASK: defines logical window
SYNTAX: WINDOW [[SCREEN] (x1!,y1!)-(x2!,y2!)]
DESC: 
CODE:
SCREEN 13
FOR i% = 1 TO 10 STEP 2
    WINDOW (-160 / i%, -100 / i%)-(160 / i%, 100 / i%)
    CIRCLE (0, 0), 10
NEXT
EXAMPLES: window.kbasic
CATEGORY: FUNCTION, BUILTIN, SCREEN
SEEALSO: CLS, PMAP, POINT, SCREEN, VIEW, WIDTH
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
/*
bool parser::fWINDOW(pcode *p)
/ *
[QBASIC]
[VB]
[*]
[*]
* /
{

	//bool bTerm_WINDOW = false;
	_BEGIN_
  if (!(parseTerm(token__WINDOW))){ _END_ }

	

	bool bTerm_SCREEN = false;

  if (bTerm_SCREEN = parseTerm(token__SCREEN)){}

	bool bTerm_COMMA = false;
	bool bEXPRESSION = false;
	bool bTerm_ = false;  

	bool bTerm_SYM_BR_OP;
	bool bTerm_SYM_BR_CL;
    

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){ 

    if (!(bEXPRESSION = fINTEGER_EXPRESSION(p))){ syntaxError(token__WINDOW, "integer expression missing"); _ERROR_ }

    if (!(bTerm_COMMA = parseTerm(token__SYM_COMMA))){ syntaxError(token__WINDOW, ", missing"); _ERROR_ }


    if (!(bEXPRESSION = fINTEGER_EXPRESSION(p))){ syntaxError(token__WINDOW, "integer expression missing"); _ERROR_ }

	  if (!(bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL)))){ syntaxError(token__WINDOW, ") missing"); _ERROR_ }


    if (!(bTerm_ = parseTerm(token__OP_SUB))){ syntaxError(token__WINDOW, ", missing"); _ERROR_ }


	  if (!(bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP))){ syntaxError(token__WINDOW, "( missing"); _ERROR_ }

    if (!(bEXPRESSION = fINTEGER_EXPRESSION(p))){ syntaxError(token__WINDOW, "integer expression missing"); _ERROR_ }

    if (!(bTerm_COMMA = parseTerm(token__SYM_COMMA))){ syntaxError(token__WINDOW, ", missing"); _ERROR_ }

    if (!(bEXPRESSION = fINTEGER_EXPRESSION(p))){ syntaxError(token__WINDOW, "integer expression missing"); _ERROR_ }

	  if (!(bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL)))){ syntaxError(token__WINDOW, ") missing"); _ERROR_ }
    
  }

  if (bProducePcode){
  	p->wr_WINDOW(pcode__WINDOW, bTerm_SCREEN, bEXPRESSION);
  }

  parseInfo(p, "parsed WINDOW");
  _DONE_

}*/

/* *
[KBASIC][VB][QBASIC]
NAME: VIEWPRINT
PRINTNAME: View Print
TASK: defines the border of the text window
SYNTAX: VIEW PRINT [rowtop% TO rowbottom%]
DESC: 
CODE:
VIEW PRINT 10 TO 15
FOR i% = 1 TO 100
    PRINT i%
NEXT i%
EXAMPLES: viewprint.kbasic
CATEGORY: FUNCTION, BUILTIN, FILE
SEEALSO:
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
/* *
[KBASIC][VB][QBASIC]
NAME: VIEW
PRINTNAME: View
TASK: defines the graphical view
SYNTAX: VIEW [[SCREEN] (x1!,y1!)-(x2!,y2!) [,[color%] [,border%]]]
DESC: 
CODE:
SCREEN 13
VIEW (10, 10)-(300, 180), , 1
LOCATE 1, 11: PRINT "A big graphic area";
VIEW SCREEN (80, 80)-(200, 125), , 1
LOCATE 11, 11: PRINT "A small graphic area";
EXAMPLES: view.kbasic
CATEGORY: FUNCTION, BUILTIN, SCREEN
SEEALSO: CLS, SCREEN, VIEWPRINT, WINDOW
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
/*
bool parser::fVIEW(pcode *p)
/ *
[QBASIC]
[VB]
[*]
[*]
* /
{

	//bool bTerm_VIEW = false;
	_BEGIN_
  if (!(parseTerm(token__VIEW))){ _END_ }

	

	bool bTerm_PRINT = false;

  if ((bTerm_PRINT = parseTerm(token__PRINT))){

	  bool bTerm_ = false;

	  bool bEXPRESSION = false;

 	  bool bTerm_SYM_BR_OP;
 	  bool bTerm_SYM_BR_CL;
   	   

	  if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){}

	  if (bEXPRESSION = fINTEGER_EXPRESSION(p)){

	    if (!(bTerm_ = parseTerm(token__TO))){ syntaxError(token__VIEW, "TO missing"); _ERROR_ }

	    if (!(bEXPRESSION = fINTEGER_EXPRESSION(p))){ syntaxError(token__VIEW, "integer expression missing"); _ERROR_ }
    }
  	
    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
   	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__VIEW, ") missing"); _ERROR_ }

		{

   		if (bProducePcode){

  				p->wr_VIEWPRINT(pcode__VIEWPRINT);
   		}

   		parseInfo(p, "parsed VIEW PRINT");
   		_DONE_
  	}

 	  

	  _END_
  } else {

    bool bTerm_SCREEN = false;
	  bool bTerm_COMMA = false;
	  bool bEXPRESSION = false;
	  bool bTerm_ = false;    

	  bool color = false;
	  bool border = false;   

	  bool bTerm_SYM_BR_OP;
	  bool bTerm_SYM_BR_CL;

    if (bTerm_SCREEN = parseTerm(token__SCREEN)){}

	  if (!(bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP))){

      if (!(bEXPRESSION = fINTEGER_EXPRESSION(p))){ syntaxError(token__VIEW, "integer expression missing"); _ERROR_ }

      if (!(bTerm_COMMA = parseTerm(token__SYM_COMMA))){ syntaxError(token__VIEW, ", missing"); _ERROR_ }

      if (!(bEXPRESSION = fINTEGER_EXPRESSION(p))){ syntaxError(token__VIEW, "integer expression missing"); _ERROR_ }

	    if (!(bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL)))){ syntaxError(token__VIEW, ") missing"); _ERROR_ }

    } else if (bTerm_SCREEN){
      { syntaxError(token__PAINT, "x1, y1 missing"); _ERROR_ }
    }


    if (!(bTerm_ = parseTerm(token__OP_SUB))){ syntaxError(token__VIEW, ", missing"); _ERROR_ }


	  if (!(bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP))){

      if (!(bEXPRESSION = fINTEGER_EXPRESSION(p))){ syntaxError(token__VIEW, "integer expression missing"); _ERROR_ }

      if (!(bTerm_COMMA = parseTerm(token__SYM_COMMA))){ syntaxError(token__VIEW, ", missing"); _ERROR_ }

      if (!(bEXPRESSION = fINTEGER_EXPRESSION(p))){ syntaxError(token__VIEW, "integer expression missing"); _ERROR_ }

	    if (!(bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL)))){ syntaxError(token__VIEW, ") missing"); _ERROR_ }

    }

    if (bTerm_COMMA = parseTerm(token__SYM_COMMA)){
      if (color = fINTEGER_EXPRESSION(p)){}
    }

    if (bTerm_COMMA = parseTerm(token__SYM_COMMA)){
      if (border = fINTEGER_EXPRESSION(p)){}
    }

    if (bProducePcode){
  	  p->wr_VIEW(pcode__VIEW, bTerm_SCREEN, color, border);
    }

    parseInfo(p, "parsed VIEW");
    _DONE_
  }
}

*/



bool parser::fPREPEND(pcode *p, bool bObjectFake)
{
	_BEGIN_

  if (!(parseTerm(token__PREPEND))){ _END_ }

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

    if (!bObjectFake && !(fSTRING_EXPRESSION(p))){ syntaxError(token__PREPEND, "string expression missing"); _ERROR_ }
  	
    if (!bObjectFake && !(parseTerm(token__SYM_COMMA))){ syntaxError(token__PREPEND, ", missing"); _ERROR_ }

    if (!fSTRING_EXPRESSION(p)){ syntaxError(token__PREPEND, "expression missing"); _ERROR_ }  	     

    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
    if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__PREPEND, ") missing"); _ERROR_ }
 

   	  if (bProducePcode){
         p->wr_PREPEND(pcode__PREPEND);
   	  }

   	  parseInfo(p, "parsed PREPEND");
   	  _DONE_
  }
  
	_END_
}

bool parser::fAPPEND(pcode *p, bool bObjectFake)
{
	_BEGIN_

  if (!(parseTerm(token__APPEND))){ _END_ }

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

    if (!bObjectFake && !(fSTRING_EXPRESSION(p))){ syntaxError(token__APPEND, "string expression missing"); _ERROR_ }
  	
    if (!bObjectFake && !(parseTerm(token__SYM_COMMA))){ syntaxError(token__APPEND, ", missing"); _ERROR_ }

    if (!fSTRING_EXPRESSION(p)){ syntaxError(token__APPEND, "expression missing"); _ERROR_ }  	     

    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
    if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__APPEND, ") missing"); _ERROR_ }
 

   	  if (bProducePcode){
         p->wr_APPEND2(pcode__APPEND2);
   	  }

   	  parseInfo(p, "parsed APPEND");
   	  _DONE_
  }
  
	_END_
}

bool parser::fREMOVE(pcode *p, bool bObjectFake)
{
	_BEGIN_

  if (!(parseTerm(token__REMOVE))){ _END_ }

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

    if (!bObjectFake && !(fSTRING_EXPRESSION(p))){ syntaxError(token__REMOVE, "string expression missing"); _ERROR_ }
  	
    if (!bObjectFake && !(parseTerm(token__SYM_COMMA))){ syntaxError(token__REMOVE, ", missing"); _ERROR_ }

    if (!fINTEGER_EXPRESSION(p)){ syntaxError(token__REMOVE, "expression missing"); _ERROR_ }  	     

  	if (!parseTerm(token__SYM_COMMA)){ syntaxError(token__REMOVE, ", missing"); _ERROR_ }

    if (!fINTEGER_EXPRESSION(p)){ syntaxError(token__REMOVE, "expression missing"); _ERROR_ }  	     

    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
    if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__REMOVE, ") missing"); _ERROR_ }
 

   	  if (bProducePcode){
         p->wr_REMOVE(pcode__REMOVE);
   	  }

   	  parseInfo(p, "parsed REMOVE");
   	  _DONE_
  }
  
	_END_
}

bool parser::fTRUNCATE(pcode *p, bool bObjectFake)
{
	_BEGIN_

  if (!(parseTerm(token__TRUNCATE))){ _END_ }

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

    if (!bObjectFake && !(fSTRING_EXPRESSION(p))){ syntaxError(token__TRUNCATE, "string expression missing"); _ERROR_ }
  	
    if (!bObjectFake && !(parseTerm(token__SYM_COMMA))){ syntaxError(token__TRUNCATE, ", missing"); _ERROR_ }

    if (!fINTEGER_EXPRESSION(p)){ syntaxError(token__TRUNCATE, "expression missing"); _ERROR_ }  	     

    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
    if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__TRUNCATE, ") missing"); _ERROR_ }
 

   	  if (bProducePcode){
         p->wr_TRUNCATE(pcode__TRUNCATE);
   	  }

   	  parseInfo(p, "parsed TRUNCATE");
   	  _DONE_
  }
  
	_END_
}

bool parser::fINSERT(pcode *p, bool bObjectFake)
{
	_BEGIN_

  if (!(parseTerm(token__INSERT))){ _END_ }

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

    if (!bObjectFake && !(fSTRING_EXPRESSION(p))){ syntaxError(token__INSERT, "string expression missing"); _ERROR_ }
  	
    if (!bObjectFake && !(parseTerm(token__SYM_COMMA))){ syntaxError(token__INSERT, ", missing"); _ERROR_ }

    if (!fSTRING_EXPRESSION(p)){ syntaxError(token__INSERT, "expression missing"); _ERROR_ }  	     

  	if (!parseTerm(token__SYM_COMMA)){ syntaxError(token__INSERT, ", missing"); _ERROR_ }

    if (!fINTEGER_EXPRESSION(p)){ syntaxError(token__INSERT, "expression missing"); _ERROR_ }  	     

    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
    if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__INSERT, ") missing"); _ERROR_ }
 

   	  if (bProducePcode){
         p->wr_INSERT(pcode__INSERT);
   	  }

   	  parseInfo(p, "parsed INSERT");
   	  _DONE_
  }
  
	_END_
}

bool parser::fFILL(pcode *p, bool bObjectFake)
{
	_BEGIN_

  if (!(parseTerm(token__FILL))){ _END_ }

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

 	bool bEXPRESSION = false;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

    if (!bObjectFake && !(fSTRING_EXPRESSION(p))){ syntaxError(token__FILL, "string expression missing"); _ERROR_ }
  	
    if (!bObjectFake && !(parseTerm(token__SYM_COMMA))){ syntaxError(token__FILL, ", missing"); _ERROR_ }

    if (!fSTRING_EXPRESSION(p)){ syntaxError(token__FILL, "expression missing"); _ERROR_ }  	     

  	if (parseTerm(token__SYM_COMMA)){

      if (!(bEXPRESSION = fINTEGER_EXPRESSION(p))){ syntaxError(token__FILL, "expression missing"); _ERROR_ }  	     
    }

    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
    if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__FILL, ") missing"); _ERROR_ }
 

   	  if (bProducePcode){
         p->wr_FILL(pcode__FILL, bEXPRESSION);
   	  }

   	  parseInfo(p, "parsed FILL");
   	  _DONE_
  }
  
	_END_
}

bool parser::fWRITEBINARY(pcode *p, bool bObjectFake)
{
	_BEGIN_

  if (!(parseTerm(token__WRITEBINARY))){ _END_ }

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;
 	bool bEXPRESSION = false;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

    if (!bObjectFake){
      if (!fVARIABLE(p, &nPeekVar, &PeekScope, &nPeekType)){ syntaxError(token__PEEK, "string variable missing"); _ERROR_ }

	     if (nPeekType == token__ME){
           { semanticError(token__WRITEBINARY, "WRITEBINARY not allowed in combination with ME"); _ERROR_ }
	     } else if (nPeekType == token__PARENT){
           { semanticError(token__WRITEBINARY, "WRITEBINARY not allowed in combination with PARENT"); _ERROR_ }
	     } else if (nPeekType != pcode__QString){
           { semanticError(token__WRITEBINARY, "wrong datatype"); _ERROR_ }
       } else {
         if (bProducePcode){
            p->wr_PUSH_ID(pcode__PUSH_ID, nPeekVar, PeekScope, false);
         }
       }
    }

    if (!bObjectFake && !(parseTerm(token__SYM_COMMA))){ syntaxError(token__WRITEBINARY, ", missing"); _ERROR_ }

	  int nExpressionType = 0;

 	  if (!fEXPRESSION(p, &nExpressionType)){ syntaxError(token__WRITEBINARY, "expression missing"); _ERROR_ }  	     

    switch(nExpressionType){
      case pcode__QSTRING:
        //if (bEXPRESSION = fBOOLEAN_EXPRESSION(p)){}
        break;
      case pcode__BOOLEAN:
      //case pcode__CSTRING:
      case pcode__BYTE:
      case pcode__SHORT:
      case pcode__INTEGER:
      case pcode__LONG:
      case pcode__SINGLE:
      case pcode__DOUBLE:
      case pcode__CURRENCY:
      case pcode__DATE:
        break;
      default:
        { syntaxError(token__WRITEBINARY, "wrong datatype"); _ERROR_ }
        break;
    }

    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
    if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__WRITEBINARY, ") missing"); _ERROR_ }
 
    bool bThrows = false;
    if (parseTerm(token__THROWS)){ 
      const char *acException = "";
      if (!fID_KEYWORD_OR_BUILTIN(&acException)){ syntaxError(pcode__CAST, "exception name missing (Exception)"); _ERROR_ }
      if (utility::my_stricmp(acException, "Exception") == 0){
        bThrows = true;
      } else {
        { semanticError(pcode__CAST, "exception name not allowed (require Exception)"); _ERROR_ }
      }

    }

    if (bThrows){
      memory_sub *s2 = 0;
      int nId2 = 0;
      int nSubId2 = 0;

      switch(isScopeClass()){
				  case false:
             nId2 = myModule->getId(getScope());
   				    s2 = myModule->getSubs(nId2);
             nSubId2 = s2->getId(nId2, getSub());
					    break;
				    case true:
             nId2 = myClass->getId(getScope());
   				    s2 = myClass->getMethods(nId2);
             nSubId2 = s2->getId(nId2, getMethod());
					    break;
		  }

      registerCatch(nId2, s2, nSubId2, p, pcode__EXCEPTION);
    }

 	  if (bProducePcode){
       p->wr_WRITEBINARY(pcode__WRITEBINARY, nPeekVar, PeekScope, bEXPRESSION);
 	  }

 	  parseInfo(p, "parsed WRITEBINARY");
 	  _DONE_

  }
  
	_END_
}
