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

class _sourcecodeeditor_syntaxhighlighter : public QSyntaxHighlighter
{
    Q_OBJECT

public:
    _sourcecodeeditor_syntaxhighlighter(QTextDocument *parent = 0);

    void setHTML(bool b)
    {
      bHTML = b;
    }

    void setSyntaxHighlighting(bool b)
    {
      bSyntaxHighlighting = b;
    }

public:
    void highlightBlock(const QString &text);
    void highlightBlock2(QString sFilename, QString &text);

private:
    struct HighlightingRule
    {
        QRegExp pattern;
        QTextCharFormat format;
    };

    QVector<HighlightingRule> highlightingRules;    

    QRegExp commentStartExpression;
    QRegExp commentEndExpression;

    QTextCharFormat normalFormat;
    QTextCharFormat sqlFormat;
    QTextCharFormat keywordFormat;
    QTextCharFormat markFormat;

    //QTextCharFormat builtinFormat;
    //QTextCharFormat classFormat;
    QTextCharFormat commentFormat;
    QTextCharFormat quotationFormat;
    //QTextCharFormat functionFormat;

    bool bSyntaxHighlighting;
    bool bHTML;
};