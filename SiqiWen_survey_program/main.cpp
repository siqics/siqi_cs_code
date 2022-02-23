#include "survey_list.h"
using namespace std;


//Siqi Wen CS163
//This file is a test program which will contain implementation of
//member functions from the class survey. A menu interface is included
//in this file, the user can choose from the menu what they want to
//do about the application list and the usage survey list.


const int SIZE = 100;

int main()
{
    int a_task = 0;      //Create an int variable for user's choice from menu.
    app_info an_app;     //Create an object of app_info class.
    survey the_list;     //Create an object of survey class.
    use_info add_use;    //Create an object of use_info struct.

    char ar_name[SIZE];  //Create three arrays for the user's inputs
    char ar_type[SIZE];  //for app name and type and description.
    char ar_desc[SIZE];

    char an_app_name[SIZE]; //To store user's input for an app name
    char a_reason[SIZE];    //To store user's input for a reason of use
    int user_frequency = 0; //To store user's input for frequency of use
    char input_type[SIZE];  //To store user's input for an app type

   
    do
    { 
	menu(a_task);   //Call menu function.
        
	if(a_task == 1) //Add a new application.
        {
	    do
	    {
                cout << "\n\n\nPlease enter the app name: ";
                cin.get(ar_name, SIZE, '\n');
                cin.ignore(100, '\n');
                cout << "\n\nPlease enter the app type: ";
                cin.get(ar_type, SIZE, '\n');
                cin.ignore(100, '\n');
                cout << "\n\nPlease enter a description for this app: ";
                cin.get(ar_desc, SIZE, '\n');
                cin.ignore(100, '\n');

                if(an_app.add_one(ar_name, ar_type, ar_desc))
		    if(!the_list.add_new(an_app))
	                cout << "\n\n\n\nYou were not able to add the app: " 
	                     << ar_name << " into the list!\n\n";

	        cout << "\n\n\n\nDo you want to add another new App?\n";
	    }while(again());
        }
	else if(a_task == 2)  //Display all applications.
	{
            if(!the_list.display_all_apps())
                cout << "\n\n\nThere is nothing in the list!\n\n";
	}
	else if(a_task == 3)  //Insert survey information for a given App.
	{ 
	    cout << "\n\n\nNow, you're being surveyed!\n\n\n"
		 << "Please enter:\n1. an app name\n2. "
		 << "what you mostly use this app for\n3. "
	         << "the frequency of use - how many times do"
		 << " you open the app per week?\nUse number "
		 << "1-20, 1 is lowest and 20 is highest.\n\n";
	    do
	    {
		cout << "\nThe App name: ";
                cin.get(an_app_name, SIZE, '\n');
		cin.ignore(100, '\n');
		cout << "\nWhat do you mostly use this App for: ";
		cin.get(a_reason, SIZE, '\n');
		cin.ignore(100, '\n');
		cout << "\nWhat's the frequency of use (1-20): ";
		do
		{
		    cin >> user_frequency;
		    cin.ignore(100, '\n');
		    if(user_frequency < 1 || user_frequency > 20)
		        cout << "\n\n\nHas to be a number from 1-20: ";
		}while(user_frequency < 1 || user_frequency > 20);

		add_use.frequency = user_frequency;
		add_use.reason = new char[strlen(a_reason) + 1];
		strcpy(add_use.reason, a_reason);

		if(!the_list.insert(an_app_name, add_use))
		    cout << "\n\n\nSorry, we couldn't add this survey "
			 << "information!\n\n";

		if(add_use.reason)
		    delete []add_use.reason;

		cout << "\n\n\nWanna add another person's survey info?\n";
            }while(again());	
	}
	else if(a_task == 4)  //Display usage for apps of a particular category.
	{
	    cout << "\n\n\nPlease enter a type name so that we can show you the"
		 << "\nusage information of all apps that belong to this type: ";
	    cin.get(input_type, SIZE, '\n');
	    cin.ignore(100, '\n');
	    if(!the_list.display_usage(input_type))
	        cout << "\n\n\nSorry, we were not able to display the info of usage!\n\n";
	}		
	else if(a_task == 5)  //Remove an application by entering an app name.
	{
	    cout << "\n\n\nTo remove an app, you need to enter an app name: ";
	    cin.get(an_app_name, SIZE, '\n');
	    cin.ignore(100, '\n');
	    if(!the_list.remove_an_app(an_app_name))
	        cout << "\n\n\nSorry! we were not able to remove the app called: "
		     << an_app_name << "\n\n\n";
	    else
		cout << "\n\n\n" << an_app_name << " was removed! :)\n\n\n";
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
    cout << "\n\nWelcome to our App Survey program!\nIn this program,"
	 << " you're able to add new applications;\nmodify the applications"
	 << " in the list;\nremove an application by the name;\nadd in information"
	 << " of the usage from the people getting surveyed, and so on.\n\n";
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
	 << "Enter 1 - Add a new application.\n\n"
	 << "Enter 2 - Display all applications.\n\n"
	 << "Enter 3 - Insert survey information for a given App.\n\n"
	 << "Enter 4 - Display usage for application of a particular category.\n\n"
	 << "Enter 5 - Remove an application by entering an app name.\n\n"
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

