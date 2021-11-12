#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>



//Siqi Wen CS201
//This program is an IEEE floating point parser for an arbitrary number of
//bit setting. It would take three arguments from the command line. The
//first argument is the number of fraction bits (n) between 2 and 10 to be
//used in the representation.  The second argument is the number of exponent
//bits (k) between 3 and 5 to be used in the representation. And the third
//argument is the hexadecimal representation of the number user wants to parse.



//Prototypes
int isolate_fra(unsigned int hex, unsigned int f_bits);
int isolate_ex(unsigned int hex, unsigned int ex_bits, unsigned int f_bits);
int isolate_sign(unsigned int hex, unsigned int ex_bits, unsigned int f_bits);
float get_fra(unsigned int iso_fra, unsigned int f_bits);
float get_exp(unsigned int iso_ex);
float get_ieee(float exp, float fraction, unsigned int ex_bits, unsigned int iso_sign, float bias);



int main(int argc, char * argv[])
{
    if(argc != 4)   //make sure right number of arguments are typed on command line
    {
        printf("Usage: fp_parse <# of frac_bits> <# of exp_bits>\n");
        exit(1);
    }

    
    unsigned int f_bits, ex_bits, hex = 0;
    unsigned int iso_fra, iso_ex, iso_sign = 0;
    #define INPUT_LEN 20
    float bias = 0.0;
    float fraction = 0.0;
    float exp = 0.0;
    float ieee = 0.0;
    

    if(sscanf(argv[1], "%d", &f_bits) != 1)   //read in the fraction bits
    {
        printf("failed to parse the fraction bits...\n");
        exit(1);
    }

    if(f_bits < 2 || f_bits > 10)             //make sure fraction bits is in right range
    {
        printf("Invalid number of fraction bits (%d). Should be between 2 and 10\n", f_bits);
        exit(1);
    }

    if(sscanf(argv[2], "%d", &ex_bits) != 1) //read in the exponent bits
    {
        printf("failed to parse the exponent bits...\n");
        exit(1);
    }

    if(ex_bits < 3 || ex_bits > 5)       //make sure exponent bits is in right range
    {
        printf("Invalid number of exponent bits (%d). Should be between 3 and 5\n", ex_bits);
        exit(1);
    }

    int i;
    for(i = 0; i < INPUT_LEN; ++i)      //make sure the third argument is a correct hex number
    {
        int character = argv[3][i];
        if(character == '\0')
        {
            break;
        }
        if(!isxdigit(character))
        {
            printf("Argument 3 is not a hexadecimal number (%s).\n", argv[3]);
            exit(1);
        }
    }
    if(i == INPUT_LEN && argv[3][i] != '\0')  //make sure hex number is not too long
    {
        printf("Recived too-long hex input...\n");
        exit(1);
    }

    if(sscanf(argv[3], "%x", &hex) != 1)     //read in the hex representation
    {
        printf("failed to parse the hexadecimal representation...\n");
        exit(1);
    }

    int bits = 1 + f_bits + ex_bits;         //use left shift operator and bitwise operator
    int hex_mask = (1 << bits) - 1;          //to make sure the hex number didn't exceed
    if((hex & hex_mask) != hex)              //maximum number of bits
    {
        printf("Number %x exceeds maximum number of bits. Only 7 allowed here.\n", hex);
        exit(1);
    }

    
    iso_fra = isolate_fra(hex, f_bits);
    iso_ex = isolate_ex(hex, ex_bits, f_bits);
    iso_sign = isolate_sign(hex, ex_bits, f_bits);

    fraction = get_fra(iso_fra, f_bits);
    exp = get_exp(iso_ex);

    bias = (pow(2, (ex_bits - 1))) - 1;

    ieee = get_ieee(exp, fraction, ex_bits, iso_sign, bias);

    printf("%f\n", ieee);                   //output the ieee which is a float number


    exit(0);
}



//This function takes two unsigned integers as arguments, and it would use
//left shift and right shift operators to isolate the fraction bits. And
//return the value.
int isolate_fra(unsigned int hex, unsigned int f_bits)
{
    unsigned int iso_fra = hex << (32 - f_bits) >> (32 - f_bits);
    return iso_fra;
}


//This function takes three unsigned integers as arguments, and it would use
//left shift and right shift operators to isolate the exponent bits. And
//return the value.
int isolate_ex(unsigned int hex, unsigned int ex_bits, unsigned int f_bits)
{
    unsigned int iso_ex = hex << (32 - (f_bits + ex_bits)) >> (32 - ex_bits);
    return iso_ex;
}


//This function takes three unsigned integers as arguments, and it would use
//right shift operators to isolate the sign bit. And return the value.
int isolate_sign(unsigned int hex, unsigned int ex_bits, unsigned int f_bits)
{
    unsigned int iso_sign = hex >> (f_bits + ex_bits);
    return iso_sign;
}


//This function takes two unsigned integers as arguments, it would use the
//isolated fraction bits to calculate the value of fraction. It would return
//a float number.
float get_fra(unsigned int iso_fra, unsigned int f_bits)
{
    unsigned int fr_mask = 0x80000000;
    float fraction = 0.0;
    float count = - 1.0;                  //This is the power value

    fr_mask >>= (32 - f_bits);            //use right shift operator to change fr_mask
    
    while(fr_mask >= 1)                   //while loop stops when fr_mask is less than 1
    {
        if(fr_mask & iso_fra)             //use bitwise and operator to check if that bit is 1
        {
            if(fraction == 0)             //Calculate fraction
                fraction = pow(2, count);
            else
                fraction += pow(2, count);
        }
        -- count;                          //decrement count which is the power
        fr_mask >>= 1;                     //use right shift operator to re-assign fr_mask
    }
    return fraction;
}


//This function takes an unsigned integer as an argument, and returns a float
//number. It would use the isolated exponent bits to calculate the exp.
float get_exp(unsigned int iso_ex)
{
    unsigned int ex_mask = 1;
    float exp = 0.0;
    float count = 0.0;

    while(ex_mask <= 16)              //while loop stops when fr_mask is bigger than 16
    {
        if(ex_mask & iso_ex)          //use bitwise and operator to check if that bit is 1
        {
            if(exp == 0)              //calculate exp
                exp = pow(2, count);
            else
                exp += pow(2, count);
        }
        ++ count;                     //Increment count which is the power
        ex_mask <<= 1;                //use left shift operator to re-assign ex_mask
    }
    return exp;
}


//This function takes three float numbers and two unsigned integers as arguments,
//it would return a float number which is the value for ieee. 
float get_ieee(float exp, float fraction, unsigned int ex_bits, unsigned int iso_sign, float bias)
{
    float ieee = 0.0;
    float M = 0.0;
    float E = 0.0;
    
    if(((1 << ex_bits) - 1) == exp)  //to check is exp is all 1's
    {
        if(fraction == 0)           
        {
            if(iso_sign)            //if fraction is zero and sign is 1
                printf("-inf\n");
            else                    //if fraction is zero and sign is 0
                printf("+inf\n");
            exit(0);
        }
        else                       //if fraction is not zero
        {
            printf("NaN\n");
            exit(0);
        }
    }
    else if(exp == 0)             //Denormalized
    {
        E = 1 - bias;
        M = fraction;
    }
    else                         //Normalized
    {
        E = exp - bias;
        M = 1 + fraction;
    }

    //Use the formula to calculate ieee floating point number
    ieee = pow(-1, iso_sign) * M * pow(2, E);

    return ieee;
}
