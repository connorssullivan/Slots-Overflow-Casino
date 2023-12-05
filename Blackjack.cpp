#include "Blackjack.h"

////////////////////////////////////////////////////////////////////////////////////////////////
                            //Constructor//
////////////////////////////////////////////////////////////////////////////////////////////////
Blackjack::Blackjack(double balance):Card(){
    playerBalance = balance; //Set player balance
    gameBalance = 0.00;//Set game balance

}

////////////////////////////////////////////////////////////////////////////////////////////////
                            //Start//
////////////////////////////////////////////////////////////////////////////////////////////////
double Blackjack::start(){
    shuffleCard();//Shufle cards

    std::cout << R"(
  ____
 /\' .\    _____
/: \\__\  / .  /\
\' / . / /____/..\
 \/___/  \'  '\  /
          \'__'\/
)" << endl;


    cout << "\n💵Welcome to Binary Blackjack💵" << endl;
    
    char play; //Holds yes or no

    //While the user has no money ask them if they want to play and how much they want to deposit
    while(gameBalance == 0){
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
            cout << "\nQuiting Binary Blackjack" << endl;
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
                    <<"\n2: Validate"
                    << "\n3: Quit Or Deposit"
                    <<"\nEnter: ";
            while(!(cin >> menuOption) || menuOption < 1 || menuOption > 3)
            {
                cout << "\nYour Game Balance is = $" << gameBalance 
                    <<"\nChoose Option"
                    <<"\n1: Play Round "
                    <<"\n2: Validate" 
                    << "\n3: Quit Or Deposit"
                    <<"\nEnter: ";
                    cin.clear();
                    cin.ignore();
            }
            
            //If user enters 1 then get their bet, and play a hand
            if(menuOption == 1){
                //Get user bet
                double bet = 0.0;

                //Get user bet
                cout << "\nYour Game Balance is = $" << gameBalance 
                        << "\nEnter a bet: ";
                while(!(cin >> bet) || bet < 0 || bet > gameBalance){
                    cout << "\nYour Game Balance is = $" << gameBalance 
                        << "\nEnter a bet: ";
                    cin.clear();
                    cin.ignore();
                }

                //Subtract bet from gameBalance
                gameBalance -= bet;

                bet = startRound(bet);

                //Adjust the game balance based on the users hand
                gameBalance += bet;

            }
            
            if(menuOption == 2){
                validate();
            }

            //If user enters 2, add to the game balance to the player balance and return to previous menu
            if(menuOption == 3) {
                playerBalance += gameBalance; //add the game balance to the  playerBalance
                gameBalance = 0;//Reset game balance
            }
        }
    
    }
    return playerBalance;
}

////////////////////////////////////////////////////////////////////////////////////////////////
                            //Start Rount//
////////////////////////////////////////////////////////////////////////////////////////////////
double Blackjack::startRound(double bet){
    bool insurance = false;

    //Clear Player Hand
    

    //Get player and bot hands
    vector<Blackjack::Acard> playerHand = getHand(2);
    int playerScore = 0;
    playerScore = calculateScore(playerHand);
    vector<Blackjack::Acard> botHand = getHand(2);
    int botScore = calculateScore(botHand);

    //Print both hands
    cout << "\nDealers Hand" << endl;
    printCard(botHand[0]);

    cout << "\n\nPlayers Hand" << endl;
    printCards(playerHand.size(),playerHand);


    cout << endl;

    //If bot has an ace ask the player if they want insurance
    if(botHand[0].num == ACE && playerScore != 21){
        char insuranceOption;
        cout << "Would you like insurance?";
        cout << "\nDo You want to buy Insurance (y, n)? ";
        while(!(cin >> insuranceOption) || (insuranceOption != 'y' && insuranceOption != 'n')){
            cout << "\nDo You want Insurance (y, n)?" << endl;
            cin.clear();
		    cin.ignore();
        }

        //If player wants insurance
        if (insuranceOption == 'y'){
            insurance = true;
        }

        //If bot has 21 and player has insurance return bet
        if(calculateScore(botHand) == 21 && insurance){
            //Print both hands
            cout << "\nDealers Hand" << endl;
            printCards(botHand.size(),botHand);

            cout << "\n\nPlayers Hand" << endl;
            printCards(playerHand.size(),playerHand);

            cout << endl;

            return bet;
        }

        if(calculateScore(botHand) == 21 && !insurance){
            //Print both hands
            cout << "\nDealers Hand" << endl;
            printCards(botHand.size(),botHand);

            cout << "\n\nPlayers Hand" << endl;
            printCards(playerHand.size(),playerHand);

            cout << "\nDealet Hand = " << botScore << endl;
            cout << "Player Hand = " << playerScore << endl;
            cout << "\nYou Lose! Dealer had Blackjack "<<endl;

            cout << endl;

            return 0;
        }

        if(insurance)
            bet = bet/2;
    }
    if(playerScore != 21){
        int option;

        //Ask player to hit or stay or double for first card
        cout <<"\nChoose Option"
                    <<"\n1: Hit " 
                    <<"\n2: Stay"
                    << "\n3: Double "
                    <<"\nEnter: ";
        while(!(cin >> option) || option < 1 || option > 3)
        {
                cout << "\nEnter: ";
                cin.clear();
                cin.ignore();
        }

        //If player doubles after first card
        if(option == 3){
            //Double bet
            bet *= 2;

            //Push back new card
            playerHand.push_back(drawCard());

            //Increment hand Size
        

            //Add to player Score
            playerScore = calculateScore(playerHand);

            //Print both hands
            cout << "\nDealers Hand" << endl;
            printCard(botHand[0]);

            cout << "\n\nPlayers Hand" << endl;
            printCards(playerHand.size(),playerHand);

            cout << "\nDealet Hand = " << botScore << endl;
            cout << "Player Hand = " << playerScore << endl;
            cout << endl;

            //If the player busts
            if(playerScore > 21){
                cout << "\nDeales Hand = " << botScore << endl;
                cout << "Player Hand = " << playerScore << endl;
                cout << "\nYou Busted!"<<endl;
                return 0;
            }
        }

        //If player hits
        if(option == 1){

            //Push back to player hand
            playerHand.push_back(drawCard());

            //Add to player score the new card
            playerScore = calculateScore(playerHand);

            //Set option back to -1
            option = -1;

            //Print both hands
            cout << "\nDealers Hand" << endl;
            printCard(botHand[0]);

            cout << "\n\nPlayers Hand" << endl;
            printCards(playerHand.size(),playerHand);
            cout << "\nPlayer Hand = " << playerScore << endl;//print player score

            cout << endl;

            //Ask if user wants to hit or stay while they are below 21
            while(playerScore < 21 && option != 2){
                cout <<"\nChoose Option"
                    <<"\n1: Hit " 
                    <<"\n2: Stay"
                    <<"\nEnter: ";
                while(!(cin >> option) || option > 2 || option < 1){//Validate user input
                    cout << "\nEnter: ";
                    cin.clear();
                    cin.ignore();
                }

                //If user Hits
                if(option == 1){
                    playerHand.push_back(drawCard());//draw card
                    playerScore = calculateScore(playerHand);
                }
                //Print both hands
                cout << "\nDealers Hand" << endl;
                printCard(botHand[0]);

                cout << "\n\nPlayers Hand" << endl;
                printCards(playerHand.size(),playerHand);
                cout << "\nPlayer Hand = " << playerScore << endl;//print player score
            }

            //Print both hands
            cout << "\nDealers Hand" << endl;
            printCard(botHand[0]);

            cout << "\n\nPlayers Hand" << endl;
            printCards(playerHand.size(),playerHand);
            cout << endl;

            //If the player busts
            if(playerScore > 21){
                cout << "\nYou Busted!"<<endl;
                return 0;
            }

        }
    }


    //Print both hands
    cout << "\nDealers Hand" << endl;
    printCards(botHand.size(),botHand);

    cout << "\n\nPlayers Hand" << endl;
    printCards(playerHand.size(),playerHand);
    cout << endl;

    //draw for bot 
    while(botScore < 17){
        cout << "\nDrawing For dealer please wait" << endl;
        sleep(3);

        //Draw another card
        botHand.push_back(drawCard());

        //Add to bot score
        botScore = calculateScore(botHand);

        //Print Dealers Hand
        cout << "\nDealers Hand" << endl;
        printCards(botHand.size(),botHand);

 

    }

    //Test
    cout << endl;
    for(Acard card : botHand)
        cout << card.num << endl;

    //Get total bot score
    playerScore = calculateScore(playerHand);
    botScore = calculateScore(botHand);

    cout << "\nDealers Hand" << endl;
            printCards(botHand.size(),botHand);

    cout << "\n\nPlayers Hand" << endl;
    printCards(playerHand.size(),playerHand);

    //If Dealer busts
    if(botScore > 21){
        cout << "\nDealers Hand = " << botScore << endl;
        cout << "Player Hand = " << playerScore << endl;
        cout << "\nYou Win! "<<endl;
        return bet*2;
    }

    //If it is a tie
    if(playerScore == botScore){
        cout << "\nDealers Hand = " << botScore << endl;
        cout << "Player Hand = " << playerScore << endl;
        cout << "\nYou Tied! "<<endl;
        return bet;
    }
    
    if(botScore > playerScore){
        cout << "\nDealers Hand = " << botScore << endl;
        cout << "Player Hand = " << playerScore << endl;
        cout << "\nYou Lose! "<<endl;
        return 0;
    }
    
    if(playerScore > botScore){
        cout << "\nDealet Hand = " << botScore << endl;
        cout << "Player Hand = " << playerScore << endl;
        cout << "\nYou Win! "<<endl;
        return bet*2;
    }

}

////////////////////////////////////////////////////////////////////////////////////////////////
                            //Deposite//
////////////////////////////////////////////////////////////////////////////////////////////////
void Blackjack::deposite(){
    //Ask for user money
    double money;
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


////////////////////////////////////////////////////////////////////////////////////////////////
                            //Calculate Score//
////////////////////////////////////////////////////////////////////////////////////////////////
int Blackjack::calculateScore(const vector<Blackjack::Acard>& hand){
    int score = 0;
    int numAces = 0;

    for (const Acard& card : hand) {
        if(card.num > 10) //Check if its king or queen
            score += 10;
        else score += card.num; //If its lower then queen

        // Check if the card is an Ace
        if (card.num == 1) {
            ++numAces;
        }
    }

    // Adjust score for Aces
    while (numAces > 0 && score + 10 <= 21) {
        score += 10;
        --numAces;
    }

    return score; 
}

////////////////////////////////////////////////////////////////////////////////////////////////
                            //Validate any hand//
////////////////////////////////////////////////////////////////////////////////////////////////
void Blackjack::validate(){
    int handSize;
    cout << "\nEnter a hand size: ";
    while(!(cin >> handSize)){
        cout << "Enter: ";
        cin.clear();
        cin.ignore();
    }

    //Create custom hand
    vector<Acard> hand = customHand(handSize);

    //Print the cards
    //printCards(handSize,hand); Unesesary

    //Show the hand
    int score = calculateScore(hand);

    cout << "\n\nHand Score: " << score;
}

