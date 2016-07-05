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

#include "memory_class.h"



memory_class::memory_class			()
{

	nIdCounter = pcode__user_defined_class;
}

memory_class::~memory_class		()
{

  QMap<int, class_*>::Iterator it2;
  for ( it2 = list_class.begin(); it2 != list_class.end(); ++it2 ) {
    class_ *m = *it2;

    delete m->myPropertyGet;
    delete m->myPropertySet;
    delete m->mySub;
    delete m->vars;    
    delete m->static_vars;
    delete m->staticCode_vars;
    delete m->consts;

    delete m->myPcode;
    delete m->myClassStaticPcode;    

    //for (int i = 0; i < m->nPcodeCatchCounter; i++){
      //delete m->pcodeCatch[i];   // werden woanders freigegeben  
    //}

    delete m;
  }
  list_class.clear();
  list_class2.clear();

  findClass(-99); // delete cache
}

// ****************************
// * bool classError(char *acclassError)
// *
// * description:
// * prints a class error message
// *
// * interpreter_parameter:
// * char *acclassError = the error message to print
// *
// * return:
// * dummy
// ****************************
bool memory_class::classError(char *acclassError)
{
	static char acText[1024];

	sprintf(acText, "\nclass error: %s\n", acclassError);
	CONSOLE printError(acText);
	return false;
}

class_	*memory_class::findClass	(int nId)
{
  // * optimize
  static int _nId = -100;
  static class_ *v = 0;
  static void *_this = 0;

  if (_nId == nId && _this == this){
    return v;
  }
  // *

	if (list_class.contains(nId)){
    _nId = nId;
    _this = this;
    v = list_class[nId];
		return v;
	}
  _nId = -100;

	return 0;
}

class_ *memory_class::newClass(
                               const char *acName, 
                               pcode *myPcode, 
                               pcode *myClassStaticPcode,                                
                               const char *acExtend, 
                               const char *acFile,
                               bool bIsAbstract
                               )
{
	class_ *t = new class_();

  int n = strlen(acName);

	memcpy(t->acName, acName, n);
	t->acName[n] = '\0';  

  if (acExtend[0] != 0){

    n = strlen(acExtend);
    
	  memcpy(t->acExtendName, acExtend, n);
	  t->acExtendName[n] = '\0';
  } else {
	  memcpy(t->acExtendName, "Object", 6);
	  t->acExtendName[6] = '\0';
  }

  n = strlen(acFile);
	memcpy(t->acFile, acFile, n);
	t->acFile[n] = '\0';

	t->nId = nIdCounter;
	t->myPcode = myPcode;
	t->myClassStaticPcode = myClassStaticPcode;  
	t->pc_pos = 0;
	t->pc_len = 0;  
	t->bPcodeBuilt = false;	
	t->bRegistered = true;
	t->bIsAbstract = bIsAbstract;  
	t->bStatic = false;  
	t->nExtend = getId(acExtend);
  
//	t->myStatic = new memory_sub();
	t->mySub = new memory_sub();
	t->myPropertyGet = new memory_sub();
	t->myPropertySet = new memory_sub();
	t->vars = new memory_variable();
	t->static_vars = new memory_variable();  
	t->staticCode_vars = new memory_variable();    
	t->consts = new memory_const();		
//	t->myPropertyGetConsts = new memory_const();		
//	t->myPropertyGetConsts = new memory_const();		

  t->nCountMethod = 0;
  t->nCountPropertyGet = 0;
  t->nCountPropertySet = 0;
	
	t->nPcodeCatchIterator = 0;
	t->nPcodeCatchCounter = 0;

  return t;
}

char *memory_class::getKey(const char *acName)
{
	static char acKey[1024];
	sprintf(acKey, "%s", acName);
  // make case insensitive
  int n = strlen(acKey);
	for (unsigned int i = 0; i < n; i++) acKey[i] = toupper(acKey[i]);

	return acKey;
}

int 		memory_class::addClass			(
                                     const char *acName, 
                                     pcode *myPcode, 
                                     pcode *myClassStaticPcode,                                      
                                     const char *acExtend,
                                     const char *acFile,
                                     bool bIsAbstract, 
                                     int nId
                                     )
{
	if (exist(acName)){ // already declared
		return -1;
	} else {

		nIdCounter++;
    bool bIsCached = nId != -1;
    if (nId == -1) nId = nIdCounter; else nIdCounter = nId;    

    class_ *c = newClass(acName, myPcode, myClassStaticPcode, acExtend, acFile, bIsAbstract);
    if (c == 0) return -1; // 

    c->bIsCached = bIsCached;

		list_class.insert(nId, c);
		list_class2.insert(acName, c);

		return nId;
	
	}

}

int 		memory_class::addClassMethod	(
																				const char *acClassName, 
																				const char *acRealName, 
																				const char *acName, 
																				const char *acSuffix, 
																				const char *acReturnType, 
																				int nReturnSize, 
																				pcode *myPcode, 
																				bool function, 
			                               bool constructor, 
			                               bool destructor, 
			                               bool signal, 
			                               bool slot, 
																				int pc_pos, 
																				int nScope, 
																				int nTokenPos,
                               			int nTokenLinePos,
																				bool bStatic,
																				bool bAbstract,
                                     const char *acFile,
                                     int nLine,		
                                        bool bDeclare,
                                        const char *acAlias,
                                        const char *acLib,
                                        const char *acLibCallSignature     
                                        , int nSubId)
{
  int nId = getId(acClassName);
	class_ *m = findClass	(nId);
	if (m != 0){

    m->nCountMethod++;
   
    
		return m->mySub->addSub(acClassName, nId, acRealName, acName, acSuffix, acReturnType, nReturnSize, myPcode, function, constructor, destructor, signal, slot, pc_pos, nScope, nTokenPos, nTokenLinePos, bStatic, bAbstract, acFile, nLine, bDeclare, acAlias, acLib, acLibCallSignature, nSubId);
	}
	return 0;
}

int 		memory_class::addClassPropertyGet	(
																				const char *acClassName, 
																				const char *acName, 
																				const char *acSuffix, 
																				const char *acReturnType, 
																				int nReturnSize, 
																				pcode *myPcode, 
																				bool function, 
																				int pc_pos, 
																				int nScope, 
																				int nTokenPos,
                                    int nTokenLinePos,
																				bool bStatic,
																				bool bAbstract,
                                     const char *acFile,
                                     int nLine					
                                     , int nSubId
																			 )
{
  int nId = getId(acClassName);
	class_ *m = findClass	(nId);
	if (m != 0){

    bool constructor = false;
    bool destructor = false;
    bool signal = false;
    bool slot = false;

    m->nCountPropertyGet++;

		return m->myPropertyGet->addSub(acClassName, nId, acName, acName, acSuffix, acReturnType, nReturnSize, myPcode, function, constructor, destructor, signal, slot, pc_pos, nScope, nTokenPos, nTokenLinePos, bStatic, bAbstract, acFile, nLine, false, "", "", "", nSubId);
	}
	return 0;
}

int 		memory_class::addClassPropertySet	(
																				const char *acClassName, 
																				const char *acName, 
																				const char *acSuffix, 
																				const char *acReturnType, 
																				int nReturnSize, 
																				pcode *myPcode, 
																				bool function, 
																				int pc_pos, 
																				int nScope, 
																				int nTokenPos,
                                    int nTokenLinePos,
																				bool bStatic,
																				bool bAbstract,
                                     const char *acFile,
                                     int nLine		
                                     , int nSubId
																			 )
{
  int nId = getId(acClassName);
	class_ *m = findClass	(nId);
	if (m != 0){

    bool constructor = false;
    bool destructor = false;
    bool signal = false;
    bool slot = false;

    m->nCountPropertySet++;

		return m->myPropertySet->addSub(acClassName, nId, acName, acName, acSuffix, acReturnType, nReturnSize, myPcode, function, constructor, destructor, signal, slot, pc_pos, nScope, nTokenPos, nTokenLinePos, bStatic, bAbstract, acFile, nLine, false, "", "", "", nSubId);
	}
	return 0;
}

bool memory_class::findVar(int nId, const char **acModule, const char **acSub, const char **acVar)
{

  if (first()){
    do {
      int nClassId = getId();

      if (findVar(nClassId, nId, acModule, acSub, acVar)) return true;
      if (findStaticVar(nClassId, nId, acModule, acSub, acVar)) return true;
      if (findStaticCodeVar(nClassId, nId, acModule, acSub, acVar)) return true;

      if (firstMethod()){
        do {
         int nMethodId = getIdMethod();

         if (findMethodVar(nClassId, nMethodId, nId, acModule, acSub, acVar)) return true;

         if (findParameterMethod(nClassId, nMethodId, nId, acModule, acSub, acVar)) return true;
        } while (nextMethod());
      }

      if (firstConstructor()){
        do {
         int nMethodId = getIdMethod();

         if (findMethodVar(nClassId, nMethodId, nId, acModule, acSub, acVar)) return true;

         if (findParameterMethod(nClassId, nMethodId, nId, acModule, acSub, acVar)) return true;
        } while (nextConstructor());
      }

      if (firstPropertyGet()){
       do {
         int nMethodId = getIdPropertyGet();

         if (findPropertyGetVar(nClassId, nMethodId, nId, acModule, acSub, acVar)) return true;
       } while (nextPropertyGet());
      }
      
      if (firstPropertySet()){
        do {
         int nMethodId = getIdPropertySet();

         if (findPropertySetVar(nClassId, nMethodId, nId, acModule, acSub, acVar)) return true;
         if (findParameterPropertySet(nClassId, nMethodId, nId, acModule, acSub, acVar)) return true;
        } while (nextPropertySet());
      }

      if (firstDestructor()){
        do {
         int nMethodId = getIdMethod();

         if (findMethodVar(nClassId, nMethodId, nId, acModule, acSub, acVar)) return true;

         if (findParameterMethod(nClassId, nMethodId, nId, acModule, acSub, acVar)) return true;
        } while (nextDestructor());
      }

      if (firstSlot()){
        do {
         int nMethodId = getIdMethod();

         if (findMethodVar(nClassId, nMethodId, nId, acModule, acSub, acVar)) return true;

         if (findParameterMethod(nClassId, nMethodId, nId, acModule, acSub, acVar)) return true;
        } while (nextSlot());
      }

    } while (next());
  }

  return false;
}

bool memory_class::findConst(int nId, const char **acModule, const char **acSub, const char **acVar)
{
 
  if (first()){
    do {
      int nClassId = getId();

      if (findConst(nClassId, nId, acModule, acSub, acVar)) return true;

      if (firstMethod()){
        do {
          int nMethodId = getIdMethod();

          if (findMethodConst(nClassId, nMethodId, nId, acModule, acSub, acVar)) return true;
        } while (nextMethod());
      }

      if (firstPropertyGet()){
        do {
         int nMethodId = getIdPropertyGet();

          if (findPropertyGetConst(nClassId, nMethodId, nId, acModule, acSub, acVar)) return true;
        } while (nextPropertyGet());
      }

      if (firstPropertySet()){
        do {
         int nMethodId = getIdPropertySet();

          if (findPropertySetConst(nClassId, nMethodId, nId, acModule, acSub, acVar)) return true;
        } while (nextPropertySet());
      }

    } while (next());
  }

  return false;
}

bool 		memory_class::setDestructorId				(int nId, int nDestructorId)
{
	class_ *m = findClass	(nId);
	if (m != 0){
    m->nDestructorId = nDestructorId;
    return true;
	}
	return false;
}

bool 		memory_class::setParentId				(int nId, int nParentId)
{
	class_ *m = findClass	(nId);
	if (m != 0){
    m->nExtend = nParentId;
    return true;
	}
	return false;
}

char   *memory_class::getFile				(int nId)
{
	class_ *m = findClass	(nId);
	if (m != 0){
    return m->acFile;
	}
	return 0;
}

int 		memory_class::getDestructorId				(int nId)
{
	class_ *m = findClass	(nId);
	if (m != 0){
    return m->nDestructorId;
	}
	return 0;
}

bool 		memory_class::isCached				(int nId)
{
	class_ *m = findClass	(nId);
	if (m != 0){
    return m->bIsCached;
	}
	return false;
}

bool 		memory_class::isAbstract				(int nId)
{
	class_ *m = findClass	(nId);
	if (m != 0){
    return m->bIsAbstract;
	}
	return false;
}

bool 		memory_class::isAbstract				(const char *acName)
{
  return isAbstract(getId(acName));
}

bool 		memory_class::isAbstractMethod				(int nClassId, int nId)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){
		return m->mySub->isAbstract(nId);
	}
	return false;
}

bool 		memory_class::isAbstractMethod				(const char *acName, const char *acMethod)
{
	class_ *m = findClass	( getId(acName) );
	if (m != 0){
		return m->mySub->isAbstract(m->mySub->getId(m->acName, acMethod));
	}
	return false;
}

bool 		memory_class::isSubClass				(int nId, int nMaybeParentClass)
{
	class_ *m = findClass	(nId);
	if (m != 0){
re:
    // walk through hierarchy, find in parent class
    nId = getParentId(nId);
    if (nId > 0){
      if (nId == nMaybeParentClass) return true;
      goto re;
    }
	}
	return false;
}

bool 		memory_class::exist				(int nId)
{
	class_ *m = findClass	(nId);
	if (m != 0){
		return true;
	}
	return false;
}

bool 		memory_class::existStatic				(int nId)
{
	class_ *m = findClass	(nId);
	if (m != 0){
    return m->bStatic;
	}
	return false;
}

bool     memory_class::existMethod			(int nModuleId, int nId)
{
	class_ *m = findClass	(nModuleId);
	if (m != 0){
		return m->mySub->exist(nId);
	}
	return 0;
}

bool     memory_class::existPropertyGet			(int nModuleId, int nId)
{
	class_ *m = findClass	(nModuleId);
	if (m != 0){
		return m->myPropertyGet->exist(nId);
	}
	return 0;
}

bool     memory_class::existPropertySet			(int nModuleId, int nId)
{
	class_ *m = findClass	(nModuleId);
	if (m != 0){
		return m->myPropertySet->exist(nId);
	}
	return 0;
}

bool 		memory_class::existMethod				(int nId, const char *acMethod)
{
	class_ *m = findClass	(nId);
	if (m != 0){
		return m->mySub->exist(m->mySub->getId(m->acName, acMethod));
	}
	return false;
}

/*
bool 		memory_class::hasMethodWithSignature				(int nId, const char *acSignature)
{
	class_ *m = findClass	(nId);
	if (m != 0){
		return m->mySub->hasSubWithSignature(m->acName, acSignature);
	}
	return false;
}
*/
bool 		memory_class::existPropertyGet				(int nId, const char *acProperty)
{
	class_ *m = findClass	(nId);
	if (m != 0){
		return m->myPropertyGet->exist(m->myPropertyGet->getId(m->acName, acProperty));
	}
	return false;
}

bool 		memory_class::existPropertySet				(int nId, const char *acProperty)
{
	class_ *m = findClass	(nId);
	if (m != 0){
		return m->myPropertySet->exist(m->myPropertySet->getId(m->acName, acProperty));
	}
	return false;
}

memory_sub *memory_class::getMethods				(int nId)
{
	class_ *m = findClass	(nId);
	if (m != 0){
		return m->mySub;
	}
	return 0;
}

memory_sub *memory_class::getPropertiesGet				(int nId)
{
	class_ *m = findClass	(nId);
	if (m != 0){
		return m->myPropertyGet;
	}
	return 0;
}

memory_sub *memory_class::getPropertiesSet				(int nId)
{
	class_ *m = findClass	(nId);
	if (m != 0){
		return m->myPropertySet;
	}
	return 0;
}

memory_sub *memory_class::getMethods				(const char *acClassName)
{
	class_ *m = findClass	(getId(acClassName));
	if (m != 0){
		return m->mySub;
	}
	return 0;
}

memory_sub *memory_class::getPropertiesGet				(const char *acClassName)
{
	class_ *m = findClass	(getId(acClassName));
	if (m != 0){
		return m->myPropertyGet;
	}
	return 0;
}

memory_sub *memory_class::getPropertiesSet				(const char *acClassName)
{
	class_ *m = findClass	(getId(acClassName));
	if (m != 0){
		return m->myPropertySet;
	}
	return 0;
}

bool 		memory_class::exist				(const char *acName)
{
	return exist	(getId(acName));
}

bool 		memory_class::existStatic				(const char *acName)
{
	return existStatic	(getId(acName));
}

char     *memory_class::getSuffixMethod			(int nClassId, int nId)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){
		return m->mySub->getSuffix(nId);
	}
	return 0;
}

char     *memory_class::getSuffixPropertyGet			(int nClassId, int nId)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){
		return m->myPropertyGet->getSuffix(nId);
	}
	return 0;
}

char     *memory_class::getSuffixPropertySet			(int nClassId, int nId)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){
		return m->myPropertySet->getSuffix(nId);
	}
	return 0;
}

char     *memory_class::getName			(int nId)
{
	class_ *m = findClass	(nId);
	if (m != 0){
		return m->acName;
	}
	return 0;
}

char     *memory_class::getParentName			(int nId)
{
	class_ *m = findClass	(nId);
	if (m != 0){
		return m->acExtendName;
	}
	return 0;
}

char *memory_class::getNameMethod			(int nClassId, int nId)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){
		return m->mySub->getName(nId);
	}
	return 0;
}

char *memory_class::getNamePropertyGet			(int nClassId, int nId)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){
		return m->myPropertyGet->getName(nId);
	}
	return 0;
}

char *memory_class::getNamePropertySet			(int nClassId, int nId)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){
		return m->myPropertySet->getName(nId);
	}
	return 0;
}

char *memory_class::getRealNameMethod			(int nClassId, int nId)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){
		return m->mySub->getRealName(nId);
	}
	return 0;
}

char *memory_class::getSignatureMethod			(int nClassId, int nId)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){
		return m->mySub->getSignature(nId);
	}
	return 0;
}


int     memory_class::getPcodePos			(int nId)
{
	class_ *m = findClass	(nId);
	if (m != 0){
		return m->pc_pos;
	}
	return 0;
}

int     memory_class::getPcodeLen			(int nId)
{
	class_ *m = findClass	(nId);
	if (m != 0){
		return m->pc_len;
	}
	return 0;
}

int     memory_class::getPcodePosMethod			(int nClassId, int nId)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){
		return m->mySub->getPcodePos(nId);
	}
	return 0;
}

int     memory_class::getPcodeLenMethod			(int nClassId, int nId)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){
		return m->mySub->getPcodeLen(nId);
	}
	return 0;
}

int     memory_class::getPcodePosPropertyGet			(int nClassId, int nId)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){
		return m->myPropertyGet->getPcodePos(nId);
	}
	return 0;
}

int     memory_class::getPcodePosPropertySet			(int nClassId, int nId)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){
		return m->myPropertySet->getPcodePos(nId);
	}
	return 0;
}

int     memory_class::getTokenPosMethod			(int nClassId, int nId)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){

		return m->mySub->getTokenPos(nId);
	}
	return false;
}

int     memory_class::getTokenPosPropertyGet			(int nClassId, int nId)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){

		return m->myPropertyGet->getTokenPos(nId);
	}
	return false;
}

int     memory_class::getTokenPosPropertySet			(int nClassId, int nId)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){

		return m->myPropertySet->getTokenPos(nId);
	}
	return false;
}

int     memory_class::getScopeMethod			(int nClassId, int nId)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){

		return m->mySub->getScope(nId);
	}
	return false;
}

int     memory_class::getScopePropertyGet			(int nClassId, int nId)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){

		return m->myPropertyGet->getScope(nId);
	}
	return false;
}

int     memory_class::getScopePropertySet			(int nClassId, int nId)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){

		return m->myPropertySet->getScope(nId);
	}
	return false;
}

bool     memory_class::isStaticMethod			(int nClassId, int nId)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){

		return m->mySub->isStatic(nId);
	}
	return false;
}

int			memory_class::getId					()
{
	return (*it[idx])->nId;
}

int			memory_class::getIdMethod					()
{
	class_ *m = findClass	(getId());
	if (m != 0){
			return m->mySub->getId();
	}
	return 0;
}

int			memory_class::getIdPropertyGet					()
{
	class_ *m = findClass	(getId());
	if (m != 0){
			return m->myPropertyGet->getId();
	}
	return 0;
}

int			memory_class::getIdPropertySet					()
{
	class_ *m = findClass	(getId());
	if (m != 0){
			return m->myPropertySet->getId();
	}
	return 0;
}

int memory_class::getCountMethod(int nId)
{
	class_ *m = findClass	(nId);
	if (m != 0){
			return m->nCountMethod;
	}
	return 0;
}

int memory_class::getCountPropertyGet(int nId)
{
	class_ *m = findClass	(nId);
	if (m != 0){
			return m->nCountPropertyGet;
	}
	return 0;
}

int memory_class::getCountPropertySet(int nId)
{
	class_ *m = findClass	(nId);
	if (m != 0){
			return m->nCountPropertySet;
	}
	return 0;
}

int memory_class::getParentId(int nId)
{
	class_ *m = findClass	(nId);
	if (m != 0){
			return m->nExtend;
	}
	return 0;
}

int			memory_class::getParentId					(const char *acName)
{
	if (list_class2.contains(acName)){
		return list_class2[acName]->nExtend;
	}

	return -1;
}

int			memory_class::getId					(const char *acName)
{
	if (list_class2.contains(acName)){
		return list_class2[acName]->nId;
	}

	return -1;
}

int			memory_class::getIdMethod					(int nClassId, const char *acMethod)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){
		return m->mySub->getId(m->acName, acMethod);
	}
	return -1;
}

int			memory_class::getIdPropertyGet					(int nClassId, const char *acProperty)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){
		return m->myPropertyGet->getId(m->acName, acProperty);
	}
	return -1;
}

int			memory_class::getIdPropertySet					(int nClassId, const char *acProperty)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){
		return m->myPropertySet->getId(m->acName, acProperty);
	}
	return -1;
}

int			memory_class::getIdMethod					(const char *acName, const char *acMethod)
{
	class_ *m = findClass	(getId(acName));
	if (m != 0){
		return m->mySub->getId(m->acName, acMethod);
	}
	return -1;
}

int			memory_class::getIdPropertyGet					(const char *acName, const char *acProperty)
{
	class_ *m = findClass	(getId(acName));
	if (m != 0){
		return m->myPropertyGet->getId(m->acName, acProperty);
	}
	return -1;
}

int			memory_class::getIdPropertySet					(const char *acName, const char *acProperty)
{
	class_ *m = findClass	(getId(acName));
	if (m != 0){
		return m->myPropertySet->getId(m->acName, acProperty);
	}
	return -1;
}

pcode *memory_class::getPcode()
{
	return (*it[idx])->myPcode;
}
/*
pcode *memory_class::getPcodeStatic() // static methods
{
  class_ *m = findClass	(getId());
	if (m != 0){
			return m->myStatic->getPcode();
	}
	return 0;
}
*/
pcode *memory_class::getPcodeMethod()
{
	class_ *m = findClass	(getId());
	if (m != 0){
			return m->mySub->getPcode();
	}
	return 0;
}

pcode *memory_class::getPcodePropertyGet()
{
	class_ *m = findClass	(getId());
	if (m != 0){
			return m->myPropertyGet->getPcode();
	}
	return 0;
}

pcode *memory_class::getPcodePropertySet()
{
	class_ *m = findClass	(getId());
	if (m != 0){
			return m->myPropertySet->getPcode();
	}
	return 0;
}

pcode *memory_class::getPcode(int nId)
{
	class_ *m = findClass	(nId);
	if (m != 0){
			return m->myPcode;
	}
	return 0;
}

pcode *memory_class::getClassStaticPcode(int nId) // static scope of class --> one block  
{
	class_ *m = findClass	(nId);
	if (m != 0){
			return m->myClassStaticPcode;
	}
	return 0;
}

pcode *memory_class::getPcode(const char *acName)
{
	return getPcode(getId(acName));
}

pcode *memory_class::getPcodeMethod(int nClassId, int nId)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){
			return m->mySub->getPcode(nId);
	}
	return 0;
}

pcode *memory_class::getPcodePropertyGet(int nClassId, int nId)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){
			return m->myPropertyGet->getPcode(nId);
	}
	return 0;
}

pcode *memory_class::getPcodePropertySet(int nClassId, int nId)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){
			return m->myPropertySet->getPcode(nId);
	}
	return 0;
}

bool memory_class::findClass			(int nId, char **acName, pcode **myPcode)
{
	class_ *m = findClass	(nId);
	if (m != 0){
		*acName = m->acName;
		*myPcode = m->myPcode;
		return true;

	}
	return false;
}

class_ *memory_class::findClass			(const char *acClassName)
{
	return findClass	(getId(acClassName));
}

pcode *memory_class::getPcodeMethod(const char *acName, const char *acMethod)
{
	return getPcodeMethod				(getId(acName), getIdMethod(acName, acMethod));
}

pcode *memory_class::getPcodePropertyGet(const char *acName, const char *acProperty)
{
	return getPcodePropertyGet				(getId(acName), getIdPropertyGet(acName, acProperty));
}

pcode *memory_class::getPcodePropertySet(const char *acName, const char *acProperty)
{
	return getPcodePropertySet				(getId(acName), getIdPropertySet(acName, acProperty));
}

bool		memory_class::isCachedConstructor(int nClassId, int nId)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){
		return m->mySub->isCached(nId);
	}
	return false;
}

bool		memory_class::isCachedDestructor(int nClassId, int nId)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){
		return m->mySub->isCached(nId);
	}
	return false;
}

bool		memory_class::isCachedMethod(int nClassId, int nId)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){
		return m->mySub->isCached(nId);
	}
	return false;
}

bool		memory_class::isCachedPropertyGet(int nClassId, int nId)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){
		return m->myPropertyGet->isCached(nId);
	}
	return false;
}

bool		memory_class::isCachedPropertySet(int nClassId, int nId)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){
		return m->myPropertySet->isCached(nId);
	}
	return 0;
}

char   *memory_class::typeMethod				(int nClassId, int nId)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){
		return m->mySub->type(nId);
	}
	return 0;
}

char   *memory_class::typePropertyGet				(int nClassId, int nId)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){
		return m->myPropertyGet->type(nId);
	}
	return 0;
}

char   *memory_class::typePropertySet				(int nClassId, int nId)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){
		return m->myPropertySet->type(nId);
	}
	return 0;
}

char   *memory_class::typeMethod				(const char *acName, const char *acMethod)
{
	return typeMethod				(getId(acName), getIdMethod(acName, acMethod));
}

char   *memory_class::typePropertyGet				(const char *acName, const char *acProperty)
{
	return typePropertyGet			(getId(acName), getIdPropertyGet(acName, acProperty));
}

char   *memory_class::typePropertySet				(const char *acName, const char *acProperty)
{
	return typePropertySet			(getId(acName), getIdPropertySet(acName, acProperty));
}

bool		memory_class::addThrowMethod(int nClassId, int nId, const char *acType)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){

		return m->mySub->addThrow(nId, acType);

	}
	return false;
}

bool		memory_class::addThrowMethod(const char *acName, const char *acMethod, const char *acType)
{
	class_ *m = findClass	(getId(acName));
	if (m != 0){

		return m->mySub->addThrow(acName, acMethod, acType);

	}
	return false;
}

bool		memory_class::firstThrowMethod	(int nClassId, int nId, const char **acType)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){

		return m->mySub->firstThrow(nId, acType);

	}
	return false;
}

bool		memory_class::nextThrowMethod	(int nClassId, int nId, const char **acType)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){

		return m->mySub->nextThrow(nId, acType);

	}
	return false;
}

bool		memory_class::hasThrowMethod	(int nClassId, int nId, const char *acType)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){

		return m->mySub->hasThrow(nId, acType);

	}
	return false;
}

bool		memory_class::addParameterMethod(int nClassId, int nId, const char *acName, const char *acType, int nParameterCall, bool bOptional, bool bDefault, bool bParamArray, t_array *a, defaultvalue *defval, int *nParamId)
{

	class_ *m = findClass	(nClassId);
	if (m != 0){

		return m->mySub->addParameter(nId, acName, acType, nParameterCall, bOptional, bDefault, bParamArray, a, defval, nParamId);

	}
	return false;
}

bool		memory_class::firstParameterMethod	(int nClassId, int nId, const char **acName, const char **acType, int *nParameterCall, bool *bOptional, bool *bDefault, bool *bParamArray, t_array **a, defaultvalue **defval, int *nParamId)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){

		return m->mySub->firstParameter(nId, acName, acType, nParameterCall, bOptional, bDefault, bParamArray, a, defval, nParamId);

	}
	return false;
}

bool		memory_class::nextParameterMethod	(int nClassId, int nId, const char **acName, const char **acType, int *nParameterCall, bool *bOptional, bool *bDefault, bool *bParamArray, t_array **a, defaultvalue **defval, int *nParamId)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){

		return m->mySub->nextParameter(nId, acName, acType, nParameterCall, bOptional, bDefault, bParamArray, a, defval, nParamId);

	}
	return false;
}

bool		memory_class::lastParameterMethod	(int nClassId, int nId, const char **acName, const char **acType, int *nParameterCall, bool *bOptional, bool *bDefault, bool *bParamArray, t_array **a, defaultvalue **defval, int *nParamId)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){

		return m->mySub->lastParameter(nId, acName, acType, nParameterCall, bOptional, bDefault, bParamArray, a, defval, nParamId);

	}
	return false;
}

bool		memory_class::prevParameterMethod	(int nClassId, int nId, const char **acName, const char **acType, int *nParameterCall, bool *bOptional, bool *bDefault, bool *bParamArray, t_array **a, defaultvalue **defval, int *nParamId)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){

		return m->mySub->prevParameter(nId, acName, acType, nParameterCall, bOptional, bDefault, bParamArray, a, defval, nParamId);

	}
	return false;
}

bool		memory_class::getParameterMethod	(int nClassId, int nId, const char *acName_, const char **acType, int *nParameterCall, bool *bOptional, bool *bDefault, bool *bParamArray, t_array **a, defaultvalue **defval, int *nParamId)
{	
	class_ *m = findClass	(nClassId);
	if (m != 0){

		return m->mySub->getParameter(nId, acName_, acType, nParameterCall, bOptional, bDefault, bParamArray, a, defval, nParamId);

	}
	return false;
}

bool		memory_class::hasParameterMethod	(int nClassId, int nId, const char *acName_)
{	
	class_ *m = findClass	(nClassId);
	if (m != 0){

		return m->mySub->hasParameter(nId, acName_);

	}
	return false;
}

bool		memory_class::findParameterMethod	(int nClassId, int nMethodId, int nId, const char **acModule, const char **acSub, const char **acName)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){
		return m->mySub->findParameter(nMethodId, nId, acModule, acSub, acName);
	}
	return false;
}

int		memory_class::getParameterCountMethod				(int nClassId, int nId)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){
			return m->mySub->getParameterCount(nId);
	}
	return false;
}

bool		memory_class::addParameterPropertySet(int nClassId, int nId, const char *acName, const char *acType, int nParameterCall, bool bOptional, bool bDefault, bool bParamArray, t_array *a, defaultvalue *defval, int *nParamId)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){

		return m->myPropertySet->addParameter(nId, acName, acType, nParameterCall, bOptional, bDefault, bParamArray, a, defval, nParamId);

	}
	return false;
}

bool		memory_class::firstParameterPropertySet	(int nClassId, int nId, const char **acName, const char **acType, int *nParameterCall, bool *bOptional, bool *bDefault, bool *bParamArray, t_array **a, defaultvalue **defval, int *nParamId)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){

		return m->myPropertySet->firstParameter(nId, acName, acType, nParameterCall, bOptional, bDefault, bParamArray, a, defval, nParamId);

	}
	return false;
}

bool		memory_class::nextParameterPropertySet	(int nClassId, int nId, const char **acName, const char **acType, int *nParameterCall, bool *bOptional, bool *bDefault, bool *bParamArray, t_array **a, defaultvalue **defval, int *nParamId)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){

		return m->myPropertySet->nextParameter(nId, acName, acType, nParameterCall, bOptional, bDefault, bParamArray, a, defval, nParamId);

	}
	return false;
}

bool		memory_class::lastParameterPropertySet	(int nClassId, int nId, const char **acName, const char **acType, int *nParameterCall, bool *bOptional, bool *bDefault, bool *bParamArray, t_array **a, defaultvalue **defval, int *nParamId)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){

		return m->myPropertySet->lastParameter(nId, acName, acType, nParameterCall, bOptional, bDefault, bParamArray, a, defval, nParamId);

	}
	return false;
}

bool		memory_class::prevParameterPropertySet	(int nClassId, int nId, const char **acName, const char **acType, int *nParameterCall, bool *bOptional, bool *bDefault, bool *bParamArray, t_array **a, defaultvalue **defval, int *nParamId)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){

		return m->myPropertySet->prevParameter(nId, acName, acType, nParameterCall, bOptional, bDefault, bParamArray, a, defval, nParamId);

	}
	return false;
}

bool		memory_class::getParameterPropertySet	(int nClassId, int nId, const char *acName_, const char **acType, int *nParameterCall, bool *bOptional, bool *bDefault, bool *bParamArray, t_array **a, defaultvalue **defval, int *nParamId)
{	
	class_ *m = findClass	(nClassId);
	if (m != 0){

		return m->myPropertySet->getParameter(nId, acName_, acType, nParameterCall, bOptional, bDefault, bParamArray, a, defval, nParamId);

	}
	return false;
}

bool		memory_class::hasParameterPropertySet	(int nClassId, int nId, const char *acName_)
{	
	class_ *m = findClass	(nClassId);
	if (m != 0){

		return m->myPropertySet->hasParameter(nId, acName_);

	}
	return false;
}

bool		memory_class::findParameterPropertySet	(int nClassId, int nMethodId, int nId, const char **acModule, const char **acSub, const char **acName)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){
		return m->myPropertySet->findParameter(nMethodId, nId, acModule, acSub, acName);
	}
	return false;
}

int		memory_class::getParameterCountPropertySet				(int nClassId, int nId)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){
			return m->myPropertySet->getParameterCount(nId);
	}
	return false;
}

bool		memory_class::registered				(int nId)
{
	class_ *m = findClass	(nId);
	if (m != 0){
			return m->bRegistered;
	}
	return false;
}

bool		memory_class::registered				(const char *acName)
{
	return registered(getId(acName));
}

bool		memory_class::registeredMethod				(int nClassId, int nId)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){

		return m->mySub->registered(nId);

	}
	return false;
}

bool		memory_class::registeredPropertyGet				(int nClassId, int nId)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){

		return m->myPropertyGet->registered(nId);

	}
	return false;
}

bool		memory_class::registeredPropertySet				(int nClassId, int nId)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){

		return m->myPropertySet->registered(nId);

	}
	return false;
}

bool		memory_class::registeredMethod				(const char *acName, const char *acMethod)
{
	class_ *m = findClass	(getId(acName));
	if (m != 0){

		return m->mySub->registered(acName, acMethod);

	}
	return false;
}

bool		memory_class::registeredPropertyGet				(const char *acName, const char *acProperty)
{
	class_ *m = findClass	(getId(acName));
	if (m != 0){

		return m->myPropertyGet->registered(acName, acProperty);

	}
	return false;
}

bool		memory_class::registeredPropertySet				(const char *acName, const char *acProperty)
{
	class_ *m = findClass	(getId(acName));
	if (m != 0){

		return m->myPropertySet->registered(acName, acProperty);

	}
	return false;
}

bool 		memory_class::pcodeBuilt				(int nId)
{
	class_ *m = findClass	(nId);
	if (m != 0){
			return m->bPcodeBuilt;
	}
	return false;
}

bool 		memory_class::pcodeBuilt				(const char *acName)
{
	return pcodeBuilt(getId(acName));
}

bool 		memory_class::pcodeBuiltMethod				(const char *acName, const char *acMethod)
{
	class_ *m = findClass	(getId(acName));
	if (m != 0){

		return m->mySub->pcodeBuilt(acName, acMethod);

	}
	return false;
}

bool 		memory_class::pcodeBuiltPropertyGet				(const char *acName, const char *acProperty)
{
	class_ *m = findClass	(getId(acName));
	if (m != 0){

		return m->myPropertyGet->pcodeBuilt(acName, acProperty);

	}
	return false;
}

bool 		memory_class::pcodeBuiltPropertySet				(const char *acName, const char *acProperty)
{
	class_ *m = findClass	(getId(acName));
	if (m != 0){

		return m->myPropertySet->pcodeBuilt(acName, acProperty);

	}
	return false;
}

void		memory_class::setPcodeBuilt				(int nId, bool b)
{
	class_ *m = findClass	(nId);
	if (m != 0){
			m->bPcodeBuilt = b;
	}
}

void		memory_class::setPcodeBuilt				(const char *acName, bool b)
{
	class_ *m = findClass	(getId(acName));
	if (m != 0){
			m->bPcodeBuilt = b;
	}
}

void		memory_class::setPcodeBuiltMethod				(const char *acName, const char *acMethod, bool b)
{
	class_ *m = findClass	(getId(acName));
	if (m != 0){

		m->mySub->setPcodeBuilt(acName, acMethod, b);

	}
}

void		memory_class::setPcodeBuiltPropertyGet				(const char *acName, const char *acProperty, bool b)
{
	class_ *m = findClass	(getId(acName));
	if (m != 0){

		m->myPropertyGet->setPcodeBuilt(acName, acProperty, b);

	}
}

void		memory_class::setPcodeBuiltPropertySet				(const char *acName, const char *acProperty, bool b)
{
	class_ *m = findClass	(getId(acName));
	if (m != 0){

		m->myPropertySet->setPcodeBuilt(acName, acProperty, b);

	}
}

bool 		memory_class::pcodeBuiltMethod				(int nClassId, int nId)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){
			return m->mySub->pcodeBuilt(nId);
	}
	return false;
}

bool 		memory_class::pcodeBuiltPropertyGet				(int nClassId, int nId)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){
			return m->myPropertyGet->pcodeBuilt(nId);
	}
	return false;
}

bool 		memory_class::pcodeBuiltPropertySet				(int nClassId, int nId)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){
			return m->myPropertySet->pcodeBuilt(nId);
	}
	return false;
}

void		memory_class::setPcodeBuiltMethod				(int nClassId, int nId, bool b)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){
			m->mySub->setPcodeBuilt(nId, b);
	}
}

void		memory_class::setPcodeBuiltPropertyGet				(int nClassId, int nId, bool b)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){
			m->myPropertyGet->setPcodeBuilt(nId, b);
	}
}

void		memory_class::setPcodeBuiltPropertySet				(int nClassId, int nId, bool b)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){
			m->myPropertySet->setPcodeBuilt(nId, b);
	}
}

void memory_class::registerCallMethod(int nClassId, int nId, pcode *pcodeCall, int nPcodePos)//, int nReturnPcodePos)
{

	class_ *m = findClass	(nClassId);
	if (m != 0){
		m->mySub->registerCall(nId, pcodeCall, nPcodePos);//, nReturnPcodePos);
	}
}

void memory_class::changeRegisterCallMethod(pcode *p_old, pcode *pcodeCall, int nPcodePos)
{
  if (first()){
    do {
      int nClassId = getId();

	    class_ *m = findClass	(nClassId);
	    if (m != 0){
		    m->mySub->changeRegisterCall(p_old, pcodeCall, nPcodePos);
	    }

    } while (next());
  }

}

void memory_class::changeRegisterCallPropertyGet(pcode *p_old, pcode *pcodeCall, int nPcodePos)
{
  changeRegisterCallMethod(p_old, pcodeCall, nPcodePos);
}

void memory_class::changeRegisterCallPropertySet(pcode *p_old, pcode *pcodeCall, int nPcodePos)
{
  changeRegisterCallMethod(p_old, pcodeCall, nPcodePos);
}

void memory_class::registerCallPropertyGet(int nClassId, int nId, pcode *pcodeCall, int nPcodePos)//, int nReturnPcodePos)
{

	class_ *m = findClass	(nClassId);
	if (m != 0){
		m->myPropertyGet->registerCall(nId, pcodeCall, nPcodePos);//, nReturnPcodePos);
	}
}

void memory_class::registerCallPropertySet(int nClassId, int nId, pcode *pcodeCall, int nPcodePos)//, int nReturnPcodePos)
{

	class_ *m = findClass	(nClassId);
	if (m != 0){
		m->myPropertySet->registerCall(nId, pcodeCall, nPcodePos);//, nReturnPcodePos);
	}
}

bool		memory_class::firstPcodeCallMethod	(int nClassId, int nId, pcode **pcodeCall, int *nPcodeOffset)//, int *nReturnPcodePos)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){

		return m->mySub->firstPcodeCall(nId, pcodeCall, nPcodeOffset);//, nReturnPcodePos);

	}

	return false;
}

bool		memory_class::firstPcodeCallPropertyGet	(int nClassId, int nId, pcode **pcodeCall, int *nPcodeOffset)//, int *nReturnPcodePos)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){

		return m->myPropertyGet->firstPcodeCall(nId, pcodeCall, nPcodeOffset);//, nReturnPcodePos);

	}

	return false;
}

bool		memory_class::firstPcodeCallPropertySet	(int nClassId, int nId, pcode **pcodeCall, int *nPcodeOffset)//, int *nReturnPcodePos)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){

		return m->myPropertySet->firstPcodeCall(nId, pcodeCall, nPcodeOffset);//, nReturnPcodePos);

	}

	return false;
}

bool		memory_class::nextPcodeCallMethod	(int nClassId, int nId, pcode **pcodeCall, int *nPcodeOffset)//, int *nReturnPcodePos)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){

		return m->mySub->nextPcodeCall(nId, pcodeCall, nPcodeOffset);//, nReturnPcodePos);
	}
	return false;
}

bool		memory_class::nextPcodeCallPropertyGet	(int nClassId, int nId, pcode **pcodeCall, int *nPcodeOffset)//, int *nReturnPcodePos)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){

		return m->myPropertyGet->nextPcodeCall(nId, pcodeCall, nPcodeOffset);//, nReturnPcodePos);
	}
	return false;
}

bool		memory_class::nextPcodeCallPropertySet	(int nClassId, int nId, pcode **pcodeCall, int *nPcodeOffset)//, int *nReturnPcodePos)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){

		return m->myPropertySet->nextPcodeCall(nId, pcodeCall, nPcodeOffset);//, nReturnPcodePos);
	}
	return false;
}

bool		memory_class::first	(int _idx)
{
  idx = _idx;
  it[idx] = list_class.begin();
	class_ *c = (*it[idx]);
	return it[idx] != list_class.end();
}

bool		memory_class::gotoId	(int nClassId, int _idx)
{ 
  if (first(_idx)){
    do {
      if (nClassId == getId()){
        return true;
      }
    } while (next(_idx));
  }
  return false;
}

bool		memory_class::next	(int _idx)
{
  idx = _idx;
	++it[idx];
	return it[idx] != list_class.end();
}

bool		memory_class::firstMethod	(int _idx)
{
  idx = _idx;
	class_ *m = findClass	(getId());
	if (m != 0){
			bool b = m->mySub->first();
re:
      int nId = 0;
      if (b) nId = m->mySub->getId();

      if (b && (m->mySub->constructor(nId) || m->mySub->destructor(nId) || m->mySub->signal(nId) || m->mySub->slot(nId))){ b = m->mySub->next(); goto re; }
      return b;	
  }
	return false;
}

bool		memory_class::firstConstructor	(int _idx)
{
  idx = _idx;
	class_ *m = findClass	(getId());
	if (m != 0){
			bool b = m->mySub->first();
re:
      if (b && !m->mySub->constructor(m->mySub->getId())){ b = m->mySub->next(); goto re; }
      return b;
	}
	return false;
}

bool		memory_class::firstDestructor	(int _idx)
{
  idx = _idx;
	class_ *m = findClass	(getId());
	if (m != 0){
			bool b = m->mySub->first();
re:      
      if (b){
        if (!m->mySub->destructor(m->mySub->getId())){ 
          b = m->mySub->next(); 
          goto re; 
        }
      }
      return b;
	}
	return false;
}

bool		memory_class::firstSignal	(int _idx)
{
  idx = _idx;
	class_ *m = findClass	(getId());
	if (m != 0){
			bool b = m->mySub->first();
re:
      if (b && !m->mySub->signal(m->mySub->getId())){ b = m->mySub->next(); goto re; }
      return b;
	}
	return false;
}

bool		memory_class::firstSlot	(int _idx)
{
  idx = _idx;
	class_ *m = findClass	(getId());
	if (m != 0){
			bool b = false;
      b = m->mySub->first();
re:
      if (b && !m->mySub->slot(m->mySub->getId())){ b = m->mySub->next(); goto re; }
      return b;
	}
	return false;
}

bool		memory_class::firstPropertyGet	(int _idx)
{
  idx = _idx;
	class_ *m = findClass	(getId());
	if (m != 0){
			return m->myPropertyGet->first();
	}
	return false;
}

bool		memory_class::firstPropertySet	(int _idx)
{
  idx = _idx;
	class_ *m = findClass	(getId());
	if (m != 0){
			return m->myPropertySet->first();
	}
	return false;
}

bool		memory_class::nextMethod	(int _idx)
{
  idx = _idx;
	class_ *m = findClass	(getId());
	if (m != 0){
			bool b = false;
re:
      b = m->mySub->next();
      int nId = 0;
      
      if (b) nId = m->mySub->getId();
      if (b && (m->mySub->constructor(nId) || m->mySub->destructor(nId) || m->mySub->signal(nId) || m->mySub->slot(nId))) goto re;
      return b;	
	}
	return false;
}

bool		memory_class::nextConstructor	(int _idx)
{
  idx = _idx;
	class_ *m = findClass	(getId());
	if (m != 0){
			bool b = false;
re:
      b = m->mySub->next();
      if (b && !m->mySub->constructor(m->mySub->getId())) goto re;
      return b;
	}
	return false;
}

bool		memory_class::nextDestructor	(int _idx)
{
  idx = _idx;
	class_ *m = findClass	(getId());
	if (m != 0){
			bool b = false;
re:
      b = m->mySub->next();
      if (b && !m->mySub->destructor(m->mySub->getId())) goto re;
      return b;
	}
	return false;}

bool		memory_class::nextSignal	(int _idx)
{
  idx = _idx;
	class_ *m = findClass	(getId());
	if (m != 0){
			bool b = false;
re:
      b = m->mySub->next();
      if (b && !m->mySub->signal(m->mySub->getId())) goto re;
      return b;
	}
	return false;}

bool		memory_class::nextSlot	(int _idx)
{
  idx = _idx;
	class_ *m = findClass	(getId());
	if (m != 0){
			bool b = false;
re:
      b = m->mySub->next();
      if (b && !m->mySub->slot(m->mySub->getId())) goto re;
      return b;
	}
	return false;}

bool		memory_class::nextPropertyGet	(int _idx)
{
  idx = _idx;
	class_ *m = findClass	(getId());
	if (m != 0){
			return m->myPropertyGet->next();
	}
	return false;
}

bool		memory_class::nextPropertySet	(int _idx)
{
  idx = _idx;
	class_ *m = findClass	(getId());
	if (m != 0){
			return m->myPropertySet->next();
	}
	return false;
}

// ****

int		memory_class::addVar	(int nClassId, const char *acName, int nType, t_array *a, bool bStatic, int nScope, int nLStringLen, int nId)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){

		const char *acSub = "";				
		bool bByVal = false;
		bool bReference = false;
		bool bInit = true;    
    //int nTypeSize = 0;

    return m->vars->declare(m->acName, acSub, acName, nType, a, bByVal, bReference, bStatic, bInit, nScope, nLStringLen, nId);

	}
	return 0;
}

bool		memory_class::removeVar	(int nClassId, int nId)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){

    return m->vars->undeclare(nId);

	}
	return false;
}

bool		memory_class::firstVar	(int nClassId, const char **acName, int *nId, int *nType, t_array **a, bool *bStatic, int *nScope)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){


		if (m->vars->first()){
			*nId = m->vars->getId();

      *acName = m->vars->getName(*nId);
			*nType = m->vars->type(*nId);
			*a = m->vars->getArray(*nId);
			*bStatic = m->vars->isStatic(*nId);
			*nScope = m->vars->getScope(*nId);
			return true;

		}
	}
	return false;
}

bool		memory_class::nextVar	(int nClassId, const char **acName, int *nId, int *nType, t_array **a, bool *bStatic, int *nScope)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){

		if (m->vars->next()){
			*nId = m->vars->getId();

      *acName = m->vars->getName(*nId);
			*nType = m->vars->type(*nId);
			*a = m->vars->getArray(*nId);
			*bStatic = m->vars->isStatic(*nId);
			*nScope = m->vars->getScope(*nId);
			return true;

		}
	}
	return false;
}

bool		memory_class::getVar	(int nClassId, const char *acName, int *nId, int *nType, t_array **a, bool *bStatic, int *nScope)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){

		const char *acSub = "";				

		*nId = m->vars->getId(m->acName, acSub, acName);

		acName = m->vars->getName(*nId);
		*nType = m->vars->type(*nId);
		*a = m->vars->getArray(*nId);
		*bStatic = m->vars->isStatic(*nId);
		*nScope = m->vars->getScope(*nId);
		return true;

	}
	return false;
}

bool		memory_class::existVar	(int nClassId, const char *acName)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){

		const char *acSub = "";

		return m->vars->exist(m->acName, acSub, acName);

	}
	return false;
}

bool		memory_class::existVar	(const char *acModuleName, const char *acName)
{
  class_ *m = findClass	(getId(acModuleName));
	if (m != 0){

		const char *acSub = "";				

		return m->vars->exist(m->acName, acSub, acName);

	}
	return false;
}

bool		memory_class::findVar	(int nClassId, int nId, const char **acClass, const char **acMethod, const char **acVar)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){
		return m->vars->findVar(nId, acClass, acMethod, acVar);
	}
	return false;
}

int		memory_class::getIdVar	(int nClassId, const char *acName)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){

		const char *acSub = "";				
    
    do {
      int n =  m->vars->getId(m->acName, acSub, acName);
      if (n != -1) return n;

    } while ((m = findClass	(m->nExtend)) != 0);

	}
	return -1;
}

int		memory_class::getIdVar	(const char *acClassName, const char *acName)
{
  return getIdVar(getId(acClassName), acName);
}

int		memory_class::typeVar	(int nClassId, int nId)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){

		return m->vars->type(nId);

	}
	return false;
}

int		memory_class::typeVar	(const char *acClass_, const char *acName)
{
	class_ *m = findClass	(getId(acClass_));
	if (m != 0){

		const char *acSub = "";				

		int nId = m->vars->type(m->acName, acSub, acName);
    
      return nId;


	}
	return false;
}

int		memory_class::scopeVar	(int nClassId, int nId)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){

		return m->vars->getScope(nId);

	}
	return false;
}

int		memory_class::scopeVar	(const char *acClass_, const char *acName)
{
	class_ *m = findClass	(getId(acClass_));
	if (m != 0){

		const char *acSub = "";				

		return m->vars->getScope(m->vars->getId(m->acName, acSub, acName));

	}
	return false;
}

t_array *memory_class::getArrayVar	(int nClassId, int nId)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){

		return m->vars->getArray(nId);

	}
	return false;
}

t_array *memory_class::getArrayVar	(const char *acClass_, const char *acName)
{
	class_ *m = findClass	(getId(acClass_));
	if (m != 0){

		const char *acSub = "";				

    return m->vars->getArray( m->vars->getId(m->acName, acSub, acName) );

	}
	return false;
}

// ****

int		memory_class::addStaticVar	(int nClassId, const char *acName, int nType, t_array *a, bool bStatic, int nScope, int nLStringLen, int nId)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){

		const char *acSub = "";				
		bool bByVal = false;
		bool bReference = false;
    bool bInit = true;
    //int nTypeSize = 0;

		return m->static_vars->declare(m->acName, acSub, acName, nType, a, bByVal, bReference, bStatic, bInit, nScope, nLStringLen, nId);

	}
	return 0;
}

bool		memory_class::firstStaticVar	(int nClassId, const char **acName, int *nId, int *nType, t_array **a, bool *bStatic, int *nScope)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){


		if (m->static_vars->first()){
			*nId = m->static_vars->getId();

      *acName = m->static_vars->getName(*nId);
			*nType = m->static_vars->type(*nId);
			*a = m->static_vars->getArray(*nId);
			*bStatic = m->static_vars->isStatic(*nId);
			*nScope = m->static_vars->getScope(*nId);
			return true;

		}
	}
	return false;
}

bool		memory_class::nextStaticVar	(int nClassId, const char **acName, int *nId, int *nType, t_array **a, bool *bStatic, int *nScope)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){

		if (m->static_vars->next()){
			*nId = m->static_vars->getId();

      *acName = m->static_vars->getName(*nId);
			*nType = m->static_vars->type(*nId);
			*a = m->static_vars->getArray(*nId);
			*bStatic = m->static_vars->isStatic(*nId);
			*nScope = m->static_vars->getScope(*nId);
			return true;

		}
	}
	return false;
}

bool		memory_class::getStaticVar	(int nClassId, const char *acName, int *nId, int *nType, t_array **a, bool *bStatic, int *nScope)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){

		const char *acSub = "";				

		*nId = m->static_vars->getId(m->acName, acSub, acName);

		acName = m->static_vars->getName(*nId);
		*nType = m->static_vars->type(*nId);
		*a = m->static_vars->getArray(*nId);
		*bStatic = m->static_vars->isStatic(*nId);
		*nScope = m->static_vars->getScope(*nId);
		return true;

	}
	return false;
}

bool		memory_class::existStaticVar	(int nClassId, const char *acName)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){

		const char *acSub = "";				

		return m->static_vars->exist(m->acName, acSub, acName);

	}
	return false;
}

bool		memory_class::existStaticVar	(const char *acClassname, const char *acName)
{
	class_ *m = findClass	(getId(acClassname));
	if (m != 0){

		const char *acSub = "";				

		return m->static_vars->exist(m->acName, acSub, acName);

	}
	return false;
}

bool		memory_class::findStaticVar	(int nClassId, int nId, const char **acClass, const char **acMethod, const char **acVar)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){
		return m->static_vars->findVar(nId, acClass, acMethod, acVar);
	}
	return false;
}

int		memory_class::getIdStaticVar	(int nClassId, const char *acName)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){

		const char *acSub = "";				
    
    do {
      int n =  m->static_vars->getId(m->acName, acSub, acName);
      if (n != -1) return n;

    } while ((m = findClass	(m->nExtend)) != 0);

	}
	return -1;
}

int		memory_class::getIdStaticVar	(const char *acClassName, const char *acName)
{
  return getIdStaticVar(getId(acClassName), acName);
}

int		memory_class::typeStaticVar	(int nClassId, int nId)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){

		return m->static_vars->type(nId);

	}
	return false;
}

int		memory_class::typeStaticVar	(const char *acClass_, const char *acName)
{
	class_ *m = findClass	(getId(acClass_));
	if (m != 0){

		const char *acSub = "";				

		int nId = m->static_vars->type(m->acName, acSub, acName);
		return nId;

	}
	return false;
}

int		memory_class::scopeStaticVar	(int nClassId, int nId)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){

		return m->static_vars->getScope(nId);

	}
	return false;
}

int		memory_class::scopeStaticVar	(const char *acClass_, const char *acName)
{
	class_ *m = findClass	(getId(acClass_));
	if (m != 0){

		const char *acSub = "";				

		return m->vars->getScope(m->vars->getId(m->acName, acSub, acName));

	}
	return false;
}

t_array *memory_class::getArrayStaticVar	(int nClassId, int nId)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){

		return m->static_vars->getArray(nId);

	}
	return false;
}

t_array		*memory_class::getArrayStaticVar	(const char *acClass_, const char *acName)
{
	class_ *m = findClass	(getId(acClass_));
	if (m != 0){

		const char *acSub = "";				

    return m->static_vars->getArray( m->static_vars->getId(m->acName, acSub, acName) );

	}
	return false;
}

// ****

int		memory_class::addStaticCodeVar	(int nClassId, const char *acName, int nType, t_array *a, bool bStatic, int nScope)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){

		const char *acSub = "";				
		bool bByVal = false;
		bool bReference = false;
    bool bInit = true;
    int nTypeSize = 0;

		return m->staticCode_vars->declare(m->acName, acSub, acName, nType, a, bByVal, bReference, bStatic, bInit, nScope, nTypeSize, -1);

	}
	return 0;
}

bool		memory_class::firstStaticCodeVar	(int nClassId, const char **acName, int *nId, int *nType, t_array **a, bool *bStatic, int *nScope)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){


		if (m->staticCode_vars->first()){
			*nId = m->staticCode_vars->getId();

      *acName = m->staticCode_vars->getName(*nId);
			*nType = m->staticCode_vars->type(*nId);
			*a = m->staticCode_vars->getArray(*nId);
			*bStatic = m->staticCode_vars->isStatic(*nId);
			*nScope = m->staticCode_vars->getScope(*nId);
			return true;

		}
	}
	return false;
}

bool		memory_class::nextStaticCodeVar	(int nClassId, const char **acName, int *nId, int *nType, t_array **a, bool *bStatic, int *nScope)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){

		if (m->staticCode_vars->next()){
			*nId = m->staticCode_vars->getId();

      *acName = m->staticCode_vars->getName(*nId);
			*nType = m->staticCode_vars->type(*nId);
			*a = m->staticCode_vars->getArray(*nId);
			*bStatic = m->staticCode_vars->isStatic(*nId);
			*nScope = m->staticCode_vars->getScope(*nId);
			return true;

		}
	}
	return false;
}

bool		memory_class::getStaticCodeVar	(int nClassId, const char *acName, int *nId, int *nType, t_array **a, bool *bStatic, int *nScope)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){

		const char *acSub = "";				

		*nId = m->staticCode_vars->getId(m->acName, acSub, acName);

		acName = m->staticCode_vars->getName(*nId);
		*nType = m->staticCode_vars->type(*nId);
		*a = m->staticCode_vars->getArray(*nId);
		*bStatic = m->staticCode_vars->isStatic(*nId);
		*nScope = m->staticCode_vars->getScope(*nId);
		return true;

	}
	return false;
}

bool		memory_class::existStaticCodeVar	(int nClassId, const char *acName)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){

		const char *acSub = "";				

		return m->staticCode_vars->exist(m->acName, acSub, acName);

	}
	return false;
}

bool		memory_class::existStaticCodeVar	(const char *acClassname, const char *acName)
{
	class_ *m = findClass	(getId(acClassname));
	if (m != 0){

		const char *acSub = "";				

		return m->staticCode_vars->exist(m->acName, acSub, acName);

	}
	return false;
}

bool		memory_class::findStaticCodeVar	(int nClassId, int nId, const char **acClass, const char **acMethod, const char **acVar)
{
  static char ac[1024];

	class_ *m = findClass	(nClassId);
	if (m != 0){

    if (m->staticCode_vars->findVar(nId, acClass, acMethod, acVar)){
      *acMethod = "(class static code block)";
      return true;
    }
	}
	return false;
}

int		memory_class::getIdStaticCodeVar	(int nClassId, const char *acName)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){

		const char *acSub = "";				
    
    do {
      int n =  m->staticCode_vars->getId(m->acName, acSub, acName);
      if (n != -1) return n;

    } while ((m = findClass	(m->nExtend)) != 0);

	}
	return -1;
}

int		memory_class::getIdStaticCodeVar	(const char *acClassName, const char *acName)
{
  return getIdStaticCodeVar(getId(acClassName), acName);
}

int		memory_class::typeStaticCodeVar	(int nClassId, int nId)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){

		return m->staticCode_vars->type(nId);

	}
	return false;
}

int		memory_class::typeStaticCodeVar	(const char *acClass_, const char *acName)
{
	class_ *m = findClass	(getId(acClass_));
	if (m != 0){

		const char *acSub = "";				

		int nId = m->staticCode_vars->type(m->acName, acSub, acName);
		return nId;

	}
	return false;
}

int		memory_class::scopeStaticCodeVar	(int nClassId, int nId)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){

		return m->staticCode_vars->getScope(nId);

	}
	return false;
}

int		memory_class::scopeStaticCodeVar	(const char *acClass_, const char *acName)
{
	class_ *m = findClass	(getId(acClass_));
	if (m != 0){

		const char *acSub = "";				

		return m->vars->getScope(m->vars->getId(m->acName, acSub, acName));

	}
	return false;
}

t_array *memory_class::getArrayStaticCodeVar	(int nClassId, int nId)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){

		return m->staticCode_vars->getArray(nId);

	}
	return false;
}

t_array		*memory_class::getArrayStaticCodeVar	(const char *acClass_, const char *acName)
{
	class_ *m = findClass	(getId(acClass_));
	if (m != 0){

		const char *acSub = "";				

    return m->staticCode_vars->getArray( m->staticCode_vars->getId(m->acName, acSub, acName) );

	}
	return false;
}

// ****
int		memory_class::addMethodVar	(int nClassId, const char *acMethod, const char *acName, int nType, t_array *a, bool bStatic, int nScope, int nLStringLen, int nId)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){

		return m->mySub->addVar(nClassId, acMethod, acName, nType, a, false, nScope, nLStringLen, nId);

	}
	return 0;
}

bool		memory_class::removeMethodVar	(int nClassId, int nMethodId, int nId)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){

		return m->mySub->removeVar(nMethodId, nId);

	}
	return false;
}

bool		memory_class::firstMethodVar	(int nClassId, const char *acMethod, const char **acName, int *nId, int *nType, t_array **a, bool *bStatic, int *nScope)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){

		if (m->mySub->first()){
			*acName = m->mySub->getName();
			*nId = m->mySub->getId();
      *nType = m->mySub->typeVar(m->acName, acMethod, *nId);
			*a = m->mySub->getArrayVar(m->acName, acMethod, *nId);
      *bStatic = m->mySub->isStatic(*nId);
			*nScope = m->mySub->getScope(*nId);
			return true;

		}
	}
	return false;
}

bool		memory_class::nextMethodVar	(int nClassId, const char *acMethod, const char **acName, int *nId, int *nType, t_array **a, bool *bStatic, int *nScope)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){

		if (m->mySub->next()){
			*acName = m->mySub->getName();
			*nId = m->mySub->getId();

      *nType = m->mySub->typeVar(m->acName, acMethod, *nId);
			*a = m->mySub->getArrayVar(m->acName, acMethod, *nId);
      *bStatic = m->mySub->isStatic(*nId);
			*nScope = m->mySub->getScope(*nId);
			//*bMethod = m->mySub->isMethod();
			return true;

		}
	}
	return false;
}

bool		memory_class::getMethodVar	(int nClassId, const char *acMethod, const char *acName, int *nId, int *nType, t_array **a, bool *bStatic, int *nScope)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){

		*nId = m->mySub->getIdVar(m->acName, acMethod, acName);

		acName = m->mySub->getName(*nId);
    *nType = m->mySub->typeVar(m->acName, acMethod, *nId);
		*a = m->mySub->getArrayVar(m->acName, acMethod, *nId);
    *bStatic = m->mySub->isStatic(*nId);
		*nScope = m->mySub->getScope(*nId);
		return true;

	}
	return false;
}

bool		memory_class::existMethodVar	(int nClassId, const char *acMethod, const char *acName)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){

		return m->mySub->existVar(m->acName, acMethod, acName);

	}
	return false;
}

bool		memory_class::findMethodVar	(int nClassId, int nMethodId, int nId, const char **acClass, const char **acMethod, const char **acVar)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){
		return m->mySub->findVar(nMethodId, nId, acClass, acMethod, acVar);
	}
	return false;
}

int		memory_class::getIdMethodVar	(int nClassId, const char *acMethod, const char *acName)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){

    do {
      int n =  m->mySub->getIdVar(m->acName, acMethod, acName);
      if (n != -1) return n;

    } while ((m = findClass	(m->nExtend)) != 0);

	}
	return -1;
}

int		memory_class::getIdMethodVar	(const char *acClassName, const char *acMethod, const char *acName)
{
  return getIdMethodVar(getId(acClassName), acMethod, acName);
}

bool		memory_class::existMethodVar	(const char *acClass_, const char *acMethod, const char *acName)
{
	class_ *m = findClass	(getId(acClass_));
	if (m != 0){

		return m->mySub->existVar(m->acName, acMethod, acName);

	}
	return false;
}

bool		memory_class::isStaticMethodVar	(const char *acClass_, const char *acMethod, const char *acName)
{
	class_ *m = findClass	(getId(acClass_));
	if (m != 0){

		return m->mySub->isStaticVar(m->acName, acMethod, acName);

	}
	return false;
}

int		memory_class::typeMethodVar	(const char *acClass_, const char *acMethod, const char *acName)
{
	class_ *m = findClass	(getId(acClass_));
	if (m != 0){

		return m->mySub->typeVar(m->acName, acMethod, acName);

	}
	return false;
}

int		memory_class::typeMethodVar	(const char *acClass_, const char *acMethod, int nVar)
{
	class_ *m = findClass	(getId(acClass_));
	if (m != 0){

		return m->mySub->typeVar(m->acName, acMethod, nVar);

	}
	return false;
}

t_array *memory_class::getArrayMethodVar	(int nClassId, const char *acMethod, int nVar)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){

    return m->mySub->getArrayVar(m->acName, acMethod, nVar);

	}
	return false;
}

t_array *memory_class::getArrayMethodVar	(const char *acClass_, const char *acMethod, const char *acName)
{
	class_ *m = findClass	(getId(acClass_));
	if (m != 0){

    return m->mySub->getArrayVar( m->acName, acMethod, acName );

	}
	return false;
}

// ****

int		memory_class::addPropertyGetVar	(int nClassId, const char *acProperty, const char *acName, int nType, t_array *a, bool bProperty, int nScope, int nLStringLen, int nId)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){

		return m->myPropertyGet->addVar(nClassId, acProperty, acName, nType, a, false, nScope, nLStringLen, nId);

	}
	return 0;
}

int		memory_class::addPropertySetVar	(int nClassId, const char *acProperty, const char *acName, int nType, t_array *a, bool bProperty, int nScope, int nLStringLen, int nId)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){

		return m->myPropertySet->addVar(nClassId, acProperty, acName, nType, a, false, nScope, nLStringLen, nId);

	}
	return 0;
}

bool		memory_class::firstPropertyGetVar	(int nClassId, const char *acProperty, const char **acName, int *nId, int *nType, t_array **a, bool *bStatic, int *nScope)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){

		if (m->myPropertyGet->first()){
			*acName = m->myPropertyGet->getName();
			*nId = m->myPropertyGet->getId();
      *nType = m->myPropertyGet->typeVar(m->acName, acProperty, *nId);
			*a = m->myPropertyGet->getArrayVar(m->acName, acProperty, *nId);
      *bStatic = m->myPropertyGet->isStatic(*nId);
			*nScope = m->myPropertyGet->getScope(*nId);
			return true;

		}
	}
	return false;
}

bool		memory_class::firstPropertySetVar	(int nClassId, const char *acProperty, const char **acName, int *nId, int *nType, t_array **a, bool *bStatic, int *nScope)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){

		if (m->myPropertySet->first()){
			*acName = m->myPropertySet->getName();
			*nId = m->myPropertySet->getId();
      *nType = m->myPropertySet->typeVar(m->acName, acProperty, *nId);
			*a = m->myPropertySet->getArrayVar(m->acName, acProperty, *nId);
      *bStatic = m->myPropertySet->isStatic(*nId);
			*nScope = m->myPropertySet->getScope(*nId);
			return true;

		}
	}
	return false;
}

bool		memory_class::nextPropertyGetVar	(int nClassId, const char *acProperty, const char **acName, int *nId, int *nType, t_array **a, bool *bStatic, int *nScope)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){

    const char *acModule = "";

		if (m->myPropertyGet->next()){
			*acName = m->myPropertyGet->getName();
			*nId = m->myPropertyGet->getId();

      *nType = m->myPropertyGet->typeVar(m->acName, acProperty, *nId);
			*a = m->myPropertyGet->getArrayVar(m->acName, acProperty, *nId);
      *bStatic = m->myPropertyGet->isStatic(*nId);
			*nScope = m->myPropertyGet->getScope(*nId);
			return true;

		}
	}
	return false;
}

bool		memory_class::nextPropertySetVar	(int nClassId, const char *acProperty, const char **acName, int *nId, int *nType, t_array **a, bool *bStatic, int *nScope)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){

		if (m->myPropertySet->next()){
			*acName = m->myPropertySet->getName();
			*nId = m->myPropertySet->getId();

      *nType = m->myPropertySet->typeVar(m->acName, acProperty, *nId);
			*a = m->myPropertySet->getArrayVar(m->acName, acProperty, *nId);
      *bStatic = m->myPropertySet->isStatic(*nId);
			*nScope = m->myPropertySet->getScope(*nId);
			return true;

		}
	}
	return false;
}

bool		memory_class::getPropertyGetVar	(int nClassId, const char *acProperty, const char *acName, int *nId, int *nType, t_array **a, bool *bStatic, int *nScope)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){

		*nId = m->myPropertyGet->getIdVar(m->acName, acProperty, acName);

		acName = m->myPropertyGet->getName(*nId);
    *nType = m->myPropertyGet->typeVar(m->acName, acProperty, *nId);
		*a = m->myPropertyGet->getArrayVar(m->acName, acProperty, *nId);
    *bStatic = m->myPropertyGet->isStatic(*nId);
		*nScope = m->myPropertyGet->getScope(*nId);
		return true;

	}
	return false;
}

bool		memory_class::getPropertySetVar	(int nClassId, const char *acProperty, const char *acName, int *nId, int *nType, t_array **a, bool *bStatic, int *nScope)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){

		*nId = m->myPropertySet->getIdVar(m->acName, acProperty, acName);

		acName = m->myPropertySet->getName(*nId);
    *nType = m->myPropertySet->typeVar(m->acName, acProperty, *nId);
		*a = m->myPropertySet->getArrayVar(m->acName, acProperty, *nId);
    *bStatic = m->myPropertySet->isStatic(*nId);
		*nScope = m->myPropertySet->getScope(*nId);
		return true;

	}
	return false;
}

bool		memory_class::existPropertyGetVar	(int nClassId, const char *acProperty, const char *acName)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){

		return m->myPropertyGet->existVar(m->acName, acProperty, acName);

	}
	return false;
}

bool		memory_class::existPropertySetVar	(int nClassId, const char *acProperty, const char *acName)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){

		return m->myPropertySet->existVar(m->acName, acProperty, acName);

	}
	return false;
}

bool		memory_class::findPropertyGetVar	(int nClassId, int nMethodId, int nId, const char **acClass, const char **acMethod, const char **acVar)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){
		return m->myPropertyGet->findVar(nMethodId, nId, acClass, acMethod, acVar);
	}
	return false;
}

bool		memory_class::findPropertySetVar	(int nClassId, int nMethodId, int nId, const char **acClass, const char **acMethod, const char **acVar)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){
		return m->myPropertySet->findVar(nMethodId, nId, acClass, acMethod, acVar);
	}
	return false;
}

int		memory_class::getIdPropertyGetVar	(int nClassId, const char *acProperty, const char *acName)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){

    do {
      int n =  m->myPropertyGet->getIdVar(m->acName, acProperty, acName);
      if (n != -1) return n;

    } while ((m = findClass	(m->nExtend)) != 0);

	}
	return -1;
}

int		memory_class::getIdPropertySetVar	(int nClassId, const char *acProperty, const char *acName)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){

    do {
      int n =  m->myPropertySet->getIdVar(m->acName, acProperty, acName);
      if (n != -1) return n;

    } while ((m = findClass	(m->nExtend)) != 0);

	}
	return -1;
}

int		memory_class::getIdPropertyGetVar	(const char *acClassName, const char *acProperty, const char *acName)
{
  return getIdPropertyGetVar(getId(acClassName), acProperty, acName);
}

int		memory_class::getIdPropertySetVar	(const char *acClassName, const char *acProperty, const char *acName)
{
  return getIdPropertySetVar(getId(acClassName), acProperty, acName);
}

bool		memory_class::existPropertyGetVar	(const char *acClass_, const char *acProperty, const char *acName)
{
	class_ *m = findClass	(getId(acClass_));
	if (m != 0){

		return m->myPropertyGet->existVar(m->acName, acProperty, acName);

	}
	return false;
}

bool		memory_class::existPropertySetVar	(const char *acClass_, const char *acProperty, const char *acName)
{
	class_ *m = findClass	(getId(acClass_));
	if (m != 0){

		return m->myPropertySet->existVar(m->acName, acProperty, acName);

	}
	return false;
}

int		memory_class::typePropertyGetVar	(const char *acClass_, const char *acProperty, const char *acName)
{
	class_ *m = findClass	(getId(acClass_));
	if (m != 0){

		return m->myPropertyGet->typeVar(m->acName, acProperty, acName);

	}
	return false;
}

int		memory_class::typePropertyGetVar	(const char *acClass_, const char *acProperty, int nVar)
{
	class_ *m = findClass	(getId(acClass_));
	if (m != 0){

		return m->myPropertyGet->typeVar(m->acName, acProperty, nVar);

	}
	return false;
}

int		memory_class::typePropertySetVar	(const char *acClass_, const char *acProperty, const char *acName)
{
	class_ *m = findClass	(getId(acClass_));
	if (m != 0){

		return m->myPropertySet->typeVar(m->acName, acProperty, acName);

	}
	return false;
}

int		memory_class::typePropertySetVar	(const char *acClass_, const char *acProperty, int nVar)
{
	class_ *m = findClass	(getId(acClass_));
	if (m != 0){

		return m->myPropertySet->typeVar(m->acName, acProperty, nVar);

	}
	return false;
}

t_array *memory_class::getArrayPropertyGetVar	(int nClassId, const char *acProperty, int nVar)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){

    return m->myPropertyGet->getArrayVar(m->acName, acProperty, nVar);

	}
	return false;
}

t_array *memory_class::getArrayPropertyGetVar	(const char *acClass_, const char *acProperty, const char *acName)
{
	class_ *m = findClass	(getId(acClass_));
	if (m != 0){

    return m->myPropertyGet->getArrayVar( m->acName, acProperty, acName );

	}
	return false;
}

t_array *memory_class::getArrayPropertySetVar	(int nClassId, const char *acProperty, int nVar)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){

    return m->myPropertySet->getArrayVar( m->acName, acProperty, nVar );

	}
	return false;
}

t_array *memory_class::getArrayPropertySetVar	(const char *acClass_, const char *acProperty, const char *acName)
{
	class_ *m = findClass	(getId(acClass_));
	if (m != 0){

		return m->myPropertySet->getArrayVar(m->acName, acProperty, acName);

	}
	return false;
}
// ****

int		memory_class::addConst	(int nClassId, const char *acName, int nScope, int nId)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){

		const char *acSub = "";				

		return m->consts->declare(m->acName, acSub, acName, nScope, nId);

	}
	return 0;
}

bool		memory_class::firstConst	(int nClassId, const char **acName, int *nId, int *nScope)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){

		if (m->consts->first()){
			*nId = m->consts->getId();

			*acName = m->consts->getName(*nId);
			*nScope = m->consts->getScope(*nId);
			return true;

		}
	}
	return false;
}

bool		memory_class::nextConst	(int nClassId, const char **acName, int *nId, int *nScope)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){

		if (m->consts->next()){
			*nId = m->consts->getId();

			*acName = m->consts->getName(*nId);
			*nScope = m->consts->getScope(*nId);
			return true;

		}
	}
	return false;
}

bool		memory_class::getConst	(int nClassId, const char *acName, int *nId, int *nScope)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){

		const char *acSub = "";				

		*nId = m->consts->getId(m->acName, acSub, acName);
		acName = m->consts->getName(*nId);
		*nScope = m->consts->getScope(*nId);
		return true;

	}
	return false;
}

bool		memory_class::existConst	(const char *acClassName, const char *acName)
{
	class_ *m = findClass	(getId(acClassName));
	if (m != 0){

		const char *acSub = "";				

		return m->consts->exist(m->acName, acSub, acName);

	}
	return false;
}

bool		memory_class::existConst	(int nClassId, const char *acName)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){

		const char *acSub = "";				

		return m->consts->exist(m->acName, acSub, acName);

	}
	return false;
}

bool		memory_class::findConst	(int nClassId, int nId, const char **acClass, const char **acMethod, const char **acVar)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){
		return m->consts->findConst(nId, acClass, acMethod, acVar);
	}
	return false;
}

int		memory_class::getIdConst	(int nClassId, const char *acName)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){

		const char *acSub = "";				

    do {
      int n =  m->consts->getId(m->acName, acSub, acName);
      if (n != -1) return n;

    } while ((m = findClass	(m->nExtend)) != 0);

	}
	return -1;
}

int		memory_class::getIdConst	(const char *acClassName, const char *acName)
{
  return getIdConst(getId(acClassName), acName);
}

bool		memory_class::isPublicConst	(int nClassId, int nId)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){

		return m->consts->isPublic(nId);

	}
	return false;
}

bool		memory_class::isPublicConst	(int nClassId, const char *acName)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){

		const char *acSub = "";				

		return m->consts->exist(m->acName, acSub, acName);

	}
	return false;
}

// ****

bool		memory_class::functionMethod	(int nClassId, int nId)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){

    return m->mySub->function(nId);

	}
	return false;
}

// ****

bool		memory_class::constructorMethod	(int nClassId, int nId)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){

    return m->mySub->constructor(nId);

	}
	return false;
}


// ****

bool		memory_class::destructorMethod	(int nClassId, int nId)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){

    return m->mySub->destructor(nId);

	}
	return false;
}

// ****

int		memory_class::addMethodConst(int nClassId, const char *acMethod, const char *acName, int nId)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){

    int nScope = 0;

		int n = m->mySub->addConst(nClassId, acMethod, acName, nScope, nId); if (n > 0) return n;
		n = m->myPropertyGet->addConst(nClassId, acMethod, acName, nScope, nId); if (n > 0) return n;
		n = m->myPropertySet->addConst(nClassId, acMethod, acName, nScope, nId); if (n > 0) return n;

	}
	return 0;
}

bool		memory_class::firstMethodConst	(int nClassId, const char *acMethod, const char **acName)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){

		if (m->mySub->first()){
			*acName = m->mySub->getName();
			return true;

		}
	}
	return false;
}

bool		memory_class::nextMethodConst	(int nClassId, const char *acMethod, const char **acName)
{
  class_ *m = findClass	(nClassId);
	if (m != 0){

		if (m->mySub->next()){
			*acName = m->mySub->getName();
			return true;

		}
	}
	return false;
}

bool		memory_class::getMethodConst	(int nClassId, const char *acMethod, const char *acName)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){

		int nId = m->mySub->getIdConst(m->acName, acMethod, acName);

		acName = m->mySub->getName(nId);
		return true;

	}
  return false;
}

bool		memory_class::existMethodConst	(int nClassId, const char *acMethod, const char *acName)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){

		return m->mySub->existConst(m->acName, acMethod, acName);

	}
	return false;
}

bool		memory_class::existMethodConst	(const char *acModuleName, const char *acMethod, const char *acName)
{
	class_ *m = findClass	(getId(acModuleName));
	if (m != 0){

		return m->mySub->existConst(m->acName, acMethod, acName);

	}
	return false;
}

bool		memory_class::findMethodConst	(int nClassId, int nMethodId, int nId, const char **acClass, const char **acMethod, const char **acVar)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){
		return m->mySub->findConst(nMethodId, nId, acClass, acMethod, acVar);
	}
	return false;
}

bool		memory_class::findPropertyGetConst	(int nClassId, int nMethodId, int nId, const char **acClass, const char **acMethod, const char **acVar)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){
    return m->myPropertyGet->findConst(nMethodId, nId, acClass, acMethod, acVar);
	}
	return false;
}

bool		memory_class::findPropertySetConst	(int nClassId, int nMethodId, int nId, const char **acClass, const char **acMethod, const char **acVar)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){
		return m->myPropertySet->findConst(nMethodId, nId, acClass, acMethod, acVar);
	}
	return false;
}

int		memory_class::getIdMethodConst				(int nClassId, const char *acMethod, const char *acName)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){

    do {
      int n =  m->mySub->getIdConst(m->acName, acMethod, acName);
      if (n != -1) return n;

    } while ((m = findClass	(m->nExtend)) != 0);

	}
	return -1;
}

int		memory_class::getIdMethodConst				(const char *acModuleName, const char *acMethod, const char *acName)
{
  return getIdMethodConst(getId(acModuleName), acMethod, acName);
}

memory_const		*memory_class::getMethodConsts	(int nClassId, const char *acMethod)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){

		return m->mySub->getConsts(m->acName, acMethod, acMethod);

	}
	return 0;
}

memory_const		*memory_class::getMethodConsts	(const char *acModuleName, const char *acMethod)
{
	return getMethodConsts(getId(acModuleName), acMethod);
}




void memory_class::registerCatch(int nClassId, pcode *pcodeCatch, int nCatchType, int nPcodePos, int nCatchPcodePos)
{

	class_ *m = findClass	(nClassId);
	if (m != 0){

		if (m->nPcodeCatchCounter == MAX_SUB_USED){
			classError("too many sub catches");
			return;
		}

		m->pcodeCatch[m->nPcodeCatchCounter] = pcodeCatch;
		m->nPcodeCatch[m->nPcodeCatchCounter] = nPcodePos;
		m->nCatchType[m->nPcodeCatchCounter] = nCatchType;
		m->nCatchPcodePos[m->nPcodeCatchCounter++] = nCatchPcodePos;
		//m->nReturnPcodePos[m->nPcodeCatchCounter++] = nReturnPcodePos;

	}
}

bool		memory_class::firstPcodeCatch	(int nClassId, pcode **pcodeCatch, int *nCatchType, int *nPcodeOffset, int *nCatchPcodePos)//, int *nReturnPcodePos)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){

		m->nPcodeCatchIterator = 0;
		if (m->nPcodeCatchIterator != m->nPcodeCatchCounter){
			*pcodeCatch = m->pcodeCatch[m->nPcodeCatchIterator];
			*nPcodeOffset = m->nPcodeCatch[m->nPcodeCatchIterator];
			*nCatchType = m->nCatchType[m->nPcodeCatchIterator];
//			*nReturnPcodePos = m->nReturnPcodePos[m->nPcodeCatchIterator];
			return true;
		}

	}

	return false;
}

bool		memory_class::nextPcodeCatch	(int nClassId, pcode **pcodeCatch, int *nCatchType, int *nPcodeOffset, int *nCatchPcodePos)//, int *nReturnPcodePos)
{
	class_ *m = findClass	(nClassId);
	if (m != 0){

		m->nPcodeCatchIterator++;

		if (m->nPcodeCatchIterator < m->nPcodeCatchCounter){
			*pcodeCatch = m->pcodeCatch[m->nPcodeCatchIterator];
			*nPcodeOffset = m->nPcodeCatch[m->nPcodeCatchIterator];
			*nCatchType = m->nCatchType[m->nPcodeCatchIterator];
//			*nReturnPcodePos = m->nReturnPcodePos[m->nPcodeCatchIterator];
			return true;
		}
	}
	return false;
}

