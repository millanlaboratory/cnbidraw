#ifndef CNBIDRAW_CROSS_HPP
#define CNBIDRAW_CROSS_HPP

#include "Shape.hpp"

namespace cnbi {
	namespace draw {

/*! \brief Cross class
 *
 * Implements a cross shape.
 */
class Cross : public Shape {

	public:
		/*! \brief Constructor
		 * \param	size	Cross's size
		 * \param	thick	Cross's thickness
		 * \param	color	Cross's color
		 * \param	filled	1 if the arrow is filled, 0 otherwise
		 */
		Cross(float size, float thick, const float* color,
			  int filled = CNBIDRAW_SHAPE_DEFAULT_FILLED);
		
		/*! \brief Destructor
		 */
		virtual ~Cross(void);

		/*! \brief Creation method
		 * It actually creates the shape by using dtk_create_shape
		 * functionalities.
		 */
		virtual void Create(void);
		
		/*! \brief Get cross's thickness
		 * \return	Thickness of the cross
		 */
		float GetThick(void);

	private:
		float 		 thick_;
		dtk_hshape	 shp_hrect_;
		dtk_hshape	 shp_vrect_;
};


	}
}

#endif
