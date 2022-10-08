#ifndef ConductorH
#define ConductorH

#include <Blocks/Contour.h>
#include <Blocks/Grooves.h>

class Conductor : public Contour::Poly, public Grooves
{
public:
   Conductor();

public:
   void update(const uint8_t& newDefaultDivision, const uint32_t newSegmentCount) override;
};

#endif // NOT ConductorH
