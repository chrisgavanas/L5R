#include <cstdlib>
#include "GameBoard.hpp"

int main(int argc, char *argv[])
{
    char *host = argv[1];
    char *player = argv[5];
    int portToConnect = atoi(argv[2]);
    int portToListen = atoi(argv[3]);
    int turn = atoi(argv[4]);

    srand(time(NULL));

    GameBoard gameboard;
    PlayerComm pl(host, portToConnect, portToListen);
    pl.init(turn);

    std::cout << "I am Player: " << player << "\n\n";
    pl.sendMessage(player);
	string* opponent = pl.readMessage();
	std::cout << "My opponent is Player: " << *opponent << "\n\n";
    delete opponent;

    gameboard.gameplay(pl, turn);
    return 0;
}
