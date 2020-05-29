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
using namespace std;
using namespace std::chrono;



void LogSimulator_wrapper(int tindex, vector<string> &timeStampFormats,vector<vector<string>> &logLevels, int &thread_count, int &remainingFiles, int &filesPerThread, int &cores, mutex &mtx)
{
	++thread_count;

	string fileName;
	//auto this_id = std::this_thread::get_id();
	//LogSimulator *obj_LogSimulator[2*filesPerThread];
	vector<pair<LogSimulator*, int>> vec;
		cout<<"tid::"<< std::this_thread::get_id()<<", tindex:"<<tindex<<", thread_count:"<<thread_count<<", remainingFiles:"<<remainingFiles<<", filesPerThread:"<<filesPerThread<<", cores"<<cores<<endl;
i	
		int i = 0;
		for(i = tindex*filesPerThread; i<(filesPerThread + tindex*filesPerThread); i++)
		{
			fileName = static_cast<string>("log_" + to_string(i) + ".log");
			vec.push_back(make_pair(new LogSimulator(fileName), i));
			//*(obj_LogSimulator+i) = new LogSimulator(fileName);
			cout <<"Log_file_wrapper1::"<<std::this_thread::get_id()<<" => "<<fileName <<", fileindex: " <<i << " "<<filesPerThread <<endl;
		}

		if(remainingFiles != 0)
		{
			
			const lock_guard<mutex> lock(mtx);		
			i = filesPerThread*cores + remainingFiles - 1;
			fileName = static_cast<string>("log_" + to_string(i) + ".log");
			//*(obj_LogSimulator+i) = new LogSimulator(fileName);
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


int main()
{
	vector <string> timeStampFormats  = 
	{
		"Sun Dec 04 04:47:44 2005", //Apache	//1
		"2005-06-03-15.42.50.675872" //BGL	//2
			"2015-10-18 18:01:47,978", //HADOOP	//3
		"20171223-22:15:29:606", //HEALTH APP	//4
		"Jun 14 15:16:01", //MAC & LINUX	//5
		"2017-05-16_13:53:08", //OpenStack	//6
		"10.30 16:49:06", //Proxifier	//7
		"17/06/09 20:10:40", //SPARX	//8
		"2005.11.09 Nov 9 12:01:01", //THUNDERBIRD	//9
		"2016-09-28 04:30:30", //WINDOWS	//10
		"2015-07-29 17:41:44,747", //ZOOKEEPER	//11
		"2018-08-20'T'13:20:10*633+0000"}; //12

	vector<vector <string>> logLevels = {{"ALERT", "TRACE", "DEBUG", "INFO", "WARN", "NOTICE", "FATAL", "CRIT", "SEVERE"},{"alert", "trace", "debug", "info", "warn"}};
	ifstream file("allTimeStampList.txt");
	int numOfFiles;
	mutex mtx;
	string line;
	/*	
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
		}
		*/	
	string directory;
	cout << "Enter the number of files to be generated : ";
	cin>>numOfFiles;
	//cout << "Enter the Directory of files to be generated : ";
	//  cin>>directory;
	//	int cores = NUMOFTHREADS;
	int cores = 5;
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
		*(t+i) = thread(LogSimulator_wrapper,i, ref(timeStampFormats),ref(logLevels), ref(thread_count), ref(remainingFiles), ref(filesPerThread), ref(cores), ref(mtx));			
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
