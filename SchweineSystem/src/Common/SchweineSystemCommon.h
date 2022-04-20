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

#ifndef SchweineSystemCommonHPP
#include "SchweineSystemCommon.hpp"
#endif // NOT SchweineSystemCommonHPP

#endif // NOT SchweineSystemCommonH
