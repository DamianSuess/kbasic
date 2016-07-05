
case pcode___dir__METHOD_Create:{ p = new interpreter_parameter( _dir::METHOD_Create(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___dir__METHOD_RecursiveCreate:{ p = new interpreter_parameter( _dir::METHOD_RecursiveCreate(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___dir__METHOD_Remove:{ p = new interpreter_parameter( _dir::METHOD_Remove(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___dir__METHOD_RecursiveRemove:{ p = new interpreter_parameter( _dir::METHOD_RecursiveRemove(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___dir__METHOD_FindFile:{ p = new interpreter_parameter( _dir::METHOD_FindFile(v[0]->toQString(), v[1]->toQString(), v[2]->toQString() , v[3]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___dir__METHOD_RecursiveFindFile:{ p = new interpreter_parameter( _dir::METHOD_RecursiveFindFile(v[0]->toQString(), v[1]->toQString(), v[2]->toQString() , v[3]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___dir__METHOD_FindFile1:{ p = new interpreter_parameter( _dir::METHOD_FindFile1(v[0]->toQString(), v[1]->to_strings(), v[2]->toQString() , v[3]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___dir__METHOD_RecursiveFindFile1:{ p = new interpreter_parameter( _dir::METHOD_RecursiveFindFile1(v[0]->toQString(), v[1]->to_strings(), v[2]->toQString() , v[3]->toQString())); if (bReturn) pushStack(p); else delete p; break; }

case pcode___dir__METHOD_FileList:{ p = new interpreter_parameter( _dir::METHOD_FileList(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___dir__METHOD_RecursiveFileList:{ p = new interpreter_parameter( _dir::METHOD_RecursiveFileList(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }

case pcode___dir__METHOD_Copy:{ p = new interpreter_parameter( _dir::METHOD_Copy(v[0]->toQString(), v[1]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___dir__METHOD_Move:{ p = new interpreter_parameter( _dir::METHOD_Move(v[0]->toQString(), v[1]->toQString())); if (bReturn) pushStack(p); else delete p; break; }

case pcode___dir__METHOD_Exists:{ p = new interpreter_parameter( _dir::METHOD_Exists(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___dir__METHOD_ExistsAndIsDir:{ p = new interpreter_parameter( _dir::METHOD_ExistsAndIsDir(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___dir__METHOD_DateTimeCreated:{ p = new interpreter_parameter( _dir::METHOD_DateTimeCreated(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___dir__METHOD_DateTimeUpdated:{ p = new interpreter_parameter( _dir::METHOD_DateTimeUpdated(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___dir__METHOD_DateTimeRead:{ p = new interpreter_parameter( _dir::METHOD_DateTimeRead(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___dir__METHOD_Owner:{ p = new interpreter_parameter( _dir::METHOD_Owner(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___dir__METHOD_Group:{ p = new interpreter_parameter( _dir::METHOD_Group(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }

case pcode___dir__METHOD_IsReadable:{ p = new interpreter_parameter( _dir::METHOD_IsReadable(v[0]->toQString(), v[1]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___dir__METHOD_IsWriteable:{ p = new interpreter_parameter( _dir::METHOD_IsWriteable(v[0]->toQString(), v[1]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___dir__METHOD_IsExecutable:{ p = new interpreter_parameter( _dir::METHOD_IsExecutable(v[0]->toQString(), v[1]->toQString())); if (bReturn) pushStack(p); else delete p; break; }

case pcode___dir__METHOD_IsHidden:{ p = new interpreter_parameter( _dir::METHOD_IsHidden(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___dir__METHOD_TempPath:{ p = new interpreter_parameter( _dir::METHOD_TempPath()); if (bReturn) pushStack(p); else delete p; break; }

case pcode___dir__METHOD_IsDir:{ p = new interpreter_parameter( _dir::METHOD_IsDir(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___dir__METHOD_Drives:{ p = new interpreter_parameter( _dir::METHOD_Drives()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___dir__METHOD_HomePath:{ p = new interpreter_parameter( _dir::METHOD_HomePath()); if (bReturn) pushStack(p); else delete p; break; }

case pcode___dir__METHOD_WithNativeSeparators:{ p = new interpreter_parameter( _dir::METHOD_WithNativeSeparators(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___dir__METHOD_WithoutNativeSeparators:{ p = new interpreter_parameter( _dir::METHOD_WithoutNativeSeparators(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }

case pcode___dir__METHOD_RootPath:{ p = new interpreter_parameter( _dir::METHOD_RootPath()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___dir__METHOD_BundleName:{ p = new interpreter_parameter( _dir::METHOD_BundleName(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___dir__METHOD_SymLinkTarget:{ p = new interpreter_parameter( _dir::METHOD_SymLinkTarget(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___dir__METHOD_Name:{ p = new interpreter_parameter( _dir::METHOD_Name(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___dir__METHOD_Path:{ p = new interpreter_parameter( _dir::METHOD_Path(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___dir__METHOD_Suffix:{ p = new interpreter_parameter( _dir::METHOD_Suffix(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }


case pcode___dir__METHOD_IsRoot:{ p = new interpreter_parameter( _dir::METHOD_IsRoot(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___dir__METHOD_IsRelative:{ p = new interpreter_parameter( _dir::METHOD_IsRelative(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___dir__METHOD_IsSymLink:{ p = new interpreter_parameter( _dir::METHOD_IsSymLink(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___dir__METHOD_IsBundle:{ p = new interpreter_parameter( _dir::METHOD_IsBundle(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }

