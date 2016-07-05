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


#ifndef TYPEDEF_H
#define TYPEDEF_H

#include "define.h"

#ifdef KBC
  #include "../kbc/typedef2.h"
#elif defined (IDE)

#define MAX_ITERATOR 64  // how many recursive calls 

  #include "../kbide/typedef2.h"
#elif defined (RUN)

#define MAX_ITERATOR 64  // how many recursive calls 

  #include "../kbrun/typedef2.h"
#elif defined (KBBINDER)
  #include "../kbc/typedef2.h"

#endif



#endif
