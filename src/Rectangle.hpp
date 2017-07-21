#ifndef CNBIDRAW_RECTANGLE_HPP
#define CNBIDRAW_RECTANGLE_HPP

#include "Shape.hpp"

namespace cnbi {
	namespace draw {

class Rectangle : public Shape {

	public:
		Rectangle(float width, float height, const float* color,
				  int filled = CNBIDRAW_SHAPE_DEFAULT_FILLED);
		virtual ~Rectangle(void);

		virtual void Create(void);
};


	}
}

#endif
