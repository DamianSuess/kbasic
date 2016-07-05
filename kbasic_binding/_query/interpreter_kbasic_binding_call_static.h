
case pcode___query__METHOD_Run:{ p = new interpreter_parameter(_query::METHOD_Run(v[0]->toQString(), v[1]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___query__METHOD_Run1:{ p = new interpreter_parameter(_query::METHOD_Run1(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
   