#include <iostream>
#include <cctype>
#include <cstring>
using namespace std;

//Siqi Wen CS162
//This code contains constants for the sizes of the members in the structure,
//prototypes of functions that will be called in main, a structure definition
//of each song's contents and a class (named playlist) interface that contains
//member functions and data members.

//constants
const int ARTIST = 31;
const int TITLE = 41;
const int TYPE = 21;
const int WHEN = 26;
const int LINK = 81;

//Create a structure with five members.
struct music
{
    char artist[ARTIST]; //Create an array of characters for the song's artist.
    char title[TITLE];   //Create an array of characters for the song's title.
    char type[TYPE];     //Create an array of characters for the song's type.
    char when[WHEN];     //Create an array of characters for a situation.
    char link[LINK];     //Create an array of characters for the song's link.
};

//Create a class interface with member funtions and data members.
class playlist
{
    public:
        playlist();   //Constructor - initialize the data members.
	~playlist();  //Destructor - deallocate the dynamic memory used by the class.
	void get_size();                  //Prompt user for the size they want.
	void read_one(music & a_song);    //Read in one song from the user.
	void read_all();                  //Read in new songs from the user.
	void display_one(music & a_song); //Display one song.
	void display_all();               //Display all of the songs.
	bool match_type(char array[]);        //Check if there's a matching type.
	void display_specific(char array[]);  //Display specific songs.
	bool match_title(char array[]);       //Check if there's a matching title.
	void edit(char array[]);  //Edit the information about a particular song.
	void exit();              //Exit the program.
    private:
        music * song;      //Create a pointer to the music struct.
	int size;          //The size of the array once it is allocated.
	int num;           //The number of songs stored in the array.
};

//Prototypes
void welcome();                                                       //Output the welcome message.
bool again();                                                         //Ask if the user wants to do again. 
void menu(int & task);                                                //Show the user the menu. 
void which_to_edit(char array[], int & part_edit, char n_info[]);     //Analyze what information will be edited.
