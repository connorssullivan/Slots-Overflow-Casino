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
        double playerBalance;
        double gameBalance;// Money for user
        
        //Helper Functions
        double getReward(double, vector<Blackjack::Acard>);
        double startRound(double);
        void deposite();
        //void rewardTable();
        int calculateScore(const vector<Blackjack::Acard>& );

    //Public functions
    public:
        Blackjack(double);
        double start();
        void validate();
        
};

#endif