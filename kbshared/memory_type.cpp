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


#include "memory_type.h"

memory_type::memory_type			()
{
	nIdCounter = MAX_SKALAR_TYPE_ID;

}

memory_type::~memory_type			()
{


  if (list_type.first(&key, &value)){
    do {

      type *m = (type *) value;

      delete m->list_type_element;

      delete m;

    } while (list_type.next(&key, &value));
  }

  list_type.clear();
  list_type2.clear();

  findMemory_type(-99); // delete cache

}

bool 		memory_type::isNumeric(int nId)
{
	switch(nId){
		case pcode__BYTE:
		case pcode__SHORT:
		case pcode__INTEGER:
		case pcode__LONG:

		case pcode__SINGLE:
		case pcode__DOUBLE:

		case pcode__CURRENCY:
		case pcode__VARIANT:
			return true;
		case pcode__CONST:
			return true;
	}

	return false;
}

// ****************************
// * bool typeError(char *acTypeError)
// *
// * description:
// * prints a type error message
// *
// * parameter:
// * char *acTypeError = the error message to print
// *
// * return:
// * dummy
// ****************************
bool memory_type::memory_typeError(char *acMemory_typeError)
{
	static char acText[1024];

	sprintf(acText, "\nlabel error: %s\n", acMemory_typeError);
	console::printError(acText);
	return false;
}

type	*memory_type::findMemory_type	(int nId)
{
  // * optimize
  static int _nId = -100;
  static type *v = 0;
  static void *_this = 0;

  if (_nId == nId && _this == this){
    return v;
  }
  // *  
	if (list_type.contains(nId)){
    _nId = nId;
    _this = this;
    v = (type *) list_type.get(nId);
		return v;		
	}	 
  _nId = -100;

	return 0;
}

char *memory_type::getKey(const char *acModule, const char *acName)
{
	static char acKey[1024];
	sprintf(acKey, "%s.%s", acModule, acName);
  // make case insensitive
  int n = strlen(acKey);
	for (unsigned int i = 0; i < n; i++) acKey[i] = toupper(acKey[i]);

	return acKey;
}

type *memory_type::newMemory_type(const char *acModule, const char *acName, int nScope, int nId)
{
	type *t = new type();

  register int n = strlen(acModule);

	memcpy(t->acModule, acModule, n);
	t->acModule[n] = '\0';

  n = strlen(acName);

	memcpy(t->acName, acName, n);
	t->acName[n] = '\0';

	t->nId = nId;
	t->nScope = nScope;

  t->list_type_element = new XIntVector();//st d::li st<type_element*>();
  t->list_type_element->setAutoDelete(true);

  return t;
}

int 		memory_type::addType			(const char *acModule, const char *acName, int nScope, int nId)
{
  /*
  if (nId == 100005){
    nId = nId;
  }
  if (strcmp(acName, "rpMoviesWithActor") == 0){
    acName = acName;
  }*/
  if (nId != 0){
    if (nId > nIdCounter){   
      if (nId > MAX_SKALAR_ENUM_ID){
        //nId = nId;
      } else {
        nIdCounter = nId;
      }
    }
    return addType2(acModule, acName, nScope, nId);
  } else {
    nIdCounter++;
    return addType2(acModule, acName, nScope, nIdCounter);
  }
}

int 		memory_type::addType2			(const char *acModule, const char *acName, int nScope, int nId)
{

  if (exist(nId)){
		return 0;
  } else if (exist(acModule, acName)){
		return 0;
	}
/*
  if (nId == 20000001){
    nId = nId;
  }*/
	type *c = (newMemory_type(acModule, acName, nScope, nId));
  list_type.add(nId, (int) c);
	list_type2.addString(getKey(acModule, acName), (int) c);
	 
	return nId;
	 
}

bool 		memory_type::exist				(int nId)
{
	type *m = findMemory_type	(nId);
	if (m != 0){
		return true;
	}
	return false;
}

bool 		memory_type::exist				(const char *acModule, const char *acName)
{
	return exist	(getId(acModule, acName));
}

char     *memory_type::getModule			(int nId)
{
	type *m = findMemory_type	(nId);
	if (m != 0){
		return m->acModule;
	}
	return 0;
}

char     *memory_type::getName			(int nId)
{
	type *m = findMemory_type	(nId);
	if (m != 0){
		return m->acName;
	}
	return 0;
}

int     memory_type::getScope			(int nId)
{
	type *m = findMemory_type	(nId);
	if (m != 0){
		return m->nScope;
	}
	return 0;
}

char     *memory_type::getModule			()
{
	return it->acModule;
}

char     *memory_type::getName			()
{
	return it->acName;
}

int     memory_type::getScope			()
{
	return it->nScope;
}

int			memory_type::getId					()
{
	return it->nId;
}

int			memory_type::getId					(const char *acModule, const char *acName)
{

  char *acKey = getKey(acModule, acName);

	if (list_type2.contains(acKey)){
		return ((type *) list_type2.getString(acKey))->nId;
	}	 

	return 0;
}

int 		memory_type::getSize(int nId, int *nSize)
{
  // * needed, because recursive calls would otherwise mess up iterators
  static int parser__ITERATOR = -1; 
  parser__ITERATOR++;
  if (parser__ITERATOR > parser__MAX_ITERATOR){
    //this->err("Too many recursive calls for type elements. Try to split the types."); return 0;
    parser__ITERATOR--;
    return 0;
  }

	type *m = findMemory_type	(nId);
	if (m != 0){

		char *acElementName; char *acElementType; int nElementSize; t_array *a; int nElementId;
		if (firstElement	(nId, parser__MAX_ITERATOR, &acElementName, &acElementType, &nElementSize, &a, &nElementId)){
			do {

				int n = a->typeSizeMulitplierOfArray();
 		 		//for (int i = 0; i < a->count; i++) n *= (a->idxTo[i] - a->idx[i] + 1);

       if (strcmp(acElementType, "LQSTRING") == 0 || strcmp(acElementType, "LCSTRING") == 0){
					*nSize += nElementSize * n;
       } else if (scalar(acElementType)){
					*nSize += getElementSize(acElementType) * n;
				} else {
					*nSize += nElementSize * n;
				}

			} while (nextElement(nId, parser__MAX_ITERATOR, &acElementName, &acElementType, &nElementSize, &a, &nElementId));

      parser__ITERATOR--;
			return *nSize;
		}

	}

  parser__ITERATOR--;
	return 0;
}



int 		memory_type::getSize(int nId)
{
	int nSize = 0;

  if (nId == pcode__LQSTRING || nId == pcode__LCSTRING){
			return getSize(nId, &nSize);
  } else if (scalar(nId)){
     return getElementSize(nId);
  } else if (isClass(nId)){
     return sizeof (t_object);
  } else if (isBinding(nId)){
     return sizeof (t_pointer);
  }

	return getSize(nId, &nSize);
}

int 		memory_type::getOffset(int nId, const char *acName, int *nOffset, bool *bDone, int *nIdx, t_arrays *as)
{
  // * needed, because recursive calls would otherwise mess up iterators
  static int parser__ITERATOR = -1; 
  parser__ITERATOR++;
  if (parser__ITERATOR > parser__MAX_ITERATOR){
    parser__ITERATOR--;
    return 0;
  }

	type *m = findMemory_type	(nId);
	if (m != 0){

		char *acElementName; char *acElementType; int nElementSize; t_array *ab; int nElementId;
		if (firstElement	(nId, parser__ITERATOR, &acElementName, &acElementType, &nElementSize, &ab, &nElementId)){
			do {

				if (utility::my_stricmp(acName, acElementName) == 0){ *bDone = true; parser__ITERATOR--; return *nOffset; }

				if (scalar(acElementType)){

          *nOffset += getElementSize(acElementType) * ab->typeSizeMulitplierOfArray();
				} else {

					if (utility::my_stricmp(acName, acElementName) == 0){
						if (t_array::dimensionsEqual(&as->a[*nIdx], ab) == false){ *bDone = true; *nOffset = -3; parser__ITERATOR--; return *nOffset; }
					}

   				int n = 0;
					int nOffset2 = 0;
					int nElementSize = getSize(getId(getModule(nId), acElementType));
					bool bDone2 = false;

					if (utility::my_stricmp(acName, acElementName) == 0){
						if (t_array::getOffset(&n, &as->a[*nIdx], ab, nElementSize) == false){ *bDone = true; *nOffset = -4; parser__ITERATOR--; return *nOffset; }
					}

   				*nOffset += n + getOffset(getId(getModule(nId), acElementType), acName, &nOffset2, &bDone2, ++nIdx, as);
					if (bDone2) *bDone = bDone2;

				}

			} while (*bDone == false && nextElement(nId, parser__ITERATOR, &acElementName, &acElementType, &nElementSize, &ab, &nElementId));

			
      parser__ITERATOR--;
			return *nOffset;
		}

	}

  parser__ITERATOR--;
	return -1;
}

int 		memory_type::getOffset(int nId, const char *acName, t_arrays *as)
{
	int nOffset = 0;
	bool bDone = false;
	int nIdx = 0;


	nOffset = getOffset(nId, acName, &nOffset, &bDone, &nIdx, as);
	return bDone == true ? nOffset : -1;
}

int 		memory_type::getOffset(int nId, int nElementId)
{
	int nOffset = 0;
	bool bDone = false;
	int nIdx = 0;

	nOffset = getOffset(nId, nElementId, &nOffset, &bDone);
	return bDone == true ? nOffset : -1;
}

int 		memory_type::getOffset(int nId, int _nElementId, int *nOffset, bool *bDone)
{
  // * needed, because recursive calls would otherwise mess up iterators
  static int parser__ITERATOR = -1; 
  parser__ITERATOR++;
  if (parser__ITERATOR > parser__MAX_ITERATOR){
    parser__ITERATOR--;    
    return 0;
  }

	type *m = findMemory_type	(nId);
	if (m != 0){
		
		char *acElementName; char *acElementType; int nElementSize; t_array *ab; int nElementId;
		if (firstElement	(nId, parser__ITERATOR, &acElementName, &acElementType, &nElementSize, &ab, &nElementId)){
			do {

				if (nElementId == _nElementId){ *bDone = true; parser__ITERATOR--; return *nOffset; }

				int nElementSize = 0;

        if (strcmp(acElementType, "LQSTRING") == 0 || strcmp(acElementType, "LCSTRING") == 0){
					nElementSize = getElementSize( nId, nElementId );
        } else if (scalar(acElementType)){
					nElementSize = getElementSize(acElementType);
				} else {
					nElementSize = getElementSize( nId, nElementId );
				}

				*nOffset += nElementSize * ab->typeSizeMulitplierOfArray();;

			} while (*bDone == false && nextElement(nId, parser__ITERATOR, &acElementName, &acElementType, &nElementSize, &ab, &nElementId));

      parser__ITERATOR--; 
			return *nOffset;
		}

	}

  parser__ITERATOR--; 
	return -1;
}

int 		memory_type::getType(int nId, const char *acName)
{
  // * needed, because recursive calls would otherwise mess up iterators
  static int parser__ITERATOR = -1; 
  parser__ITERATOR++;
  if (parser__ITERATOR > parser__MAX_ITERATOR){
    parser__ITERATOR--;
    return 0;
  }

	type *m = findMemory_type	(nId);
	if (m != 0){

		char *acElementName; char *acElementType; int nElementSize; t_array *a; int nElementId;
		if (firstElement	(nId, parser__ITERATOR, &acElementName, &acElementType, &nElementSize, &a, &nElementId)){
			do {

  				if (scalar(acElementType)){
						if (utility::my_stricmp(acName, acElementName) == 0){
              parser__ITERATOR--; 
  						return getType(acElementType);
						}
  				} else {
						if (utility::my_stricmp(acName, acElementName) == 0){
              parser__ITERATOR--; 
  						return nId;
						}
  					int n = getType(getId(getModule(nId), acElementType), acName);
            if (n > 0){ parser__ITERATOR--; return n; }
  				}
				

			} while (nextElement(nId, parser__ITERATOR, &acElementName, &acElementType, &nElementSize, &a, &nElementId));

      parser__ITERATOR--; 
			return 0;
		}

	}

  parser__ITERATOR--; 
	return 0;
}

int 		memory_type::getType2(int nId, const char *acName, int *type_, int *typeelement, int *nAllSize, int *_nElementSize, bool bOnlyFirstLevel)
{
  // * needed, because recursive calls would otherwise mess up iterators
  static int parser__ITERATOR = -1; 
  parser__ITERATOR++;
  if (parser__ITERATOR > parser__MAX_ITERATOR){
    parser__ITERATOR--;
    return 0;
  }

	type *m = findMemory_type	(nId);
	if (m != 0){

		int i = 1;
		char *acElementName; char *acElementType; int nElementSize; t_array *a; int nElementId;
		if (firstElement	(nId, parser__ITERATOR, &acElementName, &acElementType, &nElementSize, &a, &nElementId)){
			do {

  				if (scalar(acElementType)){
						if (utility::my_stricmp(acName, acElementName) == 0){
							*type_ = nId;
							*typeelement = i;

             *nAllSize = nElementSize * a->typeSizeMulitplierOfArray();
             *_nElementSize = nElementSize;
             parser__ITERATOR--; 
  					 return getType(acElementType);
						}
  				} else {
						if (utility::my_stricmp(acName, acElementName) == 0){
							*type_ = nId;
							*typeelement = i;

             *nAllSize = nElementSize * a->typeSizeMulitplierOfArray();
             *_nElementSize = nElementSize;
             parser__ITERATOR--; 
  						return getId(getModule(nId), acElementType);
						}
           if (!bOnlyFirstLevel){
             // getModule(nId), type can only contains other types at the same scope
  					  int n = getType2(getId(getModule(nId), acElementType), acName, type_, typeelement, nAllSize, _nElementSize, bOnlyFirstLevel);
              if (n > 0){ parser__ITERATOR--; return n; }
           }
  				}
					i++;
				

			} while (nextElement(nId, parser__ITERATOR, &acElementName, &acElementType, &nElementSize, &a, &nElementId));

      parser__ITERATOR--; 
			return 0;
		}

	}

  parser__ITERATOR--; 
	return 0;
}

bool		memory_type::addElement	(int nId, const char *acElementName, const char *acElementType, int nElementSize, t_array *a, int nElementId)
{

	type *l = findMemory_type	(nId);
	if (l != 0){

    type_element *m = new type_element();

    register int n = strlen(acElementName);

		memcpy(m->acElementName, acElementName, n);
		m->acElementName[n] = '\0';

    n = strlen(acElementType);

		memcpy(m->acElementType, acElementType, n);
		m->acElementType[n] = '\0';

  	m->nElementSize = nElementSize;
    m->nType = nElementId;



  	m->a.count = 0;

  	if (a){
  		m->a.count = a->count;
			for (int i = 0; i < a->count; i++){
				m->a.idx[i] = a->idx[i];
				m->a.idxTo[i] = a->idxTo[i];
			}
  	}

    // * überprüfen ob element name bereits vorhanden
    type_element *m2;
    if (l->list_type_element->first((int *) &m2)){
      do {
        if (m2 == m) return false;
      } while (l->list_type_element->next((int *) &m2));
    }

    l->list_type_element->add(m); 
    m->nElementId = l->list_type_element->size();
		return true;
	}

	return false;
	
}

const char *		memory_type::findElement	(int nId, int nFieldId)
{
  // * needed, because recursive calls would otherwise mess up iterators
  static int parser__ITERATOR = -1; 
  parser__ITERATOR++;
  if (parser__ITERATOR > parser__MAX_ITERATOR){
    parser__ITERATOR--;
    return 0;
  }

  char *acElementName; char *acElementType; int nElementSize; t_array *a; int nElementId;

	int i = 1;
	if (firstElement	(nId, parser__ITERATOR, &acElementName, &acElementType, &nElementSize, &a, &nElementId)){
  	do {

      if (nFieldId == i++){ parser__ITERATOR--; return acElementName; }

  	} while (nextElement(nId, parser__ITERATOR, &acElementName, &acElementType, &nElementSize, &a, &nElementId));
	}

  parser__ITERATOR--; 
	return false;
}

t_array   *memory_type::getArray		(int nId, int nFieldId)
{
  // * needed, because recursive calls would otherwise mess up iterators
  static int parser__ITERATOR = -1; 
  parser__ITERATOR++;
  if (parser__ITERATOR > parser__MAX_ITERATOR){
    parser__ITERATOR--;
    return 0;
  }

  char *acElementName; char *acElementType; int nElementSize; t_array *a; int nElementId;;

	int i = 1;
	if (firstElement	(nId, parser__ITERATOR, &acElementName, &acElementType, &nElementSize, &a, &nElementId)){
  	do {

      if (nFieldId == i++){
        parser__ITERATOR--; 
        return a;
      }

  	} while (nextElement(nId, parser__ITERATOR, &acElementName, &acElementType, &nElementSize, &a, &nElementId));
	}

  parser__ITERATOR--; 
	return 0;
}

int   memory_type::getType		(int nId, int nFieldId)
{
	type_element *m = getElement(nId, nFieldId);
	if (m != 0){
    return m->nType;
  }
	return 0;
}

int   memory_type::getElementSize	(int nId, int nFieldId)
{
  // * needed, because recursive calls would otherwise mess up iterators
  static int parser__ITERATOR = -1; 
  parser__ITERATOR++;
  if (parser__ITERATOR > parser__MAX_ITERATOR){
    parser__ITERATOR--;
    return 0;
  }

  char *acElementName; char *acElementType; int nElementSize; t_array *a; int nElementId;

	int i = 1;
	if (firstElement	(nId, parser__ITERATOR, &acElementName, &acElementType, &nElementSize, &a, &nElementId)){
  	do {

      if (nFieldId == i++){
        parser__ITERATOR--; 
        return nElementSize;
      }

  	} while (nextElement(nId, parser__ITERATOR, &acElementName, &acElementType, &nElementSize, &a, &nElementId));
	}

  parser__ITERATOR--; 
	return 0;
}

bool		memory_type::findElement	(int nId, char *acElementNa, char **acElementName, char **acElementType, int *nElementSize, t_array **a, int *nElementId)
{
  // * needed, because recursive calls would otherwise mess up iterators
  static int parser__ITERATOR = -1; 
  parser__ITERATOR++;
  if (parser__ITERATOR > parser__MAX_ITERATOR){
    parser__ITERATOR--;
    return 0;
  }

	if (firstElement	(nId, parser__ITERATOR, acElementName, acElementType, nElementSize, a, nElementId)){
  	do {

      if (utility::my_stricmp(acElementNa, *acElementName) == 0){
        parser__ITERATOR--; 
        return true;
      }

  	} while (nextElement(nId, parser__ITERATOR, acElementName, acElementType, nElementSize, a, nElementId));
	}

  parser__ITERATOR--; 
	return false;
}

int		memory_type::findElement	(int nId, const char *acElementName)
{
  // * needed, because recursive calls would otherwise mess up iterators
  static int parser__ITERATOR = -1; 
  parser__ITERATOR++;
  if (parser__ITERATOR > parser__MAX_ITERATOR){
    parser__ITERATOR--;
    return 0;
  }

  char *acElementNa; char *acElementType; int nElementSize; t_array *a; int nElementId;

	if (firstElement	(nId, parser__ITERATOR, &acElementNa, &acElementType, &nElementSize, &a, &nElementId)){
  	do {

      if (utility::my_stricmp(acElementName, (const char *) acElementNa) == 0){ 
        parser__ITERATOR--; 
        return nElementId;
      }

  	} while (nextElement(nId, parser__ITERATOR, &acElementNa, &acElementType, &nElementSize, &a, &nElementId));
	}

  parser__ITERATOR--; 
	return 0;
}

int findElement	(int nId, char *acElementName);


type_element	*memory_type::getElement	(int nId, int _nElementId)
{
  // * needed, because recursive calls would otherwise mess up iterators
  static int parser__ITERATOR = -1; 
  parser__ITERATOR++;
  if (parser__ITERATOR > parser__MAX_ITERATOR){
    parser__ITERATOR--;
    return 0;
  }

	type *l = findMemory_type(nId);
	if (l != 0){

    char *acElementNa; char *acElementType; int nElementSize; t_array *a; int nElementId;

	  if (firstElement	(nId, parser__ITERATOR, &acElementNa, &acElementType, &nElementSize, &a, &nElementId)){
  	  do {

       if (_nElementId == nElementId){ 
         type_element	*mm = it2[parser__ITERATOR];
         parser__ITERATOR--; 
         return mm;
       }

  	  } while (nextElement(nId, parser__ITERATOR, &acElementNa, &acElementType, &nElementSize, &a, &nElementId));
	  }
  }

  parser__ITERATOR--; 
	return 0;
}

bool		memory_type::firstElement	(int nId, int parser__ITERATOR, char **acElementName, char **acElementType, int *nElementSize, t_array **a, int *nElementId)
{

	type *l = findMemory_type	(nId);
	if (l != 0){

    
    if (l->list_type_element->first((int *) &it2[parser__ITERATOR], parser__MAX_ITERATOR)){

        {

					*acElementName = it2[parser__ITERATOR]->acElementName;
					*acElementType = it2[parser__ITERATOR]->acElementType;
					*nElementSize = it2[parser__ITERATOR]->nElementSize;
					*a = &(it2[parser__ITERATOR]->a);
         *nElementId = it2[parser__ITERATOR]->nElementId;

  				return true;
				}
    }
		

	}
	return false;
}

bool		memory_type::nextElement	(int nId, int parser__ITERATOR, char **acElementName, char **acElementType, int *nElementSize, t_array **a, int *nElementId)
{
	type *l = findMemory_type(nId);
	if (l != 0){

    
    if (l->list_type_element->next((int *) &it2[parser__ITERATOR], parser__MAX_ITERATOR)){

      {

					*acElementName = it2[parser__ITERATOR]->acElementName;
					*acElementType = it2[parser__ITERATOR]->acElementType;
					*nElementSize = it2[parser__ITERATOR]->nElementSize;
					*a = &(it2[parser__ITERATOR]->a);
         *nElementId = it2[parser__ITERATOR]->nElementId;

  				return true;
				
      }      
		}
	}
	return false;
}

bool		memory_type::first	()
{
  return list_type.first(&key, (int *) &it);
}

bool		memory_type::next	()
{
  return list_type.next(&key, (int *) &it);
}

int	memory_type::getInteger(int nId, int nElementId)
{
	type_element *m = getElement(nId, nElementId);
	if (m != 0){
    return m->integer_;
  }
  return 0;
}

bool		memory_type::setInteger(int nId, int nElementId, int n)
{
	type_element *m = getElement(nId, nElementId);
	if (m != 0){
    m->integer_ = n;
    return true;
  }
  return false;
}
