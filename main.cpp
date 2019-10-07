//
//  main.cpp
//  Blackjack
//
//  Created by Xinyao Miao on 2019/9/29.
//  Copyright © 2019 xinyaomiao. All rights reserved.
//

#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

void shuffle(int cards[]);
void printCard(int id);
void printHand(vector<int> hand);

int getCardValue(int id);
int getTotalScore(vector<int> hand);

const int CARDSNUM = 52;//52 cards

const string type[13] =
{"2","3","4","5","6","7",
    "8","9","10","J","Q","K","A"};

char suit[4] = {'H','S','D','C'};
//H for Heart, S for Spade, D for Diamond, and C for Club

const int value[13] = {2,3,4,5,6,7,8,9,10,10,10,10,11};

//permute the deck of cards
//shuffle it usingthe Fisher-Yates / Durstenfeld shuffle algorithm
void shuffle(int cards[])
{
    //initialize the card values
    for(int i=0; i<CARDSNUM; i++){
        cards[i] = i;
    }
    //shuffle cards
    for(int i=CARDSNUM-1; i>=0; i--){
        
        int j = rand()%(i+1);
        int curr = cards[j];
        cards[j] = cards[i];
        cards[i] = curr;
        
    }
    
}

// prints the card in the "type-suit" format
void printCard(int id)
{
    //H cards
    if(id>=0 && id<=12){
        cout<< type[id] <<"-"<<suit[0];
    }
    //S cards
    else if(id>=13&&id<=25){
        id -= 13;
        cout<< type[id] <<"-"<<suit[1];
        
    }//D cards
    else if(id>=26&&id<=38){
        id -= 26;
        cout<< type[id] <<"-"<<suit[2];
        
    }
    //C cards
    else if(id>=39&&id<=51){
        id -= 39;
        cout<< type[id] <<"-"<<suit[3];
    }
    
}

//returns the numeric value of the card.
int getCardValue(int id)
{
    int result = 0;
    
    //H cards
    if(id>=0 && id<=12){
        result = value[id];
    }
    //S cards
    else if(id>=13&&id<=25){
        id -= 13;
        result = value[id];
        
    }//D cards
    else if(id>=26&&id<=38){
        id -= 26;
        result = value[id];
        
    }
    //C cards
    else if(id>=39&&id<=51){
        id -= 39;
        result = value[id];
    }
    
    return result;
    
    
}

// print out each card in the hand
void printHand(vector<int> hand)
{
    for(int i=0; i<(int)hand.size(); i++){
        int id = hand[i];
        printCard(id);
        cout<<" ";//seprated by a apace
    }
    cout<<endl;//print a new line at the end
    
}

//return the total score of the provided hand.
int getTotalScore(vector<int> hand)
{
    int sum = 0;
    bool AceAdded = false;
    
    for(int i=0; i<(int)hand.size(); i++){
        int id = hand[i];
        if(id%13==12){
            AceAdded = true;
        }
        sum+= getCardValue(id);
        
    }
    //if sum is greater than 21, count ACE as 1
    if(sum>21 && AceAdded){
        sum = 0;
        for(int i=0; i<(int)hand.size(); i++){
            int id = hand[i];
            if(hand[i]%13==12){
                sum += 1;
            }
            else{
                sum+=getCardValue(id);
            }
        }
    }
    return sum;
    
}

//main program logic
int main(int argc, char* argv[])
{
    if(argc < 2){
        cout << "Error: You need to provide a seed number!." << endl;
        return 1;
    }
    int seed = atoi(argv[1]);//take a seed value from the command line
    srand(seed);
    
    int cards[52];//all cards
    vector<int> dhand;//dealer's hand cards
    vector<int> phand;//player's hand cards
    
    int currCard = 0; //how many cards have been taken
    
    bool play = true;//wether to keep playing
    
    cout<<"Welcome! Let's play blackjack together!"<<endl;;
    
    while(play){
        
        //start the game
        shuffle(cards);
        
        if(currCard==51){
            currCard = 0;//if all cards were taken, start over
        }
        
        //starting hand
        phand.push_back(cards[currCard]);
        currCard++;
        dhand.push_back(cards[currCard]);
        currCard++;
        phand.push_back(cards[currCard]);
        currCard++;
        dhand.push_back(cards[currCard]);
        currCard++;
        
        //print
        cout<<"My Hand Cards: "<<"? ";
        printCard(dhand[1]);
        cout<<endl;
        cout<<"Your Hand Cards: ";
        printHand(phand);
        
        
        char choice;//user input
        
        if(getTotalScore(phand)==21){
            cout<<"You Win! Cngratulations!"<<endl;
            cout<<"You score is "<<getTotalScore(phand);
            cout<<endl;
        }
        if(getTotalScore(dhand)==21){
            cout<<"I Win!"<<endl;
            cout<<"My score is "<<getTotalScore(dhand);
            cout<<endl;
        }
        
        while(getTotalScore(phand)<21){
            cout<< "Please enter 'h' to hit and 's' to stay: ";
            cin>>choice;
            
            if(choice == 'h'){
                
                phand.push_back(cards[currCard]-1);
                currCard ++;
                cout<< "Your Hand Card: ";
                printHand(phand);
                
                if(getTotalScore(phand)==21){
                    cout<<"You Win! Cngratulations!"<<endl;
                    cout<<"You score is "<<getTotalScore(phand);
                    cout<<endl;
                    break;
                }
                
                //if the player's total score exceeds 21 after choosing hit
                if(getTotalScore(phand)>21){
                    cout<<"You Bust! "<<endl;
                    cout<<"You score is "<<getTotalScore(phand);
                    cout<<endl;
                    break;
                    
                }
                
                //dealer hit if total score is less than 17
                if(getTotalScore(dhand)<17){
                    dhand.push_back(cards[currCard]);
                    currCard++;
                }
                if(getTotalScore(dhand)==21){
                    cout<<"I Win!"<<endl;
                    cout<<"My score is "<<getTotalScore(dhand);
                    cout<<endl;
                    break;
                }
                //if the dealer's total score is greater than 21
                if(getTotalScore(dhand)>21){
                    cout<<"Oh I Bust! My current score is "<<getTotalScore(dhand)<<endl;
                    cout<<"You Win! Cngratulations!"<<endl;
                    cout<<"You score is "<<getTotalScore(phand);
                    cout<<endl;
                    break;
                }
                
            }
            else if(choice == 's'){
                
                int currCard = (int)phand.size() + (int)dhand.size();
                
                //dealer hit if total score is less than 17
                while(getTotalScore(dhand)<17){
                    dhand.push_back(cards[currCard]);
                    currCard++;
                }
                if(getTotalScore(dhand)==21){
                    cout<<"I Win!"<<endl;
                    cout<<"My score is "<<getTotalScore(dhand);
                    cout<<endl;
                    break;
                }
                //if the dealer's total score is greater than 21
                if(getTotalScore(dhand)>21){
                    cout<<"Oh I Bust! My cards cards are: ";
                    printHand(dhand);
                    cout<<"You Win! Cngratulations!"<<endl;
                    cout<<"Your score is "<<getTotalScore(phand);
                    cout<<endl;
                    break;
                }
                else{
                    if(getTotalScore(phand)>getTotalScore(dhand)){
                        cout << "You Win : )"<<endl;
                        cout <<"Your score is " <<getTotalScore(phand)<<endl;
                        cout <<"My score is "<<getTotalScore(dhand) << endl;
                        
                    }
                    
                    else if(getTotalScore(phand)<getTotalScore(dhand)){
                        cout << "You Lose : ( " <<endl;
                        cout <<"Your score is " <<getTotalScore(phand)<<endl;
                        cout <<"My score is "<<getTotalScore(dhand) << endl;
                        
                    }
                    
                    else{
                        cout << "Tie " <<endl;
                        cout <<"Our score is " <<getTotalScore(phand)<<endl;
                        
                    }
                    break;
                }
                
            }
            else{
                cout<< "Invalid input. Exit the game."<<endl;
                break;
            }
        }
        //clear hand cards
        phand.clear();
        dhand.clear();
        
        //ask if the player wants to start a new round
        cout<< "Do you want to start again? y/n: ";
        cin>> choice;
        if(choice == 'y'){
            play = true;
        }
        else{
            cout<<"Thank you for playing blackjack with me! Bye~"<<endl;
            return 0;
        }
        
    }
    return 0;
}



