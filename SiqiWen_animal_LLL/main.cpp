#include "animal.h"

//Siqi Wen CS162
//This file contains the implementation of main. Some functions
//that were created in other files will be called in main and
//complete their missions, such as adding new animals into the 
//linear linked list; displaying all animals in the list;
//displaying specific animals based on the breed and removing
//specific animals by the name.

int main()
{
    animal pet;     //Create an animal object.
    int a_task = 0; //Create an int variable.

    welcome();      //Display welcome messages.

    do
    {
        menu(a_task);   //Show the menu and get user's input.
        if(a_task == 1)
            pet.add();          //To add new animals.
        else if(a_task == 2)
            pet.display_all();  //To display all animals in the list.
        else if(a_task == 3)
            pet.display_by_breed(); //Display animals by breed.
        else if(a_task == 4)
            pet.remove_by_name();   //Remove an animal by name.

        if(a_task != 5)
            cout << "\n\n\nDo you want to check the menu again?\n"
                 << "(Enter Y/y if you want to continue, enter N/n"
                 << " if you want to exit.)";
    }while(a_task != 5 && again()); //Repeat until user wants to exit.

    cout << "\n\n\n\nThank you for using our program!"
	 << "\n\n\nHave a wonderful day!\n\n\n\n";  //Display ending messages.

    return 0;
}


//Output the welcome message and explain what the program can do.
void welcome()
{
    cout << "\n\n\n\n\nWelcome to   My Favorite Animals   program!"
	 << "\n\n\nThis program allows you to:\n1. Add new animals"
	 << "\n2. Display the contents of all animals in order by "
	 << "favorites\n3. Display just the animals of a particular "
	 << "breed\n4. Remove an animal by the name\n\n\nHope you "
	 << "enjoy our program!\n\n\n\n";
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
	 << "Enter 1 - Add new animals.\n\n"
	 << "Enter 2 - Display the contents of all animals.\n\n"
	 << "Enter 3 - Display just the animals of a particular breed.\n\n"
	 << "Enter 4 - Remove a particular animal by the name.\n\n"
	 << "Enter 5 - Exit.\n\n\n\n\n"
	 << "Now, please enter a number (1-5): ";
    do
    {
        cin >> task;               //Read in the user's answer.
	cin.ignore(100, '\n');
	if(task < 1 || task > 5)
	    cout << "\n\nYou entered a wrong number!\n\nPlease enter "
		 << "a number between 1 and 5(inclusive): ";
    }while(task < 1 || task > 5);  //Repeat until user enters a proper number.
}
