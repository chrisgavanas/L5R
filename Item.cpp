#include <iostream>
#include "Item.hpp"

/*
 * Item's constructor
 * Arguments:
 * n: name of the Item
 * t: type of the Item
 * Item types (KATANA, SPEAR, BOW, NINJATO, WAKIZASHI)
 */
Item::Item(std::string n, int t)
    : GreenCard(n, ITEM), durability(0)
{
    switch (t) {
        case KATANA:
            setCost(5);
            setAttackBonus(3);
            setDefenceBonus(3);
            setMinimumHonour(1);
            setEffectBonus(5);
            setEffectCost(6);
            durability = 4;
            break;
        case SPEAR:
            setCost(5);
            setAttackBonus(2);
            setDefenceBonus(2);
            setMinimumHonour(1);
            setEffectBonus(4);
            setEffectCost(6);
            durability = 4;
            break;
        case BOW:
            setCost(10);
            setAttackBonus(4);
            setDefenceBonus(4);
            setMinimumHonour(2);
            setEffectBonus(4);
            setEffectCost(10);
            durability = 6;
            break;
        case NINJATO:
            setCost(15);
            setAttackBonus(6);
            setDefenceBonus(6);
            setMinimumHonour(3);
            setEffectBonus(6);
            setEffectCost(10);
            durability = 8;
            break;
        case WAKIZASHI:
            setCost(20);
            setAttackBonus(8);
            setDefenceBonus(8);
            setMinimumHonour(6);
            setEffectBonus(8);
            setEffectCost(15);
            durability = 10;
            break;
        default:
            std::cerr << "shit";

    }
}

/*
 * Virtual destructor of Item
 */
Item::~Item()
{
}

int Item::getDurability()
{
    return durability;
}

/*
 * Reduces durability by 1
 */
void Item::wearOut()
{
    --durability;
}

/*
 * Returns true if item is destroyed(durability == 0).
 * In any other case returns false.
 */
bool Item::checkIfDestroyed()
{
    return (durability == 0 ? true : false);
}

/*
 * Prints the statistics of Item Card
 * Overrides pure virtual function Card::print
 */
void Item::print() const
{
    std::cout << getName() << ":\n"
            << "Attack: "          << getAttackBonus()   << " | "
            << "Defence: "         << getDefenceBonus()  << " | "
            << "Effect Bonus: "    << getEffectBonus()   << " | "
            << "Effect Cost: "     << getEffectCost()    << " | "
            << "Durability: "      << durability         << " | "
            << "Minimum Honour: "  << getMinimumHonour() << " | "
            << "Cost: "            << getCost()          << "\n";
}
