/*
***************************************************************************
Copyright (C) 2000-2008 KBasic Software (Bernd Noetscher, Boseweg 9, 60529 Frankfurt / Germany).  All rights reserved.
***************************************************************************
*/


#ifndef XINTMAP
#define XINTMAP

#define INTMAP_MAX_BUCKET 32
#define INTMAP_ELEMENTS 106

struct _item {
public:
  char used;
  int key;
  int value;
};

struct _bucket {
public:
  _item items[INTMAP_MAX_BUCKET];
  int count;
};

class XIntMap
{
public:
  XIntMap();
  ~XIntMap();

bool first(int *key, int *value);
bool next(int *key, int *value);

int size();

bool contains(int key);
bool contains(const char *key);

bool add(int key, int value);
int get(int key);

bool addString(const char *key, int value);
int getString(const char *key);

bool remove(int key);
bool removeString(const char *key);

bool set(int key, int value);
bool setString(const char *key, int value);

void clear();


int _convert(const char *key);


private:

int _hash(int key);
int _hash(const char *key);

bool _checkSize(unsigned int nPos);
bool _used(int key, unsigned int nPos);
_item * _get(int key, unsigned int nPos);
void _init();
void _prime();

int prime;
unsigned int nBufferSize;
unsigned int nSize;
unsigned int nPossibleSize;
unsigned int nElementSize;
unsigned int nReadPos;
unsigned int nBucketReadPos;
char *acMem;


};


#endif