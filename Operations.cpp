#include "Operations.h"
#include "JSONlightparser.h"
/*
void CRUD(string instruction) {

}
*/
map <string, map<string, string>> RecordDefinitions;
map <string, map<string, string>> getDefinitions() {
	
		return RecordDefinitions;
	
}
map <string, string> getDefinitions(string def) {
	return RecordDefinitions[def];
}
map <string, string> userDefinition(){
	map <string,string> user;
	user["username"] = "string.username";
	user["password"] = "string.password";
	user["type"] = "string";
	return user;
}

map <string, string> inquiryDefinition() {
	map<string, string> inquiry;
	inquiry["Inquiry Number"] = "int";
	inquiry["Inquirer Name"] = "string.username";
	inquiry["Date"] = "string.date";
	inquiry["Address"] = "string";
	inquiry["Telephone No"] = "string.phoneno";
	inquiry["Qualification"] = "string";
	inquiry["Age"] = "int";
	inquiry["Date of Birth"] = "string.date";
	return inquiry;
}


void initializeDefinitions() {
	RecordDefinitions["User"] = userDefinition();

}
void printDefinitions(map<string,map<string, string>> Definition) {
	for (map<string, map<string, string>>::iterator ii = Definition.begin(); ii != Definition.end(); ++ii)
	{		
		cout << (*ii).first << ": " << endl;
		for (map<string, string>::iterator ic = (*ii).second.begin(); ic != (*ii).second.end(); ++ic) {
			cout << (*ic).first << ": " << (*ic).second << endl;
		}
	}

}
void printDefinitions(map<string, string> Definition) {
	for (map<string, string>::iterator ii = Definition.begin(); ii != Definition.end(); ++ii)
	{
		cout << (*ii).first << ": " <<(*ii).second<< endl;	
	}

}
void readfile() {
	string STRING;
	ifstream infile;
	infile.open("names.txt");
	string users[4];
	int usercount = 0;
	while (!infile.eof()) // To get you all the lines.
	{
		if (usercount <= 3) {
			getline(infile, STRING);
			users[usercount] = STRING;
			usercount++;
			if (usercount == 4) {
				printDefinitions(readChunk(users, 4));
				usercount = 0;
			}
		}
		
		 // Saves the line in STRING.

		 // Prints our STRING.
	}
	infile.close();
	system("pause");
}
/*
bool Create(map<string, string> Record, string collectionName) {
	// for simplicity of storage and data stuctures as well as the algorithm itself we use a simple <string,string> type records reguardless of its actual datatype
	// and later we try and map it into a record refinition file for validation purposes.
	for (map<string, string>::iterator ii = Record.begin(); ii != Record.end(); ++ii)		
	{
	
			cout << (*ii).first << ": " << (*ii).second << endl;
	
	}

}
*/