#include "Card.h"
#include "Poker.h"
#include "Blackjack.h"

int main(){
    int playerBalance = 1000;
    while(true){
        int mainMenuOption = -1;

          
  std::cout << R"(
 _________.__          __    ________                      _____.__ 
/   _____/|  |   _____/  |_  \_____  \___  __ ____________/ ____\  |   ______  _  __
\_____  \ |  |  /  _ \   __\  / | |   \  \/ // __ \_  __ \   __\|  |  /  _ \ \/ \/ /
/        \|  |_(  <_> )  |   /  |_|    \   /\  ___/|  | \/|  |  |  |_(  <_> )     / 
/_______ /|____/\____/|__|   \_______  /\_/  \___  >__|   |__|  |____/\____/ \/\/ 
)" << std::endl;
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
                cin.clear();
                cin.ignore();
        }

        //Poker with Pointers
        if(mainMenuOption == 1){
            Poker p(playerBalance);
            playerBalance = p.start();
        }

        //Binary blackjack
        if(mainMenuOption == 2){
            Blackjack bj(playerBalance);
            playerBalance = bj.start();
        }


        if(mainMenuOption == 3){
            cout << "\nThank you for playing at Slots overflow casino, We hope to see you again!" << endl;
            break;
        }
    }

    
    

    return 0;
}