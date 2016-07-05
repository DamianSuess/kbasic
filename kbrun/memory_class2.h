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


#ifndef MEMORY_CLASS2_H
#define MEMORY_CLASS2_H

#include "memory_class.h"


class memory_class2: public memory_class
{
public:
  memory_class2();
  ~memory_class2();

	bool 		addClass		(
    int identifier,
    const char *classname,
    int pc_pos,
    int pc_len,    
    int nExtend,
    int destructor_id    
    );

  int		getClassId(QString sName);

	bool 		addClassMethod (
    int class_identifier,
    int identifier,
    const char *acRealname,
    const char *acName,
    int pc_pos,
    int pc_len   
		);

  int		getClassMethodId(int class_identifier, QString sName);

	bool 		addClassPropertyGet (
    int class_identifier,
    int identifier,
    const char *acRealname,
    const char *acName,
    int pc_pos,
    int pc_len   
		);

	bool 		addClassPropertySet (
    int class_identifier,
    int identifier,
    const char *acRealname,
    const char *acName,
    int pc_pos,
    int pc_len   
		);

char *getKeyMethod(int nClassId, int nId);
char *getKeyMethod2(int nClassId, const char *acName);
char *getKeyMethod2(int nClassId, const char *acName, QList<int> *param);
char *getKeyMethod3(int nClassId, sub* s);

int   getPcodePosMethod			(int nClassId, int nId);
int   getPcodeLenMethod			(int nClassId, int nId);
int   getPcodeLenMethod			(int nClassId, sub* s);

int   getPcodePosPropertyGet			(int nClassId, int nId);
int   getPcodeLenPropertyGet			(int nClassId, int nId);
int   getPcodeLenPropertyGet			(int nClassId, sub* s);

int   getPcodePosPropertySet			(int nClassId, int nId);
int   getPcodeLenPropertySet			(int nClassId, int nId);
int   getPcodeLenPropertySet			(int nClassId, sub* s);

sub* 		getLastSub (); 

sub* 		getSub (int nClassId, const char *acName);  
sub* 		getSub (int nClassId, const char *acName, QList<int> *param);  
bool 		hasMethodWithName (int nClassId, const char *acName);  
bool 		hasPropertyGetWithName (int nClassId, const char *acName);  
bool 		hasPropertySetWithName (int nClassId, const char *acName);  
//bool 		hasMethodWithNameAndReturnType (int nClassId, const char *acName, const char *acReturnType);  




private:
	typedef QMap<QString, sub*> map9;
	map9 list_method;  
	map9 list_method2; 
  map9 list_method3; 
  map9 list_method4;

	map9 list_propertyGet;  
	map9 list_propertyGet2; 
  map9 list_propertyGet3; 
  map9 list_propertyGet4; 

	map9 list_propertySet;  
	map9 list_propertySet2; 
  map9 list_propertySet3; 
  map9 list_propertySet4; 

  sub* lastSub;

};

#endif
