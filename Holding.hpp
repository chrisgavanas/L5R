#ifndef _HOLDING_HPP_
#define _HOLDING_HPP_

#include <vector>
#include "BlackCard.hpp"

enum { PLAIN = 1, MINE, GOLD_MINE, CRYSTAL_MINE, FARMS, SOLO, STRONGHOLD };


class Holding : public BlackCard {
    public:

        // member function
        Holding(std::string, int);          // constructor
        virtual ~Holding();                 // destructor

        int getKind() const;
        int getHarvestValue() const;

        void setHarvestValue(int);
        void setKind(int);

        void checkBonus(std::vector<Holding* >&);   // checking for chain Bonus
        void print() const;

    private:

        // member functions
        int checkUpper() const;
        int checkSub() const;
        void setUpper(Holding* ptr);
        void setSub(Holding* ptr);

        // data members
        int harvestValue;
        int kind;                           // kind of Holding
        Holding* upperHolding;              // pointer to upper member of chain
        Holding* subHolding;

};



#endif
