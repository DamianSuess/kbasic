case pcode___array___array:{ getParam(v, m, n); pp = new kb_array(); myStack->pushParameter(pcode___array, pp); ((kb_array *) pp)->setInterpreter(this); break; }

//case pcode___array__METHOD_Append:{ getParam(v, m, n); identifier = popStack(); kb_array *q = (kb_array *) identifier->to_array(); q->METHOD_Append(v[0]->toQString()); break; }

case pcode___array__GET:
//case pcode___array__METHOD_Get:
  { getParam(v, m, n); identifier = popStack(); kb_array *q = (kb_array *) identifier->to_array(); interpreter_parameter *p = new interpreter_parameter( q->METHOD_Get(v[0]->toQString(), v[1]->toQString(), v[2]->toQString(), v[3]->toQString(), v[4]->toQString(), v[5]->toQString(), v[6]->toQString(), v[7]->toQString())); if (bReturn) pushStack(p); else delete p; break; }

case pcode___array__SET:
//case pcode___array__METHOD_Set:
  { getParam(v, m, n); identifier = popStack(); 
  kb_array *q = (kb_array *) identifier->to_array(); 
  q->METHOD_Set(v[0]->toQString(), v[1]->toQString(), v[2]->toQString(), v[3]->toQString(), v[4]->toQString(), v[5]->toQString(), v[6]->toQString(), v[7]->toQString(), v[8]->tot_variant()); 
  break; }

/*

case pcode___array__METHOD_Len:{ getParam(v, m, n); identifier = popStack(); kb_array *q = (kb_array *) identifier->to_array(); interpreter_parameter *p = new interpreter_parameter( q->METHOD_Len()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___array__METHOD_Remove:{ getParam(v, m, n); identifier = popStack(); kb_array *q = (kb_array *) identifier->to_array(); q->METHOD_Remove(v[0]->toQString()); break; }
case pcode___array__METHOD_RemoveAll:{ getParam(v, m, n); identifier = popStack(); kb_array *q = (kb_array *) identifier->to_array(); q->METHOD_RemoveAll(); break; }


case pcode___array__METHOD_Insert:{ getParam(v, m, n); identifier = popStack(); 
  kb_array *q = (kb_array *) identifier->to_array(); 
  q->METHOD_Insert(v[0]->toQString(), v[1]->toQString()); 
  break; }

case pcode___array__METHOD_Replace:{ getParam(v, m, n); identifier = popStack(); 
  kb_array *q = (kb_array *) identifier->to_array(); 
  q->METHOD_Replace(v[0]->toQString(), v[1]->toQString()); 
  break; }

case pcode___array__FOR:{ getParam(v, m, n); identifier = popStack(); kb_array *q = (kb_array *) identifier->to_array(); interpreter_parameter *p = new interpreter_parameter( q->FOR()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___array__EACH:{ 
  getParam(v, m, n); 
  identifier = popStack(); 
  kb_array *q = (kb_array *) identifier->to_array(); 
  interpreter_parameter *p = new interpreter_parameter( q->EACH()); 
  if (bReturn) pushStack(p); else delete p; break; }

case pcode___array__METHOD_Contains:{ getParam(v, m, n); identifier = popStack(); kb_array *q = (kb_array *) identifier->to_array(); interpreter_parameter *p = new interpreter_parameter( q->METHOD_Contains(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }

case pcode___array__METHOD_Keys:{ getParam(v, m, n); identifier = popStack(); kb_array *q = (kb_array *) identifier->to_array(); interpreter_parameter *p = new interpreter_parameter( q->METHOD_Keys()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___array__METHOD_Values:{ getParam(v, m, n); identifier = popStack(); kb_array *q = (kb_array *) identifier->to_array(); interpreter_parameter *p = new interpreter_parameter( q->METHOD_Values()); if (bReturn) pushStack(p); else delete p; break; }

case pcode___array__METHOD_Key:{ getParam(v, m, n); identifier = popStack(); kb_array *q = (kb_array *) identifier->to_array(); interpreter_parameter *p = new interpreter_parameter( q->METHOD_Key()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___array__METHOD_Value:{ getParam(v, m, n); identifier = popStack(); kb_array *q = (kb_array *) identifier->to_array(); interpreter_parameter *p = new interpreter_parameter( q->METHOD_Value()); if (bReturn) pushStack(p); else delete p; break; }
*/


/*
case pcode___array__METHOD_ReadBinary:{ getParam(v, m, n); identifier = popStack(); kb_array *q = (kb_array *) identifier->to_array(); interpreter_parameter *p = new interpreter_parameter( q->METHOD_ReadBinary()); if (bReturn) pushStack(p); else delete p; break; }
     
case pcode___array__METHOD_WriteBinary:{ getParam(v, m, n); identifier = popStack(); kb_array *q = (kb_array *) identifier->to_array(); q->METHOD_WriteBinary(v[0]->toQString()); break; }              
*/

                                  
                           