/*************************************************************
Name: Jacob Weeks
Date: December 14, 2018
***************************
Files for Assignment: Student.cpp
Purpose of File: 
This program allows the user to create a 
database containing info on a student
such as the name, GPA, courses taken
*************************************************************/

//Header
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;

//Struct of courses
//for the student struct
struct course 
{
	string courseTitle;
	string alphaDesignator;
	int courseNumber;
	int creditHours;
	string gradeEarned;

	//Initializes values
	course()
	{
		courseTitle = "";
		alphaDesignator = "";
		gradeEarned = "";
		creditHours = -1;
		courseNumber = -1;
	}
};

//Student struct
struct student 
{
	string name;
	course course[10];
	double gpa;

	//Initializes values
	student()
	{
		name = "";
		course[10];
		gpa = -1;
	}
};

//Keeps record of how many classes there
//are in the students record
int CLASS_COUNT = 0;

//Functions
int displayMenu();
void addStudent(student& student);
void addCourse(student& student);
void searchByAlphaDesignator(student student);
void searchByGrade(student student);
void showListings(student student);
double getGPA(student student);
void displayGPAInfo(student student);
void saveDatabase(student student);
void loadDatabase(student& student);

/***********************************************************
Function: Main
Precondition:
none
Postcondition: 
Controls the entire program
************************************************************/
int main()
{
	//Creates a new student
	student student;

	//While loop until the user wants to exit
	bool exitProgram = false;
	while (exitProgram == false)
	{
		//Displays the menu and gets the choice
		int choice = displayMenu();

		switch (choice)
		{
			//Add student
		case 1: addStudent(student);
			cout << "\n";
			break;
			//Add course
		case 2: addCourse(student);
			cout << "\n";
			break;
			//Search by Alpha
		case 3: searchByAlphaDesignator(student);
			cout << "\n";
			break;
			//Search by Grade
		case 4: searchByGrade(student);
			cout << "\n";
			break;
			//Show all listings
		case 5: showListings(student);
			cout << "\n";
			break;
			//Display GPA
		case 6: displayGPAInfo(student);
			cout << "\n";
			break;
			//Save
		case 7: saveDatabase(student);
			cout << "\n";
			break;
			//Load
		case 8: loadDatabase(student);
			cout << "\n";
			break;
			//Exit
		case 9: exitProgram = true;
			break;
		}

	}

	cout << "\nThank you for using! Goodbye!" << endl;
	system("pause");

}

/***********************************************************
Function: displayMenu
none
Postcondition:
Displays the menu and returns the users choice
************************************************************/
int displayMenu()
{
	//While loop for valid menu choice - 1-9
	bool validInput = false;
	while (validInput == false)
	{
		int choice;
		cout << "Select an option: " << endl;
		cout << "1. Enter a Student Name" << endl;
		cout << "2. Add a Course to the Database" << endl;
		cout << "3. Search for Course(s) by Alpha-Designator" << endl;
		cout << "4. Search for Course(s) by Grade" << endl;
		cout << "5. Show a Listing of All Courses Taken w/Grades" << endl;
		cout << "6. Display GPA Information" << endl;
		cout << "7. Save Database to a file" << endl;
		cout << "8. Load Database from a file" << endl;
		cout << "9. Exit" << endl;
		cin >> choice;

		//If the choice isnt in the valid range
		if (choice < 1 || choice > 9)
		{
			//Error
			cout << "\nSelect a valid choice!" << endl;
			validInput = false;
		}
		//Else it is valid, and return it
		else
		{
			return choice;
		}

	}

	//Error 
	return -1;

}

/***********************************************************
Function: addStudent
Reference to the student in main
Postcondition:
Gets and sets the students name, and passes it back
************************************************************/
void addStudent(student& student)
{

	//Strings to be set
	string studentName;
	string firstName;
	string lastName;

	//Loop while the name is not valid
	bool validName = false;
	while (validName == false)
	{
		//Clears the getline function before use
		cin.clear();
		cin.ignore(100, '\n');

		//Gets the students first name and middle names
		cout << "\nEnter the students first name (include any middle names): " << endl;
		getline(cin, firstName);

		//If the first name is less than 2letters
		if (firstName.length() < 2)
		{
			//Name is not valid
			cout << "\nYou must enter a valid first name!" << endl;
			validName = false;
		}
		//Else it is fine, and can move to the last name
		else
		{
			//Gets the users last name, should only be one name
			cout << "\nEnter the students last name: " << endl;
			cin >> lastName;

			//If the last name is less than 2 letters
			if (lastName.length() < 2)
			{
				//Name is not valid
				cout << "\nYou must enter a valid first name!" << endl;
				validName = false;
			}
			//Else everything is good, and can break out
			else
			{

				validName = true;

			}
		}
	}

	//Set the students info to the users input
	studentName = firstName + " " + lastName;
	student.name = studentName;

}

/***********************************************************
Function: addCourse
Reference to the student in main
Postcondition:
Gets the course info and adds it to the student and passes it
back
************************************************************/
void addCourse(student& student)
{
	//Course struct
	course course;

	//Variables to be used
	string alphaDesignator;
	string courseTitle;
	int courseNumber;
	int creditHours;
	char gradeEarned;

	//Gets the alpha-designator
	cout << "\nEnter the alpha-designator: " << endl;
	cin >> alphaDesignator;

	//Gets the course number
	cout << "\nEnter the course number: " << endl;
	cin >> courseNumber;

	//Clears the getline function before use
	cin.clear();
	cin.ignore(100, '\n');

	//Gets the course title
	cout << "\nEnter the course title: " << endl;
	getline(cin, courseTitle);

	//Gets the credits earned
	cout << "\nEnter the credits earned: " << endl;
	cin >> creditHours;

	//Gets the grade earned
	cout << "\nEnter grade earned: " << endl;
	cin >> gradeEarned;

	//Sets the course info	
	course.alphaDesignator = alphaDesignator;
	course.courseNumber = courseNumber;
	course.courseTitle = courseTitle;
	course.creditHours = creditHours;
	course.gradeEarned = gradeEarned;

	//Adds the course to student
	student.course[CLASS_COUNT] = course;

	//Increase class count, so the count array knows where
	//to out the next class
	CLASS_COUNT++;

}

/***********************************************************
Function: searchByAlphaDesignator
The student, containing course info
Postcondition:
Prints out the courses found matching user alpha
************************************************************/
void searchByAlphaDesignator(student student)
{

	//Variables to be used
	string alphaDesignator;

	//Gets the users search input
	cout << "\nEnter the alpha-designator you would like to search: " << endl;
	cin >> alphaDesignator;

	//Number of classes found
	int numFound = 0;
	
	//For loop for all classes
	for (int i = 0; i < CLASS_COUNT; i++)
	{
		//If the current course alpha designator matches users input
		if (student.course[i].alphaDesignator == alphaDesignator)
		{
			//Number found goes up
			//This is to properly format entry
			numFound++;

			//If its the first one, display all the header information
			if (numFound == 1)
			{
				//The alpha designator and number together
				string courseTotal = student.course[i].alphaDesignator + to_string(student.course[i].courseNumber);

				//Formatted header data
				cout << left;
				cout << setw(courseTotal.length() + 5) << "Course";
				cout << setw(student.course[i].courseTitle.length() + 5) << "Title";
				cout << setw(10) << "Hours";
				cout << setw(10) << "Grade" << endl;

				//Formatted course data
				cout << setw(courseTotal.length() + 5) << courseTotal;
				cout << setw(student.course[i].courseTitle.length() + 5) << student.course[i].courseTitle;
				cout << setw(10) << student.course[i].creditHours;
				cout << setw(10) << student.course[i].gradeEarned;
				cout << "\n";
			}
			//Else just print the course info
			else
			{
				//The alpha designator and number together
				string courseTotal = student.course[i].alphaDesignator + to_string(student.course[i].courseNumber);

				//Formatted header data
				cout << left;
				cout << setw(courseTotal.length() + 5) << courseTotal;
				cout << setw(student.course[i].courseTitle.length() + 5) << student.course[i].courseTitle;
				cout << setw(10) << student.course[i].creditHours;
				cout << setw(10) << student.course[i].gradeEarned;
				cout << "\n";
			}

		}

	}

}

/***********************************************************
Function: searchByGrade
The student, containing course info
Postcondition:
Prints out the courses found matching user graade
************************************************************/
void searchByGrade(student student)
{

	string grade;

	cout << "\nEnter the grade you would like to search: " << endl;
	cin >> grade;

	int numFound = 0;
	for (int i = 0; i < CLASS_COUNT; i++)
	{

		if (student.course[i].gradeEarned == grade)
		{
			numFound++;

			if (numFound == 1)
			{
				string courseTotal = student.course[i].alphaDesignator + to_string(student.course[i].courseNumber);

				cout << left;
				cout << setw(courseTotal.length() + 5) << "Course";
				cout << setw(student.course[i].courseTitle.length() + 5) << "Title";
				cout << setw(10) << "Hours";
				cout << setw(10) << "Grade" << endl;

				cout << setw(courseTotal.length() + 5) << courseTotal;
				cout << setw(student.course[i].courseTitle.length() + 5) << student.course[i].courseTitle;
				cout << setw(10) << student.course[i].creditHours;
				cout << setw(10) << student.course[i].gradeEarned;
				cout << "\n";
			}
			else
			{
				string courseTotal = student.course[i].alphaDesignator + to_string(student.course[i].courseNumber);

				cout << left;
				cout << setw(courseTotal.length() + 5) << courseTotal;
				cout << setw(student.course[i].courseTitle.length() + 5) << student.course[i].courseTitle;
				cout << setw(10) << student.course[i].creditHours;
				cout << setw(10) << student.course[i].gradeEarned;
				cout << "\n";
			}

		}

	}

}

/***********************************************************
Function: showListings
The student, containing course info
Postcondition:
Prints out all classes that the user entered
************************************************************/
void showListings(student student)
{
	//Number to properly format
	int number = 0;
	
	//For all classes
	for (int i = 0; i < CLASS_COUNT; i++)
	{
		//Combine alpha and number
		string courseTotal = student.course[i].alphaDesignator + to_string(student.course[i].courseNumber);
		
		//Add one to the number for each class
		number++;

		//If the course title is over 30 letters, cut it off and add "...", formatting issues otherwise
		//This ensures everything will line up
		if (student.course[i].courseTitle.length() > 28) 
		{
			student.course[i].courseTitle = student.course[i].courseTitle.substr(0, 25) + "... ";
		}

		//If the number is 1, put the header info
		if (number == 1)
		{
			cout << left;
			cout << setw(10) << "Course";
			cout << setw(30) << "Title";
			cout << setw(10) << "Hours";
			cout << setw(10) << "Grade" << endl;
		}

		//Print current course info
		cout << left;
		cout << fixed << setw(10) << courseTotal;
		cout << fixed << setw(30) << student.course[i].courseTitle;
		cout << fixed << setw(10) << student.course[i].creditHours;
		cout << fixed << setw(10) << student.course[i].gradeEarned;
		cout << "\n";

	}

}

/***********************************************************
Function: getGPA
The student, containing grades
Postcondition:
Returns the gpa
************************************************************/
double getGPA(student student)
{
	//Variable info initialized
	double gpa = 0;
	double gradePoints = 0;
	int qualityPoints = 0;
	int totalQualityPoints = 0;
	int totalQualityHours = 0;

	if (CLASS_COUNT == 0)
	{
		return -1;
	}

	//For all classes
	for (int i = 0; i < CLASS_COUNT; i++)
	{
		//If A - Points = 4
		if (student.course[i].gradeEarned == "A")
		{
			qualityPoints = 4;
		}
		//If B - Points = 3
		else if (student.course[i].gradeEarned == "B")
		{
			qualityPoints = 3;
		}
		//If C - Points = 2
		else if (student.course[i].gradeEarned == "C")
		{
			qualityPoints = 2;
		}
		//If D - Points = 1
		else if (student.course[i].gradeEarned == "D")
		{
			qualityPoints = 1;
		}
		//If F - Points = 0
		else if (student.course[i].gradeEarned == "F")
		{
			qualityPoints = 0;
		}


		//Combine the totalpoints with the current classes points
		totalQualityPoints += qualityPoints;
		//Combine the current credit hours into the total
		totalQualityHours += student.course[i].creditHours;
		//Add the total grade points for the gpa formula
		//Quality points multiplied by credit hours
		gradePoints += qualityPoints * student.course[i].creditHours;
	}

	//Gpa is the total grade points divided by the total hours
	gpa = gradePoints / totalQualityHours;

	//Return the GPA
	return gpa;

}

/***********************************************************
Function: displayGPAInfo
The student, containing GPA
Postcondition:
Displays the GPA to user
************************************************************/
void displayGPAInfo(student student)
{
	//Calculate the GPA
	double gpa = getGPA(student);

	//If there is a gpa
	if (gpa != -1)
	{
		//Show the GPA to the user
		cout << "\nGPA: " << fixed << setprecision(2) << gpa << endl;
	}
	else
	{
		cout << "\nNo GPA on record!" << endl;
	}

}

/***********************************************************
Function: saveDatabase
The student, containing all info
Postcondition:
Saves the student info to a StudentData.txt
************************************************************/
void saveDatabase(student student)
{
	//File to write to
	ofstream myfile;
	myfile.open("StudentInfo.txt");

	//Student info
	string studentName = student.name;
	double gpa = getGPA(student);

	//If there is no name or gpa, error
	if (studentName == "" || gpa == -1)
	{
		cout << "Could not find a student name or GPA!\nMake sure that there is a name and at least one course before you save!" << endl;
	}
	//There is a name and GPA
	else
	{
		myfile << studentName << endl;
		myfile << gpa << endl;

		//All Courses
		for (int i = 0; i < CLASS_COUNT; i++)
		{
			//Variables to be used
			string courseTitle;
			string alphaDesignator;
			int courseNumber;
			int creditHours;
			string gradeEarned;

			//If there is a alpha designator, there is a course
			if (student.course[i].alphaDesignator != "")
			{
				//If were not on the last one, print a space at the end for formatting
				if (i < CLASS_COUNT - 1)
				{
					myfile << student.course[i].alphaDesignator << endl;
					myfile << student.course[i].courseNumber << endl;
					myfile << student.course[i].courseTitle << endl;
					myfile << student.course[i].creditHours << endl;
					myfile << student.course[i].gradeEarned << endl;
				}
				//Else dont print a space, because load database will get messed up
				else
				{
					myfile << student.course[i].alphaDesignator << endl;
					myfile << student.course[i].courseNumber << endl;
					myfile << student.course[i].courseTitle << endl;
					myfile << student.course[i].creditHours << endl;
					myfile << student.course[i].gradeEarned;
				}
			}

		}
	
	}
	
	cout << "\nDatabase saved to StudentInfo.txt" << endl;
	
	//Close the file
	myfile.close();

}

/***********************************************************
Function: loadDatabase
Reference to student from main
Postcondition:
Loads all the data and sets it to the student
************************************************************/
void loadDatabase(student& student)
{

	//File to read from
	ifstream inFile;
	inFile.open("StudentInfo.txt");
	
	//If the file doesnt exist
	if (!inFile) 
	{
		cout << "Cannot open file! Are you sure it exist?";
		exit(1); //exit
	}
	//Else it does exist
	else 
	{
		//Variables to get
		string studentName;
		double gpa;

		//Gets the student name
		//And gets the GPA
		getline(inFile, studentName);
		inFile >> gpa;

		//Sets the name and GPA
		student.name = studentName;
		student.gpa = gpa;

		//Counter for entry
		int counter = 0;
		
		//While there is still data
		while (inFile.peek() != EOF)
		{

			//Variables to get
			string courseTitle;
			string alphaDesignator;
			string gradeEarned;
			int creditHours;
			int courseNumber;

			//Gets the alpha and number
			inFile >> alphaDesignator;
			inFile >> courseNumber;

			//Clears the getline before it is used
			inFile.clear();
			inFile.ignore(100, '\n');

			//Gets the title, credit hours, and grade
			getline(inFile, courseTitle);
			inFile >> creditHours;
			inFile >> gradeEarned;

			//Sets the current course data
			student.course[counter].alphaDesignator = alphaDesignator;
			student.course[counter].courseNumber = courseNumber;
			student.course[counter].courseTitle = courseTitle;
			student.course[counter].creditHours = creditHours;
			student.course[counter].gradeEarned = gradeEarned;

			//Add one so the loop will know which index to add the data to
			counter++;

		}

		//Class count is the counter
		CLASS_COUNT = counter;
	
		cout << "\nDatabase loaded!" << endl;

	}
}
