
//Laura Cornwell Engram - CS162 - 3/14/2020
//
//This is a program that will keep an itinerary of spring break activities to 
//accomplish and/or enjoy. The program will allow the user to add new 
//activies to the list and view all activities, or a specific activity by name.
//Activities will include a name, description, reason,  the length of time it 
//will take, and a priority level.


//This file is the header file setting up constants and prototypes for the
//itinerary class.

//Constants
const int RESPONSE = 21;	//Size of array for user responses, names, or word

//Classes
class activity
{
	public:
		activity();
		~activity();
		void read_in(int &count);
		void prioritize();
		void display(int choice, char array[]);
		void actcpy(activity &index);
		void writeact();	
	private:
		char name [RESPONSE]; 		//Name of activity
		char *descr;			//Description of activity
		int priority;			//Priority of activity
		float time;			//Amount of time for an activity
		int len;
};
