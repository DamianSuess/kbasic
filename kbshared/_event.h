/*
***************************************************************************
Copyright (C) 2000-2008 KBasic Software: www.kbasic.com. All rights reserved.
Source codes are copyrighted by Bernd Noetscher 2000-2008.

You may use this source codes under the terms of the GNU Public License (Version 3) as published 
by the Free Software Foundation. 

If you are interested in using the source codes for other licenses or 
commercial development, you must buy commercial licenses from KBasic Software.
***************************************************************************
*/


#ifndef _EVENT_H
#define _EVENT_H

#include <QWidget>

#include "typedef.h"

#ifdef RUN


#include "_property.h"



#define TEST _event    
#define TEST2 _events   
#define TEST3 "Event"
#define SUPERCLASS QWidget   



#define _EVENT true

class _form;

// actually this is a fake class and only be used for kbasic_binding, to get access to in code

class _event : public QWidget, public _property
{
  Q_OBJECT
public:


  _event(_form *f = 0, QWidget *parent = 0) : QWidget (parent ? parent : (QWidget *) f)
{
  
}

// events

// *** bindings
// *** 





};

#undef _EVENT






#undef TEST
#undef TEST2
#undef TEST3
#undef SUPERCLASS

#endif

#endif