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

#include "_helpwindow_shortcut.h"

#include "_mainwindow.h"

_helpwindow_shortcut::_helpwindow_shortcut(QWidget *parent) : QListWidget(parent)
{

  QGridLayout *j = new QGridLayout(this);
  int x = 0;
  int y = 0;

  QPushButton *b;

  j->addWidget((b = new QPushButton("If Then Else", this)), y, x++); connect(b, SIGNAL(clicked(bool)), this, SLOT(_token__IF()));
  j->addWidget((b = new QPushButton("Select Case", this)), y, x++); connect(b, SIGNAL(clicked(bool)), this, SLOT(_token__SELECT()));
  j->addWidget((b = new QPushButton("Do While...", this)), y, x++); connect(b, SIGNAL(clicked(bool)), this, SLOT(_token__DO()));
  y++; x = 0;
  j->addWidget((b = new QPushButton("Do...Loop", this)), y, x++); connect(b, SIGNAL(clicked(bool)), this, SLOT(_token__LOOP()));
  j->addWidget((b = new QPushButton("For...Next", this)), y, x++); connect(b, SIGNAL(clicked(bool)), this, SLOT(_token__FOR()));
  j->addWidget((b = new QPushButton("Dim", this)), y, x++); connect(b, SIGNAL(clicked(bool)), this, SLOT(_token__DIM()));
  y++; x = 0;
  j->addWidget((b = new QPushButton("Const", this)), y, x++); connect(b, SIGNAL(clicked(bool)), this, SLOT(_token__CONST()));
  j->addWidget((b = new QPushButton("Sub", this)), y, x++); connect(b, SIGNAL(clicked(bool)), this, SLOT(_token__SUB()));
  j->addWidget((b = new QPushButton("Function", this)), y, x++); connect(b, SIGNAL(clicked(bool)), this, SLOT(_token__FUNCTION()));
  y++; x = 0;
  j->addWidget((b = new QPushButton("Property", this)), y, x++); connect(b, SIGNAL(clicked(bool)), this, SLOT(_token__PROPERTY()));
  j->addWidget((b = new QPushButton("Type", this)), y, x++); connect(b, SIGNAL(clicked(bool)), this, SLOT(_token__TYPE()));
  j->addWidget((b = new QPushButton("Enum", this)), y, x++); connect(b, SIGNAL(clicked(bool)), this, SLOT(_token__ENUM()));
#ifndef MAC
  y++; x = 0;
  j->addWidget((b = new QPushButton("Try Catch", this)), y, x++); connect(b, SIGNAL(clicked(bool)), this, SLOT(_token__TRY()));
  j->addWidget((b = new QPushButton("Class", this)), y, x++); connect(b, SIGNAL(clicked(bool)), this, SLOT(_token__CLASS()));
  j->addWidget((b = new QPushButton("Constructor", this)), y, x++); connect(b, SIGNAL(clicked(bool)), this, SLOT(_token__CONSTRUCTOR()));
#endif
  
  setLayout(j);

  setMinimumSize(250, 150);

}

_helpwindow_shortcut::~_helpwindow_shortcut(void)
{
}

/*
QSize _helpwindow_shortcut::sizeHint()
{
  return QSize(150, 150);
}*/

void _helpwindow_shortcut::setEnabled(bool b)
{
  QObjectList l = children();
  for (int i = 0; i < l.size(); i++){
    QPushButton *p = qobject_cast<QPushButton *>(l.at(i));
    if (p) p->setEnabled(b);
  }
}

void _helpwindow_shortcut::_token__IF()
{
  if (true){
    QString s = 
      "If CONDITION Then\n"
      "  \n"
      "Else\n"
      "  \n"
      "End If\n"  
      ;
    EXTERN_my_mainwindow->performInsertTextInSourceCode(s);
  } else if (false){
    QString s = 
      "IF condition THEN\n"
      "  \n"
      "ELSE\n"
      "  \n"
      "END IF\n"  
      ;
    EXTERN_my_mainwindow->performInsertTextInSourceCode(s);
  }
  
}

void _helpwindow_shortcut::_token__SELECT()
{
  if (true){
    QString s = 
      "Select Case EXPRESSION\n"
      "  Case EXPRESSION1\n"
      "    \n"
      "  Case EXPRESSION2\n"
      "    \n"
      "  Case EXPRESSION3\n"
      "    \n"
      "End Select\n" ;
    EXTERN_my_mainwindow->performInsertTextInSourceCode(s);
  } else if (false){
    QString s = 
      "SELECT CASE expression\n"
      "  CASE expression1\n"
      "    \n"
      "  CASE expression2\n"
      "    \n"
      "  CASE expression3\n"
      "    \n"
      "END SELECT\n" ;
    EXTERN_my_mainwindow->performInsertTextInSourceCode(s);
  }
  
  
}

void _helpwindow_shortcut::_token__DO()
{
  if (true){
    QString s = 
      "Do While CONDITION\n"
      "  \n"
      "Loop\n"  
      ;
    EXTERN_my_mainwindow->performInsertTextInSourceCode(s);
  } else if (false){
    QString s = 
      "DO WHILE condition\n"
      "  \n"
      "LOOP\n"  
      ;
    EXTERN_my_mainwindow->performInsertTextInSourceCode(s);
  }
  
  
}

void _helpwindow_shortcut::_token__LOOP()
{
  if (true){
    QString s = 
      "Do\n"
      "  \n"
      "Loop While CONDITION\n"  
      ;
    EXTERN_my_mainwindow->performInsertTextInSourceCode(s);
  } else if (false){
    QString s = 
      "DO\n"
      "  \n"
      "LOOP WHILE condition\n"  
      ;
    EXTERN_my_mainwindow->performInsertTextInSourceCode(s);
  }
  
  
}

void _helpwindow_shortcut::_token__FOR()
{
  if (true){
    QString s = 
      "For COUNTER = START To ENDING\n"
      "  \n"
      "Next\n"  
      ;
    EXTERN_my_mainwindow->performInsertTextInSourceCode(s);
  } else if (false){
    QString s = 
      "FOR counter = start TO ending\n"
      "  \n"
      "NEXT\n"  
      ;
    EXTERN_my_mainwindow->performInsertTextInSourceCode(s);
  }
  
  
}

void _helpwindow_shortcut::_token__DIM()
{
  if (true){
    QString s = 
      "Dim VARIABLE As TYPE\n"  
      ;
    EXTERN_my_mainwindow->performInsertTextInSourceCode(s);
  } else if (false){
    QString s = 
      "DIM variable AS type\n"  
      ;
    EXTERN_my_mainwindow->performInsertTextInSourceCode(s);
  }
  
  
}

void _helpwindow_shortcut::_token__CONST()
{
  if (true){
    QString s = 
      "Const NAME = EXPRESSION\n"  
      ;
    EXTERN_my_mainwindow->performInsertTextInSourceCode(s);
  } else if (false){
    QString s = 
      "CONST name = expression\n"  
      ;
    EXTERN_my_mainwindow->performInsertTextInSourceCode(s);
  }
  
  
}

void _helpwindow_shortcut::_token__SUB()
{
  if (true){
    QString s = 
      "Sub SUBNAME(ARGUMENTS)\n"
      "  \n"
      "End Sub\n"  
      ;
    EXTERN_my_mainwindow->performInsertTextInSourceCode(s);
  } else if (false){
    QString s = 
      "SUB subname(arguments)\n"
      "  \n"
      "END SUB\n"  
      ;
    EXTERN_my_mainwindow->performInsertTextInSourceCode(s);
  }
  
  
}

void _helpwindow_shortcut::_token__FUNCTION()
{
  if (true){
    QString s = 
      "Function FUNCTIONNAME(ARGUMENTS) As RETURNTYPE\n"
      "  \n"
      "End Function\n"  
      ;
    EXTERN_my_mainwindow->performInsertTextInSourceCode(s);
  } else if (false){
    QString s = 
      "FUNCTION functionname(arguments) AS returntype\n"
      "  \n"
      "END FUNCTION\n"  
      ;
    EXTERN_my_mainwindow->performInsertTextInSourceCode(s);
  }
  
  
}

void _helpwindow_shortcut::_token__TYPE()
{
  if (true){
    QString s = 
      "Type TYPENAME\n"
      "  ELEMENT1 As TYPE\n"
      "  ELEMENT2 As TYPE\n"
      "  ELEMENT3 As TYPE\n"
      "End Type\n"  
      ;
    EXTERN_my_mainwindow->performInsertTextInSourceCode(s);
  } else if (false){
    QString s = 
      "TYPE typename\n"
      "  element1 AS type\n"
      "  element2 AS type\n"
      "  element3 AS type\n"
      "END TYPE\n"  
      ;
    EXTERN_my_mainwindow->performInsertTextInSourceCode(s);
  }
  
  
}

void _helpwindow_shortcut::_token__ENUM()
{
  if (true){
    QString s = 
      "Enum ENUMNAME\n"
      "  ELEMENT1 = EXPRESSION\n"
      "  ELEMENT2 = EXPRESSION\n"
      "  ELEMENT3 = EXPRESSION\n"
      "End Enum\n"  
      ;
    EXTERN_my_mainwindow->performInsertTextInSourceCode(s);
  } else if (false){
    QString s = 
      "ENUM enumname\n"
      "  element1 = expression\n"
      "  element2 = expression\n"
      "  element3 = expression\n"
      "END ENUM\n"  
      ;
    EXTERN_my_mainwindow->performInsertTextInSourceCode(s);
  }
  
  
}

void _helpwindow_shortcut::_token__TRY()
{
  if (true){
    QString s = 
      "Try\n"
      "  \n"
      "  Catch (EXCEPTION)\n"
      "  \n"
      "End Try\n"  
      ;
    EXTERN_my_mainwindow->performInsertTextInSourceCode(s);
  } else if (false){
    QString s = 
      "TRY\n"
      "  \n"
      "  CATCH (exception)\n"
      "  \n"
      "END TRY\n"  
      ;
    EXTERN_my_mainwindow->performInsertTextInSourceCode(s);
  }
  
  
}

void _helpwindow_shortcut::_token__CLASS()
{
  if (true){
    QString s = 
      "Class CLASSNAME Inherits PARENTCLASS\n"
      "  \n"
      "  Constructor CLASSNAME(ARGUMENTS)\n"
      "    \n"
      "  End Constructor\n"  
      "  \n"
      "End Class\n"  
      ;
    EXTERN_my_mainwindow->performInsertTextInSourceCode(s);

  } else if (false){
    QString s = 
      "CLASS classname INHERITS parentclass\n"
      "  \n"
      "  CONSTRUCTOR classname(arguments)\n"
      "    \n"
      "  END CONSTRUCTOR\n"  
      "  \n"
      "END CLASS\n"  
      ;
    EXTERN_my_mainwindow->performInsertTextInSourceCode(s);
  }
  
  
}

void _helpwindow_shortcut::_token__CONSTRUCTOR()
{
  if (true){
    QString s = 
      "Constructor CLASSNAME(ARGUMENTS)\n"
      "  \n"
      "End Constructor\n"  
      ;
    EXTERN_my_mainwindow->performInsertTextInSourceCode(s);
  } else if (false){
    QString s = 
      "CONSTRUCTOR classname(arguments)\n"
      "  \n"
      "END CONSTRUCTOR\n"  
      ;
    EXTERN_my_mainwindow->performInsertTextInSourceCode(s);
  }
  
  
}

void _helpwindow_shortcut::_token__PROPERTY()
{
  if (true){
    QString s = 
      "Private _NAME As PROPERTYTYPE\n"
      "  Property PROPERTYNAME As PROPERTYTYPE\n"
      "  Set(ByVal Value As PROPERTYTYPE)\n"
      "    _NAME = Value\n"
      "  End Set\n"
      "  Get\n"
      "    return _NAME\n"
      "  End Get\n"
      "End Property\n"  
      ;
    EXTERN_my_mainwindow->performInsertTextInSourceCode(s);
  } else if (false){
    QString s = 
      "PRIVATE _name AS type\n"
      "  PROPERTY propertyname AS propertytype\n"
      "  SET(BYVAL value AS propertytype)\n"
      "    _name = value\n"
      "  END SET\n"
      "  GET\n"
      "    RETURN _name\n"
      "  END GET\n"
      "END PROPERTY\n"  
      ;
    EXTERN_my_mainwindow->performInsertTextInSourceCode(s);
  }
  
  
}
