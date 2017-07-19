#ifndef CNBIDRAW_WINDOW_HPP
#define CNBIDRAW_WINDOW_HPP

#include <string>
#include <drawtk.h>
#include <cnbicore/CcBasic.hpp>

#include "Flags.hpp"

namespace cnbi {
	namespace draw {

class Window {

	public:
		Window(void);
		Window(unsigned int width, unsigned int height, std::string caption, 
			   unsigned int x, unsigned int y, unsigned int bpp);
		virtual ~Window(void);

		void OpenWindow(void);
		void MakeCurrentWindow(void);
		void CloseWindow(void);

		void SetCaption(const std::string& caption);
		void SetGeometry(unsigned int width, unsigned int height);
		void SetPosition(unsigned int x, unsigned int y);
		void SetBpp(unsigned int bpp);

		void GetCaption(std::string* caption);
		void GetGeometry(unsigned int* width, unsigned int* height);
		void GetPosition(unsigned int* x, unsigned int* y);
		void GetBpp(unsigned int* bpp);

		void WaitWindow(void);
		void PostWindow(void);
		dtk_hwnd GetWindowPtr(void);

	private:
		dtk_hwnd 		win_ptr_;
		std::string		win_caption_;
		unsigned int 	win_width_;
		unsigned int 	win_height_;
		unsigned int 	win_x_;
		unsigned int 	win_y_;
		unsigned int 	win_bpp_;

		CcSemaphore 	win_sem_;
};

	}
}

#endif
