

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

void EVENT_OnEvent(){ 
  if (nEVENT_OnEvent != 1){
	QList<int> *param = new QList<int>; 
	
  if ((nEVENT_OnEvent == 2) || (nEVENT_OnEvent == 0 && myInterpreter && myInterpreter->hasEvent(kbScope, kbId, "OnEvent", acGroup, acName, param))){
    nEVENT_OnEvent = 2;
		EventSource = this; myInterpreter->callEvent(kbScope, kbId, "OnEvent", acGroup, acName, param);
		delete param; return;
	}
  
	delete param;
  if (kbId) nEVENT_OnEvent = 1;
}
	CLASS::EVENT_OnEvent(); 
 }


void EVENT_OnOpen(){ 
  if (nEVENT_OnOpen != 1){
	QList<int> *param = new QList<int>; 
	
  if ((nEVENT_OnOpen == 2) || (nEVENT_OnOpen == 0 && myInterpreter && myInterpreter->hasEvent(kbScope, kbId, "OnOpen", acGroup, acName, param))){
    nEVENT_OnOpen = 2;
		EventSource = this; myInterpreter->callEvent(kbScope, kbId, "OnOpen", acGroup, acName, param);
		delete param; return;
	}
  
	delete param;
  if (kbId) nEVENT_OnOpen = 1;
}
//	CLASS::EVENT_OnOpen(); 
 }


void EVENT_OnClose(){ 
  if (nEVENT_OnClose != 1){
	QList<int> *param = new QList<int>; 
	
  if ((nEVENT_OnClose == 2) || (nEVENT_OnClose == 0 && myInterpreter && myInterpreter->hasEvent(kbScope, kbId, "OnClose", acGroup, acName, param))){
    nEVENT_OnClose = 2;
		EventSource = this; myInterpreter->callEvent(kbScope, kbId, "OnClose", acGroup, acName, param);
		delete param; return;
	}
  
	delete param;
  if (kbId) nEVENT_OnClose = 1;
}
	//CLASS::EVENT_OnClose(); 
 }


int nEVENT_OnEvent;
int nEVENT_OnOpen;
int nEVENT_OnClose;


int nEVENT_OnSingleShot;
int nEVENT_OnEnabled;
int nEVENT_OnDisabled;


void initEvent()
{  
  nEVENT_OnEvent = 0;
  nEVENT_OnOpen = 0;
  nEVENT_OnClose = 0;

  nEVENT_OnSingleShot = 0;
  nEVENT_OnEnabled = 0;
  nEVENT_OnDisabled = 0;

}

