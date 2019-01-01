#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

struct Node{
    int data;
    Node *next;
};

struct Stack {
    Node *head;
    void create();
    void close();
    void push(int);
    int pop();
    bool isempty();
    int size();
    int top();
    void Print();
};

void Stack::create(){
    head = NULL;
}

void Stack::close(){
    Node *temp;
    while(head){
        temp = head;
        head = head->next;
        delete temp;
    }
}

void Stack::push(int newdata){
    Node *newnode = new Node;
    newnode->data = newdata;
    newnode->next = head;
    head = newnode;
}

int Stack::pop(){
    Node *tmp;
    int tempdata;
    tmp = head;
    head = head->next;
    tempdata = tmp->data;
    delete tmp;
    return tempdata;
}

bool Stack::isempty(){
    if(head == NULL)
        return 1;
    return 0;
}

int Stack::size(){ 
    Node* temp;
    temp = head;
    int counter = 0;
    while(temp){
        counter++;
        temp = temp->next;
    }
    return counter;
}

int Stack::top(){
    return head->data;
}


int main(int argc, char* argv[]){
    int tableDeckCount, playerDeckCount, tempcard, bin=0;
    Stack player1, player2, deck;
    
    //initializing the stacks
    deck.create();
    player1.create();
    player2.create();
    

    ifstream game;
    game.open(argv[argc-1]);

    game >> tableDeckCount;
    game >> playerDeckCount;

    //taking the inputs for the deck stack
    for(int i=0; i<tableDeckCount; i++){
        game >> tempcard;
        deck.push(tempcard);
    }
    //taking the inputs for the player1
    for(int i=0; i<playerDeckCount; i++){
        game >> tempcard;
        player1.push(tempcard);
    }
    //taking the inputs for the player2
    for(int i=0; i<playerDeckCount; i++){
        game >> tempcard;
        player2.push(tempcard);
    }
    
    int turn = 1;
    while(!player1.isempty() && !player2.isempty() && !deck.isempty()){
        int TempDeckCard = deck.pop();
        int TempPlayerCard;
        //first players turn
        if(turn&1){
            if(TempDeckCard < 0){
                //player1 gives card to player2
                for(int i=0; i<abs(TempDeckCard) && !player1.isempty(); i++){
                    if(player1.top() > player2.top()){
                        TempPlayerCard = player1.pop();
                        player2.push(TempPlayerCard);
                    } else {
                        TempPlayerCard = player1.pop();
                        bin++;
                    }
                }
            } else {
                //player2 gives card to player1
                for(int i=0; i<abs(TempDeckCard) && !player2.isempty(); i++){
                    if(player2.top() > player1.top()){
                        TempPlayerCard = player2.pop();
                        player1.push(TempPlayerCard);
                    } else {
                        TempPlayerCard = player2.pop();
                        bin++;
                    }
                }
            }
        //second players turn
        } else {
            if(TempDeckCard < 0){
                //player2 gives card to player1
                for(int i=0; i<abs(TempDeckCard) && !player1.isempty(); i++){
                    if(player2.top() > player1.top()){
                        TempPlayerCard = player2.pop();
                        player1.push(TempPlayerCard);
                    } else {
                        TempPlayerCard = player2.pop();
                        bin++;
                    }
                }
            } else {
                //player1 gives card to player2
                for(int i=0; i<abs(TempDeckCard) && !player2.isempty(); i++){
                    if(player1.top() > player2.top()){
                        TempPlayerCard = player1.pop();
                        player2.push(TempPlayerCard);
                    } else {
                        TempPlayerCard = player1.pop();
                        bin++;
                    }
                }
            }
        }
        turn++;
    }
    cout << bin;
    deck.close();
    player1.close();
    player2.close();
    return 0;
}