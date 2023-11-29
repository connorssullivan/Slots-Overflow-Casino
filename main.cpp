#include "Card.h"
#include "Poker.h"
#include "Blackjack.h"
#include <fstream>

int main(){
    ifstream input; //Set up if stream
    char name[50]; //Player name
    char tempName[50];
    char password[50]; //Player password
    char tempPassword[50];
    int playerBalance;
    int tempPlayerBalance;
    char enteredName[50];
    char enteredPasword[50];
    bool nameFound = false;
    
    //Open File
    input.open("login.txt", ios::in);
    if(!input){//On error
        cerr << "\nNo file found" <<endl;
        exit(1);
    }

    //Get users name and password
    while(!nameFound){
        cout << "\nEnter Your Name: ";
        while (!(cin >> enteredName)){//Validate name
            cin.clear();
            cin.ignore();
        }

        //Search through the file 
        while(!input.eof()){
            while(input >> tempName >> tempPassword >> tempPlayerBalance){
                if(strcmp(tempName, enteredName) == 0){//Return the last instance of the name
                    nameFound = true;
                    strcpy(name, tempName);
                    strcpy(password, tempPassword);
                    playerBalance = tempPlayerBalance;
                }
            }
        }

        //If name not found
        if(!nameFound && input.eof()){
            cout << "\nSorry Thats not in our system, Please Talk to the cashiers office to set up an account" << endl;
            input.close(); //Close file
            return -1;
        }

    }
   
    //Get password
    cout << "Enter password:";
    while (!(cin >> enteredPasword)){//Validate password
            cin.clear();
            cin.ignore();
    }

    //Check password
    if(strcmp(password, enteredPasword) != 0){
        cout << "\nSorry Thats not the correct password, Please Talk to the cashiers office to retreive your password" << endl;
        input.close();
        return -1;
    }

    //Main loop
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


    input.close();

    // Output to the file
    ofstream output("login.txt", ios::app);
    if(!output){
        cout << "error" << endl;
        return -1;
    }

   output << "\n"<<name << " "<< password << " " << playerBalance;

    output.close();
    
    return 0;
}