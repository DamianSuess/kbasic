/*
***************************************************************************
Copyright (C) 2000-2007 KBasic Software: www.kbasic.com. All rights reserved.
Source codes are copyrighted by Bernd Noetscher 2000 - 2007.

You may use this source codes under the terms of the GNU Public License (Version 2) as published 
by the Free Software Foundation. 

If you are interested in using the source codes for other licenses or 
commercial development, you must buy commercial licenses from KBasic Software.
***************************************************************************
*/

#include <QtGui>

#include "_toolboxwindow_sql.h"
#include "../kbshared/_form.h"

extern QString kbasicPath(QString sPath);

_toolboxwindow_sql *EXTERN_my_toolboxwindow_sql;


extern _form *EXTERN_my_form;

extern const QIcon &kbasicIcon(QString s);
extern QString kbasicControlPath(QString s);

_toolboxwindow_sql::_toolboxwindow_sql(QWidget *parent) : QWidget(parent)
{
  setAutoFillBackground(true);

  QPalette p = palette();
  p.setColor(QPalette::Window, Qt::white);  
  p.setColor(QPalette::Base, Qt::white);  
  p.setColor(QPalette::Button, Qt::white);            
  setPalette(p);

  //EXTERN_my_toolboxwindow_sql = this;
  QGridLayout *grid = new QGridLayout(this);
  grid->setMargin(1);
  grid->setSpacing(1);
  setLayout(grid);

  QPushButton *b;
  int x = 0;
  int y = 0;
//  setMaximumHeight(36 * 5);

  b = new QPushButton(kbasicIcon(kbasicControlPath("pointer.png")), tr(""), this); b->setToolTip("Select"); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(pointer()));
  
  b = new QPushButton(kbasicIcon(kbasicControlPath("SQLFirst.png")), tr(""), this); b->setToolTip("First"); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(SQLFirst()));
  b = new QPushButton(kbasicIcon(kbasicControlPath("SQLNext.png")), tr(""), this); b->setToolTip("Next"); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(SQLNext()));
  b = new QPushButton(kbasicIcon(kbasicControlPath("SQLPrevious.png")), tr(""), this); b->setToolTip("Previous"); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(SQLPrevious()));
  b = new QPushButton(kbasicIcon(kbasicControlPath("SQLLast.png")), tr(""), this); b->setToolTip("Last"); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(SQLLast()));
  b = new QPushButton(kbasicIcon(kbasicControlPath("SQLInsert.png")), tr(""), this); b->setToolTip("Insert"); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(SQLInsert()));
  b = new QPushButton(kbasicIcon(kbasicControlPath("SQLUpdate.png")), tr(""), this); b->setToolTip("Update"); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(SQLUpdate()));
  b = new QPushButton(kbasicIcon(kbasicControlPath("SQLDelete.png")), tr(""), this); b->setToolTip("Delete"); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(SQLDelete()));
  b = new QPushButton(kbasicIcon(kbasicControlPath("SQLGoTo.png")), tr(""), this); b->setToolTip("GoTo"); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(SQLGoTo()));
  b = new QPushButton(kbasicIcon(kbasicControlPath("SQLInfo.png")), tr(""), this); b->setToolTip("Info"); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(SQLInfo()));
  b = new QPushButton(kbasicIcon(kbasicControlPath("SQLRequery.png")), tr(""), this); b->setToolTip("Requery"); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(SQLRequery()));
  b = new QPushButton(kbasicIcon(kbasicControlPath("SQLAll.png")), tr(""), this); b->setToolTip("All"); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(SQLAll()));

  setLayout(grid);

/*
  setUniformItemSizes(true);
  setWrapping(true);
  setFlow(QListView::LeftToRight);
  setViewMode(QListView::IconMode);
  setMovement(QListView::Static);
  setGridSize(QSize(320, 320));*/
/*
  QGridLayout *grid = new QGridLayout(this);
  grid->setMargin(1);
  grid->setSpacing(1);
  setLayout(grid);*/
  /*
  //QWidget *fr = new QWidget();

  QGridLayout *grid = new QGridLayout();
  grid->setMargin(1);
  grid->setSpacing(1);
  this->setLayout(grid);

  QScrollArea *a = new QScrollArea(this);
  a->setWidget(this);
  a->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
  a->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded); 
  //a->setMinimumHeight(300);
  a->setWidgetResizable(true);
*/
/*
  QPushButton *b;
  int x = 0;
  int y = 0;
  b = new QPushButton(kbasicIcon(kbasicControlPath("pointer.png")), tr(""), this); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }
  b = new QPushButton(kbasicIcon(kbasicControlPath("commandbutton.png")), tr(""), this); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }
  b = new QPushButton(kbasicIcon(kbasicControlPath("label.png")), tr(""), this); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }
  b = new QPushButton(kbasicIcon(kbasicControlPath("textbox.png")), tr(""), this); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }
  
  b = new QPushButton(kbasicIcon(kbasicControlPath("checkbox.png")), tr(""), this); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }  
  b = new QPushButton(kbasicIcon(kbasicControlPath("radiobutton.png")), tr(""), this); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }  
  b = new QPushButton(kbasicIcon(kbasicControlPath("frame.png")), tr(""), this); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }
  b = new QPushButton(kbasicIcon(kbasicControlPath("listbox.png")), tr(""), this); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }
  b = new QPushButton(kbasicIcon(kbasicControlPath("combobox.png")), tr(""), this); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }

  b = new QPushButton(kbasicIcon(kbasicControlPath("tab.png")), tr(""), this); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }
  b = new QPushButton(kbasicIcon(kbasicControlPath("frame.png")), tr(""), this); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }
  b = new QPushButton(kbasicIcon(kbasicControlPath("progressbar.png")), tr(""), this); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }
  b = new QPushButton(kbasicIcon(kbasicControlPath("image.png")), tr(""), this); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }

  b = new QPushButton(kbasicIcon(kbasicControlPath("hidden.png")), tr(""), this); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }
  b = new QPushButton(kbasicIcon(kbasicControlPath("timer.png")), tr(""), this); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }
  b = new QPushButton(kbasicIcon(kbasicControlPath("treeview.png")), tr(""), this); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }
  b = new QPushButton(kbasicIcon(kbasicControlPath("imagebutton.png")), tr(""), this); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }

  b = new QPushButton(kbasicIcon(kbasicControlPath("vbox.png")), tr(""), this); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }
  b = new QPushButton(kbasicIcon(kbasicControlPath("hbox.png")), tr(""), this); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }
  b = new QPushButton(kbasicIcon(kbasicControlPath("vhbox.png")), tr(""), this); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }
  b = new QPushButton(kbasicIcon(kbasicControlPath("vsplit.png")), tr(""), this); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }
  
  b = new QPushButton(kbasicIcon(kbasicControlPath("hsplit.png")), tr(""), this); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }
  b = new QPushButton(kbasicIcon(kbasicControlPath("box.png")), tr(""), this); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }
  b = new QPushButton(kbasicIcon(kbasicControlPath("childcontrol.png")), tr(""), this); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }
  b = new QPushButton(kbasicIcon(kbasicControlPath("customcontrol.png")), tr(""), this); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }

  b = new QPushButton(kbasicIcon(kbasicControlPath("scrollbox.png")), tr(""), this); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }
  b = new QPushButton(kbasicIcon(kbasicControlPath("editor.png")), tr(""), this); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }
  b = new QPushButton(kbasicIcon(kbasicControlPath("browser.png")), tr(""), this); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }
  b = new QPushButton(kbasicIcon(kbasicControlPath("datebox.png")), tr(""), this); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }
  
  b = new QPushButton(kbasicIcon(kbasicControlPath("timebox.png")), tr(""), this); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }
  b = new QPushButton(kbasicIcon(kbasicControlPath("datetimebox.png")), tr(""), this); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }
*/
  /*
  connect(this, SIGNAL(currentTextChanged(const QString &)), this, SLOT(currentTextChanged(const QString &)));
  
  setIconSize(QSize(32, 32));

  QListWidgetItem *l = 0;

  

  l = new QListWidgetItem(kbasicIcon(kbasicControlPath("pointer.png")), tr("Select")); 
    
  addItem(l);
  addItem(new QListWidgetItem(tr("")));
  addItem(new QListWidgetItem(kbasicIcon(kbasicControlPath("commandbutton.png")), tr("CommandButton")));
  addItem(new QListWidgetItem(kbasicIcon(kbasicControlPath("label.png")), tr("Label")));
  addItem(new QListWidgetItem(kbasicIcon(kbasicControlPath("textbox.png")), tr("TextBox")));
  addItem(new QListWidgetItem(tr("")));
  addItem(new QListWidgetItem(kbasicIcon(kbasicControlPath("checkbox.png")), tr("CheckBox")));
  addItem(new QListWidgetItem(kbasicIcon(kbasicControlPath("radiobutton.png")), tr("RadioButton")));
  addItem(new QListWidgetItem(tr("")));
  addItem(new QListWidgetItem(kbasicIcon(kbasicControlPath("frame.png")), tr("Frame")));
  addItem(new QListWidgetItem(kbasicIcon(kbasicControlPath("listbox.png")), tr("ListBox")));
  addItem(new QListWidgetItem(kbasicIcon(kbasicControlPath("combobox.png")), tr("ComboBox")));
  addItem(new QListWidgetItem(tr("")));
  addItem(new QListWidgetItem(kbasicIcon(kbasicControlPath("tab.png")), tr("Tab")));
  addItem(new QListWidgetItem(kbasicIcon(kbasicControlPath("progressbar.png")), tr("ProgressBar")));
  addItem(new QListWidgetItem(kbasicIcon(kbasicControlPath("image.png")), tr("Image")));
  addItem(new QListWidgetItem(tr("")));
  addItem(new QListWidgetItem(kbasicIcon(kbasicControlPath("hidden.png")), tr("Hidden")));
  //addItem(new QListWidgetItem(kbasicIcon(kbasicControlPath("activex.png")), tr("(ActiveX)")));
  addItem(new QListWidgetItem(tr("")));
  addItem(new QListWidgetItem(kbasicIcon(kbasicControlPath("timer.png")), tr("Timer")));
  addItem(new QListWidgetItem(kbasicIcon(kbasicControlPath("treeview.png")), tr("(TreeView)")));
  addItem(new QListWidgetItem(tr("")));
  addItem(new QListWidgetItem(kbasicIcon(kbasicControlPath("imagebutton.png")), tr("ImageButton")));
  addItem(new QListWidgetItem(tr("")));
  addItem(new QListWidgetItem(kbasicIcon(kbasicControlPath("vbox.png")), tr("VBox")));
  addItem(new QListWidgetItem(kbasicIcon(kbasicControlPath("hbox.png")), tr("HBox")));
  //addItem(new QListWidgetItem(kbasicIcon(kbasicControlPath("vhbox.png")), tr("(VHBox)")));
  addItem(new QListWidgetItem(kbasicIcon(kbasicControlPath("vsplit.png")), tr("VSplit")));
  addItem(new QListWidgetItem(kbasicIcon(kbasicControlPath("hsplit.png")), tr("HSplit")));
  addItem(new QListWidgetItem(tr("")));
  addItem(new QListWidgetItem(kbasicIcon(kbasicControlPath("box.png")), tr("Box")));
  addItem(new QListWidgetItem(kbasicIcon(kbasicControlPath("childcontrol.png")), tr("(ChildControl)")));
  addItem(new QListWidgetItem(kbasicIcon(kbasicControlPath("customcontrol.png")), tr("CustomControl")));
  //addItem(new QListWidgetItem(kbasicIcon(kbasicControlPath("scrollbox.png")), tr("(ScrollBox)")));
  addItem(new QListWidgetItem(tr("")));
  addItem(new QListWidgetItem(kbasicIcon(kbasicControlPath("editor.png")), tr("Editor")));
  addItem(new QListWidgetItem(kbasicIcon(kbasicControlPath("browser.png")), tr("Browser")));
  addItem(new QListWidgetItem(tr("")));
  addItem(new QListWidgetItem(kbasicIcon(kbasicControlPath("datebox.png")), tr("DateBox")));
  addItem(new QListWidgetItem(kbasicIcon(kbasicControlPath("timebox.png")), tr("TimeBox")));
  addItem(new QListWidgetItem(kbasicIcon(kbasicControlPath("datetimebox.png")), tr("DateTimeBox")));
*/
}
/*
_toolboxwindow_sql::~_toolboxwindow_sql(void)
{
}
*/


void _toolboxwindow_sql::pointer(){ 
  if (EXTERN_my_form) EXTERN_my_form->setInsertControlType(t_notype); 
}

void _toolboxwindow_sql::SQLInsert()
{ 
  if (EXTERN_my_form) EXTERN_my_form->setInsertControlType(t_SQLInsert); 
}

void _toolboxwindow_sql::SQLNext()
{ 
  if (EXTERN_my_form) EXTERN_my_form->setInsertControlType(t_SQLNext); 
}

void _toolboxwindow_sql::SQLPrevious()
{ 
  if (EXTERN_my_form) EXTERN_my_form->setInsertControlType(t_SQLPrevious); 
}

void _toolboxwindow_sql::SQLUpdate()
{ 
  if (EXTERN_my_form) EXTERN_my_form->setInsertControlType(t_SQLUpdate); 
}

void _toolboxwindow_sql::SQLDelete()
{ 
  if (EXTERN_my_form) EXTERN_my_form->setInsertControlType(t_SQLDelete); 
}

void _toolboxwindow_sql::SQLFirst()
{ 
  if (EXTERN_my_form) EXTERN_my_form->setInsertControlType(t_SQLFirst); 
}

void _toolboxwindow_sql::SQLLast()
{ 
  if (EXTERN_my_form) EXTERN_my_form->setInsertControlType(t_SQLLast); 
}

void _toolboxwindow_sql::SQLGoTo()
{ 
  if (EXTERN_my_form) EXTERN_my_form->setInsertControlType(t_SQLGoTo); 
}

void _toolboxwindow_sql::SQLInfo()
{ 
  if (EXTERN_my_form) EXTERN_my_form->setInsertControlType(t_SQLInfo);
}

void _toolboxwindow_sql::SQLAll()
{ 
  if (EXTERN_my_form) EXTERN_my_form->setInsertControlType(t_SQLAll);
}

void _toolboxwindow_sql::SQLRequery()
{ 
  if (EXTERN_my_form) EXTERN_my_form->setInsertControlType(t_SQLRequery);
}






/*
void _toolboxwindow_sql::currentTextChanged ( const QString & currentText )
{
  _form *my_form = qobject_cast<_form *>(EXTERN_my_mainwindow->workspace->activeWindow());

  if (my_form){
    
    
    if (currentText == tr("Select")) my_form->setInsertControlType(t_t_notype);
    else if (currentText == tr("Label")) my_form->setInsertControlType(t_t_label);
    else if (currentText == tr("CommandButton")) my_form->setInsertControlType(t_t_commandbutton);
    else if (currentText == tr("CheckBox")) my_form->setInsertControlType(t_t_checkbox);
    else if (currentText == tr("RadioButton")) my_form->setInsertControlType(t_t_radiobutton);
    else if (currentText == tr("TextBox")) my_form->setInsertControlType(t_t_textbox);
    else if (currentText == tr("Frame")) my_form->setInsertControlType(t_t_frame);
    else if (currentText == tr("ListBox")) my_form->setInsertControlType(t_t_listbox);
    else if (currentText == tr("ComboBox")) my_form->setInsertControlType(t_t_combobox);
    else if (currentText == tr("Tab")) my_form->setInsertControlType(t_t_tab);
    else if (currentText == tr("ProgressBar")) my_form->setInsertControlType(t_t_progressbar);
    else if (currentText == tr("Image")) my_form->setInsertControlType(t_t_image);
    else if (currentText == tr("Hidden")) my_form->setInsertControlType(t_t_hidden);
    else if (currentText == tr("Timer")) my_form->setInsertControlType(t_t_timer);
    else if (currentText == tr("TreeView")) my_form->setInsertControlType(t_t_treeview);
    else if (currentText == tr("ImageButton")) my_form->setInsertControlType(t_t_imagebutton);
    else if (currentText == tr("VBox")) my_form->setInsertControlType(t_t_vbox);
    else if (currentText == tr("HBox")) my_form->setInsertControlType(t_t_hbox);
    else if (currentText == tr("VHBox")) my_form->setInsertControlType(t_t_vhbox);
    else if (currentText == tr("VSplit")) my_form->setInsertControlType(t_t_vsplit);
    else if (currentText == tr("HSplit")) my_form->setInsertControlType(t_t_hsplit);

    else if (currentText == tr("Box")) my_form->setInsertControlType(t_t_box);
    else if (currentText == tr("ChildControl")) my_form->setInsertControlType(t_t_childcontrol);
    else if (currentText == tr("CustomControl")) my_form->setInsertControlType(t_t_customcontrol);
    else if (currentText == tr("ScrollBox")) my_form->setInsertControlType(t_t_scrollbox);
    else if (currentText == tr("Editor")) my_form->setInsertControlType(t_t_editor);
    else if (currentText == tr("Browser")) my_form->setInsertControlType(t_t_browser);
    else if (currentText == tr("DateBox")) my_form->setInsertControlType(t_t_datebox);
    else if (currentText == tr("TimeBox")) my_form->setInsertControlType(t_t_timebox);
    else if (currentText == tr("DateTimeBox")) my_form->setInsertControlType(t_t_datetimebox);
    else my_form->setInsertControlType(t_t_notype);
  }
}

void _toolboxwindow_sql::set_Select()
{  
  QList<QListWidgetItem *> l = findItems("Select", Qt::MatchExactly);
  for (int i = 0; i < l.size(); ++i){
    setCurrentItem(l.at(i));
    //EXTERN_my_form->setInsertControlType(t_t_notype);
    return;
  }
}

void _toolboxwindow_sql::set(QString s)
{
  
  QList<QListWidgetItem *> l = findItems(s, Qt::MatchContains);
  for (int i = 0; i < l.size(); ++i){
    setCurrentItem(l.at(i));
    //EXTERN_my_form->setInsertControlType(t_t_notype);
    return;
  }
}*/