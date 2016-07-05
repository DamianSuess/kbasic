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

#include "_typedef.h"

#include "_inputtip.h"
#include "_inputtip_parser.h"

#include "_mainwindow.h"
#include "_sourcecodeeditor.h"
#include "_sourcecodeeditor_editor.h"

extern _mainwindow *EXTERN_my_mainwindow;
extern const QIcon &kbasicIcon(QString s);

_inputtip::_inputtip(_sourcecodeeditor_editor *_my_sourcecodeeditor_editor, bool _bDot, bool bBrace, bool _bAs, QString sSubSyntax, QString _sSubDesc, QStringList &_ln, QStringList &_lt, QStringList &_lm) : QListWidget (_my_sourcecodeeditor_editor/*(QWidget *) _my_sourcecodeeditor_editor->my_sourcecodeeditor->my_mainwindow*/)
{
  setAttribute(Qt::WA_DeleteOnClose);

  ln = _ln;
  lt = _lt;
  lm = _lm;

  bDot = _bDot;
  bAs = _bAs;

  my_sourcecodeeditor_editor = _my_sourcecodeeditor_editor;

//  setHScrollBarMode(QScrollView::AlwaysOff);  
  //setSelectionMode(QListBox::Single);
  //setFont(QFont("Arial", 10));
  
#ifdef MAC
  setMaximumWidth(180);
#else
  setMaximumWidth(150);
#endif
  /*
  setFrameShape(QFrame::StyledPanel);
  setFrameShadow(QFrame::Raised);
  setLineWidth(2);*/
  
/*
  QColor c(0, 0, 0, 188);
  QPalette p = palette();
  p.setBrush(QPalette::Window, c);  
  p.setBrush(QPalette::Base, c);  
  p.setBrush(QPalette::Button, c);    
  p.setBrush(QPalette::Text, QColor(255, 255, 255));  
  p.setBrush(QPalette::Highlight, QColor(255, 255, 255));  
  p.setBrush(QPalette::HighlightedText, QColor(0, 0, 0));  
  setPalette(p);
*/
  

  
  label = 0;

  sInputedText = "";
  connect(this, SIGNAL(itemActivated(QListWidgetItem *)), this, SLOT(itemActivated(QListWidgetItem *)));
  connect(this, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(itemActivated(QListWidgetItem *)));

  if (bDot){
    updateDotList();

  } else if (bBrace){
    QWidget *w = 
    label = new QLabel(sSub, my_sourcecodeeditor_editor->my_sourcecodeeditor->isFullscreen() ? (QWidget *) my_sourcecodeeditor_editor : (QWidget *) EXTERN_my_mainwindow);
    label->setAutoFillBackground(true);

    sSub = sSubSyntax;//"(start AS INTEGER, src AS STRING)";
    sSubDesc = _sSubDesc;
    if (sSub.isEmpty()){
      updateDotMethodList();
      sSub = item(0) ? item(0)->text() : "";
    }
    
    setLabel("", 0, true);
    label->setMargin(0);
    label->setIndent(4);    
    QPalette p = label->palette();
    p.setColor(QPalette::Window, QColor(0xFFFF9F));
    label->setPalette(p);
//    label->setBackgroundColor(QColor(0xFFFF9F));
    //label->setMinimumWidth(400);
    //label->setMaximumHeight(100);

    label->setFrameShape(QFrame::Box);
    
    //label->setFont(QFont("Arial", 8));

    //sSub = sSubSyntax;

  } else if (bAs){
    updateAsList();

   // clearSelection();
  } else if (ln.size()){
    updateControlList();

  } else if (lm.size()){
    setMaximumWidth(800);
    updateControlEventsList();    
  }
 
  
  //setSelected(item(0), true);  
  //setSelected(item(0), true);  
  
  bDoNotLooseFocus = false;
}

_inputtip::~_inputtip()
{
  delete label;
}

void _inputtip::setLabel(QString sLine, int nCursorPos, bool bStart)
{
  bool b = bStart;
  QString s = sSub;
  int nStart = 0;
  int nEnd = 0;

  int nComma = 0;
  int nParamPos = 0;
  int h = 1;

  while (h > 0){
    h = sSub.indexOf(",", h + 1);
    if (h > 0) nComma++;
  }  
  
  h = 1;

  while (h > 0){
    h = sLine.indexOf(",", h + 1);
    if (h > 0) nParamPos++;
  }

  if (nParamPos > nComma) nParamPos = nComma;

  if (nParamPos == 0){
    nStart = s.indexOf("(");
    nEnd = s.indexOf(",");
    if (nEnd == -1) nEnd = s.indexOf(")");   
  } else {
    nStart = s.indexOf("(");
    for (int i = 0; i < nParamPos; i++){
      int n = s.indexOf(",", nStart + 1);
      if (n == -1) n = s.indexOf(")");   
      nStart = n;      
    }
    nEnd = s.indexOf(",", nStart + 1);
    if (nEnd == -1) nEnd = s.indexOf(")", nStart);   
  }

  if (nCursorPos > 0){
    s.insert(nEnd, "</b></font>");
    s.insert(nStart + 1, "<font color=\"#111183\"><b>");
  }
  s = s + "<br><i> <font color=\"blue\">" + sSubDesc + "</i></font>";
  label->setText(s);
  label->adjustSize();
  label->show();
}

void _inputtip::show()
{  
  if (label != 0){
    label->move(x(), y());
    label->show();
    label->adjustSize();
  } else {
    
    if (bDot){
      updateDotList();
    } else if (bAs){
      updateAsList();
    } else if (ln.size()){
      updateControlList();
    } else if (lm.size()){
      updateControlEventsList();
    }
    QListWidget::show();
  }
  if (lm.size()){
  } else {
    adjustSize();
  }
}

bool _inputtip::isUsedAsLabel()
{
  return label != 0;
}

void _inputtip::focusOutEvent(QFocusEvent *e)
{  
  if (bDoNotLooseFocus == false){
    my_sourcecodeeditor_editor->setFocus();
    if (label != 0){
      label->hide();
      delete label;
      label = 0;     
    } 
    if (my_sourcecodeeditor_editor->my_inputtip2 == 0){
      close(); 
      if (lm.size()){
        my_sourcecodeeditor_editor->my_inputtip2 = 0;    
      } else {
        my_sourcecodeeditor_editor->my_inputtip = 0;    
        if (my_sourcecodeeditor_editor->my_inputtip2){
          my_sourcecodeeditor_editor->my_inputtip2->close(); 
          my_sourcecodeeditor_editor->my_inputtip2 = 0; 
        }
      }
    }
  } else {
    bDoNotLooseFocus = false;
  }  
}

void _inputtip::itemActivated(QListWidgetItem *item)
{
  bDoNotLooseFocus = false;
  if (ln.size()){
    QString s = currentText();
    QListWidgetItem *l = currentItem();
    QVariant v = l->data(Qt::UserRole);

    if (v == "Form" || v == "Report" || v == "MenuBar" || v == "ToolBar"){
      my_sourcecodeeditor_editor->my_sourcecodeeditor->showEvents2(v.toString());
    } else {   
      my_sourcecodeeditor_editor->my_sourcecodeeditor->showEvents2(s);
    }
  } else {
    QString s = "";
    QString k = "";

    if (currentText().isEmpty()) return;

    if (lm.size()){
      k = my_sourcecodeeditor_editor->my_inputtip->currentText() + "_" + currentText();
      if (my_sourcecodeeditor_editor->my_sourcecodeeditor->hasSub(k)){
      } else {
        if (my_sourcecodeeditor_editor->my_inputtip) s = "\n\nPrivate Sub " + k + "\n  \nEnd Sub\n";
        my_sourcecodeeditor_editor->my_sourcecodeeditor->gotoBeforeEndClass();
      }
    } else {
      s = currentText();
    }
    
    if (s.startsWith(sInputedText, Qt::CaseInsensitive) && !s.isEmpty()){
      my_sourcecodeeditor_editor->performInsertText(s.mid(sInputedText.length()));
    }
    my_sourcecodeeditor_editor->setFocus();

    if (!k.isEmpty()){
      if (my_sourcecodeeditor_editor->my_sourcecodeeditor->hasSub(k)){
      }
    }
    close(); 
    if (lm.size()){
      my_sourcecodeeditor_editor->my_inputtip2 = 0;    
      my_sourcecodeeditor_editor->my_inputtip->close(); 
      my_sourcecodeeditor_editor->my_inputtip = 0;    
    } else {
      my_sourcecodeeditor_editor->my_inputtip = 0;  
      if (my_sourcecodeeditor_editor->my_inputtip2){
        my_sourcecodeeditor_editor->my_inputtip2->close(); 
        my_sourcecodeeditor_editor->my_inputtip2 = 0; 
      }
    }    
  }
}

QString _inputtip::currentText()
{
  QListWidgetItem *i = item(currentRow());
  return i ? i->text() : "";
}

QListWidgetItem *_inputtip::itemWithText(QString s)
{

  for (int i = 0; i < count(); i++){
    QListWidgetItem *l = item(i);
    if (l->text().startsWith(s, Qt::CaseInsensitive)){
      return l;
    }
  }

  return 0;
}

void _inputtip::keyPressEvent(QKeyEvent *e)
{

  int n  = e->key();

  if (n == Qt::Key_Return || n == Qt::Key_Enter){        
    bDoNotLooseFocus = false;
    QString s = currentText();
    if (s.startsWith(sInputedText, Qt::CaseInsensitive)){
      my_sourcecodeeditor_editor->performInsertText(s.mid(sInputedText.length()));
    }
    my_sourcecodeeditor_editor->setFocus();
    close(); 
    if (lm.size()){
      my_sourcecodeeditor_editor->my_inputtip2 = 0;    
    } else {
      my_sourcecodeeditor_editor->my_inputtip = 0;    
      if (my_sourcecodeeditor_editor->my_inputtip2){
        my_sourcecodeeditor_editor->my_inputtip2->close(); 
        my_sourcecodeeditor_editor->my_inputtip2 = 0; 
      }
    }

  } else if (n == Qt::Key_Escape){
    bDoNotLooseFocus = false;
    my_sourcecodeeditor_editor->setFocus();
    close(); 
    if (lm.size()){
      my_sourcecodeeditor_editor->my_inputtip2 = 0;    
    } else {
      my_sourcecodeeditor_editor->my_inputtip = 0;    
      if (my_sourcecodeeditor_editor->my_inputtip2){
        my_sourcecodeeditor_editor->my_inputtip2->close(); 
        my_sourcecodeeditor_editor->my_inputtip2 = 0; 
      }
    }

  } else if (n == Qt::Key_Backspace){  
    int k = sInputedText.length() - 1;

    e->ignore();
    if (k == -1){
      
      close(); my_sourcecodeeditor_editor->my_inputtip = 0;    
      if (my_sourcecodeeditor_editor->my_inputtip2){
        my_sourcecodeeditor_editor->my_inputtip2->close(); 
        my_sourcecodeeditor_editor->my_inputtip2 = 0; 
      }
      my_sourcecodeeditor_editor->setFocus();
    } else {
      
      sInputedText = sInputedText.left(k);

      QListWidgetItem *k = itemWithText(sInputedText);
      if (k == 0){
        clearSelection();
      } else {
        setCurrentItem(k);
      }

    }
  } else {
    QString s = e->text();
    if (!s.isNull() && s.length() > 0){
      e->ignore();
      bDoNotLooseFocus = true;

      sInputedText.append(s);

      QListWidgetItem *k = itemWithText(sInputedText);
      if (k == 0){
        clearSelection();
      } else {
        setCurrentItem(k);
      }
    } else {

      if (n == Qt::Key_Up && currentRow() == 0){}
      else if (n == Qt::Key_Down && currentRow() == count() - 1){}
      else { 

        QListWidget::keyPressEvent(e);
      }
    }
  }

}

void _inputtip::updateAsList()
{
  clear();
  setSortingEnabled(true);

  QListWidgetItem *it;
  QIcon i;
  i = kbasicIcon(kbasicPath("ide/Scalar.png"));
  //addItem("");
  it = new QListWidgetItem(i, "Boolean"); addItem(it); it->setForeground(QBrush(Qt::darkGray));
  //addItem("");
  it = new QListWidgetItem(i, "String"); addItem(it); it->setForeground(QBrush(Qt::darkGray));
  it = new QListWidgetItem(i, "CString"); addItem(it); it->setForeground(QBrush(Qt::darkGray));
  //addItem("");
  it = new QListWidgetItem(i, "Byte"); addItem(it); it->setForeground(QBrush(Qt::darkGray));
  it = new QListWidgetItem(i, "Short"); addItem(it); it->setForeground(QBrush(Qt::darkGray));
  it = new QListWidgetItem(i, "Integer"); addItem(it); it->setForeground(QBrush(Qt::darkGray));
  it = new QListWidgetItem(i, "Long"); addItem(it); it->setForeground(QBrush(Qt::darkGray));
  //addItem("");
  it = new QListWidgetItem(i, "Single"); addItem(it); it->setForeground(QBrush(Qt::darkGray));
  it = new QListWidgetItem(i, "Double"); addItem(it); it->setForeground(QBrush(Qt::darkGray));
  //addItem("");
  it = new QListWidgetItem(i, "Variant"); addItem(it); it->setForeground(QBrush(Qt::darkGray));
  it = new QListWidgetItem(i, "Date"); addItem(it); it->setForeground(QBrush(Qt::darkGray));
  it = new QListWidgetItem(i, "Currency"); addItem(it); it->setForeground(QBrush(Qt::darkGray));

  it = new QListWidgetItem(i, "Decimal"); addItem(it); it->setForeground(QBrush(Qt::darkGray));
  it = new QListWidgetItem(i, "DateTime"); addItem(it); it->setForeground(QBrush(Qt::darkGray));

  it = new QListWidgetItem(i, "Strings"); addItem(it); it->setForeground(QBrush(Qt::darkGray));
  it = new QListWidgetItem(i, "Dictionary"); addItem(it); it->setForeground(QBrush(Qt::darkGray));
  it = new QListWidgetItem(i, "Array"); addItem(it); it->setForeground(QBrush(Qt::darkGray));
  it = new QListWidgetItem(i, "Bits"); addItem(it); it->setForeground(QBrush(Qt::darkGray));

  //addItem("");

  i = kbasicIcon(kbasicPath("ide/Object.png"));
  it = new QListWidgetItem(i, "Object"); addItem(it); it->setForeground(QBrush(Qt::darkGray));
  
  addItem(new QListWidgetItem(i, "Form"));
  addItem(new QListWidgetItem(i, "CommandButton"));
  addItem(new QListWidgetItem(i, "ToolButton"));
  addItem(new QListWidgetItem(i, "ImageButton"));
  addItem(new QListWidgetItem(i, "Label"));
  addItem(new QListWidgetItem(i, "CheckBox"));
  addItem(new QListWidgetItem(i, "RadioButton"));
  addItem(new QListWidgetItem(i, "TextBox"));
  addItem(new QListWidgetItem(i, "Frame"));
  addItem(new QListWidgetItem(i, "ComboBox"));
  addItem(new QListWidgetItem(i, "ListBox"));
  addItem(new QListWidgetItem(i, "DateBox"));
  addItem(new QListWidgetItem(i, "TimeBox"));
  addItem(new QListWidgetItem(i, "DateTimeBox"));
  addItem(new QListWidgetItem(i, "Timer"));
  addItem(new QListWidgetItem(i, "Sound"));
  addItem(new QListWidgetItem(i, "MovieBox"));
  addItem(new QListWidgetItem(i, "TabView"));
  addItem(new QListWidgetItem(i, "ImageBox"));
  addItem(new QListWidgetItem(i, "TreeView"));
  addItem(new QListWidgetItem(i, "ListView"));
  addItem(new QListWidgetItem(i, "Box"));
  addItem(new QListWidgetItem(i, "ProgressBar"));
  addItem(new QListWidgetItem(i, "RichTextBox"));
  addItem(new QListWidgetItem(i, "WebView"));
  addItem(new QListWidgetItem(i, "HtmlView"));
  addItem(new QListWidgetItem(i, "MenuBarItem"));
  addItem(new QListWidgetItem(i, "ToolBarItem"));
  addItem(new QListWidgetItem(i, "SerialPort"));
  addItem(new QListWidgetItem(i, "FormView"));
  addItem(new QListWidgetItem(i, "Line"));
  addItem(new QListWidgetItem(i, "ResizeBox"));
  addItem(new QListWidgetItem(i, "CommandLinkButton"));
  addItem(new QListWidgetItem(i, "SvgBox"));
  addItem(new QListWidgetItem(i, "ToolBarView"));
  addItem(new QListWidgetItem(i, "FormsView"));
  addItem(new QListWidgetItem(i, "Slider"));
  addItem(new QListWidgetItem(i, "SpinBox"));
  addItem(new QListWidgetItem(i, "ScrollBar"));
  addItem(new QListWidgetItem(i, "UdpSocket"));


  // CONTROL

  //addItem(new QListWidgetItem(i, "VBox"));
  //addItem(new QListWidgetItem(i, "HBox"));
  //addItem(new QListWidgetItem(i, "VHBox"));
  //addItem(new QListWidgetItem(i, "HSplit"));
  //addItem(new QListWidgetItem(i, "VSplit"));
  //addItem(new QListWidgetItem(i, "Strings"));
  //addItem(new QListWidgetItem(i, "ByteArray"));
  //addItem(new QListWidgetItem(i, "BitArray"));
  //addItem(new QListWidgetItem(i, "Collection"));
  //addItem(new QListWidgetItem(i, "Number"));
  //addItem(new QListWidgetItem(i, "Dir"));
  //addItem(new QListWidgetItem(i, "File"));
  //addItem(new QListWidgetItem(i, "Pixmap"));
  //addItem(new QListWidgetItem(i, "Sound"));
  //addItem(new QListWidgetItem(i, "Font"));
  //addItem(new QListWidgetItem(i, "DateTime"));
  //it = new QListWidgetItem(i, "Query"); addItem(it); it->setForeground(QBrush(Qt::blue));
  //it = new QListWidgetItem(i, "Record"); addItem(it); it->setForeground(QBrush(Qt::blue));
  //addItem(new QListWidgetItem(i, "Process"));


  //addItem(new QListWidgetItem(i, "Color"));


  QList<_inputtip_info>l = EXTERN_my_mainwindow->ci_getAsForFile(my_sourcecodeeditor_editor->my_sourcecodeeditor->getFilename(), my_sourcecodeeditor_editor->my_sourcecodeeditor->getScope());
  foreach (_inputtip_info v, l)
  { 
    QString ss = "";
    switch(v.type){
      case __sub: ss = "ide/Sub.png"; break;
      case __function: ss = "ide/Function.png"; break;
      case __constructor: ss = "ide/Constructor.png"; break;
      case __property2: ss = "ide/Property.png"; break;
      case __enum: ss = "ide/Enum.png"; break;
      case __type: ss = "ide/Type.png"; break;
      case __class: ss = "ide/Class.png"; break;
      case __module: ss = "ide/Module.png"; break;
      case __constant: ss = "ide/Constant.png"; break;
      case __variable: ss = "ide/Variable.png"; break;
      case __event2: continue; break;
    }
    QListWidgetItem *it;
    if (ss.isEmpty()){
      it = new QListWidgetItem(v.name);
    } else {
      it = new QListWidgetItem(kbasicIcon(kbasicPath(ss)), v.name);
    }
    addItem(it);

    if (v.scope == "Control"){
      it->setForeground(QBrush(Qt::darkGray));
    } else if (v.scope == "SQL"){
      it->setForeground(QBrush(Qt::darkCyan));
    } else {
      QFont f = it->font();
      it->setForeground(QBrush(Qt::black));
      f.setBold(true);      
      it->setFont(f);
    }
  }
  
}

void _inputtip::updateDotList()
{
  clear();
  setSortingEnabled(true);
 
  QList<_inputtip_info>l = EXTERN_my_mainwindow->ci_getDotForFile(my_sourcecodeeditor_editor->my_sourcecodeeditor->getFilename(), my_sourcecodeeditor_editor->my_sourcecodeeditor->getScope(), my_sourcecodeeditor_editor->my_sourcecodeeditor->getScope2(), my_sourcecodeeditor_editor->my_sourcecodeeditor->getDot());
  foreach (_inputtip_info v, l)
  { 
    QString ss = "";
    switch(v.type){
      case __sub: ss = "ide/Sub.png"; break;
      case __function: ss = "ide/Function.png"; break;
      case __constructor: ss = "ide/Constructor.png"; break;
      case __property2: ss = "ide/Property.png"; break;
      case __enum: ss = "ide/Enum.png"; break;
      case __type: ss = "ide/Type.png"; break;
      case __class: ss = "ide/Class.png"; break;
      case __module: ss = "ide/Module.png"; break;
      case __constant: ss = "ide/Constant.png"; break;
      case __variable: ss = "ide/Variable.png"; break;
      case __event2: continue; break;
    }
    QListWidgetItem *it;
    if (ss.isEmpty()){
      it = new QListWidgetItem(v.name);      
    } else {
      it = new QListWidgetItem(kbasicIcon(kbasicPath(ss)), v.name);
    }
    addItem(it);

    if (v.scope == "Control"){     
      it->setForeground(QBrush(Qt::darkGray));
    } else if (v.scope == "SQL"){      
      it->setForeground(QBrush(Qt::darkCyan));
    } else if (v.scope2 != "Framework"){
      QFont f = it->font();
      it->setForeground(QBrush(Qt::black));
      f.setBold(true);      
      it->setFont(f);
    }
  }
  
}

void _inputtip::updateDotMethodList()
{
  clear();
  setSortingEnabled(true);

  QString ss = my_sourcecodeeditor_editor->getLastIdentifierBeforeBrace();
  ss = ss.simplified();

  QList<_inputtip_info>l = EXTERN_my_mainwindow->ci_getDotMethodForFile(my_sourcecodeeditor_editor->my_sourcecodeeditor->getFilename(), my_sourcecodeeditor_editor->my_sourcecodeeditor->getScope(), my_sourcecodeeditor_editor->my_sourcecodeeditor->getScope2(), ss);
  foreach (_inputtip_info v, l)
  { 
    QString ss = "";
    switch(v.type){
      case __sub: ss = "ide/Sub.png"; break;
      case __function: ss = "ide/Function.png"; break;
      case __constructor: ss = "ide/Constructor.png"; break;
      case __property2: ss = "ide/Property.png"; break;
      case __enum: ss = "ide/Enum.png"; break;
      case __type: ss = "ide/Type.png"; break;
      case __class: ss = "ide/Class.png"; break;
      case __module: ss = "ide/Module.png"; break;
      case __constant: ss = "ide/Constant.png"; break;
      case __variable: ss = "ide/Variable.png"; break;
      case __event2: continue; break;
    }
    if (ss.isEmpty()){
      addItem(v.name);
    } else {
      addItem(new QListWidgetItem(kbasicIcon(kbasicPath(ss)), v.name));
    }
  }
  
}

void _inputtip::updateControlList()
{
  clear();
  setSortingEnabled(true);  

  int nForm = -1;

  for (int z = 0; z < ln.size(); z++){
    QString s = lt.at(z);

    if (s.compare("Form", Qt::CaseInsensitive) == 0){
      nForm = z;
    } else {

  #ifdef MAC
    QString ss = "ide/controls/mac/" + s.toLower() + ".png";    // HIDE
  #else
  #ifdef WINDOWS 
    QString ss = "ide/controls/windows/" + s.toLower() + ".png";    // HIDE
  #else
    QString ss = "ide/controls/linux/" + s.toLower() + ".png";   
  #endif
  #endif

      QListWidgetItem *it = new QListWidgetItem(kbasicIcon(kbasicPath(ss)), ln.at(z));
      it->setData(Qt::UserRole, s);
      addItem(it);
    }
    
  }

  if (ln.size() && nForm >= 0){
    setSortingEnabled(false);  

    QString s = "Form";
    
  #ifdef MAC
    QString ss = "ide/controls/mac/" + s.toLower() + ".png";    // HIDE
  #else
  #ifdef WINDOWS
    QString ss = "ide/controls/windows/" + s.toLower() + ".png";    // HIDE
  #else
    QString ss = "ide/controls/linux/" + s.toLower() + ".png";   
  #endif
  #endif

    insertItem(0, "");

    QListWidgetItem *it = new QListWidgetItem(kbasicIcon(kbasicPath(ss)), ln.at(nForm));
    it->setData(Qt::UserRole, s);
    insertItem(0, it);
  }

}
  


void _inputtip::updateControlEventsList()
{
  clear();
  setSortingEnabled(true);

  QString sName = lm.at(0);
  QString sControlType = lm.at(1);

  QListWidgetItem *onopen = 0;

  QList<_inputtip_info>l = EXTERN_my_mainwindow->ci_getEventsForClass(sControlType);
  foreach (_inputtip_info v, l)
  { 
    QString ss = "";
    switch(v.type){
      case __event2: ss = "ide/Event.png"; break;
      default: continue; break;
    }
    QListWidgetItem *it;
    if (ss.isEmpty()){
      it = new QListWidgetItem(v.name + "(" + v.scope2 + ")");      
    } else {
      it = new QListWidgetItem(kbasicIcon(kbasicPath(ss)), v.name + "(" + v.scope2 + ")");
    }
    //it->setData(Qt::UserRole, "s");

    QString s = sName + "_" + v.name;

    if (v.file == "Control"){     
      it->setForeground(QBrush(Qt::darkGray));
    } else if (v.file == "SQL"){      
      it->setForeground(QBrush(Qt::darkCyan));
    } else if (v.file == "Event"){      
      it->setForeground(QBrush(Qt::red));
    }
    if (my_sourcecodeeditor_editor->my_sourcecodeeditor->hasSub(s, false)){
      QFont f = it->font();
      it->setForeground(QBrush(Qt::black));
      f.setBold(true);      
      it->setFont(f);
    }

    if (v.name.compare("OnOpen", Qt::CaseInsensitive) == 0){
      onopen = it;
    } else {
      addItem(it);
    }

  }

  setSortingEnabled(false);

  if (onopen){
    insertItem(0, "");
    insertItem(0, onopen);
  }

  if (count()) setCurrentRow(0); // needed for correct mouse selections after scrolling

}