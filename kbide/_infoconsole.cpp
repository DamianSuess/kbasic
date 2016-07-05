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

#include <QtGui>


#include "_mainwindow.h"
#include "_console.h"
#include "_infoconsole.h"

extern QString kbasicPath(QString sPath);
extern const QIcon &kbasicIcon(QString s);

extern _mainwindow *EXTERN_my_mainwindow;

// ****


#ifdef MAC
_infoconsole::_infoconsole(QWidget *parent) : QDialog(parent) // HIDE
#else
_infoconsole::_infoconsole(QWidget *parent) : QWidget(0)
#endif
{
#ifdef MAC
  Qt::WindowFlags flags = 0; // HIDE
  flags = Qt::Tool; // HIDE
  setWindowFlags(flags); // HIDE
#endif
  te = new QTextEdit(this);
  QGridLayout *l = new QGridLayout(this);
  l->setSpacing(0);
  l->setMargin(0);
  this->setLayout(l);
  l->addWidget(te, 0, 0);
  bEdit = true;
  resize(640, 480);

  setWindowTitle(QObject::tr("Virtual Machine Info"));
  setWindowIcon(kbasicIcon(kbasicPath("ide/VIEW_RUNINFO.png")));
  
  setObjectName("Virtual Machine Info");
#ifdef MAC
  te->setFont(QFont("Courier", 12)); // HIDE
#else
  te->setFont(QFont("Courier", 10));
#endif
  te->setReadOnly(true);

  bSub = false;
  nCounter = 0;
  sMerker = "";

  te->append(tr("Run With Virtual Machine Info (slowest mode)\n"));
  
}


void _infoconsole::view ()
{
  static bool bFirstTime = true;

#ifdef MAC
 // EXTERN_my_mainwindow->workspace->addWindow(this, Qt::Dialog/* | Qt::CustomizeWindowHint | Qt::WindowSystemMenuHint | Qt::WindowTitleHint*/);
  show(); // HIDE
#else
  showMaximized();
#endif

 
  activateWindow();


  if (bFirstTime && (EXTERN_my_mainwindow == 0 || EXTERN_my_mainwindow->isPreferenceSet("IntroductionHelp"))){
    QApplication::restoreOverrideCursor();
    QMessageBox::information(this, QObject::tr("Virtual Machine Info"),
     QObject::tr(
    "The 'Virtual Machine Info' shows you what is happening behind, when "
    "your KBasic program is executed. Here you can find information about the three "
    "different executions steps: 1) scanning, 2) parsing and 3) interpreting "
    "<br><br>"
    "Interpreting means that KBasic's Virtual Machine executes the compiled pseudo-code.<br>"
    "<br>"
    "Watch your program running...<br>"
    )
    );

   bFirstTime = false;
  }
  

}


void _infoconsole::setSub(bool b) 
{
  bSub = b;  
}

void _infoconsole::reset() 
{
  bSub = false;
  te->clear();
  nCounter = 0;
  sMerker = "";


}

void _infoconsole::print(int nValue) // deprecated
{
	static char acText[1024];

	sprintf(acText, "%d", nValue);
  
  printlen(acText, strlen(acText));
}

void _infoconsole::print(const char * txt, int nColor)
{
	/*
  if (nColor == console__BLACK) println("<font color=black>", true);
  else if (nColor == console__RED) println("<font color=red>", true);
  else if (nColor == console__GREEN) println("<font color=gray>", true);
  else if (nColor == console__BROWN) println("<font color=brown>", true);
  else if (nColor == console__BLUE) println("<font color=blue>", true);
  else if (nColor == console__MAGENTA) println("<font color=magenta>", true);
  else if (nColor == console__CYAN) println("<font color=cyan>", true);
  else if (nColor == console__WHITE) println("<font color=white>", true);
*/
	printlen(txt, strlen(txt));
 // println("</font>", true);
}

void _infoconsole::print(const char * txt)
{

	printlen(txt, strlen(txt));
}

void _infoconsole::header(const char * txt)
{

  println("<font color=red>", true);
	printlen(txt, strlen(txt));
  println("</font>", true);
}

void _infoconsole::printlen(const char * txt, int nLen)
{
	static char acText[102400]; //  dangerous buffer overflow

	memcpy(acText, txt, nLen);
	acText[nLen] = 0;
	
	println(acText);
}

void _infoconsole::printCR()
{

	printlen("\n", 1/*strlen("\n")*/);
}

void _infoconsole::pcodePrintCR()
{
	
	printCR();
}

void _infoconsole::pcodePrintOpc(const char * txt)
{
	static char acText[1024];


  if (strstr(txt, "ENTER_LOCAL") != 0){
    bSub = true;
  } else if (strstr(txt, "CALL_RETURN") != 0){
    bSub = false;
//  } else if (strcmp(txt, "") == 0){
//    bSub = false;
  }

	sprintf(acText, "%-16.16s", txt);

  println("<b>", true);
  println(acText);
  println("</b>", true);
}

void _infoconsole::pcodePrintVar(const char *acModule, const char *acSub, const char *acVar)
{
	static char acText[1024];


	sprintf(acText, " ");
	if (acModule[0] != 0) sprintf(acText, "%s%s", acText, acModule);
	if (acSub[0] != 0) sprintf(acText, "%s.%s", acText, acSub);

	if (acModule[0] != 0 || acSub[0] != 0) sprintf(acText, "%s.", acText);
	sprintf(acText, "%s%s", acText, acVar);

  println("<font color=darkRed>", true);
  println(acText);
  println("</font>", true);
}

void _infoconsole::pcodePrintVar(const char *acVar)
{
	static char acText[1024];


	sprintf(acText, " ");
	sprintf(acText, "%s%s", acText, acVar);

  println("<font color=darkRed>", true);
  println(acText);
  println("</font>", true);
}

void _infoconsole::pcodePrintSep(const char * txt)
{
	static char acText[1024];


  if (bSub && (txt[0] != 0) == 0){
    sprintf(acText, "| %-18.18s|", "");
  } else if (bSub){
    sprintf(acText, "| %-18.18s|", txt);
  } else {
    sprintf(acText, " %-20.20s", txt);
  }

  if (bSub){
    println("<font color=darkMagenta>", true);
  } else {
    println("<font color=blue>", true);
  }
  println(acText);
  println("</font>", true);
}

void _infoconsole::pcodePrintOpcBinary(unsigned char code)
{
	static char acText[1024]; //  dynamic string

	char c = code;
	if (c < 32) c = 32;


	sprintf(acText, "%c", c);
	sprintf(acText, "%s%3d", acText, code);
	
  pcodePrint(acText);
}

void _infoconsole::pcodePrintPos(int nValue)
{
	static char acText[1024];

  sprintf(acText, "%06d: ", nValue);
  
  println("<font color=gray><sub>", true);
  printlen(acText, strlen(acText));
  println("</sub></font>", true);
}

void _infoconsole::pcodePrintPos(const char *s)
{
	static char acText[1024];


  sprintf(acText, "%7s ", s);
  
  printlen(acText, strlen(acText));
}

void _infoconsole::pcodePrint(long lValue)
{
	static char acText[1024];

  sprintf(acText, "%lld", lValue);
  
  printlen(acText, strlen(acText));
}

void _infoconsole::pcodePrint(double dValue)
{
	static char acText[1024];

  sprintf(acText, "%.6f", dValue);  

  printlen(acText, strlen(acText));
}

void _infoconsole::pcodePrint2(const char * txt)
{
	static char acText[102400]; //  dangerous buffer overflow

	int nLen = strlen(txt);
  
    
	memcpy((void *) (acText + 2), txt, nLen);
	nLen++;
	acText[0] = ' ';
	acText[1] = '"';
	acText[1 + nLen++] = '"';
	acText[1 + nLen++] = ',';
	acText[1 + nLen++] = 0;

  printlen(acText, strlen(acText));
}

void _infoconsole::pcodePrint3(const char * txt)
{
	static char acText[102400]; //  dangerous buffer overflow

	int nLen = strlen(txt);
  
    
	memcpy((void *) (acText + 2), txt, nLen);
	nLen++;
	acText[0] = ' ';
	acText[1] = '"';
	acText[1 + nLen++] = '"';
	acText[1 + nLen++] = 0;

  printlen(acText, strlen(acText));
}

void _infoconsole::pcodePrint(const char * txt)
{

	pcodePrint(txt, strlen(txt));
}

void _infoconsole::pcodePrint(const char * txt, int nLen)
{
	static char acText[102400]; //  dangerous buffer overflow

  
	memcpy((void *) (acText + 1), txt, nLen);
	nLen++;
	acText[0] = ' ';
	acText[nLen++] = 0;

	printlen(acText, strlen(acText));
}

void _infoconsole::pcodePrint(const char * txt, void *p)
{
	static char acText[1024];

	sprintf(acText, "%s 0x%X", txt, p);

	printlen(acText, strlen(acText));
}

void _infoconsole::pcodePrint(int nValue)
{
	static char acText[1024];

  sprintf(acText, "%d", nValue);
  
  printlen(acText, strlen(acText));
}

void _infoconsole::printError(const char * txt)
{
	println2 (txt);
}

void _infoconsole::println2(const char *sText)
{
  println(sText);
}



void _infoconsole::println(const char *sText, bool bSyntax)
{
#ifdef WINDOWS // HIDE
  if (EXTERN_my_mainwindow && EXTERN_my_mainwindow->isPreferenceSet("ConsoleDebugInfo")){ // HIDE
    if (!bSyntax) _console::println (sText); // HIDE
  } // HIDE
#endif // HIDE


  if (bEdit == false){
  } else {

    sMerker = sMerker + sText;

    if (strstr(sText, "\n")){ // if newline then append buffer
      te->append(sMerker.left(sMerker.length() - 1));
      sMerker = "";

      if (nCounter++ > 5000){ // clear to save memory
       te->clear();
       nCounter = 0;
       
      }
    }
  }
  
}

