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

class _mainwindow;

class _replacefile : public QDialog
{
    Q_OBJECT

public:
   _replacefile(QWidget *_parent);
   ~_replacefile();

public slots:

void findNext();
void close();


private:
_mainwindow *my_mainwindow;

QCheckBox *matchCase;

QComboBox *search;
QComboBox *search2;

};


