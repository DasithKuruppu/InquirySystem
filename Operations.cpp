#include "Operations.h"
#include "JSONlightparser.h"

// ALL basic CRUD ops on records goes here , including schema 

map <string, map<string,string>> config;
map <string, map<string, string>> schema;

map <string, string> getConfig(string args) {
	return config[args];
}
map <string, string> getSchema(string args) {
	return schema[args];
}

void Initialize() {
	// load initial configs
	clock_t starttime = clock();
	config["user"] = readALL("./storage/config/user.config");
	config["inquiry"] = readALL("./storage/config/inquiry.config");

	logger("Configs loaded from '/storage/config/'", starttime, clock());
	//load schema for the two configs expected above
	schema["user"] = readALL(config["user"]["location.schema"]);
	schema["inquiry"] = readALL(config["inquiry"]["location.schema"]);
	
}

void logger(string message, clock_t opstarttime, clock_t opendtime) {
	unsigned int total_time_ticks;
	if (opstarttime == ((clock_t)-1) || opendtime == ((clock_t)-1))
	{
		total_time_ticks = 0;
	}
	else
	{
		total_time_ticks = (unsigned int)(opendtime - opstarttime);
	}
	cout << "Log :" + message + " completed in " + to_string(total_time_ticks) + "ms "<<endl;
}



void printRecord(map<int,map<string, string>> Definition) {
	for (map<int, map<string, string>>::iterator ii = Definition.begin(); ii != Definition.end(); ++ii)
	{		
		cout <<endl<< "<< Record number: "<<to_string((*ii).first) << ">>" << endl <<endl;
		for (map<string, string>::iterator ic = (*ii).second.begin(); ic != (*ii).second.end(); ++ic) {
			cout << (*ic).first << ": " << (*ic).second << endl;
		}
	}

}
void printRecord(map<string, map<string, string>> Definition) {
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
void signup(map <string, string> info) {
	info["password"] = generatehash(info["password"]);
	Addrecord(info, getConfig("user")["location.data"], 5);
	
}
bool login(map<string, string> logindata) {
	logindata["password"] = generatehash(logindata["password"]);
	if (findWhere(logindata, getConfig("user")["location.data"], 5).size() > 0) {
		return true;
	}
	return false;
}
string generatehash(string& pw) {
	
	static const char* const lut = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ@.&$";
	size_t len = pw.length();

	std::string output;
	output.reserve(4 * len);
	for (size_t i = 0; i < len; ++i)
	{
		const unsigned char c = pw[i];
	
		output.push_back(lut[c >> 8]);
		output.push_back(lut[c & 31]);
	}
	output = output.substr(0, 15);
	return output;
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
map<string, string> readALL(string location) {
	string STRING;
	ifstream infile;
	infile.open(location);
	vector<string> info;
	int linecount = 0;
	map<string, string> returnMap;
	while (!infile.eof()) // To get you all the lines.
	{
		
			getline(infile, STRING);
			if (STRING != "\n") {
				info.push_back(STRING);
			}
			
			linecount++;
	}
	infile.close();
	
	
	returnMap = readChunk(&info[0], linecount);
	return returnMap;
}
template <typename Map>
bool compare_Record(Map const &lhs, Map const &rhs) {
	// No predicate needed because there is operator== for pairs already.
	return equal(lhs.begin(), lhs.end(),
			rhs.begin());
}

void update(map<string,string> originalrecord, map<string, string> updaterecord,string location,const int chunk) {
	/* due to OS limitations its not possible to update a file without actually rewriting the entire file, 
	or the changes should be of the same bitecount to actually do a successful write to the perticular part only
	since this is almost never the case a simpler approach is taken, An actual DB would be a better way to go
	since its not part of the syllabus yet this seems the best approach at the time*/
	string STRING;
	ifstream infile;
	ofstream ofile;
	infile.open(location);
	ofile.open(location+"temp");
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
	}
	infile.close();
	ofile.close();
	if (remove(location.c_str()) == 0) {
		if (rename((location + "temp").c_str(), location.c_str()) != 0) {
			throw runtime_error("Error Updating file");
		}
	}
	else {
		throw runtime_error("Error Updating file");
	}

}
bool queryMap(map<string, string> query, map<string, string> record) {
	for (map<string, string>::iterator ii = query.begin(); ii != query.end(); ++ii)
	{
		if (record[(*ii).first] != (*ii).second) {
			return false;
		}

	}
	return true;

}
map<string,string> findWhere(map<string,string> queryobj,string location,int chunk){
	string STRING;
	ifstream infile;
	ofstream ofile;
	infile.open(location);
	
	string *txtlines = new string[chunk];;
	int linecount = 0;
	while (!infile.eof()) // To get you all the lines.
	{
		if (linecount <= chunk - 1) {
			getline(infile, STRING);
			txtlines[linecount] = STRING;
			linecount++;
			if (linecount == chunk) {
				map <string, string> storedrecord = readChunk(txtlines, chunk);
				if (queryMap(queryobj, storedrecord)) {
					infile.close();
					ofile.close();
					return storedrecord;
				}
				linecount = 0;
			}
		}
	}

	infile.close();
	ofile.close();
	return map<string, string>{};
	
}
void search(string keywords,string location,int chunk) {

}

void Addrecord(map<string, string> newrecord,string location,int chunk) {
	string STRING;
	ofstream ofile;
	ofile.open(location, ios_base::app);
	
	writeChunk(newrecord, ofile);
	ofile.close();
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