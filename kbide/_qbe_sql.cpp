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


#include "_qbe_sql.h"
#include "_qbe_sql_syntaxhighlighter.h"


_qbe_sql::_qbe_sql(QWidget *parent) : QTextEdit(parent)
{
  setAttribute(Qt::WA_DeleteOnClose);
  

  _qbe_sql_syntaxhighlighter *highlighter = new _qbe_sql_syntaxhighlighter(document());

}


