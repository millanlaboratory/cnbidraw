#ifndef CNBIDRAW_RECTANGLE_HPP
#define CNBIDRAW_RECTANGLE_HPP

#include "Shape.hpp"

namespace cnbi {
	namespace draw {

/*! \brief Rectangle class
 *
 * Implements a rectangle shape.
 */
class Rectangle : public Shape {

	public:
		/*! \brief Constructor
		 * \param	width	Rectangle's width
		 * \param	height	Rectangle's height
		 * \param	color	Rectangle's color
		 */
		Rectangle(float height, float width, const float* color);
		
		/*! \brief Destructor
		 */
		virtual ~Rectangle(void);

	protected:
		virtual void CreateFill(void);
		virtual void CreateStroke(void);
};


	}
}

#endif
