#ifndef CNBIDRAW_RECTANGLE_CPP
#define CNBIDRAW_RECTANGLE_CPP

#include "Rectangle.hpp"

namespace cnbi {
	namespace draw {

Rectangle::Rectangle(float height, float width, const float* color) : Shape() {
	this->width_  = width;
	this->height_ = height;

	/**** Fill initialization ****/
	this->fill_color_[0] = color[0];
	this->fill_color_[1] = color[1];
	this->fill_color_[2] = color[2];
	this->fill_color_[3] = color[3];

	// Create shape
	this->Create();
}

Rectangle::~Rectangle(void) {}

void Rectangle::CreateFill(void) {
	std::lock_guard<std::mutex> lock(this->shp_mutex_);
	this->fill_ptr_ = dtk_create_rectangle_hw(this->fill_ptr_, this->orig_x_, this->orig_y_, 
			   								 this->height_, this->width_, 1,
											 this->fill_color_);
}

void Rectangle::CreateStroke(void) {

	std::lock_guard<std::mutex> lock(this->shp_mutex_);
	
    // Initialize vertex, colors and index arrays
	this->strk_nvert_    = 8;
    this->strk_nind_     = 10;
    this->strk_vertpos_  = new float[2*this->strk_nvert_];
    this->strk_vertcol_  = new float[4*this->strk_nvert_];
    this->strk_indices_  = new unsigned int[this->strk_nind_];

    // Define vertex positions
	this->strk_vertpos_[0]  = -this->width_/2.0f - this->strk_thick_;
	this->strk_vertpos_[1]  = -this->height_/2.0f - this->strk_thick_;
	this->strk_vertpos_[2]  = -this->width_/2.0f; 
	this->strk_vertpos_[3]  = -this->height_/2.0f;
	this->strk_vertpos_[4]  = -this->width_/2.0f - this->strk_thick_;
	this->strk_vertpos_[5]  = this->height_/2.0f + this->strk_thick_; 
	this->strk_vertpos_[6]  = -this->width_/2.0f; 
	this->strk_vertpos_[7]  = this->height_/2.0f;
	this->strk_vertpos_[8]  = this->width_/2.0f + this->strk_thick_;
	this->strk_vertpos_[9]  = this->height_/2.0f + this->strk_thick_;
	this->strk_vertpos_[10] = this->width_/2.0f;
	this->strk_vertpos_[11] = this->height_/2.0f;
	this->strk_vertpos_[12] = this->width_/2.0f + this->strk_thick_;
	this->strk_vertpos_[13] = -this->height_/2.0f - this->strk_thick_;
	this->strk_vertpos_[14] = this->width_/2.0f;
	this->strk_vertpos_[15] = -this->height_/2.0f;

    // Define vertex colors
    for(auto i = 0; i< this->strk_nvert_*4; i+=4) {
    	this->strk_vertcol_[i  ] = this->strk_color_[0];
    	this->strk_vertcol_[i+1] = this->strk_color_[1];
    	this->strk_vertcol_[i+2] = this->strk_color_[2];
    	this->strk_vertcol_[i+3] = this->strk_color_[3];
    }
    
	// Define indices
    this->strk_indices_[0] = 0;
    this->strk_indices_[1] = 1;
    this->strk_indices_[2] = 2;
    this->strk_indices_[3] = 3;
    this->strk_indices_[4] = 4;
    this->strk_indices_[5] = 5;
    this->strk_indices_[6] = 6;
    this->strk_indices_[7] = 7;
    this->strk_indices_[8] = 0;
    this->strk_indices_[9] = 1;

	// Create stroke
    this->strk_ptr_ = dtk_create_complex_shape(this->strk_ptr_,
					      this->strk_nvert_, this->strk_vertpos_,
					      this->strk_vertcol_, NULL, 
					      this->strk_nind_, this->strk_indices_, 
					      DTK_TRIANGLE_STRIP, NULL);
}

	}
}

#endif

