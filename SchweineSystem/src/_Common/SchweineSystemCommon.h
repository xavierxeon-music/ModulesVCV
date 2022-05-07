#ifndef SchweineSystemCommonH
#define SchweineSystemCommonH

#include <rack.hpp>

#include <Midi/MidiCommon.h>

namespace SchweineSystem
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
   class ElementList
   {
   public:
      ElementList(Module* module);

   public:
      void append(const std::vector<uint16_t>& indexList);
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

   namespace Param
   {
      using List = SubList<rack::engine::Param>;
   }

   namespace Input
   {
      using List = SubList<rack::engine::Input>;
   }

   namespace Output
   {
      using List = SubList<rack::engine::Output>;
   }

   // ************************************************

} // namespace SchweineSystem

inline void makeLEDButton(rack::ModuleWidget* widget, rack::math::Vec pos, int paramId, int firstLightId)
{
   rack::app::ParamWidget* paramWidget = rack::createLightParamCentered<rack::VCVLightBezel<rack::RedGreenBlueLight>>(pos, widget->getModule(), paramId, firstLightId);
   widget->addParam(paramWidget);
}

inline void makeButton(rack::ModuleWidget* widget, rack::math::Vec pos, int paramId)
{
   rack::app::ParamWidget* paramWidget = rack::createParamCentered<rack::TL1105>(pos, widget->getModule(), paramId);
   widget->addParam(paramWidget);
}

inline void makeSwitch(rack::ModuleWidget* widget, rack::math::Vec pos, int paramId)
{
   rack::app::ParamWidget* paramWidget = rack::createParamCentered<rack::CKSS>(pos, widget->getModule(), paramId);
   widget->addParam(paramWidget);
}

inline void makeKnob(rack::ModuleWidget* widget, rack::math::Vec pos, int paramId, uint8_t size = 1)
{
   rack::app::ParamWidget* paramWidget = nullptr;
   if (3 == size)
      paramWidget = rack::createParamCentered<rack::RoundHugeBlackKnob>(pos, widget->getModule(), paramId);
   else if (2 == size)
      paramWidget = rack::createParamCentered<rack::RoundBigBlackKnob>(pos, widget->getModule(), paramId);
   else
      paramWidget = rack::createParamCentered<rack::RoundSmallBlackKnob>(pos, widget->getModule(), paramId);
   widget->addParam(paramWidget);
}

inline void makeInput(rack::ModuleWidget* widget, rack::math::Vec pos, int inputId)
{
   rack::app::PortWidget* portWidget = rack::createInputCentered<rack::PJ301MPort>(pos, widget->getModule(), inputId);
   widget->addInput(portWidget);
}

inline void makeOutput(rack::ModuleWidget* widget, rack::math::Vec pos, int outputId)
{
   rack::app::PortWidget* portWidget = rack::createOutputCentered<rack::PJ301MPort>(pos, widget->getModule(), outputId);
   widget->addOutput(portWidget);
}

#ifndef SchweineSystemCommonHPP
#include "SchweineSystemCommon.hpp"
#endif // NOT SchweineSystemCommonHPP

#endif // NOT SchweineSystemCommonH
