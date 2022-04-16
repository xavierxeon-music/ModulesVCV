#ifndef SchweineSystemCommonHPP
#define SchweineSystemCommonHPP

#include "SchweineSystemCommon.h"

template <typename ContentType>
SchweineSystem::SubList<ContentType>::SubList(std::vector<ContentType>& fullList)
   : fullList(fullList)
{
}

template <typename ContentType>
void SchweineSystem::SubList<ContentType>::append(const std::vector<uint16_t>& idList)
{
   idMappingList.insert(idMappingList.end(), idList.begin(), idList.end());
}

template <typename ContentType>
ContentType* SchweineSystem::SubList<ContentType>::operator[](const uint16_t& index)
{
   const uint8_t fullIndex = idMappingList.at(index);
   ContentType* value = &fullList[fullIndex];
   return value;
}

#endif // NOT SchweineSystemCommonHPP
