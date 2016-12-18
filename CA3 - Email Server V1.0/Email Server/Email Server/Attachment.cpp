// regex code sources gathered from:
// http://stackoverflow.com/questions/13122492/regular-expression-for-valid-folder-name-c-windows on 27/11/2016 - 2:12 AM
// https://regex101.com/ on 27/11/2016 - used regularly for testing generated regex's written


#include "Attachment.h"
#include <regex>

using std::regex;
using std::regex_match;


Attachment::Attachment()
{

}

Attachment::Attachment(string fileName, string fileSuffix, char fileData[1000000])
{
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
	regex regex("^(?!(?:CON|PRN|AUX|NUL|COM[1-9]|LPT[1-9])(?:\.[^.]*)?$)[^<>:" / \\ | ? *\x00 - \x1F] * [^<>:"/\\|?*\x00-\x1F\ .]$"); // Windows FileName regex here
	if (regex_match(fileName, regex))
	{
		this->fileName = fileName;
	}
	else
	{
		this->fileName = "defaultFileName";
	}
}

string Attachment::getFileSuffix() const
{
	return fileSuffix;
}

void Attachment::setFileSuffix(const string &fileSuffix)
{
	regex regex("[a-z][a-z][a-z]?|[A-Z][A-Z][A-Z]?"); // Windows FileName regex here
	if (regex_match(fileSuffix, regex))
	{
		this->fileSuffix = fileSuffix;
	}
	else
	{
		this->fileName = "defaultFileName";
	}
	
}

string Attachment::getFileData() const
{
	return fileData;
}

void Attachment::setFileData(const string &fileData) // not sure about file data using a char, use string and convert to char in functions
{
	if (fileData.length() > 0)
	{
		strcpy(this->fileData, fileData.c_str());
	}
	else
	{
		this->fileData[0] = 'D';
		this->fileData[1] = 'E';
		this->fileData[2] = 'F';
		this->fileData[3] = 'A';
		this->fileData[4] = 'U';
		this->fileData[5] = 'L';
		this->fileData[6] = 'T';
	}
}

string Attachment::print() const
{
	return "Attachment: [ File Name = " + fileName + "." + fileSuffix + " file contents: = " + fileData + " ]";
}

Attachment::~Attachment()
{
}
