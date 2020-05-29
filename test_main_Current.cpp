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
#include<utility>
using namespace std;
using namespace std::chrono;



void LogSimulator_wrapper(int i_start, int i_end, vector<string> &timeStampFormats,vector<vector<string>> &logLevels, int &thread_count, int &remainingFiles, int &filesPerThread, int &cores, mutex &mtx)
{
	++thread_count;

	cout<<"i_end-i_start=>"<<(i_end-i_start)<<endl;

	string fileName;
	
	vector<pair<LogSimulator*, int>> vec;
	
	for(int i=i_start; i<i_end; i++)
	{
		fileName = static_cast<string>("log_" + to_string(i) + ".log");
		vec.push_back(make_pair(new LogSimulator(fileName), i));
		cout<<"start:"<<i_start<<", end:"<<i_end<<", fileName:"<<fileName<<", i:"<<i<<endl;	
	}
	for(auto v:vec)
        {
		(v.first)->simulateLogFile(timeStampFormats, logLevels, (v.second));
	}

	for(auto v:vec)
        {
              delete (v.first);
        }

	/*
	//LogSimulator *obj_LogSimulator[2*filesPerThread];

	{
		const lock_guard<mutex> lock(mtx);

		cout<<"tid::"<< std::this_thread::get_id()<<", tindex:"<<tindex<<", thread_count:"<<thread_count<<", remainingFiles:"<<remainingFiles<<", filesPerThread:"<<filesPerThread<<", cores"<<cores<<endl;

		int i = 0;
		for(i = tindex*filesPerThread; i<(filesPerThread + tindex*filesPerThread); i++)
		{
			fileName = static_cast<string>("log_" + to_string(i) + ".log");
			//*(obj_LogSimulator+i) = new LogSimulator(fileName);
			cout <<"Log_file_wrapper1::"<<std::this_thread::get_id()<<" => "<<fileName <<", fileindex: " <<i << " "<<filesPerThread <<endl;
		}

		if(remainingFiles != 0)
		{
			
			//const lock_guard<mutex> lock(mtx);		
			i = filesPerThread*cores + remainingFiles - 1;
			//cout<<"END i:"<<(filesPerThread*cores + remainingFiles-1)<<endl;
			//--remainingFiles;
			fileName = static_cast<string>("log_" + to_string(i) + ".log");
			//*(obj_LogSimulator+i) = new LogSimulator(fileName);
			cout <<"Log_file_wrapper2::"<<std::this_thread::get_id()<<" => "<<fileName <<", fileindex: " <<i <<endl;
			i++;	
			--remainingFiles;
		}
	}
	/*
	   while(tindex == cores-1 && (i < noOfFiles))
	   {
	   fileName = static_cast<string>("log_" + to_string(i) + ".log");
	//*(obj_LogSimulator+i) = new LogSimulator(fileName);
	cout <<"Log_file_wrapper2::"<<this_id<<" => "<<fileName <<", fileindex: " <<i <<endl;
	i++;
	}*/
	/*
	   for(int j=0; j<1000;j++)
	   {
	   int k=0;
	   for(k = tindex*filesPerThread; k<(filesPerThread + tindex*filesPerThread); k++)
	   {
	   cout<<"k value:"<<k<<endl;
	//(obj_LogSimulator[k])->simulateLogFile(timeStampFormats, logLevels, k);
	}

	//	while(tindex == cores-1 && (k < noOfFiles))
	//	{
	//		(obj_LogSimulator[k])->simulateLogFile(timeStampFormats, logLevels, k);
	//		k++;
	//	}	
	cout<<"loop:"<<to_string(j)<<endl;
	sleep(1);               
	}
	*/	
	//delete[] *obj_LogSimulator;
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
	
	int i_start;
        int i_end;
	int f_count = numOfFiles;

	for(int i=0;i<cores;i++)
	{
		if(cores*filesPerThread != numOfFiles)
		{
			if(remainingFiles != 0)
			{	
				i_start = f_count - (filesPerThread + 1);
				i_end = f_count;
				--remainingFiles;
				f_count = f_count - (filesPerThread + 1); 
			}
			else
			{
				i_start = 0;
                                i_end = f_count;
			}
		}
		else
		{
			i_start = f_count - filesPerThread;
			i_end = f_count;
			f_count = f_count - filesPerThread;
		}
		//cout<<"i::"<<i<<", i_start:"<<i_start<<", i_end:"<<i_end<<endl;
		*(t+i) = thread(LogSimulator_wrapper,i_start, i_end, ref(timeStampFormats),ref(logLevels), ref(thread_count), ref(remainingFiles), ref(filesPerThread), ref(cores), ref(mtx));			
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
