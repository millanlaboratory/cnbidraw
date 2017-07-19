#ifndef CNBIDRAW_ENGINE_HPP
#define CNBIDRAW_ENGINE_HPP

#include <memory>
#include <unordered_map>

#include <drawtk.h>
#include <cnbicore/CcBasic.hpp>
#include <cnbicore/CcThread.hpp>

#include "Flags.hpp"
#include "Window.hpp"
#include "Shape.hpp"

namespace cnbi {
	namespace draw {

typedef std::unordered_map<std::string, Shape*> ShapesMap;
typedef std::unordered_map<std::string, Shape*>::iterator ShapesMapIt;
typedef std::unordered_map<std::string, Shape*>::const_iterator ShapesMapConstIt;

class Engine : public CcThread, public Window {
	
	public:
		Engine(void);
		Engine(const std::string& caption, unsigned int width, unsigned int height);
		virtual ~Engine(void);

		void  Open(void);
		void  SetRefresh(float refresh);
		float GetRefresh(void);

		bool Exists(const std::string& name);
		bool AddShape(const std::string& name, Shape* shp, bool overwrite = true);
		bool RemoveShape(const std::string& name);

	protected:
		void Main(void);
		void Render(void);

	private:
		CcSemaphore		shps_map_sem_;
		CcSemaphore		eng_sem_;

		ShapesMap 	shps_map_;
		float 		refresh_;
};

	}
}


#endif
