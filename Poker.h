#include <iostream>
#include <unordered_map>

#include "Card.h"

#ifndef Poker_h
#define Poker_h

using namespace std;

class Poker: public Card{
    
    private:
    //Private members
        int playerBalance;
        int gameBalance;// Money for user
        const int handSize = 5; //Hand size
        enum {JACK_UP = 1, TRIPLE = 4, STRAIGHT = 6, FLUSH = 10, FULL_HOUSE = 100, FOUR_CARD = 1000, STRAIGHT_FLUSH = 10000, ROYAL_FLUSH = 10000};
        
        //Helper Functions
        int getReward(int, vector<Poker::Acard>);
        vector<Poker::Acard> startRound();
        void deposite();
        void rewardTable();

    //Public functions
    public:
        Poker(int);
        int start();
        void validate();
        
};

#endif