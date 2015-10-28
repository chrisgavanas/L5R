#include "GameBoard.hpp"
#include "libraries/L5R_Library.hpp"

bool question(string question);

void GameBoard::gameplay(PlayerComm& player_comm, int turn)
{
    while (true) {
        if (turn == 1) {
	        player_comm.sendMessage("Opponent's turn");
            initialPhase();
            equipPhase();
            if (battlePhase(player_comm) == true) {
                std::cout << "I WIN!!!\n\n";
                break;
            }
            economyPhase();
            finalPhase();

            if (L5R_Library::question("Do you want to end the game and LOSE?")) {
                player_comm.sendMessage("Terminate");
                std::cout << "I LOSE...\n\n";
                break;
            } else {
                player_comm.sendMessage("End of Turn");
                turn = !turn;
            }
        } else {
            std::cout << "Waiting for the other player...\n";
            std::cout << std::endl;
            std::string* message = player_comm.readMessage();
            if ((*message) == "Terminate") {
                std::cout << "I WIN!!\n\n";
                delete message;
                break;
            } else if ((*message) == "End of Turn") {
                turn = !turn;
            } else if ((*message) == "Attacking") {
                std::cout << "I am receiving attack\n";
                std::cout << std::endl;
                if (player.defend(player_comm) == false) {
                    std::cout << "I LOSE...\n\n";
                    delete message;
                    break;
                }
            } else {
                std::cout << *message << endl;
            }
            delete message;
	    }
	    sleep(1);
    }
}

void GameBoard::initialPhase()
{
    player.untapEverything();
    player.drawGreenCard();
    player.revealProvinces();
    player.printHand();
    player.printProvinces();
}

void GameBoard::equipPhase()
{
    Personality* person;
    GreenCard* gcard;

    while (true) {
        if (L5R_Library::question("Do you want to buy and equip any cards?")) {
            if (player.getArmySize() == 0) {
                std::cout << "Sorry you don't have any units\n";
                std::cout << std::endl;
                break;
            }
            if (!(player.selectEquipPhaseCards(&person, &gcard)))
                continue;
            if (!(player.equipGreenCard(person, gcard)))
                continue;
            player.activateGreenCardEffect(gcard);
        } else {
            break;
        }
    }
}

bool GameBoard::battlePhase(PlayerComm& player_comm)
{
    if (L5R_Library::question("Do you want to attack to your opponent?")) {
        if (player.getArmySize() == 0) {
            std::cout << "You don't have any units to attack with\n";
            std::cout << std::endl;
            player_comm.sendMessage("No attack today");
            return false;
        } else {
            return (player.attack(player_comm));
        }
    } else {
        player_comm.sendMessage("No attack today");
        return false;
    }
}

void GameBoard::economyPhase()
{
    while (true) {
        if (L5R_Library::question("Do you want to buy from any Province?")) {
            std::vector<Province*> provs;

            player.chooseProvinces(provs);
            for (int i = 0 ; i < provs.size() ; ++i) {
                if (provs[i]->getBlackCard()->checkIfRevealed() == false) {
                    std::cout << "Card is hidden and can't be bought!\n";
                    std::cout << std::endl;
                    continue;
                }
                if (player.buyBlackCard(provs[i]->getBlackCard())) {
                    std::cout << "Bought card:\n";
                    provs[i]->print();
                    std::cout << std::endl;
                    player.addBlackCard(provs[i]->removeBlackCard());
                    player.drawBlackCard(*provs[i]);
                } else {
                    std::cout << "Not enough gold to buy card:\n";
                    provs[i]->print();
                    std::cout << std::endl;
                }
            }
        } else {
            break;
        }
    }
}

void GameBoard::finalPhase()
{
    player.discardSurplusGreenCards();
    player.discardProvinceCard();
    player.print();
}