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
	this->filled_  = 0;
	this->height_  = 0.0f;
	this->width_   = 0.0f;
	this->shp_sem_.Post();
}

Shape::~Shape(void) {
	this->Destroy();
}

void Shape::Destroy(void) {
	this->shp_sem_.Wait();
	dtk_destroy_shape(this->shp_ptr_);
	this->shp_ptr_ = nullptr;
	this->shp_sem_.Post();
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
	dtk_move_shape(this->shp_ptr_, x, y);
	this->curr_x_ = x;
	this->curr_y_ = y;
	this->shp_sem_.Post();
}

void Shape::RelMove(float dx, float dy) {
	this->shp_sem_.Wait();
	dtk_relmove_shape(this->shp_ptr_, dx, dy);
	this->curr_x_ = this->curr_x_ + dx;
	this->curr_y_ = this->curr_y_ + dy;
	this->shp_sem_.Post();
}

void Shape::Rotate(float deg) {
	this->shp_sem_.Wait();
	dtk_rotate_shape(this->shp_ptr_, deg);
	this->curr_z_ = deg;
	this->shp_sem_.Post();
}

void Shape::RelRotate(float ddeg) {
	this->shp_sem_.Wait();
	dtk_relrotate_shape(this->shp_ptr_, ddeg);
	this->curr_z_ = this->curr_z_ + ddeg;
	this->shp_sem_.Post();
}

void Shape::SetAlpha(float alpha) {
	this->shp_sem_.Wait();
	this->color_[3] = alpha;
	dtk_setcolor_shape(this->shp_ptr_, this->color_, DTK_IGNRGB);
	this->shp_sem_.Post();
}

void Shape::SetColor(const float* color) {
	this->shp_sem_.Wait();
	this->color_[0] = color[0];
	this->color_[1] = color[1];
	this->color_[2] = color[2];
	this->color_[3] = color[3];
	dtk_setcolor_shape(this->shp_ptr_, this->color_, 0);
	this->shp_sem_.Post();
}

void Shape::Hide(void) {
	if(this->GetAlpha() != 0.0f)
		this->SetAlpha(0.0f);
}

void Shape::Show(void) {
	if(this->GetAlpha() != 1.0f)
		this->SetAlpha(1.0f);
}

void Shape::GetPosition(float* x, float* y) {
	this->shp_sem_.Wait();
	*x = this->curr_x_;
	*y = this->curr_y_;
	this->shp_sem_.Post();
}

float Shape::GetAlpha(void) {
	float alpha;
	this->shp_sem_.Wait();
	alpha = this->color_[3];
	this->shp_sem_.Post();
	return alpha;
}

const float* Shape::GetColor(void) {
	return this->color_;
}

void Shape::WaitShape(void) {
	this->shp_sem_.Wait();
}

void Shape::PostShape(void) {
	this->shp_sem_.Post();
}

dtk_hshape Shape::GetShapePtr(void) {
      return this->shp_ptr_;
}

	}
}

#endif
