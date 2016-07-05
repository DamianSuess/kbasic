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


#ifndef _DATABASEDIALOG_H
#define _DATABASEDIALOG_H



#include "typedef.h"

#include <QString>
#include <QDialog>
#include <QWidget>
#include <QComboBox>



extern QString p_dbuser;
extern QString p_dbname;
extern QString p_dbdriver;
extern QString p_dbhost;
extern QString p_dbport;
extern QString p_dbuserpassword;
extern QString p_dbconnectoptions;
extern bool bOk_dbcondialog;

class _dbcondialog : public QDialog
{
  Q_OBJECT
public:
  _dbcondialog(QWidget* parent);


private slots:
    
  void ok();
  void cancel();


private:

  

QComboBox *dbuser;
QComboBox *dbname;
QComboBox *dbdriver;
QComboBox *dbhost;
QComboBox *dbport;
QComboBox *dbuserpassword;
QComboBox *dbconnectoptions;
};

class _databasedialog
{
  
public:


static t_boolean METHOD_GetDatabase()
{

  p_dbuser = "";
  p_dbname = "";
  p_dbdriver = "";
  p_dbhost = "localhost";
  p_dbport = "";
  p_dbuserpassword = "";
  p_dbconnectoptions = "";

  _dbcondialog *o = new _dbcondialog(qApp->focusWidget());
  
  return bOk_dbcondialog;
} 

static t_boolean METHOD_GetDatabase(QString Driver, QString Name, QString User, QString Password, QString Host, QString Options, QString Port)
{

  p_dbuser = User;
  p_dbname = Name;
  p_dbdriver = Driver;
  p_dbhost = Host;
  p_dbport = Port;
  p_dbuserpassword = Password;
  p_dbconnectoptions = Options;

  _dbcondialog *o = new _dbcondialog(qApp->focusWidget());  

  return bOk_dbcondialog;
} 

static QString METHOD_Driver()
{
  return p_dbdriver;
} 

static QString METHOD_Host()
{
  return p_dbhost;
} 

static QString METHOD_Port()
{
  return p_dbport;
} 

static QString METHOD_Name()
{
  return p_dbname;
} 

static QString METHOD_User()
{
  return p_dbuser;
} 

static QString METHOD_Password()
{
  return p_dbuserpassword;
} 

static QString METHOD_Options()
{
  return p_dbconnectoptions;
} 

}
;



#endif