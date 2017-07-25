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

/*! \brief Events class
 *
 * This class implements a thread taking care of the events occuring to an
 * object Engine. It allows to define callbacks related to the Quit event, the
 * Redraw event, the Keyboard event and the Mouse event.
 * By default, when a Quit event occurs (click on the quit button of the
 * window), the Events class closes and try to close also the Engine object. In
 * addition, when a redraw event occurs, the Events class ask to the Engine for
 * redrawing. In addition, to these standard behaviours, user can defined
 * additional custom behaviors by implementing the provided callbacks. 
 *
 * \sa Engine, EventKeyboard, EventMouse
 */
class Events : public CcThread {

    public:
		/*! \brief Constructor
		 *
		 * Constructor with the pointer to the current engine
		 *
		 * \param engine	Pointer to the engine object
		 */
		Events(Engine* engine);
		
		/*! \brief Destructor
		 */
		virtual ~Events(void);

		/*! \brief Open the events engine
		 *
		 * It opens the events engine and start its main loop.
		 */
		void Open(void);
		
		/*! \brief Close the events engine
		 *
		 * It closes the events engine. Note that it just stops the thread and
		 * it not joins it.
		 */
		void Close(void);

		/*! \brief Callback for Quit event
		 *
		 * Public function to be defined when a Quit event occurs. It will be
		 * executed just before the events engine stops.
		 * It can be defined by means of the std::bind function.
		 * e.g., onQuit = std::bind(simple_callback_quit);
		 *
		 */
		std::function<void(void)>			onQuit;
		
		/*! \brief Callback for Redraw event
		 *
		 * Public function to be defined when a Redraw event occurs. It will be
		 * executed just before the events engine asks for redrawing.
		 * It can be defined by means of the std::bind function.
		 * e.g., onRedraw = std::bind(&Handler::redraw_callback, handler, std::placeholder::_1);
		 *
		 */
		std::function<void(void)>			onRedraw;
		
		/*! \brief Callback for Keyboard event
		 *
		 * Public function to be defined when a Keyboard event occurs.
		 * It can be defined by means of the std::bind function.
		 * e.g., onKeyboard = std::bind(&Handler::keyboard_callback, handler, std::placeholder::_1);
		 *
		 */
		std::function<void(EventKeyboard*)>	onKeyboard;
		
		/*! \brief Callback for Mouse event
		 *
		 * Public function to be defined when a Mouse event occurs.
		 * It can be defined by means of the std::bind function.
		 * e.g., onMouse = std::bind(&Handler::mouse_callback, handler, std::placeholder::_1);
		 *
		 */
		std::function<void(EventMouse*)>	onMouse;
    
    protected:
		void Main(void);
    	       
    private:
		Engine*	engine_;
};

 /*! \example events.cpp
 * Example of the use of the events engine and how to define the callbacks.
 *
 */
	}
}

#endif

