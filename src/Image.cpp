#ifndef CNBIDRAW_IMAGE_CPP
#define CNBIDRAW_IMAGE_CPP

#include "Image.hpp"


namespace cnbi {
	namespace draw {

Image::Image(float width, float height, const float* color) {
	this->height_ = height;
	this->width_  = width;
	this->filled_   = 1;	
	this->color_[0] = color[0];
	this->color_[1] = color[1];
	this->color_[2] = color[2];
	this->color_[3] = color[3];
	this->img_tex_  = nullptr;
}

Image::~Image(void) {
	this->shp_sem_.Wait();
	if(this->img_tex_ != nullptr)
		dtk_destroy_texture(this->img_tex_);
	this->shp_sem_.Post();
}

bool Image::Set(const std::string& filename, unsigned int mxlvl) {

	bool retcod = false;
	this->shp_sem_.Wait();

	if(this->img_tex_ != nullptr)
		dtk_destroy_texture(this->img_tex_);
	
	this->img_tex_ = dtk_load_image(filename.c_str(), mxlvl); 
	
	if(this->img_tex_ != nullptr) 
		retcod = true;

	this->shp_sem_.Post();

	this->Create();

	return retcod;
}

void Image::Create(void) {
	this->shp_sem_.Wait();
	if(this->img_tex_ != nullptr) {
		this->shp_ptr_ = dtk_create_image(this->shp_ptr_, 
					  this->orig_x_, this->orig_y_,
					  this->width_, this->height_, 
					  this->color_, this->img_tex_);
	}
	this->shp_sem_.Post();
}

bool Image::GetSize(unsigned int* w_px, unsigned int* h_px) {
	
	bool retcod = false;
	this->shp_sem_.Wait();
	if(this->img_tex_ != nullptr) {
		dtk_texture_getsize(this->img_tex_, w_px, h_px);
		retcod = true;
	}
	this->shp_sem_.Post();
	return retcod;
}


	}
}

#endif
