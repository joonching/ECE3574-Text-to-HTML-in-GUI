#include "convert.h"
#include "fileCommand.h"


int main(int argc, char *argv[])
{
   QApplication app(argc, argv);

   convert me;

   fileCommand yes;
   yes.setTextEdit(me.returnText(), me.returnString());

   me.showWindow();
   return app.exec();
}
 //cmake ../textCmake
//make
