#include <iostream>
#include <vector>
#include <stack>
#include <fstream>
#include <sstream>
#include <string>
#include <istream>

using namespace std;

class conversion
{
public:
	conversion();
	void enterFiles(char* argv[]);
	void headerCheck(vector<string> &temp1, int size, int count, string &strLine);
	void starCheck(vector<string> &temp2);
	string searchStar(string &strLine2);



private:
	int count;
	vector<string> convert;
	vector<string>::const_iterator iter;
	vector<string> htmlList;
	vector<string>::const_iterator iter2;
};