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
		 * \param	filled	1 if the arrow is filled, 0 otherwise
		 */
		Rectangle(float width, float height, const float* color,
				  int filled = CNBIDRAW_SHAPE_DEFAULT_FILLED);
		
		/*! \brief Destructor
		 */
		virtual ~Rectangle(void);

		/*! \brief Creation method
		 * It actually creates the shape by using dtk_create_shape
		 * functionalities.
		 */
		virtual void Create(void);
};


	}
}

#endif
