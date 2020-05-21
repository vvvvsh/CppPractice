//Note: To Compile this program use g++ -std=c++11 -pthread filename.cpp

#include <iostream>
#include <thread>
using namespace std;

void function1(int a)
{
	for(int i=0;i<a;i++)
	{
		cout << "Pointer " << i << endl;
	}
}

class TestThreading
{
public:
	void operator()(int x)
	{
		for(int i=0;i<x;i++)
		{
			cout << "Object " << i << endl; 
		}
	}
};

int main()
{
	cout << "Implementing threads 1,2,3" << endl;
	
	thread t1(function1,4);
	thread t2(TestThreading(), 4);
	auto m= [](int x) {
				for (int j=0;j<x;j++)
				cout << "Lamda " << j << endl;
			  };

	thread t3(m,4);
	t1.join();
	t2.join();
	t3.join();
	
return 0;
}


