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

	int* index;
	int maxRecords;
	int recordCount;
	std::string filename = "testData.dat";

	void CreateFile(string filename);
	void IndexFile(string filename);
	void PrintFile(string filename);
	void PrintRecord(string filename, int index);
	void PrintRecord(Record* r);

int main()
{
    std::cout << "Hello World!\n";

	CreateFile(filename);
	//PrintFile(filename);
	IndexFile(filename);
	PrintRecord(filename, 2);

	
}

void CreateFile(string filename)
{
	Record* r1 = new Record();
	Record* r2 = new Record();
	Record* r3 = new Record();

	r1->name = "Ollie";
	r1->age = 15;
	r1->nameSize = (int)r1->name.size();
	r2->name = "James";
	r2->age = 18;
	r2->nameSize = (int)r2->name.size();
	r3->name = "Ann";
	r3->age = 25;
	r3->nameSize = (int)r3->name.size();

	recordCount = 3;

	ofstream outfile(filename, ios::binary);
	outfile.write((char*)&recordCount, sizeof(int));

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

	outfile.close();

}

void IndexFile(string filename)
{
	ifstream infile(filename, ios::binary);
	infile.read((char*)&recordCount, sizeof(int));

	index = new int[recordCount];

	Record* r = new Record();
	
	for(int i = 0; i < recordCount; i++)
	{
		index[i] = infile.tellg();
		infile.read((char*)&r->nameSize, sizeof(int));
		int size = r->nameSize;
		char* name1 = new char[size + 1];
		name1[size] = '\0';

		infile.read((char*)name1, size);

		r->name = name1;
		infile.read((char*)&r->age, sizeof(int));
	}
}

void PrintRecord(string filename, int record)
{
	ifstream infile(filename, ios::binary);

	infile.seekg(index[record]);

	Record* r1 = new Record();

	infile.read((char*)&r1->nameSize, sizeof(int));
	int size = r1->nameSize;
	char* name1 = new char[size + 1];
	name1[size] = '\0';

	infile.read((char*)name1, size);

	r1->name = name1;
	infile.read((char*)&r1->age, sizeof(int));

	PrintRecord(r1);

}

void PrintFile(string filename)
{
	ifstream infile(filename, ios::binary);

	infile.read((char*)&recordCount, sizeof(int));

	std::cout << recordCount << "\n";

	Record* r1 = new Record();
	
	infile.read((char*)&r1->nameSize, sizeof(int));
	int size = r1->nameSize;
	char* name1 = new char[size + 1];
	name1[size] = '\0';
	
	infile.read((char*)name1, size);

	r1->name = name1;
	infile.read((char*)&r1->age, sizeof(int));

	PrintRecord(r1);

	Record* r2 = new Record();
	
	infile.read((char*)&r2->nameSize, sizeof(int));
	size = r2->nameSize;
	char* name2 = new char[size + 1];
	name2[size] = '\0';

	infile.read((char*)name2, size);

	r2->name = name2;
	infile.read((char*)&r2->age, sizeof(int));

	PrintRecord(r2);

	Record* r3 = new Record();

	infile.read((char*)&r3->nameSize, sizeof(int));
	size = r3->nameSize;
	char* name3 = new char[size + 1];
	name3[size] = '\0';

	infile.read((char*)name3, size);

	r3->name = name3;
	infile.read((char*)&r3->age, sizeof(int));

	PrintRecord(r3);

	infile.close();
}

void PrintRecord(Record* r)
{
	std::cout << "Name: "<< r->name << "Age: " << r->age << "\n";
}