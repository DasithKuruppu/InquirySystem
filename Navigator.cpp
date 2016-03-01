#include "Navigator.h"

void navigateMainMenu(string commands) {
	system("cls");
	Initialize();
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
		map <string, string> schemainq = getInquiry(getSchema("inquiry"));
		string inqloc = getConfig("inquiry")["location.data"];
		Addrecord(schemainq,inqloc, 10);
		system("cls");
		cout << "Record added successfully !" << endl;

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

void HelpMenu() {
	cout << "1. Adding Inquiry" << endl;
	cout << "2. Updating Inquiry" << endl;
	cout << "3. Searching Inquiry" << endl;
	cout << "4. Displaying Inquiry" << endl;
	cout << "5. Deleting Inquiry" << endl;
}