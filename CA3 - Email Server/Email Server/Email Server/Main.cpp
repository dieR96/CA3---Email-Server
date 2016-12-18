#include <map>
#include "User.h"
#include "Email.h"
#include "Attachment.h"
#include "server.h"
#include <iostream>

#include "TemplateQueue.h"

using std::map;
using std::cout;
using std::endl;



int main()
{
	mainMenu();
	
	// test on the TemplateQueue that it works in the correct order
	/*
	TemplateQueue<int> test;
	int num = 3;
	test.storeObj(num);
	num = 4;
	test.storeObj(num);
	num = 5;
	test.storeObj(num);

	cout << test.frontObj() << endl;
	test.removeFrontObj();

	cout << test.frontObj() << endl;
	test.removeFrontObj();

	cout << test.frontObj() << endl;
	test.removeFrontObj();
	*/

	return 0;
}

