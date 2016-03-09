#include "Validation.h"

bool valNumber(const string& s)
{
	return !s.empty() && find_if(s.begin(),
		s.end(), [](char c) { return !isdigit(c); }) == s.end();
}
bool valPhone(string &phoneno) {
	char *s = new char[phoneno.length() + 1];
	strcpy(s, phoneno.c_str());

	auto m = cmatch{};
	
	bool retval = regex_match(s, m, regex{ R"((0\d{2})[-|\s]?(\d{7})?)" });
	phoneno = string(m[1]) + string(m[2]);
	return retval;
	
	//samples possible - 0777790838 , 077-7790838 , 077 7790838
	
}
bool valUsername(string username) {
	char *s = new char[username.length() + 1];
	strcpy(s, username.c_str());

	auto m = cmatch{};

	return regex_match(s, m, regex{ R"((\w+){5,15})" }); // length between 5 & 15 can be alpha numberic with underscore
}

bool valPassword(string password) {
	
	char *s = new char[password.length() + 1];
	strcpy(s, password.c_str()); // convert string to char pointer this is done because regex_match requires a const char *

	auto m = cmatch{};

	return regex_match(s, m, regex{ R"(^(?=.*\d+)(?=.*[a-zA-Z]+)(?=.*[@#$&]*)(?=.{5,12}).*$)" }); 
	// must have at least 1 Alpha & 1 Nummeric character in it  + it allows for optional @ # $ & chars , also must be of length 5 - 12 
	// yes all the validations in a single line :)
}
bool valBDay(const std::string& s) {
	string age = calculateAge(s);
	if (atoi(age.c_str()) > 10) {
		return true;
	}
	else {
		return false;
	}
	
}

bool valDateTime(const std::string& s) {
	int d, m, y, hh, mm;
	std::istringstream is(s);
	char delimiter;
	if (is >> d >> delimiter >> m >> delimiter >> y >> delimiter >> hh >> delimiter >> mm) {
		struct tm t = { 0 };
		t.tm_min = mm,
		t.tm_hour=hh,
		t.tm_mday = d;
		t.tm_mon = m - 1;
		t.tm_year = y - 1900;
		t.tm_isdst = -1;

		// normalize:
		time_t when = mktime(&t);
		const struct tm *norm = localtime(&when);
		

		// validate (is the normalized date & time still the same?):
		return (norm->tm_mday == d    &&
			norm->tm_mon == m - 1 &&
			norm->tm_year == y - 1900 &&
			norm->tm_min == mm &&
			norm->tm_hour == hh);

	}
	return false;
}

genericResult validateandNormalizeField(string subtype, string &Fielddata,bool allownull, bool validate) {
	genericResult endResult;
	endResult.success = true;
	if (!validate) { // if validate is set to false;
		return endResult;
	}
	if (allownull & Fielddata == "") { // if null is allowed and field data is null
		return endResult;
	}
	if (!allownull && Fielddata == "") {
		endResult.success = false;
		endResult.message = "This field cannot be null";
		return endResult;
	}
	if (validate && subtype == "string.phoneno") { // if its a phone number
		bool strph = valPhone(Fielddata);
		if (!strph) {
			endResult.success = false;
			endResult.message = "Phone Number not in proper format; accepted formats are 0XX-XXXXXXX , 0XXXXXXXXX and 0XX XXXXXXX , where X is a Number {0-9}";
		}
	}
	if (validate && subtype == "system.number") {
		bool strnum = valNumber(Fielddata);
		if (!strnum) {
			endResult.success = false;
			endResult.message = "Not a valid input; accepted type is a Positive Number";
		}
	}
	if (validate && subtype == "system.datetime") {
		bool strdate = valDateTime(Fielddata);
		if (!strdate) {
			endResult.success = false;
			endResult.message = "Not a valid input; accepted format is dd/mm/yy hh:mm:ss";
		}
	}
	if (validate && subtype == "string.bday") {
		bool strint = valBDay(Fielddata);
		if (!strint) {
			endResult.success = false;
			endResult.message = "Not a valid input; accepted type is a date in format dd/mm/yy , where the age at the time of entry is more than 10";
		}
	}
	if (validate && subtype == "int.positive") {
		bool strint = valNumber(Fielddata);
		if (!strint) {
			endResult.success = false;
			endResult.message = "Not a valid input; accepted type is a Positive Number";
		}
	}
	return endResult;
}

void autoGenerate(string subtype, string &Fielddata, bool enable) { // set default to true
	if (enable && subtype == "system.number") {	
		auto t = std::time(nullptr);
		auto tm = *std::localtime(&t);
		int clocktime = clock();
		Fielddata= (to_string(tm.tm_sec + tm.tm_min*(60) + (tm.tm_mon * 744)) + to_string(clocktime));
	}
	else if (enable && subtype == "system.datetime") {
		auto t = std::time(nullptr);
		auto tm = *std::localtime(&t);
		put_time(&tm, "%d-%m-%Y %H-%M-%S");
		Fielddata = to_string(tm.tm_wday) + "/" + to_string(tm.tm_mon) + "/" + to_string(1900 + tm.tm_year) + "-" + to_string(tm.tm_hour) + ":" + to_string(tm.tm_min) + ":" + to_string(tm.tm_sec);
	}
}


string calculateAge(string DOB) {
	int d, m, y;
	istringstream is(DOB);
	char delimiter;
	if (is >> d >> delimiter >> m >> delimiter >> y) {
		struct tm ti = { 0 };
		ti.tm_mday = d;
		ti.tm_mon = m - 1;
		ti.tm_year = y - 1900;
		ti.tm_isdst = -1;

		// normalize:
		time_t when = mktime(&ti);
		const struct tm *norm = localtime(&when);

		// the actual date would be:
		// m = norm->tm_mon + 1;
		// d = norm->tm_mday;
		// y = norm->tm_year;
		// e.g. 29/02/2013 would become 01/03/2013
		auto t = time(nullptr);
		auto tm = *localtime(&t);
		put_time(&tm, "%d-%m-%Y");

		int yearsolder = tm.tm_year - ti.tm_year;
		if ((tm.tm_mon - ti.tm_mon) > 5) {
			yearsolder++;
		}

		// validate (is the normalized date still the same?):
		return to_string(yearsolder);
	}
	return "";
	
}

