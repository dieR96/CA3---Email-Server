#pragma once

#include <string>

using std::string;


// still need operator overloading functions
// still need copy constructor
class User
{
private:
	string email;
	string userName;
	string password;
public:
	User();
	User(string email, string userName, string password);
	string getEmail() const;
	void setEmail(const string& email);
	string getPassword() const;
	void setPassword(const string &password);
	string getUserName() const;
	void setUserName(const string &userName);
	string print() const;
	~User();
};

