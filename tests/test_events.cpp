#include "Engine.hpp"
#include "EventsEngine.hpp"
#include "EventsHandler.hpp"

using namespace std::placeholders;

class handler : public cnbi::draw::EventsHandler {
    public:
	void HandleRedraw(void) {
	    printf("Redraw from class method\n");
	}
};

void callback_simple_quit(void) {
    printf("Quit from simple function\n");
}

int main(int argc, char** argv) {

	cnbi::draw::Engine engine;
	cnbi::draw::EventsEngine events(&engine);
	handler hdl;

	events.onQuit = callback_simple_quit;
	events.onRedraw = std::bind(&handler::HandleRedraw, hdl);

	//hdl.Register(&(evtengine.i_OnQuit), &hdl, &handler::HandleQuit);
	//RegisterEvents(evtengine.i_OnQuit, handler, HandleQuit);
	//RegisterEvents(evtengine.i_OnRedraw, handler, HandleRedraw);

	engine.Open();
	events.Start();

	
	CcTimeValue tic;
	CcTime::Tic(&tic);
	while(engine.IsRunning() & events.IsRunning()) {
		
		if(CcTime::Toc(&tic) > 10000)
			break;
		
		CcTime::Sleep(100);
	}

	return 0;
}


