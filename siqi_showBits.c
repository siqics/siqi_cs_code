#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//Siqi Wen CS201
//This program is a showBits program. It would take arguments from command line,
//the arguments would be two hexadecimal 32-bit integers, the program would
//display which bits the two numbers both have set to 1. Moreover, it would
//print the bit numbers as well as the resulting number in hexadecimal, signed
//integer and unsigned integer formats. If the wrong number of arguments were
//entered, the program would output an error message and then terminate.


//Prototype
int showbits(char* argv[]);
void bit_numbers(int the_result);


int main(int argc, char* argv[])
{
    int result = 0;  //a variable to catch the returned value from showbits function
    if(argc == 3)    //only executes when the number of arguments is correct
    {
        result = showbits(argv);
        bit_numbers(result);
        printf(" Hexadecimal: %x, Signed: %d, Unsigned: %u.\n", result, result, result);

	exit(0);    //when the program runs as expected
    }
    else
    {
        printf("Error: please provide two hexadecimal numbers as arguments to the program.\n");

	exit(1);   //when something goes wrong
    }
}


//This function takes an argument. It would convert command
//line arguments to numbers and would return an integer which
//is the resulting number.
int showbits(char* argv[])
{
    int the_outcome;
    char* endptr;  //the reference to an object of type char*

    //use strtoul() to read in the hex numbers from command line
    //and store the first and second number into two variables
    long first = strtoul(argv[1], &endptr, 16);
    long second = strtoul(argv[2], &endptr, 16);

    //use the bitwise operator & to obtain the resulting number
    the_outcome = (first) & (second);

    return the_outcome;
}


//This function takes an integer as an argument and it would
//display which bits the resulting number has set to 1, which
//represent which bits the two numbers from the command line
//both have set to 1 .
void bit_numbers(int the_result)
{
    printf("Bits ");
    for(int i = 0; i < 32; ++i)
    {
	//use the bitwise operator & to compare each bit of the
	//resulting number with one and display the bit number
	//if that bit is 1 .
        if(the_result & (1 << i))
            printf("%d,", i);
    }
    printf(" in common.");
}
