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

#include "_err.h"




#ifdef RUN


void _err::METHOD_Raise(int _Number, QString _Source, QString _Description, bool bRaiseRuntimeError)
{
  nNumber = _Number;
  sSource = _Source;
  sDescription = _Description;
}
#endif
