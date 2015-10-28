#include "Card.hpp"

/*
 * Card's constructor
 * Arguments:
 * n: name of the Card
 * t: type of the Card
 * Card types (Personality, Holding, Follower, Item)
 */
Card::Card(std::string n, int t)
    : name(n), type(t), cost(0), isTapped(false)
{
}

/*
 * Virtual destructor of Card
 */
Card::~Card()
{
}

std::string Card::getName() const
{
    return name;
}

/*
 * Returns the type of the Card which can be:
 * PERSONALITY, HOLDING, FOLLOWER, ITEM
 */
int Card::getType() const
{
    return type;
}

int Card::getCost() const
{
    return cost;
}

void Card::setCost(int c)
{
    cost = c;
}

/*
 * A card can be tapped or untapped on the game board.
 * If it's tapped it can't be used any more in this round.
 */
bool Card::getIsTapped() const
{
    return isTapped;
}

/*
 * If the card has been used in this round it's tapped
 */
void Card::tap()
{
    isTapped = true;
}

/*
 * All cards are untapped at the start of a new round, but only
 */
void Card::untap()
{
    isTapped = false;
}
