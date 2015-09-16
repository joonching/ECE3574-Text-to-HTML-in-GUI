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
	string searchI(vector<string> &temp2, string strLine2, int x, int i);
	string searchB(vector<string> &temp2, string strLine2, int x, int i);


private:
	int count;
	vector<string> convert;
	vector<string>::const_iterator iter;
	vector<string> htmlList;
	vector<string>::const_iterator iter2;
};