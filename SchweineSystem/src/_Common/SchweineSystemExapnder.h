#ifndef SchweineSystemExapnderH
#define SchweineSystemExapnderH

#include <SchweineSystemModule.h>

namespace SchweineSystem
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
} // namespace SchweineSystem

#ifndef SchweineSystemExapnderHPP
#include "SchweineSystemExapnder.hpp"
#endif // NOT SchweineSystemExapnderHPP

#endif // NOT SchweineSystemExapnderH
