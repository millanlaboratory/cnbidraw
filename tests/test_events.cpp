#include "Engine.hpp"
#include "EventsHandler.hpp"


int main(int argc, char** argv) {

	cnbi::draw::Engine engine;
	cnbi::draw::EventsHandler handler(&engine);


	engine.Open();
	handler.Start();

	
	CcTimeValue tic;
	CcTime::Tic(&tic);
	while(true) {
		
		if(CcTime::Toc(&tic) > 5000)
			break;
		
		CcTime::Sleep(100);
	}

	return 0;
}


