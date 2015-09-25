#include <QString>
#include <QDebug>
#include "convert.h"
#include "assert.h"
#include "testall.h"
#include <QVector>

void test()
{
    initTest();
    qDebug("INITIAL TEST PASSED");

    qDebug("--Now check for nested * and header errors: \n");
    nestedError();

    qDebug("INDIVIDUAL TESTING");
    qDebug("CheckSize function");
    checkSizeTest();

    qDebug("Bold Test");
    checkBoldTest();

    qDebug("Italicize Test");
    checkITest();

    qDebug("Bold & Italicize Test");
    checkBothIB();
    qDebug("TESTING COMPLETE");
}

