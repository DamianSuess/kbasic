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

#ifndef XSTRING_H
#define XSTRING_H

#ifndef WINDOWS
#include <ctype.h>
#endif

#ifndef size_t
#define size_t unsigned int
#endif


class XString
{
public:

  XString ( );
  XString ( XString * s );
  XString ( const XString & s );
  XString ( const char * str );
  XString ( char str );

  ~XString ( );

  size_t length () const;

  int count ( const XString & str, bool cs = true ) const;

  XString left ( size_t len ) const;
  XString right ( size_t len ) const;
  XString mid ( size_t index, size_t len = 0xffffffff ) const;

  const char * ascii () const;
  char at ( size_t i ) const;

  int toint () const;

  char operator[] ( size_t i ) const;
  XString operator= ( const XString & s );
  XString operator+= ( const XString & str );

  XString insert ( const XString & str, size_t index = 0 );
  XString append ( const XString & str );
  XString prepend ( const XString & str );


  int find ( const XString & str, size_t index = 0, bool cs = true ) const;
  int findRev ( const XString & str, size_t index = -1, bool cs = true ) const;
  bool contains ( const XString & str, bool cs = true ) const;
  bool startsWith ( const XString & s, bool cs = true ) const;
  bool endsWith ( const XString & s, bool cs = true ) const;

  XString lower () const;
  XString upper () const;
  XString stripWhiteSpace () const;
  
  XString replace ( const XString & before, const XString & after, bool cs = true );
  
  bool isNull () const;
  bool isEmpty () const;

  void squeeze ();

  void test ( );
  bool checkSize(size_t nNewSize);

private:

  char lower(char c) const;
  char upper(char c) const;
 
  void init ( );




  char *ac;
  size_t len;    // start length at some value
  size_t allocated;    // start length at some value


};


bool operator== ( const XString & s1, const XString & s2 );
bool operator== ( const XString & s1, const char * s2 );
bool operator== ( const char * s1, const XString & s2 );

bool operator!= ( const XString & s1, const XString & s2 );
bool operator!= ( const XString & s1, const char * s2 );
bool operator!= ( const char * s1, const XString & s2 );

XString operator+ ( const XString & s1, const XString & s2 );
XString operator+ ( const XString & s1, const char * s2 );
XString operator+ ( const char * s1, const XString & s2 );



#endif