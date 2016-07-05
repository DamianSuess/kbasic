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

#include "_sourcecodeeditor.h"
#include "_sourcecodeeditor_editor.h"
#include "_inputtip.h"
#include "_mainwindow.h"
#include "_helpwindow_shortcut.h"
#include "_propertywindow.h"
//#include "_help_reference.h"
#include "_help.h"
#include "_find.h"

extern QDockWidget *EXTERN_ToolboxForm;
extern QDockWidget *EXTERN_ToolboxReport;
extern QDockWidget *EXTERN_ToolboxMenuBar;
extern QDockWidget *EXTERN_ToolboxToolBar;
extern QDockWidget *EXTERN_Helpwindow_shortcut;


extern QDockWidget *EXTERN_DatabaseTables;

extern const QIcon &kbasicIcon(QString s);

extern _helpwindow_shortcut *EXTERN_my_helpwindow_shortcut;
extern _propertywindow *EXTERN_my_propertywindow;

extern _sourcecodeeditor *EXTERN_my_sourcecodeeditor;
extern _mainwindow *EXTERN_my_mainwindow;

extern QString kbasicPath(QString sPath);

//extern _helpwindow *EXTERN_my_helpwindow;

extern int nPropertyWindowForWhat;

QMap<QString, QString> list;
QMap<QString, QString> list_desc;

_sourcecodeeditor_editor::_sourcecodeeditor_editor(QWidget* parent, _sourcecodeeditor* _my_sourcecodeeditor) : QTextEdit(parent)
{
  nOldBlockCount = -1;
  
  setAcceptRichText(false);
  setCursorWidth(2);
  setFrameStyle(QFrame::NoFrame);

  my_sourcecodeeditor = _my_sourcecodeeditor;

  connect(this, SIGNAL(textChanged(void)), this, SLOT(textChanged(void)));

  connect(this, SIGNAL(cursorPositionChanged(void)), my_sourcecodeeditor, SLOT(cursorPositionChanged(void)));
  connect(this, SIGNAL(selectionChanged(void)), my_sourcecodeeditor, SLOT(selectionChanged(void)));

  


  keyPressedTime = 0;
  my_inputtip = 0;
  my_inputtip2 = 0;

  nDotPressed = 0;
  bInputDot = false;
  bInputBrace = false;
  bInputAs = false;
  sLineBeforeInput = "";

  nTimerId = startTimer(300); 

  createList();


}

_sourcecodeeditor_editor::~_sourcecodeeditor_editor(void)
{
  killTimer(nTimerId);
  hideInput();
  
}

void _sourcecodeeditor_editor::keyPressEvent(QKeyEvent* e)
{
  keyPressedTime = QDateTime::currentDateTime().toTime_t();
  nDotPressed = 0;

  int index = 0;

  int n  = e->key();

  if (!e->text().isNull()){
    QString s = e->text();
    if (s.compare(".") == 0){      

      if (my_inputtip == 0){
        sLineBeforeInput = my_sourcecodeeditor->getCurrentLineAsString();
        nDotPressed = 1;

        bInputDot = true;
        bInputBrace = false;
        bInputAs = false;
      }

    } else if (s.compare("(") == 0){

      if (my_inputtip == 0){
        sLineBeforeInput = my_sourcecodeeditor->getCurrentLineAsString();
        nDotPressed = 1;

        bInputDot = false;
        bInputBrace = true;
        bInputAs = false;
      }
    } else if (s.compare(")") == 0){

      // getting count of braces
      QString s = my_sourcecodeeditor->getCurrentLineAsString();

      s = s.mid(sLineBeforeInput.length());
      s += ")";

      int nLeft = 0;
      int nRight = 0;
      int h = -1;

      do {
        h = s.indexOf("(", h + 1);
        if (h >= 0) nLeft++;
      } while (h >= 0);  
          
      h = -1;

      do {
        h = s.indexOf(")", h + 1);
        if (h >= 0) nRight++;
      } while (h >= 0);  
      

      if (nLeft == nRight && my_inputtip != 0 && my_inputtip->isUsedAsLabel()){
        hideInput();
      }

    } else {
      QString s = my_sourcecodeeditor->getCurrentLineAsString();
      index = my_sourcecodeeditor->getCurrentColumn();
      QString s2 = s.left(index);


      if (s2.endsWith(" As", Qt::CaseInsensitive) || (s2.endsWith("As", Qt::CaseInsensitive)/* && index == 1*/) || s2.endsWith(" New", Qt::CaseInsensitive) || (s2.endsWith("New", Qt::CaseInsensitive)/* && index == 1*/)){
        nDotPressed = 1;

        bInputDot = false;
        bInputBrace = false;
        bInputAs = true;
      }
    }
  }

  bool bAppend = false;
  if (n == Qt::Key_Escape){
    if (!bInputAs){
      hideInput();
    }
    if (my_sourcecodeeditor->isFullScreen()){
      my_sourcecodeeditor->setNoFullscreen(true);
    }
    
  } else if (n == Qt::Key_Backtab){

    my_sourcecodeeditor->performUnindent();
    goto we;
  } else if (n == Qt::Key_Tab){

    my_sourcecodeeditor->performIndent();
    goto we;
  } else if (n == Qt::Key_Return || n == Qt::Key_Enter){        
    
    bAppend = my_sourcecodeeditor->beautifyCurrentLine();

    if (my_inputtip != 0){
      hideInput();
    }

  } else if (n == Qt::Key_F3){

    if (e->modifiers() == Qt::ShiftModifier){
       _find *o = new _find(my_sourcecodeeditor, false, true);
    } else {
       _find *o = new _find(my_sourcecodeeditor, true, false);
    }

    goto we;

  } else if (n == Qt::Key_Home){
  
    QTextCursor c = textCursor();
    int nn = c.columnNumber();

    c.movePosition(QTextCursor::StartOfLine, QTextCursor::MoveAnchor);
    c.movePosition(QTextCursor::EndOfLine, QTextCursor::KeepAnchor);

    QString s = c.selectedText();

    int n = 0;

    for (; n < s.length(); n++){
      if (s.at(n).isSpace()){
      } else {
        break;
      }
    }        
    if (nn != n && nn > 0){      
      if (e->modifiers() == Qt::ShiftModifier){
        c.movePosition(QTextCursor::StartOfLine, QTextCursor::MoveAnchor);
        c.movePosition(QTextCursor::Right, QTextCursor::MoveAnchor, nn);  
        c.movePosition(QTextCursor::Left, QTextCursor::KeepAnchor, nn - n);  
        setTextCursor(c);
        goto we;
      } else {
        c.movePosition(QTextCursor::StartOfLine, QTextCursor::MoveAnchor);
        c.movePosition(QTextCursor::Right, QTextCursor::MoveAnchor, n);  
        setTextCursor(c);
        goto we;
      }
    }

  }

  QTextEdit::keyPressEvent(e);
  my_sourcecodeeditor->keyPressEvent(e);
we:
  if (n == Qt::Key_Return || n == Qt::Key_Enter){        
    my_sourcecodeeditor->insertCorrectIdentForLine(bAppend);
          
  } else if (n == Qt::Key_F1){

    QString s = my_sourcecodeeditor->getCurrentLineAsString();
    int index = my_sourcecodeeditor->getCurrentColumn();
    if (index - 1 < 0 || s[index - 1] != QChar(' ')){
      int l = index;
      int r = index;
      while (l - 1 >= 0){
        QChar c = s[--l];
        if (c != QChar('.') && (!c.isLetterOrNumber() || c == QChar(' '))) break;
      }
      int n = s.length();
      while (r < n && s[r++] != ' ');
      s = s.mid(l, r - l);

      s = s.trimmed();
      int mm = s.indexOf("(");
      if (mm >= 0){
        s = s.left(mm);
      }
      mm = s.indexOf("[");
      if (mm >= 0){
        s = s.left(mm);
      }
      if (s.contains(".")){
        int n = s.indexOf(".");
        QString l = s.left(n);
        QString r = s.mid(n + 1);
        n = r.indexOf("(");
        if (n >= 0) r = r.left(n);
        s = EXTERN_my_mainwindow->getForF1(l, r);
        if (s.length() && s[0] != QChar('\"')) QDesktopServices::openUrl(QUrl(s));
      } else {
        if (s.length() && s[0] != QChar('\"')) showHelpEntry(s);
      }
    }
  }

  if (my_inputtip != 0 && my_inputtip->isUsedAsLabel()){

    QString s = my_sourcecodeeditor->getCurrentLineAsString();
    index = my_sourcecodeeditor->getCurrentColumn();

    if (s.length() <= sLineBeforeInput.length()){
      hideInput();
    } else {
      if (index > 1) my_inputtip->setLabel(s, index, false);
    }

  }


  if (this->document()->blockCount() != nOldBlockCount){
    nOldBlockCount = this->document()->blockCount();

    EXTERN_my_mainwindow->updateBreakpointsByEditor();
  }

  
}

void _sourcecodeeditor_editor::showHelpEntry(QString k)
{
  if (k.length() == 0) return;

  k = k.toLower();

       if (k.compare("then") == 0) k = "if";
  else if (k.compare("else") == 0) k = "if";
  else if (k.compare("elseif") == 0) k = "if";
  else if (k.compare("end if") == 0) k = "if";
  else if (k.compare("as") == 0) k = "dim";
  else if (k.compare("new") == 0) k = "dim";
  else if (k.compare("abstract") == 0) k = "class";
  else if (k.compare("byref") == 0) k = "sub";
  else if (k.compare("byval") == 0) k = "sub";
  else if (k.compare("case") == 0) k = "select case";
  else if (k.compare("select") == 0) k = "select case";
  else if (k.compare("catch") == 0) k = "try";
  else if (k.compare("finally") == 0) k = "try";
  else if (k.compare("class_initialize") == 0) k = "class";
  else if (k.compare("class_terminate") == 0) k = "class";
  else if (k.compare("constructor") == 0) k = "class";
  else if (k.compare("destructor") == 0) k = "class";
  else if (k.compare("do") == 0) k = "do while";  
  else if (k.compare("loop") == 0) k = "do while";  
  else if (k.compare("each") == 0) k = "for each";  
  else if (k.compare("explicit") == 0) k = "option";  
  else if (k.compare("base") == 0) k = "option";  
  else if (k.compare("compare") == 0) k = "option";  
  else if (k.compare("global") == 0) k = "dim";  
  else if (k.compare("iterate") == 0) k = "for next";  
  else if (k.compare("next") == 0) k = "for next";  
  else if (k.compare("paramarray") == 0) k = "sub";  
  else if (k.compare("preserve") == 0) k = "dim";  
  else if (k.compare("private") == 0) k = "dim";  
  else if (k.compare("public") == 0) k = "dim";  
  else if (k.compare("protected") == 0) k = "dim";  
  else if (k.compare("kbasic") == 0) k = "option";  
  else if (k.compare("oldbasic") == 0) k = "option";  
  else if (k.compare("veryoldbasic") == 0) k = "option";  
  else if (k.compare("range") == 0) k = "option";  
  else if (k.compare("redim") == 0) k = "dim";  
  else if (k.compare("return") == 0) k = "sub";  
  else if (k.compare("select") == 0) k = "select case";  
  else if (k.compare("for") == 0) k = "for next";  
  else if (k.compare("step") == 0) k = "for next";  
  else if (k.compare("throws") == 0) k = "sub";  
  else if (k.compare("wend") == 0) k = "while";  
  else if (k.compare("inherits") == 0) k = "class";  
  
 // k = k.append(".html");

  QDesktopServices::openUrl(QUrl("http://www.kbasic.com/doku.php?id=lrkeywords#" + k));
  QDesktopServices::openUrl(QUrl("http://www.kbasic.com/doku.php?id=lrbuiltins#" + k));
  //_help_reference *h = new _help_reference(this, kbasicPath("docs/languagereference/" + k), QUrl(""));  
}

void _sourcecodeeditor_editor::keyReleaseEvent(QKeyEvent* e)
{
  QTextEdit::keyReleaseEvent(e);
  my_sourcecodeeditor->keyReleaseEvent(e);
}

void _sourcecodeeditor_editor::mousePressEvent(QMouseEvent* e)
{
  hideInput();
  QTextEdit::mousePressEvent(e);
}

void _sourcecodeeditor_editor::mouseDoubleClickEvent(QMouseEvent* e)
{
  QTextEdit::mouseDoubleClickEvent(e);
  QTextCursor c = textCursor();
  QString s = c.selectedText();

  if (!s.contains("\"")) return;

  int n = s.length();
  int y = c.blockNumber();
  int x = c.columnNumber() - n;
  int n1 = s.startsWith("\"") ? 1 : 0;
  int n2 = s.endsWith("\"") ? 1 : 0;


  c.movePosition(QTextCursor::Start, QTextCursor::MoveAnchor);
  c.movePosition(QTextCursor::Down, QTextCursor::MoveAnchor, y);
  c.movePosition(QTextCursor::Right, QTextCursor::MoveAnchor, x + n1);  
  setTextCursor(c);

  c.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor, n - n1 - n2);  
  setTextCursor(c);  

}

void _sourcecodeeditor_editor::textChanged ()
{
  my_sourcecodeeditor->updateBrowser();  
}

void _sourcecodeeditor_editor::hideInput()
{
  if (my_inputtip != 0){
    my_inputtip->hide();
    my_inputtip->close();
    delete my_inputtip;
    my_inputtip = 0;
  }
  if (my_inputtip2 != 0){
    my_inputtip2->hide();
    my_inputtip2->close();
    delete my_inputtip2;
    my_inputtip2 = 0;
  }
}

void _sourcecodeeditor_editor::hideInput2()
{
  if (my_inputtip2 != 0){
    my_inputtip2->hide();
    my_inputtip2->close();
    delete my_inputtip2;
    my_inputtip2 = 0;
  }
}

void _sourcecodeeditor_editor::showInput()
{
  hideInput();

  QPoint p;
  if (bInputBrace){
    p = mapToGlobal(cursorRect().topLeft());
  } else {
    p = cursorRect().topLeft();
  }
  int x = p.x();
  int y = p.y();
  int h = cursorRect().bottomLeft().y() - cursorRect().topLeft().y();

  //x += 4;
  if (bInputBrace){
    //y += h;//(h * 4) - 6;
  } else {
    y += h;// + 4;
  }

  QString sSubSyntax = "";
  QString sSubDesc = "";
  
  if (bInputBrace){

    QString k = getLastIdentifierBeforeBrace().toUpper();  
    k = k.trimmed();

    sSubSyntax = list[k];
    sSubDesc = list_desc[k];

  }

  //if (bInputBrace == false)
  {
    hideInput();
    QStringList ln;
    QStringList lt;
    QStringList lm;

    QWidget *w = viewport();
    int yy = w->y();
    int hh = w->height();

    my_inputtip = new _inputtip(this, bInputDot, bInputBrace, bInputAs, sSubSyntax, sSubDesc, ln, lt, lm);  
    if (my_inputtip->count() || sSubSyntax.length()){
      int n = my_inputtip->height();
//      int n = bInputBrace ? 42 : 200;
      if ( y + 200 > hh){
        my_inputtip->move(x, hh - n - (hh - y) - yy - 1);  
      } else {
        my_inputtip->move(x, y);  
      }
      my_inputtip->show();
    }
  }

  if (bInputBrace == false){
    if (my_inputtip->count() || sSubSyntax.length()) my_inputtip->setFocus();    
  }


}

void _sourcecodeeditor_editor::timerEvent(QTimerEvent *e)
{
  if (nDotPressed == 2/* && my_sourcecodeeditor->bAutoCompletion*/){
    nDotPressed = 0;  
    showInput();
  } else if (nDotPressed == 1){
    nDotPressed++;
  }
/*
  if (nDebugMousePressed == 2){
    nDebugMousePressed = 0;
    
    showInputDebug();    

  } else if (nDebugMousePressed == 1){
    nDebugMousePressed++;
  }*/
}

QString _sourcecodeeditor_editor::getLastIdentifierBeforeBrace()
{
  QString s = my_sourcecodeeditor->getCurrentLineAsString();
  s = s.left(my_sourcecodeeditor->getCurrentColumn() - 1);
  int n = s.lastIndexOf("(");
  QString s2 = s.left(n);
  int i;
  for (i = s2.length() - 1; i >= 0; i--){
    QChar c = s2.at(i);
    if (c == '.'){ i++; break; }
    if (c.isLetterOrNumber() || c == '_'){
    } else {
      break;
    }
  }

  return s2.mid(i);
}

QString _sourcecodeeditor_editor::getLastIdentifierBeforeDot()
{
  QString s = my_sourcecodeeditor->getCurrentLineAsString();
  s = s.left(my_sourcecodeeditor->getCurrentColumn() - 1);
  int n = s.lastIndexOf(".");
  QString s2 = s.left(n);
  int i;
  for (i = s2.length() - 1; i >= 0; i--){
    QChar c = s2.at(i);
    if (c.isLetterOrNumber() || c == '_'){
    } else {
      break;
    }
  }

  return s2.mid(i);
}


void _sourcecodeeditor_editor::performInsertText(QString s)
{
  my_sourcecodeeditor->performInsertText(s);
}

void _sourcecodeeditor_editor::updateActions()
{
  focusInEvent(0);
}


void _sourcecodeeditor_editor::focusInEvent(QFocusEvent *e)
{
  EXTERN_ToolboxForm->hide();
  EXTERN_ToolboxReport->hide();
  EXTERN_ToolboxMenuBar->hide();
  EXTERN_ToolboxToolBar->hide();
  //EXTERN_Helpwindow_shortcut->show();

  QWidget *w = parentWidget()->parentWidget();

  if (w) EXTERN_my_mainwindow->workspace->setActiveSubWindow((QMdiSubWindow *) w);

  EXTERN_my_sourcecodeeditor = my_sourcecodeeditor;

  EXTERN_my_mainwindow->updateGeneralActions(
   false,  false,  false,  false, 
   false,  true,  false,  false,  false,   
  false, false, false, 
  my_sourcecodeeditor->bCanCopy, canPaste(), my_sourcecodeeditor->bCanRedo, my_sourcecodeeditor->bCanUndo, 
  my_sourcecodeeditor->isFormClassSourceCode(), this->my_sourcecodeeditor->getFilename());

  EXTERN_my_mainwindow->updateRunActions();
/*
  EXTERN_my_helpwindow->setText(
"It is not much different editing text in a word processor or in KBasic. You have a cursor showing the current position you can type. You can also find and replace inside your source code as in a word processor."
    );
*/
  EXTERN_DatabaseTables->setShown(false);

  nPropertyWindowForWhat = 4; EXTERN_my_propertywindow->showProperties(true, my_sourcecodeeditor->getFilename()); // update tree view with parser info


  if (e) QTextEdit::focusInEvent(e);
}

void _sourcecodeeditor_editor::focusOutEvent(QFocusEvent *e)
{
  //EXTERN_my_sourcecodeeditor = 0;
  QTextEdit::focusOutEvent(e);
}

void _sourcecodeeditor_editor::undo()
{
  bool b = document()->isModified();
  QTextEdit::undo();
  if (b && !document()->isModified()){
    my_sourcecodeeditor->updateCaption(my_sourcecodeeditor->getFilenameWithoutPath(), false);
  }
  
}
/*
void _sourcecodeeditor_editor::insertFromMimeData ( const QMimeData * source ) 
{
  source = new QMimeData();
  if (source->hasHtml()){
    source->setText(source->text());      
  }
}*/


void _sourcecodeeditor_editor::createList()
{
  static bool bNeedToCreate = true;

  if (bNeedToCreate){
    bNeedToCreate = false;
  } else {
    return;
  }


list[QString("Boolean").toUpper()] = "Boolean(Expression) As Boolean";
list_desc[QString("Boolean").toUpper()] = "";

list[QString("String").toUpper()] = "String(Expression) As Boolean";
list_desc[QString("String").toUpper()] = "";

list[QString("Byte").toUpper()] = "Byte(Expression) As Boolean";
list_desc[QString("Byte").toUpper()] = "";

list[QString("Short").toUpper()] = "Short(Expression) As Boolean";
list_desc[QString("Short").toUpper()] = "";

list[QString("Integer").toUpper()] = "Integer(Expression) As Boolean";
list_desc[QString("Integer").toUpper()] = "";

list[QString("Long").toUpper()] = "Long(Expression) As Boolean";
list_desc[QString("Long").toUpper()] = "";

list[QString("Single").toUpper()] = "Single(Expression) As Boolean";
list_desc[QString("Single").toUpper()] = "";

list[QString("Double").toUpper()] = "Double(Expression) As Boolean";
list_desc[QString("Double").toUpper()] = "";

list[QString("Decimal").toUpper()] = "Decimal(Expression) As Boolean";
list_desc[QString("Decimal").toUpper()] = "";

list[QString("DateTime").toUpper()] = "DateTime(Expression) As Boolean";
list_desc[QString("DateTime").toUpper()] = "";

list[QString("Currency").toUpper()] = "Currency(Expression) As Boolean";
list_desc[QString("Currency").toUpper()] = "";
/*
list[QString("Date").toUpper()] = "Date(Expression) As Boolean";
list_desc[QString("Date").toUpper()] = "";
*/

list[QString("Type").toUpper()] = "Type(Variable) As String";
list_desc[QString("Type").toUpper()] = "";

list[QString("Size").toUpper()] = "Size(Variable) As Integer";
list_desc[QString("Size").toUpper()] = "";

list[QString("File").toUpper()] = "File() As String";
list_desc[QString("File").toUpper()] = "";

list[QString("Line").toUpper()] = "Line() As Integer";
list_desc[QString("Line").toUpper()] = "";

list[QString("IsLinux").toUpper()] = "IsLinux() As Boolean";
list_desc[QString("IsLinux").toUpper()] = "";

list[QString("IsMac").toUpper()] = "IsMac() As Boolean";
list_desc[QString("IsMac").toUpper()] = "";

list[QString("IsWindows").toUpper()] = "IsWindows() As Boolean";
list_desc[QString("IsWindows").toUpper()] = "";

list[QString("Sub").toUpper()] = "Sub() As String";
list_desc[QString("Sub").toUpper()] = "";

list[QString("Function").toUpper()] = "Function() As String";
list_desc[QString("Function").toUpper()] = "";

list[QString("Module").toUpper()] = "Module() As String";
list_desc[QString("Module").toUpper()] = "";

list[QString("Class").toUpper()] = "Class() As String";
list_desc[QString("Class").toUpper()] = "";
    


list[QString("kbAbort").toUpper()] = "kbAbort";
list_desc[QString("kbAbort").toUpper()] = "Constant";

list[QString("kbAbortRetryIgnore").toUpper()] = "kbAbortRetryIgnore";
list_desc[QString("kbAbortRetryIgnore").toUpper()] = "Constant";

list[QString("kbArchive").toUpper()] = "kbArchive";
list_desc[QString("kbArchive").toUpper()] = "Constant";

list[QString("kbArray").toUpper()] = "kbArray";
list_desc[QString("kbArray").toUpper()] = "Constant";

list[QString("kbBack").toUpper()] = "kbBack";
list_desc[QString("kbBack").toUpper()] = "Constant";

list[QString("kbBoolean").toUpper()] = "kbBoolean";
list_desc[QString("kbBoolean").toUpper()] = "Constant";

list[QString("kbByte").toUpper()] = "kbByte";
list_desc[QString("kbByte").toUpper()] = "Constant";

list[QString("kbCancel").toUpper()] = "kbCancel";
list_desc[QString("kbCancel").toUpper()] = "Constant";

list[QString("kbCr").toUpper()] = "kbCr";
list_desc[QString("kbCr").toUpper()] = "Constant";

list[QString("kbCrLf").toUpper()] = "kbCrLf";
list_desc[QString("kbCrLf").toUpper()] = "Constant";

list[QString("kbCritical").toUpper()] = "kbCritical";
list_desc[QString("kbCritical").toUpper()] = "Constant";

list[QString("kbCurrency").toUpper()] = "kbCurrency";
list_desc[QString("kbCurrency").toUpper()] = "Constant";

list[QString("kbDate").toUpper()] = "kbDate";
list_desc[QString("kbDate").toUpper()] = "Constant";

list[QString("kbDefaultButton1").toUpper()] = "kbDefaultButton1";
list_desc[QString("kbDefaultButton1").toUpper()] = "Constant";

list[QString("kbDefaultButton2").toUpper()] = "kbDefaultButton2";
list_desc[QString("kbDefaultButton2").toUpper()] = "Constant";

list[QString("kbDefaultButton3").toUpper()] = "kbDefaultButton3";
list_desc[QString("kbDefaultButton3").toUpper()] = "Constant";

list[QString("kbDirectory").toUpper()] = "kbDirectory";
list_desc[QString("kbDirectory").toUpper()] = "Constant";

list[QString("kbDouble").toUpper()] = "kbDouble";
list_desc[QString("kbDouble").toUpper()] = "Constant";

list[QString("kbEmpty").toUpper()] = "kbEmpty";
list_desc[QString("kbEmpty").toUpper()] = "Constant";

list[QString("kbError").toUpper()] = "kbError";
list_desc[QString("kbError").toUpper()] = "Constant";

list[QString("kbExclamation").toUpper()] = "kbExclamation";
list_desc[QString("kbExclamation").toUpper()] = "Constant";

list[QString("kbFriday").toUpper()] = "kbFriday";
list_desc[QString("kbFriday").toUpper()] = "Constant";

list[QString("kbHidden").toUpper()] = "kbHidden";
list_desc[QString("kbHidden").toUpper()] = "Constant";

list[QString("kbIgnore").toUpper()] = "kbIgnore";
list_desc[QString("kbIgnore").toUpper()] = "Constant";

list[QString("kbInformation").toUpper()] = "kbInformation";
list_desc[QString("kbInformation").toUpper()] = "Constant";

list[QString("kbInteger").toUpper()] = "kbInteger";
list_desc[QString("kbInteger").toUpper()] = "Constant";

list[QString("kbLf").toUpper()] = "kbLf";
list_desc[QString("kbLf").toUpper()] = "Constant";

list[QString("kbLong").toUpper()] = "kbLong";
list_desc[QString("kbLong").toUpper()] = "Constant";

list[QString("kbMonday").toUpper()] = "kbMonday";
list_desc[QString("kbMonday").toUpper()] = "Constant";

list[QString("kbNewLine").toUpper()] = "kbNewLine";
list_desc[QString("kbNewLine").toUpper()] = "Constant";

list[QString("kbNo").toUpper()] = "kbNo";
list_desc[QString("kbNo").toUpper()] = "Constant";

list[QString("kbNormal").toUpper()] = "kbNormal";
list_desc[QString("kbNormal").toUpper()] = "Constant";

list[QString("kbNull").toUpper()] = "kbNull";
list_desc[QString("kbNull").toUpper()] = "Constant";

list[QString("kbNullChar").toUpper()] = "kbNullChar";
list_desc[QString("kbNullChar").toUpper()] = "Constant";

list[QString("kbNullString").toUpper()] = "kbNullString";
list_desc[QString("kbNullString").toUpper()] = "Constant";

list[QString("kbOK").toUpper()] = "kbOK";
list_desc[QString("kbOK").toUpper()] = "Constant";

list[QString("kbOKCancel").toUpper()] = "kbOKCancel";
list_desc[QString("kbOKCancel").toUpper()] = "Constant";

list[QString("kbOKOnly").toUpper()] = "kbOKOnly";
list_desc[QString("kbOKOnly").toUpper()] = "Constant";

list[QString("kbObject").toUpper()] = "kbObject";
list_desc[QString("kbObject").toUpper()] = "Constant";

list[QString("kbQuestion").toUpper()] = "kbQuestion";
list_desc[QString("kbQuestion").toUpper()] = "Constant";

list[QString("kbReadOnly").toUpper()] = "kbReadOnly";
list_desc[QString("kbReadOnly").toUpper()] = "Constant";

list[QString("kbRetry").toUpper()] = "kbRetry";
list_desc[QString("kbRetry").toUpper()] = "Constant";

list[QString("kbRetryCancel").toUpper()] = "kbRetryCancel";
list_desc[QString("kbRetryCancel").toUpper()] = "Constant";

list[QString("kbSaturday").toUpper()] = "kbSaturday";
list_desc[QString("kbSaturday").toUpper()] = "Constant";

list[QString("kbShort").toUpper()] = "kbShort";
list_desc[QString("kbShort").toUpper()] = "Constant";

list[QString("kbSingle").toUpper()] = "kbSingle";
list_desc[QString("kbSingle").toUpper()] = "Constant";

list[QString("kbString").toUpper()] = "kbString";
list_desc[QString("kbString").toUpper()] = "Constant";

list[QString("kbSunday").toUpper()] = "kbSunday";
list_desc[QString("kbSunday").toUpper()] = "Constant";

list[QString("kbSystem").toUpper()] = "kbSystem";
list_desc[QString("kbSystem").toUpper()] = "Constant";

list[QString("kbTab").toUpper()] = "kbTab";
list_desc[QString("kbTab").toUpper()] = "Constant";

list[QString("kbThursday").toUpper()] = "kbThursday";
list_desc[QString("kbThursday").toUpper()] = "Constant";

list[QString("kbTuesday").toUpper()] = "kbTuesday";
list_desc[QString("kbTuesday").toUpper()] = "Constant";

list[QString("kbUseSystem").toUpper()] = "kbUseSystem";
list_desc[QString("kbUseSystem").toUpper()] = "Constant";

list[QString("kbVariant").toUpper()] = "kbVariant";
list_desc[QString("kbVariant").toUpper()] = "Constant";

list[QString("kbVolume").toUpper()] = "kbVolume";
list_desc[QString("kbVolume").toUpper()] = "Constant";

list[QString("kbWednesday").toUpper()] = "kbWednesday";
list_desc[QString("kbWednesday").toUpper()] = "Constant";

list[QString("kbYes").toUpper()] = "kbYes";
list_desc[QString("kbYes").toUpper()] = "Constant";

list[QString("kbYesNo").toUpper()] = "kbYesNo";
list_desc[QString("kbYesNo").toUpper()] = "Constant";

list[QString("kbYesNoCancel").toUpper()] = "kbYesNoCancel";
list_desc[QString("kbYesNoCancel").toUpper()] = "Constant";



list[QString("Abs").toUpper()] = "Abs(EXPRESSION) As Double";
list_desc[QString("Abs").toUpper()] = "Returns the absolute value of an argument.";

list[QString("AddDays").toUpper()] = "AddDays(DateTime, Days As Integer) As DateTime";
list_desc[QString("AddDays").toUpper()] = "";

list[QString("AddHours").toUpper()] = "AddHours(DateTime, Hours As Integer) As DateTime";
list_desc[QString("AddHours").toUpper()] = "";

list[QString("AddMinutes").toUpper()] = "AddMinutes(DateTime, Minutes As Integer) As DateTime";
list_desc[QString("AddMinutes").toUpper()] = "";

list[QString("AddMonths").toUpper()] = "AddMonths(DateTime, Months As Integer) As DateTime";
list_desc[QString("AddMonths").toUpper()] = "";

list[QString("AddSeconds").toUpper()] = "AddSeconds(DateTime, Seconds As Integer) As DateTime";
list_desc[QString("AddSeconds").toUpper()] = "";

list[QString("AddYears").toUpper()] = "AddYears(DateTime, Years As Integer) As DateTime";
list_desc[QString("AddYears").toUpper()] = "";

list[QString("Append").toUpper()] = "Append(String, String)";
list_desc[QString("Append").toUpper()] = "";

list[QString("Array").toUpper()] = "Array(ARGUMENTS) As Variant";
list_desc[QString("Array").toUpper()] = "Creates an array of variant values.";

list[QString("Asc").toUpper()] = "Asc(String) As Integer";
list_desc[QString("Asc").toUpper()] = "Returns the ASCII code for the first character of a STRING. ";

list[QString("Beep").toUpper()] = "Beep()";
list_desc[QString("Beep").toUpper()] = "Produces a sound. Depends on the system if it works.";

list[QString("Bin").toUpper()] = "Bin(EXPRESSION) As String";
list_desc[QString("Bin").toUpper()] = "Bin or BIN$ returns a string giving the binary (base 2) representation of ‘number’.";

list[QString("CBool").toUpper()] = "CBool(EXPRESSION) As Boolean";
list_desc[QString("CBool").toUpper()] = "It converts any number to a boolean.";

list[QString("CByte").toUpper()] = "CByte(EXPRESSION) As Byte";
list_desc[QString("CByte").toUpper()] = "It converts any number to a byte.";

list[QString("CCur").toUpper()] = "CCur(EXPRESSION) As Currency";
list_desc[QString("CCur").toUpper()] = "It converts any number to a currency.";

list[QString("CDate").toUpper()] = "CDate(EXPRESSION) As Date";
list_desc[QString("CDate").toUpper()] = "It converts any number to a date.";

list[QString("CDbl").toUpper()] = "CDbl(EXPRESSION) As Double";
list_desc[QString("CDbl").toUpper()] = "It converts any number to a double.";

list[QString("ChDir").toUpper()] = "ChDir(String)";
list_desc[QString("ChDir").toUpper()] = "Changes the current directory to new one.";

list[QString("ChDrive").toUpper()] = "ChDrive(String)";
list_desc[QString("ChDrive").toUpper()] = "Changes to another current drive.";

list[QString("Chr").toUpper()] = "Chr(EXPRESSION) As String";
list_desc[QString("Chr").toUpper()] = "Returns the ASCII character corresponding to the value of Val";

list[QString("CInt").toUpper()] = "CInt(EXPRESSION) As Integer";
list_desc[QString("CInt").toUpper()] = "It converts any number to an integer and takes any number and convert it to an integer.";
/*
list[QString("Circle").toUpper()] = "Circle()";
list_desc[QString("Circle").toUpper()] = "Sorry. Not supported yet.";
*/
list[QString("Clear").toUpper()] = "Clear()";
list_desc[QString("Clear").toUpper()] = "It is a method of the error object, which is provided for VB6 backward compatibility.";

list[QString("CLng").toUpper()] = "CLng(EXPRESSION) As Long";
list_desc[QString("CLng").toUpper()] = "It takes any number and tries to convert it to a long.";

list[QString("Close").toUpper()] = "Close([ [#]FileNo As Integer ] {[ , [#]FileNo As Integer ])";
list_desc[QString("Close").toUpper()] = "Closes the specified file(s).";

list[QString("CLS").toUpper()] = "CLS()";
list_desc[QString("CLS").toUpper()] = "In the terminal screen, CLS will clear the screen and returns the cursor to the upper left corner (line 1, column 1).";

list[QString("Color").toUpper()] = "Color(Fore As Integer [, Back As Integer])";
list_desc[QString("Color").toUpper()] = "Calling COLOR will set the color of either the foreground and optionally the background.";

list[QString("Command").toUpper()] = "Command() As String";
list_desc[QString("Command").toUpper()] = "Returns the arguments which have been given to your application by the OS while starting.";

list[QString("Compare").toUpper()] = "Compare(String, String, CaseSensitive As Boolean = True) As Integer";
list_desc[QString("Compare").toUpper()] = "Lexically compares this string with the other string and returns an integer less than, equal to, or greater than zero if this string is less than, equal to, or greater than the other string.";

list[QString("Contains").toUpper()] = "Contains(String, String, CaseSensitive As Boolean = True) As Boolean";
list_desc[QString("Contains").toUpper()] = "Returns true if this string contains an occurrence of the string str; otherwise returns false.";

list[QString("Count").toUpper()] = "Count(String, String, CaseSensitive As Boolean = True) As Integer";
list_desc[QString("Count").toUpper()] = "Returns the number of (potentially overlapping) occurrences of the string str in this string.";

list[QString("Cos").toUpper()] = "Cos(EXPRESSION) As Double";
list_desc[QString("Cos").toUpper()] = "It returns the cosine of the argument ‘number’ in radians.";

list[QString("CShort").toUpper()] = "CShort(EXPRESSION) As Short";
list_desc[QString("CShort").toUpper()] = "Sorry. Not implemented yet. Use CInt instead of it.";

list[QString("CSng").toUpper()] = "CSng(EXPRESSION) As Single";
list_desc[QString("CSng").toUpper()] = "It converts any number to a single.";

list[QString("CSRLin").toUpper()] = "CSRLin() As Integer";
list_desc[QString("CSRLin").toUpper()] = "It returns the current line of the cursor.";

list[QString("CurDir").toUpper()] = "CurDir([Drive As String]) As String";
list_desc[QString("CurDir").toUpper()] = "It returns the current path.";

list[QString("CVErr").toUpper()] = "CVErr(EXPRESSION) As Variant";
list_desc[QString("CVErr").toUpper()] = "It returns a user defined error.";

list[QString("Date").toUpper()] = "Date() As String";
list_desc[QString("Date").toUpper()] = "Date or DATE$ returns the current system date as a string.";

list[QString("DateAdd").toUpper()] = "DateAdd(Interval As String, Number As Integer, DateToChange As Date) As Date";
list_desc[QString("DateAdd").toUpper()] = "Adds something to a date.";

list[QString("DateDiff").toUpper()] = "DateDiff(Interval As String, Date1 As Date, Date2 As Date[, FirstDayOfWeek As String[, FirstWeekOfYear As String]]) As Date";
list_desc[QString("DateDiff").toUpper()] = "Returns the number of interval laying between date1 and date2.";

list[QString("DatePart").toUpper()] = "DatePart(Interval As String, DateToAsk As Date [, FirstDayOfWeek As String[, FirstWeekOfYear As String]]) As Integer";
list_desc[QString("DatePart").toUpper()] = "Returns the desired part of a date.";

list[QString("DateSerial").toUpper()] = "DatePart(Year As Integer, Month As Integer, Day As Integer) As Date";
list_desc[QString("DateSerial").toUpper()] = "Converts a date given by year, month and day into a big number.";

list[QString("DateValue").toUpper()] = "DateValue(STRINGEXPRESSION) As Date";
list_desc[QString("DateValue").toUpper()] = "Converts a date given in a string into a date type.";

list[QString("Day").toUpper()] = "Day(DATEEXPRESSION) As Integer";
list_desc[QString("Day").toUpper()] = "Returns the day part of an date expression.";

list[QString("DayName").toUpper()] = "DayName(DateTime, Format As String = \"\") As String";
list_desc[QString("DayName").toUpper()] = "Format may be \"ShortFormat\" or \"LongFormat\". If no Format is given, \"LongFormat\" is used.";

list[QString("DayOfWeek").toUpper()] = "DayOfWeek(DateTime, Format As String = \"\") As String) As String";
list_desc[QString("DayOfWeek").toUpper()] = "Format may be \"ShortFormat\" or \"LongFormat\". If no Format is given, \"LongFormat\" is used.";

list[QString("DayOfYear").toUpper()] = "DayOfYear(DateTime) As Integer";
list_desc[QString("DayOfYear").toUpper()] = "";

list[QString("DaysInMonth").toUpper()] = "DaysInMonth(DateTime) As Integer";
list_desc[QString("DaysInMonth").toUpper()] = "";

list[QString("DaysInYear").toUpper()] = "DaysInYear(DateTime) As Integer";
list_desc[QString("DaysInYear").toUpper()] = "";

list[QString("Decode").toUpper()] = "Decode(String) As String";
list_desc[QString("Decode").toUpper()] = "";

list[QString("DiffDays").toUpper()] = "DiffDays(DateTime, DateTime) As Integer";
list_desc[QString("DiffDays").toUpper()] = "";

list[QString("DiffSeconds").toUpper()] = "DiffSeconds(DateTime, DateTime) As Integer";
list_desc[QString("DiffSeconds").toUpper()] = "";

list[QString("Dir").toUpper()] = "Dir([Path As String [, Attribute]]) As String";
list_desc[QString("Dir").toUpper()] = "";

list[QString("DoEvents").toUpper()] = "DoEvents()";
list_desc[QString("DoEvents").toUpper()] = "Enables the application to process events.";

list[QString("Encode").toUpper()] = "Encode(String) As String";
list_desc[QString("Encode").toUpper()] = "";

list[QString("EndsWith").toUpper()] = "EndsWith(String, String, CaseSensitive As Boolean = True) As Boolean";
list_desc[QString("EndsWith").toUpper()] = "";

list[QString("EOF").toUpper()] = "EOF([#]FileNo) As Boolean";
list_desc[QString("EOF").toUpper()] = "It returns true if end of file has been reached.";

list[QString("Erl").toUpper()] = "Erl() As Integer";
list_desc[QString("Erl").toUpper()] = "It returns the line in which the last error occured.";

list[QString("Err").toUpper()] = "Err() As Integer";
list_desc[QString("Err").toUpper()] = "As for VeryOldBasic, it returns the runtime error code, as for OldBasic it is an object for error handling.";

list[QString("Error").toUpper()] = "Error(EXPRESSION) As String";
list_desc[QString("Error").toUpper()] = "Simulates an error.";

list[QString("Exp").toUpper()] = "Exp(EXPRESSION) As Double";
list_desc[QString("Exp").toUpper()] = "It returns the exponential value of an expression.";

list[QString("FileAttr").toUpper()] = "FileAttr([#]FileNo As Integer, ReturnType As Integer) As Double";
list_desc[QString("FileAttr").toUpper()] = "It returns the access mode for an opened file.";

list[QString("FileCopy").toUpper()] = "FileCopy(Source As String, Destination As String)";
list_desc[QString("FileCopy").toUpper()] = "It copies a file from source to destination.";

list[QString("FileDateTime").toUpper()] = "FileDateTime(FileName As String) As Date";
list_desc[QString("FileDateTime").toUpper()] = "It returns the date of the file.";

list[QString("FileLen").toUpper()] = "FileLen(FileName As String) As Long";
list_desc[QString("FileLen").toUpper()] = "It returns the length of a file in bytes.";

list[QString("Files").toUpper()] = "Files()";
list_desc[QString("Files").toUpper()] = "Provided for QBasic compatibility.";

list[QString("Fill").toUpper()] = "Fill(String, String, Length As Integer = -1)";
list_desc[QString("Fill").toUpper()] = "Provided for QBasic compatibility.";

list[QString("Fix").toUpper()] = "Fix(EXPRESSION) As Long";
list_desc[QString("Fix").toUpper()] = "It cuts off the trail of a number.";

list[QString("Format").toUpper()] = "Format(EXPRESSION, [Format As String, [FillChar As String[, RightAligned As Boolean]]]) As String";
list_desc[QString("Format").toUpper()] = "Creates a string with desired format.";
/*
list[QString("FormatDateTime").toUpper()] = "FormatDateTime(STRINGEXPRESSION[{, EXPRESSION,…]}) As String";
list_desc[QString("FormatDateTime").toUpper()] = "Sorry. Not implemented yet.";
*/

list[QString("Fre").toUpper()] = "Fre(EXPRESSION) As Long";
list_desc[QString("Fre").toUpper()] = "It returns the available memory.";

list[QString("FreeFile").toUpper()] = "FreeFile([Range]) As Integer";
list_desc[QString("FreeFile").toUpper()] = "It returns the next free available file handle.";

list[QString("Get").toUpper()] = "Get([#]FileNo As Integer[, RecordNo As Integer], Variable As AnyType)";
list_desc[QString("Get").toUpper()] = "It reads a record from file.";

list[QString("GetAttr").toUpper()] = "GetAttr(Path As String)";
list_desc[QString("GetAttr").toUpper()] = "It returns attributes of files or directories.";

list[QString("Hex").toUpper()] = "Hex(EXPRESSION) As String";
list_desc[QString("Hex").toUpper()] = "It returns a string giving the hexadecimal (base 16) value.";

list[QString("Hour").toUpper()] = "Hour(DATEEXPRESSION) As Integer";
list_desc[QString("Hour").toUpper()] = "";

list[QString("IndexOf").toUpper()] = "IndexOf(String, Sub As String, Start As Integer = 1, CaseSensitive As Boolean = True) As Integer";
list_desc[QString("IndexOf").toUpper()] = "";

list[QString("Inkey").toUpper()] = "Inkey() As String";
list_desc[QString("Inkey").toUpper()] = "Returns the key code, which was pressed.";

list[QString("Input").toUpper()] = "INPUT([;][STRINGEXPRESSION{;,}] VARIABLENAME[,VARIABLENAME…])";
list_desc[QString("Input").toUpper()] = "Combined screen output and keyboard input.";

list[QString("InputBox").toUpper()] = "InputBox(Prompt As String [, Title As String] [, Default As String]) As String";
list_desc[QString("InputBox").toUpper()] = "Get a string from the user using a input box on screen.";

list[QString("Insert").toUpper()] = "Insert(String, Insert As String, Position As Integer)";
list_desc[QString("Insert").toUpper()] = "";

list[QString("InStr").toUpper()] = "InStr([Start As Integer,] Source As String, Find As String) As Integer";
list_desc[QString("InStr").toUpper()] = "InStr finds one string inside another.";

list[QString("InStRev").toUpper()] = "InStRev([Start As Integer,] Source As String, Find As String) As Integer";
list_desc[QString("InStRev").toUpper()] = "InStRevsearches the Source string for and occurance of the Find string and returns the index of the Find string in the Source string.";

list[QString("Int").toUpper()] = "Int(EXPRESSION) As Long";
list_desc[QString("Int").toUpper()] = "Returns the next integer number < = given number.";

list[QString("IsArray").toUpper()] = "IsArray(EXPRESSION) As Boolean";
list_desc[QString("IsArray").toUpper()] = "Returns true if a variable represents an array type.";

list[QString("IsBoolean").toUpper()] = "IsBoolean(EXPRESSION) As Boolean";
list_desc[QString("IsBoolean").toUpper()] = "Returns true if a variable represents a boolean type.";

list[QString("IsByte").toUpper()] = "IsByte(EXPRESSION) As Boolean";
list_desc[QString("IsByte").toUpper()] = "Returns true if a variable represents a byte type.";

list[QString("IsCurrency").toUpper()] = "IsCurrency(EXPRESSION) As Boolean";
list_desc[QString("IsCurrency").toUpper()] = "Returns true if a variable represents a currency type.";

list[QString("IsDate").toUpper()] = "IsDate(EXPRESSION) As Boolean";
list_desc[QString("IsDate").toUpper()] = "Returns true if a variable represents a date type.";

list[QString("IsDate").toUpper()] = "IsDate(EXPRESSION) As Boolean";
list_desc[QString("IsDate").toUpper()] = "Returns true if a variable represents a date type.";

list[QString("IsDateValid").toUpper()] = "IsDateValid(DateTime) As Boolean";
list_desc[QString("IsDateValid").toUpper()] = "";

list[QString("IsDateTimeValid").toUpper()] = "IsDateTimeValid(DateTime) As Boolean";
list_desc[QString("IsDateTimeValid").toUpper()] = "";

list[QString("IsDouble").toUpper()] = "IsDouble(EXPRESSION) As Boolean";
list_desc[QString("IsDouble").toUpper()] = "";

list[QString("IsEmpty").toUpper()] = "IsEmpty(EXPRESSION) As Boolean";
list_desc[QString("IsEmpty").toUpper()] = "Returns true if expression represents a empty value.";

list[QString("IsError").toUpper()] = "IsError(EXPRESSION) As Boolean";
list_desc[QString("IsError").toUpper()] = "Returns true if the expression represents an error type.";

list[QString("IsInteger").toUpper()] = "IsInteger(EXPRESSION) As Boolean";
list_desc[QString("IsInteger").toUpper()] = "Returns true if the expression represents an integer type.";

list[QString("IsLeapYear").toUpper()] = "IsLeapYear(DateTime) As Boolean";
list_desc[QString("IsLeapYear").toUpper()] = "";

list[QString("IsMissing").toUpper()] = "IsMissing(EXPRESSION) As Boolean";
list_desc[QString("IsMissing").toUpper()] = "Returns if an optional argument of a sub/function has not been given = is missing.";

list[QString("IsNull").toUpper()] = "IsNull(EXPRESSION) As Boolean";
list_desc[QString("IsNull").toUpper()] = "Returns true if the expression represents null.";

list[QString("IsNumeric").toUpper()] = "IsNumeric(EXPRESSION) As Boolean";
list_desc[QString("IsNumeric").toUpper()] = "Returns true if expression represents a numeric value.";

list[QString("IsObject").toUpper()] = "IsObject(EXPRESSION) As Boolean";
list_desc[QString("IsObject").toUpper()] = "Returns true if expression represents an object value.";

list[QString("IsShort").toUpper()] = "IsShort(EXPRESSION) As Boolean";
list_desc[QString("IsShort").toUpper()] = "Returns true if expression represents a short value.";

list[QString("IsSingle").toUpper()] = "IsSingle(EXPRESSION) As Boolean";
list_desc[QString("IsSingle").toUpper()] = "Returns true if expression represents a single value.";

list[QString("IsLong").toUpper()] = "IsLong(EXPRESSION) As Boolean";
list_desc[QString("IsLong").toUpper()] = "Returns true if expression represents a long value.";

list[QString("IsString").toUpper()] = "IsString(EXPRESSION) As Boolean";
list_desc[QString("IsString").toUpper()] = "Returns true if expression represents a string value.";

list[QString("IsTimeValid").toUpper()] = "IsTimeValid(DateTime) As Boolean";
list_desc[QString("IsTimeValid").toUpper()] = "";

list[QString("IsVariant").toUpper()] = "IsVariant(EXPRESSION) As Boolean";
list_desc[QString("IsVariant").toUpper()] = "Returns true if expression represents a variant value.";

list[QString("KBasicDir").toUpper()] = "KBasicDir() As String";
list_desc[QString("KBasicDir").toUpper()] = "It returns the path to the KBasic installation directory. ";

list[QString("Kill").toUpper()] = "Kill(FileName As String)";
list_desc[QString("Kill").toUpper()] = "Deletes a file specified by a filename.";

list[QString("LastIndexOf").toUpper()] = "LastIndexOf(String, Sub As String, Start As Integer = -1, CaseSensitive As Boolean = True) As Integer";
list_desc[QString("LastIndexOf").toUpper()] = "";

list[QString("LCase").toUpper()] = "LCase(STRINGEXPRESSION) As String";
list_desc[QString("LCase").toUpper()] = "LCASE take a string and converts all its characters to lower case.";

list[QString("Left").toUpper()] = "Left(STRINGEXPRESSION, Len As Integer) As String";
list_desc[QString("Left").toUpper()] = "LEFT returns a string containing the first characters of a string.";

list[QString("LeftJustified").toUpper()] = "LeftJustified(String, Width As Integer, Fill As String = " ", Truncate As Boolean = False) As String";
list_desc[QString("LeftJustified").toUpper()] = "Returns a string of size width that contains this string padded by the fill character.";

list[QString("Len").toUpper()] = "Len(STRINGEXPRESSION|VARIABLENAME) As Integer";
list_desc[QString("Len").toUpper()] = "LEN returns the length of a string or the size of a variable in bytes.";

list[QString("Length").toUpper()] = "Length(STRINGEXPRESSION) As Integer";
list_desc[QString("Length").toUpper()] = "Returns the length of a string. ";

/*
list[QString("Line").toUpper()] = "Line([(x1!, y1!)] - (x2!, y2!) [, Color As Integer] ])";
list_desc[QString("Line").toUpper()] = "Draws a line on the screen.";
*/
list[QString("Ln").toUpper()] = "Ln(n As Double) As Long";
list_desc[QString("Ln").toUpper()] = "LN returns the natural logaritm of a number. ";

list[QString("Loc").toUpper()] = "Loc([#]FileNo As Integer) As Long";
list_desc[QString("Loc").toUpper()] = "Returns the current position for reading or writing in a file.";

list[QString("Locate").toUpper()] = "Locate([Y As Integer] [,X As Integer] [,Cursor As Integer])";
list_desc[QString("Locate").toUpper()] = "Sets the cursor position on screen.";

list[QString("LOF").toUpper()] = "LOF([#]FileNo As Integer) As Long";
list_desc[QString("LOF").toUpper()] = "Returns the length of a file in bytes.";

list[QString("Log").toUpper()] = "Log(n As Double) As Long";
list_desc[QString("Log").toUpper()] = "LOG returns a the natural logaritm of a number. ";

list[QString("Lower").toUpper()] = "Lower(String) As String";
list_desc[QString("Lower").toUpper()] = "Returns a new string. It contains the source string converted to all lower case. ";

list[QString("LTrim").toUpper()] = "LTrim(STRINGEXPRESSION) As String";
list_desc[QString("LTrim").toUpper()] = "LTRIM function removes the source string’s leading spaces, from the beginning of the source string.";


createList2();
}


void _sourcecodeeditor_editor::createList2()
{

list[QString("Max").toUpper()] = "Max(EXPRESSION, EXPRESSION) As Double";
list_desc[QString("Max").toUpper()] = "Returns the major value of two values. Both expressions must be numeric.";

list[QString("Mid").toUpper()] = "Mid(Variable As String, Start As Integer[, Len As Integer]) As String";
list_desc[QString("Mid").toUpper()] = "Gets a part of a string.";

list[QString("Min").toUpper()] = "Min(EXPRESSION, EXPRESSION) As Double";
list_desc[QString("Min").toUpper()] = "Returns the minor value of two values. Both expressions must be numeric.";

list[QString("Minute").toUpper()] = "Minute(DATEEXPRESSION) As Integer";
list_desc[QString("Minute").toUpper()] = "Returns the minute part of a time expression.";

list[QString("MkDir").toUpper()] = "MkDir(String)";
list_desc[QString("MkDir").toUpper()] = "Creates a new directory.";

list[QString("Month").toUpper()] = "Month(DATEEXPRESSION) As Integer";
list_desc[QString("Month").toUpper()] = "Returns the month part of a date expression.";

list[QString("MonthName").toUpper()] = "MonthName(DateTime, Format As String = \"\") As String";
list_desc[QString("MonthName").toUpper()] = "";

/*
list[QString("MonthName").toUpper()] = "MonthName(Month As Integer, ShortName As Boolean) As Integer";
list_desc[QString("MonthName").toUpper()] = "Returns the month part of a date expression.";
*/

list[QString("MsgBox").toUpper()] = "MsgBox(Prompt As String [, Buttons As Integer] [, Title As String])";
list_desc[QString("MsgBox").toUpper()] = "Prints a message in a GUI dialog box.";

list[QString("Name").toUpper()] = "Name(OldName As String, NewName As String)";
list_desc[QString("Name").toUpper()] = "Renames a file or a directory.";

list[QString("Now").toUpper()] = "Now() As DateTime";
list_desc[QString("Now").toUpper()] = "Returns the current system date.";

list[QString("Nz").toUpper()] = "Nz(EXPRESSION) As String";
list_desc[QString("Nz").toUpper()] = "Changes to expression from null to nullstring "", if needed.";

list[QString("Oct").toUpper()] = "Oct(EXPRESSION) As String";
list_desc[QString("Oct").toUpper()] = "Returns a string giving the octal (base 8) representation of ‘number’.";

list[QString("Open").toUpper()] = "Open(STRINGEXPRESSION For [Input|Output|Append|Binary|Random] As [#]FileNo [LEN=RecordLen As Integer])";
list_desc[QString("Open").toUpper()] = "Opens a file related on the given mode.";

list[QString("Peek").toUpper()] = "Peek(ByRef String, UDF, Length As Integer)";
list_desc[QString("Peek").toUpper()] = "";

list[QString("Poke").toUpper()] = "STRING, UDF, Length As Integer";
list_desc[QString("Poke").toUpper()] = "";

list[QString("Pos").toUpper()] = "Pos(EXPRESSION) As Integer";
list_desc[QString("Pos").toUpper()] = "POS returns the current cursor position in the line.";

list[QString("Prepend").toUpper()] = "Prepend(String, Prepend As String)";
list_desc[QString("Prepend").toUpper()] = "";

list[QString("Print").toUpper()] = "Print({[ [#]FileNo ,] (EXPRESSION Spc(EXPRESSION ) Tab(EXPRESSION) [; | ,]) })";
list_desc[QString("Print").toUpper()] = "";

list[QString("PrintScreen").toUpper()] = "PrintScreen (PrintDialog As Boolean)";
list_desc[QString("PrintScreen").toUpper()] = "";

list[QString("Put").toUpper()] = "Put([#]FileNo As Integer[, RecordNo As Integer], Variable As AnyType)";
list_desc[QString("Put").toUpper()] = "It wrtites a record to a file.";

list[QString("Rad").toUpper()] = "Rad(EXPRESSION) As Double";
list_desc[QString("Rad").toUpper()] = "";

list[QString("Rad").toUpper()] = "Rad(EXPRESSION) As Double";
list_desc[QString("Rad").toUpper()] = "";

list[QString("Random").toUpper()] = "Random(EXPRESSION) As Double";
list_desc[QString("Random").toUpper()] = "Returns an integer pseudo-random number.";

list[QString("Randomize").toUpper()] = "Randomize([StartValue As Integer])";
list_desc[QString("Randomize").toUpper()] = "Start the random generator.";

list[QString("ReadBinary").toUpper()] = "ReadBinary(String) As AnyType Throws Exception";
list_desc[QString("ReadBinary").toUpper()] = "";

list[QString("Remove").toUpper()] = "Remove(String, Position As Integer, Length As Integer)";
list_desc[QString("Remove").toUpper()] = "";

list[QString("Replace").toUpper()] = "Replace (Str As String, SearchFor As String, ReplaceWith As String, CaseSensitive As Boolean = True)";
list_desc[QString("Replace").toUpper()] = "Replaces string occurances with another string.";

list[QString("Reset").toUpper()] = "Reset()";
list_desc[QString("Reset").toUpper()] = "Closes all opened files.";

list[QString("Reversed").toUpper()] = "Reversed(String) As String";
list_desc[QString("Reversed").toUpper()] = "";

list[QString("RGB").toUpper()] = "RGB(Eed As Integer, Green As Integer, Blue As Integer) As Long";
list_desc[QString("RGB").toUpper()] = "Returns a long value generated by a triple.";

list[QString("Right").toUpper()] = "Right(STRINGEXPRESSION, Len As Integer) As String";
list_desc[QString("Right").toUpper()] = "Right returns a string containing the last characters of a string.";

list[QString("RightJustified").toUpper()] = "RightJustified(String, Width As Integer, Fill As String = " ", Truncate As Boolean = False) As String";
list_desc[QString("RightJustified").toUpper()] = "Returns a string of size() width that contains the fill character followed by the string.";

list[QString("RmDir").toUpper()] = "RmDir(String)";
list_desc[QString("RmDir").toUpper()] = "Deletes a complete directory.";

list[QString("RND").toUpper()] = "RND(EXPRESSION) As Double";
list_desc[QString("RND").toUpper()] = "Returns an integer pseudo-random number.";

list[QString("Round").toUpper()] = "Round(EXPRESSION, Precision As Integer = 0) As Decimal/Double/Long";
list_desc[QString("Round").toUpper()] = "Rounds a value, while Precision determines the number of digits after the dot.";

list[QString("RTrim").toUpper()] = "RTrim(STRINGEXPRESSION) As String";
list_desc[QString("RTrim").toUpper()] = "RTRIM function removes the source string’s trailing spaces, from the end of the source string.";

list[QString("Second").toUpper()] = "Second(DATEEXPRESSION) As Integer";
list_desc[QString("Second").toUpper()] = "Returns the second part of a date expression.";

list[QString("Section").toUpper()] = "Section(String, Separator As String, Start As Integer, End As Integer = -1, SectionFlags = \"SectionDefault\") As String";
list_desc[QString("Section").toUpper()] = "This function returns a section of the string.";

list[QString("Seek").toUpper()] = "Seek(#FileNo, RecordPosition As Long)";
list_desc[QString("Seek").toUpper()] = "Returns the current position in file or set the new position in file.";

list[QString("SeekBinary").toUpper()] = "SeekBinary(String, Integer) As Integer Throws Exception";
list_desc[QString("SeekBinary").toUpper()] = "";

list[QString("Sgn").toUpper()] = "Sgn(EXPRESSION) As Integer";
list_desc[QString("Sgn").toUpper()] = "SGN returns the sign.";

list[QString("Shell").toUpper()] = "Shell(EXPRESSION [, WAIT AS BOOLEAN]) As Long";
list_desc[QString("Shell").toUpper()] = "Send a command to the environment.";

list[QString("Simplified").toUpper()] = "Simplified(String) As String";
list_desc[QString("Simplified").toUpper()] = "Returns a string that has whitespace removed from the start and the end, and that has each sequence of internal whitespace replaced with a single space.";

list[QString("Sin").toUpper()] = "Sin(EXPRESSION) As Long";
list_desc[QString("Sin").toUpper()] = "SIN returns the sine of the argument ‘number’ in radians.";

list[QString("Sleep").toUpper()] = "Sleep([Seconds As Integer])";
list_desc[QString("Sleep").toUpper()] = "Waits for until a was key pressed, or the after a time period.";

list[QString("Space").toUpper()] = "Space(INTEGEREXPRESSION) As String";
list_desc[QString("Space").toUpper()] = "SPACE function creates a string consisting of spaces.";

list[QString("Spc").toUpper()] = "Spc(INTEGEREXPRESSION) As String";
list_desc[QString("Spc").toUpper()] = "Returns a string with a number of spaces. Used together with Print.";

list[QString("Split").toUpper()] = "Split(STRINGEXPRESSION, Separator As String, KeepEmptyParts As Boolean, CaseSensitive As Boolean) As Strings ";
list_desc[QString("Split").toUpper()] = "";

list[QString("Sqr").toUpper()] = "Sqr(EXPRESSION) As Long";
list_desc[QString("Sqr").toUpper()] = "SQR returns the square root of the argument ‘number’.";

list[QString("StartsWith").toUpper()] = "StartsWith(String, String, CaseSensitive As Boolean = True) As Boolean";
list_desc[QString("StartsWith").toUpper()] = "";

list[QString("Str").toUpper()] = "Str(EXPRESSION) As String";
list_desc[QString("Str").toUpper()] = "Converts a number to a string.";

list[QString("StrComp").toUpper()] = "StrComp(STRINGEXPRESSION, STRINGEXPRESSION [, ComparisionMode As Integer]) As String";
list_desc[QString("StrComp").toUpper()] = "Compares two strings.";

list[QString("StrReverse").toUpper()] = "StrReverse(STRINGEXPRESSION) As String";
list_desc[QString("StrReverse").toUpper()] = "Returns a given string reversed.";

list[QString("SubDays").toUpper()] = "SubDays(DateTime, Days As Integer) As DateTime";
list_desc[QString("SubDays").toUpper()] = "";

list[QString("SubHours").toUpper()] = "SubHours(DateTime, Hours As Integer) As DateTime";
list_desc[QString("SubHours").toUpper()] = "";

list[QString("SubMinutes").toUpper()] = "SubMinutes(DateTime, Minutes As Integer) As DateTime";
list_desc[QString("SubMinutes").toUpper()] = "";

list[QString("SubMonths").toUpper()] = "SubMonths(DateTime, Months As Integer) As DateTime";
list_desc[QString("SubMonths").toUpper()] = "";

list[QString("SubSeconds").toUpper()] = "SubSeconds(DateTime, Seconds As Integer) As DateTime";
list_desc[QString("SubSeconds").toUpper()] = "";

list[QString("SubYears").toUpper()] = "SubYears(DateTime, Years As Integer) As DateTime";
list_desc[QString("SubYears").toUpper()] = "";

list[QString("Tab").toUpper()] = "Tab(EXPRESSION) As String";
list_desc[QString("Tab").toUpper()] = "Print Tabs. Used together with Print.";

list[QString("Tan").toUpper()] = "Tan(EXPRESSION) As Long";
list_desc[QString("Tan").toUpper()] = "TAN returns the tangent of the argument ‘number’ in radians.";

list[QString("Time").toUpper()] = "Time() As String";
list_desc[QString("Time").toUpper()] = "Date or TIME$ returns the current system time as a string.";

list[QString("TimeSerial").toUpper()] = "TimeSerial(Hour As Integer, Minute As Integer, Second As Integer) As Long";
list_desc[QString("TimeSerial").toUpper()] = "Returns a time as a integer.";

list[QString("TimeValue").toUpper()] = "TimeValue(STRINGEXPRESSION) As Date";
list_desc[QString("TimeValue").toUpper()] = "Returns a time given in a string expression as a date.";

list[QString("Trim").toUpper()] = "Trim(STRINGEXPRESSION) As String";
list_desc[QString("Trim").toUpper()] = "TRIM function removes the source string’s leading and trailing spaces.";

list[QString("Trimmed").toUpper()] = "Trimmed(String) As String";
list_desc[QString("Trimmed").toUpper()] = "Returns a string that has whitespace removed from the start and the end.";

list[QString("Truncate").toUpper()] = "Truncate(String, Position As Integer)";
list_desc[QString("Truncate").toUpper()] = "";

list[QString("TypeName").toUpper()] = "TypeName(VARIABLENAME) As String";
list_desc[QString("TypeName").toUpper()] = "Returns the type name of a variable as string.";

list[QString("UCase").toUpper()] = "UCase(STRINGEXPRESSION) As String";
list_desc[QString("UCase").toUpper()] = "It takes a string and converts all its characters to upper case. ";

list[QString("Unicode").toUpper()] = "Unicode(String, Position As Integer = 1) As Integer";
list_desc[QString("Unicode").toUpper()] = "Returns the character at the given index position in the string, if Position is unequal 1. Otherwise it returns it for the first character of the string.";

list[QString("Upper").toUpper()] = "Upper(String) As String";
list_desc[QString("Upper").toUpper()] = "";

list[QString("Utf8").toUpper()] = "Utf8(STRINGEXPRESSION) As String";
list_desc[QString("Utf8").toUpper()] = "Utf8 converts a String to a CString or vice versa using UTF8 or the current local 8 Bit character set.";

list[QString("Utf16").toUpper()] = "Utf8(STRINGEXPRESSION) As String";
list_desc[QString("Utf16").toUpper()] = "Utf16 converts a String to a CString or vice versa using UTF16.";

list[QString("Val").toUpper()] = "Val(STRINGEXPRESSION) As Double";
list_desc[QString("Val").toUpper()] = "VAL returns the numerical value of a string.";

list[QString("Value").toUpper()] = "Value(STRINGEXPRESSION) As Double";
list_desc[QString("Value").toUpper()] = "Value returns the numerical value of a string.";

list[QString("VarType").toUpper()] = "VarType(VARIABLENAME) As Integer ";
list_desc[QString("VarType").toUpper()] = "Returns the type of a variable.";

list[QString("Weekday").toUpper()] = "Weekday(DATEEXPRESSION [,FirstDayOfWeek As Integer]) As Integer";
list_desc[QString("Weekday").toUpper()] = "Returns the weekday of a date.";

list[QString("WeekdayName").toUpper()] = "WeekdayName(Weekday As Integer [,ShortName As Boolean, [,FirstDay As Integer] ]) As Integer";
list_desc[QString("WeekdayName").toUpper()] = "Returns the name of the given weekday.";

list[QString("WeekNumber").toUpper()] = "WeekNumber(DateTime) As Integer";
list_desc[QString("WeekNumber").toUpper()] = "";

list[QString("Write").toUpper()] = "Write([ [#]FileNo As Integer, EXPRESSION, EXPRESSION...)";
list_desc[QString("Write").toUpper()] = "Writes data to the screen or a file.";

list[QString("WriteBinary").toUpper()] = "WriteBinary(String, AnyType) Throws Exception";
list_desc[QString("WriteBinary").toUpper()] = "";

list[QString("Year").toUpper()] = "Year(DATEEXPRESSION) As Integer";
list_desc[QString("Year").toUpper()] = "Returns the year of a date.";


}
