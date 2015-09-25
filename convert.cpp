#include "convert.h"
#include "fileCommand.h"

convert::convert()
{
    textEdit = new QTextEdit;
    mainWindow = new QWidget;
    layout = new QHBoxLayout;
    webView = new QWebView;
    openCall = new QKeySequence;
    menu = new QMenu();
}


convert::~convert()
{
    delete mainWindow;
}

QString convert::parse(std::string plainText)
{
    QVector<std::string> paragraphs;
    QVector<std::string>::const_iterator iter;
    std::string parse = plainText,
            str = "<p>", line = "";

       if (!parse.empty())
       {
           for (int i = 0; parse[i] != '\0'; i++)
           {
               if (parse[i] == '\n' && parse[i+1] == '\n')
               {
                  std::string show = str + "</p>";
                  paragraphs.push_back(show);
                  str = "<p>";
               }

               else if(parse[i] == '\n' && parse[i-1] != '\n')
               {
                   paragraphs.push_back(str);
                   str = "";
               }

               else if(parse[i+1] == '\0' && parse.size()>2)
               {
                   std::string show = str + parse[i] + "</p>";
                   paragraphs.push_back(show);
               }

               else if(parse[i+1] == '\0')
               {
                   paragraphs.push_back(str+parse[i]);
               }

               else
                   str = str + parse[i];

           }
           //for check method;
         vStr = paragraphs;
            headerCheck(paragraphs);
         }//end of if


      for (iter = paragraphs.begin(); iter < paragraphs.end(); iter++)
      {
          line = line + *iter;
      }

      searchStar(line);

      QString printLine = QString::fromStdString(line);

       printLine = "<html><body>" + printLine +"</body></html>";

       returnStr = printLine;
       return printLine;

}

void convert::headerCheck(QVector<std::string> &checkString)
{
    //remember to return a string or Qstring
    std::string prevLine,
            charLine;


    int charSize = 0,
            prevSize = 0;
   for (int i = 0; i < checkString.size(); i++)
   {
       //initial check
       //if i find a char = or - then i want to go ahead and get the previous string and compare the size
       //Make sure that its not the first (contains <p>)
       if (checkString.at(i)[0] == '=' || checkString.at(i)[0] == '-')
       {
           prevLine = checkString[i-1];
           charLine = checkString[i];

           checkSize(prevLine, charLine, charSize, prevSize);

               //check for the size and -3 because this is the case where its the beginning of a new string
               if (charSize >= prevSize)
               {
                   prevLine.erase(0,3);
                   if (checkString.at(i)[0] == '=')
                   {
                       checkString[i-1] = "<h1>" + prevLine + "</h1>";
                       h1Str = checkString[i-1];
                   }

                   if (checkString.at(i)[0] == '-')
                   {
                       checkString[i-1] = "<h2>" + prevLine + "</h2>";
                       h2Str = checkString[i-1];
                   }

                    checkString.remove(i);
               } //end of if
       } //end of if
   }//end of for
}

void convert::checkHeader(bool &checkChar, int &size,int& cSize, std::string cLine)
{
    checkChar = true;
    size = cLine.size();
    cSize = 0;
}

void convert::checkSize(std::string &previousLine, std::string characterLine, int& cSize, int& pSize)
{
    std::size_t findP, findC;
    findP = previousLine.find("<p>");
    findC = characterLine.find("</p>");
    bool badChar = false;
    int charSize = 0;

     if (findC != std::string::npos)
         charSize = characterLine.size()-4;


     else
         charSize = characterLine.size();

    for (int i = 0; i < charSize; i++)
    {
        if (isalpha(characterLine[i]))
            checkHeader(badChar,i,cSize, characterLine);

        else if(characterLine[0] == '=')
        {
           if (characterLine[i] == '-')
              checkHeader(badChar,i,cSize, characterLine);
        }

        else if (characterLine[0] == '-')
         {
            if (characterLine[i] == '=')
                 checkHeader(badChar,i,cSize,characterLine);
         }
    }
    //i want to find the size...check the case if the charLine is the last line containing the </p> char

    if (badChar == false)
    {
        if (findC != std::string::npos  )
        {
            //if i find it
            cSize = characterLine.size() - 4;
        }
        else
        {
            cSize = characterLine.size();
        }
    }

    if (findP != std::string::npos && previousLine[3] == '\n')
        pSize = previousLine.size() - 4;


    else if(findP != std::string::npos)
        pSize = previousLine.size()- 3;


    else
    {
        previousLine = "<p>" + previousLine;
        pSize = previousLine.size() - 3;
    }

}

std::string convert::searchStar(std::string &strLine2)
{
    for (int y = 0; y < strLine2.size(); y++)
    {
        if (strLine2[y] == '*' && strLine2[y + 1] == '*') //This loop I find the first **
        {
            checkBold(strLine2, y);
        }

        else if (strLine2[y] == '*') //initial find of 1 star
        {
            checkItalicize(strLine2, y);
        }
    }

    return strLine2;
}

void convert::checkBold(std::string &bLine, int &i)
{

    int j = 0;
    std::string bold = "";
    bool check = false,
            found = false;
    //with this one i want to be able to bring all the characters inbetween the ** and put it in a string
    for (int t = i + 2; t < bLine.size(); t++) //once you're done you might want to set y to the value at the end of the string
    {

        if (bLine[t] == '*' && bLine[t + 1] == '*') //I want to run this loop until i find another ** but until then I want to put the string/word
        {											//inbetween the ** in a string.
            check = true;							//then i want to replace the string with the html tags
            found = true;
        }

        if (check == false)
        {
            bold = bold + bLine[t]; // I should have the word inbetween the ** in bold
            j++; //i increment beacuse I want to count how many characters I just read in...then i use this value for replacement
        }
    }

    if (found == true)
    {
        bold = "<b>" + bold + "</b>";
        //+4 is for the ** and **
        bLine.replace(i, j + 4, bold);
        i = 0;
    }
    bStr = QString::fromStdString(bold);
    bold = "";

}

void convert::checkItalicize(std::string &iLine, int &i)
{
    std::string italicize = "";
    bool check = false,
            found = false;

    int j = 0;
    for (int x = i + 1; x < iLine.size(); x++)
    {
        if (iLine[x] == '*') //&& strLine2[x + 1] != '*')
        {

            check = true;
            found = true;

        }


        if (check == false)
        {
            italicize = italicize + iLine[x];
            j++;
        }
    }
    if (found == true)
    {
        italicize = "<i>" + italicize + "</i>";
        iLine.replace(i, j + 2, italicize);
        i = 0;
    }
    iStr = QString::fromStdString(italicize);
    italicize = "";

}

void convert::printToWeb()
{
    QString html = textEdit->toPlainText();

    std::string parseMe = html.toStdString();

    QString webText = parse(parseMe);

    webView->setHtml(webText);
}

void convert::setWindowLayout()
{
    //if set as parent then dont delete
    layout->addWidget(textEdit);
    layout->addWidget(webView);
    mainWindow->setLayout(layout);
}
void convert::setup()
{
  connect(textEdit, SIGNAL(textChanged()), this, SLOT(printToWeb()));
}

void convert::showWindow()
{
    setWindowLayout();
    setup();
    mainWindow->show();
}

QTextEdit *convert::returnText()
{
    return textEdit;
}

QString *convert::returnString()
{
    return &returnStr;
}

QString convert::returnI()
{
    return iStr;
}

QString convert::returnB()
{
    return bStr;
}

QString convert::returnH1()
{
    QString h = QString::fromStdString(h1Str);
    return h;
}

QString convert::returnH2()
{
    QString h = QString::fromStdString(h2Str);
    return h;
}

QVector<std::string> convert::returnV()
{
    return vStr;
}
