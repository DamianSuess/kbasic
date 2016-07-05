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

#include <QtGui>


#include "_welcome.h"
#include "_mainwindow.h"

#include "_preferences.h"

_welcome::_welcome( QWidget *parent) : QDialog(0)
{
  setAttribute(Qt::WA_DeleteOnClose);
  setWindowFlags(windowFlags() | Qt::Tool);

  my_mainwindow = (_mainwindow *) parent;

  setWindowTitle(tr("Welcome"));
  setModal(true);

  QVBoxLayout *j = new QVBoxLayout();
  setLayout(j);



  browser = new QTextBrowser(); j->addWidget(browser);
  browser->setMinimumSize(450, 200);  

  QString s = tr(""
    "<h2>This is a full featured, modern object orientated BASIC language for Linux, Mac OS X and Windows.</h2>"
    "<br>"
    "It is a powerful programming language, which is simply intuitive and fast easy to learn. KBasic is developed for Linux, Mac OS X and Windows and represents a further bridge between Linux, Mac and Windows. KBasic a new programming language, a further basic dialect, is related to Visual Basic 6 and Java. More exactly said KBasic is an object-orientated and event-controlled programming language, developed by KBasic Software (www.kbasic.com), is particularly designed for Windows and Linux and for the needs by Qt-developers and has thus a strength in the Qt-application development. For C/C++ developers BASIC has generally a bad reputation as child programming language that is not true becomes clearly with KBasic. With KBasic you can write nearly all applications, which perhaps would have been written by you in C/C++, if there were not KBasic.<br>"
    "<br>"
    "<br>"
    "<i>KBasic 2008</i>"
    "");


  browser->setText(s);

  QPushButton *p;
  p = new QPushButton(tr("'H&ello World' Example")); j->addWidget(p);
  connect(p, SIGNAL( clicked() ), this, SLOT(SLOT_ok()) );

  p = new QPushButton(tr("&Close Welcome")); j->addWidget(p);
  p->setFocus();
  
  connect(p, SIGNAL( clicked() ), this, SLOT(SLOT_close()) );



  move(QApplication::desktop()->width() / 2 - sizeHint().width() / 2, QApplication::desktop()->height() / 2 - sizeHint().height() / 2);
  show();


  if (my_mainwindow->getPreference("ImportantHelpIndex") == "Yes"){
    if ( !QMessageBox::question(
              this,
              tr("What is your preference?"),
              tr("Do you like to activate help entries and tips?\n"
                  "Many experienced BASIC user would NOT need such stuff. You can change the preferences anyway later.\n\n"
                  "If you are new to BASIC or coding, I suggest you to select 'Yes'. Otherwise please select 'No' -> deactivate help entries.\n"),
              tr("&Yes"), tr("&No"),
              QString::null, 0, 1 ) )
    {
        my_mainwindow->setPreference("BackgroundImages", "No");
        my_mainwindow->setPreference("QuickCommands", "No");
        my_mainwindow->setPreference("ExampleOnQuickCommands", "No");
        my_mainwindow->setPreference("ImportantHelpIndex", "No");
        my_mainwindow->setPreference("BackImageInFormDesign", "No");
        my_mainwindow->setPreference("PlaySound", "No");
        my_mainwindow->setPreference("BookmarkPicture", "No");
        my_mainwindow->setPreference("FlashDebuggingMessage", "No");
        my_mainwindow->setPreference("BreakpointPicture", "No");
        my_mainwindow->setPreference("BackImageOnNewFile", "No");

        _preferences c(my_mainwindow, true);  

    } else {
        my_mainwindow->setPreference("ImportantHelpIndex", "No");
        _preferences c(my_mainwindow, true);  
    }
  }
    


}



void _welcome::SLOT_ok()
{ 
  EXTERN_my_mainwindow->loadFile(kbasicPath("examples/kbasic/hello.kbasic"));

  EXTERN_my_mainwindow->setPreference("WelcomeScreen", "No");
  _preferences c(this, true);  

  close();
}

void _welcome::SLOT_close()
{
  EXTERN_my_mainwindow->setPreference("WelcomeScreen", "No");
  _preferences c(this, true);  

  close();
}

