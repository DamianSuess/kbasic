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

#ifndef _sourcecodeeditor_H
#define _sourcecodeeditor_H

#include <QFrame>
#include <QTextEdit>
#include <QListWidget>


class QTextCursor;
class QComboBox;
class QLabel;
class QPushButton;
class QSize;
class QPoint;

class _sourcecodeeditor_syntaxhighlighter;
class _sourcecodeeditor_editor;
class _mainwindow;


extern _mainwindow *EXTERN_my_mainwindow;


class _sourcecodeeditor : public QFrame
{
  Q_OBJECT

public:
  _sourcecodeeditor(/*_mainwindow *_my_mainwindow*/);
  ~_sourcecodeeditor();

  void setCurrentLineAndSelectLine(int line);
  void insertCorrectIdentForLine(bool bAppend);
  bool beautifyCurrentLine();
  bool isModified();
  
  void setSyntaxHighlighting(bool b);

  virtual void keyPressEvent(QKeyEvent* e);
  virtual void keyReleaseEvent(QKeyEvent* e); 

  void unselect();

  void performFindDefinition();
  void performUndo();
  void performRedo();
  void performCut();
  void performCopy();
  void performPaste();
  void performDelete();
  void performSelectAll();
  void performComment();
  void performUncomment();
  void performIndent();
  void performUnindent();
  void performMark();
  void performUpper();
  void performLower();
  void performInsertFile();
  void performGotoLine();
  void performFind();
  void performReplace();
  void performInsertText(QString s);
  
  

  bool replace(QString replace);
  void replaceAll(QString search, QString replace, bool bMatchCase, bool bMatchWhole, bool bSearchUp, bool bSelection);

  QString getBeforeCurrentLineAsString();
  QString getCurrentLineAsString(int nLineOffset = 0);

  int getCurrentLine();
  int getCurrentColumn();

  bool setUnsetBookmarkSelection();
  void clearBookmarkSelection();

  bool setUnsetBreakpointSelection();
  void clearBreakpointSelection();

  QString getBreakpointsAsString();


    bool load( const QString& fn, bool _bClassForm);
    void save(bool saveAs = false);
    void saveAs();
    void saveAsHTML();

    bool isFullscreen(){ return bFullscreen; }

    void reloadAfterFileReplacement();

    static void createMap();

    void updateCaption(QString s, bool bSaving = true);

    QString getSourceCode(bool b = true);
    static QString getSourceCode(QString sFileName);

    void closeEvent( QCloseEvent * );

    bool isFormClassSourceCode()
    {
      return bClassForm;
    }

    QString getFilename();
    QString getScope(); // class name or module name of current cursor line
    QString getScope2(); // method name
    QString getDot();

    void focusInEvent(QFocusEvent *e);

    bool newEvent(QString sControlName, QString sEvent, QString sParameter, QString sCode = "");
    bool addToEvent(QString sControlName, QString sEvent, QString sParameter, QString sCode);
    
    bool hasSub(QString s, bool bSelect = true);
    void gotoBeforeEndClass();

    QString getFilenameWithoutPath()
    { 
      QString s = filename;
      int i = s.lastIndexOf('/');
      s = s.right(s.length() - i - 1);
      return s; 
    }

    QString getPath()
    { 
      QString s = filename;
      int i = s.lastIndexOf('/');
      s = s.left(i + 1);
      return s; 
    }


    QPushButton *events;   


  _sourcecodeeditor_editor *my_sourcecodeeditor_editor;

  void showEvents2(QString sControlName);    
  void setNoFullscreen(bool bSwitch = true);  


public slots:
  void updateBrowser();
  void cursorPositionChanged(void);
  void activated(int index);
  void setFullscreen();
  void setNoFullscreen2();  
  void setWindow_extend();    
  void showEvents();    

private slots:
  void copyAvailable(bool yes);
  void redoAvailable(bool yes);
  void undoAvailable(bool yes);
  void textChanged();  
  void selectionChanged();

private:
  
  void createMap3();

  void updateScopes();

  void updatingBrowser();

  void timerEvent(QTimerEvent *event);
  void updateExtraSelections();

  _sourcecodeeditor_syntaxhighlighter *highlighter;
  
  QComboBox *browser; 
  QLabel *info; 

  int nTimerBrowserNeedsUpdate;
  bool bBrowserNeedsUpdate;
  int nBrowserUpdated;

  bool bFullscreen;  
  QIcon noFullScreenIcon;
  QWidget *noFullScreenParent;
  QPushButton *window_nofullscreen;   
  QPushButton *window_extend;   
  Qt::WindowFlags noFullScreenWindowFlags;
  QPoint noFullScreenPos;
  QSize noFullScreenSize;

  

  QList<QTextEdit::ExtraSelection> allExtraSelections;

  QList<QTextEdit::ExtraSelection> bookmarks;
  QTextCharFormat bookmarkFormat;

  QList<QTextEdit::ExtraSelection> breakpoints;
  QTextCharFormat breakpointFormat;

  QTextCharFormat currentLineFormat;

  int nOldBlock;

  bool bClosing;

  QString filename;

  bool bCTRL;
  bool bSHIFT;

  bool bClassForm;
  bool bOLDFORMAT;
  bool bSyntaxHighlighting;

  QString sScope;
  QString sScope2;
  QString sDot;
public:
  bool bCanUndo;
  bool bCanRedo;
  bool bCanCopy;
  
 

};


class _border: public QWidget
{
Q_OBJECT
public:
  _border(_sourcecodeeditor *p);
  
 void mouseDoubleClickEvent ( QMouseEvent * e );
 void mouseMoveEvent ( QMouseEvent * e );
 void mousePressEvent ( QMouseEvent * e );
 void mouseReleaseEvent ( QMouseEvent * e );
 void leaveEvent ( QEvent * );
 void done();
 void select (QMouseEvent * e); 
private:
_sourcecodeeditor *editor;
bool bButton;
bool bDouble;
int nStartLine;
};

class _finddefinition : public QListWidget
{
  Q_OBJECT

public:
  _finddefinition();

  void performFindDefinition(QString s);

private slots:

void itemDoubleClicked(QListWidgetItem *item);

private:



};

#endif