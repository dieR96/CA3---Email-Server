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
	char fileData[1000000]; // don't know about defining right size char array for file contents size
public:
	Attachment();
	Attachment(string fileName, string fileSuffix, char fileData[1000000]);
	string getFileName() const;
	void setFileName(const string &fileName);
	string getFileSuffix() const;
	void setFileSuffix(const string &fileSuffix);
	string getFileData() const;
	void setFileData(const string &fileData); // not sure about file data using a char, use string and convert to char in functions
	string print() const;
	~Attachment();
};

