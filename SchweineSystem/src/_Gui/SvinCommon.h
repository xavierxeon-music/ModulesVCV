#ifndef SvinCommonH
#define SvinCommonH

#include <MusicTools.h>

namespace Svin
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

} // namespace Svin


#ifndef SvinCommonHPP
#include "SvinCommon.hpp"
#endif // NOT SvinCommonHPP

#endif // NOT SvinCommonH
