#include<iostream>
#include "simulator.h"
#include<thread>
#include<fstream>
#include<vector>
#include <chrono> 
using namespace std;
using namespace std::chrono;
int main()
{
	string fileName;
	int numOfFiles;
	vector <string> timeStampFormates;
	vector <string> logLevels = {"ALERT", "TRACE", "DEBUG", "INFO", "WARN", "NOTICE", "FATAL", "CRIT", "SEVERE"};
	fstream file("timeStampList.txt");
	string line;
	if (file.is_open())
        {
                while(getline(file, line))
                {
                        timeStampFormates.push_back(line);
                }
                file.close();
        }
        else
        {
        cout << "Unable to open file";
        }

	cout << "Enter the number of files to be generated : ";
	cin>>numOfFiles;
	auto start = high_resolution_clock::now();
	for(int i=0; i<numOfFiles; i++)
	{ 
		fileName = static_cast<string>("log_" + to_string(i) + ".txt");
		LogSimulator *obj_LogSimulator= new LogSimulator(fileName);
	//	auto start = high_resolution_clock::now();
		obj_LogSimulator->simulateLogFile(timeStampFormates, logLevels);
	//	auto stop = high_resolution_clock::now();
	//	auto duration = duration_cast<microseconds>(stop - start);
	//	cout << "Time taken by function: "<< duration.count() << " microseconds" << endl;
		delete obj_LogSimulator;
	}
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<milliseconds>(stop - start);
	cout << "Time taken by function: "<< duration.count() << " milliseconds" << endl;
	return 0;
}
