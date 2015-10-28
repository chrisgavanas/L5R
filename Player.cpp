#include <string>
#include <cstring>
#include <sstream>
#include <algorithm>
#include "Player.hpp"
#include "libraries/L5R_Library.hpp"

//Two fuctions only for Player's use
std::vector<int>& tokenizer(std::string str, std::vector<int>& nums);
bool find(const int& val, const std::vector<int>& values);

/*
 * Player's constructor
 * Create and Shuffle Decks
 * Create Stronghold
 * Draw a GreenCard
 * Draw BlackCards as many as the number of Provinces
 */
Player::Player()
    : no_provinces(STARTING_NO_PROVINCES)
{
    fateDeck = deck.createFateDeck();
    deck.deckShuffler(fateDeck);
    dynastyDeck = deck.createDynastyDeck();
    deck.deckShuffler(dynastyDeck);

    stronghold = new StrongHold("StrongHold");
    addHolding(stronghold);
    playerHonour = stronghold->getHonour();

    for (int i = 0 ; i < MAX_NO_HAND_CARDS ; ++i)
        drawGreenCard();
    for (int i = 0 ; i < STARTING_NO_PROVINCES ; ++i)
        drawBlackCard(provinces[i]);
}

/*
 * Player's Destructor
 */
Player::~Player()
{
    for (int i = 0; i < hand.size(); ++i)
        delete hand[i];
    for (int i = 0; i < army.size(); ++i)
        delete army[i];
    for (int i = 0; i < holdings.size(); ++i)
        delete holdings[i];

    hand.clear();
    army.clear();
    holdings.clear();
}

/*
 * Accessors
 */
int Player::getHonour() const
{
    return playerHonour;
}

int Player::getProvincesDefence() const
{
    return stronghold->getInitialDefence();
}

int Player::getNumberOfProvinces() const
{
    return no_provinces;
}

int Player::getHandSize() const
{
    return hand.size();
}

int Player::getArmySize() const
{
    return army.size();
}

/*
 * Adds all untapped Holdings to the vector
 * of pointers to Holding, passed as argument.
 * Returns the number of Holdings added.
 */
int Player::getUntapped(std::vector<Holding*>& untapped_holdings) const
{
    for (int i = 0 ; i < holdings.size() ; ++i) {
        if (!holdings[i]->getIsTapped()) {
            untapped_holdings.push_back(holdings[i]);
        }
    }
    return untapped_holdings.size();
}

/*
 * Adds all untapped Personalities to the vector
 * of pointers to Personality, passed as argument.
 * Returns the number of Personalities added.
 */
int Player::getUntapped(std::vector<Personality*>& untapped_army) const
{
    for (int i = 0 ; i < army.size() ; ++i) {
        if (!army[i]->getIsTapped()) {
            untapped_army.push_back(army[i]);
        }
    }
    return untapped_army.size();
}

/*
 * Draws a GreenCard from the FateDeck
 */
void Player::drawGreenCard()
{
    if (fateDeck->size() > 0) {
        hand.push_back(fateDeck->front());
        fateDeck->pop_front();
    }
}

/*
 * Print Player's Hand
 */
void Player::printHand() const
{
    std::cout << "Your hand:\n";
    for (int i = 0 ; i < hand.size() ; ++i) {
        std::cout << "[" << i+1 << "]" << " ";
        hand[i]->print();
    }
    std::cout << std::endl;
}

/*
 * Print the vectors of Personalities
 */
void Player::printArmy(const std::vector<Personality*>& units) const
{
    std::cout << "Your Army:\n";
    for (int i = 0 ; i < units.size() ; ++i) {
        std::cout << "[" << i+1 << "]" << " ";
        units[i]->print();
    }
    std::cout << std::endl;
}

/*
 * Print the vector of Holdings
 */
void Player::printHoldings(const std::vector<Holding*>& holds) const
{
    std::cout << "Your Holdings:\n";
    for (int i = 0 ; i < holds.size() ; ++i) {
        std::cout << "[" << i+1 << "]" << " ";
        holds[i]->print();
    }
    std::cout << std::endl;
}

/*
 * Print all the Provinces
 */
void Player::printProvinces() const
{
    std::cout << "Your Provinces:\n";
    for (int i = 0 ; i < STARTING_NO_PROVINCES ; ++i) {
        std::cout << "[" << i+1 << "] ";
        provinces[i].print();
    }
    std::cout << std::endl;
}

/*
 * Print all Player's information
 */
void Player::print()
{
    printHand();
    printProvinces();
    printArmy(army);
    printHoldings(holdings);
}

/*
 * Reveal Black Cards of all the Provinces
 */
void Player::revealProvinces()
{
    for (int i = 0 ; i < STARTING_NO_PROVINCES ; ++i)
        provinces[i].reveal();
}

/*
 * Untap all the Cards to be available for use
 */
void Player::untapEverything()
{
    for (int i = 0 ; i < army.size() ; ++i)
        army[i]->untap();
    for (int i = 0 ; i < holdings.size() ; ++i)
        holdings[i]->untap();
}

/*
 * Adding a Holding in Player's Holdings after tapping it
 * so it can't be harvested before the next turn and
 * checking if it can be chained with another Holding.
 */
void Player::addHolding(Holding* holding)
{
    holding->tap();
    holding->checkBonus(holdings);
    holdings.push_back(holding);
}

/*
 * Player chooses Untapped Holdings and returns them
 * in a vector to be harvested
 */
void Player::chooseHoldings(std::vector<Holding*>& chosen_holdings)
{
    std::vector<Holding*> untapped_holdings;
    std::vector<int> nums;
    std::string str;

    // if there are no untapped holdings
    if (getUntapped(untapped_holdings) == 0) {
        std::cout << "No available Holdings!\n\n";
        return;
    }

    printHoldings(untapped_holdings);
    std::cout << "Input: ";
    std::getline(std::cin, str);          // choose from the untapped holdings
    std::cout << std::endl;

    L5R_Library::tokenizer(str, nums);    // tokenize input to get every integer

    for (int i = 0 ; i < nums.size() ; ++i) {
        if (nums[i]-1 >= 0 && nums[i]-1 < untapped_holdings.size()) {
            chosen_holdings.push_back(untapped_holdings[nums[i]-1]);
        }
    }
}

/*
 * Player chooses Holdings to harvest to pay the cost of the card.
 * If the card is bought return true, if not return false.
 */
bool Player::buy(int cost)
{
    vector<Holding*> chosen_holdings;       // chosen holdings to be harvested

    if (cost == 0) {                        // if the cost is 0
        std::cout << "Card costs 0 gold!!\n\n";
        return true;
    } else {                                // if the cost is > 0
        std::cout << "You need " << cost << " gold! Harvest your Holdings:\n";
        chooseHoldings(chosen_holdings);
    }
    for (int i = 0 ; i < chosen_holdings.size() ; ++i) {
        cost -= chosen_holdings[i]->getHarvestValue();
    }

    // if bought card tap the chosen holdings
    if (cost <= 0) {
        for (int i = 0 ; i < chosen_holdings.size() ; ++i) {
            chosen_holdings[i]->tap();
        }
        return true;
    } else {
        return false;
    }
}

bool Player::buyGreenCard(GreenCard* gcard)
{
    int cost = gcard->getCost();

    return (buy(cost));
}

/*
 * Player chooses if he activates the Effect Bonus
 * of the GreenCard he bought and equipped.
 */
void Player::activateGreenCardEffect(GreenCard* gcard)
{
    int cost = 0;

    // if choose to not activate -> return
    if (L5R_Library::question("Activate the Effect Bonus of the card?") == false)
        return;

    cost = gcard->getEffectCost();
    // try to buy
    if (buy(cost)) {
        gcard->activateEffect();
        std::cout << "Effect Bonus of " << gcard->getName() << " activated\n\n";
    } else {
        std::cout << "Not enough gold to activate Effect Bonus of "
                << gcard->getName() << "\n\n";
    }
}

/*
 * Player tries to attach the GreenCard to the Personality.
 * If it can be done return true and if not return false.
 */
bool Player::equipGreenCard(Personality* person, GreenCard* gcard)
{
    Follower* follower = NULL;
    Item* item = NULL;

    // check if the GreenCard is Follower or Item
    converter.getCorrectType(gcard, &follower, &item);

    // If it's Follower
    if (follower != NULL) {
        if (person->getHonour() < follower->getMinimumHonour()) {
            std::cout << person->getName() << " cannot be followed by "
                    << follower->getName() << "!\n\n";
            return false;
        }
        if (person->isFollowingFull()) { // if following is full
            std::cout << person->getName() << "cannot have any more Followers!\n\n";
            return false;
        }
        if (!buyGreenCard(gcard)) { // if can't afford the cost
            std::cout << "Not enough gold to recruit " << follower->getName() << "!\n\n";
            return false;
        } else {    // if can attach to the Personality
            std::cout << follower->getName() << " is in command of "
                    << person->getName() << "!\n\n";
            person->attachFollower(follower);
        }
    } else if (item != NULL) {  // If it's Item
        if (person->getHonour() < item->getMinimumHonour()) {
            std::cout << person->getName() << " cannot wield "
                    << item->getName() << "!\n\n";
            return false;
        }
        if (person->isInventoryFull()) { // if inventory is full
            std::cout << person->getName() << "cannot carry any more items!\n\n";
            return false;
        }
        if (!buyGreenCard(gcard)) { // if can't afford the cost
            std::cout << "Not enough gold to buy " << item->getName() << "!\n\n";
            return false;
        } else {    // if can attach to Personality
            std::cout << item->getName() << " is now wielded by "
                    << person->getName() << "!\n\n";
            person->attachItem(item);
        }
    }
    // remove attached card from hand
    hand.erase(find(hand.begin(), hand.end(), gcard));
    return true;
}

/*
 * Player chooses a Follower or an Item from his Hand
 * and then the Personality which is going to attach it on
 */
bool Player::selectEquipPhaseCards(Personality** person, GreenCard** gcard)
{
    int no_person;                          // number of Personality
    int no_gcard;                           // number of GreenCard
    std::string str;                        // used for input and parsing

    std::cout << "Choose a card from your hand!\n";
    printHand();
    std::cout << "Input: ";
    std::getline(std::cin, str);            // choose GreenCard
    std::cout << std::endl;

    no_gcard = atoi(str.c_str());
    if (no_gcard <= 0 || no_gcard > hand.size()) {  // if no such card
        std::cout << "Invalid card number\n";
        std::cout << std::endl;
        return false;
    } else {                                // if card exists
        *gcard = hand[no_gcard-1];
        std::cout << "Selected card:\n";
        (*gcard)->print();
        std::cout << std::endl;
    }

    std::cout << "Choose a Personality from your army!\n";
    printArmy(army);
    std::cout << "Input: ";
    std::getline(std::cin, str);            // choose Personality from army
    std::cout << std::endl;

    no_person = atoi(str.c_str());
    if (no_person <= 0 || no_person > army.size()) {    // if no such Personality
        std::cout << "Invalid card number\n";
        std::cout << std::endl;
        return false;
    } else {                                // if Personality exists
        *person = army[no_person-1];
        std::cout << "Selected card:\n";
        (*person)->print();
        std::cout << std::endl;
    }
    return true;
}

/*
 * Player's Untapped Units are printed.
 * Player chooses and adds them to the argument vector
 * to be used for Attack or Defence.
 */
bool Player::chooseUnits(std::vector<Personality*>& chosen_army)
{
    std::vector<Personality*> untapped_army;
    std::vector<int> nums;
    std::string str;

    if (getUntapped(untapped_army) == 0) {  // if there are no untapped units
        std::cout << "No available Units!\n";
        std::cout << std::endl;
        return false;
    }

    std::cout << "Choose Units!\n";
    printArmy(untapped_army);
    std::cout << "Input: ";
    std::getline(std::cin, str);            // choose units - input
    std::cout << std::endl;

    L5R_Library::tokenizer(str, nums);      // tokenize input to get every integer

    for (int i = 0 ; i < nums.size() ; ++i) {
        //Removing chosen Personalities from Player's Army and adding them to vector
        if (nums[i]-1 >= 0 && nums[i]-1 < untapped_army.size()) {   // if units exists
            chosen_army.push_back(*(std::find(army.begin(), army.end(), untapped_army[nums[i]-1])));        // add to chosen
            // remove from army
            army.erase(std::find(army.begin(), army.end(), untapped_army[nums[i]-1]));
        }
    }
    return true;
}

/*
 * Getting attack summary of Personalities placed in vector
 */
int Player::getUnitsAttack(std::vector<Personality*>& attackers)
{
	int attack = 0;
	for (int i = 0; i < attackers.size(); ++i)
		attack += attackers[i]->getTotalAttack();
	return attack;
}

/*
 * Getting defence summary of Personalities placed in vector
 */
int Player::getUnitsDefence(std::vector<Personality* >& defenders)
{
	int defence = 0;
	for (int i = 0; i < defenders.size(); ++i)
		defence += defenders[i]->getTotalDefence();
	return defence;
}

/*
 * Attacking Phase for PvP part.
 * Send Attack Points and Province to attack to the Opponent.
 * Receive Defence Points.
 * Return true if win, false if not.
 */
bool Player::attack(PlayerComm &pl)
{
    int province;
    std::string str;
    std::vector<int> attacked_provinces;

    while (true) {
        std::cout << "Choose a Province to attack to!\n";
        std::cout << "Input: ";
        std::getline(std::cin, str);        // choose Province to attack
        std::cout << std::endl;

        province = atoi(str.c_str());
        if (province < 1 && province > STARTING_NO_PROVINCES)
            continue;
        // Cannot double attack to a Province on the same turn
        if (L5R_Library::find(province, attacked_provinces)) {
            std::cout << "You have already attacked to this Province!\n";
            std::cout << std::endl;
            continue;
        } else {
            int units_attack = 0, units_defence = 0;
            char mes_province[8];                   // province getting attacked
            char mes_attack[8];                     // attack of attacking units
            std::string* mes_defence;               // defence of defending units
            std::vector<Personality*> attackers;    // chosen attacking units

            // choose attacking units
            do {
                if (chooseUnits(attackers) == false) {
                    return false;
                }
            } while (attackers.size() == 0);
            units_attack = getUnitsAttack(attackers);


            // messages
            pl.sendMessage("Attacking");            // send attack message
            attacked_provinces.push_back(province);
            sleep(2);

            sprintf(mes_province, "%d", province);
            pl.sendMessage(mes_province);
            sleep(2);                               // wait a little
            sprintf(mes_attack, "%d", units_attack);
            pl.sendMessage(mes_attack);
            mes_defence = pl.readMessage();
            sleep(1);
            units_defence = atoi(mes_defence->c_str());

            if (units_defence == -1) {
                std::cout << "This Province is destroyed!!\n\n";
                //Tapping all attacking Units so they can't be used again in this turn
                for (int i = 0; i < attackers.size(); ++i) {
                    attackers[i]->tap();
                    army.push_back(attackers[i]);   // push units back to army
                }
                continue;
            } else {
                // Calculate battle results
                attackersBattleConsequences(units_attack, units_defence, attackers);
            }

            // delete
            delete mes_defence;

            // check if you win
            std::string* mes_win = pl.readMessage();
            if (atoi(mes_win->c_str()) == 1) {
                delete mes_win;
                return true;
            }
            delete mes_win;

        }
        // Attack again to another Province this time?
        if (L5R_Library::question("Do you want to attack again?") == false)
            return false;
        //If Player has attacked to all Available Provinces
        if (attacked_provinces.size() == STARTING_NO_PROVINCES) {
            std::cout << "You have attacked to all available Provinces!\n\n";
            return false;
        }
    }
}

/*
 * Calculate battle consequences for the attacker
 */
void Player::attackersBattleConsequences
    (int attack, int defence, std::vector<Personality*>& attackers)
{
    int province_defence = getProvincesDefence();
    int difference = attack-defence-province_defence;

    if (difference > province_defence) {  // If Player conquered Opponent
        std::cout << "Your attack was successful, you ruined the Province\n\n";
    } else if (difference > 0) {  // If Player killed Opponent's Army, but not his Province
        std::cout << "Your attack was successful, but didn't destroy the"
                  << " Province and you lose some of your units\n\n";

        /*
         * Player needs to lose Army until he covers a difference
         * between Attack and Defence according to the rules so he
         * chooses attacking Units to die until difference is <= 0
         */
        while (chooseToDie(attackers, difference) > 0);
        // Personalities attacked and did not win.
        // They lose Honour & Items' Durability
        for (int i = 0 ; i < attackers.size() ; ++i)
            attackers[i]->loseHonour();
        for (int i = 0 ; i < attackers.size() ; ++i)
            attackers[i]->itemsWearOut();
    } else if (difference <= 0) { // attack points are equal to or less from opponent's defence points
        std::cout << "Your attack was not successful and you lose all your units\n\n";
        for (int i = 0; i < attackers.size(); ++i)
            delete attackers[i];
        attackers.clear();
    }
    //Checking if any Attacker's Personality has zero honour
    for (int i = 0 ; i < attackers.size() ; ) {
        if (attackers[i]->IsDishonoured()) {    //If yes, kill it
            attackers[i]->performSeppuku();
            attackers.erase(attackers.begin() + i);
            --i;
        } else {
            ++i;
        }
    }
    //Tapping all attacking Units so they can't be used again in this turn
    for (int i = 0; i < attackers.size(); ++i) {
        attackers[i]->tap();
        army.push_back(attackers[i]);
    }
}

/*
 * Defending Phase for PvP part
 * Wait to receive Opponent's Attack Points and Province attacked
 * Send Defence Points
 * Return true if didn't lose, false if lost.
 */
bool Player::defend(PlayerComm& pl)
{
	int attack = 0, defence = 0;
    int attacked_province = 0;
	bool survived = true;                   // false if province was destroyed
	std::string *mes_province;              // message: province getting attacked
    std::string *mes_attack;                // message: attack of enemy units
    char mes_defence[8];                    // message: defence of defending units
	std::vector<Personality*> defenders;    // chosen defending units

	mes_province = pl.readMessage();        //message: number of Province attacked
	mes_attack = pl.readMessage();          //message: opponent's attack points

	attacked_province = atoi(mes_province->c_str());
    // If Province is already destroyed
    if (provinces[attacked_province-1].checkIfDestroyed()) {
        std::cout << "Opponent tried to attack to a destroyed Province and failed...\n\n";
        sprintf(mes_defence, "%d", -1);     // message -1 for Destroyed Province
        pl.sendMessage(mes_defence);
        return true;
    }
	attack = atoi(mes_attack->c_str());
    std::cout << "Province [" << attacked_province << "] is getting attacked\n";
	std::cout << "Opponent units attack points: " << attack << "\n";
	std::cout << "Defend!\n\n";
	chooseUnits(defenders);                 //Choosing Units for defence
	defence = getUnitsDefence(defenders);   //Getting total defence

    // send message: defence points
    sprintf(mes_defence, "%d", defence);
	pl.sendMessage(mes_defence);
    sleep(1);

    //Calculating battle's result
	survived = defendersBattleConsequences(attack, defence, defenders);
    // If Province didn't survive the attack
	if (survived == false)
		provinces[attacked_province-1].destroy();

    // deletes
    delete mes_province;
    delete mes_attack;

    // If Player loses all his provinces
    char mes_win[1];
    if (no_provinces == 0) {
        sprintf(mes_win, "%d", 1);
        pl.sendMessage(mes_win);
        return false;
    } else {
        sprintf(mes_win, "%d", 0);
        pl.sendMessage(mes_win);
        return true;
    }
}

/*
 * Calculates the battle consequences for the defender
 */
bool Player::defendersBattleConsequences
    (int attack, int defence, std::vector<Personality*>& defenders)
{
    int	province_defence = getProvincesDefence();
	int difference = attack-defence-province_defence;

	if (difference > province_defence) {  //Opponent conquers Province
        std::cout << "You lost! The Province under attack was destroyed...\n\n";
		for (int i = 0; i < defenders.size(); ++i)  // defending army dies
            delete defenders[i];
		defenders.clear();
		--no_provinces;                             // minus 1 Province
		return false;
	} else if (difference >= 0) {  // lost defence but not his Province
        std::cout << "The Province was protected but all defending units died...\n\n";
        for (int i = 0; i < defenders.size(); ++i)  // defending army dies
            delete defenders[i];
        defenders.clear();
    } else {  // won the fight but may have lost Army
        std::cout << "You won the fight but you may have casualties!\n\n";
        difference = abs(difference);   // take the absolute value

        /*
         * Player needs to lose Army until he covers a difference
         * between Attack and Defence according to the rules so he
         * chooses defending Units to die until difference is <= 0
         */
        while (chooseToDie(defenders, difference) > 0) {}
    }
    //Tapping defenders left so he can't reuse them until next turn
	for (int i = 0; i < defenders.size(); ++i) {
		defenders[i]->tap();
        army.push_back(defenders[i]);
    }
	return true;
}

/*
 * As a result of a battle Player may need to choose
 * Units that attacked or defended to die. These Units must
 * have a summary of attack points at least equal to "difference".
 * After Player's decision, function returns the difference minus
 * the summary of attack points
*/
int Player::chooseToDie(std::vector<Personality*>& units, int &difference)
{
	int attack = 0;
	std::string str;
	std::vector<int> p_nums;

    if (units.size() == 0)              // if no units were chosen
        return 0;

	attack = getUnitsAttack(units);     // get attack of all Units
    if (attack < difference) {          // if all units can't cover the difference needed
        std::cout << "You lose all your units!...\n";
        std::cout << std::endl;
        for (int i = 0 ; i < units.size() ; ++i)
            delete units[i];
        units.clear();
        return 0;
    }

    //Asking Player to choose Units to die
	std::cout << "Choose units with attack summary at least " << difference << "\n";
	printArmy(units);
    std::cout << "Choose Personalities!\n";
    std::cout << "Input: ";
    std::getline(std::cin, str);            // choose Personalities
    std::cout << std::endl;
    L5R_Library::tokenizer(str, p_nums);    // tokenize input
    std::sort(p_nums.begin(), p_nums.end());
    for (int i = 0 ; i < p_nums.size() ; ++i) {
        if (p_nums[i] >= 1 && p_nums[i] <= units.size()) {
            // Player has the option to kill Followers instead of Personality itself
            if (units[p_nums[i]-1]->getFollowingsSize() > 0) {
                units[p_nums[i]-1]->print();
                if (L5R_Library::question("Want to choose any of the Personality's followers?") == true) {
                    std::vector<int> f_nums;
                    std::cout << "Choose Followers!\n";
                    std::cout << "Input: ";
                    std::getline(std::cin, str);    // choose Followers
                    std::cout << std::endl;

                    L5R_Library::tokenizer(str, f_nums);
                    difference -= units[p_nums[i]-1]->detachFollowers(f_nums);
                }
            }
            // Decide for the Personality at last
            if (L5R_Library::question("Do you want the Personality to die?") == true) {
                difference -= units[p_nums[i]-1]->getTotalAttack();
                delete units[p_nums[i]-1];
                units.erase(units.begin()+p_nums[i]-1);
                for (int j = i+1 ; j < p_nums.size() ; ++j) {
                    --p_nums[j];
                }
            }
        }
    }
    return difference;
}

/*
 * Player chooses Provinces to buy  BlackCards.
 * Province are added to the argument vector.
 */
void Player::chooseProvinces(std::vector<Province*>& provs)
{
    std::vector<int> nums;
    std::string str;

    printProvinces();     //Printing available Black Cards on Provinces

    std::cout << "Choose Provinces to buy from!\n" << "Input: ";
    std::getline(std::cin, str);        // choose Provinces
    std::cout << std::endl;

    L5R_Library::tokenizer(str, nums);               // tokenize input to get every integer

    for (int i = 0 ; i < nums.size() ; ++i) {
        if (nums[i]-1 >= 0 && nums[i]-1 < STARTING_NO_PROVINCES) {
            if (!(provinces[nums[i]-1].checkIfDestroyed()))
                provs.push_back(&provinces[nums[i]-1]);
        }
    }
}

/*
 * Return true if Player can buy the BlackCard.
 * If he can't return false;
 */
bool Player::buyBlackCard(BlackCard* pcard)
{
    int cost = pcard->getCost();

    std::cout << "Buying card:\n";
    pcard->print();
    std::cout << std::endl;

    return (buy(cost));
}

/*
 * Player adds a BlackCard in his Army or Holdings
 */
void Player::addBlackCard(BlackCard* black_card)
{
    Personality* personality;
    Holding* holding;

    //Checking if BlackCard is Personality or Holding
    converter.getCorrectType(black_card, &personality, &holding);
    if (personality != NULL) {
        army.push_back(personality);
    } else {
        addHolding(holding);
    }
}

/*
 * Player draws a BlackCard from the DynastyDeck
 * and places it on the Province
 */
void Player::drawBlackCard(Province& prov)
{
    if (dynastyDeck->size() > 0) {
        prov.addBlackCard(dynastyDeck->front());
        dynastyDeck->pop_front();
    }
}

/*
 * Remove a card from Player's hand and from the game
 */
void Player::discardGreenCard(GreenCard* gcard)
{
	delete gcard;
	hand.erase(find(hand.begin(), hand.end(), gcard));
}

/*
 * Player can be found with MAX_NO_HAND_CARDS+1 in hand,
 * so he needs to be able to discard one.
 */
void Player::discardSurplusGreenCards()
{
	int card;
    std::string str;

    if (getHandSize() > MAX_NO_HAND_CARDS) {
        std::cout << "The number of cards on your hand exceed the limit\n";
        std::cout << "Please choose one to discard\n";
        std::cout << std::endl;
        printHand();
        do {
            std::cout << "Input: ";
            std::getline(std::cin, str);    // choose card to discard
            std::cout << std::endl;

            card = atoi(str.c_str());
            if (card >= 1 && card <= getHandSize()) { // if card exists
                break;
            } else { // if card doesn't exist
                std::cout << "You've given an invalid card number, choose again\n";
                std::cout << std::endl;
            }
        } while (true);
        discardGreenCard(hand[card-1]);    // discard Card
    }
}

/*
 * Asking Player if he wants to discard
 * any BlackCards from his Provinces
 */
void Player::discardProvinceCard()
{
    while (true) {
        std::string answer;

        if (L5R_Library::question("Do you want to discard any Province?") == true) {
            std::string str;
            std::vector<int> nums;

            std::cout << "Choose one or more Provinces you want to discard\n";
            printProvinces();
            std::cout << "Input: ";
			std::getline(std::cin, str);            // choose BlackCard
            std::cout << std::endl;

			L5R_Library::tokenizer(str, nums);
            for (int i = 0 ; i < nums.size() ; ++i) {
                if (nums[i] >= 1 && nums[i] <= 4) {
                     // If chosen Province is not destroyed
                    if (!provinces[nums[i]-1].checkIfDestroyed()) {
                         // If Card is revealed
                        if (provinces[nums[i]-1].getBlackCard()->checkIfRevealed()) {
                            delete provinces[nums[i]-1].removeBlackCard(); // discard it
                            drawBlackCard(provinces[nums[i]-1]);    // draw new
                        } else {
                            std::cout << "Hidden cards cannot be discarded!\n\n";
                        }
                    }
                }
            }
        } else {
            break;
        }
    }
}