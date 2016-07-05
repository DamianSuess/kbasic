
case pcode___file__METHOD_Size:{ p = new interpreter_parameter( _file::METHOD_Size(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___file__METHOD_Resize:{ p = new interpreter_parameter( _file::METHOD_Resize(v[0]->toQString(), v[1]->tot_long())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___file__METHOD_Truncate:{ p = new interpreter_parameter( _file::METHOD_Truncate(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }

case pcode___file__METHOD_SetReadable:{ p = new interpreter_parameter( _file::METHOD_SetReadable(v[0]->toQString(), v[1]->tot_boolean(), v[2]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___file__METHOD_SetWriteable:{ p = new interpreter_parameter( _file::METHOD_SetWriteable(v[0]->toQString(), v[1]->tot_boolean(), v[2]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___file__METHOD_SetExecutable:{ p = new interpreter_parameter( _file::METHOD_SetExecutable(v[0]->toQString(), v[1]->tot_boolean(), v[2]->toQString())); if (bReturn) pushStack(p); else delete p; break; }

case pcode___file__METHOD_ReadText:{ p = new interpreter_parameter( _file::METHOD_ReadText(v[0]->toQString(), v[1]->toQString(), v[2]->tot_boolean(), v[3]->tot_boolean())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___file__METHOD_WriteText:{ p = new interpreter_parameter( _file::METHOD_WriteText(v[0]->toQString(), v[1]->toQString(), v[2]->tot_boolean(), v[3]->toQString(), v[4]->tot_boolean(), v[5]->tot_boolean())); if (bReturn) pushStack(p); else delete p; break; }


case pcode___file__METHOD_ReadBinary:{ p = new interpreter_parameter( _file::METHOD_ReadBinary(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___file__METHOD_WriteBinary:{ p = new interpreter_parameter( _file::METHOD_WriteBinary(v[0]->toQString(), v[1]->toQString(), v[2]->tot_boolean())); if (bReturn) pushStack(p); else delete p; break; }

case pcode___file__METHOD_Link:{ p = new interpreter_parameter( _file::METHOD_Link(v[0]->toQString(), v[1]->toQString())); if (bReturn) pushStack(p); else delete p; break; }



case pcode___file__METHOD_Create:{ p = new interpreter_parameter( _file::METHOD_Create(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___file__METHOD_Remove:{ p = new interpreter_parameter( _file::METHOD_Remove(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___file__METHOD_Rename:{ p = new interpreter_parameter( _file::METHOD_Rename(v[0]->toQString(), v[1]->toQString(), v[2]->tot_boolean())); if (bReturn) pushStack(p); else delete p; break; }

case pcode___file__METHOD_Copy:{ p = new interpreter_parameter( _file::METHOD_Copy(v[0]->toQString(), v[1]->toQString(), v[2]->tot_boolean())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___file__METHOD_Move:{ p = new interpreter_parameter( _file::METHOD_Move(v[0]->toQString(), v[1]->toQString(), v[2]->tot_boolean())); if (bReturn) pushStack(p); else delete p; break; }

case pcode___file__METHOD_Exists:{ p = new interpreter_parameter( _file::METHOD_Exists(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___file__METHOD_DateTimeCreated:{ p = new interpreter_parameter( _file::METHOD_DateTimeCreated(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___file__METHOD_DateTimeUpdated:{ p = new interpreter_parameter( _file::METHOD_DateTimeUpdated(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___file__METHOD_DateTimeRead:{ p = new interpreter_parameter( _file::METHOD_DateTimeRead(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___file__METHOD_Owner:{ p = new interpreter_parameter( _file::METHOD_Owner(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___file__METHOD_Group:{ p = new interpreter_parameter( _file::METHOD_Group(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }

case pcode___file__METHOD_IsReadable:{ p = new interpreter_parameter( _file::METHOD_IsReadable(v[0]->toQString(), v[1]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___file__METHOD_IsWriteable:{ p = new interpreter_parameter( _file::METHOD_IsWriteable(v[0]->toQString(), v[1]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___file__METHOD_IsExecutable:{ p = new interpreter_parameter( _file::METHOD_IsExecutable(v[0]->toQString(), v[1]->toQString())); if (bReturn) pushStack(p); else delete p; break; }

case pcode___file__METHOD_IsHidden:{ p = new interpreter_parameter( _file::METHOD_IsHidden(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }

case pcode___file__METHOD_IsFile:{ p = new interpreter_parameter( _file::METHOD_IsFile(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }

case pcode___file__METHOD_WithNativeSeparators:{ p = new interpreter_parameter( _file::METHOD_WithNativeSeparators(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___file__METHOD_WithoutNativeSeparators:{ p = new interpreter_parameter( _file::METHOD_WithoutNativeSeparators(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }

case pcode___file__METHOD_SymLinkTarget:{ p = new interpreter_parameter( _file::METHOD_SymLinkTarget(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___file__METHOD_Name:{ p = new interpreter_parameter( _file::METHOD_Name(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___file__METHOD_NameWithoutSuffix:{ p = new interpreter_parameter( _file::METHOD_NameWithoutSuffix(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___file__METHOD_Path:{ p = new interpreter_parameter( _file::METHOD_Path(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___file__METHOD_Suffix:{ p = new interpreter_parameter( _file::METHOD_Suffix(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }


case pcode___file__METHOD_IsRelative:{ p = new interpreter_parameter( _file::METHOD_IsRelative(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___file__METHOD_IsSymLink:{ p = new interpreter_parameter( _file::METHOD_IsSymLink(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }

