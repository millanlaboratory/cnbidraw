#ifndef CNBIDRAW_FONT_CPP
#define CNBIDRAW_FONT_CPP

#include "Font.hpp"

namespace cnbi {
    namespace draw {

Font::Font(const std::string& name) {
	this->name_ = name;
	this->font_ = dtk_load_font(name.c_str());
}

Font::~Font(void) {}

bool Font::Load(const std::string& name) {

	bool retcod = false;	
	
	this->Destroy();
	
	this->font_ = dtk_load_font(name.c_str());

	if(this->font_ != nullptr)
		retcod = true;
	
	return retcod;
}

void Font::Destroy(void) {
	if(this->font_ != nullptr)
		dtk_destroy_font(this->font_);
}

	}
}
#endif
