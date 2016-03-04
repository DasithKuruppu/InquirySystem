#include "Navigator.h"
#include "Inputs.h"
#include "Models.h"
using namespace std;
void main()
{
	//initializeDefinitions();
	
	//printDefinitions(getDefinitions("User"));
	
	
		//update(originalrecord,updaterecord, loc);
		//printRecord();
	Initialize();
	userModel::schema = readALL(getConfig("user")["location.schema"]);
	userModel::location = getConfig("user")["location.data"];
	userModel::chunksize = 5;
		LoginMenu();
	system("Pause");
}