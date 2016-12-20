#pragma once

#include <string>
#include <iostream>

using std::string;
using std::istream;
using std::ostream;


class Attachment
{
private:
	string fileName;
	string fileSuffix;
	char* fileData; // Pointer to array, get size from file
	int size; // size of file data
public:
	Attachment();
	Attachment(string fileName, string fileSuffix, string file);
	Attachment(const Attachment &att);
	void operator=(const Attachment &att);
	bool operator==(const Attachment &att);
	bool operator!=(const Attachment &att);
	friend ostream& operator<<(ostream &out, const Attachment &att);
	friend istream& operator>>(const istream &in, Attachment &att);
	string getFileName() const;
	void setFileName(const string &fileName);
	string getFileSuffix() const;
	void setFileSuffix(const string &fileSuffix);
	string getFileData() const;
	void setFileData(string file); // not sure about file data using a char, use string and convert to char in functions
	string print() const;
	~Attachment();
};

