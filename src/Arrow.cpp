#ifndef CNBIDRAW_ARROW_CPP
#define CNBIDRAW_ARROW_CPP

#include "Arrow.hpp"

namespace cnbi {
    namespace draw {

Arrow::Arrow(float width, float height, const float* color, 
	     float thick, float squeeze) {
    this->height_   = height;
    this->width_    = width;
    this->thick_    = thick;
    this->squeeze_  = squeeze;
    
	/**** Fill initialization ****/
	this->fill_color_[0] = color[0];
    this->fill_color_[1] = color[1];
    this->fill_color_[2] = color[2];
    this->fill_color_[3] = color[3];
    
    // Initialize vertex, colors and index arrays
    this->fill_nvert_    = 7;
    this->fill_nind_     = 7;
    this->fill_vertpos_  = new float[2*this->fill_nvert_];
    this->fill_vertcol_  = new float[4*this->fill_nvert_];
    this->fill_indices_  = new unsigned int[this->fill_nind_];
    
    // Define vertex positions
    this->fill_vertpos_[0]  = -this->width_/2.0f;
    this->fill_vertpos_[1]  = 0.0f;
    this->fill_vertpos_[2]  = -this->width_/2.0f + this->width_*this->squeeze_;
    this->fill_vertpos_[3]  = this->height_/2.0f;
    this->fill_vertpos_[4]  = -this->width_/2.0f + this->width_*this->squeeze_;
    this->fill_vertpos_[5]  = (this->height_*this->thick_)/2.0f;
    this->fill_vertpos_[6]  = this->width_/2.0f;
    this->fill_vertpos_[7]  = (this->height_*this->thick_)/2.0f;
    this->fill_vertpos_[8]  = this->width_/2.0f;
    this->fill_vertpos_[9]  = -(this->height_*this->thick_)/2.0f;
    this->fill_vertpos_[10] = -this->width_/2.0f + this->width_*this->squeeze_;
    this->fill_vertpos_[11] = -(this->height_*this->thick_)/2.0f;
    this->fill_vertpos_[12] = -this->width_/2.0f + this->width_*this->squeeze_;
    this->fill_vertpos_[13] = -this->height_/2.0f;
    
    // Define vertex colors
    for(auto i = 0; i< this->fill_nvert_*4; i+=4) {
    	this->fill_vertcol_[i  ] = this->fill_color_[0];
    	this->fill_vertcol_[i+1] = this->fill_color_[1];
    	this->fill_vertcol_[i+2] = this->fill_color_[2];
    	this->fill_vertcol_[i+3] = this->fill_color_[3];
    }
    
    // Define indices
    this->fill_indices_[0] = 1;
    this->fill_indices_[1] = 6;
    this->fill_indices_[2] = 0;
    this->fill_indices_[3] = 2;
    this->fill_indices_[4] = 5;
    this->fill_indices_[5] = 3;
    this->fill_indices_[6] = 4;

	// Create shape
	this->Create();
}

Arrow::~Arrow(void) {
    delete this->fill_vertcol_;
    delete this->fill_vertpos_;
    delete this->fill_indices_;
}

void Arrow::CreateFill(void) {
    this->shp_sem_.Wait();	
    this->fill_ptr_ = dtk_create_complex_shape(this->fill_ptr_,
					      this->fill_nvert_, this->fill_vertpos_,
					      this->fill_vertcol_, NULL, 
					      this->fill_nind_, this->fill_indices_, 
					      DTK_TRIANGLE_STRIP, NULL);
    this->shp_sem_.Post();	
}

void Arrow::CreateStroke(void) {
}

float Arrow::GetThick(void) {
    float thick;
    this->shp_sem_.Wait();	
    thick = this->thick_;
    this->shp_sem_.Post();
    return thick;
}

float Arrow::GetSqueeze(void) {
    float squeeze;
    this->shp_sem_.Wait();	
    squeeze = this->squeeze_;
    this->shp_sem_.Post();
    return squeeze;
}
    }
}

#endif

