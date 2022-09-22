#ifndef SvinMessageH
#define SvinMessageH

namespace Svin
{
   template <typename MessageType>
   class Message
   {
   public:
      class Publisher;
      class Subscriber;

   private:
      inline Message();
      inline static Message* broker();

   private:
      std::list<Publisher*> publisherList;
      std::list<Subscriber*> subscriberList;
   } // namespace Message
} // namespace Svin

#ifndef SvinMessageHPP
#include "SvinMessage.hpp"
#endif // NOT SvinMessageHPP

#endif // NOT SvinMessageH