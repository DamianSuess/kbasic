
case pcode___database__METHOD_Exists:{ p = new interpreter_parameter(_database::METHOD_Exists(v[0]->toQString(), v[1]->toQString(), v[2]->toQString(), v[3]->toQString(), v[4]->toQString(), v[5]->toQString(), v[6]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___database__METHOD_SetCurrentDatabase:{ p = new interpreter_parameter(_database::METHOD_SetCurrentDatabase(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___database__METHOD_CurrentDatabase:{ p = new interpreter_parameter(_database::METHOD_CurrentDatabase()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___database__METHOD_OpenSQLite:{ p = new interpreter_parameter(_database::METHOD_OpenSQLite(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___database__METHOD_Open:{ p = new interpreter_parameter(_database::METHOD_Open(v[0]->toQString(), v[1]->toQString(), v[2]->toQString(), v[3]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___database__METHOD_Open1:{ p = new interpreter_parameter(_database::METHOD_Open(v[0]->toQString(), v[1]->toQString(), v[2]->toQString(), v[3]->toQString(), v[4]->toQString(), v[5]->toQString(), v[6]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___database__METHOD_Close:{ p = new interpreter_parameter(_database::METHOD_Close(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___database__METHOD_IsOpen:{ p = new interpreter_parameter(_database::METHOD_IsOpen(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___database__METHOD_Create:{ p = new interpreter_parameter(_database::METHOD_Create(v[0]->toQString(), v[1]->toQString(), v[2]->toQString(), v[3]->toQString(), v[4]->toQString(), v[5]->toQString(), v[6]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___database__METHOD_TestConnection:{ p = new interpreter_parameter(_database::METHOD_TestConnection(v[0]->toQString(), v[1]->toQString(), v[2]->toQString(), v[3]->toQString(), v[4]->toQString(), v[5]->toQString())); if (bReturn) pushStack(p); else delete p; break; }                                     
case pcode___database__METHOD_Clear:{ p = new interpreter_parameter(_database::METHOD_Clear(v[0]->toQString(), v[1]->toQString(), v[2]->toQString(), v[3]->toQString(), v[4]->toQString(), v[5]->toQString(), v[6]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___database__METHOD_Drop:{ p = new interpreter_parameter(_database::METHOD_Drop(v[0]->toQString(), v[1]->toQString(), v[2]->toQString(), v[3]->toQString(), v[4]->toQString(), v[5]->toQString(), v[6]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___database__METHOD_Copy:{ p = new interpreter_parameter(_database::METHOD_Copy(v[0]->toQString(), v[1]->toQString())); if (bReturn) pushStack(p); else delete p; break; }

case pcode___database__METHOD_LastSQLError:{ p = new interpreter_parameter(_database::METHOD_LastSQLError(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___database__METHOD_LastSQLCommands:{ p = new interpreter_parameter(_database::METHOD_LastSQLCommands(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___database__METHOD_LastSQLCommandFailed:{ p = new interpreter_parameter(_database::METHOD_LastSQLCommandFailed(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }

case pcode___database__METHOD_IsTransactionSupported:{ p = new interpreter_parameter(_database::METHOD_IsTransactionSupported(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___database__METHOD_Transaction:{ p = new interpreter_parameter(_database::METHOD_Transaction(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___database__METHOD_Commit:{ p = new interpreter_parameter(_database::METHOD_Commit(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___database__METHOD_Rollback:{ p = new interpreter_parameter(_database::METHOD_Rollback(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }

case pcode___database__METHOD_Tables:{ p = new interpreter_parameter(_database::METHOD_Tables(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___database__METHOD_Drivers:{ p = new interpreter_parameter(_database::METHOD_Drivers()); if (bReturn) pushStack(p); else delete p; break; }

case pcode___database__METHOD_MySQL:{ p = new interpreter_parameter(_database::METHOD_MySQL()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___database__METHOD_PostgreSQL:{ p = new interpreter_parameter(_database::METHOD_PostgreSQL()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___database__METHOD_SQLite:{ p = new interpreter_parameter(_database::METHOD_SQLite()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___database__METHOD_ODBC:{ p = new interpreter_parameter(_database::METHOD_ODBC()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___database__METHOD_LocalHost:{ p = new interpreter_parameter(_database::METHOD_LocalHost()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___database__METHOD_DefaultPort:{ p = new interpreter_parameter(_database::METHOD_DefaultPort()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___database__METHOD_DefaultOptions:{ p = new interpreter_parameter(_database::METHOD_DefaultOptions()); if (bReturn) pushStack(p); else delete p; break; }

