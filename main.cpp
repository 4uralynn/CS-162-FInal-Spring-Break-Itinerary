#include "main.h"
using namespace std;

//Laura Cornwell Engram - CS162 - 3/14/2020
//
//This is a program that will keep an itinerary of spring break activities to 
//accomplish and/or enjoy. The program will allow the user to add new 
//activies to the list and view all activities, or a specific activity by name.
//Activities will include a name, description, reason,  the length of time it 
//will take, and a priority level.


//This file is to hold the main funtion, which manages the rest of the program.

//Main function for setting defining a class-based (itinerary) vairable 
//and managing the succession of other functions.
int main()
{ 
	char input;	//The user's input as a character
	itinerary list;	//The list of activities
	
	while(!('X' == toupper(input)))
	{
		navi(input, list);
		if ('A' == toupper(input))
		{
			list.readinloop();
		}
		if ('D' == toupper(input))
		{
		       list.displayspec(0); 	
		}
		if ('W' == toupper(input))
		{
			list.writefile();	
		}
		if ('N' == toupper(input))
		{
			list.displayspec(1); 
		}
	} 
	return 0;
}
