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

#include "_find.h"
#include "_sourcecodeeditor.h"
#include "_sourcecodeeditor_editor.h"
#include "../kbshared/typedef.h"

class _mainwindow;

extern _mainwindow *EXTERN_my_mainwindow;

QStringList find_list;

bool bFind_MatchCase = false;
bool bFind_MatchWhole = false;
bool bFind_SearchUp = false;

QString sHidden = "";
bool bHiddenBackwardFirst = true;

_find::_find(_sourcecodeeditor *_my_sourcecodeeditor, bool _bHiddenForward, bool _bHiddenBackward) : QDialog((QWidget *) EXTERN_my_mainwindow)
{

  setAttribute(Qt::WA_DeleteOnClose);
  setWindowFlags(windowFlags() | Qt::Tool);

  setObjectName("Find");

  bHiddenForward = _bHiddenForward;
  bHiddenBackward = _bHiddenBackward;

  my_sourcecodeeditor = _my_sourcecodeeditor;

  setWindowTitle(tr("Find"));
#ifdef LINUX
  setModal(true);
#else
  setModal(false);
#endif

  QGridLayout *grid = new QGridLayout();
  setLayout(grid);

  QHBoxLayout *_tt = new QHBoxLayout();  
  grid->addLayout(_tt, 0, 0);
  

  QLabel *l;
  l = new QLabel(tr("Search for:")); _tt->addWidget(l);

  
  search = new QComboBox(); _tt->addWidget(search);
  //search->addItem("");
  search->setMinimumWidth(200);
  search->setEditable(true);
  search->setInsertPolicy(QComboBox::NoInsert);
  _tt->setStretchFactor(search, 10);
  
  QTextCursor f = my_sourcecodeeditor->my_sourcecodeeditor_editor->textCursor(); 
  QString r = f.selectedText();
  if (bHiddenForward || bHiddenBackward){
    if (!r.isEmpty()) sHidden = r;
  }


  for (int i = 0; i < find_list.size(); i++){
    search->addItem(find_list.at(i));
  }
  if (!r.contains(QString(QChar(0x2029)))){
    search->lineEdit()->setText(r);
  }
/*

  for ( QStringList::Iterator it = list.begin(); it != list.end(); ++it ) {
     search->addItem(*it);      
  }
*/
  setFocusProxy(search);


  QVBoxLayout *_tab1 = new QVBoxLayout();


  matchCase = new QCheckBox(tr("Match case")); _tab1->addWidget(matchCase); matchCase->setChecked(bFind_MatchCase);
  matchWhole = new QCheckBox(tr("Match whole word only")); _tab1->addWidget(matchWhole); matchWhole->setChecked(bFind_MatchWhole);
  searchUp = new QCheckBox(tr("Search up")); _tab1->addWidget(searchUp); 
  if (bHiddenForward || bHiddenBackward){
    searchUp->setChecked(bHiddenBackward);
  } else {
    searchUp->setChecked(bFind_SearchUp);
  }
 // searchUp->setDisabled(true);
  regex = new QCheckBox(tr("Regular Expression")); _tab1->addWidget(regex);
  grid->addLayout(_tab1, 1, 0);

  QPushButton *p;
  p = new QPushButton(tr("&Find next"));
  grid->addWidget(p, 0, 2);
  connect(p, SIGNAL( clicked() ), this, SLOT(findNext()) );

  p = new QPushButton(tr("&Close"));
  grid->addWidget(p, 1, 2);//, AlignTop);
  connect(p, SIGNAL( clicked() ), this, SLOT(close()) );

  if (QApplication::desktop()->width() > 800){
    move(500, 30);
  } else {
    move(300, 30);
  }

  //move(QApplication::desktop()->width() / 2 - sizeHint().width() / 2, QApplication::desktop()->height() / 2 - sizeHint().height() / 2);
  if (!bHiddenForward && !bHiddenBackward){
    show(); 
  } else {
    findNext();
    if (bHiddenBackward){
      if (bHiddenBackwardFirst) findNext(); // just to go up
      bHiddenBackwardFirst = false;
    } else {
      bHiddenBackwardFirst = true;
    }
  }
  this->activateWindow();
  this->setFocus();

}

_find::~_find()
{
  if (bHiddenForward || bHiddenBackward){
    sHidden = search->currentText();  
  } else {
    bFind_MatchCase = matchCase->isChecked();
    bFind_MatchWhole = matchWhole->isChecked();
    bFind_SearchUp = searchUp->isChecked();
  }

  
}

void _find::findNext()
{
  bool bNotFoundAtAll = false;
  static QString sLastSearch = "";
goo:  
  qApp->processEvents();
  QString s = "";
  if (bHiddenForward || bHiddenBackward){
    s = sHidden;  
  } else {
    s = search->currentText();  
  }
  bool bMatchCase = matchCase->isChecked();
  bool bMatchWhole = matchWhole->isChecked();
  bool bSearchUp = searchUp->isChecked();
  bool bRegEx = regex->isChecked();

  QTextDocument *d = my_sourcecodeeditor->my_sourcecodeeditor_editor->document();
  QTextCursor c = my_sourcecodeeditor->my_sourcecodeeditor_editor->textCursor();

  int nFlag = 0;
  if (bMatchCase) nFlag |= QTextDocument::FindCaseSensitively;
  if (bMatchWhole) nFlag |= QTextDocument::FindWholeWords;
  if (bSearchUp) nFlag |= QTextDocument::FindBackward;

  if (bSearchUp){
    int k = c.selectedText().length();
    c.clearSelection();
    c.movePosition(QTextCursor::Left, QTextCursor::KeepAnchor, k);
  } 

  if (bRegEx){    
    c = d->find(QRegExp(s), c, (QTextDocument::FindFlag) nFlag);
  } else {
    c = d->find(s, c, (QTextDocument::FindFlag) nFlag);
  }
  
  if (c.hasSelection() == false){

    if (!bNotFoundAtAll && QMessageBox::question(bHiddenForward || bHiddenBackward ? (QWidget *) my_sourcecodeeditor : this, tr("Find"), 
      bSearchUp ?
      tr("Search for '%1' reached beginning of file.\nWould you like to start search from the end of the document?").arg(s)
      : 
      tr("Search for '%1' reached end of file.\nWould you like to start search from the beginning of the document?").arg(s),
//      tr("'%1' has not been found till end of file.\nWould you like to start search from the beginning?").arg(s), 
      
      QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
    {
      QTextCursor c = my_sourcecodeeditor->my_sourcecodeeditor_editor->textCursor();
      if (bSearchUp){
        c.movePosition(QTextCursor::End, QTextCursor::MoveAnchor);
        c.movePosition(QTextCursor::EndOfLine, QTextCursor::MoveAnchor);
      } else {
        c.movePosition(QTextCursor::Start, QTextCursor::MoveAnchor);
        c.movePosition(QTextCursor::StartOfLine, QTextCursor::MoveAnchor);
      }
      my_sourcecodeeditor->my_sourcecodeeditor_editor->setTextCursor(c);

      bNotFoundAtAll = true;

      goto goo;
    } else {
        if (sLastSearch != s) QMessageBox::information(this, tr("Replace"), 
          bSearchUp ?
          tr("'%1' has not been found until beginning of file.").arg(s)
          :
          tr("'%1' has not been found until end of file.").arg(s), 
          QMessageBox::Close);
    }    

   //   my_sourcecodeeditor->activateWindow();
    activateWindow();

  } else {
    sLastSearch = s;

    if (bSearchUp){
      int k = c.selectedText().length();
      c.clearSelection();
      c.movePosition(QTextCursor::Left, QTextCursor::KeepAnchor, k);
    } 
    my_sourcecodeeditor->my_sourcecodeeditor_editor->setTextCursor(c);

    QStringList::Iterator it = find_list.begin();
    if (find_list.count() == 0 || *it != s){
      if (s.trimmed().length()){
        search->insertItem(0, s);
        search->setCurrentIndex(0);
        find_list.prepend(s);
      }
    }
  }

  search->setFocus();
  my_sourcecodeeditor->activateWindow();
  if (bHiddenForward || bHiddenBackward) close();
}

void _find::close()
{
  accept();
}




