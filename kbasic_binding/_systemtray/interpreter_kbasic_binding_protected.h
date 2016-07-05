/*
void EVENT_OnEvent(){ 
  CLASS::EVENT_OnEvent(); 
	QList<int> *param = new QList<int>; 
	
  if (myInterpreter && myInterpreter->hasEvent(kbScope, kbId, "OnEvent", acGroup, acName, param)){
		EventSource = this; myInterpreter->callEvent(kbScope, kbId, "OnEvent", acGroup, acName, param);
		delete param; return;
	}
  
	delete param;

	//CLASS::EVENT_OnEvent(); 
 }
*/