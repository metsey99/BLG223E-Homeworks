/*
    @Authour
    Student Name: Metehan Seyran
    Student ID: 150170903
    Date: 22/12/2018
*/
#include <iostream>
#include <fstream>
using namespace std;

struct Node{
    int data;
    Node *next;
};

struct stack {
    Node *head_stack = NULL;
    void push_stack(int);
    int pop_stack();
    void print_stack();
};

void stack::push_stack(int newdata){
    Node *newnode = new Node;
    newnode->data = newdata;
    newnode->next = head_stack;
    head_stack = newnode;
}

int stack::pop_stack(){
    Node *tmp;
    int tempdata;
    tmp = head_stack;
    head_stack = head_stack->next;
    tempdata = tmp->data;
    delete tmp;
    return tempdata;
}

void stack::print_stack(){
    Node *ptr;
    ptr = head_stack;
    while(ptr != NULL){
        cout << ptr->data << " ";
        ptr = ptr->next;
    }
}

struct node{
    int data;
    node *left, *right;
};

struct tree_operations{
    stack path;
    node *root = NULL;
    node* build(node *root_ptr, int size, int array[], int index);
    int sum = 0;
    int flag = 1;
    void preorder(node* root_ptr, int target);
};

node* tree_operations::build(node *rootptr, int size, int array[], int index){
    if(index <= size){
        node *temp = new node;
        temp->data = array[index];
        temp->right = NULL;
        temp->left = NULL;
        rootptr = temp;
        rootptr->left = build(rootptr->left, size, array, 2*index);
        rootptr->right = build(rootptr->right, size, array, (2*index)+1);
    }
    return rootptr;
}

void tree_operations::preorder(node* root, int target){
    if(root == NULL || !flag) 
        return;
    sum += root->data;
    path.push_stack(root->data);
    preorder(root->left, target);
    preorder(root->right, target);
    if(sum == target){
        flag = 0;
        cout << "Path Found: ";
        stack new_stack;
        while(path.head_stack != NULL){
            new_stack.push_stack(path.pop_stack());
        }
        new_stack.print_stack();
        while(new_stack.head_stack != NULL){
            path.push_stack(new_stack.pop_stack());
        }
        cout << endl;
        sum--; 
        return;
    } else {
        path.pop_stack();        
        sum -= root->data;
    }
}

int main(int argc, char* argv[]){
    int arr[500], target, arr_i;
    ifstream file;
    file.open(argv[argc-1]);
    arr[0] = 0;
    int size=1;
    while(!file.eof()){
        file >> arr_i;
        if( file.eof() ) break;
        arr[size] = arr_i;
        size++;
    }
    //real size == size-2
    //size-1 == target
    target = arr[size-1];

    int main_flag = 1;
    tree_operations tree;
   
    tree.root = tree.build(tree.root, size-2, arr, 1);
    if(target == tree.root->data)
        cout << "Path Found: " << tree.root->data << endl;
    else {
        tree.sum = tree.root->data;
        tree.path.push_stack(tree.root->data);
        tree.preorder(tree.root->left, target);
        if(tree.flag == 1) cout << "No Path Found" << endl;
        tree.flag = 1;
        tree.sum = tree.root->data;
        tree.path.head_stack = NULL;
        tree.path.push_stack(tree.root->data);
        tree.preorder(tree.root->right, target);
        if(tree.flag == 1) cout << "No Path Found" << endl;
    }
    return 0;
}