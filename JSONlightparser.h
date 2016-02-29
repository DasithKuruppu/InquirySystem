#pragma once
#ifndef JSONlightparser    // To make sure you don't declare the function more than once by including the header multiple times.
#define JSONlightparser
#include <utility>
#include <fstream>
#include <iostream>
#include <regex>
#include <map>
using namespace std;

map <string, string> readChunk(string lines[], int length);
void writeChunk(map<string, string> record, ofstream &outputfile);
#endif