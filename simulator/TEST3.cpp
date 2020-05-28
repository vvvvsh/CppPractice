#include<iostream>
//#include <stdio.h>      /* puts */
#include <time.h>       /* time_t, struct tm, time, localtime, strftime */

using namespace std;

int main ()
{
  time_t rawtime;
  struct tm * timeinfo;
  char buffer [80];

  time (&rawtime);
  timeinfo = localtime (&rawtime);

  //strftime (buffer,80,"%G-%m-%d\'T\'%T*%z+0000",timeinfo);
  //strftime (buffer,80,"%G-%m-%d\'T\'%T*%z",timeinfo);
  //strftime (buffer,80,"%a %b %d %T %G",timeinfo);
  //strftime (buffer,80,"%G-%m-%d-%T.675872",timeinfo);
  //strftime (buffer,80,"%G-%m-%d\'T\'%T*%z",timeinfo);
  //strftime (buffer,80,"%g/%m/%d %T",timeinfo);
  //strftime (buffer,80,"%G-%m-%d\'T\'%T*633%z",timeinfo);
  //strftime (buffer,80,"%G %b %d %T.211 %Z",timeinfo);
  strftime (buffer,80,"%d/%b/%G:%T %z",timeinfo);
  string s = string(buffer);
  cout<<s<<"\n";
  return 0;
}
