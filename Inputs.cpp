#include "Inputs.h"

string getInput(string Field,string subtype) {
	string Fielddata;
	cout << Field + " :";
	getline(cin, Fielddata);
	if (subtype == "string.phoneno"){

	}
	return Fielddata;
}

map<string,string> getInquiry(map<string,string> schema) {
	map<string, string> record;
	for (map<string, string>::iterator definition = schema.begin(); definition != schema.end(); ++definition) {
		
		record[(*definition).first]=getInput((*definition).first,(*definition).second); // get inputs for each field
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