#ifndef CNBIDRAW_EVENTS_HANDLER_HPP
#define CNBIDRAW_EVENTS_HANDLER_HPP

#include <drawtk.h>
#include <dtk_event.h>
#include <cnbicore/CcCallback.hpp>
#include <cnbicore/CcThread.hpp>
#include "Window.hpp"

namespace cnbi {
	namespace draw {

class EventsHandler : public CcThread {

	public:
		EventsHandler(Window* win);
		virtual ~EventsHandler(void);

		void Main(void);

	private:
		//int event_handler(dtk_hwnd wnd, int type, const union dtk_event* evt);

	private:
		Window*	win_;
};

	}
}

#endif

