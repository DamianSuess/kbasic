/*
***************************************************************************
Copyright (C) 2000-2008 KBasic Software (Bernd Noetscher, Boseweg 9, 60529 Frankfurt / Germany).  All rights reserved.

console.h
---------------------------------------------------------------------------
19.02.2004 - new header for this file (BN)
***************************************************************************
*/



#ifndef CONSOLE_H
#define CONSOLE_H

#include "typedef.h"


#include <stdio.h>
#include <string.h>

static bool console__bDebugOutput;

extern bool bPcodePrint_SilentMode;

#ifdef KBC
#include "../kbc/XFile.h"
extern XFile finfo;
#endif


// console::color codes:
const char console__BLACK  		= 0;
const char console__RED  		= 1;
const char console__GREEN  		= 2;
const char console__BROWN  		= 3;
const char console__BLUE  		= 4;
const char console__MAGENTA  		= 5;
const char console__CYAN  		= 6;
const char console__WHITE  		= 7;

class console{
public:
	console();
	~console();



static const void print(int nValue) // deprecated
{
	static char acText[1024];

	sprintf(acText, "%d", nValue);
  console::printlen(acText, strlen(acText));
}

static const void print(const char * txt, int nColor)
{
	console::printlen(txt, strlen(txt));
}

static const void print(const char * txt)
{
	console::printlen(txt, strlen(txt));
}

static const void header(const char * txt)
{  
	printlen(txt, strlen(txt));  
}

static const void printlen(const char * txt, int nLen)
{
	static char acText[1024];

	memcpy(acText, txt, nLen);
	acText[nLen] = 0;

	console::println(acText);
}

static const void printError(const char * txt)
{
  fprintf(stderr, txt);	
  fflush(stderr);
}


#ifdef KBC
static const void printKBPROGRESS(int n)
{  

  static char acInfo[1024];
  if (finfo.open(Truncate)){ sprintf(acInfo, "#%d", n); finfo.writeBlock(acInfo, strlen(acInfo)); finfo.close(); }

}
#endif

static const void println(const char *sText)
{
  fprintf(stdout, sText);

}

static void printCR()
{

	printlen("\n", 1);
}

static const void println2(const char *sText)
{
	fprintf(stdout, sText);
}

static void setDebugOutput(bool b)
{
	console__bDebugOutput = b;
}

static bool getDebugOutput()
{
	return console__bDebugOutput;
}

static void setSub(bool b) 
{
}

static void pcodePrintOpc(const char * txt)
{
	static char acText[1024];

/*
  if (strstr(txt, "ENTER_LOCAL") != 0){
    //bSub = true;
  } else if (strstr(txt, "CALL_RETURN") != 0){
   // bSub = false;
//  } else if (strcmp(txt, "") == 0){
//    bSub = false;
  }*/

	sprintf(acText, "%-16.16s", txt);

  println(acText);
}

static void pcodePrintVar(const char *acModule, const char *acSub, const char *acVar)
{
	static char ac[1024];
	static char acText[1024];

	sprintf(acText, " ");
  if (acModule[0] != 0){
    sprintf(ac, "%s", acModule); strcat(acText, ac);    
  }
  if (acSub[0] != 0){
    sprintf(ac, ".%s", acSub); strcat(acText, ac);    
  }

  if (acModule[0] != 0 || acSub[0] != 0){
    sprintf(ac, "."); strcat(acText, ac);    
  }
	sprintf(acText, "%s", acVar); strcat(acText, ac);    

  println(acText);
}

static void pcodePrintVar(const char *acVar)
{
	static char ac[1024];
	static char acText[1024];


	sprintf(acText, " ");
	sprintf(ac, "%s", acVar); strcat(acText, ac);

  println(acText);
}

static void pcodePrintSep(const char * txt)
{
	static char acText[1024];


  sprintf(acText, " %-20.20s", txt);
  println(acText);
}

static void pcodePrintOpcBinary(unsigned char code)
{
	static char acText[1024];
	static char ac[1024];

	char c = code;
	if (c < 32) c = 32;


	sprintf(acText, "%c", c);
	sprintf(ac, "%3d", code);
  strcat(acText, ac);
	
  pcodePrint(acText);
}

static void pcodePrintPos(int nValue)
{
	static char acText[1024];

  sprintf(acText, "%06d: ", nValue);
  
  printlen(acText, strlen(acText));
}

static void pcodePrintPos(const char *s)
{
	static char acText[1024];


  sprintf(acText, "%7s ", s);
  
  printlen(acText, strlen(acText));
}

static void pcodePrint(long lValue)
{
	static char acText[1024];

  sprintf(acText, "%lld", lValue);
  
  printlen(acText, strlen(acText));
}

static void pcodePrint(double dValue)
{
	static char acText[1024];

  sprintf(acText, "%.6f", dValue);  

  printlen(acText, strlen(acText));
}

static void pcodePrint2(const char * txt)
{
	static char acText[1024];

	int nLen = strlen(txt);
  if (nLen > 1000) nLen = 1000;
    
	memcpy((void *) (acText + 2), txt, nLen);
	nLen++;
	acText[0] = ' ';
	acText[1] = '"';
	acText[1 + nLen++] = '"';
	acText[1 + nLen++] = ',';
	acText[1 + nLen++] = 0;

  printlen(acText, strlen(acText));
}

static void pcodePrint3(const char * txt)
{
	static char acText[1024];

	int nLen = strlen(txt);
  if (nLen > 1000) nLen = 1000;
  
    
	memcpy((void *) (acText + 2), txt, nLen);
	nLen++;
	acText[0] = ' ';
	acText[1] = '"';
	acText[1 + nLen++] = '"';
	acText[1 + nLen++] = 0;

  printlen(acText, strlen(acText));
}

static void pcodePrint(const char * txt)
{

	pcodePrint(txt, strlen(txt));
}

static void pcodePrint(const char * txt, int nLen)
{
	static char acText[1024];

  
	memcpy((void *) (acText + 1), txt, nLen);
	nLen++;
	acText[0] = ' ';
	acText[nLen++] = 0;

	printlen(acText, strlen(acText));
}

static void pcodePrint(const char * txt, void *p)
{
	static char acText[1024];

	sprintf(acText, "%s 0x%X", txt, p);

	printlen(acText, strlen(acText));
}

static void pcodePrint(int nValue)
{
	static char acText[1024];

  sprintf(acText, "%d", nValue);
  
  printlen(acText, strlen(acText));
}

static void pcodePrintCR()
{
	
	printCR();
}

};

#endif
