/*
***************************************************************************
Copyright (C) 2000-2008 KBasic Software: www.kbasic.com. All rights reserved.
Source codes are copyrighted by Bernd Noetscher 2000-2008.

You may use this source codes under the terms of the GNU Public License (Version 3) as published 
by the Free Software Foundation. 

If you are interested in using the source codes for other licenses or 
commercial development, you must buy commercial licenses from KBasic Software.
***************************************************************************
*/

#ifndef _BITS_H
#define _BITS_H


#include "typedef.h"


#include <QBitArray>


class _bits
{  

public:

QBitArray a;

#ifdef RUN
_bits()
{
  a.resize(32);
}



void METHOD_SetByte(t_byte Value);

void METHOD_SetShort(t_short Value)
{
  a.clear();
  a.resize(16);

  a[0] = Value & 1;
  a[1] = Value & 2;
  a[2] = Value & 4;
  a[3] = Value & 8;
  a[4] = Value & 16;
  a[5] = Value & 32;
  a[6] = Value & 64;
  a[7] = Value & 128;  
  a[8] = Value & 256;
  a[9] = Value & 512;
  a[10] = Value & 1024;
  a[11] = Value & 2048;
  a[12] = Value & 4096;
  a[13] = Value & 8192;
  a[14] = Value & 16384;
  a[15] = Value & 32768;  
}

void METHOD_SetInteger(t_integer Value)
{
  a.clear();
  a.resize(32);

  a[0] = Value & 1;
  a[1] = Value & 2;
  a[2] = Value & 4;
  a[3] = Value & 8;
  a[4] = Value & 16;
  a[5] = Value & 32;
  a[6] = Value & 64;
  a[7] = Value & 128;  
  a[8] = Value & 256;
  a[9] = Value & 512;
  a[10] = Value & 1024;
  a[11] = Value & 2048;
  a[12] = Value & 4096;
  a[13] = Value & 8192;
  a[14] = Value & 16384;
  a[15] = Value & 32768;  
  a[16] = Value & 65536;
  a[17] = Value & 131072;
  a[18] = Value & 262144;
  a[19] = Value & 524288;
  a[20] = Value & 1048576;
  a[21] = Value & 2097152;
  a[22] = Value & 4194304;
  a[23] = Value & 8388608;  
  a[24] = Value & 16777216;
  a[25] = Value & 33554432;
  a[26] = Value & 67108864;
  a[27] = Value & 134217728;
  a[28] = Value & 268435456;
  a[29] = Value & 536870912;
  a[30] = Value & 1073741824;
  a[31] = Value & 2147483648;  
}

void METHOD_SetLong(t_long Value)
{
}

t_byte METHOD_Byte();


t_short METHOD_Short()
{
  a.resize(16);

  t_short c = 0;

  c |= a[0] << 0;
  c |= a[1] << 1;
  c |= a[2] << 2;
  c |= a[3] << 3;
  c |= a[4] << 4;
  c |= a[5] << 5;
  c |= a[6] << 6;
  c |= a[7] << 7;
  c |= a[8] << 8;
  c |= a[9] << 9;
  c |= a[10] << 10;
  c |= a[11] << 11;
  c |= a[12] << 12;
  c |= a[13] << 13;
  c |= a[14] << 14;
  c |= a[15] << 15;

  return c;
}

t_integer METHOD_Integer()
{
  a.resize(32);

  t_integer c = 0;

  c |= a[0] << 0;
  c |= a[1] << 1;
  c |= a[2] << 2;
  c |= a[3] << 3;
  c |= a[4] << 4;
  c |= a[5] << 5;
  c |= a[6] << 6;
  c |= a[7] << 7;
  c |= a[8] << 8;
  c |= a[9] << 9;
  c |= a[10] << 10;
  c |= a[11] << 11;
  c |= a[12] << 12;
  c |= a[13] << 13;
  c |= a[14] << 14;
  c |= a[15] << 15;
  c |= a[16] << 16;
  c |= a[17] << 17;
  c |= a[18] << 18;
  c |= a[19] << 19;
  c |= a[20] << 20;
  c |= a[21] << 21;
  c |= a[22] << 22;
  c |= a[23] << 23;
  c |= a[24] << 24;
  c |= a[25] << 25;
  c |= a[26] << 26;
  c |= a[27] << 27;
  c |= a[28] << 28;
  c |= a[29] << 29;
  c |= a[30] << 30;
  c |= a[31] << 31;

  return c;
}

t_long METHOD_Long()
{
  return 0;
}

void METHOD_SetBit(t_integer Position, t_boolean YesNo)
{
  if (YesNo){
    a.setBit(Position - 1);
  } else {
    a.clearBit(Position - 1);
  }  
}

t_boolean METHOD_Bit(t_integer Position)
{
  return a.testBit(Position - 1);
}

void METHOD_ToogleBit(t_integer Position)
{
  a.toggleBit(Position - 1);
}

// *** bindings
// *** 
private:
#endif
};

#endif

