#include "Card.h"
#include "Poker.h"

int main(){
    int playerBalance = 1000;
    while(true){
        int mainMenuOption = -1;
        cout << "\n💵Welcome to Slot Overflow Casino💵\n\n" 
                << "\nYour Balance is: $" << playerBalance
                << "\n1: Play Poker With Pointers" 
                << "\n2: Play Binary Blackjack" 
                << "\n3: Quit"
                << "\nEnter: ";
        while(!(cin >> mainMenuOption) || mainMenuOption < 1 || mainMenuOption > 3){
            cout << "\n💵Welcome to Slot Overflow Casino💵\n\n" 
                << "\nYour Balance is: $" << playerBalance
                << "\n1: Play Poker With Pointers" 
                << "\n2: Play Binary Blackjack" 
                << "\n3: Quit"
                << "\nEnter: ";
                cin.ignore();
                cin.clear();
        }

        //When defining blackjack we can name it binary blackjack
        if(mainMenuOption == 1){
            Poker p(playerBalance);
            playerBalance = p.start();
        }

        if(mainMenuOption == 3)
            break;
    }

    
    

    return 0;
}