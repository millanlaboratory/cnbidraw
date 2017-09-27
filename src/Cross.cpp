#ifndef CNBIDRAW_CROSS_CPP
#define CNBIDRAW_CROSS_CPP

#include "Cross.hpp"

namespace cnbi {
	namespace draw {

Cross::Cross(float size, float thick, const float* color) {
	this->height_ = size;
	this->width_  = size;
	this->thick_  = thick;
	
	/**** Fill initialization ****/
	this->hrect_shp_ = nullptr;
	this->vrect_shp_ = nullptr;
	
	this->fill_color_[0] = color[0];
	this->fill_color_[1] = color[1];
	this->fill_color_[2] = color[2];
	this->fill_color_[3] = color[3];

	// Create shape
	this->Create();
}

Cross::~Cross(void) {}

void Cross::CreateFill(void) {
	this->shp_sem_.Wait();	
	dtk_hshape shps[] = {
		this->hrect_shp_ = dtk_create_rectangle_hw(this->hrect_shp_, 
								this->orig_x_, this->orig_y_, 
								this->width_, this->thick_, 1,
								this->fill_color_), 
		this->vrect_shp_ = dtk_create_rectangle_hw(this->vrect_shp_, 
								this->orig_x_, this->orig_y_, 
			   					this->thick_, this->height_, 1,
								this->fill_color_)
	};
	this->fill_ptr_ = dtk_create_composite_shape(this->fill_ptr_, sizeof(shps)/sizeof(shps[0]), shps, 1);
	this->shp_sem_.Post();	
}

void Cross::CreateStroke(void) {
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

