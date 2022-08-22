#ifndef SyExapnderH
#define SyExapnderH

#include <SyModule.h>

namespace Sy
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

   protected:
      void allowExpanderOnLeft();
      void allowExpanderOnRight();

      bool canCommunicatWithLeft();
      bool canCommunicatWithRight();

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
} // namespace Sy

#ifndef SyExapnderHPP
#include "SyExapnder.hpp"
#endif // NOT SyExapnderHPP

#endif // NOT SyExapnderH
