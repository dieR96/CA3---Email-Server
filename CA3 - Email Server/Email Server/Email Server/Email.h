#pragma once
#include <string>
#include <vector>
#include <ctime>
#include <iostream>
#include "Attachment.h"

using std::istream;
using std::ostream;
using std::string;
using std::vector;

class Email
{
private:
	string sender;
	string recipients;
	time_t dateTime; // stores time and needs to be read into stringbuffer then tostring on that to see string of time, use now(0) to get current time into it
	string subject;
	string body;
	Attachment attachment; // using related class in attachment.h
public:
	Email();
	Email(string sender, string recipients, time_t dateTime, string subject, string body, Attachment& attachment);
	Email(const Email &email);
	void operator=(const Email &email);
	bool operator==(const Email &email);
	bool operator!=(const Email &email);
	friend ostream& operator<<(ostream &out, const Email &email);
	friend istream& operator>>(const istream &in, Email &email);
	string getSender() const;
	void setSender(const string &sender);
	string getRecipients() const;
	void setRecipients(const string recipients);
	string getDateTime() const;
	time_t getRawDateTime() const;
	void setDateTime(const time_t &dateTime);
	string  getSubject() const;
	void setSubject(const string &subject);
	string getBody() const;
	void setBody(const string &body);
	Attachment getAttachment() const;
	void setAttachment(const Attachment &attachments);
	string print();
	~Email();
};

