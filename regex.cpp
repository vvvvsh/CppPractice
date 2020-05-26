#include <iostream>
#include <string>
#include <regex>
#include <cstdlib>
#include <iomanip>

using namespace std;

int main()
{
	string str = "skdbflsdbafkjbkjfsdajkf Sun Dec 04 04:47:44 2005 ksdjbfsdhbafjkbsdafb";
	smatch match;
	string date_time;
	regex rx("\\s*(Sun|Mon|Tue|Wed|Thurs|Fri|Sat)\\s(Jan|Feb|Mar|Apr|May|Jun|Jul|Aug|Sep|Oct|Nov|Dec)\\s([0-9]{1,2})\\s([0-9]{1,2}[:][0-9]{1,2}[:][0-9]{1,2})\\s([0-9]{2,4})\\s*");
	if(regex_search(str,match,rx))
		{
			//cout << match[1] << endl;
			//cout << match[2] << endl;
			//cout << match[3] << endl;
			//cout << match[4] << endl;
			//cout << match[5] << endl;
			//cout << match[4] << " " << match[3] << "-" << match[2] << "-" << match[5] << endl;
			date_time.append(match[4]).append(" ").append(match[3]).append("-").append(match[2]).append("-").append(match[5]);
			cout << date_time << endl;

			tm t = {};
			std::istringstream ss(date_time);
			//ss.imbue(std::locale("de_DE.utf-8"));
			// ss >> get_time(&t, "%Y-%b-%d %H:%M:%S");
			// if (ss.fail()) {
			//   cout << "Parse failed\n";
			//} else {
			//   cout << put_time(&t, "%c") << '\n';
			// }
		}
}





















