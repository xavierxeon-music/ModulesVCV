#ifndef SvinCommonH
#define SvinCommonH

#include <map>

#include <MusicTools.h>

namespace Svin
{   

   class Module;

   // goups existing elements into a list

   template <typename ElementType>
   class ElementList
   {
   public:
      struct Params
      {
         uint16_t paramA;
         uint16_t paramB;

         using List = std::vector<Params>;
      };

   public:
      ElementList(Module* module);
      ~ElementList();

   public:
      void append(const std::vector<uint16_t>& indexList);  // single id
      void append(const typename Params::List& paramsList); // two ids
      ElementType* operator[](const uint16_t& index);

   private:
      Module* module;
      std::vector<ElementType*> instanceList;
   };

   // keeep list of all instances of a type

   struct Base
   {
      Module* module;
      const uint16_t identifier;
   };

   template <typename InstanceType>
   class InstanceMap : protected Base
   {
   public:
      class Access : protected Base
      {
      public:
         Access(Module* module, const uint16_t identifier);

      public:
         InstanceType* findIntstance() const;
      };

   public:
      InstanceMap(Module* module, const uint16_t identifier, InstanceType* instance);
      virtual ~InstanceMap();

   private:
      //friend class Access<ContentType>;
      using IdMap = std::map<const uint16_t, InstanceType*>;
      using ContentMap = std::map<Module*, IdMap>;

   private:
      static ContentMap instances;
   };

} // namespace Svin


#ifndef SvinCommonHPP
#include "SvinCommon.hpp"
#endif // NOT SvinCommonHPP

#endif // NOT SvinCommonH
