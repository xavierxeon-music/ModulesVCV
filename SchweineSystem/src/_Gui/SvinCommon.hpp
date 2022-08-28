#ifndef SvinCommonHPP
#define SvinCommonHPP

#include "SvinCommon.h"

// ElementList

template <typename ElementType>
Svin::ElementList<ElementType>::ElementList(Module* module)
   : module(module)
   , instanceList()
{
}

template <typename ElementType>
void Svin::ElementList<ElementType>::append(const std::vector<uint16_t>& paramIndexList)
{
   for (const uint16_t paramIndex : paramIndexList)
   {
      ElementType element(module, paramIndex);
      instanceList.push_back(element);
   }
}

template <typename ElementType>
ElementType* Svin::ElementList<ElementType>::operator[](const uint16_t& index)
{
   return &instanceList[index];
}

// TwoParamElementList

template <typename ElementType>
Svin::TwoParamElementList<ElementType>::TwoParamElementList(Module* module)
   : module(module)
   , instanceList()
{
}

template <typename ElementType>
void Svin::TwoParamElementList<ElementType>::append(const typename Params::List& paramsList)
{
   for (const Params& params : paramsList)
   {
      ElementType element(module, params.paramA, params.paramB);
      instanceList.push_back(element);
   }
}

template <typename ElementType>
ElementType* Svin::TwoParamElementList<ElementType>::operator[](const uint16_t& index)
{
   return &instanceList[index];
}

#endif // NOT SvinCommonHPP
