#ifndef SvinUiElementH
#define SvinUiElementH

#include <map>

#include <MusicTools.h>

namespace Svin
{
   class Module;

   namespace UiElement
   {
      // the controller is knonw by the module and holds the data to be used by the fes (e.g. widget)

      struct Base
      {
         Module* module;
         const uint16_t identifier;
      };

      template <typename ControllerType>
      class View : protected Base
      {
      public:
         View(Module* module, const uint16_t identifier);

      public:
         ControllerType* findController() const;
      };

      template <typename ControllerType>
      class Controller : protected Base
      {
      public:
         Controller(Module* module, const uint16_t identifier, ControllerType* controller);
         virtual ~Controller();

      private:
         friend class View<ControllerType>;
         using IdMap = std::map<const uint16_t, ControllerType*>;
         using ControllerMap = std::map<Module*, IdMap>;

      private:
         static ControllerMap controllerMap;
      };
   } // namespace UiElement

} // namespace Svin

#ifndef SvinUiElementHPP
#include "SvinUiElement.hpp"
#endif // NOT SvinUiElementHPP

#endif // NOT SvinUiElementH
