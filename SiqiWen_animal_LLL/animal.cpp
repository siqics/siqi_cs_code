#include "animal.h"

//Siqi Wen CS162
//This file contains implementations of those member functions in class
//animal. These functions have access to the data member in this class
//(which is a pointer), and each function will be called in either some
//of these functions or main.


//This is a constructor, it initializes the data member in the class.
animal::animal()
{
    head = NULL;
}


//This is a destructor, it releases all memories dynamically allocated
//with the pointers in the class and in the node structure.And it would
//reset the data member to its zero equivalent value.
animal::~animal()
{
    if(head)      //Only release memory when the pointer is not NULL.
    {
        node * current = head;  //Create a temporary pointer.
        while(current)          //Repeat when there is item left.
	{
            delete []current->name;     //Release memory name points to.
            delete []current->breed;    //Release memory breed points to.
            delete []current->reason;   //Release memory reason points to.
	    delete []current->nickname; //Release memory nickname points to.
	    
	    current = current->next;  //Move current to point to the next item.

	    delete head;         //Release memory head is pointing to.
	    head = current;      //Move head to point to what current points to.
	}
    }
}


//This function takes a pointer as an argument, this pointer will be passed by 
//reference, because we need to modify and update the information of this temp 
//pointer.
void animal::get_info(node * & temp)
{
    temp = new node;      //Set temp to point to a new node.
    char array[100];      //Create a temporary array of characters.

    cout << "\n\nEnter the animal's name(e.g. dog; cat; tiger): ";
    cin.get(array, 100, '\n');              //Store user's input in the temporary array.
    cin.ignore(100, '\n');
    temp->name = new char[strlen(array)+1]; //Create a dynamically allocated array of right size.
    strcpy(temp->name, array);              //Copy the content to the new array of characters.

    cout << "\n\nEnter the animal's breed: ";
    cin.get(array, 100, '\n');               //Store user's input in the temporary array.
    cin.ignore(100, '\n');
    temp->breed = new char[strlen(array)+1]; //Create a dynamically allocated array of right size.
    strcpy(temp->breed, array);              //Copy the content to the new array of characters. 

    cout << "\n\nEnter the reason why you like them "
	 << "(What do you like about them)?: ";
    cin.get(array, 100, '\n');                //Store user's input in the temporary array.
    cin.ignore(100, '\n');
    temp->reason = new char[strlen(array)+1]; //Create a dynamically allocated array of right size. 
    strcpy(temp->reason, array);              //Copy the content to the new array of characters.  

    cout << "\n\nEnter a number representing how much "
	 << "you like them (1 is lowest, 10 is highest): ";
    do
    {
        cin >> temp->rating;                  //Read in user's input.
	cin.ignore(100, '\n');
	if(temp->rating < 1 || temp->rating > 10)
	    cout << "\n\nYou entered a wrong number!\nIt has"
		 << " to be between 1 to 10(inclusive).\n1 is"
		 << " lowest, 10 is highest.\nPlease re-enter: ";
    }while(temp->rating < 1 || temp->rating > 10); //Repeat until a proper number was entered.

    cout << "\n\nIf you could have this animal as a pet, what"
         << " nickname would you give to it?\nEnter a nickname: ";
    cin.get(array, 100, '\n');                  //Store user's input in the temporary array.
    cin.ignore(100, '\n');
    temp->nickname = new char[strlen(array)+1]; //Create a dynamically allocated array of right size. 
    strcpy(temp->nickname, array);              //Copy the content to the new array of characters.
}


//This function would insert the new item into the right spot in the list
//based on its rating value.
void animal::insert()
{
    node * temp;      //Create a pointer variable pointing to a node.	
    get_info(temp);   //Call the function and pass the pointer as an argument.

    if(!head)         //If head is NULL (empty list).
    {
        head = temp;  //Let head point to the new node.
	head->next = NULL;
    }
    else if(head->rating < temp->rating) //Insert the new node in the beginning of the list.
    {
        temp->next = head;
	head = temp;
    }
    else                //Insert the new node in the middle (or at the end) of the list.
    {
        node * prev;    //Create two temporary pointer variables.
	node * current;

	prev = head;          //Set prev point to the first node.
	current = head->next; //Set current point to the second node.

	//Repeat until either there is no more item or the right spot is found.
	while(current && temp->rating < current->rating)
	{
	    prev = current;   //Traverse through the list.
	    current = current->next;
	}
	temp->next = current; //Insert the node between prev node and current node.
	prev->next = temp;
    }
}


//This function will allow user to keep adding new animals to the list
//until they want to stop.
void animal::add()
{
    cout << "\n\nDo you want to add a new animal?\n";
    while(again())  //Repeat until user wants to stop.
    {
        insert();   //Call this function to add and insert a new item. 
        cout << "\n\nWant to add another animal?\n";
    }
}


//This function takes a pointer variable as an argument, and it will display
//contents for each item.
void animal::display_one(node * current)
{
    cout << "\n\nName of the animal: " 
	 << current->name << endl
	 << "Breed: " 
	 << current->breed << endl
	 << "Reason why I like them: "
	 << current->reason << endl
	 << "Number of likes: "
	 << current->rating << endl
	 << "If they were my pet, I would"
	 << " call them: " 
	 << current->nickname
	 << "\n\n\n";
}


//This function displays all contents of all items in the list.
void animal::display_all()
{
    if(!head)  //If head is NULL.
        cout << "\n\n\nThe list is empty!\n\nYou have"
             << " to add some animals first!\n\n\n";
    else
    {
        node * current = head; //A temporary pointer.

	cout << "\n\n\nHere are all the animals in the"
	     << " list: \n\n";
        while(current)  //Traverse through the list and display every item.
        {
            display_one(current);
            current = current->next;
        }
    }
}


//This function displays all breed types in the list.
void animal::display_breeds()
{
    node * current = head;  //A temporary pointer variable.

    cout << "\n\n\n\nHere are all the breed types"
         << " in the list:\n\n";
    while(current)          //Repeat as long as current is not NULL.
    {
        cout << current->breed << endl; //Display the breed.
	current = current->next;        //Traverse.
    }
}


//This function takes an array pointer as an argument,
//and it would traverse through the list and check if
//there's a matching breed, then it would return true
//or false.
bool animal::match_breed(char * choicebreed)
{
    bool match = false;      //A bool variable.

    node * current = head;   //A temporary pointer used to traverse.
    while(current && !match) //Repeat when there's item left and no match found.
    {
	if(strcmp(choicebreed, current->breed)==0) //If a match is found.
	    match = true;                          //Assign match with true.
        current = current->next;                   //Traverse.
    }
    return match;            //Return the value of the bool variable.
}


//This function would analyze if there is a match with user's choice
//of breed. If there is, it would display all animals information of
//that breed.
void animal::display_by_breed()
{
    if(!head)  //If the list is empty.
        cout << "\n\n\nThere is no animal in the list yet!"
             << "\n\nPlease add some animals first!\n\n\n";
    else       //If the list is not empty.
    {
        char array[100];       //A temporary array.
	char * choicebreed;
	bool match_breedtype;  //A bool variable.
	node * current = head; //A temporary pointer.

	display_breeds();      //To display all breed types in the list.

        cout << "\n\n\nNow, you can enter a specific breed.\nThen"
	     << " the program would display all animals that"
	     << " match with this breed.\n\n\nWARNING: You have"
	     << " to enter something that is the same as one of "
	     << "the breeds showed above.\nIf not, there would be"
	     << " no match.\n\n\nPlease enter a breed: ";
        cin.get(array, 100, '\n');               //Read in user's input.
        cin.ignore(100, '\n');
        choicebreed = new char[strlen(array)+1]; //Set the right size.
        strcpy(choicebreed, array);              //Copy the array of characters.

	match_breedtype = match_breed(choicebreed); //Store and use the returned value.
	if(match_breedtype)                         //If true was returned.
	{
	    cout << "\n\n\nHere are all animals matching "
		 << "with breed: " << choicebreed << "\n\n\n";

	    while(current)                          //Repeat until current is NULL.
	    {
	        if(strcmp(choicebreed, current->breed)==0)
		    display_one(current);           //Display if it's a match.
		current = current->next;            //Traverse.
	    }
	}
	else
	    cout << "\n\n\n\nSorry, there is no match with "
		 << "breed type: " << choicebreed << "\n\n\n";

	if(choicebreed)  //Make sure the pointer is not NULL.
	{
	    delete []choicebreed; //Release the memory.
	    choicebreed = NULL;   //Set the pointer to NULL.
	}
    }
}


//This function would traverse through the list and display
//all animal names in the list.
void animal::display_names()
{
    node * current = head;  //A temporary pointer variable.

    cout << "\n\n\n\nHere are all the animal names that"
         << " you entered earlier in the list:\n\n";
    while(current)          //Repeat as long as current is not NULL.
    {
        cout << current->name << endl;  //Display the name.
        current = current->next;        //Traverse.
    }
}


//This function takes an array pointer as an argument,
//and it would traverse through the list and check if
//there's a matching name, then it would return true
//or false.
bool animal::match_name(char * choicename)
{
    bool match = false;      //A bool variable.

    node * current = head;   //A temporary pointer used to traverse.
    while(current && !match) //Repeat when there's item left and no match found.
    {
        if(strcmp(choicename, current->name)==0)   //If a match is found.
            match = true;                          //Assign match with true.
        current = current->next;                   //Traverse.
    }
    return match;            //Return the value of the bool variable.
}


//This function will prompt user for an input for an animal name
//if the list is not empty. Then it would analyze if there's a
//matching name in the list, if there is, the corresponding animal
//would be removed.
void animal::remove_by_name()
{
    if(!head)                  //If the list is empty.
        cout << "\n\n\n\nThe list is empty!\nYou cannot"
	     << " remove anything!\n\nPlease add some "
             << "animals first!\n\n\n\n";
    else                       //If the list is not empty.
    {
        char array[100];       //A temporary array.
        char * choicename;     //A pointer to an array of characters.
        bool matching_name;    //A bool variable.

        display_names();       //To display all animal names in the list.

	cout << "\n\n\n\nNow, you can remove an item from the list"
	     << " by entering an animal name.\n\nWARNING: The animal"
	     << " name you enter has to be the same as one of the "
	     << "names showed above,\nor nothing will be removed from"
	     << " the list.\n\n\n\nPlease enter an animal name here: ";
        cin.get(array, 100, '\n');              //Read in user's input.
	cin.ignore(100, '\n');
	choicename = new char[strlen(array)+1]; //Set the right size.
	strcpy(choicename, array);

	matching_name = match_name(choicename); //Assign with the returned value.
	if(matching_name)                       //If true was returned.
	{
	    if(strcmp(head->name, choicename)==0)
	    {                                //If the first node is the match.
	        node * temp;                 //Release the memory of the first node,
		temp = head->next;           //then change head to point to the 
		delete []head->name;         //second node.
		delete []head->breed;
		delete []head->reason;
		delete []head->nickname;
		delete head;
		head = temp;
	    }
	    else                             //When the first node is not the match.
	    {
	        node * prev = head;          //Points to the first node.
		node * current = head->next; //Points to the second node.

		while(strcmp(current->name, choicename)) //Repeat when it's no match.
		{
		    prev = current;                      //Traverse.
		    current = current->next;
		}
	                                      //When match is found.
		prev->next = current->next;   //Go around the matching node and connect.
		delete []current->name;       //Delete all the memories in the node.
		delete []current->breed;
		delete []current->reason;
		delete []current->nickname;
		delete current;
            }
	    cout << "\n\n\n\nCongrats! The animal: "
		 << choicename << "\nwas removed from"
		 << " the list!\n\n\n\n";
	}
	else                                  //If false was returned.
	    cout << "\n\n\n\nSorry! The animal name: "
		 << choicename << " doesn't exit in the"
		 << " list.\n\nNo item was removed!\n\n\n\n";

	if(choicename)       //Make sure the pointer is not NULL before releasing memory.
	{
	    delete []choicename;  //Release memory of the array of characters.
	    choicename = NULL;    //Set the pointer to NULL.
	}
    }
}
