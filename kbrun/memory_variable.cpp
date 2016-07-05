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

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "utility.h"
#include "../kbshared/console.h"
#include "memory_variable.h"
#include "../kbshared/pcode.h"

#include "interpreter_parameter.h"

extern int nBinaryPos;

int memory_variable::nIdCounter = 0;

QString kbNullQString = "";

memory_variable::memory_variable			()
{
  nClassId = 0;
  vBindingParentClassPointer = 0;
  nBindingParentClassType = 0;

  bError = false;
	//nIdCounter = 0; darf nicht auf 0 gesetzt werden, da sonst nicht jede id einer variablen unique ist
}

memory_variable::~memory_variable			()
{
  // clear memory for string and structs/types

  for ( it = list_variable.begin(); it != list_variable.end(); ++it ) {
     remove(*it);
  }

  list_variable.clear();

  findMemory_variable(-99); // delete cache
}

void memory_variable::removeAllExceptObjects			()
{
  // clear memory for string and structs/types

  for ( it = list_variable.begin(); it != list_variable.end(); ++it ) {
      remove((*it));
  }

  list_variable.clear();
//  list_variable2.clear();
}

void memory_variable::remove			(variable *v)
{
  char **ac;
  QString **s;
  
  if (v->nType == pcode__VARIANT){

    { 
      if ((char *) (v->struct_)) free ((char *) (v->struct_));
    }

  } else {
    if (v->nType == pcode__QSTRING){
      s = (QString **) (v->struct_);
      if (*s) delete (*s);
      if ((char *) (v->struct_)){
        free ((char *) (v->struct_));
      }

    } else if (v->nType == pcode__CSTRING){
      ac = (char **) (v->struct_);
      if (*ac){
        free (*ac);
      }
      if ((char *) (v->struct_)){
        free ((char *) (v->struct_));
      }

      // struct as type used
    } else { 
      if ((char *) (v->struct_)) free ((char *) (v->struct_));
    }
  }

  if ((char *) (v->struct2_)){
    free ((char *) (v->struct2_));
  }

  delete v;
}

void memory_variable::resetIdCounter			()
{
	nIdCounter = 0;
}

int memory_variable::addIdCounter			()
{
	nIdCounter++;
  return nIdCounter;
}

void memory_variable::setIdCounter			(int i)
{
	nIdCounter = i;
}

// ****************************
// * bool memory_variableError(char *acmemory_variableError)
// *
// * description:
// * prints a variable error message
// *
// * parameter:
// * char *acmemory_variableError = the error message to print
// *
// * return:
// * dummy
// ****************************
bool memory_variable::memory_variableError(char *acMemory_variableError)
{
	static char acText[1024];

  if (bError) return false;

	sprintf(acText, "\ninternal error (memory variable): %s\n", acMemory_variableError);
	CONSOLE printError(acText);

  bError = true;
	return false;
}

variable *memory_variable::newMemory_variable(
                const char *acModule, 
                const char *acSub, 
                const char *acName, 
                int nId, 
                int nType, 
                t_array *a, 
                bool bByVal, 
                bool bReference, 
                bool bStatic, 
                int nScope,
                int nTypeSize
                )
{
  /*
  if (nId == 26){
    nId = nId;
  }*/

	variable *v = new variable();

#ifdef HAS_CONSOLE
  int n = strlen(acModule);

	memcpy(v->acModule, acModule, n);
	v->acModule[n] = '\0';

  n = strlen(acSub);

  memcpy(v->acSub, acSub, n);
	v->acSub[n] = '\0';

  n = strlen(acName);

  memcpy(v->acName, acName, n);
	v->acName[n] = '\0';
#endif

	v->struct_ = 0;
	v->struct2_ = 0;

	v->nType = nType;

  v->nReferenceId = 0;


	v->nTypeSize = nTypeSize;
	v->bByVal = bByVal;
	v->bIsMissing = false;  
	v->bReference = bReference;
	v->nScope = nScope;
	
	v->nId = nId;
	v->bStatic = bStatic;

 

  v->nVariantType = pcode__EMPTY;

  if (nType == pcode__LQSTRING){
    if (nTypeSize < sizeof(t_qstring)){
      nTypeSize = 5;
    } else {
      nTypeSize++;
    }
  } else if (nType == pcode__LCSTRING){
    if (nTypeSize < sizeof(t_cstring)){
      nTypeSize = 5;
    } else {
      nTypeSize++;
    }
  }

	int nStructSize = 1;
	int nStructSize2 = 1;
	if (a){
		v->a.count = a->count;
		v->a.type = nType;
		for (int i = 0; i < a->count; i++){
      v->a.idx[i] = a->idx[i];
      v->a.idxTo[i] = a->idxTo[i];
      //int nn = (a->idx[i] + 0 - a->idxTo[i] + 1); // get count of idx			
      //###nStructSize *= a->typeSizeMulitplierOfArray();
    }
    nStructSize *= a->typeSizeMulitplierOfArray();
  } else {
		v->a.count = 0;
		v->a.type = 0;
  }

	if (nStructSize <= 1){
		nStructSize = nTypeSize;
	} else {
		nStructSize *= nTypeSize;
	}

  if (nStructSize == 0){
    nStructSize = sizeof(t_variant); // at least t_variant size;
  }

  nStructSize2 = interpreter_parameter::kbasic_binding_sizeof(nType) * 2; 

	v->nStructSize = nStructSize;
	v->nStructSize2 = nStructSize2;	

  {
		v->struct_ = (char *) malloc(nStructSize);
		//if (v->struct_ == 0){ memory_variableError("memory allocation failed"); return 0; }
    memset(v->struct_, 0, nStructSize);
	}

  if (nStructSize2){
		v->struct2_ = (char *) malloc(nStructSize2);
		//if (v->struct2_ == 0){ memory_variableError("memory allocation failed (2)"); return 0; }
    memset(v->struct2_, 0, nStructSize2);
  } else {
    v->struct2_ = 0;
  }

  return v;
}

void memory_variable::declare(int nId, int n)
{	
	variable *v = new variable();
  memset(v, 0, sizeof(variable));
  v->nType = pcode__t_integer;

  v->struct_ = (char *) malloc(sizeof(int));
  memset(v->struct_, 0, sizeof(int));

  *(t_integer *)(v->struct_) = n;

	list_variable.insert(nId, v);

}

void memory_variable::declare(int nId, bool b)
{	
	variable *v = new variable();
  memset(v, 0, sizeof(variable));
  v->nType = pcode__t_boolean;

  v->struct_ = (char *) malloc(sizeof(bool));
  memset(v->struct_, 0, sizeof(bool));

  *(t_boolean *)(v->struct_) = b;

	list_variable.insert(nId, v);

}

int 		memory_variable::declare			(
                                       const char *acModule, 
                                       const char *acSub, 
                                       const char *acName, 
                                       int nType, 
                                       t_array *a, 
                                       bool bByVal, 
                                       bool bReference, 
                                       bool bStatic, 
                                       bool bInit, 
                                       int nScope, 
                                       int nTypeSize,
                                       int nId
                                      )
{

  
  {


    bool bExist = exist(nId);
    if (nId != -1 && bExist == false){
		  variable *c = newMemory_variable(acModule, acSub, acName, nId, nType, a, bByVal, bReference, bStatic, nScope, nTypeSize);

		  list_variable.insert(nId, c);
    }
	
    if (!bInit || bExist) return nId;

		// zero other datatypes, default values

		switch(nType){
/*
			case pcode__BOOLEAN:
				setBoolean(nId, false, 0);
				break;
*/
			case pcode__QSTRING:
			case pcode__LQSTRING:
				setQString(nId, &kbNullQString, 0);
				break;			
			case pcode__CSTRING:
			case pcode__LCSTRING:
				setCString(nId, "", 0, nTypeSize);
				break;			
/*
			case pcode__SINGLE:
				setSingle(nId, 0, 0);
				break;
			case pcode__DOUBLE:
				setDouble(nId, 0, 0);
				break;

      case pcode__BYTE:
				setByte(nId, 0, 0);
        break;
			case pcode__SHORT:
				setShort(nId, 0, 0);
				break;
			case pcode__INTEGER:
				setInteger(nId, 0, 0);
				break;
      case pcode__LONG:
				setLong(nId, 0, 0);
				break;*/
/*
			case pcode__INT16:
				setInt16(nId, 0, 0);
				break;
			case pcode__INT32:
				setInt32(nId, 0, 0);
				break;
			case pcode__INT64:
				setInt64(nId, 0, 0);
				break;
			case pcode__UINT16:
				setUInt16(nId, 0, 0);
				break;
			case pcode__UINT32:
				setUInt32(nId, 0, 0);
				break;
			case pcode__UINT64:
				setUInt64(nId, 0, 0);
				break;
        */
     
      case pcode__VARIANT: // 
        /*
				setVariant_Boolean(nId, false, 0);

       setVariant_String(nId, "", 0);

				setVariant_Single(nId, 0, 0);
				setVariant_Double(nId, 0, 0);

				setVariant_Byte(nId, 0, 0);
				setVariant_Short(nId, 0, 0);
				setVariant_Integer(nId, 0, 0);
				setVariant_Long(nId, 0, 0);
        */


       setVariantType(nId, pcode__EMPTY);

       break;

      /*
			case pcode__CHARACTER:
				// setDate(nId, 0, 0); // TODO3
				break;
      */
			case pcode__CURRENCY:
			  setCurrency(nId, 0, 0); 
				break;
			case pcode__DATE:
			  setDate(nId, 0, 0); 
				break;
 //			case pcode__OBJECT:
//				setObject(nId, 0, 0);
//				break;
 //   default:
				// pointer or object set zero
	//			setPointer(nId, 0, 0);
	//			break;
   	}

    return nId;

	}
	return 0;
}

int 		memory_variable::declare			(int nType, t_array *a, bool bByVal, bool bStatic, int nId)
{

 	nIdCounter++;
 	if (nId == -1) nId = nIdCounter; else nIdCounter = nId;

  int nTypeSize = 0;

  variable *c = newMemory_variable("", "", "", nId, nType, a, bByVal, false, bStatic, false, nTypeSize);
	list_variable.insert(nId, c);

  switch(nType){
		case pcode__QSTRING:
		case pcode__LQSTRING:
       setQString(nId, &kbNullQString, 0); // init the STRING, other datatypes are zeroed
       break;
		case pcode__CSTRING:
		case pcode__LCSTRING:
       setCString(nId, "", 0, 0); // init the STRING, other datatypes are zeroed
       break;
  }

 	return nId;

}

int 		memory_variable::redeclare		(int nId, int nType, t_array *a, bool bPreserve)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){
    {

      if (v->nType == pcode__VARIANT){
        v->nVariantType = pcode__EMPTY;
      }

	    v->a.count = 0;  

	    int nStructSize = 1;
	    int nStructSize2 = 1;
	    if (a){
		    v->a.count = a->count;
		    v->a.type = nType;
		    for (int i = 0; i < a->count; i++){
        v->a.idx[i] = a->idx[i];
        v->a.idxTo[i] = a->idxTo[i];
        //int nn = (a->idx[i] + 0 - a->idxTo[i] + 1); // get count of idx
			    nStructSize *= a->typeSizeMulitplierOfArray();
       }
	    }

	    if (nStructSize <= 1){
		    nStructSize = v->nTypeSize;
	    } else {
		    nStructSize *= v->nTypeSize;
	    }

      if (nStructSize == 0){
       nStructSize = sizeof(t_variant); // at least t_variant size;
      }

      int nOldStructSize = v->nStructSize;
	    v->nStructSize = nStructSize;

      if (bPreserve){

        v->struct_ = (char *) realloc(v->struct_, nStructSize);
        if (v->struct_ == 0){ memory_variableError("memory allocation failed"); return 0; }

        if (nOldStructSize < nStructSize){ // if old was smaller, then
          memset(v->struct_ + nOldStructSize, 0, nStructSize - nOldStructSize);
        }

      } else {

        free(v->struct_);

	      v->struct_ = (char *) malloc(nStructSize);
	      if (v->struct_ == 0){ memory_variableError("memory allocation failed"); return 0; }
        memset(v->struct_, 0, nStructSize);
  	
      }

    }


  	return true;
  }

	return false;

}


bool 		memory_variable::undeclare			(int nId)
{
  if (nId == 0) return false;  

	variable *v = findMemory_variable	(nId);
	if (v != 0){
    remove(v);
    list_variable.remove(nId);

  	return true;
  }


	return false;
}

bool 		memory_variable::undeclare			(const char *acModule, const char *acSub, const char *acName)
{
	return undeclare (getId(acModule, acSub, acName));
}


char *memory_variable::getKey(const char *acModule, const char *acSub, const char *acName)
{
	static char acKey[1024];
	sprintf(acKey, "%s.%s.%s", acModule, acSub, acName);
  // make case insensitive
  int n = strlen(acKey);
	for (unsigned int i = 0; i < n; i++) acKey[i] = toupper(acKey[i]);

	return acKey;
}

bool 		memory_variable::exist				(int nId)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){
		return true;
	}
	return false;
}

bool 		memory_variable::exist				(const char *acModule, const char *acSub, const char *acName)
{
	return exist	(getId(acModule, acSub, acName));
}

bool 		memory_variable::findVar				(int nId, const char **acModule, const char **acSub, const char **acName)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){	
   
    *acModule = getModule(nId); 
    *acSub = getSub(nId); 
    *acName = getName(nId); 

    return true; 
  }
  return false;
}

const char     *memory_variable::getModule			(int nId)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){
		return v->acModule;
	}
	return 0; 
}

const char     *memory_variable::getSub			(int nId)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){
		return v->acSub;
	}
	return 0;
}

const char     *memory_variable::getName			(int nId)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){
		return v->acName;
	}
	return 0;
}

void     memory_variable::setTypeSize			(int nId, int n)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){
		v->nTypeSize = n;
	}
}

int     memory_variable::getTypeSize			(int nId)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){
		return v->nTypeSize;
	}
	return 0;
}

int     memory_variable::getStructSize			(int nId)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){
		return v->nStructSize;
	}
	return 0;
}

t_array   *memory_variable::getArray		(int nId)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){
		return &(v->a);
	}
	return 0;
}

bool memory_variable::isEmpty		(int nId)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){
    return v->nType == pcode__VARIANT && v->nVariantType == pcode__EMPTY;
	}
	return false;
}

bool memory_variable::isArray		(int nId)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){
    return v->a.isArray();
	}
	return false;
}

bool   memory_variable::isByVal		(int nId)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){
		return v->bByVal;
	}
	return true;
}

bool   memory_variable::isByRef	(int nId)
{
	return !isByVal(nId);
}

bool   memory_variable::isMissing	(int nId)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){
		return v->bIsMissing;
	}
	return true;
}

int			memory_variable::getId					()
{
	return (*it)->nId;
}

bool   memory_variable::isStatic		(int nId)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){
		return v->bStatic;
	}
	return true;
}

bool   memory_variable::isPrivate		(int nId)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){
    int nScope = v->nScope;
	  return nScope == 0;
	}
	return true;
}

bool   memory_variable::isPublic		(int nId)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){
    int nScope = v->nScope;
	  return nScope == 0;
	}
	return true;
}

bool   memory_variable::isProtected		(int nId)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){
    int nScope = v->nScope;
	  return nScope == 0;
	}
	return true;
}

int   memory_variable::getScope		(int nId)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){
    int nScope = v->nScope;
	  return nScope;
	}
	return true;
}

int			memory_variable::getId					(const char *acModule, const char *acSub, const char *acName)
{
  /*
  char *acKey = getKey(acModule, acSub, acName);

	if (list_variable2.contains(acKey)){
		return list_variable2[acKey]->nId;
	}	 
*/
	return -1;
}

int			memory_variable::type				(int nId)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){
			return v->nType;
	}
	return -1;
}

int			memory_variable::getVariantType				(int nId)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){
			return v->nVariantType;
	}
	return -1;
}

int			memory_variable::type				(const char *acModule, const char *acSub, const char *acName)
{
	return type				(getId(acModule, acSub, acName));
}

// getter

t_qstring memory_variable::getQString		(int nId, int nOffset)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){

		if (v->nType == pcode__VARIANT){
      return getVariant_QString(nId, nOffset);

    } 

    
    {

			if (!checkOffset(v, nOffset, sizeof(t_qstring))) return false; 

      QString **ac2 = (QString **) (v->struct_ + nOffset);
      if (*ac2 == 0) return &kbNullQString;

      t_qstring ac = (t_qstring) *ac2;
			return ac;
		}
		//memory_variableError(utility::con(utility::ident(v->acModule, v->acSub, v->acName), " has wrong datatype"));
	}
	return 0; 
}
t_cstring memory_variable::getCString		(int nId, int nOffset)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){

		if (v->nType == pcode__VARIANT){
      return getVariant_CString(nId, nOffset);

    } 

    
    {

			if (!checkOffset(v, nOffset, sizeof(char))) return false;

      char **ac2 = (char **) (v->struct_ + nOffset);
     t_cstring ac = (t_cstring) *ac2;
			return ac;
		}
		//memory_variableError(utility::con(utility::ident(v->acModule, v->acSub, v->acName), " has wrong datatype"));
	}
	return 0; 
}
/*
t_string memory_variable::getString		(const char *acModule, const char *acSub, const char *acName, int nOffset)
{
	return getString		(getId(acModule, acSub, acName), nOffset);
}
*/

t_qstring memory_variable::getLQString		(int nId, int nOffset)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){


    
    {

			if (!checkOffset(v, nOffset, sizeof(t_qstring))) return false; 

      char *ac2 = (char *) (v->struct_ + nOffset);
     t_cstring ac = (t_cstring) ac2;


      static QString s;

      s = s.fromUtf8(ac);

      return &s;



		}
		//memory_variableError(utility::con(utility::ident(v->acModule, v->acSub, v->acName), " has wrong datatype"));
	}
	return 0; 
}
t_cstring memory_variable::getLCString		(int nId, int nOffset)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){

    {

			if (!checkOffset(v, nOffset, sizeof(char))) return false; 

      char *ac2 = (char *) (v->struct_ + nOffset);
     t_cstring ac = (t_cstring) ac2;
			return ac;
		}
		//memory_variableError(utility::con(utility::ident(v->acModule, v->acSub, v->acName), " has wrong datatype"));
	}
	return 0;
}
/*
t_string memory_variable::getLString		(const char *acModule, const char *acSub, const char *acName, int nOffset)
{
	return getLString		(getId(acModule, acSub, acName), nOffset);
}
*/

t_double 	memory_variable::getDouble 	(int nId, int nOffset)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){

    {
			if (!checkOffset(v, nOffset, sizeof(t_double))) return false;


      return *(t_double *) (v->struct_ + nOffset);

		}
		//memory_variableError(utility::con(utility::ident(v->acModule, v->acSub, v->acName), " has wrong datatype"));
	}
	return 0;
}
/*
t_double 	memory_variable::getDouble 	(const char *acModule, const char *acSub, const char *acName, int nOffset)
{
	return getDouble 	(getId(acModule, acSub, acName), nOffset);
}
*/
t_single 	memory_variable::getSingle		(int nId, int nOffset)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){

    {
			if (!checkOffset(v, nOffset, sizeof(t_single))) return false;
      
      return *(t_single *) (v->struct_ + nOffset);

		}
		//memory_variableError(utility::con(utility::ident(v->acModule, v->acSub, v->acName), " has wrong datatype"));
	}
	return 0;
}
/*
t_single 	memory_variable::getSingle		(const char *acModule, const char *acSub, const char *acName, int nOffset)
{
	return getSingle		(getId(acModule, acSub, acName), nOffset);
}
*/
t_integer 		memory_variable::getInteger	(int nId, int nOffset)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){

    {
			if (!checkOffset(v, nOffset, sizeof(t_integer))) return false;

      return *(t_integer *) (v->struct_ + nOffset);

		}
		//memory_variableError(utility::con(utility::ident(v->acModule, v->acSub, v->acName), " has wrong datatype"));
	}
	return 0;
}

t_variant 		memory_variable::getVariant	(int nId, int nOffset)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){
    
    {
			if (!checkOffset(v, nOffset, sizeof(t_variant))) return false;

      return *(t_variant *) (v->struct_ + nOffset);

		}
		//memory_variableError(utility::con(utility::ident(v->acModule, v->acSub, v->acName), " has wrong datatype"));
	}
	return 0;
}

t_boolean 		memory_variable::getVariant_Boolean	(int nId, int nOffset)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){

    {
			if (!checkOffset(v, nOffset, sizeof(t_variant))) return false;

			t_variant *n = (t_variant *) (v->struct_ + nOffset);
      if (n->nType == pcode__EMPTY || n->nType == 0) return 0;
      return n->toBoolean();

		}
		//memory_variableError(utility::con(utility::ident(v->acModule, v->acSub, v->acName), " has wrong datatype"));
	}
	return 0;
}

t_qstring 		memory_variable::getVariant_QString	(int nId, int nOffset)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){
    
    {
			if (!checkOffset(v, nOffset, sizeof(t_variant))) return false;

			t_variant *n = (t_variant *) (v->struct_ + nOffset);
      if (n->nType == pcode__EMPTY || n->nType == 0) return &kbNullQString;
      return n->toQString();

		}
		//memory_variableError(utility::con(utility::ident(v->acModule, v->acSub, v->acName), " has wrong datatype"));
	}
	return 0;
}

t_cstring 		memory_variable::getVariant_CString	(int nId, int nOffset)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){
    
    {
			if (!checkOffset(v, nOffset, sizeof(t_variant))) return false;

			t_variant *n = (t_variant *) (v->struct_ + nOffset);
      if (n->nType == pcode__EMPTY || n->nType == 0) return "";
      return n->toCString();
      
		}
		//memory_variableError(utility::con(utility::ident(v->acModule, v->acSub, v->acName), " has wrong datatype"));
	}
	return 0;
}

t_byte 		memory_variable::getVariant_Byte	(int nId, int nOffset)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){
    
    {
			if (!checkOffset(v, nOffset, sizeof(t_variant))) return false;

			t_variant *n = (t_variant *) (v->struct_ + nOffset);
      if (n->nType == pcode__EMPTY || n->nType == 0) return 0;
      return n->toByte();
      
		}
		//memory_variableError(utility::con(utility::ident(v->acModule, v->acSub, v->acName), " has wrong datatype"));
	}
	return 0;
}

t_short 		memory_variable::getVariant_Short	(int nId, int nOffset)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){
    
    {
			if (!checkOffset(v, nOffset, sizeof(t_variant))) return false;

			t_variant *n = (t_variant *) (v->struct_ + nOffset);
      if (n->nType == pcode__EMPTY || n->nType == 0) return 0;
      return n->toShort();
      
		}
		//memory_variableError(utility::con(utility::ident(v->acModule, v->acSub, v->acName), " has wrong datatype"));
	}
	return 0;
}

t_integer 		memory_variable::getVariant_Integer	(int nId, int nOffset)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){
    
    {
			if (!checkOffset(v, nOffset, sizeof(t_variant))) return false;

			t_variant *n = (t_variant *) (v->struct_ + nOffset);
      if (n->nType == pcode__EMPTY || n->nType == 0) return 0;
      return n->toInteger();

		}
		//memory_variableError(utility::con(utility::ident(v->acModule, v->acSub, v->acName), " has wrong datatype"));
	}
	return 0;
}

t_long 		memory_variable::getVariant_Long	(int nId, int nOffset)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){
    
    {
			if (!checkOffset(v, nOffset, sizeof(t_variant))) return false;

			t_variant *n = (t_variant *) (v->struct_ + nOffset);
      if (n->nType == pcode__EMPTY || n->nType == 0) return 0;
      return n->toLong();
      
		}
		//memory_variableError(utility::con(utility::ident(v->acModule, v->acSub, v->acName), " has wrong datatype"));
	}
	return 0;
}

t_single		memory_variable::getVariant_Single	(int nId, int nOffset)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){
    
    {
			if (!checkOffset(v, nOffset, sizeof(t_variant))) return false;

			t_variant *n = (t_variant *) (v->struct_ + nOffset);
      if (n->nType == pcode__EMPTY || n->nType == 0) return 0;
      return n->toSingle();

		}
		//memory_variableError(utility::con(utility::ident(v->acModule, v->acSub, v->acName), " has wrong datatype"));
	}
	return 0;
}

t_double		memory_variable::getVariant_Double	(int nId, int nOffset)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){
    
    {
			if (!checkOffset(v, nOffset, sizeof(t_variant))) return false;

			t_variant *n = (t_variant *) (v->struct_ + nOffset);
      if (n->nType == pcode__EMPTY || n->nType == 0) return 0;
      return n->toDouble();
      
		}
		//memory_variableError(utility::con(utility::ident(v->acModule, v->acSub, v->acName), " has wrong datatype"));
	}
	return 0;
}

t_currency		memory_variable::getVariant_Currency	(int nId, int nOffset)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){
    
    {
			if (!checkOffset(v, nOffset, sizeof(t_variant))) return t_currency();

			t_variant *n = (t_variant *) (v->struct_ + nOffset);
      if (n->nType == pcode__EMPTY || n->nType == 0) return t_currency();
      return n->toCurrency();

		}
		//memory_variableError(utility::con(utility::ident(v->acModule, v->acSub, v->acName), " has wrong datatype"));
	}
	return t_currency();
}

t_date		memory_variable::getVariant_Date	(int nId, int nOffset)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){
    
    {
			if (!checkOffset(v, nOffset, sizeof(t_variant))) return false;

			t_variant *n = (t_variant *) (v->struct_ + nOffset);
      if (n->nType == pcode__EMPTY || n->nType == 0) return 0;
      return n->toDate();

		}
		//memory_variableError(utility::con(utility::ident(v->acModule, v->acSub, v->acName), " has wrong datatype"));
	}
	return 0;
}

t_object		memory_variable::getVariant_Object	(int nId, int nOffset)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){
    
    {
			if (!checkOffset(v, nOffset, sizeof(t_variant))) return false;

			t_variant *n = (t_variant *) (v->struct_ + nOffset);
      if (n->nType == pcode__EMPTY || n->nType == 0) return 0;
      return n->toObject();

		}
		//memory_variableError(utility::con(utility::ident(v->acModule, v->acSub, v->acName), " has wrong datatype"));
	}
	return 0;
}

t_pointer		memory_variable::getVariant_Pointer	(int nId, int nOffset)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){

    {
			if (!checkOffset(v, nOffset, sizeof(t_variant))) return false;

			t_variant *n = (t_variant *) (v->struct_ + nOffset);
      if (n->nType == pcode__EMPTY || n->nType == 0) return 0;
      return n->toPointer();

		}
		//memory_variableError(utility::con(utility::ident(v->acModule, v->acSub, v->acName), " has wrong datatype"));
	}
	return 0;
}

t_short 		memory_variable::getShort	(int nId, int nOffset)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){
    
    {
			if (!checkOffset(v, nOffset, sizeof(t_short))) return false;

      return *(t_short *) (v->struct_ + nOffset);

		}
		//memory_variableError(utility::con(utility::ident(v->acModule, v->acSub, v->acName), " has wrong datatype"));
	}
	return 0;
}
/*
t_short 		memory_variable::getShort	(const char *acModule, const char *acSub, const char *acName, int nOffset)
{
	return getUInt64	(getId(acModule, acSub, acName), nOffset);
}
*/
t_long 		memory_variable::getLong			(int nId, int nOffset)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){
    
    {
			if (!checkOffset(v, nOffset, sizeof(t_long))) return false;

      return *(t_long *) (v->struct_ + nOffset);
      
		}
		//memory_variableError(utility::con(utility::ident(v->acModule, v->acSub, v->acName), " has wrong datatype"));
	}
	return 0;
}
/*
t_long 		memory_variable::getLong			(const char *acModule, const char *acSub, const char *acName, int nOffset)
{
	return getLong			(getId(acModule, acSub, acName), nOffset);
}
*/
t_boolean		memory_variable::getBoolean	(int nId, int nOffset)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){
    
    {
			if (!checkOffset(v, nOffset, sizeof(t_boolean))) return false;

      return *(t_boolean *) (v->struct_ + nOffset);
      
		}

		//memory_variableError(utility::con(utility::ident(v->acModule, v->acSub, v->acName), " has wrong datatype"));
	}
	return 0;
}
/*
t_boolean		memory_variable::getBoolean	(const char *acModule, const char *acSub, const char *acName, int nOffset)
{
	return getBoolean	(getId(acModule, acSub, acName), nOffset);
}
*/
t_byte		memory_variable::getByte	(int nId, int nOffset)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){
    
    {
			if (!checkOffset(v, nOffset, sizeof(t_byte))) return false;

      return *(t_byte *) (v->struct_ + nOffset);
      
		}
		//memory_variableError(utility::con(utility::ident(v->acModule, v->acSub, v->acName), " has wrong datatype"));
	}
	return 0;
}
/*
t_byte		memory_variable::getByte	(const char *acModule, const char *acSub, const char *acName, int nOffset)
{
	return getByte	(getId(acModule, acSub, acName), nOffset);
}
*/

// setter


void 		memory_variable::setQString_Boolean		(int nId, t_qstring s, t_boolean c, int nOffset)
{
//  QString str = QString("%1").arg(c ? "TRUE" : "FALSE");
  //sprintf(str, "%s", c ? "TRUE" : "FALSE");
	setQString_QString		(nId, s, &QString("%1").arg(c ? "TRUE" : "FALSE"), nOffset);
}

void 		memory_variable::setQString_Boolean		(int nId, t_boolean c, t_qstring s, int nOffset)
{
 // QString str = QString("%1").arg(c ? "TRUE" : "FALSE");
	setQString_QString		(nId, &QString("%1").arg(c ? "TRUE" : "FALSE"), s, nOffset);
}

void 		memory_variable::setQString_Byte		(int nId, t_qstring s, t_byte n, int nOffset)
{
	//static char str[1024];

	//sprintf(str, "%d", (t_integer) n);
	 setQString_QString		(nId, s, &QString("%1").arg(n), nOffset);
}

void 		memory_variable::setQString_Byte		(int nId, t_byte n, t_qstring s, int nOffset)
{
	//static char str[1024];

	//sprintf(str, "%d", (t_integer) n);
	 setQString_QString		(nId, &QString("%1").arg(n), s, nOffset);
}

void 		memory_variable::setQString_Short		(int nId, t_qstring s, t_short n, int nOffset)
{
//	static char str[1024];

	//sprintf(str, "%d", n);
	 setQString_QString		(nId, s, &QString("%1").arg(n), nOffset);
}

void 		memory_variable::setQString_Short		(int nId, t_short n, t_qstring s, int nOffset)
{
//	static char str[1024];

	//sprintf(str, "%d", n);
	 setQString_QString		(nId, &QString("%1").arg(n), s, nOffset);
}

void 		memory_variable::setQString_Integer		(int nId, t_qstring s, t_integer n, int nOffset)
{
//	static char str[1024];

//	sprintf(str, "%d", n);
	 setQString_QString		(nId, s, &QString("%1").arg(n), nOffset);
}

void 		memory_variable::setQString_Integer		(int nId, t_integer n, t_qstring s, int nOffset)
{
	//static char str[1024];

//	sprintf(str, "%d", n);
	 setQString_QString		(nId, &QString("%1").arg(n), s, nOffset);
}

void 		memory_variable::setQString_Long		(int nId, t_qstring s, t_long l, int nOffset)
{
	 setQString_QString		(nId, s, &QString("%1").arg(l), nOffset);
}

void 		memory_variable::setQString_Long		(int nId, t_long l, t_qstring s, int nOffset)
{
	 setQString_QString		(nId, &QString("%1").arg(l), s, nOffset);
}

void 		memory_variable::setQString_Single		(int nId, t_qstring s, t_single f, int nOffset)
{
	//static char str[1024];

	//sprintf(str, "%6f", f);
	 setQString_QString		(nId, s, &QString("%1").arg(f), nOffset);
}

void 		memory_variable::setQString_Single		(int nId, t_single f, t_qstring s, int nOffset)
{
	//static char str[1024];

	//sprintf(str, "%6f", f);
	 setQString_QString		(nId, &QString("%1").arg(f), s, nOffset);
}

void 		memory_variable::setQString_Double		(int nId, t_qstring s, t_double d, int nOffset)
{
  /*
	static char str[1024];

	sprintf(str, "%6f", d);*/
	 setQString_QString		(nId, s, &QString("%1").arg(d), nOffset);
}

void 		memory_variable::setQString_Double		(int nId, t_double d, t_qstring s, int nOffset)
{
  /*
	static char str[1024];

	sprintf(str, "%6f", d);*/
	 setQString_QString		(nId, &QString("%1").arg(d), s, nOffset);
}

void 		memory_variable::setQString_Currency		(int nId, t_qstring s, t_currency n, int nOffset)
{
/*
	static char str[1024];

  sprintf(str, "%s", n.toString());
*/
	 setQString_QString		(nId, s, n.toQString(), nOffset);
}

void 		memory_variable::setQString_Currency		(int nId, t_currency n, t_qstring s, int nOffset)
{
  /*
	static char str[1024];

  sprintf(str, "%s", n.toString());*/
	 setQString_QString		(nId, n.toQString(), s, nOffset);
}

void 		memory_variable::setQString_Date		(int nId, t_qstring s, t_date n, int nOffset)
{
	 setQString_QString		(nId, s, n.toQString(), nOffset);
}

void 		memory_variable::setQString_Date		(int nId, t_date n, t_qstring s, int nOffset)
{
	 setQString_QString		(nId, n.toQString(), s, nOffset);
}

void 		memory_variable::setQString_QString		(int nId, t_qstring s, t_qstring s2, int nOffset)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){

    QString **k = (QString **) (v->struct_ + nOffset);
    if (*k == 0) *k = new QString(); 
    QString *t = *k;
    *t = *s;
    *t += *s2;

    return;
   
		//memory_variableError(utility::con(utility::ident(v->acModule, v->acSub, v->acName), " has wrong datatype"));
	}
	return;
}

void 		memory_variable::setQString_CString		(int nId, t_qstring s, t_cstring s2, int nOffset)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){

   
      QString **k = (QString **) (v->struct_ + nOffset);
      if (*k == 0) *k = new QString(); 
      QString *t = *k;
      *t = *s;
      *t += s2;

      return;
  

	}
	return;
}

/*
void 		memory_variable::setQString_WString		(int nId, t_qstring s, t_cstring s2, int nOffset, int nStringLen)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){

   // if (v->nType == 9999){
      QString **k = (QString **) (v->struct_ + nOffset);
      if (*k == 0) *k = new QString(); 
      QString *t = *k;
      *t = *s;
      QString r;
      r.setUtf16((const ushort *) s2, nStringLen);
      *t += r;

      return;
  //  } 

	}
	return;
}*/

void 		memory_variable::setQString		(int nId, t_qstring s, int nOffset, int nBinaryPos)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){

    

   
      QString **k = (QString **) (v->struct_ + nOffset);
      if (s){
        if (*k == 0) *k = new QString(); 
        QString *t = *k;
        
        {
          *t = *s;

        }
      } else {
        if (*k != 0) delete *k;
        *k = 0;
      }

      return ;
  

	}
	return ;
  
}








void 		memory_variable::setCString_Boolean		(int nId, t_cstring s, t_boolean c, int nOffset)
{
	static char str[1024];

  sprintf(str, "%s", c ? "TRUE" : "FALSE");
	 setCString_CString		(nId, s, str, nOffset);
}

void 		memory_variable::setCString_Boolean		(int nId, t_boolean c, t_cstring s, int nOffset)
{
	static char str[1024];

  sprintf(str, "%s", c ? "TRUE" : "FALSE");
	 setCString_CString		(nId, str, s, nOffset);
}

void 		memory_variable::setCString_Byte		(int nId, t_cstring s, t_byte n, int nOffset)
{
	static char str[1024];

	sprintf(str, "%d", (t_integer) n);
	 setCString_CString		(nId, s, str, nOffset);
}

void 		memory_variable::setCString_Byte		(int nId, t_byte n, t_cstring s, int nOffset)
{
	static char str[1024];

	sprintf(str, "%d", (t_integer) n);
	 setCString_CString		(nId, str, s, nOffset);
}

void 		memory_variable::setCString_Short		(int nId, t_cstring s, t_short n, int nOffset)
{
	static char str[1024];

	sprintf(str, "%d", n);
	 setCString_CString		(nId, s, str, nOffset);
}

void 		memory_variable::setCString_Short		(int nId, t_short n, t_cstring s, int nOffset)
{
	static char str[1024];

	sprintf(str, "%d", n);
	 setCString_CString		(nId, str, s, nOffset);
}

void 		memory_variable::setCString_Integer		(int nId, t_cstring s, t_integer n, int nOffset)
{
	static char str[1024];

	sprintf(str, "%d", n);
	 setCString_CString		(nId, s, str, nOffset);
}

void 		memory_variable::setCString_Integer		(int nId, t_integer n, t_cstring s, int nOffset)
{
	static char str[1024];

	sprintf(str, "%d", n);
	 setCString_CString		(nId, str, s, nOffset);
}

void 		memory_variable::setCString_Long		(int nId, t_cstring s, t_long l, int nOffset)
{
	static char str[1024];

#ifdef WINDOWS
	sprintf(str, "%I64d", l); // HIDE
#else
	sprintf(str, "%lld", l);
#endif
	 setCString_CString		(nId, s, str, nOffset);
}

void 		memory_variable::setCString_Long		(int nId, t_long l, t_cstring s, int nOffset)
{
	static char str[1024];

#ifdef WINDOWS
	sprintf(str, "%I64d", l); // HIDE
#else
	sprintf(str, "%lld", l);
#endif
	 setCString_CString		(nId, str, s, nOffset);
}

void 		memory_variable::setCString_Single		(int nId, t_cstring s, t_single f, int nOffset)
{
	static char str[1024];

	sprintf(str, "%6f", f);
	 setCString_CString		(nId, s, str, nOffset);
}

void 		memory_variable::setCString_Single		(int nId, t_single f, t_cstring s, int nOffset)
{
	static char str[1024];

	sprintf(str, "%6f", f);
	 setCString_CString		(nId, str, s, nOffset);
}

void 		memory_variable::setCString_Double		(int nId, t_cstring s, t_double d, int nOffset)
{
	static char str[1024];

	sprintf(str, "%6f", d);
	 setCString_CString		(nId, s, str, nOffset);
}

void 		memory_variable::setCString_Double		(int nId, t_double d, t_cstring s, int nOffset)
{
	static char str[1024];

	sprintf(str, "%6f", d);
	 setCString_CString		(nId, str, s, nOffset);
}

void 		memory_variable::setCString_Currency		(int nId, t_cstring s, t_currency n, int nOffset)
{
  /*
	static char str[1024];

  sprintf(str, "%s", n.toCString());*/
	 setCString_CString		(nId, s, n.toCString(), nOffset);
}

void 		memory_variable::setCString_Currency		(int nId, t_currency n, t_cstring s, int nOffset)
{
  /*
	static char str[1024];

  sprintf(str, "%s", n.toString());*/
	 setCString_CString		(nId, n.toCString(), s, nOffset);
}

void 		memory_variable::setCString_Date		(int nId, t_cstring s, t_date n, int nOffset)
{
  /*
	static char str[1024];

  sprintf(str, "%s", n.toString());*/
	 setCString_CString		(nId, s, n.toCString(), nOffset);
}

void 		memory_variable::setCString_Date		(int nId, t_date n, t_cstring s, int nOffset)
{
  /*
	static char str[1024];

  sprintf(str, "%s", n.toString());*/
	 setCString_CString		(nId, n.toCString(), s, nOffset);
}

void 		memory_variable::setCString_QString		(int nId, t_cstring s, t_qstring s2, int nOffset)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){

		char **ac = 0;
    

    ac = (char **) (v->struct_ + nOffset);

		
    {
			if (!checkOffset(v, nOffset, sizeof(char))) return ;

		  int nLen = strlen(s);
		  int nLen2 = s2->length();//strlen(s2);
		  if (*ac == 0) *ac = (char *) malloc(nLen + nLen2 + 1);
		  else *ac = (char *) realloc(*ac, nLen + nLen2 + 1);

			if (*ac == 0){ memory_variableError(utility::con(utility::ident(v->acModule, v->acSub, v->acName), " variable allocation failed")); return ;}

			memcpy(*ac, s, nLen);
      QByteArray a = s2->toLocal8Bit();
			memcpy(*ac + nLen, a.data(), nLen2);
			memset(*ac + nLen + nLen2, 0, 1);
			
			return ;
		}
		//memory_variableError(utility::con(utility::ident(v->acModule, v->acSub, v->acName), " has wrong datatype"));
	}
	return ;
}
void 		memory_variable::setCString_CString		(int nId, t_cstring s, t_cstring s2, int nOffset)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){


		char **ac = 0;
    

    ac = (char **) (v->struct_ + nOffset);

		
    {
			if (!checkOffset(v, nOffset, sizeof(char))) return ;

		  int nLen = strlen(s);
		  int nLen2 = strlen(s2);
		  if (*ac == 0) *ac = (char *) malloc(nLen + nLen2 + 1);
		  else *ac = (char *) realloc(*ac, nLen + nLen2 + 1);

			if (*ac == 0){ memory_variableError(utility::con(utility::ident(v->acModule, v->acSub, v->acName), " variable allocation failed")); return ;}

			memcpy(*ac, s, nLen);
			memcpy(*ac + nLen, s2, nLen2);
			memset(*ac + nLen + nLen2, 0, 1);
			
			return ;
		}
		//memory_variableError(utility::con(utility::ident(v->acModule, v->acSub, v->acName), " has wrong datatype"));
	}
	return ;
}
void 		memory_variable::setWString		(int nId, t_cstring s, int nOffset, int nStringLen)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){

		char **ac = 0;

    ac = (char **) (v->struct_ + nOffset);
		
    {
			if (!checkOffset(v, nOffset, sizeof(char))) return ;

      if (*ac == 0) *ac = (char *) malloc(nStringLen + 2);
		  else *ac = (char *) realloc(*ac, nStringLen + 2);

			if (*ac == 0){ memory_variableError(utility::con(utility::ident(v->acModule, v->acSub, v->acName), " variable allocation failed")); return ;}

			memcpy(*ac, s, nStringLen);
			memset(*ac + nStringLen, 0, 2);
			
			return ;
		}
		//memory_variableError(utility::con(utility::ident(v->acModule, v->acSub, v->acName), " has wrong datatype"));
	}
	return ;
}























void 		memory_variable::setCString		(int nId, t_cstring s, int nOffset, int nStringLen)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){

		char **ac = 0;
    

    ac = (char **) (v->struct_ + nOffset);

		
    {
      
      
      {
			  if (!checkOffset(v, nOffset, sizeof(t_cstring))) return ;

		    int nLen = strlen(s);
		    //int nLen2 = strlen(s2);
		    if (*ac == 0) *ac = (char *) malloc(nLen + 1);
		    else *ac = (char *) realloc(*ac, nLen + 1);

			  if (*ac == 0){ memory_variableError(utility::con(utility::ident(v->acModule, v->acSub, v->acName), " variable allocation failed")); return ;}

			  memcpy(*ac, s, nLen);
			  memset(*ac + nLen, 0, 1);
     
      }


			
			return ;
		}
		//memory_variableError(utility::con(utility::ident(v->acModule, v->acSub, v->acName), " has wrong datatype"));
	}
	return ;
}






















void 		memory_variable::setLQString_Boolean		(int nId, t_qstring s, t_boolean c, int nOffset, int nLStringLen)
{
  /*
	static char str[1024];

  sprintf(str, "%s", c ? "TRUE" : "FALSE");*/
	 setLQString_QString		(nId, s, &QString("%1").arg(c ? "TRUE" : "FALSE"), nOffset, nLStringLen);
}

void 		memory_variable::setLQString_Byte		(int nId, t_qstring s, t_byte n, int nOffset, int nLStringLen)
{
  /*
	static char str[1024];

	sprintf(str, "%d", (t_integer) n);*/
	 setLQString_QString		(nId, s, &QString("%1").arg(n), nOffset, nLStringLen);
}

void 		memory_variable::setLQString_Short		(int nId, t_qstring s, t_short n, int nOffset, int nLStringLen)
{
  /*
	static char str[1024];

	sprintf(str, "%d", n); */
	 setLQString_QString		(nId, s, &QString("%1").arg(n), nOffset, nLStringLen);
}

void 		memory_variable::setLQString_Integer		(int nId, t_qstring s, t_integer n, int nOffset, int nLStringLen)
{
  /*
	static char str[1024];

	sprintf(str, "%d", n);*/
	 setLQString_QString		(nId, s, &QString("%1").arg(n), nOffset, nLStringLen);
}

void 		memory_variable::setLQString_Long		(int nId, t_qstring s, t_long l, int nOffset, int nLStringLen)
{
	 setLQString_QString		(nId, s, &QString("%1").arg(l), nOffset, nLStringLen);
}

void 		memory_variable::setLQString_Single		(int nId, t_qstring s, t_single f, int nOffset, int nLStringLen)
{

	 setLQString_QString		(nId, s, &QString("%1").arg(f), nOffset, nLStringLen);
}

void 		memory_variable::setLQString_Double		(int nId, t_qstring s, t_double d, int nOffset, int nLStringLen)
{

	 setLQString_QString		(nId, s, &QString("%1").arg(d), nOffset, nLStringLen);
}

void 		memory_variable::setLQString_QString		(int nId, t_qstring s, t_qstring s2, int nOffset, int _nLen)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){
		char *ac = 0;

    ac = (char *) (v->struct_ + nOffset);
		
    {

      QByteArray a; a = s->toUtf8();
      QByteArray a2; a2 = s2->toUtf8();

      int nLen = a.size();
      int nLen2 = a2.size();

      // check len copy
      if (_nLen > nLen + 1){
        _nLen = _nLen - nLen;            

        if (_nLen > nLen2 + 1){
          _nLen = _nLen - nLen2;        

        } else {
          nLen2 = _nLen - 1;          
        }

      } else {
        if (_nLen > 0){
          nLen = _nLen - 1;
          nLen2 = 0;
        } else {
          nLen2 = 0;
        }
      }

      memcpy(ac, a.data(), nLen);
	    memcpy(ac + nLen, a2.data(), nLen2);
	    memset(ac + nLen + nLen2, 0, 1);
    }
  }
			
  
	return ;
}

void 		memory_variable::setLQString_CString		(int nId, t_qstring s, t_cstring s2, int nOffset, int _nLen)
{
  /*
	variable *v = findMemory_variable	(nId);
	if (v != 0){
		char *ac = 0;

    ac = (char *) (v->struct_ + nOffset);
		
    {
			if (!checkOffset(v, nOffset, sizeof(const char *))) return false;

		  int nLen = strlen(s);
		  int nLen2 = strlen(s2);

      // check len copy
      if (_nLen > nLen + 1){
        _nLen = _nLen - nLen;            

        if (_nLen > nLen2 + 1){
          _nLen = _nLen - nLen2;        

        } else {
          nLen2 = _nLen - 1;          
        }

      } else {
        if (_nLen > 0){
          nLen = _nLen - 1;
          nLen2 = 0;
        } else {
          nLen2 = 0;
        }
      }

      // HINT LSTRING-Len ist immer um eins kürzer
			memcpy(ac, s, nLen);
			memcpy(ac + nLen, s2, nLen2);
			memset(ac + nLen + nLen2, 0, 1);
			
			return true;
		}
		//memory_variableError(utility::con(utility::ident(v->acModule, v->acSub, v->acName), " has wrong datatype"));
	}
  */
	return ;
}

void 		memory_variable::setLQString		(int nId, t_qstring s, int nOffset, int nLStringLen)
{
   setLQString_QString(nId, s, &kbNullQString, nOffset, nLStringLen);
}

void 		memory_variable::setRQString_QString		(int nId, t_qstring s, t_qstring s2, int nOffset, int _nLen)
{
  /*
	variable *v = findMemory_variable	(nId);
	if (v != 0){
		char *ac = 0;

    ac = (char *) (v->struct_ + nOffset);
		
    {
			if (!checkOffset(v, nOffset, sizeof(const char *))) return false;

		  int nLen = strlen(s);
		  int nLen2 = strlen(s2);

      // check len copy
      if (_nLen > nLen + 1){
        _nLen = _nLen - nLen;            

        if (_nLen > nLen2 + 1){
          _nLen = _nLen - nLen2;        

        } else {
          nLen2 = _nLen - 1;          
        }

      } else {
        if (_nLen > 0){
          nLen = _nLen - 1;
          nLen2 = 0;
        } else {
          nLen2 = 0;
        }
      }

      // HINT LSTRING-Len ist immer um eins kürzer
			memcpy(ac, s, nLen);
			memcpy(ac + nLen, s2, nLen2);
			memset(ac + nLen + nLen2, 0, 1);
			
			return true;
		}
		//memory_variableError(utility::con(utility::ident(v->acModule, v->acSub, v->acName), " has wrong datatype"));
	}
  */
	return ;
}

void 		memory_variable::setRQString_CString		(int nId, t_qstring s, t_cstring s2, int nOffset, int _nLen)
{
  /*
	variable *v = findMemory_variable	(nId);
	if (v != 0){
		char *ac = 0;

    ac = (char *) (v->struct_ + nOffset);
		
    {
			if (!checkOffset(v, nOffset, sizeof(const char *))) return false;

		  int nLen = strlen(s);
		  int nLen2 = strlen(s2);

      // check len copy
      if (_nLen > nLen + 1){
        _nLen = _nLen - nLen;            

        if (_nLen > nLen2 + 1){
          _nLen = _nLen - nLen2;        

        } else {
          nLen2 = _nLen - 1;          
        }

      } else {
        if (_nLen > 0){
          nLen = _nLen - 1;
          nLen2 = 0;
        } else {
          nLen2 = 0;
        }
      }

      // HINT LSTRING-Len ist immer um eins kürzer
			memcpy(ac, s, nLen);
			memcpy(ac + nLen, s2, nLen2);
			memset(ac + nLen + nLen2, 0, 1);
			
			return true;
		}
		//memory_variableError(utility::con(utility::ident(v->acModule, v->acSub, v->acName), " has wrong datatype"));
	}
  */
	return ;
}

void 		memory_variable::setRQString		(int nId, t_qstring s, int nOffset, int nRStringLen)
{
   setRQString_QString(nId, s, &kbNullQString, nOffset, nRStringLen);
}



void 		memory_variable::setLCString_Boolean		(int nId, t_cstring s, t_boolean c, int nOffset, int nLStringLen)
{
	static char str[1024];

  sprintf(str, "%s", c ? "TRUE" : "FALSE");
	 setLCString_CString		(nId, s, str, nOffset, nLStringLen);
}

void 		memory_variable::setLCString_Byte		(int nId, t_cstring s, t_byte n, int nOffset, int nLStringLen)
{
	static char str[1024];

	sprintf(str, "%d", (t_integer) n);
	 setLCString_CString		(nId, s, str, nOffset, nLStringLen);
}

void 		memory_variable::setLCString_Short		(int nId, t_cstring s, t_short n, int nOffset, int nLStringLen)
{
	static char str[1024];

	sprintf(str, "%d", n); 
	 setLCString_CString		(nId, s, str, nOffset, nLStringLen);
}

void 		memory_variable::setLCString_Integer		(int nId, t_cstring s, t_integer n, int nOffset, int nLStringLen)
{
	static char str[1024];

	sprintf(str, "%d", n);
	 setLCString_CString		(nId, s, str, nOffset, nLStringLen);
}

void 		memory_variable::setLCString_Long		(int nId, t_cstring s, t_long l, int nOffset, int nLStringLen)
{
	static char str[1024];

#ifdef WINDOWS
	sprintf(str, "%I64d", l); // HIDE
#else
	sprintf(str, "%lld", l);
#endif
	 setLCString_CString		(nId, s, str, nOffset, nLStringLen);
}

void 		memory_variable::setLCString_Single		(int nId, t_cstring s, t_single f, int nOffset, int nLStringLen)
{
	static char str[1024];

	sprintf(str, "%6f", f);
	 setLCString_CString		(nId, s, str, nOffset, nLStringLen);
}

void 		memory_variable::setLCString_Double		(int nId, t_cstring s, t_double d, int nOffset, int nLStringLen)
{
	static char str[1024];

	sprintf(str, "%6f", d);
	 setLCString_CString		(nId, s, str, nOffset, nLStringLen);
}

void 		memory_variable::setLCString_CString		(int nId, t_cstring s, t_cstring s2, int nOffset, int _nLen)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){
		char *ac = 0;

    ac = (char *) (v->struct_ + nOffset);
		
    {
			if (!checkOffset(v, nOffset, sizeof(char))) return ;

		  int nLen = strlen(s);
		  int nLen2 = strlen(s2);

      // check len copy
      if (_nLen > nLen + 1){
        _nLen = _nLen - nLen;            

        if (_nLen > nLen2 + 1){
          _nLen = _nLen - nLen2;        

        } else {
          nLen2 = _nLen - 1;          
        }

      } else {
        if (_nLen > 0){
          nLen = _nLen - 1;
          nLen2 = 0;
        } else {
          nLen2 = 0;
        }
      }

      // HINT LSTRING-Len ist immer um eins kürzer
			memcpy(ac, s, nLen);
			memcpy(ac + nLen, s2, nLen2);
			memset(ac + nLen + nLen2, 0, 1);
			
			return ;
		}
		//memory_variableError(utility::con(utility::ident(v->acModule, v->acSub, v->acName), " has wrong datatype"));
	}
	return ;
}

void 		memory_variable::setLCString_QString		(int nId, t_cstring s, t_qstring s2, int nOffset, int _nLen)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){
		char *ac = 0;

    ac = (char *) (v->struct_ + nOffset);
		
    {
			if (!checkOffset(v, nOffset, sizeof(char))) return ;

		  int nLen = strlen(s);
      QByteArray a = s2->toLocal8Bit();
		  int nLen2 = a.size();

      // check len copy
      if (_nLen > nLen + 1){
        _nLen = _nLen - nLen;            

        if (_nLen > nLen2 + 1){
          _nLen = _nLen - nLen2;        

        } else {
          nLen2 = _nLen - 1;          
        }

      } else {
        if (_nLen > 0){
          nLen = _nLen - 1;
          nLen2 = 0;
        } else {
          nLen2 = 0;
        }
      }

      // HINT LSTRING-Len ist immer um eins kürzer
			memcpy(ac, s, nLen);
			memcpy(ac + nLen, a.data(), nLen2);
			memset(ac + nLen + nLen2, 0, 1);
			
			return ;
		}
		//memory_variableError(utility::con(utility::ident(v->acModule, v->acSub, v->acName), " has wrong datatype"));
	}
	return ;
}

void 		memory_variable::setLCString		(int nId, t_cstring s, int nOffset, int nLStringLen)
{
   setLCString_CString(nId, s, "", nOffset, nLStringLen);
}

void 		memory_variable::setRCString_CString		(int nId, t_cstring s, t_cstring s2, int nOffset, int _nLen)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){
		char *ac = 0;

    ac = (char *) (v->struct_ + nOffset);
		
    {
			if (!checkOffset(v, nOffset, sizeof(char))) return ;

		  int nLen = strlen(s);
		  int nLen2 = strlen(s2);

      // check len copy
      if (_nLen > nLen + 1){
        _nLen = _nLen - nLen;            

        if (_nLen > nLen2 + 1){
          _nLen = _nLen - nLen2;        

        } else {
          nLen2 = _nLen - 1;          
        }

      } else {
        if (_nLen > 0){
          nLen = _nLen - 1;
          nLen2 = 0;
        } else {
          nLen2 = 0;
        }
      }

      // HINT LSTRING-Len ist immer um eins kürzer
			memcpy(ac, s, nLen);
			memcpy(ac + nLen, s2, nLen2);
			memset(ac + nLen + nLen2, 0, 1);
			
			return ;
		}
		//memory_variableError(utility::con(utility::ident(v->acModule, v->acSub, v->acName), " has wrong datatype"));
	}
	return ;
}

void 		memory_variable::setRCString_QString		(int nId, t_cstring s, t_qstring s2, int nOffset, int _nLen)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){
		char *ac = 0;

    ac = (char *) (v->struct_ + nOffset);
		
    {
			if (!checkOffset(v, nOffset, sizeof(char))) return ;

		  int nLen = strlen(s);
		  int nLen2 = s2->length();//strlen(s2);

      // check len copy
      if (_nLen > nLen + 1){
        _nLen = _nLen - nLen;            

        if (_nLen > nLen2 + 1){
          _nLen = _nLen - nLen2;        

        } else {
          nLen2 = _nLen - 1;          
        }

      } else {
        if (_nLen > 0){
          nLen = _nLen - 1;
          nLen2 = 0;
        } else {
          nLen2 = 0;
        }
      }

      // HINT LSTRING-Len ist immer um eins kürzer
			memcpy(ac, s, nLen);
      QByteArray a = s2->toLocal8Bit();
			memcpy(ac + nLen, a.data(), nLen2);
			memset(ac + nLen + nLen2, 0, 1);
			
			return ;
		}
		//memory_variableError(utility::con(utility::ident(v->acModule, v->acSub, v->acName), " has wrong datatype"));
	}
	return ;
}

void 		memory_variable::setRCString		(int nId, t_cstring s, int nOffset, int nRStringLen)
{
   setRCString_CString(nId, s, "", nOffset, nRStringLen);
}

void 		memory_variable::setReferenceVariablePool		(int nId, memory_variable *_v)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){
		v->ReferenceVariablePool = _v;
		return ;
	}
	return ;
}

void 		memory_variable::setReferenceOffset		(int nId, int nOffset)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){
		v->nReferenceOffset = nOffset;
		return ;
	}
	return ;
}

void 		memory_variable::setReferenceScope		(int nId, t_scope n)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){
		v->ReferenceScope = n;
		return ;
	}
	return ;
}

void 		memory_variable::setReferenceArray		(int nId, t_array *n)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){
    n->copyArray(&v->ReferenceArray);
		return ;
	}
	return ;
}

void 		memory_variable::setReferenceId		(int nId, int n)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){
		v->nReferenceId = n;
		return ;
	}
	return ;
}

void 		memory_variable::setDouble		(int nId, t_double d, int nOffset)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){
    
    {
			if (!checkOffset(v, nOffset, sizeof(t_double))) return ;

     *(t_double *)(v->struct_ + nOffset) = d;

			return ;
		}
		//memory_variableError(utility::con(utility::ident(v->acModule, v->acSub, v->acName), " has wrong datatype"));
	}
	return ;
}
/*
bool 		memory_variable::setDouble		(const char *acModule, const char *acSub, const char *acName, t_double d, int nOffset)
{
	return setDouble		(getId(acModule, acSub, acName), d, nOffset);
}
*/
void 		memory_variable::setSingle		(int nId, t_single d, int nOffset)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){

    {
			if (!checkOffset(v, nOffset, sizeof(t_single))) return ;

      *(t_single *)(v->struct_ + nOffset) = d;

			return ;
		}
		//memory_variableError(utility::con(utility::ident(v->acModule, v->acSub, v->acName), " has wrong datatype"));
	}
	return ;
}
/*
bool 		memory_variable::setSingle		(const char *acModule, const char *acSub, const char *acName, t_single f, int nOffset)
{
	return setSingle		(getId(acModule, acSub, acName), f, nOffset);
}
*/
void 		memory_variable::setInteger	(int nId, t_integer d, int nOffset)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){
    
    {
			if (!checkOffset(v, nOffset, sizeof(t_integer))) return ; 

      *(t_integer *)(v->struct_ + nOffset) = d;
     	
			return ;
		}
		//memory_variableError(utility::con(utility::ident(v->acModule, v->acSub, v->acName), " has wrong datatype"));
	}
	return ;
}

/*
bool 		memory_variable::setUInt64	(const char *acModule, const char *acSub, const char *acName, t_uint64 n, int nOffset)
{
	return setUInt64	(getId(acModule, acSub, acName), n, nOffset);
}
*/

void 		memory_variable::setVariantType	(int nId, t_pcode c)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){
    v->nVariantType = c;
		return ;
	}
	return ;
}

void 		memory_variable::setVariant	(int nId, t_variant n, int nOffset)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){
    
    {
			if (!checkOffset(v, nOffset, sizeof(t_variant))) return ;

      *(t_variant *)(v->struct_ + nOffset) = n;
     	
			return ;
		}
		//memory_variableError(utility::con(utility::ident(v->acModule, v->acSub, v->acName), " has wrong datatype"));
	}
	return ;
}

void 		memory_variable::setVariant_Boolean	(int nId, t_boolean n, int nOffset)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){
    
    {
			if (!checkOffset(v, nOffset, sizeof(t_variant))) return ;

      t_variant *old = (t_variant *) (v->struct_ + nOffset);
      if (old->nType == pcode__QSTRING) old->string_ = "";
      else if (old->nType == pcode__CSTRING && old->cstring_ && old->cstring_ != "") free(old->cstring_);

      old->nType = pcode__BOOLEAN;
      old->boolean_ = n;

      v->nVariantType = pcode__BOOLEAN;
			return ;
		}
		//memory_variableError(utility::con(utility::ident(v->acModule, v->acSub, v->acName), " has wrong datatype"));
	}
	return ;
}

void 		memory_variable::setVariant_QString	(int nId, t_qstring n, int nOffset)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){
    
    {
			if (!checkOffset(v, nOffset, sizeof(t_variant))) return ;

      t_variant *old = (t_variant *) (v->struct_ + nOffset);
      if (old->nType == pcode__QSTRING) old->string_ = "";
      else if (old->nType == pcode__CSTRING && old->cstring_ && old->cstring_ != "") free(old->cstring_);

      old->nType = pcode__QSTRING;

		  int nLen = n->length();
      QString s; memcpy(&old->string_, &s, sizeof(QString)); // needed to make string_ working

      old->string_ = *n;
		  old->qstring_ = &old->string_;

      v->nVariantType = pcode__QSTRING;
			return ;

		}
		//memory_variableError(utility::con(utility::ident(v->acModule, v->acSub, v->acName), " has wrong datatype"));
	}
	return ;
}

void 		memory_variable::setVariant_CString	(int nId, t_cstring n, int nOffset)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){
    
    {
			if (!checkOffset(v, nOffset, sizeof(t_variant))) return ;


      t_variant *old = (t_variant *) (v->struct_ + nOffset);
      if (old->nType == pcode__QSTRING) old->string_ = "";
      else if (old->nType == pcode__CSTRING && old->cstring_ && old->cstring_ != "") free(old->cstring_);

      old->nType = pcode__CSTRING;

		  int nLen = strlen(n);
		  char *ac = (char *) malloc(nLen + 1);		  

			if (ac == 0){ memory_variableError(utility::con(utility::ident(v->acModule, v->acSub, v->acName), " variable allocation failed")); return ;}

			memcpy(ac, n, nLen);
			memset(ac + nLen, 0, 1);

      old->cstring_ = ac;

      v->nVariantType = pcode__CSTRING;
			return ;

		}
		//memory_variableError(utility::con(utility::ident(v->acModule, v->acSub, v->acName), " has wrong datatype"));
	}
	return ;
}

void 		memory_variable::setVariant_Byte	(int nId, t_byte n, int nOffset)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){
    
    {
			if (!checkOffset(v, nOffset, sizeof(t_variant))) return ;

      t_variant *old = (t_variant *) (v->struct_ + nOffset);
      if (old->nType == pcode__QSTRING) old->string_ = "";
      else if (old->nType == pcode__CSTRING && old->cstring_ && old->cstring_ != "") free(old->cstring_);

      old->nType = pcode__BYTE;
      old->byte_ = n;

      v->nVariantType = pcode__BYTE;
			return ;
		}
		//memory_variableError(utility::con(utility::ident(v->acModule, v->acSub, v->acName), " has wrong datatype"));
	}
	return ;
}

void 		memory_variable::setVariant_Short	(int nId, t_short n, int nOffset)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){
    
    {
			if (!checkOffset(v, nOffset, sizeof(t_variant))) return ;

      t_variant *old = (t_variant *) (v->struct_ + nOffset);
      if (old->nType == pcode__QSTRING) old->string_ = "";
      else if (old->nType == pcode__CSTRING && old->cstring_ && old->cstring_ != "") free(old->cstring_);

      old->nType = pcode__SHORT;
      old->short_ = n;
      
      v->nVariantType = pcode__SHORT;
			return ;
		}
		//memory_variableError(utility::con(utility::ident(v->acModule, v->acSub, v->acName), " has wrong datatype"));
	}
	return ;
}

void 		memory_variable::setVariant_Integer	(int nId, t_integer n, int nOffset)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){
    
    {
			if (!checkOffset(v, nOffset, sizeof(t_variant))) return ;

      t_variant *old = (t_variant *) (v->struct_ + nOffset);
      if (old->nType == pcode__QSTRING) old->string_ = "";
      else if (old->nType == pcode__CSTRING && old->cstring_ && old->cstring_ != "") free(old->cstring_);

      old->nType = pcode__INTEGER;
      old->integer_ = n;
      
      v->nVariantType = pcode__INTEGER;
			return ;
		}
		//memory_variableError(utility::con(utility::ident(v->acModule, v->acSub, v->acName), " has wrong datatype"));
	}
	return ;
}

void 		memory_variable::setVariant_Long	(int nId, t_long n, int nOffset)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){
    
    {
			if (!checkOffset(v, nOffset, sizeof(t_variant))) return ;

      t_variant *old = (t_variant *) (v->struct_ + nOffset);
      if (old->nType == pcode__QSTRING) old->string_ = "";
      else if (old->nType == pcode__CSTRING && old->cstring_ && old->cstring_ != "") free(old->cstring_);

      old->nType = pcode__LONG;
      old->long_ = n;
      
      v->nVariantType = pcode__LONG;
			return ;
		}
		//memory_variableError(utility::con(utility::ident(v->acModule, v->acSub, v->acName), " has wrong datatype"));
	}
	return ;
}

void 		memory_variable::setVariant_Single	(int nId, t_single n, int nOffset)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){
    
    {
			if (!checkOffset(v, nOffset, sizeof(t_variant))) return ;

      t_variant *old = (t_variant *) (v->struct_ + nOffset);
      if (old->nType == pcode__QSTRING) old->string_ = "";
      else if (old->nType == pcode__CSTRING && old->cstring_ && old->cstring_ != "") free(old->cstring_);

      old->nType = pcode__SINGLE;
      old->single_ = n;
      
      v->nVariantType = pcode__SINGLE;
			return ;
		}
		//memory_variableError(utility::con(utility::ident(v->acModule, v->acSub, v->acName), " has wrong datatype"));
	}
	return ;
}

void 		memory_variable::setVariant_Double	(int nId, t_double n, int nOffset)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){
    
    {
			if (!checkOffset(v, nOffset, sizeof(t_variant))) return ;

      t_variant *old = (t_variant *) (v->struct_ + nOffset);
      if (old->nType == pcode__QSTRING) old->string_ = "";
      else if (old->nType == pcode__CSTRING && old->cstring_ && old->cstring_ != "") free(old->cstring_);

      old->nType = pcode__DOUBLE;
      old->double_ = n;
      
      v->nVariantType = pcode__DOUBLE;
			return ;
		}
		//memory_variableError(utility::con(utility::ident(v->acModule, v->acSub, v->acName), " has wrong datatype"));
	}
	return ;
}

void 		memory_variable::setVariant_Currency	(int nId, t_currency n, int nOffset)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){
    
    {
			if (!checkOffset(v, nOffset, sizeof(t_variant))) return ;

      t_variant *old = (t_variant *) (v->struct_ + nOffset);
      if (old->nType == pcode__QSTRING) old->string_ = "";
      else if (old->nType == pcode__CSTRING && old->cstring_ && old->cstring_ != "") free(old->cstring_);

      old->nType = pcode__CURRENCY;
      old->currency_ = n;
      
      v->nVariantType = pcode__CURRENCY;
			return ;
		}
		//memory_variableError(utility::con(utility::ident(v->acModule, v->acSub, v->acName), " has wrong datatype"));
	}
	return ;
}

void 		memory_variable::setVariant_Date	(int nId, t_date n, int nOffset)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){
    
    {
			if (!checkOffset(v, nOffset, sizeof(t_variant))) return;
      t_variant *old = (t_variant *) (v->struct_ + nOffset);
      if (old->nType == pcode__QSTRING) old->string_ = "";
      else if (old->nType == pcode__CSTRING && old->cstring_ && old->cstring_ != "") free(old->cstring_);

      old->nType = pcode__DATE;
      old->date_ = n;

      v->nVariantType = pcode__DATE;
			return ;
		}
		//memory_variableError(utility::con(utility::ident(v->acModule, v->acSub, v->acName), " has wrong datatype"));
	}
	return ;
}

void 		memory_variable::setVariant_Object	(int nId, t_object n, int nOffset)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){
    
    {
			if (!checkOffset(v, nOffset, sizeof(t_variant))) return ;
      t_variant *old = (t_variant *) (v->struct_ + nOffset);
      if (old->nType == pcode__QSTRING) old->string_ = "";
      else if (old->nType == pcode__CSTRING && old->cstring_ && old->cstring_ != "") free(old->cstring_);

      old->nType = pcode__OBJECT;
      old->object_ = n;
      
      v->nVariantType = pcode__OBJECT;
			return ;
		}
		//memory_variableError(utility::con(utility::ident(v->acModule, v->acSub, v->acName), " has wrong datatype"));
	}
	return ;
}

void 		memory_variable::setVariant_Pointer	(int nId, t_pointer n, int nType, int nOffset)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){

    {
			if (!checkOffset(v, nOffset, sizeof(t_variant))) return ;

      t_variant *old = (t_variant *) (v->struct_ + nOffset);
      if (old->nType == pcode__QSTRING) old->string_ = "";
      else if (old->nType == pcode__CSTRING && old->cstring_ && old->cstring_ != "") free(old->cstring_);

      old->nType = nType;
      old->pointer_ = n;

     v->nVariantType = nType;

			return ;
		}
		//memory_variableError(utility::con(utility::ident(v->acModule, v->acSub, v->acName), " has wrong datatype"));
	}
	return ;
}

void 		memory_variable::setVariant_Empty	(int nId, t_pcode n, int nOffset)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){
    
    {
			if (!checkOffset(v, nOffset, sizeof(t_variant))) return ;
      t_variant *old = (t_variant *) (v->struct_ + nOffset);
      if (old->nType == pcode__QSTRING) old->string_ = "";
      else if (old->nType == pcode__CSTRING && old->cstring_ && old->cstring_ != "") free(old->cstring_);

      old->nType = pcode__EMPTY;

      v->nVariantType = pcode__EMPTY;
			return ;
		}
		//memory_variableError(utility::con(utility::ident(v->acModule, v->acSub, v->acName), " has wrong datatype"));
	}
	return ;
}

void 		memory_variable::setVariant_Error(int nId, t_pcode n, int nOffset)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){
    
    {
			if (!checkOffset(v, nOffset, sizeof(t_variant))) return ;

      t_variant *old = (t_variant *) (v->struct_ + nOffset);
      if (old->nType == pcode__QSTRING) old->string_ = "";
      else if (old->nType == pcode__CSTRING && old->cstring_ && old->cstring_ != "") free(old->cstring_);

      old->nType = pcode__ERROR;
      
      v->nVariantType = pcode__ERROR;
			return ;
		}
		//memory_variableError(utility::con(utility::ident(v->acModule, v->acSub, v->acName), " has wrong datatype"));
	}
	return ;
}

void 		memory_variable::setShort	(int nId, t_short d, int nOffset)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){
    
    {
			if (!checkOffset(v, nOffset, sizeof(t_short))) return ;

      *(t_short *)(v->struct_ + nOffset) = d;
			return ;
		}
		//memory_variableError(utility::con(utility::ident(v->acModule, v->acSub, v->acName), " has wrong datatype"));
	}
	return ;
}
/*
bool 		memory_variable::setShort	(const char *acModule, const char *acSub, const char *acName, t_short n, int nOffset)
{
	return setShort	(getId(acModule, acSub, acName), n, nOffset);
}
*/
void 		memory_variable::setLong			(int nId, t_long d, int nOffset)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){
    
    {
			if (!checkOffset(v, nOffset, sizeof(t_long))) return ;

      *(t_long *)(v->struct_ + nOffset) = d;
			return ;
		}
		//memory_variableError(utility::con(utility::ident(v->acModule, v->acSub, v->acName), " has wrong datatype"));
	}
	return ;
}
/*
bool 		memory_variable::setLong			(const char *acModule, const char *acSub, const char *acName, t_long l, int nOffset)
{
	return		setLong			(getId(acModule, acSub, acName), l, nOffset);
}
*/

void		memory_variable::setArray	(int nId, t_array *a)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){

	  v->a.count = 0;

	  if (a){
		  v->a.count = a->count;
		  v->a.type = pcode__VARIANT;
		  for (int i = 0; i < a->count; i++){
       v->a.idx[i] = a->idx[i];
       v->a.idxTo[i] = a->idxTo[i];      
      }
	  }

    v->nVariantType = pcode__ARRAY;

		return ;
	}
	return ;
}

void		memory_variable::setIsMissing	(int nId, bool b)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){   

    v->bIsMissing = b;
		return ;
	}
	return ;
}

void		memory_variable::setBindingParentClassPointer	(t_pointer p)
{

 vBindingParentClassPointer = p;
 return ;
}

void		memory_variable::setBindingParentClassType	(int n)
{

 nBindingParentClassType = n;
 return ;
}

/*
bool		memory_variable::setBindingParentClassPointer	(int nId, t_pointer p)
{
 variable *v = findMemory_variable	(nId);
 if (v != 0){   
   vBindingParentClassPointer = p;
   return true;
 } 
 return false;
}

bool		memory_variable::setBindingParentClassType	(int nId, int n)
{
 variable *v = findMemory_variable	(nId);
 if (v != 0){   
   nBindingParentClassType = n;
   return true;
 } 
 return false;
}
*/

void		memory_variable::setBoolean	(int nId, t_boolean d, int nOffset)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){
    
    {
			if (!checkOffset(v, nOffset, sizeof(t_boolean))) return ;

      *(t_boolean *)(v->struct_ + nOffset) = d;
			return ;
		}
		//memory_variableError(utility::con(utility::ident(v->acModule, v->acSub, v->acName), " has wrong datatype"));
	}
	return ;
}
/*
bool		memory_variable::setBoolean	(const char *acModule, const char *acSub, const char *acName, t_boolean c, int nOffset)
{
	return setBoolean	(getId(acModule, acSub, acName), c, nOffset);
}
*/
void		memory_variable::setByte	(int nId, t_byte d, int nOffset)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){

    {
			if (!checkOffset(v, nOffset, sizeof(t_byte))) return ;

      *(t_byte *)(v->struct_ + nOffset) = d;
			return ;
		}
		//memory_variableError(utility::con(utility::ident(v->acModule, v->acSub, v->acName), " has wrong datatype"));
	}
	return ;
}
/*
bool		memory_variable::setByte	(const char *acModule, const char *acSub, const char *acName, t_byte c, int nOffset)
{
	return setByte	(getId(acModule, acSub, acName), c, nOffset);
}
*/
void	memory_variable::setStruct		(int nId, void *p, int nOffset, int nSize)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){
		memcpy((char *) (v->struct_ + nOffset), p, nSize);
		return ;
	}
	return ;	
}

void	memory_variable::setPointer		(int nId, void *p, int nOffset)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){
     t_integer n = (t_integer) p;
  		memcpy(v->struct_ + nOffset, &n, sizeof(n));

		return ;
	}
	return ;	
}

void *	memory_variable::copyPointer		(int nId, void *p, int nOffset, int nSize)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){
   
  		memcpy(v->struct2_ + nOffset, p, nSize);
  		
      return v->struct2_ + nOffset;

	}
	return 0;	
}

void	memory_variable::setObject		(int nId, void *p, int nOffset)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){

      t_integer n = (t_integer) p;
  		memcpy(v->struct_ + nOffset, &n, sizeof(n));
    
     return ;
	}
	return ;	
}

void * memory_variable::getAddress(int nId, int nOffset, int nType)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){
		return (v->struct_ + nOffset); 

    
  }

	return 0;	
}

t_currency	memory_variable::getCurrency		(int nId, int nOffset)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){

    {
			if (!checkOffset(v, nOffset, sizeof(t_currency))) return t_currency();

     return *(t_currency *) (v->struct_ + nOffset);
     
		}
		//memory_variableError(utility::con(utility::ident(v->acModule, v->acSub, v->acName), " has wrong datatype"));
    
  }
	return t_currency();
}

t_date	memory_variable::getDate		(int nId, int nOffset)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){

    {
			if (!checkOffset(v, nOffset, sizeof(t_date))) return false;

      return *(t_date *) (v->struct_ + nOffset);
     
      
		}
		//memory_variableError(utility::con(utility::ident(v->acModule, v->acSub, v->acName), " has wrong datatype"));
    
  }
	return 0;	
}

/*
t_date memory_variable::getDate		(int nId, int nOffset)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){
		if (nOffset > 0){
//			return ((date) (v->struct_) + nOffset);
		} else {
			return v->date_;
		}
	}
	return 0;	
}
*/

memory_variable* memory_variable::getReferenceVariablePool		(int nId)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){
		return v->ReferenceVariablePool;	
	}
	return 0;	
}

int memory_variable::getReferenceOffset		(int nId)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){
		return v->nReferenceOffset;	
	}
	return 0;	
}

t_array *memory_variable::getReferenceArray		(int nId)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){
		return &(v->ReferenceArray);	
	}
	return 0;	
}

t_scope memory_variable::getReferenceScope		(int nId)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){
		return v->ReferenceScope;	
	}
	return global;	
}

int memory_variable::getReferenceId		(int nId)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){
		return v->nReferenceId;	
	}
	return 0;	
}

bool memory_variable::isReference		(int nId)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){
		return v->bReference;	
	}
	return false;	
}

/*
t_pointer memory_variable::getBindingParentClassPointer		(int nId)
{
 	variable *v = findMemory_variable	(nId);
	if (v != 0){
    return v->vBindingParentClassPointer;	
  }
  return 0;
}

int memory_variable::getBindingParentClassType		(int nId)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){
    return v->nBindingParentClassType;	
  } 
  return 0;
}
*/



void	memory_variable::setCurrency		(int nId, t_long d, int nOffset)
{
  t_currency c(d, 0);
  return setCurrency(nId, c, nOffset);
}

void	memory_variable::setCurrencyDouble		(int nId, t_double d, int nOffset)
{
  t_currency c(d);
   setCurrency(nId, c, nOffset);
}

void	memory_variable::setCurrency		(int nId, t_currency c, int nOffset)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){

    {
			if (!checkOffset(v, nOffset, sizeof(t_currency))) return ;

      *(t_currency *)(v->struct_ + nOffset) = c;
			return ;
		}
//		memory_variableError(utility::con(utility::ident(v->acModule, v->acSub, v->acName), " has wrong datatype"));

	}
	return ;	
}

void	memory_variable::setDate		(int nId, t_date c, int nOffset)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){

    {
			if (!checkOffset(v, nOffset, sizeof(t_date))) return ;

      *(t_date *)(v->struct_ + nOffset) = c;
			return ;
		}
		//memory_variableError(utility::con(utility::ident(v->acModule, v->acSub, v->acName), " has wrong datatype"));

	}
	return ;	
}

/*
bool	memory_variable::setDate		(int nId, t_date d, int nOffset)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){
		if (nOffset > 0 ){
		//	memcpy(((char *) (v->struct_ + nOffset)), p, sizeof(p));
		} else {
			v->date_ = d;
		}
		return true;
	}
	return false;	
}
*/
void	*memory_variable::getStruct		(int nId, int nOffset)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){
		return ((char *) (v->struct_ + nOffset));
	}
	return 0;	
}

void	*memory_variable::getPointer		(int nId, int nOffset)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){

		t_integer n = 0;
   memcpy(&n, (v->struct_ + nOffset), sizeof(t_integer));
		return (void *) n;
	}
	return 0;	
}

void	*memory_variable::getPointerPointer		(int nId, int nOffset)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){
  
		return (void *) (v->struct_ + nOffset);
	}
	return 0;	
}

memory_variable	*memory_variable::getObject		(int nId, int nOffset)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){

		t_integer n = 0;
   memcpy(&n, (v->struct_ + nOffset), sizeof(t_integer));
		return (memory_variable *) n;
    
	}
	return 0;	
}

bool		memory_variable::first	()
{
  it = list_variable.begin();
	return it != list_variable.end();
}

bool		memory_variable::next	()
{
	++it;
	return it != list_variable.end();
}
/*
bool 		memory_variable::checkOffset	(variable *v, int nOffset, int nSize)
{
  if (nOffset + nSize > v->nStructSize){ memory_variableError(utility::con(utility::ident(v->acModule, v->acSub, v->acName), ": offset out of size of struct")); return false; }

	return true;
}
*/
// used to call destructors by interpreter
int memory_variable::getClassId()
{
  return nClassId;
}

// used to call destructors by interpreter
void memory_variable::setClassId(int nId)
{
  nClassId = nId;
}

QString memory_variable::toQString(int nId)
{
  QString s = "?";

  memory_variable *v = this;

  if (v->isMissing(nId)) return "isMissing";

  if (isReference(nId)){
    v = getReferenceVariablePool(nId);
    nId = getReferenceId(nId);   
  }

  if (v->isArray(nId)) return "Array()";
  if (v->isEmpty(nId)) return "Empty";
  

  int nType = v->type(nId);
  switch(nType){

    case pcode__BOOLEAN:
      {
        bool b = v->getBoolean(nId);
        s = b ? "True" : "False";
      }
      break;  

    //case pcode__QString:
    case pcode__QSTRING:
      {
        s = "\"";
        s += *v->getQString(nId);        
        s += "\"";        
      }
      break;  
    case pcode__CSTRING:
      {
        s = "\"";
        s += v->getCString(nId);        
        s += "\"";        
      }
      break;  

    case pcode__LQSTRING:
      {
        s = "\"";
        s += *v->getLQString(nId);        
        s += "\"";    
      }
      break;  

    case pcode__LCSTRING:
      {
        s = "\"";
        s += v->getLCString(nId);        
        s += "\"";    
      }
      break;  

    case pcode__BYTE:
      {
        int n = v->getByte(nId);
        s = QString("%1").arg(n);
      }
      break;  

    case pcode__SHORT:
      {
        int n = v->getShort(nId);
        s = QString("%1").arg(n);
      }
      break;  

    case pcode__INTEGER:
      {
        int n = v->getInteger(nId);
        s = QString("%1").arg(n);
      }
      break;  

    case pcode__LONG:
      {
        t_long n = v->getLong(nId);
        s = QString("%1").arg(n);
      }
      break;  

    case pcode__SINGLE:
      {
        t_single n = v->getSingle(nId);
        s = QString("%1").arg(n);
      }
      break;  
    case pcode__DOUBLE:
      {
        t_double n = v->getDouble(nId);
        s = QString("%1").arg(n);
      }
      break;  
/*
    case pcode__INT16:
      {
        t_integer n = v->getInt16(nId);
        s.sprintf("%d", n);
      }
      break;  
    case pcode__INT32:
      {
        t_integer n = v->getInt32(nId);
        s.sprintf("%d", n);
      }
      break;  
    case pcode__INT64:
      {
        t_long n = v->getInt64(nId);
        s.sprintf("%lld", n);
      }
      break;  
    case pcode__UINT16:
      {
        t_integer n = v->getUInt16(nId);
        s.sprintf("%d", n);
      }
      break;  
    case pcode__UINT32:
      {
        t_long n = v->getUInt32(nId);
        s.sprintf("%lld", n);
      }
      break;  
    case pcode__UINT64:
      {
        t_long n = v->getUInt64(nId);
        s.sprintf("%lld", n);
      }
      break;      
      */
    case pcode__CURRENCY:
      {
        t_currency n = v->getCurrency(nId);
        s = *n.toQString();
      }
      break;  

    case pcode__DATE:
      {
        t_date n = v->getDate(nId);
        s = *n.toQString();
      }
      break;  

		case pcode__VARIANT:

     switch(v->getVariantType(nId)){

       case pcode__BOOLEAN:
       {
           bool b = v->getVariant_Boolean(nId);
           s = b ? "True" : "False";
       }
       break;  

       //case pcode__QString:
       case pcode__QSTRING:
       {
           s = "\"";
           s += *v->getVariant_QString(nId);        
           s += "\"";        
       }
       break;  
       case pcode__CSTRING:
       {
           s = "\"";
           s += v->getVariant_CString(nId);        
           s += "\"";        
       }
       break;  

       case pcode__BYTE:
       {
           int n = v->getVariant_Byte(nId);
           s = QString("%1").arg(n);
       }
       break;  

       case pcode__SHORT:
       {
           int n = v->getVariant_Short(nId);
           s = QString("%1").arg(n);
       }
       break;  

       case pcode__INTEGER:
       {
           int n = v->getVariant_Integer(nId);
           s = QString("%1").arg(n);
       }
       break;  

       case pcode__LONG:
       {
           t_long n = v->getVariant_Long(nId);
           s = QString("%1").arg(n);
       }
       break;  

       case pcode__SINGLE:
       {
           t_single n = v->getVariant_Single(nId);
           s = QString("%1").arg(n);
       }
       break;  
       case pcode__DOUBLE:
       {
           t_double n = v->getVariant_Double(nId);
           s = QString("%1").arg(n);
       }
       break;  

       case pcode__CURRENCY:
        {
          t_currency n = v->getVariant_Currency(nId);
          s = *n.toQString();
        }
        break;  
       case pcode__DATE:
        {
          t_date n = v->getVariant_Date(nId);
          s = *n.toQString();
        }
        break;  

     }
     break;  

		default:
      {        
        if (memory_type::isBinding(nType)){
           s = "Binding Object";          
        } else if (memory_type::isKBasic(nType)){
          s = "KBasic Object";
        } else if (memory_type::isType(nType)){
          s = "User Defined Type";
        } else {
          memory_variable *v2 = v->getObject(nId);
          s.sprintf("&H%X", v2);
        }
      }
      break;  

  }

  return s;
}
