
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>

using std::vector;
using std::endl;
using std::cout;
using std::any_of;
using std::all_of;
using std::none_of;
using std::string;

int main()
{
	vector<string> data = { "1","2","3" };
	if (none_of(data.begin(), data.end(), [](string s) {return s == "4"; }))
	{
		cout << "yes" << endl;
	}
	else
	{
		cout << "no" << endl;
	}

	return 0;
}