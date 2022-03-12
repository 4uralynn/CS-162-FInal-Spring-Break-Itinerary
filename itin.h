#include "act.h"

//Laura Cornwell Engram - CS162 - 3/14/2020
//
//This is a program that will keep an itinerary of spring break activities to 
//accomplish and/or enjoy. The program will allow the user to add new 
//activies to the list and view all activities, or a specific activity by name.
//Activities will include a name, description, reason,  the length of time it 
//will take, and a priority level.


//This file is the header file setting up constants and prototypes for the
//itinerary class.
//

//Class
class itinerary
{
	public:	//Constructor and class member prototypes
		itinerary();
		~itinerary();
		void displayspec(int choice);
		void readinloop();
		void writefile();
		bool exists();
	private:  
		activity *array; 	//All activites
		int total;		// Amount of activities	
};
