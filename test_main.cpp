#include<iostream>
#include "simulator.h"
#include<thread>
#include<fstream>
#include<vector>
#include <chrono>
#include<queue> 
#include<algorithm>
#include<list>
#include<mutex>
#include <sys/types.h>
#include <sys/stat.h>
using namespace std;
using namespace std::chrono;



void LogSimulator_wrapper(int tindex, vector<string> &timeStampFormats,vector<vector<string>> &logLevels, int &thread_count, int &remainingFiles, int &filesPerThread, int &cores, mutex &mtx, string &mydir)
{
	++thread_count;

	string fileName;
	//auto this_id = std::this_thread::get_id();
	vector<pair<LogSimulator*, int>> vec;
		int i = 0;
		for(i = tindex*filesPerThread; i<(filesPerThread + tindex*filesPerThread); i++)
		{
			fileName = static_cast<string>(mydir + "log_" + to_string(i) + ".log");
			vec.push_back(make_pair(new LogSimulator(fileName), i));
			cout <<"Log_file_wrapper1::"<<std::this_thread::get_id()<<" => "<<fileName <<", fileindex: " <<i << " "<<filesPerThread <<endl;
		}

		if(remainingFiles != 0)
		{
			
			const lock_guard<mutex> lock(mtx);		
			i = filesPerThread*cores + remainingFiles - 1;
			fileName = static_cast<string>("log_" + to_string(i) + ".log");
			vec.push_back(make_pair(new LogSimulator(fileName), i));
			cout <<"Log_file_wrapper2::"<<std::this_thread::get_id()<<" => "<<fileName <<", fileindex: " <<i <<endl;
			i++;	
			--remainingFiles;
		}
	
	        for(int j=0; j<1000;j++)
	        {
	   		for(auto v:vec)
		        {
                		(v.first)->simulateLogFile(timeStampFormats, logLevels, (v.second));
       	 		}
			sleep(1);               
	   	}
		for(auto v:vec)
       		{
              		delete (v.first);
        	}	
	--thread_count;
}
int dirExists(string mydir)
{
    struct stat info;

    if(stat( mydir.c_str(), &info ) != 0)
        return 0;
    else if(info.st_mode & S_IFDIR)
        return 1;
    else
        return 0;
}

int main()
{
	vector <string> timeStampFormats; 
	vector<vector <string>> logLevels = {{"ALERT", "TRACE", "DEBUG", "INFO", "WARN", "NOTICE", "FATAL", "CRIT", "SEVERE"},{"alert", "trace", "debug", "info", "warn"}};
	ifstream file("allTimeStampList.txt");
	int numOfFiles;
	mutex mtx;
	string line;
		
	if (file.is_open())
	{

		while(getline(file, line))
		{
			timeStampFormats.push_back(line);
		}
		file.close();
	}
	else 
	{
		cout << "Unable to open file";
		exit(1);
	}
	int cores = NUMOFTHREADS;		
	cout << "Enter the number of files to be generated : ";
	cin>>numOfFiles;
	cout << "Enter the directory(followed by forward slash /) in which files will be generated : ";
        string mydir;
	cin >> mydir;
	if(dirExists(mydir)!=1)
	{
		cout<<"Entered directory does not exists"<<endl;
		exit(2);
	}
	
	static int thread_count = 0;
	if((numOfFiles/cores)<1)
	{
		cores = numOfFiles;
	}

	int filesPerThread = static_cast<int>(numOfFiles/cores) ;
	int remainingFiles =  numOfFiles % cores; 
	std::thread *t = new std::thread[cores];
	for(int i=0;i<cores;i++)
	{
		*(t+i) = thread(LogSimulator_wrapper,i, ref(timeStampFormats),ref(logLevels), ref(thread_count), ref(remainingFiles), ref(filesPerThread), ref(cores), ref(mtx), ref(mydir));			
	}
	for(int i=0;i<cores;i++)
	{
		if((t+i)->joinable())
		{
			(t+i)->join();
		}
	}

	t = nullptr;

	return 0;
}
