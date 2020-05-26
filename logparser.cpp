#include <fstream>
#include <iostream>
#include <vector>
#include <string.h>
#include <sstream>
#include <thread>
#include <dirent.h>
#include <boost/algorithm/string.hpp> 
#include <regex>
using namespace std;

class LogParser{
	public :
		ifstream logfile; 
		char *p;
		char bufstr[100];
		string str_logfiles;
		string* arr;
		vector<string> logfilesvec;
		string files;
		int n = 10 ;
		const char* configfile = "Lc.conf";
	
	string* ReadFromConfigFile()
		{
		logfile.open(configfile);
		while(!logfile.eof())
			{
				logfile.getline(bufstr,100);
				if(bufstr[0] != '\0'){	
					str_logfiles = bufstr;}
			}
		stringstream stream(str_logfiles);
		string logfilesitem;
		int count =0;
		arr = new string[n];
		while(getline(stream, logfilesitem, ','))
			{	
			arr[count] = logfilesitem.substr(logfilesitem.find('=') + 1);
			count ++;
			}	
		for(int i=0;i<sizeof(arr);i++)
			{	
			if(arr[i] != "\0")
				cout << "LogFile =  " << i << " : " << arr[i] << endl;
			}
		return arr;
		}
};

class Threading
{
	public:

	void ReadLogFiles(string file)
		{
		char filearr[100];
		ifstream infileobj;
		vector<string> result;
		infileobj.open(file.substr(file.find_last_of("/\\")+1));

		if(infileobj.is_open())
		{	
		string line;
		while(infileobj)
		   {
			cout << "Entered While" << endl;
                	infileobj.getline(filearr,100);
			cout << "Line = " << filearr << endl;
	                if(filearr[0] != '\0')
	                {

			//[Sun Dec 04 04:54:18 2005] [error] mod_jk child workerEnv in error state 6
			line = filearr;
			cout <<	"Displaying = " <<line.substr(0,line.find("]")) << endl;
			string timestampstr = line.substr(line.find("["), line.find("]")+1);
			cout << "TimeStamp : " << timestampstr << endl;
			string loglevel = (line.substr(timestampstr.length() + 1)).substr(line.substr(timestampstr.length() + 1).find("["), line.substr(timestampstr.length() + 1).find("]")+1);
			cout << "LogLevel : " << loglevel << "Length = " <<loglevel.length() << endl;
			string msg = line.substr(line.find(loglevel)+loglevel.length());
			cout << "Msg : " << msg << endl;




     			//tm t = {};

			//istringstream ss(timestampstr);
		   	//ss.imbue(std::locale("de_DE.utf-8"));
			//ss >> get_time(&t, "%Y-%b-%d %H:%M:%S");
			//if (ss.fail()) 
			//{
    			//std::cout << "Parse failed\n";
			//} 
			//else 
			//{
			//std::cout << put_time(&t, "%c") << '\n';
			//}
			WriteToJson(timestampstr,loglevel,msg,file); //Pass by reference
                	}
	           }
		 }
		 else
		  {
			cout << "Unable to open file = " << file << endl;
		  }
		}
	
	void writeToJson(string timestampstr,string loglevel,string msg, string filename) //Name
	{
	  ofstream outfile;
	  outfile.open("Outfile.json");
	  //regex time("[aeiou][0_9]");
	  string chars = "[]";
	  for(char c: chars)
	  {
		timestampstr.erase(remove(timestampstr.begin(),timestampstr.end(),c),timestampstr.end());
		loglevel.erase(remove(loglevel.begin(),loglevel.end(),c),loglevel.end());
	  }
	  
	  outfile << "{host : " << getenv("HOSTNAME") << ", ";
	  outfile << "file-name : "<< filename.substr(filename.find_last_of("/\\")+1) << " , ";
	  outfile << "TimeStamp : "<< timestampstr  << " ,";  
	  outfile << "log-level : \"" << loglevel<< " \" , ";
	  outfile << "message : " << msg << "}"<< endl;
	  outfile.close();
	// {host: “hostname”, file-name:”hadoop.log”, Timestamp: “TS”, log-level:”error”, message: “abc”} 
	}

};

int main()
{
	LogParser log1;
	string* logfilesarr;
	string files;
	logfilesarr = log1.ReadFromConfigFile();
	Threading* thobj = new Threading();
	for (int i = 0; i < sizeof(logfilesarr); i++)
        {
                if(logfilesarr[i] != "\0")
                {
                        files = logfilesarr[i];
			cout << "Creating thread for " << files << endl;
                        thread t1(&Threading::ReadLogFiles,thobj, files);
			t1.join();
                }
        }
}
