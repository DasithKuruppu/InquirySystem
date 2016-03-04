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
struct userstatus {
	map<string, string> user = {};
	map<string, string> getUser() {
		return user;
	}
	void setUser(map<string, string> usr) {
		user = usr;
	}
	bool isLoggedin() {
		return (user.size() > 0);
	}
};

void Initialize();
void signup(map <string, string> info);
userstatus currentuser();
bool login(map<string, string> logindata);
void printRecord(map<string, map<string, string>> Definition);
void printRecord(map<string, string> Definition);
void printRecord(map<int, map<string, string>> Definition);
map<int, map<string, string>> readfile(string location,int chunk = 4);
string generatehash(string& pw);
map<string, string> readALL(string location);
map <string, string> getConfig(string args);
map <string, string> getSchema(string args);
void update(map<string, string> originalrecord, map<string, string> updaterecord,string location,int chunk = 4);
void Addrecord(map<string, string> newrecord, string location, int chunk);
void deleteRecord(map<string, string> Deleterecord, string location, const int chunk);
map<string, string> findWhere(map<string, string> queryobj, string location, int chunk);
void logger(string message, clock_t opstarttime, clock_t opendtime);
#endif