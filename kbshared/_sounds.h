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


#ifndef _SOUNDS2_H
#define _SOUNDS2_H

#include "typedef.h"

#ifdef RUN
#include <phonon/phononnamespace.h>
#include <phonon/audiooutput.h>
#include <phonon/mediaobject.h>
#include <phonon/mediasource.h>

#include <QBuffer>
#include <QMap>
#include <QFile>


struct t_sound2
{
public:
  QByteArray *bytearray;
  QBuffer *buffer;
  
};
extern QMap<QString, t_sound2>sounds_map;
extern QMap<Phonon::MediaObject*, Phonon::AudioOutput*>sounds_playing;
extern QList<Phonon::MediaObject*>sounds_to_be_deleted;
extern QMap<Phonon::MediaObject*, Phonon::MediaSource*>sounds_playing2;
extern QMap<Phonon::MediaObject*, Phonon::Path>sounds_playing3;

extern t_pointer loadProjectFile(QString sFile, t_integer *nSize);


class _sounds2;
extern _sounds2 *EXTERN_my_sounds;

#else
#include <QObject>
#endif

/*
void PhononMixingTest::PlayClicked()
  {
    QString soundFilePath = ui.fileLineEdit_->text();   
    if (soundFilePath.isEmpty())
    {
        return;
    }
 
    Phonon::AudioOutput* audioOutput = new Phonon::AudioOutput(Phonon::MusicCategory, this);
    Phonon::MediaObject* mediaObject = new Phonon::MediaObject(this);
    Phonon::createPath(mediaObject, audioOutput);
    connect (mediaObject, SIGNAL(finished()), this, SLOT(SoundFinishedPlaying()));
    mediaObject->setCurrentSource(soundFilePath);
    mediaObject->play();
  }
 
  void PhononMixingTest::SoundFinishedPlaying()
  {
    Phonon::MediaObject* mediaObject = qobject_cast<Phonon::MediaObject*>(sender());
    if (mediaObject)
    {
        mediaObject->stop();
        mediaObject->clearQueue();
        mediaObject->deleteLater();
    }
  }
*/

class _sounds2 : public QObject
{
  Q_OBJECT
#ifdef RUN
public:

_sounds2()
{
  mediaObject = 0;
  audioOutput = 0;

  nTimer = 0;
}

~_sounds2();


QByteArray aa;
QBuffer bb;

void playOnce(QString s)
{  
  if (mediaObject) delete mediaObject;
  if (audioOutput) delete audioOutput;

  mediaObject = new Phonon::MediaObject();
  audioOutput = new Phonon::AudioOutput(Phonon::MusicCategory);

  if (s.length() > 200){ // QString contains binary data
    {
      aa = s.toLatin1();
      bb.close(); bb.setData(aa);
      mediaObject->setCurrentSource(Phonon::MediaSource(&bb));   
    }
  } else {

    if (!(s.contains("/") || s.contains("\\"))){    
      t_integer n = 0;
      t_pointer pp = loadProjectFile(s, &n);
      if (pp != 0){
        aa = QByteArray((const char *) pp, n);
        bb.close(); bb.setData(aa);
        mediaObject->setCurrentSource(Phonon::MediaSource(&bb));   
      }
      
    } else {
      mediaObject->setCurrentSource(Phonon::MediaSource(s));   
    }
  }
  Phonon::createPath(mediaObject, audioOutput);
  mediaObject->seek(0);
  mediaObject->play();
}


static t_boolean METHOD_SetSound(const QString & Id, const QString & filename)
{
  if (!(filename.contains("/") || filename.contains("\\"))){    
    t_integer n = 0;
    t_pointer pp = loadProjectFile(filename, &n);
    if (pp != 0){
      t_sound2 ts;
      ts.bytearray = new QByteArray((const char *) pp, n);
      ts.buffer = new QBuffer(); ts.buffer->setData(*ts.bytearray);
      sounds_map[Id] = ts;
    }
  } else {
    QFile f(filename);
    if (f.open(QFile::ReadOnly)){
      t_sound2 ts;
      ts.bytearray = new QByteArray(f.readAll());
      ts.buffer = new QBuffer(); ts.buffer->setData(*ts.bytearray);
      sounds_map[Id] = ts;
      f.close();
    }
  }

  return true;
}

static void METHOD_Play(const QString & Id);


void timerEvent(QTimerEvent *e);

/*
void myDeleteLater()
{

  sounds_playing[mediaObject]->deleteLater();
  mediaObject->deleteLater();;
  sounds_playing.remove(mediaObject);
}*/

public slots:
void finished();

/*
static _sound *METHOD_LoadFile(QString Name)
{
}


static _sound *GET(QString Name)
{
  return 0;
}
*/

private:
  Phonon::AudioOutput *audioOutput;
  Phonon::MediaObject *mediaObject;

public:
  int nTimer;
  //QMap<QString, Phonon::MediaSource> loaded;


#endif
};




#endif