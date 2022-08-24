#ifndef SyCommonHPP
#define SyCommonHPP

#include "SyCommon.h"

// OneParamElementList

template <typename ElementType>
Sy::OneParamElementList<ElementType>::OneParamElementList(Module* module)
   : module(module)
   , instanceList()
{
}

template <typename ElementType>
void Sy::OneParamElementList<ElementType>::append(const std::vector<uint16_t>& paramIndexList)
{
   for (const uint16_t paramIndex : paramIndexList)
   {
      ElementType element(module, paramIndex);
      instanceList.push_back(element);
   }
}

template <typename ElementType>
ElementType* Sy::OneParamElementList<ElementType>::operator[](const uint16_t& index)
{
   return &instanceList[index];
}

// TwoParamElementList

template <typename ElementType>
Sy::TwoParamElementList<ElementType>::TwoParamElementList(Module* module)
   : module(module)
   , instanceList()
{
}

template <typename ElementType>
void Sy::TwoParamElementList<ElementType>::append(const typename Params::List& paramsList)
{
   for (const Params& params : paramsList)
   {
      ElementType element(module, params.paramA, params.paramB);
      instanceList.push_back(element);
   }
}

template <typename ElementType>
ElementType* Sy::TwoParamElementList<ElementType>::operator[](const uint16_t& index)
{
   return &instanceList[index];
}

// ************************************************

template <typename ContentType>
Sy::SubList<ContentType>::SubList(std::vector<ContentType>& fullList)
   : fullList(fullList)
{
}

template <typename ContentType>
void Sy::SubList<ContentType>::append(const std::vector<uint16_t>& idList)
{
   idMappingList.insert(idMappingList.end(), idList.begin(), idList.end());
}

template <typename ContentType>
ContentType* Sy::SubList<ContentType>::operator[](const uint16_t& index)
{
   const uint8_t fullIndex = idMappingList.at(index);
   ContentType* value = &fullList[fullIndex];
   return value;
}

#endif // NOT SyCommonHPP
