#ifndef CNBIDRAW_EVENT_KEYBOARD_CPP
#define CNBIDRAW_EVENT_KEYBOARD_CPP

#include "EventKeyboard.hpp"

namespace cnbi {
	namespace draw {

EventKeyboard::EventKeyboard(void) {
	this->key_	  = 0;
	this->mod_	  = 0;
	this->state_  = 0;
	this->win_    = nullptr;
	this->is_set_ = 0;
}

EventKeyboard::~EventKeyboard(void) {}

void EventKeyboard::Set(const dtk_hwnd& win, const dtk_event* event) {
	this->key_	  = event->key.sym;
	this->mod_	  = event->key.mod;
	this->state_  = event->key.state;
	this->win_    = win; 
	this->is_set_ = true;
}

bool EventKeyboard::IsSet(void) {
	return this->is_set_;
}

bool EventKeyboard::IsPressed(unsigned int key) {
	return (this->key_ == key) & this->state_ == 1;
}

void EventKeyboard::GetKey(unsigned int* key, unsigned int* mod) {
	*key = this->key_;
	*mod = this->mod_;
}

	}
}

#endif
