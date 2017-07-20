#ifndef CNBIDRAW_SHAPE_MAP_CPP
#define CNBIDRAW_SHAPE_MAP_CPP

#include "ShapeMap.hpp"

namespace cnbi {
	namespace draw {

ShapeMap::ShapeMap(void) {}
ShapeMap::~ShapeMap(void) {}

bool ShapeMap::Emplace(const std::string& name, Shape* shp) {

	std::pair<MShapeIt, bool> retshp;
	std::pair<MOrderIt, bool> retord;

	// Try to emplace Shape* to the shapes map 
	retshp = this->map_shape_.emplace(name, shp);

	// If added, try to emplace the new element in the order map
	if(retshp.second == true)
		retord = this->map_order_.emplace(this->map_shape_.size()-1, name);

	return retshp.second & retord.second;
}

bool ShapeMap::Erase(const std::string& name) {

	unsigned int nerased_shp;	
	unsigned int nerased_ord;	
	MOrderIt it;

	nerased_shp = this->map_shape_.erase(name);

	if(nerased_shp != 1)
		return false;
	
	it = this->FindOrder(name);
	if(it == this->map_order_.end())
		return false;

	nerased_ord = this->map_order_.erase(it->first);
	if(nerased_ord !=1)
		return false;

	this->Consolidate();

	return true;
}

unsigned int ShapeMap::Size(void) {
	return this->map_shape_.size();
}

MShapeIt ShapeMap::FindShape(const std::string& name) {
	return this->map_shape_.find(name);
}

MOrderIt ShapeMap::FindOrder(const std::string& name) {
	
	MOrderIt retIt = this->map_order_.end();	

	for(auto it=this->map_order_.begin(); it!=this->map_order_.end(); ++it) {
		if(name.compare(it->second) == 0) {
			retIt = it;
			break;
		}
	}

	return retIt;
}

MOrderIt ShapeMap::FindOrder(const unsigned int key) {
	return this->map_order_.find(key);
}

bool ShapeMap::Exists(const std::string& name) {
	auto shpit = this->FindShape(name);
	auto ordit = this->FindOrder(name);

	return (shpit != this->map_shape_.end()) & (ordit != this->map_order_.end());
}

void ShapeMap::Consolidate(void) {

   unsigned int key = 0;
   MOrder local(this->map_order_);
   this->map_order_.clear();

   for(auto it=local.begin(); it!=local.end(); ++it) {
      this->map_order_.emplace(key, it->second);
      key++;
   }
}

bool ShapeMap::SwitchPosition(const std::string& name1, const std::string& name2) {

	MOrderIt it1, it2;
	bool found1, found2;

	it1 = this->FindOrder(name1);
	it2 = this->FindOrder(name2);

	found1 = it1 != this->map_order_.end();
	found2 = it2 != this->map_order_.end();

	if(found1 == false || found2 == false)
		return false;

	return this->SwitchPosition(it1, it2);
}

bool ShapeMap::SwitchPosition(MOrderIt it1, MOrderIt it2) {
	
	unsigned int key1, key2;
	std::string name1, name2;
	std::pair<MOrderIt, bool> ret1;
	std::pair<MOrderIt, bool> ret2;
	
	key1  = it1->first;
	key2  = it2->first;
	name1 = it1->second;
	name2 = it2->second;

	this->map_order_.erase(it1);
	this->map_order_.erase(it2);

	ret1 = this->map_order_.emplace(key1, name2);
	ret2 = this->map_order_.emplace(key2, name1);

	return ret1.second & ret2.second;
}

bool ShapeMap::Up(const std::string& name) {
	
	MOrderIt it1, it2;
	bool found1, found2;

	it1 = this->FindOrder(name);
	it2 = this->FindOrder(it1->first+1);

	found1 = it1 != this->map_order_.end();
	found2 = it2 != this->map_order_.end();
	
	if(found1 == false || found2 == false)
		return false;

	return this->SwitchPosition(it1, it2);

}

bool ShapeMap::Down(const std::string& name) {
	
	MOrderIt it1, it2;
	bool found1, found2;

	it1 = this->FindOrder(name);
	it2 = this->FindOrder(it1->first-1);

	found1 = it1 != this->map_order_.end();
	found2 = it2 != this->map_order_.end();
	
	if(found1 == false || found2 == false)
		return false;

	return this->SwitchPosition(it1, it2);
}

bool ShapeMap::Top(const std::string& name) {

	bool retcod;
	retcod = this->Up(name);

	if(retcod == true)
		retcod = this->Top(name);

	return retcod;
}

bool ShapeMap::Bottom(const std::string& name) {

	bool retcod;
	retcod = this->Down(name);

	if(retcod == true)
		retcod = this->Bottom(name);

	return retcod;
}

bool ShapeMap::Empty(void) {
	return this->Size() == 0 ? true : false;
}

void ShapeMap::Dump(void) {

	if(this->Empty()) {
		printf("[shapemap] - No elements in the container\n");
		return;
	}

	printf("[shapemap] - Dumping elements in the container:\n");
	for(auto it = this->RBeginOrder(); it != this->REndOrder(); ++it)
		printf("           |- %d / %s\n", it->first, it->second.c_str());
}

MShapeIt ShapeMap::BeginShape(void) {
	return this->map_shape_.begin();
}

MShapeIt ShapeMap::EndShape(void) {
	return this->map_shape_.end();
}

MOrderIt ShapeMap::BeginOrder(void) {
	return this->map_order_.begin();
}

MOrderIt ShapeMap::EndOrder(void) {
	return this->map_order_.end();
}

MOrderRIt ShapeMap::RBeginOrder(void) {
	return this->map_order_.rbegin();
}

MOrderRIt ShapeMap::REndOrder(void) {
	return this->map_order_.rend();
}
	}
}

#endif
