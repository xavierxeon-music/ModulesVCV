#ifndef ConductorH
#define ConductorH

#include <Blocks/Contour.h>
#include <Blocks/Grooves.h>

class Conductor : public Contour::Poly, public Grooves
{
public:
   Conductor()
      : Abstract::SegmentCrawler()
      , Contour::Poly()
      , Grooves()
   {
   }

public:
   void update(const uint8_t& newDefaultDivision, const uint32_t newSegmentCount) override
   {
      Contour::Poly::update(newDefaultDivision, newSegmentCount);
      Grooves::update(newDefaultDivision, newSegmentCount);
   }
};

#endif // NOT ConductorH
