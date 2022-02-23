#include "queue_stack.h"
using namespace std;


//Siqi Wen CS163
//This file contains the implementations of member functions
//in stack class, which includes a constructor; a destructor;
//a function to push a queue at the top; a function to display
//every queue on the stack; a function to display just the data
//at the top of the stack; a function to remove the most recent
//queue from top. And the private data members are: a head pointer
//points to the first node_stack; an integer representing the index
//for top.


//Constructor - initialize the data members.
stack::stack()
{
    head = NULL;
    top_index = 0;
}


//Destructor - release all dynamically allocated memory.
stack::~stack()
{
    if(head)                           //make sure head is not NULL
    {
        node_stack * temp = head;      //Traverse over the list
	while(head)
	{
	    temp = head->next;
	    if(head->array)            //make sure the pointer is not NULL
	        delete [] head->array; //before deallocating the memory
	    delete head;
	    head = temp;
	}
	top_index = 0;                 //reset to zero
    }
}


//This function takes a queue object as an argument, it would call
//the copy function in queue.cpp and it would push a queue object
//onto the top of the stack.
int stack::push(queue & toadd)
{
    if(!head)                  //If the stack list is empty
    {
        head = new node_stack;
	head->next = NULL;
	head->array = new queue[MAX];
    }
    else if(top_index == MAX)  //If all arrays are full on the stack,
    {                          //create a new node on top of the stack and a
	top_index = 0;         //new array of size MAX, reset top_index to zero
	node_stack * hold = head;
	head = new node_stack;
	head->next = hold;
	head->array = new queue[MAX];
    }

    //This also works for when the array of the node on the top is not full.
    //call the copy function in queue.cpp with a specific array index
    if(!head->array[top_index].copy_a_queue(toadd))
        return 0;
    ++ top_index;
    return 1;
}


//This function takes a queue object as an argument, and it would call the
//remove_all function for that object from the queue class to release all
//dynamically allocated memories of that object so that we can use
//the object again like brand new. 
int stack::reset_q_ob(queue & q_ob)
{
    return q_ob.remove_all();
}


//This function takes no argument and it would display every queue
//on the stack. It would return 0 if there is no queue, otherwise,
//return the amount of queues.
int stack::display_allqueue()
{
    if(!head)                   //when there is nothing on the stack
        return 0;
    node_stack * temp_h = head; //points to the first node of stack(on the top)
    int amount = 0;
    amount = display_allq(head, temp_h, top_index);
    if(amount != 0)
        cout << "\n\n\nIn total, there is/are "
	     << amount << " trial(s).\n\n";
    return amount;
}


//This function takes two pointers and an integer as arguments, it would
//count the amount of queues on the stack and return the amount. Also,
//it would display all queues in the order from old to new.
int stack::display_allq(node_stack * hptr, node_stack * temp, int index)
{
    if(!hptr)
        return 0;
    int count = 0;
    int num = 0;
    count += display_allq(hptr->next, temp, index);
    if(hptr == temp)              //if it's the first node, then the limit is
        num = index;              //top_index;
    else                          //if it's other nodes, then the limit is
	num = MAX;                //MAX, because the array of these nodes
    for(int i = 0; i < num; ++i)  //would be full for sure
    {
        cout << "\n\nTrial #" << count+1 << ":\n";  //prints out the trial number
        if(hptr->array[i].display_allsteps())       //display all steps for each queue
	{
            ++ count;                               //add one to the number of queue
        }
    }
    return count;
}


//This function takes no argument and returns an integer for success
//or failure. It would display just the data at the top of the stack.
int stack::display_top()
{
    if(!head)       //if stack is empty
        return 0;

    cout << "\n\n\nThis is the data at the Top of the stack:\n\n";
    if(head->array[top_index-1].display_allsteps())
	return 1;
    return 0;
}


//This function takes a queue object as an argument, it would copy the most
//recent queue into the argument then it would remove the most recent
//queue from top. An integer will be returned for success or failure.
int stack::pop(queue & popped)
{
    if(!head)      //if the stack is empty
        return 0;

    //If the stack is not empty, then copy the most recent queue first
    if(popped.copy_a_queue(head->array[top_index-1]))
    {
        if(top_index > 1)  //if there's more than one queue in the array 
	{                  //of first node on stack
	    -- top_index;
	    if(head->array[top_index].remove_all())
	        return 1;
	}
	else if(top_index == 1)  //if there's only one queue in the array
	{                        //of first node on stack
	    -- top_index;
	    if(head->array[top_index].remove_all())
	    {
	        if(head->array)  //delete the dynamically allocated array
	            delete [] head->array;
		node_stack * hold = head->next;
		delete head;     //delete first node then connect with the next node
		head = hold;     //if there's any node left, or head would be NULL
		if(head)             //if there's node left, top_index should be MAX again
		    top_index = MAX;
		else                 //if there's no node left, top_index should be zero
		    top_index = 0;
		return 1;
	    }
	}
    }
    return 0;
}
