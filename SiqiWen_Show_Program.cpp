#include <iostream>
using namespace std;

/* Siqi Wen  CS162
   This is a program that will help the user calculate how many commercials
   can fit in a show that is scheduled for a 60 minute time slot. */

int main()
{
     //Variable definitions
     int length_of_show = 0;        //The user will enter the length of the show
     int leftover_time = 0;         //The time left over for potential commercials
     int length_of_commercial = 0;  //The user will enter the length of the commercial they want to run
     int amount_of_commercials = 0; //The amount of commercials that can fit in
     int previews = 0;              //The length of previews that might be needed

     //Welcome the user and explain the main purpose of the program
     cout << "\n\nHi there, welcome to our program!\n\n";
     cout << "\n\nWe're here to help you calculate how many commercials can fit" 
	  << " in a show that is scheduled for a 60 minute time slot.\n\n";

     do
     {	     
	 //Prompt the user to enter the length of the show
         cout << "\n\nPlease enter the length of the show in minutes"
	      << "(in the range of 0-60, including 0 and 60): ";
         cin >> length_of_show;                              //Store the answer in a variable
	 if(length_of_show < 0 || length_of_show > 60)
	     cout << "\n\n\nYou entered something out of "  //Inform the user when they entered a number out of range
		  << "the range! Please try again...\n\n"; 

     } while(length_of_show < 0 || length_of_show > 60);  //Loop until the user enters a proper number
     
     cout << "\n\n\nThe length of the show is "          //Echo out the answer back to user
	  << length_of_show << " minute(s).\n\n";      
    
     leftover_time = 60 - length_of_show;              //Calculate the leftover time for potential commercials
     cout << "\n\nThis leaves " << leftover_time      //Output the result
	  << " minute(s) for commercials.\n\n";     

     while(leftover_time > 0)                    //This loop will only be executed when leftover time is more than zero
     {
         do
         {
             //Prompt the user to enter the length of the commercial they want to air
             cout << "\n\nPlease enter the length of "
		  << "the commercial you want to air: ";
	     cin >> length_of_commercial;               //Store the answer in a variable
	    
	     if(length_of_commercial > leftover_time)
	         cout << "\n\n\nWe are out of time"   //Inform the user when they entered a number out of range
		      << " and it can't be used.\n\n";
	     else if(length_of_commercial < 0)
	         cout << "\n\n\nYou cannot enter "    //Inform the user that they cannot enter a negative number
		      << "a negative number.\n\n"; 

         } while(length_of_commercial > leftover_time || length_of_commercial < 0);  //Loop until the user enters a proper number

         if(length_of_commercial != 0)  //If the length of the commercial is less than or equal to the leftover time and is more than zero
         {	
	     ++amount_of_commercials;                //Increment the amount of commercials by one
	     leftover_time -= length_of_commercial;  //Update the leftover time for potential commercials
	     cout << "\n\n\nThere are/is "           //Inform the user the updated leftover time for commercials
		  << leftover_time << " minute(s) "
		  << "left for commercials.\n\n";
         }
         else                              //If the user has no commercials they want to run
         {
	     previews = leftover_time;  //Assign the value of leftover time to the variable that represents the length of fillers
             leftover_time = 0;         //Assign the variable that represents leftover time with zero

             cout << "\n\n\nThere is still time left over, filler "    //Inform the user that fillers will be needed when they don't have
		  << "commercials (such as previews) will be needed,"  //enough commercials to fulfill the leftover time for commercials
		  << " and the length needed for those fillers "       
		  << "should be " << previews << " minute(s).\n\n\n";  //And tell them how long the fillers need to be
      
         }
     }

     cout << "\n\n\nThere are/is " << amount_of_commercials    //Tell the user the amount of commercials that can fit in the show
	  << " commercial(s) that can fit in the show. And "   //and the length needed for filler commercials
	  << "the length needed for filler commercials should "         
	  << "be " << previews << " minute(s).\n\n\n\n\n\n";

     cout << "Thank you for using our program, "           //Ending message
	  << "have a wonderful day!\n\n\n\n\n\n";      

     return 0;
}
