#include "Province.hpp"

/*
 * Province's constructor
 * The Province has no BlackCard when created
 * The Province is not destroyed when created
 */
Province::Province()
    : pcard(NULL), isDestroyed(false)
{
}

/*
 * Destructor of Province
 */
Province::~Province()
{
    delete pcard;                           // delete BlackCard
}

/*
 * Return true if Province is destroyed
 * and false if it's not.
 */
bool Province::checkIfDestroyed()
{
    return isDestroyed;
}

/*
 * Province is now considered destroyed.
 * Players cannot attack to this Province.
 * The BlackCard is removed from the game.
 */
void Province::destroy()
{
    isDestroyed = true;                     // province destroyed
    delete pcard;                           // remove(delete) BlackCard from game
    pcard = NULL;
}

/*
 * Return the Province's BlackCard(pointer)
 * without removing it from the Province.
 */
BlackCard* Province::getBlackCard()
{
    return pcard;
}

/*
 * Adds a BlackCard(pointer) to the Province.
 */
void Province::addBlackCard(BlackCard* c)
{
    pcard = c;
}

/*
 * The BlackCard(pointer) is removed from the
 * Province and is returned to the caller.
 */
BlackCard* Province::removeBlackCard()
{
    BlackCard* temp = pcard;

    pcard = NULL;                           // Province has no BlackCard
    return temp;
}

/*
 * If the Province is not destroyed reveal
 * its BlackCard.
 */
void Province::reveal()
{
    if (!isDestroyed)
        pcard->setFaceUp();
}

/*
 * If the Province is not destroyed and
 * the BlackCard is revealed, it's printed.
 */
void Province::print() const
{
    if (!isDestroyed) {
        if (pcard->checkIfRevealed()) {
            pcard->print();
        } else {
            std::cout << "Unknown Province state!\n";
        }
    } else {
        std::cout << "Province destroyed!...\n";
    }
}
