#include "Navigator.h"
#include "Models.h"

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
	system("cls");
	int menuid = 0;
	unsigned int mno = 0;
	cout << "Welcome to Inquiry system- ESOFT" << endl;
	cout << to_string(mno) + ". Add Inquiry" << endl;
	cout << to_string(++mno) + ". Update Inquiry" << endl;
	cout << to_string(++mno) + ". Search Inquiry" << endl;
	cout << to_string(++mno) + ". Display Inquiry" << endl;
	cout << to_string(++mno) + ". Delete Inquiry" << endl;
	if (currentuser().isLoggedin() & (currentuser().user["type"] == "Admin" | currentuser().user["type"] == "admin")) {
		cout << to_string(++mno) + ". User Config" << endl;
	}
	cout << to_string(++mno) + ". Options" << endl;
	cout << to_string(++mno) + ". Help" << endl;
	cout << to_string(++mno) + ". Quit" << endl;
	cin >> menuid;
	switch (menuid) {
	case 5: {
		userConfigMenu();
	}
	}

}
	
void LoginMenu() {
	system("cls");
	
	cout << "Welcome to Inquiry system - Login" << endl;
	if (!currentuser().isLoggedin()) {
		cout << "Signin to enter main menu :" << endl;		
		userModel newUser(getRecords(userModel::schema, vector<string>{ "type" }));
		genericResult signinResult=newUser.signIn();
	
	
		if (signinResult.success) {
			cout << "Successfully logged in ! - \nPress any key to enter" << endl;
			getchar();
			MainMenu();
		}
		else {
			cout << "login attemp failed ! \nPress any key to retry" <<endl;
			cout << signinResult.message << endl;
			getchar();
			LoginMenu();

		}
	}
	
}

void  userConfigMenu() {
	system("cls");
	cout << "<<USER Management>>" << endl;
	if (!currentuser().isLoggedin()) {
		unsigned int mno = 0;
		
		cout << to_string(mno) + ". Add User" << endl;
		cout << to_string(++mno) + ". Delete User" << endl;
		cout << to_string(++mno) + ". Main Menu" << endl;
		cout << to_string(++mno) + ".Quit" << endl;
		cout << "Enter your selection 0.."+to_string(mno)+" for the relevent task" << endl;
		cin >> mno;
		switch (mno) {
			case 0: {
				map<string, string> newuserinp = getRecords(userModel::schema);
				genericResult actionresult = userModel::addUser(newuserinp);
				if (actionresult.success) {
					cout << "Successfully added a new user!" << endl;
					cout << "Press any key to go back to previous menu" << endl;
					getchar();
					userConfigMenu();
				}
				else {
					cout << "Creating new user failed !" << endl;
					cout << actionresult.message << endl;
				}

				break;

		}
			
		case 1: {
			map<string, string> deleteusr = getRecords(userModel::schema, vector<string>{"password", "type"});
			genericResult actionresult = userModel::addUser(deleteusr);
			userModel::removeUser(deleteusr);
			if (actionresult.success) {
				cout << "Successfully added a new user!" << endl;

			}
			else {
				cout << "Delete failed !" << endl;
				cout << actionresult.message << endl;

			}
		}
	}
		
	}

	cout << "Press any key to go back to previous menu" << endl;
	getchar();
	userConfigMenu();
}

void HelpMenu() {
	cout << "1. Adding Inquiry" << endl;
	cout << "2. Updating Inquiry" << endl;
	cout << "3. Searching Inquiry" << endl;
	cout << "4. Displaying Inquiry" << endl;
	cout << "5. Deleting Inquiry" << endl;
}