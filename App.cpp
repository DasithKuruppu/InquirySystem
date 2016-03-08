#include "Navigator.h"
#include "Models.h"
#include "Validation.h"

using namespace std;
void main()

{

	
	Initialize();
	userModel::schema = readALL(getConfig("user")["location.schema"]);
	userModel::location = getConfig("user")["location.data"];
	userModel::chunksize = 5;

	inquiryModel::schema = readALL(getConfig("inquiry")["location.schema"]);
	inquiryModel::location = getConfig("inquiry")["location.data"];
	inquiryModel::chunksize = 10;

	LoginMenu();
	
	system("Pause");
}