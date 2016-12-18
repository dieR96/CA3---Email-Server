// regex code sources gathered from:
// http://stackoverflow.com/questions/13122492/regular-expression-for-valid-folder-name-c-windows on 27/11/2016 - 2:12 AM
// https://regex101.com/ on 27/11/2016 - used regularly for testing generated regex's written
/* for reading in a file size : http://stackoverflow.com/questions/5840148/how-can-i-get-a-files-size-in-c */

#include "Attachment.h"
#include <regex>
#include <iostream>

using std::regex;
using std::regex_match;
using std::cout;

Attachment::Attachment()
{
}

Attachment::Attachment(string fileName, string fileSuffix, char fileData[], int size)
{
	this->size = size;
	setFileName(fileName);
	setFileSuffix(fileSuffix);
	setFileData(fileData, size);
	

	// Required Validations:
	// fileName - regex valid windows file name
	// fileSuffix - regex 2-3 character alphanumeric suffix
	// fileData - non-null character stream
}

string Attachment::getFileName() const
{
	return fileName;
}

void Attachment::setFileName(const string &fileName)
{
	// regex for valid windows file name
	regex regex("[a-z]{1,}|[A-Z]{1,}"); // Windows FileName regex here
	if (regex_match(fileName, regex))
	{
		this->fileName = fileName;
	}
	else
	{
		this->fileName = "default";
	}
}

string Attachment::getFileSuffix() const
{
	return fileSuffix;
}

void Attachment::setFileSuffix(const string &fileSuffix)
{
	// regex for valid 2-3 character alphanumeric suffix
	regex regex("[a-z][a-z][a-z]?|[A-Z][A-Z][A-Z]?"); // Windows File extension regex here
	if (regex_match(fileSuffix, regex))
	{
		this->fileSuffix = fileSuffix;
	}
	else
	{
		this->fileName = "txt";
	}
	
}

string Attachment::getFileData() const
{
	return fileData;
}

void Attachment::setFileData(char data[], int size) // not sure about file data using a char, use string and convert to char in functions
{
	// check that the fileData char stream is not empty
	if (size > 0)
	{
		fileData = data;
	}
	else
	{
		fileData = new char[7];
		this->size = 7;
		fileData[0] = 'D';
		fileData[1] = 'E';
		fileData[2] = 'F';
		fileData[3] = 'A';
		fileData[4] = 'U';
		fileData[5] = 'L';
		fileData[6] = 'T';
	}
}

string Attachment::print() const
{
	string fileContent = "";

	for (int i = 0; i < size; i++)
	{
		fileContent += fileData[i];
	}

	return "Attachment: [ File Name = " + fileName + "." + fileSuffix + " file contents: = " + fileContent + " ]";
}

Attachment::~Attachment()
{
}
