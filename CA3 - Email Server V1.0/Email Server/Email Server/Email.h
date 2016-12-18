#pragma once
#include <string>
#include <vector>
#include <ctime>
#include "Attachment.h"

using std::string;
using std::vector;


// still need operator overloading functions
// still need copy constructor
class Email
{
private:
	string sender;
	string recipients; // need to use non-vector item, maybe a list?
	time_t dateTime; // stores time and needs to be read into stringbuffer then tostring on that to see string of time, use now(0) to get current time into it
	string subject;
	string body;
	vector<Attachment> attachments; // using related class in attachment.h
public:
	Email();
	Email(string sender, vector<string> recipients, time_t dateTime, string subject, string body, vector<Attachment> attachments);
	string getSender() const;
	void setSender(const string &sender);
	string getRecipients() const;
	void setRecipients(const string recipients);
	time_t getDateTime() const;
	void setDateTime(const time_t &dateTime);
	string  getSubject() const;
	void setSubject(const string &subject);
	string getBody() const;
	void setBody(const string &body);
	vector<Attachment> getAttachments() const;
	void setAttachments(const vector<Attachment> &attachments);
	string print();
	~Email();
};

