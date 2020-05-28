#pragma once
#include<regex>
#include<string>
#include<vector>
#include <iostream>
using namespace std;

const string loglevel("ALERT|DEBUG|TRACE|NOTICE|FATAL|WARN|INFO|SEVERE|CRIT");
regex timestamprx1("([0-9]{2,4}[-][0-9]{1,2}[-][0-9]{1,2}\\s[0-9]{1,2}[:][0-9]{1,2}[:][0-9]{1,2}[,][0-9]{1,3})\\s*("+loglevel+")\\s\\s(.*$)");
regex timestamprx2("([0-9]{1,4}[_][0-9]{1,2}[:][0-9]{1,2}[:][0-9]{1,2})\\s*("+loglevel+")\\s\\s(.*$)");
vector<regex> regexvec = {timestamprx1, timestamprx2};
