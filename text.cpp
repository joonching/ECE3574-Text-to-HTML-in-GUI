#include "text.h"

conversion::conversion()
{
	count = 0;
}

void conversion::enterFiles(char* argv[])
{
	string ifile,
		ofile;
	string completeLine = "";
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

		//lloop for my header
		if (line.size() > 0)
		{
			line = "<p>" + line + "</p>";
			int sym_count = line.size();
			convert.push_back(line);
			if (line[4] == '=' || line[4] == '-')
			{
				headerCheck(convert, sym_count, i, line);
				i--;
			}


			i++;

		}
	}
	int x = 0;
	for (iter = convert.begin(); iter < convert.end(); iter++)
	{

		completeLine = completeLine + *iter;
		x++;
	}


	string parsedString = searchStar(completeLine);

	int t = 0;

	while (t < parsedString.size())
	{
		if (parsedString[t] == '/' && parsedString[t + 1] == 'p')
		{
			parsedString.insert(t + 3, "\n");
		}

		t++;
	}

	cout << "<html>\n<body>\n" + parsedString + "</body>\n</html>";
	outputFile << "<html>\n<body>\n" + parsedString + "</body>\n</html>";
}

void conversion::headerCheck(vector<string> &temp1, int size, int count, string &strLine)
{
	string prev = temp1[count - 1]; //im referring to the string before the == or -
	if (size + 7 >= prev.size())
	{
		prev.erase(prev.size() - 4, 4);
		prev.erase(0, 3);
		if (strLine[4] == '=')
		{
			//if greater I want to add the header tag around the <h1> around the header string
			//then i want to delete the == string;

			temp1[count - 1] = "<h1>" + prev + "</h1>" + "\n";
		}
		if (strLine[4] == '-')
		{
			temp1[count - 1] = "<h2>" + prev + "</h2>" + "\n";
		}


		temp1.erase(temp1.begin() + count);

	}

}

//for bold and italicize
string conversion::searchStar(string& strLine2)
{

	string bold = "",
		italicize = "";


	for (int y = 0; y < strLine2.size(); y++)
	{
		bool check = false;
		bool found = false;

		//error: need to find a way so that you can print out a ** if they dont find one

		if (strLine2[y] == '*' && strLine2[y + 1] == '*') //This loop I find the first ** 
		{
			int i = 0;
			//with this one i want to be able to bring all the characters inbetween the ** and put it in a string
			for (int t = y + 2; t < strLine2.size(); t++) //once you're done you might want to set y to the value at the end of the string
			{

				if (strLine2[t] == '*' && strLine2[t + 1] == '*') //I want to run this loop until i find another ** but until then I want to put the string/word
				{											//inbetween the ** in a string. 
					check = true;							//then i want to replace the string with the html tags
					found = true;
				}

				if (check == false)
				{
					bold = bold + strLine2[t]; // I should have the word inbetween the ** in bold
					i++; //i increment beacuse I want to count how many characters I just read in...then i use this value for replacement 
				}
			}

			if (found == true)
				bold = "<b>" + bold + "</b>";

			strLine2.replace(y, i + 4, bold);
			y = 0; //i do this so i can skip over everything I just read into the file
			bold = "";

		}

		else if (strLine2[y] == '*' && isalpha(strLine2[y + 1])) //initial find of 1 star
		{
			int j = 0;
			for (int x = y + 1; x < strLine2.size(); x++)
			{
				if (strLine2[x] == '*' && strLine2[x + 1] != '*')
				{
					//cout << strLine2[x+2];
					check = true;
					//cout << " :true" << endl;
				}


				if (check == false)
				{
					italicize = italicize + strLine2[x];
					j++;
				}
			}
			italicize = "<i>" + italicize + "</i>";
			strLine2.replace(y, j + 2, italicize);
			italicize = "";
		}

	}
	//cout << strLine2;
	return strLine2;
}


