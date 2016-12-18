#include "Email.h"
#include <sstream>
#include <regex>

using std::stringstream;
using std::regex;
using std::regex_match;

// default constructor
Email::Email()
{
	setSender("defaultSender@mail.com");
	setRecipients("defaultUser@mail.com");
	time_t currentTime;
	setDateTime(time(&currentTime));
	setSubject("");
	setBody("Default Body");
	Attachment attachment;
	setAttachment(attachment);

}

// parameterised constructor
Email::Email(string sender, string recipients, time_t dateTime, string subject, string body, Attachment& attachment)
{
	setSender(sender);
	setRecipients(recipients);
	setDateTime(dateTime);
	setSubject(subject);
	setBody(body);
	setAttachment(attachment);
}

// overloaded copy constructor
Email::Email(const Email &email)
{
	setSender(email.sender);
	setRecipients(email.recipients);
	setDateTime(email.dateTime);
	setSubject(email.subject);
	setBody(email.body);
	setAttachment(email.attachment);
}

// overloaded assignment operator
void Email::operator=(const Email &email)
{
	setSender(email.sender);
	setRecipients(email.recipients);
	setDateTime(email.dateTime);
	setSubject(email.subject);
	setBody(email.body);
	setAttachment(email.attachment);
}

bool Email::operator==(const Email &email)
{
	if (this->sender == email.sender && this->recipients == email.recipients && this->dateTime == email.dateTime && this->subject == email.subject && this->body == email.body && this->attachment == email.attachment)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Email::operator!=(const Email &email)
{
	if (this->sender != email.sender || this->recipients != email.recipients || this->dateTime != email.dateTime || this->subject != email.subject || this->body != email.body || this->attachment != email.attachment)
	{
		return true;
	}
	else
	{
		return true;
	}
}

ostream& operator<<(ostream &out, const Email &email)
{
	out << "Email = Sender: " << email.sender << " Recipients: " << email.recipients << " date created: " << email.getDateTime() << " Subject: " << email.subject << " Body: " << email.body << " Attachment: " << email.attachment.print();
	return out;
}

istream& operator>>(const istream &in, Email &email)
{
	// using a static cast to get non-constant istream out
	istream* input = const_cast<istream*>(&in);
	
	string garbage;
	*input >> email.sender;
	*input >> garbage;
	*input >> email.recipients;
	*input >> garbage;
	*input >> email.dateTime;
	*input >> garbage;
	*input >> email.subject;
	*input >> garbage;
	*input >> email.body;
	*input >> garbage;
	*input >> email.attachment;
	*input >> garbage;
	return *input;
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
		recs = recs.substr(recs.find_first_of(';') + 1);

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

string Email::getDateTime() const 
{
	return ctime(&dateTime);
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

Attachment Email::getAttachment() const
{
	return attachment;
}

void Email::setAttachment(const Attachment &attachment)
{
	this->attachment = attachment;
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


	return "Email: [ sender = " + sender + " Recipients = "  + recipients + " Time Created = " + time.str()  + " Subject = " + subject + " Body = " + body + " Attachment = " + attachment.print() + " ]";
}
Email::~Email()
{
}
