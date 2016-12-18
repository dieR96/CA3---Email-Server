#pragma once

#include <string>
#include <iostream>

using std::ostream;
using std::istream;
using std::cin;
using std::cout;
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
	User(const User &user);
	void operator=(const User &user);
	bool operator==(const User &user);
	bool operator!=(const User &user);
	friend ostream& operator<<(ostream &out,const User &user);
	friend istream& operator>>(const istream &in, User &user);

	string getEmail() const;
	void setEmail(const string& email);
	string getPassword() const;
	void setPassword(const string &password);
	string getUserName() const;
	void setUserName(const string &userName);
	string print() const;
	~User();
};

