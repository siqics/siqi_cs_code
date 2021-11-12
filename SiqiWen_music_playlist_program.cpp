#include <iostream>
#include <cctype>
#include <cstring>
#include <fstream>
using namespace std;

//Siqi Wen CS162
//This program is a music playlist program, which will allow the user to add in
//new songs and it will display all songs. Moreover, it saves the current list
//of songs to an external file and also loads new songs from a file previously
//stored. Then the program would prompt the user to enter in a situation so that
//the program would display all songs that match with that particular choice.

//constants
const int ARTIST = 31;
const int TITLE = 41;
const int TYPE = 21;
const int WHEN = 26;
const int LINK = 81;
const int SONGS = 10;

//Create a structure with five members.
struct music
{
    char artist[ARTIST]; //Create an array of characters for the song's artist.
    char title[TITLE];   //Create an array of characters for the song's title.
    char type[TYPE];     //Create an array of characters for the song's type.
    char when[WHEN];     //Create an array of characters for a situation.
    char link[LINK];     //Create an array of characters for the song's link.
};

//Prototypes
void welcome();   //Output the welcome message.
bool again();     //Ask if the user wants to do again. 
void menu(int & task); //Show the user the menu. 
void read_a_song(music & a_song);    //Read in contents about a song.
void display_a_song(music & a_song); //Display contents about a song.
void read_songs(music library[], int & num);  //Read in contents about songs.
void display_songs(music library[], int num); //Display contents about songs.
int load(music library[]);           //Read information from a file and return an integer.
void save(music library[], int num_to_save);  //Save the songs read in to an external data file.
void display_whens(music library[], int num); //Display all situations: when songs are listened.
void ask_message();                           //Display a message to the user.
bool is_match(music library[], char choice[], int num);      //Check if there is a match with user's choice.
void display_specific_songs(music library[], char choice[], int num); //Display songs based on user's choice.


int main()
{
    music library[SONGS];  //Create an array of structures of size SONGS.
    int num_of_songs = 0;  //Create a variable for the number of songs.
    int a_task = 0;        //Create a variable for user's choice of task.
    char user_choice[WHEN]; //An array to store user's input.

    welcome();            //Call the welcome function to display messages.

    do
    {
        menu(a_task);                  //Call the menu function to show the menu.

        num_of_songs = load(library);  //Assign the returned value to num_of_songs.

        if(a_task == 1)                //If the user choose task one.
        {
            read_songs(library, num_of_songs);    //Call this function to read in mutiple songs.
            save(library, num_of_songs);          //Call this function to save songs to an external file.
        }
        else if(a_task == 2)                      //If user choose task two.
        {		
            cout << "\n\n\n\n"                   
                 << "The number of songs in the playlist is: "   
	             << num_of_songs << ".\n\n\n";    //Output the number of songs read in. 
            display_songs(library, num_of_songs); //Call this function to display mutiple songs.
        }
        else if(a_task == 3)                      //If user choose task three.
        {
	    if(num_of_songs > 0)                  //Only executes when number of songs is more than zero.
            {
                ask_message();                    //Call this function to output a message.
	            while(again())                    //Only executes when true is returned from again function.
                {
                    display_specific_songs(library, user_choice, num_of_songs); //Display matched songs.
	                cout << "\n\n\nWanna enter another choice to find matched songs?";
                }
            }
	    else                                 //Executes when number of songs is not more than zero.
	        cout << "\n\nSorry! There is no song in the playlist yet!\n\n";
        }

	if(a_task != 4)
	    cout << "\n\nDo you want to check the menu again?\n"
             << "(Enter Y/y if you want to continue, enter N/n"
	         << " if you want to exit.)";
    }while(a_task != 4 && again());  //Only repeats when user didn't choose to exit and true is returned.

    cout << "\n\n\n\nThank you for using our program!\n\n"
	     << "Have a wonderful day!\n\n\n";      //Output ending messages.

    return 0;
}


//Output the welcome message and explain what the program can do.
void welcome()
{
    cout << "\n\n\nWelcome to our Music Playlist program!\n\n\n"
	 << "Here are what this program can do for you:\n\n1. It "
	 << "allows you to add new songs and display all songs.\n\n2. "
	 << "It can save the current list of songs to an external file"
	 << " and also load new songs from a file previously stored."
	 << "\n\n3. When you enter a situation, the program will "
	 << "display all songs that match with that particular choice."
	 << "\n\n\n\n";
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
	 << "Enter 2 - Display saved songs.\n"
	 << "Enter 3 - Display all songs that match a particular choice.\n"
	 << "Enter 4 - Exit.\n\n\n"
	 << "Now, please enter a number (1-4): ";
    do
    {
        cin >> task;              //Read in the user's answer.
	    cin.ignore(100, '\n');
	    if(task < 1 || task > 4)
	        cout << "\n\nYou entered a wrong number!\n\nPlease enter a "
		         << "number between 1 and 4(inclusive): ";
    }while(task < 1 || task > 4); //Repeat until user enters a proper number.
}


//This function takes a structure variable as an argument and reads in contents about a song.
void read_a_song(music & a_song)
{
    cout << "\n\n\n\n";                   //new lines

    //Prompt and read in the artist, title, type, situation and link.
    cout << "Please enter the artist for the song: ";
    cin.get(a_song.artist, ARTIST, '\n');
    cin.ignore(100, '\n');

    cout << "Please enter the title for the song: ";
    cin.get(a_song.title, TITLE, '\n');
    cin.ignore(100, '\n');

    cout << "Please enter the song type: ";
    cin.get(a_song.type, TYPE, '\n');
    cin.ignore(100, '\n');

    cout << "Please enter one situation when you like to listen to it\n"
	     << "(enter a few words, e.g. taking test / driving / working out): ";
    cin.get(a_song.when, WHEN, '\n');
    cin.ignore(100, '\n');

    cout << "Please enter the link for the song: ";
    cin.width(LINK);        //Restrict the length to LINK-1
    cin >> a_song.link;
    cin.ignore(100, '\n');
}


//This function takes a structure variable as an argument and 
//displays contents about a song.
void display_a_song(music & a_song)
{
    cout << "Artist: " << a_song.artist << endl
	 << "Title: " << a_song.title << endl
	 << "Type: " << a_song.type << endl
	 << "I listen to it when: " << a_song.when << endl
	 << "The link to access is: "
	 << a_song.link << "\n\n\n";
}


//This function takes an array of structures and an integer as arguments
//and it reads in contents about songs.
void read_songs(music library[], int & num)
{
    cout << "\n\n\nDo you want to add a new song?\n";

    //Call again function, this loop will only be executed when true was
    //returned and when num is less than the size of the array of structures.
    while(again() && num < SONGS) 
    {
        read_a_song(library[num]);   //Call the function to read in each single song.
	    ++ num;                      //Increment num by one.
	    cout << "\n\n\nAnother song? ";
    }
}


//This function takes an array of structures and an integer as arguments 
//and it displays contents about songs.
void display_songs(music library[], int num)
{
    for(int i = 0; i < num; ++i)
        display_a_song(library[i]); //Call this function in a for loop to display songs.
}


//This function takes an array of structures as an argument and reads information
//from a file, then it would return the number of songs read in.
int load(music library[])
{
    ifstream file_in;       //This variable will be used to read from a file.
    int temp = 0;

    //Load any songs stored in an external data file -- song.txt
    file_in.open("song.txt"); 

    if(file_in)            //file_in would return true if we connected successfully
    {
	    //Try to read first so that we can test if it's the end of file later.
        file_in.get(library[temp].artist, ARTIST, '|');
	    file_in.ignore(100, '|');

	    //This while loop only executes when it's not the end of file and when 
	    //the number of songs read in is less than the constant SONGS.
	    while(!file_in.eof() && temp < SONGS)
	    {
	        file_in.get(library[temp].title, TITLE, '|');
	        file_in.ignore(100, '|');
	    
	        file_in.get(library[temp].type, TYPE, '|');
	        file_in.ignore(100, '|');
	    
	        file_in.get(library[temp].when, WHEN, '|');
	        file_in.ignore(100, '|');

	        file_in >> library[temp].link;
	        file_in.ignore(100, '\n');

	        ++ temp;       //Increment temp by one.

	        file_in.get(library[temp].artist, ARTIST, '|'); //Try to read first.
	        file_in.ignore(100, '|');
        }
	    file_in.close();   //Close the file when done.
    }
    return temp;           //Return the number of songs read in.
}


//This function takes an array of structures and an integer as arguments, and 
//it saves the songs read in to an external data file.
void save(music library[], int num_to_save)
{
    ofstream file_out;                    //This variable will be used to write to a file.
    file_out.open("song.txt");            //Try to connect to the file.

    if(file_out)    //file_out would return true if we connected successfully
    {
        for(int i = 0; i < num_to_save; ++i)
	    {
	        file_out << library[i].artist << '|'
		             << library[i].title << '|'
		             << library[i].type << '|'
		             << library[i].when << '|'
		             << library[i].link << endl;
	    }
	    file_out.close();   //Close the file when done.
    }
}


//This function takes an array of structures and an integer as arguments, and
//it will display all the situations in terms of when the songs are listened.
void display_whens(music library[], int num)
{
    cout << "\n\n\n\n"
	 << "Here are all the situations that you entered,"
	 << " in terms of when you would listen to the "
	 << "songs in the playlist: \n\n";

    for(int i = 0; i < num; ++i)
        cout << library[i].when << endl;
}
    

//This function takes an array of structures, an array of characters and an integer 
//as arguments, and it will check if there is any song matches with user's choice.
bool is_match(music library[], char choice[], int num)
{ 
    display_whens(library, num); //Call this function to display all situations.

    cout << "\n\n\nPlease enter your choice here(it has to be "
	     << "something listed above): ";
    cin.get(choice, WHEN, '\n');
    cin.ignore(100, '\n');

    for(int i = 0; i < num; ++i) //Loop through the array.
    {
        if(strcmp(choice, library[i].when) == 0)
	    return true;    //Return true once there is a match with user's choice.
    }
    return false;           //Return false when there's no match at all.
}       	


//This function takes no arguments, it displays a message to the user and asks
//if the user wants to find a match or not.
void ask_message()
{    
    cout << "\n\nNow, you can enter a situation in terms of"
	     << " when you would listen to some songs, then\n"
         << "the program would display all songs that "
	     << "match with this choice.\n\n(WARNING: You have "
	     << "to enter a choice that is listed, otherwise, "
	     << "there will be\nnothing matches with your answer!)"
         << "\n\nDo you want to find songs"
         << " that match with your choice?";
}


//This function takes an array of structures, an array of characters and an integer 
//as arguments, and it will display specific songs based on user's choice.
void display_specific_songs(music library[], char choice[], int num)
{
    bool match;          //Create a bool variable.

    match = is_match(library, choice, num); //Assign match with the returned value.

    if(!match)          //If false was returned.
        cout << "\n\nSorry! There is no match in the playlist "
	         << "with the choice: " << choice << endl;
    else               //If true was returned.
    {
        cout << "\n\n\nHere are all songs you listen to when "
	         << choice << ": \n\n";

        for(int i = 0; i < num; ++i)         //Loop through the array.
        {
            if(strcmp(choice, library[i].when) == 0)
	        {   	
	        display_a_song(library[i]); //Display all songs match with this choice.
	        cout << "\n\n";
            }
        }
    }
}	
