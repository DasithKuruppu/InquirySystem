#pragma once
#ifndef Operations    // To make sure you don't declare the function more than once by including the header multiple times.
#define Operations
#include<iostream>
#include<string>
#include<regex>
#include <map>
#include <utility>
#include <fstream>


using namespace std;
map <string, map<string, string>> getDefinitions();
map <string, string> getDefinitions(string def);
void initializeDefinitions();
void printDefinitions(map<string, map<string, string>> Definition);
void printDefinitions(map<string, string> Definition);
map <string, string> userDefinition();
void readfile(int chunk = 4);
void update(map<string, string> originalrecord, map<string, string> updaterecord, const int chunk = 4);
#endif