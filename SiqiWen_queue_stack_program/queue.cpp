#include "queue_stack.h"
using namespace std;


//Siqi Wen CS163
//This file contains the implementations of the member functions
//in class queue, which includes a constructor, a destructor, a
//function to enqueue an activity's step to the rear; a function
//to dequeue an activity's step from front; a function to display
//the whole CLL list for all steps; a function to copy a queue.
//And the private data member is a tail/rear pointer points to
//the most recent queue object.


//Constructor - initialize the data members.
queue::queue()
{
    rear = NULL;
}


//Destructor - release all dynamically allocated memory.
queue::~queue()
{
    remove_all();
}    


//This function takes no argument and it would delete all dynamically
//allocated memories for data, and return an integer for success or
//failure.
int queue::remove_all()
{
    if(rear)    //make sure rear is not NULL
    {
        node_queue * current = rear->next_queue;  //Break this CLL into a LLL,
        rear->next_queue = NULL;                  //then traverse and deallocate
        while(current)                            //all memory.
	{
	    rear = current->next_queue;
            current->task_num = 0;
            if(current->plan)
	        delete [] current->plan;
            if(current->note)
	        delete [] current->note;
            delete current;
            current = rear;
        }
	return 1;
    }
    return 0;
}


//This function takes an integer and two pointers as arguments, it would
//enqueue an activity's step to the rear, and return one for success and
//zero for failure.
int queue::enqueue(int task, char * desc, char * a_note)
{
    if(!desc || !a_note)        //when user's input is invalid
        return 0;
    if(!rear)                   //when it's an empty list, just enqueue one
    {                           //to the rear and set the next pointer point
        rear = new node_queue;  //to the node itself.
	rear->next_queue = rear;
    }
    else                       //when the list is not empty, enqueue one to the
    {                          //rear and set the new node's next pointer point
        node_queue * temp = rear->next_queue;              //to the oldest node.
	rear->next_queue = new node_queue;
	rear = rear->next_queue;
	rear->next_queue = temp;
    }
    rear->task_num = task;                 //Copy user's inputs into the new node
    rear->plan = new char[strlen(desc)+1]; //that was enqueued to the rear.
    strcpy(rear->plan, desc);
    rear->note = new char[strlen(a_note)+1];
    strcpy(rear->note, a_note);
    return 1;                              //Return one for success.
}


//This function takes a node_queue object, an integer, two char pointers as arguments.
//It would copy the data that will be removed into the object, and it would return one
//for success, zero for failure.
int queue::store_dequeued(node_queue & removed, int task, char * desc, char * a_note)
{
    if(!desc || !a_note)      //if the information to be copied is invalid
        return 0;
    if(removed.plan)          //if the pointers already point to some data
	delete [] removed.plan;
    if(removed.note)          //deallocate before assigning to avoid memory leak
	delete [] removed.note;

    removed.task_num = task;  //copy the data into the data members of this object
    removed.plan = new char[strlen(desc) + 1];
    strcpy(removed.plan, desc);
    removed.note = new char[strlen(a_note) + 1];
    strcpy(removed.note, a_note);
    removed.next_queue = NULL;
    cout << "\n\nCongrats!\nThe deleted step info is:\n"
	 << "\nStep " << removed.task_num
	 << "\nDescription: " << removed.plan
	 << "\nNote: " << removed.note << "\n\n\n";
    return 1;
}


//This function takes no argument, the purpose of this function is to
//dequeue an activity's step from front, it would return an integer
//for success or failure.
int queue::dequeue()
{
    if(!rear)                    //empty list
        return 0;
    node_queue a_removed;        //create a node_queue object
    if(rear == rear->next_queue) //only one item in the list
    {
	if(store_dequeued(a_removed, rear->task_num, rear->plan, rear->note))
	{                        //call this function to store the data before deleting
            rear->task_num = 0;
            if(rear->plan)
	        delete [] rear->plan;
	    if(rear->note)
	        delete [] rear->note;
	    delete rear;
	    rear = NULL;
	    return 1;
	}
	else
            return 0;
    }
    else                         //more than one item in the list
    {
	if(store_dequeued(a_removed, rear->next_queue->task_num, rear->next_queue->plan, rear->next_queue->note))
	{
            node_queue * temp = rear->next_queue->next_queue;
	    rear->next_queue->task_num = 0;
	    if(rear->next_queue->plan)
	        delete [] rear->next_queue->plan;
	    if(rear->next_queue->note)
	        delete [] rear->next_queue->note;
	    delete rear->next_queue;
	    rear->next_queue = temp;
	    return 1;
	}
	else
	    return 0;
    }
}


//This function takes no argument and it would display all the steps
//in the whole CLL list, it would return zero for failure, one for
//success.
int queue::display_allsteps() const
{
    if(!rear)                    //empty list
        return 0;
    if(rear == rear->next_queue) //only one item to display
    {
        cout << "\nStep " << rear->task_num
	     << "\nDescription: " << rear->plan
	     << "\nNote: " << rear->note << "\n\n";
    }
    else                         //more than one item to display
    {
        node_queue * current = rear->next_queue;
	while(current != rear)
	{
	    cout << "\nStep " << current->task_num
                 << "\nDescription: " << current->plan
                 << "\nNote: " << current->note << "\n\n";
	    current = current->next_queue;
	}                       //this stops at the last node
	cout << "\nStep " << rear->task_num
             << "\nDescription: " << rear->plan
             << "\nNote: " << rear->note << "\n\n";
    }
    return 1;
}


//This function takes a queue object as an argument, it would copy
//a queue(a CLL), and it will be needed for the push function in
//stack.cpp, an integer will be returned in this function for success
//or failure.
int queue::copy_a_queue(queue & cll)
{       
    if(!cll.rear)                         //when there is nothing to be copied
        return 0;
    if(cll.rear == cll.rear->next_queue)  //when there is only one item in the CLL
    {   
        rear = new node_queue;            //create one new node, and make the next
        rear->next_queue = rear;          //pointer points to itself
        rear->task_num = cll.rear->task_num;
        rear->plan = new char[strlen(cll.rear->plan) + 1];
        strcpy(rear->plan, cll.rear->plan);
        rear->note = new char[strlen(cll.rear->note) + 1];
        strcpy(rear->note, cll.rear->note);
    }
    else  //when there's more than one item in the CLL
    {
        node_queue * current = cll.rear->next_queue; //Iterate over the CLL and
        node_queue * t_front = NULL;                 //copy the data in each item
        rear = new node_queue;                       //while creating new nodes for
        t_front = rear;                              //the queue object which was
        while(current != cll.rear)                   //passed in as an argument.
        {
            rear->task_num = current->task_num;
            rear->plan = new char[strlen(current->plan) + 1];
            strcpy(rear->plan, current->plan);
            rear->note = new char[strlen(current->note) + 1];
            strcpy(rear->note, current->note);
            rear->next_queue = new node_queue;
            rear = rear->next_queue;
            current = current->next_queue;
        }                                        //this stops at the last node which
        rear->task_num = current->task_num;      //is pointed to by the rear pointer
        rear->plan = new char[strlen(current->plan) + 1];
        strcpy(rear->plan, current->plan);
        rear->note = new char[strlen(current->note) + 1];
        strcpy(rear->note, current->note);
        rear->next_queue = t_front;              //set the next pointer of the last node
    }                                            //point to the oldest node to form a CLL
    return 1;
}

