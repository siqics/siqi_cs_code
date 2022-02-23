#include "table.h"
using namespace std;



//Siqi Wen CS163
//This file contains a test program for the Animal Shelter program,
//this test program will complete the missions that the user wants
//by calling different functions we implemented in animal class and
//table class based on user's choice from the menu.


const int SIZE = 100;


int main()
{
    int a_task = 0;      //Create an int variable for user's choice from menu.

    char file[] = "animal.txt";

    animal * add = NULL;
    table list;

    animal * found = NULL;

    char in_type[SIZE];
    char in_breed[SIZE];
    char in_name[SIZE];
    char in_re[SIZE];
    int in_age = 0;
    char in_desc[SIZE];


    if(load(file, in_type, in_breed, in_name, in_re, in_age, in_desc, add, list))
	cout << "\n\n\nWe already loaded the file!!\n\n\n";
    else
	cout << "\n\n\nOops..We couldn't load the file...\n\n\n";

    do
    {
        menu(a_task);      //Call menu function.


	if(a_task == 1)    //Add a new animal.
        {
	    do
	    {
                add = new animal;

	        cout << "\n\nEnter the animal type: ";
		cin.get(in_type, SIZE, '\n');
		cin.ignore(100, '\n');
		cout << "\n\nEnter the animal breed: ";
		cin.get(in_breed, SIZE, '\n');
		cin.ignore(100, '\n');
		cout << "\n\nEnter the animal name: ";
		cin.get(in_name, SIZE, '\n');
		cin.ignore(100, '\n');
		cout << "\n\nEnter the requirement for the animal: ";
		cin.get(in_re, SIZE, '\n');
		cin.ignore(100, '\n');
		cout << "\n\nEnter the animal's age: ";
		cin >> in_age;
		cin.ignore(100, '\n');
		cout << "\n\nEnter the description for this animal: ";
		cin.get(in_desc, SIZE, '\n');

		if(add->create_animal(in_type, in_breed, in_name, in_re, in_age, in_desc))
		{
		    if(list.insert_both(add))
		        cout << "\n\nCongrats! New animal was added into hashtable and BST!\n\n";
	            else
		        cout << "\n\nSorry, we couldn't add data into hashtable and BST...\n\n";
		}
		else
		    cout << "\n\n\n\n\nOops...we couldn't add a new animal...\n\n\n";

		add = NULL;

                cout << "\n\n\n\nDo you want to add another new animal?\n";
            }while(again());
        }

	else if(a_task == 2)
	{
            cout << "\n\n\n\nYou're trying to find matching animals."
		 << "\nYou need to enter a type and a breed.\n\n\n";
            cout << "Enter an animal type: ";
	    cin.get(in_type, SIZE, '\n');
	    cin.ignore(100, '\n');
	    cout << "\nEnter an animal breed: ";
	    cin.get(in_breed, SIZE, '\n');
	    cin.ignore(100, '\n');

	    if(!list.display_matches_hash(in_type, in_breed))
	        cout << "\n\n\n\nOops, no match found...\n\n\n";
	}

	else if(a_task == 3)
	{
	    cout << "\n\n\n\nTo find a particular animal based on their breed and name,"
		 << "\nyou need to enter an animal breed and name.\n\n"
		 << "\n\n\nThe information will be stored in ADT but not displayed!\n\n\n"
		 << "\n\nIt will be displayed in the test program tho!\n\n\n"
		 << "\nEnter a breed: ";
	    cin.get(in_breed, SIZE, '\n');
	    cin.ignore(100, '\n');
	    cout << "\nEnter a name: ";
	    cin.get(in_name, SIZE, '\n');
	    cin.ignore(100, '\n');

	    if(list.retrieve_BST(in_breed, in_name, found))
	    {
	        cout << "\n\n\n\nWe found a match!! (breed and name)\n\n"
		     << "The animal is:\n\n";
		found->display_one_animal();
	    }
	    else
		cout << "\n\n\nSorry, there is no animal matching with:\n"
		     << "breed: " << in_breed
		     << "\nname: " << in_name << "\n\n";
	}

	else if(a_task == 4)
        {
	    if(!list.display_all())
	        cout << "\n\n\nThere is NO animal in the shelter...\n\n\n";
	}

	else if(a_task == 5)
	{
            cout << "\n\n\nTo remove an animal, you need to enter the type,"
		 << " breed and name.\n\n"
                 << "\n\nEnter the animal type: ";
            cin.get(in_type, SIZE, '\n');
            cin.ignore(100, '\n');
            cout << "\n\nEnter the animal breed: ";
            cin.get(in_breed, SIZE, '\n');
            cin.ignore(100, '\n');
            cout << "\n\nEnter the animal name: ";
            cin.get(in_name, SIZE, '\n');
            cin.ignore(100, '\n');

	    if(list.remove_one(in_type, in_breed, in_name))
	        cout << "\n\n\n\nCongrats! We deleted that item!\n\n\n";
	    else
		cout << "\n\n\nOops, we couldn't delete " << in_name << "...\n\n\n";
	}

	if(a_task != 6)
	    cout << "\n\n\nCheck the menu again??\n\n";
    }while(a_task != 6 && again());  //Call again function. Continue until user wants to stop.

    cout << "\n\n\n\nThank you for using our program!"
	 << "\n\nHave a wonderful day!\n\n\n\n\n";

    return 0;
}



//Output the welcome message and explain what the program can do.
void welcome()
{
    cout << "\n\nWelcome to our Animal Shelter program!\nIn this program,"
	 << "you'll be able to insert a new animal into the system;\ndisplay"
	 << " all matches of a particular type and breed;\nfind a particular"
	 << " animal based on their breed and name;\ndisplay all animals in"
	 << " sorted order by their breed and name;\nremove an animal that's"
	 << " no longer available for fostering.\n\n\n\n"
	 << "When you run the program, the file will be loaded automatically!\n\n\n";
}


//This function asks the user if they want to do it again by
//prompting the user for an input, true or false will be returned.
bool again()
{
     char answer;                              //Create a character variable
     do
     {
         cout << "\n\n\n\nPlease enter Y/y or N/n: ";
         cin >> answer;                       //Read in the user's answer.
         cin.ignore(100, '\n');
         answer = toupper(answer);            //Convert the character to an uppercase letter
         if (answer != 'Y' && answer != 'N')
             cout << "\n\nYou entered a wrong letter. Please enter Y/y or N/n.";
     }while(answer != 'Y' && answer != 'N'); //continue until the uppercase letter is Y or N
     if (answer == 'Y')                      //This function will return true if answer is Y
         return true;
     return false;                           //Return false if answer is N
}


//This function takes an integer as an argument and it will show the user the menu, and
//prompts the user to enter a choice in terms of which task the user wants to do.
void menu(int & task)
{
    cout << "\n\n\n\nHere is the menu:\n\n"
	 << "Enter 1 - Add a new animal.\n\n"
	 << "Enter 2 - Display all matches of a particular type and breed.\n\n"
	 << "Enter 3 - Find a particular animal based on their breed and name.\n\n"
	 << "Enter 4 - Display all animals in sorted order by their breed and name.\n\n"
	 << "Enter 5 - Remove an animal that's no longer available for fostering.\n\n"
	 << "Enter 6 - Exit.\n\n\n\n\n"
	 << "Now, please enter a number (1-6): ";
    do
    {
        cin >> task;               //Read in the user's answer.
	cin.ignore(100, '\n');
	if(task < 1 || task > 6)
	    cout << "\n\nYou entered a wrong number!\n\nPlease enter "
		 << "a number between 1 and 6(inclusive): ";
    }while(task < 1 || task > 6);  //Repeat until user enters a proper number.
}



//This function takes an array of characters, five char pointers, an integer,
//a pointer to an animal and a table object as arguments. It would load info
//of animals from a file and insert the animals into both hash table and BST.
//1 will be returned for success, 0 will be returned for failure.
int load(char filename[], char * t, char * b, char * n, char * r, int a, char * d, animal * add, table & list)
{
    ifstream file_in;        //This variable will be used to read from a file.

    file_in.open(filename);  //Open the file and load info stored in the external data file

    if(file_in)              //file_in would return true if we connected successfully
    {
	//Try to read first so that we can test if it's the end of file later.
        file_in.get(t, SIZE, '|');
	file_in.ignore(100, '|');

	//This while loop only executes when it's not the end of file
	while(!file_in.eof())
	{
	    file_in.get(b, SIZE, '|');
            file_in.ignore(100, '|');

	    file_in.get(n, SIZE, '|');
            file_in.ignore(100, '|');

	    file_in.get(r, SIZE, '|');
            file_in.ignore(100, '|');

	    file_in >> a;
	    file_in.ignore(100, '|');

	    file_in.get(d, SIZE, '\n');
            file_in.ignore(100, '\n');

	    //Create a new animal with the pointer, copy all info into
	    //this new animal, and insert this animal into both hash
	    //table and BST.
	    add = new animal;
	    if(add->create_animal(t, b, n, r, a, d))
	    {
	        if(list.insert_both(add))
		    cout << "\n\n\nWe inserted  " << n << "  into hash table and BST from"
			 << " file successfully!\n\n\n";
		else
		    cout << "\n\n\nWe couldn't insert  " << n << "  from file...\n\n\n";
	    }
	    else
		cout << "\n\n\nWe couldn't read this animal from file...\n\n\n";

	    add = NULL;

            file_in.get(t, SIZE, '|');   //Try to read first.
            file_in.ignore(100, '|');
	}
	file_in.close();                 //Close the file when done.
	return 1;
    }
    return 0;
}




