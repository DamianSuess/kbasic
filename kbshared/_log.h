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

#ifndef _log_H
#define _log_H


#include "../kbshared/typedef.h"
//#include "../kbshared/_sql_syntaxhighlighter.h"

#include <QTextEdit>

extern QString highlightSQL(QString);
extern QTextEdit *log_te;

class _log : public QTextEdit
{ 
public:

  _log(QWidget *parent = 0) : QTextEdit(parent)
  {
    //setAttribute(Qt::WA_DeleteOnClose);

    setWindowTitle(QObject::tr("Log"));  

    resize(640, 480);

    setGeometry(QApplication::desktop()->width() / 2 - width() / 2, QApplication::desktop()->height() / 2 - height() / 2, width(), height());

    setReadOnly(true);

    //bOpenAutomatically = false;
    log_te = this;
   //_sql_syntaxhighlighter *highlighter = new _sql_syntaxhighlighter(document());

  }


    void closeEvent ( QCloseEvent * event )
    {
      hide();
      event->ignore();
    }

    static QString toHtml()
    {
      return log_te->toHtml();
    }

    static void METHOD_Print(QString s)
    {
      if (log_te->isVisible() == false) log_te->show();
      
      QTextCursor c = log_te->textCursor();
      c.movePosition(QTextCursor::End);
      log_te->setTextCursor(c);

      log_te->insertPlainText(s + "\n");
      log_te->ensureCursorVisible();  
    }

    static void METHOD_PrintHtml(QString s)
    {
      if (log_te->isVisible() == false) log_te->show();

      QTextCursor c = log_te->textCursor();
      c.movePosition(QTextCursor::End);
      log_te->setTextCursor(c);

      log_te->insertHtml(s + "<br>");
      log_te->ensureCursorVisible();  
    }

    static void METHOD_PrintSql(QString s)
    {

      if (log_te->isVisible() == false) log_te->show();

      s = highlightSQL(s);

      QTextCursor c = log_te->textCursor();
      c.movePosition(QTextCursor::End);
      log_te->setTextCursor(c);

      log_te->insertHtml(s + "<br>");
      log_te->ensureCursorVisible();  
    }

    static void METHOD_Show()
    {
      log_te->show();
    }

    static void METHOD_ShowMaximized()
    {
      log_te->showMaximized();
    }

    static void METHOD_ShowMinimized()
    {
      log_te->showMinimized();
    }

    static void METHOD_Hide()
    {
      log_te->hide();
    }

    static void METHOD_Clear()
    {
      log_te->clear();
    }
private:

 

};




#endif