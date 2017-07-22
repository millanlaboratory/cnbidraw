#ifndef CNBIDRAW_EVENTS_HANDLER_CPP
#define CNBIDRAW_EVENTS_HANDLER_CPP

#include "EventsEngine.hpp"

namespace cnbi {
	namespace draw {

EventType	evttype;    
EventKeyboard	evtkeyboard;
EventMouse	evtmouse;

EventsEngine::EventsEngine(Engine* engine) {
	this->engine_	 = engine;
	this->onQuit   	 = nullptr;
	this->onRedraw 	 = nullptr;
	this->onKeyboard = nullptr;
	this->onMouse	 = nullptr;
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
    if(this->IsRunning())
	this->Stop();
}

int event_handler(dtk_hwnd wnd, int type, const union dtk_event* evt) {
    evttype = type;
    switch(type) {
    	case DTK_EVT_QUIT:
    	    break;
    	case DTK_EVT_REDRAW:
	   break;
    	case DTK_EVT_KEYBOARD:
	    evtkeyboard.sym   = evt->key.sym;
	    evtkeyboard.state = evt->key.state;
	    evtkeyboard.mod   = evt->key.mod;
    	    break;
    	case DTK_EVT_MOUSEBUTTON:
    	case DTK_EVT_MOUSEMOTION:
	    evtmouse.x	    = evt->mouse.x;
	    evtmouse.y	    = evt->mouse.y;
	    evtmouse.button = evt->mouse.button;
	    evtmouse.state  = evt->mouse.state;
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


	switch(evttype) {
	    case DTK_EVT_QUIT:
		this->engine_->WaitWindow();
		this->engine_->Close();
		this->engine_->PostWindow();
		
		if(this->onQuit != nullptr)
		    this->onQuit();
	
		this->Close();
		break;
	    case DTK_EVT_REDRAW:
		this->engine_->WaitWindow();
		this->engine_->Refresh();
		this->engine_->PostWindow();
		
		if(this->onRedraw != nullptr)
		    this->onRedraw();
		break;
	    case DTK_EVT_KEYBOARD:
		if(this->onKeyboard != nullptr)
		    this->onKeyboard(evtkeyboard);
		break;
	    case DTK_EVT_MOUSEBUTTON:
	    case DTK_EVT_MOUSEMOTION:
		if(this->onMouse != nullptr)
		    this->onMouse(evtmouse);
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
