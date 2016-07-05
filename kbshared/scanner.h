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


#ifndef SCANNER_H
#define SCANNER_H


 	

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <math.h>



#include "XIntMap.h"
#include "utility.h"
#include "token.h"


class cache;



extern XIntMap map_keyword;
extern XIntMap map_builtin;
extern XIntMap map_operator;
extern XIntMap map_type;
extern XIntMap map_symbol;

class scanner {
public:
  scanner(token *t, cache *my_cache = 0);
  scanner();
  ~scanner();


bool scan(char *text, char *filename = 0, bool bSilent = false, bool bDebug = false, bool bAddEOFToken = true, bool bUseCache = true);
bool scanAdditional(char *text, char *filename = 0, bool bSilent = false, bool bDebug = false, bool bUseCache = true);


void addEOFToken()
{  
  myToken->wr_Token(0, 0, 0, token__KB_EOF); // set stop character at the end
}

// ****************************
// * bool isKeyword()
// *
// * description:
// * scans for a keyword using the keyword table
// * if a keyword has been found, it generates the associated token
// * if both parameters are 0, it will test for standard acInput
// *
// * parameter:
// * none
// *
// * return:
// * true, if a keyword has been found
// * false, no keyword has been found
// ****************************
bool isKeyword()
{
	return isKeyword(0, 0);
}

// ****************************
// * bool isKeyword()
// *
// * description:
// * scans for a keyword using the keyword table
// * if a keyword has been found, it generates the associated token
// *
// * parameter:
// * char *b = String (or keyword) to test
// * int nLen = len of String (or keyword)
// *
// * return:
// * true, if a keyword has been found
// * false, no keyword has been found
// ****************************
bool isKeyword(char *b, int nLenB)
{
  if (!proceedScan()) return false;


  static bool bStandard;
  bStandard = (b == 0);



	if (bStandard){
	} else {
 		acTest = b;
		nLenTest = nLenB;
	}

  static int nLen;
  for (nLen = 0; nLen < nLenTest; nLen++){

    if (isSeparator(acTest[nLen])) break;

  }

  if (nLen > 0){

		static char *s;
    s = mk_s(acTest, nLen, true);    

		static int nID;
 
    nID = (int) map_keyword.getString(s); // if element not in map, a new entry will be created with nID = 0

    if (nID > 0){
      goto t;
    }

    nID = (int) map_builtin.getString(s);
    if (nID > 0){
t:

			if (bStandard){

        static char *z;
        if (nOldFormatStyle == 0){
          z = mk_s(acTest, nLen);
          checkFormatStyle(z, nID);
        }

        static int nOldInput;
        nOldInput = nInput;

        static int nOldXPos;
        nOldXPos = nXPos;

				nInput += nLen; nXPos += nLen;
				if (nID == token___END) bGoOn = false;

        if (nID == token__DECIMAL) nID = token__TYP_CURRENCY;
        else if (nID == token__DATETIME) nID = token__TYP_DATE;

				myToken->wr_Token(nOldInput, nOldXPos, nOldXPos + (nInput - nOldInput), nID);
      }
			return true;
		}
	}

	return false;
}

// ****************************
// * bool isBuiltin()
// *
// * description:
// * scans for a builtin using the builtin table
// * if a builtin has been found, it generates the associated token
// *
// * parameter:
// * char *b = String (or builtin) to test
// * int nLen = len of String (or builtin)
// *
// * return:
// * true, if a builtin has been found
// * false, no builtin has been found
// ****************************
bool isBuiltin()
{
  if (!proceedScan()) return false;

  static int nLen;
  for (nLen = 0; nLen < nLenTest; nLen++){

    if (isSeparator(acTest[nLen])) break;

  }

	if (nLen > 0){

    static char *s;
    s = mk_s(acTest, nLen, true);   

    static int nID;
    nID = (int) map_builtin.getString(s);

    if (nID > 0){

      if (nOldFormatStyle == 0){
        static char *z;
        z = mk_s(acTest, nLen);
        checkFormatStyle(z, nID);
      }

      static int nOldInput;
      nOldInput = nInput;

      static int nOldXPos;
      nOldXPos = nXPos;

			nInput += nLen; nXPos += nLen;

			myToken->wr_Token(nOldInput, nOldXPos, nOldXPos + (nInput - nOldInput), nID);

			return true;
		}
	}
	return false;
}

// ****************************
bool isOperator()
{
  if (!proceedScan()) return false;

  static char c;
  c = acTest[0];

  static bool bChar;
  bChar = isDelimitorCharacter(c); // AND, OR

  static int nLen;
  for (nLen = 0; nLen < nLenTest; nLen++){
    static char c2;
    c2 = acTest[nLen];

    if (isWhitespace(c2) || isDelimitorMisc(c2) || isDelimitorNumber(c2) || (!bChar && isDelimitorCharacter(c2)) || isDelimitorSymbol(c2)) break;
    if (c == '=' && isDelimitorOperator(c2)){
      nLen++;
      break;
    }

  }

	if (nLen > 0){

    static char *s;
    s = mk_s(acTest, nLen, true);

    if (s[0] == '*' && s[1] == '/'){ // strncmp(s, "*/", 2) == 0

      static int nOldInput;
      nOldInput = nInput;

      static int nOldXPos;
      nOldXPos = nXPos;

			nInput += nLen; nXPos += nLen;

  		myToken->wr_Token(nOldInput, nOldXPos, nOldXPos + (nInput - nOldInput), token__REM_MULTILINE_STOP);

			return true;

    } else {
      static int nID;
      nID = (int) map_operator.getString(s);

      if (nID > 0){

       static int nOldInput;
       nOldInput = nInput;

       static int nOldXPos;
       nOldXPos = nXPos;

			  nInput += nLen; nXPos += nLen;

			  myToken->wr_Token(nOldInput, nOldXPos, nOldXPos + (nInput - nOldInput), nID);

			  return true;
		  }
    }

	}
	return false;
}

// ****************************
// * bool isSymbol()
// *
// * description:
// * scans for a symbol using the symbol table
// * if a symbol has been found, it generates the associated token
// *
// * parameter:
// * none
// *
// * return:
// * true, if a symbol has been found
// * false, no symbol has been found
// ****************************
bool isSymbol()
{
  if (!proceedScan()) return false;

  static int nLen;
  for (nLen = 0; nLen < nLenTest; nLen++){

    static char c;
    c = acTest[nLen];

    if (isDelimitorSymbol(c)){ nLen = 1; break; }
		else if(isWhitespace(c) || isDelimitorMisc(c) || isDelimitorNumber(c) || isDelimitorCharacter(c) || isDelimitorOperator(c)) break;

  }

	if (nLen > 0){

		static char *s;
    s = mk_s(acTest, nLen);

		static int nID;
    nID = (int) map_symbol.getString(s);

    if (nID > 0){

      static int nOldInput;
      nOldInput = nInput;

      static int nOldXPos; 
      nOldXPos = nXPos;

			nInput += nLen; nXPos += nLen;

			myToken->wr_Token(nOldInput, nOldXPos, nOldXPos + (nInput - nOldInput), nID);
      
			return true;
		}
	}
	return false;
}

// ****************************
// * bool isMultiLineSymbol()
// *
// * description:
// * scans for a symbol using the symbol table
// * if a symbol has been found, it generates the associated token
// *
// * parameter:
// * none
// *
// * return:
// * true, if a symbol has been found
// * false, no symbol has been found
// ****************************
bool isMultiLineSymbol()
{
  if (!proceedScan()) return false;

  static int nLen;
  nLen = 1;

	if (acTest[0] == '_'){    
    {

      static int nOldInput;
      nOldInput = nInput;

      static int nOldXPos;
      nOldXPos = nXPos;

			nInput += nLen; nXPos += nLen;

			myToken->wr_Token(nOldInput, nOldXPos, nOldXPos + (nInput - nOldInput), token__SYM_UL);
      
			return true;
		}
	}
	return false;
}

// ****************************
// * bool isType()
// *
// * description:
// * scans for a type using the type table
// * if a type has been found, it generates the associated token
// *
// * parameter:
// * none
// *
// * return:
// * true, if a type has been found
// * false, no type has been found
// ****************************
bool isType()
{
  if (!proceedScan()) return false;

  static int nLen;
  for (nLen = 0; nLen < nLenTest; nLen++){

    if (isSeparator(acTest[nLen])) break;

  }

	if (nLen > 0){

    static char *s;
    s = mk_s(acTest, nLen, true);

    static int nID;
    nID = (int) map_type.getString(s);

    if (nID > 0){

      static char *z;
      z = mk_s(acTest, nLen);

      static int nOldInput;
      nOldInput = nInput;

      static int nOldXPos;
      nOldXPos = nXPos;

			nInput += nLen; nXPos += nLen;

			myToken->wr_Token(nOldInput, nOldXPos, nOldXPos + (nInput - nOldInput), nID);
			return true;
		}
	}
	return false;
}

// ****************************
// * bool isConstant()
// *

// * description:
// * searches for several constants
// * if a constant has been found in one of the sub-functions, the associated token has been generated
// *
// * parameter:
// * none
// *
// * return:
// * true, if a constant has been found
// * false, no constant has been found
// ****************************
bool isConstant()
{
   	// think carefully, if you want to change the order of the following function calls!
	     if (isCurrency	()) return true; 
  //else if (isSingle  	()) return true; // isDouble() is used everytime
	else if (isDouble		()) return true;
	else if (isBoolean	()) return true;
	else if (isHex			()) return true;
	else if (isOctal		()) return true;
	else if (isBinary		()) return true;
	else if (isByte			()) return true;
	else if (isInteger	()) return true;
	else if (isLong			()) return true;

	return false;
}

bool isLong()
{
  static t_long l;

  static int nOldInput;
  nOldInput = nInput;

  static int nOldXPos;
  nOldXPos = nXPos;

	if (isLong(currentPhrase(), &l, false)){
    myToken->wr_Long(nOldInput, nOldXPos, nOldXPos + (nInput - nOldInput), token__LITERAL_LONG, l);
    return true;
	}
	return false;
}

// ****************************
// * bool isLong(char *acText, t_long *l, bool bTestLength = true)
// *
// * description:
// * searches for  a long constant
// * if a long constant has been found, the associated token will be generated
// *
// * e.g. 2134&
// *
// * return:
// * true, if a long constant has been found
// * false, no long constant has been found
// ****************************
bool isLong(char *acText, t_long *l, bool bTestLength = true)
{
  if (!bTestLength) if (!proceedScan()) return false;

  static char *s, *b, *c;
	s = b = acText;

	static int nLen;
  nLen = 1;

	static bool bOK;
  bOK = false;

	static bool bSuffix;
  bSuffix = false;

	static char cSign;
  cSign = 0;

	if (*s >= '0' && *s <= '9'){	bOK = true; s++;	}
 	else if(*s == '+' || *s == '-'){
		cSign = *s;
		s++;
	} else return false;

	if (*s >= '0' && *s <= '9'){ s++; nLen++; }
	else if (bOK == false) return false;

	while(*s != 0){
 		if (*s >= '0' && *s <= '9')	s++;
		else if (*s == '&'){ bSuffix = true; break; }
		else break;
		nLen++;
	}

  if (s[0] != 0 && !isSeparator(*s)) return false; // Oops, no separator = not a number

  if (myToken != 0){
  	// test for unary +/-
  	if (cSign){
			if (checkUnary()) return false;
  	}
	}

	if (bTestLength) if (nLen != (signed) strlen(b)) return false; // some wrong characters in trailer?

   { scannerError(" Sorry! LONG not supported yet due to 64bit calculation limits of C library" ); }

	errno = 0;
  char *ss = mk_s(b, nLen);
#ifdef WINDOWS  // HIDE
  *l = _strtoi64(ss, &c, 10); // HIDE
#else // HIDE
  *l = strtoll(ss, &c, 10); // HIDE
#endif // HIDE
   // UNHIDE *l = strtoll(ss, &c, 10);
  if (c - nLen != ss) return false;

	// * check for overflow
  // *  LONG_LONG_MIN, LONG_LONG_MAX
  // http://msdn.microsoft.com/library/en-us/vclib/html/_crt_atof.2c_.atoi.2c_._atoi64.2c_.atol.asp?frame=true
// sieht so aus als k?nte ich keinen check unter win machen, ist sowieso anders als unter linux
/*
  int n = errno;
	if (n == ERANGE && *l == LONG_MIN){ scannerError("long number underflow < -4294967296"); bSuccess = false; return false; }
	if (n == ERANGE && *l == LONG_MAX){ scannerError("long number overflow > 4294967295"); bSuccess = false; return false; }
*/
	nInput += nLen; nXPos += nLen;
  if (bSuffix){ nInput++;  nXPos++; }// skip the suffix

	return true;
}

bool isByte()
{
	static t_byte c;

  static int nOldInput;
  nOldInput = nInput;

  static int nOldXPos;
  nOldXPos = nXPos;

	if (isByte(currentPhrase(), &c, false)){
		myToken->wr_Byte(nOldInput, nOldXPos, nOldXPos + (nInput - nOldInput), token__LITERAL_BYTE, c);
    return true;
	}
	return false;
}

// ****************************
// * bool isByte(char *acText, t_byte *c, bool bTestLength = true)
// *
// * description:
// * searches for a byte constant
// * if a byte constant has been found, the associated token will be generated
// *
// * e.g. 2134%
// *
// * return:
// * true, if a byte constant has been found
// * false, no byte constant has been found
// ****************************
bool isByte(char *acText, t_byte *c, bool bTestLength = true)
{
  if (!bTestLength) if (!proceedScan()) return false;

  static char *s, *b;
	s = b = acText;

  static int nLen;
  nLen = 1;

	static bool bOK;
  bOK = false;

	static bool bSuffix;
  bSuffix = false;

	static char cSign;
  cSign = 0;

	if (*s >= '0' && *s <= '9'){	bOK = true; s++;	}
 	else if(*s == '+' || *s == '-'){
		cSign = *s;
		s++;
	}
	else return false;

	if (*s >= '0' && *s <= '9'){ s++; nLen++; }
	else if (bOK == false) return false;


	while(*s != 0){
 		if (*s >= '0' && *s <= '9')	s++;
		else if (*s == '%'){ bSuffix = true; break; }
		else break;
		nLen++;
	}
	if (*s == '%'){ return false; } // Oops, the suffix is for int
	if (*s == '&'){ return false; } // Oops, the suffix is for long

  if (s[0] != 0 && !isSeparator(*s)) return false; // Oops, no separator = not a number; example: 8e --> unknown token (right)

	if (myToken != 0){
  	// test for unary +/-
  	if (cSign){
			if (checkUnary()) return false;
  	}
	}
	if (bTestLength) if (nLen != (signed) strlen(b)) return false; // some wrong characters in trailer?

	static int n;
  n = atoi(mk_s(b, nLen));
	if (n > 255 || n < 0) return false; // out of range
	*c = n;

	nInput += nLen; nXPos += nLen;
  if (bSuffix){ nInput++; nXPos++; }// skip the suffix

	return true;
}

bool isInteger()
{
	static t_integer n;
  
  static int nOldInput;
  nOldInput = nInput;

  static int nOldXPos;
  nOldXPos = nXPos;

	if (isInteger(currentPhrase(), &n, false)){
		myToken->wr_Integer(nOldInput, nOldXPos, nOldXPos + (nInput - nOldInput), token__LITERAL_INTEGER, n);
    return true;
	}
	return false;
}

// ****************************
// * bool isInteger(char *acText, t_integer *n, bool bTestLength = true)
// *
// * description:
// * searches for a integer constant
// * if a integer constant has been found, the associated token will be generated
// *
// * e.g. 2134%
// *
// * return:
// * true, if a integer constant has been found
// * false, no integer constant has been found
// ****************************
bool isInteger(char *acText, t_integer *n, bool bTestLength = true);

bool isHex()
{
  static t_long l;

  static int nOldInput;
  nOldInput = nInput;

  static int nOldXPos;
  nOldXPos = nXPos;

  if (isHex(currentPhrase(), &l, false)){
		myToken->wr_Long(nOldInput, nOldXPos, nOldXPos + (nInput - nOldInput), token__LITERAL_LONG, l);
    return true;
	}
	return false;
}

// ****************************
// * bool isHex(char *acText, t_long *l, bool bTestLength = true)
// *
// * description:
// * searches for a hex constant
// * if a hex constant has been found, the associated token will be generated
// *
// * isHex scans string pointer to determine if it's a hexadecimal number.
// * A valid hexadecimal number starts with '&H' and is followed
// * by up to 16 significant digits
// * comprised of 0-9, and a-f (case insensitive).
// * Values are by default unsigned
// *
// * return:
// * true, if a hex constant has been found
// * false, no hex constant has been found
// ****************************
bool isHex(char *acText, t_long *l, bool bTestLength = true)
{
  if (!bTestLength) if (!proceedScan()) return false;

  static char *s, *str, *b;
  b = s = str = acText;

	static bool bOK;
  bOK = false;

  static double dValue;
  dValue = 0;

  static bool bSigned;
  bSigned = true;

	static int nLen;
  nLen = 0;

  if ((str[0] == '&' && (str[1] == 'h' || str[1] == 'H'))) {
		str += 2;
		s = str;
		nLen += 2;
  } else return false;

	if (*s != 0){
        while ((*s >= '0' && *s <= '9') || (*s >= 'A' && *s <= 'F') || (*s >= 'a' && *s <= 'f')) {
            if (*s >= '0' && *s <= '9') dValue = dValue * 16 + *s - '0';
            if (*s >= 'A' && *s <= 'F') dValue = dValue * 16 + 10 + *s - 'A';
            if (*s >= 'a' && *s <= 'f') dValue = dValue * 16 + 10 + *s - 'a';
            s++;
						nLen++;
            if (*s == 0) break;
        }
        if (s > str) {    // make sure at least one hex character
        	bOK = true;
        }
	  	else return false;
    }

  if (bTestLength) if (nLen != (signed) strlen(b)) return false; // some wrong characters in trailer?

  if (s[0] != 0 && !isSeparator(*s)) return false; // Oops, no separator = not a number

	if (bSigned) if (dValue > 2147483647.) dValue = -(4294967296. - dValue);

	if (nLen <= 16) *l = (t_long) dValue;
	else { scannerError(" hex long number overflow > FFFFFFFFFFFFFFFF"); bSuccess = false; return false; }


  if (str - s < 0){
    nInput += s - str + 2;
    nXPos += s - str + 2;
  } else {
    nInput += str - s + 2;
    nXPos += str - s + 2;
  }

	return bOK;
}

bool isBinary()
{
  static t_long l;

  static int nOldInput;
  nOldInput = nInput;

  static int nOldXPos;
  nOldXPos = nXPos;

	if (isBinary(currentPhrase(), &l, false)){
		myToken->wr_Long(nOldInput, nOldXPos, nOldXPos + (nInput - nOldInput), token__LITERAL_LONG, l);
    return true;
	}
	return false;
}

// ****************************
// * bool isBinary(char *acText, t_long *l, bool bTestLength = true)
// *
// * description:
// * searches for a binary constant
// * if a binary constant has been found, the associated token will be generated
// *
// * isBinary scans string pointer to determine if it's a binary number.
// * A valid binary number starts with '0b' (or '0B'), or '&B'  (or '&b) and is followed
// * by up to 31 significant digits (as many leading 0's as desired are permitted)
// * comprised of 0 or 1.
// *
// * return:
// * true, if a binary constant has been found
// * false, no binary constant has been found
// ****************************
bool isBinary(char *acText, t_long *l, bool bTestLength = true)
{
 if (!bTestLength) if (!proceedScan()) return false;

 static char *s, *str, *b;
 
 b = s = str = acText;

 static bool bOK;
 bOK  = false;

 static t_long lValue;
 lValue  = 0;

 static int nLen;
 nLen = 0;

 if ((str[0] == '&' && (str[1] == 'b' || str[1] == 'B')))
 {
  str += 2;
  nLen += 2;
  s = str;
 } else return false;

 if (*s != 0){
        while (*s >= '0' && *s <= '1') {
            if (*s >= '0' && *s <= '1') lValue = (lValue << 1) + *s - '0';
            s++;
						nLen++;
            if (*s == 0) break;
        }
        if (s > str) {    // make sure at least one binary character
         bOK = true;
        }
    else return false;
    }

	if (bTestLength) if (nLen != (signed) strlen(b)) return false; // some wrong characters in trailer?

  if (s[0] != 0 && !isSeparator(*s)) return false; // Oops, no separator = not a number

  if (nLen <= 64) *l = lValue;
	else { scannerError(" binary long number overflow > 2^64"); bSuccess = false; return false; }


  if (str - s < 0){
    nInput += s - str + 2;
    nXPos += s - str + 2;    
  } else {
    nInput += str - s + 2;
    nXPos += str - s + 2;
  }

  return bOK;
}

// ****************************
// * bool isDate()
// *
// * description:
// * searches for a date constant
// * if a date constant has been found, the associated token will be generated
// *
// * parameter:
// * none
// *
// * return:
// * true, if a date constant has been found
// * false, no date constant has been found
// ****************************
bool isDate();

// ****************************
// * bool isTime()
// *
// * description:
// * searches for a time constant
// * if a time constant has been found, the associated token will be generated
// *
// * parameter:
// * none
// *
// * return:
// * true, if a time constant has been found
// * false, no time constant has been found
// ****************************
bool isTime();

bool isOctal()
{
	static t_long l;

  static int nOldInput; nOldInput = nInput;
  static int nOldXPos; nOldXPos = nXPos;

	if (isOctal(currentPhrase(), &l, false)){
		myToken->wr_Long(nOldInput, nOldXPos, nOldXPos + (nInput - nOldInput), token__LITERAL_LONG, l);
    return true;
	}
	return false;
}

// ****************************
// * bool isOctal(char *acText, t_long *l, bool bTestLength = true)
// *
// * description:
// * searches for a octal constant
// * if a octal constant has been found, the associated token will be generated
// *
// * isOctal scans string pointer to determine if it's an octal number.
// * A valid octal number starts with '&O' and is followed by up to 11
// * significant digits
// * comprised of 0-7. Values are by default signed positive values.
// *
// * parameter:
// * none
// *
// * return:
// * true, if a octal constant has been found
// * false, no octal constant has been found
// ****************************
bool isOctal(char *acText, t_long *l, bool bTestLength = true)
{
  if (!bTestLength) if (!proceedScan()) return false;

  static char *s, *str, *b;
	
  b = s = str = acText;

	static bool bOK;
  bOK = false;

  static t_double dValue; 
  dValue = 0;

  static int nLen;
  nLen = 0;

  if (str[0] == '&' && (str[1] == 'o' || str[1] == 'O')) {
		str += 2;
		nLen += 2;
		s = str;
  } else return false;

	if (*s != 0){
    while (*s >= '0' && *s <= '7') {
        dValue = dValue * 8 + *s - '0';
        s++;
        nLen++;
        if (*s == 0) break;
    }
    if (s > str) bOK = true;    // make sure at least one octal character
	  else return false;
  }

	if (bTestLength) if (nLen != (signed) strlen(b)) return false; // some wrong characters in trailer?

  if (s[0] != 0 && !isSeparator(*s)) return false; // Oops, no separator = not a number

  if (nLen <= 23) *l = (t_long) dValue;
	else { scannerError(" octal long number overflow > 2^64"); bSuccess = false; return false; }

  if (str - s < 0){
    nInput += s - str + 2;
    nXPos += s - str + 2;    
  }	else {
    nInput += str - s + 2;
    nXPos += str - s + 2;
  }

	return bOK;
}

// ****************************
// * bool isString()
// *
// * description:
// * searches for a string constant
// * if a string constant has been found, the associated token will be generated
// *
// * parameter:
// * none
// *
// * return:
// * true, if a string constant has been found
// * false, no string constant has been found
// ****************************
bool isString();

bool isSingle()
{
	static t_single f;

  static int nOldInput; nOldInput = nInput;
  static int nOldXPos; nOldXPos = nXPos;

	if (isSingle(currentPhrase(), &f, false)){
		myToken->wr_Single(nOldInput, nOldXPos, nOldXPos + (nInput - nOldInput), token__LITERAL_SINGLE, f);
    return true;
	}
	return false;
}

// ****************************
// * bool isSingle(char *acText, t_single *f, bool bTestLength = true)
// *
// * description:
// * searches for a single constant
// * if a single constant has been found, the associated token will be generated
// *
// * parameter:
// * none
// *
// * e.g. 21.34!
// *
// * return:
// * true, if a single constant has been found
// * false, no single constant has been found
// ****************************
bool isSingle(char *acText, t_single *f, bool bTestLength = true)
{
  if (!bTestLength) if (!proceedScan()) return false;

  static char *s, *b;
	static bool t, p;
	s = b = acText;

  static int nLen; 
  nLen = 0;

	static bool qb;
  qb = false;

	static bool bSuffix;
  bSuffix = false;

	static char cSign;
  cSign = 0;

  t = false;
	if (*s == '+' || *s == '-'){
		cSign = *s;
		s++;
		nLen++;
  }
  while (*s >= '0' && *s <= '9') {
    s++;
		nLen++;
    t = true;
  }
  if (p = (*s == '.')) {
    s++;
		nLen++;
    while (*s >= '0' && *s <= '9') {
      s++;
			nLen++;
      t = true;
    }
  }
  if (!t) return false;

  if (*s == 'E' || *s == 'e' || *s == '^'){
	  if (*s == '^'){
			qb = true;
		}
		s++;
		nLen++;
	}
	else if (p == true) goto ok;
	else return false;

  if (*s == '-' || *s == '+'){
		s++;
		nLen++;
	}
  t = false;
  while (*s >= '0' && *s <= '9') {
    s++;
		nLen++;
    t = true;
  }
  if (!t) return false;

ok:
  if (s && (*s == 'F' || *s == 'f')){
		if (qb == true){
			return false;
		}
		s++;
		nLen++;
	} else if (qb == true){
		return false;
	}
	if (*s == '!'){ bSuffix = true; }
	if (*s == '#'){ return false; } // Oops, the suffix is for double

	// test for unary +/-
	if (cSign){
		if (checkUnary()) return false;
	}

	if (bTestLength) if (nLen != (signed) strlen(b)) return false; // some wrong characters in trailer?

  if (s[0] != 0 && !isSeparator(*s)) return false; // Oops, no separator = not a number

  *f = atof(mk_s(b, nLen));


  // 
  // * check for overflow, if a suffix is present, a overflow is an error, otherwise it is a long constant
  // * since atof() returns a double, the return is accepted as a double then compared against
	// * the min and max allowable values for overflow.
//	if (*f > FLT_MAX) { if (bSuffix == true) { scannerError("single number overflow < -3.402823e38 to -1.401298e-45"); bSuccess = false; } return false; }
//	if (*f < FLT_MIN) { if (bSuffix == true) { scannerError("single number underflow > 1.401298e-45 to 3,402823e38"); bSuccess = false; } return false; }

	nInput += nLen; nXPos += nLen;
  if (bSuffix){ nInput++; nXPos++; }// skip the suffix

	return true;
}

bool isDouble()
{
	static t_double d;

  static int nOldInput; nOldInput = nInput;
  static int nOldXPos; nOldXPos = nXPos;

	if (isDouble(currentPhrase(), &d, false)){
		myToken->wr_Double(nOldInput, nOldXPos, nOldXPos + (nInput - nOldInput), token__LITERAL_DOUBLE, d);
    return true;
	}
	return false;
}

// ****************************
// * bool isDouble(char *acText, t_double *d, bool bTestLength = true)
// *
// * description:
// * searches for a double constant
// * if a double constant has been found, the associated token will be generated
// *
// * parameter:
// * none
// *
// * e.g. 21.34#
// *
// * return:
// * true, if a double constant has been found
// * false, no double constant has been found
// ****************************
bool isDouble(char *acText, t_double *d, bool bTestLength = true)
{
  if (!bTestLength) if (!proceedScan()) return false;

  static char *s, *b;
	static bool t, p;
	
  s = b = acText;

	static int nLen;
  nLen = 0;

	static bool qb;
  qb = false;

	static bool bSuffix;
  bSuffix = false;

	static char cSign;
  cSign = 0;

  t = false;
	if (*s == '+' || *s == '-'){
		cSign = *s;
		s++;
		nLen++;
  }
  while (*s >= '0' && *s <= '9') {
    s++;
		nLen++;
    t = true;
  }
  if (p = (*s == '.')) {
    s++;
		nLen++;
    while (*s >= '0' && *s <= '9') {
      s++;
			nLen++;
      t = true;
    }
  }
  if (!t){
    return false;
  }

  if (*s == '#'){ 
    goto ok2;
  }

  if (*s == 'E' || *s == 'e' || *s == '^'){
	  if (*s == '^'){
			qb = true;
		}
		s++;
		nLen++;
	}
	else if (p == true) goto ok;
	else return false;

  if (*s == '-' || *s == '+'){
		s++;
		nLen++;
	}
  t = false;
  while (*s >= '0' && *s <= '9') {
    s++;
		nLen++;
    t = true;
  }
  if (!t) return false;

ok:
  if (s && (*s == 'F' || *s == 'f')){
		if (qb == true){
			return false;
		}
		s++;
		nLen++;
	}  
ok2:
	if (qb == true){
		return false;
	}

	if (*s == '#'){ bSuffix = true; }

	// test for unary +/-
	if (cSign){
		if (checkUnary()) return false;
	}

	if (bTestLength) if (nLen != (signed) strlen(b)) return false; // some wrong characters in trailer?

  if (s[0] != 0 && !isSeparator(*s)) return false; // Oops, no separator = not a number

  errno = 0;
  *d = strtod(mk_s(b, nLen), NULL);

/*
  if (errno == ERANGE && *d == -HUGE_VAL) { scannerError("double number underflow < 2.2250738585072014E-308"); bSuccess = false; return false; }
  if (errno == ERANGE && *d ==  HUGE_VAL) { scannerError("double number overflow > 1.7976931348623157e+308"); bSuccess = false; return false; }
*/

	nInput += nLen; nXPos += nLen;
  if (bSuffix){ nInput++; nXPos++; }// skip the suffix

	return true;
}

bool isCurrency()
{
	static t_currency c;

  static int nOldInput; nOldInput = nInput;
  static int nOldXPos; nOldXPos = nXPos;

	if (isCurrency(currentPhrase(), &c, false)){
		myToken->wr_Currency(nOldInput, nOldXPos, nOldXPos + (nInput - nOldInput), token__LITERAL_CURRENCY, c);
    return true;
	}
	return false;
}

// ****************************
// * bool isCurrency(char *acText, t_currency *c, bool bTestLength = true)
// *
// * description:
// * searches for a currency constant
// * if a currency constant has been found, the associated token will be generated
// *
// * parameter:
// * none
// *
// * e.g. 21.34@
// *
// * return:
// * true, if a currency constant has been found
// * false, no currency constant has been found
// ****************************
bool isCurrency(char *acText, t_currency *c, bool bTestLength = true)
{
  if (!bTestLength) if (!proceedScan()) return false;

  static char *s, *b;
	static bool t, p;
	
  s = b = acText;
	static int nLen; nLen = 0;
	static int nLen2; nLen2 = 0;
	static bool qb; qb = false;
	static bool bSuffix; bSuffix = false;
	static char cSign; cSign = 0;

  t = false;
	if (*s == '+' || *s == '-'){
		cSign = *s;
		s++;
		nLen++;
  }
  while (*s >= '0' && *s <= '9') {
    s++;
		nLen++;
    t = true;
  }
  if (p = (*s == '.')) {
    s++;
		nLen++;
    while (*s >= '0' && *s <= '9') {
      s++;
			nLen++;
  		nLen2++;
      t = true;
    }
  }
  if (!t) return false;

	if (p == true) goto ok;
	else return false;

  t = false;
  while (*s >= '0' && *s <= '9') {
    s++;
		nLen++;
    t = true;
  }
  if (!t) return false;

ok:

  if (*s == '@'){ bSuffix = true; } else { return false; }

	// test for unary +/-
	if (cSign){
		if (checkUnary()) return false;
	}

	if (bTestLength) if (nLen != (signed) strlen(b)) return false; // some wrong characters in trailer?

  if (nLen2 > 4) { scannerError("currency number overflow"); bSuccess = false; return false; }

  errno = 0;
 
  static t_long bc; bc = atol(mk_s(b, nLen - 1 - nLen2));

  static t_long ad; 


  if (nLen2){
    ad = atol(mk_s(b + nLen - nLen2, nLen));
    for (int i = 0; i < 4 - nLen2; i++){
      ad = ad * 10;
    }
  } else {
    ad = 0;
  }

  (*c).setValue(bc, ad);


/*
  if (errno == ERANGE && d == -HUGE_VAL) { scannerError("currency number underflow < 2.2250738585072014E-308"); bSuccess = false; return false; }
  if (errno == ERANGE && d ==  HUGE_VAL) { scannerError("currency number overflow > 1.7976931348623157e+308"); bSuccess = false; return false; }
*/	

	nInput += nLen; nXPos += nLen;
  if (bSuffix){ nInput++; nXPos++; } // skip the suffix

	return true;
}

// ****************************
// * bool isIdentifier()
// *
// * description:
// * searches for a identifier
// * if a identifier has been found, the associated token will be generated
// *
// * parameter:
// * none
// *
// * return:
// * true, if an identifier has been found
// * false, no identifier has been found
// ****************************
bool isIdentifier()
{
  if (!proceedScan()) return false;

  static char *s, *b;
	
  s = b = currentPhrase();
	static int nLen; nLen = 0;
	static int nType; nType = token__MSC_IDENTIFIER;


  if ((*s >= 'a' && *s <= 'z') || (*s >= 'A' && *s <= 'Z') || (*s == '_')) {
    s++;
		nLen++;
		while(*s != 0){
	    if ((*s >= 'a' && *s <= 'z')
           || (*s >= 'A' && *s <= 'Z')
           || (*s >= '0' && *s <= '9')
           || *s == '_'){ s++; }
			else if (*s == '%'){ nType = token__MSC_ID_INTEGER; break; }
			else if (*s == '#'){ nType = token__MSC_ID_DOUBLE; break; }
			else if (*s == '!'){ nType = token__MSC_ID_SINGLE; break; }
			else if (*s == '$'){ nType = token__MSC_ID_QSTRING; break; }
			else if (*s == '&'){ nType = token__MSC_ID_LONG; break; }
			else break;

			nLen++;

		}
  }

  if (b[0] == '_' && nLen == 1) return false;

	if (nLen == 0) return false;
/*
	if (isKeyword(b, nLen)){ // check if someone has used a DIM as identifier like in "DIM+ n AS INTEGER"
		scannerError(utility::con(mk_s(b, nLen), " is a keyword and can not be used as an identifier"));
		bSuccess = false;
		return false;
	}
*/
	if (nLen > MAX_IDENTIFIER){ // identifier length too long
		scannerError(utility::con(mk_s(b, nLen), " is too long, please find shorter identifier name"));
		bSuccess = false;
		return false;
	}

  static int nOldInput; nOldInput = nInput;
  static int nOldXPos; nOldXPos = nXPos;
	
	nInput += nLen; nXPos += nLen;
  if (nType != token__MSC_IDENTIFIER){ nInput++; nXPos++; }// skip the suffix %, $... etc.

	myToken->wr_CString(nOldInput, nOldXPos, nOldXPos + (nInput - nOldInput), nType, b, nLen);

	return true;
}

// ****************************
// * bool isExtIdentifier()
// *
// * description:
// * searches for a ext. identifier
// * if a identifier has been found, the associated token will be generated
// *
// * parameter:
// * none
// *
// * return:
// * true, if an identifier has been found
// * false, no identifier has been found
// ****************************
bool isExtIdentifier()
{
  if (!proceedScan()) return false;

  static char *s, *b;
	
  s = b = currentPhrase();
	static int nLen; nLen = 0;
	static int nType; nType = token__MSC_EXTIDENTIFIER;


  if (*s >= ' ' || *s <= -1) {
    s++;
		nLen++;
		while((int) *s != 0){
      if(isSeparator(*s) || isDelimitor(*s) || isQuote(*s)) break;
	    else if (*s >= ' ' || *s <= -1){ s++; }
			else break;

     
			nLen++;

		}
  }

  if (b[0] == '_' && nLen == 1) return false;

	if (nLen == 0) return false;
/*
	if (isKeyword(b, nLen)){ // check if someone has used a DIM as identifier like in "DIM+ n AS INTEGER"
		scannerError(utility::con(mk_s(b, nLen), " is a keyword and can not be used as an identifier"));
		bSuccess = false;
		return false;
	}
*/
	if (nLen > MAX_IDENTIFIER){ // identifier length too long
		scannerError(utility::con(mk_s(b, nLen), " is too long, please find shorter identifier name"));
		bSuccess = false;
		return false;
	}

  static int nOldInput; nOldInput = nInput;
  static int nOldXPos; nOldXPos = nXPos;
	
	nInput += nLen; nXPos += nLen;

	myToken->wr_CString(nOldInput, nOldXPos, nOldXPos + (nInput - nOldInput), nType, b, nLen);

	return true;
}

// ****************************
// * bool isLabel()
// *
// * description:
// * searches for a label
// * if a label has been found, the associated token will be generated
// *
// * parameter:
// * none
// *
// * return:
// * true, if a label has been found
// * false, no label has been found
// ****************************
bool isLabel()
{
  if (!proceedScan()) return false;

	if (myToken->lastWrittenToken() != token__KB_LINE) return false;

  static char *s, *b;
	
  s = b = currentPhrase();
	static int nLen; nLen = 1;
	static int nPos; nPos = nInput;
  

  if (/*(*s >= '0' && *s <= '9') || */(*s >= 'a' && *s <= 'z') || (*s >= 'A' && *s <= 'Z') || (*s == '_')) {
    s++;
		while(*s != 0 && *s != ':'){
	    if ((*s >= 'a' && *s <= 'z')
           || (*s >= 'A' && *s <= 'Z')
           || (*s >= '0' && *s <= '9')
           || *s == '_') s++;
			else break;
			nLen++;

		}
  }

  if (*s != ':'){
    nInput = nPos;
    return false;
  }

	if (nLen > MAX_IDENTIFIER){ // identifier length too long
		scannerError(utility::con(mk_s(b, nLen), " is too long, please find shorter identifier name"));
		bSuccess = false;
		return false;
	}

  static int nOldInput; nOldInput = nInput;
  static int nOldXPos; nOldXPos = nXPos;

	nInput += nLen + 1; nXPos += nLen + 1;

  myToken->wr_CString(nOldInput, nOldXPos, nOldXPos + (nInput - nOldInput), token__MSC_LABEL, b, nLen);

	return true;
}

// ****************************
// * bool isLine()
// *
// * description:
// * searches for a line number
// * if a line number has been found, the associated token will be generated
// *
// * parameter:
// * none
// *
// * return:
// * true, if a line number has been found
// * false, no line number has been found
// ****************************
bool isLine()
{
  if (!proceedScan()) return false;

	if (myToken->lastWrittenToken() != token__KB_LINE) return false;

  static char *s, *b;
	
  s = b = currentPhrase();
	static int nLen; nLen = 0;
	static int nPos; nPos = nInput;

  if (*s >= '0' && *s <= '9') {
    s++;
		nLen++;
		while(*s != 0){
	    if (*s >= '0' && *s <= '9') s++;
			else break;
			nLen++;

		}
  }

	switch(*s){
		// all separators
	  case ' ':
    case '\'':
    case '\t':
    case '\v':
    case '\f':
    case '\n':
    case 13: // 0xd
			break;
		default:
      nInput = nPos;
			return false;
	}

	if (myToken->lastLastLastWrittenToken() == token__SYM_UL && myToken->lastLastWrittenToken() == token__MSC_EOL) return false; // _ EOL pretends from to be LINE

	if (nLen > MAX_IDENTIFIER){ // identifier's length too long
		scannerError(utility::con(mk_s(b, nLen), " is too long, please find a shorter identifier name"));
		bSuccess = false;
		return false;
	}

  if (nLen == 0){
    nInput = nPos;
    return false;
  }

  static int nOldInput; nOldInput = nInput;
  static int nOldXPos; nOldXPos = nXPos;

	nInput += nLen; nXPos += nLen;

  myToken->wr_CString(nOldInput, nOldXPos, nOldXPos + (nInput - nOldInput), token__MSC_LINE, b, nLen);

	return true;
}

// ****************************
// * bool isComment()
// *
// * description:
// * searches for a comment
// * if a comment has been found, the associated token will be generated
// *
// * parameter:
// * none
// *
// * return:
// * true, if a comment has been found
// * false, no comment has been found
// ****************************
bool isComment()
{
  if (!proceedScan()) return false;
  
  register int i;

  if (acTest[0] == 'R' || acTest[0] == 'r') i = 0;
  else if (acTest[0] == '\'') i = 1;
  else if (acTest[0] == '/') i = 2;
  else return false;


	static const char *acPattern; //acPattern = 0;
	static bool b; b = false;

  static int nLen3;
  static bool bMultiLine; bMultiLine = false;
	for (; b == false && i < 4; i++){

    if (i == 0){
      acPattern = "REM";
    }
    else if (i == 1){
      acPattern = "'";
    }
    else if (i == 2){ 
      bMultiLine = true;
      acPattern = "/*";
    } else if (i == 3){ 
      bMultiLine = true;
      acPattern = "/**";
   }


  	nLen3 = strlen(acPattern);
 		if (nLenTest >= nLen3){
  	  if (utility::my_strnicmp(acPattern, acTest, nLen3) == 0){
				if (utility::my_stricmp(acPattern, "REM") == 0){
     			switch(acTest[nLen3]){
      			// all separators
        		case ' ':
      	    case '\t':
      	    case ':':
      	    case '\n':
      	    case '\f':
      	    case '\r':
      	    case '\v':
  				  	b = true;
		 		          if (i == 0) nLenTest -= 3;
		          else if (i == 1) nLenTest -= 1;
              else if (i == 3) nLenTest -= 3;
              else if (i == 2) nLenTest -= 2;
              
      				break;
      			default:
     					b = false;
      				break;
     			}
				} else b = true; // ' needs no separator
   		}
		}
	}

 	if (b){

		static char *s, *t, s2;
		static int nLen; nLen = 0;

		s = t = &acInput[nInput + nLen3];
    s2 = *s;

    static int nLen2; nLen2 = 0;

    {
		  while(*s != 0){

	    for (int i = 0; *s == '$' && i < 2; i++){

      	const char *acPattern2 = 0;

		  		   if (i == 0)	acPattern2 = "$dynamic";
		    else if (i == 1)	acPattern2 = "$static";

  	    int n = strlen(acPattern2);
     		if (nLenTest >= n){
          if (utility::my_strnicmp(acPattern2, s, n) == 0){
            if (i == 0){
              myToken->wr_Token(0, 0, 0, token___DYNAMIC);
            } else if (i == 1){
              myToken->wr_Token(0, 0, 0, token___STATIC);
            }
          }
        }
      }

      if (bMultiLine){
        bREMMulti = true;
        if (s2 == '*' && (*s == '/' || *s == 0)){
          if (*s == 0){ scannerError(" unexpected end of file, missing */ at the end"); }
          nLen += 1;
          nLen2 = 2;
          bREMMulti = false;
          break; 
        }
  			if (*s == '\n'){ increaseLineNr(); }  	
      } else {
  			if (*s == '\n'){ break; }
      }
      s2 = *s;
			s++;
			nLen++;
		}
    }
    static int nOldInput; nOldInput = nInput;
    static int nOldXPos; nOldXPos = nXPos;

		nInput += nLen3 + nLen; nXPos += nLen3 + nLen;
		
		if (utility::my_stricmp(acPattern, "REM") == 0){
			myToken->wr_CString(nOldInput, nOldXPos, nOldXPos + (nInput - nOldInput), token__REM, t, nLen);
    } else if (utility::my_stricmp(acPattern, "/**") == 0){
			myToken->wr_CString(nOldInput, nOldXPos, nOldXPos + (nInput - nOldInput), token__REM_DOCUMENTATION, t, nLen - nLen2);
    } else if (utility::my_stricmp(acPattern, "/*") == 0){      
			myToken->wr_CString(nOldInput, nOldXPos, nOldXPos + (nInput - nOldInput), token__REM_MULTILINE, t, nLen - nLen2);
      if (nLen2){
      		myToken->wr_Token(nInput, nXPos, nXPos + 2, token__REM_MULTILINE_STOP);
      }

		} else if (strcmp(acPattern, "'") == 0){
			myToken->wr_CString(nOldInput, nOldXPos, nOldXPos + (nInput - nOldInput), token__REM_SHORT, t, nLen);
		}
 		return true;

	}
	return false;
}

bool isBoolean()
{
	static t_boolean c;

  static int nOldInput; nOldInput = nInput;
  static int nOldXPos; nOldXPos = nXPos;

	if (isBoolean(&(acInput[nInput]), &c, false)){
		myToken->wr_Boolean(nOldInput, nOldXPos, nOldXPos + (nInput - nOldInput), token__LITERAL_BOOLEAN, c);
    return true;
	}
	return false;
}

// ****************************
// * bool isBoolean(char *acText, t_boolean *c, bool bTestLength = true)
// *
// * description:
// * searches for a boolean literal
// * if a boolean literal has been found, the associated token will be generated
// *
// * parameter:
// * none
// *
// * return:
// * true, if a boolean literal has been found
// * false, no boolean literal has been found
// ****************************
bool isBoolean(char *acText, t_boolean *c, bool bTestLength = true)
{
  if (!bTestLength) if (!proceedScan()) return false;

  static char *acTest;
	static int nLenTest;

	acTest = acText;

  int i;
  if (acTest[0] == 'T' || acTest[0] == 't') i = 0;
  else if (acTest[0] == 'F' || acTest[0] == 'f') i = 1;
  else return false;

	nLenTest = strlen(acTest);

	static const char *acPattern; acPattern = 0;
	static bool b; b = false;

  int nLen;
	for (; b == false && i < 2; i++){

		 		 if (i == 0)	acPattern = "TRUE";
		else if (i == 1)	acPattern = "FALSE";

  	nLen = strlen(acPattern);

 		if (nLenTest >= nLen){

    	if (utility::my_strnicmp(acPattern, acTest, nLen) == 0){
 
        if (isSeparator(acTest[nLen])){
		   		b = true;
        } else {
   		  	b = false;
   			}
   		}
		}
	}

	if (b){
    // TRUE is -1 and not 1, because of TRUE = NOT FALSE (1111 1111 = NOT 0000 0000) as signed: -1 --> FALSE = 0
		*c = (utility::my_stricmp(acPattern, "TRUE") == 0 ? -1 : 0);
    int k = strlen(acPattern);
		nInput += nLen; nXPos += nLen;    
		return true;
	}
	return false;
}

// ****************************
// * bool addLineNr()
// *
// * description:
// * generate the internal! line number token, this line number represents the line number of the scanned kbasic source codes
// *
// * parameter:
// * none
// *
// * return:
// * true
// ****************************
bool addLineNr()
{
  //console::print(nLineNr);
  //console::print("\n");
	myToken->wr_Integer(0, 0, 0, token__KB_LINE, nLineNr);
  increaseLineNr();
	return true;
}

void increaseLineNr()
{
  nLineNr++;
  nXPos = 1; // current row in line
}

// ****************************
// * char *mk_s(char *s, int nLen)
// *
// * description:
// * terminates a given string (array of characters) by zero
// *
// * parameter:
// * none
// *
// * return:
// * the zero-terminated string (array of characters)
// ****************************
char *mk_s(char *s, int nLen, bool bUpper = false)
{
  char *c = myTextbuffer->get(s, nLen);
  if (!bUpper) return c;

	for (register unsigned int i = 0; i < nLen; i++) c[i] = toupper(c[i]);

	return c;
}

// ****************************
// * char *currentPhrase()
// *
// * description:
// * generate a string (array of characters) terminated by zero for comparision in the several tokenizer functions
// *
// * parameter:
// * none
// *
// * return:
// * the generated string (array of characters, zero-terminated)
// ****************************
char *currentPhrase()
{
  return &(acInput[nInput]);
}

char currentChar()
{
  return (acInput[nInput]);
}

bool isNewline(bool bWriteToken = true)
{
  if (!proceedScan()) return false;

  switch(currentChar())
	{
  case '\n':
    nInput++; nXPos++;
    if (bWriteToken){
      myToken->wr_Token(0, 0, 0, token__MSC_EOL);
    	addLineNr();
    }
		return true;
    break;
  default:
    return false;
    break;
	}
	return false;
}

bool isQuote()
{
  if (!proceedScan()) return false;

  switch(currentChar())

	{
  case '\"':
    nInput++; nXPos++;
		return true;
  default:
    return false;
	}

  return false;
}

bool isQuote(char c)
{
	return c == '\"';
}

bool isSeparator()
{
	if (isSeparator(currentChar())){
    nInput++; nXPos++;
    return true;
  }
  return false;
}

static bool isSeparator(char c)
{
	return isWhitespace(c) || isDelimitor(c);
}

static bool isWhitespace(char c)
{
	switch(c)
	{
  case ' ':
  case '\t':
  case '\f':
  case '\r':
  case '\v':
		return true;
    break;
  default:
    return false;
    break;
	}
	return false;
}


static bool isDelimitor(char c)
{
  return isDelimitorOperator(c) || isDelimitorSymbol(c) || isDelimitorMisc(c);
}


static bool isDelimitorOperator(char c)
{
	switch(c)
	{
  case '+':
  case '-':
  case '*':
  case '/':
  case '\\':
  case '=':
  case '>':
  case '<':
  case '^':
  case '&':
  case '|':
		return true;
  default:
    return false;
    break;
  }
	return false;
}

static bool isDelimitorSymbol(char c)
{
	switch(c)
	{
  case '.':
  case '(':
  case ')':
  case '[':
  case ']':
  case ',':
  case ':':
  case '!':
  case ';':
  case '?':
//  case '_':  HINT kann sowohl als symbol oder bestandteil eines identifiers vorkommen, deswegen auskommentiert
  case '#':
  case '{':
  case '}':
		return true;
  default:
    return false;
    break;
  }
	return false;
}

static bool isDelimitorCharacter(char c)
{
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z' || c == '_');
}

static bool isDelimitorNumber(char c)
{
	switch(c)
	{
  case '0':
  case '1':
	case '2':
  case '3':
  case '4':
  case '5':
	case '6':
  case '7':
  case '8':
  case '9':
    return true;
    break;
  default:
    return false;
    break;
  }
	return false;
}

static bool isDelimitorMisc(char c)
{
	switch(c)
	{
  case '\"':
  case '\'':
  case '\n':
  case 13: // 0xd
		return true;
    break;
  default:
    return false;
    break;
  }
	return false;
}

bool proceedScan()
{
  return bSuccess && bGoOn && nInput < nInputLen && nInputLen > 0;
}

bool checkUnary()
{
	static int n; n = myToken->lastWrittenToken();
	if (n == token__KB_LINE || n == token__SYM_COMMA) return false;
		
	if (!(strcmp("", myToken->operator_(n)) || n == token__SYM_BR_OP || n == token__DATA)) return true;

	return false;
}

void checkFormatStyle(char *s, int nId)
{
  if (!(nOldFormatStyle == 0)) return;

  nOldFormatStyle = 1;
}

int formatStyle()
{
  return nOldFormatStyle;
}



public:
bool bSuccess;

private:

char *acTest;
int nLenTest;
int nInputLen;

bool scan_main(char *text, char *filename, bool bSilent, bool bDebug, bool bAdditional, bool bAddEOFToken, bool bUseCache);
bool analyse(char *filename, bool bAdditional, bool bAddEOFToken);

bool createMapKeyword();
bool createMapBuiltin();
bool createMapOperator();
bool createMapType();
bool createMapSymbol();

void init(token *t, cache *_my_cache);

bool scannerError(const char *acScannerError, bool bLineNr = true);


bool printToken();

bool bREMMulti;


char *acInput;
int nInput;
int nStart;
int nLineNr; // the current line number
token *myToken;

cache *my_cache;

textbuffer *myTextbuffer;

int nXPos;
bool bGoOn;


int nOldFormatStyle;

const char *acFilename;


};



#endif
