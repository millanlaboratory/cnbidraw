#ifndef CNBIDRAW_STRING_HPP
#define CNBIDRAW_STRING_HPP

#include "Shape.hpp"

namespace cnbi {
	namespace draw {

class String : public Shape {

	public:
		String(const std::string& text, float size, const float* color);
		virtual ~String(void);

		virtual void Create(void);


		bool SetFormat(const std::string& format);
		void SetAlign(unsigned int align);
		void SetSize(float size);

	public:
		static const unsigned int ToBottom = DTK_BOTTOM;
		static const unsigned int ToMiddle = DTK_VMID;
		static const unsigned int ToTop	   = DTK_TOP;
		static const unsigned int ToLeft   = DTK_RIGHT;
		static const unsigned int ToCenter = DTK_HMID;
		static const unsigned int ToRight  = DTK_LEFT;

	private:
		dtk_hfont		str_font_;
		std::string		str_format_;
		unsigned int	str_align_;
		std::string		str_text_;
		float			str_size_;
};


	}
}

#endif

