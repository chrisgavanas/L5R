#ifndef _STRONGHOLD_HPP_
#define _STRONGHOLD_HPP_

#include "Holding.hpp"

class StrongHold : public Holding {
    public:

        // member functions
        StrongHold(std::string);
        virtual ~StrongHold();

        int getHonour() const;
        int getInitialDefence() const;

        void print() const;

    private:

        // data members
        int honour;
        int initialDefence;
};


#endif
