#ifndef CNBIDRAW_STRING_HPP
#define CNBIDRAW_STRING_HPP

#include "Shape.hpp"
#include "Font.hpp"

namespace cnbi {
	namespace draw {

/*! \brief String class
 *
 * Implements a string shape.
 * \sa Font
 */
class String : public Shape {

	public:
		/*! \brief Constructor
		 *
		 * Full constructor with string's text
		 *
		 * \param	text	String's text
		 * \param	size	String's size
		 * \param	color	String's color
		 */
		String(const std::string& text, float size, const float* color);
		
		/*! \brief Constructor
		 *
		 * Partial constructor withour string's text (to be set with SetText
		 * method)
		 *
		 * \param	size	String's size
		 * \param	color	String's color
		 */
		String(float size, const float* color);
		
		/*! \brief Destructor
		 */
		virtual ~String(void);

		/*! \brief Creation method
		 * It actually creates the shape by using dtk_create_shape
		 * functionalities. Call to String::SetFont method should happen before
		 * the creation of the shape.
		 */
		virtual void Create(void);

		/*! \brief Set font method
		 * It applies the given Font to the current string. It must be called
		 * before the String::Create method.
		 *
		 * \param	font	Pointer to the font object
		 * \return	True if the font is set, false otherwise
		 */
		bool SetFont(Font* font);
		
		/*! \brief Set text method
		 * It set the given text to the current string.
		 *
		 * \param	text	Text of the string
		 */
		void SetText(const std::string& text);
		
		/*! \brief Set align method
		 * It sets the alignement of the string according to the given argument
		 *
		 * \param	align	Types of alignement
		 * \sa String::ToBotton, String::ToMiddle, String::ToTop,
		 * String::ToLeft, String::ToCenter, String::ToRight
		 */
		void SetAlign(unsigned int align);
		
		/*! \brief Set the size of the string
		 *
		 * \param	size	String's size
		 */
		void SetSize(float size);

	public:
		/// Vertical alignment to the bottom
		static const unsigned int ToBottom = DTK_BOTTOM;
		/// \brief Vertical alignment to the middle
		static const unsigned int ToMiddle = DTK_VMID;
		/// \brief Vertical alignment to the top
		static const unsigned int ToTop	   = DTK_TOP;
		/// \brief Horizontal alignment to the right
		static const unsigned int ToLeft   = DTK_RIGHT;
		/// \brief Horizontal alignment to the center
		static const unsigned int ToCenter = DTK_HMID;
		/// \brief Horizontal alignment to the left
		static const unsigned int ToRight  = DTK_LEFT;

	private:
		Font*			font_;
		unsigned int	align_;
		std::string		text_;
		float			size_;
};


	}
}

#endif

