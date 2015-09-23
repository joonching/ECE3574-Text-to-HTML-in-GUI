#include <QtGui/QApplication>
#include <QHBoxLayout>
#include <QSlider>
#include <QSpinBox>
#include <QTextEdit>
#include <QWebView>
#include "gui.h"



int main(int argc, char *argv[])
{
   QApplication app(argc, argv);

   convert me;
   me.showWindow();
   return app.exec();
}
 //cmake ../textCmake
//make


