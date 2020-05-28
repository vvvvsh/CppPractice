#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <thread>
//#include <regex>
#include <boost/regex.hpp>

using namespace std;


class PerformParsing{
public : 
const char* configFile = "Lc.conf"; //Camel case
const char CDELIMITER = '=';
//const string loglevel("ALERT|DEBUG|TRACE|NOTICE|FATAL|WARN|INFO|SEVERE|CRIT");
//const regex timestamprx1("([0-9]{2,4}[-][0-9]{1,2}[-][0-9]{1,2}\\s[0-9]{1,2}[:][0-9]{1,2}[:][0-9]{1,2}[,][0-9]{1,3})\\s*("+loglevel+"\s)*")");

void parseLogFile(string file){
const string loglevel("ALERT|DEBUG|TRACE|NOTICE|FATAL|WARN|INFO|SEVERE|CRIT");
boost::regex timestamprx1{"([0-9]{2,4}[-][0-9]{1,2}[-][0-9]{1,2}\\s[0-9]{1,2}[:][0-9]{1,2}[:][0-9]{1,2}[,][0-9]{1,3})\\s*("+loglevel+"\\s)*"};

	ifstream inlogfile(file);
	string readLine;
	cout << file.substr(file.find_last_of("/\\")+1) << endl;
	inlogfile.open(file.substr(file.find_last_of("/\\")+1));
	if(!inlogfile.is_open()){	
		cout << "Unable to Open File : " << file << endl;
	}
	else{
	   string line;
	   boost::smatch match;
	   while(getline(inlogfile,readLine)){
			cout << "Line = " << readLine << endl;
			//if(boost::regex_search(readLine,match,timestamprx1))
			//	{
			//		cout <<"timestamp = " <<  match[1] << ";";
			//		cout <<"loglevel = " << match[2] << endl;
			//	}
					
		}
	}
}


vector<string> getLogFiles(){ //Change Method Name with small letter
	ifstream config;
	string bufLine;
	config.open(configFile); 
 	string logFilesstr;//Change to string
	vector<string> files;
	//Get the line and push the tokens to Vector
	//cout << "Getting Log Files list... " << endl;
	if(!config.is_open()){
	     cout << "Unable to Open File : " << configFile << endl;
	     exit(EXIT_FAILURE);
	}
	while (getline(config, bufLine)){
		istringstream ss(bufLine);
		if (bufLine.find('=') == string::npos){
			cout << "Invalid entry in the  Config File" << endl;
		}
		else{
		while(getline(ss, logFilesstr, CDELIMITER)){
			cout << logFilesstr << endl;			
}
	    }
	    //Split the tokens
	    stringstream logfilestream(logFilesstr);
	    while(getline(logfilestream, bufLine, ','))
		files.push_back(bufLine);
	}
	return files;
}
};


int main()
{
  PerformParsing pars;
  vector<string> logfiles = pars.getLogFiles(); //Check for Negative scenarios as well,Error Handling
  int logFileCount = 0;
  PerformParsing* Parsobj = new PerformParsing();
  for (size_t i = 0; i < logfiles.size(); i++){	
	if(logfiles[i].find(".log") != string::npos || logfiles[i].find(".txt") != string::npos ){
		logFileCount ++ ;
		cout << "Parsing Log File :  " << logfiles[i] << endl;
		thread t1(&PerformParsing::parseLogFile,Parsobj, logfiles[i]);
		t1.detach(); //Look to wait for threads , Sleep
		this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
	if(logFileCount == 0){
	       cout << "Warning : No log files present in the Configuration file" << endl;
	}
     }
}
  //vector<std::thread> threads;
  //for(int i = 0; i < logfiles.size(); ++i){
//	cout << "Adding thread for : " << logfiles[i] << endl;
  //      threads.push_back(thread(&PerformParsing::parseLogFile,Parsobj, logfiles[i]));
   // }

    //for(auto& thread : threads){
     //   thread.join();
//	this_thread::sleep_for(std::chrono::milliseconds(300));
  //  }
//}
  //if(logFileCount == 0){
    //   cout << "Warning : No log files present in the Configuration file" << endl;
     //}
//}
