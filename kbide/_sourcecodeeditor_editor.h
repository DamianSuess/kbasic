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

#ifndef _sourcecodeeditor_editor_H
#define _sourcecodeeditor_editor_H

#include <QTextEdit>

class _sourcecodeeditor;
class _inputtip;

class _sourcecodeeditor_editor : public QTextEdit
{
  Q_OBJECT

public:
  _sourcecodeeditor_editor(QWidget* parent = 0, _sourcecodeeditor* _my_sourcecodeeditor = 0);
  ~_sourcecodeeditor_editor(void);

  _inputtip *my_inputtip;
  _inputtip *my_inputtip2;
  void showInput();
  void hideInput();
  void hideInput2();

  void performInsertText(QString s);

  _sourcecodeeditor *my_sourcecodeeditor;

  QString getLastIdentifierBeforeBrace();
  QString getLastIdentifierBeforeDot();

  void updateActions();
  void focusInEvent(QFocusEvent *e);

  static void createList();
  static void createList2();

public slots:
  void undo();

private:
  void keyPressEvent(QKeyEvent* e);
  void keyReleaseEvent(QKeyEvent* e);
  void mousePressEvent(QMouseEvent* e);
  void focusOutEvent(QFocusEvent *e);
  void mouseDoubleClickEvent(QMouseEvent* e);
  
  void showHelpEntry(QString k);
  

private slots:
  void textChanged();

private:  


  
  int nOldBlockCount;

  void timerEvent(QTimerEvent *e);


  unsigned int keyPressedTime;
  int nDotPressed;
  int nTimerId;

  bool bInputDot;
  bool bInputBrace;
  bool bInputAs;
  QString sLineBeforeInput;
};


#endif