#pragma once
#include "Operations.h";
#include "Validation.h";

struct genericResult {
	bool success = false;
	string message = "";
	map<string, string> errorstack;
};
struct userModel
{
	userModel(map<string, string> data) {
		if (data.size() != 0) {
			Data = data;
		}
	}
	map <string, string> Data = {};
	bool isExisting = false;
	static int chunksize;
	static string location;
	static map <string, string> schema;
	static genericResult addUser(map<string, string> data);
	static map<int, map<string, string>>  getRecords();
	static map<string, string> findRecord(map<string,string> query) {
		return findWhere(query, userModel::location, userModel::chunksize);
	}
	static void  removeUser(map<string, string> remUser) {
		remUser = findRecord(remUser); //get the exact record;
		deleteRecord(remUser, userModel::location, userModel::chunksize);
	}
	genericResult editProfile(string username="",string password="") {
		map<string, string> editedobj;
		if (username != "") {
			editedobj["username"] = username;
		}
		if (password != "") {
			editedobj["password"] = password;
		}
		editedobj["type"] = Data["type"];
		update(userModel::Data, editedobj, userModel::location, userModel::chunksize);
	}

	genericResult save() {
		map<string,string> findresult=findWhere(userModel::Data, userModel::location, userModel::chunksize);
		genericResult returnresult;
		if (findresult.size() == 0) {
			Addrecord(userModel::Data, userModel::location, userModel::chunksize);
			returnresult.success = true;
		}
		else {
			returnresult.success = false;
			returnresult.message = "Record already exists";
		}
		return returnresult;
		
	}
	genericResult signIn() {
		genericResult returnresult;
		try {
			returnresult.success = login(userModel::findRecord(Data));
			Data = currentuser().getUser();
		}
		catch(map<string, string> e){
			
			returnresult.errorstack = e;
			returnresult.message = "error occured during signin";
		}
		
		return returnresult;
		 
	}
	
};


