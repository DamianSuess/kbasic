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


#include "_toolboxwindow_toolbar.h"
#include "../kbshared/_toolbar.h"

extern QString kbasicPath(QString sPath);

_toolboxwindow_toolbar *EXTERN_my_toolboxwindow_toolbar;


extern _toolbar *EXTERN_my_toolbar;


extern const QIcon &kbasicIcon(QString s);
extern QString kbasicControlPath(QString s);

_toolboxwindow_toolbar::_toolboxwindow_toolbar(QWidget *parent) : QWidget(parent)
{
  setAutoFillBackground(true);

  QPalette p = palette();
  p.setColor(QPalette::Window, Qt::white);  
  p.setColor(QPalette::Base, Qt::white);  
  p.setColor(QPalette::Button, Qt::white);            
  setPalette(p);

  QGridLayout *grid = new QGridLayout(this);
  grid->setMargin(1);
  grid->setSpacing(1);
  setLayout(grid);


  QPushButton *b;
  int x = 0;
  int y = 0;

  b = new QPushButton(kbasicIcon(kbasicControlPath("pointer.png")), tr(""), this); b->setToolTip("Select"); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(pointer()));

  
  b = new QPushButton(kbasicIcon(kbasicControlPath("toolbaritem.png")), tr(""), this); b->setToolTip("ToolBarItem"); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(toolbaritem()));
  b = new QPushButton(kbasicIcon(kbasicControlPath("move.png")), tr(""), this); b->setToolTip("Move"); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(move()));
  b = new QPushButton(kbasicIcon(kbasicControlPath("delete.png")), tr(""), this); b->setToolTip("Delete"); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(_delete()));

  setLayout(grid);


}


void _toolboxwindow_toolbar::pointer(){ 
  if (EXTERN_my_toolbar) EXTERN_my_toolbar->setInsertControlType(t_notype); 
}

void _toolboxwindow_toolbar::toolbaritem(){ if (EXTERN_my_toolbar) EXTERN_my_toolbar->setInsertControlType(t_toolbaritem); }
void _toolboxwindow_toolbar::move()
{ 
  if (EXTERN_my_toolbar) EXTERN_my_toolbar->setInsertControlType(t_move); 
}
void _toolboxwindow_toolbar::_delete()
{ 
  if (EXTERN_my_toolbar) EXTERN_my_toolbar->setInsertControlType(t_delete); 
}


