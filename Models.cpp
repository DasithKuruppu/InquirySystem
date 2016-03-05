#include "Models.h"
string userModel::location = "";
int userModel::chunksize = 5;
map<string, string> userModel::schema = map<string, string>{};

genericResult userModel::addUser(map<string, string> data) {
	return genericResult();
}
map<int, map<string, string>>  userModel::getRecords() {
	return readfile(getConfig("user")["location.data"], userModel::chunksize);
}

