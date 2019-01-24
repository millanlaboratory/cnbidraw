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
    int ret;
    this->Close();
    ret = this->Join(); 
    printf("[engine] - Return of Join: %d\n", ret);
}

void Engine::Open(void) {
    if(this->IsRunning() == false)
		this->Start();
}

void Engine::Close(void) {
	std::lock_guard<std::mutex> lock(this->eng_mutex_);
    if(this->IsRunning())
		this->Stop();
}

void Engine::SetRefresh(float refresh) {
	std::lock_guard<std::mutex> lock(this->eng_mutex_);
    this->refresh_ = refresh;
}

float Engine::GetRefresh(void) {
    float refresh;
	std::lock_guard<std::mutex> lock(this->eng_mutex_);
    refresh = this->refresh_;
    return refresh;
}


bool Engine::Add(const std::string& name, Shape* shp, bool overwrite) {
   
    bool retcod = true;	
    
	std::lock_guard<std::mutex> lock(this->shps_mutex_);
    
    if(this->shps_.Exists(name) && overwrite == true)
		retcod = this->shps_.Erase(name);
    
    if(retcod == true)
		retcod = this->shps_.Emplace(name, shp);
    
    return retcod;
}

bool Engine::Remove(const std::string& name) {
    bool retcod = false;	
    
	std::lock_guard<std::mutex> lock(this->shps_mutex_);
    retcod = this->shps_.Erase(name);
    return retcod;
}

bool Engine::Raise(const std::string& name) {
    bool retcod;
	std::lock_guard<std::mutex> lock(this->shps_mutex_);
    retcod = this->shps_.Up(name);
    return retcod;
}

bool Engine::Lower(const std::string& name) {
    bool retcod;
	std::lock_guard<std::mutex> lock(this->shps_mutex_);
    retcod = this->shps_.Down(name);	
    return retcod;
}

bool Engine::LowerBottom(const std::string& name) {
    bool retcod;
	std::lock_guard<std::mutex> lock(this->shps_mutex_);
    retcod = this->shps_.Bottom(name);	
    return retcod;
}

bool Engine::RaiseTop(const std::string& name) {
    bool retcod;
	std::lock_guard<std::mutex> lock(this->shps_mutex_);
    retcod = this->shps_.Top(name);	
    return retcod;
}

void Engine::Main(void) {
    if(!CcThread::IsRunning()) {
       return;
    }
    
    this->OpenWindow();
    
    while(CcThread::IsRunning()) {
		this->ClearWindow();
		this->Render();
		this->UpdateWindow();

		this->ProcessEvents();
		
		CcTime::Sleep(1000.0f/this->GetRefresh());
    }
    
    this->CloseWindow();
}

void Engine::Render(void) {
	MShapeIt shpIt;
    
	std::lock_guard<std::mutex> lock(this->shps_mutex_);
    for(auto ordIt = this->shps_.BeginOrder(); ordIt != this->shps_.EndOrder(); ++ordIt) {
	
		shpIt = this->shps_.FindShape(ordIt->second);	
	
		if(shpIt == this->shps_.EndShape())
			continue;
	
		shpIt->second->Draw();
	}
}

void Engine::Refresh(void) {
	this->ClearWindow();
	this->UpdateWindow();
}

void Engine::Dump(void) {
	std::lock_guard<std::mutex> lock(this->shps_mutex_);
    this->shps_.Dump();
}

    }
}
#endif
