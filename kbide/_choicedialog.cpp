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

#include "_choicedialog.h"
#include "_mainwindow.h"
#include "../kbshared/typedef.h"


QString sSet;
QString sGet;

_choicedialog::_choicedialog(QWidget* _parent, QString _sAllowed) : QDialog(_parent)
{
  setAttribute(Qt::WA_DeleteOnClose);
  setWindowFlags(windowFlags() | Qt::Tool);

  QVBoxLayout *j = new QVBoxLayout();
  setLayout(j);

  QWidget *g = new QWidget();

  QVBoxLayout *jj = new QVBoxLayout();
  g->setLayout(jj);
  QScrollArea *a = new QScrollArea(this);
  a->setWidget(g);
  a->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
  a->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded); 
  a->setWidgetResizable(true);

  QStringList l;
  if (_sAllowed.contains(";")) l = _sAllowed.split(";");
  else if (_sAllowed.contains(",")) l = _sAllowed.split(",");
  
  for (int i = 0; i < l.size(); i++){   
    
    pref[l.at(i)] = new QCheckBox(l.at(i), g); 
    QCheckBox *c = pref[l.at(i)];
    jj->addWidget(c);
    c->setChecked(sSet.contains(l.at(i)));
  }

  j->addWidget(a);

  setWindowTitle(tr("Selectable Properties"));
  setModal(true);
  
  QWidget *f = new QWidget();
  QHBoxLayout *fj = new QHBoxLayout();
  f->setLayout(fj);
  j->addWidget(f);
 
  QPushButton *p;

  p = new QPushButton(tr("&Ok"), f); fj->addWidget(p);
  connect(p, SIGNAL( clicked() ), this, SLOT(performClose()) );
 
  move(QApplication::desktop()->width() / 2 - sizeHint().width() / 2, QApplication::desktop()->height() / 2 - sizeHint().height() / 2);
  
  qApp->setActiveWindow(this);

  exec();
  
}

void _choicedialog::performClose()
{
  sGet = "";

  QMap<QString, QCheckBox*>::Iterator it;
  for ( it = pref.begin(); it != pref.end(); ++it ) {
    QString sKey = it.key();
    QCheckBox *c = *it;
    if (c->checkState() == Qt::Checked){ 
      sGet += sKey;
      sGet += ";";
    }
  }
  close();  
}  

QString _choicedialog::get(QString _sAllowed, QString _sSet)
{
  sSet = _sSet;
  sGet = "";

  _choicedialog *d = new _choicedialog(EXTERN_my_mainwindow, _sAllowed);

  return sGet;
}