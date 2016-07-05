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

#include "_quickcode.h"
#include "_mainwindow.h"
#include "_sourcecodeeditor.h"

#include "_sourcecodeeditor_syntaxhighlighter.h"

extern _mainwindow *EXTERN_my_mainwindow;
extern QDockWidget *EXTERN_Quickcode;

_quickcode::_quickcode(QWidget *parent) : QTextEdit(parent)
{
  _sourcecodeeditor_syntaxhighlighter *highlighter = new _sourcecodeeditor_syntaxhighlighter(document());
}

void _quickcode::keyPressEvent(QKeyEvent* e)
{

  int n  = e->key();
  if (n == Qt::Key_Return || n == Qt::Key_Enter){       

    QTextCursor c = textCursor();
    c.movePosition(QTextCursor::StartOfLine, QTextCursor::MoveAnchor);
    c.movePosition(QTextCursor::EndOfLine, QTextCursor::KeepAnchor);
    QString s = c.selectedText();

    if (EXTERN_my_mainwindow->runRun(!EXTERN_my_mainwindow->isPreferenceSet("ConsoleInfo"), false, false, true, false, false, "", s)){
      EXTERN_Quickcode->hide();
    }

  }
  QTextEdit::keyPressEvent(e);

}
