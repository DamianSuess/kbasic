
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


#ifndef _udpsocket_H
#define _udpsocket_H

#include <QLabel>



#include "typedef.h"


#ifdef RUN
#include "_sounds.h"
extern _sounds2 *EXTERN_my_sounds;

#include <QUdpSocket>

#endif

#include "_property.h"
#include "_control0.h"

#define TEST _udpsocket    
#define TEST2 _udpsockets 
#define TEST3 "UdpSocket"
#define SUPERCLASS QLabel   

#define _UDPSOCKET true

class _form;


class _udpsocket : public QLabel, public _property
{
  Q_OBJECT
public:



_udpsocket(_form *f = 0, QWidget *parent = 0) : QLabel (parent ? parent : (QWidget *) f)
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
  addProperty("Host", pt_qstring);
  addProperty("Port", pt_qstring);

  // events
  addProperty("OnEvent", pt_event);
  addProperty("OnOpen", pt_event);
  addProperty("OnClose", pt_event);
  addProperty("OnSingleShot", pt_event);
  addProperty("OnEnabled", pt_event);
  addProperty("OnDisabled", pt_event);

  
  // default values
  SETPROPERTY_ControlType("UdpSocket");
  
  SETPROPERTY_Enabled(true);


#ifdef IDE
#else
  t = new QUdpSocket(this);
  nPort = 0;
  a = 0; a2 = 0;
 
  connect(t, SIGNAL(readyRead()), this, SLOT(SoundOnEvent()));
  connect(t, SIGNAL(readyRead()), this, SLOT(EVENT_OnEvent()));
  connect(t, SIGNAL(connected()), this, SLOT(EVENT_OnOpen()));
  connect(t, SIGNAL(disconnected()), this, SLOT(EVENT_OnClose()));

#endif


}

#include "__property_x.h"
#include "__property_y.h"

#ifdef RUN
~_udpsocket()
{
  delete t;
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

#ifdef RUN
virtual void EVENT_OnOpen()
{
}

virtual void EVENT_OnClose()
{
}
#endif

// KBBINDINGMETHODS

public:


#ifdef RUN


t_boolean METHOD_Open()
{    
  if (GETPROPERTY_Host().compare("LocalHost", Qt::CaseInsensitive) == 0) a = new QHostAddress(QHostAddress::LocalHost);
  else if (GETPROPERTY_Host().compare("LocalHostIPv6", Qt::CaseInsensitive) == 0) a = new QHostAddress(QHostAddress::LocalHostIPv6);
  else if (GETPROPERTY_Host().compare("Broadcast", Qt::CaseInsensitive) == 0) a = new QHostAddress(QHostAddress::Broadcast);
  else if (GETPROPERTY_Host().compare("Any", Qt::CaseInsensitive) == 0) a = new QHostAddress(QHostAddress::Any);
  else if (GETPROPERTY_Host().compare("AnyIPv6", Qt::CaseInsensitive) == 0) a = new QHostAddress(QHostAddress::AnyIPv6);
  else a = new QHostAddress(GETPROPERTY_Host());

  t->connectToHost(*a, nPort);

  if (t->waitForConnected()){
    return true;
  }
  
  return false;
}

t_boolean METHOD_Bind(QString Host, t_integer Port)
{    
  nPort2 = Port;
  if (GETPROPERTY_Host().compare("LocalHost", Qt::CaseInsensitive) == 0) a2 = new QHostAddress(QHostAddress::LocalHost);
  else if (GETPROPERTY_Host().compare("LocalHostIPv6", Qt::CaseInsensitive) == 0) a2 = new QHostAddress(QHostAddress::LocalHostIPv6);
  else if (GETPROPERTY_Host().compare("Broadcast", Qt::CaseInsensitive) == 0) a2 = new QHostAddress(QHostAddress::Broadcast);
  else if (GETPROPERTY_Host().compare("Any", Qt::CaseInsensitive) == 0) a2 = new QHostAddress(QHostAddress::Any);
  else if (GETPROPERTY_Host().compare("AnyIPv6", Qt::CaseInsensitive) == 0) a2 = new QHostAddress(QHostAddress::AnyIPv6);
  else a2 = new QHostAddress(GETPROPERTY_Host());

  if (t->bind(*a2, nPort2)){    
    return true;
  }
  
  return false;
}

QString METHOD_ReadData()
{ 
   QString s;

    while ((a || a2) && t->hasPendingDatagrams()) {
         QByteArray datagram;
         datagram.resize(t->pendingDatagramSize());
         QHostAddress sender;
         quint16 senderPort;

         t->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);

         s += QString::fromLatin1((const char *) datagram.data(), datagram.size());
    }

    return s;
}

t_boolean METHOD_WriteData(QString sData)
{
  if (a == 0) return false;

  QByteArray datagram = sData.toLatin1();
  return t->writeDatagram(datagram.data(), datagram.size(), *a, nPort) > 0;
}

void METHOD_Close()
{
  t->disconnectFromHost();
  delete a;
  a = 0;
}

QString METHOD_LastError()
{
  QAbstractSocket::SocketError l = t->error();

  QString s = "";

  if (l == QAbstractSocket::ConnectionRefusedError) s = "ConnectionRefusedError";
  else if (l == QAbstractSocket::RemoteHostClosedError) s = "RemoteHostClosedError";
  else if (l == QAbstractSocket::HostNotFoundError) s = "HostNotFoundError";
  else if (l == QAbstractSocket::SocketAccessError) s = "SocketAccessError";
  else if (l == QAbstractSocket::SocketResourceError) s = "SocketResourceError";
  else if (l == QAbstractSocket::SocketTimeoutError) s = "SocketTimeoutError";
  else if (l == QAbstractSocket::DatagramTooLargeError) s = "DatagramTooLargeError";
  else if (l == QAbstractSocket::NetworkError) s = "NetworkError";
  else if (l == QAbstractSocket::AddressInUseError) s = "AddressInUseError";
  else if (l == QAbstractSocket::SocketAddressNotAvailableError) s = "SocketAddressNotAvailableError";
  else if (l == QAbstractSocket::UnsupportedSocketOperationError) s = "UnsupportedSocketOperationError";
  else if (l == QAbstractSocket::ProxyAuthenticationRequiredError) s = "ProxyAuthenticationRequiredError";
  else if (l == QAbstractSocket::SslHandshakeFailedError) s = "SslHandshakeFailedError";
  else if (l == QAbstractSocket::UnfinishedSocketOperationError) s = "UnfinishedSocketOperationError";
#ifndef LINUX
  else if (l == QAbstractSocket::ProxyConnectionRefusedError) s = "ProxyConnectionRefusedError";
  else if (l == QAbstractSocket::ProxyConnectionClosedError) s = "ProxyConnectionClosedError";
  else if (l == QAbstractSocket::ProxyConnectionTimeoutError) s = "ProxyConnectionTimeoutError";
  else if (l == QAbstractSocket::ProxyNotFoundError) s = "ProxyNotFoundError";
  else if (l == QAbstractSocket::ProxyProtocolError) s = "ProxyProtocolError";
#endif
  else if (l == QAbstractSocket::UnknownSocketError) s = "UnknownSocketError";
 
  return s;
}

QString METHOD_LastErrorText()
{
  return t->errorString();
}

QString GETPROPERTY_Host()
{
  return sHost;
}

void SETPROPERTY_Host(const QString & n)
{ 
  sHost = n;
}

QString GETPROPERTY_Port()
{
  return sPort;
}

void SETPROPERTY_Port(const QString & n)
{   
  sPort = n; 
  nPort = GETPROPERTY_Port().toInt();
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


private:
QUdpSocket *t;
QHostAddress *a;
int nPort;

QHostAddress *a2;
int nPort2;

QString sHost;
QString sPort;


int nSingleShot;
int nTimerId;

#endif

// ***
#ifdef IDE
#include "_control1_binding.h"


// ***
#include "_control1.h"
#endif


};

#include "_control2.h"

#undef _UDPSOCKET

#undef TEST
#undef TEST2
#undef TEST3
#undef SUPERCLASS

#endif