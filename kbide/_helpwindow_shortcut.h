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

#include <QListWidget>


class _helpwindow_shortcut : public QListWidget 
{
Q_OBJECT

public:
  _helpwindow_shortcut(QWidget *parent);

   void setEnabled(bool b);

  ~_helpwindow_shortcut(void);

private slots:
    void _token__IF();
    void _token__SELECT();
    void _token__DO();
    void _token__LOOP();
    void _token__FOR();
    void _token__DIM();
    void _token__CONST();
    void _token__SUB();
    void _token__FUNCTION();
    void _token__TYPE();
    void _token__ENUM();
    void _token__TRY();
    void _token__CLASS();
    void _token__CONSTRUCTOR();
    void _token__PROPERTY();


};

