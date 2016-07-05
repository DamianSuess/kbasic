/*
***************************************************************************
Copyright (C) 2000-2008 KBasic Software: www.kbasic.com. All rights reserved.
Source codes are copyrighted by Bernd Noetscher 2000-2008.

You may use this source codes under the terms of the GNU Public License (Version 3) 
as published by the Free Software Foundation. 

If you are interested in using the source codes for other licenses or 
commercial development, you must buy commercial licenses from KBasic Software.
***************************************************************************
*/

#include "_toolboxwindow_form.h"

#include "../kbshared/_form.h"


_toolboxwindow_form *EXTERN_my_toolboxwindow_form;
extern _mainwindow *EXTERN_my_mainwindow;

extern QString sInsertTypeOption;

extern _form *EXTERN_my_form;
extern _menubar *EXTERN_my_menubar;
extern _toolbar *EXTERN_my_toolbar;

extern const QIcon &kbasicIcon(QString s);
extern QString kbasicControlPath(QString s);

bool bInfo;

#define MSG if(bInfo){QMessageBox::information(this,MYAPP,tr("Please click on the position, \nwhere the control is to be inserted."));bInfo=false;}

_toolboxwindow_form::_toolboxwindow_form(QWidget *parent) : QListWidget(parent)
{
  bInfo = EXTERN_my_mainwindow->isPreferenceSet("IntroductionHelp");
  //setAutoFillBackground(true);

  //setSelectionRectVisible(false);

  setIconSize(QSize(34, 34));
 // setViewMode(QListView::IconMode);
 // setMovement(QListView::Static);

  connect(this, SIGNAL(currentRowChanged  (int)), this, SLOT(currentRowChanged (int)));
 // connect(this, SIGNAL(currentItemChanged  (QListWidgetItem *, QListWidgetItem *)), this, SLOT(currentItemChanged (QListWidgetItem *, QListWidgetItem *)));


 // connect(this, SIGNAL(itemActivated  (QListWidgetItem *, )), this, SLOT(itemActivated (QListWidgetItem *, 0)));

   


  QListWidgetItem *l;

  l = new QListWidgetItem(kbasicIcon(kbasicControlPath("pointer.png")), tr("Select")); l->setData(Qt::UserRole, QVariant("pointer")); l->setToolTip(tr("Select")); addItem(l);
  l = new QListWidgetItem(kbasicIcon(kbasicControlPath("commandbutton.png")), tr("CommandButton")); l->setData(Qt::UserRole, QVariant("commandbutton")); l->setToolTip(tr("CommandButton")); addItem(l);


  l = new QListWidgetItem(kbasicIcon(kbasicControlPath("label.png")), tr("Label")); l->setData(Qt::UserRole, QVariant("label")); l->setToolTip("Label");  addItem(l);
  l = new QListWidgetItem(kbasicIcon(kbasicControlPath("textbox.png")), tr("TextBox")); l->setData(Qt::UserRole, QVariant("textbox")); l->setToolTip("TextBox");  addItem(l);
  
  l = new QListWidgetItem(kbasicIcon(kbasicControlPath("checkbox.png")), tr("CheckBox")); l->setData(Qt::UserRole, QVariant("checkbox")); l->setToolTip("CheckBox"); addItem(l);
  l = new QListWidgetItem(kbasicIcon(kbasicControlPath("radiobutton.png")), tr("RadioButton")); l->setData(Qt::UserRole, QVariant("radiobutton")); l->setToolTip("RadioButton");  addItem(l);
  l = new QListWidgetItem(kbasicIcon(kbasicControlPath("frame.png")), tr("Frame")); l->setData(Qt::UserRole, QVariant("frame")); l->setToolTip("Frame"); addItem(l);
  l = new QListWidgetItem(kbasicIcon(kbasicControlPath("listbox.png")), tr("ListBox")); l->setData(Qt::UserRole, QVariant("listbox")); l->setToolTip("ListBox");  addItem(l);
  l = new QListWidgetItem(kbasicIcon(kbasicControlPath("listbox_iconmode.png")), tr("ListBox (IconMode)"), this); l->setData(Qt::UserRole, QVariant("listbox_iconmode")); l->setToolTip("ListBox (IconMode)"); addItem(l);
  l = new QListWidgetItem(kbasicIcon(kbasicControlPath("combobox.png")), tr("ComboBox")); l->setData(Qt::UserRole, QVariant("combobox")); l->setToolTip("ComboBox"); addItem(l);
  l = new QListWidgetItem(kbasicIcon(kbasicControlPath("combobox_editable.png")), tr("ComboBox (Editable)"), this); l->setData(Qt::UserRole, QVariant("combobox_editable")); l->setToolTip("ComboBox (Editable)");addItem(l);

  l = new QListWidgetItem(kbasicIcon(kbasicControlPath("tabview.png")), tr("TabView")); l->setData(Qt::UserRole, QVariant("tab")); l->setToolTip("TabView");  addItem(l);
  l = new QListWidgetItem(kbasicIcon(kbasicControlPath("progressbar.png")), tr("ProgressBar")); l->setData(Qt::UserRole, QVariant("progressbar")); l->setToolTip("ProgressBar"); addItem(l);
  l = new QListWidgetItem(kbasicIcon(kbasicControlPath("progressbar_spinning.png")), tr("ProgressBar (Spinning)"), this); l->setData(Qt::UserRole, QVariant("progressbar_spinning")); l->setToolTip("ProgressBar (Spinning)"); addItem(l);
  l = new QListWidgetItem(kbasicIcon(kbasicControlPath("image.png")), tr("ImageBox")); l->setData(Qt::UserRole, QVariant("image")); l->setToolTip("ImageBox"); addItem(l);

  l = new QListWidgetItem(kbasicIcon(kbasicControlPath("timer.png")), tr("Timer")); l->setData(Qt::UserRole, QVariant("timer")); l->setToolTip("Timer");  addItem(l);
  l = new QListWidgetItem(kbasicIcon(kbasicControlPath("treeview.png")), tr("TreeView")); l->setData(Qt::UserRole, QVariant("treeview")); l->setToolTip("TreeView");  addItem(l);
  l = new QListWidgetItem(kbasicIcon(kbasicControlPath("treeview_listview.png")), tr("ListView (TreeView)"), this);l->setData(Qt::UserRole, QVariant("treeview_listview")); l->setToolTip("ListView (TreeView)");  addItem(l);
  l = new QListWidgetItem(kbasicIcon(kbasicControlPath("imagebutton.png")), tr("ImageButton")); l->setData(Qt::UserRole, QVariant("imagebutton")); l->setToolTip("ImageButton");  addItem(l);


  l = new QListWidgetItem(kbasicIcon(kbasicControlPath("box.png")), tr("Box")); l->setData(Qt::UserRole, QVariant("box")); l->setToolTip("Box");  addItem(l);
  l = new QListWidgetItem(kbasicIcon(kbasicControlPath("textbox_password.png")), tr("Password (TextBox)")); l->setData(Qt::UserRole, QVariant("textbox_password")); l->setToolTip("Password (TextBox)");  addItem(l);
  l = new QListWidgetItem(kbasicIcon(kbasicControlPath("label_link.png")), tr("Link (Label)")); l->setData(Qt::UserRole, QVariant("label_link")); l->setToolTip("Link (Label)"); addItem(l);
  l = new QListWidgetItem(kbasicIcon(kbasicControlPath("line_vertical.png")), tr("Vertical Line")); l->setData(Qt::UserRole, QVariant("line_vertical")); l->setToolTip("Vertical Line");  addItem(l);
  l = new QListWidgetItem(kbasicIcon(kbasicControlPath("line_horizontal.png")), tr("Horizontal Line")); l->setData(Qt::UserRole, QVariant("line_horizontal")); l->setToolTip("Horizontal Line");  addItem(l);
  l = new QListWidgetItem(kbasicIcon(kbasicControlPath("formview.png")), tr("FormView")); l->setData(Qt::UserRole, QVariant("childcontrol")); l->setToolTip("FormView");  addItem(l);

  l = new QListWidgetItem(kbasicIcon(kbasicControlPath("toolbutton.png")), tr("ToolButton")); l->setData(Qt::UserRole, QVariant("toolbutton")); l->setToolTip("ToolButton");  addItem(l);
  l = new QListWidgetItem(kbasicIcon(kbasicControlPath("editor.png")), tr("RichTextBox")); l->setData(Qt::UserRole, QVariant("editor")); l->setToolTip("RichTextBox");  addItem(l);
  l = new QListWidgetItem(kbasicIcon(kbasicControlPath("browser.png")), tr("HtmlView")); l->setData(Qt::UserRole, QVariant("browser")); l->setToolTip("HtmlView");  addItem(l);
  l = new QListWidgetItem(kbasicIcon(kbasicControlPath("datebox.png")), tr("DateBox")); l->setData(Qt::UserRole, QVariant("datebox")); l->setToolTip("DateBox");  addItem(l);
  
  l = new QListWidgetItem(kbasicIcon(kbasicControlPath("timebox.png")), tr("TimeBox")); l->setData(Qt::UserRole, QVariant("timebox")); l->setToolTip("TimeBox"); addItem(l);
  l = new QListWidgetItem(kbasicIcon(kbasicControlPath("datetimebox.png")), tr("DateTimeBox")); l->setData(Qt::UserRole, QVariant("datetimebox")); l->setToolTip("DateTimeBox");  addItem(l);
  // CONTROL
  l = new QListWidgetItem(kbasicIcon(kbasicControlPath("slider.png")), tr("Slider")); l->setData(Qt::UserRole, QVariant("slider")); l->setToolTip("Slider"); addItem(l);
  l = new QListWidgetItem(kbasicIcon(kbasicControlPath("scrollbar.png")), tr("ScrollBar")); l->setData(Qt::UserRole, QVariant("scrollbar")); l->setToolTip("ScrollBar");  addItem(l);
  l = new QListWidgetItem(kbasicIcon(kbasicControlPath("spinbox.png")), tr("SpinBox")); l->setData(Qt::UserRole, QVariant("spinbox")); l->setToolTip("SpinBox"); addItem(l);
  l = new QListWidgetItem(kbasicIcon(kbasicControlPath("serialport.png")), tr("SerialPort")); l->setData(Qt::UserRole, QVariant("serialport")); l->setToolTip("SerialPort"); addItem(l);
  l = new QListWidgetItem(kbasicIcon(kbasicControlPath("movie.png")), tr("MovieBox")); l->setData(Qt::UserRole, QVariant("movie")); l->setToolTip("MovieBox");  addItem(l);
  l = new QListWidgetItem(kbasicIcon(kbasicControlPath("sound.png")), tr("Sound")); l->setData(Qt::UserRole, QVariant("sound")); l->setToolTip("Sound");  addItem(l);
  l = new QListWidgetItem(kbasicIcon(kbasicControlPath("web.png")), tr("WebView")); l->setData(Qt::UserRole, QVariant("web")); l->setToolTip("WebView"); addItem(l);
  l = new QListWidgetItem(kbasicIcon(kbasicControlPath("resizebox.png")), tr("ResizeBox")); l->setData(Qt::UserRole, QVariant("resizebox")); l->setToolTip("ResizeBox");  addItem(l);
  l = new QListWidgetItem(kbasicIcon(kbasicControlPath("commandlinkbutton.png")), tr("CommandLinkButton")); l->setData(Qt::UserRole, QVariant("commandlinkbutton")); l->setToolTip("CommandLinkButton"); addItem(l);
  l = new QListWidgetItem(kbasicIcon(kbasicControlPath("svg.png")), tr("SvgBox")); l->setData(Qt::UserRole, QVariant("svg")); l->setToolTip("SvgBox");  addItem(l);
  l = new QListWidgetItem(kbasicIcon(kbasicControlPath("toolbarview.png")), tr("ToolBarView")); l->setData(Qt::UserRole, QVariant("toolbarview")); l->setToolTip("ToolBarView"); addItem(l);
  l = new QListWidgetItem(kbasicIcon(kbasicControlPath("formsview.png")), tr("FormsView")); l->setData(Qt::UserRole, QVariant("formsview")); l->setToolTip("FormsView");  addItem(l);
  l = new QListWidgetItem(kbasicIcon(kbasicControlPath("udpsocket.png")), tr("UdpSocket")); l->setData(Qt::UserRole, QVariant("udpsocket")); l->setToolTip("UdpSocket");  addItem(l);
  

/*
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
  b = new QPushButton(kbasicIcon(kbasicControlPath("commandbutton.png")), tr(""), this); b->setToolTip("CommandButton"); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(commandbutton()));
  b = new QPushButton(kbasicIcon(kbasicControlPath("label.png")), tr(""), this); b->setToolTip("Label"); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(label()));
  b = new QPushButton(kbasicIcon(kbasicControlPath("textbox.png")), tr(""), this); b->setToolTip("TextBox"); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(textbox()));
  
  b = new QPushButton(kbasicIcon(kbasicControlPath("checkbox.png")), tr(""), this); b->setToolTip("CheckBox"); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }  ; connect(b, SIGNAL(clicked(bool)), this, SLOT(checkbox()));
  b = new QPushButton(kbasicIcon(kbasicControlPath("radiobutton.png")), tr(""), this); b->setToolTip("RadioButton"); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }  ; connect(b, SIGNAL(clicked(bool)), this, SLOT(radiobutton()));
  b = new QPushButton(kbasicIcon(kbasicControlPath("frame.png")), tr(""), this); b->setToolTip("Frame"); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(frame()));
  b = new QPushButton(kbasicIcon(kbasicControlPath("listbox.png")), tr(""), this); b->setToolTip("ListBox"); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(listbox()));
  b = new QPushButton(kbasicIcon(kbasicControlPath("listbox_iconmode.png")), tr(""), this); b->setToolTip("ListBox (IconMode)"); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(listbox_iconmode()));
  b = new QPushButton(kbasicIcon(kbasicControlPath("combobox.png")), tr(""), this); b->setToolTip("ComboBox"); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(combobox()));
  b = new QPushButton(kbasicIcon(kbasicControlPath("combobox_editable.png")), tr(""), this); b->setToolTip("ComboBox (Editable)"); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(combobox_editable()));

  b = new QPushButton(kbasicIcon(kbasicControlPath("tabview.png")), tr(""), this); b->setToolTip("TabView"); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(tab()));
  //b = new QPushButton(kbasicIcon(kbasicControlPath("frame.png")), tr(""), this); b->setToolTip("Frame"); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(frame()));
  b = new QPushButton(kbasicIcon(kbasicControlPath("progressbar.png")), tr(""), this); b->setToolTip("ProgressBar"); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(progressbar()));
  b = new QPushButton(kbasicIcon(kbasicControlPath("progressbar_spinning.png")), tr(""), this); b->setToolTip("ProgressBar (Spinning)"); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(progressbar_spinning()));
  b = new QPushButton(kbasicIcon(kbasicControlPath("image.png")), tr(""), this); b->setToolTip("ImageBox"); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(image()));

  //b = new QPushButton(kbasicIcon(kbasicControlPath("hidden.png")), tr(""), this); b->setToolTip("Hidden"); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(hidden()));
  b = new QPushButton(kbasicIcon(kbasicControlPath("timer.png")), tr(""), this); b->setToolTip("Timer"); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(timer()));
  b = new QPushButton(kbasicIcon(kbasicControlPath("treeview.png")), tr(""), this); b->setToolTip("TreeView"); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(treeview()));
  b = new QPushButton(kbasicIcon(kbasicControlPath("treeview_listview.png")), tr(""), this); b->setToolTip("ListView (TreeView)"); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(treeview_listview()));
  b = new QPushButton(kbasicIcon(kbasicControlPath("imagebutton.png")), tr(""), this); b->setToolTip("ImageButton"); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(imagebutton()));

  //b = new QPushButton(kbasicIcon(kbasicControlPath("vbox.png")), tr(""), this); b->setToolTip("VBox"); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(vbox()));
  //b = new QPushButton(kbasicIcon(kbasicControlPath("hbox.png")), tr(""), this); b->setToolTip("HBox"); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(hbox()));
  //b = new QPushButton(kbasicIcon(kbasicControlPath("vhbox.png")), tr(""), this); b->setToolTip("VHBox"); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(vhbox()));
  //b = new QPushButton(kbasicIcon(kbasicControlPath("vsplit.png")), tr(""), this); b->setToolTip("VSplit"); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(vsplit()));
  
  //b = new QPushButton(kbasicIcon(kbasicControlPath("hsplit.png")), tr(""), this); b->setToolTip("HSplit"); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(hsplit()));
  b = new QPushButton(kbasicIcon(kbasicControlPath("box.png")), tr(""), this); b->setToolTip("Box"); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(box()));
  b = new QPushButton(kbasicIcon(kbasicControlPath("textbox_password.png")), tr(""), this); b->setToolTip("Password (TextBox)"); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(textbox_password()));
  b = new QPushButton(kbasicIcon(kbasicControlPath("label_link.png")), tr(""), this); b->setToolTip("Link (Label)"); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(label_link()));
  b = new QPushButton(kbasicIcon(kbasicControlPath("line_vertical.png")), tr(""), this); b->setToolTip("Vertical Line"); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(line_vertical()));
  b = new QPushButton(kbasicIcon(kbasicControlPath("line_horizontal.png")), tr(""), this); b->setToolTip("Horizontal Line"); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(line_horizontal()));
  b = new QPushButton(kbasicIcon(kbasicControlPath("formview.png")), tr(""), this); b->setToolTip("FormView"); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(childcontrol()));
  //b = new QPushButton(kbasicIcon(kbasicControlPath("customcontrol.png")), tr(""), this); b->setToolTip("CustomControl"); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(customcontrol()));

  //b = new QPushButton(kbasicIcon(kbasicControlPath("scrollbox.png")), tr(""), this); b->setToolTip("ScrollBox"); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(scrollbox()));
  b = new QPushButton(kbasicIcon(kbasicControlPath("toolbutton.png")), tr(""), this); b->setToolTip("ToolButton"); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(toolbutton()));
  b = new QPushButton(kbasicIcon(kbasicControlPath("editor.png")), tr(""), this); b->setToolTip("RichTextBox"); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(editor()));
  b = new QPushButton(kbasicIcon(kbasicControlPath("browser.png")), tr(""), this); b->setToolTip("HtmlView"); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(browser()));
  b = new QPushButton(kbasicIcon(kbasicControlPath("datebox.png")), tr(""), this); b->setToolTip("DateBox"); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(datebox()));
  
  b = new QPushButton(kbasicIcon(kbasicControlPath("timebox.png")), tr(""), this); b->setToolTip("TimeBox"); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(timebox()));
  b = new QPushButton(kbasicIcon(kbasicControlPath("datetimebox.png")), tr(""), this); b->setToolTip("DateTimeBox"); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(datetimebox()));
  // CONTROL
  b = new QPushButton(kbasicIcon(kbasicControlPath("slider.png")), tr(""), this); b->setToolTip("Slider"); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(slider()));
  b = new QPushButton(kbasicIcon(kbasicControlPath("scrollbar.png")), tr(""), this); b->setToolTip("ScrollBar"); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(scrollbar()));
  b = new QPushButton(kbasicIcon(kbasicControlPath("spinbox.png")), tr(""), this); b->setToolTip("SpinBox"); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(spinbox()));
  b = new QPushButton(kbasicIcon(kbasicControlPath("serialport.png")), tr(""), this); b->setToolTip("SerialPort"); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(serialport()));
  b = new QPushButton(kbasicIcon(kbasicControlPath("movie.png")), tr(""), this); b->setToolTip("MovieBox"); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(movie()));
  l = new QListWidgetItem(kbasicIcon(kbasicControlPath("sound.png")), tr(""), this); b->setToolTip("Sound"); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(sound()));
  l = new QListWidgetItem(kbasicIcon(kbasicControlPath("web.png")), tr(""), this); b->setToolTip("WebView"); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(web()));
  l = new QListWidgetItem(kbasicIcon(kbasicControlPath("resizebox.png")), tr(""), this); b->setToolTip("ResizeBox"); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(resizebox()));
  l = new QListWidgetItem(kbasicIcon(kbasicControlPath("commandlinkbutton.png")), tr(""), this); b->setToolTip("CommandLinkButton"); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(commandlinkbutton()));
  l = new QListWidgetItem(kbasicIcon(kbasicControlPath("svg.png")), tr("")); l->setToolTip("SvgBox"); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(svg()));
  l = new QListWidgetItem(kbasicIcon(kbasicControlPath("toolbarview.png")), tr("")); l->setToolTip("ToolBarView"); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(toolbarview()));
  l = new QListWidgetItem(kbasicIcon(kbasicControlPath("formsview.png")), tr("")); l->setToolTip("FormsView"); b->setFlat(true); b->setIconSize(QSize(32, 32)); b->setFixedSize(QSize(34, 34)); grid->addWidget(b, y, x); x++; if (x > 3){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(formsview()));
  

  setLayout(grid);
  */


}


void _toolboxwindow_form::currentRowChanged  ( int nRow )
//void _toolboxwindow_form::currentItemChanged  ( QListWidgetItem * l, QListWidgetItem *ll )
{
  //setCurrentItem(item(0));
  QListWidgetItem *l = item(nRow);
  if (l == 0 || qApp->focusWidget() != this) return;

//QMessageBox::information(this, "nRow=",  QString("%1").arg(nRow)); 

  QString s = l->data(Qt::UserRole).toString();
  if (s == "pointer") { if (EXTERN_my_form){ EXTERN_my_form->setInsertControlType(t_notype); sInsertTypeOption = ""; }}
  if (s == "commandbutton"){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_commandbutton); sInsertTypeOption = ""; }}


  if (s == "label"){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_label); sInsertTypeOption = ""; }}
  if (s == "textbox"){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_textbox); sInsertTypeOption = ""; }}
  if (s == "checkbox"){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_checkbox); sInsertTypeOption = ""; }}

  if (s == "radiobutton"){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_radiobutton); sInsertTypeOption = ""; }}
  if (s == "frame"){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_frame); sInsertTypeOption = ""; }}
  if (s == "listbox"){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_listbox); sInsertTypeOption = ""; }}
  if (s == "listbox_iconmode"){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_listbox); sInsertTypeOption = "IconMode"; }}
  if (s == "combobox"){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_combobox); sInsertTypeOption = ""; }}
  if (s == "combobox_editable"){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_combobox); sInsertTypeOption = "Editable"; }}
  if (s == "tab"){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_tab); sInsertTypeOption = ""; }}

  if (s == "progressbar"){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_progressbar); sInsertTypeOption = ""; }}
  if (s == "progressbar_spinning"){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_progressbar); sInsertTypeOption = "Spinning"; }}
  if (s == "treeview_listview"){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_treeview); sInsertTypeOption = "ListView"; }}
  if (s == "image"){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_image); sInsertTypeOption = ""; }}
  if (s == "hidden"){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_hidden); sInsertTypeOption = ""; }}
  if (s == "timer"){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_timer); sInsertTypeOption = ""; }}
  if (s == "treeview"){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_treeview); sInsertTypeOption = ""; }}

  if (s == "imagebutton"){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_imagebutton); sInsertTypeOption = ""; }}

  if (s == "textbox_password"){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_textbox); sInsertTypeOption = "Password"; }}
  if (s == "label_link"){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_label); sInsertTypeOption = "Link"; }}
  if (s == "line_vertical"){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_line); sInsertTypeOption = "Vertical"; }}
  if (s == "line_horizontal"){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_line); sInsertTypeOption = "Horizontal"; }}

  if (s == "hsplit"){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_hsplit); sInsertTypeOption = ""; }}
  if (s == "box"){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_box); sInsertTypeOption = ""; }}
  if (s == "childcontrol"){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_childcontrol); sInsertTypeOption = ""; }}

  if (s == "toolbutton"){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_toolbutton); sInsertTypeOption = ""; }}
  if (s == "editor"){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_editor); sInsertTypeOption = ""; }}
  if (s == "browser"){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_browser); sInsertTypeOption = ""; }}
  if (s == "datebox"){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_datebox); sInsertTypeOption = ""; }}
  if (s == "timebox"){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_timebox); sInsertTypeOption = ""; }}
  if (s == "datetimebox"){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_datetimebox); sInsertTypeOption = ""; }}
  if (s == "serialport"){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_serialport); sInsertTypeOption = ""; }}
  if (s == "movie"){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_movie); sInsertTypeOption = ""; }}
  if (s == "sound"){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_sound); sInsertTypeOption = ""; }}
  if (s == "web"){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_web); sInsertTypeOption = ""; }}
  // CONTROL
  if (s == "resizebox"){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_resizebox); sInsertTypeOption = ""; }}
  if (s == "commandlinkbutton"){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_commandlinkbutton); sInsertTypeOption = ""; }}
  if (s == "svg"){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_svg); sInsertTypeOption = ""; }}
  if (s == "toolbarview"){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_toolbarview); sInsertTypeOption = ""; }}
  if (s == "formsview"){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_formsview); sInsertTypeOption = ""; }}
  if (s == "scrollbar"){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_scrollbar); sInsertTypeOption = ""; }}
  if (s == "slider"){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_slider); sInsertTypeOption = ""; }}
  if (s == "spinbox"){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_spinbox); sInsertTypeOption = ""; }}
  if (s == "udpsocket"){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_udpsocket); sInsertTypeOption = ""; }}


}

/*
void _toolboxwindow_form::pointer(){ if (EXTERN_my_form){ EXTERN_my_form->setInsertControlType(t_notype); sInsertTypeOption = ""; }}
void _toolboxwindow_form::commandbutton(){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_commandbutton); sInsertTypeOption = ""; }}
void _toolboxwindow_form::label(){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_label); sInsertTypeOption = ""; }}
void _toolboxwindow_form::textbox(){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_textbox); sInsertTypeOption = ""; }}
void _toolboxwindow_form::checkbox(){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_checkbox); sInsertTypeOption = ""; }}

void _toolboxwindow_form::radiobutton(){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_radiobutton); sInsertTypeOption = ""; }}
void _toolboxwindow_form::frame(){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_frame); sInsertTypeOption = ""; }}
void _toolboxwindow_form::listbox(){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_listbox); sInsertTypeOption = ""; }}
void _toolboxwindow_form::listbox_iconmode(){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_listbox); sInsertTypeOption = "IconMode"; }}
void _toolboxwindow_form::combobox(){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_combobox); sInsertTypeOption = ""; }}
void _toolboxwindow_form::combobox_editable(){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_combobox); sInsertTypeOption = "Editable"; }}
void _toolboxwindow_form::tab(){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_tab); sInsertTypeOption = ""; }}

void _toolboxwindow_form::progressbar(){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_progressbar); sInsertTypeOption = ""; }}
void _toolboxwindow_form::progressbar_spinning(){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_progressbar); sInsertTypeOption = "Spinning"; }}
void _toolboxwindow_form::treeview_listview(){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_treeview); sInsertTypeOption = "ListView"; }}
void _toolboxwindow_form::image(){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_image); sInsertTypeOption = ""; }}
void _toolboxwindow_form::hidden(){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_hidden); sInsertTypeOption = ""; }}
void _toolboxwindow_form::timer(){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_timer); sInsertTypeOption = ""; }}
void _toolboxwindow_form::treeview(){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_treeview); sInsertTypeOption = ""; }}

void _toolboxwindow_form::imagebutton(){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_imagebutton); sInsertTypeOption = ""; }}
void _toolboxwindow_form::vbox(){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_vbox); sInsertTypeOption = ""; }}
void _toolboxwindow_form::hbox(){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_hbox); sInsertTypeOption = ""; }}
void _toolboxwindow_form::vhbox(){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_vhbox); sInsertTypeOption = ""; }}
void _toolboxwindow_form::vsplit(){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_vsplit); sInsertTypeOption = ""; }}

void _toolboxwindow_form::textbox_password(){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_textbox); sInsertTypeOption = "Password"; }}
void _toolboxwindow_form::label_link(){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_label); sInsertTypeOption = "Link"; }}
void _toolboxwindow_form::line_vertical(){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_line); sInsertTypeOption = "Vertical"; }}
void _toolboxwindow_form::line_horizontal(){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_line); sInsertTypeOption = "Horizontal"; }}

void _toolboxwindow_form::hsplit(){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_hsplit); sInsertTypeOption = ""; }}
void _toolboxwindow_form::box(){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_box); sInsertTypeOption = ""; }}
void _toolboxwindow_form::childcontrol(){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_childcontrol); sInsertTypeOption = ""; }}

void _toolboxwindow_form::toolbutton(){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_toolbutton); sInsertTypeOption = ""; }}
void _toolboxwindow_form::editor(){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_editor); sInsertTypeOption = ""; }}
void _toolboxwindow_form::browser(){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_browser); sInsertTypeOption = ""; }}
void _toolboxwindow_form::datebox(){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_datebox); sInsertTypeOption = ""; }}
void _toolboxwindow_form::timebox(){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_timebox); sInsertTypeOption = ""; }}
void _toolboxwindow_form::datetimebox(){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_datetimebox); sInsertTypeOption = ""; }}
void _toolboxwindow_form::serialport(){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_serialport); sInsertTypeOption = ""; }}
void _toolboxwindow_form::movie(){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_movie); sInsertTypeOption = ""; }}
void _toolboxwindow_form::sound(){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_sound); sInsertTypeOption = ""; }}
void _toolboxwindow_form::web(){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_web); sInsertTypeOption = ""; }}
// CONTROL
void _toolboxwindow_form::resizebox(){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_resizebox); sInsertTypeOption = ""; }}
void _toolboxwindow_form::commandlinkbutton(){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_commandlinkbutton); sInsertTypeOption = ""; }}
void _toolboxwindow_form::svg(){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_svg); sInsertTypeOption = ""; }}
void _toolboxwindow_form::toolbarview(){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_toolbarview); sInsertTypeOption = ""; }}
void _toolboxwindow_form::formsview(){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_formsview); sInsertTypeOption = ""; }}
void _toolboxwindow_form::scrollbar(){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_scrollbar); sInsertTypeOption = ""; }}
void _toolboxwindow_form::slider(){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_slider); sInsertTypeOption = ""; }}
void _toolboxwindow_form::spinbox(){ if (EXTERN_my_form){ MSG EXTERN_my_form->setInsertControlType(t_spinbox); sInsertTypeOption = ""; }}


*/