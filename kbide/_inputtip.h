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

#ifndef _inputtip_H
#define _inputtip_H

#include <QListWidget> 

class QString;
class QLabel;

class _sourcecodeeditor_editor;

class _inputtip: public QListWidget
{
Q_OBJECT
public:
  _inputtip(_sourcecodeeditor_editor *e, bool bDot, bool bBrace, bool bAs, QString sSubSyntax, QString sSubDesc, QStringList &ln, QStringList &lt, QStringList &lm);
  ~_inputtip();

  void focusOutEvent (QFocusEvent * e);
  void keyPressEvent (QKeyEvent * e);

  void show();
  void setLabel(QString sLine, int nCursorPos, bool bStart);

  bool isUsedAsLabel();

public slots:
  void itemActivated(QListWidgetItem *item);
  
private:
  void updateControlList();
  void updateControlEventsList();
  void updateAsList();
  void updateDotList();
  void updateDotMethodList();  

  QString currentText();
  QListWidgetItem *itemWithText(QString s);


_sourcecodeeditor_editor *my_sourcecodeeditor_editor;
QString sInputedText;
QString sSub;
QString sSubDesc;

QLabel *label;

bool bDot;
bool bAs;

bool bDoNotLooseFocus;

QStringList ln;
QStringList lt;
QStringList lm;

};



#endif