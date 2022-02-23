#include <iostream>
#include <cctype>
#include <cstring>
#include <fstream>



//Siqi Wen CS163
//This file contains a class animal which contains some memeber functions
//(that will remove all info for one animal; create an animal with user's
//input; copy an animal's info and store the info in the argument so that
//it can be used later; display one animal's info; display info of animals
//that match with a specific type and breed; retrieve an animal with user's
//input for a breed and a name), and six data members represents an animal's
//info. Another class is table, it has some member functions that will use
//some meber functions from class animal and complete the missions, it also
//has three data members. There are also two structures, one for node_chain,
//one for BST.



class animal
{
    public:
        animal();     //Constructor - initialize the data members.
	~animal();    //Destructor - release all dynamically allocated memory.
	int remove_all_info();          //Remove all info for an animal

        int save_file(char filename[]); //To save data into a file

	//Create an animal with user's input
	int create_animal(char * t, char * b, char * n, char * r, int a, char * d);

	int hash_function(int si);      //Calculate an index for hash table
	
	int compare_breeds(animal * toadd);  //compare breeds
	int compare_brs(char * br);
	int compare_names(animal * toadd);   //compare names
	int compare_nas(char * na);
	int copy_type_breed(char * ty, char * br);     //copy type and breed
	int display_one_animal() const;                //Display one animal's info
	
	int if_match(char * a_type, char * a_breed) const;       //Check if types and breeds match
	int if_match_br_na(char * a_breed, char * a_name) const; //check if breeds and names match
    private:
        char * type;
        char * breed;
        char * name;
        char * require;
        int age;
        char * desc;
};


struct node_chain
{
    animal * info_h;    //a pointer to animal
    node_chain * next;  //a next pointer
};



struct node_BST
{
    animal * info_b;    //a pointer to animal
    node_BST * left;    //a left pointer
    node_BST * right;   //a right pointer
};



class table
{
    public:
        table(int size = 5);  //Constructor - initialize the data members.
	~table();             //Destructor - release all dynamically allocated memory.
	int remove_all_in_ht();  //remove all items in hash table
	int remove_all_in_BST(); //remove all items in BST

	int hash_function(animal * toadd) const;  //calculate the index for hash table
	int insert_both(animal * toadd);          //insert info into both data structures
	int insert_hash(animal * toadd);          //Insert an animal in hash table
	int insert_BST(animal * toadd);           //insert an animal in BST

	int display_matches_hash(char * a_ty, char * a_br);//display matches with hashtable
	int retrieve_BST(char * a_br, char * a_na, animal * & found);//look for a match
	int display_all();                        //display all animal in sorted order
	int hash_function_char(char * ty, char * br);
	int remove_one(char *, char *, char *);//remove one animal in both data structures


    private:
        node_chain ** hash_table;    //a pointer to an array of pointers to node_chain
	int ht_size;                 //size of the hash table array
	node_BST * root;             //a pointer to BST node


	int insert_BST_recursion(node_BST * & root, animal * toadd); //recursive function to insert
	int remove_all_BST(node_BST * & root);    //recursive function to remove all in BST
	int remove_fromhash(char * ty, char * br);//private function to remove from hash table
	int remove_fromBST(char * br, char * na); //private function to remove from BST
	int remove_fromBST(node_BST * & root, char * br, char * na);

	//recursive function to retrieve an item in BST
	int retrieve_BST(node_BST * & root, char * a_br, char * a_na, animal * & found);

	int display_all(node_BST * & root);       //recursive function to display in sorted order
};


//Prototypes
void welcome();            //Output the welcome message.
bool again();              //Ask if the user wants to do again. 
void menu(int & task);     //Show the user the menu. 

//This function is to load information from a file.
int load(char filename[], char * t, char * b, char * n, char * r, int a, char * d, animal * add, table & list);

