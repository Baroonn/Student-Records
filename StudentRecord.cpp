/* 
	Name of Programmer: Bolaji Boluwatife
	Date of Completion: August 6, 2020.
	Version: 0.1
	About: 	This program was written to keep records of a student
			in a particular educational institution. This version
			allows the user to add a student to the record, check 
			for a particular student and also to output a list of
			all the students presently in the institution.
*/
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <exception>
#include <stdexcept>

using namespace std;

//class containing data for a student
struct New_Student
{
	New_Student()
		:firstName("EMPTY"), lastName("EMPTY"), course("EMPTY")
		{}
	string firstName;
	string lastName;
	string course;	
};

void createStudent()
{
	New_Student student; //create a new object
	cout<<"Enter first name: ";
	cin>>student.firstName;
	cout<<"Enter last name: ";
	cin>>student.lastName;
	cout<<"Enter current course: ";
	cin>>student.course;
	//open "StudentRecords.txt" as an output file to append to
	ofstream f("C:\\Users\\Bolaji\\Documents\\DevC++\\StudentRecords.txt", ios_base::app);
	//append to file "StudentRecords.txt" in a specified format
	f<<"\n[ "<<student.firstName<<" , "<<student.lastName<<" , "<<student.course<<" ]";	
}

void checkStudent()
{
	//open "StudentRecords.txt" as an input file
	ifstream f("C:\\Users\\Bolaji\\Documents\\DevC++\\StudentRecords.txt");
	cout<<"Enter the first or last name of the student\n";
	cout<<"whose records you would like to check:\n";
	string name;
	cin>>name;
	int count=0;//position of student's record in the file (starting from 0)
	int count1=0;//number of records found
	while(!f.eof())//while not end of file
	{
		vector<string> v(7);
		for(int i=0;i<7;i++)f>>v[i];
		//in case the file has been tampered with
		if(v[0]!="[" || v[6]!="]" || v[2]!= "," || v[4] != ",")throw runtime_error("Corrupt file");
		//if the name user inputed is a first or last name of a student in the record:
		if(name==v[1] || name== v[3])
		{
			cout<<"Record "<<count<<":"<<endl;
			cout<<"First Name:"<<v[1]<<endl;
			cout<<"Last Name:"<<v[3]<<endl;
			cout<<"Course Studied: "<<v[5]<<"\n\n";
			++count1;//increase the number of records found
		}
		++count;
	}
	//if computer reaches the end of file and no record was found, tell the user
	if(f.eof() && count1 == 0)cout<<"No records found"<<endl;
}

void displayRecords()
{
	ifstream f("C:\\Users\\Bolaji\\Documents\\DevC++\\StudentRecords.txt");
	int count=0;//position of student's record and number of records found
	while(!f.eof())
	{
		vector<string> v(7);
		for(int i=0;i<7;i++)f>>v[i];
		//in case the file has been tampered with
		if(v[0]!="[" || v[6]!="]" || v[2]!= "," || v[4] != ",")throw runtime_error("Corrupt file");
		cout<<"Record "<<count<<":"<<endl;
		cout<<"First Name: "<<v[1]<<endl;
		cout<<"Last Name: "<<v[3]<<endl;
		cout<<"Course Studied: "<<v[5]<<"\n\n";
		++count;
	}
	//If no record in the file, tell the user
	if(f.eof() && count == 0)cout<<"No records found"<<endl;
}

void editRecords()
{
	fstream f;
	//open "StudentRecords.txt" as an input file
	f.open("C:\\Users\\Bolaji\\Documents\\DevC++\\StudentRecords.txt", ios_base::in);
	//a container of students created from "StudentRecords.txt"
	vector<New_Student> students;
	int record=0;
	while (!f.eof())
	{
		vector<string> v(7);
		for(int i=0;i<7;i++)f>>v[i];
		//in case the file has been tampered with
		if(v[0]!="[" || v[6]!="]" || v[2]!= "," || v[4] != ",")throw runtime_error("Corrupt file");
		//notice removal of 's' for a single object/student
		New_Student student;
		student.firstName=v[1];
		student.lastName=v[3];
		student.course=v[5];
		students.push_back(student);
	}
	f.close();//close "StudentRecords.txt"
	cout<<"Which record would you like to edit?"<<endl;
	cin>>record;
	cout<<"Enter First Name: ";
	cin>>students[record].firstName;
	cout<<"Enter Last Name: ";
	cin>>students[record].lastName;
	cout<<"Enter Course: ";
	cin>>students[record].course;
	//reopen "StudentRecords.txt" as an output file
	f.open("C:\\Users\\Bolaji\\Documents\\DevC++\\StudentRecords.txt", ios_base::out);
	for(int i=0;i<students.size();i++)
		f<<"\n[ "<<students[i].firstName<<" , "<<students[i].lastName<<" , "<<students[i].course<<" ]";
	f.close();
}

int main()
try{
	string ichoice;
	cout<<"Pick an action you would like to perform:\n";
	cout<<"1. Create a new student\n";
	cout<<"2. Check student records\n";
	cout<<"3. Display all student records\n";
	for(;;)
	{
	cin>>ichoice;//Take input as a string
	//Check against input with more than one character and input that is not a number
	if(ichoice.size()>1 || !isdigit(ichoice[0]))cout<<"Wrong Input!"<<endl;
	else
	{
	switch (ichoice[0])
	{
		case '1':
			createStudent();
			break;
		case '2':
		{
			checkStudent();
			cout<<"Would you like to edit a record?y/n"<<endl;
			char ans;
			cin>>ans;
			if(ans=='y')editRecords();
			break;
		}
		case '3':
			displayRecords();
			cout<<"Would you like to edit a record?y/n"<<endl;
			char ans;
			cin>>ans;
			if(ans=='y')editRecords();
			break;
		default:
			//last check against wrong input
			cout<<"Not a choice!\n";
			break;
	}
	}
	//if correct input was given, end program; else ask for input again
	if(ichoice=="1" || ichoice=="2" || ichoice == "3")break;
	}	
	return 0;
}

catch(exception& e)
{
	cerr<<"Error: "<<e.what()<<endl;
}
