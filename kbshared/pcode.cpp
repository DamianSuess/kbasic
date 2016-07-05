
/*
***************************************************************************
Copyright (C) 2000-2008 KBasic Software (Bernd Noetscher, Boseweg 9, 60529 Frankfurt / Germany).  All rights reserved.

pcode.cpp
---------------------------------------------------------------------------
READY
19.02.2004 - new header for this file (BN)
***************************************************************************
*/





#include <string.h>
#include <stdlib.h>
#include <stdio.h>


#include "typedef.h"

#ifdef IDE
#else

#include "../kbshared/pcode.h"
#include "../kbshared/console.h"


#ifdef RUN
#include "../kbasic_binding/_box/kb_box.h"
#include "../kbasic_binding/_form/kb_form.h"
#include "../kbasic_binding/_childcontrol/kb_childcontrol.h"

extern bool bLockingCauseOfBinaryDrawing;


void kb_childcontrol::EVENT_OnPaint(t_integer X, t_integer Y, t_integer Width, t_integer Height){ 
}

void kb_box::EVENT_OnPaint(t_integer X, t_integer Y, t_integer Width, t_integer Height)
{ 
  if (bLockingCauseOfBinaryDrawing) return;
  
  if (bSupresseRecursive) return;
  bSupresseRecursive = true;

  if (nEVENT_OnPaint == 1){    
	  _box::EVENT_OnPaint(X, Y, Width, Height);
  } else {
	QList<int> *param = new QList<int>;
	 param->append((pcode__t_integer));  param->append((pcode__t_integer));  param->append((pcode__t_integer));  param->append((pcode__t_integer)); 
  if (myInterpreter->hasEvent(kbScope, kbId, "OnPaint", acGroup, acName, param)){

    nEVENT_OnPaint = 2;
    
		myInterpreter->pushStack(new interpreter_parameter(X));
		myInterpreter->pushStack(new interpreter_parameter(Y));
		myInterpreter->pushStack(new interpreter_parameter(Width));
		myInterpreter->pushStack(new interpreter_parameter(Height));
    
 
      QPainter *SAVE = EXTERN_myQPainter;
      QPainter p(this); EXTERN_myQPainter = &p;
		  EventSource = this; myInterpreter->callEvent(kbScope, kbId, "OnPaint", acGroup, acName, param);
      EXTERN_myQPainter = SAVE;
  
		delete param; 
    bSupresseRecursive = false;
    return;
	}
	delete param;
  nEVENT_OnPaint = 1;
re:

	_box::EVENT_OnPaint(X, Y, Width, Height);
  bSupresseRecursive = false;

  ;
  }
 }

void kb_form::EVENT_OnPaint(t_integer X, t_integer Y, t_integer Width, t_integer Height)
{ 
  if (bLockingCauseOfBinaryDrawing) return;  

  if (bSupresseRecursive) return;
  

  bSupresseRecursive = true;

  if (nEVENT_OnPaint != 1){
	static QList<int> param;;
  if (kbId && nEVENT_OnPaint == 0 && param.count() == 0){ 
	 param.append((pcode__t_integer));  param.append((pcode__t_integer));  param.append((pcode__t_integer));  param.append((pcode__t_integer)); 
  }
  if (myInterpreter->hasEvent(kbScope, kbId, "OnPaint", acGroup, acName, &param)){
    nEVENT_OnPaint = 2;
		myInterpreter->pushStack(new interpreter_parameter(X));
		myInterpreter->pushStack(new interpreter_parameter(Y));
		myInterpreter->pushStack(new interpreter_parameter(Width));
		myInterpreter->pushStack(new interpreter_parameter(Height));

    QPainter *SAVE = EXTERN_myQPainter;
    QPainter p(main); EXTERN_myQPainter = &p;
		EventSource = this; myInterpreter->callEvent(kbScope, kbId, "OnPaint", acGroup, acName, &param);
    
    //_log::METHOD_Print(QString("%1").arg((int) this));
    //_paint::METHOD_DrawLine(11, 22, 333,444);
    EXTERN_myQPainter = SAVE;
     
    bSupresseRecursive = false;
    return;
	}
	
  if (kbId) nEVENT_OnPaint = 1; // test for kbId, because first paint event is before completing loading form
}
#ifdef CLASS
	CLASS::EVENT_OnPaint(X, Y, Width, Height);
#endif 
  bSupresseRecursive = false;
 }

#endif



pcode::pcode(const char *_acCurrentFile)
{
	ba = new bytearray();

	nIndent = 0; // for output while parsing


  nAppendOffset = 0;
  nAppendOffset2 = 0;
  nAppendOffset3 = 0;
  nAppendOffset4 = 0;

  nDeclarationSize = 0;

#ifdef KBC
  sCurrentFile = _acCurrentFile;
#endif

}

pcode::~pcode()
{
	delete ba;
  ba = 0;
}



bool pcode::pcodeWritePcode(pcode *p, int nOffset)
{
  bytearray *b = p->getBytearray();
  int nLen = b->getPos() - nOffset;

  if (nLen == 0) return true;

#ifdef KBC
  if (p->sCurrentFile.contains("frm_diplomacy")){
    int i = 0;
    i++;
  }
#endif

  if (p->nAppendOffset2 == 0 && nOffset != -1) p->nAppendOffset2 = ba->getPos();
  if (p->nAppendOffset4 == 0 && nOffset != -1) p->nAppendOffset4 = p->ba->getPos();

  p->nAppendOffset = ba->getPos();
  p->nAppendOffset3 = p->ba->getPos();

  return ba->append(b, nOffset == -1 ? 0 : nOffset);
}

#endif

t_cstring pcode::encode(t_cstring s)
{
#ifdef KBC
  XString ss = s;
  
#endif

  return s;
}

t_cstring pcode::decode(t_cstring s)
{
#ifdef RUN
#endif
  return s;
}
