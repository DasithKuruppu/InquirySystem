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
	/*bool x = valDateTime("3/2/2016 17:19:12");

	cout << calculateAge("03/03/1994");
	if (x) {
		cout << "true";
	}
	else {
		cout << "false";
	}*/
	system("Pause");
}