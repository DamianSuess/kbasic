case pcode___strings___strings:{ getParam(v, m, n); pp = new kb_strings(); myStack->pushParameter(pcode___strings, pp); ((kb_strings *) pp)->setInterpreter(this); break; }
case pcode___strings__METHOD_Len:{ getParam(v, m, n); identifier = popStack(); kb_strings *q = (kb_strings *) identifier->to_strings(); interpreter_parameter *p = new interpreter_parameter( q->METHOD_Len()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___strings__METHOD_Append:{ getParam(v, m, n); identifier = popStack(); kb_strings *q = (kb_strings *) identifier->to_strings(); q->METHOD_Append(v[0]->toQString()); break; }
case pcode___strings__METHOD_Prepend:{ getParam(v, m, n); identifier = popStack(); kb_strings *q = (kb_strings *) identifier->to_strings(); q->METHOD_Prepend(v[0]->toQString()); break; }
case pcode___strings__METHOD_Remove:{ getParam(v, m, n); identifier = popStack(); kb_strings *q = (kb_strings *) identifier->to_strings(); q->METHOD_Remove(v[0]->tot_integer()); break; }
case pcode___strings__METHOD_RemoveAll:{ getParam(v, m, n); identifier = popStack(); kb_strings *q = (kb_strings *) identifier->to_strings(); q->METHOD_RemoveAll(); break; }
case pcode___strings__METHOD_Sort:{ getParam(v, m, n); identifier = popStack(); kb_strings *q = (kb_strings *) identifier->to_strings(); q->METHOD_Sort(); break; }

case pcode___strings__GET:
case pcode___strings__METHOD_Get:{ getParam(v, m, n); identifier = popStack(); kb_strings *q = (kb_strings *) identifier->to_strings(); interpreter_parameter *p = new interpreter_parameter( q->METHOD_Get(v[0]->tot_integer())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___strings__SET:
case pcode___strings__METHOD_Set:{ getParam(v, m, n); identifier = popStack(); 
  kb_strings *q = (kb_strings *) identifier->to_strings(); 
  q->METHOD_Set(v[0]->tot_integer(), v[1]->toQString()); 
  break; }

case pcode___strings__METHOD_Insert:{ getParam(v, m, n); identifier = popStack(); 
  kb_strings *q = (kb_strings *) identifier->to_strings(); 
  q->METHOD_Insert(v[0]->tot_integer(), v[1]->toQString()); 
  break; }

case pcode___strings__METHOD_Replace:{ getParam(v, m, n); identifier = popStack(); 
  kb_strings *q = (kb_strings *) identifier->to_strings(); 
  q->METHOD_Replace(v[0]->tot_integer(), v[1]->toQString()); 
  break; }

case pcode___strings__FOR:{ 
  getParam(v, m, n); identifier = popStack(); 
  kb_strings *q = (kb_strings *) identifier->to_strings(); 
  bool bBreak = false;
  t_qstring s = q->FOR(&bBreak);
  myStack->pushBoolean(!bBreak);

  interpreter_parameter *p = new interpreter_parameter(s); 
  pushStack(p);
  //if (bReturn) pushStack(p); else delete p;
  break; 
  }

case pcode___strings__EACH:{ 
  getParam(v, m, n); 
  identifier = popStack(); 
  kb_strings *q = (kb_strings *) identifier->to_strings(); 
  bool bBreak = false;
  t_qstring s = q->EACH(&bBreak);

  myStack->pushBoolean(!bBreak);
  interpreter_parameter *p = new interpreter_parameter(s); 
  pushStack(p);
  //if (bReturn) pushStack(p); else delete p; 
  break; }

case pcode___strings__METHOD_Join:{ getParam(v, m, n); identifier = popStack(); 
  kb_strings *q = (kb_strings *) identifier->to_strings(); 
  interpreter_parameter *p = new interpreter_parameter( q->METHOD_Join(v[0]->toQString())); 
  if (bReturn) pushStack(p); else delete p; break; }

case pcode___strings__METHOD_Contains:{ getParam(v, m, n); identifier = popStack(); kb_strings *q = (kb_strings *) identifier->to_strings(); interpreter_parameter *p = new interpreter_parameter( q->METHOD_Contains(v[0]->toQString(), v[1]->tot_boolean())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___strings__METHOD_ReadBinary:{ getParam(v, m, n); identifier = popStack(); kb_strings *q = (kb_strings *) identifier->to_strings(); interpreter_parameter *p = new interpreter_parameter( q->METHOD_ReadBinary()); if (bReturn) pushStack(p); else delete p; break; }
     
case pcode___strings__METHOD_WriteBinary:{ getParam(v, m, n); identifier = popStack(); kb_strings *q = (kb_strings *) identifier->to_strings(); q->METHOD_WriteBinary(v[0]->toQString()); break; }              

case pcode___strings__METHOD_IndexOf:{ getParam(v, m, n); identifier = popStack(); kb_strings *q = (kb_strings *) identifier->to_strings(); interpreter_parameter *p = new interpreter_parameter( q->METHOD_IndexOf(v[0]->toQString(), v[1]->tot_integer())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___strings__METHOD_LastIndexOf:{ getParam(v, m, n); identifier = popStack(); kb_strings *q = (kb_strings *) identifier->to_strings(); interpreter_parameter *p = new interpreter_parameter( q->METHOD_LastIndexOf(v[0]->toQString(), v[1]->tot_integer())); if (bReturn) pushStack(p); else delete p; break; }



                                  
                           