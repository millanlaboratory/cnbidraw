#ifndef CNBIDRAW_EVENTS_HPP
#define CNBIDRAW_EVENTS_HPP

#include <functional>
#include <drawtk.h>
#include <dtk_event.h>
#include <cnbicore/CcThread.hpp>

#include "Engine.hpp"
#include "EventMouse.hpp"
#include "EventKeyboard.hpp"

namespace cnbi {
	namespace draw {

typedef int	EventType;

class Events : public CcThread {

    public:
		Events(Engine* engine);
		virtual ~Events(void);

		void Open(void);
		void Close(void);

		std::function<void(void)>			onQuit;
		std::function<void(void)>			onRedraw;
		std::function<void(EventKeyboard*)>	onKeyboard;
		std::function<void(EventMouse*)>	onMouse;
    
    protected:
		void Main(void);
    	       
    private:
		Engine*	engine_;
};

	}
}

#endif

