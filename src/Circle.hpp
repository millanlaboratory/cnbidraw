#ifndef CNBIDRAW_CIRCLE_HPP
#define CNBIDRAW_CIRCLE_HPP

#include "Shape.hpp"

namespace cnbi {
	namespace draw {

class Circle : public Shape {

	public:
		Circle(float radius, const float* color,
			   int filled = CNBIDRAW_SHAPE_DEFAULT_FILLED,
			   unsigned int npoints = CNBIDRAW_SHAPE_DEFAULT_NPOINTS);
		virtual ~Circle(void);

		virtual void Create(void);
		unsigned int GetNumPoints(void);

	protected:
		float 		 radius_;
		unsigned int npoints_;
};


	}
}

#endif
