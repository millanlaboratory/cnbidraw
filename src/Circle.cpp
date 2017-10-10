#ifndef CNBIDRAW_CIRCLE_CPP
#define CNBIDRAW_CIRCLE_CPP

#include "Circle.hpp"

namespace cnbi {
	namespace draw {

Circle::Circle(float radius, const float* color, unsigned int npoints) : Shape() {
	this->radius_   = radius;
	this->npoints_  = npoints;
	
	/**** Fill initialization ****/
	this->fill_color_[0] = color[0];
	this->fill_color_[1] = color[1];
	this->fill_color_[2] = color[2];
	this->fill_color_[3] = color[3];

	// Create shape
	this->Create();
}

Circle::~Circle(void){};

void Circle::CreateFill(void) {
	this->shp_sem_.Wait();
	this->fill_ptr_ = dtk_create_circle(this->fill_ptr_, this->orig_x_,
			   						   this->orig_y_, this->radius_, 
									   1, this->fill_color_, 
									   this->npoints_);
	this->shp_sem_.Post();
}

void Circle::CreateStroke(void) {
	this->shp_sem_.Wait();
	this->strk_ptr_ = nullptr;
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


