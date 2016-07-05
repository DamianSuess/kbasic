/*
***************************************************************************
Copyright (C) 2000-2008 KBasic Software: www.kbasic.com. All rights reserved.
Source codes are copyrighted by Bernd Noetscher 2000-2008.

You may use this source codes under the terms of the GNU Public License (Version 3) as published 
by the Free Software Foundation. 

If you are interested in using the source codes for other licenses or 
commercial development, you must buy commercial licenses from KBasic Software (Bernd Noetscher, Boseweg 9, 60529 Frankfurt / Germany).
***************************************************************************
*/



#ifndef DEFINE_H
#define DEFINE_H



//#define KBC
//#define IDE
#define RUN

//#define KBBINDER



//#define WINDOWS
#define LINUX
//#define MAC

#define HAS_CONSOLE true
#define CONSOLE	console::

#ifdef MAC
  #define MYAPP "KBasic"
#else
  #define MYAPP "KBasic"
#endif

#endif
