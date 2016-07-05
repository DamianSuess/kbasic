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

#include <qlibrary.h>
#include <qmap.h>

#include "interpreter.h"
#include "../kbshared/pcode.h"

#include "../kbshared/_form.h"


extern QMap<QString,QLibrary*>ll;

QObject *EventSource = 0;

bool interpreter::findVars(int id, const char **acModule, const char **acSub, const char **acName)
{
  if (myParser != 0) return myParser->findVar(id, acModule, acSub, acName);
  return false;
}

bool interpreter::findConsts(int id, const char **acModule, const char **acSub, const char **acName)
{
  if (id <= 65){ // magic number see kbc in parser registerConstPublic()
    *acModule = "Global";
    *acSub = "";
    *acName = "Builtin";
    return true;
  }
  if (myParser != 0) return myParser->findConst(id, acModule, acSub, acName);
  return false;
}

bool interpreter::findScope(int nModuleId, int nSubId, bool bPropertyGet, bool bPropertySet, const char **acModule, const char **acSub)
{
  if (myParser != 0){
    return myParser->findScope(nModuleId, nSubId, bPropertyGet, bPropertySet, acModule, acSub);
  }

  return false;
}

bool interpreter::findScope2(int nModuleId, int nSubId, bool bPropertyGet, bool bPropertySet, const char **acModule, const char **acSub)
{
  if (myParser != 0){
    return myParser->findScope2(nModuleId, nSubId, bPropertyGet, bPropertySet, acModule, acSub);
  }

  return false;
}

const char *interpreter::findStatics(int id)
{
 if (myParser != 0) return myParser->findStringLiteral(id);
 return "";
}

const char *interpreter::findTypes(int id)
{
  if (memory_type::scalar(id)) return pcode::pcode_(id);
  if (memory_type::isBinding(id)) return pcode_kbasic_binding::classname_(id);
  if (id == pcode__OBJECT) return pcode::pcode_(pcode__OBJECT);
  if (myParser != 0){
    const char *ac = myParser->findEnum(id);
    if (ac) return ac;
    return myParser->findType(id);
  }
 return "";
}

const char *interpreter::findFieldInType(int type_id, int field_id)
{
	if (myParser != 0) return myParser->findTypeElement(type_id, field_id);
  return "";
}

const char *interpreter::findFieldInEnum(int enum_id, int field_id)
{
	if (myParser != 0) return myParser->findEnumElement(enum_id, field_id);
  return "";
}

int interpreter::registerTypePublic(const char *name, int id){ return myType->addType("", name, 0, id); }


void interpreter::callSlot(memory_variable2 *v3, int identifier2, const char *name, QList<int> *param2, int return_type)
{
  class_bindingconnect9 *m = class_bindingconnect[name];

  if (m->count()){

    memory_variable2 *v = (memory_variable2 *) v3->getObject(identifier2);

    for ( uint i = 0; i < m->count(); ++i ){
      connect_ *c = m->at(i);
      if (c->vSender == v){         
    
  int nClassId = v3->getClassId();

  sub *s = myClass->getSub(nClassId, name);

  if (s){

#ifdef HAS_CONSOLE
    if (!bSilent){
		  info("SIGNAL", name);
    }
#endif

    memory_variable2 *oldMeVars = meVars;    
    meVars = v3;//(memory_variable2 *) v3->getObject(identifier2);


    int m = myPcode->getPos();
    myPcode->setPos(s->pc_pos);

    enterLocal(name);

    // 
    myLocalFrame.last()->subPcodeOffset = s->pc_pos;
    myLocalFrame.last()->onErrorGotoPos = 0;
    myLocalFrame.last()->return_pos = 0;  // wird bei classes nicht benutzt
    

    // create vars on local
    int n = param2->count();
    for ( uint i = 0; i < n; ++i ){
      int o = n - i - 1;
      int type = param2->at(o);      

      const char *acModule = "";
      const char *acSub = "";
      const char *acVar = "";
      t_array *a = new t_array();
      bool bByVal = false;
      bool bReference = false;
      bool bStatic = false;
      int nScope = 0;
      int nTypeSize = sizeof(t_pointer);

      QString classmethodno = myClass->getName(nClassId);
      classmethodno += name;
      QString kk; kk = kk.sprintf("%d", o);
      classmethodno += kk;


      int identifier = class_bindingparam[classmethodno];
       
      getVar(param)->declare(acModule, acSub, acVar, type, a, bByVal, bReference, bStatic, true, nScope, nTypeSize, identifier);


      myStack->popPCode();      
      bool b44 = myStack->popBoolean();
      bool memory_variable2 = myStack->popBoolean();
      interpreter_parameter *ppp = (interpreter_parameter *) myStack->popPointer(); 

      t_pointer pp = (void *) ppp->pointer_;

      getVar(param)->setPointer(identifier, pp);

    }


    interpret2(true, false, myClass->getPcodeLenMethod(nClassId, s));
    exitLocal();

    myPcode->setPos(m);
    meVars = oldMeVars;
  }

      }
    }
 
  }
 
}

interpreter_parameter *interpreter::callFunction(memory_variable2 *v, int identifier, const char *name, QList<int> *param)
{
  int return_type;
  return_type = pcode__BOOLEAN;
  interpreter_parameter *returner;

  callSub(v, identifier, name, param, return_type, returner);

  return returner;  
}

void interpreter::callSub(memory_variable2 *v3, int identifier2, const char *name, QList<int> *param2, int return_type, interpreter_parameter *returner)
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif



  sub *s = myClass->getLastSub();

  if (s){
    
#ifdef HAS_CONSOLE
    if (!bSilent){
		  info("EVENT", name); 
    }
#endif

    memory_variable2 *oldMeVars = meVars; 
    
    meVars = (memory_variable2 *) v3->getObject(identifier2);
    int nClassId = meVars->getClassId();
   
    int m = myPcode->getPos();
    myPcode->setPos(s->pc_pos);

    enterLocal(name);

    
    myLocalFrame.last()->subPcodeOffset = s->pc_pos;
    myLocalFrame.last()->onErrorGotoPos = 0;
    myLocalFrame.last()->return_pos = 0;  // wird bei classes nicht benutzt
    

    // create vars on local
    int n = param2->count();
    for ( uint i = 0; i < n; ++i ){
      int o = n - i - 1;
      int type = param2->at(o);      

      const char *acModule = "";
      const char *acSub = "";
      const char *acVar = "";
      t_array *a = new t_array();
      bool bByVal = false;
      bool bReference = false;
      bool bStatic = false;
      int nScope = 0;
      int nTypeSize = sizeof(t_pointer);

      QString classmethodno = myClass->getName(nClassId);
      classmethodno += name;
      QString kk; kk = kk.sprintf("%d", o);
      classmethodno += kk;


      int identifier = class_bindingparam[classmethodno];
       
      getVar(param)->declare(acModule, acSub, acVar, type, a, bByVal, bReference, bStatic, true, nScope, nTypeSize, identifier);


      myStack->popPCode();      
      bool b44 = myStack->popBoolean();
      bool memory_variable2 = myStack->popBoolean();
      interpreter_parameter *ppp = (interpreter_parameter *) myStack->popPointer(); 

      t_pointer pp = (void *) ppp->pointer_;

      getVar(param)->setPointer(identifier, pp);

    }


    interpret2(true, false, myClass->getPcodeLenMethod(nClassId, s));
    exitLocal();

    meVars = oldMeVars; 
    myPcode->setPos(m);

  }

	
}


extern _form *EXTERN_my_form_test;

void interpreter::callEvent(memory_variable2 *v3, int identifier2, const char *name, const char *group, const char *control, QList<int> *param2, int return_type, interpreter_parameter *returner, t_boolean *bReturnCode)
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif

  QString ss;
  sub *s;
  


  bool bGroup = false;

  if (identifier2 > pcode__user_defined_class && identifier2 < pcode__user_defined_module){
re2:
    s = myClass->getLastSub();
    if (s){
   
      ss = s->acRealName;

      if (ss.startsWith(control, Qt::CaseInsensitive)){
        ss = control;
        if (ss.length()){
          ss = ss + "_";
          ss += name;
        } else {
          ss = name;
        }
      }

      // try name
      ss = control;
      if (ss.length()){
        ss = ss + "_";
        ss += name;
      } else {
        ss = name;
      }

      if (ss.compare(s->acRealName, Qt::CaseInsensitive) != 0){ // retry, because getLastSub() might be wrong


        s = myClass->getSub(identifier2, ss.toAscii(), param2);

        if (s){
          goto re2;
        }

        return;

      }
      goto we;
    }

    return;
  }

re:
  s = myClass->getLastSub();

  if (s){
    
    ss = bGroup ? s->acRealName : s->acName;

    if (ss.startsWith(control, Qt::CaseInsensitive)){
      ss = control;
      if (ss.length()){
        ss = ss + "_";
        ss += name;
      } else if (strlen(group)){
        ss = group;
        ss = ss + "_";
        ss += name;
      } else {
        ss = name;
      }
      
    }

    if (ss.compare(s->acRealName, Qt::CaseInsensitive) != 0){ // retry, because getLastSub() might be wrong

      int nClassId = v3->getClassId();

      // try name
      ss = control;
      if (ss.length()){
        ss = ss + "_";
        ss += name;
      } else {
        ss = name;
      }

      s = myClass->getSub(nClassId, ss.toAscii(), param2);

      if (s){
        goto re;
      }

      // try group
      if (bGroup) return; else bGroup = true;
      ss = group;
      if (ss.length()){
        ss = ss + "_";
        ss += name;
      } else {
        ss = name;
      }

      s = myClass->getSub(nClassId, ss.toAscii(), param2);

      if (s){
        goto re;
      }

      return;

    }

we:
#ifdef HAS_CONSOLE
    if (!bSilent){
		  info("EVENT2", ss.toAscii());
    }
#endif

    memory_variable2 *oldMeVars = meVars; 
    
    meVars = v3; 
    int nClassId = meVars->getClassId();
    
    int m = myPcode->getPos();
    myPcode->setPos(s->pc_pos);

    enterLocal(ss.toAscii());

    
    local_frame_ *l = myLocalFrame.last();
    l->subPcodeOffset = s->pc_pos;
    l->onErrorGotoPos = 0;
    l->return_pos = 0;  // wird bei classes nicht benutzt
    
    int nCancelId = 0;

    int nestatics[interpreter__MAX_PARAM];

    // create vars on local
    int n = param2->count();
    for ( uint i = 0; i < n; ++i ){
      nestatics[i] = 0;
      int o = n - i - 1;
      int type = param2->at(o);      

      static t_array a;// = new t_array();      
            
      QString classmethodno = myClass->getName(nClassId);
      classmethodno += s->acName;
      QString kk; kk = kk.sprintf("%d", o);
      classmethodno += kk;


      int identifier = class_bindingparam[classmethodno];
       
      int nId = getVar(param)->declare("", "", "", type, &a, false, false, false, false, 0, sizeof(t_variant), identifier);
      if (type == pcode__BOOLEAN && strncmp(s->acName, "Form_OnClose", 12) == 0) nCancelId = nId;

      int nn = myStack->popPCode();
      switch(nn){
        
        case pcode__BOOLEAN:
           getVar(param)->setBoolean(identifier, myStack->popBoolean());
          break;

        case pcode__QSTRING:
           getVar(param)->setQString(identifier, myStack->popQString(), 0);
          break;
        case pcode__CSTRING:
           getVar(param)->setCString(identifier, myStack->popCString(), 0, 0);
          break;

    		case pcode__EQSTRING:
             nestatics[i] =myStack->popQStringId();
             getVar(param)->setQString(identifier, estatics->getQString(nestatics[i], 0), 0);
						 break;
    		case pcode__ECSTRING:
             nestatics[i] =myStack->popCStringId();
             getVar(param)->setCString(identifier, estatics->getCString(nestatics[i], 0), 0, 0);
						 break;

    		case pcode__REALCSTRING: 
          getVar(param)->setCString(identifier, myStack->popRealCString(), 0, 0); 
          break;


        case pcode__BYTE: getVar(param)->setByte(identifier, myStack->popByte()); break;
        case pcode__SHORT: getVar(param)->setShort(identifier, myStack->popShort()); break;
        case pcode__INTEGER: getVar(param)->setInteger(identifier, myStack->popInteger()); break;
        case pcode__LONG: getVar(param)->setLong(identifier, myStack->popLong()); break;

        case pcode__SINGLE: getVar(param)->setSingle(identifier, myStack->popSingle()); break;
        case pcode__DOUBLE: getVar(param)->setDouble(identifier, myStack->popDouble()); break;

        case pcode__CURRENCY: getVar(param)->setCurrency(identifier, myStack->popCurrency()); break;
        case pcode__DATE: getVar(param)->setDate(identifier, myStack->popDate()); break;

        case pcode__OBJECT: 
          {          
            bool b44 = myStack->popBoolean();
            bool memory_variable2 = myStack->popBoolean();
				    t_pointer p = myStack->popPointer();          
            getVar(param)->setObject(identifier, p); break;
          }          

        default:
          {
             bool b44 = myStack->popBoolean();
             bool memory_variable2 = myStack->popBoolean();
             interpreter_parameter *ppp = (interpreter_parameter *) myStack->popPointer(); 
             t_pointer pp = (void *) ppp->pointer_;
             getVar(param)->setPointer(identifier, pp);
          }
          break;
      }

    }
    
    interpret2(true, false, myClass->getPcodeLenMethod(nClassId, s));

    if (n == 1 && nCancelId){
       *bReturnCode = getVar(param)->getBoolean(nCancelId);
       exitLocal();
    } else {
      exitLocal();

      if (bReturnCode != 0){
        if (myStack->peekPCode()){
          *bReturnCode = myStack->popBoolean();
          myStack->pushBoolean(*bReturnCode);
        }
      }
    }

    meVars = oldMeVars; 
    myPcode->setPos(m);

   
    EventSource = 0;

  }
	
}

bool interpreter::hasSlot(memory_variable2 *v3, int identifier, const char *name, QList<int> *param, int return_type)
{
  if (interpretPcode() == false || /*scope == outofscope || */identifier == 0) return false;
  
  class_bindingconnect9 *m = class_bindingconnect[name];

  if (m->count()){

    memory_variable2 *v = (memory_variable2 *) v3->getObject(identifier);

    int nClassId = v3->getClassId();
    
    for ( uint i = 0; i < m->count(); ++i ){
      connect_ *c = m->at(i);
      if (c->vSender == v){
         return true;
      }
    }

  }
 
  
  return false;
}

bool interpreter::hasFunction(memory_variable2 *v, int identifier, const char *name, QList<int> *param, int return_type)
{
  return hasSub(v, identifier, name, param, return_type);
}

bool interpreter::hasSub(memory_variable2 *v3, int identifier, const char *name, QList<int> *param, int return_type)
{

  if (interpretPcode() == false || /*scope == outofscope || */identifier == 0) return false;
  
  if (bParentCalled == true){
    bParentCalled = false;
    return false;
  }   
  memory_variable2 *v = (memory_variable2 *) v3->getObject(identifier);

  int nClassId = v->getClassId();

  sub *s = myClass->getSub(nClassId, name, param);


  if (s){
    return true;

  }


	return false;
}

bool interpreter::hasEvent(memory_variable2 *v3, int identifier, const char *name, const char *group, const char *control, QList<int> *param, int return_type)
{

/*
QString q;
  
    if (EXTERN_my_form_test)q = EXTERN_my_form_test->GETPROPERTY_Flag();

    if (EXTERN_my_form_test && q.isEmpty()){
      q = q;
    }
*/

  if (interpretPcode() == false || v3 == 0/*|| identifier == 0*/) return false;
  if ((strlen(control) == 0 && strlen(group) == 0) && identifier == 0) return false;
  
  if (bParentCalled == true){
    bParentCalled = false;
    return false;
  }   

  if (identifier > pcode__user_defined_class && identifier < pcode__user_defined_module){

    // try name
    QString ss = control;
    if (ss.length()){
      ss = ss + "_";
      ss += name;
    } else {
      ss = name;
    }
    
    sub *s = myClass->getSub(identifier, ss.toAscii(), param);

    if (s){
      return true;
    }

    return false;
  }

  memory_variable2 *v = v3;//(memory_variable2 *) v3->getObject(identifier);

  int nClassId = v->getClassId();
  

  // try name
  QString ss = control;
  if (ss.length()){
    ss = ss + "_";
    ss += name;
  } else {
    ss = name;
  }

  sub *s = myClass->getSub(nClassId, ss.toAscii(), param);

  if (s){
    return true;
  }

  // try group
  ss = group;
  if (ss.length()){
    ss = ss + "_";
    ss += name;
  } else {
    ss = name;
  }

  s = myClass->getSub(nClassId, ss.toAscii(), param);

  if (s){
    return true;
  }

	return false;
}

bool interpreter::callLib(memory_variable2 *v2, const char *lib, const char *function, int rt, int count, const char *signature)
{   
//
  
  if (!ll.contains(lib)){
     ll.insert(lib, new QLibrary(lib));
     if (!ll[lib]->load()){
       runtimeError(utility::con(lib, ": error while loading extern library. Could not resolve or load it."));
     }
   }

   bool bReturn = rt != pcode__VOID;// && rt != 0;

   bool rb;
   char ry;
   short rs;
   int ri;
   t_long rl;
   t_single rk;
   t_double rd;
   void *rp;

   bool *b[10];
   char *y[10];
   short *s[10];
   int *i[10];
   t_long *l[10];
   t_integer *k[10];
   t_long *d[10];
   void *p[10];

   int  t[10]; // type
   bool v[10]; // byref/byval

   char *ac = (char *) signature;

   QList<int> kk = v2->list_variable.keys();
   QList<int>::iterator it = kk.begin();

   //int kkk = 2;
 //  char ttt[10000];

   // copy the addresses of the vars
   for (int x = 0; x < count; x++){


     ac[8] = 0;
     t[x] = atoi(ac); ac += 9;
     ac[1] = 0;
     v[x] = atoi(ac) == 1; ac += 2;

     memory_variable *v3;
     int o; 
     int f;
     if (v[x]){
       v3 = v2;
       o = *it;
       f = 0;
     } else {
       int nId = v2->getReferenceId(*it); 
       if (nId){
         v3 = v2->getReferenceVariablePool(*it);
         o = nId;
         f = v2->getReferenceOffset(*it);
       } else { // WORKAROUND for dynamic string, non variable
          v3 = v2;
          o = *it;
          f = 0;         
       }
     }
     
     switch(t[x]){
       case pcode__BOOLEAN:
         b[x] = (bool *) v3->getAddress(o, f, 0);
         break;
       case pcode__CSTRING:
         p[x] = (void *) v3->getCString(o, f);
         break;
       case pcode__BYTE:
         y[x] = (char *) v3->getAddress(o, f, 0);
         break;
       case pcode__SHORT:
         s[x] = (short *) v3->getAddress(o, f, 0);
         break;
       case pcode__ANY:
          i[x] = (int *) v3->getInteger(o, f);
          t[x] = pcode__INTEGER;
          break;
       case pcode__INTEGER:
         {
         i[x] = (int *) v3->getAddress(o, f, 0);
          break;
         }
       case pcode__LONG:
         l[x] = (t_long *) v3->getAddress(o, f, 0);
         break;
       case pcode__SINGLE:
         k[x] = (t_integer *) v3->getAddress(o, f, 0);  // compiler complains about using t_single 
         break;
       case pcode__DOUBLE:
         d[x] = (t_long *) v3->getAddress(o, f, 0);  // compiler complains about using t_double
         break;

       default:
         p[x] = (t_long *) v3->getAddress(o, f, 0);
         break;
     }
     
     ++it;
   }
   
   if (bReturn){
     switch(rt){
       case pcode__BOOLEAN:
        switch(count){
          case 0:
            {
              bool_c0 c = (bool_c0) ll[lib]->resolve( function );
              if (c) rb = c (
              );
              else runtimeError(utility::con(function, ": Could not resolve function in extern library."));
            }
            myStack->pushBoolean(rb);
            break;
          case 1:
            {
              bool_c1 c = (bool_c1) ll[lib]->resolve( function );
              if (c) rb = c (
                  t[0] == pcode__BOOLEAN  ? v[0] ? ( void *) (*b[0]) : ( void *) (b[0])
                : t[0] == pcode__BYTE     ? v[0] ? ( void *) (*y[0]) : ( void *) (y[0])
                : t[0] == pcode__SHORT    ? v[0] ? ( void *) (*s[0]) : ( void *) (s[0])
                : t[0] == pcode__INTEGER  ? v[0] ? ( void *) (*i[0]) : ( void *) (i[0])
                : t[0] == pcode__LONG     ? v[0] ? ( void *) (*l[0]) : ( void *) (l[0])
                : t[0] == pcode__SINGLE   ? v[0] ? ( void *) (*k[0]) : ( void *) (k[0])
                : t[0] == pcode__DOUBLE   ? v[0] ? ( void *) (*d[0]) : ( void *) (d[0])
                :                          (p[0])
              );
              else return runtimeError(utility::con(function, " function call failed. ", ll[lib]->errorString()));
              myStack->pushBoolean(rb);
            }
            break;
          case 2:
            {
              bool_c2 c = (bool_c2) ll[lib]->resolve( function );
              if (c) rb = c (
                  t[0] == pcode__BOOLEAN  ? v[0] ? ( void *) (*b[0]) : ( void *) (b[0])
                : t[0] == pcode__BYTE     ? v[0] ? ( void *) (*y[0]) : ( void *) (y[0])
                : t[0] == pcode__SHORT    ? v[0] ? ( void *) (*s[0]) : ( void *) (s[0])
                : t[0] == pcode__INTEGER  ? v[0] ? ( void *) (*i[0]) : ( void *) (i[0])
                : t[0] == pcode__LONG     ? v[0] ? ( void *) (*l[0]) : ( void *) (l[0])
                : t[0] == pcode__SINGLE   ? v[0] ? ( void *) (*k[0]) : ( void *) (k[0])
                : t[0] == pcode__DOUBLE   ? v[0] ? ( void *) (*d[0]) : ( void *) (d[0])
                :                          (p[0])
                ,
                  t[1] == pcode__BOOLEAN  ? v[1] ? ( void *) (*b[1]) : ( void *) (b[1])
                : t[1] == pcode__BYTE     ? v[1] ? ( void *) (*y[1]) : ( void *) (y[1])
                : t[1] == pcode__SHORT    ? v[1] ? ( void *) (*s[1]) : ( void *) (s[1])
                : t[1] == pcode__INTEGER  ? v[1] ? ( void *) (*i[1]) : ( void *) (i[1])
                : t[1] == pcode__LONG     ? v[1] ? ( void *) (*l[1]) : ( void *) (l[1])
                : t[1] == pcode__SINGLE   ? v[1] ? ( void *) (*k[1]) : ( void *) (k[1])
                : t[1] == pcode__DOUBLE   ? v[1] ? ( void *) (*d[1]) : ( void *) (d[1])
                :                          (p[1])
              );
              else return runtimeError(utility::con(function, " function call failed. ", ll[lib]->errorString()));
              myStack->pushBoolean(rb);
            }
            break;
          case 3:
            {
              bool_c3 c = (bool_c3) ll[lib]->resolve( function );
              if (c) rb = c (
                  t[0] == pcode__BOOLEAN  ? v[0] ? ( void *) (*b[0]) : ( void *) (b[0])
                : t[0] == pcode__BYTE     ? v[0] ? ( void *) (*y[0]) : ( void *) (y[0])
                : t[0] == pcode__SHORT    ? v[0] ? ( void *) (*s[0]) : ( void *) (s[0])
                : t[0] == pcode__INTEGER  ? v[0] ? ( void *) (*i[0]) : ( void *) (i[0])
                : t[0] == pcode__LONG     ? v[0] ? ( void *) (*l[0]) : ( void *) (l[0])
                : t[0] == pcode__SINGLE   ? v[0] ? ( void *) (*k[0]) : ( void *) (k[0])
                : t[0] == pcode__DOUBLE   ? v[0] ? ( void *) (*d[0]) : ( void *) (d[0])
                :                          (p[0])
                ,
                  t[1] == pcode__BOOLEAN  ? v[1] ? ( void *) (*b[1]) : ( void *) (b[1])
                : t[1] == pcode__BYTE     ? v[1] ? ( void *) (*y[1]) : ( void *) (y[1])
                : t[1] == pcode__SHORT    ? v[1] ? ( void *) (*s[1]) : ( void *) (s[1])
                : t[1] == pcode__INTEGER  ? v[1] ? ( void *) (*i[1]) : ( void *) (i[1])
                : t[1] == pcode__LONG     ? v[1] ? ( void *) (*l[1]) : ( void *) (l[1])
                : t[1] == pcode__SINGLE   ? v[1] ? ( void *) (*k[1]) : ( void *) (k[1])
                : t[1] == pcode__DOUBLE   ? v[1] ? ( void *) (*d[1]) : ( void *) (d[1])
                :                          (p[1])
                ,
                  t[2] == pcode__BOOLEAN  ? v[2] ? ( void *) (*b[2]) : ( void *) (b[2])
                : t[2] == pcode__BYTE     ? v[2] ? ( void *) (*y[2]) : ( void *) (y[2])
                : t[2] == pcode__SHORT    ? v[2] ? ( void *) (*s[2]) : ( void *) (s[2])
                : t[2] == pcode__INTEGER  ? v[2] ? ( void *) (*i[2]) : ( void *) (i[2])
                : t[2] == pcode__LONG     ? v[2] ? ( void *) (*l[2]) : ( void *) (l[2])
                : t[2] == pcode__SINGLE   ? v[2] ? ( void *) (*k[2]) : ( void *) (k[2])
                : t[2] == pcode__DOUBLE   ? v[2] ? ( void *) (*d[2]) : ( void *) (d[2])
                :                          (p[2])
              );
              else return runtimeError(utility::con(function, " function call failed. ", ll[lib]->errorString()));
              myStack->pushBoolean(rb);
            }
            break;
          case 4:
            {
              bool_c4 c = (bool_c4) ll[lib]->resolve( function );
              if (c) rb = c (
                  t[0] == pcode__BOOLEAN  ? v[0] ? ( void *) (*b[0]) : ( void *) (b[0])
                : t[0] == pcode__BYTE     ? v[0] ? ( void *) (*y[0]) : ( void *) (y[0])
                : t[0] == pcode__SHORT    ? v[0] ? ( void *) (*s[0]) : ( void *) (s[0])
                : t[0] == pcode__INTEGER  ? v[0] ? ( void *) (*i[0]) : ( void *) (i[0])
                : t[0] == pcode__LONG     ? v[0] ? ( void *) (*l[0]) : ( void *) (l[0])
                : t[0] == pcode__SINGLE   ? v[0] ? ( void *) (*k[0]) : ( void *) (k[0])
                : t[0] == pcode__DOUBLE   ? v[0] ? ( void *) (*d[0]) : ( void *) (d[0])
                :                          (p[0])
                ,
                  t[1] == pcode__BOOLEAN  ? v[1] ? ( void *) (*b[1]) : ( void *) (b[1])
                : t[1] == pcode__BYTE     ? v[1] ? ( void *) (*y[1]) : ( void *) (y[1])
                : t[1] == pcode__SHORT    ? v[1] ? ( void *) (*s[1]) : ( void *) (s[1])
                : t[1] == pcode__INTEGER  ? v[1] ? ( void *) (*i[1]) : ( void *) (i[1])
                : t[1] == pcode__LONG     ? v[1] ? ( void *) (*l[1]) : ( void *) (l[1])
                : t[1] == pcode__SINGLE   ? v[1] ? ( void *) (*k[1]) : ( void *) (k[1])
                : t[1] == pcode__DOUBLE   ? v[1] ? ( void *) (*d[1]) : ( void *) (d[1])
                :                          (p[1])
                ,
                  t[2] == pcode__BOOLEAN  ? v[2] ? ( void *) (*b[2]) : ( void *) (b[2])
                : t[2] == pcode__BYTE     ? v[2] ? ( void *) (*y[2]) : ( void *) (y[2])
                : t[2] == pcode__SHORT    ? v[2] ? ( void *) (*s[2]) : ( void *) (s[2])
                : t[2] == pcode__INTEGER  ? v[2] ? ( void *) (*i[2]) : ( void *) (i[2])
                : t[2] == pcode__LONG     ? v[2] ? ( void *) (*l[2]) : ( void *) (l[2])
                : t[2] == pcode__SINGLE   ? v[2] ? ( void *) (*k[2]) : ( void *) (k[2])
                : t[2] == pcode__DOUBLE   ? v[2] ? ( void *) (*d[2]) : ( void *) (d[2])
                :                          (p[2])
                ,
                  t[3] == pcode__BOOLEAN  ? v[3] ? ( void *) (*b[3]) : ( void *) (b[3])
                : t[3] == pcode__BYTE     ? v[3] ? ( void *) (*y[3]) : ( void *) (y[3])
                : t[3] == pcode__SHORT    ? v[3] ? ( void *) (*s[3]) : ( void *) (s[3])
                : t[3] == pcode__INTEGER  ? v[3] ? ( void *) (*i[3]) : ( void *) (i[3])
                : t[3] == pcode__LONG     ? v[3] ? ( void *) (*l[3]) : ( void *) (l[3])
                : t[3] == pcode__SINGLE   ? v[3] ? ( void *) (*k[3]) : ( void *) (k[3])
                : t[3] == pcode__DOUBLE   ? v[3] ? ( void *) (*d[3]) : ( void *) (d[3])
                :                          (p[3])
              );
              else return runtimeError(utility::con(function, " function call failed. ", ll[lib]->errorString()));
              myStack->pushBoolean(rb);
            }
            break;
          case 5:
            {
              bool_c5 c = (bool_c5) ll[lib]->resolve( function );
              if (c) rb = c (
                  t[0] == pcode__BOOLEAN  ? v[0] ? ( void *) (*b[0]) : ( void *) (b[0])
                : t[0] == pcode__BYTE     ? v[0] ? ( void *) (*y[0]) : ( void *) (y[0])
                : t[0] == pcode__SHORT    ? v[0] ? ( void *) (*s[0]) : ( void *) (s[0])
                : t[0] == pcode__INTEGER  ? v[0] ? ( void *) (*i[0]) : ( void *) (i[0])
                : t[0] == pcode__LONG     ? v[0] ? ( void *) (*l[0]) : ( void *) (l[0])
                : t[0] == pcode__SINGLE   ? v[0] ? ( void *) (*k[0]) : ( void *) (k[0])
                : t[0] == pcode__DOUBLE   ? v[0] ? ( void *) (*d[0]) : ( void *) (d[0])
                :                          (p[0])
                ,
                  t[1] == pcode__BOOLEAN  ? v[1] ? ( void *) (*b[1]) : ( void *) (b[1])
                : t[1] == pcode__BYTE     ? v[1] ? ( void *) (*y[1]) : ( void *) (y[1])
                : t[1] == pcode__SHORT    ? v[1] ? ( void *) (*s[1]) : ( void *) (s[1])
                : t[1] == pcode__INTEGER  ? v[1] ? ( void *) (*i[1]) : ( void *) (i[1])
                : t[1] == pcode__LONG     ? v[1] ? ( void *) (*l[1]) : ( void *) (l[1])
                : t[1] == pcode__SINGLE   ? v[1] ? ( void *) (*k[1]) : ( void *) (k[1])
                : t[1] == pcode__DOUBLE   ? v[1] ? ( void *) (*d[1]) : ( void *) (d[1])
                :                          (p[1])
                ,
                  t[2] == pcode__BOOLEAN  ? v[2] ? ( void *) (*b[2]) : ( void *) (b[2])
                : t[2] == pcode__BYTE     ? v[2] ? ( void *) (*y[2]) : ( void *) (y[2])
                : t[2] == pcode__SHORT    ? v[2] ? ( void *) (*s[2]) : ( void *) (s[2])
                : t[2] == pcode__INTEGER  ? v[2] ? ( void *) (*i[2]) : ( void *) (i[2])
                : t[2] == pcode__LONG     ? v[2] ? ( void *) (*l[2]) : ( void *) (l[2])
                : t[2] == pcode__SINGLE   ? v[2] ? ( void *) (*k[2]) : ( void *) (k[2])
                : t[2] == pcode__DOUBLE   ? v[2] ? ( void *) (*d[2]) : ( void *) (d[2])
                :                          (p[2])
                ,
                  t[3] == pcode__BOOLEAN  ? v[3] ? ( void *) (*b[3]) : ( void *) (b[3])
                : t[3] == pcode__BYTE     ? v[3] ? ( void *) (*y[3]) : ( void *) (y[3])
                : t[3] == pcode__SHORT    ? v[3] ? ( void *) (*s[3]) : ( void *) (s[3])
                : t[3] == pcode__INTEGER  ? v[3] ? ( void *) (*i[3]) : ( void *) (i[3])
                : t[3] == pcode__LONG     ? v[3] ? ( void *) (*l[3]) : ( void *) (l[3])
                : t[3] == pcode__SINGLE   ? v[3] ? ( void *) (*k[3]) : ( void *) (k[3])
                : t[3] == pcode__DOUBLE   ? v[3] ? ( void *) (*d[3]) : ( void *) (d[3])
                :                          (p[3])
                ,
                  t[4] == pcode__BOOLEAN  ? v[4] ? ( void *) (*b[4]) : ( void *) (b[4])
                : t[4] == pcode__BYTE     ? v[4] ? ( void *) (*y[4]) : ( void *) (y[4])
                : t[4] == pcode__SHORT    ? v[4] ? ( void *) (*s[4]) : ( void *) (s[4])
                : t[4] == pcode__INTEGER  ? v[4] ? ( void *) (*i[4]) : ( void *) (i[4])
                : t[4] == pcode__LONG     ? v[4] ? ( void *) (*l[4]) : ( void *) (l[4])
                : t[4] == pcode__SINGLE   ? v[4] ? ( void *) (*k[4]) : ( void *) (k[4])
                : t[4] == pcode__DOUBLE   ? v[4] ? ( void *) (*d[4]) : ( void *) (d[4])
                :                          (p[4])
              );
              else return runtimeError(utility::con(function, " function call failed. ", ll[lib]->errorString()));
              myStack->pushBoolean(rb);
            }
            break;
          case 6:
            {
              bool_c6 c = (bool_c6) ll[lib]->resolve( function );
              if (c) rb = c (
                  t[0] == pcode__BOOLEAN  ? v[0] ? ( void *) (*b[0]) : ( void *) (b[0])
                : t[0] == pcode__BYTE     ? v[0] ? ( void *) (*y[0]) : ( void *) (y[0])
                : t[0] == pcode__SHORT    ? v[0] ? ( void *) (*s[0]) : ( void *) (s[0])
                : t[0] == pcode__INTEGER  ? v[0] ? ( void *) (*i[0]) : ( void *) (i[0])
                : t[0] == pcode__LONG     ? v[0] ? ( void *) (*l[0]) : ( void *) (l[0])
                : t[0] == pcode__SINGLE   ? v[0] ? ( void *) (*k[0]) : ( void *) (k[0])
                : t[0] == pcode__DOUBLE   ? v[0] ? ( void *) (*d[0]) : ( void *) (d[0])
                :                          (p[0])
                ,
                  t[1] == pcode__BOOLEAN  ? v[1] ? ( void *) (*b[1]) : ( void *) (b[1])
                : t[1] == pcode__BYTE     ? v[1] ? ( void *) (*y[1]) : ( void *) (y[1])
                : t[1] == pcode__SHORT    ? v[1] ? ( void *) (*s[1]) : ( void *) (s[1])
                : t[1] == pcode__INTEGER  ? v[1] ? ( void *) (*i[1]) : ( void *) (i[1])
                : t[1] == pcode__LONG     ? v[1] ? ( void *) (*l[1]) : ( void *) (l[1])
                : t[1] == pcode__SINGLE   ? v[1] ? ( void *) (*k[1]) : ( void *) (k[1])
                : t[1] == pcode__DOUBLE   ? v[1] ? ( void *) (*d[1]) : ( void *) (d[1])
                :                          (p[1])
                ,
                  t[2] == pcode__BOOLEAN  ? v[2] ? ( void *) (*b[2]) : ( void *) (b[2])
                : t[2] == pcode__BYTE     ? v[2] ? ( void *) (*y[2]) : ( void *) (y[2])
                : t[2] == pcode__SHORT    ? v[2] ? ( void *) (*s[2]) : ( void *) (s[2])
                : t[2] == pcode__INTEGER  ? v[2] ? ( void *) (*i[2]) : ( void *) (i[2])
                : t[2] == pcode__LONG     ? v[2] ? ( void *) (*l[2]) : ( void *) (l[2])
                : t[2] == pcode__SINGLE   ? v[2] ? ( void *) (*k[2]) : ( void *) (k[2])
                : t[2] == pcode__DOUBLE   ? v[2] ? ( void *) (*d[2]) : ( void *) (d[2])
                :                          (p[2])
                ,
                  t[3] == pcode__BOOLEAN  ? v[3] ? ( void *) (*b[3]) : ( void *) (b[3])
                : t[3] == pcode__BYTE     ? v[3] ? ( void *) (*y[3]) : ( void *) (y[3])
                : t[3] == pcode__SHORT    ? v[3] ? ( void *) (*s[3]) : ( void *) (s[3])
                : t[3] == pcode__INTEGER  ? v[3] ? ( void *) (*i[3]) : ( void *) (i[3])
                : t[3] == pcode__LONG     ? v[3] ? ( void *) (*l[3]) : ( void *) (l[3])
                : t[3] == pcode__SINGLE   ? v[3] ? ( void *) (*k[3]) : ( void *) (k[3])
                : t[3] == pcode__DOUBLE   ? v[3] ? ( void *) (*d[3]) : ( void *) (d[3])
                :                          (p[3])
                ,
                  t[4] == pcode__BOOLEAN  ? v[4] ? ( void *) (*b[4]) : ( void *) (b[4])
                : t[4] == pcode__BYTE     ? v[4] ? ( void *) (*y[4]) : ( void *) (y[4])
                : t[4] == pcode__SHORT    ? v[4] ? ( void *) (*s[4]) : ( void *) (s[4])
                : t[4] == pcode__INTEGER  ? v[4] ? ( void *) (*i[4]) : ( void *) (i[4])
                : t[4] == pcode__LONG     ? v[4] ? ( void *) (*l[4]) : ( void *) (l[4])
                : t[4] == pcode__SINGLE   ? v[4] ? ( void *) (*k[4]) : ( void *) (k[4])
                : t[4] == pcode__DOUBLE   ? v[4] ? ( void *) (*d[4]) : ( void *) (d[4])
                :                          (p[4])
                ,
                  t[5] == pcode__BOOLEAN  ? v[5] ? ( void *) (*b[5]) : ( void *) (b[5])
                : t[5] == pcode__BYTE     ? v[5] ? ( void *) (*y[5]) : ( void *) (y[5])
                : t[5] == pcode__SHORT    ? v[5] ? ( void *) (*s[5]) : ( void *) (s[5])
                : t[5] == pcode__INTEGER  ? v[5] ? ( void *) (*i[5]) : ( void *) (i[5])
                : t[5] == pcode__LONG     ? v[5] ? ( void *) (*l[5]) : ( void *) (l[5])
                : t[5] == pcode__SINGLE   ? v[5] ? ( void *) (*k[5]) : ( void *) (k[5])
                : t[5] == pcode__DOUBLE   ? v[5] ? ( void *) (*d[5]) : ( void *) (d[5])
                :                          (p[5])
              );
              else return runtimeError(utility::con(function, " function call failed. ", ll[lib]->errorString()));
              myStack->pushBoolean(rb);
            }
            break;
          case 7:
            {
              bool_c7 c = (bool_c7) ll[lib]->resolve( function );
              if (c) rb = c (
                  t[0] == pcode__BOOLEAN  ? v[0] ? ( void *) (*b[0]) : ( void *) (b[0])
                : t[0] == pcode__BYTE     ? v[0] ? ( void *) (*y[0]) : ( void *) (y[0])
                : t[0] == pcode__SHORT    ? v[0] ? ( void *) (*s[0]) : ( void *) (s[0])
                : t[0] == pcode__INTEGER  ? v[0] ? ( void *) (*i[0]) : ( void *) (i[0])
                : t[0] == pcode__LONG     ? v[0] ? ( void *) (*l[0]) : ( void *) (l[0])
                : t[0] == pcode__SINGLE   ? v[0] ? ( void *) (*k[0]) : ( void *) (k[0])
                : t[0] == pcode__DOUBLE   ? v[0] ? ( void *) (*d[0]) : ( void *) (d[0])
                :                          (p[0])
                ,
                  t[1] == pcode__BOOLEAN  ? v[1] ? ( void *) (*b[1]) : ( void *) (b[1])
                : t[1] == pcode__BYTE     ? v[1] ? ( void *) (*y[1]) : ( void *) (y[1])
                : t[1] == pcode__SHORT    ? v[1] ? ( void *) (*s[1]) : ( void *) (s[1])
                : t[1] == pcode__INTEGER  ? v[1] ? ( void *) (*i[1]) : ( void *) (i[1])
                : t[1] == pcode__LONG     ? v[1] ? ( void *) (*l[1]) : ( void *) (l[1])
                : t[1] == pcode__SINGLE   ? v[1] ? ( void *) (*k[1]) : ( void *) (k[1])
                : t[1] == pcode__DOUBLE   ? v[1] ? ( void *) (*d[1]) : ( void *) (d[1])
                :                          (p[1])
                ,
                  t[2] == pcode__BOOLEAN  ? v[2] ? ( void *) (*b[2]) : ( void *) (b[2])
                : t[2] == pcode__BYTE     ? v[2] ? ( void *) (*y[2]) : ( void *) (y[2])
                : t[2] == pcode__SHORT    ? v[2] ? ( void *) (*s[2]) : ( void *) (s[2])
                : t[2] == pcode__INTEGER  ? v[2] ? ( void *) (*i[2]) : ( void *) (i[2])
                : t[2] == pcode__LONG     ? v[2] ? ( void *) (*l[2]) : ( void *) (l[2])
                : t[2] == pcode__SINGLE   ? v[2] ? ( void *) (*k[2]) : ( void *) (k[2])
                : t[2] == pcode__DOUBLE   ? v[2] ? ( void *) (*d[2]) : ( void *) (d[2])
                :                          (p[2])
                ,
                  t[3] == pcode__BOOLEAN  ? v[3] ? ( void *) (*b[3]) : ( void *) (b[3])
                : t[3] == pcode__BYTE     ? v[3] ? ( void *) (*y[3]) : ( void *) (y[3])
                : t[3] == pcode__SHORT    ? v[3] ? ( void *) (*s[3]) : ( void *) (s[3])
                : t[3] == pcode__INTEGER  ? v[3] ? ( void *) (*i[3]) : ( void *) (i[3])
                : t[3] == pcode__LONG     ? v[3] ? ( void *) (*l[3]) : ( void *) (l[3])
                : t[3] == pcode__SINGLE   ? v[3] ? ( void *) (*k[3]) : ( void *) (k[3])
                : t[3] == pcode__DOUBLE   ? v[3] ? ( void *) (*d[3]) : ( void *) (d[3])
                :                          (p[3])
                ,
                  t[4] == pcode__BOOLEAN  ? v[4] ? ( void *) (*b[4]) : ( void *) (b[4])
                : t[4] == pcode__BYTE     ? v[4] ? ( void *) (*y[4]) : ( void *) (y[4])
                : t[4] == pcode__SHORT    ? v[4] ? ( void *) (*s[4]) : ( void *) (s[4])
                : t[4] == pcode__INTEGER  ? v[4] ? ( void *) (*i[4]) : ( void *) (i[4])
                : t[4] == pcode__LONG     ? v[4] ? ( void *) (*l[4]) : ( void *) (l[4])
                : t[4] == pcode__SINGLE   ? v[4] ? ( void *) (*k[4]) : ( void *) (k[4])
                : t[4] == pcode__DOUBLE   ? v[4] ? ( void *) (*d[4]) : ( void *) (d[4])
                :                          (p[4])
                ,
                  t[5] == pcode__BOOLEAN  ? v[5] ? ( void *) (*b[5]) : ( void *) (b[5])
                : t[5] == pcode__BYTE     ? v[5] ? ( void *) (*y[5]) : ( void *) (y[5])
                : t[5] == pcode__SHORT    ? v[5] ? ( void *) (*s[5]) : ( void *) (s[5])
                : t[5] == pcode__INTEGER  ? v[5] ? ( void *) (*i[5]) : ( void *) (i[5])
                : t[5] == pcode__LONG     ? v[5] ? ( void *) (*l[5]) : ( void *) (l[5])
                : t[5] == pcode__SINGLE   ? v[5] ? ( void *) (*k[5]) : ( void *) (k[5])
                : t[5] == pcode__DOUBLE   ? v[5] ? ( void *) (*d[5]) : ( void *) (d[5])
                :                          (p[5])
                ,
                  t[6] == pcode__BOOLEAN  ? v[6] ? ( void *) (*b[6]) : ( void *) (b[6])
                : t[6] == pcode__BYTE     ? v[6] ? ( void *) (*y[6]) : ( void *) (y[6])
                : t[6] == pcode__SHORT    ? v[6] ? ( void *) (*s[6]) : ( void *) (s[6])
                : t[6] == pcode__INTEGER  ? v[6] ? ( void *) (*i[6]) : ( void *) (i[6])
                : t[6] == pcode__LONG     ? v[6] ? ( void *) (*l[6]) : ( void *) (l[6])
                : t[6] == pcode__SINGLE   ? v[6] ? ( void *) (*k[6]) : ( void *) (k[6])
                : t[6] == pcode__DOUBLE   ? v[6] ? ( void *) (*d[6]) : ( void *) (d[6])
                :                          (p[6])
              );
              else return runtimeError(utility::con(function, " function call failed. ", ll[lib]->errorString()));
              myStack->pushBoolean(rb);
            }
            break;
          case 8:
            {
              bool_c8 c = (bool_c8) ll[lib]->resolve( function );
              if (c) rb = c (
                  t[0] == pcode__BOOLEAN  ? v[0] ? ( void *) (*b[0]) : ( void *) (b[0])
                : t[0] == pcode__BYTE     ? v[0] ? ( void *) (*y[0]) : ( void *) (y[0])
                : t[0] == pcode__SHORT    ? v[0] ? ( void *) (*s[0]) : ( void *) (s[0])
                : t[0] == pcode__INTEGER  ? v[0] ? ( void *) (*i[0]) : ( void *) (i[0])
                : t[0] == pcode__LONG     ? v[0] ? ( void *) (*l[0]) : ( void *) (l[0])
                : t[0] == pcode__SINGLE   ? v[0] ? ( void *) (*k[0]) : ( void *) (k[0])
                : t[0] == pcode__DOUBLE   ? v[0] ? ( void *) (*d[0]) : ( void *) (d[0])
                :                          (p[0])
                ,
                  t[1] == pcode__BOOLEAN  ? v[1] ? ( void *) (*b[1]) : ( void *) (b[1])
                : t[1] == pcode__BYTE     ? v[1] ? ( void *) (*y[1]) : ( void *) (y[1])
                : t[1] == pcode__SHORT    ? v[1] ? ( void *) (*s[1]) : ( void *) (s[1])
                : t[1] == pcode__INTEGER  ? v[1] ? ( void *) (*i[1]) : ( void *) (i[1])
                : t[1] == pcode__LONG     ? v[1] ? ( void *) (*l[1]) : ( void *) (l[1])
                : t[1] == pcode__SINGLE   ? v[1] ? ( void *) (*k[1]) : ( void *) (k[1])
                : t[1] == pcode__DOUBLE   ? v[1] ? ( void *) (*d[1]) : ( void *) (d[1])
                :                          (p[1])
                ,
                  t[2] == pcode__BOOLEAN  ? v[2] ? ( void *) (*b[2]) : ( void *) (b[2])
                : t[2] == pcode__BYTE     ? v[2] ? ( void *) (*y[2]) : ( void *) (y[2])
                : t[2] == pcode__SHORT    ? v[2] ? ( void *) (*s[2]) : ( void *) (s[2])
                : t[2] == pcode__INTEGER  ? v[2] ? ( void *) (*i[2]) : ( void *) (i[2])
                : t[2] == pcode__LONG     ? v[2] ? ( void *) (*l[2]) : ( void *) (l[2])
                : t[2] == pcode__SINGLE   ? v[2] ? ( void *) (*k[2]) : ( void *) (k[2])
                : t[2] == pcode__DOUBLE   ? v[2] ? ( void *) (*d[2]) : ( void *) (d[2])
                :                          (p[2])
                ,
                  t[3] == pcode__BOOLEAN  ? v[3] ? ( void *) (*b[3]) : ( void *) (b[3])
                : t[3] == pcode__BYTE     ? v[3] ? ( void *) (*y[3]) : ( void *) (y[3])
                : t[3] == pcode__SHORT    ? v[3] ? ( void *) (*s[3]) : ( void *) (s[3])
                : t[3] == pcode__INTEGER  ? v[3] ? ( void *) (*i[3]) : ( void *) (i[3])
                : t[3] == pcode__LONG     ? v[3] ? ( void *) (*l[3]) : ( void *) (l[3])
                : t[3] == pcode__SINGLE   ? v[3] ? ( void *) (*k[3]) : ( void *) (k[3])
                : t[3] == pcode__DOUBLE   ? v[3] ? ( void *) (*d[3]) : ( void *) (d[3])
                :                          (p[3])
                ,
                  t[4] == pcode__BOOLEAN  ? v[4] ? ( void *) (*b[4]) : ( void *) (b[4])
                : t[4] == pcode__BYTE     ? v[4] ? ( void *) (*y[4]) : ( void *) (y[4])
                : t[4] == pcode__SHORT    ? v[4] ? ( void *) (*s[4]) : ( void *) (s[4])
                : t[4] == pcode__INTEGER  ? v[4] ? ( void *) (*i[4]) : ( void *) (i[4])
                : t[4] == pcode__LONG     ? v[4] ? ( void *) (*l[4]) : ( void *) (l[4])
                : t[4] == pcode__SINGLE   ? v[4] ? ( void *) (*k[4]) : ( void *) (k[4])
                : t[4] == pcode__DOUBLE   ? v[4] ? ( void *) (*d[4]) : ( void *) (d[4])
                :                          (p[4])
                ,
                  t[5] == pcode__BOOLEAN  ? v[5] ? ( void *) (*b[5]) : ( void *) (b[5])
                : t[5] == pcode__BYTE     ? v[5] ? ( void *) (*y[5]) : ( void *) (y[5])
                : t[5] == pcode__SHORT    ? v[5] ? ( void *) (*s[5]) : ( void *) (s[5])
                : t[5] == pcode__INTEGER  ? v[5] ? ( void *) (*i[5]) : ( void *) (i[5])
                : t[5] == pcode__LONG     ? v[5] ? ( void *) (*l[5]) : ( void *) (l[5])
                : t[5] == pcode__SINGLE   ? v[5] ? ( void *) (*k[5]) : ( void *) (k[5])
                : t[5] == pcode__DOUBLE   ? v[5] ? ( void *) (*d[5]) : ( void *) (d[5])
                :                          (p[5])
                ,
                  t[6] == pcode__BOOLEAN  ? v[6] ? ( void *) (*b[6]) : ( void *) (b[6])
                : t[6] == pcode__BYTE     ? v[6] ? ( void *) (*y[6]) : ( void *) (y[6])
                : t[6] == pcode__SHORT    ? v[6] ? ( void *) (*s[6]) : ( void *) (s[6])
                : t[6] == pcode__INTEGER  ? v[6] ? ( void *) (*i[6]) : ( void *) (i[6])
                : t[6] == pcode__LONG     ? v[6] ? ( void *) (*l[6]) : ( void *) (l[6])
                : t[6] == pcode__SINGLE   ? v[6] ? ( void *) (*k[6]) : ( void *) (k[6])
                : t[6] == pcode__DOUBLE   ? v[6] ? ( void *) (*d[6]) : ( void *) (d[6])
                :                          (p[6])
                ,
                  t[7] == pcode__BOOLEAN  ? v[7] ? ( void *) (*b[7]) : ( void *) (b[7])
                : t[7] == pcode__BYTE     ? v[7] ? ( void *) (*y[7]) : ( void *) (y[7])
                : t[7] == pcode__SHORT    ? v[7] ? ( void *) (*s[7]) : ( void *) (s[7])
                : t[7] == pcode__INTEGER  ? v[7] ? ( void *) (*i[7]) : ( void *) (i[7])
                : t[7] == pcode__LONG     ? v[7] ? ( void *) (*l[7]) : ( void *) (l[7])
                : t[7] == pcode__SINGLE   ? v[7] ? ( void *) (*k[7]) : ( void *) (k[7])
                : t[7] == pcode__DOUBLE   ? v[7] ? ( void *) (*d[7]) : ( void *) (d[7])
                :                          (p[7])
              );
              else return runtimeError(utility::con(function, " function call failed. ", ll[lib]->errorString()));
              myStack->pushBoolean(rb);
            }
            break;
          case 9:
            {
              bool_c9 c = (bool_c9) ll[lib]->resolve( function );
              if (c) rb = c (
                  t[0] == pcode__BOOLEAN  ? v[0] ? ( void *) (*b[0]) : ( void *) (b[0])
                : t[0] == pcode__BYTE     ? v[0] ? ( void *) (*y[0]) : ( void *) (y[0])
                : t[0] == pcode__SHORT    ? v[0] ? ( void *) (*s[0]) : ( void *) (s[0])
                : t[0] == pcode__INTEGER  ? v[0] ? ( void *) (*i[0]) : ( void *) (i[0])
                : t[0] == pcode__LONG     ? v[0] ? ( void *) (*l[0]) : ( void *) (l[0])
                : t[0] == pcode__SINGLE   ? v[0] ? ( void *) (*k[0]) : ( void *) (k[0])
                : t[0] == pcode__DOUBLE   ? v[0] ? ( void *) (*d[0]) : ( void *) (d[0])
                :                          (p[0])
                ,
                  t[1] == pcode__BOOLEAN  ? v[1] ? ( void *) (*b[1]) : ( void *) (b[1])
                : t[1] == pcode__BYTE     ? v[1] ? ( void *) (*y[1]) : ( void *) (y[1])
                : t[1] == pcode__SHORT    ? v[1] ? ( void *) (*s[1]) : ( void *) (s[1])
                : t[1] == pcode__INTEGER  ? v[1] ? ( void *) (*i[1]) : ( void *) (i[1])
                : t[1] == pcode__LONG     ? v[1] ? ( void *) (*l[1]) : ( void *) (l[1])
                : t[1] == pcode__SINGLE   ? v[1] ? ( void *) (*k[1]) : ( void *) (k[1])
                : t[1] == pcode__DOUBLE   ? v[1] ? ( void *) (*d[1]) : ( void *) (d[1])
                :                          (p[1])
                ,
                  t[2] == pcode__BOOLEAN  ? v[2] ? ( void *) (*b[2]) : ( void *) (b[2])
                : t[2] == pcode__BYTE     ? v[2] ? ( void *) (*y[2]) : ( void *) (y[2])
                : t[2] == pcode__SHORT    ? v[2] ? ( void *) (*s[2]) : ( void *) (s[2])
                : t[2] == pcode__INTEGER  ? v[2] ? ( void *) (*i[2]) : ( void *) (i[2])
                : t[2] == pcode__LONG     ? v[2] ? ( void *) (*l[2]) : ( void *) (l[2])
                : t[2] == pcode__SINGLE   ? v[2] ? ( void *) (*k[2]) : ( void *) (k[2])
                : t[2] == pcode__DOUBLE   ? v[2] ? ( void *) (*d[2]) : ( void *) (d[2])
                :                          (p[2])
                ,
                  t[3] == pcode__BOOLEAN  ? v[3] ? ( void *) (*b[3]) : ( void *) (b[3])
                : t[3] == pcode__BYTE     ? v[3] ? ( void *) (*y[3]) : ( void *) (y[3])
                : t[3] == pcode__SHORT    ? v[3] ? ( void *) (*s[3]) : ( void *) (s[3])
                : t[3] == pcode__INTEGER  ? v[3] ? ( void *) (*i[3]) : ( void *) (i[3])
                : t[3] == pcode__LONG     ? v[3] ? ( void *) (*l[3]) : ( void *) (l[3])
                : t[3] == pcode__SINGLE   ? v[3] ? ( void *) (*k[3]) : ( void *) (k[3])
                : t[3] == pcode__DOUBLE   ? v[3] ? ( void *) (*d[3]) : ( void *) (d[3])
                :                          (p[3])
                ,
                  t[4] == pcode__BOOLEAN  ? v[4] ? ( void *) (*b[4]) : ( void *) (b[4])
                : t[4] == pcode__BYTE     ? v[4] ? ( void *) (*y[4]) : ( void *) (y[4])
                : t[4] == pcode__SHORT    ? v[4] ? ( void *) (*s[4]) : ( void *) (s[4])
                : t[4] == pcode__INTEGER  ? v[4] ? ( void *) (*i[4]) : ( void *) (i[4])
                : t[4] == pcode__LONG     ? v[4] ? ( void *) (*l[4]) : ( void *) (l[4])
                : t[4] == pcode__SINGLE   ? v[4] ? ( void *) (*k[4]) : ( void *) (k[4])
                : t[4] == pcode__DOUBLE   ? v[4] ? ( void *) (*d[4]) : ( void *) (d[4])
                :                          (p[4])
                ,
                  t[5] == pcode__BOOLEAN  ? v[5] ? ( void *) (*b[5]) : ( void *) (b[5])
                : t[5] == pcode__BYTE     ? v[5] ? ( void *) (*y[5]) : ( void *) (y[5])
                : t[5] == pcode__SHORT    ? v[5] ? ( void *) (*s[5]) : ( void *) (s[5])
                : t[5] == pcode__INTEGER  ? v[5] ? ( void *) (*i[5]) : ( void *) (i[5])
                : t[5] == pcode__LONG     ? v[5] ? ( void *) (*l[5]) : ( void *) (l[5])
                : t[5] == pcode__SINGLE   ? v[5] ? ( void *) (*k[5]) : ( void *) (k[5])
                : t[5] == pcode__DOUBLE   ? v[5] ? ( void *) (*d[5]) : ( void *) (d[5])
                :                          (p[5])
                ,
                  t[6] == pcode__BOOLEAN  ? v[6] ? ( void *) (*b[6]) : ( void *) (b[6])
                : t[6] == pcode__BYTE     ? v[6] ? ( void *) (*y[6]) : ( void *) (y[6])
                : t[6] == pcode__SHORT    ? v[6] ? ( void *) (*s[6]) : ( void *) (s[6])
                : t[6] == pcode__INTEGER  ? v[6] ? ( void *) (*i[6]) : ( void *) (i[6])
                : t[6] == pcode__LONG     ? v[6] ? ( void *) (*l[6]) : ( void *) (l[6])
                : t[6] == pcode__SINGLE   ? v[6] ? ( void *) (*k[6]) : ( void *) (k[6])
                : t[6] == pcode__DOUBLE   ? v[6] ? ( void *) (*d[6]) : ( void *) (d[6])
                :                          (p[6])
                ,
                  t[7] == pcode__BOOLEAN  ? v[7] ? ( void *) (*b[7]) : ( void *) (b[7])
                : t[7] == pcode__BYTE     ? v[7] ? ( void *) (*y[7]) : ( void *) (y[7])
                : t[7] == pcode__SHORT    ? v[7] ? ( void *) (*s[7]) : ( void *) (s[7])
                : t[7] == pcode__INTEGER  ? v[7] ? ( void *) (*i[7]) : ( void *) (i[7])
                : t[7] == pcode__LONG     ? v[7] ? ( void *) (*l[7]) : ( void *) (l[7])
                : t[7] == pcode__SINGLE   ? v[7] ? ( void *) (*k[7]) : ( void *) (k[7])
                : t[7] == pcode__DOUBLE   ? v[7] ? ( void *) (*d[7]) : ( void *) (d[7])
                :                          (p[7])
                ,
                  t[8] == pcode__BOOLEAN  ? v[8] ? ( void *) (*b[8]) : ( void *) (b[8])
                : t[8] == pcode__BYTE     ? v[8] ? ( void *) (*y[8]) : ( void *) (y[8])
                : t[8] == pcode__SHORT    ? v[8] ? ( void *) (*s[8]) : ( void *) (s[8])
                : t[8] == pcode__INTEGER  ? v[8] ? ( void *) (*i[8]) : ( void *) (i[8])
                : t[8] == pcode__LONG     ? v[8] ? ( void *) (*l[8]) : ( void *) (l[8])
                : t[8] == pcode__SINGLE   ? v[8] ? ( void *) (*k[8]) : ( void *) (k[8])
                : t[8] == pcode__DOUBLE   ? v[8] ? ( void *) (*d[8]) : ( void *) (d[8])
                :                          (p[8])
              );
              else return runtimeError(utility::con(function, " function call failed. ", ll[lib]->errorString()));
              myStack->pushBoolean(rb);
            }
            break;
          default:
            return runtimeError(utility::con(function, ": Too much arguments (max. 9 allowed) when calling declare function."));
            break;
         }
         break;
       case pcode__BYTE:
        switch(count){
          case 0:
            {
              byte_c0 c = (byte_c0) ll[lib]->resolve( function );
              if (c) ry = c (
              );
              else return runtimeError(utility::con(function, " function call failed. ", ll[lib]->errorString()));
              myStack->pushByte(ry);
            }
            break;
          case 1:
            {
              byte_c1 c = (byte_c1) ll[lib]->resolve( function );
              if (c) ry = c (
                  t[0] == pcode__BOOLEAN  ? v[0] ? ( void *) (*b[0]) : ( void *) (b[0])
                : t[0] == pcode__BYTE     ? v[0] ? ( void *) (*y[0]) : ( void *) (y[0])
                : t[0] == pcode__SHORT    ? v[0] ? ( void *) (*s[0]) : ( void *) (s[0])
                : t[0] == pcode__INTEGER  ? v[0] ? ( void *) (*i[0]) : ( void *) (i[0])
                : t[0] == pcode__LONG     ? v[0] ? ( void *) (*l[0]) : ( void *) (l[0])
                : t[0] == pcode__SINGLE   ? v[0] ? ( void *) (*k[0]) : ( void *) (k[0])
                : t[0] == pcode__DOUBLE   ? v[0] ? ( void *) (*d[0]) : ( void *) (d[0])
                :                          (p[0])
              );
              else return runtimeError(utility::con(function, " function call failed. ", ll[lib]->errorString()));
              myStack->pushByte(ry);
            }
            break;
          case 2:
            {
              byte_c2 c = (byte_c2) ll[lib]->resolve( function );
              if (c) ry = c (
                  t[0] == pcode__BOOLEAN  ? v[0] ? ( void *) (*b[0]) : ( void *) (b[0])
                : t[0] == pcode__BYTE     ? v[0] ? ( void *) (*y[0]) : ( void *) (y[0])
                : t[0] == pcode__SHORT    ? v[0] ? ( void *) (*s[0]) : ( void *) (s[0])
                : t[0] == pcode__INTEGER  ? v[0] ? ( void *) (*i[0]) : ( void *) (i[0])
                : t[0] == pcode__LONG     ? v[0] ? ( void *) (*l[0]) : ( void *) (l[0])
                : t[0] == pcode__SINGLE   ? v[0] ? ( void *) (*k[0]) : ( void *) (k[0])
                : t[0] == pcode__DOUBLE   ? v[0] ? ( void *) (*d[0]) : ( void *) (d[0])
                :                          (p[0])
                ,
                  t[1] == pcode__BOOLEAN  ? v[1] ? ( void *) (*b[1]) : ( void *) (b[1])
                : t[1] == pcode__BYTE     ? v[1] ? ( void *) (*y[1]) : ( void *) (y[1])
                : t[1] == pcode__SHORT    ? v[1] ? ( void *) (*s[1]) : ( void *) (s[1])
                : t[1] == pcode__INTEGER  ? v[1] ? ( void *) (*i[1]) : ( void *) (i[1])
                : t[1] == pcode__LONG     ? v[1] ? ( void *) (*l[1]) : ( void *) (l[1])
                : t[1] == pcode__SINGLE   ? v[1] ? ( void *) (*k[1]) : ( void *) (k[1])
                : t[1] == pcode__DOUBLE   ? v[1] ? ( void *) (*d[1]) : ( void *) (d[1])
                :                          (p[1])
              );
              else return runtimeError(utility::con(function, " function call failed. ", ll[lib]->errorString()));
              myStack->pushByte(ry);
            }
            break;
          case 3:
            {
              byte_c3 c = (byte_c3) ll[lib]->resolve( function );
              if (c) ry = c (
                  t[0] == pcode__BOOLEAN  ? v[0] ? ( void *) (*b[0]) : ( void *) (b[0])
                : t[0] == pcode__BYTE     ? v[0] ? ( void *) (*y[0]) : ( void *) (y[0])
                : t[0] == pcode__SHORT    ? v[0] ? ( void *) (*s[0]) : ( void *) (s[0])
                : t[0] == pcode__INTEGER  ? v[0] ? ( void *) (*i[0]) : ( void *) (i[0])
                : t[0] == pcode__LONG     ? v[0] ? ( void *) (*l[0]) : ( void *) (l[0])
                : t[0] == pcode__SINGLE   ? v[0] ? ( void *) (*k[0]) : ( void *) (k[0])
                : t[0] == pcode__DOUBLE   ? v[0] ? ( void *) (*d[0]) : ( void *) (d[0])
                :                          (p[0])
                ,
                  t[1] == pcode__BOOLEAN  ? v[1] ? ( void *) (*b[1]) : ( void *) (b[1])
                : t[1] == pcode__BYTE     ? v[1] ? ( void *) (*y[1]) : ( void *) (y[1])
                : t[1] == pcode__SHORT    ? v[1] ? ( void *) (*s[1]) : ( void *) (s[1])
                : t[1] == pcode__INTEGER  ? v[1] ? ( void *) (*i[1]) : ( void *) (i[1])
                : t[1] == pcode__LONG     ? v[1] ? ( void *) (*l[1]) : ( void *) (l[1])
                : t[1] == pcode__SINGLE   ? v[1] ? ( void *) (*k[1]) : ( void *) (k[1])
                : t[1] == pcode__DOUBLE   ? v[1] ? ( void *) (*d[1]) : ( void *) (d[1])
                :                          (p[1])
                ,
                  t[2] == pcode__BOOLEAN  ? v[2] ? ( void *) (*b[2]) : ( void *) (b[2])
                : t[2] == pcode__BYTE     ? v[2] ? ( void *) (*y[2]) : ( void *) (y[2])
                : t[2] == pcode__SHORT    ? v[2] ? ( void *) (*s[2]) : ( void *) (s[2])
                : t[2] == pcode__INTEGER  ? v[2] ? ( void *) (*i[2]) : ( void *) (i[2])
                : t[2] == pcode__LONG     ? v[2] ? ( void *) (*l[2]) : ( void *) (l[2])
                : t[2] == pcode__SINGLE   ? v[2] ? ( void *) (*k[2]) : ( void *) (k[2])
                : t[2] == pcode__DOUBLE   ? v[2] ? ( void *) (*d[2]) : ( void *) (d[2])
                :                          (p[2])
              );
              else return runtimeError(utility::con(function, " function call failed. ", ll[lib]->errorString()));
              myStack->pushByte(ry);
            }
            break;
          case 4:
            {
              byte_c4 c = (byte_c4) ll[lib]->resolve( function );
              if (c) ry = c (
                  t[0] == pcode__BOOLEAN  ? v[0] ? ( void *) (*b[0]) : ( void *) (b[0])
                : t[0] == pcode__BYTE     ? v[0] ? ( void *) (*y[0]) : ( void *) (y[0])
                : t[0] == pcode__SHORT    ? v[0] ? ( void *) (*s[0]) : ( void *) (s[0])
                : t[0] == pcode__INTEGER  ? v[0] ? ( void *) (*i[0]) : ( void *) (i[0])
                : t[0] == pcode__LONG     ? v[0] ? ( void *) (*l[0]) : ( void *) (l[0])
                : t[0] == pcode__SINGLE   ? v[0] ? ( void *) (*k[0]) : ( void *) (k[0])
                : t[0] == pcode__DOUBLE   ? v[0] ? ( void *) (*d[0]) : ( void *) (d[0])
                :                          (p[0])
                ,
                  t[1] == pcode__BOOLEAN  ? v[1] ? ( void *) (*b[1]) : ( void *) (b[1])
                : t[1] == pcode__BYTE     ? v[1] ? ( void *) (*y[1]) : ( void *) (y[1])
                : t[1] == pcode__SHORT    ? v[1] ? ( void *) (*s[1]) : ( void *) (s[1])
                : t[1] == pcode__INTEGER  ? v[1] ? ( void *) (*i[1]) : ( void *) (i[1])
                : t[1] == pcode__LONG     ? v[1] ? ( void *) (*l[1]) : ( void *) (l[1])
                : t[1] == pcode__SINGLE   ? v[1] ? ( void *) (*k[1]) : ( void *) (k[1])
                : t[1] == pcode__DOUBLE   ? v[1] ? ( void *) (*d[1]) : ( void *) (d[1])
                :                          (p[1])
                ,
                  t[2] == pcode__BOOLEAN  ? v[2] ? ( void *) (*b[2]) : ( void *) (b[2])
                : t[2] == pcode__BYTE     ? v[2] ? ( void *) (*y[2]) : ( void *) (y[2])
                : t[2] == pcode__SHORT    ? v[2] ? ( void *) (*s[2]) : ( void *) (s[2])
                : t[2] == pcode__INTEGER  ? v[2] ? ( void *) (*i[2]) : ( void *) (i[2])
                : t[2] == pcode__LONG     ? v[2] ? ( void *) (*l[2]) : ( void *) (l[2])
                : t[2] == pcode__SINGLE   ? v[2] ? ( void *) (*k[2]) : ( void *) (k[2])
                : t[2] == pcode__DOUBLE   ? v[2] ? ( void *) (*d[2]) : ( void *) (d[2])
                :                          (p[2])
                ,
                  t[3] == pcode__BOOLEAN  ? v[3] ? ( void *) (*b[3]) : ( void *) (b[3])
                : t[3] == pcode__BYTE     ? v[3] ? ( void *) (*y[3]) : ( void *) (y[3])
                : t[3] == pcode__SHORT    ? v[3] ? ( void *) (*s[3]) : ( void *) (s[3])
                : t[3] == pcode__INTEGER  ? v[3] ? ( void *) (*i[3]) : ( void *) (i[3])
                : t[3] == pcode__LONG     ? v[3] ? ( void *) (*l[3]) : ( void *) (l[3])
                : t[3] == pcode__SINGLE   ? v[3] ? ( void *) (*k[3]) : ( void *) (k[3])
                : t[3] == pcode__DOUBLE   ? v[3] ? ( void *) (*d[3]) : ( void *) (d[3])
                :                          (p[3])
              );
              else return runtimeError(utility::con(function, " function call failed. ", ll[lib]->errorString()));
              myStack->pushByte(ry);
            }
            break;
          case 5:
            {
              byte_c5 c = (byte_c5) ll[lib]->resolve( function );
              if (c) ry = c (
                  t[0] == pcode__BOOLEAN  ? v[0] ? ( void *) (*b[0]) : ( void *) (b[0])
                : t[0] == pcode__BYTE     ? v[0] ? ( void *) (*y[0]) : ( void *) (y[0])
                : t[0] == pcode__SHORT    ? v[0] ? ( void *) (*s[0]) : ( void *) (s[0])
                : t[0] == pcode__INTEGER  ? v[0] ? ( void *) (*i[0]) : ( void *) (i[0])
                : t[0] == pcode__LONG     ? v[0] ? ( void *) (*l[0]) : ( void *) (l[0])
                : t[0] == pcode__SINGLE   ? v[0] ? ( void *) (*k[0]) : ( void *) (k[0])
                : t[0] == pcode__DOUBLE   ? v[0] ? ( void *) (*d[0]) : ( void *) (d[0])
                :                          (p[0])
                ,
                  t[1] == pcode__BOOLEAN  ? v[1] ? ( void *) (*b[1]) : ( void *) (b[1])
                : t[1] == pcode__BYTE     ? v[1] ? ( void *) (*y[1]) : ( void *) (y[1])
                : t[1] == pcode__SHORT    ? v[1] ? ( void *) (*s[1]) : ( void *) (s[1])
                : t[1] == pcode__INTEGER  ? v[1] ? ( void *) (*i[1]) : ( void *) (i[1])
                : t[1] == pcode__LONG     ? v[1] ? ( void *) (*l[1]) : ( void *) (l[1])
                : t[1] == pcode__SINGLE   ? v[1] ? ( void *) (*k[1]) : ( void *) (k[1])
                : t[1] == pcode__DOUBLE   ? v[1] ? ( void *) (*d[1]) : ( void *) (d[1])
                :                          (p[1])
                ,
                  t[2] == pcode__BOOLEAN  ? v[2] ? ( void *) (*b[2]) : ( void *) (b[2])
                : t[2] == pcode__BYTE     ? v[2] ? ( void *) (*y[2]) : ( void *) (y[2])
                : t[2] == pcode__SHORT    ? v[2] ? ( void *) (*s[2]) : ( void *) (s[2])
                : t[2] == pcode__INTEGER  ? v[2] ? ( void *) (*i[2]) : ( void *) (i[2])
                : t[2] == pcode__LONG     ? v[2] ? ( void *) (*l[2]) : ( void *) (l[2])
                : t[2] == pcode__SINGLE   ? v[2] ? ( void *) (*k[2]) : ( void *) (k[2])
                : t[2] == pcode__DOUBLE   ? v[2] ? ( void *) (*d[2]) : ( void *) (d[2])
                :                          (p[2])
                ,
                  t[3] == pcode__BOOLEAN  ? v[3] ? ( void *) (*b[3]) : ( void *) (b[3])
                : t[3] == pcode__BYTE     ? v[3] ? ( void *) (*y[3]) : ( void *) (y[3])
                : t[3] == pcode__SHORT    ? v[3] ? ( void *) (*s[3]) : ( void *) (s[3])
                : t[3] == pcode__INTEGER  ? v[3] ? ( void *) (*i[3]) : ( void *) (i[3])
                : t[3] == pcode__LONG     ? v[3] ? ( void *) (*l[3]) : ( void *) (l[3])
                : t[3] == pcode__SINGLE   ? v[3] ? ( void *) (*k[3]) : ( void *) (k[3])
                : t[3] == pcode__DOUBLE   ? v[3] ? ( void *) (*d[3]) : ( void *) (d[3])
                :                          (p[3])
                ,
                  t[4] == pcode__BOOLEAN  ? v[4] ? ( void *) (*b[4]) : ( void *) (b[4])
                : t[4] == pcode__BYTE     ? v[4] ? ( void *) (*y[4]) : ( void *) (y[4])
                : t[4] == pcode__SHORT    ? v[4] ? ( void *) (*s[4]) : ( void *) (s[4])
                : t[4] == pcode__INTEGER  ? v[4] ? ( void *) (*i[4]) : ( void *) (i[4])
                : t[4] == pcode__LONG     ? v[4] ? ( void *) (*l[4]) : ( void *) (l[4])
                : t[4] == pcode__SINGLE   ? v[4] ? ( void *) (*k[4]) : ( void *) (k[4])
                : t[4] == pcode__DOUBLE   ? v[4] ? ( void *) (*d[4]) : ( void *) (d[4])
                :                          (p[4])
              );
              else return runtimeError(utility::con(function, " function call failed. ", ll[lib]->errorString()));
              myStack->pushByte(ry);
            }
            break;
          case 6:
            {
              byte_c6 c = (byte_c6) ll[lib]->resolve( function );
              if (c) ry = c (
                  t[0] == pcode__BOOLEAN  ? v[0] ? ( void *) (*b[0]) : ( void *) (b[0])
                : t[0] == pcode__BYTE     ? v[0] ? ( void *) (*y[0]) : ( void *) (y[0])
                : t[0] == pcode__SHORT    ? v[0] ? ( void *) (*s[0]) : ( void *) (s[0])
                : t[0] == pcode__INTEGER  ? v[0] ? ( void *) (*i[0]) : ( void *) (i[0])
                : t[0] == pcode__LONG     ? v[0] ? ( void *) (*l[0]) : ( void *) (l[0])
                : t[0] == pcode__SINGLE   ? v[0] ? ( void *) (*k[0]) : ( void *) (k[0])
                : t[0] == pcode__DOUBLE   ? v[0] ? ( void *) (*d[0]) : ( void *) (d[0])
                :                          (p[0])
                ,
                  t[1] == pcode__BOOLEAN  ? v[1] ? ( void *) (*b[1]) : ( void *) (b[1])
                : t[1] == pcode__BYTE     ? v[1] ? ( void *) (*y[1]) : ( void *) (y[1])
                : t[1] == pcode__SHORT    ? v[1] ? ( void *) (*s[1]) : ( void *) (s[1])
                : t[1] == pcode__INTEGER  ? v[1] ? ( void *) (*i[1]) : ( void *) (i[1])
                : t[1] == pcode__LONG     ? v[1] ? ( void *) (*l[1]) : ( void *) (l[1])
                : t[1] == pcode__SINGLE   ? v[1] ? ( void *) (*k[1]) : ( void *) (k[1])
                : t[1] == pcode__DOUBLE   ? v[1] ? ( void *) (*d[1]) : ( void *) (d[1])
                :                          (p[1])
                ,
                  t[2] == pcode__BOOLEAN  ? v[2] ? ( void *) (*b[2]) : ( void *) (b[2])
                : t[2] == pcode__BYTE     ? v[2] ? ( void *) (*y[2]) : ( void *) (y[2])
                : t[2] == pcode__SHORT    ? v[2] ? ( void *) (*s[2]) : ( void *) (s[2])
                : t[2] == pcode__INTEGER  ? v[2] ? ( void *) (*i[2]) : ( void *) (i[2])
                : t[2] == pcode__LONG     ? v[2] ? ( void *) (*l[2]) : ( void *) (l[2])
                : t[2] == pcode__SINGLE   ? v[2] ? ( void *) (*k[2]) : ( void *) (k[2])
                : t[2] == pcode__DOUBLE   ? v[2] ? ( void *) (*d[2]) : ( void *) (d[2])
                :                          (p[2])
                ,
                  t[3] == pcode__BOOLEAN  ? v[3] ? ( void *) (*b[3]) : ( void *) (b[3])
                : t[3] == pcode__BYTE     ? v[3] ? ( void *) (*y[3]) : ( void *) (y[3])
                : t[3] == pcode__SHORT    ? v[3] ? ( void *) (*s[3]) : ( void *) (s[3])
                : t[3] == pcode__INTEGER  ? v[3] ? ( void *) (*i[3]) : ( void *) (i[3])
                : t[3] == pcode__LONG     ? v[3] ? ( void *) (*l[3]) : ( void *) (l[3])
                : t[3] == pcode__SINGLE   ? v[3] ? ( void *) (*k[3]) : ( void *) (k[3])
                : t[3] == pcode__DOUBLE   ? v[3] ? ( void *) (*d[3]) : ( void *) (d[3])
                :                          (p[3])
                ,
                  t[4] == pcode__BOOLEAN  ? v[4] ? ( void *) (*b[4]) : ( void *) (b[4])
                : t[4] == pcode__BYTE     ? v[4] ? ( void *) (*y[4]) : ( void *) (y[4])
                : t[4] == pcode__SHORT    ? v[4] ? ( void *) (*s[4]) : ( void *) (s[4])
                : t[4] == pcode__INTEGER  ? v[4] ? ( void *) (*i[4]) : ( void *) (i[4])
                : t[4] == pcode__LONG     ? v[4] ? ( void *) (*l[4]) : ( void *) (l[4])
                : t[4] == pcode__SINGLE   ? v[4] ? ( void *) (*k[4]) : ( void *) (k[4])
                : t[4] == pcode__DOUBLE   ? v[4] ? ( void *) (*d[4]) : ( void *) (d[4])
                :                          (p[4])
                ,
                  t[5] == pcode__BOOLEAN  ? v[5] ? ( void *) (*b[5]) : ( void *) (b[5])
                : t[5] == pcode__BYTE     ? v[5] ? ( void *) (*y[5]) : ( void *) (y[5])
                : t[5] == pcode__SHORT    ? v[5] ? ( void *) (*s[5]) : ( void *) (s[5])
                : t[5] == pcode__INTEGER  ? v[5] ? ( void *) (*i[5]) : ( void *) (i[5])
                : t[5] == pcode__LONG     ? v[5] ? ( void *) (*l[5]) : ( void *) (l[5])
                : t[5] == pcode__SINGLE   ? v[5] ? ( void *) (*k[5]) : ( void *) (k[5])
                : t[5] == pcode__DOUBLE   ? v[5] ? ( void *) (*d[5]) : ( void *) (d[5])
                :                          (p[5])
              );
              else return runtimeError(utility::con(function, " function call failed. ", ll[lib]->errorString()));
              myStack->pushByte(ry);
            }
            break;
          case 7:
            {
              byte_c7 c = (byte_c7) ll[lib]->resolve( function );
              if (c) ry = c (
                  t[0] == pcode__BOOLEAN  ? v[0] ? ( void *) (*b[0]) : ( void *) (b[0])
                : t[0] == pcode__BYTE     ? v[0] ? ( void *) (*y[0]) : ( void *) (y[0])
                : t[0] == pcode__SHORT    ? v[0] ? ( void *) (*s[0]) : ( void *) (s[0])
                : t[0] == pcode__INTEGER  ? v[0] ? ( void *) (*i[0]) : ( void *) (i[0])
                : t[0] == pcode__LONG     ? v[0] ? ( void *) (*l[0]) : ( void *) (l[0])
                : t[0] == pcode__SINGLE   ? v[0] ? ( void *) (*k[0]) : ( void *) (k[0])
                : t[0] == pcode__DOUBLE   ? v[0] ? ( void *) (*d[0]) : ( void *) (d[0])
                :                          (p[0])
                ,
                  t[1] == pcode__BOOLEAN  ? v[1] ? ( void *) (*b[1]) : ( void *) (b[1])
                : t[1] == pcode__BYTE     ? v[1] ? ( void *) (*y[1]) : ( void *) (y[1])
                : t[1] == pcode__SHORT    ? v[1] ? ( void *) (*s[1]) : ( void *) (s[1])
                : t[1] == pcode__INTEGER  ? v[1] ? ( void *) (*i[1]) : ( void *) (i[1])
                : t[1] == pcode__LONG     ? v[1] ? ( void *) (*l[1]) : ( void *) (l[1])
                : t[1] == pcode__SINGLE   ? v[1] ? ( void *) (*k[1]) : ( void *) (k[1])
                : t[1] == pcode__DOUBLE   ? v[1] ? ( void *) (*d[1]) : ( void *) (d[1])
                :                          (p[1])
                ,
                  t[2] == pcode__BOOLEAN  ? v[2] ? ( void *) (*b[2]) : ( void *) (b[2])
                : t[2] == pcode__BYTE     ? v[2] ? ( void *) (*y[2]) : ( void *) (y[2])
                : t[2] == pcode__SHORT    ? v[2] ? ( void *) (*s[2]) : ( void *) (s[2])
                : t[2] == pcode__INTEGER  ? v[2] ? ( void *) (*i[2]) : ( void *) (i[2])
                : t[2] == pcode__LONG     ? v[2] ? ( void *) (*l[2]) : ( void *) (l[2])
                : t[2] == pcode__SINGLE   ? v[2] ? ( void *) (*k[2]) : ( void *) (k[2])
                : t[2] == pcode__DOUBLE   ? v[2] ? ( void *) (*d[2]) : ( void *) (d[2])
                :                          (p[2])
                ,
                  t[3] == pcode__BOOLEAN  ? v[3] ? ( void *) (*b[3]) : ( void *) (b[3])
                : t[3] == pcode__BYTE     ? v[3] ? ( void *) (*y[3]) : ( void *) (y[3])
                : t[3] == pcode__SHORT    ? v[3] ? ( void *) (*s[3]) : ( void *) (s[3])
                : t[3] == pcode__INTEGER  ? v[3] ? ( void *) (*i[3]) : ( void *) (i[3])
                : t[3] == pcode__LONG     ? v[3] ? ( void *) (*l[3]) : ( void *) (l[3])
                : t[3] == pcode__SINGLE   ? v[3] ? ( void *) (*k[3]) : ( void *) (k[3])
                : t[3] == pcode__DOUBLE   ? v[3] ? ( void *) (*d[3]) : ( void *) (d[3])
                :                          (p[3])
                ,
                  t[4] == pcode__BOOLEAN  ? v[4] ? ( void *) (*b[4]) : ( void *) (b[4])
                : t[4] == pcode__BYTE     ? v[4] ? ( void *) (*y[4]) : ( void *) (y[4])
                : t[4] == pcode__SHORT    ? v[4] ? ( void *) (*s[4]) : ( void *) (s[4])
                : t[4] == pcode__INTEGER  ? v[4] ? ( void *) (*i[4]) : ( void *) (i[4])
                : t[4] == pcode__LONG     ? v[4] ? ( void *) (*l[4]) : ( void *) (l[4])
                : t[4] == pcode__SINGLE   ? v[4] ? ( void *) (*k[4]) : ( void *) (k[4])
                : t[4] == pcode__DOUBLE   ? v[4] ? ( void *) (*d[4]) : ( void *) (d[4])
                :                          (p[4])
                ,
                  t[5] == pcode__BOOLEAN  ? v[5] ? ( void *) (*b[5]) : ( void *) (b[5])
                : t[5] == pcode__BYTE     ? v[5] ? ( void *) (*y[5]) : ( void *) (y[5])
                : t[5] == pcode__SHORT    ? v[5] ? ( void *) (*s[5]) : ( void *) (s[5])
                : t[5] == pcode__INTEGER  ? v[5] ? ( void *) (*i[5]) : ( void *) (i[5])
                : t[5] == pcode__LONG     ? v[5] ? ( void *) (*l[5]) : ( void *) (l[5])
                : t[5] == pcode__SINGLE   ? v[5] ? ( void *) (*k[5]) : ( void *) (k[5])
                : t[5] == pcode__DOUBLE   ? v[5] ? ( void *) (*d[5]) : ( void *) (d[5])
                :                          (p[5])
                ,
                  t[6] == pcode__BOOLEAN  ? v[6] ? ( void *) (*b[6]) : ( void *) (b[6])
                : t[6] == pcode__BYTE     ? v[6] ? ( void *) (*y[6]) : ( void *) (y[6])
                : t[6] == pcode__SHORT    ? v[6] ? ( void *) (*s[6]) : ( void *) (s[6])
                : t[6] == pcode__INTEGER  ? v[6] ? ( void *) (*i[6]) : ( void *) (i[6])
                : t[6] == pcode__LONG     ? v[6] ? ( void *) (*l[6]) : ( void *) (l[6])
                : t[6] == pcode__SINGLE   ? v[6] ? ( void *) (*k[6]) : ( void *) (k[6])
                : t[6] == pcode__DOUBLE   ? v[6] ? ( void *) (*d[6]) : ( void *) (d[6])
                :                          (p[6])
              );
              else return runtimeError(utility::con(function, " function call failed. ", ll[lib]->errorString()));
              myStack->pushByte(ry);
            }
            break;
          case 8:
            {
              byte_c8 c = (byte_c8) ll[lib]->resolve( function );
              if (c) ry = c (
                  t[0] == pcode__BOOLEAN  ? v[0] ? ( void *) (*b[0]) : ( void *) (b[0])
                : t[0] == pcode__BYTE     ? v[0] ? ( void *) (*y[0]) : ( void *) (y[0])
                : t[0] == pcode__SHORT    ? v[0] ? ( void *) (*s[0]) : ( void *) (s[0])
                : t[0] == pcode__INTEGER  ? v[0] ? ( void *) (*i[0]) : ( void *) (i[0])
                : t[0] == pcode__LONG     ? v[0] ? ( void *) (*l[0]) : ( void *) (l[0])
                : t[0] == pcode__SINGLE   ? v[0] ? ( void *) (*k[0]) : ( void *) (k[0])
                : t[0] == pcode__DOUBLE   ? v[0] ? ( void *) (*d[0]) : ( void *) (d[0])
                :                          (p[0])
                ,
                  t[1] == pcode__BOOLEAN  ? v[1] ? ( void *) (*b[1]) : ( void *) (b[1])
                : t[1] == pcode__BYTE     ? v[1] ? ( void *) (*y[1]) : ( void *) (y[1])
                : t[1] == pcode__SHORT    ? v[1] ? ( void *) (*s[1]) : ( void *) (s[1])
                : t[1] == pcode__INTEGER  ? v[1] ? ( void *) (*i[1]) : ( void *) (i[1])
                : t[1] == pcode__LONG     ? v[1] ? ( void *) (*l[1]) : ( void *) (l[1])
                : t[1] == pcode__SINGLE   ? v[1] ? ( void *) (*k[1]) : ( void *) (k[1])
                : t[1] == pcode__DOUBLE   ? v[1] ? ( void *) (*d[1]) : ( void *) (d[1])
                :                          (p[1])
                ,
                  t[2] == pcode__BOOLEAN  ? v[2] ? ( void *) (*b[2]) : ( void *) (b[2])
                : t[2] == pcode__BYTE     ? v[2] ? ( void *) (*y[2]) : ( void *) (y[2])
                : t[2] == pcode__SHORT    ? v[2] ? ( void *) (*s[2]) : ( void *) (s[2])
                : t[2] == pcode__INTEGER  ? v[2] ? ( void *) (*i[2]) : ( void *) (i[2])
                : t[2] == pcode__LONG     ? v[2] ? ( void *) (*l[2]) : ( void *) (l[2])
                : t[2] == pcode__SINGLE   ? v[2] ? ( void *) (*k[2]) : ( void *) (k[2])
                : t[2] == pcode__DOUBLE   ? v[2] ? ( void *) (*d[2]) : ( void *) (d[2])
                :                          (p[2])
                ,
                  t[3] == pcode__BOOLEAN  ? v[3] ? ( void *) (*b[3]) : ( void *) (b[3])
                : t[3] == pcode__BYTE     ? v[3] ? ( void *) (*y[3]) : ( void *) (y[3])
                : t[3] == pcode__SHORT    ? v[3] ? ( void *) (*s[3]) : ( void *) (s[3])
                : t[3] == pcode__INTEGER  ? v[3] ? ( void *) (*i[3]) : ( void *) (i[3])
                : t[3] == pcode__LONG     ? v[3] ? ( void *) (*l[3]) : ( void *) (l[3])
                : t[3] == pcode__SINGLE   ? v[3] ? ( void *) (*k[3]) : ( void *) (k[3])
                : t[3] == pcode__DOUBLE   ? v[3] ? ( void *) (*d[3]) : ( void *) (d[3])
                :                          (p[3])
                ,
                  t[4] == pcode__BOOLEAN  ? v[4] ? ( void *) (*b[4]) : ( void *) (b[4])
                : t[4] == pcode__BYTE     ? v[4] ? ( void *) (*y[4]) : ( void *) (y[4])
                : t[4] == pcode__SHORT    ? v[4] ? ( void *) (*s[4]) : ( void *) (s[4])
                : t[4] == pcode__INTEGER  ? v[4] ? ( void *) (*i[4]) : ( void *) (i[4])
                : t[4] == pcode__LONG     ? v[4] ? ( void *) (*l[4]) : ( void *) (l[4])
                : t[4] == pcode__SINGLE   ? v[4] ? ( void *) (*k[4]) : ( void *) (k[4])
                : t[4] == pcode__DOUBLE   ? v[4] ? ( void *) (*d[4]) : ( void *) (d[4])
                :                          (p[4])
                ,
                  t[5] == pcode__BOOLEAN  ? v[5] ? ( void *) (*b[5]) : ( void *) (b[5])
                : t[5] == pcode__BYTE     ? v[5] ? ( void *) (*y[5]) : ( void *) (y[5])
                : t[5] == pcode__SHORT    ? v[5] ? ( void *) (*s[5]) : ( void *) (s[5])
                : t[5] == pcode__INTEGER  ? v[5] ? ( void *) (*i[5]) : ( void *) (i[5])
                : t[5] == pcode__LONG     ? v[5] ? ( void *) (*l[5]) : ( void *) (l[5])
                : t[5] == pcode__SINGLE   ? v[5] ? ( void *) (*k[5]) : ( void *) (k[5])
                : t[5] == pcode__DOUBLE   ? v[5] ? ( void *) (*d[5]) : ( void *) (d[5])
                :                          (p[5])
                ,
                  t[6] == pcode__BOOLEAN  ? v[6] ? ( void *) (*b[6]) : ( void *) (b[6])
                : t[6] == pcode__BYTE     ? v[6] ? ( void *) (*y[6]) : ( void *) (y[6])
                : t[6] == pcode__SHORT    ? v[6] ? ( void *) (*s[6]) : ( void *) (s[6])
                : t[6] == pcode__INTEGER  ? v[6] ? ( void *) (*i[6]) : ( void *) (i[6])
                : t[6] == pcode__LONG     ? v[6] ? ( void *) (*l[6]) : ( void *) (l[6])
                : t[6] == pcode__SINGLE   ? v[6] ? ( void *) (*k[6]) : ( void *) (k[6])
                : t[6] == pcode__DOUBLE   ? v[6] ? ( void *) (*d[6]) : ( void *) (d[6])
                :                          (p[6])
                ,
                  t[7] == pcode__BOOLEAN  ? v[7] ? ( void *) (*b[7]) : ( void *) (b[7])
                : t[7] == pcode__BYTE     ? v[7] ? ( void *) (*y[7]) : ( void *) (y[7])
                : t[7] == pcode__SHORT    ? v[7] ? ( void *) (*s[7]) : ( void *) (s[7])
                : t[7] == pcode__INTEGER  ? v[7] ? ( void *) (*i[7]) : ( void *) (i[7])
                : t[7] == pcode__LONG     ? v[7] ? ( void *) (*l[7]) : ( void *) (l[7])
                : t[7] == pcode__SINGLE   ? v[7] ? ( void *) (*k[7]) : ( void *) (k[7])
                : t[7] == pcode__DOUBLE   ? v[7] ? ( void *) (*d[7]) : ( void *) (d[7])
                :                          (p[7])
              );
              else return runtimeError(utility::con(function, " function call failed. ", ll[lib]->errorString()));
              myStack->pushByte(ry);
            }
            break;
          case 9:
            {
              byte_c9 c = (byte_c9) ll[lib]->resolve( function );
              if (c) ry = c (
                  t[0] == pcode__BOOLEAN  ? v[0] ? ( void *) (*b[0]) : ( void *) (b[0])
                : t[0] == pcode__BYTE     ? v[0] ? ( void *) (*y[0]) : ( void *) (y[0])
                : t[0] == pcode__SHORT    ? v[0] ? ( void *) (*s[0]) : ( void *) (s[0])
                : t[0] == pcode__INTEGER  ? v[0] ? ( void *) (*i[0]) : ( void *) (i[0])
                : t[0] == pcode__LONG     ? v[0] ? ( void *) (*l[0]) : ( void *) (l[0])
                : t[0] == pcode__SINGLE   ? v[0] ? ( void *) (*k[0]) : ( void *) (k[0])
                : t[0] == pcode__DOUBLE   ? v[0] ? ( void *) (*d[0]) : ( void *) (d[0])
                :                          (p[0])
                ,
                  t[1] == pcode__BOOLEAN  ? v[1] ? ( void *) (*b[1]) : ( void *) (b[1])
                : t[1] == pcode__BYTE     ? v[1] ? ( void *) (*y[1]) : ( void *) (y[1])
                : t[1] == pcode__SHORT    ? v[1] ? ( void *) (*s[1]) : ( void *) (s[1])
                : t[1] == pcode__INTEGER  ? v[1] ? ( void *) (*i[1]) : ( void *) (i[1])
                : t[1] == pcode__LONG     ? v[1] ? ( void *) (*l[1]) : ( void *) (l[1])
                : t[1] == pcode__SINGLE   ? v[1] ? ( void *) (*k[1]) : ( void *) (k[1])
                : t[1] == pcode__DOUBLE   ? v[1] ? ( void *) (*d[1]) : ( void *) (d[1])
                :                          (p[1])
                ,
                  t[2] == pcode__BOOLEAN  ? v[2] ? ( void *) (*b[2]) : ( void *) (b[2])
                : t[2] == pcode__BYTE     ? v[2] ? ( void *) (*y[2]) : ( void *) (y[2])
                : t[2] == pcode__SHORT    ? v[2] ? ( void *) (*s[2]) : ( void *) (s[2])
                : t[2] == pcode__INTEGER  ? v[2] ? ( void *) (*i[2]) : ( void *) (i[2])
                : t[2] == pcode__LONG     ? v[2] ? ( void *) (*l[2]) : ( void *) (l[2])
                : t[2] == pcode__SINGLE   ? v[2] ? ( void *) (*k[2]) : ( void *) (k[2])
                : t[2] == pcode__DOUBLE   ? v[2] ? ( void *) (*d[2]) : ( void *) (d[2])
                :                          (p[2])
                ,
                  t[3] == pcode__BOOLEAN  ? v[3] ? ( void *) (*b[3]) : ( void *) (b[3])
                : t[3] == pcode__BYTE     ? v[3] ? ( void *) (*y[3]) : ( void *) (y[3])
                : t[3] == pcode__SHORT    ? v[3] ? ( void *) (*s[3]) : ( void *) (s[3])
                : t[3] == pcode__INTEGER  ? v[3] ? ( void *) (*i[3]) : ( void *) (i[3])
                : t[3] == pcode__LONG     ? v[3] ? ( void *) (*l[3]) : ( void *) (l[3])
                : t[3] == pcode__SINGLE   ? v[3] ? ( void *) (*k[3]) : ( void *) (k[3])
                : t[3] == pcode__DOUBLE   ? v[3] ? ( void *) (*d[3]) : ( void *) (d[3])
                :                          (p[3])
                ,
                  t[4] == pcode__BOOLEAN  ? v[4] ? ( void *) (*b[4]) : ( void *) (b[4])
                : t[4] == pcode__BYTE     ? v[4] ? ( void *) (*y[4]) : ( void *) (y[4])
                : t[4] == pcode__SHORT    ? v[4] ? ( void *) (*s[4]) : ( void *) (s[4])
                : t[4] == pcode__INTEGER  ? v[4] ? ( void *) (*i[4]) : ( void *) (i[4])
                : t[4] == pcode__LONG     ? v[4] ? ( void *) (*l[4]) : ( void *) (l[4])
                : t[4] == pcode__SINGLE   ? v[4] ? ( void *) (*k[4]) : ( void *) (k[4])
                : t[4] == pcode__DOUBLE   ? v[4] ? ( void *) (*d[4]) : ( void *) (d[4])
                :                          (p[4])
                ,
                  t[5] == pcode__BOOLEAN  ? v[5] ? ( void *) (*b[5]) : ( void *) (b[5])
                : t[5] == pcode__BYTE     ? v[5] ? ( void *) (*y[5]) : ( void *) (y[5])
                : t[5] == pcode__SHORT    ? v[5] ? ( void *) (*s[5]) : ( void *) (s[5])
                : t[5] == pcode__INTEGER  ? v[5] ? ( void *) (*i[5]) : ( void *) (i[5])
                : t[5] == pcode__LONG     ? v[5] ? ( void *) (*l[5]) : ( void *) (l[5])
                : t[5] == pcode__SINGLE   ? v[5] ? ( void *) (*k[5]) : ( void *) (k[5])
                : t[5] == pcode__DOUBLE   ? v[5] ? ( void *) (*d[5]) : ( void *) (d[5])
                :                          (p[5])
                ,
                  t[6] == pcode__BOOLEAN  ? v[6] ? ( void *) (*b[6]) : ( void *) (b[6])
                : t[6] == pcode__BYTE     ? v[6] ? ( void *) (*y[6]) : ( void *) (y[6])
                : t[6] == pcode__SHORT    ? v[6] ? ( void *) (*s[6]) : ( void *) (s[6])
                : t[6] == pcode__INTEGER  ? v[6] ? ( void *) (*i[6]) : ( void *) (i[6])
                : t[6] == pcode__LONG     ? v[6] ? ( void *) (*l[6]) : ( void *) (l[6])
                : t[6] == pcode__SINGLE   ? v[6] ? ( void *) (*k[6]) : ( void *) (k[6])
                : t[6] == pcode__DOUBLE   ? v[6] ? ( void *) (*d[6]) : ( void *) (d[6])
                :                          (p[6])
                ,
                  t[7] == pcode__BOOLEAN  ? v[7] ? ( void *) (*b[7]) : ( void *) (b[7])
                : t[7] == pcode__BYTE     ? v[7] ? ( void *) (*y[7]) : ( void *) (y[7])
                : t[7] == pcode__SHORT    ? v[7] ? ( void *) (*s[7]) : ( void *) (s[7])
                : t[7] == pcode__INTEGER  ? v[7] ? ( void *) (*i[7]) : ( void *) (i[7])
                : t[7] == pcode__LONG     ? v[7] ? ( void *) (*l[7]) : ( void *) (l[7])
                : t[7] == pcode__SINGLE   ? v[7] ? ( void *) (*k[7]) : ( void *) (k[7])
                : t[7] == pcode__DOUBLE   ? v[7] ? ( void *) (*d[7]) : ( void *) (d[7])
                :                          (p[7])
                ,
                  t[8] == pcode__BOOLEAN  ? v[8] ? ( void *) (*b[8]) : ( void *) (b[8])
                : t[8] == pcode__BYTE     ? v[8] ? ( void *) (*y[8]) : ( void *) (y[8])
                : t[8] == pcode__SHORT    ? v[8] ? ( void *) (*s[8]) : ( void *) (s[8])
                : t[8] == pcode__INTEGER  ? v[8] ? ( void *) (*i[8]) : ( void *) (i[8])
                : t[8] == pcode__LONG     ? v[8] ? ( void *) (*l[8]) : ( void *) (l[8])
                : t[8] == pcode__SINGLE   ? v[8] ? ( void *) (*k[8]) : ( void *) (k[8])
                : t[8] == pcode__DOUBLE   ? v[8] ? ( void *) (*d[8]) : ( void *) (d[8])
                :                          (p[8])
              );
              else return runtimeError(utility::con(function, " function call failed. ", ll[lib]->errorString()));
              myStack->pushByte(ry);
            }
            break;
          default:
            return runtimeError(utility::con(function, ": Too much arguments (max. 9 allowed) when calling declare function."));
            break;
         }
         break;
       case pcode__SHORT:
        switch(count){
          case 0:
            {
              short_c0 c = (short_c0) ll[lib]->resolve( function );
              if (c) rs = c (
              );
              else return runtimeError(utility::con(function, " function call failed. ", ll[lib]->errorString()));
              myStack->pushShort(rs);
            }
            break;
          case 1:
            {
              short_c1 c = (short_c1) ll[lib]->resolve( function );
              if (c) rs = c (
                  t[0] == pcode__BOOLEAN  ? v[0] ? ( void *) (*b[0]) : ( void *) (b[0])
                : t[0] == pcode__BYTE     ? v[0] ? ( void *) (*y[0]) : ( void *) (y[0])
                : t[0] == pcode__SHORT    ? v[0] ? ( void *) (*s[0]) : ( void *) (s[0])
                : t[0] == pcode__INTEGER  ? v[0] ? ( void *) (*i[0]) : ( void *) (i[0])
                : t[0] == pcode__LONG     ? v[0] ? ( void *) (*l[0]) : ( void *) (l[0])
                : t[0] == pcode__SINGLE   ? v[0] ? ( void *) (*k[0]) : ( void *) (k[0])
                : t[0] == pcode__DOUBLE   ? v[0] ? ( void *) (*d[0]) : ( void *) (d[0])
                :                          (p[0])
              );
              else return runtimeError(utility::con(function, " function call failed. ", ll[lib]->errorString()));
              myStack->pushShort(rs);
            }
            break;
          case 2:
            {
              short_c2 c = (short_c2) ll[lib]->resolve( function );
              if (c) rs = c (
                  t[0] == pcode__BOOLEAN  ? v[0] ? ( void *) (*b[0]) : ( void *) (b[0])
                : t[0] == pcode__BYTE     ? v[0] ? ( void *) (*y[0]) : ( void *) (y[0])
                : t[0] == pcode__SHORT    ? v[0] ? ( void *) (*s[0]) : ( void *) (s[0])
                : t[0] == pcode__INTEGER  ? v[0] ? ( void *) (*i[0]) : ( void *) (i[0])
                : t[0] == pcode__LONG     ? v[0] ? ( void *) (*l[0]) : ( void *) (l[0])
                : t[0] == pcode__SINGLE   ? v[0] ? ( void *) (*k[0]) : ( void *) (k[0])
                : t[0] == pcode__DOUBLE   ? v[0] ? ( void *) (*d[0]) : ( void *) (d[0])
                :                          (p[0])
                ,
                  t[1] == pcode__BOOLEAN  ? v[1] ? ( void *) (*b[1]) : ( void *) (b[1])
                : t[1] == pcode__BYTE     ? v[1] ? ( void *) (*y[1]) : ( void *) (y[1])
                : t[1] == pcode__SHORT    ? v[1] ? ( void *) (*s[1]) : ( void *) (s[1])
                : t[1] == pcode__INTEGER  ? v[1] ? ( void *) (*i[1]) : ( void *) (i[1])
                : t[1] == pcode__LONG     ? v[1] ? ( void *) (*l[1]) : ( void *) (l[1])
                : t[1] == pcode__SINGLE   ? v[1] ? ( void *) (*k[1]) : ( void *) (k[1])
                : t[1] == pcode__DOUBLE   ? v[1] ? ( void *) (*d[1]) : ( void *) (d[1])
                :                          (p[1])
              );
              else return runtimeError(utility::con(function, " function call failed. ", ll[lib]->errorString()));
              myStack->pushShort(rs);
            }
            break;
          case 3:
            {
              short_c3 c = (short_c3) ll[lib]->resolve( function );
              if (c) rs = c (
                  t[0] == pcode__BOOLEAN  ? v[0] ? ( void *) (*b[0]) : ( void *) (b[0])
                : t[0] == pcode__BYTE     ? v[0] ? ( void *) (*y[0]) : ( void *) (y[0])
                : t[0] == pcode__SHORT    ? v[0] ? ( void *) (*s[0]) : ( void *) (s[0])
                : t[0] == pcode__INTEGER  ? v[0] ? ( void *) (*i[0]) : ( void *) (i[0])
                : t[0] == pcode__LONG     ? v[0] ? ( void *) (*l[0]) : ( void *) (l[0])
                : t[0] == pcode__SINGLE   ? v[0] ? ( void *) (*k[0]) : ( void *) (k[0])
                : t[0] == pcode__DOUBLE   ? v[0] ? ( void *) (*d[0]) : ( void *) (d[0])
                :                          (p[0])
                ,
                  t[1] == pcode__BOOLEAN  ? v[1] ? ( void *) (*b[1]) : ( void *) (b[1])
                : t[1] == pcode__BYTE     ? v[1] ? ( void *) (*y[1]) : ( void *) (y[1])
                : t[1] == pcode__SHORT    ? v[1] ? ( void *) (*s[1]) : ( void *) (s[1])
                : t[1] == pcode__INTEGER  ? v[1] ? ( void *) (*i[1]) : ( void *) (i[1])
                : t[1] == pcode__LONG     ? v[1] ? ( void *) (*l[1]) : ( void *) (l[1])
                : t[1] == pcode__SINGLE   ? v[1] ? ( void *) (*k[1]) : ( void *) (k[1])
                : t[1] == pcode__DOUBLE   ? v[1] ? ( void *) (*d[1]) : ( void *) (d[1])
                :                          (p[1])
                ,
                  t[2] == pcode__BOOLEAN  ? v[2] ? ( void *) (*b[2]) : ( void *) (b[2])
                : t[2] == pcode__BYTE     ? v[2] ? ( void *) (*y[2]) : ( void *) (y[2])
                : t[2] == pcode__SHORT    ? v[2] ? ( void *) (*s[2]) : ( void *) (s[2])
                : t[2] == pcode__INTEGER  ? v[2] ? ( void *) (*i[2]) : ( void *) (i[2])
                : t[2] == pcode__LONG     ? v[2] ? ( void *) (*l[2]) : ( void *) (l[2])
                : t[2] == pcode__SINGLE   ? v[2] ? ( void *) (*k[2]) : ( void *) (k[2])
                : t[2] == pcode__DOUBLE   ? v[2] ? ( void *) (*d[2]) : ( void *) (d[2])
                :                          (p[2])
              );
              else return runtimeError(utility::con(function, " function call failed. ", ll[lib]->errorString()));
              myStack->pushShort(rs);
            }
            break;
          case 4:
            {
              short_c4 c = (short_c4) ll[lib]->resolve( function );
              if (c) rs = c (
                  t[0] == pcode__BOOLEAN  ? v[0] ? ( void *) (*b[0]) : ( void *) (b[0])
                : t[0] == pcode__BYTE     ? v[0] ? ( void *) (*y[0]) : ( void *) (y[0])
                : t[0] == pcode__SHORT    ? v[0] ? ( void *) (*s[0]) : ( void *) (s[0])
                : t[0] == pcode__INTEGER  ? v[0] ? ( void *) (*i[0]) : ( void *) (i[0])
                : t[0] == pcode__LONG     ? v[0] ? ( void *) (*l[0]) : ( void *) (l[0])
                : t[0] == pcode__SINGLE   ? v[0] ? ( void *) (*k[0]) : ( void *) (k[0])
                : t[0] == pcode__DOUBLE   ? v[0] ? ( void *) (*d[0]) : ( void *) (d[0])
                :                          (p[0])
                ,
                  t[1] == pcode__BOOLEAN  ? v[1] ? ( void *) (*b[1]) : ( void *) (b[1])
                : t[1] == pcode__BYTE     ? v[1] ? ( void *) (*y[1]) : ( void *) (y[1])
                : t[1] == pcode__SHORT    ? v[1] ? ( void *) (*s[1]) : ( void *) (s[1])
                : t[1] == pcode__INTEGER  ? v[1] ? ( void *) (*i[1]) : ( void *) (i[1])
                : t[1] == pcode__LONG     ? v[1] ? ( void *) (*l[1]) : ( void *) (l[1])
                : t[1] == pcode__SINGLE   ? v[1] ? ( void *) (*k[1]) : ( void *) (k[1])
                : t[1] == pcode__DOUBLE   ? v[1] ? ( void *) (*d[1]) : ( void *) (d[1])
                :                          (p[1])
                ,
                  t[2] == pcode__BOOLEAN  ? v[2] ? ( void *) (*b[2]) : ( void *) (b[2])
                : t[2] == pcode__BYTE     ? v[2] ? ( void *) (*y[2]) : ( void *) (y[2])
                : t[2] == pcode__SHORT    ? v[2] ? ( void *) (*s[2]) : ( void *) (s[2])
                : t[2] == pcode__INTEGER  ? v[2] ? ( void *) (*i[2]) : ( void *) (i[2])
                : t[2] == pcode__LONG     ? v[2] ? ( void *) (*l[2]) : ( void *) (l[2])
                : t[2] == pcode__SINGLE   ? v[2] ? ( void *) (*k[2]) : ( void *) (k[2])
                : t[2] == pcode__DOUBLE   ? v[2] ? ( void *) (*d[2]) : ( void *) (d[2])
                :                          (p[2])
                ,
                  t[3] == pcode__BOOLEAN  ? v[3] ? ( void *) (*b[3]) : ( void *) (b[3])
                : t[3] == pcode__BYTE     ? v[3] ? ( void *) (*y[3]) : ( void *) (y[3])
                : t[3] == pcode__SHORT    ? v[3] ? ( void *) (*s[3]) : ( void *) (s[3])
                : t[3] == pcode__INTEGER  ? v[3] ? ( void *) (*i[3]) : ( void *) (i[3])
                : t[3] == pcode__LONG     ? v[3] ? ( void *) (*l[3]) : ( void *) (l[3])
                : t[3] == pcode__SINGLE   ? v[3] ? ( void *) (*k[3]) : ( void *) (k[3])
                : t[3] == pcode__DOUBLE   ? v[3] ? ( void *) (*d[3]) : ( void *) (d[3])
                :                          (p[3])
              );
              else return runtimeError(utility::con(function, " function call failed. ", ll[lib]->errorString()));
              myStack->pushShort(rs);
            }
            break;
          case 5:
            {
              short_c5 c = (short_c5) ll[lib]->resolve( function );
              if (c) rs = c (
                  t[0] == pcode__BOOLEAN  ? v[0] ? ( void *) (*b[0]) : ( void *) (b[0])
                : t[0] == pcode__BYTE     ? v[0] ? ( void *) (*y[0]) : ( void *) (y[0])
                : t[0] == pcode__SHORT    ? v[0] ? ( void *) (*s[0]) : ( void *) (s[0])
                : t[0] == pcode__INTEGER  ? v[0] ? ( void *) (*i[0]) : ( void *) (i[0])
                : t[0] == pcode__LONG     ? v[0] ? ( void *) (*l[0]) : ( void *) (l[0])
                : t[0] == pcode__SINGLE   ? v[0] ? ( void *) (*k[0]) : ( void *) (k[0])
                : t[0] == pcode__DOUBLE   ? v[0] ? ( void *) (*d[0]) : ( void *) (d[0])
                :                          (p[0])
                ,
                  t[1] == pcode__BOOLEAN  ? v[1] ? ( void *) (*b[1]) : ( void *) (b[1])
                : t[1] == pcode__BYTE     ? v[1] ? ( void *) (*y[1]) : ( void *) (y[1])
                : t[1] == pcode__SHORT    ? v[1] ? ( void *) (*s[1]) : ( void *) (s[1])
                : t[1] == pcode__INTEGER  ? v[1] ? ( void *) (*i[1]) : ( void *) (i[1])
                : t[1] == pcode__LONG     ? v[1] ? ( void *) (*l[1]) : ( void *) (l[1])
                : t[1] == pcode__SINGLE   ? v[1] ? ( void *) (*k[1]) : ( void *) (k[1])
                : t[1] == pcode__DOUBLE   ? v[1] ? ( void *) (*d[1]) : ( void *) (d[1])
                :                          (p[1])
                ,
                  t[2] == pcode__BOOLEAN  ? v[2] ? ( void *) (*b[2]) : ( void *) (b[2])
                : t[2] == pcode__BYTE     ? v[2] ? ( void *) (*y[2]) : ( void *) (y[2])
                : t[2] == pcode__SHORT    ? v[2] ? ( void *) (*s[2]) : ( void *) (s[2])
                : t[2] == pcode__INTEGER  ? v[2] ? ( void *) (*i[2]) : ( void *) (i[2])
                : t[2] == pcode__LONG     ? v[2] ? ( void *) (*l[2]) : ( void *) (l[2])
                : t[2] == pcode__SINGLE   ? v[2] ? ( void *) (*k[2]) : ( void *) (k[2])
                : t[2] == pcode__DOUBLE   ? v[2] ? ( void *) (*d[2]) : ( void *) (d[2])
                :                          (p[2])
                ,
                  t[3] == pcode__BOOLEAN  ? v[3] ? ( void *) (*b[3]) : ( void *) (b[3])
                : t[3] == pcode__BYTE     ? v[3] ? ( void *) (*y[3]) : ( void *) (y[3])
                : t[3] == pcode__SHORT    ? v[3] ? ( void *) (*s[3]) : ( void *) (s[3])
                : t[3] == pcode__INTEGER  ? v[3] ? ( void *) (*i[3]) : ( void *) (i[3])
                : t[3] == pcode__LONG     ? v[3] ? ( void *) (*l[3]) : ( void *) (l[3])
                : t[3] == pcode__SINGLE   ? v[3] ? ( void *) (*k[3]) : ( void *) (k[3])
                : t[3] == pcode__DOUBLE   ? v[3] ? ( void *) (*d[3]) : ( void *) (d[3])
                :                          (p[3])
                ,
                  t[4] == pcode__BOOLEAN  ? v[4] ? ( void *) (*b[4]) : ( void *) (b[4])
                : t[4] == pcode__BYTE     ? v[4] ? ( void *) (*y[4]) : ( void *) (y[4])
                : t[4] == pcode__SHORT    ? v[4] ? ( void *) (*s[4]) : ( void *) (s[4])
                : t[4] == pcode__INTEGER  ? v[4] ? ( void *) (*i[4]) : ( void *) (i[4])
                : t[4] == pcode__LONG     ? v[4] ? ( void *) (*l[4]) : ( void *) (l[4])
                : t[4] == pcode__SINGLE   ? v[4] ? ( void *) (*k[4]) : ( void *) (k[4])
                : t[4] == pcode__DOUBLE   ? v[4] ? ( void *) (*d[4]) : ( void *) (d[4])
                :                          (p[4])
              );
              else return runtimeError(utility::con(function, " function call failed. ", ll[lib]->errorString()));
              myStack->pushShort(rs);
            }
            break;
          case 6:
            {
              short_c6 c = (short_c6) ll[lib]->resolve( function );
              if (c) rs = c (
                  t[0] == pcode__BOOLEAN  ? v[0] ? ( void *) (*b[0]) : ( void *) (b[0])
                : t[0] == pcode__BYTE     ? v[0] ? ( void *) (*y[0]) : ( void *) (y[0])
                : t[0] == pcode__SHORT    ? v[0] ? ( void *) (*s[0]) : ( void *) (s[0])
                : t[0] == pcode__INTEGER  ? v[0] ? ( void *) (*i[0]) : ( void *) (i[0])
                : t[0] == pcode__LONG     ? v[0] ? ( void *) (*l[0]) : ( void *) (l[0])
                : t[0] == pcode__SINGLE   ? v[0] ? ( void *) (*k[0]) : ( void *) (k[0])
                : t[0] == pcode__DOUBLE   ? v[0] ? ( void *) (*d[0]) : ( void *) (d[0])
                :                          (p[0])
                ,
                  t[1] == pcode__BOOLEAN  ? v[1] ? ( void *) (*b[1]) : ( void *) (b[1])
                : t[1] == pcode__BYTE     ? v[1] ? ( void *) (*y[1]) : ( void *) (y[1])
                : t[1] == pcode__SHORT    ? v[1] ? ( void *) (*s[1]) : ( void *) (s[1])
                : t[1] == pcode__INTEGER  ? v[1] ? ( void *) (*i[1]) : ( void *) (i[1])
                : t[1] == pcode__LONG     ? v[1] ? ( void *) (*l[1]) : ( void *) (l[1])
                : t[1] == pcode__SINGLE   ? v[1] ? ( void *) (*k[1]) : ( void *) (k[1])
                : t[1] == pcode__DOUBLE   ? v[1] ? ( void *) (*d[1]) : ( void *) (d[1])
                :                          (p[1])
                ,
                  t[2] == pcode__BOOLEAN  ? v[2] ? ( void *) (*b[2]) : ( void *) (b[2])
                : t[2] == pcode__BYTE     ? v[2] ? ( void *) (*y[2]) : ( void *) (y[2])
                : t[2] == pcode__SHORT    ? v[2] ? ( void *) (*s[2]) : ( void *) (s[2])
                : t[2] == pcode__INTEGER  ? v[2] ? ( void *) (*i[2]) : ( void *) (i[2])
                : t[2] == pcode__LONG     ? v[2] ? ( void *) (*l[2]) : ( void *) (l[2])
                : t[2] == pcode__SINGLE   ? v[2] ? ( void *) (*k[2]) : ( void *) (k[2])
                : t[2] == pcode__DOUBLE   ? v[2] ? ( void *) (*d[2]) : ( void *) (d[2])
                :                          (p[2])
                ,
                  t[3] == pcode__BOOLEAN  ? v[3] ? ( void *) (*b[3]) : ( void *) (b[3])
                : t[3] == pcode__BYTE     ? v[3] ? ( void *) (*y[3]) : ( void *) (y[3])
                : t[3] == pcode__SHORT    ? v[3] ? ( void *) (*s[3]) : ( void *) (s[3])
                : t[3] == pcode__INTEGER  ? v[3] ? ( void *) (*i[3]) : ( void *) (i[3])
                : t[3] == pcode__LONG     ? v[3] ? ( void *) (*l[3]) : ( void *) (l[3])
                : t[3] == pcode__SINGLE   ? v[3] ? ( void *) (*k[3]) : ( void *) (k[3])
                : t[3] == pcode__DOUBLE   ? v[3] ? ( void *) (*d[3]) : ( void *) (d[3])
                :                          (p[3])
                ,
                  t[4] == pcode__BOOLEAN  ? v[4] ? ( void *) (*b[4]) : ( void *) (b[4])
                : t[4] == pcode__BYTE     ? v[4] ? ( void *) (*y[4]) : ( void *) (y[4])
                : t[4] == pcode__SHORT    ? v[4] ? ( void *) (*s[4]) : ( void *) (s[4])
                : t[4] == pcode__INTEGER  ? v[4] ? ( void *) (*i[4]) : ( void *) (i[4])
                : t[4] == pcode__LONG     ? v[4] ? ( void *) (*l[4]) : ( void *) (l[4])
                : t[4] == pcode__SINGLE   ? v[4] ? ( void *) (*k[4]) : ( void *) (k[4])
                : t[4] == pcode__DOUBLE   ? v[4] ? ( void *) (*d[4]) : ( void *) (d[4])
                :                          (p[4])
                ,
                  t[5] == pcode__BOOLEAN  ? v[5] ? ( void *) (*b[5]) : ( void *) (b[5])
                : t[5] == pcode__BYTE     ? v[5] ? ( void *) (*y[5]) : ( void *) (y[5])
                : t[5] == pcode__SHORT    ? v[5] ? ( void *) (*s[5]) : ( void *) (s[5])
                : t[5] == pcode__INTEGER  ? v[5] ? ( void *) (*i[5]) : ( void *) (i[5])
                : t[5] == pcode__LONG     ? v[5] ? ( void *) (*l[5]) : ( void *) (l[5])
                : t[5] == pcode__SINGLE   ? v[5] ? ( void *) (*k[5]) : ( void *) (k[5])
                : t[5] == pcode__DOUBLE   ? v[5] ? ( void *) (*d[5]) : ( void *) (d[5])
                :                          (p[5])
                );
              else return runtimeError(utility::con(function, " function call failed. ", ll[lib]->errorString()));
              myStack->pushShort(rs);
            }
            break;
          case 7:
            {
              short_c7 c = (short_c7) ll[lib]->resolve( function );
              if (c) rs = c (
                  t[0] == pcode__BOOLEAN  ? v[0] ? ( void *) (*b[0]) : ( void *) (b[0])
                : t[0] == pcode__BYTE     ? v[0] ? ( void *) (*y[0]) : ( void *) (y[0])
                : t[0] == pcode__SHORT    ? v[0] ? ( void *) (*s[0]) : ( void *) (s[0])
                : t[0] == pcode__INTEGER  ? v[0] ? ( void *) (*i[0]) : ( void *) (i[0])
                : t[0] == pcode__LONG     ? v[0] ? ( void *) (*l[0]) : ( void *) (l[0])
                : t[0] == pcode__SINGLE   ? v[0] ? ( void *) (*k[0]) : ( void *) (k[0])
                : t[0] == pcode__DOUBLE   ? v[0] ? ( void *) (*d[0]) : ( void *) (d[0])
                :                          (p[0])
                ,
                  t[1] == pcode__BOOLEAN  ? v[1] ? ( void *) (*b[1]) : ( void *) (b[1])
                : t[1] == pcode__BYTE     ? v[1] ? ( void *) (*y[1]) : ( void *) (y[1])
                : t[1] == pcode__SHORT    ? v[1] ? ( void *) (*s[1]) : ( void *) (s[1])
                : t[1] == pcode__INTEGER  ? v[1] ? ( void *) (*i[1]) : ( void *) (i[1])
                : t[1] == pcode__LONG     ? v[1] ? ( void *) (*l[1]) : ( void *) (l[1])
                : t[1] == pcode__SINGLE   ? v[1] ? ( void *) (*k[1]) : ( void *) (k[1])
                : t[1] == pcode__DOUBLE   ? v[1] ? ( void *) (*d[1]) : ( void *) (d[1])
                :                          (p[1])
                ,
                  t[2] == pcode__BOOLEAN  ? v[2] ? ( void *) (*b[2]) : ( void *) (b[2])
                : t[2] == pcode__BYTE     ? v[2] ? ( void *) (*y[2]) : ( void *) (y[2])
                : t[2] == pcode__SHORT    ? v[2] ? ( void *) (*s[2]) : ( void *) (s[2])
                : t[2] == pcode__INTEGER  ? v[2] ? ( void *) (*i[2]) : ( void *) (i[2])
                : t[2] == pcode__LONG     ? v[2] ? ( void *) (*l[2]) : ( void *) (l[2])
                : t[2] == pcode__SINGLE   ? v[2] ? ( void *) (*k[2]) : ( void *) (k[2])
                : t[2] == pcode__DOUBLE   ? v[2] ? ( void *) (*d[2]) : ( void *) (d[2])
                :                          (p[2])
                ,
                  t[3] == pcode__BOOLEAN  ? v[3] ? ( void *) (*b[3]) : ( void *) (b[3])
                : t[3] == pcode__BYTE     ? v[3] ? ( void *) (*y[3]) : ( void *) (y[3])
                : t[3] == pcode__SHORT    ? v[3] ? ( void *) (*s[3]) : ( void *) (s[3])
                : t[3] == pcode__INTEGER  ? v[3] ? ( void *) (*i[3]) : ( void *) (i[3])
                : t[3] == pcode__LONG     ? v[3] ? ( void *) (*l[3]) : ( void *) (l[3])
                : t[3] == pcode__SINGLE   ? v[3] ? ( void *) (*k[3]) : ( void *) (k[3])
                : t[3] == pcode__DOUBLE   ? v[3] ? ( void *) (*d[3]) : ( void *) (d[3])
                :                          (p[3])
                ,
                  t[4] == pcode__BOOLEAN  ? v[4] ? ( void *) (*b[4]) : ( void *) (b[4])
                : t[4] == pcode__BYTE     ? v[4] ? ( void *) (*y[4]) : ( void *) (y[4])
                : t[4] == pcode__SHORT    ? v[4] ? ( void *) (*s[4]) : ( void *) (s[4])
                : t[4] == pcode__INTEGER  ? v[4] ? ( void *) (*i[4]) : ( void *) (i[4])
                : t[4] == pcode__LONG     ? v[4] ? ( void *) (*l[4]) : ( void *) (l[4])
                : t[4] == pcode__SINGLE   ? v[4] ? ( void *) (*k[4]) : ( void *) (k[4])
                : t[4] == pcode__DOUBLE   ? v[4] ? ( void *) (*d[4]) : ( void *) (d[4])
                :                          (p[4])
                ,
                  t[5] == pcode__BOOLEAN  ? v[5] ? ( void *) (*b[5]) : ( void *) (b[5])
                : t[5] == pcode__BYTE     ? v[5] ? ( void *) (*y[5]) : ( void *) (y[5])
                : t[5] == pcode__SHORT    ? v[5] ? ( void *) (*s[5]) : ( void *) (s[5])
                : t[5] == pcode__INTEGER  ? v[5] ? ( void *) (*i[5]) : ( void *) (i[5])
                : t[5] == pcode__LONG     ? v[5] ? ( void *) (*l[5]) : ( void *) (l[5])
                : t[5] == pcode__SINGLE   ? v[5] ? ( void *) (*k[5]) : ( void *) (k[5])
                : t[5] == pcode__DOUBLE   ? v[5] ? ( void *) (*d[5]) : ( void *) (d[5])
                :                          (p[5])
                ,
                  t[6] == pcode__BOOLEAN  ? v[6] ? ( void *) (*b[6]) : ( void *) (b[6])
                : t[6] == pcode__BYTE     ? v[6] ? ( void *) (*y[6]) : ( void *) (y[6])
                : t[6] == pcode__SHORT    ? v[6] ? ( void *) (*s[6]) : ( void *) (s[6])
                : t[6] == pcode__INTEGER  ? v[6] ? ( void *) (*i[6]) : ( void *) (i[6])
                : t[6] == pcode__LONG     ? v[6] ? ( void *) (*l[6]) : ( void *) (l[6])
                : t[6] == pcode__SINGLE   ? v[6] ? ( void *) (*k[6]) : ( void *) (k[6])
                : t[6] == pcode__DOUBLE   ? v[6] ? ( void *) (*d[6]) : ( void *) (d[6])
                :                          (p[6])
                );
              else return runtimeError(utility::con(function, " function call failed. ", ll[lib]->errorString()));
              myStack->pushShort(rs);
            }
            break;
          case 8:
            {
              short_c8 c = (short_c8) ll[lib]->resolve( function );
              if (c) rs = c (
                  t[0] == pcode__BOOLEAN  ? v[0] ? ( void *) (*b[0]) : ( void *) (b[0])
                : t[0] == pcode__BYTE     ? v[0] ? ( void *) (*y[0]) : ( void *) (y[0])
                : t[0] == pcode__SHORT    ? v[0] ? ( void *) (*s[0]) : ( void *) (s[0])
                : t[0] == pcode__INTEGER  ? v[0] ? ( void *) (*i[0]) : ( void *) (i[0])
                : t[0] == pcode__LONG     ? v[0] ? ( void *) (*l[0]) : ( void *) (l[0])
                : t[0] == pcode__SINGLE   ? v[0] ? ( void *) (*k[0]) : ( void *) (k[0])
                : t[0] == pcode__DOUBLE   ? v[0] ? ( void *) (*d[0]) : ( void *) (d[0])
                :                          (p[0])
                ,
                  t[1] == pcode__BOOLEAN  ? v[1] ? ( void *) (*b[1]) : ( void *) (b[1])
                : t[1] == pcode__BYTE     ? v[1] ? ( void *) (*y[1]) : ( void *) (y[1])
                : t[1] == pcode__SHORT    ? v[1] ? ( void *) (*s[1]) : ( void *) (s[1])
                : t[1] == pcode__INTEGER  ? v[1] ? ( void *) (*i[1]) : ( void *) (i[1])
                : t[1] == pcode__LONG     ? v[1] ? ( void *) (*l[1]) : ( void *) (l[1])
                : t[1] == pcode__SINGLE   ? v[1] ? ( void *) (*k[1]) : ( void *) (k[1])
                : t[1] == pcode__DOUBLE   ? v[1] ? ( void *) (*d[1]) : ( void *) (d[1])
                :                          (p[1])
                ,
                  t[2] == pcode__BOOLEAN  ? v[2] ? ( void *) (*b[2]) : ( void *) (b[2])
                : t[2] == pcode__BYTE     ? v[2] ? ( void *) (*y[2]) : ( void *) (y[2])
                : t[2] == pcode__SHORT    ? v[2] ? ( void *) (*s[2]) : ( void *) (s[2])
                : t[2] == pcode__INTEGER  ? v[2] ? ( void *) (*i[2]) : ( void *) (i[2])
                : t[2] == pcode__LONG     ? v[2] ? ( void *) (*l[2]) : ( void *) (l[2])
                : t[2] == pcode__SINGLE   ? v[2] ? ( void *) (*k[2]) : ( void *) (k[2])
                : t[2] == pcode__DOUBLE   ? v[2] ? ( void *) (*d[2]) : ( void *) (d[2])
                :                          (p[2])
                ,
                  t[3] == pcode__BOOLEAN  ? v[3] ? ( void *) (*b[3]) : ( void *) (b[3])
                : t[3] == pcode__BYTE     ? v[3] ? ( void *) (*y[3]) : ( void *) (y[3])
                : t[3] == pcode__SHORT    ? v[3] ? ( void *) (*s[3]) : ( void *) (s[3])
                : t[3] == pcode__INTEGER  ? v[3] ? ( void *) (*i[3]) : ( void *) (i[3])
                : t[3] == pcode__LONG     ? v[3] ? ( void *) (*l[3]) : ( void *) (l[3])
                : t[3] == pcode__SINGLE   ? v[3] ? ( void *) (*k[3]) : ( void *) (k[3])
                : t[3] == pcode__DOUBLE   ? v[3] ? ( void *) (*d[3]) : ( void *) (d[3])
                :                          (p[3])
                ,
                  t[4] == pcode__BOOLEAN  ? v[4] ? ( void *) (*b[4]) : ( void *) (b[4])
                : t[4] == pcode__BYTE     ? v[4] ? ( void *) (*y[4]) : ( void *) (y[4])
                : t[4] == pcode__SHORT    ? v[4] ? ( void *) (*s[4]) : ( void *) (s[4])
                : t[4] == pcode__INTEGER  ? v[4] ? ( void *) (*i[4]) : ( void *) (i[4])
                : t[4] == pcode__LONG     ? v[4] ? ( void *) (*l[4]) : ( void *) (l[4])
                : t[4] == pcode__SINGLE   ? v[4] ? ( void *) (*k[4]) : ( void *) (k[4])
                : t[4] == pcode__DOUBLE   ? v[4] ? ( void *) (*d[4]) : ( void *) (d[4])
                :                          (p[4])
                ,
                  t[5] == pcode__BOOLEAN  ? v[5] ? ( void *) (*b[5]) : ( void *) (b[5])
                : t[5] == pcode__BYTE     ? v[5] ? ( void *) (*y[5]) : ( void *) (y[5])
                : t[5] == pcode__SHORT    ? v[5] ? ( void *) (*s[5]) : ( void *) (s[5])
                : t[5] == pcode__INTEGER  ? v[5] ? ( void *) (*i[5]) : ( void *) (i[5])
                : t[5] == pcode__LONG     ? v[5] ? ( void *) (*l[5]) : ( void *) (l[5])
                : t[5] == pcode__SINGLE   ? v[5] ? ( void *) (*k[5]) : ( void *) (k[5])
                : t[5] == pcode__DOUBLE   ? v[5] ? ( void *) (*d[5]) : ( void *) (d[5])
                :                          (p[5])
                ,
                  t[6] == pcode__BOOLEAN  ? v[6] ? ( void *) (*b[6]) : ( void *) (b[6])
                : t[6] == pcode__BYTE     ? v[6] ? ( void *) (*y[6]) : ( void *) (y[6])
                : t[6] == pcode__SHORT    ? v[6] ? ( void *) (*s[6]) : ( void *) (s[6])
                : t[6] == pcode__INTEGER  ? v[6] ? ( void *) (*i[6]) : ( void *) (i[6])
                : t[6] == pcode__LONG     ? v[6] ? ( void *) (*l[6]) : ( void *) (l[6])
                : t[6] == pcode__SINGLE   ? v[6] ? ( void *) (*k[6]) : ( void *) (k[6])
                : t[6] == pcode__DOUBLE   ? v[6] ? ( void *) (*d[6]) : ( void *) (d[6])
                :                          (p[6])
                ,
                  t[7] == pcode__BOOLEAN  ? v[7] ? ( void *) (*b[7]) : ( void *) (b[7])
                : t[7] == pcode__BYTE     ? v[7] ? ( void *) (*y[7]) : ( void *) (y[7])
                : t[7] == pcode__SHORT    ? v[7] ? ( void *) (*s[7]) : ( void *) (s[7])
                : t[7] == pcode__INTEGER  ? v[7] ? ( void *) (*i[7]) : ( void *) (i[7])
                : t[7] == pcode__LONG     ? v[7] ? ( void *) (*l[7]) : ( void *) (l[7])
                : t[7] == pcode__SINGLE   ? v[7] ? ( void *) (*k[7]) : ( void *) (k[7])
                : t[7] == pcode__DOUBLE   ? v[7] ? ( void *) (*d[7]) : ( void *) (d[7])
                :                          (p[7])
                );
              else return runtimeError(utility::con(function, " function call failed. ", ll[lib]->errorString()));
              myStack->pushShort(rs);
            }
            break;
          case 9:
            {
              short_c9 c = (short_c9) ll[lib]->resolve( function );
              if (c) rs = c (
                  t[0] == pcode__BOOLEAN  ? v[0] ? ( void *) (*b[0]) : ( void *) (b[0])
                : t[0] == pcode__BYTE     ? v[0] ? ( void *) (*y[0]) : ( void *) (y[0])
                : t[0] == pcode__SHORT    ? v[0] ? ( void *) (*s[0]) : ( void *) (s[0])
                : t[0] == pcode__INTEGER  ? v[0] ? ( void *) (*i[0]) : ( void *) (i[0])
                : t[0] == pcode__LONG     ? v[0] ? ( void *) (*l[0]) : ( void *) (l[0])
                : t[0] == pcode__SINGLE   ? v[0] ? ( void *) (*k[0]) : ( void *) (k[0])
                : t[0] == pcode__DOUBLE   ? v[0] ? ( void *) (*d[0]) : ( void *) (d[0])
                :                          (p[0])
                ,
                  t[1] == pcode__BOOLEAN  ? v[1] ? ( void *) (*b[1]) : ( void *) (b[1])
                : t[1] == pcode__BYTE     ? v[1] ? ( void *) (*y[1]) : ( void *) (y[1])
                : t[1] == pcode__SHORT    ? v[1] ? ( void *) (*s[1]) : ( void *) (s[1])
                : t[1] == pcode__INTEGER  ? v[1] ? ( void *) (*i[1]) : ( void *) (i[1])
                : t[1] == pcode__LONG     ? v[1] ? ( void *) (*l[1]) : ( void *) (l[1])
                : t[1] == pcode__SINGLE   ? v[1] ? ( void *) (*k[1]) : ( void *) (k[1])
                : t[1] == pcode__DOUBLE   ? v[1] ? ( void *) (*d[1]) : ( void *) (d[1])
                :                          (p[1])
                ,
                  t[2] == pcode__BOOLEAN  ? v[2] ? ( void *) (*b[2]) : ( void *) (b[2])
                : t[2] == pcode__BYTE     ? v[2] ? ( void *) (*y[2]) : ( void *) (y[2])
                : t[2] == pcode__SHORT    ? v[2] ? ( void *) (*s[2]) : ( void *) (s[2])
                : t[2] == pcode__INTEGER  ? v[2] ? ( void *) (*i[2]) : ( void *) (i[2])
                : t[2] == pcode__LONG     ? v[2] ? ( void *) (*l[2]) : ( void *) (l[2])
                : t[2] == pcode__SINGLE   ? v[2] ? ( void *) (*k[2]) : ( void *) (k[2])
                : t[2] == pcode__DOUBLE   ? v[2] ? ( void *) (*d[2]) : ( void *) (d[2])
                :                          (p[2])
                ,
                  t[3] == pcode__BOOLEAN  ? v[3] ? ( void *) (*b[3]) : ( void *) (b[3])
                : t[3] == pcode__BYTE     ? v[3] ? ( void *) (*y[3]) : ( void *) (y[3])
                : t[3] == pcode__SHORT    ? v[3] ? ( void *) (*s[3]) : ( void *) (s[3])
                : t[3] == pcode__INTEGER  ? v[3] ? ( void *) (*i[3]) : ( void *) (i[3])
                : t[3] == pcode__LONG     ? v[3] ? ( void *) (*l[3]) : ( void *) (l[3])
                : t[3] == pcode__SINGLE   ? v[3] ? ( void *) (*k[3]) : ( void *) (k[3])
                : t[3] == pcode__DOUBLE   ? v[3] ? ( void *) (*d[3]) : ( void *) (d[3])
                :                          (p[3])
                ,
                  t[4] == pcode__BOOLEAN  ? v[4] ? ( void *) (*b[4]) : ( void *) (b[4])
                : t[4] == pcode__BYTE     ? v[4] ? ( void *) (*y[4]) : ( void *) (y[4])
                : t[4] == pcode__SHORT    ? v[4] ? ( void *) (*s[4]) : ( void *) (s[4])
                : t[4] == pcode__INTEGER  ? v[4] ? ( void *) (*i[4]) : ( void *) (i[4])
                : t[4] == pcode__LONG     ? v[4] ? ( void *) (*l[4]) : ( void *) (l[4])
                : t[4] == pcode__SINGLE   ? v[4] ? ( void *) (*k[4]) : ( void *) (k[4])
                : t[4] == pcode__DOUBLE   ? v[4] ? ( void *) (*d[4]) : ( void *) (d[4])
                :                          (p[4])
                ,
                  t[5] == pcode__BOOLEAN  ? v[5] ? ( void *) (*b[5]) : ( void *) (b[5])
                : t[5] == pcode__BYTE     ? v[5] ? ( void *) (*y[5]) : ( void *) (y[5])
                : t[5] == pcode__SHORT    ? v[5] ? ( void *) (*s[5]) : ( void *) (s[5])
                : t[5] == pcode__INTEGER  ? v[5] ? ( void *) (*i[5]) : ( void *) (i[5])
                : t[5] == pcode__LONG     ? v[5] ? ( void *) (*l[5]) : ( void *) (l[5])
                : t[5] == pcode__SINGLE   ? v[5] ? ( void *) (*k[5]) : ( void *) (k[5])
                : t[5] == pcode__DOUBLE   ? v[5] ? ( void *) (*d[5]) : ( void *) (d[5])
                :                          (p[5])
                ,
                  t[6] == pcode__BOOLEAN  ? v[6] ? ( void *) (*b[6]) : ( void *) (b[6])
                : t[6] == pcode__BYTE     ? v[6] ? ( void *) (*y[6]) : ( void *) (y[6])
                : t[6] == pcode__SHORT    ? v[6] ? ( void *) (*s[6]) : ( void *) (s[6])
                : t[6] == pcode__INTEGER  ? v[6] ? ( void *) (*i[6]) : ( void *) (i[6])
                : t[6] == pcode__LONG     ? v[6] ? ( void *) (*l[6]) : ( void *) (l[6])
                : t[6] == pcode__SINGLE   ? v[6] ? ( void *) (*k[6]) : ( void *) (k[6])
                : t[6] == pcode__DOUBLE   ? v[6] ? ( void *) (*d[6]) : ( void *) (d[6])
                :                          (p[6])
                ,
                  t[7] == pcode__BOOLEAN  ? v[7] ? ( void *) (*b[7]) : ( void *) (b[7])
                : t[7] == pcode__BYTE     ? v[7] ? ( void *) (*y[7]) : ( void *) (y[7])
                : t[7] == pcode__SHORT    ? v[7] ? ( void *) (*s[7]) : ( void *) (s[7])
                : t[7] == pcode__INTEGER  ? v[7] ? ( void *) (*i[7]) : ( void *) (i[7])
                : t[7] == pcode__LONG     ? v[7] ? ( void *) (*l[7]) : ( void *) (l[7])
                : t[7] == pcode__SINGLE   ? v[7] ? ( void *) (*k[7]) : ( void *) (k[7])
                : t[7] == pcode__DOUBLE   ? v[7] ? ( void *) (*d[7]) : ( void *) (d[7])
                :                          (p[7])
                ,
                  t[8] == pcode__BOOLEAN  ? v[8] ? ( void *) (*b[8]) : ( void *) (b[8])
                : t[8] == pcode__BYTE     ? v[8] ? ( void *) (*y[8]) : ( void *) (y[8])
                : t[8] == pcode__SHORT    ? v[8] ? ( void *) (*s[8]) : ( void *) (s[8])
                : t[8] == pcode__INTEGER  ? v[8] ? ( void *) (*i[8]) : ( void *) (i[8])
                : t[8] == pcode__LONG     ? v[8] ? ( void *) (*l[8]) : ( void *) (l[8])
                : t[8] == pcode__SINGLE   ? v[8] ? ( void *) (*k[8]) : ( void *) (k[8])
                : t[8] == pcode__DOUBLE   ? v[8] ? ( void *) (*d[8]) : ( void *) (d[8])
                :                          (p[8])
                );
              else return runtimeError(utility::con(function, " function call failed. ", ll[lib]->errorString()));
              myStack->pushShort(rs);
            }
            break;
          default:
            return runtimeError(utility::con(function, ": Too much arguments (max. 9 allowed) when calling declare function."));
            break;
         }
         break;
       default: // must be pointer type
       case pcode__INTEGER:
        switch(count){
          case 0:
            {
              int_c0 c = (int_c0) ll[lib]->resolve( function );
              if (c) ri = c (
              );
              else return runtimeError(utility::con(function, " function call failed. ", ll[lib]->errorString()));
              myStack->pushInteger(ri);
            }
            break;
          case 1:
            {
              int_c1 c = (int_c1) ll[lib]->resolve( function );
              if (c) ri = c (
                  t[0] == pcode__BOOLEAN  ? v[0] ? ( void *) (*b[0]) : ( void *) (b[0])
                : t[0] == pcode__BYTE     ? v[0] ? ( void *) (*y[0]) : ( void *) (y[0])
                : t[0] == pcode__SHORT    ? v[0] ? ( void *) (*s[0]) : ( void *) (s[0])
                : t[0] == pcode__INTEGER  ? v[0] ? ( void *) (*i[0]) : ( void *) (i[0])
                : t[0] == pcode__LONG     ? v[0] ? ( void *) (*l[0]) : ( void *) (l[0])
                : t[0] == pcode__SINGLE   ? v[0] ? ( void *) (*k[0]) : ( void *) (k[0])
                : t[0] == pcode__DOUBLE   ? v[0] ? ( void *) (*d[0]) : ( void *) (d[0])
                :                          (p[0])
              );
              else return runtimeError(utility::con(function, " function call failed. ", ll[lib]->errorString()));
              myStack->pushInteger(ri);
            }
            break;
          case 2:
            {
              int_c2 c = (int_c2) ll[lib]->resolve( function );

              if (c) ri = c (
                  t[0] == pcode__BOOLEAN  ? v[0] ? ( void *) (*b[0]) : ( void *) (b[0])
                : t[0] == pcode__BYTE     ? v[0] ? ( void *) (*y[0]) : ( void *) (y[0])
                : t[0] == pcode__SHORT    ? v[0] ? ( void *) (*s[0]) : ( void *) (s[0])
                : t[0] == pcode__INTEGER  ? v[0] ? ( void *) (*i[0]) : ( void *) (i[0])
                : t[0] == pcode__LONG     ? v[0] ? ( void *) (*l[0]) : ( void *) (l[0])
                : t[0] == pcode__SINGLE   ? v[0] ? ( void *) (*k[0]) : ( void *) (k[0])
                : t[0] == pcode__DOUBLE   ? v[0] ? ( void *) (*d[0]) : ( void *) (d[0])
                :                          (p[0])
                ,
                  t[1] == pcode__BOOLEAN  ? v[1] ? ( void *) (*b[1]) : ( void *) (b[1])
                : t[1] == pcode__BYTE     ? v[1] ? ( void *) (*y[1]) : ( void *) (y[1])
                : t[1] == pcode__SHORT    ? v[1] ? ( void *) (*s[1]) : ( void *) (s[1])
                : t[1] == pcode__INTEGER  ? v[1] ? ( void *) (*i[1]) : ( void *) (i[1])
                : t[1] == pcode__LONG     ? v[1] ? ( void *) (*l[1]) : ( void *) (l[1])
                : t[1] == pcode__SINGLE   ? v[1] ? ( void *) (*k[1]) : ( void *) (k[1])
                : t[1] == pcode__DOUBLE   ? v[1] ? ( void *) (*d[1]) : ( void *) (d[1])
                :                          (p[1])
              );
              else return runtimeError(utility::con(function, " function call failed. ", ll[lib]->errorString()));
              myStack->pushInteger(ri);
            }
            break;
          case 3:
            {
              /*
              {
              int_c3 c = (int_c3) ll[lib]->resolve( function );
              if (c) ri = c (( void *) (i[0]), ( void *) (i[1]), ( void *) (*i[2]));
              }*/

              int_c3 c = (int_c3) ll[lib]->resolve( function );
              if (c) ri = c (
                  t[0] == pcode__BOOLEAN  ? v[0] ? ( void *) (*b[0]) : ( void *) (b[0])
                : t[0] == pcode__BYTE     ? v[0] ? ( void *) (*y[0]) : ( void *) (y[0])
                : t[0] == pcode__SHORT    ? v[0] ? ( void *) (*s[0]) : ( void *) (s[0])
                : t[0] == pcode__INTEGER  ? v[0] ? ( void *) (*i[0]) : ( void *) (i[0])
                : t[0] == pcode__LONG     ? v[0] ? ( void *) (*l[0]) : ( void *) (l[0])
                : t[0] == pcode__SINGLE   ? v[0] ? ( void *) (*k[0]) : ( void *) (k[0])
                : t[0] == pcode__DOUBLE   ? v[0] ? ( void *) (*d[0]) : ( void *) (d[0])
                :                          (p[0])
                ,
                  t[1] == pcode__BOOLEAN  ? v[1] ? ( void *) (*b[1]) : ( void *) (b[1])
                : t[1] == pcode__BYTE     ? v[1] ? ( void *) (*y[1]) : ( void *) (y[1])
                : t[1] == pcode__SHORT    ? v[1] ? ( void *) (*s[1]) : ( void *) (s[1])
                : t[1] == pcode__INTEGER  ? v[1] ? ( void *) (*i[1]) : ( void *) (i[1])
                : t[1] == pcode__LONG     ? v[1] ? ( void *) (*l[1]) : ( void *) (l[1])
                : t[1] == pcode__SINGLE   ? v[1] ? ( void *) (*k[1]) : ( void *) (k[1])
                : t[1] == pcode__DOUBLE   ? v[1] ? ( void *) (*d[1]) : ( void *) (d[1])
                :                          (p[1])
                ,
                  t[2] == pcode__BOOLEAN  ? v[2] ? ( void *) (*b[2]) : ( void *) (b[2])
                : t[2] == pcode__BYTE     ? v[2] ? ( void *) (*y[2]) : ( void *) (y[2])
                : t[2] == pcode__SHORT    ? v[2] ? ( void *) (*s[2]) : ( void *) (s[2])
                : t[2] == pcode__INTEGER  ? v[2] ? ( void *) (*i[2]) : ( void *) (i[2])
                : t[2] == pcode__LONG     ? v[2] ? ( void *) (*l[2]) : ( void *) (l[2])
                : t[2] == pcode__SINGLE   ? v[2] ? ( void *) (*k[2]) : ( void *) (k[2])
                : t[2] == pcode__DOUBLE   ? v[2] ? ( void *) (*d[2]) : ( void *) (d[2])
                :                          (p[2])
              );
              else return runtimeError(utility::con(function, " function call failed. ", ll[lib]->errorString()));
              myStack->pushInteger(ri);
            }
            break;
          case 4:
            {
              int_c4 c = (int_c4) ll[lib]->resolve( function );
              if (c) ri = c (
                  t[0] == pcode__BOOLEAN  ? v[0] ? ( void *) (*b[0]) : ( void *) (b[0])
                : t[0] == pcode__BYTE     ? v[0] ? ( void *) (*y[0]) : ( void *) (y[0])
                : t[0] == pcode__SHORT    ? v[0] ? ( void *) (*s[0]) : ( void *) (s[0])
                : t[0] == pcode__INTEGER  ? v[0] ? ( void *) (*i[0]) : ( void *) (i[0])
                : t[0] == pcode__LONG     ? v[0] ? ( void *) (*l[0]) : ( void *) (l[0])
                : t[0] == pcode__SINGLE   ? v[0] ? ( void *) (*k[0]) : ( void *) (k[0])
                : t[0] == pcode__DOUBLE   ? v[0] ? ( void *) (*d[0]) : ( void *) (d[0])
                :                          (p[0])
                ,
                  t[1] == pcode__BOOLEAN  ? v[1] ? ( void *) (*b[1]) : ( void *) (b[1])
                : t[1] == pcode__BYTE     ? v[1] ? ( void *) (*y[1]) : ( void *) (y[1])
                : t[1] == pcode__SHORT    ? v[1] ? ( void *) (*s[1]) : ( void *) (s[1])
                : t[1] == pcode__INTEGER  ? v[1] ? ( void *) (*i[1]) : ( void *) (i[1])
                : t[1] == pcode__LONG     ? v[1] ? ( void *) (*l[1]) : ( void *) (l[1])
                : t[1] == pcode__SINGLE   ? v[1] ? ( void *) (*k[1]) : ( void *) (k[1])
                : t[1] == pcode__DOUBLE   ? v[1] ? ( void *) (*d[1]) : ( void *) (d[1])
                :                          (p[1])
                ,
                  t[2] == pcode__BOOLEAN  ? v[2] ? ( void *) (*b[2]) : ( void *) (b[2])
                : t[2] == pcode__BYTE     ? v[2] ? ( void *) (*y[2]) : ( void *) (y[2])
                : t[2] == pcode__SHORT    ? v[2] ? ( void *) (*s[2]) : ( void *) (s[2])
                : t[2] == pcode__INTEGER  ? v[2] ? ( void *) (*i[2]) : ( void *) (i[2])
                : t[2] == pcode__LONG     ? v[2] ? ( void *) (*l[2]) : ( void *) (l[2])
                : t[2] == pcode__SINGLE   ? v[2] ? ( void *) (*k[2]) : ( void *) (k[2])
                : t[2] == pcode__DOUBLE   ? v[2] ? ( void *) (*d[2]) : ( void *) (d[2])
                :                          (p[2])
                ,
                  t[3] == pcode__BOOLEAN  ? v[3] ? ( void *) (*b[3]) : ( void *) (b[3])
                : t[3] == pcode__BYTE     ? v[3] ? ( void *) (*y[3]) : ( void *) (y[3])
                : t[3] == pcode__SHORT    ? v[3] ? ( void *) (*s[3]) : ( void *) (s[3])
                : t[3] == pcode__INTEGER  ? v[3] ? ( void *) (*i[3]) : ( void *) (i[3])
                : t[3] == pcode__LONG     ? v[3] ? ( void *) (*l[3]) : ( void *) (l[3])
                : t[3] == pcode__SINGLE   ? v[3] ? ( void *) (*k[3]) : ( void *) (k[3])
                : t[3] == pcode__DOUBLE   ? v[3] ? ( void *) (*d[3]) : ( void *) (d[3])
                :                          (p[3])
              );
              else return runtimeError(utility::con(function, " function call failed. ", ll[lib]->errorString()));
              myStack->pushInteger(ri);
            }
            break;
          case 5:
            {
              int_c5 c = (int_c5) ll[lib]->resolve( function );
              if (c) ri = c (
                  t[0] == pcode__BOOLEAN  ? v[0] ? ( void *) (*b[0]) : ( void *) (b[0])
                : t[0] == pcode__BYTE     ? v[0] ? ( void *) (*y[0]) : ( void *) (y[0])
                : t[0] == pcode__SHORT    ? v[0] ? ( void *) (*s[0]) : ( void *) (s[0])
                : t[0] == pcode__INTEGER  ? v[0] ? ( void *) (*i[0]) : ( void *) (i[0])
                : t[0] == pcode__LONG     ? v[0] ? ( void *) (*l[0]) : ( void *) (l[0])
                : t[0] == pcode__SINGLE   ? v[0] ? ( void *) (*k[0]) : ( void *) (k[0])
                : t[0] == pcode__DOUBLE   ? v[0] ? ( void *) (*d[0]) : ( void *) (d[0])
                :                          (p[0])
                ,
                  t[1] == pcode__BOOLEAN  ? v[1] ? ( void *) (*b[1]) : ( void *) (b[1])
                : t[1] == pcode__BYTE     ? v[1] ? ( void *) (*y[1]) : ( void *) (y[1])
                : t[1] == pcode__SHORT    ? v[1] ? ( void *) (*s[1]) : ( void *) (s[1])
                : t[1] == pcode__INTEGER  ? v[1] ? ( void *) (*i[1]) : ( void *) (i[1])
                : t[1] == pcode__LONG     ? v[1] ? ( void *) (*l[1]) : ( void *) (l[1])
                : t[1] == pcode__SINGLE   ? v[1] ? ( void *) (*k[1]) : ( void *) (k[1])
                : t[1] == pcode__DOUBLE   ? v[1] ? ( void *) (*d[1]) : ( void *) (d[1])
                :                          (p[1])
                ,
                  t[2] == pcode__BOOLEAN  ? v[2] ? ( void *) (*b[2]) : ( void *) (b[2])
                : t[2] == pcode__BYTE     ? v[2] ? ( void *) (*y[2]) : ( void *) (y[2])
                : t[2] == pcode__SHORT    ? v[2] ? ( void *) (*s[2]) : ( void *) (s[2])
                : t[2] == pcode__INTEGER  ? v[2] ? ( void *) (*i[2]) : ( void *) (i[2])
                : t[2] == pcode__LONG     ? v[2] ? ( void *) (*l[2]) : ( void *) (l[2])
                : t[2] == pcode__SINGLE   ? v[2] ? ( void *) (*k[2]) : ( void *) (k[2])
                : t[2] == pcode__DOUBLE   ? v[2] ? ( void *) (*d[2]) : ( void *) (d[2])
                :                          (p[2])
                ,
                  t[3] == pcode__BOOLEAN  ? v[3] ? ( void *) (*b[3]) : ( void *) (b[3])
                : t[3] == pcode__BYTE     ? v[3] ? ( void *) (*y[3]) : ( void *) (y[3])
                : t[3] == pcode__SHORT    ? v[3] ? ( void *) (*s[3]) : ( void *) (s[3])
                : t[3] == pcode__INTEGER  ? v[3] ? ( void *) (*i[3]) : ( void *) (i[3])
                : t[3] == pcode__LONG     ? v[3] ? ( void *) (*l[3]) : ( void *) (l[3])
                : t[3] == pcode__SINGLE   ? v[3] ? ( void *) (*k[3]) : ( void *) (k[3])
                : t[3] == pcode__DOUBLE   ? v[3] ? ( void *) (*d[3]) : ( void *) (d[3])
                :                          (p[3])
                ,
                  t[4] == pcode__BOOLEAN  ? v[4] ? ( void *) (*b[4]) : ( void *) (b[4])
                : t[4] == pcode__BYTE     ? v[4] ? ( void *) (*y[4]) : ( void *) (y[4])
                : t[4] == pcode__SHORT    ? v[4] ? ( void *) (*s[4]) : ( void *) (s[4])
                : t[4] == pcode__INTEGER  ? v[4] ? ( void *) (*i[4]) : ( void *) (i[4])
                : t[4] == pcode__LONG     ? v[4] ? ( void *) (*l[4]) : ( void *) (l[4])
                : t[4] == pcode__SINGLE   ? v[4] ? ( void *) (*k[4]) : ( void *) (k[4])
                : t[4] == pcode__DOUBLE   ? v[4] ? ( void *) (*d[4]) : ( void *) (d[4])
                :                          (p[4])
              );
              else return runtimeError(utility::con(function, " function call failed. ", ll[lib]->errorString()));
              myStack->pushInteger(ri);
            }
            break;
          case 6:
            {
              int_c6 c = (int_c6) ll[lib]->resolve( function );
              if (c) ri = c (
                  t[0] == pcode__BOOLEAN  ? v[0] ? ( void *) (*b[0]) : ( void *) (b[0])
                : t[0] == pcode__BYTE     ? v[0] ? ( void *) (*y[0]) : ( void *) (y[0])
                : t[0] == pcode__SHORT    ? v[0] ? ( void *) (*s[0]) : ( void *) (s[0])
                : t[0] == pcode__INTEGER  ? v[0] ? ( void *) (*i[0]) : ( void *) (i[0])
                : t[0] == pcode__LONG     ? v[0] ? ( void *) (*l[0]) : ( void *) (l[0])
                : t[0] == pcode__SINGLE   ? v[0] ? ( void *) (*k[0]) : ( void *) (k[0])
                : t[0] == pcode__DOUBLE   ? v[0] ? ( void *) (*d[0]) : ( void *) (d[0])
                :                          (p[0])
                ,
                  t[1] == pcode__BOOLEAN  ? v[1] ? ( void *) (*b[1]) : ( void *) (b[1])
                : t[1] == pcode__BYTE     ? v[1] ? ( void *) (*y[1]) : ( void *) (y[1])
                : t[1] == pcode__SHORT    ? v[1] ? ( void *) (*s[1]) : ( void *) (s[1])
                : t[1] == pcode__INTEGER  ? v[1] ? ( void *) (*i[1]) : ( void *) (i[1])
                : t[1] == pcode__LONG     ? v[1] ? ( void *) (*l[1]) : ( void *) (l[1])
                : t[1] == pcode__SINGLE   ? v[1] ? ( void *) (*k[1]) : ( void *) (k[1])
                : t[1] == pcode__DOUBLE   ? v[1] ? ( void *) (*d[1]) : ( void *) (d[1])
                :                          (p[1])
                ,
                  t[2] == pcode__BOOLEAN  ? v[2] ? ( void *) (*b[2]) : ( void *) (b[2])
                : t[2] == pcode__BYTE     ? v[2] ? ( void *) (*y[2]) : ( void *) (y[2])
                : t[2] == pcode__SHORT    ? v[2] ? ( void *) (*s[2]) : ( void *) (s[2])
                : t[2] == pcode__INTEGER  ? v[2] ? ( void *) (*i[2]) : ( void *) (i[2])
                : t[2] == pcode__LONG     ? v[2] ? ( void *) (*l[2]) : ( void *) (l[2])
                : t[2] == pcode__SINGLE   ? v[2] ? ( void *) (*k[2]) : ( void *) (k[2])
                : t[2] == pcode__DOUBLE   ? v[2] ? ( void *) (*d[2]) : ( void *) (d[2])
                :                          (p[2])
                ,
                  t[3] == pcode__BOOLEAN  ? v[3] ? ( void *) (*b[3]) : ( void *) (b[3])
                : t[3] == pcode__BYTE     ? v[3] ? ( void *) (*y[3]) : ( void *) (y[3])
                : t[3] == pcode__SHORT    ? v[3] ? ( void *) (*s[3]) : ( void *) (s[3])
                : t[3] == pcode__INTEGER  ? v[3] ? ( void *) (*i[3]) : ( void *) (i[3])
                : t[3] == pcode__LONG     ? v[3] ? ( void *) (*l[3]) : ( void *) (l[3])
                : t[3] == pcode__SINGLE   ? v[3] ? ( void *) (*k[3]) : ( void *) (k[3])
                : t[3] == pcode__DOUBLE   ? v[3] ? ( void *) (*d[3]) : ( void *) (d[3])
                :                          (p[3])
                ,
                  t[4] == pcode__BOOLEAN  ? v[4] ? ( void *) (*b[4]) : ( void *) (b[4])
                : t[4] == pcode__BYTE     ? v[4] ? ( void *) (*y[4]) : ( void *) (y[4])
                : t[4] == pcode__SHORT    ? v[4] ? ( void *) (*s[4]) : ( void *) (s[4])
                : t[4] == pcode__INTEGER  ? v[4] ? ( void *) (*i[4]) : ( void *) (i[4])
                : t[4] == pcode__LONG     ? v[4] ? ( void *) (*l[4]) : ( void *) (l[4])
                : t[4] == pcode__SINGLE   ? v[4] ? ( void *) (*k[4]) : ( void *) (k[4])
                : t[4] == pcode__DOUBLE   ? v[4] ? ( void *) (*d[4]) : ( void *) (d[4])
                :                          (p[4])
                ,
                  t[5] == pcode__BOOLEAN  ? v[5] ? ( void *) (*b[5]) : ( void *) (b[5])
                : t[5] == pcode__BYTE     ? v[5] ? ( void *) (*y[5]) : ( void *) (y[5])
                : t[5] == pcode__SHORT    ? v[5] ? ( void *) (*s[5]) : ( void *) (s[5])
                : t[5] == pcode__INTEGER  ? v[5] ? ( void *) (*i[5]) : ( void *) (i[5])
                : t[5] == pcode__LONG     ? v[5] ? ( void *) (*l[5]) : ( void *) (l[5])
                : t[5] == pcode__SINGLE   ? v[5] ? ( void *) (*k[5]) : ( void *) (k[5])
                : t[5] == pcode__DOUBLE   ? v[5] ? ( void *) (*d[5]) : ( void *) (d[5])
                :                          (p[5])
              );
              else return runtimeError(utility::con(function, " function call failed. ", ll[lib]->errorString()));
              myStack->pushInteger(ri);
            }
            break;
          case 7:
            {
              int_c7 c = (int_c7) ll[lib]->resolve( function );
              if (c) ri = c (
                  t[0] == pcode__BOOLEAN  ? v[0] ? ( void *) (*b[0]) : ( void *) (b[0])
                : t[0] == pcode__BYTE     ? v[0] ? ( void *) (*y[0]) : ( void *) (y[0])
                : t[0] == pcode__SHORT    ? v[0] ? ( void *) (*s[0]) : ( void *) (s[0])
                : t[0] == pcode__INTEGER  ? v[0] ? ( void *) (*i[0]) : ( void *) (i[0])
                : t[0] == pcode__LONG     ? v[0] ? ( void *) (*l[0]) : ( void *) (l[0])
                : t[0] == pcode__SINGLE   ? v[0] ? ( void *) (*k[0]) : ( void *) (k[0])
                : t[0] == pcode__DOUBLE   ? v[0] ? ( void *) (*d[0]) : ( void *) (d[0])
                :                          (p[0])
                ,
                  t[1] == pcode__BOOLEAN  ? v[1] ? ( void *) (*b[1]) : ( void *) (b[1])
                : t[1] == pcode__BYTE     ? v[1] ? ( void *) (*y[1]) : ( void *) (y[1])
                : t[1] == pcode__SHORT    ? v[1] ? ( void *) (*s[1]) : ( void *) (s[1])
                : t[1] == pcode__INTEGER  ? v[1] ? ( void *) (*i[1]) : ( void *) (i[1])
                : t[1] == pcode__LONG     ? v[1] ? ( void *) (*l[1]) : ( void *) (l[1])
                : t[1] == pcode__SINGLE   ? v[1] ? ( void *) (*k[1]) : ( void *) (k[1])
                : t[1] == pcode__DOUBLE   ? v[1] ? ( void *) (*d[1]) : ( void *) (d[1])
                :                          (p[1])
                ,
                  t[2] == pcode__BOOLEAN  ? v[2] ? ( void *) (*b[2]) : ( void *) (b[2])
                : t[2] == pcode__BYTE     ? v[2] ? ( void *) (*y[2]) : ( void *) (y[2])
                : t[2] == pcode__SHORT    ? v[2] ? ( void *) (*s[2]) : ( void *) (s[2])
                : t[2] == pcode__INTEGER  ? v[2] ? ( void *) (*i[2]) : ( void *) (i[2])
                : t[2] == pcode__LONG     ? v[2] ? ( void *) (*l[2]) : ( void *) (l[2])
                : t[2] == pcode__SINGLE   ? v[2] ? ( void *) (*k[2]) : ( void *) (k[2])
                : t[2] == pcode__DOUBLE   ? v[2] ? ( void *) (*d[2]) : ( void *) (d[2])
                :                          (p[2])
                ,
                  t[3] == pcode__BOOLEAN  ? v[3] ? ( void *) (*b[3]) : ( void *) (b[3])
                : t[3] == pcode__BYTE     ? v[3] ? ( void *) (*y[3]) : ( void *) (y[3])
                : t[3] == pcode__SHORT    ? v[3] ? ( void *) (*s[3]) : ( void *) (s[3])
                : t[3] == pcode__INTEGER  ? v[3] ? ( void *) (*i[3]) : ( void *) (i[3])
                : t[3] == pcode__LONG     ? v[3] ? ( void *) (*l[3]) : ( void *) (l[3])
                : t[3] == pcode__SINGLE   ? v[3] ? ( void *) (*k[3]) : ( void *) (k[3])
                : t[3] == pcode__DOUBLE   ? v[3] ? ( void *) (*d[3]) : ( void *) (d[3])
                :                          (p[3])
                ,
                  t[4] == pcode__BOOLEAN  ? v[4] ? ( void *) (*b[4]) : ( void *) (b[4])
                : t[4] == pcode__BYTE     ? v[4] ? ( void *) (*y[4]) : ( void *) (y[4])
                : t[4] == pcode__SHORT    ? v[4] ? ( void *) (*s[4]) : ( void *) (s[4])
                : t[4] == pcode__INTEGER  ? v[4] ? ( void *) (*i[4]) : ( void *) (i[4])
                : t[4] == pcode__LONG     ? v[4] ? ( void *) (*l[4]) : ( void *) (l[4])
                : t[4] == pcode__SINGLE   ? v[4] ? ( void *) (*k[4]) : ( void *) (k[4])
                : t[4] == pcode__DOUBLE   ? v[4] ? ( void *) (*d[4]) : ( void *) (d[4])
                :                          (p[4])
                ,
                  t[5] == pcode__BOOLEAN  ? v[5] ? ( void *) (*b[5]) : ( void *) (b[5])
                : t[5] == pcode__BYTE     ? v[5] ? ( void *) (*y[5]) : ( void *) (y[5])
                : t[5] == pcode__SHORT    ? v[5] ? ( void *) (*s[5]) : ( void *) (s[5])
                : t[5] == pcode__INTEGER  ? v[5] ? ( void *) (*i[5]) : ( void *) (i[5])
                : t[5] == pcode__LONG     ? v[5] ? ( void *) (*l[5]) : ( void *) (l[5])
                : t[5] == pcode__SINGLE   ? v[5] ? ( void *) (*k[5]) : ( void *) (k[5])
                : t[5] == pcode__DOUBLE   ? v[5] ? ( void *) (*d[5]) : ( void *) (d[5])
                :                          (p[5])
                ,
                  t[6] == pcode__BOOLEAN  ? v[6] ? ( void *) (*b[6]) : ( void *) (b[6])
                : t[6] == pcode__BYTE     ? v[6] ? ( void *) (*y[6]) : ( void *) (y[6])
                : t[6] == pcode__SHORT    ? v[6] ? ( void *) (*s[6]) : ( void *) (s[6])
                : t[6] == pcode__INTEGER  ? v[6] ? ( void *) (*i[6]) : ( void *) (i[6])
                : t[6] == pcode__LONG     ? v[6] ? ( void *) (*l[6]) : ( void *) (l[6])
                : t[6] == pcode__SINGLE   ? v[6] ? ( void *) (*k[6]) : ( void *) (k[6])
                : t[6] == pcode__DOUBLE   ? v[6] ? ( void *) (*d[6]) : ( void *) (d[6])
                :                          (p[6])
              );
              else return runtimeError(utility::con(function, " function call failed. ", ll[lib]->errorString()));
              myStack->pushInteger(ri);
            }
            break;
          case 8:
            {
              int_c8 c = (int_c8) ll[lib]->resolve( function );
              if (c) ri = c (
                  t[0] == pcode__BOOLEAN  ? v[0] ? ( void *) (*b[0]) : ( void *) (b[0])
                : t[0] == pcode__BYTE     ? v[0] ? ( void *) (*y[0]) : ( void *) (y[0])
                : t[0] == pcode__SHORT    ? v[0] ? ( void *) (*s[0]) : ( void *) (s[0])
                : t[0] == pcode__INTEGER  ? v[0] ? ( void *) (*i[0]) : ( void *) (i[0])
                : t[0] == pcode__LONG     ? v[0] ? ( void *) (*l[0]) : ( void *) (l[0])
                : t[0] == pcode__SINGLE   ? v[0] ? ( void *) (*k[0]) : ( void *) (k[0])
                : t[0] == pcode__DOUBLE   ? v[0] ? ( void *) (*d[0]) : ( void *) (d[0])
                :                          (p[0])
                ,
                  t[1] == pcode__BOOLEAN  ? v[1] ? ( void *) (*b[1]) : ( void *) (b[1])
                : t[1] == pcode__BYTE     ? v[1] ? ( void *) (*y[1]) : ( void *) (y[1])
                : t[1] == pcode__SHORT    ? v[1] ? ( void *) (*s[1]) : ( void *) (s[1])
                : t[1] == pcode__INTEGER  ? v[1] ? ( void *) (*i[1]) : ( void *) (i[1])
                : t[1] == pcode__LONG     ? v[1] ? ( void *) (*l[1]) : ( void *) (l[1])
                : t[1] == pcode__SINGLE   ? v[1] ? ( void *) (*k[1]) : ( void *) (k[1])
                : t[1] == pcode__DOUBLE   ? v[1] ? ( void *) (*d[1]) : ( void *) (d[1])
                :                          (p[1])
                ,
                  t[2] == pcode__BOOLEAN  ? v[2] ? ( void *) (*b[2]) : ( void *) (b[2])
                : t[2] == pcode__BYTE     ? v[2] ? ( void *) (*y[2]) : ( void *) (y[2])
                : t[2] == pcode__SHORT    ? v[2] ? ( void *) (*s[2]) : ( void *) (s[2])
                : t[2] == pcode__INTEGER  ? v[2] ? ( void *) (*i[2]) : ( void *) (i[2])
                : t[2] == pcode__LONG     ? v[2] ? ( void *) (*l[2]) : ( void *) (l[2])
                : t[2] == pcode__SINGLE   ? v[2] ? ( void *) (*k[2]) : ( void *) (k[2])
                : t[2] == pcode__DOUBLE   ? v[2] ? ( void *) (*d[2]) : ( void *) (d[2])
                :                          (p[2])
                ,
                  t[3] == pcode__BOOLEAN  ? v[3] ? ( void *) (*b[3]) : ( void *) (b[3])
                : t[3] == pcode__BYTE     ? v[3] ? ( void *) (*y[3]) : ( void *) (y[3])
                : t[3] == pcode__SHORT    ? v[3] ? ( void *) (*s[3]) : ( void *) (s[3])
                : t[3] == pcode__INTEGER  ? v[3] ? ( void *) (*i[3]) : ( void *) (i[3])
                : t[3] == pcode__LONG     ? v[3] ? ( void *) (*l[3]) : ( void *) (l[3])
                : t[3] == pcode__SINGLE   ? v[3] ? ( void *) (*k[3]) : ( void *) (k[3])
                : t[3] == pcode__DOUBLE   ? v[3] ? ( void *) (*d[3]) : ( void *) (d[3])
                :                          (p[3])
                ,
                  t[4] == pcode__BOOLEAN  ? v[4] ? ( void *) (*b[4]) : ( void *) (b[4])
                : t[4] == pcode__BYTE     ? v[4] ? ( void *) (*y[4]) : ( void *) (y[4])
                : t[4] == pcode__SHORT    ? v[4] ? ( void *) (*s[4]) : ( void *) (s[4])
                : t[4] == pcode__INTEGER  ? v[4] ? ( void *) (*i[4]) : ( void *) (i[4])
                : t[4] == pcode__LONG     ? v[4] ? ( void *) (*l[4]) : ( void *) (l[4])
                : t[4] == pcode__SINGLE   ? v[4] ? ( void *) (*k[4]) : ( void *) (k[4])
                : t[4] == pcode__DOUBLE   ? v[4] ? ( void *) (*d[4]) : ( void *) (d[4])
                :                          (p[4])
                ,
                  t[5] == pcode__BOOLEAN  ? v[5] ? ( void *) (*b[5]) : ( void *) (b[5])
                : t[5] == pcode__BYTE     ? v[5] ? ( void *) (*y[5]) : ( void *) (y[5])
                : t[5] == pcode__SHORT    ? v[5] ? ( void *) (*s[5]) : ( void *) (s[5])
                : t[5] == pcode__INTEGER  ? v[5] ? ( void *) (*i[5]) : ( void *) (i[5])
                : t[5] == pcode__LONG     ? v[5] ? ( void *) (*l[5]) : ( void *) (l[5])
                : t[5] == pcode__SINGLE   ? v[5] ? ( void *) (*k[5]) : ( void *) (k[5])
                : t[5] == pcode__DOUBLE   ? v[5] ? ( void *) (*d[5]) : ( void *) (d[5])
                :                          (p[5])
                ,
                  t[6] == pcode__BOOLEAN  ? v[6] ? ( void *) (*b[6]) : ( void *) (b[6])
                : t[6] == pcode__BYTE     ? v[6] ? ( void *) (*y[6]) : ( void *) (y[6])
                : t[6] == pcode__SHORT    ? v[6] ? ( void *) (*s[6]) : ( void *) (s[6])
                : t[6] == pcode__INTEGER  ? v[6] ? ( void *) (*i[6]) : ( void *) (i[6])
                : t[6] == pcode__LONG     ? v[6] ? ( void *) (*l[6]) : ( void *) (l[6])
                : t[6] == pcode__SINGLE   ? v[6] ? ( void *) (*k[6]) : ( void *) (k[6])
                : t[6] == pcode__DOUBLE   ? v[6] ? ( void *) (*d[6]) : ( void *) (d[6])
                :                          (p[6])
                ,
                  t[7] == pcode__BOOLEAN  ? v[7] ? ( void *) (*b[7]) : ( void *) (b[7])
                : t[7] == pcode__BYTE     ? v[7] ? ( void *) (*y[7]) : ( void *) (y[7])
                : t[7] == pcode__SHORT    ? v[7] ? ( void *) (*s[7]) : ( void *) (s[7])
                : t[7] == pcode__INTEGER  ? v[7] ? ( void *) (*i[7]) : ( void *) (i[7])
                : t[7] == pcode__LONG     ? v[7] ? ( void *) (*l[7]) : ( void *) (l[7])
                : t[7] == pcode__SINGLE   ? v[7] ? ( void *) (*k[7]) : ( void *) (k[7])
                : t[7] == pcode__DOUBLE   ? v[7] ? ( void *) (*d[7]) : ( void *) (d[7])
                :                          (p[7])
              );
              else return runtimeError(utility::con(function, " function call failed. ", ll[lib]->errorString()));
              myStack->pushInteger(ri);
            }
            break;
          case 9:
            {
              int_c9 c = (int_c9) ll[lib]->resolve( function );
              if (c) ri = c (
                  t[0] == pcode__BOOLEAN  ? v[0] ? ( void *) (*b[0]) : ( void *) (b[0])
                : t[0] == pcode__BYTE     ? v[0] ? ( void *) (*y[0]) : ( void *) (y[0])
                : t[0] == pcode__SHORT    ? v[0] ? ( void *) (*s[0]) : ( void *) (s[0])
                : t[0] == pcode__INTEGER  ? v[0] ? ( void *) (*i[0]) : ( void *) (i[0])
                : t[0] == pcode__LONG     ? v[0] ? ( void *) (*l[0]) : ( void *) (l[0])
                : t[0] == pcode__SINGLE   ? v[0] ? ( void *) (*k[0]) : ( void *) (k[0])
                : t[0] == pcode__DOUBLE   ? v[0] ? ( void *) (*d[0]) : ( void *) (d[0])
                :                          (p[0])
                ,
                  t[1] == pcode__BOOLEAN  ? v[1] ? ( void *) (*b[1]) : ( void *) (b[1])
                : t[1] == pcode__BYTE     ? v[1] ? ( void *) (*y[1]) : ( void *) (y[1])
                : t[1] == pcode__SHORT    ? v[1] ? ( void *) (*s[1]) : ( void *) (s[1])
                : t[1] == pcode__INTEGER  ? v[1] ? ( void *) (*i[1]) : ( void *) (i[1])
                : t[1] == pcode__LONG     ? v[1] ? ( void *) (*l[1]) : ( void *) (l[1])
                : t[1] == pcode__SINGLE   ? v[1] ? ( void *) (*k[1]) : ( void *) (k[1])
                : t[1] == pcode__DOUBLE   ? v[1] ? ( void *) (*d[1]) : ( void *) (d[1])
                :                          (p[1])
                ,
                  t[2] == pcode__BOOLEAN  ? v[2] ? ( void *) (*b[2]) : ( void *) (b[2])
                : t[2] == pcode__BYTE     ? v[2] ? ( void *) (*y[2]) : ( void *) (y[2])
                : t[2] == pcode__SHORT    ? v[2] ? ( void *) (*s[2]) : ( void *) (s[2])
                : t[2] == pcode__INTEGER  ? v[2] ? ( void *) (*i[2]) : ( void *) (i[2])
                : t[2] == pcode__LONG     ? v[2] ? ( void *) (*l[2]) : ( void *) (l[2])
                : t[2] == pcode__SINGLE   ? v[2] ? ( void *) (*k[2]) : ( void *) (k[2])
                : t[2] == pcode__DOUBLE   ? v[2] ? ( void *) (*d[2]) : ( void *) (d[2])
                :                          (p[2])
                ,
                  t[3] == pcode__BOOLEAN  ? v[3] ? ( void *) (*b[3]) : ( void *) (b[3])
                : t[3] == pcode__BYTE     ? v[3] ? ( void *) (*y[3]) : ( void *) (y[3])
                : t[3] == pcode__SHORT    ? v[3] ? ( void *) (*s[3]) : ( void *) (s[3])
                : t[3] == pcode__INTEGER  ? v[3] ? ( void *) (*i[3]) : ( void *) (i[3])
                : t[3] == pcode__LONG     ? v[3] ? ( void *) (*l[3]) : ( void *) (l[3])
                : t[3] == pcode__SINGLE   ? v[3] ? ( void *) (*k[3]) : ( void *) (k[3])
                : t[3] == pcode__DOUBLE   ? v[3] ? ( void *) (*d[3]) : ( void *) (d[3])
                :                          (p[3])
                ,
                  t[4] == pcode__BOOLEAN  ? v[4] ? ( void *) (*b[4]) : ( void *) (b[4])
                : t[4] == pcode__BYTE     ? v[4] ? ( void *) (*y[4]) : ( void *) (y[4])
                : t[4] == pcode__SHORT    ? v[4] ? ( void *) (*s[4]) : ( void *) (s[4])
                : t[4] == pcode__INTEGER  ? v[4] ? ( void *) (*i[4]) : ( void *) (i[4])
                : t[4] == pcode__LONG     ? v[4] ? ( void *) (*l[4]) : ( void *) (l[4])
                : t[4] == pcode__SINGLE   ? v[4] ? ( void *) (*k[4]) : ( void *) (k[4])
                : t[4] == pcode__DOUBLE   ? v[4] ? ( void *) (*d[4]) : ( void *) (d[4])
                :                          (p[4])
                ,
                  t[5] == pcode__BOOLEAN  ? v[5] ? ( void *) (*b[5]) : ( void *) (b[5])
                : t[5] == pcode__BYTE     ? v[5] ? ( void *) (*y[5]) : ( void *) (y[5])
                : t[5] == pcode__SHORT    ? v[5] ? ( void *) (*s[5]) : ( void *) (s[5])
                : t[5] == pcode__INTEGER  ? v[5] ? ( void *) (*i[5]) : ( void *) (i[5])
                : t[5] == pcode__LONG     ? v[5] ? ( void *) (*l[5]) : ( void *) (l[5])
                : t[5] == pcode__SINGLE   ? v[5] ? ( void *) (*k[5]) : ( void *) (k[5])
                : t[5] == pcode__DOUBLE   ? v[5] ? ( void *) (*d[5]) : ( void *) (d[5])
                :                          (p[5])
                ,
                  t[6] == pcode__BOOLEAN  ? v[6] ? ( void *) (*b[6]) : ( void *) (b[6])
                : t[6] == pcode__BYTE     ? v[6] ? ( void *) (*y[6]) : ( void *) (y[6])
                : t[6] == pcode__SHORT    ? v[6] ? ( void *) (*s[6]) : ( void *) (s[6])
                : t[6] == pcode__INTEGER  ? v[6] ? ( void *) (*i[6]) : ( void *) (i[6])
                : t[6] == pcode__LONG     ? v[6] ? ( void *) (*l[6]) : ( void *) (l[6])
                : t[6] == pcode__SINGLE   ? v[6] ? ( void *) (*k[6]) : ( void *) (k[6])
                : t[6] == pcode__DOUBLE   ? v[6] ? ( void *) (*d[6]) : ( void *) (d[6])
                :                          (p[6])
                ,
                  t[7] == pcode__BOOLEAN  ? v[7] ? ( void *) (*b[7]) : ( void *) (b[7])
                : t[7] == pcode__BYTE     ? v[7] ? ( void *) (*y[7]) : ( void *) (y[7])
                : t[7] == pcode__SHORT    ? v[7] ? ( void *) (*s[7]) : ( void *) (s[7])
                : t[7] == pcode__INTEGER  ? v[7] ? ( void *) (*i[7]) : ( void *) (i[7])
                : t[7] == pcode__LONG     ? v[7] ? ( void *) (*l[7]) : ( void *) (l[7])
                : t[7] == pcode__SINGLE   ? v[7] ? ( void *) (*k[7]) : ( void *) (k[7])
                : t[7] == pcode__DOUBLE   ? v[7] ? ( void *) (*d[7]) : ( void *) (d[7])
                :                          (p[7])
                ,
                  t[8] == pcode__BOOLEAN  ? v[8] ? ( void *) (*b[8]) : ( void *) (b[8])
                : t[8] == pcode__BYTE     ? v[8] ? ( void *) (*y[8]) : ( void *) (y[8])
                : t[8] == pcode__SHORT    ? v[8] ? ( void *) (*s[8]) : ( void *) (s[8])
                : t[8] == pcode__INTEGER  ? v[8] ? ( void *) (*i[8]) : ( void *) (i[8])
                : t[8] == pcode__LONG     ? v[8] ? ( void *) (*l[8]) : ( void *) (l[8])
                : t[8] == pcode__SINGLE   ? v[8] ? ( void *) (*k[8]) : ( void *) (k[8])
                : t[8] == pcode__DOUBLE   ? v[8] ? ( void *) (*d[8]) : ( void *) (d[8])
                :                          (p[8])
              );
              else return runtimeError(utility::con(function, " function call failed. ", ll[lib]->errorString()));
              myStack->pushInteger(ri);
            }
            break;
          default:
            return runtimeError(utility::con(function, ": Too much arguments (max. 9 allowed) when calling declare function."));
            break;
         }
         break;
       case pcode__LONG:
        switch(count){
          case 0:
            {
              long_c0 c = (long_c0) ll[lib]->resolve( function );
              if (c) rl = c (
              );
              else return runtimeError(utility::con(function, " function call failed. ", ll[lib]->errorString()));
              myStack->pushLong(rl);
            }
            break;
          case 1:
            {
              long_c1 c = (long_c1) ll[lib]->resolve( function );
              if (c) rl = c (
                  t[0] == pcode__BOOLEAN  ? v[0] ? ( void *) (*b[0]) : ( void *) (b[0])
                : t[0] == pcode__BYTE     ? v[0] ? ( void *) (*y[0]) : ( void *) (y[0])
                : t[0] == pcode__SHORT    ? v[0] ? ( void *) (*s[0]) : ( void *) (s[0])
                : t[0] == pcode__INTEGER  ? v[0] ? ( void *) (*i[0]) : ( void *) (i[0])
                : t[0] == pcode__LONG     ? v[0] ? ( void *) (*l[0]) : ( void *) (l[0])
                : t[0] == pcode__SINGLE   ? v[0] ? ( void *) (*k[0]) : ( void *) (k[0])
                : t[0] == pcode__DOUBLE   ? v[0] ? ( void *) (*d[0]) : ( void *) (d[0])
                :                          (p[0])
              );
              else return runtimeError(utility::con(function, " function call failed. ", ll[lib]->errorString()));
              myStack->pushLong(rl);
            }
            break;
          case 2:
            {
              long_c2 c = (long_c2) ll[lib]->resolve( function );
              if (c) rl = c (
                  t[0] == pcode__BOOLEAN  ? v[0] ? ( void *) (*b[0]) : ( void *) (b[0])
                : t[0] == pcode__BYTE     ? v[0] ? ( void *) (*y[0]) : ( void *) (y[0])
                : t[0] == pcode__SHORT    ? v[0] ? ( void *) (*s[0]) : ( void *) (s[0])
                : t[0] == pcode__INTEGER  ? v[0] ? ( void *) (*i[0]) : ( void *) (i[0])
                : t[0] == pcode__LONG     ? v[0] ? ( void *) (*l[0]) : ( void *) (l[0])
                : t[0] == pcode__SINGLE   ? v[0] ? ( void *) (*k[0]) : ( void *) (k[0])
                : t[0] == pcode__DOUBLE   ? v[0] ? ( void *) (*d[0]) : ( void *) (d[0])
                :                          (p[0])
                ,
                  t[1] == pcode__BOOLEAN  ? v[1] ? ( void *) (*b[1]) : ( void *) (b[1])
                : t[1] == pcode__BYTE     ? v[1] ? ( void *) (*y[1]) : ( void *) (y[1])
                : t[1] == pcode__SHORT    ? v[1] ? ( void *) (*s[1]) : ( void *) (s[1])
                : t[1] == pcode__INTEGER  ? v[1] ? ( void *) (*i[1]) : ( void *) (i[1])
                : t[1] == pcode__LONG     ? v[1] ? ( void *) (*l[1]) : ( void *) (l[1])
                : t[1] == pcode__SINGLE   ? v[1] ? ( void *) (*k[1]) : ( void *) (k[1])
                : t[1] == pcode__DOUBLE   ? v[1] ? ( void *) (*d[1]) : ( void *) (d[1])
                :                          (p[1])
              );
              else return runtimeError(utility::con(function, " function call failed. ", ll[lib]->errorString()));
              myStack->pushLong(rl);
            }
            break;
          case 3:
            {
              long_c3 c = (long_c3) ll[lib]->resolve( function );
              if (c) rl = c (
                  t[0] == pcode__BOOLEAN  ? v[0] ? ( void *) (*b[0]) : ( void *) (b[0])
                : t[0] == pcode__BYTE     ? v[0] ? ( void *) (*y[0]) : ( void *) (y[0])
                : t[0] == pcode__SHORT    ? v[0] ? ( void *) (*s[0]) : ( void *) (s[0])
                : t[0] == pcode__INTEGER  ? v[0] ? ( void *) (*i[0]) : ( void *) (i[0])
                : t[0] == pcode__LONG     ? v[0] ? ( void *) (*l[0]) : ( void *) (l[0])
                : t[0] == pcode__SINGLE   ? v[0] ? ( void *) (*k[0]) : ( void *) (k[0])
                : t[0] == pcode__DOUBLE   ? v[0] ? ( void *) (*d[0]) : ( void *) (d[0])
                :                          (p[0])
                ,
                  t[1] == pcode__BOOLEAN  ? v[1] ? ( void *) (*b[1]) : ( void *) (b[1])
                : t[1] == pcode__BYTE     ? v[1] ? ( void *) (*y[1]) : ( void *) (y[1])
                : t[1] == pcode__SHORT    ? v[1] ? ( void *) (*s[1]) : ( void *) (s[1])
                : t[1] == pcode__INTEGER  ? v[1] ? ( void *) (*i[1]) : ( void *) (i[1])
                : t[1] == pcode__LONG     ? v[1] ? ( void *) (*l[1]) : ( void *) (l[1])
                : t[1] == pcode__SINGLE   ? v[1] ? ( void *) (*k[1]) : ( void *) (k[1])
                : t[1] == pcode__DOUBLE   ? v[1] ? ( void *) (*d[1]) : ( void *) (d[1])
                :                          (p[1])
                ,
                  t[2] == pcode__BOOLEAN  ? v[2] ? ( void *) (*b[2]) : ( void *) (b[2])
                : t[2] == pcode__BYTE     ? v[2] ? ( void *) (*y[2]) : ( void *) (y[2])
                : t[2] == pcode__SHORT    ? v[2] ? ( void *) (*s[2]) : ( void *) (s[2])
                : t[2] == pcode__INTEGER  ? v[2] ? ( void *) (*i[2]) : ( void *) (i[2])
                : t[2] == pcode__LONG     ? v[2] ? ( void *) (*l[2]) : ( void *) (l[2])
                : t[2] == pcode__SINGLE   ? v[2] ? ( void *) (*k[2]) : ( void *) (k[2])
                : t[2] == pcode__DOUBLE   ? v[2] ? ( void *) (*d[2]) : ( void *) (d[2])
                :                          (p[2])
              );
              else return runtimeError(utility::con(function, " function call failed. ", ll[lib]->errorString()));
              myStack->pushLong(rl);
            }
            break;
          case 4:
            {
              long_c4 c = (long_c4) ll[lib]->resolve( function );
              if (c) rl = c (
                  t[0] == pcode__BOOLEAN  ? v[0] ? ( void *) (*b[0]) : ( void *) (b[0])
                : t[0] == pcode__BYTE     ? v[0] ? ( void *) (*y[0]) : ( void *) (y[0])
                : t[0] == pcode__SHORT    ? v[0] ? ( void *) (*s[0]) : ( void *) (s[0])
                : t[0] == pcode__INTEGER  ? v[0] ? ( void *) (*i[0]) : ( void *) (i[0])
                : t[0] == pcode__LONG     ? v[0] ? ( void *) (*l[0]) : ( void *) (l[0])
                : t[0] == pcode__SINGLE   ? v[0] ? ( void *) (*k[0]) : ( void *) (k[0])
                : t[0] == pcode__DOUBLE   ? v[0] ? ( void *) (*d[0]) : ( void *) (d[0])
                :                          (p[0])
                ,
                  t[1] == pcode__BOOLEAN  ? v[1] ? ( void *) (*b[1]) : ( void *) (b[1])
                : t[1] == pcode__BYTE     ? v[1] ? ( void *) (*y[1]) : ( void *) (y[1])
                : t[1] == pcode__SHORT    ? v[1] ? ( void *) (*s[1]) : ( void *) (s[1])
                : t[1] == pcode__INTEGER  ? v[1] ? ( void *) (*i[1]) : ( void *) (i[1])
                : t[1] == pcode__LONG     ? v[1] ? ( void *) (*l[1]) : ( void *) (l[1])
                : t[1] == pcode__SINGLE   ? v[1] ? ( void *) (*k[1]) : ( void *) (k[1])
                : t[1] == pcode__DOUBLE   ? v[1] ? ( void *) (*d[1]) : ( void *) (d[1])
                :                          (p[1])
                ,
                  t[2] == pcode__BOOLEAN  ? v[2] ? ( void *) (*b[2]) : ( void *) (b[2])
                : t[2] == pcode__BYTE     ? v[2] ? ( void *) (*y[2]) : ( void *) (y[2])
                : t[2] == pcode__SHORT    ? v[2] ? ( void *) (*s[2]) : ( void *) (s[2])
                : t[2] == pcode__INTEGER  ? v[2] ? ( void *) (*i[2]) : ( void *) (i[2])
                : t[2] == pcode__LONG     ? v[2] ? ( void *) (*l[2]) : ( void *) (l[2])
                : t[2] == pcode__SINGLE   ? v[2] ? ( void *) (*k[2]) : ( void *) (k[2])
                : t[2] == pcode__DOUBLE   ? v[2] ? ( void *) (*d[2]) : ( void *) (d[2])
                :                          (p[2])
                ,
                  t[3] == pcode__BOOLEAN  ? v[3] ? ( void *) (*b[3]) : ( void *) (b[3])
                : t[3] == pcode__BYTE     ? v[3] ? ( void *) (*y[3]) : ( void *) (y[3])
                : t[3] == pcode__SHORT    ? v[3] ? ( void *) (*s[3]) : ( void *) (s[3])
                : t[3] == pcode__INTEGER  ? v[3] ? ( void *) (*i[3]) : ( void *) (i[3])
                : t[3] == pcode__LONG     ? v[3] ? ( void *) (*l[3]) : ( void *) (l[3])
                : t[3] == pcode__SINGLE   ? v[3] ? ( void *) (*k[3]) : ( void *) (k[3])
                : t[3] == pcode__DOUBLE   ? v[3] ? ( void *) (*d[3]) : ( void *) (d[3])
                :                          (p[3])
              );
              else return runtimeError(utility::con(function, " function call failed. ", ll[lib]->errorString()));
              myStack->pushLong(rl);
            }
            break;
          case 5:
            {
              long_c5 c = (long_c5) ll[lib]->resolve( function );
              if (c) rl = c (
                  t[0] == pcode__BOOLEAN  ? v[0] ? ( void *) (*b[0]) : ( void *) (b[0])
                : t[0] == pcode__BYTE     ? v[0] ? ( void *) (*y[0]) : ( void *) (y[0])
                : t[0] == pcode__SHORT    ? v[0] ? ( void *) (*s[0]) : ( void *) (s[0])
                : t[0] == pcode__INTEGER  ? v[0] ? ( void *) (*i[0]) : ( void *) (i[0])
                : t[0] == pcode__LONG     ? v[0] ? ( void *) (*l[0]) : ( void *) (l[0])
                : t[0] == pcode__SINGLE   ? v[0] ? ( void *) (*k[0]) : ( void *) (k[0])
                : t[0] == pcode__DOUBLE   ? v[0] ? ( void *) (*d[0]) : ( void *) (d[0])
                :                          (p[0])
                ,
                  t[1] == pcode__BOOLEAN  ? v[1] ? ( void *) (*b[1]) : ( void *) (b[1])
                : t[1] == pcode__BYTE     ? v[1] ? ( void *) (*y[1]) : ( void *) (y[1])
                : t[1] == pcode__SHORT    ? v[1] ? ( void *) (*s[1]) : ( void *) (s[1])
                : t[1] == pcode__INTEGER  ? v[1] ? ( void *) (*i[1]) : ( void *) (i[1])
                : t[1] == pcode__LONG     ? v[1] ? ( void *) (*l[1]) : ( void *) (l[1])
                : t[1] == pcode__SINGLE   ? v[1] ? ( void *) (*k[1]) : ( void *) (k[1])
                : t[1] == pcode__DOUBLE   ? v[1] ? ( void *) (*d[1]) : ( void *) (d[1])
                :                          (p[1])
                ,
                  t[2] == pcode__BOOLEAN  ? v[2] ? ( void *) (*b[2]) : ( void *) (b[2])
                : t[2] == pcode__BYTE     ? v[2] ? ( void *) (*y[2]) : ( void *) (y[2])
                : t[2] == pcode__SHORT    ? v[2] ? ( void *) (*s[2]) : ( void *) (s[2])
                : t[2] == pcode__INTEGER  ? v[2] ? ( void *) (*i[2]) : ( void *) (i[2])
                : t[2] == pcode__LONG     ? v[2] ? ( void *) (*l[2]) : ( void *) (l[2])
                : t[2] == pcode__SINGLE   ? v[2] ? ( void *) (*k[2]) : ( void *) (k[2])
                : t[2] == pcode__DOUBLE   ? v[2] ? ( void *) (*d[2]) : ( void *) (d[2])
                :                          (p[2])
                ,
                  t[3] == pcode__BOOLEAN  ? v[3] ? ( void *) (*b[3]) : ( void *) (b[3])
                : t[3] == pcode__BYTE     ? v[3] ? ( void *) (*y[3]) : ( void *) (y[3])
                : t[3] == pcode__SHORT    ? v[3] ? ( void *) (*s[3]) : ( void *) (s[3])
                : t[3] == pcode__INTEGER  ? v[3] ? ( void *) (*i[3]) : ( void *) (i[3])
                : t[3] == pcode__LONG     ? v[3] ? ( void *) (*l[3]) : ( void *) (l[3])
                : t[3] == pcode__SINGLE   ? v[3] ? ( void *) (*k[3]) : ( void *) (k[3])
                : t[3] == pcode__DOUBLE   ? v[3] ? ( void *) (*d[3]) : ( void *) (d[3])
                :                          (p[3])
                ,
                  t[4] == pcode__BOOLEAN  ? v[4] ? ( void *) (*b[4]) : ( void *) (b[4])
                : t[4] == pcode__BYTE     ? v[4] ? ( void *) (*y[4]) : ( void *) (y[4])
                : t[4] == pcode__SHORT    ? v[4] ? ( void *) (*s[4]) : ( void *) (s[4])
                : t[4] == pcode__INTEGER  ? v[4] ? ( void *) (*i[4]) : ( void *) (i[4])
                : t[4] == pcode__LONG     ? v[4] ? ( void *) (*l[4]) : ( void *) (l[4])
                : t[4] == pcode__SINGLE   ? v[4] ? ( void *) (*k[4]) : ( void *) (k[4])
                : t[4] == pcode__DOUBLE   ? v[4] ? ( void *) (*d[4]) : ( void *) (d[4])
                :                          (p[4])
              );
              else return runtimeError(utility::con(function, " function call failed. ", ll[lib]->errorString()));
              myStack->pushLong(rl);
            }
            break;
          case 6:
            {
              long_c6 c = (long_c6) ll[lib]->resolve( function );
              if (c) rl = c (
                  t[0] == pcode__BOOLEAN  ? v[0] ? ( void *) (*b[0]) : ( void *) (b[0])
                : t[0] == pcode__BYTE     ? v[0] ? ( void *) (*y[0]) : ( void *) (y[0])
                : t[0] == pcode__SHORT    ? v[0] ? ( void *) (*s[0]) : ( void *) (s[0])
                : t[0] == pcode__INTEGER  ? v[0] ? ( void *) (*i[0]) : ( void *) (i[0])
                : t[0] == pcode__LONG     ? v[0] ? ( void *) (*l[0]) : ( void *) (l[0])
                : t[0] == pcode__SINGLE   ? v[0] ? ( void *) (*k[0]) : ( void *) (k[0])
                : t[0] == pcode__DOUBLE   ? v[0] ? ( void *) (*d[0]) : ( void *) (d[0])
                :                          (p[0])
                ,
                  t[1] == pcode__BOOLEAN  ? v[1] ? ( void *) (*b[1]) : ( void *) (b[1])
                : t[1] == pcode__BYTE     ? v[1] ? ( void *) (*y[1]) : ( void *) (y[1])
                : t[1] == pcode__SHORT    ? v[1] ? ( void *) (*s[1]) : ( void *) (s[1])
                : t[1] == pcode__INTEGER  ? v[1] ? ( void *) (*i[1]) : ( void *) (i[1])
                : t[1] == pcode__LONG     ? v[1] ? ( void *) (*l[1]) : ( void *) (l[1])
                : t[1] == pcode__SINGLE   ? v[1] ? ( void *) (*k[1]) : ( void *) (k[1])
                : t[1] == pcode__DOUBLE   ? v[1] ? ( void *) (*d[1]) : ( void *) (d[1])
                :                          (p[1])
                ,
                  t[2] == pcode__BOOLEAN  ? v[2] ? ( void *) (*b[2]) : ( void *) (b[2])
                : t[2] == pcode__BYTE     ? v[2] ? ( void *) (*y[2]) : ( void *) (y[2])
                : t[2] == pcode__SHORT    ? v[2] ? ( void *) (*s[2]) : ( void *) (s[2])
                : t[2] == pcode__INTEGER  ? v[2] ? ( void *) (*i[2]) : ( void *) (i[2])
                : t[2] == pcode__LONG     ? v[2] ? ( void *) (*l[2]) : ( void *) (l[2])
                : t[2] == pcode__SINGLE   ? v[2] ? ( void *) (*k[2]) : ( void *) (k[2])
                : t[2] == pcode__DOUBLE   ? v[2] ? ( void *) (*d[2]) : ( void *) (d[2])
                :                          (p[2])
                ,
                  t[3] == pcode__BOOLEAN  ? v[3] ? ( void *) (*b[3]) : ( void *) (b[3])
                : t[3] == pcode__BYTE     ? v[3] ? ( void *) (*y[3]) : ( void *) (y[3])
                : t[3] == pcode__SHORT    ? v[3] ? ( void *) (*s[3]) : ( void *) (s[3])
                : t[3] == pcode__INTEGER  ? v[3] ? ( void *) (*i[3]) : ( void *) (i[3])
                : t[3] == pcode__LONG     ? v[3] ? ( void *) (*l[3]) : ( void *) (l[3])
                : t[3] == pcode__SINGLE   ? v[3] ? ( void *) (*k[3]) : ( void *) (k[3])
                : t[3] == pcode__DOUBLE   ? v[3] ? ( void *) (*d[3]) : ( void *) (d[3])
                :                          (p[3])
                ,
                  t[4] == pcode__BOOLEAN  ? v[4] ? ( void *) (*b[4]) : ( void *) (b[4])
                : t[4] == pcode__BYTE     ? v[4] ? ( void *) (*y[4]) : ( void *) (y[4])
                : t[4] == pcode__SHORT    ? v[4] ? ( void *) (*s[4]) : ( void *) (s[4])
                : t[4] == pcode__INTEGER  ? v[4] ? ( void *) (*i[4]) : ( void *) (i[4])
                : t[4] == pcode__LONG     ? v[4] ? ( void *) (*l[4]) : ( void *) (l[4])
                : t[4] == pcode__SINGLE   ? v[4] ? ( void *) (*k[4]) : ( void *) (k[4])
                : t[4] == pcode__DOUBLE   ? v[4] ? ( void *) (*d[4]) : ( void *) (d[4])
                :                          (p[4])
                ,
                  t[5] == pcode__BOOLEAN  ? v[5] ? ( void *) (*b[5]) : ( void *) (b[5])
                : t[5] == pcode__BYTE     ? v[5] ? ( void *) (*y[5]) : ( void *) (y[5])
                : t[5] == pcode__SHORT    ? v[5] ? ( void *) (*s[5]) : ( void *) (s[5])
                : t[5] == pcode__INTEGER  ? v[5] ? ( void *) (*i[5]) : ( void *) (i[5])
                : t[5] == pcode__LONG     ? v[5] ? ( void *) (*l[5]) : ( void *) (l[5])
                : t[5] == pcode__SINGLE   ? v[5] ? ( void *) (*k[5]) : ( void *) (k[5])
                : t[5] == pcode__DOUBLE   ? v[5] ? ( void *) (*d[5]) : ( void *) (d[5])
                :                          (p[5])
              );
              else return runtimeError(utility::con(function, " function call failed. ", ll[lib]->errorString()));
              myStack->pushLong(rl);
            }
            break;
          case 7:
            {
              long_c7 c = (long_c7) ll[lib]->resolve( function );
              if (c) rl = c (
                  t[0] == pcode__BOOLEAN  ? v[0] ? ( void *) (*b[0]) : ( void *) (b[0])
                : t[0] == pcode__BYTE     ? v[0] ? ( void *) (*y[0]) : ( void *) (y[0])
                : t[0] == pcode__SHORT    ? v[0] ? ( void *) (*s[0]) : ( void *) (s[0])
                : t[0] == pcode__INTEGER  ? v[0] ? ( void *) (*i[0]) : ( void *) (i[0])
                : t[0] == pcode__LONG     ? v[0] ? ( void *) (*l[0]) : ( void *) (l[0])
                : t[0] == pcode__SINGLE   ? v[0] ? ( void *) (*k[0]) : ( void *) (k[0])
                : t[0] == pcode__DOUBLE   ? v[0] ? ( void *) (*d[0]) : ( void *) (d[0])
                :                          (p[0])
                ,
                  t[1] == pcode__BOOLEAN  ? v[1] ? ( void *) (*b[1]) : ( void *) (b[1])
                : t[1] == pcode__BYTE     ? v[1] ? ( void *) (*y[1]) : ( void *) (y[1])
                : t[1] == pcode__SHORT    ? v[1] ? ( void *) (*s[1]) : ( void *) (s[1])
                : t[1] == pcode__INTEGER  ? v[1] ? ( void *) (*i[1]) : ( void *) (i[1])
                : t[1] == pcode__LONG     ? v[1] ? ( void *) (*l[1]) : ( void *) (l[1])
                : t[1] == pcode__SINGLE   ? v[1] ? ( void *) (*k[1]) : ( void *) (k[1])
                : t[1] == pcode__DOUBLE   ? v[1] ? ( void *) (*d[1]) : ( void *) (d[1])
                :                          (p[1])
                ,
                  t[2] == pcode__BOOLEAN  ? v[2] ? ( void *) (*b[2]) : ( void *) (b[2])
                : t[2] == pcode__BYTE     ? v[2] ? ( void *) (*y[2]) : ( void *) (y[2])
                : t[2] == pcode__SHORT    ? v[2] ? ( void *) (*s[2]) : ( void *) (s[2])
                : t[2] == pcode__INTEGER  ? v[2] ? ( void *) (*i[2]) : ( void *) (i[2])
                : t[2] == pcode__LONG     ? v[2] ? ( void *) (*l[2]) : ( void *) (l[2])
                : t[2] == pcode__SINGLE   ? v[2] ? ( void *) (*k[2]) : ( void *) (k[2])
                : t[2] == pcode__DOUBLE   ? v[2] ? ( void *) (*d[2]) : ( void *) (d[2])
                :                          (p[2])
                ,
                  t[3] == pcode__BOOLEAN  ? v[3] ? ( void *) (*b[3]) : ( void *) (b[3])
                : t[3] == pcode__BYTE     ? v[3] ? ( void *) (*y[3]) : ( void *) (y[3])
                : t[3] == pcode__SHORT    ? v[3] ? ( void *) (*s[3]) : ( void *) (s[3])
                : t[3] == pcode__INTEGER  ? v[3] ? ( void *) (*i[3]) : ( void *) (i[3])
                : t[3] == pcode__LONG     ? v[3] ? ( void *) (*l[3]) : ( void *) (l[3])
                : t[3] == pcode__SINGLE   ? v[3] ? ( void *) (*k[3]) : ( void *) (k[3])
                : t[3] == pcode__DOUBLE   ? v[3] ? ( void *) (*d[3]) : ( void *) (d[3])
                :                          (p[3])
                ,
                  t[4] == pcode__BOOLEAN  ? v[4] ? ( void *) (*b[4]) : ( void *) (b[4])
                : t[4] == pcode__BYTE     ? v[4] ? ( void *) (*y[4]) : ( void *) (y[4])
                : t[4] == pcode__SHORT    ? v[4] ? ( void *) (*s[4]) : ( void *) (s[4])
                : t[4] == pcode__INTEGER  ? v[4] ? ( void *) (*i[4]) : ( void *) (i[4])
                : t[4] == pcode__LONG     ? v[4] ? ( void *) (*l[4]) : ( void *) (l[4])
                : t[4] == pcode__SINGLE   ? v[4] ? ( void *) (*k[4]) : ( void *) (k[4])
                : t[4] == pcode__DOUBLE   ? v[4] ? ( void *) (*d[4]) : ( void *) (d[4])
                :                          (p[4])
                ,
                  t[5] == pcode__BOOLEAN  ? v[5] ? ( void *) (*b[5]) : ( void *) (b[5])
                : t[5] == pcode__BYTE     ? v[5] ? ( void *) (*y[5]) : ( void *) (y[5])
                : t[5] == pcode__SHORT    ? v[5] ? ( void *) (*s[5]) : ( void *) (s[5])
                : t[5] == pcode__INTEGER  ? v[5] ? ( void *) (*i[5]) : ( void *) (i[5])
                : t[5] == pcode__LONG     ? v[5] ? ( void *) (*l[5]) : ( void *) (l[5])
                : t[5] == pcode__SINGLE   ? v[5] ? ( void *) (*k[5]) : ( void *) (k[5])
                : t[5] == pcode__DOUBLE   ? v[5] ? ( void *) (*d[5]) : ( void *) (d[5])
                :                          (p[5])
                ,
                  t[6] == pcode__BOOLEAN  ? v[6] ? ( void *) (*b[6]) : ( void *) (b[6])
                : t[6] == pcode__BYTE     ? v[6] ? ( void *) (*y[6]) : ( void *) (y[6])
                : t[6] == pcode__SHORT    ? v[6] ? ( void *) (*s[6]) : ( void *) (s[6])
                : t[6] == pcode__INTEGER  ? v[6] ? ( void *) (*i[6]) : ( void *) (i[6])
                : t[6] == pcode__LONG     ? v[6] ? ( void *) (*l[6]) : ( void *) (l[6])
                : t[6] == pcode__SINGLE   ? v[6] ? ( void *) (*k[6]) : ( void *) (k[6])
                : t[6] == pcode__DOUBLE   ? v[6] ? ( void *) (*d[6]) : ( void *) (d[6])
                :                          (p[6])
              );
              else return runtimeError(utility::con(function, " function call failed. ", ll[lib]->errorString()));
              myStack->pushLong(rl);
            }
            break;
          case 8:
            {
              long_c8 c = (long_c8) ll[lib]->resolve( function );
              if (c) rl = c (
                  t[0] == pcode__BOOLEAN  ? v[0] ? ( void *) (*b[0]) : ( void *) (b[0])
                : t[0] == pcode__BYTE     ? v[0] ? ( void *) (*y[0]) : ( void *) (y[0])
                : t[0] == pcode__SHORT    ? v[0] ? ( void *) (*s[0]) : ( void *) (s[0])
                : t[0] == pcode__INTEGER  ? v[0] ? ( void *) (*i[0]) : ( void *) (i[0])
                : t[0] == pcode__LONG     ? v[0] ? ( void *) (*l[0]) : ( void *) (l[0])
                : t[0] == pcode__SINGLE   ? v[0] ? ( void *) (*k[0]) : ( void *) (k[0])
                : t[0] == pcode__DOUBLE   ? v[0] ? ( void *) (*d[0]) : ( void *) (d[0])
                :                          (p[0])
                ,
                  t[1] == pcode__BOOLEAN  ? v[1] ? ( void *) (*b[1]) : ( void *) (b[1])
                : t[1] == pcode__BYTE     ? v[1] ? ( void *) (*y[1]) : ( void *) (y[1])
                : t[1] == pcode__SHORT    ? v[1] ? ( void *) (*s[1]) : ( void *) (s[1])
                : t[1] == pcode__INTEGER  ? v[1] ? ( void *) (*i[1]) : ( void *) (i[1])
                : t[1] == pcode__LONG     ? v[1] ? ( void *) (*l[1]) : ( void *) (l[1])
                : t[1] == pcode__SINGLE   ? v[1] ? ( void *) (*k[1]) : ( void *) (k[1])
                : t[1] == pcode__DOUBLE   ? v[1] ? ( void *) (*d[1]) : ( void *) (d[1])
                :                          (p[1])
                ,
                  t[2] == pcode__BOOLEAN  ? v[2] ? ( void *) (*b[2]) : ( void *) (b[2])
                : t[2] == pcode__BYTE     ? v[2] ? ( void *) (*y[2]) : ( void *) (y[2])
                : t[2] == pcode__SHORT    ? v[2] ? ( void *) (*s[2]) : ( void *) (s[2])
                : t[2] == pcode__INTEGER  ? v[2] ? ( void *) (*i[2]) : ( void *) (i[2])
                : t[2] == pcode__LONG     ? v[2] ? ( void *) (*l[2]) : ( void *) (l[2])
                : t[2] == pcode__SINGLE   ? v[2] ? ( void *) (*k[2]) : ( void *) (k[2])
                : t[2] == pcode__DOUBLE   ? v[2] ? ( void *) (*d[2]) : ( void *) (d[2])
                :                          (p[2])
                ,
                  t[3] == pcode__BOOLEAN  ? v[3] ? ( void *) (*b[3]) : ( void *) (b[3])
                : t[3] == pcode__BYTE     ? v[3] ? ( void *) (*y[3]) : ( void *) (y[3])
                : t[3] == pcode__SHORT    ? v[3] ? ( void *) (*s[3]) : ( void *) (s[3])
                : t[3] == pcode__INTEGER  ? v[3] ? ( void *) (*i[3]) : ( void *) (i[3])
                : t[3] == pcode__LONG     ? v[3] ? ( void *) (*l[3]) : ( void *) (l[3])
                : t[3] == pcode__SINGLE   ? v[3] ? ( void *) (*k[3]) : ( void *) (k[3])
                : t[3] == pcode__DOUBLE   ? v[3] ? ( void *) (*d[3]) : ( void *) (d[3])
                :                          (p[3])
                ,
                  t[4] == pcode__BOOLEAN  ? v[4] ? ( void *) (*b[4]) : ( void *) (b[4])
                : t[4] == pcode__BYTE     ? v[4] ? ( void *) (*y[4]) : ( void *) (y[4])
                : t[4] == pcode__SHORT    ? v[4] ? ( void *) (*s[4]) : ( void *) (s[4])
                : t[4] == pcode__INTEGER  ? v[4] ? ( void *) (*i[4]) : ( void *) (i[4])
                : t[4] == pcode__LONG     ? v[4] ? ( void *) (*l[4]) : ( void *) (l[4])
                : t[4] == pcode__SINGLE   ? v[4] ? ( void *) (*k[4]) : ( void *) (k[4])
                : t[4] == pcode__DOUBLE   ? v[4] ? ( void *) (*d[4]) : ( void *) (d[4])
                :                          (p[4])
                ,
                  t[5] == pcode__BOOLEAN  ? v[5] ? ( void *) (*b[5]) : ( void *) (b[5])
                : t[5] == pcode__BYTE     ? v[5] ? ( void *) (*y[5]) : ( void *) (y[5])
                : t[5] == pcode__SHORT    ? v[5] ? ( void *) (*s[5]) : ( void *) (s[5])
                : t[5] == pcode__INTEGER  ? v[5] ? ( void *) (*i[5]) : ( void *) (i[5])
                : t[5] == pcode__LONG     ? v[5] ? ( void *) (*l[5]) : ( void *) (l[5])
                : t[5] == pcode__SINGLE   ? v[5] ? ( void *) (*k[5]) : ( void *) (k[5])
                : t[5] == pcode__DOUBLE   ? v[5] ? ( void *) (*d[5]) : ( void *) (d[5])
                :                          (p[5])
                ,
                  t[6] == pcode__BOOLEAN  ? v[6] ? ( void *) (*b[6]) : ( void *) (b[6])
                : t[6] == pcode__BYTE     ? v[6] ? ( void *) (*y[6]) : ( void *) (y[6])
                : t[6] == pcode__SHORT    ? v[6] ? ( void *) (*s[6]) : ( void *) (s[6])
                : t[6] == pcode__INTEGER  ? v[6] ? ( void *) (*i[6]) : ( void *) (i[6])
                : t[6] == pcode__LONG     ? v[6] ? ( void *) (*l[6]) : ( void *) (l[6])
                : t[6] == pcode__SINGLE   ? v[6] ? ( void *) (*k[6]) : ( void *) (k[6])
                : t[6] == pcode__DOUBLE   ? v[6] ? ( void *) (*d[6]) : ( void *) (d[6])
                :                          (p[6])
                ,
                  t[7] == pcode__BOOLEAN  ? v[7] ? ( void *) (*b[7]) : ( void *) (b[7])
                : t[7] == pcode__BYTE     ? v[7] ? ( void *) (*y[7]) : ( void *) (y[7])
                : t[7] == pcode__SHORT    ? v[7] ? ( void *) (*s[7]) : ( void *) (s[7])
                : t[7] == pcode__INTEGER  ? v[7] ? ( void *) (*i[7]) : ( void *) (i[7])
                : t[7] == pcode__LONG     ? v[7] ? ( void *) (*l[7]) : ( void *) (l[7])
                : t[7] == pcode__SINGLE   ? v[7] ? ( void *) (*k[7]) : ( void *) (k[7])
                : t[7] == pcode__DOUBLE   ? v[7] ? ( void *) (*d[7]) : ( void *) (d[7])
                :                          (p[7])
              );
              else return runtimeError(utility::con(function, " function call failed. ", ll[lib]->errorString()));
              myStack->pushLong(rl);
            }
            break;
          case 9:
            {
              long_c9 c = (long_c9) ll[lib]->resolve( function );
              if (c) rl = c (
                  t[0] == pcode__BOOLEAN  ? v[0] ? ( void *) (*b[0]) : ( void *) (b[0])
                : t[0] == pcode__BYTE     ? v[0] ? ( void *) (*y[0]) : ( void *) (y[0])
                : t[0] == pcode__SHORT    ? v[0] ? ( void *) (*s[0]) : ( void *) (s[0])
                : t[0] == pcode__INTEGER  ? v[0] ? ( void *) (*i[0]) : ( void *) (i[0])
                : t[0] == pcode__LONG     ? v[0] ? ( void *) (*l[0]) : ( void *) (l[0])
                : t[0] == pcode__SINGLE   ? v[0] ? ( void *) (*k[0]) : ( void *) (k[0])
                : t[0] == pcode__DOUBLE   ? v[0] ? ( void *) (*d[0]) : ( void *) (d[0])
                :                          (p[0])
                ,
                  t[1] == pcode__BOOLEAN  ? v[1] ? ( void *) (*b[1]) : ( void *) (b[1])
                : t[1] == pcode__BYTE     ? v[1] ? ( void *) (*y[1]) : ( void *) (y[1])
                : t[1] == pcode__SHORT    ? v[1] ? ( void *) (*s[1]) : ( void *) (s[1])
                : t[1] == pcode__INTEGER  ? v[1] ? ( void *) (*i[1]) : ( void *) (i[1])
                : t[1] == pcode__LONG     ? v[1] ? ( void *) (*l[1]) : ( void *) (l[1])
                : t[1] == pcode__SINGLE   ? v[1] ? ( void *) (*k[1]) : ( void *) (k[1])
                : t[1] == pcode__DOUBLE   ? v[1] ? ( void *) (*d[1]) : ( void *) (d[1])
                :                          (p[1])
                ,
                  t[2] == pcode__BOOLEAN  ? v[2] ? ( void *) (*b[2]) : ( void *) (b[2])
                : t[2] == pcode__BYTE     ? v[2] ? ( void *) (*y[2]) : ( void *) (y[2])
                : t[2] == pcode__SHORT    ? v[2] ? ( void *) (*s[2]) : ( void *) (s[2])
                : t[2] == pcode__INTEGER  ? v[2] ? ( void *) (*i[2]) : ( void *) (i[2])
                : t[2] == pcode__LONG     ? v[2] ? ( void *) (*l[2]) : ( void *) (l[2])
                : t[2] == pcode__SINGLE   ? v[2] ? ( void *) (*k[2]) : ( void *) (k[2])
                : t[2] == pcode__DOUBLE   ? v[2] ? ( void *) (*d[2]) : ( void *) (d[2])
                :                          (p[2])
                ,
                  t[3] == pcode__BOOLEAN  ? v[3] ? ( void *) (*b[3]) : ( void *) (b[3])
                : t[3] == pcode__BYTE     ? v[3] ? ( void *) (*y[3]) : ( void *) (y[3])
                : t[3] == pcode__SHORT    ? v[3] ? ( void *) (*s[3]) : ( void *) (s[3])
                : t[3] == pcode__INTEGER  ? v[3] ? ( void *) (*i[3]) : ( void *) (i[3])
                : t[3] == pcode__LONG     ? v[3] ? ( void *) (*l[3]) : ( void *) (l[3])
                : t[3] == pcode__SINGLE   ? v[3] ? ( void *) (*k[3]) : ( void *) (k[3])
                : t[3] == pcode__DOUBLE   ? v[3] ? ( void *) (*d[3]) : ( void *) (d[3])
                :                          (p[3])
                ,
                  t[4] == pcode__BOOLEAN  ? v[4] ? ( void *) (*b[4]) : ( void *) (b[4])
                : t[4] == pcode__BYTE     ? v[4] ? ( void *) (*y[4]) : ( void *) (y[4])
                : t[4] == pcode__SHORT    ? v[4] ? ( void *) (*s[4]) : ( void *) (s[4])
                : t[4] == pcode__INTEGER  ? v[4] ? ( void *) (*i[4]) : ( void *) (i[4])
                : t[4] == pcode__LONG     ? v[4] ? ( void *) (*l[4]) : ( void *) (l[4])
                : t[4] == pcode__SINGLE   ? v[4] ? ( void *) (*k[4]) : ( void *) (k[4])
                : t[4] == pcode__DOUBLE   ? v[4] ? ( void *) (*d[4]) : ( void *) (d[4])
                :                          (p[4])
                ,
                  t[5] == pcode__BOOLEAN  ? v[5] ? ( void *) (*b[5]) : ( void *) (b[5])
                : t[5] == pcode__BYTE     ? v[5] ? ( void *) (*y[5]) : ( void *) (y[5])
                : t[5] == pcode__SHORT    ? v[5] ? ( void *) (*s[5]) : ( void *) (s[5])
                : t[5] == pcode__INTEGER  ? v[5] ? ( void *) (*i[5]) : ( void *) (i[5])
                : t[5] == pcode__LONG     ? v[5] ? ( void *) (*l[5]) : ( void *) (l[5])
                : t[5] == pcode__SINGLE   ? v[5] ? ( void *) (*k[5]) : ( void *) (k[5])
                : t[5] == pcode__DOUBLE   ? v[5] ? ( void *) (*d[5]) : ( void *) (d[5])
                :                          (p[5])
                ,
                  t[6] == pcode__BOOLEAN  ? v[6] ? ( void *) (*b[6]) : ( void *) (b[6])
                : t[6] == pcode__BYTE     ? v[6] ? ( void *) (*y[6]) : ( void *) (y[6])
                : t[6] == pcode__SHORT    ? v[6] ? ( void *) (*s[6]) : ( void *) (s[6])
                : t[6] == pcode__INTEGER  ? v[6] ? ( void *) (*i[6]) : ( void *) (i[6])
                : t[6] == pcode__LONG     ? v[6] ? ( void *) (*l[6]) : ( void *) (l[6])
                : t[6] == pcode__SINGLE   ? v[6] ? ( void *) (*k[6]) : ( void *) (k[6])
                : t[6] == pcode__DOUBLE   ? v[6] ? ( void *) (*d[6]) : ( void *) (d[6])
                :                          (p[6])
                ,
                  t[7] == pcode__BOOLEAN  ? v[7] ? ( void *) (*b[7]) : ( void *) (b[7])
                : t[7] == pcode__BYTE     ? v[7] ? ( void *) (*y[7]) : ( void *) (y[7])
                : t[7] == pcode__SHORT    ? v[7] ? ( void *) (*s[7]) : ( void *) (s[7])
                : t[7] == pcode__INTEGER  ? v[7] ? ( void *) (*i[7]) : ( void *) (i[7])
                : t[7] == pcode__LONG     ? v[7] ? ( void *) (*l[7]) : ( void *) (l[7])
                : t[7] == pcode__SINGLE   ? v[7] ? ( void *) (*k[7]) : ( void *) (k[7])
                : t[7] == pcode__DOUBLE   ? v[7] ? ( void *) (*d[7]) : ( void *) (d[7])
                :                          (p[7])
                ,
                  t[8] == pcode__BOOLEAN  ? v[8] ? ( void *) (*b[8]) : ( void *) (b[8])
                : t[8] == pcode__BYTE     ? v[8] ? ( void *) (*y[8]) : ( void *) (y[8])
                : t[8] == pcode__SHORT    ? v[8] ? ( void *) (*s[8]) : ( void *) (s[8])
                : t[8] == pcode__INTEGER  ? v[8] ? ( void *) (*i[8]) : ( void *) (i[8])
                : t[8] == pcode__LONG     ? v[8] ? ( void *) (*l[8]) : ( void *) (l[8])
                : t[8] == pcode__SINGLE   ? v[8] ? ( void *) (*k[8]) : ( void *) (k[8])
                : t[8] == pcode__DOUBLE   ? v[8] ? ( void *) (*d[8]) : ( void *) (d[8])
                :                          (p[8])
              );
              else return runtimeError(utility::con(function, " function call failed. ", ll[lib]->errorString()));
              myStack->pushLong(rl);
            }
            break;
          default:
            return runtimeError(utility::con(function, ": Too much arguments (max. 9 allowed) when calling declare function."));
            break;
         }
        break;

       case pcode__SINGLE:
        switch(count){
          case 0:
            {
              single_c0 c = (single_c0) ll[lib]->resolve( function );
              if (c) rk = c (
              );
              else return runtimeError(utility::con(function, " function call failed. ", ll[lib]->errorString()));
              myStack->pushSingle(rk);
            }
            break;
          case 1:
            {
              single_c1 c = (single_c1) ll[lib]->resolve( function );
              if (c) rk = c (
                  t[0] == pcode__BOOLEAN  ? v[0] ? ( void *) (*b[0]) : ( void *) (b[0])
                : t[0] == pcode__BYTE     ? v[0] ? ( void *) (*y[0]) : ( void *) (y[0])
                : t[0] == pcode__SHORT    ? v[0] ? ( void *) (*s[0]) : ( void *) (s[0])
                : t[0] == pcode__INTEGER  ? v[0] ? ( void *) (*i[0]) : ( void *) (i[0])
                : t[0] == pcode__LONG     ? v[0] ? ( void *) (*l[0]) : ( void *) (l[0])
                : t[0] == pcode__SINGLE   ? v[0] ? ( void *) (*k[0]) : ( void *) (k[0])
                : t[0] == pcode__DOUBLE   ? v[0] ? ( void *) (*d[0]) : ( void *) (d[0])
                :                          (p[0])
              );
              else return runtimeError(utility::con(function, " function call failed. ", ll[lib]->errorString()));
              myStack->pushSingle(rk);
            }
            break;
          case 2:
            {
              single_c2 c = (single_c2) ll[lib]->resolve( function );
              if (c) rk = c (
                  t[0] == pcode__BOOLEAN  ? v[0] ? ( void *) (*b[0]) : ( void *) (b[0])
                : t[0] == pcode__BYTE     ? v[0] ? ( void *) (*y[0]) : ( void *) (y[0])
                : t[0] == pcode__SHORT    ? v[0] ? ( void *) (*s[0]) : ( void *) (s[0])
                : t[0] == pcode__INTEGER  ? v[0] ? ( void *) (*i[0]) : ( void *) (i[0])
                : t[0] == pcode__LONG     ? v[0] ? ( void *) (*l[0]) : ( void *) (l[0])
                : t[0] == pcode__SINGLE   ? v[0] ? ( void *) (*k[0]) : ( void *) (k[0])
                : t[0] == pcode__DOUBLE   ? v[0] ? ( void *) (*d[0]) : ( void *) (d[0])
                :                          (p[0])
                ,
                  t[1] == pcode__BOOLEAN  ? v[1] ? ( void *) (*b[1]) : ( void *) (b[1])
                : t[1] == pcode__BYTE     ? v[1] ? ( void *) (*y[1]) : ( void *) (y[1])
                : t[1] == pcode__SHORT    ? v[1] ? ( void *) (*s[1]) : ( void *) (s[1])
                : t[1] == pcode__INTEGER  ? v[1] ? ( void *) (*i[1]) : ( void *) (i[1])
                : t[1] == pcode__LONG     ? v[1] ? ( void *) (*l[1]) : ( void *) (l[1])
                : t[1] == pcode__SINGLE   ? v[1] ? ( void *) (*k[1]) : ( void *) (k[1])
                : t[1] == pcode__DOUBLE   ? v[1] ? ( void *) (*d[1]) : ( void *) (d[1])
                :                          (p[1])
              );
              else return runtimeError(utility::con(function, " function call failed. ", ll[lib]->errorString()));
              myStack->pushSingle(rk);
            }
            break;
          case 3:
            {
              single_c3 c = (single_c3) ll[lib]->resolve( function );
              if (c) rk = c (
                  t[0] == pcode__BOOLEAN  ? v[0] ? ( void *) (*b[0]) : ( void *) (b[0])
                : t[0] == pcode__BYTE     ? v[0] ? ( void *) (*y[0]) : ( void *) (y[0])
                : t[0] == pcode__SHORT    ? v[0] ? ( void *) (*s[0]) : ( void *) (s[0])
                : t[0] == pcode__INTEGER  ? v[0] ? ( void *) (*i[0]) : ( void *) (i[0])
                : t[0] == pcode__LONG     ? v[0] ? ( void *) (*l[0]) : ( void *) (l[0])
                : t[0] == pcode__SINGLE   ? v[0] ? ( void *) (*k[0]) : ( void *) (k[0])
                : t[0] == pcode__DOUBLE   ? v[0] ? ( void *) (*d[0]) : ( void *) (d[0])
                :                          (p[0])
                ,
                  t[1] == pcode__BOOLEAN  ? v[1] ? ( void *) (*b[1]) : ( void *) (b[1])
                : t[1] == pcode__BYTE     ? v[1] ? ( void *) (*y[1]) : ( void *) (y[1])
                : t[1] == pcode__SHORT    ? v[1] ? ( void *) (*s[1]) : ( void *) (s[1])
                : t[1] == pcode__INTEGER  ? v[1] ? ( void *) (*i[1]) : ( void *) (i[1])
                : t[1] == pcode__LONG     ? v[1] ? ( void *) (*l[1]) : ( void *) (l[1])
                : t[1] == pcode__SINGLE   ? v[1] ? ( void *) (*k[1]) : ( void *) (k[1])
                : t[1] == pcode__DOUBLE   ? v[1] ? ( void *) (*d[1]) : ( void *) (d[1])
                :                          (p[1])
                ,
                  t[2] == pcode__BOOLEAN  ? v[2] ? ( void *) (*b[2]) : ( void *) (b[2])
                : t[2] == pcode__BYTE     ? v[2] ? ( void *) (*y[2]) : ( void *) (y[2])
                : t[2] == pcode__SHORT    ? v[2] ? ( void *) (*s[2]) : ( void *) (s[2])
                : t[2] == pcode__INTEGER  ? v[2] ? ( void *) (*i[2]) : ( void *) (i[2])
                : t[2] == pcode__LONG     ? v[2] ? ( void *) (*l[2]) : ( void *) (l[2])
                : t[2] == pcode__SINGLE   ? v[2] ? ( void *) (*k[2]) : ( void *) (k[2])
                : t[2] == pcode__DOUBLE   ? v[2] ? ( void *) (*d[2]) : ( void *) (d[2])
                :                          (p[2])
              );
              else return runtimeError(utility::con(function, " function call failed. ", ll[lib]->errorString()));
              myStack->pushSingle(rk);
            }
            break;
          case 4:
            {
              single_c4 c = (single_c4) ll[lib]->resolve( function );
              if (c) rk = c (
                  t[0] == pcode__BOOLEAN  ? v[0] ? ( void *) (*b[0]) : ( void *) (b[0])
                : t[0] == pcode__BYTE     ? v[0] ? ( void *) (*y[0]) : ( void *) (y[0])
                : t[0] == pcode__SHORT    ? v[0] ? ( void *) (*s[0]) : ( void *) (s[0])
                : t[0] == pcode__INTEGER  ? v[0] ? ( void *) (*i[0]) : ( void *) (i[0])
                : t[0] == pcode__LONG     ? v[0] ? ( void *) (*l[0]) : ( void *) (l[0])
                : t[0] == pcode__SINGLE   ? v[0] ? ( void *) (*k[0]) : ( void *) (k[0])
                : t[0] == pcode__DOUBLE   ? v[0] ? ( void *) (*d[0]) : ( void *) (d[0])
                :                          (p[0])
                ,
                  t[1] == pcode__BOOLEAN  ? v[1] ? ( void *) (*b[1]) : ( void *) (b[1])
                : t[1] == pcode__BYTE     ? v[1] ? ( void *) (*y[1]) : ( void *) (y[1])
                : t[1] == pcode__SHORT    ? v[1] ? ( void *) (*s[1]) : ( void *) (s[1])
                : t[1] == pcode__INTEGER  ? v[1] ? ( void *) (*i[1]) : ( void *) (i[1])
                : t[1] == pcode__LONG     ? v[1] ? ( void *) (*l[1]) : ( void *) (l[1])
                : t[1] == pcode__SINGLE   ? v[1] ? ( void *) (*k[1]) : ( void *) (k[1])
                : t[1] == pcode__DOUBLE   ? v[1] ? ( void *) (*d[1]) : ( void *) (d[1])
                :                          (p[1])
                ,
                  t[2] == pcode__BOOLEAN  ? v[2] ? ( void *) (*b[2]) : ( void *) (b[2])
                : t[2] == pcode__BYTE     ? v[2] ? ( void *) (*y[2]) : ( void *) (y[2])
                : t[2] == pcode__SHORT    ? v[2] ? ( void *) (*s[2]) : ( void *) (s[2])
                : t[2] == pcode__INTEGER  ? v[2] ? ( void *) (*i[2]) : ( void *) (i[2])
                : t[2] == pcode__LONG     ? v[2] ? ( void *) (*l[2]) : ( void *) (l[2])
                : t[2] == pcode__SINGLE   ? v[2] ? ( void *) (*k[2]) : ( void *) (k[2])
                : t[2] == pcode__DOUBLE   ? v[2] ? ( void *) (*d[2]) : ( void *) (d[2])
                :                          (p[2])
                ,
                  t[3] == pcode__BOOLEAN  ? v[3] ? ( void *) (*b[3]) : ( void *) (b[3])
                : t[3] == pcode__BYTE     ? v[3] ? ( void *) (*y[3]) : ( void *) (y[3])
                : t[3] == pcode__SHORT    ? v[3] ? ( void *) (*s[3]) : ( void *) (s[3])
                : t[3] == pcode__INTEGER  ? v[3] ? ( void *) (*i[3]) : ( void *) (i[3])
                : t[3] == pcode__LONG     ? v[3] ? ( void *) (*l[3]) : ( void *) (l[3])
                : t[3] == pcode__SINGLE   ? v[3] ? ( void *) (*k[3]) : ( void *) (k[3])
                : t[3] == pcode__DOUBLE   ? v[3] ? ( void *) (*d[3]) : ( void *) (d[3])
                :                          (p[3])
              );
              else return runtimeError(utility::con(function, " function call failed. ", ll[lib]->errorString()));
              myStack->pushSingle(rk);
            }
            break;
          case 5:
            {
              single_c5 c = (single_c5) ll[lib]->resolve( function );
              if (c) rk = c (
                  t[0] == pcode__BOOLEAN  ? v[0] ? ( void *) (*b[0]) : ( void *) (b[0])
                : t[0] == pcode__BYTE     ? v[0] ? ( void *) (*y[0]) : ( void *) (y[0])
                : t[0] == pcode__SHORT    ? v[0] ? ( void *) (*s[0]) : ( void *) (s[0])
                : t[0] == pcode__INTEGER  ? v[0] ? ( void *) (*i[0]) : ( void *) (i[0])
                : t[0] == pcode__LONG     ? v[0] ? ( void *) (*l[0]) : ( void *) (l[0])
                : t[0] == pcode__SINGLE   ? v[0] ? ( void *) (*k[0]) : ( void *) (k[0])
                : t[0] == pcode__DOUBLE   ? v[0] ? ( void *) (*d[0]) : ( void *) (d[0])
                :                          (p[0])
                ,
                  t[1] == pcode__BOOLEAN  ? v[1] ? ( void *) (*b[1]) : ( void *) (b[1])
                : t[1] == pcode__BYTE     ? v[1] ? ( void *) (*y[1]) : ( void *) (y[1])
                : t[1] == pcode__SHORT    ? v[1] ? ( void *) (*s[1]) : ( void *) (s[1])
                : t[1] == pcode__INTEGER  ? v[1] ? ( void *) (*i[1]) : ( void *) (i[1])
                : t[1] == pcode__LONG     ? v[1] ? ( void *) (*l[1]) : ( void *) (l[1])
                : t[1] == pcode__SINGLE   ? v[1] ? ( void *) (*k[1]) : ( void *) (k[1])
                : t[1] == pcode__DOUBLE   ? v[1] ? ( void *) (*d[1]) : ( void *) (d[1])
                :                          (p[1])
                ,
                  t[2] == pcode__BOOLEAN  ? v[2] ? ( void *) (*b[2]) : ( void *) (b[2])
                : t[2] == pcode__BYTE     ? v[2] ? ( void *) (*y[2]) : ( void *) (y[2])
                : t[2] == pcode__SHORT    ? v[2] ? ( void *) (*s[2]) : ( void *) (s[2])
                : t[2] == pcode__INTEGER  ? v[2] ? ( void *) (*i[2]) : ( void *) (i[2])
                : t[2] == pcode__LONG     ? v[2] ? ( void *) (*l[2]) : ( void *) (l[2])
                : t[2] == pcode__SINGLE   ? v[2] ? ( void *) (*k[2]) : ( void *) (k[2])
                : t[2] == pcode__DOUBLE   ? v[2] ? ( void *) (*d[2]) : ( void *) (d[2])
                :                          (p[2])
                ,
                  t[3] == pcode__BOOLEAN  ? v[3] ? ( void *) (*b[3]) : ( void *) (b[3])
                : t[3] == pcode__BYTE     ? v[3] ? ( void *) (*y[3]) : ( void *) (y[3])
                : t[3] == pcode__SHORT    ? v[3] ? ( void *) (*s[3]) : ( void *) (s[3])
                : t[3] == pcode__INTEGER  ? v[3] ? ( void *) (*i[3]) : ( void *) (i[3])
                : t[3] == pcode__LONG     ? v[3] ? ( void *) (*l[3]) : ( void *) (l[3])
                : t[3] == pcode__SINGLE   ? v[3] ? ( void *) (*k[3]) : ( void *) (k[3])
                : t[3] == pcode__DOUBLE   ? v[3] ? ( void *) (*d[3]) : ( void *) (d[3])
                :                          (p[3])
                ,
                  t[4] == pcode__BOOLEAN  ? v[4] ? ( void *) (*b[4]) : ( void *) (b[4])
                : t[4] == pcode__BYTE     ? v[4] ? ( void *) (*y[4]) : ( void *) (y[4])
                : t[4] == pcode__SHORT    ? v[4] ? ( void *) (*s[4]) : ( void *) (s[4])
                : t[4] == pcode__INTEGER  ? v[4] ? ( void *) (*i[4]) : ( void *) (i[4])
                : t[4] == pcode__LONG     ? v[4] ? ( void *) (*l[4]) : ( void *) (l[4])
                : t[4] == pcode__SINGLE   ? v[4] ? ( void *) (*k[4]) : ( void *) (k[4])
                : t[4] == pcode__DOUBLE   ? v[4] ? ( void *) (*d[4]) : ( void *) (d[4])
                :                          (p[4])
              );
              else return runtimeError(utility::con(function, " function call failed. ", ll[lib]->errorString()));
              myStack->pushSingle(rk);
            }
            break;
          case 6:
            {
              single_c6 c = (single_c6) ll[lib]->resolve( function );
              if (c) rk = c (
                  t[0] == pcode__BOOLEAN  ? v[0] ? ( void *) (*b[0]) : ( void *) (b[0])
                : t[0] == pcode__BYTE     ? v[0] ? ( void *) (*y[0]) : ( void *) (y[0])
                : t[0] == pcode__SHORT    ? v[0] ? ( void *) (*s[0]) : ( void *) (s[0])
                : t[0] == pcode__INTEGER  ? v[0] ? ( void *) (*i[0]) : ( void *) (i[0])
                : t[0] == pcode__LONG     ? v[0] ? ( void *) (*l[0]) : ( void *) (l[0])
                : t[0] == pcode__SINGLE   ? v[0] ? ( void *) (*k[0]) : ( void *) (k[0])
                : t[0] == pcode__DOUBLE   ? v[0] ? ( void *) (*d[0]) : ( void *) (d[0])
                :                          (p[0])
                ,
                  t[1] == pcode__BOOLEAN  ? v[1] ? ( void *) (*b[1]) : ( void *) (b[1])
                : t[1] == pcode__BYTE     ? v[1] ? ( void *) (*y[1]) : ( void *) (y[1])
                : t[1] == pcode__SHORT    ? v[1] ? ( void *) (*s[1]) : ( void *) (s[1])
                : t[1] == pcode__INTEGER  ? v[1] ? ( void *) (*i[1]) : ( void *) (i[1])
                : t[1] == pcode__LONG     ? v[1] ? ( void *) (*l[1]) : ( void *) (l[1])
                : t[1] == pcode__SINGLE   ? v[1] ? ( void *) (*k[1]) : ( void *) (k[1])
                : t[1] == pcode__DOUBLE   ? v[1] ? ( void *) (*d[1]) : ( void *) (d[1])
                :                          (p[1])
                ,
                  t[2] == pcode__BOOLEAN  ? v[2] ? ( void *) (*b[2]) : ( void *) (b[2])
                : t[2] == pcode__BYTE     ? v[2] ? ( void *) (*y[2]) : ( void *) (y[2])
                : t[2] == pcode__SHORT    ? v[2] ? ( void *) (*s[2]) : ( void *) (s[2])
                : t[2] == pcode__INTEGER  ? v[2] ? ( void *) (*i[2]) : ( void *) (i[2])
                : t[2] == pcode__LONG     ? v[2] ? ( void *) (*l[2]) : ( void *) (l[2])
                : t[2] == pcode__SINGLE   ? v[2] ? ( void *) (*k[2]) : ( void *) (k[2])
                : t[2] == pcode__DOUBLE   ? v[2] ? ( void *) (*d[2]) : ( void *) (d[2])
                :                          (p[2])
                ,
                  t[3] == pcode__BOOLEAN  ? v[3] ? ( void *) (*b[3]) : ( void *) (b[3])
                : t[3] == pcode__BYTE     ? v[3] ? ( void *) (*y[3]) : ( void *) (y[3])
                : t[3] == pcode__SHORT    ? v[3] ? ( void *) (*s[3]) : ( void *) (s[3])
                : t[3] == pcode__INTEGER  ? v[3] ? ( void *) (*i[3]) : ( void *) (i[3])
                : t[3] == pcode__LONG     ? v[3] ? ( void *) (*l[3]) : ( void *) (l[3])
                : t[3] == pcode__SINGLE   ? v[3] ? ( void *) (*k[3]) : ( void *) (k[3])
                : t[3] == pcode__DOUBLE   ? v[3] ? ( void *) (*d[3]) : ( void *) (d[3])
                :                          (p[3])
                ,
                  t[4] == pcode__BOOLEAN  ? v[4] ? ( void *) (*b[4]) : ( void *) (b[4])
                : t[4] == pcode__BYTE     ? v[4] ? ( void *) (*y[4]) : ( void *) (y[4])
                : t[4] == pcode__SHORT    ? v[4] ? ( void *) (*s[4]) : ( void *) (s[4])
                : t[4] == pcode__INTEGER  ? v[4] ? ( void *) (*i[4]) : ( void *) (i[4])
                : t[4] == pcode__LONG     ? v[4] ? ( void *) (*l[4]) : ( void *) (l[4])
                : t[4] == pcode__SINGLE   ? v[4] ? ( void *) (*k[4]) : ( void *) (k[4])
                : t[4] == pcode__DOUBLE   ? v[4] ? ( void *) (*d[4]) : ( void *) (d[4])
                :                          (p[4])
                ,
                  t[5] == pcode__BOOLEAN  ? v[5] ? ( void *) (*b[5]) : ( void *) (b[5])
                : t[5] == pcode__BYTE     ? v[5] ? ( void *) (*y[5]) : ( void *) (y[5])
                : t[5] == pcode__SHORT    ? v[5] ? ( void *) (*s[5]) : ( void *) (s[5])
                : t[5] == pcode__INTEGER  ? v[5] ? ( void *) (*i[5]) : ( void *) (i[5])
                : t[5] == pcode__LONG     ? v[5] ? ( void *) (*l[5]) : ( void *) (l[5])
                : t[5] == pcode__SINGLE   ? v[5] ? ( void *) (*k[5]) : ( void *) (k[5])
                : t[5] == pcode__DOUBLE   ? v[5] ? ( void *) (*d[5]) : ( void *) (d[5])
                :                          (p[5])
              );
              else return runtimeError(utility::con(function, " function call failed. ", ll[lib]->errorString()));
              myStack->pushSingle(rk);
            }
            break;
          case 7:
            {
              single_c7 c = (single_c7) ll[lib]->resolve( function );
              if (c) rk = c (
                  t[0] == pcode__BOOLEAN  ? v[0] ? ( void *) (*b[0]) : ( void *) (b[0])
                : t[0] == pcode__BYTE     ? v[0] ? ( void *) (*y[0]) : ( void *) (y[0])
                : t[0] == pcode__SHORT    ? v[0] ? ( void *) (*s[0]) : ( void *) (s[0])
                : t[0] == pcode__INTEGER  ? v[0] ? ( void *) (*i[0]) : ( void *) (i[0])
                : t[0] == pcode__LONG     ? v[0] ? ( void *) (*l[0]) : ( void *) (l[0])
                : t[0] == pcode__SINGLE   ? v[0] ? ( void *) (*k[0]) : ( void *) (k[0])
                : t[0] == pcode__DOUBLE   ? v[0] ? ( void *) (*d[0]) : ( void *) (d[0])
                :                          (p[0])
                ,
                  t[1] == pcode__BOOLEAN  ? v[1] ? ( void *) (*b[1]) : ( void *) (b[1])
                : t[1] == pcode__BYTE     ? v[1] ? ( void *) (*y[1]) : ( void *) (y[1])
                : t[1] == pcode__SHORT    ? v[1] ? ( void *) (*s[1]) : ( void *) (s[1])
                : t[1] == pcode__INTEGER  ? v[1] ? ( void *) (*i[1]) : ( void *) (i[1])
                : t[1] == pcode__LONG     ? v[1] ? ( void *) (*l[1]) : ( void *) (l[1])
                : t[1] == pcode__SINGLE   ? v[1] ? ( void *) (*k[1]) : ( void *) (k[1])
                : t[1] == pcode__DOUBLE   ? v[1] ? ( void *) (*d[1]) : ( void *) (d[1])
                :                          (p[1])
                ,
                  t[2] == pcode__BOOLEAN  ? v[2] ? ( void *) (*b[2]) : ( void *) (b[2])
                : t[2] == pcode__BYTE     ? v[2] ? ( void *) (*y[2]) : ( void *) (y[2])
                : t[2] == pcode__SHORT    ? v[2] ? ( void *) (*s[2]) : ( void *) (s[2])
                : t[2] == pcode__INTEGER  ? v[2] ? ( void *) (*i[2]) : ( void *) (i[2])
                : t[2] == pcode__LONG     ? v[2] ? ( void *) (*l[2]) : ( void *) (l[2])
                : t[2] == pcode__SINGLE   ? v[2] ? ( void *) (*k[2]) : ( void *) (k[2])
                : t[2] == pcode__DOUBLE   ? v[2] ? ( void *) (*d[2]) : ( void *) (d[2])
                :                          (p[2])
                ,
                  t[3] == pcode__BOOLEAN  ? v[3] ? ( void *) (*b[3]) : ( void *) (b[3])
                : t[3] == pcode__BYTE     ? v[3] ? ( void *) (*y[3]) : ( void *) (y[3])
                : t[3] == pcode__SHORT    ? v[3] ? ( void *) (*s[3]) : ( void *) (s[3])
                : t[3] == pcode__INTEGER  ? v[3] ? ( void *) (*i[3]) : ( void *) (i[3])
                : t[3] == pcode__LONG     ? v[3] ? ( void *) (*l[3]) : ( void *) (l[3])
                : t[3] == pcode__SINGLE   ? v[3] ? ( void *) (*k[3]) : ( void *) (k[3])
                : t[3] == pcode__DOUBLE   ? v[3] ? ( void *) (*d[3]) : ( void *) (d[3])
                :                          (p[3])
                ,
                  t[4] == pcode__BOOLEAN  ? v[4] ? ( void *) (*b[4]) : ( void *) (b[4])
                : t[4] == pcode__BYTE     ? v[4] ? ( void *) (*y[4]) : ( void *) (y[4])
                : t[4] == pcode__SHORT    ? v[4] ? ( void *) (*s[4]) : ( void *) (s[4])
                : t[4] == pcode__INTEGER  ? v[4] ? ( void *) (*i[4]) : ( void *) (i[4])
                : t[4] == pcode__LONG     ? v[4] ? ( void *) (*l[4]) : ( void *) (l[4])
                : t[4] == pcode__SINGLE   ? v[4] ? ( void *) (*k[4]) : ( void *) (k[4])
                : t[4] == pcode__DOUBLE   ? v[4] ? ( void *) (*d[4]) : ( void *) (d[4])
                :                          (p[4])
                ,
                  t[5] == pcode__BOOLEAN  ? v[5] ? ( void *) (*b[5]) : ( void *) (b[5])
                : t[5] == pcode__BYTE     ? v[5] ? ( void *) (*y[5]) : ( void *) (y[5])
                : t[5] == pcode__SHORT    ? v[5] ? ( void *) (*s[5]) : ( void *) (s[5])
                : t[5] == pcode__INTEGER  ? v[5] ? ( void *) (*i[5]) : ( void *) (i[5])
                : t[5] == pcode__LONG     ? v[5] ? ( void *) (*l[5]) : ( void *) (l[5])
                : t[5] == pcode__SINGLE   ? v[5] ? ( void *) (*k[5]) : ( void *) (k[5])
                : t[5] == pcode__DOUBLE   ? v[5] ? ( void *) (*d[5]) : ( void *) (d[5])
                :                          (p[5])
                ,
                  t[6] == pcode__BOOLEAN  ? v[6] ? ( void *) (*b[6]) : ( void *) (b[6])
                : t[6] == pcode__BYTE     ? v[6] ? ( void *) (*y[6]) : ( void *) (y[6])
                : t[6] == pcode__SHORT    ? v[6] ? ( void *) (*s[6]) : ( void *) (s[6])
                : t[6] == pcode__INTEGER  ? v[6] ? ( void *) (*i[6]) : ( void *) (i[6])
                : t[6] == pcode__LONG     ? v[6] ? ( void *) (*l[6]) : ( void *) (l[6])
                : t[6] == pcode__SINGLE   ? v[6] ? ( void *) (*k[6]) : ( void *) (k[6])
                : t[6] == pcode__DOUBLE   ? v[6] ? ( void *) (*d[6]) : ( void *) (d[6])
                :                          (p[6])
              );
              else return runtimeError(utility::con(function, " function call failed. ", ll[lib]->errorString()));
              myStack->pushSingle(rk);
            }
            break;
          case 8:
            {
              single_c8 c = (single_c8) ll[lib]->resolve( function );
              if (c) rk = c (
                  t[0] == pcode__BOOLEAN  ? v[0] ? ( void *) (*b[0]) : ( void *) (b[0])
                : t[0] == pcode__BYTE     ? v[0] ? ( void *) (*y[0]) : ( void *) (y[0])
                : t[0] == pcode__SHORT    ? v[0] ? ( void *) (*s[0]) : ( void *) (s[0])
                : t[0] == pcode__INTEGER  ? v[0] ? ( void *) (*i[0]) : ( void *) (i[0])
                : t[0] == pcode__LONG     ? v[0] ? ( void *) (*l[0]) : ( void *) (l[0])
                : t[0] == pcode__SINGLE   ? v[0] ? ( void *) (*k[0]) : ( void *) (k[0])
                : t[0] == pcode__DOUBLE   ? v[0] ? ( void *) (*d[0]) : ( void *) (d[0])
                :                          (p[0])
                ,
                  t[1] == pcode__BOOLEAN  ? v[1] ? ( void *) (*b[1]) : ( void *) (b[1])
                : t[1] == pcode__BYTE     ? v[1] ? ( void *) (*y[1]) : ( void *) (y[1])
                : t[1] == pcode__SHORT    ? v[1] ? ( void *) (*s[1]) : ( void *) (s[1])
                : t[1] == pcode__INTEGER  ? v[1] ? ( void *) (*i[1]) : ( void *) (i[1])
                : t[1] == pcode__LONG     ? v[1] ? ( void *) (*l[1]) : ( void *) (l[1])
                : t[1] == pcode__SINGLE   ? v[1] ? ( void *) (*k[1]) : ( void *) (k[1])
                : t[1] == pcode__DOUBLE   ? v[1] ? ( void *) (*d[1]) : ( void *) (d[1])
                :                          (p[1])
                ,
                  t[2] == pcode__BOOLEAN  ? v[2] ? ( void *) (*b[2]) : ( void *) (b[2])
                : t[2] == pcode__BYTE     ? v[2] ? ( void *) (*y[2]) : ( void *) (y[2])
                : t[2] == pcode__SHORT    ? v[2] ? ( void *) (*s[2]) : ( void *) (s[2])
                : t[2] == pcode__INTEGER  ? v[2] ? ( void *) (*i[2]) : ( void *) (i[2])
                : t[2] == pcode__LONG     ? v[2] ? ( void *) (*l[2]) : ( void *) (l[2])
                : t[2] == pcode__SINGLE   ? v[2] ? ( void *) (*k[2]) : ( void *) (k[2])
                : t[2] == pcode__DOUBLE   ? v[2] ? ( void *) (*d[2]) : ( void *) (d[2])
                :                          (p[2])
                ,
                  t[3] == pcode__BOOLEAN  ? v[3] ? ( void *) (*b[3]) : ( void *) (b[3])
                : t[3] == pcode__BYTE     ? v[3] ? ( void *) (*y[3]) : ( void *) (y[3])
                : t[3] == pcode__SHORT    ? v[3] ? ( void *) (*s[3]) : ( void *) (s[3])
                : t[3] == pcode__INTEGER  ? v[3] ? ( void *) (*i[3]) : ( void *) (i[3])
                : t[3] == pcode__LONG     ? v[3] ? ( void *) (*l[3]) : ( void *) (l[3])
                : t[3] == pcode__SINGLE   ? v[3] ? ( void *) (*k[3]) : ( void *) (k[3])
                : t[3] == pcode__DOUBLE   ? v[3] ? ( void *) (*d[3]) : ( void *) (d[3])
                :                          (p[3])
                ,
                  t[4] == pcode__BOOLEAN  ? v[4] ? ( void *) (*b[4]) : ( void *) (b[4])
                : t[4] == pcode__BYTE     ? v[4] ? ( void *) (*y[4]) : ( void *) (y[4])
                : t[4] == pcode__SHORT    ? v[4] ? ( void *) (*s[4]) : ( void *) (s[4])
                : t[4] == pcode__INTEGER  ? v[4] ? ( void *) (*i[4]) : ( void *) (i[4])
                : t[4] == pcode__LONG     ? v[4] ? ( void *) (*l[4]) : ( void *) (l[4])
                : t[4] == pcode__SINGLE   ? v[4] ? ( void *) (*k[4]) : ( void *) (k[4])
                : t[4] == pcode__DOUBLE   ? v[4] ? ( void *) (*d[4]) : ( void *) (d[4])
                :                          (p[4])
                ,
                  t[5] == pcode__BOOLEAN  ? v[5] ? ( void *) (*b[5]) : ( void *) (b[5])
                : t[5] == pcode__BYTE     ? v[5] ? ( void *) (*y[5]) : ( void *) (y[5])
                : t[5] == pcode__SHORT    ? v[5] ? ( void *) (*s[5]) : ( void *) (s[5])
                : t[5] == pcode__INTEGER  ? v[5] ? ( void *) (*i[5]) : ( void *) (i[5])
                : t[5] == pcode__LONG     ? v[5] ? ( void *) (*l[5]) : ( void *) (l[5])
                : t[5] == pcode__SINGLE   ? v[5] ? ( void *) (*k[5]) : ( void *) (k[5])
                : t[5] == pcode__DOUBLE   ? v[5] ? ( void *) (*d[5]) : ( void *) (d[5])
                :                          (p[5])
                ,
                  t[6] == pcode__BOOLEAN  ? v[6] ? ( void *) (*b[6]) : ( void *) (b[6])
                : t[6] == pcode__BYTE     ? v[6] ? ( void *) (*y[6]) : ( void *) (y[6])
                : t[6] == pcode__SHORT    ? v[6] ? ( void *) (*s[6]) : ( void *) (s[6])
                : t[6] == pcode__INTEGER  ? v[6] ? ( void *) (*i[6]) : ( void *) (i[6])
                : t[6] == pcode__LONG     ? v[6] ? ( void *) (*l[6]) : ( void *) (l[6])
                : t[6] == pcode__SINGLE   ? v[6] ? ( void *) (*k[6]) : ( void *) (k[6])
                : t[6] == pcode__DOUBLE   ? v[6] ? ( void *) (*d[6]) : ( void *) (d[6])
                :                          (p[6])
                ,
                  t[7] == pcode__BOOLEAN  ? v[7] ? ( void *) (*b[7]) : ( void *) (b[7])
                : t[7] == pcode__BYTE     ? v[7] ? ( void *) (*y[7]) : ( void *) (y[7])
                : t[7] == pcode__SHORT    ? v[7] ? ( void *) (*s[7]) : ( void *) (s[7])
                : t[7] == pcode__INTEGER  ? v[7] ? ( void *) (*i[7]) : ( void *) (i[7])
                : t[7] == pcode__LONG     ? v[7] ? ( void *) (*l[7]) : ( void *) (l[7])
                : t[7] == pcode__SINGLE   ? v[7] ? ( void *) (*k[7]) : ( void *) (k[7])
                : t[7] == pcode__DOUBLE   ? v[7] ? ( void *) (*d[7]) : ( void *) (d[7])
                :                          (p[7])
              );
              else return runtimeError(utility::con(function, " function call failed. ", ll[lib]->errorString()));
              myStack->pushSingle(rk);
            }
            break;
          case 9:
            {
              single_c9 c = (single_c9) ll[lib]->resolve( function );
              if (c) rk = c (
                  t[0] == pcode__BOOLEAN  ? v[0] ? ( void *) (*b[0]) : ( void *) (b[0])
                : t[0] == pcode__BYTE     ? v[0] ? ( void *) (*y[0]) : ( void *) (y[0])
                : t[0] == pcode__SHORT    ? v[0] ? ( void *) (*s[0]) : ( void *) (s[0])
                : t[0] == pcode__INTEGER  ? v[0] ? ( void *) (*i[0]) : ( void *) (i[0])
                : t[0] == pcode__LONG     ? v[0] ? ( void *) (*l[0]) : ( void *) (l[0])
                : t[0] == pcode__SINGLE   ? v[0] ? ( void *) (*k[0]) : ( void *) (k[0])
                : t[0] == pcode__DOUBLE   ? v[0] ? ( void *) (*d[0]) : ( void *) (d[0])
                :                          (p[0])
                ,
                  t[1] == pcode__BOOLEAN  ? v[1] ? ( void *) (*b[1]) : ( void *) (b[1])
                : t[1] == pcode__BYTE     ? v[1] ? ( void *) (*y[1]) : ( void *) (y[1])
                : t[1] == pcode__SHORT    ? v[1] ? ( void *) (*s[1]) : ( void *) (s[1])
                : t[1] == pcode__INTEGER  ? v[1] ? ( void *) (*i[1]) : ( void *) (i[1])
                : t[1] == pcode__LONG     ? v[1] ? ( void *) (*l[1]) : ( void *) (l[1])
                : t[1] == pcode__SINGLE   ? v[1] ? ( void *) (*k[1]) : ( void *) (k[1])
                : t[1] == pcode__DOUBLE   ? v[1] ? ( void *) (*d[1]) : ( void *) (d[1])
                :                          (p[1])
                ,
                  t[2] == pcode__BOOLEAN  ? v[2] ? ( void *) (*b[2]) : ( void *) (b[2])
                : t[2] == pcode__BYTE     ? v[2] ? ( void *) (*y[2]) : ( void *) (y[2])
                : t[2] == pcode__SHORT    ? v[2] ? ( void *) (*s[2]) : ( void *) (s[2])
                : t[2] == pcode__INTEGER  ? v[2] ? ( void *) (*i[2]) : ( void *) (i[2])
                : t[2] == pcode__LONG     ? v[2] ? ( void *) (*l[2]) : ( void *) (l[2])
                : t[2] == pcode__SINGLE   ? v[2] ? ( void *) (*k[2]) : ( void *) (k[2])
                : t[2] == pcode__DOUBLE   ? v[2] ? ( void *) (*d[2]) : ( void *) (d[2])
                :                          (p[2])
                ,
                  t[3] == pcode__BOOLEAN  ? v[3] ? ( void *) (*b[3]) : ( void *) (b[3])
                : t[3] == pcode__BYTE     ? v[3] ? ( void *) (*y[3]) : ( void *) (y[3])
                : t[3] == pcode__SHORT    ? v[3] ? ( void *) (*s[3]) : ( void *) (s[3])
                : t[3] == pcode__INTEGER  ? v[3] ? ( void *) (*i[3]) : ( void *) (i[3])
                : t[3] == pcode__LONG     ? v[3] ? ( void *) (*l[3]) : ( void *) (l[3])
                : t[3] == pcode__SINGLE   ? v[3] ? ( void *) (*k[3]) : ( void *) (k[3])
                : t[3] == pcode__DOUBLE   ? v[3] ? ( void *) (*d[3]) : ( void *) (d[3])
                :                          (p[3])
                ,
                  t[4] == pcode__BOOLEAN  ? v[4] ? ( void *) (*b[4]) : ( void *) (b[4])
                : t[4] == pcode__BYTE     ? v[4] ? ( void *) (*y[4]) : ( void *) (y[4])
                : t[4] == pcode__SHORT    ? v[4] ? ( void *) (*s[4]) : ( void *) (s[4])
                : t[4] == pcode__INTEGER  ? v[4] ? ( void *) (*i[4]) : ( void *) (i[4])
                : t[4] == pcode__LONG     ? v[4] ? ( void *) (*l[4]) : ( void *) (l[4])
                : t[4] == pcode__SINGLE   ? v[4] ? ( void *) (*k[4]) : ( void *) (k[4])
                : t[4] == pcode__DOUBLE   ? v[4] ? ( void *) (*d[4]) : ( void *) (d[4])
                :                          (p[4])
                ,
                  t[5] == pcode__BOOLEAN  ? v[5] ? ( void *) (*b[5]) : ( void *) (b[5])
                : t[5] == pcode__BYTE     ? v[5] ? ( void *) (*y[5]) : ( void *) (y[5])
                : t[5] == pcode__SHORT    ? v[5] ? ( void *) (*s[5]) : ( void *) (s[5])
                : t[5] == pcode__INTEGER  ? v[5] ? ( void *) (*i[5]) : ( void *) (i[5])
                : t[5] == pcode__LONG     ? v[5] ? ( void *) (*l[5]) : ( void *) (l[5])
                : t[5] == pcode__SINGLE   ? v[5] ? ( void *) (*k[5]) : ( void *) (k[5])
                : t[5] == pcode__DOUBLE   ? v[5] ? ( void *) (*d[5]) : ( void *) (d[5])
                :                          (p[5])
                ,
                  t[6] == pcode__BOOLEAN  ? v[6] ? ( void *) (*b[6]) : ( void *) (b[6])
                : t[6] == pcode__BYTE     ? v[6] ? ( void *) (*y[6]) : ( void *) (y[6])
                : t[6] == pcode__SHORT    ? v[6] ? ( void *) (*s[6]) : ( void *) (s[6])
                : t[6] == pcode__INTEGER  ? v[6] ? ( void *) (*i[6]) : ( void *) (i[6])
                : t[6] == pcode__LONG     ? v[6] ? ( void *) (*l[6]) : ( void *) (l[6])
                : t[6] == pcode__SINGLE   ? v[6] ? ( void *) (*k[6]) : ( void *) (k[6])
                : t[6] == pcode__DOUBLE   ? v[6] ? ( void *) (*d[6]) : ( void *) (d[6])
                :                          (p[6])
                ,
                  t[7] == pcode__BOOLEAN  ? v[7] ? ( void *) (*b[7]) : ( void *) (b[7])
                : t[7] == pcode__BYTE     ? v[7] ? ( void *) (*y[7]) : ( void *) (y[7])
                : t[7] == pcode__SHORT    ? v[7] ? ( void *) (*s[7]) : ( void *) (s[7])
                : t[7] == pcode__INTEGER  ? v[7] ? ( void *) (*i[7]) : ( void *) (i[7])
                : t[7] == pcode__LONG     ? v[7] ? ( void *) (*l[7]) : ( void *) (l[7])
                : t[7] == pcode__SINGLE   ? v[7] ? ( void *) (*k[7]) : ( void *) (k[7])
                : t[7] == pcode__DOUBLE   ? v[7] ? ( void *) (*d[7]) : ( void *) (d[7])
                :                          (p[7])
                ,
                  t[8] == pcode__BOOLEAN  ? v[8] ? ( void *) (*b[8]) : ( void *) (b[8])
                : t[8] == pcode__BYTE     ? v[8] ? ( void *) (*y[8]) : ( void *) (y[8])
                : t[8] == pcode__SHORT    ? v[8] ? ( void *) (*s[8]) : ( void *) (s[8])
                : t[8] == pcode__INTEGER  ? v[8] ? ( void *) (*i[8]) : ( void *) (i[8])
                : t[8] == pcode__LONG     ? v[8] ? ( void *) (*l[8]) : ( void *) (l[8])
                : t[8] == pcode__SINGLE   ? v[8] ? ( void *) (*k[8]) : ( void *) (k[8])
                : t[8] == pcode__DOUBLE   ? v[8] ? ( void *) (*d[8]) : ( void *) (d[8])
                :                          (p[8])
              );
              else return runtimeError(utility::con(function, " function call failed. ", ll[lib]->errorString()));
              myStack->pushSingle(rk);
            }
            break;
          default:
            return runtimeError(utility::con(function, ": Too much arguments (max. 9 allowed) when calling declare function."));
            break;
         }
        break;     

       case pcode__DOUBLE:
        switch(count){
          case 0:
            {
              double_c0 c = (double_c0) ll[lib]->resolve( function );
              if (c) rd = c (
              );
              else return runtimeError(utility::con(function, " function call failed. ", ll[lib]->errorString()));
              myStack->pushDouble(rd);
            }
            break;
          case 1:
            {
              double_c1 c = (double_c1) ll[lib]->resolve( function );
              if (c) rd = c (
                  t[0] == pcode__BOOLEAN  ? v[0] ? ( void *) (*b[0]) : ( void *) (b[0])
                : t[0] == pcode__BYTE     ? v[0] ? ( void *) (*y[0]) : ( void *) (y[0])
                : t[0] == pcode__SHORT    ? v[0] ? ( void *) (*s[0]) : ( void *) (s[0])
                : t[0] == pcode__INTEGER  ? v[0] ? ( void *) (*i[0]) : ( void *) (i[0])
                : t[0] == pcode__LONG     ? v[0] ? ( void *) (*l[0]) : ( void *) (l[0])
                : t[0] == pcode__SINGLE   ? v[0] ? ( void *) (*k[0]) : ( void *) (k[0])
                : t[0] == pcode__DOUBLE   ? v[0] ? ( void *) (*d[0]) : ( void *) (d[0])
                :                          (p[0])
              );
              else return runtimeError(utility::con(function, " function call failed. ", ll[lib]->errorString()));
              myStack->pushDouble(rd);
            }
            break;
          case 2:
            {
              double_c2 c = (double_c2) ll[lib]->resolve( function );
              if (c) rd = c (
                  t[0] == pcode__BOOLEAN  ? v[0] ? ( void *) (*b[0]) : ( void *) (b[0])
                : t[0] == pcode__BYTE     ? v[0] ? ( void *) (*y[0]) : ( void *) (y[0])
                : t[0] == pcode__SHORT    ? v[0] ? ( void *) (*s[0]) : ( void *) (s[0])
                : t[0] == pcode__INTEGER  ? v[0] ? ( void *) (*i[0]) : ( void *) (i[0])
                : t[0] == pcode__LONG     ? v[0] ? ( void *) (*l[0]) : ( void *) (l[0])
                : t[0] == pcode__SINGLE   ? v[0] ? ( void *) (*k[0]) : ( void *) (k[0])
                : t[0] == pcode__DOUBLE   ? v[0] ? ( void *) (*d[0]) : ( void *) (d[0])
                :                          (p[0])
                ,
                  t[1] == pcode__BOOLEAN  ? v[1] ? ( void *) (*b[1]) : ( void *) (b[1])
                : t[1] == pcode__BYTE     ? v[1] ? ( void *) (*y[1]) : ( void *) (y[1])
                : t[1] == pcode__SHORT    ? v[1] ? ( void *) (*s[1]) : ( void *) (s[1])
                : t[1] == pcode__INTEGER  ? v[1] ? ( void *) (*i[1]) : ( void *) (i[1])
                : t[1] == pcode__LONG     ? v[1] ? ( void *) (*l[1]) : ( void *) (l[1])
                : t[1] == pcode__SINGLE   ? v[1] ? ( void *) (*k[1]) : ( void *) (k[1])
                : t[1] == pcode__DOUBLE   ? v[1] ? ( void *) (*d[1]) : ( void *) (d[1])
                :                          (p[1])
              );
              else return runtimeError(utility::con(function, " function call failed. ", ll[lib]->errorString()));
              myStack->pushDouble(rd);
            }
            break;
          case 3:
            {
              double_c3 c = (double_c3) ll[lib]->resolve( function );
              if (c) rd = c (
                  t[0] == pcode__BOOLEAN  ? v[0] ? ( void *) (*b[0]) : ( void *) (b[0])
                : t[0] == pcode__BYTE     ? v[0] ? ( void *) (*y[0]) : ( void *) (y[0])
                : t[0] == pcode__SHORT    ? v[0] ? ( void *) (*s[0]) : ( void *) (s[0])
                : t[0] == pcode__INTEGER  ? v[0] ? ( void *) (*i[0]) : ( void *) (i[0])
                : t[0] == pcode__LONG     ? v[0] ? ( void *) (*l[0]) : ( void *) (l[0])
                : t[0] == pcode__SINGLE   ? v[0] ? ( void *) (*k[0]) : ( void *) (k[0])
                : t[0] == pcode__DOUBLE   ? v[0] ? ( void *) (*d[0]) : ( void *) (d[0])
                :                          (p[0])
                ,
                  t[1] == pcode__BOOLEAN  ? v[1] ? ( void *) (*b[1]) : ( void *) (b[1])
                : t[1] == pcode__BYTE     ? v[1] ? ( void *) (*y[1]) : ( void *) (y[1])
                : t[1] == pcode__SHORT    ? v[1] ? ( void *) (*s[1]) : ( void *) (s[1])
                : t[1] == pcode__INTEGER  ? v[1] ? ( void *) (*i[1]) : ( void *) (i[1])
                : t[1] == pcode__LONG     ? v[1] ? ( void *) (*l[1]) : ( void *) (l[1])
                : t[1] == pcode__SINGLE   ? v[1] ? ( void *) (*k[1]) : ( void *) (k[1])
                : t[1] == pcode__DOUBLE   ? v[1] ? ( void *) (*d[1]) : ( void *) (d[1])
                :                          (p[1])
                ,
                  t[2] == pcode__BOOLEAN  ? v[2] ? ( void *) (*b[2]) : ( void *) (b[2])
                : t[2] == pcode__BYTE     ? v[2] ? ( void *) (*y[2]) : ( void *) (y[2])
                : t[2] == pcode__SHORT    ? v[2] ? ( void *) (*s[2]) : ( void *) (s[2])
                : t[2] == pcode__INTEGER  ? v[2] ? ( void *) (*i[2]) : ( void *) (i[2])
                : t[2] == pcode__LONG     ? v[2] ? ( void *) (*l[2]) : ( void *) (l[2])
                : t[2] == pcode__SINGLE   ? v[2] ? ( void *) (*k[2]) : ( void *) (k[2])
                : t[2] == pcode__DOUBLE   ? v[2] ? ( void *) (*d[2]) : ( void *) (d[2])
                :                          (p[2])
              );
              else return runtimeError(utility::con(function, " function call failed. ", ll[lib]->errorString()));
              myStack->pushDouble(rd);
            }
            break;
          case 4:
            {
              double_c4 c = (double_c4) ll[lib]->resolve( function );
              if (c) rd = c (
                  t[0] == pcode__BOOLEAN  ? v[0] ? ( void *) (*b[0]) : ( void *) (b[0])
                : t[0] == pcode__BYTE     ? v[0] ? ( void *) (*y[0]) : ( void *) (y[0])
                : t[0] == pcode__SHORT    ? v[0] ? ( void *) (*s[0]) : ( void *) (s[0])
                : t[0] == pcode__INTEGER  ? v[0] ? ( void *) (*i[0]) : ( void *) (i[0])
                : t[0] == pcode__LONG     ? v[0] ? ( void *) (*l[0]) : ( void *) (l[0])
                : t[0] == pcode__SINGLE   ? v[0] ? ( void *) (*k[0]) : ( void *) (k[0])
                : t[0] == pcode__DOUBLE   ? v[0] ? ( void *) (*d[0]) : ( void *) (d[0])
                :                          (p[0])
                ,
                  t[1] == pcode__BOOLEAN  ? v[1] ? ( void *) (*b[1]) : ( void *) (b[1])
                : t[1] == pcode__BYTE     ? v[1] ? ( void *) (*y[1]) : ( void *) (y[1])
                : t[1] == pcode__SHORT    ? v[1] ? ( void *) (*s[1]) : ( void *) (s[1])
                : t[1] == pcode__INTEGER  ? v[1] ? ( void *) (*i[1]) : ( void *) (i[1])
                : t[1] == pcode__LONG     ? v[1] ? ( void *) (*l[1]) : ( void *) (l[1])
                : t[1] == pcode__SINGLE   ? v[1] ? ( void *) (*k[1]) : ( void *) (k[1])
                : t[1] == pcode__DOUBLE   ? v[1] ? ( void *) (*d[1]) : ( void *) (d[1])
                :                          (p[1])
                ,
                  t[2] == pcode__BOOLEAN  ? v[2] ? ( void *) (*b[2]) : ( void *) (b[2])
                : t[2] == pcode__BYTE     ? v[2] ? ( void *) (*y[2]) : ( void *) (y[2])
                : t[2] == pcode__SHORT    ? v[2] ? ( void *) (*s[2]) : ( void *) (s[2])
                : t[2] == pcode__INTEGER  ? v[2] ? ( void *) (*i[2]) : ( void *) (i[2])
                : t[2] == pcode__LONG     ? v[2] ? ( void *) (*l[2]) : ( void *) (l[2])
                : t[2] == pcode__SINGLE   ? v[2] ? ( void *) (*k[2]) : ( void *) (k[2])
                : t[2] == pcode__DOUBLE   ? v[2] ? ( void *) (*d[2]) : ( void *) (d[2])
                :                          (p[2])
                ,
                  t[3] == pcode__BOOLEAN  ? v[3] ? ( void *) (*b[3]) : ( void *) (b[3])
                : t[3] == pcode__BYTE     ? v[3] ? ( void *) (*y[3]) : ( void *) (y[3])
                : t[3] == pcode__SHORT    ? v[3] ? ( void *) (*s[3]) : ( void *) (s[3])
                : t[3] == pcode__INTEGER  ? v[3] ? ( void *) (*i[3]) : ( void *) (i[3])
                : t[3] == pcode__LONG     ? v[3] ? ( void *) (*l[3]) : ( void *) (l[3])
                : t[3] == pcode__SINGLE   ? v[3] ? ( void *) (*k[3]) : ( void *) (k[3])
                : t[3] == pcode__DOUBLE   ? v[3] ? ( void *) (*d[3]) : ( void *) (d[3])
                :                          (p[3])
              );
              else return runtimeError(utility::con(function, " function call failed. ", ll[lib]->errorString()));
              myStack->pushDouble(rd);
            }
            break;
          case 5:
            {
              double_c5 c = (double_c5) ll[lib]->resolve( function );
              if (c) rd = c (
                  t[0] == pcode__BOOLEAN  ? v[0] ? ( void *) (*b[0]) : ( void *) (b[0])
                : t[0] == pcode__BYTE     ? v[0] ? ( void *) (*y[0]) : ( void *) (y[0])
                : t[0] == pcode__SHORT    ? v[0] ? ( void *) (*s[0]) : ( void *) (s[0])
                : t[0] == pcode__INTEGER  ? v[0] ? ( void *) (*i[0]) : ( void *) (i[0])
                : t[0] == pcode__LONG     ? v[0] ? ( void *) (*l[0]) : ( void *) (l[0])
                : t[0] == pcode__SINGLE   ? v[0] ? ( void *) (*k[0]) : ( void *) (k[0])
                : t[0] == pcode__DOUBLE   ? v[0] ? ( void *) (*d[0]) : ( void *) (d[0])
                :                          (p[0])
                ,
                  t[1] == pcode__BOOLEAN  ? v[1] ? ( void *) (*b[1]) : ( void *) (b[1])
                : t[1] == pcode__BYTE     ? v[1] ? ( void *) (*y[1]) : ( void *) (y[1])
                : t[1] == pcode__SHORT    ? v[1] ? ( void *) (*s[1]) : ( void *) (s[1])
                : t[1] == pcode__INTEGER  ? v[1] ? ( void *) (*i[1]) : ( void *) (i[1])
                : t[1] == pcode__LONG     ? v[1] ? ( void *) (*l[1]) : ( void *) (l[1])
                : t[1] == pcode__SINGLE   ? v[1] ? ( void *) (*k[1]) : ( void *) (k[1])
                : t[1] == pcode__DOUBLE   ? v[1] ? ( void *) (*d[1]) : ( void *) (d[1])
                :                          (p[1])
                ,
                  t[2] == pcode__BOOLEAN  ? v[2] ? ( void *) (*b[2]) : ( void *) (b[2])
                : t[2] == pcode__BYTE     ? v[2] ? ( void *) (*y[2]) : ( void *) (y[2])
                : t[2] == pcode__SHORT    ? v[2] ? ( void *) (*s[2]) : ( void *) (s[2])
                : t[2] == pcode__INTEGER  ? v[2] ? ( void *) (*i[2]) : ( void *) (i[2])
                : t[2] == pcode__LONG     ? v[2] ? ( void *) (*l[2]) : ( void *) (l[2])
                : t[2] == pcode__SINGLE   ? v[2] ? ( void *) (*k[2]) : ( void *) (k[2])
                : t[2] == pcode__DOUBLE   ? v[2] ? ( void *) (*d[2]) : ( void *) (d[2])
                :                          (p[2])
                ,
                  t[3] == pcode__BOOLEAN  ? v[3] ? ( void *) (*b[3]) : ( void *) (b[3])
                : t[3] == pcode__BYTE     ? v[3] ? ( void *) (*y[3]) : ( void *) (y[3])
                : t[3] == pcode__SHORT    ? v[3] ? ( void *) (*s[3]) : ( void *) (s[3])
                : t[3] == pcode__INTEGER  ? v[3] ? ( void *) (*i[3]) : ( void *) (i[3])
                : t[3] == pcode__LONG     ? v[3] ? ( void *) (*l[3]) : ( void *) (l[3])
                : t[3] == pcode__SINGLE   ? v[3] ? ( void *) (*k[3]) : ( void *) (k[3])
                : t[3] == pcode__DOUBLE   ? v[3] ? ( void *) (*d[3]) : ( void *) (d[3])
                :                          (p[3])
                ,
                  t[4] == pcode__BOOLEAN  ? v[4] ? ( void *) (*b[4]) : ( void *) (b[4])
                : t[4] == pcode__BYTE     ? v[4] ? ( void *) (*y[4]) : ( void *) (y[4])
                : t[4] == pcode__SHORT    ? v[4] ? ( void *) (*s[4]) : ( void *) (s[4])
                : t[4] == pcode__INTEGER  ? v[4] ? ( void *) (*i[4]) : ( void *) (i[4])
                : t[4] == pcode__LONG     ? v[4] ? ( void *) (*l[4]) : ( void *) (l[4])
                : t[4] == pcode__SINGLE   ? v[4] ? ( void *) (*k[4]) : ( void *) (k[4])
                : t[4] == pcode__DOUBLE   ? v[4] ? ( void *) (*d[4]) : ( void *) (d[4])
                :                          (p[4])
              );
              else return runtimeError(utility::con(function, " function call failed. ", ll[lib]->errorString()));
              myStack->pushDouble(rd);
            }
            break;
          case 6:
            {
              double_c6 c = (double_c6) ll[lib]->resolve( function );
              if (c) rd = c (
                  t[0] == pcode__BOOLEAN  ? v[0] ? ( void *) (*b[0]) : ( void *) (b[0])
                : t[0] == pcode__BYTE     ? v[0] ? ( void *) (*y[0]) : ( void *) (y[0])
                : t[0] == pcode__SHORT    ? v[0] ? ( void *) (*s[0]) : ( void *) (s[0])
                : t[0] == pcode__INTEGER  ? v[0] ? ( void *) (*i[0]) : ( void *) (i[0])
                : t[0] == pcode__LONG     ? v[0] ? ( void *) (*l[0]) : ( void *) (l[0])
                : t[0] == pcode__SINGLE   ? v[0] ? ( void *) (*k[0]) : ( void *) (k[0])
                : t[0] == pcode__DOUBLE   ? v[0] ? ( void *) (*d[0]) : ( void *) (d[0])
                :                          (p[0])
                ,
                  t[1] == pcode__BOOLEAN  ? v[1] ? ( void *) (*b[1]) : ( void *) (b[1])
                : t[1] == pcode__BYTE     ? v[1] ? ( void *) (*y[1]) : ( void *) (y[1])
                : t[1] == pcode__SHORT    ? v[1] ? ( void *) (*s[1]) : ( void *) (s[1])
                : t[1] == pcode__INTEGER  ? v[1] ? ( void *) (*i[1]) : ( void *) (i[1])
                : t[1] == pcode__LONG     ? v[1] ? ( void *) (*l[1]) : ( void *) (l[1])
                : t[1] == pcode__SINGLE   ? v[1] ? ( void *) (*k[1]) : ( void *) (k[1])
                : t[1] == pcode__DOUBLE   ? v[1] ? ( void *) (*d[1]) : ( void *) (d[1])
                :                          (p[1])
                ,
                  t[2] == pcode__BOOLEAN  ? v[2] ? ( void *) (*b[2]) : ( void *) (b[2])
                : t[2] == pcode__BYTE     ? v[2] ? ( void *) (*y[2]) : ( void *) (y[2])
                : t[2] == pcode__SHORT    ? v[2] ? ( void *) (*s[2]) : ( void *) (s[2])
                : t[2] == pcode__INTEGER  ? v[2] ? ( void *) (*i[2]) : ( void *) (i[2])
                : t[2] == pcode__LONG     ? v[2] ? ( void *) (*l[2]) : ( void *) (l[2])
                : t[2] == pcode__SINGLE   ? v[2] ? ( void *) (*k[2]) : ( void *) (k[2])
                : t[2] == pcode__DOUBLE   ? v[2] ? ( void *) (*d[2]) : ( void *) (d[2])
                :                          (p[2])
                ,
                  t[3] == pcode__BOOLEAN  ? v[3] ? ( void *) (*b[3]) : ( void *) (b[3])
                : t[3] == pcode__BYTE     ? v[3] ? ( void *) (*y[3]) : ( void *) (y[3])
                : t[3] == pcode__SHORT    ? v[3] ? ( void *) (*s[3]) : ( void *) (s[3])
                : t[3] == pcode__INTEGER  ? v[3] ? ( void *) (*i[3]) : ( void *) (i[3])
                : t[3] == pcode__LONG     ? v[3] ? ( void *) (*l[3]) : ( void *) (l[3])
                : t[3] == pcode__SINGLE   ? v[3] ? ( void *) (*k[3]) : ( void *) (k[3])
                : t[3] == pcode__DOUBLE   ? v[3] ? ( void *) (*d[3]) : ( void *) (d[3])
                :                          (p[3])
                ,
                  t[4] == pcode__BOOLEAN  ? v[4] ? ( void *) (*b[4]) : ( void *) (b[4])
                : t[4] == pcode__BYTE     ? v[4] ? ( void *) (*y[4]) : ( void *) (y[4])
                : t[4] == pcode__SHORT    ? v[4] ? ( void *) (*s[4]) : ( void *) (s[4])
                : t[4] == pcode__INTEGER  ? v[4] ? ( void *) (*i[4]) : ( void *) (i[4])
                : t[4] == pcode__LONG     ? v[4] ? ( void *) (*l[4]) : ( void *) (l[4])
                : t[4] == pcode__SINGLE   ? v[4] ? ( void *) (*k[4]) : ( void *) (k[4])
                : t[4] == pcode__DOUBLE   ? v[4] ? ( void *) (*d[4]) : ( void *) (d[4])
                :                          (p[4])
                ,
                  t[5] == pcode__BOOLEAN  ? v[5] ? ( void *) (*b[5]) : ( void *) (b[5])
                : t[5] == pcode__BYTE     ? v[5] ? ( void *) (*y[5]) : ( void *) (y[5])
                : t[5] == pcode__SHORT    ? v[5] ? ( void *) (*s[5]) : ( void *) (s[5])
                : t[5] == pcode__INTEGER  ? v[5] ? ( void *) (*i[5]) : ( void *) (i[5])
                : t[5] == pcode__LONG     ? v[5] ? ( void *) (*l[5]) : ( void *) (l[5])
                : t[5] == pcode__SINGLE   ? v[5] ? ( void *) (*k[5]) : ( void *) (k[5])
                : t[5] == pcode__DOUBLE   ? v[5] ? ( void *) (*d[5]) : ( void *) (d[5])
                :                          (p[5])
              );
              else return runtimeError(utility::con(function, " function call failed. ", ll[lib]->errorString()));
              myStack->pushDouble(rd);
            }
            break;
          case 7:
            {
              double_c7 c = (double_c7) ll[lib]->resolve( function );
              if (c) rd = c (
                  t[0] == pcode__BOOLEAN  ? v[0] ? ( void *) (*b[0]) : ( void *) (b[0])
                : t[0] == pcode__BYTE     ? v[0] ? ( void *) (*y[0]) : ( void *) (y[0])
                : t[0] == pcode__SHORT    ? v[0] ? ( void *) (*s[0]) : ( void *) (s[0])
                : t[0] == pcode__INTEGER  ? v[0] ? ( void *) (*i[0]) : ( void *) (i[0])
                : t[0] == pcode__LONG     ? v[0] ? ( void *) (*l[0]) : ( void *) (l[0])
                : t[0] == pcode__SINGLE   ? v[0] ? ( void *) (*k[0]) : ( void *) (k[0])
                : t[0] == pcode__DOUBLE   ? v[0] ? ( void *) (*d[0]) : ( void *) (d[0])
                :                          (p[0])
                ,
                  t[1] == pcode__BOOLEAN  ? v[1] ? ( void *) (*b[1]) : ( void *) (b[1])
                : t[1] == pcode__BYTE     ? v[1] ? ( void *) (*y[1]) : ( void *) (y[1])
                : t[1] == pcode__SHORT    ? v[1] ? ( void *) (*s[1]) : ( void *) (s[1])
                : t[1] == pcode__INTEGER  ? v[1] ? ( void *) (*i[1]) : ( void *) (i[1])
                : t[1] == pcode__LONG     ? v[1] ? ( void *) (*l[1]) : ( void *) (l[1])
                : t[1] == pcode__SINGLE   ? v[1] ? ( void *) (*k[1]) : ( void *) (k[1])
                : t[1] == pcode__DOUBLE   ? v[1] ? ( void *) (*d[1]) : ( void *) (d[1])
                :                          (p[1])
                ,
                  t[2] == pcode__BOOLEAN  ? v[2] ? ( void *) (*b[2]) : ( void *) (b[2])
                : t[2] == pcode__BYTE     ? v[2] ? ( void *) (*y[2]) : ( void *) (y[2])
                : t[2] == pcode__SHORT    ? v[2] ? ( void *) (*s[2]) : ( void *) (s[2])
                : t[2] == pcode__INTEGER  ? v[2] ? ( void *) (*i[2]) : ( void *) (i[2])
                : t[2] == pcode__LONG     ? v[2] ? ( void *) (*l[2]) : ( void *) (l[2])
                : t[2] == pcode__SINGLE   ? v[2] ? ( void *) (*k[2]) : ( void *) (k[2])
                : t[2] == pcode__DOUBLE   ? v[2] ? ( void *) (*d[2]) : ( void *) (d[2])
                :                          (p[2])
                ,
                  t[3] == pcode__BOOLEAN  ? v[3] ? ( void *) (*b[3]) : ( void *) (b[3])
                : t[3] == pcode__BYTE     ? v[3] ? ( void *) (*y[3]) : ( void *) (y[3])
                : t[3] == pcode__SHORT    ? v[3] ? ( void *) (*s[3]) : ( void *) (s[3])
                : t[3] == pcode__INTEGER  ? v[3] ? ( void *) (*i[3]) : ( void *) (i[3])
                : t[3] == pcode__LONG     ? v[3] ? ( void *) (*l[3]) : ( void *) (l[3])
                : t[3] == pcode__SINGLE   ? v[3] ? ( void *) (*k[3]) : ( void *) (k[3])
                : t[3] == pcode__DOUBLE   ? v[3] ? ( void *) (*d[3]) : ( void *) (d[3])
                :                          (p[3])
                ,
                  t[4] == pcode__BOOLEAN  ? v[4] ? ( void *) (*b[4]) : ( void *) (b[4])
                : t[4] == pcode__BYTE     ? v[4] ? ( void *) (*y[4]) : ( void *) (y[4])
                : t[4] == pcode__SHORT    ? v[4] ? ( void *) (*s[4]) : ( void *) (s[4])
                : t[4] == pcode__INTEGER  ? v[4] ? ( void *) (*i[4]) : ( void *) (i[4])
                : t[4] == pcode__LONG     ? v[4] ? ( void *) (*l[4]) : ( void *) (l[4])
                : t[4] == pcode__SINGLE   ? v[4] ? ( void *) (*k[4]) : ( void *) (k[4])
                : t[4] == pcode__DOUBLE   ? v[4] ? ( void *) (*d[4]) : ( void *) (d[4])
                :                          (p[4])
                ,
                  t[5] == pcode__BOOLEAN  ? v[5] ? ( void *) (*b[5]) : ( void *) (b[5])
                : t[5] == pcode__BYTE     ? v[5] ? ( void *) (*y[5]) : ( void *) (y[5])
                : t[5] == pcode__SHORT    ? v[5] ? ( void *) (*s[5]) : ( void *) (s[5])
                : t[5] == pcode__INTEGER  ? v[5] ? ( void *) (*i[5]) : ( void *) (i[5])
                : t[5] == pcode__LONG     ? v[5] ? ( void *) (*l[5]) : ( void *) (l[5])
                : t[5] == pcode__SINGLE   ? v[5] ? ( void *) (*k[5]) : ( void *) (k[5])
                : t[5] == pcode__DOUBLE   ? v[5] ? ( void *) (*d[5]) : ( void *) (d[5])
                :                          (p[5])
                ,
                  t[6] == pcode__BOOLEAN  ? v[6] ? ( void *) (*b[6]) : ( void *) (b[6])
                : t[6] == pcode__BYTE     ? v[6] ? ( void *) (*y[6]) : ( void *) (y[6])
                : t[6] == pcode__SHORT    ? v[6] ? ( void *) (*s[6]) : ( void *) (s[6])
                : t[6] == pcode__INTEGER  ? v[6] ? ( void *) (*i[6]) : ( void *) (i[6])
                : t[6] == pcode__LONG     ? v[6] ? ( void *) (*l[6]) : ( void *) (l[6])
                : t[6] == pcode__SINGLE   ? v[6] ? ( void *) (*k[6]) : ( void *) (k[6])
                : t[6] == pcode__DOUBLE   ? v[6] ? ( void *) (*d[6]) : ( void *) (d[6])
                :                          (p[6])
              );
              else return runtimeError(utility::con(function, " function call failed. ", ll[lib]->errorString()));
              myStack->pushDouble(rd);
            }
            break;
          case 8:
            {
              double_c8 c = (double_c8) ll[lib]->resolve( function );
              if (c) rd = c (
                  t[0] == pcode__BOOLEAN  ? v[0] ? ( void *) (*b[0]) : ( void *) (b[0])
                : t[0] == pcode__BYTE     ? v[0] ? ( void *) (*y[0]) : ( void *) (y[0])
                : t[0] == pcode__SHORT    ? v[0] ? ( void *) (*s[0]) : ( void *) (s[0])
                : t[0] == pcode__INTEGER  ? v[0] ? ( void *) (*i[0]) : ( void *) (i[0])
                : t[0] == pcode__LONG     ? v[0] ? ( void *) (*l[0]) : ( void *) (l[0])
                : t[0] == pcode__SINGLE   ? v[0] ? ( void *) (*k[0]) : ( void *) (k[0])
                : t[0] == pcode__DOUBLE   ? v[0] ? ( void *) (*d[0]) : ( void *) (d[0])
                :                          (p[0])
                ,
                  t[1] == pcode__BOOLEAN  ? v[1] ? ( void *) (*b[1]) : ( void *) (b[1])
                : t[1] == pcode__BYTE     ? v[1] ? ( void *) (*y[1]) : ( void *) (y[1])
                : t[1] == pcode__SHORT    ? v[1] ? ( void *) (*s[1]) : ( void *) (s[1])
                : t[1] == pcode__INTEGER  ? v[1] ? ( void *) (*i[1]) : ( void *) (i[1])
                : t[1] == pcode__LONG     ? v[1] ? ( void *) (*l[1]) : ( void *) (l[1])
                : t[1] == pcode__SINGLE   ? v[1] ? ( void *) (*k[1]) : ( void *) (k[1])
                : t[1] == pcode__DOUBLE   ? v[1] ? ( void *) (*d[1]) : ( void *) (d[1])
                :                          (p[1])
                ,
                  t[2] == pcode__BOOLEAN  ? v[2] ? ( void *) (*b[2]) : ( void *) (b[2])
                : t[2] == pcode__BYTE     ? v[2] ? ( void *) (*y[2]) : ( void *) (y[2])
                : t[2] == pcode__SHORT    ? v[2] ? ( void *) (*s[2]) : ( void *) (s[2])
                : t[2] == pcode__INTEGER  ? v[2] ? ( void *) (*i[2]) : ( void *) (i[2])
                : t[2] == pcode__LONG     ? v[2] ? ( void *) (*l[2]) : ( void *) (l[2])
                : t[2] == pcode__SINGLE   ? v[2] ? ( void *) (*k[2]) : ( void *) (k[2])
                : t[2] == pcode__DOUBLE   ? v[2] ? ( void *) (*d[2]) : ( void *) (d[2])
                :                          (p[2])
                ,
                  t[3] == pcode__BOOLEAN  ? v[3] ? ( void *) (*b[3]) : ( void *) (b[3])
                : t[3] == pcode__BYTE     ? v[3] ? ( void *) (*y[3]) : ( void *) (y[3])
                : t[3] == pcode__SHORT    ? v[3] ? ( void *) (*s[3]) : ( void *) (s[3])
                : t[3] == pcode__INTEGER  ? v[3] ? ( void *) (*i[3]) : ( void *) (i[3])
                : t[3] == pcode__LONG     ? v[3] ? ( void *) (*l[3]) : ( void *) (l[3])
                : t[3] == pcode__SINGLE   ? v[3] ? ( void *) (*k[3]) : ( void *) (k[3])
                : t[3] == pcode__DOUBLE   ? v[3] ? ( void *) (*d[3]) : ( void *) (d[3])
                :                          (p[3])
                ,
                  t[4] == pcode__BOOLEAN  ? v[4] ? ( void *) (*b[4]) : ( void *) (b[4])
                : t[4] == pcode__BYTE     ? v[4] ? ( void *) (*y[4]) : ( void *) (y[4])
                : t[4] == pcode__SHORT    ? v[4] ? ( void *) (*s[4]) : ( void *) (s[4])
                : t[4] == pcode__INTEGER  ? v[4] ? ( void *) (*i[4]) : ( void *) (i[4])
                : t[4] == pcode__LONG     ? v[4] ? ( void *) (*l[4]) : ( void *) (l[4])
                : t[4] == pcode__SINGLE   ? v[4] ? ( void *) (*k[4]) : ( void *) (k[4])
                : t[4] == pcode__DOUBLE   ? v[4] ? ( void *) (*d[4]) : ( void *) (d[4])
                :                          (p[4])
                ,
                  t[5] == pcode__BOOLEAN  ? v[5] ? ( void *) (*b[5]) : ( void *) (b[5])
                : t[5] == pcode__BYTE     ? v[5] ? ( void *) (*y[5]) : ( void *) (y[5])
                : t[5] == pcode__SHORT    ? v[5] ? ( void *) (*s[5]) : ( void *) (s[5])
                : t[5] == pcode__INTEGER  ? v[5] ? ( void *) (*i[5]) : ( void *) (i[5])
                : t[5] == pcode__LONG     ? v[5] ? ( void *) (*l[5]) : ( void *) (l[5])
                : t[5] == pcode__SINGLE   ? v[5] ? ( void *) (*k[5]) : ( void *) (k[5])
                : t[5] == pcode__DOUBLE   ? v[5] ? ( void *) (*d[5]) : ( void *) (d[5])
                :                          (p[5])
                ,
                  t[6] == pcode__BOOLEAN  ? v[6] ? ( void *) (*b[6]) : ( void *) (b[6])
                : t[6] == pcode__BYTE     ? v[6] ? ( void *) (*y[6]) : ( void *) (y[6])
                : t[6] == pcode__SHORT    ? v[6] ? ( void *) (*s[6]) : ( void *) (s[6])
                : t[6] == pcode__INTEGER  ? v[6] ? ( void *) (*i[6]) : ( void *) (i[6])
                : t[6] == pcode__LONG     ? v[6] ? ( void *) (*l[6]) : ( void *) (l[6])
                : t[6] == pcode__SINGLE   ? v[6] ? ( void *) (*k[6]) : ( void *) (k[6])
                : t[6] == pcode__DOUBLE   ? v[6] ? ( void *) (*d[6]) : ( void *) (d[6])
                :                          (p[6])
                ,
                  t[7] == pcode__BOOLEAN  ? v[7] ? ( void *) (*b[7]) : ( void *) (b[7])
                : t[7] == pcode__BYTE     ? v[7] ? ( void *) (*y[7]) : ( void *) (y[7])
                : t[7] == pcode__SHORT    ? v[7] ? ( void *) (*s[7]) : ( void *) (s[7])
                : t[7] == pcode__INTEGER  ? v[7] ? ( void *) (*i[7]) : ( void *) (i[7])
                : t[7] == pcode__LONG     ? v[7] ? ( void *) (*l[7]) : ( void *) (l[7])
                : t[7] == pcode__SINGLE   ? v[7] ? ( void *) (*k[7]) : ( void *) (k[7])
                : t[7] == pcode__DOUBLE   ? v[7] ? ( void *) (*d[7]) : ( void *) (d[7])
                :                          (p[7])
              );
              else return runtimeError(utility::con(function, " function call failed. ", ll[lib]->errorString()));
              myStack->pushDouble(rd);
            }
            break;
          case 9:
            {
              double_c9 c = (double_c9) ll[lib]->resolve( function );
              if (c) rd = c (
                  t[0] == pcode__BOOLEAN  ? v[0] ? ( void *) (*b[0]) : ( void *) (b[0])
                : t[0] == pcode__BYTE     ? v[0] ? ( void *) (*y[0]) : ( void *) (y[0])
                : t[0] == pcode__SHORT    ? v[0] ? ( void *) (*s[0]) : ( void *) (s[0])
                : t[0] == pcode__INTEGER  ? v[0] ? ( void *) (*i[0]) : ( void *) (i[0])
                : t[0] == pcode__LONG     ? v[0] ? ( void *) (*l[0]) : ( void *) (l[0])
                : t[0] == pcode__SINGLE   ? v[0] ? ( void *) (*k[0]) : ( void *) (k[0])
                : t[0] == pcode__DOUBLE   ? v[0] ? ( void *) (*d[0]) : ( void *) (d[0])
                :                          (p[0])
                ,
                  t[1] == pcode__BOOLEAN  ? v[1] ? ( void *) (*b[1]) : ( void *) (b[1])
                : t[1] == pcode__BYTE     ? v[1] ? ( void *) (*y[1]) : ( void *) (y[1])
                : t[1] == pcode__SHORT    ? v[1] ? ( void *) (*s[1]) : ( void *) (s[1])
                : t[1] == pcode__INTEGER  ? v[1] ? ( void *) (*i[1]) : ( void *) (i[1])
                : t[1] == pcode__LONG     ? v[1] ? ( void *) (*l[1]) : ( void *) (l[1])
                : t[1] == pcode__SINGLE   ? v[1] ? ( void *) (*k[1]) : ( void *) (k[1])
                : t[1] == pcode__DOUBLE   ? v[1] ? ( void *) (*d[1]) : ( void *) (d[1])
                :                          (p[1])
                ,
                  t[2] == pcode__BOOLEAN  ? v[2] ? ( void *) (*b[2]) : ( void *) (b[2])
                : t[2] == pcode__BYTE     ? v[2] ? ( void *) (*y[2]) : ( void *) (y[2])
                : t[2] == pcode__SHORT    ? v[2] ? ( void *) (*s[2]) : ( void *) (s[2])
                : t[2] == pcode__INTEGER  ? v[2] ? ( void *) (*i[2]) : ( void *) (i[2])
                : t[2] == pcode__LONG     ? v[2] ? ( void *) (*l[2]) : ( void *) (l[2])
                : t[2] == pcode__SINGLE   ? v[2] ? ( void *) (*k[2]) : ( void *) (k[2])
                : t[2] == pcode__DOUBLE   ? v[2] ? ( void *) (*d[2]) : ( void *) (d[2])
                :                          (p[2])
                ,
                  t[3] == pcode__BOOLEAN  ? v[3] ? ( void *) (*b[3]) : ( void *) (b[3])
                : t[3] == pcode__BYTE     ? v[3] ? ( void *) (*y[3]) : ( void *) (y[3])
                : t[3] == pcode__SHORT    ? v[3] ? ( void *) (*s[3]) : ( void *) (s[3])
                : t[3] == pcode__INTEGER  ? v[3] ? ( void *) (*i[3]) : ( void *) (i[3])
                : t[3] == pcode__LONG     ? v[3] ? ( void *) (*l[3]) : ( void *) (l[3])
                : t[3] == pcode__SINGLE   ? v[3] ? ( void *) (*k[3]) : ( void *) (k[3])
                : t[3] == pcode__DOUBLE   ? v[3] ? ( void *) (*d[3]) : ( void *) (d[3])
                :                          (p[3])
                ,
                  t[4] == pcode__BOOLEAN  ? v[4] ? ( void *) (*b[4]) : ( void *) (b[4])
                : t[4] == pcode__BYTE     ? v[4] ? ( void *) (*y[4]) : ( void *) (y[4])
                : t[4] == pcode__SHORT    ? v[4] ? ( void *) (*s[4]) : ( void *) (s[4])
                : t[4] == pcode__INTEGER  ? v[4] ? ( void *) (*i[4]) : ( void *) (i[4])
                : t[4] == pcode__LONG     ? v[4] ? ( void *) (*l[4]) : ( void *) (l[4])
                : t[4] == pcode__SINGLE   ? v[4] ? ( void *) (*k[4]) : ( void *) (k[4])
                : t[4] == pcode__DOUBLE   ? v[4] ? ( void *) (*d[4]) : ( void *) (d[4])
                :                          (p[4])
                ,
                  t[5] == pcode__BOOLEAN  ? v[5] ? ( void *) (*b[5]) : ( void *) (b[5])
                : t[5] == pcode__BYTE     ? v[5] ? ( void *) (*y[5]) : ( void *) (y[5])
                : t[5] == pcode__SHORT    ? v[5] ? ( void *) (*s[5]) : ( void *) (s[5])
                : t[5] == pcode__INTEGER  ? v[5] ? ( void *) (*i[5]) : ( void *) (i[5])
                : t[5] == pcode__LONG     ? v[5] ? ( void *) (*l[5]) : ( void *) (l[5])
                : t[5] == pcode__SINGLE   ? v[5] ? ( void *) (*k[5]) : ( void *) (k[5])
                : t[5] == pcode__DOUBLE   ? v[5] ? ( void *) (*d[5]) : ( void *) (d[5])
                :                          (p[5])
                ,
                  t[6] == pcode__BOOLEAN  ? v[6] ? ( void *) (*b[6]) : ( void *) (b[6])
                : t[6] == pcode__BYTE     ? v[6] ? ( void *) (*y[6]) : ( void *) (y[6])
                : t[6] == pcode__SHORT    ? v[6] ? ( void *) (*s[6]) : ( void *) (s[6])
                : t[6] == pcode__INTEGER  ? v[6] ? ( void *) (*i[6]) : ( void *) (i[6])
                : t[6] == pcode__LONG     ? v[6] ? ( void *) (*l[6]) : ( void *) (l[6])
                : t[6] == pcode__SINGLE   ? v[6] ? ( void *) (*k[6]) : ( void *) (k[6])
                : t[6] == pcode__DOUBLE   ? v[6] ? ( void *) (*d[6]) : ( void *) (d[6])
                :                          (p[6])
                ,
                  t[7] == pcode__BOOLEAN  ? v[7] ? ( void *) (*b[7]) : ( void *) (b[7])
                : t[7] == pcode__BYTE     ? v[7] ? ( void *) (*y[7]) : ( void *) (y[7])
                : t[7] == pcode__SHORT    ? v[7] ? ( void *) (*s[7]) : ( void *) (s[7])
                : t[7] == pcode__INTEGER  ? v[7] ? ( void *) (*i[7]) : ( void *) (i[7])
                : t[7] == pcode__LONG     ? v[7] ? ( void *) (*l[7]) : ( void *) (l[7])
                : t[7] == pcode__SINGLE   ? v[7] ? ( void *) (*k[7]) : ( void *) (k[7])
                : t[7] == pcode__DOUBLE   ? v[7] ? ( void *) (*d[7]) : ( void *) (d[7])
                :                          (p[7])
                ,
                  t[8] == pcode__BOOLEAN  ? v[8] ? ( void *) (*b[8]) : ( void *) (b[8])
                : t[8] == pcode__BYTE     ? v[8] ? ( void *) (*y[8]) : ( void *) (y[8])
                : t[8] == pcode__SHORT    ? v[8] ? ( void *) (*s[8]) : ( void *) (s[8])
                : t[8] == pcode__INTEGER  ? v[8] ? ( void *) (*i[8]) : ( void *) (i[8])
                : t[8] == pcode__LONG     ? v[8] ? ( void *) (*l[8]) : ( void *) (l[8])
                : t[8] == pcode__SINGLE   ? v[8] ? ( void *) (*k[8]) : ( void *) (k[8])
                : t[8] == pcode__DOUBLE   ? v[8] ? ( void *) (*d[8]) : ( void *) (d[8])
                :                          (p[8])
              );
              else return runtimeError(utility::con(function, " function call failed. ", ll[lib]->errorString()));
              myStack->pushDouble(rd);
            }
            break;
          default:
            return runtimeError(utility::con(function, ": Too much arguments (max. 9 allowed) when calling declare function."));
            break;
         }
        break;
     }


   } else {

     switch(count){
       case 0:
         {
          void_c0 c = (void_c0) ll[lib]->resolve( function );
          if (c) c (
          );
          else return runtimeError(utility::con(function, " function call failed. ", ll[lib]->errorString()));
         }
         break;
       case 1:
         {
          void_c1 c = (void_c1) ll[lib]->resolve( function );
          if (c) c (
                  t[0] == pcode__BOOLEAN  ? v[0] ? ( void *) (*b[0]) : ( void *) (b[0])
                : t[0] == pcode__BYTE     ? v[0] ? ( void *) (*y[0]) : ( void *) (y[0])
                : t[0] == pcode__SHORT    ? v[0] ? ( void *) (*s[0]) : ( void *) (s[0])
                : t[0] == pcode__INTEGER  ? v[0] ? ( void *) (*i[0]) : ( void *) (i[0])
                : t[0] == pcode__LONG     ? v[0] ? ( void *) (*l[0]) : ( void *) (l[0])
                : t[0] == pcode__SINGLE   ? v[0] ? ( void *) (*k[0]) : ( void *) (k[0])
                : t[0] == pcode__DOUBLE   ? v[0] ? ( void *) (*d[0]) : ( void *) (d[0])
                :                          (p[0])
          );
          else return runtimeError(utility::con(function, " function call failed. ", ll[lib]->errorString()));
         }
         break;
       case 2:
         {
          void_c2 c = (void_c2) ll[lib]->resolve( function );
          if (c) c (
                  t[0] == pcode__BOOLEAN  ? v[0] ? ( void *) (*b[0]) : ( void *) (b[0])
                : t[0] == pcode__BYTE     ? v[0] ? ( void *) (*y[0]) : ( void *) (y[0])
                : t[0] == pcode__SHORT    ? v[0] ? ( void *) (*s[0]) : ( void *) (s[0])
                : t[0] == pcode__INTEGER  ? v[0] ? ( void *) (*i[0]) : ( void *) (i[0])
                : t[0] == pcode__LONG     ? v[0] ? ( void *) (*l[0]) : ( void *) (l[0])
                : t[0] == pcode__SINGLE   ? v[0] ? ( void *) (*k[0]) : ( void *) (k[0])
                : t[0] == pcode__DOUBLE   ? v[0] ? ( void *) (*d[0]) : ( void *) (d[0])
                :                          (p[0])
                ,
                  t[1] == pcode__BOOLEAN  ? v[1] ? ( void *) (*b[1]) : ( void *) (b[1])
                : t[1] == pcode__BYTE     ? v[1] ? ( void *) (*y[1]) : ( void *) (y[1])
                : t[1] == pcode__SHORT    ? v[1] ? ( void *) (*s[1]) : ( void *) (s[1])
                : t[1] == pcode__INTEGER  ? v[1] ? ( void *) (*i[1]) : ( void *) (i[1])
                : t[1] == pcode__LONG     ? v[1] ? ( void *) (*l[1]) : ( void *) (l[1])
                : t[1] == pcode__SINGLE   ? v[1] ? ( void *) (*k[1]) : ( void *) (k[1])
                : t[1] == pcode__DOUBLE   ? v[1] ? ( void *) (*d[1]) : ( void *) (d[1])
                :                          (p[1])
          );
          else return runtimeError(utility::con(function, " function call failed. ", ll[lib]->errorString()));
         }
         break;
       case 3:
         {
          void *pp = ( void *) (i[0]);
          void_c3 c = (void_c3) ll[lib]->resolve( function );
        //  char ac[1024];
          //char ac[] = ( char *) (i[0]);
          if (c) c (
                  t[0] == pcode__BOOLEAN  ? v[0] ? ( void *) (*b[0]) : ( void *) (b[0])
                : t[0] == pcode__BYTE     ? v[0] ? ( void *) (*y[0]) : ( void *) (y[0])
                : t[0] == pcode__SHORT    ? v[0] ? ( void *) (*s[0]) : ( void *) (s[0])
                : t[0] == pcode__INTEGER  ? v[0] ? ( void *) (*i[0]) : ( void *) (i[0])
                : t[0] == pcode__LONG     ? v[0] ? ( void *) (*l[0]) : ( void *) (l[0])
                : t[0] == pcode__SINGLE   ? v[0] ? ( void *) (*k[0]) : ( void *) (k[0])
                : t[0] == pcode__DOUBLE   ? v[0] ? ( void *) (*d[0]) : ( void *) (d[0])
                :                          (p[0])
                ,
                  t[1] == pcode__BOOLEAN  ? v[1] ? ( void *) (*b[1]) : ( void *) (b[1])
                : t[1] == pcode__BYTE     ? v[1] ? ( void *) (*y[1]) : ( void *) (y[1])
                : t[1] == pcode__SHORT    ? v[1] ? ( void *) (*s[1]) : ( void *) (s[1])
                : t[1] == pcode__INTEGER  ? v[1] ? ( void *) (*i[1]) : ( void *) (i[1])
                : t[1] == pcode__LONG     ? v[1] ? ( void *) (*l[1]) : ( void *) (l[1])
                : t[1] == pcode__SINGLE   ? v[1] ? ( void *) (*k[1]) : ( void *) (k[1])
                : t[1] == pcode__DOUBLE   ? v[1] ? ( void *) (*d[1]) : ( void *) (d[1])
                :                          (p[1])
                ,
                  t[2] == pcode__BOOLEAN  ? v[2] ? ( void *) (*b[2]) : ( void *) (b[2])
                : t[2] == pcode__BYTE     ? v[2] ? ( void *) (*y[2]) : ( void *) (y[2])
                : t[2] == pcode__SHORT    ? v[2] ? ( void *) (*s[2]) : ( void *) (s[2])
                : t[2] == pcode__INTEGER  ? v[2] ? ( void *) (*i[2]) : ( void *) (i[2])
                : t[2] == pcode__LONG     ? v[2] ? ( void *) (*l[2]) : ( void *) (l[2])
                : t[2] == pcode__SINGLE   ? v[2] ? ( void *) (*k[2]) : ( void *) (k[2])
                : t[2] == pcode__DOUBLE   ? v[2] ? ( void *) (*d[2]) : ( void *) (d[2])
                :                          (p[2])
          );
          else return runtimeError(utility::con(function, " function call failed. ", ll[lib]->errorString()));
        //  memcpy(&ac, ( void *) (i[0]), 20);
        //  v[0] = v[0];
/*
INPUT InputData;
  int iEvents;
  
  
  memset(&InputData, 0, sizeof(InputData));
  InputData.type = INPUT_KEYBOARD;
  InputData.ki.wVk = 72;
  InputData.ki.wScan = 0;//35;
  InputData.ki.dwFlags = 0;
  InputData.ki.time = 0;//time(NULL);
  InputData.ki.dwExtraInfo = 0;

  memcpy(&ac, &InputData, sizeof(InputData));
 
  
  iEvents = SendInput(1, &InputData, sizeof(InputData));
  iEvents = iEvents; */

         }
         break;
       case 4:
         {
          void_c4 c = (void_c4) ll[lib]->resolve( function );
          if (c) c (
                  t[0] == pcode__BOOLEAN  ? v[0] ? ( void *) (*b[0]) : ( void *) (b[0])
                : t[0] == pcode__BYTE     ? v[0] ? ( void *) (*y[0]) : ( void *) (y[0])
                : t[0] == pcode__SHORT    ? v[0] ? ( void *) (*s[0]) : ( void *) (s[0])
                : t[0] == pcode__INTEGER  ? v[0] ? ( void *) (*i[0]) : ( void *) (i[0])
                : t[0] == pcode__LONG     ? v[0] ? ( void *) (*l[0]) : ( void *) (l[0])
                : t[0] == pcode__SINGLE   ? v[0] ? ( void *) (*k[0]) : ( void *) (k[0])
                : t[0] == pcode__DOUBLE   ? v[0] ? ( void *) (*d[0]) : ( void *) (d[0])
                :                          (p[0])
                ,
                  t[1] == pcode__BOOLEAN  ? v[1] ? ( void *) (*b[1]) : ( void *) (b[1])
                : t[1] == pcode__BYTE     ? v[1] ? ( void *) (*y[1]) : ( void *) (y[1])
                : t[1] == pcode__SHORT    ? v[1] ? ( void *) (*s[1]) : ( void *) (s[1])
                : t[1] == pcode__INTEGER  ? v[1] ? ( void *) (*i[1]) : ( void *) (i[1])
                : t[1] == pcode__LONG     ? v[1] ? ( void *) (*l[1]) : ( void *) (l[1])
                : t[1] == pcode__SINGLE   ? v[1] ? ( void *) (*k[1]) : ( void *) (k[1])
                : t[1] == pcode__DOUBLE   ? v[1] ? ( void *) (*d[1]) : ( void *) (d[1])
                :                          (p[1])
                ,
                  t[2] == pcode__BOOLEAN  ? v[2] ? ( void *) (*b[2]) : ( void *) (b[2])
                : t[2] == pcode__BYTE     ? v[2] ? ( void *) (*y[2]) : ( void *) (y[2])
                : t[2] == pcode__SHORT    ? v[2] ? ( void *) (*s[2]) : ( void *) (s[2])
                : t[2] == pcode__INTEGER  ? v[2] ? ( void *) (*i[2]) : ( void *) (i[2])
                : t[2] == pcode__LONG     ? v[2] ? ( void *) (*l[2]) : ( void *) (l[2])
                : t[2] == pcode__SINGLE   ? v[2] ? ( void *) (*k[2]) : ( void *) (k[2])
                : t[2] == pcode__DOUBLE   ? v[2] ? ( void *) (*d[2]) : ( void *) (d[2])
                :                          (p[2])
                ,
                  t[3] == pcode__BOOLEAN  ? v[3] ? ( void *) (*b[3]) : ( void *) (b[3])
                : t[3] == pcode__BYTE     ? v[3] ? ( void *) (*y[3]) : ( void *) (y[3])
                : t[3] == pcode__SHORT    ? v[3] ? ( void *) (*s[3]) : ( void *) (s[3])
                : t[3] == pcode__INTEGER  ? v[3] ? ( void *) (*i[3]) : ( void *) (i[3])
                : t[3] == pcode__LONG     ? v[3] ? ( void *) (*l[3]) : ( void *) (l[3])
                : t[3] == pcode__SINGLE   ? v[3] ? ( void *) (*k[3]) : ( void *) (k[3])
                : t[3] == pcode__DOUBLE   ? v[3] ? ( void *) (*d[3]) : ( void *) (d[3])
                :                          (p[3])
          );
          else return runtimeError(utility::con(function, " function call failed. ", ll[lib]->errorString()));
         }
         break;
       case 5:
         {
          void_c5 c = (void_c5) ll[lib]->resolve( function );
          if (c) c (
                  t[0] == pcode__BOOLEAN  ? v[0] ? ( void *) (*b[0]) : ( void *) (b[0])
                : t[0] == pcode__BYTE     ? v[0] ? ( void *) (*y[0]) : ( void *) (y[0])
                : t[0] == pcode__SHORT    ? v[0] ? ( void *) (*s[0]) : ( void *) (s[0])
                : t[0] == pcode__INTEGER  ? v[0] ? ( void *) (*i[0]) : ( void *) (i[0])
                : t[0] == pcode__LONG     ? v[0] ? ( void *) (*l[0]) : ( void *) (l[0])
                : t[0] == pcode__SINGLE   ? v[0] ? ( void *) (*k[0]) : ( void *) (k[0])
                : t[0] == pcode__DOUBLE   ? v[0] ? ( void *) (*d[0]) : ( void *) (d[0])
                :                          (p[0])
                ,
                  t[1] == pcode__BOOLEAN  ? v[1] ? ( void *) (*b[1]) : ( void *) (b[1])
                : t[1] == pcode__BYTE     ? v[1] ? ( void *) (*y[1]) : ( void *) (y[1])
                : t[1] == pcode__SHORT    ? v[1] ? ( void *) (*s[1]) : ( void *) (s[1])
                : t[1] == pcode__INTEGER  ? v[1] ? ( void *) (*i[1]) : ( void *) (i[1])
                : t[1] == pcode__LONG     ? v[1] ? ( void *) (*l[1]) : ( void *) (l[1])
                : t[1] == pcode__SINGLE   ? v[1] ? ( void *) (*k[1]) : ( void *) (k[1])
                : t[1] == pcode__DOUBLE   ? v[1] ? ( void *) (*d[1]) : ( void *) (d[1])
                :                          (p[1])
                ,
                  t[2] == pcode__BOOLEAN  ? v[2] ? ( void *) (*b[2]) : ( void *) (b[2])
                : t[2] == pcode__BYTE     ? v[2] ? ( void *) (*y[2]) : ( void *) (y[2])
                : t[2] == pcode__SHORT    ? v[2] ? ( void *) (*s[2]) : ( void *) (s[2])
                : t[2] == pcode__INTEGER  ? v[2] ? ( void *) (*i[2]) : ( void *) (i[2])
                : t[2] == pcode__LONG     ? v[2] ? ( void *) (*l[2]) : ( void *) (l[2])
                : t[2] == pcode__SINGLE   ? v[2] ? ( void *) (*k[2]) : ( void *) (k[2])
                : t[2] == pcode__DOUBLE   ? v[2] ? ( void *) (*d[2]) : ( void *) (d[2])
                :                          (p[2])
                ,
                  t[3] == pcode__BOOLEAN  ? v[3] ? ( void *) (*b[3]) : ( void *) (b[3])
                : t[3] == pcode__BYTE     ? v[3] ? ( void *) (*y[3]) : ( void *) (y[3])
                : t[3] == pcode__SHORT    ? v[3] ? ( void *) (*s[3]) : ( void *) (s[3])
                : t[3] == pcode__INTEGER  ? v[3] ? ( void *) (*i[3]) : ( void *) (i[3])
                : t[3] == pcode__LONG     ? v[3] ? ( void *) (*l[3]) : ( void *) (l[3])
                : t[3] == pcode__SINGLE   ? v[3] ? ( void *) (*k[3]) : ( void *) (k[3])
                : t[3] == pcode__DOUBLE   ? v[3] ? ( void *) (*d[3]) : ( void *) (d[3])
                :                          (p[3])
                ,
                  t[4] == pcode__BOOLEAN  ? v[4] ? ( void *) (*b[4]) : ( void *) (b[4])
                : t[4] == pcode__BYTE     ? v[4] ? ( void *) (*y[4]) : ( void *) (y[4])
                : t[4] == pcode__SHORT    ? v[4] ? ( void *) (*s[4]) : ( void *) (s[4])
                : t[4] == pcode__INTEGER  ? v[4] ? ( void *) (*i[4]) : ( void *) (i[4])
                : t[4] == pcode__LONG     ? v[4] ? ( void *) (*l[4]) : ( void *) (l[4])
                : t[4] == pcode__SINGLE   ? v[4] ? ( void *) (*k[4]) : ( void *) (k[4])
                : t[4] == pcode__DOUBLE   ? v[4] ? ( void *) (*d[4]) : ( void *) (d[4])
                :                          (p[4])
          );
          else return runtimeError(utility::con(function, " function call failed. ", ll[lib]->errorString()));
         }
         break;
       case 6:
         {
          void_c6 c = (void_c6) ll[lib]->resolve( function );
          if (c) c (
                  t[0] == pcode__BOOLEAN  ? v[0] ? ( void *) (*b[0]) : ( void *) (b[0])
                : t[0] == pcode__BYTE     ? v[0] ? ( void *) (*y[0]) : ( void *) (y[0])
                : t[0] == pcode__SHORT    ? v[0] ? ( void *) (*s[0]) : ( void *) (s[0])
                : t[0] == pcode__INTEGER  ? v[0] ? ( void *) (*i[0]) : ( void *) (i[0])
                : t[0] == pcode__LONG     ? v[0] ? ( void *) (*l[0]) : ( void *) (l[0])
                : t[0] == pcode__SINGLE   ? v[0] ? ( void *) (*k[0]) : ( void *) (k[0])
                : t[0] == pcode__DOUBLE   ? v[0] ? ( void *) (*d[0]) : ( void *) (d[0])
                :                          (p[0])
                ,
                  t[1] == pcode__BOOLEAN  ? v[1] ? ( void *) (*b[1]) : ( void *) (b[1])
                : t[1] == pcode__BYTE     ? v[1] ? ( void *) (*y[1]) : ( void *) (y[1])
                : t[1] == pcode__SHORT    ? v[1] ? ( void *) (*s[1]) : ( void *) (s[1])
                : t[1] == pcode__INTEGER  ? v[1] ? ( void *) (*i[1]) : ( void *) (i[1])
                : t[1] == pcode__LONG     ? v[1] ? ( void *) (*l[1]) : ( void *) (l[1])
                : t[1] == pcode__SINGLE   ? v[1] ? ( void *) (*k[1]) : ( void *) (k[1])
                : t[1] == pcode__DOUBLE   ? v[1] ? ( void *) (*d[1]) : ( void *) (d[1])
                :                          (p[1])
                ,
                  t[2] == pcode__BOOLEAN  ? v[2] ? ( void *) (*b[2]) : ( void *) (b[2])
                : t[2] == pcode__BYTE     ? v[2] ? ( void *) (*y[2]) : ( void *) (y[2])
                : t[2] == pcode__SHORT    ? v[2] ? ( void *) (*s[2]) : ( void *) (s[2])
                : t[2] == pcode__INTEGER  ? v[2] ? ( void *) (*i[2]) : ( void *) (i[2])
                : t[2] == pcode__LONG     ? v[2] ? ( void *) (*l[2]) : ( void *) (l[2])
                : t[2] == pcode__SINGLE   ? v[2] ? ( void *) (*k[2]) : ( void *) (k[2])
                : t[2] == pcode__DOUBLE   ? v[2] ? ( void *) (*d[2]) : ( void *) (d[2])
                :                          (p[2])
                ,
                  t[3] == pcode__BOOLEAN  ? v[3] ? ( void *) (*b[3]) : ( void *) (b[3])
                : t[3] == pcode__BYTE     ? v[3] ? ( void *) (*y[3]) : ( void *) (y[3])
                : t[3] == pcode__SHORT    ? v[3] ? ( void *) (*s[3]) : ( void *) (s[3])
                : t[3] == pcode__INTEGER  ? v[3] ? ( void *) (*i[3]) : ( void *) (i[3])
                : t[3] == pcode__LONG     ? v[3] ? ( void *) (*l[3]) : ( void *) (l[3])
                : t[3] == pcode__SINGLE   ? v[3] ? ( void *) (*k[3]) : ( void *) (k[3])
                : t[3] == pcode__DOUBLE   ? v[3] ? ( void *) (*d[3]) : ( void *) (d[3])
                :                          (p[3])
                ,
                  t[4] == pcode__BOOLEAN  ? v[4] ? ( void *) (*b[4]) : ( void *) (b[4])
                : t[4] == pcode__BYTE     ? v[4] ? ( void *) (*y[4]) : ( void *) (y[4])
                : t[4] == pcode__SHORT    ? v[4] ? ( void *) (*s[4]) : ( void *) (s[4])
                : t[4] == pcode__INTEGER  ? v[4] ? ( void *) (*i[4]) : ( void *) (i[4])
                : t[4] == pcode__LONG     ? v[4] ? ( void *) (*l[4]) : ( void *) (l[4])
                : t[4] == pcode__SINGLE   ? v[4] ? ( void *) (*k[4]) : ( void *) (k[4])
                : t[4] == pcode__DOUBLE   ? v[4] ? ( void *) (*d[4]) : ( void *) (d[4])
                :                          (p[4])
                ,
                  t[5] == pcode__BOOLEAN  ? v[5] ? ( void *) (*b[5]) : ( void *) (b[5])
                : t[5] == pcode__BYTE     ? v[5] ? ( void *) (*y[5]) : ( void *) (y[5])
                : t[5] == pcode__SHORT    ? v[5] ? ( void *) (*s[5]) : ( void *) (s[5])
                : t[5] == pcode__INTEGER  ? v[5] ? ( void *) (*i[5]) : ( void *) (i[5])
                : t[5] == pcode__LONG     ? v[5] ? ( void *) (*l[5]) : ( void *) (l[5])
                : t[5] == pcode__SINGLE   ? v[5] ? ( void *) (*k[5]) : ( void *) (k[5])
                : t[5] == pcode__DOUBLE   ? v[5] ? ( void *) (*d[5]) : ( void *) (d[5])
                :                          (p[5])
          );
          else return runtimeError(utility::con(function, " function call failed. ", ll[lib]->errorString()));
         }
         break;
       case 7:
         {
          void_c7 c = (void_c7) ll[lib]->resolve( function );
          if (c) c (
                  t[0] == pcode__BOOLEAN  ? v[0] ? ( void *) (*b[0]) : ( void *) (b[0])
                : t[0] == pcode__BYTE     ? v[0] ? ( void *) (*y[0]) : ( void *) (y[0])
                : t[0] == pcode__SHORT    ? v[0] ? ( void *) (*s[0]) : ( void *) (s[0])
                : t[0] == pcode__INTEGER  ? v[0] ? ( void *) (*i[0]) : ( void *) (i[0])
                : t[0] == pcode__LONG     ? v[0] ? ( void *) (*l[0]) : ( void *) (l[0])
                : t[0] == pcode__SINGLE   ? v[0] ? ( void *) (*k[0]) : ( void *) (k[0])
                : t[0] == pcode__DOUBLE   ? v[0] ? ( void *) (*d[0]) : ( void *) (d[0])
                :                          (p[0])
                ,
                  t[1] == pcode__BOOLEAN  ? v[1] ? ( void *) (*b[1]) : ( void *) (b[1])
                : t[1] == pcode__BYTE     ? v[1] ? ( void *) (*y[1]) : ( void *) (y[1])
                : t[1] == pcode__SHORT    ? v[1] ? ( void *) (*s[1]) : ( void *) (s[1])
                : t[1] == pcode__INTEGER  ? v[1] ? ( void *) (*i[1]) : ( void *) (i[1])
                : t[1] == pcode__LONG     ? v[1] ? ( void *) (*l[1]) : ( void *) (l[1])
                : t[1] == pcode__SINGLE   ? v[1] ? ( void *) (*k[1]) : ( void *) (k[1])
                : t[1] == pcode__DOUBLE   ? v[1] ? ( void *) (*d[1]) : ( void *) (d[1])
                :                          (p[1])
                ,
                  t[2] == pcode__BOOLEAN  ? v[2] ? ( void *) (*b[2]) : ( void *) (b[2])
                : t[2] == pcode__BYTE     ? v[2] ? ( void *) (*y[2]) : ( void *) (y[2])
                : t[2] == pcode__SHORT    ? v[2] ? ( void *) (*s[2]) : ( void *) (s[2])
                : t[2] == pcode__INTEGER  ? v[2] ? ( void *) (*i[2]) : ( void *) (i[2])
                : t[2] == pcode__LONG     ? v[2] ? ( void *) (*l[2]) : ( void *) (l[2])
                : t[2] == pcode__SINGLE   ? v[2] ? ( void *) (*k[2]) : ( void *) (k[2])
                : t[2] == pcode__DOUBLE   ? v[2] ? ( void *) (*d[2]) : ( void *) (d[2])
                :                          (p[2])
                ,
                  t[3] == pcode__BOOLEAN  ? v[3] ? ( void *) (*b[3]) : ( void *) (b[3])
                : t[3] == pcode__BYTE     ? v[3] ? ( void *) (*y[3]) : ( void *) (y[3])
                : t[3] == pcode__SHORT    ? v[3] ? ( void *) (*s[3]) : ( void *) (s[3])
                : t[3] == pcode__INTEGER  ? v[3] ? ( void *) (*i[3]) : ( void *) (i[3])
                : t[3] == pcode__LONG     ? v[3] ? ( void *) (*l[3]) : ( void *) (l[3])
                : t[3] == pcode__SINGLE   ? v[3] ? ( void *) (*k[3]) : ( void *) (k[3])
                : t[3] == pcode__DOUBLE   ? v[3] ? ( void *) (*d[3]) : ( void *) (d[3])
                :                          (p[3])
                ,
                  t[4] == pcode__BOOLEAN  ? v[4] ? ( void *) (*b[4]) : ( void *) (b[4])
                : t[4] == pcode__BYTE     ? v[4] ? ( void *) (*y[4]) : ( void *) (y[4])
                : t[4] == pcode__SHORT    ? v[4] ? ( void *) (*s[4]) : ( void *) (s[4])
                : t[4] == pcode__INTEGER  ? v[4] ? ( void *) (*i[4]) : ( void *) (i[4])
                : t[4] == pcode__LONG     ? v[4] ? ( void *) (*l[4]) : ( void *) (l[4])
                : t[4] == pcode__SINGLE   ? v[4] ? ( void *) (*k[4]) : ( void *) (k[4])
                : t[4] == pcode__DOUBLE   ? v[4] ? ( void *) (*d[4]) : ( void *) (d[4])
                :                          (p[4])
                ,
                  t[5] == pcode__BOOLEAN  ? v[5] ? ( void *) (*b[5]) : ( void *) (b[5])
                : t[5] == pcode__BYTE     ? v[5] ? ( void *) (*y[5]) : ( void *) (y[5])
                : t[5] == pcode__SHORT    ? v[5] ? ( void *) (*s[5]) : ( void *) (s[5])
                : t[5] == pcode__INTEGER  ? v[5] ? ( void *) (*i[5]) : ( void *) (i[5])
                : t[5] == pcode__LONG     ? v[5] ? ( void *) (*l[5]) : ( void *) (l[5])
                : t[5] == pcode__SINGLE   ? v[5] ? ( void *) (*k[5]) : ( void *) (k[5])
                : t[5] == pcode__DOUBLE   ? v[5] ? ( void *) (*d[5]) : ( void *) (d[5])
                :                          (p[5])
                ,
                  t[6] == pcode__BOOLEAN  ? v[6] ? ( void *) (*b[6]) : ( void *) (b[6])
                : t[6] == pcode__BYTE     ? v[6] ? ( void *) (*y[6]) : ( void *) (y[6])
                : t[6] == pcode__SHORT    ? v[6] ? ( void *) (*s[6]) : ( void *) (s[6])
                : t[6] == pcode__INTEGER  ? v[6] ? ( void *) (*i[6]) : ( void *) (i[6])
                : t[6] == pcode__LONG     ? v[6] ? ( void *) (*l[6]) : ( void *) (l[6])
                : t[6] == pcode__SINGLE   ? v[6] ? ( void *) (*k[6]) : ( void *) (k[6])
                : t[6] == pcode__DOUBLE   ? v[6] ? ( void *) (*d[6]) : ( void *) (d[6])
                :                          (p[6])
          );
          else return runtimeError(utility::con(function, " function call failed. ", ll[lib]->errorString()));
         }
         break;
       case 8:
         {
          void_c8 c = (void_c8) ll[lib]->resolve( function );
          if (c) c (
                  t[0] == pcode__BOOLEAN  ? v[0] ? ( void *) (*b[0]) : ( void *) (b[0])
                : t[0] == pcode__BYTE     ? v[0] ? ( void *) (*y[0]) : ( void *) (y[0])
                : t[0] == pcode__SHORT    ? v[0] ? ( void *) (*s[0]) : ( void *) (s[0])
                : t[0] == pcode__INTEGER  ? v[0] ? ( void *) (*i[0]) : ( void *) (i[0])
                : t[0] == pcode__LONG     ? v[0] ? ( void *) (*l[0]) : ( void *) (l[0])
                : t[0] == pcode__SINGLE   ? v[0] ? ( void *) (*k[0]) : ( void *) (k[0])
                : t[0] == pcode__DOUBLE   ? v[0] ? ( void *) (*d[0]) : ( void *) (d[0])
                :                          (p[0])
                ,
                  t[1] == pcode__BOOLEAN  ? v[1] ? ( void *) (*b[1]) : ( void *) (b[1])
                : t[1] == pcode__BYTE     ? v[1] ? ( void *) (*y[1]) : ( void *) (y[1])
                : t[1] == pcode__SHORT    ? v[1] ? ( void *) (*s[1]) : ( void *) (s[1])
                : t[1] == pcode__INTEGER  ? v[1] ? ( void *) (*i[1]) : ( void *) (i[1])
                : t[1] == pcode__LONG     ? v[1] ? ( void *) (*l[1]) : ( void *) (l[1])
                : t[1] == pcode__SINGLE   ? v[1] ? ( void *) (*k[1]) : ( void *) (k[1])
                : t[1] == pcode__DOUBLE   ? v[1] ? ( void *) (*d[1]) : ( void *) (d[1])
                :                          (p[1])
                ,
                  t[2] == pcode__BOOLEAN  ? v[2] ? ( void *) (*b[2]) : ( void *) (b[2])
                : t[2] == pcode__BYTE     ? v[2] ? ( void *) (*y[2]) : ( void *) (y[2])
                : t[2] == pcode__SHORT    ? v[2] ? ( void *) (*s[2]) : ( void *) (s[2])
                : t[2] == pcode__INTEGER  ? v[2] ? ( void *) (*i[2]) : ( void *) (i[2])
                : t[2] == pcode__LONG     ? v[2] ? ( void *) (*l[2]) : ( void *) (l[2])
                : t[2] == pcode__SINGLE   ? v[2] ? ( void *) (*k[2]) : ( void *) (k[2])
                : t[2] == pcode__DOUBLE   ? v[2] ? ( void *) (*d[2]) : ( void *) (d[2])
                :                          (p[2])
                ,
                  t[3] == pcode__BOOLEAN  ? v[3] ? ( void *) (*b[3]) : ( void *) (b[3])
                : t[3] == pcode__BYTE     ? v[3] ? ( void *) (*y[3]) : ( void *) (y[3])
                : t[3] == pcode__SHORT    ? v[3] ? ( void *) (*s[3]) : ( void *) (s[3])
                : t[3] == pcode__INTEGER  ? v[3] ? ( void *) (*i[3]) : ( void *) (i[3])
                : t[3] == pcode__LONG     ? v[3] ? ( void *) (*l[3]) : ( void *) (l[3])
                : t[3] == pcode__SINGLE   ? v[3] ? ( void *) (*k[3]) : ( void *) (k[3])
                : t[3] == pcode__DOUBLE   ? v[3] ? ( void *) (*d[3]) : ( void *) (d[3])
                :                          (p[3])
                ,
                  t[4] == pcode__BOOLEAN  ? v[4] ? ( void *) (*b[4]) : ( void *) (b[4])
                : t[4] == pcode__BYTE     ? v[4] ? ( void *) (*y[4]) : ( void *) (y[4])
                : t[4] == pcode__SHORT    ? v[4] ? ( void *) (*s[4]) : ( void *) (s[4])
                : t[4] == pcode__INTEGER  ? v[4] ? ( void *) (*i[4]) : ( void *) (i[4])
                : t[4] == pcode__LONG     ? v[4] ? ( void *) (*l[4]) : ( void *) (l[4])
                : t[4] == pcode__SINGLE   ? v[4] ? ( void *) (*k[4]) : ( void *) (k[4])
                : t[4] == pcode__DOUBLE   ? v[4] ? ( void *) (*d[4]) : ( void *) (d[4])
                :                          (p[4])
                ,
                  t[5] == pcode__BOOLEAN  ? v[5] ? ( void *) (*b[5]) : ( void *) (b[5])
                : t[5] == pcode__BYTE     ? v[5] ? ( void *) (*y[5]) : ( void *) (y[5])
                : t[5] == pcode__SHORT    ? v[5] ? ( void *) (*s[5]) : ( void *) (s[5])
                : t[5] == pcode__INTEGER  ? v[5] ? ( void *) (*i[5]) : ( void *) (i[5])
                : t[5] == pcode__LONG     ? v[5] ? ( void *) (*l[5]) : ( void *) (l[5])
                : t[5] == pcode__SINGLE   ? v[5] ? ( void *) (*k[5]) : ( void *) (k[5])
                : t[5] == pcode__DOUBLE   ? v[5] ? ( void *) (*d[5]) : ( void *) (d[5])
                :                          (p[5])
                ,
                  t[6] == pcode__BOOLEAN  ? v[6] ? ( void *) (*b[6]) : ( void *) (b[6])
                : t[6] == pcode__BYTE     ? v[6] ? ( void *) (*y[6]) : ( void *) (y[6])
                : t[6] == pcode__SHORT    ? v[6] ? ( void *) (*s[6]) : ( void *) (s[6])
                : t[6] == pcode__INTEGER  ? v[6] ? ( void *) (*i[6]) : ( void *) (i[6])
                : t[6] == pcode__LONG     ? v[6] ? ( void *) (*l[6]) : ( void *) (l[6])
                : t[6] == pcode__SINGLE   ? v[6] ? ( void *) (*k[6]) : ( void *) (k[6])
                : t[6] == pcode__DOUBLE   ? v[6] ? ( void *) (*d[6]) : ( void *) (d[6])
                :                          (p[6])
                ,
                  t[7] == pcode__BOOLEAN  ? v[7] ? ( void *) (*b[7]) : ( void *) (b[7])
                : t[7] == pcode__BYTE     ? v[7] ? ( void *) (*y[7]) : ( void *) (y[7])
                : t[7] == pcode__SHORT    ? v[7] ? ( void *) (*s[7]) : ( void *) (s[7])
                : t[7] == pcode__INTEGER  ? v[7] ? ( void *) (*i[7]) : ( void *) (i[7])
                : t[7] == pcode__LONG     ? v[7] ? ( void *) (*l[7]) : ( void *) (l[7])
                : t[7] == pcode__SINGLE   ? v[7] ? ( void *) (*k[7]) : ( void *) (k[7])
                : t[7] == pcode__DOUBLE   ? v[7] ? ( void *) (*d[7]) : ( void *) (d[7])
                :                          (p[7])
          );
          else return runtimeError(utility::con(function, " function call failed. ", ll[lib]->errorString()));
         }
         break;
       case 9:
         {
          void_c9 c = (void_c9) ll[lib]->resolve( function );
          if (c) c (
                  t[0] == pcode__BOOLEAN  ? v[0] ? ( void *) (*b[0]) : ( void *) (b[0])
                : t[0] == pcode__BYTE     ? v[0] ? ( void *) (*y[0]) : ( void *) (y[0])
                : t[0] == pcode__SHORT    ? v[0] ? ( void *) (*s[0]) : ( void *) (s[0])
                : t[0] == pcode__INTEGER  ? v[0] ? ( void *) (*i[0]) : ( void *) (i[0])
                : t[0] == pcode__LONG     ? v[0] ? ( void *) (*l[0]) : ( void *) (l[0])
                : t[0] == pcode__SINGLE   ? v[0] ? ( void *) (*k[0]) : ( void *) (k[0])
                : t[0] == pcode__DOUBLE   ? v[0] ? ( void *) (*d[0]) : ( void *) (d[0])
                :                          (p[0])
                ,
                  t[1] == pcode__BOOLEAN  ? v[1] ? ( void *) (*b[1]) : ( void *) (b[1])
                : t[1] == pcode__BYTE     ? v[1] ? ( void *) (*y[1]) : ( void *) (y[1])
                : t[1] == pcode__SHORT    ? v[1] ? ( void *) (*s[1]) : ( void *) (s[1])
                : t[1] == pcode__INTEGER  ? v[1] ? ( void *) (*i[1]) : ( void *) (i[1])
                : t[1] == pcode__LONG     ? v[1] ? ( void *) (*l[1]) : ( void *) (l[1])
                : t[1] == pcode__SINGLE   ? v[1] ? ( void *) (*k[1]) : ( void *) (k[1])
                : t[1] == pcode__DOUBLE   ? v[1] ? ( void *) (*d[1]) : ( void *) (d[1])
                :                          (p[1])
                ,
                  t[2] == pcode__BOOLEAN  ? v[2] ? ( void *) (*b[2]) : ( void *) (b[2])
                : t[2] == pcode__BYTE     ? v[2] ? ( void *) (*y[2]) : ( void *) (y[2])
                : t[2] == pcode__SHORT    ? v[2] ? ( void *) (*s[2]) : ( void *) (s[2])
                : t[2] == pcode__INTEGER  ? v[2] ? ( void *) (*i[2]) : ( void *) (i[2])
                : t[2] == pcode__LONG     ? v[2] ? ( void *) (*l[2]) : ( void *) (l[2])
                : t[2] == pcode__SINGLE   ? v[2] ? ( void *) (*k[2]) : ( void *) (k[2])
                : t[2] == pcode__DOUBLE   ? v[2] ? ( void *) (*d[2]) : ( void *) (d[2])
                :                          (p[2])
                ,
                  t[3] == pcode__BOOLEAN  ? v[3] ? ( void *) (*b[3]) : ( void *) (b[3])
                : t[3] == pcode__BYTE     ? v[3] ? ( void *) (*y[3]) : ( void *) (y[3])
                : t[3] == pcode__SHORT    ? v[3] ? ( void *) (*s[3]) : ( void *) (s[3])
                : t[3] == pcode__INTEGER  ? v[3] ? ( void *) (*i[3]) : ( void *) (i[3])
                : t[3] == pcode__LONG     ? v[3] ? ( void *) (*l[3]) : ( void *) (l[3])
                : t[3] == pcode__SINGLE   ? v[3] ? ( void *) (*k[3]) : ( void *) (k[3])
                : t[3] == pcode__DOUBLE   ? v[3] ? ( void *) (*d[3]) : ( void *) (d[3])
                :                          (p[3])
                ,
                  t[4] == pcode__BOOLEAN  ? v[4] ? ( void *) (*b[4]) : ( void *) (b[4])
                : t[4] == pcode__BYTE     ? v[4] ? ( void *) (*y[4]) : ( void *) (y[4])
                : t[4] == pcode__SHORT    ? v[4] ? ( void *) (*s[4]) : ( void *) (s[4])
                : t[4] == pcode__INTEGER  ? v[4] ? ( void *) (*i[4]) : ( void *) (i[4])
                : t[4] == pcode__LONG     ? v[4] ? ( void *) (*l[4]) : ( void *) (l[4])
                : t[4] == pcode__SINGLE   ? v[4] ? ( void *) (*k[4]) : ( void *) (k[4])
                : t[4] == pcode__DOUBLE   ? v[4] ? ( void *) (*d[4]) : ( void *) (d[4])
                :                          (p[4])
                ,
                  t[5] == pcode__BOOLEAN  ? v[5] ? ( void *) (*b[5]) : ( void *) (b[5])
                : t[5] == pcode__BYTE     ? v[5] ? ( void *) (*y[5]) : ( void *) (y[5])
                : t[5] == pcode__SHORT    ? v[5] ? ( void *) (*s[5]) : ( void *) (s[5])
                : t[5] == pcode__INTEGER  ? v[5] ? ( void *) (*i[5]) : ( void *) (i[5])
                : t[5] == pcode__LONG     ? v[5] ? ( void *) (*l[5]) : ( void *) (l[5])
                : t[5] == pcode__SINGLE   ? v[5] ? ( void *) (*k[5]) : ( void *) (k[5])
                : t[5] == pcode__DOUBLE   ? v[5] ? ( void *) (*d[5]) : ( void *) (d[5])
                :                          (p[5])
                ,
                  t[6] == pcode__BOOLEAN  ? v[6] ? ( void *) (*b[6]) : ( void *) (b[6])
                : t[6] == pcode__BYTE     ? v[6] ? ( void *) (*y[6]) : ( void *) (y[6])
                : t[6] == pcode__SHORT    ? v[6] ? ( void *) (*s[6]) : ( void *) (s[6])
                : t[6] == pcode__INTEGER  ? v[6] ? ( void *) (*i[6]) : ( void *) (i[6])
                : t[6] == pcode__LONG     ? v[6] ? ( void *) (*l[6]) : ( void *) (l[6])
                : t[6] == pcode__SINGLE   ? v[6] ? ( void *) (*k[6]) : ( void *) (k[6])
                : t[6] == pcode__DOUBLE   ? v[6] ? ( void *) (*d[6]) : ( void *) (d[6])
                :                          (p[6])
                ,
                  t[7] == pcode__BOOLEAN  ? v[7] ? ( void *) (*b[7]) : ( void *) (b[7])
                : t[7] == pcode__BYTE     ? v[7] ? ( void *) (*y[7]) : ( void *) (y[7])
                : t[7] == pcode__SHORT    ? v[7] ? ( void *) (*s[7]) : ( void *) (s[7])
                : t[7] == pcode__INTEGER  ? v[7] ? ( void *) (*i[7]) : ( void *) (i[7])
                : t[7] == pcode__LONG     ? v[7] ? ( void *) (*l[7]) : ( void *) (l[7])
                : t[7] == pcode__SINGLE   ? v[7] ? ( void *) (*k[7]) : ( void *) (k[7])
                : t[7] == pcode__DOUBLE   ? v[7] ? ( void *) (*d[7]) : ( void *) (d[7])
                :                          (p[7])
                ,
                  t[8] == pcode__BOOLEAN  ? v[8] ? ( void *) (*b[8]) : ( void *) (b[8])
                : t[8] == pcode__BYTE     ? v[8] ? ( void *) (*y[8]) : ( void *) (y[8])
                : t[8] == pcode__SHORT    ? v[8] ? ( void *) (*s[8]) : ( void *) (s[8])
                : t[8] == pcode__INTEGER  ? v[8] ? ( void *) (*i[8]) : ( void *) (i[8])
                : t[8] == pcode__LONG     ? v[8] ? ( void *) (*l[8]) : ( void *) (l[8])
                : t[8] == pcode__SINGLE   ? v[8] ? ( void *) (*k[8]) : ( void *) (k[8])
                : t[8] == pcode__DOUBLE   ? v[8] ? ( void *) (*d[8]) : ( void *) (d[8])
                :                          (p[8])
          );
          else return runtimeError(utility::con(function, " function call failed. ", ll[lib]->errorString()));
         }
         break;
       default:
         return runtimeError(utility::con(function, ": Too much arguments (max. 9 allowed) when calling declare function."));
         break;
     }
   }
//#endif
   exitLocal();
   return true;
}



bool interpreter::EVENT_OnPaint(memory_variable2 *v3, int identifier2, const char *name, const char *group, QWidget *W, t_integer X, t_integer Y, t_integer Width, t_integer Height)
{ 
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif



  sub *s = 0;

  {
    

    { 

      int nClassId = v3->getClassId();

      s = myClass->getSub(nClassId, "Form_OnPaint");

      if (s == 0){
         return false;

      }
    }

#ifdef HAS_CONSOLE
    if (!bSilent){
		 // info("EVENT2", ss.toAscii());
    }
#endif

    memory_variable2 *oldMeVars = meVars; 
    
    meVars = v3; 
    int nClassId = meVars->getClassId();

    int m = myPcode->getPos();
    myPcode->setPos(s->pc_pos);

    QPainter p(W); EXTERN_myQPainter = &p;		

    enterLocal("");

    
    local_frame_ *l = myLocalFrame.last();
    l->subPcodeOffset = s->pc_pos;
    l->onErrorGotoPos = 0;
    l->return_pos = 0;  // wird bei classes nicht benutzt
    

    memory_variable2 *vv = getVar(param);

    

    vv->declare(class_bindingparam["Form1Form_OnPaint001530022500022500022500022503"], Height);
    vv->declare(class_bindingparam["Form1Form_OnPaint001530022500022500022500022502"], Width);
    vv->declare(class_bindingparam["Form1Form_OnPaint001530022500022500022500022501"], Y);
    vv->declare(class_bindingparam["Form1Form_OnPaint001530022500022500022500022503"], X);


    interpret2(true, false, myClass->getPcodeLenMethod(nClassId, s));

    exitLocal();

    EXTERN_myQPainter = 0;

    

    meVars = oldMeVars; 
    myPcode->setPos(m);

  }
  return true;
}