#ifndef SvinExapnderH
#define SvinExapnderH

#include <SvinModule.h>

namespace Svin
{
   struct Direction
   {
      bool left = false;
      bool right = false;
   };

   template <typename MessageType>
   class Exapnder
   {
   public:
      Exapnder(Module* module);
      ~Exapnder();

   public:
      bool canCommunicatWithLeft();
      bool canCommunicatWithRight();

   protected:
      void allowExpanderOnLeft();
      void allowExpanderOnRight();

      void sendToLeft(const MessageType& message);
      void sendToRight(const MessageType& message);

      MessageType receiveFromLeft();
      MessageType receiveFromRight();

   private:
      using InstanceMap = std::map<rack::Module*, Direction>;

   private:
      static InstanceMap instanceMap;
      Module* module;
   };
} // namespace Svin

#ifndef SvinExapnderHPP
#include "SvinExpander.hpp"
#endif // NOT SvinExapnderHPP

#endif // NOT SvinExapnderH
