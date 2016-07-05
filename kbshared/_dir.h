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


#ifndef _DIR_H
#define _DIR_H


#include <QDir>
class _strings;

#include "typedef.h"

#ifdef RUN
extern QDir dir;
#endif

class _dir
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

static bool copyDir (const QString& from, const QString& to)
{
  QDir d;
  d.mkpath(to);

  QDir thisDir( from );	
  QFileInfoList files = thisDir.entryInfoList();

  if ( files.size() ) {

    QFileInfo fi;
    for (int i = 0; i < files.size(); ++i) {
      fi = files.at(i);

      QString ss = fi.absoluteFilePath();

		  if (fi.fileName() == "." || fi.fileName() == ".."){
		      ; // nothing
		  } else if ( fi.isSymLink()){
          ; // nothing
		  } else if ( fi.isDir() ){

        if (!copyDir(fi.absoluteFilePath(), to + "/" + fi.fileName())) return false;

      } else {

        if (!copyFile(fi.absoluteFilePath(), to + "/" + fi.fileName())) return false;

      }		    
	}
  
  }    
  return true;
}

static QFileInfo getFileInfo(QString Path)
{
  Path = QDir::fromNativeSeparators(Path);

  dir.setPath(Path);
  dir.cdUp();
  
  if (dir.exists()){
    QFileInfoList ff = dir.entryInfoList();
    
    foreach(QFileInfo f, ff){
      if (f.isDir()){
        QString s = QDir::fromNativeSeparators(f.absoluteFilePath());
        if (s.compare(Path, Qt::CaseInsensitive) == 0){
          return f;
        }
      }
    }
  }

  return QFileInfo();
}

static _strings *FindFile(QString Path, QString NameFilter, QStringList NameFilter2, QString Filter, QString Sorting, bool bRecursive = false, bool bRecursiveCall = false, bool bbb = false);


// ******

static t_boolean METHOD_Create(QString Path)
{  
  return dir.mkdir(Path);
}

static t_boolean METHOD_RecursiveCreate(QString Path)
{  
  return dir.mkpath(Path);
}

static t_boolean METHOD_Remove(QString Path)
{
  return dir.rmdir(Path);
}

static t_boolean METHOD_RecursiveRemove(QString Path)
{
  return dir.rmpath(Path);
}

static _strings *METHOD_FindFile(QString Path, QString NameFilter, QString Filter, QString Sorting)
{
  return FindFile(Path, NameFilter, QStringList(), Filter, Sorting);
}

static _strings *METHOD_RecursiveFindFile(QString Path, QString NameFilter, QString Filter, QString Sorting)
{
  return FindFile(Path, NameFilter, QStringList(), Filter, Sorting, true);
}

static _strings *METHOD_FindFile1(QString Path, _strings *NameFilter, QString Filter, QString Sorting)
{
  return FindFile(Path, "", NameFilter->qstringlist, Filter, Sorting);
}

static _strings *METHOD_RecursiveFindFile1(QString Path, _strings *NameFilter, QString Filter, QString Sorting)
{
  return FindFile(Path, "", NameFilter->qstringlist, Filter, Sorting, true);
}

static _strings *METHOD_FileList(QString Path)
{
  return FindFile(Path, "*.*", QStringList(), "NoFilter", "NoSort");
}

static _strings *METHOD_RecursiveFileList(QString Path)
{
  return FindFile(Path, "*.*", QStringList(), "NoFilter", "NoSort", true);
}

static t_boolean METHOD_Copy(QString SourcePath, QString DestinationPath)
{
  return copyDir(SourcePath, DestinationPath);
}

static t_boolean METHOD_Move(QString SourcePath, QString DestinationPath)
{
  return dir.rename(SourcePath, DestinationPath);
}

static t_boolean METHOD_Exists(QString Path)
{
  return dir.exists(Path);
}

static t_boolean METHOD_ExistsAndIsDir(QString Path)
{
  return dir.exists(Path) && METHOD_IsDir(Path);
}

/*
static t_boolean METHOD_IsReadable(QString Path)
{
  dir.setPath(Path);
  return dir.isReadable();
}*/

static _strings *METHOD_Drives()
{
  QFileInfoList ff = QDir::drives();

  _strings *ss = new _strings();

  foreach(QFileInfo f, ff){
    ss->METHOD_Append(f.absolutePath());
  }
  return ss;
}

static QString METHOD_TempPath()
{
  return QDir::fromNativeSeparators(QDir::tempPath());
}

static QString METHOD_HomePath()
{
  return QDir::fromNativeSeparators(QDir::homePath());
}

static QString METHOD_RootPath()
{
  return QDir::fromNativeSeparators(QDir::rootPath());
}



static QString METHOD_DateTimeCreated(QString Path)
{
  QFileInfo f = getFileInfo(Path);
  if (f.exists()) return f.created().toString("yyyy-MM-dd hh:mm:ss");      
  return "";
}

static QString METHOD_DateTimeUpdated(QString Path)
{
  QFileInfo f = getFileInfo(Path);
  if (f.exists()) return f.lastModified().toString("yyyy-MM-dd hh:mm:ss");      
  return "";
}

static QString METHOD_DateTimeRead(QString Path)
{
  QFileInfo f = getFileInfo(Path);
  if (f.exists()) return f.lastRead().toString("yyyy-MM-dd hh:mm:ss");      
  return "";
}

static QString METHOD_WithNativeSeparators(QString Path)
{
  return QDir::toNativeSeparators(Path);
}

static QString METHOD_WithoutNativeSeparators(QString Path)
{
  return QDir::fromNativeSeparators(Path);
}

static QString METHOD_Owner(QString Path)
{
  QFileInfo f = getFileInfo(Path);
  if (f.exists()) return f.owner();      
  return "";
}

static QString METHOD_Group(QString Path)
{
  QFileInfo f = getFileInfo(Path);
  if (f.exists()) return f.group();      
  return "";
}

static QString METHOD_BundleName(QString Path)
{
  QFileInfo f = getFileInfo(Path);
  if (f.exists()) return f.bundleName();      
  return false;
}

static QString METHOD_SymLinkTarget(QString Path)
{
  QFileInfo f = getFileInfo(Path);
  if (f.exists()) return f.symLinkTarget();      
  return false;
}

static QString METHOD_Name(QString Path)
{
  QFileInfo f = getFileInfo(Path);
  if (f.exists()) return f.fileName();      
  return false;
}

static QString METHOD_Path(QString Path)
{
  QFileInfo f = getFileInfo(Path);
  if (f.exists()) return f.path();      
  return false;
}

static QString METHOD_Suffix(QString Path)
{
  QFileInfo f = getFileInfo(Path);
  if (f.exists()) return f.suffix();      
  return false;
}
/*
static QString METHOD_CompleteSuffix (QString Path)
{
  QFileInfo f = getFileInfo(Path);
  if (f.exists()) return f.completeSuffix();      
  return false;
}*/


static t_boolean METHOD_IsRoot(QString Path)
{
  QFileInfo f = getFileInfo(Path);
  if (f.exists()) return f.isRoot();      
  return false;
}

static t_boolean METHOD_IsRelative(QString Path)
{
  QFileInfo f = getFileInfo(Path);
  if (f.exists()) return f.isRelative();      
  return false;
}

static t_boolean METHOD_IsSymLink(QString Path)
{
  QFileInfo f = getFileInfo(Path);
  if (f.exists()) return f.isSymLink();      
  return false;
}

static t_boolean METHOD_IsReadable(QString Path, QString Who)
{
  if (Who.isEmpty() || Who.contains("User", Qt::CaseInsensitive)){
    QFileInfo f = getFileInfo(Path);
    if (f.exists()) return f.isReadable();      
  } else if (Who.contains("Owner", Qt::CaseInsensitive)){
    QFileInfo f = getFileInfo(Path);
    if (f.exists()) return f.permission(QFile::ReadOwner);   
  } else if (Who.contains("Group", Qt::CaseInsensitive)){
    QFileInfo f = getFileInfo(Path);
    if (f.exists()) return f.permission(QFile::ReadGroup);   
  } else if (Who.contains("Other", Qt::CaseInsensitive)){
    QFileInfo f = getFileInfo(Path);
    if (f.exists()) return f.permission(QFile::ReadOther);   
  }
  return false;
}

static t_boolean METHOD_IsWriteable(QString Path, QString Who)
{
  if (Who.isEmpty() || Who.contains("User", Qt::CaseInsensitive)){
    QFileInfo f = getFileInfo(Path);
    if (f.exists()) return f.isWritable();      
  } else if (Who.contains("Owner", Qt::CaseInsensitive)){
    QFileInfo f = getFileInfo(Path);
    if (f.exists()) return f.permission(QFile::WriteOwner);   
  } else if (Who.contains("Group", Qt::CaseInsensitive)){
    QFileInfo f = getFileInfo(Path);
    if (f.exists()) return f.permission(QFile::WriteGroup);   
  } else if (Who.contains("Other", Qt::CaseInsensitive)){
    QFileInfo f = getFileInfo(Path);
    if (f.exists()) return f.permission(QFile::WriteOther);   
  }
  return false;
}

static t_boolean METHOD_IsExecutable(QString Path, QString Who)
{
  if (Who.isEmpty() || Who.contains("User", Qt::CaseInsensitive)){
    QFileInfo f = getFileInfo(Path);
    if (f.exists()) return f.isExecutable();      
  } else if (Who.contains("Owner", Qt::CaseInsensitive)){
    QFileInfo f = getFileInfo(Path);
    if (f.exists()) return f.permission(QFile::ExeOwner);   
  } else if (Who.contains("Group", Qt::CaseInsensitive)){
    QFileInfo f = getFileInfo(Path);
    if (f.exists()) return f.permission(QFile::ExeGroup);   
  } else if (Who.contains("Other", Qt::CaseInsensitive)){
    QFileInfo f = getFileInfo(Path);
    if (f.exists()) return f.permission(QFile::ExeOther);   
  }
  return false;
}

static t_boolean METHOD_IsHidden(QString Path)
{
  QFileInfo f = getFileInfo(Path);
  if (f.exists()) return f.isHidden();      
  return false;
}

static t_boolean METHOD_IsDir(QString Path)
{
  QFileInfo f = getFileInfo(Path);  
  if (f.exists()){
    return f.isDir();      
  }
  return false;
}

static t_boolean METHOD_IsBundle(QString Path)
{
  QFileInfo f = getFileInfo(Path);
  if (f.exists()) return f.isBundle();      
  return false;
}



/*
static t_integer METHOD_CopyTotal()
{
  return 0;
}

static t_integer METHOD_CopyCurrent()
{
  return 0;
}

static t_boolean METHOD_CopyFinished()
{
  return 0;
}

static t_boolean METHOD_CopyNoError()
{
  return 0;
}

static t_boolean METHOD_CopyCancel()
{
  return 0;
}

Dir.CopyAnd???("j,lök", "kljöl")

static void METHOD_CopyAnd???(QString SourcePath, QString DestinationPath)
{
  copyDir(SourcePath, DestinationPath);
}

*/


#endif
};


#endif