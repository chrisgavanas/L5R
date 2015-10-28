#ifndef _FOLLOWER_HPP_
#define	_FOLLOWER_HPP_

#include "GreenCard.hpp"

// enumeration of the types of Followers
enum { FOOTSOLDIER, ARCHER, SIEGER, CAVALRY, NAVAL, BUSHIDO };

class Follower : public GreenCard {
    public:

        // member functions
        Follower(std::string, int);         // constructor
        virtual ~Follower();                // destructor

        void print() const;                 // print card's statistics

    private:

        // no data members

};

#endif	// _FOLLOWER_HPP_
