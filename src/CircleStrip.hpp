#ifndef CNBIDRAW_CIRCLE_STRIP_HPP
#define CNBIDRAW_CIRCLE_STRIP_HPP

#include "Circle.hpp"

namespace cnbi {
	namespace draw {

class CircleStrip : public Circle {

	public:
		CircleStrip(float radius, float thick, const float* color,
					unsigned int npoints = CNBIDRAW_SHAPE_DEFAULT_NPOINTS);
		virtual ~CircleStrip(void);

		virtual void Create(void);
		float GetThick(void);

	protected:
		float 		 thick_;
};


	}
}

#endif
