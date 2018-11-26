
/*@Author
 * 
 * Student Name: Metehan Seyran
 * Student ID: 150170903
 * Date 08/11/2018
 * 
 * Note: The space character can be searched by typing " " or ' ' 
 * Note2: The \n characters are ignored and did not counter as Space character
 * Note3: Compiled and tested in Ubuntu Linux enviroment
 * */


#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#define CAP 500
using namespace std;


//node to create and keep data of sub linked list nodes
struct occur_node {
	char character;
	occur_node *next;
	int occurence;
};

//node to create the main linked list
struct vocab_node {
	char character;
	vocab_node *next;
	occur_node *list;
};

//struct that keep all the functions and the head of linked list
 struct vocab_list {
	vocab_node *head;
	void create();
	void print();
	void add_char(char );
	void add_occurence(char , char );
	int get_occurence(char );
	int get_union_occurence (char , char );
};

struct language_model {
	vocab_list *vocabularylist;
	void readData (const char *);
	double calculateProbability (char, char);
};

//linked list gets created 
void vocab_list::create(){
	head = NULL;
}

void vocab_list::add_char(char a){
	vocab_node *ptr, *temp, *tail;
	occur_node *list;
	//initialize a temp vocab_node for new node
	temp = new vocab_node;
	temp->list = new occur_node;
	temp->character = tolower(a);
	temp->next = NULL;
	temp->list = NULL;
	if(head == NULL){           
		head = temp;
	} else {
		ptr = head;
		//Addition for letter characters
		if(temp->character <= 122 && temp->character >= 97){
			//add to the beginning
			if(ptr->character > temp->character){
				temp->next = ptr;
				head = temp;
				return;
			} else {
				//search if it is in middle
				while(ptr && (ptr->character < temp->character) && (ptr->character >= 97)){
					tail = ptr;
					ptr = ptr->next;
				}
			}
			//check if its equal to the a
			if(ptr == NULL){
				tail->next = temp;
			} else if(ptr && ((ptr->character > temp->character) || (ptr->character < 97))){
				tail->next = temp;
				temp->next = ptr;
			} else if(ptr->character == temp->character){
				return;
			}
		} else {
			//Addition for non letter characters
			while(ptr && (ptr->character > temp->character)){
				tail = ptr;
				ptr = ptr->next;
			}
			if(ptr == NULL){
				tail->next = temp;
			} else if(ptr && ptr->character < temp->character){
				tail->next = temp;
				temp->next = ptr;
			} else if(ptr->character == temp->character){
				return;
			}
		}
		
	}
}

void vocab_list::add_occurence(char a, char b){
	vocab_node *ptr;
	occur_node *temp2, *ptr2, *tail2;
	char first = tolower(a);
	char second = tolower(b);
	//initialize ptr for search in main linked list
	ptr = head;
	//initialize temp occur_node to store new occurence
	temp2 = new occur_node;
	temp2->character = second;
	temp2->next = NULL;
	temp2->occurence = 1;
	//search for the first letter in main linked list
	while(first != ptr->character){
		ptr = ptr->next;
	}
	ptr2 = ptr->list;
	//if found assign ptr2 to the ptr->list and add the temp2
	if(!ptr->list){
		ptr->list = temp2;
		ptr2 = ptr->list;
	} else {
		//searching for the second character
		while(ptr2 && (ptr2->character != second)){
			tail2 = ptr2;
			ptr2 = ptr2->next;
		}
		//if there is no such character
		if(!ptr2){
			tail2->next = temp2;
		//if there exist such kind of character
		} else if(ptr2->character == second){
			ptr2->occurence += 1;
		}
	}
}

void vocab_list::print(){
	vocab_node *ptr;
	occur_node *ptr2;
	ptr = head;
	//traversing the main linked list
    while(ptr != NULL){
		if(ptr->character == 32){
			cout << "<SP>" << ":" << endl;
		} else {
			cout << ptr->character << ":" << endl;
		}
		ptr2 = ptr->list;
		//traversing the sub linked list
		while(ptr2 != NULL){
			if(ptr2->character == 32){
				cout << "\t<" << "<SP>" << "," << ptr2->occurence << ">" <<endl;
				ptr2 = ptr2->next;
			} else {
				cout << "\t<" << ptr2->character << "," << ptr2->occurence << ">" <<endl;
				ptr2 = ptr2->next;
			}
		}
		ptr = ptr->next;
	}
}

int vocab_list::get_occurence(char a){
	vocab_node *ptr;
	occur_node *ptr2;
	int sum = 0;
	ptr = head;
	//searching for the character in main linked list
	while(ptr != NULL){
		if(ptr->character == a){
			ptr2 = ptr->list;
			//adding all occurences to the sum variable
			while(ptr2 != NULL){
				sum += ptr2->occurence;
				ptr2 = ptr2->next;
			}
			//returns sum
			return sum;
		} else {
			ptr = ptr->next;
		}
	}
}


int vocab_list::get_union_occurence(char a, char b){
	vocab_node *ptr;
	occur_node *ptr2;
	//assigning head to the pointer
	ptr = head;
	//searching for the character a
	while(ptr->character != a){
		ptr = ptr->next;
	}
	ptr2 = ptr->list;
	//searching for the character b
	while(ptr2->character != b){
		ptr2 = ptr2->next;
	}
	return ptr2->occurence;
}

void language_model::readData(const char *argument){
	vocabularylist->create();
	ifstream text;
	text.open(argument);
	string line;
	int i = 0;
	while(!text.eof()){
		getline(text, line); //Got the first line to the string 'text'
		if( text.eof() ) break;
		//adding the letters to the main linked list
		for(int i=0; i<line.size()-1; i++){
			vocabularylist->add_char(line[i]);
		}
		//adding the letters' occurences
		for(int i=1; i<line.size()-1; i++){
			vocabularylist->add_occurence(line[i-1], line[i]);
		}
	}
}

double language_model::calculateProbability(char a, char b){
	double n, m, k;
	n = vocabularylist->get_union_occurence(a, b);
	m = vocabularylist->get_occurence(a);
	k = n/m;
	return k;
}

int main(int argc, char* argv[]){
	//reading data
	language_model new_lang_model;
	new_lang_model.readData(argv[1]);
	//checking whether user wanted to get a probability of a certain to characters
	if(!argv[2]){
		new_lang_model.vocabularylist->print();
	} else {
		//checking the space character
		if(argv[2]=="\" \"" || argv[2] == "\' \'"){
			cout << new_lang_model.calculateProbability(32, *argv[3]) << endl;
		} else if(argv[3] == "\" \"" || argv[3] == "\' \'"){
			cout << new_lang_model.calculateProbability(*argv[2], 32) << endl;
		} else {
			cout << new_lang_model.calculateProbability(*argv[2], *argv[3]) << endl;
		}
	}
	
	return 0;
}
