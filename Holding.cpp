#include "Holding.hpp"

/*
 * Holding's constructor
 * Arguments:
 * n: name of the Holding
 * t: type of the Holding
 * Holding types (PLAIN, MINE, GOLD_MINE, CRYSTAL_MINE, FARMS, SOLO, STRONGHOLD)
 */
Holding::Holding(std::string name, int k)
    : BlackCard(name, HOLDING), upperHolding(NULL), subHolding(NULL)
{
    switch (k) {
        case PLAIN:
            setCost(2); harvestValue = 2; kind = PLAIN;
            break;
        case MINE:
            setCost(5); harvestValue = 3; kind = MINE;
            break;
        case GOLD_MINE:
            setCost(7); harvestValue = 5; kind = GOLD_MINE;
            break;
        case CRYSTAL_MINE:
            setCost(12); harvestValue = 6; kind = CRYSTAL_MINE;
            break;
        case FARMS:
            setCost(3); harvestValue = 4; kind = FARMS;
            break;
        case SOLO:
            setCost(2); harvestValue = 2; kind = SOLO;
            break;
    }
}

/*
 * Virtual destructor of Holding
 */
Holding::~Holding()
{
}

void Holding::setHarvestValue(int harval)
{
    harvestValue = harval;
}

void Holding::setKind(int k)
{
	kind = k;
}

void Holding::setUpper(Holding* upper_ptr)
{
    upperHolding = upper_ptr;
}

void Holding::setSub(Holding* sub_ptr)
{
    subHolding = sub_ptr;
}

int Holding::getHarvestValue() const
{
    return harvestValue;
}

int Holding::getKind() const
{
    return kind;
}

/*
 * Return true if the Holding is not upper-chained.
 * Return false if it's upper-chained.
 */
int Holding::checkUpper() const
{
    return (upperHolding == NULL);
}

/*
 * Return true if the Holding is not sub-chained
 * Return false if it's sub-chained.
 */
int Holding::checkSub() const
{
    return (subHolding == NULL);
}

/*
 * When the Holding is bought check if it's a Mine.
 * If yes continue and check if the player has any
 * other Mines that can be chained with this one.
 * A Mine can be chained with a Gold Mine which can
 * also be chained with a Crystal Mine.
 * Chains give bigger harvest values to the Mines.
 *
 * Argument:
 * holdings: all the Holdings of the Player
 */
void Holding::checkBonus(std::vector<Holding* >& holdings)
{
    if (kind == MINE) {
        for (int i = 0; i < holdings.size(); ++i) {
            // if there is an available Gold Mine
            if ( (holdings[i]->getKind() == GOLD_MINE) && (holdings[i]->checkSub()) ) {
                setUpper(holdings[i]);           // connect Mine with Gold Mine
                holdings[i]->setSub(this);       // connect Gold Mine with Mine
                setHarvestValue(5);              // new harvest of Mine
                holdings[i]->setHarvestValue(9); // new harvest of Gold Mine
                break;                           // nothing else to do
            }
        }

        /*
         * Check if the Mine is chained with a Gold Mine and if this Gold Mine
         * is chained with a Crystal Mine and they form a complete chain.
         */
        if (!checkUpper() && !upperHolding->checkUpper()) {
            upperHolding->setHarvestValue(15);
            upperHolding->upperHolding->setHarvestValue(24);
        }
    } else if (kind == GOLD_MINE) {
        for (int i = 0; i< holdings.size(); ++i) {
            if ( (holdings[i]->getKind() == MINE) && (holdings[i]->checkUpper()) ) {
                setSub(holdings[i]);             // connect Gold Mine with Mine
                holdings[i]->setUpper(this);     // connect Mine with Gold Mine
                setHarvestValue(9);              // new harvest of Gold Mine
                holdings[i]->setHarvestValue(5); // new harvest of Mine
                break;
            }
        }
        for (int i = 0; i< holdings.size(); ++i) {
            if ( (holdings[i]->getKind() == CRYSTAL_MINE) && (holdings[i]->checkSub()) ) {
                setUpper(holdings[i]);            // connect Gold Mine with Crystal Mine
                holdings[i]->setSub(this);        // connect Crystal Mine with Gold Mine
                setHarvestValue(10);              // new harvest of Gold Mine
                holdings[i]->setHarvestValue(12); // new harvest of Crystal Mine
                break;
            }
        }

        /*
         * Check if the Gold Mine is chained with a Mine and
         * a Crystal Mine and they form a complete chain.
         */
        if (!checkUpper() && !checkSub() ) {
            setHarvestValue(15);
            upperHolding->setHarvestValue(24);
        }
    } else if (kind == CRYSTAL_MINE) {
        for (int i = 0; i< holdings.size(); ++i) {
            if ( (holdings[i]->getKind() == GOLD_MINE) && (holdings[i]->checkUpper()) ) {
                setSub(holdings[i]);              // connect Crystal Mine with Gold Mine
                holdings[i]->setUpper(this);      // connect Gold Mine with Crystal Mine
                setHarvestValue(12);              // new harvest of Crystal Mine
                holdings[i]->setHarvestValue(10); // new harvest of Gold Mine
                break;
            }
        }

        /*
         * Check if the Gold Mine, chained with the Crystal Mine,
         * is chained with a Mine and they form a complete chain.
         */
        if (!checkSub() && !subHolding->checkSub() ) {
            subHolding->setHarvestValue(15);
            setHarvestValue(24);
        }
    }
}

/*
 * Print Holding's statistics.
 * If the Holding can be chained with other Holdings
 * print if it's chained.
 */
void Holding::print() const
{
    std::cout << getName() << ":\n"
            << "HarvestValue: " << harvestValue << " | "
            << "Cost: "         << getCost();
    if (kind == MINE) {
        std::cout << " | UpperChained: " << (upperHolding != NULL ? "YES" : "NO") << "\n";
    } else if (kind == GOLD_MINE) {
        std::cout << " | SubChained: "   << (subHolding != NULL ? "YES" : "NO") << " | "
                << "UpperChained: " << (upperHolding != NULL ? "YES" : "NO") << "\n";
    } else if (kind == CRYSTAL_MINE) {
        std::cout << " | SubChained: "   << (subHolding != NULL ? "YES" : "NO") << "\n";
    } else {
        std::cout << "\n";
    }
}
