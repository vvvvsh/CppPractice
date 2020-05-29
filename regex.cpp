#include <iostream>
#include <string>
#include <regex>
#include <cstdlib>
#include <iomanip>

using namespace std;

int main()
{
	string str10 = "Fri May 29 06:29:39 2020  alert  [RMCommunicator Allocator] org.apache.hadoop.mapreduce.v2.app.rm.RMContainerAllocator: IN CONTACTING RM";
        string str1 = "skdbflsdbafkjbkjfsdajkf Sun Dec 04 04:47:44 2005 ksdjbfsdhbafjkbsdafb";
        string str2 = "o1229321 ksjfkewfj 2005-06-03-15.42.50.675872 ldkjsldjfalasljf1249823u498732";
        string str3 = "ldksmflks  ldskflsda 2017-06-26 02:31:29,573 lsdjflsjaiflj";
        string str4 = "20171223-22:15:29:606";
       	string str5 = "skdnf Mar 16 08:12:04 lksdf";
	string str6 = "ldkfmskld 2017-04-12_19:37:50 sdfmsakl";
	string str7 = "10.30 16:49:06";
        smatch match;
        string date_time;
	const string loglevel("ALERT|DEBUG|TRACE|NOTICE|FATAL|WARN|INFO|SEVERE|CRIT|alert|debug|trace|notice|fatal|warn|info|server|crit");
        const string day("Sun|Mon|Tue|Wed|Thurs|Fri|Sat");
        const string month("Jan|Feb|Mar|Apr|May|Jun|Jul|Aug|Sep|Oct|Nov|Dec|January|February|March|April|May|June|July|August|September|October|November|December");
        regex timestamprx1("\\s*("+day+"\\s"+month+"\\s[0-9]{1,2}\\s[0-9]{1,2}[:][0-9]{1,2}[:][0-9]{1,2}\\s[0-9]{2,4})\\s*");
        regex timestamprx2("([0-9]{2,4}[-][0-9]{1,2}[-][0-9]{1,2}[-][0-9]{1,2}[.][0-9]{1,2}[.][0-9]{1,2}[.][0-9]{1,6})");
        regex timestamprx3("([0-9]{2,4}[-][0-9]{1,2}[-][0-9]{1,2}\\s[0-9]{1,2}[:][0-9]{1,2}[:][0-9]{1,2}[,][0-9]{1,3})");
        regex timestamprx4("([0-9]{1,8}[-][0-9]{1,2}[:][0-9]{1,2}[:][0-9]{1,2}[:][0-9]{1,3})");
	regex timestamprx5("\\s*("+month+"\\s[0-9]{1,2}\\s[0-9]{1,2}[:][0-9]{1,2}[:][0-9]{1,2})");
	regex timestamprx6("([0-9]{2,4}[-][0-9]{1,2}[-][0-9]{1,2}[_][0-9]{1,2}[:][0-9]{1,2}[:][0-9]{1,2})");
	regex timestamprx7("([0-9]{1,2}[.][0-9]{1,2}\\s[0-9]{1,2}[:][0-9]{1,2}[:][0-9]{1,2})");
	//regex timestamprx10("("+day+"\\s"+month+"\\s[0-9]{1,2}\\s[0-9]{1,2}[:][0-9]{1,2}[:][0-9]{1,2}\\s[0-9]{2,4})\\s\\s("+loglevel+")\\s\\s(.*$)*");
	regex stamprx10("\\b(Sun|Mon|Tue|Wed|Thurs|Fri|Sat)\\s(Jan|Feb|Mar|Apr|May|Jun|Jul|Aug|Sep|Oct|Nov|Dec|January|February|March|April|May|June|July|August|September|October|November|December)\\s([0-9]{1,2}\\s[0-9]{1,2}[:][0-9]{1,2}[:][0-9]{1,2}\\s[0-9]{2,4})\\b\\s\\s("+loglevel+")\\s\\s(.*$)");
        if(regex_search(str10,match,stamprx10))
                {
			//cout << sizeof(match) << endl;
                        //cout << "String str1 = " ;
                        //cout << match[1] << endl;
			//cout << match[2] << endl;
			//cout << match[3] << endl;
//cout << match[4] << endl;
//cout << match[5] << endl;
//cout << match[6] << endl;
for(int i=0; i<=match.size();i++)
if(match[i]!=""){
	//cout << "At " << i<< endl;
	cout << match[i] << endl;
        }
}
       // if(regex_search(str2,match,timestamprx2))
        //        {
         //               cout << "String str2 = ";
          //              cout << match[1] << endl;
       // }
       // if(regex_search(str3,match,timestamprx3)){
         //               cout << "String str3 = ";
           //             cout << match[1] << endl;

        //}
        //if(regex_search(str4,match,timestamprx4)){
         //               cout << "String str4 = ";
           //             cout << match[1] << endl;
       // }
        //if(regex_search(str5,match,timestamprx5)){
         //               cout << "String str5 = ";
          //              cout << match[1] << endl;
       // }
	//if(regex_search(str6,match,timestamprx6)){
	//		cout << "String str6 = ";
	//		cout << match[1] << endl;
//	}
//	if(regex_search(str7,match,timestamprx7)){
//			cout << "String str7 = ";
//			cout << match[1] << endl;
//	}
}



















































































