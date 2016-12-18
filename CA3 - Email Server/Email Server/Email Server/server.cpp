#include "User.h"
#include "server.h"
#include <iostream>
#include <string>
#include <map>
#include <set>
#include <list>
#include <algorithm>
#include "TemplateQueue.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::getline;
using std::stoi;
using std::map;
using std::list;
using std::all_of;
using std::any_of;
using std::none_of;
using std::invalid_argument;

// houses all emails related to each user
map<string, list<Email*>> userEmails;
// stores users in the file, won't be reset when user resets the server
map<string, User> users;
// holds data about the results of searches, global here to have easy access
list<Email*> results;
// holds created emails not yet sent to their recipents, cleared when user calls sends all pending emails
list<Email*> drafts;
// creates a queue for storing the data for sending out after creating some emails and store here before sending all of them at once in send emails function
TemplateQueue<Email*> sendCache;

// global variables that hold the current input from the user and email account they wish to view in the various functions
string input;
string targetEmail;


// this file will house functions for each operation such as add, delete, delete all, etc, these functions will be called in the menu to keep menu to one function and tidy


// function shows the looping main menu for the program, this will call the other functions in the server for operations the user has selected
void mainMenu()
{
	// call function to set up data in the program initially, data is not saved in the program yet, so all changes and restart of the program reset all data
	initialData();


	cout << "______ _     ___  ___      _ _   _____ _____   _____                          " << endl;
	cout << "|  _  \\ |    |  \\/  |     (_) | |_   _|_   _| /  ___|                         " << endl;
	cout << "| | | | | __ | .  . | __ _ _| |   | |   | |   \\ `--.  ___ _ ____   _____ _ __ " << endl;
	cout << "| | | | |/ / | |\\/| |/ _` | | |   | |   | |    `--. \\/ _ \\ '__\\ \\ / / _ \\ '__|" << endl;
	cout << "| |/ /|   <  | |  | | (_| | | |  _| |_  | |   /\\__/ /  __/ |   \\ V /  __/ |   " << endl;
	cout << "|___/ |_|\\_\\ \\_|  |_/\\__,_|_|_|  \\___/  \\_/   \\____/ \\___|_|    \\_/ \\___|_|   " << endl;
	cout << "MX server ver. 1.34" << endl << endl;
	cout << "Welcome To DkMailIT!" << endl;
	cout << "Licenced to MyMail Ltd. since 2016" << endl << endl << endl;


	string word;
	int choice = 0;

	do
	{
		cout << "Main Menu" << endl;
		cout << "Please select what you would like to do:" << endl << endl << endl;
		cout << " > 1. New email" << endl;
		cout << " > 2. Send email" << endl;
		cout << " > 3. View previous emails" << endl;
		cout << " > 4. Delete specific email" << endl;
		cout << " > 5. Delete all emails" << endl;
		cout << " > 6. Search emails menu" << endl; // by date, subject or hasAttachements
		cout << " > 7. Reset emails" << endl; // delete all objects assigned in the program
		cout << " > 8. Exit" << endl;
		getline(cin, word);

		try 
		{
			choice = stoi(word);
		}
		catch (const invalid_argument& ia) 
		{
			cout << "Please enter in a number from 1-8 for you selection" << endl;
			//cout << "Invalid argument: " << ia.what() << endl;
			choice = 0;
		}

		switch (choice)
		{
		case 1:
			cout << "New email here" << endl;
			addEmail(); // add to list of emails, set who to get the email
			break;
		case 2:
			cout << "Send email" << endl;
			sendEmail(); // select email from existing email list for user enetered in, has emails the recieved and have composed, can choose email to send and enter in recipients to overwrite original recipient value
			break;
		case 3:
			cout << "View previous emails" << endl;
			viewEmails(); // show all emails for specified user out from the map
			break;
		case 4:
			cout << "Delete specific user emails" << endl;
			deleteUserEmail(); // delete email from the list shown to the user of their emails
			break;
		case 5:
			cout << "Delete all User emails" << endl;
			deleteAllUserEmails(); // for a specific user delete all emails
			break;
		case 6:
			emailsMenu();
			break;
		case 7:
			cout << "Reset Server Data" << endl;
			// will empty out everything from the maps and lists email objects, except the users themselves
			resetServer();
			break;
		case 8:
			cout << "Exiting Server..." << endl;
			break;
		}
		cout << endl << endl;
	} while (choice != 8);
}

void emailsMenu()
{

	string word;
	int choice = 0;
	do {

		cout << "Search Emails Menu" << endl;
		cout << "Please select what you would like to do:" << endl << endl << endl;

		cout << " > 1. Search emails by date range" << endl;
		cout << " > 2. Search emails by subject" << endl;
		cout << " > 3. Search emails containing attachements" << endl;
		cout << " > 4. Return to main Menu" << endl;
		
		getline(cin, word);

		try {
			choice = stoi(word);
		}
		catch (const invalid_argument& ia) {
			cout << "Please enter in a number from 1-4 for you selection" << endl;
			//cout << "Invalid argument: " << ia.what() << endl;
			choice = 0;
		}

		switch (choice)
		{
		case 1:
			cout << "Search by date range here" << endl;
			dateSearch();
			break;
		case 2:
			cout << "Search by subject here" << endl;
			subjectSearch();
			break;
		case 3:
			cout << "Search by having attachments here" << endl;
			attachmentSearch();
			break;
		}

	} while (choice != 4);
}


void addEmail()
{
	string from;
	string to;
	string subject;
	string body;
	string answer;
	string path;
	time_t currentTime;
	Attachment* file;


	cout << "Enter in the Email Address this will come from" << endl;
	getline(cin,from);
	cout << "Enter in Email addresses separated by ; to send this email to, leave no spaces between emails" << endl;
	getline(cin, to);
	cout << "Enter in the Email subject" << endl;
	getline(cin, subject);
	cout << "Enter in the body of the Email" << endl;
	getline(cin, body);
	cout << "Would you like to add an attachment to this email?(Yes/No)" << endl;
	getline(cin, answer);

	
	
	if (answer == "yes" || answer == "Yes" || answer == "y" || answer == "Y")
	{
		cout << "Enter in the file path for your attachement" << endl;
		getline(cin, path);
		file = new Attachment(path.substr(0, path.find(".")), path.substr(path.find(".") + 1), path);
	}
	else
	{
		file = new Attachment("default","txt","default.txt");
	}
	
	
	
	Email* newEmail = new Email(from, to + ";", time(&currentTime), subject, body, *file);
	sendCache.storeObj(newEmail);


	// clear memory up, destructor will handle the deletion of these variables later on
	file = 0;
	delete[] file;
	newEmail = 0;
	delete[] newEmail;

}

void sendEmail()
{
	
	if (sendCache.sizeOfQueue() > 0)
	{
		Email* mail;
		string recipients, recipient;
		list<Email*> emails;

		// while the queue is not empty
		while (sendCache.sizeOfQueue() > 0)
		{
			// big operation to send to right email address
			// get mail out from the queue and remove from the queue
			mail = sendCache.frontObj();
			sendCache.removeFrontObj();

			// get out addresses to send this email to
			recipients = mail->getRecipients();

			// while all recipients have not had their mail sent yet
			while (recipients != "")
			{
				// get address out and cut down string to one less to send to
				recipient = recipients.substr(0, recipients.find(";"));
				recipients = recipients.substr(recipients.find(";") + 1);
				// get out user emails, add it on to the list and put back into the map of userEmails
				emails = userEmails[recipient];
				emails.push_back(mail);
				userEmails[recipient] = emails;
			}

		}


		cout << "All Emails have been successfully sent" << endl;
	}
	else
	{


		cout << "No Emails to send" << endl;
	}

}

void viewEmails()
{
	cout << endl << "Enter in Email address from a list of emails: " << endl;
	getUserList();
	showEmail();
}

void deleteUserEmail()
{
	cout << endl << "Enter in Email address from a list of emails: " << endl;
	getUserList();
	Email *message = showEmail();

	if (message)
	{
		cout << "Are you sure that you want to delete this email(No/Yes)?";
		cin >> input;

		if (input == "Yes" || input == "Y" || input == "yes" || input == "y")
		{
			doDelete(message);
			cout << "Email Deleted" << endl;
		}
		else
		{
			cout << "Email not deleted" << endl;
		}
	}
	else
	{
		cout << "invalid email name, please enter in a valid email from the list" << endl;
	}



}

void deleteAllUserEmails()
{
	cout << endl << "Enter in Email address from a list of emails: " << endl;
	// show user all users in the system to choose from
	getUserList();
	getline(cin,targetEmail);
	getUserEmailList();
	cout << endl << "Are you sure that you want to delete all of this users emails that are listed above(Yes/No)?";
	getline(cin,input);

	if (input == "Yes" || input == "Y" || input == "yes" || input == "y")
	{
		// clear the emails for this user key reference, needed to see this user contents, even if left blank when viewed
		list<Email*> blank;
		userEmails[targetEmail] = blank;
		cout << "All userEmails Deleted" << endl;
	}
	else
	{
		cout << "All User Emails were not deleted" << endl;
	}
	
}

void resetServer()
{
	// clearing all global data out from the structures and return to default initialisation state;
	results.empty();
	drafts.empty();
	input = "";
	targetEmail = "";
	map<string, list<Email*>>::iterator iter = userEmails.begin();

	while (iter != userEmails.end())
	{
		// setting the userEmails values for each key to an empty list of emails for all users to delete every email
		iter->second = results;
		iter++;
	}
	// resetting the state of the server to the initial data that was there when it was first started up
	initialData();

}


// searching method options
void dateSearch()
{

}

void subjectSearch()
{

}

void attachmentSearch()
{

}



// helper functions
void getUserList()
{
	map<string, list<Email*>>::iterator iter = userEmails.begin();
	while (iter != userEmails.end())
	{
		// show the user the list of each email in the map to choose from
		cout << iter->first << endl;
		iter++;
	}
	cout << endl;
}

void getUserEmailList()
{
	map<string, list<Email*>>::iterator iter = userEmails.begin();
	bool validEmail = false;

	while (iter != userEmails.end())
	{
		if (targetEmail == iter->first)
		{
			
			validEmail = true;
		}
		iter++;
	}
	iter = userEmails.begin();

	// check is a valid selection before continuing
	if (validEmail)
	{
		results = userEmails[targetEmail];

		list<Email*>::iterator iter2 = results.begin();

		while (iter2 != results.end())
		{

			cout << (*iter2)->getSubject() << endl;
			iter2++;
		}
		iter2 = results.begin();
	}
	else
	{
		list<Email*> blank;
		results = blank;
	}
	
	
}

Email* showEmail()
{
	Email* message = 0;
	cin >> targetEmail;
	// get back a list of emails for the selected email address
	getUserEmailList();
	if (results.size() > 0)
	{
		cout << endl << "Now enter in the subject of message to view: " << endl;
		getline(cin, input);
		getline(cin, input);
		list<Email*>::iterator iter = results.begin();
		bool found = false;

		while (iter != results.end() && !found)
		{
			if ((*iter)->getSubject() == input)
			{
				message = *iter;
				found = true;
			}
			iter++;
		}
		iter = results.begin();
		if (found)
		{
			cout << endl << endl << "Message content:" << endl;
			cout << "Subject: " << message->getSubject() << endl;
			cout << "Date Sent: " << message->getDateTime() << endl;
			cout << "Sender: " << message->getSender() << endl;
			cout << "Recipients: " << message->getRecipients() << endl;
			cout << "Subject: " << message->getSubject() << endl << endl;
			cout << message->getBody() << endl << endl;

			if (message->getAttachment().getFileName() != "default")
			{
				cout << "Attachment: " << message->getAttachment().getFileName() << "." << message->getAttachment().getFileSuffix() << endl << endl;
			}
			else
			{
				cout << "Attachment: None" << endl << endl;
			}
			return message;
		}
		else
		{
			cout << "You have not entered in the subject from the selection list correctly, please enter a valid selection" << endl;
		}
	}
	else
	{
		getline(cin, input);
		cout << "Email account not found, please enter in a valid entry or Email does not have any Emails to show" << endl;
	}
	return message;
}

void doDelete(Email* message)
{
	list<Email*>::iterator iter = results.begin();
	
	while (iter != results.end())
	{
		if (message->getSubject() == (*iter)->getSubject())
		{
			iter = results.erase(iter);
		}
		else
		{
			iter++;
		}
		
	}
	userEmails[targetEmail] = results;
}


void initialData()
{

	// creating some emails to use on startup of program so you have initial model set up for viewing the data
	time_t currentTime;
	Attachment* file = new Attachment("data", "txt", "data.txt");
	Email* email1 = new Email("VitaliyV@student.dkit.ie", "kieronpeters1@gmail.com;darrenreid@outlook.com;", time(&currentTime), "LinkedIn Profile Request", "Vitaliy asked you to like his profile page!", *file);
	Email* email2 = new Email("darrenreid@outlook.com", "kieronpeters1@gmail.com;", time(&currentTime), "Vitaliy on LinkedIn", "Don't add vitaliy, he wants use your profile to get work placement interview!", *file);
	list<Email*> emails;
	emails.push_back(email1);
	emails.push_back(email2);
	userEmails["kieronpeters1@gmail.com"] = emails;
	list<Email*> kp = userEmails.at("kieronpeters1@gmail.com");
	list<Email*>::iterator iter = kp.begin();
	
	Email* e;
	while (iter != kp.end())
	{
		e = *iter;
		cout << "Sender = " << e->print() << endl;
		iter++;
	}

	// cannot remove until I move the pointer to null as the emails in the list are pointers to these and deleting them, removes them from the list, so set to 0 first
	email1 = 0;
	delete[] email1;
	email2 = 0;
	delete[] email2;
	file = 0;
	delete[] file;
}