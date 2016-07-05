
case pcode___movie___movie1:{ getParam(v, m, n); pp = new kb_movie(0); myStack->pushParameter(pcode___movie, pp); ((kb_movie *) pp)->setInterpreter(this); break; }
case pcode___movie___movie:{ getParam(v, m, n); pp = new kb_movie(v[0]->to_form()); myStack->pushParameter(pcode___movie, pp); ((kb_movie *) pp)->setInterpreter(this); break; }

case pcode___movie__SETPROPERTY_MouseTracking:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); q->SETPROPERTY_MouseTracking(v[0]->tot_boolean()); break; }
case pcode___movie__GETPROPERTY_MouseTracking:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_MouseTracking()); if (bReturn) pushStack(p); else delete p; break; }
                                 
case pcode___movie__SETPROPERTY_CursorAnimation:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); q->SETPROPERTY_CursorAnimation(v[0]->toQString()); break; }
case pcode___movie__GETPROPERTY_CursorAnimation:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_CursorAnimation()); if (bReturn) pushStack(p); else delete p; break; }

case pcode___movie__METHOD_DataIds:{   
  
  getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); 
   
  QList<QByteArray> l = q->dynamicPropertyNames();
  
  _strings *ss = new _strings();

  foreach(QByteArray a, l)
  {
    QString s = QString::fromUtf8(a);
    if (s.compare("__kb1979.ControlType.kb__", Qt::CaseSensitive) != 0){
      ss->METHOD_Append(s);
    }
  }

  interpreter_parameter *p = new interpreter_parameter(ss); 
    
  if (bReturn) pushStack(p); else delete p; break; 
}

case pcode___movie__METHOD_DataRemove:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); q->METHOD_DataRemove(v[0]->toQString()); break; }
case pcode___movie__METHOD_DataRemoveAll:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); q->METHOD_DataRemoveAll(); break; }
case pcode___movie__METHOD_DataSetBoolean:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); q->METHOD_DataSetBoolean(v[0]->toQString(), v[1]->tot_boolean()); break; }
case pcode___movie__METHOD_DataSetInteger:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); q->METHOD_DataSetInteger(v[0]->toQString(), v[1]->tot_integer()); break; }
case pcode___movie__METHOD_DataSetString:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); q->METHOD_DataSetString(v[0]->toQString(), v[1]->toQString()); break; }
case pcode___movie__METHOD_DataSetDouble:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); q->METHOD_DataSetDouble(v[0]->toQString(), v[1]->tot_double()); break; }

case pcode___movie__METHOD_DataSetLong:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); q->METHOD_DataSetLong(v[0]->toQString(), v[1]->tot_long()); break; }
case pcode___movie__METHOD_DataSetDecimal:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); q->METHOD_DataSetDecimal(v[0]->toQString(), v[1]->toDecimal()); break; }
case pcode___movie__METHOD_DataSetDateTime:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); q->METHOD_DataSetDateTime(v[0]->toQString(), v[1]->totDateTime()); break; }

case pcode___movie__METHOD_DataBoolean:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); interpreter_parameter *p = new interpreter_parameter(q->METHOD_DataBoolean(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___movie__METHOD_DataInteger:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); interpreter_parameter *p = new interpreter_parameter(q->METHOD_DataInteger(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___movie__METHOD_DataString:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); interpreter_parameter *p = new interpreter_parameter(q->METHOD_DataString(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___movie__METHOD_DataDouble:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); interpreter_parameter *p = new interpreter_parameter(q->METHOD_DataDouble(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }

case pcode___movie__METHOD_DataLong:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); interpreter_parameter *p = new interpreter_parameter(q->METHOD_DataLong(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___movie__METHOD_DataDecimal:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); interpreter_parameter *p = new interpreter_parameter(q->METHOD_DataDecimal(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___movie__METHOD_DataDateTime:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); interpreter_parameter *p = new interpreter_parameter(q->METHOD_DataDateTime(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }


case pcode___movie__METHOD_ClearFocus:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); q->METHOD_ClearFocus(); break; }
case pcode___movie__METHOD_ToggleVisible:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); q->METHOD_ToggleVisible(); break; }
case pcode___movie__METHOD_SingleShot:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); q->METHOD_SingleShot(v[0]->tot_integer()); break; }
case pcode___movie__METHOD_StartTimer:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); q->METHOD_StartTimer(); break; }
case pcode___movie__METHOD_StopTimer:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); q->METHOD_StopTimer(); break; }

case pcode___movie__METHOD_LocalX:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); interpreter_parameter *p = new interpreter_parameter(q->METHOD_LocalX(v[0]->tot_integer())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___movie__METHOD_LocalY:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); interpreter_parameter *p = new interpreter_parameter(q->METHOD_LocalY(v[0]->tot_integer())); if (bReturn) pushStack(p); else delete p; break; }

case pcode___movie__METHOD_GlobalX:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); interpreter_parameter *p = new interpreter_parameter(q->METHOD_GlobalX(v[0]->tot_integer())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___movie__METHOD_GlobalY:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); interpreter_parameter *p = new interpreter_parameter(q->METHOD_GlobalY(v[0]->tot_integer())); if (bReturn) pushStack(p); else delete p; break; }

case pcode___movie__METHOD_UnderMouse:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); interpreter_parameter *p = new interpreter_parameter(q->METHOD_UnderMouse()); if (bReturn) pushStack(p); else delete p; break; }

case pcode___movie__SETPROPERTY_Mask:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); q->SETPROPERTY_Mask(v[0]->toQString()); break; }
case pcode___movie__GETPROPERTY_Mask:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_Mask()); if (bReturn) pushStack(p); else delete p; break; }
                         
case pcode___movie__SETPROPERTY_SoundOnEvent:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); q->SETPROPERTY_SoundOnEvent(v[0]->toQString()); break; }
case pcode___movie__GETPROPERTY_SoundOnEvent:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_SoundOnEvent()); if (bReturn) pushStack(p); else delete p; break; }

case pcode___movie__SETPROPERTY_Left:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); q->SETPROPERTY_X(v[0]->tot_integer()); break; }
case pcode___movie__GETPROPERTY_Left:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie();  i = q->GETPROPERTY_X(); if (bReturn) pushStackInteger(i); break; }
case pcode___movie__SETPROPERTY_Top:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); q->SETPROPERTY_Y(v[0]->tot_integer()); break; }
case pcode___movie__GETPROPERTY_Top:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie();  i =  q->GETPROPERTY_Y(); if (bReturn) pushStackInteger(i); break; }

case pcode___movie__SETPROPERTY_LocalX:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); q->SETPROPERTY_X(v[0]->tot_integer()); break; }
case pcode___movie__GETPROPERTY_LocalX:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie();  i = q->GETPROPERTY_X(); if (bReturn) pushStackInteger(i); break; }
case pcode___movie__SETPROPERTY_LocalY:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); q->SETPROPERTY_Y(v[0]->tot_integer()); break; }
case pcode___movie__GETPROPERTY_LocalY:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie();  i =  q->GETPROPERTY_Y(); if (bReturn) pushStackInteger(i); break; }

case pcode___movie__SETPROPERTY_DrawOnPaint:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); q->SETPROPERTY_DrawOnPaint(v[0]->tot_boolean()); break; }
case pcode___movie__GETPROPERTY_DrawOnPaint:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_DrawOnPaint()); if (bReturn) pushStack(p); else delete p; break; }
                    
case pcode___movie__SETPROPERTY_Palette:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); q->SETPROPERTY_Palette(v[0]->toQString()); break; }
case pcode___movie__GETPROPERTY_Palette:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_Palette()); if (bReturn) pushStack(p); else delete p; break; }
                         
case pcode___movie__SETPROPERTY_BackgroundStyle:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); q->SETPROPERTY_BackgroundStyle(v[0]->toQString()); break; }
case pcode___movie__GETPROPERTY_BackgroundStyle:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_BackgroundStyle()); if (bReturn) pushStack(p); else delete p; break; }
                         

case pcode___movie__SETPROPERTY_Brightness:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); q->SETPROPERTY_Brightness(v[0]->tot_integer()); break; }
case pcode___movie__GETPROPERTY_Brightness:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_Brightness()); if (bReturn) pushStack(p); else delete p; break; }

case pcode___movie__SETPROPERTY_Contrast:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); q->SETPROPERTY_Contrast(v[0]->tot_integer()); break; }
case pcode___movie__GETPROPERTY_Contrast:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_Contrast()); if (bReturn) pushStack(p); else delete p; break; }

case pcode___movie__SETPROPERTY_Hue:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); q->SETPROPERTY_Hue(v[0]->tot_integer()); break; }
case pcode___movie__GETPROPERTY_Hue:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_Hue()); if (bReturn) pushStack(p); else delete p; break; }

case pcode___movie__SETPROPERTY_Saturation:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); q->SETPROPERTY_Saturation(v[0]->tot_integer()); break; }
case pcode___movie__GETPROPERTY_Saturation:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_Saturation()); if (bReturn) pushStack(p); else delete p; break; }

case pcode___movie__SETPROPERTY_ScaleMode:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); q->SETPROPERTY_ScaleMode(v[0]->toQString()); break; }
case pcode___movie__GETPROPERTY_ScaleMode:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_ScaleMode()); if (bReturn) pushStack(p); else delete p; break; }

case pcode___movie__SETPROPERTY_AspectRatio:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); q->SETPROPERTY_AspectRatio(v[0]->toQString()); break; }
case pcode___movie__GETPROPERTY_AspectRatio:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_AspectRatio()); if (bReturn) pushStack(p); else delete p; break; }

case pcode___movie__METHOD_State:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); interpreter_parameter *p = new interpreter_parameter( q->METHOD_State()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___movie__METHOD_ErrorType:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); interpreter_parameter *p = new interpreter_parameter( q->METHOD_ErrorType()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___movie__METHOD_ErrorString:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); interpreter_parameter *p = new interpreter_parameter( q->METHOD_ErrorString()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___movie__METHOD_CurrentTime:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); interpreter_parameter *p = new interpreter_parameter( q->METHOD_CurrentTime()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___movie__METHOD_TotalTime:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); interpreter_parameter *p = new interpreter_parameter( q->METHOD_TotalTime()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___movie__METHOD_IsPlaying:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); interpreter_parameter *p = new interpreter_parameter( q->METHOD_IsPlaying()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___movie__METHOD_IsPaused:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); interpreter_parameter *p = new interpreter_parameter( q->METHOD_IsPaused()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___movie__METHOD_IsMuted:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); interpreter_parameter *p = new interpreter_parameter( q->METHOD_IsMuted()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___movie__METHOD_IsSeekable:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); interpreter_parameter *p = new interpreter_parameter( q->METHOD_IsSeekable()); if (bReturn) pushStack(p); else delete p; break; }

case pcode___movie__METHOD_Play:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); q->METHOD_Play(); break; }
case pcode___movie__METHOD_Play1:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); q->METHOD_Play(v[0]->toQString()); break; }
case pcode___movie__METHOD_Load:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); q->METHOD_Load(v[0]->toQString()); break; }
case pcode___movie__METHOD_PlayInQueue:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); q->METHOD_PlayInQueue(v[0]->toQString()); break; }
case pcode___movie__METHOD_Pause:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); q->METHOD_Pause(); break; }
case pcode___movie__METHOD_Stop:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); q->METHOD_Stop(); break; }
case pcode___movie__METHOD_ClearQueue:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); q->METHOD_ClearQueue(); break; }
case pcode___movie__METHOD_Seek:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); q->METHOD_Seek(v[0]->tot_long()); break; }

								
case pcode___movie__SETPROPERTY_StringValue:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); q->SETPROPERTY_StringValue(v[0]->toQString()); break; }
case pcode___movie__GETPROPERTY_StringValue:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_StringValue()); if (bReturn) pushStack(p); else delete p; break; }

case pcode___movie__SETPROPERTY_TransitionTime:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); q->SETPROPERTY_TransitionTime(v[0]->tot_long()); break; }
case pcode___movie__GETPROPERTY_TransitionTime:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_TransitionTime()); if (bReturn) pushStack(p); else delete p; break; }

case pcode___movie__SETPROPERTY_Muted:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); q->SETPROPERTY_Muted(v[0]->tot_boolean()); break; }
case pcode___movie__GETPROPERTY_Muted:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_Muted()); if (bReturn) pushStack(p); else delete p; break; }

case pcode___movie__SETPROPERTY_Volume:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); q->SETPROPERTY_Volume(v[0]->tot_integer()); break; }
case pcode___movie__GETPROPERTY_Volume:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_Volume()); if (bReturn) pushStack(p); else delete p; break; }

case pcode___movie__SETPROPERTY_PrefinishMark:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); q->SETPROPERTY_PrefinishMark(v[0]->tot_long()); break; }
case pcode___movie__GETPROPERTY_PrefinishMark:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_PrefinishMark()); if (bReturn) pushStack(p); else delete p; break; }

case pcode___movie__SETPROPERTY_Tick:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); q->SETPROPERTY_Tick(v[0]->tot_integer()); break; }
case pcode___movie__GETPROPERTY_Tick:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_Tick()); if (bReturn) pushStack(p); else delete p; break; }






case pcode___movie__SETPROPERTY_Layout:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); q->SETPROPERTY_Layout(v[0]->toQString()); break; }
case pcode___movie__GETPROPERTY_Layout:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_Layout()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___movie__METHOD_Move:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); q->METHOD_Move(v[0]->tot_integer(), v[1]->tot_integer()); break; }
case pcode___movie__METHOD_Resize:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); q->METHOD_Resize(v[0]->tot_integer(), v[1]->tot_integer()); break; }
case pcode___movie__METHOD_Show:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); q->METHOD_Show(); break; }
case pcode___movie__METHOD_Hide:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); q->METHOD_Hide(); break; }
case pcode___movie__METHOD_RepaintAlways:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); q->METHOD_RepaintAlways(); break; }
case pcode___movie__METHOD_Repaint:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); q->METHOD_Repaint(); break; }
case pcode___movie__METHOD_Raise:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); q->METHOD_Raise(); break; }
case pcode___movie__METHOD_Lower:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); q->METHOD_Lower(); break; }
case pcode___movie__METHOD_Close:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); q->METHOD_Close(); break; }
case pcode___movie__METHOD_Open:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); q->METHOD_Open(); break; }
case pcode___movie__METHOD_SetFocus:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); q->METHOD_SetFocus(); break; }
case pcode___movie__SETPROPERTY_Name:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); q->SETPROPERTY_Name(v[0]->toQString()); break; }
case pcode___movie__GETPROPERTY_Name:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_Name()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___movie__SETPROPERTY_Group:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); q->SETPROPERTY_Group(v[0]->toQString()); break; }
case pcode___movie__GETPROPERTY_Group:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_Group()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___movie__SETPROPERTY_Background:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); q->SETPROPERTY_Background(v[0]->toQString()); break; }
case pcode___movie__GETPROPERTY_Background:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_Background()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___movie__SETPROPERTY_X:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); q->SETPROPERTY_X(v[0]->tot_integer()); break; }
case pcode___movie__GETPROPERTY_X:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie();  i = q->GETPROPERTY_X(); if (bReturn) pushStackInteger(i); break; }
case pcode___movie__SETPROPERTY_Y:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); q->SETPROPERTY_Y(v[0]->tot_integer()); break; }
case pcode___movie__GETPROPERTY_Y:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie();  i =  q->GETPROPERTY_Y(); if (bReturn) pushStackInteger(i); break; }
case pcode___movie__SETPROPERTY_Width:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); q->SETPROPERTY_Width(v[0]->tot_integer()); break; }
case pcode___movie__GETPROPERTY_Width:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie();  i = q->GETPROPERTY_Width(); if (bReturn) pushStackInteger(i); break; }
case pcode___movie__SETPROPERTY_Height:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); q->SETPROPERTY_Height(v[0]->tot_integer()); break; }
case pcode___movie__GETPROPERTY_Height:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie();  i = q->GETPROPERTY_Height(); if (bReturn) pushStackInteger(i); break; }
case pcode___movie__GETPROPERTY_GlobalX:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie();  i = q->GETPROPERTY_GlobalX(); if (bReturn) pushStackInteger(i); break; }
case pcode___movie__GETPROPERTY_GlobalY:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie();  i = q->GETPROPERTY_GlobalY(); if (bReturn) pushStackInteger(i); break; }
case pcode___movie__GETPROPERTY_OldX:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie();  i = q->GETPROPERTY_OldX(); if (bReturn) pushStackInteger(i); break; }
case pcode___movie__GETPROPERTY_OldY:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie();  i = q->GETPROPERTY_OldY(); if (bReturn) pushStackInteger(i); break; }
case pcode___movie__GETPROPERTY_OldWidth:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie();  i = q->GETPROPERTY_OldWidth(); if (bReturn) pushStackInteger(i); break; }
case pcode___movie__GETPROPERTY_OldHeight:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie();  i = q->GETPROPERTY_OldHeight(); if (bReturn) pushStackInteger(i); break; }
case pcode___movie__SETPROPERTY_MinimumWidth:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); q->SETPROPERTY_MinimumWidth(v[0]->tot_integer()); break; }
case pcode___movie__GETPROPERTY_MinimumWidth:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie();  i =  q->GETPROPERTY_MinimumWidth(); if (bReturn) pushStackInteger(i); break; }
case pcode___movie__SETPROPERTY_MinimumHeight:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); q->SETPROPERTY_MinimumHeight(v[0]->tot_integer()); break; }
case pcode___movie__GETPROPERTY_MinimumHeight:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie();  i =  q->GETPROPERTY_MinimumHeight(); if (bReturn) pushStackInteger(i); break; }
case pcode___movie__SETPROPERTY_MaximumWidth:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); q->SETPROPERTY_MaximumWidth(v[0]->tot_integer()); break; }
case pcode___movie__GETPROPERTY_MaximumWidth:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie();  i =  q->GETPROPERTY_MaximumWidth(); if (bReturn) pushStackInteger(i); break; }
case pcode___movie__SETPROPERTY_MaximumHeight:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); q->SETPROPERTY_MaximumHeight(v[0]->tot_integer()); break; }
case pcode___movie__GETPROPERTY_MaximumHeight:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie();  i =  q->GETPROPERTY_MaximumHeight(); if (bReturn) pushStackInteger(i); break; }
case pcode___movie__SETPROPERTY_Tag:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); q->SETPROPERTY_Tag(v[0]->toQString()); break; }
case pcode___movie__GETPROPERTY_Tag:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_Tag()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___movie__SETPROPERTY_CSV:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); q->SETPROPERTY_CSV(v[0]->toQString()); break; }
case pcode___movie__GETPROPERTY_CSV:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_CSV()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___movie__SETPROPERTY_ParentForm:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); q->SETPROPERTY_ParentForm(v[0]->toQString()); break; }
case pcode___movie__GETPROPERTY_ParentForm:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_ParentForm()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___movie__SETPROPERTY_ParentControl:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); q->SETPROPERTY_ParentControl(v[0]->toQString()); break; }
case pcode___movie__GETPROPERTY_ParentControl:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_ParentControl()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___movie__SETPROPERTY_DragDrop:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); q->SETPROPERTY_DragDrop(v[0]->tot_boolean()); break; }
case pcode___movie__GETPROPERTY_ParentControl1:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_ParentControl()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___movie__SETPROPERTY_ControlType:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); q->SETPROPERTY_ControlType(v[0]->toQString()); break; }
case pcode___movie__GETPROPERTY_ControlType:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_ControlType()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___movie__SETPROPERTY_Focus:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); q->SETPROPERTY_Focus(v[0]->tot_boolean()); break; }
case pcode___movie__GETPROPERTY_Focus:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie();  b = q->GETPROPERTY_Focus(); if (bReturn) pushStackBoolean(b); break; }
case pcode___movie__SETPROPERTY_FocusPolicy:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); q->SETPROPERTY_FocusPolicy(v[0]->toQString()); break; }
case pcode___movie__GETPROPERTY_FocusPolicy:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_FocusPolicy()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___movie__SETPROPERTY_FocusProxy:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); q->SETPROPERTY_FocusProxy(v[0]->toQString()); break; }
case pcode___movie__GETPROPERTY_FocusProxy:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_FocusProxy()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___movie__SETPROPERTY_FocusOrder:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); q->SETPROPERTY_FocusOrder(v[0]->tot_integer()); break; }
case pcode___movie__GETPROPERTY_FocusOrder:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie();  i = q->GETPROPERTY_FocusOrder(); if (bReturn) pushStackInteger(i); break; }
case pcode___movie__SETPROPERTY_Cursor:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); q->SETPROPERTY_Cursor(v[0]->toQString()); break; }
case pcode___movie__GETPROPERTY_Cursor:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_Cursor()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___movie__SETPROPERTY_FontName:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); q->SETPROPERTY_FontName(v[0]->toQString()); break; }
case pcode___movie__GETPROPERTY_FontName:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_FontName()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___movie__SETPROPERTY_FontSize:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); q->SETPROPERTY_FontSize(v[0]->tot_integer()); break; }
case pcode___movie__GETPROPERTY_FontSize:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie();  i = q->GETPROPERTY_FontSize(); if (bReturn) pushStackInteger(i); break; }
case pcode___movie__SETPROPERTY_FontItalic:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); q->SETPROPERTY_FontItalic(v[0]->tot_boolean()); break; }
case pcode___movie__GETPROPERTY_FontItalic:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie();  b = q->GETPROPERTY_FontItalic(); if (bReturn) pushStackBoolean(b); break; }
case pcode___movie__SETPROPERTY_FontBold:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); q->SETPROPERTY_FontBold(v[0]->tot_boolean()); break; }
case pcode___movie__GETPROPERTY_FontBold:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie();  b = q->GETPROPERTY_FontBold(); if (bReturn) pushStackBoolean(b); break; }
case pcode___movie__SETPROPERTY_FontUnderline:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); q->SETPROPERTY_FontUnderline(v[0]->tot_boolean()); break; }
case pcode___movie__GETPROPERTY_FontUnderline:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie();  b = q->GETPROPERTY_FontUnderline(); if (bReturn) pushStackBoolean(b); break; }
case pcode___movie__SETPROPERTY_FontColor:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); q->SETPROPERTY_FontColor(v[0]->toQString()); break; }
case pcode___movie__GETPROPERTY_FontColor:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_FontColor()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___movie__SETPROPERTY_Enabled:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); q->SETPROPERTY_Enabled(v[0]->tot_boolean()); break; }
case pcode___movie__GETPROPERTY_Enabled:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie();  b = q->GETPROPERTY_Enabled(); if (bReturn) pushStackBoolean(b); break; }
case pcode___movie__SETPROPERTY_Visible:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); q->SETPROPERTY_Visible(v[0]->tot_boolean()); break; }
case pcode___movie__GETPROPERTY_Visible:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie();  b = q->GETPROPERTY_Visible(); if (bReturn) pushStackBoolean(b); break; }
case pcode___movie__SETPROPERTY_StatusTip:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); q->SETPROPERTY_StatusTip(v[0]->toQString()); break; }
case pcode___movie__GETPROPERTY_StatusTip:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_StatusTip()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___movie__SETPROPERTY_ToolTip:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); q->SETPROPERTY_ToolTip(v[0]->toQString()); break; }
case pcode___movie__GETPROPERTY_ToolTip:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_ToolTip()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___movie__SETPROPERTY_StyleSheet:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); q->SETPROPERTY_StyleSheet(v[0]->toQString()); break; }
case pcode___movie__GETPROPERTY_StyleSheet:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_StyleSheet()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___movie__SETPROPERTY_WhatsThis:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); q->SETPROPERTY_WhatsThis(v[0]->toQString()); break; }
case pcode___movie__GETPROPERTY_WhatsThis:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_WhatsThis()); if (bReturn) pushStack(p); else delete p; break; }
//case pcode___movie__SETPROPERTY_TimerInterval:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); q->SETPROPERTY_TimerInterval(v[0]->tot_integer()); break; }
//case pcode___movie__GETPROPERTY_TimerInterval:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie();  i = q->GETPROPERTY_TimerInterval(); if (bReturn) pushStackInteger(i); break; }
case pcode___movie__SETPROPERTY_Opacity:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); q->SETPROPERTY_Opacity(v[0]->tot_integer()); break; }
case pcode___movie__GETPROPERTY_Opacity:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie();  i = q->GETPROPERTY_Opacity(); if (bReturn) pushStackInteger(i); break; }
case pcode___movie__SETPROPERTY_BoxIndex:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); q->SETPROPERTY_BoxIndex(v[0]->tot_integer()); break; }
case pcode___movie__GETPROPERTY_BoxIndex:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie();  i = q->GETPROPERTY_BoxIndex(); if (bReturn) pushStackInteger(i); break; }
case pcode___movie__SETPROPERTY_SplitIndex:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); q->SETPROPERTY_SplitIndex(v[0]->tot_integer()); break; }
case pcode___movie__GETPROPERTY_SplitIndex:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie();  i = q->GETPROPERTY_SplitIndex(); if (bReturn) pushStackInteger(i); break; }
case pcode___movie__SETPROPERTY_TabIndex:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); q->SETPROPERTY_TabIndex(v[0]->tot_integer()); break; }
case pcode___movie__GETPROPERTY_TabIndex:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie();  i = q->GETPROPERTY_TabIndex(); if (bReturn) pushStackInteger(i); break; }
case pcode___movie__SETPROPERTY_BoxX:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); q->SETPROPERTY_BoxX(v[0]->tot_integer()); break; }
case pcode___movie__GETPROPERTY_BoxX:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie();  i = q->GETPROPERTY_BoxX(); if (bReturn) pushStackInteger(i); break; }
case pcode___movie__SETPROPERTY_BoxY:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); q->SETPROPERTY_BoxY(v[0]->tot_integer()); break; }
case pcode___movie__GETPROPERTY_BoxY:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie();  i = q->GETPROPERTY_BoxY(); if (bReturn) pushStackInteger(i); break; }
case pcode___movie__SETPROPERTY_ParentIndex:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); q->SETPROPERTY_ParentIndex(v[0]->tot_integer()); break; }
case pcode___movie__GETPROPERTY_ParentIndex:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie();  i = q->GETPROPERTY_ParentIndex(); if (bReturn) pushStackInteger(i); else delete p; break; }
case pcode___movie__SETPROPERTY_ControlType1:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); q->SETPROPERTY_ControlType(v[0]->toQString()); break; }
case pcode___movie__GETPROPERTY_ControlType1:{ getParam(v, m, n); identifier = popStack(); kb_movie *q = (kb_movie *) identifier->to_movie(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_ControlType()); if (bReturn) pushStack(p); else delete p; break; }
