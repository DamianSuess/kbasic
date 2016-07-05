

case pcode___toolbaritem__SETPROPERTY_ActionId:{ getParam(v, m, n); identifier = popStack(); kb_toolbaritem *q = (kb_toolbaritem *) identifier->to_toolbaritem(); q->SETPROPERTY_ActionId(v[0]->toQString()); break; }
case pcode___toolbaritem__GETPROPERTY_ActionId:{ getParam(v, m, n); identifier = popStack(); kb_toolbaritem *q = (kb_toolbaritem *) identifier->to_toolbaritem(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_ActionId()); if (bReturn) pushStack(p); else delete p; break; }

case pcode___toolbaritem__SETPROPERTY_Visible:{ getParam(v, m, n); identifier = popStack(); kb_toolbaritem *q = (kb_toolbaritem *) identifier->to_toolbaritem(); q->SETPROPERTY_Visible(v[0]->tot_boolean()); break; }
case pcode___toolbaritem__GETPROPERTY_Visible:{ getParam(v, m, n); identifier = popStack(); kb_toolbaritem *q = (kb_toolbaritem *) identifier->to_toolbaritem(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_Visible()); if (bReturn) pushStack(p); else delete p; break; }

case pcode___toolbaritem__SETPROPERTY_Checkable:{ getParam(v, m, n); identifier = popStack(); kb_toolbaritem *q = (kb_toolbaritem *) identifier->to_toolbaritem(); q->SETPROPERTY_Checkable(v[0]->tot_boolean()); break; }
case pcode___toolbaritem__GETPROPERTY_Checkable:{ getParam(v, m, n); identifier = popStack(); kb_toolbaritem *q = (kb_toolbaritem *) identifier->to_toolbaritem(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_Checkable()); if (bReturn) pushStack(p); else delete p; break; }

case pcode___toolbaritem__SETPROPERTY_Checked:{ getParam(v, m, n); identifier = popStack(); kb_toolbaritem *q = (kb_toolbaritem *) identifier->to_toolbaritem(); q->SETPROPERTY_Checked(v[0]->tot_boolean()); break; }
case pcode___toolbaritem__GETPROPERTY_Checked:{ getParam(v, m, n); identifier = popStack(); kb_toolbaritem *q = (kb_toolbaritem *) identifier->to_toolbaritem(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_Checked()); if (bReturn) pushStack(p); else delete p; break; }

case pcode___toolbaritem__SETPROPERTY_ContextMenu:{ getParam(v, m, n); identifier = popStack(); kb_toolbaritem *q = (kb_toolbaritem *) identifier->to_toolbaritem(); q->SETPROPERTY_ContextMenu(v[0]->toQString()); break; }
case pcode___toolbaritem__GETPROPERTY_ContextMenu:{ getParam(v, m, n); identifier = popStack(); kb_toolbaritem *q = (kb_toolbaritem *) identifier->to_toolbaritem(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_ContextMenu()); if (bReturn) pushStack(p); else delete p; break; }


case pcode___toolbaritem__SETPROPERTY_StringValue:{ getParam(v, m, n); identifier = popStack(); kb_toolbaritem *q = (kb_toolbaritem *) identifier->to_toolbaritem(); q->SETPROPERTY_StringValue(v[0]->toQString()); break; }
case pcode___toolbaritem__GETPROPERTY_StringValue:{ getParam(v, m, n); identifier = popStack(); kb_toolbaritem *q = (kb_toolbaritem *) identifier->to_toolbaritem(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_StringValue()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___toolbaritem__GETPROPERTY_OldStringValue:{ getParam(v, m, n); identifier = popStack(); kb_toolbaritem *q = (kb_toolbaritem *) identifier->to_toolbaritem(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_OldStringValue()); if (bReturn) pushStack(p); else delete p; break; }

case pcode___toolbaritem__SETPROPERTY_Caption:{ getParam(v, m, n); identifier = popStack(); kb_toolbaritem *q = (kb_toolbaritem *) identifier->to_toolbaritem(); q->SETPROPERTY_Caption(v[0]->toQString()); break; }
case pcode___toolbaritem__GETPROPERTY_Caption:{ getParam(v, m, n); identifier = popStack(); kb_toolbaritem *q = (kb_toolbaritem *) identifier->to_toolbaritem(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_Caption()); if (bReturn) pushStack(p); else delete p; break; }

case pcode___toolbaritem__SETPROPERTY_Text:{ getParam(v, m, n); identifier = popStack(); kb_toolbaritem *q = (kb_toolbaritem *) identifier->to_toolbaritem(); q->SETPROPERTY_Caption(v[0]->toQString()); break; }
case pcode___toolbaritem__GETPROPERTY_Text:{ getParam(v, m, n); identifier = popStack(); kb_toolbaritem *q = (kb_toolbaritem *) identifier->to_toolbaritem(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_Caption()); if (bReturn) pushStack(p); else delete p; break; }

case pcode___toolbaritem__SETPROPERTY_ArrowType:{ getParam(v, m, n); identifier = popStack(); kb_toolbaritem *q = (kb_toolbaritem *) identifier->to_toolbaritem(); q->SETPROPERTY_ArrowType(v[0]->toQString()); break; }
case pcode___toolbaritem__GETPROPERTY_ArrowType:{ getParam(v, m, n); identifier = popStack(); kb_toolbaritem *q = (kb_toolbaritem *) identifier->to_toolbaritem(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_ArrowType()); if (bReturn) pushStack(p); else delete p; break; }

case pcode___toolbaritem__SETPROPERTY_PopupMode:{ getParam(v, m, n); identifier = popStack(); kb_toolbaritem *q = (kb_toolbaritem *) identifier->to_toolbaritem(); q->SETPROPERTY_PopupMode(v[0]->toQString()); break; }
case pcode___toolbaritem__GETPROPERTY_PopupMode:{ getParam(v, m, n); identifier = popStack(); kb_toolbaritem *q = (kb_toolbaritem *) identifier->to_toolbaritem(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_PopupMode()); if (bReturn) pushStack(p); else delete p; break; }

case pcode___toolbaritem__SETPROPERTY_ToolBarRole:{ getParam(v, m, n); identifier = popStack(); kb_toolbaritem *q = (kb_toolbaritem *) identifier->to_toolbaritem(); q->SETPROPERTY_ToolBarRole(v[0]->toQString()); break; }
case pcode___toolbaritem__GETPROPERTY_ToolBarRole:{ getParam(v, m, n); identifier = popStack(); kb_toolbaritem *q = (kb_toolbaritem *) identifier->to_toolbaritem(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_ToolBarRole()); if (bReturn) pushStack(p); else delete p; break; }


case pcode___toolbaritem__SETPROPERTY_Name:{ getParam(v, m, n); identifier = popStack(); kb_toolbaritem *q = (kb_toolbaritem *) identifier->to_toolbaritem(); q->SETPROPERTY_Name(v[0]->toQString()); break; }
case pcode___toolbaritem__GETPROPERTY_Name:{ getParam(v, m, n); identifier = popStack(); kb_toolbaritem *q = (kb_toolbaritem *) identifier->to_toolbaritem(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_Name()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___toolbaritem__SETPROPERTY_ControlType:{ getParam(v, m, n); identifier = popStack(); kb_toolbaritem *q = (kb_toolbaritem *) identifier->to_toolbaritem(); q->SETPROPERTY_ControlType(v[0]->toQString()); break; }
case pcode___toolbaritem__GETPROPERTY_ControlType:{ getParam(v, m, n); identifier = popStack(); kb_toolbaritem *q = (kb_toolbaritem *) identifier->to_toolbaritem(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_ControlType()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___toolbaritem__SETPROPERTY_Tag:{ getParam(v, m, n); identifier = popStack(); kb_toolbaritem *q = (kb_toolbaritem *) identifier->to_toolbaritem(); q->SETPROPERTY_Tag(v[0]->toQString()); break; }
case pcode___toolbaritem__GETPROPERTY_Tag:{ getParam(v, m, n); identifier = popStack(); kb_toolbaritem *q = (kb_toolbaritem *) identifier->to_toolbaritem(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_Tag()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___toolbaritem__SETPROPERTY_Separator:{ getParam(v, m, n); identifier = popStack(); kb_toolbaritem *q = (kb_toolbaritem *) identifier->to_toolbaritem(); q->SETPROPERTY_Separator(v[0]->tot_boolean()); break; }
case pcode___toolbaritem__GETPROPERTY_Separator:{ getParam(v, m, n); identifier = popStack(); kb_toolbaritem *q = (kb_toolbaritem *) identifier->to_toolbaritem(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_Separator()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___toolbaritem__SETPROPERTY_Enabled:{ getParam(v, m, n); identifier = popStack(); kb_toolbaritem *q = (kb_toolbaritem *) identifier->to_toolbaritem(); q->SETPROPERTY_Enabled(v[0]->tot_boolean()); break; }
case pcode___toolbaritem__GETPROPERTY_Enabled:{ getParam(v, m, n); identifier = popStack(); kb_toolbaritem *q = (kb_toolbaritem *) identifier->to_toolbaritem(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_Enabled()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___toolbaritem__SETPROPERTY_Icon:{ getParam(v, m, n); identifier = popStack(); kb_toolbaritem *q = (kb_toolbaritem *) identifier->to_toolbaritem(); q->SETPROPERTY_Icon(v[0]->toQString()); break; }
case pcode___toolbaritem__GETPROPERTY_Icon:{ getParam(v, m, n); identifier = popStack(); kb_toolbaritem *q = (kb_toolbaritem *) identifier->to_toolbaritem(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_Icon()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___toolbaritem__SETPROPERTY_ToolTip:{ getParam(v, m, n); identifier = popStack(); kb_toolbaritem *q = (kb_toolbaritem *) identifier->to_toolbaritem(); q->SETPROPERTY_ToolTip(v[0]->toQString()); break; }
case pcode___toolbaritem__GETPROPERTY_ToolTip:{ getParam(v, m, n); identifier = popStack(); kb_toolbaritem *q = (kb_toolbaritem *) identifier->to_toolbaritem(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_ToolTip()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___toolbaritem__SETPROPERTY_StatusTip:{ getParam(v, m, n); identifier = popStack(); kb_toolbaritem *q = (kb_toolbaritem *) identifier->to_toolbaritem(); q->SETPROPERTY_StatusTip(v[0]->toQString()); break; }
case pcode___toolbaritem__GETPROPERTY_StatusTip:{ getParam(v, m, n); identifier = popStack(); kb_toolbaritem *q = (kb_toolbaritem *) identifier->to_toolbaritem(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_StatusTip()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___toolbaritem__SETPROPERTY_WhatsThis:{ getParam(v, m, n); identifier = popStack(); kb_toolbaritem *q = (kb_toolbaritem *) identifier->to_toolbaritem(); q->SETPROPERTY_WhatsThis(v[0]->toQString()); break; }
case pcode___toolbaritem__GETPROPERTY_WhatsThis:{ getParam(v, m, n); identifier = popStack(); kb_toolbaritem *q = (kb_toolbaritem *) identifier->to_toolbaritem(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_WhatsThis()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___toolbaritem__SETPROPERTY_ParentIndex:{ getParam(v, m, n); identifier = popStack(); kb_toolbaritem *q = (kb_toolbaritem *) identifier->to_toolbaritem(); q->SETPROPERTY_ParentIndex(v[0]->tot_integer()); break; }
case pcode___toolbaritem__GETPROPERTY_ParentIndex:{ getParam(v, m, n); identifier = popStack(); kb_toolbaritem *q = (kb_toolbaritem *) identifier->to_toolbaritem(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_ParentIndex()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___toolbaritem__SETPROPERTY_SoundOnEvent:{ getParam(v, m, n); identifier = popStack(); kb_toolbaritem *q = (kb_toolbaritem *) identifier->to_toolbaritem(); q->SETPROPERTY_SoundOnEvent(v[0]->toQString()); break; }
case pcode___toolbaritem__GETPROPERTY_SoundOnEvent:{ getParam(v, m, n); identifier = popStack(); kb_toolbaritem *q = (kb_toolbaritem *) identifier->to_toolbaritem(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_SoundOnEvent()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___toolbaritem__EVENT_OnEvent:{ getParam(v, m, n); identifier = popStack(); kb_toolbaritem *q = (kb_toolbaritem *) identifier->to_toolbaritem(); q->EVENT_OnEvent(); break; }