#include "Poker.h"


////////////////////////////////////////////////////////////////////////////////////////////////
                            //Constructor //
////////////////////////////////////////////////////////////////////////////////////////////////
Poker::Poker(int balance):Card(){
    playerBalance = balance; //Set player balance
    gameBalance = 0;//Set game balance

}

////////////////////////////////////////////////////////////////////////////////////////////////
                            //Start//
////////////////////////////////////////////////////////////////////////////////////////////////
int Poker::start(){
    shuffleCard();//Shufle cards

    cout << "\n💵Welcome to Poker With Pointers💵" << endl;
    
    char play; //Holds yes or no

    //While the user has no money ask them if they want to play and how much they want to deposit
    while(gameBalance < 1){
        //Ask the user if they want to play
        cout << "\nYou need to have at least 1 💵 in your game balance to play\nYour Total 💵 is  " << playerBalance << endl;
        cout << "\nDo You want to play (y, n)? ";
        while(!(cin >> play) || (play != 'y' && play != 'n')){
            cout << "\nDo You want to play (y, n)?" << endl;
            cin.clear();
		    cin.ignore();
        }

        //If user wants to quit then quit
        if(play == 'n'){
            cout << "\nQuiting Poker With Pointers" << endl;
            return playerBalance;
        }

        //Deposit money into the game balance
        deposite();

        
        //Loop through the game until the game balance is 0, this can happen due to loss, or it could also end because of maual input
        while(gameBalance > 0){

            //Print game menu and get user input
            int menuOption;
            cout << "\nYour Game Balance is = $" << gameBalance 
                    <<"\nChoose Option"
                    <<"\n1: Play Round " 
                    << "\n2: Quit "
                    <<"\nEnter: ";
                    cin.ignore();
                    cin.clear();
            while(!(cin >> menuOption) || menuOption < 1 || menuOption > 2)
            {
                cout << "\nYour Game Balance is = $" << gameBalance 
                    <<"\nChoose Option"
                    <<"\n1: Play Round " 
                    << "\n2: Quit "
                    <<"\nEnter: ";
                    cin.ignore();
                    cin.clear();
            }
            
            //If user enters 1 then get their bet, and play a hand
            if(menuOption == 1){
                //Get user bet
                int bet = 0;

                //Get user bet
                cout << "\nYour Game Balance is = $" << gameBalance 
                        << "\nEnter a bet: ";
                while(!(cin >> bet) || bet < 1 || bet > gameBalance){
                    cout << "\nYour Game Balance is = $" << gameBalance 
                        << "\nEnter a bet: ";
                    cin.ignore();
                    cin.clear();
                }

                //Subtract bet from gameBalance
                gameBalance -= bet;

                //Get a hand
                vector<Poker::Acard> currentHand = startRound();
                
                //Get the reward for the hand
                int mult = getReward(gameBalance, currentHand);
                cout << "\nYour multiplier is " << mult << endl;
                bet *= mult;

                //Adjust the game balance based on the users hand
                gameBalance += bet;
            }

            //If user enters 2, add to the game balance to the player balance and return to previous menu
            if(menuOption == 2) {
                playerBalance += gameBalance; //add the game balance to the  playerBalance
                gameBalance = 0;//Reset game balance
            }
        }
    
    }
    return playerBalance;
}

////////////////////////////////////////////////////////////////////////////////////////////////
                            //StartRound//
////////////////////////////////////////////////////////////////////////////////////////////////
vector<Poker::Acard> Poker::startRound(){
    //Get how much the user wants to bet this round

    vector<Poker::Acard> currentHand = getHand(handSize);//Get the players initial hand

    //Display hand and ask the user what if they want to hold or redraw each card
    printCards(handSize, currentHand);

    //Ask the user if they would like to change their cards
    cout << endl;
    for(int i =0; i < currentHand.size();i++){
        cout << currentHand[i].num << currentHand[i].pic << " "<<i+1 <<": Hold(0), Redraw(1)?";

        //Input validation
        int hold = -1;
        while(!(cin >> hold) || (hold != 0 && hold!= 1)){
            cout << "\n"<<currentHand[i].num << currentHand[i].pic << i+1 <<": Hold(0), Redraw(1)?";
            cin.clear();
		    cin.ignore();
        }

        //If user enters 1 redraw
        if(hold == 1){
            Poker::Acard a = drawCard();
            currentHand[i] = a;
        }
    }

    //Print and return the new hand
    printCards(handSize, currentHand);
    return currentHand;

}


////////////////////////////////////////////////////////////////////////////////////////////////
                            //Get Reward//
////////////////////////////////////////////////////////////////////////////////////////////////

int Poker::getReward(int bet, vector<Poker::Acard> hand){
    int multiplier = 0;

    //Make a pap for the hands suits and ranks
    unordered_map<char,int> suits; 
    unordered_map<int, int> ranks;

    //Put the cards in a map
    for(Poker::Acard& card : hand){

        //Add one to Spade map
        if(strcmp(card.pic, spade) == 0)
            ++suits['s']; 


        //Add one to club map
        if(strcmp(card.pic, club) == 0)
            ++suits['c']; 

        //Add one to heartmap
        if(strcmp(card.pic, heart) == 0)
            ++suits['h']; 

        //Add one to Diamond map
        if(strcmp(card.pic, diamond) == 0)
            ++suits['d']; 

        ++ranks[card.num];
    }


    //Determine if it's a royal flush
    if(suits.size() == 1 && ranks[ACE] && ranks[KING] && ranks[QUEEN] && ranks[JACK] && ranks[TEN])
        multiplier = ROYAL_FLUSH;

    //If straight flush
    if(multiplier == 0  && suits.size() == 1){

        //If the ranks of the hand are in order, multiplier will be set to straight flush
        int prevRank = 0;
        for(const auto rank : ranks){

            //If they are not in order
            if(prevRank != 0 && (prevRank+1) != rank.first){
                prevRank = -1; //Indicates not a flush
                break;
            }
            prevRank = rank.first; //Update prev rank
        }

        //Check if it is sequential
        if(prevRank != -1)
            multiplier = STRAIGHT_FLUSH;
    }

    //If Four of a kind
    if(multiplier == 0  && ranks.size() <= 2){
        bool fourKind = false;

        //Go through the ranks of cards
        for(const auto rank : ranks) 
            if(rank.second == 4) //If four of the same card are found, set fourKind to true
                fourKind = true;

        if(fourKind)
            multiplier = FOUR_CARD;
        
    }

    //Full house
    if(multiplier == 0 && ranks.size() == 2){
        bool kind3 = false; //Keep track three of 1 card is found

        //Go through the ranks of cards
        for(const auto rank : ranks) 
            if(rank.second == 3) //If four of the same card are found, set fourKind to true
                kind3 = true;

        if(kind3)
            multiplier = FULL_HOUSE;
    }

    //If flush
    if(multiplier == 0 && suits.size() == 1){
        multiplier = FLUSH; //If theres is only 1 suite it's a flush
    }

    //If straight
    if(multiplier == 0 && ranks.size() == 5){
        bool first = true; //Flag for if it's first
        bool straight = false; //Flag for if it's a straight
        int prev; //For previous card

        //Loop through the ranks present
        for(auto card : ranks){
            if(!first && card.first != prev+1){
                straight = false;
                break;
            }

            prev = card.first;
            first = false; //Start comparing
        }

        if(straight) 
            multiplier = STRAIGHT;
    }

    //If three of a kind
    if(multiplier == 0){
        bool threeKind = false;

        for(const auto rank : ranks) 
            if(rank.second == 3) //If you find 3 of the same cards set three kinds to true
                threeKind = true;

        //If three kind is true, then change multiplier
        if(threeKind)
            multiplier = TRIPLE;
    }

    //If two of a kind
    if(multiplier == 0){
        bool twoKind = false; //Check if two cards are found

        for(const auto rank : ranks) 
            if(rank.second == 2) //If you find 2 of the same cards set three kinds to true
                twoKind = true;

        //If three kind is true, then change multiplier
        if(twoKind)
            multiplier = TRIPLE;
    }

    if(multiplier == 0){
        bool highCard = false; //Check if a card is a high card or better

        for(auto card : hand){
            if(card.num > 10){
                highCard = true;
                break;
            }
        }

        if(highCard)
            multiplier = 1;
    }

    return multiplier;
}


////////////////////////////////////////////////////////////////////////////////////////////////
                            //Deposite//
////////////////////////////////////////////////////////////////////////////////////////////////
void Poker::deposite(){

    //Ask for user money
    int money;
    cout <<"\nDeposit 💵: ";
    while(!(cin >> money) || money > playerBalance){ //get the amount of money deposited
        cout << "\nYou only have " << playerBalance << endl;
        cout << "Deposit valid 💵: ";
        cin.clear();
		cin.ignore();
    }

    //if the deposited money is less then 0 then make it 0
    if(money < 0)
        money = 0;

    //Adjust the balances
    gameBalance += money;
    playerBalance -= money;

    //Output the new Game balance
    cout << "\nDeposited $" << money << endl;
    cout << "Game balance is now " << gameBalance << " 💵"<< endl;
}

