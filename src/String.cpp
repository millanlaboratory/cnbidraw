#ifndef CNBIDRAW_STRING_CPP
#define CNBIDRAW_STRING_CPP

#include "String.hpp"

namespace cnbi {
	namespace draw {

String::String(const std::string& text, float size, const float* color) : Shape() {
	this->height_	= 0.0;
	this->width_  	= 0.0f;

	/**** String initialization ****/
	this->text_     = text;
	this->size_		= size;
	this->align_	= CNBIDRAW_STRING_DEFAULT_ALIGN;
	this->font_		= nullptr;
	
	/**** Fill initialization ****/
	this->fill_color_[0] = color[0];
	this->fill_color_[1] = color[1];
	this->fill_color_[2] = color[2];
	this->fill_color_[3] = color[3];
}

String::String(float size, const float* color) {
	this->height_	= 0.0;
	this->width_  	= 0.0f;
	
	/**** String initialization ****/
	this->text_     = "";
	this->size_		= size;
	this->align_	= CNBIDRAW_STRING_DEFAULT_ALIGN;
	this->font_		= nullptr;
	
	/**** Fill initialization ****/
	this->fill_color_[0] = color[0];
	this->fill_color_[1] = color[1];
	this->fill_color_[2] = color[2];
	this->fill_color_[3] = color[3];

}


String::~String(void) {}

bool String::SetFont(Font* font) {

	bool retcod = true;

	this->font_ = font;

	if(this->font_ == nullptr) 
		retcod = false;

	// Create shape
	this->Create();

	return retcod;
}

void String::SetText(const std::string& text) {
	
	this->shp_mutex_.lock();
	this->text_ = text;
	this->shp_mutex_.unlock();
	
	// Create shape
	this->Create();
}

void String::SetAlign(unsigned int align) {
	this->shp_mutex_.lock();
	this->align_ = align;
	this->shp_mutex_.unlock();

	// Create shape
	this->Create();
}

void String::SetSize(float size) {
	this->shp_mutex_.lock();
	this->size_ = size;
	this->shp_mutex_.unlock();
	
	// Create shape
	this->Create();
}

void String::CreateFill(void) {

	std::lock_guard<std::mutex> lock(this->shp_mutex_);
	if(this->font_ != nullptr) {
		this->fill_ptr_ = dtk_create_string(this->fill_ptr_, 
										   this->text_.c_str(), this->size_,
										   this->orig_x_, this->orig_y_, 
										   this->align_, this->fill_color_, 
										   this->font_->font_);
	}

}

void String::CreateStroke(void) {
	std::lock_guard<std::mutex> lock(this->shp_mutex_);
	this->strk_ptr_ = nullptr;
}

	}
}

#endif
