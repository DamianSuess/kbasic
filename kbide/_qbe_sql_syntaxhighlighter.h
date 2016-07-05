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

#include <QSyntaxHighlighter>

#include <QTextCharFormat>

class QTextDocument;

class _qbe_sql_syntaxhighlighter : public QSyntaxHighlighter
{
    Q_OBJECT

public:
    _qbe_sql_syntaxhighlighter(QTextDocument *parent = 0);


public:
    void highlightBlock(const QString &text);

private:
    struct HighlightingRule
    {
        QRegExp pattern;
        QTextCharFormat format;
    };

    QVector<HighlightingRule> highlightingRules;    

    QTextCharFormat normalFormat;
    QTextCharFormat keywordFormat;

    QTextCharFormat commentFormat;
    QTextCharFormat quotationFormat;

};