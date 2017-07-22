#ifndef CNBIDRAW_EVENTS_HANDLER_HPP
#define CNBIDRAW_EVENTS_HANDLER_HPP

#include <stdio.h>

namespace cnbi {
	namespace draw {

class EventsHandler  {

    public:
	EventsHandler(void);
	virtual ~EventsHandler(void);

	virtual void HandleQuit(void);
	virtual void HandleRedraw(void);

	//void Register(
	//template<class T, class U>
	//void Register(U* sender, T* receiver, void *method);
};

//template<class T, class U>
//void EventsHandler::Register(U* sender, T* receiver, void *method) {
//    sender->Register((EventsHandler*)receiver, T::method);
//}

#define RegisterEvents(sender_event, receiver_ptr, method)	\
	sender_event.Register((cnbi::draw::EventsHandler*)receiver_ptr,	    \
			&cnbi::draw::EventsHandler::method);

    }
}

#endif

