
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <time.h>

using std::vector;
using std::endl;
using std::cout;
using std::any_of;
using std::all_of;
using std::none_of;
using std::string;
using std::stringstream;
using std::stoi;

int main()
{
	// date time object in email
	time_t dateTime;
	// created to use the current exact time at creation of the email
	time(&dateTime);
	


	// use a struct to parse the date out of previous today's date created struct in the file
	struct tm * ptm;
	ptm = gmtime(&dateTime);	
	
	cout << "date created = " << ptm->tm_year + 1900 << "/" << ptm->tm_mon + 1 << "/" << ptm->tm_mday << endl;
	cout << ptm << endl;
	cout << dateTime << endl;

	
	// to get user inputs into a time object, first get the time() function to make it to now, then change the day, month, year by using
	// their input, but like above, set ptm->tm_year = year - 1900 where year is the users input year then you can use mktime on the struct
	// you just changed by using mktime which returns a time_t object, use the early and latest to compare each email time object



	// converting time_t to string
	stringstream ss;
	ss << dateTime;

	cout << dateTime << endl;
	cout << ss.str() << endl;

	return 0;
}