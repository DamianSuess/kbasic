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

#ifndef _TOOLBOXWINDOW_LEOPARD_H
#define _TOOLBOXWINDOW_LEOPARD_H

#include <QWidget>

class _toolboxwindow_leopard : public QWidget 
{
Q_OBJECT

public:
  _toolboxwindow_leopard(QWidget *parent);


private slots:

void pointer();
void leopard_rounded_rect_button();
void leopard_gradient_button();
void leopard_square_button();




// CONTROL

private:

};

#endif