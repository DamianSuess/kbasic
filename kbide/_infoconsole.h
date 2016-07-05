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

#ifndef _infoconsole_H
#define _infoconsole_H


#include "../kbshared/typedef.h"

#include <qtextedit.h>


class _mainwindow;
class _infoconsole;



#ifdef MAC
class _infoconsole : public QDialog // HIDE
#else
class _infoconsole : public QWidget
#endif
{ 
public:

  _infoconsole(QWidget *parent);


  void print(int nValue); // deprecated
  void print(const char * txt, int nColor);
  void print(const char * txt);
  void header(const char * txt);  
  void printlen(const char * txt, int nLen);
  void printCR();
  void pcodePrintCR();
  void pcodePrintOpc(const char * txt);
  void pcodePrintVar(const char *acModule, const char *acSub, const char *acVar);
  void pcodePrintVar(const char *acVar);
  void pcodePrintSep(const char * txt);
  void pcodePrintOpcBinary(unsigned char code);
  void pcodePrintPos(int nValue);
  void pcodePrintPos(const char *s);
  void pcodePrint(long lValue);
  void pcodePrint(double dValue);
  void pcodePrint2(const char * txt);
  void pcodePrint3(const char * txt);
  void pcodePrint(const char * txt);
  void pcodePrint(const char * txt, int nLen);
  void pcodePrint(const char * txt, void *p);
  void pcodePrint(int nValue);
  void printError(const char * txt);
  void println2(const char *sText);
  void println(const char *sText, bool bSyntax = false);
  void reset();

  void setSub(bool b);

  void view ();

public:
  _mainwindow *my_mainwindow;
 QTextEdit *te;
private:

 bool bEdit;

 QString sMerker;
 bool bSub;
 int nCounter;
 
 

};




#endif