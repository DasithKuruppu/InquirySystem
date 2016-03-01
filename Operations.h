#pragma once
#ifndef Operations    // To make sure you don't declare the function more than once by including the header multiple times.
#define Operations
#include<iostream>
#include<string>
#include<regex>
#include <map>
#include <utility>
#include <fstream>
#include <cstdio>
#include <ctime>


using namespace std;
void Initialize();
void printRecord(map<string, map<string, string>> Definition);
void printRecord(map<string, string> Definition);
void printRecord(map<int, map<string, string>> Definition);
map<int, map<string, string>> readfile(string location,int chunk = 4);
map<string, string> readALL(string location);
map <string, string> getConfig(string args);
map <string, string> getSchema(string args);
void update(map<string, string> originalrecord, map<string, string> updaterecord,string location,int chunk = 4);
void Addrecord(map<string, string> newrecord, string location, int chunk);
void logger(string message, clock_t opstarttime, clock_t opendtime);
#endif