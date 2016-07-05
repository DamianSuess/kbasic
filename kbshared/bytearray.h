/*
***************************************************************************
Copyright (C) 2000-2008 KBasic Software (Bernd Noetscher, Boseweg 9, 60529 Frankfurt / Germany).  All rights reserved.

bytearray.h
---------------------------------------------------------------------------
19.02.2004 - new header for this file (BN)
***************************************************************************
*/





#ifndef BYTEARRAY_H
#define BYTEARRAY_H

#include <string.h>
#include <stdlib.h>


#include "typedef.h"


#ifdef IDE
#else



const char bytearray__CURRENTPOS = -1;

// error codes
const char bytearray__UNDEFINED = 0;
const char bytearray__STACK_UNDERFLOW = bytearray__UNDEFINED + 1;
const char bytearray__STACK_OVERFLOW = bytearray__STACK_UNDERFLOW + 1;
const char bytearray__NOT_ENOUGH_MEMORY = bytearray__STACK_OVERFLOW + 1;

class bytearray {
public:
  bytearray();
  ~bytearray();

void wr_Char(unsigned char cValue)
{
  // // write();

	if (checkSize(sizeof(cValue)) == false){ bytearrayError(error(bytearray__NOT_ENOUGH_MEMORY)); return ;}

  acMem[nMemOffset] = cValue;
  nMemOffset += sizeof(cValue);

	return ;
}

void wr_Byte(t_byte c)
{
	return wr_Char(c);
}

void wr_Boolean(t_boolean bValue)
{
	return wr_Char(bValue);
}

void wr_Currency(t_currency d)
{
  // // write();
	if (checkSize(sizeof(d)) == false){ bytearrayError(error(bytearray__NOT_ENOUGH_MEMORY)); return ;}

   *((t_currency *)(acMem + nMemOffset)) = d;
	
  nMemOffset += sizeof(d);

	return ;
}

void wr_Date(t_date d)
{
  // // write();
	if (checkSize(sizeof(d)) == false){ bytearrayError(error(bytearray__NOT_ENOUGH_MEMORY)); return ;}

  *((t_date *)(acMem + nMemOffset)) = d;
	
  nMemOffset += sizeof(d);

	return ;
}

void wr_Variant(t_variant d)
{
  // write();
	if (checkSize(sizeof(d)) == false){ bytearrayError(error(bytearray__NOT_ENOUGH_MEMORY)); return ;}

  *((t_variant *)(acMem + nMemOffset)) = d;
	
  nMemOffset += sizeof(d);

	return ;
}

void wr_Time(t_date d)
{
  // write();
	if (checkSize(sizeof(d)) == false){ bytearrayError(error(bytearray__NOT_ENOUGH_MEMORY)); return ;}

  *((t_date *)(acMem + nMemOffset)) = d;
	
  nMemOffset += sizeof(d);

	return ;
}

void wr_Integer(t_integer nValue)
{
  // write();
	if (checkSize(sizeof(nValue)) == false){ bytearrayError(error(bytearray__NOT_ENOUGH_MEMORY)); return ;}

  *((t_integer *)(acMem + nMemOffset)) = nValue;

  nMemOffset += sizeof(nValue);

	return ;
}

void wr_Long(t_long lValue)
{
  // write();
	if (checkSize(sizeof(lValue)) == false){ bytearrayError(error(bytearray__NOT_ENOUGH_MEMORY)); return ;}

  *((t_long *)(acMem + nMemOffset)) = lValue;

  nMemOffset += sizeof(lValue);

	return ;
}

void wr_Single(t_single fValue)
{
  // write();
	if (checkSize(sizeof(fValue)) == false){ bytearrayError(error(bytearray__NOT_ENOUGH_MEMORY)); return ;}

  *((t_single *)(acMem + nMemOffset)) = fValue;

  nMemOffset += sizeof(fValue);

	return ;
}

void wr_Double(t_double dValue)
{
  // write();
	if (checkSize(sizeof(dValue)) == false){ bytearrayError(error(bytearray__NOT_ENOUGH_MEMORY)); return ;}

  *((t_double *)(acMem + nMemOffset)) = dValue;

  nMemOffset += sizeof(dValue);

	return ;
}
/*
void wr_Character(t_character d)
{
  // write();
	if (checkSize(sizeof(d)) == false){ bytearrayError(error(bytearray__NOT_ENOUGH_MEMORY)); return ;}

  *((t_character *)(acMem + nMemOffset)) = d;
	//memcpy(acMem + nMemOffset, &d, sizeof(d)); 
  nMemOffset += sizeof(d);

	return ;
}
*/
/*
void wr_Int16(t_int16 d)
{
  // write();
	if (checkSize(sizeof(d)) == false){ bytearrayError(error(bytearray__NOT_ENOUGH_MEMORY)); return ;}

  *((t_int16 *)(acMem + nMemOffset)) = d;

  nMemOffset += sizeof(d);

	return ;
}

void wr_Int32(t_int32 d)
{
  // write();
	if (checkSize(sizeof(d)) == false){ bytearrayError(error(bytearray__NOT_ENOUGH_MEMORY)); return ;}

  *((t_int32 *)(acMem + nMemOffset)) = d;

  nMemOffset += sizeof(d);

	return ;
}

void wr_Int64(t_int64 d)
{
  // write();
	if (checkSize(sizeof(d)) == false){ bytearrayError(error(bytearray__NOT_ENOUGH_MEMORY)); return ;}

  *((t_int64 *)(acMem + nMemOffset)) = d;

  nMemOffset += sizeof(d);

	return ;
}

void wr_UInt16(t_uint16 d)
{
  // write();
	if (checkSize(sizeof(d)) == false){ bytearrayError(error(bytearray__NOT_ENOUGH_MEMORY)); return ;}

  *((t_uint16 *)(acMem + nMemOffset)) = d;

  nMemOffset += sizeof(d);

	return ;
}

void wr_UInt32(t_uint32 d)
{
  // write();
	if (checkSize(sizeof(d)) == false){ bytearrayError(error(bytearray__NOT_ENOUGH_MEMORY)); return ;}

  *((t_uint32 *)(acMem + nMemOffset)) = d;

  nMemOffset += sizeof(d);

	return ;
}

void wr_UInt64(t_uint64 d)
{
  // write();
	if (checkSize(sizeof(d)) == false){ bytearrayError(error(bytearray__NOT_ENOUGH_MEMORY)); return ;}

  *((t_uint64 *)(acMem + nMemOffset)) = d;

  nMemOffset += sizeof(d);

	return ;
}
*/
void wr_Short(t_short d)
{
  // write();
	if (checkSize(sizeof(d)) == false){ bytearrayError(error(bytearray__NOT_ENOUGH_MEMORY)); return ;}

  *((t_short *)(acMem + nMemOffset)) = d;

  nMemOffset += sizeof(d);

	return ;
}

void wr_Token(t_token d)
{
  // write();
	if (checkSize(sizeof(d)) == false){ bytearrayError(error(bytearray__NOT_ENOUGH_MEMORY)); return ;}

  *((t_token *)(acMem + nMemOffset)) = d;

  nMemOffset += sizeof(d);

	return ;
}

void wr_PCode(t_pcode d);


void wr_CString(t_cstring acValue)
{
  // write();
	return wr_CString(acValue, strlen(acValue));
}

void wr_CString(t_cstring acValue, int nLen)
{
  // write();
	if (checkSize(sizeof(t_integer) + nLen + sizeof(char)) == false){ bytearrayError(error(bytearray__NOT_ENOUGH_MEMORY)); return ;}

#ifdef RUN
  if (!bStack){ 
     *((t_integer *)(acMem + nMemOffset)) = nLen; nMemOffset += sizeof(t_integer);
  }
#else
     *((t_integer *)(acMem + nMemOffset)) = nLen; nMemOffset += sizeof(t_integer);
#endif

	if (nLen > 0){
		memcpy((acMem + nMemOffset), acValue, nLen); nMemOffset += nLen;
	}
  acMem[nMemOffset] = 0;

  nMemOffset += sizeof(char);

	return ;
}

void wr_CString2(t_cstring acValue, int nLen)
{
  // write();
	if (checkSize(nLen) == false){ bytearrayError(error(bytearray__NOT_ENOUGH_MEMORY)); return ;}

	if (nLen > 0){
		memcpy((acMem + nMemOffset), acValue, nLen); nMemOffset += nLen;
	}

	return ;
}

/*
void wr_CString(t_cstring acValue, int nLen)
{
  // write();
	if (checkSize(sizeof(t_integer) + nLen + sizeof(char)) == false){ bytearrayError(error(bytearray__NOT_ENOUGH_MEMORY)); return ;}

  if (!bStack){ 
    *((t_integer *)(acMem + nMemOffset)) = nLen; nMemOffset += sizeof(t_integer);
  }
	if (nLen > 0){
		memcpy((acMem + nMemOffset), acValue, nLen); nMemOffset += nLen;
	}
  acMem[nMemOffset] = 0;

  nMemOffset += sizeof(char);

	return ;
}

void wr_CString(t_cstring acValue)
{
  // write();
	return wr_CString(acValue, strlen(acValue));
}
*/
void wr_Struct(int nSizeOf, void *s)
{
  // write();
	register int nLen = nSizeOf;
	if (checkSize(nLen) == false){ bytearrayError(error(bytearray__NOT_ENOUGH_MEMORY)); return ;}

	if (nLen > 0){
		memcpy((acMem + nMemOffset), s, nLen); nMemOffset += nLen;
	}
	
	return ;
}

unsigned char rd_Char(int nPos = -1)
{
  // read();
  if (nPos != -1) nMemOffset = nPos;

	static /**/ unsigned char c;

#ifdef RUN
  if (bStack){
	  if (nMemOffset - sizeof(c) < 0){ bytearrayError(error(bytearray__STACK_UNDERFLOW)); return 0; }
	  nMemOffset -= sizeof(c);
    c = acMem[nMemOffset];
    return c;
  } else {
#endif
  	if (nMemOffset + sizeof(c) > nMem){ bytearrayError(error(bytearray__STACK_OVERFLOW)); return 0; }
    c = acMem[nMemOffset];
	  nMemOffset += sizeof(c);
    return c;
#ifdef RUN
  }
#endif

	return c;
}

t_currency rd_Currency(int nPos = -1)
{
  // read();
	if (nPos != -1) nMemOffset = nPos;

	static /**/ t_currency f;

#ifdef RUN
  if (bStack){
	  if (nMemOffset - sizeof(f) < 0){ bytearrayError(error(bytearray__STACK_UNDERFLOW)); return f; }
	  nMemOffset -= sizeof(f);
    return *(t_currency *) (acMem + nMemOffset);

  } else {
#endif
  	if (nMemOffset + sizeof(f) > nMem){ bytearrayError(error(bytearray__STACK_OVERFLOW)); return f; }
    
    f = *(t_currency *) (acMem + nMemOffset);
	  nMemOffset += sizeof(f);
    return f;
#ifdef RUN
  }
#endif

	return f;
}

t_date rd_Date(int nPos = -1)
{
  // // read();
	if (nPos != -1) nMemOffset = nPos;

	static /**/ t_date f;

#ifdef RUN
  if (bStack){
	  if (nMemOffset - sizeof(f) < 0){ bytearrayError(error(bytearray__STACK_UNDERFLOW)); return f; }
	  nMemOffset -= sizeof(f);
    memcpy(&f, (acMem + nMemOffset), sizeof(f));
    return *(t_date *) (acMem + nMemOffset);
    //return f;
  } else {
#endif
  	if (nMemOffset + sizeof(f) > nMem){ bytearrayError(error(bytearray__STACK_OVERFLOW)); return f; }
    //memcpy(&f, (acMem + nMemOffset), sizeof(f));
    f = *(t_date *) (acMem + nMemOffset);
	  nMemOffset += sizeof(f);
    return f;
#ifdef RUN
  }
#endif

	return f;
}

t_variant rd_Variant(int nPos = -1)
{
  // read();
	if (nPos != -1) nMemOffset = nPos;

	static /**/ t_variant f;

#ifdef RUN
  if (bStack){
	  if (nMemOffset - sizeof(f) < 0){ bytearrayError(error(bytearray__STACK_UNDERFLOW)); return f; }
	  nMemOffset -= sizeof(f);
    
    return *(t_variant *) (acMem + nMemOffset);
    
  } else {
#endif
  	if (nMemOffset + sizeof(f) > nMem){ bytearrayError(error(bytearray__STACK_OVERFLOW)); return f; }
    
    f = *(t_variant *) (acMem + nMemOffset);
	  nMemOffset += sizeof(f);
    return f;
#ifdef RUN
  }
#endif

  return f;
	
}

t_date rd_Time(int nPos = -1)
{
  // read();
	if (nPos != -1) nMemOffset = nPos;

	static /**/ t_date f;

#ifdef RUN
  if (bStack){
	  if (nMemOffset - sizeof(f) < 0){ bytearrayError(error(bytearray__STACK_UNDERFLOW)); return f; }
	  nMemOffset -= sizeof(f);
    
    return *(t_date *) (acMem + nMemOffset);
    
  } else {
#endif
  	if (nMemOffset + sizeof(f) > nMem){ bytearrayError(error(bytearray__STACK_OVERFLOW)); return f; }
    
    f = *(t_date *) (acMem + nMemOffset);
	  nMemOffset += sizeof(f);
    return f;
#ifdef RUN
  }
#endif

	return f;
}
/*
t_character rd_Character(int nPos = -1)
{
  // read();
	if (nPos != -1) nMemOffset = nPos;

	static / ** / t_character f;


  if (bStack){
	  if (nMemOffset - sizeof(f) < 0){ bytearrayError(error(bytearray__STACK_UNDERFLOW)); return f; }
	  nMemOffset -= sizeof(f);
    return *(t_character *) (acMem + nMemOffset);
    //memcpy(&f, (acMem + nMemOffset), sizeof(f));
    //return f;
  } else {
  	if (nMemOffset + sizeof(f) > nMem){ bytearrayError(error(bytearray__STACK_OVERFLOW)); return f; }
    //memcpy(&f, (acMem + nMemOffset), sizeof(f));
    f = *(t_character *) (acMem + nMemOffset);
	  nMemOffset += sizeof(f);
    return f;
#ifdef RUN
  }
#endif

	return f;
}
*/
t_boolean rd_Boolean(int nPos = -1)
{
  // read();
	return !(rd_Char(nPos) == 0);
}

t_byte rd_Byte(int nPos = -1)
{
	return rd_Char(nPos);
}

t_cstring rd_CString(int nPos = -1)
{
  // read();
	if (nPos != -1) nMemOffset = nPos;

	static /**/ int nLen;
	static /**/ char *s;
  		
#ifdef RUN
  if (bStack){
    nLen = 2;
		
		do { // #Salsa#@   #=0    @=bytecode  read-->right2left
			if (nMemOffset - nLen < 0){ bytearrayError(error(bytearray__STACK_UNDERFLOW)); return 0; }
		} while(acMem[nMemOffset - nLen++] != 0);
    nMemOffset-= nLen - 2;
	}	
#endif

#ifdef RUN
  if (bStack){
    s = (char *) (acMem + nMemOffset);

    nMemOffset--;
    return s;
  } else {
#endif

    nLen = (*((t_integer *)(acMem + nMemOffset))) + 1;
	  nMemOffset += sizeof(t_integer);

    //if (nMemOffset + nLen > nMem){ bytearrayError(error(bytearray__STACK_OVERFLOW)); return 0; }

    s = (char *) (acMem + nMemOffset);
	  
    //int k = strlen(s) + 1;//nLen;
    nMemOffset += nLen;
    return s;
#ifdef RUN
  }
#endif

	return s;
}

t_single rd_Single(int nPos = -1)
{
  // read();
	if (nPos != -1) nMemOffset = nPos;

	static /**/ t_single f;

#ifdef RUN
  if (bStack){
	  if (nMemOffset - sizeof(f) < 0){ bytearrayError(error(bytearray__STACK_UNDERFLOW)); return f; }
	  nMemOffset -= sizeof(f);
    return *((t_single *)(acMem + nMemOffset));    
  } else {
#endif
  	if (nMemOffset + sizeof(f) > nMem){ bytearrayError(error(bytearray__STACK_OVERFLOW)); return f; }
    f = *((t_single *)(acMem + nMemOffset));
	  nMemOffset += sizeof(f);
    return f;
#ifdef RUN
  }
#endif

	return f;
}

t_double rd_Double(int nPos = -1)
{
  // read();
	if (nPos != -1) nMemOffset = nPos;

	static /**/ t_double f;

#ifdef RUN
  //  zwei bytearray klassen ohne if(bstack)....
  if (bStack){
	  if (nMemOffset - sizeof(f) < 0){ bytearrayError(error(bytearray__STACK_UNDERFLOW)); return f; }
	  nMemOffset -= sizeof(f);
    return *((t_double *)(acMem + nMemOffset));    
  } else {
#endif
  	if (nMemOffset + sizeof(f) > nMem){ bytearrayError(error(bytearray__STACK_OVERFLOW)); return f; }
    f = *((t_double *)(acMem + nMemOffset));
	  nMemOffset += sizeof(f);
    return f;
#ifdef RUN
  }
#endif


	return f;
}

t_integer rd_Integer(int nPos = -1)
{
  // read();
	if (nPos != -1) nMemOffset = nPos;

	static /**/ t_integer f;

#ifdef RUN
  if (bStack){
	  if (nMemOffset - sizeof(f) < 0){ bytearrayError(error(bytearray__STACK_UNDERFLOW)); return f; }
	  nMemOffset -= sizeof(f);
    return *((t_integer *)(acMem + nMemOffset));    
  } else {
#endif
  	if (nMemOffset + sizeof(f) > nMem){ bytearrayError(error(bytearray__STACK_OVERFLOW)); return f; }
    f = *((t_integer *)(acMem + nMemOffset));
	  nMemOffset += sizeof(f);
    return f;
#ifdef RUN
  }
#endif


	return f;
}

t_long rd_Long(int nPos = -1)
{
  // read();
	if (nPos != -1) nMemOffset = nPos;

	static /**/ t_long f;

#ifdef RUN  
  if (bStack){
	  if (nMemOffset - sizeof(f) < 0){ bytearrayError(error(bytearray__STACK_UNDERFLOW)); return f; }
	  nMemOffset -= sizeof(f);
    return *((t_long *)(acMem + nMemOffset));    
  } else {
#endif
  	if (nMemOffset + sizeof(f) > nMem){ bytearrayError(error(bytearray__STACK_OVERFLOW)); return f; }
    f = *((t_long *)(acMem + nMemOffset));
	  nMemOffset += sizeof(f);
    return f;
#ifdef RUN
  }
#endif

	return f;
}

t_short rd_Short(int nPos = -1)
{
  // read();
	if (nPos != -1) nMemOffset = nPos;

	static /**/ t_short f;

#ifdef RUN
  if (bStack){
	  if (nMemOffset - sizeof(f) < 0){ bytearrayError(error(bytearray__STACK_UNDERFLOW)); return f; }
	  nMemOffset -= sizeof(f);
    return *((t_short *)(acMem + nMemOffset));    
  } else {
#endif
  	if (nMemOffset + sizeof(f) > nMem){ bytearrayError(error(bytearray__STACK_OVERFLOW)); return f; }
    f = *((t_short *)(acMem + nMemOffset));
	  nMemOffset += sizeof(f);
    return f;
#ifdef RUN
  }
#endif

	return f;
}

t_pcode rd_PCode(int nPos = -1)
{
  // read();
	if (nPos != -1) nMemOffset = nPos;

	static /**/ t_pcode f;

#ifdef RUN
  if (bStack){
	  if (nMemOffset - sizeof(f) < 0){ bytearrayError(error(bytearray__STACK_UNDERFLOW)); return f; }
	  nMemOffset -= sizeof(f);
    return *((t_pcode *)(acMem + nMemOffset));    
  } else {
#endif
  	if (nMemOffset + sizeof(f) > nMem){ bytearrayError(error(bytearray__STACK_OVERFLOW)); return f; }
    f = *((t_pcode *)(acMem + nMemOffset));
	  nMemOffset += sizeof(f);
    return f;
#ifdef RUN
  }
#endif

	return f;
}

t_token rd_Token(int nPos = -1)
{
  // read();
	if (nPos != -1) nMemOffset = nPos;

	static /**/ t_token f;

#ifdef RUN
  if (bStack){
	  if (nMemOffset - sizeof(f) < 0){ bytearrayError(error(bytearray__STACK_UNDERFLOW)); return f; }
	  nMemOffset -= sizeof(f);
    return *((t_token *)(acMem + nMemOffset));    
  } else {
#endif
  	if (nMemOffset + sizeof(f) > nMem){ bytearrayError(error(bytearray__STACK_OVERFLOW)); return f; }
    f = *((t_token *)(acMem + nMemOffset));
	  nMemOffset += sizeof(f);
    return f;
#ifdef RUN
  }
#endif

	return f;
}

void rd_Struct(int nSizeOf, void *s, int nPos = -1)
{
  // read();
	if (nPos != -1) nMemOffset = nPos;	

#ifdef RUN
  if (bStack){
    if (nMemOffset - nSizeOf < 0){ bytearrayError(error(bytearray__STACK_UNDERFLOW)); return; }
	  nMemOffset -= nSizeOf;
    memcpy(s, (acMem + nMemOffset), nSizeOf);
    return;
  } else {
#endif
	  if (nMemOffset + nSizeOf > nMem){ bytearrayError(error(bytearray__STACK_OVERFLOW)); return; }
    memcpy(s, (acMem + nMemOffset), nSizeOf);
    nMemOffset += nSizeOf;
    return;
#ifdef RUN
  }
#endif
	
	return;
}

void *rd_Struct2(int nSizeOf, int nPos = -1)
{
  void *p = 0;
  // read();
	if (nPos != -1) nMemOffset = nPos;	

#ifdef RUN
  if (bStack){
    if (nMemOffset - nSizeOf < 0){ bytearrayError(error(bytearray__STACK_UNDERFLOW)); return 0; }
    p = (acMem + nMemOffset);
	  nMemOffset -= nSizeOf;
    
    return p;
  } else {
#endif
	  if (nMemOffset + nSizeOf > nMem){ bytearrayError(error(bytearray__STACK_OVERFLOW)); return 0; }
    p = (acMem + nMemOffset);
    
    nMemOffset += nSizeOf;
    return p;
#ifdef RUN
  }
#endif
	
	return 0;
}

unsigned char peekChar(int nPos = -1)
{
	if (nPos == -1) nPos = nMemOffset;

#ifdef RUN
  if (bStack){
	  if (nMemOffset - sizeof(char) < 0){ bytearrayError(error(bytearray__STACK_UNDERFLOW)); return 0; }	  
    return *((unsigned char *)(acMem + nPos - sizeof(char)));
  } else {
#endif
  	if (nMemOffset + sizeof(char) > nMem){ bytearrayError(error(bytearray__STACK_OVERFLOW)); return 0; }
    return *((unsigned char *)(acMem + nPos));
#ifdef RUN
  }
#endif

	return 0;
}
  
t_integer peekBoolean(int nPos = -1)
{
	if (nPos == -1) nPos = nMemOffset;

#ifdef RUN
  if (bStack){
	  if (nMemOffset - sizeof(t_boolean) < 0){ bytearrayError(error(bytearray__STACK_UNDERFLOW)); return 0; }	  
    return *((t_boolean *)(acMem + nPos - sizeof(t_boolean)));
  } else {
#endif
  	if (nMemOffset + sizeof(t_boolean) > nMem){ bytearrayError(error(bytearray__STACK_OVERFLOW)); return 0; }
    return *((t_boolean *)(acMem + nPos));
#ifdef RUN
  }
#endif

	return 0;
}

t_integer peekInteger(int nPos = -1)
{
	if (nPos == -1) nPos = nMemOffset;

#ifdef RUN
  if (bStack){
	  if (nMemOffset - sizeof(t_integer) < 0){ bytearrayError(error(bytearray__STACK_UNDERFLOW)); return 0; }	  
    return *((t_integer *)(acMem + nPos - sizeof(t_integer)));
  } else {
#endif
  	if (nMemOffset + sizeof(t_integer) > nMem){ bytearrayError(error(bytearray__STACK_OVERFLOW)); return 0; }
    return *((t_integer *)(acMem + nPos));
#ifdef RUN
  }
#endif

	return 0;
}

t_pcode peekPCode(int nPos = -1)
{
	if (nPos == -1) nPos = nMemOffset;

#ifdef RUN
  if (bStack){
	  if (nMemOffset - sizeof(t_pcode) < 0){ bytearrayError(error(bytearray__STACK_UNDERFLOW)); return 0; }	  
    return *((t_integer *)(acMem + nPos - sizeof(t_integer)));
  } else {
#endif
  	if (nMemOffset + sizeof(t_pcode) > nMem){ bytearrayError(error(bytearray__STACK_OVERFLOW)); return 0; }
    return *((t_integer *)(acMem + nPos));
#ifdef RUN
  }
#endif

	return 0;
  
}

t_token peekToken(int nPos = -1)
{
	if (nPos == -1) nPos = nMemOffset;

#ifdef RUN
  if (bStack){
	  if (nMemOffset - sizeof(t_token) < 0){ bytearrayError(error(bytearray__STACK_UNDERFLOW)); return 0; }	  
    return *((t_integer *)(acMem + nPos - sizeof(t_integer)));
  } else {
#endif
  	if (nMemOffset + sizeof(t_token) > nMem){ bytearrayError(error(bytearray__STACK_OVERFLOW)); return 0; }
    return *((t_integer *)(acMem + nPos));
#ifdef RUN
  }
#endif

	return 0;
  
}

/**
	reset current index to start
*/
bool resetPos()
{
	nMemOffset = 0;
	return true;
}

/**
	reset current index to start
*/
int getPos()
{
	return nMemOffset;
}

/**
	reset current index to start
*/
void setPos(int nPos/* = -1*/);

bool append(bytearray *ba, int nOffset = 0)
{
	static int nLen; nLen = ba->getPos() - nOffset;

  if (nLen > 0){
	  if (checkSize(nLen) == false){ bytearrayError(error(bytearray__NOT_ENOUGH_MEMORY)); return false;}

    memcpy(acMem + nMemOffset, ba->getMem() + nOffset, nLen); nMemOffset += nLen;
    return true;
  }

	return true;
}

bool insert(t_pointer v, int nSize);

bool append(t_pointer v, int nSize)
{
  if (nSize > 0){
	  if (checkSize(nSize) == false){ bytearrayError(error(bytearray__NOT_ENOUGH_MEMORY)); return false;}

    memcpy(acMem + nMemOffset, v, nSize); nMemOffset += nSize;
    return true;
  }

	return true;
}

void wr_Array(t_array *a)
{
   if (bStack){
	    for (register int i = 0; i < a->count; i++){
		    wr_Integer(a->idxTo[i]);
		    wr_Integer(a->idx[i]);
	    }
	    wr_Integer(a->count);
   } else {
      // kein wr_Struct() verwenden, da so kompakter
	    wr_Integer(a->count);
      /*
	    for (register int i = 0; i < a->count; i++){
		    wr_Integer(a->idx[i]);
		    wr_Integer(a->idxTo[i]);
	    }*/

      register int i = sizeof(t_integer) * a->count;
      memcpy(acMem + nMemOffset, a->idx, i); nMemOffset += i;
      memcpy(acMem + nMemOffset, a->idxTo, i); nMemOffset += i;
   }
 	return ;
}

void rd_Array(t_array *a)
{
   if (bStack){
	    a->count = rd_Integer();
	    for (register int i = 0; i < a->count; i++){
		    a->idx[i] = rd_Integer();
		    a->idxTo[i] = rd_Integer();
	    }
   } else {
      // kein rd_Struct() verwenden, da so kompakter
	    a->count = rd_Integer();

      /*
      //  geschwindigkeitsoptimierung, durch einmal lesen der count idx, memcpy auf idx[i]
	    for (register int i = 0; i < a->count; i++){
		    a->idx[i] = rd_Integer();
		    a->idxTo[i] = rd_Integer();
	    }
      */

      register int i = sizeof(t_integer) * a->count;
      memcpy(a->idx, acMem + nMemOffset, i); nMemOffset += i;
      memcpy(a->idxTo, acMem + nMemOffset, i); nMemOffset += i;
   }
}

char *getMem()
{
	return acMem;
}

void saveStack()
{
 	nSaveStack = nMemOffset;
}

void restoreStack()
{
	nMemOffset = nSaveStack;
}

int getSize()
{
	return nMemOffset;
}

int getSize2()
{
	return nMem;
}

void setStack(bool b)
{
	bStack = b;
}

//void saveStack();
//void restoreStack();

///* */ bool read();
///* */ void write();

//int getSize();
//int getSize2();

//void dump();

//private:
public:

bool checkSize(int nAddedSize);

char *acMem;
int nMemOffset;
int nMem;    // start length at some value
int nMemInc;    // set memory increment to some value

bool bStack;
int nSaveStack;

//textbuffer *myTextbuffer;

bool bError;

bool bytearrayError(const char *acBytearrayError);


static const char *error(int n)
{
  switch(n){

  case bytearray__UNDEFINED: return "undefined error";
  case bytearray__STACK_UNDERFLOW:  return "stack underflow";
  case bytearray__STACK_OVERFLOW:     return "stack overflow";
  case bytearray__NOT_ENOUGH_MEMORY: return "not enough memory";

  default: return "";
  }
}


};

#endif

#endif
