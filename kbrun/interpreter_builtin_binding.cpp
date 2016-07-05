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


#include <stdlib.h>

#include <stdio.h>
#include <math.h>
#include <errno.h>
#include <string.h>

#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <ctype.h>

#include <qdatetime.h>
#include <qdir.h> 

#include "interpreter.h"

extern interpreter *EXTERN_myInterpreter;

extern QString kbNullQString;

extern QLocale *qlocale;

#define M_PI 3.14159265358979323846

function::function(screen *_myScreen, interpreter *_myInterpreter)
{
  myScreen = _myScreen;
  myInterpreter = _myInterpreter;

	myTextbuffer = new textbuffer(); // needed to truncate big input strings or zero terminate them
	myTextbuffer2 = new textbuffer(); // needed to truncate big input strings or zero terminate them

  nLastFILEHANDLE = 0;

#ifdef WINDOWS
  curdrive = 'C'; // HIDE
  curdir = "C:\\"; // HIDE
#else
  curdrive = '/';
  curdir = "/";
#endif

  for (int i = 0; i < 26; i++){
    curdir2[i] = "";
  }
  curdir2[curdrive - 65 < 0 || curdrive - 65 > 25 ? 26 : curdrive - 65] = curdir;

  dir = 0;
  dirIt = 0;
  
}

function::~function()
{
  if (dirIt) delete dirIt;
  if (dir) delete dir;

	
	delete myTextbuffer;
	delete myTextbuffer2;

	closeAllFiles();

}


// ****************************
// * description:
// * prints an error
// *
// * interpreter_parameter:
// * the error messages to print
// *
// * return:
// * false
// ****************************
bool function::error(const char *acError)
{
  myInterpreter->runtimeError(acError);
  //myScreen->print(acError); 	
	return false;
}

void function::fCLS()
{
  myScreen->cls(0);
}

void function::fLINE(t_boolean step, t_integer x1, t_integer y1, 
         t_boolean step2, t_boolean expression, t_integer x2, t_integer y2, 
         t_boolean bColor, t_integer color, t_boolean b, t_boolean bf, t_boolean bStyle, t_integer style)
{
  myScreen->line(step, x1, y1, 
         step2, expression, x2, y2, 
         bColor, color, b, bf, bStyle, style);
}



interpreter_parameter* function::fDATEADD(t_qstring mode, t_integer n, t_date d)
{  
  QDateTime t;

  if (d.nYear || d.nMonth || d.nDay){
    t.setDate(QDate(d.nYear, d.nMonth, d.nDay));
  }

  if (d.nHour || d.nMinute || d.nSecond){
    t.setTime(QTime(d.nHour, d.nMinute, d.nSecond));
  }

  QDateTime k;

  if (*mode == "yyyy"){ // yyyy	Jahr
    k = t.addMonths(n * 12);
  } else if (*mode == "w"){ // w	Wochentag   
    k = t.addDays(n);
  } else if (*mode == "q"){ // q	Quartal
    k = t.addMonths(n * 4);
  } else if (*mode == "ww"){ // ww	Woche
    k = t.addDays(n * 7);
  } else if (*mode == "m"){ //m	Monat	 	
    k = t.addMonths(n);
  } else if (*mode == "h"){ // h	Stunde
    k = t.addSecs(n * 3600);
  } else if (*mode == "y"){ // y	Tag des Jahres	 	
    k = t.addDays(n);
  } else if (*mode == "n"){ // n	Minute
    k = t.addSecs(n * 60);
  } else if (*mode == "d"){ // d	Tag	 	
    k = t.addDays(n);
  } else if (*mode == "s"){ // s	Sekunde
    k = t.addSecs(n);
     
  }

  t_date m(k.date().year(), k.date().month(), k.date().day());

	return new interpreter_parameter((t_date) m);
}

interpreter_parameter* function::fDATEADD(t_cstring mode, t_integer n, t_date d)
{  
  QDateTime t;

  if (d.nYear || d.nMonth || d.nDay){
    t.setDate(QDate(d.nYear, d.nMonth, d.nDay));
  }

  if (d.nHour || d.nMinute || d.nSecond){
    t.setTime(QTime(d.nHour, d.nMinute, d.nSecond));
  }

  QDateTime k;

  if (strcmp(mode, "yyyy") == 0){ // yyyy	Jahr
    k = t.addMonths(n * 12);
  } else if (strcmp(mode, "w") == 0){ // w	Wochentag   
    k = t.addDays(n);
  } else if (strcmp(mode, "q") == 0){ // q	Quartal
    k = t.addMonths(n * 4);
  } else if (strcmp(mode, "ww") == 0){ // ww	Woche
    k = t.addDays(n * 7);
  } else if (strcmp(mode, "m") == 0){ //m	Monat	 	
    k = t.addMonths(n);
  } else if (strcmp(mode, "h") == 0){ // h	Stunde
    k = t.addSecs(n * 3600);
  } else if (strcmp(mode, "y") == 0){ // y	Tag des Jahres	 	
    k = t.addDays(n);
  } else if (strcmp(mode, "n") == 0){ // n	Minute
    k = t.addSecs(n * 60);
  } else if (strcmp(mode, "d") == 0){ // d	Tag	 	
    k = t.addDays(n);
  } else if (strcmp(mode, "s") == 0){ // s	Sekunde
    k = t.addSecs(n);
     
  }

  t_date m(k.date().year(), k.date().month(), k.date().day());

	return new interpreter_parameter((t_date) m);
}

interpreter_parameter* function::fNOW()
{  
  QDateTime k;
  k = QDateTime::currentDateTime();
  t_date t;

  QDate j = k.date();
  QTime j2 = k.time();

  t.nYear = j.year();
  t.nMonth = j.month();
  t.nDay = j.day();

  t.nHour = j2.hour();
  t.nMinute = j2.minute();
  t.nSecond = j2.second();

	return new interpreter_parameter((t_date) t);
}

t_date function::fFILEDATETIME(t_qstring ss)
{
  t_date d;
  
  QString s2 = *ss;
  if (!s2.contains("/") && !s2.contains("\\")){
    QString s = s2;
    s2 = curdir;
    s2 += "/";
    s2 += s;
  }

  QFileInfo f(s2);

  if (f.exists()){
    QDateTime t = f.lastModified();
    if (t.isValid()){
      d.nYear = t.date().year();
      d.nMonth = t.date().month();
      d.nDay = t.date().day();
      d.nHour = t.time().hour();
      d.nMinute = t.time().minute();
      d.nSecond = t.time().second();
    } else {
      t = f.created();
      d.nYear = t.date().year();
      d.nMonth = t.date().month();
      d.nDay = t.date().day();
      d.nHour = t.time().hour();
      d.nMinute = t.time().minute();
      d.nSecond = t.time().second();
    }
  }

  return d;
}

t_date function::fFILEDATETIME(t_cstring ss)
{
  t_date d;

  QString s2 = ss;
  if (!s2.contains("/") && !s2.contains("\\")){
    QString s = ss;
    s2 = curdir;
    s2 += "/";
    s2 += s;
  }

  QFileInfo f(s2);

  if (f.exists()){
    QDateTime t = f.lastModified();
    if (t.isValid()){
      d.nYear = t.date().year();
      d.nMonth = t.date().month();
      d.nDay = t.date().day();
      d.nHour = t.time().hour();
      d.nMinute = t.time().minute();
      d.nSecond = t.time().second();
    } else {
      t = f.created();
      d.nYear = t.date().year();
      d.nMonth = t.date().month();
      d.nDay = t.date().day();
      d.nHour = t.time().hour();
      d.nMinute = t.time().minute();
      d.nSecond = t.time().second();
    }
  }

  return d;
}

t_integer function::fDATEPART(t_qstring mode, t_date d, t_integer firstdayofweek, t_integer firstweekofyear)
{  

  if (firstdayofweek != -1 && firstdayofweek != 1) error("Sorry! FirstDayOfWeek not supported yet. Try to change the data calculation.");
  if (firstweekofyear != -1 && firstweekofyear != 1) error("Sorry! FirstDayOfWeek not supported yet. Try to change the data calculation.");

  QDateTime t;

  if (d.nYear || d.nMonth || d.nDay){
    t.setDate(QDate(d.nYear, d.nMonth, d.nDay));
  }
  if (d.nHour || d.nMinute || d.nSecond){
    t.setTime(QTime(d.nHour, d.nMinute, d.nSecond));
  }

  int y = 0;

  if (*mode == "yyyy"){ // yyyy	Jahr
    y = t.date().year();
  } else if (*mode == "w"){ // w	Wochentag   
    y = t.date().dayOfWeek();
    switch(y){
      case 1: return 2;
      case 2: return 3;
      case 3: return 4;
      case 4: return 5;
      case 5: return 6;
      case 6: return 7;
      case 7: return 1;
    }
    return 0;
  } else if (*mode == "q"){ // q	Quartal
    y = t.date().month() / 4 + 1;  
  } else if (*mode == "ww"){ // ww	Woche
    y = t.date().weekNumber();  
  } else if (*mode == "m"){ //m	Monat	 	
    y = t.date().month();  
  } else if (*mode == "h"){ // h	Stunde
    y = t.time().hour();        
  } else if (*mode == "y"){ // y	Tag des Jahres	 	
    y = t.date().dayOfYear();  
  } else if (*mode == "n"){ // n	Minute
    y = t.time().minute();        
  } else if (*mode == "d"){ // d	Tag	 	
    y = t.date().day();  
  } else if (*mode == "s"){ // s	Sekunde
    y = t.time().second();        
  }

	return y;
}

t_integer function::fDATEPART(t_cstring mode, t_date d, t_integer firstdayofweek, t_integer firstweekofyear)
{  

  if (firstdayofweek != -1 && firstdayofweek != 1) error("Sorry! FirstDayOfWeek not supported yet. Try to change the data calculation.");
  if (firstweekofyear != -1 && firstweekofyear != 1) error("Sorry! FirstDayOfWeek not supported yet. Try to change the data calculation.");

  QDateTime t;

  if (d.nYear || d.nMonth || d.nDay){
    t.setDate(QDate(d.nYear, d.nMonth, d.nDay));
  }
  if (d.nHour || d.nMinute || d.nSecond){
    t.setTime(QTime(d.nHour, d.nMinute, d.nSecond));
  }

  int y = 0;

  if (strcmp(mode, "yyyy") == 0){ // yyyy	Jahr
    y = t.date().year();
  } else if (strcmp(mode, "w") == 0){ // w	Wochentag   
    y = t.date().dayOfWeek();
    switch(y){
      case 1: return 2;
      case 2: return 3;
      case 3: return 4;
      case 4: return 5;
      case 5: return 6;
      case 6: return 7;
      case 7: return 1;
    }
    return 0;
  } else if (strcmp(mode, "q") == 0){ // q	Quartal
    y = t.date().month() / 4 + 1;  
  } else if (strcmp(mode, "ww") == 0){ // ww	Woche
    y = t.date().weekNumber();  
  } else if (strcmp(mode, "m") == 0){ //m	Monat	 	
    y = t.date().month();  
  } else if (strcmp(mode, "h") == 0){ // h	Stunde
    y = t.time().hour();        
  } else if (strcmp(mode, "y") == 0){ // y	Tag des Jahres	 	
    y = t.date().dayOfYear();  
  } else if (strcmp(mode, "n") == 0){ // n	Minute
    y = t.time().minute();        
  } else if (strcmp(mode, "d") == 0){ // d	Tag	 	
    y = t.date().day();  
  } else if (strcmp(mode, "s") == 0){ // s	Sekunde
    y = t.time().second();        
  }

	return y;
}

interpreter_parameter* function::fDATEDIFF(t_qstring mode, t_date d, t_date d2, t_integer firstdayofweek, t_integer firstweekofyear)
{  
  /*
FirstDayOfWeek
vbUseSystem	0 Verwendet die Systemeinstellung
vbSunday	1 Sonntag (Voreinstellung)
vbMonday	2 Montag
vbTuesday	3 Dienstag
vbWednesday	4 Mittwoch
vbThursday	5 Donnerstag
vbFriday	6 Freitag
vbSaturday	7 Samstag

FirstDayOfYear:
vbUseSystem	0 Verwendet die Systemeinstellung
vbFirstJan1	1 Voreinstellung. Die Woche, in der der 1. Januar fällt.
vbFirstFourDays	2 Die Woche, die mindestens 4 Tage im neuen Jahr enthällt.
vbFirstFullWeek	3 Die erste volle Woche des Jahres
  */
  if (firstdayofweek != -1 && firstdayofweek != 1) error("Sorry! FirstDayOfWeek not supported yet. Try to change the data calculation.");
  if (firstweekofyear != -1 && firstweekofyear != 1) error("Sorry! FirstDayOfWeek not supported yet. Try to change the data calculation.");

  QDateTime t;
  QDateTime t2;

  if (d.nYear || d.nMonth || d.nDay){
    t.setDate(QDate(d.nYear, d.nMonth, d.nDay));
  }
  if (d.nHour || d.nMinute || d.nSecond){
    t.setTime(QTime(d.nHour, d.nMinute, d.nSecond));
  }

  if (d2.nYear || d2.nMonth || d2.nDay){
    t2.setDate(QDate(d2.nYear, d2.nMonth, d2.nDay));
  }
  if (d2.nHour || d2.nMinute || d2.nSecond){
    t2.setTime(QTime(d2.nHour, d2.nMinute, d2.nSecond));
  }

  int y = 0;

  if (*mode == "yyyy"){ // yyyy	Jahr
    y = t2.daysTo(t) / 365;
  } else if (*mode == "w"){ // w	Wochentag   
     error("Sorry! \"w\" not supported yet. Try to change the data calculation.");
  } else if (*mode == "q"){ // q	Quartal
    y = t2.daysTo(t) / (3 * 30);        
  } else if (*mode == "ww"){ // ww	Woche
     error("Sorry! \"ww\" not supported yet. Try to change the data calculation.");    
  } else if (*mode == "m"){ //m	Monat	 	
    y = t2.daysTo(t) / 12;    
  } else if (*mode == "h"){ // h	Stunde
    y = t2.secsTo(t) * 3600;            
  } else if (*mode == "y"){ // y	Tag des Jahres	 	
     error("Sorry! \"y\" not supported yet. Try to change the data calculation.");        
  } else if (*mode == "n"){ // n	Minute
    y = t2.secsTo(t) * 60;        
  } else if (*mode == "d"){ // d	Tag	 	
    y = t2.daysTo(t);
  } else if (*mode == "s"){ // s	Sekunde
    y = t2.secsTo(t);    
  }

	return new interpreter_parameter((t_long) y);
}

interpreter_parameter* function::fDATEDIFF(t_cstring mode, t_date d, t_date d2, t_integer firstdayofweek, t_integer firstweekofyear)
{  
  /*
FirstDayOfWeek
vbUseSystem	0 Verwendet die Systemeinstellung
vbSunday	1 Sonntag (Voreinstellung)
vbMonday	2 Montag
vbTuesday	3 Dienstag
vbWednesday	4 Mittwoch
vbThursday	5 Donnerstag
vbFriday	6 Freitag
vbSaturday	7 Samstag

FirstDayOfYear:
vbUseSystem	0 Verwendet die Systemeinstellung
vbFirstJan1	1 Voreinstellung. Die Woche, in der der 1. Januar fällt.
vbFirstFourDays	2 Die Woche, die mindestens 4 Tage im neuen Jahr enthällt.
vbFirstFullWeek	3 Die erste volle Woche des Jahres
  */
  if (firstdayofweek != -1 && firstdayofweek != 1) error("Sorry! FirstDayOfWeek not supported yet. Try to change the data calculation.");
  if (firstweekofyear != -1 && firstweekofyear != 1) error("Sorry! FirstDayOfWeek not supported yet. Try to change the data calculation.");

  QDateTime t;
  QDateTime t2;

  if (d.nYear || d.nMonth || d.nDay){
    t.setDate(QDate(d.nYear, d.nMonth, d.nDay));
  }
  if (d.nHour || d.nMinute || d.nSecond){
    t.setTime(QTime(d.nHour, d.nMinute, d.nSecond));
  }

  if (d2.nYear || d2.nMonth || d2.nDay){
    t2.setDate(QDate(d2.nYear, d2.nMonth, d2.nDay));
  }
  if (d2.nHour || d2.nMinute || d2.nSecond){
    t2.setTime(QTime(d2.nHour, d2.nMinute, d2.nSecond));
  }

  int y = 0;

  if (strcmp(mode, "yyyy") == 0){ // yyyy	Jahr
    y = t2.daysTo(t) / 365;
  } else if (strcmp(mode, "w") == 0){ // w	Wochentag   
     error("Sorry! \"w\" not supported yet. Try to change the data calculation.");
  } else if (strcmp(mode, "q") == 0){ // q	Quartal
    y = t2.daysTo(t) / (3 * 30);        
  } else if (strcmp(mode, "ww") == 0){ // ww	Woche
     error("Sorry! \"ww\" not supported yet. Try to change the data calculation.");    
  } else if (strcmp(mode, "m") == 0){ //m	Monat	 	
    y = t2.daysTo(t) / 12;    
  } else if (strcmp(mode, "h") == 0){ // h	Stunde
    y = t2.secsTo(t) * 3600;            
  } else if (strcmp(mode, "y") == 0){ // y	Tag des Jahres	 	
     error("Sorry! \"y\" not supported yet. Try to change the data calculation.");        
  } else if (strcmp(mode, "n") == 0){ // n	Minute
    y = t2.secsTo(t) * 60;        
  } else if (strcmp(mode, "d") == 0){ // d	Tag	 	
    y = t2.daysTo(t);
  } else if (strcmp(mode, "s") == 0){ // s	Sekunde
    y = t2.secsTo(t);    
  }

	return new interpreter_parameter((t_long) y);
}


/*
t_cstring function::fMONTHNAME(t_integer month, t_boolean shorty)
{
  switch(month){
    case 1: return shorty ? "Jan" : "January";
    case 2: return shorty ? "Feb" : "February";
    case 3: return shorty ? "Mar" : "March";
    case 4: return shorty ? "Apr" : "April";
    case 5: return shorty ? "May" : "May";
    case 6: return shorty ? "Jun" : "June";
    case 7: return shorty ? "Jul" : "July";
    case 8: return shorty ? "Aug" : "August";
    case 9: return shorty ? "Sep" : "September";
    case 10: return shorty ? "Oct" : "October";
    case 11: return shorty ? "Nov" : "November";
    case 12: return shorty ? "Dec" : "December";
  }
  error("month <= 0 or >= 13");
  return "";
}

*/
t_qstring function::fWEEKDAYNAME(t_integer day, t_boolean shorty, t_integer firstdayofweek)
{
  if (firstdayofweek != -1){
    error("Sorry! FirstDayOfWeek not supported yet. Try to change the data calculation.");        
//    if (firstdayofweek == 0) error("Sorry! kbUseSystem not supported yet. Try to change the data calculation.");        
    //day += dayfirstdayofweek - 1;
  }

  switch(day){
    case 1: return shorty ? new QString("Sun") : new QString("Sunday");
    case 2: return shorty ? new QString("Mon") : new QString("Monday");
    case 3: return shorty ? new QString("Tue") : new QString("Tuesday");
    case 4: return shorty ? new QString("Wed") : new QString("Wednesday");
    case 5: return shorty ? new QString("Thu") : new QString("Thursday");
    case 6: return shorty ? new QString("Fri") : new QString("Friday");
    case 7: return shorty ? new QString("Sat") : new QString("Saturday");
  }
  error("day <= 0 or >= 7");
  return &kbNullQString;
}

/*
t_cstring function::fWEEKDAYNAME(t_integer day, t_boolean shorty, t_integer firstdayofweek)
{
  if (firstdayofweek != -1){
    error("Sorry! FirstDayOfWeek not supported yet. Try to change the data calculation.");        
//    if (firstdayofweek == 0) error("Sorry! kbUseSystem not supported yet. Try to change the data calculation.");        
    //day += dayfirstdayofweek - 1;
  }

  switch(day){
    case 1: return shorty ? "Sun" : "Sunday";
    case 2: return shorty ? "Mon" : "Monday";
    case 3: return shorty ? "Tue" : "Tuesday";
    case 4: return shorty ? "Wed" : "Wednesday";
    case 5: return shorty ? "Thu" : "Thursday";
    case 6: return shorty ? "Fri" : "Friday";
    case 7: return shorty ? "Sat" : "Saturday";
  }
  error("day <= 0 or >= 7");
  return "";
}*/

t_date function::fDATESERIAL(t_integer y, t_integer m, t_integer d)
{
  t_date dd(y, m, d);
  return dd;
}

t_date function::fTIMESERIAL(t_integer y, t_integer m, t_integer d)
{
  t_date dd(y, m, d, true);
  return dd;
}

t_integer function::fWEEKDAY(t_date d)
{
  QDateTime t;

  if (d.nYear || d.nMonth || d.nDay){
    t.setDate(QDate(d.nYear, d.nMonth, d.nDay));
  }

  // Qt: the weekday (Monday=1..Sunday=7) for this date.
  int n = t.date().dayOfWeek();

  switch(n){
    case 1: return 2;
    case 2: return 3;
    case 3: return 4;
    case 4: return 5;
    case 5: return 6;
    case 6: return 7;
    case 7: return 1;
  }
  return 0;
}

t_long function::fDAY(t_date d)
{  
	return d.nDay;
}

t_long function::fMONTH(t_date d)
{  
	return d.nMonth;
}

t_long function::fYEAR(t_date d)
{  
	return d.nYear;
}

t_long function::fHOUR(t_date d)
{  
	return d.nHour;
}

t_long function::fMINUTE(t_date d)
{  
	return d.nMinute;
}

t_long function::fSECOND(t_date d)
{  
	return d.nSecond;
}

void function::fPSET(t_boolean step, t_integer x, t_integer y, t_boolean bColor, t_integer color)
{
  myScreen->pset(step, x, y, bColor, color);
}

void function::fSCREEN(t_integer no)
{
 // myScreen->setScreen(no);
}

interpreter_parameter* function::fRGB(t_integer red, t_integer green, t_integer blue)
{
  t_integer n = (red * 256 * 256) + (green * 256) + blue;

	return new interpreter_parameter((t_long) n);
}

interpreter_parameter* function::fCSRLIN()
{
	return new interpreter_parameter((t_long) myScreen->csrlin());
}

interpreter_parameter* function::fPOS(t_integer nExpression)
{
	return new interpreter_parameter((t_long) myScreen->pos());
}

/*
        0 black
        1 red
        2 green
        3 brown
        4 blue
        5 magenta
        6 cyan
        7 white

----------------------------------------------------------------------------------------

Doesn't that depend on the console type? I eman, VT100 Terminals are capable
of a lot more colors for example.
How about letting the user choose from an int value (written in hex it would
be the an RGB triple like in HTML) and translate colors to the one possible
in the current console.
Any unknown foreground color gets translated to white any unknown background
color to black, or you could ignore unknown colors.

That would keep the interface expandable, because you don't have to change
semantics of parameters when you are writting text to a GUI window.

----------------------------------------------------------------------------------------

For the Color function, why were the same codes as VB's QbColor function uses not adopted?
i.e. 0 = black, 1 = blue, 2 = green, 3 = cyan, 4 = red, 5 = magenta, 6 = brown, 7 = white, 8 = grey, 9 = light blue, 11 = light cyan, 12 = light red, 13 = light magenta, 14 = yellow, 15 = bright white.

For the suggested Color2 function,

I have a suggestion for a future color function syntax.  Could be called
COLOR2.  The syntax is:
        COLOR2(RED[0-255],GREEN[0-255],BLUE[0-255],Fore/Back[0/1])

VB's name for the same function is RGB.

The difference is that VB does not allow you specify, with either QBColor or RGB, whether you are talking about the foreground or background color, since this is done according to which property it's being assigned to instead, e.g. Form1.Backcolor=qbcolor(5) versus Form1.Forecolor=qbcolor(5)

----------------------------------------------------------------------------------------

I have a suggestion for a future color function syntax.  Could be called
COLOR2.  The syntax is:
	COLOR2(RED[0-255],GREEN[0-255],BLUE[0-255],Fore/Back[0/1])
              COLOR2(255,255,255,0)  is white foreground
              COLOR2(0,0,0,1)  is black background



*/
void function::fCOLOR(t_boolean bFORE, t_boolean bBACK, t_integer nFORE, t_integer nBACK)
{
  if (bFORE && bBACK){
//    myTerminal->settextcolor(nFORE, nBACK);
    myScreen->color(nFORE, nBACK);
  }	else if (bFORE){
 //   myTerminal->settextfgcolor(nFORE);
    myScreen->color(nFORE, -1);
  }	else if (bBACK){
  //  myTerminal->settextbgcolor(nBACK);
    myScreen->color(-1, nBACK);
  }
}


/*
PRINT
PRINT USING
PRINT#, PRINT# USING

so PRINT and PRINT USING are described as 2 different statements, that makes the thing somewhat easier to understand.

PRINT [expression [{,| |;} [expression]]...]
PRINT USING formatstring; expression [{,| |;} [expression]]...
PRINT #filenumber, [[USING formatstring;] expression [{,| |;} [expression]]...]

Does this help you a little bit?

Actually, in PowerBasic you can switch off parts of the PRINT library in the compiler to save space (if I remember correctly, you can switch off the USING part).

A summary of the manual about PRINT USING:

---------
Formatted strings:

formatstring may contain \\ or ! or &

you can use "\\" to print a certain number of characters (n-2), so

"\\" will print 2
"\  \" will print 4 characters

A "!" will print only the first character of the string

A "&" will print the whole string

----------
Formatted numbers:
you can choose the width of the printing, the number of decimals and the place of the decimal point. Also the place of $, kommas and + or minus

- every # is a decimal digit (max 18)
- additional spaces right of the decimal point will be filled with 0
- additional spaces left of the decimal point will be filled with spaces
- exception: 1 > n > -1 when a 0 is before the decimal point
- all numbers rounded to number of digits
- negative numbers with a leading -
- this leading - takes one # in the formatstring

 0.468  ##.##    0.47   one leading space
 0.468  #.####  0.4680  no leading space
12.5    ##.##   12.50   no leading space
12.5    ####.#    12.5  two leading spaces

Well, this is a bit confusing:

- a plus at the beginning produces a leading + or - before the number
- a minus at the beginning produces always a - (for positive and negative)
- a plus at the end produces a trailing + or -
- a minus at the end produces a space for positive and a - for negative numbers

Now the $ and stuff:
- a $ at the beginning: $ before the number
- for a negative value, the - is between $ and first digit
- several $ reserve additional spaces, but only one $ is printed
- two * fill the spaces with ***
- you can combine ** and $
- a komma left of decimal point marks thousands (1,000,000 - English style)

Exponentials:
- scientific notation by including 3 - 6 "^" signs
- one for "E", one for +/- and two to four for the exponents

Literals:
literals must be preceeded by a "_":

print using "_##"; 1  'prints #1
print using "#_#"; 1  'prints 1#

- if the number doesn't fit, the formatstring is ignored and the whole number with a leading "%" is printed

- variables may be used as formatstrings

- formatstrings may be emedded into normal text (seems like C to me):

a = 12.56
x$= "sum"
print using "The & is $##.##";x$,a

Please be careful, this is PowerBasic not qbasic. There may be differences, but I did not found a better description.


PRINT {[#filehandle ,] [USING string_expression ;] | (expression | SPC(expression) | TAB(expression) [;|,]) }

, = TAB
; = nothing
EOL = \n

NUMBER

# number


. decimal
, print thousand separator
+
^^^^^
-
$$
**
**$

--> sprintf

##. number to large then print as exp
###,.##
###+.
###.+#
$$###
**$####

STRING

&complete string
! first character
\ \     print count spaces between \ + 2

&
!
\\

ESCAPE
_


   Would you be able to provide more detail for the minus at the beginning.
 Does "-##.##" product -12.34 for both positive and negative numbers or does
it produce an output of (12..34) for negative numbers and 12.34 for positive
numbers ?  If not it would be nice to have this format option also.  The $
combined with *** option is great for financial programming.  Including the
() option for negative numbers would add to this power.

*/
void function::fPRINT(t_boolean bFIRST, t_boolean bFILEHANDLE, 
                      t_integer nFILEHANDLE, t_qstring ac, t_boolean bEcho, t_boolean bLog)
{
  if (bFILEHANDLE){

    static /**/ int k;

    if (bFIRST){
      k = nFILEHANDLE;
      nLastFILEHANDLE = nFILEHANDLE;
    } else {
      k = nLastFILEHANDLE;
    }

    if (!(k > 0 && k < MAX_FILEHANDLE)){
      error(utility::con(k, " (file handle) too big or too small"));
      goto exit;
    }

    if (file[k].f.isOpen()){
      switch(file[k].nMode){
   	    case pcode__OUTPUT:
   	    case pcode__APPEND:
		    case pcode__BINARY:
		    case pcode__RANDOM:
         break;
       default:
        error(utility::con(k, " (file) not open in the right mode"));
        goto exit;
        break;
      }

      static /**/ int n;
      QByteArray a = ac->toUtf8();
      n = file[k].f.write(a);//qac, qac->length());			

      if (n == -1){
       error(utility::con(k, " (file) could not write"));
       goto exit;
      }


    } else {
      error(utility::con(k, " (file) not open"));
      goto exit;
    }

  } else {
    if (bLog){
      _log::METHOD_Print(*ac);
    } else {
      myScreen->print(*ac);
    }    
    /*
    if (bEcho && myBrowser){
      myBrowser->echo(ac);
    } else {*/
    //QString s = *ac;
    //  myScreen->print(s);
    //}
  }

exit:
  return;
}


void function::fPRINT(t_boolean bFIRST, t_boolean bFILEHANDLE, 
                      t_integer nFILEHANDLE, t_cstring ac, t_boolean bEcho, t_boolean bLog)
{
  if (bFILEHANDLE){

    static /**/ int k;

    if (bFIRST){
      k = nFILEHANDLE;
      nLastFILEHANDLE = nFILEHANDLE;
    } else {
      k = nLastFILEHANDLE;
    }

    if (!(k > 0 && k < MAX_FILEHANDLE)){
      error(utility::con(k, " (file handle) too big or too small"));
      goto exit;
    }

    if (file[k].f.isOpen()){
      switch(file[k].nMode){
   	    case pcode__OUTPUT:
   	    case pcode__APPEND:
		    case pcode__BINARY:
		    case pcode__RANDOM:
         break;
       default:
        error(utility::con(k, " (file) not open in the right mode"));
        goto exit;
        break;
      }

      static /**/ int n;
      n = file[k].f.write(ac, strlen(ac));			

      if (n == -1){
       error(utility::con(k, " (file) could not write"));
       goto exit;
      }


    } else {
      error(utility::con(k, " (file) not open"));
      goto exit;
    }

  } else {
    if (bLog){
      _log::METHOD_Print(ac);
    } else {
      myScreen->print(ac);
    }
    
      
  }

exit:
  return;
}


void function::fLOCATE(t_boolean bY, t_boolean bX, t_integer nY, t_integer nX)
{
  if (bY && bX) myScreen->locate(nY, nX);
	else if (bY) myScreen->locate(nY, -1);
	else if (bX) myScreen->locate(-1, nX);
}

interpreter_parameter* function::fABS (t_double d)
{
 d = fabs(d);
 return new interpreter_parameter(d);
}

void function::fERROR(t_integer n)
{
	error(runtime_error(n));
}  

// 1=success; 0=no name, -1=dir. doesn't exist,  -2=access denied, -255=other error
t_integer function::fKILL(t_qstring filename)
{
  //t_integer returnvalue = 0;
  if (filename->isEmpty() || filename->isNull())
    return 0;

  QString s2 = *filename;
  if (!s2.contains("/") && !s2.contains("\\")){
    QString s = *filename;
    s2 = curdir;
    s2 += "/";
    s2 += s;
  }

  return QFile::remove(s2) ? 1 : 0;
/*
  switch (errno) {
    case ENOENT:
			error(runtime_error(function__FILENOTFOUND));
			break;
    case EACCES:
			error(runtime_error(function__ACCESSDENIED));
			break;
  }
  */  
}
t_integer function::fKILL(t_cstring filename)
{
  //t_integer returnvalue = 0;
  if ((!filename) || (! *filename))
    return 0;

  QString s2 = filename;
  if (!s2.contains("/") && !s2.contains("\\")){
    QString s = filename;
    s2 = curdir;
    s2 += "/";
    s2 += s;
  }

  return QFile::remove(s2) ? 1 : 0;
/*
  switch (errno) {
    case ENOENT:
			error(runtime_error(function__FILENOTFOUND));
			break;
    case EACCES:
			error(runtime_error(function__ACCESSDENIED));
			break;
  }
  */  
}

/*
{
Search string for any characters other than y, m, d and ".", "/", "-"...
Found something wrong -> ERROR
}

Else:
{
1. Look for yyyy - found? Yes: replace by 2001; No:
   Look for yy - found? Yes: replace by 01

2. Look for mm - found? Yes: replace by 08; No:
   Look for m - found? Yes: replace by 8

3. Look for dd - found? Yes: replace by 03; No:
   Look for d - found? Yes: replace by 3
}

This is a quick and dirty solution. I first thought about writing something
like a simple parser that accepts everything in the string and looks
for yy, yyyy, m, mm, d, dd. But you could run into difficulties
if someone writes "Today is yy-m-d" as "Today" contains a "d" and "y".
Regarding this problem, it is perhaps even better to limit the use of 
characters in the string to usual date-delimiting characters like ".", "/" and "-".
*/
// return current date, format is yyyy-mm-dd with fixed length of 10 chars
interpreter_parameter* function::fDATE ()
{
  static /**/ struct tm *timep;
  static /**/ time_t atime;
	char *result = myTextbuffer->get(11);

  time(&atime); timep=localtime(&atime);
  sprintf (result, "%04i-%02i-%02i",
    timep->tm_year+1900, timep->tm_mon+1, timep->tm_mday);

  return new interpreter_parameter(&QString(result));

}

// return current time, format is hh:mm:ss with fixed length of 8 chars
interpreter_parameter* function::fTIME ()
{
  static /**/ struct tm *timep;
  static /**/ time_t atime;
	char *result = myTextbuffer->get(9);

  time(&atime); timep=localtime(&atime);
  sprintf (result, "%02i:%02i:%02i",
      timep->tm_hour, timep->tm_min, timep->tm_sec);

  return new interpreter_parameter(&QString(result));

}

interpreter_parameter* function::fSTRING2(t_boolean btoAscii, t_boolean bString, t_integer nLen, int ctoAscii, QChar cChar)
{
  if (btoAscii && ctoAscii > 255 || bString && cChar > 255){

    QString sResult;
    if (btoAscii) sResult = sResult.fill(QChar(ctoAscii), nLen);
    else if (bString) sResult = sResult.fill(QChar(cChar), nLen);

    return new interpreter_parameter(&sResult);

  } else {
	  char *acResult = myTextbuffer->get(nLen + 1);

    char cc = cChar.toAscii();
	  if (btoAscii) memset(acResult, ctoAscii, nLen);
	  else if (bString) memset(acResult, cc, nLen);

    acResult[nLen] = '\0';

    return new interpreter_parameter(acResult);

  }
  
}

// converts a string/double to a int
interpreter_parameter* function::fCINT(interpreter_parameter *p)
{
  interpreter_parameter *r = 0;

  switch(p->pcodeType){
    case pcode__BOOLEAN:
      r = new interpreter_parameter(p->toInteger());
      break;
    case pcode__QSTRING:
    case pcode__CSTRING:
      {
        QString s = p->toQString();
        if (s.compare("FALSE", Qt::CaseInsensitive) == 0) r = new interpreter_parameter((t_boolean) false);
        else if (s.compare("TRUE", Qt::CaseInsensitive) == 0) r = new interpreter_parameter((t_boolean) true);
        else if (s.contains(".")) r = new interpreter_parameter ((t_long) (((t_long) ((s.toDouble() + 0.5) * 100)) / 100));
        else r = new interpreter_parameter(s.toLongLong());
        break;
      }
    case pcode__BYTE:
    case pcode__SHORT:
    case pcode__INTEGER:
      r = new interpreter_parameter(p->toInteger());
      break;
    case pcode__LONG:
      r = new interpreter_parameter(p->toLong());
      break;
    case pcode__SINGLE:
      {
        t_single d = p->toSingle();
        bool b = d < 0;
        
        if (b){
          r = new interpreter_parameter ((t_long) (((t_long) ((d - 0.5) * 100)) / 100));
        } else {
          r = new interpreter_parameter ((t_long) (((t_long) ((d + 0.5) * 100)) / 100));
        }
      }
      break;
    case pcode__DOUBLE:
      {
        t_single d = p->toDouble();
        bool b = d < 0;
        
        if (b){
          r = new interpreter_parameter ((t_long) (((t_long) ((d - 0.5) * 100)) / 100));
        } else {
          r = new interpreter_parameter ((t_long) (((t_long) ((d + 0.5) * 100)) / 100));
        }
      }
      break;
    case pcode__CURRENCY:
      {        
        t_currency d = p->toCurrency();
        t_long l2 = d.bc();
        bool b = l2 < 0;
        t_long l = d.ad();
        
        if (b){  // 23.5
          l += 5000;
          if (l >= +10000){
            l2 -= 1;
          }
          d.setValue(l2, 0);
          r = new interpreter_parameter (d.toLong());
        } else {
          l += 5000;
          if (l >= +10000){
            l2 += 1;
          }
          d.setValue(l2, 0);
          r = new interpreter_parameter (d.toLong());
        }   
      }
      break;
    case pcode__DATE:
      r = new interpreter_parameter (p->toLong());
      break;
  }
  delete p;
  return r;

}


interpreter_parameter* function::fCSNG(interpreter_parameter *p)
{
  return fCDBL(p);
}

interpreter_parameter* function::fCDBL(interpreter_parameter *p)
{
  interpreter_parameter *r = 0;

  switch(p->pcodeType){
    case pcode__BOOLEAN:
      r = new interpreter_parameter(p->toDouble());
      break;
    case pcode__QSTRING:
    case pcode__CSTRING:
      {
        QString s = p->toQString();
        if (s.compare("FALSE", Qt::CaseInsensitive) == 0) r = new interpreter_parameter((t_double) false);
        else if (s.compare("TRUE", Qt::CaseInsensitive) == 0) r = new interpreter_parameter((t_double) true);
        else if (s.contains(".")) r = new interpreter_parameter(s.toDouble());
        else r = new interpreter_parameter((t_double) s.toLongLong());
        break;
      }
    case pcode__BYTE:
    case pcode__SHORT:
    case pcode__INTEGER:
      r = new interpreter_parameter(p->toDouble());
      break;
    case pcode__LONG:
      r = new interpreter_parameter(p->toDouble());
      break;
    case pcode__SINGLE:
      r = new interpreter_parameter (p->toDouble());
    case pcode__DOUBLE:
      r = new interpreter_parameter (p->toDouble());
      break;
    case pcode__CURRENCY:
      r = new interpreter_parameter (p->toDouble());
      break;
    case pcode__DATE:
      r = new interpreter_parameter (p->toDouble());
      break;
  }
  delete p;
  return r;

  
}

interpreter_parameter* function::fCCUR(interpreter_parameter *p)
{
  interpreter_parameter *r = 0;

  switch(p->pcodeType){
    case pcode__BOOLEAN:
      r = new interpreter_parameter(t_currency(p->toDouble()));
      break;
    case pcode__QSTRING:
    case pcode__CSTRING:
      {
        QString s = p->toQString();
        if (s.compare("FALSE", Qt::CaseInsensitive) == 0) r = new interpreter_parameter(t_currency((t_double) false));
        else if (s.compare("TRUE", Qt::CaseInsensitive) == 0) r = new interpreter_parameter(t_currency((t_double) true));
        else if (s.contains(".")) r = new interpreter_parameter(t_currency(s.toDouble()));
        else r = new interpreter_parameter(t_currency((t_double) s.toLongLong()));
        break;
      }
    case pcode__BYTE:
    case pcode__SHORT:
    case pcode__INTEGER:
      r = new interpreter_parameter(t_currency(p->toDouble()));
      break;
    case pcode__LONG:
      r = new interpreter_parameter(t_currency(p->toDouble()));
      break;
    case pcode__SINGLE:
      r = new interpreter_parameter (t_currency(p->toDouble()));
    case pcode__DOUBLE:
      r = new interpreter_parameter (t_currency(p->toDouble()));
      break;
    case pcode__CURRENCY:
      r = new interpreter_parameter (p->toCurrency());
      break;
    case pcode__DATE:
      r = new interpreter_parameter (t_currency(p->toDouble()));
      break;
  }
  delete p;
  return r;

  
}


t_boolean function::fLIKE(t_qstring acString, t_qstring acPattern, t_integer nMode)
/*
http://msdn.microsoft.com/library/default.asp?url=/library/en-us/vbenlr98/html/vaoprlike.asp

option binary,option text

? Match any single character.
* Match zero or more characters.
# Match a single digit (0-9).

keine sonderbedeutung von ?,*,#, [ innerhalb []; für ] außerhalb von []
innerhalb von [] suche nach mehreren Zeichen erlaubt, ohne trenner definiert

[A-Za-z0-9],.+-
[*] escape mit []
[]] nicht erlaubt nur ...][...]]...
[] zero length string
[A-Za-z0-9[*]],.+-
[!charlist] Match any char not in the list.
- am ende oder anfang von [] selbst -
#[#][*]*[?]?

*/
{
  QByteArray a = acString->toLocal8Bit();
  QByteArray b = acPattern->toLocal8Bit();

  return fLIKE(a.data(), b.data(), nMode);
}


t_boolean function::fLIKE(t_cstring acString, t_cstring acPattern, t_integer nMode)
/*
http://msdn.microsoft.com/library/default.asp?url=/library/en-us/vbenlr98/html/vaoprlike.asp

option binary,option text

? Match any single character.
* Match zero or more characters.
# Match a single digit (0-9).

keine sonderbedeutung von ?,*,#, [ innerhalb []; für ] außerhalb von []
innerhalb von [] suche nach mehreren Zeichen erlaubt, ohne trenner definiert

[A-Za-z0-9],.+-
[*] escape mit []
[]] nicht erlaubt nur ...][...]]...
[] zero length string
[A-Za-z0-9[*]],.+-
[!charlist] Match any char not in the list.
- am ende oder anfang von [] selbst -
#[#][*]*[?]?

*/
{
  int i = 0;
  int k = 0;
  //bool bBracket = false;
  bool bStar = false;
  bool bExclamation = false;
  char c = 0;
  char p = 0;
  int nBracketCounter = 0;  

  //nMode == 0 binary
  //nMode == 1 text

  
  while (acPattern[i]){
    p = acPattern[i];
    c = acString[k];    
    switch(p){
      case '?':
        if (c){
          k++; 
          if (bStar){
            if (acPattern[i + 1] != 0) i++;
          }
        } else goto f;
        //if (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') k++; else goto f;
        break;
      case '*':
        if (c == 0) goto t; // zero match

        bStar = true;
        
        k++; 
        if (acPattern[i + 1] != 0 
          && acPattern[i + 1] != '?'
          && acPattern[i + 1] != '#'
          && acPattern[i + 1] != '['
          && acPattern[i + 1] != ']'
        ){
           i++;
        }

        break;
      case '#':              
        if (c >= '0' && c <= '9') ; else if (!bStar) goto f;
        k++; 
        if (bStar){
          if (acPattern[i + 1] != 0) i++;
        }
        break;
      case ']':
        if (c == ']'){ bStar = false; } else if (!bStar) goto f;
        k++; 
        if (bStar){
          if (acPattern[i + 1] != 0) i++;
        }  
        break;
      case '[':
        i++;
        bStar = false;
        nBracketCounter = 0;
        while (acPattern[i]){
          p = acPattern[i];
          c = acString[k];    
          //bBracket = true;
          switch(p){
            /*
            case '*':
              if (acPattern[i + 1] != 0 && acPattern[i + 1] == ']'){

              if (c == '*'){ if (bExclamation) goto f; } else if (!bExclamation) goto f;
              k++; 
              break;
            case '?':
              if (c == '?'){ if (bExclamation) goto f; } else if (!bExclamation) goto f;
              k++; 
              break;
            case '#':
              if (c == '#'){ if (bExclamation) goto f; } else if (!bExclamation) goto f;
              k++; 
              break;
              */
            case '-':
              if (nBracketCounter == 0 ||(nBracketCounter == 1 && bExclamation)){ // beginning
                if (c == '-'){ if (bExclamation) goto f; } else if (!bExclamation) goto f;
              } else if (acPattern[i + 1] != 0 && acPattern[i + 1] == ']'){
                if (c == '-'){ if (bExclamation) goto f; } else if (!bExclamation) goto f; // ending
              } else {
                goto f;               
              }
              k++; 
              break;
            case '!':
              if (nBracketCounter == 0){
                bExclamation = true;
              } else {
                if (c == '!'){ if (bExclamation) goto f; } else if (!bExclamation) goto f;
                k++; 
              }
              break;
            case ']':              
              if (acPattern[i + 1] == 0) goto t;
              goto e;              
              break;
            case 0:
              goto t;
              break;
            default:
              // range [A-Za-z0-9]
              if (acPattern[i + 1] != 0 && acPattern[i + 2] != 0 && acPattern[i + 1] == '-'){
                if (p > acPattern[i + 2]) goto f;
                if (p <= c && c <= acPattern[i + 2]){ if (bExclamation) goto f; } else if (!bExclamation) goto f;
                i += 2; 

              // default
              } else if (nMode == 1 && (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')){
                if (c <= 'Z'){
                  if (c == p || c + 26 == p){ if (bExclamation) goto f; } else if (!bExclamation) goto f;
                } else {
                  if (c == p || c - 26 == p){ if (bExclamation) goto f; } else if (!bExclamation) goto f;
                }
              } else if ( (nMode == 0 && c == p) ){ if (bExclamation) goto f; } else if (!bExclamation) goto f;
              k++; 
              break;
          }
          nBracketCounter++;
          i++;
        }
e:
        //bBracket = false;
        bExclamation = false;
        break;
      case 0:
        goto t;
        break;
      default:
        if (nMode == 1 && (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')){
          if (c <= 'Z'){
            if (c == p || c + 26 == p) bStar = false; else if (!bStar) goto f;
          } else {
            if (c == p || c - 26 == p) bStar = false; else if (!bStar) goto f;
          }
        } else if ( (nMode == 0 && c == p) ) bStar = false; else if (!bStar) goto f;
        k++; 
        if (bStar){
          if (acPattern[i + 1] != 0) i++;
        }
        break;
    }
    if (!bStar) i++;
  }
t:
  return k == strlen(acString);
f:
  return false;
}



interpreter_parameter* function::fCBOOL(interpreter_parameter *p)
{
  return fCINT(p);
}

interpreter_parameter* function::fCBYTE(interpreter_parameter *p)
{
  return fCINT(p);
}
interpreter_parameter* function::fCDATE(interpreter_parameter *p)
{
  return new interpreter_parameter (t_date(p->toDate()));
}


/*
> CDBL, CSNG - some string conversion
> CINT, CLNG - yet another string conversion
I looked these up in the QBasic help and they didn't say anything about strings. I'm kind of confused by what these functions do. I made CINT and CLNG (I think), but what would CDBL and CSNG do in C?
*/
interpreter_parameter* function::fCLNG(interpreter_parameter *p)
{
  interpreter_parameter *r = 0;

  switch(p->pcodeType){
    case pcode__BOOLEAN:
      r = new interpreter_parameter(p->toLong());
      break;
    case pcode__QSTRING:
    case pcode__CSTRING:
      {
        QString s = p->toQString();
        if (s.compare("FALSE", Qt::CaseInsensitive) == 0) r = new interpreter_parameter((t_boolean) false);
        else if (s.compare("TRUE", Qt::CaseInsensitive) == 0) r = new interpreter_parameter((t_boolean) true);
        else if (s.contains(".")) r = new interpreter_parameter ((t_long) (((t_long) ((s.toDouble() + 0.5) * 100)) / 100));
        else r = new interpreter_parameter(s.toLongLong());
        break;
      }
    case pcode__BYTE:
    case pcode__SHORT:
    case pcode__INTEGER:
      r = new interpreter_parameter(p->toLong());
      break;
    case pcode__LONG:
      r = new interpreter_parameter(p->toLong());
      break;
    case pcode__SINGLE:
      {
        t_single d = p->toSingle();
        bool b = d < 0;
        
        if (b){
          r = new interpreter_parameter ((t_long) (((t_long) ((d - 0.5) * 100)) / 100));
        } else {
          r = new interpreter_parameter ((t_long) (((t_long) ((d + 0.5) * 100)) / 100));
        }
      }
      break;
    case pcode__DOUBLE:
      {
        t_single d = p->toDouble();
        bool b = d < 0;
        
        if (b){
          r = new interpreter_parameter ((t_long) (((t_long) ((d - 0.5) * 100)) / 100));
        } else {
          r = new interpreter_parameter ((t_long) (((t_long) ((d + 0.5) * 100)) / 100));
        }
      }
      break;
    case pcode__CURRENCY:
      {        
        t_currency d = p->toCurrency();
        t_long l2 = d.bc();
        bool b = l2 < 0;
        t_long l = d.ad();
        
        if (b){  // 23.5
          l += 5000;
          if (l >= +10000){
            l2 -= 1;
          }
          d.setValue(l2, 0);
          r = new interpreter_parameter (d.toLong());
        } else {
          l += 5000;
          if (l >= +10000){
            l2 += 1;
          }
          d.setValue(l2, 0);
          r = new interpreter_parameter (d.toLong());
        }   
      }
      break;
    case pcode__DATE:
      r = new interpreter_parameter (p->toLong());
      break;
  }
  delete p;
  return r;
}

interpreter_parameter *function::fSPACE(t_integer nLen)
{
  QString sResult; sResult.fill(' ', nLen);
  
  return new interpreter_parameter(&sResult);
}



interpreter_parameter * function::fINSTR(t_boolean bBegin, t_integer nBegin, t_qstring s, t_qstring acSearch, t_boolean CaseSensitive)
{

  t_integer n;
  n = s->indexOf(*acSearch, bBegin ? nBegin - 1 : 0, CaseSensitive ? Qt::CaseSensitive : Qt::CaseInsensitive);
  if (n >= 0) return new interpreter_parameter(n + 1);

  return new interpreter_parameter((t_integer) 0);
}

interpreter_parameter * function::fINSTR(t_boolean bBegin, t_integer nBegin, t_cstring acString, t_cstring acSearch, t_boolean CaseSensitive)
{
  QString s;
  s = acString;

  t_integer n;
  n = s.indexOf(acSearch, bBegin ? nBegin - 1 : 0, CaseSensitive ? Qt::CaseSensitive : Qt::CaseInsensitive);
  if (n >= 0) return new interpreter_parameter((t_long) n + 1);

  return new interpreter_parameter((t_integer) 0);
}

interpreter_parameter * function::fINSTREV(t_boolean bBegin, t_integer nBegin, t_qstring s, t_qstring acSearch, t_boolean CaseSensitive)
{
  t_integer n;
  n = 0;
  if (bBegin){
    n = s->lastIndexOf(*acSearch, nBegin - 1, CaseSensitive ? Qt::CaseSensitive : Qt::CaseInsensitive);
  } else {
    n = s->lastIndexOf(*acSearch, -1, CaseSensitive ? Qt::CaseSensitive : Qt::CaseInsensitive);
  }
  if (n >= 0) return new interpreter_parameter((t_long) n + 1);

  return new interpreter_parameter((t_integer) 0);
}

interpreter_parameter * function::fINSTREV(t_boolean bBegin, t_integer nBegin, t_cstring acString, t_cstring acSearch, t_boolean CaseSensitive)
{
  QString s;
  s = acString;

  t_integer n;
  n = 0;
  if (bBegin){
    n = s.lastIndexOf(acSearch, nBegin - 1, CaseSensitive ? Qt::CaseSensitive : Qt::CaseInsensitive);
  } else {
    n = s.lastIndexOf(acSearch, -1, CaseSensitive ? Qt::CaseSensitive : Qt::CaseInsensitive);
  }
  if (n >= 0) return new interpreter_parameter((t_long) n + 1);

  return new interpreter_parameter((t_integer) 0);
}

interpreter_parameter * function::fREPLACE(t_qstring s, t_qstring acPattern, t_qstring acBy, t_boolean CaseSensitive)
{      
  s->replace(*acPattern, *acBy, CaseSensitive ? Qt::CaseSensitive : Qt::CaseInsensitive);

  return new interpreter_parameter(s);
}

interpreter_parameter *function::fREPLACE(t_cstring str, t_cstring acPattern, t_cstring acBy, t_boolean CaseSensitive)
{
  QString s;
  t_cstring ac;

  s = str;

  QByteArray a; a = (s.replace(acPattern, acBy, CaseSensitive ? Qt::CaseSensitive : Qt::CaseInsensitive)).toLocal8Bit();
  ac = a.data();
  
  int n = strlen(ac);
  char *acResult = myTextbuffer->get(n);

  memcpy(acResult, ac, n);

  return new interpreter_parameter(acResult);


}

extern int MAIN_argc;
extern char **MAIN_argv;

interpreter_parameter *function::fCOMMAND()
{   
  QString s;
  s = "";

  for (int i = 0; i < MAIN_argc; i++){
    s += MAIN_argv[i];
    s += " ";
  }

  return new interpreter_parameter(s);


}

bool function::fFILECOPY(t_qstring acFrom, t_qstring acTo)
{
  QString s2 = *acFrom;
  if (!s2.contains("/") && !s2.contains("\\")){
    QString s = s2;
    s2 = curdir;
    s2 += "/";
    s2 += s;
  }
  
  QString s3 = *acTo;
  if (!s3.contains("/") && !s3.contains("\"")){
    QString s = s3;
    s3 = curdir;
    s3 += "/";
    s3 += s;
  }

  QFile file(s2);

  QFile file2(s3);
  file2.remove();

  return file.copy(s3);

}

bool function::fFILECOPY(t_cstring acFrom, t_cstring acTo)
{
  QString s2 = acFrom;
  if (!s2.contains("/") && !s2.contains("\\")){
    QString s = acFrom;
    s2 = curdir;
    s2 += "/";
    s2 += s;
  }
  QString s3 = acTo;
  if (!s3.contains("/") && !s3.contains("\"")){
    QString s = acTo;
    s3 = curdir;
    s3 += "/";
    s3 += s;
  }

  QFile file(s2);

  QFile file2(s3);
  file2.remove();

  return file.copy(s3);

}

interpreter_parameter *function::fFILELEN(t_qstring ac)
{
  QString s2 = *ac;
  if (!s2.contains("/") && !s2.contains("\\")){
    QString s = s2;
    s2 = curdir;
    s2 += "/";
    s2 += s;
  }

  
  QFile file(s2);

  return new interpreter_parameter((t_long) file.size());
}

interpreter_parameter *function::fFILELEN(t_cstring ac)
{
  QString s2 = ac;
  if (!s2.contains("/") && !s2.contains("\\")){
    QString s = ac;
    s2 = curdir;
    s2 += "/";
    s2 += s;
  }

  
  QFile file(s2);

  return new interpreter_parameter((t_long) file.size());
}
interpreter_parameter* function::fEOF(t_integer nFILEHANDLE)
{
  if (!file[nFILEHANDLE].f.isOpen()){
    error(utility::con(nFILEHANDLE, " (file) is not open"));
    return new interpreter_parameter((t_boolean) false);
  }      
  
  return new interpreter_parameter((t_boolean) file[nFILEHANDLE].f.atEnd());
}

/*
Das optionale Argument Bereichsnummer ist ein Wert vom 
Typ Variant, der den Bereich festlegt, aus dem die 
nächste Dateinummer zurückgegeben werden wird. 
Bei 0 (Voreinstellung) wird eine Dateinummer im Bereich 1 bis 255 (einschließlich) 
zurückgegeben. Bei 1 wird eine Dateinummer im Bereich von 256 bis 511 zurückgegeben.
*/
interpreter_parameter* function::fFREEFILE(t_integer nRANGE)
{
  static /**/ int i;
  i = 0;
  if (nRANGE == 0){
    i = 1;
  } else {
    i = 256;
  }

  for (; i < MAX_FILEHANDLE; i++){
    if (!file[i].f.isOpen()){
      return new interpreter_parameter((t_long) i);
    }
  }

  return new interpreter_parameter((t_long) 0);
}

/*
void function::fSETATTR(t_string ac, t_integer nAttr)
{
}*/

interpreter_parameter *function::fFILEATTR(t_integer nFILEHANDLE, t_integer dummy)
{

  if (!(nFILEHANDLE > 0 && nFILEHANDLE < MAX_FILEHANDLE)){
    error(utility::con(nFILEHANDLE, " (file handle) too big or too small"));
    return new interpreter_parameter((t_integer) 0);
  }

  if (!file[nFILEHANDLE].f.isOpen()){
    error(utility::con(nFILEHANDLE, " (file handle) not open"));
    return new interpreter_parameter((t_integer) 0);
  }

  t_integer n = 0;

	switch(file[nFILEHANDLE].nMode){
		case pcode__OUTPUT:
			n = 2;
			break;				
 		case pcode__INPUT:
			n = 1;
			break;
		case pcode__APPEND:
			n = 8; 
			break;
		case pcode__BINARY:
			n = 32;
			break;
		case pcode__RANDOM:
			n = 4;
			break;
   default:
     error("FILEATTR: wrong file mode");
     break;
	}

  return new interpreter_parameter((t_integer) n);
}

interpreter_parameter *function::fGETATTR(t_qstring ac)
{
  QString s2 = *ac;
  if (!s2.contains("/") && !s2.contains("\\")){
    QString s = *ac;
    s2 = curdir;
    s2 += "/";
    s2 += s;
  }

  QFileInfo f(s2);
  
  if (!f.isReadable()){
    QString ss = *ac + " (file) could not be open";
    QByteArray a; a = ss.toLocal8Bit();
    error(a.data());
    return new interpreter_parameter((t_integer) 0);
  }

  t_integer n = 0;

  n += f.isReadable() && !f.isWritable() ? 1 : 0;
  n += f.isHidden() ? 2 : 0;
  //n += f.isHidden() ? 4 : 0; // kbSystem 
  n += f.isDir() ? 16 : 0;
  //n += f.isHidden() ? 32 : 0; // kbArchive 

  return new interpreter_parameter((t_integer) n);
}


interpreter_parameter *function::fGETATTR(t_cstring ac)
{
  QString s2 = ac;
  if (!s2.contains("/") && !s2.contains("\\")){
    QString s = ac;
    s2 = curdir;
    s2 += "/";
    s2 += s;
  }

  QFileInfo f(s2);
  
  if (!f.isReadable()){
    error(utility::con(ac, " (file) could not be open"));
    return new interpreter_parameter((t_integer) 0);
  }

  t_integer n = 0;

  n += f.isReadable() && !f.isWritable() ? 1 : 0;
  n += f.isHidden() ? 2 : 0;
  //n += f.isHidden() ? 4 : 0; // kbSystem 
  n += f.isDir() ? 16 : 0;
  //n += f.isHidden() ? 32 : 0; // kbArchive 

  return new interpreter_parameter((t_integer) n);
}

void function::fOPEN(t_qstring ac, t_integer nMode, t_integer nFILEHANDLE, t_integer nLen)
{
  if (!(nFILEHANDLE > 0 && nFILEHANDLE < MAX_FILEHANDLE)){
    error(utility::con(nFILEHANDLE, " (file handle) too big or too small"));
    return;
  }

  file[nFILEHANDLE].nMode = nMode; 
  file[nFILEHANDLE].nRecordPos = 1;

  QIODevice::OpenMode n;
  n = 0;
	switch(nMode){
		case pcode__OUTPUT:
			n = QFile::WriteOnly;
     file[nFILEHANDLE].nRecordLen = 512;
			break;				
 		case pcode__INPUT:
			n = QFile::ReadOnly;
     file[nFILEHANDLE].nRecordLen = 512;
			break;
		case pcode__APPEND:
			n = QFile::Append | QFile::WriteOnly; 
     file[nFILEHANDLE].nRecordLen = 512;
			break;
		case pcode__BINARY:
			n = QFile::ReadWrite;
     file[nFILEHANDLE].nRecordLen = 128;
			break;
		case pcode__RANDOM:
			n = QFile::ReadWrite;
     file[nFILEHANDLE].nRecordLen = 128;
			break;
   default:
     error("OPEN: wrong file mode");
     return;
     break;
	}

  if (nLen) file[nFILEHANDLE].nRecordLen = nLen;

  QString s2 = *ac;
  if (!s2.contains("/") && !s2.contains("\\")){
    QString s = *ac;
    s2 = curdir;
    s2 += "/";
    s2 += s;
  }


  file[nFILEHANDLE].f.setFileName(s2);
  static /**/ bool b;
  b = file[nFILEHANDLE].f.open(n);

  QFile::FileError er = file[nFILEHANDLE].f.error();

  if (!b){
    QString ss = *ac + " (file) could not be open";
    QByteArray a; a = ss.toLocal8Bit();
    error(a.data());
    return;
  }

  

}


void function::fOPEN(t_cstring ac, t_integer nMode, t_integer nFILEHANDLE, t_integer nLen)
{
  if (!(nFILEHANDLE > 0 && nFILEHANDLE < MAX_FILEHANDLE)){
    error(utility::con(nFILEHANDLE, " (file handle) too big or too small"));
    return;
  }

  file[nFILEHANDLE].nMode = nMode; 
  file[nFILEHANDLE].nRecordPos = 1;

  QIODevice::OpenMode n;
  n = 0;
	switch(nMode){
		case pcode__OUTPUT:
			n = QFile::WriteOnly;
     file[nFILEHANDLE].nRecordLen = 512;
			break;				
 		case pcode__INPUT:
			n = QFile::ReadOnly;
     file[nFILEHANDLE].nRecordLen = 512;
			break;
		case pcode__APPEND:
			n = QFile::Append | QFile::WriteOnly; 
     file[nFILEHANDLE].nRecordLen = 512;
			break;
		case pcode__BINARY:
			n = /*QFile::Raw | */QFile::ReadWrite;
     file[nFILEHANDLE].nRecordLen = 512;
			break;
		case pcode__RANDOM:
			n = /*QFile::Raw | */QFile::ReadWrite;
     file[nFILEHANDLE].nRecordLen = 128;
			break;
   default:
     error("OPEN: wrong file mode");
     return;
     break;
	}

  if (nLen) file[nFILEHANDLE].nRecordLen = nLen;

  QString s2 = ac;
  if (!s2.contains("/") && !s2.contains("\\")){
    QString s = ac;
    s2 = curdir;
    s2 += "/";
    s2 += s;
  }


  file[nFILEHANDLE].f.setFileName(s2);
  static /**/ bool b;
  b = file[nFILEHANDLE].f.open(n);

  QFile::FileError er = file[nFILEHANDLE].f.error();

  if (!b){
    error(utility::con(ac, " (file) could not be open"));
    return;
  }

  if (nMode == pcode__APPEND){
    static /**/ int u;
    u = file[nFILEHANDLE].f.size();

    file[nFILEHANDLE].f.seek( u ); 
  }
  

}

interpreter_parameter* function::fLOF(t_integer nFILEHANDLE)
{
  if (!(nFILEHANDLE > 0 && nFILEHANDLE < MAX_FILEHANDLE)){
    error(utility::con(nFILEHANDLE, " (file handle) too big or too small"));
    goto exit;
  }

  if (file[nFILEHANDLE].f.isOpen()){
     return new interpreter_parameter((t_long) file[nFILEHANDLE].f.size());    
	} 
exit:        
	return new interpreter_parameter((t_long) -1);
}

t_integer function::getRecordSizeFile(t_integer nFILEHANDLE)
{
  if (!(nFILEHANDLE > 0 && nFILEHANDLE < MAX_FILEHANDLE)){
    error(utility::con(nFILEHANDLE, " (file handle) too big or too small"));
    goto exit;
  }

  if (file[nFILEHANDLE].f.isOpen()){
    return file[nFILEHANDLE].nRecordLen;   
	} 
exit:        
	return 0;
}

interpreter_parameter* function::fLOC(t_integer nFILEHANDLE)
{
  if (!(nFILEHANDLE > 0 && nFILEHANDLE < MAX_FILEHANDLE)){
    error(utility::con(nFILEHANDLE, " (file handle) too big or too small"));
    goto exit;
  }

  if (file[nFILEHANDLE].f.isOpen()){
    return new interpreter_parameter((t_long) file[nFILEHANDLE].f.pos());    
	} 
exit:        
	return new interpreter_parameter((t_long) 0);
}

void function::closeAllFiles()
{
	for (t_integer i = 1; i < MAX_FILEHANDLE; i++){
 		if (file[i].f.isOpen()) file[i].f.close();		
	}
}

bool function::setRecordPos(t_integer nFILEHANDLE, t_integer nRecordPos, int nRecordLenOverwrite)
{
  static /**/ int n;

  switch(file[nFILEHANDLE].nMode){
	  case pcode__BINARY:
      n = (nRecordPos - 1);
      break;
 	  case pcode__INPUT:
	  case pcode__RANDOM:
      n = (nRecordPos - 1) * file[nFILEHANDLE].nRecordLen;
      break;
    default:
      break;
  }


  static /**/ bool b;
  if (nRecordLenOverwrite == 0) b = file[nFILEHANDLE].f.seek(n); else b = true;

  if (!b){
    error(utility::con(nFILEHANDLE, " (file) could not be seeked (record positioning)"));
    goto exit;
  }

  file[nFILEHANDLE].nRecordPos = nRecordPos;

  return true;

exit:
  return false;
}

char *function::fGET(t_integer nFILEHANDLE, t_integer nRecord, t_boolean bRecordLen, int *nRecordLenOverwrite)
{
  int nId = 0;
  char *ac = 0;

  if (!(nFILEHANDLE > 0 && nFILEHANDLE < MAX_FILEHANDLE)){
    error(utility::con(nFILEHANDLE, " (file handle) too big or too small"));
    goto exit;
  }


  if (file[nFILEHANDLE].f.isOpen()){
    switch(file[nFILEHANDLE].nMode){
   	  case pcode__INPUT:
		  case pcode__BINARY:
		  case pcode__RANDOM:
        break;
      default:
       error(utility::con(nFILEHANDLE, " (file) not open in the right mode"));
       goto exit;
       break;
    }

    if (bRecordLen){
      if (!setRecordPos(nFILEHANDLE, nRecord)) goto exit;
    } else {
      if (!setRecordPos(nFILEHANDLE, file[nFILEHANDLE].nRecordPos/* + 1*/)) goto exit;
    }
    static /**/ int n;

    switch(file[nFILEHANDLE].nMode){
		  case pcode__BINARY:
        {
          t_long l = file[nFILEHANDLE].f.size() - file[nFILEHANDLE].f.pos();
        //  l *= 2;
          ac = (char *) malloc(l);
          n = file[nFILEHANDLE].f.read((char *) ac, l);			
          file[nFILEHANDLE].nRecordLen = n;
          if (nRecordLenOverwrite) *nRecordLenOverwrite = n;
        }
        break;
   	  case pcode__INPUT:
		  case pcode__RANDOM:
        ac = (char *) malloc(file[nFILEHANDLE].nRecordLen);
        n = file[nFILEHANDLE].f.read((char *) ac, file[nFILEHANDLE].nRecordLen);			
        if (nRecordLenOverwrite) *nRecordLenOverwrite = n;
        break;
      default:
       error(utility::con(nFILEHANDLE, " (file) not open in the right mode"));
       goto exit;
       break;
    }


    if (n == -1){
      error(utility::con(nFILEHANDLE, " (file) could not be read"));
      goto exit;
    }

  } else {
    error(utility::con(nFILEHANDLE, " (file) not open"));
    goto exit;
  }

  return ac;

exit:
  return 0;
	

}

void function::fPUT(t_integer nFILEHANDLE, t_integer nRecord, t_boolean bRecordLen, const char *ac, int nRecordLenOverwrite)
{
  if (!(nFILEHANDLE > 0 && nFILEHANDLE < MAX_FILEHANDLE)){
    error(utility::con(nFILEHANDLE, " (file handle) too big or too small"));
    goto exit;
  }

  if (file[nFILEHANDLE].f.isOpen()){
    switch(file[nFILEHANDLE].nMode){
   	  case pcode__OUTPUT:
		  case pcode__BINARY:
		  case pcode__RANDOM:
        break;
      default:
       error(utility::con(nFILEHANDLE, " (file) not open in the right mode"));
       goto exit;
       break;
    }

    if (bRecordLen){
      if (!setRecordPos(nFILEHANDLE, nRecord)) goto exit;
    } else {
      if (!setRecordPos(nFILEHANDLE, file[nFILEHANDLE].nRecordPos/* + 1*/, nRecordLenOverwrite)) goto exit;
    }

    int n = file[nFILEHANDLE].f.write(ac, nRecordLenOverwrite ? nRecordLenOverwrite : file[nFILEHANDLE].nRecordLen);			

    if (n == -1){
      error(utility::con(nFILEHANDLE, " (file) could not write"));
      goto exit;
    }

  } else {
    error(utility::con(nFILEHANDLE, " (file) not open"));
    goto exit;
  }

 	return;

exit:
	return;

}


void function::fPOKE(const char *ac, t_integer nStringLen, const char *p, int nPSize)
{
  t_integer n = nPSize;
  if (n > nStringLen) n = nStringLen;
  memcpy((void *) p, (void *) ac, n);
}

interpreter_parameter* function::fLINEINPUT(t_integer nFILEHANDLE)
{
  int nId;

  if (!(nFILEHANDLE > 0 && nFILEHANDLE < MAX_FILEHANDLE)){
    error(utility::con(nFILEHANDLE, " (file handle) too big or too small"));
    return new interpreter_parameter("");
  }

   static char ac[0xffff];

  if (file[nFILEHANDLE].f.isOpen()){
    switch(file[nFILEHANDLE].nMode){
   	  case pcode__INPUT:
		  case pcode__BINARY:
		  case pcode__RANDOM:
        break;
      default:
       error(utility::con(nFILEHANDLE, " (file) not open in the right mode"));
       return new interpreter_parameter("");
       break;
    }

    static /**/ int n;
    n = file[nFILEHANDLE].f.readLine((char *) &ac, 0xffff);			

    if (n == -1){
      error(utility::con(nFILEHANDLE, " (file) could not be read"));
      return new interpreter_parameter("");
    }

    // get rid of the readed return character
    if (n > 0){
      if (ac[n - 2] == 0xd) ac[n - 2] = 0; // LINUX anderes return zeichen nur 1byte groß
      else ac[n - 1] = 0;
    }

  } else {
    error(utility::con(nFILEHANDLE, " (file) not open"));
    return new interpreter_parameter("");
  }

  int n = strlen(ac);
  char *acResult = myTextbuffer->get(n);
  memcpy(acResult, ac, n);
  return new interpreter_parameter(acResult);

}	

interpreter_parameter* function::fINPUT2(t_integer nFILEHANDLE)
{
  int nId;
  int k = 0;
  int k2 = 0;
   
  if (!(nFILEHANDLE > 0 && nFILEHANDLE < MAX_FILEHANDLE)){
    error(utility::con(nFILEHANDLE, " (file handle) too big or too small"));
    return new interpreter_parameter("");
  }

   static char ac[0xffff]; //  inputbuffer global für alle file read funktionen

  if (file[nFILEHANDLE].f.isOpen()){
    switch(file[nFILEHANDLE].nMode){
   	  case pcode__INPUT:
		  case pcode__BINARY:
		  case pcode__RANDOM:
        break;
      default:
       error(utility::con(nFILEHANDLE, " (file) not open in the right mode"));
       return new interpreter_parameter("");
       break;
    }

    static /**/ int nPos;
    nPos = file[nFILEHANDLE].f.pos();

    static /**/ int n;
    n = file[nFILEHANDLE].f.readLine((char *) &ac, 0xffff);			

    if (n == -1){
      error(utility::con(nFILEHANDLE, " (file) could not be read"));
      return new interpreter_parameter("");
    }

    static /**/ QString s;
    s = ac;
    static /**/ int x;
    x = s.indexOf(',');
    if (x >= 0) n = x + 1;

    // get rid of the readed return character
    if (n > 0){
      if (ac[n - 2] == 0xd) ac[n - 2] = 0; // LINUX  anderes return zeichen nur 1byte groß
      else ac[n - 1] = 0;
    }

    if (ac[0] == -17 && ac[1] == -69 && ac[2] == -65){
      k += 3;
    }

    if (ac[k] == '\"') k += 1;
    if (ac[n - 2] == '\"'){ ac[n - 2] = 0; k2 = 1; }


    static /**/ int m;
    if (x >= 0){
      m = nPos + strlen(ac) + k2 + (x >= 0 ? 1 : 1); // + 1 fürs komma
    } else {
      m = nPos + n;
    }

    file[nFILEHANDLE].f.seek(m); 

  } else {
    error(utility::con(nFILEHANDLE, " (file) not open"));
    return new interpreter_parameter("");
  }

  int n = strlen((ac + k));
  char *acResult = myTextbuffer->get(n);
  memcpy(acResult, (ac + k), n);
  return new interpreter_parameter(acResult);

}	

interpreter_parameter* function::fSEEK2(t_integer nFILEHANDLE)
{
  if (!(nFILEHANDLE > 0 && nFILEHANDLE < MAX_FILEHANDLE)){
    error(utility::con(nFILEHANDLE, " (file handle) too big or too small"));
    goto exit;
  }

  if (file[nFILEHANDLE].f.isOpen()){

    return new interpreter_parameter((t_long) file[nFILEHANDLE].f.pos());

  } else {
    error(utility::con(nFILEHANDLE, " (file) not open"));
    goto exit;
  } 	

exit:
	return new interpreter_parameter((t_long) 0);

}	

void function::fSEEK(t_integer nFILEHANDLE, t_integer nPos)
{
  if (!(nFILEHANDLE > 0 && nFILEHANDLE < MAX_FILEHANDLE)){
    error(utility::con(nFILEHANDLE, " (file handle) too big or too small"));
    goto exit;
  }

  if (file[nFILEHANDLE].f.isOpen()){

    static /**/ bool b;
    b = file[nFILEHANDLE].f.seek(nPos);

    if (!b){
      error(utility::con(nFILEHANDLE, " (file) could not be seeked"));
      goto exit;
    }

  } else {
    error(utility::con(nFILEHANDLE, " (file) not open"));
    goto exit;
  } 	

exit:
  return;
}	

void function::fCLOSE(t_integer nFILEHANDLE)
{
  if (!(nFILEHANDLE > 0 && nFILEHANDLE < MAX_FILEHANDLE)){
    error(utility::con(nFILEHANDLE, " (file handle) too big or too small"));
    return;
  }

  if (file[nFILEHANDLE].f.isOpen()){
    file[nFILEHANDLE].f.close();		
  }
	
}	

void function::fCLOSEALL()
{
	closeAllFiles();
}

// comma is whether to stop at comma or not (like INPUT vs. LINE INPUT)

//  -1 = not open; -2 = open for input; -255 fputs error (internal error)

// 1=success; 0= > 40; -1 = not open; -255 = fclose error (internal error)


// close 'em all
void function::fRESET()
{
  closeAllFiles();
}


interpreter_parameter *function::fDIR(t_qstring path, t_integer nAttr, t_boolean bFilesAll)
{

  QFileInfo *fi;
  static int nn = 0;

  QString k = *path;
  QString a = *path;
  QString b = *path;
  static QFileInfoList files;

  if (path->isEmpty() || path->isNull()){
    nn++;


    k = curdir;
    a = curdir;
    b = curdir;
    dir = new QDir(a);    
    files = dir->entryInfoList();

    goto z;

  } else {
     
    nn = 0;

    if (k.contains("*") || k.contains("?")){      
      int i = k.lastIndexOf('\\');
      if (i == -1){
        i = k.lastIndexOf('/');
      }
      b = k.right(k.length() - i - 1);
      a = k.left(i);
    } else {
      b = "";
    }
    dir = new QDir(a);   
    files = dir->entryInfoList();
z:

    if (files.size()){
      QFileInfo fi;

      if (nn < files.size()){
        fi = files.at(nn);

        static QString s; s = fi.absoluteFilePath ();

        curdir = fi.absolutePath();

        
        if (fi.isDir() && (nAttr == 0 || nAttr && 16)){

          return new interpreter_parameter(s);

        } else if (fi.isHidden() && (nAttr == 0 || nAttr && 2)){

          return new interpreter_parameter(s);

        } else if (nAttr == 0){

          return new interpreter_parameter(s);
        }

      }

    } else {
      error(runtime_error(function__PATHNOTFOUND));
    }
  }

  return new interpreter_parameter("");
}

interpreter_parameter *function::fDIR(t_cstring path, t_integer nAttr, t_boolean bFilesAll)
{
  static t_cstring ac = "";
  QFileInfo *fi;
  static int nn = 0;


  QString k = path;
  QString a = path;
  QString b = path;
  static QFileInfoList files;

  if (path[0] == 0){
    nn++;


    k = curdir;
    a = curdir;
    b = curdir;
    dir = new QDir(a);    
    files = dir->entryInfoList();


    goto z;

  } else {
     
    nn = 0;

    if (k.contains("*") || k.contains("?")){      
      int i = k.lastIndexOf('\\');
      if (i == -1){
        i = k.lastIndexOf('/');
      }
      b = k.right(k.length() - i - 1);
      a = k.left(i);
    } else {
      b = "";
    }
    dir = new QDir(a);   
    files = dir->entryInfoList();
z:

    if (files.size()){
      QFileInfo fi;

      if (nn < files.size()){
        fi = files.at(nn);

        static QString s; s = fi.absoluteFilePath ();

        curdir = fi.absolutePath();

        static QByteArray a; a = s.toLocal8Bit();
        ac = a.data();

        if (fi.isDir() && (nAttr == 0 || nAttr && 16)){

          int n = strlen(ac);
          char *acResult = myTextbuffer->get(n);
          memcpy(acResult, ac, n);
          return new interpreter_parameter(acResult);

        } else if (fi.isHidden() && (nAttr == 0 || nAttr && 2)){

          int n = strlen(ac);
          char *acResult = myTextbuffer->get(n);
          memcpy(acResult, ac, n);
          return new interpreter_parameter(acResult);

        } else if (nAttr == 0){


          int n = strlen(ac);
          char *acResult = myTextbuffer->get(n);
          memcpy(acResult, ac, n);
          return new interpreter_parameter(acResult);
        }

      }

    } else {
      error(runtime_error(function__PATHNOTFOUND));
    }
  }

  return new interpreter_parameter("");
}

interpreter_parameter *function::fCURDIR(t_qstring drive)
{
  QByteArray a; a = drive->toLocal8Bit();
  return fCURDIR(a.data());
}

interpreter_parameter *function::fCURDIR(t_cstring drive)
{
  if (!strlen(drive)){
    return new interpreter_parameter(curdir);
  }
  
  if (drive[0] - 65 < 0 || drive[0] - 65 > 26){
    error(runtime_error(function__PATHNOTFOUND));
    return new interpreter_parameter("");
  }


  return new interpreter_parameter(&curdir2[drive[0] - 65 < 0 || drive[0] - 65 > 25 ? 26 : drive[0] - 65]);

}

void function::fCHDRIVE(t_qstring drive)
{
  QByteArray a; a = drive->toLocal8Bit();
  fCHDRIVE(a.data());
}

void function::fCHDRIVE(t_cstring drive)
{
  if (!strlen(drive)) return;
  
  switch(drive[0]){
    case 'A': curdrive = drive[0]; if (curdir == "") curdir = "A:\\"; break;
    case 'B': curdrive = drive[0]; if (curdir == "") curdir = "B:\\"; break;
    case 'C': curdrive = drive[0]; if (curdir == "") curdir = "C:\\"; break;
    case 'D': curdrive = drive[0]; if (curdir == "") curdir = "D:\\"; break;
    case 'E': curdrive = drive[0]; if (curdir == "") curdir = "E:\\"; break;
    case 'F': curdrive = drive[0]; if (curdir == "") curdir = "F:\\"; break;
    case 'G': curdrive = drive[0]; if (curdir == "") curdir = "G:\\"; break;
    case 'H': curdrive = drive[0]; if (curdir == "") curdir = "H:\\"; break;
    case 'I': curdrive = drive[0]; if (curdir == "") curdir = "I:\\"; break;
    case 'J': curdrive = drive[0]; if (curdir == "") curdir = "J:\\"; break;
    case 'K': curdrive = drive[0]; if (curdir == "") curdir = "K:\\"; break;
    case 'L': curdrive = drive[0]; if (curdir == "") curdir = "L:\\"; break;
    case 'M': curdrive = drive[0]; if (curdir == "") curdir = "M:\\"; break;
    case 'N': curdrive = drive[0]; if (curdir == "") curdir = "N:\\"; break;
    case 'O': curdrive = drive[0]; if (curdir == "") curdir = "O:\\"; break;
    case 'P': curdrive = drive[0]; if (curdir == "") curdir = "P:\\"; break;
    case 'Q': curdrive = drive[0]; if (curdir == "") curdir = "Q:\\"; break;
    case 'R': curdrive = drive[0]; if (curdir == "") curdir = "R:\\"; break;
    case 'S': curdrive = drive[0]; if (curdir == "") curdir = "S:\\"; break;
    case 'T': curdrive = drive[0]; if (curdir == "") curdir = "T:\\"; break;
    case 'U': curdrive = drive[0]; if (curdir == "") curdir = "U:\\"; break;
    case 'V': curdrive = drive[0]; if (curdir == "") curdir = "V:\\"; break;
    case 'W': curdrive = drive[0]; if (curdir == "") curdir = "W:\\"; break;
    case 'X': curdrive = drive[0]; if (curdir == "") curdir = "X:\\"; break;
    case 'Y': curdrive = drive[0]; if (curdir == "") curdir = "Y:\\"; break;
    case 'Z': curdrive = drive[0]; if (curdir == "") curdir = "Z:\\"; break;
    default:
      error(runtime_error(function__PATHNOTFOUND));
      break;
  }
}

void function::fPRINTSCREEN(t_boolean b)
{
  myScreen->printScreen(b);
}

void function::fCHDIR(t_qstring dir)
{
  QByteArray a; a = dir->toLocal8Bit();
  fCHDRIVE(a.data());
}

void function::fCHDIR(t_cstring dir)
{
  if (dir[0] == '/'){ // LINUX // MACOS

    curdir = dir;

  } else {

    if (dir[0] - 65 < 0 || dir[0] - 65 > 26){
      error(runtime_error(function__PATHNOTFOUND));
      return;
    }

    curdrive = dir[0]; 
    curdir = dir;  
    curdir2[dir[0] - 65 < 0 || dir[0] - 65 > 25 ? 26 : dir[0] - 65];
  }
}

interpreter_parameter *function::fRMDIR(t_qstring directory)
{
	QDir d; 
  QString s2 = *directory;
  if (!s2.contains("/") && !s2.contains("\\")){
    QString s = *directory;
    s2 = curdir;
    s2 += "/";
    s2 += s;
  }
  d.rmdir(s2);
  return 0;
}

interpreter_parameter *function::fRMDIR(t_cstring directory)
{
	QDir d; 
  QString s2 = directory;
  if (!s2.contains("/") && !s2.contains("\\")){
    QString s = directory;
    s2 = curdir;
    s2 += "/";
    s2 += s;
  }
  d.rmdir(s2);
  return 0;

}

interpreter_parameter *function::fMKDIR(t_qstring directory)
{
  if (directory->isEmpty() || directory->isNull())
    return 0;

  QString s2 = *directory;
  if (!s2.contains("/") && !s2.contains("\\")){
    QString s = *directory;
    s2 = curdir;
    s2 += "/";
    s2 += s;
  }

	QDir d;
  d.mkdir(s2);
	
}

interpreter_parameter *function::fMKDIR(t_cstring directory)
{
  if ((!directory) || (!*directory))
    return 0;

  QString s2 = directory;
  if (!s2.contains("/") && !s2.contains("\\")){
    QString s = directory;
    s2 = curdir;
    s2 += "/";
    s2 += s;
  }

	QDir d;
  d.mkdir(s2);
	
}

t_integer function::fNAME(t_qstring file, t_qstring as)
{
  if (file->isEmpty() || file->isNull() || as->isEmpty() || as->isNull())
    return 0;

  QString s2 = (QString) *file;
  if (!s2.contains("/") && !s2.contains("\\")){
    QString s = (QString) *file;
    s2 = curdir;
    s2 += "/";
    s2 += s;
  }

  QString s3 = (QString) *as;
  if (!s3.contains("/") && !s2.contains("\\")){
    QString s = (QString) *as;
    s3 = curdir;
    s3 += "/";
    s3 += s;
  }

  static QByteArray a; a = s2.toLocal8Bit();
  static QByteArray b; b = s3.toLocal8Bit();

  errno = 0;
  if (rename(a.data(), b.data()) == 0)
    return 1;

  switch (errno){
    case ENOENT:
			error(runtime_error(function__FILENOTFOUND));
			break;
    case EACCES:
			error(runtime_error(function__ACCESSDENIED));
			break;
  }

  return -255;
}

t_integer function::fNAME(t_cstring file, t_cstring as)
{
  if (!file || !strlen(file))
    return 0;

  QString s2 = (const char *) *file;
  if (!s2.contains("/") && !s2.contains("\\")){
    QString s = (const char *) *file;
    s2 = curdir;
    s2 += "/";
    s2 += s;
  }

  QString s3 = (const char *) *as;
  if (!s3.contains("/") && !s2.contains("\\")){
    QString s = (const char *) *as;
    s3 = curdir;
    s3 += "/";
    s3 += s;
  }

  static QByteArray a; a = s2.toLocal8Bit();
  static QByteArray b; b = s3.toLocal8Bit();

  errno = 0;
  if (rename(a.data(), b.data()) == 0)
    return 1;

  switch (errno){
    case ENOENT:
			error(runtime_error(function__FILENOTFOUND));
			break;
    case EACCES:
			error(runtime_error(function__ACCESSDENIED));
			break;
  }

  return -255;
}


void function::fFILES(t_boolean bDirectory, t_qstring acDirectory)
{  
  QFileInfo *fi;

  QString k = *acDirectory;
  QString a = *acDirectory;
  QString b = *acDirectory;

  if (bDirectory == false){


    k = curdir;
    a = curdir;
    b = curdir;

    goto z;

  } else {

    if (k.contains("*") || k.contains("?")){      
      int i = k.lastIndexOf('\\');
      if (i == -1){
        i = k.lastIndexOf('/');
      }
      b = k.right(k.length() - i - 1);
      a = k.left(i);
    } else {
      b = "";
    }
z:
    dir = new QDir(a);    
    //dir->setNameFilters(QStringList(b));
    QFileInfoList files = dir->entryInfoList();

    if (files.size()){
    QFileInfo fi;
QString s;
    for (int i = 0; i < files.size(); ++i) {
     fi = files.at(i);

        s = fi.absoluteFilePath ();

        myScreen->print((const QString &) s);
        myScreen->print("\n");
      }

    } else {
      error(runtime_error(function__PATHNOTFOUND));
    }
   //  QMessageBox::information(0,"", "1111111"); 
  }


}



void function::fFILES(t_boolean bDirectory, t_cstring acDirectory)
{
  t_cstring ac = "";
  QFileInfo *fi;

  QString k = acDirectory;
  QString a = acDirectory;
  QString b = acDirectory;

  if (bDirectory == false){


    k = curdir;
    a = curdir;
    b = curdir;

    goto z;

  } else {

    if (k.contains("*") || k.contains("?")){      
      int i = k.lastIndexOf('\\');
      if (i == -1){
        i = k.lastIndexOf('/');
      }
      b = k.right(k.length() - i - 1);
      a = k.left(i);
    } else {
      b = "";
    }
z:
    dir = new QDir(a);    
    //dir->setNameFilters(QStringList(b));
    QFileInfoList files = dir->entryInfoList();

    if (files.size()){
    QFileInfo fi;
QString s;
    for (int i = 0; i < files.size(); ++i) {
     fi = files.at(i);

         s = fi.absoluteFilePath ();

        QByteArray a = s.toLocal8Bit();
        ac = a.data();
        myScreen->print(ac);
        myScreen->print("\n");

      }

    } else {
      error(runtime_error(function__PATHNOTFOUND));
    }
   //  QMessageBox::information(0,"", "1111111"); 
  }

}


/*
  Combined screen output and keyboard input into variable
*/
interpreter_parameter *function::fINPUT(t_qstring acSTRING_EXPRESSION, t_boolean bQuestionMark, t_boolean bNewLine, t_integer nInputType)
{
  QByteArray a; if (acSTRING_EXPRESSION) a = acSTRING_EXPRESSION->toLocal8Bit();
  return fINPUT(a.data(), bQuestionMark, bNewLine, nInputType);
}

interpreter_parameter *function::fINPUT(t_cstring acSTRING_EXPRESSION, t_boolean bQuestionMark, t_boolean bNewLine, t_integer nInputType)
{
	if (acSTRING_EXPRESSION && strlen(acSTRING_EXPRESSION)) myScreen->print(acSTRING_EXPRESSION); // string expression
  if (bQuestionMark) myScreen->print("? ");  // question mark
repeat:
  char *acBuffer = myScreen->input();

	static /**/ t_integer n; // = 0;
	static /**/ t_long l; // = 0;
	static /**/ t_single f; // = 0;
	static /**/ t_double d; // = 0;
	static /**/ t_boolean c; // = 0;
	static /**/ t_cstring ac; // = 0;

	// think carefully, if you want to change the order of the following function calls!
	if (isSingle	(acBuffer, &f)){
    switch (nInputType){
      case pcode__INTEGER: n = (t_integer) floor(f); break;
      case pcode__LONG: l = (t_long) floor(f); break;
  		case pcode__SINGLE: f = f; break;
  		case pcode__DOUBLE: d = f; break;
  		case pcode__BOOLEAN: c = (char) f; break;
      case pcode__QSTRING: ac = acBuffer; break;
  		case pcode__CSTRING: ac = acBuffer; break;
    }
	} else if (isDouble	(acBuffer, &d)){
    switch (nInputType){
      case pcode__INTEGER: n = (t_integer) floor(d); break;
      case pcode__LONG: l = (t_long) floor(d); break;
  		case pcode__SINGLE: f = d; break;
  		case pcode__DOUBLE: d = d; break;
  		case pcode__BOOLEAN: c = (char) d; break;
      case pcode__QSTRING: ac = acBuffer; break;
  		case pcode__CSTRING: ac = acBuffer; break;
    }
	} else if (isBoolean	(acBuffer, &c)){
    switch (nInputType){
      case pcode__INTEGER: n = c; break;
      case pcode__LONG: l = c; break;
  		case pcode__SINGLE: f = c; break;
  		case pcode__DOUBLE: d = c; break;
  		case pcode__BOOLEAN: c = c; break;
      case pcode__QSTRING: ac = acBuffer; break;
  		case pcode__CSTRING: ac = acBuffer; break;
    }
	}	else {

  	if ((isHex			 (acBuffer, &l))
    	|| (isOctal	 (acBuffer, &l))
    	|| (isBinary  (acBuffer, &l))
    	|| (isLong		 (acBuffer, &l)))
		{

      switch (nInputType){
        case pcode__INTEGER: n = l; break;
        case pcode__LONG: l = l; break;
    		case pcode__SINGLE: f = (t_single) l; break;
    		case pcode__DOUBLE: d = (t_double) l; break;
    		case pcode__BOOLEAN: c = l; break;
        case pcode__QSTRING: ac = acBuffer; break;
  		  case pcode__CSTRING: ac = acBuffer; break;
      }

  	} else if (isInteger			 (acBuffer, &n)){

      switch (nInputType){
        case pcode__INTEGER: n = n; break;
        case pcode__LONG: l = n; break;
    		case pcode__SINGLE: f = (t_single) n; break;
    		case pcode__DOUBLE: d = (t_double) n; break;
    		case pcode__BOOLEAN: c = n; break;
        case pcode__QSTRING: ac = acBuffer; break;
  		  case pcode__CSTRING: ac = acBuffer; break;
      }

  	} else { // STRING
			if (acBuffer[0] != 0){

        switch (nInputType){
          case pcode__INTEGER:
          case pcode__LONG:
      		case pcode__SINGLE:
      		case pcode__DOUBLE:
      		case pcode__BOOLEAN:
      			error("Please try again ");
						bQuestionMark = true;
      			goto repeat;
						break;
          case pcode__QSTRING: ac = acBuffer; break;
  		    case pcode__CSTRING: ac = acBuffer; break;
        }
			} else {
				l = 0;
        switch (nInputType){
          case pcode__INTEGER: n = l; break;
          case pcode__LONG: l = l; break;
      		case pcode__SINGLE: f = (t_single) l; break;
      		case pcode__DOUBLE: d = (t_double) l; break;
      		case pcode__BOOLEAN: c = l; break;
          case pcode__QSTRING: ac = acBuffer; break;
  		    case pcode__CSTRING: ac = acBuffer; break;
				}
			}
		}
	}

  if (bNewLine) myScreen->print("\n");

	interpreter_parameter *p = new interpreter_parameter();

  p->pcodeType = nInputType;
  switch (p->pcodeType){
    case pcode__INTEGER: p->integer_ = n; break;
    case pcode__LONG: p->long_= l; break;
		case pcode__SINGLE: p->single_ = f; break;
		case pcode__DOUBLE: p->double_ = d; break;
		case pcode__BOOLEAN: p->boolean_ = c; break;
		case pcode__QSTRING: 
      p->string_ = QString::fromLocal8Bit(ac); 
      p->qstring_ = &p->string_; 
      break;
		case pcode__CSTRING: p->cstring_ = ac; break;
  }

	return p;

}

interpreter_parameter *function::fINKEY(t_integer *nKeyPressed)
{
  char *ac = myScreen->inkey(nKeyPressed);

  if (*nKeyPressed == 3){

    int n = strlen(ac);
    char *acResult = myTextbuffer->get(n);
    memcpy(acResult, ac, n);
    return new interpreter_parameter(acResult);

  } else return 0;
}

void function::fSLEEP(t_boolean bExpression, t_integer seconds)
{
  static /**/ t_integer nKeyPressed;
  nKeyPressed = 0;

  if (bExpression){

    static /**/ time_t a; 
    static /**/ time_t b;

    time(&a); 

    while(true){
      time(&b); 
      if (a + seconds <= b) break;
      qApp->processEvents(); // IMPORTANT: process gui events 100 msec
  
    }

  } else {
    int n = 0;

    while (strcmp((t_cstring ) myScreen->inkey(&nKeyPressed), "") == 0){
      if (n++ % 1000) qApp->processEvents();// IMPORTANT: process gui events 100 msec
    }
  }
}

interpreter_parameter *function::fINT(t_double d)
{
	static /**/ long l;
  l = (t_long) floor(d);

	interpreter_parameter *p = new interpreter_parameter((t_long) l);

	return p;
}

interpreter_parameter *function::fROUND(interpreter_parameter *p, int nCount)
{
  int m = 1;
  for (int i = 0; i < nCount; i++){
    m = m * 10;
  }

  switch(p->pcodeType){
    case pcode__CURRENCY:      
      
      {

        int m2 = 1;

        for (int i = 0; i < 4 - nCount; i++){
          m2 = m2 * 10;
        }

        t_currency c = p->toCurrency();

        t_integer bc = c.bc();
        t_integer ad = c.ad();

        ad = (ad + 0.5 * m2);
        ad = (ad / m2) * m2;

        delete p;
        if (nCount == 0){
          if (ad >= 10000){
            c.setValue(bc + 1, 0);
          } else {
            c.setValue(bc, 0);
          }
        } else {
          c.setValue(bc, ad);
        }
        return new interpreter_parameter(c);
        break;
      }
    case pcode__SINGLE:
    case pcode__DOUBLE:
    default:
      if (nCount > 0){
        t_double d = p->toDouble();
        bool b = d < 0;
        if (b) d = -d;
        d = (d * m + 0.5) / m;
        if (b) d = -d;
        delete p;
        return new interpreter_parameter(d);
        break;
      }
    case pcode__BYTE:
    case pcode__SHORT:
    case pcode__INTEGER:
    case pcode__LONG:
      {
        t_long d = p->toLong();
        bool b = d < 0;
        if (b) d = -d;
        d = (d * m + 0.5) / m;
        if (b) d = -d;
        delete p;
        return new interpreter_parameter(d);
        break;
      }
  }

  return 0;
}


// get length of string
interpreter_parameter* function::fLEN (t_qstring s)
{
	interpreter_parameter *p = new interpreter_parameter((t_integer) s->length());
	return p;
}

interpreter_parameter* function::fLEN (t_cstring ac)
{
	static /**/ t_integer n;
  n = strlen(ac);
	interpreter_parameter *p = new interpreter_parameter((t_integer) n);
	return p;
}

interpreter_parameter* function::fUTF8 (t_qstring s)
{
  QByteArray a; a = s->toUtf8();

  char *ac = a.data();

  int n = strlen(ac);
  char *acResult = myTextbuffer->get(n);
  memcpy(acResult, ac, n);
  return new interpreter_parameter(acResult);

}

interpreter_parameter* function::fUTF8 (t_cstring s)
{
  QString ss; ss = ss.fromUtf8(s);

  return new interpreter_parameter(&ss);
}

interpreter_parameter* function::fUTF16 (t_cstring s, int wlen)
{
  
  QString ss; ss = ss.setUtf16((const ushort *) s, wlen);
  ss = ss.left(wlen);

  return new interpreter_parameter(&ss);
}

// convert a string to a number
interpreter_parameter* function::fVAL (t_qstring s)
{
	static /**/ t_integer n; // = 0;
	static /**/ t_long l; // = 0;
	static /**/ t_single f; // = 0;
	static /**/ t_double d; // = 0;
	static /**/ t_boolean c; // = 0;
	static /**/ char *ac; // = (char *) acc;
  
  *s = s->trimmed(); // ignore whitespaces

  QByteArray a = s->toLocal8Bit();
  ac = (char *) a.data();

  interpreter_parameter *p;
  p = 0;

	// think carefully, if you want to change the order of the following function calls!

  if (isDouble	(ac, &d, false, true)){
		p = new interpreter_parameter(d);
	} else if (isBoolean	(ac, &c, false, true)){
		p = new interpreter_parameter(c);
	}	else {
  	if ((isHex			 (ac, &l, false, true))
    	|| (isOctal	 (ac, &l, false, true))
    	|| (isBinary  (ac, &l, false, true))
    	|| (isLong		 (ac, &l, false, true)))
		{
			p = new interpreter_parameter(l);
  	} else if (isInteger			 (ac, &n, false, true)){
			p = new interpreter_parameter((t_long) n);
  	} else { // STRING
			if (ac[0] != 0){
				p = new interpreter_parameter((t_long) 0);
			} else {
				p = new interpreter_parameter((t_long) 0);
			}
		}
	}

	return p;

}

interpreter_parameter* function::fVAL (t_cstring acc)
{
	static /**/ t_integer n; // = 0;
	static /**/ t_long l; // = 0;
	static /**/ t_single f; // = 0;
	static /**/ t_double d; // = 0;
	static /**/ t_boolean c; // = 0;
	static /**/ char *ac; // = (char *) acc;

  QString s = acc;
  s = s.trimmed(); // ignore whitespaces

  QByteArray a = s.toLocal8Bit();
  ac = (char *) a.data();

  interpreter_parameter *p;
  p = 0;

	// think carefully, if you want to change the order of the following function calls!
	if (isSingle	(ac, &f)){
		p = new interpreter_parameter(f);
	} else if (isDouble	(ac, &d)){
		p = new interpreter_parameter(d);
	} else if (isBoolean	(ac, &c)){
		p = new interpreter_parameter(c);
	}	else {
  	if ((isHex			 (ac, &l))
    	|| (isOctal	 (ac, &l))
    	|| (isBinary  (ac, &l))
    	|| (isLong		 (ac, &l)))
		{
			p = new interpreter_parameter(l);
  	} else if (isInteger			 (ac, &n)){
			p = new interpreter_parameter((t_long) n);
  	} else { // STRING
			if (ac[0] != 0){
				p = new interpreter_parameter((t_long) 0);
			} else {
				p = new interpreter_parameter((t_long) 0);
			}
		}
	}

	return p;

}



// get toAscii value of first char in a string
interpreter_parameter* function::fASC (t_qstring acString)
{
	static /**/ QChar c;
  if (acString->isEmpty()){
    c = 0;
  } else {
    c = acString->at(0);
  }
	return new interpreter_parameter((t_long) c.unicode());
}

interpreter_parameter* function::fASC (t_cstring acString)
{
	static /**/ unsigned char c;
  c = (unsigned char) acString[0];
	return new interpreter_parameter((t_long) c);
}

interpreter_parameter* function::fFORMAT(interpreter_parameter *p, t_qstring sFormat, t_qstring sFillChar, t_boolean bRightAligned)
{
  interpreter_parameter *r = 0;


  QString s = "%1";
  QString sPrefix;
  QString sSuffix;

  int fieldWidth = 0;
  int base = 10;
  char format = ' '; 
  int precision = -1;
  QChar fillChar = sFillChar->at(0);
  bool bAfter = false;
  bool bFormat = false;
  bool bDot = false;

  int l = sFormat->length();
  for (int i = 0; i < l; i++){
    QChar c = sFormat->at(i);
    if (c == '#'){
      fieldWidth++;
      if (bAfter){
        precision++;
      }
    } else {
      if (c == '.' && precision == -1){
        bAfter = true;
        precision++;
        fieldWidth++;
        bDot = true;
      } else {
        if (fieldWidth == 0){
          sPrefix += c;
        } else {
          if (bFormat == false){
            char cc = c.toAscii();
            switch(cc){
              case 'E':
              case 'e':
              case 'f':
               
                format = cc;
                bFormat = true;
               
                break;
              default:
                sSuffix += c;
                bFormat = true;
                break;
            }
          } else {
            sSuffix += c;
          }
        }
      }
    }
  }

  if (format == ' '){
    format = 'f'; 
  }


  if (bRightAligned == false){
    fieldWidth = -fieldWidth;
  }

  switch(p->pcodeType){
    case pcode__BOOLEAN:
      {        
        bool b = p->toBoolean();
        int n = sFormat->indexOf("/");
        QString sTrue = "";
        QString sFalse = "";
        if (n >= 0){
          sTrue = sFormat->left(n);
          sFalse = sFormat->mid(n + 1);
          r = new interpreter_parameter(b ? sTrue : sFalse);
        } else {
          r = new interpreter_parameter(*sFormat);
        }       
      }
      break;
    case pcode__QSTRING:
    case pcode__CSTRING:
      {
        if (bDot) precision--;
        QString ss = p->toQString();
        s = s.arg(ss, fieldWidth, fillChar);
        s = s.append(sSuffix);
        s = s.prepend(sPrefix);
        r = new interpreter_parameter(s);
        break;
      }
    case pcode__BYTE:
      if (bDot) precision--;
      s = s.arg(p->toByte(), fieldWidth, base, fillChar);
      s = s.append(sSuffix);
      s = s.prepend(sPrefix);
      r = new interpreter_parameter(s);
      break;
    case pcode__SHORT:
    case pcode__INTEGER:
      if (bDot) precision--;
      s = s.arg(p->toInteger(), fieldWidth, base, fillChar);
      s = s.append(sSuffix);
      s = s.prepend(sPrefix);
      r = new interpreter_parameter(s);
      break;
    case pcode__LONG:
      if (bDot) precision--;
      s = s.arg(p->toLong(), fieldWidth, base, fillChar);
      s = s.append(sSuffix);
      s = s.prepend(sPrefix);
      r = new interpreter_parameter(s);
      break;       
    case pcode__SINGLE:
    case pcode__DOUBLE:
      s = s.arg(p->toDouble(), fieldWidth, format, precision, fillChar);
      s = s.append(sSuffix);
      s = s.prepend(sPrefix);
      r = new interpreter_parameter(s);
      break;    
    case pcode__CURRENCY:
      {
        QString ss = p->toQString();
        int n = ss.indexOf(".");
        if (n >= 0){
          ss = ss.left(n + 1 + precision);
        }
        s = s.arg(ss, fieldWidth, fillChar);
        s = s.append(sSuffix);
        s = s.prepend(sPrefix);
        r = new interpreter_parameter(s);
      }
      break;     
    case pcode__DATE:
      {
        QString ss = p->toQString();

        QDateTime d; 
        if (ss.contains("-")){
          d = QDateTime::fromString(ss, "yyyy-MM-dd hh:mm:ss");
        } else {
          d = QDateTime::fromString(ss, "hh:mm:ss");
        }

        QString sss = d.toString(*sFormat);
        s = s.arg(sss, fieldWidth, fillChar);
        r = new interpreter_parameter(s);
        break;
      }

    default:
      r = new interpreter_parameter(p->toQString());
      delete p;
      return r;
      break;
  }
  delete p;
  return r;
}


interpreter_parameter* function::fENCODE(t_qstring sString)
{
  sString->replace(QChar(0), "ZERO_kbasic");
  sString->replace(QChar('\''), "SINGLEQUOTE_kbasic");
  sString->replace(QChar('\\'), "BACKSLASH_kbasic");

  sString->replace(QChar('\x00'), "x00_kbasic");
  sString->replace(QChar('\x1a'), "x1a_kbasic");

  sString->replace(QChar('\n'), "n_kbasic");
  sString->replace(QChar('\t'), "t_kbasic");
  sString->replace(QChar('\f'), "f_kbasic");
  sString->replace(QChar('\r'), "r_kbasic");
  sString->replace(QChar('\v'), "v_kbasic");

  return new interpreter_parameter(sString);
}

interpreter_parameter* function::fENCODE(t_cstring acString)
{
  return fENCODE(&QString::fromLocal8Bit(acString));
}

interpreter_parameter* function::fDECODE(t_qstring sString)
{
  sString->replace("ZERO_kbasic", QChar(0));
  sString->replace("BACKSLASH_kbasic", QChar('\\'));
  sString->replace("SINGLEQUOTE_kbasic", QChar('\''));

  sString->replace("x00_kbasic", QChar('\x00'));
  sString->replace("x1a_kbasic", QChar('\x1a'));

  sString->replace("n_kbasic", QChar('\n'));
  sString->replace("t_kbasic", QChar('\t'));
  sString->replace("f_kbasic", QChar('\f'));
  sString->replace("r_kbasic", QChar('\r'));
  sString->replace("v_kbasic", QChar('\v'));

  return new interpreter_parameter(sString);
}

interpreter_parameter* function::fDECODE(t_cstring acString)
{
  return fDECODE(&QString::fromLocal8Bit(acString));
}

// get first n characters from a string
interpreter_parameter* function::fLEFT (t_qstring sString, t_integer nLen)
{
  //nLen--;
  static /**/ t_integer n;
  n = sString->length();
  if (nLen > (signed) n){

    return new interpreter_parameter(sString);

  } else {

    return new interpreter_parameter(&sString->left(nLen));
  }
}


interpreter_parameter* function::fLEFT (t_cstring acString, t_integer nLen)
{
  static /**/ t_integer n;
  n = strlen(acString);
	char *result = myTextbuffer->get(n);

  if (nLen > (signed) n){
	  memcpy(result, acString, n);
	  result[n] = '\0';
  } else {
	  memcpy(result, acString, n);
	  result[nLen] = '\0';
  }



  return new interpreter_parameter(result);

}


// get last n characters from a string
interpreter_parameter* function::fRIGHT (t_qstring sString, t_integer nLen)
{
 // nLen--;
  static /**/ t_integer n; 
  n = sString->length();

  if (nLen > (signed) n){

    return new interpreter_parameter(sString);
  } else {

    return new interpreter_parameter(&sString->right(nLen));
  }


}


interpreter_parameter* function::fRIGHT (t_cstring acString, t_integer nLen)
{
	char *result = myTextbuffer->get(strlen(acString));
  
  static /**/ t_integer n;
  n = strlen(acString);

  if (nLen > (signed) n){
    memcpy (result, acString, n);
  	result[n] = '\0';
  } else {
	  memcpy(result, acString + (n - nLen), nLen);
	  result[nLen] = '\0';
  }

  return new interpreter_parameter(result);

}


// grab portion of a string
interpreter_parameter* function::fMID (t_qstring ac, t_integer nStart, t_integer nLen)
{
  QString result;
  int l = ac->length();
  if (nStart - 1 > (t_integer) l) return new interpreter_parameter("");
	if (nLen == -1){

  	nLen = (t_integer) l - nStart + 1;

    if (nStart + nLen > (t_integer) l + 1) return new interpreter_parameter("");

    result = ac->mid(nStart -1, nLen);


	} else {

    if (nStart + nLen > (t_integer) l + 1) return new interpreter_parameter("");

    result = ac->mid(nStart -1, nLen);

	}
  
  return new interpreter_parameter(&result);

}


interpreter_parameter* function::fMID (t_cstring ac, t_integer nStart, t_integer nLen)
{
  int l = strlen(ac);
	char *result = myTextbuffer->get(l + 1);
	memcpy(result, ac, l);
  result[l] = 0;
  if (nStart - 1 > (t_integer) l) return new interpreter_parameter("");
	if (nLen == -1){

  	nLen = (t_integer) l - nStart + 1;

    if (nStart + nLen > (t_integer) l + 1) return new interpreter_parameter("");

    memcpy (result, ac + nStart - 1, nLen + 1);
    result[nLen + 1] = '\0';

	} else {

    if (nStart + nLen > (t_integer) l + 1) return new interpreter_parameter("");

    memcpy (result, ac + nStart - 1, nLen);
    result[nLen] = '\0';

	}
  return new interpreter_parameter(result);

}


interpreter_parameter* function::fSPLIT(t_qstring s, t_qstring s2, t_boolean bKeepEmptyParts, t_boolean bCaseSensitive)
{
  _strings *ss = new _strings();
  QStringList l = s->split(*s2, bKeepEmptyParts ? QString::KeepEmptyParts : QString::SkipEmptyParts, bCaseSensitive ? Qt::CaseSensitive : Qt::CaseInsensitive);

  foreach(QString s, l)
  {
    ss->METHOD_Append(s);
  }



  return new interpreter_parameter(ss);
  
}

interpreter_parameter* function::fSTRCOMP (t_qstring s, t_qstring s2, t_integer nMode)
{

	if (nMode == 0){ // binary
    int n = s->compare(*s2) - 1;
    if (n < 0) n = -1;
    if (n > 0) n = 1;
    return new interpreter_parameter(n);
	} else if (nMode == 1){ // text
    int n = s->localeAwareCompare(s2->toLower()) - 1;
    if (n < 0) n = -1;
    if (n > 0) n = 1;
    return new interpreter_parameter(n);
	}

  return new interpreter_parameter((t_boolean) false);
  
}

interpreter_parameter* function::fSTRCOMP (t_cstring ac, t_cstring ac2, t_integer nMode)
{
	static /**/ t_integer n; 
  n = 0;

	if (nMode == 0){ // binary
		n = strcmp(ac, ac2);
    if (n < 0) n = -1;
    if (n > 0) n = 1;
    return new interpreter_parameter(n );
	} else if (nMode == 1){ // text
    QString s = ac;
    QString s2 = ac2;
    n = s.toLower().localeAwareCompare(s2.toLower()) - 1;
    if (n < 0) n = -1;
    if (n > 0) n = 1;
    return new interpreter_parameter(n);    
	}

  return new interpreter_parameter((t_boolean) false);
  
}

void function::fMID2 (t_qstring ac, t_qstring acNew, t_integer nStart, t_integer nLen)
{

  int l = ac->length();
  if (nStart > (t_integer) l) return;

	if (nLen == -1){

  	nLen = (t_integer) acNew->length();

    if (nStart + nLen > l + 1) nLen = l + 1 - nStart;

    *ac = ac->replace(nStart - 1, nLen, acNew->left(nLen));

	} else {

		if (nLen > (t_integer) acNew->length()) nLen = acNew->length();

    if (nStart + nLen > l + 1) nLen = l + 1 - nStart;

    *ac = ac->replace(nStart - 1, nLen, acNew->left(nLen));

	}

  return;
}


void function::fMID2 (t_cstring ac, t_cstring acNew, t_integer nStart, t_integer nLen)
{

  if (nStart > (t_integer) strlen(ac)) return;

	if (nLen == -1){

  	nLen = (t_integer) strlen(acNew);

    if (nStart + nLen > (t_integer) strlen(ac) + 1) nLen = (t_integer) strlen(ac) + 1 - nStart;

    memcpy ((char *) ac + nStart - 1, acNew, nLen);

	} else {

		if (nLen > (t_integer) strlen(acNew)) nLen = strlen(acNew);

    if (nStart + nLen > (t_integer) strlen(ac) + 1) nLen = (t_integer) strlen(ac) + 1 - nStart;

    memcpy ((char *) ac + nStart - 1, acNew, nLen);

	}

  return;
}

// convert number to string representation
interpreter_parameter* function::fSTR (t_double d)
{
	char *result = myTextbuffer->get(1024);

  sprintf (result, "%f", d);

  return new interpreter_parameter(result);

}

// get a string of single character of given toAscii code
interpreter_parameter* function::fCHR (t_integer n)
{

  if (n <= 0 || n > 255){

    QString s = QString(QChar(n));

    return new interpreter_parameter(&s);

  } else {

	  char *result = myTextbuffer->get(1024);

	  result[0] = n;
	  result[1] = '\0';

    return new interpreter_parameter(result);

  }

}

interpreter_parameter* function::fSTRREVERSE (t_qstring s)
{
  
  static QString t; t = "";

  for (t_integer i = 0; i < s->length(); i++){
    t = s->at(i) + t;
  }

  return new interpreter_parameter(&t);

}

interpreter_parameter* function::fSTRREVERSE (t_cstring acString)
{
  QString s = acString;
  QString t = "";

  for (t_integer i = 0; i < s.length(); i++){
    t = s[i] + t;
  }

  static QByteArray a; a = t.toLocal8Bit();

  acString = a.data();


  int n = strlen(acString);
  char *acResult = myTextbuffer->get(n);
  memcpy(acResult, acString, n);
  return new interpreter_parameter(acResult);

}

// convert uppercase letters in a string to toLowercase
interpreter_parameter* function::fLCASE(t_qstring sString)
{
  return new interpreter_parameter(&sString->toLower());

}

interpreter_parameter* function::fLCASE(t_cstring acString)
{
  register int n = strlen(acString);
	char *result = myTextbuffer->get(n);
	memcpy(result, acString, n);

	for(unsigned int i = 0; i < n; i++) result[i] = tolower(result[i]);

  return new interpreter_parameter(result);

}


// convert toLowercase letters in a string to uppercase
interpreter_parameter* function::fUCASE(t_qstring acString)
{

  return new interpreter_parameter(&acString->toUpper());
}

interpreter_parameter* function::fUCASE(t_cstring acString)
{
  register int n = strlen(acString);
	char *result = myTextbuffer->get(n);
	memcpy(result, acString, n);
	for(unsigned int i = 0; i < n; i++) result[i] = toupper(result[i]);

  return new interpreter_parameter(result);

}



interpreter_parameter* function::fTIMER()
{
 static /**/ struct tm *timep;
 static /**/ time_t atime;

 time(&atime); timep=localtime(&atime);

  return new interpreter_parameter( timep->tm_sec + (int) timep );
}

interpreter_parameter* function::fRND(t_boolean bExpression, t_double dValue)
{
  if (dLastRND == 0){ // if Randomize Timer hasn't be called before, make automatically
    this->fRANDOMIZE(true, 0);
  }

	if (bExpression){
    if (dValue == 0) return new interpreter_parameter( dLastRND );

    if (dValue < 0){
      nStartValue = dValue * 10000;

      nStartValue = 16807L * (nStartValue % 127773L) - 2836L * (nStartValue / 127773L);
      if (nStartValue <= 0) nStartValue += 2147483647;
      dLastRND = (double) nStartValue / 2147483648.0;

      return new interpreter_parameter( dLastRND );
    }
	}


  nStartValue = 16807L * (nStartValue % 127773L) - 2836L * (nStartValue / 127773L);
  if (nStartValue <= 0) nStartValue += 2147483647;
  dLastRND = (double) nStartValue / 2147483648.0;

  if (dValue > 0){
    dLastRND *= dValue;
  }

	interpreter_parameter *p = new interpreter_parameter( dLastRND );

  return p;
}

t_qstring function::fFORMATCURRENCY()
{	
  return &kbNullQString;
}

t_qstring function::fFORMATDATETIME()
{	
  return &kbNullQString;
}

t_qstring function::fFORMATNUMBER()
{	
  return &kbNullQString;
}

t_qstring function::fFORMATPERCENT()
{	
  return &kbNullQString;
}

t_qstring function::fWEEKDAYNAME()
{	
  return &kbNullQString;
}

t_qstring function::fMONTHNAME()
{	
  return &kbNullQString;
}

void function::fRANDOMIZE(t_boolean bExpression, t_double dStartValue)
{	
  nStartValue = 0;

	if (bExpression){

    static /**/ struct tm *timep;
    static /**/ time_t atime;

    time(&atime); timep=localtime(&atime);

    nStartValue = timep->tm_sec + (int) timep;

    // in order to get different first number every time
    nStartValue = 16807L * (nStartValue % 127773L) - 2836L * (nStartValue / 127773L);
    if (nStartValue <= 0) nStartValue += 2147483647;
    dLastRND = (double) nStartValue / 2147483648.0;

    nStartValue = 16807L * (nStartValue % 127773L) - 2836L * (nStartValue / 127773L);
    if (nStartValue <= 0) nStartValue += 2147483647;
    dLastRND = (double) nStartValue / 2147483648.0;


    return;

	} else {

repeat:
	myScreen->print("input start value for random generator (-32768 till 32767)? ");

  char *acBuffer = myScreen->input();

	static /**/ t_integer n;// = 0;
	static /**/ t_long l;// = 0;
	static /**/ t_single f;// = 0;
	static /**/ t_double d;// = 0;
	static /**/ t_boolean c;// = 0;
	static /**/ char *ac;// = 0;

	static /**/ int nInputType;
  nInputType = pcode__INTEGER;

	// think carefully, if you want to change the order of the following function calls!
	if (isSingle	(acBuffer, &f)){
    switch (nInputType){
      case pcode__INTEGER: n = (int) floor(f); break;
    }
	} else if (isDouble	(acBuffer, &d)){
    switch (nInputType){
      case pcode__INTEGER: n = (int) floor(d); break;
    }
	} else if (isBoolean	(acBuffer, &c)){
    switch (nInputType){
      case pcode__INTEGER: n = c; break;
    }
	}	else {

  	if ((isHex			 (acBuffer, &l))
    	|| (isOctal	 (acBuffer, &l))
    	|| (isBinary  (acBuffer, &l))
    	|| (isLong		 (acBuffer, &l)))
		{

      switch (nInputType){
        case pcode__INTEGER: n = l; break;
      }

  	} else if (isInteger			 (acBuffer, &n)){

      switch (nInputType){
        case pcode__INTEGER: n = n; break;
      }

  	} else { // STRING
			if (acBuffer[0] != 0){

        switch (nInputType){
          case pcode__INTEGER:
      			error("Please try again");
      			goto repeat;
						break;
      		case pcode__QSTRING: ac = acBuffer; break;
      		case pcode__CSTRING: ac = acBuffer; break;
        }
			} else {
				l = 0;

        switch (nInputType){
          case pcode__INTEGER: n = l; break;
				}
			}
		}
	}

	nStartValue = n;

	if (!(nStartValue >= -32768 && nStartValue <= 32767)){ error(" Overflow, please try again "); goto repeat; }

	}


  // in order to get different first number every time
  nStartValue = 16807L * (nStartValue % 127773L) - 2836L * (nStartValue / 127773L);
  if (nStartValue <= 0) nStartValue += 2147483647;
  dLastRND = (double) nStartValue / 2147483648.0;

  nStartValue = 16807L * (nStartValue % 127773L) - 2836L * (nStartValue / 127773L);
  if (nStartValue <= 0) nStartValue += 2147483647;
  dLastRND = (double) nStartValue / 2147483648.0;


}

void function::fDOEVENTS()
{
  qApp->processEvents();
}

void function::fBEEP()
{
  myScreen->beep();	
}

interpreter_parameter *function::fHEX(int n)
{
 char *rBuf = myTextbuffer->get(1024);

 sprintf( rBuf, "%X", n);

 return new interpreter_parameter(rBuf);

}

interpreter_parameter *function::fOCT(int n)
{
 char *rBuf = myTextbuffer->get(1024);

 sprintf( rBuf, "%o", n);

 return new interpreter_parameter(rBuf);

}

interpreter_parameter *function::fBIN(int n)
{
 static char rBuf[1024];

 char *ac = myTextbuffer->get(1024);

 static /**/ char b;// = 0;

 sprintf( rBuf, "%s", "");

 static /**/ int i;
 i = 0;
 bool bNegative = false;
 if (n < 0){
   if (n < -655536) n = 4294967295 + n;
   if (n < -256) n = 65536 + n;
   else n = 256 + n;
 }
 while (n > 0)
 {
		b = n % 2;
		n = n / 2;
  	rBuf[i++] = b ? '1' : '0';
 
 }

 i--;
 static /**/ int z;
 z = 0;

 while (i >= 0){
		*(ac + z++) = *(rBuf + i--);
 }
 ac[z] = '\0';

 return new interpreter_parameter(ac);

}

interpreter_parameter* function::fRAD (t_double angle){ //converts degrees to radians
return new interpreter_parameter(angle * (M_PI / 180));
}

interpreter_parameter* function::fDEG (t_double angle){ //converts radians to degrees
return new interpreter_parameter(angle * (180 / M_PI));
}

interpreter_parameter* function::fACS (t_double angle){ //angle is supposed to be in radians for
 return new interpreter_parameter(acos(angle));
}

interpreter_parameter* function::fASN (t_double angle){
 return new interpreter_parameter(asin(angle));
}

interpreter_parameter* function::fATN (t_double angle){
 return new interpreter_parameter(atan(angle));
}

interpreter_parameter* function::fCOS (t_double angle){
 return new interpreter_parameter(cos(angle));
}

interpreter_parameter* function::fEXP (t_double n){
 return new interpreter_parameter(exp(n));
}

interpreter_parameter* function::fLOG (t_double n){ //this function is the ten-based logarithmic function
 return new interpreter_parameter(log10(n));
}

interpreter_parameter* function::fLN (t_double n){
 return new interpreter_parameter(log(n));
}

interpreter_parameter* function::fSGN (t_double n){ //returns -1 if negative, 0 if zero, and 1 if positive
	if (n<0) return new interpreter_parameter((t_long) -1);
  else if (n>0) return new interpreter_parameter((t_long) 1);
	else return new interpreter_parameter((t_long) 0);
}

interpreter_parameter* function::fFIX (t_double n){
 return new interpreter_parameter((t_long) n);
}

interpreter_parameter* function::fSIN(t_double angle){
 return new interpreter_parameter(sin(angle));
}

interpreter_parameter* function::fSQR(t_double n){
 return new interpreter_parameter(sqrt(n));
}

interpreter_parameter* function::fTAN(t_double angle){
 return new interpreter_parameter(tan(angle));
}

interpreter_parameter* function::fFACT(t_double n) {
// Or n! instead of fact(n)
  static /**/ double x;
  static /**/ double y;
  y = 1;
  for (x = 1; x <= n; x++){
       y = y * x;
  }
  return new interpreter_parameter(y);
}

interpreter_parameter* function::fLOGB(t_double n, t_double base) {
	return new interpreter_parameter(log(n) / log(base));
}

interpreter_parameter* function::fFRAC(t_double n) {
  return new interpreter_parameter(n - floor(n));
}

interpreter_parameter* function::fHYPOT (t_double a, t_double b) {
  return new interpreter_parameter(sqrt(a * a + b * b));
}

interpreter_parameter* function::fMAX(t_double n, t_double m) {
  return new interpreter_parameter((n >= m)? n : m);
}

interpreter_parameter* function::fMIN(t_double n, t_double m) {
  return new interpreter_parameter((n <= m)? n : m);
}

interpreter_parameter* function::fSEC (t_double angle) {
  return new interpreter_parameter(1 / cos(angle));  // Secant
}


interpreter_parameter *function::fLTRIM(t_qstring acString)
{
  if (acString->isEmpty()){
    return new interpreter_parameter(&acString);
  }

  int i = 0;
  while (acString->at(i).isSpace()) i++;

  return new interpreter_parameter(&acString->mid(i));
}

interpreter_parameter *function::fLTRIM(t_cstring acString)
{
  static /**/ int i;
  i = 0;
  register int n = strlen(acString);
	char *result = myTextbuffer->get(n);
	memcpy(result, acString, n);
  result[n] = 0;
  
  while ((*(result + i)) && (
    (*(result + i)) == ' ' || (*(result + i)) == '\t' || (*(result + i)) == '\n' || (*(result + i)) == '\v' || (*(result + i)) == '\f' || (*(result + i)) == '\r')
    ) i++;

  if (!i){
    return new interpreter_parameter(result);

  }



  return new interpreter_parameter(result + i);

  
}

interpreter_parameter *function::fRTRIM(t_qstring acString)
{
  if (acString->isEmpty()){
    return new interpreter_parameter(&acString);
  }

  int i = acString->length();
  while (acString->at(i - 1).isSpace()) i--;
  
  
  return new interpreter_parameter(&acString->left(i));
}

interpreter_parameter *function::fRTRIM(t_cstring acString)
{  
  static /**/ unsigned int i;

  register int n = strlen(acString);
	char *result = myTextbuffer2->get(n);
	memcpy(result, acString, n);
  result[n] = 0;

  i = n - 1;

  while ((*(result + i)) && (
    (*(result + i)) == ' ' || (*(result + i)) == '\t' || (*(result + i)) == '\n' || (*(result + i)) == '\v' || (*(result + i)) == '\f' || (*(result + i)) == '\r')
    ) i--;

  if (i == (n - 1)){

    return new interpreter_parameter(result);

  }

  int nn = strlen(result) + 1;
  char *dummy = new char[nn]; 
  memcpy(dummy, result, nn);


  result = dummy;
  *(result + i + 1) = '\0';

  interpreter_parameter *p = new interpreter_parameter(result);

  free(dummy);
  return p;

}

interpreter_parameter* function::fTRIM (t_qstring acString)
{
  
  return new interpreter_parameter(&acString->trimmed());
}


interpreter_parameter* function::fTRIM (t_cstring acString)
{
  static /**/ int i;
  i = 0;
  register int n = strlen(acString);
	char *result = myTextbuffer->get(n);
	memcpy(result, acString, n);
  result[n] = 0;
  
  while ((*(result + i)) && ((*(result + i)) == ' ')) i++;

  if (!i){
  } else {
  
    result = result + i;
  }

	
	interpreter_parameter *p2 = fRTRIM(result);
	

	return p2;
}

void mySystem::run()
{    
  t_cstring ac;

  QByteArray a; a = sCommand.toLocal8Bit();
  ac = a.data();

  system(ac);
  quit();
}


interpreter_parameter* function::fSHELL(t_boolean bCommand, t_boolean bSynchron, t_qstring acCommand)
{
  QByteArray a; a = acCommand->toLocal8Bit();

  return fSHELL(bCommand, bSynchron, a.data());
}

interpreter_parameter* function::fSHELL(t_boolean bCommand, t_boolean bSynchron, t_cstring acCommand)
{
  if (bSynchron){
    int result;

	  if (!bCommand || acCommand[0] == 0) return new interpreter_parameter((t_long) 0);

    result = system(acCommand);

    if (result == 127) result = -255;

    return new interpreter_parameter((t_long) result);
  } else {
    if (bCommand) (new mySystem(&QString(acCommand)))->start(); //  might be a memory leak thread got never released

    return new interpreter_parameter(0);
  }

}





/*


---------
Formatted strings:

formatstring may contain \\ or ! or &

you can use "\\" to print a certain number of characters (n-2), so

"\\" will print 2
"\  \" will print 4 characters

A "!" will print only the first character of the string

A "&" will print the whole string

----------
Formatted numbers:
you can choose the width of the printing, the number of decimals and the place of the decimal point. Also the place of $, kommas and + or minus

- every # is a decimal digit (max 18)
- additional spaces right of the decimal point will be filled with 0
- additional spaces left of the decimal point will be filled with spaces
- exception: 1 > n > -1 when a 0 is before the decimal point
- all numbers rounded to number of digits
- negative numbers with a leading -
- this leading - takes one # in the formatstring

 0.468  ##.##    0.47   one leading space
 0.468  #.####  0.4680  no leading space
12.5    ##.##   12.50   no leading space
12.5    ####.#    12.5  two leading spaces

Well, this is a bit confusing:

- a plus at the beginning produces a leading + or - before the number
- a minus at the beginning produces always a - (for positive and negative)
- a plus at the end produces a trailing + or -
- a minus at the end produces a space for positive and a - for negative numbers

Now the $ and stuff:
- a $ at the beginning: $ before the number
- for a negative value, the - is between $ and first digit
- several $ reserve additional spaces, but only one $ is printed
- two * fill the spaces with ***
- you can combine ** and $
- a komma left of decimal point marks thousands (1,000,000 - English style)

Exponentials:
- scientific notation by including 3 - 6 "^" signs
- one for "E", one for +/- and two to four for the exponents

Literals:
literals must be preceeded by a "_":

print using "_##"; 1  'prints #1
print using "#_#"; 1  'prints 1#

- if the number doesn't fit, the formatstring is ignored and the whole number with a leading "%" is printed

- variables may be used as formatstrings

- formatstrings may be emedded into normal text (seems like C to me):

a = 12.56
x$= "sum"
print using "The & is $##.##";x$,a

Please be careful, this is PowerBasic not qbasic. There may be differences, but I did not found a better description.

NUMBER

# number
. decimal
, print thousand separator
+
^^^^^
-
$$
**
**$

--> sprintf

##. number to large then print as exp
###,.##
###+.
###.+#
$$###
**$####

STRING

&complete string
! first character
\ \     print count spaces between \ + 2

&
!
\\

ESCAPE
_


*/

/*
char *function::fUSING(char *acUSING, char c)
{
	return "";
}

char *function::fUSING(char *acUSING, int n)
{
	return "";
}

char *function::fUSING(char *acUSING, long l)
{
	return "";
}

char *function::fUSING(char *acUSING, float f)
{
	return "";
}

char *function::fUSING(char *acUSING, double d)
{
	return "";
}

char *function::fUSING(char *acUSING, char *ac)
{
	return "";
}
*/

/*
Hello, Bernd and Everyone,<br>
  <br>
I read this and noticed that PowerBASIC is being used to describe behavior
in statements. &nbsp;As I recall from having used PowerBASIC some, it differs
significantly from MS's various BASIC dialects. &nbsp;Therefore, I include for
your perusal, a definition of the PRINT USING statement.<br>
  <br>
PRINT USING<br>
  <br>
Action:<br>
  <br>
&nbsp;&nbsp;Prints strings or numbers using a specified format<br>
  <br>
Syntax:<br>
  <br>
&nbsp;&nbsp;PRINT USING <i>formatstring; expressionlist</i> [{,|;}]<br>
  <br>
Remarks:<br>
  <br>
&nbsp;&nbsp;The <i>formatstring</i> is a string literal (or variable) containing literal
characters to print (such as labels) and special formatting characters. &nbsp;These
&nbsp; formatting characters determine the field and the format of the printed
string or numbers. &nbsp;Spaces, commas, and semicolons in the <i>expressionlist</i>
 have the same meaning as they do in a PRINT statement.<br>
  <br>
The <i>expressionlist</i> contains the string expressions or numeric expressions
to be printed, separated by semicolons.<br>
  <br>
When PRINT USING is used to print strings, you may use one of three formatting
characters to format the string field, as described in the following list:<br>
  <br>
  <table cellpadding="2" cellspacing="2" border="1" width="80%" align="Center">
    <tbody>
      <tr>
        <td valign="Top">Character<br>
        </td>
        <td valign="Top">Description<br>
        </td>
      </tr>
      <tr>
        <td valign="Top">!<br>
        </td>
        <td valign="Top">Only the first character in the given string is
to be printed<br>
        </td>
      </tr>
      <tr>
        <td valign="Top">\ &nbsp; &nbsp;\<br>
        </td>
        <td valign="Top">Prints 2+n characters from a string where n is the
number of spaces between the two backslashes. &nbsp;If the backslashes are typed
with no spaces, two characters are printed, and so on. &nbsp;If the field is longer
than the string, the string is left-justified in the field and padded with
spaces to the right.<br>
        </td>
      </tr>
      <tr>
        <td valign="Top">&amp;<br>
        </td>
        <td valign="Top">Indicates a variable length string field. &nbsp;When
the field is specified with the ampersand (&amp;), the string is output without
modification.<br>
        </td>
      </tr>
    </tbody>
  </table>
&nbsp;<br>
When PRINT USING is used to print numbers, the following special characters
can be used to format the numeric field:<br>
  <br>
  <table cellpadding="2" cellspacing="2" border="1" width="80%" align="Center">
    <tbody>
      <tr>
        <td valign="Top">Character<br>
        </td>
        <td valign="Top">Description<br>
        </td>
      </tr>
      <tr>
        <td valign="Top">#<br>
        </td>
        <td valign="Top">Represents each digit position. &nbsp;Digit positions
are always filled. &nbsp;If the number to be printed has fewer digits than positions
specified, the number is right justified (preceded by spaces) in the field.<br>
        </td>
      </tr>
      <tr>
        <td valign="Top">.<br>
        </td>
        <td valign="Top">Prints a decimal point. &nbsp;A decimal point may be
inserted at any position in the field. If the format string specifies that
a digit is to precede the decimal point, the digit is always printed (as
0, if necessary). &nbsp;If necessary, numbers are rounded.<br>
        </td>
      </tr>
      <tr>
        <td valign="Top">+<br>
        </td>
        <td valign="Top">Causes the sign of the number (plus or minus) to
be printed before the number (if it appears at the beginningat
string) or after (if it appears at the endat string).<br>
        </td>
      </tr>
      <tr>
        <td valign="Top">-<br>
        </td>
        <td valign="Top">Causes a negative number to be printed with a trailing
minus sign if it appears at the endat string.<br>
        </td>
      </tr>
      <tr>
        <td valign="Top">**<br>
        </td>
        <td valign="Top">Causes leading spaces in the numeric field to be
filled with asterisks. &nbsp;The double asterisk also specifies positions for
two more digits.<br>
        </td>
      </tr>
      <tr>
        <td valign="Top">$$<br>
        </td>
        <td valign="Top">Causes a dollar sign to be printed to the immediate
leftatted number. &nbsp;The $$ specifies two more digit positions,
one of which is the dollar sign.<br>
        </td>
      </tr>
      <tr>
        <td valign="Top">**$<br>
        </td>
        <td valign="Top">Combines the effects of the double-asterisk and
double-dollar sign signals. &nbsp;Leading spaces are asterisk filled, and a dollar
sign is printed before the number. &nbsp;The **$ symbols specify three more digit
positions, one of which is the dollar sign. When negative numbers are printed,
the minus sign appears to the immediate left of the dollar sign.<br>
        </td>
      </tr>
      <tr>
        <td valign="Top">,<br>
        </td>
        <td valign="Top">If the comma appears to the left of the decimal
point, in a format string, it causes a comma to be printed to the left of
every third digit left of the decimal point. &nbsp;If it appears at the end of
the format string, it is printed as part of the string. &nbsp;A comma specifies
another digit position. The comma has no effect if used with exponential
(^^^^ or ^^^^^) format.<br>
        </td>
      </tr>
      <tr>
        <td valign="Top">^^^^<br>
        </td>
        <td valign="Top">Specifies exponential format. &nbsp;You can also use
five carets (^^^^^) to allow E+xxx to be printed for larger numbers. &nbsp;Any
decimal point position may be specified. &nbsp;The significant digits are left
justified and the exponent is adjusted. &nbsp;Unless a leading +, trailing +,
or - is specified, one digit position is used to the left of the decimal
point to print a space or a minus sign. <br>
        </td>
      </tr>
      <tr>
        <td valign="Top">_<br>
        </td>
        <td valign="Top">An underscore in the format string prints the next
character as a literal character. &nbsp;A literal underscore is printed as the
result of two underscores in the format string.<br>
        </td>
      </tr>
    </tbody>
  </table>
  <br>
If he number to be printed is larger than the specified numeric field, a
percent sign (%) is printed in front of the number. &nbsp;If rounding causes a
number to exceed the field, a percent sign is printed in front of the rounded
number. If the number of digits specified exceeds 24, an error message results
that reads <tt>Illegal function call.</tt><br>
  <br>
[examples omitted - too tedious to count all those spaces and type in correctly.]
&nbsp;&nbsp; &nbsp;&nbsp; &nbsp;<br>
  <br>
I hope this helps out some. &nbsp;This info may be viewed by engaging the help
facilities in either QBASIC or QuickBASIC 4.5 (it is essentially the same
for either of them). I don't know if Visual BASIC added anything to this

*/

//  Ergebnisse werden nicht von double/single-Berechnungen werden mit Nachkommastellen ausgegeben, 
// qbasic lässt NAchkommastellen weg
void function::fPRINT(t_boolean bWRITE, t_boolean bWRITEStringExpression, 
                      t_boolean bFIRST, t_boolean bFILEHANDLE, 
                      t_integer nFILEHANDLE, t_qstring acUSING, 
                      t_boolean bEXPRESSION, t_boolean bSPC, t_boolean bTAB, 
                      interpreter_parameter *STRING_EXPRESSION, t_integer nSPC, 
                      t_integer nTAB, t_boolean bTabbedOutput, t_boolean bNewLine, t_boolean bEcho, t_boolean bLog)
{
  QByteArray a; a = acUSING->toLocal8Bit();

  fPRINT(bWRITE, bWRITEStringExpression, 
                      bFIRST, bFILEHANDLE, 
                      nFILEHANDLE, a.data(), 
                      bEXPRESSION, bSPC, bTAB, 
                      STRING_EXPRESSION, nSPC, 
                      nTAB, bTabbedOutput, bNewLine, bEcho, bLog);
}

void function::fPRINT(t_boolean bWRITE, t_boolean bWRITEStringExpression, 
                      t_boolean bFIRST, t_boolean bFILEHANDLE, 
                      t_integer nFILEHANDLE, t_cstring acUSING, 
                      t_boolean bEXPRESSION, t_boolean bSPC, t_boolean bTAB, 
                      interpreter_parameter *STRING_EXPRESSION, t_integer nSPC, 
                      t_integer nTAB, t_boolean bTabbedOutput, t_boolean bNewLine, t_boolean bEcho, t_boolean bLog)
{

  
  {

		if (bSPC){
      bNewLine = false;
      for (int i = 0; i < nSPC; i++){ fPRINT(bFIRST, bFILEHANDLE, nFILEHANDLE, " ", bEcho, bLog); /*myTerminal->print(" "); */}
		} else if (bTAB){
      bNewLine = false;
      nTAB -= myScreen->pos();
      for (int i = 0; i < nTAB; i++){ 
        fPRINT(bFIRST, bFILEHANDLE, nFILEHANDLE, " ", bEcho, bLog); /*myTerminal->print(" ");*/ 
      }
		} else if (bEXPRESSION){

      static /**/ t_cstring s;
      static /**/ t_cstring s2;
      s = 0;

      bool bUnicode = false;

      bool bPrintNumberSpace = false;
      

			if (acUSING != 0 && acUSING[0] != 0){
        bool bString = true;
        int i = 0;
        static int i2 = 0;
        int i3 = 0;

        if (bFIRST){
          i2 = 0;
        }

        static char usi[1024];
        static char usi2[1024];
        static char obi[1024];

        int bef = 0;
        int aft = 0;
        int expo = 0;
        bool bDot = false;
        bool bSign = false;
        bool bDollar = false;
        bool bStar = false;
        bool bMinus = false;        
        bool bComma = false;        
        int m = 0;

        bool b = false;

        int nLen = strlen(acUSING);


        while(acUSING[i2] != 0){

          switch(acUSING[i2]){

            // STRING
            case '&': // Druckt gesamte Zeichenfolge
              if (b) goto r; 
              if (bString && s == 0){
                bString = false;
                s = STRING_EXPRESSION->toCString(); 
              }
              while (s[i3] != 0){
                usi[i++] = s[i3]; i3++;
              }
              i2++;  
              b = true;
              break;
            case '!': // Druckt nur das erste Zeichen
              if (b) goto r;
              if (bString && s == 0){
                bString = false;
                s = STRING_EXPRESSION->toCString(); 
              }
              if (s[i3] != 0){
                usi[i++] = s[i3]; i3++;
              }
              i2++;  
              b = true;
              break;
            case '\\': // \ \   Druckt die ersten n Zeichen,wobei n die Anzahl der Leerzeichen zwischen den Schrägstrichen plus 2 ist.
              {
               if (b) goto r;
               if (bString && s == 0){
                  bString = false;
                  s = STRING_EXPRESSION->toCString(); 
               }
               bool bEnd = false;
                while (s[i3] != 0 && acUSING[i2] != 0){
                  usi[i++] = s[i3]; i3++;
                  if (acUSING[++i2] == '\\'){
                    usi[i++] = s[i3]; i3++;
                    bEnd = true;
                    break;
                  }
                }
                if (bEnd == false){
                  myInterpreter->runtimeError("missing ending \\ in PRINT USING");
                }
                i2++;  
                b = true;              
              }
              break;

            
/*
              Zeichen, die einen numerischen Ausdruck formatieren
 #    Position einer Ziffer             ¦ -     Nach der Ziffer plaziert,
 .    Position des Dezimalpunkts        ¦       druckt nachfolgendes Minus-
 ,    Wird links des Dezimalpunkts      ¦       zeichen für negative Zahlen.
      plaziert, druckt Komma nach jeder ¦ $$    Druckt führendes $.
      dritten Ziffer.                   ¦ **    Füllt führende Leerstellen
 +    Position des Nummernzeichens      ¦       mit einem *.
^^^^  Druckt im Exponentialformat       ¦ **$   Kombiniert ** und $$.

*/
            // NUMERIC
            case '+':
              if (b || bSign) goto r;
              if (bSign){                
              } else {
                bSign = true;
              }
              i2++;   
              break;
            case '#':
              if (b) goto r;
              if (bDot){
                aft++;
              } else {
                bef++;
              }
              i2++;   
              break;
            case '.':
              if (b || bDot) goto r;
              bDot = true;
              i2++;   
              break;
            case ',':
              if (b || bComma) goto r;
              bComma = true;
              //bef++;
              i2++;   
              break;
            case '-':
              if (b || bMinus) goto r;
              bMinus = true;
              i2++;            
              if (aft || bef) goto numb;
              break;
            case '^':
              if (b) goto r;
              if (i2 + 3 < nLen && acUSING[i2 + 1] == '^' && acUSING[i2 + 2] == '^' && acUSING[i2 + 3] == '^'){
                i2 += 4;   
                expo = 4;
                if (i2 + 1 < nLen && acUSING[i2 + 1] == '^'){
                  i2++;
                  expo++;
                }
              } else goto def;
              break;

            case '$':
              if (b) goto r;
              if (i2 + 1 < nLen && acUSING[i + 1] == '$'){
                if (b || bDollar) goto r;
                if (bDollar){                
                } else {
                  bDollar = true;
                }              
                i2 += 2;   
              } else goto def;
              break;
            case '*':
              if (b) goto r;
              if (i2 + 2 < nLen && acUSING[i + 1] == '*' && acUSING[i + 2] == '$'){
                if (b || bDollar || bStar) goto r;
                if (bDollar || bStar){                
                } else {
                  bDollar = true;
                  bStar = true;
                }              
                i2 += 3;   
              } else if (i2 + 1 < nLen && acUSING[i + 1] == '*'){
                if (b || bStar) goto r;
                if (bStar){                
                } else {
                  bStar = true;
                }     
                i2 += 2;   
              } else goto def;
              break;


            case '_': // escape code
              if (i2 + 1 < nLen){
                usi[i++] = acUSING[i2 + 1]; i2 += 2;              
              }
              break;
            default:
              
numb:

              if (aft || bef || expo){
              int nType = STRING_EXPRESSION->pcodeType;

                  sprintf(obi, ""); 
                  if (bDollar){
                    sprintf("%s ", obi); 
                    bef++;
                  }
                  if (bStar && bDollar){
                    bef++;
                  } else if (bStar){
                    bef += 2;
                  }

                  sprintf(obi, "%s%%", obi); 
                  if (bSign) sprintf(obi, "%s+", obi); 


                  if (expo){
                    sprintf(obi, "%s.0E", obi);  // TODO2 unterschied zu qbasic  -1D+06  -1E+006  dreistellung und kein d in kbasic manchmal
                    //sprintf(obi, "%s%d", obi, 2); 
                    //sprintf(obi, "%sf", obi); 
                  } else {

                    switch(nType){
                      case pcode__BOOLEAN:
                        /*
                      case pcode__INT16:
                      case pcode__INT32:
                      case pcode__UINT16:
                      */
                      case pcode__BYTE:
                      case pcode__SHORT:
                      case pcode__INTEGER://"%d"
                        sprintf(obi, "%s%d", obi, bef); 
                        sprintf(obi, "%sd", obi); 
                        break;
                        /*
                      case pcode__INT64:
                      case pcode__UINT32:
                      case pcode__UINT64:*/
                      case pcode__LONG://"%I64d"  "%lld"
                        sprintf(obi, "%s%d", obi, bef); 
                        sprintf(obi, "%slld", obi); 
                        break;
                      case pcode__SINGLE:
                      case pcode__DOUBLE://"%.6f"                   
                      case pcode__CURRENCY://""  
                        sprintf(obi, "%s%d.", obi, bef); 
                        sprintf(obi, "%s%d", obi, aft); 
                        sprintf(obi, "%sf", obi); 
                        break;
                    }             

                  }

                  if (expo){
                    sprintf(&(usi[i]), obi, STRING_EXPRESSION->toDouble()); 
                  } else {

                    switch(nType){
                      case pcode__BOOLEAN:
                        /*
                      case pcode__INT16:
                      case pcode__INT32:
                      case pcode__UINT16:*/
                      case pcode__BYTE:
                      case pcode__SHORT:
                      case pcode__INTEGER://"%d"
                        sprintf(&(usi[i]), obi, STRING_EXPRESSION->toInteger()); 
                        break;
                        /*
                      case pcode__INT64:
                      case pcode__UINT32:
                      case pcode__UINT64:*/
                      case pcode__LONG://"%I64d"  "%lld"
                        sprintf(&(usi[i]), obi, STRING_EXPRESSION->toLong()); 
                        break;
                      case pcode__SINGLE:
                      case pcode__DOUBLE://"%.6f"                   
                        sprintf(&(usi[i]), obi, STRING_EXPRESSION->toDouble()); 
                        break;
                      case pcode__CURRENCY://""  
                        sprintf(&(usi[i]), obi, STRING_EXPRESSION->toDouble()); 
                        break;
                    }             

                  }

                  m = strlen(&(usi[i]));
                  if (bStar){
                    for (int x = i; x < m; x++){
                      if (usi[x] == ' '){
                        usi[x] = '*';
                      } else if (usi[x] != '$'){
                        break;
                      }
                    }
                  }
                  if (bDollar){
                    for (int x = i; x < m; x++){
                      if (usi[x] == '-' && x - 1 >= 0){
                        usi[x - 1] = '-';
                        usi[x] = '$';
                      } else if (usi[x] != ' ' && usi[x] != '*'){
                        break;
                      }
                    }
                  }
                  if (bMinus){
                    bool bb = false;
                    for (int x = i; x < m; x++){
                      if (usi[x] == '-'){
                        bb = true;
                        usi[x] = bStar ? '*' : ' '; 
                        break;
                      }
                    }
                    
                    i += m;
                    if (bb){
                      usi[i++] = '-'; 
                    } else {
                      usi[i++] = ' '; 
                    }
                    usi[i] = '\0';
                                        
                  } else {
                    i += m;
                  }

                  if (bComma && bDot){
                    strcpy(usi2, usi);
                    for (int x = i - m; x < m; x++){
                      if (usi[x] == '.'){
                        int k = 0;
                        int h = 0;
                        for (int y = x - 1; y >= 0; y--){
                          if (k % 3 == 0 && k > 0){ //  fehelr kommasetzung
                            obi[h++] = usi[y];
                            obi[h++] = ',';                       
                          } else {
                            obi[h++] = usi[y];
                          }
                          k++;
                        }
                        if (obi[h] == ',') h -= 3;//obi[h] = '\0';
                        else h -= 2;
                        //else obi[h++] = '\0';

                        for (int y = h; y >= 0; y--){
                          usi[h - y] = obi[y];
                        }

                        for (int y = h; true; y++){                           
                          usi[y] = usi2[y];
                          if (usi2[y] == '\0') break;
                        }

                        break;
                      }
                    }
                  }

                aft = 0;
                bef = 0;
                expo = 0;
              
                if (acUSING[i2]){
                  usi[i++] = acUSING[i2]; i2++;              
                } else {    
                  goto r;
                }

                break;                
              }
def:
              usi[i++] = acUSING[i2]; i2++;              
              break;
            }
          

        }

r:
        if (bef || aft || expo) goto numb;   
        usi[i] = '\0';
        s = usi;      

      } else {

        switch(STRING_EXPRESSION->pcodeType){
          case pcode__BYTE:
          case pcode__SHORT:
          case pcode__INTEGER:
          case pcode__LONG:
          case pcode__SINGLE:
          case pcode__DOUBLE:
          case pcode__CURRENCY:
            {
              if (!bFILEHANDLE && !bTabbedOutput /*&& !bNewLine*/){ 
                bPrintNumberSpace = true;
                int n = STRING_EXPRESSION->pcodeType;
                if (STRING_EXPRESSION->toInteger() >= 0) fPRINT(bFIRST, bFILEHANDLE, nFILEHANDLE, " ", bEcho, bLog);
                STRING_EXPRESSION->pcodeType = n;
              }
            }
            break;
        }       

        bUnicode = STRING_EXPRESSION->pcodeType == pcode__QSTRING;
        if (bUnicode == false){

          s = STRING_EXPRESSION->toCString(); 
          
        }
      }

      if (bWRITE){
        if (!bFIRST){
          fPRINT(bFIRST, bFILEHANDLE, nFILEHANDLE, ",", bEcho, bLog);
        }       
        if (bWRITEStringExpression){
          fPRINT(bFIRST, bFILEHANDLE, nFILEHANDLE, "\"", bEcho, bLog);
        }       
      }

      if (bUnicode){
        fPRINT( bFIRST, bFILEHANDLE, nFILEHANDLE, &STRING_EXPRESSION->toQString(), bEcho, bLog);
      } else {
        s2 = s;
        fPRINT( bFIRST, bFILEHANDLE, nFILEHANDLE, s2, bEcho, bLog);
      }

      if (bWRITE){
        if (bWRITEStringExpression){
          fPRINT(bFIRST, bFILEHANDLE, nFILEHANDLE, "\"", bEcho, bLog);
        }       
      }

      if (bPrintNumberSpace){
        fPRINT(bFIRST, bFILEHANDLE, nFILEHANDLE, " ", bEcho, bLog);
      }

		
		}

 		if (bTabbedOutput){
      int n = myScreen->pos();
      n = 14 - (n % 14);

      for (int i = 0; i < n; i++){ 
        fPRINT(bFIRST, bFILEHANDLE, nFILEHANDLE, " ", bEcho, bLog);
      }
    }

    if ((!bFILEHANDLE || bWRITE) && bNewLine && !bLog){ 
      fPRINT(bFIRST, bFILEHANDLE, nFILEHANDLE, "\n", bEcho, bLog);  // prevent EOL after pressing return if true
    }

	}

}




interpreter_parameter *function::fCOMPARE(t_qstring s, t_qstring s2, t_boolean CaseSensitive)
{
  return new interpreter_parameter((t_integer) s->compare(*s2, CaseSensitive ? Qt::CaseSensitive : Qt::CaseInsensitive));
}

interpreter_parameter *function::fCONTAINS(t_qstring s, t_qstring s2, t_boolean CaseSensitive)
{
  bool b = (s->contains(*s2, CaseSensitive ? Qt::CaseSensitive : Qt::CaseInsensitive));
  return new interpreter_parameter((t_boolean) b);
}

interpreter_parameter *function::fCOUNT(t_qstring s, t_qstring s2, t_boolean CaseSensitive)
{
  return new interpreter_parameter((t_integer) s->count(*s2, CaseSensitive ? Qt::CaseSensitive : Qt::CaseInsensitive));
}

interpreter_parameter *function::fENDSWITH(t_qstring s, t_qstring s2, t_boolean CaseSensitive)
{
  return new interpreter_parameter((t_boolean) s->endsWith(*s2, CaseSensitive ? Qt::CaseSensitive : Qt::CaseInsensitive));
}

interpreter_parameter *function::fSTARTSWITH(t_qstring s, t_qstring s2, t_boolean CaseSensitive)
{
  return new interpreter_parameter((t_boolean) s->startsWith(*s2, CaseSensitive ? Qt::CaseSensitive : Qt::CaseInsensitive));
}

interpreter_parameter *function::fLEFTJUSTIFIED(t_qstring s, t_integer Width, t_qstring s2, t_boolean CaseSensitive)
{
  return new interpreter_parameter(s->leftJustified(Width, s2->at(0), CaseSensitive ? Qt::CaseSensitive : Qt::CaseInsensitive));
}

interpreter_parameter *function::fRIGHTJUSTIFIED(t_qstring s, t_integer Width, t_qstring s2, t_boolean CaseSensitive)
{
  return new interpreter_parameter(s->rightJustified(Width, s2->at(0), CaseSensitive ? Qt::CaseSensitive : Qt::CaseInsensitive));
}

interpreter_parameter *function::fSECTION(t_qstring s, t_qstring s2, t_integer Start, t_integer End, t_qstring SectionFlags)
{
  int i = QString::SectionDefault;

  if (!SectionFlags->isEmpty()){
    if (SectionFlags->contains("SectionSkipEmpty", Qt::CaseInsensitive)) i |= QString::SectionSkipEmpty;
    if (SectionFlags->contains("SectionIncludeLeadingSep", Qt::CaseInsensitive)) i |= QString::SectionIncludeLeadingSep;
    if (SectionFlags->contains("SectionIncludeTrailingSep", Qt::CaseInsensitive)) i |= QString::SectionIncludeTrailingSep;
    if (SectionFlags->contains("SectionCaseInsensitiveSeps", Qt::CaseInsensitive)) i |= QString::SectionCaseInsensitiveSeps;
  }

  return new interpreter_parameter(s->section(*s2, Start, End, (QString::SectionFlags) i));
}

interpreter_parameter *function::fSIMPLIFIED(t_qstring s)
{
  return new interpreter_parameter(s->simplified());
}

interpreter_parameter *function::fTRIMMED(t_qstring s)
{
  return new interpreter_parameter(s->trimmed());
}
/*
interpreter_parameter *function::fREVERSED(t_qstring s)
{
  return new interpreter_parameter(s->reversed());
}*/

interpreter_parameter *function::fUNICODE(t_qstring s, t_integer Position, t_boolean bEXPRESSION2, t_integer Unicode)
{
  if (bEXPRESSION2){
    return new interpreter_parameter(QString(QChar(Unicode)));
  } else {
    return new interpreter_parameter(QString(s->at(Position)));
  }
}

void function::fPREPEND(t_qstring s, t_qstring s2)
{
  s->prepend(*s2);
}

void function::fAPPEND(t_qstring s, t_qstring s2)
{
  s->append(*s2);
}

void function::fREMOVE(t_qstring s, t_integer Position, t_integer Length)
{
  s->remove(Position, Length);
}

void function::fTRUNCATE(t_qstring s, t_integer Position)
{
  s->truncate(Position);
}

void function::fINSERT(t_qstring s, t_qstring s2, t_integer Position)
{
  s->insert(Position, *s2);
}

void function::fFILL(t_qstring s, t_qstring s2, t_integer Position)
{
  s->fill(s2->at(0), Position);
}

interpreter_parameter *function::fADDDAYS(t_date d1, t_integer n)
{  
  QDateTime dt1(QDate(d1.nYear, d1.nMonth, d1.nDay), QTime(d1.nHour, d1.nMinute, d1.nSecond));
  QDateTime dt2 = dt1.addDays(n);

  return new interpreter_parameter(t_date(dt2));  
}

interpreter_parameter *function::fADDMONTHS(t_date d1, t_integer n)
{  
  QDateTime dt1(QDate(d1.nYear, d1.nMonth, d1.nDay), QTime(d1.nHour, d1.nMinute, d1.nSecond));
  QDateTime dt2 = dt1.addMonths(n);

  return new interpreter_parameter(t_date(dt2));  
}

interpreter_parameter *function::fADDYEARS(t_date d1, t_integer n)
{  
  QDateTime dt1(QDate(d1.nYear, d1.nMonth, d1.nDay), QTime(d1.nHour, d1.nMinute, d1.nSecond));
  QDateTime dt2 = dt1.addYears(n);

  return new interpreter_parameter(t_date(dt2));  
}

interpreter_parameter *function::fSUBDAYS(t_date d1, t_integer n)
{  
  QDateTime dt1(QDate(d1.nYear, d1.nMonth, d1.nDay), QTime(d1.nHour, d1.nMinute, d1.nSecond));
  QDateTime dt2 = dt1.addDays(-n);

  return new interpreter_parameter(t_date(dt2));  
}

interpreter_parameter *function::fSUBMONTHS(t_date d1, t_integer n)
{  
  QDateTime dt1(QDate(d1.nYear, d1.nMonth, d1.nDay), QTime(d1.nHour, d1.nMinute, d1.nSecond));
  QDateTime dt2 = dt1.addMonths(-n);

  return new interpreter_parameter(t_date(dt2));  
}

interpreter_parameter *function::fSUBYEARS(t_date d1, t_integer n)
{  
  QDateTime dt1(QDate(d1.nYear, d1.nMonth, d1.nDay), QTime(d1.nHour, d1.nMinute, d1.nSecond));
  QDateTime dt2 = dt1.addYears(-n);

  return new interpreter_parameter(t_date(dt2));  
}

interpreter_parameter *function::fADDHOURS(t_date d1, t_integer n)
{  
  QDateTime dt1(QDate(d1.nYear, d1.nMonth, d1.nDay), QTime(d1.nHour, d1.nMinute, d1.nSecond));
  QDateTime dt2 = dt1.addSecs(60 * 60 * n);

  return new interpreter_parameter(t_date(dt2));  
}

interpreter_parameter *function::fADDMINUTES(t_date d1, t_integer n)
{  
  QDateTime dt1(QDate(d1.nYear, d1.nMonth, d1.nDay), QTime(d1.nHour, d1.nMinute, d1.nSecond));
  QDateTime dt2 = dt1.addSecs(60 * n);

  return new interpreter_parameter(t_date(dt2));  
}

interpreter_parameter *function::fADDSECONDS(t_date d1, t_integer n)
{  
  QDateTime dt1(QDate(d1.nYear, d1.nMonth, d1.nDay), QTime(d1.nHour, d1.nMinute, d1.nSecond));
  QDateTime dt2 = dt1.addSecs(n);

  return new interpreter_parameter(t_date(dt2));  
}

interpreter_parameter *function::fSUBHOURS(t_date d1, t_integer n)
{  
  QDateTime dt1(QDate(d1.nYear, d1.nMonth, d1.nDay), QTime(d1.nHour, d1.nMinute, d1.nSecond));
  QDateTime dt2 = dt1.addSecs(-(60 * 60 * n));

  return new interpreter_parameter(t_date(dt2));  
}

interpreter_parameter *function::fSUBMINUTES(t_date d1, t_integer n)
{  
  QDateTime dt1(QDate(d1.nYear, d1.nMonth, d1.nDay), QTime(d1.nHour, d1.nMinute, d1.nSecond));
  QDateTime dt2 = dt1.addSecs(-(60 * n));

  return new interpreter_parameter(t_date(dt2));  
}

interpreter_parameter *function::fSUBSECONDS(t_date d1, t_integer n)
{  
  QDateTime dt1(QDate(d1.nYear, d1.nMonth, d1.nDay), QTime(d1.nHour, d1.nMinute, d1.nSecond));
  QDateTime dt2 = dt1.addSecs(-n);

  return new interpreter_parameter(t_date(dt2));  
}

interpreter_parameter *function::fDAYOFWEEK(t_date d1, t_qstring Format)
{  
  bool shorty = Format->compare("ShortFormat", Qt::CaseInsensitive) == 0;

  QDateTime dt1(QDate(d1.nYear, d1.nMonth, d1.nDay), QTime(d1.nHour, d1.nMinute, d1.nSecond));

  switch(dt1.date().dayOfWeek()){
    case 1: return shorty ? new interpreter_parameter(new QString("Mon")) : new interpreter_parameter(new QString("Monday"));
    case 2: return shorty ? new interpreter_parameter(new QString("Tue")) : new interpreter_parameter(new QString("Tuesday"));
    case 3: return shorty ? new interpreter_parameter(new QString("Wed")) : new interpreter_parameter(new QString("Wednesday"));
    case 4: return shorty ? new interpreter_parameter(new QString("Thu")) : new interpreter_parameter(new QString("Thursday"));
    case 5: return shorty ? new interpreter_parameter(new QString("Fri")) : new interpreter_parameter(new QString("Friday"));
    case 6: return shorty ? new interpreter_parameter(new QString("Sat")) : new interpreter_parameter(new QString("Saturday"));
    case 7: return shorty ? new interpreter_parameter(new QString("Sun")) : new interpreter_parameter(new QString("Sunday"));
  }
  error("dayOfWeek <= 0 or >= 8");
  return new interpreter_parameter(&kbNullQString);
}

interpreter_parameter *function::fDAYOFYEAR(t_date d1)
{  
  QDateTime dt1(QDate(d1.nYear, d1.nMonth, d1.nDay), QTime(d1.nHour, d1.nMinute, d1.nSecond));

  return new interpreter_parameter((t_integer) dt1.date().dayOfYear());  
}

interpreter_parameter *function::fDAYSINMONTH(t_date d1)
{  
  QDateTime dt1(QDate(d1.nYear, d1.nMonth, d1.nDay), QTime(d1.nHour, d1.nMinute, d1.nSecond));

  return new interpreter_parameter((t_integer) dt1.date().daysInMonth());  
}

interpreter_parameter *function::fDAYSINYEAR(t_date d1)
{  
  QDateTime dt1(QDate(d1.nYear, d1.nMonth, d1.nDay), QTime(d1.nHour, d1.nMinute, d1.nSecond));

  return new interpreter_parameter((t_integer) dt1.date().daysInYear());  
}

interpreter_parameter *function::fWEEKNUMBER(t_date d1)
{  
  QDateTime dt1(QDate(d1.nYear, d1.nMonth, d1.nDay), QTime(d1.nHour, d1.nMinute, d1.nSecond));

  return new interpreter_parameter((t_integer) dt1.date().weekNumber());  
}

interpreter_parameter *function::fISLEAPYEAR(t_date d1)
{  
  QDateTime dt1(QDate(d1.nYear, d1.nMonth, d1.nDay), QTime(d1.nHour, d1.nMinute, d1.nSecond));

  return new interpreter_parameter((t_integer) QDate::isLeapYear(dt1.date().year()));  
}

interpreter_parameter *function::fISDATEVALID(t_date d1)
{  
  QDate d(d1.nYear, d1.nMonth, d1.nDay);

  return new interpreter_parameter((t_boolean) d.isValid());  
}

interpreter_parameter *function::fISTIMEVALID(t_date d1)
{  
  QTime t(d1.nHour, d1.nMinute, d1.nSecond);

  return new interpreter_parameter((t_boolean) t.isValid());  
}
  
interpreter_parameter *function::fISDATETIMEVALID(t_date d1)
{  
  QDateTime dt1(QDate(d1.nYear, d1.nMonth, d1.nDay), QTime(d1.nHour, d1.nMinute, d1.nSecond));

  return new interpreter_parameter((t_boolean) dt1.isValid());  
}

interpreter_parameter *function::fDIFFDAY(t_date d1, t_date d2)
{  
  QDateTime dt1(QDate(d1.nYear, d1.nMonth, d1.nDay), QTime(d1.nHour, d1.nMinute, d1.nSecond));
  QDateTime dt2(QDate(d2.nYear, d2.nMonth, d2.nDay), QTime(d2.nHour, d2.nMinute, d2.nSecond));

  int n = dt1.daysTo(dt2);

  return new interpreter_parameter((t_integer) n);  
}

interpreter_parameter *function::fDIFFSECONDS(t_date d1, t_date d2)
{  
  QDateTime dt1(QDate(d1.nYear, d1.nMonth, d1.nDay), QTime(d1.nHour, d1.nMinute, d1.nSecond));
  QDateTime dt2(QDate(d2.nYear, d2.nMonth, d2.nDay), QTime(d2.nHour, d2.nMinute, d2.nSecond));

  int n = dt1.daysTo(dt2) * 24 * 60 * 60;

  return new interpreter_parameter((t_integer) n);  
}

interpreter_parameter *function::fDAYNAME(t_integer day, t_qstring Format)
{  
  bool shorty = Format->compare("ShortFormat", Qt::CaseInsensitive) == 0;

  switch(day){
    case 1: return shorty ? new interpreter_parameter(new QString("Mon")) : new interpreter_parameter(new QString("Monday"));
    case 2: return shorty ? new interpreter_parameter(new QString("Tue")) : new interpreter_parameter(new QString("Tuesday"));
    case 3: return shorty ? new interpreter_parameter(new QString("Wed")) : new interpreter_parameter(new QString("Wednesday"));
    case 4: return shorty ? new interpreter_parameter(new QString("Thu")) : new interpreter_parameter(new QString("Thursday"));
    case 5: return shorty ? new interpreter_parameter(new QString("Fri")) : new interpreter_parameter(new QString("Friday"));
    case 6: return shorty ? new interpreter_parameter(new QString("Sat")) : new interpreter_parameter(new QString("Saturday"));
    case 7: return shorty ? new interpreter_parameter(new QString("Sun")) : new interpreter_parameter(new QString("Sunday"));
  }
  error("day <= 0 or >= 8");
  return new interpreter_parameter(&kbNullQString);
}

interpreter_parameter *function::fMONTHNAME(t_integer month, t_qstring shorty_)
{
  bool shorty = shorty_->compare("ShortFormat", Qt::CaseInsensitive) == 0;

  switch(month){
    case 1: return shorty ? new interpreter_parameter(new QString("Jan")) : new interpreter_parameter(new QString("January"));
    case 2: return shorty ? new interpreter_parameter(new QString("Feb")) : new interpreter_parameter(new QString("February"));
    case 3: return shorty ? new interpreter_parameter(new QString("Mar")) : new interpreter_parameter(new QString("March"));
    case 4: return shorty ? new interpreter_parameter(new QString("Apr")) : new interpreter_parameter(new QString("April"));
    case 5: return shorty ? new interpreter_parameter(new QString("May")) : new interpreter_parameter(new QString("May"));
    case 6: return shorty ? new interpreter_parameter(new QString("Jun")) : new interpreter_parameter(new QString("June"));
    case 7: return shorty ? new interpreter_parameter(new QString("Jul")) : new interpreter_parameter(new QString("July"));
    case 8: return shorty ? new interpreter_parameter(new QString("Aug")) : new interpreter_parameter(new QString("August"));
    case 9: return shorty ? new interpreter_parameter(new QString("Sep")) : new interpreter_parameter(new QString("September"));
    case 10: return shorty ? new interpreter_parameter(new QString("Oct")) : new interpreter_parameter(new QString("October"));
    case 11: return shorty ? new interpreter_parameter(new QString("Nov")) : new interpreter_parameter(new QString("November"));
    case 12: return shorty ? new interpreter_parameter(new QString("Dec")) : new interpreter_parameter(new QString("December"));
  }
  error("month <= 0 or >= 13");
  return new interpreter_parameter(&kbNullQString);
}