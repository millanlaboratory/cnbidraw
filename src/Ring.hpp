#ifndef CNBIDRAW_RING_HPP
#define CNBIDRAW_RING_HPP

#include "Circle.hpp"

namespace cnbi {
	namespace draw {

/*! \brief Ring class
 *
 * Implements a ring (circular strip) shape.
 */
class Ring : public Circle {

	public:
		/*! \brief Constructor
		 * \param	radius	Ring's radius
		 * \param	thick	Ring's thickness 
		 * \param	color	Ring's color
		 * \param	npoints	Number of points to be used for the circle
		 */
		Ring(float radius, float thick, const float* color,
			 unsigned int npoints = CNBIDRAW_SHAPE_DEFAULT_NPOINTS);
		
		/*! \brief Destructor
		 */
		virtual ~Ring(void);

		/*! \brief Creation method
		 * It actually creates the shape by using dtk_create_shape
		 * functionalities.
		 */
		virtual void Create(void);
		
		/*! \brief Get ring's thickness
		 * \return	Thickness of the ring
		 */
		float GetThick(void);

	protected:
		float 		 thick_;
};


	}
}

#endif
