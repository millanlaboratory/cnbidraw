#ifndef CNBIDRAW_STRING_CPP
#define CNBIDRAW_STRING_CPP

#include "String.hpp"

namespace cnbi {
	namespace draw {

String::String(const std::string& text, float size, const float* color) {
	this->height_	  = 0.0;
	this->width_  	  = 0.0f;
	this->filled_	  = 1;	
	this->color_[0]   = color[0];
	this->color_[1]   = color[1];
	this->color_[2]   = color[2];
	this->color_[3]   = color[3];
	this->str_text_   = text;
	this->str_size_   = size;
	this->str_format_ = CNBIDRAW_STRING_DEFAULT_FORMAT;
	this->str_align_  = CNBIDRAW_STRING_DEFAULT_ALIGN;
	this->str_font_	  = nullptr;
}

String::~String(void) {
	this->shp_sem_.Wait();
	if(this->str_font_ != nullptr)
		dtk_destroy_font(this->str_font_);
	this->shp_sem_.Post();
}

bool String::SetFormat(const std::string& format) {

	bool retcod = false;	
	
	this->shp_sem_.Wait();
	if(this->str_font_ != nullptr)
		dtk_destroy_font(this->str_font_);

	this->str_font_ = dtk_load_font(format.c_str());

	if(this->str_font_ != nullptr)
		retcod = true;
	this->shp_sem_.Post();

	this->Create();
	
	return retcod;
}

void String::SetAlign(unsigned int align) {
	this->shp_sem_.Wait();
	this->str_align_ = align;
	this->shp_sem_.Post();
	
	this->Create();
}

void String::SetSize(float size) {
	this->shp_sem_.Wait();
	this->str_size_ = size;
	this->shp_sem_.Post();
	
	this->Create();
}

void String::Create(void) {

	this->shp_sem_.Wait();
	if(this->str_font_ != nullptr) {
		this->shp_ptr_ = dtk_create_string(this->shp_ptr_, 
										   this->str_text_.c_str(), this->str_size_,
										   this->orig_x_, this->orig_y_, 
										   this->str_align_, this->color_, 
										   this->str_font_);
	}
	this->shp_sem_.Post();

}

	}
}

#endif
