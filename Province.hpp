#ifndef _PROVINCE_HPP_
#define	_PROVINCE_HPP_

#include "Personality.hpp"
#include "Holding.hpp"

/*
 * Each Player has the same number of Provinces
 * Each Province has the same defence and
 * has a BlackCard(pointer) that the player can buy.
 */
class Province {
    public:

        // member functions
        Province();                         // constructor
        ~Province();                        // destructor

        bool checkIfDestroyed();
        void destroy();

        void reveal();
        BlackCard* getBlackCard();
        void addBlackCard(BlackCard*);
        BlackCard* removeBlackCard();

        void print() const;

    private:

        // data members
        BlackCard* pcard;
        bool isDestroyed;

};

#endif	// _PROVINCE_HPP_
