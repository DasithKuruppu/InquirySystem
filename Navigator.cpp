#include "Navigator.h"
#include "Models.h"

userModel loggedinuser(map<string, string>{});


void MainMenu() {
	system("cls");
	int menuid = 0;
	unsigned int mno = 0;
	cout << "Welcome to Inquiry system- ESOFT" << endl;
	cout << to_string(mno) + ". Add Inquiry" << endl; // 0
	cout << to_string(++mno) + ". Update Inquiry" << endl; // 1
	cout << to_string(++mno) + ". Search Inquiry" << endl; // 2
	cout << to_string(++mno) + ". Display Inquiry" << endl; // 3
	cout << to_string(++mno) + ". Delete Inquiry" << endl; // 4
	cout << to_string(++mno) + ". User Config" << endl; //5
	
	cout << to_string(++mno) + ". Options" << endl; //6
	cout << to_string(++mno) + ". Help" << endl; //7
	cout << to_string(++mno) + ". Quit" << endl; //8
	cout << "Enter Number of the task you wish to perform :";
	cin >> menuid;
	getchar();
	system("cls");
	switch (menuid) {
	case 0: {
		map<string, string> newinqinp;
		try {
			newinqinp = getRecords(inquiryModel::schema, vector<string> {"Inquiry Number","Date","Age"},true,true); //ignore Inq Number & date when taking inputs and validate the inputs
		}
		catch (map<string, string> e) {
			cout << endl;
			cout << "The following errors occured when processing the inputs :" << endl;
			printRecord(e);
		}	
		genericResult actionresult = inquiryModel::addInquiry(newinqinp);
		if (actionresult.success) {
			cout << "Successfully added a new Inquiry!" << endl;
		}
		else {
			cout << actionresult.message << endl;
		}
		break;
	}
	case 1: {
		
		cout << "Enter the updated inquiry-(Note that inquiry number & date is not subject to be updated)" << endl;
		map<string, string> inprecord;
		try {
			inprecord = getRecords(inquiryModel::schema, vector<string>{"Age"});
		}
		catch (map<string,string> e){
			cout << "Following Errors occured when processing the inputs:" << endl;
			printRecord(e);
			cout << "Press any key to go to Main menu" << endl;
			getchar();
			MainMenu();
		}
		map<string, string> originalrecord;
		originalrecord["Inquiry Number"] =inprecord["Inquiry Number"];
		originalrecord = inquiryModel::findRecord(originalrecord);
		inquiryModel::updateRecord(originalrecord, inprecord);
		cout << "Updated scuccesfully"<<endl;	
		break;
	}
	case 2: {
		
		cout << "Enter the details of the item you want to Search, leave the ones you don't know blank" << endl;
		map<string, string> inprecord;
		try {
			inprecord = getRecords(inquiryModel::schema, vector<string>{"Age"},false,false);
		}
		catch (map<string, string> e) {
			cout << "Following Errors occured when processing the inputs:" << endl;
			printRecord(e);
			cout << "Press any key to go to Main menu" << endl;
			getchar();
			MainMenu();
		}
		inprecord=stripNullfields(inprecord);
		system("cls");
		printRecord(inquiryModel::findRecords(inprecord));
		
		break;
	}
	case 3: {
		printRecord(inquiryModel::getRecords());
		break;
	}
	case 4: {

		cout << "Enter the details of the item you want to Delete, leave the ones you don't know blank" << endl;
		map<string, string> inprecord;
		try {
			inprecord = getRecords(inquiryModel::schema, vector<string>{"Age"}, false, false);
		}
		catch (map<string, string> e) {
			cout << "Following Errors occured when processing the inputs:" << endl;
			printRecord(e);
			cout << "Press any key to go to Main menu" << endl;
			getchar();
			MainMenu();
		}
		inprecord = stripNullfields(inprecord);
		system("cls");
		genericResult actionresult =inquiryModel::removeRecord(inprecord);
		if (actionresult.success) {
			cout << "Successfully deleted the record !" << endl;
		}
		else {
			cout << actionresult.message << endl;
		}

		break;
		break;
	}
	case 5: {
		if (currentuser().isLoggedin() & (currentuser().user["type"] == "Admin" | currentuser().user["type"] == "admin")) {
			userConfigMenu();
		}
		else {
			cout << "You need to be logged in as an Admin to access this menu" << endl;
			cout << "press any key to login again as an admin" << endl;
			getchar();
			getchar();
			LoginMenu();
		}
		break;
	}
	}
	cout << endl;
	cout << endl;
	cout << "Press any key to go back to previous menu" << endl;
	getchar(); // previos carrage return
	getchar();
	MainMenu();
	
}
	
void LoginMenu() {
	system("cls");
	char key;
	cout << "Welcome to Inquiry system - Login" << endl;
	cout << "1. Login" << endl;
	cout << "2. Reset Default config" << endl;
	cout << "Select 1 or 2 to continue" << endl;
	cin >> key;
	getchar();
	switch(key) {
	case '1': {
			if (!currentuser().isLoggedin()) {
				system("cls");
				cout << "Sign in to enter main menu :" << endl;
				userModel newUser(getRecords(userModel::schema, vector<string>{ "type" },false,true));
				genericResult signinResult = newUser.signIn();


				if (signinResult.success) {
					cout << "Successfully logged in ! - \nPress any key to enter" << endl;
					getchar();
					MainMenu();
				}
				else {
					cout << "login attemp failed ! \nPress any key to retry" << endl;
					cout << signinResult.message << endl;
					getchar();
				
					LoginMenu();

				}
			}

		}
	case '2': {
		userModel user(map<string, string>{
			{"username","Admin"},
			{"password","Admin"},
			{"type","Admin"}
		});

		user.save();
		system("cls");
		cout << "Admin info reset to defaults !, You may now login with default credentials to continue as admin" << endl;
		
		getchar();
		LoginMenu();

	 }
	}
	
	
}

void  userConfigMenu() {
	system("cls");
	cout << "<<USER Management>>" << endl;
	if (currentuser().isLoggedin()) {
		unsigned int mno = 0;
		
		cout << to_string(mno) + ". Add User" << endl;
		cout << to_string(++mno) + ". Delete User" << endl;
		cout << to_string(++mno) + ". Main Menu" << endl;
		cout << to_string(++mno) + ". Quit" << endl;
		cout << "Enter your selection 0.."+to_string(mno)+" for the relevent task" << endl;
		cin >> mno;
		cin.ignore();
		switch (mno) {
		case 0: {
			system("cls");
			map<string, string> newuserinp = getRecords(userModel::schema, vector<string> {}, true, true);
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
		case 2: {
			MainMenu();
		}
		case 3: {
			system("exit");
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

void OptionsMenu() {
	cout << "1. Change Username" << endl;
	cout << "2. Change Password" << endl;
}