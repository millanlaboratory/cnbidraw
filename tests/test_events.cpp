#include "Engine.hpp"
#include "EventsEngine.hpp"
#include "EventsHandler.hpp"

using namespace std::placeholders;

class handler : public cnbi::draw::EventsHandler {
    public:
	void HandleRedraw(void) {
	    printf("redraw\n");
	}
};

void callback_simple_quit(void) {
    printf("quit\n");
}

int main(int argc, char** argv) {

	cnbi::draw::Engine engine;
	cnbi::draw::EventsEngine events(&engine);
	handler hdl;

	events.OnQuit = callback_simple_quit;
	events.OnRedraw = std::bind(&handler::HandleRedraw, hdl);

	//hdl.Register(&(evtengine.i_OnQuit), &hdl, &handler::HandleQuit);
	//RegisterEvents(evtengine.i_OnQuit, handler, HandleQuit);
	//RegisterEvents(evtengine.i_OnRedraw, handler, HandleRedraw);

	engine.Open();
	events.Start();

	
	CcTimeValue tic;
	CcTime::Tic(&tic);
	while(true) {
		
		if(CcTime::Toc(&tic) > 5000)
			break;
		
		CcTime::Sleep(100);
	}

	return 0;
}


