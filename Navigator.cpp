#include "Navigator.h"
#include "Models.h";

userModel loggedinuser(map<string, string>{});
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
	unsigned int mno= 0;
	cout << "Welcome to Inquiry system- ESOFT"<<endl;
	cout << to_string(mno)+". Add Inquiry" << endl;
	cout << to_string(++mno)+". Update Inquiry" << endl;
	cout << to_string(++mno)+". Search Inquiry" << endl;
	cout << to_string(++mno)+". Display Inquiry" << endl;
	cout << to_string(++mno) + ". Delete Inquiry" << endl;
	if (currentuser().isLoggedin() & (currentuser().user["type"] == "Admin" | currentuser().user["type"] == "admin")) {
		cout << to_string(++mno) + ". User Config" << endl;
	}
	cout << to_string(++mno) + ". Options" << endl;
	cout << to_string(++mno) + ". Help" << endl;
	cout << to_string(++mno) + ". Quit" << endl;
}
void LoginMenu() {
	system("cls");
	
	cout << "Welcome to Inquiry system - Login" << endl;
	if (!currentuser().isLoggedin()) {
		cout << "Signin to enter main menu :" << endl;		
		userModel newUser(getRecords(userModel::schema, vector<string>{ "type" }));
		genericResult signinResult=newUser.signIn();
	
	
		if (signinResult.success) {
			cout << "Successfully logged in ! - /n Press any key to enter" << endl;
			getchar();
			MainMenu();
		}
		else {
			cout << "login attemp failed ! /n Press any key to retry" <<endl;
			cout << signinResult.message << endl;
			getchar();
			LoginMenu();

		}
	}
	
}

void  userConfigMenu() {
	system("cls");
	cout << "User Config :" << endl;
	char action = '1';
	/*switch (action) {
	case '1':



	}*/

	/*map <string, string> usr;
	bool errflag = false;
	try {
		usr = getRecords(getSchema("user"));
	}
	catch (map<string, string> e) {
		errflag = true;
		usr = e;
	}
	if (errflag) {
		cout << "Error occured when adding user" << endl;

	}
	else {
		signup(usr);
		cout << "User added!" << endl;
		cout << "press any key to access main menu";
		getchar();
		navigateMainMenu("o");
	}*/
}

void HelpMenu() {
	cout << "1. Adding Inquiry" << endl;
	cout << "2. Updating Inquiry" << endl;
	cout << "3. Searching Inquiry" << endl;
	cout << "4. Displaying Inquiry" << endl;
	cout << "5. Deleting Inquiry" << endl;
}