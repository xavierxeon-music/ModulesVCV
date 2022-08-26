#ifndef SyCommonH
#define SyCommonH

#include <MusicTools.h>

namespace Sy
{   
   struct Color
   {
      uint8_t red;
      uint8_t green;
      uint8_t blue;
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

} // namespace Sy


#ifndef SyCommonHPP
#include "SyCommon.hpp"
#endif // NOT SyCommonHPP

#endif // NOT SyCommonH
