#ifndef CNBIDRAW_EVENTS_ENGINE_HPP
#define CNBIDRAW_EVENTS_ENGINE_HPP

#include <functional>
#include <drawtk.h>
#include <dtk_event.h>
#include <cnbicore/CcCallback.hpp>
#include <cnbicore/CcThread.hpp>
#include "Engine.hpp"
#include "EventsHandler.hpp"

namespace cnbi {
	namespace draw {


class EventsEngine : public CcThread {

    public:
	EventsEngine(Engine* engine);
	virtual ~EventsEngine(void);

	void Open(void);
	void Close(void);

	std::function<void(void)> onQuit;
	std::function<void(void)> onRedraw;
    
    protected:
	void Main(void);
    	       
    private:
	Engine*	engine_;
};

	}
}

#endif

