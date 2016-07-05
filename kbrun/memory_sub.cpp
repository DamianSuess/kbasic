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



#include "memory_sub.h"




memory_sub::memory_sub			()
{

	nIdCounter = 0;
}

memory_sub::~memory_sub		()
{

  QMap<int, sub*>::Iterator it2;
  for ( it2 = list_sub.begin(); it2 != list_sub.end(); ++it2 ) {
    sub *m = *it2;

    delete m->vars;
    delete m->consts;

    delete m;
  }

  list_sub.clear();
  list_sub2.clear();
  list_sub3.clear();
  list_sub4.clear();

  findSub(-99); // delete cache
}

// ****************************
// * bool subError(char *acsubError)
// *
// * description:
// * prints a sub error message
// *
// * interpreter_parameter:
// * char *acsubError = the error message to print
// *
// * return:
// * dummy
// ****************************
bool memory_sub::subError(char *acSubError)
{
	static char acText[1024];

	sprintf(acText, "\nsub error: %s\n", acSubError);
	CONSOLE printError(acText);
	return false;
}

sub	*memory_sub::findSub	(int nId)
{
  // * optimize
  static int _nId = -100;
  static sub *v = 0;
  static void *_this = 0;

  if (_nId == nId && _this == this){
    return v;
  }
  // *

	if (list_sub.contains(nId)){
    _nId = nId;
    _this = this;
    v = list_sub[nId];
		return v;		
	}	 
  _nId = -100;

	return 0;
}

char *memory_sub::getKeyFromRealNameAndFileAndLine(const char *acModule, const char *acRealName, const char *acFile, int nLine)
{
	static char acKey[2048];
	sprintf(acKey, "%s.%s.%s.%d", acModule, acRealName, acFile, nLine);
  // make case insensitive
  int n = strlen(acKey);
	for (unsigned int i = 0; i < n; i++) acKey[i] = toupper(acKey[i]);

	return acKey;
}

char *memory_sub::getKey(const char *acModule, const char *acName)
{
	static char acKey[1024];
	sprintf(acKey, "%s.%s", acModule, acName);
  // make case insensitive
  int n = strlen(acKey);
	for (unsigned int i = 0; i < n; i++) acKey[i] = toupper(acKey[i]);

	return acKey;
}

sub *memory_sub::newSub(
													const char *acModule,                           
                          int nModuleId,
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
												)
{
	sub *t = new sub();

  register int n = strlen(acModule);

	memcpy(t->acModule, acModule, n);
	t->acModule[n] = '\0';
  
  t->nModuleId = nModuleId;

  register int n2 = strlen(acRealName);

	memcpy(t->acRealName, acRealName, n2);
	t->acRealName[n2] = '\0';

  n = strlen(acName);

	memcpy(t->acName, acName, n);
	t->acName[n] = '\0';


  n -= n2;
	memcpy(t->acSignature, acName + n2, n);
	t->acSignature[n] = '\0';

  n = strlen(acReturnType);
	if (acReturnType != 0) memcpy(t->acReturnType, acReturnType, n);
	t->acReturnType[n] = '\0';

  n = strlen(acSuffix);
	if (acSuffix != 0) memcpy(t->acSuffix, acSuffix, n);
	t->acSuffix[n] = '\0';

  t->nId = nIdCounter;
	t->myPcode = myPcode;
  if (myPcode == 0){
    myPcode = myPcode;
  }
	t->bRegistered = true;
	t->bPcodeBuilt = false;
	t->nReturnSize = nReturnSize;
	t->nPcodeCallIterator = 0;
	t->nPcodeCallCounter = 0;
	t->nPcodeCatchIterator = 0;
	t->nPcodeCatchCounter = 0;

  t->bDeclare = bDeclare;

  n = strlen(acAlias);
	memcpy(t->acAlias, acAlias, n);
	t->acAlias[n] = '\0';

  n = strlen(acLib);
	memcpy(t->acLib, acLib, n);
	t->acLib[n] = '\0';

  n = strlen(acLibCallSignature);
	memcpy(t->acLibCallSignature, acLibCallSignature, n);
	t->acLibCallSignature[n] = '\0';

  t->bFunction = function;
	t->bConstructor = constructor;
	t->bDestructor = destructor;
	t->bSignal = signal;
	t->bSlot = slot;

  t->nParameterCounter = 0;
	t->nParameterIterator = 0;
	t->nThrowCounter = 0;
	t->nThrowIterator = 0;
	t->pc_pos = pc_pos;
	t->nScope = nScope;
	t->nTokenPos = nTokenPos;
	t->nTokenLinePos = nTokenLinePos;  
	t->bStatic = bStatic;
	t->bAbstract = bAbstract;

  n = strlen(acFile);
	if (acFile != 0) memcpy(t->acFile, acFile, n);
	t->acFile[n] = '\0';
	t->nLine = nLine;

	t->vars = new memory_variable();
	t->consts = new memory_const();
  
  return t;
}

int 		memory_sub::addSub			(
																 const char *acModule, 
                              int nModuleId,
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
                                 , int nSubId

																 )
{
	if (exist(acModule, acName)){ // already declared
		return -1;
	} else {

		nIdCounter++;
    bool bCached = nSubId != -1;
    if (nSubId == -1) ; else nIdCounter = nSubId;    
    

		sub *c = newSub(acModule, nModuleId, acRealName, acName, acSuffix, acReturnType, nReturnSize, myPcode, function, constructor, destructor, signal, slot, pc_pos, nScope, nTokenPos, nTokenLinePos, bStatic, bAbstract, acFile, nLine, bDeclare, acAlias, acLib, acLibCallSignature);
    c->bCached = bCached; 
		list_sub.insert(nIdCounter, c);
		list_sub2.insert(getKey(acModule, acName), c);
		list_sub3.insert(getKeyFromRealNameAndFileAndLine(acModule, acRealName, acFile, nLine), c);
		list_sub4.insert(nModuleId, c);
		//list_sub5.insert(getKey(acModule, acName), c);

		return nIdCounter;
	
	}

}

bool 		memory_sub::exist				(int nId)
{
	sub *m = findSub	(nId);
	if (m != 0){
		return true;
	}
	return false;
}
/*
bool 		memory_sub::hasSubWithSignature (const char *acModule, const char *acSignature)
{
	return exist	(getIdFromSignature(acModule, acSignature));
}
*/
bool 		memory_sub::exist				(const char *acModule, const char *acName)
{
	return exist	(getId(acModule, acName));
}

char     *memory_sub::getSuffix			(int nId)
{
	sub *m = findSub	(nId);
	if (m != 0){
		return m->acSuffix;
	}
	return 0;
}

char     *memory_sub::getAlias			(int nId)
{
	sub *m = findSub	(nId);
	if (m != 0){
		return m->acAlias;
	}
	return 0;
}

char     *memory_sub::getLib			(int nId)
{
	sub *m = findSub	(nId);
	if (m != 0){
		return m->acLib;
	}
	return 0;
}

char     *memory_sub::getLibCallSignature			(int nId)
{
	sub *m = findSub	(nId);
	if (m != 0){
		return m->acLibCallSignature;
	}
	return 0;
}

char     *memory_sub::getRealName			(int nId)
{
	sub *m = findSub	(nId);
	if (m != 0){
		return m->acRealName;
	}
	return 0;
}

char     *memory_sub::getName			(int nId)
{
	sub *m = findSub	(nId);
	if (m != 0){
		return m->acName;
	}
	return 0;
}

char     *memory_sub::getSignature			(int nId)
{
	sub *m = findSub	(nId);
	if (m != 0){
		return m->acSignature;
	}
	return 0;
}

// returns  moduleid --> modulename 
char     *memory_sub::getModuleByModuleId			(int nModuleId)
{
	if (list_sub4.contains(nModuleId)){
		sub *m = list_sub4[nModuleId];
   	if (m != 0){
	  	return m->acModule;
	  }
	}	 

	return 0;  
}

char     *memory_sub::getModule			(int nId)
{

	sub *m = findSub	(nId);
	if (m != 0){
		return m->acModule;
	}
	return 0;
}

int     memory_sub::getPcodePos			(int nId)
{
	sub *m = findSub	(nId);
	if (m != 0){
		return m->pc_pos;
	}
	return 0;
}

int     memory_sub::getPcodeLen			(int nId)
{
	sub *m = findSub	(nId);
	if (m != 0){
		return m->pc_len;
	}
	return 0;
}

char *memory_sub::getFile			(int nId)
{
	sub *m = findSub	(nId);
	if (m != 0){
		return m->acFile;
	}
	return 0;
}

int     memory_sub::getLine			(int nId)
{
	sub *m = findSub	(nId);
	if (m != 0){
		return m->nLine;
	}
	return 0;
}

int     memory_sub::getTokenPos			(int nId)
{
	sub *m = findSub	(nId);
	if (m != 0){
		return m->nTokenPos;
	}
	return 0;
}

int     memory_sub::getTokenLinePos			(int nId)
{
	sub *m = findSub	(nId);
	if (m != 0){
		return m->nTokenLinePos;
	}
	return 0;
}

int     memory_sub::getScope			(int nId)
{
	sub *m = findSub	(nId);
	if (m != 0){
		return m->nScope;
	}
	return 0;
}

bool     memory_sub::isPublic			(int nId)
{
  return getScope(nId) == 0;
}

bool     memory_sub::isPrivate			(int nId)
{
  return getScope(nId) == 0;
}

bool     memory_sub::isProtected			(int nId)
{
  return getScope(nId) == 0;
}

bool     memory_sub::isStatic			(int nId)
{
	sub *m = findSub	(nId);
	if (m != 0){
		return m->bStatic;
	}
	return false;
}

bool     memory_sub::isAbstract			(int nId)
{
	sub *m = findSub	(nId);
	if (m != 0){
		return m->bAbstract;
	}
	return false;
}

char     *memory_sub::getModule			()
{
	return (*it[idx])->acModule;
}

char     *memory_sub::getRealName			()
{
	return (*it[idx])->acRealName;
}

char     *memory_sub::getName			()
{
	return (*it[idx])->acName;
}

int     memory_sub::getParamCount			()
{
	return (*it[idx])->nParameterCounter;
}

int     memory_sub::getParamCount			(int nId)
{
	sub *m = findSub	(nId);
	if (m != 0){
		return m->nParameterCounter;
	}
	return 0;
}

char     *memory_sub::getSuffix			()
{
	return (*it[idx])->acSuffix;
}

char     *memory_sub::getAlias			()
{
	return (*it[idx])->acAlias;
}

char     *memory_sub::getLibCallSignature			()
{
	return (*it[idx])->acLibCallSignature;
}

char     *memory_sub::getLib			()
{
	return (*it[idx])->acLib;
}

bool     memory_sub::function			(int nId)
{
	sub *m = findSub	(nId);
	if (m != 0){
		return m->bFunction;
	}
	return false;
}

bool     memory_sub::constructor			(int nId)
{
	sub *m = findSub	(nId);
	if (m != 0){
		return m->bConstructor;
	}
	return false;
}

bool     memory_sub::destructor			(int nId)
{
	sub *m = findSub	(nId);
	if (m != 0){
		return m->bDestructor;
	}
	return false;
}

bool     memory_sub::signal			(int nId)
{
	sub *m = findSub	(nId);
	if (m != 0){
		return m->bSignal;
	}
	return false;
}

bool     memory_sub::slot			(int nId)
{
	sub *m = findSub	(nId);
	if (m != 0){
		return m->bSlot;
	}
	return false;
}

bool     memory_sub::declare			(int nId)
{
	sub *m = findSub	(nId);
	if (m != 0){
		return m->bDeclare;
	}
	return false;
}

bool     memory_sub::isCached			(int nId)
{
	sub *m = findSub	(nId);
	if (m != 0){
		return m->bCached;
	}
	return false;
}

/*
bool     memory_sub::function			()
{
	return it.data()->bFunction;
}
*/
int			memory_sub::getId					()
{
	return (*it[idx])->nId;
}

int			memory_sub::getIdFromRealNameAndFileAndLine					(const char *acModule, const char *acRealName, const char *acFile, int nLine)
{
  char *acKey = getKeyFromRealNameAndFileAndLine(acModule, acRealName, acFile, nLine);
	if (list_sub3.contains(acKey)){
		return list_sub3[acKey]->nId;
	}	 

	return -1;
}
/*
int			memory_sub::getIdFromSignature					(const char *acModule, const char *acSignature)
{
  char *acKey = getKey(acModule, acSignature);
	if (list_sub5.contains(acKey)){
		return list_sub5[acKey]->nId;
	}	 

	return -1;
}
*/
int			memory_sub::getId					(const char *acModule, const char *acName)
{
  char *acKey = getKey(acModule, acName);
	if (list_sub2.contains(acKey)){
		return list_sub2[acKey]->nId;
	}	 

	return -1;
}

int			memory_sub::getId					(int nModuleId, const char *acName)
{
  const char *acModule = getModuleByModuleId(nModuleId);
  char *acKey = getKey(acModule, acName);
	if (list_sub2.contains(acKey)){
		return list_sub2[acKey]->nId;
	}	 

	return -1;
}
/*
int			memory_sub::getId					(int nModuleId, int nId)
{
	sub *m = findSub	(nId);

	if (m != 0){
    return nId;
  }

	return -1;
}
*/

pcode *memory_sub::getPcode()
{
	return (*it[idx])->myPcode;
}

pcode *memory_sub::getPcode(int nId)
{
	sub *m = findSub	(nId);
	if (m != 0){
			return m->myPcode;
	}
	return 0;
}

bool memory_sub::findSub			(int nId, const char **acModule, const char **acRealName, const char **acName, const char **acSuffix, const char **acReturnType, int *nReturnSize, pcode **myPcode, bool *function)
{
	sub *m = findSub	(nId);
	if (m != 0){
		*acModule = m->acModule;
		*acRealName = m->acRealName;
		*acName = m->acName;
		*acSuffix = m->acSuffix;
		*acReturnType = m->acReturnType;
		*nReturnSize = m->nReturnSize;
		*myPcode = m->myPcode;
		*function = m->bFunction;
		return true;

	}
	return false;
}

char *memory_sub::getNameFromRealNameAndFileAndLine(const char *acModule, const char *acRealName, const char *acFile, int nLine)
{
	sub *m = findSub	(getIdFromRealNameAndFileAndLine(acModule, acRealName, acFile, nLine));
	if (m != 0){
		return m->acName;
  }
  return 0;
}

char *memory_sub::getRealNameFromName(const char *acModule, const char *acName)
{
	sub *m = findSub	(getId(acModule, acName));
	if (m != 0){
		return m->acRealName;
  }
  return 0;
}

pcode *memory_sub::getPcode(const char *acModule, const char *acName)
{
	return getPcode				(getId(acModule, acName));
}

char   *memory_sub::type				(int nId)
{
	sub *m = findSub	(nId);
	if (m != 0){
			return m->acReturnType;
	}
	return "";
}

char   *memory_sub::type				(const char *acModule, const char *acName)
{
	return type				(getId(acModule, acName));
}

bool		memory_sub::addThrow(int nId, const char *acType)
{
	sub *m = findSub	(nId);
	if (m != 0){
    
    for (int i = 0; i < m->nThrowCounter; i++){
  		if (strcmp(m->acThrowType[i], acType) == 0) return false;
    }

    strcpy(m->acThrowType[m->nThrowCounter], acType);
		m->nThrowCounter++;

		return m->nThrowCounter;
	}
	return false;
}

bool memory_sub::addThrow(const char *acModule, const char *acName, const char *acType)
{
	return addThrow				(getId(acModule, acName), acType);
}

bool		memory_sub::firstThrow	(int nId, const char **acType)
{
	sub *m = findSub	(nId);
	if (m != 0){

		m->nThrowIterator = 0;
		if (m->nThrowIterator != m->nThrowCounter){
			*acType = m->acThrowType[m->nThrowIterator];

			return true;
		}
	}
	return false;
}

bool		memory_sub::nextThrow	(int nId, const char **acType)
{
	sub *m = findSub	(nId);
	if (m != 0){

		m->nThrowIterator++;

		if (m->nThrowIterator < m->nThrowCounter){
			*acType = m->acThrowType[m->nThrowIterator];

			return true;
		}
	}
	return false;
}

bool		memory_sub::hasThrow	(int nId, const char *acType)
{
	sub *m = findSub	(nId);
	if (m != 0){

    const char *ac;

    if (firstThrow(nId, &ac)){
      do {

        if (strcmp(ac, acType) == 0){ return true; }

      } while (nextThrow(nId, &ac));
    }
	}
	return false;
}

bool		memory_sub::addParameter(int nId, const char *acName, const char *acType, int nParameterCall, bool bOptional, bool bDefault, bool bParamArray, t_array *a, defaultvalue *defval, int *nParamId)
{
	sub *m = findSub	(nId);
	if (m != 0){

    // acName must be unique
		if (hasParameter(nId, acName) == false){

			strcpy(m->acParameter[m->nParameterCounter], acName);
			strcpy(m->acParameterType[m->nParameterCounter], acType);

			m->nParameterCall[m->nParameterCounter] = nParameterCall;
			m->bParameterOptional[m->nParameterCounter] = bOptional;
			m->bParameterDefault[m->nParameterCounter] = bDefault;
			m->bParameterParamArray[m->nParameterCounter] = bParamArray;

			if (defval != NULL){
				m->defval[m->nParameterCounter].double_ = defval->double_;
				m->defval[m->nParameterCounter].single_ = defval->single_;
				m->defval[m->nParameterCounter].integer_ = defval->integer_;
				m->defval[m->nParameterCounter].long_ = defval->long_;
				m->defval[m->nParameterCounter].boolean_ = defval->boolean_;
				m->defval[m->nParameterCounter].cstring_ = defval->cstring_;
			}

			m->a[m->nParameterCounter].count = 0;

  		if (a){
       a->copyArray(&m->a[m->nParameterCounter]);
  			//m->a[m->nParameterCounter].count = a->count;
  			//for (int i = 0; i < a->count; i++) m->a[m->nParameterCounter].idx[i] = a->idx[i];
  		}

      if (*nParamId == 0){ 
        *nParamId = m->nParameterParamId[m->nParameterCounter] = memory_variable::addIdCounter();
      } else { 
        memory_variable::addIdCounter();
        m->nParameterParamId[m->nParameterCounter] = *nParamId;
      }

			m->nParameterCounter++;

			return true;
		}
	}
	return false;
}

bool		memory_sub::firstParameter	(int nId, const char **acName, const char **acType, int *nParameterCall, bool *bOptional, bool *bDefault, bool *bParamArray, t_array **a, defaultvalue **defval, int *nParamId)
{
	sub *m = findSub	(nId);
	if (m != 0){

		m->nParameterIterator = 0;
		if (m->nParameterIterator != m->nParameterCounter){
			*acName = m->acParameter[m->nParameterIterator];
			*acType = m->acParameterType[m->nParameterIterator];
			*nParameterCall = m->nParameterCall[m->nParameterIterator];
			*bOptional = m->bParameterOptional[m->nParameterIterator];
			*bDefault = m->bParameterDefault[m->nParameterIterator];      
			*bParamArray = m->bParameterParamArray[m->nParameterIterator];
			*a = &m->a[m->nParameterIterator];

			*defval = &m->defval[m->nParameterIterator];

      *nParamId = m->nParameterParamId[m->nParameterIterator];

			return true;
		}
	}
	return false;
}

bool		memory_sub::nextParameter	(int nId, const char **acName, const char **acType, int *nParameterCall, bool *bOptional, bool *bDefault, bool *bParamArray, t_array **a, defaultvalue **defval, int *nParamId)
{
	sub *m = findSub	(nId);
	if (m != 0){

		m->nParameterIterator++;

		if (m->nParameterIterator < m->nParameterCounter){
			*acName = m->acParameter[m->nParameterIterator];
			*acType = m->acParameterType[m->nParameterIterator];
			*nParameterCall = m->nParameterCall[m->nParameterIterator];
			*bOptional = m->bParameterOptional[m->nParameterIterator];
			*bDefault = m->bParameterDefault[m->nParameterIterator];      
			*bParamArray = m->bParameterParamArray[m->nParameterIterator];
			*a = &m->a[m->nParameterIterator];

			*defval = &m->defval[m->nParameterIterator];

      *nParamId = m->nParameterParamId[m->nParameterIterator];

			return true;
		}
	}
	return false;
}

bool		memory_sub::lastParameter	(int nId, const char **acName, const char **acType, int *nParameterCall, bool *bOptional, bool *bDefault, bool *bParamArray, t_array **a, defaultvalue **defval, int *nParamId)
{
	sub *m = findSub	(nId);
	if (m != 0){

		m->nParameterIterator = m->nParameterCounter - 1;
		if (m->nParameterIterator  >= 0){
			*acName = m->acParameter[m->nParameterIterator];
			*acType = m->acParameterType[m->nParameterIterator];
			*nParameterCall = m->nParameterCall[m->nParameterIterator];
			*bOptional = m->bParameterOptional[m->nParameterIterator];
			*bDefault = m->bParameterDefault[m->nParameterIterator];      
			*bParamArray = m->bParameterParamArray[m->nParameterIterator];
			*a = &m->a[m->nParameterIterator];

			*defval = &m->defval[m->nParameterIterator];

      *nParamId = m->nParameterParamId[m->nParameterIterator];

			return true;
		}
	}
	return false;
}

bool		memory_sub::prevParameter	(int nId, const char **acName, const char **acType, int *nParameterCall, bool *bOptional, bool *bDefault, bool *bParamArray, t_array **a, defaultvalue **defval, int *nParamId)
{
	sub *m = findSub	(nId);
	if (m != 0){

		m->nParameterIterator--;

		if (m->nParameterIterator  >= 0){
			*acName = m->acParameter[m->nParameterIterator];
			*acType = m->acParameterType[m->nParameterIterator];
			*nParameterCall = m->nParameterCall[m->nParameterIterator];
			*bOptional = m->bParameterOptional[m->nParameterIterator];
			*bDefault = m->bParameterDefault[m->nParameterIterator];      
			*bParamArray = m->bParameterParamArray[m->nParameterIterator];
			*a = &m->a[m->nParameterIterator];

			*defval = &m->defval[m->nParameterIterator];

      *nParamId = m->nParameterParamId[m->nParameterIterator];

			return true;
		}
	}
	return false;
}

bool		memory_sub::getParameter	(int nId, const char *acName_, const char **acType, int *nParameterCall, bool *bOptional, bool *bDefault, bool *bParamArray, t_array **a, defaultvalue **defval, int *nParamId)
{	
  const char *acName = "";

	// 
  if (firstParameter (nId, &acName, acType, nParameterCall, bOptional, bDefault, bParamArray, a, defval, nParamId)){

		do{ 
			if (strcmp(acName_, acName) == 0){
				return true;
			}

		} while(nextParameter (nId, &acName, acType, nParameterCall, bOptional, bDefault, bParamArray, a, defval, nParamId));

	}
	
	return false;
}

bool		memory_sub::hasParameter	(int nId, const char *acName_)
{	
  const char *acName = "";
  const char *acType = "";
	int nParameterCall = 0;
	bool bOptional = false; 
	bool bDefault = false;   
	bool bParamArray = false; 
	t_array *a = 0; 
	defaultvalue *defval = 0;
  int nParamId = 0;

	
  if (firstParameter (nId, &acName, &acType, &nParameterCall, &bOptional, &bDefault, &bParamArray, &a, &defval, &nParamId)){

		do{ 
			if (strcmp(acName_, acName) == 0){
				return true;
			}

		} while(nextParameter (nId, &acName, &acType, &nParameterCall, &bOptional, &bDefault, &bParamArray, &a, &defval, &nParamId));

	}
	
	return false;
}

bool		memory_sub::findParameter	(int nSubId, int nId, const char **acModuleName, const char **acSub, const char **acName)
{
  const char *_acName = "";
  const char *acType = "";
	int nParameterCall = 0;
	bool bOptional = false; 
	bool bDefault = false;   
	bool bParamArray = false; 
	t_array *a = 0; 
	defaultvalue *defval = 0;
  int nParamId = 0;

	
  if (firstParameter (nSubId, &_acName, &acType, &nParameterCall, &bOptional, &bDefault, &bParamArray, &a, &defval, &nParamId)){

		do{ 
			if (nId == nParamId){

	       sub *m = findSub	(nSubId);
	       if (m != 0){

          *acModuleName = m->acModule;
          *acSub = m->acName;
          *acName = _acName;

				   return true;
	      }
			}

		} while(nextParameter (nSubId, &_acName, &acType, &nParameterCall, &bOptional, &bDefault, &bParamArray, &a, &defval, &nParamId));

	}
	
	return false;
}

int		memory_sub::getParameterCount				(int nId)
{
	sub *m = findSub	(nId);
	if (m != 0){
			return m->nParameterCounter;
	}
	return false;
}

bool		memory_sub::registered				(int nId)
{
	sub *m = findSub	(nId);
	if (m != 0){
			return m->bRegistered;
	}
	return false;
}

bool		memory_sub::registered				(const char *acModule, const char *acName)
{
	return registered				(getId(acModule, acName));
}

bool 		memory_sub::pcodeBuilt				(int nId)
{
	sub *m = findSub	(nId);
	if (m != 0){
			return m->bPcodeBuilt;
	}
	return false;
}

bool 		memory_sub::pcodeBuilt				(const char *acModule, const char *acName)
{
	return pcodeBuilt				(getId(acModule, acName));
}

void		memory_sub::setPcodeBuilt				(int nId, bool b)
{
	sub *m = findSub	(nId);
	if (m != 0){
			m->bPcodeBuilt = b;
	}
}

void		memory_sub::setPcodeBuilt				(const char *acModule, const char *acName, bool b)
{
	setPcodeBuilt				(getId(acModule, acName), b);
}

void memory_sub::registerCall(int nId, pcode *pcodeCall, int nPcodePos)//, int nReturnPcodePos)
{

	sub *m = findSub	(nId);
	if (m != 0){

		if (m->nPcodeCallCounter == MAX_SUB_USED){
			subError("too many sub calls");
			return;
		}

		m->pcodeCall[m->nPcodeCallCounter] = pcodeCall;
		m->nPcodeCall[m->nPcodeCallCounter++] = nPcodePos;
		//m->nReturnPcodePos[m->nPcodeCallCounter++] = nReturnPcodePos;

	}
}

void memory_sub::changeRegisterCall(pcode *p_old, pcode *pcodeCall, int nPcodePos)
{

  if (first()){
    do {
      int nId = getId();

     	sub *m = findSub	(nId);
	    if (m != 0 && m->nPcodeCallCounter > 0){
        
        // add new pcode position to old = offset generated by ondemand-dimed variables
        for (int i = 0; i < m->nPcodeCallCounter; i++){
          if (m->pcodeCall[i] == p_old){
             m->pcodeCall[i] = pcodeCall;
             m->nPcodeCall[i] += nPcodePos;

          }
        }

      }

    } while (next());
  }

}

void memory_sub::registerCatch(int nId, pcode *pcodeCatch, int nCatchType, int nPcodePos, int nCatchPcodePos)
{

	sub *m = findSub	(nId);
	if (m != 0){

		if (m->nPcodeCatchCounter == MAX_SUB_USED){
			subError("too many sub catches");
			return;
		}

		m->pcodeCatch[m->nPcodeCatchCounter] = pcodeCatch;
		m->nPcodeCatch[m->nPcodeCatchCounter] = nPcodePos;
		m->nCatchType[m->nPcodeCatchCounter] = nCatchType;
		m->nCatchPcodePos[m->nPcodeCatchCounter++] = nCatchPcodePos;
		//m->nReturnPcodePos[m->nPcodeCatchCounter++] = nReturnPcodePos;

	}
}


bool		memory_sub::firstPcodeCall	(int nId, pcode **pcodeCall, int *nPcodeOffset)//, int *nReturnPcodePos)
{
	sub *m = findSub	(nId);
	if (m != 0){

		m->nPcodeCallIterator = 0;
		if (m->nPcodeCallIterator != m->nPcodeCallCounter){
			*pcodeCall = m->pcodeCall[m->nPcodeCallIterator];
			*nPcodeOffset = m->nPcodeCall[m->nPcodeCallIterator];
//			*nReturnPcodePos = m->nReturnPcodePos[m->nPcodeCallIterator];
			return true;
		}

	}

	return false;
}

bool		memory_sub::nextPcodeCall	(int nId, pcode **pcodeCall, int *nPcodeOffset)//, int *nReturnPcodePos)
{
	sub *m = findSub	(nId);
	if (m != 0){

		m->nPcodeCallIterator++;

		if (m->nPcodeCallIterator < m->nPcodeCallCounter){
			*pcodeCall = m->pcodeCall[m->nPcodeCallIterator];
			*nPcodeOffset = m->nPcodeCall[m->nPcodeCallIterator];
//			*nReturnPcodePos = m->nReturnPcodePos[m->nPcodeCallIterator];
			return true;
		}
	}
	return false;
}

bool		memory_sub::firstPcodeCatch	(int nId, pcode **pcodeCatch, int *nCatchType, int *nPcodeOffset, int *nCatchPcodePos)//, int *nReturnPcodePos)
{
	sub *m = findSub	(nId);
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

bool		memory_sub::nextPcodeCatch	(int nId, pcode **pcodeCatch, int *nCatchType, int *nPcodeOffset, int *nCatchPcodePos)//, int *nReturnPcodePos)
{
	sub *m = findSub	(nId);
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

bool		memory_sub::first	(int _idx)
{
  idx = _idx;
  it[idx] = list_sub.begin();
	sub *c = (*it[idx]);
	return it[idx] != list_sub.end();
}

bool		memory_sub::next	(int _idx)
{
  idx = _idx;
	++it[idx];
	return it[idx] != list_sub.end();
}

int		memory_sub::addVar(int nModuleId, const char *acSub, const char *acName, int nType, t_array *a, bool bStatic, int nScope, int nLStringLen, int nId)
{
	sub *m = findSub	(getId(nModuleId, acSub));
	if (m != 0){

		bool bByVal = false;
		bool bReference = false;
		bool bInit = true;
    //int nTypeSize = 0;

    return m->vars->declare(m->acModule, acSub, acName, nType, a, bByVal, bReference, bStatic, bInit, nScope, nLStringLen, nId);

	}
	return 0; 
}

bool		memory_sub::removeVar	(int nModuleId, int nId)
{
	sub *m = findSub	(nId);
	if (m != 0){

    return m->vars->undeclare(nId);

	}
	return false;
}

bool		memory_sub::firstVar	(int nModuleId, const char *acSub, const char **acName, int *nIdVar, int *nType, t_array **a, bool *bStatic, int *nScope)
{
	sub *m = findSub	(getId(nModuleId, acSub));
	if (m != 0){

		if (m->vars->first()){
			*nIdVar = m->vars->getId();
			*acName = m->vars->getName(*nIdVar);
			*nType = m->vars->type(*nIdVar);
			*a = m->vars->getArray(*nIdVar);
			*bStatic = m->vars->isStatic(*nIdVar);
			*nScope = m->vars->getScope(*nIdVar);
			return true;

		}
	}
	return false;
}

bool		memory_sub::nextVar	(int nModuleId, const char *acSub, const char **acName, int *nIdVar, int *nType, t_array **a, bool *bStatic, int *nScope)
{
	sub *m = findSub	(getId(nModuleId, acSub));
	if (m != 0){

		if (m->vars->next()){
			*nIdVar = m->vars->getId();
			*acName = m->vars->getName(*nIdVar);
			*nType = m->vars->type(*nIdVar);
			*a = m->vars->getArray(*nIdVar);
			*bStatic = m->vars->isStatic(*nIdVar);
			*nScope = m->vars->getScope(*nIdVar);
			return true;

		}
	}
	return false;
}

bool		memory_sub::getVar	(int nModuleId, const char *acSub, const char *acName, int *nIdVar, int *nType, t_array **a, bool *bStatic, int *nScope)
{
	sub *m = findSub	(getId(nModuleId, acSub));
	if (m != 0){

    *nIdVar = m->vars->getId(m->acModule, acSub, acName);

		acName = m->vars->getName(*nIdVar);
		*nType = m->vars->type(*nIdVar);
		*a = m->vars->getArray(*nIdVar);
		*bStatic = m->vars->isStatic(*nIdVar);
		*nScope = m->vars->getScope(*nIdVar);
		return true;

	}
	return false;
}

bool		memory_sub::existVar	(const char *acModule, const char *acSub, const char *acName)
{
	sub *m = findSub	(getId(acModule, acSub));
	if (m != 0){

		return m->vars->exist(acModule, acSub, acName);

	}
	return false;
}

bool		memory_sub::findVar	(int nModuleId, int nId, const char **acModule, const char **acSub, const char **acName)
{
	sub *m = findSub(nModuleId);
	if (m != 0){
		return m->vars->findVar(nId, acModule, acSub, acName);
	}
	return false;
}

int		memory_sub::getIdVar			(const char *acModule, const char *acSub, const char *acName)
{
	sub *m = findSub	(getId(acModule, acSub));
	if (m != 0){

		return m->vars->getId(acModule, acSub, acName);

	}
	return false;
}

int		memory_sub::typeVar				(const char *acModule, const char *acSub, const char *acName)
{
	sub *m = findSub	(getId(acModule, acSub));
	if (m != 0){

		return m->vars->type(acModule, acSub, acName);

	}
	return -1;
}

bool		memory_sub::isStaticVar				(const char *acModule, const char *acSub, const char *acName)
{
	sub *m = findSub	(getId(acModule, acSub));
	if (m != 0){

		return m->vars->isStatic(m->vars->getId(acModule, acSub, acName));

	}
	return false;
}

int		memory_sub::typeVar				(const char *acModule, const char *acSub, int nIdVar)
{
	sub *m = findSub	(getId(acModule, acSub));
	if (m != 0){

		return m->vars->type(nIdVar);

	}
	return false;
}

t_array		*memory_sub::getArrayVar		(const char *acModule, const char *acSub, const char *acName)
{
	sub *m = findSub	(getId(acModule, acSub));
	if (m != 0){

		return m->vars->getArray(m->vars->getId(acModule, acSub, acName));

	}
	return false;
}

t_array		*memory_sub::getArrayVar		(const char *acModule, const char *acSub, int nIdVar)
{
	sub *m = findSub	(getId(acModule, acSub));
	if (m != 0){

		return m->vars->getArray(nIdVar);

	}
	return false;
}

memory_variable		*memory_sub::getVars		(int nId)
{
	sub *m = findSub	(nId);
	if (m != 0){

		return m->vars;

	}
	return false;
}

memory_variable		*memory_sub::getVars		(const char *acModule, const char *acSub, const char *acName)
{
	sub *m = findSub	(getId(acModule, acSub));
	if (m != 0){

		return m->vars;

	}
	return false;
}

int		memory_sub::addConst(int nModuleId, const char *acSub, const char *acName, int nScope, int nId)
{
	sub *m = findSub	(getId(nModuleId, acSub));
	if (m != 0){

    return m->consts->declare(m->acModule, acSub, acName, nScope, nId);

	}
	return 0;
}

bool		memory_sub::firstConst	(int nModuleId, const char *acSub, const char **acName, int *nScope)
{
	sub *m = findSub	(getId(nModuleId, acSub));
	if (m != 0){

		if (m->consts->first()){
      int nId = m->consts->getId();

      *acName = m->consts->getName(nId);
      *nScope = m->consts->getScope(nId);
			return true;

		}
	}
	return false;
}

bool		memory_sub::nextConst	(int nModuleId, const char *acSub, const char **acName, int *nScope)
{
	sub *m = findSub	(getId(nModuleId, acSub));
	if (m != 0){

		if (m->consts->next()){
      int nId = m->consts->getId();

      *acName = m->consts->getName(nId);
      *nScope = m->consts->getScope(nId);
			return true;

		}
	}
	return false;
}

bool		memory_sub::existConst	(const char *acModule, const char *acSub, const char *acName)
{
	sub *m = findSub	(getId(acModule, acSub));
	if (m != 0){

		return m->consts->exist(acModule, acSub, acName);

	}
	return false;
}

bool		memory_sub::findConst	(int nModuleId, int nId, const char **acModule, const char **acSub, const char **acName)
{
	sub *m = findSub(nModuleId);
	if (m != 0){
		return m->consts->findConst(nId, acModule, acSub, acName);
	}
	return false;
}

int		memory_sub::getIdConst			(const char *acModule, const char *acSub, const char *acName)
{
	sub *m = findSub	(getId(acModule, acSub));
	if (m != 0){

		return m->consts->getId(acModule, acSub, acName);

	}
	return false;
}

memory_const		*memory_sub::getConsts		(int nId)
{
	sub *m = findSub	(nId);
	if (m != 0){

		return m->consts;

	}
	return false;
}

memory_const		*memory_sub::getConsts		(const char *acModule, const char *acSub, const char *acName)
{
	sub *m = findSub	(getId(acModule, acSub));
	if (m != 0){

		return m->consts;

	}
	return false;
}

