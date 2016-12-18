#include "Email.h"
#include "User.h";
#include "server.h"
#include <iostream>
#include <string>
#include <map>
#include <set>
#include <list>


using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::getline;
using std::stoi;
using std::map;
using std::list;

map<string, list<Email>> userEmails;
map<string, User> users;


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

	cout << "Welcome To DkMailIT !" << endl;
	

	string word;
	int choice = 0;

	do
	{
		cout << "Main Menu" << endl;
		cout << "Please select what you would like to do:" << endl << endl << endl;

		cout << "1. New email" << endl;
		cout << "2. Send email" << endl;
		cout << "3. View previous emails" << endl;
		cout << "4. Delete specific email" << endl;
		cout << "5. Delete all emails" << endl;
		cout << "6. Search emails menu" << endl; // by date, subject or hasAttachements
		cout << "7. Reset emails" << endl; // delete all objects assigned in the program
		cout << "8. Exit" << endl;
		getline(cin, word);

		try {
			choice = stoi(word);
		}
		catch (const std::invalid_argument& ia) {
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
			cout << "Delete specific emails" << endl;
			deleteEmail(); // delete email from the list shown to the user of their emails
			break;
		case 5:
			cout << "Delete all emails" << endl;
			deleteAllEmails(); // for a specific user delete all emails
			break;
		case 6:
			emailsMenu();
			break;
		case 7:
			cout << "Reset emails" << endl;
			clearEmails(); // will empty out everything from the maps and lists email objects, except the users themselves;
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


		cout << "1. Search emails by date range" << endl;
		cout << "2. Search emails by subject" << endl;
		cout << "3. Search emails containing attachements" << endl;
		cout << "4. Return to main Menu" << endl;
		
		getline(cin, word);

		try {
			choice = stoi(word);
		}
		catch (const std::invalid_argument& ia) {
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

void initialData()
{

	// creating some emails to use on startup of program so you have initial model set up for viewing the data
	time_t currentTime;
	char contents[]{ 'D','A','T','A' };
	Attachment file("data", "txt", contents, 4);
	Email email1("VitaliyV@student.dkit.ie", "kieronpeters1@gmail.com;darrenreid@outlook.com;", time(&currentTime), "LinkedIn Profile Request", "Vitaliy asked you to like his profile page!", file);
	Email email2("darrenreid@outlook.com", "kieronpeters1@gmail.com;", time(&currentTime), "Vitaliy on LinkedIn", "Don't add vitaliy, he want's use your profile to get work placement interview!", file);
	
	list<Email> emails;
	emails.push_back(email1);
	emails.push_back(email2);
	userEmails["kieronpeters1@gmail.com"] = emails;
	list<Email> kp = userEmails.at("kieronpeters1@gmail.com");
	list<Email>::iterator iter = kp.begin();

	Email e;
	while (iter != kp.end())
	{
		e = *iter;
		cout << "Sender = " << e.print() << endl;
		iter++;
	}
}

void dateSearch()
{

}

void subjectSearch()
{

}

void attachmentSearch()
{

}

void addEmail()
{

}

void sendEmail()
{

}

void viewEmails()
{

}
void deleteEmail()
{

}

void deleteAllEmails()
{

}

void clearEmails()
{

}