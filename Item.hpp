#ifndef _ITEM_HPP_
#define	_ITEM_HPP_

#include "GreenCard.hpp"

// enumeration of the types of Items
enum { KATANA, SPEAR, BOW, NINJATO, WAKIZASHI };

class Item : public GreenCard {
    public:

        // member functions
        Item(std::string, int);         // constructor
        virtual ~Item();                // destructor

        int getDurability();

        void wearOut();                 // item loses 1 durability
        bool checkIfDestroyed();        // true if item is destroyed, else false

        void print() const;             // print card's statistics

    private:

        // data members
        int durability;
};

#endif	// _ITEM_HPP_
