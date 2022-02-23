#include<iostream>
#include<cstring>
using namespace std;

//Siqi Wen CS162
//This file contains a structure definition that includes six data members
//(five of them are pointers); a class interface that includes some member
//functions and one data member which is a pointer; prototypes of functions
//that will be used and called in main.


//Create a struct with six members.
struct node
{
    char * name;      //A pointer to a dynamically allocated array of characters for the name.
    char * breed;     //A pointer to a dynamically allocated array of characters for the breed.
    char * reason;    //A pointer to a dynamically allocated array of characters for the reason.
    int rating;       //An integer represents the number of likes.
    char * nickname;  //A pointer to a dynamically allocated array of characters for the nickname.
    node * next;      //Create a pointer.
};


//Create a class interface with member functions and a data member.
class animal
{
    public:
        animal();    //Constructor - initialize the data members.
        ~animal();   //Destructor - deallocate the dynamic memory used by the class.
        void get_info(node * & temp);         //Get information from user.
        void insert();                        //Insert the new node to the list.
        void add();                           //Add new animals to the list.
        void display_one(node * current);     //Display one item in the list.
        void display_all();                   //Display all items in the list.
	void display_breeds();                //Display all breed types in the list.
	bool match_breed(char * choicebreed); //Check if there's a matching breed.
	void display_by_breed();              //Display animals of certain breed.
	void display_names();                 //Display all animal names.
	bool match_name(char * choicename);   //Check if there's a matching name.
	void remove_by_name();                //Remove an animal by its name.
    private:
	node * head;                          //A pointer points to a node.
};


//Prototypes
void welcome();            //Output the welcome message.
bool again();              //Ask if the user wants to do again. 
void menu(int & task);     //Show the user the menu. 

