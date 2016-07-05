
case pcode___savedialog__METHOD_GetFile:{ p = new interpreter_parameter(_savedialog::METHOD_GetFile()); if (bReturn) pushStack(p); else delete p; break; }

case pcode___savedialog__METHOD_GetFile1:{ p = new interpreter_parameter(_savedialog::METHOD_GetFile(v[0]->toQString(), v[1]->toQString(), v[2]->toQString()));if (bReturn) pushStack(p); else delete p; break; }

case pcode___savedialog__METHOD_GetDirectory:{ p = new interpreter_parameter(_savedialog::METHOD_GetDirectory()); if (bReturn) pushStack(p); else delete p; break; }

case pcode___savedialog__METHOD_GetDirectory1:{ p = new interpreter_parameter(_savedialog::METHOD_GetDirectory(v[0]->toQString(), v[1]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
/*
case pcode___savedialog__METHOD_SetMode:{ savedialog::METHOD_SetMode(v[0]->toQString()); break; }

case pcode___savedialog__METHOD_SetOption:{ savedialog::METHOD_SetOption(v[0]->toQString()); break; }
*/