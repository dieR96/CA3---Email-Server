#include "User.h"
#include "server.h"
#include "TemplateQueue.h"

#include <iostream>
#include <string>
#include <map>
#include <set>
#include <list>
#include <algorithm>
#include <regex>
#include <sstream>


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
using std::regex;
using std::to_string;
using std::stringstream;
using std::swap;

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

	// main server intro display the user will see on start up

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
		catch (/*const invalid_argument& ia*/ invalid_argument) 
		{
			cout << "Please enter in a number from 1-8 for you selection" << endl;
			//cout << "Invalid argument: " << ia.what() << endl;
			choice = 0;
		}

		switch (choice)
		{
		case 1:
			//cout << "New email here" << endl;
			addEmail(); // add to list of emails, set who to get the email
			break;
		case 2:
			//cout << "Send email" << endl;
			sendEmail(); // select email from existing email list for user enetered in, has emails the recieved and have composed, can choose email to send and enter in recipients to overwrite original recipient value
			break;
		case 3:
			//cout << "View previous emails" << endl;
			viewEmails(); // show all emails for specified user out from the map
			break;
		case 4:
			//cout << "Delete specific user emails" << endl;
			deleteUserEmail(); // delete email from the list shown to the user of their emails
			break;
		case 5:
			//cout << "Delete all User emails" << endl;
			deleteAllUserEmails(); // for a specific user delete all emails
			break;
		case 6:
			//cout << "search menu here" << endl;
			emailsMenu();
			break;
		case 7:
			//cout << "Reset Server Data" << endl;
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

// second menu displayed when you want to search for certain emails
void emailsMenu()
{

	string word;
	int choice = 0;
	do {
		// help on declaring array of function pointers available at http://stackoverflow.com/questions/5093090/array-of-function-pointers-without-a-typedef accessed on 16/12/2016 11:55pm

		// store three search functions into an array of function pointers declared size of 3 that takes no parameters and return a list of emails found
		void(*functs[3])();
		// fill array funct with the names of the three search functions here
		functs[0] = dateSearch;
		functs[1] = subjectSearch;
		functs[2] = attachmentSearch;


		cout << "Search Emails Menu" << endl;
		cout << "Please select what you would like to do:" << endl << endl << endl;
		cout << " > 1. Search emails by date range" << endl;
		cout << " > 2. Search emails by subject" << endl;
		cout << " > 3. Search emails containing attachments" << endl;
		cout << " > 4. Return to main Menu" << endl;
		
		getline(cin, word);

		try {
			choice = stoi(word);
		}
		catch (/*const invalid_argument& ia*/ invalid_argument) {
			cout << "Please enter in a number from 1-4 for you selection" << endl;
			//cout << "Invalid argument: " << ia.what() << endl;
			choice = 0;
		}
		
		// much smaller code than below for the switch cases
		if (choice >= 1 && choice < 4)
		{
			// subtract one due to arrays starting at index position 0
			functs[choice - 1]();
		}


		// could use but same as above with the array pointers now
		/*
		switch (choice)
		{
		case 1:
			//cout << "Search by date range here" << endl;
			functs[0]();
			// same operation as above does
			//dateSearch();
			break;
		case 2:
			//cout << "Search by subject here" << endl;
			functs[1]();
			// same operation as above does
			//subjectSearch();
			break;
		case 3:
			//cout << "Search by having attachments here" << endl;
			functs[2]();
			// same operation as above does
			//attachmentSearch();
			break;
		}
		*/


	} while (choice != 4);
}

// gets the necessary information from the user about the data they want to store in a new emails and option of specifying the attachment for the email as well
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
	
	// logic for specifying an attachment or default one will be used
	if (answer == "yes" || answer == "Yes" || answer == "y" || answer == "Y")
	{
		cout << "Enter in the file path for your attachement" << endl;
		getline(cin, path);
		// may not work for file name as path with directory will go all the way up to the first . in it
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

// send all emails stored in the templated queue
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

// show email from the list after selecting a user of emails to view
void viewEmails()
{
	cout << endl << "Enter in Email address from a list of emails: " << endl;
	getUserList();
	showEmail();
}

// methods that allows you to select a specific email from a specific user to delete
void deleteUserEmail()
{
	cout << endl << "Enter in Email address from a list of emails: " << endl;
	getUserList();
	Email *message = showEmail();

	// logic finds the email if it exists and what choice they give for the email
	if (message)
	{
		cout << "Are you sure that you want to delete this email(No/Yes)?";
		cin >> input;

		if (input == "Yes" || input == "Y" || input == "yes" || input == "y")
		{
			// helper method that deletes the specified email
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

// deletes every email from a specified user upon confirmation of the operation
void deleteAllUserEmails()
{
	cout << endl << "Enter in Email address from a list of emails: " << endl;
	// show user all users in the system to choose from
	getUserList();
	getline(cin,targetEmail);
	getUserEmailList();
	cout << endl << "Are you sure that you want to delete all of this users emails that are listed above(Yes/No)?";
	getline(cin,input);

	// logic check for user confirmation of delete all emails
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

// reset option in main menu
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

// searching method options, used as function pointers in the search menu of the emails
void dateSearch()
{
	//cout << "running the date function" << endl;
	int eDay, eMonth, eYear, lDay, lMonth, lYear;
	string first, second;
	
	//char garbage;

	cout << "enter in the earliest date range to search from in the format DD/MM/YYYY" << endl;
	getline(cin,first);
	//cin >> eDay >> garbage >> eMonth >> garbage >> eYear;
	cout << "enter in the latest date range to search to in the format DD/MM/YYYY" << endl;
	getline(cin, second);
	//cin >> lDay >> garbage >> lMonth >> garbage >> lYear;

	// check both regex's match for input being correct
	
	try
	{
		// try to read in valid input from the user
		eDay = stoi(first.substr(0, first.find_first_of("/")));
		eMonth = stoi(first.substr(first.find_first_of("/") + 1, first.find_last_of("/")));
		eYear = stoi(first.substr(first.find_last_of("/") + 1));
		lDay = stoi(second.substr(0, second.find_first_of("/")));
		lMonth = stoi(second.substr(second.find_first_of("/") + 1, second.find_last_of("/")));
		lYear = stoi(second.substr(second.find_last_of("/") + 1));
	}
	catch (/*const invalid_argument& ia*/ invalid_argument)
	{
		cout << "Please enter in the format suggested" << endl;
		//cout << "Invalid argument: " << ia.what() << endl;
		// if statement never runs as checks only if eday is right && won't carry equating this statment after that, so user has to try again
		eDay = 0;
	}

	// regex found and modified from: http://stackoverflow.com/questions/51224/regular-expression-to-match-valid-dates/8768241#8768241 accessed on 17/12/2016 at 1:20AM
	// regex testing extensive and cannot work out why is showing up invalid when tested so left it out of this method for regex validation on the dates
	//regex regex("([1-9]|[12][0-9]|3[01])([- .])([1-9]|1[012])\2(19|20)[0123456789][0123456789]");

	// check valid ranges of input for max allowed for longest month, 12 months and valid year from 1970 to 2050
	if (eDay > 0 && eDay < 32 && eMonth > 0 && eMonth < 13 && eYear > 1969 && eYear < 2051 && lDay > 0 && lDay < 32 && lMonth > 0 && lMonth < 13 && lYear > 1969 && lYear < 2051)
	{
		// create time objects from the inputs
		time_t earliestDate;
		time_t latestDate;
		// get current time for now
		time(&earliestDate);
		time(&latestDate);
		// use a struct to alter the times to the users inputs
		struct tm * earliest;
		earliest = gmtime(&earliestDate);
		// set those times correctly offset for the format the tm struct uses
		// set the time_t objects ready for use in the loop with comparing them for the email date checking
		earliest->tm_mday = eDay;
		earliest->tm_mon = eMonth - 1;
		earliest->tm_year = eYear - 1900;
		earliestDate = mktime(earliest);

		// second struct needed independent to other as caused same year to be set on them all for some strange reason unknown to me
		struct tm * latest;
		latest = gmtime(&latestDate);
		latest->tm_mday = lDay;
		latest->tm_mon = lMonth - 1;
		latest->tm_year = lYear - 1900;
		latestDate = mktime(latest);
		time_t now;
		time(&now);

		// testing for outputs and calculations
		/*
		cout << earliestDate << endl;
		cout << latestDate << endl;
		
		cout << now << endl;
		cout << (earliestDate < latestDate) << endl;
		*/

		// validation for dates in right order and is no greater than now in date range searches
		if (earliestDate < latestDate && latestDate <= now)
		{
			// carry out actual search here using first iterator of all emails in the map of users
			map<string, list<Email*>>::const_iterator mapIter = userEmails.begin();
			// setting list pointers for storing the map data and results of the matching emails to the criteria of valid date ranges
			list<Email*> emails;
			list<Email*> searchResults;
			while (mapIter != userEmails.end())
			{
				emails = mapIter->second;
				
				for (Email* e : emails)
				{
					if (e->getRawDateTime() >= earliestDate && e->getRawDateTime() <= latestDate)
					{
						searchResults.push_back(e);
					}
				}

				mapIter++;
			}
			
			if (searchResults.size() > 0)
			{
				// new sorting function to sort the list alphabetically by subject string title using a bubbleSort 
				sortBySubject(searchResults);

				// old sorting method using the standard template library function .sort()
				// sorting the data based on the overloaded greater than operator in the email class in ascending order
				//searchResults.sort();


				int count = 0;
				for (Email* e : searchResults)
				{
					count++;
					// reuse the code for showing out a message here
					cout << endl << endl << "Message (" << count << "/" << searchResults.size() << ") content:" << endl;
					cout << "Subject: " << e->getSubject() << endl;
					cout << "Date Sent: " << e->getDateTime() << endl;
					cout << "Sender: " << e->getSender() << endl;
					cout << "Recipients: " << e->getRecipients() << endl;
					cout << "Subject: " << e->getSubject() << endl << endl;
					cout << e->getBody() << endl << endl;

					// same check for existing attachment file
					if (e->getAttachment().getFileName() != "default")
					{
						cout << "Attachment: " << e->getAttachment().getFileName() << "." << e->getAttachment().getFileSuffix() << endl << endl;
					}
					else
					{
						cout << "Attachment: None" << endl << endl;
					}
				}

			}
			else
			{
				cout << "Sorry, no Emails to show that match these ranges of dates in the server" << endl;
			}
		}
		else
		{
			cout << "Please enter in a valid date range in the correct order and lower than a date not past today!!" << endl;
		}
	}
	else
	{
		cout << "please enter in valid dates to search for" << endl;
	}
}

// searches for a specified sentence as a subject by each word on every email in the server and returns their content to the user
void subjectSearch()
{
	//cout << "running the subject function" << endl;

	string searchSubject;
	cout << "Enter in the subject of the emails you are searching for" << endl;
	getline(cin, searchSubject);

	// if the regex does not match, then the user is shown their input error
	regex subjectRegex("[0-9A-ZA-z ]*");	
	if (regex_match(searchSubject, subjectRegex))
	{
		// carry out actual search here using first iterator of all emails in the map of users
		map<string, list<Email*>>::const_iterator mapIter = userEmails.begin();
		// setting list pointers for storing the map data and results of the matching emails to the criteria of matching subjects
		list<Email*> emails;
		list<Email*> searchResults;
		string statement;
		string word;
		bool added = false;
		int pos;
		while (mapIter != userEmails.end())
		{
			// getting out the list for each user email in turn in this while loop
			emails = mapIter->second;

			// for every email this user has, we check for any word the types is contained in the subject matter
			for (Email* e : emails)
			{

				// refilling string for next email to search, adding space onto string in order to search it
				statement = searchSubject + " ";
				// for each word in the sentence is checked for a match until string is empty
				while (statement != "")
				{
					// taking out first word
					word = statement.substr(0, statement.find_first_of(" "));
					statement = statement.substr(statement.find_first_of(" ") + 1);
					// matches the subject in the email, add to the list of results if so, pos returns match in position to found value, -1 if not so we know this email matches if greater than -1
					pos = e->getSubject().find(word);
					if (pos >= 0 && !added)
					{
						// adding the email, added boolean check will prevent an added email being added again in the statement loop and rest before next while loop new email is ran
						searchResults.push_back(e);
						added = true;
					}
				}
				added = false;
			}

			mapIter++;
		}

		if (searchResults.size() > 0)
		{
			// new sorting function to sort the list alphabetically by subject string title using a bubbleSort 
			sortBySubject(searchResults);

			// old sorting method using the standard template library function .sort()
			// sorting the data based on the overloaded greater than operator in the email class in ascending order
			//searchResults.sort();

			int count = 0;
			for (Email* e : searchResults)
			{
				count++;
				// reuse the code for showing out a message here
				cout << endl << endl << "Message (" << count << "/" << searchResults.size() << ") content:" << endl;
				cout << "Subject: " << e->getSubject() << endl;
				cout << "Date Sent: " << e->getDateTime() << endl;
				cout << "Sender: " << e->getSender() << endl;
				cout << "Recipients: " << e->getRecipients() << endl;
				cout << "Subject: " << e->getSubject() << endl << endl;
				cout << e->getBody() << endl << endl;

				// same check for existing attachment file
				if (e->getAttachment().getFileName() != "default")
				{
					cout << "Attachment: " << e->getAttachment().getFileName() << "." << e->getAttachment().getFileSuffix() << endl << endl;
				}
				else
				{
					cout << "Attachment: None" << endl << endl;
				}
			}
		}
		else
		{
			cout << "Sorry, no Emails to show that match this subject in the server" << endl;
		}

	}
	else
	{
		cout << "Please enter in a subject without special characters" << endl;
	}

}

// simpler search that returns any email in the sever that has a valid attachment that the user can view all of these at once
void attachmentSearch()
{
	//cout << "running the attachment function" << endl;

	// carry out actual search here using first iterator of all emails in the map of users
	map<string, list<Email*>>::const_iterator mapIter = userEmails.begin();
	// setting list pointers for storing the map data and results of the matching emails to the criteria of having an attachment in the email
	list<Email*> emails;
	list<Email*> searchResults;

	while (mapIter != userEmails.end())
	{
		emails = mapIter->second;
		// using std library function to check if any emails in the list now has an attachment, checking default.txt is not the file name to execute that loop of functions
		if (any_of(emails.begin(), emails.end(), [](Email* e) {return (*e).getAttachment().getFileName() != "default"; }))
		{
			// do the actual loop for finding the emails in the list of emails that have an existing attachment
			for (Email* e : emails)
			{
				// matches the attachment in the email, add to the list of results if so
				if (e->getAttachment().getFileName() != "default")
				{
					searchResults.push_back(e);
				}
			}
		}
		mapIter++;
	}

	if (searchResults.size() > 0)
	{
		// new sorting function to sort the list alphabetically by subject string title using a bubbleSort 
		sortBySubject(searchResults);
		
		// old sorting method using the standard template library function .sort()
		// sorting the data based on the overloaded greater than operator in the email class in ascending order
		//searchResults.sort();
		
		
		int count = 0;
		for (Email* e : searchResults)
		{
			count++;
			// reuse the code for showing out a message here
			cout << endl << endl << "Message (" << count << "/" << searchResults.size() << ") content:" << endl;
			cout << "Subject: " << e->getSubject() << endl;
			cout << "Date Sent: " << e->getDateTime() << endl;
			cout << "Sender: " << e->getSender() << endl;
			cout << "Recipients: " << e->getRecipients() << endl;
			cout << "Subject: " << e->getSubject() << endl << endl;
			cout << e->getBody() << endl << endl;

			// same check for existing attachment file
			if (e->getAttachment().getFileName() != "default")
			{
				cout << "Attachment: " << e->getAttachment().getFileName() << "." << e->getAttachment().getFileSuffix() << endl << endl;
			}
			else
			{
				cout << "Attachment: None" << endl << endl;
			}
		}
	}
	else
	{
		cout << "Sorry, no Emails to show that contain attachments in the server" << endl;
	}

}

// helper functions

// gets a list of users back before user has to type the one they want in
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

// shows back a specified users email subject for user to pick the email they would like to view
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

// shows a specific emails details out to the user, reused in multiple functions such as delete a specific email by showing it before delete confirmation is asked of the user
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

// carries out the specific email deletion from the user and reinserts the list with that one deleted that matches the subject
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

void sortBySubject(list<Email*> &searchResults)
{
	// getting two iterators to first and next email value for comparing in sorting algorithm
	list<Email*>::iterator current;
	list<Email*>::iterator next;
	Email* nextMail, *currentMail;
	int end = searchResults.size();

	// as I am not sure about sorting with iterators for insertions, I went with a longer bubbleSort for this program, had problems with swap using pointers to emails
	// had to dereference the mail from iterator and swap it with iterator, the iterator_swap and swap wouldn't work when iterated to show the sorting working, made
	// no difference and the insertion on a small result set would not cost much in time for this small email server
	while (end != 0)
	{
		// setting iterators for first and next value up for next loop through the list to sort it
		current = searchResults.begin();
		next = searchResults.begin();
		next++;

		// inner sort getting one short off the end each time to sort with bubbleSort algorithm on the email pointer list
		for (int pos = 1; pos < end; pos++)
		{
			// take references of actual emails
			nextMail = *next;
			currentMail = *current;
			// compare their subjects alphabetically
			if (nextMail->getSubject() < currentMail->getSubject())
			{
				// swap elements to correct alphabetical order by subject title
				swap(*nextMail, *currentMail);
			}
			// increment iterators for next two element comparances
			next++;
			current++;
		}
		// end gets closer to 0 to stop this outer loop without causing iterators to go out of memory location of the list, carful with using pointers
		end--;
	}
}

// initial state of the server or start up or after choosing the reset option
void initialData()
{
	// creating some emails to use on startup of program so you have initial model set up for viewing some emails with and without attachments, note - attachments files are assumed to be in the project folder
	// see the folder for data.txt used below, you can specify the full file where the program asks for the path to the file, this is just initial test, so depends on where you are running this program from
	// for how the file paths will work
	time_t currentTime;
	Attachment* file = new Attachment("data", "txt", "data.txt");
	Attachment* file2 = new Attachment();
	Email* email1 = new Email("vitaliyvasyltsiv@msn.com", "kieronpeters1@gmail.com;darrenreid@hotmail.com;", time(&currentTime), "LinkedIn Profile Request", "Vitaliy asked you to like his profile page!", *file);
	Email* email2 = new Email("darrenreid@hotmail.com", "kieronpeters1@gmail.com;", time(&currentTime), "Vitaliy on LinkedIn", "Don't add vitaliy, he wants use your profile to get work placement interview!", *file2);
	list<Email*> emails;
	emails.push_back(email1);
	emails.push_back(email2);
	userEmails["kieronpeters1@gmail.com"] = emails;
	emails.clear();
	emails.push_back(email1);
	userEmails["darrenreid@hotmail.com"] = emails;
	emails.clear();
	userEmails["dandansong@yahoo.ie"] = emails;
	userEmails["tunleang@student.dkit.ie"] = emails;
	userEmails["vitaliyvasyltsiv@msn.com"] = emails;


	// test data that prints out at very start and on the reset option display of all information of emails from my user
	/*
	list<Email*> kp = userEmails.at("kieronpeters1@gmail.com");
	list<Email*>::iterator iter = kp.begin();
	
	Email* e;
	while (iter != kp.end())
	{
		e = *iter;
		cout << "Sender = " << e->print() << endl;
		iter++;
	}
	*/

	// cannot remove until I move the pointer to null as the emails in the list are pointers to these and deleting them, removes them from the list, so set to 0 first
	email1 = 0;
	delete[] email1;
	email2 = 0;
	delete[] email2;
	file = 0;
	delete[] file;
	file2 = 0;
	delete[] file2;
}