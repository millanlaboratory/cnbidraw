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
		 */
		Cross(float size, float thick, const float* color);
		
		/*! \brief Destructor
		 */
		virtual ~Cross(void);

		/*! \brief Get cross's thickness
		 * \return	Thickness of the cross
		 */
		float GetThick(void);

	protected:
		virtual void CreateFill(void);

	private:
		float 		 thick_;
		dtk_hshape	 hrect_shp_;
		dtk_hshape	 vrect_shp_;
};


	}
}

#endif
