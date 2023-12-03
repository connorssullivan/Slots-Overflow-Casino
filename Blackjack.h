#include <iostream>
#include <unordered_map>
#include <thread> 
#include <chrono> 

#include "Card.h"

#ifndef Blackjackr_h
#define Blackjack_h

using namespace std;

class Blackjack: public Card{
    
    private:
    //Private members
        int playerBalance;
        int gameBalance;// Money for user
        
        //Helper Functions
        int getReward(int, vector<Blackjack::Acard>);
        int startRound(int);
        void deposite();
        //void rewardTable();
        int calculateScore(const vector<Blackjack::Acard>& );

    //Public functions
    public:
        Blackjack(int);
        int start();
        void validate();
        
};

#endif