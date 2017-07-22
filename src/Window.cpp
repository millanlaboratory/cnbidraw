#ifndef CNBIDRAW_WINDOW_CPP
#define CNBIDRAW_WINDOW_CPP

#include "Window.hpp"

namespace cnbi {
	namespace draw {

Window::Window(void) {
	this->win_caption_ = CNBIDRAW_WINDOW_DEFAULT_CAPTION;
	this->win_width_   = CNBIDRAW_WINDOW_DEFAULT_WIDTH;
	this->win_height_  = CNBIDRAW_WINDOW_DEFAULT_HEIGHT;
	this->win_x_ 	   = CNBIDRAW_WINDOW_DEFAULT_X;
	this->win_y_ 	   = CNBIDRAW_WINDOW_DEFAULT_Y;
	this->win_bpp_ 	   = CNBIDRAW_WINDOW_DEFAULT_BPP;
	this->win_ptr_	   = nullptr;
}

Window::Window(unsigned int width, unsigned int height, std::string caption, 
			   unsigned int x, unsigned int y, unsigned int bpp) {
	this->win_caption_ = caption; 
	this->win_width_   = width;
	this->win_height_  = height;
	this->win_x_ 	   = x;
	this->win_y_ 	   = y;
	this->win_bpp_ 	   = bpp;
	this->win_ptr_	   = nullptr;
}

Window::~Window(void) {
	if(this->win_ptr_ != nullptr)
		this->CloseWindow();
}

void Window::SetCaption(const std::string& caption) {
	this->win_caption_ = caption;
}

void Window::SetGeometry(unsigned int width, unsigned int height) {
	this->win_width_  = width;
	this->win_height_ = height;
}

void Window::SetPosition(unsigned int x, unsigned int y) {
	this->win_x_ = x;
	this->win_y_ = y;
}

void Window::SetBpp(unsigned int bpp) {
	this->win_bpp_ = bpp;
}

void Window::GetCaption(std::string* caption) {
	caption = &(this->win_caption_);
}

void Window::GetGeometry(unsigned int* width, unsigned int* height) {
	width  = &(this->win_width_);
	height = &(this->win_height_);
}

void Window::GetPosition(unsigned int* x, unsigned int* y) {
	x = &(this->win_x_);
	y = &(this->win_y_);
}

void Window::GetBpp(unsigned int* bpp) {
	bpp = &(this->win_bpp_);
}

dtk_hwnd Window::GetWindowPtr(void) {
    return this->win_ptr_;
}

void Window::OpenWindow(void) {
	this->win_sem_.Wait();
	this->win_ptr_ = dtk_create_window(this->win_width_, this->win_height_, this->win_x_, 
						this->win_y_, this->win_bpp_, this->win_caption_.c_str());
	dtk_make_current_window(this->win_ptr_);
	this->win_sem_.Post();
}

void Window::CloseWindow(void) {
	this->win_sem_.Wait();
	dtk_close(this->win_ptr_);
	this->win_ptr_ = nullptr;
	this->win_sem_.Post();
}

void Window::MakeCurrentWindow(void) {
	this->win_sem_.Wait();
	dtk_make_current_window(this->win_ptr_);
	this->win_sem_.Post();
}

void Window::WaitWindow(void) {
	this->win_sem_.Wait();
}

void Window::PostWindow(void) {
	this->win_sem_.Post();
}

	}
}
#endif
