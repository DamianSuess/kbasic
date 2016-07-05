/*
***************************************************************************
Copyright (C) 2000-2008 KBasic Software (Bernd Noetscher, Boseweg 9, 60529 Frankfurt / Germany).  All rights reserved.

cache.cpp
---------------------------------------------------------------------------

***************************************************************************
*/



#include "cache.h"

#ifdef KBIDE
#else

#ifdef KBC
  #include "../kbc/token.h"
  #include "../kbc/parser.h"

  #include "../kbc/XFileInfo.h"
  #include "../kbc/XFile.h"


  memory_module *EXTERN_myModule;
  parser *EXTERN_myParser;

  extern char **MAIN_argv;
  extern XString cachePath(XString s);

  #define GETNEWPCODE getNewPcode(myPcode)
  #define GETNEWPCODEP getNewPcode(p)
  #define GETNEWPCODEP2 getNewPcode(p2)

#else

  #include "../kbrun/parser.h"
  #define GETNEWPCODE 0
  #define GETNEWPCODEP 0
  #define GETNEWPCODEP2 0

  extern QString cachePath(QString s);

#endif





cache::cache()
{
  defaultkbasic = 0;

#ifdef KBC
  //my_mainwindow = m;
//  bParserReading = false;

  myDeclaration2 = 0;
  myStatements2 = 0;

  setMode(false, false);
//  ac = "";

#endif

}

cache::~cache()
{
  if (defaultkbasic) delete defaultkbasic;
}

#ifdef KBC
bool cache::readScanner(const char *acFile, token *t, bool bInsert)
{
  //return false;
  if (acFile == 0) return false;
  XString s = acFile;
  if (s.endsWith("/default.kbasic")) return false;
  if (s.endsWith("\\default.kbasic")) return false;
  if (s.endsWith("/default2.kbasic")) return false;
  if (s.endsWith("\\default2.kbasic")) return false;

  XString m = "";
  m += changeFilenameWithoutPathSeparators(acFile);
  m += ".scanner";
  m = cachePath(m);
  
  XFileInfo k(m.ascii());

  if (k.exists()){
    XFileInfo d(acFile);

    int l = k.lastModified();
    int r = d.lastModified();
    if (l >= r){

  	

      XFile f(m.ascii());
      if (!f.open(ReadOnly)){
      } else {

        if (isParserValid(acFile)){


          // add no tokens; because the parser stuff will be added
          t->wr_CString(0, 0, 0, token__KB_FILENAME, (char *) acFile);

        } else {   
      
          static char acBuffer[10240];
          int i = 0;
          int i2 = 0;
          int nSize = f.size();
          int n = t->ba->getPos();
    
          while (i2 < nSize && (i = f.readBlock(acBuffer, 10240)) > 0){    
            if (bInsert){
              t->ba->insert(acBuffer, i);
            } else {
              t->ba->append(acBuffer, i);
            }
            i2 += i;
          }
          if (bInsert) t->ba->setPos(n);
          
        }
        f.close();

        return true;
      }
      
    }
  }

  return false;
}

void cache::writeScanner(const char *acFile, token *t, int nTokenFromPos)
{
  

  if (acFile == 0) return;
  XString s = acFile;
  if (s.endsWith("/default.kbasic")) return;
  if (s.endsWith("\\default.kbasic")) return;
  if (s.endsWith("/default2.kbasic")) return;
  if (s.endsWith("\\default2.kbasic")) return;

  //*if (strcmp(acFile, "Inserted by KBasic Atelier automatically") == 0) return;

  

  XString m = "";
  m += changeFilenameWithoutPathSeparators(acFile);
  m += ".scanner";
  m = cachePath(m);
/*
  printf("11111111");
  printf(m.ascii());
  printf("22222222");
*/
  XFile f(m.ascii());
  if (!f.open(WriteOnly)){
    
  } else {
    int n = t->ba->getSize() - nTokenFromPos;
//printf("222222");
    f.writeBlock (t->ba->getMem() + nTokenFromPos, n);
    f.close();
  }

}
/*
void cache::parserSetFile(const char *acFile)
{
  ac = acFile;
}
*/
void cache::wr_parserOpen(parser *myParser, const char *acFile)
{
  XString m;
  if (acFile == 0) return;// goto re;
  XString s = acFile;
  if (s.endsWith("/default.kbasic")) return;
  if (s.endsWith("\\default.kbasic")) return;
  if (s.endsWith("/default2.kbasic")) return;
  if (s.endsWith("\\default2.kbasic")) return;

  //*if (strcmp(acFile, "Inserted by KBasic Atelier automatically") == 0) return;// goto re;

  m = "";
  m += changeFilenameWithoutPathSeparators(acFile);
  m += ".parser.";
  m += acMode;
  m = cachePath(m);

/*
  if ((XFile *)(ff.getString(acFile)).isOpen()){
    wr_parserClose();
  }
*/
  if (!ff.contains(acFile)){
    ff.addString(acFile, (int) new XFile());
    x.addString(acFile, (int) new pcode(acFile));
    xx.addString(acFile, (int) new pcode(acFile));
    xxx.addString(acFile, (int) new pcode(acFile));

    ((pcode *)(x.getString(acFile)))->resetPos();
    ((pcode *)(xx.getString(acFile)))->resetPos();
    ((pcode *)(xxx.getString(acFile)))->resetPos();
  }
  ((XFile *)(ff.getString(acFile)))->setName(m.ascii());
  if (strcmp(myParser->acDefaultModuleName, acFile) != 0){
    if (!((XFile *)(ff.getString(acFile)))->open(WriteOnly)){
    
    } else {
      wr_version(acFile, version, compiler__KBASIC_VERSION);
    }
  }
  //return;
//re:
  //wr_parserClose();
}

// save parser information in file
void cache::wr_parserCloseAll(bool bSave)
{  


  //QMap<XString, XFile*>::Iterator it2;
  //for ( it2 = ff.begin(); it2 != ff.end(); ++it2 ) {
  XString m = cachePath("runtime.parser");
  XFile f(m.ascii());
  if (bSave && !f.open(Append)){
    //  error
    return;
  } else if (bSave){
    f.atEnd();
  }

  XString ss = "";  
  bool b = true;

  if (ff.first(&key, &value)){
    do {

      XFile *m = (XFile *) value;

      if (m->isOpen()){

        XString s = m->name();
        /*
        if (s.contains("_cache_default.kbasic.parser.")){
          ss = s;
        }
        if (s.contains("_cache_default2.kbasic.parser.")){
          ss = s;
        }*/


        pcode *ttt = (pcode *) xxx.get(key);
        pcode *tt = (pcode *) xx.get(key);
        pcode *t = (pcode *) x.get(key);

        ttt->pcodeWritePcode(tt); 

        if (b){
          b = false;
          wr_memory_variable_setIdCounter(ttt, memory_variable_setIdCounter, memory_variable::nIdCounter);
        }


        // first xxx, 2nd xx, then x must be placed in file,
        // xxx are dependencies
        // xx are pcode blocks only, x are registerXYZ commands 
        // and pcode blocks must be first executed before registerXYZ
        ttt->pcodeWritePcode(t); 

        int n = ttt->ba->getSize();

        // save pcode commands in file
        if (bSave){
          m->writeBlock (ttt->ba->getMem(), n);
          f.writeBlock (t->ba->getMem(), t->ba->getSize());
        }

        m->close();
      }

      delete m;

    } while (ff.next(&key, &value));
  }

  // add defaultkbasic parser information for runtime
  if (bSave) f.writeBlock (defaultkbasic->ba->getMem(), defaultkbasic->ba->getSize());  

  if (bSave) f.close();

  ff.clear();

  if (x.first(&key, &value)){
    do {
      pcode *m = (pcode *) value;
      delete m;
    } while (x.next(&key, &value));
  }    
  x.clear();

  if (xx.first(&key, &value)){
    do {
      pcode *m = (pcode *) value;
      delete m;
    } while (xx.next(&key, &value));
  }    
  xx.clear();

  if (xxx.first(&key, &value)){
    do {
      pcode *m = (pcode *) value;
      delete m;
    } while (xxx.next(&key, &value));
  }    
  xxx.clear();

  delete myDeclaration2; myDeclaration2 = 0;
  delete myStatements2; myStatements2 = 0;
/*
  // delete default.kbasic cache, must be deleted later, because we need parser information in runtime.parser
  if (!ss.isEmpty()){
    XFile k(ss.ascii());    
    if (k.open(Truncate | WriteOnly)){
     // k.close();
    }
    bool b = k.del();
  }    
*/
}

bool cache::isParserValid(const char *acFile)
{
  //return false;
  if (acFile == 0) return false;
  XString s = acFile;
  if (s.endsWith("/default.kbasic")) return false;
  if (s.endsWith("\\default.kbasic")) return false;
  if (s.endsWith("/default2.kbasic")) return false;
  if (s.endsWith("\\default2.kbasic")) return false;

  //*if (strcmp(acFile, "Inserted by KBasic Atelier automatically") == 0) return false;

  XString m = "";
  m += changeFilenameWithoutPathSeparators(acFile);
  m += ".parser.";
  m += acMode;
  m = cachePath(m);

  XFileInfo k(m.ascii());

  if (k.exists()){
    XFileInfo d(acFile);

    int l = k.lastModified();
    int r = d.lastModified();

    if (l >= r){
      
      XFile f(m.ascii());
      if (!f.open(ReadOnly)){
        
      } else {

        if (f.size() == 0){
          f.close();
          return false;
        }
      }

      { // copy data
        XString m = cachePath("runtime.parser");
        XFile k(m.ascii());
        if (!k.open(Append)){
          //  error
          //return;
        } else {
          k.atEnd();
          int i = 0;
          char acBuffer[10240];
          do {
            i = f.readBlock(acBuffer, 10240);
            if (i > 0) k.writeBlock(acBuffer, i);
          } while (i > 0);
     
          k.close();
        }
      }

      f.close();

      return true;
    }
  }
  return false;
}


// read cached parser pcodes and add it to global myDeclaration2 and myStatements2 or normal pcode block of subs
bool cache::readParserPhase0(const char *acFile, parser *p, bool bFirst, bool *bDependencyFailed, bool *bVersionFailed)
{
  //return false;
  if (acFile == 0) return false;
  XString s = acFile;
  if (s.endsWith("/default.kbasic")) return false;
  if (s.endsWith("\\default.kbasic")) return false;
  if (s.endsWith("/default2.kbasic")) return false;
  if (s.endsWith("\\default2.kbasic")) return false;
  //*if (strcmp(acFile, "Inserted by KBasic Atelier automatically") == 0) return false;

  XString m = "";
  m += changeFilenameWithoutPathSeparators(acFile);
  m += ".parser.";
  m += acMode;
  m = cachePath(m);

  XFileInfo k(m.ascii());

  if (bFirst){
    if (myDeclaration2) myDeclaration2->resetPos();
    if (myStatements2) myStatements2->resetPos();
  }

  if (k.exists()){
    XFileInfo d(acFile);

    int l = k.lastModified();
    int r = d.lastModified();
    if (l >= r){

      XFile f(m.ascii());
      if (!f.open(ReadOnly)){
        
      } else {

        if (f.size() == 0){
          f.close();
          return false;
        }

//        parserSetFile(acFile);

        if (!x.contains(acFile)){
          x.addString(acFile, (int) new pcode(acFile));
          xx.addString(acFile, (int) new pcode(acFile));
          xxx.addString(acFile, (int) new pcode(acFile));
        }

        ((pcode *) x.getString(acFile))->resetPos();
        ((pcode *) xx.getString(acFile))->resetPos();
        ((pcode *) xxx.getString(acFile))->resetPos();
        
        static char acBuffer[10240];
        int i = 0;
        int i2 = 0;
        int nSize = f.size();
        while (i2 < nSize && (i = f.readBlock(acBuffer, 10240)) > 0){    
          ((pcode *) x.getString(acFile))->ba->wr_Struct(i, acBuffer);
          i2 += i;
        }        
        
        bool b = doParser(p, acFile, 0, bDependencyFailed, bVersionFailed);

        f.close();

        if (b == false){
          delete ((pcode *) x.getString(acFile)); x.removeString(acFile);
          delete ((pcode *) xx.getString(acFile)); xx.removeString(acFile);
          delete ((pcode *) xxx.getString(acFile)); xxx.removeString(acFile);
          if (bDependencyFailed && *bDependencyFailed) deleteParser(acFile);
        }
/*
        delete x[acFile];
        x.clear();

        delete xx[acFile];
        xx.clear();

        //bParserReading = false;
*/
        
        return b;
      }
      
    }
  }
  return false;
}

bool cache::readParserPhase1(const char *acFile, parser *p, bool bFirst)
{
  //return false;
  if (acFile == 0) return false;
  XString s = acFile;
  if (s.endsWith("/default.kbasic")) return false;
  if (s.endsWith("\\default.kbasic")) return false;
  if (s.endsWith("/default2.kbasic")) return false;
  if (s.endsWith("\\default2.kbasic")) return false;
  //*if (strcmp(acFile, "Inserted by KBasic Atelier automatically") == 0) return false;

  XString m = "";
  m += changeFilenameWithoutPathSeparators(acFile);
  m += ".parser.";
  m += acMode;
  m = cachePath(m);

  XFileInfo k(m.ascii());

  if (k.exists()){
    XFileInfo d(acFile);

    int l = k.lastModified();
    int r = d.lastModified();
    if (l >= r){

      XFile f(m.ascii());
      if (!f.open(ReadOnly)){
        
      } else {

        if (f.size() == 0){
          f.close();
          return false;
        }

//        parserSetFile(acFile);
/*
        if (!x.contains(acFile)){
          x[acFile] = new pcode(acFile);
          xx[acFile] = new pcode(acFile);
        }

        x[acFile]->resetPos();
        xx[acFile]->resetPos();
        
        if (bFirst){
          if (myDeclaration2) myDeclaration2->resetPos();
          if (myStatements2) myStatements2->resetPos();
        }

        static char acBuffer[10240];
        int i = 0;
        int i2 = 0;
        int nSize = f.size();
        while (i2 < nSize && (i = f.readBlock(acBuffer, 10240)) > 0){    
          x[acFile]->ba->wr_Struct(i, acBuffer);
          i2 += i;
        }     */   
        
        bool b = doParser(p, acFile, 1);

        //delete x[acFile];

        //delete xx[acFile];

        //bParserReading = false;

        f.close();
        return b;
      }
      
    }
  }
  return false;
}

void cache::deleteParser(const char *acFile)
{
  //return false;
  if (acFile == 0) return;
  XString s = acFile;
  if (s.endsWith("/default.kbasic")) return;
  if (s.endsWith("\\default.kbasic")) return;
  if (s.endsWith("/default2.kbasic")) return;
  if (s.endsWith("\\default2.kbasic")) return;
  //*if (strcmp(acFile, "Inserted by KBasic Atelier automatically") == 0) return;

  XString m = "";
  m += changeFilenameWithoutPathSeparators(acFile);
  m += ".parser.";
  m += acMode;
  m = cachePath(m);

  XFile k(m.ascii());
  if (k.open(Truncate | WriteOnly)){
    //k.close();
  }
  bool b = k.del();
  b = b;

}
/*
// prepend pcode stuff before parser stuff  -  pp is used as buffer
void cache::initPcode()
{
//  pp.resetPos();
//  pp.pcodeWritePcode(this);
//  this->resetPos();
}

// append parser stuff
void cache::releasePcode()
{
 // wr_CString("22222222222222222222222222");
   pp.pcodeWritePcode(this); 
//  pp.resetPos();
}*/


void cache::initParser()
{
  acLastFile = "";
  acLastFile2 = "";
  acLastFile3 = "";
  pcodeCache.clear();
}

void cache::deinitParser()
{
  pcodeCache.clear();
}
/*
bool cache::checkDependencyFor(const char *acFile)
{
  return false;
}
*/

pcode *cache::getNewPcode(int _pcode)
{
  return ((pcode *) pcodeCache.get(_pcode));
}
#endif

bool cache::doParser(parser *myParser, const char *acFile, int nPhase, bool *bDependencyFailed, bool *bVersionFailed)
{
#ifdef KBC
  int nLen = ((pcode *)x.getString(acFile))->getPos();

  if (bDependencyFailed) *bDependencyFailed = false;
  if (bVersionFailed) *bVersionFailed = false;

  ((pcode *)x.getString(acFile))->resetPos();
  ((pcode *)xx.getString(acFile))->resetPos();
  ((pcode *)xxx.getString(acFile))->resetPos();
  /*
  if (nPhase == 0) pcodeCache.clear();
  int nn = pcodeCache.count();*/

#else
  ppp = new pcode("");

  QFile f(cachePath("runtime.parser"));
  if (!f.open(QFile::ReadOnly)){
    
  } else {
            
    static char acBuffer[10240];
    int i = 0;
    int i2 = 0;
    int nSize = f.size();
    while (i2 < nSize && (i = f.read(acBuffer, 10240)) > 0){    
      ppp->ba->append(acBuffer, i);
      i2 += i;
    }
    
    
  }
  f.close();
     
  int nLen = ppp->getPos();
  ppp->resetPos();

  myParser->myModule->addModule("Global", 0, 0, "");


#endif

/*
  XString sFile = acFile;
  if (sFile.contains("myMenuBar.kbasic_menubar")){
    sFile = sFile;
  }
*/
  int nTest = 0;

  if (nLen) 
	do {

#ifdef KBC
		nTest = ((pcode *)x.getString(acFile))->peekInteger();
#else
		nTest = ppp->peekInteger();
#endif

    switch(nTest){
  
      case version:
        {
          static t_builtin c; static t_double version;

          rd_version(acFile, &c, &version);

//#ifdef KBC    
          if (version != compiler__KBASIC_VERSION){
            if (bVersionFailed) *bVersionFailed = true;
            if (bDependencyFailed) *bDependencyFailed = true; // if version is different, prevent using scanner cache

            return false;          
          }
//#endif

        }
        break;

      case dependency:
        {
          static t_builtin c; static t_cstring acDependency;

          rd_dependency(acFile, &c, &acDependency);
  
#ifdef KBC    
          if (isParserValid(acDependency) == false){
            if (bDependencyFailed) *bDependencyFailed = true;
            return false;          
          }
#endif

          //if (nPhase == 0) myParser->myMemory_type->addElement(nId, acElementName, acElementType, nElementSize, &a, nElementId);         

        }
        break;

      case dependency_globalvar:
        {
          static t_builtin c; static t_integer nId;

          rd_dependency_globalvar(acFile, &c, &nId);
  
#ifdef KBC    
          if (EXTERN_myModule->existVar(EXTERN_myModule->getId(EXTERN_myParser->acDefaultModuleName), nId) == false){
            if (bDependencyFailed) *bDependencyFailed = true;
            return false;          
          }
#endif

        }
        break;

      case pcodeBlock:
        {          
          static t_builtin c; static t_integer p; static t_integer len; static void *pcodeNew; static t_pcodeCache t;

          rd_pcodeBlock(acFile, &c, &p, &len, &pcodeNew, &t);

#ifdef KBC    
          if (nPhase == 0){

            if (t == declaration2){
              if (myDeclaration2 == 0){
                myDeclaration2 = new pcode("");
                //myDeclaration2->wr_PUSH_STRING(pcode__PUSH_STRING, 1);
              }
              pcodeCache.add(p, (int) myDeclaration2);
            } else if (t == statements2){
              if (myStatements2 == 0){
                myStatements2 = new pcode("");
                //myStatements2->wr_PUSH_STRING(pcode__PUSH_STRING, 19);
              }
              pcodeCache.add(p, (int) myStatements2);
            } else {
              pcodeCache.add(p, (int) new pcode(""));
            }
                      /*
            char ac[888];
            sprintf(ac, "%d\n", p); 
            printf(ac);
*/
            if (len){
              ((pcode *)pcodeCache.get(p))->wr_Struct(len, pcodeNew);
            }
          }
#endif
        }
        break;

      case memory_variable_setIdCounter:
        {
          static t_builtin c; static t_integer n;

#ifdef KBC
		rd_memory_variable_setIdCounter(((pcode *)x.getString(acFile)), &c, &n);
#else
		rd_memory_variable_setIdCounter(ppp, &c, &n);nTest = ppp->peekInteger();
#endif

          if (nPhase == 0) memory_variable::setIdCounter(n);

        }
        break;

      case memory_type_addType:
        {
          static t_builtin c; static t_integer ID; static t_cstring acModule; static t_cstring acName; static t_integer nScope; static t_integer nId;

          rd_memory_type_addType(acFile, &c, &ID, &acModule, &acName, &nScope, &nId);

          if (nPhase == 0) myParser->myMemory_type->addType(acModule, acName, nScope, nId);

        }
        break;

      case memory_type_addElement:
        {
          static t_builtin c; static t_integer ID; static t_integer nId; static t_cstring acElementName; static t_cstring acElementType; static t_integer nElementSize; static t_array a; static t_integer nElementId;

          rd_memory_type_addElement(acFile, &c, &ID, &nId, &acElementName, &acElementType, &nElementSize, &a, &nElementId);

          if (nPhase == 0) myParser->myMemory_type->addElement(nId, acElementName, acElementType, nElementSize, &a, nElementId);         

        }
        break;

      case memory_enum_addEnum:
        {
          static t_builtin c; static t_integer ID; static t_cstring acModule; static t_cstring acName; static t_integer nScope; static t_integer nId;

          rd_memory_enum_addEnum(acFile, &c, &ID, &acModule, &acName, &nScope, &nId);

          if (nPhase == 0) myParser->myMemory_enum->addEnum(acModule, acName, nScope, nId);

        }
        break;

      case memory_enum_addElement:
        {
          static t_builtin c; static t_integer ID; static t_integer nId; static t_cstring acElementName; static t_cstring acElementType; static t_integer nElementSize; static t_integer nElementId;

          rd_memory_enum_addElement(acFile, &c, &ID, &nId, &acElementName, &acElementType, &nElementSize, &nElementId);

          if (nPhase == 0) myParser->myMemory_enum->addElement(nId, acElementName, acElementType, nElementSize, 0, nElementId);         

        }
        break;

      case memory_stringliteral_declare:
        {
          static t_builtin c; static t_integer ID; static t_cstring acName; static t_integer nId;

          rd_memory_stringliteral_declare(acFile, &c, &ID, &acName, &nId);

          if (nPhase == 0) myParser->myMemory_stringliteral->declare(acName, nId);         

        }
        break;

      case memory_module_addModule:
        {
          static t_builtin c; static t_integer ID; static t_cstring acName; static t_integer p; static t_integer pc_pos;

          rd_memory_module_addModule(acFile, &c, &ID, &acName, &p, &pc_pos);

          if (nPhase == 0) myParser->myModule->addModule(acName, GETNEWPCODEP, pc_pos, acFile, ID);

        }
        break;    

      case memory_module_addModuleSub:
        {
          static t_builtin c; t_integer ID; 
			    static t_cstring acModuleName; 
			    static t_cstring acRealName; 
			    static t_cstring acName; 
			    static t_cstring acSuffix; 
			    static t_cstring acReturnType; 
			    static t_integer nReturnSize; 
			    static t_integer myPcode; 
			    static t_boolean function; 
			    static t_integer pc_pos; 
			    static t_integer nScope; 
			    static t_integer nTokenPos;
			    static t_integer nTokenLinePos;
			    static t_boolean bStatic;
			    static t_boolean bAbstract;
          static t_cstring acFile2;
          static t_integer nLine;
          static t_boolean bDeclare;
          static t_cstring acAlias;
          static t_cstring acLib;
          static t_cstring acLibCallSignature;   



          rd_memory_module_addModuleSub(acFile, &c, &ID, 
			      &acModuleName, 
			      &acRealName, 
			      &acName, 
			      &acSuffix, 
			      &acReturnType, 
			      &nReturnSize, 
			      &myPcode, 
			      &function, 
			      &pc_pos, 
			      &nScope, 
			      &nTokenPos,
			      &nTokenLinePos,
			      &bStatic,
			      &bAbstract,
            &acFile2,
            &nLine,
            &bDeclare,
            &acAlias,
            &acLib,
            &acLibCallSignature      
         );

          if (nPhase == 0) myParser->myModule->addModuleSub(
            	acModuleName, 
			        acRealName, 
			        acName, 
			        acSuffix, 
			        acReturnType, 
			        nReturnSize, 
			        GETNEWPCODE, 
			        function, 
			        pc_pos, 
			        nScope, 
			        nTokenPos,
			        nTokenLinePos,
			        bStatic,
			        bAbstract,
              acFile2,
              nLine,
              bDeclare,
              acAlias,
              acLib,
              acLibCallSignature                
              , ID);

        }
        break;   
  
      case memory_module_addThrowSub:
        {
          static t_builtin c; static t_integer nModuleId; static t_integer nId; static t_cstring acType;

          rd_memory_module_addThrowSub(acFile, &c, &nModuleId, &nId, &acType);

          if (nPhase == 0) myParser->myModule->addThrowSub(nModuleId, nId, acType);

        }
        break;        

      case memory_module_addParameterSub:
        {
          static t_builtin c; static t_integer nModuleId; static t_integer nId; static t_cstring acName; static t_cstring acType; static t_integer nParameterCall; static t_boolean bOptional; static t_boolean bDefault; static t_boolean bParamArray; static t_array a; static defaultvalue defval; static t_integer nParamId; static t_integer nParamLStringLen;

          rd_memory_module_addParameterSub(acFile, &c, &nModuleId, &nId, &acName, &acType, &nParameterCall, &bOptional, &bDefault, &bParamArray, &a, &defval, &nParamId, &nParamLStringLen);

#ifdef KBC
          if (nPhase == 0) myParser->myModule->addParameterSub(nModuleId, nId, acName, acType, nParameterCall, bOptional, bDefault, bParamArray, &a, &defval, &nParamId, &nParamLStringLen);
#else
          if (nPhase == 0) myParser->myModule->addParameterSub(nModuleId, nId, acName, acType, nParameterCall, bOptional, bDefault, bParamArray, &a, &defval, &nParamId);
#endif

        }
        break;       

      case memory_module_registerCatch:
        {

          static t_builtin c; static t_integer nModuleId; static t_integer pcodeCall; static t_integer nCatchType; static t_integer nPcodePos; static t_integer nCatchPcodePos;

          rd_memory_module_registerCatch(acFile, &c, &nModuleId, &pcodeCall, &nCatchType, &nPcodePos, &nCatchPcodePos);

#ifdef KBC
          if (nPhase == 1) myParser->myModule->registerCatch(nModuleId, getNewPcode(pcodeCall), nCatchType, nPcodePos, nCatchPcodePos);
#endif

        }
        break;       

      case memory_module_registerCallSub:
        {
          static t_builtin c; static t_integer nModuleId; static t_integer nId; static t_integer pcodeCall; static t_integer nPcodePos;

          rd_memory_module_registerCallSub(acFile, &c, &nModuleId, &nId, &pcodeCall, &nPcodePos);

 /*
          char ac[888];
          sprintf(ac, "rc          %d\n", pcodeCall); 
          printf(ac);
*/
#ifdef KBC
          pcode *pp = getNewPcode(pcodeCall);
          if (nPhase == 1) myParser->myModule->registerCallSub(nModuleId, nId, pp == 0 ? (pcode *) pcodeCall : pp, nPcodePos, 0);
#endif

        }
        break;       

      case memory_module_changeRegisterCallSub:
        {
          static t_builtin c; static t_integer p_old; static t_integer pcodeCall; static t_integer nPcodePos;

          rd_memory_module_changeRegisterCallSub(acFile, &c, &p_old, &pcodeCall, &nPcodePos);

 /*
          char ac[888];
          sprintf(ac, "old %d  %d\n", p_old, pcodeCall); 
          printf(ac);
          */
#ifdef KBC
          if (nPhase == 1) myParser->myModule->changeRegisterCallSub((pcode *) p_old, getNewPcode(pcodeCall), nPcodePos);
#endif

        }
        break;   

      case memory_module_addVar_defaultkbasic:
        {
          static t_builtin c; static t_integer ID; static t_integer nModuleId; static t_cstring acName; static t_integer nType; static t_array a; static t_integer nScope; static t_integer nLStringLen;

          rd_memory_module_addVar_defaultkbasic(acFile, &c, &ID, &nModuleId, &acName, &nType, &a, &nScope, &nLStringLen);
#ifdef RUN
          if (nPhase == 0) myParser->myModule->addVar(nModuleId, acName, nType, &a, nScope, nLStringLen, ID);
#endif
        }
        break;      

      case memory_module_addVar:
        {
          static t_builtin c; static t_integer ID; static t_integer nModuleId; static t_cstring acName; static t_integer nType; static t_array a; static t_integer nScope; static t_integer nLStringLen;

          rd_memory_module_addVar(acFile, &c, &ID, &nModuleId, &acName, &nType, &a, &nScope, &nLStringLen);

          if (nPhase == 0) myParser->myModule->addVar(nModuleId, acName, nType, &a, nScope, nLStringLen, ID);

        }
        break;      

      case memory_module_addConst:
        {
          static t_builtin c; static t_integer ID; static t_integer nModuleId; static t_cstring acName; static t_integer nScope;

          rd_memory_module_addConst(acFile, &c, &ID, &nModuleId, &acName, &nScope);

          if (nPhase == 0) myParser->myModule->addConst(nModuleId, acName, nScope, ID);

        }
        break;      

      case memory_module_addSubVar:
        {
          static t_builtin c; static t_integer ID; static t_integer nModuleId; static t_cstring acSub; static t_cstring acName; static t_integer nType; static t_array a; static t_boolean bStatic; static t_integer nScope; static t_integer nLStringLen;

          rd_memory_module_addSubVar(acFile, &c, &ID, &nModuleId, &acSub, &acName, &nType, &a, &bStatic, &nScope, &nLStringLen);

          if (nPhase == 0) myParser->myModule->addSubVar(nModuleId, acSub, acName, nType, &a, bStatic, nScope, nLStringLen, ID);

        }
        break;      

      case memory_module_addSubConst:
        {
          static t_builtin c; static t_integer ID; static t_integer nModuleId; static t_cstring acSub; static t_cstring acName;

          rd_memory_module_addSubConst(acFile, &c, &ID, &nModuleId, &acSub, &acName);

          if (nPhase == 0) myParser->myModule->addSubConst(nModuleId, acSub, acName, ID);

        }
        break;      

      case memory_class_addClass:
        {
          static t_builtin c; static t_integer ID; static t_cstring acName; static t_integer p; static t_integer p2; static t_cstring acExtendName; static t_boolean bIsAbstract;

          rd_memory_class_addClass(acFile, &c, &ID, &acName, &p, &p2, &acExtendName, &bIsAbstract);

          if (nPhase == 0){
            myParser->myClass->addClass(acName, GETNEWPCODEP, GETNEWPCODEP2, acExtendName, acFile, bIsAbstract, ID);
#ifdef KBC
            int nParentId = myParser->myClass->getId(acExtendName); // user defined parent class
            if (nParentId == 0) nParentId = (int) binding_map_class.getString(acExtendName); // qt binding class

            // alle klassen werden am ende der registrierung nochmal durchgegangen um nParentId zu setzen, notwendig wenn reihenfolge der classendef. vertauscht ist
            myParser->myClass->setParentId(ID, nParentId);

            // alle sub classes aktualisieren auf neue parent id
            if (myParser->myClass->first()){
              do {
                int nClassId = myParser->myClass->getId();

                if (utility::my_stricmp(myParser->myClass->getParentName(nClassId), acName) == 0){
                    myParser->myClass->setParentId(nClassId, ID);
                }
              } while (myParser->myClass->next());
            }
#endif

          }

        }
        break;     

      case memory_class_addClassMethod:
        {
          static t_builtin c; t_integer ID; 
			    static t_cstring acClassName; 
			    static t_cstring acRealName; 
			    static t_cstring acName; 
			    static t_cstring acSuffix; 
			    static t_cstring acReturnType; 
			    static t_integer nReturnSize; 
			    static t_integer myPcode; 
			    static t_boolean function; 
			    static t_boolean constructor; 
			    static t_boolean destructor; 
			    static t_boolean signal; 
			    static t_boolean slot; 
			    static t_integer pc_pos; 
			    static t_integer nScope; 
			    static t_integer nTokenPos;
			    static t_integer nTokenLinePos;
			    static t_boolean bStatic;
			    static t_boolean bAbstract;
          static t_cstring acFile2;
          static t_integer nLine;
          static t_boolean bDeclare;
          static t_cstring acAlias;
          static t_cstring acLib;
          static t_cstring acLibCallSignature;   

          rd_memory_class_addClassMethod(acFile, &c, &ID, 
			      &acClassName, 
			      &acRealName, 
			      &acName, 
			      &acSuffix, 
			      &acReturnType, 
			      &nReturnSize, 
			      &myPcode, 
			      &function, 
			      &constructor, 
			      &destructor, 
			      &signal, 
			      &slot, 
			      &pc_pos, 
			      &nScope, 
			      &nTokenPos,
			      &nTokenLinePos,
			      &bStatic,
			      &bAbstract,
            &acFile2,
            &nLine,
            &bDeclare,
            &acAlias,
            &acLib,
            &acLibCallSignature      
         );

          if (nPhase == 0){ myParser->myClass->addClassMethod(
            	acClassName, 
			        acRealName, 
			        acName, 
			        acSuffix, 
			        acReturnType, 
			        nReturnSize, 
			        GETNEWPCODE, 
			        function, 
			        constructor, 
			        destructor, 
			        signal, 
			        slot, 
			        pc_pos, 
			        nScope, 
			        nTokenPos,
			        nTokenLinePos,
			        bStatic,
			        bAbstract,
              acFile2,
              nLine,
              bDeclare,
              acAlias,
              acLib,
              acLibCallSignature                
              , ID);
          
              if (destructor){
                // merke destructor id
                myParser->myClass->setDestructorId(myParser->myClass->getId(acClassName), ID);
              }
          }

            nLine = nLine;


        }
        break;     

      case memory_class_addClassPropertyGet:
        {
          static t_builtin c; t_integer ID; 
			    static t_cstring acClassName; 
			    static t_cstring acRealName; 
			    static t_cstring acName; 
			    static t_cstring acSuffix; 
			    static t_cstring acReturnType; 
			    static t_integer nReturnSize; 
			    static t_integer myPcode; 
			    static t_boolean function; 
			    static t_integer pc_pos; 
			    static t_integer nScope; 
			    static t_integer nTokenPos;
			    static t_integer nTokenLinePos;
			    static t_boolean bStatic;
			    static t_boolean bAbstract;
          static t_cstring acFile2;
          static t_integer nLine;
          static t_boolean bDeclare;
          static t_cstring acAlias;
          static t_cstring acLib;
          static t_cstring acLibCallSignature;   

          rd_memory_class_addClassPropertyGet(acFile, &c, &ID, 
			      &acClassName, 
			      &acName, 
			      &acSuffix, 
			      &acReturnType, 
			      &nReturnSize, 
			      &myPcode, 
			      &function, 
			      &pc_pos, 
			      &nScope, 
			      &nTokenPos,
			      &nTokenLinePos,
			      &bStatic,
			      &bAbstract,
            &acFile2,
            &nLine
         );

          if (nPhase == 0) myParser->myClass->addClassPropertyGet(
            	acClassName, 
			        acName, 
			        acSuffix, 
			        acReturnType, 
			        nReturnSize, 
			        GETNEWPCODE, 
			        function, 
			        pc_pos, 
			        nScope, 
			        nTokenPos,
			        nTokenLinePos,
			        bStatic,
			        bAbstract,
              acFile2,
              nLine         
              , ID);

        }
        break;     

      case memory_class_addClassPropertySet:
        {
          static t_builtin c; t_integer ID; 
			    static t_cstring acClassName; 
			    static t_cstring acRealName; 
			    static t_cstring acName; 
			    static t_cstring acSuffix; 
			    static t_cstring acReturnType; 
			    static t_integer nReturnSize; 
			    static t_integer myPcode; 
			    static t_boolean function; 
			    static t_integer pc_pos; 
			    static t_integer nScope; 
			    static t_integer nTokenPos;
			    static t_integer nTokenLinePos;
			    static t_boolean bStatic;
			    static t_boolean bAbstract;
          static t_cstring acFile2;
          static t_integer nLine;
          static t_boolean bDeclare;
          static t_cstring acAlias;
          static t_cstring acLib;
          static t_cstring acLibCallSignature;   

          rd_memory_class_addClassPropertySet(acFile, &c, &ID, 
			      &acClassName, 
			      &acName, 
			      &acSuffix, 
			      &acReturnType, 
			      &nReturnSize, 
			      &myPcode, 
			      &function, 
			      &pc_pos, 
			      &nScope, 
			      &nTokenPos,
			      &nTokenLinePos,
			      &bStatic,
			      &bAbstract,
            &acFile2,
            &nLine
         );

          if (nPhase == 0) myParser->myClass->addClassPropertySet(
            	acClassName, 
			        acName, 
			        acSuffix, 
			        acReturnType, 
			        nReturnSize, 
			        GETNEWPCODE, 
			        function, 
			        pc_pos, 
			        nScope, 
			        nTokenPos,
			        nTokenLinePos,
			        bStatic,
			        bAbstract,
              acFile2,
              nLine         
              , ID);

        }
        break;     

      case memory_class_addThrowMethod:
        {
          static t_builtin c; static t_integer nClassId; static t_integer nId; static t_cstring acType;

          rd_memory_class_addThrowMethod(acFile, &c, &nClassId, &nId, &acType);

          if (nPhase == 0) myParser->myClass->addThrowMethod(nClassId, nId, acType);

        }
        break;     

      case memory_class_addParameterMethod:
        {
          static t_builtin c; static t_integer nClassId; static t_integer nId; static t_cstring acName; static t_cstring acType; static t_integer nParameterCall; static t_boolean bOptional; static t_boolean bDefault; static t_boolean bParamArray; static t_array a; static defaultvalue defval; static t_integer nParamId; static t_integer nParamLStringLen; 

          rd_memory_class_addParameterMethod(acFile, &c, &nClassId, &nId, &acName, &acType, &nParameterCall, &bOptional, &bDefault, &bParamArray, &a, &defval, &nParamId, &nParamLStringLen);


#ifdef KBC
          if (nPhase == 0) myParser->myClass->addParameterMethod(nClassId, nId, acName, acType, nParameterCall, bOptional, bDefault, bParamArray, &a, &defval, &nParamId, &nParamLStringLen);
#else
          if (nPhase == 0) myParser->myClass->addParameterMethod(nClassId, nId, acName, acType, nParameterCall, bOptional, bDefault, bParamArray, &a, &defval, &nParamId);
#endif          

        }
        break;     
        
      case memory_class_addParameterPropertySet:
        {
          static t_builtin c; static t_integer nClassId; static t_integer nId; static t_cstring acName; static t_cstring acType; static t_integer nParameterCall; static t_boolean bOptional; static t_boolean bDefault; static t_boolean bParamArray; static t_array a; static defaultvalue defval; static t_integer nParamId;  static t_integer nParamLStringLen; 

          rd_memory_class_addParameterPropertySet(acFile, &c, &nClassId, &nId, &acName, &acType, &nParameterCall, &bOptional, &bDefault, &bParamArray, &a, &defval, &nParamId, &nParamLStringLen);


#ifdef KBC
          if (nPhase == 0) myParser->myClass->addParameterPropertySet(nClassId, nId, acName, acType, nParameterCall, bOptional, bDefault, bParamArray, &a, &defval, &nParamId, &nParamLStringLen);
#else
          if (nPhase == 0) myParser->myClass->addParameterPropertySet(nClassId, nId, acName, acType, nParameterCall, bOptional, bDefault, bParamArray, &a, &defval, &nParamId);
#endif          

        }
        break;     

      case memory_class_registerCallMethod:
        {
          static t_builtin c; static t_integer nClassId; static t_integer nId; static t_integer pcodeCall; static t_integer nPcodePos;

          rd_memory_class_registerCallMethod(acFile, &c, &nClassId, &nId, &pcodeCall, &nPcodePos);
#ifdef KBC
          if (nPhase == 1) myParser->myClass->registerCallMethod(nClassId, nId, getNewPcode(pcodeCall), nPcodePos);
#endif

        }
        break;     
        
      case memory_class_registerCallPropertyGet:
        {
          static t_builtin c; static t_integer nClassId; static t_integer nId; static t_integer pcodeCall; static t_integer nPcodePos;

          rd_memory_class_registerCallPropertyGet(acFile, &c, &nClassId, &nId, &pcodeCall, &nPcodePos);
#ifdef KBC
          if (nPhase == 1) myParser->myClass->registerCallPropertyGet(nClassId, nId, getNewPcode(pcodeCall), nPcodePos);
#endif

        }
        break;     
        
      case memory_class_registerCallPropertySet:
        {
          static t_builtin c; static t_integer nClassId; static t_integer nId; static t_integer pcodeCall; static t_integer nPcodePos;

          rd_memory_class_registerCallPropertySet(acFile, &c, &nClassId, &nId, &pcodeCall, &nPcodePos);
#ifdef KBC
          if (nPhase == 1) myParser->myClass->registerCallPropertySet(nClassId, nId, getNewPcode(pcodeCall), nPcodePos);
#endif

        }
        break;     
        
      case memory_class_addVar:
        {
          static t_builtin c; static t_integer ID; static t_integer nClassId; static t_cstring acName; static t_integer nType; static t_array a; static  t_boolean bStatic; static t_integer nScope; static t_integer nLStringLen;

          rd_memory_class_addVar(acFile, &c, &ID, &nClassId, &acName, &nType, &a, &bStatic, &nScope, &nLStringLen);

          if (nPhase == 0) myParser->myClass->addVar(nClassId, acName, nType, &a, bStatic, nScope, nLStringLen, ID);

        }
        break;     
        
      case memory_class_addStaticVar:
        {
          static t_builtin c; static t_integer ID; static t_integer nClassId; static t_cstring acName; static t_integer nType; static t_array a; static t_boolean bStatic; static t_integer nScope; static t_integer nLStringLen;

          rd_memory_class_addStaticVar(acFile, &c, &ID, &nClassId, &acName, &nType, &a, &bStatic, &nScope, &nLStringLen);

          if (nPhase == 0) myParser->myClass->addStaticVar(nClassId, acName, nType, &a, bStatic, nScope, nLStringLen, ID);

        }
        break;     
        
      case memory_class_addConst:
        {
          static t_builtin c; static t_integer ID; static t_integer nClassId; static t_cstring acName; static t_integer nScope;

          rd_memory_class_addConst(acFile, &c, &ID, &nClassId, &acName, &nScope);

          if (nPhase == 0) myParser->myClass->addConst(nClassId, acName, nScope, ID);

        }
        break;     
        
      case memory_class_addMethodVar:
        {
          static t_builtin c; static t_integer ID; static t_integer nClassId; static t_cstring acMethod; static t_cstring acName; static t_integer nType; static t_array a; static t_boolean bStatic; static t_integer nScope; static t_integer nLStringLen;

          rd_memory_class_addMethodVar(acFile, &c, &ID, &nClassId, &acMethod, &acName, &nType, &a, &bStatic, &nScope, &nLStringLen);

          if (nPhase == 0) myParser->myClass->addMethodVar(nClassId, acMethod, acName, nType, &a, bStatic, nScope, nLStringLen, ID);

        }
        break;     
        
      case memory_class_addPropertyGetVar:
        {
          static t_builtin c; static t_integer ID; static t_integer nClassId; static t_cstring acMethod; static t_cstring acName; static t_integer nType; static t_array a; static t_boolean bStatic; static t_integer nScope; static t_integer nLStringLen;

          rd_memory_class_addPropertyGetVar(acFile, &c, &ID, &nClassId, &acMethod, &acName, &nType, &a, &bStatic, &nScope, &nLStringLen);

          if (nPhase == 0) myParser->myClass->addPropertyGetVar(nClassId, acMethod, acName, nType, &a, bStatic, nScope, nLStringLen, ID);

        }
        break;     
        
      case memory_class_addPropertySetVar:
        {
          static t_builtin c; static t_integer ID; static t_integer nClassId; static t_cstring acMethod; static t_cstring acName; static t_integer nType; static t_array a; static t_boolean bStatic; static t_integer nScope; static t_integer nLStringLen;

          rd_memory_class_addPropertySetVar(acFile, &c, &ID, &nClassId, &acMethod, &acName, &nType, &a, &bStatic, &nScope, &nLStringLen);

          if (nPhase == 0) myParser->myClass->addPropertySetVar(nClassId, acMethod, acName, nType, &a, bStatic, nScope, nLStringLen, ID);

        }
        break;     
        
      case memory_class_addMethodConst:
        {
          static t_builtin c; static t_integer ID; static t_integer nClassId; static t_cstring acMethod; static t_cstring acName;  

          rd_memory_class_addMethodConst(acFile, &c, &ID, &nClassId, &acMethod, &acName);

          if (nPhase == 0) myParser->myClass->addMethodConst(nClassId, acMethod, acName, ID);

        }
        break;     

      case memory_class_addPropertyGetConst:
        {
          static t_builtin c; static t_integer ID; static t_integer nClassId; static t_cstring acMethod; static t_cstring acName;  

          rd_memory_class_addPropertyGetConst(acFile, &c, &ID, &nClassId, &acMethod, &acName);

          // addMethodConst takes care of PropertyGet
          if (nPhase == 0) myParser->myClass->addMethodConst(nClassId, acMethod, acName, ID);

        }
        break;     

      case memory_class_addPropertySetConst:
        {
          static t_builtin c; static t_integer ID; static t_integer nClassId; static t_cstring acMethod; static t_cstring acName;  

          rd_memory_class_addPropertySetConst(acFile, &c, &ID, &nClassId, &acMethod, &acName);

          // addMethodConst takes care of PropertySet
          if (nPhase == 0) myParser->myClass->addMethodConst(nClassId, acMethod, acName, ID);

        }
        break;     

      case memory_class_registerCatch:
        {

          static t_builtin c; static t_integer nClassId; static t_integer pcodeCall; static t_integer nCatchType; static t_integer nPcodePos; static t_integer nCatchPcodePos;

          rd_memory_class_registerCatch(acFile, &c, &nClassId, &pcodeCall, &nCatchType, &nPcodePos, &nCatchPcodePos);
#ifdef KBC
          if (nPhase == 1) myParser->myClass->registerCatch(nClassId, getNewPcode(pcodeCall), nCatchType, nPcodePos, nCatchPcodePos);
#endif

        }
        break;     

      case memory_class_bindingparam:
        {
          static t_builtin c; static t_integer classid; static t_cstring classmethodno; static t_integer no; static t_integer identifier;

          rd_memory_class_bindingparam(acFile, &c, &classid, &classmethodno, &no, &identifier);

#ifdef KBC
          if (nPhase == 1) myParser->myPcodeAll->wr_CLASS_BINDINGPARAM(pcode__CLASS_BINDINGPARAM, classid, classmethodno, no, identifier);
#endif

        }
        break;   

      default:
        //  error
     	  CONSOLE printError("error reading cache information in cache.cpp");
        goto ex;

        break;
    }



#ifdef KBC
	} while( ((pcode *) x.getString(acFile))->getPos() < nLen );
ex:
#else
	} while(ppp->getPos() < nLen );
ex:
  delete ppp;
#endif

  return true;

}

#endif