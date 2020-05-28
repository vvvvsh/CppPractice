#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <thread>
#include <regex>
#include <vector>
using namespace std;


class PerformParsing{
public : 
const char* configFile = "Lc.conf"; //Camel case
const char CDELIMITER = '=';
ofstream outfile;
PerformParsing()
{
	cout<< "In Constructor" << endl;
	outfile.open("final.json", ios::app);
}


void parseLogFile(string file){
const string loglevel("ALERT|DEBUG|TRACE|NOTICE|FATAL|WARN|INFO|SEVERE|CRIT");
regex timestamprx1("([0-9]{2,4}[-][0-9]{1,2}[-][0-9]{1,2}\\s[0-9]{1,2}[:][0-9]{1,2}[:][0-9]{1,2}[,][0-9]{1,3})\\s*("+loglevel+")\\s\\s(.*$)");
regex timestamprx2("([0-9]{1,4}[_][0-9]{1,2}[:][0-9]{1,2}[:][0-9]{1,2})\\s*("+loglevel+")\\s\\s(.*$)");
vector<regex> regexvec = {timestamprx1, timestamprx2};			 
	ifstream inlogfile(file);
	string readLine;
	//cout << file.substr(file.find_last_of("/\\")+1) << endl;
	inlogfile.open(file.substr(file.find_last_of("/\\")+1));
	if(!inlogfile.is_open()){	
		cout << "Unable to Open File : " << file << endl;
	}
	else{
	   string line;
	   smatch match;
	   while(getline(inlogfile,readLine)){
			//cout << "Line = " << readLine << endl;
			for(size_t i=0; i < regexvec.size();i++){
				//cout << "Entered For Loop :  " << endl;
				if(regex_search(readLine,match,regexvec[i])){
					//cout << match[i] << endl;
					outfile << "{host : " << getenv("HOSTNAME")<< ", ";
			        	outfile << "file-name : " << file << ", ";
			        	outfile <<"Timestamp : " <<  match[1] << ",";
			        	outfile <<"log-level :\"" << match[2] << "\"" << endl;
			        	outfile << "message :\"" << match[3] << "\"}" << endl;
				}
			}
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
		while(getline(ss, logFilesstr, CDELIMITER)){}
	    }
	    //Split the tokens
	    stringstream logfilestream(logFilesstr);
	    while(getline(logfilestream, bufLine, ','))
		files.push_back(bufLine);
	}
	return files;
}

~PerformParsing()
{
cout << "In destructor" << endl;
outfile.close();
}
};


int main()
{
  PerformParsing pars;
  vector<string> logfiles = pars.getLogFiles(); //Check for Negative scenarios as well,Error Handling
  vector<thread> threads;
  int logFileCount = 0;
  PerformParsing* Parsobj = new PerformParsing();
  for (size_t i = 0; i < logfiles.size(); i++){	
	if(logfiles[i].find(".log") != string::npos || logfiles[i].find(".txt") != string::npos ){
		logFileCount ++ ;
		cout << "Parsing Log File :  " << logfiles[i] << endl;
		//cout << i+10 << endl;
		threads.push_back(thread(&PerformParsing::parseLogFile,Parsobj, logfiles[i]));
//		threads.push_back(t1);
//		t1.detach(); //Look to wait for threads , Sleep
		//this_thread::sleep_for(std::chrono::milliseconds(5000));	
		//cout << i << endl;
	}
	if(logFileCount == 0){
	       cout << "Warning : No log files present in the Configuration file" << endl;
	}
     }
  for(size_t i=0 ; i < threads.size(); i++){
	threads[i].join();
}

}
