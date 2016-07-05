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


#ifndef UTILITY_H
#define UTILITY_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#include "XString.h"
#include "../kbshared/typedef.h"
#include "../kbshared/console.h"


#include <ctype.h>



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
		console::print(str[i]);
		console::print("/");
	}
}

static bool readSourceFile(char **acText, const char *acFile, textbuffer *myTextbuffer)
{
  FILE *fh;// = 0;
  if ((fh = fopen(acFile, "rb")) > 0){
    
    fseek( fh, 0, SEEK_END );     
    size_t n = ftell( fh );        
    

    fseek( fh, 0, SEEK_SET );    

    *acText = myTextbuffer->get(n + 1);


    fread(*acText, 1, n, fh);

    (*acText)[n] = 0;

    fclose(fh);
    return true;
  }

  *acText = "";

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
 //  alert mit nullpointer, kde-crash window oder besser eigenes crash-window???
	return 0;
}
*/

inline static int my_strnicmp(const char *c, const char *c2, int n)
{ 
#ifdef LINUX // HIDE
  return strncasecmp(c, c2, n); // HIDE
#endif // HIDE
#ifdef MAC // HIDE
  return strncasecmp(c, c2, n); // HIDE
#endif // HIDE
#ifdef WINDOWS // HIDE
  return strnicmp(c, c2, n);  // HIDE
#endif // HIDE
  // UNHIDE return strncasecmp(c, c2, n);
  return 0;
}

inline static int my_stricmp(const char *c, const char *c2)
{
#ifdef LINUX // HIDE
  return strcasecmp(c, c2); // HIDE
#endif // HIDE
#ifdef MAC // HIDE
  return strcasecmp(c, c2); // HIDE
#endif // HIDE
#ifdef WINDOWS // HIDE
  return stricmp(c, c2);  // HIDE
#endif // HIDE
  // UNHIDE return strcasecmp(c, c2);
  return 0;
}


};





#endif
