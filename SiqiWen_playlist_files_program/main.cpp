#include "music.h"

//Siqi Wen CS162
//This code contains the implementation of main, some functions
//that were created in other codes will be called in main and 
//complete their missions, such as read in songs, display all
//songs, display specific songs based on the user's input and 
//edit the information about a particular song based on the 
//user's input.

int main()
{
    int a_task = 0;         //Create a variable for user's choice of task.
    char type_choice[TYPE]; //Create an array variable for user's choice of type.
    char edit_title[TITLE]; //Create an array variable for user's choice of title.
    playlist library;       //Create a class variable.

    welcome();           //Call the welcome function to output welcome messages.
    library.get_size();  //Call the get_size function to prompt for the size.
 
    do
    { 
        menu(a_task);     //Call the menu function to show the menu.

	//Call the corresponding function based on user's input.
        if(a_task == 1)
            library.read_all();        //Call the function to read all songs.
        else if(a_task == 2) 
            library.display_all();     //Call the function to display all songs.
        else if(a_task == 3)
            library.display_specific(type_choice);  //To display specific songs.
        else if(a_task == 4)
	    library.edit(edit_title);  //To allow user to edit some information.

	if(a_task != 5)
	    cout << "\n\n\nDo you want to check the menu again?\n"
                 << "(Enter Y/y if you want to continue, enter N/n"
	         << " if you want to exit.)";
    }while(a_task != 5 && again());

    library.exit();  //Call the exit function to release memory and output ending messages.
         
    return 0;
}


//Output the welcome message and explain what the program can do.
void welcome()
{
    cout << "\n\n\nWelcome to our Music Playlist program!\n\n\n"
	 << "This program allows you to:\nadd new songs(whenever"
	 << " you want unless the playlist is full or you re-run "
	 << "the program);\ndisplay all songs;\ndisplay only songs"
	 << " that are of a particular genre or type;\nedit some "
	 << "information about a particular song.\n\n\n\n"
	 << "You will see the menu after you enter a size you want"
	 << " for the playlist :)\n\n\n\n\n";
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
    cout << "\n\n\n\nHere is the menu: \n"   //Output the menu options.
	 << "Enter 1 - Add new songs.\n"
	 << "Enter 2 - Display all songs.\n"
	 << "Enter 3 - Display only songs that match a particular type.\n"
	 << "Enter 4 - Edit the information about a particular song.\n"
	 << "Enter 5 - Exit.\n\n\n"
	 << "Now, please enter a number (1-5): ";
    do
    {
        cin >> task;              //Read in the user's answer.
	cin.ignore(100, '\n');
	if(task < 1 || task > 5)
	    cout << "\n\nYou entered a wrong number!\n\nPlease enter a "
		 << "number between 1 and 5(inclusive): ";
    }while(task < 1 || task > 5); //Repeat until user enters a proper number.
}

//This function will take two arrays of characters and an integer as arguments.
//It will check which part of the information the user would like to edit.
void which_to_edit(char array[], int & part_edit, char n_info[])
{
    cout << "\n\nNow, Please enter a number for the part of "  //Output the options
	 << "information you'd like to\nedit for the song: "   //of parts the user
	 << array << "\n\n\n1. Artist;\n2. Type;\n3. When you" //can edit.
	 << " listen to this song;\n4. Link.\n\n\n"
	 << "Enter a number (1-4): ";
    do
    {
        cin >> part_edit;                    //Read in the user's answer.
	cin.ignore(100, '\n');
	if(part_edit < 1 || part_edit > 4)
	    cout << "\n\nYou entered a wrong number!\n\nPlease enter a "
		 << "number between 1 and 4(inclusive): ";
    }while(part_edit < 1 || part_edit > 4);  //Repeat until user enters a proper number.

    cout << "\n\n\n\nPlease enter the new information to replace the"
	 << " old\ninformation in the playlist for the song: " 
	 << array << ": ";                  //Prompt user for the new information.
    cin.get(n_info, LINK, '\n');            //Read in the new information.
    cin.ignore(100, '\n');
}
