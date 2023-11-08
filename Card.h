//Librarys
#include <iostream>
#include<vector>
#include <cstring>
#include <ctime>
#include <cstdlib>
#include <unistd.h> 
#include <stdio.h>
#include <cstdlib>
#include <unordered_map>



#ifndef CARD_h
#define CARD_h

using namespace std;
class Card {
public:
    //Acard structure
    struct Acard {
        int num;
        char pic[4];
    };

    //Node structure
    struct Node{
        char str[25];
        Node* next;
    };

    //Head of each line
    vector<Node*> heads;

    //deck
    vector<Acard> deck;
    int nextCard; //!!!Important not index of the card, if you want index subtract 1 !!!!!!!!!!!!

    //Cards Symbols
    const char spade[4] ="\xe2\x99\xa0";
    const char club[4] ="\xe2\x99\xa3";
    const char heart[4] ="\xe2\x99\xa5";
    const char diamond[4] ="\xe2\x99\xa6";

    //Used to keep track of suite order
    enum Suite{
        SPADE=1,CLUB,HEART,DIAMOND
    };

    //Used ro keep track of rank order
    enum Rank{
            ACE=1,TWO,THREE,FOUR,FIVE,SIX,SEVAN,EIGHT,NINE,TEN,JACK,QUEEN,KING
    };

    //Private Functions
    void getCardFunc(Acard card, int row);
    char* getPic(Acard* card);
    void cardAce(const char card[], int row); 
    void cardTwo(const char card[], int row);
    void cardThree(const char card[], int row);
    void cardFour(const char card[], int row);
    void cardFive(const char card[], int row);
    void cardSix(const char card[], int row);
    void cardSeven(const char card[], int row);
    void cardEight(const char card[], int row);
    void cardNine(const char card[], int row);
    void cardTen(const char card[], int row);
    void cardJack(const char card[], int row);
    void cardQueen(const char card[], int row);
    void cardKing(const char card[], int row);

    void createHeads(int numberOfCards, int cols);
    void deleteHeads();
    Acard drawCard();
    
    //Functions
    Card();
    ~Card();
    void shuffleCard();
    void printDeckPart1Test(); //My function
    void printCard();
    void printCards(int rowSize, vector<Acard> dk);
    vector<Acard> getHand(int numCards);
    vector<Acard> customHand(int);

    
};

#endif

