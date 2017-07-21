#ifndef CNBIDRAW_CROSS_CPP
#define CNBIDRAW_CROSS_CPP

#include "Cross.hpp"

namespace cnbi {
	namespace draw {

Cross::Cross(float size, float thick, const float* color, int filled) {
	this->height_ = size;
	this->width_  = size;
	this->thick_  = thick;
	this->filled_   = filled;	
	this->color_[0] = color[0];
	this->color_[1] = color[1];
	this->color_[2] = color[2];
	this->color_[3] = color[3];
	this->shp_hrect_ = nullptr;
	this->shp_vrect_ = nullptr;
}

Cross::~Cross(void) {}

void Cross::Create(void) {
	this->shp_sem_.Wait();	
	dtk_hshape shps[] = {
		this->shp_hrect_ = dtk_create_rectangle_hw(this->shp_hrect_, 
								this->orig_x_, this->orig_y_, 
								this->width_, this->thick_, this->filled_,
								this->color_), 
		this->shp_vrect_ = dtk_create_rectangle_hw(this->shp_vrect_, 
								this->orig_x_, this->orig_y_, 
			   					this->thick_, this->height_, this->filled_,
								this->color_)
	};
	this->shp_ptr_ = dtk_create_composite_shape(this->shp_ptr_, sizeof(shps)/sizeof(shps[0]), shps, 1);
	this->shp_sem_.Post();	
}

float Cross::GetThick(void) {
	float thick;
	this->shp_sem_.Wait();	
	thick = this->thick_;
	this->shp_sem_.Post();
	return thick;
}



	}
}

#endif

