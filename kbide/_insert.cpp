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

#include "_insert.h"

#include "_sourcecodeeditor.h"
#include "_mainwindow.h"
#include "_typedef.h"

extern _mainwindow *EXTERN_my_mainwindow;
extern QString kbasicPath(QString sPath);


_insert::_insert(QWidget *parent, _sourcecodeeditor *_my_sourcecodeeditor, QString title, QIcon icon, QString helpStart, QString helpEnd) : QDialog( parent)
{
  setAttribute(Qt::WA_DeleteOnClose);
  setWindowFlags(windowFlags() | Qt::Tool);

  my_sourcecodeeditor = _my_sourcecodeeditor;

  my_mainwindow = (_mainwindow *) parent;

  resize(500, 400);
  
  setWindowTitle(title);
  setWindowIcon (icon);
  
  setModal(false);

  grid = new QGridLayout();  
  grid->setSpacing(10);
  this->setLayout(grid);
/*
  QTextBrowser* browser;

  browser = new QTextBrowser( this );
  browser->setFixedHeight(200);  

  browser->setText(loadHelp(helpStart, helpEnd, my_mainwindow));

  grid->addWidget (browser, 0, 0, 1, 3);    */

  QWidget *k = new QWidget(this);
  QVBoxLayout *y = new QVBoxLayout();
  y->setAlignment(Qt::AlignBottom);
  k->setLayout(y);
  grid->addWidget (k, 2, 1, 3, 1);    

  QPushButton *p;

#ifdef MAC

  p = new QPushButton(tr("&Cancel"), this);
  p->setFixedWidth(100);
  connect(p, SIGNAL( clicked() ), this, SLOT(SLOT_close()) );
  y->addWidget(p);  

  p = new QPushButton(tr("&Insert"), this);
  p->setFixedWidth(100);   
  connect(p, SIGNAL( clicked() ), this, SLOT(SLOT_ok()) );
  y->addWidget(p);  

#else
  p = new QPushButton(tr("&Insert"), this);
  p->setFixedWidth(100);   
  connect(p, SIGNAL( clicked() ), this, SLOT(SLOT_ok()) );
  y->addWidget(p);  

  p = new QPushButton(tr("&Cancel"), this);
  p->setFixedWidth(100);
  connect(p, SIGNAL( clicked() ), this, SLOT(SLOT_close()) );
  y->addWidget(p);  
#endif


  QLabel *l = new QLabel(tr("The following source code will be inserted:"), this);
  grid->addWidget (l, 2, 0);

  se = new QTextEdit(this);
  se->setReadOnly(true);
  se->setText("");
  grid->addWidget (se, 3, 0);
}


QString _insert::insert()
{
  if (true){
    return format1();
  } else if (false){
    return format2();
  }
}

void _insert::insert(QString sFormat1, QString sFormat2)
{
  if (true){
    my_mainwindow->performInsertTextInSourceCode(sFormat1);
  } else if (false){
    my_mainwindow->performInsertTextInSourceCode(sFormat2);
  }
  accept();
}

void _insert::SLOT_ok()
{ 
  insert(format1(), format2());
  accept();
}

void _insert::SLOT_close()
{
  accept();
}

QString _insert::format1()
{
  return "";
}

QString _insert::format2()
{
  return "";
}

QString _insert::loadHelp( QString search, QString sStop, _mainwindow *m)
{
  
  QString filename  = kbasicPath("docs\\kbasicbook\\home" + _mainwindow::locale() + ".html");

  QFile f(filename);
  if (!f.open(QIODevice::ReadOnly)){
    return "error: could not read file";
  }

  QString s = "";

  QTextStream t(&f);
  
  t.setCodec("UTF-8");
  t.setAutoDetectUnicode(true);
  t.setGenerateByteOrderMark(true);

  s = t.readAll();
  s = s.replace("\r", "");
  f.close();  

  int n = 0;
  if (m->locale() == "de"){
    n = s.indexOf("<H2><A NAME=\"Einf&uuml;hrung\""); 
  } else {
    n = s.indexOf("<H2><A NAME=\"Introduction\""); 
  }
  s = s.mid(n);

  n = s.indexOf(search);
  s = s.mid(n);

  n = s.indexOf(sStop, 40);


  if (n != -1) s = s.left(n);

  if (m->locale() == "de"){
    s = s + tr("<BR><BR><i>(Auszug aus 'Das KBasic Buch')</i><BR>");
  } else {
    s = s + tr("<BR><BR><i>(Part of 'The KBasic Book')</i><BR>");
  }
  

  s = s.replace("<A NAME=\"\"><FONT CLASS=\"h2\"><B><FONT FACE=\"Courier New, monospace\"><BR></FONT></FONT></B>", ""); // WORKAROUND
  
  s = appendHTMLGeneralTags(s);

  return s;  
}

QString _insert::appendHTMLGeneralTags(QString s)
{
  QString m;
  m = ""
"<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0 Transitional//EN\">"
"<html>"
"<head>"
"<title>Language Reference</title>"
"</head>"
;

  m.append(s);

  m.append(""
"</body>"
"</html>"
);
  return m;
}

// ****  
// ****  
// ****  

_insert_option_kbasic::_insert_option_kbasic( QWidget *parent, _sourcecodeeditor *_my_sourcecodeeditor, QString title, QIcon icon, QString helpStart, QString helpEnd, int nDefaultButton)
    : _insert( parent, _my_sourcecodeeditor, title, icon, helpStart, helpEnd)
{  
  QWidget *k = new QWidget(this);

  QVBoxLayout *y = new QVBoxLayout();
  y->setAlignment(Qt::AlignBottom);
  k->setLayout(y);
  grid->addWidget(k, 1, 0, 1, 3);    

  g = new QGroupBox(tr("Mode"), this);
  QVBoxLayout *z = new QVBoxLayout();
  g->setLayout(z);
  y->addWidget(g);

  QRadioButton *rb;
  rb = new QRadioButton ("Option KBasic", g); z->addWidget(rb); connect(rb, SIGNAL(clicked(bool)), this, SLOT(clicked_0(bool)));
  if (nDefaultButton == 0){ rb->setChecked(true); nSelected = 0; }
  setFocusProxy(rb);
  rb->setFocus(Qt::ActiveWindowFocusReason);
  
  rb = new QRadioButton ("Option OldBasic", g); z->addWidget(rb); connect(rb, SIGNAL(clicked(bool)), this, SLOT(clicked_1(bool)));
  if (nDefaultButton == 1){ rb->setChecked(true); nSelected = 1; }

  rb = new QRadioButton ("Option VeryOldBasic", g); z->addWidget(rb); connect(rb, SIGNAL(clicked(bool)), this, SLOT(clicked_2(bool)));
  if (nDefaultButton == 2){ rb->setChecked(true); nSelected = 2; }

  
  
  se->setText(insert());

  move(QApplication::desktop()->width() / 2 - sizeHint().width() / 2, QApplication::desktop()->height() / 2 - sizeHint().height() / 2);
  show();
  qApp->setActiveWindow(this);


}

void _insert_option_kbasic::clicked_0(bool b)
{
  if (b) nSelected = 0;
  se->setText(insert());
}

void _insert_option_kbasic::clicked_1(bool b)
{
  if (b) nSelected = 1;
  se->setText(insert());
}

void _insert_option_kbasic::clicked_2(bool b)
{
  if (b) nSelected = 2;
  se->setText(insert());
}

QString _insert_option_kbasic::format1()
{  
  switch(nSelected){
    case 0:
        return "\nOption KBasic\n";
    case 1:
        return "\nOption OldBasic\n";
    case 2:
        return "\nOption VeryOldBasic\n";
  }
  return "";
}

QString _insert_option_kbasic::format2()
{  
  switch(nSelected){
    case 0:
        return "\nOPTION KBASIC\n";
    case 1:
        return "\nOPTION OLDBASIC\n";
    case 2:
        return "\nOPTION VERYOLDBASIC\n";
  }
  return "";
}


_insert_option_oldbasic::_insert_option_oldbasic( QWidget *parent, _sourcecodeeditor *_editor, QString title, QIcon icon, QString helpStart, QString helpEnd)
    : _insert_option_kbasic( parent, _editor, title, icon, helpStart, helpEnd, 1)
{
}

// ****  
// ****  
// ****  

_insert_option_veryoldbasic::_insert_option_veryoldbasic( QWidget *parent, _sourcecodeeditor *_editor, QString title, QIcon icon, QString helpStart, QString helpEnd)
    : _insert_option_kbasic( parent, _editor, title, icon, helpStart, helpEnd, 2)
{
}

// ****  
// ****  
// ****  

_insert_assignment::_insert_assignment( QWidget *parent, _sourcecodeeditor *_editor, QString title, QIcon icon, QString helpStart, QString helpEnd)
    : _insert( parent, _editor, title, icon, helpStart, helpEnd)
{

  QWidget *k = new QWidget(this);

  QVBoxLayout *y = new QVBoxLayout();
  y->setAlignment(Qt::AlignBottom);
  k->setLayout(y);
  grid->addWidget(k, 1, 0, 1, 3);    

  QLabel *l = new QLabel(tr("Your Assignment(s):"), this); y->addWidget(l);

  g = new QTextEdit(this);
  y->addWidget(g);  

  setFocusProxy(g);
  g->setFocus(Qt::ActiveWindowFocusReason);

  connect(g, SIGNAL(textChanged()), this, SLOT(textChanged()));

  move(QApplication::desktop()->width() / 2 - sizeHint().width() / 2, QApplication::desktop()->height() / 2 - sizeHint().height() / 2);
  show();
  qApp->setActiveWindow(this);

}

void _insert_assignment::textChanged()
{
  se->setText(insert());
}

QString _insert_assignment::format1()
{
  return g->toPlainText();
}

QString _insert_assignment::format2()
{
  return g->toPlainText();
}

// ****  
// ****  
// ****  

_insert_statement::_insert_statement( QWidget *parent, _sourcecodeeditor *_editor, QString title, QIcon icon, QString helpStart, QString helpEnd)
    : _insert( parent, _editor, title, icon, helpStart, helpEnd)
{

  QWidget *k = new QWidget(this);

  QVBoxLayout *y = new QVBoxLayout();
  y->setAlignment(Qt::AlignBottom);
  k->setLayout(y);
  grid->addWidget(k, 1, 0, 1, 3);    

  QLabel *l = new QLabel(tr("Your Statement(s):"), this); y->addWidget(l);

  g = new QTextEdit(this);
  y->addWidget(g);  

  setFocusProxy(g);
  g->setFocus(Qt::ActiveWindowFocusReason);

  connect(g, SIGNAL(textChanged()), this, SLOT(textChanged()));

  move(QApplication::desktop()->width() / 2 - sizeHint().width() / 2, QApplication::desktop()->height() / 2 - sizeHint().height() / 2);
  show();
  qApp->setActiveWindow(this);

}

void _insert_statement::textChanged()
{
  se->setText(insert());
}

QString _insert_statement::format1()
{
  return g->toPlainText();
}

QString _insert_statement::format2()
{
  return g->toPlainText();
}

// ****  
// ****  
// ****  

_insert_expression::_insert_expression( QWidget *parent, _sourcecodeeditor *_editor, QString title, QIcon icon, QString helpStart, QString helpEnd)
    : _insert( parent, _editor, title, icon, helpStart, helpEnd)
{

  QWidget *k = new QWidget(this);

  QVBoxLayout *y = new QVBoxLayout();
  y->setAlignment(Qt::AlignBottom);
  k->setLayout(y);
  grid->addWidget(k, 1, 0, 1, 3);    

  QLabel *l = new QLabel(tr("Your Expression(s):"), this); y->addWidget(l);

  g = new QTextEdit(this);
  y->addWidget(g);  

  setFocusProxy(g);
  g->setFocus(Qt::ActiveWindowFocusReason);

  connect(g, SIGNAL(textChanged()), this, SLOT(textChanged()));

  move(QApplication::desktop()->width() / 2 - sizeHint().width() / 2, QApplication::desktop()->height() / 2 - sizeHint().height() / 2);
  show();
  qApp->setActiveWindow(this);

}

void _insert_expression::textChanged()
{
  se->setText(insert());
}

QString _insert_expression::format1()
{
  return g->toPlainText();
}

QString _insert_expression::format2()
{
  return g->toPlainText();
}

// ****  
// ****  
// ****  

_insert_operator::_insert_operator( QWidget *parent, _sourcecodeeditor *_editor, QString title, QIcon icon, QString helpStart, QString helpEnd)
    : _insert( parent, _editor, title, icon, helpStart, helpEnd)
{

  QWidget *k = new QWidget(this);

  QVBoxLayout *y = new QVBoxLayout();
  y->setAlignment(Qt::AlignBottom);
  k->setLayout(y);
  grid->addWidget(k, 1, 0, 1, 3);    

  QLabel *l = new QLabel(tr("Possible Operators:"), this); y->addWidget(l);

  QComboBox *x = g = new QComboBox(this); y->addWidget(x);
  x->setMaximumWidth(100);

  x->addItem("");
  x->addItem("+");
  x->addItem("-");
  x->addItem("/");
  x->addItem("*");
  x->addItem("Mod");
  x->addItem("\\");
  x->addItem("^");
  x->addItem("&");
  x->addItem("");
  x->addItem("=");
  x->addItem("<>");
  x->addItem("<");
  x->addItem("<=");
  x->addItem(">");
  x->addItem(">=");
  x->addItem("");
  x->addItem("Not");
  x->addItem("And");
  x->addItem("Or");
  x->addItem("Xor");
  x->addItem("AndAlso");
  x->addItem("OrElse");
  x->addItem("Eqv");
  x->addItem("Imp");

  setFocusProxy(g);
  g->setFocus(Qt::ActiveWindowFocusReason);
  
  connect(g, SIGNAL(activated(int)), this, SLOT(activated(int)));

  move(QApplication::desktop()->width() / 2 - sizeHint().width() / 2, QApplication::desktop()->height() / 2 - sizeHint().height() / 2);
  show();
  qApp->setActiveWindow(this);

}

void _insert_operator::activated(int n)
{
  se->setText(insert());
}

QString _insert_operator::format1()
{
  return g->currentText();
}

QString _insert_operator::format2()
{
  return g->currentText();
}

// ****  
// ****  
// ****  

_insert_if::_insert_if( QWidget *parent, _sourcecodeeditor *_editor, QString title, QIcon icon, QString helpStart, QString helpEnd)
    : _insert( parent, _editor, title, icon, helpStart, helpEnd)
{

  QWidget *k = new QWidget(this);

  QVBoxLayout *y = new QVBoxLayout();
  y->setAlignment(Qt::AlignBottom);
  k->setLayout(y);
  grid->addWidget(k, 1, 0, 1, 3);    

  QLabel *l = new QLabel(tr("Condition / Expression:"), this); y->addWidget(l);

  g = new QLineEdit(this);
  y->addWidget(g);  

  setFocusProxy(g);
  g->setFocus(Qt::ActiveWindowFocusReason);

  connect(g, SIGNAL(textChanged(const QString &)), this, SLOT(textChanged(const QString &)));

  move(QApplication::desktop()->width() / 2 - sizeHint().width() / 2, QApplication::desktop()->height() / 2 - sizeHint().height() / 2);
  show();
  qApp->setActiveWindow(this);

}

void _insert_if::textChanged( const QString &s)
{
  se->setText(insert());
}

QString _insert_if::format1()
{
  QString s = "";
  
  s = s + "\nIf " + g->text() + " Then" + "\n";
  s = s + "  \n";
  s = s + "End If\n";
  return s;
}

QString _insert_if::format2()
{
  QString s = "";
  
  s = s + "\nIF " + g->text() + " THEN" + "\n";
  s = s + "  \n";
  s = s + "END IF\n";
  return s;
}

// ****  
// ****  
// ****  

_insert_select::_insert_select( QWidget *parent, _sourcecodeeditor *_editor, QString title, QIcon icon, QString helpStart, QString helpEnd)
    : _insert( parent, _editor, title, icon, helpStart, helpEnd)
{

  QWidget *k = new QWidget(this);

  QVBoxLayout *y = new QVBoxLayout();
  y->setAlignment(Qt::AlignBottom);
  k->setLayout(y);
  grid->addWidget(k, 1, 0, 1, 3);    

  QLabel *l = new QLabel(tr("Condition / Expression:"), this); y->addWidget(l);

  g = new QLineEdit(this);
  y->addWidget(g);  

  setFocusProxy(g);
  g->setFocus(Qt::ActiveWindowFocusReason);

  connect(g, SIGNAL(textChanged(const QString &)), this, SLOT(textChanged(const QString &)));

  move(QApplication::desktop()->width() / 2 - sizeHint().width() / 2, QApplication::desktop()->height() / 2 - sizeHint().height() / 2);
  show();
  qApp->setActiveWindow(this);

}

void _insert_select::textChanged( const QString &s)
{
  se->setText(insert());
}

QString _insert_select::format1()
{
  QString s = "";

  s = s + "\nSelect Case " + g->text() + "\n";
  s = s + "  Case EXPRESSION:\n";
  s = s + "    ' your code here\n";
  s = s + "    \n";
  s = s + "  Case EXPRESSION:\n";
  s = s + "    ' your code here\n";
  s = s + "    \n";
  s = s + "  Case Else\n";
  s = s + "    ' your code here\n";
  s = s + "    \n";
  s = s + "End Select\n";

  return s;
}

QString _insert_select::format2()
{
  QString s = "";

  s = s + "\nSELECT CASE " + g->text() + "\n";
  s = s + "  CASE expression:\n";
  s = s + "    ' your code here\n";
  s = s + "    \n";
  s = s + "  CASE expression:\n";
  s = s + "    ' your code here\n";
  s = s + "    \n";
  s = s + "  CASE ELSE\n";
  s = s + "    ' your code here\n";
  s = s + "    \n";
  s = s + "END SELECT\n";

  return s;
}

// ****  
// ****  
// ****  

_insert_fornext::_insert_fornext( QWidget *parent, _sourcecodeeditor *_editor, QString title, QIcon icon, QString helpStart, QString helpEnd)
    : _insert( parent, _editor, title, icon, helpStart, helpEnd)
{

  QWidget *k = new QWidget(this);

  QVBoxLayout *y = new QVBoxLayout();
  y->setAlignment(Qt::AlignBottom);
  k->setLayout(y);
  grid->addWidget(k, 1, 0, 1, 3);    

  QLabel *l = new QLabel(tr("From-Expression:"), this); y->addWidget(l);

  name = new QLineEdit(this);
  y->addWidget(name);  

  setFocusProxy(name);
  name->setFocus(Qt::ActiveWindowFocusReason);

  connect(name, SIGNAL(textChanged(const QString &)), this, SLOT(textChanged(const QString &)));


  l = new QLabel(tr("To-Expression:"), this); y->addWidget(l);
  name2 = new QLineEdit(this);
  y->addWidget(name2);  
  connect(name2, SIGNAL(textChanged(const QString &)), this, SLOT(textChanged(const QString &)));

  move(QApplication::desktop()->width() / 2 - sizeHint().width() / 2, QApplication::desktop()->height() / 2 - sizeHint().height() / 2);
  show();
  qApp->setActiveWindow(this);

}

void _insert_fornext::textChanged( const QString &s)
{
  se->setText(insert());
}

QString _insert_fornext::format1()
{
  QString s = "";
  
  s = s + "\nFor i As Integer = " + name->text() + " To " + name2->text() + "\n";
  s = s + "  \n";
  s = s + "Next\n";

  return s;
}

QString _insert_fornext::format2()
{
  QString s = "";
  
  s = s + "\nFOR i AS INTEGER = " + name->text() + " TO " + name2->text() + "\n";
  s = s + "  \n";
  s = s + "NEXT\n";

  return s;
}

// ****  
// ****  
// ****  

_insert_loopwhile::_insert_loopwhile( QWidget *parent, _sourcecodeeditor *_editor, QString title, QIcon icon, QString helpStart, QString helpEnd)
    : _insert( parent, _editor, title, icon, helpStart, helpEnd)
{

  QWidget *k = new QWidget(this);

  QVBoxLayout *y = new QVBoxLayout();
  y->setAlignment(Qt::AlignBottom);
  k->setLayout(y);
  grid->addWidget(k, 1, 0, 1, 3);    

  QLabel *l = new QLabel(tr("Condition / Expression:"), this); y->addWidget(l);

  g = new QLineEdit(this);
  y->addWidget(g);  

  setFocusProxy(g);
  g->setFocus(Qt::ActiveWindowFocusReason);

  connect(g, SIGNAL(textChanged(const QString &)), this, SLOT(textChanged(const QString &)));

  move(QApplication::desktop()->width() / 2 - sizeHint().width() / 2, QApplication::desktop()->height() / 2 - sizeHint().height() / 2);
  show();
  qApp->setActiveWindow(this);

}

void _insert_loopwhile::textChanged(const QString &)
{
  se->setText(insert());
}

QString _insert_loopwhile::format1()
{
  QString s = "";
  
  s = s + "\nDo\n";
  s = s + "  \n";
  s = s + "Loop While " + g->text() + "\n";

  return s;
}

QString _insert_loopwhile::format2()
{
  QString s = "";

  s = s + "\nDO\n";
  s = s + "  \n";
  s = s + "LOOP WHILE " + g->text() + "\n";

  return s;
}

// ****  
// ****  
// ****  

_insert_whileloop::_insert_whileloop( QWidget *parent, _sourcecodeeditor *_editor, QString title, QIcon icon, QString helpStart, QString helpEnd)
    : _insert( parent, _editor, title, icon, helpStart, helpEnd)
{

  QWidget *k = new QWidget(this);

  QVBoxLayout *y = new QVBoxLayout();
  y->setAlignment(Qt::AlignBottom);
  k->setLayout(y);
  grid->addWidget(k, 1, 0, 1, 3);    

  QLabel *l = new QLabel(tr("Condition / Expression:"), this); y->addWidget(l);

  g = new QLineEdit(this);
  y->addWidget(g);  

  setFocusProxy(g);
  g->setFocus(Qt::ActiveWindowFocusReason);

  connect(g, SIGNAL(textChanged(const QString &)), this, SLOT(textChanged(const QString &)));

  move(QApplication::desktop()->width() / 2 - sizeHint().width() / 2, QApplication::desktop()->height() / 2 - sizeHint().height() / 2);
  show();
  qApp->setActiveWindow(this);

}

void _insert_whileloop::textChanged(const QString &)
{
  se->setText(insert());
}

QString _insert_whileloop::format1()
{
  QString s = "";
  
  s = s + "\nDo While " + g->text() + "\n";
  s = s + "  \n";
  s = s + "Loop\n";

  return s;
}

QString _insert_whileloop::format2()
{
  QString s = "";
  
  s = s + "\nDO WHILE " + g->text() + "\n";
  s = s + "  \n";
  s = s + "LOOP\n";

  return s;
}

// ****  
// ****  
// ****  

_insert_exception::_insert_exception( QWidget *parent, _sourcecodeeditor *_editor, QString title, QIcon icon, QString helpStart, QString helpEnd)
    : _insert( parent, _editor, title, icon, helpStart, helpEnd)
{

  QWidget *k = new QWidget(this);

  QVBoxLayout *y = new QVBoxLayout();
  y->setAlignment(Qt::AlignBottom);
  k->setLayout(y);
  grid->addWidget(k, 1, 0, 1, 3);    

  QLabel *l = new QLabel(tr("Name:"), this); y->addWidget(l);

  g = new QLineEdit(this);
  y->addWidget(g);  

  setFocusProxy(g);
  g->setFocus(Qt::ActiveWindowFocusReason);

  connect(g, SIGNAL(textChanged(const QString &)), this, SLOT(textChanged(const QString &)));

  l = new QLabel(tr("Exception Type:"), this); y->addWidget(l);

  QComboBox *x = r = new QComboBox(this); y->addWidget(r);
  r->setEditable(true);
  x->addItem("");
  x->addItem("Object");
  connect(x, SIGNAL(textChanged( const QString &)), this, SLOT(textChanged( const QString &)));

  move(QApplication::desktop()->width() / 2 - sizeHint().width() / 2, QApplication::desktop()->height() / 2 - sizeHint().height() / 2);
  show();
  qApp->setActiveWindow(this);
}

void _insert_exception::textChanged( const QString &s)
{
  se->setText(insert());
}

QString _insert_exception::format1()
{
  QString s = "";
  
  s = s + "\nTry\n  \n";
  s = s + "Catch (_" + g->text() + " As " + r->currentText() + ")\n";
  s = s + "  \n";
  s = s + "End Catch\n";

  return s;
}

QString _insert_exception::format2()
{
  QString s = "";
  
  s = s + "\nTRY\n  \n";
  s = s + "CATCH (_" + g->text() + " AS " + r->currentText() + ")\n";
  s = s + "  \n";
  s = s + "END CATCH\n";

  return s;
}

// ****  
// ****  
// ****  

_insert_variable::_insert_variable( QWidget *parent, _sourcecodeeditor *_editor, QString title, QIcon icon, QString helpStart, QString helpEnd)
    : _insert( parent, _editor, title, icon, helpStart, helpEnd)
{

  QWidget *k = new QWidget(this);

  QVBoxLayout *y = new QVBoxLayout();
  y->setAlignment(Qt::AlignBottom);
  k->setLayout(y);
  grid->addWidget(k, 1, 0, 1, 3);    

  QLabel *l = new QLabel(tr("Name:"), this); y->addWidget(l);

  g = new QLineEdit(this);
  y->addWidget(g);  

  setFocusProxy(g);
  g->setFocus(Qt::ActiveWindowFocusReason);

  connect(g, SIGNAL(textChanged(const QString &)), this, SLOT(textChanged(const QString &)));

  l = new QLabel(tr("Type:"), this); y->addWidget(l);

  QComboBox *x = r = new QComboBox(this); y->addWidget(r);
  r->setEditable(true);

  x->addItem("");
  x->addItem("Boolean");
  x->addItem("");
  x->addItem("String");
  x->addItem("CString");
  x->addItem("");
  x->addItem("Byte");
  x->addItem("Short");
  x->addItem("Integer");
  x->addItem("Long");
  x->addItem("");
  x->addItem("Variant");
  x->addItem("");
  x->addItem("Object");
  /*
  x->addItem("");
  x->addItem("(Int16)");
  x->addItem("(Int32)");
  x->addItem("(Int64)");
  x->addItem("(UInt16)");
  x->addItem("(UInt32)");
  x->addItem("(UInt64)");*/

  x->addItem("Currency");
  x->addItem("Date");
  x->addItem("Decimal");
  x->addItem("DateTime");

  connect(x, SIGNAL(textChanged( const QString &)), this, SLOT(textChanged( const QString &)));

  move(QApplication::desktop()->width() / 2 - sizeHint().width() / 2, QApplication::desktop()->height() / 2 - sizeHint().height() / 2);
  show();
  qApp->setActiveWindow(this);
}

void _insert_variable::textChanged( const QString &s)
{
  se->setText(insert());
}

QString _insert_variable::format1()
{
  QString s = "";
  
  s = s + "Dim " + g->text();
  if (r->currentText().length()) s = s + " As " + r->currentText();
  s = s + "\n";

  return s;
}

QString _insert_variable::format2()
{
  QString s = "";
  
  s = s + "DIM " + g->text();
  if (r->currentText().length()) s = s + " AS " + r->currentText();
  s = s + "\n";

  return s;
}

// ****  
// ****  
// ****  

_insert_const::_insert_const( QWidget *parent, _sourcecodeeditor *_editor, QString title, QIcon icon, QString helpStart, QString helpEnd)
    : _insert( parent, _editor, title, icon, helpStart, helpEnd)
{

  QWidget *k = new QWidget(this);

  QVBoxLayout *y = new QVBoxLayout();
  y->setAlignment(Qt::AlignBottom);
  k->setLayout(y);
  grid->addWidget(k, 1, 0, 1, 3);    

  QLabel *l = new QLabel(tr("Name:"), this); y->addWidget(l);

  name = new QLineEdit(this);
  y->addWidget(name);  

  setFocusProxy(name);
  name->setFocus(Qt::ActiveWindowFocusReason);

  connect(name, SIGNAL(textChanged(const QString &)), this, SLOT(textChanged(const QString &)));

  l = new QLabel(tr("Const Expression:"), this); y->addWidget(l);
  ex = new QLineEdit(this); y->addWidget(ex);  
  connect(ex, SIGNAL(textChanged( const QString &)), this, SLOT(textChanged( const QString &)));

  l = new QLabel(tr("Const Type:"), this); y->addWidget(l);

  QComboBox *x = r = new QComboBox(this); y->addWidget(r);
  r->setEditable(true);

  x->addItem("");
  x->addItem("Boolean");
  x->addItem("");
  x->addItem("String");
  x->addItem("CString");
  x->addItem("");
  x->addItem("Byte");
  x->addItem("Short");
  x->addItem("Integer");
  x->addItem("Long");
  x->addItem("");
  x->addItem("Variant");
  x->addItem("");
  x->addItem("Object");
  /*
  x->addItem("");
  x->addItem("(Int16)");
  x->addItem("(Int32)");
  x->addItem("(Int64)");
  x->addItem("(UInt16)");
  x->addItem("(UInt32)");
  x->addItem("(UInt64)");*/

  x->addItem("Currency");
  x->addItem("Date");
  x->addItem("Decimal");
  x->addItem("DateTime");

  connect(x, SIGNAL(textChanged( const QString &)), this, SLOT(textChanged( const QString &)));

  move(QApplication::desktop()->width() / 2 - sizeHint().width() / 2, QApplication::desktop()->height() / 2 - sizeHint().height() / 2);
  show();
  qApp->setActiveWindow(this);
}

void _insert_const::textChanged( const QString &s)
{
  se->setText(insert());
}

QString _insert_const::format1()
{
  QString s = "";
  
  s = s + "Const " + name->text();
  if (r->currentText().length()) s = s + " As " + r->currentText();
  if (ex->text().length()) s = s + " = " + ex->text();
  s = s + "\n";

  return s;
}

QString _insert_const::format2()
{
  QString s = "";
  
  s = s + "CONST " + name->text();
  if (r->currentText().length()) s = s + " AS " + r->currentText();
  if (ex->text().length()) s = s + " = " + ex->text();
  s = s + "\n";

  return s;
}

// ****  
// ****  
// ****  

_insert_general::_insert_general(_sourcecodeeditor *_my_sourcecodeeditor, QString sFormat1, QString sFormat2)  
{
  if (true){
    EXTERN_my_mainwindow->performInsertTextInSourceCode(sFormat1);
  } else if (false){
    EXTERN_my_mainwindow->performInsertTextInSourceCode(sFormat2);
  }
}

// ****  
// ****  
// ****  

_insert_sub::_insert_sub( QWidget *parent, _sourcecodeeditor *_editor, QString title, QIcon icon, QString helpStart, QString helpEnd)
    : _insert( parent, _editor, title, icon, helpStart, helpEnd)
{

  QWidget *k = new QWidget(this);

  QVBoxLayout *y = new QVBoxLayout();
  y->setAlignment(Qt::AlignBottom);
  k->setLayout(y);
  grid->addWidget(k, 1, 0, 1, 3);    

  // ***
  QLabel *l = new QLabel(tr("Name:"), this); y->addWidget(l);

  name = new QLineEdit(this); y->addWidget(name);
  connect(name, SIGNAL(textChanged( const QString &)), this, SLOT(textChanged( const QString &)));

  // ***
  l = new QLabel(tr("Your Arguments (argument name / argument type):"), this); y->addWidget(l);

  for (int i = 0; i < 10; i++){
    g[i] = 0;
    ex[i] = 0;
  }

  for (int i = 0; i < 4; i++){

    QWidget *kk = new QWidget(this); y->addWidget(kk);
    QHBoxLayout *yy = new QHBoxLayout();
    yy->setAlignment(Qt::AlignBottom);
    kk->setLayout(yy);

    g[i] = new QLineEdit(this); yy->addWidget(g[i]);

    connect(g[i], SIGNAL(textChanged( const QString &)), this, SLOT(textChanged( const QString &)));

    l = new QLabel(tr(" As "), this); yy->addWidget(l);

    QComboBox *x = ex[i] = new QComboBox(this); yy->addWidget(x);
    ex[i]->setEditable(true);

    x->addItem("");
    x->addItem("Boolean");
    x->addItem("");
    x->addItem("String");
    x->addItem("CString");
    x->addItem("");
    x->addItem("Byte");
    x->addItem("Short");
    x->addItem("Integer");
    x->addItem("Long");
    x->addItem("");
    x->addItem("Variant");
    x->addItem("");
    x->addItem("Object");
    /*
    x->addItem("");
    x->addItem("(Int16)");
    x->addItem("(Int32)");
    x->addItem("(Int64)");
    x->addItem("(UInt16)");
    x->addItem("(UInt32)");
    x->addItem("(UInt64)");*/

    x->addItem("Currency");
    x->addItem("Date");
    x->addItem("Decimal");
    x->addItem("DateTime");

    connect(ex[i], SIGNAL(textChanged( const QString &)), this, SLOT(textChanged( const QString &)));

  }

  setFocusProxy(name);
  name->setFocus(Qt::ActiveWindowFocusReason);

  move(QApplication::desktop()->width() / 2 - sizeHint().width() / 2, QApplication::desktop()->height() / 2 - sizeHint().height() / 2);
  show();
  qApp->setActiveWindow(this);
}

void _insert_sub::textChanged( const QString &s)
{

  se->setText(insert());
}

QString _insert_sub::format1()
{
  QString s = "\nSub " + name->text() + "(";

  for (int i = 0; i < 4; i++){
    
    if (g[i]->text().length()){ 
      s = s + g[i]->text();
      if (ex[i]->currentText().length()) s = s + " As " + ex[i]->currentText() + ", ";
    }
    
  }
  if (s.endsWith(", ")) s = s.left(s.length() - 2);
  s = s + ")";

  s = s + "\n  \nEnd Sub\n";

  return s;
}

QString _insert_sub::format2()
{
  QString s = "\nSUB " + name->text() + "(";

  for (int i = 0; i < 4; i++){
    
    if (g[i]->text().length()){
      s = s + g[i]->text();
      if (ex[i]->currentText().length()) s = s + " AS " + ex[i]->currentText() + ", ";
    }

  }
  if (s.endsWith(", ")) s = s.left(s.length() - 2);
  s = s + ")";

  s = s + "\n  \nEND SUB\n";

  return s;
}


// ****  
// ****  
// ****  

_insert_function::_insert_function( QWidget *parent, _sourcecodeeditor *_editor, QString title, QIcon icon, QString helpStart, QString helpEnd)
    : _insert( parent, _editor, title, icon, helpStart, helpEnd)
{

  QWidget *k = new QWidget(this);

  QVBoxLayout *y = new QVBoxLayout();
  y->setAlignment(Qt::AlignBottom);
  k->setLayout(y);
  grid->addWidget(k, 1, 0, 1, 3);    

  // ***
  QLabel *l = new QLabel(tr("Name:"), this); y->addWidget(l);

  name = new QLineEdit(this); y->addWidget(name);
  connect(name, SIGNAL(textChanged( const QString &)), this, SLOT(textChanged( const QString &)));

  // ***
  l = new QLabel(tr("Your Arguments (argument name / argument type):"), this); y->addWidget(l);

  for (int i = 0; i < 10; i++){
    g[i] = 0;
    ex[i] = 0;
  }

  for (int i = 0; i < 4; i++){

    QWidget *kk = new QWidget(this); y->addWidget(kk);
    QHBoxLayout *yy = new QHBoxLayout();
    yy->setAlignment(Qt::AlignBottom);
    kk->setLayout(yy);

    g[i] = new QLineEdit(this); yy->addWidget(g[i]);

    connect(g[i], SIGNAL(textChanged( const QString &)), this, SLOT(textChanged( const QString &)));

    l = new QLabel(tr(" As "), this); yy->addWidget(l);

    QComboBox *x = ex[i] = new QComboBox(this); yy->addWidget(x);
    ex[i]->setEditable(true);

    x->addItem("");
    x->addItem("Boolean");
    x->addItem("");
    x->addItem("String");
    x->addItem("CString");
    x->addItem("");
    x->addItem("Byte");
    x->addItem("Short");
    x->addItem("Integer");
    x->addItem("Long");
    x->addItem("");
    x->addItem("Variant");
    x->addItem("");
    x->addItem("Object");
    /*
    x->addItem("");
    x->addItem("(Int16)");
    x->addItem("(Int32)");
    x->addItem("(Int64)");
    x->addItem("(UInt16)");
    x->addItem("(UInt32)");
    x->addItem("(UInt64)");*/

    x->addItem("Currency");
    x->addItem("Date");
    x->addItem("Decimal");
    x->addItem("DateTime");

    connect(ex[i], SIGNAL(textChanged( const QString &)), this, SLOT(textChanged( const QString &)));

  }

  l = new QLabel(tr("Return Type"), this); y->addWidget(l);

  QComboBox *x = r = new QComboBox(this); y->addWidget(x);
  x->setEditable(true);

  x->addItem("");
  x->addItem("Boolean");
  x->addItem("");
  x->addItem("String");
  x->addItem("CString");
  x->addItem("");
  x->addItem("Byte");
  x->addItem("Short");
  x->addItem("Integer");
  x->addItem("Long");
  x->addItem("");
  x->addItem("Variant");
  x->addItem("");
  x->addItem("Object");
  /*
  x->addItem("");
  x->addItem("(Int16)");
  x->addItem("(Int32)");
  x->addItem("(Int64)");
  x->addItem("(UInt16)");
  x->addItem("(UInt32)");
  x->addItem("(UInt64)");*/

  x->addItem("Currency");
  x->addItem("Date");
  x->addItem("Decimal");
  x->addItem("DateTime");

  connect(x, SIGNAL(textChanged( const QString &)), this, SLOT(textChanged( const QString &)));

  setFocusProxy(name);
  name->setFocus(Qt::ActiveWindowFocusReason);

  move(QApplication::desktop()->width() / 2 - sizeHint().width() / 2, QApplication::desktop()->height() / 2 - sizeHint().height() / 2);
  show();
  qApp->setActiveWindow(this);
}

void _insert_function::textChanged( const QString &s)
{

  se->setText(insert());
}

QString _insert_function::format1()
{
  QString s = "\nFunction " + name->text() + "(";

  for (int i = 0; i < 4; i++){
    
    if (g[i]->text().length()){ 
      s = s + g[i]->text();
      if (ex[i]->currentText().length()) s = s + " As " + ex[i]->currentText() + ", ";
    }
    
  }
  if (s.endsWith(", ")) s = s.left(s.length() - 2);
  if (r->currentText().length()) s = s + ") As " + r->currentText(); else s = s + ")";

  s = s + "\n  \nEnd Function\n";

  return s;
}

QString _insert_function::format2()
{
  QString s = "\nFUNCTION " + name->text() + "(";

  for (int i = 0; i < 4; i++){
    
    if (g[i]->text().length()){
      s = s + g[i]->text();
      if (ex[i]->currentText().length()) s = s + " AS " + ex[i]->currentText() + ", ";
    }

  }
  if (s.endsWith(", ")) s = s.left(s.length() - 2);
  if (r->currentText().length()) s = s + ") AS " + r->currentText(); else s = s + ")";

  s = s + "\n  \nEND FUNCTION\n";

  return s;
}

// ****  
// ****  
// ****  

_insert_property::_insert_property( QWidget *parent, _sourcecodeeditor *_editor, QString title, QIcon icon, QString helpStart, QString helpEnd)
    : _insert( parent, _editor, title, icon, helpStart, helpEnd)
{

  QWidget *k = new QWidget(this);

  QVBoxLayout *y = new QVBoxLayout();
  y->setAlignment(Qt::AlignBottom);
  k->setLayout(y);
  grid->addWidget(k, 1, 0, 1, 3);    

  QLabel *l = new QLabel(tr("Property Type:"), this); y->addWidget(l);

  name = new QLineEdit(this);
  y->addWidget(name);  

  setFocusProxy(name);
  name->setFocus(Qt::ActiveWindowFocusReason);

  connect(name, SIGNAL(textChanged(const QString &)), this, SLOT(textChanged(const QString &)));

  l = new QLabel(tr("Type:"), this); y->addWidget(l);

  QComboBox *x = r = new QComboBox(this); y->addWidget(r);
  r->setEditable(true);

  x->addItem("");
  x->addItem("Boolean");
  x->addItem("");
  x->addItem("String");
  x->addItem("CString");
  x->addItem("");
  x->addItem("Byte");
  x->addItem("Short");
  x->addItem("Integer");
  x->addItem("Long");
  x->addItem("");
  x->addItem("Variant");
  x->addItem("");
  x->addItem("Object");
  /*
  x->addItem("");
  x->addItem("(Int16)");
  x->addItem("(Int32)");
  x->addItem("(Int64)");
  x->addItem("(UInt16)");
  x->addItem("(UInt32)");
  x->addItem("(UInt64)");*/

  x->addItem("Currency");
  x->addItem("Date");
  x->addItem("Decimal");
  x->addItem("DateTime");

  connect(x, SIGNAL(textChanged( const QString &)), this, SLOT(textChanged( const QString &)));

  move(QApplication::desktop()->width() / 2 - sizeHint().width() / 2, QApplication::desktop()->height() / 2 - sizeHint().height() / 2);
  show();
  qApp->setActiveWindow(this);
}

void _insert_property::textChanged( const QString &s)
{
  se->setText(insert());
}

QString _insert_property::format1()
{
  QString s = "";
  
  s = s + "Private propVar_" + name->text() + " As " + r->currentText() + "\n";

  s = s + "\nProperty " + name->text() + " As " + r->currentText() + "\n\n";

  s = s + "  Get\n";
  s = s + "    Return " + "propVar_" + name->text() + "\n";
  s = s + "  End Get\n  \n";

  s = s + "  Set (_" + name->text() + " As " + r->currentText() + ")\n";
  s = s + "    " + "propVar_" + name->text() + " = " + "_" + name->text() + "\n";
  s = s + "  End Set\n";

  s = s + "\nEnd Property\n";

  return s;
}

QString _insert_property::format2()
{
  QString s = "";
  
  s = s + "PRIVATE propVar_" + name->text() + " AS " + r->currentText() + "\n";

  s = s + "\nPROPERTY " + name->text() + " AS " + r->currentText() + "\n\n";

  s = s + "  GET\n";
  s = s + "    RETURN " + "propVar_" + name->text() + "\n";
  s = s + "  END GET\n  \n";

  s = s + "  SET (_" + name->text() + " AS " + r->currentText() + ")\n";
  s = s + "    " + "propVar_" + name->text() + " = " + "_" + name->text() + "\n";
  s = s + "  END SET\n";

  s = s + "\nEND PROPERTY\n";

  return s;
}

// ****  
// ****  
// ****  

_insert_type::_insert_type( QWidget *parent, _sourcecodeeditor *_editor, QString title, QIcon icon, QString helpStart, QString helpEnd)
    : _insert( parent, _editor, title, icon, helpStart, helpEnd)
{

  QWidget *k = new QWidget(this);

  QVBoxLayout *y = new QVBoxLayout();
  y->setAlignment(Qt::AlignBottom);
  k->setLayout(y);
  grid->addWidget(k, 1, 0, 1, 3);    

  // ***
  QLabel *l = new QLabel(tr("Name:"), this); y->addWidget(l);

  name = new QLineEdit(this); y->addWidget(name);
  connect(name, SIGNAL(textChanged( const QString &)), this, SLOT(textChanged( const QString &)));

  // ***
  l = new QLabel(tr("Your Type (field name / field array / field type):"), this); y->addWidget(l);

  for (int i = 0; i < 10; i++){
    g[i] = 0;
    ex[i] = 0;
    a[i] = 0;
  }

  for (int i = 0; i < 4; i++){

    QWidget *kk = new QWidget(this); y->addWidget(kk);
    QHBoxLayout *yy = new QHBoxLayout();
    yy->setAlignment(Qt::AlignBottom);
    kk->setLayout(yy);

    g[i] = new QLineEdit(this); yy->addWidget(g[i]);

    connect(g[i], SIGNAL(textChanged( const QString &)), this, SLOT(textChanged( const QString &)));

    QComboBox *x = a[i] = new QComboBox(this); yy->addWidget(a[i]);
    //a[i]->setFixedWidth(80);
    a[i]->setEditable(true);

    x->addItem("");
    x->addItem("10");
    x->addItem("100");
    x->addItem("1000");

    connect(a[i], SIGNAL(textChanged( const QString &)), this, SLOT(textChanged( const QString &)));


    l = new QLabel(tr(" As "), this); yy->addWidget(l);

    x = ex[i] = new QComboBox(this); yy->addWidget(x);
    ex[i]->setEditable(true);

    x->addItem("");
    x->addItem("Boolean");
    x->addItem("");
    x->addItem("String * 255");
    x->addItem("");
    x->addItem("Byte");
    x->addItem("Short");
    x->addItem("Integer");
    x->addItem("Long");
    x->addItem("");
    x->addItem("Variant");
    x->addItem("");
    x->addItem("Object");
    /*
    x->addItem("");
    x->addItem("(Int16)");
    x->addItem("(Int32)");
    x->addItem("(Int64)");
    x->addItem("(UInt16)");
    x->addItem("(UInt32)");
    x->addItem("(UInt64)");*/

    x->addItem("Currency");
    x->addItem("Date");
    x->addItem("Decimal");
    x->addItem("DateTime");

    connect(ex[i], SIGNAL(textChanged( const QString &)), this, SLOT(textChanged( const QString &)));

  }

  setFocusProxy(name);
  name->setFocus(Qt::ActiveWindowFocusReason);

  move(QApplication::desktop()->width() / 2 - sizeHint().width() / 2, QApplication::desktop()->height() / 2 - sizeHint().height() / 2);
  show();
  qApp->setActiveWindow(this);
}

void _insert_type::textChanged( const QString &s)
{

  se->setText(insert());
}

QString _insert_type::format1()
{
  QString s = "\nType " + name->text() + "\n";

  for (int i = 0; i < 4; i++){
    
    if (g[i]->text().length()){ 
      s = s + "  " + g[i]->text();
      if (a[i]->currentText().length()) s = s + "[" + a[i]->currentText() + "]";
      if (ex[i]-> currentText().length()) s = s + " As " + ex[i]->currentText() + "\n"; else s = s + "\n";
    }
    
  }

  s = s + "End Type\n";

  return s;
}

QString _insert_type::format2()
{
  QString s = "\nTYPE " + name->text() + "\n";

  for (int i = 0; i < 4; i++){
    
    if (g[i]->text().length()){
      s = s + "  " + g[i]->text();
      if (a[i]->currentText().length()) s = s + "(" + a[i]->currentText() + ")";
      if (ex[i]->currentText().length()) s = s + " AS " + ex[i]->currentText() + "\n"; else s = s + "\n";
    }

  }

  s = s + "END TYPE\n";

  return s;
}

// ****  
// ****  
// ****  

_insert_enum::_insert_enum( QWidget *parent, _sourcecodeeditor *_editor, QString title, QIcon icon, QString helpStart, QString helpEnd)
    : _insert( parent, _editor, title, icon, helpStart, helpEnd)
{

  QWidget *k = new QWidget(this);

  QVBoxLayout *y = new QVBoxLayout();
  y->setAlignment(Qt::AlignBottom);
  k->setLayout(y);
  grid->addWidget(k, 1, 0, 1, 3);    

  // ***
  QLabel *l = new QLabel(tr("Name:"), this); y->addWidget(l);

  name = new QLineEdit(this); y->addWidget(name);
  connect(name, SIGNAL(textChanged( const QString &)), this, SLOT(textChanged( const QString &)));

  // ***
  l = new QLabel(tr("Your Type (field name / field array / field type):"), this); y->addWidget(l);

  for (int i = 0; i < 10; i++){
    g[i] = 0;
    ex[i] = 0;
  }

  for (int i = 0; i < 4; i++){

    QWidget *kk = new QWidget(this); y->addWidget(kk);
    QHBoxLayout *yy = new QHBoxLayout();
    yy->setAlignment(Qt::AlignBottom);
    kk->setLayout(yy);

    g[i] = new QLineEdit(this); yy->addWidget(g[i]);

    connect(g[i], SIGNAL(textChanged( const QString &)), this, SLOT(textChanged( const QString &)));

    l = new QLabel(tr(" = "), this); yy->addWidget(l);

    ex[i] = new QLineEdit(this); yy->addWidget(ex[i]);

    connect(ex[i], SIGNAL(textChanged( const QString &)), this, SLOT(textChanged( const QString &)));

  }

  setFocusProxy(name);
  name->setFocus(Qt::ActiveWindowFocusReason);

  move(QApplication::desktop()->width() / 2 - sizeHint().width() / 2, QApplication::desktop()->height() / 2 - sizeHint().height() / 2);
  show();
  qApp->setActiveWindow(this);
}

void _insert_enum::textChanged( const QString &s)
{

  se->setText(insert());
}

QString _insert_enum::format1()
{
  QString s = "\nEnum " + name->text() + "\n";

  for (int i = 0; i < 4; i++){
    
    if (g[i]->text().length()){ 
      s = s + "  " + g[i]->text();
      if (ex[i]->text().length()) s = s + " = " + ex[i]->text() + "\n"; else s = s + "\n";
    }
    
  }

  s = s + "End Enum\n";

  return s;
}

QString _insert_enum::format2()
{
  QString s = "\nENUM " + name->text() + "\n";

  for (int i = 0; i < 4; i++){
    
    if (g[i]->text().length()){
      s = s + "  " + g[i]->text();
      if (ex[i]->text().length()) s = s + " = " + ex[i]->text() + "\n"; else s = s + "\n";
    }

  }

  s = s + "END ENUM\n";

  return s;
}

// ****  
// ****  
// ****  

_insert_remark::_insert_remark( QWidget *parent, _sourcecodeeditor *_editor, QString title, QIcon icon, QString helpStart, QString helpEnd)
    : _insert( parent, _editor, title, icon, helpStart, helpEnd)
{

  QWidget *k = new QWidget(this);

  QVBoxLayout *y = new QVBoxLayout();
  y->setAlignment(Qt::AlignBottom);
  k->setLayout(y);
  grid->addWidget(k, 1, 0, 1, 3);    

  QLabel *l = new QLabel(tr("Your remark or comment (type without 'or REM or /*):"), this); y->addWidget(l);

  g = new QTextEdit(this);
  y->addWidget(g);  

  setFocusProxy(g);
  g->setFocus(Qt::ActiveWindowFocusReason);

  connect(g, SIGNAL(textChanged()), this, SLOT(textChanged()));

  move(QApplication::desktop()->width() / 2 - sizeHint().width() / 2, QApplication::desktop()->height() / 2 - sizeHint().height() / 2);
  show();
  qApp->setActiveWindow(this);

}

void _insert_remark::textChanged()
{
  se->setText(insert());
}

QString _insert_remark::format1()
{
  return "/* " + g->toPlainText() + " */";
}

QString _insert_remark::format2()
{
  return "/* " + g->toPlainText() + " */";
}
