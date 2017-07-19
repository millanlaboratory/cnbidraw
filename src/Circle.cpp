#ifndef CNBIDRAW_CIRCLE_CPP
#define CNBIDRAW_CIRCLE_CPP

#include "Circle.hpp"

namespace cnbi {
	namespace draw {

Circle::Circle(float radius, const float* color, int filled, unsigned int npoints) {

	this->shp_sem_.Wait();
	this->radius_   = radius;
	this->filled_   = filled;	
	this->color_[0] = color[0];
	this->color_[1] = color[1];
	this->color_[2] = color[2];
	this->color_[3] = color[3];
	this->npoints_  = npoints;
	this->shp_sem_.Post();
}

Circle::~Circle(void){};

void Circle::Create(void) {
	this->shp_sem_.Wait();
	this->shp_ptr_ = dtk_create_circle(this->shp_ptr_, this->orig_x_,
			   						   this->orig_y_, this->radius_, 
									   this->filled_, this->color_, 
									   this->npoints_);
	this->shp_sem_.Post();
}

unsigned int Circle::GetNumPoints(void) {
	unsigned int npoints;
	this->shp_sem_.Wait();
	npoints = this->npoints_;
	this->shp_sem_.Post();
	return npoints;
}

	}
}
#endif


