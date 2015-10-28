#include "BlackCard.hpp"

/*
 * BlackCard's constructor
 * Arguments:
 * n: name of the BlackCard
 * t: type of the BlackCard
 * BlackCard types (Personality, Holding)
 */
BlackCard::BlackCard(std::string n, int t)
    : Card(n, t), isRevealed(false)
{
}

/*
 * Virtual destructor of BlackCard
 */
BlackCard::~BlackCard()
{
}

void BlackCard::setFaceUp()
{
    isRevealed = true;
}

void BlackCard::setFaceDown()
{
    isRevealed = false;
}

bool BlackCard::checkIfRevealed()
{
    return isRevealed;
}
