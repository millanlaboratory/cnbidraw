#ifndef CNBIDRAW_EVENTS_CPP
#define CNBIDRAW_EVENTS_CPP

#include "Events.hpp"

namespace cnbi {
	namespace draw {

EventType		evttype;    
EventKeyboard	evtkeyboard;
EventMouse		evtmouse;

Events::Events(Engine* engine) {
	this->engine_	 = engine;
	this->onQuit   	 = nullptr;
	this->onRedraw 	 = nullptr;
	this->onKeyboard = nullptr;
	this->onMouse	 = nullptr;
}

Events::~Events(void) {
    int ret;
    this->Close();
    ret = this->Join();
    printf("[Events] - Return of Join: %d\n", ret);
}

void Events::Open(void) {
	if(this->IsRunning() == false)
		this->Start();
}

void Events::Close(void) {
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
			evtkeyboard.Set(wnd, evt);
    	    break;
    	case DTK_EVT_MOUSEBUTTON:
    	case DTK_EVT_MOUSEMOTION:
			evtmouse.Set(wnd, evt);
    	    break;
    }
    return 1;
}

void Events::Main(void) {

    bool acquired;
    bool once = true;

    while(this->IsRunning()) { 
		if(acquired = this->engine_->IsValidWindow()) {
		    printf("[Events] - Acquired window\n");
		    break;
		}
		
		if(once == true){
		    printf("[Events] - Waiting for engine\n");
		    once = false;
		}
    }

	this->engine_->SetEventHandler(event_handler);

    while(this->IsRunning()) {
		

		switch(evttype) {
		    case DTK_EVT_QUIT:
				this->engine_->Stop();
			
				if(this->onQuit != nullptr)
					this->onQuit();
		
				this->Stop();
				break;
		    case DTK_EVT_REDRAW:
				//this->engine_->Refresh();
			
				if(this->onRedraw != nullptr)
					this->onRedraw();
				break;
		    case DTK_EVT_KEYBOARD:
				if(this->onKeyboard != nullptr)
					this->onKeyboard(&evtkeyboard);
				break;
		    case DTK_EVT_MOUSEBUTTON:
		    case DTK_EVT_MOUSEMOTION:
				if(this->onMouse != nullptr)
					this->onMouse(&evtmouse);
				break;
		    default:
				break;
		}

		CcTime::Sleep(50.0f);
    }

	this->Close();
}

	}
}

#endif
