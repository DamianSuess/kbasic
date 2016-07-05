//case pcode___stringsstrings___stringsstrings:{ getParam(v, m, n); pp = 0; myStack->pushParameter(pcode___stringsstrings, pp); break; }
case pcode___stringsstrings___stringsstrings:{ getParam(v, m, n); pp = new kb_stringsstrings(); myStack->pushParameter(pcode___stringsstrings, pp); ((kb_stringsstrings *) pp)->setInterpreter(this); break; }
                                             
case pcode___stringsstrings__METHOD_Len:{ getParam(v, m, n); identifier = popStack(); kb_stringsstrings *q = (kb_stringsstrings *) identifier->to_stringsstrings(); interpreter_parameter *p = new interpreter_parameter( q->METHOD_Len()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___stringsstrings__METHOD_Append:{ getParam(v, m, n); identifier = popStack(); kb_stringsstrings *q = (kb_stringsstrings *) identifier->to_stringsstrings(); q->METHOD_Append(v[0]->toQString(), v[1]->toQString()); break; }
case pcode___stringsstrings__METHOD_Remove:{ getParam(v, m, n); identifier = popStack(); kb_stringsstrings *q = (kb_stringsstrings *) identifier->to_stringsstrings(); q->METHOD_Remove(v[0]->toQString()); break; }
case pcode___stringsstrings__METHOD_RemoveAll:{ getParam(v, m, n); identifier = popStack(); kb_stringsstrings *q = (kb_stringsstrings *) identifier->to_stringsstrings(); q->METHOD_RemoveAll(); break; }

case pcode___stringsstrings__GET:
case pcode___stringsstrings__METHOD_Get:{ getParam(v, m, n); identifier = popStack(); kb_stringsstrings *q = (kb_stringsstrings *) identifier->to_stringsstrings(); interpreter_parameter *p = new interpreter_parameter( q->METHOD_Get(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___stringsstrings__SET:
case pcode___stringsstrings__METHOD_Set:{ getParam(v, m, n); identifier = popStack(); 
  kb_stringsstrings *q = (kb_stringsstrings *) identifier->to_stringsstrings(); 
  q->METHOD_Set(v[0]->toQString(), v[1]->toQString()); 
  break; }

case pcode___stringsstrings__METHOD_Insert:{ getParam(v, m, n); identifier = popStack(); 
  kb_stringsstrings *q = (kb_stringsstrings *) identifier->to_stringsstrings(); 
  q->METHOD_Insert(v[0]->toQString(), v[1]->toQString()); 
  break; }

case pcode___stringsstrings__METHOD_Replace:{ getParam(v, m, n); identifier = popStack(); 
  kb_stringsstrings *q = (kb_stringsstrings *) identifier->to_stringsstrings(); 
  q->METHOD_Replace(v[0]->toQString(), v[1]->toQString()); 
  break; }

case pcode___stringsstrings__FOR:{ getParam(v, m, n); identifier = popStack(); kb_stringsstrings *q = (kb_stringsstrings *) identifier->to_stringsstrings(); interpreter_parameter *p = new interpreter_parameter( q->FOR()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___stringsstrings__EACH:{ 
  getParam(v, m, n); 
  identifier = popStack(); 
  kb_stringsstrings *q = (kb_stringsstrings *) identifier->to_stringsstrings(); 
  interpreter_parameter *p = new interpreter_parameter( q->EACH()); 
  if (bReturn) pushStack(p); else delete p; break; }

case pcode___stringsstrings__METHOD_Contains:{ getParam(v, m, n); identifier = popStack(); kb_stringsstrings *q = (kb_stringsstrings *) identifier->to_stringsstrings(); interpreter_parameter *p = new interpreter_parameter( q->METHOD_Contains(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }


case pcode___stringsstrings__METHOD_Keys:{ getParam(v, m, n); identifier = popStack(); kb_stringsstrings *q = (kb_stringsstrings *) identifier->to_stringsstrings(); interpreter_parameter *p = new interpreter_parameter( q->METHOD_Keys()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___stringsstrings__METHOD_Values:{ getParam(v, m, n); identifier = popStack(); kb_stringsstrings *q = (kb_stringsstrings *) identifier->to_stringsstrings(); interpreter_parameter *p = new interpreter_parameter( q->METHOD_Values()); if (bReturn) pushStack(p); else delete p; break; }

case pcode___stringsstrings__METHOD_Key:{ getParam(v, m, n); identifier = popStack(); kb_stringsstrings *q = (kb_stringsstrings *) identifier->to_stringsstrings(); interpreter_parameter *p = new interpreter_parameter( q->METHOD_Key()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___stringsstrings__METHOD_Value:{ getParam(v, m, n); identifier = popStack(); kb_stringsstrings *q = (kb_stringsstrings *) identifier->to_stringsstrings(); interpreter_parameter *p = new interpreter_parameter( q->METHOD_Value()); if (bReturn) pushStack(p); else delete p; break; }

/*
case pcode___stringsstrings__METHOD_ReadBinary:{ getParam(v, m, n); identifier = popStack(); kb_stringsstrings *q = (kb_stringsstrings *) identifier->to_stringsstrings(); interpreter_parameter *p = new interpreter_parameter( q->METHOD_ReadBinary()); if (bReturn) pushStack(p); else delete p; break; }
     
case pcode___stringsstrings__METHOD_WriteBinary:{ getParam(v, m, n); identifier = popStack(); kb_stringsstrings *q = (kb_stringsstrings *) identifier->to_stringsstrings(); q->METHOD_WriteBinary(v[0]->toQString()); break; }              
*/


                                  
                           