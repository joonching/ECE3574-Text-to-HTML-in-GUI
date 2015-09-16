#include "text.h"

conversion::conversion()
{
	count = 0;
}

void conversion::enterFiles(char* argv[])
{
	string ifile,
		ofile;
	//set the input file and output file to a string
	ifile = argv[1];
	ofile = argv[2];

	ifstream textFile;
	textFile.open(ifile.c_str());

	ofstream outputFile;
	outputFile.open(ofile.c_str());
	int i = 0;
	while (!textFile.eof())
	{
		string line;
		
		//line reads the next line character of \n
		//<SOVLVED>problem: how do i get rid of that or not include it into vector
		//         it adds an index in the vector but i dont want that
		//problem2: I need to figure out a way to get rid of the == or - symbols
		getline(textFile, line);
		int sym_count = line.size();
		if (line.size() > 0)
		{
			convert.push_back(line);
			if (line[0] == '=' || line[0] == '-')
			{
				headerCheck(convert, sym_count, i, line);
				i--;
			}
				

			int y = 0;
			bool complete = false;
			bool completeB = false;
			for (int t = 0; t < line.size(); t++)
			{
				
				//my italicize -- check if the next isnt a * too so that i know its an italicize function call
				if (line[t] == '*' && line[t+1] != '*' && complete == false)
				{
					searchI(convert, line, t, i);
					complete = true;
				}

				if (line[t] == '*' && line[t + 1] == '*')
				{
					cout << "inside";
					//searchB(convert, line, t, i);
				}

			}
			
			i++;
			
		}
	}
	int t = 0;
	for (iter = convert.begin(); iter < convert.end(); iter++, t++)
	{
		outputFile << *iter << endl << endl;
	}
		

}

void conversion::headerCheck(vector<string> &temp1, int size, int count, string &strLine)
{
		string prev = temp1[count - 1]; //im referring to the string before the == or -


		if (size >= prev.size())
		{

			if (strLine[0] == '=')
			{
				//if greater I want to add the header tag around the <h1> around the header string
				//then i want to delete the == string;
				temp1[count - 1] = "<h1>" + prev + "</h1>";
			}
			if (strLine[0] == '-')
			{
				temp1[count - 1] = "<h2>" + prev + "</h2>";
			}

			
			temp1.erase(temp1.begin() + count);

		}

		else
		{
			//if its not greater than its just a string and just leave it as is and add a <p> to the front
			cout << "uhoh";
		}
}

string conversion::searchI(vector<string> &temp2, string strLine2, int x, int i)
{
	bool check = false;
	string italicize = "";
	int y = 0;
	for (int t = x+1; t < strLine2.size(); t++)
	{
		if (strLine2[t] == '*')
		{
			check = true; //you're done
		}

		if (strLine2[t] != '*' && check == false)
		{
			italicize = italicize + strLine2[t];
			y++;
		}
		
	}
	italicize = "<i>" + italicize + "</i>";

	convert[i].replace(x, y+2, italicize);
	
	return italicize;
}

string conversion::searchB(vector<string> &temp2, string strLine2, int x, int i)
{
	bool check = false;
	string bold = "";
	int y = 0;
	for (int t = x + 1; t < strLine2.size(); t++)
	{
		if (strLine2[t] == '*' && strLine2[t + 1] == '*')
		{
			check = true; //you're done
		}

		if (strLine2[t] != '*' && check == false)
		{
			bold = bold + strLine2[t];
			y++;
		}

	}
	bold = "<b>" + bold + "</b>";

	convert[i].replace(x, y + 2, bold);

	return bold;
}
