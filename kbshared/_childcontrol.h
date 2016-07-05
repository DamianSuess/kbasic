/*
***************************************************************************
Copyright (C) 2000-2008 KBasic Software.  All rights reserved.

_childcontrol.h
---------------------------------------------------------------------------
19.02.2004 - new header for this file (BN)
***************************************************************************
*/


#ifndef _CHILDCONTROL_H
#define _CHILDCONTROL_H

#include <QLabel>

#include "typedef.h"



#include "_property.h"
#include "_control0.h"

#define TEST _childcontrol    
#define TEST2 _childcontrols   
#define TEST3 "FormView"
#define SUPERCLASS QLabel

#define _CHILDCONTROL true

class _form;
class kb_form;


class _childcontrol : public QLabel, public _property
{
  Q_OBJECT
public:



  _childcontrol(_form *f = 0, QWidget *parent = 0) : QLabel (parent ? parent : (QWidget *) f)
{
  constructor(f, parent);


  setAutoFillBackground(true);
  QPalette p = palette();
  p.setColor(QPalette::Window, Qt::white);  
  setPalette(p);


  // properties

  addProperty("StringValue", pt_qstring); addProperty("OldStringValue", pt_qstring);


  // default values
  SETPROPERTY_ControlType("FormView");
  SETPROPERTY_MouseTracking(true);

#ifdef IDE
  setText("Control 'FormView'");
#endif

#ifdef RUN
  ParentForm = 0;
#endif

}

#include "__property_x.h"
#include "__property_y.h"
#include "__property_stringvalue.h"

#ifdef RUN

kb_form *ParentForm;

kb_form *METHOD_Form()
{
  return ParentForm;
}

#endif

// ***
#include "_control1_binding.h"


// ***
#include "_control1.h"


};

#include "_control2.h"

#undef _CHILDCONTROL

#undef TEST
#undef TEST2
#undef TEST3
#undef SUPERCLASS

#endif