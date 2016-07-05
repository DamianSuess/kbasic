//case pcode___pixmaps__METHOD_Pixmap:{ interpreter_parameter *p = new interpreter_parameter( _pixmaps::METHOD_Pixmap(v[0]->toConstQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___pixmaps__METHOD_Load:{ interpreter_parameter *p = new interpreter_parameter( _pixmaps::METHOD_SetPixmap(v[0]->toConstQString(), v[1]->toConstQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___pixmaps__METHOD_SetPixmap:{ interpreter_parameter *p = new interpreter_parameter( _pixmaps::METHOD_SetPixmap(v[0]->toConstQString(), v[1]->toConstQString())); if (bReturn) pushStack(p); else delete p; break; }

