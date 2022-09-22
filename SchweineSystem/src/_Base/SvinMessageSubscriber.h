#ifndef SvinMessageSubscriberH
#define SvinMessageSubscriberH

#include <SvinMessage.h>

namespace Svin
{
   class Module;

   template <typename MessageType>
   class Message::Subscriber
   {
   public:
      inline Subscriber(Module* module);

   protected:
      void processBuffer();
      virtual void receive(const MessageType& message, Module* sender) = 0;

   private:
      Module* module;
   };
} // namespace Svin

#ifndef SvinMessageSubscriberHPP
#include "SvinMessageSubscriber.hpp"
#endif // NOT SvinMessageSubscriberHPP

#endif // NOT SvinMessageSubscriberH
