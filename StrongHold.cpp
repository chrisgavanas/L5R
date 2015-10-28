#include "StrongHold.hpp"

StrongHold::StrongHold(std::string name)
    : Holding(name, HOLDING), honour(3), initialDefence(7)
{
	setHarvestValue(5);
	setKind(STRONGHOLD);
	setCost(0);
}

StrongHold::~StrongHold()
{
}

int StrongHold::getHonour() const
{
    return honour;
}

int StrongHold::getInitialDefence() const
{
    return initialDefence;
}

void StrongHold::print() const
{
    std::cout << getName() << ": " << "\n"
            << "Harvest value: " << getHarvestValue() << "\n";
}
