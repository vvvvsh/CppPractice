#include <iostream>
#include <string>
#include <regex>
#include <cstdlib>
#include <iomanip>

using namespace std;

int main()
{
        string str1 = "skdbflsdbafkjbkjfsdajkf Sun Dec 04 04:47:44 2005 ksdjbfsdhbafjkbsdafb";
        string str2 = "o1229321 ksjfkewfj 2005-06-03-15.42.50.675872 ldkjsldjfalasljf1249823u498732";
        string str3 = "ldksmflks  ldskflsda 2017-06-26 02:31:29,573 lsdjflsjaiflj";
        string str4 = "20171223-22:15:29:606";
        string str4 = "Mar 16 08:12:04";
        smatch match;
        string date_time;
        const string day("(Sun|Mon|Tue|Wed|Thurs|Fri|Sat)");
        const string month("(Jan|Feb|Mar|Apr|May|Jun|Jul|Aug|Sep|Oct|Nov|Dec|January|February|March|April|May|June|July|August|September|October|November|December)");
        regex timestamprx1("\\s*("+day+"\\s"+month+"\\s[0-9]{1,2}\\s[0-9]{1,2}[:][0-9]{1,2}[:][0-9]{1,2}\\s[0-9]{2,4})\\s*");
        regex timestamprx2("([0-9]{2,4}[-][0-9]{1,2}[-][0-9]{1,2}[-][0-9]{1,2}[.][0-9]{1,2}[.][0-9]{1,2}[.][0-9]{1,6})");
        regex timestamprx3("([0-9]{2,4}[-][0-9]{1,2}[-][0-9]{1,2}\\s[0-9]{1,2}[:][0-9]{1,2}[:][0-9]{1,2}[,][0-9]{1,3})");
        regex timestamprx4("([0-9]{1,8}[-][0-9]{1,2}[:][0-9]{1,2}[:][0-9]{1,2}[:][0-9]{1,3})");
        regex timestamprx5("\\s*("+month+"\\s[0-9]{1,2}\\s[0-9]{1,2}[:][0-9]{1,2}[:][0-9]{1,2})*);
        if(regex_search(str1,match,timestamprx1))
                {
                        cout << "String str1 = " ;
                        cout << match[1] << endl;
        }
        if(regex_search(str2,match,timestamprx2))
                {
                        cout << "String str2 = ";
                        cout << match[1] << endl;
        }
        if(regex_search(str3,match,timestamprx3)){
                        cout << "String str3 = ";
                        cout << match[1] << endl;

        }
        if(regex_search(str4,match,timestamprx4)){
                        cout << "String str4 = ";
                        cout << match[1] << endl;
        }
        if(regex_search(str5,match,timestamprx5)){
                        cout << "String str5 = ";
                        cout << match[1] << endl;
        }
}



















































































