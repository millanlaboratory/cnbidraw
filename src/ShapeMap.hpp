#ifndef CNBIDRAW_SHAPE_MAP_HPP
#define CNBIDRAW_SHAPE_MAP_HPP

#include <map>
#include <unordered_map>

#include "Flags.hpp"
#include "Shape.hpp"

namespace cnbi {
	namespace draw {

typedef std::unordered_map<std::string, Shape*> MShape;
typedef std::unordered_map<std::string, Shape*>::iterator MShapeIt;

typedef std::map<unsigned int, std::string> MOrder;
typedef std::map<unsigned int, std::string>::iterator MOrderIt;
typedef std::map<unsigned int, std::string>::reverse_iterator MOrderRIt;

class ShapeMap {
	
	public:
		ShapeMap(void);
		~ShapeMap(void);

		bool Emplace(const std::string& name, Shape* shp);
		bool Erase(const std::string& name);
		bool Exists(const std::string& name);
		unsigned int Size(void);
		bool Empty(void);
		bool SwitchPosition(const std::string& name1, const std::string& name2);
		bool SwitchPosition(MOrderIt it1, MOrderIt it2);
		bool Up(const std::string& name);
		bool Down(const std::string& name);
		bool Top(const std::string& name);
		bool Bottom(const std::string& name);

		MShapeIt FindShape(const std::string& name);
		MOrderIt FindOrder(const std::string& name);
		MOrderIt FindOrder(const unsigned int key);
		
		void Consolidate(void);
		void Dump(void);
		
		MShapeIt  BeginShape(void);
		MShapeIt  EndShape(void);

		MOrderIt  BeginOrder(void);
		MOrderIt  EndOrder(void);
		MOrderRIt RBeginOrder(void);
		MOrderRIt REndOrder(void);
		
	private:

	private:
		MShape	map_shape_;
		MOrder	map_order_;

};

	}
}
#endif

