#ifndef _CARD_HPP_
#define _CARD_HPP_

#include <iostream>
#include <string>

// Type of the Card
enum { PERSONALITY = 1, HOLDING, FOLLOWER, ITEM };

/*
 * Abstract class Card.
 * Base class for every other type of Card.
 */
class Card {
    public:

        // member functions
        Card(std::string, int);         // constructor
        virtual ~Card();                // destructor

        std::string getName() const;
        int getType() const;
        int getCost() const;
        bool getIsTapped() const;

        void setCost(int);

        virtual void tap();             // tap the card, which can't be used again
        virtual void untap();           // untap the tapped card

        virtual void print() const = 0; // pure virtual

    private:

        // data members
        std::string name;               // name of the Card
        int type;                       // type of the Card
        int cost;                       // cost paid when buing the Card
        bool isTapped;                  // true if tapped, false if not
                                        // if tapped the card can't be used
};

#endif  // _CARD_HPP_
