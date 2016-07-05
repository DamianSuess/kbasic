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

#ifndef _TOOLBOXWINDOW_MENUBAR_H
#define _TOOLBOXWINDOW_MENUBAR_H

#include <QWidget>

class _toolboxwindow_menubar : public QWidget 
{
Q_OBJECT

public:
  _toolboxwindow_menubar(QWidget *parent);

private slots:

void pointer();

void menu();
void childmenu();
void menubaritem();
void move();
void _delete();

};

#endif