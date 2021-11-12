#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>



//Siqi Wen CS201
//This program will take from 2 arguments up to 15 arguments,
//inclusive. This argument count does not include the name of
//the executable. The operations to be performed on those
//arguments will be based on the menu, which includes exit,
//addition, subtraction, multiplication, division, modulo
//and reverse.




//Prototypes
void ex(int array[], char * argv[], int argc);
void addition(int array[], char * argv[], int argc);
void subtraction(int array[], char * argv[], int argc);
void multiplication(int array[], char * argv[], int argc);
void division(int array[], char * argv[], int argc);
void modulo(int array[], char * argv[], int argc);
void reverse(int array[], char * argv[], int argc);




int main(int argc, char * argv[])
{
    if(argc < 3 || argc > 16)        //make sure the number of arguements is in the right range
    {
        printf("\nThe number of arguments has to be between 2 to 15, inclusive.\n");
        exit(1);
    }

    int array[argc - 1];             //create an int array to store the numbers from command line

    int p_hex = 0;
    for(int i = 1; i < argc; ++i)    //iterate over the command line
    {
        p_hex = strtol(argv[i], NULL, 0);  //converts a string to a long integer
        array[i - 1] = p_hex;              //store the integer into the int array
    }

    //create an array of function pointers, and then call them through indexing the array
    void (*functions[])(int[], char*[], int) = {ex, addition, subtraction, multiplication, division, modulo, reverse};
    int answer = 1;

    while(answer)                     //only executes when answer is not 0
    {
        printf("0. Exit\n1. Addition\n2. Subtraction\n3. Multiplication\n4. Division\n5. Modulo\n6. Reverse Input\n\nMenu Item: ");
        scanf("%d", &answer);         //read in the answer and store it into the variable
        printf("\n");

        if(answer < 0 || answer > 6)  //check if the answer is in the right range
            printf("Invalid selection. Try again.\n");
        else                          //if it's in right range, call the corresponding function
            (*functions[answer])(array, argv, argc);
        printf("\n");
    }

    exit(0);
}



//This function is an exit function, it will simply display a new line.
void ex(int array[], char * argv[], int argc)
{
    printf("\n");
}



//This function takes three arguments and it would add all the numbers
//from the command line and output the result in both decimal version
//and hex version after displaying all numbers in decimal version and
//hex version.
void addition(int array[], char * argv[], int argc)
{
    int sum = array[0];
    printf("%d", array[0]);          //display the first number in decimal version

    for(int i = 1; i < argc-1; ++i)  //iterate over the whole int array and calculate the sum
    {
        printf(" + %d", array[i]);
        sum += array[i];
    }
    printf(" = %d", sum);           //display the result in decimal version

    printf("\n0x%x", array[0]);     //display the first number in hex version

    for(int i = 1; i < argc-1; ++i)
    {
        printf(" + 0x%x", array[i]);
    }
    printf(" = 0x%x", sum);
}



//This function takes three arguments and it would calculate the
//difference of all the numbers from the command line and output
//the result in both decimal version and hex version after
//displaying all numbers in decimal version and hex version.
void subtraction(int array[], char * argv[], int argc)
{
    int diff = array[0];
    printf("%d", array[0]);           //display the first number in decimal version

    for(int i = 1; i < argc-1; ++i)   //iterate over the whole int array and calculate the difference
    {
        printf(" - %d", array[i]);
        diff -= array[i];
    }
    printf(" = %d", diff);            //display the result in decimal version

    printf("\n0x%x", array[0]);       //display the first number in hex version

    for(int i = 1; i < argc-1; ++i)
    {
        printf(" - 0x%x", array[i]);
    }
    printf(" = 0x%x", diff);
}



//This function takes three arguments and it would calculate the
//product of all the numbers from the command line and output
//the result in both decimal version and hex version after
//displaying all numbers in decimal version and hex version.
void multiplication(int array[], char * argv[], int argc)
{
    int product = array[0];
    printf("%d", array[0]);

    for(int i = 1; i < argc-1; ++i)   //iterate over the whole int array and calculate the product
    {
        printf(" * %d", array[i]);
        product *= array[i];
    }
    printf(" = %d", product);

    printf("\n0x%x", array[0]);

    for(int i = 1; i < argc-1; ++i)
    {
        printf(" * 0x%x", array[i]);
    }
    printf(" = 0x%x", product);
}



//This function takes three arguments, it will only process
//the first two numbers on the command line. The result will
//be the first number divided by the second number. Also,
//the result will be a floating point number.
void division(int array[], char * argv[], int argc)
{
    float result = (float)array[0] / (float)array[1];
    printf("%d / %d = %f\n", array[0], array[1], result);
}



//This function takes three arguments, it will only process
//the first two numbers on the command line. The result will
//be the first number modulo (%) by the second number. The
//result will be an integer.
void modulo(int array[], char * argv[], int argc)
{
    int result = array[0] % array[1];
    printf("%d mod %d = %d\n", array[0], array[1], result);
}



//This function takes three arguments, it will print out
//the command line arguments in reverse.
void reverse(int array[], char * argv[], int argc)
{
    int len = 0;
    char * str;
    for(int i = argc; i > 1; -- i)      //Iterate over the command lines from back to front
    {
        str = argv[i-1];                //This is the last number on command line
        len = strlen(str);              //calculate the len of this string which is also a number
        for(int j = len; j > 0; -- j)   //Iterate over the string from back to front
        {
            printf("%c", str[j-1]);     //display the number in reverse
        }
        printf(" ");
    }
    printf("\n");
}


