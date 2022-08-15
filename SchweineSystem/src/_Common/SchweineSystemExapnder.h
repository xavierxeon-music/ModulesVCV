#ifndef SchweineSystemExapnderH
#define SchweineSystemExapnderH

#include <SchweineSystemModule.h>

namespace SchweineSystem
{

   template <typename MessageType>
   class Exapnder
   {
   public:
      Exapnder(Module* module);
      ~Exapnder();

   protected:
      bool hasExpanderToLeft();
      bool hasExpanderToRight();

      void sendToLeft(const MessageType& message);
      void sendToRight(const MessageType& message);

      MessageType receiveFromLeft();
      MessageType receiveFromRight();

   private:
      using InstanceList = std::list<rack::Module*>;

   private:
      static InstanceList instanceList;
      Module* module;
   };
} // namespace SchweineSystem

#ifndef SchweineSystemExapnderHPP
#include "SchweineSystemExapnder.hpp"
#endif // NOT SchweineSystemExapnderHPP

#endif // NOT SchweineSystemExapnderH
