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




#ifndef _SOUND_H
#define _SOUND_H

#include "typedef.h"


#include <QLabel>


#ifdef RUN
#include <phonon/phononnamespace.h>
#include <phonon/audiooutput.h>

#include <phonon/mediaobject.h>
#include <phonon/mediasource.h>
#endif

 
#ifdef RUN
#include "_sounds.h"
extern _sounds2 *EXTERN_my_sounds;


#include <QBuffer>
extern t_pointer loadProjectFile(QString sFile, t_integer *nSize);

#endif


#include "typedef.h"



#include "_property.h"
#include "_control0.h"

#define TEST _sound    
#define TEST2 _sounds
#define TEST3 "Sound"


#define SUPERCLASS QLabel   

#define SUPERCLASS QLabel


#define _SOUND true

class _form;



class _sound : public QLabel, public _property


{
  Q_OBJECT
public:




_sound(_form *f = 0, QWidget *parent = 0) : QLabel (parent ? parent : (QWidget *) f)

{
  constructor(f, parent);

#ifdef IDE
  setAutoFillBackground(true);
  QPalette p = palette();
  p.setColor(QPalette::Window, Qt::white);  
  setPalette(p);
#endif

  // properties

  addProperty("StringValue", pt_qstring); addProperty("OldStringValue", pt_qstring);
  addProperty("TransitionTime", pt_integer);
  addProperty("Muted", pt_boolean);
  addProperty("Volume", pt_integer);
  addProperty("PrefinishMark", pt_integer);
  addProperty("Tick", pt_integer);
  addProperty("Enabled", pt_boolean);

  // events
  addProperty("OnEvent", pt_event);
  addProperty("OnTick", pt_event);
  addProperty("OnStateChanged", pt_event);
  addProperty("OnAboutToFinish", pt_event);
  addProperty("OnFinished", pt_event);
  addProperty("OnMutedChanged", pt_event);
  addProperty("OnVolumeChanged", pt_event);
  addProperty("OnPlayedTitleChanged", pt_event);
  addProperty("OnBufferStatus", pt_event);
  addProperty("OnTotalTimeChanged", pt_event);

  // default values
  SETPROPERTY_ControlType("Sound");

  SETPROPERTY_Enabled(true);

#ifdef RUN
  mediaObject = new Phonon::MediaObject(this);


  audioOutput = new Phonon::AudioOutput(Phonon::MusicCategory, this);

  Phonon::createPath(mediaObject, audioOutput);

  connect(mediaObject, SIGNAL(stateChanged(Phonon::State, Phonon::State)), this, SLOT(stateChanged(Phonon::State, Phonon::State)));
  connect(mediaObject, SIGNAL(aboutToFinish()), this, SLOT(aboutToFinish()));
  connect(mediaObject, SIGNAL(finished()), this, SLOT(finished()));

#endif
}


#ifdef RUN
~_sound()
{
  delete audioOutput;
  delete mediaObject;
/*
  foreach(Phonon::MediaSource s, loaded){
    delete s;
  }*/
  
}
#endif

#include "__property_x.h"
#include "__property_y.h"
//#include "__property_interval.h"


#ifdef RUN
void EVENT_OnSQLEvent();

QByteArray aa;
QBuffer bb;
#endif

void SETPROPERTY_StringValue(const QString & s)
{ 
  if (GETPROPERTY_StringValue() != s){  

#ifdef RUN

  if (s.length() > 200){
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
      //MediaSourcesetAutoDelete 
      mediaObject->setCurrentSource(Phonon::MediaSource(s));   
    }
  }
#endif

    _property::SETPROPERTY_StringValue(s);
  }
}

QString GETPROPERTY_StringValue()
{ 
#ifdef RUN
   
#endif
  return _property::GETPROPERTY_StringValue();
}


QString METHOD_State()
{
#ifdef RUN
   
  switch(mediaObject->state())
  {
     case Phonon::LoadingState: return "LoadingState"; break;
     case Phonon::StoppedState: return "StoppedState"; break;
     case Phonon::PlayingState: return "PlayingState"; break;
     case Phonon::BufferingState: return "BufferingState"; break;
     case Phonon::PausedState: return "PausedState"; break;
     case Phonon::ErrorState: return "ErrorState"; break;
  }

#endif
  return "";
}

QString METHOD_ErrorType()
{
#ifdef RUN
   

  switch(mediaObject->errorType())
  {
     case Phonon::NoError: return "NoError"; break;
     case Phonon::NormalError: return "NormalError"; break;
     case Phonon::FatalError: return "FatalError"; break;
  }

  return "";

#endif
  return "";
}

QString METHOD_ErrorString()
{
#ifdef RUN
   
  return mediaObject->errorString();

#endif
  return "";
}

t_long METHOD_CurrentTime()
{
#ifdef RUN
   
  return mediaObject->currentTime();

#endif
  return 0;
}

t_long METHOD_TotalTime()
{
#ifdef RUN
   
  return mediaObject->totalTime();

#endif
  return 0;
}

t_boolean METHOD_IsPlaying()
{
#ifdef RUN
   
  switch(mediaObject->state())
  {
     case Phonon::PlayingState: return true; break;
  }

#endif
  return 0;
}

t_boolean METHOD_IsPaused()
{
#ifdef RUN
   
  switch(mediaObject->state())
  {
     case Phonon::PausedState: return true; break;
  }

#endif
  return 0;
}

t_boolean METHOD_IsMuted()
{
#ifdef RUN
   
  return audioOutput->isMuted();

#endif
  return 0;
}

t_boolean METHOD_IsSeekable()
{
#ifdef RUN
   
  return mediaObject->isSeekable();

#endif
  return 0;
}

void METHOD_Play()
{
#ifdef RUN

  mediaObject->play();

#endif
}

void METHOD_Play(const QString & s)
{
#ifdef RUN

  if (s.length() > 200){ // QString contains binary data
    {
      SETPROPERTY_StringValue(s);
      mediaObject->play();
    }
  } else {

    if (!(s.contains("/") || s.contains("\\"))){    

      SETPROPERTY_StringValue(s);
      mediaObject->play();
      
    } else {

      if (loaded.contains(s)){
        mediaObject->setCurrentSource(loaded[s]);
        mediaObject->play();
      } else {
        SETPROPERTY_StringValue(s);
        mediaObject->play();
      }
    }
  }

#endif
}

void METHOD_Load(const QString & s)
{
#ifdef RUN

  if (!(s.contains("/") || s.contains("\\"))){    
  } else {
    loaded[s] = Phonon::MediaSource(s);   
  }

#endif
}

void METHOD_PlayInQueue(const QString & n)
{
#ifdef RUN
   
  mediaObject->enqueue(n);

#endif
}

void METHOD_Pause()
{
#ifdef RUN
   
  mediaObject->pause();

#endif
}

void METHOD_Stop()
{
#ifdef RUN
   
  mediaObject->stop();

#endif
}

void METHOD_ClearQueue()
{
#ifdef RUN
   
  mediaObject->clearQueue();

#endif
}

void METHOD_Seek(t_long n)
{
#ifdef RUN
   
  mediaObject->seek(n);

#endif
}

void SETPROPERTY_TransitionTime(t_long n)
{ 
  if (GETPROPERTY_TransitionTime() != n){  

#ifdef RUN
   
#endif

    _property::SETPROPERTY_TransitionTime(n);
  }
}

t_long GETPROPERTY_TransitionTime()
{ 
#ifdef RUN
   
#endif
  return _property::GETPROPERTY_TransitionTime();
}

void SETPROPERTY_Muted(t_boolean n)
{ 
  //if (GETPROPERTY_Muted() != n)
  {  

#ifdef RUN

    audioOutput->setMuted(n);
   
#endif

    _property::SETPROPERTY_Muted(n);
  }
}

t_boolean GETPROPERTY_Muted()
{ 
#ifdef RUN

  return audioOutput->isMuted(); 
   
#endif
  return _property::GETPROPERTY_Muted();
}

void SETPROPERTY_Volume(t_integer n)
{ 
  //if (GETPROPERTY_Volume() != n)
  {  

#ifdef RUN
   
    //audioOutput->setVolume(n / 100);

#endif

    _property::SETPROPERTY_Volume(n);
  }
}

t_integer GETPROPERTY_Volume()
{ 
#ifdef RUN

 // return audioOutput->volume() / 100; 

#endif
  return _property::GETPROPERTY_Volume();
}

void SETPROPERTY_PrefinishMark(t_long n)
{ 
  if (GETPROPERTY_PrefinishMark() != n){  

#ifdef RUN
   
#endif

    _property::SETPROPERTY_PrefinishMark(n);
  }
}

t_long GETPROPERTY_PrefinishMark()
{ 
#ifdef RUN
   
#endif
  return _property::GETPROPERTY_PrefinishMark();
}



// KBBINDINGEVENTS
public slots:

#ifdef RUN
void stateChanged(Phonon::State newstate, Phonon::State oldstate)
{
  QString NewState;
  QString OldState;

  switch(newstate)
  {
     case Phonon::LoadingState: NewState = "LoadingState"; break;
     case Phonon::StoppedState: NewState = "StoppedState"; break;
     case Phonon::PlayingState: NewState = "PlayingState"; break;
     case Phonon::BufferingState: NewState = "BufferingState"; break;
     case Phonon::PausedState: NewState = "PausedState"; break;
     case Phonon::ErrorState: NewState = "ErrorState"; break;
  }

  switch(oldstate)
  {
     case Phonon::LoadingState: OldState = "LoadingState"; break;
     case Phonon::StoppedState: OldState = "StoppedState"; break;
     case Phonon::PlayingState: OldState = "PlayingState"; break;
     case Phonon::BufferingState: OldState = "BufferingState"; break;
     case Phonon::PausedState: OldState = "PausedState"; break;
     case Phonon::ErrorState: OldState = "ErrorState"; break;
  }

  EVENT_OnStateChanged(NewState, OldState);
}

void aboutToFinish()
{
  EVENT_OnAboutToFinish();
}

void finished()
{
  SoundOnEvent();
  EVENT_OnEvent();
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

virtual void EVENT_OnTick(t_long n)
{
}

virtual void EVENT_OnStateChanged(QString NewState, QString OldState)
{
#ifdef RUN
  //QMessageBox::information(this, mediaObject->errorString(), NewState);
#endif
}

virtual void EVENT_OnAboutToFinish()
{
}

virtual void EVENT_OnFinished()
{
}

virtual void EVENT_OnMutedChanged(t_boolean n)
{
}

virtual void EVENT_OnVolumeChanged(t_integer n)
{
}

virtual void EVENT_OnPlayingTitleChanged(QString n)
{
}

virtual void EVENT_OnBufferStatus(t_integer n)
{
}

virtual void EVENT_OnTotalTimeChanged(t_long n)
{
}


public:
// KBBINDINGMETHODS
/*
t_boolean METHOD_IsRunning()
{
  return t.isActive();
}

void METHOD_Start()
{  
  SETPROPERTY_Interval(GETPROPERTY_Interval());
  t.start();  
}

void METHOD_Stop()
{
  t.stop();
}


// ***

void timerEvent(QTimerEvent * e)
{
  EVENT_OnEvent();
}

*/

// ***
#include "_control1_binding.h"


// ***
#include "_control1.h"

//QTimer t;

private:
#ifdef RUN
  Phonon::AudioOutput *audioOutput;
  Phonon::MediaObject *mediaObject;
  QMap<QString, Phonon::MediaSource> loaded;
#endif
};

#include "_control2.h"

#undef _SOUND

#undef TEST
#undef TEST2
#undef TEST3
#undef SUPERCLASS



#endif