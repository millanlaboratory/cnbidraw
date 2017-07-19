#ifndef CNBIDRAW_ENGINE_CPP
#define CNBIDRAW_ENGINE_CPP

#include "Engine.hpp"

namespace cnbi {
	namespace draw {

Engine::Engine(void){
	this->refresh_ = CNBIDRAW_ENGINE_DEFAULT_REFRESH;
}

Engine::Engine(const std::string& caption, unsigned int width, unsigned int height){
	this->SetCaption(caption);
	this->SetGeometry(width, height);
	this->refresh_ = CNBIDRAW_ENGINE_DEFAULT_REFRESH;
}

Engine::~Engine(void) {
	if(this->IsRunning())
		this->Stop();
	
	this->Join();
}

void Engine::Open(void) {
	this->Start();
}

void Engine::SetRefresh(float refresh) {
	this->eng_sem_.Wait();
	this->refresh_ = refresh;
	this->eng_sem_.Post();
}

float Engine::GetRefresh(void) {
	float refresh;
	this->eng_sem_.Wait();
	refresh = this->refresh_;
	this->eng_sem_.Post();
	return refresh;
}

bool Engine::Exists(const std::string& name) {
	bool has;	

	this->shps_map_sem_.Wait();
	auto it = this->shps_map_.find(name);
	has = it != this->shps_map_.end();
	this->shps_map_sem_.Post();

	return has;
}

bool Engine::AddShape(const std::string& name, Shape* shp, bool overwrite) {
	
	if(this->Exists(name) && overwrite == true) {
		this->RemoveShape(name);
	}
	
	this->shps_map_sem_.Wait();
	auto result = this->shps_map_.emplace(name, shp);
	this->shps_map_sem_.Post();

	return result.second;
}

bool Engine::RemoveShape(const std::string& name) {
	bool retcod = false;	

	if(this->Exists(name)) {
		this->shps_map_sem_.Wait();
		auto it = this->shps_map_.find(name);
		this->shps_map_.erase(name);
		this->shps_map_sem_.Post();
		retcod = true;
	} 
	return retcod;
}

void Engine::Main(void) {
	if(!CcThread::IsRunning()) {
		return;
	}

	printf("Creating OpenGL window\n");
	this->OpenWindow();
	
	printf("Starting Engine\n");
	while(CcThread::IsRunning()) {
		this->WaitWindow();
		dtk_clear_screen(this->GetWindowPtr());
		this->Render();
		dtk_update_screen(this->GetWindowPtr());
		this->PostWindow();

		CcTime::Sleep(1000.0f/this->GetRefresh());
	}
	
	printf("Stopped Engine\n");
	this->CloseWindow();
}

void Engine::Render(void) {
	this->shps_map_sem_.Wait();
	for(auto it = this->shps_map_.begin(); it != this->shps_map_.end(); ++it) {
		if(it->second->GetShapePtr() != nullptr)
			dtk_draw_shape(it->second->GetShapePtr());
	}
	this->shps_map_sem_.Post();
}

	}
}
#endif
