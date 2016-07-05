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

#ifndef _TOOLBOXWINDOW_FORM_H
#define _TOOLBOXWINDOW_FORM_H

#include <QListWidget>

class _toolboxwindow_form : public QListWidget 
{
Q_OBJECT

public:
  _toolboxwindow_form(QWidget *parent);



private slots:

  void currentRowChanged ( int );
//  void currentItemChanged ( QListWidgetItem * l, QListWidgetItem *ll );
/*
void pointer();
void commandbutton();
void label();
void textbox();
void checkbox();

void radiobutton();
void frame();
void listbox();
void listbox_iconmode();
void combobox();
void combobox_editable();
void tab();

void progressbar();
void progressbar_spinning();
void treeview_listview();
void image();
void hidden();
void timer();
void treeview();

void imagebutton();
void vbox();
void hbox();
void vhbox();
void vsplit();

void hsplit();
void box();
void childcontrol();


void textbox_password();
void label_link();
void line_vertical();
void line_horizontal();

void toolbutton();
void editor();
void browser();
void datebox();
void timebox();
void datetimebox();
void serialport();

void movie();
void sound();
void web();
// CONTROL
void scrollbar();
void slider();
void resizebox();
void commandlinkbutton();
void svg();
void toolbarview();
void formsview();
void spinbox();
*/
};

#endif