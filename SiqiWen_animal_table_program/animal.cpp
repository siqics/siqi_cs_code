#include "table.h"
using namespace std;



//Siqi Wen CS163
//This file contains the implementations of member functions
//in the animal class, including the constructor and destructor;
//a function to create a new animal and copy the new animal's info;
//a function to display one animal's info; a function to display all
//matches based on type and breed; a function to retrieve an animal
//based on breed and name and it would copy and pass the info into
//the animal object that was passed as an argument.


/*
        char * type;
        char * breed;
        char * name;
        char * require;
        int age;
        char * desc;
*/



//Constructor - initialize the data members.
animal::animal()
{
    type = NULL;
    breed = NULL;
    name = NULL;
    require = NULL;
    age = 0;
    desc = NULL;
}



//Destructor - release all dynamically allocated memory.
animal::~animal()
{
    remove_all_info();
}



//This function will remove all info for an animal. It takes
//no arguments and return 1 for success.
int animal::remove_all_info()
{
    if(type)                 //Make sure the pointers are not NULL
    {                        //before deallocating the memory.
        delete [] type;
	type = NULL;
    }
    if(breed)
    {
	delete [] breed;
	breed = NULL;
    }
    if(name)
    {
	delete [] name;
	name = NULL;
    }
    if(require)
    {
	delete [] require;
	require = NULL;
    }
    age = 0;
    if(desc)
    {
	delete [] desc;
	desc = NULL;
    }
    return 1;
}



//This function takes an array of characters, which is a file name, as an
//argument, it saves the animal read in to an external data file. 1 will
//be returned if we connected to the file successfully, if not, 0 will
//be returned.
int animal::save_file(char filename[])
{
    ofstream file_out;                    //This variable will be used to write to a file.
    file_out.open(filename, ios::app);    //Try to connect to the file.

    if(file_out)    //file_out would return true if we connected successfully
    {
        file_out << type << '|'
		 << breed << '|'
		 << name << '|'
		 << require << '|'
		 << age << '|'
		 << desc << endl;

	file_out.close();   //Close the file when done.
	return 1;
    }
    return 0;
}



//This function takes an integer as an argument and would
//return an integer for the index for the hash table.
//There would be some math operation with the animal's
//type and animal's breed.
int animal::hash_function(int si)
{
    int len_type = strlen(type);
    int len_breed = strlen(breed);

    int result = 0;
    int index = 0;
    int len = 0;
    if(len_type < len_breed)           //use the shorter length
        len = len_type;
    else
	len = len_breed;

    for(int i = 0; i < len_type; ++i)  //turn every character in the array
        type[i] = tolower(type[i]);    //into lowercase
    for(int j = 0; j < len_breed; ++j)
	breed[j] = tolower(breed[j]);

    for(int k = 0; k < len; ++k)       //This math operation adds up the ASCII values of
    {                                  //all characters in the range of the shorter length
        result += type[k] + breed[k];  //from the two lengths of the arrays of characters.
    }
    index = result % si;               //use the mod operator to get a number
    return index;
}



//This function takes five pointers and one integer as arguments,
//it would create an animal with user's input and return 0 or 1
//for failure or success.
int animal::create_animal(char * t, char * b, char * n, char * r, int a, char * d)
{
    if(!t || !b || !n || !r || !d)   //If there's something wrong with
        return 0;                    //user's input.

    type = new char[strlen(t)+1];  //Allocate the right size of memory for pointers.
    strcpy(type, t);               //Copy user's input to the data member.
    breed = new char[strlen(b)+1];
    strcpy(breed, b);
    name = new char[strlen(n)+1];
    strcpy(name, n);
    require = new char[strlen(r)+1];
    strcpy(require, r);
    age = a;
    desc = new char[strlen(d)+1];
    strcpy(desc, d);

    return 1;
}



//This function takes an animal pointer as an argument, it would
//compare the breeds and return an integer for result, which
//represents one of the breeds is alphabetically bigger or smaller
//than the other breed.
int animal::compare_breeds(animal * toadd)
{
    int result = strcmp(toadd->breed, breed);
    return result;
}



//This function takes a pointer as an argument, it would
//compare the breeds and return an integer for result, which
//represents one of the breeds is alphabetically bigger or smaller
//than the other breed.
int animal::compare_brs(char * br)
{
    int result = strcmp(br, breed);
    return result;
}



//This function takes an animal pointer as an argument, it would
//compare the names and return an integer for result, which
//represents one of the names is alphabetically bigger or smaller
//than the other name.
int animal::compare_names(animal * toadd)
{
    int result = strcmp(toadd->name, name);
    return result;
}



//This function takes a pointer as an argument, it would
//compare the names and return an integer for result, which
//represents one of the names is alphabetically bigger or smaller
//than the other name.
int animal::compare_nas(char * na)
{
    int result = strcmp(na, name);
    return result;
}



//This function takes two pointers as argument, and return
//an integer for success or failure. It would copy the type
//and breed from the arguments into the data members.
int animal::copy_type_breed(char * ty, char * br)
{
    if(!ty || !br)                   //If any of the arguments is invalid
        return 0;

    type = new char[strlen(ty)+1];   //Allocate the right size for the array
    strcpy(type, ty);                //and copy the data.
    breed = new char[strlen(br)+1];
    strcpy(breed, br);

    return 1;
}



//This function takes no argument and returns 1 for success.
//It will display one animal's info.
int animal::display_one_animal() const
{
    if(type && breed && name && require && desc)
    {
        cout << "\n\n\nType: " << type
	     << "\nBreed: " << breed
	     << "\nName: " << name
	     << "\nRequirement: " << require
	     << "\nAge: " << age
	     << "\nDescription: " << desc
	     << "\n\n\n";
	return 1;
    }
    return 0;
}



//This function takes two pointers as arguments, it would compare
//the type and breed with the arguments. An integer will be returned,
//1 if they match, 0 if they don't match.
int animal::if_match(char * a_type, char * a_breed) const
{
    if(!strcmp(type, a_type) && !strcmp(breed, a_breed))
        return 1;
    return 0;
}



//This function looks for a particular animal based on their
//breed and name, an integer will be returned, 1 if they match,
//0 if they don't match.
int animal::if_match_br_na(char * a_breed, char * a_name) const
{
    if(!strcmp(breed, a_breed) && !strcmp(name, a_name))
        return 1;
    return 0;
}


