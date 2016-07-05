
case pcode___process__METHOD_Run:{ p = new interpreter_parameter(_process::METHOD_Run(v[0]->toQString(), v[1]->tot_boolean())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___process__METHOD_Run1:{ p = new interpreter_parameter(_process::METHOD_Run1(v[0]->toQString(), v[1]->to_strings(), v[2]->tot_boolean())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___process__METHOD_Run2:{ p = new interpreter_parameter(_process::METHOD_Run2(v[0]->toQString(), v[1]->to_strings(), v[2]->to_strings(), v[3]->tot_boolean())); if (bReturn) pushStack(p); else delete p; break; }
