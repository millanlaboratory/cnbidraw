#ifndef CNBIDRAW_EVENTS_HANDLER_CPP
#define CNBIDRAW_EVENTS_HANDLER_CPP

#include "EventsHandler.hpp"

namespace cnbi {
    namespace draw {

EventsHandler::EventsHandler(void){}
EventsHandler::~EventsHandler(void){}

void EventsHandler::HandleQuit(void) {
    printf("[EventsHandler] - Quit\n");
}

void EventsHandler::HandleRedraw(void) {
    printf("[EventsHandler] - Redraw\n");
}
    }
}

#endif
