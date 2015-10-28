#ifndef _GREENCARD_HPP_
#define	_GREENCARD_HPP_

#include "Card.hpp"

/*
 * Abstract class GreenCard.
 *
 * A GreenCard can be either a Follower or an Item.
 * GreenCards are equiped to Personality cards
 * and give bonus statistics.
 */
class GreenCard : public Card {
    public:

        // member functions
        GreenCard(std::string, int);            // constructor
        virtual ~GreenCard();                   // destructor

        // setters
        void setCardText(std::string);
        void setAttackBonus(int);
        void setDefenceBonus(int);
        void setMinimumHonour(int);
        void setEffectBonus(int);
        void setEffectCost(int);

        // getters
        std::string getCardText() const;
        int getAttackBonus() const;
        int getDefenceBonus() const;
        int getMinimumHonour() const;
        int getEffectBonus() const;
        int getEffectCost() const;

        void activateEffect();                  // isEffectActivated = true
        bool checkIfEffectActivated() const;    // true if effect activated

    private:

        // data members
        std::string cardText;           // description of the card
        int attackBonus;                // attack bonus given to Personality
        int defenceBonus;               // defence bonus given to Personality
        int minimumHonour;              // minimum honour of Personality
                                        // needed to equip
        int effectBonus;                // an effect bonus which can be activated
                                        // only when equiping the card
        int effectCost;                 // cost to activate the effect bonus
        bool isEffectActivated;         // false when the card is created
                                        // true if the effect gets activated

};

#endif	// _GREENCARD_HPP_
