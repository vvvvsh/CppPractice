#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <thread>
#include <regex>
#include <vector>
#include <exception>
#include <mutex>
using namespace std;

const char* configFile = "Lc.conf";
const char CDELIMITER = '=';
const string day("Sun|Mon|Tue|Wed|Thurs|Fri|Sat");
const string month("Jan|Feb|Mar|Apr|May|Jun|Jul|Aug|Sep|Oct|Nov|Dec|January|February|March|April|May|June|July|August|September|October|November|December");
const string loglevel("ALERT|DEBUG|TRACE|NOTICE|FATAL|WARN|INFO|SEVERE|CRIT|alert|debug|trace|notice|fatal|warn|info|server|crit");
regex timestamprx1("\\s*("+day+")\\s("+month+")\\s([0-9]{1,2}\\s[0-9]{1,2}[:][0-9]{1,2}[:][0-9]{1,2}\\s[0-9]{2,4})\\s*");
regex loglevelrx("\\s*("+loglevel+")\\s\\s(.*$)");
regex timestamprx2("\\s*([0-9]{2,4}[-][0-9]{1,2}[-][0-9]{1,2}[-][0-9]{1,2}[:][0-9]{1,2}[:][0-9]{1,2}[.][0-9]{1,6})\\s*");
ofstream outfile;
vector<regex> regexvec = {timestamprx1,timestamprx2};
map<string,regex> regexmap;
map<string, regex>::iterator regexit; 
regex fileRegex;
mutex mmutex;
class PerformParsing{
public : 

PerformParsing()
{
	if(!outfile.is_open()){ //Check if outfile is open to write, if not open it
		cout << "Opening outfile " << endl;
		outfile.open("final.json", ios::app);
		if(!outfile.is_open()){ //Check if it is able to open the outfile, if not exit with error
			cout << "Unable to Open file to write : " << "final.json" << endl;
			exit(EXIT_FAILURE);
		}
	}
}

void parseLogFile(string file){
//	mmutex.lock();
	ifstream inlogfile(file);
	string readLine;
	inlogfile.open(file.substr(file.find_last_of("/\\")+1), ios::in);
	if(!inlogfile.is_open()){	
		cout << "Unable to Open File : " << file << endl;
	}
	else{
	   streampos gpos = inlogfile.tellg();
	   smatch match;
  	  
 	   getline(inlogfile,readLine);
          // cout << readLine << endl;
           for(size_t i=0; i< regexvec.size();i++){
                      if(regex_search(readLine,match,regexvec[i])){
                                regexmap.insert(pair<string,regex>(file,regexvec[i]));
                                  // cout << "Regex Matched : " << file << endl;
                      }
           }
           while(true){
	              if(!getline(inlogfile,readLine) || inlogfile.eof()){
               		        inlogfile.clear();
		                inlogfile.seekg(gpos);
		                std::this_thread::sleep_for(std::chrono::milliseconds(300));
                	        continue;
	              }
	              gpos=inlogfile.tellg();
        	   //   cout << file << endl;
		      regexit = regexmap.find(file);
		      if(regexit == regexmap.end())
	                     cout << "Regex not found for file : " << file << endl;
	              else{
	                       if(regex_search(readLine,match,regexit->second)){
           		            	//cout << file << endl;
		                    	std::this_thread::sleep_for(std::chrono::milliseconds(300));
		                        outfile << "{host : " << getenv("HOSTNAME")<< ", ";
                	 		outfile << "file-name : " << file << ", ";
		                        outfile << "Timestamp : " <<  match[1] << " ";
		                        outfile << match[2] << " ";
                		        outfile << match[3] << ",";
	//			        cout << "{host : " << getenv("HOSTNAME")<< ", " <<  "file-name : " << file << ", "  << "Timestamp : " <<  match[1] << " " << match[2] << " "  << match[3] << ",";
              				if(regex_search(readLine,match,loglevelrx)){
				  		outfile << "log-level :\"" << match[1] << "\" , ";			    
						outfile << "message :\"" << match[2] << "\"}" << endl;
	//			cout << "log-level :\"" << match[1] << "\"" <<  "message :\"" << match[2] << "\"}" << endl;
					}
		    		}
			}
	     }		
	  }
	inlogfile.close();
//	mmutex.unlock();
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

~PerformParsing(){
	outfile.close();
   }
};


int main(){
	try{
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
			//threads.push_back(t1);
			//t1.detach(); //Look to wait for threads , Sleep
			//this_thread::sleep_for(std::chrono::milliseconds(5000));	
			//cout << i << endl;	
			}
		}
		if(logFileCount == 0){
	         	cout << "Warning : No log files present in the Configuration file" << endl;
		} 
	       	for(size_t i=0 ; i < threads.size(); i++){
				if(threads[i].joinable()){
					cout << "Joining threads " << endl;
					threads[i].join();
					}
		} 
	}
	catch(exception& e){
		cout << "Exception Occured : " << e.what() << endl;
	}
}