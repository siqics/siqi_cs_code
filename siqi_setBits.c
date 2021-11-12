#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//Siqi Wen CS201
//This program is a setBits program. It will accept a list of integers in the range
//0-15(inclusive) and turn on the corresponding bits in an unsigned short to output
//a result that shows set membership. If any integer is not in the correct range,
//an error message will be printed and the program will be aborted before displaying
//any results.


//Prototypes
int in_the_range(int argc, char* argv[], long number);
void setbits(int argc, char* argv[], long number);


int main(int argc, char* argv[])
{
    long number = 0;

    //call in_the_range function and assign the returned value to
    //the variable called yes_range
    int yes_range = in_the_range(argc, argv, number);

    //If all integers are within the range and there is any integer
    //on the command line
    if(yes_range && argc > 1)
    {
        setbits(argc, argv, number);
        printf("\n");
        
        exit(0);
    }
    else  //If there is no integer from command line or some integer is not in the range
    {
        printf("Error: Please enter integers between 0 and 15 (inclusive)!\n");
        exit(1);
    }
}


//This function takes three arguments and return an integer. It would check if there
//is any integer from command line out of the proper range, if there is, then zero
//will be returned, otherwise, one will be returned.
int in_the_range(int argc, char* argv[], long number)
{
    int in_range = 1; //a variable for checking if command line integers are in proper range
    char* endptr;     //the reference to an object of type char*

    //Iterate over the integer numbers from the command line
    for(int i = 1; in_range && i < argc; ++i)
    {
	//use strtoul() to read in the decimal numbers from command line
	//and store them one by one in this variable
        number = strtoul(argv[i], &endptr, 0);

        if(number < 0 || number > 15) //if any command line integer is not in the range
            in_range = 0;             //set this variable to zero
    }
    return in_range;
}


//This function takes three arguments and returns nothing. Based on the integers
//from command line, this function would turn on the corresponding bits in an
//unsigned short to output a result that shows set membership.
void setbits(int argc, char* argv[], long number)
{
    int temp;
    char* endptr;                  //the reference to an object of type char*
    for(int i = 15; i >= 0;  -- i) //to output the result from left to right
    {
        int match = 0;            //check if the bit number matches with any integer from command line
        int j = 1;                //index for integers on command line
        while(!match && j < argc)
        {
	    //use strtoul() to read in one decimal number from command line
            //and store it in this variable
            temp = strtoul(argv[j], &endptr, 0);

            if(temp == i)         //if bit number matches with an integer from command line
                match = 1;
            else                  //if not match
                ++ j;             //check next integer
        }
        if(match)
            printf("1");
        else                      //if there is no match between this bit number and any integer
            printf("0");
        if(i == 12 || i == 8 || i == 4)
            printf(" ");
    }  
}
