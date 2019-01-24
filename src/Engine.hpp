#ifndef CNBIDRAW_ENGINE_HPP
#define CNBIDRAW_ENGINE_HPP

#include <drawtk.h>
//#include <cnbicore/CcSemaphore.hpp>
#include <mutex>
#include <cnbicore/CcThread.hpp>

#include "Flags.hpp"
#include "Window.hpp"
#include "Shape.hpp"
#include "ShapeMap.hpp"

namespace cnbi {
   namespace draw {

/*! \brief Engine class
 *
 * This class implements a simple drawing engine to display Shape objects on the
 * screen. Shape objects can be added/removed to/from the engine by means of he
 * provided methods. Events can be handled by means of the class Events. Once
 * the method Engine::Open() is called, the Engine class create a new thread
 * taking care of the drawing. Once opened, the engine will draw all the shapes
 * in the internal shape map. The class derives from the Window and CcThread
 * class, and so it shares their public methods. The class is thread-safe.
 *
 * \sa Shape, Events
 */ 
class Engine : public CcThread, public Window {
    
    public:
		/*! \brief Constructor
		 */
		Engine(void);
		
		/*! \brief Constructor
		 *
		 * Construct with parameters for the window 
		 *
		 * \param caption	Window's title
		 * \param width		Window's width
		 * \param height	Window's height
		 *
		 */
		Engine(const std::string& caption, unsigned int width, unsigned int height);
		
		/*! \brief Destructor
		 */
		virtual ~Engine(void);
		
		/*! \brief Open the window and start the engine
		 *
		 * It opens the window and starts a new thread for the engine.
		 */
		void  Open(void);
		
		/*! \brief Stop the engine
		 *
		 * It closes the window and stop the engine. Note that it just stops the
		 * thread and it not joins it.
		 */
		void  Close(void);
		
		/*! \brief Set the refresh frequency
		 *
		 * It sets the refresh frequency for the internal drawing loop of the
		 * engine.  By default it is sets at CNBIDRAW_ENGINE_DEFAULT_REFRESH.
		 *
		 * \param refresh	Refresh frequency [Hz]
		 */
		void  SetRefresh(float refresh);
		
		/*! \brief Get the refresh frequency
		 *
		 * It gets the current refresh frequency of the internal drawing loop of the engine.
		 *
		 * \return Refresh frequency
		 */
		float GetRefresh(void);
		
		/*! \brief Force the screen refresh
		 *
		 * It forces the screen refresh
		 *
		 * \return Refresh frequency
		 */
		void  Refresh(void);
		
		/*! \brief Add a new shape to the engine
		 *
		 * It adds a new shape to the engine. By default it overwrites a
		 * previous shape with the same name.
		 *
		 * \param	name	Shape's name
		 * \param	shp		Shape's pointer
		 * \param	overwrite	True if a shape with the same name must be
		 * overwritten, false otherwise [default: true]
		 *
		 * \return True if the shape is added to the engine, false otherwise
		 */
		bool Add(const std::string& name, Shape* shp, bool overwrite = true);
		
		/*! \brief Remove a shape from the engine
		 *
		 * It remove a shape identified by name from the engine.
		 *
		 * \param	name	Shape's name
		 *
		 * \return True if the shape is removed from the engine, false otherwise
		 */
		bool Remove(const std::string& name);
		
		/*! \brief Raise up the given shape
		 *
		 * It raises up the position of the shape identified by name.
		 *
		 * \param	name	Shape's name
		 *
		 * \return True if the shape is raised up, false otherwise
		 */
		bool Raise(const std::string& name);
		
		/*! \brief Raise to the top
		 *
		 * It raises to the top the position of the shape identified by name.
		 *
		 * \param	name	Shape's name
		 *
		 * \return True if the shape is raised to the top, false otherwise
		 */
		bool RaiseTop(const std::string& name);
		
		/*! \brief Lower down the given shape
		 *
		 * It lowers down the position of the shape identified by name.
		 *
		 * \param	name	Shape's name
		 *
		 * \return True if the shape is lowered down, false otherwise
		 */
		bool Lower(const std::string& name);
		
		/*! \brief Lower to the bottom
		 *
		 * It lowers to the bottom the position of the shape identified by name.
		 *
		 * \param	name	Shape's name
		 *
		 * \return True if the shape is lowered to the bottom, false otherwise
		 */
		bool LowerBottom(const std::string& name);

		/*! \brief Dump the shapes currently in the engine
		 *
		 */
		void Dump(void);

    protected:
		void Main(void);
		void Render(void);

    private:
		//CcSemaphore shps_sem_;
		//CcSemaphore eng_sem_;
		std::mutex  shps_mutex_;
		std::mutex  eng_mutex_;
		ShapeMap    shps_;
		float	    refresh_;
};

 /*! \example shapes.cpp
 * Example of the use of the engine with several basic shapes provided by the
 * library.
 *
 * \example images.cpp
 * Example of the use of the engine with external images.
 *
 * \example strings.cpp
 * Example of the use of the engine with text strings.
 *
 */
   }
}


#endif
