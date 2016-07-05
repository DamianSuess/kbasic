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

#include "memory_label.h"
#include "utility.h"


memory_label::memory_label			()
{

	nIdCounter = 0;

}
              
memory_label::~memory_label			()
{
  if (list_label.first(&key, &value)){
    do {

      label *m = (label *) value;



    delete m->list_label_used;

    delete m;

    } while (list_label.next(&key, &value));
  }

  list_label.clear();
  list_label2.clear();

  findMemory_label(-99); // delete cache

}

// ****************************
// * bool labelError(char *acLabelError)
// *
// * description:
// * prints a label error message
// *
// * parameter:
// * char *acLabelError = the error message to print
// *
// * return:
// * dummy
// ****************************
bool memory_label::memory_labelError(char *acLabelError)
{
	static char acText[1024];

	sprintf(acText, "\nlabel error: %s\n", acLabelError);
	console::printError(acText);
	return false;
}

char *memory_label::getKey(const char *acModule, const char *acSub, const char *acName)
{
	static char acKey[1024];
	sprintf(acKey, "%s.%s.%s", acModule, acSub, acName);
  // make case insensitive
  int n = strlen(acKey);
	for (unsigned int i = 0; i < n; i++) acKey[i] = toupper(acKey[i]);

	return acKey;
}

label	*memory_label::findMemory_label	(int nId)
{
  // * optimize
  static int _nId = -100;
  static label *v = 0;
  static void *_this = 0;

  if (_nId == nId && _this == this){
    //v2 = list_label[nId];
    return v;
  }
  // *
	if (list_label.contains(nId)){
    _nId = nId;
    _this = this;
    v = (label *) list_label.get(nId);
		return v;
	}
  _nId = -100;  

	return 0;
}

label *memory_label::newMemory_label(const char *acModule, const char *acSub, const char *acName, int nPcodeOffset)
{
	label *l = new label();

  register int n = strlen(acModule);

	memcpy(l->acModule, acModule, n);
	l->acModule[n] = '\0';

  n = strlen(acSub);

  memcpy(l->acSub, acSub, n);
	l->acSub[n] = '\0';

  n = strlen(acName);

  memcpy(l->acName, acName, n);
	l->acName[n] = '\0';

	l->nId = nIdCounter;

	l->bLabelDeclared = false;
	l->nPcodeOffset = nPcodeOffset;

  l->list_label_used = new XIntVector();//s td::li st<label_used*>();
  l->list_label_used->setAutoDelete(true);

  return l;
}

int 		memory_label::addLabel			(const char *acModule, const char *acSub, const char *acName, int nPcodeOffset)
{
	if (exist(acModule, acSub, acName)){ // already declared
		return 0;
	} else {

		nIdCounter++;

		label *c = newMemory_label(acModule, acSub, acName, nPcodeOffset);
    list_label.add(nIdCounter, (int) c);
		list_label2.addString(getKey(acModule, acSub, acName), (int) c);
		
    return nIdCounter;
    
	}

}

bool 		memory_label::exist				(int nId)
{
	label *l = findMemory_label	(nId);
	if (l != 0){
		return true;
	}
	return false;
}

bool 		memory_label::exist				(const char *acModule, const char *acSub, const char *acName)
{
	return exist	(getId(acModule, acSub, acName));
}

char     *memory_label::getName			(int nId)
{
	label *l = findMemory_label	(nId);
	if (l != 0){
		return l->acName;
	}
	return 0;
}

char     *memory_label::getModule			(int nId)
{
	label *l = findMemory_label	(nId);
	if (l != 0){
		return l->acModule;
	}
	return 0;
}

char     *memory_label::getModule			()
{
	return it->acModule;
}

char     *memory_label::getSub			()
{
	return it->acSub;
}

char     *memory_label::getName			()
{
	return it->acName;
}

int			memory_label::getId					()
{
	return it->nId;
}

bool memory_label::setPcodeOffset(int nId, int nPcodeOffset)
{
	label *l = findMemory_label	(nId);
	if (l != 0){
		l->nPcodeOffset = nPcodeOffset;
		return true;
	}
	return false;
}

int  memory_label::getPcodeOffset(int nId)
{
	label *l = findMemory_label	(nId);
	if (l != 0){
		return l->nPcodeOffset;
	}
	return 0;
}

int			memory_label::getId					(const char *acModule, const char *acSub, const char *acName)
{

  char *acKey = getKey(acModule, acSub, acName);
	if (list_label2.contains(acKey)){
    return ((label *) list_label2.getString(acKey))->nId;
	}

	return 0;
}

bool memory_label::registerCall(int nId, pcode *myPcode, int nGotoPcodeOffset, int nCurrentLine, bool bGoto, t_pcode p)
{
	label *l = findMemory_label	(nId);
	if (l != 0){

    label_used *lu = new label_used();
    lu->pcodeCall = myPcode;
		lu->bGoto = bGoto;
		lu->nCurrentLine = nCurrentLine;
		lu->nGotoPcodeOffset = nGotoPcodeOffset;
		lu->nPcodeId = p;    

    l->list_label_used->add(lu);
		return true;
	}

	return false;
}

bool		memory_label::firstCall	(int nId, pcode **pcodeCall, int *nGotoPcodeOffset, int *nCurrentLine, bool *bGoto, t_pcode *nPcodeId)
{
	label *l = findMemory_label	(nId);
	if (l != 0){

		if (l->list_label_used->size() > 0){
      
      if (l->list_label_used->first((int *) &it2)){

        {

				  *pcodeCall = it2->pcodeCall;
  			  *bGoto = it2->bGoto;
  			  *nGotoPcodeOffset = it2->nGotoPcodeOffset;
  			  *nCurrentLine = it2->nCurrentLine;
  			  *nPcodeId = it2->nPcodeId;
  			  return true;
			  }
      }
    }
	}
	return false;
}

bool		memory_label::nextCall	(int nId, pcode **pcodeCall, int *nGotoPcodeOffset, int *nCurrentLine, bool *bGoto, t_pcode *nPcodeId)
{
	label *l = findMemory_label	(nId);
	if (l != 0){

		if (l->list_label_used->size() > 0){


      if (l->list_label_used->next((int *) &it2)){

        {
        
				  *pcodeCall = it2->pcodeCall;
		  	  *bGoto = it2->bGoto;
	  		  *nGotoPcodeOffset = it2->nGotoPcodeOffset;
  			  *nCurrentLine = it2->nCurrentLine;
  			  *nPcodeId = it2->nPcodeId;

  			  return true;
        }
			}
      
		}
	}
	return false;
}

bool		memory_label::first	()
{
  return list_label.first(&key, (int *) &it);
}

bool		memory_label::last	()
{
  if (list_label.size() > 0){

    // move to last
    it = 0;
    int n = list_label.size() - 1; 
    if (list_label.first(&key, (int *) &it)){
      do {
      } while (list_label.next(&key, (int *) &it));
      return true;
    }
    
    
  } 
	return false;
}

bool		memory_label::next	()
{
  return list_label.next(&key, (int *) &it);
}

bool 		memory_label::removeLast			()
{

    // move to last
    it = 0;
    int n = list_label.size() - 1; 
    if (list_label.first(&key, (int *) &it)){
      do {
      } while (list_label.next(&key, (int *) &it));

      // move to last
	    list_label2.removeString ( getKey(getModule(), getSub(), getName()) );

      delete it->list_label_used;
	    list_label.remove ( key );

    // move to last
    it = 0;
    int n = list_label.size() - 1; 
    if (list_label.first(&key, (int *) &it)){
      do {
      } while (list_label.next(&key, (int *) &it));

    }

   }

	return true;
}

