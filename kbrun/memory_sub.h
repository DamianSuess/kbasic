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


#ifndef MEMORY_SUB_H
#define MEMORY_SUB_H

#include <qmap.h>



#include "const.h"
#include "interpreter_parameter.h"
#include "memory_variable.h"
#include "memory_const.h"



struct sub {
	char acModule[MAX_IDENTIFIER];
  int nModuleId;
	char acRealName[MAX_IDENTIFIER]; // is the same of one overloaded sub
	char acName[MAX_IDENTIFIER]; // overloaded sub contains a counter at the end
	char acSignature[MAX_IDENTIFIER * 10]; 
	char acSuffix[MAX_IDENTIFIER];
	char acReturnType[MAX_IDENTIFIER];
	int nReturnSize;

	char acParameter[MAX_PARAM][MAX_IDENTIFIER];
	char acParameterType[MAX_PARAM][MAX_IDENTIFIER];
	int  nParameterCall[MAX_PARAM]; // call by ref, call by val
	bool bParameterOptional[MAX_PARAM];
	bool bParameterDefault[MAX_PARAM];  
	bool bParameterParamArray[MAX_PARAM];
	int nParameterParamId[MAX_PARAM];
  

	defaultvalue defval[MAX_PARAM];

	t_array a[MAX_PARAM];
	int pc_pos;
	int pc_len;

	int nScope;

	int nParameterCounter;
	int nParameterIterator;

	pcode *myPcode;

	int nId;

	bool bRegistered;
	bool bPcodeBuilt;
	bool bCached;  

  // *** FUNCTION/SUB CALL, aber nicht methods
	// array of pcode address (jmp)
	int nPcodeCall[MAX_SUB_USED];
	//int nReturnPcodePos[MAX_SUB_USED];
	pcode *pcodeCall[MAX_SUB_USED];
	int nPcodeCallCounter;
	int nPcodeCallIterator;
  // ***

  // *** CATCH  
	int nCatchType[MAX_SUB_USED];
	int nCatchPcodePos[MAX_SUB_USED];
	int nPcodeCatch[MAX_SUB_USED];
	pcode *pcodeCatch[MAX_SUB_USED]; 

	int nPcodeCatchCounter;
	int nPcodeCatchIterator;
  // ***

	int nPcodeAddress; // address -> name of sub for interpreter debug print

	bool bFunction;
	bool bConstructor;
	bool bDestructor;
	bool bSignal;
	bool bSlot;

	char acThrowType[MAX_THROW][MAX_IDENTIFIER];
	int nThrowCounter;
	int nThrowIterator;

	int nTokenPos;
  int nTokenLinePos;
	bool bStatic;
	bool bAbstract;

  bool bDeclare;
	char acAlias[MAX_IDENTIFIER];
	char acLib[MAX_IDENTIFIER];
	char acLibCallSignature[MAX_IDENTIFIER * 10];  

	char acFile[MAX_FILENAMELEN];
	int nLine;

  memory_variable *vars;
  memory_const *consts;

};

class memory_sub
{
public:
	memory_sub				();
	~memory_sub				();

	int addSub (
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
    , int nSubId = -1
	);

	bool 		exist				(int nId);
	bool 		exist				(const char *acModule, const char *acName);
	//bool 		hasSubWithSignature (const char *acModule, const char *acSignature);  

	char   *type				(int nId);
	char   *type				(const char *acModule, const char *acName);
	
  char   *getModule		(int nId);

	char   *getModuleByModuleId		(int nModuleId);
	char   *getRealName	(int nId);
	char   *getName			(int nId);
	char   *getSignature			(int nId);
	char   *getSuffix		(int nId);
	char   *getAlias		(int nId);
	char   *getLib		(int nId);
	char   *getLibCallSignature			(int nId);
	int			getIdFromRealNameAndFileAndLine	(const char *acModule, const char *acRealName, const char *acFile, int nLine);
	//int			getIdFromSignature    (const char *acModule, const char *acSignature);
	int			getId				      (const char *acModule, const char *acName);
  int			getId					    (int nModuleId, const char *acName);  
  //int			getId					    (int nModuleId, int nId);
	char   *getModule		();
	char   *getRealName	();
	char   *getName			();
	char   *getSuffix		();
	char   *getAlias		();
	char   *getLib  		();
	char   *getLibCallSignature  ();
	int			getId				();

	int			getParamCount();
	int			getParamCount(int nId);

	int			getPcodePos(int nId);
	int			getPcodeLen(int nId);
	int			getTokenPos(int nId);
	int			getTokenLinePos(int nId);

	char   *getFile		(int nId);
	int			getLine(int nId);
	
	int			getParameterCount(int nId);

	bool    function			(int nId);
	bool    constructor		(int nId);
	bool    destructor		(int nId);
	bool    signal	  		(int nId);
	bool    slot    			(int nId);
	bool    declare  			(int nId);
//	bool		function			();

  bool		isCached(int nId);

	int getScope		(int nId);
	bool isPrivate	(int nId);
	bool isPublic 	(int nId);
	bool isProtected(int nId);
	bool isStatic		(int nId);
	bool isAbstract	(int nId);

	bool 	findSub			(int nId, const char **acModule, const char **acRealName, const char **acName, const char **acSuffix, const char **acReturnType, int *nReturnSize, pcode **myPcode, bool *function);
  char  *getNameFromRealNameAndFileAndLine(const char *acModule, const char *acRealName, const char *acFile, int nLine);
  char  *getRealNameFromName(const char *acModule, const char *acName);

	pcode *getPcode(const char *acModule, const char *acName);
	pcode *getPcode(int nId);
	pcode *getPcode();

	int addVar(int nModuleId, const char *acSub, const char *acName, int nType, t_array *a, bool bStatic, int nScope, int nLStringLen, int nId = -1);
	bool removeVar(int nModuleId, int nId);
	bool firstVar	(int nModuleId, const char *acSub, const char **acName, int *nIdVar, int *nType, t_array **a, bool *bStatic, int *nScope);
	bool nextVar	(int nModuleId, const char *acSub, const char **acName, int *nIdVar, int *nType, t_array **a, bool *bStatic, int *nScope);
	bool getVar	(int nModuleId, const char *acSub, const char *acName, int *nIdVar, int *nType, t_array **a, bool *bStatic, int *nScope);
	bool existVar	(const char *acModule, const char *acSub, const char *acName);
 	bool findVar	(int nModuleId, int nId, const char **acModule, const char **acSub, const char **acName);
	int			getIdVar			(const char *acModule, const char *acSub, const char *acName);
	int			typeVar				(const char *acModule, const char *acSub, const char *acName);
	int			typeVar				(const char *acModule, const char *acSub, int nIdVar);
	t_array  *getArrayVar		(const char *acModule, const char *acSub, const char *acName);
	t_array  *getArrayVar		(const char *acModule, const char *acSub, int nIdVar);
	bool			isStaticVar				(const char *acModule, const char *acSub, const char *acName);

	memory_variable *getVars	(int nId);
	memory_variable *getVars	(const char *acModule, const char *acSub, const char *acName);


	int addConst(int nModuleId, const char *acSub, const char *acName, int nScope, int nId = -1);
	bool firstConst	(int nModuleId, const char *acSub, const char **acName, int *nScope);
	bool nextConst	(int nModuleId, const char *acSub, const char **acName, int *nScope);
	bool existConst	(const char *acModule, const char *acSub, const char *acName);
 	bool findConst	(int nModuleId, int nId, const char **acModule, const char **acSub, const char **acName);
	int			getIdConst			(const char *acModule, const char *acSub, const char *acName);

	memory_const *getConsts	(int nId);
	memory_const *getConsts	(const char *acModule, const char *acSub, const char *acName);


	bool addThrow(const char *acModule, const char *acName, const char *acType);
	bool addThrow(int nId, const char *acType);
	bool firstThrow	(int nId, const char **acType);
	bool nextThrow	(int nId, const char **acType);
	bool hasThrow	(int nId, const char *acType);

	bool addParameter(int nId, const char *acName, const char *acType, int nParameterCall, bool bOptional, bool bDefault, bool bParamArray, t_array *a, defaultvalue *defval, int *nParamId);
	bool firstParameter	(int nId, const char **acName, const char **acType, int *nParameterCall, bool *bOptional, bool *bDefault, bool *bParamArray, t_array **a, defaultvalue **defval, int *nParamId);
	bool nextParameter	(int nId, const char **acName, const char **acType, int *nParameterCall, bool *bOptional, bool *bDefault, bool *bParamArray, t_array **a, defaultvalue **defval, int *nParamId);
	bool lastParameter	(int nId, const char **acName, const char **acType, int *nParameterCall, bool *bOptional, bool *bDefault, bool *bParamArray, t_array **a, defaultvalue **defval, int *nParamId);
	bool prevParameter	(int nId, const char **acName, const char **acType, int *nParameterCall, bool *bOptional, bool *bDefault, bool *bParamArray, t_array **a, defaultvalue **defval, int *nParamId);
	bool getParameter	(int nId, const char *acName, const char **acType, int *nParameterCall, bool *bOptional, bool *bDefault, bool *bParamArray, t_array **a, defaultvalue **defval, int *nParamId);
	bool hasParameter	(int nId, const char *acName);
	bool findParameter	(int nSubId, int nId, const char **acModuleName, const char **acSub, const char **acName);

	bool registered(const char *acModule, const char *acName);
	bool registered(int nId);
	bool pcodeBuilt(const char *acModule, const char *acName);
	bool pcodeBuilt(int nId);
	void setPcodeBuilt(const char *acModule, const char *acName, bool b);
	void setPcodeBuilt(int nId, bool b);


	void registerCall(int nId, pcode *pcodeCall, int nPcodePos);//, int nReturnPcodePos);
  void changeRegisterCall(pcode *p_old, pcode *pcodeCall, int nPcodePos);

	void registerCatch(int nId, pcode *pcodeCall, int nCatchType, int nPcodePos, int nCatchPcodePos);
  //void changeRegisterCatch(pcode *p_old, pcode *pcodeCall, int nCatchType, int nPcodePos, int nCatchPcodePos);


	bool 		first(int idx = 0);
	bool 		next(int idx = 0);


	bool		firstPcodeCall	(int nId, pcode **pcodeCall, int *nPcodeOffset);//, int *nReturnPcodePos);
	bool		nextPcodeCall	(int nId, pcode **pcodeCall, int *nPcodeOffset);//, int *nReturnPcodePos);

	bool		firstPcodeCatch	(int nId, pcode **pcodeCatch, int *nCatchType, int *nPcodeOffset, int *nCatchPcodePos);
	bool		nextPcodeCatch	(int nId, pcode **pcodeCatch, int *nCatchType, int *nPcodeOffset, int *nCatchPcodePos);


	sub	*findSub	(int nId);

	char *getKeyFromRealNameAndFileAndLine(const char *acModule, const char *acRealName, const char *acFile, int nLine);
	char *getKey(const char *acModule, const char *acName);

private:
	bool subError(char *acsubError);

	sub *newSub (
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
	);


	typedef QMap<int, sub*> map9;
	map9 list_sub;
	QMap<QString, sub*> list_sub2;
	QMap<QString, sub*> list_sub3;
	QMap<int, sub*> list_sub4;  
	//QMap<QString, sub*> list_sub5;  

  map9::Iterator it[parser__MAX_ITERATOR];
  int idx; // idx and parser__MAX_ITERATOR needed for recursive calls


	int nIdCounter;

};

#endif
