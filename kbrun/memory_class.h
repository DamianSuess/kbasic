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


#ifndef MEMORY_CLASS_H
#define MEMORY_CLASS_H

#include <qmap.h>
#include <qstring.h>


#include "const.h"
#include "interpreter_parameter.h"

#include "memory_sub.h"
#include "memory_variable.h"
#include "memory_const.h"

struct class_{
public:
	char acName[MAX_IDENTIFIER];
 	char acFile[MAX_FILENAMELEN];
	int pc_pos;
	int pc_len;  
	pcode *myPcode;
	pcode *myClassStaticPcode;
	int nId;
	bool bPcodeBuilt;
	bool bRegistered;
  bool bIsAbstract;
  bool bIsCached;  
  bool bStatic;
	char acExtendName[MAX_IDENTIFIER];
	int nExtend;
  void *pExtend; // pointer to the originally c++ object

  int nCountMethod;
  int nCountPropertyGet;
  int nCountPropertySet;
  
  int nDestructorId;  

  // *** CATCH  
	int nCatchType[MAX_SUB_USED];
	int nCatchPcodePos[MAX_SUB_USED];
	int nPcodeCatch[MAX_SUB_USED];
	pcode *pcodeCatch[MAX_SUB_USED]; 

	int nPcodeCatchCounter;
	int nPcodeCatchIterator;
  // ***

	memory_sub *myPropertyGet;
	memory_sub *myPropertySet;
	memory_sub *mySub;
	memory_variable *vars;
	memory_variable *static_vars;
	memory_variable *staticCode_vars;  
	memory_const *consts;
};

class memory_class
{
public:
	memory_class				();
	~memory_class				();
   
	int 		addClass		(
    const char *acName, 
    pcode *myPcode, 
    pcode *myClassStaticPcode,     
    const char *acExtendName, 
    const char *acFile,
    bool bIsAbstract = false, int nId = -1
    );

	int 		addClassMethod (
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
      , int nSubId = -1
		);   

	int 		addClassPropertyGet (
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
     , int nSubId = -1
		);

	int 		addClassPropertySet (
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
     , int nSubId = -1
		);

	char *getKey(const char *acName);

  bool isSubClass(int nId, int nMaybeParentClass);
	

	bool 		exist				(int nClassId);
	bool 		exist				(const char *acName);

	bool findVar(int nId, const char **acModule, const char **acSub, const char **acVar);
	bool findConst(int nId, const char **acModule, const char **acSub, const char **acVar);

	bool 		existStatic				(int nClassId);
	bool 		existStatic				(const char *acName);

  bool 		existMethod	(int nClassId, int nId);
	bool 		existMethod (const char *acName, const char *acMethod);
	bool 		existMethod (int nClassId, const char *acMethod);
//	bool 		hasMethodWithSignature (int nClassId, const char *acSignature);  

  bool 		existPropertyGet	(int nClassId, int nId);
	bool 		existPropertyGet (const char *acName, const char *acMethod);
	bool 		existPropertyGet (int nClassId, const char *acMethod);
  bool 		existPropertySet	(int nClassId, int nId);
	bool 		existPropertySet (const char *acName, const char *acMethod);
	bool 		existPropertySet (int nClassId, const char *acMethod);
  
	bool 		setDestructorId				(int nClassId, int nDestructorId);
	int 		getDestructorId				(int nClassId);

  char   *getFile			(int nClassId);

	bool 		isAbstract				(int nClassId);
	bool 		isAbstract  (const char *acName);

  bool		isCached(int nClassId);

  bool 		isAbstractMethod	(int nClassId, int nId);
	bool 		isAbstractMethod (const char *acName, const char *acMethod);

  bool		isCachedConstructor(int nClassId, int nId);
  bool		isCachedDestructor(int nClassId, int nId);
  bool		isCachedMethod(int nClassId, int nId);
  bool		isCachedPropertyGet(int nClassId, int nId);
  bool		isCachedPropertySet(int nClassId, int nId);

	char   *typeMethod	(int nClassId, int nId);
	char   *typePropertyGet	(int nClassId, int nId);
	char   *typePropertySet	(int nClassId, int nId);
	char   *typeMethod	(const char *acName, const char *acMethod);
	char   *typePropertyGet	(const char *acName, const char *acMethod);
	char   *typePropertySet	(const char *acName, const char *acMethod);

	char   *getName			(int nClassId);
	char   *getParentName (int nClassId);
	char   *getNameMethod (int nClassId, int nId);
	char   *getRealNameMethod (int nClassId, int nId);  
	char   *getSignatureMethod (int nClassId, int nId);  
	char   *getNamePropertyGet (int nClassId, int nId);
	char   *getNamePropertySet (int nClassId, int nId);

	char   *getSuffixMethod		(int nClassId, int nId);
	char   *getSuffixPropertyGet		(int nClassId, int nId);
	char   *getSuffixPropertySet		(int nClassId, int nId);

	int			getId				(const char *acName);
	int			getIdMethod				(int nClassId, const char *acMethod);
	int			getIdMethod				(const char *acName, const char *acMethod);
	int			getIdPropertyGet			(int nClassId, const char *acProperty);
	int			getIdPropertyGet			(const char *acName, const char *acProperty);
	int			getIdPropertySet			(int nClassId, const char *acProperty);
	int			getIdPropertySet			(const char *acName, const char *acProperty);

	bool		setParentId				(int nClassId, int nParentId);
	int			getParentId				(int nClassId);
	int			getParentId				(const char *acName);

	int			getCountMethod				(int nClassId);
	int			getCountPropertyGet				(int nClassId);
	int			getCountPropertySet				(int nClassId);

//	char   *getName			();
//	char   *getNameMethod			();

//	char   *getSuffixMethod		();

	int			getId				();
	int			getIdMethod				();
	int			getIdPropertyGet		();
	int			getIdPropertySet		();


	int			getPcodePos(int nClassId);
	int			getPcodeLen(int nClassId);
	int			getPcodePosMethod(int nClassId, int nId);
	int			getPcodeLenMethod(int nClassId, int nId);
	int			getTokenPosMethod(int nClassId, int nId);
	int			getPcodePosPropertyGet(int nClassId, int nId);
	int			getTokenPosPropertyGet(int nClassId, int nId);
	int			getPcodePosPropertySet(int nClassId, int nId);
	int			getTokenPosPropertySet(int nClassId, int nId);


	bool    functionMethod			(int nClassId, int nId);
	bool    constructorMethod		(int nClassId, int nId);
	bool    destructorMethod		(int nClassId, int nId);

	int getScopeMethod		(int nClassId, int nId);
	int getScopePropertyGet	(int nClassId, int nId);
	int getScopePropertySet	(int nClassId, int nId);

	bool isStaticMethod		(int nClassId, int nId);

	bool 		findClass			(int nClassId, char **acName, pcode **myPcode);

	pcode *getPcode(const char *acName);
	pcode *getPcodeMethod(const char *acName, const char *acMethod);
	pcode *getPcodePropertyGet(const char *acName, const char *acProperty);
	pcode *getPcodePropertySet(const char *acName, const char *acProperty);

	pcode *getPcode(int nClassId);
	pcode *getClassStaticPcode(int nClassId); // static scope of class --> one block  
	pcode *getPcodeMethod(int nClassId, int nId);
	pcode *getPcodePropertyGet(int nClassId, int nId);
	pcode *getPcodePropertySet(int nClassId, int nId);

	pcode *getPcode();
	//pcode *getPcodeStatic(); // static methods
	pcode *getPcodeMethod();
	pcode *getPcodePropertyGet();
	pcode *getPcodePropertySet();

	bool addThrowMethod(int nClassId, int nId, const char *acType);
	bool addThrowMethod(const char *acName, const char *acMethod, const char *acType);
  
	bool firstThrowMethod	(int nClassId, int nId, const char **acType);
	bool nextThrowMethod	(int nClassId, int nId, const char **acType);
	bool hasThrowMethod	(int nClassId, int nId, const char *acType);

	bool addParameterMethod(int nClassId, int nId, const char *acName, const char *acType, int nParameterCall, bool bOptional, bool bDefault, bool bParamArray, t_array *a, defaultvalue *defval, int *nParamId);
	bool firstParameterMethod	(int nClassId, int nId, const char **acName, const char **acType, int *nParameterCall, bool *bOptional, bool *bDefault, bool *bParamArray, t_array **a, defaultvalue **defval, int *nParamId);
	bool nextParameterMethod	(int nClassId, int nId, const char **acName, const char **acType, int *nParameterCall, bool *bOptional, bool *bDefault, bool *bParamArray, t_array **a, defaultvalue **defval, int *nParamId);
	bool lastParameterMethod	(int nClassId, int nId, const char **acName, const char **acType, int *nParameterCall, bool *bOptional, bool *bDefault, bool *bParamArray, t_array **a, defaultvalue **defval, int *nParamId);
	bool prevParameterMethod	(int nClassId, int nId, const char **acName, const char **acType, int *nParameterCall, bool *bOptional, bool *bDefault, bool *bParamArray, t_array **a, defaultvalue **defval, int *nParamId);
	bool getParameterMethod	(int nClassId, int nId, const char *acName, const char **acType, int *nParameterCall, bool *bOptional, bool *bDefault, bool *bParamArray, t_array **a, defaultvalue **defval, int *nParamId);
	bool hasParameterMethod	(int nClassId, int nId, const char *acName);
	bool findParameterMethod	(int nClassId, int nMethodId, int nId, const char **acModuleName, const char **acSub, const char **acName);

  int	 getParameterCountMethod(int nClassId, int nId);


	bool addParameterPropertySet(int nClassId, int nId, const char *acName, const char *acType, int nParameterCall, bool bOptional, bool bDefault, bool bParamArray, t_array *a, defaultvalue *defval, int *nParamId);
	bool firstParameterPropertySet	(int nClassId, int nId, const char **acName, const char **acType, int *nParameterCall, bool *bOptional, bool *bDefault, bool *bParamArray, t_array **a, defaultvalue **defval, int *nParamId);
	bool nextParameterPropertySet	(int nClassId, int nId, const char **acName, const char **acType, int *nParameterCall, bool *bOptional, bool *bDefault, bool *bParamArray, t_array **a, defaultvalue **defval, int *nParamId);
	bool lastParameterPropertySet	(int nClassId, int nId, const char **acName, const char **acType, int *nParameterCall, bool *bOptional, bool *bDefault, bool *bParamArray, t_array **a, defaultvalue **defval, int *nParamId);
	bool prevParameterPropertySet	(int nClassId, int nId, const char **acName, const char **acType, int *nParameterCall, bool *bOptional, bool *bDefault, bool *bParamArray, t_array **a, defaultvalue **defval, int *nParamId);
	bool getParameterPropertySet	(int nClassId, int nId, const char *acName, const char **acType, int *nParameterCall, bool *bOptional, bool *bDefault, bool *bParamArray, t_array **a, defaultvalue **defval, int *nParamId);
	bool hasParameterPropertySet	(int nClassId, int nId, const char *acName);
	bool findParameterPropertySet	(int nClassId, int nMethodId, int nId, const char **acModuleName, const char **acSub, const char **acName);

  int	 getParameterCountPropertySet(int nClassId, int nId);


	bool registered(const char *acName);
	bool registeredMethod(const char *acName, const char *acMethod);
  bool registeredPropertyGet(const char *acName, const char *acProperty);
  bool registeredPropertySet(const char *acName, const char *acProperty);

	bool registered(int nClassId);
	bool registeredMethod(int nClassId, int nId);
	bool registeredPropertyGet(int nClassId, int nId);
	bool registeredPropertySet(int nClassId, int nId);

	bool pcodeBuilt(const char *acName);
	bool pcodeBuiltMethod(const char *acName, const char *acMethod);
	bool pcodeBuiltPropertyGet(const char *acName, const char *acProperty);
	bool pcodeBuiltPropertySet(const char *acName, const char *acProperty);

	bool pcodeBuilt(int nClassId);
	bool pcodeBuiltMethod(int nClassId, int nId);
	bool pcodeBuiltPropertyGet(int nClassId, int nId);
	bool pcodeBuiltPropertySet(int nClassId, int nId);

	void registerCatch(int nClassId, pcode *pcodeCall, int nCatchType, int nPcodePos, int nCatchPcodePos);
	bool firstPcodeCatch	(int nClassId, pcode **pcodeCatch, int *nCatchType, int *nPcodeOffset, int *nCatchPcodePos);
	bool nextPcodeCatch	(int nClassId, pcode **pcodeCatch, int *nCatchType, int *nPcodeOffset, int *nCatchPcodePos);

	void setPcodeBuilt(const char *acName, bool b);
	void setPcodeBuiltMethod(const char *acName, const char *acMethod, bool b);
	void setPcodeBuiltPropertyGet(const char *acName, const char *acMethod, bool b);
	void setPcodeBuiltPropertySet(const char *acName, const char *acMethod, bool b);

	void setPcodeBuilt(int nClassId, bool b);
	void setPcodeBuiltMethod(int nClassId, int nId, bool b);
	void setPcodeBuiltPropertyGet(int nClassId, int nId, bool b);
	void setPcodeBuiltPropertySet(int nClassId, int nId, bool b);

	void registerCallMethod(int nClassId, int nId, pcode *pcodeCall, int nPcodePos);//, int nReturnPcodePos);
	void registerCallPropertyGet(int nClassId, int nId, pcode *pcodeCall, int nPcodePos);//, int nReturnPcodePos);
	void registerCallPropertySet(int nClassId, int nId, pcode *pcodeCall, int nPcodePos);//, int nReturnPcodePos);

  void changeRegisterCallMethod(pcode *p_old, pcode *pcodeCall, int nPcodePos);
  void changeRegisterCallPropertyGet(pcode *p_old, pcode *pcodeCall, int nPcodePos);
  void changeRegisterCallPropertySet(pcode *p_old, pcode *pcodeCall, int nPcodePos);

	bool 		first(int idx = 0);
	bool 		gotoId(int nClassId, int idx = 0);
	bool 		next(int idx = 0);

	bool 		firstMethod(int idx = 0);
	bool 		nextMethod(int idx = 0);

	bool 		firstConstructor(int idx = 0);
	bool 		nextConstructor(int idx = 0);

	bool 		firstDestructor(int idx = 0);
	bool 		nextDestructor(int idx = 0);

	bool 		firstSignal(int idx = 0);
	bool 		nextSignal(int idx = 0);

	bool 		firstSlot(int idx = 0);
	bool 		nextSlot(int idx = 0);

	bool 		firstPropertyGet(int idx = 0);
	bool 		nextPropertyGet(int idx = 0);
	bool 		firstPropertySet(int idx = 0);
	bool 		nextPropertySet(int idx = 0);


//	bool		firstPcodeCall	(int nClassId, pcode **pcodeCall, int *nPcodeOffset, int *nReturnPcodePos);
//	bool		nextPcodeCall	(int nClassId, pcode **pcodeCall, int *nPcodeOffset, int *nReturnPcodePos);

	bool		firstPcodeCallMethod	(int nClassId, int nId, pcode **pcodeCall, int *nPcodeOffset);//, int *nReturnPcodePos);
	bool		nextPcodeCallMethod	(int nClassId, int nId, pcode **pcodeCall, int *nPcodeOffset);//, int *nReturnPcodePos);
	
	bool		firstPcodeCallPropertyGet	(int nClassId, int nId, pcode **pcodeCall, int *nPcodeOffset);//, int *nReturnPcodePos);
	bool		nextPcodeCallPropertyGet	(int nClassId, int nId, pcode **pcodeCall, int *nPcodeOffset);//, int *nReturnPcodePos);
	bool		firstPcodeCallPropertySet	(int nClassId, int nId, pcode **pcodeCall, int *nPcodeOffset);//, int *nReturnPcodePos);
	bool		nextPcodeCallPropertySet	(int nClassId, int nId, pcode **pcodeCall, int *nPcodeOffset);//, int *nReturnPcodePos);
	
	class_ *findClass	(const char *acClassName);
	
	memory_sub *getMethods	(int nClassId);
	memory_sub *getMethods	(const char *acClassName);
	
	memory_sub *getPropertiesGet	(int nClassId);
	memory_sub *getPropertiesGet	(const char *acClassName);
	memory_sub *getPropertiesSet	(int nClassId);
	memory_sub *getPropertiesSet	(const char *acClassName);
	

	int addVar(int nClassId, const char *acName, int nType, t_array *a, bool bStatic, int nScope, int nLStringLen, int nId = -1);
	bool removeVar(int nClassId, int nId);
	bool firstVar	(int nClassId, const char **acName, int *nId, int *nType, t_array **a, bool *bStatic, int *nScope);
	bool nextVar	(int nClassId, const char **acName, int *nId, int *nType, t_array **a, bool *bStatic, int *nScope);
	bool getVar	(int nClassId, const char *acName, int *nId, int *nType, t_array **a, bool *bStatic, int *nScope);
	bool existVar	(int nClassId, const char *acName);
	bool existVar	(const char *acClassName, const char *acName);
	bool findVar	(int nClassId, int nId, const char **acClass, const char **acMethod, const char **acVar);
	int			getIdVar				(int nClassId, const char *acName);
	int			getIdVar				(const char *acClassName, const char *acName);
	int			typeVar				(int nClassId, int nId);
	int			typeVar				(const char *acClassName, const char *acName);
	int			scopeVar				(int nClassId, int nId);
	int			scopeVar				(const char *acClassName, const char *acName);
	t_array  *getArrayVar		(int nClassId, int nId);
	t_array  *getArrayVar		(const char *acClassName, const char *acName);
	memory_variable *getVars	(int nClassId);
	memory_variable *getVars	(const char *acClassName);

	int addStaticVar(int nClassId, const char *acName, int nType, t_array *a, bool bStatic, int nScope, int nLStringLen, int nId = -1);
	bool firstStaticVar	(int nClassId, const char **acName, int *nId, int *nType, t_array **a, bool *bStatic, int *nScope);
	bool nextStaticVar	(int nClassId, const char **acName, int *nId, int *nType, t_array **a, bool *bStatic, int *nScope);
	bool getStaticVar	(int nClassId, const char *acName, int *nId, int *nType, t_array **a, bool *bStatic, int *nScope);
	bool existStaticVar	(int nClassId, const char *acName);
	bool existStaticVar	(const char *acClassName, const char *acName);
	bool findStaticVar	(int nClassId, int nId, const char **acClass, const char **acMethod, const char **acVar);
	int			getIdStaticVar				(int nClassId, const char *acName);
	int			getIdStaticVar				(const char *acClassName, const char *acName);
	int			typeStaticVar				(int nClassId, int nId);
	int			typeStaticVar				(const char *acClassName, const char *acName);
	int			scopeStaticVar				(int nClassId, int nId);
	int			scopeStaticVar				(const char *acClassName, const char *acName);
	t_array  *getArrayStaticVar		(int nClassId, int nId);
	t_array  *getArrayStaticVar		(const char *acClassName, const char *acName);
	memory_variable *getStaticVars	(int nClassId);
	memory_variable *getStaticVars	(const char *acClassName);

  // vars of static block of class
	int addStaticCodeVar(int nClassId, const char *acName, int nType, t_array *a, bool bStatic, int nScope);
	bool firstStaticCodeVar	(int nClassId, const char **acName, int *nId, int *nType, t_array **a, bool *bStaticCode, int *nScope);
	bool nextStaticCodeVar	(int nClassId, const char **acName, int *nId, int *nType, t_array **a, bool *bStaticCode, int *nScope);
	bool getStaticCodeVar	(int nClassId, const char *acName, int *nId, int *nType, t_array **a, bool *bStaticCode, int *nScope);
	bool existStaticCodeVar	(int nClassId, const char *acName);
	bool existStaticCodeVar	(const char *acClassName, const char *acName);
	bool findStaticCodeVar	(int nClassId, int nId, const char **acClass, const char **acMethod, const char **acVar);
	int			getIdStaticCodeVar				(int nClassId, const char *acName);
	int			getIdStaticCodeVar				(const char *acClassName, const char *acName);
	int			typeStaticCodeVar				(int nClassId, int nId);
	int			typeStaticCodeVar				(const char *acClassName, const char *acName);
	int			scopeStaticCodeVar				(int nClassId, int nId);
	int			scopeStaticCodeVar				(const char *acClassName, const char *acName);
	t_array  *getArrayStaticCodeVar		(int nClassId, int nId);
	t_array  *getArrayStaticCodeVar		(const char *acClassName, const char *acName);
	memory_variable *getStaticCodeVars	(int nClassId);
	memory_variable *getStaticCodeVars	(const char *acClassName);

	int addMethodVar(int nClassId, const char *acMethod, const char *acName, int nType, t_array *a, bool bStatic, int nScope, int nLStringLen, int nId = -1);
	bool removeMethodVar(int nClassId, int nMethodId, int nId);
	bool firstMethodVar	(int nClassId, const char *acMethod, const char **acName, int *nId, int *nType, t_array **a, bool *bStatic, int *nScope);
	bool nextMethodVar	(int nClassId, const char *acMethod, const char **acName, int *nId, int *nType, t_array **a, bool *bStatic, int *nScope);
	bool getMethodVar	(int nClassId, const char *acMethod, const char *acName, int *nId, int *nType, t_array **a, bool *bStatic, int *nScope);
	bool existMethodVar	(int nClassId, const char *acMethod, const char *acName);
	bool existMethodVar	(const char *acClassName, const char *acMethod, const char *acName);
	bool findMethodVar	(int nClassId, int nMethodId, int nId, const char **acClass, const char **acMethod, const char **acVar);
	int			getIdMethodVar				(int nClassId, const char *acMethod, const char *acName);
	int			getIdMethodVar				(const char *acClassName, const char *acMethod, const char *acName);
	int			typeMethodVar				(int nClassId, int nId);
	int			typeMethodVar				(const char *acClassName, const char *acMethod, const char *acName);
	int			typeMethodVar				(const char *acClassName, const char *acMethod, int nVar);
	t_array  *getArrayMethodVar		(int nClassId, const char *acMethod, int nVar);
	t_array  *getArrayMethodVar		(const char *acClassName, const char *acMethod, const char *acName);
	memory_variable *getMethodVars	(int nClassId, const char *acMethod);
	memory_variable *getMethodVars	(const char *acClassName, const char *acMethod);
	bool			isStaticMethodVar				(const char *acModuleName, const char *acSub, const char *acName);


	int addPropertyGetVar(int nClassId, const char *acProperty, const char *acName, int nType, t_array *a, bool bStatic, int nScope, int nLStringLen, int nId = -1);
	bool firstPropertyGetVar	(int nClassId, const char *acProperty, const char **acName, int *nId, int *nType, t_array **a, bool *bStatic, int *nScope);
	bool nextPropertyGetVar	(int nClassId, const char *acProperty, const char **acName, int *nId, int *nType, t_array **a, bool *bStatic, int *nScope);
	bool getPropertyGetVar	(int nClassId, const char *acProperty, const char *acName, int *nId, int *nType, t_array **a, bool *bStatic, int *nScope);
	bool existPropertyGetVar	(int nClassId, const char *acProperty, const char *acName);
	bool existPropertyGetVar	(const char *acClassName, const char *acProperty, const char *acName);
	bool findPropertyGetVar	(int nClassId, int nMethodId, int nId, const char **acClass, const char **acMethod, const char **acVar);
	int			getIdPropertyGetVar				(int nClassId, const char *acProperty, const char *acName);
	int			getIdPropertyGetVar				(const char *acClassName, const char *acProperty, const char *acName);
	int			typePropertyGetVar				(const char *acClassName, const char *acProperty, const char *acName);
	int			typePropertyGetVar				(const char *acClassName, const char *acProperty, int nVar);
	t_array  *getArrayPropertyGetVar		(int nClassId, const char *acProperty, int nVar);
	t_array  *getArrayPropertyGetVar		(const char *acClassName, const char *acProperty, const char *acName);
	memory_variable *getPropertyGetVars	(int nClassId, const char *acProperty);
	memory_variable *getPropertyGetVars	(const char *acClassName, const char *acProperty);

	int addPropertySetVar(int nClassId, const char *acProperty, const char *acName, int nType, t_array *a, bool bStatic, int nScope, int nLStringLen, int nId = -1);
	bool firstPropertySetVar	(int nClassId, const char *acProperty, const char **acName, int *nId, int *nType, t_array **a, bool *bStatic, int *nScope);
	bool nextPropertySetVar	(int nClassId, const char *acProperty, const char **acName, int *nId, int *nType, t_array **a, bool *bStatic, int *nScope);
	bool getPropertySetVar	(int nClassId, const char *acProperty, const char *acName, int *nId, int *nType, t_array **a, bool *bStatic, int *nScope);
	bool existPropertySetVar	(int nClassId, const char *acProperty, const char *acName);
	bool existPropertySetVar	(const char *acClassName, const char *acProperty, const char *acName);
	bool findPropertySetVar	(int nClassId, int nMethodId, int nId, const char **acClass, const char **acMethod, const char **acVar);
	int			getIdPropertySetVar				(int nClassId, const char *acProperty, const char *acName);
	int			getIdPropertySetVar				(const char *acClassName, const char *acProperty, const char *acName);
	int			typePropertySetVar				(const char *acClassName, const char *acProperty, const char *acName);
	int			typePropertySetVar				(const char *acClassName, const char *acProperty, int nVar);
	t_array  *getArrayPropertySetVar		(int nClassId, const char *acProperty, int nVar);
	t_array  *getArrayPropertySetVar		(const char *acClassName, const char *acProperty, const char *acName);
	memory_variable *getPropertySetVars	(int nClassId, const char *acProperty);
	memory_variable *getPropertySetVars	(const char *acClassName, const char *acProperty);


	int addConst(int nClassId, const char *acName, int nScope, int nId = -1);
	bool firstConst	(int nClassId, const char **acName, int *nId, int *nScope);
	bool nextConst	(int nClassId, const char **acName, int *nId, int *nScope);
	bool getConst	(int nClassId, const char *acName, int *nId, int *nScope);
	bool existConst	(int nClassId, const char *acName);
	bool existConst	(const char *acClassName, const char *acName);
	bool findConst	(int nClassId, int nId, const char **acClass, const char **acMethod, const char **acVar);
	int			getIdConst				(int nClassId, const char *acName);
	int			getIdConst				(const char *acClassName, const char *acName);
	bool isPublicConst (int nClassId, int nId);
	bool isPublicConst (int nClassId, const char *acName);
	memory_const *getConsts	(int nClassId);
	memory_const *getConsts	(const char *acClassName);

	int addMethodConst(int nClassId, const char *acMethod, const char *acName, int nId = -1);
	bool firstMethodConst	(int nClassId, const char *acMethod, const char **acName);
	bool nextMethodConst	(int nClassId, const char *acMethod, const char **acName);
	bool getMethodConst	(int nClassId, const char *acMethod, const char *acName);
	bool existMethodConst	(int nClassId, const char *acMethod, const char *acName);
	bool existMethodConst	(const char *acClassName, const char *acMethod, const char *acName);
	bool findMethodConst	(int nClassId, int nMethodId, int nId, const char **acClass, const char **acMethod, const char **acVar);
	int			getIdMethodConst				(int nClassId, const char *acMethod, const char *acName);
	int			getIdMethodConst				(const char *acClassName, const char *acMethod, const char *acName);
	memory_const *getMethodConsts	(int nClassId, const char *acMethod);
	memory_const *getMethodConsts	(const char *acClassName, const char *acMethod);

/*
	int addPropertyGetConst(int nClassId, const char *acMethod, const char *acName, int nId = 0);
	bool firstPropertyGetConst	(int nClassId, const char *acMethod, const char **acName);
	bool nextPropertyGetConst	(int nClassId, const char *acMethod, const char **acName);
	bool getPropertyGetConst	(int nClassId, const char *acMethod, const char *acName);
	bool existPropertyGetConst	(int nClassId, const char *acMethod, const char *acName);
	bool existPropertyGetConst	(const char *acClassName, const char *acMethod, const char *acName);
	bool findPropertyGetConst	(int nClassId, int nMethodId, int nId, const char **acClass, const char **acMethod, const char **acVar);
	int			getIdPropertyGetConst				(int nClassId, const char *acMethod, const char *acName);
	int			getIdPropertyGetConst				(const char *acClassName, const char *acMethod, const char *acName);
	memory_const *getPropertyGetConsts	(int nClassId, const char *acMethod);
	memory_const *getPropertyGetConsts	(const char *acClassName, const char *acMethod);


	int addPropertySetConst(int nClassId, const char *acMethod, const char *acName, int nId = 0);
	bool firstPropertySetConst	(int nClassId, const char *acMethod, const char **acName);
	bool nextPropertySetConst	(int nClassId, const char *acMethod, const char **acName);
	bool getPropertySetConst	(int nClassId, const char *acMethod, const char *acName);
	bool existPropertySetConst	(int nClassId, const char *acMethod, const char *acName);
	bool existPropertySetConst	(const char *acClassName, const char *acMethod, const char *acName);
	bool findPropertySetConst	(int nClassId, int nMethodId, int nId, const char **acClass, const char **acMethod, const char **acVar);
	int			getIdPropertySetConst				(int nClassId, const char *acMethod, const char *acName);
	int			getIdPropertySetConst				(const char *acClassName, const char *acMethod, const char *acName);
	memory_const *getPropertySetConsts	(int nClassId, const char *acMethod);
	memory_const *getPropertySetConsts	(const char *acClassName, const char *acMethod);
*/

	bool findPropertyGetConst	(int nClassId, int nMethodId, int nId, const char **acClass, const char **acMethod, const char **acVar);
	bool findPropertySetConst	(int nClassId, int nMethodId, int nId, const char **acClass, const char **acMethod, const char **acVar);

  class_ *findClass	(int nClassId);

private:
	bool classError(char *acclassError);

	class_ *newClass(
    const char *acName, 
    pcode *myPcode, 
    pcode *myClassStaticPcode,     
    const char *acExtendName,
    const char *acFile,
    bool bIsAbstract
    );

	int nIdCounter;

protected:
	typedef QMap<int, class_*> map9;
	map9 list_class;
	QMap<QString, class_*> list_class2;
  map9::Iterator it[parser__MAX_ITERATOR];
  int idx; // idx and parser__MAX_ITERATOR needed for recursive calls




};
#endif
