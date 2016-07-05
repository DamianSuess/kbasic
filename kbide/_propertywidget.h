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
#include "../kbshared/_property.h"
#include "_qbe_sql_syntaxhighlighter.h"



class _propertywindow;

class _property_header : public QLabel
{
  Q_OBJECT
public:

_property_header(QString text, QWidget *parent, _propertywindow *_pw) : QLabel(text, parent)
{

  setIndent(2);
#ifdef MAC
  QFont f = font(); f.setPixelSize(10); setFont(f); 
#endif
  //f.setUnderline(true);
  //setPaletteForegroundColor(Qt::white); 

  //setFont(f);  
//  setCursor(Qt::pointingHandCursor);

  caption = text;
  pw = _pw;
  on = true;

  setAutoFillBackground(true);
  QPalette p = palette();
  p.setColor(QPalette::WindowText, Qt::white);
  p.setColor(QPalette::Window, Qt::black);  
  setPalette(p);

  setFixedHeight(height() - 6);

  //setPaletteBackgroundColor(Qt::darkBlue);

}

//void mouseReleaseEvent ( QMouseEvent * e );

bool on;
private:
_propertywindow *pw;
QString caption;
};


// *****************

class _property_label : public QLabel
{
  Q_OBJECT
public:

  _property_label(QString text, QWidget *parent, QWidget *_neighbour) : QLabel(text, parent)
{
#ifdef MAC
  QFont f = font(); f.setPixelSize(10); setFont(f); 
#endif
  //setFixedSize(100, 18);
  setIndent(2);
  neighbour = _neighbour;
  caption = text;
  hide();
}

void mouseReleaseEvent ( QMouseEvent * e );

void bold()
{
  QString s = "<b>" + caption + "</b>";
  setText(s);
  //setText(caption);
}

void normal()
{
  setText(caption);
}

_property_label *getNeighbour(int y, bool bNewHeader)
{  
  static bool b = false;

  //if (b == false)
  {
    b = true;

/*
  if (y % 2 == 0){ 
    setAutoFillBackground(true);
    QPalette p = palette();
    p.setColor(QPalette::Window, Qt::lightGray);  
    setPalette(p);

    p.setColor(QPalette::Base, Qt::lightGray);  
    p.setColor(QPalette::Window, Qt::lightGray);      
    neighbour->setPalette(p);
    
  } else {*/
    setAutoFillBackground(true);
    QPalette p = palette();
    p.setColor(QPalette::Window, Qt::white);  
    setPalette(p);

    p.setColor(QPalette::Base, Qt::white);  
    p.setColor(QPalette::Window, Qt::white);      
    neighbour->setPalette(p);
//  }
    neighbour->setFixedHeight(height() - 6);

  }


  
  return this;
}

private:
  QWidget *neighbour;
  QString caption;

};


// *****************


class _property_linelabel : public QLabel
{
  Q_OBJECT
public:
_property_linelabel(QWidget *parent) : QLabel(parent)
{
  setMargin(1);

  bDisplay = false;

  hide();
}

signals:
void textChanged();


public:
void setNeighbour(_property_label *_neighbour)
{
  neighbour = _neighbour;
}

void display(bool bBold = false)
{
  if (bBold) neighbour->bold(); else neighbour->normal();
  neighbour->setHidden(false);
  setHidden(false);

  //neighbour->show();
 // show();
  bDisplay = true;
}

void undisplay()
{
  neighbour->setHidden(true);
  setHidden(true);

  //neighbour->hide();
  //hide();
//  bDisplay = false;
}

void setText(QString s)
{
  QLabel::setText(s);
  emit textChanged();
}

_property_label *getNeighbour(int y, bool bNewHeader = false)
{
  return neighbour->getNeighbour(y, bNewHeader);
}

_property_label * getNeighbour()
{
  return neighbour;
}

bool bDisplay;

private:
_property_label *neighbour;

};


// *****************


class _property_lineedit : public QLineEdit
{
  Q_OBJECT
public:

_property_lineedit(QWidget *parent, QString label, bool _bZoom, QString help = "") : QLineEdit(parent)
{
#ifdef MAC
  QFont f = font(); f.setPixelSize(10); setFont(f); 
#endif
  if (!label.isEmpty()) setNeighbour(new _property_label(label, parent, this));

  parent = parent;
  sHelp = help;

  bZoom = _bZoom;
  sLabel = label;


//  setMargin(0);
//  setSpacing(0);

  setFrame(false);  
  //move(0, 0);

  connect(this, SIGNAL(textChanged(const QString &)), this, SLOT(checkOldValue2()));

  if (bZoom || sHelp.length()){
    pb = new QPushButton(bZoom ? "+" : "?", this);
    pb->setCursor(Qt::ArrowCursor);
    
    
//    pb->setFocusPolicy(NoFocus);
    pb->setAutoDefault(false);
    pb->setDefault(false);

    connect(pb, SIGNAL(released()), this, SLOT(showHelp()));
  } else {
    pb = 0;
  }

  sOldValue = "";
  nOldValue = 0;

  bDisplay = false;

  hide();
  highlighter = 0;  
}

~_property_lineedit()
{
 if (highlighter) delete highlighter; highlighter = 0; 
}

void resizeEvent(QResizeEvent * e)
{
  if (pb){
    pb->move(width() - pb->width(), 0);
    pb->setFixedSize(30, height());
  }
}

public slots:

void showHelp()
{
  if (bZoom){
    b = new QTextEdit(0);
    b->setAcceptRichText(false);
    b->setAttribute(Qt::WA_DeleteOnClose);
    b->setWindowFlags(b->windowFlags() | Qt::Tool);
    if (!sLabel.isEmpty()){
      b->setWindowTitle(sLabel);
    } else {
      b->setWindowTitle("Zoom");
    }

    connect(b, SIGNAL(textChanged()), this, SLOT(textChanged()));
    connect(b, SIGNAL(textChanged()), this, SLOT(emit_editingFinished()));    

    b->setText(QLineEdit::text());
    b->selectAll();
    //b->setAcceptRichText(true);
    b->setGeometry(QApplication::desktop()->width() / 2 - 400 / 2, QApplication::desktop()->height() / 2 - 400 / 2, 400, 400);
    
   // if (highlighter == 0) highlighter = new _qbe_sql_syntaxhighlighter(b->document());

    b->show();
    qApp->setActiveWindow(b);
    b->setFocus();

  } else {
    QTextBrowser *b = new QTextBrowser(0);
    b->setAttribute(Qt::WA_DeleteOnClose);
    b->setWindowFlags(b->windowFlags() | Qt::Tool);
    b->setWindowTitle(tr("Help"));

    b->setText(sHelp);
    b->setGeometry(QApplication::desktop()->width() / 2 - 400 / 2, QApplication::desktop()->height() / 2 - 400 / 2, 400, 400);
    b->show();
    qApp->setActiveWindow(b);
    b->setFocus();
  }
}

void checkOldValue()
{
  nOldValue = 0;
}

void checkOldValue2()
{
  nOldValue++;

}

void emit_editingFinished()
{
  setModified(true);
  emit editingFinished();
}





void textChanged()
{
  QLineEdit::setText(b->toPlainText());
/*
  QString s = b->toPlainText();
  s = s.simplified();
  if (s.startsWith("SELECT ", Qt::CaseInsensitive) 
    || s.startsWith("INSERT ", Qt::CaseInsensitive) 
    || s.startsWith("UPDATE ", Qt::CaseInsensitive) 
    || s.startsWith("DELETE ", Qt::CaseInsensitive) 
    || s.startsWith("MERGE ", Qt::CaseInsensitive) 
    || s.startsWith("TRUNCATE ", Qt::CaseInsensitive) 
    || s.startsWith("COMMIT ", Qt::CaseInsensitive) 
    || s.startsWith("ROLLBACK ", Qt::CaseInsensitive) 
    || s.startsWith("START TRANSACTION ", Qt::CaseInsensitive) 
    || s.startsWith("CREATE TABLE ", Qt::CaseInsensitive) 
    || s.startsWith("DROP TABLE ", Qt::CaseInsensitive) 
    || s.startsWith("GRANT ", Qt::CaseInsensitive))
  {     
    if (highlighter != 0){ delete highlighter; highlighter = 0; }
    highlighter = new _qbe_sql_syntaxhighlighter(b->document());
  }

  QLineEdit::setText(s);*/

}


public:

_qbe_sql_syntaxhighlighter *highlighter;
void focusInEvent ( QFocusEvent * e)
{
  //neighbour->bold();
  checkOldValue();
  QLineEdit::focusInEvent(e);
}

void focusOutEvent ( QFocusEvent * e)
{
  //neighbour->normal();
  checkOldValue();
  QLineEdit::focusOutEvent(e);
}

void setNeighbour(_property_label *_neighbour)
{
  neighbour = _neighbour;
}

void display(bool bBold = false)
{
  if (bBold) neighbour->bold(); else neighbour->normal();
  neighbour->setHidden(false);
  setHidden(false);

  //neighbour->setEnabled(true);
  //setEnabled(true);
//  neighbour->show();
 // show();
  bDisplay = true;
/*
  QPalette p = neighbour->palette();
  p.setColor(QPalette::WindowText, Qt::black);
  neighbour->setPalette(p);*/

}

void undisplay()
{
 // setText("");
  //setText2("");

  neighbour->setHidden(true);
  setHidden(true);

  //neighbour->hide();
  //hide();
//  bDisplay = false;
/*
  QPalette p = neighbour->palette();
  p.setColor(QPalette::WindowText, Qt::white);
  neighbour->setPalette(p);*/

}

void setText(QString s)
{
  if (nOldValue < 2){
    sOldValue = s;
  }
  QLineEdit::setText(s);
}

void setText2(QString s)
{
  QLineEdit::setText(s);
}

void setHelp(QString s)
{
  sHelp = s;
}

QString oldValue()
{
  return sOldValue;
}

_property_label *getNeighbour(int y, bool bNewHeader = false)
{
  return neighbour->getNeighbour(y, bNewHeader);
}

_property_label * getNeighbour()
{
  return neighbour;
}

bool bDisplay;

private:
QTextEdit *b;
_property_label *neighbour;
QString sOldValue;
QString sLabel;

int nOldValue;
QString sHelp;
QPushButton *pb;
QWidget *parent;
bool bZoom;

};


// *****************


class _property_booleancombobox : public QComboBox
{
  Q_OBJECT
public:

_property_booleancombobox(QWidget *parent, QString label) : QComboBox(parent)
{
#ifdef MAC
  QFont f = font(); f.setPixelSize(10); setFont(f); 
#endif
  if (!label.isEmpty()) setNeighbour(new _property_label(label, parent, this));
  setFrame(false);  

  setFocusPolicy(Qt::StrongFocus);

  addItem("");
  addItem("True");
  addItem("False");

  connect(this, SIGNAL(highlighted(int)), this, SLOT(highlighted()));

  bDisplay = false;

  hide();
}

public slots:

void highlighted()
{
  //setFocus();
  //neighbour->bold();
}
public:
void focusInEvent ( QFocusEvent * e)
{
  //neighbour->bold();
  QComboBox::focusInEvent(e);
}

void focusOutEvent ( QFocusEvent * e)
{
  //neighbour->normal();
  QComboBox::focusOutEvent(e);
}

void setNeighbour(_property_label *_neighbour)
{
  neighbour = _neighbour;
}

void display(bool bBold = false)
{
  if (bBold) neighbour->bold(); else neighbour->normal();
  neighbour->setHidden(false);
  setHidden(false);

  //neighbour->show();
  //show();
  bDisplay = true;
}

void undisplay()
{
  //neighbour->setEnabled(false);
  //neighbour->hide();
  //hide();
  //setCurrentIndex(0);
  neighbour->setHidden(true);
  setHidden(true);
//  bDisplay = false;
}

_property_label *getNeighbour(int y, bool bNewHeader = false)
{
  return neighbour->getNeighbour(y, bNewHeader);
}

_property_label *getNeighbour()
{
  return neighbour;
}

bool  bDisplay;

void wheelEvent(QWheelEvent *e)
{
  e->ignore(); // do not change the content by accident using mouse wheel
}

private:
_property_label *neighbour;

};

// *****************


class _property_listcombobox : public QComboBox
{
  Q_OBJECT
public:

_property_listcombobox(QWidget *parent, QString label) : QComboBox(parent)
{
#ifdef MAC
  QFont f = font(); f.setPixelSize(10); setFont(f); 
#endif
  if (!label.isEmpty()) setNeighbour(new _property_label(label, parent, this));
  setFrame(false);  

  setFocusPolicy(Qt::StrongFocus);

  addItem("");

  bDisplay = false;

  hide();
}

void focusInEvent ( QFocusEvent * e)
{
  //neighbour->bold();
  QComboBox::focusInEvent(e);
}

void focusOutEvent ( QFocusEvent * e)
{
  //neighbour->normal();
  QComboBox::focusOutEvent(e);
}

void setNeighbour(_property_label *_neighbour)
{
  neighbour = _neighbour;
}

void display(bool bBold = false)
{
  if (bBold) neighbour->bold(); else neighbour->normal();
  neighbour->setHidden(false);
  setHidden(false);
//  neighbour->show();
  //show();
  bDisplay = true;
}

void undisplay()
{
  //setCurrentIndex(0);
  neighbour->setHidden(true);
  setHidden(true);

//  neighbour->hide();
  //hide();
//  bDisplay = false;
}

_property_label *getNeighbour(int y, bool bNewHeader = false)
{
  return neighbour->getNeighbour(y, bNewHeader);
}

bool bDisplay;


private:
_property_label *neighbour;

};

// *****************


class _property_coloredit : public QWidget
{
  Q_OBJECT
public:

_property_coloredit(QWidget *parent, QString label) : QWidget(parent)
{
#ifdef MAC
  QFont f = font(); f.setPixelSize(10); setFont(f); 
#endif
  le = new _property_lineedit(this, "", false);

  if (!label.isEmpty()) setNeighbour(new _property_label(label, parent, this));
  setAutoFillBackground(true);

  /*
  fr = new QFrame(this);
  fr->setLineWidth(0);
  fr->setFrameStyle(QFrame::Box | QFrame::Plain);
  fr->setFixedSize(10, 10);*/

  le->move(0, 0);

  connect(le, SIGNAL(returnPressed()), this, SLOT(checkColor()));
  connect(le, SIGNAL(editingFinished()), this, SLOT(checkColor()));
  
  pb = new QPushButton("#", this);
  //pb->setFixedSize(30, 18);
  //pb->move(120, 0);
//  pb->setFocusPolicy(NoFocus);
  pb->setAutoDefault(false);
  pb->setDefault(false);

  connect(pb, SIGNAL(released()), this, SLOT(getColor()));

  bSETPROPERTY = false;

  bDisplay = false;

  hide();


}

void resizeEvent(QResizeEvent * e)
{
  if (pb){
    pb->move(width() - pb->width(), 0);
    pb->setFixedSize(30, height());
    le->setFixedSize(width() - pb->width(), height());
  }
  //fr->move(3, height() / 2 - fr->height() / 2);
  
  //le->move(15, height() / 2 - fr->height() / 2);
}

public slots:


void checkColor()
{

  bSETPROPERTY = true;
  QString s = le->text();
  bool ok = false;
  if (s.startsWith("&h") || s.startsWith("&H")){    
    s = s.mid(2);
    int hex = s.toInt( &ok, 16 );
    if (ok){
//      setFrame();
      return;
    }
  }

  int dec = s.toInt( &ok, 10 );     
  if (ok){
    //setFrame();
    return;
  }

  if ((le->text()).isEmpty()){
    setText("");
    //setFrame();
    return;
  }

  bSETPROPERTY = false;
  le->setText2(le->oldValue());

}

void getColor()
{

  QColor c = QColorDialog::getColor(Qt::white, this);

  if (c.isValid()){
    bSETPROPERTY = true;
    QString s;
    s.sprintf("&H%02X%02X%02X" , c.red(), c.green(), c.blue());    
    setText(s);
    selectAll();
    setFocus();
   // setFrame();
  }

}

public:
/*
void setFrame()
{
  QString s = le->text();
  if (s.isEmpty()){
    fr->setLineWidth(0);

    QPalette p = palette();
    p.setColor(QPalette::Window, Qt::white);  
    fr->setPalette(p);

  } else {
    bool ok = false;
    int v = 0;
    if (s.startsWith("&h") || s.startsWith("&H")){    
      s = s.mid(2);
      v = s.toInt( &ok, 16 );
    } else {
      v = s.toInt( &ok, 10 );     
    }

    int r = 0xff & (v >> 16);
    int g = 0xff & (v >> 8);
    int b = 0xff & v;
    fr->setLineWidth(1);

    QPalette p = palette();
    p.setColor(QPalette::Base, QColor(r, g, b));  
    fr->setPalette(p);
  }
}*/

void setFocus()
{
  le->setFocus();
}

void selectAll()
{
  le->selectAll();
}
/*
void setPalette(const QPalette &p)
{
  setPalette(p);

//  le->setPaletteBackgroundColor(c);
 // QWidget::setPaletteBackgroundColor(c);
}*/

void setText(QString s)
{
  le->setText(s);
//  setFrame();
}

void setNeighbour(_property_label *_neighbour)
{
  le->setNeighbour(_neighbour);
}

void show ()
{
 // setFrame();
  QWidget::show();
}

void display(bool bBold = false)
{
  if (bBold) le->getNeighbour()->bold(); else le->getNeighbour()->normal();

  le->getNeighbour()->setHidden(false);
  le->setHidden(false);
  setHidden(false);
//  le->show();
 // show();
 // setFrame();
  bDisplay = true;
}

void undisplay()
{
  //setText("");
  //setFrame();

  le->getNeighbour()->setHidden(true);
  le->setHidden(true);
  setHidden(true);

  //le->undisplay();
  //hide();
//  bDisplay = false;
}

_property_label *getNeighbour(int y, bool bNewHeader = false)
{
  return le->getNeighbour(y, bNewHeader);
}

_property_lineedit *lineedit()
{
  return le;
}

bool SETPROPERTY()
{
  bool b = bSETPROPERTY;
  bSETPROPERTY = false;
  return b;
}

bool bDisplay;

private:
_property_lineedit *le;
QPushButton *pb;
//QFrame *fr;
bool bSETPROPERTY;
};

// *************************


class _property_imageedit : public QWidget
{
  Q_OBJECT
public:

_property_imageedit(QWidget *parent, QString label) : QWidget(parent)
{
  #ifdef MAC
  QFont f = font(); f.setPixelSize(10); setFont(f); 
#endif
  le = new _property_lineedit(this, "", true);

  if (!label.isEmpty()) setNeighbour(new _property_label(label, parent, this));
  setAutoFillBackground(true);

//  le->//setFixedWidth(115);
  le->move(0, 0);
  
#ifndef MAC
  pb2 = new QPushButton("*", this);
  pb2->setAutoDefault(false);
  pb2->setDefault(false);
  connect(pb2, SIGNAL(released()), this, SLOT(getFile2()));
#endif

  pb = new QPushButton("...", this);
//  pb->setFixedSize(30, 18);
  pb->move(width() - pb->width(), 0);
  //pb->move(120, 0);
//  pb->setFocusPolicy(NoFocus);
  pb->setAutoDefault(false);
  pb->setDefault(false);

  connect(pb, SIGNAL(released()), this, SLOT(getFile()));
#ifndef MAC
  pb2->move(width() - pb->width(), 0);
#endif

  bDisplay = false;

  hide();

}

void resizeEvent(QResizeEvent * e)
{
  if (pb){
    pb->move(width() - pb->width(), 0);
    pb->setFixedSize(30, height());
    le->setFixedSize(width() - pb->width(), height());
  }
#ifndef MAC
  if (pb2){
    pb2->move(width() - pb->width() - pb2->width(), 0);
    pb2->setFixedSize(30, height());
    le->setFixedSize(width() - pb->width() - pb2->width(), height());
  }
#endif
}

public slots:

void getFile()
{
  QFileDialog *fd = new QFileDialog( this, tr("Choose a file"));
  fd->setFilter( tr("Media Files (*.png *.mng *.jpg *.jpeg *.mpg *.mpeg *.mp3 *.avi *.wmv *.gif)") );
  // *.pbm *.pgm *.ppm *.xbm *.xpm  *.bmp

  if ( fd->exec() == QDialog::Accepted ){
    QStringList l = fd->selectedFiles();
    le->setText(l.size() ? l.at(0) : "");
    selectAll();
    setFocus();    
  }

  delete fd;

}

void getFile2();

public:

void setFocus()
{
  le->setFocus();
}

void selectAll()
{
  le->selectAll();
}
/*
void setPalette(const QPalette &p)
{
  setPalette(p);

//  le->setPaletteBackgroundColor(c);
//  QWidget::setPaletteBackgroundColor(c);
}
*/
void setText(QString s)
{
  le->setText(s);
}

void setNeighbour(_property_label *_neighbour)
{
  le->setNeighbour(_neighbour);
}

void display(bool bBold = false)
{
  if (bBold) le->getNeighbour()->bold(); else le->getNeighbour()->normal();
  le->getNeighbour()->setHidden(false);
  le->setHidden(false);
  setHidden(false);
  //le->show();
  //show();
  bDisplay = true;
}

void undisplay()
{
  //setText("");

  le->getNeighbour()->setHidden(true);
  le->setHidden(true);
  setHidden(true);
//  le->undisplay();
 // hide();
//  bDisplay = false;
}

_property_label *getNeighbour(int y, bool bNewHeader = false)
{
  return le->getNeighbour(y, bNewHeader);
}

_property_lineedit *lineedit()
{
  return le;
}

bool bDisplay;

private:
_property_lineedit *le;
QPushButton *pb;
#ifndef MAC
QPushButton *pb2;
#endif

};


// *************************

class _property_fileedit : public QWidget
{
  Q_OBJECT
public:

_property_fileedit(QWidget *parent, QString label) : QWidget(parent)
{
#ifdef MAC
  QFont f = font(); f.setPixelSize(10); setFont(f); 
#endif
  le = new _property_lineedit(this, "", false);

  if (!label.isEmpty()) setNeighbour(new _property_label(label, parent, this));
  setAutoFillBackground(true);

//  le->//setFixedWidth(115);
  le->move(0, 0);
  
  pb = new QPushButton("...", this);
//  pb->setFixedSize(30, 18);
  pb->move(120, 0);
//  pb->setFocusPolicy(NoFocus);
  pb->setAutoDefault(false);
  pb->setDefault(false);

  connect(pb, SIGNAL(released()), this, SLOT(getFile()));

  bDisplay = false;

  hide();

}

void resizeEvent(QResizeEvent * e)
{
  if (pb){
    pb->move(width() - pb->width(), 0);
    pb->setFixedSize(30, height());
    le->setFixedSize(width() - pb->width(), height());
  }
}

public slots:

void getFile()
{
  QFileDialog *fd = new QFileDialog( this, tr("Choose a file"));
  fd->setFilter( tr("Files (*.*)") );

  if ( fd->exec() == QDialog::Accepted ){
    QStringList l = fd->selectedFiles();
    le->setText(l.size() ? l.at(0) : "");
    selectAll();
    setFocus();    
  }

  delete fd;

}

public:

void setFocus()
{
  le->setFocus();
}

void selectAll()
{
  le->selectAll();
}
/*
void setPalette(const QPalette &p)
{
  setPalette(p);

//  le->setPaletteBackgroundColor(c);
//  QWidget::setPaletteBackgroundColor(c);
}
*/
void setText(QString s)
{
  le->setText(s);
}

void setNeighbour(_property_label *_neighbour)
{
  le->setNeighbour(_neighbour);
}

void display(bool bBold = false)
{
    if (bBold) le->getNeighbour()->bold(); else le->getNeighbour()->normal();

  le->getNeighbour()->setHidden(false);
  le->setHidden(false);
  setHidden(false);
  //le->show();
  //show();
  bDisplay = true;
}

void undisplay()
{
  //setText("");

  le->getNeighbour()->setHidden(true);
  le->setHidden(true);
  setHidden(true);
//  le->undisplay();
 // hide();
//  bDisplay = false;
}

_property_label *getNeighbour(int y, bool bNewHeader = false)
{
  return le->getNeighbour(y, bNewHeader);
}

_property_lineedit *lineedit()
{
  return le;
}

bool bDisplay;

private:
_property_lineedit *le;
QPushButton *pb;

};


// *************************


class _property_soundedit : public QWidget
{
  Q_OBJECT
public:

_property_soundedit(QWidget *parent, QString label) : QWidget(parent)
{
#ifdef MAC
  QFont f = font(); f.setPixelSize(10); setFont(f); 
#endif
  le = new _property_lineedit(this, "", false);

  if (!label.isEmpty()) setNeighbour(new _property_label(label, parent, this));
  setAutoFillBackground(true);

//  le->//setFixedWidth(115);
  le->move(0, 0);
  
  pb = new QPushButton("...", this);
//  pb->setFixedSize(30, 18);
  pb->move(120, 0);
//  pb->setFocusPolicy(NoFocus);
  pb->setAutoDefault(false);
  pb->setDefault(false);

  connect(pb, SIGNAL(released()), this, SLOT(getFile()));

  bDisplay = false;

  hide();

}

void resizeEvent(QResizeEvent * e)
{
  if (pb){
    pb->move(width() - pb->width(), 0);
    pb->setFixedSize(30, height());
    le->setFixedSize(width() - pb->width(), height());
  }
}

public slots:

void getFile()
{
  QFileDialog *fd = new QFileDialog( this, tr("Choose a file"));
  fd->setFilter( tr("Sounds (*.wav *.*)") );

  if ( fd->exec() == QDialog::Accepted ){
    QStringList l = fd->selectedFiles();
    le->setText(l.size() ? l.at(0) : "");
    selectAll();
    setFocus();    
  }

  delete fd;

}

public:

void setFocus()
{
  le->setFocus();
}

void selectAll()
{
  le->selectAll();
}
/*
void setPalette(const QPalette &p)
{
  setPalette(p);

//  le->setPaletteBackgroundColor(c);
//  QWidget::setPaletteBackgroundColor(c);
}
*/
void setText(QString s)
{
  le->setText(s);
}

void setNeighbour(_property_label *_neighbour)
{
  le->setNeighbour(_neighbour);
}

void display(bool bBold = false)
{
    if (bBold) le->getNeighbour()->bold(); else le->getNeighbour()->normal();

  le->getNeighbour()->setHidden(false);
  le->setHidden(false);
  setHidden(false);
  //le->show();
  //show();
  bDisplay = true;
}

void undisplay()
{
  //setText("");

  le->getNeighbour()->setHidden(true);
  le->setHidden(true);
  setHidden(true);
//  le->undisplay();
 // hide();
//  bDisplay = false;
}

_property_label *getNeighbour(int y, bool bNewHeader = false)
{
  return le->getNeighbour(y, bNewHeader);
}

_property_lineedit *lineedit()
{
  return le;
}

bool bDisplay;

private:
_property_lineedit *le;
QPushButton *pb;

};

// *************************


class _property_pixeledit : public QWidget
{
  Q_OBJECT
public:

_property_pixeledit(QWidget *parent, QString label) : QWidget(parent)
{
#ifdef MAC
  QFont f = font(); f.setPixelSize(10); setFont(f); 
#endif
  le = new _property_lineedit(this, "", false);

  if (!label.isEmpty()) setNeighbour(new _property_label(label, parent, this));
  setAutoFillBackground(true);

  
//  le->//setFixedWidth(115);
  le->move(0, 0);
  
  pb = new QPushButton("@", this);
//  pb->setFixedSize(30, 18);
  pb->move(width() - pb->width(), 0);
//  pb->move(120, 0);
//  pb->setFocusPolicy(NoFocus);
  pb->setAutoDefault(false);
  pb->setDefault(false);

  connect(pb, SIGNAL(released()), this, SLOT(getFile()));

  bDisplay = false;

  hide();

}

void resizeEvent(QResizeEvent * e)
{
  if (pb){
    pb->move(width() - pb->width(), 0);
    pb->setFixedSize(30, height());
    le->setFixedSize(width() - pb->width(), height());
  }
}

static inline int pixels2Inches(float pixels)
{
  return qRound(pixels / qApp->desktop()->screen()->logicalDpiY());
}

static inline int inches2Pixels(float inches)
{
    return qRound(inches * qApp->desktop()->screen()->logicalDpiY());
}

static inline qreal cm2Inches(double mm)
{
    return mm * 0.39370147;
}

static inline qreal inches2cm(double mm)
{
    return mm / 0.39370147;
}

public slots:

void getFile();

public:

void setFocus()
{
  le->setFocus();
}

void selectAll()
{
  le->selectAll();
}
/*
void setPalette(const QPalette &p)
{
  setPalette(p);

//  le->setPaletteBackgroundColor(c);
//  QWidget::setPaletteBackgroundColor(c);
}
*/
void setText(QString s)
{
  le->setText(s);
}

void setNeighbour(_property_label *_neighbour)
{
  le->setNeighbour(_neighbour);
}

void display(bool bBold = false)
{
    if (bBold) le->getNeighbour()->bold(); else le->getNeighbour()->normal();

  le->getNeighbour()->setHidden(false);
  le->setHidden(false);
  setHidden(false);
  //le->show();
  //show();
  bDisplay = true;
}

void undisplay()
{
  //setText("");

  le->getNeighbour()->setHidden(true);
  le->setHidden(true);
  setHidden(true);
//  le->undisplay();
 // hide();
//  bDisplay = false;
}

_property_label *getNeighbour(int y, bool bNewHeader = false)
{
  return le->getNeighbour(y, bNewHeader);
}

_property_lineedit *lineedit()
{
  return le;
}

bool bDisplay;

private:
_property_lineedit *le;
QPushButton *pb;

};

// *************************

class _property_colorimageedit : public QWidget
{
  Q_OBJECT
public:

_property_colorimageedit(QWidget *parent, QString label) : QWidget(parent)
{
#ifdef MAC
  QFont f = font(); f.setPixelSize(10); setFont(f); 
#endif
  le = new _property_lineedit(this, "", false);

  if (!label.isEmpty()) setNeighbour(new _property_label(label, parent, this));
  setAutoFillBackground(true);

//  le->//setFixedWidth(115);
  le->move(0, 0);
  
  pb3 = new QPushButton("#", this);
  pb3->move(120, 0);
  pb3->setAutoDefault(false);
  pb3->setDefault(false);

#ifndef MAC
  pb2 = new QPushButton("*", this);
  pb2->setAutoDefault(false);
  pb2->setDefault(false);
  connect(pb2, SIGNAL(released()), this, SLOT(getFile2()));
#endif

  pb = new QPushButton("...", this);
  pb->move(120, 0);
  pb->setAutoDefault(false);
  pb->setDefault(false);

  connect(pb, SIGNAL(released()), this, SLOT(getFile()));
  connect(pb3, SIGNAL(released()), this, SLOT(getColor()));

  bDisplay = false;

  hide();

}

void resizeEvent(QResizeEvent * e)
{
  if (pb){
    pb->setFixedSize(30, height());
#ifndef MAC
    pb2->setFixedSize(30, height());
#endif
    pb3->setFixedSize(30, height());

    pb->move(width() - pb->width(), 0);
#ifndef MAC
    pb2->move(width() - pb->width() - pb2->width(), 0);
    pb3->move(width() - pb->width() - pb2->width() - pb3->width(), 0);
    le->setFixedSize(width() - pb->width() - pb2->width() - pb3->width(), height());
#else
    pb3->move(width() - pb->width() - pb3->width(), 0);
    le->setFixedSize(width() - pb->width(), height());
#endif

  }
}

public slots:

void getFile()
{
  QFileDialog *fd = new QFileDialog( this, tr("Choose a file"));
  fd->setFilter( tr("Images (*.png *.mng *.jpg *.jpeg *.bmp *.gif *.pbm *.pgm *.ppm *.xbm *.xpm)") );

  if ( fd->exec() == QDialog::Accepted ){
    QStringList l = fd->selectedFiles();
    le->setText(l.size() ? l.at(0) : "");
    selectAll();
    setFocus();    
  }

  delete fd;

}

void getFile2();

void getColor()
{

  QColor c = QColorDialog::getColor(Qt::white, this);

  if (c.isValid()){
    QString s;
    s.sprintf("&H%02X%02X%02X" , c.red(), c.green(), c.blue());    
    le->setText(s);
    selectAll();
    setFocus();
  }

}

public:

void setFocus()
{
  le->setFocus();
}

void selectAll()
{
  le->selectAll();
}
/*
void setPalette(const QPalette &p)
{
  setPalette(p);

//  le->setPaletteBackgroundColor(c);
//  QWidget::setPaletteBackgroundColor(c);
}
*/
void setText(QString s)
{
  le->setText(s);
}

void setNeighbour(_property_label *_neighbour)
{
  le->setNeighbour(_neighbour);
}

void display(bool bBold = false)
{
    if (bBold) le->getNeighbour()->bold(); else le->getNeighbour()->normal();

  le->getNeighbour()->setHidden(false);
  le->setHidden(false);
  setHidden(false);
  //le->show();
  //show();
  bDisplay = true;
}

void undisplay()
{
  //setText("");

  le->getNeighbour()->setHidden(true);
  le->setHidden(true);
  setHidden(true);
//  le->undisplay();
 // hide();
//  bDisplay = false;
}

_property_label *getNeighbour(int y, bool bNewHeader = false)
{
  return le->getNeighbour(y, bNewHeader);
}

_property_lineedit *lineedit()
{
  return le;
}

bool bDisplay;

private:
_property_lineedit *le;
QPushButton *pb;
#ifndef MAC
QPushButton *pb2;
#endif
QPushButton *pb3;

};

// *************************

class _property_choicebox : public QWidget
{
  Q_OBJECT

public:

_property_choicebox(QWidget *parent, QString label) : QWidget(parent)
{
#ifdef MAC
  QFont f = font(); f.setPixelSize(10); setFont(f); 
#endif
  le = new _property_lineedit(this, "", false);

  if (!label.isEmpty()) setNeighbour(new _property_label(label, parent, this));
  //setFixedHeight(18);
  setAutoFillBackground(true);

//  le->//setFixedWidth(115);
  le->move(0, 0);

  le->setReadOnly(true);
  
  pb = new QPushButton("...", this);
  pb->setFixedSize(30, 18);
  pb->move(120, 0);
//  pb->setFocusPolicy(NoFocus);
  pb->setAutoDefault(false);
  pb->setDefault(false);

  connect(pb, SIGNAL(released()), this, SLOT(get()));

  bDisplay = false;

  hide();
}

void resizeEvent(QResizeEvent * e)
{
  if (pb){
    pb->move(width() - pb->width(), 0);
    pb->setFixedSize(30, height());
    le->setFixedSize(width() - pb->width(), height());
  }
}

public slots:

void get();


public:
/*
void setPalette(const QPalette &p)
{
  setPalette(p);
//  le->setPaletteBackgroundColor(c);
 // QWidget::setPaletteBackgroundColor(c);
}
*/
void selectAll()
{
  le->setFocus();
  le->selectAll();
}

void setText(QString s)
{
  le->setText(s);
}

QString text()
{
  return le->text();
}

void setNeighbour(_property_label *_neighbour)
{
  le->setNeighbour(_neighbour);
}

void set(QString s)
{
  sSet = s;
}

void display(bool bBold = false)
{
    if (bBold) le->getNeighbour()->bold(); else le->getNeighbour()->normal();

  le->getNeighbour()->setHidden(false);
  le->setHidden(false);
  setHidden(false);
//  le->show();
 // show();
  bDisplay = true;
}

void undisplay()
{
 // setText("");

  le->getNeighbour()->setHidden(true);
  le->setHidden(true);
  setHidden(true);
  //le->undisplay();
  //hide();
//  bDisplay = false;
}

_property_label *getNeighbour(int y, bool bNewHeader = false)
{
  return le->getNeighbour(y, bNewHeader);
}

_property_lineedit *lineedit()
{
  return le;
}

bool bDisplay;

private:
_property_lineedit *le;
QPushButton *pb;
QString sSet;

};

// *************************


class _property_fontedit : public QWidget
{
  Q_OBJECT

public:

_property_fontedit(QWidget *parent, QString label) : QWidget(parent)
{
#ifdef MAC
  QFont f = font(); f.setPixelSize(10); setFont(f); 
#endif
  le = new _property_lineedit(this, "", false);

  if (!label.isEmpty()) setNeighbour(new _property_label(label, parent, this));
  //setFixedHeight(18);
  setAutoFillBackground(true);

//  le->//setFixedWidth(115);
  le->move(0, 0);

  le->setReadOnly(true);
  
  pb = new QPushButton("...", this);
  pb->setFixedSize(30, 18);
  pb->move(120, 0);
//  pb->setFocusPolicy(NoFocus);
  pb->setAutoDefault(false);
  pb->setDefault(false);

  connect(pb, SIGNAL(released()), this, SLOT(getFont()));

  bDisplay = false;

  hide();
}

void resizeEvent(QResizeEvent * e)
{
  if (pb){
    pb->move(width() - pb->width(), 0);
    pb->setFixedSize(30, height());
    le->setFixedSize(width() - pb->width(), height());
  }
}

public slots:

void getFont()
{
  bool ok;
  QFont f;

  if (!(le->text()).isEmpty()){
    f = QFontDialog::getFont( &ok, _property::getFont(le->text()), this);
  } else {
    f = QFontDialog::getFont( &ok, this);
  } 

  if (ok){
    QString s;
    //s.sprintf("%s (%d %s%s%s%s)", f.family().ascii(), f.pointSize(), f.bold() ? "b" : "", f.italic() ? "i" : "", f.underline() ? "u" : "", f.strikeOut() ? "s" : "");    
    setText(f.family());
  }
}

public:
/*
void setPalette(const QPalette &p)
{
  setPalette(p);
//  le->setPaletteBackgroundColor(c);
 // QWidget::setPaletteBackgroundColor(c);
}
*/
void selectAll()
{
  le->setFocus();
  le->selectAll();
}

void setText(QString s)
{
  le->setText(s);
}

void setNeighbour(_property_label *_neighbour)
{
  le->setNeighbour(_neighbour);
}

void display(bool bBold = false)
{
    if (bBold) le->getNeighbour()->bold(); else le->getNeighbour()->normal();

  le->getNeighbour()->setHidden(false);
  le->setHidden(false);
  setHidden(false);
//  le->show();
 // show();
  bDisplay = true;
}

void undisplay()
{
 // setText("");

  le->getNeighbour()->setHidden(true);
  le->setHidden(true);
  setHidden(true);
  //le->undisplay();
  //hide();
//  bDisplay = false;
}

_property_label *getNeighbour(int y, bool bNewHeader = false)
{
  return le->getNeighbour(y, bNewHeader);
}

_property_lineedit *lineedit()
{
  return le;
}

bool bDisplay;

private:
_property_lineedit *le;
QPushButton *pb;

};

// *************************



class _property_event : public QWidget
{
  Q_OBJECT
public:

_property_event(QWidget *parent, QString label) : QWidget(parent)
{
#ifdef MAC
  QFont f = font(); f.setPixelSize(10); setFont(f); 
#endif
  le = new _property_lineedit(this, "", false);

  if (!label.isEmpty()) setNeighbour(new _property_label(label, parent, this));
  //setFixedHeight(18);
  setAutoFillBackground(true);

//  le->//setFixedWidth(115);
  le->move(0, 0);

  le->setReadOnly(true);
  
  pb = new QPushButton("...", this);
  pb->setFixedSize(30, 18);
  pb->move(120, 0);
//  pb->setFocusPolicy(NoFocus);
  pb->setAutoDefault(false);
  pb->setDefault(false);

  connect(pb, SIGNAL(released()), this, SLOT(goEvent()));

  bDisplay = false;

  hide();
}

void resizeEvent(QResizeEvent * e)
{
  if (pb){
    pb->move(width() - pb->width(), 0);
    pb->setFixedSize(30, height());
  }
}

public slots:

void setPropertyWindow(_propertywindow *_pw)
{
  my_propertywindow = _pw;
}

void goEvent();
public:
/*
void setPalette(const QPalette &p)
{
  setPalette(p);
//  le->setPaletteBackgroundColor(c);
  //QWidget::setPaletteBackgroundColor(c);
}*/

void selectAll()
{
  le->setFocus();
  le->selectAll();
}

void setText(QString s)
{
  le->setText(s);
}

void setNeighbour(_property_label *_neighbour)
{
  le->setNeighbour(_neighbour);
}

void display(bool bBold = false)
{
    if (bBold) le->getNeighbour()->bold(); else le->getNeighbour()->normal();

  le->getNeighbour()->setHidden(false);
  le->setHidden(false);
  setHidden(false);
//  le->show();
 // show();
  bDisplay = true;
}

void undisplay()
{
 // setText("");

  le->getNeighbour()->setHidden(true);
  le->setHidden(true);
  setHidden(true);
  //le->undisplay();
  //hide();
//  bDisplay = false;
}

_property_label *getNeighbour(int y, bool bNewHeader = false)
{
  return le->getNeighbour(y, bNewHeader);
}

_property_lineedit *lineedit()
{
  return le;
}

bool bDisplay;

private:
_property_lineedit *le;
QPushButton *pb;
_propertywindow *my_propertywindow;

};
