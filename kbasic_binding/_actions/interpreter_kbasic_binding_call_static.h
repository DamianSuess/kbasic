
case pcode___actions__METHOD_SetEnabled:{ _actions::METHOD_SetEnabled(v[0]->toQString(), v[1]->tot_boolean()); break; }
case pcode___actions__METHOD_IsEnabled:{ p = new interpreter_parameter( _actions::METHOD_IsEnabled(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }

case pcode___actions__METHOD_SetVisible:{ _actions::METHOD_SetVisible(v[0]->toQString(), v[1]->tot_boolean()); break; }
case pcode___actions__METHOD_IsVisible:{ p = new interpreter_parameter( _actions::METHOD_IsVisible(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }

case pcode___actions__METHOD_SetChecked:{ _actions::METHOD_SetChecked(v[0]->toQString(), v[1]->tot_boolean()); break; }
case pcode___actions__METHOD_IsChecked:{ p = new interpreter_parameter( _actions::METHOD_IsChecked(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }

case pcode___actions__METHOD_SetStatusTip:{ _actions::METHOD_SetStatusTip(v[0]->toQString(), v[1]->toQString()); break; }
case pcode___actions__METHOD_StatusTip:{ p = new interpreter_parameter( _actions::METHOD_StatusTip(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }

case pcode___actions__METHOD_SetToolTip:{ _actions::METHOD_SetToolTip(v[0]->toQString(), v[1]->toQString()); break; }
case pcode___actions__METHOD_ToolTip:{ p = new interpreter_parameter( _actions::METHOD_ToolTip(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }

case pcode___actions__METHOD_SetWhatsThis:{ _actions::METHOD_SetWhatsThis(v[0]->toQString(), v[1]->toQString()); break; }
case pcode___actions__METHOD_WhatsThis:{ p = new interpreter_parameter( _actions::METHOD_WhatsThis(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }

case pcode___actions__METHOD_SetIcon:{ _actions::METHOD_SetIcon(v[0]->toQString(), v[1]->toQString()); break; }
case pcode___actions__METHOD_Icon:{ p = new interpreter_parameter( _actions::METHOD_Icon(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }

case pcode___actions__METHOD_SetTag:{ _actions::METHOD_SetTag(v[0]->toQString(), v[1]->toQString()); break; }
case pcode___actions__METHOD_Tag:{ p = new interpreter_parameter( _actions::METHOD_Tag(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }

case pcode___actions__METHOD_SetCaption:{ _actions::METHOD_SetCaption(v[0]->toQString(), v[1]->toQString()); break; }
case pcode___actions__METHOD_Caption:{ p = new interpreter_parameter( _actions::METHOD_Caption(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }

case pcode___actions__METHOD_SetText:{ _actions::METHOD_SetText(v[0]->toQString(), v[1]->toQString()); break; }
case pcode___actions__METHOD_Text:{ p = new interpreter_parameter( _actions::METHOD_Text(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }

case pcode___actions__METHOD_SetSoundOnEvent:{ _actions::METHOD_SetSoundOnEvent(v[0]->toQString(), v[1]->toQString()); break; }
case pcode___actions__METHOD_SoundOnEvent:{ p = new interpreter_parameter( _actions::METHOD_SoundOnEvent(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }

case pcode___actions__METHOD_SetGroup:{ _actions::METHOD_SetGroup(v[0]->toQString(), v[1]->toQString()); break; }
case pcode___actions__METHOD_Group:{ p = new interpreter_parameter( _actions::METHOD_Group(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }

case pcode___actions__METHOD_SetKey:{ _actions::METHOD_SetKey(v[0]->toQString(), v[1]->toQString()); break; }
case pcode___actions__METHOD_Key:{ p = new interpreter_parameter( _actions::METHOD_Key(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
