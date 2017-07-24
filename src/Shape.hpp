#ifndef CNBIDRAW_SHAPE_HPP
#define CNBIDRAW_SHAPE_HPP

#include <string.h>
#include <drawtk.h>
#include <dtk_colors.h>
#include <cnbicore/CcSemaphore.hpp>
#include <cnbicore/CcTime.hpp>

#include "Flags.hpp"

namespace cnbi {
	namespace draw {

/*! \brief Shape class
 *
 * This class represents the base class for evry shape. It is pure virtual
 * class, the method Create must be implemented in order to instanciate it.
 * The class is thread-safe.
 */
class Shape {

	public:
		/*! \brief Constructor
		 */
		Shape(void);
		/*! \brief Destructor
		 */
		virtual ~Shape(void);

		/*! \brief Pure virtual method
		 */
		virtual void Create(void) = 0;

		/*! \brief Destroy method
		 */
		virtual void Destroy(void);

		/*! \brief Move method
		 * It moves the shape to the new coordinate with respect to the center
		 * of th screen (0.0, 0.0).
		 * Call to draw method is required.
		 *
		 * \param	x	x-coordinate in window framework
		 * \param	y	y-coordinate in window framework
		 */
		void Move(float x, float y);
		
		/*! \brief Rotate method
		 * It rotates (counter-clockwise) the shape to the given degree around the center
		 * of th screen (0.0, 0.0).
		 * Call to draw method is required.
		 * \param	deg	angle
		 */
		void Rotate(float deg);
		
		/*! \brief Relative move method
		 * It moves the shape of dx and dy with respect to the current position
		 * Call to draw method is required.
		 *
		 * \param	dx	step along x-axis
		 * \param	dy	step along y-axis
		 */
		void RelMove(float dx, float dy);
		
		/*! \brief Relative rotate method
		 * It rotates the shape of ddeg and dy with respect to the current angle
		 * Call to draw method is required.
		 *
		 * \param	ddeg	angular step
		 */
		void RelRotate(float ddeg);
		
		/*! \brief Hide method
		 * It hides the shape (set alpha to 0.0)
		 * Call to draw method is required.
		 */
		void Hide(void);
		
		/*! \brief Show method
		 * It showes the shape (set alpha to 1.0)
		 * Call to draw method is required.
		 */
		void Show(void);
		
		/*! \brief Draw method
		 * It draws the shape in the rendering context.
		 * Call to update window is required.
		 */
		void Draw(void);

		/*! \brief Set the color of the shape
		 * It sets the color of the shape for the next drawing.
		 *
		 * \param	color	RGBA values to be set
		 */
		void SetColor(const float* color);
		
		/*! \brief Set the alpha of the shape
		 * It set the alpha of the shape for the next drawing.
		 *
		 * \param	alpha	alpha value to be set
		 */
		void SetAlpha(float alpha);
	
		/*! \brief Get the width of the shape
		 * It gets the current width of the shape
		 *
		 * \return	Shape's width
		 */
		float GetWidth(void);
		
		/*! \brief Get the height of the shape
		 * It gets the current height of the shape
		 *
		 * \return	Shape's height
		 */
		float GetHeight(void);
		
		/*! \brief Get the position of the shape
		 * It gets the current position of the shape
		 *
		 * \param[out]	x	x-coordinate
		 * \param[out]	y	y-coordinate
		 */
		void  GetPosition(float* x, float* y);
		
		/*! \brief Get the color of the shape
		 * It gets the current color of the shape
		 *
		 * \param[out]	color	Shape's color
		 */
		void  GetColor(float* color);
		
		/*! \brief Get the alpha of the shape
		 * It gets the current alpha of the shape
		 *
		 * \param[out]	alpha	Shape's alpha
		 */
		float GetAlpha(void);

		/*! \brief Shape's lock
		 * It locks the local resources
		 */
		void WaitShape(void);
		
		/*! \brief Shape's unlock
		 * It unlocks the local resources
		 */
		void PostShape(void);

	protected:
		dtk_hshape 	shp_ptr_;
		CcSemaphore shp_sem_;
		float		curr_x_;
		float 		curr_y_;
		float 		curr_z_;
		float 		orig_x_;
		float		orig_y_;
		float 		color_[4];
		int			filled_;
		float 		height_;
		float 		width_;

};


	}
}
#endif
