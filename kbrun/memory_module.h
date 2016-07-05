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

#ifndef MEMORY_MODULE_H
#define MEMORY_MODULE_H

#include <qmap.h>


#include "const.h"
#include "interpreter_parameter.h"

#include "memory_sub.h"
#include "memory_variable.h"
#include "memory_const.h"


struct module_{
	char acName[MAX_IDENTIFIER];
	char acFile[MAX_FILENAMELEN];
	int pc_pos;
	//pcode *myPcode;
	int nId;
	bool bPcodeBuilt;
	bool bRegistered;
  bool bIsCached;  

  // *** CATCH  
	int nCatchType[MAX_SUB_USED];
	int nCatchPcodePos[MAX_SUB_USED];
	int nPcodeCatch[MAX_SUB_USED];
	pcode *pcodeCatch[MAX_SUB_USED]; 

	int nPcodeCatchCounter;
	int nPcodeCatchIterator;
  // ***

public:
	memory_sub *mySub;
	memory_sub *myPropertyGet;
	memory_sub *myPropertySet;
	memory_variable *vars;
	memory_const *consts;
};

class memory_module
{
public:
	memory_module				();
	~memory_module				();

	int 		addModule			 (const char *acName, pcode *myPcode, int pc_pos, const char *acFile, int nId = -1/*, int nExtend*/);

	int 		addModuleSub (
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
      , int nSubId = -1
		);

	

	bool 		exist				(int nModuleId);
	bool 		exist				(const char *acName);

	bool findVar(int nId, const char **acModule, const char **acSub, const char **acVar);
	bool findConst(int nId, const char **acModule, const char **acSub, const char **acVar);

	bool 		existSub	(int nModuleId, int nId);
	bool 		existSub (const char *acName, const char *acSub);
	bool 		existSub (int nModuleId, const char *acSub);

	char   *typeSub	(int nModuleId, int nId);
	char   *typeSub	(const char *acName, const char *acSub);

  char   *getFile			(int nModuleId);

	char   *getName			(int nModuleId);
	char   *getNameSub (int nModuleId, int nId);
	char   *getRealNameSub (int nModuleId, int nId);

	char   *getSuffixSub		(int nModuleId, int nId);

	int			getId				(const char *acName);
	int			getIdSub				(int nModuleId, const char *acSub);
	int			getIdSub				(const char *acName, const char *acSub);

	int			getParentId				(int nModuleId);
	int			getParentId				(const char *acName);

	int			getId				();
	int			getIdSub				();

	int			getParamCountSub(int nModuleId, int nId);

  bool		isCached(int nModuleId);
  bool		isCachedSub(int nModuleId, int nId);

	int			getPcodePos(int nModuleId);
	int			getPcodePosSub(int nModuleId, int nId);
	int			getTokenPosSub(int nModuleId, int nId);

	int			getParameterCountSub(int nModuleId, int nId);

	bool    functionSub			(int nModuleId, int nId);

	int getScopeSub		(int nModuleId, int nId);
	bool isStaticSub		(int nModuleId, int nId);
	bool isAbstractSub	(int nModuleId, int nId);

	bool 		findModule			(int nModuleId, char **acName, pcode **myPcode);

	//pcode *getPcode(const char *acName);
	pcode *getPcodeSub(const char *acName, const char *acSub);

	//pcode *getPcode(int nModuleId);
	pcode *getPcodeSub(int nModuleId, int nId);

	//pcode *getPcode();
	pcode *getPcodeSub();
  
	bool addThrowSub(int nModuleId, int nId, const char *acType);
	bool addThrowSub(const char *acName, const char *acSub, const char *acType);
	bool firstThrowSub	(int nModuleId, int nId, const char **acType);
	bool nextThrowSub	(int nModuleId, int nId, const char **acType);
	bool hasThrowSub	(int nModuleId, int nId, const char *acType);

	bool addParameterSub(int nModuleId, int nId, const char *acName, const char *acType, int nParameterCall, bool bOptional, bool bDefault, bool bParamArray, t_array *a, defaultvalue *defval, int *nParamId);
	bool firstParameterSub	(int nModuleId, int nId, const char **acName, const char **acType, int *nParameterCall, bool *bOptional, bool *bDefault, bool *bParamArray, t_array **a, defaultvalue **defval, int *nParamId);
	bool nextParameterSub	(int nModuleId, int nId, const char **acName, const char **acType, int *nParameterCall, bool *bOptional, bool *bDefault, bool *bParamArray, t_array **a, defaultvalue **defval, int *nParamId);
	bool lastParameterSub	(int nModuleId, int nId, const char **acName, const char **acType, int *nParameterCall, bool *bOptional, bool *bDefault, bool *bParamArray, t_array **a, defaultvalue **defval, int *nParamId);
	bool prevParameterSub	(int nModuleId, int nId, const char **acName, const char **acType, int *nParameterCall, bool *bOptional, bool *bDefault, bool *bParamArray, t_array **a, defaultvalue **defval, int *nParamId);
	bool getParameterSub	(int nModuleId, int nId, const char *acName, const char **acType, int *nParameterCall, bool *bOptional, bool *bDefault, bool *bParamArray, t_array **a, defaultvalue **defval, int *nParamId);
	bool hasParameterSub	(int nModuleId, int nId, const char *acName);
	bool findParameterSub	(int nModuleId, int nSubId, int nId, const char **acModuleName, const char **acSub, const char **acName);

	void registerCatch(int nModuleId, pcode *pcodeCall, int nCatchType, int nPcodePos, int nCatchPcodePos);
	bool firstPcodeCatch	(int nModuleId, pcode **pcodeCatch, int *nCatchType, int *nPcodeOffset, int *nCatchPcodePos);
	bool nextPcodeCatch	(int nModuleId, pcode **pcodeCatch, int *nCatchType, int *nPcodeOffset, int *nCatchPcodePos);

	bool registered(const char *acName);
	bool registeredSub(const char *acName, const char *acSub);

	bool registered(int nModuleId);
	bool registeredSub(int nModuleId, int nId);

	bool pcodeBuilt(const char *acName);
	bool pcodeBuiltSub(const char *acName, const char *acSub);

	bool pcodeBuilt(int nModuleId);
	bool pcodeBuiltSub(int nModuleId, int nId);

	void setPcodeBuilt(const char *acName, bool b);
	void setPcodeBuiltSub(const char *acName, const char *acSub, bool b);

	void setPcodeBuilt(int nModuleId, bool b);
	void setPcodeBuiltSub(int nModuleId, int nId, bool b);

	void registerCallSub(int nModuleId, int nId, pcode *pcodeCall, int nPcodePos, int nReturnPcodePos);
  void changeRegisterCallSub(pcode *p_old, pcode *pcodeCall, int nPcodePos);

	bool 		first(int idx = 0);
	bool 		next(int idx = 0);

	bool 		firstSub(int idx = 0);
	bool 		nextSub(int idx = 0);

	bool		firstPcodeCallSub	(int nModuleId, int nId, pcode **pcodeCall, int *nPcodeOffset);//, int *nReturnPcodePos);
	bool		nextPcodeCallSub	(int nModuleId, int nId, pcode **pcodeCall, int *nPcodeOffset);//, int *nReturnPcodePos);
	
	module_ *findModule	(const char *acModuleName);
	
	memory_sub *getSubs	(int nModuleId);
	memory_sub *getSubs	(const char *acModuleName);
	

	
  int addVar(int nModuleId, const char *acName, int nType, t_array *a, int nScope, int nLStringLen, int nId = -1);
  bool removeVar(int nModuleId, int nId);
	bool firstVar	(int nModuleId, const char **acName, int *nId, int *nType, t_array **a, int *nScope);
	bool nextVar	(int nModuleId, const char **acName, int *nId, int *nType, t_array **a, int *nScope);
	bool getVar	(int nModuleId, const char *acName, int *nId, int *nType, t_array **a, int *nScope);
	bool existVar	(int nModuleId, const char *acName);
	bool existVar	(const char *acModuleName, const char *acName);
	bool findVar	(int nModuleId, int nId, const char **acModuleName, const char **acSub, const char **acName);
	int			getIdVar				(int nModuleId, const char *acName);
	int			getIdVar				(const char *acModuleName, const char *acName);
	int			typeVar				(int nModuleId, int nId);
	int			typeVar				(const char *acModuleName, const char *acName);
	int			scopeVar				(int nModuleId, int nId);
	int			scopeVar				(const char *acModuleName, const char *acName);
	t_array  *getArrayVar		(int nModuleId, int nId);
	t_array  *getArrayVar		(const char *acModuleName, const char *acName);
	memory_variable *getVars	(int nModuleId);
	memory_variable *getVars	(const char *acModuleName);


	int addSubVar(int nModuleId, const char *acSub, const char *acName, int nType, t_array *a, bool bStatic, int nScope, int nLStringLen, int nId = -1);
  bool removeSubVar(int nModuleId, int nSubId, int nId);
	bool firstSubVar	(int nModuleId, const char *acSub, const char **acName, int *nId, int *nType, t_array **a, bool *bStatic, int *nScope);
	bool nextSubVar	(int nModuleId, const char *acSub, const char **acName, int *nId, int *nType, t_array **a, bool *bStatic, int *nScope);
	bool getSubVar	(int nModuleId, const char *acSub, const char *acName, int *nId, int *nType, t_array **a, bool *bStatic, int *nScope);
	bool existSubVar	(int nModuleId, const char *acSub, const char *acName);
	bool existSubVar	(const char *acModuleName, const char *acSub, const char *acName);
	bool findSubVar	(int nModuleId, int nSubId, int nId, const char **acModuleName, const char **acSub, const char **acName);
	int			getIdSubVar				(int nModuleId, const char *acSub, const char *acName);
	int			getIdSubVar				(const char *acModuleName, const char *acSub, const char *acName);
	int			typeSubVar				(const char *acModuleName, const char *acSub, const char *acName);
	int			typeSubVar				(const char *acModuleName, const char *acSub, int nVar);
	t_array  *getArraySubVar		(int nModuleId, const char *acSub, int nVar);
	t_array  *getArraySubVar		(const char *acModuleName, const char *acSub, const char *acName);
	memory_variable *getSubVars	(int nModuleId, const char *acSub);
	memory_variable *getSubVars	(const char *acModuleName, const char *acSub);
	bool			isStaticSubVar				(const char *acModuleName, const char *acSub, const char *acName);
  


	int addConst(int nModuleId, const char *acName, int nScope, int nId = -1);
	bool firstConst	(int nModuleId, const char **acName, int *nId, int *nScope);
	bool nextConst	(int nModuleId, const char **acName, int *nId, int *nScope);
	bool getConst	(int nModuleId, const char *acName, int *nId, int *nScope);
	bool existConst	(const char *acModuleName, const char *acName);
	bool existConst	(int nModuleId, const char *acName);
	bool findConst	(int nModuleId, int nId, const char **acModuleName, const char **acSub, const char **acName);
	int			getIdConst				(int nModuleId, const char *acName);
	int			getIdConst				(const char *acModuleName, const char *acName);
	bool isPublicConst (int nModuleId, int nId);
	bool isPublicConst (int nModuleId, const char *acName);
	memory_const *getConsts	(int nModuleId);
	memory_const *getConsts	(const char *acModuleName);


	int addSubConst(int nModuleId, const char *acSub, const char *acName, int nId = -1);
	bool firstSubConst	(int nModuleId, const char *acSub, const char **acName);
	bool nextSubConst	(int nModuleId, const char *acSub, const char **acName);
	bool getSubConst	(int nModuleId, const char *acSub, const char *acName);
	bool existSubConst	(int nModuleId, const char *acSub, const char *acName);
	bool existSubConst	(const char *acModuleName, const char *acSub, const char *acName);
	bool findSubConst	(int nModuleId, int nSubId, int nId, const char **acModuleName, const char **acSub, const char **acName);
	int			getIdSubConst				(int nModuleId, const char *acSub, const char *acName);
	int			getIdSubConst				(const char *acModuleName, const char *acSub, const char *acName);
	memory_const *getSubConsts	(int nModuleId, const char *acSub);
	memory_const *getSubConsts	(const char *acModuleName, const char *acSub);


private:
	bool moduleError(char *acmoduleError);

	module_ *newModule(const char *acName, pcode *myPcode, int pc_pos, const char *acFile/*, int nExtend*/);

	typedef QMap<int, module_*> map9;
	map9 list_module;
	QMap<QString, module_*> list_module2;
  map9::Iterator it[parser__MAX_ITERATOR];
  int idx; // idx and parser__MAX_ITERATOR needed for recursive calls

	int nIdCounter;
	module_ *findModule	(int nModuleId);


};

#endif
