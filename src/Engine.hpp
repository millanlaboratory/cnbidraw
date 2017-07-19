#ifndef CNBIDRAW_ENGINE_HPP
#define CNBIDRAW_ENGINE_HPP

#include <memory>
#include <map>
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
typedef std::map<unsigned int, std::string> ShapesOrder;

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

      bool RaiseShape(const std::string& name);
      bool LowerShape(const std::string& name);
      
      void Dump(void);

   protected:
      void Main(void);
      void Render(void);
   
   private:
      void shps_order_emplace(const std::string& name);
      void shps_order_erase(const std::string& name);
      bool shps_order_find(const std::string& name, unsigned int* key);
      void shps_order_consolidate(void);
      void shps_order_up(const std::string& name);
      void shps_order_down(const std::string& name);

   private:
      CcSemaphore shps_map_sem_;
      CcSemaphore eng_sem_;
      
      ShapesMap	  shps_map_;
      ShapesOrder shps_order_;
      float	  refresh_;
};

   }
}


#endif
