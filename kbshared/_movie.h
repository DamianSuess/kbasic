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



#ifndef _MOVIE_H
#define _MOVIE_H

#include "typedef.h"

#ifdef IDE
#include <QLabel>
#endif

#ifdef RUN
#include <phonon/phononnamespace.h>
#include <phonon/audiooutput.h>
#include <phonon/videowidget.h>
#include <phonon/mediaobject.h>
#include <phonon/mediasource.h>
#endif


#ifdef RUN
#include "_sounds.h"
extern _sounds2 *EXTERN_my_sounds;


#include <QBuffer>
extern t_pointer loadProjectFile(QString sFile, t_integer *nSize);

#endif
 




#include "_property.h"
#include "_control0.h"

#define TEST _movie    
#define TEST2 _movies   
#define TEST3 "MovieBox"

#ifdef IDE
#define SUPERCLASS QLabel   
#endif

#ifdef RUN
#define SUPERCLASS Phonon::VideoWidget   
#endif

#define _MOVIE true

class _form;


#ifdef IDE
class _movie : public QLabel, public _property
#endif

#ifdef RUN
class _movie : public Phonon::VideoWidget, public _property
#endif


{
  Q_OBJECT
public:



#ifdef IDE
_movie(_form *f = 0, QWidget *parent = 0) : QLabel (parent ? parent : (QWidget *) f)
#endif

#ifdef RUN
_movie(_form *f = 0, QWidget *parent = 0) : Phonon::VideoWidget (parent ? parent : (QWidget *) f)
#endif

{
  constructor(f, parent);

#ifdef RUN
  bKeyAndMouseCanCancel = false;
#endif
#ifdef IDE
  setAutoFillBackground(true);
  QPalette p = palette();
  p.setColor(QPalette::Window, Qt::white);  
  setPalette(p);
#endif

  // properties

  addProperty("Brightness", pt_integer);
  addProperty("Contrast", pt_integer);
  addProperty("Hue", pt_integer);
  addProperty("Saturation", pt_integer);
  addProperty("ScaleMode", pt_qstring);
  addProperty("AspectRatio", pt_qstring);

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
  SETPROPERTY_ControlType("MovieBox");
  
#ifdef IDE
  setText("Control 'MovieBox'");
#endif

  SETPROPERTY_Visible(true);
  SETPROPERTY_Enabled(true);

#ifdef RUN
  mediaObject = new Phonon::MediaObject(this);
  Phonon::createPath(mediaObject, this);

  audioOutput = new Phonon::AudioOutput(Phonon::VideoCategory, this);

  Phonon::createPath(mediaObject, audioOutput);

  connect(mediaObject, SIGNAL(stateChanged(Phonon::State, Phonon::State)), this, SLOT(stateChanged(Phonon::State, Phonon::State)));
  connect(mediaObject, SIGNAL(aboutToFinish()), this, SLOT(aboutToFinish()));
  connect(mediaObject, SIGNAL(finished()), this, SLOT(finished()));
   


  //QMessageBox::information(this, mediaObject->errorString(), "");

  
#endif
}


#ifdef RUN
~_movie()
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
#endif

#ifdef RUN



void setKeyAndMouseCanCancel(bool b)
{
  bKeyAndMouseCanCancel = b;
}

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
      mediaObject->stop();
      mediaObject->setCurrentSource(Phonon::MediaSource(&bb));   
    }
  } else {

    if (!(s.contains("/") || s.contains("\\"))){    
      t_integer n = 0;
      t_pointer pp = loadProjectFile(s, &n);
      if (pp != 0){
        aa = QByteArray((const char *) pp, n);
        bb.close(); bb.setData(aa);
        mediaObject->stop();
        mediaObject->setCurrentSource(Phonon::MediaSource(&bb));   
      }
    } else {
      //MediaSourcesetAutoDelete 
      mediaObject->stop();
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

void SETPROPERTY_Brightness(t_integer n)
{ 
  if (GETPROPERTY_Brightness() != n){  

#ifdef RUN

    setBrightness(n / 100);
   
#endif

    _property::SETPROPERTY_Brightness(n);
  }
}

t_integer GETPROPERTY_Brightness()
{ 
#ifdef RUN

  return brightness() * 100;
   
#endif
  return _property::GETPROPERTY_Brightness();
  
}

void SETPROPERTY_Contrast(t_integer n)
{ 
  if (GETPROPERTY_Contrast() != n){  

#ifdef RUN
   
    setContrast(n / 100);

#endif

    _property::SETPROPERTY_Contrast(n);
  }
}

t_integer GETPROPERTY_Contrast()
{ 
#ifdef RUN

   return contrast() * 100;

#endif
  return _property::GETPROPERTY_Contrast();
}

void SETPROPERTY_Hue(t_integer n)
{ 
  if (GETPROPERTY_Hue() != n){  

#ifdef RUN

    setHue(n / 100);
   
#endif

    _property::SETPROPERTY_Hue(n);
  }
}

t_integer GETPROPERTY_Hue()
{ 
#ifdef RUN

   return hue() * 100;
   
#endif
  return _property::GETPROPERTY_Hue();
}

void SETPROPERTY_Saturation(t_integer n)
{ 
  if (GETPROPERTY_Saturation() != n){  

#ifdef RUN

    setSaturation(n / 100);
   
#endif

    _property::SETPROPERTY_Saturation(n);
  }
}

t_integer GETPROPERTY_Saturation()
{ 
#ifdef RUN
   
   return saturation() * 100;

#endif
 return _property::GETPROPERTY_Saturation();
}

void SETPROPERTY_ScaleMode(const QString & n)
{ 
  //if (GETPROPERTY_ScaleMode() != n)
  {

#ifdef RUN

    if (n.compare("FitInView", Qt::CaseInsensitive) == 0) setScaleMode(Phonon::VideoWidget::FitInView);
    else if (n.compare("ScaleAndCrop", Qt::CaseInsensitive) == 0) setScaleMode(Phonon::VideoWidget::ScaleAndCrop);
   
#endif

    _property::SETPROPERTY_ScaleMode(n);
  }
}

QString GETPROPERTY_ScaleMode()
{ 
#ifdef RUN
   
#endif
  return _property::GETPROPERTY_ScaleMode();
}

void SETPROPERTY_AspectRatio(const QString & n)
{ 
  //if (GETPROPERTY_AspectRatio() != n)
  {  

#ifdef RUN

    if (n.compare("AspectRatioAuto", Qt::CaseInsensitive) == 0) setAspectRatio(Phonon::VideoWidget::AspectRatioAuto);
    else if (n.compare("AspectRatioWidget", Qt::CaseInsensitive) == 0){
      setAspectRatio(Phonon::VideoWidget::AspectRatioWidget);
    }
    else if (n.compare("AspectRatio4_3", Qt::CaseInsensitive) == 0){
      setAspectRatio(Phonon::VideoWidget::AspectRatio4_3);
    }
    else if (n.compare("AspectRatio16_9", Qt::CaseInsensitive) == 0){
      setAspectRatio(Phonon::VideoWidget::AspectRatio16_9);
    }

#endif

    _property::SETPROPERTY_AspectRatio(n);
  }
}

QString GETPROPERTY_AspectRatio()
{ 
#ifdef RUN
   
#endif
  return _property::GETPROPERTY_AspectRatio();
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

  bool bKeyAndMouseCanCancel;
#endif
};

#include "_control2.h"

#undef _MOVIE

#undef TEST
#undef TEST2
#undef TEST3
#undef SUPERCLASS



#endif