#pragma once
#include "Operations.h"
#include "Validation.h"

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
	genericResult returnresult;
	map<string, string> search;
	search["username"] = Data["username"];
	search = findWhere(search, userModel::location, userModel::chunksize);
	Data["password"] = generatehash(Data["password"]);
	if (search.size() == 0) {
		Addrecord(userModel::Data, userModel::location, userModel::chunksize);
		returnresult.success = true;
	}
	else {
		update(search, Data, userModel::location, userModel::chunksize);
		returnresult.success = true;
	}
	return returnresult;

}
genericResult signIn() {
	genericResult returnresult;
	try {

		returnresult.success = login(Data);
		Data = currentuser().getUser();
	}
	catch (map<string, string> e) {

		returnresult.errorstack = e;
		returnresult.message = "error occured during sign in";
	}

	return returnresult;

}

};

struct inquiryModel {
	static int chunksize; // Determines the length of each record
	static string location; //Determines where to fetch the data from
	static map <string, string> schema; // provides a 1:1 map of the fields : datatype to be used, data is then validated againt the schema

	static genericResult addInquiry(map<string, string> data) {
		map<string, string> findresult = findWhere(data, inquiryModel::location, inquiryModel::chunksize);
		genericResult returnresult;
		if (data.size() == 0) {
			returnresult.success = false;
			returnresult.message = "Failed to add record";
		}
		else if (findresult.size() == 0) {
			Addrecord(data, inquiryModel::location, inquiryModel::chunksize);
			returnresult.success = true;
		}
		else {
			returnresult.success = false;
			returnresult.message = "Record already exists";
		}
		return returnresult;
	}
	static void autoGenerateAge(map<int,map<string,string>> &results) {
		for (map<int, map<string, string>>::iterator ii = results.begin(); ii != results.end(); ++ii)
		{
			(*ii).second["Age"] = calculateAge((*ii).second["Date of Birth"]);
		}
	}
	static map<int, map<string, string>>  getRecords() {
		map<int, map<string, string>> results = readfile(inquiryModel::location, inquiryModel::chunksize);
		inquiryModel::autoGenerateAge(results);
		return results ;
	}
	static map<string, string> findRecord(map<string, string> query) {
		
		return findWhere(query, inquiryModel::location, inquiryModel::chunksize);
		
	}
	static map<int,map<string, string>> findRecords(map<string, string> query) {
		map<int, map<string, string>> results = searchRecords(query, inquiryModel::location, inquiryModel::chunksize);
		inquiryModel::autoGenerateAge(results);
		return results;

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
	static void updateRecord(map <string,string> originalobj,map<string,string> uptatedobj) {
		
		for (map<string, string>::iterator ii = uptatedobj.begin(); ii != uptatedobj.end(); ++ii)
			{
				if ((*ii).second == "" | (*ii).second=="Date") {
					uptatedobj[(*ii).first] = originalobj[(*ii).first];
				}

			}
		update(originalobj, uptatedobj, inquiryModel::location, inquiryModel::chunksize);
	}
	
};
