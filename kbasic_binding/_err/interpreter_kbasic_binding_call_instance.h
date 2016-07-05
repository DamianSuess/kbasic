case pcode___err___err:{ 
                 

  getParam(v, m, n); pp = new kb_err(); myStack->pushParameter(pcode___err, pp); ((kb_err *) pp)->setInterpreter(this); 
                       
                                      break; 

                       }
case pcode___err__METHOD_Clear:{ getParam(v, m, n); identifier = popStack(); kb_err *q = (kb_err *) identifier->to_err(); q->METHOD_Clear(); break; }
case pcode___err__METHOD_Raise:{ getParam(v, m, n); identifier = popStack(); kb_err *q = (kb_err *) identifier->to_err(); q->METHOD_Raise(v[0]->toInteger()); break; }
case pcode___err__METHOD_Raise1:{ getParam(v, m, n); identifier = popStack(); kb_err *q = (kb_err *) identifier->to_err(); q->METHOD_Raise(v[0]->toInteger(), v[1]->toQString()); break; }
case pcode___err__METHOD_Raise2:{ getParam(v, m, n); identifier = popStack(); kb_err *q = (kb_err *) identifier->to_err(); q->METHOD_Raise(v[0]->toInteger(), v[1]->toQString(), v[2]->toQString()); break; }
case pcode___err__GETPROPERTY_Number:{ getParam(v, m, n); identifier = popStack(); kb_err *q = (kb_err *) identifier->to_err(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_Number()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___err__GETPROPERTY_Source:{ getParam(v, m, n); identifier = popStack(); kb_err *q = (kb_err *) identifier->to_err(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_Source()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___err__GETPROPERTY_Description:{ getParam(v, m, n); identifier = popStack(); kb_err *q = (kb_err *) identifier->to_err(); interpreter_parameter *p = new interpreter_parameter( q->GETPROPERTY_Description()); if (bReturn) pushStack(p); else delete p; break; }