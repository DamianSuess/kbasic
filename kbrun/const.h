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


#ifndef CONST_H
#define CONST_H

const int ARRAY_START 	= 0;  // which number is the first possible index (default, depends on oldbasic, veryoldbasic)

// there is a reason why the following const are declared here, because they 
// are used in type, memory and so, there it is not reasonable to put them in parser.h

const int MAX_ARRAY 	= 8;  // how many dimension each array can contain of
const int MAX_TYPE 	= 256;  // how many element types are allowed in a type definition
const int MAX_STRUCTURE 	= 256;  // how many elements are allowed in a structure definition
const int MAX_ENUM 	= 512;  // how many elements of enum are allowed in an enum definition
const int MAX_PARAM 	= 64;  // how many parameters are allowed in a function definition
const int MAX_IDENTIFIER	= 128;  // how long each identifier part may be, e.g. Length of DIM test1 = 5
const int MAX_THROW = 8;  // how many throws are allowed in method definition

const int MAX_LABEL_USED	= 256;  // how many a label can be referenced
const int MAX_SUB_USED	= 4096;  // how many a sub can be referenced
const int MAX_CLASSMETHOD_USED	= 4096;  // how many a classmethod can be referenced

const int MAX_FILENAMELEN	= 256;  // how long a filename might be


const int MAX_SKALAR_TYPE_ID	= 20000000;  // border: begin of user defined type id
const int MAX_SKALAR_ENUM_ID	= 30000000;  // border: begin of user defined enum id


const float scanner__KBASIC_VERSION = 1.080924; // versionsnr.xx jahr xx monat xx tag
const float interpreter__KBASIC_VERSION = 1.080924; // versionsnr.xx jahr xx monat xx tag
const float parser__KBASIC_VERSION 	= 1.080924; // versionsnr.xx jahr xx monat xx tag
const double compiler__KBASIC_VERSION 	= 1.080924; // versionsnr.xx jahr xx monat xx tag

const int parser__MAX_nDEF = 26;


const int parser__MAX_ELSEIF 	= 256;// how many elseif are possible
const int parser__MAX_CASE 	= 256;     // how many cases are possible
const int parser__MAX_CASECOMMA 	= 64; // how many comma cases are possible, e.g. case 15, 24, 34, 45
const int parser__MAX_DIM 	= 20;   // how many DIM are possible in one line
const int parser__MAX_CONST 	= 10;   // how many CONST are possible in one line
const int parser__MAX_DATA 	= 256;   // how many DATA are possible in one line
const int parser__MAX_ID 		= 32;  // how many sub identifiers are allowed, e.g i.name = 2; address.phone.first = 3
const int parser__MAX_EXPRESSION	= 32;  // how many sub identifiers are allowed, e.g i.name = 2; address.phone.first = 3
const int parser__ARRAY_DEFAULT = 10;  // size of all dimensions to default, if array var was not declared and EXPLICIT OFF
const int parser__MAX_FIELD	= 32;  // how many expressions are allowed for FIELD
const int parser__MAX_CLOSE	= 32;  // how many expressions are allowed for CLOSE
const int parser__MAX_ONGOSUB	= 32;  // how many labels are allowed for ON GOSUB in one line
const int parser__MAX_ONGOTO	= 32;  // how many labels are allowed for ON GOTO in one line
const int parser__MAX_DEF	= 26;  // how many def are allowed in one line

const int parser__MAX_CHOOSE	= 13;  // how many choose entries are allowed
const int parser__MAX_SWITCH	= 7;  // how many switch entries are allowed

const int parser__MAX_CATCH	= 16;  // how many catches are allowed in one try
const int parser__MAX_THROW = 16;  // how many throws are allowed in method definition

const int interpreter__MAX_STACK = 0xffff;  // how many times a stack can be created = stack size
const int interpreter__MAX_PARAM 	= 16;  // how many parameters are allowed in a function definition

const int parser__MAX_WRITE	= interpreter__MAX_PARAM;  // how many expressions are allowed for WRITE
const int parser__MAX_INPUT	= parser__MAX_WRITE;  // how many expressions are allowed for INPUT #1, $stringvariable, ...

const int parser__MAX_ITERATOR = 32;  // how many recursive calls of parser fSUB_CALL is possible for myModule->first(idx) ...


const int interpreter__MAX_PCODE_ID = 2048;  // how big a pcode number could be




#endif
