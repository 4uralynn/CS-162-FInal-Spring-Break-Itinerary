#include "main.h"
using namespace std;

//Laura Cornwell Engram - CS162 - 3/14/2020
//
//This is a program that will keep an itinerary of spring break activities to 
//accomplish and/or enjoy. The program will allow the user to add new 
//activies to the list and view all activities, or a specific activity by name.
//Activities will include a name, description, reason,  the length of time it 
//will take, and a priority level.


//Navigation Menu function to offer up choices to act as a central hub of choices
//for managing the itinerary and individual activities 
void navi(char &input, itinerary &list)
{
	do
	{
		cout << "\n\n" <<
			"Spring Itinerary | "
			"Please enter the appropriate key...\n"
			"You can choose exit or help (X/H) or pick "
			"from the following menu options:\n\n"
			"| Add Activities | ";
		if (list.exists())
		{
			cout << "Display All Acitivities |"
				" Display an Activity by Name | Write to Text File |"
				"\n|\tA\t |\t      D\t\t   |\t\t  N\t\t |\t    W\t      |  ";
		}
		else
		{
			cout << "\n|\tA\t |  ";
		 }
		cin >> input;
		cin.ignore(2, '\n');
	}while(!('A' == toupper(input)) && !('D' == toupper(input)) &&
	       !('N' == toupper(input)) && !('X' == toupper(input)) && 
	       !('H' == toupper(input)) && !('W' == toupper(input)));
	if ('H' == toupper(input))
	{
		displayhelp();
	}	
}
//Function to handle quick yes or no questions and check errors
char confirmresponse()
{
	char resp[RESPONSE];
	do
	{	
		cin.width(RESPONSE);
		cin >> resp;
		cin.clear();
		cin.ignore(RESPONSE, '\n');
		resp[0] = toupper(resp[0]);
	}while(!('Y' == resp[0]) && !('N' == resp[0]));

	return resp[0];
}

//Function to display help information 
//and user notes (to be implemented in program 5);
void displayhelp()
{
	char choice[2];
	int value;
	cout << "\n\nHELP INFORMATION:\n\n"
		"- At the beginning of this program, you will only have the options to\n" 
		"  Add Activities (A), find Help (H), or Exit (X) Once you have added at\n" 
		"  least one activity, the following options are available:\n"
		"	- Display Activities(D) will simply display all activities entered\n"
		"  	  since the session began.\n"
		" 	- Display By Name (N) will display a list of activity names\n"
		"	  entered.\n"
		" 		- Names are CASE SENSITIVE. Be sure to enter them\n" 
		"     		  correctly.\n"
		"	- Write To File (W) will write all the activities you've entered\n"
		"	  in to a formatted text file named 'itinerary.txt'.\n"
		"		- The 'itinerary.txt' file can be found in the program\n"
		"		  directory. The entire file is rewrittne every time.\n"
		"- The program is designed to be semi-intuitive. Respond to questions as\n"
		"  might normally. The program will ask you to add a response to it's data\n"
		"  if your answers aren't recognized.\n"
		"  	- MANAGE response lists by pressing Y(es), N(o), (e)X(it), or\n"
		"  	  H(elp) now. Otherwise press C.\n"
		"- While entering information, you can also say to stop, or ask for help\n"
		"  When entering new activities for spring break, you'll be asked for the\n"
		"  name of the activity. Enter something simple so it is easy to re-enter\n"
		"  later. After the name is confirmed, the program will ask for a\n"
		"  description of the activity, how much time it will take, and it's\n"
		"  priority, on a scale of 0 to 3.\n"
		"- The Navigation Menu returns after each phase, where you can again\n"
		"  recall these help instructions, if needed.\n\n Happy Spring Break!\n\n";
	do
	{	
		cout << "\nContinue with C, \nor manage responses (Y,N,X,H):  ";
		cin.get(choice, 2, '\n');
		cin.ignore(2, '\n');
		choice[0] = tolower(choice[0]);
		if('y' == choice[0] || 'n' == choice[0] || 
		   'x' == choice[0] || 'h' == choice[0])
		{
			value = morpheus(3, choice);
		}
	}while('c' != choice[0]);
}

//Lead function to make sense of a user responses
int morpheus(int prompt, char input [])
{
	int returnvalue = 0;
	char temp[101];
	node *yhead = NULL;
	node *nhead = NULL;
	node *xhead = NULL;
	node *hhead = NULL;
	ifstream file_in;
	file_in.open("yresponses.it");
	neo(yhead, file_in, temp);
	file_in.close();
	file_in.open("nresponses.it");
	neo(nhead, file_in, temp);
	file_in.close();
	file_in.open("xresponses.it");
	neo(xhead, file_in, temp);
	file_in.close();
	file_in.open("hresponses.it");
	neo(hhead, file_in, temp);
	file_in.close();
	for (int i = 0, j = 0; i < 100 && j <= 3 && '\0' != input[i]; ++i)
	{
		temp[i] = tolower(input[i]);
		temp[i+1] = '\0';
		if (' ' == input[i])
			++j;
	}	
	returnvalue = cypher(yhead, nhead, xhead, hhead, prompt, temp);
 	return returnvalue;
}

//Function to decode and destroy lists
int cypher(node *& yhead, node *& nhead, node *& xhead, node *& hhead, 
	   int prompt, char temp[])
{
	int returnvalue;
	if (!listmatch(yhead, temp) && !listmatch(nhead, temp) &&
	    !listmatch(xhead, temp) && !listmatch(hhead, temp))
	{
		returnvalue = trinity(yhead, nhead, xhead, hhead, prompt, temp);
	}
	if (listmatch(yhead, temp))
	{
		if (prompt < 1)
			returnvalue = 1;
		if (prompt == 3)
			manage(yhead);		
	}	
	if (listmatch(nhead, temp))
	{
		if (prompt <= 1)
			returnvalue = 2;
		if (prompt ==3)
			manage(nhead);
	}
	if (listmatch(xhead, temp))
	{
		returnvalue =3;
		if (prompt ==3)
			manage(xhead);
	}
	if (listmatch(hhead, temp))
	{
		returnvalue = 4;
		if (prompt ==3)
			manage(hhead);
	}
	deletelist(yhead);
	deletelist(nhead);
	deletelist(xhead);
	deletelist(hhead);
	return returnvalue;
}

//Function to read possible responses from files
void neo(node *& head, ifstream &file_in, char temp[])
{
	for (int i = 0; file_in && !file_in.eof(); ++i)
	{
		file_in.get(temp, 100, ':');
		file_in.ignore(100, ':');
		file_in.ignore(100, '\n');
		append(head, temp);
	}
}

//Funtion to handle large responses and short responses that don't match
//up to expections.
int trinity(node *& yhead, node *& nhead, node *& xhead, node *& hhead, 
            int prompt, char input[])
{
	char resp;
	int returnv = 0;
	if (0 == prompt)
	{
		cout << "\n\nI don't recognize the response, '" << input 
		     << "'. Would you like me to save\n it as a response"
		     << " to expect in the future?  ";
		resp = confirmresponse();
		if ('Y' == resp)
		{
			cout << "\n\nDoes this response mean yes, no, "
				"exit, or help?";
			do
			{
				cout << "\n\n(y, n, x, h)  ";
				cin >> resp;
				cin.ignore(100, '\n');
				resp = toupper(resp);
			}while('Y' != resp && 'N' != resp && 
			       'X' != resp && 'H' != resp);
			if ('Y' == resp)
			{
				writenewresp(yhead, input);
			}
			if ('N' == resp)
			{
				writenewresp(nhead, input);
			}
			if ('X' == resp)
			{
				writenewresp(xhead, input);
			}
			if ('H' == resp)
			{
				writenewresp(hhead, input);
			}
		}
		else
			returnv = 0;
	}
	if (2 == prompt)
		returnv = 5;
	return returnv;
}

//Function to manage responses separately, accessed though
//the displayhelp function, mediated by morpheus.
void manage(node *& head)
{
	char resp[101];
	cout << "\n\nSaved responses are:\n";
	node * current = head;
	while (current->link)
	{
		cout << "'" << current->data << "', ";
		current = current->link;
	}
	cout << "'" << current->data << "'";
	cout << "\n\nThe response you type will be added if not in "
		"the list, or\nremoved if it already exists:   ";
	cin.get(resp, 100, '\n');
	cin.ignore(100, '\n');
	for (int i = 0; i > strlen(resp); ++i)
	{
		tolower(resp[i]);
	}
	if (!listmatch(head, resp))
	{
		writenewresp(head, resp);
	}
	else
	{
		ofstream file_out;
		if (file_out && 'y' == (head->data)[0])
			file_out.open("yresponses.it");
		if (file_out && 'n' == (head->data)[0])
			file_out.open("nresponses.it");
		if (file_out && 'x' == (head->data)[0])
			file_out.open("xresponses.it");
		if (file_out && 'h' == (head->data)[0])
			file_out.open("hresponses.it");
		node * target = head;
		while(target && strcmp(resp, target->data) != 0)
		{	
			current = target;
			file_out << current->data << ":\n";
			target = target->link;
		}
		current->link = target->link;
		delete target;
		target = NULL;
		current = current->link;
		while (current->link)
		{
			file_out << current->data << ":\n";
			current = current->link;
		}
		file_out.close();
	}
	cout << "\n\nDone!";
}

//Function to write unrecognized responses into the files
//to save for future use, and append to the end of the LLL
void writenewresp(node *& head, char input[])
{
	ofstream file_out;
	if (file_out && 'y' == (head->data)[0])
	{
		file_out.open("yresponses.it", ios::app);
		file_out << input << ":\n";
		file_out.close();
	}
	if (file_out && 'n' == (head->data)[0])
	{
		file_out.open("nresponses.it", ios::app);
		file_out << input << ":\n";
		file_out.close();
	}
	if (file_out && 'x' == (head->data)[0])
	{
		file_out.open("xresponses.it", ios::app);
		file_out << input << ":\n";
		file_out.close();
	}
	if (file_out && 'h' == (head->data)[0])
	{
		file_out.open("hresponses.it", ios::app);
		file_out << input << ":\n";
		file_out.close();
	}
	append(head, input);
}

//Function to match user response with possible responses
bool listmatch(node *& head, char array[])
{	
	bool match = false;
	for (int i = 0; i > strlen(array); ++i)
	{
		tolower(array[i]);
	}
	if (!head)
	{
		cout << "\n\nError: Missing or currupted "
			"response file!";
	}
	else
	{
		node * current = head;
		while (current->link)
		{
			if(strcmp(current->data, array) == 0)
			{
				match = true;
			}
			current = current->link;
		}
		if (strcmp(current->data, array) == 0)
		{
			match = true;
		}
	}
	return match;
}

//Function to append possible nodes (responses) to LLL
void append(node *& head, char temp [])
{
	if(!head)
	{
		head = new node;
		head->data = new char[strlen(temp) +1];
		strcpy(head->data, temp);
		head->link = NULL;
	}
	else
	{
		append(head->link, temp);
	}
}

//Function to delete the entire list of responses
void deletelist(node *& head)
{	
	if(!head)
		return;
	if(!head->link)
	{
		delete head;
		head = NULL;
	}
	else
	{
		deletelist(head->link);
	}
}
