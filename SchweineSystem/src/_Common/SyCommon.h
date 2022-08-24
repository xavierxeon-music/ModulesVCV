#ifndef SyCommonH
#define SyCommonH

#include <rack.hpp>

#include <Midi/MidiCommon.h>

namespace Sy
{   
   struct Color
   {
      uint8_t red;
      uint8_t green;
      uint8_t blue;
   };

   struct Common
   {
      using MidiInterfaceMap = std::map<Midi::Device::Channel, std::string>;
      static const MidiInterfaceMap midiInterfaceMap;
   };

   class Module;

   template <typename ElementType>
   class OneParamElementList
   {
   public:
      OneParamElementList(Module* module);

   public:
      void append(const std::vector<uint16_t>& indexList);
      ElementType* operator[](const uint16_t& index);

   private:
      Module* module;
      std::vector<ElementType> instanceList;
   };

   template <typename ElementType>
   class TwoParamElementList
   {
   public:
      struct Params
      {
         uint16_t paramA;
         uint16_t paramB;

         using List = std::vector<Params>;
      };

   public:
      TwoParamElementList(Module* module);

   public:
      void append(const typename Params::List& paramsList);
      ElementType* operator[](const uint16_t& index);

   private:
      Module* module;
      std::vector<ElementType> instanceList;
   };

   // ************************************************

   template <typename ContentType>
   class SubList
   {
   public:
      explicit SubList(std::vector<ContentType>& fullList);

   public:
      void append(const std::vector<uint16_t>& idList);
      ContentType* operator[](const uint16_t& index);

   private:
      std::vector<ContentType>& fullList;
      std::vector<uint16_t> idMappingList;
   };

   namespace Input
   {
      using List = SubList<rack::engine::Input>;
   }

   namespace Output
   {
      using List = SubList<rack::engine::Output>;
   }

   // ************************************************

} // namespace Sy

inline void makeInput(rack::ModuleWidget* widget, rack::math::Vec pos, int inputId, bool black = false)
{
   rack::app::PortWidget* portWidget = nullptr;
   if (black)
      portWidget = rack::createInputCentered<rack::PJ3410Port>(pos, widget->getModule(), inputId);
   else
      portWidget = rack::createInputCentered<rack::PJ301MPort>(pos, widget->getModule(), inputId);
   widget->addInput(portWidget);
}

inline void makeOutput(rack::ModuleWidget* widget, rack::math::Vec pos, int outputId, bool black = false)
{
   rack::app::PortWidget* portWidget = nullptr;
   if (black)
      portWidget = rack::createOutputCentered<rack::PJ3410Port>(pos, widget->getModule(), outputId);
   else
      portWidget = rack::createOutputCentered<rack::PJ301MPort>(pos, widget->getModule(), outputId);
   widget->addOutput(portWidget);
}

#ifndef SyCommonHPP
#include "SyCommon.hpp"
#endif // NOT SyCommonHPP

#endif // NOT SyCommonH
