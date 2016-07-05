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

#include "memory_class2.h"



memory_class2::memory_class2()
{
}

memory_class2::~memory_class2()
{

  QMap<QString, sub*>::Iterator it2;

  for ( it2 = list_method.begin(); it2 != list_method.end(); ++it2 ) {
    sub *m = (*it2);
    delete m;
  }
  list_method.clear();

  for ( it2 = list_propertyGet.begin(); it2 != list_propertyGet.end(); ++it2 ) {
    sub *m = (*it2);
    delete m;
  }
  list_propertyGet.clear();

  for ( it2 = list_propertySet.begin(); it2 != list_propertySet.end(); ++it2 ) {
    sub *m = (*it2);
    delete m;
  }
  list_propertySet.clear();


  list_method2.clear();
  list_method3.clear();
  list_method4.clear();

  list_propertyGet2.clear();
  list_propertyGet3.clear();
  list_propertyGet4.clear();

  list_propertySet2.clear();
  list_propertySet3.clear();
  list_propertySet4.clear();

}


bool 		memory_class2::addClass			(
    int identifier,
    const char *classname,
    int pc_pos,
    int pc_len,    
    int nExtend,
    int destructor_id
                                     )
{

	class_ *t = new class_();

  register int n = strlen(classname);

	memcpy(t->acName, classname, n);
	t->acName[n] = '\0';

  t->nId = identifier;

	t->pc_pos = pc_pos;
	t->pc_len = pc_len;
	t->nExtend = nExtend;
	t->nDestructorId = destructor_id;
  
  
	list_class.insert(identifier, t);
	list_class2.insert(classname, t);

	return true;		

}

int		memory_class2::getClassId(QString sName)
{
  if (list_class2.contains(sName)) return list_class2[sName]->nId;
  return 0;
}

int		memory_class2::getClassMethodId(int class_identifier, QString sName)
{
  QByteArray a = sName.toAscii();
  const char *ac = a.data();
  const char *result = getKeyMethod2(class_identifier, ac);

  if (list_method2.contains(result)) return list_method2[result]->nId;
  return 0;
}


bool memory_class2::addClassMethod	(
    int class_identifier,
    int identifier,
    const char *acRealname,
    const char *acName,
    int pc_pos,
    int pc_len    
                                     )
{

	sub *t = new sub();

	t->nModuleId = class_identifier;/*
  if (class_identifier == 100007){
    class_identifier = class_identifier;
  }*/

  t->nId = identifier;

  register int n = strlen(acName);

	memcpy(t->acName, acName, n);
	t->acName[n] = '\0';

  n = strlen(acRealname);

	memcpy(t->acRealName, acRealname, n);
	t->acRealName[n] = '\0';

	t->pc_pos = pc_pos;
	t->pc_len = pc_len;
  
	list_method.insert(getKeyMethod(class_identifier, identifier), t);
	list_method2.insert(getKeyMethod2(class_identifier, acName), t);
	list_method3.insert(getKeyMethod2(class_identifier, acRealname), t);
	list_method4.insert(getKeyMethod3(class_identifier, t), t);
  

	return true;		

}

bool memory_class2::addClassPropertyGet	(
    int class_identifier,
    int identifier,
    const char *acRealname,
    const char *acName,
    int pc_pos,
    int pc_len    
                                     )
{

	sub *t = new sub();

	t->nModuleId = class_identifier;

  register int n = strlen(acName);

	memcpy(t->acName, acName, n);
	t->acRealName[n] = '\0';

  n = strlen(acRealname);

	memcpy(t->acRealName, acRealname, n);
	t->acRealName[n] = '\0';

	t->pc_pos = pc_pos;
	t->pc_len = pc_len;
  
	list_propertyGet.insert(getKeyMethod(class_identifier, identifier), t);
	list_propertyGet2.insert(getKeyMethod2(class_identifier, acName), t);
	list_propertyGet3.insert(getKeyMethod2(class_identifier, acRealname), t);
	list_propertyGet4.insert(getKeyMethod3(class_identifier, t), t);
  
	return true;		

}

bool memory_class2::addClassPropertySet	(
    int class_identifier,
    int identifier,
    const char *acRealname,
    const char *acName,
    int pc_pos,
    int pc_len    
                                     )
{

	sub *t = new sub();

	t->nModuleId = class_identifier;

  register int n = strlen(acName);

	memcpy(t->acName, acName, n);
	t->acRealName[n] = '\0';

  n = strlen(acRealname);

	memcpy(t->acRealName, acRealname, n);
	t->acRealName[n] = '\0';

	t->pc_pos = pc_pos;
	t->pc_len = pc_len;
  
	list_propertySet.insert(getKeyMethod(class_identifier, identifier), t);
	list_propertySet2.insert(getKeyMethod2(class_identifier, acName), t);
	list_propertySet3.insert(getKeyMethod2(class_identifier, acRealname), t);
	list_propertySet4.insert(getKeyMethod3(class_identifier, t), t);
  
	return true;		

}

char *memory_class2::getKeyMethod(int nClassId, int nId)
{
	static char acKey[1024];

	sprintf(acKey, "%d.%d", nClassId, nId);

	return acKey;
}

char *memory_class2::getKeyMethod2(int nClassId, const char *acName)
{
	static char acKey[1024];

	sprintf(acKey, "%d.%s", nClassId, acName);
  // make case insensitive
  int n = strlen(acKey);
	for (unsigned int i = 0; i < n; i++) acKey[i] = toupper(acKey[i]);

	return acKey;
}

char *memory_class2::getKeyMethod2(int nClassId, const char *acName, QList<int> *param)
{
	static char acKey[2048];
	static char ac[2048];

	sprintf(acKey, "%d.%s", nClassId, acName);
  // make case insensitive
  int n = strlen(acKey);
	for (unsigned int i = 0; i < n; i++) acKey[i] = toupper(acKey[i]);

  sprintf(ac, "%05d", 155);// 155 == token__SUB
  strcat(acKey, ac);

  n = param->count();
  for ( uint i = 0; i < n; ++i ){
    sprintf(ac, "%05ld%01d", (param->at(i)), 0);
    strcat(acKey, ac);
  }

	return acKey;
}

char *memory_class2::getKeyMethod3(int nClassId, sub *s)
{
	static char acKey[1024];

	sprintf(acKey, "%d.%d", nClassId, (int) s);

	return acKey;
}

int     memory_class2::getPcodePosMethod			(int nClassId, int nId)
{
  sub *t = list_method[getKeyMethod(nClassId, nId)];

	if (t != 0){
		return t->pc_pos;
	}
	return 0;
}

int     memory_class2::getPcodePosPropertyGet			(int nClassId, int nId)
{
  sub *t = list_propertyGet[getKeyMethod(nClassId, nId)];

	if (t != 0){
		return t->pc_pos;
	}
	return 0;
}

int     memory_class2::getPcodePosPropertySet			(int nClassId, int nId)
{
  sub *t = list_propertySet[getKeyMethod(nClassId, nId)];

	if (t != 0){
		return t->pc_pos;
	}
	return 0;
}

int     memory_class2::getPcodeLenMethod			(int nClassId, int nId)
{
  sub *t = list_method[getKeyMethod(nClassId, nId)];

	if (t != 0){
		return t->pc_len;
	}
	return 0;
}

int     memory_class2::getPcodeLenPropertyGet			(int nClassId, int nId)
{
  sub *t = list_propertyGet[getKeyMethod(nClassId, nId)];

	if (t != 0){
		return t->pc_len;
	}
	return 0;
}

int     memory_class2::getPcodeLenPropertySet			(int nClassId, int nId)
{
  sub *t = list_propertySet[getKeyMethod(nClassId, nId)];

	if (t != 0){
		return t->pc_len;
	}
	return 0;
}

int     memory_class2::getPcodeLenMethod			(int nClassId, sub *s)
{
  sub *t = list_method4[getKeyMethod3(nClassId, s)];

	if (t != 0){
		return t->pc_len;
	}
	return 0;
}

int     memory_class2::getPcodeLenPropertyGet			(int nClassId, sub *s)
{
  sub *t = list_propertyGet4[getKeyMethod3(nClassId, s)];

	if (t != 0){
		return t->pc_len;
	}
	return 0;
}

int     memory_class2::getPcodeLenPropertySet			(int nClassId, sub *s)
{
  sub *t = list_propertySet4[getKeyMethod3(nClassId, s)];

	if (t != 0){
		return t->pc_len;
	}
	return 0;
}

bool     memory_class2::hasMethodWithName			(int nClassId, const char *acName)
{
  sub *t = list_method2[getKeyMethod2(nClassId, acName)];

	if (t != 0){
		return true;
	}
	return false;
}

bool     memory_class2::hasPropertyGetWithName			(int nClassId, const char *acName)
{
  sub *t = list_propertyGet2[getKeyMethod2(nClassId, acName)];

	if (t != 0){
		return true;
	}
	return false;
}

bool     memory_class2::hasPropertySetWithName			(int nClassId, const char *acName)
{
  sub *t = list_propertySet2[getKeyMethod2(nClassId, acName)];

	if (t != 0){
		return true;
	}
	return false;
}

sub*     memory_class2::getSub			(int nClassId, const char *acName)
{
  sub *t = list_method3[getKeyMethod2(nClassId, acName)];

	if (t != 0){
    lastSub = t;
		return t;
	}
	return 0;
}

sub*     memory_class2::getSub			(int nClassId, const char *acName, QList<int> *param)
{
  sub *t = list_method2[getKeyMethod2(nClassId, acName, param)];

	if (t != 0){
    lastSub = t;
		return t;
	}
	return 0;
}

sub*     memory_class2::getLastSub			()
{ 
	return lastSub;
}

/*
bool     memory_class2::hasMethodWithNameAndReturnType			(int nClassId, const char *acName, const char *acReturnType)
{
  sub *t = list_method2[getKeyMethod2(nClassId, acName)];

	if (t != 0){
    if (strcmp(t->acReturnType, acReturnType) == 0) return true;
	}
	return false;
}

*/