#ifndef CNBIDRAW_ARROW_CPP
#define CNBIDRAW_ARROW_CPP

#include "Arrow.hpp"

namespace cnbi {
    namespace draw {

Arrow::Arrow(float width, float height, const float* color, 
	     float thick, float squeeze, int filled) {
    this->height_   = height;
    this->width_    = width;
    this->thick_    = thick;
    this->squeeze_  = squeeze;
    this->filled_   = filled;	
    this->color_[0] = color[0];
    this->color_[1] = color[1];
    this->color_[2] = color[2];
    this->color_[3] = color[3];
    
    // Initialize vertex, colors and index arrays
    this->nvert_    = 7;
    this->nind_     = 7;
    this->vertpos_  = new float[2*this->nvert_];
    this->vertcol_  = new float[4*this->nvert_];
    this->indices_  = new unsigned int[this->nind_];
    
    // Define vertex positions
    this->vertpos_[0]  = -this->width_/2.0f;
    this->vertpos_[1]  = 0.0f;
    this->vertpos_[2]  = -this->width_/2.0f + this->width_*this->squeeze_;
    this->vertpos_[3]  = this->height_/2.0f;
    this->vertpos_[4]  = -this->width_/2.0f + this->width_*this->squeeze_;
    this->vertpos_[5]  = (this->height_*this->thick_)/2.0f;
    this->vertpos_[6]  = this->width_/2.0f;
    this->vertpos_[7]  = (this->height_*this->thick_)/2.0f;
    this->vertpos_[8]  = this->width_/2.0f;
    this->vertpos_[9]  = -(this->height_*this->thick_)/2.0f;
    this->vertpos_[10] = -this->width_/2.0f + this->width_*this->squeeze_;
    this->vertpos_[11] = -(this->height_*this->thick_)/2.0f;
    this->vertpos_[12] = -this->width_/2.0f + this->width_*this->squeeze_;
    this->vertpos_[13] = -this->height_/2.0f;
    
    // Define vertex colors
    for(auto i = 0; i< this->nvert_*4; i+=4) {
    	this->vertcol_[i  ] = this->color_[0];
    	this->vertcol_[i+1] = this->color_[1];
    	this->vertcol_[i+2] = this->color_[2];
    	this->vertcol_[i+3] = this->color_[3];
    }
    
    // Define indices
    this->indices_[0] = 1;
    this->indices_[1] = 6;
    this->indices_[2] = 0;
    this->indices_[3] = 2;
    this->indices_[4] = 5;
    this->indices_[5] = 3;
    this->indices_[6] = 4;
}

Arrow::~Arrow(void) {
    delete this->vertcol_;
    delete this->vertpos_;
    delete this->indices_;
}

void Arrow::Create(void) {
    this->shp_sem_.Wait();	
    this->shp_ptr_ = dtk_create_complex_shape(this->shp_ptr_,
					      this->nvert_, this->vertpos_,
					      this->vertcol_, NULL, 
					      this->nind_, this->indices_, 
					      DTK_TRIANGLE_STRIP, NULL);
    this->shp_sem_.Post();	
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

