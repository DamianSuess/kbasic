/*
***************************************************************************
Copyright (C) 2000-2008 KBasic Software: www.kbasic.com. All rights reserved.
Source codes are copyrighted by Bernd Noetscher 2000-2008.

You may use this source codes under the terms of the GNU Public License (Version 3) 
as published by the Free Software Foundation. 

If you are interested in using the source codes for other licenses or 
commercial development, you must buy commercial licenses from KBasic Software.
***************************************************************************
*/


#ifndef SCREEN_H
#define SCREEN_H


#include <QApplication>
#include <QWidget>


#include "../kbshared/typedef.h"


class screen: public QWidget
{
    Q_OBJECT
public:
  
screen(QWidget *parent = 0);
~screen();

void focusInEvent (QFocusEvent *e);
void focusOutEvent (QFocusEvent *e);
void hideEvent (QHideEvent *e);

void setWindowIcon2();

void activate();
void deactivate();

void setActiveW();
bool isActivated();

void pressAnyKey(bool bPrintText = true);
void clearLastLine();

void line(bool step, int x1, int y1, 
         bool step2, bool expression, int x2, int y2, 
         bool bColor, int color, bool b, bool bf, bool bStyle, int style);
void color(int forecolor, int backcolor);
void cls(int no);
void beep();
char *inkey(int *nKeyPressed);
void print(const char *s);
void print(const QString & s);
char *input();
int pos();
void locate(int y, int x);
int csrlin();
void setActivated(bool b);

// not supported yet:
void circle(bool step, int x, int y, int radius, int color, int start, int end, int aspect);
void paint(bool step, int x, int y, int color, char *pattern, int bordercolor, int backcolor);
void viewprint(int no);
void viewscreen(int no);
void window(int no);
void pmap(int no);
void point(int no);
void draw(int no);
void get(int no);
void put(int no);
void key(int no);

void preset(bool step, int x, int y, int color);
void pset(bool step, int x, int y, bool bColor, int color);
void palette(int no);
void sound(int no);
void play(int no);
void view(int no);

void printScreen(bool bDialog);


void test1();
void test2();

bool bHide;

void captureScreen();


public slots:
void aboutToQuit();


private:


QPixmap m2;


void paintEvent(QPaintEvent *);
void timerEvent( QTimerEvent * );

int nCurrentScreen;
int nForecolor;
int nBackcolor;





void incCursorX();
void incCursorY();
void decCursorX();
void decCursorY();


void setCursorX(int n);
void setCursorY(int n);



void keyPressEvent( QKeyEvent * e);
void keyReleaseEvent ( QKeyEvent * e );

void closeEvent ( QCloseEvent * e );

static int abs(int n);

int nCursorX;
int nCursorY;
bool bCursor;
QFont font;

int nFontWidth;
int nFontHeight;

bool bActivated;
bool bWasActivated;

bool bCTRL;
bool bSHIFT;

int nTimerId;
int nInput;
int nInput2;
QString sInput;
bool bInputted;



};

#endif