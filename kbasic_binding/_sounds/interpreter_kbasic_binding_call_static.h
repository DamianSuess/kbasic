case pcode___sounds__METHOD_Load:    { interpreter_parameter *p = new interpreter_parameter( _sounds2::METHOD_SetSound(v[0]->toConstQString(), v[1]->toConstQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___sounds__METHOD_SetSound:{ interpreter_parameter *p = new interpreter_parameter( _sounds2::METHOD_SetSound(v[0]->toConstQString(), v[1]->toConstQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___sounds__METHOD_Play:{  _sounds2::METHOD_Play(v[0]->toConstQString()); break; }

