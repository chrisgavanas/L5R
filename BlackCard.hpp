#ifndef _BLACKCARD_HPP_
#define _BLACKCARD_HPP_

#include "Card.hpp"

/*
 * Abstract class BlackCard.
 *
 * A BlackCard can be either a Personality or a Holding.
 * Personalities make up the army of the player.
 * Holdings provide gold so the player can buy
 * units, weapons and other holdings.
 */
class BlackCard : public Card {
    public:

        // member functions
        BlackCard(std::string, int);        // constructor
        virtual ~BlackCard();               // destructor

        void setFaceUp();                   // the card is revelead
        void setFaceDown();                 // the card is hidden

        bool checkIfRevealed();             // true if card is revealed

    private:

        // data members
        bool isRevealed;                // card is hidden when placed and gets
                                        // revealed in the initial phase

};

#endif  // _BLACKCARD_HPP_
