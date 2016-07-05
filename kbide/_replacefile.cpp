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

#include "_replacefile.h"
#include "_sourcecodeeditor.h"
#include "_sourcecodeeditor_editor.h"

#include "_mainwindow.h"
#include "_sourcecodeeditor.h"
#include "_sourcecodeeditor_editor.h"

#include "_replacefilelist.h"
#include "../kbshared/typedef.h"

extern _mainwindow *EXTERN_my_mainwindow;
extern _replacefilelist *EXTERN_replacefilelist;

extern QDockWidget *EXTERN_FileReplace;
extern QString sFindText;



QStringList replacefile_list;
QStringList replacefile_list2;

bool bReplaceFile_MatchCase = false;

_replacefile::_replacefile(QWidget *_parent) : QDialog(_parent)
{
  setAttribute(Qt::WA_DeleteOnClose);
  setWindowFlags(windowFlags() | Qt::Tool);

  setObjectName("ReplaceFile");
  
  QApplication::restoreOverrideCursor();
  QMessageBox::information(_parent, tr("Replace In File"),
      tr(
"File Replacement\n"
"\n"
"Watch out! There is no way to undo file replacements. So be sure about what you are doing "
"or what you want to replace. All project files will be searched and if the searched string is found, "
"it will modify the matched file and replace the occurance of that string.\n\n"
"Section of properties like in form files are ignored.\n\nUnsaved changes in opened files will be ignored."
)
    );

  QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

  my_mainwindow = (_mainwindow *) _parent;

  setWindowTitle(tr("Replace In File"));
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
  search->addItem("");
  search->setMinimumWidth(200);
  search->setEditable(true);
  search->setInsertPolicy(QComboBox::NoInsert);
  
  if (!sFindText.isEmpty() && !sFindText.contains(QString(QChar(0x2029)))){
    search->lineEdit()->setText(sFindText);
  }

  _tt->setStretchFactor(search, 10);

  for ( QStringList::Iterator it = replacefile_list.begin(); it != replacefile_list.end(); ++it ) {
     search->addItem(*it);      
  }
  setFocusProxy(search);


  QHBoxLayout *_tt2 = new QHBoxLayout();  
  grid->addLayout(_tt2, 1, 0);

  QLabel *l2;
  l2 = new QLabel(tr("Replace with:")); _tt2->addWidget(l2);
 
  search2 = new QComboBox(); _tt2->addWidget(search2);
  search2->addItem("");
  search2->setMinimumWidth(200);
  search2->setEditable(true);
  search2->setInsertPolicy(QComboBox::NoInsert);
  _tt2->setStretchFactor(search2, 10);

  if (!sFindText.isEmpty() && !sFindText.contains(QString(QChar(0x2029)))){
    setFocusProxy(search2);
  }

  QWidget::setTabOrder(search, search2);
  
  for ( QStringList::Iterator it = replacefile_list2.begin(); it != replacefile_list2.end(); ++it ) {
     search2->addItem(*it);      
  }
  
  QVBoxLayout *_tab1 = new QVBoxLayout();


  matchCase = new QCheckBox(tr("Match case")); _tab1->addWidget(matchCase);
  matchCase->setChecked(bReplaceFile_MatchCase);

  grid->addLayout(_tab1, 2, 0);

  QPushButton *p;
  p = new QPushButton(tr("&Replace In File"));
  grid->addWidget(p, 0, 2);
  connect(p, SIGNAL( clicked() ), this, SLOT(findNext()) );

  p = new QPushButton(tr("&Close"));
  grid->addWidget(p, 3, 2);//, AlignTop);
  connect(p, SIGNAL( clicked() ), this, SLOT(close()) );

  move(QApplication::desktop()->width() / 2 - sizeHint().width() / 2, QApplication::desktop()->height() / 2 - sizeHint().height() / 2);
  show();

  this->activateWindow();
  this->setFocus();
}

_replacefile::~_replacefile()
{
  bReplaceFile_MatchCase = matchCase->isChecked();
}

void _replacefile::findNext()
{
  static bool bLock = false;

  if (bLock) return;
  bLock = true;

  QString s = search->currentText();
  QString ss = search2->currentText();
  bool bMatchCase = matchCase->isChecked();

  search->setFocus();


  if (s.simplified().length() == 0){
    bLock = false;
    return;
  }
  if (ss.simplified().length() == 0){
    bLock = false;
    return;
  }

  QStringList::Iterator it = replacefile_list.begin();
  if (replacefile_list.count() == 0 || *it != s){
    if (s.trimmed().length()){
      search->insertItem(0, s);
      search->setCurrentIndex(0);
      replacefile_list.prepend(s);
    }
  }

  QStringList::Iterator it2 = replacefile_list2.begin();
  if (replacefile_list2.count() == 0 || *it2 != ss){
    if (ss.trimmed().length()){
      search2->insertItem(0, ss);
      search2->setCurrentIndex(0);
      replacefile_list2.prepend(ss);
    }
  }

  s = search->currentText();
  ss = search2->currentText();


  EXTERN_replacefilelist->clear();
  EXTERN_FileReplace->setHidden(false);  


  EXTERN_replacefilelist->addItem(tr("Searching..."));  ;  

  int nHits = 0;
  int nFileHits = 0;
  int nSearchFiles = 0;

  QDir thisDir( EXTERN_my_mainwindow->getProjectPath() );	
  QFileInfoList files = thisDir.entryInfoList();

  QString k = "";
  if ( files.size() ) {
      
     QFileInfo fi;
	    for (int i = 0; i < files.size(); ++i) {
	      fi = files.at(i);

        if (fi.fileName() == "." || fi.fileName() == "..")
		        ; // nothing
		    else if ( fi.isSymLink()) {  }
        else if ( fi.isDir() ){ } 
        else {

          EXTERN_my_mainwindow->processGUI(100);

          QString z = fi.absoluteFilePath();

          if (!(z.endsWith(".kbasic", Qt::CaseInsensitive) || z.endsWith(".kbasic_form", Qt::CaseInsensitive)
            || z.endsWith(".kbasic_class", Qt::CaseInsensitive) || z.endsWith(".kbasic_module", Qt::CaseInsensitive)
             || z.endsWith(".kbasic_menubar", Qt::CaseInsensitive) || z.endsWith(".kbasic_toolbar", Qt::CaseInsensitive))) continue;

          QFile f(z);
          if (!f.open(QFile::ReadOnly)){
             continue;
         }
         nSearchFiles++;

	       QTextStream t(&f);
         
         t.setCodec("UTF-8");
         t.setAutoDetectUnicode(true);
         t.setGenerateByteOrderMark(true);

         QString sText = t.readAll();
	       f.close();

         int yy = 0;
         QString sText2 = "";
        // ignore property entries
         /*
          if (!(z.endsWith(".kbasic", Qt::CaseInsensitive)
            || z.endsWith(".kbasic_class", Qt::CaseInsensitive) || z.endsWith(".kbasic_module", Qt::CaseInsensitive)
         //   || z.endsWith(".kbasic_menubar", Qt::CaseInsensitive) || z.endsWith(".kbasic_toolbar", Qt::CaseInsensitive)
            ))*/
          {
            int n = -1;
            if (z.endsWith(".kbasic_form", Qt::CaseInsensitive)) n = sText.indexOf("\nEnd Form"); 
            else if (z.endsWith(".kbasic_menubar", Qt::CaseInsensitive)) n = sText.indexOf("\nEnd MenuBar"); 
            else if (z.endsWith(".kbasic_toolbar", Qt::CaseInsensitive)) n = sText.indexOf("\nEnd ToolBar"); 

            if (n >= 0){
            //  n = sText.lastIndexOf("End", n); 
              n = sText.indexOf("\n", n);
              sText2 = sText.left(n);
              yy = (sText.left(n)).count(s, bMatchCase ? Qt::CaseSensitive : Qt::CaseInsensitive) + 1;
              sText = sText.mid(n + 1);
            }  
          }

         int y = sText.count(s, bMatchCase ? Qt::CaseSensitive : Qt::CaseInsensitive);
         nHits += y;

         int h = 0;
         int h2 = 0;
         int h3 = 0;

         for (int i = 0; i < y; i++){
           EXTERN_my_mainwindow->processGUI(100);

           if (i == 0){
             nFileHits++;
           } else {
             h++;
           }

          int nLine = 0;
          QString sHit = "";

           h = sText.indexOf(s, h, bMatchCase ? Qt::CaseSensitive : Qt::CaseInsensitive);
           h2 = sText.lastIndexOf("\n", h);
           if (h2 == -1) h2 = 0;
           h3 = sText.indexOf("\n", h);
           if (h3 == -1) h3 = sText.length();

           QString d = sText.left(h2);
           if (!d.isEmpty()) nLine = d.count("\n") + 1 - yy;
           sHit = sText.mid(h2 + 1, h3 - h2);

            k = k.sprintf("(%d): ", nLine + 1);
            k = k.prepend(z);
            k += sHit;

            EXTERN_replacefilelist->addItem(k);  
         }



            if (y){
        
              sText = sText.replace(s, ss, bMatchCase ? Qt::CaseSensitive : Qt::CaseInsensitive);
                
              QFile ff(z);
              if (!ff.open(QFile::WriteOnly | QFile::Truncate)){
                  continue;
              }

              QTextStream t(&ff);
              
              t.setCodec("UTF-8");
              t.setAutoDetectUnicode(true);
              t.setGenerateByteOrderMark(true);

              if (!sText2.isEmpty()) t << sText2;
              t << sText;

              ff.close();
       
            }

         
        }
      }
  }
	   

  QString sss = "";

  sss = tr("Completed Replacement!   Hits: %1       File Hits: %2        Changed Files: %3").arg(nHits).arg(nSearchFiles).arg(nFileHits);
  
  EXTERN_replacefilelist->addItem(sss); 
  
  

  QList<QMdiSubWindow *> l = EXTERN_my_mainwindow->workspace->subWindowList();
  for (int i = 0; i < l.size(); i++){

    QWidget *w = l.at(i)->widget();
    _sourcecodeeditor *o = 0;

    if ((o = qobject_cast<_sourcecodeeditor *>(w))){
      o->reloadAfterFileReplacement();
    }
  }

  accept();  
    
  bLock = false;

}

void _replacefile::close()
{
  accept();
}




