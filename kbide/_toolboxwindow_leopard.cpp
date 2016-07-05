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

#include "_toolboxwindow_leopard.h"


#include "../kbshared/_form.h"

_toolboxwindow_leopard *EXTERN_my_toolboxwindow_leopard;
extern _mainwindow *EXTERN_my_mainwindow;

extern QString sInsertTypeOption;

extern _form *EXTERN_my_form;
extern _menubar *EXTERN_my_menubar;
extern _toolbar *EXTERN_my_toolbar;

extern const QIcon &kbasicIcon(QString s);
extern QString kbasicControlPath(QString s);
extern QString kbasicControlLeopardPath(QString s);

extern bool bInfo;

#define MSG if(bInfo){QMessageBox::information(this,MYAPP,tr("Please click on the position, \nwhere the control is to be inserted."));bInfo=false;}

_toolboxwindow_leopard::_toolboxwindow_leopard(QWidget *parent) : QWidget(parent)
{
  bInfo = EXTERN_my_mainwindow->isPreferenceSet("IntroductionHelp");
  setAutoFillBackground(true);

  QPalette p = palette();
  p.setColor(QPalette::Window, Qt::white);  
  p.setColor(QPalette::Base, Qt::white);  
  p.setColor(QPalette::Button, Qt::white);            
  setPalette(p);

  QGridLayout *grid = new QGridLayout(this);
  grid->setMargin(18);
  grid->setSpacing(18);
  setLayout(grid);

  QPushButton *b;
  int x = 0;
  int y = 0;

  b = new QPushButton(kbasicIcon(kbasicControlPath("pointer.png")), tr(""), this); b->setToolTip("Select"); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(pointer()));
  b = new QPushButton(kbasicIcon(kbasicControlLeopardPath("leopard_rounded_rect_button.png")), tr(""), this); b->setToolTip("Rounded Rect Button"); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(leopard_rounded_rect_button()));
  b = new QPushButton(kbasicIcon(kbasicControlLeopardPath("leopard_gradient_button.png")), tr(""), this); b->setToolTip("Gradient Button"); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(leopard_gradient_button()));
  b = new QPushButton(kbasicIcon(kbasicControlLeopardPath("leopard_square_button.png")), tr(""), this); b->setToolTip("Square Button"); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(leopard_square_button()));
  
  // CONTROL

  setLayout(grid);

}

void _toolboxwindow_leopard::pointer(){ if (EXTERN_my_form){ EXTERN_my_form->setInsertControlType(t_notype); sInsertTypeOption = ""; }}
void _toolboxwindow_leopard::leopard_rounded_rect_button(){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_commandbutton); sInsertTypeOption = "leopard_rounded_rect_button"; }}
void _toolboxwindow_leopard::leopard_gradient_button(){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_commandbutton); sInsertTypeOption = "leopard_gradient_button"; }}
void _toolboxwindow_leopard::leopard_square_button(){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_commandbutton); sInsertTypeOption = "leopard_square_button"; }}

