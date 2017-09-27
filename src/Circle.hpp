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
		 * \param	npoints	Number of points to be used for the circle
		 */
		Circle(float radius, const float* color,
			   unsigned int npoints = CNBIDRAW_SHAPE_DEFAULT_NPOINTS);
		
		/*! \brief Destructor
		 */
		virtual ~Circle(void);

		
		/*! \brief Get the number of points set
		 * \return	Number of points set
		 */
		unsigned int GetNumPoints(void);

	protected:
		virtual void CreateFill(void);
		virtual void CreateStroke(void);

	protected:
		float 		 radius_;
		unsigned int npoints_;
};


	}
}

#endif
