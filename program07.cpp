/*
Erik Lougee
Programming Assignment 7
This was the largest program I wrote, combining elements of all the previous assignments 
into one completed work. The purpose of the program was to create a sequential disk file,
fill it with class information obtained by the user's input, and load that data into arrays.
From the arrays, we then have two separate functions that sort them alphabetically by 
class name and instructor name. We are also able to obtain information from a search performed
by entering the class name, and relevant data is displayed. Any of these functions (save input)
may be performed after data has been loaded into the arrays. 
VARIABLE DICTIONARY:
VARIABLE		TYPE		REPRESENTING
choice			char		Used in the menu function to determine user's choice of menu options
array_length	int			Change this value if more arrays are needed (more input for classes)
enrollment[]	int			Array used to hold number of students per class
i				int			Used in all for loops so local declaration is deemed null
index[]			int			Array used to keep all arrays in correct order relative to others (cohesion)
answer			string		Only used to determine if the user needs to input data for the sequential disk file (SDF)
array_copy[]	string		Used to keep a copy of any array to be sorted, thereby determining sorted order without ruining cohesion 
class_name[]	string		Array used to hold class name data
file_built		string		Used to determine if the SDF has been built or not. Used in conjunction with menu()'s main loop
instructor[]	string		Array used to hold instructor name data
search_this		string		Used to determine which class to search for in the obtain_instructor() function
swapping		string		Used to determine if swapping must be made in arrays to put them in order
*/

#include <iostream>
#include <string>
#include <Windows.h>
#include <fstream>

using namespace std;

ifstream fin;
ofstream fout;

char choice[10];

int array_length = 6;
int enrollment[6];
int i;
int index[6];

string answer;
string array_copy[6];
string class_name[6];
string file_built;
string instructor[6];
string search_this;
string swapping;

int menu();								//Main Menu function
void build_file();						//Builds a data file based on user input
void error_trap();						//Determines if Y or N is selected, informs user of valid choices
void load_data();						//Loads the data from the data file into arrays to be sorted
void obtain_instructor();				//Search for class and print relevant data
void sort();							//Sorts arrays and makes an index for selected array
void sort_by_instructor();				//Sorts by instructor's name
void sort_by_class();					//Sorts by class name


int main()
{
	cout << "This program is designed to keep track of college enrollment activity in a \nnumber of courses. ";
	cout << "Do you wish to run this program? (Y)es or (N)o\n>";
	string run;
	cin >> run;

	if (run != "Y" && run != "y")
	{
		cout << "Ok, be seeing you!\n";
		system("PAUSE");
		return 0;
	}

	cout << "Do you wish to enter input data?\n>";
	error_trap();
	if (answer == "Y")
		build_file();
	else 
		file_built = "Y";
		answer = "Y";
		menu();
}

//All functions alphabetical from this point on

void build_file()
{
	string data;
	int number_data;
	fout.open("school.dat");
	cout << "File created.";
	for (int x = 0; x < 6; x++)
	{
		cout << "Please input class name: ";
		cin >> data;
		fout << data << " ";
		cout << "Please input instructor's last name: ";
		cin >> data;
		fout << data << " ";
		cout << "Please input number of students in the class: ";
		cin >> number_data;
		while (number_data > 25 || number_data < 1)
		{
			cout << "\nSorry, that is an invalid answer.";
			cout << "\nPlease input a number from 1 to 25: ";
			cin >> number_data;
		}
		fout << number_data << " ";
	}
	file_built = "Y";
	fout.close();
}

void error_trap()
{	
	cin >> answer;
	while (answer != "Y" && answer != "N")
	{
		Beep(550, 100);
		Beep(550, 200);
		cout << "Error.\n";
		cout << "The valid choices are (Y)es or (N)o.\n";
		cout << "Please enter a valid choice.\n>";
		cin >> answer;
	}
}

void load_data()
{
	fin.open("school.dat");

	string data;

	for (int x = 0; x < 6; x++)
	{
		fin >> class_name[x];
		fin >> instructor[x];
		fin >> enrollment[x];
	}
	sort();
	cout << "\nData loaded.\n";
	fin.close();
	system("PAUSE");
}

int menu()
{
	while (file_built == "Y" && answer == "Y")
	{
		system("CLS");
		cout << "C L A S S   M E N U\n\n\n";
		cout << "(L)oad Data to Process.\n";
		cout << "List classes by (N)ame.\n";
		cout << "List classes by (I)nstructor.\n";
		cout << "(O)btain Instructor Name and Enrollment.\n";
		cout << "(E)xit program.\n";

		cout << "Enter choice:";

		cin >> choice;

		switch (choice[0])
		{
		case ('L'):
			{
			cout << "Loading...one moment please.";
			load_data();
			break;
			}
		case ('N'):
			{
			sort_by_class();
			break;
			}
		case ('I'):
			{
			sort_by_instructor();
			break;
			}
		case ('O'):
			{
			obtain_instructor();
			break;
			}
		case ('E'):
			{
			cout << "Be seeing you...\n";
			system("PAUSE");
			return false;
			}
		default:
			{
			cout << "Invalid choice. Please try again.\n" << endl;
			break;
			}
		}
	}
}

void obtain_instructor()
{
	system("CLS");
	
	cout << "I can show you relevant data based on class name.\n";
	cout << "Please enter the name of the class to obtain data about: ";
	cin >> search_this;

	string record_found = "N";
	for (i = 0; i < array_length; i++)
	{
		if (class_name[index[i]] == search_this)
		{
			record_found = "Y";
			cout << "The instructor for class " << class_name[index[i]] << " is professor " << instructor[index[i]] << " and there are " << enrollment[index[i]] << "\nstudents enrolled.\n"; 
			break;
		}
	}
	if (record_found == "N")
	{
		cout << "I'm sorry, I cannot find " << search_this << " in our database.\n";
	}

	system("PAUSE");
}

void sort()
{
	//Initializes index
	for (i = 0 ; i < 6 ; i++)
	{
		index[i] = i;
	}

	swapping = "Y";
	while (swapping == "Y")
	{
		swapping = "N";
		for (i = 0; i < array_length - 1; i++)
		{
			if (array_copy[i] > array_copy[i+1])
			{
				swap (array_copy[i], array_copy[i+1]);
				swap (index[i], index[i+1]);

				swapping = "Y";
			}
		}
	}
}

void sort_by_class()
{
	system("CLS");
	for (i = 0; i < array_length; i++)
	{
		array_copy[i] = class_name[i];		
	}
	
	sort();

	cout << "ALPHABETICAL CLASS LISTING BY CLASS NAME:\n";
	cout << "CLASS NAME | INSTRUCTOR | ENROLLMENT\n\n";

	for (i = 0; i < array_length; i++)
	{
		cout << class_name[index[i]] << " taught by Prof. " << instructor[index[i]] << " with " << enrollment[index[i]] << " students.\n";
	}
	system("PAUSE");
}

void sort_by_instructor()
{
	system("CLS");
	for (i = 0; i < array_length; i++)
	{
		array_copy[i] = instructor[i];		
	}
	
	sort();

	cout << "ALPHABETICAL CLASS LISTING BY INSTRUCTOR NAME:\n";
	cout << "CLASS | INSTRUCTOR | ENROLLMENT\n\n";

	for (i = 0; i < array_length; i++)
	{
		cout << class_name[index[i]] << " taught by Prof. " << instructor[index[i]] << " with " << enrollment[index[i]] << " students.\n";
	}
	system("PAUSE");
}
