#ifndef CNBIDRAW_FONT_HPP
#define CNBIDRAW_FONT_HPP

#include <string>
#include <drawtk.h>

#include "Flags.hpp"

namespace cnbi {
    namespace draw {

class String;

/*! \brief Font class
 *
 * Font class to load system fonts.
 * \sa String
 */
class Font {
	/*! \brief This class is friend of String class
	 */
	friend String;

    public:
		/*! \brief Constructor
		 *	Constructor that load a system font via fontname. If the font
		 *	cannot be found the default one will be loaded ("arial:style=bold").
		 *
		 *	Example of fontname: "arial:style=italic"
		 *
		 * \param	name	Fontname and style
		 */
		Font(const std::string& name = CNBIDRAW_FONT_DEFAULT);
		
		/*! \brief Destructor
		 */
		virtual ~Font(void);

		/*! \brief Load a system font
		 *	It loads a system font via fontname. 
		 *	Example: "arial:style=bold"
		 *
		 * \param	name	Fontname and style
		 * \return	True if the font is loaded, false otherwise
		 */
		bool Load(const std::string& name);	
		
		/*! \brief Destroy method
		 */
		void Destroy(void);

	private:
		std::string name_;
		dtk_hfont	font_;
};
    }
}
#endif
