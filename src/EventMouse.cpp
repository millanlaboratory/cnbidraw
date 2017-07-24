#ifndef CNBIDRAW_EVENT_MOUSE_CPP
#define CNBIDRAW_EVENT_MOUSE_CPP

#include "EventMouse.hpp"

namespace cnbi {
	namespace draw {

EventMouse::EventMouse(void) {
	this->x_	  = 0;
	this->y_	  = 0;
	this->button_ = 0;
	this->state_  = 0;
	this->win_    = nullptr;
	this->is_set_ = 0;
}

EventMouse::~EventMouse(void) {}

void EventMouse::Set(const dtk_hwnd& win, const dtk_event* event) {
	this->x_	  = event->mouse.x;
	this->y_	  = event->mouse.y;
	this->button_ = event->mouse.button;
	this->state_  = event->mouse.state;
	this->win_    = win; 
	this->is_set_ = true;
}

bool EventMouse::IsSet(void) {
	return this->is_set_;
}

bool EventMouse::IsPressed(unsigned int id_button) {
	return (button_ == id_button) & state_ == 1;
}

void EventMouse::GetPosition(unsigned int* x, unsigned int* y) {
	*x = this->x_;
	*y = this->y_;
}

void EventMouse::GetCoordinates(float* x, float* y) {

	unsigned int wwidth, wheight;
	unsigned int minpx_x, minpx_y, maxpx_x, maxpx_y;
	float minrg_x, minrg_y, maxrg_x, maxrg_y;
	float screen_ratio;

	dtk_window_getsize(this->win_, &wwidth, &wheight);

	screen_ratio = float(wwidth)/float(wheight);

	minpx_x = 0;
	maxpx_x = wwidth;
	minpx_y = 0;
	maxpx_y = wheight;

	minrg_x = -1;
	maxrg_x =  1;
	minrg_y = -1;
	maxrg_y =  1;

    if(screen_ratio > 1.0f) {
		minrg_x = minrg_x*screen_ratio;
    	maxrg_x = maxrg_x*screen_ratio;
    } else {
		minrg_y = minrg_y/screen_ratio;
    	maxrg_y = maxrg_y/screen_ratio;
    }
    
	*x =   (maxrg_x-minrg_x)*(this->x_-minpx_x)/(maxpx_x-minpx_x) + minrg_x;
    *y = -((maxrg_y-minrg_y)*(this->y_-minpx_y)/(maxpx_y-minpx_y) + minrg_y);
}


	}
}

#endif
