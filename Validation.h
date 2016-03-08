#pragma once
#ifndef Validation    // To make sure you don't declare the function more than once by including the header multiple times.
#define Valudation

#include<regex>
#include<iostream>
#include<string>
#include <sstream>
#include <ctime>

using namespace std;

bool valPhone(string phoneno);
bool valDateTime(const std::string& s);

#endif