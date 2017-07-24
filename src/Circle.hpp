#ifndef CNBIDRAW_CIRCLE_HPP
#define CNBIDRAW_CIRCLE_HPP

#include "Shape.hpp"

namespace cnbi {
	namespace draw {

/*! \brief Circle class
 *
 * Implements a circle shape.
 */
class Circle : public Shape {

	public:
		/*! \brief Constructor
		 * \param	radius	Circle's radius
		 * \param	color	Arrow's color
		 * \param	filled	1 if the arrow is filled, 0 otherwise
		 * \param	npoints	Number of points to be used for the circle
		 */
		Circle(float radius, const float* color,
			   int filled = CNBIDRAW_SHAPE_DEFAULT_FILLED,
			   unsigned int npoints = CNBIDRAW_SHAPE_DEFAULT_NPOINTS);
		
		/*! \brief Destructor
		 */
		virtual ~Circle(void);

		/*! \brief Creation method
		 * It actually creates the shape by using dtk_create_shape
		 * functionalities.
		 */
		virtual void Create(void);
		
		/*! \brief Get the number of points set
		 * \return	Number of points set
		 */
		unsigned int GetNumPoints(void);

	protected:
		float 		 radius_;
		unsigned int npoints_;
};


	}
}

#endif
