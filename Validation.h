#pragma once
#ifndef Validation    // To make sure you don't declare the function more than once by including the header multiple times.
#define Valudation

#include<regex>
#include<iostream>
#include<string>
#include <sstream>
#include <ctime>
#include <iomanip>
#include <map>
using namespace std;
struct genericResult {
	bool success = false;
	string message = "";
	map<string, string> errorstack;
};

bool valDateTime(const std::string& s);
genericResult validateandNormalizeField(string subtype, string &Fielddata, bool allownull=true, bool validate=true);
void autoGenerate(string subtype, string &Fielddata, bool enable);
string calculateAge(string DOB);


#endif