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


#ifndef _EDITOR_H
#define _EDITOR_H

#include <QTextEdit>
#include <QSyntaxHighlighter>
#include <QTextCharFormat>
#include <QTextDocument>


class QTextDocument;
class _syntaxhighlighter;
class _editor;

#include "typedef.h"


#ifdef RUN
#include "_sounds.h"
extern _sounds2 *EXTERN_my_sounds;
#endif

extern void rehighlight(_syntaxhighlighter *h);
extern _syntaxhighlighter *new_highlighter(_editor *e, QTextDocument *d);


#include "_property.h"
#include "_control0.h"

#define TEST _editor    
#define TEST2 _editors 
#define TEST3 "RichTextBox"
#define SUPERCLASS QTextEdit   

#define _EDITOR true

class _form;
class _syntaxhighlighter;

#ifdef RUN
#include <QtSql>
#include "_color.h"



extern QMap<QString, QColor>colors_map;
#endif

class _editor : public QTextEdit, public _property
{
  Q_OBJECT
public:



_editor(_form *f = 0, QWidget *parent = 0) : QTextEdit (parent ? parent : (QWidget *) f)
{
  constructor(f, parent);


  bool bForm = my_form_isForm(my_form);

#ifdef IDE
  viewport()->setCursor(Qt::ArrowCursor); // WORKAROUND
#endif

  // properties
  addProperty("StringValue", pt_qstring); addProperty("OldStringValue", pt_qstring);

  if (bForm){
    addProperty("Flat", pt_boolean);
    addProperty("WordWrap", pt_boolean);
    addProperty("ReadOnly", pt_boolean);
    setTabChangesFocus(true);
  }

  addProperty("Alignment", pt_qstring);   
  addProperty("AcceptRichText", pt_boolean);   

  addProperty("Comment1Begin", pt_qstring);
  addProperty("Comment1End", pt_qstring);
  addProperty("Comment2Begin", pt_qstring);

  addProperty("Keywords", pt_qstring);
  addProperty("Commands", pt_qstring);
  addProperty("CommentColor", pt_qstring);
  addProperty("KeywordColor", pt_qstring);
  addProperty("CommandColor", pt_qstring);

  // events
  addProperty("OnEvent", pt_event);
  addProperty("OnCursorPositionChanged", pt_event);
  addProperty("OnAction", pt_event);

  // default values
  SETPROPERTY_ControlType("RichTextBox");
  SETPROPERTY_Visible(true);
  SETPROPERTY_AcceptRichText(true);
  if (bForm) SETPROPERTY_Enabled(true);
  
  // slots
  connect(this, SIGNAL(textChanged()), this, SLOT(SoundOnEvent()));
  connect(this, SIGNAL(textChanged()), this, SLOT(EVENT_OnEvent()));
  connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(EVENT_OnCursorPositionChanged()));

  //connect(this, SIGNAL(copyAvailable(bool)), this, SLOT(copyAvailable(bool)));
  connect(this, SIGNAL(redoAvailable(bool)), this, SLOT(redoAvailable(bool)));
  connect(this, SIGNAL(undoAvailable(bool)), this, SLOT(undoAvailable(bool)));
  connect(this, SIGNAL(selectionChanged()), this, SLOT(selectionChanged()));

  connect(this, SIGNAL(textChanged()), this, SLOT(EVENT_OnSQLEvent()));


  highlighter = 0;

  bTextSelected = bCanPaste = bRedoAvailable = bUndoAvailable = false;

}

_syntaxhighlighter *highlighter;

#include "__property_x.h"
#include "__property_y.h"
#include "__property_flat.h"
#include "__property_stringvalue.h"
#include "__property_wordwrap.h"
#include "__property_readonly.h"
#include "__property_acceptrichtext.h"
#include "__property_alignment.h"

#include "__property_comment1begin.h"
#include "__property_comment1end.h"
#include "__property_comment2begin.h"
//#include "__property_comment2end.h"
#include "__property_keywords.h"
#include "__property_commands.h"
#include "__property_commentcolor.h"
#include "__property_keywordcolor.h"
#include "__property_commandcolor.h"



QString GETPROPERTY_StringValue()
{

  {
    if (GETPROPERTY_AcceptRichText()){
      return toHtml();
    } else {
      return toPlainText();
    }
  }

}


// KBBINDINGEVENTS
public slots:

/*
void copyAvailable(bool yes)
{
  if (bCopyAvailable != yes){
    bCopyAvailable = yes;
    EVENT_OnEvent1(bTextSelected, canPaste(), bUndoAvailable, bRedoAvailable);
  }
}*/

void redoAvailable(bool yes)
{
  if (bRedoAvailable != yes || bCanPaste != canPaste()){
    bCanPaste = canPaste();
    bRedoAvailable = yes;
    EVENT_OnEvent1(bTextSelected, bCanPaste, bUndoAvailable, bRedoAvailable);
  }
}

void undoAvailable(bool yes)
{
  if (bUndoAvailable != yes || bCanPaste != canPaste()){
    bCanPaste = canPaste();
    bUndoAvailable = yes;
    EVENT_OnEvent1(bTextSelected, bCanPaste, bUndoAvailable, bRedoAvailable);
  }
}

void selectionChanged()
{
  bool yes = textCursor().hasSelection();
  if (bTextSelected != yes || bCanPaste != canPaste()){
    bCanPaste = canPaste();
    bTextSelected = yes;
    EVENT_OnEvent1(bTextSelected, bCanPaste, bUndoAvailable, bRedoAvailable);
  }
}

void SoundOnEvent()
{
#ifdef RUN
  QString s = GETPROPERTY_SoundOnEvent();
  if (!s.isEmpty()){
    EXTERN_my_sounds->playOnce(s);
  }
#endif
}

virtual void EVENT_OnEvent()
{
}

virtual void EVENT_OnEvent1(t_boolean TextSelected, t_boolean PasteAvailable, t_boolean UndoAvailable, t_boolean RedoAvailable)
{
}

virtual void EVENT_OnCursorPositionChanged()
{
}

void EVENT_OnSQLEvent();

// KBBINDINGMETHODS

public:


#ifdef RUN

QString METHOD_HTML()
{
  return toHtml();
}

QString METHOD_PlainText()
{
  return toPlainText();
}
t_boolean METHOD_IsModified()
{
  return document()->isModified();
}

void METHOD_SetModified(t_boolean b)
{
  document()->setModified();
}


void METHOD_SetFontColor(_color *ColorObject)
{
  if ((t_integer) ColorObject < 100){   
    setTextColor((Qt::GlobalColor) (t_integer) ColorObject);
    /*
  } else {
    QColor c; c.setRgba(ColorObject->rgba());
    setTextColor(c);*/
  }

}


void METHOD_SetFontColor1(QString ColorId)
{
  if (!colors_map.contains(ColorId)) return;
  setTextColor(colors_map[ColorId]);
}

void METHOD_SetFontPointSize(t_double FontPointSize)
{
  setFontPointSize(FontPointSize);
}

void METHOD_SetFontFamily(const QString & IsFontFamily)
{
  setFontFamily(IsFontFamily);
}

void METHOD_SetFontColor(const QString & c)
{
  if (colors_map.contains(c)) setTextColor(colors_map[c]);
}

void METHOD_SetFontBold(t_boolean IsFontBold)
{
  setFontWeight(IsFontBold ? QFont::Bold : QFont::Normal);
}

void METHOD_SetFontItalic(t_boolean IsFontItalic)
{
  setFontItalic(IsFontItalic);
}

void METHOD_SetFontUnderline(t_boolean IsFontUnderline)
{
  setFontUnderline(IsFontUnderline);
}

t_integer METHOD_Line()
{
  QTextCursor c = textCursor();

  return c.blockNumber() + 1;
}

t_integer METHOD_Column()
{
  QTextCursor c = textCursor();

  return c.columnNumber() + 1;
}

QString METHOD_Selected()
{
  QTextCursor c = textCursor();

  return c.selectedText();
}

void METHOD_Undo()
{
  undo();
}

void METHOD_Redo()
{
  redo();
}

void METHOD_SetTabChangesFocus(t_boolean IsTabChangesFocus)
{
  setTabChangesFocus(IsTabChangesFocus);
}

void METHOD_RemoveAll()
{
  clear();
}

void METHOD_Copy()
{
  copy();
}

void METHOD_Paste()
{
  paste();
}

void METHOD_Cut()
{
  cut();
}

void METHOD_SelectAll()
{
  selectAll();
}

void METHOD_SetHtml(const QString & Text)
{
  setHtml(Text);
}

void METHOD_SetPlainText(const QString & Text)
{
  setPlainText(Text);
}

void METHOD_InsertHtml(const QString & Text)
{
  insertHtml(Text);
}

void METHOD_InsertPlainText(const QString & Text)
{
  insertPlainText(Text);
}

void METHOD_Append(const QString & Text)
{
  append(Text);
}
#endif

// ***
#include "_control1_binding.h"


// ***
#include "_control1.h"


private:
 bool bTextSelected;
 bool bCanPaste;
 bool bRedoAvailable;
 bool bUndoAvailable; 

};

#include "_control2.h"

#undef _EDITOR

#undef TEST
#undef TEST2
#undef TEST3
#undef SUPERCLASS

class _syntaxhighlighter : public QSyntaxHighlighter
{
    Q_OBJECT

public:
_syntaxhighlighter(_editor *_my_editor, QTextDocument *parent = 0)  : QSyntaxHighlighter(parent)
{
  my_editor = _my_editor;   
  update();
}

void update()
{
  QString s = my_editor->GETPROPERTY_FontName();
  if (s.isEmpty()) s = my_editor->fontFamily();
  int n = my_editor->GETPROPERTY_FontSize();
  if (n == 0) n = my_editor->fontPointSize();

  normalFormat.setForeground(my_editor->getColor(my_editor->GETPROPERTY_FontColor()));
  if (!s.isEmpty()) normalFormat.setFontFamily(s);
  if (n) normalFormat.setFontPointSize(n);

  keywordFormat.setForeground(my_editor->getColor(my_editor->GETPROPERTY_KeywordColor()));
  if (!s.isEmpty()) keywordFormat.setFontFamily(s);
  if (n) keywordFormat.setFontPointSize(n);

  commandFormat.setForeground(my_editor->getColor(my_editor->GETPROPERTY_CommandColor()));
  if (!s.isEmpty()) commandFormat.setFontFamily(s);
  if (n) commandFormat.setFontPointSize(n);

  commentFormat.setForeground(my_editor->getColor(my_editor->GETPROPERTY_CommentColor()));
  if (!s.isEmpty()) commentFormat.setFontFamily(s);
  if (n) commentFormat.setFontPointSize(n);

  quotationFormat.setForeground(my_editor->getColor(my_editor->GETPROPERTY_KeywordColor()));
  if (!s.isEmpty()) quotationFormat.setFontFamily(s);
  if (n) quotationFormat.setFontPointSize(n);
  
  QString r = "";
  QString r2 = "";
  r = "/" + my_editor->GETPROPERTY_Comment1Begin();
  r2 = "\\" + my_editor->GETPROPERTY_Comment1End();

  commentStartExpression = QRegExp(r.length() > 1 &&  r2.length() > 1 ? r : "");
  commentEndExpression = QRegExp(r.length() > 1 &&  r2.length() > 1 ? r2 : "");
    
  s = my_editor->GETPROPERTY_Comment2Begin();
  if (s.isEmpty()){
    commentStart2 = 0;
  } else {
    QChar data = s.at(0);
    commentStart2 = data.toAscii();
  }

  setKeywords(my_editor->GETPROPERTY_Keywords());
  setCommands(my_editor->GETPROPERTY_Commands());
}

public:

void setKeywords(const QString & n)
{ 
  set.clear();

  QString s = n;
  if (s.trimmed().length()){
    QStringList l = n.split(s.contains(",") ? "," : ";");
    for (int i = 0; i < l.size(); i++){
      QString k = l.at(i).simplified();
      if (k.isEmpty()) continue;
      set << k;
      set << k.toUpper();
      set << k.toLower();
    }

  }

}

void setCommands(const QString & n)
{ 
  set2.clear();  

  QString s = n;
  if (s.trimmed().length()){
    QStringList l = n.split(s.contains(",") ? "," : ";");
    for (int i = 0; i < l.size(); i++){
      QString k = l.at(i).simplified();
      if (k.isEmpty()) continue;
      set2 << k;
      set << k.toUpper();
      set << k.toLower();
    }

  }
}


void highlightBlock(const QString &text);

private:
    
    QSet<QString> set;
    QSet<QString> set2;    

    QRegExp commentStartExpression;
    QRegExp commentEndExpression;

    QTextCharFormat normalFormat;
    QTextCharFormat keywordFormat;
    QTextCharFormat commandFormat;

    QTextCharFormat commentFormat;
    QTextCharFormat quotationFormat;

    char commentStart2;

    _editor *my_editor;

    
};


#endif