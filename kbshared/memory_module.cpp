/*
***************************************************************************
Copyright (C) 2000-2008 KBasic Software: www.kbasic.com. All rights reserved.
Source codes are copyrighted by Bernd Noetscher 2000-2008.

You may use this source codes under the terms of the GNU Public License (Version 3)
as published by the Free Software Foundation. 

If you are interested in using the source codes for other licenses or 
commercial development, you must buy commercial licenses from KBasic Software.

This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
***************************************************************************
*/

#include "memory_module.h"




memory_module::memory_module			()
{

	nIdCounter = pcode__user_defined_module;
}

memory_module::~memory_module		()
{

  if (list_module.first(&key, &value)){
    do {

      module_ *m = (module_ *) value;

    delete m->mySub;
    delete m->myPropertyGet;
    delete m->myPropertySet;
    delete m->vars;    
    delete m->consts;

    //for (int i = 0; i < m->nPcodeCatchCounter; i++){
      //delete m->pcodeCatch[i];     // werden woanders freigegeben 
    //}

    delete m;

    } while (list_module.next(&key, &value));
  }


  list_module.clear();
  list_module2.clear();

  findModule(-99); // delete cache
}

// ****************************
// * bool moduleError(char *acmoduleError)
// *
// * description:
// * prints a module error message
// *
// * interpreter_parameter:
// * char *acmoduleError = the error message to print
// *
// * return:
// * dummy
// ****************************
bool memory_module::moduleError(char *acModuleError)
{
	static char acText[1024];

	sprintf(acText, "\nmodule error: %s\n", acModuleError);
	console::printError(acText);
	return false;
}

module_	*memory_module::findModule	(int nId)
{
  // * optimize
  static int _nId = -100;
  static module_ *v = 0;
  static void *_this = 0;

  if (_nId == nId && _this == this){
    return v;
  }
  // *
	if (list_module.contains(nId)){
    _nId = nId;
    _this = this;
    v = (module_ *) list_module.get(nId);
		return v;
	}
  _nId = -100;

  return 0;
}

module_ *memory_module::newModule(const char *acName, pcode *myPcode, int pc_pos, const char *acFile/*, int nExtend*/)
{
	module_ *t = new module_();

  int n = strlen(acName);

	memcpy(t->acName, acName, n);
	t->acName[n] = '\0';

  n = strlen(acFile);
	memcpy(t->acFile, acFile, n);
	t->acFile[n] = '\0';

	t->nId = nIdCounter;

  t->pc_pos = pc_pos;
	t->bPcodeBuilt = false;
	t->bRegistered = true;

	t->mySub = new memory_sub();
	t->vars = new memory_variable();
	t->consts = new memory_const();
	
	t->nPcodeCatchIterator = 0;
	t->nPcodeCatchCounter = 0;

  return t;
}

int 		memory_module::addModule			(const char *acName, pcode *myPcode, int pc_pos, const char *acFile, int nId/*, int nExtend*/)
{
	if (exist(acName)){ // already declared
		return 0;
	} else {

		nIdCounter++;
    if (nId == 0) nId = nIdCounter; else nIdCounter = nId;        
		
		module_ *c = newModule(acName, myPcode, pc_pos, acFile/*, nExtend*/);
    
    c->bIsCached = nId != 0;

    list_module.add(nId, (int) c);
		list_module2.addString(acName, (int) c);

		return nId;
	
	}

}

int 		memory_module::addModuleSub	(
																				const char *acModuleName, 
																				const char *acRealName, 
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
                                        int nLine,
                                        bool bDeclare,
                                        const char *acAlias,
                                        const char *acLib,
                                        const char *acLibCallSignature        
                                        , int nSubId
																			 )
{
  int nId = getId(acModuleName);
	module_ *m = findModule	(nId);
	if (m != 0){
   
    bool constructor = false;
    bool destructor = false;
    bool signal = false;
    bool slot = false;

		return m->mySub->addSub(acModuleName, nId, acRealName, acName, acSuffix, acReturnType, nReturnSize, myPcode, function, constructor, destructor, signal, slot, pc_pos, nScope, nTokenPos, nTokenLinePos, bStatic, bAbstract, acFile, nLine, bDeclare, acAlias, acLib, acLibCallSignature, nSubId);
	}
	return 0;
}

bool 		memory_module::exist				(int nId)
{
	return (findModule	(nId) != 0);
}

bool memory_module::findVar(int nId, const char **acModule, const char **acSub, const char **acVar)
{
 
  if (first()){
    do {
      int nModuleId = getId();

      if (findVar(nModuleId, nId, acModule, acSub, acVar)) return true;

      if (firstSub()){
       do {
         int nSubId = getIdSub();

         if (findSubVar(nModuleId, nSubId, nId, acModule, acSub, acVar)) return true;

         if (findParameterSub(nModuleId, nSubId, nId, acModule, acSub, acVar)) return true;

       } while (nextSub());
      }

    } while (next());
  }

  return false;
}

bool memory_module::findConst(int nId, const char **acModule, const char **acSub, const char **acVar)
{

  if (first()){
    do {
      int nModuleId = getId();

      if (findConst(nModuleId, nId, acModule, acSub, acVar)) return true;

      if (firstSub()){
        do {
         int nSubId = getIdSub();

         if (findSubConst(nModuleId, nSubId, nId, acModule, acSub, acVar)) return true;
        } while (nextSub());
      }

    } while (next());
  }

  return false;
}

bool     memory_module::existSub			(int nModuleId, int nId)
{
	module_ *m = findModule	(nModuleId);
	if (m != 0){
		return m->mySub->exist(nId);
	}
	return 0;
}

bool 		memory_module::existSub				(int nId, const char *acSub)
{
	module_ *m = findModule	(nId);
	if (m != 0){
		return m->mySub->exist(m->mySub->getId(m->acName, acSub));
	}
	return false;
}

bool 		memory_module::existSub				(const char *acModuleName, const char *acSub)
{
	module_ *m = findModule	(getId(acModuleName));
	if (m != 0){
		return m->mySub->exist(m->mySub->getId(m->acName, acSub));
	}
	return false;
}

char   *memory_module::getFile				(int nId)
{
	module_ *m = findModule	(nId);
	if (m != 0){
    return m->acFile;
	}
	return 0;
}

memory_sub *memory_module::getSubs				(int nId)
{
	module_ *m = findModule	(nId);
	if (m != 0){
		return m->mySub;
	}
	return 0;
}

memory_sub *memory_module::getSubs				(const char *acModuleName)
{
	module_ *m = findModule	(getId(acModuleName));
	if (m != 0){
		return m->mySub;
	}
	return 0;
}

bool		memory_module::isCachedSub(int nModuleId, int nId)
{
	module_ *m = findModule	(nModuleId);
	if (m != 0){
		return m->mySub->isCached(nId);
	}
	return false;
}

bool 		memory_module::exist				(const char *acName)
{
	return exist	(getId(acName));
}

char     *memory_module::getSuffixSub			(int nModuleId, int nId)
{
	module_ *m = findModule	(nModuleId);
	if (m != 0){
		return m->mySub->getSuffix(nId);
	}
	return 0;
}

char     *memory_module::getName			(int nId)
{
	module_ *m = findModule	(nId);
	if (m != 0){
		return m->acName;
	}
	return 0;
}

char *memory_module::getNameSub			(int nModuleId, int nId)
{
	module_ *m = findModule	(nModuleId);
	if (m != 0){
		return m->mySub->getName(nId);
	}
	return 0;
}

char *memory_module::getRealNameSub			(int nModuleId, int nId)
{
	module_ *m = findModule	(nModuleId);
	if (m != 0){
		return m->mySub->getRealName(nId);
	}
	return 0;
}

int     memory_module::getParamCountSub			(int nModuleId, int nId)
{
	module_ *m = findModule	(nModuleId);
	if (m != 0){
		return m->mySub->getParamCount(nId);
	}
	return 0;
}

int     memory_module::getPcodePos			(int nId)
{
	module_ *m = findModule	(nId);
	if (m != 0){
		return m->pc_pos;
	}
	return 0;
}

int     memory_module::getPcodePosSub			(int nModuleId, int nId)
{
	module_ *m = findModule	(nModuleId);
	if (m != 0){
		return m->mySub->getPcodePos(nId);
	}
	return 0;
}

int     memory_module::getTokenPosSub			(int nModuleId, int nId)
{
	module_ *m = findModule	(nModuleId);
	if (m != 0){

		return m->mySub->getTokenPos(nId);
	}
	return false;
}

int     memory_module::getScopeSub			(int nModuleId, int nId)
{
	module_ *m = findModule	(nModuleId);
	if (m != 0){

		return m->mySub->getScope(nId);
	}
	return false;
}

bool     memory_module::isStaticSub			(int nModuleId, int nId)
{
	module_ *m = findModule	(nModuleId);
	if (m != 0){

		return m->mySub->isStatic(nId);
	}
	return false;
}

bool     memory_module::isAbstractSub			(int nModuleId, int nId)
{
	module_ *m = findModule	(nModuleId);
	if (m != 0){

		return m->mySub->isAbstract(nId);
	}
	return false;
}

int			memory_module::getId					()
{
	return it[idx]->nId;
}

int			memory_module::getIdSub					()
{
	module_ *m = findModule	(getId());
	if (m != 0){
			return m->mySub->getId();
	}
	return 0;
}

int			memory_module::getId					(const char *acName)
{

	if (list_module2.contains(acName)){
    return ((module_ *)list_module2.getString(acName))->nId;
	}

	return 0;
}

int			memory_module::getIdSub					(int nModuleId, const char *acSub)
{
	module_ *m = findModule	(nModuleId);
	if (m != 0){
		return m->mySub->getId(m->acName, acSub);
	}
	return 0;
}

int			memory_module::getIdSub					(const char *acName, const char *acSub)
{
	module_ *m = findModule	(getId(acName));
	if (m != 0){
		return m->mySub->getId(m->acName, acSub);
	}
	return 0;
}


pcode *memory_module::getPcodeSub()
{
	module_ *m = findModule	(getId());
	if (m != 0){
			return m->mySub->getPcode();
	}
	return 0;
}
/*
pcode *memory_module::getPcode(int nId)
{
	module_ *m = findModule	(nId);
	if (m != 0){
			return m->myPcode;
	}
	return 0;
}

pcode *memory_module::getPcode(const char *acName)
{
	return getPcode(getId(acName));
}
*/
pcode *memory_module::getPcodeSub(int nModuleId, int nId)
{
	module_ *m = findModule	(nModuleId);
	if (m != 0){
			return m->mySub->getPcode(nId);
	}
	return 0;
}

bool memory_module::findModule			(int nId, char **acName, pcode **myPcode) 
{
	module_ *m = findModule	(nId);
	if (m != 0){
		*acName = m->acName;

		return true;

	}
	return false;
}

module_ *memory_module::findModule			(const char *acModuleName)
{
	return findModule	(getId(acModuleName));
}

pcode *memory_module::getPcodeSub(const char *acName, const char *acSub)
{
	return getPcodeSub				(getId(acName), getIdSub(acName, acSub));
}

char   *memory_module::typeSub				(int nModuleId, int nId)
{
	module_ *m = findModule	(nModuleId);
	if (m != 0){
		return m->mySub->type(nId);
	}
	return 0;
}

char   *memory_module::typeSub				(const char *acName, const char *acSub)
{
	return typeSub				(getId(acName), getIdSub(acName, acSub));
}

bool		memory_module::addThrowSub(int nModuleId, int nId, const char *acType)
{
	module_ *m = findModule	(nModuleId);
	if (m != 0){

		return m->mySub->addThrow(nId, acType);

	}
	return false;
}

bool		memory_module::addThrowSub(const char *acName, const char *acSub, const char *acType)
{
	module_ *m = findModule	(getId(acName));
	if (m != 0){

		return m->mySub->addThrow(acName, acSub, acType);

	}
	return false;
}

bool		memory_module::firstThrowSub	(int nModuleId, int nId, const char **acType)
{
	module_ *m = findModule	(nModuleId);
	if (m != 0){

		return m->mySub->firstThrow(nId, acType);

	}
	return false;
}

bool		memory_module::nextThrowSub	(int nModuleId, int nId, const char **acType)
{
	module_ *m = findModule	(nModuleId);
	if (m != 0){

		return m->mySub->nextThrow(nId, acType);

	}
	return false;
}

bool		memory_module::addParameterSub(int nModuleId, int nId, const char *acName, const char *acType, int nParameterCall, bool bOptional, bool bDefault, bool bParamArray, t_array *a, defaultvalue *defval, int *nParamId, int *nParamLStringLen)
{
	module_ *m = findModule	(nModuleId);
	if (m != 0){

		return m->mySub->addParameter(nId, acName, acType, nParameterCall, bOptional, bDefault, bParamArray, a, defval, nParamId, nParamLStringLen);

	}
	return false;
}

bool		memory_module::firstParameterSub	(int nModuleId, int nId, const char **acName, const char **acType, int *nParameterCall, bool *bOptional, bool *bDefault, bool *bParamArray, t_array **a, defaultvalue **defval, int *nParamId, int *nParamLStringLen)
{
	module_ *m = findModule	(nModuleId);
	if (m != 0){

		return m->mySub->firstParameter(nId, acName, acType, nParameterCall, bOptional, bDefault, bParamArray, a, defval, nParamId, nParamLStringLen);

	}
	return false;
}

bool		memory_module::nextParameterSub	(int nModuleId, int nId, const char **acName, const char **acType, int *nParameterCall, bool *bOptional, bool *bDefault, bool *bParamArray, t_array **a, defaultvalue **defval, int *nParamId, int *nParamLStringLen)
{
	module_ *m = findModule	(nModuleId);
	if (m != 0){

		return m->mySub->nextParameter(nId, acName, acType, nParameterCall, bOptional, bDefault, bParamArray, a, defval, nParamId, nParamLStringLen);

	}
	return false;
}

bool		memory_module::lastParameterSub	(int nModuleId, int nId, const char **acName, const char **acType, int *nParameterCall, bool *bOptional, bool *bDefault, bool *bParamArray, t_array **a, defaultvalue **defval, int *nParamId, int *nParamLStringLen)
{
	module_ *m = findModule	(nModuleId);
	if (m != 0){

		return m->mySub->lastParameter(nId, acName, acType, nParameterCall, bOptional, bDefault, bParamArray, a, defval, nParamId, nParamLStringLen);

	}
	return false;
}

bool		memory_module::prevParameterSub	(int nModuleId, int nId, const char **acName, const char **acType, int *nParameterCall, bool *bOptional, bool *bDefault, bool *bParamArray, t_array **a, defaultvalue **defval, int *nParamId, int *nParamLStringLen)
{
	module_ *m = findModule	(nModuleId);
	if (m != 0){

		return m->mySub->prevParameter(nId, acName, acType, nParameterCall, bOptional, bDefault, bParamArray, a, defval, nParamId, nParamLStringLen);

	}
	return false;
}

bool		memory_module::getParameterSub	(int nModuleId, int nId, const char *acName_, const char **acType, int *nParameterCall, bool *bOptional, bool *bDefault, bool *bParamArray, t_array **a, defaultvalue **defval, int *nParamId, int *nParamLStringLen)
{	
	module_ *m = findModule	(nModuleId);
	if (m != 0){

		return m->mySub->getParameter(nId, acName_, acType, nParameterCall, bOptional, bDefault, bParamArray, a, defval, nParamId, nParamLStringLen);

	}
	return false;
}

bool		memory_module::hasParameterSub	(int nModuleId, int nId, const char *acName_)
{	
	module_ *m = findModule	(nModuleId);
	if (m != 0){

		return m->mySub->hasParameter(nId, acName_);

	}
	return false;
}

bool		memory_module::findParameterSub	(int nModuleId, int nSubId, int nId, const char **acModule, const char **acSub, const char **acName)
{
	module_ *m = findModule	(nModuleId);
	if (m != 0){
		return m->mySub->findParameter(nSubId, nId, acModule, acSub, acName);
	}
	return false;
}


int		memory_module::getParameterCountSub				(int nModuleId, int nId)
{
	module_ *m = findModule	(nModuleId);
	if (m != 0){
			return m->mySub->getParameterCount(nId);
	}
	return false;
}

bool 		memory_module::isCached				(int nId)
{
	module_ *m = findModule	(nId);
	if (m != 0){
    return m->bIsCached;
	}
	return false;
}

bool		memory_module::registered				(int nId)
{
	module_ *m = findModule	(nId);
	if (m != 0){
			return m->bRegistered;
	}
	return false;
}

bool		memory_module::registered				(const char *acName)
{
	return registered(getId(acName));
}

bool		memory_module::registeredSub				(int nModuleId, int nId)
{
	module_ *m = findModule	(nModuleId);
	if (m != 0){

		return m->mySub->registered(nId);

	}
	return false;
}

bool		memory_module::registeredSub				(const char *acName, const char *acSub)
{
	module_ *m = findModule	(getId(acName));
	if (m != 0){

		return m->mySub->registered(acName, acSub);

	}
	return false;
}

bool 		memory_module::pcodeBuilt				(int nId)
{
	module_ *m = findModule	(nId);
	if (m != 0){
			return m->bPcodeBuilt;
	}
	return false;
}

bool 		memory_module::pcodeBuilt				(const char *acName)
{
	return pcodeBuilt(getId(acName));
}

bool 		memory_module::pcodeBuiltSub				(const char *acName, const char *acSub)
{
	module_ *m = findModule	(getId(acName));
	if (m != 0){

		return m->mySub->pcodeBuilt(acName, acSub);

	}
	return false;
}

void		memory_module::setPcodeBuilt				(int nId, bool b)
{
	module_ *m = findModule	(nId);
	if (m != 0){
			m->bPcodeBuilt = b;
	}
}

void		memory_module::setPcodeBuilt				(const char *acName, bool b)
{
	module_ *m = findModule	(getId(acName));
	if (m != 0){
			m->bPcodeBuilt = b;
	}
}

void		memory_module::setPcodeBuiltSub				(const char *acName, const char *acSub, bool b)
{
	module_ *m = findModule	(getId(acName));
	if (m != 0){

		m->mySub->setPcodeBuilt(acName, acSub, b);

	}
}

bool 		memory_module::pcodeBuiltSub				(int nModuleId, int nId)
{
	module_ *m = findModule	(nModuleId);
	if (m != 0){
			return m->mySub->pcodeBuilt(nId);
	}
	return false;
}

void		memory_module::setPcodeBuiltSub				(int nModuleId, int nId, bool b)
{
	module_ *m = findModule	(nModuleId);
	if (m != 0){
			m->mySub->setPcodeBuilt(nId, b);
	}
}

void memory_module::registerCallSub(int nModuleId, int nId, pcode *pcodeCall, int nPcodePos, int nReturnPcodePos)
{

	module_ *m = findModule	(nModuleId);
	if (m != 0){
		m->mySub->registerCall(nId, pcodeCall, nPcodePos);//, nReturnPcodePos);
	}
}

void memory_module::changeRegisterCallSub(pcode *p_old, pcode *pcodeCall, int nPcodePos)
{

  if (first()){
    do {
      int nModuleId = getId();

	    module_ *m = findModule	(nModuleId);
	    if (m != 0){
		    m->mySub->changeRegisterCall(p_old, pcodeCall, nPcodePos);

        for (int i = 0; i < m->nPcodeCatchCounter; i++){
          if (m->pcodeCatch[i] == p_old){            
             m->pcodeCatch[i] = pcodeCall;
             m->nPcodeCatch[i] += nPcodePos;             
          }
        }

	    }

    } while (next());
  }

}

bool		memory_module::firstPcodeCallSub	(int nModuleId, int nId, pcode **pcodeCall, int *nPcodeOffset)//, int *nReturnPcodePos)
{
	module_ *m = findModule	(nModuleId);
	if (m != 0){

		return m->mySub->firstPcodeCall(nId, pcodeCall, nPcodeOffset);//, nReturnPcodePos);

	}

	return false;
}

bool		memory_module::nextPcodeCallSub	(int nModuleId, int nId, pcode **pcodeCall, int *nPcodeOffset)//, int *nReturnPcodePos)
{
	module_ *m = findModule	(nModuleId);
	if (m != 0){

		return m->mySub->nextPcodeCall(nId, pcodeCall, nPcodeOffset);//, nReturnPcodePos);
	}
	return false;
}

bool		memory_module::first	(int _idx)
{
  idx = _idx;
	return list_module.first(&key, (int *) &it[idx]);
}

bool		memory_module::next	(int _idx)
{
  idx = _idx;
  return list_module.next(&key, (int *) &it[idx]);
}

bool		memory_module::firstSub	(int _idx)
{
  idx = _idx;
	module_ *m = findModule	(getId());
	if (m != 0){
			return m->mySub->first(idx);
	}
	return false;
}

bool		memory_module::nextSub	(int _idx)
{
  idx = _idx;
	module_ *m = findModule	(getId());
	if (m != 0){
			return m->mySub->next(idx);
	}
	return false;
}

int		memory_module::addVar	(int nModuleId, const char *acName, int nType, t_array *a, int nScope, int nLStringLen, int nId)
{
	module_ *m = findModule	(nModuleId);
	if (m != 0){

		const char *acSub = "";				
		bool bByVal = false;
		bool bReference = false;
		bool bStatic = false;
    //int nLStringLen = 0;
/*
    if (strcmp(acName, "THIp") == 0){
      acName = acName;
    }*/

		return m->vars->declare(m->acName, acSub, acName, nType, a, bByVal, bReference, bStatic, nScope, nLStringLen, nId);

	}
	return 0;
}

bool		memory_module::removeVar	(int nModuleId, int nId)
{
	module_ *m = findModule	(nModuleId);
	if (m != 0){

    return m->vars->undeclare(nId);

	}
	return false;
}

bool		memory_module::firstVar	(int nModuleId, const char **acName, int *nId, int *nType, t_array **a, int *nScope)
{
	module_ *m = findModule	(nModuleId);
	if (m != 0){


		if (m->vars->first()){
			*nId = m->vars->getId();

			*acName = m->vars->getName(*nId);
			*nType = m->vars->type(*nId);
			*a = m->vars->getArray(*nId);
			*nScope = m->vars->getScope(*nId);
			return true;

		}
	}
	return false;
}

bool		memory_module::nextVar	(int nModuleId, const char **acName, int *nId, int *nType, t_array **a, int *nScope)
{
	module_ *m = findModule	(nModuleId);
	if (m != 0){

		if (m->vars->first()){
			*nId = m->vars->getId();

      *acName = m->vars->getName(*nId);
			*nType = m->vars->type(*nId);
			*a = m->vars->getArray(*nId);
			*nScope = m->vars->getScope(*nId);
			return true;

		}
	}
	return false;
}

bool		memory_module::getVar	(int nModuleId, const char *acName, int *nId, int *nType, t_array **a, int *nScope)
{
	module_ *m = findModule	(nModuleId);
	if (m != 0){

		const char *acSub = "";				

    *nId = m->vars->getId(m->acName, acSub, acName);

		acName = m->vars->getName(*nId);
		*nType = m->vars->type(*nId);
		*a = m->vars->getArray(*nId);
		*nScope = m->vars->getScope(*nId);
		return true;

	}
	return false;
}

bool		memory_module::existVar	(int nModuleId, const char *acName)
{
	module_ *m = findModule	(nModuleId);
	if (m != 0){

		const char *acSub = "";				

    return m->vars->exist(m->acName, acSub, acName);

	}
	return false;
}

bool		memory_module::findVar	(int nModuleId, int nId, const char **acModule, const char **acSub, const char **acName)
{
	module_ *m = findModule	(nModuleId);
	if (m != 0){
		return m->vars->findVar(nId, acModule, acSub, acName);
	}
	return false;
}

int		memory_module::typeVar	(int nModuleId, int nId)
{
	module_ *m = findModule	(nModuleId);
	if (m != 0){

		return m->vars->type(nId);

	}
	return false;
}

int		memory_module::typeVar	(const char *acModule_, const char *acName)
{
	module_ *m = findModule	(getId(acModule_));
	if (m != 0){

		const char *acSub = "";				
    
		int nId = m->vars->type(m->acName, acSub, acName);
    //if (memory_type::scalar(nId)) 
      return nId;

		//return m->vars->type(nId);

	}
	return false;
}

int		memory_module::scopeVar	(int nModuleId, int nId)
{
	module_ *m = findModule	(nModuleId);
	if (m != 0){

		return m->vars->getScope(nId);

	}
	return false;
}

bool		memory_module::existVar	(int nModuleId, int nId)
{
	module_ *m = findModule	(nModuleId);
	if (m != 0){

		return m->vars->exist(nId);

	}
	return false;
}

int		memory_module::scopeVar	(const char *acModule_, const char *acName)
{
	module_ *m = findModule	(getId(acModule_));
	if (m != 0){

		const char *acSub = "";				
    
		return m->vars->getScope(m->vars->getId(m->acName, acSub, acName));

	}
	return false;
}

int		memory_module::getIdVar	(const char *acModule_, const char *acName)
{
	module_ *m = findModule	(getId(acModule_));
	if (m != 0){

		const char *acSub = "";				

    return m->vars->getId(m->acName, acSub, acName);

	}
	return 0;
}


int		memory_module::getIdVar	(int nModuleId, const char *acName)
{
	module_ *m = findModule	(nModuleId);
	if (m != 0){

		const char *acSub = "";				

		return m->vars->getId(m->acName, acSub, acName);

	}
	return 0;
}

bool		memory_module::existVar	(const char *acModuleName, const char *acName)
{
  module_ *m = findModule	(getId(acModuleName));
	if (m != 0){

		const char *acSub = "";				

		return m->vars->exist(m->acName, acSub, acName);

	}
	return false;
}

t_array *memory_module::getArrayVar	(int nModuleId, int nId)
{
	module_ *m = findModule	(nModuleId);
	if (m != 0){

		return m->vars->getArray(nId);

	}
	return false;
}

t_array *memory_module::getArrayVar	(const char *acModuleName, const char *acName)
{
  module_ *m = findModule	(getId(acModuleName));
	if (m != 0){

		const char *acSub = "";				

    return m->vars->getArray( m->vars->getId(m->acName, acSub, acName) );

	}
	return false;
}

int memory_module::getLStringLenVar	(int nModuleId, int nId)
{
	module_ *m = findModule	(nModuleId);
	if (m != 0){

		return m->vars->getLStringLen(nId);

	}
	return false;
}

int memory_module::getLStringLenVar	(const char *acModuleName, const char *acName)
{
  module_ *m = findModule	(getId(acModuleName));
	if (m != 0){

		const char *acSub = "";				

    return m->vars->getLStringLen( m->vars->getId(m->acName, acSub, acName) );

	}
	return false;
}

int		memory_module::addConst	(int nModuleId, const char *acName, int nScope, int nId)
{
	module_ *m = findModule	(nModuleId);
	if (m != 0){

		const char *acSub = "";				

		return m->consts->declare(m->acName, acSub, acName, nScope, nId);

	}
	return 0;
}

bool		memory_module::firstConst	(int nModuleId, const char **acName, int *nId, int *nScope)
{
	module_ *m = findModule	(nModuleId);
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

bool		memory_module::nextConst	(int nModuleId, const char **acName, int *nId, int *nScope)
{
	module_ *m = findModule	(nModuleId);
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

bool		memory_module::getConst	(int nModuleId, const char *acName, int *nId, int *nScope)
{
	module_ *m = findModule	(nModuleId);
	if (m != 0){

		const char *acSub = "";				

		*nId = m->consts->getId(m->acName, acSub, acName);
		acName = m->consts->getName(*nId);
		*nScope = m->consts->getScope(*nId);
		return true;

	}
	return false;
}


bool		memory_module::existConst	(const char *acModuleName, const char *acName)
{
  module_ *m = findModule	(getId(acModuleName));
	if (m != 0){

		const char *acSub = "";				

    return m->consts->exist(m->acName, acSub, acName);

	}
	return false;
}

bool		memory_module::existConst	(int nModuleId, const char *acName)
{
	module_ *m = findModule	(nModuleId);
	if (m != 0){
		
		const char *acSub = "";				

		return m->consts->exist(m->acName, acSub, acName);

	}
	return false;
}

bool		memory_module::findConst	(int nModuleId, int nId, const char **acModule, const char **acSub, const char **acName)
{
	module_ *m = findModule	(nModuleId);
	if (m != 0){
		return m->consts->findConst(nId, acModule, acSub, acName);
	}
	return false;
}

int		memory_module::getIdConst	(int nModuleId, const char *acName)
{
	module_ *m = findModule	(nModuleId);
	if (m != 0){

		const char *acSub = "";				

    int n =  m->consts->getId(m->acName, acSub, acName);    
    return n;

	}
	return 0;
}

int		memory_module::getIdConst	(const char *acModuleName, const char *acName)
{
  return getIdConst(getId(acModuleName), acName);
}

bool		memory_module::isPublicConst	(int nModuleId, int nId)
{
	module_ *m = findModule	(nModuleId);
	if (m != 0){

		return m->consts->isPublic(nId);

	}
	return false;
}

bool		memory_module::isPublicConst	(int nModuleId, const char *acName)
{
	module_ *m = findModule	(nModuleId);
	if (m != 0){

		const char *acSub = "";				

		return m->consts->exist(m->acName, acSub, acName);

	}
	return false;
}


int		memory_module::addSubVar(int nModuleId, const char *acSub, const char *acName, int nType, t_array *a, bool bStatic, int nScope, int nLStringLen, int nId)
{
	module_ *m = findModule	(nModuleId);
	if (m != 0){

		return m->mySub->addVar(nModuleId, acSub, acName, nType, a, bStatic, nScope, nLStringLen, nId);

	}
	return 0;
}

bool		memory_module::removeSubVar	(int nModuleId, int nSubId, int nId)
{
	module_ *m = findModule	(nModuleId);
	if (m != 0){

		return m->mySub->removeVar(nSubId, nId);

	}
	return false;
}

bool		memory_module::firstSubVar	(int nModuleId, const char *acSub, const char **acName, int *nId, int *nType, t_array **a, bool *bStatic, int *nScope)
{
	module_ *m = findModule	(nModuleId);
	if (m != 0){

		if (m->mySub->first()){
			*acName = m->mySub->getName();
			*nId = m->mySub->getId();
      *nType = m->mySub->typeVar(m->acName, acSub, *nId);
			*a = m->mySub->getArrayVar(m->acName, acSub, *nId);
      *bStatic = m->mySub->isStatic(*nId);
			*nScope = m->mySub->getScope(*nId);
			return true;

		}
	}
	return false;
}

bool		memory_module::nextSubVar	(int nModuleId, const char *acSub, const char **acName, int *nId, int *nType, t_array **a, bool *bStatic, int *nScope)
{
  module_ *m = findModule	(nModuleId);
	if (m != 0){

		if (m->mySub->first()){
			*acName = m->mySub->getName();
			*nId = m->mySub->getId();

      *nType = m->mySub->typeVar(m->acName, acSub, *nId);
			*a = m->mySub->getArrayVar(m->acName, acSub, *nId);
      *bStatic = m->mySub->isStatic(*nId);
			*nScope = m->mySub->getScope(*nId);
			
			return true;

		}
	}
	return false;
}

bool		memory_module::getSubVar	(int nModuleId, const char *acSub, const char *acName, int *nId, int *nType, t_array **a, bool *bStatic, int *nScope)
{
	module_ *m = findModule	(nModuleId);
	if (m != 0){

		*nId = m->mySub->getIdVar(m->acName, acSub, acName);

		acName = m->mySub->getName(*nId);
    *nType = m->mySub->typeVar(m->acName, acSub, *nId);
		*a = m->mySub->getArrayVar(m->acName, acSub, *nId);
    *bStatic = m->mySub->isStatic(*nId);
		*nScope = m->mySub->getScope(*nId);
		return true;

	}
  return false;
}

bool		memory_module::existSubVar	(int nModuleId, const char *acSub, const char *acName)
{
	module_ *m = findModule	(nModuleId);
	if (m != 0){

		return m->mySub->existVar(m->acName, acSub, acName);

	}
	return false;
}

bool		memory_module::existSubVar	(const char *acModuleName, const char *acSub, const char *acName)
{
	module_ *m = findModule	(getId(acModuleName));
	if (m != 0){

		return m->mySub->existVar(m->acName, acSub, acName);

	}
	return false;
}

bool		memory_module::findSubVar	(int nModuleId, int nSubId, int nId, const char **acModule, const char **acSub, const char **acName)
{
	module_ *m = findModule	(nModuleId);
	if (m != 0){
		return m->mySub->findVar(nSubId, nId, acModule, acSub, acName);
	}
	return false;
}

int		memory_module::getIdSubVar				(int nModuleId, const char *acSub, const char *acName)
{
	module_ *m = findModule	(nModuleId);
	if (m != 0){

    //do {
      int n =  m->mySub->getIdVar(m->acName, acSub, acName);
      return n;

    //} while ((m = findModule	(m->nExtend)) != 0);

	}
	return 0;
}

int		memory_module::getIdSubVar				(const char *acModuleName, const char *acSub, const char *acName)
{
  return getIdSubVar(getId(acModuleName), acSub, acName);
}

int		memory_module::typeSubVar				(const char *acModuleName, const char *acSub, const char *acName)
{
	module_ *m = findModule	(getId(acModuleName));
	if (m != 0){

		return m->mySub->typeVar(m->acName, acSub, acName);

	}
	return false;
}

bool		memory_module::isStaticSubVar				(const char *acModuleName, const char *acSub, const char *acName)
{
	module_ *m = findModule	(getId(acModuleName));
	if (m != 0){

		return m->mySub->isStaticVar(m->acName, acSub, acName);

	}
	return false;
}

	bool			isStaticSubVar				(const char *acModuleName, const char *acSub, const char *acName);


int		memory_module::typeSubVar				(const char *acModuleName, const char *acSub, int nVar)
{
	module_ *m = findModule	(getId(acModuleName));
	if (m != 0){

		return m->mySub->typeVar(m->acName, acSub, nVar);

	}
	return false;
}

memory_variable		*memory_module::getSubVars	(int nModuleId, const char *acSub)
{
	module_ *m = findModule	(nModuleId);
	if (m != 0){

		return m->mySub->getVars(m->acName, acSub, acSub);

	}
	return 0;
}

memory_variable		*memory_module::getSubVars	(const char *acModuleName, const char *acSub)
{
	return getSubVars(getId(acModuleName), acSub);
}

bool		memory_module::functionSub	(int nModuleId, int nId)
{
	module_ *m = findModule	(nModuleId);
	if (m != 0){

    return m->mySub->function(nId);

	}
	return false;
}

t_array *memory_module::getArraySubVar	(int nModuleId, const char *acSub, int nVar)
{
	module_ *m = findModule	(nModuleId);
	if (m != 0){

    return m->mySub->getArrayVar(m->acName, acSub, nVar);

	}
	return false;
}

t_array *memory_module::getArraySubVar	(const char *acModuleName, const char *acSub, const char *acName)
{
	module_ *m = findModule	(getId(acModuleName));
	if (m != 0){

    return m->mySub->getArrayVar( m->acName, acSub, acName );

	}
	return false;
}

int memory_module::getLStringLenSubVar	(int nModuleId, const char *acSub, int nVar)
{
	module_ *m = findModule	(nModuleId);
	if (m != 0){

    return m->mySub->getLStringLenVar(m->acName, acSub, nVar);

	}
	return false;
}

int memory_module::getLStringLenSubVar	(const char *acModuleName, const char *acSub, const char *acName)
{
	module_ *m = findModule	(getId(acModuleName));
	if (m != 0){

    return m->mySub->getLStringLenVar( m->acName, acSub, acName );

	}
	return false;
}

int		memory_module::addSubConst(int nModuleId, const char *acSub, const char *acName, int nId)
{
	module_ *m = findModule	(nModuleId);
	if (m != 0){

    int nScope = token__PUBLIC;
		return m->mySub->addConst(nModuleId, acSub, acName, nScope, nId);

	}
	return 0;
}

bool		memory_module::firstSubConst	(int nModuleId, const char *acSub, const char **acName)
{
	module_ *m = findModule	(nModuleId);
	if (m != 0){

		if (m->mySub->first()){
			*acName = m->mySub->getName();
			return true;

		}
	}
	return false;
}

bool		memory_module::nextSubConst	(int nModuleId, const char *acSub, const char **acName)
{
  module_ *m = findModule	(nModuleId);
	if (m != 0){

		if (m->mySub->first()){
			*acName = m->mySub->getName();
			return true;

		}
	}
	return false;
}

bool		memory_module::getSubConst	(int nModuleId, const char *acSub, const char *acName)
{
	module_ *m = findModule	(nModuleId);
	if (m != 0){

		int nId = m->mySub->getIdConst(m->acName, acSub, acName);

		acName = m->mySub->getName(nId);
		return true;

	}
  return false;
}

bool		memory_module::existSubConst	(int nModuleId, const char *acSub, const char *acName)
{
	module_ *m = findModule	(nModuleId);
	if (m != 0){

		return m->mySub->existConst(m->acName, acSub, acName);

	}
	return false;
}

bool		memory_module::existSubConst	(const char *acModuleName, const char *acSub, const char *acName)
{
	module_ *m = findModule	(getId(acModuleName));
	if (m != 0){

		return m->mySub->existConst(m->acName, acSub, acName);

	}
	return false;
}

bool		memory_module::findSubConst	(int nModuleId, int nSubId, int nId, const char **acModuleName, const char **acSub, const char **acName)
{
	module_ *m = findModule	(nModuleId);
	if (m != 0){
		return m->mySub->findConst(nSubId, nId, acModuleName, acSub, acName);
	}
	return false;
}

int		memory_module::getIdSubConst				(int nModuleId, const char *acSub, const char *acName)
{
	module_ *m = findModule	(nModuleId);
	if (m != 0){

    //do {
      int n =  m->mySub->getIdConst(m->acName, acSub, acName);
      return n;

    //} while ((m = findModule	(m->nExtend)) != 0);

	}
	return 0;
}

int		memory_module::getIdSubConst				(const char *acModuleName, const char *acSub, const char *acName)
{
  return getIdSubConst(getId(acModuleName), acSub, acName);
}

memory_const		*memory_module::getSubConsts	(int nModuleId, const char *acSub)
{
	module_ *m = findModule	(nModuleId);
	if (m != 0){

		return m->mySub->getConsts(m->acName, acSub, acSub);

	}
	return 0;
}

memory_const		*memory_module::getSubConsts	(const char *acModuleName, const char *acSub)
{
	return getSubConsts(getId(acModuleName), acSub);
}

void memory_module::registerCatch(int nModuleId, pcode *pcodeCatch, int nCatchType, int nPcodePos, int nCatchPcodePos)
{

	module_ *m = findModule	(nModuleId);
	if (m != 0){

		if (m->nPcodeCatchCounter == MAX_SUB_USED){
			moduleError("too many sub catches");
			return;
		}

		m->pcodeCatch[m->nPcodeCatchCounter] = pcodeCatch;
		m->nPcodeCatch[m->nPcodeCatchCounter] = nPcodePos;
		m->nCatchType[m->nPcodeCatchCounter] = nCatchType;
		m->nCatchPcodePos[m->nPcodeCatchCounter++] = nCatchPcodePos;
		//m->nReturnPcodePos[m->nPcodeCatchCounter++] = nReturnPcodePos;

	}
}

bool		memory_module::firstPcodeCatch	(int nModuleId, pcode **pcodeCatch, int *nCatchType, int *nPcodeOffset, int *nCatchPcodePos)//, int *nReturnPcodePos)
{
	module_ *m = findModule	(nModuleId);
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

bool		memory_module::nextPcodeCatch	(int nModuleId, pcode **pcodeCatch, int *nCatchType, int *nPcodeOffset, int *nCatchPcodePos)//, int *nReturnPcodePos)
{
	module_ *m = findModule	(nModuleId);
	if (m != 0){

		m->nPcodeCatchIterator++;

		if (m->nPcodeCatchIterator < m->nPcodeCatchCounter){
			*pcodeCatch = m->pcodeCatch[m->nPcodeCatchIterator];
			*nPcodeOffset = m->nPcodeCatch[m->nPcodeCatchIterator];
			*nCatchType = m->nCatchType[m->nPcodeCatchIterator];
			return true;
		}
	}
	return false;
}
