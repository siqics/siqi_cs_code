#include "music.h"

//Siqi Wen CS162
//The purpose of this file is to implement the member functions
//provided in the playlist class. These functions are mostly doing
//things to the playlist, such as: setting up the size for the playlist;
//reading in songs from the user and adding them to the playlist; displaying
//all songs in the playlist; displaying only songs based on user's choice
//of type; allowing user to edit information of songs.


//This is the playlist constructor and it should initialize all of the
//data members in the playlist class.
playlist::playlist()
{
    song = NULL;  //Initialize this pointer to NULL.
    size = 0;     //Initialize size to zero.
    num = 0;      //Initialize num to zero.
}

//This is the playlist destructor and it should reset all of the data
//members to the zero equivalent values.
playlist::~playlist()
{
    song = NULL;  //Reset this pointer to NULL.
    size = 0;     //Reset size to zero.
    num = 0;      //Reset num to zero.
}

//This function prompts the user for the size they want 
//for the playlist.
void playlist::get_size()
{
    cout << "\n\n\nPlease think about how many songs you might want to "
	 << "add.\nThen enter a whole number for the size you want"
	 << " for the playlist: ";
    do
    {
        cin >> size;            //Read in the size the user wants.
        cin.ignore(100, '\n');

	if(size < 0 || size == 0)
	    cout << "\n\nYou have to enter a size bigger than zero!\n"
		 << "Please re-enter a whole number for the size: ";
    }while(size < 0 || size == 0);  //Loop until user enters a proper number.

    song = new music[size];    //Create a dynamically allocated array of structures.

    cout << "\n\n\nThe size you entered for the playlist is : " 
	 << size << "\n\n\n";
}

//This function takes a structure variable as an argument and reads 
//in contents about a song.
void playlist::read_one(music & a_song)
{
    cout << "\n\n\n\n";       //new lines

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
void playlist::display_one(music & a_song)
{
    cout << "Artist: " << a_song.artist << endl
	 << "Title: " << a_song.title << endl
	 << "Type: " << a_song.type << endl
	 << "I listen to it when: " << a_song.when << endl
	 << "The link to access is: "
	 << a_song.link << "\n\n\n";
}

//This function will read in new songs from the user and store them 
//in the playlist.
void playlist::read_all()
{
    cout << "\n\n\nThe size you entered for the playlist is : " 
	 << size << "\n\n\n" << "The current number of songs "
	 << "is: " << num << "\n\n\n";

    if(num == size)              //Inform user when the playlist is full.
        cout << "\n\n\nSorry, the playlist is FULL!\nYou can't"
             << " enter another song!\n\n\n";
    else if(num < size)
    {
        cout << "\n\n\nDo you want to add a new song?\n\n";

        //Keep looping until user has no more song to add or the array is full.
        while(num < size && again())
        {
            read_one(song[num]);  //Read in contents for every song.
            ++ num;               //Increment num by one.
	    if(num == size)       //Inform user when the playlist is full.
                cout << "\n\n\nSorry, the playlist is FULL!\nYou can't"
                     << " enter another song!\n\n\n";
	    else
                cout << "\n\n\nAnother song? ";
        }
    }
}

//This function will display all of the songs.
void playlist::display_all()
{
    if(num == 0)   //When there is no song in the playlist.
        cout << "\n\n\nThere is no song in the playlist!\n\n";
    else           //When the playlist is not empty.
    {
	cout << "\n\n\nThe number of songs in the playlist is: "
	     << num << "\n\n\n";     //Output the amount for the number of songs.
        for(int i = 0; i < num; ++i) //Iterate over the array.
            display_one(song[i]);    //Display each song each time.
    }
}

//This function will release the memory to avoid memory leak,
//and it will output the ending messages.
void playlist::exit()
{
    if(song != NULL)  //Release the memory once we're done to avoid memory leak.
        delete []song;  

    cout << "\n\n\n\nThank you for using our program!\n\n"
	 << "Have a wonderful day!\n\n\n";      //Output ending messages.
}

//This function takes an array of characters as an argument and it will find out if
//there is any match with the user's input for some type, then return true or false.
bool playlist::match_type(char array[])
{
    bool match = false;   //Create a bool variable and initialize it with false.

    cout << "\n\n\n\nHere are all the types for the songs "
	 << "in the playlist:\n\n\n";
    for(int i = 0; i < num; ++i)      //Output all type options.
        cout << song[i].type << endl; 

    cout << "\n\n\n\nYou can enter a type, then the program "
	 << "will output all songs that are of this type."
	 << "\n\n\nBut you have to enter something showed above"
	 << " or you won't find any match!\n\n\nPlease enter your"
	 << " choice of type here: ";
    cin.get(array, TYPE, '\n');
    cin.ignore(100, '\n');
 
    for(int i = 0; i < num && !match; ++i)  //Compare user's input with the type options
    {                                       //and check if there's a match, if there is,
        if(strcmp(array, song[i].type)==0)  //assign match with true, if not, match will
            match = true;                   //be returned as false.
    }
    return match;
}

//This function takes an array of characters as an argument and it will prompt
//the user for an input and display only songs that are of a particular type.
void playlist::display_specific(char array[])
{
    bool matching_type;  //This variable will be assigned with a returned value.

    if(num == 0)         //If the playlist is empty.
        cout << "\n\n\nThe playlist is empty!\n\n"
	     << "You have to enter some songs first!"
	     << "\n\n\n\n";
    else                //If the playlist is not empty.
    {
	matching_type = match_type(array);  //Assign with the value from this funtion.
        if(matching_type)                   //If true was returned.
	{
	    cout << "\n\n\n\nHere are all songs that "
		 << "match with the type: " << array;
            for(int i = 0; i < num; ++i)   //Iterate over the array, and output all
            {                              //songs match with this choice of type.
                if(strcmp(array, song[i].type)==0)
		{
		    cout << "\n\n\n\n";
                    display_one(song[i]);
		}
	    }
        }
	else                              //If false was returned.
	    cout << "\n\n\n\n\nSorry! There is no song "
		 << "matches with type: " << array << "\n\n\n";
    }
}

//This function takes an array of characters as an argument and it will find out if
//there is any match with the user's input for some title, then return true or false.
bool playlist::match_title(char array[])
{
    bool match = false;   //Create a bool variable and initialize it with false.

    cout << "\n\n\n\nHere are all the titles for the songs "
	 << "in the playlist:\n\n\n";
    for(int i = 0; i < num; ++i)             //Output all title options.
        cout << song[i].title << endl; 

    cout << "\n\nYou can enter a title, then the program will "
	 << "check if there's a song\nmatches with this title."
	 << " If there is, then the program will ask you\nwhat "
	 << "information you'd like to edit about this song, follow "
	 << "the instructions,\nthen you'll be able to edit the song's"
	 << " information. If there's no match,\nthen you can't edit any"
	 << " song's information.\n\nWARNING: When you enter a title, make"
	 << " sure to enter something that is exactly the same as one of "
	 << "the titles showed above!\n\n\nEnter the title here: ";
    cin.get(array, TITLE, '\n');             //Read in user's input for a song title.
    cin.ignore(100, '\n');
 
    for(int i = 0; i < num && !match; ++i)   //Compare user's input with the title options
    {                                        //and check if there's a match, if there is,
        if(strcmp(array, song[i].title)==0)  //assign match with true, if not, match will
            match = true;                    //be returned as false.
    }
    return match;
}

//This function will call another function and allow user to edit the 
//information about a particular song.
void playlist::edit(char array[])
{ 
    bool matching_title;  //This variable will be assigned with a returned value.
    int part_edit = 0;    //A variable that is passed in which_to_edit function.
    char n_info[LINK];    //A variable for the new information.

    if(num == 0)         //If the playlist is empty.
        cout << "\n\n\nThe playlist is empty!\n\n"
	     << "You have to enter some songs first!"
	     << "\n\n\n\n";
    else                //If the playlist is not empty.
    {
	matching_title = match_title(array);  //Assign with the value from this funtion.
        if(matching_title)                    //If true was returned.
	{
	    for(int i = 0; i < num; ++i)      //Iterate over the array.
	    {                                 //Find the matching song.
	        if(strcmp(array, song[i].title)==0)
		{                             //Figure out which part user wants to edit.
                    which_to_edit(array, part_edit, n_info);
		    if(part_edit == 1)
	            {
			cout << "\n\nFor song: " << array  //Inform user the updated information.
		             << ", you replaced the artist: "
			     << song[i].artist << " with the "
			     << "new artist: " << n_info 
			     << "\n\n\n";
		        strcpy(song[i].artist, n_info);   //Update the information.
		    }
		    else if(part_edit == 2)
		    {
			cout << "\n\nFor song: " << array
                             << ", you replaced the type: "
                             << song[i].type << " with the "
                             << "new type: " << n_info
                             << "\n\n\n";
			strcpy(song[i].type, n_info);    //Update the information.
	            }
		    else if(part_edit == 3)
		    {
			cout << "\n\nFor song: " << array
                             << ", you replaced the situation(when"
			     << " you would listen to this song): "
                             << song[i].when << " with the "
                             << "new situation: " << n_info
                             << "\n\n\n";
			strcpy(song[i].when, n_info);   //Update the information.
		    }
		    else
		    {
			cout << "\n\nFor song: " << array
                             << ", you replaced the link: "
                             << song[i].link << " with the "
                             << "new link: " << n_info
                             << "\n\n\n";
			strcpy(song[i].link, n_info);   //Update the information.
		    }
		}
	    }
        }
	else                              //If false was returned.
	    cout << "\n\n\n\n\nSorry! There is no song "
		 << "matches with title: " << array << "\n\n\n";
    }
}
