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


#include "_translation.h"
#include "_mainwindow.h"

#include "../kbshared/_menubar.h"
#include "../kbshared/_toolbar.h"
#include "../kbshared/_form.h"
#include "../kbshared/_report.h"

QStringList lAll;

bool bAccept;
bool bInitGerman = false;

QStringList trl;
QMap<QString, QStringList> trs;
QList<QTextEdit *> tes;

QString sCurrent;

extern _mainwindow *EXTERN_my_mainwindow;

_translation::_translation(QWidget* _parent) : QDialog(_parent)
{  
  sCurrent = "";

  tes.clear();
  trl.clear();
  trs.clear();


  QString s = EXTERN_my_mainwindow->getProjectPreference("Translation");
  trl = s.split(";");



  setAttribute(Qt::WA_DeleteOnClose);
  setWindowFlags(windowFlags() | Qt::Dialog);

  lAll.clear();

  bAccept = false;


  setWindowTitle(tr("Translation"));
  setModal(true);
  setMinimumWidth(500);

 
  QPushButton *p;
  QWidget *f;
  QHBoxLayout *fj;


  QVBoxLayout *j = new QVBoxLayout();
  
    setLayout(j);
    j->setMargin(5);
    j->setSpacing(0);


  QWidget *tt = new QWidget();
  tt->setFixedSize(1, 20);
  j->addWidget(tt);

  QHBoxLayout *jj = new QHBoxLayout();
  jj->setMargin(4);

  QLabel *l;
  l = new QLabel(tr("Select Language: ")); jj->addWidget(l);
  {
    QFont f = l->font();
    f.setBold(true);
    l->setFont(f);
  }

  lang = new QComboBox();
  lang->setMaximumWidth(200);
  
  jj->addWidget(lang);
  jj->setStretchFactor(lang, 99);
  if (trl.size()){
    foreach(QString m, trl){    
      if (!m.isEmpty()){
        lang->addItem(m);
      }
    }
  }
  if (lang->count() == 0){
    lang->addItem("German");
    bInitGerman = true;
  }

  if (!EXTERN_my_mainwindow->TRANSLATION->currentText().isEmpty()) lang->setCurrentIndex(lang->findText(EXTERN_my_mainwindow->TRANSLATION->currentText()));

  sCurrent = lang->currentText();

  connect(lang, SIGNAL(currentIndexChanged (const QString &)), this, SLOT(currentIndexChanged (const QString &))); 

  j->addLayout(jj);


  f = new QWidget();
  fj = new QHBoxLayout();
  f->setLayout(fj);
  j->addWidget(f);


  p = new QPushButton(tr("&Add"), f); fj->addWidget(p, Qt::AlignRight); p->setMaximumWidth(100);
  connect(p, SIGNAL( clicked() ), this, SLOT(add()) );

  p = new QPushButton(tr("&Remove"), f); fj->addWidget(p, Qt::AlignRight); p->setMaximumWidth(100);
  connect(p, SIGNAL( clicked() ), this, SLOT(remove()) );

  tt = new QWidget();
  tt->setFixedSize(1, 5);
  j->addWidget(tt);

  
  info = new QLabel();
  j->addWidget(info, Qt::AlignCenter);



  tt = new QWidget();
  tt->setFixedSize(1, 20);
  j->addWidget(tt);

  tab = new QTabWidget(); j->addWidget(tab);

  tab->setUsesScrollButtons(true);

  f = new QWidget();
  fj = new QHBoxLayout();
  f->setLayout(fj);
  j->addWidget(f);

 /*
  p = new QPushButton(tr("&Save"), f); fj->addWidget(p);
  connect(p, SIGNAL( clicked() ), this, SLOT(ok()) );
*/

  p = new QPushButton(tr("&Next (Ctrl + Return)"), f); fj->addWidget(p); p->setMaximumWidth(150);p->setShortcut(QKeySequence("Ctrl+Return"));// p->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_Right));
  connect(p, SIGNAL( clicked() ), this, SLOT(next()) );
  p->setMaximumSize(0, 0);

  p = new QPushButton(tr("&Mark (Ctrl + Space)"), f); fj->addWidget(p); p->setMaximumWidth(150); p->setShortcut(QKeySequence("Ctrl+Space"));
  connect(p, SIGNAL( clicked() ), this, SLOT(mark()) );
  p->setMaximumSize(0, 0);

  l = new QLabel(tr("Next (Ctrl + Return)"), f); fj->addWidget(l);
  l = new QLabel(tr("Mark (Ctrl + Space)"), f); fj->addWidget(l);



  f = new QWidget();
  fj = new QHBoxLayout();
  f->setLayout(fj);
  j->addWidget(f);

 /*
  p = new QPushButton(tr("&Save"), f); fj->addWidget(p); p->setMaximumWidth(100);
  connect(p, SIGNAL( clicked() ), this, SLOT(ok()) );
*/

  p = new QPushButton(tr("&Close"), f); fj->addWidget(p); p->setMaximumWidth(150);
  connect(p, SIGNAL( clicked() ), this, SLOT(cancel()) );

  setupWindow();  
  setupRecord();  

  QString sName = EXTERN_my_mainwindow->first();

  if (!sName.isEmpty()){
    do {

      bool b = false;
      QString s = "";
      QString sAllText = "";

      if (sName.endsWith(".kbasic_class", Qt::CaseInsensitive) || sName.endsWith(".kbasic_module", Qt::CaseInsensitive) || sName.endsWith(".kbasic", Qt::CaseInsensitive)){
        EXTERN_my_mainwindow->loadStringFromFile(sName, s);
        b = true;
      } else if (sName.endsWith(".kbasic_report", Qt::CaseInsensitive)){        
        s = _form::getFormClassSourceCode(sName, sAllText, false);
        b = true;
      } else if (sName.endsWith(".kbasic_menubar", Qt::CaseInsensitive)){
        s = _menubar::getMenuBarClassSourceCode(sName, sAllText, false);
        b = true;
      } else if (sName.endsWith(".kbasic_toolbar", Qt::CaseInsensitive)){
        s = _toolbar::getToolBarClassSourceCode(sName, sAllText, false);
        b = true;
      } else if (sName.endsWith(".kbasic_form", Qt::CaseInsensitive)){
        s = _form::getFormClassSourceCode(sName, sAllText, false);
        b = true;
      }  
      QStringList l = parseStrings(s);
      if (b) b = l.size() > 0;
      if (b){

        QWidget *g = new QWidget();

        QVBoxLayout *j = new QVBoxLayout();
        g->setLayout(j);
        QScrollArea *aa = new QScrollArea(this);
        aa->setFrameShape(QFrame::NoFrame);
        aa->setWidget(g);
        aa->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        aa->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded); 
        aa->setWidgetResizable(true);

        int y = 0;
        QGridLayout *a;

        QTextEdit *la;
        QTextEdit *d;
        
        a = new QGridLayout();  
        j->addLayout(a);

        foreach(QString m, l){
          
          la = new QTextEdit(m); a->addWidget(la, y, 0);
          la->setReadOnly(true);
          la->setFocusPolicy(Qt::NoFocus);
          la->setFrameStyle(QFrame::NoFrame);
          QPalette p = la->palette();
          QColor c = QColor(0, 0, 0, 0);
          p.setColor(QPalette::Window, c);  
          p.setColor(QPalette::Base, c);  
          p.setColor(QPalette::Button, c);            
          la->setPalette(p);

          d = new QTextEdit(); a->addWidget(d, y++, 1); d->setObjectName(la->toPlainText());          
          d->setProperty("QScrollArea", QVariant((int) aa));
          connect(d, SIGNAL(textChanged()), this, SLOT(textChanged())); d->setTabChangesFocus(true); tes.append(d);
          
        }

        tab->addTab(aa, EXTERN_my_mainwindow->getFilenameWithoutPathAndExtension(sName)); 
      }

      sName = EXTERN_my_mainwindow->next();

    } while (sName.length());     
  }


  if (trl.size()){
    foreach(QString m, trl){    
      if (!m.isEmpty()){
        QString r = EXTERN_my_mainwindow->getProjectPath() + "/" + m + ".kbasic_translation";
        if (QFile::exists(r)){
          EXTERN_my_mainwindow->loadStringFromFile(r, s);      
        }
      }
    }
  }


  updateInfo();
  load();

  
  
  
  move(QApplication::desktop()->width() / 2 - sizeHint().width() / 2, QApplication::desktop()->height() / 2 - sizeHint().height() / 2);
  show();
  bAccept = true;
  qApp->setActiveWindow(this);
  
}

QStringList _translation::parseStrings(QString s)
{
  
  QStringList l;
  int n = 0;
  int n2 = 0;

  do {
    n = s.indexOf("\"", n);
    if (n >= 0){
      n2 = s.indexOf("\"", n + 1);
      if (n2 >= 0){
        QString k = s.mid(n + 1, n2 - n - 1);
        if (!k.simplified().isEmpty()){
          if (k != "="){
            if (!lAll.contains(k)){
              l.append(k);        
              lAll.append(k);        
            }
          }
        }
      } else break;
    } else break;
    n = n2 + 1;
  } while (n2 >= 0);

  return l;
}

void _translation::setupWindow()
{

  QWidget *g = new QWidget();

  QVBoxLayout *j = new QVBoxLayout();
  g->setLayout(j);
  QScrollArea *aa = new QScrollArea(this);
  aa->setFrameShape(QFrame::NoFrame);
  aa->setWidget(g);
  aa->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
  aa->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded); 
  aa->setWidgetResizable(true);


  bool t = false;


  QGridLayout *a;

  QTextEdit *d;
  int y = 0;

  a = new QGridLayout();  
  j->addLayout(a);
  QLabel *l;
  l = new QLabel(tr("&Window")); a->addWidget(l, y, 0);
  Window = d = new QTextEdit(); a->addWidget(d, y++, 1); d->setObjectName(l->text());
  connect(d, SIGNAL(textChanged()), this, SLOT(textChanged())); d->setTabChangesFocus(true); tes.append(d);

  if (bInitGerman) d->setPlainText("&Fenster");


  l = new QLabel(tr("&Help")); a->addWidget(l, y, 0);
  Help = d = new QTextEdit(); a->addWidget(d, y++, 1);  d->setObjectName(l->text());
  connect(d, SIGNAL(textChanged()), this, SLOT(textChanged())); d->setTabChangesFocus(true); tes.append(d);
  

  if (bInitGerman) d->setPlainText("&Hilfe");

  l = new QLabel(tr("C&ontents")); a->addWidget(l, y, 0);
  Contents = d = new QTextEdit(); a->addWidget(d, y++, 1); d->setObjectName(l->text());
  connect(d, SIGNAL(textChanged()), this, SLOT(textChanged())); d->setTabChangesFocus(true); tes.append(d);
  
  if (bInitGerman) d->setPlainText("&Inhalt");

  l = new QLabel(tr("A&bout")); a->addWidget(l, y, 0);
  About = d = new QTextEdit(); a->addWidget(d, y++, 1); d->setObjectName(l->text());
  connect(d, SIGNAL(textChanged()), this, SLOT(textChanged())); d->setTabChangesFocus(true); tes.append(d);
  
  if (bInitGerman) d->setPlainText("Ü&ber...");

  l = new QLabel(tr("Cl&ose")); a->addWidget(l, y, 0);
  Close = d = new QTextEdit(); a->addWidget(d, y++, 1); d->setObjectName(l->text());
  connect(d, SIGNAL(textChanged()), this, SLOT(textChanged())); d->setTabChangesFocus(true); tes.append(d);
  
  if (bInitGerman) d->setPlainText("Schl&ießen");

  l = new QLabel(tr("Close &All")); a->addWidget(l, y, 0);
  CloseAll = d = new QTextEdit(); a->addWidget(d, y++, 1); d->setObjectName(l->text());
  connect(d, SIGNAL(textChanged()), this, SLOT(textChanged())); d->setTabChangesFocus(true); tes.append(d);
  
  if (bInitGerman) d->setPlainText("&Alle schließen");

  l = new QLabel(tr("&Tile")); a->addWidget(l, y, 0);
  Tile = d = new QTextEdit(); a->addWidget(d, y++, 1); d->setObjectName(l->text());
  connect(d, SIGNAL(textChanged()), this, SLOT(textChanged())); d->setTabChangesFocus(true); tes.append(d);
  
  if (bInitGerman) d->setPlainText("&Teilen");

  l = new QLabel(tr("&Cascade")); a->addWidget(l, y, 0);
  Cascade = d = new QTextEdit(); a->addWidget(d, y++, 1); d->setObjectName(l->text());
  connect(d, SIGNAL(textChanged()), this, SLOT(textChanged())); d->setTabChangesFocus(true); tes.append(d);
  
  if (bInitGerman) d->setPlainText("&Anordnen");
 
  l = new QLabel(tr("Ne&xt")); a->addWidget(l, y, 0);
  Next = d = new QTextEdit(); a->addWidget(d, y++, 1); d->setObjectName(l->text());
  connect(d, SIGNAL(textChanged()), this, SLOT(textChanged())); d->setTabChangesFocus(true); tes.append(d);

  if (bInitGerman) d->setPlainText("N&ächstes Fenster");

  l = new QLabel(tr("Pre&vious")); a->addWidget(l, y, 0);
  Previous = d = new QTextEdit(); a->addWidget(d, y++, 1); d->setObjectName(l->text());
  connect(d, SIGNAL(textChanged()), this, SLOT(textChanged())); d->setTabChangesFocus(true); tes.append(d);
  
  if (bInitGerman) d->setPlainText("Vorheri&ges Fenster");


  QWidget *f = new QWidget(); j->addWidget(f);
  QHBoxLayout *fj = new QHBoxLayout();
  f->setLayout(fj);
  


  tab->addTab(aa, tr("Window"));  
}

void _translation::setupRecord()
{
  QWidget *g = new QWidget();

  QVBoxLayout *j = new QVBoxLayout();
  g->setLayout(j);
  QScrollArea *aa = new QScrollArea(this);
  aa->setFrameShape(QFrame::NoFrame);
  aa->setWidget(g);
  aa->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
  aa->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded); 
  aa->setWidgetResizable(true);



  bool t = false;


  QString en = _mainwindow::locale();
  bool b = false;
  if (en == "de"){
    b = true;
  }

  QGridLayout *a;

  QTextEdit *d;

  int y = 0;

  a = new QGridLayout();  
  j->addLayout(a);
  QLabel *l;
  l = new QLabel(tr("&Records")); a->addWidget(l, y, 0);
  Records = d = new QTextEdit(); a->addWidget(d, y++, 1); d->setObjectName(l->text());
  connect(d, SIGNAL(textChanged()), this, SLOT(textChanged())); d->setTabChangesFocus(true); tes.append(d);

  if (bInitGerman) d->setPlainText("&Datensätze");

  l = new QLabel(tr("&Requery")); a->addWidget(l, y, 0);
  Requery = d = new QTextEdit(); a->addWidget(d, y++, 1); d->setObjectName(l->text());
  connect(d, SIGNAL(textChanged()), this, SLOT(textChanged())); d->setTabChangesFocus(true); tes.append(d);

  if (bInitGerman) d->setPlainText("&Aktualisieren");

  l = new QLabel(tr("Add &New")); a->addWidget(l, y, 0);
  AddNew = d = new QTextEdit(); a->addWidget(d, y++, 1); d->setObjectName(l->text());
  connect(d, SIGNAL(textChanged()), this, SLOT(textChanged())); d->setTabChangesFocus(true); tes.append(d);

  if (bInitGerman) d->setPlainText("Neu &hinzufügen");

  l = new QLabel(tr("&Update")); a->addWidget(l, y, 0);
  Update = d = new QTextEdit(); a->addWidget(d, y++, 1); d->setObjectName(l->text());
  connect(d, SIGNAL(textChanged()), this, SLOT(textChanged())); d->setTabChangesFocus(true); tes.append(d);

  if (bInitGerman) d->setPlainText("&Speichern...");

  l = new QLabel(tr("&Delete")); a->addWidget(l, y, 0);
  Delete = d = new QTextEdit(); a->addWidget(d, y++, 1); d->setObjectName(l->text());
  connect(d, SIGNAL(textChanged()), this, SLOT(textChanged())); d->setTabChangesFocus(true); tes.append(d);

  if (bInitGerman) d->setPlainText("&Löschen");

  l = new QLabel(tr("&Seek")); a->addWidget(l, y, 0);
  Seek = d = new QTextEdit(); a->addWidget(d, y++, 1); d->setObjectName(l->text());
  connect(d, SIGNAL(textChanged()), this, SLOT(textChanged())); d->setTabChangesFocus(true); tes.append(d);
  
  if (bInitGerman) d->setPlainText("&Suchen");

  l = new QLabel(tr("&Add Filter")); a->addWidget(l, y, 0);
  AddFilter = d = new QTextEdit(); a->addWidget(d, y++, 1); d->setObjectName(l->text());
  connect(d, SIGNAL(textChanged()), this, SLOT(textChanged())); d->setTabChangesFocus(true); tes.append(d);
  
  if (bInitGerman) d->setPlainText("&Auswahlbasierter Filter hinzufügen");

  l = new QLabel(tr("Add &NotFilter")); a->addWidget(l, y, 0);
  AddNotFilter = d = new QTextEdit(); a->addWidget(d, y++, 1); d->setObjectName(l->text());
  connect(d, SIGNAL(textChanged()), this, SLOT(textChanged())); d->setTabChangesFocus(true); tes.append(d);
  
  if (bInitGerman) d->setPlainText("Auswahlau&schließender Filter hinzufügen");

  l = new QLabel(tr("&Set Filter")); a->addWidget(l, y, 0);
  SetFilter = d = new QTextEdit(); a->addWidget(d, y++, 1); d->setObjectName(l->text());
  connect(d, SIGNAL(textChanged()), this, SLOT(textChanged())); d->setTabChangesFocus(true); tes.append(d);
  
  if (bInitGerman) d->setPlainText("Filter &setzen");

  l = new QLabel(tr("Set &NotFilter")); a->addWidget(l, y, 0);
  SetNotFilter = d = new QTextEdit(); a->addWidget(d, y++, 1); d->setObjectName(l->text());
  connect(d, SIGNAL(textChanged()), this, SLOT(textChanged())); d->setTabChangesFocus(true); tes.append(d);
  
  if (bInitGerman) d->setPlainText("Auswahlauschließender F&ilter setzen");

  l = new QLabel(tr("&Clear Filter")); a->addWidget(l, y, 0);
  ClearFilter = d = new QTextEdit(); a->addWidget(d, y++, 1); d->setObjectName(l->text());
  connect(d, SIGNAL(textChanged()), this, SLOT(textChanged())); d->setTabChangesFocus(true); tes.append(d);
  
  if (bInitGerman) d->setPlainText("Filter &zurücksetzen");

  l = new QLabel(tr("Sort Ascen&ding")); a->addWidget(l, y, 0);
  SortAscending = d = new QTextEdit(); a->addWidget(d, y++, 1); d->setObjectName(l->text());
  connect(d, SIGNAL(textChanged()), this, SLOT(textChanged())); d->setTabChangesFocus(true); tes.append(d);
  
  if (bInitGerman) d->setPlainText("Aufsteigend sor&tieren");

  l = new QLabel(tr("Sort Desce&nding")); a->addWidget(l, y, 0);
  SortDescending = d = new QTextEdit(); a->addWidget(d, y++, 1); d->setObjectName(l->text());
  connect(d, SIGNAL(textChanged()), this, SLOT(textChanged())); d->setTabChangesFocus(true); tes.append(d);
  
  if (bInitGerman) d->setPlainText("Absteigend sort&ieren");



  l = new QLabel(tr("New Record")); a->addWidget(l, y, 0);
  d = new QTextEdit(); a->addWidget(d, y++, 1); d->setObjectName(l->text());
  connect(d, SIGNAL(textChanged()), this, SLOT(textChanged())); d->setTabChangesFocus(true); tes.append(d);
  if (bInitGerman) d->setPlainText("Neuer Datensatz");

  l = new QLabel(tr("Would you like to save this new record (else changes will be lost)?")); a->addWidget(l, y, 0);
  d = new QTextEdit(); a->addWidget(d, y++, 1); d->setObjectName(l->text());
  connect(d, SIGNAL(textChanged()), this, SLOT(textChanged())); d->setTabChangesFocus(true); tes.append(d);
  if (bInitGerman) d->setPlainText("Möchten diesen neuen Datensatz speichern?");

  l = new QLabel(tr("Current Record Changed")); a->addWidget(l, y, 0);
  d = new QTextEdit(); a->addWidget(d, y++, 1); d->setObjectName(l->text());
  connect(d, SIGNAL(textChanged()), this, SLOT(textChanged())); d->setTabChangesFocus(true); tes.append(d);
  if (bInitGerman) d->setPlainText("Aktueller Datensatz geändert");

  l = new QLabel(tr("Would you like to save the changes?")); a->addWidget(l, y, 0);
  d = new QTextEdit(); a->addWidget(d, y++, 1); d->setObjectName(l->text());
  connect(d, SIGNAL(textChanged()), this, SLOT(textChanged())); d->setTabChangesFocus(true); tes.append(d);
  if (bInitGerman) d->setPlainText("Möchten Sie die Änderungen speichern?");

  l = new QLabel(tr("New Record")); a->addWidget(l, y, 0);
  d = new QTextEdit(); a->addWidget(d, y++, 1); d->setObjectName(l->text());
  connect(d, SIGNAL(textChanged()), this, SLOT(textChanged())); d->setTabChangesFocus(true); tes.append(d);
  if (bInitGerman) d->setPlainText("Neuer Datensatz");

  l = new QLabel(tr("Delete Current Record")); a->addWidget(l, y, 0);
  d = new QTextEdit(); a->addWidget(d, y++, 1); d->setObjectName(l->text());
  connect(d, SIGNAL(textChanged()), this, SLOT(textChanged())); d->setTabChangesFocus(true); tes.append(d);
  if (bInitGerman) d->setPlainText("Aktuellen Datensatz löschen");

  l = new QLabel(tr("Would you like to delete the current record?")); a->addWidget(l, y, 0);
  d = new QTextEdit(); a->addWidget(d, y++, 1); d->setObjectName(l->text());
  connect(d, SIGNAL(textChanged()), this, SLOT(textChanged())); d->setTabChangesFocus(true); tes.append(d);
  if (bInitGerman) d->setPlainText("Möchten Sie den aktuellen Datensatz löschen?");

  l = new QLabel(tr("Delete Record")); a->addWidget(l, y, 0);
  d = new QTextEdit(); a->addWidget(d, y++, 1); d->setObjectName(l->text());
  connect(d, SIGNAL(textChanged()), this, SLOT(textChanged())); d->setTabChangesFocus(true); tes.append(d);
  if (bInitGerman) d->setPlainText("Datensatz löschen");


  





  QWidget *f = new QWidget(); j->addWidget(f);
  QHBoxLayout *fj = new QHBoxLayout();
  f->setLayout(fj);

  
  


  tab->addTab(aa, tr("Records"));  

}

void _translation::remove()
{

  QString s = lang->currentText();

	  switch( QMessageBox::question( this, tr("Delete current selected language"), 
	      tr("Do you really want to delete %1? All translation data will be lost.").arg( s ),
	      QMessageBox::Yes | QMessageBox::No )){
	    case QMessageBox::Yes:
	        {
            lang->removeItem(lang->findText(s));
            lang->setCurrentIndex(0);
          }
	        break;    

	  }
}

void _translation::add()
{
  bool b;
  QString text = QInputDialog::getText(this, tr("New Language"), tr("Enter the name of the new language:"), QLineEdit::Normal, QString::null, &b);
  if (b && !text.isEmpty()){
    lang->addItem(text);
    lang->setCurrentIndex(lang->findText(text));

    foreach(QTextEdit *te, tes){
      te->setPlainText("");      
    }

  }
}

void _translation::next()
{
  bool bDone = false;
  bool bSecond = false;
re:
  QWidget *o = focusWidget();
  if (o && qobject_cast<QTextEdit *>(o)){
    QTextEdit *e = (QTextEdit *) o;
    bool b = false;
    foreach(QTextEdit *te, tes){
      if (bSecond) b = true;
      if (b == true && te->toPlainText().isEmpty()){
        QScrollArea *aa = (QScrollArea *) te->property("QScrollArea").toInt();
        tab->setCurrentWidget(aa);
        te->setFocus();
        aa->ensureWidgetVisible(te, 50, 200);
        aa->ensureWidgetVisible(te, 50, 50);
        bDone = true;
        break;
      }
      if (te == e){
        b = true;
      }
    }
    if (bDone == false && bSecond == false){
      bSecond = true;
      goto re;
    }
  }
}

void _translation::mark()
{
  QWidget *o = this->focusWidget();
  if (o && qobject_cast<QTextEdit *>(o)){
    QTextEdit *e = (QTextEdit *) o;
    e->setPlainText(" ");
    next();

  }

}

void _translation::currentIndexChanged  ( const QString & text ) 
{  
  save();
  load();
  updateInfo();
  sCurrent = text;
}

void _translation::updateInfo()
{
  int n = 0;
  int nAll = 0;
  foreach(QTextEdit *te, tes){
    nAll++;
    if (te->toPlainText().isEmpty()){
      n++;
    }
  }
  info->setText(QString(tr("   Phrases to translate = %1        Total phrases = %2")).arg(n).arg(nAll));
}

void _translation::textChanged()
{
  QObject *o = this->sender();
  if (o && qobject_cast<QTextEdit *>(o)){
    QTextEdit *e = (QTextEdit *) o;
    QString s = e->toPlainText();
    QString m = s;
    s = s.simplified();
    if (!s.isEmpty() || m == " "){
      QPalette p = e->palette();
      QColor c = Qt::lightGray;
      p.setColor(QPalette::Window, c);  
      p.setColor(QPalette::Base, c);  
      p.setColor(QPalette::Button, c);            
      e->setPalette(p);
    } else {
      QPalette p = e->palette();
      QColor c = Qt::white;
      p.setColor(QPalette::Window, c);  
      p.setColor(QPalette::Base, c);  
      p.setColor(QPalette::Button, c);            
      e->setPalette(p);
    }
  }
  updateInfo();
}

void _translation::load ( )
{
  QString s = "";
  QString r = EXTERN_my_mainwindow->getProjectPath() + "/" + lang->currentText() + ".kbasic_translation";
  if (QFile::exists(r)){
    EXTERN_my_mainwindow->loadStringFromFile(r, s);      

    QStringList l = s.split("\n");

    foreach(QString m, l){
      int n = m.indexOf("=");
      if (n >= 0){
        QString k = m.left(n);
        if (k.contains("!\"§$%&/()")){
          k = k.replace("!\"§$%&/()", "=");
        }
        QString v = m.mid(n + 1);

        foreach(QTextEdit *te, tes){
          QString kk = te->objectName();
          if (kk == k){
            te->setPlainText(v);
          }
        }
      }
    }

    updateInfo();
  }
}

void _translation::save ( )
{
  QString s = "";
  foreach(QTextEdit *te, tes){

    QString k = te->objectName();
    if (k.contains("=")){
      k = k.replace("=", "!\"§$%&/()");
    }
    if (!k.isEmpty()){
      QString v = te->toPlainText();
      s += k;
      s += "=";
      s += v;
      s += "\n";
    }
  }

  QString r = EXTERN_my_mainwindow->getProjectPath() + "/" + sCurrent + ".kbasic_translation";
  EXTERN_my_mainwindow->saveStringInFile(r, s);      

}


void _translation::closeEvent ( QCloseEvent * e )
{
  QString s = "";
  for (int i = 0; i < lang->count(); i++){
    s += lang->itemText(i);
    s += ";";
  }
  EXTERN_my_mainwindow->setProjectPreference("Translation", s);
  EXTERN_my_mainwindow->saveProjectPreferences();
  
  save();
 QString q = EXTERN_my_mainwindow->TRANSLATION->currentText();
 EXTERN_my_mainwindow->bProjectLoading = true; // blocking

  EXTERN_my_mainwindow->TRANSLATION->clear();
  EXTERN_my_mainwindow->TRANSLATION->addItem("");

  s = EXTERN_my_mainwindow->getProjectPreference("Translation");
  trl = s.split(";");

  if (trl.size()){
    foreach(QString m, trl){    
      if (!m.isEmpty()){
        EXTERN_my_mainwindow->TRANSLATION->addItem(m);
      }
    }
  }
 
 EXTERN_my_mainwindow->TRANSLATION->setCurrentIndex(EXTERN_my_mainwindow->TRANSLATION->findText(q));

 EXTERN_my_mainwindow->bProjectLoading = false; 

  e->accept();
  
}


void _translation::cancel()
{
  close();
}
