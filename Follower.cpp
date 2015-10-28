#include <iostream>
#include "Follower.hpp"

/*
 * Follower's constructor
 * Arguments:
 * n: name of the Follower
 * t: type of the Follower
 * Follower types (FOOTSOLDIER, ARCHER, SIEGER, CAVALRY, NAVAL, BUSHIDO)
 */
Follower::Follower(std::string n, int t)
    : GreenCard(n, FOLLOWER)
{
    switch (t) {
        case FOOTSOLDIER:
            setCost(0);
            setAttackBonus(2);
            setDefenceBonus(0);
            setMinimumHonour(1);
            setEffectBonus(1);
            setEffectCost(2);
            break;
        case ARCHER:
            setCost(0);
            setAttackBonus(0);
            setDefenceBonus(2);
            setMinimumHonour(1);
            setEffectBonus(1);
            setEffectCost(2);
            break;
        case SIEGER:
            setCost(5);
            setAttackBonus(3);
            setDefenceBonus(3);
            setMinimumHonour(2);
            setEffectBonus(2);
            setEffectCost(3);
            break;
        case CAVALRY:
            setCost(3);
            setAttackBonus(4);
            setDefenceBonus(2);
            setMinimumHonour(3);
            setEffectBonus(3);
            setEffectCost(4);
            break;
        case NAVAL:
            setCost(3);
            setAttackBonus(2);
            setDefenceBonus(4);
            setMinimumHonour(3);
            setEffectBonus(3);
            setEffectCost(4);
            break;
        case BUSHIDO:
            setCost(8);
            setAttackBonus(8);
            setDefenceBonus(8);
            setMinimumHonour(6);
            setEffectBonus(3);
            setEffectCost(8);
            break;
    }
}

/*
 * Virtual destructor of Follower
 */
Follower::~Follower()
{
}

/*
 * Prints the statistics of Follower Card
 * Overrides pure virtual function Card::print
 */
void Follower::print() const
{
    std::cout << getName() << ":\n"
            << "Attack: "         << getAttackBonus()   << " | "
            << "Defence: "        << getDefenceBonus()  << " | "
            << "Effect Bonus: "   << getEffectBonus()   << " | "
            << "Effect Cost: "    << getEffectCost()    << " | "
            << "Minimum Honour: " << getMinimumHonour() << " | "
            << "Cost: "           << getCost()          << "\n";
}
