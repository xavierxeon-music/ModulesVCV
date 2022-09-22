#ifndef SvinMessagePublisherH
#define SvinMessagePublisherH

#include <SvinMessage.h>

namespace Svin
{
   class Module;

   template <typename MessageType>
   class Message<MessageType>::Publisher
   {
   public:
      inline Publisher(Module* module);

   public:
      inline void publishMessage(const MessageType& message, Module* receiver = nullptr); // if receiver is nullptr, broadcast to all subsribers

   private:
      Module* module;
   };
} // namespace Svin

#ifndef SvinMessagePublisherHPP
#include "SvinMessagePublisher.hpp"
#endif // NOT SvinMessagePublisherHPP

#endif // NOT SvinMessagePublisherH
