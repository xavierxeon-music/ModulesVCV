#include "BitBusCommon.h"

#include "SchweineSystem.h"

BitBusCommon::ModelMap BitBusCommon::outputMap = BitBusCommon::ModelMap();
BitBusCommon::ModelMap BitBusCommon::inputMap = BitBusCommon::ModelMap();

BitBusCommon::BitBusCommon(Module* module)
   : module(module)
{
   module->rightExpander.producerMessage = new Message{};
   module->rightExpander.consumerMessage = new Message{};

   module->leftExpander.producerMessage = new Message{};
   module->leftExpander.consumerMessage = new Message{};
}

BitBusCommon::~BitBusCommon()
{
   module->rightExpander.producerMessage = nullptr;
   module->rightExpander.consumerMessage = nullptr;

   module->leftExpander.producerMessage = nullptr;
   module->leftExpander.consumerMessage = nullptr;
}

void BitBusCommon::registerBusOutput()
{
   Model* myModel = module->getModel();
   outputMap[myModel] = true;
}

bool BitBusCommon::canSendBusMessage()
{
   Model* myModel = module->getModel();
   if (!contains(outputMap, myModel))
      return false;

   Module* expanderModule = module->rightExpander.module;
   if (!expanderModule)
      return false;

   if (!contains(inputMap, expanderModule->model))
      return false;

   return true;
}

void BitBusCommon::registerBusInput()
{
   Model* myModel = module->getModel();
   inputMap[myModel] = true;
}

void BitBusCommon::sendByteToBus(const uint8_t& byte)
{
   Module* expanderModule = module->rightExpander.module;
   Module::Expander& target = expanderModule->leftExpander;

   Message* busMessage = reinterpret_cast<Message*>(target.producerMessage);
   busMessage->byte = byte;

   target.requestMessageFlip();
}

bool BitBusCommon::canReceiveBusMessage()
{
   Model* myModel = module->getModel();
   if (!contains(inputMap, myModel))
      return false;

   Module* expanderModule = module->leftExpander.module;
   if (!expanderModule)
      return false;

   if (!contains(outputMap, expanderModule->model))
      return false;

   return true;
}

uint8_t BitBusCommon::getByteFromBus()
{
   Module::Expander& source = module->leftExpander;

   Message* busMessage = reinterpret_cast<Message*>(source.consumerMessage);
   return busMessage->byte;
}

bool BitBusCommon::contains(ModelMap& map, Model* model)
{
   try
   {
      const bool value = map.at(model);
      return value;
   }
   catch (std::out_of_range e)
   {
      map[model] = false;
      return true;
   }

   return true;
}
