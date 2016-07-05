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

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <math.h>



#include "../kbshared/cache.h"

#include "token.h"
#include "../kbshared/console.h"
#include "scanner.h"
#include "utility.h"
#include "memory_variable.h"

#include "../kbshared/typedef.h"

bool bInitDone = false;





XIntMap map_keyword;
XIntMap map_builtin;
XIntMap map_operator;
XIntMap map_type;
XIntMap map_symbol;

scanner::scanner(token *t, cache *_my_cache)
{
	init(t, _my_cache);
}

scanner::scanner()
{
	init(0, 0);
}

scanner::~scanner()
{
	delete myTextbuffer;
}


void scanner::init(token *t, cache *_my_cache)
{
  my_cache = _my_cache;

  acInput = 0;
  nInput = 0;

  nLineNr = 1; // the current line number of the kbasic input source code
  nXPos = 1; // current row in line

  bSuccess = true;
	myToken = t;

  myTextbuffer = new textbuffer(); // needed to truncate big input strings or zero terminate them

  if (bInitDone == false){
    bInitDone = true;

    createMapKeyword();
    createMapBuiltin();
    createMapOperator();
    createMapType();
    createMapSymbol();
  }


  nOldFormatStyle = 0;

//  setInfoWindow(0);

}

bool scanner::scan(char *text, char *filename, bool bSilent, bool bDebug, bool bAddEOFToken, bool bUseCache)
{
  return scan_main(text, filename, bSilent, bDebug, false, bAddEOFToken, bUseCache);
}

bool scanner::scanAdditional(char *text, char *filename, bool bSilent, bool bDebug, bool bUseCache)
{
  return scan_main(text, filename, bSilent, bDebug, true, false, bUseCache);
}

// ****************************
// * bool scan(char *text)
// *
// * description:
// * entry point for this module
// *
// * parameter:
// * char *text = kbasic source code, which have to be scanned by the scanner
// *
// * return:
// * true, if no error
// * false, if error occured
// ****************************
bool scanner::scan_main(char *text, char *filename, bool bSilent, bool bDebug, bool bAdditional, bool bAddEOFToken, bool bUseCache)
{
//  ir = _ir;
  acFilename = filename;

  if (bSilent == false){
    if (HAS_CONSOLE){
 	     if (!bAdditional) CONSOLE print("\nKBasic Scanner - highly optimized scanner\n(C) Copyright KBasic Software 2000 - 2006\n");

      //if (bAdditional){
        CONSOLE header("\n-- scan -- ");
        CONSOLE print(filename);
        CONSOLE print("\n\n");
//        CONSOLE printKBFILE(filename);
      //} else {
       //CONSOLE header("\n-- scan --\n\n");
      //}
    }
  }

	acInput = text;
	static /**/ bool bRet;
	static /**/ int nPos;
  nPos = myToken->getPos();
  myToken->addSource(text);
  bool bCached = false;
  

  if (bUseCache && filename && my_cache) bCached = bRet = my_cache->readScanner(filename, myToken);
  if (bCached){ 
    if (bSilent == false && HAS_CONSOLE){
      CONSOLE print("Using scanner cache for ", console__GREEN);
      CONSOLE print(filename, console__GREEN);
      CONSOLE print("\n", console__GREEN);
    }

    CONSOLE printKBPROGRESS(0);

  } else {
    bRet = analyse(filename, bAdditional, bAddEOFToken);
  }

  if (!bAdditional && bAddEOFToken){
    addEOFToken();
  } else {
    myToken->wr_Token(0, 0, 0, token__KB_EOF2); // set stop character at the end
  }

  if (bUseCache && bRet && !bCached && my_cache && filename && strlen(filename)) my_cache->writeScanner(filename, myToken, nPos);
	

  if (bSilent == false && !bCached){
    myToken->setPos(nPos);
    bRet = printToken();
    
	  if (HAS_CONSOLE) CONSOLE print("\n");
  }

	return bRet;
}

// ****************************
// * bool analyse()
// *
// * description:
// * the main scanner routine, the different scanner routines are called here
// *
// * parameter:
// * none
// *
// * return:
// * true, if no error
// * false, if error occured
// ****************************
bool scanner::analyse(char *filename, bool bAdditional, bool bAddEOFToken)
{

	nInput = 0;
	nLineNr = 1;
  nXPos = 1;

	bGoOn = true;
  bSuccess = true;

  nInputLen = strlen(acInput);
 
  bREMMulti = false;
  

  if (!bAdditional){ 
    myToken->resetPos();
	  myToken->wr_Single(0, 0, 0, token__KB_VERSION, scanner__KBASIC_VERSION);
  }
  
  if (filename != 0){
    myToken->wr_CString(0, 0, 0, token__KB_FILENAME, filename);
  }

	if (proceedScan()){ // only if not empty
  	addLineNr();

    bool bLong;
    int nLen;
     while (proceedScan()){

       if (nInput % 10)CONSOLE printKBPROGRESS((nInput * 100 / nInputLen));
         acTest = currentPhrase();
	       nLenTest = nInputLen - nInput;//****strlen(acTest);

			// scan with the help of these sub scanner routines, symbols, types etc. have different routines (with sub-routines too)

        // speed optimizations        
         if (acTest[0] == '\n' && isNewline ()){
            continue;
         }


          if (bREMMulti){ // optimization for syntax highlighting, won't use this, if it is for parsing
            if (acTest[0] == '*' && nInput + 1 < nInputLen && acTest[1] == '/'){
              if (isComment ()){
                bREMMulti = false;
                continue;
              }
            }
            nInput++;
            nXPos++;
            continue;
          }

          // check for " and “
          if (acTest[0] == '\"'/* || (nInput + 2 < nInputLen && acTest[0] == -30 && acTest[1] == -128 && acTest[2] == -100)*/ && isString()) continue;
          if (acTest[0] == '<' && nInput + 1 < nInputLen && acTest[1] == '?' && isString()) continue;

          if (acTest[0] == ' '){
            nInput++;
            nXPos++;
            continue;
            }

         // speed optimization, keywords must be longer than 1
         for (nLen = 0; nLen < nLenTest; nLen++){
           if (isSeparator(acTest[nLen])) break;
         }
         bLong = nLen > 1;


			     if (isComment  ()) continue;
      else if (bLong && isKeyword	(0, 0)) continue;

      else if ((acTest[0] == '#' || bLong) && isDate			()) continue;
    	else if ((acTest[0] == '#' || bLong) && isTime			()) continue;

 			else if (isLabel		()) continue;
 			else if (isLine			()) continue;

 			else if (bLong && isType			()) continue;

 			else if (isConstant	()) continue; // 
 			else if (isSymbol		()) continue;
 			else if (isOperator	()) continue;

			else if (isSeparator()) continue;

 			else if (isIdentifier()) continue;
 			else if (isExtIdentifier()) continue;// write as string  umlaute ... ����

      else if (isMultiLineSymbol()) continue;

      else if (proceedScan()){ // print message only if a error has not already been echoed
 				scannerError("unknown token");        
        break;
      }
 		}

  }

  if (bSuccess && nInputLen) CONSOLE printKBPROGRESS(100);
 
	return bSuccess;
}

bool scanner::createMapKeyword()
{
  register int i = token__KEYWORD + 1;

//  map_keyword.resize(499);
  //map_keyword.setAutoDelete(false);

	const char *acLast;
	while (true){

		const char *acPattern = token::keyword_(i);
		if (strcmp(acPattern, "") == 0) break;
	//	acLast = acPattern;

     //printf("%s ", acPattern);

    //int *nn = 0;
    map_keyword.addString(acPattern, i++);
    //map_keyword[acPattern] = nn;//(int *) i++;
    //int k = map_keyword[acPattern];
    //k = k;

  }
  return true;
  
}

bool scanner::createMapBuiltin()
{
  register int i = token__BUILTIN + 1;

	const char *acLast;
	while (true){

		const char *acPattern = token::builtin_(i);
		if (strcmp(acPattern, "") == 0) break;
		//acLast = acPattern;
     //printf("%s ", acPattern);

    map_keyword.addString(acPattern, i++);

  }

  return true;

}

bool scanner::createMapOperator()
{
  register int i = token__OPERATOR + 1;

	const char *acLast;

	while (true){

		const char *acPattern = token::operator_(i);
		if (strcmp(acPattern, "") == 0) break;
		//acLast = acPattern;
    // printf("%s ", acPattern);

    map_operator.addString(acPattern, i++);

  }
  return true;

}

bool scanner::createMapType()
{
  register int i = token__NUM_TYPE + 1;

  const char *acLast;
	while (true){

		const char *acPattern = token::type_(i);
		if (strcmp(acPattern, "") == 0) break;
		//acLast = acPattern;
    // printf("%s ", acPattern);

    map_type.addString(acPattern, i++);

  }
  return true;

}

bool scanner::createMapSymbol()
{
  register int i = token__SYMBOL + 1;

  const char *acLast;
	while (true){

		const char *acPattern = token::symbol_(i);
		if (strcmp(acPattern, "") == 0) break;
		//acLast = acPattern;
   // printf("%s ", acPattern);

    map_symbol.addString(acPattern, i++);

  }
  return true;

}

// ****************************
// * bool scannerError(char *acScannerError)
// *
// * description:

// * prints a scanner error message
// *
// * parameter:
// * char *acScannerError = the error message to print
// *
// * return:
// * dummy
// ****************************
bool scanner::scannerError(const char *acScannerError, bool bLineNr)
{
	char *acText = myTextbuffer->get(1024 + strlen(acScannerError));

  if (bLineNr) sprintf(acText, "\nscanner error: %s in line %d in file %s\n", acScannerError, (nLineNr - 1), acFilename);
	else sprintf(acText, "\nscanner error: %s\n", acScannerError);

  CONSOLE printError(acText);

	//sprintf(acText, "scanner error in <b>line %d</b>:<br> <font color='#0000ff'>%s</font>", (nLineNr - 1), acScannerError);
//  showError(acText);

  bSuccess = false;
	return false;
}

// ****************************
// * bool printToken()
// *
// * description:
// * prints all scanned token (formated)
// *
// * parameter:
// * none
// *
// * return:
// * true, if no error
// * false, if error occured
// ****************************
bool scanner::printToken()
{
  bool bError = false;

  while (myToken->printOneToken(&bError));

	return !bError;
}

bool scanner::isString()
{
  if (!proceedScan()) return false;

  static char *s, *s2, *b;	

  s = b = currentPhrase();
	static int nLen;
	static int nLen2;
  nLen = 2;
  nLen2 = 0;

	static int nSaveOutput;
	static int nSaveOutput2;
  nSaveOutput = myToken->getPos();

  bool bHTMLEscape;
  int nInside;

  if (*s == '<' && *(s + 1) != 0 && *(s + 1) == '?'){
    bHTMLEscape = true; 
    nInside = 0;
    s++;
  } else {
    bHTMLEscape = false;
  }

  if (bHTMLEscape || *s == '"'){

      s++;
  
    s2 = s;

		myToken->wr_Token(0, 0, 0, token__LITERAL_STRING);
    nSaveOutput2 = myToken->getPos();
    myToken->wr_Integer2(0);

    int n = 0;
		while(*s != 0){      
      if (bHTMLEscape && (*s == '<' && *(s + 1) == '?')){
        nInside++;
      }

			if (bHTMLEscape == false && (*s == '"' && *(s + 1) == '"') 
       ){ // is there "   ""  " inside? --> "   "    "
        if (n){
				  myToken->wr_CString2((t_cstring) s2, n);
				  nLen += n;
          nLen2 += n;
          n = 0;
        }
				myToken->wr_Char(*s);
				s += 2;
				nLen += 2;
        nLen2++;
        s2 = s;
			} else {
        if (bHTMLEscape){
          if (*s == '?' && *(s + 1) != 0 && *(s + 1) == '>'){
            if (nInside == 0){
              s++;
              break;
            } else {
              nInside--;
            }
          }
        } else {
  				if (*s == '"') break;
        }
    
				if (*s == '\n' && bHTMLEscape == false){
					myToken->setPos(nSaveOutput);
 	  			scannerError("string literal not closed, missing \" or ?> at the end of line");
          bSuccess = false;
					return false; // print error
				}
        n++;
   		  s++;
			}
		}
    if (n){
	    myToken->wr_CString2((t_cstring) s2, n);
	    nLen += n;
      nLen2 += n;
      n = 0;
    }

  } else return false;

	myToken->wr_Char(0);

  static int nOldInput; 
  nOldInput = nInput;

  static int nOldXPos;
  nOldXPos = nXPos;

	nInput += nLen; nXPos += nLen;

  static int n;
  n = myToken->getPos();
  myToken->setPos(nSaveOutput);
	myToken->wr_Token(nOldInput, nOldXPos, nOldXPos + (nInput - nOldInput), token__LITERAL_STRING);
  myToken->setPos(nSaveOutput2);
	myToken->wr_Integer2(nLen2);
  myToken->setPos(n);

  if (bHTMLEscape){
  	nInput += 2;
  }

	return true;
}

bool scanner::isDate()
{
  if (!proceedScan()) return false;

  static char *s, *str, *b;
	
  b = s = str = currentPhrase();

	static bool bOK;
  bOK = false;

	static int nLen;
  nLen = 0;

  // format is #yyyy-mm-dd#

  if (str[0] == '#') {
		str += 1;
		s = str;
		
	}	else return false;


  static char acYear[64];
  static char acMonth[64];
  static char acDay[64];

  static int i;
	if (*s != 0){

      i = 0;
      while ((*s >= '0' && *s <= '9') && i < 4) {

          if (*s >= '0' && *s <= '9') acYear[i] = *s;
          s++;
					
          i++;
          if (*s == 0){ return false; } // no error, maybe it's a filehandle
          else if (*s == '#'){ return false; } // no error, maybe it's a filehandle
          else if (*s == '-'){ s++; break; }

      }
      if (i == 0) return false; // maybe it is  just the symbol #
      acYear[i] = '\0';

      i = 0;
      while ((*s >= '0' && *s <= '9') && i < 2) {

          if (*s >= '0' && *s <= '9') acMonth[i] = *s;
          s++;
					
          i++;
          if (*s == 0){ return false; } //  scannerError("Wrong date format. It must be #yyyy-mm-dd#."); }
          else if (*s == '#'){ return false; } //  scannerError("Wrong date format. It must be #yyyy-mm-dd#."); }
          else if (*s == '-'){ s++; break; }

      }
      if (i == 0) return false; // maybe it is  just the symbol #
      acMonth[i] = '\0';

      i = 0;
      while ((*s >= '0' && *s <= '9') && i < 2) {

          if (*s >= '0' && *s <= '9') acDay[i] = *s;
          s++;
					
          i++;
          if (*s == 0){ return false; } //  scannerError("Wrong date format. It must be #yyyy-mm-dd#."); }
          else if (*s == '#') break;
          else if (*s == ' '){ break; }

      }
      acDay[i] = '\0';

      if (s > str) {    // make sure at least one number character
        bOK = true;
      }	else return false;
  }

  // *** test for time literal

  static char acHour[64];
  static char acMinute[64];
  static char acSecond[64];
  static bool am; am = false;
  static bool ampm; ampm = true;

  acHour[0] = '\0';
  acMinute[0] = '\0';
  acSecond[0] = '\0';

  if (*s == ' ') {
		s++;
		
	}	else goto g;

	if (*s != 0){

      i = 0;
      while ((*s >= '0' && *s <= '9') && i < 2) {

          if (*s >= '0' && *s <= '9') acHour[i] = *s;
          s++;
					
          i++;
          if (*s == 0){ return false; } // no error, maybe it's a filehandle
          else if (*s == '#'){ return false; } // no error, maybe it's a filehandle
          else if (*s == ':'){ s++; break; }

      }
      if (i == 0) return false; // maybe it is  just the symbol #

      acHour[i] = '\0';

      i = 0;
      while ((*s >= '0' && *s <= '9') && i < 2) {

          if (*s >= '0' && *s <= '9') acMinute[i] = *s;
          s++;
					
          i++;
          if (*s == 0){ return false; } //  scannerError("Wrong time format. It must be #hh:mm:ss AM/PM#."); }
          else if (*s == '#'){ return false; } //  scannerError("Wrong time format. It must be #hh:mm:ss AM/PM#."); }
          else if (*s == ':'){ s++; break; }

      }
      if (i == 0) return false; // maybe it is  just the symbol #

      acMinute[i] = '\0';

      i = 0;
      while ((*s >= '0' && *s <= '9') && i < 2) {

          if (*s >= '0' && *s <= '9') acSecond[i] = *s;
          s++;
					
          i++;
          if (*s == 0){ return false; } //  scannerError("Wrong time format. It must be #hh:mm:ss AM/PM#."); }
          else if (*s == ' ') break;

      }
      acSecond[i] = '\0';

      char c[3];
      c[1] = 0;
      i = 0;

      if (*s == ' '){
       while (i < 3) {

         c[i] = *s;
           s++;
					  
           i++;
           if (*s == 0){ return false; } //  scannerError("Wrong time format. It must be #hh:mm:ss AM/PM#."); }
           else if (*s == '#') break;

       }
      }
      if ((c[1] == 'A' || c[1] == 'a') && (c[2] == 'M' || c[2] == 'm')){
        am = true;
      } else if ((c[1] == 'P' || c[1] == 'p') && (c[2] == 'M' || c[2] == 'm')){
        am = false;
      } else if (*s == '#'){
        ampm = false;
      } else {
        return false;  //  scannerError("Wrong time format. It must be #hh:mm:ss AM/PM#."); 
      }


      if (s > str) {    // make sure at least one number character
        bOK = true;
      }	else return false;
  }

g:
  if (*s == '#'){
		s++;
		
	}	else return false;

  static int nHour; nHour = atoi(acHour);
  static int nMinute; nMinute = atoi(acMinute);
  static int nSecond; nSecond = atoi(acSecond);

  if (ampm && !am) nHour += 12;

  if (nHour < 0 || nHour >= 24){ return false; } //  scannerError("Wrong time. Hour must be > 0 and <= 12."); }
  if (nMinute < 0 || nMinute > 59){ return false; } //  scannerError("Wrong time. Month must be > 0 and <= 59."); }
  if (nSecond < 0 || nSecond > 59){ return false; } //  scannerError("Wrong time. Second must be > 0 and <= 59."); }

  // ***

  static int nYear; nYear = atoi(acYear);
  static int nMonth; nMonth = atoi(acMonth);
  static int nDay; nDay = atoi(acDay);

  if (nMonth <= 0 || nMonth >= 13){ return false; } //  scannerError("Wrong date. Month must be > 0 and < 13."); }
  if (nDay <= 0 || nDay >= 32){ return false; } // scannerError("Wrong date. Day must be > 0 and < 32."); }

  t_date d(nYear, nMonth, nDay);
  d.nHour = nHour;
  d.nMinute = nMinute;
  d.nSecond = nSecond;

  static int nOldInput; nOldInput = nInput;
  static int nOldXPos; nOldXPos = nXPos;

  if (str - s < 0){
    nInput += s - str + 1;
    nXPos += s - str + 1;    
  } else {
    nInput += str - s + 1;
    nXPos += str - s + 1;    
  }

  myToken->wr_Date(nOldInput, nOldXPos, nOldXPos + (nInput - nOldInput), token__LITERAL_DATE, d);

	return bOK;
}

bool scanner::isTime()
{
  if (!proceedScan()) return false;

  static char *s, *str, *b;
	

  b = s = str = currentPhrase();

	static bool bOK;
  bOK = false;

	
  // format is #hh:mm:ss PM#
  // format is #hh:mm:ss AM#
  // format is #0-12:m:s#

  if (str[0] == '#') {
		str += 1;
		s = str;
		
	}	else return false;


  static char acHour[64];
  static char acMinute[64];
  static char acSecond[64];
  static bool am; am = false;

  static int i;
	if (*s != 0){

      i = 0;
      while ((*s >= '0' && *s <= '9') && i < 2) {

          if (*s >= '0' && *s <= '9') acHour[i] = *s;
          s++;
					
          i++;
          if (*s == 0){ return false; } // no error, maybe it's a filehandle
          else if (*s == '#'){ return false; } // no error, maybe it's a filehandle
          else if (*s == ':'){ s++; break; }

      }
      if (i == 0) return false; // maybe it is  just the symbol #

      acHour[i] = '\0';

      i = 0;
      while ((*s >= '0' && *s <= '9') && i < 2) {

          if (*s >= '0' && *s <= '9') acMinute[i] = *s;
          s++;
					
          i++;
          if (*s == 0){ return false; } //scannerError("Wrong time format. It must be #hh:mm:ss AM/PM#."); }
          else if (*s == '#'){ return false; } // scannerError("Wrong time format. It must be #hh:mm:ss AM/PM#."); }
          else if (*s == ':'){ s++; break; }

      }
      if (i == 0) return false; // maybe it is  just the symbol #

      acMinute[i] = '\0';

      i = 0;
      while ((*s >= '0' && *s <= '9') && i < 2) {

          if (*s >= '0' && *s <= '9') acSecond[i] = *s;
          s++;
					
          i++;
          if (*s == 0){ return false; } // scannerError("Wrong time format. It must be #hh:mm:ss AM/PM#."); }
          else if (*s == ' ') break;

      }
      acSecond[i] = '\0';

      char c[3];
      c[1] = 0;
      i = 0;

      if (*s == ' '){
       while (i < 3) {

         c[i] = *s;
           s++;
					  
           i++;
           if (*s == 0){ return false; } // scannerError("Wrong time format. It must be #hh:mm:ss AM/PM#."); }
           else if (*s == '#') break;

       }
      }
      if ((c[1] == 'A' || c[1] == 'a') && (c[2] == 'M' || c[2] == 'm')){
        am = true;
      } else if ((c[1] == 'P' || c[1] == 'p') && (c[2] == 'M' || c[2] == 'm')){
        am = false;
      } else {
        return false;  // scannerError("Wrong time format. It must be #hh:mm:ss AM/PM#."); 
      }


      if (s > str) {    // make sure at least one number character
        bOK = true;
      }	else return false;
  }

  if (*s == '#') {
		s++;
		
	}	else return false;

  static int nHour; nHour = atoi(acHour);
  static int nMinute; nMinute = atoi(acMinute);
  static int nSecond; nSecond = atoi(acSecond);

  if (nHour < 0 || nHour >= 24){ return false; } // scannerError("Wrong time. Hour must be >= 0 and <= 12."); }
  if (nMinute < 0 || nMinute > 59){ return false; } // scannerError("Wrong time. Month must be >= 0 and <= 59."); }
  if (nSecond < 0 || nSecond > 59){ return false; } // scannerError("Wrong time. Second must be >= 0 and <= 59."); }

  t_date d(nHour, nMinute, nSecond, am);

  static int nOldInput; nOldInput = nInput;
  static int nOldXPos; nOldXPos = nXPos;

  if (str - s < 0){
    nInput += s - str + 1;
    nXPos += s - str + 1;    
  } else {
    nInput += str - s + 1;
    nXPos += str - s + 1;    
  }

  myToken->wr_Time(nOldInput, nOldXPos, nOldXPos + (nInput - nOldInput), token__LITERAL_TIME, d);

	return bOK;
}

bool scanner::isInteger(char *acText, t_integer *n, bool bTestLength)
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
	if (*s == '&'){ return false; } // Oops, the suffix is for long

  if (s[0] != 0 && !isSeparator(*s)) return false; // Oops, no separator = not a number; example: 8e --> unknown token (right)

	if (myToken != 0){
  	// test for unary +/-
  	if (cSign){
			if (checkUnary()) return false;
  	}
	}
	if (bTestLength) if (nLen != (signed) strlen(b)) return false; // some wrong characters in trailer?

  errno = 0;
	*n = atoi(mk_s(b, nLen));

  if (*n >= 0 && b[0] == '-'){ /*if (bSuffix == true)*//*{ scannerError("integer number underflow < -2147483648"); bSuccess = false;}*/ return false; }
  if (*n < 0 && b[0] != '-'){ /*if (bSuffix == true)*//*{ scannerError("integer number overflow > 2147483647"); bSuccess = false;}*/ return false; }


	nInput += nLen; nXPos += nLen;
  if (bSuffix){ nInput++;  nXPos++; }// skip the suffix

	return true;
}
