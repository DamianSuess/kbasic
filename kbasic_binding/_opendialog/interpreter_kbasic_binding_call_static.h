
case pcode___opendialog__METHOD_GetFile:{ p = new interpreter_parameter(_opendialog::METHOD_GetFile()); if (bReturn) pushStack(p); else delete p; break; }

case pcode___opendialog__METHOD_GetFile1:{ p = new interpreter_parameter(_opendialog::METHOD_GetFile(v[0]->toQString(), v[1]->toQString(), v[2]->toQString()));if (bReturn) pushStack(p); else delete p; break; }

case pcode___opendialog__METHOD_GetFiles:{ p = new interpreter_parameter(_opendialog::METHOD_GetFiles()); if (bReturn) pushStack(p); else delete p; break; }

case pcode___opendialog__METHOD_GetFiles1:{ p = new interpreter_parameter(_opendialog::METHOD_GetFiles(v[0]->toQString(), v[1]->toQString(), v[2]->toQString()));if (bReturn) pushStack(p); else delete p; break; }

case pcode___opendialog__METHOD_GetDirectory:{ p = new interpreter_parameter(_opendialog::METHOD_GetDirectory()); if (bReturn) pushStack(p); else delete p; break; }

case pcode___opendialog__METHOD_GetDirectory1:{ p = new interpreter_parameter(_opendialog::METHOD_GetDirectory(v[0]->toQString(), v[1]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
/*
case pcode___opendialog__METHOD_SetMode:{ opendialog::METHOD_SetMode(v[0]->toQString()); break; }

case pcode___opendialog__METHOD_SetOption:{ opendialog::METHOD_SetOption(v[0]->toQString()); break; }
*/