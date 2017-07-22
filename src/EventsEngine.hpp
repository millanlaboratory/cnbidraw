#ifndef CNBIDRAW_EVENTS_ENGINE_HPP
#define CNBIDRAW_EVENTS_ENGINE_HPP

#include <functional>
#include <drawtk.h>
#include <dtk_event.h>
#include <cnbicore/CcCallback.hpp>
#include <cnbicore/CcThread.hpp>
#include "Window.hpp"
#include "EventsHandler.hpp"

namespace cnbi {
	namespace draw {


class EventsEngine : public CcThread {

    public:
	EventsEngine(Window* win);
	virtual ~EventsEngine(void);

	std::function<void(void)> OnQuit;
	std::function<void(void)> OnRedraw;
	//CcCallback1<EventsHandler, EventsEngine*> i_OnQuit;
	//CcCallback1<EventsHandler, EventsEngine*> i_OnRedraw;
    protected:
	void Main(void);
    	       
    private:
	Window*	win_;
};

	}
}

#endif

