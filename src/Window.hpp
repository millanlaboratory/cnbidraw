#ifndef CNBIDRAW_WINDOW_HPP
#define CNBIDRAW_WINDOW_HPP

#include <string>
#include <string.h>
#include <drawtk.h>
#include <dtk_event.h>
#include <mutex>

#include "Flags.hpp"

namespace cnbi {
	namespace draw {

/*! \brief Window class
 *
 * The class implements a window object and the related functionalities. The
 * class is thread-safe. drawtk legacy: the window's coordinates are defined as
 * follow:
 *
 *	- Left-Top coordinates:		(-r, 1)
 *	- Rigth-Top coordinates:		(r, 1)
 *	- Left-Bottom coordinates:		(-r, -1)
 *	- Right-Bottom coordinates:	(r, -1)
 *	- Center coordinates:		(0, 0)
 *
 * where \f$r\f$ is the ratio between the window sizes, defined as: \f$ r=\frac{BigDim}{SmallDim} \f$ in pixel
 *
 */
class Window {

    public:
		/*! \brief Constructor
		 *
		 * Simple constructor. Window's parameters can be set after the object
		 * instanciation (but before calling OpenWindow()), by the class
		 * methods (e.g., SetCaption());
		 */
		Window(void);
		
		/*! \brief Constructor
		 *
		 * Arguments width and height can be set to 0 and 0, to create a
		 * fullsize window.
		 *
		 * \param	width	Window's width
		 * \param	height	Window's height
		 * \param	caption	Window's title
		 * \param	x		Window's x-position
		 * \param	y		Window's y-position
		 * \param	bpp		Window's bits per pixel
		 */
		Window(unsigned int width, unsigned int height, std::string caption, 
		       unsigned int x, unsigned int y, unsigned int bpp);
		
		/*! \brief Destructor
		 */
		virtual ~Window(void);
		
		/*! \brief Open window method
		 *
		 * It created and opens a new window and it makes the window current.
		 */
		void OpenWindow(void);
		
		/*! \brief Close window method
		 *
		 * It closes the current window.
		 */
		void CloseWindow(void);
		
		/*! \brief Clear window method
		 *
		 * It clears the screen (window).
		 */
		void ClearWindow(void);
		
		/*! \brief Update window method
		 *
		 * It updates the screen (window).
		 */
		void UpdateWindow(void);
		
		/*! \brief Make current window method
		 *
		 * It makes the window current.
		 */
		void MakeCurrentWindow(void);
		
		/*! \brief Check if the window is valid
		 *
		 * It checks if the window is valid (open and/or different from nullptr).
		 * \return True if the window is valid, false otherwise
		 */
		bool IsValidWindow(void);

		/*! \brief Set the current window title
		 *
		 * It sets the current window title. This method works only before
		 * calling OpenWindow()
		 * 
		 * \param	caption		Window's title
		 */
		void SetCaption(const std::string& caption);
		
		/*! \brief Set the current window geometry 
		 *
		 * It sets the current window geometry (width and height). 
		 * This method works only before calling OpenWindow()
		 * 
		 * \param	width		Window's width
		 * \param	height		Window's height
		 */
		void SetGeometry(unsigned int width, unsigned int height);
		
		/*! \brief Set the current window position
		 *
		 * It sets the current window position (x and y). 
		 * This method works only before calling OpenWindow()
		 * 
		 * \param	x		Window's x-position
		 * \param	y		Window's y-position
		 */
		void SetPosition(unsigned int x, unsigned int y);
		
		/*! \brief Set the current window bits per pixel
		 *
		 * It sets the current window bit per pixel value. 
		 * This method works only before calling OpenWindow()
		 * 
		 * \param	bpp		Window's bit per pixel
		 */
		void SetBpp(unsigned int bpp);
		
		/*! \brief Get the current window title
		 *
		 * It gets the current window title.
		 *
		 * \param[out]	caption	Window's title
		 */
		void GetCaption(std::string* caption);
		
		/*! \brief Get the current window geometry
		 *
		 * It gets the current window geometry.
		 *
		 * \param[out]	width	Window's width
		 * \param[out]	height	Window's height
		 */
		void GetGeometry(unsigned int* width, unsigned int* height);
		
		/*! \brief Get the current window position
		 *
		 * It gets the current window position.
		 *
		 * \param[out]	x	Window's x-position
		 * \param[out]	y	Window's y-poistion
		 */
		void GetPosition(unsigned int* x, unsigned int* y);
		
		/*! \brief Get the current window bit per pixel
		 *
		 * It gets the current window bit per pixel value.
		 *
		 * \param[out]	bpp	Window's bit per pixel value
		 */
		void GetBpp(unsigned int* bpp);

		/*! \brief Set the event handler
		 *
		 * It sets the event handler function for the current window
		 *
		 * \param	handler	Handler function for the current window
		 */
		void SetEventHandler(DTKEvtProc handler);
		
		/*! \brief Process window's events
		 *
		 * It processes the events related to the current window
		 */
		void ProcessEvents(void);

	    
    private:
		dtk_hwnd		win_ptr_;
		std::string		win_caption_;
		unsigned int	win_width_;
		unsigned int	win_height_;
		unsigned int	win_x_;
		unsigned int	win_y_;
		unsigned int	win_bpp_;
    	
		std::mutex		win_mutex_;
};

	}
}

#endif
