#include "queue_stack.h"
using namespace std;


//Siqi Wen CS163
//This file is a test program which will contain implementations of
//member functions from the class queue and stack. A menu interface
//is included in this file, the user can choose from the menu what
//they want to do.


const int SIZE = 200;



int main()
{
    int menu_task = 0;
    queue q_object;
    queue store_pop;
    stack stack_ob;
    int input_step = 0;
    char input_desc[SIZE];
    char input_note[SIZE];


    welcome();

    do
    {
        menu(menu_task);

	if(menu_task == 1)
	{
	    do
	    {
	        cout << "\n\nEnter the step number: ";
	        cin >> input_step;
	        cin.ignore(100, '\n');
	        cout << "\n\nEnter the description for this step: ";
	        cin.get(input_desc, SIZE, '\n');
	        cin.ignore(100, '\n');
	        cout << "\n\nEnter the note for this step: ";
	        cin.get(input_note, SIZE, '\n');
	        cin.ignore(100, '\n');

	        if(q_object.enqueue(input_step, input_desc, input_note))
		    cout << "\n\nWe added a new step!!\n\n\n";
		else
		    cout << "\n\nOops, we couldn't add the new step...\n\n";
	        
		cout << "\n\nDo you want to add one more step?\n";
	    }while(again());
	}
	else if(menu_task == 2)
	{
	    if(q_object.dequeue())
	        cout << "\n\nWe deleted the oldest step!\n\n\n";
	    else
	        cout << "\n\nOops, we couldn't delete the oldest step...\n\n\n";
        }
        else if(menu_task == 3)
	{
	    if(!q_object.display_allsteps())
	        cout << "\n\n\nThere is no steps recorded!!\n\n";
	}
	else if(menu_task == 4)
	{
	    if(!stack_ob.push(q_object))
		cout << "\n\n\nOops, we couldn't push the activity onto the stack...\n\n";
            else
		cout << "\n\n\nCongrats! We pushed an activity onto the stack successfully!\n\n";
	    if(stack_ob.reset_q_ob(q_object))
		cout << "\n\nAnd we reset the queue object, now you can create another trial"
	             << " with it.\n\n";
	}
	else if(menu_task == 5)
	{
	    if(!stack_ob.display_allqueue())
	        cout << "\n\n\nThere is NO trials yet!\n\n";
	}
	else if(menu_task == 6)
	{
	    if(!stack_ob.display_top())
	        cout << "\n\n\nOops, we couldn't display the data at the Top of stack...\n\n";
	}
	else if(menu_task == 7)
	{
	    if(!stack_ob.pop(store_pop))
		cout << "\n\n\nOops, we couldn't pop the most recent data from top...\n\n";
	    else
	    {
		cout << "\n\n\nCongrats! We just popped the most recent data from top!\n\n";
		cout << "\n\nAnd the data that we popped is:\n\n";
		if(!store_pop.display_allsteps())
		    cout << "\n\n\nSorry, cannot display the data just got popped!...\n\n";
	    }
	}

	if(menu_task != 8)
	    cout << "\n\n\n\nWanna check menu again?";
    }while(menu_task != 8 && again());

    cout << "\n\n\n\n\nThank you for using our program!\n\n"
	 << "Have a wonderful day!!\n\n\n\n\n\n";

    return 0;
}


//Output the welcome message and explain what the program can do.
void welcome()
{
    cout << "\n\nWelcome to our Note-taking Program!\n\nIn this program,"
	 << " you'll be able to take notes for doing your favorite activity."
	 << "\nYou can enter a step number, what to do for each step and what"
	 << " went wrong\nthis time/what needs to be improved next time.\nYou"
	 << " can add new steps or delete the oldest step;\nWhen you're done "
	 << "writing the steps, you can add the entire activity to a list.\n"
	 << "You'll also be able to display all the trials you did for one "
	 << "activity which includes all the steps.\n\n\nHope you enjoy our"
	 << " program!\n\n\n";
}


//This function asks the user if they want to do it again by
//prompting the user for an input, true or false will be returned.
bool again()
{
     char answer;                              //Create a character variable
     do
     {
         cout << "\n\n\nPlease enter Y/y or N/n: ";
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
         << "Enter 1 - Add a new step for this trial.\n\n"
         << "Enter 2 - Delete the oldest step for this trial.\n\n"
         << "Enter 3 - Display all steps for this trial.\n\n"
         << "Enter 4 - Add the entire activity into the Trial List (Push).\n\n"
         << "Enter 5 - Display all trials from old to new.\n"
	 << "(display every queue from bottom to top on stack)\n\n"
	 << "Enter 6 - Display just the data at the Top of stack.\n\n"
	 << "Enter 7 - Pop the most recent Queue from Top (removing it).\n\n"
         << "Enter 8 - Exit.\n\n\n\n\n"
         << "Now, please enter a number (1-8): ";
    do
    {
        cin >> task;               //Read in the user's answer.
        cin.ignore(100, '\n');
        if(task < 1 || task > 8)
            cout << "\n\nYou entered a wrong number!\n\nPlease enter "
                 << "a number between 1 and 8(inclusive): ";
    }while(task < 1 || task > 8);  //Repeat until user enters a proper number.
}
