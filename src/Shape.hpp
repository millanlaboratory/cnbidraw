#ifndef CNBIDRAW_SHAPE_HPP
#define CNBIDRAW_SHAPE_HPP

#include <drawtk.h>
#include <dtk_colors.h>
#include <cnbicore/CcBasic.hpp>

#include "Flags.hpp"

namespace cnbi {
	namespace draw {

class Shape {

	public:
		Shape(void);
		virtual ~Shape(void);

		virtual void Create(void) = 0;
		virtual void Destroy(void);

		void Move(float x, float y);
		void Rotate(float deg);
		void RelMove(float dx, float dy);
		void RelRotate(float ddeg);
		void Hide(void);
		void Show(void);
		void SetColor(const float* color);
		void SetAlpha(float alpha);
	
		float GetWidth(void);
		float GetHeight(void);
		void GetPosition(float* x, float* y);
		const float* GetColor(void);
		float GetAlpha(void);

		void WaitShape(void);
		void PostShape(void);
		
		virtual dtk_hshape GetShapePtr(void);

	protected:
		dtk_hshape 	shp_ptr_;
		CcSemaphore shp_sem_;
		float		curr_x_;
		float 		curr_y_;
		float 		curr_z_;
		float 		orig_x_;
		float		orig_y_;
		float 		color_[4];
		int			filled_;
		float 		height_;
		float 		width_;

};


	}
}
#endif
