#include "JSONlightparser.h";
// reads a single chunk of file
map <string, string> readChunk(string lines[],int length) {
	// since its sort of dynamic array we need the length explicitly here just to keep things simple , any workaround requires too much work
	map<string, string> returnObj;
	if (lines[0] != "{") {
		throw std::runtime_error("Recieved chunk not in expected format , should start with a '{'");
	}
	int i = 0;
	for ( i= 0; i < length; i++) {
		if (i != 0 & i != length-1) {
			char *line = new char[lines[i].length() + 1];
			strcpy_s(line,lines[i].length()+1, lines[i].c_str());
			// copy lines[i] to a variable line

			auto m = cmatch{}; //holds the results of the match
			

			//R"('([^\/\\\}]+)':'([^\/\\\}]+)',?/)"
			bool x = regex_match(line, m, regex{ R"(\s*'([\w\s\.]+)':'([\w#@$\d\s\/\\\.-]+)',?)" });
			if (x) {
				returnObj[m[1]] = m[2];
			}
			else {
				throw runtime_error("Match failed in line " + to_string(i));
			}
		}

	}
	return returnObj;
}

void writeChunk(map<string, string> record,ofstream &outputfile) {
	outputfile << "{" << endl; // begining of record
	for (map<string, string>::iterator ii = record.begin(); ii != record.end(); ++ii)
	{
		outputfile << "'"+(*ii).first+"':'"+(*ii).second+"'" << endl;
	}
	outputfile << "}," << endl; // end of record
}

