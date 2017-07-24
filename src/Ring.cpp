#ifndef CNBIDRAW_RING_CPP
#define CNBIDRAW_RING_CPP

#include "Ring.hpp"

namespace cnbi {
	namespace draw {

Ring::Ring(float radius, float thick, const float* color, unsigned int npoints) :
		     Circle(radius, color, 1.0f, npoints) {

	this->shp_sem_.Wait();

	this->shp_ptr_ = dtk_create_circle_str(this->shp_ptr_, CNBIDRAW_SHAPE_DEFAULT_X,
			   						   CNBIDRAW_SHAPE_DEFAULT_Y, radius, thick,
									   color, npoints);

	this->filled_   = 1.0f;	
	this->color_[0] = color[0];
	this->color_[1] = color[1];
	this->color_[2] = color[2];
	this->color_[3] = color[3];
	this->npoints_  = npoints;
	this->thick_	= thick;

	this->shp_sem_.Post();
}

Ring::~Ring(void){};

void Ring::Create(void) {
	this->shp_sem_.Wait();

	this->shp_ptr_ = dtk_create_circle_str(this->shp_ptr_, this->orig_x_,
			   						       this->orig_y_, this->radius_, 
										   this->thick_, this->color_, 
										   this->npoints_);
	this->shp_sem_.Post();
}

float Ring::GetThick(void) {
	float thick;
	this->shp_sem_.Wait();
	thick = this->thick_;
	this->shp_sem_.Post();
	return thick;
}


	}
}
#endif


