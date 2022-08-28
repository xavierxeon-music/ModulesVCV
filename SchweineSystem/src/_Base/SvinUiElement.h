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

      template <typename ControllerType>
      class View
      {
      public:
         View(Module* module, const uint16_t controllerId);

      public:
         ControllerType* findController() const;

      protected:
         Module* module;
         const uint16_t controllerId;
      };

      template <typename ControllerType>
      class Controller
      {
      public:
         Controller(Module* module, const uint16_t controllerId, ControllerType* controller);
         virtual ~Controller();

      protected:
         Module* module;
         const uint16_t controllerId;

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
