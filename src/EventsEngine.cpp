#ifndef CNBIDRAW_EVENTS_HANDLER_CPP
#define CNBIDRAW_EVENTS_HANDLER_CPP

#include "EventsEngine.hpp"

namespace cnbi {
	namespace draw {

int 		EventType;    
dtk_keyevent	EventKeyboard;
dtk_mouseevent	EventMouse;

EventsEngine::EventsEngine(Engine* engine) {
	this->engine_  = engine;
	this->onQuit   = nullptr;
	this->onRedraw = nullptr;
}

EventsEngine::~EventsEngine(void) {
    int ret;
    this->Close();
    ret = this->Join();
    printf("[events] - Return of Join: %d\n", ret);
}

void EventsEngine::Open(void) {
    if(this->IsRunning() == false)
	this->Start();
}

void EventsEngine::Close(void) {
    if(this->IsRunning()) {
	this->Stop();
    }

}

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
	this->engine_->WaitWindow();
	acquired = (this->engine_->GetWindowPtr() != nullptr);
	this->engine_->PostWindow();

	if(acquired){
	    printf("Acquired window\n");
	    break;
	}
	
	if(once == true){
	    printf("Waiting for engine\n");
	    once = false;
	}
    }

    dtk_set_event_handler(this->engine_->GetWindowPtr(), event_handler);

    while(this->IsRunning()) {
	this->engine_->WaitWindow();
	dtk_process_events(this->engine_->GetWindowPtr());
	this->engine_->PostWindow();


	switch(EventType) {
	    case DTK_EVT_QUIT:
		if(this->onQuit != nullptr)
		    this->onQuit();
		this->engine_->WaitWindow();
		this->engine_->Close();
		this->engine_->PostWindow();
		this->Close();
		break;
	    case DTK_EVT_REDRAW:
		if(this->onRedraw != nullptr)
		    this->onRedraw();
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
