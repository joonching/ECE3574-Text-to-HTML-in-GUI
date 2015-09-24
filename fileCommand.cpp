#include "fileCommand.h"

fileCommand::fileCommand()
{
    textEditor = new QTextEdit;
    openned = false;
}

fileCommand::~fileCommand()
{

}

bool fileCommand::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::KeyPress)
    {
       QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
       if (keyEvent->matches(QKeySequence::Open))
       {
           fileName = QFileDialog::getOpenFileName(textEditor, tr("open"), "C:\\Users\\Josh");

               QFile oFile(fileName);
               if(oFile.open(QFile::ReadWrite|QFile::Text))
               {
                   QTextStream in(&oFile);
                   textEditor->setText(in.readAll());
                   oFile.close();
                   openned = true;
               }

       }


       else if(keyEvent->matches(QKeySequence::Save))
       {
            if(openned)
            {
                QString getFile = textEditor->toPlainText();
                QFile sfile(fileName);

                sfile.open(QFile::ReadWrite|QFile::Text);
                sfile.resize(0);
                QTextStream out(&sfile);
                out << getFile;
                sfile.close();

                QFile htmlFile(fileName + ".html");
                htmlFile.open(QFile::ReadWrite|QFile::Text);

                QTextStream printHTML(&htmlFile);
                printHTML << *fString;
                htmlFile.close();

            }

            else
            {
                QString wholeFile = textEditor->toPlainText();
                fileName = QFileDialog::getSaveFileName(textEditor, tr("save"), "C:\\Users\\Josh");
                QFile file(fileName);
                file.open(QFile::ReadWrite|QFile::Text);

                QTextStream out(&file);

                out << wholeFile;
                file.close();

                QFile htmlFile(fileName+".html");
                htmlFile.open(QFile::ReadWrite|QFile::Text);

                QTextStream printHTML(&htmlFile);
                printHTML << *fString;
                htmlFile.close();
            }
       }



        else
            return false;

    }//end of if
    else
        return QObject::eventFilter(obj, event);

    fileName = "";
}


void fileCommand::setTextEdit(QTextEdit *testEdit, QString* filename)
{
    textEditor  = testEdit;
    fString = filename;
    textEditor->installEventFilter(this);
}

