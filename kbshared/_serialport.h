
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


#ifndef _SERIALPORT_H
#define _SERIALPORT_H

#include <QLabel>



#include "typedef.h"


#ifdef RUN
#include "_sounds.h"
extern _sounds2 *EXTERN_my_sounds;
#endif

#include "_property.h"
#include "_control0.h"

#define TEST _serialport    
#define TEST2 _serialports 
#define TEST3 "SerialPort"
#define SUPERCLASS QLabel   

#define _SERIALPORT true

class _form;

#ifdef RUN

#include "../kbrun/qextserialport.h"



#endif

class _serialport : public QLabel, public _property
{
  Q_OBJECT
public:



_serialport(_form *f = 0, QWidget *parent = 0) : QLabel (parent ? parent : (QWidget *) f)
{

#ifdef IDE
  constructor(f, parent);

  setAutoFillBackground(true);
  QPalette p = palette();
  p.setColor(QPalette::Window, Qt::white);  
  setPalette(p);
#else
  addProperty("Name", pt_qstring);
  addProperty("ControlType", pt_qstring);
  addProperty("X", pt_integer);
  addProperty("Y", pt_integer);
  addProperty("Width", pt_integer);
  addProperty("Height", pt_integer);

  addProperty("LoadedX", pt_integer);
  addProperty("LoadedY", pt_integer);
  addProperty("LoadedWidth", pt_integer);
  addProperty("LoadedHeight", pt_integer);


  addProperty("OldX", pt_integer);
  addProperty("GlobalX", pt_integer);
  addProperty("OldY", pt_integer);
  addProperty("GlobalY", pt_integer);
  addProperty("OldWidth", pt_integer);
  addProperty("OldHeight", pt_integer);
#endif

  // properties
  addProperty("PortName", pt_qstring);
  addProperty("BaudRate", pt_qstring);
  addProperty("DataBits", pt_qstring);
  addProperty("FlowControl", pt_qstring);
  addProperty("Parity", pt_qstring);
  addProperty("StopBits", pt_qstring);
  addProperty("TimeOutMillisec", pt_integer);
  addProperty("PollingInterval", pt_integer);

  // events
  addProperty("OnEvent", pt_event);
  addProperty("OnSingleShot", pt_event);
  addProperty("OnEnabled", pt_event);
  addProperty("OnDisabled", pt_event);

  
  // default values
  SETPROPERTY_ControlType("SerialPort");
  
  SETPROPERTY_Enabled(true);
  SETPROPERTY_TimeOutMillisec(500);
  SETPROPERTY_PollingInterval(500);


#ifdef IDE
  //setText("Control 'SerialPort'");
#else
  
  connect(&t, SIGNAL(timeout()), this, SLOT(SoundOnEvent()));
  connect(&t, SIGNAL(timeout()), this, SLOT(EVENT_OnEvent()));

  nBytesRead = 0;
  nBytesWritten = 0;
#endif


}

#include "__property_x.h"
#include "__property_y.h"

#ifdef RUN
~_serialport()
{
  t.stop();
  if (sp.isOpen()) sp.close();
}

void incX(int n)
{
}

void incY(int n)
{
}

void decX(int n)
{
}

void decY(int n)
{
}

void incWidth(int n)
{
}

void incHeight(int n)
{
}

void decWidth(int n)
{
}

void decHeight(int n)
{     
}

#endif

// KBBINDINGEVENTS
public slots:

#ifdef RUN
virtual void EVENT_OnSingleShot()
{
}

virtual void EVENT_OnEnabled()
{
}
virtual void EVENT_OnDisabled()
{
}
#endif

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

// KBBINDINGMETHODS

public:


#ifdef RUN
/*
void timerEvent(QTimerEvent * e)
{
  if (sp.bytesAvailable()) EVENT_OnEvent();
}
*/
t_boolean METHOD_Open()
{    
  if (sp.open(QIODevice::ReadWrite | QIODevice::Unbuffered/*(QIODevice::OpenMode) QextSerialPort::Polling)*/)){

    SETPROPERTY_PortName(GETPROPERTY_PortName());

    SETPROPERTY_BaudRate(GETPROPERTY_BaudRate());

    SETPROPERTY_DataBits(GETPROPERTY_DataBits());

    SETPROPERTY_FlowControl(GETPROPERTY_FlowControl());

    SETPROPERTY_Parity(GETPROPERTY_Parity());

    SETPROPERTY_StopBits(GETPROPERTY_StopBits());

    SETPROPERTY_TimeOutMillisec(GETPROPERTY_TimeOutMillisec());

    SETPROPERTY_PollingInterval(GETPROPERTY_PollingInterval());

    t.start();
  }
  return sp.isOpen();
}

int nBytesRead;
int nBytesWritten;

t_integer METHOD_BytesRead()
{
  return nBytesRead;
}

t_integer METHOD_BytesWritten()
{
  return nBytesWritten;
}

void METHOD_ReadData();
void METHOD_WriteData();


void METHOD_ReadLine();


void METHOD_WriteLine(const QString & s);


t_boolean METHOD_IsOpen()
{
  return sp.isOpen();
}

t_boolean METHOD_IsReadable()
{
  return sp.isReadable();
}

t_boolean METHOD_IsWritable()
{
  return sp.isWritable();
}
/*
t_boolean METHOD_IsSequential()
{
  return sp.isSequential();
}
*/
void METHOD_Close()
{
  if (sp.isOpen()){
    t.stop();
    sp.close();
  }
}

void METHOD_Flush()
{
  if (sp.isOpen()) sp.flush();
}

t_integer METHOD_BytesAvailable()
{
  return sp.bytesAvailable();
}

void METHOD_SetDtr(t_boolean b)
{
  sp.setDtr(b);
}

void METHOD_SetRts(t_boolean b)
{
  sp.setRts(b);
}

t_boolean METHOD_AtEnd()
{
  return sp.atEnd();
}

QString METHOD_LineStatus()
{
  ulong n = sp.lineStatus();
  QString s = "";
  if (n & LS_CTS) if (!s.isEmpty()) s += ","; s += "CTS";
  if (n & LS_DSR) if (!s.isEmpty()) s += ","; s += "DSR";
  if (n & LS_DCD) if (!s.isEmpty()) s += ","; s += "DCD";
  if (n & LS_RI) if (!s.isEmpty()) s += ","; s += "RI";
  return s;
}

t_boolean METHOD_IsCTS()
{
  ulong n = sp.lineStatus();
  return n & LS_CTS;
}

t_boolean METHOD_IsDSR()
{
  ulong n = sp.lineStatus();
  return n & LS_DSR;
}

t_boolean METHOD_IsDCD()
{
  ulong n = sp.lineStatus();
  return n & LS_DCD;
}

t_boolean METHOD_IsRI()
{
  ulong n = sp.lineStatus();
  return n & LS_RI;
}

QString METHOD_LastError()
{
  ulong l = sp.lastError();

  QString s = "";

  if (l == E_NO_ERROR) s = "NO_ERROR";
  else if (l == E_INVALID_FD) s = "INVALID_FD";
  else if (l == E_NO_MEMORY) s = "NO_MEMORY";
  else if (l == E_CAUGHT_NON_BLOCKED_SIGNAL) s = "CAUGHT_NON_BLOCKED_SIGNAL";
  else if (l == E_PORT_TIMEOUT) s = "PORT_TIMEOUT";
  else if (l == E_INVALID_DEVICE) s = "INVALID_DEVICE";
  else if (l == E_BREAK_CONDITION) s = "BREAK_CONDITION";
  else if (l == E_FRAMING_ERROR) s = "FRAMING_ERROR";
  else if (l == E_IO_ERROR) s = "IO_ERROR";
  else if (l == E_BUFFER_OVERRUN) s = "BUFFER_OVERRUN";
  else if (l == E_RECEIVE_OVERFLOW) s = "RECEIVE_OVERFLOW";
  else if (l == E_RECEIVE_PARITY_ERROR) s = "RECEIVE_PARITY_ERROR";
  else if (l == E_TRANSMIT_OVERFLOW) s = "TRANSMIT_OVERFLOW";
  else if (l == E_READ_FAILED) s = "READ_FAILED";
  else if (l == E_WRITE_FAILED) s = "WRITE_FAILED";
 
  return s;
}

QString METHOD_LastErrorText()
{
  ulong l = sp.lastError();

  QString s = "";

  if (l == E_NO_ERROR) s = "No Error has occured.";
  else if (l == E_INVALID_FD) s = "Invalid file descriptor (port was not opened correctly).";
  else if (l == E_NO_MEMORY) s = "Unable to allocate memory tables (POSIX).";
  else if (l == E_CAUGHT_NON_BLOCKED_SIGNAL) s = "Caught a non-blocked signal (POSIX).";
  else if (l == E_PORT_TIMEOUT) s = "Operation timed out (POSIX).";
  else if (l == E_INVALID_DEVICE) s = "The file opened by the port is not a character device (POSIX).";
  else if (l == E_BREAK_CONDITION) s = "The port detected a break condition.";
  else if (l == E_FRAMING_ERROR) s = "The port detected a framing error.";
  else if (l == E_IO_ERROR) s = "There was an I/O error while communicating with the port (usually caused by incorrect baud rate settings).";
  else if (l == E_BUFFER_OVERRUN) s = "Character buffer overrun.";
  else if (l == E_RECEIVE_OVERFLOW) s = "Receive buffer overflow.";
  else if (l == E_RECEIVE_PARITY_ERROR) s = "The port detected a parity error in the received data.";
  else if (l == E_TRANSMIT_OVERFLOW) s = "Transmit buffer overflow.";
  else if (l == E_READ_FAILED) s = "General read operation failure.";
  else if (l == E_WRITE_FAILED) s = "General write operation failure.";
 
  return s;
}

QString GETPROPERTY_PortName()
{
  return sp.portName();
}

void SETPROPERTY_PortName(const QString & n)
{ 
  //if (GETPROPERTY_PortName() != n)
  {    
    _property::SETPROPERTY_PortName(n);
    sp.setPortName(n);
  }  
}

QString GETPROPERTY_BaudRate()
{
  BaudRateType n = sp.baudRate();

  QString s = "";
  if (n == BAUD50) s = "BAUD50";
  else if (n == BAUD75) s = "BAUD75";
  else if (n == BAUD110) s = "BAUD110";
  else if (n == BAUD134) s = "BAUD134";
  else if (n == BAUD150) s = "BAUD150";
  else if (n == BAUD200) s = "BAUD200";
  else if (n == BAUD300) s = "BAUD300";
  else if (n == BAUD600) s = "BAUD600";
  else if (n == BAUD1200) s = "BAUD1200";
  else if (n == BAUD1800) s = "BAUD1800";
  else if (n == BAUD2400) s = "BAUD2400";
  else if (n == BAUD4800) s = "BAUD4800";
  else if (n == BAUD9600) s = "BAUD9600";
  else if (n == BAUD14400) s = "BAUD14400";
  else if (n == BAUD19200) s = "BAUD19200";
  else if (n == BAUD38400) s = "BAUD38400";
  else if (n == BAUD56000) s = "BAUD56000";
  else if (n == BAUD76800) s = "BAUD76800";
  else if (n == BAUD115200) s = "BAUD115200";
  else if (n == BAUD128000) s = "BAUD128000";
  else if (n == BAUD256000) s = "BAUD256000";

  return s;
}

void SETPROPERTY_BaudRate(const QString & n)
{ 

  //if (GETPROPERTY_BaudRate() != n)
  {    

    if (n.compare("BAUD50", Qt::CaseInsensitive) == 0) sp.setBaudRate(BAUD50);
    else if (n.compare("BAUD75", Qt::CaseInsensitive) == 0) sp.setBaudRate(BAUD75);
    else if (n.compare("BAUD110", Qt::CaseInsensitive) == 0) sp.setBaudRate(BAUD110);
    else if (n.compare("BAUD134", Qt::CaseInsensitive) == 0) sp.setBaudRate(BAUD134);
    else if (n.compare("BAUD150", Qt::CaseInsensitive) == 0) sp.setBaudRate(BAUD150);
    else if (n.compare("BAUD200", Qt::CaseInsensitive) == 0) sp.setBaudRate(BAUD200);
    else if (n.compare("BAUD300", Qt::CaseInsensitive) == 0) sp.setBaudRate(BAUD300);
    else if (n.compare("BAUD600", Qt::CaseInsensitive) == 0) sp.setBaudRate(BAUD600);
    else if (n.compare("BAUD1200", Qt::CaseInsensitive) == 0) sp.setBaudRate(BAUD1200);
    else if (n.compare("BAUD1800", Qt::CaseInsensitive) == 0) sp.setBaudRate(BAUD1800);
    else if (n.compare("BAUD2400", Qt::CaseInsensitive) == 0) sp.setBaudRate(BAUD2400);
    else if (n.compare("BAUD4800", Qt::CaseInsensitive) == 0) sp.setBaudRate(BAUD4800);
    else if (n.compare("BAUD9600", Qt::CaseInsensitive) == 0) sp.setBaudRate(BAUD9600);
    else if (n.compare("BAUD14400", Qt::CaseInsensitive) == 0) sp.setBaudRate(BAUD14400);
    else if (n.compare("BAUD19200", Qt::CaseInsensitive) == 0) sp.setBaudRate(BAUD19200);
    else if (n.compare("BAUD38400", Qt::CaseInsensitive) == 0) sp.setBaudRate(BAUD38400);
    else if (n.compare("BAUD56000", Qt::CaseInsensitive) == 0) sp.setBaudRate(BAUD56000);
    else if (n.compare("BAUD76800", Qt::CaseInsensitive) == 0) sp.setBaudRate(BAUD76800);
    else if (n.compare("BAUD115200", Qt::CaseInsensitive) == 0) sp.setBaudRate(BAUD115200);
    else if (n.compare("BAUD128000", Qt::CaseInsensitive) == 0) sp.setBaudRate(BAUD128000);
    else if (n.compare("BAUD256000", Qt::CaseInsensitive) == 0) sp.setBaudRate(BAUD256000);

    _property::SETPROPERTY_BaudRate(n);
  }
}

QString GETPROPERTY_DataBits()
{
  DataBitsType n = sp.dataBits();

  QString s = "";
  if (n == DATA_5) s = "DATA_5";
  else if (n == DATA_6) s = "DATA_6";
  else if (n == DATA_7) s = "DATA_7";
  else if (n == DATA_8) s = "DATA_8";

  return s;
}

void SETPROPERTY_DataBits(const QString & n)
{ 

  //if (GETPROPERTY_DataBits() != n)
  {    

    if (n.compare("DATA_5", Qt::CaseInsensitive) == 0) sp.setDataBits(DATA_5);
    else if (n.compare("DATA_6", Qt::CaseInsensitive) == 0) sp.setDataBits(DATA_6);
    else if (n.compare("DATA_7", Qt::CaseInsensitive) == 0) sp.setDataBits(DATA_7);
    else if (n.compare("DATA_8", Qt::CaseInsensitive) == 0) sp.setDataBits(DATA_8);

    _property::SETPROPERTY_DataBits(n);

  }
}

QString GETPROPERTY_FlowControl()
{  
  FlowType n = sp.flowControl();

  QString s = "";
  if (n == FLOW_OFF) s = "FLOW_OFF";
  else if (n == FLOW_HARDWARE ) s = "FLOW_HARDWARE";
  else if (n == FLOW_XONXOFF ) s = "FLOW_XONXOFF";

  return s;  
}

void SETPROPERTY_FlowControl(const QString & n)
{ 

  //if (GETPROPERTY_FlowControl() != n)
  {    

    if (n.compare("FLOW_OFF", Qt::CaseInsensitive) == 0) sp.setFlowControl(FLOW_OFF);
    else if (n.compare("FLOW_HARDWARE", Qt::CaseInsensitive) == 0) sp.setFlowControl(FLOW_HARDWARE);
    else if (n.compare("FLOW_XONXOFF", Qt::CaseInsensitive) == 0) sp.setFlowControl(FLOW_XONXOFF);

    _property::SETPROPERTY_FlowControl(n);
  }
}

QString GETPROPERTY_Parity()
{
  ParityType n = sp.parity();

  QString s = "";
  if (n == PAR_NONE) s = "PAR_NONE";
  else if (n == PAR_ODD) s = "PAR_ODD";
  else if (n == PAR_EVEN) s = "PAR_EVEN";
  else if (n == PAR_MARK) s = "PAR_MARK";
  else if (n == PAR_SPACE) s = "PAR_SPACE";

  return s;  
}

void SETPROPERTY_Parity(const QString & n)
{ 

  //if (GETPROPERTY_Parity() != n)
  {    

    if (n.compare("PAR_NONE", Qt::CaseInsensitive) == 0) sp.setParity(PAR_NONE);
    else if (n.compare("PAR_ODD", Qt::CaseInsensitive) == 0) sp.setParity(PAR_ODD);
    else if (n.compare("PAR_EVEN", Qt::CaseInsensitive) == 0) sp.setParity(PAR_EVEN);
    else if (n.compare("PAR_MARK", Qt::CaseInsensitive) == 0) sp.setParity(PAR_MARK);
    else if (n.compare("PAR_SPACE", Qt::CaseInsensitive) == 0) sp.setParity(PAR_SPACE);

    _property::SETPROPERTY_Parity(n);
  }
}

QString GETPROPERTY_StopBits()
{
  StopBitsType n = sp.stopBits();

  QString s = "";
  if (n == STOP_1) s = "STOP_1";
  else if (n == STOP_1_5) s = "STOP_1_5";
  else if (n == STOP_2) s = "STOP_2";

  return s;  
}

void SETPROPERTY_StopBits(const QString & n)
{ 

  //if (GETPROPERTY_StopBits() != n)
  {    

    if (n.compare("STOP_1", Qt::CaseInsensitive) == 0) sp.setStopBits(STOP_1);
    else if (n.compare("STOP_1_5", Qt::CaseInsensitive) == 0) sp.setStopBits(STOP_1_5);
    else if (n.compare("STOP_2", Qt::CaseInsensitive) == 0) sp.setStopBits(STOP_2);

    _property::SETPROPERTY_StopBits(n);
  }
}

void SETPROPERTY_TimeOutMillisec(t_integer n)
{ 
  //if (GETPROPERTY_TimeOutMillisec() != n)
  {

    sp.setTimeout(n);

    _property::SETPROPERTY_TimeOutMillisec(n);
  }
  
}

void SETPROPERTY_PollingInterval(t_integer n)
{ 
  //if (GETPROPERTY_PollingInterval() != n)
  {

    t.setInterval(n);

    _property::SETPROPERTY_PollingInterval(n);
  }
  
}



void METHOD_DataRemove(QString Id)
{
  QByteArray a = Id.toUtf8();
  setProperty(a.data(), QVariant(QVariant::Invalid));
}

void METHOD_DataRemoveAll()
{
  QList<QByteArray> l = dynamicPropertyNames();

  foreach(QByteArray a, l)
  {
    QString s = QString::fromUtf8(a);
    if (s.compare("__kb1979.ControlType.kb__", Qt::CaseSensitive) != 0){
      setProperty(a.data(), QVariant(QVariant::Invalid));
    }
  }

}

void METHOD_DataSetBoolean(QString Id, t_boolean Value)
{
  QByteArray a = Id.toUtf8();
  setProperty(a.data(), QVariant(Value));
}

void METHOD_DataSetInteger(QString Id, t_integer Value)
{
  QByteArray a = Id.toUtf8();
  setProperty(a.data(), QVariant(Value));
}

void METHOD_DataSetString(QString Id, QString Value)
{
  QByteArray a = Id.toUtf8();
  setProperty(a.data(), QVariant(Value));
}

void METHOD_DataSetDouble(QString Id, t_double Value)
{
  QByteArray a = Id.toUtf8();
  setProperty(a.data(), QVariant(Value));
}

void METHOD_DataSetLong(QString Id, t_long Value)
{
  QByteArray a = Id.toUtf8();
  setProperty(a.data(), QVariant(Value));
}

void METHOD_DataSetDecimal(QString Id, t_currency Value)
{
  QByteArray a = Id.toUtf8();
  setProperty(a.data(), QVariant(*Value.toQString()));
}

void METHOD_DataSetDateTime(QString Id, t_date Value)
{
  QByteArray a = Id.toUtf8();
  setProperty(a.data(), QVariant(*Value.toQString()));
}

t_boolean METHOD_DataBoolean(QString Id)
{
  QByteArray a = Id.toUtf8();
  QVariant v = property(a.data());
  if (v.isValid()) return v.toBool();
  return 0;
}

t_integer METHOD_DataInteger(QString Id)
{
  QByteArray a = Id.toUtf8();
  QVariant v = property(a.data());
  if (v.isValid()) return v.toInt();
  return 0;
}

QString METHOD_DataString(QString Id)
{
  QByteArray a = Id.toUtf8();
  QVariant v = property(a.data());
  if (v.isValid()) return v.toString();
  return "";
}

t_double METHOD_DataDouble(QString Id)
{
  QByteArray a = Id.toUtf8();
  QVariant v = property(a.data());
  if (v.isValid()) return v.toDouble();
  return 0;
}

t_currency METHOD_DataDecimal(QString Id)
{
  QByteArray a = Id.toUtf8();
  QVariant v = property(a.data());
  if (v.isValid()){
    QString s = v.toString();
    return t_currency(&s);
  }
  return t_currency();
}

t_date METHOD_DataDateTime(QString Id)
{
  QByteArray a = Id.toUtf8();
  QVariant v = property(a.data());
  if (v.isValid()){
    QString s = v.toString();
    return t_date(&s);
  }
  return t_date();
}

t_long METHOD_DataLong(QString Id)
{
  QByteArray a = Id.toUtf8();
  QVariant v = property(a.data());
  if (v.isValid()) return v.toLongLong();
  return 0;
}

void METHOD_ClearFocus()
{
  clearFocus();
}

void METHOD_ToggleVisible()
{
  setHidden(isVisible());
}

void METHOD_SingleShot(t_integer Milliseconds)
{
  nSingleShot = startTimer(Milliseconds);
}

void METHOD_StartTimer()
{
  if (nTimerId != 0) killTimer(nTimerId);
  int n = GETPROPERTY_TimerInterval();
  nTimerId = startTimer(n);
}

void METHOD_StopTimer()
{
  if (nTimerId != 0) killTimer(nTimerId);
}


t_integer METHOD_LocalX(t_integer GlobalX)
{
  return mapFromGlobal(QPoint(GlobalX, 0)).x() + x(); 
}

t_integer METHOD_LocalY(t_integer GlobalY)
{
  return mapFromGlobal(QPoint(0, GlobalY)).y() + y(); 
}

t_integer METHOD_GlobalX(t_integer LocalX)
{
  return mapToGlobal(QPoint(LocalX, 0)).x() - x(); 
}

t_integer METHOD_GlobalY(t_integer LocalY)
{
  return mapToGlobal(QPoint(0, LocalY)).y() - y(); 
}

t_boolean METHOD_UnderMouse()
{
  return underMouse();
}

int nSingleShot;
int nTimerId;



QTimer t;


QextSerialPort sp;

#endif

// ***
#ifdef IDE
#include "_control1_binding.h"


// ***
#include "_control1.h"
#endif


};

#include "_control2.h"

#undef _SERIALPORT

#undef TEST
#undef TEST2
#undef TEST3
#undef SUPERCLASS

#endif