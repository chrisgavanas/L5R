#ifndef _GAMEBOARD_HPP_
#define	_GAMEBOARD_HPP_

#include "libraries/PlayerComm.hpp"
#include "Player.hpp"

class GameBoard {
    public:

        // member functions
        void gameplay(PlayerComm&, int);

    private:

        // member functions
        void initialPhase();
        void equipPhase();
        bool battlePhase(PlayerComm&);
        void economyPhase();
        void finalPhase();

        // data members
        Player player;
};

#endif	// _GAMEBOARD_HPP_

