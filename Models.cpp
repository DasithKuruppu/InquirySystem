#include "Models.h"
string userModel::location = "";
int userModel::chunksize = 5;
map<string, string> userModel::schema = map<string, string>{};

genericResult userModel::addUser(map<string, string> data) {
	data["password"] = generatehash(data["password"]);
	map<string, string> temp = data;
	temp["type"] = "";
	temp["password"] = "";
	temp = stripNullfields(temp);
	map<string, string> findresult = findWhere(temp, userModel::location, userModel::chunksize);
	genericResult returnresult;
	if (data.size() == 0) {
		returnresult.success = false;
		returnresult.message = "Failed to add record";
	}
	else if (findresult.size() == 0) {
		Addrecord(data, userModel::location, userModel::chunksize);
		returnresult.success = true;
	}
	else {
		returnresult.success = false;
		returnresult.message = "Record already exists";
	}
	return returnresult;
}
map<int, map<string, string>>  userModel::getRecords() {
	return readfile(getConfig("user")["location.data"], userModel::chunksize);
}

string inquiryModel::location = "";
int inquiryModel::chunksize = 10;
map<string, string> inquiryModel::schema = map<string, string>{};
