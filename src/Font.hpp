#ifndef CNBIDRAW_FONT_HPP
#define CNBIDRAW_FONT_HPP

#include <string>
#include <drawtk.h>

#include "Flags.hpp"

namespace cnbi {
    namespace draw {

class String;

class Font {
	friend String;

    public:
		Font(const std::string& name = CNBIDRAW_FONT_DEFAULT);
		virtual ~Font(void);

		bool Load(const std::string& name);	
		void Destroy(void);

	private:
		std::string name_;
		dtk_hfont	font_;
};
    }
}
#endif
