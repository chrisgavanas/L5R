#ifndef _PLAYER_HPP_
#define	_PLAYER_HPP_

#include <string>
#include <list>
#include "libraries/DeckBuilder.hpp"
#include "libraries/TypeConverter.hpp"
#include "libraries/PlayerComm.hpp"
#include "StrongHold.hpp"
#include "Province.hpp"

#define STARTING_NO_PROVINCES 4
#define MAX_NO_HAND_CARDS     6

class Player {
    public:

        // member functions
        Player();
        virtual ~Player();

        int getHonour() const;
        int getProvincesDefence() const;
        int getNumberOfProvinces() const;
        int getHandSize() const;
        int getArmySize() const;

        void discardGreenCard(GreenCard*);
        void discardSurplusGreenCards();

        void drawGreenCard();
        void drawBlackCard(Province&);

        void printHand() const;
        void printArmy(const std::vector<Personality*>&) const;
        void printHoldings(const std::vector<Holding*>&) const;
        void printProvinces() const;
        void print();



        void revealProvinces();
        void untapEverything();

        void addHolding(Holding*);
        void addPersonality(Personality*);
        void addBlackCard(BlackCard*);

        bool buy(int cost);
        void chooseHoldings(std::vector<Holding*>&);
        bool buyGreenCard(GreenCard*);
        void activateGreenCardEffect(GreenCard*);
        bool equipGreenCard(Personality*, GreenCard*);
        bool selectEquipPhaseCards(Personality**, GreenCard**);

        bool chooseUnits(std::vector<Personality*>&);
        bool attack(PlayerComm&);
        void attackersBattleConsequences(int, int, std::vector<Personality*>&);
        bool defend(PlayerComm&);
        bool defendersBattleConsequences(int, int, std::vector<Personality*>&);

        void chooseProvinces(std::vector<Province*>&);
        bool buyBlackCard(BlackCard* pcard);

        bool checkWinningCondition(Player*[]);
        void discardProvinceCard();


    private:

        // member functions
        int getUntapped(std::vector<Holding*>&) const;
        int getUntapped(std::vector<Personality*>&) const;
        int getUnitsAttack(std::vector<Personality* >&);
        int getUnitsDefence(std::vector<Personality* >&);
        int chooseToDie(std::vector<Personality*>&, int&);

        // data members
        DeckBuilder deck;
        TypeConverter converter;
        std::list<GreenCard*>* fateDeck;
        std::list<BlackCard*>* dynastyDeck;

        StrongHold* stronghold;

        int no_provinces;
        Province provinces[STARTING_NO_PROVINCES];

        int playerHonour;

        std::vector<GreenCard*> hand;
        std::vector<Personality*> army;
        std::vector<Holding*> holdings;
};

#endif	// _PLAYER_HPP_
