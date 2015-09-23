#ifndef GUI_H
#define GUI_H

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

class convert : public QObject
{
    Q_OBJECT

public:
    convert();
    ~convert();

    //QString getText();

    void showWindow();
    void showtext();
    void setWindowLayout();
    QString save(QString savedStr);
    void setup();
    QString parse(std::string plainText);
    void headerCheck(QVector<std::string> &checkString);
 private slots:
        void printToWeb();

private:
    QWebView *webView;
    QTextEdit *textEdit,
               *textE;
    QHBoxLayout *layout;
    QWidget *mainWindow;
    QPushButton *quitButton;
};

#endif
