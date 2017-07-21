#ifndef CNBIDRAW_IMAGE_HPP
#define CNBIDRAW_IMAGE_HPP

#include "Shape.hpp"


namespace cnbi {
	namespace draw {

class Image : public Shape {

	public:
		Image(float width, float height, const float* color = dtk_white);
		virtual ~Image(void);

		virtual void Create(void);

		bool Set(const std::string& filename, unsigned int mxlvl = CNBIDRAW_IMAGE_DEFAULT_MXLVL);

		bool GetSize(unsigned int* w_px, unsigned int* h_px);
	private:
		dtk_htex	img_tex_;
};


	}
}

#endif
