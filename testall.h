#include <QString>
#include <QDebug>
#include "convert.h"
#include "assert.h"
#include <QVector>

void checkSizeTest()
{
    convert c;
    int cSize, pSize;
    std::string hCheck = "header check",
                pCheck = "------------";
				
	std::string pTag = "</p>";
    c.checkSize(hCheck, pCheck,cSize, pSize);
    assert(pSize == 12);
    assert(cSize == pSize);
    pCheck = "------------p";
    c.checkSize(hCheck, pCheck, cSize, pSize);
    assert(cSize == 0);
    pCheck = "----------=-";
    c.checkSize(hCheck, pCheck, cSize, pSize);
    assert(cSize == 0);
    pCheck = "=============-";
    c.checkSize(hCheck, pCheck, cSize, pSize);
    assert(cSize == 0);
	hCheck = "<p>\nheader check";
	pCheck = "-------------" + pTag;
	c.checkSize(hCheck, pCheck, cSize, pSize);
	assert(pSize == 12);
	assert(cSize == 13);
	hCheck = "<p>header check";
	c.checkSize(hCheck, pCheck, cSize,pSize);
	assert(pSize == 12);
	qDebug("checkSize = PASS\n");
}

void  checkBoldTest()
{
	convert c;
	std::string strLine;
	strLine = "nono**bold**";
	int i = 4;
	
	c.checkBold(strLine, i);
	assert(c.returnB() == "<b>bold</b>");
	
	strLine = "yes***bold***";
	i = 3;
	c.checkBold(strLine, i);
	assert(c.returnB() == "<b>*bold</b>");
	qDebug("bold = PASS\n");
}

void checkITest()
{
	convert c;
	std::string strLine;
	strLine = "nono**bold**";
	int i = 5;
	
	c.checkItalicize(strLine, i);
	assert(c.returnI() == "<i>bold</i>");
	qDebug("Italicize = PASS\n");
}

void checkBothIB()
{
	convert c;
	std::string strLine, wholeLine,
				it = "</i>";
	strLine = "***bold***";
	wholeLine = c.searchStar(strLine);
	assert(c.returnB() == "<b>*bold</b>");
	assert(c.returnI() == "<i>bold</b>" + QString::fromStdString(it));
	assert(wholeLine == "<b><i>bold</b>" + it);
	
	strLine = "**hi my *name* is josh**";
	wholeLine = c.searchStar(strLine);
	assert(c.returnB() == "<b>hi my *name* is josh</b>");
	assert(c.returnI() == "<i>name" + QString::fromStdString(it));
	assert(wholeLine == "<b>hi my <i>name</i> is josh</b>");
	
	qDebug("Both I&B = PASS\n");
}

void nestedError()
{
    convert c;
    //this is to check for nested * and faulty header lines
   std::string testLine = "** this *is* test **\n\nCheck**Header**\n===============\n*I'm a new line\n\ncheck2*\n-------\n"
               "New Line\n\nfaultyH\n=======-\n\nfaulty";

    QString strLine = "<html><body><p><b> this <i>is</i> test </b></p><h1>\nCheck<b>Header</b>"
              "</h1><i>I'm a new line</p><h2>\ncheck2</i></h2>New Line</p><p>"
              "\nfaultyH=======-</p><p>\nfaulty</p></body></html>";

    c.parse(testLine);

    QVector<std::string> vSize = c.returnV();


    //checks the initial size of the vector
    assert(vSize.size() == 10);
    assert(c.returnH1() == "<h1>\nCheck**Header**</h1>");
    assert(c.returnH2() == "<h2>\ncheck2*</h2>");
    assert(c.returnB() == "<b>Header</b>");
    assert(c.returnI() == "<i>I'm a new line</p><h2>\ncheck2</i>");
    assert(*c.returnString() == strLine);

    qDebug("HARD CODE TEST PASSED: All Done for Hard Code Testing\n");
}

void initTest()
{
    qDebug() << "\nInitial Whole Line Testing";
    convert c;
    std::string testLine = " Big Header\n===========\n\nThis is some *fancy* text.\n\nA small header\n---------------\n\n"
                           "This is some **very** important text.\n\nThis raw html <code> is left as is.</code>";

    QString strLine = "<html><body><h1> Big Header</h1><p>\n"
                      "This is some <i>fancy</i> text.</p>"
                      "<h2>\nA small header</h2><p>"
                      "\nThis is some <b>very</b> important text.</p><p>"
                      "\nThis raw html <code> is left as is.</code></p></body></html>";


    c.parse(testLine);

    QVector<std::string> vSize = c.returnV();
    //checks the initial size of the vector
    assert(vSize.size() == 7);
    assert(c.returnH1() == "<h1> Big Header</h1>");
    assert(c.returnH2() == "<h2>\nA small header</h2>");
    assert(c.returnB() == "<b>very</b>");
    assert(c.returnI() == "<i>fancy</i>");
    assert(*c.returnString() == strLine);

}
