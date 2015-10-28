#include "GreenCard.hpp"

/*
 * Card's constructor
 * Arguments:
 * n: name of the GreenCard
 * t: type of the GreenCard
 * GreenCard types (Follower, Item)
 */
GreenCard::GreenCard(std::string n, int t)
    : Card(n, t), attackBonus(0), defenceBonus(0),
      minimumHonour(0), effectBonus(0), effectCost(0),
      isEffectActivated(false)
{
}

/*
 * Virtual destructor of GreenCard
 */
GreenCard::~GreenCard()
{
}

//setters

void GreenCard::setCardText(std::string card_text)
{
    cardText = card_text;
}

void GreenCard::setAttackBonus(int att_bonus)
{
    attackBonus = att_bonus;
}

void GreenCard::setDefenceBonus(int def_bonus)
{
    defenceBonus = def_bonus;
}

void GreenCard::setMinimumHonour(int min_honour)
{
    minimumHonour = min_honour;
}

void GreenCard::setEffectBonus(int effect_bonous)
{
    effectBonus = effect_bonous;
}

void GreenCard::setEffectCost(int effect_cost)
{
    effectCost = effect_cost;
}

// getters

std::string GreenCard::getCardText() const
{
    return cardText;
}

int GreenCard::getAttackBonus() const
{
    return attackBonus;
}

int GreenCard::getDefenceBonus() const
{
    return defenceBonus;
}

int GreenCard::getMinimumHonour() const
{
    return minimumHonour;
}

int GreenCard::getEffectBonus() const
{
    return effectBonus;
}

int GreenCard::getEffectCost() const
{
    return effectCost;
}

void GreenCard::activateEffect()
{
    isEffectActivated = true;
}

/*
 * Returns true if effect is activated and false if not
 */
bool GreenCard::checkIfEffectActivated() const
{
    return isEffectActivated;
}
