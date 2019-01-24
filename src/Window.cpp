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
	std::lock_guard<std::mutex> lock(this->win_mutex_);
	this->win_caption_ = caption;
}

void Window::SetGeometry(unsigned int width, unsigned int height) {
	std::lock_guard<std::mutex> lock(this->win_mutex_);
	this->win_width_  = width;
	this->win_height_ = height;
}

void Window::SetPosition(unsigned int x, unsigned int y) {
	std::lock_guard<std::mutex> lock(this->win_mutex_);
	this->win_x_ = x;
	this->win_y_ = y;
}

void Window::SetBpp(unsigned int bpp) {
	std::lock_guard<std::mutex> lock(this->win_mutex_);
	this->win_bpp_ = bpp;
}

void Window::GetCaption(std::string* caption) {
	std::lock_guard<std::mutex> lock(this->win_mutex_);
	caption = &(this->win_caption_);
}

void Window::GetGeometry(unsigned int* width, unsigned int* height) {
	std::lock_guard<std::mutex> lock(this->win_mutex_);
	width  = &(this->win_width_);
	height = &(this->win_height_);
}

void Window::GetPosition(unsigned int* x, unsigned int* y) {
	std::lock_guard<std::mutex> lock(this->win_mutex_);
	x = &(this->win_x_);
	y = &(this->win_y_);
}

void Window::GetBpp(unsigned int* bpp) {
	std::lock_guard<std::mutex> lock(this->win_mutex_);
	bpp = &(this->win_bpp_);
}


void Window::OpenWindow(void) {
	std::lock_guard<std::mutex> lock(this->win_mutex_);
	this->win_ptr_ = dtk_create_window(this->win_width_, this->win_height_, this->win_x_, 
						this->win_y_, this->win_bpp_, this->win_caption_.c_str());
	dtk_make_current_window(this->win_ptr_);
}

void Window::CloseWindow(void) {
	std::lock_guard<std::mutex> lock(this->win_mutex_);
	dtk_close(this->win_ptr_);
	this->win_ptr_ = nullptr;
}

void Window::MakeCurrentWindow(void) {
	std::lock_guard<std::mutex> lock(this->win_mutex_);
	dtk_make_current_window(this->win_ptr_);
}

void Window::ClearWindow(void) {
	std::lock_guard<std::mutex> lock(this->win_mutex_);
	dtk_clear_screen(this->win_ptr_);
}

void Window::UpdateWindow(void) {
	std::lock_guard<std::mutex> lock(this->win_mutex_);
	dtk_update_screen(this->win_ptr_);
}

bool Window::IsValidWindow(void) {
	bool retcod = true;
	std::lock_guard<std::mutex> lock(this->win_mutex_);
	if(this->win_ptr_ == nullptr)
		retcod = false;
	return retcod;
}

void Window::SetEventHandler(DTKEvtProc handler) {
	std::lock_guard<std::mutex> lock(this->win_mutex_);
	dtk_set_event_handler(this->win_ptr_, handler);
}

void Window::ProcessEvents(void) {
	std::lock_guard<std::mutex> lock(this->win_mutex_);
	dtk_process_events(this->win_ptr_);
}

	}
}
#endif
