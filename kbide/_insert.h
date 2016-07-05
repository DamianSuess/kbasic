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

#include <QDialog>

class QGridLayout;
class QGroupBox;
class QTextEdit;
class QComboBox;
class QLineEdit;

class _mainwindow;
class _sourcecodeeditor;

class _insert : public QDialog
{
    Q_OBJECT

public:
   _insert( QWidget *parent, _sourcecodeeditor *_my_sourcecodeeditor, QString title, QIcon icon, QString helpStart, QString helpEnd);

  static QString loadHelp(QString sSearch, QString sStop, _mainwindow *m);

  QString insert();
  void insert(QString sFormat1, QString sFormat2);

  virtual QString format1();
  virtual QString format2();

  void insertFile(QString sFile, QString sText);

  static QString appendHTMLGeneralTags(QString s);

_sourcecodeeditor *my_sourcecodeeditor;
QGridLayout *grid;

QTextEdit* se;

QString sFilename;
_mainwindow *my_mainwindow;

public slots:


void SLOT_ok();
void SLOT_close();


private:

};

// *****
// *****
// *****

class _insert_option_kbasic : public _insert
{
    Q_OBJECT

public:
   _insert_option_kbasic( QWidget *parent, _sourcecodeeditor *_my_sourcecodeeditor, QString title, QIcon icon, QString helpStart, QString helpEnd, int nDefaultButton = 0);

  QString format1();
  QString format2();

public slots:

void clicked_0 (bool b);
void clicked_1 (bool b);
void clicked_2 (bool b);

protected:
QGroupBox *g; 
int nSelected;


};


// *****
// *****
// *****

class _insert_option_oldbasic : public _insert_option_kbasic
{
    Q_OBJECT
public:
   _insert_option_oldbasic( QWidget *parent, _sourcecodeeditor *_my_sourcecodeeditor, QString title, QIcon icon, QString helpStart, QString helpEnd);
};

// *****
// *****
// *****

class _insert_option_veryoldbasic : public _insert_option_kbasic
{
    Q_OBJECT
public:
   _insert_option_veryoldbasic( QWidget *parent, _sourcecodeeditor *_my_sourcecodeeditor, QString title, QIcon icon, QString helpStart, QString helpEnd);
};

// *****
// *****
// *****

class _insert_assignment : public _insert
{
    Q_OBJECT

public:
   _insert_assignment( QWidget *parent, _sourcecodeeditor *_my_sourcecodeeditor, QString title, QIcon icon, QString helpStart, QString helpEnd);

  QString format1();
  QString format2();
public slots:
   void textChanged();
protected:
  QTextEdit *g;
};

// *****
// *****
// *****

class _insert_statement : public _insert
{
    Q_OBJECT

public:
   _insert_statement( QWidget *parent, _sourcecodeeditor *_my_sourcecodeeditor, QString title, QIcon icon, QString helpStart, QString helpEnd);

  QString format1();
  QString format2();
public slots:
   void textChanged();
protected:
  QTextEdit *g;
};

// *****
// *****
// *****

class _insert_expression : public _insert
{
    Q_OBJECT

public:
   _insert_expression( QWidget *parent, _sourcecodeeditor *_my_sourcecodeeditor, QString title, QIcon icon, QString helpStart, QString helpEnd);

  QString format1();
  QString format2();
public slots:
   void textChanged();
protected:
  QTextEdit *g;
};


// *****
// *****
// *****

class _insert_operator : public _insert
{
    Q_OBJECT

public:
   _insert_operator( QWidget *parent, _sourcecodeeditor *_my_sourcecodeeditor, QString title, QIcon icon, QString helpStart, QString helpEnd);

  QString format1();
  QString format2();
public slots:
   void activated(int index);
protected:
  QComboBox *g;
};

// *****
// *****
// *****

class _insert_if : public _insert
{
    Q_OBJECT

public:
   _insert_if( QWidget *parent, _sourcecodeeditor *_my_sourcecodeeditor, QString title, QIcon icon, QString helpStart, QString helpEnd);

  QString format1();
  QString format2();
public slots:
   void textChanged( const QString &s);     
protected:
  QLineEdit *g;  
};

// *****
// *****
// *****

class _insert_select : public _insert
{
    Q_OBJECT

public:
   _insert_select( QWidget *parent, _sourcecodeeditor *_my_sourcecodeeditor, QString title, QIcon icon, QString helpStart, QString helpEnd);

  QString format1();
  QString format2();
public slots:
   void textChanged( const QString &s);     
protected:
  QLineEdit *g;  
};

// *****
// *****
// *****

class _insert_fornext : public _insert
{
    Q_OBJECT

public:
   _insert_fornext( QWidget *parent, _sourcecodeeditor *_my_sourcecodeeditor, QString title, QIcon icon, QString helpStart, QString helpEnd);

  QString format1();
  QString format2();
public slots:
   void textChanged( const QString &s);     
protected:
  QLineEdit *name;  
  QLineEdit *name2;  
};

// *****
// *****
// *****

class _insert_whileloop : public _insert
{
    Q_OBJECT

public:
   _insert_whileloop( QWidget *parent, _sourcecodeeditor *_my_sourcecodeeditor, QString title, QIcon icon, QString helpStart, QString helpEnd);

  QString format1();
  QString format2();
public slots:
   void textChanged(const QString &);     
protected:
  QLineEdit *g;  
};

// *****
// *****
// *****

class _insert_loopwhile : public _insert
{
    Q_OBJECT

public:
   _insert_loopwhile( QWidget *parent, _sourcecodeeditor *_my_sourcecodeeditor, QString title, QIcon icon, QString helpStart, QString helpEnd);

  QString format1();
  QString format2();
public slots:
   void textChanged(const QString &);     
protected:
  QLineEdit *g;  
};

// *****
// *****
// *****

class _insert_exception : public _insert
{
    Q_OBJECT

public:
   _insert_exception( QWidget *parent, _sourcecodeeditor *_my_sourcecodeeditor, QString title, QIcon icon, QString helpStart, QString helpEnd);

  QString format1();
  QString format2();
public slots:
   void textChanged( const QString &s);     
protected:
  QLineEdit *g;
  QComboBox *r;
};

// *****
// *****
// *****

class _insert_variable : public _insert
{
    Q_OBJECT

public:
   _insert_variable( QWidget *parent, _sourcecodeeditor *_my_sourcecodeeditor, QString title, QIcon icon, QString helpStart, QString helpEnd);

  QString format1();
  QString format2();
public slots:
   void textChanged( const QString &s);     
protected:
  QLineEdit *g;
  QComboBox *r;
};

// *****
// *****
// *****

class _insert_const : public _insert
{
    Q_OBJECT

public:
   _insert_const( QWidget *parent, _sourcecodeeditor *_my_sourcecodeeditor, QString title, QIcon icon, QString helpStart, QString helpEnd);

  QString format1();
  QString format2();
public slots:
   void textChanged( const QString &s);     
protected:
  QLineEdit *name;
  QLineEdit *ex;
  QComboBox *r;
};

// *****
// *****
// *****

class _insert_general
{    

public:
   _insert_general(_sourcecodeeditor *_my_sourcecodeeditor, QString sFormat1, QString sFormat2);
};

// *****
// *****
// *****

class _insert_sub : public _insert
{
    Q_OBJECT

public:
   _insert_sub( QWidget *parent, _sourcecodeeditor *_my_sourcecodeeditor, QString title, QIcon icon, QString helpStart, QString helpEnd);

  QString format1();
  QString format2();
public slots:
   void textChanged( const QString &s);     
protected:
  QLineEdit *name;
  QLineEdit *g[10];
  QComboBox *ex[10];
  QComboBox *a[10];
};

// *****
// *****
// *****

class _insert_function : public _insert
{
    Q_OBJECT

public:
   _insert_function( QWidget *parent, _sourcecodeeditor *_my_sourcecodeeditor, QString title, QIcon icon, QString helpStart, QString helpEnd);

  QString format1();
  QString format2();
public slots:
   void textChanged( const QString &s);     
protected:
  QLineEdit *name;
  QLineEdit *g[10];
  QComboBox *ex[10];
  QComboBox *a[10];
  QComboBox *r;
};


// *****
// *****
// *****

class _insert_property : public _insert
{
    Q_OBJECT

public:
   _insert_property( QWidget *parent, _sourcecodeeditor *_my_sourcecodeeditor, QString title, QIcon icon, QString helpStart, QString helpEnd);

  QString format1();
  QString format2();
public slots:
   void textChanged( const QString &s);     
protected:
  QLineEdit *name;
  QComboBox *r;
};

// *****
// *****
// *****

class _insert_type : public _insert
{
    Q_OBJECT

public:
   _insert_type( QWidget *parent, _sourcecodeeditor *_my_sourcecodeeditor, QString title, QIcon icon, QString helpStart, QString helpEnd);

  QString format1();
  QString format2();
public slots:
   void textChanged( const QString &s);      
protected:
  QLineEdit *name;
  QLineEdit *g[10];
  QComboBox *ex[10];
  QComboBox *a[10];
};

// *****
// *****
// *****

class _insert_enum : public _insert
{
    Q_OBJECT

public:
   _insert_enum( QWidget *parent, _sourcecodeeditor *_my_sourcecodeeditor, QString title, QIcon icon, QString helpStart, QString helpEnd);  

  QString format1();
  QString format2();
public slots:
   void textChanged( const QString &s);   
protected:
  QLineEdit *name;
  QLineEdit *g[10];
  QLineEdit *ex[10];
};

// *****
// *****
// *****

class _insert_remark : public _insert
{
    Q_OBJECT

public:
   _insert_remark( QWidget *parent, _sourcecodeeditor *_my_sourcecodeeditor, QString title, QIcon icon, QString helpStart, QString helpEnd);

  QString format1();
  QString format2();
public slots:
   void textChanged();
protected:
  QTextEdit *g;
};




