#include "survey_list.h"
using namespace std;

//Siqi Wen CS163
//This file includes implementations of member functions in the class
//survey which was created in the survey_list.h file. Each function will
//return a value which will be used when the function gets called in main.
//And depends on the returned value, specific instructions will be executed.


//Constructor - initialize the data members
survey::survey()
{
    head = NULL;
}
	

//Destructor - deallocate the dynamic memory used by the class
survey::~survey()
{
    if(head)
    {
        node_app * current = head;
        while(current)
	{
	    if(current->head_ofuse)
	    {
	        node_use * temp = current->head_ofuse; //Create a pointer points to the
		while(temp)                            //beginning of the usage list.
		{
		    temp->usage.frequency = 0;         //Reset all data members in the node_use
		    if(temp->usage.reason)             //to their zero equivalent values.
		        delete [] temp->usage.reason; 
		    temp = temp->next_ofuse;
		    delete current->head_ofuse;
		    current->head_ofuse = temp;
		}
	    }
	    current = current->next;
	    delete head;    //This will implicitly call the destructor of the app_info class.
	    head = current;
	}
    }
}


//This function takes two class objects and it would call another
//function from the app_info class with the same arguments. An
//integer will be returned.
int survey::compare_name(app_info & obj1, app_info & obj2)
{
    int cmp_result = head->application.compare(obj1, obj2);
    return cmp_result;
}


//This function takes an app_info object and a pointer as arguements,
//it will find out if the names match and will return an integer.
int survey::matching_names(app_info & obj1, char * input_n)
{
    int cmp_n_result = head->application.matching_n(obj1, input_n);
    return cmp_n_result;
}


//This function takes a class object as an arguement and will
//add a new application to the list.
bool survey::add_new(app_info & toadd_app)
{
    node_app * temp = new node_app;  //Store the new node in a temp pointer.
    if(!temp->application.copy_one(toadd_app)) //Copy the info from a single
    {                                          //app_info object into another
	delete temp;                           //app_info object which is in
        return false;                          //a node_app.
    }
    if(!head)               //Call the compare_name function to figure out the
    {                       //right spot to insert the new node_app.
        head = temp;
	head->next = NULL;  //When the list was empty, head will be changed.
    }
    else if(compare_name(temp->application, head->application) == 0)
    {
	delete temp;
        return false;       //If the name is the same as the one in first node.
    }
    else if(compare_name(temp->application, head->application) < 0)
    {
        temp->next = head;  //If this node_app should be inserted before first node.
	head = temp;
    }
    else
    {
        node_app * previous = head;
        node_app * current = head->next;
        while(current && compare_name(temp->application, current->application) > 0)
        {
            previous = current;       //Traverse to the right spot.
	    current = current->next;
        }
        if(current && compare_name(temp->application, current->application) == 0)
	{
	    delete temp;
	    return false;  //If the app name already existed in the app list.
	}
        else	
        {
            previous->next = temp;
	    temp->next = current;
        }
    }
    return true;
}
	

//This function will call the display_one_app function in the
//app_info class and display all applications in the list.
int survey::display_all_apps() const
{
    if(!head)    //Empty list.
	return 0;
    if(!head->application.display_one_app())
        return 0;
    node_app * current = head->next;
    while(current)  //Traverse all the way to the end.
    {
        current->application.display_one_app();
	current = current->next;
    }
    return 1;
}
	

//This function takes a pointer and an use_info object as arguments
//it will insert survey information for a given app and return success.
bool survey::insert(char * ap_name, use_info & toadd_use)
{
    if(!ap_name || !toadd_use.frequency || !toadd_use.reason)
        return false;
    if(!head)
	return false;
    
    //Create a new node_use, and copy the information we got from main
    //into the data members in the use_info in this node_use.
    node_use * hold_use = new node_use;
    hold_use->usage.frequency = toadd_use.frequency;
    hold_use->usage.reason = new char[strlen(toadd_use.reason) + 1];
    strcpy(hold_use->usage.reason, toadd_use.reason);
    hold_use->next_ofuse = NULL;

    //First, find the matching app name in the LLL of node_app, then
    //find the right spot to insert this node_use in the LLL of node_use.
    node_app * current = head;
    int which_app = matching_names(current->application, ap_name);
    while(current && which_app)
    {
        current = current->next;
        if(current)
            which_app = matching_names(current->application, ap_name);
    }
    if(current)
    {
        if(!current->head_ofuse)  //If the LLL of node_use is empty, then just
	{                         //add the new node_use in the beginning
            current->head_ofuse = hold_use;
	    current->head_ofuse->next_ofuse = NULL;
	}

	//When the new node_use needs to be inserted in front of the first
	//node_use in the LLL
	else if(hold_use->usage.frequency > current->head_ofuse->usage.frequency)
	{                         
	    hold_use->next_ofuse = current->head_ofuse;
	    current->head_ofuse = hold_use;
	}
	else    //Insert in the middle or at the end
	{
	    node_use * previous = current->head_ofuse;
	    node_use * traverseptr = current->head_ofuse->next_ofuse;
	    while(traverseptr && hold_use->usage.frequency <= traverseptr->usage.frequency)
	    {
	        previous = traverseptr;
		traverseptr = traverseptr->next_ofuse;
	    }
	    hold_use->next_ofuse = traverseptr;
	    previous->next_ofuse = hold_use;
	}
	return true;
    }
    return false;
}


//This function takes an app_info object and a pointer as arguments,
//it would call another function to check if the object's type match
//with the pointer's type. An integer would be returned.
int survey::matching_types(app_info & obj, char * some_type)
{
    int m_types = head->application.matching_t(obj, some_type);
    return m_types;
}


//This function takes an app_info object as an argument, and it would
//call another function to display an app name. An integer would be
//returned for success.
int survey::display_one_appname(app_info & obj) const
{
    int output_name = head->application.display_one_name(obj);
    return output_name;
}


//This function takes a pointer as an argument, it would display
//the list of usage for applications of a specific type.
int survey::display_usage(char * some_type)
{
    cout << "\n\nFor type: " << some_type << ":\n\n";
    if(!some_type)     //If the input is not valid
        return 0;
    if(!head)          //If the list of app is empty
	return 0;

    node_app * current = head;
    int num_user = 0;  //Represent the user's number...user 1; user 2 and so on.
    int yes_match = 0; //This value will be returned from this function.
    while(current)
    {
	num_user = 0;  //Has to be reset to zero when it's a different app.

	//If a specific app's type matches with the input for type.
        if(!matching_types(current->application, some_type))
	{
	    if(current->head_ofuse) //when the list of usage for this app is not empty
            {   
	        node_use * temp = current->head_ofuse;
	        if(display_one_appname(current->application)) //display the app name
	        {
	            while(temp)   //Display the whole list of usage info for this app.
	            {
		        ++ num_user;
	                cout << "\n\nHere is info of usage from User "
		             << num_user << ":\n"
		             << "\nThe frequency of use is: "
		             << temp->usage.frequency
		             << "\nThe main reason of use is: "
		             << temp->usage.reason << "\n\n";
			temp = temp->next_ofuse;
	            }
	        }
	        yes_match = 1;   //set the return value to 1 when any usage info was displayed
	    }
	}
	current = current->next; //Traverse over the list of app.
    }
    return yes_match;
}


//This function takes a pointer as an argument and it would
//remove an app and its list of usage info by the app name.
bool survey::remove_an_app(char * app_name)
{
    if(!app_name)
        return false;
    if(!head)
        return false;
    if(!matching_names(head->application, app_name))
    {                                      //If the first app is the match.
        if(head->head_ofuse)               //We need to remove the list of usage of
	{                                  //that app before we remove the app.
	    node_use * temp = head->head_ofuse;
	    head->head_ofuse = NULL;
	    node_use * hold = temp;
	    while(temp)
	    {
	        hold = temp->next_ofuse;
		if(temp->usage.reason)            //Only deallocating the memory of an array
		    delete [] temp->usage.reason; //when the pointer is not NULL.
		delete temp;
		temp = hold;
	    }
	}
	node_app * hold_applist = head->next;     //Remove the app from the app list after
	delete head;                              //deallocating memory for the usage list.
	head = head->next;
    }
    else  //To remove in the middle or at the end of the app list.
    {     //Or maybe there is no matching app in the list, then return false.
        node_app * previous = head;
	node_app * current = head->next;
	while(current && matching_names(current->application, app_name))
	{
            previous = current;
	    current = current->next;
	}
	if(current)
	{
	    if(current->head_ofuse)           //Same here, remove the usage list first,
	    {                                 //then remove the specific app node.
	        node_use * h = current->head_ofuse;
		current->head_ofuse = NULL;
		node_use * t = h;
		while(h)
		{
		    t = h->next_ofuse;
		    if(h->usage.reason)
		        delete [] h->usage.reason;
		    delete h;
		    h = t;
		}
	    }
            previous->next = current->next;
	    delete current;
	}
	else        //This is when there's no matching app in the app list.
	    return false;
    }
    return true;
}
