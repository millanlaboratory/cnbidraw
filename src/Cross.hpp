#ifndef CNBIDRAW_CROSS_HPP
#define CNBIDRAW_CROSS_HPP

#include "Shape.hpp"

namespace cnbi {
	namespace draw {

class Cross : public Shape {

	public:
		Cross(float size, float thick, const float* color,
			  int filled = CNBIDRAW_SHAPE_DEFAULT_FILLED);
		virtual ~Cross(void);

		virtual void Create(void);
		float GetThick(void);

	private:
		float 		 thick_;
		dtk_hshape	 shp_hrect_;
		dtk_hshape	 shp_vrect_;
};


	}
}

#endif
