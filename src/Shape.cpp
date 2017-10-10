#ifndef CNBIDRAW_SHAPE_CPP
#define CNBIDRAW_SHAPE_CPP

#include "Shape.hpp"

namespace cnbi {
	namespace draw {

Shape::Shape(void){
	this->shp_sem_.Wait();
	this->shp_ptr_ = nullptr;
	this->curr_x_  = 0.0f;
	this->curr_y_  = 0.0f;
	this->curr_z_  = 0.0f;
	this->orig_x_  = 0.0f;
	this->orig_y_  = 0.0f;
	this->height_  = 0.0f;
	this->width_   = 0.0f;

	/**** Fill initialization ****/
	this->fill_ptr_	  = nullptr;
	this->fill_nvert_ = 0;
	this->fill_nind_  = 0;
	
	this->fill_color_[0] = 1.0f;
	this->fill_color_[1] = 1.0f;
	this->fill_color_[2] = 1.0f;
	this->fill_color_[3] = 1.0f;
	
	/**** Stroke initialization ****/
	this->strk_ptr_	  = nullptr;
	this->strk_thick_ = 0.0f;
	this->strk_nvert_ = 0;
	this->strk_nind_  = 0;
	
	this->strk_color_[0] = 0.0f;
	this->strk_color_[1] = 0.0f;
	this->strk_color_[2] = 0.0f;
	this->strk_color_[3] = 1.0f;
	this->shp_sem_.Post();
}

Shape::~Shape(void) {
	this->Destroy();
}

void Shape::Destroy(void) {
	this->shp_sem_.Wait();
	dtk_destroy_shape(this->shp_ptr_);
	this->shp_ptr_ = nullptr;
	this->strk_ptr_ = nullptr;
	this->fill_ptr_ = nullptr;
	this->shp_sem_.Post();
}

void Shape::Create(void) {
	
	dtk_hshape* shps;
	unsigned int nshps = 0;

	this->CreateFill();
	this->CreateStroke();

	this->shp_sem_.Wait();
	if(this->strk_ptr_ != nullptr && this->fill_ptr_ != nullptr) {
		nshps = 2;
		shps = new dtk_hshape[nshps*sizeof(dtk_hshape)];
		shps[0] = this->strk_ptr_;
		shps[1] = this->fill_ptr_;
	} else if(this->strk_ptr_ == nullptr && this->fill_ptr_ != nullptr) {
		nshps = 1;
		shps = new dtk_hshape[nshps*sizeof(dtk_hshape)];
		shps[0] = this->fill_ptr_;
	} else if(this->strk_ptr_ != nullptr && this->fill_ptr_ == nullptr) {
		nshps = 1;
		shps = new dtk_hshape[nshps*sizeof(dtk_hshape)];
		shps[0] = this->strk_ptr_;
	}

	if(nshps > 0) {
		this->shp_ptr_ = dtk_create_composite_shape(this->shp_ptr_, nshps, shps, 1);
	}
	this->shp_sem_.Post();

	delete shps;
}

void Shape::SetStroke(float thick, const float* color) {
	this->shp_sem_.Wait();
	this->strk_thick_ = thick;
	this->strk_color_[0] = color[0];
	this->strk_color_[1] = color[1];
	this->strk_color_[2] = color[2];
	this->strk_color_[3] = color[3];
	this->shp_sem_.Post();

	this->Create();
}

float Shape::GetHeight(void) {
	float height;
	this->shp_sem_.Wait();
	height = this->height_;
	this->shp_sem_.Post();
	return height;
}

float Shape::GetWidth(void) {
	float width;
	this->shp_sem_.Wait();
	width = this->width_;
	this->shp_sem_.Post();
	return width;
}

void Shape::Move(float x, float y) {
	this->shp_sem_.Wait();
	if(this->shp_ptr_ != nullptr) {
		dtk_move_shape(this->shp_ptr_, x, y);
		this->curr_x_ = x;
		this->curr_y_ = y;
	}
	this->shp_sem_.Post();
}

void Shape::RelMove(float dx, float dy) {
	this->shp_sem_.Wait();
	if(this->shp_ptr_ != nullptr) {
		dtk_relmove_shape(this->shp_ptr_, dx, dy);
		this->curr_x_ = this->curr_x_ + dx;
		this->curr_y_ = this->curr_y_ + dy;
	}
	this->shp_sem_.Post();
}

void Shape::Rotate(float deg) {
	this->shp_sem_.Wait();
	if(this->shp_ptr_ != nullptr) {
		dtk_rotate_shape(this->shp_ptr_, deg);
		this->curr_z_ = deg;
	}
	this->shp_sem_.Post();
}

void Shape::RelRotate(float ddeg) {
	this->shp_sem_.Wait();
	if(this->shp_ptr_ != nullptr) {
		dtk_relrotate_shape(this->shp_ptr_, ddeg);
		this->curr_z_ = this->curr_z_ + ddeg;
	}
	this->shp_sem_.Post();
}

void Shape::SetAlpha(float alpha, unsigned int element) {

	this->shp_sem_.Wait();

	switch(element) {
		case Shape::Stroke:
			this->set_alpha_stroke(alpha);
			break;
		case Shape::Fill:
			this->set_alpha_fill(alpha);
			break;
		case Shape::Whole:
			this->set_alpha_stroke(alpha);
			this->set_alpha_fill(alpha);
			break;
		default:
			break;
	}

	this->shp_sem_.Post();
	
	//this->Create();
}

void Shape::set_alpha_stroke(float alpha) {
	if(this->strk_ptr_ != nullptr) {
		this->strk_color_[3] = alpha;
		dtk_setcolor_shape(this->strk_ptr_, this->strk_color_, DTK_IGNRGB);
	}
}

void Shape::set_alpha_fill(float alpha) {
	if(this->fill_ptr_ != nullptr) {
		this->fill_color_[3] = alpha;
		dtk_setcolor_shape(this->fill_ptr_, this->fill_color_, DTK_IGNRGB);
	}
}

void Shape::set_color_stroke(const float*& color) {
	if(this->strk_ptr_ != nullptr) {
		this->strk_color_[0] = color[0];
		this->strk_color_[1] = color[1];
		this->strk_color_[2] = color[2];
		dtk_setcolor_shape(this->strk_ptr_, this->strk_color_, DTK_IGNA);
	}
}

void Shape::set_color_fill(const float*& color) {
	if(this->fill_ptr_ != nullptr) {
		this->fill_color_[0] = color[0];
		this->fill_color_[1] = color[1];
		this->fill_color_[2] = color[2];
		dtk_setcolor_shape(this->fill_ptr_, this->fill_color_, DTK_IGNA);
	}
}

void Shape::SetColor(const float* color, unsigned int element) {

	this->shp_sem_.Wait();
	switch(element) {
		case Shape::Stroke:
			this->set_color_stroke(color);
			break;
		case Shape::Fill:
			this->set_color_fill(color);
			break;
		case Shape::Whole:
			this->set_color_stroke(color);
			this->set_color_fill(color);
			break;
		default:
			break;
	}
	this->shp_sem_.Post();

	//this->Create();
}

void Shape::Hide(unsigned int element) {
	this->SetAlpha(0.0f, element);
}

void Shape::Show(unsigned int element) {
	this->SetAlpha(1.0f, element);
}

void Shape::GetPosition(float* x, float* y) {
	this->shp_sem_.Wait();
	*x = this->curr_x_;
	*y = this->curr_y_;
	this->shp_sem_.Post();
}

float Shape::GetAlpha(unsigned int element) {
	float alpha;
	this->shp_sem_.Wait();

	switch(element) {
		case Shape::Stroke:
			alpha = this->strk_color_[3];
			break;
		case Shape::Fill:
			alpha = this->fill_color_[3];
			break;
		case Shape::Whole:
			alpha = this->fill_color_[3];
			break;
		default:
			break;
	}

	this->shp_sem_.Post();
	return alpha;
}

void Shape::GetColor(float* color, unsigned int element) {
	this->shp_sem_.Wait();
	
	switch(element) {
		case Shape::Stroke:
			memcpy(color, this->strk_color_, 4*sizeof(float));
			break;
		case Shape::Fill:
			memcpy(color, this->fill_color_, 4*sizeof(float));
			break;
		case Shape::Whole:
			memcpy(color, this->fill_color_, 4*sizeof(float));
			break;
		default:
			break;
	}
	this->shp_sem_.Post();
}

void Shape::WaitShape(void) {
	this->shp_sem_.Wait();
}

void Shape::PostShape(void) {
	this->shp_sem_.Post();
}

void Shape::Draw(void) {
	this->shp_sem_.Wait();
	if(this->shp_ptr_ != nullptr)
		dtk_draw_shape(this->shp_ptr_);
	this->shp_sem_.Post();
}

	}
}

#endif
