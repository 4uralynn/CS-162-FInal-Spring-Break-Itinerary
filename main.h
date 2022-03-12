#include <iostream>
#include <cstring>
#include <cctype>
#include <fstream>
#include "itin.h"
using namespace std;

//Laura Cornwell Engram - CS162 - 3/14/2020
//
//This is a program that will keep an itinerary of spring break activities to 
//accomplish and/or enjoy. The program will allow the user to add new 
//activies to the list and view all activities, or a specific activity by name.
//Activities will include a name, description, reason,  the length of time it 
//will take, and a priority level.


//This file is the main header file setting up constants, data types, and function
//prototypes for the program.


//Constants
const int TEMP = 1000;		//Amount of characters in decription


//Structures
struct node
{
	char * data = NULL;
	struct node * link = NULL;
};


//Prototypes
void navi(char &input, itinerary &list);	
char confirmresponse();					
void displayhelp();
bool listmatch(node *& head, char array[]);
void append(node *& head, char temp []);
void deletelist(node *& head);
void writenewresp(node *& head, char input[]);
void manage(node *& head);
void neo(node *& head, ifstream &file_in, char temp[]);
int morpheus(int prompt, char input []);
int trinity(node *& yhead, node *& nhead, node *& xhead, node *& hhead, 
	    int prompt, char input[]);
int cypher(node *& yhead, node *& nhead, node *& xhead, node *& hhead, 
	   int prompt, char temp[]);
