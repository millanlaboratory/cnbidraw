#ifndef CNBIDRAW_ENGINE_HPP
#define CNBIDRAW_ENGINE_HPP

#include <drawtk.h>
#include <cnbicore/CcBasic.hpp>
#include <cnbicore/CcThread.hpp>

#include "Flags.hpp"
#include "Window.hpp"
#include "Shape.hpp"
#include "ShapeMap.hpp"

namespace cnbi {
   namespace draw {

class Engine : public CcThread, public Window {
	
   public:
      Engine(void);
      Engine(const std::string& caption, unsigned int width, unsigned int height);
      virtual ~Engine(void);
      
      void  Open(void);
      void  SetRefresh(float refresh);
      float GetRefresh(void);
     
      bool Add(const std::string& name, Shape* shp, bool overwrite = true);
      bool Remove(const std::string& name);
      bool Raise(const std::string& name);
      bool RaiseTop(const std::string& name);
      bool Lower(const std::string& name);
      bool LowerBottom(const std::string& name);
      
      void Dump(void);

   protected:
      void Main(void);
      void Render(void);

   private:
      CcSemaphore shps_sem_;
      CcSemaphore eng_sem_;
     
	  ShapeMap	shps_;
      float		refresh_;
};

   }
}


#endif
