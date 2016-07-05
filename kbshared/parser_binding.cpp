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


#include "parser.h"
#include "../kbshared/pcode.h"

extern char ac[1024];

bool parser::registerBindingTypes()
{
	
	// qt_binding
//  #include "parser_binding_qt_binding.h"

  // kbasic binding
  #include "parser_binding_kbasic_binding.h"

// kbasic binding
/*
registerBinding("scanner", pcode__scanner);
registerBinding("parser", pcode__parser);
registerBinding("interpreter", pcode__interpreter);
registerBinding("pcode", pcode__pcode);
registerBinding("token", pcode__token);
*/


  return true;
}


bool parser::binding_createMapClass()
{/*
  int i = pcode__qt_binding_class + 1;

	//const char *acLast;
  const char *acPattern;

//  binding_map_class.setAutoDelete(false);

	while (true){
		acPattern = pcode_qt_binding::classname_(i);
		if (strcmp(acPattern, "") == 0) break;
		//acLast = acPattern;
    
    //printf("%s ", acPattern);

    binding_map_class.addString(acPattern, i++); 

  }
*/
  const char *acPattern;
  int i = pcode__kbasic_binding_class + 1;

	while (true){
		acPattern = pcode_kbasic_binding::classname_(i);
    if (strcmp(acPattern, "") == 0){
      break;
    }
		//acLast = acPattern;

    binding_map_class.addString(acPattern, i++); 

  }
  
  return true;
  
}

bool parser::binding_createMapMethod()
{
  /*
  int i = pcode__qt_binding_method + 1;

//  binding_map_method.setAutoDelete(false);

	//const char *acLast;
	while (true){
		const char *acPattern = pcode_qt_binding::methodname_(i);
		if (strcmp(acPattern, "") == 0) break;
		//acLast = acPattern;

    binding_map_method.addString(acPattern, i++);    

  }
*/
  const char *acPattern;
  int i = pcode__kbasic_binding_method + 1;

	while (true){
		const char *acPattern = pcode_kbasic_binding::methodname_(i);
		if (strcmp(acPattern, "") == 0) break;
		//acLast = acPattern;

    binding_map_method.addString(acPattern, i++);    

  }
  
  return true;
  
}




// ************************************************************************************
// ************************************************************************************
// ************************************************************************************



bool parser_classMethod::setNamespace(int p1)
{
  nNamespace = p1;
	return true;
}

bool parser_classMethod::new_class(int p1, int p2, int p3, bool bAbstract)
{
  if (myParser_class.contains(p1)){ // important! could be when unfinished binding object files are included which addresses the same class id
    return true;
  }

  parser_class2 *p = new parser_class2(p2, p3, p1, bAbstract);
	myParser_class.set(p1, (int) p);
  
  p = ((parser_class2 *) myParser_class.get(p1));
  p->nNamespace = nNamespace;


  if (p3 != 0){
    p3 = p3;
    /*

    new_class(pcode__QTextEdit, pcode__QScrollView, pcode__QObject); 
    new_class(pcode__QXmlDefaultHandler, pcode__QXmlContentHandler, pcode__QXmlErrorHandler); 
    new_class(pcode__QPopupMenu, pcode__QFrame, pcode__QMenuData); 
    new_class(pcode__QSlider, pcode__QWidget, pcode__QRangeControl); 
    new_class(pcode__QSocket, pcode__QObject, pcode__QIODevice); 
    new_class(pcode__QSpinBox, pcode__QWidget, pcode__QRangeControl); 
    new_class(pcode__QSqlCursor, pcode__QSqlRecord, pcode__QSqlQuery); 
    new_class(pcode__QMenuBar, pcode__QFrame, pcode__QMenuData); 
    new_class(pcode__QGLWidget, pcode__QWidget, pcode__QGL); 
    new_class(pcode__QWidget, pcode__QObject, pcode__QPaintDevice); 
    new_class(pcode__QFrame, pcode__QWidget, pcode__QObject); 
    new_class(pcode__QObject, pcode__Qt, pcode__QPaintDevice); 
    new_class(pcode__QApplication, pcode__QObject, pcode__QObject); 
    new_class(pcode__QLayout, pcode__QObject, pcode__QLayoutItem); 
    */
  }

  /*
  if (pp_list == 0){
    pp_list = new XIntVector;
    pp_list->setAutoDelete(true);  
  }
  */
	return true;
}

bool parser_classMethod::new_param(char *p1, int p2, bool p3)
{	
  ///**/return true;
  pp_list->add(new parser_parameter(p1, p2, p3)); return true; 
}
bool parser_classMethod::new_param(char *p1, int p2, bool p3, bool p4)
{	
  ///**/return true;
  pp_list->add(new parser_parameter(p1, p2, p3, p4)); return true; 
}
bool parser_classMethod::new_param(char *p1, int p2, bool p3, float p4)
{	
  ///**/return true;
  pp_list->add(new parser_parameter(p1, p2, p3, p4)); 
  return true; 
}
bool parser_classMethod::new_param(char *p1, int p2, bool p3, double p4){	
  ///**/return true;
  pp_list->add(new parser_parameter(p1, p2, p3, p4)); return true; 
}
bool parser_classMethod::new_param(char *p1, int p2, bool p3, int p4)
{	
  ///**/return true;
  pp_list->add(new parser_parameter(p1, p2, p3, p4)); return true; }
bool parser_classMethod::new_param(char *p1, int p2, bool p3, long p4)
{	
  ///**/return true;
  pp_list->add(new parser_parameter(p1, p2, p3, p4)); return true; }
bool parser_classMethod::new_param(char *p1, int p2, bool p3, const char *p4)
{	
  ///**/return true;
  pp_list->add(new parser_parameter(p1, p2, p3, p4)); return true; }


bool parser_classMethod::new_const(int p1, int p2)
{
  XString s = pcode::pcode_(p2); s = s.upper();

  if (myParser_class.contains(p1) && ((parser_class2 *)myParser_class.get(p1))->myParser_const.contains(s.ascii())){
    return false;
	}

  ((parser_class2 *) myParser_class.get(p1))->myParser_const.addString(s.ascii(), (int) p2);

	return true;
}

bool parser_classMethod::new_method(bool bSupported, int p1, int p2, int p3, bool bSignal, bool bSlot, bool bStatic, bool bEvent)
{
///**/return true;
  XString s = pcode::pcode_(p2); s = s.upper();
	//char ac[1024];
/*
  if (p1 == pcode___form){
    p1 = p1;
  }*/

	//sprintf(ac, "%s", pcode::pcode_(p2));

	int i = 0;
  while (myParser_class.contains(p1) && ((parser_class2 *)myParser_class.get(p1))->myParser_method.contains(s.ascii())){
			
		i++;

		sprintf(ac, "%s%d", pcode::pcode_(p2), i);
    //s.format("%s%d", pcode::pcode_(p2), i); 
    s = ac;
    s = s.upper();

	}

  ((parser_class2 *) myParser_class.get(p1))->myParser_method.addString(s.ascii(), (int) new parser_method(bSupported, p2, p3, pp_list, bSignal, bSlot, bStatic, bEvent));
  /*
  ((parser_class2 *) myParser_class.get(p1))->myParser_method[ac]->bSignal = bSignal;
  ((parser_class2 *) myParser_class.get(p1))->myParser_method[ac]->bSlot = bSlot;
  ((parser_class2 *) myParser_class.get(p1))->myParser_method[ac]->bStatic = bStatic;
*/
  pp_list = new XIntVector();//st d::li st<parser_parameter*>;
  pp_list->setAutoDelete(true);
	return true;
}

bool parser_classMethod::new_property_get(int p1, int p2, int p3)
{
  ///**/return true;
  XString s = pcode::pcode_(p2); s = s.upper();
	//char ac[1024];

  if (p1 == 1171){
    p1 = p1;
  }

	//sprintf(ac, "%s", pcode::pcode_(p2));

	int i = 0;
  while (((parser_class2 *) myParser_class.get(p1))->myParser_property_get.contains(s.ascii())){		
		
		i++;
		sprintf(ac, "%s%d", pcode::pcode_(p2), i);
    //s.format("%s%d", pcode::pcode_(p2), i); 
    s = ac;
    s = s.upper();


	}

	((parser_class2 *) myParser_class.get(p1))->myParser_property_get.addString(s.ascii(), (int) new parser_method(true, p2, p3, pp_list, false, false, false, false));

  pp_list = new XIntVector();//st d::li st<parser_parameter*>;
  pp_list->setAutoDelete(true);
	return true;
}

bool parser_classMethod::new_property_set(int p1, int p2, int p3)
{
  ///**/return true;
  XString s = pcode::pcode_(p2); s = s.upper();
	//char ac[1024];

  if (p1 == 1171){
    p1 = p1;
  }

	//sprintf(ac, "%s", pcode::pcode_(p2));

	int i = 0;
	while (((parser_class2 *) myParser_class.get(p1))->myParser_property_set.contains(s.ascii())){		
		
		i++;
		sprintf(ac, "%s%d", pcode::pcode_(p2), i);
    //s.format("%s%d", pcode::pcode_(p2), i); 
    s = ac;
    s = s.upper();

	}

	((parser_class2 *) myParser_class.get(p1))->myParser_property_set.addString(s.ascii(), (int) new parser_method(true, p2, p3, pp_list, false, false, false, false));

  pp_list = new XIntVector();//st d::lis t<parser_parameter*>;
  pp_list->setAutoDelete(true);
	return true;
}

bool parser_classMethod::new_staticproperty_get(int p1, int p2, int p3)
{
  ///**/return true;
  XString s = pcode::pcode_(p2); s = s.upper();
	//char ac[1024];

  if (p1 == 1171){
    p1 = p1;
  }

	//sprintf(ac, "%s", pcode::pcode_(p2));

	int i = 0;
  while (((parser_class2 *) myParser_class.get(p1))->myParser_staticproperty_get.contains(s.ascii())){		
		
		i++;
		sprintf(ac, "%s%d", pcode::pcode_(p2), i);
    //s.format("%s%d", pcode::pcode_(p2), i); 
    s = ac;
    s = s.upper();


	}

	((parser_class2 *) myParser_class.get(p1))->myParser_staticproperty_get.addString(s.ascii(), (int) new parser_method(true, p2, p3, pp_list, false, false, false, false));

  pp_list = new XIntVector();//st d::li st<parser_parameter*>;
  pp_list->setAutoDelete(true);
	return true;
}

bool parser_classMethod::new_staticproperty_set(int p1, int p2, int p3)
{
  ///**/return true;
  XString s = pcode::pcode_(p2); s = s.upper();
	//char ac[1024];

  if (p1 == 1171){
    p1 = p1;
  }

	//sprintf(ac, "%s", pcode::pcode_(p2));

	int i = 0;
	while (((parser_class2 *) myParser_class.get(p1))->myParser_staticproperty_set.contains(s.ascii())){		
		
		i++;
		sprintf(ac, "%s%d", pcode::pcode_(p2), i);
    //s.format("%s%d", pcode::pcode_(p2), i); 
    s = ac;
    s = s.upper();

	}

	((parser_class2 *) myParser_class.get(p1))->myParser_staticproperty_set.addString(s.ascii(), (int) new parser_method(true, p2, p3, pp_list, false, false, false, false));

  pp_list = new XIntVector();//st d::lis t<parser_parameter*>;
  pp_list->setAutoDelete(true);
	return true;
}

/*
bool parser_classMethod::new_function(bool bSupported, int p1, int p2)
{
  //return true;

  XString s = pcode::pcode_(p2); s = s.upper();
	//char ac[1024];

	//sprintf(ac, "%s", pcode::pcode_(p2));

  // pseudo-class anlegen
  if (((parser_class2 *) myParser_class.get(p1)) == 0){
    new_class(p1, 0, 0);
  }

	int i = 0;
	while (((parser_class2 *) myParser_class.get(p1))->myParser_function.contains(s.ascii())){

		i++;
		sprintf(ac, "%s%d", pcode::pcode_(p2), i);
    //s.format("%s%d", pcode::pcode_(p2), i); 
    s = ac;
    s = s.upper();

	}

  ((parser_class2 *) myParser_class.get(p1))->myParser_function.addString(s.ascii(), (int) new parser_method(bSupported, p1, p2, pp_list, false, false, false, false));

  pp_list = new XIntVector();// XIntVector;
  pp_list->setAutoDelete(true);
	return true;
}

bool parser_classMethod::new_function_operator(bool bSupported, int p0, int p1, int p2, int p3)
{
  //return true;

  XString s = pcode::pcode_(p3); s = s.upper();
	//char ac[1024];
  
  
	//sprintf(ac, "%s", token::operator_(p3));

	int i = 0;
	while (((parser_class2 *) myParser_class.get(p0))->myParser_function_operator.contains(s.ascii())){
		
		i++;
		sprintf(ac, "%s%d", pcode::pcode_(p2), i);
    //s.format("%s%d", pcode::pcode_(p2), i); 
    s = ac;
    s = s.upper();
	}

	((parser_class2 *) myParser_class.get(p0))->myParser_function_operator.addString(s.ascii(), (int) new parser_operator(bSupported, p1, p2, p3, pp_list));

	pp_list = new XIntVector();// XIntVector;
  pp_list->setAutoDelete(true);
	return true;
}


bool parser_classMethod::new_operator(bool bSupported, int p1, int p2, int p3, int p4)
{
  //return true;
  XString s = pcode::pcode_(p4); s = s.upper();
	//char ac[1024];

	//sprintf(ac, "%s", token::operator_(p4));

	int i = 0;
	while (((parser_class2 *) myParser_class.get(p1))->myParser_operator.contains(s.ascii())){
		
		i++;
		sprintf(ac, "%s%d", pcode::pcode_(p2), i);
    //s.format("%s%d", pcode::pcode_(p2), i); 
    s = ac;
    s = s.upper();
	}

  ((parser_class2 *) myParser_class.get(p1))->myParser_operator.addString(s.ascii(), (int) new parser_operator(bSupported, p2, p3, p4, pp_list));

	pp_list = new XIntVector();// XIntVector;
  pp_list->setAutoDelete(true);
	return true;
}

bool parser_classMethod::new_slot(bool bSupported, int p1, int p2, int p3)
{
  //return true;
  return new_method(bSupported, p1, p2, p3, false, true, false);
}

bool parser_classMethod::new_signal(bool bSupported, int p1, int p2, int p3)
{
  //return true;
  return new_method(bSupported, p1, p2, p3, true, false, false);
}*/


bool parser_classMethod::new_staticmethod(bool bSupported, int p1, int p2, int p3)
{
  ///**/return true;
  XString s = pcode::pcode_(p2); s = s.upper();
	//char ac[1024];

	//sprintf(ac, "%s", pcode::pcode_(p2));
  if (p1 == 10031){
    p1 = p1;
  }

	int i = 0;
	while (((parser_class2 *) myParser_class.get(p1))->myParser_staticmethod.contains(s.ascii())){

		i++;
		sprintf(ac, "%s%d", pcode::pcode_(p2), i);
    //s.format("%s%d", pcode::pcode_(p2), i); 
    s = ac;
    s = s.upper();

	}

	((parser_class2 *) myParser_class.get(p1))->myParser_staticmethod.addString(s.ascii(), (int) new parser_method(bSupported, p2, p3, pp_list, false, false, true, false));
	
  pp_list = new XIntVector();// XIntVector;
  pp_list->setAutoDelete(true);
	return true;
}

/*
bool parser_classMethod::new_enum(int p1, char *p2, int p3)
{
  //return true;
  if (p1 == 1357){
    p1 = p1;
  }
  ((parser_class2 *) myParser_class.get(p1))->myParser_enum.addString(p2, p3);
	return true;
}*/



parser_classMethod::parser_classMethod()
{

  pp_list = new XIntVector();// XIntVector;
  pp_list->setAutoDelete(true);

//  #include "parser_qt_binding.h"
  #include "parser_kbasic_binding.h"

  return;
 

}


parser_classMethod::~parser_classMethod()
{
  int key; // used for iterations of XIntMap
  int value; // used for iterations of XIntMap

  pp_list->clear();
  delete pp_list;
  
  //printf("\n\n");
  //int i = 0;
//return;

  if (myParser_class.first(&key, &value)){
    do {

      parser_class2 *m = (parser_class2 *) value;

      delete m;

    } while (myParser_class.next(&key, &value));
  }

  myParser_class.clear();  
  
  
}

parser_class2::parser_class2(int _nParentClassId, int _nParentClassId2, int _nClassId, bool _bAbstract)
{
	nParentClassId = _nParentClassId;
	nParentClassId2 = _nParentClassId2;
	nClassId = _nClassId;
	bAbstract = _bAbstract;
}


parser_class2::~parser_class2()
{ 
  int key; // used for iterations of XIntMap
  int value; // used for iterations of XIntMap

  if (myParser_method.first(&key, &value)){
    do {

      parser_method *m = (parser_method *) value;

      delete m;

    } while (myParser_method.next(&key, &value));
  }

  myParser_method.clear();

  myParser_const.clear();

  if (myParser_property_get.first(&key, &value)){
    do {

      parser_method *m = (parser_method *) value;

      delete m;

    } while (myParser_property_get.next(&key, &value));
  }
  myParser_property_get.clear();


  if (myParser_property_set.first(&key, &value)){
    do {

      parser_method *m = (parser_method *) value;

      delete m;

    } while (myParser_property_set.next(&key, &value));
  }
  myParser_property_set.clear();


  if (myParser_staticproperty_get.first(&key, &value)){
    do {

      parser_method *m = (parser_method *) value;

      delete m;

    } while (myParser_staticproperty_get.next(&key, &value));
  }
  myParser_staticproperty_get.clear();


  if (myParser_staticproperty_set.first(&key, &value)){
    do {

      parser_method *m = (parser_method *) value;

      delete m;

    } while (myParser_staticproperty_set.next(&key, &value));
  }
  myParser_staticproperty_set.clear();

/*
  if (myParser_function.first(&key, &value)){
    do {

      parser_method *m = (parser_method *) value;

      delete m;

    } while (myParser_function.next(&key, &value));
  }
  myParser_function.clear();

  if (myParser_operator.first(&key, &value)){
    do {

      parser_operator *m = (parser_operator *) value;

      delete m;

    } while (myParser_operator.next(&key, &value));
  }
  myParser_operator.clear();

  if (myParser_function_operator.first(&key, &value)){
    do {

      parser_operator *m = (parser_operator *) value;

      delete m;

    } while (myParser_function_operator.next(&key, &value));
  }
  myParser_function_operator.clear();
*/
  if (myParser_staticmethod.first(&key, &value)){
    do {

      parser_method *m = (parser_method *) value;

      delete m;

    } while (myParser_staticmethod.next(&key, &value));
  }
  myParser_staticmethod.clear();
/*
  if (myParser_slot.first(&key, &value)){
    do {

      parser_method *m = (parser_method *) value;

      delete m;

    } while (myParser_slot.next(&key, &value));
  }
  myParser_slot.clear();

  if (myParser_signal.first(&key, &value)){
    do {

      parser_method *m = (parser_method *) value;

      delete m;

    } while (myParser_signal.next(&key, &value));
  }
  myParser_signal.clear();

  if (myParser_protected.first(&key, &value)){
    do {

      parser_method *m = (parser_method *) value;

      delete m;

    } while (myParser_protected.next(&key, &value));
  }
  myParser_protected.clear();

  if (myParser_property.first(&key, &value)){
    do {

      parser_method *m = (parser_method *) value;

      delete m;

    } while (myParser_property.next(&key, &value));
  }
  myParser_property.clear();

  myParser_enum.clear();*/
}


parser_method::parser_method(bool _bSupported, int _nClassMethodId, int _nReturnType, XIntVector *pp, bool _bSignal, bool _bSlot, bool _bStatic, bool _bEvent)
{
	nClassMethodId = _nClassMethodId;
	nReturnType = _nReturnType;
  bSupported = _bSupported;

  bSignal = _bSignal;
  bSlot = _bSlot;
  bStatic = _bStatic;
  bEvent = _bEvent;  

	myParser_parameter = pp;
}

parser_method::~parser_method()
{
  myParser_parameter->clear();
  delete myParser_parameter;

}

/*
parser_operator::parser_operator(bool _bSupported, int _nClassOperatorId, int _nReturnType, int _nOperatorType, XIntVector *pp)
{
	nClassOperatorId = _nClassOperatorId;
	nReturnType = _nReturnType;
	nOperatorType = _nOperatorType;
  bSupported = _bSupported;

	myParser_parameter = pp;
//  myParser_parameter->setAutoDelete(true);
}

parser_operator::~parser_operator()
{
  myParser_parameter->clear();
	delete myParser_parameter;
}*/


parser_parameter::parser_parameter(const char *_sName, int _nType, bool _bOptional)
{
	sName = _sName;
	nType = _nType;
	bOptional = _bOptional;
  /*
  if (!bOptional){
    int i = 0;
    i++;
  }
  */
 bDefault = false;
}

parser_parameter::parser_parameter(const char *_sName, int _nType, bool _bOptional, bool _bDefault)
{
	sName = _sName;	nType = _nType;	bOptional = _bOptional;	bDefault = true; boolean_ = _bDefault;
/*
  if (strcmp("unclipped123", sName) == 0){

    QString ss;
    ss = ss.sprintf("%s  %d %s %s", sName.latin1(), nType, bDefault ? "yes" : "no", bOptional ? "yes" : "no");
    QMessageBox::information(0, "", ss);

  }
  */
}

parser_parameter::parser_parameter(const char *_sName, int _nType, bool _bOptional, float fDefault)
{
	sName = _sName;	nType = _nType;	bOptional = _bOptional;	bDefault = true; single_ = fDefault;
}

parser_parameter::parser_parameter(const char *_sName, int _nType, bool _bOptional, double dDefault)
{
	sName = _sName;	nType = _nType;	bOptional = _bOptional;	bDefault = true; double_ = dDefault;
}

parser_parameter::parser_parameter(const char *_sName, int _nType, bool _bOptional, int nDefault)
{
	sName = _sName;	nType = _nType;	bOptional = _bOptional;	bDefault = true; integer_ = nDefault;
}

parser_parameter::parser_parameter(const char *_sName, int _nType, bool _bOptional, long lDefault)
{
	sName = _sName;	nType = _nType;	bOptional = _bOptional;	bDefault = true; long_ = lDefault;
}

parser_parameter::parser_parameter(const char *_sName, int _nType, bool _bOptional, const char *sDefault)
{
	sName = _sName;	nType = _nType;	bOptional = _bOptional;	bDefault = true; cstring_ = sDefault;
}



bool parser::binding_fClassMethod_default(pcode *p, parser_parameter *pp)
{
	switch(pp->nType){
		case pcode__LONG:
			if (bProducePcode) p->wr_PUSH_LONG(pcode__PUSH_LONG, pp->long_);
			break;
		case pcode__SINGLE:
			if (bProducePcode) p->wr_PUSH_SINGLE(pcode__PUSH_SINGLE, pp->single_);
			break;
		case pcode__DOUBLE:
			if (bProducePcode) p->wr_PUSH_DOUBLE(pcode__PUSH_DOUBLE, pp->double_);
			break;
		case pcode__BOOLEAN:
			if (bProducePcode) p->wr_PUSH_BOOLEAN(pcode__PUSH_BOOLEAN, pp->boolean_);
			break;
		case pcode__QSTRING:
		case pcode__CSTRING:
			{
        register const char *ac = pp->cstring_.ascii();

        // wird für "const char * name = 0" benötigt
        if (pp->cstring_ == 0){
          ac = "";
        }

				register int nStringLiteral = registerStringLiteral(ac);
   	 		if (nStringLiteral == 0){ internalError( utility::con(ac, " string literal not declared") ); _ERROR_ }
  			if (bProducePcode) p->wr_PUSH_QSTRING(pcode__PUSH_QSTRING, nStringLiteral);						
			}
			break;
		case pcode__INTEGER: // default is used for object, probably with zero init
		default:
  		if (bProducePcode) p->wr_PUSH_INTEGER(pcode__PUSH_INTEGER, pp->integer_);
			break;
	}
	return true;
}

bool parser::binding_fCLASS_METHOD_CALL(pcode *p, int *nReturnExpressionType, bool bReturn, bool bPrintError, bool bInnerCall)
{
	_BEGIN_

  
	int nVar;// = 0;
	t_scope scope;// = global;
	int nType;// = 0;
  int nType2;// = 0;
 	//bool bMETHOD = false;
  const char *acMethod;// = "";

#ifdef KBDEBUG
  if (stopAtLine(26, "C:/kbasic17/kbide/examples/projects/demo_winzip.kbasic_project/configuration.kbasic_form")){
     int i = 9;
     i++;
  }
#endif

	if (bInnerCall || fVARIABLE_DECLARED(p, &nVar, &scope, &nType)){
    /*
    if (scope == global){
      scope = scope;
    }*/
    if (bInnerCall){
      nType = nType2 = *nReturnExpressionType;
    } else {
      nType2 = nType;
    }
    
    if (!bSilent && bProducePcode){
      p->wr_SEPARATOR(pcode__SEPARATOR, utility::con(" binding_CLASS_METHOD_CALL", getCurrentLine() - 1));
    }    

    switch(nType){
      case pcode___strings:
        {
          bool b1 = false;
          bool b2 = false;

          
          if (parseTerm(token__SYM_BC_OP)){
//          if ((b1 = parseTerm(token__SYM_BR_OP)) || (b2 = parseTerm(token__SYM_BR_OP))){
            if (!bInnerCall && bProducePcode) p->wr_PUSH_ID(pcode__PUSH_ID, nVar, scope, false);

            if (!fNUMERIC_EXPRESSION(p)){ syntaxError(pcode___strings, "expression missing"); _ERROR_ }

            if (!parseTerm(token__SYM_BC_CL)){ syntaxError(pcode___strings, "} missing"); _ERROR_ }

            if (!bReturn){
   	          if (!parseTerm(token__OP_EQUAL)){ syntaxError(pcode___strings, "= missing"); _ERROR_ }
              if (!fSTRING_EXPRESSION(p)){ syntaxError(pcode___strings, "expression missing"); _ERROR_ }
              
              *nReturnExpressionType = pcode__VOID;
            } else {
              *nReturnExpressionType = pcode__QString;
            }
            
            //if (b1 && !parseTerm(token__SYM_BR_CL)){ syntaxError(pcode___strings, ") missing"); _ERROR_ }
            //else if (b2 && !parseTerm(token__SYM_BS_CL)){ syntaxError(pcode___strings, "] missing"); _ERROR_ }
            
            if (bProducePcode){
              if (!bReturn){
                p->wr_PUSH_INTEGER(pcode__PUSH_INTEGER, 2);
	  			      p->wr_binding_ClassMethod(pcode__binding_CLASSMETHOD, pcode___strings__SET, bReturn);
              } else {
                p->wr_PUSH_INTEGER(pcode__PUSH_INTEGER, 1);
	  			      p->wr_binding_ClassMethod(pcode__binding_CLASSMETHOD, pcode___strings__GET, bReturn);
              }
            }

            _DONE_
          }
        }
        break;
      case pcode___stringsstrings:
        {
          bool b1 = false;
          bool b2 = false;

          
          if (parseTerm(token__SYM_BC_OP)){
//          if ((b1 = parseTerm(token__SYM_BR_OP)) || (b2 = parseTerm(token__SYM_BR_OP))){
            if (!bInnerCall && bProducePcode) p->wr_PUSH_ID(pcode__PUSH_ID, nVar, scope, false);

            if (!fSTRING_EXPRESSION(p)){ syntaxError(pcode___stringsstrings, "string expression missing"); _ERROR_ }

            if (!parseTerm(token__SYM_BC_CL)){ syntaxError(pcode___stringsstrings, "} missing"); _ERROR_ }

            if (!bReturn){
   	          if (!parseTerm(token__OP_EQUAL)){ syntaxError(pcode___stringsstrings, "= missing"); _ERROR_ }
              if (!fSTRING_EXPRESSION(p)){ syntaxError(pcode___stringsstrings, "expression missing"); _ERROR_ }
              
              *nReturnExpressionType = pcode__VOID;
            } else {
              *nReturnExpressionType = pcode__QString;
            }
            
            //if (b1 && !parseTerm(token__SYM_BR_CL)){ syntaxError(pcode___stringsstrings, ") missing"); _ERROR_ }
            //else if (b2 && !parseTerm(token__SYM_BS_CL)){ syntaxError(pcode___stringsstrings, "] missing"); _ERROR_ }
            
            if (bProducePcode){
              if (!bReturn){
                p->wr_PUSH_INTEGER(pcode__PUSH_INTEGER, 2);
	  			      p->wr_binding_ClassMethod(pcode__binding_CLASSMETHOD, pcode___stringsstrings__SET, bReturn);
              } else {
                p->wr_PUSH_INTEGER(pcode__PUSH_INTEGER, 1);
	  			      p->wr_binding_ClassMethod(pcode__binding_CLASSMETHOD, pcode___stringsstrings__GET, bReturn);
              }
            }

            _DONE_
          }
        }
        break;
      case pcode___array:
        {
          bool b1 = false;
          bool b2 = false;

          
          if (parseTerm(token__SYM_BC_OP)){
//          if ((b1 = parseTerm(token__SYM_BR_OP)) || (b2 = parseTerm(token__SYM_BR_OP))){
            if (!bInnerCall && bProducePcode) p->wr_PUSH_ID(pcode__PUSH_ID, nVar, scope, false);

            if (!fEXPRESSION(p)){ syntaxError(pcode___array, "expression missing"); _ERROR_ }

            for (int i = 0; i < MAX_ARRAY - 1; i++){
              if (parseTerm(token__SYM_COMMA)){ 
                if (!fEXPRESSION(p)){ syntaxError(pcode___array, "expression missing"); _ERROR_ }
              } else {
	              int nStringLiteral = findStringLiteral("");
 	              if (nStringLiteral == 0){ internalError( utility::con("", " string literal not declared") ); _ERROR_ }
	              if (bProducePcode) p->wr_PUSH_QSTRING(pcode__PUSH_QSTRING, nStringLiteral);
              }
            }

            if (!parseTerm(token__SYM_BC_CL)){ syntaxError(pcode___array, "} missing"); _ERROR_ }

            if (!bReturn){
   	          if (!parseTerm(token__OP_EQUAL)){ syntaxError(pcode___array, "= missing"); _ERROR_ }
              if (!fEXPRESSION(p)){ syntaxError(pcode___array, "expression missing"); _ERROR_ }

              *nReturnExpressionType = pcode__VOID;
            } else {
              *nReturnExpressionType = pcode__VARIANT;
            }
            
            //if (b1 && !parseTerm(token__SYM_BR_CL)){ syntaxError(pcode___array, ") missing"); _ERROR_ }
            //else if (b2 && !parseTerm(token__SYM_BS_CL)){ syntaxError(pcode___array, "] missing"); _ERROR_ }
            
            if (bProducePcode){
              if (!bReturn){
                p->wr_PUSH_INTEGER(pcode__PUSH_INTEGER, 1 + MAX_ARRAY);
	  			      p->wr_binding_ClassMethod(pcode__binding_CLASSMETHOD, pcode___array__SET, bReturn);
              } else {
                p->wr_PUSH_INTEGER(pcode__PUSH_INTEGER, MAX_ARRAY);
	  			      p->wr_binding_ClassMethod(pcode__binding_CLASSMETHOD, pcode___array__GET, bReturn);
              }
            }

            _DONE_
          }
        }
        break;
    }

		if (parseTerm(token__SYM_DOT)){

			if (fID_KEYWORD_OR_BUILTIN(&acMethod, true)){

        _BEGIN3_
				if (!bInnerCall && bProducePcode){

		      if (nType2 == token__ME){
            nType = myClass->getId(getClass());
			      p->wr_PUSH_ME(pcode__PUSH_ME);
		      } else if (nType2 == token__PARENT){
            nType = myClass->getId(getParentClass());
			      p->wr_PUSH_PARENT(pcode__PUSH_PARENT);        
         } else {
 				    p->wr_PUSH_ID(pcode__PUSH_ID, nVar, scope, false);
         }

   			}

      // walk hierarchy
      do {
        
				if (binding_fCLASS_METHOD_CALL(p, nReturnExpressionType, bReturn, nType, acMethod, bPrintError)){
          
          do {
            _BEGIN2_
            if (parseTerm(token__SYM_DOT)){
          			if (fID_KEYWORD_OR_BUILTIN(&acMethod, true)){
         				  if (binding_fCLASS_METHOD_CALL(p, nReturnExpressionType, bReturn, *nReturnExpressionType, acMethod, bPrintError)){
                 } else {
                  _END2_
                  return true;
                 }
               }
            } else {
              return true;
            }
          } while (true);
					
				}

      _END3_

      nType = myClass->getParentId(nType);    

      if (!bInnerCall && bProducePcode){
	      
         if (memory_type::isBinding(nType)){
           p->wr_binding_PUSH_ID(pcode__binding_PUSH_ID, nVar, scope);

         } else if (nType2 == token__ME){            
			      p->wr_PUSH_ME(pcode__PUSH_ME);
		     } else if (nType2 == token__PARENT){            
			      p->wr_PUSH_PARENT(pcode__PUSH_PARENT);        
         } else {
 				    p->wr_PUSH_ID(pcode__PUSH_ID, nVar, scope, false);
         }
      }
        

    } while (nType > 0);
  
      }
		}
	}


  // implicitly called, if class inherits qt binding class, and one of those methods is called
  if (fID_KEYWORD_OR_BUILTIN(&acMethod, true)){

#ifdef KBDEBUG
    if (stopAtLine(11)){
      int i = 9;
      i++;
    }
#endif

    if (!bInnerCall &&bProducePcode){
      p->wr_PUSH__binding_ME(pcode__PUSH__binding_ME);
    }

    nType = myClass->getId(getClass());

    // walk hierarchy
    do {

      if (binding_fCLASS_METHOD_CALL(p, nReturnExpressionType, bReturn, nType, acMethod, false)){

          do {
            _BEGIN2_

            if (parseTerm(token__SYM_DOT)){
          			if (fID_KEYWORD_OR_BUILTIN(&acMethod, true)){
         				  if (binding_fCLASS_METHOD_CALL(p, nReturnExpressionType, bReturn, *nReturnExpressionType, acMethod, bPrintError)){
                 } else {
                  _END2_
                  return true;
                 }
               }
            } else {
              return true;
            }
          } while (true);
      }

      _END2_
      fID_KEYWORD_OR_BUILTIN(&acMethod, true);

      if (!bInnerCall &&bProducePcode){
         p->wr_PUSH__binding_ME(pcode__PUSH__binding_ME);
      }
      nType = myClass->getParentId(nType);      

    } while (nType > 0);
  }

	_END_

}

bool parser::binding_fCLASS_METHOD_CALL(pcode *p, int *nReturnExpressionType, bool bReturn, int nClassId, const char *acMethod, bool bPrintError, bool bSignalSlotDefinition)
{
	_BEGIN_

	bool bTerm_SYM_BR_OP;// = false;
	bool bTerm_SYM_BR_CL;// = false;
	//bool bTerm_SYM_COMMA = false;
	int nParamCount = 0;
	int nUsedParam = 0;

	int i = 0;
	//char ac[1024];
  bool b2 = false;

  XString s = acMethod; s = s.upper();

	//sprintf(ac, "%s", acMethod);

	goto j;
retry:
	_END2_
	_BEGIN2_
	i++;
//  s.format("%s%d", acMethod, i); s = s.upper();
	sprintf(ac, "%s%d", acMethod, i);
  s = ac;
  s = s.upper();

  nParamCount = 0;
  nUsedParam = 0;
  b2 = false;
j:


	parser_class2 *pc = (parser_class2*) myParser_classMethod->myParser_class.get(nClassId);

  bool bForNext = false;

  if (nFORNEXT && s == "NEXT"){
    bForNext = true;    
  }
/*
  if (s == "GET"){
    bForNext = bForNext;    
  }*/

  if (nClassId == 1381){
    nClassId = nClassId;
  }



	if (pc){
		parser_method *pm = 0;

		while (pc != 0 && (pm = (parser_method *) pc->myParser_method.getString(s.ascii())) == 0){ // search in super class, if method in current class wasn't found
			if (pc->nParentClassId == 0) break;
			pc = (parser_class2 *) myParser_classMethod->myParser_class.get(pc->nParentClassId);
		}

		if (pm == 0){ // zweiter Versuch in anderer parent class -> Mehrfachvererbung
			pc = (parser_class2 *) myParser_classMethod->myParser_class.get(nClassId);
		}

		while (pc != 0 && (pm = (parser_method *) pc->myParser_method.getString(s.ascii())) == 0){ // search in super class, if method in current class wasn't found
			if (pc->nParentClassId2 == 0) break;
			pc = (parser_class2 *) myParser_classMethod->myParser_class.get(pc->nParentClassId2);
		}

		if (pm){
      b2 = true;

			if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){}

      if (bForNext && !bTerm_SYM_BR_OP) _END_ // WORKAROUND is FOR NEXT not call of Form.Next()

			int n = 0;
			
			//parser_parameter *pp2;	
			//for (pp2 = pp = pm->myParser_parameter->first(); pp != 0; pp = pm->myParser_parameter->next()){

      //bool b = true;

      //st d::li st<parser_parameter*>::iterator 
        parser_parameter *it = 0;
/*
#ifdef KBDEBUG
  if (stopAtLine(13)){
     int i = 9;
     i++;
#endif


     for ( it = pm->myParser_parameter->begin(); it != pm->myParser_parameter->end(); ++it ){
				
       pp = (*it);

    QString ss;
    ss = ss.sprintf("11 %s  %d %s %s", pp->sName.latin1(), pp->nType, pp->bDefault ? "yes" : "no", pp->bOptional ? "yes" : "no");
    QMessageBox::information(0, "", ss);

     }

  }
  */  
     pcode *pp = 0;

/*
    if (pm->nClassMethodId == pcode___udpsocket__METHOD_ReadData){
      bool bImplicitDIM = false;
      bool bTestImplicitDim = true;
      bool bSizeAll = false;
      int nLStringLen = 0;
      bool bReference = false;  
      bool bAssignment = false;  
      bool bProperty = false;  
      bool bTestProperty = false;  

	    int nVar = 0; t_scope scope = global; int nIdType = 0; int nType = 0; t_arrayVariable a;

      bool bIDENTIFIER = false;
      if ((bIDENTIFIER = fVARIABLE_ASSIGNMENT(p, &nVar, &scope, &nIdType, &nType, &bImplicitDIM, 
                                bTestImplicitDim, &a, 
                                &bSizeAll, &nLStringLen, &bReference, &bProperty, bTestProperty                 
                                ))){ 
                                  switch(nType){
                                    case pcode__STRING:
                                    //case pcode__LSTRING:
                                      bIDENTIFIER = true;
                                      break;
                                    default:
                                      bIDENTIFIER = false;
                                      { syntaxError(token__KEYWORD, "data type not allowed here"); _ERROR_ }
                                      
                                      break;     
 


                                  }
                                }

      if (!bIDENTIFIER){ syntaxError(token__INPUT, "variable missing"); _ERROR_ }

      if (bProducePcode){
        p->wr_PUSH_INTEGER(pcode__PUSH_INTEGER, nType); 
//        p->wr_PUSH_INTEGER(pcode__PUSH_INTEGER, nType == pcode__LSTRING ? 100000 + nLStringLen : nType); 
        pp = new pcode("");        
        pp->wr_MOV(pcode__MOV, nVar, scope); 
      }
      nParamCount++;
                                 
    } else if (pm->nClassMethodId == pcode___udpsocket__METHOD_WriteData){

      int nExpressionType = 0;
     
      if (!fEXPRESSION(p, &nExpressionType)){ syntaxError(token__MSGBOX, "expression missing"); _ERROR_ }
      switch(nExpressionType){
        case pcode__STRING:
      //  case pcode__LSTRING:
          break;
        default:
          //if (!memory_type::isType(nExpressionType))
          { syntaxError(token__KEYWORD, "data type not allowed here"); _ERROR_ }
          break;
      }
      nParamCount++;

    } else 
    */
    if (pm->nClassMethodId == pcode___serialport__METHOD_ReadData){
      bool bImplicitDIM = false;
      bool bTestImplicitDim = true;
      bool bSizeAll = false;
      int nLStringLen = 0;
      bool bReference = false;  
      bool bAssignment = false;  
      bool bProperty = false;  
      bool bTestProperty = false;  

	    int nVar = 0; t_scope scope = global; int nIdType = 0; int nType = 0; t_arrayVariable a;

      bool bIDENTIFIER = false;
      if ((bIDENTIFIER = fVARIABLE_ASSIGNMENT(p, &nVar, &scope, &nIdType, &nType, &bImplicitDIM, 
                                bTestImplicitDim, &a, 
                                &bSizeAll, &nLStringLen, &bReference, &bProperty, bTestProperty                 
                                ))){ 
                                  switch(nType){
                                    case pcode__BOOLEAN:
                                  //  case pcode__STRING:
                                    //case pcode__LSTRING:
                                    case pcode__BYTE:
                                    case pcode__SHORT:
                                    case pcode__INTEGER:
                                    case pcode__LONG:
                                    case pcode__SINGLE:
                                    case pcode__DOUBLE:
                                      bIDENTIFIER = true;
                                      break;
                                    default:
                                      bIDENTIFIER = false;
                                      { syntaxError(token__KEYWORD, "data type not allowed here"); _ERROR_ }
                                      
                                      break;     
 


                                  }
                                }

      if (!bIDENTIFIER){ syntaxError(token__INPUT, "variable missing"); _ERROR_ }

      if (bProducePcode){
        p->wr_PUSH_INTEGER(pcode__PUSH_INTEGER, nType); 
//        p->wr_PUSH_INTEGER(pcode__PUSH_INTEGER, nType == pcode__LSTRING ? 100000 + nLStringLen : nType); 
        pp = new pcode("");        
        pp->wr_MOV(pcode__MOV, nVar, scope); 
      }
      nParamCount++;
                                 
    } else if (pm->nClassMethodId == pcode___serialport__METHOD_WriteData){

      int nExpressionType = 0;
     
      if (!fEXPRESSION(p, &nExpressionType)){ syntaxError(token__MSGBOX, "expression missing"); _ERROR_ }
      switch(nExpressionType){
        case pcode__BOOLEAN:
      //  case pcode__STRING:
      //  case pcode__LSTRING:
        case pcode__BYTE:
        case pcode__SHORT:
        case pcode__INTEGER:
        case pcode__LONG:
        case pcode__SINGLE:
        case pcode__DOUBLE:
          break;
        default:
          //if (!memory_type::isType(nExpressionType))
          { syntaxError(token__KEYWORD, "data type not allowed here"); _ERROR_ }
          break;
      }
      nParamCount++;

    } else if (pm->nClassMethodId == pcode___serialport__METHOD_ReadLine){
      bool bImplicitDIM = false;
      bool bTestImplicitDim = true;
      bool bSizeAll = false;
      int nLStringLen = 0;
      bool bReference = false;  
      bool bAssignment = false;  
      bool bProperty = false;  
      bool bTestProperty = false;  

	    int nVar = 0; t_scope scope = global; int nIdType = 0; int nType = 0; t_arrayVariable a;

      bool bIDENTIFIER = false;
      if ((bIDENTIFIER = fVARIABLE_ASSIGNMENT(p, &nVar, &scope, &nIdType, &nType, &bImplicitDIM, 
                                bTestImplicitDim, &a, 
                                &bSizeAll, &nLStringLen, &bReference, &bProperty, bTestProperty                 
                                ))){ bIDENTIFIER = memory_type::isString(nType); }

      if (!bIDENTIFIER){ syntaxError(token__INPUT, "string variable missing"); _ERROR_ }

      if (bProducePcode){
        pp = new pcode("");
        if (nType == pcode__QSTRING) pp->wr_MOV_QSTRING(pcode__MOV_QSTRING, nVar, scope); 
        else pp->wr_MOV_CSTRING(pcode__MOV_CSTRING, nVar, scope); 
      }


    } else if (pm->nClassMethodId == pcode___serialport__METHOD_WriteLine){
      
      //pp = new pcode("");
      if (!fSTRING_EXPRESSION(p)){ syntaxError(token__MSGBOX, "string expression missing"); _ERROR_ }
      nParamCount++;

    } else {

    parser_parameter *pp = 0;	
    if (pm->myParser_parameter->first((int *) &pp)){
      
      do {


     //XIntVector::iterator IT;
     //for ( IT = pm->myParser_parameter->begin(); *IT; ++IT ){
//     for ( it = pm->myParser_parameter->begin(); it != pm->myParser_parameter->end(); ++it) ){
				/*
       if (b){
         pp2 = pp = (*it);
       } else {
         pp = (*it);
       }
       */
        //pp = *IT;


#ifdef KBDEBUG
  if (stopAtLine(13)){
     int i = 9;
     i++;
/*
    QString ss;
    ss = ss.sprintf("%s  %d %s %s", pp->sName.latin1(), pp->nType, pp->bDefault ? "yes" : "no", pp->bOptional ? "yes" : "no");
    QMessageBox::information(0, "", ss);
*/
  }
#endif

				if (n != nUsedParam/* && pp != pp2*/){
					if (!(parseTerm(token__SYM_COMMA)) && pp->bOptional == false){ goto retry; }
            //syntaxError(token__SUB, ", and parameter missing"); _ERROR_ }
				}
				
				n = nUsedParam;

				switch(pp->nType){
          /*
					case pcode__DOUBLE_POINTER:
						if (fDOUBLE_POINTER(p)){ nUsedParam++; }
						else if (pp->bDefault && binding_fClassMethod_default(p, pp)){}
						else if (pp->bOptional == false){ goto retry; }
						nParamCount++;
						break;*/
					case pcode__DOUBLE:
						if (fDOUBLE_EXPRESSION(p)){ nUsedParam++; }
						else if (pp->bDefault && binding_fClassMethod_default(p, pp)){}
						else if (pp->bOptional == false){ goto retry; }
						nParamCount++;
						break;/*
					case pcode__INTEGER_POINTER:
						if (fINTEGER_POINTER(p)){ nUsedParam++; }
						else if (pp->bDefault && binding_fClassMethod_default(p, pp)){}
						else if (pp->bOptional == false){ goto retry; }
						nParamCount++;
						break;*/
					case pcode__INTEGER:
						if (fINTEGER_EXPRESSION(p)){ nUsedParam++; }
						else if (pp->bDefault && binding_fClassMethod_default(p, pp)){}
						else if (pp->bOptional == false){ goto retry; }
						nParamCount++;
						break;/*
					case pcode__CSTRING_POINTER:
						if (fCSTRING_POINTER(p)){ nUsedParam++; }
						else if (pp->bDefault && binding_fClassMethod_default(p, pp)){}
						else if (pp->bOptional == false){ goto retry; }
						nParamCount++;
						break;*/
					case pcode__QSTRING:
					case pcode__CSTRING:
						if (fSTRING_EXPRESSION(p)){ nUsedParam++; }
						else if (pp->bDefault && binding_fClassMethod_default(p, pp)){}
						else if (pp->bOptional == false){ goto retry; }
						nParamCount++;
						break;/*
					case pcode__BOOLEAN_POINTER:
						if (fBOOLEAN_POINTER(p)){ nUsedParam++; }
						else if (pp->bDefault && binding_fClassMethod_default(p, pp)){}
						else if (pp->bOptional == false){ goto retry; }
						nParamCount++;
						break;*/
					case pcode__BOOLEAN:
						if (fBOOLEAN_EXPRESSION(p)){ nUsedParam++; }
						else if (pp->bDefault && binding_fClassMethod_default(p, pp)){}
						else if (pp->bOptional == false){ goto retry; }
						nParamCount++;
						break;/*
					case pcode__LONG_POINTER:
						if (fLONG_POINTER(p)){ nUsedParam++; }
						else if (pp->bDefault && binding_fClassMethod_default(p, pp)){}
						else if (pp->bOptional == false){ goto retry; }
						nParamCount++;
						break;*/
					case pcode__LONG:
						if (fLONG_EXPRESSION(p)){ nUsedParam++; }
						else if (pp->bDefault && binding_fClassMethod_default(p, pp)){}
						else if (pp->bOptional == false){ goto retry; }
						nParamCount++;
						break;/*
					case pcode__SINGLE_POINTER:
						if (fSINGLE_POINTER(p)){ nUsedParam++; }
						else if (pp->bDefault && binding_fClassMethod_default(p, pp)){}
						else if (pp->bOptional == false){ goto retry; }
						nParamCount++;
						break;*/
					case pcode__SINGLE:
						if (fSINGLE_EXPRESSION(p)){ nUsedParam++; }
						else if (pp->bDefault && binding_fClassMethod_default(p, pp)){}
						else if (pp->bOptional == false){ goto retry; }
						nParamCount++;
						break;           
					default:	
						if (fEXPRESSION2(p, pp->nType, false, true)){ nUsedParam++; }
						else if (pp->bDefault && binding_fClassMethod_default(p, pp)){}
						else if (pp->bOptional == false){ goto retry; }
						nParamCount++;
						break;
				}
        //b = false;

      } while (pm->myParser_parameter->next((int *) &pp));
    }
   }
			

   		if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL)))){}
   		if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ goto retry; }

  		*nReturnExpressionType = pm->nReturnType;

   		if (bProducePcode){
       if (bSignalSlotDefinition){
				  p->wr_PUSH_BOOLEAN(pcode__PUSH_BOOLEAN, true);
				  p->wr_PUSH_INTEGER(pcode__PUSH_INTEGER, pm->nClassMethodId);
				  int nStringLiteral = registerStringLiteral(acMethod);
   	 		  if (nStringLiteral == 0){ internalError( utility::con(acMethod, " string literal not declared") ); _ERROR_ }
  			  p->wr_PUSH_QSTRING(pcode__PUSH_QSTRING, nStringLiteral);						
       } else {
				  p->wr_PUSH_INTEGER(pcode__PUSH_INTEGER, nParamCount);
          /*
          if (pm->nClassMethodId == pcode___form__METHOD_Resize){
            pm->nClassMethodId = pm->nClassMethodId;
          }*/
				  p->wr_binding_ClassMethod(pcode__binding_CLASSMETHOD, pm->nClassMethodId, bReturn);
       }
       if (pp){
         p->pcodeWritePcode(pp);
         delete pp;
       }
   		}

     if (bSignalSlotDefinition){
       parseInfo(p,  utility::con ("parsed SIGNAL/SLOT definition: ", pcode::pcode_(pm->nClassMethodId)));
     } else {
  			parseInfo(p, utility::con("parsed ", pcode::pcode_(pm->nClassMethodId)));
     }

			_DONE_

		} else {
			const char *acType = findType(nClassId);
      if (b2){
   			 semanticError(token__CLASS, utility::con("no matching arguments found for method", acMethod, "in class", acType) );
      } else if (bPrintError){
  			 //semanticError(token__CLASS, utility::con(acMethod, "method not found in class", acType) );
      }
      // could be a property
//      _ERROR_
		
    }
	}

	_END_
}

/*
bool parser::binding_fCLASS_OPERATOR(pcode *p, int *nReturnExpressionType, int nClassId, int nOperatorType)
{
	_BEGIN_

  if (!bSilent && bProducePcode){
    p->wr_SEPARATOR(pcode__SEPARATOR, utility::con(" binding_CLASS_OPERATOR", getCurrentLine() - 1));
  }

	bool bTerm_SYM_BR_OP;// = false;
	bool bTerm_SYM_BR_CL;// = false;
	bool bTerm_SYM_COMMA;// = false;
	int nParamCount = 0;
	int nUsedParam = 0;

	int i = 0;
	//char ac[1024];
  bool b = false;

  const char *acMethod = token::operator_(nOperatorType);

	//sprintf(ac, "%s", acMethod);
  XString s = acMethod; s = s.upper();

	goto j;
retry:
	_END2_
	_BEGIN2_
	i++;
//  s.format("%s%d", acMethod, i); s = s.upper();
	sprintf(ac, "%s%d", acMethod, i);
  s = ac;
  s = s.upper();

  nParamCount = 0;
  nUsedParam = 0;
  b = false;
j:


	parser_class2 *pc = (parser_class2 *) myParser_classMethod->myParser_class.get(nClassId);

  if (nClassId == 1357){
    nClassId = nClassId;
  }

	if (pc){
		parser_operator *pm = 0;

		while (pc != 0 && (pm = (parser_operator *) pc->myParser_operator.getString(s.ascii())) == 0){ // search in super class, if method in current class wasn't found
			if (pc->nParentClassId == 0) break;
			pc =(parser_class2 *) myParser_classMethod->myParser_class.get(pc->nParentClassId);
		}    

		if (pm == 0){ // zweiter Versuch in anderer parent class -> Mehrfachvererbung
			pc = (parser_class2 *) myParser_classMethod->myParser_class.get(nClassId);
		}

		while (pc != 0 && (pm = (parser_operator *) pc->myParser_operator.getString(s.ascii())) == 0){ // search in super class, if method in current class wasn't found
			if (pc->nParentClassId2 == 0) break;
			pc = (parser_class2 *) myParser_classMethod->myParser_class.get(pc->nParentClassId2);
		}

		if (pm){
      b = true;

			//if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){}

			int n = 0;
			parser_parameter *pp;	
			parser_parameter *pp2;	

      bool b = true;
     parser_parameter *it;


     if (pm->myParser_parameter->first((int *) &pp)){
       do {

     //XIntVector::iterator IT;
     //for ( IT = pm->myParser_parameter->begin(); *IT; ++IT ){
				
       if (b){
         pp2 = pp;// = (*IT);
       } else {
        // pp = (*IT);
       }

				if (n != nUsedParam){
					if (!(bTerm_SYM_COMMA = parseTerm(token__SYM_COMMA)) && pp->bOptional == false){ syntaxError(token__SUB, ", and parameter missing"); _ERROR_ }
				}
				
				n = nUsedParam;

				switch(pp->nType){
					case pcode__DOUBLE_POINTER:
						if (fDOUBLE_POINTER(p)){ nUsedParam++; }
						else if (pp->bDefault && binding_fClassMethod_default(p, pp)){}
						else if (pp->bOptional == false){ goto retry; }
						nParamCount++;
						break;
					case pcode__DOUBLE:
						if (fDOUBLE_EXPRESSION(p)){ nUsedParam++; }
						else if (pp->bDefault && binding_fClassMethod_default(p, pp)){}
						else if (pp->bOptional == false){ goto retry; }
						nParamCount++;
						break;
					case pcode__INTEGER_POINTER:
						if (fINTEGER_POINTER(p)){ nUsedParam++; }
						else if (pp->bDefault && binding_fClassMethod_default(p, pp)){}
						else if (pp->bOptional == false){ goto retry; }
						nParamCount++;
						break;
					case pcode__INTEGER:
						if (fINTEGER_EXPRESSION(p)){ nUsedParam++; }
						else if (pp->bDefault && binding_fClassMethod_default(p, pp)){}
						else if (pp->bOptional == false){ goto retry; }
						nParamCount++;
						break;
					case pcode__CSTRING_POINTER:
						if (fCSTRING_POINTER(p)){ nUsedParam++; }
						else if (pp->bDefault && binding_fClassMethod_default(p, pp)){}
						else if (pp->bOptional == false){ goto retry; }
						nParamCount++;
						break;
					case pcode__QSTRING:
					case pcode__CSTRING:
						if (fSTRING_EXPRESSION(p)){ nUsedParam++; }
						else if (pp->bDefault && binding_fClassMethod_default(p, pp)){}
						else if (pp->bOptional == false){ goto retry; }
						nParamCount++;
						break;
					case pcode__BOOLEAN_POINTER:
						if (fBOOLEAN_POINTER(p)){ nUsedParam++; }
						else if (pp->bDefault && binding_fClassMethod_default(p, pp)){}
						else if (pp->bOptional == false){ goto retry; }
						nParamCount++;
						break;
					case pcode__BOOLEAN:
						if (fBOOLEAN_EXPRESSION(p)){ nUsedParam++; }
						else if (pp->bDefault && binding_fClassMethod_default(p, pp)){}
						else if (pp->bOptional == false){ goto retry; }
						nParamCount++;
						break;
					case pcode__LONG_POINTER:
						if (fLONG_POINTER(p)){ nUsedParam++; }
						else if (pp->bDefault && binding_fClassMethod_default(p, pp)){}
						else if (pp->bOptional == false){ goto retry; }
						nParamCount++;
						break;
					case pcode__LONG:
						if (fLONG_EXPRESSION(p)){ nUsedParam++; }
						else if (pp->bDefault && binding_fClassMethod_default(p, pp)){}
						else if (pp->bOptional == false){ goto retry; }
						nParamCount++;
						break;
					case pcode__SINGLE_POINTER:
						if (fSINGLE_POINTER(p)){ nUsedParam++; }
						else if (pp->bDefault && binding_fClassMethod_default(p, pp)){}
						else if (pp->bOptional == false){ goto retry; }
						nParamCount++;
						break;
					case pcode__SINGLE:
						if (fSINGLE_EXPRESSION(p)){ nUsedParam++; }
						else if (pp->bDefault && binding_fClassMethod_default(p, pp)){}
						else if (pp->bOptional == false){ goto retry; }
						nParamCount++;
						break;
					default:	
						if (fEXPRESSION3(p, pp->nType)){ nUsedParam++; }
						else if (pp->bDefault && binding_fClassMethod_default(p, pp)){}
						else if (pp->bOptional == false){ goto retry; }
						nParamCount++;
						break;
				}
			
      } while (pm->myParser_parameter->next((int *) &pp));
    }


//			if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL)))){}
 //  		if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ goto retry; }

  		*nReturnExpressionType = pm->nReturnType;

   		if (bProducePcode){
				p->wr_PUSH_INTEGER(pcode__PUSH_INTEGER, nParamCount);
				p->wr_binding_ClassOperator(pcode__binding_CLASSOPERATOR, pm->nClassOperatorId);
   		}

			//parseInfo(p, utility::con("parsed ", pcode::pcode_(pm->nClassOperatorId)));
			_DONE_

		} else {
			const char *acType = findType(nClassId);
      if (b){
   			 semanticError(token__CLASS, utility::con("no matching arguments found for operator overloading", acMethod, "in class", acType) );
         _ERROR_
      } else {
        _END_
  			 //semanticError(token__CLASS, utility::con(acMethod, " (operator overloading) not found in class", acType) );
      }      
		}
	}

	_END_
}

bool parser::binding_fFUNCTION_OPERATOR(pcode *p, int *nReturnExpressionType)
{
	_BEGIN_

  _END_ //  noch falsch

  if (!bSilent && bProducePcode){
    p->wr_SEPARATOR(pcode__SEPARATOR, utility::con(" binding_FUNCTION_OPERATOR", getCurrentLine() - 1));
  }

	bool bTerm_SYM_BR_OP;// = false;
	bool bTerm_SYM_BR_CL;// = false;
	bool bTerm_SYM_COMMA;// = false;
	int nParamCount = 0;
	int nUsedParam = 0;

	int i = 0;
	//char ac[1024];
  bool b = false;

  int nToken = peekToken();
  int nClassId = nToken;

  const char *acMethod = token::operator_(nToken);

	//sprintf(ac, "%s", acMethod);
  XString s = acMethod; s = s.upper();

	goto j;
retry:
	_END2_
	_BEGIN2_
	i++;
//  s.format("%s%d", acMethod, i); s = s.upper();
	sprintf(ac, "%s%d", acMethod, i);
  s = ac;
  s = s.upper();

  nParamCount = 0;
  nUsedParam = 0;
  b = false;
j:


	parser_class2 *pc = (parser_class2 *) myParser_classMethod->myParser_class.get(nClassId);

  if (nClassId == 1350){
    nClassId = nClassId;
  }

	if (pc){
		parser_operator *pm = 0;

		while (pc != 0 && (pm = (parser_operator *) pc->myParser_operator.getString(s.ascii())) == 0){ // search in super class, if method in current class wasn't found
			if (pc->nParentClassId == 0) break;
			pc =(parser_class2 *) myParser_classMethod->myParser_class.get(pc->nParentClassId);
		}

		if (pm == 0){ // zweiter Versuch in anderer parent class -> Mehrfachvererbung
			pc = (parser_class2 *) myParser_classMethod->myParser_class.get(nClassId);
		}

		while (pc != 0 && (pm = (parser_operator *) pc->myParser_operator.getString(s.ascii())) == 0){ // search in super class, if method in current class wasn't found
			if (pc->nParentClassId2 == 0) break;
			pc = (parser_class2 *) myParser_classMethod->myParser_class.get(pc->nParentClassId2);
		}

		if (pm){
      b = true;

			//if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){}

			int n = 0;
			parser_parameter *pp;	
			parser_parameter *pp2;	

      bool b = true;


      if (pm->myParser_parameter->first((int *) &pp)){
        do {

      //XIntVector::iterator IT;
      //for ( IT = pm->myParser_parameter->begin(); *IT; ++IT ){
				
       if (b){
         pp2 = pp;// = (*IT);
       } else {
       //  pp = (*IT);
       }

				if (n != nUsedParam){
					if (!(bTerm_SYM_COMMA = parseTerm(token__SYM_COMMA)) && pp->bOptional == false){ syntaxError(token__SUB, ", and parameter missing"); _ERROR_ }
				}
				
				n = nUsedParam;

				switch(pp->nType){
					case pcode__DOUBLE_POINTER:
						if (fDOUBLE_POINTER(p)){ nUsedParam++; }
						else if (pp->bDefault && binding_fClassMethod_default(p, pp)){}
						else if (pp->bOptional == false){ goto retry; }
						nParamCount++;
						break;
					case pcode__DOUBLE:
						if (fDOUBLE_EXPRESSION(p)){ nUsedParam++; }
						else if (pp->bDefault && binding_fClassMethod_default(p, pp)){}
						else if (pp->bOptional == false){ goto retry; }
						nParamCount++;
						break;
					case pcode__INTEGER_POINTER:
						if (fINTEGER_POINTER(p)){ nUsedParam++; }
						else if (pp->bDefault && binding_fClassMethod_default(p, pp)){}
						else if (pp->bOptional == false){ goto retry; }
						nParamCount++;
						break;
					case pcode__INTEGER:
						if (fINTEGER_EXPRESSION(p)){ nUsedParam++; }
						else if (pp->bDefault && binding_fClassMethod_default(p, pp)){}
						else if (pp->bOptional == false){ goto retry; }
						nParamCount++;
						break;
					case pcode__CSTRING_POINTER:
						if (fCSTRING_POINTER(p)){ nUsedParam++; }
						else if (pp->bDefault && binding_fClassMethod_default(p, pp)){}
						else if (pp->bOptional == false){ goto retry; }
						nParamCount++;
						break;
					case pcode__QSTRING:
					case pcode__CSTRING:
						if (fSTRING_EXPRESSION(p)){ nUsedParam++; }
						else if (pp->bDefault && binding_fClassMethod_default(p, pp)){}
						else if (pp->bOptional == false){ goto retry; }
						nParamCount++;
						break;
					case pcode__BOOLEAN_POINTER:
						if (fBOOLEAN_POINTER(p)){ nUsedParam++; }
						else if (pp->bDefault && binding_fClassMethod_default(p, pp)){}
						else if (pp->bOptional == false){ goto retry; }
						nParamCount++;
						break;
					case pcode__BOOLEAN:
						if (fBOOLEAN_EXPRESSION(p)){ nUsedParam++; }
						else if (pp->bDefault && binding_fClassMethod_default(p, pp)){}
						else if (pp->bOptional == false){ goto retry; }
						nParamCount++;
						break;
					case pcode__LONG_POINTER:
						if (fLONG_POINTER(p)){ nUsedParam++; }
						else if (pp->bDefault && binding_fClassMethod_default(p, pp)){}
						else if (pp->bOptional == false){ goto retry; }
						nParamCount++;
						break;
					case pcode__LONG:
						if (fLONG_EXPRESSION(p)){ nUsedParam++; }
						else if (pp->bDefault && binding_fClassMethod_default(p, pp)){}
						else if (pp->bOptional == false){ goto retry; }
						nParamCount++;
						break;
					case pcode__SINGLE_POINTER:
						if (fSINGLE_POINTER(p)){ nUsedParam++; }
						else if (pp->bDefault && binding_fClassMethod_default(p, pp)){}
						else if (pp->bOptional == false){ goto retry; }
						nParamCount++;
						break;
					case pcode__SINGLE:
						if (fSINGLE_EXPRESSION(p)){ nUsedParam++; }
						else if (pp->bDefault && binding_fClassMethod_default(p, pp)){}
						else if (pp->bOptional == false){ goto retry; }
						nParamCount++;
						break;
					default:	
						if (fEXPRESSION3(p, pp->nType)){ nUsedParam++; }
						else if (pp->bDefault && binding_fClassMethod_default(p, pp)){}
						else if (pp->bOptional == false){ goto retry; }
						nParamCount++;
						break;
				}

      } while (pm->myParser_parameter->next((int *) &pp));
    }			

//			if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL)))){}
 //  		if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ goto retry; }

  		*nReturnExpressionType = pm->nReturnType;

   		if (bProducePcode){
				p->wr_PUSH_INTEGER(pcode__PUSH_INTEGER, nParamCount);
				p->wr_binding_FunctionOperator(pcode__binding_FUNCTIONOPERATOR, pm->nClassOperatorId);
   		}

			//parseInfo(p, utility::con("parsed ", pcode::pcode_(pm->nClassOperatorId)));
			_DONE_

		} else {
			const char *acType = findType(nClassId);
      if (b){
   			 semanticError(token__CLASS, utility::con("no matching arguments found for operator overloading", acMethod) );
      } else {
  			 semanticError(token__CLASS, utility::con(acMethod, "(operator overloading) not found") );
      }
      _ERROR_
		}
	}

	_END_
}

bool parser::binding_fCONNECT(pcode *p)
{
	_BEGIN_

  if (!(parseTerm(token__CONNECT))){ _END_ }

 	bool bTerm_SYM_BR_OP = false;
 	bool bTerm_SYM_BR_CL = false;

 	bool bTerm_SYM_BR_OP2 = false;
 	bool bTerm_SYM_BR_CL2 = false;

 	bool bTerm_SIGNAL = false;
 	bool bTerm_SLOT = false;

	bool bEXPRESSION = false;
	bool bEXPRESSION2 = false;

	bool bTerm_COMMA = false;
  int nExpressionType = 0;
  int nExpressionType2 = 0;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

  	if (!(bEXPRESSION = fEXPRESSION(p, &nExpressionType))){ syntaxError(token__CONNECT, "object expression missing"); _ERROR_ }
		if (!memory_type::isObject(nExpressionType) && !memory_type::isBinding(nExpressionType)){ syntaxError(token__CONNECT, "incompatible types. Must be OBJECT"); _ERROR_ }

    if (!(bTerm_COMMA = parseTerm(token__SYM_COMMA))){ syntaxError(token__CONNECT, ", missing"); _ERROR_ }

    if (!(bTerm_SIGNAL = parseTerm(token__SIGNAL))){ syntaxError(token__CONNECT, "SIGNAL missing"); _ERROR_ }

    if (!(bTerm_SYM_BR_OP2 = parseTerm(token__SYM_BR_OP))){ syntaxError(token__CONNECT, "( missing"); _ERROR_ }
    // 
    if (!binding_fSIGNAL(p, nExpressionType)){ syntaxError(token__CONNECT, "SIGNAL defintion missing"); _ERROR_ }

    if (!(bTerm_SYM_BR_CL2 = parseTerm(token__SYM_BR_CL))){ syntaxError(token__CONNECT, ") missing"); _ERROR_ }


    if (!(bTerm_COMMA = parseTerm(token__SYM_COMMA))){ syntaxError(token__CONNECT, ", missing"); _ERROR_ }


  	if (!(bEXPRESSION = fEXPRESSION(p, &nExpressionType2))){ syntaxError(token__CONNECT, "object expression missing"); _ERROR_ }
		if (!memory_type::isObject(nExpressionType2) && !memory_type::isBinding(nExpressionType2)){ syntaxError(token__CONNECT, "incompatible types. Must be OBJECT"); _ERROR_ }

    if (!(bTerm_COMMA = parseTerm(token__SYM_COMMA))){ syntaxError(token__CONNECT, ", missing"); _ERROR_ }

    if (!(bTerm_SLOT = parseTerm(token__SLOT))){ syntaxError(token__CONNECT, "SLOT missing"); _ERROR_ }

    if (!(bTerm_SYM_BR_OP2 = parseTerm(token__SYM_BR_OP))){ syntaxError(token__CONNECT, "( missing"); _ERROR_ }
    
    if (!binding_fSLOT(p, nExpressionType2)){ syntaxError(token__CONNECT, "SLOT defintion missing"); _ERROR_ }

    if (!(bTerm_SYM_BR_CL2 = parseTerm(token__SYM_BR_CL))){ syntaxError(token__CONNECT, ") missing"); _ERROR_ }


    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
   	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__CONNECT, ") missing"); _ERROR_ }

  	{

   		if (bProducePcode){
 				 p->wr_PUSH_INTEGER(pcode__PUSH_INTEGER, nExpressionType);
 				 p->wr_PUSH_INTEGER(pcode__PUSH_INTEGER, nExpressionType2);
 				 p->wr_CONNECT(pcode__CONNECT);
   		}

   		parseInfo(p, "parsed CONNECT");

   		_DONE_
  	}
	}
 	if (!bTerm_SYM_BR_OP){ syntaxError(token__CONNECT, "( missing"); _ERROR_ }

	_END_
}

bool parser::binding_fDISCONNECT(pcode *p)
{
	_BEGIN_

  if (!(parseTerm(token__DISCONNECT))){ _END_ }

  { internalError("Sorry! DISCONNECT for qt bindings is not supported yet."); _ERROR_ }

 	bool bTerm_SYM_BR_OP = false;
 	bool bTerm_SYM_BR_CL = false;

 	bool bTerm_SYM_BR_OP2 = false;
 	bool bTerm_SYM_BR_CL2 = false;

 	bool bTerm_SIGNAL = false;
 	bool bTerm_SLOT = false;

	bool bEXPRESSION = false;
	bool bEXPRESSION2 = false;

	bool bTerm_COMMA = false;
  int nExpressionType = 0;
  int nExpressionType2 = 0;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

  	if (!(bEXPRESSION = fEXPRESSION(p, &nExpressionType))){ syntaxError(token__CONNECT, "object expression missing"); _ERROR_ }
		if (!memory_type::isObject(nExpressionType)){ syntaxError(token__CONNECT, "incompatible types. Must be OBJECT"); _ERROR_ }

    if (!(bTerm_COMMA = parseTerm(token__SYM_COMMA))){ syntaxError(token__CONNECT, ", missing"); _ERROR_ }

    if (!(bTerm_SIGNAL = parseTerm(token__SIGNAL))){ syntaxError(token__CONNECT, "SIGNAL missing"); _ERROR_ }

    if (!(bTerm_SYM_BR_OP2 = parseTerm(token__SYM_BR_OP))){ syntaxError(token__CONNECT, "( missing"); _ERROR_ }
    // 
    if (!binding_fSIGNAL(p, nExpressionType)){ syntaxError(token__CONNECT, "SIGNAL defintion missing"); _ERROR_ }

    if (!(bTerm_SYM_BR_CL2 = parseTerm(token__SYM_BR_CL))){ syntaxError(token__CONNECT, ") missing"); _ERROR_ }


    if (!(bTerm_COMMA = parseTerm(token__SYM_COMMA))){ syntaxError(token__CONNECT, ", missing"); _ERROR_ }


  	if (!(bEXPRESSION = fEXPRESSION(p, &nExpressionType2))){ syntaxError(token__CONNECT, "object expression missing"); _ERROR_ }
		if (!memory_type::isObject(nExpressionType2)){ syntaxError(token__CONNECT, "incompatible types. Must be OBJECT"); _ERROR_ }

    if (!(bTerm_COMMA = parseTerm(token__SYM_COMMA))){ syntaxError(token__CONNECT, ", missing"); _ERROR_ }

    if (!(bTerm_SLOT = parseTerm(token__SLOT))){ syntaxError(token__CONNECT, "SLOT missing"); _ERROR_ }

    if (!(bTerm_SYM_BR_OP2 = parseTerm(token__SYM_BR_OP))){ syntaxError(token__CONNECT, "( missing"); _ERROR_ }
    
    if (!binding_fSLOT(p, nExpressionType)){ syntaxError(token__CONNECT, "SLOT defintion missing"); _ERROR_ }

    if (!(bTerm_SYM_BR_CL2 = parseTerm(token__SYM_BR_CL))){ syntaxError(token__CONNECT, ") missing"); _ERROR_ }


    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
   	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__CONNECT, ") missing"); _ERROR_ }

  	{

   		if (bProducePcode){
 				 p->wr_PUSH_INTEGER(pcode__PUSH_INTEGER, nExpressionType);
 				 p->wr_PUSH_INTEGER(pcode__PUSH_INTEGER, nExpressionType2);
 				 p->wr_DISCONNECT(pcode__DISCONNECT);
   		}

   		parseInfo(p, "parsed DISCONNECT");

   		_DONE_
  	}
	}
 	if (!bTerm_SYM_BR_OP){ syntaxError(token__DISCONNECT, "( missing"); _ERROR_ }

	_END_

}

bool parser::binding_fSIGNAL(pcode *p, int nType)
{
  _BEGIN_

  const char *acIdentifier = "";
  const char *acMethod = "";
  int nReturnExpressionType = 0;
  bool bUnknownFunction = false;

  bool b = fSUB_CALL(p, &acIdentifier, &nReturnExpressionType, false, false, &bUnknownFunction,  
    false, true, nType, false, false, false, false, true);
    
  if (b) return true;
  
  if (fID_KEYWORD_OR_BUILTIN(&acMethod, true)){
     return binding_fCLASS_METHOD_CALL(p, &nReturnExpressionType, false, nType, acMethod, true, true);
  }

  _END_
}

bool parser::binding_fSLOT(pcode *p, int nType)
{
  return binding_fSIGNAL(p, nType);
}

bool parser::binding_fCLASS_ENUM(pcode *p, int *nReturnExpressionType, bool bReturn)
{
	_BEGIN_

  
	int nType = 0;
  const char *acEnum = 0;
  bool bENUM = false;

  if (binding_fVARIABLE_OR_CLASSNAME(p, &nType)){

    if (!bSilent && bProducePcode){
      p->wr_SEPARATOR(pcode__SEPARATOR, utility::con(" binding_CLASS_ENUM", getCurrentLine() - 1));
    }

	  bool bTerm_SYM_DOT = false;
	
		if (bTerm_SYM_DOT = parseTerm(token__SYM_DOT)){

			if (bENUM = fID_KEYWORD_OR_BUILTIN(&acEnum)){

       // walk hierarchy
       do {

         if (binding_fCLASS_ENUM(p, nReturnExpressionType, bReturn, nType, acEnum)){
           return true;
         }

         _END2_
         bENUM = fID_KEYWORD_OR_BUILTIN(&acEnum, true);

         if (bProducePcode){
	         p->wr_PUSH_ME(pcode__PUSH_ME);
         }
         nType = myClass->getParentId(nType);      

       } while (nType > 0);

			}
		}
	}

  // implicitly called, if class inherits qt binding class, and one of those methods is called
  if (bENUM = fID_KEYWORD_OR_BUILTIN(&acEnum, true)){

    if (bProducePcode){
	    p->wr_PUSH_ME(pcode__PUSH_ME);
    }

    nType = myClass->getId(getClass());

    // walk hierarchy
    do {

      if (binding_fCLASS_ENUM(p, nReturnExpressionType, bReturn, nType, acEnum)){
        return true;
      }

      _END2_
      bENUM = fID_KEYWORD_OR_BUILTIN(&acEnum, true);

      if (bProducePcode){
	      p->wr_PUSH_ME(pcode__PUSH_ME);
      }
      nType = myClass->getParentId(nType);      

    } while (nType > 0);
  }

	_END_

}

bool parser::binding_fCLASS_ENUM(pcode *p, int *nReturnExpressionType, bool bReturn, int nClassId, const char *acEnum)
{
	_BEGIN_

	int nParamCount = 0;
	int nUsedParam = 0;

	
	parser_class2 *pc = (parser_class2 *) myParser_classMethod->myParser_class.get(nClassId);

	if (pc){

    int e = 0;
    int kk = 0;

    if (pc->myParser_enum.contains(acEnum)){      
		   e = pc->myParser_enum.getString(acEnum);
       kk = pc->myParser_enum.size();
    }

		while (pc != 0 && pc->myParser_enum.contains(acEnum)){ // search in super class, if method in current class wasn't found
     if (pc->myParser_enum.contains(acEnum)){      
       e = pc->myParser_enum.getString(acEnum);
     }
			
			if (pc->nParentClassId == 0) break;
			pc =(parser_class2 *) myParser_classMethod->myParser_class.get(pc->nParentClassId);
		}

		if (pc == 0){ // zweiter Versuch, andere parent class -> Mehrfachvererbung
			pc = (parser_class2 *) myParser_classMethod->myParser_class.get(nClassId);
		}

		while (pc != 0 && pc->myParser_enum.contains(acEnum)){ // search in super class, if method in current class wasn't found
     if (pc->myParser_enum.contains(acEnum)){     
       e = pc->myParser_enum.getString(acEnum);
     }
			
			if (pc->nParentClassId2 == 0) break;
			pc = (parser_class2 *) myParser_classMethod->myParser_class.get(pc->nParentClassId2);
		}

		if (pc->myParser_enum.contains(acEnum)){

  		*nReturnExpressionType = pcode__INTEGER;

   		if (bProducePcode){
				p->wr_PUSH_INTEGER(pcode__PUSH_INTEGER, e);
   		}

			parseInfo(p, utility::con("parsed ", acEnum));
			_DONE_

		} else {
			//const char *acType = findType(nClassId);
			//semanticError(token__CLASS, utility::con(acEnum, "enum not found in class", acType) );
      //_ERROR_
		}
	}

	_END_
}


*/

bool parser::binding_fCLASS_CONST(pcode *p, int *nReturnExpressionType, bool bReturn)
{
	_BEGIN_

#ifdef KBDEBUG
  if (stopAtLine(7)){
     int i = 9;
     i++;
  }
#endif

	int nType = 0;

	if (binding_fVARIABLE_OR_CLASSNAME(p, &nType)){

    if (!bSilent && bProducePcode){
      p->wr_SEPARATOR(pcode__SEPARATOR, utility::con(" binding_CLASS_CONST", getCurrentLine() - 1));
    }

	  const char *acMethod = 0;
	  bool bTerm_SYM_DOT = false;
	  bool bMETHOD = false;

		if (bTerm_SYM_DOT = parseTerm(token__SYM_DOT)){
			if (bMETHOD = fID_KEYWORD_OR_BUILTIN(&acMethod, true)){

				if (binding_fCLASS_CONST(p, nReturnExpressionType, bReturn, nType, acMethod)){
					_DONE_
				}

			}
		}		
	}

	_END_

}

bool parser::binding_fCLASS_CONST(pcode *p, int *nReturnExpressionType, bool bReturn, int nClassId, const char *acMethod)
{
	_BEGIN_

	bool bTerm_SYM_BR_OP = false;
	bool bTerm_SYM_BR_CL = false;
	bool bTerm_SYM_COMMA = false;
	int nParamCount = 0;
	int nUsedParam = 0;

	int i = 0;
	//char ac[1024];

  //sprintf(ac, "%s", acMethod);
  XString s = acMethod; s = s.upper();

	goto j;
retry:
	_END2_
	_BEGIN2_
	i++;
//  s.format("%s%d", acMethod, i); s = s.upper();
	sprintf(ac, "%s%d", acMethod, i);
  s = ac;
  s = s.upper();

  nParamCount = 0;
  nUsedParam = 0;
j:

#ifdef KBDEBUG
  if (stopAtLine(85)){
     int i = 9;
     i++;
  }
#endif


	parser_class2 *pc = (parser_class2 *) myParser_classMethod->myParser_class.get(nClassId);

	if (pc){
		parser_method *pm = 0;

    while (pc != 0 && (pm = (parser_method *) pc->myParser_const.getString(s.ascii())) == 0){ // search in super class, if method in current class wasn't found
			if (pc->nParentClassId == 0) break;
			pc =(parser_class2 *) myParser_classMethod->myParser_class.get(pc->nParentClassId);
		}

		if (pm == 0){ // zweiter Versuch, andere parent class -> Mehrfachvererbung
			pc = (parser_class2 *) myParser_classMethod->myParser_class.get(nClassId);
		}

		while (pc != 0 && (pm = (parser_method *) pc->myParser_const.getString(s.ascii())) == 0){ // search in super class, if method in current class wasn't found
			if (pc->nParentClassId2 == 0) break;
			pc = (parser_class2 *) myParser_classMethod->myParser_class.get(pc->nParentClassId2);
		}

		if (pm){

  		*nReturnExpressionType = pcode__QString;

   		if (bProducePcode){
  		  int nStringLiteral = registerStringLiteral(acMethod);
 	 		  if (nStringLiteral == 0){ internalError( utility::con(acMethod, " string literal not declared") ); _ERROR_ }
				p->wr_PUSH_QSTRING(pcode__PUSH_QSTRING, nStringLiteral);
   		}

			//parseInfo(p, utility::con("parsed ", pcode::pcode_(pm->nClassMethodId)));
			_DONE_

		}
	}

	_END_
}

bool parser::binding_fCLASS_STATICMETHOD_CALL(pcode *p, int *nReturnExpressionType, bool bReturn)
{
	_BEGIN_

#ifdef KBDEBUG
  if (stopAtLine(26)){
     int i = 9;
     i++;
  }
#endif

	int nType = 0;

	if (binding_fVARIABLE_OR_CLASSNAME(p, &nType)){

    if (!bSilent && bProducePcode){
      p->wr_SEPARATOR(pcode__SEPARATOR, utility::con(" binding_CLASS_STATICMETHOD_CALL", getCurrentLine() - 1));
    }

	  const char *acMethod = 0;
	  bool bTerm_SYM_DOT = false;
	  bool bMETHOD = false;

		if (bTerm_SYM_DOT = parseTerm(token__SYM_DOT)){
			if (bMETHOD = fID_KEYWORD_OR_BUILTIN(&acMethod, true)){

				if (binding_fCLASS_STATICMETHOD_CALL(p, nReturnExpressionType, bReturn, nType, acMethod)){
          if (peekToken() == token__SYM_DOT){
             if (binding_fCLASS_METHOD_CALL(p, nReturnExpressionType, bReturn, false, true));
          }
					_DONE_
				}

			}
		}		
	}

	_END_

}

bool parser::binding_fCLASS_STATICMETHOD_CALL(pcode *p, int *nReturnExpressionType, bool bReturn, int nClassId, const char *acMethod)
{
	_BEGIN_

	bool bTerm_SYM_BR_OP = false;
	bool bTerm_SYM_BR_CL = false;
	bool bTerm_SYM_COMMA = false;
	int nParamCount = 0;
	int nUsedParam = 0;

	int i = 0;
	//char ac[1024];

  //sprintf(ac, "%s", acMethod);
  XString s = acMethod; s = s.upper();

	goto j;
retry:
	_END2_
	_BEGIN2_
	i++;
//  s.format("%s%d", acMethod, i); s = s.upper();
	sprintf(ac, "%s%d", acMethod, i);
  s = ac;
  s = s.upper();

  nParamCount = 0;
  nUsedParam = 0;
j:

#ifdef KBDEBUG
  if (stopAtLine(85)){
     int i = 9;
     i++;
  }
#endif


	parser_class2 *pc = (parser_class2 *) myParser_classMethod->myParser_class.get(nClassId);

	if (pc){
		parser_method *pm = 0;

    while (pc != 0 && (pm = (parser_method *) pc->myParser_staticmethod.getString(s.ascii())) == 0){ // search in super class, if method in current class wasn't found
			if (pc->nParentClassId == 0) break;
			pc =(parser_class2 *) myParser_classMethod->myParser_class.get(pc->nParentClassId);
		}

		if (pm == 0){ // zweiter Versuch, andere parent class -> Mehrfachvererbung
			pc = (parser_class2 *) myParser_classMethod->myParser_class.get(nClassId);
		}

		while (pc != 0 && (pm = (parser_method *) pc->myParser_staticmethod.getString(s.ascii())) == 0){ // search in super class, if method in current class wasn't found
			if (pc->nParentClassId2 == 0) break;
			pc = (parser_class2 *) myParser_classMethod->myParser_class.get(pc->nParentClassId2);
		}

		if (pm){

			if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){}

			int n = 0;
			parser_parameter *pp;	
			//parser_parameter *pp2;	
//			for (pp2 = pp = pm->myParser_parameter->first(); pp != 0; pp = pm->myParser_parameter->next()){

     // bool b = true;

      if (pm->myParser_parameter->first((int *) &pp)){
        do {

      //XIntVector::iterator IT;
      //for ( IT = pm->myParser_parameter->begin(); *IT; ++IT ){
			/*	
       if (b){
        // pp2 = pp;// = (*IT);
       } else {
       //  pp = (*IT);
       }*/
      

				if (n != nUsedParam /*&& pp != pp2*/){
					if (!(bTerm_SYM_COMMA = parseTerm(token__SYM_COMMA)) && pp->bOptional == false){ 
            goto retry;
          //  syntaxError(token__SUB, ", missing"); _ERROR_ 
          }
				}
				
				n = nUsedParam;

				switch(pp->nType){
          /*
					case pcode__DOUBLE_POINTER:
						if (fDOUBLE_POINTER(p)){ nUsedParam++; }
						else { goto retry; }
						nParamCount++;
						break;*/
					case pcode__DOUBLE:
						if (fDOUBLE_EXPRESSION(p)){ nUsedParam++; }
						else if (pp->bDefault && binding_fClassMethod_default(p, pp)){}
						else if (pp->bOptional == false){ goto retry; }
						nParamCount++;
						break;/*
					case pcode__INTEGER_POINTER:
						if (fINTEGER_POINTER(p)){ nUsedParam++; }
						else { goto retry; }
						nParamCount++;
						break;*/
					case pcode__INTEGER:
						if (fINTEGER_EXPRESSION(p)){ nUsedParam++; }
						else if (pp->bDefault && binding_fClassMethod_default(p, pp)){}
						else if (pp->bOptional == false){ goto retry; }
						nParamCount++;
						break;/*
					case pcode__CSTRING_POINTER:
						if (fCSTRING_POINTER(p)){ nUsedParam++; }
						else { goto retry; }
						nParamCount++;
						break;*/
					case pcode__QSTRING:
					case pcode__CSTRING:
						if (fSTRING_EXPRESSION(p)){ nUsedParam++; }
						else if (pp->bDefault && binding_fClassMethod_default(p, pp)){}
						else if (pp->bOptional == false){ goto retry; }
						nParamCount++;
						break;/*
					case pcode__BOOLEAN_POINTER:
						if (fBOOLEAN_POINTER(p)){ nUsedParam++; }
						else { goto retry; }
						nParamCount++;
						break;*/
					case pcode__BOOLEAN:
						if (fBOOLEAN_EXPRESSION(p)){ nUsedParam++; }
						else if (pp->bDefault && binding_fClassMethod_default(p, pp)){}
						else if (pp->bOptional == false){ goto retry; }
						nParamCount++;
						break;/*
					case pcode__LONG_POINTER:
						if (fLONG_POINTER(p)){ nUsedParam++; }
						else { goto retry; }
						nParamCount++;
						break;*/
					case pcode__LONG:
						if (fLONG_EXPRESSION(p)){ nUsedParam++; }
						else if (pp->bDefault && binding_fClassMethod_default(p, pp)){}
						else if (pp->bOptional == false){ goto retry; }
						nParamCount++;
						break;/*
					case pcode__SINGLE_POINTER:
						if (fSINGLE_POINTER(p)){ nUsedParam++; }
						else { goto retry; }
						nParamCount++;
						break;*/
					case pcode__SINGLE:
						if (fSINGLE_EXPRESSION(p)){ nUsedParam++; }
						else if (pp->bDefault && binding_fClassMethod_default(p, pp)){}
						else if (pp->bOptional == false){ goto retry; }
						nParamCount++;
						break;
					default:	
						if (fEXPRESSION2(p, pp->nType, false, true)){ nUsedParam++; }
						else if (pp->bDefault && binding_fClassMethod_default(p, pp)){}
						else if (pp->bOptional == false){ goto retry; }
						nParamCount++;
						break;
				}

      } while (pm->myParser_parameter->next((int *) &pp));
    }						

   		if (nUsedParam > 0 && !bTerm_SYM_BR_OP){ syntaxError(token__SUB, "( missing"); _ERROR_ } 
			if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL)))){}
   		if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ goto retry; }

  		*nReturnExpressionType = pm->nReturnType;

   		if (bProducePcode){
				p->wr_PUSH_INTEGER(pcode__PUSH_INTEGER, nParamCount);
				p->wr_binding_ClassStaticMethod(pcode__binding_CLASSMETHOD, pm->nClassMethodId, bReturn);
   		}

			parseInfo(p, utility::con("parsed ", pcode::pcode_(pm->nClassMethodId)));
			_DONE_

		} else {
			//const char *acType = findType(nClassId);
			//semanticError(token__CLASS, utility::con(acMethod, "static method not found in class", acType) );
     // _ERROR_
      // could be a property
		}
	}

	_END_
}

/*
bool parser::binding_fFUNCTION_CALL(pcode *p, int *nReturnExpressionType, bool bReturn)
{
	_BEGIN_

  _END_ 

	bool bTerm_SYM_BR_OP = false;
	bool bTerm_SYM_BR_CL = false;
	bool bTerm_SYM_COMMA = false;
	int nParamCount = 0;
	int nUsedParam = 0;

	int i = 0;
	//char ac[1024];

  int nToken = peekToken();
  int nClassId =  nToken;

  const char *acMethod = token::operator_(nToken);

	//sprintf(ac, "%s", acMethod);
  XString s = acMethod; s = s.upper();

	goto j;
retry:
	_END2_
	_BEGIN2_
	i++;
//  s.format("%s%d", acMethod, i); s = s.upper();
	sprintf(ac, "%s%d", acMethod, i);
  s = ac;
  s = s.upper();

  nParamCount = 0;
  nUsedParam = 0;
j:
  
  
	parser_class2 *pc = (parser_class2 *) myParser_classMethod->myParser_class.get(nClassId);

	if (pc){
		parser_method *pm = 0;

    if (nClassId == 1404){
      nClassId = nClassId;
    }

		while (pc != 0 && (pm = (parser_method *) pc->myParser_staticmethod.getString(s.ascii())) == 0){ // search in super class, if method in current class wasn't found
			if (pc->nParentClassId == 0) break;
			pc =(parser_class2 *) myParser_classMethod->myParser_class.get(pc->nParentClassId);
		}

		if (pm == 0){ // zweiter Versuch, andere parent class -> Mehrfachvererbung
			pc = (parser_class2 *) myParser_classMethod->myParser_class.get(nClassId);
		}

    while (pc != 0 && (pm = (parser_method *) pc->myParser_staticmethod.getString(s.ascii())) == 0){ // search in super class, if method in current class wasn't found
			if (pc->nParentClassId2 == 0) break;
			pc = (parser_class2 *) myParser_classMethod->myParser_class.get(pc->nParentClassId2);
		}

		if (pm){

			if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){}

			int n = 0;
			parser_parameter *pp;	
			parser_parameter *pp2;	

      bool b = true;


      if (pm->myParser_parameter->first((int *) &pp)){
        do {

      //XIntVector::iterator IT;
      //for ( IT = pm->myParser_parameter->begin(); *IT; ++IT ){
				
       if (b){
         pp2 = pp;// = (*IT);
       } else {
       //  pp = (*IT);
       }

				if (n != nUsedParam ){
					if (!(bTerm_SYM_COMMA = parseTerm(token__SYM_COMMA)) && pp->bOptional == false){ syntaxError(token__SUB, ", missing"); _ERROR_ }
				}
				
				n = nUsedParam;

				switch(pp->nType){
					case pcode__DOUBLE_POINTER:
						if (fDOUBLE_POINTER(p)){ nUsedParam++; }
						else { goto retry; }
						nParamCount++;
						break;
					case pcode__DOUBLE:
						if (fDOUBLE_EXPRESSION(p)){ nUsedParam++; }
						else if (pp->bDefault && binding_fClassMethod_default(p, pp)){}
						else if (pp->bOptional == false){ goto retry; }
						nParamCount++;
						break;
					case pcode__INTEGER_POINTER:
						if (fINTEGER_POINTER(p)){ nUsedParam++; }
						else { goto retry; }
						nParamCount++;
						break;
					case pcode__INTEGER:
						if (fINTEGER_EXPRESSION(p)){ nUsedParam++; }
						else if (pp->bDefault && binding_fClassMethod_default(p, pp)){}
						else if (pp->bOptional == false){ goto retry; }
						nParamCount++;
						break;
					case pcode__CSTRING_POINTER:
						if (fCSTRING_POINTER(p)){ nUsedParam++; }
						else { goto retry; }
						nParamCount++;
						break;
					case pcode__QSTRING:
					case pcode__CSTRING:
						if (fSTRING_EXPRESSION(p)){ nUsedParam++; }
						else if (pp->bDefault && binding_fClassMethod_default(p, pp)){}
						else if (pp->bOptional == false){ goto retry; }
						nParamCount++;
						break;
					case pcode__BOOLEAN_POINTER:
						if (fBOOLEAN_POINTER(p)){ nUsedParam++; }
						else { goto retry; }
						nParamCount++;
						break;
					case pcode__BOOLEAN:
						if (fBOOLEAN_EXPRESSION(p)){ nUsedParam++; }
						else if (pp->bDefault && binding_fClassMethod_default(p, pp)){}
						else if (pp->bOptional == false){ goto retry; }
						nParamCount++;
						break;
					case pcode__LONG_POINTER:
						if (fLONG_POINTER(p)){ nUsedParam++; }
						else { goto retry; }
						nParamCount++;
						break;
					case pcode__LONG:
						if (fLONG_EXPRESSION(p)){ nUsedParam++; }
						else if (pp->bDefault && binding_fClassMethod_default(p, pp)){}
						else if (pp->bOptional == false){ goto retry; }
						nParamCount++;
						break;
					case pcode__SINGLE_POINTER:
						if (fSINGLE_POINTER(p)){ nUsedParam++; }
						else { goto retry; }
						nParamCount++;
						break;
					case pcode__SINGLE:
						if (fSINGLE_EXPRESSION(p)){ nUsedParam++; }
						else if (pp->bDefault && binding_fClassMethod_default(p, pp)){}
						else if (pp->bOptional == false){ goto retry; }
						nParamCount++;
						break;
					default:	
						if (fEXPRESSION2(p, pp->nType)){ nUsedParam++; }
						else if (pp->bDefault && binding_fClassMethod_default(p, pp)){}
						else if (pp->bOptional == false){ goto retry; }
						nParamCount++;
						break;
				}

      } while (pm->myParser_parameter->next((int *) &pp));
    }						

   		if (nUsedParam > 0 && !bTerm_SYM_BR_OP){ syntaxError(token__SUB, "( missing"); _ERROR_ } 
			if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL)))){}
   		if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ goto retry; }

  		*nReturnExpressionType = pm->nReturnType;

   		if (bProducePcode){
				p->wr_PUSH_INTEGER(pcode__PUSH_INTEGER, nParamCount);
				p->wr_binding_Function(pcode__binding_FUNCTION, pm->nClassMethodId, bReturn);
   		}

			parseInfo(p, utility::con("parsed ", pcode::pcode_(pm->nClassMethodId)));
			_DONE_

		} else {
			const char *acType = findType(nClassId);
			semanticError(token__CLASS, utility::con(acMethod, "static method not found in class", acType) );
      _ERROR_
		}
	}

	_END_
}

*/
bool parser::binding_fTYPE_Class(pcode *p, const char **acType, bool bNew)
{
	_TBEGIN_

	bool bIDENTIFIER = false;
	const char *acIdentifier = "";


	if (bIDENTIFIER = fID_KEYWORD_OR_BUILTIN(&acIdentifier, false)){

    int i = (int) binding_map_class.getString(acIdentifier);

    if (i > 0){

      if (!bSilent && bProducePcode){
        p->wr_SEPARATOR(pcode__SEPARATOR, utility::con(" binding_TYPE_Class", getCurrentLine() - 1));
      }

			*acType = acIdentifier;
/*
      if (i == pcode___strings && bNew){
        { syntaxError(token__CLASS, " use of class construtor not allowed here"); _TERROR_ };
      }*/

			// p == 0, ist bei cast und typedef
			if (p == 0){ syntaxError(token__CLASS, " use of class construtor not allowed here"); _TERROR_ };

			int nReturnExpressionType = i;

      /*
      switch(i){
        case pcode__strings:
          bNew = true;
          break;
      }*/
			
			if (bNew == false) return true; // don't call the constructor of this class

			return binding_fCLASS_METHOD_CALL(p, &nReturnExpressionType, false, i, acIdentifier, true);
			
		}
	}

	_TEND_
}

bool parser::binding_fSELECTOR_CLASS_PROPERTY(pcode *p, int nClassId,
                                 const char *acIdentifier,
                                 bool bAssignment
                                 )
{
	_BEGIN_

#ifdef KBDEBUG
   if (stopAtLine(26)){
     int i = 9;
     i++;
   }
#endif

   bool bParent = nClassId == myClass->getParentId(getClass());
   int nId; 
    
   if (!bAssignment){
     nId = myClass->getIdPropertyGet(nClassId, acIdentifier);

     if (bProducePcode){
       p->wr_ENTER_PROPERTYGET(pcode__ENTER_PROPERTYGET, nClassId, nId); // write pcode
  	   	p->wr_ClassPropertyGet(pcode__CLASSPROPERTYGET, nClassId, nId, acIdentifier, false, false, bParent, true);
     }

     _DONE_

   } else {

     if (myClass->existPropertySet(nClassId, acIdentifier)){         
        _DONE_
     }

   }

	_END_
}


bool parser::binding_fPROPERTY_ASSIGNMENT(pcode *p, int *nClassId, int *nId, int *nReturnType)
{
  _BEGIN_

	int nVar = 0;
	t_scope scope = global;
	int nType = 0;

  int nIdType = 0;
  bool bImplicitDIM = false;
  bool bTestImplicitDim = false;  
  t_arrayVariable a;
  bool bSizeAll = false;
  int nLStringLen = 0;
  bool bReference = false;  
  bool bProperty = false;    
  bool bTestProperty = false;  
  bool bClassVar = false;   
  bool bArgumentOnly = false; 
  bool bAssignment = true; 

#ifdef KBDEBUG
  if (stopAtLine(7)){
    int i = 9;
    i++;
  }
#endif

  bool bTerm_ME = false;
  bool bTerm_PARENT = false;
  bool bTerm_MEimplictly = false;
  

	if ((bTerm_ME = parseTerm(token__ME))){}
	else if ((bTerm_PARENT = parseTerm(token__PARENT))){}
re:
	if (bTerm_ME || bTerm_PARENT){
    const char *ac = getParentClass();
    if (ac == 0) _END_
    nType = findType(ac);
    if (memory_type::isBinding(nType)){
       if (bProducePcode) p->wr_PUSH__binding_PARENT(pcode__PUSH__binding_PARENT);
    } else {
      _END_
    }
  }
	
  if ((bTerm_ME || bTerm_PARENT) || fVARIABLE(p, &nVar, &scope, &nIdType, &nType, &bImplicitDIM, bTestImplicitDim, &a, &bSizeAll, &nLStringLen, &bReference, &bProperty, bTestProperty, bClassVar, *nClassId, bArgumentOnly, bAssignment)){

    bool bTerm_SYM_DOT = false;

    if (bTerm_MEimplictly || (bTerm_SYM_DOT = parseTerm(token__SYM_DOT))){ 

      bool bPROPERTY = false;
      const char *acProperty = "";

      if (/*memory_type::isBinding(nType) && */(bPROPERTY = fID_KEYWORD_OR_BUILTIN(&acProperty, true))){
        XString s = acProperty;

        s = s.prepend("SETPROPERTY_");

        if (!bSilent && bProducePcode){
         p->wr_SEPARATOR(pcode__SEPARATOR, utility::con("fPROPERTY_ASSIGNMENT", getCurrentLine() - 1));
        }

        { 
 				   if (!bTerm_ME && !bTerm_PARENT) if (bProducePcode) p->wr_binding_PUSH_ID(pcode__binding_PUSH_ID, nVar, scope);
// 				   if (!bTerm_ME && !bTerm_PARENT) if (bProducePcode) p->wr_PUSH_ID(pcode__PUSH_ID, nVar, scope, false);
        }

        int n = nType;
        do {
          if (binding_fPROPERTY_ASSIGNMENT2(p, n, s.ascii(), nId, nReturnType)){
            *nClassId = n;          

            // access test private, public... not needed
            _DONE_
          }

          n = myClass->getParentId(n);

        } while (n);

      }
     	 
	  }
  /*
  } else if (bTerm_ME == false){
    // try implictly Me
    bTerm_ME = true;
    bTerm_MEimplictly = true;
    goto re;*/
  }

  _END_
}


bool parser::binding_fPROPERTY_ASSIGNMENT2(pcode *p, int nClassId, const char *acMethod, int *nMethodId, int *nReturnType)
{
	_BEGIN_

	//bool bTerm_SYM_BR_OP = false;
	//bool bTerm_SYM_BR_CL = false;
	//bool bTerm_SYM_COMMA = false;
	int nParamCount = 0;
	int nUsedParam = 0;

	int i = 0;
	//char ac[1024];
  bool b2 = false;

	//sprintf(ac, "%s", acMethod);
  XString s = acMethod; s = s.upper();
/*
	goto j;
retry:
	_END2_
	_BEGIN2_
	i++;
//  s.format("%s%d", acMethod, i); s = s.upper();
	sprintf(ac, "%s%d", acMethod, i);
  s = ac;
  s = s.upper();

  nParamCount = 0;
  nUsedParam = 0;
  b2 = false;
  */
j:


	parser_class2 *pc = (parser_class2 *) myParser_classMethod->myParser_class.get(nClassId);

#ifdef KBDEBUG
  if (stopAtLine(101)){
     int i = 9;
     i++;
  }
#endif

  if (nClassId == 1381){
    nClassId = nClassId;
  }

	if (pc){
		parser_method *pm = 0;

    while (pc != 0 && (pm = (parser_method *) pc->myParser_property_set.getString(s.ascii())) == 0){ // search in super class, if method in current class wasn't found      
			if (pc->nParentClassId == 0) break;
			pc =(parser_class2 *) myParser_classMethod->myParser_class.get(pc->nParentClassId);
		}

		if (pm == 0){ // zweiter Versuch in anderer parent class -> Mehrfachvererbung
			pc = (parser_class2 *) myParser_classMethod->myParser_class.get(nClassId);
		}

    while (pc != 0 && (pm = (parser_method *) pc->myParser_property_set.getString(s.ascii())) == 0){ // search in super class, if method in current class wasn't found
			if (pc->nParentClassId2 == 0) break;
			pc = (parser_class2 *) myParser_classMethod->myParser_class.get(pc->nParentClassId2);
		}

		if (pm){
      *nMethodId = pm->nClassMethodId;    

      parser_parameter *pp;	
      if (pm->myParser_parameter->first((int *) &pp)){
          *nReturnType = pp->nType;          
       }

      _DONE_
    }

	}

	_END_
}

bool parser::binding_fPROPERTY(pcode *p, int *nReturnExpressionType)
{
  _BEGIN_

	int nVar = 0;
	t_scope scope = global;
	int nType = 0;

//#ifdef KBDEBUG
  if (stopAtLine(5)){
    int i = 9;
    i++;
  }
//#endif

  int nClassId = 0;
  int nIdType = 0;
  bool bImplicitDIM = false;
  bool bTestImplicitDim = false;  
  t_arrayVariable a;
  bool bSizeAll = false;
  int nLStringLen = 0;
  bool bReference = false;  
  bool bProperty = false;    
  bool bTestProperty = false;  
  bool bClassVar = false;   
  bool bArgumentOnly = false; 
  bool bAssignment = false; 

  bool bTerm_ME = false;
  bool bTerm_PARENT = false;
  bool bTerm_MEimplictly = false;  

	if ((bTerm_ME = parseTerm(token__ME))){}
	else if ((bTerm_PARENT = parseTerm(token__PARENT))){}
re:
	if (bTerm_ME || bTerm_PARENT){
    const char *ac = getParentClass();
    if (ac == 0) _END_
    nType = findType(ac);
    if (memory_type::isBinding(nType)){
       if (bProducePcode) p->wr_PUSH__binding_PARENT(pcode__PUSH__binding_PARENT);
    } else {
      _END_
    }
  }
	if ((bTerm_ME || bTerm_PARENT) || fVARIABLE(p, &nVar, &scope, &nIdType, &nType, &bImplicitDIM, bTestImplicitDim, &a, &bSizeAll, &nLStringLen, &bReference, &bProperty, bTestProperty, bClassVar, nClassId, bArgumentOnly, bAssignment)){

    bool bTerm_SYM_DOT = false;

    // workaorund nIdType == -100 || 
	  if (bTerm_MEimplictly || (nIdType == -100 || (bTerm_SYM_DOT = parseTerm(token__SYM_DOT)))){

      bool bPROPERTY = false;
      const char *acProperty = "";

      if (/*memory_type::isBinding(nType) && */(bPROPERTY = fID_KEYWORD_OR_BUILTIN(&acProperty, true))){
        XString s = acProperty;
        s = s.prepend("GETPROPERTY_");

        if (!bSilent && bProducePcode){
         p->wr_SEPARATOR(pcode__SEPARATOR, utility::con("fPROPERTY", getCurrentLine() - 1));
        }

        if (nIdType != -200){ // workaorund nIdType == -200
 				  if (!bTerm_ME && !bTerm_PARENT && bProducePcode) p->wr_binding_PUSH_ID(pcode__binding_PUSH_ID, nVar, scope);        
        }        
        

        int n = nType;
        do {
 
          int nId = 0;
          if (binding_fPROPERTY2(p, n, s.ascii(), &nId, nReturnExpressionType)){

            if (bProducePcode){

                static int nParamCount = 0;
                static bool bReturn = true;

                p->wr_PUSH_INTEGER(pcode__PUSH_INTEGER, nParamCount);
                int n = p->getPos();
				        p->wr_binding_ClassProperty(pcode__binding_CLASSPROPERTY, nId, bReturn);                
              }

              // access test private, public... not needed
              _DONE_
            }

          n = myClass->getParentId(n);

        } while (n);

     
      }
     	 
	  }

/*
  } else if (bTerm_ME == false){
    // try implictly Me
    bTerm_ME = true;
    bTerm_MEimplictly = true;
    goto re;*/
  }

  _END_
}


bool parser::binding_fPROPERTY2(pcode *p, int nClassId, const char *acMethod, int *nMethodId, int *nReturnType)
{
	_BEGIN_

	//bool bTerm_SYM_BR_OP = false;
	//bool bTerm_SYM_BR_CL = false;
	//bool bTerm_SYM_COMMA = false;
	int nParamCount = 0;
	int nUsedParam = 0;

	int i = 0;
	//char ac[1024];
  bool b2 = false;

	//sprintf(ac, "%s", acMethod);
  XString s = acMethod; s = s.upper();

/*
	goto j;
retry:
	_END2_
	_BEGIN2_
	i++;
//  s.format("%s%d", acMethod, i); s = s.upper();
	sprintf(ac, "%s%d", acMethod, i);
  s = ac;
  s = s.upper();

  nParamCount = 0;
  nUsedParam = 0;
  b2 = false;
  */
j:


	parser_class2 *pc = (parser_class2 *) myParser_classMethod->myParser_class.get(nClassId);

#ifdef KBDEBUG
  if (stopAtLine(101)){
     int i = 9;
     i++;
  }

  if (nClassId == 1381){
    nClassId = nClassId;
  }
#endif

	if (pc){
		parser_method *pm = 0;

    while (pc != 0 && (pm = (parser_method *) pc->myParser_property_get.getString(s.ascii())) == 0){ // search in super class, if method in current class wasn't found      
			if (pc->nParentClassId == 0) break;
			pc =(parser_class2 *) myParser_classMethod->myParser_class.get(pc->nParentClassId);
		}

		if (pm == 0){ // zweiter Versuch in anderer parent class -> Mehrfachvererbung
			pc = (parser_class2 *) myParser_classMethod->myParser_class.get(nClassId);
		}

    while (pc != 0 && (pm = (parser_method *) pc->myParser_property_get.getString(s.ascii())) == 0){ // search in super class, if method in current class wasn't found
			if (pc->nParentClassId2 == 0) break;
			pc = (parser_class2 *) myParser_classMethod->myParser_class.get(pc->nParentClassId2);
		}

		if (pm){
      *nMethodId = pm->nClassMethodId;    
      *nReturnType = pm->nReturnType;

      _DONE_
    }

	}

	_END_
}



bool parser::binding_fSTATICPROPERTY(pcode *p, int *nReturnExpressionType, int *nId)
{
  _BEGIN_


#ifdef KBDEBUG
  if (stopAtLine(5)){
    int i = 9;
    i++;
  }
#endif

	int nType = 0;

  bool bTerm_ME = false;
  bool bTerm_PARENT = false;
  bool bTerm_MEimplictly = false;  

	if ((bTerm_ME = parseTerm(token__ME))){}
	else if ((bTerm_PARENT = parseTerm(token__PARENT))){}
re:
	if (bTerm_ME || bTerm_PARENT){
    const char *ac = getParentClass();
    if (ac == 0) _END_
    nType = findType(ac);
    if (memory_type::isBinding(nType)){
       if (bProducePcode) p->wr_PUSH__binding_PARENT(pcode__PUSH__binding_PARENT);
    } else {
      _END_
    }
  }

	if ((bTerm_ME || bTerm_PARENT) || binding_fVARIABLE_OR_CLASSNAME(p, &nType)){

    bool bTerm_SYM_DOT = false;
     
	  if (bTerm_MEimplictly || (bTerm_SYM_DOT = parseTerm(token__SYM_DOT))){

      bool bPROPERTY = false;
      const char *acProperty = "";

      if (/*memory_type::isBinding(nType) && */(bPROPERTY = fID_KEYWORD_OR_BUILTIN(&acProperty, true))){
        XString s = acProperty;
        s = s.prepend("GETPROPERTY_");

        if (!bSilent && bProducePcode){
         p->wr_SEPARATOR(pcode__SEPARATOR, utility::con("fPROPERTY", getCurrentLine() - 1));
        }       


        int n = nType;
        do {

          //int nId = 0;
          if (binding_fSTATICPROPERTY2(p, n, s.ascii(), nId, nReturnExpressionType)){

            if (bProducePcode){

              static int nParamCount = 0;
              static bool bReturn = true;

              p->wr_PUSH_INTEGER(pcode__PUSH_INTEGER, nParamCount);
 			        p->wr_binding_ClassStaticProperty(pcode__binding_CLASSSTATICPROPERTY, *nId, bReturn);                
            }
          
  /*          if (*nReturnExpressionType == pcode___collection && peekToken() == token__SYM_BR_OP){
              / *
              if (fCOLLECTION(p, 0, global, nReturnExpressionType, true)){
              } else 
                * /
              {
                _END_
              }
            }*/
             
            // access test private, public... not needed
            _DONE_
          }

          n = myClass->getParentId(n);

        } while (n);

      }
     	 
	  }

/*
  } else if (bTerm_ME == false){
    // try implictly Me
    bTerm_ME = true;
    bTerm_MEimplictly = true;
    goto re;*/
  }

  _END_
}


bool parser::binding_fSTATICPROPERTY2(pcode *p, int nClassId, const char *acMethod, int *nMethodId, int *nReturnType)
{
	_BEGIN_

	//bool bTerm_SYM_BR_OP = false;
	//bool bTerm_SYM_BR_CL = false;
	//bool bTerm_SYM_COMMA = false;
	int nParamCount = 0;
	int nUsedParam = 0;

	int i = 0;
	//char ac[1024];
  bool b2 = false;

	//sprintf(ac, "%s", acMethod);
  XString s = acMethod; s = s.upper();

/*
	goto j;
retry:
	_END2_
	_BEGIN2_
	i++;
//  s.format("%s%d", acMethod, i); s = s.upper();
	sprintf(ac, "%s%d", acMethod, i);
  s = ac;
  s = s.upper();

  nParamCount = 0;
  nUsedParam = 0;
  b2 = false;
  */
j:


	parser_class2 *pc = (parser_class2 *) myParser_classMethod->myParser_class.get(nClassId);

#ifdef KBDEBUG
  if (stopAtLine(101)){
     int i = 9;
     i++;
  }

  if (nClassId == 1381){
    nClassId = nClassId;
  }
#endif

	if (pc){
		parser_method *pm = 0;

    while (pc != 0 && (pm = (parser_method *) pc->myParser_staticproperty_get.getString(s.ascii())) == 0){ // search in super class, if method in current class wasn't found      
			if (pc->nParentClassId == 0) break;
			pc =(parser_class2 *) myParser_classMethod->myParser_class.get(pc->nParentClassId);
		}

		if (pm == 0){ // zweiter Versuch in anderer parent class -> Mehrfachvererbung
			pc = (parser_class2 *) myParser_classMethod->myParser_class.get(nClassId);
		}

    while (pc != 0 && (pm = (parser_method *) pc->myParser_staticproperty_get.getString(s.ascii())) == 0){ // search in super class, if method in current class wasn't found
			if (pc->nParentClassId2 == 0) break;
			pc = (parser_class2 *) myParser_classMethod->myParser_class.get(pc->nParentClassId2);
		}

		if (pm){
      *nMethodId = pm->nClassMethodId;    
      *nReturnType = pm->nReturnType;

      _DONE_
    }

	}

	_END_
}

bool parser::binding_fSTATICPROPERTY_ASSIGNMENT(pcode *p, int *nClassId, int *nId, int *nReturnType)
{
  _BEGIN_

#ifdef KBDEBUG
  if (stopAtLine(135)){
    int i = 9;
    i++;
  }
#endif


	int nType = 0;


  bool bTerm_ME = false;
  bool bTerm_PARENT = false;
  bool bTerm_MEimplictly = false;  

	if ((bTerm_ME = parseTerm(token__ME))){}
	else if ((bTerm_PARENT = parseTerm(token__PARENT))){}
re:
	if (bTerm_ME || bTerm_PARENT){
    const char *ac = getParentClass();
    if (ac == 0) _END_
    nType = findType(ac);
    if (memory_type::isBinding(nType)){
        if (bProducePcode) p->wr_PUSH__binding_PARENT(pcode__PUSH__binding_PARENT);
    } else {
      _END_
    }
  
	}

	if ((bTerm_ME || bTerm_PARENT) || binding_fVARIABLE_OR_CLASSNAME(p, &nType)){

    bool bTerm_SYM_DOT = false;

    if (bTerm_MEimplictly || (bTerm_SYM_DOT = parseTerm(token__SYM_DOT))){

      bool bPROPERTY = false;
      const char *acProperty = "";

      if (/*memory_type::isBinding(nType) && */(bPROPERTY = fID_KEYWORD_OR_BUILTIN(&acProperty, true))){
        XString s = acProperty;

        s = s.prepend("SETPROPERTY_");

        if (!bSilent && bProducePcode){
         p->wr_SEPARATOR(pcode__SEPARATOR, utility::con("fPROPERTY_ASSIGNMENT", getCurrentLine() - 1));
        }

        int n = nType;
        do {
          if (binding_fSTATICPROPERTY_ASSIGNMENT2(p, n, s.ascii(), nId, nReturnType)){
            *nClassId = n;          

            // access test private, public... not needed
            _DONE_
          }

          n = myClass->getParentId(n);

        } while (n);

      }
     	 
	  }
/*
  } else if (bTerm_ME == false){
    // try implictly Me
    bTerm_ME = true;
    bTerm_MEimplictly = true;
    goto re;*/
  }

  _END_
}


bool parser::binding_fSTATICPROPERTY_ASSIGNMENT2(pcode *p, int nClassId, const char *acMethod, int *nMethodId, int *nReturnType)
{
	_BEGIN_

	//bool bTerm_SYM_BR_OP = false;
	//bool bTerm_SYM_BR_CL = false;
	//bool bTerm_SYM_COMMA = false;
	int nParamCount = 0;
	int nUsedParam = 0;

	int i = 0;
	//char ac[1024];
  bool b2 = false;

	//sprintf(ac, "%s", acMethod);
  XString s = acMethod; s = s.upper();
/*
	goto j;
retry:
	_END2_
	_BEGIN2_
	i++;
//  s.format("%s%d", acMethod, i); s = s.upper();
	sprintf(ac, "%s%d", acMethod, i);
  s = ac;
  s = s.upper();

  nParamCount = 0;
  nUsedParam = 0;
  b2 = false;
  */
j:


	parser_class2 *pc = (parser_class2 *) myParser_classMethod->myParser_class.get(nClassId);

#ifdef KBDEBUG
  if (stopAtLine(135)){
     int i = 9;
     i++;
  }
#endif

  if (nClassId == 1381){
    nClassId = nClassId;
  }

	if (pc){
		parser_method *pm = 0;

    while (pc != 0 && (pm = (parser_method *) pc->myParser_staticproperty_set.getString(s.ascii())) == 0){ // search in super class, if method in current class wasn't found      
			if (pc->nParentClassId == 0) break;
			pc =(parser_class2 *) myParser_classMethod->myParser_class.get(pc->nParentClassId);
		}

		if (pm == 0){ // zweiter Versuch in anderer parent class -> Mehrfachvererbung
			pc = (parser_class2 *) myParser_classMethod->myParser_class.get(nClassId);
		}

    while (pc != 0 && (pm = (parser_method *) pc->myParser_staticproperty_set.getString(s.ascii())) == 0){ // search in super class, if method in current class wasn't found
			if (pc->nParentClassId2 == 0) break;
			pc = (parser_class2 *) myParser_classMethod->myParser_class.get(pc->nParentClassId2);
		}

		if (pm){
      *nMethodId = pm->nClassMethodId;    


      parser_parameter *pp;	
      if (pm->myParser_parameter->first((int *) &pp)){
          *nReturnType = pp->nType;
          
       }
/*
      XIntVector::iterator IT;
      for ( IT = pm->myParser_parameter->begin(); *IT; ++IT ){
							
         parser_parameter *pp;	
         pp = (*IT);
          *nReturnType = pp->nType;
          break;
       }
*/
      _DONE_
    }

	}

	_END_
}







