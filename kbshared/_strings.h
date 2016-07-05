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

#ifndef _STRINGS_H
#define _STRINGS_H


#include "typedef.h"


#include <QLinkedList>


class _strings
{  

public:

QStringList qstringlist;

#ifdef RUN
_strings()
{
  i = 0;
}


t_boolean METHOD_Contains(QString Text, t_boolean CaseSensitive)
{
  return (bool) qstringlist.contains(Text, CaseSensitive ? Qt::CaseSensitive : Qt::CaseInsensitive);
}

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
}
 
int METHOD_IndexOf(QString Text, t_integer Position)
{
  return qstringlist.indexOf(Text, Position - 1);
}

int METHOD_LastIndexOf(QString Text, t_integer Position)
{
  return qstringlist.lastIndexOf(Text, Position);
}

        

int METHOD_Len()
{
  return qstringlist.count();
}

void METHOD_Remove(t_integer m)
{
  qstringlist.removeAt(m);
}

void METHOD_Sort()
{
  qstringlist.sort();
}

void METHOD_RemoveAll()
{
  qstringlist.clear();
}

void METHOD_Prepend(QString p)
{
  qstringlist.prepend(p);
}

void METHOD_Append(QString p)
{
  qstringlist.append(p);
}

QString METHOD_Join(QString Separator)
{
  return qstringlist.join(Separator);
}

QString METHOD_Get(t_integer n)
{
  if (n - 1 >= 0 && n - 1 < qstringlist.count()) return qstringlist.at(n - 1);

  return "";
}

void METHOD_Insert(t_integer n, QString s)
{
  if (n - 1 >= 0 && n - 1 < qstringlist.count()) {
    qstringlist.insert(n - 1, s);
  }
}

void METHOD_Replace(t_integer n, QString s)
{
  if (n - 1 >= 0 && n - 1 < qstringlist.count()) {
    qstringlist.replace(n - 1, s);
  }
}

void METHOD_Set(t_integer n, QString s)
{
  if (n - 1 >= 0 && n - 1 < qstringlist.count()) {
    qstringlist.replace(n - 1, s);
    
  }
}

t_qstring FOR(bool *bBreak)
{
  i = 0;
  if (i < qstringlist.count()){
    *bBreak = false;
    return (t_qstring) &qstringlist.at(0);
  } else {
    *bBreak = true;
    return 0;
  }
  
  //return i < qstringlist.count() ? (t_qstring) &qstringlist.at(0) : 0;
}

t_qstring EACH(bool *bBreak)
{
  i++;
  if (i < qstringlist.count()){
    *bBreak = false;
    return (t_qstring) &qstringlist.at(i);
  } else {
    *bBreak = true;
    return 0;
  }

  //return ++i < qstringlist.count() ? (t_qstring) &qstringlist.at(i) : 0;
}



// *** bindings
// *** 
private:
  int i;  
#endif
};

#endif

