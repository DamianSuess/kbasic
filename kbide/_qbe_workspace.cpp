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
#include <QtSql>


#include "_qbe_workspace.h"
#include "_qbe_table.h"

extern QSqlDatabase CurrentDatabase;





_qbe_workspace::_qbe_workspace(bool _bEdit) : QWorkspace()
{
  bEdit = _bEdit;

  nSelectedRule = -1;
  installEventFilter(this);

}

_qbe_workspace::~_qbe_workspace()
{
  RelationRules.clear();
}



QPoint _qbe_workspace::getPointFor(_qbe_table *o, int nIndex)
{
  int x0 = o->parentWidget()->x();
  int y0 = o->parentWidget()->y();

  int x1 = o->x();
  int y1 = o->y();

  QListWidgetItem *l = o->item(nIndex);

  QRect r = o->visualItemRect(l);
  int x2 = r.x();
  int y2 = r.y() - 4 + r.height();

  int xx = x0 + x1 + x2;
  int yy = y0 + y1 + y2;
  if (yy < y0 ){
    yy = y0;
  }
  if (yy > y0 + o->parentWidget()->height() - 5){
    yy = y0 + o->parentWidget()->height() - 5;
  }
  return QPoint(xx, yy);
}

void  _qbe_workspace::paintEvent(QPaintEvent *e)
{
  QPainter p( this );
  

  for (int i = 0; i < RelationRules.size(); ++i) {
    RelationRule &r = RelationRules[i];

    QPoint a = getPointFor(r.oSource, r.nSourceIndex);
    QPoint b = getPointFor(r.oDestination, r.nDestinationIndex);

    int xxx = a.x();
    int yyy = a.y();

    int xx = b.x();
    int yy = b.y();

    bool bb = xxx < xx;
    int x3 = xx - 20 + (bb ? 0 : r.oDestination->parentWidget()->width() + 32);
    int y3 = yy;

    p.setPen(Qt::black);

    
    int x4 = xxx - 20;
    int y4 = yyy;

    p.setPen(Qt::black);

    int points[] = {x4 - 2, y4 - 2, x4 + 2, y4 + 2, x3 + 2, y3 + 2, x3 - 2, y3 - 2};
    QPolygon polygon;
    polygon.setPoints(4, points);
    
    r.region = QRegion(polygon);

    if (bb){      
      p.drawLine(x3, y3, xx - 5, yy);
      p.drawLine(x3 + 5, y3 - 5, xx - 5, yy);
      p.drawLine(x3 + 5, y3 + 5, xx - 5, yy);
    } else {
      xx += r.oDestination->parentWidget()->width() - 10;
      p.drawLine(x3, y3, xx + 5, yy);
      p.drawLine(x3 - 5, y3 + 5, xx + 5, yy);
      p.drawLine(x3 - 5, y3 - 5, xx + 5, yy);
    }

    if (nSelectedRule == i){
      QPen ppp = p.pen();
      ppp.setWidth(2);
      p.setPen(ppp);
    }
    p.drawLine(x4, y4, x3, y3); // actually the line

    p.setPen(Qt::white);
    p.drawText(x4, y4, "1:n");
    p.setPen(Qt::black);
    p.drawText(x4 - 1, y4 - 1, "1:n");

    p.drawLine(x4, y4, xxx - 5, yyy);


    if (!r.sForeignKeyReplacement.isEmpty()){
      int xxq = (x4 - x3) / 2 + x3 - 20;
      int yyq = (y4 - y3) / 2 + y3;

      p.setPen(Qt::white);
      p.drawText(xxq, yyq, r.sForeignKeyReplacement);
      p.setPen(Qt::blue);
      p.drawText(xxq - 1, yyq - 1, r.sForeignKeyReplacement);
      
      
    }
  }

}

bool _qbe_workspace::eventFilter(QObject *obj, QEvent *event)
{
  if (event->type() == QEvent::Move || event->type() == QEvent::Resize){
    update();
  }
  return QObject::eventFilter(obj, event);
}

void  _qbe_workspace::mouseReleaseEvent(QMouseEvent *e)
{
  if (!bEdit) return;
  
  for (int i = 0; i < RelationRules.size(); ++i) {
    RelationRule r = RelationRules.at(i);
   
    if (r.region.contains(e->pos())){
      nSelectedRule = i;
      update();
      return;
    }

  }
  nSelectedRule = -1;
  update();

}


void  _qbe_workspace::mouseDoubleClickEvent(QMouseEvent *e)
{
  if (!bEdit) return;

  //if (CurrentDatabase.open())
  {
    if (nSelectedRule >= 0 && nSelectedRule < RelationRules.size()){
      QStringList items;

      RelationRule &r = RelationRules[nSelectedRule];

      QString sTable = r.sDestinationName;
      
      QSqlRecord rr = CurrentDatabase.record(sTable);
        for (int i = 0; i < rr.count(); ++i){
          if (rr.fieldName(i) == "kbrecordid") continue;

          items << rr.fieldName(i);
        }

      bool ok;
      QString item = QInputDialog::getItem(this, tr("Foreign Key"),
                tr("Enter the name of the field instead of the foreign key:"), items, 0, false, &ok);
      if (ok && !item.isEmpty()){
        r.sForeignKeyReplacement = item;
      }

    }
  }
}


