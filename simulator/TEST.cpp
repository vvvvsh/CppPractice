#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

typedef unsigned long ul;
typedef unsigned int ui;

ul CalcDayNumFromDate(ui y, ui m, ui d)
{
  m = (m + 9) % 12;
  y -= m / 10;
  ul dn = 365*y + y/4 - y/100 + y/400 + (m*306 + 5)/10 + (d - 1);

  return dn;
}

std::string CalcDayOfWeek(int y, ul m, ul d)
{
  std::string day[] = {
    "Wednesday",
    "Thursday",
    "Friday",
    "Saturday",
    "Sunday",
    "Monday",
    "Tuesday"
  };

  ul dn = CalcDayNumFromDate(y, m, d);

  return day[dn % 7];
}

/*int main(int argc, char **argv)
{
  ui y = 2017, m = 8, d = 29; // 29th August, 2017.
  std::string dow = CalcDayOfWeek(y, m, d);

  std::cout << std::setfill('0') << std::setw(4) << y << "/";
  std::cout << std::setfill('0') << std::setw(2) << m << "/";
  std::cout << std::setfill('0') << std::setw(2) << d << ": ";
  std::cout << dow << std::endl;

  return 0;
}
*/


int main()
{
	vector<std::string> full_day = {	
		"Monday",	
		"Tuesday",
		"Wednesday",
		"Thursday",
		"Friday",
		"Saturday",
		"Sunday"
	} ;

	 vector<std::string> short_day = {
                "Mon",
                "Tue",
                "Wed",
                "Thu",
                "Fri",
                "Sat",
                "Sun"
        };

	time_t ttime = time(0);
	tm *local_time = localtime(&ttime);
	cout << "Year: "<<1900+local_time->tm_year << endl;
	cout << "Month: "<<1+ local_time->tm_mon<< endl;
	cout << "Day: "<< local_time->tm_mday << endl;
	cout << "Time: "<< local_time->tm_hour<<":"<<local_time->tm_min<<":"
		<<local_time->tm_sec<<":"<<local_time->tm_isdst<< endl;
	cout << "tm_wday: "<< short_day[local_time->tm_wday] << endl;

	return 0;
}
