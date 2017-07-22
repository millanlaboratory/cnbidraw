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

typedef int			EventType;
typedef struct dtk_keyevent	EventKeyboard;
typedef struct dtk_mouseevent	EventMouse;

class EventsEngine : public CcThread {

    public:
	EventsEngine(Engine* engine);
	virtual ~EventsEngine(void);

	void Open(void);
	void Close(void);

	std::function<void(void)>	    onQuit;
	std::function<void(void)>	    onRedraw;
	std::function<void(EventKeyboard)>  onKeyboard;
	std::function<void(EventMouse)>	    onMouse;
    
    protected:
	void Main(void);
    	       
    private:
	Engine*	engine_;
};

	}
}

#endif

