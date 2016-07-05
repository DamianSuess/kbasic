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

#include "_toolboxwindow_report.h"
#include "../kbshared/_report.h"

_toolboxwindow_report *EXTERN_my_toolboxwindow_report;

extern _report *EXTERN_my_report;
extern _menubar *EXTERN_my_menubar;
extern _toolbar *EXTERN_my_toolbar;

extern QString kbasicControlPath(QString s);
extern const QIcon &kbasicIcon(QString s);

_toolboxwindow_report::_toolboxwindow_report(QWidget *parent) : QWidget(parent)
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
  b = new QPushButton(kbasicIcon(kbasicControlPath("label.png")), tr(""), this); b->setToolTip("Label"); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(label()));
  b = new QPushButton(kbasicIcon(kbasicControlPath("textbox.png")), tr(""), this); b->setToolTip("TextBox"); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(textbox()));
  
  b = new QPushButton(kbasicIcon(kbasicControlPath("checkbox.png")), tr(""), this); b->setToolTip("CheckBox"); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }  ; connect(b, SIGNAL(clicked(bool)), this, SLOT(checkbox()));
  b = new QPushButton(kbasicIcon(kbasicControlPath("frame.png")), tr(""), this); b->setToolTip("Frame"); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(frame()));

  b = new QPushButton(kbasicIcon(kbasicControlPath("image.png")), tr(""), this); b->setToolTip("Image"); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(image()));

  b = new QPushButton(kbasicIcon(kbasicControlPath("editor.png")), tr(""), this); b->setToolTip("Editor"); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(editor()));
  b = new QPushButton(kbasicIcon(kbasicControlPath("datebox.png")), tr(""), this); b->setToolTip("DateBox"); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(datebox()));
  
  b = new QPushButton(kbasicIcon(kbasicControlPath("timebox.png")), tr(""), this); b->setToolTip("TimeBox"); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(timebox()));

  b = new QPushButton(kbasicIcon(kbasicControlPath("header.png")), tr(""), this); b->setToolTip("Header"); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(header()));
  b = new QPushButton(kbasicIcon(kbasicControlPath("footer.png")), tr(""), this); b->setToolTip("Footer"); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(footer()));

  setLayout(grid);


}



void _toolboxwindow_report::pointer(){ if (EXTERN_my_report) EXTERN_my_report->setInsertControlType(t_notype); sInsertTypeOption = ""; }
void _toolboxwindow_report::label(){ if (EXTERN_my_report) EXTERN_my_report->setInsertControlType(t_label); sInsertTypeOption = ""; }
void _toolboxwindow_report::textbox(){ if (EXTERN_my_report) EXTERN_my_report->setInsertControlType(t_textbox); sInsertTypeOption = ""; }
void _toolboxwindow_report::checkbox(){ if (EXTERN_my_report) EXTERN_my_report->setInsertControlType(t_checkbox); sInsertTypeOption = ""; }

void _toolboxwindow_report::frame(){ if (EXTERN_my_report) EXTERN_my_report->setInsertControlType(t_frame); sInsertTypeOption = ""; }

void _toolboxwindow_report::progressbar(){ if (EXTERN_my_report) EXTERN_my_report->setInsertControlType(t_progressbar); sInsertTypeOption = ""; }
void _toolboxwindow_report::image(){ if (EXTERN_my_report) EXTERN_my_report->setInsertControlType(t_image); sInsertTypeOption = ""; }

void _toolboxwindow_report::box(){ if (EXTERN_my_report) EXTERN_my_report->setInsertControlType(t_box); }

void _toolboxwindow_report::editor(){ if (EXTERN_my_report) EXTERN_my_report->setInsertControlType(t_editor); sInsertTypeOption = ""; }
void _toolboxwindow_report::browser(){ if (EXTERN_my_report) EXTERN_my_report->setInsertControlType(t_browser); sInsertTypeOption = ""; }
void _toolboxwindow_report::datebox(){ if (EXTERN_my_report) EXTERN_my_report->setInsertControlType(t_datebox); sInsertTypeOption = ""; }
void _toolboxwindow_report::timebox(){ if (EXTERN_my_report) EXTERN_my_report->setInsertControlType(t_timebox); sInsertTypeOption = ""; }
void _toolboxwindow_report::datetimebox(){ if (EXTERN_my_report) EXTERN_my_report->setInsertControlType(t_datetimebox); sInsertTypeOption = ""; }

void _toolboxwindow_report::header(){ if (EXTERN_my_report) EXTERN_my_report->setInsertControlType(t_header); sInsertTypeOption = ""; }
void _toolboxwindow_report::footer(){ if (EXTERN_my_report) EXTERN_my_report->setInsertControlType(t_footer); sInsertTypeOption = ""; }
