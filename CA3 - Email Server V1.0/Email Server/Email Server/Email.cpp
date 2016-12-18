#include "Email.h"
#include <sstream>
#include <regex>

using std::stringstream;
using std::regex;
using std::regex_match;

Email::Email()
{

}

Email::Email(string sender, vector<string> recipients, time_t dateTime, string subject, string body, vector<Attachment> attachments)
{
	// Required Validations:
	// sender - valid email regex
	// recipients - valid emails regex
	// dateTime - valid time object
	// subject - optional requirement
	// body - length >= 1 character
	// attachments -properly created objects of attachment class objects
}

string Email::getSender() const
{
	return sender;
}

void Email::setSender(const string &sender)
{
	regex regex("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+"); // email regex here
	if (regex_match(sender, regex))
	{
		this->sender = sender;
	}
	else
	{
		this->sender = "defaultSender@mail.com";
	}
}

string Email::getRecipients() const
{
	return recipients;
}


void Email::setRecipients(const string recipients)
{
	regex regex("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+"); // email regex here
	bool validEmails = true;
	string recs = recipients;
	string mail;
	while (recs != "")
	{
		mail = recs.substr(0, recs.find_first_of(';'));
		if (!regex_match(mail, regex))
		{
			validEmails = false;
		}
		recs.substr(recs.find_first_of(';') + 1);

	}
	
	if (validEmails)
	{
		this->recipients = recipients;
	}
	else
	{
		this->recipients = "defaultUser@mail.com";
	}
}

time_t Email::getDateTime() const 
{
	return dateTime;
}

void Email::setDateTime(const time_t &dateTime)
{
	// setting up time struct to analyse the time object passed in
	struct tm * ptm;
	ptm = gmtime(&dateTime);
	// if the value of year is pre-1969 for epoch year 1970, then it is not a valid time object
	if (ptm->tm_year > 1969)
	{
		// can safely set the valid time to this object
		this->dateTime = dateTime;
	}
	else
	{
		// set to current time right now if not valid
		time(&this->dateTime);
	}
}

string  Email::getSubject() const
{
	return subject;
}

void Email::setSubject(const string &subject)
{
	this->subject = subject;
}

string Email::getBody() const
{
	return body;
}

void Email::setBody(const string &body)
{
	if (body.length() >= 1)
	{
		this->body = body;
	}
	else
	{
		this->body = "Default Body";
	}
}

vector<Attachment> Email::getAttachments() const
{
	return attachments;
}

void Email::setAttachments(const vector<Attachment> &attachments)
{
	this->attachments = attachments;
}

string Email::print()
{
	// converting time to valid time format as string later
	stringstream st;
	st << dateTime;

	time_t t = dateTime;
	time(&t);
	stringstream time;
	time << t;
	// getting out file attachement information
	int count = 0;
	string attach = "";

	for (Attachment a : attachments)
	{
		if (count == 0)
		{
			attach += (a.getFileName() + "." + a.getFileSuffix());
		}
		else
		{
			attach += ", " + (a.getFileName() + "." + a.getFileSuffix());
		}
		count++;
	}
	count = 0;

	return "Email: [ sender = " + sender + " Recipients = "  + recipients + " Time Created = " + time.str()  + " Subject = " + subject + " Body = " + body + " Attachements = " + " ]";
}
Email::~Email()
{
}
