#ifndef CNBIDRAW_EVENT_MOUSE_HPP
#define CNBIDRAW_EVENT_MOUSE_HPP

#include <drawtk.h>
#include <dtk_event.h>

namespace cnbi {
	namespace draw {

/*! \brief EventMouse class
 * 
 * This class wraps a mouse event and provides some useful methods to
 * interact with it.
 *
 * \sa Events, EventKeyboard, Window
 */
class EventMouse {
	
	public:

		/*! \brief Constructor
		 */
		EventMouse(void);
		
		/*! \brief Destructor
		 */
		virtual ~EventMouse(void);

		/*! \brief Set the mouse event
		 *
		 * It stores the mouse event associated to the given window in the
		 * class.
		 *
		 * \param	win		Current window
		 * \param	event	Keyboard event
		 */
		void Set(const dtk_hwnd& win, const dtk_event* event);
		
		/*! \brief Check if a mouse event is set
		 *
		 * It checks if a mouse event has been set.
		 *
		 * \return True if the event is set, false otherwise
		 */
		bool IsSet(void);
		
		/*! \brief Check if a mouse button is pressed
		 *
		 * It checks if the mouse button with the given id is pressed
		 *
		 * \param key	Id of the mouse button [default: 1]
		 *
		 * \return True if the button is pressed, false otherwise
		 */
		bool IsPressed(unsigned int id_button_ = 1);
		
		/*! \brief Get mouse position in pixel
		 *
		 * It gets the current position of the mouse [pixel] inside the current
		 * window.
		 *
		 * \param[out]	x	x-position [pixel]
		 * \param[out]	y	y-position [pixel]
		 */
		void GetPosition(unsigned int* x, unsigned int* y);
		
		/*! \brief Get mouse coordinates
		 *
		 * It gets the current coordinates of the mouse in the window reference
		 * system.
		 *
		 * \param[out]	x	x-coordinate
		 * \param[out]	y	y-coordinate
		 */
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
