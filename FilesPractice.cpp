// FilesPractice.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>

using namespace std;

struct Record {
		std::string name;
		int nameSize;
		int age;
	};

	int* index; //Array for record indexes
	int recordCount; //num of records
	std::string filename = "testData.dat";

	void CreateFile(string filename);
	void IndexFile(string filename);
	void PrintFile(string filename);
	void PrintRecord(string filename, int index);
	void PrintRecord(Record* r);

int main()
{
	//Create file and add some records
	CreateFile(filename);
	//Read records from file and print to console
	PrintFile(filename);
	//Get start of each record and populate index array
	IndexFile(filename);
	//use index array to print record and index 2
	PrintRecord(filename, 2);
}

void CreateFile(string filename)
{
	//create some records
	Record* r1 = new Record();
	r1->name = "Ollie";
	r1->age = 15;
	r1->nameSize = (int)r1->name.size();

	Record* r2 = new Record();
	r2->name = "James";
	r2->age = 18;
	r2->nameSize = (int)r2->name.size();
	
	Record* r3 = new Record();
	r3->name = "Ann";
	r3->age = 25;
	r3->nameSize = (int)r3->name.size();

	//set record count
	recordCount = 3;

	//open file to write
	ofstream outfile(filename, ios::binary);

	//first write the record count
	outfile.write((char*)&recordCount, sizeof(int));

	//print each record to console then write to file
	std::cout << "Name: " << r1->name << "Age: " << r1->age << "\n";
	outfile.write((char*)&r1->nameSize, sizeof(int));
	outfile.write((char*)r1->name.c_str(), r1->nameSize);
	outfile.write((char*)&r1->age, sizeof(int));

	std::cout << "Name: " << r2->name << "Age: " << r2->age << "\n";
	outfile.write((char*)&r2->nameSize, sizeof(int));
	outfile.write((char*)r2->name.c_str(), r2->nameSize);
	outfile.write((char*)&r2->age, sizeof(int));

	std::cout << "Name: " << r3->name << "Age: " << r3->age << "\n";
	outfile.write((char*)&r3->nameSize, sizeof(int));
	outfile.write((char*)r3->name.c_str(), r3->nameSize);
	outfile.write((char*)&r3->age, sizeof(int));

	//close file
	outfile.close();
}

void IndexFile(string filename)
{
	//open the file
	ifstream infile(filename, ios::binary);

	//get the record count
	infile.read((char*)&recordCount, sizeof(int));

	//setup array with length of recordCount
	index = new int[recordCount];

	//create placeholder record
	Record* r = new Record();
	
	//for as many records
	for(int i = 0; i < recordCount; i++)
	{
		//store the current location in the file to the array
		index[i] = infile.tellg();

		//read the rest of the entry
		infile.read((char*)&r->nameSize, sizeof(int));
		int size = r->nameSize;
		char* name1 = new char[size + 1];
		infile.read((char*)name1, size);
		r->name = name1;
		infile.read((char*)&r->age, sizeof(int));
	}
}

void PrintRecord(string filename, int record)
{
	//open the file
	ifstream infile(filename, ios::binary);

	//move to the the location for the start of the record as in the index array
	infile.seekg(index[record]);

	//create a new record
	Record* r1 = new Record();

	//read the data and update record
	infile.read((char*)&r1->nameSize, sizeof(int));
	int size = r1->nameSize;
	char* name1 = new char[size + 1];
	name1[size] = '\0';

	infile.read((char*)name1, size);

	r1->name = name1;
	infile.read((char*)&r1->age, sizeof(int));

	//print our finished record
	PrintRecord(r1);

}

void PrintFile(string filename)
{
	//open file to read
	ifstream infile(filename, ios::binary);

	//get the record count
	infile.read((char*)&recordCount, sizeof(int));
	
	//create placeholder record
	Record* r1 = new Record();
	
	for (int i = 0; i < recordCount; i++)
	{
		//read data and store as record
		infile.read((char*)&r1->nameSize, sizeof(int));
		int size = r1->nameSize;
		char* name1 = new char[size + 1];
		name1[size] = '\0';

		infile.read((char*)name1, size);

		r1->name = name1;
		infile.read((char*)&r1->age, sizeof(int));

		//print the record
		PrintRecord(r1);
	}

	//close the file
	infile.close();
}

void PrintRecord(Record* r)
{
	std::cout << "Name: "<< r->name << " Age: " << r->age << "\n";
}