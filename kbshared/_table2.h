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

#ifndef _table2_H
#define _table2_H


#include "../kbshared/typedef.h"
#include "../kbshared/_stringsstrings.h"


class _table2

{ 
public:


  static t_boolean METHOD_Exists1(QString Table);
  static t_boolean METHOD_Exists(QString Database, QString Table);


 // static t_boolean METHOD_Create(QString Database, QString Table);


  static t_boolean METHOD_Create(QString Database, QString Table, _array *Fields);
  static t_boolean METHOD_Create1(QString Table, _array *Fields);

  static t_boolean METHOD_Create2(QString Database, QString Table);
  static t_boolean METHOD_Create3(QString Table);


  static t_boolean METHOD_Clear1(QString Table);
  static t_boolean METHOD_Clear(QString Database, QString Table);

  static t_boolean METHOD_Drop1(QString Table);
  static t_boolean METHOD_Drop(QString Database, QString Table);

  static _strings *METHOD_FieldNames1(QString Table);
  static _strings *METHOD_FieldNames(QString Database, QString Table);

  static QString METHOD_PrimaryKeyName1(QString Table);
  static QString METHOD_PrimaryKeyName(QString Database, QString Table);



//  static t_boolean METHOD_Copy(QString Database, QString Source, QString Destination);


  static t_boolean METHOD_Delete1(QString Table, _array *Where);
  static t_boolean METHOD_Delete(QString Database, QString Table, _array *Where);


  static t_boolean METHOD_Update1(QString Table, _array *Update, _array *Where);
  static t_boolean METHOD_Update(QString Database, QString Table, _array *Update, _array *Where);


  static t_boolean METHOD_Insert1(QString Table, _array *Insert);
  static t_boolean METHOD_Insert(QString Database, QString Table, _array *Insert);


private:


};




#endif