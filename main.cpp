#include "convert.h"
#include "fileCommand.h"
#include <iostream>
#include <QString>
#include <QTextStream>
#include <QEvent>
#include <QKeyEvent>
#include "test.h"

int main(int argc, char *argv[])
{
   QApplication app(argc, argv);

   convert me;
   fileCommand yes;
   test();
   yes.setTextEdit(me.returnText(), me.returnString());
   me.showWindow();

   return app.exec();
}
 //cmake ../textCmake
//make

//QTEST_MAIN(testClass)
