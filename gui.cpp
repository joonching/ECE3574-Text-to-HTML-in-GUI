#include "gui.h"

#include <iostream>
convert::convert()
{
    textEdit = new QTextEdit;
    textE = new QTextEdit;
    mainWindow = new QWidget;
    layout = new QHBoxLayout;
    webView = new QWebView;
    quitButton = new QPushButton;
}


convert::~convert()
{
    delete mainWindow;
}

QString convert::parse(std::string plainText)
{

    QVector<std::string> paragraphs;
    QVector<std::string>::const_iterator iter;
    std::string parse = plainText;
    std::string str = "<p>";
       if (parse.size() != 0)
       {
           for (int i = 0; i < parse.size(); i++)
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

               else if(parse[i+1] == '\0')
               {
                   std::string show = str + "</p>";
                   paragraphs.push_back(show);
               }

               else
                   str = str + parse[i];

           }
            headerCheck(paragraphs);
         }//end of if





      std::string line = "" ;
      for (iter = paragraphs.begin(); iter < paragraphs.end(); iter++)
      {
          line = line + *iter;
      }

      QString printLine = QString::fromStdString(line);

       qDebug() << printLine << paragraphs.size() << endl;

       printLine = "<html><body>" + printLine +"</html></body>";
       return printLine;
}


//change back to vector
void convert::headerCheck(QVector<std::string> &checkString)
{
    //remember to return a string or Qstring
    std::string prevLine,
            charLine;
    std::size_t findP, findC;

    int charSize, prevSize;
   for (int i = 0; i < checkString.size(); i++)
   {
       //initial check
       //if i find a char = or - then i want to go ahead and get the previous string and compare the size
       //Make sure that its not the first (contains <p>)
       if (checkString.at(i)[0] == '=' || checkString.at(i)[0] == '-')
       {

           prevLine = checkString[i-1];
           charLine = checkString[i];
           findP = prevLine.find("<p>");
           findC = charLine.find("</p>");

           //i want to find the size...check the case if the charLine is the last line containing the </p> char
           if (findC != std::string::npos )
           {
               charSize = charLine.size() - 4;

           }
           else
           {
               charSize = charLine.size();
           }



           if (findP != std::string::npos && prevLine[3] == '\n')
               prevSize = prevLine.size() - 5;


           else if(findP != std::string::npos)
               prevSize = prevLine.size()- 4;


           else
           {
               prevSize = prevLine.size();
           }




               //check for the size and -3 because this is the case where its the beginning of a new string
               if (charSize >= prevSize)
               {
                   prevLine.erase(0,3);
                  // qDebug() << "inside";
                   if (checkString.at(i)[0] == '=')
                   {
                       checkString[i-1] = "<h1>" + prevLine + "</h1>";
                   }

                   if (checkString.at(i)[0] == '-')
                   {
                       checkString[i-1] = "<h2>" + prevLine + "</h2>";
                   }
               }

               checkString.remove(i);


       }
   }
}



void convert::printToWeb()
{
    QString html = textEdit->toPlainText();
    std::string parseMe = html.toStdString();



    QString webText = parse(parseMe);
    //size for html starts at 447
    //qDebug() << html;

    webView->setHtml(webText);
}


void convert::setWindowLayout()
{
    quitButton->setText("quit");
    //if set as parent then dont delete
    layout->addWidget(textEdit);
    layout->addWidget(webView);
    layout->addWidget(quitButton);

    mainWindow->setLayout(layout);
}
void convert::setup()
{
  connect(textEdit, SIGNAL(textChanged()), this, SLOT(printToWeb()));
}

void convert::showWindow()
{
    setup();
    setWindowLayout();
    mainWindow->show();
}
