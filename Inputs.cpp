#include "Inputs.h"
void createField(string Field) {
	cout << Field + " :";
}

string getInput(string Field,string subtype) {
	string Fielddata;
	createField(Field);
	cin >> Fielddata;
	cout << endl;
	return Fielddata;
}
int getInput(string Field) {
	int Fielddata;
	createField(Field);
	cin >> Fielddata;
	cout << endl;
	return Fielddata;
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