#include "main.h"
using namespace std;

//Laura Cornwell Engram - CS162 - 3/14/2020
//
//This is a program that will keep an itinerary of spring break activities to 
//accomplish and/or enjoy. The program will allow the user to add new 
//activies to the list and view all activities, or a specific activity by name.
//Activities will include a name, description, reason,  the length of time it 
//will take, and a priority level.


//This file holds the function implementations for the itinerary and associated activity class.

//Constructor
activity::activity()
{
	descr = NULL;
	name[0] = '\0';
	priority = 0;
	time = 0;
	len = 0;
}

activity::~activity()
{	if (descr)
	{
		delete [] descr;
		descr = NULL;
	}
}

itinerary::itinerary()
{
	array = NULL;
	total = 0;
}

itinerary::~itinerary()
{
	if (array)
	{
		delete [] array;
		array = NULL;
	}
}

//Function to display all the activities in the itinerary
void itinerary::displayspec(int choice)
{
	char response[RESPONSE]; 	//For user responses
	int nav;			//To evaluate responses
	if ( 0 == choice)
	{
		for (int i = 0; i < total; ++i)
		{	
			array[i].display(0, response);
		}
	}
	else if ( 1 == choice)
	{
		for (int k = 0; k < total; ++k)
		{
			array[k].display(2, response);
		}
		do
		{
			cout << "\n\nWhich activity would you like to see?  ";
			cin.get(response, RESPONSE, '\n');
			cin.ignore(RESPONSE, '\n');
			nav = morpheus(1, response);
			if (nav == 4)
				displayhelp();
		}while(nav == 4);
		if (nav == 3)
			return;
		for (int j = 0; j < total; ++j)
		{
			array[j].display(1, response); 
		}
	}
}


//Function to display each activity input by the user.
void activity::display(int choice, char array[])
{
	if (0 == choice)
	{
		cout << "\n\n\n'" << name << "'\n\nDescription:\n" << descr 
		     << "\n\nExpected length of time to complete:\t" 
		     << time << " hour(s) " << "\t\tPriority:\t" << priority << endl;
	}
	if (1 == choice)
	{		
		if (strcmp(array, name) == 0)
		{
		cout << "\n\n\n'" << name << "'\n\nDescription:\n" << descr 
		     << "\n\nExpected length of time to complete:\t" 
		     << time << " hour(s) " << "\t\tPriority:\t" << priority << endl;
		}
	}
	if (2 == choice)
	{
		cout << "'" << name << "', ";
	}	
	
}

//Function to read-in activities into the itinerary, back to back.
void itinerary::readinloop()
{	
	activity temp[20];		//Temporary activity array
	activity *newtemp;		//Temporary array to move existing
	newtemp = NULL;			//activities to.
	char response [101];			//Users response
	int nav = 0;
	int count = 0;			//To count space for activities
	do				//to allocate
	{
		temp[count].read_in(count);
		do
		{
			cout << "\n\nDo you want to add a new activity "
				"to your itinerary?  ";
			cin.get(response, 100, '\n');
			cin.ignore(100, '\n');
			nav = morpheus(0, response);
			if (4 == nav)
				displayhelp();
		}while (nav == 0 || nav == 4);		
	}while((1 == nav));
	if (3 == nav)
		return;
	if (array)             
	{
		newtemp = new activity[total];
		for (int i = 0; i < total; ++i)
		{
			array[i].actcpy(newtemp[i]);
		}
		delete []array;
		array = NULL;	
		array = new activity[(total + count)];
		for (int j = 0; j < total; ++j)
		{
			newtemp[j].actcpy(array[j]);
		}
		for (int l = 0; l < count; ++l)
		{
			temp[l].actcpy(array[(l + total)]);
		}
		total = total + count;
	}
	else
	{
		total = count;
		array = new activity[total];
		for (int k = 0; k < total; ++k)
		{
			temp[k].actcpy(array[k]);
		}
	}
	if (newtemp)
		delete [] newtemp;
}

//Function for copying activities, similar to strcpy
void activity::actcpy(activity &index)
{
	strcpy(index.name, name);
	index.descr = new char[strlen(descr)];
	strcpy(index.descr, descr);
	index.priority = priority;
	index.time = time;
	index.len = len;
}
//Funtion to allow the user to enter a new activity into the itinerary
void activity::read_in(int &count)
{
	char temp[TEMP]; 	//Temporary arrary to read an activity detail
	char response [101];		///User responses
	int nav = 0;	//integer to represent how to handle user responses
	do	
	{	
		do
		{	
			cout << "\n\nEnter the name of the activity:   ";
			cin.get(name, RESPONSE, '\n'); 
			cin.ignore(RESPONSE, '\n');
	       		nav = morpheus(1, name);
			if (4 == nav)
				displayhelp();
		}while(4 == nav);
		if (3 != nav && 2 != nav)	
		{
			cout << "\n\nThe name for the activity "
				"you are adding will be\n\n"
			     << name << "\n\nNote: You will need "
			        "to enter this name to "
				"display your activity details later."
				"\n\nIs this correct?  ";
			cin.get(response, 100, '\n');
	       		cin.ignore(100, '\n');	
			nav = morpheus(0, response);
			if (4 == nav)
				displayhelp();
		}
	}while(nav != 3 && nav != 1 && nav != 0);
	if (3 == nav)
		return;
	do
	{
		cout << "\n\nEnter the description of "
			"your spring break activity:\n";
		cin.get(temp, TEMP, '\n');
		cin.ignore(TEMP, '\n');
		nav = morpheus(2, temp);
		if (4 == nav)
			displayhelp();
	}while(5 != nav && 3 != nav);
	if (3 == nav)
		return;
	len = strlen(temp) + 1;
	descr = new char[len];
	strcpy(descr, temp);
	prioritize();
	++count;
}

//Function to read in activity time and priority
void activity::prioritize()
{
	int add = 0;		//To add hours to minutes

	cout << "\n\nAbout how much time will this activity take?\n\nWhole hours?  ";
	cin >> add;
	cin.ignore(100, '\n');
	cout << "    Minutes?  ";
	cin >> time;
	cin.ignore(100, '\n');
	time = add + (time / 60);
	cout << "Rate the activity's importance, from 0 (none) to 3 (high):  ";
	do
	{
		cin >> priority;
		cin.ignore(100, '\n');
		if (priority > 3 || priority < 0)
			cout << "\nPlease enter a number from 0 to 3:  ";
	}while(priority > 3 || priority < 0);
}

//Function to write the entire itinerary to a text file.
void itinerary::writefile()
{

	ofstream file_out;
	file_out.open("itinerary.txt");
	if (file_out)
	{
		file_out << "Spring Break Itinerary - Activities Planned";
		file_out.close();
	}
	for (int i = 0; i < total; ++i)
	{
		array[i].writeact();	
	}

	cout << "\n\n" << total << " activitiess were saved to the file.";
}

//Function to write all activities entered in by the user into a file.
void activity::writeact()
{
	ofstream file_out;				
	file_out.open("itinerary.txt", ios::app);
	if (file_out)
	{	
		file_out << endl << endl << "'" << name << "'" << endl 
			 << endl << "Description:" << endl 
			 << descr << endl << endl 
			 << "Expected length of time to complete:	" 
			 << time << " hour(s)		Priority:	" 
			 << priority << endl;
		file_out.close();
	}
	else
	{
		cout << "\n\nError: Issue writing to file.";
	}
}

//Function to check if an itinerary exits
bool itinerary::exists()
{
	if (array)
	{
		return true;
	}
	else
	{
		return false;
	}
}
