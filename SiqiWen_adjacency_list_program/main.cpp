#include "adjacency.h"
using namespace std;




//Siqi Wen CS163
//This file is the client program. In this program we will
//call the member functions from table class based on the
//user's choice of task. We are able to insert an vertex;
//insert an edge; display all choices at a given vertex,
//those choices are vertices that are adjacent to the
//specific vertex.




int main()
{
    int a_task = 0;      //Create an int variable for user's choice from menu.

    table trails;
    int array_full = 0;

    char name[100];
    char one_name[100];
    char adjacent_name[100];
    char choice_vertex[100];

    welcome();

    do
    {
        menu(a_task);      //Call menu function.

	if(a_task == 1)    //Add a new animal.
	{
	    do
	    {
	        cout << "\n\nEnter a trailhead or intersection name: ";
		cin.get(name, 100, '\n');
		cin.ignore(100, '\n');

		if(!trails.insert_vertex(name, array_full))
		    cout << "\n\n\nOops...couldn't insert this vertex...\n\n";
     
		if(!array_full)
		    cout << "\n\nWanna insert another vertex?\n\n";
		else
		    cout << "\n\nThe array is full, cannot insert more vertices!\n\n\n";
	    }while(!array_full && again());
	}

	else if(a_task == 2)
	{
	    do
	    {
	        cout << "\n\nEnter two vertices that are connected:\n"
		     << "\n\nFirst vertex: ";
	        cin.get(one_name, 100, '\n');
         	cin.ignore(100, '\n');

	        cout << "\n\nSecond vertex: ";
	        cin.get(adjacent_name, 100, '\n');
	        cin.ignore(100, '\n');

		if(trails.insert_edge(one_name, adjacent_name))
		{
		    if(trails.insert_edge(adjacent_name, one_name))
		        cout << "\n\n\nCongrats!!\n\n";
		}
		else
		    cout << "\n\n\nOops, couldn't insert the edge...\n\n\n";


		cout << "\n\n\nWanna insert another edge?\n\n";

	    }while(again());
	}

	else if(a_task == 3)
	{
	    do
	    {
	        cout << "\n\n\nTo find choices for an intersection, you have to "
	             << "enter the intersection's name.\n\n"
		     << "\n\n\nEnter the intersection's name: ";
		cin.get(choice_vertex, 100, '\n');
		cin.ignore(100, '\n');

		if(!trails.display_adjacent(choice_vertex))
		    cout << "\n\n\nOops, we couldn't find another choices adjacent"
			 << " to " << choice_vertex << "...\n\n\n";

		cout << "\n\n\nWanna find choices for another intersection?\n\n";
	    }while(again());
	}

	if(a_task != 4)
	    cout << "\n\n\nCheck the menu again??\n\n";
    }while(a_task != 4 && again());

    cout << "\n\n\n\nThank you for using our program!\n\n"
	 << "Have a wonderful day!\n\n\n\n\n";

    return 0;
}



//Output the welcome message and explain what the program can do.
void welcome()
{
    cout << "\n\nWelcome to our Finding Trails Program.\n\n\nIn this"
	 << " program, you will be able to insert all trailheads and"
	 << " intersections as vertices;\ninsert edges which represent"
	 << " that there is a connection between two vertices;\ndisplay"
	 << " all choices at a given intersection.\n\n\n\n";
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
	 << "Enter 1 - Add a vertex.\n\n"
	 << "Enter 2 - Add an edge.\n\n"
	 << "Enter 3 - Display all choices at a given intersection.\n\n"
	 << "Enter 4 - Exit.\n\n\n\n\n"
	 << "Now, please enter a number (1-4): ";
    do
    {
        cin >> task;               //Read in the user's answer.
	cin.ignore(100, '\n');
	if(task < 1 || task > 4)
	    cout << "\n\nYou entered a wrong number!\n\nPlease enter "
		 << "a number between 1 and 4(inclusive): ";
    }while(task < 1 || task > 4);  //Repeat until user enters a proper number.
}


