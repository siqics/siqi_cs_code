#include<iostream>
#include<cstring>
#include<cctype>


//Siqi Wen CS163
//This file contains two class interfaces and two structure definitions.
//A struct for node_queue which contains the information for a step of
//an activity and a next pointer; another struct for node_stack which
//contains a pointer points to a dynamically allocated array of queues
//and a next pointer points to another node_stack; a class interface for
//queue which contains member functions to enqueue and dequeue an activity's
//step; another class interface for stack which contains member functions
//to push or pop a queue from the top.


//Create a constant for the size of the array.
const int MAX = 5;


//This is a structure for node_queue, it includes four members: an integer
//represents the task number; a pointer points to a dynamically allocated
//array of characters that represents the description of the task; another
//pointer points to a dynamically allocated array of characters for the note
//in terms of how to improve; a next pointer to another node_queue.
struct node_queue
{
    int task_num;             //an integer for the task number
    char * plan;              //a pointer for the description of the task
    char * note;              //how to improve or what went wrong
    node_queue * next_queue;  //a next pointer to another node_queue
};
 

//This is a class interface for queue, it includes some member functions
//and a data member. These member functions can enqueue an activity's step
//to the rear of the CLL; dequeue an activity's step from front; display
//all steps in the CLL list; copy a queue, which will be needed for push.
class queue
{
    public:
	queue();              //Constructor - initialize the data members.
	~queue();             //Destructor - release all dynamically allocated memory.
        int remove_all();     //Delete all dynamically allocated memory for all data.
	//enqueue an activity's step to the rear
	int enqueue(int task, char * desc, char * a_note); 
	int dequeue();                 //dequeue an activity's step from front
	int display_allsteps() const;  //display the whole CLL list
	int copy_a_queue(queue & cll); //copy a queue, will be needed for push
    private:
        node_queue * rear;    //a tail/rear pointer points to the most recent queue object
	//copy the data that will be removed into the object
	int store_dequeued(node_queue & removed, int task, char * desc, char * a_note);
};


//This is a structure of node_stack, it includes a pointer points to a
//dynamically allocated array of queues and a next pointer points to
//another node_stack.
struct node_stack
{
    queue * array;      //a pointer points to a dynamically allocated array of queues
    node_stack * next;  //a next pointer points to another node_stack
};


//This is a class interface for stack, it includes some member functions and two
//data members: a head pointer points to the first node_stack and an integer for
//the index for top. These member functions can push a queue at the top; display
//every queue on the stack; display just the data at the top of the stack; remove
//the most recent queue from top.
class stack
{
    public:
        stack();                  //Constructor - initialize the data members.
	~stack();                 //Destructor - release all dynamically allocated memory.
	int push(queue & );       //Push a queue at the top.
	int reset_q_ob(queue & ); //reset the queue object to be reused
	int display_allqueue();   //Display every queue on the stack.
	int display_top();        //Display just the data at the top of the stack.
	int pop(queue & );        //Remove the most recent queue from top.
    private:
        node_stack * head;        //points to the first node_stack
	int top_index;            //the index for top
	//display all queues in the order from old to new
        int display_allq(node_stack * hptr, node_stack * temp, int index);
};


//Prototypes
void welcome();            //Output the welcome message.
bool again();              //Ask if the user wants to do again.
void menu(int & task);     //Show the user the menu.
