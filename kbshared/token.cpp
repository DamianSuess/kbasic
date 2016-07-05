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
/*

statistics:
count all
count token

*/


#include <stdlib.h>
#include <stdio.h>

#include "../kbshared/pcode_kbasic_binding.h"

#include "scanner.h"
#include "token.h"
#include "../kbshared/console.h"

token::token()
{

	ba = new bytearray();

  sSource = "";

	nLastWrittenToken = 0;
	nLastLastWrittenToken = 0;
	nLastLastLastWrittenToken = 0;

  bOutdated = true;


	myTextbuffer = new textbuffer(); // needed to truncate big input strings or zero terminate them
	myTextbuffer2 = new textbuffer(); // needed to truncate big input strings or zero terminate them
 

  bError = false;
   
}

token::~token()
{
	delete myTextbuffer;
	delete myTextbuffer2;
	delete ba;
  ba = 0;
}


void token::addSource(const char *ac)
{
  sSource += ac;
}

const char *token::getSource()
{
  return sSource.ascii();
}
