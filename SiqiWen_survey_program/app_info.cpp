#include "survey_list.h"
using namespace std;

//Siqi Wen CS163
//This file contains implementations of the member functions in the class
//app_info which was created in the survey_list.h file. Each of the function
//will either return true/false or a number, and the returned value will be
//used in the member functions in survey list.


//Constructor - initialize the data members
app_info::app_info()
{
    name = NULL;
    type = NULL;
    desc = NULL;
}


//Destructor - deallocate the dynamic memory used by the class
app_info::~app_info()
{
    if(name)             //Make sure the pointers are not NULL
        delete [] name;  //before deallocating the memory.
    if(type)
	delete [] type;
    if(desc)
	delete [] desc;
    name = NULL;
    type = NULL;
    desc = NULL;
}


//This function takes three pointers as arguments and copies the value of
//user's input into the data members.
bool app_info::add_one(char * new_name, char * new_type, char * new_desc)
{
    if(!new_name || !new_type || !new_desc)  //If there's something wrong with
        return false;                        //user's input.

    if(name)             //If name is already pointing to some memory, delete it first 
	delete [] name;  //to avoid memory leak.
    if(type)
	delete [] type;
    if(desc)
	delete [] desc;
    name = new char[strlen(new_name) + 1]; //Allocate the right size of memory for pointers.
    strcpy(name, new_name);                //Copy user's input to the data member.
    type = new char[strlen(new_type) + 1];
    strcpy(type, new_type);
    desc = new char[strlen(new_desc) + 1];
    strcpy(desc, new_desc);
    return true;                           //return true when the process was successful
}


//This function takes a class object as an argument, then it would add a new app
//to the list. And it would return a bool value to represent the success or failure.
bool app_info::copy_one(app_info & toadd_app)
{
    if(!toadd_app.name || !toadd_app.type || !toadd_app.desc)
        return false;    //return false if there's something worng with the values

    if(name)             //If name is already pointing to some memory, delete it first 
	delete [] name;  //to avoid memory leak.
    if(type)
	delete [] type;
    if(desc)
	delete [] desc;
    name = new char[strlen(toadd_app.name) + 1]; //Allocate the right size for arrays.
    strcpy(name, toadd_app.name);                //Copy the information from a single
    type = new char[strlen(toadd_app.type) + 1]; //app_info object item into another
    strcpy(type, toadd_app.type);                //app_info object item which is in a
    desc = new char[strlen(toadd_app.desc) + 1]; //node_app.
    strcpy(desc, toadd_app.desc);
    return true;        //return true if the process was successful
}


//This function take two ojects as arguments and it compares the arrays
//which are data members in those two objects. The function would return
//a number.
int app_info::compare(app_info & obj1, app_info & obj2)
{
    int cmp = strcmp(obj1.name, obj2.name);
    return cmp;  //return an integer which might be zero or positive or negative
} 


//This function takes an app_info object and a pointer as arguments,
//it will compare the names' alphabetic orders to see if they match
//and it will return an integer. 
int app_info::matching_n(app_info & obj1, char * in_name)
{
    int cmp_n = strcmp(obj1.name, in_name);
    return cmp_n;  //return an integer which might be zero or positive or negative
} 


//This function will display all information of one application.
int app_info::display_one_app() const
{
    if(!name || !type || !desc)
        return 0; 
    cout << "\n\nApp name: " << name
	 << "\nApp type: " << type
	 << "\nDescription: " << desc
	 << endl;
    return 1;
}


//This function takes an app_info object and a pointer as arguments,
//it will compare the types and see if they match. It will return an
//integer as a result, which would be zero or positive or negative.
int app_info::matching_t(app_info & obj, char * some_type)
{
    int m_type = strcmp(obj.type, some_type);
    return m_type;
}


//This function takes an app_info object as an argument, and it
//would display name for that object. and return 1 for success.
int app_info::display_one_name(app_info & obj) const
{
    cout << "\n\n\n\nApp name is: " << obj.name;
    return 1;
}
