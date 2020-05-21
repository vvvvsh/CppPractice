#include <fstream>
#include <iostream>
#include <vector>
	#include <string.h>
#include <sstream>

using namespace std;

class LogParser
{
 
public :

	ifstream logfile; 
	char *p;
	char bufstr[100];
	string str_logfiles;
	char** arr;
	vector<string> logfilesvec;
	
void ReadFromConfigFile() 
   {
	logfile.open("Lc.conf");

	while(logfile)
	{
		logfile.getline(bufstr,100);
	        for (p=bufstr; *p; p++)  // note 2
		    {
		      //cout << *p;
		    }
	cout << endl;
	str_logfiles = bufstr;
	istringstream istream(str_logfiles);
	for(string s; istream >> str_logfiles; )
	{
		logfilesvec.push_back(str_logfiles);
	}
	
	  for (int i = 0; i < logfilesvec.size(); i++) 
	        cout << logfilesvec.at(i) << " ";


	//	char *token = strtok(bufstr, "=,");
	//	while (token != NULL) 
	//	{	 
	//	cout << token << endl;
	//       token = strtok(NULL, "=,"); 
	//}  
	
	}	
   }
};
int main()
{
	LogParser log1;
	log1.ReadFromConfigFile();
}
