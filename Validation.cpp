#include "Validation.h"

bool valPhone(string phoneno) {
	char *s = new char[phoneno.length() + 1];
	strcpy(s, phoneno.c_str());

	auto m = cmatch{};

	return regex_match(s, m, regex{ R"((0\d{2}[-|\s]?\d{7})?)" });
	
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
bool valDate(const std::string& s, int& d, int& m, int& y) {
	std::istringstream is(s);
	char delimiter;
	if (is >> d >> delimiter >> m >> delimiter >> y) {
		struct tm t = { 0 };
		t.tm_mday = d;
		t.tm_mon = m - 1;
		t.tm_year = y - 1900;
		t.tm_isdst = -1;

		// normalize:
		time_t when = mktime(&t);
		const struct tm *norm = localtime(&when);
		// the actual date would be:
		// m = norm->tm_mon + 1;
		// d = norm->tm_mday;
		// y = norm->tm_year;
		// e.g. 29/02/2013 would become 01/03/2013
		
		// validate (is the normalized date still the same?):
		return (norm->tm_mday == d    &&
			norm->tm_mon == m - 1 &&
			norm->tm_year == y - 1900);

	}
	return false;
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