#ifndef GUI_H
#define GUI_H

#include <cctype>
#include <QObject>
#include <QTextEdit>
#include <QWebView>
#include <QString>
#include <QHBoxLayout>
#include <QMainWindow>
#include <QtGui>
#include <QWidget>
#include <QTextStream>
#include <QDebug>
#include <string>
#include <QVector>
#include <QKeySequence>
#include <QMenu>
#include <QFile>
#include <QMessageBox>
#include <QAction>
#include <QFileDialog>
#include "fileCommand.h"

class convert : public QObject
{
    Q_OBJECT

public:
    convert();
    ~convert();


    void checkSize (std::string &previousLine, std::string characterLine, int &cSize, int &pSize);
    void showWindow();
    void showtext();
    void setWindowLayout();
    QString save(QString savedStr);
    void setup();
    QString parse(std::string plainText);
    void headerCheck(QVector<std::string> &checkString);
    std::string searchStar(std::string & strLine2);
    void checkItalicize(std::string &iLine, int &i);
    void checkBold(std::string &bLine, int &i);
    QTextEdit* returnText();
    QString* returnString();
    void checkHeader(bool &checkChar, int &size, int &cSize, std::string cLine);

private slots:
    void printToWeb();
    //void fExit();
    //void iInfo();

private:
    QWebView *webView;
    QTextEdit *textEdit,
               *textE;
    QHBoxLayout *layout;
    QWidget *mainWindow;
    QKeySequence *openCall;
    QMenu *menu;
    QString returnStr;

};

#endif
