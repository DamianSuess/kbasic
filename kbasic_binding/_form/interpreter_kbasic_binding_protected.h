

bool bSupresseRecursive;

int nEVENT_OnDockMove;
int nEVENT_OnDockShow;
int nEVENT_OnDockHide;
int nEVENT_OnDockFloating;
int nEVENT_OnDockNotFloating;


int nEVENT_OnSingleShot;
int nEVENT_OnEnabled;
int nEVENT_OnDisabled;


//int nEVENT_OnLoad;

int nEVENT_OnScroll;

int nEVENT_OnMultiPageShow;

int nEVENT_OnGoTo;

int nEVENT_OnGoTo2;

int nEVENT_OnQuery;

int nEVENT_OnDirty;

int nEVENT_OnAddNew;

int nEVENT_OnBeforeInsert;

int nEVENT_OnBeforeUpdate;

int nEVENT_OnBeforeDelete;


int nEVENT_OnAfterInsert;

int nEVENT_OnAfterUpdate;

int nEVENT_OnAfterDelete;

int nEVENT_OnOpen;

int nEVENT_OnClose;

int nEVENT_OnContextMenu;

int nEVENT_OnDragEnter;

int nEVENT_OnDragExit;

int nEVENT_OnDragMove;

int nEVENT_OnDrop;

int nEVENT_OnEnter;

int nEVENT_OnGotFocus;

int nEVENT_OnLostFocus;

int nEVENT_OnHide;

int nEVENT_OnKeyDown;

int nEVENT_OnKeyUp;

int nEVENT_OnKeyPress;

int nEVENT_OnExit;

int nEVENT_OnDblClick;

int nEVENT_OnClick;

int nEVENT_OnMouseMove;

int nEVENT_OnMouseDown;

int nEVENT_OnMouseUp;

int nEVENT_OnMove;

int nEVENT_OnPaint;

int nEVENT_OnResize;

int nEVENT_OnShow;

int nEVENT_OnMouseWheel;

int nEVENT_OnTimer;

int nEVENT_OnPrint;



void initEvent()
{  
  bSupresseRecursive = false;
    
  nEVENT_OnDockMove = 0;
  nEVENT_OnDockShow = 0;
  nEVENT_OnDockHide = 0;
  nEVENT_OnDockFloating = 0;
  nEVENT_OnDockNotFloating = 0;


  nEVENT_OnSingleShot = 0;
  nEVENT_OnEnabled = 0;
  nEVENT_OnDisabled = 0;


  nEVENT_OnScroll = 0;
    
  nEVENT_OnMultiPageShow = 0;

  //nEVENT_OnLoad = 0;
  nEVENT_OnGoTo = 0;
  nEVENT_OnGoTo2 = 0;
  nEVENT_OnQuery = 0;
  nEVENT_OnDirty = 0;
  nEVENT_OnAddNew = 0;
  
  nEVENT_OnBeforeInsert = 0;
  nEVENT_OnBeforeUpdate = 0;
  nEVENT_OnBeforeDelete = 0;

  nEVENT_OnAfterInsert = 0;
  nEVENT_OnAfterUpdate = 0;
  nEVENT_OnAfterDelete = 0;

  nEVENT_OnOpen = 0;

  nEVENT_OnClose = 0;

  nEVENT_OnContextMenu = 0;

  nEVENT_OnDragEnter = 0;

  nEVENT_OnDragExit = 0;

  nEVENT_OnDragMove = 0;

  nEVENT_OnDrop = 0;

  nEVENT_OnEnter = 0;

  nEVENT_OnGotFocus = 0;

  nEVENT_OnLostFocus = 0;

  nEVENT_OnHide = 0;

  nEVENT_OnKeyDown = 0;

  nEVENT_OnKeyUp = 0;

  nEVENT_OnKeyPress = 0;

  nEVENT_OnExit = 0;

  nEVENT_OnDblClick = 0;

  nEVENT_OnClick = 0;

  nEVENT_OnMouseMove = 0;

  nEVENT_OnMouseDown = 0;

  nEVENT_OnMouseUp = 0;

  nEVENT_OnMove = 0;

  nEVENT_OnPaint = 0;

  nEVENT_OnResize = 0;

  nEVENT_OnShow = 0;

  nEVENT_OnMouseWheel = 0;

  nEVENT_OnTimer = 0;

  nEVENT_OnPrint = 0;

  nEVENT_OnEnter = 0;


}

void EVENT_OnPaint(t_integer X, t_integer Y, t_integer Width, t_integer Height);



void EVENT_OnDockMove(){ 
  if (nEVENT_OnDockMove != 1){
	QList<int> *param = new QList<int>;
	
  if ((nEVENT_OnDockMove == 2) || (nEVENT_OnDockMove == 0 && myInterpreter && myInterpreter->hasEvent(kbScope, kbId, "OnDockMove", acGroup, acName, param))){
    nEVENT_OnDockMove = 2;
		EventSource = this; myInterpreter->callEvent(kbScope, kbId, "OnDockMove", acGroup, acName, param);
		delete param; return;
	}
	delete param;
  if (kbId) nEVENT_OnDockMove = 1;
}
#ifdef CLASS
	CLASS::EVENT_OnDockMove();
#endif
 }
 
void EVENT_OnDockShow(){ 
  if (nEVENT_OnDockShow != 1){
	QList<int> *param = new QList<int>;
	
  if ((nEVENT_OnDockShow == 2) || (nEVENT_OnDockShow == 0 && myInterpreter && myInterpreter->hasEvent(kbScope, kbId, "OnDockShow", acGroup, acName, param))){
    nEVENT_OnDockShow = 2;
		EventSource = this; myInterpreter->callEvent(kbScope, kbId, "OnDockShow", acGroup, acName, param);
		delete param; return;
	}
	delete param;
  if (kbId) nEVENT_OnDockShow = 1;
}
#ifdef CLASS
	CLASS::EVENT_OnDockShow();
#endif
 }

void EVENT_OnDockHide(){ 
  if (nEVENT_OnDockHide != 1){
	QList<int> *param = new QList<int>;
	
  if ((nEVENT_OnDockHide == 2) || (nEVENT_OnDockHide == 0 && myInterpreter && myInterpreter->hasEvent(kbScope, kbId, "OnDockHide", acGroup, acName, param))){
    nEVENT_OnDockHide = 2;
		EventSource = this; myInterpreter->callEvent(kbScope, kbId, "OnDockHide", acGroup, acName, param);
		delete param; return;
	}
	delete param;
  if (kbId) nEVENT_OnDockHide = 1;
}
#ifdef CLASS
	CLASS::EVENT_OnDockHide();
#endif
 }



void EVENT_OnDockFloating(){ 
  if (nEVENT_OnDockFloating != 1){
	QList<int> *param = new QList<int>;
	
  if ((nEVENT_OnDockFloating == 2) || (nEVENT_OnDockFloating == 0 && myInterpreter && myInterpreter->hasEvent(kbScope, kbId, "OnDockFloating", acGroup, acName, param))){
    nEVENT_OnDockFloating = 2;
		EventSource = this; myInterpreter->callEvent(kbScope, kbId, "OnDockFloating", acGroup, acName, param);
		delete param; return;
	}
	delete param;
  if (kbId) nEVENT_OnDockFloating = 1;
}
#ifdef CLASS
	CLASS::EVENT_OnDockFloating();
#endif
 }

void EVENT_OnDockNotFloating(){ 
  if (nEVENT_OnDockNotFloating != 1){
	QList<int> *param = new QList<int>;
	
  if ((nEVENT_OnDockNotFloating == 2) || (nEVENT_OnDockNotFloating == 0 && myInterpreter && myInterpreter->hasEvent(kbScope, kbId, "OnDockNotFloating", acGroup, acName, param))){
    nEVENT_OnDockNotFloating = 2;
		EventSource = this; myInterpreter->callEvent(kbScope, kbId, "OnDockNotFloating", acGroup, acName, param);
		delete param; return;
	}
	delete param;
  if (kbId) nEVENT_OnDockNotFloating = 1;
}
#ifdef CLASS
	CLASS::EVENT_OnDockNotFloating();
#endif
 }

void EVENT_OnSingleShot(){ 
  if (nEVENT_OnSingleShot != 1){
	QList<int> *param = new QList<int>;
	
  if ((nEVENT_OnSingleShot == 2) || (nEVENT_OnSingleShot == 0 && myInterpreter && myInterpreter->hasEvent(kbScope, kbId, "OnSingleShot", acGroup, acName, param))){
    nEVENT_OnSingleShot = 2;
		EventSource = this; myInterpreter->callEvent(kbScope, kbId, "OnSingleShot", acGroup, acName, param);
		delete param; return;
	}
	delete param;
  if (kbId) nEVENT_OnSingleShot = 1;
}
#ifdef CLASS
	CLASS::EVENT_OnSingleShot();
#endif
 }

void EVENT_OnEnabled(){ 
  if (nEVENT_OnEnabled != 1){
	QList<int> *param = new QList<int>;
	
  if ((nEVENT_OnEnabled == 2) || (nEVENT_OnEnabled == 0 && myInterpreter && myInterpreter->hasEvent(kbScope, kbId, "OnEnabled", acGroup, acName, param))){
    nEVENT_OnEnabled = 2;
		EventSource = this; myInterpreter->callEvent(kbScope, kbId, "OnEnabled", acGroup, acName, param);
		delete param; return;
	}
	delete param;
  if (kbId) nEVENT_OnEnabled = 1;
}
#ifdef CLASS
	CLASS::EVENT_OnEnabled();
#endif
 }

void EVENT_OnDisabled(){ 
  if (nEVENT_OnDisabled != 1){
	QList<int> *param = new QList<int>;
	
  if ((nEVENT_OnDisabled == 2) || (nEVENT_OnDisabled == 0 && myInterpreter && myInterpreter->hasEvent(kbScope, kbId, "OnDisabled", acGroup, acName, param))){
    nEVENT_OnDisabled = 2;
		EventSource = this; myInterpreter->callEvent(kbScope, kbId, "OnDisabled", acGroup, acName, param);
		delete param; return;
	}
	delete param;
  if (kbId) nEVENT_OnDisabled = 1;
}
#ifdef CLASS
	CLASS::EVENT_OnDisabled();
#endif
 }


void EVENT_OnScroll(){ 
  if (nEVENT_OnScroll != 1){
	static QList<int> param;;

  if ((nEVENT_OnScroll == 2) || (nEVENT_OnScroll == 0 && myInterpreter && myInterpreter->hasEvent(kbScope, kbId, "OnScroll", acGroup, acName, &param))){
    nEVENT_OnScroll = 2;
		EventSource = this; myInterpreter->callEvent(kbScope, kbId, "OnScroll", acGroup, acName, &param);
    CLASS::EVENT_OnScroll();
		return;
	}
	//delete param; 
  if (kbId) nEVENT_OnScroll = 1;
}
	CLASS::EVENT_OnScroll();
 }

void EVENT_OnMultiPageShow(t_integer nPage){ 
  if (nEVENT_OnMultiPageShow != 1){
	static QList<int> param;;
  if (kbId && nEVENT_OnMultiPageShow == 0 && param.count() == 0){ 
	 param.append((pcode__INTEGER)); 
  }
  if ((nEVENT_OnMultiPageShow == 2) || (nEVENT_OnMultiPageShow == 0 && myInterpreter && myInterpreter->hasEvent(kbScope, kbId, "OnMultiPageShow", acGroup, acName, &param))){
    nEVENT_OnMultiPageShow = 2;
		myInterpreter->pushStack(new interpreter_parameter(nPage));
		EventSource = this; myInterpreter->callEvent(kbScope, kbId, "OnMultiPageShow", acGroup, acName, &param);
    CLASS::EVENT_OnMultiPageShow(nPage);
		return;
	}
	
  if (kbId) nEVENT_OnMultiPageShow = 1;
}
	CLASS::EVENT_OnMultiPageShow(nPage);
}


void EVENT_OnGoTo(){ 
  if (nEVENT_OnGoTo != 1){
	static QList<int> param;;

  if ((nEVENT_OnGoTo == 2) || (nEVENT_OnGoTo == 0 && myInterpreter && myInterpreter->hasEvent(kbScope, kbId, "OnGoTo", acGroup, acName, &param))){
    nEVENT_OnGoTo = 2;
		EventSource = this; myInterpreter->callEvent(kbScope, kbId, "OnGoTo", acGroup, acName, &param);
    CLASS::EVENT_OnGoTo();
		return;
	}
	//delete param; 
  if (kbId) nEVENT_OnGoTo = 1;
}
	CLASS::EVENT_OnGoTo();
 }

void EVENT_OnGoTo2(){ 
  if (nEVENT_OnGoTo2 != 1){
	static QList<int> param;;

  if ((nEVENT_OnGoTo2 == 2) || (nEVENT_OnGoTo2 == 0 && myInterpreter && myInterpreter->hasEvent(kbScope, kbId, "OnGoTo2", acGroup, acName, &param))){
    nEVENT_OnGoTo2 = 2;
		EventSource = this; myInterpreter->callEvent(kbScope, kbId, "OnGoTo2", acGroup, acName, &param);
    CLASS::EVENT_OnGoTo2();
		return;
	}
	//delete param; 
  if (kbId) nEVENT_OnGoTo2 = 1;
}
	CLASS::EVENT_OnGoTo2();
 }

void EVENT_OnQuery(){ 
  if (nEVENT_OnQuery != 1){
	static QList<int> param;;

  if ((nEVENT_OnQuery == 2) || (nEVENT_OnQuery == 0 && myInterpreter && myInterpreter->hasEvent(kbScope, kbId, "OnQuery", acGroup, acName, &param))){
    nEVENT_OnQuery = 2;
		EventSource = this; myInterpreter->callEvent(kbScope, kbId, "OnQuery", acGroup, acName, &param);
    CLASS::EVENT_OnQuery();
		return;
	}
	//delete param; 
  if (kbId) nEVENT_OnQuery = 1;
}
	CLASS::EVENT_OnQuery();
 }
void EVENT_OnDirty(){ 
  if (nEVENT_OnDirty != 1){
	static QList<int> param;;

  if ((nEVENT_OnDirty == 2) || (nEVENT_OnDirty == 0 && myInterpreter && myInterpreter->hasEvent(kbScope, kbId, "OnDirty", acGroup, acName, &param))){
    nEVENT_OnDirty = 2;
		EventSource = this; myInterpreter->callEvent(kbScope, kbId, "OnDirty", acGroup, acName, &param);
    CLASS::EVENT_OnDirty();
		return;
	}
	//delete param; 
  if (kbId) nEVENT_OnDirty = 1;
}
	CLASS::EVENT_OnDirty();
 }
void EVENT_OnAddNew(){ 
  if (nEVENT_OnAddNew != 1){
	static QList<int> param;;

  if ((nEVENT_OnAddNew == 2) || (nEVENT_OnAddNew == 0 && myInterpreter && myInterpreter->hasEvent(kbScope, kbId, "OnAddNew", acGroup, acName, &param))){
    nEVENT_OnAddNew = 2;
		EventSource = this; myInterpreter->callEvent(kbScope, kbId, "OnAddNew", acGroup, acName, &param);
    CLASS::EVENT_OnAddNew();
		return;
	}
	//delete param; 
  if (kbId) nEVENT_OnAddNew = 1;
}
	CLASS::EVENT_OnAddNew();
 }

void EVENT_OnAfterInsert(){ 
  if (nEVENT_OnAfterInsert != 1){
	static QList<int> param;;

  if ((nEVENT_OnAfterInsert == 2) || (nEVENT_OnAfterInsert == 0 && myInterpreter && myInterpreter->hasEvent(kbScope, kbId, "OnAfterInsert", acGroup, acName, &param))){
    nEVENT_OnAfterInsert = 2;
		EventSource = this; myInterpreter->callEvent(kbScope, kbId, "OnAfterInsert", acGroup, acName, &param);
    CLASS::EVENT_OnAfterInsert();
		return;
	}
	//delete param; 
  if (kbId) nEVENT_OnAfterInsert = 1;
}
	CLASS::EVENT_OnAfterInsert();
 }

void EVENT_OnAfterUpdate(){ 
  if (nEVENT_OnAfterUpdate != 1){
	static QList<int> param;;

  if ((nEVENT_OnAfterUpdate == 2) || (nEVENT_OnAfterUpdate == 0 && myInterpreter && myInterpreter->hasEvent(kbScope, kbId, "OnAfterUpdate", acGroup, acName, &param))){
    nEVENT_OnAfterUpdate = 2;
		EventSource = this; myInterpreter->callEvent(kbScope, kbId, "OnAfterUpdate", acGroup, acName, &param);
    CLASS::EVENT_OnAfterUpdate();
		return;
	}
	//delete param; 
  if (kbId) nEVENT_OnAfterUpdate = 1;
}
	CLASS::EVENT_OnAfterUpdate();
 }

void EVENT_OnAfterDelete(){ 
  if (nEVENT_OnAfterDelete != 1){
	static QList<int> param;;

  if ((nEVENT_OnAfterDelete == 2) || (nEVENT_OnAfterDelete == 0 && myInterpreter && myInterpreter->hasEvent(kbScope, kbId, "OnAfterDelete", acGroup, acName, &param))){
    nEVENT_OnAfterDelete = 2;
		EventSource = this; myInterpreter->callEvent(kbScope, kbId, "OnAfterDelete", acGroup, acName, &param);
    CLASS::EVENT_OnAfterDelete();
		return;
	}
	//delete param; 
  if (kbId) nEVENT_OnAfterDelete = 1;
}
	CLASS::EVENT_OnAfterDelete();
 }
void EVENT_OnBeforeInsert(t_boolean *Cancel){ 
  if (nEVENT_OnBeforeInsert != 1){
	static QList<int> param;
  if (kbId && nEVENT_OnBeforeInsert == 0 && param.count() == 0){ 
  	 param.append((pcode__BOOLEAN)); 
  }
  if ((nEVENT_OnBeforeInsert == 2) || (nEVENT_OnBeforeInsert == 0 && myInterpreter && myInterpreter->hasEvent(kbScope, kbId, "OnBeforeInsert", acGroup, acName, &param))){
    nEVENT_OnBeforeInsert = 2;
		myInterpreter->pushStack(new interpreter_parameter(Cancel));
		EventSource = this; myInterpreter->callEvent(kbScope, kbId, "OnBeforeInsert", acGroup, acName, &param);
    CLASS::EVENT_OnBeforeInsert(Cancel);
		return;
	}
	//delete param; 
  if (kbId) nEVENT_OnBeforeInsert = 1;
}
	CLASS::EVENT_OnBeforeInsert(Cancel);
 }
void EVENT_OnBeforeUpdate(t_boolean *Cancel){ 
  if (nEVENT_OnBeforeUpdate != 1){
	static QList<int> param;;
  if (kbId && nEVENT_OnBeforeUpdate == 0 && param.count() == 0){ 
	 param.append((pcode__BOOLEAN)); 
  }
  if ((nEVENT_OnBeforeUpdate == 2) || (nEVENT_OnBeforeUpdate == 0 && myInterpreter && myInterpreter->hasEvent(kbScope, kbId, "OnBeforeUpdate", acGroup, acName, &param))){
    nEVENT_OnBeforeUpdate = 2;
		myInterpreter->pushStack(new interpreter_parameter(Cancel));
		EventSource = this; myInterpreter->callEvent(kbScope, kbId, "OnBeforeUpdate", acGroup, acName, &param);
    CLASS::EVENT_OnBeforeUpdate(Cancel);
		return;
	}
	//delete param; 
  if (kbId) nEVENT_OnBeforeUpdate = 1;
}
	CLASS::EVENT_OnBeforeUpdate(Cancel);
 }
void EVENT_OnBeforeDelete(t_boolean *Cancel){ 
  if (nEVENT_OnBeforeDelete != 1){
	static QList<int> param;;
  if (kbId && nEVENT_OnBeforeDelete == 0 && param.count() == 0){ 
	 param.append((pcode__BOOLEAN)); 
  }
  if ((nEVENT_OnBeforeDelete == 2) || (nEVENT_OnBeforeDelete == 0 && myInterpreter && myInterpreter->hasEvent(kbScope, kbId, "OnBeforeDelete", acGroup, acName, &param))){
    nEVENT_OnBeforeDelete = 2;
		myInterpreter->pushStack(new interpreter_parameter(Cancel));
		EventSource = this; myInterpreter->callEvent(kbScope, kbId, "OnBeforeDelete", acGroup, acName, &param);
    CLASS::EVENT_OnBeforeDelete(Cancel);
		return;
	}
	//delete param; 
  if (kbId) nEVENT_OnBeforeDelete = 1;
}
	CLASS::EVENT_OnBeforeDelete(Cancel);
}





void EVENT_OnOpen(){ 
  if (nEVENT_OnOpen != 1){
	static QList<int> param;;
	
  if ((nEVENT_OnOpen == 2) || (nEVENT_OnOpen == 0 && myInterpreter && myInterpreter->hasEvent(kbScope, kbId, "OnOpen", acGroup, acName, &param))){
    nEVENT_OnOpen = 2;
		EventSource = this; myInterpreter->callEvent(kbScope, kbId, "OnOpen", acGroup, acName, &param);
		return;
	}
	//delete param; 
  if (kbId) nEVENT_OnOpen = 1;
}
#ifdef CLASS
	CLASS::EVENT_OnOpen();
#endif
 }
void EVENT_OnClose(t_boolean *Cancel){ 
  if (nEVENT_OnClose != 1){
	static QList<int> param;;
  if (kbId && nEVENT_OnClose == 0 && param.count() == 0){ 
	 param.append((pcode__BOOLEAN)); 
  }
  if ((nEVENT_OnClose == 2) || (nEVENT_OnClose == 0 && myInterpreter && myInterpreter->hasEvent(kbScope, kbId, "OnClose", acGroup, acName, &param))){
    nEVENT_OnClose = 2;
		myInterpreter->pushStack(new interpreter_parameter(Cancel));
		EventSource = this; myInterpreter->callEvent(kbScope, kbId, "OnClose", acGroup, acName, &param, 0, 0, Cancel);
		return;
	}
	//delete param; 
  if (kbId) nEVENT_OnClose = 1;
}
#ifdef CLASS
	CLASS::EVENT_OnClose(Cancel);
#endif
 }
bool EVENT_OnContextMenu(t_integer X, t_integer Y, t_integer GlobalX, t_integer GlobalY){ 
  if (nEVENT_OnContextMenu != 1){
	static QList<int> param;;
  if (kbId && nEVENT_OnContextMenu == 0 && param.count() == 0){ 
	 param.append((pcode__t_integer));  param.append((pcode__t_integer));  param.append((pcode__t_integer));  param.append((pcode__t_integer)); 
  }
  if ((nEVENT_OnContextMenu == 2) || (nEVENT_OnContextMenu == 0 && myInterpreter && myInterpreter->hasEvent(kbScope, kbId, "OnContextMenu", acGroup, acName, &param))){
    nEVENT_OnContextMenu = 2;
		myInterpreter->pushStack(new interpreter_parameter(X));
		myInterpreter->pushStack(new interpreter_parameter(Y));
		myInterpreter->pushStack(new interpreter_parameter(GlobalX));
		myInterpreter->pushStack(new interpreter_parameter(GlobalY));
		EventSource = this; myInterpreter->callEvent(kbScope, kbId, "OnContextMenu", acGroup, acName, &param);
		return true;
	}
	//delete param; 
  if (kbId) nEVENT_OnContextMenu = 1;
}
#ifdef CLASS
	return CLASS::EVENT_OnContextMenu(X, Y, GlobalX, GlobalY);
#endif	
  return false;
 }
void EVENT_OnDragEnter(t_boolean *Cancel, t_integer X, t_integer Y, t_integer GlobalX, t_integer GlobalY, t_integer Width, t_integer Height, t_boolean Left, t_boolean Right, t_boolean Mid, t_boolean Shift, t_boolean Control, t_boolean Alt){ 
  if (nEVENT_OnDragEnter != 1){
	static QList<int> param;;
  if (kbId && nEVENT_OnDragEnter == 0 && param.count() == 0){ 
	 param.append((pcode__t_boolean));  param.append((pcode__t_integer)); param.append((pcode__t_integer)); param.append((pcode__t_integer));  param.append((pcode__t_integer));  param.append((pcode__t_integer));  param.append((pcode__t_integer)); param.append((pcode__t_boolean)); param.append((pcode__t_boolean)); param.append((pcode__t_boolean)); param.append((pcode__t_boolean)); param.append((pcode__t_boolean)); param.append((pcode__t_boolean));
  }
  if ((nEVENT_OnDragEnter == 2) || (nEVENT_OnDragEnter == 0 && myInterpreter && myInterpreter->hasEvent(kbScope, kbId, "OnDragEnter", acGroup, acName, &param))){
    nEVENT_OnDragEnter = 2;
		myInterpreter->pushStack(new interpreter_parameter(Cancel));
		myInterpreter->pushStack(new interpreter_parameter(X));
		myInterpreter->pushStack(new interpreter_parameter(Y));
		myInterpreter->pushStack(new interpreter_parameter(GlobalX));
		myInterpreter->pushStack(new interpreter_parameter(GlobalY));
		myInterpreter->pushStack(new interpreter_parameter(Width));
		myInterpreter->pushStack(new interpreter_parameter(Height));
		myInterpreter->pushStack(new interpreter_parameter(Left));
		myInterpreter->pushStack(new interpreter_parameter(Right));
		myInterpreter->pushStack(new interpreter_parameter(Mid));
		myInterpreter->pushStack(new interpreter_parameter(Shift));
		myInterpreter->pushStack(new interpreter_parameter(Control));
		myInterpreter->pushStack(new interpreter_parameter(Alt));     
		EventSource = this; myInterpreter->callEvent(kbScope, kbId, "OnDragEnter", acGroup, acName, &param);
		return;
	}
	//delete param; 
  if (kbId) nEVENT_OnDragEnter = 1;
}
#ifdef CLASS
	CLASS::EVENT_OnDragEnter(Cancel, X, Y, GlobalX, GlobalY, Width, Height, Left, Right, Mid, Shift, Control, Alt);
#endif  
 }
void EVENT_OnDragExit(){ 
  if (nEVENT_OnDragExit != 1){
	static QList<int> param;;
	
  if ((nEVENT_OnDragExit == 2) || (nEVENT_OnDragExit == 0 && myInterpreter && myInterpreter->hasEvent(kbScope, kbId, "OnDragExit", acGroup, acName, &param))){
    nEVENT_OnDragExit = 2;
		EventSource = this; myInterpreter->callEvent(kbScope, kbId, "OnDragExit", acGroup, acName, &param);
		return;
	}
	//delete param; 
  if (kbId) nEVENT_OnDragExit = 1;
}
#ifdef CLASS
	CLASS::EVENT_OnDragExit();
#endif  
 }
void EVENT_OnDragMove(t_boolean *Cancel, t_integer X, t_integer Y, t_integer GlobalX, t_integer GlobalY, t_integer Width, t_integer Height, t_boolean Left, t_boolean Right, t_boolean Mid, t_boolean Shift, t_boolean Control, t_boolean Alt){ 
  if (nEVENT_OnDragMove != 1){
	static QList<int> param;;
  if (kbId && nEVENT_OnDragMove == 0 && param.count() == 0){ 
	 param.append((pcode__t_boolean));   param.append((pcode__t_integer)); param.append((pcode__t_integer));param.append((pcode__t_integer));  param.append((pcode__t_integer));  param.append((pcode__t_integer));  param.append((pcode__t_integer)); param.append((pcode__t_boolean)); param.append((pcode__t_boolean)); param.append((pcode__t_boolean)); param.append((pcode__t_boolean)); param.append((pcode__t_boolean)); param.append((pcode__t_boolean));
  }
  if ((nEVENT_OnDragMove == 2) || (nEVENT_OnDragMove == 0 && myInterpreter && myInterpreter->hasEvent(kbScope, kbId, "OnDragMove", acGroup, acName, &param))){
    nEVENT_OnDragMove = 2;
		myInterpreter->pushStack(new interpreter_parameter(Cancel));
		myInterpreter->pushStack(new interpreter_parameter(X));
		myInterpreter->pushStack(new interpreter_parameter(Y));
		myInterpreter->pushStack(new interpreter_parameter(GlobalX));
		myInterpreter->pushStack(new interpreter_parameter(GlobalY));
		myInterpreter->pushStack(new interpreter_parameter(Width));
		myInterpreter->pushStack(new interpreter_parameter(Height));
		myInterpreter->pushStack(new interpreter_parameter(Left));
		myInterpreter->pushStack(new interpreter_parameter(Right));
		myInterpreter->pushStack(new interpreter_parameter(Mid));
		myInterpreter->pushStack(new interpreter_parameter(Shift));
		myInterpreter->pushStack(new interpreter_parameter(Control));
		myInterpreter->pushStack(new interpreter_parameter(Alt));     
		EventSource = this; myInterpreter->callEvent(kbScope, kbId, "OnDragMove", acGroup, acName, &param);
		return;
	}
	//delete param; 
  if (kbId) nEVENT_OnDragMove = 1;
}
#ifdef CLASS
	CLASS::EVENT_OnDragMove(Cancel, X, Y, GlobalX, GlobalY, Width, Height, Left, Right, Mid, Shift, Control, Alt);
#endif  
 }
void EVENT_OnDrop(t_boolean *Cancel, QString MimeData, t_integer X, t_integer Y, t_integer GlobalX, t_integer GlobalY, t_boolean Left, t_boolean Right, t_boolean Mid, t_boolean Shift, t_boolean Control, t_boolean Alt){ 
  if (nEVENT_OnDrop != 1){
	static QList<int> param;;
  if (kbId && nEVENT_OnDrop == 0 && param.count() == 0){ 
	 param.append((pcode__t_boolean));  param.append((pcode__QString)); param.append((pcode__t_integer)); param.append((pcode__t_integer)); param.append((pcode__t_integer)); param.append((pcode__t_integer)); param.append((pcode__t_boolean)); param.append((pcode__t_boolean)); param.append((pcode__t_boolean)); param.append((pcode__t_boolean)); param.append((pcode__t_boolean)); param.append((pcode__t_boolean));
  }
  if ((nEVENT_OnDrop == 2) || (nEVENT_OnDrop == 0 && myInterpreter && myInterpreter->hasEvent(kbScope, kbId, "OnDrop", acGroup, acName, &param))){
    nEVENT_OnDrop = 2;
		myInterpreter->pushStack(new interpreter_parameter(Cancel));
		myInterpreter->pushStack(new interpreter_parameter(MimeData));
		myInterpreter->pushStack(new interpreter_parameter(X));
		myInterpreter->pushStack(new interpreter_parameter(Y));
		myInterpreter->pushStack(new interpreter_parameter(GlobalX));
		myInterpreter->pushStack(new interpreter_parameter(GlobalY));
    myInterpreter->pushStack(new interpreter_parameter(Left));
		myInterpreter->pushStack(new interpreter_parameter(Right));
		myInterpreter->pushStack(new interpreter_parameter(Mid));
		myInterpreter->pushStack(new interpreter_parameter(Shift));
		myInterpreter->pushStack(new interpreter_parameter(Control));
		myInterpreter->pushStack(new interpreter_parameter(Alt));    
		EventSource = this; myInterpreter->callEvent(kbScope, kbId, "OnDrop", acGroup, acName, &param);
		return;
	}
	//delete param; 
  if (kbId) nEVENT_OnDrop = 1;
}
#ifdef CLASS
  	CLASS::EVENT_OnDrop(Cancel, MimeData, X, Y, GlobalX, GlobalY, Left, Right, Mid, Shift, Control, Alt);
#endif  
 }
void EVENT_OnEnter(){ 
  if (nEVENT_OnEnter != 1){

	static QList<int> param;; 	
	
  if ((nEVENT_OnEnter == 2) || (nEVENT_OnEnter == 0 && myInterpreter && myInterpreter->hasEvent(kbScope, kbId, "OnEnter", acGroup, acName, &param))){
    nEVENT_OnEnter = 2;
		EventSource = this; myInterpreter->callEvent(kbScope, kbId, "OnEnter", acGroup, acName, &param);
		return;
	}
  
	//delete param; 
  if (kbId) nEVENT_OnEnter = 1; 
}
	CLASS::EVENT_OnEnter(); 
 }
void EVENT_OnGotFocus(){ 
  if (nEVENT_OnGotFocus != 1){
	static QList<int> param;;
	
  if ((nEVENT_OnGotFocus == 2) || (nEVENT_OnGotFocus == 0 && myInterpreter && myInterpreter->hasEvent(kbScope, kbId, "OnGotFocus", acGroup, acName, &param))){
    nEVENT_OnGotFocus = 2;
		EventSource = this; myInterpreter->callEvent(kbScope, kbId, "OnGotFocus", acGroup, acName, &param);
		return;
	}
	//delete param; 
  if (kbId) nEVENT_OnGotFocus = 1;
}
#ifdef CLASS
	CLASS::EVENT_OnGotFocus();
#endif  
 }
void EVENT_OnLostFocus(){ 
  if (nEVENT_OnLostFocus != 1){
	static QList<int> param;;
	
  if ((nEVENT_OnLostFocus == 2) || (nEVENT_OnLostFocus == 0 && myInterpreter && myInterpreter->hasEvent(kbScope, kbId, "OnLostFocus", acGroup, acName, &param))){
    nEVENT_OnLostFocus = 2;
		EventSource = this; myInterpreter->callEvent(kbScope, kbId, "OnLostFocus", acGroup, acName, &param);
		return;
	}
	//delete param; 
  if (kbId) nEVENT_OnLostFocus = 1;
}
#ifdef CLASS
		CLASS::EVENT_OnLostFocus();
#endif  
 }
void EVENT_OnHide(){ 
  if (nEVENT_OnHide != 1){
	static QList<int> param;;
	
  if ((nEVENT_OnHide == 2) || (nEVENT_OnHide == 0 && myInterpreter && myInterpreter->hasEvent(kbScope, kbId, "OnHide", acGroup, acName, &param))){
    nEVENT_OnHide = 2;
		EventSource = this; myInterpreter->callEvent(kbScope, kbId, "OnHide", acGroup, acName, &param);
		return;
	}
	//delete param; 
  if (kbId) nEVENT_OnHide = 1;
}
#ifdef CLASS
			CLASS::EVENT_OnHide();
#endif  
 }
void EVENT_OnKeyDown(t_integer Key, t_boolean Shift, t_boolean Control, t_boolean Alt){ 
  if (nEVENT_OnKeyDown != 1){
	static QList<int> param;;
  if (kbId && nEVENT_OnKeyDown == 0 && param.count() == 0){ 
	 param.append((pcode__t_integer));  param.append((pcode__t_boolean));  param.append((pcode__t_boolean));  param.append((pcode__t_boolean)); 
  }
  if ((nEVENT_OnKeyDown == 2) || (nEVENT_OnKeyDown == 0 && myInterpreter && myInterpreter->hasEvent(kbScope, kbId, "OnKeyDown", acGroup, acName, &param))){
    nEVENT_OnKeyDown = 2;
		myInterpreter->pushStack(new interpreter_parameter(Key));
		myInterpreter->pushStack(new interpreter_parameter(Shift));
		myInterpreter->pushStack(new interpreter_parameter(Control));
		myInterpreter->pushStack(new interpreter_parameter(Alt));
		EventSource = this; myInterpreter->callEvent(kbScope, kbId, "OnKeyDown", acGroup, acName, &param);
		return;
	}
	//delete param; 
  if (kbId) nEVENT_OnKeyDown = 1;
}
#ifdef CLASS
				CLASS::EVENT_OnKeyDown(Key, Shift, Control, Alt);
#endif  
 }
void EVENT_OnKeyUp(t_integer Key, t_boolean Shift, t_boolean Control, t_boolean Alt){ 
  if (nEVENT_OnKeyUp != 1){
	static QList<int> param;;
  if (kbId && nEVENT_OnKeyUp == 0 && param.count() == 0){ 
	 param.append((pcode__t_integer));  param.append((pcode__t_boolean));  param.append((pcode__t_boolean));  param.append((pcode__t_boolean)); 
  }
  if ((nEVENT_OnKeyUp == 2) || (nEVENT_OnKeyUp == 0 && myInterpreter && myInterpreter->hasEvent(kbScope, kbId, "OnKeyUp", acGroup, acName, &param))){
    nEVENT_OnKeyUp = 2;
		myInterpreter->pushStack(new interpreter_parameter(Key));
		myInterpreter->pushStack(new interpreter_parameter(Shift));
		myInterpreter->pushStack(new interpreter_parameter(Control));
		myInterpreter->pushStack(new interpreter_parameter(Alt));
		EventSource = this; myInterpreter->callEvent(kbScope, kbId, "OnKeyUp", acGroup, acName, &param);
		return;
	}
	//delete param; 
  if (kbId) nEVENT_OnKeyUp = 1;
}
#ifdef CLASS
	CLASS::EVENT_OnKeyUp(Key, Shift, Control, Alt);
#endif  
 }
void EVENT_OnKeyPress(t_integer Key, t_boolean Shift, t_boolean Control, t_boolean Alt){ 
  if (nEVENT_OnKeyPress != 1){
	static QList<int> param;;
  if (kbId && nEVENT_OnKeyPress == 0 && param.count() == 0){ 
	 param.append((pcode__t_integer));  param.append((pcode__t_boolean));  param.append((pcode__t_boolean));  param.append((pcode__t_boolean)); 
  }
  if ((nEVENT_OnKeyPress == 2) || (nEVENT_OnKeyPress == 0 && myInterpreter && myInterpreter->hasEvent(kbScope, kbId, "OnKeyPress", acGroup, acName, &param))){
    nEVENT_OnKeyPress = 2;
		myInterpreter->pushStack(new interpreter_parameter(Key));
		myInterpreter->pushStack(new interpreter_parameter(Shift));
		myInterpreter->pushStack(new interpreter_parameter(Control));
		myInterpreter->pushStack(new interpreter_parameter(Alt));
		EventSource = this; myInterpreter->callEvent(kbScope, kbId, "OnKeyPress", acGroup, acName, &param);
		return;
	}
	//delete param; 
  if (kbId) nEVENT_OnKeyPress = 1;
}
#ifdef CLASS
	CLASS::EVENT_OnKeyPress(Key, Shift, Control, Alt);
#endif  
 }
void EVENT_OnExit(){ 
  if (nEVENT_OnExit != 1){
	static QList<int> param;;
	
  if ((nEVENT_OnExit == 2) || (nEVENT_OnExit == 0 && myInterpreter && myInterpreter->hasEvent(kbScope, kbId, "OnExit", acGroup, acName, &param))){
    nEVENT_OnExit = 2;
		EventSource = this; myInterpreter->callEvent(kbScope, kbId, "OnExit", acGroup, acName, &param);
		return;
	}
	//delete param; 
  if (kbId) nEVENT_OnExit = 1;
}
#ifdef CLASS
	CLASS::EVENT_OnExit();
#endif  
 }
void EVENT_OnDblClick(t_integer X, t_integer Y, t_integer GlobalX, t_integer GlobalY, t_boolean Left, t_boolean Right, t_boolean Mid){ 
  if (nEVENT_OnDblClick != 1){
	static QList<int> param;;
  if (kbId && nEVENT_OnDblClick == 0 && param.count() == 0){ 
	 param.append((pcode__t_integer));  param.append((pcode__t_integer));  param.append((pcode__t_integer));  param.append((pcode__t_integer));  param.append((pcode__t_boolean));  param.append((pcode__t_boolean));  param.append((pcode__t_boolean)); 
  }
  if ((nEVENT_OnDblClick == 2) || (nEVENT_OnDblClick == 0 && myInterpreter && myInterpreter->hasEvent(kbScope, kbId, "OnDblClick", acGroup, acName, &param))){
    nEVENT_OnDblClick = 2;
		myInterpreter->pushStack(new interpreter_parameter(X));
		myInterpreter->pushStack(new interpreter_parameter(Y));
		myInterpreter->pushStack(new interpreter_parameter(GlobalX));
		myInterpreter->pushStack(new interpreter_parameter(GlobalY));
		myInterpreter->pushStack(new interpreter_parameter(Left));
		myInterpreter->pushStack(new interpreter_parameter(Right));
		myInterpreter->pushStack(new interpreter_parameter(Mid));
		EventSource = this; myInterpreter->callEvent(kbScope, kbId, "OnDblClick", acGroup, acName, &param);
		return;
	}
	//delete param; 
  if (kbId) nEVENT_OnDblClick = 1;
}
#ifdef CLASS
	CLASS::EVENT_OnDblClick(X, Y, GlobalX, GlobalY, Left, Right, Mid);
#endif  
 }
void EVENT_OnClick(t_integer X, t_integer Y, t_integer GlobalX, t_integer GlobalY, t_boolean Left, t_boolean Right, t_boolean Mid){ 
  if (nEVENT_OnClick != 1){
	static QList<int> param;;
  if (kbId && nEVENT_OnClick == 0 && param.count() == 0){ 
	 param.append((pcode__t_integer));  param.append((pcode__t_integer));  param.append((pcode__t_integer));  param.append((pcode__t_integer));  param.append((pcode__t_boolean));  param.append((pcode__t_boolean));  param.append((pcode__t_boolean)); 
  }
  if ((nEVENT_OnClick == 2) || (nEVENT_OnClick == 0 && myInterpreter && myInterpreter->hasEvent(kbScope, kbId, "OnClick", acGroup, acName, &param))){
    nEVENT_OnClick = 2;
		myInterpreter->pushStack(new interpreter_parameter(X));
		myInterpreter->pushStack(new interpreter_parameter(Y));
		myInterpreter->pushStack(new interpreter_parameter(GlobalX));
		myInterpreter->pushStack(new interpreter_parameter(GlobalY));
		myInterpreter->pushStack(new interpreter_parameter(Left));
		myInterpreter->pushStack(new interpreter_parameter(Right));
		myInterpreter->pushStack(new interpreter_parameter(Mid));
		EventSource = this; myInterpreter->callEvent(kbScope, kbId, "OnClick", acGroup, acName, &param);
		return;
	}
	//delete param; 
  if (kbId) nEVENT_OnClick = 1;
}
#ifdef CLASS
	CLASS::EVENT_OnClick(X, Y, GlobalX, GlobalY, Left, Right, Mid);
#endif  
 }
void EVENT_OnMouseMove(t_integer X, t_integer Y, t_integer GlobalX, t_integer GlobalY){ 
  if (nEVENT_OnMouseMove != 1){
	static QList<int> param;;
  if (kbId && nEVENT_OnMouseMove == 0 && param.count() == 0){ 
	 param.append((pcode__t_integer));  param.append((pcode__t_integer));  param.append((pcode__t_integer));  param.append((pcode__t_integer)); 
  }
  if ((nEVENT_OnMouseMove == 2) || (nEVENT_OnMouseMove == 0 && myInterpreter && myInterpreter->hasEvent(kbScope, kbId, "OnMouseMove", acGroup, acName, &param))){
    nEVENT_OnMouseMove = 2;
		myInterpreter->pushStack(new interpreter_parameter(X));
		myInterpreter->pushStack(new interpreter_parameter(Y));
		myInterpreter->pushStack(new interpreter_parameter(GlobalX));
		myInterpreter->pushStack(new interpreter_parameter(GlobalY));
		EventSource = this; myInterpreter->callEvent(kbScope, kbId, "OnMouseMove", acGroup, acName, &param);
		return;
	}
	//delete param; 
  if (kbId) nEVENT_OnMouseMove = 1;
}
#ifdef CLASS
	CLASS::EVENT_OnMouseMove(X, Y, GlobalX, GlobalY);
#endif  
 }
void EVENT_OnMouseDown(t_integer X, t_integer Y, t_integer GlobalX, t_integer GlobalY, t_boolean Left, t_boolean Right, t_boolean Mid){ 
  if (nEVENT_OnMouseDown != 1){
	static QList<int> param;;
  if (kbId && nEVENT_OnMouseDown == 0 && param.count() == 0){ 
	 param.append((pcode__t_integer));  param.append((pcode__t_integer));  param.append((pcode__t_integer));  param.append((pcode__t_integer));  param.append((pcode__t_boolean));  param.append((pcode__t_boolean));  param.append((pcode__t_boolean)); 
  }
  if ((nEVENT_OnMouseDown == 2) || (nEVENT_OnMouseDown == 0 && myInterpreter && myInterpreter->hasEvent(kbScope, kbId, "OnMouseDown", acGroup, acName, &param))){
    nEVENT_OnMouseDown = 2;
		myInterpreter->pushStack(new interpreter_parameter(X));
		myInterpreter->pushStack(new interpreter_parameter(Y));
		myInterpreter->pushStack(new interpreter_parameter(GlobalX));
		myInterpreter->pushStack(new interpreter_parameter(GlobalY));
		myInterpreter->pushStack(new interpreter_parameter(Left));
		myInterpreter->pushStack(new interpreter_parameter(Right));
		myInterpreter->pushStack(new interpreter_parameter(Mid));
		EventSource = this; myInterpreter->callEvent(kbScope, kbId, "OnMouseDown", acGroup, acName, &param);
		return;
	}
	//delete param; 
  if (kbId) nEVENT_OnMouseDown = 1;
}
#ifdef CLASS
	CLASS::EVENT_OnMouseDown(X, Y, GlobalX, GlobalY, Left, Right, Mid);
#endif  
 }
void EVENT_OnMouseUp(t_integer X, t_integer Y, t_integer GlobalX, t_integer GlobalY, t_boolean Left, t_boolean Right, t_boolean Mid){ 
  if (nEVENT_OnMouseUp != 1){
	static QList<int> param;;
  if (kbId && nEVENT_OnMouseUp == 0 && param.count() == 0){ 
	 param.append((pcode__t_integer));  param.append((pcode__t_integer));  param.append((pcode__t_integer));  param.append((pcode__t_integer));  param.append((pcode__t_boolean));  param.append((pcode__t_boolean));  param.append((pcode__t_boolean)); 
  }
  if ((nEVENT_OnMouseUp == 2) || (nEVENT_OnMouseUp == 0 && myInterpreter && myInterpreter->hasEvent(kbScope, kbId, "OnMouseUp", acGroup, acName, &param))){
    nEVENT_OnMouseUp = 2;
		myInterpreter->pushStack(new interpreter_parameter(X));
		myInterpreter->pushStack(new interpreter_parameter(Y));
		myInterpreter->pushStack(new interpreter_parameter(GlobalX));
		myInterpreter->pushStack(new interpreter_parameter(GlobalY));
		myInterpreter->pushStack(new interpreter_parameter(Left));
		myInterpreter->pushStack(new interpreter_parameter(Right));
		myInterpreter->pushStack(new interpreter_parameter(Mid));
		EventSource = this; myInterpreter->callEvent(kbScope, kbId, "OnMouseUp", acGroup, acName, &param);
		return;
	}
	//delete param; 
  if (kbId) nEVENT_OnMouseUp = 1;
}
#ifdef CLASS
	CLASS::EVENT_OnMouseUp(X, Y, GlobalX, GlobalY, Left, Right, Mid);
#endif 
 }
void EVENT_OnMove(t_integer X, t_integer Y, t_integer OldX, t_integer OldY){ 
  if (nEVENT_OnMove != 1){
	static QList<int> param;;
  if (kbId && nEVENT_OnMove == 0 && param.count() == 0){ 
	 param.append((pcode__t_integer));  param.append((pcode__t_integer));  param.append((pcode__t_integer));  param.append((pcode__t_integer)); 
  }
  if ((nEVENT_OnMove == 2) || (nEVENT_OnMove == 0 && myInterpreter && myInterpreter->hasEvent(kbScope, kbId, "OnMove", acGroup, acName, &param))){
    nEVENT_OnMove = 2;
		myInterpreter->pushStack(new interpreter_parameter(X));
		myInterpreter->pushStack(new interpreter_parameter(Y));
		myInterpreter->pushStack(new interpreter_parameter(OldX));
		myInterpreter->pushStack(new interpreter_parameter(OldY));
		EventSource = this; myInterpreter->callEvent(kbScope, kbId, "OnMove", acGroup, acName, &param);
		return;
	}
	//delete param; 
  if (kbId) nEVENT_OnMove = 1;
}
#ifdef CLASS
	CLASS::EVENT_OnMove(X, Y, OldX, OldY);
#endif 
 }




void EVENT_OnResize(t_integer Width, t_integer Height, t_integer OldWidth, t_integer OldHeight){ 
  if (nEVENT_OnResize != 1){
	static QList<int> param;;
  if (kbId && nEVENT_OnResize == 0 && param.count() == 0){ 
	 param.append((pcode__t_integer));  param.append((pcode__t_integer));  param.append((pcode__t_integer));  param.append((pcode__t_integer)); 
  }
  if ((nEVENT_OnResize == 2) || (nEVENT_OnResize == 0 && myInterpreter && myInterpreter->hasEvent(kbScope, kbId, "OnResize", acGroup, acName, &param))){
    nEVENT_OnResize = 2;
		myInterpreter->pushStack(new interpreter_parameter(Width));
		myInterpreter->pushStack(new interpreter_parameter(Height));
		myInterpreter->pushStack(new interpreter_parameter(OldWidth));
		myInterpreter->pushStack(new interpreter_parameter(OldHeight));
		EventSource = this; myInterpreter->callEvent(kbScope, kbId, "OnResize", acGroup, acName, &param);
		return;
	}
	//delete param; 
  if (kbId) nEVENT_OnResize = 1;
}
#ifdef CLASS
	CLASS::EVENT_OnResize(Width, Height, OldWidth, OldHeight);
#endif 
 }
void EVENT_OnShow(){ 
  if (nEVENT_OnShow != 1){
	static QList<int> param;;
	
  if ((nEVENT_OnShow == 2) || (nEVENT_OnShow == 0 && myInterpreter && myInterpreter->hasEvent(kbScope, kbId, "OnShow", acGroup, acName, &param))){
    nEVENT_OnShow = 2;
		EventSource = this; myInterpreter->callEvent(kbScope, kbId, "OnShow", acGroup, acName, &param);
		return;
	}
	//delete param; 
  if (kbId) nEVENT_OnShow = 1;
}
#ifdef CLASS
	CLASS::EVENT_OnShow();
#endif 
 }
void EVENT_OnMouseWheel(t_integer X, t_integer Y, t_integer GlobalX, t_integer GlobalY){ 
  if (nEVENT_OnMouseWheel != 1){
	static QList<int> param;;
  if (kbId && nEVENT_OnMouseWheel == 0 && param.count() == 0){ 
	 param.append((pcode__t_integer));  param.append((pcode__t_integer));  param.append((pcode__t_integer));  param.append((pcode__t_integer)); 
  }
  if ((nEVENT_OnMouseWheel == 2) || (nEVENT_OnMouseWheel == 0 && myInterpreter && myInterpreter->hasEvent(kbScope, kbId, "OnMouseWheel", acGroup, acName, &param))){
    nEVENT_OnMouseWheel = 2;
		myInterpreter->pushStack(new interpreter_parameter(X));
		myInterpreter->pushStack(new interpreter_parameter(Y));
		myInterpreter->pushStack(new interpreter_parameter(GlobalX));
		myInterpreter->pushStack(new interpreter_parameter(GlobalY));
		EventSource = this; myInterpreter->callEvent(kbScope, kbId, "OnMouseWheel", acGroup, acName, &param);
		return;
	}
	//delete param; 
  if (kbId) nEVENT_OnMouseWheel = 1;
}
#ifdef CLASS
	CLASS::EVENT_OnMouseWheel(X, Y, GlobalX, GlobalY);
#endif 
 }
void EVENT_OnTimer(){ 
  if (nEVENT_OnTimer != 1){
	static QList<int> param;;
	
  if ((nEVENT_OnTimer == 2) || (nEVENT_OnTimer == 0 && myInterpreter && myInterpreter->hasEvent(kbScope, kbId, "OnTimer", acGroup, acName, &param))){
    nEVENT_OnTimer = 2;
		EventSource = this; myInterpreter->callEvent(kbScope, kbId, "OnTimer", acGroup, acName, &param);
		return;
	}
	//delete param; 
  if (kbId) nEVENT_OnTimer = 1;
}
#ifdef CLASS
	CLASS::EVENT_OnTimer();
#endif 
 }
void EVENT_OnPrint(){ 
  if (nEVENT_OnPrint != 1){
	static QList<int> param;;
	
  if ((nEVENT_OnPrint == 2) || (nEVENT_OnPrint == 0 && myInterpreter && myInterpreter->hasEvent(kbScope, kbId, "OnPrint", acGroup, acName, &param))){
    nEVENT_OnPrint = 2;
		EventSource = this; myInterpreter->callEvent(kbScope, kbId, "OnPrint", acGroup, acName, &param);
		return;
	}
	//delete param; 
  if (kbId) nEVENT_OnPrint = 1;
}
#ifdef CLASS
	CLASS::EVENT_OnPrint();
#endif 
 }

 