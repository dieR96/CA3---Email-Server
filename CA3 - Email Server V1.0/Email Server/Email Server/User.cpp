// regex code sources gathered from:
// http://stackoverflow.com/questions/36903985/email-validation-in-c on 27/11/16 - 2:03AM
// http://stackoverflow.com/questions/19605150/regex-for-password-must-be-contain-at-least-8-characters-least-1-number-and-bot on 27/11/16 - 2:07AM

#include "User.h"
#include <regex>

using std::regex;
using std::regex_match;

User::User()
{

}

User::User(string email, string userName, string password)
{
	// Required Validations:
	// email - valid email regex
	// userName - length >= 8
	// password - length >= 8 and at least 1 number, not case-sensitive
}

string User::getEmail() const
{

	return email;
}

void User::setEmail(const string& email)
{
	regex regex("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+"); // email regex here
	if (regex_match(email, regex))
	{
		this->email = email;
	}
	else
	{
		this->email = "defaultUser@mail.com";
	}
}

string User::getPassword() const
{
	return password;
}

void User::setPassword(const string& password)
{
	regex regex("^(?=.*[a-z])(?=.*[A-Z])(?=.*\d)[a-zA-Z\d]{8,}$"); // password regex here - 1 uppercase, lowercase and number regex
	if (regex_match(password, regex))
	{
		this->password = password;
	}
	else
	{
		this->password = "defaultPassword1";
	}
}

string User::getUserName() const
{
	return userName;
}

void User::setUserName(const string& userName)
{
	if (userName.length() >= 8)
	{
		this->userName = userName;
	}
	else
	{
		this->userName = "Default User";
	}
}

string User::print() const
{
	return "User: [ email = " + email + " User Name = " + userName + " Password = " + password  + " ]";
}

User::~User()
{
}
