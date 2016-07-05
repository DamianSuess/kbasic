/*
***************************************************************************
Copyright (C) 2000-2008 KBasic Software.  All rights reserved.

_childcontrol.h
---------------------------------------------------------------------------
19.02.2004 - new header for this file (BN)
***************************************************************************
*/


#ifndef _FORMSVIEW_H
#define _FORMSVIEW_H

#include <QLabel>




#include "typedef.h"



#include "_property.h"
#include "_control0.h"

#define TEST _formsview    
#define TEST2 _formsviews   
#define TEST3 "FormsView"

#ifdef IDE
  #define SUPERCLASS QLabel
#else
  #define SUPERCLASS QWidget
#endif


#define _FORMSVIEW true

class _form;
class kb_form;

#ifdef IDE
class _formsview : public QLabel, public _property
#else
class _formsview : public QWidget, public _property
#endif
{
  Q_OBJECT
public:


#ifdef IDE
  _formsview(_form *f = 0, QLabel *parent = 0) : QLabel (parent ? parent : (QLabel *) f)
#else
  _formsview(_form *f = 0, QWidget *parent = 0) : QWidget (parent ? parent : (QWidget *) f)
#endif
  
{
  constructor(f, parent);

#ifdef IDE
  setAutoFillBackground(true);
  QPalette p = palette();
  p.setColor(QPalette::Window, Qt::white);  
  setPalette(p);
#endif

  // properties
  addProperty("SelectionMode", pt_qstring);


  // default values
  SETPROPERTY_ControlType("FormsView");
  SETPROPERTY_MouseTracking(true);
  SETPROPERTY_Visible(true);

#ifdef IDE
  setText("Control 'FormsView'");
#endif

#ifdef RUN
  ParentForm = 0;
  init();
#endif

}

#include "__property_x.h"
#include "__property_y.h"
#include "__property_selectionmode.h"

#ifdef RUN

kb_form *ParentForm;

QVBoxLayout *qvboxlayout;

void init();
void METHOD_SelectAll(t_boolean YesNo);
void METHOD_Select(t_integer Index, t_boolean YesNo);
t_boolean METHOD_IsSelected(t_integer Index);
t_integer METHOD_Length();
void METHOD_RemoveAll();
void METHOD_Remove(t_integer Index);
void METHOD_Insert(t_integer Index, _form *Form);
void METHOD_Append(_form *Form);
void METHOD_SetForm(t_integer Index, _form *Form);
_form *METHOD_Form(t_integer Index);
void METHOD_ScrollTo(t_integer Index);

#endif

// ***
#include "_control1_binding.h"


// ***
#include "_control1.h"


};

#include "_control2.h"

#undef _FORMSVIEW

#undef TEST
#undef TEST2
#undef TEST3
#undef SUPERCLASS

#endif