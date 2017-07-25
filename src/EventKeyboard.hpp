#ifndef CNBIDRAW_EVENT_KEYBOARD_HPP
#define CNBIDRAW_EVENT_KEYBOARD_HPP

#include <drawtk.h>
#include <dtk_event.h>

namespace cnbi {
	namespace draw {

/*! \brief EventKeyboard class
 * 
 * This class wraps a keyboard event and provides some useful methods to
 * interact with it.
 *
 * \sa Events, EventMouse
 */
class EventKeyboard {
	
	public:
		/*! \brief Constructor
		 */
		EventKeyboard(void);
		
		/*! \brief Destructor
		 */
		virtual ~EventKeyboard(void);

		/*! \brief Set the keyboard event
		 *
		 * It stores the keyboard event associated to the given window in the
		 * class.
		 *
		 * \param	win		Current window
		 * \param	event	Keyboard event
		 */
		void Set(const dtk_hwnd& win, const dtk_event* event);
		
		/*! \brief Check if a keyboard event is set
		 *
		 * It checks if a keyboard event has been set.
		 *
		 * \return True if the event is set, false otherwise
		 */
		bool IsSet(void);
		
		/*! \brief Check if a key is pressed
		 *
		 * It checks if the given key is pressed
		 *
		 * \param key	Value of the key
		 *
		 * \return True if the key is pressed, false otherwise
		 */
		bool IsPressed(unsigned int key);
		
		/*! \brief Get the key 
		 *
		 * It gets the key associated to the keyboard event just occured.
		 *
		 * \param[out] key	Key pressed
		 * \param[out] mod	Key pressed modifier
		 */
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
