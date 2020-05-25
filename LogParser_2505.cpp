#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <thread>
using namespace std;


class PerformParsing{
public : 
const char* configfile = "Lc.conf";
const char CDELIMITER = '=';

void ParseLogFile(string file){

}

vector<string> ReadConfigFile(){
    ifstream config;
    string buf;
    config.open(configfile);
    vector<string> linevec;
    vector<string> files;
    //Get the line and push the tokens to Vector
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

return files;
}};


int main()
{
  PerformParsing pars;
  vector<string> logfiles = pars.ReadConfigFile();
  PerformParsing* Parsobj = new PerformParsing();
  for (size_t i = 0; i < logfiles.size(); i++)
  {
       //cout << "Token[" << i << "] = " << logfiles[i] << endl;
	if(logfiles[i].find(".log") != string::npos){
        cout << "Parsing Log File :  " << logfiles[i] << endl;
        thread t1(&PerformParsing::ParseLogFile,Parsobj, logfiles[i]);
        t1.join();
	}
  }
}
