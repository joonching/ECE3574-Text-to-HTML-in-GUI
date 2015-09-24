#ifndef FILECOMMAND_H
#define FILECOMMAND_H

#include <QObject>
#include <QString>
#include <QTextEdit>
#include <QKeyEvent>
#include <QEvent>
#include <QTextStream>
#include <QFileDialog>
#include <QFile>

class fileCommand : public QObject
{
    Q_OBJECT

public:
    fileCommand();
    ~fileCommand();

    bool eventFilter(QObject *obj, QEvent *event);
    void setTextEdit(QTextEdit *testEdit, QString *filename);

private:
    QTextEdit *textEditor;
    QString fileName;
    QString *fString;
    bool openned;
};


#endif
