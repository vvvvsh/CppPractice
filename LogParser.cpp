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
#include <iomanip>
#include <chrono>

using namespace std;
using namespace std::chrono;

const char* configFile = "Lc.conf";
const char CDELIMITER = '=';
const char CDELIMITER2 = '.';

const string day("Sun|Mon|Tue|Wed|Thurs|Fri|Sat");
const string month("Jan|Feb|Mar|Apr|May|Jun|Jul|Aug|Sep|Oct|Nov|Dec|January|February|March|April|May|June|July|August|September|October|November|December");
const string loglevel("ALERT|DEBUG|TRACE|NOTICE|FATAL|WARN|INFO|SEVERE|CRIT|alert|debug|trace|notice|fatal|warn|info|server|crit");

regex loglevelrx("\\s*("+loglevel+")\\s\\s(.*$)");
regex timestamprx1("\\s*([0-9]{2,4}[-][0-9]{1,2}[-][0-9]{1,2}[-][0-9]{1,2}[:][0-9]{1,2}[:][0-9]{1,2}[.][0-9]{1,6})\\s*");
regex timestamprx2("\\s*("+day+")\\s("+month+")\\s([0-9]{1,2}\\s[0-9]{1,2}[:][0-9]{1,2}[:][0-9]{1,2}\\s[0-9]{2,4})\\s*");

ofstream outfile;
vector<regex> regexvec = {timestamprx1,timestamprx2};
map<string,int> dateTimeMap;
map<string,int>::iterator dateTimeit; 

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

void getMatchingRegex(string *file, string *line, regex *fileRegex){
	smatch match;
	auto start = std::chrono::high_resolution_clock::now();

	for(size_t i=0; i< regexvec.size();i++){
                      if(regex_search(*line,match,regexvec[i])){
                               *fileRegex = regexvec[i];
				dateTimeMap.insert(pair<string,int>(*file,i+1));
                      }
        }
	auto finish = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> elapsed = finish - start;
	cout << "Regex search finished " << endl;
	cout << "Elapsed time : " << elapsed.count() << " milliseconds" << endl; 
}

void writeToFile(string *line, regex *fileRegex,string *filename){
	smatch match;
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	
	if(regex_search(*line,match,*fileRegex)){
			outfile << "{host:" << "\"" << getenv("HOSTNAME")<< "\", ";
			cout << "{host:" << "\"" << getenv("HOSTNAME")<< "\", ";
			outfile << "file-name:" <<"\""<< *filename << "\", ";
			cout <<  "file-name:" <<"\""<< *filename << "\", ";
			dateTimeit = dateTimeMap.find(*filename);

			string timestampstr="";
			if(dateTimeit == dateTimeMap.end()){
		                //cout << "No matching Timestamp value found for file :" <<*filename << endl;
				outfile << "Timestamp:\""<<match[1] << "\",";
        		}
			else{
				timestampstr = match[1];
				string str=match[2];
				if(!str.empty()){
					timestampstr.append(" ").append(match[2]).append(" ").append(match[3]).append(" ");
				}
				auto start = std::chrono::high_resolution_clock::now();	
				outfile << "Timestamp :\"" <<convertDateTime(dateTimeit->second, timestampstr) << "\",";
				cout <<  "Timestamp:\"" <<convertDateTime(dateTimeit->second, timestampstr) << "\",";
				auto finish = std::chrono::high_resolution_clock::now();
				std::chrono::duration<double, std::milli> elapsed = finish - start;
				//std::cout << "Elapsed Time for datetime Conversion: " << elapsed.count() << " seconds" << std::endl;
				//std::this_thread::sleep_for(std::chrono::milliseconds(1000));
			}
			if(regex_search(*line,match,loglevelrx)){
					outfile << "log-level:\"" << match[1] << "\",";
					cout <<  "log-level:\"" << match[1] << "\",";
					outfile << "message:\"" << match[2] << "\"}" << endl;
					cout <<  "message:\"" << match[2] << "\"}" << endl;
			}
	}
}

string convertDateTime(int regexformat, string match){
	char buffer [20];
	string year,month, date, hour, min, second;
	string strDate = match;
	switch(regexformat){
		case 1:
        		{
            			year = strDate.substr(0,4);
           			month = strDate.substr(5,2);
            			date = strDate.substr(8,2);

            			hour = strDate.substr(11,2);
            			min = strDate.substr(14,2);
            			second = strDate.substr(17,2);

 				strDate = "";           			
            			strDate.append(date).append("-").append(month).append("-").append(year).append(" ").append(hour).append(":").append(min).append(":").append(second);
		
	 			break;   

			}	
		case 2:
			{
				istringstream iss(strDate);
			        vector<std::string> results((istream_iterator<string>(iss)),istream_iterator<string>());

			        vector<string>::iterator it = results.begin();
				
            			month = results.at(1);
            			month = ConvertToLowerCase(month);
            			month = get_month_index(month);
            			date = results.at(2);
            			string hh_mm_ss = results.at(3);
            			year = results.at(4);
            			strDate = "";
            			strDate.append(date).append("-").append(month).append("-").append(year).append(" ").append(hh_mm_ss) ;
				break;
			}
		default:
				cout << "Invalid Regex format for timestamp" << endl;
				break;
	}

return strDate;
}


string ConvertToLowerCase(string strData)
{
    int i=0;
    char *arr = new char [strData.length()+1];
    strcpy (arr, strData.c_str());
    while (arr[i])
    {
        arr[i]= tolower(arr[i]);
        i++;
    }
    string res = arr;
    return res;
}

string get_month_index(string name)
{
   map<string, string> months
    {
        { "jan", "01" },
        { "feb", "02" },
        { "mar", "03" },
        { "apr", "04" },
        { "may", "05" },
        { "jun", "06" },
        { "jul", "07" },
        { "aug", "08" },
        { "sep", "09" },
        { "oct", "10" },
        { "nov", "11" },
        { "dec", "12" }
    };

    const auto iter = months.find( name );

    if( iter != months.cend() )
        return iter->second;
    return "";
}



void parseLogFile(string file){
	ifstream inlogfile(file);
	string readLine;
	regex fileRegex;	
	inlogfile.open(file.substr(file.find_last_of("/\\")+1), ios::in);
	if(!inlogfile.is_open()){	
		cout << "Unable to Open File : " << file << endl;
	}
	else{
	   streampos gpos = inlogfile.tellg();
	   smatch match;
 	   getline(inlogfile,readLine);
	   //Finding Matching Regex
	   getMatchingRegex(&file, &readLine, &fileRegex);

	   while(true){
               	if(!getline(inlogfile,readLine) || inlogfile.eof()){
                                inlogfile.clear();
                                inlogfile.seekg(gpos);
                                std::this_thread::sleep_for(std::chrono::milliseconds(300));
                                continue;
                }
                gpos=inlogfile.tellg();

	   	//Write the output to a file   
	   	auto start = high_resolution_clock::now();
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		writeToFile(&readLine, &fileRegex, &file);
		auto stop = high_resolution_clock::now();			
		std::chrono::duration<double, std::milli> elapsed = stop - start;
//		cout << "Writing to file finished " << endl;
//        	cout << "Elapsed time : " << elapsed.count() << " seconds" << endl;


	   } 
	}
	inlogfile.close();
}



vector<string> getLogFiles(){
	ifstream config;
	string bufLine;
	config.open(configFile);
	string logFilesstr;
	vector<string> files;


	if(!config.is_open()){
	     cout << "Unable to Open File : " << configFile << endl;
	     exit(EXIT_FAILURE);
	}
	while (!config.eof()){
		getline(config, bufLine);
		istringstream ss(bufLine);
		if (bufLine.find('=') != string::npos){
		while(getline(ss, logFilesstr, CDELIMITER)){}
	    }
	}
	    //Split the tokens
	    stringstream logfilestream(logFilesstr);
	    while(getline(logfilestream, bufLine, ','))
		files.push_back(bufLine);
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
				threads.push_back(thread(&PerformParsing::parseLogFile,Parsobj, logfiles[i]));
			}
		}
		if(logFileCount == 0){
	         	cout << "Warning : No log files present in the Configuration file" << endl;
		} 
	       	for(size_t i=0 ; i < threads.size(); i++){
				if(threads[i].joinable()){
					threads[i].join();
					}
		} 
	}
	catch(exception& e){
		cout << "Exception Occured : " << e.what() << endl;
	}
}
