/* regex code sources gathered from:
* http://stackoverflow.com/questions/13122492/regular-expression-for-valid-folder-name-c-windows on 27/11/2016 - 2:12 AM
* https://regex101.com/ on 27/11/2016 - used regularly for testing generated regex's written
 for reading in a file size : http://stackoverflow.com/questions/5840148/how-can-i-get-a-files-size-in-c */

#include "Attachment.h"
#include <regex>
#include <iostream>
#include <fstream>

using std::regex;
using std::regex_match;
using std::cout;
using std::ifstream;
using std::istreambuf_iterator;



Attachment::Attachment()
{
}



Attachment::Attachment(const Attachment& att)
{
	this->size = att.size;
	setFileName(att.fileName);
	setFileSuffix(att.fileSuffix);
	fileData = new char[att.size];
	for (int i = 0; i < att.size; i++)
	{
		this->fileData[i] = att.fileData[i];
	}
}

void Attachment::operator=(const Attachment& att)
{
	this->size = att.size;
	setFileName(att.fileName);
	setFileSuffix(att.fileSuffix);
	fileData = new char[att.size];
	for (int i = 0; i < att.size; i++)
	{
		this->fileData[i] = att.fileData[i];
	}
}

Attachment::Attachment(string fileName, string fileSuffix, string file)
{
	this->size = size;
	setFileName(fileName);
	setFileSuffix(fileSuffix);
	setFileData(file);

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
	regex regex("[a-zA-Z1-9]{1,}"); // Windows FileName regex here
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
	regex regex("[a-zA-Z][a-zA-Z][a-zA-Z]?"); // Windows File extension regex here
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

void Attachment::setFileData(string file) // not sure about file data using a char, use string and convert to char in functions
{
	// check that the fileData char stream is not empty
	ifstream in(file);

	if (in)
	{
		// read in the file into a streambuffer and iterate through the file to read it in
		string contents((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());

		fileData = new char[contents.length()];
		this->size = contents.length();
		//fileData = strcpy(fileData, contents.c_str());
		for (int i = 0; i < this->size; i++)
		{
			this->fileData[i] = contents[i];
		}
		// testing the file data is in the char array

		cout << "File Data = " << fileData[0];
		for (int i = 1; i < contents.length(); i++)
		{
			cout << ", " << fileData[i];
		}

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
	delete [] fileData;
	fileData = 0;
}
