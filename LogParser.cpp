#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <thread>
#include <regex>
#include <vector>
#include "logparser.h"
using namespace std;


class PerformParsing{
public : 
const char* configFile = "Lc.conf";
const char CDELIMITER = '=';
ofstream outfile;
PerformParsing()
{
	if(!outfile.is_open())
	outfile.open("final.json", ios::app);
}


void parseLogFile(string file){
	ifstream inlogfile(file);
	string readLine;

	inlogfile.open(file.substr(file.find_last_of("/\\")+1));
	if(!inlogfile.is_open()){	
		cout << "Unable to Open File : " << file << endl;
	}
	else{
	   string line;
	   smatch match;
	   while(getline(inlogfile,readLine)){

			for(size_t i=0; i < regexvec.size();i++){

				if(regex_search(readLine,match,regexvec[i])){

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
outfile.close();
}
};


int main()
{
  PerformParsing pars;
  vector<string> logfiles = pars.getLogFiles();
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
