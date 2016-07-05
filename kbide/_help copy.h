/*
***************************************************************************
Copyright (C) 2000-2007 KBasic Software: www.kbasic.com. All rights reserved.
Source codes are copyrighted by Bernd Noetscher 2000 - 2007.

You may use this source codes under the terms of the GNU Public License (Version 2) as published 
by the Free Software Foundation. 

If you are interested in using the source codes for other licenses or 
commercial development, you must buy commercial licenses from KBasic Software.
***************************************************************************
*/

#include <QMainWindow>
#include <QDialog>
#include <QTextBrowser>

class QWidget;
class QString;
class QTextBrowser;
class QToolBox;
class QGridLayout;


class _helpwindow : public QTextBrowser
{
  Q_OBJECT
public:
  _helpwindow(QWidget *parent) :  QTextBrowser(parent)
  {

    QPalette p = palette();
    p.setColor(QPalette::Window, Qt::lightGray);  
    p.setColor(QPalette::Base, Qt::lightGray);  
    setPalette(p);

  }
};


class _help : public QMainWindow
{
  Q_OBJECT
public:
  _help(QWidget* parent, QString home_, int width, int height);
private:
  QTextBrowser* browser;
};

class _examplebrowser : public QDialog
{
  Q_OBJECT
public:
  _examplebrowser(QWidget* parent);

public slots:
  void perform();

private:

  void addExample(QString s, QGridLayout *j, int y);

    void setupGeneral(); 
    void setupGeneral2(); 
    void setupSQL(); 
    void setupMisc(); 
    void setupForm(); 
    
    
    

    QToolBox *tab;


};