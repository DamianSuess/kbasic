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

#include "parser.h"
#include "../kbshared/cache.h"

parser::parser()
{
  bNoError = true;

  myMemory_stringliteral = new memory_stringliteral();
  myMemory_type = new memory_type();
  myMemory_enum = new memory_enum();
  myClass = new memory_class();
  myModule = new memory_module();

  my_cache = new cache();
  my_cache->doParser(this, "", 0);
}

parser::~parser()
{
  delete myMemory_stringliteral;
  delete myMemory_type;
  delete myMemory_enum;
  delete myClass;
  delete myModule;

  delete my_cache;
}
  
bool parser::findVar(int nId, const char **acModule, const char **acSub, const char **acName){

  // class
  if (myClass->findVar(nId, acModule, acSub, acName)) return true;

  // default global & module
  if (myModule->findVar(nId, acModule, acSub, acName)) return true;

  
  //variables of dll calls are not stored in the parser information file, so drop no error please

  char ac[1024];
  sprintf(ac, "parser_interface::findVar() --> variable %d not found", nId);
 internalError(ac);
  return false; 
}

bool parser::findConst(int nId, const char **acModule, const char **acSub, const char **acName)
{ 

  // class
  if (myClass->findConst(nId, acModule, acSub, acName)) return true;

  // default global & module
  if (myModule->findConst(nId, acModule, acSub, acName)) return true;

 internalError("parser_interface::findConst() --> const not found");

 return false;
}

bool parser::findScope(int nModuleId, int nSubId, bool bPropertyGet, bool bPropertySet, const char **acModule, const char **acSub)
{
  
  if (bPropertyGet){

    // class
    if (myClass->existPropertyGet(nModuleId, nSubId)){
      *acModule = myClass->getName(nModuleId);
      *acSub = myClass->getNamePropertyGet(nModuleId, nSubId);
      return true;
    }
  } else if (bPropertySet){

    // class
    if (myClass->existPropertySet(nModuleId, nSubId)){
      *acModule = myClass->getName(nModuleId);
      *acSub = myClass->getNamePropertySet(nModuleId, nSubId);
      return true;
    }
  } else {

  // class
  if (myClass->existMethod(nModuleId, nSubId)){
    *acModule = myClass->getName(nModuleId);
    *acSub = myClass->getNameMethod(nModuleId, nSubId);
    return true;
  }

  // module
  if (myModule->existSub(nModuleId, nSubId)){
    *acModule = myModule->getName(nModuleId);
    *acSub = myModule->getNameSub(nModuleId, nSubId);
    return true;
  }
  }

 internalError("parser_interface::findScope() --> scope not found");

 return false;
}

bool parser::findScope2(int nModuleId, int nSubId, bool bPropertyGet, bool bPropertySet, const char **acModule, const char **acSub)
{

  if (bPropertyGet){

    // class
    if (myClass->existPropertyGet(nModuleId, nSubId)){
      *acModule = myClass->getName(nModuleId);
      *acSub = myClass->getNamePropertyGet(nModuleId, nSubId);
      return true;
    }
  } else if (bPropertySet){

    // class
    if (myClass->existPropertySet(nModuleId, nSubId)){
      *acModule = myClass->getName(nModuleId);
      *acSub = myClass->getNamePropertySet(nModuleId, nSubId);
      return true;
    }
  } else {

    // class
    if (myClass->existMethod(nModuleId, nSubId)){
      *acModule = myClass->getName(nModuleId);
      *acSub = myClass->getRealNameMethod(nModuleId, nSubId);
      return true;
    }

    // module
    if (myModule->existSub(nModuleId, nSubId)){
      *acModule = myModule->getName(nModuleId);
      *acSub = myModule->getRealNameSub(nModuleId, nSubId);
      return true;
    }
  }

 internalError("parser_interface::findScope() --> scope not found");

 return false;
}

const char *parser::findStringLiteral(int id){ return myMemory_stringliteral->getName(id); }

const char *parser::findType(int id){ return myMemory_type->getName(id); }
const char *parser::findTypeElement(int myMemory_typeid, int field_id){ return myMemory_type->findElement(myMemory_typeid, field_id); }

const char *parser::findEnum(int id){ return myMemory_enum->getName(id); }
const char *parser::findEnumElement(int nEnumId, int field_id){ return myMemory_enum->findEnumElement(nEnumId, field_id); }

bool parser::internalError(const char *acInternalError)
{
	if (bNoError){ // throw error only, if no other error occured before
  	static char acText[1024];

  	sprintf(acText, "internal error: %s", acInternalError);
  	CONSOLE printError(acText);

  //} else if (bCodeInsight){
    //errorRecovering();	
    bNoError = false;
    qApp->exit();
  }
	return false;
}