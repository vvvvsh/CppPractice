#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <thread>

using namespace std;


class PerformParsing{
public : 
const char* configFile = "Lc.conf"; //Camel case
const char CDELIMITER = '=';

void ParseLogFile(string file){
	ifstream inlogfile(file);
	cout << file.substr(file.find_last_of("/\\")+1) << endl;
	inlogfile.open(file.substr(file.find_last_of("/\\")+1));
	if(inlogfile.is_open())
	{	
	   string line;
	   while(inlogfile)
	   {
		cout << "Entered While" << endl ;
	   }
	}
	else
	{
	 cout << "Unable to Open File : " << file << endl;
	}
}

vector<string> getLogFiles(){ //Change Method Name with small letter
	ifstream config;
	string buf;
	config.open(configfile); 
 	vector<string> linevec;//Change to string
	vector<string> files;
    //Get the line and push the tokens to Vector
	if(config.is_open())
	{
	    while (getline(config, buf))
	    {
		istringstream ss(buf);
	        while (getline(ss, buf, CDELIMITER))
	            linevec.push_back(buf);
	    }
	    //Split the tokens
	    for(size_t i=0;i<linevec.size();i++)
	    {
		 stringstream logfilestream(linevec[i]);
		 while(getline(logfilestream, buf, ','))
		 files.push_back(buf);
	     }
	}
	else
	{
		cout << "Unable to Open File : " << configfile << endl;
	}
return files;
}

 };


int main()
{
  PerformParsing pars;
  vector<string> logfiles = pars.ReadConfigFile(); //Check for Negative scenarios as well,Error Handling
  PerformParsing* Parsobj = new PerformParsing();
  for (size_t i = 0; i < logfiles.size(); i++)
  {
       //cout << "Token[" << i << "] = " << logfiles[i] << endl;
	if(logfiles[i].find(".log") != string::npos){
        cout << "Parsing Log File :  " << logfiles[i] << endl;
        thread t1(&PerformParsing::ParseLogFile,Parsobj, logfiles[i]);
        t1.join(); //Look to wait for threads , Sleep
	}
  }
}
