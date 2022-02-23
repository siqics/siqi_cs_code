#include "adjacency.h"
using namespace std;


//Siqi Wen CS163
//This file contains implementations of member
//functions in the table class. The functions
//are a constructor and a destructor for the
//adjacency list; inserting an vertex; inserting
//an edge; display each choice we have at any given
//intersection.




//constructor
table::table(int size)       //Initialize each data member in the table class
{                            //And initialize the two pointers in each array
    list_size = size;        //element to NULL.
    adjacency_list = new vertex[list_size];
    for(int i = 0; i < list_size; ++i)
    {
        adjacency_list[i].route_name = NULL;
	adjacency_list[i].head = NULL;
    }
}
    


//destructor
table::~table()
{                          //Reset all data members to their zero equivalent values.
    if(adjacency_list)     //If there's a LLL, we need to deallocate the memory related
    {                      //to the LLL also.
        for(int i = 0; i < list_size; ++i)
	{
	    if(adjacency_list[i].route_name)
	    {
	        delete [] adjacency_list[i].route_name;
		adjacency_list[i].route_name = NULL;
	    }
	    if(adjacency_list[i].head)
	    {
	        node * current = adjacency_list[i].head->next;
		while(adjacency_list[i].head)     //Iterate over the LLL is it exists
		{
		    adjacency_list[i].head->adjacent = NULL;
		    delete adjacency_list[i].head;
		    adjacency_list[i].head = current;
		    if(current)
		        current = current->next;
		}
	    }
	}
	delete [] adjacency_list;   //deallocate the dynamically allocated array
	adjacency_list = NULL;      //at the end, and set the array pointer to NULL.
    }
}



//This function takes a char pointer as an argument, it would
//insert a vertex into the adjacency list. If there is no more
//space to insert a vertex, 0 will be returned as a failure. If
//there's space to insert a vertex, we will insert the vertex
//and return 1 as success.
int table::insert_vertex(char * one_vertex, int & full)
{
    if(!one_vertex)  //make sure the input is valid
        return 0;

    int i = 0;
    while(i < list_size && adjacency_list[i].route_name)
    {
	if(!strcmp(adjacency_list[i].route_name, one_vertex))
	    return 0;            //return 0 if there's already a vertex name same as the new one
        ++ i;                    //Iterate over the array

	if(i == (list_size-1))   //set full to 1 when we fill up all array element
	    full = 1;
    }
    if(i == list_size)           //return 0 if the array if already full
    {
        return 0;
    }
    adjacency_list[i].route_name = new char[strlen(one_vertex)+1];
    strcpy(adjacency_list[i].route_name, one_vertex);
    return 1;
}



//This function takes a two char pointers as arguments,
//it would build an edge between these two vertices, and
//return 1 for success; 0 will be returned if we couldn't
//build an edge between these two vertices.
int table::insert_edge(char * current_vertex, char * to_attach)
{
    if(!current_vertex || !to_attach)  //make sure the inputs are valid
        return 0;
    
    int match_current = 0;
    int match_toattach = 0;
    int i = 0;
    int j = 0;
    while(i < list_size && !match_current)  //Iterate over the array twice and find if
    {                                       //there are macthing vertices with both vertices
	if(adjacency_list[i].route_name)
	{
            if(!strcmp(adjacency_list[i].route_name, current_vertex))
	        match_current = 1;
	    else
	        ++i;
        }
	else                                
	    return 0;
    }
    while(j < list_size && !match_toattach)
    {
        if(adjacency_list[j].route_name)
        {
            if(!strcmp(adjacency_list[j].route_name, to_attach))
                match_toattach = 1;
	    else
		++ j;
        }
	else
            return 0;
    }

    if(match_current && match_toattach)                      //found both matching vertices
    {
	node * hold = adjacency_list[i].head;                //create a new node and connect with
	adjacency_list[i].head = new node;                   //the old nodes, and let the vertex
	adjacency_list[i].head->next = hold;                 //pointer in the node points to right
	adjacency_list[i].head->adjacent = adjacency_list+j; //element in the array
	return 1;
    }
    else                //return 0 if there's no matching vertices for either one
        return 0;
}

       

//This function takes a char pointer as an argument, it
//would display each choice we have at any given intersection.
//0 will be returned if the input is invalid or if there's no
//matching vertex in the array or if there's no choices for
//this input. 1 will be returned for success.
int table::display_adjacent(char * key_value)
{
    if(!key_value)   //make sure the input is valid
        return 0;
    
    int match = 0;
    int i = 0;
    while(i < list_size && !match)      //Iterate over the array and find the match
    {
        if(adjacency_list[i].route_name)
        {
            if(!strcmp(adjacency_list[i].route_name, key_value))
	        match = 1;
	}
	++ i;
    }

    -- i;                              //decrease i by one to move it to the correct position

    if(match)                          //if we found a match
    {
        if(!adjacency_list[i].head)    //if the edge list is empty
	    return 0;

	cout << "\n\n\nHere are the options for next choice to go:\n\n";
	
	node * current = adjacency_list[i].head;
	while(current)                 //display all data in the edge list
	{
	    cout << "\nName: " << current->adjacent->route_name << "\n\n";
	    current = current->next;
	}
	return 1;
    }
    else
        return 0;
}
