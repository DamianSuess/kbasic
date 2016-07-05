case pcode___image___image1:{ getParam(v, m, n); pp = new kb_image(0); myStack->pushParameter(pcode___image, pp); ((kb_image *) pp)->setInterpreter(this); break; }
case pcode___image___image:{ getParam(v, m, n); pp = new kb_image(v[0]->to_form()); myStack->pushParameter(pcode___image, pp); ((kb_image *) pp)->setInterpreter(this); break; }

case pcode___image__SETPROPERTY_MouseTracking:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); q->SETPROPERTY_MouseTracking(v[0]->tot_boolean()); break; }
case pcode___image__GETPROPERTY_MouseTracking:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_MouseTracking()); if (bReturn) pushStack(p); else delete p; break; }
                                 
case pcode___image__SETPROPERTY_CursorAnimation:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); q->SETPROPERTY_CursorAnimation(v[0]->toQString()); break; }
case pcode___image__GETPROPERTY_CursorAnimation:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_CursorAnimation()); if (bReturn) pushStack(p); else delete p; break; }

case pcode___image__METHOD_DataIds:{   
  
  getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); 
   
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

case pcode___image__METHOD_DataRemove:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); q->METHOD_DataRemove(v[0]->toQString()); break; }
case pcode___image__METHOD_DataRemoveAll:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); q->METHOD_DataRemoveAll(); break; }
case pcode___image__METHOD_DataSetBoolean:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); q->METHOD_DataSetBoolean(v[0]->toQString(), v[1]->tot_boolean()); break; }
case pcode___image__METHOD_DataSetInteger:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); q->METHOD_DataSetInteger(v[0]->toQString(), v[1]->tot_integer()); break; }
case pcode___image__METHOD_DataSetString:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); q->METHOD_DataSetString(v[0]->toQString(), v[1]->toQString()); break; }
case pcode___image__METHOD_DataSetDouble:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); q->METHOD_DataSetDouble(v[0]->toQString(), v[1]->tot_double()); break; }

case pcode___image__METHOD_DataSetLong:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); q->METHOD_DataSetLong(v[0]->toQString(), v[1]->tot_long()); break; }
case pcode___image__METHOD_DataSetDecimal:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); q->METHOD_DataSetDecimal(v[0]->toQString(), v[1]->toDecimal()); break; }
case pcode___image__METHOD_DataSetDateTime:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); q->METHOD_DataSetDateTime(v[0]->toQString(), v[1]->totDateTime()); break; }

case pcode___image__METHOD_DataBoolean:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); interpreter_parameter *p = new interpreter_parameter(q->METHOD_DataBoolean(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___image__METHOD_DataInteger:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); interpreter_parameter *p = new interpreter_parameter(q->METHOD_DataInteger(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___image__METHOD_DataString:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); interpreter_parameter *p = new interpreter_parameter(q->METHOD_DataString(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___image__METHOD_DataDouble:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); interpreter_parameter *p = new interpreter_parameter(q->METHOD_DataDouble(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }

case pcode___image__METHOD_DataLong:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); interpreter_parameter *p = new interpreter_parameter(q->METHOD_DataLong(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___image__METHOD_DataDecimal:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); interpreter_parameter *p = new interpreter_parameter(q->METHOD_DataDecimal(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___image__METHOD_DataDateTime:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); interpreter_parameter *p = new interpreter_parameter(q->METHOD_DataDateTime(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }


case pcode___image__METHOD_ClearFocus:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); q->METHOD_ClearFocus(); break; }
case pcode___image__METHOD_ToggleVisible:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); q->METHOD_ToggleVisible(); break; }
case pcode___image__METHOD_SingleShot:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); q->METHOD_SingleShot(v[0]->tot_integer()); break; }
case pcode___image__METHOD_StartTimer:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); q->METHOD_StartTimer(); break; }
case pcode___image__METHOD_StopTimer:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); q->METHOD_StopTimer(); break; }

case pcode___image__METHOD_LocalX:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); interpreter_parameter *p = new interpreter_parameter(q->METHOD_LocalX(v[0]->tot_integer())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___image__METHOD_LocalY:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); interpreter_parameter *p = new interpreter_parameter(q->METHOD_LocalY(v[0]->tot_integer())); if (bReturn) pushStack(p); else delete p; break; }

case pcode___image__METHOD_GlobalX:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); interpreter_parameter *p = new interpreter_parameter(q->METHOD_GlobalX(v[0]->tot_integer())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___image__METHOD_GlobalY:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); interpreter_parameter *p = new interpreter_parameter(q->METHOD_GlobalY(v[0]->tot_integer())); if (bReturn) pushStack(p); else delete p; break; }

case pcode___image__METHOD_UnderMouse:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); interpreter_parameter *p = new interpreter_parameter(q->METHOD_UnderMouse()); if (bReturn) pushStack(p); else delete p; break; }

case pcode___image__SETPROPERTY_Mask:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); q->SETPROPERTY_Mask(v[0]->toQString()); break; }
case pcode___image__GETPROPERTY_Mask:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_Mask()); if (bReturn) pushStack(p); else delete p; break; }
                         
case pcode___image__SETPROPERTY_SoundOnEvent:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); q->SETPROPERTY_SoundOnEvent(v[0]->toQString()); break; }
case pcode___image__GETPROPERTY_SoundOnEvent:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_SoundOnEvent()); if (bReturn) pushStack(p); else delete p; break; }

case pcode___image__SETPROPERTY_Left:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); q->SETPROPERTY_X(v[0]->tot_integer()); break; }
case pcode___image__GETPROPERTY_Left:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image();  i = q->GETPROPERTY_X(); if (bReturn) pushStackInteger(i); break; }
case pcode___image__SETPROPERTY_Top:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); q->SETPROPERTY_Y(v[0]->tot_integer()); break; }
case pcode___image__GETPROPERTY_Top:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image();  i =  q->GETPROPERTY_Y(); if (bReturn) pushStackInteger(i); break; }

case pcode___image__SETPROPERTY_LocalX:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); q->SETPROPERTY_X(v[0]->tot_integer()); break; }
case pcode___image__GETPROPERTY_LocalX:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image();  i = q->GETPROPERTY_X(); if (bReturn) pushStackInteger(i); break; }
case pcode___image__SETPROPERTY_LocalY:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); q->SETPROPERTY_Y(v[0]->tot_integer()); break; }
case pcode___image__GETPROPERTY_LocalY:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image();  i =  q->GETPROPERTY_Y(); if (bReturn) pushStackInteger(i); break; }

case pcode___image__SETPROPERTY_DrawOnPaint:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); q->SETPROPERTY_DrawOnPaint(v[0]->tot_boolean()); break; }
case pcode___image__GETPROPERTY_DrawOnPaint:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_DrawOnPaint()); if (bReturn) pushStack(p); else delete p; break; }
                    
case pcode___image__SETPROPERTY_Palette:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); q->SETPROPERTY_Palette(v[0]->toQString()); break; }
case pcode___image__GETPROPERTY_Palette:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_Palette()); if (bReturn) pushStack(p); else delete p; break; }
                         
case pcode___image__SETPROPERTY_BackgroundStyle:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); q->SETPROPERTY_BackgroundStyle(v[0]->toQString()); break; }
case pcode___image__GETPROPERTY_BackgroundStyle:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_BackgroundStyle()); if (bReturn) pushStack(p); else delete p; break; }
                         

case pcode___image__SETPROPERTY_Value:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); q->SETPROPERTY_StringValue(v[0]->toQString()); break; }
case pcode___image__GETPROPERTY_Value:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_StringValue()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___image__GETPROPERTY_OldValue:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_OldStringValue()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___image__SETPROPERTY_Text:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); q->SETPROPERTY_StringValue(v[0]->toQString()); break; }
case pcode___image__GETPROPERTY_Text:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_StringValue()); if (bReturn) pushStack(p); else delete p; break; }

case pcode___image__SETPROPERTY_Layout:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); q->SETPROPERTY_Layout(v[0]->toQString()); break; }
case pcode___image__GETPROPERTY_Layout:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_Layout()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___image__METHOD_Move:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); q->METHOD_Move(v[0]->tot_integer(), v[1]->tot_integer()); break; }
case pcode___image__METHOD_Resize:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); q->METHOD_Resize(v[0]->tot_integer(), v[1]->tot_integer()); break; }
case pcode___image__METHOD_Show:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); q->METHOD_Show(); break; }
case pcode___image__METHOD_Hide:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); q->METHOD_Hide(); break; }
case pcode___image__METHOD_RepaintAlways:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); q->METHOD_RepaintAlways(); break; }
case pcode___image__METHOD_Repaint:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); q->METHOD_Repaint(); break; }
case pcode___image__METHOD_Raise:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); q->METHOD_Raise(); break; }
case pcode___image__METHOD_Lower:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); q->METHOD_Lower(); break; }
case pcode___image__METHOD_Close:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); q->METHOD_Close(); break; }
case pcode___image__METHOD_Open:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); q->METHOD_Open(); break; }
case pcode___image__METHOD_SetFocus:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); q->METHOD_SetFocus(); break; }
case pcode___image__SETPROPERTY_Name:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); q->SETPROPERTY_Name(v[0]->toQString()); break; }
case pcode___image__GETPROPERTY_Name:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_Name()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___image__SETPROPERTY_Group:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); q->SETPROPERTY_Group(v[0]->toQString()); break; }
case pcode___image__GETPROPERTY_Group:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_Group()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___image__SETPROPERTY_Background:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); q->SETPROPERTY_Background(v[0]->toQString()); break; }
case pcode___image__GETPROPERTY_Background:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_Background()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___image__SETPROPERTY_X:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); q->SETPROPERTY_X(v[0]->tot_integer()); break; }
case pcode___image__GETPROPERTY_X:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); i = q->GETPROPERTY_X(); if (bReturn) pushStackInteger(i); break; }
case pcode___image__SETPROPERTY_Y:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); q->SETPROPERTY_Y(v[0]->tot_integer()); break; }
case pcode___image__GETPROPERTY_Y:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); i =  q->GETPROPERTY_Y(); if (bReturn) pushStackInteger(i); break; }
case pcode___image__SETPROPERTY_Width:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); q->SETPROPERTY_Width(v[0]->tot_integer()); break; }
case pcode___image__GETPROPERTY_Width:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); i = q->GETPROPERTY_Width(); if (bReturn) pushStackInteger(i); break; }
case pcode___image__SETPROPERTY_Height:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); q->SETPROPERTY_Height(v[0]->tot_integer()); break; }
case pcode___image__GETPROPERTY_Height:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); i = q->GETPROPERTY_Height(); if (bReturn) pushStackInteger(i); break; }
case pcode___image__GETPROPERTY_GlobalX:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); i = q->GETPROPERTY_GlobalX(); if (bReturn) pushStackInteger(i); break; }
case pcode___image__GETPROPERTY_GlobalY:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); i = q->GETPROPERTY_GlobalY(); if (bReturn) pushStackInteger(i); break; }
case pcode___image__GETPROPERTY_OldX:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); i = q->GETPROPERTY_OldX(); if (bReturn) pushStackInteger(i); break; }
case pcode___image__GETPROPERTY_OldY:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); i = q->GETPROPERTY_OldY(); if (bReturn) pushStackInteger(i); break; }
case pcode___image__GETPROPERTY_OldWidth:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); i = q->GETPROPERTY_OldWidth(); if (bReturn) pushStackInteger(i); break; }
case pcode___image__GETPROPERTY_OldHeight:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); i = q->GETPROPERTY_OldHeight(); if (bReturn) pushStackInteger(i); break; }
case pcode___image__SETPROPERTY_MinimumWidth:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); q->SETPROPERTY_MinimumWidth(v[0]->tot_integer()); break; }
case pcode___image__GETPROPERTY_MinimumWidth:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); i =  q->GETPROPERTY_MinimumWidth(); if (bReturn) pushStackInteger(i); break; }
case pcode___image__SETPROPERTY_MinimumHeight:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); q->SETPROPERTY_MinimumHeight(v[0]->tot_integer()); break; }
case pcode___image__GETPROPERTY_MinimumHeight:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); i =  q->GETPROPERTY_MinimumHeight(); if (bReturn) pushStackInteger(i); break; }
case pcode___image__SETPROPERTY_MaximumWidth:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); q->SETPROPERTY_MaximumWidth(v[0]->tot_integer()); break; }
case pcode___image__GETPROPERTY_MaximumWidth:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); i =  q->GETPROPERTY_MaximumWidth(); if (bReturn) pushStackInteger(i); break; }
case pcode___image__SETPROPERTY_MaximumHeight:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); q->SETPROPERTY_MaximumHeight(v[0]->tot_integer()); break; }
case pcode___image__GETPROPERTY_MaximumHeight:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); i =  q->GETPROPERTY_MaximumHeight(); if (bReturn) pushStackInteger(i); break; }
case pcode___image__SETPROPERTY_Tag:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); q->SETPROPERTY_Tag(v[0]->toQString()); break; }
case pcode___image__GETPROPERTY_Tag:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_Tag()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___image__SETPROPERTY_CSV:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); q->SETPROPERTY_CSV(v[0]->toQString()); break; }
case pcode___image__GETPROPERTY_CSV:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_CSV()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___image__SETPROPERTY_ParentForm:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); q->SETPROPERTY_ParentForm(v[0]->toQString()); break; }
case pcode___image__GETPROPERTY_ParentForm:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_ParentForm()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___image__SETPROPERTY_ParentControl:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); q->SETPROPERTY_ParentControl(v[0]->toQString()); break; }
case pcode___image__GETPROPERTY_ParentControl:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_ParentControl()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___image__SETPROPERTY_DragDrop:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); q->SETPROPERTY_DragDrop(v[0]->tot_boolean()); break; }
case pcode___image__GETPROPERTY_ParentControl1:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_ParentControl()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___image__SETPROPERTY_ControlType:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); q->SETPROPERTY_ControlType(v[0]->toQString()); break; }
case pcode___image__GETPROPERTY_ControlType:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_ControlType()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___image__SETPROPERTY_Focus:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); q->SETPROPERTY_Focus(v[0]->tot_boolean()); break; }
case pcode___image__GETPROPERTY_Focus:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); b = q->GETPROPERTY_Focus(); if (bReturn) pushStackBoolean(b); break; }
case pcode___image__SETPROPERTY_FocusPolicy:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); q->SETPROPERTY_FocusPolicy(v[0]->toQString()); break; }
case pcode___image__GETPROPERTY_FocusPolicy:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_FocusPolicy()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___image__SETPROPERTY_FocusProxy:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); q->SETPROPERTY_FocusProxy(v[0]->toQString()); break; }
case pcode___image__GETPROPERTY_FocusProxy:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_FocusProxy()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___image__SETPROPERTY_FocusOrder:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); q->SETPROPERTY_FocusOrder(v[0]->tot_integer()); break; }
case pcode___image__GETPROPERTY_FocusOrder:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); i = q->GETPROPERTY_FocusOrder(); if (bReturn) pushStackInteger(i); break; }
case pcode___image__SETPROPERTY_Cursor:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); q->SETPROPERTY_Cursor(v[0]->toQString()); break; }
case pcode___image__GETPROPERTY_Cursor:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_Cursor()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___image__SETPROPERTY_FontName:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); q->SETPROPERTY_FontName(v[0]->toQString()); break; }
case pcode___image__GETPROPERTY_FontName:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_FontName()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___image__SETPROPERTY_FontSize:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); q->SETPROPERTY_FontSize(v[0]->tot_integer()); break; }
case pcode___image__GETPROPERTY_FontSize:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); i = q->GETPROPERTY_FontSize(); if (bReturn) pushStackInteger(i); break; }
case pcode___image__SETPROPERTY_FontItalic:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); q->SETPROPERTY_FontItalic(v[0]->tot_boolean()); break; }
case pcode___image__GETPROPERTY_FontItalic:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); b = q->GETPROPERTY_FontItalic(); if (bReturn) pushStackBoolean(b); break; }
case pcode___image__SETPROPERTY_FontBold:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); q->SETPROPERTY_FontBold(v[0]->tot_boolean()); break; }
case pcode___image__GETPROPERTY_FontBold:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); b = q->GETPROPERTY_FontBold(); if (bReturn) pushStackBoolean(b); break; }
case pcode___image__SETPROPERTY_FontUnderline:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); q->SETPROPERTY_FontUnderline(v[0]->tot_boolean()); break; }
case pcode___image__GETPROPERTY_FontUnderline:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); b = q->GETPROPERTY_FontUnderline(); if (bReturn) pushStackBoolean(b); break; }
case pcode___image__SETPROPERTY_FontColor:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); q->SETPROPERTY_FontColor(v[0]->toQString()); break; }
case pcode___image__GETPROPERTY_FontColor:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_FontColor()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___image__SETPROPERTY_Enabled:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); q->SETPROPERTY_Enabled(v[0]->tot_boolean()); break; }
case pcode___image__GETPROPERTY_Enabled:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); b = q->GETPROPERTY_Enabled(); if (bReturn) pushStackBoolean(b); break; }
case pcode___image__SETPROPERTY_Visible:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); q->SETPROPERTY_Visible(v[0]->tot_boolean()); break; }
case pcode___image__GETPROPERTY_Visible:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); b = q->GETPROPERTY_Visible(); if (bReturn) pushStackBoolean(b); break; }
case pcode___image__SETPROPERTY_StatusTip:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); q->SETPROPERTY_StatusTip(v[0]->toQString()); break; }
case pcode___image__GETPROPERTY_StatusTip:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_StatusTip()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___image__SETPROPERTY_ToolTip:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); q->SETPROPERTY_ToolTip(v[0]->toQString()); break; }
case pcode___image__GETPROPERTY_ToolTip:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_ToolTip()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___image__SETPROPERTY_StyleSheet:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); q->SETPROPERTY_StyleSheet(v[0]->toQString()); break; }
case pcode___image__GETPROPERTY_StyleSheet:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_StyleSheet()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___image__SETPROPERTY_WhatsThis:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); q->SETPROPERTY_WhatsThis(v[0]->toQString()); break; }
case pcode___image__GETPROPERTY_WhatsThis:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_WhatsThis()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___image__SETPROPERTY_TimerInterval:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); q->SETPROPERTY_TimerInterval(v[0]->tot_integer()); break; }
case pcode___image__GETPROPERTY_TimerInterval:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); i = q->GETPROPERTY_TimerInterval(); if (bReturn) pushStackInteger(i); break; }
case pcode___image__SETPROPERTY_Opacity:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); q->SETPROPERTY_Opacity(v[0]->tot_integer()); break; }
case pcode___image__GETPROPERTY_Opacity:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); i = q->GETPROPERTY_Opacity(); if (bReturn) pushStackInteger(i); break; }
case pcode___image__SETPROPERTY_BoxIndex:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); q->SETPROPERTY_BoxIndex(v[0]->tot_integer()); break; }
case pcode___image__GETPROPERTY_BoxIndex:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); i = q->GETPROPERTY_BoxIndex(); if (bReturn) pushStackInteger(i); break; }
case pcode___image__SETPROPERTY_SplitIndex:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); q->SETPROPERTY_SplitIndex(v[0]->tot_integer()); break; }
case pcode___image__GETPROPERTY_SplitIndex:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); i = q->GETPROPERTY_SplitIndex(); if (bReturn) pushStackInteger(i); break; }
case pcode___image__SETPROPERTY_TabIndex:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); q->SETPROPERTY_TabIndex(v[0]->tot_integer()); break; }
case pcode___image__GETPROPERTY_TabIndex:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); i = q->GETPROPERTY_TabIndex(); if (bReturn) pushStackInteger(i); break; }
case pcode___image__SETPROPERTY_BoxX:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); q->SETPROPERTY_BoxX(v[0]->tot_integer()); break; }
case pcode___image__GETPROPERTY_BoxX:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); i = q->GETPROPERTY_BoxX(); if (bReturn) pushStackInteger(i); break; }
case pcode___image__SETPROPERTY_BoxY:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); q->SETPROPERTY_BoxY(v[0]->tot_integer()); break; }
case pcode___image__GETPROPERTY_BoxY:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); i = q->GETPROPERTY_BoxY(); if (bReturn) pushStackInteger(i); break; }
case pcode___image__SETPROPERTY_ParentIndex:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); q->SETPROPERTY_ParentIndex(v[0]->tot_integer()); break; }
case pcode___image__GETPROPERTY_ParentIndex:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); i = q->GETPROPERTY_ParentIndex(); if (bReturn) pushStackInteger(i); else delete p; break; }
case pcode___image__SETPROPERTY_ControlType1:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); q->SETPROPERTY_ControlType(v[0]->toQString()); break; }
case pcode___image__GETPROPERTY_ControlType1:{ getParam(v, m, n); identifier = popStack(); kb_image *q = (kb_image *) identifier->to_image(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_ControlType()); if (bReturn) pushStack(p); else delete p; break; }
