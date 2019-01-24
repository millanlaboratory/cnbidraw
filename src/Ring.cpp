#ifndef CNBIDRAW_RING_CPP
#define CNBIDRAW_RING_CPP

#include "Ring.hpp"

namespace cnbi {
	namespace draw {

Ring::Ring(float radius, float thick, const float* color, unsigned int npoints) :
		     Circle(radius, color, npoints) {

	this->npoints_  = npoints;
	this->thick_	= thick;

	/**** Fill initialization ****/
	this->fill_color_[0] = color[0];
	this->fill_color_[1] = color[1];
	this->fill_color_[2] = color[2];
	this->fill_color_[3] = color[3];

	// Create shape
	this->Create();
}

Ring::~Ring(void){};

void Ring::CreateFill(void) {
	std::lock_guard<std::mutex> lock(this->shp_mutex_);

	this->fill_ptr_ = dtk_create_circle_str(this->fill_ptr_, this->orig_x_,
			   						       this->orig_y_, this->radius_, 
										   this->thick_, this->fill_color_, 
										   this->npoints_);
}

void Ring::CreateStroke(void) {
	std::lock_guard<std::mutex> lock(this->shp_mutex_);
	this->strk_ptr_ = nullptr;
}

float Ring::GetThick(void) {
	float thick;
	std::lock_guard<std::mutex> lock(this->shp_mutex_);
	thick = this->thick_;
	return thick;
}


	}
}
#endif


