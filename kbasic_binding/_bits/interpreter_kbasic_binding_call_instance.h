case pcode___bits___bits:{ getParam(v, m, n); pp = new kb_bits(); myStack->pushParameter(pcode___bits, pp); ((kb_bits *) pp)->setInterpreter(this); break; }

case pcode___bits__METHOD_SetByte:{ getParam(v, m, n); identifier = popStack(); kb_bits *q = (kb_bits *) identifier->to_bits(); q->METHOD_SetByte(v[0]->tot_integer()); break; }              
case pcode___bits__METHOD_SetShort:{ getParam(v, m, n); identifier = popStack(); kb_bits *q = (kb_bits *) identifier->to_bits(); q->METHOD_SetShort(v[0]->tot_integer()); break; }              
case pcode___bits__METHOD_SetInteger:{ getParam(v, m, n); identifier = popStack(); kb_bits *q = (kb_bits *) identifier->to_bits(); q->METHOD_SetInteger(v[0]->tot_integer()); break; }              
case pcode___bits__METHOD_SetLong:{ getParam(v, m, n); identifier = popStack(); kb_bits *q = (kb_bits *) identifier->to_bits(); q->METHOD_SetLong(v[0]->tot_long()); break; }              

case pcode___bits__METHOD_Byte:{ getParam(v, m, n); identifier = popStack(); kb_bits *q = (kb_bits *) identifier->to_bits(); interpreter_parameter *p = new interpreter_parameter( q->METHOD_Byte()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___bits__METHOD_Short:{ getParam(v, m, n); identifier = popStack(); kb_bits *q = (kb_bits *) identifier->to_bits(); interpreter_parameter *p = new interpreter_parameter( q->METHOD_Short()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___bits__METHOD_Integer:{ getParam(v, m, n); identifier = popStack(); kb_bits *q = (kb_bits *) identifier->to_bits(); interpreter_parameter *p = new interpreter_parameter( q->METHOD_Integer()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___bits__METHOD_Long:{ getParam(v, m, n); identifier = popStack(); kb_bits *q = (kb_bits *) identifier->to_bits(); interpreter_parameter *p = new interpreter_parameter( q->METHOD_Long()); if (bReturn) pushStack(p); else delete p; break; }

case pcode___bits__METHOD_SetBit:{ getParam(v, m, n); identifier = popStack(); kb_bits *q = (kb_bits *) identifier->to_bits(); q->METHOD_SetBit(v[0]->tot_integer(), v[1]->tot_boolean()); break; }              
case pcode___bits__METHOD_Bit:{ getParam(v, m, n); identifier = popStack(); kb_bits *q = (kb_bits *) identifier->to_bits(); interpreter_parameter *p = new interpreter_parameter( q->METHOD_Bit(v[0]->tot_integer())); if (bReturn) pushStack(p); else delete p; break; }

case pcode___bits__METHOD_TestBit:{ getParam(v, m, n); identifier = popStack(); kb_bits *q = (kb_bits *) identifier->to_bits(); interpreter_parameter *p = new interpreter_parameter( q->METHOD_Bit(v[0]->tot_integer())); if (bReturn) pushStack(p); else delete p; break; }

case pcode___bits__METHOD_ToogleBit:{ getParam(v, m, n); identifier = popStack(); kb_bits *q = (kb_bits *) identifier->to_bits(); q->METHOD_ToogleBit(v[0]->tot_integer()); break; }              
         