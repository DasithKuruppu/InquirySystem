#include "Operations.h"
#include "JSONlightparser.h"
/*
void CRUD(string instruction) {

}
*/
map <int, map<string,string>> config = readfile("./storage/config/user.config", 4);

map <string, map<string, string>> RecordDefinitions;
map <string, map<string, string>> getDefinitions() {
	
		return RecordDefinitions;
}
map <string, string> getConfig(string args) {
	return config[0];
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
	RecordDefinitions["Inquiry"] = inquiryDefinition();
}
void printRecord(map<string,map<string, string>> Definition) {
	for (map<string, map<string, string>>::iterator ii = Definition.begin(); ii != Definition.end(); ++ii)
	{		
		cout << (*ii).first << ": " << endl;
		for (map<string, string>::iterator ic = (*ii).second.begin(); ic != (*ii).second.end(); ++ic) {
			cout << (*ic).first << ": " << (*ic).second << endl;
		}
	}

}
void printRecord(map<string, string> Definition) {
	for (map<string, string>::iterator ii = Definition.begin(); ii != Definition.end(); ++ii)
	{
		cout << (*ii).first << ": " <<(*ii).second<< endl;	
	}

}
map<int, map<string, string>> readfile(string location,int chunk) {
	string STRING;
	ifstream infile;
	infile.open(location);
	string *users=new string[chunk];
	int usercount = 0;
	int recordcount = 0;
	map<int, map<string, string>> returnMap;
	while (!infile.eof()) // To get you all the lines.
	{
		if (usercount <= chunk-1) {
			getline(infile, STRING);
			users[usercount] = STRING;
			usercount++;
			if (usercount == chunk) {
				returnMap[recordcount]=readChunk(users, chunk);
				usercount = 0;
				recordcount++;
			}
		}
		
		 // Saves the line in STRING.

		 // Prints our STRING.
	}
	infile.close();
	return returnMap;
}
template <typename Map>
bool compare_Record(Map const &lhs, Map const &rhs) {
	// No predicate needed because there is operator== for pairs already.
	return equal(lhs.begin(), lhs.end(),
			rhs.begin());
}

void update(map<string,string> originalrecord, map<string, string> updaterecord,const int chunk) {
	/* due to OS limitations its not possible to update a file without actually rewriting the entire file, 
	or the changes should be of the same bitecount to actually do a successful write to the perticular part only
	since this is almost never the case a simpler approach is taken, An actual DB would be a better way to go
	since its not part of the syllabus yet this seems the best approach at the time*/
	string STRING;
	ifstream infile;
	ofstream ofile;;
	infile.open("names.txt");
	ofile.open("updating.txt");
	string *txtlines= new string[chunk];;
	int linecount = 0;
	while (!infile.eof()) // To get you all the lines.
	{
		if (linecount <= chunk-1) {
			getline(infile, STRING);
			txtlines[linecount] = STRING;
			linecount++;
			if (linecount == chunk) {
				map <string, string> storedrecord = readChunk(txtlines, chunk);
				if (compare_Record(storedrecord, originalrecord)) {
					writeChunk(updaterecord, ofile);
				}
				else {
					writeChunk(storedrecord, ofile);
				}
				linecount = 0;
			}
		}

		// Saves the line in STRING.

		// Prints our STRING.
	}
	infile.close();
	ofile.close();
}
void search(string keywords) {

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