case pcode___menubaritem___menubaritem:{ getParam(v, m, n); pp = new kb_menubaritem(v[0]->to_form()); myStack->pushParameter(pcode___menubaritem, pp); ((kb_menubaritem *) pp)->setInterpreter(this); break; }

case pcode___menubaritem__SETPROPERTY_ActionId:{ getParam(v, m, n); identifier = popStack(); kb_menubaritem *q = (kb_menubaritem *) identifier->to_menubaritem(); q->SETPROPERTY_ActionId(v[0]->toQString()); break; }
case pcode___menubaritem__GETPROPERTY_ActionId:{ getParam(v, m, n); identifier = popStack(); kb_menubaritem *q = (kb_menubaritem *) identifier->to_menubaritem(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_ActionId()); if (bReturn) pushStack(p); else delete p; break; }

case pcode___menubaritem__SETPROPERTY_Checkable:{ getParam(v, m, n); identifier = popStack(); kb_menubaritem *q = (kb_menubaritem *) identifier->to_menubaritem(); q->SETPROPERTY_Checkable(v[0]->tot_boolean()); break; }
case pcode___menubaritem__GETPROPERTY_Checkable:{ getParam(v, m, n); identifier = popStack(); kb_menubaritem *q = (kb_menubaritem *) identifier->to_menubaritem(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_Checkable()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___menubaritem__SETPROPERTY_Visible:{ getParam(v, m, n); identifier = popStack(); kb_menubaritem *q = (kb_menubaritem *) identifier->to_menubaritem(); q->SETPROPERTY_Visible(v[0]->tot_boolean()); break; }
case pcode___menubaritem__GETPROPERTY_Visible:{ getParam(v, m, n); identifier = popStack(); kb_menubaritem *q = (kb_menubaritem *) identifier->to_menubaritem(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_Visible()); if (bReturn) pushStack(p); else delete p; break; }

case pcode___menubaritem__SETPROPERTY_MenuBarRole:{ getParam(v, m, n); identifier = popStack(); kb_menubaritem *q = (kb_menubaritem *) identifier->to_menubaritem(); q->SETPROPERTY_MenuBarRole(v[0]->toQString()); break; }
case pcode___menubaritem__GETPROPERTY_MenuBarRole:{ getParam(v, m, n); identifier = popStack(); kb_menubaritem *q = (kb_menubaritem *) identifier->to_menubaritem(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_MenuBarRole()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___menubaritem__SETPROPERTY_Data:{ getParam(v, m, n); identifier = popStack(); kb_menubaritem *q = (kb_menubaritem *) identifier->to_menubaritem(); q->SETPROPERTY_Data(v[0]->toQString()); break; }
case pcode___menubaritem__GETPROPERTY_Data:{ getParam(v, m, n); identifier = popStack(); kb_menubaritem *q = (kb_menubaritem *) identifier->to_menubaritem(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_Data()); if (bReturn) pushStack(p); else delete p; break; }

case pcode___menubaritem__SETPROPERTY_Name:{ getParam(v, m, n); identifier = popStack(); kb_menubaritem *q = (kb_menubaritem *) identifier->to_menubaritem(); q->SETPROPERTY_Name(v[0]->toQString()); break; }
case pcode___menubaritem__GETPROPERTY_Name:{ getParam(v, m, n); identifier = popStack(); kb_menubaritem *q = (kb_menubaritem *) identifier->to_menubaritem(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_Name()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___menubaritem__SETPROPERTY_ControlType:{ getParam(v, m, n); identifier = popStack(); kb_menubaritem *q = (kb_menubaritem *) identifier->to_menubaritem(); q->SETPROPERTY_ControlType(v[0]->toQString()); break; }
case pcode___menubaritem__GETPROPERTY_ControlType:{ getParam(v, m, n); identifier = popStack(); kb_menubaritem *q = (kb_menubaritem *) identifier->to_menubaritem(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_ControlType()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___menubaritem__SETPROPERTY_ParentControl:{ getParam(v, m, n); identifier = popStack(); kb_menubaritem *q = (kb_menubaritem *) identifier->to_menubaritem(); q->SETPROPERTY_ParentControl(v[0]->toQString()); break; }
case pcode___menubaritem__GETPROPERTY_ParentControl:{ getParam(v, m, n); identifier = popStack(); kb_menubaritem *q = (kb_menubaritem *) identifier->to_menubaritem(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_ParentControl()); if (bReturn) pushStack(p); else delete p; break; }

case pcode___menubaritem__SETPROPERTY_Caption:{ getParam(v, m, n); identifier = popStack(); kb_menubaritem *q = (kb_menubaritem *) identifier->to_menubaritem(); q->SETPROPERTY_Caption(v[0]->toQString()); break; }
case pcode___menubaritem__GETPROPERTY_Caption:{ getParam(v, m, n); identifier = popStack(); kb_menubaritem *q = (kb_menubaritem *) identifier->to_menubaritem(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_Caption()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___menubaritem__SETPROPERTY_Text:{ getParam(v, m, n); identifier = popStack(); kb_menubaritem *q = (kb_menubaritem *) identifier->to_menubaritem(); q->SETPROPERTY_Caption(v[0]->toQString()); break; }
case pcode___menubaritem__GETPROPERTY_Text:{ getParam(v, m, n); identifier = popStack(); kb_menubaritem *q = (kb_menubaritem *) identifier->to_menubaritem(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_Caption()); if (bReturn) pushStack(p); else delete p; break; }

case pcode___menubaritem__SETPROPERTY_Separator:{ getParam(v, m, n); identifier = popStack(); kb_menubaritem *q = (kb_menubaritem *) identifier->to_menubaritem(); q->SETPROPERTY_Separator(v[0]->tot_boolean()); break; }
case pcode___menubaritem__GETPROPERTY_Separator:{ getParam(v, m, n); identifier = popStack(); kb_menubaritem *q = (kb_menubaritem *) identifier->to_menubaritem(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_Separator()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___menubaritem__SETPROPERTY_Tag:{ getParam(v, m, n); identifier = popStack(); kb_menubaritem *q = (kb_menubaritem *) identifier->to_menubaritem(); q->SETPROPERTY_Tag(v[0]->toQString()); break; }
case pcode___menubaritem__GETPROPERTY_Tag:{ getParam(v, m, n); identifier = popStack(); kb_menubaritem *q = (kb_menubaritem *) identifier->to_menubaritem(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_Tag()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___menubaritem__SETPROPERTY_Group:{ getParam(v, m, n); identifier = popStack(); kb_menubaritem *q = (kb_menubaritem *) identifier->to_menubaritem(); q->SETPROPERTY_Group(v[0]->toQString()); break; }
case pcode___menubaritem__GETPROPERTY_Group:{ getParam(v, m, n); identifier = popStack(); kb_menubaritem *q = (kb_menubaritem *) identifier->to_menubaritem(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_Group()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___menubaritem__SETPROPERTY_Enabled:{ getParam(v, m, n); identifier = popStack(); kb_menubaritem *q = (kb_menubaritem *) identifier->to_menubaritem(); q->SETPROPERTY_Enabled(v[0]->tot_boolean()); break; }
case pcode___menubaritem__GETPROPERTY_Enabled:{ getParam(v, m, n); identifier = popStack(); kb_menubaritem *q = (kb_menubaritem *) identifier->to_menubaritem(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_Enabled()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___menubaritem__SETPROPERTY_Checked:{ getParam(v, m, n); identifier = popStack(); kb_menubaritem *q = (kb_menubaritem *) identifier->to_menubaritem(); q->SETPROPERTY_Checked(v[0]->tot_boolean()); break; }
case pcode___menubaritem__GETPROPERTY_Checked:{ getParam(v, m, n); identifier = popStack(); kb_menubaritem *q = (kb_menubaritem *) identifier->to_menubaritem(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_Checked()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___menubaritem__SETPROPERTY_Icon:{ getParam(v, m, n); identifier = popStack(); kb_menubaritem *q = (kb_menubaritem *) identifier->to_menubaritem(); q->SETPROPERTY_Icon(v[0]->toQString()); break; }
case pcode___menubaritem__GETPROPERTY_Icon:{ getParam(v, m, n); identifier = popStack(); kb_menubaritem *q = (kb_menubaritem *) identifier->to_menubaritem(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_Icon()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___menubaritem__SETPROPERTY_ParentIndex:{ getParam(v, m, n); identifier = popStack(); kb_menubaritem *q = (kb_menubaritem *) identifier->to_menubaritem(); q->SETPROPERTY_ParentIndex(v[0]->tot_integer()); break; }
case pcode___menubaritem__GETPROPERTY_ParentIndex:{ getParam(v, m, n); identifier = popStack(); kb_menubaritem *q = (kb_menubaritem *) identifier->to_menubaritem(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_ParentIndex()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___menubaritem__SETPROPERTY_Key:{ getParam(v, m, n); identifier = popStack(); kb_menubaritem *q = (kb_menubaritem *) identifier->to_menubaritem(); q->SETPROPERTY_Key(v[0]->toQString()); break; }
case pcode___menubaritem__GETPROPERTY_Key:{ getParam(v, m, n); identifier = popStack(); kb_menubaritem *q = (kb_menubaritem *) identifier->to_menubaritem(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_Key()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___menubaritem__SETPROPERTY_StatusTip:{ getParam(v, m, n); identifier = popStack(); kb_menubaritem *q = (kb_menubaritem *) identifier->to_menubaritem(); q->SETPROPERTY_StatusTip(v[0]->toQString()); break; }
case pcode___menubaritem__GETPROPERTY_StatusTip:{ getParam(v, m, n); identifier = popStack(); kb_menubaritem *q = (kb_menubaritem *) identifier->to_menubaritem(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_StatusTip()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___menubaritem__SETPROPERTY_SoundOnEvent:{ getParam(v, m, n); identifier = popStack(); kb_menubaritem *q = (kb_menubaritem *) identifier->to_menubaritem(); q->SETPROPERTY_SoundOnEvent(v[0]->toQString()); break; }
case pcode___menubaritem__GETPROPERTY_SoundOnEvent:{ getParam(v, m, n); identifier = popStack(); kb_menubaritem *q = (kb_menubaritem *) identifier->to_menubaritem(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_SoundOnEvent()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___menubaritem__EVENT_OnEvent:{ getParam(v, m, n); identifier = popStack(); kb_menubaritem *q = (kb_menubaritem *) identifier->to_menubaritem(); q->EVENT_OnEvent(); break; }