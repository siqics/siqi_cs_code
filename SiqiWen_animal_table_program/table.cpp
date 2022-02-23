#include "table.h"
using namespace std;



//Siqi Wen CS163
//This file contains the implementations of member functions
//in the table class. We are using two data structures: a
//hash table using chaining and a BST. These functions will
//insert new animals into both hash table and BST; display
//all matches of a particular type and breed by using the
//hash table; look for a particular animal by using the BST
//for retrieval; display all animals in sorted order by using
//BST; remove an animal from both data structures.


/*

        node_chain ** hash_table;
	int ht_size;
	node_BST * root;
*/



//Constructor - initialize the data members.
table::table(int size)
{
    //Allocate the hash table and initialize each
    //element and data member.
    hash_table = new node_chain* [size];
    for(int i = 0; i < size; ++i)
        hash_table[i] = NULL;
    ht_size = size;

    root = NULL;
}



//Destructor - release all dynamically allocated memory.
table::~table()
{
    remove_all_in_ht();
    remove_all_in_BST();
}



//This function takes no arguments and will return 1 for success.
//It will remove all animal info in the hash table.
int table::remove_all_in_ht()
{
    for(int i = 0; i < ht_size; ++i) //Iterate over the hash table (array).
    {
        if(hash_table[i])            //If the head pointer is not NULL.
	{
	    node_chain * current = hash_table[i];
	    while(current)           //Iterate over the LLL
	    {
	        if(current->info_h)  //if the pointer to an animal class is not NULL
		{                    //call the remove funtion and set it to NULL
		    current->info_h->remove_all_info();
		    current->info_h = NULL;
		}
		current = current->next;
	    }
	}
    }
    return 1;
}



//This function takes no argument and would return an integer
//which is the returned value from the recursive call for success
//or failure. It would remove all animal info in the BST.
int table::remove_all_in_BST()
{
    return remove_all_BST(root);
}



//This function takes a pointer to node_BST as an argument and it's
//passed by reference. An integer will be returned for success or
//failure. It would remove all animal info in the BST.
int table::remove_all_BST(node_BST * & root)
{
    if(!root)      //Empty tree or finished traversing
        return 0;
    if(!root->left && !root->right)  //if it's a leaf
    {
	if(root->info_b)             //if the animal pointer is not NULL
	{
	    root->info_b->remove_all_info();
	    root->info_b = NULL;
	}
	delete root;                 //delete this node_BST
	root = NULL;
	return 1;                    //return 1 if a leaf's info was removed
    }
    return remove_all_BST(root->left) + remove_all_BST(root->right);
}



//This function takes an animal pointer as an argument and it
//would return an integer as the index for the hash table. It
//would call another hash function from animal class.
int table::hash_function(animal * toadd) const
{
    return toadd->hash_function(ht_size); 
}



//This function takes an animal pointer as an argument and it
//would call the insert functions for both hash table and BST.
//An integer will be returned for success or failure.
int table::insert_both(animal * toadd)
{
    if(insert_hash(toadd) && insert_BST(toadd))
        return 1;
    return 0;
}



//This function takes an animal pointer as an argument, it
//would insert an animal info into the hash function. An
//integer will be returned for success or failure. It would
//call the hash function and use the returned value as the
//index from the hash function when inserting.
int table::insert_hash(animal * toadd)
{
    if(!toadd)     //If the animal pointer is NULL
        return 0;

    int index = hash_function(toadd);  //catch the returned value

    if(!hash_table[index])             //Means there is no collision in this spot
    {
        hash_table[index] = new node_chain;
	hash_table[index]->info_h = toadd;
	hash_table[index]->next = NULL;
    }
    else                               //Means this is a collision happening
    {
	node_chain * hold = hash_table[index];  //Traverse to the right spot then
	hash_table[index] = new node_chain;     //insert the node.
	hash_table[index]->info_h = toadd;
	hash_table[index]->next = hold;
    }

    return 1;
}
 


//This function takes an animal pointer as an argument, and it would
//return 0 for failure, 1 for success. It would call another function,
//which is a recursive function, to insert a new node into the BST.
int table::insert_BST(animal * toadd)
{
    if(!toadd)     //If the animal pointer is NULL
        return 0;
    
    return insert_BST_recursion(root, toadd);
}



//This function is a recursion function, it takes a node_BST pointer
//(passed by reference) and an animal pointer as arguments, 1 will
//be returned for success. It would insert a new animal info into
//the right spot.
int table::insert_BST_recursion(node_BST * & root, animal * toadd)
{
    if(!root)          //Always adding as a leaf.
    {
        root = new node_BST;
        root->info_b = toadd;
        root->left = NULL;
        root->right = NULL;

        return 1;
    }

    if(root->info_b->compare_breeds(toadd) < 0)         //Compare the breeds first, then the
        return insert_BST_recursion(root->left, toadd); //names. If the new data is alphabetically
    if(root->info_b->compare_breeds(toadd) == 0)        //smaller, then it should go to the left, 
    {                                                   //otherwise, it should go to the right.
        if(root->info_b->compare_names(toadd) < 0)
            return insert_BST_recursion(root->left, toadd);
	else
	    return insert_BST_recursion(root->right, toadd);
    }
    else
	return insert_BST_recursion(root->right, toadd);
}
        


//This function takes two pointers as arguments, and it would return
//an integer for success or failure. It would display matches with
//hashtable based on the type and breed.
int table::display_matches_hash(char * a_ty, char * a_br)
{
    if(!a_ty || !a_br)                        //if the input is invalid
        return 0;

    int ind = 0;

    ind = hash_function_char(a_ty, a_br);     //calculate the index with hash function

    if(!hash_table[ind])                      //If the head pointer(this element) is NULL
        return 0;

    int match = 0;                            //Otherwise, iterate over the LLL of this
    node_chain * current = hash_table[ind];   //element, and display all matches. If there's
                                              //no matches, zero will be returned.
    while(current)
    {
        if(current->info_h->if_match(a_ty, a_br))
	{
	    match = 1;
	    current->info_h->display_one_animal();
	}
 
	current = current->next;
    }

    return match;
}
        


//This function looks for a particular animal based on their
//breed and name, and it would supply the matching information
//back to the calling routine through the argument list. An
//integer will be returned for success or failure.
int table::retrieve_BST(char * a_br, char * a_na, animal * & found)
{
    if(!a_br || !a_na)
	return 0;

    if(!root)
        return 0;
    return retrieve_BST(root, a_br, a_na, found);
}
       


//This function is a recursive function, it will be called in another
//function and it would supply the matching information back to the
//calling routine through the argument list. An integer will be
//returned for success or failure.
int table::retrieve_BST(node_BST * & root, char * a_br, char * a_na, animal * & found)
{
    if(!root)
        return 0;

    if(root->info_b)                                  //If the breeds and names both match,
    {                                                 //let found points to this data.
        if(root->info_b->if_match_br_na(a_br, a_na))
        {
            found = root->info_b;
	    return 1;
        }
    }

    if(root->info_b->compare_brs(a_br) < 0)                  //Compare the alphabetic orders for
        return retrieve_BST(root->left, a_br, a_na, found);  //breeds and names, if what we are
    if(root->info_b->compare_brs(a_br) == 0)                 //looking for is smaller, go to left,
    {                                                        //otherwise, go to right.
	if(root->info_b->compare_nas(a_na) < 0)
            return retrieve_BST(root->left, a_br, a_na, found);
	else
	    return retrieve_BST(root->right, a_br, a_na, found);
    }
    else
        return retrieve_BST(root->right, a_br, a_na, found);
}



//This function takes no argument and return 0 if it's an empty
//tree, 1 if it's not. It will display all animals in sorted
//order by their breed and name.
int table::display_all()
{
    if(!root)
        return 0;
    return display_all(root);
}



//This function is a recursive function. It takes a node_BST pointer
//as an argument and return 0 if it's an empty tree, 1 if it's not.
//It will display all animals in sorted order by their breed and name.
int table::display_all(node_BST * & root)
{
    if(!root)
        return 0;

    display_all(root->left);                 //Go all the way to the left, display data,
    if(root->info_b)                         //then go to the right. This is in-order
        root->info_b->display_one_animal();  //traversal.
    display_all(root->right);
    return 1;
}



//This function takes three char pointers as arguments, it would
//return 1 if we successfully removed the item in both data structure,
//otherwise, 0 will be returned.
int table::remove_one(char * ty, char * br, char * na)
{
    if(!ty || !br || !na)
        return 0;
    
    if(remove_fromhash(ty, br) && remove_fromBST(br, na))
	return 1;
    return 0;
}



//This function takes two char pointers as arguments, it would
//calculate the index for the hash table and return the index.
int table::hash_function_char(char * ty, char * br)
{
    int len_ty = strlen(ty);
    int len_br = strlen(br);

    int result = 0;
    int index = 0;
    int len = 0;
    if(len_ty < len_br)                //use the shorter length
        len = len_ty;
    else
	len = len_br;

    for(int i = 0; i < len_ty; ++i)    //turn every character in the array
        ty[i] = tolower(ty[i]);        //into lowercase
    for(int j = 0; j < len_br; ++j)
	br[j] = tolower(br[j]);

    for(int k = 0; k < len; ++k)       //This math operation adds up the ASCII values of
    {                                  //all characters in the range of the shorter length
        result += ty[k] + br[k];       //from the two lengths of the arrays of characters.
    }
    index = result % ht_size;          //use the mod operator to get a number
    return index;
}



//This function takes two char pointers as arguments, it would remove
//the node that contains the target data without delete the target data,
//because we still need to use that data to find the match in BST. 0 or 1
//will be returned for failure or success.
int table::remove_fromhash(char * ty, char * br)
{
    if(!ty || !br)
        return 0;

    int ind = 0;
    ind = hash_function_char(ty, br);         //calculate the index with hash function

    if(!hash_table[ind])                      //If the head pointer(this element) is NULL
        return 0;
    if(!hash_table[ind]->next)                //if there is only one node in that index
    {                                         //delete the node if it's a match
        if(hash_table[ind]->info_h->if_match(ty, br))
        {
	    delete hash_table[ind];
	    hash_table[ind] = NULL;
	    return 1;
	}
	else
	    return 0;
    }


    int match = 0;                             //Otherwise, iterate over the LLL of this
    node_chain * previous = hash_table[ind];   //element to find the match.
    node_chain * current = hash_table[ind]->next;
    
    while(current && !match)
    {
        if(current->info_h->if_match(ty, br))
	    match = 1;                         //Change match to 1
	else
        {
	    previous = current;                //Traverse till we find the match
	    current = current->next;
	}
    }
    if(match == 1)                             //means we found a match, then we
    {                                          //need to delete the node that contains
	node_chain * hold = current->next;     //the data without deleting the data
	delete current;
	previous->next = hold;
	return 1;
    }
    return 0;
}



//This function takes two char pointers as arguments, it would call
//another recrusive function to delete the target data and matching
//node, 0 will be returned if the BST is empty, then 0 or 1 will be
//returned from the recursive function.
int table::remove_fromBST(char * br, char * na)
{
    if(!root)
        return 0;
    return remove_fromBST(root, br, na);
}



//This function takes a node_BST pointer and two char pointers as
//arguments, it would look for a match in BST, if there's a match,
//delete the target data and delete the node, and 1 will be returned,
//if there's no match, 0 will be returned.
int table::remove_fromBST(node_BST * & root, char * br, char * na)
{
    if(!root)
        return 0;

    if(root->info_b)
    {
        //check if the breeds and names both match
        if(root->info_b->if_match_br_na(br, na))
        {
            root->info_b->remove_all_info();     //delete the target data if it's a match
	    root->info_b = NULL;

            if(!root->left && !root->right)      //If it's a leaf
       	    {
	        delete root;
	        root = NULL;
	    } 

	    else if(root->left && !root->right)  //If it has a left child
	    {
	        node_BST * hold = root->left;
                delete root;
	        root = hold;
	    }

	    else if(!root->left && root->right)  //If the match has a right child
	    {
	        node_BST * hold = root->right;
                delete root;
                root = hold;
	    }
	    else                                     //If the match has two children
	    {
	        node_BST * current = root->right;
	        if(!current->left)                   //then we need to find the IOS and
	        {                                    //replace the matching node's data
	            root->info_b = current->info_b;  //with IOS
		    node_BST * hold = current->right;
		    delete current;
                    root->right = hold;
	        }
	        else
	        {
	            node_BST * parent = current;
		    while(current->left)
		    {
		        parent = current;
		        current = current->left;
		    }
		    node_BST * hold = current->right;
		    root->info_b = current->info_b;
		    delete current;
		    parent->left = hold;
	        }
	    }   
            return 1;
        }

        if(root->info_b->compare_brs(br) < 0)                  //Compare the alphabetic orders for
            return remove_fromBST(root->left, br, na);         //breeds and names, if what we are
        if(root->info_b->compare_brs(br) == 0)                 //looking for is smaller, go to left,
        {                                                      //otherwise, go to right.
            if(root->info_b->compare_nas(na) < 0)
                return remove_fromBST(root->left, br, na);
            else
                return remove_fromBST(root->right, br, na);
        }
        else
            return remove_fromBST(root->right, br, na);
    }
    return 0;
}
