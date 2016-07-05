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
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>

#include "../kbshared/typedef.h"
#include "XString.h"


XString::XString ( )
{
  init();
}

XString::~XString ( )
{
  if (ac){
    free(ac);
    ac = 0;
    len = 0;
  }
}

void XString::init ( )
{
	ac = 0;  
	len = 0;
  allocated = 0;
}

bool XString::checkSize(size_t nNewSize)
{    
  len = nNewSize;  // adjust count of memory allocated
  nNewSize++;
	if (ac != 0){
  	if (nNewSize >= allocated) {
			ac = (char *) realloc(ac, nNewSize);  // get some memory
	 		if (ac == 0) return false;  // couldn't get memory   		
      allocated = nNewSize; // adjust count of memory allocated
  	}
    
    return true;
	} else {
	 	ac = (char *) malloc(nNewSize);  // get some memory
 		if (ac == 0) return false;  // couldn't get memory
    allocated = nNewSize; // adjust count of memory allocated
	}
	return true;
}

XString::XString ( XString * s )
{
  init();
  
  size_t n = s->length();
  if (checkSize(n)){
    memcpy((void *) ac, (void *) s->ac, n);
    ac[n] = 0;
  }
}

XString::XString ( const XString & s )
{
  init();
  
  size_t n = s.length();
  if (checkSize(n)){
    memcpy((void *) ac, (void *) s.ac, n);
    ac[n] = 0;
  }
}

XString::XString ( const char * str )
{
  init();
  
  size_t n = strlen(str);
  if (checkSize(n)){
    memcpy((void *) ac, (void *) str, n);
    ac[n] = 0;
  }
}

XString::XString ( char c )
{
  init();
  
  if (checkSize(1)){
    ac[0] = c;
    ac[1] = 0;
  }
}

XString XString::operator= ( const XString & s )
{  
  size_t n = s.length();

  if (checkSize(n)){
    memcpy((void *) ac, (void *) s.ac, n);
    ac[n] = 0;
  }

  return this;
}

size_t XString::length () const
{
  return len;
}
/*
void XString::format ( const char * format, ... )
{  
  va_list args;
  va_start(args, format);  

#ifdef WINDOWS
  if (checkSize(_vscprintf( format, args ))){
    vsprintf(ac, format, args);
  }  
#else
  char *p = 0;
  
  if (checkSize(vasprintf(&p, format, args ))){ // vasprintf = allocate a string large enough to hold the output
    free(p);
    vsprintf(ac, format, args);
  }  
#endif

  va_end(args);
}*/

char XString::at ( size_t i ) const
{
  if (i >= len) return 0;

  return ac[i];
}

char XString::operator[] ( size_t i ) const
{
  if (i >= len) return 0;

  return ac[i];
}

XString XString::left ( size_t _len ) const
{
  if (_len > len) return XString("");

  XString z("");

  if (z.checkSize(_len)){
    memcpy((void *) z.ac, (void *) ac, _len);
    z.ac[_len] = 0;
  }

  return z;
}

XString XString::right ( size_t _len ) const
{
  if (_len > len) return XString("");

  XString z("");

  if (z.checkSize(_len)){
    memcpy((void *) z.ac, (void *) ( ac + (len - _len) ), _len);
    z.ac[_len] = 0;
  }

  return z;
}

XString XString::operator+= ( const XString & str )
{
  XString z("");

  if (z.checkSize(len + str.len)){
    memcpy((void *) z.ac, (void *) ac, len);
    memcpy((void *) (z.ac + len), (void *) str.ac, str.len);
    z.ac[len + str.len] = 0;
  }

  size_t n = z.length();
  if (checkSize(n)){
    memcpy((void *) ac, (void *) z.ac, n);
    ac[n] = 0;
  }

  return this;
}

char XString::upper(char c) const
{
  if (c >= 'a' && c <= 'z') return c - 32; //  Ü->ü ausländische sprachen
  return c;
}

char XString::lower(char c) const
{
  if (c >= 'A' && c <= 'Z') return c + 32; //  Ü->ü ausländische sprachen
  return c;
}

int XString::find ( const XString & s, size_t index, bool cs ) const
{  
  if (index < 0 || index >= len) return -1;

  if (!cs){
    if (s.len > len) return -1;

    size_t t = 0;

    while (true){
      if ( t + s.len > len) return -1;

      const char *s1 = ac + index + t;
      const char *s2 = s.ac;

      size_t g = 0;
      while (true){
        if (s1[0] == 0 || s2[0] == 0){
          if (s.len == g) break;
          return -1;
        }
        if (s.len == g) break;
        if ( lower (s1[0]) != lower (s2[0]) ) break;
        s1++; s2++;
        g++;        
      }

      if (s.len == g) return (int) (t + index);

      t++;
    }
    
    return -1;
  } 

  char *n = strstr ( (ac + index), s.ac );

  if (n){
    return (int) (n - ac);
  }

  return -1;
}

int XString::findRev ( const XString & s, size_t index, bool cs ) const
{
  int k = (int) index;
  if (k >= 0 || k * -1 >= (int) len) return -1;

  if (!cs){
    if (s.len > len) return -1;

    size_t t = 0;

    while (true){
      if ( t - s.len < 0) return -1;

      const char *s1 = ac + len + k - t;
      const char *s2 = s.ac + s.len - 1;

      size_t g = 0;
      while (true){
        if (s1[0] == 0 || s2[0] == 0){
          if (s.len == g) break;
          return -1;
        }
        if (s.len == g) break;
        if ( lower (s1[0]) != lower (s2[0]) ) break;
        s1--; s2--;
        g++;        
      }

      if (s.len == g) return (int) (len - t - s.len);

      t++;
    }    

    return -1;
  } 

  char *n = strstr ( ac, s.ac );
  char *y;


  if (n){
re:
    y = strstr ( n + 1, s.ac );    
    if (y && (int) (y - (ac)) < (int) (len + k)){
      n = y;
      goto re;
    }

    return (int) (n - (ac));
  }

  return -1;
}

bool XString::contains ( const XString & s, bool cs ) const
{  
  return (s.length() > 0) && (find (s, 0, cs ) != -1);
}

XString XString::mid ( size_t index, size_t _len ) const
{
  if (index > len || _len < 0) return XString("");
  if (index < 0) index = 0;
  if (_len == -1 || index + _len >= len) _len = len - index;

  XString z("");

  if (z.checkSize(_len)){
    memcpy((void *) z.ac, (void *) (ac + index), _len);
    z.ac[_len] = 0;
  }

  return z;
}

XString XString::lower () const
{
  XString z("");

  if (z.checkSize(len)){

    memcpy((void *) z.ac, (void *) ac, len);
    z.ac[len] = 0;

    size_t t = 0;
    while (t < z.len){
      char *s1 = z.ac + t;
      s1[0] = lower(s1[0]);
      t++;
    }
  }

  return z;
}

XString XString::upper () const
{
  XString z("");

  if (z.checkSize(len)){

    memcpy((void *) z.ac, (void *) ac, len);
    z.ac[len] = 0;

    size_t t = 0;
    while (t < z.len){
      char *s1 = z.ac + t;
      s1[0] = upper(s1[0]);
      t++;
    }
  }

  return z;}

XString XString::stripWhiteSpace () const
{
  XString z("");

  if (z.checkSize(len)){

    size_t t = 0;
    size_t t2 = 0;
    size_t l = 0;

    while (t < len){

      char *s1 = ac + t;
      char *s2 = z.ac + t2;

      switch(s1[0]){
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
        case 32:
          break;
        default:
          s2[0] = s1[0];
          l++;
          t2++;
          break;
      }
      
      t++;
    }

    z.ac[l] = 0;
    z.len = l;
  }

  return z;

}

XString XString::insert ( const XString & str, size_t index )
{
  XString z("");

  if (z.checkSize(str.len + len)){
    memcpy((void *) (z.ac + index), (void *) str.ac, str.len);
    memcpy((void *) (z.ac + index + str.len), (void *) (ac + index), len - index);
    memcpy((void *) (z.ac), (void *) ac, index);
    z.ac[str.len + len] = 0;
  }

  return z;
}

XString XString::append ( const XString & str )
{
  XString z("");

  if (z.checkSize(len + str.len)){
    memcpy((void *) z.ac, (void *) ac, len);
    memcpy((void *) (z.ac + len), (void *) str.ac, str.len);
    z.ac[len + str.len] = 0;
  }

  return z;
}

/*
XString XString::appendNull()
{
  XString z("");

  if (z.checkSize(len + 1)){
    memcpy((void *) z.ac, (void *) ac, len);
    const char *str = 0;
    //memcpy((void *) (z.ac + len), (void *) str, 1);
    z.ac[len] = 0;
  }

  return z;
}*/

XString XString::prepend ( const XString & str )
{
  XString z("");

  if (z.checkSize(str.len + len)){
    memcpy((void *) z.ac, (void *) str.ac, str.len);
    memcpy((void *) (z.ac + str.len), (void *) ac, len);
    z.ac[str.len + len] = 0;
  }

  return z;
}

XString XString::replace ( const XString & before, const XString & after, bool cs )
{
  static XString z("");

  int t = find(before, 0, cs);
  size_t n = 0;
  size_t m = 0; // len

  if (z.checkSize(len)){
    if (t >= 0){
re:
      z.checkSize((t - n) + after.len + (z.len));

      memcpy((void *) (z.ac + m), (void *) (ac + n), t - n);
      m += t - n;

      n = t + before.len;

      memcpy((void *) (z.ac + m), (void *)( after.ac), after.len);
      m += after.len;      
     
      t = find(before, n, cs);      

      if (t >= 0){
        goto re;
      } else {
        memcpy((void *) (z.ac + m), (void *) (ac + n), len - n);
        m += len - n;
        z.ac[m] = 0;
        z.len = m;
      }

    } else {
      memcpy((void *) z.ac, (void *) ac, len);
      z.ac[len] = 0;    
      z.len = len;
    }
  }

  return z;
}

const char * XString::ascii () const
{
  return ac;
}

int XString::toint () const
{
  return atoi(ac);
}

bool XString::startsWith ( const XString & s, bool cs ) const
{
  if (!cs){
    if (s.len > len) return false;

    while (true){

      const char *s1 = ac;
      const char *s2 = s.ac;

      size_t g = 0;
      while (true){
        if (s1[0] == 0 || s2[0] == 0){
          if (s.len == g) break;
          return false;
        }
        if (s.len == g) break;
        if ( lower (s1[0]) != lower (s2[0]) ) break;
        s1++; s2++;
        g++;        
      }

      if (s.len == g) return true;
      return false;
      
    }
    
    return false;
  } 

  char *n = strstr ( (ac), s.ac );

  if (n){
    return (int) (n - ac) == 0;
  }

  return false;
}

bool XString::endsWith ( const XString & s, bool cs ) const
{
  if (!cs){
    if (s.len > len) false;

    while (true){

      const char *s1 = ac + len - 1;
      const char *s2 = s.ac + s.len - 1;

      size_t g = 0;
      while (true){
        if (s1[0] == 0 || s2[0] == 0){
          if (s.len == g) break;
          return false;
        }
        if (s.len == g) break;
        if ( lower (s1[0]) != lower (s2[0]) ) break;
        s1--; s2--;
        g++;        
      }

      if (s.len == g) return true;

      return false;
    }    

    return false;
  } 

  char *n = strstr ( ac, s.ac );
  char *y;


  if (n){
re:
    y = strstr ( n + 1, s.ac );    
    if (y && (int) (y - (ac)) < (int) (len)){
      n = y;
      goto re;
    }

    return (int) (n - (ac)) == len - s.len;
  }

  return false;
}

bool XString::isNull () const
{
  return ac == 0;
}

bool XString::isEmpty () const
{
  return ac == 0 || len == 0;
}

void XString::squeeze ()
{
  if (ac != 0){
  	if (allocated > len) {
			ac = (char *) realloc(ac, len);  // get some memory
	 		if (ac == 0) return;  // couldn't get memory   		
      allocated = len; // adjust count of memory allocated
  	}
  }    
}

bool operator== ( const XString & s1, const XString & s2 )
{

  return strcmp(s1.ascii(), s2.ascii()) == 0;
}

bool operator== ( const XString & s1, const char * s2 )
{
  if (s2 == 0){
    if (s1.ascii() == 0) return true;
    return false;
  }
  return strcmp(s1.ascii(), s2) == 0;
}

bool operator== ( const char * s1, const XString & s2 )
{
  if (s1 == 0){
    if (s2.ascii() == 0) return true;
    return false;
  }

  return strcmp(s1, s2.ascii()) == 0;
}

bool operator!= ( const XString & s1, const XString & s2 )
{

  return strcmp(s1.ascii(), s2.ascii()) != 0;
}

bool operator!= ( const XString & s1, const char * s2 )
{
    if (s2 == 0){
    if (s1.ascii() != 0) return true;
    return false;
  }

  return strcmp(s1.ascii(), s2) != 0;
}

bool operator!= ( const char * s1, const XString & s2 )
{
    if (s1 == 0){
    if (s2.ascii() != 0) return true;
    return false;
  }
 
  return strcmp(s1, s2.ascii()) != 0;
}


XString operator+ ( const XString & s1, const XString & s2 )
{
  XString z(s1);

  if (z.checkSize(s1.length() + s2.length() )){
    memcpy((void *) z.ascii(), (void *) s1.ascii(), s1.length());
    memcpy((void *) (z.ascii() + s1.length()), (void *) s2.ascii(), s2.length());
    char *ac = (char *) z.ascii();
    ac[s1.length() + s2.length()] = 0;
  }

  return z;
}

XString operator+ ( const XString & s1, const char * s2 )
{
  XString z(s1);

  int n = strlen(s2);
  if (z.checkSize(s1.length() + n )){
    memcpy((void *) z.ascii(), (void *) s1.ascii(), s1.length());
    memcpy((void *) (z.ascii() + s1.length()), (void *) s2, n);
    char *ac = (char *) z.ascii();
    ac[s1.length() + n] = 0;
  }

  return z;
}

XString operator+ ( const char * s1, const XString & s2 )
{
  XString z(s1);

  int n = strlen(s1);
  if (z.checkSize(n + s2.length() )){
    memcpy((void *) z.ascii(), (void *) s1, n);
    memcpy((void *) (z.ascii() + n), (void *) s2.ascii(), s2.length());
    char *ac = (char *) z.ascii();
    ac[n + s2.length()] = 0;
  }

  return z;
}
/*
void XString::test()
{

 

  XString a = "test it";
  
  XString c(a);
  XString b = a;    
  XString d;    

  d = a;

  d.format("hello %d %s", 99, "er");


  b = a.ascii();
  a = d.right(5);
  a = d.left(5);

  b = a.at(1);
  b = a[2];

  b += d;
  b += " BERND";
  b = b.append(" NADJA");
  b = b.prepend("JULIE ");

  b = d.mid(3);
  b = d.mid(3, 2);

  XString e = " te oi te jj ";
  int z = e.find("TE", 0, false);

//  z = e.findRev("TE", -1, false);

  bool bb = e.contains("TE", true);
 

  XString h = e.upper();
  h = e.lower();
  h = e.stripWhiteSpace();

  bb = e.startsWith(" T5E", false);
  bb = e.endsWith("oii ", false);

  //int t = e.find("te", 9, false);
  h = e.replace("te", "hu", false);

  if (h == "test"){

  }

  int i = 0; 
  i++;
}*/

int XString::count ( const XString & s, bool cs ) const
{  
  int i = 0;
  int n = -1;
  while ((n = find (s, n + 1, cs)) != -1) i++;
  return i;
}
