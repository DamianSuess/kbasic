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

#ifndef _PROGRESSDIALOG_H
#define _PROGRESSDIALOG_H


#include <QProgressDialog>

#include "typedef.h"


extern QString ProgressDialog_Caption;
extern QString ProgressDialog_CancelCaption;
extern t_integer ProgressDialog_Value;
extern t_integer ProgressDialog_Minimum;
extern t_integer ProgressDialog_Maximum;
extern t_integer ProgressDialog_Wait;


extern QProgressDialog *qprogressdialog;

class _progressdialog
{
#ifdef RUN
public:


static void METHOD_Show()
{
  if (qprogressdialog) delete qprogressdialog;
  qprogressdialog = new QProgressDialog(qApp->focusWidget());
  qprogressdialog->setAutoClose(false);
  qprogressdialog->setAutoReset(false);

  if (!ProgressDialog_Caption.isEmpty()) qprogressdialog->setLabelText(ProgressDialog_Caption); 
  if (!ProgressDialog_CancelCaption.isEmpty()) qprogressdialog->setCancelButtonText(ProgressDialog_CancelCaption); 
  qprogressdialog->setValue(ProgressDialog_Value); 
  qprogressdialog->setMinimum(ProgressDialog_Minimum); 
  qprogressdialog->setMaximum(ProgressDialog_Maximum); 
  qprogressdialog->setMinimumDuration(ProgressDialog_Wait); 

  qprogressdialog->show();
} 

static void METHOD_Show1(QString Caption, QString CancelCaption)
{
  if (qprogressdialog) delete qprogressdialog;
  qprogressdialog = new QProgressDialog(qApp->focusWidget());
  qprogressdialog->setAutoClose(false);
  qprogressdialog->setAutoReset(false);

  if (!ProgressDialog_Caption.isEmpty()) qprogressdialog->setLabelText(Caption); 
  if (!ProgressDialog_CancelCaption.isEmpty()) qprogressdialog->setCancelButtonText(CancelCaption); 

  qprogressdialog->setValue(ProgressDialog_Value); 
  qprogressdialog->setMinimum(ProgressDialog_Minimum); 
  qprogressdialog->setMaximum(ProgressDialog_Maximum); 
  qprogressdialog->setMinimumDuration(ProgressDialog_Wait); 

  qprogressdialog->show();
} 

static void METHOD_Hide()
{
  qprogressdialog->hide();

  delete qprogressdialog;
  qprogressdialog = 0;

  ProgressDialog_Caption = ""; 
  ProgressDialog_CancelCaption = "";
  ProgressDialog_Value = 0;
  ProgressDialog_Minimum = 0;
  ProgressDialog_Maximum = 100;
  ProgressDialog_Wait = 4000;
} 

static t_boolean METHOD_Canceled()
{
  if (qprogressdialog == 0) return false;

  return qprogressdialog->wasCanceled();
} 

static void PROPERTYSET_Caption(QString k)
{
  if (qprogressdialog == 0) return;

  if (qprogressdialog->isVisible()){
    qprogressdialog->setLabelText(k); 
  } else {
    ProgressDialog_Caption = k;
  }
}

static QString PROPERTYGET_Caption()
{
  if (qprogressdialog == 0) return "";

  if (qprogressdialog->isVisible()){
    return qprogressdialog->labelText(); 
  } else {
    return ProgressDialog_Caption;
  }
}

static void PROPERTYSET_CancelCaption(QString k)
{
  if (qprogressdialog == 0) return;

  if (qprogressdialog->isVisible()){
    qprogressdialog->setCancelButtonText(k); 
    ProgressDialog_CancelCaption = k;
  } else {
    ProgressDialog_CancelCaption = k;
  }
}

static QString PROPERTYGET_CancelCaption()
{
  if (qprogressdialog == 0) return "";

  return ProgressDialog_CancelCaption;
  /*
  if (qprogressdialog->isVisible()){
    return qprogressdialog->cancelButtonText(); 
  } else {
    return ProgressDialog_CancelCaption;
  }*/
}

static void PROPERTYSET_Value(t_integer k)
{
  if (qprogressdialog == 0) return;

  if (qprogressdialog->isVisible()){
    qprogressdialog->setValue(k); 
  } else {
    ProgressDialog_Value = k;
  }
}

static t_integer PROPERTYGET_Value()
{
  if (qprogressdialog == 0) return 0;

  if (qprogressdialog->isVisible()){
    return qprogressdialog->value(); 
  } else {
    return ProgressDialog_Value;
  }
}

static void PROPERTYSET_Minimum(t_integer k)
{
  if (qprogressdialog == 0) return;

  if (qprogressdialog->isVisible()){
    qprogressdialog->setMinimum(k); 
  } else {
    ProgressDialog_Minimum = k;
  }  
}

static t_integer PROPERTYGET_Minimum()
{
  if (qprogressdialog == 0) return 0;

  if (qprogressdialog->isVisible()){
    return qprogressdialog->minimum(); 
  } else {
    return ProgressDialog_Minimum;
  }
}

static void PROPERTYSET_Maximum(t_integer k)
{
  if (qprogressdialog == 0) return;

  if (qprogressdialog->isVisible()){
    qprogressdialog->setMaximum(k); 
  } else {
    ProgressDialog_Maximum = k;
  }     
}

static t_integer PROPERTYGET_Maximum()
{
  if (qprogressdialog == 0) return 0;

  if (qprogressdialog->isVisible()){
    return qprogressdialog->maximum(); 
  } else {
    return ProgressDialog_Maximum;
  }
}

static void PROPERTYSET_Wait(t_integer k)
{
  if (qprogressdialog == 0) return;

  if (qprogressdialog->isVisible()){
    qprogressdialog->setMinimumDuration(k); 
  } else {
    ProgressDialog_Wait = k;
  }     
}

static t_integer PROPERTYGET_Wait()
{
  if (qprogressdialog == 0) return 0;

  if (qprogressdialog->isVisible()){
    return qprogressdialog->minimumDuration(); 
  } else {
    return ProgressDialog_Wait;
  }
}

#endif
}
;



#endif