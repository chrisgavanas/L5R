#include <algorithm>
#include "Personality.hpp"

/*
 * Personality's constructor
 * Arguments:
 * n: name of the Personality
 * t: type of the Personality
 * Personality types (ATTACKER, DEFENDER, SHOGUN, CHANCELLOR, CHAMPION)
 */
Personality::Personality(std::string n, int t)
    : BlackCard(n, PERSONALITY)
{
    switch (t) {
        case ATTACKER:
            setCost(5); attack = 3; defence = 2; honour = 2;
            break;
        case DEFENDER:
            setCost(5); attack = 2; defence = 3; honour = 2;
            break;
        case SHOGUN:
            setCost(15); attack = 10; defence = 5; honour = 8;
            break;
        case CHANCELLOR:
            setCost(15); attack = 5; defence = 10; honour = 8;
            break;
        case CHAMPION:
            setCost(30); attack = 20; defence = 20; honour = 12;
            break;
    }
}

/*
 * Virtual destructor of Personality
 * Followers and items are also destructed
 */
Personality::~Personality()
{
    for (int i = 0 ; i < followers.size() ; ++i)
        delete followers[i];
    for (int i = 0 ; i < items.size() ; ++i)
        delete items[i];

    followers.clear();
    items.clear();
}

void Personality::setAttack(int att)
{
    attack = att;
}

void Personality::setDefence(int def)
{
    defence = def;
}

void Personality::setHonour(int hon)
{
    honour = hon;
}

int Personality::getAttack() const
{
    return attack;
}

int Personality::getDefence() const
{
    return defence;
}

int Personality::getHonour() const
{
    return honour;
}

/*
 * Return the number of the Personality's followers
 */
int Personality::getFollowingsSize() const
{
    return followers.size();
}

/*
 * Return Personality's total attack.
 * Base attack + Followers' attack + Items' attack
 */
int Personality::getTotalAttack() const
{
    int total_attack = attack;   // base attack

    // Followers' attack
    for (int i = 0 ; i < followers.size() ; ++i) {
        total_attack += followers[i]->getAttackBonus();
        // if bonus effect is activated
        if (followers[i]->checkIfEffectActivated())
            total_attack += followers[i]->getEffectBonus();
    }

    // Items' attack
    for (int i = 0 ; i < items.size() ; ++i) {
        total_attack += items[i]->getAttackBonus();
        // if bonus effect is activated
        if (items[i]->checkIfEffectActivated())
            total_attack += items[i]->getEffectBonus();
    }
    return total_attack;
}

/*
 * Return Personality's total defence
 * Base defence + Followers' defence + Items' defence
 */
int Personality::getTotalDefence() const
{
    int total_defence = defence;  // base defence

    // Followers' defence
    for (int i = 0 ; i < followers.size() ; ++i) {
        total_defence += followers[i]->getDefenceBonus();
        // if bonus effect is activated
        if (followers[i]->checkIfEffectActivated())
            total_defence += followers[i]->getEffectBonus();
    }

    // Items' defence
    for (int i = 0 ; i < items.size() ; ++i) {
        total_defence += items[i]->getDefenceBonus();
        // if bonus effect is activated
        if (items[i]->checkIfEffectActivated())
            total_defence += items[i]->getEffectBonus();
    }
    return total_defence;
}

/* Return true if the Personality can't have
 * more Followers. Return true if there is room for more.
 */
bool Personality::isFollowingFull() const
{
    if (followers.size() < max_no_followers)
        return false;
    return true;
}

/*
 * Attach Follower to the Personality if
 * following is not full.
 */
void Personality::attachFollower(Follower* follower)
{
    if (!isFollowingFull())
        followers.push_back(follower);
}

/*
 * Return true if the Personality can't have more
 * Items. Return true if there is room for more.
 */
bool Personality::isInventoryFull() const
{
    if (items.size() < max_no_items)
        return false;
    return true;
}

/*
 * Attach Item to the Personality if
 * Inventory is not full.
 */
void Personality::attachItem(Item* item)
{
    if (!isInventoryFull())
        items.push_back(item);
}

int Personality::detachFollowers(std::vector<int>& nums)
{
    int total_attack = 0;

    std::sort(nums.begin(), nums.end());
    for (int i = 0 ; i < nums.size() ; ++i) {
        if (nums[i]-1 >= 0 && nums[i]-1 < followers.size()) {
            total_attack += followers[nums[i]-1]->getAttackBonus();
            delete followers[nums[i]-1];
            followers.erase(followers.begin()+nums[i]-1);
            for (int j = i+1 ; j < nums.size() ; ++j)
                --nums[j];
        }
    }
    return total_attack;
}

/*
 * All items of the Personality lose 1 durability.
 * This happens when the Personality participated
 * in a battle that was eventually lost.
 * Destroyed Items are deleted!
 */
void Personality::itemsWearOut()
{
    for (int i = 0 ; i < items.size() ; ++i) {
        items[i]->wearOut();
        if (items[i]->checkIfDestroyed()) {
            delete items[i];
            items.erase(items.begin() + i);
            i--;
        }
    }
}

/*
 * The Personality loses 1 honour after surviving
 * from a lost battle.
 */
void Personality::loseHonour()
{
	--honour;
}

/*
 * Return true if the Personality's honour
 * is equal to 0 and false if it's not.
 */
bool Personality::IsDishonoured()
{
	return (honour == 0 ? true : false);
}

/*
 * If the Personality has 0 honour, suicides
 * in order to protect his family honour.
 */
void Personality::performSeppuku()
{
    std::cout << getName() << " suicides to protect his family honour!\n\n";
    delete this;
}

/*
 * Taps the Personality and it's Followers and Items.
 * The Personality can't attack or defend any more
 * until it gets untapped in the next round.
 */
void Personality::tap()
{
    Card::tap();
    for (int i = 0 ; i < followers.size() ; ++i)
        followers[i]->tap();
    for (int i = 0 ; i < items.size() ; ++i)
        items[i]->tap();
}

/* Untaps the Personality and it's Followers and Items.
 * The Personality can attack or defend now.
 */
void Personality::untap()
{
    Card::untap();
    for (int i = 0 ; i < followers.size() ; ++i)
        followers[i]->untap();
    for (int i = 0 ; i < items.size() ; ++i)
        items[i]->untap();
}

/*
 * Prints Personality's statistics and all attached
 * Followers and Items and their statistics.
 */
void Personality::print() const
{
    // print statistics of Personality
    std::cout << getName() << ":\n"
            << "Attack: "  << getAttack()   << " | "
            << "Defence: " << getDefence()  << " | "
            << "Honour: "  << getHonour()   << " | "
            << "Cost: "    << getCost()     << "\n";

    // print the statistics of Followers attached to Personality
    if (followers.size() > 0) {
        std::cout << "Followers:" << std::endl;
        for (int i = 0 ; i < followers.size() ; ++i)
            std::cout << "  [" << i+1 << "] " << followers[i]->getName() << ":\n  "
                << "Attack Bonus: "  << followers[i]->getAttackBonus()   << " | "
                << "Defence Bonus: " << followers[i]->getDefenceBonus()  << " | "
                << "Effect Bonus: "  << followers[i]->getEffectBonus()   << " | "
                << "Effect Activated: "
                  << (followers[i]->checkIfEffectActivated() ? "YES" : "NO") << "\n";
    }

    // print statistics of Items attached to Personality
    if (items.size() > 0) {
        std::cout << "Items:" << std::endl;
        for (int i = 0 ; i < items.size() ; ++i)
            std::cout << "  [" << i+1 << "] " << items[i]->getName() << ":\n  "
                << "Attack Bonus: "    << items[i]->getAttackBonus()   << " | "
                << "Defence Bonus: "   << items[i]->getDefenceBonus()  << " | "
                << "Effect Bonus: "    << items[i]->getEffectBonus()   << " | "
                << "Effect Activated: "
                  << (items[i]->checkIfEffectActivated() ? "YES" : "NO") << " | "
                << "Durability: " << items[i]->getDurability() << "\n";
    }
}

