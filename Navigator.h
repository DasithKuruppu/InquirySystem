#pragma once
#pragma once
#ifndef Navigator    // To make sure you don't declare the function more than once by including the header multiple times.
#define Navigator
#include<iostream>
#include<string>
#include<regex>
#include "Operations.h"
#include "Inputs.h"
using namespace std;
void MainMenu();
void HelpMenu();
void navigateMainMenu(string commands);
void LoginMenu();
#endif