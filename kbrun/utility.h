/*
***************************************************************************
Copyright (C) 2000-2008 KBasic Software: www.kbasic.com. All rights reserved.
Source codes are copyrighted by Bernd Noetscher 2000-2008.

You may use this source codes under the terms of the GNU Public License (Version 3) 
as published by the Free Software Foundation. 

If you are interested in using the source codes for other licenses or 
commercial development, you must buy commercial licenses from KBasic Software.
***************************************************************************
*/


#ifndef UTILITY_H
#define UTILITY_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <qfile.h> 
#include <ctype.h>

#include "../kbshared/typedef.h"
#include "../kbshared/console.h"

class textbuffer {
public:
	textbuffer();
	~textbuffer();


// ****************************
// * bool checkSize(int nAddedSize)
// *
// * description:
// * checks if there's enough memory in a dynamic array to add an int nSize to
// * if not it gets more memory
// *
// * parameter:
// * int nSize = added size to check
// *
// * return:
// * true, if no error occurs
// * false, if couldn't get more memory to extend array
// ****************************
inline bool checkSize(int nSize)
{

	if (acMem != 0){
  	if (nSize > nMem){

  	 	static char *acMemNew;
     acMemNew = (char *) realloc(acMem, nSize);  // get some memory

 			if (acMemNew == 0) return false;  // couldn't get memory
 			acMem = acMemNew;
   		nMem = nSize;  // adjust count of memory allocated
      return true;
  	}
	} else {
  	//if (nSize < 10240) nSize = 10240;// at least 10240kb big, needed for malloc

	 	acMem = (char *) malloc(nSize);  // get some memory
 		if (acMem == 0) return false;  // couldn't get memory
 		nMem = nSize;  // adjust count of memory allocated
    return true;
	}
	return true;
}

char *get(const char *acValue)
{
	return get(acValue, strlen(acValue));
}

char *get(const char *acValue, int nLen)
{
	if (checkSize(nLen + sizeof(char)) == false){ return 0; }

  memcpy((acMem), acValue, nLen);
  acMem[nLen] = 0;

	return acMem;
}

char *get(int nLen)
{
	if (checkSize(nLen + sizeof(char)) == false){ return 0; }

  acMem[0] = 0;
  acMem[nLen] = 0;

	return acMem;
}

char *getMem()
{
	return acMem;
}

int getAllocatedSize()
{
	return nMem;
}


private:


char *acMem;
int nMem;

};


extern char acText[1024 * 100];

class utility {
public:
	utility();
	~utility();

public:


static char *toString(int nInteger)
{
	sprintf(acText, "%d", nInteger);
	return acText;
}

static char *toString2(int nInteger)
{
	sprintf(acText, "%d", nInteger);
	return acText;
}

static char *con(const char *acLeft, const char *acRight, bool b = true)
{
  sprintf(acText, "%s%s%s", acLeft, acRight,  b ? "\n" : "");
	return acText;
}

static char *con(QString sLeft, QString sRight, QString s2)
{
  static QByteArray ba;
  static QString s;

  s = sLeft + sRight + s2;
  ba = s.toLocal8Bit();
  return ba.data();
}

static char *con(int nLeft, const char *acRight)
{
	sprintf(acText, "%d%s\n", nLeft, acRight);
	return acText;
}

static char *con(const char *acLeft, int nRight)
{
	sprintf(acText, "%s (%d)", acLeft, nRight);
	return acText;
}

static char *con(const char *acLeft, double dRight, const char *acRight2)
{
	sprintf(acText, "%s%.6f%s", acLeft, dRight, acRight2);
	return acText;
}

static char *con(const char *acLeft, const char *acRight, const char *acRight2)
{
	sprintf(acText, "%s %s %s\n", acLeft, acRight, acRight2);
	return acText;
}

static char *uniqueName(const char *acLeft, const char *acRight, const char *acRight2)
{
	sprintf(acText, "%s.%s.%s", (acLeft == 0 ? "" : acLeft), (acRight == 0 ? "" : acRight), acRight2);
	return acText;
}

static char *con(const char *ac1, const char *ac2, const char *ac3, const char *ac4, const char *acRight2 = "")
{
	sprintf(acText, "%s %s %s %s %s\n", ac1, ac2, ac3, ac4, acRight2);
	return acText;
}

static void printString(const char *str, int len)
{
	for (signed int i = 0; i < len; i++){
		CONSOLE print(str[i]);
		CONSOLE print("/");
	}
}

static bool readSourceFile(char **acText, const char *acFile, textbuffer *myTextbuffer)
{
  QFile f(acFile);
	
  if (f.open(QFile::ReadOnly )){
   	*acText = myTextbuffer->get(f.size() + 1);
		f.read(*acText, f.size()); 
		(*acText)[f.size()] = 0;
		f.close();
		return true;
	}

	return false;
}

static char *eatUTF16DOM(char *acBuffer)
{
  int n = 0;
  if (acBuffer[0] == -17 && acBuffer[1] == -69 && acBuffer[2] == -65){
    n += 3;
  }
  return acBuffer + n;
}

// convert uppercase letters in a string to uppercase
static char *toupper22(char *acString)
{
	for(unsigned int i = 0; i < strlen(acString); i++) acString[i] = toupper(acString[i]);

  return acString;
}

static char *ident(const char *ac1, const char *ac2, const char *ac3)
{
	sprintf(acText, "%s.%s.%s", ac1, ac2, ac3);
	return acText;
}

static char *ident(const char *ac1, const char *ac2)
{
	sprintf(acText, "%s.%s", ac1, ac2);
	return acText;
}

static char *uniqueName()
{
	static int n = 0;

	sprintf(acText, "kbVarRefImplicit_%d", n++);
	return acText;
}

/*
static void *crashHandler()
{
 
	return 0;
}
*/

inline static int my_strnicmp(const char *c, const char *c2, int n)
{ 
#ifdef LINUX
  return strncasecmp(c, c2, n); // LINUX // UNHIDE
#endif
#ifdef MAC
  return strncasecmp(c, c2, n); // LINUX // HIDE
#endif
#ifdef WINDOWS
  return strnicmp(c, c2, n); // HIDE
#endif
  return 0;
}

inline static int my_stricmp(const char *c, const char *c2)
{
#ifdef LINUX
  return strcasecmp(c, c2); // LINUX // UNHIDE
#endif
#ifdef MAC
  return strcasecmp(c, c2); // LINUX // HIDE
#endif
#ifdef WINDOWS
  return stricmp(c, c2); // HIDE
#endif
  return 0;
}


};



#endif
