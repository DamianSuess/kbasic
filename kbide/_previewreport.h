/*
***************************************************************************
Copyright (C) 2000-2007 KBasic Software: www.kbasic.com. All rights reserved.
Source codes are copyrighted by Bernd Noetscher 2000 - 2007.

You may use this source codes under the terms of the GNU Public License (Version 2) as published 
by the Free Software Foundation. 

If you are interested in using the source codes for other licenses or 
commercial development, you must buy commercial licenses from KBasic Software.
***************************************************************************
*/

#ifndef _PREVIEWREPORT_H
#define _PREVIEWREPORT_H

#include <QMainWindow>
#include <QPrinter>

class _form;
class _view;
//class QTextDocument;

class _previewreport : public QMainWindow
{
    Q_OBJECT
public:
    _previewreport(_form *f/*const QTextDocument *document*/, QWidget *parent);
    virtual ~_previewreport();

private slots:
    void print();
    void pageSetup();

private:
    void setup();

    _form *my_form;
    _view *view;
    QPrinter printer;
};

#endif

