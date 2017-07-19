#ifndef CNBIDRAW_RECTANGLE_CPP
#define CNBIDRAW_RECTANGLE_CPP

#include "Rectangle.hpp"

namespace cnbi {
	namespace draw {

Rectangle::Rectangle(float width, float height, const float* color, int filled) {
	this->height_ = height;
	this->width_  = width;
	this->filled_   = filled;	
	this->color_[0] = color[0];
	this->color_[1] = color[1];
	this->color_[2] = color[2];
	this->color_[3] = color[3];
}

Rectangle::~Rectangle(void) {}

void Rectangle::Create(void) {
	this->shp_sem_.Wait();	
	this->shp_ptr_ = dtk_create_rectangle_hw(this->shp_ptr_, this->orig_x_, this->orig_y_, 
			   								 this->height_, this->width_, this->filled_,
											 this->color_);
	this->shp_sem_.Post();	
}

	}
}

#endif

