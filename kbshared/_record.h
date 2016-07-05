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


#ifndef _RECORD_H
#define _RECORD_H


#include "typedef.h"



class _record
{
  
public:


static QString METHOD_Open(QString Database, QString TableOrSql);


static QString METHOD_Open(QString Database, QString Table, _array *Where, _array *OrderBy);


static QString METHOD_Open(QString Database, _strings *Tables, _array *Where);


static QString METHOD_Open3(QString TableOrSql);


static QString METHOD_Open4(QString Table, _array *Where, _array *OrderBy);


static QString METHOD_Open5(_strings *Tables, _array *Where);


static t_boolean METHOD_Close(QString QueryId);

static t_boolean METHOD_Requery(QString QueryId);

static t_boolean METHOD_First(QString QueryId);


static t_boolean METHOD_Next(QString QueryId);


static t_boolean METHOD_Previous(QString QueryId);


static t_boolean METHOD_Last(QString QueryId);


static t_boolean METHOD_GoTo(QString QueryId, t_integer Position);


static t_integer METHOD_Length(QString QueryId);


static t_integer METHOD_Position(QString QueryId);


static t_boolean METHOD_AddNew(QString QueryId);


static t_boolean METHOD_Insert(QString QueryId);


static t_boolean METHOD_Update(QString QueryId);


static t_boolean METHOD_Delete(QString QueryId);


static t_boolean METHOD_Clear(QString QueryId);


static void METHOD_Set(QString QueryId, QString Field, t_variant Value);
 

static t_variant METHOD_Get(QString QueryId, QString Field);

static _strings *METHOD_Fields(QString QueryId);

static QString METHOD_PrimaryKeyName(QString QueryId);
static t_integer METHOD_PrimaryKey(QString QueryId);




}
;



#endif