#include <iostream>
#include <fstream>
using namespace std;

//Stack's node struct
struct Node{
    int data;
    Node *next;
};
//Stack and its applications
struct stackAnt {
    Node *head_stack;
    void create_stack();
    void close_stack();
    void push_stack(int);
    int pop_stack();
    void printStack_stack();
};
//creating the Stack
void stackAnt::create_stack(){
    head_stack = NULL;
}
//Deleting the stack
void stackAnt::close_stack(){
    Node *temp;
    while(head_stack){
        temp = head_stack;
        head_stack = head_stack->next;
        delete temp;
    }
}
//Pushing and element into the top of the stack
void stackAnt::push_stack(int newdata){
    Node *newnode = new Node;
    newnode->data = newdata;
    newnode->next = head_stack;
    head_stack = newnode;
}
//Popping the top element from the stack
int stackAnt::pop_stack(){
    Node *tmp;
    int tempdata;
    tmp = head_stack;
    head_stack = head_stack->next;
    tempdata = tmp->data;
    delete tmp;
    return tempdata;
}


struct queueAnt{
    Node *head_queue;
    Node *tail;
    void create_queue();
    void close_queue();
    void push_queue(int);
    int pop_queue();
    bool isempty_queue();
    void printQueue();
};

void queueAnt::create_queue(){
    head_queue = NULL;
    tail = NULL;
}


void queueAnt::close_queue(){
    Node *temp1;
    while(head_queue){
        temp1 = head_queue;
        head_queue = head_queue->next;
        delete temp1;
    }
}

bool queueAnt::isempty_queue(){
    if(head_queue == NULL) return true;
    return false;
}

void queueAnt::push_queue(int newData){
    Node *temp2 = new Node;
    temp2->data = newData;
    temp2->next = NULL;
    //if queue is empty
    if(head_queue == NULL){
       tail = temp2;
       head_queue = tail;
    } else {
        tail->next = temp2;
        tail = temp2;
    }
}

int queueAnt::pop_queue(){
    int tempdata;
    Node *temp3;
    temp3 = head_queue;
    head_queue = head_queue->next;
    tempdata = temp3->data;
    delete temp3;
    return tempdata;
}

void queueAnt::printQueue(){
    Node *temp4 = head_queue;
    while(temp4){
        cout << temp4->data << " ";
        temp4 = temp4->next;
    }
}

struct Ants {
    queueAnt ants ;
    queueAnt holeDepths ;
    stackAnt hole ;
    void ReadFile (const char *);
    void ShowContents ( bool );
    void CrossRoad ();
};

void Ants::ReadFile(const char* filename){
    ifstream file;
    file.open(filename);
    int antNumber, depth;
    file >> antNumber;
    //assigning ants to ants queue
    for(int i=1; i<=antNumber; i++){
        ants.push_queue(i);
    }
    //reading the depth of holes from file and push to queue
    while(!file.eof()){
        file >> depth; 
        if( file.eof() ) break;
        holeDepths.push_queue(depth);
    }
}

void Ants::ShowContents(bool number){
    if(!number){
        holeDepths.printQueue();
    } else {
        ants.printQueue();
    }
}

void Ants::CrossRoad(){
    int tmp;
    while(!holeDepths.isempty_queue()){
        tmp = holeDepths.pop_queue();
        for(int i=0; i<tmp; i++){
            hole.push_stack(ants.pop_queue());
        }
        for(int i=0; i<tmp; i++){
            ants.push_queue(hole.pop_stack());
        }
    }
}

int main(int argc, char* argv[]){
    Ants antt;
    
    antt.ants.create_queue();
    antt.hole.create_stack();
    antt.holeDepths.create_queue();
    
    antt.ReadFile(argv[1]);
    cout << "The initial Ant sequence is: ";
    antt.ShowContents(1);
    cout << endl;
    cout << "The depth of holes are: ";
    antt.ShowContents(0);
    cout << endl;
    antt.CrossRoad();
    cout << "The final Ant sequence is: ";
    antt.ShowContents(1);

    antt.ants.close_queue();
    antt.hole.close_stack();
    antt.holeDepths.close_queue();
    return 0;
}