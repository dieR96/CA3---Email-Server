#pragma once
#include <string>

using std::string;


// still need operator overloading functions
// still need copy constructor
class Attachment
{
private:
	string fileName;
	string fileSuffix;
	char* fileData; // Pointer to array, get size from file
	int size; // size of file data
public:
	Attachment();
	Attachment(string fileName, string fileSuffix, char fileData[], int size);
	string getFileName() const;
	void setFileName(const string &fileName);
	string getFileSuffix() const;
	void setFileSuffix(const string &fileSuffix);
	string getFileData() const;
	void setFileData(char data[], int size); // not sure about file data using a char, use string and convert to char in functions
	string print() const;
	~Attachment();
};

