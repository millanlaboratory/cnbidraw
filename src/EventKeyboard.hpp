#ifndef CNBIDRAW_EVENT_KEYBOARD_HPP
#define CNBIDRAW_EVENT_KEYBOARD_HPP

#include <drawtk.h>
#include <dtk_event.h>

namespace cnbi {
	namespace draw {

class EventKeyboard {
	
	public:
		EventKeyboard(void);
		virtual ~EventKeyboard(void);

		void Set(const dtk_hwnd& win, const dtk_event* event);
		bool IsSet(void);
		bool IsPressed(unsigned int key);
		void GetKey(unsigned int* key, unsigned int* mod);

	private:
		dtk_hwnd		win_;
		bool			is_set_;
		unsigned int	key_;
		unsigned int	mod_;
		unsigned int	state_;
};

	}
}


#endif
