#include "Validation.h"
#include "Operations.h"
using namespace std;
void main()
{
	//initializeDefinitions();
	
	//printDefinitions(getDefinitions("User"));
	map<string, string> originalrecord = {
		{ "user","xueyz" },
		{ "password" , "MEWEEOW#$#@#" }
	};
	map<string, string> updaterecord = {
		{"user","Dasith"},
	    {"password" , "MEWEEOW#$#@#"}
	};
	update(originalrecord,updaterecord);
	system("Pause");
}