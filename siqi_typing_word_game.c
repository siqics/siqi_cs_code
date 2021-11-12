#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>


//Siqi Wen CS201
//This program is a typing speed game program. It will randomly choose a word
//from a specific sentence, and the user has to type in the correct word. If
//the user types soemthing wrong, the program will keep prompting until the
//user types it right. When the user finishes typing all words, the program
//will display the time the user used.


//Prototypes.
int get_a_number(int amount_of_words, struct timeval tv);
void make_random_ar(int random_array[], int the_amount, struct timeval start_time);


int main(void)
{
    int amount = 9;             //Number of words in the sentence.
    int c;
    char word[11];              //Create an array to store user's input.
    struct timeval used_time;   //Create three objects of struct timeval.
    struct timeval start;
    struct timeval end;

    //Create an array literal of pointers to string literals.
    char *words[] = {"The", "quick", "brown", "fox", "jumps", "over", "the", "lazy", "dog"};
    int random_num_array[9] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    
    printf("\nThis is a game that tests typing speed\n\nType the following words:\n");

    //Call this function to shuffle the elements in the array of integers.
    make_random_ar(random_num_array, amount, start);

    gettimeofday(&start, NULL);           //Get the starting time.

    for(int j = 0; j < amount; ++j)       //Iterate over the array of integers.
    {                                     
        int index = random_num_array[j];  //Each element of the array of integers will be
        do                                //the index for the array of pointers.
        {
            printf("word #%i is %s: ", j+1, words[index]);
            scanf("%10s", word);                        //Reads in ten characters of input,
            while((c = getchar()) != '\n' && c != EOF); //then throws away the rest of the line.
        }while(strcmp(words[index], word));             //Keep prompting until user types right word.
    }

    gettimeofday(&end, NULL);            //Get the ending time when the user finishes.
    timersub(&end, &start, &used_time);  //Calculate the total time the user used.
    printf("You took %lu seconds and %ld microseconds\n", used_time.tv_sec, used_time.tv_usec);

    return 0;
}


//This function takes an interger and a struct object as arguments, it
//would return an integer which was chosen randomly within a range.
int get_a_number(int amount_of_words, struct timeval tv)
{
    int random_num;
    int temp = amount_of_words;

    gettimeofday(&tv, NULL);     //Seed srand() using the usec field from a call to
    srand(tv.tv_usec);           //gettimeofday() so that all permutations are possible.

    random_num = rand() % temp;  //Get a random number from a specific range.
    return random_num;
}


//This function takes an array of integers, an integer and a struct object as
//arguments, it will shuffle the elements in the array of integers.
void make_random_ar(int random_array[], int the_amount, struct timeval start_time)
{
    int a_num;
    int temp_hold;
    for(int i = 0; i < the_amount; ++i)        //Iterate over the array of integers.
    {
        a_num = get_a_number(the_amount, start_time);
        temp_hold = random_array[i];           //Use the random number that was returned from
        random_array[i] = random_array[a_num]; //get_a_number function as an index each round
        random_array[a_num] = temp_hold;       //to shuffle the elements in the array of integers.
    }
}
