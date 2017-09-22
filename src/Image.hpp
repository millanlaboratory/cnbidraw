#ifndef CNBIDRAW_IMAGE_HPP
#define CNBIDRAW_IMAGE_HPP

#include "Shape.hpp"


namespace cnbi {
	namespace draw {

/*! \brief Image class
 *
 * Implements a image shape.
 */
class Image : public Shape {

	public:
		/*! \brief Constructor
		 * Once set, the image will be resized according to the provided width
		 * and height. The default color is white. By changing the color, the
		 * image color mask will be changed.
		 *
		 * \param	width	Image's frame width
		 * \param	height	Image's frame height
		 * \param	color	Image's color
		 */
		Image(float width, float height, const float* color = dtk_white);
		
		/*! \brief Destructor
		 */
		virtual ~Image(void);

		/*! \brief Creation method
		 * It actually creates the shape by using dtk_create_shape
		 * functionalities. Call to Image::Set method should happen before the
		 * creation of the shape.
		 */
		virtual void Create(void);

		/*! \brief Set method
		 * It loads an external image and it set it as the texture for the
		 * shape.
		 *
		 * \param	filename	Filename (with path) to the image
		 * \param	mxlvl		MipMaps level
		 * \return	True if the image is loaded, false otherwise
		 * */
		bool Set(const std::string& filename, unsigned int mxlvl = CNBIDRAW_IMAGE_DEFAULT_MXLVL);

		/*! \brief Get original size of the image
		 * It gets the original size of the image (in pixels).
		 *
		 * \param[out]	w_px	Original image's width [pixels]
		 * \param[out]	h_px	Original image's height [pixels]
		 * \return	True if the image exists, false otherwise
		 * */
		bool GetSize(unsigned int* w_px, unsigned int* h_px);
	private:
		dtk_htex	img_tex_;
};


	}
}

#endif
