#include "Navigator.h"

void navigateMainMenu(string commands) {
	system("cls");
	MainMenu();
	cout << "Sub-menu number you wish to enter to :";
	string action;
	getline(cin, action);
	if (action == "4") {
		system("cls");
		cout << "List of all Inquiries :" << endl;
		printRecord(readfile(getConfig("inquiry")["location.data"],10));
		cout <<endl << "Press 1 and Enter to get back to Main menu" << endl;
		getline(cin, action);
		if (action == "1") {
			navigateMainMenu("d");
		}
	}
	if (action == "1") {
		system("cls");
		cout << "Add new Inquiry :" << endl;
		map <string, string> schemainq;
		bool errflag = false;
		try {
			schemainq = getRecords(getSchema("inquiry"));
		}	
		catch (map<string,string> e) {
			errflag = true;
			schemainq = e;
		}
		string inqloc = getConfig("inquiry")["location.data"];
		system("cls");
		if (errflag) {
			cout << "Adding record failed !" << endl;
			printRecord(schemainq);
		}
		else {
			Addrecord(schemainq, inqloc, 10);
			cout << "Record added successfully !" << endl;
		}


		cout << endl << "Press 1 and Enter to get back to Main menu" << endl;
		getline(cin, action);
		if (action == "1") {
			navigateMainMenu("d");
		}
	}
}

void MainMenu() {
	cout << "Welcome to Inquiry system- ESOFT"<<endl;
	cout << "1. Add Inquiry" << endl;
	cout << "2. Update Inquiry" << endl;
	cout << "3. Search Inquiry" << endl;
	cout << "4. Display Inquiry" << endl;
	cout << "5. Delete Inquiry" << endl;
	cout << "6. Help" << endl;

}
void LoginMenu() {
	cout << "Welcome to Inquiry system - Login" << endl;
	cout << "1. Login" << endl;
	cout << "2. Signup" << endl;
	cout << "Sub-menu number you wish to enter to :";
	string action;
	getline(cin, action);
	Initialize();
	if (action == "1") {
		system("cls");
		cout << "Log into Inquiry management system :" << endl;
		map <string, string> usr;
		bool errflag = false;
		try {
			usr = getRecords(getSchema("user"));
		}
		catch (map<string, string> e) {
			errflag = true;
			usr = e;
		}
		if (errflag) {
			cout << "Error occured during login" << endl;

		}
		else {
			if (login(usr)) {
				cout << "successfully logged in !";
				cout << "press any key for mainmenu";
				string x;
				cin >> x;
				navigateMainMenu("e");
			};
		}
	}
	else if (action == "2") {
		system("cls");
		cout << "Signup into Inquiry management system :" << endl;

		map <string, string> usr;
		bool errflag = false;
		try {
			usr = getRecords(getSchema("user"));
		}
		catch (map<string, string> e) {
			errflag = true;
			usr = e;
		}
		if (errflag) {
			cout << "Error occured during login" << endl;

		}
		else {
			signup(usr);
			cout << "User added!" << endl;
			cout << "press any key to access main menu";
			getchar();
			navigateMainMenu("o");
		}
	}
}

void HelpMenu() {
	cout << "1. Adding Inquiry" << endl;
	cout << "2. Updating Inquiry" << endl;
	cout << "3. Searching Inquiry" << endl;
	cout << "4. Displaying Inquiry" << endl;
	cout << "5. Deleting Inquiry" << endl;
}