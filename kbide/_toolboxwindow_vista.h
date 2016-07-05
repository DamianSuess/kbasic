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

#ifndef _TOOLBOXWINDOW_VISTA_H
#define _TOOLBOXWINDOW_VISTA_H

#include <QWidget>

class _toolboxwindow_vista : public QWidget 
{
Q_OBJECT

public:
  _toolboxwindow_vista(QWidget *parent);

private slots:

void pointer();
void vista_bar();
void vista_ball();
void vista_bar_commandbutton();
void vista_window_close();
void vista_window_minimize();
void vista_window_maximize();
void vista_button_arrowleft();
void vista_button_arrowright();
void vista_box_black();
void vista_box_white();
void vista_window_white();
void vista_icon_search();
void vista_imagebox_whiteblack();
void vista_separator_white();
void vista_separator_black();
void vista_textbox_whiteblack();
void vista_button_middle();
void vista_button_left();
void vista_button_right();
void vista_buttonblack_middle();
void vista_selection_black();
void vista_selection_white();
void vista_navigation_bar();
void vista_navigation_left();
void vista_navigation_right();



// CONTROL

};

#endif