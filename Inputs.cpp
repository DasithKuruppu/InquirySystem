#include "Inputs.h"
bool ignoreFields(string field,vector<string> Fieldslist) {
	for (unsigned int i = 0;i < Fieldslist.size();i++) { // Determine if a perticular string is in the ignore list[] if so return true;
		if (field == Fieldslist[i]) {
			return true;
		}
	}
	return false;
}
vector<string> stringsplit(string str) {
	istringstream iss(str);
	vector<string> outputvec;
	string sub;
	while (iss >> sub) {
		outputvec.push_back(sub);
	}
	return outputvec;
}
string getInput(string Field, string subtype, vector<string> ignore, bool validate = false, bool acceptnulls =true) {
	vector<string> Fieldinfo = stringsplit(subtype);
	string Fielddata;
	bool allownull = acceptnulls;
	if (Fieldinfo.size() > 1) {
		allownull= !(Fieldinfo[1] == "NOTNULL" && acceptnulls);
	}
	else {
		allownull = true;
	}
		
	subtype = stringsplit(subtype)[0];
	// Check explicitly to see if subtype is password
	// mask it with asterics (*) if it is , otherwise get standered input.
	if (!ignoreFields(Field,ignore) & subtype!="string.password") { // If not password
		cout << Field + " : ";		
		
		getline(cin, Fielddata);

		
	}
	else if(!ignoreFields(Field,ignore) & subtype=="string.password") {  // If it is a password
		
		char ch;
		const char ENTER = 13;
		cout << Field + " : ";
		while ((ch = _getch()) != ENTER) // Mask the chars with * and append chars entered into a string.
		{
			Fielddata += ch;
			std::cout << '*';
		}
		cout << endl; // ohh yea don't forget the endl
		
	}
	autoGenerate(subtype, Fielddata, validate);
    genericResult valcontainer=validateandNormalizeField(subtype, Fielddata,allownull,validate);
	if (!valcontainer.success) {
		throw invalid_argument(valcontainer.message);
	}
	
	
	return Fielddata;
}


map<string, string> getRecords(map<string, string> schema, vector<string> ignoreFields,bool validate,bool allownulls) {
	map<string, string> record;
	map<string, string> errstack;
	for (map<string, string>::iterator definition = schema.begin(); definition != schema.end(); ++definition) {
		string data="";
		
			try {
				data = getInput((*definition).first, (*definition).second,ignoreFields,validate,allownulls);
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