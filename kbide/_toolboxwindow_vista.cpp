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

#include "_toolboxwindow_vista.h"

#include "../kbshared/_form.h"


_toolboxwindow_vista *EXTERN_my_toolboxwindow_vista;
extern _mainwindow *EXTERN_my_mainwindow;

extern QString sInsertTypeOption;

extern _form *EXTERN_my_form;
extern _menubar *EXTERN_my_menubar;
extern _toolbar *EXTERN_my_toolbar;

extern const QIcon &kbasicIcon(QString s);
extern QString kbasicControlPath(QString s);
extern QString kbasicControlVistaPath(QString s);

extern bool bInfo;

#define MSG if(bInfo){QMessageBox::information(this,MYAPP,tr("Please click on the position, \nwhere the control is to be inserted."));bInfo=false;}

_toolboxwindow_vista::_toolboxwindow_vista(QWidget *parent) : QWidget(parent)
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
  b = new QPushButton(kbasicIcon(kbasicControlVistaPath("vista_bar.png")), tr(""), this); b->setToolTip("Bar"); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(vista_bar()));
  b = new QPushButton(kbasicIcon(kbasicControlVistaPath("vista_ball.png")), tr(""), this); b->setToolTip("Ball"); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(vista_ball()));
  b = new QPushButton(kbasicIcon(kbasicControlVistaPath("vista_bar_commandbutton_enabled.png")), tr(""), this); b->setToolTip("CommandButton (Bar)"); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(vista_bar_commandbutton()));
  b = new QPushButton(kbasicIcon(kbasicControlVistaPath("vista_window_close_enabled.png")), tr(""), this); b->setToolTip("Close (Window)"); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(vista_window_close()));
  b = new QPushButton(kbasicIcon(kbasicControlVistaPath("vista_window_minimize_enabled.png")), tr(""), this); b->setToolTip("Minimize (Window)"); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(vista_window_minimize()));
  b = new QPushButton(kbasicIcon(kbasicControlVistaPath("vista_window_maximize_enabled.png")), tr(""), this); b->setToolTip("Maximize (Window)"); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(vista_window_maximize()));
  b = new QPushButton(kbasicIcon(kbasicControlVistaPath("vista_button_arrowleft.png")), tr(""), this); b->setToolTip("Button (Arrow Left)"); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(vista_button_arrowleft()));
  b = new QPushButton(kbasicIcon(kbasicControlVistaPath("vista_buttonblack_middle.png")), tr(""), this); b->setToolTip("Button Black (Middle)"); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(vista_buttonblack_middle()));
  b = new QPushButton(kbasicIcon(kbasicControlVistaPath("vista_button_arrowright.png")), tr(""), this); b->setToolTip("Button (Arrow Right)"); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(vista_button_arrowright()));
  b = new QPushButton(kbasicIcon(kbasicControlVistaPath("vista_box_black.png")), tr(""), this); b->setToolTip("Box (Black)"); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(vista_box_black()));
  b = new QPushButton(kbasicIcon(kbasicControlVistaPath("vista_box_white.png")), tr(""), this); b->setToolTip("Box (White)"); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(vista_box_white()));
  b = new QPushButton(kbasicIcon(kbasicControlVistaPath("vista_window_light.png")), tr(""), this); b->setToolTip("Window (Light)"); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(vista_window_white()));
  b = new QPushButton(kbasicIcon(kbasicControlVistaPath("vista_icon_search.png")), tr(""), this); b->setToolTip("Icon (Search)"); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(vista_icon_search()));
  b = new QPushButton(kbasicIcon(kbasicControlVistaPath("vista_imagebox_whiteblack.png")), tr(""), this); b->setToolTip("ImageBox (White)"); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(vista_imagebox_whiteblack()));
  b = new QPushButton(kbasicIcon(kbasicControlVistaPath("vista_separator_white.png")), tr(""), this); b->setToolTip("Separator (White)"); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(vista_separator_white()));
  b = new QPushButton(kbasicIcon(kbasicControlVistaPath("vista_separator_black.png")), tr(""), this); b->setToolTip("Separator (Black)"); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(vista_separator_black()));
  b = new QPushButton(kbasicIcon(kbasicControlVistaPath("vista_textbox_whiteblack.png")), tr(""), this); b->setToolTip("TextBox (White & Black)"); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(vista_textbox_whiteblack()));
  b = new QPushButton(kbasicIcon(kbasicControlVistaPath("vista_button_left.png")), tr(""), this); b->setToolTip("Button (Left)"); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(vista_button_left()));
  b = new QPushButton(kbasicIcon(kbasicControlVistaPath("vista_button_middle.png")), tr(""), this); b->setToolTip("Button (Middle)"); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(vista_button_middle()));
  b = new QPushButton(kbasicIcon(kbasicControlVistaPath("vista_button_right.png")), tr(""), this); b->setToolTip("Button (Right)"); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(vista_button_right()));
  b = new QPushButton(kbasicIcon(kbasicControlVistaPath("vista_selection_black.png")), tr(""), this); b->setToolTip("Selection (Black)"); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(vista_selection_black()));
  b = new QPushButton(kbasicIcon(kbasicControlVistaPath("vista_selection_white_enter.png")), tr(""), this); b->setToolTip("Selection (White)"); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(vista_selection_white()));
  b = new QPushButton(kbasicIcon(kbasicControlVistaPath("vista_navigation_bar.png")), tr(""), this); b->setToolTip("Window (Light)"); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(vista_navigation_bar()));
  b = new QPushButton(kbasicIcon(kbasicControlVistaPath("vista_navigation_left_enabled.png")), tr(""), this); b->setToolTip("Navigation (Left)"); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(vista_navigation_left()));
  b = new QPushButton(kbasicIcon(kbasicControlVistaPath("vista_navigation_right_enabled.png")), tr(""), this); b->setToolTip("Navigation (Right)"); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(vista_navigation_right()));

  
  
  // CONTROL

  setLayout(grid);

}

void _toolboxwindow_vista::pointer(){ if (EXTERN_my_form){ EXTERN_my_form->setInsertControlType(t_notype); sInsertTypeOption = ""; }}
void _toolboxwindow_vista::vista_bar(){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_label); sInsertTypeOption = "vista_bar"; }}
void _toolboxwindow_vista::vista_ball(){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_image); sInsertTypeOption = "vista_ball"; }}
void _toolboxwindow_vista::vista_bar_commandbutton(){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_imagebutton); sInsertTypeOption = "vista_bar_commandbutton"; }}
void _toolboxwindow_vista::vista_window_close(){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_imagebutton); sInsertTypeOption = "vista_window_close"; }}
void _toolboxwindow_vista::vista_window_minimize(){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_imagebutton); sInsertTypeOption = "vista_window_minimize"; }}
void _toolboxwindow_vista::vista_window_maximize(){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_imagebutton); sInsertTypeOption = "vista_window_maximize"; }}
void _toolboxwindow_vista::vista_button_arrowright(){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_imagebutton); sInsertTypeOption = "vista_button_arrowright"; }}
void _toolboxwindow_vista::vista_button_arrowleft(){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_imagebutton); sInsertTypeOption = "vista_button_arrowleft"; }}
void _toolboxwindow_vista::vista_box_black(){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_label); sInsertTypeOption = "vista_box_black"; }}
void _toolboxwindow_vista::vista_box_white(){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_label); sInsertTypeOption = "vista_box_white"; }}
void _toolboxwindow_vista::vista_window_white(){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_label); sInsertTypeOption = "vista_window_white"; }}
void _toolboxwindow_vista::vista_icon_search(){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_label); sInsertTypeOption = "vista_icon_search"; }}
void _toolboxwindow_vista::vista_imagebox_whiteblack(){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_label); sInsertTypeOption = "vista_imagebox_whiteblack"; }}
void _toolboxwindow_vista::vista_separator_white(){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_label); sInsertTypeOption = "vista_separator_white"; }}
void _toolboxwindow_vista::vista_separator_black(){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_label); sInsertTypeOption = "vista_separator_black"; }}
void _toolboxwindow_vista::vista_textbox_whiteblack(){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_label); sInsertTypeOption = "vista_textbox_whiteblack"; }}
void _toolboxwindow_vista::vista_button_middle(){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_imagebutton); sInsertTypeOption = "vista_button_middle"; }}
void _toolboxwindow_vista::vista_button_left(){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_imagebutton); sInsertTypeOption = "vista_button_left"; }}
void _toolboxwindow_vista::vista_button_right(){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_imagebutton); sInsertTypeOption = "vista_button_right"; }}
void _toolboxwindow_vista::vista_buttonblack_middle(){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_imagebutton); sInsertTypeOption = "vista_buttonblack_middle"; }}
void _toolboxwindow_vista::vista_selection_black(){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_imagebutton); sInsertTypeOption = "vista_selection_black"; }}
void _toolboxwindow_vista::vista_selection_white(){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_imagebutton); sInsertTypeOption = "vista_selection_white"; }}
void _toolboxwindow_vista::vista_navigation_bar(){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_label); sInsertTypeOption = "vista_navigation_bar"; }}
void _toolboxwindow_vista::vista_navigation_right(){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_imagebutton); sInsertTypeOption = "vista_navigation_right"; }}
void _toolboxwindow_vista::vista_navigation_left(){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_imagebutton); sInsertTypeOption = "vista_navigation_left"; }}

