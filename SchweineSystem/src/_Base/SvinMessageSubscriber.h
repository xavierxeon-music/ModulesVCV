#ifndef SvinMessageSubscriberH
#define SvinMessageSubscriberH

#include <SvinMessage.h>

#include <mutex>

namespace Svin
{
   class Module;

   template <typename MessageType>
   class Message<MessageType>::Subscriber
   {
   public:
      inline Subscriber(Module* module);
      inline ~Subscriber();

   protected:
      void processMessageBuffer();
      virtual void receiveMessage(const MessageType& message, Module* sender) = 0;

   private:
      friend class Publisher;
      struct Stack
      {
         const MessageType message;
         Module* sender;

         using List = std::list<Stack>;
      };

   private:
      void queue(const MessageType& message, Module* sender);

   private:
      Module* module;
      typename Stack::List stackList;
      mutable std::mutex mutex;
   };
} // namespace Svin

#ifndef SvinMessageSubscriberHPP
#include "SvinMessageSubscriber.hpp"
#endif // NOT SvinMessageSubscriberHPP

#endif // NOT SvinMessageSubscriberH
