#include "Inputs.h"
bool ignoreFields(string field,vector<string> Fieldslist) {
	for (int i = 0;i < Fieldslist.size();i++) {
		if (field == Fieldslist[i]) {
			return true;
		}
	}
	return false;
}
string getInput(string Field,string subtype,vector<string> ignore) {
	string Fielddata;
	if (!ignoreFields(Field,ignore)) {
		cout << Field + " : ";
		getline(cin, Fielddata);
	}
	
	if (subtype == "string.phoneno"){
		bool strph = valPhone(Fielddata);
		if (!strph) {
			throw invalid_argument("Phone number entered is invalid");
		}
	}
	else if (subtype == "system.datetime") {
		auto t = std::time(nullptr);
		auto tm = *std::localtime(&t);
		put_time(&tm, "%d-%m-%Y %H-%M-%S");
		Fielddata = to_string(tm.tm_wday) + "/" + to_string(tm.tm_mon) + "/" + to_string(1900 + tm.tm_year) +" " + to_string(tm.tm_hour) + "-"+to_string(tm.tm_min)+"-"+to_string(tm.tm_sec);
	}
	else if (subtype == "system.number") {
		Fielddata = AutoIDgenerator();
	}
	
	return Fielddata;
}

string AutoIDgenerator() {
	auto t = std::time(nullptr);
	auto tm = *std::localtime(&t);
	int clocktime = clock();
	return (to_string(tm.tm_sec + tm.tm_min*(60)+(tm.tm_mon*744))+to_string(clocktime));
}

map<string, string> getRecords(map<string, string> schema, vector<string> ignoreFields) {
	map<string, string> record;
	map<string, string> errstack;
	for (map<string, string>::iterator definition = schema.begin(); definition != schema.end(); ++definition) {
		string data="";
		
			try {
				data = getInput((*definition).first, (*definition).second,ignoreFields);
			}
			catch (invalid_argument& e) {
				errstack[(*definition).first] = e.what();
				
			}
			record[(*definition).first] = data;
			
		
		 // get inputs for each field
	}
	if (errstack.size() > 0) {
		throw errstack;
	}
	
		return record;
	

	
}



string PhoneNumberHelp(char inquiry) {
	string syntax = "0XX-XXXXXXX or 0XXXXXXXXX  or 0XX XXXXXXX";
	string example = "012-3456789 or 0123456789 or 012 3456789";
	// s = syntax
	// e = example
	switch (inquiry) {
	case 's':
		return syntax;
	case 'e':
		return example;
	default:
		return "none";
	}
}