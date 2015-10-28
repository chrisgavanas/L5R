#ifndef _PERSONALITY_HPP_
#define _PERSONALITY_HPP_

#include <vector>
#include "BlackCard.hpp"
#include "Follower.hpp"
#include "Item.hpp"

// enumeration of the types of Personalities
enum { ATTACKER = 1, DEFENDER, SHOGUN, CHANCELLOR, CHAMPION };

class Personality : public BlackCard {
    public:

        // member functions
        Personality(std::string, int);
        virtual ~Personality();

        void setAttack(int);
        void setDefence(int);
        void setHonour(int);

        int getAttack() const;
        int getDefence() const;
        int getHonour() const;
        int getFollowingsSize() const;
        int getTotalAttack() const;
        int getTotalDefence() const;

        bool isFollowingFull() const;
        void attachFollower(Follower*);
        bool isInventoryFull() const;
        void attachItem(Item*);

        int detachFollowers(std::vector<int>&);
        void itemsWearOut();

        void loseHonour();
        bool IsDishonoured();
        void performSeppuku();

        void tap();                             // overrides Card::tap()
        void untap();                           // overrides Card::untap()
        void print() const;                     // overrides Card::print()

    private:

        // constants
        static const int max_no_followers = 4;  // max number of followers attached
        static const int max_no_items = 2;      // max number of items attached

        // data members
        int attack;
        int defence;
        int honour;

        std::vector<Follower* > followers;      // followers attached
        std::vector<Item* > items;              // items attached

};

#endif // _PERSONALITY_HPP_
