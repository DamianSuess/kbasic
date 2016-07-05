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

#ifndef _STRINGSSTRINGS_H
#define _STRINGSSTRINGS_H


#include "typedef.h"

#include <QMap>
#include <QMapIterator>



class _stringsstrings
{  

public:

#ifdef RUN

QMap<QString, QString> qmap;
QMap<QString, QString>::const_iterator i;

_stringsstrings()
{
  i = qmap.constBegin();
}

~_stringsstrings()
{
  qmap.clear();
}

t_boolean METHOD_Contains(QString Key)
{
  return (bool) qmap.contains(Key);
}

 
_strings *METHOD_Keys()
{
  _strings *ss = new _strings();

  foreach(QString s, qmap.keys())
  {
    ss->METHOD_Append(s);
  }

  return ss;
}

_strings *METHOD_Values()
{
  _strings *ss = new _strings();

  foreach(QString s, qmap.values())
  {
    ss->METHOD_Append(s);
  }

  return ss;
}
 

int METHOD_Len()
{
  return qmap.count();
}

void METHOD_Remove(QString Key)
{
  qmap.remove(Key);
}

void METHOD_RemoveAll()
{
  qmap.clear();
}

void METHOD_Append(QString Key, QString Value)
{
  if (!qmap.contains(Key)){
    qmap.insert(Key, Value);
  }
}

QString METHOD_Get(QString Key)
{
  if (qmap.contains(Key)) return qmap.value(Key);

  return "";
}

void METHOD_Insert(QString Key, QString Value)
{
  if (!qmap.contains(Key)){
    qmap.insert(Key, Value);
  }
}

void METHOD_Replace(QString Key, QString Value)
{
  if (qmap.contains(Key)){
    qmap[Key] = Value;
  }
}

void METHOD_Set(QString Key, QString Value)
{
  //if (qmap.contains(Key))
  {
    qmap[Key] = Value;
  }
}

t_qstring FOR()
{
  i = qmap.constBegin();
  if (i != qmap.constEnd()){
    key = (t_qstring) &i.value();
    value = (t_qstring) &i.value();
    return value;
  }

  return 0;  
}

t_qstring EACH()
{
  ++i;
  if (i != qmap.constEnd()){
    key = (t_qstring) &i.value();
    value = (t_qstring) &i.value();
    return value;
  }

  return 0;  
}

QString METHOD_Key()
{
  if (i != qmap.constEnd()){
    return i.key();
  }
  return "";
}

QString METHOD_Value()
{
  if (i != qmap.constEnd()){
    return i.value();
  }
  return "";
}
       



// *** bindings
// *** 
private:  
  t_qstring key;
  t_qstring value;



/*
QString METHOD_ReadBinary()
{
  QByteArray ba;  
  QDataStream as(&ba, QIODevice::ReadWrite);
  as << qstringlist;

  QString Binary = QString::fromLatin1(ba.data(), ba.length());
  int n = Binary.length();
  return Binary;
}

void METHOD_WriteBinary(QString Binary)
{  
  int n = Binary.length();
  qstringlist.clear();

  QByteArray ba(Binary.toLatin1());  
  QDataStream as(&ba, QIODevice::ReadWrite);
  as >> qstringlist;
}*/

#endif
};

#endif

