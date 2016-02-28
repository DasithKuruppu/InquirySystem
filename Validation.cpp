#include "Validation.h"

bool valPhone(string phoneno) {
	char *s = new char[phoneno.length() + 1];
	strcpy(s, phoneno.c_str());

	auto m = cmatch{};

	return regex_match(s, m, regex{ R"(0\d{2}[-|\s]?\d{7})" });
	
	//samples possible - 0777790838 , 077-7790838 , 077 7790838
	
}



