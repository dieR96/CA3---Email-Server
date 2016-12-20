#pragma once
#include "Email.h"
#include <list>

using std::list;

// main operations
void mainMenu();
void emailsMenu();
void initialData();
void dateSearch();
void subjectSearch();
void attachmentSearch();
void addEmail();
void sendEmail();
void viewEmails();
void deleteUserEmail();
void deleteAllUserEmails();
void resetServer();

// helper methods
void getUserList();
void getUserEmailList();
Email* showEmail();
void doDelete(Email* message);
void sortBySubject(list<Email*> &searchResults);