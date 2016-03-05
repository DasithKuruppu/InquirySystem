#pragma once
#include "Operations.h"
#include "Validation.h"

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
	static genericResult removeUser(map<string, string> remUser) {
		genericResult returnresult;
		remUser = findWhere(remUser,location,chunksize); //get the exact record;
		if (remUser.size() == 0) {
			returnresult.message = "User dosent exist !";
			return returnresult;
		}
		else {
			deleteRecord(remUser, userModel::location, userModel::chunksize);
			returnresult.success = true;
			return returnresult;
		}
	
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
			
			returnresult.success = login(Data);
			Data = currentuser().getUser();
		}
		catch(map<string, string> e){
			
			returnresult.errorstack = e;
			returnresult.message = "error occured during sign in";
		}
		
		return returnresult;
		 
	}
	
};

struct inquiryModel {
	static int chunksize;
	static string location;
	static map <string, string> schema;

	static genericResult addInquiry(map<string, string> data) {

	}
	static map<int, map<string, string>>  getRecords() {

	}
	static map<string, string> findRecord(map<string, string> query) {
		
		return findWhere(query, inquiryModel::location, inquiryModel::chunksize);
		
	}
	static genericResult removeRecord(map<string, string> remRecord) {
		genericResult returnresult;
		remRecord = findWhere(remRecord, location, chunksize); //get the exact record;
		if (remRecord.size() == 0) {
			returnresult.message = "User dosent exist !";
			return returnresult;
		}
		else {
			deleteRecord(remRecord, inquiryModel::location, inquiryModel::chunksize);
			returnresult.success = true;
			return returnresult;
		}

	}
};
