#include "Conductor.h"

Conductor::Conductor()
   : Abstract::SegmentCrawler()
   , Contour::Poly()
   , Grooves()
{
}

void Conductor::update(const uint8_t& newDefaultDivision, const uint32_t newSegmentCount)
{
   Contour::Poly::update(newDefaultDivision, newSegmentCount);
   Grooves::update(newDefaultDivision, newSegmentCount);
}
