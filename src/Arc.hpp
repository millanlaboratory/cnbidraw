#ifndef CNBIDRAW_ARC_HPP
#define CNBIDRAW_ARC_HPP

#include <cmath>
#include "Ring.hpp"

namespace cnbi {
	namespace draw {

/*! \brief Arc class
 *
 * Implements a arc shape.
 */
class Arc : public Ring {

	public:
		/*! \brief Constructor
		 * \param	radius	Arc's radius
		 * \param	angle	Arc's length [rad]
		 * \param	thick	Arc's thickness 
		 * \param	color	Arc's color
		 * \param	npoints	Number of points to be used for the circle
		 */
		Arc(float radius, float length, float thick, const float* color,
			unsigned int npoints = CNBIDRAW_SHAPE_DEFAULT_NPOINTS);
		
		/*! \brief Destructor
		 */
		virtual ~Arc(void);
		
		/*! \brief Get arc's length
		 * \return	Length of the arc in rad
		 */
		float GetLength(void);


	protected:
		virtual void CreateFill(void);
		virtual void CreateStroke(void){};

	protected:
		float	length_;	
};


	}
}

#endif
