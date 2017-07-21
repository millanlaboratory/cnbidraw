#ifndef CNBIDRAW_EVENTS_HANDLER_CPP
#define CNBIDRAW_EVENTS_HANDLER_CPP

#include "EventsHandler.hpp"

namespace cnbi {
	namespace draw {

EventsHandler::EventsHandler(Window* win) {
	this->win_ = win;
}

EventsHandler::~EventsHandler(void) {}


int event_handler(dtk_hwnd wnd, int type, const union dtk_event* evt) {
	switch(type) {
		case DTK_EVT_QUIT:
			printf("Event quit\n");
			break;
		case DTK_EVT_REDRAW:
			printf("Event redraw\n");
			break;
		case DTK_EVT_KEYBOARD:
			printf("Event keyboard\n");
			break;
		case DTK_EVT_MOUSEBUTTON:
			printf("Event mouse button\n");
		case DTK_EVT_MOUSEMOTION:
			printf("Event mouse motion\n");
			break;
	}
	return 1;


}

void EventsHandler::Main(void) {

	bool acquired;
	bool once = true;

	while(this->IsRunning()) { 
		this->win_->WaitWindow();
		acquired = (this->win_ != nullptr);
		this->win_->PostWindow();

		if(acquired){
			printf("Acquired window\n");
			break;
		}
		if (once){
			printf("Waiting for engine\n");
			once = false;
		}
	}

	dtk_set_event_handler(this->win_->GetWindowPtr(), event_handler);

	while(this->IsRunning()) {
		this->win_->WaitWindow();
		dtk_process_events(this->win_->GetWindowPtr());
		this->win_->PostWindow();
		CcTime::Sleep(50.0f);
	}
}

	}
}

#endif
