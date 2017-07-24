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
    this->eng_sem_.Wait();
    if(this->IsRunning())
		this->Stop();
    this->eng_sem_.Post();
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


bool Engine::Add(const std::string& name, Shape* shp, bool overwrite) {
   
    bool retcod = true;	
    
    this->shps_sem_.Wait();
    
    if(this->shps_.Exists(name) && overwrite == true)
	retcod = this->shps_.Erase(name);
    
    if(retcod == true)
	retcod = this->shps_.Emplace(name, shp);
    
    this->shps_sem_.Post();
    
    return retcod;
}

bool Engine::Remove(const std::string& name) {
    bool retcod = false;	
    
    this->shps_sem_.Wait();
    retcod = this->shps_.Erase(name);
    this->shps_sem_.Post();
    return retcod;
}

bool Engine::Raise(const std::string& name) {
    bool retcod;
    this->shps_sem_.Wait();
    retcod = this->shps_.Up(name);
    this->shps_sem_.Post();
    return retcod;
}

bool Engine::Lower(const std::string& name) {
    bool retcod;
    this->shps_sem_.Wait();
    retcod = this->shps_.Down(name);	
    this->shps_sem_.Post();
    return retcod;
}

bool Engine::LowerBottom(const std::string& name) {
    bool retcod;
    this->shps_sem_.Wait();
    retcod = this->shps_.Bottom(name);	
    this->shps_sem_.Post();
    return retcod;
}

bool Engine::RaiseTop(const std::string& name) {
    bool retcod;
    this->shps_sem_.Wait();
    retcod = this->shps_.Top(name);	
    this->shps_sem_.Post();
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
		CcTime::Sleep(1000.0f/this->GetRefresh());
    }
    
    this->CloseWindow();
}

void Engine::Render(void) {
	MShapeIt shpIt;
    
	this->shps_sem_.Wait();
    for(auto ordIt = this->shps_.BeginOrder(); ordIt != this->shps_.EndOrder(); ++ordIt) {
	
		shpIt = this->shps_.FindShape(ordIt->second);	
	
		if(shpIt == this->shps_.EndShape())
			continue;
	
		shpIt->second->Draw();
	}
	this->shps_sem_.Post();
}

void Engine::Refresh(void) {
	this->ClearWindow();
	this->UpdateWindow();
}

void Engine::Dump(void) {
	this->shps_sem_.Wait();
    this->shps_.Dump();
	this->shps_sem_.Post();
}

    }
}
#endif
