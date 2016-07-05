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

#ifndef _query_H
#define _query_H


#include "../kbshared/typedef.h"

class _query 

{ 
public:

  
    static t_boolean METHOD_Run(QString Database, QString QueryNameOrSql);
    static t_boolean METHOD_Run1(QString QueryNameOrSql);

    


private:


};




#endif