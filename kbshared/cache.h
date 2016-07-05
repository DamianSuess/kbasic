/*
***************************************************************************
Copyright (C) 2000-2008 KBasic Software (Bernd Noetscher, Boseweg 9, 60529 Frankfurt / Germany).  All rights reserved.

_cache.h
---------------------------------------------------------------------------
19.02.2004 - new header for this file (BN)
***************************************************************************
*/



#ifndef CACHE_H
#define CACHE_H

#include "typedef.h"

#ifdef KBIDE
#else

#ifdef KBC
#include "../kbc/XString.h"
#include "../kbc/XIntMap.h"

#define GETX getX(acFile)
#define GETXX getXX(acFile)
#define GETXXX getXXX(acFile)


#else

#define GETX ppp
#define GETXX ppp
#define GETXXX ppp

#endif

#include "../kbshared/pcode.h"

class parser;
class pcode;
class token;
class _mainwindow;


/*

abhängigkeit: constbenutzung, variablenbenutzung, methodenbenutzung, typbenuztzung

xyz.scanner wird gebraucht falls, referencens innerhalb von xyz.parser sich ändern durch änderung in andere source datei

files: cache/xyz.scanner   xyz.parser(wie original pcode) 1. .2 .3 .4 verschiedene modi = bSilent, bDebug

datatypes: t_array, defaultvalue

*/


const t_pcode memory_type_addType			          = 1;
const t_pcode memory_type_addElement            = 2;

const t_pcode memory_enum_addEnum			          = 3;
const t_pcode memory_enum_addElement            = 4;

const t_pcode memory_stringliteral_declare      = 5;

const t_pcode memory_module_addModule           = 6;
const t_pcode memory_module_addModuleSub        = 7;
const t_pcode memory_module_addThrowSub         = 8;
const t_pcode memory_module_addParameterSub     = 9;
const t_pcode memory_module_registerCatch       = 10;
const t_pcode memory_module_registerCallSub     = 11;
const t_pcode memory_module_addVar              = 12;
const t_pcode memory_module_addConst            = 13;
const t_pcode memory_module_addSubVar           = 14;
const t_pcode memory_module_addSubConst         = 15;
const t_pcode memory_module_changeRegisterCallSub  = 55;




const t_pcode memory_class_addClass                 = 17;
const t_pcode memory_class_addClassMethod           = 18;
const t_pcode memory_class_addClassPropertyGet      = 19;
const t_pcode memory_class_addClassPropertySet      = 20;
const t_pcode memory_class_addThrowMethod           = 21;
const t_pcode memory_class_addParameterMethod       = 22;
const t_pcode memory_class_addParameterPropertySet  = 23;
const t_pcode memory_class_registerCallMethod       = 24;
const t_pcode memory_class_registerCallPropertyGet  = 25;
const t_pcode memory_class_registerCallPropertySet  = 26;
const t_pcode memory_class_addVar                   = 27;
const t_pcode memory_class_addStaticVar             = 28;
const t_pcode memory_class_addConst                 = 29;
const t_pcode memory_class_addMethodVar             = 30;
const t_pcode memory_class_addPropertyGetVar        = 31;
const t_pcode memory_class_addPropertySetVar        = 32;
const t_pcode memory_class_addMethodConst           = 33;
const t_pcode memory_class_registerCatch            = 34;

const t_pcode dependency                            = 35;
const t_pcode memory_class_bindingparam             = 36;

const t_pcode memory_variable_setIdCounter             = 37;

const t_pcode version                               = 38;

const t_pcode memory_module_addVar_defaultkbasic              = 39;

const t_pcode dependency_globalvar                         = 40;

const t_pcode memory_class_addPropertyGetConst           = 41;
const t_pcode memory_class_addPropertySetConst           = 42;

const t_pcode pcodeBlock                        = 255;


enum t_pcodeCache {
  declaration2 = 0,
  statements2,
  sub2,
};


class cache //: public pcode
{
public:
  cache(/*_mainwindow *m*/);
  ~cache();

  bool doParser(parser *p, const char *acFile, int nPhase, bool *bDependencyFailed = 0, bool *bVersionFailed = 0);

#ifdef KBC
  bool readScanner(const char *acFile, token *t, bool bInsert = false);
  void writeScanner(const char *acFile, token *t, int nTokenFromPos);

  //void parserSetFile(const char *acFile);
  void setMode(bool bSilent, bool bDebug, bool bCodeInsight = false)
  { 
    if (bCodeInsight) acMode = "4";

    else if (bSilent && bDebug) acMode = "0";
    else if (!bSilent && bDebug) acMode = "1";
    else if (bSilent && !bDebug) acMode = "2";
    else if (!bSilent && !bDebug) acMode = "3";
  }
  const char *acMode;

  void wr_parserOpen(parser *p, const char *acFile);
  void wr_parserCloseAll(bool bSave);

  bool parserOpened(const char *acFile)
  {
    return ff.contains(acFile);
  } 

  //bool checkDependencyFor(const char *acFile);

  inline pcode *getX(const char *acFile)
  {
    static pcode *p = 0;

    if (acLastFile == acFile) return p;

    acLastFile = acFile;
    p = (pcode *) x.getString(acFile);
    return p;
  }

  inline pcode *getXX(const char *acFile)
  {
    static pcode *p = 0;

    if (acLastFile2 == acFile) return p;

    acLastFile2 = acFile;
    p = (pcode *) xx.getString(acFile);
    return p;
  }

  inline pcode *getXXX(const char *acFile)
  {
    static pcode *p = 0;

    if (acLastFile3 == acFile) return p;

    acLastFile3 = acFile;
    p = (pcode *) xxx.getString(acFile);
    return p;
  }

  const char *acLastFile;
  const char *acLastFile2;
  const char *acLastFile3;

  void initParser();
  void deinitParser();


  bool isParserValid(const char *acFile);
  bool readParserPhase0(const char *acFile, parser *p, bool bFirst, bool *bDependencyFailed, bool *bVersionFailed);
  bool readParserPhase1(const char *acFile, parser *p, bool bFirst);

  void deleteParser(const char *acFile);



  XString changeFilenameWithoutPathSeparators(XString filename)
  { 
    XString s = filename;
    s = s.replace("\\", "_");
    s = s.replace("/", "_");
    s = s.replace(":", "_");

    return s; 
  }
/*
  QString getFilenameWithoutPath(QString filename)
  { 
    QString s = filename;
    int i = s.findRev('\\');
    if (i == -1){
      i = s.findRev('/');
    }
    s = s.right(s.length() - i - 1);

    i = s.findRev('.');

    s = s.left(i);

    return s; 
  }
*/

  pcode *getNewPcode(int pcode);
#endif

  void rd_dependency(const char *acFile, t_builtin *c, t_cstring *acDependency){ *c = GETX->rd_PCode(); *acDependency = GETX->rd_CString(); }
  void wr_dependency(const char *acFile, t_builtin c, t_cstring acDependency){ GETXXX->wr_PCode(c) ; GETXXX->wr_CString(acDependency) ; }

  void rd_dependency_globalvar(const char *acFile, t_builtin *c, t_integer *nId){ *c = GETX->rd_PCode(); *nId = GETX->rd_Integer(); }
  void wr_dependency_globalvar(const char *acFile, t_builtin c, t_integer nId){ GETXXX->wr_PCode(c) ; GETXXX->wr_Integer(nId) ; }

  void rd_version(const char *acFile, t_builtin *c, t_double *version){ *c = GETX->rd_PCode(); *version = GETX->rd_Double(); }
  void wr_version(const char *acFile, t_builtin c, t_double version){ GETXXX->wr_PCode(c) ; GETXXX->wr_Double(version) ; }


  void rd_pcodeBlock(const char *acFile, t_builtin *c, t_integer *p, t_integer *len, void **pcodeNew, t_pcodeCache *t){ *c = GETX->rd_PCode(); *p = GETX->rd_Integer(); *len = GETX->rd_Integer(); *t = (t_pcodeCache) GETX->rd_Integer(); *pcodeNew = GETX->rd_Struct2(*len);  }
  void wr_pcodeBlock(const char *acFile, t_builtin c, pcode *p, t_integer len, t_pcodeCache t, pcode *p2 = 0, int nOffset2 = 0){ 
    GETXX->wr_PCode(c) ; GETXX->wr_Integer((t_integer) p) ; GETXX->wr_Integer(len) ; GETXX->wr_Integer((t_pcodeCache) t) ; p2 ? GETXX->wr_Struct(len, p2->ba->getMem() + nOffset2) : GETXX->wr_Struct(len, p->ba->getMem()) ; 
  }


  
  void rd_memory_variable_setIdCounter(pcode *p, t_builtin *c, t_integer *n){ 
    *c = p->rd_PCode(); *n = p->rd_Integer(); 
  }
  void wr_memory_variable_setIdCounter(pcode *p, t_builtin c, t_integer n){ 
    p->wr_PCode(c) ; p->wr_Integer(n) ;
  }

  void rd_memory_type_addType(const char *acFile, t_builtin *c, t_integer *ID, t_cstring *acModule, t_cstring *acName, t_integer *nScope, t_integer *nId){ *c = GETX->rd_PCode(); *ID = GETX->rd_Integer(); *acModule = GETX->rd_CString(); *acName = GETX->rd_CString(); *nScope = GETX->rd_Integer(); *nId = GETX->rd_Integer(); }
  void wr_memory_type_addType(const char *acFile, t_builtin c, t_integer ID, t_cstring acModule, t_cstring acName, t_integer nScope, t_integer nId){ GETX->wr_PCode(c) ; GETX->wr_Integer(ID) ; GETX->wr_CString(acModule) ; GETX->wr_CString(acName) ; GETX->wr_Integer(nScope) ; GETX->wr_Integer(nId) ; }

  void rd_memory_type_addElement(const char *acFile, t_builtin *c, t_integer *ID, t_integer *nId, t_cstring *acElementName, t_cstring *acElementType, t_integer *nElementSize, t_array *a, t_integer *nElementId){ *c = GETX->rd_PCode(); *ID = GETX->rd_Integer(); *nId = GETX->rd_Integer(); *acElementName = GETX->rd_CString(); *acElementType = GETX->rd_CString(); *nElementSize = GETX->rd_Integer(); GETX->rd_Array(a); *nElementId = GETX->rd_Integer(); }
  void wr_memory_type_addElement(const char *acFile, t_builtin c, t_integer ID, t_integer nId, t_cstring acElementName, t_cstring acElementType, t_integer nElementSize, t_array *a, t_integer nElementId){ GETX->wr_PCode(c) ; GETX->wr_Integer(ID) ; GETX->wr_Integer(nId) ; GETX->wr_CString(acElementName) ; GETX->wr_CString(acElementType) ; GETX->wr_Integer(nElementSize) ; GETX->wr_Array(a) ; GETX->wr_Integer(nElementId) ; }

  void rd_memory_enum_addEnum(const char *acFile, t_builtin *c, t_integer *ID, t_cstring *acModule, t_cstring *acName, t_integer *nScope, t_integer *nId){ *c = GETX->rd_PCode(); *ID = GETX->rd_Integer(); *acModule = GETX->rd_CString(); *acName = GETX->rd_CString(); *nScope = GETX->rd_Integer(); *nId = GETX->rd_Integer(); }
  void wr_memory_enum_addEnum(const char *acFile, t_builtin c, t_integer ID, t_cstring acModule, t_cstring acName, t_integer nScope, t_integer nId){ GETX->wr_PCode(c) ; GETX->wr_Integer(ID) ; GETX->wr_CString(acModule) ; GETX->wr_CString(acName) ; GETX->wr_Integer(nScope) ; GETX->wr_Integer(nId) ; }

  void rd_memory_enum_addElement(const char *acFile, t_builtin *c, t_integer *ID, t_integer *nId, t_cstring *acElementName, t_cstring *acElementType, t_integer *nElementSize, t_integer *nElementId){ *c = GETX->rd_PCode(); *ID = GETX->rd_Integer(); *nId = GETX->rd_Integer(); *acElementName = GETX->rd_CString(); *acElementType = GETX->rd_CString(); *nElementSize = GETX->rd_Integer(); *nElementId = GETX->rd_Integer(); }
  void wr_memory_enum_addElement(const char *acFile, t_builtin c, t_integer ID, t_integer nId, t_cstring acElementName, t_cstring acElementType, t_integer nElementSize, t_integer nElementId){ GETX->wr_PCode(c) ; GETX->wr_Integer(ID) ; GETX->wr_Integer(nId) ; GETX->wr_CString(acElementName) ; GETX->wr_CString(acElementType) ; GETX->wr_Integer(nElementSize) ; GETX->wr_Integer(nElementId) ; }

  void rd_memory_stringliteral_declare(const char *acFile, t_builtin *c, t_integer *ID, t_cstring *acName, t_integer *nId){ *c = GETX->rd_PCode(); *ID = GETX->rd_Integer(); *acName = GETX->rd_CString();  *nId = GETX->rd_Integer(); }
  void wr_memory_stringliteral_declare(const char *acFile, t_builtin c, t_integer ID, t_cstring acName, t_integer nId){ GETX->wr_PCode(c) ; GETX->wr_Integer(ID) ; GETX->wr_CString(acName) ; GETX->wr_Integer(nId) ; }

  void rd_memory_module_addModule(const char *acFile, t_builtin *c, t_integer *ID, t_cstring *acName, t_integer *p, t_integer *pc_pos){ *c = GETX->rd_PCode(); *ID = GETX->rd_Integer(); *acName = GETX->rd_CString(); *p = GETX->rd_Integer(); *pc_pos = GETX->rd_Integer(); }
  void wr_memory_module_addModule(const char *acFile, t_builtin c, t_integer ID, t_cstring acName, pcode *p, t_integer pc_pos){ GETX->wr_PCode(c) ; GETX->wr_Integer(ID) ; GETX->wr_CString(acName) ; GETX->wr_Integer((t_integer) p) ; GETX->wr_Integer(pc_pos) ; }

  void rd_memory_module_addModuleSub(const char *acFile, t_builtin *c, t_integer *ID,
			t_cstring *acModuleName, 
			t_cstring *acRealName, 
			t_cstring *acName, 
			t_cstring *acSuffix, 
			t_cstring *acReturnType, 
			t_integer *nReturnSize, 
			t_integer *myPcode, 
			t_boolean *function, 
			t_integer *pc_pos, 
			t_integer *nScope, 
			t_integer *nTokenPos,
			t_integer *nTokenLinePos,
			t_boolean *bStatic,
			t_boolean *bAbstract,
      t_cstring *acFile2,
      t_integer *nLine,
      t_boolean *bDeclare,
      t_cstring *acAlias,
      t_cstring *acLib,
      t_cstring *acLibCallSignature      
      ){
         *c = GETX->rd_PCode(); *ID = GETX->rd_Integer(); 
         *acModuleName = GETX->rd_CString(); 
         *acRealName = GETX->rd_CString(); 
         *acName = GETX->rd_CString(); 
         *acSuffix = GETX->rd_CString(); 
         *acReturnType = GETX->rd_CString(); 
         *nReturnSize = GETX->rd_Integer(); 
         *myPcode = GETX->rd_Integer(); 
         *function = GETX->rd_Boolean(); 
         *pc_pos = GETX->rd_Integer(); 
         *nScope = GETX->rd_Integer(); 
         *nTokenPos = GETX->rd_Integer(); 
         *nTokenLinePos = GETX->rd_Integer(); 
         *bStatic = GETX->rd_Boolean(); 
         *bAbstract = GETX->rd_Boolean(); 
         *acFile2 = GETX->rd_CString(); 
         *nLine = GETX->rd_Integer(); 
         *bDeclare = GETX->rd_Boolean(); 
         *acAlias = GETX->rd_CString(); 
         *acLib = GETX->rd_CString(); 
         *acLibCallSignature = GETX->rd_CString(); 
      }

  void wr_memory_module_addModuleSub(const char *acFile, t_builtin c, t_integer ID, 
			t_cstring acModuleName, 
			t_cstring acRealName, 
			t_cstring acName, 
			t_cstring acSuffix, 
			t_cstring acReturnType, 
			t_integer nReturnSize, 
			pcode *myPcode, 
			t_boolean function, 
			t_integer pc_pos, 
			t_integer nScope, 
			t_integer nTokenPos,
			t_integer nTokenLinePos,
			t_boolean bStatic,
			t_boolean bAbstract,
      t_cstring acFile2,
      t_integer nLine,
      t_boolean bDeclare,
      t_cstring acAlias,
      t_cstring acLib,
      t_cstring acLibCallSignature      
    ){ 
      GETX->wr_PCode(c) ; GETX->wr_Integer(ID) ; 
      GETX->wr_CString(acModuleName) ; 
      GETX->wr_CString(acRealName) ; 
      GETX->wr_CString(acName) ; 
      GETX->wr_CString(acSuffix) ; 
      GETX->wr_CString(acReturnType) ; 
      GETX->wr_Integer(nReturnSize) ; 
      GETX->wr_Integer((t_integer) myPcode) ; 
      GETX->wr_Boolean(function) ; 
      GETX->wr_Integer(pc_pos) ; 
      GETX->wr_Integer(nScope) ; 
      GETX->wr_Integer(nTokenPos) ; 
      GETX->wr_Integer(nTokenLinePos) ; 
      GETX->wr_Boolean(bStatic) ; 
      GETX->wr_Boolean(bAbstract) ; 
      GETX->wr_CString(acFile2) ; 
      GETX->wr_Integer(nLine) ; 
      GETX->wr_Boolean(bDeclare) ; 
      GETX->wr_CString(acAlias) ; 
      GETX->wr_CString(acLib) ; 
      GETX->wr_CString(acLibCallSignature) ; 
    }

  void rd_memory_module_addThrowSub(const char *acFile, t_builtin *c, t_integer *nModuleId, t_integer *nId, t_cstring *acType){ *c = GETX->rd_PCode(); *nModuleId = GETX->rd_Integer(); *nId = GETX->rd_Integer(); *acType = GETX->rd_CString(); }
  void wr_memory_module_addThrowSub(const char *acFile, t_builtin c, t_integer nModuleId, t_integer nId, t_cstring acType){ GETX->wr_PCode(c) ; GETX->wr_Integer(nModuleId) ; GETX->wr_Integer(nId) ; GETX->wr_CString(acType) ; }

  void rd_memory_module_addParameterSub(const char *acFile, t_builtin *c, t_integer *nModuleId, t_integer *nId, t_cstring *acName, t_cstring *acType, t_integer *nParameterCall, t_boolean *bOptional, t_boolean *bDefault, t_boolean *bParamArray, t_array *a, defaultvalue *defval, t_integer *nParamId, t_integer *nParamLStringLen){ 
    *c = GETX->rd_PCode(); 
    *nModuleId = GETX->rd_Integer(); 
    *nId = GETX->rd_Integer(); 
    *acName = GETX->rd_CString(); 
    *acType = GETX->rd_CString(); 
    *nParameterCall = GETX->rd_Integer(); 
    *bOptional = GETX->rd_Boolean(); 
    *bDefault = GETX->rd_Boolean(); 
    *bParamArray = GETX->rd_Boolean(); 
    GETX->rd_Array(a); 
    GETX->rd_Struct(sizeof(defaultvalue), defval); 
    *nParamId = GETX->rd_Integer(); 
    *nParamLStringLen = GETX->rd_Integer(); 
  }
  void wr_memory_module_addParameterSub(const char *acFile, t_builtin c, t_integer nModuleId, t_integer nId, t_cstring acName, t_cstring acType, t_integer nParameterCall, t_boolean bOptional, t_boolean bDefault, t_boolean bParamArray, t_array *a, defaultvalue defval, t_integer nParamId, t_integer nParamLStringLen){ 
    GETX->wr_PCode(c) ; GETX->wr_Integer(nModuleId) ; GETX->wr_Integer(nId) ; GETX->wr_CString(acName) ; GETX->wr_CString(acType) ; GETX->wr_Integer(nParameterCall) ; GETX->wr_Boolean(bOptional) ; GETX->wr_Boolean(bDefault) ; GETX->wr_Boolean(bParamArray) ; GETX->wr_Array(a) ; GETX->wr_Struct(sizeof(defaultvalue), &defval) ; GETX->wr_Integer(nParamId) ;GETX->wr_Integer(nParamLStringLen) ;  }


  void rd_memory_module_registerCatch(const char *acFile, t_builtin *c, t_integer *nModuleId, t_integer *pcodeCall, t_integer *nCatchType, t_integer *nPcodePos, t_integer *nCatchPcodePos){ *c = GETX->rd_PCode(); *nModuleId = GETX->rd_Integer(); *pcodeCall = GETX->rd_Integer(); *nCatchType = GETX->rd_Integer(); *nPcodePos = GETX->rd_Integer(); *nCatchPcodePos = GETX->rd_Integer(); }
  void wr_memory_module_registerCatch(const char *acFile, t_builtin c, t_integer nModuleId, t_integer pcodeCall, t_integer nCatchType, t_integer nPcodePos, t_integer nCatchPcodePos){ GETX->wr_PCode(c) ; GETX->wr_Integer(nModuleId) ; GETX->wr_Integer(pcodeCall) ; GETX->wr_Integer(nCatchType) ; GETX->wr_Integer(nPcodePos); GETX->wr_Integer(nCatchPcodePos) ; }
//  	void registerCatch(int nClassId, pcode *pcodeCall, int nCatchType, int nPcodePos, int nCatchPcodePos);

  
  void rd_memory_module_changeRegisterCallSub(const char *acFile, t_builtin *c, t_integer *p_old, t_integer *pcodeCall, t_integer *nPcodePos){ *c = GETX->rd_PCode(); *p_old = GETX->rd_Integer(); *pcodeCall = GETX->rd_Integer(); *nPcodePos = GETX->rd_Integer(); }
  void wr_memory_module_changeRegisterCallSub(const char *acFile, t_builtin c, pcode *p_old, pcode *pcodeCall, t_integer nPcodePos){   
    /*
    char ac[888];
    sprintf(ac, "change            old %d  pc %d   pos %d\n", p_old, pcodeCall, nPcodePos); 
    printf(ac);
*/
    GETX->wr_PCode(c) ; GETX->wr_Integer((t_integer) p_old) ; GETX->wr_Integer((t_integer) pcodeCall) ; GETX->wr_Integer(nPcodePos) ; 
  }
  void rd_memory_module_registerCallSub(const char *acFile, t_builtin *c, t_integer *nModuleId, t_integer *nId, t_integer *pcodeCall, t_integer *nPcodePos){ *c = GETX->rd_PCode(); *nModuleId = GETX->rd_Integer(); *nId = GETX->rd_Integer(); *pcodeCall = GETX->rd_Integer(); *nPcodePos = GETX->rd_Integer(); }
  void wr_memory_module_registerCallSub(const char *acFile, t_builtin c, t_integer nModuleId, t_integer nId, pcode *pcodeCall, t_integer nPcodePos){ 
    /*
    char ac[888];
    sprintf(ac, "22          %d:%d   pc %d   pos %d\n", nModuleId, nId, pcodeCall, nPcodePos); 
    printf(ac);
*/
    GETX->wr_PCode(c) ; GETX->wr_Integer(nModuleId) ; GETX->wr_Integer(nId) ; GETX->wr_Integer((t_integer) pcodeCall) ; GETX->wr_Integer(nPcodePos) ; 
  }


  void rd_memory_module_addVar_defaultkbasic(const char *acFile, t_builtin *c, t_integer *ID, t_integer *nModuleId, t_cstring *acName, t_integer *nType, t_array *a, t_integer *nScope, t_integer *nLStringLen){ 
    *c = GETX->rd_PCode(); *ID = GETX->rd_Integer(); *nModuleId = GETX->rd_Integer(); *acName = GETX->rd_CString(); *nType = GETX->rd_Integer(); GETX->rd_Array(a); *nScope = GETX->rd_Integer(); *nLStringLen = GETX->rd_Integer(); }
  
  void wr_memory_module_addVar_defaultkbasic(const char *acFile, t_builtin c, t_integer ID, t_integer nModuleId, t_cstring acName, t_integer nType, t_array *a, t_integer nScope, t_integer nLStringLen){ 
    if (defaultkbasic == 0) defaultkbasic = new pcode(acFile);
    defaultkbasic->wr_PCode(c) ; defaultkbasic->wr_Integer(ID) ; defaultkbasic->wr_Integer(nModuleId) ; defaultkbasic->wr_CString(acName) ; defaultkbasic->wr_Integer(nType) ; defaultkbasic->wr_Array(a); defaultkbasic->wr_Integer(nScope) ; defaultkbasic->wr_Integer(nLStringLen) ; }


  void rd_memory_module_addVar(const char *acFile, t_builtin *c, t_integer *ID, t_integer *nModuleId, t_cstring *acName, t_integer *nType, t_array *a, t_integer *nScope, t_integer *nLStringLen){ *c = GETX->rd_PCode(); *ID = GETX->rd_Integer(); *nModuleId = GETX->rd_Integer(); *acName = GETX->rd_CString(); *nType = GETX->rd_Integer(); GETX->rd_Array(a); *nScope = GETX->rd_Integer(); *nLStringLen = GETX->rd_Integer(); }
  void wr_memory_module_addVar(const char *acFile, t_builtin c, t_integer ID, t_integer nModuleId, t_cstring acName, t_integer nType, t_array *a, t_integer nScope, t_integer nLStringLen){ GETX->wr_PCode(c) ; GETX->wr_Integer(ID) ; GETX->wr_Integer(nModuleId) ; GETX->wr_CString(acName) ; GETX->wr_Integer(nType) ; GETX->wr_Array(a); GETX->wr_Integer(nScope) ; GETX->wr_Integer(nLStringLen) ; }

  void rd_memory_module_addSubVar(const char *acFile, t_builtin *c, t_integer *ID, t_integer *nModuleId, t_cstring *acSub, t_cstring *acName, t_integer *nType, t_array *a, t_boolean *bStatic, t_integer *nScope, t_integer *nLStringLen){ *c = GETX->rd_PCode(); *ID = GETX->rd_Integer(); *nModuleId = GETX->rd_Integer(); *acSub = GETX->rd_CString(); *acName = GETX->rd_CString(); *nType = GETX->rd_Integer(); GETX->rd_Array(a); *bStatic = GETX->rd_Boolean(); *nScope = GETX->rd_Integer(); *nLStringLen = GETX->rd_Integer();}
  void wr_memory_module_addSubVar(const char *acFile, t_builtin c, t_integer ID, t_integer nModuleId, t_cstring acSub, t_cstring acName, t_integer nType, t_array *a, t_boolean bStatic, t_integer nScope, t_integer nLStringLen){ GETX->wr_PCode(c) ; GETX->wr_Integer(ID) ; GETX->wr_Integer(nModuleId) ; GETX->wr_CString(acSub) ; GETX->wr_CString(acName) ; GETX->wr_Integer(nType) ; GETX->wr_Array(a); GETX->wr_Boolean(bStatic) ; GETX->wr_Integer(nScope) ;GETX->wr_Integer(nLStringLen) ; }

  void rd_memory_module_addConst(const char *acFile, t_builtin *c, t_integer *ID, t_integer *nModuleId, t_cstring *acName, t_integer *nScope){ *c = GETX->rd_PCode(); *ID = GETX->rd_Integer(); *nModuleId = GETX->rd_Integer(); *acName = GETX->rd_CString(); *nScope = GETX->rd_Integer(); }
  void wr_memory_module_addConst(const char *acFile, t_builtin c, t_integer ID, t_integer nModuleId, t_cstring acName, t_integer nScope){ GETX->wr_PCode(c) ; GETX->wr_Integer(ID) ; GETX->wr_Integer(nModuleId) ; GETX->wr_CString(acName) ; GETX->wr_Integer(nScope) ; }

  void rd_memory_module_addSubConst(const char *acFile, t_builtin *c, t_integer *ID, t_integer *nModuleId, t_cstring *acSub, t_cstring *acName){ *c = GETX->rd_PCode(); *ID = GETX->rd_Integer(); *nModuleId = GETX->rd_Integer(); *acSub = GETX->rd_CString(); *acName = GETX->rd_CString(); }
  void wr_memory_module_addSubConst(const char *acFile, t_builtin c, t_integer ID, t_integer nModuleId, t_cstring acSub, t_cstring acName){ GETX->wr_PCode(c) ; GETX->wr_Integer(ID) ; GETX->wr_Integer(nModuleId) ; GETX->wr_CString(acSub) ; GETX->wr_CString(acName) ; }



  void rd_memory_class_registerCatch(const char *acFile, t_builtin *c, t_integer *nClassId, t_integer *pcodeCall, t_integer *nCatchType, t_integer *nPcodePos, t_integer *nCatchPcodePos){ *c = GETX->rd_PCode(); *nClassId = GETX->rd_Integer(); *pcodeCall = GETX->rd_Integer(); *nCatchType = GETX->rd_Integer(); *nPcodePos = GETX->rd_Integer(); *nCatchPcodePos = GETX->rd_Integer(); }
  void wr_memory_class_registerCatch(const char *acFile, t_builtin c, t_integer nClassId, t_integer pcodeCall, t_integer nCatchType, t_integer nPcodePos, t_integer nCatchPcodePos){ GETX->wr_PCode(c) ; GETX->wr_Integer(nClassId) ; GETX->wr_Integer(pcodeCall) ; GETX->wr_Integer(nCatchType) ; GETX->wr_Integer(nPcodePos); GETX->wr_Integer(nCatchPcodePos) ; }


  void rd_memory_class_addClass(const char *acFile, t_builtin *c, t_integer *ID, t_cstring *acName, t_integer *p, t_integer *p2, t_cstring *acExtendName, t_boolean *bIsAbstract){ *c = GETX->rd_PCode(); *ID = GETX->rd_Integer(); *acName = GETX->rd_CString(); *p = GETX->rd_Integer(); *p2 = GETX->rd_Integer(); *acExtendName = GETX->rd_CString(); *bIsAbstract = GETX->rd_Integer(); }
  void wr_memory_class_addClass(const char *acFile, t_builtin c, t_integer ID, t_cstring acName, pcode *p, pcode *p2, t_cstring acExtendName, t_boolean bIsAbstract){ GETX->wr_PCode(c) ; GETX->wr_Integer(ID) ; GETX->wr_CString(acName) ; GETX->wr_Integer((t_integer) p) ; GETX->wr_Integer((t_integer) p2) ; GETX->wr_CString(acExtendName) ; GETX->wr_Integer(bIsAbstract) ; }

  void rd_memory_class_addClassMethod(const char *acFile, t_builtin *c, t_integer *ID,
			t_cstring *acClassName, 
			t_cstring *acRealName, 
			t_cstring *acName, 
			t_cstring *acSuffix, 
			t_cstring *acReturnType, 
			t_integer *nReturnSize, 
			t_integer *myPcode, 
			t_boolean *function, 
			t_boolean *constructor, 
			t_boolean *destructor, 
			t_boolean *signal, 
			t_boolean *slot, 
			t_integer *pc_pos, 
			t_integer *nScope, 
			t_integer *nTokenPos,
			t_integer *nTokenLinePos,
			t_boolean *bStatic,
			t_boolean *bAbstract,
      t_cstring *acFile2,
      t_integer *nLine,
      t_boolean *bDeclare,
      t_cstring *acAlias,
      t_cstring *acLib,
      t_cstring *acLibCallSignature      
      ){
         *c = GETX->rd_PCode(); *ID = GETX->rd_Integer(); 
         *acClassName = GETX->rd_CString(); 
         *acRealName = GETX->rd_CString(); 
         *acName = GETX->rd_CString(); 
         *acSuffix = GETX->rd_CString(); 
         *acReturnType = GETX->rd_CString(); 
         *nReturnSize = GETX->rd_Integer(); 
         *myPcode = GETX->rd_Integer(); 
         *function = GETX->rd_Boolean(); 
         *constructor = GETX->rd_Boolean(); 
         *destructor = GETX->rd_Boolean(); 
         *signal = GETX->rd_Boolean(); 
         *slot = GETX->rd_Boolean(); 
         *pc_pos = GETX->rd_Integer(); 
         *nScope = GETX->rd_Integer(); 
         *nTokenPos = GETX->rd_Integer(); 
         *nTokenLinePos = GETX->rd_Integer(); 
         *bStatic = GETX->rd_Boolean(); 
         *bAbstract = GETX->rd_Boolean(); 
         *acFile2 = GETX->rd_CString(); 
         *nLine = GETX->rd_Integer(); 
         *bDeclare = GETX->rd_Boolean(); 
         *acAlias = GETX->rd_CString(); 
         *acLib = GETX->rd_CString(); 
         *acLibCallSignature = GETX->rd_CString(); 
      }

  void wr_memory_class_addClassMethod(const char *acFile, t_builtin c, t_integer ID, 
			t_cstring acClassName, 
			t_cstring acRealName, 
			t_cstring acName, 
			t_cstring acSuffix, 
			t_cstring acReturnType, 
			t_integer nReturnSize, 
			pcode *myPcode, 
			t_boolean function, 
			t_boolean constructor, 
			t_boolean destructor, 
			t_boolean signal, 
			t_boolean slot, 
			t_integer pc_pos, 
			t_integer nScope, 
			t_integer nTokenPos,
			t_integer nTokenLinePos,
			t_boolean bStatic,
			t_boolean bAbstract,
      t_cstring acFile2,
      t_integer nLine,
      t_boolean bDeclare,
      t_cstring acAlias,
      t_cstring acLib,
      t_cstring acLibCallSignature      
    ){ 
      GETX->wr_PCode(c) ; GETX->wr_Integer(ID) ; 
      GETX->wr_CString(acClassName) ; 
      GETX->wr_CString(acRealName) ; 
      GETX->wr_CString(acName) ; 
      GETX->wr_CString(acSuffix) ; 
      GETX->wr_CString(acReturnType) ; 
      GETX->wr_Integer(nReturnSize) ; 
      GETX->wr_Integer((t_integer) myPcode) ; 
      GETX->wr_Boolean(function) ; 
      GETX->wr_Boolean(constructor) ; 
      GETX->wr_Boolean(destructor) ; 
      GETX->wr_Boolean(signal) ; 
      GETX->wr_Boolean(slot) ; 
      GETX->wr_Integer(pc_pos) ; 
      GETX->wr_Integer(nScope) ; 
      GETX->wr_Integer(nTokenPos) ; 
      GETX->wr_Integer(nTokenLinePos) ; 
      GETX->wr_Boolean(bStatic) ; 
      GETX->wr_Boolean(bAbstract) ; 
      GETX->wr_CString(acFile2) ; 
      GETX->wr_Integer(nLine) ; 
      GETX->wr_Boolean(bDeclare) ; 
      GETX->wr_CString(acAlias) ; 
      GETX->wr_CString(acLib) ; 
      GETX->wr_CString(acLibCallSignature) ; 
    }


  void rd_memory_class_addClassPropertyGet(const char *acFile, t_builtin *c, t_integer *ID,
			t_cstring *acClassName, 
			t_cstring *acName, 
			t_cstring *acSuffix, 
			t_cstring *acReturnType, 
			t_integer *nReturnSize, 
			t_integer *myPcode, 
			t_boolean *function, 
			t_integer *pc_pos, 
			t_integer *nScope, 
			t_integer *nTokenPos,
			t_integer *nTokenLinePos,
			t_boolean *bStatic,
			t_boolean *bAbstract,
      t_cstring *acFile2,
      t_integer *nLine
      ){
         *c = GETX->rd_PCode(); *ID = GETX->rd_Integer(); 
         *acClassName = GETX->rd_CString(); 
         *acName = GETX->rd_CString(); 
         *acSuffix = GETX->rd_CString(); 
         *acReturnType = GETX->rd_CString(); 
         *nReturnSize = GETX->rd_Integer(); 
         *myPcode = GETX->rd_Integer(); 
         *function = GETX->rd_Boolean(); 
         *pc_pos = GETX->rd_Integer(); 
         *nScope = GETX->rd_Integer(); 
         *nTokenPos = GETX->rd_Integer(); 
         *nTokenLinePos = GETX->rd_Integer(); 
         *bStatic = GETX->rd_Boolean(); 
         *bAbstract = GETX->rd_Boolean(); 
         *acFile2 = GETX->rd_CString(); 
         *nLine = GETX->rd_Integer(); 
      }

  void wr_memory_class_addClassPropertyGet(const char *acFile, t_builtin c, t_integer ID, 
			t_cstring acClassName, 
			t_cstring acName, 
			t_cstring acSuffix, 
			t_cstring acReturnType, 
			t_integer nReturnSize, 
			pcode *myPcode, 
			t_boolean function, 
			t_integer pc_pos, 
			t_integer nScope, 
			t_integer nTokenPos,
			t_integer nTokenLinePos,
			t_boolean bStatic,
			t_boolean bAbstract,
      t_cstring acFile2,
      t_integer nLine
    ){ 
      GETX->wr_PCode(c) ; GETX->wr_Integer(ID) ; 
      GETX->wr_CString(acClassName) ; 
      GETX->wr_CString(acName) ; 
      GETX->wr_CString(acSuffix) ; 
      GETX->wr_CString(acReturnType) ; 
      GETX->wr_Integer(nReturnSize) ; 
      GETX->wr_Integer((t_integer) myPcode) ; 
      GETX->wr_Boolean(function) ; 
      GETX->wr_Integer(pc_pos) ; 
      GETX->wr_Integer(nScope) ; 
      GETX->wr_Integer(nTokenPos) ; 
      GETX->wr_Integer(nTokenLinePos) ; 
      GETX->wr_Boolean(bStatic) ; 
      GETX->wr_Boolean(bAbstract) ; 
      GETX->wr_CString(acFile2) ; 
      GETX->wr_Integer(nLine) ; 
    }

  void rd_memory_class_addClassPropertySet(const char *acFile, t_builtin *c, t_integer *ID,
			t_cstring *acClassName, 
			t_cstring *acName, 
			t_cstring *acSuffix, 
			t_cstring *acReturnType, 
			t_integer *nReturnSize, 
			t_integer *myPcode, 
			t_boolean *function, 
			t_integer *pc_pos, 
			t_integer *nScope, 
			t_integer *nTokenPos,
			t_integer *nTokenLinePos,
			t_boolean *bStatic,
			t_boolean *bAbstract,
      t_cstring *acFile2,
      t_integer *nLine
      ){
         *c = GETX->rd_PCode(); *ID = GETX->rd_Integer(); 
         *acClassName = GETX->rd_CString(); 
         *acName = GETX->rd_CString(); 
         *acSuffix = GETX->rd_CString(); 
         *acReturnType = GETX->rd_CString(); 
         *nReturnSize = GETX->rd_Integer(); 
         *myPcode = GETX->rd_Integer(); 
         *function = GETX->rd_Boolean(); 
         *pc_pos = GETX->rd_Integer(); 
         *nScope = GETX->rd_Integer(); 
         *nTokenPos = GETX->rd_Integer(); 
         *nTokenLinePos = GETX->rd_Integer(); 
         *bStatic = GETX->rd_Boolean(); 
         *bAbstract = GETX->rd_Boolean(); 
         *acFile2 = GETX->rd_CString(); 
         *nLine = GETX->rd_Integer(); 
      }

  void wr_memory_class_addClassPropertySet(const char *acFile, t_builtin c, t_integer ID, 
			t_cstring acClassName, 
			t_cstring acName, 
			t_cstring acSuffix, 
			t_cstring acReturnType, 
			t_integer nReturnSize, 
			pcode *myPcode, 
			t_boolean function, 
			t_integer pc_pos, 
			t_integer nScope, 
			t_integer nTokenPos,
			t_integer nTokenLinePos,
			t_boolean bStatic,
			t_boolean bAbstract,
      t_cstring acFile2,
      t_integer nLine
    ){ 
      GETX->wr_PCode(c) ; GETX->wr_Integer(ID) ; 
      GETX->wr_CString(acClassName) ; 
      GETX->wr_CString(acName) ; 
      GETX->wr_CString(acSuffix) ; 
      GETX->wr_CString(acReturnType) ; 
      GETX->wr_Integer(nReturnSize) ; 
      GETX->wr_Integer((t_integer) myPcode) ; 
      GETX->wr_Boolean(function) ; 
      GETX->wr_Integer(pc_pos) ; 
      GETX->wr_Integer(nScope) ; 
      GETX->wr_Integer(nTokenPos) ; 
      GETX->wr_Integer(nTokenLinePos) ; 
      GETX->wr_Boolean(bStatic) ; 
      GETX->wr_Boolean(bAbstract) ; 
      GETX->wr_CString(acFile2) ; 
      GETX->wr_Integer(nLine) ; 
    }


  void rd_memory_class_bindingparam(const char *acFile, t_builtin *c, t_integer *classid, t_cstring *classmethodno, t_integer *no, t_integer *identifier){ *c = GETX->rd_PCode(); *classid = GETX->rd_Integer(); *classmethodno = GETX->rd_CString(); *no = GETX->rd_Integer(); *identifier = GETX->rd_Integer(); }
  void wr_memory_class_bindingparam(const char *acFile, t_builtin c, t_integer classid, t_cstring classmethodno, t_integer no, t_integer identifier){ GETX->wr_PCode(c) ; GETX->wr_Integer(classid) ; GETX->wr_CString(classmethodno) ; GETX->wr_Integer(no) ; GETX->wr_Integer(identifier) ; }


  void rd_memory_class_addThrowMethod(const char *acFile, t_builtin *c, t_integer *nClassId, t_integer *nId, t_cstring *acType){ *c = GETX->rd_PCode(); *nClassId = GETX->rd_Integer(); *nId = GETX->rd_Integer(); *acType = GETX->rd_CString(); }
  void wr_memory_class_addThrowMethod(const char *acFile, t_builtin c, t_integer nClassId, t_integer nId, t_cstring acType){ GETX->wr_PCode(c) ; GETX->wr_Integer(nClassId) ; GETX->wr_Integer(nId) ; GETX->wr_CString(acType) ; }

  void rd_memory_class_addParameterMethod(const char *acFile, t_builtin *c, t_integer *nClassId, t_integer *nId, t_cstring *acName, t_cstring *acType, t_integer *nParameterCall, t_boolean *bOptional, t_boolean *bDefault, t_boolean *bParamArray, t_array *a, defaultvalue *defval, t_integer *nParamId, t_integer *nParamLStringLen){ 
    *c = GETX->rd_PCode(); *nClassId = GETX->rd_Integer(); *nId = GETX->rd_Integer(); *acName = GETX->rd_CString(); *acType = GETX->rd_CString(); *nParameterCall = GETX->rd_Integer(); *bOptional = GETX->rd_Boolean(); *bDefault = GETX->rd_Boolean(); *bParamArray = GETX->rd_Boolean(); GETX->rd_Array(a); GETX->rd_Struct(sizeof(defaultvalue), defval); *nParamId = GETX->rd_Integer(); *nParamLStringLen = GETX->rd_Integer(); }
  void wr_memory_class_addParameterMethod(const char *acFile, t_builtin c, t_integer nClassId, t_integer nId, t_cstring acName, t_cstring acType, t_integer nParameterCall, t_boolean bOptional, t_boolean bDefault, t_boolean bParamArray, t_array *a, defaultvalue defval, t_integer nParamId, t_integer nParamLStringLen){ 
    GETX->wr_PCode(c) ; GETX->wr_Integer(nClassId) ; GETX->wr_Integer(nId) ; GETX->wr_CString(acName) ; GETX->wr_CString(acType) ; GETX->wr_Integer(nParameterCall) ; GETX->wr_Boolean(bOptional) ; GETX->wr_Boolean(bDefault) ; GETX->wr_Boolean(bParamArray) ; GETX->wr_Array(a) ; GETX->wr_Struct(sizeof(defaultvalue), &defval) ; GETX->wr_Integer(nParamId) ;GETX->wr_Integer(nParamLStringLen) ; }

  void rd_memory_class_addParameterPropertySet(const char *acFile, t_builtin *c, t_integer *nClassId, t_integer *nId, t_cstring *acName, t_cstring *acType, t_integer *nParameterCall, t_boolean *bOptional, t_boolean *bDefault, t_boolean *bParamArray, t_array *a, defaultvalue *defval, t_integer *nParamId, t_integer *nParamLStringLen){ 
    *c = GETX->rd_PCode(); *nClassId = GETX->rd_Integer(); *nId = GETX->rd_Integer(); *acName = GETX->rd_CString(); *acType = GETX->rd_CString(); *nParameterCall = GETX->rd_Integer(); *bOptional = GETX->rd_Boolean(); *bDefault = GETX->rd_Boolean(); *bParamArray = GETX->rd_Boolean(); GETX->rd_Array(a); GETX->rd_Struct(sizeof(defaultvalue), defval); *nParamId = GETX->rd_Integer(); *nParamLStringLen = GETX->rd_Integer(); }
  void wr_memory_class_addParameterPropertySet(const char *acFile, t_builtin c, t_integer nClassId, t_integer nId, t_cstring acName, t_cstring acType, t_integer nParameterCall, t_boolean bOptional, t_boolean bDefault, t_boolean bParamArray, t_array *a, defaultvalue defval, t_integer nParamId, t_integer nParamLStringLen){ 
    GETX->wr_PCode(c) ; GETX->wr_Integer(nClassId) ; GETX->wr_Integer(nId) ; GETX->wr_CString(acName) ; GETX->wr_CString(acType) ; GETX->wr_Integer(nParameterCall) ; GETX->wr_Boolean(bOptional) ; GETX->wr_Boolean(bDefault) ; GETX->wr_Boolean(bParamArray) ; GETX->wr_Array(a) ; GETX->wr_Struct(sizeof(defaultvalue), &defval) ; GETX->wr_Integer(nParamId) ;GETX->wr_Integer(nParamLStringLen) ; }


  void rd_memory_class_registerCallMethod(const char *acFile, t_builtin *c, t_integer *nClassId, t_integer *nId, t_integer *pcodeCall, t_integer *nPcodePos){ *c = GETX->rd_PCode(); *nClassId = GETX->rd_Integer(); *nId = GETX->rd_Integer(); *pcodeCall = GETX->rd_Integer(); *nPcodePos = GETX->rd_Integer(); }
  void wr_memory_class_registerCallMethod(const char *acFile, t_builtin c, t_integer nClassId, t_integer nId, pcode *pcodeCall, t_integer nPcodePos){ 
    if (nClassId == 100007){
      nClassId = nClassId;
    }
    GETX->wr_PCode(c) ; GETX->wr_Integer(nClassId) ; GETX->wr_Integer(nId) ; GETX->wr_Integer((t_integer) pcodeCall) ; GETX->wr_Integer(nPcodePos) ; }

  void rd_memory_class_registerCallPropertyGet(const char *acFile, t_builtin *c, t_integer *nClassId, t_integer *nId, t_integer *pcodeCall, t_integer *nPcodePos){ *c = GETX->rd_PCode(); *nClassId = GETX->rd_Integer(); *nId = GETX->rd_Integer(); *pcodeCall = GETX->rd_Integer(); *nPcodePos = GETX->rd_Integer(); }
  void wr_memory_class_registerCallPropertyGet(const char *acFile, t_builtin c, t_integer nClassId, t_integer nId, pcode *pcodeCall, t_integer nPcodePos){ GETX->wr_PCode(c) ; GETX->wr_Integer(nClassId) ; GETX->wr_Integer(nId) ; GETX->wr_Integer((t_integer) pcodeCall) ; GETX->wr_Integer(nPcodePos) ; }

  void rd_memory_class_registerCallPropertySet(const char *acFile, t_builtin *c, t_integer *nClassId, t_integer *nId, t_integer *pcodeCall, t_integer *nPcodePos){ *c = GETX->rd_PCode(); *nClassId = GETX->rd_Integer(); *nId = GETX->rd_Integer(); *pcodeCall = GETX->rd_Integer(); *nPcodePos = GETX->rd_Integer(); }
  void wr_memory_class_registerCallPropertySet(const char *acFile, t_builtin c, t_integer nClassId, t_integer nId, pcode *pcodeCall, t_integer nPcodePos){ GETX->wr_PCode(c) ; GETX->wr_Integer(nClassId) ; GETX->wr_Integer(nId) ; GETX->wr_Integer((t_integer) pcodeCall) ; GETX->wr_Integer(nPcodePos) ; }


  void rd_memory_class_addVar(const char *acFile, t_builtin *c, t_integer *ID, t_integer *nClassId, t_cstring *acName, t_integer *nType, t_array *a, t_boolean *bStatic, t_integer *nScope, t_integer *nLStringLen){ *c = GETX->rd_PCode(); *ID = GETX->rd_Integer(); *nClassId = GETX->rd_Integer(); *acName = GETX->rd_CString(); *nType = GETX->rd_Integer(); GETX->rd_Array(a); *bStatic = GETX->rd_Boolean(); *nScope = GETX->rd_Integer();*nLStringLen = GETX->rd_Integer(); }
  void wr_memory_class_addVar(const char *acFile, t_builtin c, t_integer ID, t_integer nClassId, t_cstring acName, t_integer nType, t_array *a, t_boolean bStatic, t_integer nScope, t_integer nLStringLen){ GETX->wr_PCode(c) ; GETX->wr_Integer(ID) ; GETX->wr_Integer(nClassId) ; GETX->wr_CString(acName) ; GETX->wr_Integer(nType) ; GETX->wr_Array(a); GETX->wr_Boolean(bStatic) ; GETX->wr_Integer(nScope) ; GETX->wr_Integer(nLStringLen) ; }

  void rd_memory_class_addStaticVar(const char *acFile, t_builtin *c, t_integer *ID, t_integer *nClassId, t_cstring *acName, t_integer *nType, t_array *a, t_boolean *bStatic, t_integer *nScope, t_integer *nLStringLen){ *c = GETX->rd_PCode(); *ID = GETX->rd_Integer(); *nClassId = GETX->rd_Integer(); *acName = GETX->rd_CString(); *nType = GETX->rd_Integer(); GETX->rd_Array(a); *bStatic = GETX->rd_Boolean(); *nScope = GETX->rd_Integer(); *nLStringLen = GETX->rd_Integer(); }
  void wr_memory_class_addStaticVar(const char *acFile, t_builtin c, t_integer ID, t_integer nClassId, t_cstring acName, t_integer nType, t_array *a, t_boolean bStatic, t_integer nScope, t_integer nLStringLen){ GETX->wr_PCode(c) ; GETX->wr_Integer(ID) ; GETX->wr_Integer(nClassId) ; GETX->wr_CString(acName) ; GETX->wr_Integer(nType) ; GETX->wr_Array(a); GETX->wr_Boolean(bStatic) ; GETX->wr_Integer(nScope) ; GETX->wr_Integer(nLStringLen) ; }

  void rd_memory_class_addConst(const char *acFile, t_builtin *c, t_integer *ID, t_integer *nClassId, t_cstring *acName, t_integer *nScope){ *c = GETX->rd_PCode(); *ID = GETX->rd_Integer(); *nClassId = GETX->rd_Integer(); *acName = GETX->rd_CString(); *nScope = GETX->rd_Integer(); }
  void wr_memory_class_addConst(const char *acFile, t_builtin c, t_integer ID, t_integer nClassId, t_cstring acName, t_integer nScope){ GETX->wr_PCode(c) ; GETX->wr_Integer(ID) ; GETX->wr_Integer(nClassId) ; GETX->wr_CString(acName) ; GETX->wr_Integer(nScope) ; }

  void rd_memory_class_addMethodVar(const char *acFile, t_builtin *c, t_integer *ID, t_integer *nClassId, t_cstring *acMethod, t_cstring *acName, t_integer *nType, t_array *a, t_boolean *bStatic, t_integer *nScope, t_integer *nLStringLen){ *c = GETX->rd_PCode(); *ID = GETX->rd_Integer(); *nClassId = GETX->rd_Integer(); *acMethod = GETX->rd_CString(); *acName = GETX->rd_CString(); *nType = GETX->rd_Integer(); GETX->rd_Array(a); *nScope = GETX->rd_Integer(); *nLStringLen = GETX->rd_Integer(); *bStatic = GETX->rd_Boolean(); }
  void wr_memory_class_addMethodVar(const char *acFile, t_builtin c, t_integer ID, t_integer nClassId, t_cstring acMethod, t_cstring acName, t_integer nType, t_array *a, t_boolean bStatic, t_integer nScope, t_integer nLStringLen){ GETX->wr_PCode(c) ; GETX->wr_Integer(ID) ; GETX->wr_Integer(nClassId) ; GETX->wr_CString(acMethod) ; GETX->wr_CString(acName) ; GETX->wr_Integer(nType) ; GETX->wr_Array(a); GETX->wr_Integer(nScope) ; GETX->wr_Integer(nLStringLen) ; GETX->wr_Boolean(bStatic) ; }

  void rd_memory_class_addPropertyGetVar(const char *acFile, t_builtin *c, t_integer *ID, t_integer *nClassId, t_cstring *acProperty, t_cstring *acName, t_integer *nType, t_array *a, t_boolean *bStatic, t_integer *nScope, t_integer *nLStringLen){ *c = GETX->rd_PCode(); *ID = GETX->rd_Integer(); *nClassId = GETX->rd_Integer(); *acProperty = GETX->rd_CString(); *acName = GETX->rd_CString(); *nType = GETX->rd_Integer(); GETX->rd_Array(a); *nScope = GETX->rd_Integer();  *nLStringLen = GETX->rd_Integer();  *bStatic = GETX->rd_Boolean(); }
  void wr_memory_class_addPropertyGetVar(const char *acFile, t_builtin c, t_integer ID, t_integer nClassId, t_cstring acProperty, t_cstring acName, t_integer nType, t_array *a, t_boolean bStatic, t_integer nScope, t_integer nLStringLen){ GETX->wr_PCode(c) ; GETX->wr_Integer(ID) ; GETX->wr_Integer(nClassId) ; GETX->wr_CString(acProperty) ; GETX->wr_CString(acName) ; GETX->wr_Integer(nType) ; GETX->wr_Array(a); GETX->wr_Integer(nScope) ; GETX->wr_Integer(nLStringLen) ; GETX->wr_Boolean(bStatic) ; }

  void rd_memory_class_addPropertySetVar(const char *acFile, t_builtin *c, t_integer *ID, t_integer *nClassId, t_cstring *acProperty, t_cstring *acName, t_integer *nType, t_array *a, t_boolean *bStatic, t_integer *nScope, t_integer *nLStringLen){ *c = GETX->rd_PCode(); *ID = GETX->rd_Integer(); *nClassId = GETX->rd_Integer(); *acProperty = GETX->rd_CString(); *acName = GETX->rd_CString(); *nType = GETX->rd_Integer(); GETX->rd_Array(a); *nScope = GETX->rd_Integer(); *nLStringLen = GETX->rd_Integer(); *bStatic = GETX->rd_Boolean(); }
  void wr_memory_class_addPropertySetVar(const char *acFile, t_builtin c, t_integer ID, t_integer nClassId, t_cstring acProperty, t_cstring acName, t_integer nType, t_array *a, t_boolean bStatic, t_integer nScope, t_integer nLStringLen){ GETX->wr_PCode(c) ; GETX->wr_Integer(ID) ; GETX->wr_Integer(nClassId) ; GETX->wr_CString(acProperty) ; GETX->wr_CString(acName) ; GETX->wr_Integer(nType) ; GETX->wr_Array(a); GETX->wr_Integer(nScope) ; GETX->wr_Integer(nLStringLen) ; GETX->wr_Boolean(bStatic) ; }

  void rd_memory_class_addMethodConst(const char *acFile, t_builtin *c, t_integer *ID, t_integer *nClassId, t_cstring *acMethod, t_cstring *acName){ *c = GETX->rd_PCode(); *ID = GETX->rd_Integer(); *nClassId = GETX->rd_Integer(); *acMethod = GETX->rd_CString(); *acName = GETX->rd_CString(); }
  void wr_memory_class_addMethodConst(const char *acFile, t_builtin c, t_integer ID, t_integer nClassId, t_cstring acMethod, t_cstring acName){ GETX->wr_PCode(c) ; GETX->wr_Integer(ID) ; GETX->wr_Integer(nClassId) ; GETX->wr_CString(acMethod) ; GETX->wr_CString(acName) ; }

  void rd_memory_class_addPropertySetConst(const char *acFile, t_builtin *c, t_integer *ID, t_integer *nClassId, t_cstring *acMethod, t_cstring *acName){ *c = GETX->rd_PCode(); *ID = GETX->rd_Integer(); *nClassId = GETX->rd_Integer(); *acMethod = GETX->rd_CString(); *acName = GETX->rd_CString(); }
  void wr_memory_class_addPropertySetConst(const char *acFile, t_builtin c, t_integer ID, t_integer nClassId, t_cstring acMethod, t_cstring acName){ GETX->wr_PCode(c) ; GETX->wr_Integer(ID) ; GETX->wr_Integer(nClassId) ; GETX->wr_CString(acMethod) ; GETX->wr_CString(acName) ; }

  void rd_memory_class_addPropertyGetConst(const char *acFile, t_builtin *c, t_integer *ID, t_integer *nClassId, t_cstring *acMethod, t_cstring *acName){ *c = GETX->rd_PCode(); *ID = GETX->rd_Integer(); *nClassId = GETX->rd_Integer(); *acMethod = GETX->rd_CString(); *acName = GETX->rd_CString(); }
  void wr_memory_class_addPropertyGetConst(const char *acFile, t_builtin c, t_integer ID, t_integer nClassId, t_cstring acMethod, t_cstring acName){ GETX->wr_PCode(c) ; GETX->wr_Integer(ID) ; GETX->wr_Integer(nClassId) ; GETX->wr_CString(acMethod) ; GETX->wr_CString(acName) ; }


  // ***

  //void initPcode();
  //void releasePcode();

  //bool bParserReading;

  pcode *myDeclaration2;
  pcode *myStatements2;

  pcode *defaultkbasic;

private:

#ifdef KBC
  XIntMap ff;
  XIntMap pcodeCache;
  XIntMap x;
  XIntMap xx;
  XIntMap xxx;

  int key; 
  int value;
#else
  pcode *ppp;
#endif
 
};

#endif

#endif