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


#ifndef _FILE_H
#define _FILE_H

#include <QFile>


#include "typedef.h"


#ifdef RUN
extern QFile qfile;
#endif

class _file
{
#ifdef RUN
public:


static bool copyFile (const QString& from, const QString& to)
{
  QFile file(from);
  if (file.exists()){
    QFile file2(to);  
    file2.remove();
    return file.copy(to);
  }
  return false;
} 

// ******


static t_long METHOD_Size(QString FileName)
{  
  qfile.setFileName(FileName);
  return qfile.size();
}

static t_boolean METHOD_Resize(QString FileName, t_long NewSize)
{  
  qfile.setFileName(FileName);
  return qfile.resize(NewSize);   
}

static t_boolean METHOD_Truncate(QString FileName)
{  
  qfile.setFileName(FileName);
  if (qfile.open(QIODevice::Truncate | QIODevice::WriteOnly)){
    qfile.close();
    return true;
  }
  return false;
}

static t_boolean METHOD_SetReadable(QString FileName, t_boolean Readable, QString Who)
{  
  return false;
}

static t_boolean METHOD_SetWriteable(QString FileName, t_boolean Writable, QString Who);

static t_boolean METHOD_SetExecutable(QString FileName, t_boolean Readable, QString Who)
{  
  return false;
}

static QString METHOD_ReadText(QString FileName, QString Codec, t_boolean AutoDetectUnicode, t_boolean GenerateByteOrderMark)
{  
  QFile f(FileName);
  bool b = false;

  if (FileName.compare("stderr", Qt::CaseInsensitive) == 0) b = f.open(stderr, QIODevice::ReadOnly);
  else if (FileName.compare("stdin", Qt::CaseInsensitive) == 0) b = f.open(stdin, QIODevice::ReadOnly);
  else if (FileName.compare("stdout", Qt::CaseInsensitive) == 0) b = f.open(stdout, QIODevice::ReadOnly);
  else b = f.open(QIODevice::ReadOnly);

  if (b){
    QTextStream t(&f);
    
    t.setCodec(QTextCodec::codecForName(Codec.toLatin1().data()));
    t.setAutoDetectUnicode(AutoDetectUnicode);
    t.setGenerateByteOrderMark(GenerateByteOrderMark);

    QString s = t.readAll();
    f.close();
    return s;
  }

  return "";
}

static t_boolean METHOD_WriteText(QString FileName, QString Text, t_boolean Append, QString Codec, t_boolean AutoDetectUnicode, t_boolean GenerateByteOrderMark)
{  
  QFile f(FileName);
  bool b = false;

  if (FileName.compare("stderr", Qt::CaseInsensitive) == 0) b = f.open(stderr, QIODevice::WriteOnly | (Append ? QIODevice::Append : QIODevice::Truncate));
  else if (FileName.compare("stdin", Qt::CaseInsensitive) == 0) b = f.open(stdin, QIODevice::WriteOnly | (Append ? QIODevice::Append : QIODevice::Truncate));
  else if (FileName.compare("stdout", Qt::CaseInsensitive) == 0) b = f.open(stdout, QIODevice::WriteOnly | (Append ? QIODevice::Append : QIODevice::Truncate));
  else b = f.open(QIODevice::WriteOnly | (Append ? QIODevice::Append : QIODevice::Truncate));

  if (b){
    QTextStream t(&f);

    t.setCodec(QTextCodec::codecForName(Codec.toLatin1().data()));
    t.setAutoDetectUnicode(AutoDetectUnicode);
    t.setGenerateByteOrderMark(GenerateByteOrderMark);

    t << Text;
    f.close();

    return true;
  }

  return false;
}

static QString METHOD_ReadBinary(QString FileName)
{  
  QFile f(FileName);
  bool b = false;

  if (FileName.compare("stderr", Qt::CaseInsensitive) == 0) b = f.open(stderr, QIODevice::ReadOnly);
  else if (FileName.compare("stdin", Qt::CaseInsensitive) == 0) b = f.open(stdin, QIODevice::ReadOnly);
  else if (FileName.compare("stdout", Qt::CaseInsensitive) == 0) b = f.open(stdout, QIODevice::ReadOnly);
  else b = f.open(QIODevice::ReadOnly);

  if (b){
    QByteArray ba = f.readAll();
    QString s = QString::fromLatin1(ba.data(), ba.length());
    f.close();
    return s;
  }

  return "";
}

static t_boolean METHOD_WriteBinary(QString FileName, QString Binary, t_boolean Append)
{  
  QFile f(FileName);
  bool b = false;

  if (FileName.compare("stderr", Qt::CaseInsensitive) == 0) b = f.open(stderr, QIODevice::WriteOnly | (Append ? QIODevice::Append : QIODevice::Truncate));
  else if (FileName.compare("stdin", Qt::CaseInsensitive) == 0) b = f.open(stdin, QIODevice::WriteOnly | (Append ? QIODevice::Append : QIODevice::Truncate));
  else if (FileName.compare("stdout", Qt::CaseInsensitive) == 0) b = f.open(stdout, QIODevice::WriteOnly | (Append ? QIODevice::Append : QIODevice::Truncate));
  else b = f.open(QIODevice::WriteOnly | (Append ? QIODevice::Append : QIODevice::Truncate));

  if (b){
    QByteArray ba(Binary.toLatin1());
    t_long l = f.write(ba);
    f.close();
    return l == ba.length();
  }

  return false;
}

static t_boolean METHOD_Link(QString SourceFileName, QString DestinationFileName)
{
  qfile.setFileName(SourceFileName);
  if (QFile::exists(SourceFileName)) return qfile.link(DestinationFileName);
  return false;
}

static t_boolean METHOD_Create(QString FileName)
{  
  if (QFile::exists(FileName)) return true;

  QFile f(FileName);
  if (f.open(QIODevice::WriteOnly)){
    f.close();
    return true;
  }
  
  return false;
}

static t_boolean METHOD_Remove(QString FileName)
{
  if (QFile::exists(FileName)) return QFile::remove(FileName);
  return false;
}

static t_boolean METHOD_Copy(QString SourceFileName, QString DestinationFileName, t_boolean Overwrite)
{
  if (Overwrite){
    return copyFile(SourceFileName, DestinationFileName);
  } else {
    return QFile::copy(SourceFileName, DestinationFileName);
  }
}

static t_boolean METHOD_Move(QString SourceFileName, QString DestinationFileName, t_boolean Overwrite)
{
  if (Overwrite){
    if (copyFile(SourceFileName, DestinationFileName)){
      QFile::remove(SourceFileName);
      return true;
    }
  } else {
    if (QFile::copy(SourceFileName, DestinationFileName)){
      QFile::remove(SourceFileName);
      return true;
    }
  }
  return false;
}

static t_boolean METHOD_Rename(QString SourceFileName, QString DestinationFileName, t_boolean Overwrite)
{
  if (Overwrite && QFile::exists(DestinationFileName)){
    QFile::remove(DestinationFileName);
  }
  return QFile::rename(SourceFileName, DestinationFileName);
}

static t_boolean METHOD_Exists(QString FileName)
{
  return QFile::exists(FileName);
}

static QString METHOD_DateTimeCreated(QString FileName)
{
  QFileInfo f(FileName);
  if (f.exists()) return f.created().toString("yyyy-MM-dd hh:mm:ss");      
  return "";
}

static QString METHOD_DateTimeUpdated(QString FileName)
{
  QFileInfo f(FileName);
  if (f.exists()) return f.lastModified().toString("yyyy-MM-dd hh:mm:ss");      
  return "";
}

static QString METHOD_DateTimeRead(QString FileName)
{
  QFileInfo f(FileName);
  if (f.exists()) return f.lastRead().toString("yyyy-MM-dd hh:mm:ss");      
  return "";
}

static QString METHOD_WithNativeSeparators(QString FileName)
{
  return QDir::toNativeSeparators(FileName);
}

static QString METHOD_WithoutNativeSeparators(QString FileName)
{
  return QDir::fromNativeSeparators(FileName);
}

static QString METHOD_Owner(QString FileName)
{
  QFileInfo f(FileName);
  if (f.exists()) return f.owner();      
  return "";
}

static QString METHOD_Group(QString FileName)
{
  QFileInfo f(FileName);
  if (f.exists()) return f.group();      
  return "";
}

static QString METHOD_SymLinkTarget(QString FileName)
{
  QFileInfo f(FileName);
  if (f.exists()) return f.symLinkTarget();      
  return false;
}

static QString METHOD_NameWithoutSuffix(QString FileName)
{
  QFileInfo f(FileName);
  if (f.exists()) return f.baseName();      
  return false;
}

static QString METHOD_Name(QString FileName)
{
  QFileInfo f(FileName);
  if (f.exists()) return f.fileName();      
  return false;
}

static QString METHOD_Path(QString FileName)
{
  QFileInfo f(FileName);
  if (f.exists()) return f.path();      
  return false;
}

static QString METHOD_Suffix(QString FileName)
{
  QFileInfo f(FileName);
  if (f.exists()) return f.suffix();      
  return false;
}

static t_boolean METHOD_IsRelative(QString FileName)
{
  QFileInfo f(FileName);
  if (f.exists()) return f.isRelative();      
  return false;
}

static t_boolean METHOD_IsSymLink(QString FileName)
{
  QFileInfo f(FileName);
  if (f.exists()) return f.isSymLink();      
  return false;
}

static t_boolean METHOD_IsReadable(QString FileName, QString Who)
{
  if (Who.isEmpty() || Who.contains("User", Qt::CaseInsensitive)){
    QFileInfo f(FileName);
    if (f.exists()) return f.isReadable();      
  } else if (Who.contains("Owner", Qt::CaseInsensitive)){
    QFileInfo f(FileName);
    if (f.exists()) return f.permission(QFile::ReadOwner);   
  } else if (Who.contains("Group", Qt::CaseInsensitive)){
    QFileInfo f(FileName);
    if (f.exists()) return f.permission(QFile::ReadGroup);   
  } else if (Who.contains("Other", Qt::CaseInsensitive)){
    QFileInfo f(FileName);
    if (f.exists()) return f.permission(QFile::ReadOther);   
  }
  return false;
}

static t_boolean METHOD_IsWriteable(QString FileName, QString Who)
{
  if (Who.isEmpty() || Who.contains("User", Qt::CaseInsensitive)){
    QFileInfo f(FileName);
    if (f.exists()) return f.isWritable();      
  } else if (Who.contains("Owner", Qt::CaseInsensitive)){
    QFileInfo f(FileName);
    if (f.exists()) return f.permission(QFile::WriteOwner);   
  } else if (Who.contains("Group", Qt::CaseInsensitive)){
    QFileInfo f(FileName);
    if (f.exists()) return f.permission(QFile::WriteGroup);   
  } else if (Who.contains("Other", Qt::CaseInsensitive)){
    QFileInfo f(FileName);
    if (f.exists()) return f.permission(QFile::WriteOther);   
  }
  return false;
}

static t_boolean METHOD_IsExecutable(QString FileName, QString Who)
{
  if (Who.isEmpty() || Who.contains("User", Qt::CaseInsensitive)){
    QFileInfo f(FileName);
    if (f.exists()) return f.isExecutable();      
  } else if (Who.contains("Owner", Qt::CaseInsensitive)){
    QFileInfo f(FileName);
    if (f.exists()) return f.permission(QFile::ExeOwner);   
  } else if (Who.contains("Group", Qt::CaseInsensitive)){
    QFileInfo f(FileName);
    if (f.exists()) return f.permission(QFile::ExeGroup);   
  } else if (Who.contains("Other", Qt::CaseInsensitive)){
    QFileInfo f(FileName);
    if (f.exists()) return f.permission(QFile::ExeOther);   
  }
  return false;
}

static t_boolean METHOD_IsHidden(QString FileName)
{
  QFileInfo f(FileName);
  if (f.exists()) return f.isHidden();      
  return false;
}

static t_boolean METHOD_IsFile(QString FileName)
{
  QFileInfo f(FileName);  
  if (f.exists()){
    return f.isFile();      
  }
  return false;
}




#endif
};


#endif