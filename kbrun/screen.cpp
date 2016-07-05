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


#include "screen.h"
#include "interpreter.h"


#include <QtGui>

extern QString idePath(QString s);



#define getWidth 800
#define getHeight 570
#define getColumn 81
#define getLine 30

#define nFontWidth 10
#define nFontHeight 19

#define getCursorX (nCursorX-1)*nFontWidth
#define getCursorY (nCursorY*nFontHeight)-5

extern interpreter *EXTERN_myInterpreter;

#define PI 3.14159265

QColor colors[256];

QPainter p2;

extern const QPixmap &interpreter_loadPixmap(QString fn);

screen::screen(QWidget *_parent) : QWidget (0)
{

  bInputted = false;
  setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowMinimizeButtonHint);
//  setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);
  bHide = false;

  setFocusPolicy(Qt::StrongFocus);

  for (int i = 0; i < 256; i++){
    switch(i % 16){
      case 0:
        colors[i] = Qt::black;
        break;
      case 1:
        colors[i] = Qt::darkBlue;
        break;
      case 2:
        colors[i] = Qt::darkGreen;
        break;
      case 3:
        colors[i] = Qt::darkCyan;
        break;
      case 4:
        colors[i] = Qt::darkRed;
        break;
      case 5:
        colors[i] = Qt::darkMagenta;
        break;
      case 6:
        colors[i] = QColor(153, 102, 0);
        break;
      case 7:
        colors[i] = Qt::lightGray;
        break;
      case 8:
        colors[i] = Qt::darkGray;
        break;
      case 9:
        colors[i] = Qt::blue;
        break;
      case 10:
        colors[i] = Qt::green;
        break;
      case 11:
        colors[i] = Qt::cyan;
        break;
      case 12:
        colors[i] = Qt::red;
        break;
      case 13:
        colors[i] = Qt::magenta;
        break;
      case 14:
        colors[i] = Qt::yellow;
        break;
      case 15:
        colors[i] = Qt::white;
        break;
    }
   
    if (i / 16 > 0){
      colors[i] = colors[i].dark(100 + 50 * i / 16);
    }    


  }

  nForecolor = 15;
  nBackcolor = 0;

 
  nInput2 = nInput = 0xffff; // no key pressed

  setWindowTitle("Screen");
  setWindowIconText("Screen");

  m2 = QPixmap(getWidth, getHeight);
  m2.fill(Qt::black);


  nForecolor = 15;
  nBackcolor = 0;

  bCursor = false;
  nCursorX = 1;
  nCursorY = 1;
  font = QFont("Courier");
  font.setPixelSize(16);


	setHidden(true);
  setFixedSize(getWidth, getHeight); // WORKAROUND

  nTimerId = startTimer( 500 ); 
  
  bCTRL = false;
  bSHIFT = false;

  bWasActivated = bActivated = false;
  setHidden(true);
  
  QRect r = QApplication::desktop()->screenGeometry(QApplication::desktop()->primaryScreen());
  move((r.width() / 2) - (width() / 2), (r.height() / 2) - (height() / 2));

}


screen::~screen(void)
{  
  killTimer(nTimerId);  
  nTimerId = 0;
  
  captureScreen();
  hide();

 // QMessageBox::information(0,paintingActive() ? "paintingActive()" : "", "2222222222"); 
}

void screen::setWindowIcon2()
{ 
  QPixmap p = interpreter_loadPixmap("VIEW_KONSOLE.png");
  setWindowIcon(QIcon(p));
}

void screen::activate()
{ 
  if (bActivated == false){

    nInput2 = nInput = 0xffff; // no key pressed

    bWasActivated = bActivated = true;
    show();   
    activateWindow();
    if (bWasActivated) clearLastLine();
  } else show();

}

void screen::setActiveW()
{
  show();
  activateWindow();
}

void screen::deactivate()
{
  if (bActivated == true){
//    pressAnyKey();
    bActivated = false;

    bHide = true; hide();
  }

}

void screen::setActivated(bool b)
{
  bActivated = b;
}

void screen::pressAnyKey(bool bPrintText)
{
  if (bPrintText){

    int x = pos();
    int y = csrlin();

    int forecolor = nForecolor;
    int backcolor = nBackcolor;
  
    locate(getLine, 1);
    color(15, 0);
    print("Press ANY KEY to continue...");

    // restore
    locate(y, x);
    nForecolor = forecolor;
    nBackcolor = backcolor;
    
  }

  bActivated = false;
}

bool screen::isActivated()
{
  return bActivated;
}

void screen::paintEvent( QPaintEvent * e)
{

  QPainter p(this);

  p.drawPixmap(0, 0, m2);
  if (bCursor || bInputted){
    p.setPen( colors[nBackcolor] );      
    p.fillRect( QRect(getCursorX, getCursorY + 1, nFontWidth,  3), colors[nForecolor]);
  }

 // show();   
  //p.end(); 
}

void screen::keyPressEvent( QKeyEvent * e)
{
  /*
  int x = pos();
  int y = csrlin();

  switch(e->key()){
    case Qt::Key_Escape:
      hide();
      break;      
    case Qt::Key_Left:
      x--;
      if (x <= 0) x = getColumn;
      locate(y, x);
      break;
    case Qt::Key_Right:
      x++;
      if (x > getColumn) x = 1;
      locate(y, x);
      break;
    case Qt::Key_Up:
      y--;
      if (y <= 0) y = getLine;
      locate(y, x);
      break;
    case Qt::Key_Down:
      y++;
      if (y > getLine) y = 1;
      locate(y, x);
      break;
    case Qt::Key_Return:
      locate(34, 1);
      print("\n");
      break;

    default:
//      close();
      break;     
  }  
  
*/
  nInput = e->nativeVirtualKey();
  nInput2 = e->key();
  sInput = e->text();
  //QMessageBox::information(this, "", sInput);
  if (nInput == 0 && e->key() != 0){ // extended key pressed ?
    int b = e->key();

    if ((b == Qt::Key_Shift) || (b == Qt::Key_Alt) || (b == Qt::Key_Control) || (b == Qt::Key_Meta)) {
      nInput2 = nInput = 0xffff; // no key pressed
    } else {
      nInput = 0;//e->key();
    }
  } else {
    bInputted = true;
  }

  if (!bActivated){    
//    pressAnyKey(false);       
    bHide = true; hide();
    nInput2 = nInput = 0xffff; // no key pressed
  }

  int n = e->key();

  if (n == Qt::Key_Control){
    bCTRL = true;
  }

  if (n == Qt::Key_C && bCTRL){
  //  EXTERN_myInterpreter->stop_interpret();
  }

}
 
void screen::closeEvent ( QCloseEvent * e )
{
//*  my_mainwindow->event_RUN_STOP();
  //pressAnyKey(false);       
  bHide = true; hide();
  e->accept();
}

void screen::keyReleaseEvent ( QKeyEvent * e )
{  
  switch(e->key()){
    case Qt::Key_Control:
      bCTRL = false;
      break;
    case Qt::Key_Shift:
      bSHIFT = false;
      break;
  }
}

void screen::focusInEvent (QFocusEvent *e)
{
  show();
}

void screen::focusOutEvent (QFocusEvent *e)
{
//  pressAnyKey(false);       
}

void screen::hideEvent (QHideEvent *e)
{
  if (bHide){
    bHide = false;
  } else {
//    pressAnyKey(false);       
  }
  QWidget::hideEvent(e);
}

void screen::timerEvent( QTimerEvent * )
{  
  bCursor = !bCursor;
  static QRect r2;
  
  QRect r = QRect(getCursorX, getCursorY + 1, nFontWidth,  3);
  update(r);
  update(r2);
  r2 = r;
  
}

void screen::incCursorX()
{
  nCursorX++;
  if (nCursorX >= getColumn){
    nCursorX = 1;
    incCursorY();
  }
}

void screen::decCursorX()
{
  nCursorX--;
  if (nCursorX < 1){
    nCursorX = getColumn;
    decCursorY();
  }
}

void screen::setCursorX(int n)
{
  nCursorX = n;
}

void screen::setCursorY(int n)
{
  nCursorY = n;
}

void screen::decCursorY()
{
  nCursorY--;
  if (nCursorY < 1){
    nCursorX = 1;
    nCursorY = 1;
  }
}

void screen::incCursorY()
{
  nCursorY++;
  if (nCursorY > getLine){

    int h = getHeight - nFontHeight;    


    p2.drawPixmap(0, 0, m2, 0, nFontHeight, getWidth, h);

    p2.fillRect(QRect(0, h, getWidth, nFontHeight), colors[nBackcolor]);
    //p.end(); 

    nCursorY = getLine;
  }
}

void screen::clearLastLine()
{
  int y = getHeight - (nFontHeight + 0);
  int w = getWidth;

  QPainter p( &m2 );

  QRect r = QRect(0, y, w, nFontHeight + 0);
  p.fillRect(r, colors[nBackcolor]);
  //p.end();   
  update(r);
}

int screen::abs(int n)
{
  if (n < 0) return n *= -1;
  return n;
}

/*
 step, stil
*/
void screen::line(bool step, int x1, int y1, 
                bool step2, bool expression, int x2, int y2, 
                bool bColor, int color, bool b, bool bf, bool bStyle, int style)
{
  activate();

  QPainter p2( &m2 );

  p2.setPen( colors[color] );      
  if (bStyle){
    p2.setPen( QPen(colors[color]) );      
  }
  if (b){     
    p2.drawRect(x1, y1, abs(x2 - x1), abs(y2 - y1)); 
  } else if (bf){
    QPixmap k( abs(x2 - x1), abs(y2 - y1));
    k.fill(colors[color]);    
    p2.drawPixmap(x1, y1, k); 
  } else {
    p2.drawLine(x1, y1, x2, y2); 
  }
  //p2.end();  

  update();
}

/*
 step, start, end, aspect
*/
void screen::circle(bool step, int x, int y, int radius, int color, int start, int end, int aspect)
{
  activate();

  QPainter p( &m2 );

  //p.begin( &m );   

  if (start == -1) start = 0 / (PI / 180);
  if (end == -1) end = 360 / (PI / 180);
  if (aspect == -1) aspect = 1;

  if (color == -1){
    p.setPen( colors[nForecolor] );   
  } else {
    p.setPen( colors[color] );   
  }

  p.drawArc ( x - radius, y - radius, radius * 2, radius * 2, 0 * 16, 360 * 16);
  
  
  update();
}

/*
*/
void screen::color(int forecolor, int backcolor)
{
  activate();

  if (forecolor < 256 && forecolor != -1) nForecolor = forecolor;
  if (backcolor < 256 && backcolor != -1) nBackcolor = backcolor;
}

/*
*/
void screen::paint(bool step, int x, int y, int color, char *pattern, int bordercolor, int backcolor)
{
}

/*
 no
*/
void screen::cls(int no)
{
  activate();

  QPainter p( &m2 );

  QPixmap k(QApplication::desktop()->width(), QApplication::desktop()->height());
  k.fill( colors[nBackcolor] );    
  

  p.drawPixmap(0, 0, k); 
  
  locate(1, 1);
  update();
}

/*

*/
void screen::viewprint(int no)
{
  activate();

}

/*

*/
void screen::viewscreen(int no)
{
  activate();

}

/*
 
*/
void screen::window(int no)
{
  activate();

}

/*
*/
int screen::csrlin()
{
  activate();

  return nCursorY;
}

/*
 
*/
void screen::pmap(int no)
{
  activate();

}

/*
 
*/
void screen::point(int no)
{
  activate();

}

/*
 
*/
void screen::beep()
{
  //activate();
  QApplication::beep();
}

/*
 
*/
void screen::draw(int no)
{
  activate();

}

/*
 
*/
void screen::get(int no)
{
  activate();

}

/*
 
*/
void screen::put(int no)
{
  activate();

}

/*

*/
void screen::key(int no)
{
  activate();

}

char *screen::inkey(int *nKeyPressed)
{
  //qApp->processEvents();
  activate();

  static char ac[1024];
/*
  if (nInput == 0){
    nInput = nInput;
  }*/

  // no key pressed
  if (nInput == 0xffff){ 
    *nKeyPressed = 1;

    ac[0] = '\0';
    return ac;
  }

  if (nInput == 0){ 
    *nKeyPressed = 2;

	  ac[0] = ' ';
    ac[1] = '\0';  

    
    return ac;
  }

  *nKeyPressed = 3;

	ac[0] = sInput.at(0).toAscii();
  ac[1] = '\0';  

  nInput = 0xffff; // no key pressed

  return ac;
}


char *screen::input()
{
  activate();
  
  static char ac[1024];

  int i = 0;
  while (nInput2 != Qt::Key_Enter && nInput2 != Qt::Key_Return){
    if (nInput2 != 0xffff){ // no key pressed = 0xffff

 // QMessageBox::information(this, "", QString("%1").arg(nInput2));

      if (nInput2 == Qt::Key_Backspace){
        if (i > 0){ // backspace
         i--;

         decCursorX();
         static QString ss = QString(QChar(' '));
         print(ss);
         decCursorX();
        }

        nInput2 = 0xffff; // no key pressed
        bInputted = false;
      } else if (nInput2 >= 32){

       QChar *c = sInput.data();
       ac[i] = c->toAscii();       

       print(sInput);
       nInput2 = 0xffff; // no key pressed
       bInputted = false;
       i++;
       if (i > 1023) break;
      
      } else { // ignore special keys
       nInput2 = 0xffff; // no key pressed
       bInputted = false;
      }
    }
    update();
    qApp->processEvents(QEventLoop::AllEvents, 100);
  };  

  setCursorX(1);
  incCursorY();

  nInput2 = 0xffff; // no key pressed
  bInputted = false;

	ac[i] = '\0';  

  return ac;  
}

/*
*/
/*
void screen::print(char s)
{
  static char ac[2];
  //char *ac = new char[2]; 

  ac[0] = s;
  ac[1] = '\0';
  
  print(QString(ac));
}*/

void screen::print(const char *s)
{  
  
  
  static QString ss; ss = s;
  print(ss);
  
}


void screen::print(const QString &j)
{
  activate();

  p2.begin(&m2);

  p2.setPen( colors[nForecolor] );   
  p2.setBackgroundMode(Qt::OpaqueMode);
  p2.setBackground ( colors[nBackcolor] );
  p2.setFont(font); 


  int i = 0;
  int i2 = 0;
  bool b = false;
  QString k;

  do {

    i2 = j.indexOf("\n", i);
    if (i2 != -1){
      k = j.mid(i, i2 - i);
      i = i2;
      b = true;
    } else {
      k = j.mid(i);
      if (k == 0) break;
      b = false;
    }

  
   do {

      int n = k.length() + nCursorX;
      if (n > getColumn){
        n = getColumn - nCursorX;
       // p.drawText(getCursorX, getCursorY, k.left(n));

        p2.drawText(getCursorX, getCursorY, k.left(n));

        k = k.mid(n);

        nCursorX = 1;
        incCursorY();

      } else {
        

        p2.drawText(getCursorX, getCursorY, k);

        if (b){
          i++;
          nCursorX = 1;
          incCursorY();
        } else {
          nCursorX += k.length();
        }

        break;
      }

   } while (k.length());
 
 
} while (b);

  update();

  p2.end();

}


/*
 step
*/
void screen::preset(bool step, int x, int y, int color)
{
  activate();

  QPainter p( this );

//  p.begin( &m );   
  if (color == -1){
    p.setPen( colors[nBackcolor] );      
  } else {
    p.setPen( colors[color] );      
  }

  p.drawPoint(x, y); 

  update();
}

/*
 step
*/
void screen::pset(bool step, int x, int y, bool bColor, int color)
{
  activate();

  QPainter p( &m2 );

//  p.begin( &m );   
  if (bColor){
    p.setPen( colors[color] );      
  } else {
    p.setPen( colors[nForecolor] );      
  }

  p.drawPoint(x, y); 

  //p.end();  
  update();
}

/*
*/
int screen::pos()
{
  activate();

  return nCursorX;
}

/*
*/
void screen::locate(int y, int x)
{
  activate();

  if (x > getColumn || y > getLine) return;

  if (x != -1) nCursorX = x;
  if (y != -1) nCursorY = y;
  //update();
}

/*
 
*/
void screen::palette(int no)
{
  activate();
}

/*
 
*/
void screen::sound(int no)
{
}

/*
 
*/
void screen::play(int no)
{
}

/*
 
*/
void screen::view(int no)
{
  activate();
}

void screen::test1()
{
/*
  line(false, 110, 40, false, 320, 200, 15, false, 0, false, false, 0);
  line(false, 110, 40, 320, 200, 15, true, false, 0);
  line(false, 110, 40, 32, 20, 15, false, true, 0);*/
  circle(false, 44, 66, 8, 8, 6, 6, 4);
  //cls(0);
  color(15, 1);
  locate(1, 1);
  print("1gy567890 1234567890 123456g890 1234567u90 1234567u90 1234567u90 1234567u90 1234567u90");

  char buffer[1024];
  sprintf(buffer, "\n\n\n     hi");
  print(buffer);
  int n = pos();
  n = csrlin();

  locate(5, 11);
  print("gut");

  locate(2, 1);
  print(".2\n");
  print(".3\n");
  print(".4\n");
  print(".5\n");
  print(".6\n");
  print(".7\n");
  print(".8\n");
  print(".9\n");
  //print("\n");
  print(".0\n");
  print(".1\n");
  print(".2\n");
  print(".3\n");
  print(".4\n");
  print(".5\n");
  print(".6\n");
  print(".7\n");
  print(".8\n");
  print(".9\n");
  
  //print("\n");
  print(".0\n");
  print(".1\n");
  print(".2\n");
  print(".3\n");
  print(".4\n");
  print(".5\n");
  print(".6\n");
  print(".7\n");
  print(".8\n");
  print(".9\n");
  print(".0\n");
  /*print("\n");
  print(".0\n");
  print(".1\n");
  print(".2\n");
  print(".3\n");
  print(".4\n");
  print(".5\n");
  print(".6\n");
  print(".7\n");
  print(".8\n");
  print(".9\n");
  
*/

  locate(2, 1);
  print("WyW");
  locate(2, 2);
  
  /*
  for (int y = 110; y < 200; y++){
    for (int x = 110; x < 200; x++){
      line(false, x, y, 320 - x, 200 + y, x+y , false, false, 0);
    }
  }
  */
  /*
  locate(34, 1);
  print("!!!\n");
  locate(35, 1);
  print("gW!");
*/
}


void screen::test2()
{
  color(15, 1);

  locate(1, 1);
  
  input();
  for (int i = 0; i < 35; i++){

   // if (i >= 14) 

    QString s = "1234567890 1234567890 123456g890 1234567u90 1234567890 1234567890 1234567u9!";

    QString k;
    k.sprintf("%d\n", i);

    print((s + k));
  }


  //line(false, 110, 70, 190, 120, 15, false, true, 0);
  //line(false, 0, 0, 320, 200, 3, false, false, 0xff00);

  circle(false, 320, 100, 200, 15, -1, -1, -1);

 // for (int i = 0; i < 256; i++){
 //   pset(false, 1, i, i);
    //pset(false, 2, i, 15);
//    line(false, 110, i, 320, i, i, false, false, 0);
 // }
  //line(false, 110, 40, 320, 200, 15, true, false, 0);
  //line(false, 110, 40, 32, 20, 15, false, true, 0);
  //circle(false, 44, 66, 8, 8, 6, 6, 4);
  //cls(0);
//  pressAnyKey();
  
}


void screen::aboutToQuit()
{
  
  if (bActivated){
  // qApp->processEvents(); // do last paint operations
    
    m2.save(idePath("screen.png"));
  }
}

void screen::captureScreen()
{
  //QMessageBox::information(this, "julie", "");

  if (bActivated){
    qApp->processEvents(); // do last paint operations    
    m2.save(idePath("screen.png"));    
  }
 
}

void screen::printScreen(bool bDialog)
{
  static QPrinter printer;
  //printer.setOrientation(QPrinter::Landscape);

  if (bDialog){
    QPrintDialog *dialog = new QPrintDialog(&printer, this);
    dialog->setWindowTitle(tr("Print Document"));
    if (dialog->exec() != QDialog::Accepted) return;
  }

  QPainter painter;
  painter.begin(&printer);

  painter.drawPixmap(0, 0, m2);

  painter.end();
}