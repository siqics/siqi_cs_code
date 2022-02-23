#include<iostream>
#include<cstring>
#include<cctype>


//Siqi Wen CS163
//This file contains two class interfaces and three structure definitions: a
//class for the app information that conations member functions and three data
//members; a struct for the usage information that contains the frequency of
//use and the main reason people use it; a struct for the node of usage which
//contains an object of the use_info and a next pointer points to the next node
//of usage; a struct for the node of application which contains an object of the
//app_info a head pointer points to the first node of usage and a next pointer
//that points to the next node of application; a class for the survey that contains
//member functions that will build, modify and destroy the linear linked list of
//applications based on the needs of the client.


//Create a class of app_info that deals with each app's information.
class app_info
{
    public:
	app_info();   //Constructor - initialize the data members
	~app_info();  //Destructor - deallocate the dynamic memory used by the class 
	bool add_one(char * new_name, char * new_type, char * new_desc); //Add app info
        bool copy_one(app_info & toadd_app);             //Add a new application
	int compare(app_info & obj1, app_info & obj2);   //Compares two strings
	int matching_n(app_info & obj1, char * in_name); //Check if names match.
	int display_one_app() const;                     //Display one app
	int matching_t(app_info & obj, char * some_type);//Check for matching type.
	int display_one_name(app_info & obj) const;      //Display one app name.
    private:
        char * name;  //a pointer to a dynamically allocated array of characters for the name
        char * type;  //the type of the app
        char * desc;  //the description of the app
};


//Create a struct of information of usage that contains two members.
struct use_info
{
    int frequency;   //how often people use this app
    char * reason;   //the main reason why people use this app
};


//Create a struct of node for the usage that contains two members.
struct node_use
{
    use_info usage;         //an object of the use_info
    node_use * next_ofuse;  //a next pointer that points to the next node of usage
};


//Create a struct of node for the application that contains three members.
struct node_app
{
    app_info application;   //an object of the app_info
    node_use * head_ofuse;  //a head pointer points to the first node of usage
    node_app * next;        //a next pointer that points to the next node of app
};


//Create a class interface that contains some member functions and data members.
class survey
{
    public:
        survey();  //Constructor - initialize the data members
	~survey(); //Destructor - deallocate the dynamic memory used by the class
	int compare_name(app_info & obj1, app_info & obj2);  //Compares two names and return a number
        bool add_new(app_info & toadd_app);                  //Add a new application to the list
	int display_all_apps() const;                        //Display all applications in the list
	bool insert(char * ap_name, use_info & toadd_use);   //Insert survey information for an app
	int matching_names(app_info & obj1, char * input_n); //Compare if names match.
	int matching_types(app_info & obj, char * some_type);//Check for matching type.
	int display_one_appname(app_info & obj) const;       //Display one app name.
	int display_usage(char * some_type);           //Display usage for application of a type
	bool remove_an_app(char * app_name);           //Remove an app by the name
    private:
	node_app * head;                               //points to the first node of app
};


//Prototypes
void welcome();            //Output the welcome message.
bool again();              //Ask if the user wants to do again. 
void menu(int & task);     //Show the user the menu. 

