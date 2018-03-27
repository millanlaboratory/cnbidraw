#ifndef CNBIDRAW_ARC_CPP
#define CNBIDRAW_ARC_CPP

#include "Arc.hpp"

namespace cnbi {
	namespace draw {

Arc::Arc(float radius, float length, float thick, const float* color, unsigned int npoints) : Ring(radius, thick, color, npoints) {

	this->length_	= length;

	// Initialize vertex, colors and index arrays
    this->fill_nvert_    = 2*this->npoints_ + 2;
    this->fill_nind_     = 2*this->npoints_ + 2;
    this->fill_vertpos_  = new float[2*this->fill_nvert_];
    this->fill_vertcol_  = new float[4*this->fill_nvert_];
    this->fill_indices_  = new unsigned int[this->fill_nind_];

    // Define vertex positions
	float cr, r1, r2;
	r1 = radius;
	r2 = radius - thick;
	for(unsigned int i = 0; i<this->fill_nvert_; i++) {
		cr = i % 2 ? r2 : r1;
		this->fill_indices_[i] = i;
		this->fill_vertpos_[2*i]=cr*cos((float)i*this->length_/this->npoints_/2.0f);
		this->fill_vertpos_[2*(i)+1]=cr*sin((float)(i)*this->length_/this->npoints_/2.0f);
	}
    
	// Define vertex colors
    for(auto i = 0; i< this->fill_nvert_*4; i+=4) {
    	this->fill_vertcol_[i  ] = this->fill_color_[0];
    	this->fill_vertcol_[i+1] = this->fill_color_[1];
    	this->fill_vertcol_[i+2] = this->fill_color_[2];
    	this->fill_vertcol_[i+3] = this->fill_color_[3];
    }

	// Create shape
	this->Create();
}

Arc::~Arc(void) {};


void Arc::CreateFill(void) {
	
	this->shp_sem_.Wait();

	this->fill_ptr_ = dtk_create_complex_shape(this->fill_ptr_,
					      this->fill_nvert_, this->fill_vertpos_,
					      this->fill_vertcol_, NULL, 
					      this->fill_nind_, this->fill_indices_, 
					      DTK_TRIANGLE_STRIP, NULL);

	this->shp_sem_.Post();
}

float Arc::GetLength(void) {
	float length;
	this->shp_sem_.Wait();
	length = this->length_;
	this->shp_sem_.Post();
	return length;
}
	}

}

#endif
