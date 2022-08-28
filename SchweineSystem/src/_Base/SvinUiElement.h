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

      template <typename ContentType>
      class ElementMap : protected Base
      {
      public:
         class Access : protected Base
         {
         public:
            Access(Module* module, const uint16_t identifier);

         public:
            ContentType* findElement() const;
         };

      public:
         ElementMap(Module* module, const uint16_t identifier, ContentType* content);
         virtual ~ElementMap();

      private:
         //friend class Access<ContentType>;
         using IdMap = std::map<const uint16_t, ContentType*>;
         using ContentMap = std::map<Module*, IdMap>;

      private:
         static ContentMap instances;
      };
   } // namespace UiElement

} // namespace Svin

#ifndef SvinUiElementHPP
#include "SvinUiElement.hpp"
#endif // NOT SvinUiElementHPP

#endif // NOT SvinUiElementH
