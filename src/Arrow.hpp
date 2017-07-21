#ifndef CNBIDRAW_ARROW_HPP
#define CNBIDRAW_ARROW_HPP

#include "Shape.hpp"


namespace cnbi {
	namespace draw {

class Arrow : public Shape {

	public:
		Arrow(float width, float height, const float* color,
			  float thick = CNBIDRAW_ARROW_DEFAULT_THICK, 
			  float squeeze = CNBIDRAW_ARROW_DEFAULT_SQUEEZE, 
			  int filled = CNBIDRAW_SHAPE_DEFAULT_FILLED);
		virtual ~Arrow(void);

		virtual void Create(void);
		float GetThick(void);
		float GetSqueeze(void);

	private:
		float			thick_;
		float			squeeze_;
		unsigned int	nvert_;
		unsigned int 	nind_;
		float*			vertpos_;
		float*			vertcol_;
		unsigned int*	indices_;
};


	}
}

#endif
