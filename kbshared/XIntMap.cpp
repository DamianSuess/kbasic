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

#include "XIntMap.h"
#include "utility.h"

XIntMap::XIntMap(void)
{
  _init();
}

XIntMap::~XIntMap(void)
{
  if (acMem != 0){
		free(acMem);
		acMem = 0;
    nBufferSize = 0;
	}
}

void XIntMap::_init()
{
  acMem = 0;  
  nBufferSize = 0;
  nSize = 0;
  nPossibleSize = 0;  
  nElementSize = sizeof(_bucket);
  nReadPos = 0;
  nBucketReadPos = 0;

  prime = 107;
}

bool XIntMap::first(int *key, int *value)
{ 
  if (nSize == 0) return 0;
  
  nReadPos = 0;
   
  while (nReadPos < nPossibleSize && nReadPos >= 0){

    _bucket *b = (_bucket *) (acMem + nReadPos * nElementSize);
    for (int i = nBucketReadPos; i < INTMAP_MAX_BUCKET; i++){
      
      if (i > b->count) break;

      _item *t = &(b->items[i]);
      if (t->used == 1){
        nBucketReadPos = i + 1;
        *key = t->key;
        *value = t->value;
        return true;
      }
      if (i == 0) break;
    } 
    nReadPos++;
    nBucketReadPos = 0;
  } 

  return false;
}

bool XIntMap::next(int *key, int *value)
{    
  while (nReadPos < nPossibleSize && nReadPos >= 0){

    _bucket *b = (_bucket *) (acMem + nReadPos * nElementSize);
    for (int i = nBucketReadPos; i < INTMAP_MAX_BUCKET; i++){
      
      if (i > b->count) break;

      _item *t = &(b->items[i]);
      if (t->used == 1){
        nBucketReadPos = i + 1;
        *key = t->key;
        *value = t->value;
        return true;
      }
      if (i == 0) break;
    } 
    nReadPos++;
    nBucketReadPos = 0;
  } 

  return false;
}

int XIntMap::size()
{ 
  return nSize;
}

bool XIntMap::_used(int key, unsigned int nPos)
{ 
  _item *x = _get(key, nPos);
  if (x == 0) return false;
  return x->used;
}

_item * XIntMap::_get(int key, unsigned int nPos)
{   
  if (nPos < nPossibleSize && nPos >= 0){
    _bucket *b = (_bucket *) (acMem + nPos * nElementSize);
    for (int i = 0; i < INTMAP_MAX_BUCKET; i++){
      
      if (i > b->count) break;

      _item *t = &(b->items[i]);
      if (t->key == key){
        return t;
      }
    }
  }

  return 0;
}

bool XIntMap::add(int key, int value)
{ 
  int nWhere = _hash(key);
  
  if (_checkSize(nWhere)){
    

      _bucket *b = (_bucket *) (acMem + nWhere * nElementSize);

      int i = b->count;
      for (; i < INTMAP_MAX_BUCKET; i++){
             

        _item *t = &(b->items[i]);

        if (t->used == 0){
          t->used = 1;
          t->key = key;
          t->value = value; 
          b->count++;
          break;
        }

             

    }
      if (i == INTMAP_MAX_BUCKET) return false;
      nSize++;

      return true;
    
  }
  printf("error adding item to hash map");
  return false;
}

bool XIntMap::addString(const char *key, int value)
{ 
/*
  if (strcmp("rumba.monique00072002250002241002380.301", key) == 0){
    int i = 0;
    i++;
  }*/
  int nWhere = _hash(key);
  
  /*
  if (strcmp(key, "myForm..Label5") == 0){
    key = key;
  }

  if (nWhere * nElementSize == 390328){
    nWhere = nWhere;
  }

  if (nWhere == 106){
    nWhere = nWhere;
  }*/
  
  if (_checkSize(nWhere)){

    


      _bucket *b = (_bucket *) (acMem + nWhere * nElementSize);

      int i = b->count;

      for (; i < INTMAP_MAX_BUCKET; i++){              

        _item *t = &(b->items[i]);

        if (t->used == 0){
          t->used = 1;
          t->key = _convert(key);
          t->value = value; 
          b->count++;
          break;
        }
              
      }
      if (i == INTMAP_MAX_BUCKET) return false;

      nSize++;

      return true;
    
  }
  printf("error adding item to hash map");
  return false;
}


bool XIntMap::set(int key, int value)
{ 
  int nWhere = _hash(key);
  
  if (_checkSize(nWhere)){

    

      _bucket *b = (_bucket *) (acMem + nWhere * nElementSize);
      
      int i = b->count;
      // if no item there, add one
      if (i == 0){
addit:
        for (; i < INTMAP_MAX_BUCKET; i++){
               
          _item *t = &(b->items[i]);

          if (t->used == 0){
            t->used = 1;
            t->key = key;
            t->value = value; 
            b->count++;
            break;
          }
        }
        if (i == INTMAP_MAX_BUCKET) return false;
        nSize++;
        return true;
      }

      i = 0;
      for (; i < b->count; i++){
      

        _item *t = &(b->items[i]);

        if (t->used == 1 && t->key == key){
          t->value = value; 
          break;
        }             

      }
      if (i == b->count) goto addit;

      return true;
    
  }
  printf("error setting item to hash map");
  return false;
}

bool XIntMap::setString(const char *key, int value)
{ 
  int nWhere = _hash(key);
  
  if (_checkSize(nWhere)){

    


      _bucket *b = (_bucket *) (acMem + nWhere * nElementSize);

      int i = b->count;
      if (i == 0){
addit:
        for (; i < INTMAP_MAX_BUCKET; i++){              

          _item *t = &(b->items[i]);

          if (t->used == 0){
            t->used = 1;
            t->key = _convert(key);
            t->value = value; 
            b->count++;
            break;
          }
                
        }
        if (i == INTMAP_MAX_BUCKET) return false;

        nSize++;

        return true;
      }

      i = 0;
      for (; i < b->count; i++){
   
        _item *t = &(b->items[i]);

        if (t->used == 1 && t->key == _convert(key)){
          t->value = value; 
          break;
        }
              
      }
      if (i == b->count) goto addit;

      return true;
    
  }
  printf("error setting item to hash map");
  return false;
}


int XIntMap::get(int key)
{ 
  int nWhere = _hash(key);  

  if (nWhere < nPossibleSize && nWhere >= 0){

      _bucket *b = (_bucket *) (acMem + nWhere * nElementSize);

      int i = 0;
      for (; i < INTMAP_MAX_BUCKET; i++){
      
        

        _item *t = &(b->items[i]);

        if (t->used == 1 && t->key == key) return t->value;

    }
      if (i == b->count) return 0;
  }

  return 0;
}

int XIntMap::getString(const char *key)
{ 
  int nWhere = _hash(key);  

  if (nWhere < nPossibleSize && nWhere >= 0){

      _bucket *b = (_bucket *) (acMem + nWhere * nElementSize);

      for (int i = 0; i < INTMAP_MAX_BUCKET; i++){
      
        if (i > b->count){
          return 0;
        }


        _item *t = &(b->items[i]);
/*
        if (strcmp("10", key) == 0){
          t = t; 
        }

        if (b->count > 1){
  console::print(key);
  console::print(" = ");
  console::print(b->count);
  console::printCR();
          t = t; 
        }
*/
        if (t->used == 1 && t->key == _convert(key)) return t->value;
      }
  }

  return 0;
}

bool XIntMap::contains(int key)
{ 
  return _used(key, _hash(key));
}

bool XIntMap::contains(const char *key)
{ 
  return _used(_convert(key), _hash(key));
}

bool XIntMap::remove(int key)
{ 
  int nWhere = _hash(key);
  
  if (_checkSize(nWhere)){

    {

      _bucket *b = (_bucket *) (acMem + nWhere * nElementSize);

      int i = 0;
      for (; i < b->count; i++){
      
        

        _item *t = &(b->items[i]);

        if (t->used == 1 && t->key == key){
          t->used = 0; 
          b->count--;
          nSize--;
          break;
        }             

      }
      if (i == b->count) return false;

      return true;
    }
  }

  return false;
}

bool XIntMap::removeString(const char *key)
{ 
  int nWhere = _hash(key);
  
  if (_checkSize(nWhere)){

    {


      _bucket *b = (_bucket *) (acMem + nWhere * nElementSize);

      int i = 0;
      for (; i < b->count; i++){
      
        

        _item *t = &(b->items[i]);

        if (t->used == 1 && t->key == _convert(key)){
          t->used = 0; 
          b->count--;
          nSize--;
          break;
        }
              
      }
      if (i == b->count) return false;

      return true;
    }
  }
  return false;
}

void  XIntMap::clear()
{ 
  if (acMem != 0){
		free(acMem);
		acMem = 0;
    nBufferSize = 0;
	}
  _init();
}

bool XIntMap::_checkSize(unsigned int nPos)
{

	if (acMem != 0){
  	if (nPos * nElementSize >= nBufferSize || nSize + 1 > nPossibleSize) {
      int m;
      if (nPos < INTMAP_ELEMENTS){
        m = INTMAP_ELEMENTS * nElementSize;
      } else {
        m = (INTMAP_ELEMENTS + nPos) * nElementSize;
      }
			acMem = (char *) realloc(acMem, nBufferSize + m);  // get some memory
	 		if (acMem == 0) return false;  // couldn't get memory
   		nBufferSize += m;  // adjust count of memory allocated
      memset(acMem + nBufferSize - m, 0, m);
      nPossibleSize = nBufferSize / nElementSize;
      //console::print("realloc\n");
  	}
    return true;
	} else {
    int m;
    if (nPos < INTMAP_ELEMENTS){
      m = INTMAP_ELEMENTS * nElementSize;
    } else {
      m = (INTMAP_ELEMENTS + nPos) * nElementSize;
    }
	 	acMem = (char *) malloc(m);  // get some memory
 		if (acMem == 0) return false;  // couldn't get memory
    memset(acMem, 0, m);
 		nBufferSize += m;  // adjust count of memory allocated
    nPossibleSize = nBufferSize / nElementSize;
//      console::printError("malloc\n");
	}
	return true;
}


int XIntMap::_hash(int key)
{
  if (key == prime) key++;
  return key % prime;
}

int XIntMap::_hash(const char *key)
{
  int h = 0;
  for ( ; *key; ++key){
    h = 31 * h + (*key);
  }
  if (h == prime) h++;
  return h > 0 ? h % prime : -h % prime;
}

int XIntMap::_convert(const char *key)
{
  int h = 0;
  for ( ; *key; ++key){
    h = 31 * h + (*key);
  }
  return h > 0 ? h : -h;
}

void XIntMap::_prime()
{
  prime = 107; return;
}