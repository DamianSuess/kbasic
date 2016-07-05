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


#ifndef XINTVECTOR
#define XINTVECTOR

#define ELEMENTS 64
#define MAX_ITERATOR 64

struct _item2 {
public:
  int value;
};


class XIntVector
{
public:
  XIntVector();
  ~XIntVector();

void setAutoDelete(bool b);

bool first(int *value, int nItNo = 0);
bool next(int *value, int nItNo = 0);

bool first(void **value, int nItNo = 0);
bool next(void **value, int nItNo = 0);

int size();

bool add(int value);
bool add(void *value);
int at(unsigned int nPos);

bool remove(unsigned int nPos);
bool removeCurrent(int nItNo = 0);

void clear();



private:
bool _checkSize(unsigned int nPos);
void _init();



unsigned int nBufferSize;
unsigned int nSize;
unsigned int nPossibleSize;
unsigned int nElementSize;
unsigned int nReadPos[MAX_ITERATOR];
bool bAutoDelete;

char *acMem;


};


#endif