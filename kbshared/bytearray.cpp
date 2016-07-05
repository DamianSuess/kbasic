/*
***************************************************************************
Copyright (C) 2000-2008 KBasic Software (Bernd Noetscher, Boseweg 9, 60529 Frankfurt / Germany).  All rights reserved.

bytearray.cpp
---------------------------------------------------------------------------
READY
19.02.2004 - new header for this file (BN)
***************************************************************************
*/



#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "typedef.h"
#include "console.h"

#ifdef IDE
#else

#include "../kbshared/console.h"

#ifdef KBBINDER
  #include "../kbshared/bytearray.h"
#else
  #include "bytearray.h"
#endif



bytearray::bytearray()
{

	acMem = 0;    // similar to before
	nMemOffset = 0;
	nMem = 0;    // start length at some value
	nMemInc = 1024 * 8;    // set memory increment to some value

	bStack = false;
	nSaveStack = 0;


  bError = false;



}

bytearray::~bytearray()
{
	if (acMem != 0){
		free(acMem);
		acMem = 0;
	}
	
}

// ****************************
// * bool bytearrayError(const char *acBytearrayError)
// *
// * description:
// * prints a bytearray error message
// *
// * parameter:
// * char *acBytearrayError = the error message to print
// *
// * return:
// * dummy
// ****************************
bool bytearray::bytearrayError(const char *acBytearrayError)
{
  if (bError) return false;

  char acText[10240];// = myTextbuffer->get(1024 + strlen(acBytearrayError));

	sprintf(acText, "\nbytearray error: %s\n", acBytearrayError);
	console::printError(acText);
  bError = true;

	return false;
}
/*
void bytearray::dump()
{
  
  
	for (int i = 0; i < nMem; i++){
	  if (i % 8 == 0){
			console::pcodePrintPos(i);
		}

		console::pcodePrintOpcBinary(acMem[i]);
	  if ((i + 1) % 8 == 0){
			console::print("\n");
		}
	}  
  
}*/

bool bytearray::insert(t_pointer v, int nSize)
{
  
  if (nSize > 0){
    int n = nMemOffset;
    int n2 = nMem;
    nMemOffset = 0;
	  if (checkSize((nMem + n + nSize)) == false){ bytearrayError(error(bytearray__NOT_ENOUGH_MEMORY)); return false;}
    nMemOffset = n;

    memcpy(acMem + nMemOffset + nSize, acMem + nMemOffset, n2 - nMemOffset);
    memcpy(acMem + nMemOffset, v, nSize); nMemOffset += nSize;
    return true;
  }

	return true;
}

void bytearray::wr_PCode(t_pcode d)
{
  // write();
	if (checkSize(sizeof(d)) == false){ bytearrayError(error(bytearray__NOT_ENOUGH_MEMORY)); return ;}

  *((t_pcode *)(acMem + nMemOffset)) = d;


  nMemOffset += sizeof(d);

	return ;
}

bool bytearray::checkSize(int nAddedSize)
{
  if (bError) return false;

	if (acMem != 0){
    /*
    if (nMemOffset + nAddedSize > 2048){
     console::print(nMemOffset + nAddedSize);
     console::print("\n");
    }*/

  	if (nMemOffset + nAddedSize >= nMem) {

			acMem = (char *) realloc(acMem, nMemOffset + nAddedSize);  // get some memory
      if (acMem == 0){
        return false;  // couldn't get memory
      }
   		nMem = nMemOffset + nAddedSize;  // adjust count of memory allocated
      //console::print("realloc\n");
  	}
    return true;
	} else {
    int n = nMemOffset + nMemInc;
    if (n < nAddedSize) n = nAddedSize;
	 	acMem = (char *) malloc(n);  // get some memory
 		if (acMem == 0) return false;  // couldn't get memory
 		nMem += n;  // adjust count of memory allocated
//      console::printError("malloc\n");
	}
	return true;
}

void bytearray::setPos(int nPos/* = -1*/)
{
#ifdef RUN
  // boundary check
	if (bStack && nPos < 0){ bytearrayError(error(bytearray__STACK_UNDERFLOW)); return; }
	if (!bStack && nPos > nMem){ bytearrayError(error(bytearray__STACK_OVERFLOW)); return; }
#else
  /*
    if (nPos == 17 && nMem == 0){
      nPos = nPos;
    }*/
	if (nPos > nMem){ 
    /*
    char ac[888];
    sprintf(ac, "|setPos %d |", (int) this);
//    sprintf(ac, "%d nPos=%d nMem=%d nMemOffset=%d %-10.10s", (int) this, nPos, nMem, nMemOffset, acMem);
    bytearrayError(ac);
    */
    bytearrayError(error(bytearray__STACK_OVERFLOW));
    return; }
#endif

	nMemOffset = nPos;
}

#endif
