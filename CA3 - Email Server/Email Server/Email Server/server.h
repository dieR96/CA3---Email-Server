#pragma once
#include "Email.h"


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
void getUserEmails();
void getEmails();
Email showEmail();
void doDelete(Email message);