#ifndef BitBusCommonH
#define BitBusCommonH

#include <rack.hpp>
using namespace rack;

class BitBusCommon
{
public:
   BitBusCommon(Module* module);
   virtual ~BitBusCommon();

protected:
   void registerBusOutput();
   bool canSendBusMessage(); // has module with bus output on the left and this module is registered as bus input
   void sendByteToBus(const uint8_t& byte);

   void registerBusInput();
   bool canReceiveBusMessage(); // has module with bus input on the right and this module isregistered as bus output
   uint8_t getByteFromBus();

private:
   using ModelMap = std::map<Model*, bool>;
   struct Message
   {
      uint8_t byte;
   };

private:
   bool contains(ModelMap& map, Model* model);

private:
   static ModelMap outputMap;
   static ModelMap inputMap;
   Module* module;
};

#endif // NOT BitBusCommonH
