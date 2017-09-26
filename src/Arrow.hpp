#ifndef CNBIDRAW_ARROW_HPP
#define CNBIDRAW_ARROW_HPP

#include "Shape.hpp"

namespace cnbi {
    namespace draw {

/*! \brief Arrow class
 *
 * Implements an arrow shape.
 */
class Arrow : public Shape {

    public:
		/*! \brief Constructor
		 * \param	width	Arrow's width
		 * \param	height	Arrow's height
		 * \param	color	Arrow's color
		 * \param	thick	Arrow's body thickness (in percentage with respecth
		 *					to the overall height)
		 * \param	squeeze	Arrow's edge squeeze (in percentage with respecth
		 *					to the overall width)
		 * \param	filled	1 if the arrow is filled, 0 otherwise
		 */
		Arrow(float width, float height, const float* color,
		      float thick = CNBIDRAW_ARROW_DEFAULT_THICK, 
		      float squeeze = CNBIDRAW_ARROW_DEFAULT_SQUEEZE);

		/*! \brief Destructor
		 */
		virtual ~Arrow(void);
	
		/*! \brief Get the arrow thickness
		 * \return	Arrow's thickness
		 */
		float GetThick(void);
		
		/*! \brief Get the arrow squeeze
		 * \return	Arrow's squeeze
		 */
		float GetSqueeze(void);
	
	protected:
		virtual void CreateFill(void);

	private:
	    float			thick_;
	    float			squeeze_;

};
    }
}
#endif
