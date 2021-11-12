#include<iostream>
#include<cctype>
#include<cstring>
using namespace std;

//Siqi Wen CS162
//This program allows the user to set up three words for shorthand substitution.
//The user can type in those shorthand notations while writing notes, the program
//will then replace those notations with the actual words. If the short hand notation
//is capitalized, then the actual word would be capitalized; if it starts with a lower
//case letter, then the actual word would not be capitalized. 

const int WORD = 31;        //Set the size of the array for the word with a constant.
const int ABBR = 11;       //Set the size of the array for the abbreviation with a constant.
const int SENC = 201;     //Set the size of the array for the sentence with a constant.

//Prototypes,declaring to the compiler that these functions exist
void welcome();                  //Display the welcome information about how the program works.
void setup_word(char word[]);    //This function will prompt the user for an array and read it in.
void setup_abbr(char abbr[]);    //This function will prompt the user for an array and read it in.
void read_sentence(char senc[]); //This function will prompt the user for a sentence and read it in.
bool again();                    //Ask the user for an input and decide whether to return true or false.       
void convert(char abbr[], char temp[]); //This funtion converts first array into uppercase.
void output(char chk[], char wd[]);    //Analyzes an array and output the right version of actual word. 
//This function takes 7 arrays as arguments and replace all the shorthand with actual words.
void replace(char senc[], char ab1[], char wd1[], char ab2[], char wd2[], char ab3[], char wd3[]);


int main()
{
     //Local variables
     char word1[WORD];    //This variable is for storing the array for the first word.
     char word2[WORD];    //This variable is for storing the array for the second word.
     char word3[WORD];    //This variable is for storing the array for the third word. 
     char abbr1[ABBR];    //This variable is for storing the array for the first abbreviation.
     char abbr2[ABBR];    //This variable is for storing the array for the second abbreviation.
     char abbr3[ABBR];    //This variable is for storing the array for the third abbreviation.
     char sentence[SENC]; //This variable is for storing the array for the sentence.

     do
     {
         welcome();        //Call the welcome function

         do
         {
	     //Fill up the array from a function
             setup_word(word1);
	     setup_abbr(abbr1);
	     setup_word(word2);
	     setup_abbr(abbr2);
	     setup_word(word3);
	     setup_abbr(abbr3);

	     cout << "\n\n\n\n";  //new lines
	 
	     //Output the words and abbreviations the user has set up
	     cout << "These are what you’ve set up: \n\n\n" << abbr1 << " stands"
	          << " for " << word1 << "\n\n" << abbr2 << " stands for "
	          << word2 << "\n\n" << abbr3 << " stands for " << word3 << "\n\n";

         }while(again()); //Call the again function, the loop will continue if true is returned.

         do
         {
	     //Fill up the array for the sentence from a function
             read_sentence(sentence);

	     cout << "\n\n"; //new lines

	     //Output the sentence the user entered
	     cout << "The sentence you entered is: \n\n" << sentence << "\n\n";

         }while(again()); //Call the again function, the loop will continue if true is returned. 
         
         replace(sentence, abbr1, word1, abbr2, word2, abbr3, word3);

         cout << "\n\nPlease enter Y/y if you want to use this program again; "
	      << "enter N/n if you want to leave this program.";  //Guidance of what to enter

     }while(again());    //The loop will continue if true is returned.

     cout << "\n\n\n\nThank you for using our program! Have a great day!"; //ending message
     cout << "\n\n\n\n\n";    //new lines

     return 0;
}	

//The welcome function will output messages to the user about how the program works.
//It takes no arguments and returns nothing.
void welcome()
{
     cout << "\n\n\nWelcome to the shorthand notation program.\n\n\n"
	  << "You'll need to set up three words with corresponding abbreviations"
	  << ", and you can enter in your notes in shorthand notation, then the "
	  << "program will replaces those abbreviations with actual words in the"
	  << " sentence.\n\n\n";
}

//This function takes an array as argument and will prompt the user for an array and read it in.
void setup_word(char word[])
{
     cout << "\n\nPlease enter the word: ";
     cin.width(WORD);   
     cin >> word;
     cin.ignore(100, '\n');
}

//This function takes an array as argument and will prompt the user for an array and read it in.
void setup_abbr(char abbr[])
{
     cout << "\n\nPlease enter the abbreviation: ";
     cin.width(ABBR);
     cin >> abbr;
     cin.ignore(100, '\n');
}

//This function takes an array as argument and will prompt the user for an array and read it in.
void read_sentence(char senc[])
{
     cout << "\n\n\n\n\nPlease enter in a sentence representing "
	  << "your notes in shorthand notation: ";
     cin.get(senc, SENC, '\n');
     cin.ignore(100, '\n');
}

//This funtion takes two arguments, and it converts all the characters in the first array
//into uppercase and store them in the second array arguemnt.
void convert(char abbr[], char temp[])
{
     int len_abbr = strlen(abbr);
     for(int j = 0; j < len_abbr; ++j) //Iterate through the array
         temp[j] = toupper(abbr[j]);  //And convert each character into uppercase
     temp[len_abbr] = '\0';          //Assign '\0' to the last element of the array.
}

//This function takes two arrays as arguments, it checks if the first character in 
//the first array argument is uppercase or lowercase, then decides whether to output
//the actual word capitalized or not.
void output(char chk[], char wd[])
{
    if(isupper(chk[0]))         //If the first character in the chunk is uppercase.
        wd[0] = toupper(wd[0]); //Then turn the first character in the word into uppercase.
    else                        //Otherwise,
        wd[0] = tolower(wd[0]); //Turn the first character in the word into lowercase.
    cout << wd;                 //Output the word.
}

//This function takes six arguements. The sentence that the user enters; the three abbreviations
//and three actual words. And the funtion would replace every abbreviation with actual word, if 
//the abbreviation in the sentence is capitalized, then the actual word been displayed would also
//be capitalized; otherwise, it would be lowercase letters in the actual word.
void replace(char senc[], char ab1[], char wd1[], char ab2[], char wd2[], char ab3[], char wd3[])
{
     int len_senc = strlen(senc); //Assign the variable with the value for the length of the sentence.
     int len_ab1 = strlen(ab1); //Assign the variable with the value for the length of the first abbreviation.
     int len_ab2 = strlen(ab2); //Assign the variable with the value for the length of the second abbreviation.
     int len_ab3 = strlen(ab3); //Assign the variable with the value for the length of the third abbreviation.
     char chunk[SENC];        //Create an array variable for the chunk array that will be used.
     char temp1[len_ab1 + 1]; //Create a variable for storing an array related to the first abbraviation.
     char temp2[len_ab2 + 1]; //Create a variable for storing an array related to the second abbraviation.
     char temp3[len_ab3 + 1]; //Create a variable for storing an array related to the third abbraviation.
     char temp_ch[SENC];      //Create a variable for storing an array related to the chunk array.
     int i = 0;               //Create an integer variable and initialize it with zero.
     while(i < len_senc)      //Executes when there are still elements haven't been analyzed in the sentence.
     {
	 int k = 0;              //Create a variable k and initialize it to zero.
	 while(isalpha(senc[i])) //While loop executes when the specific character is an alphabet letter.
         {
             chunk[k] = senc[i]; //Assign the letter to the variable called chunk.
	     ++k;                //Increment k with one.
	     ++i;                //Increment i with one.
	 }
	 chunk[k] = '\0';     //Add '\0' to the end of the chunk when it's completed. 
	 convert(ab1, temp1); //Call convert function to get the uppercase version of the first abbreviation.
	 convert(ab2, temp2); //Call convert function to get the uppercase version of the second abbreviation.
	 convert(ab3, temp3); //Call convert function to get the uppercase version of the third abbreviation.
         convert(chunk, temp_ch); //Call convert function to get the uppercase version of the chunk.	 
	 if(strcmp(temp_ch, temp1) == 0) //If the chunk matches with the first abbreviation.
             output(chunk, wd1);         //Call the output function.
	 else if(strcmp(temp_ch, temp2) == 0) //If the chunk matches with the second abbreviation.
             output(chunk, wd2);
	 else if(strcmp(temp_ch, temp3) == 0) //If the chunk matches with the third abbreviation.
             output(chunk, wd3);
         else                      //If the chunk doesn't match with any abbreviations
             cout << chunk;        //Output the chunk itself

	 //while the specific character is not an alphabet or the '\0'(the end of the array) 
         while(!isalpha(senc[i]) && senc[i] != '\0') 
	 {
	     cout << senc[i];      //Output the character itself
	     ++i;                  //Increment i with one each time
	 }
     }

     cout << "\n\n\n\n";          //new lines
     cout << endl;
}

//This function asks the user if they want to do it again by
//prompting the user for an input, true or false will be returned.
bool again()
{
     char answer;                              //Create a character variable
     do
     {
         cout << "\n\n\nDo you want to re-enter?(Y/y or N/n): ";
         cin >> answer;
	 cin.ignore(100, '\n');
	 answer = toupper(answer);            //Convert the character to an uppercase letter
	 if (answer != 'Y' && answer != 'N')
             cout << "\n\nYou entered a wrong letter. Please enter Y/y or N/n.";
     }while(answer != 'Y' && answer != 'N'); //This loop will continue until the uppercase letter is Y or N
     if (answer == 'Y')                     //This function will return true if answer is Y
         return true;
     return false;                         //Return false if answer is N
}    

