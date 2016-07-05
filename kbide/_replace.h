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

class QCheckBox;
class QStringList;
class QComboBox;
class QPushButton;

class _sourcecodeeditor;

class _replace : public QDialog
{
    Q_OBJECT

public:
   _replace(_sourcecodeeditor *_my_sourcecodeeditor);
   ~_replace();
 

public slots:

bool findNext(bool bReplaceAll = false, int *nSelectionLength = 0);
void replace();
void replaceAll();
void close();
void toggled(bool bChecked);


private:
_sourcecodeeditor *my_sourcecodeeditor;

QCheckBox *matchCase;
QCheckBox *matchWhole;
QCheckBox *searchUp;
QCheckBox *selectionOnly;
QCheckBox *regex;

QComboBox *search;
QComboBox *search2;

QPushButton *pFindNext;
QPushButton *pReplace;

};


