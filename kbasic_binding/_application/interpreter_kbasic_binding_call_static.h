case pcode___application__PROPERTYSET_X:{ _application::SETPROPERTY_X(v[0]->toInteger()); break; }

case pcode___application__PROPERTYGET_X:{ i = _application::GETPROPERTY_X(); if (bReturn) pushStackInteger(i); break; }

case pcode___application__PROPERTYSET_Y:{ _application::SETPROPERTY_Y(v[0]->toInteger()); break; }

case pcode___application__PROPERTYGET_Y:{ i = _application::GETPROPERTY_Y(); if (bReturn) pushStackInteger(i); break; }

case pcode___application__PROPERTYSET_Width:{ _application::SETPROPERTY_Width(v[0]->toInteger()); break; }

case pcode___application__PROPERTYGET_Width:{ i =  _application::GETPROPERTY_Width(); if (bReturn) pushStackInteger(i); break; }

case pcode___application__PROPERTYSET_Height:{ _application::SETPROPERTY_Height(v[0]->toInteger()); break; }

case pcode___application__PROPERTYGET_Height:{ i =  _application::GETPROPERTY_Height(); if (bReturn) pushStackInteger(i);  break; }


                                             
case pcode___application__METHOD_PlaySound:{ _application::METHOD_PlaySound(v[0]->toQString()); break; }
case pcode___application__METHOD_PlayMovie:{ _application::METHOD_PlayMovie(v[0]->toQString(), v[1]->tot_boolean()); break; }

case pcode___application__METHOD_AvailableLanguages:{ p = new interpreter_parameter( _application::METHOD_AvailableLanguages()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___application__METHOD_SetLanguage:{ _application::METHOD_SetLanguage(v[0]->toQString()); break; }
case pcode___application__METHOD_SetCountry:{ _application::METHOD_SetCountry(v[0]->toQString()); break; }

case pcode___application__METHOD_SetViewMode:{ _application::METHOD_SetViewMode(v[0]->toQString()); break; }
case pcode___application__METHOD_ViewMode:{ p = new interpreter_parameter( _application::METHOD_ViewMode()); if (bReturn) pushStack(p); else delete p; break; }
                     

case pcode___application__METHOD_IsMimeTypeAvailable:{ p = new interpreter_parameter( _application::METHOD_IsMimeTypeAvailable(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___application__METHOD_AvailableMimeTypes:{ p = new interpreter_parameter( _application::METHOD_AvailableMimeTypes()); if (bReturn) pushStack(p); else delete p; break; }

case pcode___application__METHOD_LoadProjectFileAsString:{ p = new interpreter_parameter( _application::METHOD_LoadProjectFileAsString(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___application__METHOD_LoadProjectFileAsBinary:{ p = new interpreter_parameter( _application::METHOD_LoadProjectFileAsBinary(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }

case pcode___application__METHOD_LoadFileAsString:{ p = new interpreter_parameter( _application::METHOD_LoadFileAsString(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
case pcode___application__METHOD_LoadURLAsBinary:{ p = new interpreter_parameter( _application::METHOD_LoadURLAsBinary(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }
                                                  

case pcode___application__METHOD_Move:{ _application::METHOD_Move(v[0]->tot_integer(), v[1]->tot_integer()); break; }

case pcode___application__METHOD_Resize:{ _application::METHOD_Resize(v[0]->tot_integer(), v[1]->tot_integer()); break; }

case pcode___application__METHOD_Close:{ _application::METHOD_Close(); break; }

case pcode___application__METHOD_QtVersion:{ p = new interpreter_parameter( _application::METHOD_QtVersion()); if (bReturn) pushStack(p); else delete p; break; }

case pcode___application__METHOD_OperatingSystemName:{ p = new interpreter_parameter( _application::METHOD_OperatingSystemName()); if (bReturn) pushStack(p); else delete p; break; }

case pcode___application__METHOD_SetDefaultIcon:{ _application::METHOD_SetDefaultIcon(v[0]->toQString()); break; }

case pcode___application__METHOD_ExternalOpenFile:{ _application::METHOD_ExternalOpenFile(v[0]->toQString()); break; }

case pcode___application__METHOD_CloseAllWindows:{ _application::METHOD_CloseAllWindows(); break; }

case pcode___application__METHOD_IsLayoutDirection:{ b = _application::METHOD_IsLayoutDirection(); if (bReturn) pushStackBoolean(b); break; }

case pcode___application__METHOD_CurrentForm:{ p = new interpreter_parameter( _application::METHOD_CurrentForm()); if (bReturn) pushStack(p); else delete p; break; }

case pcode___application__METHOD_FocusControl:{ p = new interpreter_parameter( _application::METHOD_FocusControl()); if (bReturn) pushStack(p); else delete p; break; }

case pcode___application__METHOD_SetStyle:{ _application::METHOD_SetStyle(v[0]->toQString()); break; }


case pcode___application__METHOD_ShowFullScreen:{ _application::METHOD_ShowFullScreen(); break; }

case pcode___application__METHOD_ShowMaximized:{ _application::METHOD_ShowMaximized(); break; }

case pcode___application__METHOD_ShowMinimized:{ _application::METHOD_ShowMinimized(); break; }

case pcode___application__METHOD_ShowNormal:{ _application::METHOD_ShowNormal(); break; }

case pcode___application__METHOD_MsgBox:{ _application::METHOD_MsgBox(v[0]->toQString(), v[1]->toQString()); break; }

case pcode___application__METHOD_SetCaption:{ _application::METHOD_SetCaption(v[0]->toQString()); break; }

case pcode___application__METHOD_SetIcon:{ _application::METHOD_SetIcon(v[0]->toQString()); break; }

case pcode___application__METHOD_SetClipboardText:{ _application::METHOD_SetClipboardText(v[0]->toQString()); break; }

case pcode___application__METHOD_ClipboardText:{ interpreter_parameter *p = new interpreter_parameter( _application::METHOD_ClipboardText()); if (bReturn) pushStack(p); else delete p; break; }

case pcode___application__METHOD_Path:
case pcode___application__METHOD_DirectoryName:{ interpreter_parameter *p = new interpreter_parameter( _application::METHOD_DirectoryName()); if (bReturn) pushStack(p); else delete p; break; }

case pcode___application__METHOD_FileName:{ interpreter_parameter *p = new interpreter_parameter( _application::METHOD_FileName()); if (bReturn) pushStack(p); else delete p; break; }

case pcode___application__METHOD_ArgumentsAsString:{ interpreter_parameter *p = new interpreter_parameter( _application::METHOD_ArgumentsAsString()); if (bReturn) pushStack(p); else delete p; break; }

case pcode___application__METHOD_Arguments:{ interpreter_parameter *p = new interpreter_parameter( _application::METHOD_Arguments()); if (bReturn) pushStack(p); else delete p; break; }

case pcode___application__METHOD_IsScrollBarsEnabled:{ b = _application::METHOD_IsScrollBarsEnabled(); if (bReturn) pushStackBoolean(b); break; }

                                      
case pcode___application__METHOD_Run:{ _application::METHOD_Run(); break; }

case pcode___application__METHOD_Stop:{ _application::METHOD_Stop(); break; }

case pcode___application__METHOD_SetWaitCursor:{ _application::METHOD_SetWaitCursor(); break; }

case pcode___application__METHOD_UnsetWaitCursor:{ _application::METHOD_UnsetWaitCursor(); break; }


case pcode___application__METHOD_AddLanguageTranslatorFile:{ _application::METHOD_AddLanguageTranslatorFile(v[0]->toQString()); break; }

case pcode___application__METHOD_DoEvents:{ _application::METHOD_DoEvents(); break; }

case pcode___application__METHOD_SetStyleSheet:{ _application::METHOD_SetStyleSheet(v[0]->toQString()); break; }

case pcode___application__METHOD_SetLayoutDirection:{ _application::METHOD_SetLayoutDirection(v[0]->tot_boolean()); break; }

case pcode___application__METHOD_ScreenWidth:{ i = _application::METHOD_ScreenWidth(); if (bReturn) pushStackInteger(i); break; }

case pcode___application__METHOD_ScreenHeight:{ i = _application::METHOD_ScreenHeight(); if (bReturn) pushStackInteger(i);  break; }

case pcode___application__METHOD_LoadExternalBrowserWithHTML:{ _application::METHOD_LoadExternalBrowserWithHTML(v[0]->toQString()); break; }


case pcode___application__METHOD_SetFocusNextForm:{ _application::METHOD_SetFocusNextForm(); break; }

case pcode___application__METHOD_SetFocusPreviousForm:{ _application::METHOD_SetFocusPreviousForm(); break; }

case pcode___application__METHOD_Cascade:{ _application::METHOD_Cascade(); break; }

case pcode___application__METHOD_CloseActiveForm:{ _application::METHOD_CloseActiveForm(); break; }

case pcode___application__METHOD_CloseAllapplication:{ _application::METHOD_CloseAll(); break; }


case pcode___application__METHOD_Tile:{ _application::METHOD_Tile(); break; }

case pcode___application__METHOD_SetScrollBarsEnabled:{ _application::METHOD_SetScrollBarsEnabled(v[0]->tot_boolean()); break; }

case pcode___application__METHOD_TakeScreenShot:{ interpreter_parameter *p = new interpreter_parameter( _application::METHOD_TakeScreenShot()); if (bReturn) pushStack(p); else delete p; break; }

case pcode___application__METHOD_StandardIcon:{ p = new interpreter_parameter( _application::METHOD_StandardIcon(v[0]->toQString())); if (bReturn) pushStack(p); else delete p; break; }

case pcode___application__METHOD_AvailableFontNames:{ p = new interpreter_parameter( _application::METHOD_AvailableFontNames()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___application__METHOD_ProcessId:{ p = new interpreter_parameter( _application::METHOD_ProcessId()); if (bReturn) pushStack(p); else delete p; break; }

case pcode___application__METHOD_PrintHtml:{ _application::METHOD_PrintHtml(v[0]->toQString()); break; }
case pcode___application__METHOD_PrintHtmlAsPdf:{ _application::METHOD_PrintHtmlAsPdf(v[0]->toQString(), v[1]->toQString()); break; }

case pcode___application__METHOD_QtException:{ interpreter_parameter *p = new interpreter_parameter( _application::METHOD_QtException()); if (bReturn) pushStack(p); else delete p; break; }
case pcode___application__METHOD_ClearQtException:{  _application::METHOD_ClearQtException(); break; }
                    