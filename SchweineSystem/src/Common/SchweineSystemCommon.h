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

} // namespace SchweineSystem

inline void makeButton(rack::ModuleWidget* widget, rack::math::Vec pos, int paramId, int firstLightId)
{
   rack::app::ParamWidget* paramWidget = rack::createLightParamCentered<rack::VCVLightBezel<rack::RedGreenBlueLight>>(pos, widget->getModule(), paramId, firstLightId);
   widget->addParam(paramWidget);
}

inline void makeKnob(rack::ModuleWidget* widget, rack::math::Vec pos, int paramId)
{
   rack::app::ParamWidget* paramWidget = rack::createParamCentered<rack::RoundSmallBlackKnob>(pos, widget->getModule(), paramId);
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
