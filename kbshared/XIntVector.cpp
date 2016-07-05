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


#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "XIntVector.h"
#include "utility.h"


XIntVector::XIntVector(void)
{
  _init();
}

XIntVector::~XIntVector(void)
{
  clear();
}

void XIntVector::_init()
{
  acMem = 0;  
  nBufferSize = 0;
  nSize = 0;
  nPossibleSize = 0;  
  nElementSize = sizeof(_item2);
  memset(&nReadPos, 0, sizeof(nReadPos));
  bAutoDelete = false;
}

void XIntVector::setAutoDelete(bool b)
{
  bAutoDelete = b;
}

bool XIntVector::first(int *value, int nItNo)
{ 
  if (nSize == 0) return 0;
  
  nReadPos[nItNo] = 0;
   
  if (nReadPos[nItNo] < nPossibleSize && nReadPos[nItNo] >= 0){
    _item2 *b = (_item2 *) (acMem + nReadPos[nItNo] * nElementSize);
    *value = b->value;
//    nReadPos[nItNo]++;
    return true;
  } 

  return false;
}

bool XIntVector::next(int *value, int nItNo)
{       
  nReadPos[nItNo]++;
  if (nReadPos[nItNo] < nPossibleSize && nReadPos[nItNo] >= 0 && nReadPos[nItNo] < nSize){
    _item2 *b = (_item2 *) (acMem + nReadPos[nItNo] * nElementSize);
    *value = b->value;    
    return true;
  } 

  return false;
}

bool XIntVector::first(void **value, int nItNo)
{ 
  if (nSize == 0) return 0;
  
  nReadPos[nItNo] = 0;
   
  if (nReadPos[nItNo] < nPossibleSize && nReadPos[nItNo] >= 0){
    _item2 *b = (_item2 *) (acMem + nReadPos[nItNo] * nElementSize);
    *value = (void *) b->value;
    nReadPos[nItNo]++;
    return true;
  } 

  return false;
}

bool XIntVector::next(void **value, int nItNo)
{       
  if (nReadPos[nItNo] < nPossibleSize && nReadPos[nItNo] >= 0 && nReadPos[nItNo] < nSize){
    _item2 *b = (_item2 *) (acMem + nReadPos[nItNo] * nElementSize);
    *value = (void *) b->value;
    nReadPos[nItNo]++;
    return true;
  } 

  return false;
}

int XIntVector::size()
{ 
  return nSize;
}

bool XIntVector::add(int value)
{ 
 
  if (_checkSize(nSize + 1)){

    _item2 *b = (_item2 *) (acMem + (nSize) * nElementSize);
    b->value = value; 
    nSize++;

    return true;
    
  }
  printf("error adding item to vector");
  return false;
}

bool XIntVector::add(void *value)
{ 
 
  if (_checkSize(nSize + 1)){

    _item2 *b = (_item2 *) (acMem + (nSize) * nElementSize);
    b->value = (int) value; 
    nSize++;

    return true;
    
  }
  printf("error adding item to vector");
  return false;
}

int XIntVector::at(unsigned int nPos)
{ 
  if (nPos < nPossibleSize && nPos >= 0){

    _item2 *b = (_item2 *) (acMem + nPos * nElementSize);
    return b->value;
   
  }

  return 0;
}

bool XIntVector::remove(unsigned int nPos)
{ 
  if (nPos < nPossibleSize && nPos >= 0){

    memcpy(acMem + (nPos + 0) * nElementSize, acMem + (nPos + 1) * nElementSize, nBufferSize - (nPos + 1) * nElementSize);
    
    nSize--;

    return true;
   
  }

  return false;
}

bool XIntVector::removeCurrent(int nItNo)
{ 
  return remove(nReadPos[nItNo]);
}

void  XIntVector::clear()
{ 
  if (acMem != 0){

    if (bAutoDelete){

      int v;
      if (first(&v)){
        do {
          free ((void *) v);
        } while (next(&v));
      }

    }

		free(acMem);
		acMem = 0;
    nBufferSize = 0;
	}

  _init();
}

bool XIntVector::_checkSize(unsigned int nPos)
{
	if (acMem != 0){
  	if (nPos * nElementSize >= nBufferSize || nSize + 1 > nPossibleSize) {

			acMem = (char *) realloc(acMem, nBufferSize + ELEMENTS * nElementSize);  // get some memory
	 		if (acMem == 0) return false;  // couldn't get memory
   		nBufferSize += ELEMENTS * nElementSize;  // adjust count of memory allocated
      memset(acMem + nBufferSize - ELEMENTS * nElementSize, 0, ELEMENTS * nElementSize);
      nPossibleSize = nBufferSize / nElementSize;
      //console::print("realloc\n");
  	}
    return true;
	} else {
	 	acMem = (char *) malloc(ELEMENTS * nElementSize);  // get some memory
 		if (acMem == 0) return false;  // couldn't get memory
    memset(acMem, 0, ELEMENTS * nElementSize);
 		nBufferSize += ELEMENTS * nElementSize;  // adjust count of memory allocated
    nPossibleSize = nBufferSize / nElementSize;
//      console::printError("malloc\n");
	}
	return true;
}


