#include "Card.h"

////////////////////////////////////////////////////////////////////////////////////////////////
                            //Constructor //
////////////////////////////////////////////////////////////////////////////////////////////////
Card::Card(){
    nextCard = 0;

    for(int suit = SPADE; suit <= DIAMOND; suit++){
        for(int rank = ACE; rank <= KING; rank++){
            //Create new card
            Acard newCard;
            //Set card Rank
            newCard.num = rank;

            //Switch to set card suite
            switch(suit) {
                //Set pic as spade
                case SPADE:
                    strcpy(newCard.pic, spade);
                    break;
                
                //Set pic as club
                case CLUB:
                    strcpy(newCard.pic, club);
                    break;

                //Set pic to heart
                case HEART:
                    strcpy(newCard.pic, heart);
                    break;

                //Set pic to diamond
                case DIAMOND: 
                    strcpy(newCard.pic, diamond);
                    break;

            }
            deck.push_back(newCard);
            ++nextCard;
        }
    }

    //cout << "First card is " << deck[0].num << " of " << deck[0].pic << endl;  
}

////////////////////////////////////////////////////////////////////////////////////////////////
                            //DeConstructor //
////////////////////////////////////////////////////////////////////////////////////////////////
Card::~Card(){
    Node* curr;
    Node* nx;

    //Go through the heads array
    for(int i = 0; i < heads.size();i++){
        curr = heads[i];

        //Delete each node
        while(curr){
            nx = curr->next;
            delete curr;
            curr = nx;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////
                            //Delete heads //
////////////////////////////////////////////////////////////////////////////////////////////////
void Card::deleteHeads(){
    Node* curr;
    Node* nx;

    //Go through the heads array
    for(int i = 0; i < heads.size();i++){
        curr = heads[i];

        //Delete each node
        while(curr){
            nx = curr->next;
            delete curr;
            curr = nx;
        }
    }

    heads.clear();
}


////////////////////////////////////////////////////////////////////////////////////////////////
                            //Get card Function //
////////////////////////////////////////////////////////////////////////////////////////////////
void Card::getCardFunc(Acard card,int row){
    int num = card.num;
    
    switch (num)
    {
    case ACE:
        cardAce(card.pic, row);
        break;
    case TWO:
        cardTwo(card.pic, row);
        break;
    case THREE: 
        cardThree(card.pic, row);
        break;
    case FOUR:
        cardFour(card.pic, row);
        break;
    case FIVE:
        cardFive(card.pic, row);
        break;
    case SIX:
        cardSix(card.pic, row);
        break;
    case SEVAN:
        cardSeven(card.pic, row);
        break;
    case EIGHT:
        cardEight(card.pic, row);
        break;
    case NINE:
        cardNine(card.pic, row);
        break;
    case TEN:
        cardTen(card.pic, row);
        break;
    case JACK:
        cardJack(card.pic, row);
        break;
    case QUEEN:
        cardQueen(card.pic, row);
        break;
    case KING:
        cardKing(card.pic, row);
        break;
    default:
        Acard defaultCard;
        strcpy(defaultCard.pic,spade);
        defaultCard.num=1;
        cardAce(defaultCard.pic, row);
        break;
    
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////
                            //Draw Card //
////////////////////////////////////////////////////////////////////////////////////////////////
Card::Acard Card::drawCard(){
    --nextCard;//Subrtact from next card

    //If next card is < 0, then we have to shuffle
    if(nextCard < 0){
        //cout << "\nShuffling cards at index " << nextCard<<endl; 
        shuffleCard();
        nextCard = 52;//Set the 1 more then after last index
    }

    //Get the top card
    //cout << "\nIndex: " << nextCard << endl;
    //cout << "Deck Size: " << deck.size() << endl;
    Acard topCard = deck[nextCard];
    
    return topCard;
}


////////////////////////////////////////////////////////////////////////////////////////////////
                            //Get Hand //
////////////////////////////////////////////////////////////////////////////////////////////////
vector<Card::Acard> Card::getHand(int numCards){
    vector<Acard> hand;//The hand

    //Draw numCards and push to hand
    for(int i = 0;i < numCards;i++)
        hand.push_back(drawCard());
    
    return hand;
}

////////////////////////////////////////////////////////////////////////////////////////////////
                            //Print Card //
////////////////////////////////////////////////////////////////////////////////////////////////
void Card::printCard(Acard card){
    if(!heads.empty())
        deleteHeads();

    //Create the heads
    createHeads(1, 1); 
    for(int i = 0; i < heads.size(); i+=11)
        getCardFunc(card,i);

    //Print cards
    Node* curr;
    for(int i = 0; i < heads.size(); i++){
        curr = heads[i];
        while(curr){
            cout << curr->str;
            curr = curr->next;
        }
    }

}

////////////////////////////////////////////////////////////////////////////////////////////////
                            //Print Cards //
////////////////////////////////////////////////////////////////////////////////////////////////
void Card::printCards(int rowSize, vector<Acard> dk){
    //If there are heads from the old output delete them
    if(!heads.empty())
        deleteHeads();

    
    //Create the heads
    createHeads(dk.size(), rowSize);   


    int index = 0; //Index of dk
    for(int i = 0; i < heads.size(); i+=11){

        for(int j = rowSize; j > 0; j--){
            getCardFunc(dk[index],i); //Get the card function
            //cout << "Card Symbol is " << dk[index].pic << endl;
            ++index;//Iterate through cards
        }
    }

    //Print cards
    Node* curr;
    for(int i = 0; i < heads.size(); i++){
        curr = heads[i];
        while(curr){
            cout << curr->str;
            curr = curr->next;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////
                            //Get Pic //
////////////////////////////////////////////////////////////////////////////////////////////////
char* Card::getPic(Acard* card){
    char* pic = card->pic;
    return pic;
}

////////////////////////////////////////////////////////////////////////////////////////////////
                            //Shuffle Cards //
////////////////////////////////////////////////////////////////////////////////////////////////
void Card::shuffleCard() {
    //Set up random generator
    int r;
    srand(static_cast<unsigned>(time(NULL)));

    //Go through cards
    for (int i = nextCard-1; i >= 0; i--) {
        //cout << "Card "<< i << ": "<< deck[i].pic<< deck[i].num << endl;

        // Generate random number between 0 and i
        r = rand() % (i+1);
        if(r > 51 || r < 0)
            cout << "R is " << r;

        //Swap the cards 
        Acard temp = deck[r];
        deck[r] = deck[i];
        deck[i] = temp;

        //cout << "\nPost Shuffle" << endl;
        //cout << "Card "<< i << deck[i].pic<< deck[i].num << endl;

    }
}


////////////////////////////////////////////////////////////////////////////////////////////////
                            //Create heads //
////////////////////////////////////////////////////////////////////////////////////////////////
void Card::createHeads(int numberOfCards, int cols){

    int numberOfRows = (numberOfCards/cols)*11; //Get the number of rows
    //Make the heads of each line
    for(int i = 0; i < numberOfRows; i++){
        //cout << "Head #" << i << endl;
        //Make new head
        Node* head = new Node;
        head->next = NULL;
        strcpy(head->str, "\n");

        //Push back head 
        heads.push_back(head);

        //If enough space is allocated
        if(i*cols >= numberOfCards*11)
            break;


    }
    
}

////////////////////////////////////////////////////////////////////////////////////////////////
                            //Custom hand //
////////////////////////////////////////////////////////////////////////////////////////////////
vector<Card::Acard> Card::customHand(int handSize){
        vector<Acard> hand;
        cout << "\nEnter " << handSize << " Cards" << endl;
        for(int i = 0; i < handSize; i++){
            
            Acard card;//Initalize card
            
            //Get card Numbe
            int num = -1;
            cout << "\nCard " << i+1 << endl;
            cout << "Enter a number between 1 and 13\nEnter: ";
            while(!(cin >> num) || num < 1 || num > 13){
                cout << "Enter: ";
                cin.clear();
                cin.ignore();
            }

            //Get card Suite
            int s = -1;
            cout << "\nCard " << i+1 << endl;
            cout << "1: Spade\n2: Club \n3: Heart\n4: Diamond\nEnter: ";
            while(!(cin >> s) || s < 1 || s > 4){
                cout << "Enter: ";
                cin.clear();
                cin.ignore();
            }

            //Put card Suite into card.pic
            card.num = num;
            switch (s)
            {
            case 1:
                strcpy(card.pic, spade);
                break;
            case 2:
                strcpy(card.pic, club);
                break;
            case 3:
                strcpy(card.pic, heart);
                break;
            case 4:
                strcpy(card.pic, diamond);
                break;
        
            }

            hand.push_back(card);
        }

        printCards(handSize, hand);
        return hand;
}

////////////////////////////////////////////////////////////////////////////////////////////////
                            //Start Of Card Functions //
////////////////////////////////////////////////////////////////////////////////////////////////
void Card::cardAce(const char card[], int row) {
    Node* curr;
    Node* line;
    
    // Loop through each line 
    for (int i = 0; i < 11; i++) {
        curr = heads[row + i];
        line = new Node;
        line->next = nullptr;

        //Top of card
        if (i == 0) {
            strcpy(line->str, " _____ ");
        } 
        else if (i == 1) {
            strcpy(line->str, "|A    |");
        } 
        
        //Middle of card
        else if (i == 5) {
            strcpy(line->str, "|  ");
            strcat(line->str, card);
            strcat(line->str, "  |");
        } 
        
        //Bottom of card
        else if (i == 10) {
            strcpy(line->str, " ‾‾‾‾‾ ");
        } 

        
        //Bottom of card
        else if (i == 9) {
            strcpy(line->str, "|    A|");
        } 

        //Body of card
        else {
            strcpy(line->str, "|     |");
        }

        //Update the list
        while (curr->next) {
            curr = curr->next;
        }
        curr->next = line;
    }
}

void Card::cardTwo(const char card[], int row) {
    Node* curr;
    Node* line;
    
    // Loop through each line 
    for (int i = 0; i < 11; i++) {
        curr = heads[row + i];
        line = new Node;
        line->next = nullptr;

        //Top of card
        if (i == 0) {
            strcpy(line->str, " _____ ");
        } 
        else if (i == 1) {
            strcpy(line->str, "|2    |");
        } 
        
        //Middle of card
        else if (i == 2 || i == 6) {
            strcpy(line->str, "|  ");
            strcat(line->str, card);
            strcat(line->str, "  |");
        } 
        
        //Bottom of card
        else if (i == 9) {
            strcpy(line->str, "|    2|");
        } 
        else if (i == 10) {
            strcpy(line->str, " ‾‾‾‾‾ ");
        } 

        //Body of card
        else {
            strcpy(line->str, "|     |");
        }

        while (curr->next) {
            curr = curr->next;
        }
        curr->next = line;
    }
}


void Card::cardThree(const char card[], int row) {
    Node* curr;
    Node* line;
    
    // Loop through each line 
    for (int i = 0; i < 11; i++) {
        curr = heads[row + i];
        line = new Node;
        line->next = nullptr;

        //Top of card
        if (i == 0) {
            strcpy(line->str, " _____ ");
        } 
        else if (i == 1) {
            strcpy(line->str, "|3    |");
        } 
        
        //Middle of card
        else if (i == 3 || i == 5 || i == 7) {
            strcpy(line->str, "|  ");
            strcat(line->str, card);
            strcat(line->str, "  |");
        } 

        
        //Bottom of card
        else if (i == 9) {
            strcpy(line->str, "|    3|");
        } 
        else if (i == 10) {
            strcpy(line->str, " ‾‾‾‾‾ ");
        } 

        //Body of card
        else {
            strcpy(line->str, "|     |");
        }

        while (curr->next) {
            curr = curr->next;
        }
        curr->next = line;
    }
}


void Card::cardFour(const char card[], int row) {
    Node* curr;
    Node* line;
    
    // Loop through each line 
    for (int i = 0; i < 11; i++) {
        curr = heads[row + i];
        line = new Node;
        line->next = nullptr;

        //Top of card
        if (i == 0) {
            strcpy(line->str, " _____ ");
        } 
        else if (i == 1) {
            strcpy(line->str, "|4    |");
        } 
        
        //Middle of card
        else if (i == 2 || i == 8) {
            strcpy(line->str, "| ");
            strcat(line->str, card);
            strcat(line->str, " ");
            strcat(line->str, card);
            strcat(line->str, " |");
        } 
        
        //Bottom of card
        else if (i == 9) {
            strcpy(line->str, "|    4|");
        } 
        else if (i == 10) {
            strcpy(line->str, " ‾‾‾‾‾ ");
        } 

        //Body of card
        else {
            strcpy(line->str, "|     |");
        }

        while (curr->next) {
            curr = curr->next;
        }
        curr->next = line;
    }
}


void Card::cardFive(const char card[], int row) {
    Node* curr;
    Node* line;
    
    // Loop through each line 
    for (int i = 0; i < 11; i++) {
        curr = heads[row + i];
        line = new Node;
        line->next = nullptr;

        //Top of card
        if (i == 0) {
            strcpy(line->str, " _____ ");
        } 
        else if (i == 1) {
            strcpy(line->str, "|5    |");
        } 
        

        //Middle
        else if (i == 2 || i == 8) {
            strcpy(line->str, "| ");
            strcat(line->str, card);
            strcat(line->str, " ");
            strcat(line->str, card);
            strcat(line->str, " |");
        } 
        else if (i == 5) {
            strcpy(line->str, "|  ");
            strcat(line->str, card);
            strcat(line->str, "  |");
        } 

        else if (i == 9) {
            strcpy(line->str, "|    5|");
        } 

        else if (i == 10) {
            strcpy(line->str, " ‾‾‾‾‾ ");
        } 

        //Body of card
        else {
            strcpy(line->str, "|     |");
        }

        while (curr->next) {
            curr = curr->next;
        }
        curr->next = line;
    }
}


void Card::cardSix(const char card[], int row) {
    Node* curr;
    Node* line;
    
    // Loop through each line 
    for (int i = 0; i < 11; i++) {
        curr = heads[row + i];
        line = new Node;
        line->next = nullptr;

        //Top of card
        if (i == 0) {
            strcpy(line->str, " _____ ");
        } 
        else if (i == 1) {
            strcpy(line->str, "|6    |");
        } 
        
        else if (i == 2 || i == 5 ||  i == 8) {
            strcpy(line->str, "| ");
            strcat(line->str, card);
            strcat(line->str, " ");
            strcat(line->str, card);
            strcat(line->str, " |");
        } 
        
        //Bottom of card
        else if (i == 9) {
            strcpy(line->str, "|    6|");
        } 
        else if (i == 10) {
            strcpy(line->str, " ‾‾‾‾‾ ");
        } 

        //Body of card
        else {
            strcpy(line->str, "|     |");
        }

        while (curr->next) {
            curr = curr->next;
        }
        curr->next = line;
    }
}


void Card::cardSeven(const char card[], int row) {
    Node* curr;
    Node* line;
    
    // Loop through each line 
    for (int i = 0; i < 11; i++) {
        curr = heads[row + i];
        line = new Node;
        line->next = nullptr;

        //Top of card
        if (i == 0) {
            strcpy(line->str, " _____ ");
        } 
        else if (i == 1) {
            strcpy(line->str, "|7    |");
        } 
        
        //Middle of card
        else if (i == 2 || i == 5 ||  i == 8) {
            strcpy(line->str, "| ");
            strcat(line->str, card);
            strcat(line->str, " ");
            strcat(line->str, card);
            strcat(line->str, " |");
        } 
        else if (i == 3) {
            strcpy(line->str, "|  ");
            strcat(line->str, card);
            strcat(line->str, "  |");
        } 
        
        //Bottom of card
        else if (i == 9) {
            strcpy(line->str, "|    7|");
        } 
        else if (i == 10) {
            strcpy(line->str, " ‾‾‾‾‾ ");
        } 

        //Body of card
        else {
            strcpy(line->str, "|     |");
        }

        while (curr->next) {
            curr = curr->next;
        }
        curr->next = line;
    }
}


void Card::cardEight(const char card[], int row) {
    Node* curr;
    Node* line;
    
    // Loop through each line 
    for (int i = 0; i < 11; i++) {
        curr = heads[row + i];
        line = new Node;
        line->next = nullptr;

        //Top of card
        if (i == 0) {
            strcpy(line->str, " _____ ");
        } 
        else if (i == 1) {
            strcpy(line->str, "|8    |");
        } 
        
        //Middle of card
        else if (i == 2 || i == 5 ||  i == 8) {
            strcpy(line->str, "| ");
            strcat(line->str, card);
            strcat(line->str, " ");
            strcat(line->str, card);
            strcat(line->str, " |");
        } 
        else if (i == 3 || i == 7) {
            strcpy(line->str, "|  ");
            strcat(line->str, card);
            strcat(line->str, "  |");
        } 
        
        
        //Bottom of card
        else if (i == 9) {
            strcpy(line->str, "|    8|");
        } 
        else if (i == 10) {
            strcpy(line->str, " ‾‾‾‾‾ ");
        } 

        //Body of card
        else {
            strcpy(line->str, "|     |");
        }

        while (curr->next) {
            curr = curr->next;
        }
        curr->next = line;
    }
}


void Card::cardNine(const char card[], int row) {
    Node* curr;
    Node* line;
    
    // Loop through each line 
    for (int i = 0; i < 11; i++) {
        curr = heads[row + i];
        line = new Node;
        line->next = nullptr;

        //Top of card
        if (i == 0) {
            strcpy(line->str, " _____ ");
        } 
        else if (i == 1) {
            strcpy(line->str, "|9    |");
        } 
        
        //Middle of card
        else if (i == 2 || i == 4 || i == 6 || i == 8) {
            strcpy(line->str, "| ");
            strcat(line->str, card);
            strcat(line->str, " ");
            strcat(line->str, card);
            strcat(line->str, " |");
        } 
        else if (i == 3) {
            strcpy(line->str, "|  ");
            strcat(line->str, card);
            strcat(line->str, "  |");
        } 
        
        
        //Bottom of card
        else if (i == 9) {
            strcpy(line->str, "|    9|");
        } 
        else if (i == 10) {
            strcpy(line->str, " ‾‾‾‾‾ ");
        } 

        //Body of card
        else {
            strcpy(line->str, "|     |");
        }

        while (curr->next) {
            curr = curr->next;
        }
        curr->next = line;
    }
}


void Card::cardTen(const char card[], int row) {
    Node* curr;
    Node* line;
    
    // Loop through each line 
    for (int i = 0; i < 11; i++) {
        curr = heads[row + i];
        line = new Node;
        line->next = nullptr;

        //Top of card
        if (i == 0) {
            strcpy(line->str, " _____ ");
        } 
        else if (i == 1) {
            strcpy(line->str, "|10   |");
        } 
        
        //Middle of card
        else if (i == 2 || i == 4 || i == 6 || i == 8) {
            strcpy(line->str, "| ");
            strcat(line->str, card);
            strcat(line->str, " ");
            strcat(line->str, card);
            strcat(line->str, " |");
        } 
        else if (i == 3 || i == 7) {
            strcpy(line->str, "|  ");
            strcat(line->str, card);
            strcat(line->str, "  |");
        } 
        
        //Bottom of card
        else if (i == 9) {
            strcpy(line->str, "|   10|");
        } 
        else if (i == 10) {
            strcpy(line->str, " ‾‾‾‾‾ ");
        } 

        //Body of card
        else {
            strcpy(line->str, "|     |");
        }

        while (curr->next) {
            curr = curr->next;
        }
        curr->next = line;
    }
}


void Card::cardJack(const char card[], int row) {
    Node* curr;
    Node* line;
    
    // Loop through each line 
    for (int i = 0; i < 11; i++) {
        curr = heads[row + i];
        line = new Node;
        line->next = nullptr;

        //Top of card
        if (i == 0) {
            strcpy(line->str, " _____ ");
        } 
        else if (i == 1) {
            strcpy(line->str, "|J    |");
        } 
        
        //Middle of card
        else if (i == 5) {
            strcpy(line->str, "|  ");
            strcat(line->str, card);
            strcat(line->str, "  |");
        } 
        
        //Bottom of card
        else if (i == 9) {
            strcpy(line->str, "|    J|");
        } 
        else if (i == 10) {
            strcpy(line->str, " ‾‾‾‾‾ ");
        } 

        //Body of card
        else {
            strcpy(line->str, "|     |");
        }

        while (curr->next) {
            curr = curr->next;
        }
        curr->next = line;
    }
}


void Card::cardQueen(const char card[], int row) {
    Node* curr;
    Node* line;
    
    // Loop through each line 
    for (int i = 0; i < 11; i++) {
        curr = heads[row + i];
        line = new Node;
        line->next = nullptr;

        //Top of card
        if (i == 0) {
            strcpy(line->str, " _____ ");
        } 
        else if (i == 1) {
            strcpy(line->str, "|Q    |");
        } 
        
        //Middle of card
        else if (i == 5) {
            strcpy(line->str, "|  ");
            strcat(line->str, card);
            strcat(line->str, "  |");
        } 
        
        //Bottom of card
        else if (i == 9) {
            strcpy(line->str, "|    Q|");
        } 
        else if (i == 10) {
            strcpy(line->str, " ‾‾‾‾‾ ");
        } 

        //Body of card
        else {
            strcpy(line->str, "|     |");
        }

        while (curr->next) {
            curr = curr->next;
        }
        curr->next = line;
    }
}


void Card::cardKing(const char card[], int row) {
    Node* curr;
    Node* line;
    
    // Loop through each line 
    for (int i = 0; i < 11; i++) {
        curr = heads[row + i];
        line = new Node;
        line->next = nullptr;

        //Top of card
        if (i == 0) {
            strcpy(line->str, " _____ ");
        } 
        else if (i == 1) {
            strcpy(line->str, "|K    |");
        } 
        
        //Middle of card
        else if (i ==5) {
            strcpy(line->str, "|  ");
            strcat(line->str, card);
            strcat(line->str, "  |");
        } 
        
        //Bottom of card
        else if (i == 9) {
            strcpy(line->str, "|    K|");
        } 
        else if (i == 10) {
            strcpy(line->str, " ‾‾‾‾‾ ");
        } 

        //Body of card
        else {
            strcpy(line->str, "|     |");
        }

        while (curr->next) {
            curr = curr->next;
        }
        curr->next = line;
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////
                            //End Of Card Functions //
////////////////////////////////////////////////////////////////////////////////////////////////





/*
////////////////////////////////////////////////////////////////////////////////////////////////
                            //Print Deck Part 1 Test//
////////////////////////////////////////////////////////////////////////////////////////////////
void Card::printDeckPart1Test(){
    //If there are heads from the old output delete them
    if(!heads.empty()){
        deleteHeads();
    }

    //Allocate all lines for printing
    for(int size = 2; size < 6; size++){
        createHeads(size, size);//
    
    }

    //Put all lines in correct list
    int rowLength = 2;//For the row length
    for(int i = 0; i < heads.size(); i+=11){

            //If deck is out of cards
            if(nextCard < 1)
                break;
            for(int j = rowLength; j > 0;j--){

                //If deck is out of cards
                if(nextCard < 0)
                    break;
                getCardFunc(deck[nextCard-1], i);//get correct card function
                nextCard--;//Iterate through cards

            }
            ++rowLength;//update row length
        }

    //Print cards
    Node* curr;
    for(int i = 0; i < heads.size(); i++){
        curr = heads[i];
        while(curr){
            cout << curr->str;
            curr = curr->next;
        }
    }


    
}

*/
