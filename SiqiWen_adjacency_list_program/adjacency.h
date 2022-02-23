#include <iostream>
#include <cctype>
#include <cstring>


//Siqi Wen CS163
//This file contains two structs: one is struct vertex which contains
//a char pointer for a vertex name and a head pointer for a node; another
//struct is node, which contains a pointer to a vertex and a next pointer.
//There is also a class table, which contains some member functions that
//allow us to insert a connection between two vertices and display each
//choice we have at any given intersection.



struct vertex
{
    char * route_name;    //info of a vertex
    struct node * head;   //a head pointer
};



struct node
{
    vertex * adjacent;    //a pointer to a vertex
    node * next;          //a next pointer
};



class table
{
    public:
        table(int size=5);          //constructor
	~table();                   //destructor

	int insert_vertex(char * one_vertex, int & full);

	//Insert a connection between two vertices
	int insert_edge(char * current_vertex, char * to_attach);

	//display each choice we have at any given intersection
        int display_adjacent(char * key_value);

    private:
        vertex * adjacency_list;   //a pointer to the adjacency list
	int list_size;            //size of the list
};



//Prototypes
void welcome();            //Output the welcome message.
bool again();              //Ask if the user wants to do again.
void menu(int & task);     //Show the user the menu.

