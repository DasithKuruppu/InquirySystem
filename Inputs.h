#ifndef Inputs    // To make sure you don't declare the function more than once by including the header multiple times.
#define Inputs
#include<iostream>
#include<string>
#include <map>
#include "Validation.h"
#include <iomanip>
#include <ctime>
using namespace std;

map<string, string> getRecords(map<string, string> schema, vector<string> ignoreFields = { "Inquiry Number","Date" });
bool ignoreFields(string field, vector<string> Fieldslist);
string AutoIDgenerator();
#endif