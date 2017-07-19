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
   
   if(this->Exists(name) && overwrite == true)
      this->RemoveShape(name);
   
   this->shps_map_sem_.Wait();
   auto retmap = this->shps_map_.emplace(name, shp);
   this->shps_order_emplace(name);
   this->shps_map_sem_.Post();
   
   return retmap.second;
}

bool Engine::RemoveShape(const std::string& name) {
   bool retcod = false;	

   if(this->Exists(name)) {
      this->shps_map_sem_.Wait();
      auto it = this->shps_map_.find(name);
      this->shps_map_.erase(name);
      this->shps_order_erase(name);
      this->shps_order_consolidate();
      this->shps_map_sem_.Post();
      retcod = true;
   } 
   return retcod;
}

bool Engine::RaiseShape(const std::string& name) {
   bool retcod = false;	

   if(this->Exists(name)) {
      this->shps_map_sem_.Wait();
      this->shps_order_up(name);
      this->shps_map_sem_.Post();
      retcod = true;
   } 
   return retcod;
}

bool Engine::LowerShape(const std::string& name) {
   bool retcod = false;	

   if(this->Exists(name)) {
      this->shps_map_sem_.Wait();
      this->shps_order_down(name);
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

void Engine::Dump(void) {
   printf("[Engine] - Dump shape list: \n");
   for(auto it=this->shps_order_.begin(); it != this->shps_order_.end(); ++it) {
      printf("         |+ (%d) %s\n", it->first, it->second.c_str());
   }
}

void Engine::shps_order_emplace(const std::string& name) {
   this->shps_order_.emplace(this->shps_map_.size()-1, name);
}

void Engine::shps_order_erase(const std::string& name) {
   unsigned int key;
   if(this->shps_order_find(name, &key))
      this->shps_order_.erase(key);
}

void Engine::shps_order_consolidate(void) {
   unsigned int key = 0;
   ShapesOrder lmap(this->shps_order_);
   this->shps_order_.clear();

   for(auto it=lmap.begin(); it!=lmap.end(); ++it) {
      this->shps_order_.emplace(key, it->second);
      key++;
   }
}

bool Engine::shps_order_find(const std::string& name, unsigned int* key) {
   bool retcod = false;
   for(auto it=this->shps_order_.begin(); it!=this->shps_order_.end(); ++it) {
      if(name.compare(it->second) == 0) {
	 *key = it->first;
	 retcod = true;
      }
   }
   return retcod; 
}

void Engine::shps_order_up(const std::string& name) {
   unsigned int key;
   std::string  other_name;
  
   if(this->shps_order_find(name, &key) == false)
      return;

   auto it = this->shps_order_.find(key+1);

   if(it == this->shps_order_.end())
      return;
  
   other_name = it->second;

   this->shps_order_.erase(key);
   this->shps_order_.erase(key+1);

   this->shps_order_.emplace(key, other_name);
   this->shps_order_.emplace(key+1, name);
}

void Engine::shps_order_down(const std::string& name) {
   unsigned int key;
   std::string  other_name;
  
   if(this->shps_order_find(name, &key) == false)
      return;

   auto it = this->shps_order_.find(key-1);

   if(it == this->shps_order_.end())
      return;
  
   other_name = it->second;

   this->shps_order_.erase(key);
   this->shps_order_.erase(key-1);

   this->shps_order_.emplace(key, other_name);
   this->shps_order_.emplace(key-1, name);
}

   }
}
#endif
