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
#include "_help.h"
#include "_mainwindow.h"
#include "_typedef.h"
extern _mainwindow *EXTERN_my_mainwindow;
extern QString kbasicPath(QString sPath);

_help::_help(QWidget* parent, QString home_, int width, int height) : QMainWindow(parent)
{
  setAttribute(Qt::WA_DeleteOnClose);
  
  Qt::WindowFlags flags = 0;
  flags = Qt::Dialog;
  setWindowFlags(flags);

  int w = width;
  int h = height;

  browser = new QTextBrowser( this );
  
  browser->setOpenExternalLinks(true);

  setCentralWidget( browser );
  browser->setFocus();
  
  if (!home_.isEmpty()){
    home_ = "file:///" + home_;
    browser->setSource( QUrl(home_) );
  }

  if (home_.contains("aboutkbasic_professional")){
    QString s = browser->toHtml();

    QString ss = "????";

    QFileInfo f(qApp->applicationFilePath());

    if (f.isReadable()){
      ss = f.lastModified().toString("d MMM yyyy");
    }
    s = s.replace("####-##-##", ss);
    browser->setHtml(s);
  }

  setWindowTitle(MYAPP);
  setFixedWidth(w);
  setFixedHeight(h);

  //
  browser->setFixedWidth(w);
  browser->setFixedHeight(h);

  setGeometry(QApplication::desktop()->width() / 2 - w / 2, QApplication::desktop()->height() / 2 - h / 2, w, h);
  statusBar()->setHidden(true);

#ifndef MAC
  QPushButton *p = new QPushButton(tr("&Close"), browser);
  connect(p, SIGNAL (clicked ()), this, SLOT( close() ));

  p->move(browser->width() / 2 - 50, browser->height() - 40);
  p->resize(100, 25);
#endif

  show();
  qApp->setActiveWindow(this);
}

_examplebrowser::_examplebrowser(QWidget* _parent) : QDialog(_parent)
{
  setAttribute(Qt::WA_DeleteOnClose);
  setWindowFlags(windowFlags() | Qt::Dialog);


  QVBoxLayout *j = new QVBoxLayout();
    setLayout(j);
    j->setMargin(0);
    j->setSpacing(0);


  QLabel *tt = new QLabel(tr(" This is a small list of the available examples. For more examples check out the menubar entry 'Examples'. "));
  tt->setFixedHeight(40);
  j->addWidget(tt);

  tab = new QToolBox(); j->addWidget(tab);

#ifdef MAC
  resize(740, 480); // HIDE
#else
  resize(480, 480);
#endif
  setWindowTitle(tr("Example Browser"));
  setModal(true);
  
  setupGeneral();  
  setupForm();  
  setupGeneral2();  
  setupMisc();    
 
  move(QApplication::desktop()->width() / 2 - width() / 2, QApplication::desktop()->height() / 2 - height() / 2);
  show();
  qApp->setActiveWindow(this);
  
}

void _examplebrowser::setupGeneral()
{

    QWidget *g = new QWidget();
    QGridLayout *j = new QGridLayout();
    j->setMargin(1);
    j->setSpacing(1);

    int y = 0;
    addExample("htmlview", j, y++);
    addExample("listbox", j, y++);
    addExample("listview", j, y++);
    addExample("checkbox", j, y++);
    addExample("combobox", j, y++);
    addExample("control", j, y++);
    addExample("richtextbox", j, y++);
    addExample("radiobutton", j, y++);
    addExample("tabview", j, y++);
    addExample("textbox", j, y++);
    addExample("treeview", j, y++);


    

    g->setLayout(j);
    QScrollArea *a = new QScrollArea(this);
    a->setFrameShape(QFrame::NoFrame);
    a->setWidget(g);
    a->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    a->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded); 
    a->setWidgetResizable(true);
    a->setMinimumHeight(100);



    tab->addItem(a, tr("Controls"));
  
}

void _examplebrowser::setupGeneral2()
{

    QWidget *g = new QWidget();
    QGridLayout *j = new QGridLayout();
    j->setMargin(1);
    j->setSpacing(1);
    int y = 0;

    g->setLayout(j);
    QScrollArea *a = new QScrollArea(this);
    a->setFrameShape(QFrame::NoFrame);
    a->setWidget(g);
    a->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    a->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded); 
    a->setWidgetResizable(true);

    addExample("application", j, y++);
    addExample("menubar", j, y++);
    addExample("toolbar", j, y++);
    addExample("helloworld", j, y++);
    addExample("stylesheet", j, y++);
    addExample("stylesheet2", j, y++);

    tab->addItem(a, tr("Application"));
  
}

void _examplebrowser::setupSQL()
{

    QWidget *g = new QWidget();
    QGridLayout *j = new QGridLayout();
    j->setMargin(1);
    j->setSpacing(1);
    int y = 0;

    g->setLayout(j);
    QScrollArea *a = new QScrollArea(this);
    a->setFrameShape(QFrame::NoFrame);
    a->setWidget(g);
    a->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    a->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded); 
    a->setWidgetResizable(true);

    //addExample("postgresql", j, y++);
    addExample("sql", j, y++);

    tab->addItem(a, tr("SQL"));
  
}

void _examplebrowser::setupMisc()
{

    QWidget *g = new QWidget();
    QGridLayout *j = new QGridLayout();
    j->setMargin(1);
    j->setSpacing(1);
    int y = 0;

    g->setLayout(j);
    QScrollArea *a = new QScrollArea(this);
    a->setFrameShape(QFrame::NoFrame);
    a->setWidget(g);
    a->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    a->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded); 
    a->setWidgetResizable(true);

    //addExample("game", j, y++);
    addExample("paint", j, y++);
    addExample("syntaxhighlighting", j, y++);
    addExample("timer", j, y++);
    addExample("timer2", j, y++);
    addExample("events", j, y++);
    addExample("focus", j, y++);
    addExample("focusorder", j, y++);

    addExample("calculator", j, y++);

    tab->addItem(a, tr("Misc"));
  
}


void _examplebrowser::setupForm()
{

    QWidget *g = new QWidget();
    QGridLayout *j = new QGridLayout();
    j->setMargin(1);
    j->setSpacing(1);

    int y = 0;

    addExample("form", j, y++);
    addExample("form2", j, y++);
    addExample("forms", j, y++);


    

    g->setLayout(j);
    QScrollArea *a = new QScrollArea(this);
    a->setFrameShape(QFrame::NoFrame);
    a->setWidget(g);
    a->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    a->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded); 
    a->setWidgetResizable(true);



    tab->addItem(a, tr("Form"));
  
}

void _examplebrowser::addExample(QString sFile, QGridLayout *j, int y)
{
  QString m = kbasicPath("examples/projects/");
  m += sFile;
  m += ".kbasic_project";

  QString s = "";
  QFile f(m + "/INFO.html");
  if (!f.open(QIODevice::ReadOnly)){
//    QMessageBox::information(this, MYAPP, QString("Could not read from %1").arg(m));
  } else {
    QTextStream t(&f);
    
    t.setCodec("UTF-8");
    t.setAutoDetectUnicode(true);
    t.setGenerateByteOrderMark(true);

    s = t.readAll();
    s = s.replace("\r", "");
    f.close();
  }

  QTextBrowser *tb = new QTextBrowser();
  tb->setHtml(s);
  j->addWidget(tb, y, 0);

  QPushButton *p = new QPushButton();
  connect(p, SIGNAL( clicked() ), this, SLOT(perform()) );

  p->setFlat(true);
  p->setIconSize(QSize(200, 200));
  p->setCursor(Qt::PointingHandCursor);

  p->setIcon(QPixmap(m + "/INFO.png"));
  p->setToolTip(tr("Click to open"));
  m += "/";
  m += sFile;
  m += ".kbasic_project";
  p->setObjectName(m);

  j->addWidget(p, y, 1);
}

void _examplebrowser::perform()
{
  QPushButton *p = qobject_cast<QPushButton *>(sender());
  if (p){
    close();
    EXTERN_my_mainwindow->loadProject(p->objectName());  
  }
}  
