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


int nEVENT_OnEvent;


void initEvent()
{  
  nEVENT_OnEvent = 0;


}



