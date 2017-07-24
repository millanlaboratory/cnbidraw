#ifndef CNBIDRAW_EVENT_MOUSE_HPP
#define CNBIDRAW_EVENT_MOUSE_HPP

#include <drawtk.h>
#include <dtk_event.h>

namespace cnbi {
	namespace draw {

class EventMouse {
	
	public:
		EventMouse(void);
		virtual ~EventMouse(void);

		void Set(const dtk_hwnd& win, const dtk_event* event);
		bool IsSet(void);
		bool IsPressed(unsigned int id_button_ = 1);
		void GetPosition(unsigned int* x, unsigned int* y);
		void GetCoordinates(float* x, float* y);

	private:
		dtk_hwnd		win_;
		bool			is_set_;
		float			x_;
		float			y_;
		unsigned int	button_;
		unsigned int	state_;
		unsigned int	wwin_;
		unsigned int	hwin_;
};

	}
}

#endif
