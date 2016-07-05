/*
***************************************************************************
Copyright (C) 2000-2008 KBasic Software: www.kbasic.com. All rights reserved.
Source codes are copyrighted by Bernd Noetscher 2000-2008.

You may use this source codes under the terms of the GNU Public License (Version 3) as published 
by the Free Software Foundation. 

If you are interested in using the source codes for other licenses or 
commercial development, you must buy commercial licenses from KBasic Software.
***************************************************************************
*/


#ifndef _console_H
#define _console_H


#include <stdio.h>
#include <string.h>


static bool console__bDebugOutput;



// console color codes:
const char console__BLACK  		= 0;
const char console__RED  		= 1;
const char console__GREEN  		= 2;
const char console__BROWN  		= 3;
const char console__BLUE  		= 4;
const char console__MAGENTA  		= 5;
const char console__CYAN  		= 6;
const char console__WHITE  		= 7;

class _console {
public:



static const void print(int nValue) // deprecated
{
	static char acText[1024];

	sprintf(acText, "%d", nValue);
  _console::printlen(acText, strlen(acText));
}

static const void print(const char * txt, int nColor)
{
	_console::printlen(txt, strlen(txt));
}

static const void print(const char * txt)
{
	_console::printlen(txt, strlen(txt));
}

static const void printlen(const char * txt, int nLen)
{
	static char acText[1024];

	memcpy(acText, txt, nLen);
	acText[nLen] = 0;

	_console::println(acText);
}

static const void printError(const char * txt)
{
	_console::println2 (txt);
}

static const void println(const char *sText)
{
  printf(sText);

}


static const void println2(const char *sText)
{
	printf(sText);
}

static void setDebugOutput(bool b)
{
	console__bDebugOutput = b;
}

static bool getDebugOutput()
{
	return console__bDebugOutput;
}


};

#endif
