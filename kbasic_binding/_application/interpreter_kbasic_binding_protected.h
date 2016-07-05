



static void EVENT_Forms_OnFormGotFocus(const QString & s){ 

  if (nEVENT_Forms_OnFormGotFocus != 1){
	static QList<int> param;
  if (kbEventId && nEVENT_Forms_OnFormGotFocus == 0 && param.count() == 0){ 
	 param.append((pcode__QSTRING)); 
  }
  if ((nEVENT_Forms_OnFormGotFocus == 2) || (nEVENT_Forms_OnFormGotFocus == 0 && EXTERN_myInterpreter && EXTERN_myInterpreter->hasEvent(kbEventScope, kbEventId, "Forms_OnFormGotFocus", "", "", &param))){
    nEVENT_Forms_OnFormGotFocus = 2;
		EXTERN_myInterpreter->pushStack(new interpreter_parameter(s));
		EXTERN_myInterpreter->callEvent(kbEventScope, kbEventId, "Forms_OnFormGotFocus", "", "", &param);
    
		return;
	}
  if (kbEventId) nEVENT_Forms_OnFormGotFocus = 1;
}
	
 }

static void EVENT_Actions_OnAction(const QString & s){ 

  if (nEVENT_Actions_OnAction != 1){
	static QList<int> param;
  if (kbEventId && nEVENT_Actions_OnAction == 0 && param.count() == 0){ 
	 param.append((pcode__QSTRING)); 
  }
  if ((nEVENT_Actions_OnAction == 2) || (nEVENT_Actions_OnAction == 0 && EXTERN_myInterpreter && EXTERN_myInterpreter->hasEvent(kbEventScope, kbEventId, "Actions_OnAction", "", "", &param))){
    nEVENT_Actions_OnAction = 2;
		EXTERN_myInterpreter->pushStack(new interpreter_parameter(s));
		EXTERN_myInterpreter->callEvent(kbEventScope, kbEventId, "Actions_OnAction", "", "", &param);
    
		return;
	}	
  if (kbEventId) nEVENT_Actions_OnAction = 1;
}
	
 }

static void EVENT_MenuBar_OnEvent(const QString & s)
{ 
  if (nEVENT_MenuBar_OnEvent != 1){
	  static QList<int> param;
    if (kbEventId && nEVENT_MenuBar_OnEvent == 0 && param.count() == 0){ 
	  param.append((pcode__QSTRING)); 
    }
    if ((nEVENT_MenuBar_OnEvent == 2) || (nEVENT_MenuBar_OnEvent == 0 && EXTERN_myInterpreter && EXTERN_myInterpreter->hasEvent(kbEventScope, kbEventId, "MenuBar_OnEvent", "", "", &param))){
      nEVENT_MenuBar_OnEvent = 2;
		  EXTERN_myInterpreter->pushStack(new interpreter_parameter(s));
		  EXTERN_myInterpreter->callEvent(kbEventScope, kbEventId, "MenuBar_OnEvent", "", "", &param);
      
		  return;
	  }
    if (kbEventId) nEVENT_MenuBar_OnEvent = 1;
  }
}

static void EVENT_MenuBar_OnHovered(const QString & s)
{ 
  if (nEVENT_MenuBar_OnHovered != 1){
	  static QList<int> param;
    if (kbEventId && nEVENT_MenuBar_OnHovered == 0 && param.count() == 0){ 
	  param.append((pcode__QSTRING)); 
    }
    if ((nEVENT_MenuBar_OnHovered == 2) || (nEVENT_MenuBar_OnHovered == 0 && EXTERN_myInterpreter && EXTERN_myInterpreter->hasEvent(kbEventScope, kbEventId, "MenuBar_OnHovered", "", "", &param))){
      nEVENT_MenuBar_OnHovered = 2;
		  EXTERN_myInterpreter->pushStack(new interpreter_parameter(s));
		  EXTERN_myInterpreter->callEvent(kbEventScope, kbEventId, "MenuBar_OnHovered", "", "", &param);
      
		  return;
	  }
    if (kbEventId) nEVENT_MenuBar_OnHovered = 1;
  }
}

static void EVENT_MenuBar_OnAboutToShow(const QString & s)
{ 
  if (nEVENT_MenuBar_OnAboutToShow != 1){
	  static QList<int> param;
    if (kbEventId && nEVENT_MenuBar_OnAboutToShow == 0 && param.count() == 0){ 
	  param.append((pcode__QSTRING)); 
    }
    if ((nEVENT_MenuBar_OnAboutToShow == 2) || (nEVENT_MenuBar_OnAboutToShow == 0 && EXTERN_myInterpreter && EXTERN_myInterpreter->hasEvent(kbEventScope, kbEventId, "MenuBar_OnAboutToShow", "", "", &param))){
      nEVENT_MenuBar_OnAboutToShow = 2;
		  EXTERN_myInterpreter->pushStack(new interpreter_parameter(s));
		  EXTERN_myInterpreter->callEvent(kbEventScope, kbEventId, "MenuBar_OnAboutToShow", "", "", &param);
      
		  return;
	  }
    if (kbEventId) nEVENT_MenuBar_OnAboutToShow = 1;
  }
}

static void EVENT_MenuBar_OnAboutToHide(const QString & s)
{ 
  if (nEVENT_MenuBar_OnAboutToHide != 1){
	  static QList<int> param;
    if (kbEventId && nEVENT_MenuBar_OnAboutToHide == 0 && param.count() == 0){ 
	  param.append((pcode__QSTRING)); 
    }
    if ((nEVENT_MenuBar_OnAboutToHide == 2) || (nEVENT_MenuBar_OnAboutToHide == 0 && EXTERN_myInterpreter && EXTERN_myInterpreter->hasEvent(kbEventScope, kbEventId, "MenuBar_OnAboutToHide", "", "", &param))){
      nEVENT_MenuBar_OnAboutToHide = 2;
		  EXTERN_myInterpreter->pushStack(new interpreter_parameter(s));
		  EXTERN_myInterpreter->callEvent(kbEventScope, kbEventId, "MenuBar_OnAboutToHide", "", "", &param);
      
		  return;
	  }
    if (kbEventId) nEVENT_MenuBar_OnAboutToHide = 1;
  }
}

static void EVENT_ToolBar_OnEvent(const QString & s)
{ 
  if (nEVENT_ToolBar_OnEvent != 1){
	  static QList<int> param;
    if (kbEventId && nEVENT_ToolBar_OnEvent == 0 && param.count() == 0){ 
	  param.append((pcode__QSTRING)); 
    }
    if ((nEVENT_ToolBar_OnEvent == 2) || (nEVENT_ToolBar_OnEvent == 0 && EXTERN_myInterpreter && EXTERN_myInterpreter->hasEvent(kbEventScope, kbEventId, "ToolBar_OnEvent", "", "", &param))){
      nEVENT_ToolBar_OnEvent = 2;
		  EXTERN_myInterpreter->pushStack(new interpreter_parameter(s));
		  EXTERN_myInterpreter->callEvent(kbEventScope, kbEventId, "ToolBar_OnEvent", "", "", &param);
      
		  return;
	  }
    if (kbEventId) nEVENT_ToolBar_OnEvent = 1;
  }
}

static void EVENT_SystemTray_OnEvent(const QString & s)
{ 
  if (nEVENT_SystemTray_OnEvent != 1){
	  static QList<int> param;
    if (kbEventId && nEVENT_SystemTray_OnEvent == 0 && param.count() == 0){ 
	  param.append((pcode__QSTRING)); 
    }
    if ((nEVENT_SystemTray_OnEvent == 2) || (nEVENT_SystemTray_OnEvent == 0 && EXTERN_myInterpreter && EXTERN_myInterpreter->hasEvent(kbEventScope, kbEventId, "SystemTray_OnEvent", "", "", &param))){
      nEVENT_SystemTray_OnEvent = 2;
		  EXTERN_myInterpreter->pushStack(new interpreter_parameter(s));
		  EXTERN_myInterpreter->callEvent(kbEventScope, kbEventId, "SystemTray_OnEvent", "", "", &param);

		  return;
	  }
    if (kbEventId) nEVENT_SystemTray_OnEvent = 1;
  }
}


