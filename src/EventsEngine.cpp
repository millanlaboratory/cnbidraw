#ifndef CNBIDRAW_EVENTS_HANDLER_CPP
#define CNBIDRAW_EVENTS_HANDLER_CPP

#include "EventsEngine.hpp"

namespace cnbi {
	namespace draw {

int 		EventType;    
dtk_keyevent	EventKeyboard;
dtk_mouseevent	EventMouse;

EventsEngine::EventsEngine(Window* win) {
	this->win_ = win;
	this->OnQuit   = nullptr;
	this->OnRedraw = nullptr;
}

EventsEngine::~EventsEngine(void) {}


int event_handler(dtk_hwnd wnd, int type, const union dtk_event* evt) {
    EventType = type;
    switch(type) {
    	case DTK_EVT_QUIT:
    	    break;
    	case DTK_EVT_REDRAW:
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

void EventsEngine::Main(void) {

    bool acquired;
    bool once = true;

    while(this->IsRunning()) { 
	this->win_->WaitWindow();
	acquired = (this->win_->GetWindowPtr() != nullptr);
	this->win_->PostWindow();

	if(acquired){
	    printf("Acquired window\n");
	    break;
	}
	
	if(once == true){
	    printf("Waiting for engine\n");
	    once = false;
	}
    }

    dtk_set_event_handler(this->win_->GetWindowPtr(), event_handler);

    while(this->IsRunning()) {
	this->win_->WaitWindow();
	dtk_process_events(this->win_->GetWindowPtr());
	this->win_->PostWindow();


	switch(EventType) {
	    case DTK_EVT_QUIT:
		if(this->OnQuit != nullptr)
		    this->OnQuit();
		break;
	    case DTK_EVT_REDRAW:
		if(this->OnRedraw != nullptr)
		    this->OnRedraw();
		break;
	    default:
		break;
	}

	CcTime::Sleep(50.0f);
    }
}

	}
}

#endif
